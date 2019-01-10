
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sys/uio.h"
#include "wl_main.h"
extern "C"
{
#include "SDL.h"
}

void wolfTask(void *pvParameters)
{
    char *argv[]={"", NULL};
    main(1, argv);
}

extern "C" void app_main(void)
//void app_main(void)
{
	xTaskCreatePinnedToCore(&wolfTask, "wolfTask", 22000, NULL, 5, NULL, 0/*tskNO_AFFINITY*/);
}
