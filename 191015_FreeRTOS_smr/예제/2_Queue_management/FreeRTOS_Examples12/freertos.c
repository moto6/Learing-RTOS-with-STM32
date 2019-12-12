/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
/* The task functions. */
static void vSenderTask1( void *pvParameters );
static void vSenderTask2( void *pvParameters );
static void vReceiverTask( void *pvParameters );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* handle of queue. */
static QueueHandle_t xQueue1 = NULL, xQueue2 = NULL;
/* handle of queue set */
static QueueSetHandle_t xQueueSet = NULL;


/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* Create Queue */
	xQueue1 = xQueueCreate( 1, sizeof( char * ) );
	xQueue2 = xQueueCreate( 1, sizeof( char * ) );

	/* create Queue-set */
	xQueueSet = xQueueCreateSet( 2 );

	/* Add the two queues to the set. */
	xQueueAddToSet( xQueue1, xQueueSet );
	xQueueAddToSet( xQueue2, xQueueSet );

	/* Create the tasks that send to the queues. */
	xTaskCreate( vSenderTask1, "Sender1", 128, NULL, 1, NULL );
	xTaskCreate( vSenderTask2, "Sender2", 128, NULL, 1, NULL );

	/* Create the receiver task. */
	xTaskCreate( vReceiverTask, "Receiver", 128, NULL, 2, NULL );
}

static void vSenderTask1( void *pvParameters )
{
	const TickType_t xBlockTime = pdMS_TO_TICKS( 100 );
	const char * const pcMessage = "Message from vSenderTask1\r\n";

	for( ;; )
	{
		/* Block for 100ms. */
		vTaskDelay( xBlockTime );

		/* Send this task's string to xQueue1. */
		xQueueSend( xQueue1, &pcMessage, 0 );
	}
}

static void vSenderTask2( void *pvParameters )
{
	const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );
	const char * const pcMessage = "Message from vSenderTask2\r\n";

	for( ;; )
	{
		/* Block for 200ms. */
		vTaskDelay( xBlockTime );

		/* Send this task's string to xQueue2. */
		xQueueSend( xQueue2, &pcMessage, 0 );
	}
}

static void vReceiverTask( void *pvParameters )
{
	QueueHandle_t xQueueThatContainsData;
	char *pcReceivedString;

	for( ;; )
	{
		/* Block on the queue set to wait for one of the queues in the set to contain data. */
		xQueueThatContainsData = ( QueueHandle_t ) xQueueSelectFromSet( xQueueSet, portMAX_DELAY );

		xQueueReceive( xQueueThatContainsData, &pcReceivedString, 0 );
		printf( pcReceivedString );
	}
}

