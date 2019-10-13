/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
/* task function */
static void prvPrintTask( void *pvParameters );

/* The gatekeeper task itself. */
static void prvStdioGatekeeperTask( void *pvParameters );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

static const char *pcStringsToPrint[] =
{
	"Task 1 ****************************************************\r\n",
	"Task 2 ----------------------------------------------------\r\n",
	"Message printed from the tick hook interrupt ##############\r\n"
};

/* Mutex Handle */
static QueueHandle_t xPrintQueue;

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* create queue */
	xPrintQueue = xQueueCreate( 5, sizeof( char * ) );

	if( xPrintQueue != NULL )
	{
		xTaskCreate( prvPrintTask, "Print1", 128, ( void * ) 0, 1, NULL );
		xTaskCreate( prvPrintTask, "Print2", 128, ( void * ) 1, 2, NULL );

		xTaskCreate( prvStdioGatekeeperTask, "Gatekeeper", 128, NULL, 0, NULL );

	}
}

static void prvPrintTask( void *pvParameters )
{
	int iIndexToString;
	const TickType_t xMaxBlockTimeTicks = 0x20;

	iIndexToString = ( int ) pvParameters;

	for( ;; )
	{
		xQueueSendToBack( xPrintQueue, &( pcStringsToPrint[ iIndexToString ] ), 0 );

		vTaskDelay( rand() % xMaxBlockTimeTicks );
	}
}

static void prvStdioGatekeeperTask( void *pvParameters )
{
	char *pcMessageToPrint;

	for( ;; )
	{
		/* Wait for a message to arrive. */
		xQueueReceive( xPrintQueue, &pcMessageToPrint, portMAX_DELAY );

		printf( "%s", pcMessageToPrint );
	}
}

#if configUSE_TICK_HOOK
void vApplicationTickHook( void )
{
	static int iCount = 0;
	iCount++;

	if( iCount >= 200 )
	{
		xQueueSendToFrontFromISR( xPrintQueue, &( pcStringsToPrint[ 2 ] ), NULL );

		iCount = 0;
	}
}
#endif
