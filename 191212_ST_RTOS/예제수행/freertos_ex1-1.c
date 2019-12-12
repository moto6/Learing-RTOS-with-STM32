/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/*
2-5-3-4 : 결론 ?��??�? ?���? ?��??�? ?��개씩 ?��?�� 차�?차�? ?��?��?��


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
osThreadId_t defaultTaskHandle;
osThreadId_t Task1Handle;
osThreadId_t Task2Handle;
osThreadId_t Task3Handle;
osThreadId_t Task4Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Start_Task1(void *argument);
void Start_Task2(void *argument);
void Start_Task3(void *argument);
void Start_Task4(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */
osKernelInitialize();

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
  /* definition and creation of defaultTask */
  const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* definition and creation of Task1 */
  const osThreadAttr_t Task1_attributes = {
    .name = "Task1",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  Task1Handle = osThreadNew(Start_Task1, NULL, &Task1_attributes);

  /* definition and creation of Task2 */
  const osThreadAttr_t Task2_attributes = {
    .name = "Task2",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  Task2Handle = osThreadNew(Start_Task2, NULL, &Task2_attributes);

  /* definition and creation of Task3 */
  const osThreadAttr_t Task3_attributes = {
    .name = "Task3",
    .priority = (osPriority_t) osPriorityAboveNormal,
    .stack_size = 128
  };
  Task3Handle = osThreadNew(Start_Task3, NULL, &Task3_attributes);

  /* definition and creation of Task4 */
  const osThreadAttr_t Task4_attributes = {
    .name = "Task4",
    .priority = (osPriority_t) osPriorityAboveNormal,
    .stack_size = 128
  };
  Task4Handle = osThreadNew(Start_Task4, NULL, &Task4_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
    
    
    
    
    
    

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Start_Task1 */
/**
* @brief Function implementing the Task1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Task1 */
void Start_Task1(void *argument)
{
  /* USER CODE BEGIN Start_Task1 */
  /* Infinite loop */
  for(;;)
  {
    printf("Task1 \n");
    osDelay(1000);
  }
  /* USER CODE END Start_Task1 */
}

/* USER CODE BEGIN Header_Start_Task2 */
/**
* @brief Function implementing the Task2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Task2 */
void Start_Task2(void *argument)
{
  /* USER CODE BEGIN Start_Task2 */
  /* Infinite loop */
  for(;;)
  {
      printf("Task2 \n");
      osDelay(1000);
  }
  /* USER CODE END Start_Task2 */
}

/* USER CODE BEGIN Header_Start_Task3 */
/**
* @brief Function implementing the Task3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Task3 */
void Start_Task3(void *argument)
{
  /* USER CODE BEGIN Start_Task3 */
  /* Infinite loop */
  for(;;)
  {
      printf("Task3 \n");
      osDelay(1000);
  }
  /* USER CODE END Start_Task3 */
}

/* USER CODE BEGIN Header_Start_Task4 */
/**
* @brief Function implementing the Task4 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Task4 */
void Start_Task4(void *argument)
{
  /* USER CODE BEGIN Start_Task4 */
  /* Infinite loop */
  for(;;)
  {
      printf("Task4 \n");
      osDelay(1000);
  }
  /* USER CODE END Start_Task4 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
