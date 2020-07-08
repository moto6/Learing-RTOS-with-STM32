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
EventGroupHandle_t evtGrpHandle;
uint32_t evtFlag1 = 0x01;
uint32_t evtFlag2 = 0x02;

/* USER CODE END Variables */
osThreadId EventReceiverHandle;
osThreadId EventSender1Handle;
osThreadId EventSender2Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartEventReceiverTask(void const *argument);
void StartEventSender1Task(void const *argument);
void StartEventSender2Task(void const *argument);

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
	evtGrpHandle = xEventGroupCreate();
	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

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
	/* definition and creation of EventReceiver */
	osThreadDef(EventReceiver, StartEventReceiverTask, osPriorityNormal, 0,
			128);
	EventReceiverHandle = osThreadCreate(osThread(EventReceiver), NULL);

	/* definition and creation of EventSender1 */
	osThreadDef(EventSender1, StartEventSender1Task, osPriorityNormal, 0, 128);
	EventSender1Handle = osThreadCreate(osThread(EventSender1), NULL);

	/* definition and creation of EventSender2 */
	osThreadDef(EventSender2, StartEventSender2Task, osPriorityNormal, 0, 128);
	EventSender2Handle = osThreadCreate(osThread(EventSender2), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartEventReceiverTask */
/**
 * @brief  Function implementing the EventReceiver thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartEventReceiverTask */
void StartEventReceiverTask(void const *argument)
{
	/* USER CODE BEGIN StartEventReceiverTask */
	uint32_t result;
	/* Infinite loop */
	for (;;)
	{
		result = xEventGroupWaitBits(
				evtGrpHandle, //handle
				(evtFlag1 | evtFlag2), //flags to wait
				pdTRUE, //clear flags
				pdTRUE, //wait all flags
				2000);

		if ((result & (evtFlag1 | evtFlag2)) == (evtFlag1 | evtFlag2))
		{
			printf("evtFlag1 | evtFlag2 set\n");
		}
		else
		{
			if (result & evtFlag1)
			{
				printf("evtFlag1 set\n");
			}
			else if (result & evtFlag2)
			{
				printf("evtFlag2 set\n");
			}
			else
			{
				printf("None is set\n");
			}
		}

		osDelay(1);
	}
	/* USER CODE END StartEventReceiverTask */
}

/* USER CODE BEGIN Header_StartEventSender1Task */
/**
 * @brief Function implementing the EventSender1 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartEventSender1Task */
void StartEventSender1Task(void const *argument)
{
	/* USER CODE BEGIN StartEventSender1Task */
	/* Infinite loop */
	for (;;)
	{
		printf("Sender1 set evtFlag1\n");
		xEventGroupSetBits(evtGrpHandle, evtFlag1);
		osDelay(1000);
	}
	/* USER CODE END StartEventSender1Task */
}

/* USER CODE BEGIN Header_StartEventSender2Task */
/**
 * @brief Function implementing the EventSender2 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartEventSender2Task */
void StartEventSender2Task(void const *argument)
{
	/* USER CODE BEGIN StartEventSender2Task */
	/* Infinite loop */
	for (;;)
	{
		printf("Sender2 set evtFlag2\n");
		xEventGroupSetBits(evtGrpHandle, evtFlag2);
		osDelay(3000);
	}
	/* USER CODE END StartEventSender2Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
