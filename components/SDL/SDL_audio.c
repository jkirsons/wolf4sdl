#include "SDL_audio.h"

SDL_AudioSpec as;
unsigned char *sdl_buffer;
unsigned char *out_buffer;
void *user_data;
bool paused = true;
bool locked = false;
xSemaphoreHandle xSemaphoreAudio = NULL;

char global_volume = 20;

IRAM_ATTR void audioToOdroidGoFormat(unsigned char * buf, unsigned char * out_buf, int len)
{

	Sint16 *sbuf = buf;
	Uint16 *ubuf = out_buf;

	int32_t dac0;
	int32_t dac1;

	if(buf != NULL && len > 0)
		//for(int i = len-2; i >= 0; i-=2)
		for(int i = 0; i < (len / 2); i += 1)  
		{
			Sint16 range = *sbuf * global_volume / 100 >> 8 ; 
			sbuf += as.channels;

			// Convert to differential output
			if (range > 127)
			{
				dac1 = (range - 127);
				dac0 = 127;
			}
			else if (range < -127)
			{
				dac1  = (range + 127);
				dac0 = -127;
			}
			else
			{
				dac1 = 0;
				dac0 = range;
			}

			dac0 += 0x80;
			dac1 = 0x80 - dac1;

			dac0 <<= 8;
			dac1 <<= 8;

			ubuf[i*2] = (int16_t)dac1;
			ubuf[i*2 + 1] = (int16_t)dac0;
		}
}

IRAM_ATTR void updateTask(void *arg)
{
  size_t bytesWritten;
  while(1)
  {
	  if(!paused){
		  //memset(out_buffer, 0, SAMPLECOUNT*SAMPLESIZE*2);
		  //memset(sdl_buffer, 0, SAMPLECOUNT*SAMPLESIZE);
		  SDL_LockAudio();
		  (*as.callback)(NULL, sdl_buffer, SAMPLECOUNT*SAMPLESIZE);
		  SDL_UnlockAudio();

		  audioToOdroidGoFormat(sdl_buffer, out_buffer, SAMPLECOUNT*SAMPLESIZE);
		  ESP_ERROR_CHECK(i2s_write(I2S_NUM_0, out_buffer, SAMPLECOUNT*SAMPLESIZE*2, &bytesWritten, 500 / portTICK_PERIOD_MS /*portMAX_DELAY*/ ));
		  
	  } else {
		  vTaskDelay( 5 );
	  }
	  taskYIELD();
	  //vTaskDelay( 1 );
  }
}

void SDL_AudioInit()
{
	sdl_buffer = heap_caps_malloc(SAMPLECOUNT * SAMPLESIZE, MALLOC_CAP_8BIT);
	out_buffer = heap_caps_malloc(SAMPLECOUNT * SAMPLESIZE * 2, MALLOC_CAP_8BIT);
	static const i2s_config_t i2s_config = {
	.mode = I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN,
	.sample_rate = SAMPLERATE, 
	.bits_per_sample = SAMPLESIZE*8, /* the DAC module will only take the 8bits from MSB */
	.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
	.communication_format = I2S_COMM_FORMAT_I2S_LSB,
	.dma_buf_count = 2,
	.dma_buf_len = SAMPLECOUNT * SAMPLESIZE,
	.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,                                //Interrupt level 1
    .use_apll = 0
	};
	static const int i2s_num = I2S_NUM_0; // i2s port number

	ESP_ERROR_CHECK(i2s_driver_install(i2s_num, &i2s_config, 0, NULL));   //install and start i2s driver

	ESP_ERROR_CHECK(i2s_set_pin(i2s_num, NULL));
	//ESP_ERROR_CHECK(i2s_set_clk(i2s_num, SAMPLERATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO));
	ESP_ERROR_CHECK(i2s_set_dac_mode(I2S_DAC_CHANNEL_BOTH_EN));	
}

int SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained)
{
	SDL_AudioInit();
	memset(obtained, 0, sizeof(SDL_AudioSpec)); 
	obtained->freq = SAMPLERATE;
	obtained->format = desired->format;
	obtained->channels = desired->channels;
	obtained->samples = SAMPLECOUNT * SAMPLESIZE;
	obtained->callback = desired->callback;
	memcpy(&as,obtained,sizeof(SDL_AudioSpec));  

	xTaskCreatePinnedToCore(&updateTask, "updateTask", 5000, NULL, 2, NULL, tskNO_AFFINITY); //tskNO_AFFINITY
	printf("audio task started\n");
	return 0;
}

void SDL_PauseAudio(int pause_on)
{
	paused = pause_on;
}

void SDL_CloseAudio(void)
{
	  i2s_driver_uninstall(I2S_NUM_0); //stop & destroy i2s driver
	  free(sdl_buffer);
}

