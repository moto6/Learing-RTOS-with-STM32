/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#define HEALTHY_PERIOD		( pdMS_TO_TICKS( 2000UL ) )
#define ERROR_PERIOD		( pdMS_TO_TICKS( 300UL ) )

/* Private function prototypes -----------------------------------------------*/
/* The Software timer callback functions. */
static void prvTimerCallback( TimerHandle_t xTimer );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

extern uint8_t count_i;
TimerHandle_t xAutoReloadTimer;


/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	BaseType_t xTimerStarted;

	/* Create the auto-reload software timer */
	xAutoReloadTimer = xTimerCreate( "AutoReload", HEALTHY_PERIOD, pdTRUE, 0,  prvTimerCallback);

	/* Check the timers were created. */
	if( xAutoReloadTimer != NULL )
	{
		/* Start the software timers */
		xTimerStarted = xTimerStart( xAutoReloadTimer, 0 );

		if(  xTimerStarted == pdPASS )
		{
			printf("Start Software timer\r\n");
		}
	}
}

static void prvTimerCallback( TimerHandle_t xTimer )
{
	if(count_i)
	{
		xTimerChangePeriod(xAutoReloadTimer, ERROR_PERIOD, 0);
	}
	else
	{
		xTimerChangePeriod(xAutoReloadTimer, HEALTHY_PERIOD, 0);
	}

	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}

