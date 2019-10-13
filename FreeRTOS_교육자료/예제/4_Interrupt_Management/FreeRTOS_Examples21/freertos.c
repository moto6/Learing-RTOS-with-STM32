/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
/* task function */
static void vStringPrinter( void *pvParameters );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* variables of type QueueHandle_t. */
QueueHandle_t xStringQueue;
char Buffer[12];

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* Create Queue */
	xStringQueue = xQueueCreate( 10, sizeof( char * ) );

	/*Create Task */
	xTaskCreate( vStringPrinter, "String", 128, NULL, 3, NULL );
}

static void vStringPrinter( void *pvParameters )
{
	char *pcString=NULL;

	for( ;; )
	{
		/* Block on the queue to wait for data to arrive. */
		xQueueReceive( xStringQueue, (void*)&pcString, portMAX_DELAY );
//		xQueueReceive( xStringQueue, (void*)pcString, portMAX_DELAY );		// Interrupt does not occur.

		/* Print out the received string. */
		printf(pcString );
	}
}

/* interrupt callback functions */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	BaseType_t xHigherPriorityTaskWoken;

	static int index = 0;
	memset(Buffer, 0, sizeof(Buffer));
	index++;
	sprintf(Buffer, "String %d\r\n", index);

	static const char *pcStrings[] = {Buffer};

	xHigherPriorityTaskWoken = pdFALSE;

	/* Send string to the queue */
	xQueueSendToBackFromISR( xStringQueue, (void*)&pcStrings[0], &xHigherPriorityTaskWoken );
//	xQueueSendToBackFromISR( xStringQueue, (void*)Buffer, &xHigherPriorityTaskWoken );	// ERROR

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
