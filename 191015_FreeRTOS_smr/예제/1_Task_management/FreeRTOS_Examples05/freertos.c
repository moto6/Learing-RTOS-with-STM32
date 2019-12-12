/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
void vTaskFunction( void *pvParameters );

/* task parameters */
const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\r\n";

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* Create the thread(s) */
	xTaskCreate(vTaskFunction, "Task 1", 128, (void*)pcTextForTask1, 3, NULL );
	xTaskCreate(vTaskFunction, "Task 2", 128, (void*)pcTextForTask2, 4, NULL );
}

void vTaskFunction( void *pvParameters )
{
	char *pcTaskName;
	const TickType_t xDelay250ms = pdMS_TO_TICKS( 250UL );
	TickType_t xLastWakeTime;

	pcTaskName = ( char * ) pvParameters;

	/* current tick count */
	xLastWakeTime = xTaskGetTickCount();

	/* infinite loop. */
	for( ;; )
	{
		printf( pcTaskName );

		/* Delay for a period. */
		vTaskDelayUntil( &xLastWakeTime, xDelay250ms );
	}
}
