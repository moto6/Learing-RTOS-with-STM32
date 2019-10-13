/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#define mainDELAY_LOOP_COUNT		( 0xffffff )

/* Private function prototypes -----------------------------------------------*/
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* Create the thread(s) */
	xTaskCreate(vTask1,		/* Pointer to the function that implements the task. */
				"Task 1",	/* text name */
				128,		/* stack depth */
				NULL,		/* task parameter. */
				3,			/* task priority */
				NULL );		/* task handle. */

	/* Create the other task in exactly the same way. */
	xTaskCreate( vTask2, "Task 2", 128, NULL, 3, NULL );
}

void vTask1( void *pvParameters )
{
	const char *pcTaskName = "Task 1 is running\r\n";
	volatile uint32_t ul;

	/* infinite loop. */
	for( ;; )
	{
		printf( pcTaskName );

		/* Delay*/
		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
		}
	}
}

void vTask2( void *pvParameters )
{
	const char *pcTaskName = "Task 2 is running\r\n";
	volatile uint32_t ul;

	/* infinite loop. */
	for( ;; )
	{
		printf( pcTaskName );

		/* Delay*/
		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
		}
	}
}
