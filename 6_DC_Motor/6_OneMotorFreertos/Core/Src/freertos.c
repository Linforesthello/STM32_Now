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

#include "motor.h"

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

extern Motor_t motor1;

/* USER CODE END Variables */
/* Definitions for LedTask */
osThreadId_t LedTaskHandle;
const osThreadAttr_t LedTask_attributes = {
  .name = "LedTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for MotorTask */
osThreadId_t MotorTaskHandle;
const osThreadAttr_t MotorTask_attributes = {
  .name = "MotorTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UartTask */
osThreadId_t UartTaskHandle;
const osThreadAttr_t UartTask_attributes = {
  .name = "UartTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Start_LedTask(void *argument);
void Start_MotorTask(void *argument);
void Start_UartTask(void *argument);

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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of LedTask */
  LedTaskHandle = osThreadNew(Start_LedTask, NULL, &LedTask_attributes);

  /* creation of MotorTask */
  MotorTaskHandle = osThreadNew(Start_MotorTask, NULL, &MotorTask_attributes);

  /* creation of UartTask */
  UartTaskHandle = osThreadNew(Start_UartTask, NULL, &UartTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Start_LedTask */
/**
  * @brief  Function implementing the LedTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Start_LedTask */
void Start_LedTask(void *argument)
{
  /* USER CODE BEGIN Start_LedTask */
  /* Infinite loop */
  for(;;)
  {
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    // osDelay(200);
    osDelay(1);
  }
  /* USER CODE END Start_LedTask */
}

/* USER CODE BEGIN Header_Start_MotorTask */
/**
* @brief Function implementing the MotorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_MotorTask */
void Start_MotorTask(void *argument)
{
  /* USER CODE BEGIN Start_MotorTask */
  /* Infinite loop */
  for(;;)
  {
    //     HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    // HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
    Motor_SetSpeed(&motor1, 800);
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    osDelay(500);

    Motor_SetSpeed(&motor1, -500);
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    osDelay(500);

    Motor_Stop(&motor1);
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    osDelay(500);
    
    osDelay(1);
  }
  /* USER CODE END Start_MotorTask */
}

/* USER CODE BEGIN Header_Start_UartTask */
/**
* @brief Function implementing the UartTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_UartTask */
void Start_UartTask(void *argument)
{
  /* USER CODE BEGIN Start_UartTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Start_UartTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

