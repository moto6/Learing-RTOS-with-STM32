/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
/* The task functions. */
static void vUpdateMailBox( void *pvParameters );
static void vReadMailbox( void *pvParameters );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

typedef struct xExampleStructure
{
	TickType_t xTimeStamp;
	uint32_t ulValue;
} Example_t;

/* handle of queue. */
static QueueHandle_t xMailbox;

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* Create Queue */
	xMailbox = xQueueCreate( 1, sizeof( Example_t ) );

	/* Create the tasks that send to the queues. */
	xTaskCreate( vUpdateMailBox, "UpdateMailBox", 128, NULL, 1, NULL );
	xTaskCreate( vReadMailbox, "ReadMailbox", 128, NULL, 1, NULL );
}

static void vUpdateMailBox( void *pvParameters )
{
	Example_t xData;
	uint32_t value = 0;
	const TickType_t xBlockTime = pdMS_TO_TICKS( 100 );

	for(;;)
	{
		xData.ulValue = value++;
		xData.xTimeStamp = xTaskGetTickCount();

		xQueueOverwrite(xMailbox, &xData);

		vTaskDelay( xBlockTime );
	}
}

static void vReadMailbox( void *pvParameters )
{
	Example_t xData;
	TickType_t xPrevTimeStamp;
	const TickType_t xBlockTime = pdMS_TO_TICKS( 50 );

	memset(&xData, 0, sizeof(Example_t));

	for(;;)
	{
		xPrevTimeStamp = xData.xTimeStamp;
		xQueuePeek(xMailbox, &xData, portMAX_DELAY);

		if(xData.xTimeStamp > xPrevTimeStamp)
		{
			printf("value: %d\r\n", xData.ulValue);
		}
		else
		{
			printf("Not receive Mailbox\r\n");
		}

		vTaskDelay( xBlockTime );
	}
}
