/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
/* Definitions for MotorTask */
osThreadId_t MotorTaskHandle;
const osThreadAttr_t MotorTask_attributes = {
  .name = "MotorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for EncoderTask */
osThreadId_t EncoderTaskHandle;
const osThreadAttr_t EncoderTask_attributes = {
  .name = "EncoderTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for UartTxTask */
osThreadId_t UartTxTaskHandle;
const osThreadAttr_t UartTxTask_attributes = {
  .name = "UartTxTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for InitTask */
osThreadId_t InitTaskHandle;
const osThreadAttr_t InitTask_attributes = {
  .name = "InitTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for MotorSpeedQueue */
osMessageQueueId_t MotorSpeedQueueHandle;
const osMessageQueueAttr_t MotorSpeedQueue_attributes = {
  .name = "MotorSpeedQueue"
};
/* Definitions for UartTxDateQueue */
osMessageQueueId_t UartTxDateQueueHandle;
const osMessageQueueAttr_t UartTxDateQueue_attributes = {
  .name = "UartTxDateQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Start_MotorTask(void *argument);
void Start_EncoderTask(void *argument);
void Start_UartTxTask(void *argument);
void Start_InitTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of MotorSpeedQueue */
  MotorSpeedQueueHandle = osMessageQueueNew (5, sizeof(uint16_t), &MotorSpeedQueue_attributes);

  /* creation of UartTxDateQueue */
  UartTxDateQueueHandle = osMessageQueueNew (3, 64, &UartTxDateQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of MotorTask */
  MotorTaskHandle = osThreadNew(Start_MotorTask, NULL, &MotorTask_attributes);

  /* creation of EncoderTask */
  EncoderTaskHandle = osThreadNew(Start_EncoderTask, NULL, &EncoderTask_attributes);

  /* creation of UartTxTask */
  UartTxTaskHandle = osThreadNew(Start_UartTxTask, NULL, &UartTxTask_attributes);

  /* creation of InitTask */
  InitTaskHandle = osThreadNew(Start_InitTask, NULL, &InitTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Start_MotorTask */
/**
  * @brief  Function implementing the MotorTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Start_MotorTask */
void Start_MotorTask(void *argument)
{
  /* USER CODE BEGIN Start_MotorTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Start_MotorTask */
}

/* USER CODE BEGIN Header_Start_EncoderTask */
/**
* @brief Function implementing the EncoderTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_EncoderTask */
void Start_EncoderTask(void *argument)
{
  /* USER CODE BEGIN Start_EncoderTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Start_EncoderTask */
}

/* USER CODE BEGIN Header_Start_UartTxTask */
/**
* @brief Function implementing the UartTxTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_UartTxTask */
void Start_UartTxTask(void *argument)
{
  /* USER CODE BEGIN Start_UartTxTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Start_UartTxTask */
}

/* USER CODE BEGIN Header_Start_InitTask */
/**
* @brief Function implementing the InitTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_InitTask */
void Start_InitTask(void *argument)
{
  /* USER CODE BEGIN Start_InitTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Start_InitTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

