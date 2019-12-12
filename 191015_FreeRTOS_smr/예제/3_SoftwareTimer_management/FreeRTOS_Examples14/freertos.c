/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#define mainONE_SHOT_TIMER_PERIOD		( pdMS_TO_TICKS( 3333UL ) )
#define mainAUTO_RELOAD_TIMER_PERIOD	( pdMS_TO_TICKS( 500UL ) )

/* Private function prototypes -----------------------------------------------*/
/* The Software timer callback functions. */
static void prvOneShotTimerCallback( TimerHandle_t xTimer );
static void prvAutoReloadTimerCallback( TimerHandle_t xTimer );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */


/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	TimerHandle_t xAutoReloadTimer, xOneShotTimer;
	BaseType_t xTimer1Started, xTimer2Started;

	/* Create the one shot software timer */
	xOneShotTimer = xTimerCreate( "OneShot", mainONE_SHOT_TIMER_PERIOD, pdFALSE, 0, prvOneShotTimerCallback );

	/* Create the auto-reload software timer */
	xAutoReloadTimer = xTimerCreate( "AutoReload", mainAUTO_RELOAD_TIMER_PERIOD, pdTRUE, 0, prvAutoReloadTimerCallback );

	/* Check the timers were created. */
	if( ( xOneShotTimer != NULL ) && ( xAutoReloadTimer != NULL ) )
	{
		/* Start the software timers */
		xTimer1Started = xTimerStart( xOneShotTimer, 0 );
		xTimer2Started = xTimerStart( xAutoReloadTimer, 0 );

		if( ( xTimer1Started == pdPASS ) && ( xTimer2Started == pdPASS ) )
		{
			printf("Start Software timer\r\n");
		}
	}
}

static void prvOneShotTimerCallback( TimerHandle_t xTimer )
{
	static TickType_t xTimeNow;

	/* Obtain the current tick count. */
	xTimeNow = xTaskGetTickCount();

	printf( "One-shot timer callback executing %d\r\n", xTimeNow );
}

static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
{
	static TickType_t xTimeNow;

	/* Obtain the current tick count. */
	xTimeNow = xTaskGetTickCount();

	printf( "Auto-reload timer callback executing %d\r\n", xTimeNow );
}
