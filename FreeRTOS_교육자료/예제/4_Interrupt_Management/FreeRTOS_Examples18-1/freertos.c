/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
/* The task functions. */
static void vHandlerTask( void *pvParameters );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Declare a variable of type SemaphoreHandle_t. */
SemaphoreHandle_t xBinarySemaphore;

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* create binary semaphore */
	xBinarySemaphore = xSemaphoreCreateBinary();

	/* Check the semaphore was created successfully. */
	if( xBinarySemaphore != NULL )
	{
		xTaskCreate( vHandlerTask, "Handler", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
	}
}

static void vHandlerTask( void *pvParameters )
{
	const TickType_t xDelay = pdMS_TO_TICKS( 2000 );

	for( ;; )
	{
		xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );

		printf( "Handler task - Processing event.\r\n" );
		vTaskDelay(xDelay);
		printf( "Handler task - Delay Expire.\r\n" );
	}
}

/* interrupt callback functions */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	BaseType_t xHigherPriorityTaskWoken;

	xHigherPriorityTaskWoken = pdFALSE;

	/* 'Give' the semaphore to unblock the task. */
	xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
