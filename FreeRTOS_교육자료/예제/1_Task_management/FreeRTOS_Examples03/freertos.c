/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#define mainDELAY_LOOP_COUNT		( 0xffffff )

/* Private function prototypes -----------------------------------------------*/
void vTaskFunction( void *pvParameters );

/* task parameters */
const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\r\n";

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* Create the thread(s) */
	xTaskCreate(vTaskFunction, "Task 1", 128, (void*)pcTextForTask1, 3, NULL );
	xTaskCreate(vTaskFunction, "Task 2", 128, (void*)pcTextForTask2, 4, NULL );
}

void vTaskFunction( void *pvParameters )
{
	char *pcTaskName;
	volatile uint32_t ul;

	pcTaskName = ( char * ) pvParameters;

	/* infinite loop. */
	for( ;; )
	{
		printf( pcTaskName );

		/* Delay for a period. */
		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
		}
	}
}
