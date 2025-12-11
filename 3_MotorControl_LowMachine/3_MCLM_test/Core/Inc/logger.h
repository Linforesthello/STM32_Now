#ifndef __UART_APP_H
#define __UART_APP_H

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "command.h"

// 串口接收缓冲区长度
#define UART2_RX_BUF_LEN 32

// 串口初始化函数
void UART_App_Init(void);

// 串口发送函数
void UART2_Print(const char *msg);

// 串口接收中断回调
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif
