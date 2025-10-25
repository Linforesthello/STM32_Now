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
/* Definitions for HeartTask */
osThreadId_t HeartTaskHandle;
const osThreadAttr_t HeartTask_attributes = {
  .name = "HeartTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Pc14Task */
osThreadId_t Pc14TaskHandle;
const osThreadAttr_t Pc14Task_attributes = {
  .name = "Pc14Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Start_Heart(void *argument);
void Start_Pc14(void *argument);

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
  /* creation of HeartTask */
  HeartTaskHandle = osThreadNew(Start_Heart, NULL, &HeartTask_attributes);

  /* creation of Pc14Task */
  Pc14TaskHandle = osThreadNew(Start_Pc14, NULL, &Pc14Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Start_Heart */
/**
  * @brief  Function implementing the HeartTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Start_Heart */
void Start_Heart(void *argument)
{
  /* USER CODE BEGIN Start_Heart */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	  osDelay(50);
//    osDelay(1);
  }
  /* USER CODE END Start_Heart */
}

/* USER CODE BEGIN Header_Start_Pc14 */
/**
* @brief Function implementing the Pc14Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Pc14 */
void Start_Pc14(void *argument)
{
  /* USER CODE BEGIN Start_Pc14 */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_14);
	  osDelay(25);
//    osDelay(1);
  }
  /* USER CODE END Start_Pc14 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

