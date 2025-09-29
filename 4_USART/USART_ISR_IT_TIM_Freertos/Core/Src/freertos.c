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

#include "queue.h"
#include "usart.h"
#include "string.h"

// extern QueueHandle_t LED_Queue;


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
/* Definitions for LED_UART_Task */
osThreadId_t LED_UART_TaskHandle;
const osThreadAttr_t LED_UART_Task_attributes = {
  .name = "LED_UART_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LED_Queue */
osMessageQueueId_t LED_QueueHandle;
const osMessageQueueAttr_t LED_Queue_attributes = {
  .name = "LED_Queue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Start_LED_UART_Task(void *argument);

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
  /* creation of LED_Queue */
  LED_QueueHandle = osMessageQueueNew (16, sizeof(uint8_t), &LED_Queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of LED_UART_Task */
  LED_UART_TaskHandle = osThreadNew(Start_LED_UART_Task, NULL, &LED_UART_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Start_LED_UART_Task */
/**
  * @brief  Function implementing the LED_UART_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Start_LED_UART_Task */
void Start_LED_UART_Task(void *argument)
{
  /* USER CODE BEGIN Start_LED_UART_Task */

  uint8_t event;
  uint8_t led_state = 0;
  const char *msg = "LED toggled!\r\n";

  /* Infinite loop */
  for(;;)
  {
    if (osMessageQueueGet(LED_QueueHandle, &event, NULL, osWaitForever) == osOK)
    {
      if (event == 1)
      {
        led_state = !led_state;
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 
                          led_state ? GPIO_PIN_RESET : GPIO_PIN_SET);

        // Send a message over UART
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
      }
    }
    osDelay(1);
  }
  /* USER CODE END Start_LED_UART_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

