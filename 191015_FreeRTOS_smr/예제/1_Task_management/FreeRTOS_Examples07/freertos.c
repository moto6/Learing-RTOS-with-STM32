/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
void vTaskFunction( void *pvParameters );

static uint32_t ulIdleCycleCount = 0UL;

/* task parameters */
const char *pcTextForTask1 = "Task 1 is running";
const char *pcTextForTask2 = "Task 2 is running";

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
}


void vTaskFunction( void *pvParameters )
{
	char *pcTaskName;
	const TickType_t xDelay200ms = pdMS_TO_TICKS( 200UL );

	pcTaskName = ( char * ) pvParameters;

	/* infinite loop. */
	for( ;; )
	{
		printf("%s\t%d\r\n", pcTaskName, ulIdleCycleCount);

		/* Delay for a period. */
		vTaskDelay( xDelay200ms );
	}
}

void vApplicationIdleHook( void )
{
	/* increment a counter. */
	ulIdleCycleCount++;
}
