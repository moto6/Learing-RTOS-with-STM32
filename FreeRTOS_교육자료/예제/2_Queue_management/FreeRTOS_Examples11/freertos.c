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

typedef enum
{
	eSender1,
	eSender2
} DataSource_t;

/* Define the structure type that will be passed on the queue. */
typedef struct
{
	uint8_t ucValue;
	DataSource_t eDataSource;
} Data_t;

/* Declare two variables of type Data_t that will be passed on the queue. */
static const Data_t xStructsToSend[ 2 ] =
{
	{ 100, eSender1 }, /* Used by Sender1. */
	{ 200, eSender2 }  /* Used by Sender2. */
};

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* Create Queue */
	 xQueue = xQueueCreate( 3, sizeof( Data_t ) );

	 if(xQueue != NULL)
	 {
		 /* Create the thread(s) */
		 xTaskCreate( vSenderTask, "Sender1", 128, ( void * ) &xStructsToSend[0], 2, NULL );
		 xTaskCreate( vSenderTask, "Sender2", 128, ( void * ) &xStructsToSend[1], 2, NULL );

		 xTaskCreate( vReceiverTask, "Receiver", 128, NULL, 1, NULL );
	 }
	 else
	 {
		 printf("Create Queue failed\r\n");
	 }
}

static void vSenderTask( void *pvParameters )
{
	BaseType_t xStatus;
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 100UL );

	for(;;)
	{
		/*
		 *  The second parameter is the address of the data to be sent.
		 *  The third parameter is the Block time.
		 */
		xStatus = xQueueSendToBack( xQueue, pvParameters, xTicksToWait );

		if(xStatus != pdPASS )
		{
			printf("Could not send to the queue.\r\n");
		}
	}
}

static void vReceiverTask( void *pvParameters )
{
	BaseType_t xStatus;
	Data_t xReceivedStructure;

	for(;;)
	{
		if( uxQueueMessagesWaiting( xQueue ) != 3 )
		{
			printf( "Queue should have been full!\r\n" );
		}

		xStatus = xQueueReceive( xQueue, &xReceivedStructure, 0 );

		if( xStatus == pdPASS )
		{
			/* Data was successfully received  */
			if( xReceivedStructure.eDataSource == eSender1 )
			{
				printf( "From Sender 1 = %d\r\n", xReceivedStructure.ucValue );
			}
			else
			{
				printf( "From Sender 2 = %d\r\n", xReceivedStructure.ucValue );
			}
		}
		else
		{
			printf( "Could not receive from the queue.\r\n" );
		}
	}
}
