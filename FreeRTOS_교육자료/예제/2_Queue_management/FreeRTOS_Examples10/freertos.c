/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
/* The two task functions. */
static void vSenderTask( void *pvParameters );
static void vReceiverTask( void *pvParameters );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* handle of Task. */
QueueHandle_t xQueue;

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* Create Queue */
	 xQueue = xQueueCreate( 5, sizeof( int32_t ) );

	 if(xQueue != NULL)
	 {
		 /* Create the thread(s) */
		 xTaskCreate( vSenderTask, "Sender1", 128, ( void * ) 100, 1, NULL );
		 xTaskCreate( vSenderTask, "Sender2", 128, ( void * ) 200, 1, NULL );

		 xTaskCreate( vReceiverTask, "Receiver", 128, NULL, 2, NULL );
	 }
	 else
	 {
		 printf("Create Queue failed\r\n");
	 }
}

static void vSenderTask( void *pvParameters )
{
	int32_t lValueToSend;
	BaseType_t xStatus;

	lValueToSend = ( int32_t ) pvParameters;

	for(;;)
	{
		/*
		 *  The second parameter is the address of the data to be sent.
		 *  The third parameter is the Block time.
		 */
		xStatus = xQueueSendToBack( xQueue, &lValueToSend, 0 );

		if(xStatus != pdPASS )
		{
			printf("Could not send to the queue.\r\n");
		}
	}
}

static void vReceiverTask( void *pvParameters )
{
	int32_t lReceivedValue;
	BaseType_t xStatus;
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 100UL );

	for(;;)
	{
		if( uxQueueMessagesWaiting( xQueue ) != 0 )
		{
			printf( "Queue should have been empty!\r\n" );
		}

		xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );

		if( xStatus == pdPASS )
		{
			/* Data was successfully received  */
			printf( "Received = %d\r\n", lReceivedValue );
		}
		else
		{
			printf( "Could not receive from the queue.\r\n" );
		}
	}
}
