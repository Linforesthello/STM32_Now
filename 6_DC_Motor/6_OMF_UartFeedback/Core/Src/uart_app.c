#include "uart_app.h"
#include "usart.h"
#include "string.h"
#include "command.h"

// 串口接收缓冲区
static uint8_t uart2_rx_buf[UART2_RX_BUF_LEN];
static uint8_t uart2_rx_index = 0;
static uint8_t uart2_rx_data;

// 串口发送缓冲区
static uint8_t uart2_tx_buf[64];
static volatile uint8_t uart2_tx_busy = 0;

// 串口初始化函数
void UART_App_Init(void)
{
    // 启动串口接收中断
    HAL_UART_Receive_IT(&huart2, &uart2_rx_data, 1);
}

// 串口发送函数
void UART2_Print(const char *msg)
{
    if (uart2_tx_busy) return; // 若上次发送未完成则丢弃（简化处理）
    uint16_t len = strlen(msg);
    if (len > 64) len = 64;

    memcpy(uart2_tx_buf, msg, len);
    uart2_tx_busy = 1;
    HAL_UART_Transmit_IT(&huart2, uart2_tx_buf, len);
}

// 串口接收中断回调
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        uint8_t ch = uart2_rx_data;

        if (ch == '\r' || ch == '\n') // 一帧命令结束
        {
            uart2_rx_buf[uart2_rx_index] = '\0';
            uart2_rx_index = 0;

            CommandMsg_t msg = Command_ParseString((char*)uart2_rx_buf);
            osMessageQueuePut(CommandQueueHandle, &msg, 0, 0); // 将命令放入消息队列
        }
        else if (uart2_rx_index < UART2_RX_BUF_LEN - 1)
        {
            uart2_rx_buf[uart2_rx_index++] = ch;
        }

        // 继续接收下一个字节
        HAL_UART_Receive_IT(&huart2, &uart2_rx_data, 1);
    }
}

// 串口发送完成回调
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        uart2_tx_busy = 0; // 释放发送锁
    }
}
