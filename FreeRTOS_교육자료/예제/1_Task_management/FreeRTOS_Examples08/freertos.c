/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private function prototypes -----------------------------------------------*/
/* The two task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* handle of Task. */
TaskHandle_t xTask2Handle;

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
	/* Create the thread(s) */
	xTaskCreate(vTask1, "Task 1", 128, NULL, 4, NULL );
	xTaskCreate(vTask2, "Task 2", 128, NULL, 3, &xTask2Handle );
}

void vTask1( void *pvParameters )
{
	UBaseType_t uxPriority;

	uxPriority = uxTaskPriorityGet( NULL );

	/* infinite loop. */
	for( ;; )
	{
		printf("Task1 is running\r\n");

		/* Setting the Task2 priority */
		printf("About to raise the Task2 priority\r\n");
		vTaskPrioritySet( xTask2Handle, ( uxPriority + 1 ) );
	}
}

void vTask2( void *pvParameters )
{
	UBaseType_t uxPriority;

	uxPriority = uxTaskPriorityGet( NULL );

	/* infinite loop. */
	for( ;; )
	{
		printf("Task2 is running\r\n");

		/* Setting the Task2 priority */
		printf("About to lower the Task2 priority\r\n");
		vTaskPrioritySet( NULL, ( uxPriority - 2 ) );
	}
}
