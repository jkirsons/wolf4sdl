#include "SDL_video.h"
#include "SDL.h"
#include "SDL_blit.h"

#define SPI_BUS TFT_VSPI_HOST

SDL_Surface* primary_surface;

int SDL_LockSurface(SDL_Surface *surface)
{
    return 0;
}

void SDL_UnlockSurface(SDL_Surface* surface)
{

}

void SDL_UpdateRect(SDL_Surface *screen, Sint32 x, Sint32 y, Sint32 w, Sint32 h)
{
    SDL_Flip(screen);
}

SDL_VideoInfo *SDL_GetVideoInfo(void)
{
    SDL_VideoInfo *info = malloc(sizeof(SDL_VideoInfo));
    info->hw_available = 0;
    info->wm_available = 0;
    info->video_mem = 1024*4;
    info->blit_hw = 0;
    info->blit_hw_CC = 0;
    info->blit_hw_A = 0;
    info->blit_sw = 0;
    info->blit_sw_CC = 0;
    info->blit_sw_A = 0;
    info->vfmt = NULL;
    info->vfmt = malloc(sizeof(SDL_PixelFormat));

    info->vfmt->palette = NULL;
    info->vfmt->BitsPerPixel = 8;
    info->vfmt->BytesPerPixel = 1;
    info->vfmt->Rloss = 0;
    info->vfmt->Gloss = 0;
    info->vfmt->Bloss = 0;
    info->vfmt->Aloss = 0;
    info->vfmt->Rshift = 0;
    info->vfmt->Gshift = 0;
    info->vfmt->Bshift = 0;
    info->vfmt->Ashift = 0;
    info->vfmt->Rmask = 0;
    info->vfmt->Gmask = 0;
    info->vfmt->Bmask = 0;
    info->vfmt->Amask = 0;
    info->vfmt->colorkey = 0;
    info->vfmt->alpha = 0;

    return info;
}

char *SDL_VideoDriverName(char *namebuf, int maxlen)
{
    return "Gadget Workbench - Awesome SPI TFT Driver";
}


SDL_Rect **SDL_ListModes(SDL_PixelFormat *format, Uint32 flags)
{
    SDL_Rect mode[1] = {{0,0,320,200}};
    return &mode;
}

void SDL_WM_SetCaption(const char *title, const char *icon)
{
    printf("Title: %s\n", title);
}

char *SDL_GetKeyName(SDLKey key)
{
    return (char *)"";
}

IRAM_ATTR Uint32 SDL_GetTicks(void)
{
    return esp_timer_get_time() / 1000;    
}

Uint32 SDL_WasInit(Uint32 flags)
{
    //return (tft == NULL);
	return 0;
}

int SDL_InitSubSystem(Uint32 flags)
{
    if(flags == SDL_INIT_VIDEO)
    {
    	spi_lcd_init();
        SDL_CreateRGBSurface(0, 320, 200, 8, 0,0,0,0);
    }
    return 0; // 0 = OK, -1 = Error
}




SDL_Surface *SDL_CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
{

    SDL_Surface *surface = (SDL_Surface *)calloc(1, sizeof(SDL_Surface));
    SDL_Rect rect = { .x=0, .y=0, .w=width, .h=height};
    SDL_Color col = {.r=0, .g=0, .b=0, .unused=0};
    SDL_Palette pal =  {.ncolors=1, .colors=&col};
    SDL_PixelFormat* pf = (SDL_PixelFormat*)calloc(1, sizeof(SDL_PixelFormat));
	pf->palette = &pal;
	pf->BitsPerPixel = 8;
	pf->BytesPerPixel = 1;
	pf->Rloss = 0; pf->Gloss = 0; pf->Bloss = 0; pf->Aloss = 0,
	pf->Rshift = 0; pf->Gshift = 0; pf->Bshift = 0; pf->Ashift = 0;
	pf->Rmask = 0; pf->Gmask = 0; pf->Bmask = 0; pf->Amask = 0;
	pf->colorkey = 0;
	pf->alpha = 0;

    surface->flags = flags;
    surface->format = pf;
    surface->w = width;
    surface->h = height;
    surface->pitch = width*(depth/8);
    surface->clip_rect = rect;
    surface->refcount = 1;
    surface->pixels = heap_caps_malloc(width*height*1, MALLOC_CAP_SPIRAM);
    surface->map = malloc(sizeof(SDL_BlitMap));
    surface->map->sw_blit = SDL_SoftBlit;
    surface->map->sw_data = malloc(sizeof(pub_swaccel));
    surface->map->sw_data->blit = SDL_BlitCopy;


    memset(surface->pixels,0,(width*height/sizeof(surface->pixels)));
    if(primary_surface == NULL)
    	primary_surface = surface;
    return surface;
}

