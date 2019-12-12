/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
void vTaskFunction( void *pvParameters );
void vPeriodicTask( void *pvParameters );

/* task parameters */
const char *pcTextForTask1 = "Continuous Task 1 is running\r\n";
const char *pcTextForTask2 = "Continuous Task 2 is running\r\n";
const char *pcTextForPeriodicTask = "Periodic task is running\r\n";

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
	xTaskCreate(vTaskFunction, "Task 2", 128, (void*)pcTextForTask2, 3, NULL );

	xTaskCreate( vPeriodicTask, "Task 3", 128, (void*)pcTextForPeriodicTask, 4, NULL );
}


void vTaskFunction( void *pvParameters )
{
	char *pcTaskName;

	pcTaskName = ( char * ) pvParameters;

	/* infinite loop. */
	for( ;; )
	{
		printf( pcTaskName );
		//vTaskDelay( pdMS_TO_TICKS( 5UL ) );
	}
}

void vPeriodicTask( void *pvParameters )
{
	char *pcTaskName;
	const TickType_t xDelay15ms = pdMS_TO_TICKS( 15UL );
	TickType_t xLastWakeTime;

	pcTaskName = ( char * ) pvParameters;

	/* current tick count */
	xLastWakeTime = xTaskGetTickCount();

	/* infinite loop. */
	for( ;; )
	{
		printf( pcTaskName );

		/* Delay for a period. */
		vTaskDelayUntil( &xLastWakeTime, xDelay15ms );
	}
}
