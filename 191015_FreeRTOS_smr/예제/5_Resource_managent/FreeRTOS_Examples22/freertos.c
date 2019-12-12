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

/* The function that uses a mutex. */
static void prvNewPrintString( const char *pcString );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Mutex Handle */
SemaphoreHandle_t xMutex;

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* create mutex */
	xMutex = xSemaphoreCreateMutex();

	xTaskCreate( prvPrintTask, "Print1", 128, "Task 1 **\r\n", 1, NULL );
	xTaskCreate( prvPrintTask, "Print2", 128, "Task 2 --\r\n", 2, NULL );
}

static void prvPrintTask( void *pvParameters )
{
	char *pcStringToPrint;
	const TickType_t xSlowDownDelay = pdMS_TO_TICKS( 5UL );
	const TickType_t xMaxBlockTimeTicks = 0x20;

	pcStringToPrint = ( char * ) pvParameters;

	for( ;; )
	{
		prvNewPrintString( pcStringToPrint );

		vTaskDelay( rand() % xMaxBlockTimeTicks );

		/* Just to ensure the scrolling is not too fast! */
		vTaskDelay( xSlowDownDelay );
	}
}

static void prvNewPrintString( const char *pcString )
{
	xSemaphoreTake( xMutex, portMAX_DELAY );
	{
		printf( "%s", pcString );
	}
	xSemaphoreGive( xMutex );
}

