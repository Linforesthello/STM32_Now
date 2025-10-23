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

#include "usart.h"
#include "stdio.h"
#include "string.h"

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
// volatile uint8_t counter = 0;

/* USER CODE END Variables */
/* Definitions for UartTask */
osThreadId_t UartTaskHandle;
const osThreadAttr_t UartTask_attributes = {
  .name = "UartTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LedTask */
osThreadId_t LedTaskHandle;
const osThreadAttr_t LedTask_attributes = {
  .name = "LedTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for UartQueue */
osMessageQueueId_t UartQueueHandle;
const osMessageQueueAttr_t UartQueue_attributes = {
  .name = "UartQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Start_UartTask(void *argument);
void Start_LedTask(void *argument);

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
  /* creation of UartQueue */
  UartQueueHandle = osMessageQueueNew (16, sizeof(uint16_t), &UartQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of UartTask */
  UartTaskHandle = osThreadNew(Start_UartTask, NULL, &UartTask_attributes);

  /* creation of LedTask */
  LedTaskHandle = osThreadNew(Start_LedTask, NULL, &LedTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Start_UartTask */
/**
  * @brief  Function implementing the UartTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Start_UartTask */
void Start_UartTask(void *argument)
{
  /* USER CODE BEGIN Start_UartTask */

  char txBuf[64];
  uint8_t recvData;

  /* Infinite loop */
  for(;;)
  {
    if (osMessageQueueGet(UartQueueHandle, &recvData, NULL, osWaitForever) == osOK)
    {
      snprintf(txBuf, sizeof(txBuf), "Counter = %d\r\n", recvData);

      if (huart1.gState == HAL_UART_STATE_READY)
      {
        HAL_UART_Transmit_DMA(&huart1, (uint8_t *)txBuf, strlen(txBuf));
      }
    }
  }
  /* USER CODE END Start_UartTask */
}

/* USER CODE BEGIN Header_Start_LedTask */
/**
* @brief Function implementing the LedTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_LedTask */
void Start_LedTask(void *argument)
{
  /* USER CODE BEGIN Start_LedTask */

  uint8_t counter = 0;

  /* Infinite loop */
  for(;;)
  {
    //这里的LedTask，或许现在换成CountTask更合适hh
    
    osDelay(500);
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    osMessageQueuePut(UartQueueHandle, &counter, 0, 0);
    // osMessageQueuePut()
    counter++;
    //计数完成后翻转LED
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  }
  /* USER CODE END Start_LedTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

