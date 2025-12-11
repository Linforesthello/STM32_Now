// #ifndef __COMMAND_H
// #define __COMMAND_H

// #include "main.h"
// #include "cmsis_os.h"
// #include "motor.h"

// // 外部变量声明
// extern Motor_t motor1;
// extern volatile uint8_t motor_enable_flag;

// // 解析串口接收到的命令
// void Command_Parse(uint8_t cmd);

// #endif

#ifndef __COMMAND_H
#define __COMMAND_H

#include "main.h"
#include "cmsis_os.h"
#include "motor.h"
#include "stdint.h"

//=================== 命令类型定义 ===================//
typedef enum {
    CMD_NONE = 0,
    CMD_FORWARD,
    CMD_REVERSE,
    CMD_STOP,
    CMD_SET_SPEED
} CommandType_t;

//=================== 命令结构体定义 ===================//
typedef struct {
    CommandType_t type;  // 命令类型
    int16_t value;       // 参数（例如速度值）
} CommandMsg_t;

//=================== 外部变量 ===================//
extern Motor_t motor1;
// extern volatile uint8_t motor_enable_flag;       //20251210改动，未验证
extern osMessageQueueId_t CommandQueueHandle;

//=================== 函数声明 ===================//

// 串口字符串解析函数，例如输入 "S500" → CMD_SET_SPEED, value=500
CommandMsg_t Command_ParseString(const char *cmdStr);

// // 单字节命令兼容函数（旧版用）
// void Command_Parse(uint8_t cmd);

#endif
