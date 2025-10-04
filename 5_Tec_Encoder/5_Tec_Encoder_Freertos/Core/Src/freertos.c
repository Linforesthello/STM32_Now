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

#include "stdio.h"
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

extern volatile int16_t current_speed; 
extern TIM_HandleTypeDef htim2; 
extern UART_HandleTypeDef huart1; 
// extern TIM_HandleTypeDef htim1;
extern Motor_t motor1; // 声明全局电机实例

// LogTask 的任务句柄由 CubeMX 自动生成并在此处声明
// osThreadId_t LogTaskHandle; 
uint8_t tx_buf[50]; 

/* USER CODE END Variables */
/* Definitions for LedTask */
osThreadId_t LedTaskHandle;
const osThreadAttr_t LedTask_attributes = {
  .name = "LedTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LogTask */
osThreadId_t LogTaskHandle;
const osThreadAttr_t LogTask_attributes = {
  .name = "LogTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for MotorTask */
osThreadId_t MotorTaskHandle;
const osThreadAttr_t MotorTask_attributes = {
  .name = "MotorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Start_LedTask(void *argument);
void Start_LogTask(void *argument);
void Start_MotorTask(void *argument);

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

  /* creation of LogTask */
  LogTaskHandle = osThreadNew(Start_LogTask, NULL, &LogTask_attributes);

  /* creation of MotorTask */
  MotorTaskHandle = osThreadNew(Start_MotorTask, NULL, &MotorTask_attributes);

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
    // 周期性操作：切换 PC13 引脚状态 (假设 PC13 是 LED)
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

    // 任务休眠 500ms
    osDelay(500); // CMSIS V2 的延时函数
    // osDelay(1);
  }
  /* USER CODE END Start_LedTask */
}

/* USER CODE BEGIN Header_Start_LogTask */
/**
* @brief Function implementing the LogTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_LogTask */
void Start_LogTask(void *argument)
{
  /* USER CODE BEGIN Start_LogTask */
  /* Infinite loop */
  for(;;)
  {
    // 阻塞等待来自 TIM3 中断的标志位 (0x01)
    // osThreadFlagsWait(flags, options, timeout)
    osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);

    // 收到标志位 (每 10ms 唤醒一次) 后执行耗时 I/O：

    // 1. 安全地读取速度
    int16_t speed_val = current_speed;
    uint32_t cnt_val = __HAL_TIM_GET_COUNTER(&htim2); 

    // 2. 格式化数据
    int len = sprintf((char *)tx_buf, "cnt=%ld,speed=%d\r\n", cnt_val, speed_val);

    // 3. 串口发送 (耗时操作，安全)
    HAL_UART_Transmit(&huart1, tx_buf, len, HAL_MAX_DELAY);

    // osDelay(1);
  }
  /* USER CODE END Start_LogTask */
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
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
    Motor_SetSpeed(&motor1, 1000); // 正转
    osDelay(2000);


    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
    Motor_SetSpeed(&motor1, 0); // 停止
    osDelay(1000);

    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
    Motor_SetSpeed(&motor1, -50); // 反转
    osDelay(2000);

        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
    Motor_SetSpeed(&motor1, -100); // 反转
    osDelay(2000);

        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
    Motor_SetSpeed(&motor1, -200); // 反转
    osDelay(2000);

        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
    Motor_SetSpeed(&motor1, -300); // 反转
    osDelay(2000);

        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
    Motor_SetSpeed(&motor1, -400); // 反转
    osDelay(2000);

        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
    Motor_SetSpeed(&motor1, -500); // 反转
    osDelay(2000);
    osDelay(1000);
  }
  /* USER CODE END Start_MotorTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

