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
osMessageQId myQueue01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void SenderTask1(void const * argument);
void SenderTask2(void const * argument);
void ReceiverTask1(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

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
void MX_FREERTOS_Init(void) {
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

  /* Create the queue(s) */
  /* definition and creation of myQueue01 */
  osMessageQDef(myQueue01, 128, uint8_t);
  myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Sender1 */
  osThreadDef(Sender1, SenderTask1, osPriorityNormal, 0, 128);
  Sender1Handle = osThreadCreate(osThread(Sender1), NULL);

  /* definition and creation of Sender2 */
  osThreadDef(Sender2, SenderTask2, osPriorityNormal, 0, 128);
  Sender2Handle = osThreadCreate(osThread(Sender2), NULL);

  /* definition and creation of Receiver1 */
  osThreadDef(Receiver1, ReceiverTask1, osPriorityAboveNormal, 0, 128);
  Receiver1Handle = osThreadCreate(osThread(Receiver1), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_SenderTask1 */
/**
 * @brief  Function implementing the Sender1 thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_SenderTask1 */
void SenderTask1(void const * argument)
{
  /* USER CODE BEGIN SenderTask1 */
	/* Infinite loop */
	for (;;)
	{
		printf("Sender1\n");
		osMessagePut(myQueue01Handle, 0x01, 100);
		printf("Sender1 delay\n");
		osDelay(2000);
	}
  /* USER CODE END SenderTask1 */
}

/* USER CODE BEGIN Header_SenderTask2 */
/**
 * @brief Function implementing the Sender2 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_SenderTask2 */
void SenderTask2(void const * argument)
{
  /* USER CODE BEGIN SenderTask2 */
	/* Infinite loop */
	for (;;)
	{
		printf("Sender2\n");
		osMessagePut(myQueue01Handle, 0x02, 100);
		printf("Sender2 delay\n");
		osDelay(2000);
	}
  /* USER CODE END SenderTask2 */
}

/* USER CODE BEGIN Header_ReceiverTask1 */
/**
 * @brief Function implementing the Receiver1 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_ReceiverTask1 */
void ReceiverTask1(void const * argument)
{
  /* USER CODE BEGIN ReceiverTask1 */
	osEvent retVal;
	/* Infinite loop */
	for (;;)
	{
		retVal = osMessageGet(myQueue01Handle, 1000);
		if(retVal.status == osEventMessage)
		{
			printf("Receiver %lu\n", retVal.value.v);
		}
		else if(retVal.status == osEventTimeout)
		{
			printf("Receiver timeout\n");
		}
	}
  /* USER CODE END ReceiverTask1 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
