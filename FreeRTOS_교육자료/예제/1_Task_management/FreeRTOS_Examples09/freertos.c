/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
/* The two task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* handle of Task. */
TaskHandle_t xTask2Handle;

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* Create the thread(s) */
	xTaskCreate(vTask1, "Task 1", 128, NULL, 3, NULL );
}

void vTask1( void *pvParameters )
{
	const TickType_t xDelay100ms = pdMS_TO_TICKS( 100UL );

	/* infinite loop. */
	for( ;; )
	{
		printf("Task1 is running\r\n");

		/* create task2 at a higher priority */
		xTaskCreate( vTask2, "Task 2", 128, NULL, 4, &xTask2Handle );

		vTaskDelay( xDelay100ms );
	}
}

void vTask2( void *pvParameters )
{
	printf( "Task2 is running and delete\r\n" );
	vTaskDelete( xTask2Handle );
}