int SDL_FillRect(SDL_Surface *dst, SDL_Rect *dstrect, Uint32 color)
{
    if(dst == NULL )//|| dst->sprite == NULL)
    {
        // Draw directly on screen
    	//if(dstrect == NULL)
    		//TFT_fillWindow(TFT_BLACK);
    	//else
    		//TFT_fillRect(dstrect->x, dstrect->y, dstrect->w, dstrect->h, TFT_BLACK);
    } else {
    	if(dstrect != NULL)
    	{
			for(int y = dstrect->y; y < dstrect->y + dstrect->h;y++)
				memset((unsigned char *)dst->pixels + y*320 + dstrect->x, (unsigned char)color, dstrect->w);
    	} else {
    		memset(dst->pixels, (unsigned char)color, dst->pitch*dst->h);
    	}
    }
    return 0;
}

SDL_Surface *SDL_GetVideoSurface(void)
{
    return primary_surface;
}

Uint32 SDL_MapRGB(SDL_PixelFormat *fmt, Uint8 r, Uint8 g, Uint8 b)
{
    if(fmt->BitsPerPixel == 16)
    {
        uint16_t bb = (b >> 3) & 0x1f;
        uint16_t gg = ((g >> 2) & 0x3f) << 5;
        uint16_t rr = ((r >> 3) & 0x1f) << 11;
        return (Uint32) (rr | gg | bb);        
    }
    return (Uint32)0;
}

int SDL_SetColors(SDL_Surface *surface, SDL_Color *colors, int firstcolor, int ncolors)
{
	for(int i = firstcolor; i < firstcolor+ncolors; i++)
	{
		int v=((colors[i].r>>3)<<11)+((colors[i].g>>2)<<5)+(colors[i].b>>3);
		lcdpal[i]=(v>>8)+(v<<8);
	}
	return 1;
}

SDL_Surface *SDL_SetVideoMode(int width, int height, int bpp, Uint32 flags)
{
	return SDL_GetVideoSurface();
}

void SDL_FreeSurface(SDL_Surface *surface)
{
    free(surface->pixels);
    free(surface->format);
    surface->refcount = 0;
}

void SDL_QuitSubSystem(Uint32 flags)
{

}

int SDL_Flip(SDL_Surface *screen)
{
	spi_lcd_send_boarder(screen->pixels, 20);
	//spi_lcd_send(screen->pixels);
	return 0;
}

int SDL_VideoModeOK(int width, int height, int bpp, Uint32 flags)
{
	if(bpp == 8)
		return 1;
	return 0;
}

SemaphoreHandle_t display_mutex = NULL;

void SDL_LockDisplay()
{
    if (display_mutex == NULL)
    {
        printf("Creating display mutex.\n");
        display_mutex = xSemaphoreCreateMutex();
        if (!display_mutex) 
            abort();
        //xSemaphoreGive(display_mutex);
    }

    if (!xSemaphoreTake(display_mutex, 60000 / portTICK_RATE_MS))
    {
        printf("Timeout waiting for display lock.\n");
        abort();
    }
    //printf("L");   
    //taskYIELD(); 
}

void SDL_UnlockDisplay()
{
    if (!display_mutex) 
        abort();
    if (!xSemaphoreGive(display_mutex))
        abort();

    //printf("U ");
    //taskYIELD();
}

/*
 * Set the physical and/or logical colormap of a surface:
 * Only the screen has a physical colormap. It determines what is actually
 * sent to the display.
 * The logical colormap is used to map blits to/from the surface.
 * 'which' is one or both of SDL_LOGPAL, SDL_PHYSPAL
 *
 * Return nonzero if all colours were set as requested, or 0 otherwise.
 */
int SDL_SetPalette(SDL_Surface *screen, int which,
		   SDL_Color *colors, int firstcolor, int ncolors)
{
    return SDL_SetColors(screen, colors, firstcolor, ncolors);
}

/*
int SDL_UpperBlit (SDL_Surface *src, SDL_Rect *srcrect,
		   SDL_Surface *dst, SDL_Rect *dstrect)
{

    return 0;
}
*/

