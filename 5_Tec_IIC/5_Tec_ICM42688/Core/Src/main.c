/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdio.h"
#include "string.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */



/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define ICM42688_ADDR       (0x68 << 1)   // HAL I2C地址左移1位
#define REG_WHO_AM_I        0x75
#define REG_PWR_MGMT0       0x4E
#define REG_ACCEL_DATA_X1   0x1F
#define REG_GYRO_DATA_X1    0x25

#define LED_ON()   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)
#define LED_OFF()  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t whoami = 0;
uint8_t buf[6];          // 读加速度或陀螺仪数据
// char uart_buf[64];
uint8_t tx_buf[64];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void UART_SendText(char *msg);

void ICM42688_Init(void);
void ICM42688_ReadData(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  LED_OFF();
  ICM42688_Init();

  HAL_Delay(100);  // 等待ICM42688上电稳定

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
        LED_ON();
        ICM42688_ReadData();
        HAL_Delay(50);
        LED_OFF();
        HAL_Delay(50);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/* USER CODE BEGIN 4 */

void UART_SendText(char *msg)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

void ICM42688_Init(void)
{
    uint8_t data;

    // 读取 WHO_AM_I 寄存器
    if(HAL_I2C_Mem_Read(&hi2c1, ICM42688_ADDR, REG_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, &whoami, 1, 100) == HAL_OK)
    {
        sprintf((char*)tx_buf, "WHO_AM_I = 0x%02X\r\n", whoami);
        UART_SendText((char*)tx_buf);
        if (whoami != 0x47)
        {
            UART_SendText("ICM42688 not detected!\r\n");
            return;
        }
    }
    else
    {
        UART_SendText("I2C communication failed!\r\n");
        return;
    }

    // 解除休眠，启动加速度计和陀螺仪
    data = 0x0F;
    HAL_I2C_Mem_Write(&hi2c1, ICM42688_ADDR, REG_PWR_MGMT0, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
    HAL_Delay(10);

    UART_SendText("ICM42688 Init OK\r\n");
}

void ICM42688_ReadData(void)
{
    // 读取加速度计数据
    HAL_I2C_Mem_Read(&hi2c1, ICM42688_ADDR, REG_ACCEL_DATA_X1, I2C_MEMADD_SIZE_8BIT, buf, 6, 100);
    int16_t ax = (int16_t)(buf[0]<<8 | buf[1]);
    int16_t ay = (int16_t)(buf[2]<<8 | buf[3]);
    int16_t az = (int16_t)(buf[4]<<8 | buf[5]);

    // 读取陀螺仪数据
    HAL_I2C_Mem_Read(&hi2c1, ICM42688_ADDR, REG_GYRO_DATA_X1, I2C_MEMADD_SIZE_8BIT, buf, 6, 100);
    int16_t gx = (int16_t)(buf[0]<<8 | buf[1]);
    int16_t gy = (int16_t)(buf[2]<<8 | buf[3]);
    int16_t gz = (int16_t)(buf[4]<<8 | buf[5]);

    sprintf((char*)tx_buf, "%6d,%6d,%6d,%6d,%6d,%6d\r\n",
            ax, ay, az, gx, gy, gz);
    UART_SendText((char*)tx_buf);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
