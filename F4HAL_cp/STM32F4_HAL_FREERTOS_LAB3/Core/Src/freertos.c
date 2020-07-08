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
typedef struct
{
	uint8_t buf[8];
	uint8_t idx;
} _Message;
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
osThreadId SenderHandle;
osThreadId ReceiverHandle;
osMessageQId Queue1Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void SenderTask(void const * argument);
void ReceiverTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
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
  /* definition and creation of Queue1 */
  osMessageQDef(Queue1, 32, _Message);
  Queue1Handle = osMessageCreate(osMessageQ(Queue1), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Sender */
  osThreadDef(Sender, SenderTask, osPriorityNormal, 0, 128);
  SenderHandle = osThreadCreate(osThread(Sender), NULL);

  /* definition and creation of Receiver */
  osThreadDef(Receiver, ReceiverTask, osPriorityNormal, 0, 128);
  ReceiverHandle = osThreadCreate(osThread(Receiver), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_SenderTask */
/**
 * @brief  Function implementing the Sender thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_SenderTask */
void SenderTask(void const * argument)
{
  /* USER CODE BEGIN SenderTask */
	_Message msg;
	msg.buf[0] = 0xAA;
	msg.buf[1] = 0xBB;
	msg.idx = 0;

	/* Infinite loop */
	for (;;)
	{
		printf("Sender enqueues\n");
		osMessagePut(Queue1Handle, &msg, 100); //enqueue
		msg.idx++;
		printf("Sender delays for a sec.\n");
		osDelay(1000);
	}
  /* USER CODE END SenderTask */
}

/* USER CODE BEGIN Header_ReceiverTask */
/**
 * @brief Function implementing the Receiver thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_ReceiverTask */
void ReceiverTask(void const * argument)
{
  /* USER CODE BEGIN ReceiverTask */
	_Message *pMsg;
	osEvent retVal;

	/* Infinite loop */
	for (;;)
	{
		printf("Receiver is trying to dequeue\n");
		retVal = osMessageGet(Queue1Handle, 500); //dequeue
		if(retVal.status == osEventMessage)
		{
			pMsg = retVal.value.p;
			printf("Receiver received: msg.buf[0]=0x%X, msg.idx=%u\n", pMsg->buf[0]  , pMsg->idx);
		}
	}
  /* USER CODE END ReceiverTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