/* Duplicate a mono channel to both stereo channels */
IRAM_ATTR void SDLCALL SDL_ConvertStereo(SDL_AudioCVT *cvt, Uint16 format)
{
	int i;
	if ( (format & 0xFF) == 16 ) {
		Uint16 *src, *dst;

		src = (Uint16 *)(cvt->buf+cvt->len_cvt);
		dst = (Uint16 *)(cvt->buf+cvt->len_cvt*2);
		for ( i=cvt->len_cvt/2; i; --i ) {
			dst -= 2;
			src -= 1;
			dst[0] = src[0];
			dst[1] = src[0];
		}
	} else {
		Uint8 *src, *dst;

		src = cvt->buf+cvt->len_cvt;
		dst = cvt->buf+cvt->len_cvt*2;
		for ( i=cvt->len_cvt; i; --i ) {
			dst -= 2;
			src -= 1;
			dst[0] = src[0];
			dst[1] = src[0];
		}
	}
	cvt->len_cvt *= 2;
	if ( cvt->filters[++cvt->filter_index] ) {
		cvt->filters[cvt->filter_index](cvt, format);
	}
}

int SDL_BuildAudioCVT(SDL_AudioCVT *cvt, Uint16 src_format, Uint8 src_channels, int src_rate, Uint16 dst_format, Uint8 dst_channels, int dst_rate)
{
	cvt->len_mult = 1;
	cvt->len = SAMPLECOUNT*SAMPLESIZE*2;
	
	cvt->needed = 0;
	cvt->filter_index = 0;
	cvt->filters[0] = NULL;
	cvt->len_ratio = 1.0;

	/* Last filter:  Mono/Stereo conversion */
	if ( src_channels != dst_channels ) {
		if ( (src_channels == 1) && (dst_channels > 1) ) {
			cvt->filters[cvt->filter_index++] = 
						SDL_ConvertStereo;
			cvt->len_mult *= 2;
			src_channels = 2;
			cvt->len_ratio *= 2;
		}
		while ( (src_channels*2) <= dst_channels ) {
			cvt->filters[cvt->filter_index++] = 
						SDL_ConvertStereo;
			cvt->len_mult *= 2;
			src_channels *= 2;
			cvt->len_ratio *= 2;
		}
		/* This assumes that 4 channel audio is in the format:
		     Left {front/back} + Right {front/back}
		   so converting to L/R stereo works properly.
		 */
/*		
		while ( ((src_channels%2) == 0) &&
				((src_channels/2) >= dst_channels) ) {
			cvt->filters[cvt->filter_index++] =
						 SDL_ConvertMono;
			src_channels /= 2;
			cvt->len_ratio /= 2;
		}
*/		
		if ( src_channels != dst_channels ) {
			/* Uh oh.. */;
		}
	}
	
	/* Set up the filter information */
	if ( cvt->filter_index != 0 ) {
		cvt->needed = 1;
		cvt->src_format = src_format;
		cvt->dst_format = dst_format;
		cvt->len = 0;
		cvt->buf = NULL;
		cvt->filters[cvt->filter_index] = NULL;
	}
	return(cvt->needed);
}

IRAM_ATTR int SDL_ConvertAudio(SDL_AudioCVT *cvt)
{
#if 0
	/* Make sure there's data to convert */
	if ( cvt->buf == NULL ) {
		SDL_SetError("No buffer allocated for conversion");
		return(-1);
	}
	/* Return okay if no conversion is necessary */
	cvt->len_cvt = cvt->len;
	if ( cvt->filters[0] == NULL ) {
		return(0);
	}

	/* Set up the conversion and go! */
	cvt->filter_index = 0;
	cvt->filters[0](cvt, cvt->src_format);
#endif
	return 0;
}

void SDL_LockAudio(void)
{
    if (xSemaphoreAudio == NULL)
    {
        printf("Creating audio mutex.\n");
        xSemaphoreAudio = xSemaphoreCreateMutex();
        if (!xSemaphoreAudio) 
            abort();
    }

    if (!xSemaphoreTake(xSemaphoreAudio, 5000 / portTICK_RATE_MS))
    {
        printf("Timeout waiting for audio lock.\n");
        abort();
    }		
}

void SDL_UnlockAudio(void)
{
    if (!xSemaphoreAudio) 
        abort();
    if (!xSemaphoreGive(xSemaphoreAudio))
        abort();		 
}

/*
 * Moved here from SDL_mixer.c, since it relies on internals of an opened
 *  audio device (and is deprecated, by the way!).
 */
//void SDL_MixAudio(Uint8 * dst, const Uint8 * src, Uint32 len, int volume)
//{
//}
