/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#define mainBACKLIGHT_TIMER_PERIOD		( pdMS_TO_TICKS( 5000UL ) )

/* Private function prototypes -----------------------------------------------*/
/* The Software timer callback functions. */
static void prvBacklightTimerCallback( TimerHandle_t xTimer );
/* The task functions. */
static void vKeyHitTask( void *pvParameters );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

extern uint8_t count_i;
static BaseType_t xSimulatedBacklightOn = pdFALSE;
static TimerHandle_t xBacklightTimer = NULL;

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	xSimulatedBacklightOn = pdFALSE;

	xBacklightTimer = xTimerCreate( "Backlight", mainBACKLIGHT_TIMER_PERIOD, pdFALSE, 0, prvBacklightTimerCallback );

	xTaskCreate( vKeyHitTask, "Key poll", configMINIMAL_STACK_SIZE, NULL, 3, NULL );

	/* Start the timer. */
	xTimerStart( xBacklightTimer, 0 );
}

static void prvBacklightTimerCallback( TimerHandle_t xTimer )
{
	TickType_t xTimeNow = xTaskGetTickCount();

	/* The backlight timer expired, turn the backlight off. */
	xSimulatedBacklightOn = pdFALSE;

	/* Print the time at which the backlight was turned off. */
	printf( "Timer expired, turning backlight OFF at time %d\r\n", xTimeNow );
}

static void vKeyHitTask( void *pvParameters )
{
	const TickType_t xShortDelay = pdMS_TO_TICKS( 50 );
	TickType_t xTimeNow;

	printf( "Press a key to turn the backlight on.\r\n" );

	for( ;; )
	{
		/* Has a key been pressed? */
		if(count_i != 0 )
		{
			/* Record the time at which the key press was noted. */
			xTimeNow = xTaskGetTickCount();

			/* A key has been pressed. */
			if( xSimulatedBacklightOn == pdFALSE )
			{
				xSimulatedBacklightOn = pdTRUE;
				printf( "Key pressed, turning backlight ON at time %d\r\n", xTimeNow );
			}
			else
			{
				printf( "Key pressed, resetting software timer at time %d\r\n", xTimeNow );
			}

			xTimerReset( xBacklightTimer, xShortDelay );
		}

		vTaskDelay( xShortDelay );
	}
}
