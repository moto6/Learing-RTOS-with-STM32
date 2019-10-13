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
SemaphoreHandle_t xCountingSemaphore;

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* create binary semaphore */
	xCountingSemaphore = xSemaphoreCreateCounting( 10, 0 );

	/* Check the semaphore was created successfully. */
	if( xCountingSemaphore != NULL )
	{
		xTaskCreate( vHandlerTask, "Handler", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
	}
}

static void vHandlerTask( void *pvParameters )
{
	uint32_t count=0;

	for( ;; )
	{
		xSemaphoreTake( xCountingSemaphore, portMAX_DELAY );

		count++;
		printf( "Handler task - Processing event count: %d\r\n", count );
	}
}

/* interrupt callback functions */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	BaseType_t xHigherPriorityTaskWoken;

	xHigherPriorityTaskWoken = pdFALSE;

	/* 'Give' the semaphore to unblock the task. */
	xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
	xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
	xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
