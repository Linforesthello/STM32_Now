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
typedef StaticTask_t osStaticThreadDef_t;
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

extern TIM_HandleTypeDef htim2; 
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

extern Motor_t motor1;
extern volatile int16_t current_speed;

uint8_t tx_buf[50];

// extern UART2_TX_BUF_LEN
extern uint8_t uart2_rx_data;                      // 单字节接收缓冲
extern uint8_t uart2_tx_buf[64];     // 发送缓冲
extern volatile uint8_t uart2_tx_busy;         // 发送忙标志
extern volatile uint8_t motor_enable_flag;     // 电机控制标志

/* USER CODE END Variables */
/* Definitions for MotorControlTas */
osThreadId_t MotorControlTasHandle;
uint32_t MotorControlTasBuffer[ 256 ];
osStaticThreadDef_t MotorControlTasControlBlock;
const osThreadAttr_t MotorControlTas_attributes = {
  .name = "MotorControlTas",
  .cb_mem = &MotorControlTasControlBlock,
  .cb_size = sizeof(MotorControlTasControlBlock),
  .stack_mem = &MotorControlTasBuffer[0],
  .stack_size = sizeof(MotorControlTasBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for HeartbeatTask */
osThreadId_t HeartbeatTaskHandle;
uint32_t HeartbeatTaskBuffer[ 128 ];
osStaticThreadDef_t HeartbeatTaskControlBlock;
const osThreadAttr_t HeartbeatTask_attributes = {
  .name = "HeartbeatTask",
  .cb_mem = &HeartbeatTaskControlBlock,
  .cb_size = sizeof(HeartbeatTaskControlBlock),
  .stack_mem = &HeartbeatTaskBuffer[0],
  .stack_size = sizeof(HeartbeatTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for SpeedMeasureTas */
osThreadId_t SpeedMeasureTasHandle;
uint32_t SpeedMeasureTasBuffer[ 128 ];
osStaticThreadDef_t SpeedMeasureTasControlBlock;
const osThreadAttr_t SpeedMeasureTas_attributes = {
  .name = "SpeedMeasureTas",
  .cb_mem = &SpeedMeasureTasControlBlock,
  .cb_size = sizeof(SpeedMeasureTasControlBlock),
  .stack_mem = &SpeedMeasureTasBuffer[0],
  .stack_size = sizeof(SpeedMeasureTasBuffer),
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for SerialLogTask */
osThreadId_t SerialLogTaskHandle;
uint32_t SerialLogTaskBuffer[ 384 ];
osStaticThreadDef_t SerialLogTaskControlBlock;
const osThreadAttr_t SerialLogTask_attributes = {
  .name = "SerialLogTask",
  .cb_mem = &SerialLogTaskControlBlock,
  .cb_size = sizeof(SerialLogTaskControlBlock),
  .stack_mem = &SerialLogTaskBuffer[0],
  .stack_size = sizeof(SerialLogTaskBuffer),
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for CommandQueue */
osMessageQueueId_t CommandQueueHandle;
const osMessageQueueAttr_t CommandQueue_attributes = {
  .name = "CommandQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Start_MotorControl(void *argument);
void Start_Heartbeat(void *argument);
void Start_SpeedMeasure(void *argument);
void Start_SerialLog(void *argument);

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
  /* creation of CommandQueue */
  CommandQueueHandle = osMessageQueueNew (16, sizeof(uint16_t), &CommandQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of MotorControlTas */
  MotorControlTasHandle = osThreadNew(Start_MotorControl, NULL, &MotorControlTas_attributes);

  /* creation of HeartbeatTask */
  HeartbeatTaskHandle = osThreadNew(Start_Heartbeat, NULL, &HeartbeatTask_attributes);

  /* creation of SpeedMeasureTas */
  SpeedMeasureTasHandle = osThreadNew(Start_SpeedMeasure, NULL, &SpeedMeasureTas_attributes);

  /* creation of SerialLogTask */
  SerialLogTaskHandle = osThreadNew(Start_SerialLog, NULL, &SerialLogTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Start_MotorControl */
/**
  * @brief  Function implementing the MotorControlTas thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Start_MotorControl */
void Start_MotorControl(void *argument)
{
  /* USER CODE BEGIN Start_MotorControl */
  /* Infinite loop */
  for(;;)
  {
    if (motor_enable_flag == 0)
    {
      // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
      Motor_SetSpeed(&motor1, 0); // 停止
      osDelay(1);
    }
    else if (motor_enable_flag == 1)
    {

      // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
      Motor_SetSpeed(&motor1, 1000); // 正转
      osDelay(2000);

      motor_enable_flag = 0; // 运行一次后复位标志

      // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
      Motor_SetSpeed(&motor1, 0); // 停止
      osDelay(1000);
    }
    else if (motor_enable_flag == 2)
    {
      // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
      Motor_SetSpeed(&motor1, -800); // 反转
      osDelay(2000);

      motor_enable_flag = 0; // 运行一次后复位标志

      // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
      Motor_SetSpeed(&motor1, 0); // 停止
      osDelay(1000);
      // motor_enable_flag = 0; // 运行一次后复位标志
    }
    else if (motor_enable_flag == 3)
    {
      // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // 切换 LED 状态，观察任务运行情况
      Motor_SetSpeed(&motor1, 0); // 停止
      osDelay(1);
    }
  }
  /* USER CODE END Start_MotorControl */
}

/* USER CODE BEGIN Header_Start_Heartbeat */
/**
* @brief Function implementing the HeartbeatTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Heartbeat */
void Start_Heartbeat(void *argument)
{
  /* USER CODE BEGIN Start_Heartbeat */
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    osDelay(50);
  }
  /* USER CODE END Start_Heartbeat */
}

/* USER CODE BEGIN Header_Start_SpeedMeasure */
/**
* @brief Function implementing the SpeedMeasureTas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_SpeedMeasure */
void Start_SpeedMeasure(void *argument)
{
  /* USER CODE BEGIN Start_SpeedMeasure */
  /* Infinite loop */
  for(;;)
  {
    static int16_t last_cnt = 0; 
    int16_t now = (int16_t)__HAL_TIM_GET_COUNTER(&htim2);

    // 1. 速度计算 (快速操作)
    current_speed =  (now - last_cnt);
    // current_speed = - (now - last_cnt);
    last_cnt = now;

    // 2. 唤醒 LogTask (使用 CMSIS V2 任务通知)
    if (SerialLogTaskHandle != NULL)
    {
      osThreadFlagsSet(SerialLogTaskHandle, 0x01); // 设置标志位 0x01 唤醒 LogTask
    }
    osDelay(10); // 10ms 测速周期可行；1ms不行，完不成就过掉了
    // osDelay(1);    //冗余
  }
  /* USER CODE END Start_SpeedMeasure */
}

/* USER CODE BEGIN Header_Start_SerialLog */
/**
* @brief Function implementing the SerialLogTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_SerialLog */
void Start_SerialLog(void *argument)
{
  /* USER CODE BEGIN Start_SerialLog */
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
    int len = sprintf((char *)tx_buf, "%ld,%d\r\n", cnt_val, speed_val);

    // 3. 串口发送，DMA 方式
    // HAL_UART_Transmit(&huart1, tx_buf, len, HAL_MAX_DELAY);
    HAL_UART_Transmit_DMA(&huart1, tx_buf, len);

    osDelay(1);
  }
  /* USER CODE END Start_SerialLog */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

