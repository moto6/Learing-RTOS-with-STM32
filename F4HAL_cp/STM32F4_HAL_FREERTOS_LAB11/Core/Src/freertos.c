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
osThreadId Sender1Handle;
osThreadId Sender2Handle;
osThreadId Receiver1Handle;
osThreadId Receiver2Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartSender1Task(void const *argument);
void StartSender2Task(void const *argument);
void StartReceiver1Task(void const *argument);
void StartReceiver2Task(void const *argument);

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
	/* definition and creation of Sender1 */
	osThreadDef(Sender1, StartSender1Task, osPriorityNormal, 0, 128);
	Sender1Handle = osThreadCreate(osThread(Sender1), NULL);

	/* definition and creation of Sender2 */
	osThreadDef(Sender2, StartSender2Task, osPriorityNormal, 0, 128);
	Sender2Handle = osThreadCreate(osThread(Sender2), NULL);

	/* definition and creation of Receiver1 */
	osThreadDef(Receiver1, StartReceiver1Task, osPriorityNormal, 0, 128);
	Receiver1Handle = osThreadCreate(osThread(Receiver1), NULL);

	/* definition and creation of Receiver2 */
	osThreadDef(Receiver2, StartReceiver2Task, osPriorityNormal, 0, 128);
	Receiver2Handle = osThreadCreate(osThread(Receiver2), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartSender1Task */
/**
 * @brief  Function implementing the Sender1 thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSender1Task */
void StartSender1Task(void const *argument)
{
	/* USER CODE BEGIN StartSender1Task */
	/* Infinite loop */
	for (;;)
	{
		osSignalSet(Receiver1Handle, 0x11);
		osDelay(1000);
		osSignalSet(Receiver2Handle, 0x12);
		osDelay(1000);
	}
	/* USER CODE END StartSender1Task */
}

/* USER CODE BEGIN Header_StartSender2Task */
/**
 * @brief Function implementing the Sender2 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSender2Task */
void StartSender2Task(void const *argument)
{
	/* USER CODE BEGIN StartSender2Task */
	/* Infinite loop */
	for (;;)
	{
		osSignalSet(Receiver1Handle, 0x21);
		osDelay(1000);
		osSignalSet(Receiver2Handle, 0x22);
		osDelay(1000);
	}
	/* USER CODE END StartSender2Task */
}

/* USER CODE BEGIN Header_StartReceiver1Task */
/**
 * @brief Function implementing the Receiver1 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartReceiver1Task */
void StartReceiver1Task(void const *argument)
{
	/* USER CODE BEGIN StartReceiver1Task */
	osEvent evt;
	/* Infinite loop */

	for (;;)
	{
		evt = osSignalWait(0x11 | 0x21, 100);
		if (evt.status == osEventSignal)
		{
			if ((evt.value.signals & 0x11) == 0x11)
			{
				printf("Receiver1: Notify from Sender1\n");
			}

			if ((evt.value.signals & 0x21) == 0x21)
			{
				printf("Receiver1: Notify from Sender2\n");
			}
		}
	}

	/* USER CODE END StartReceiver1Task */
}

/* USER CODE BEGIN Header_StartReceiver2Task */
/**
 * @brief Function implementing the Receiver2 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartReceiver2Task */
void StartReceiver2Task(void const *argument)
{
	/* USER CODE BEGIN StartReceiver2Task */
	osEvent evt;
	/* Infinite loop */

	for (;;)
	{
		evt = osSignalWait(0x12 | 0x22, 100);
		if (evt.status == osEventSignal)
		{
			if ((evt.value.signals & 0x12) == 0x12)
			{
				printf("Receiver2: Notify from Sender1\n");
			}

			if ((evt.value.signals & 0x22) == 0x22)
			{
				printf("Receiver2: Notify from Sender2\n");
			}
		}
	}
	/* USER CODE END StartReceiver2Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
