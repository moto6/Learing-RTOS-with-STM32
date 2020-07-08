/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId Task1Handle;
osThreadId Task2Handle;
osThreadId Task3Handle;
osSemaphoreId myCountingSem01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTask1(void const *argument);
void StartTask2(void const *argument);
void StartTask3(void const *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = &xIdleStack[0];
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
	/* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* Create the semaphores(s) */
	/* definition and creation of myCountingSem01 */
	osSemaphoreDef(myCountingSem01);
	myCountingSem01Handle = osSemaphoreCreate(osSemaphore(myCountingSem01), 2);

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of Task1 */
	osThreadDef(Task1, StartTask1, osPriorityNormal, 0, 128);
	Task1Handle = osThreadCreate(osThread(Task1), NULL);

	/* definition and creation of Task2 */
	osThreadDef(Task2, StartTask2, osPriorityNormal, 0, 128);
	Task2Handle = osThreadCreate(osThread(Task2), NULL);

	/* definition and creation of Task3 */
	osThreadDef(Task3, StartTask3, osPriorityNormal, 0, 128);
	Task3Handle = osThreadCreate(osThread(Task3), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartTask1 */
/**
 * @brief  Function implementing the Task1 thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask1 */
void StartTask1(void const *argument)
{
	/* USER CODE BEGIN StartTask1 */
	/* Infinite loop */
	for (;;)
	{
		osDelay(2000);
		printf("Task1 release counting semaphore.\n");
		osSemaphoreRelease(myCountingSem01Handle);
	}
	/* USER CODE END StartTask1 */
}

/* USER CODE BEGIN Header_StartTask2 */
/**
 * @brief Function implementing the Task2 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask2 */
void StartTask2(void const *argument)
{
	/* USER CODE BEGIN StartTask2 */
	/* Infinite loop */
	for (;;)
	{
		osDelay(2000);
		printf("Task2 release counting semaphore.\n");
		osSemaphoreRelease(myCountingSem01Handle);
	}
	/* USER CODE END StartTask2 */
}

/* USER CODE BEGIN Header_StartTask3 */
/**
 * @brief Function implementing the Task3 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask3 */
void StartTask3(void const *argument)
{
	/* USER CODE BEGIN StartTask3 */
	int32_t retVal;
	/* Infinite loop */
	for (;;)
	{
		osSemaphoreWait(myCountingSem01Handle, 4000);
		retVal = osSemaphoreWait(myCountingSem01Handle, 4000);

		if(retVal == 0)
		{
			printf("Task3 synchronized...\n");
		}
		else
		{
			printf("Task3 timeout or error.\n");
		}
	}
	/* USER CODE END StartTask3 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