/* 
 * Set up a blit between two surfaces -- split into three parts:
 * The upper part, SDL_UpperBlit(), performs clipping and rectangle 
 * verification.  The lower part is a pointer to a low level
 * accelerated blitting function.
 *
 * These parts are separated out and each used internally by this 
 * library in the optimimum places.  They are exported so that if
 * you know exactly what you are doing, you can optimize your code
 * by calling the one(s) you need.
 */
int SDL_LowerBlit (SDL_Surface *src, SDL_Rect *srcrect,
				SDL_Surface *dst, SDL_Rect *dstrect)
{
	SDL_blit do_blit;
	SDL_Rect hw_srcrect;
	SDL_Rect hw_dstrect;

	/* Check to make sure the blit mapping is valid */
	if ( (src->map->dst != dst) ||
             (src->map->dst->format_version != src->map->format_version) ) {
		//if ( SDL_MapSurface(src, dst) < 0 ) {
		//	return(-1);
		//}
	}

	/* Figure out which blitter to use */
    /*
	if ( (src->flags & SDL_HWACCEL) == SDL_HWACCEL ) {
		if ( src == SDL_VideoSurface ) {
			hw_srcrect = *srcrect;
			hw_srcrect.x += current_video->offset_x;
			hw_srcrect.y += current_video->offset_y;
			srcrect = &hw_srcrect;
		}
		if ( dst == SDL_VideoSurface ) {
			hw_dstrect = *dstrect;
			hw_dstrect.x += current_video->offset_x;
			hw_dstrect.y += current_video->offset_y;
			dstrect = &hw_dstrect;
		}
		do_blit = src->map->hw_blit;
	} else {
    */    
		do_blit = src->map->sw_blit;
	//}
	return(do_blit(src, srcrect, dst, dstrect));
}


int SDL_UpperBlit (SDL_Surface *src, SDL_Rect *srcrect,
		   SDL_Surface *dst, SDL_Rect *dstrect)
{
        SDL_Rect fulldst;
	int srcx, srcy, w, h;

	/* Make sure the surfaces aren't locked */
	if ( ! src || ! dst ) {
		SDL_SetError("SDL_UpperBlit: passed a NULL surface");
		return(-1);
	}
	if ( src->locked || dst->locked ) {
		SDL_SetError("Surfaces must not be locked during blit");
		return(-1);
	}

	/* If the destination rectangle is NULL, use the entire dest surface */
	if ( dstrect == NULL ) {
	        fulldst.x = fulldst.y = 0;
		dstrect = &fulldst;
	}

	/* clip the source rectangle to the source surface */
	if(srcrect) {
	        int maxw, maxh;
	
		srcx = srcrect->x;
		w = srcrect->w;
		if(srcx < 0) {
		        w += srcx;
			dstrect->x -= srcx;
			srcx = 0;
		}
		maxw = src->w - srcx;
		if(maxw < w)
			w = maxw;

		srcy = srcrect->y;
		h = srcrect->h;
		if(srcy < 0) {
		        h += srcy;
			dstrect->y -= srcy;
			srcy = 0;
		}
		maxh = src->h - srcy;
		if(maxh < h)
			h = maxh;
	    
	} else {
	        srcx = srcy = 0;
		w = src->w;
		h = src->h;
	}

	/* clip the destination rectangle against the clip rectangle */
	{
	        SDL_Rect *clip = &dst->clip_rect;
		int dx, dy;

		dx = clip->x - dstrect->x;
		if(dx > 0) {
			w -= dx;
			dstrect->x += dx;
			srcx += dx;
		}
		dx = dstrect->x + w - clip->x - clip->w;
		if(dx > 0)
			w -= dx;

		dy = clip->y - dstrect->y;
		if(dy > 0) {
			h -= dy;
			dstrect->y += dy;
			srcy += dy;
		}
		dy = dstrect->y + h - clip->y - clip->h;
		if(dy > 0)
			h -= dy;
	}

	if(w > 0 && h > 0) {
	        SDL_Rect sr;
	        sr.x = srcx;
		sr.y = srcy;
		sr.w = dstrect->w = w;
		sr.h = dstrect->h = h;
		return SDL_LowerBlit(src, &sr, dst, dstrect);
	}
	dstrect->w = dstrect->h = 0;
	return 0;
}