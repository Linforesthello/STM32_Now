#ifndef __COMMAND_H
#define __COMMAND_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ===================== 命令类型定义 ===================== */

typedef enum {
    CMD_NONE = 0,      // 无效命令
    CMD_FORWARD,       // 前进（具体速度由电机控制任务决定）
    CMD_REVERSE,       // 后退
    CMD_STOP,          // 停止
    CMD_SET_SPEED      // 设置速度：例如 "S500"
} CommandType_t;

/* ===================== 命令消息结构 ===================== */

typedef struct {
    CommandType_t type;    // 命令类型
    int16_t value;         // 参数（如速度值），对无参数命令无效
} CommandMsg_t;

/* ===================== 协议说明 ===================== */
/*
 * 字符串协议格式：
 *   "Sxxx"    → CMD_SET_SPEED, value = xxx
 *   "F"       → CMD_FORWARD
 *   "R"       → CMD_REVERSE
 *   "X"       → CMD_STOP
 *
 * 数字格式支持正/负，如 "S-300"
 */

/* ===================== 函数声明 ===================== */

// 字符串解析（主函数）
// 输入:    字符串，例如 "S500"
// 返回:    CommandMsg_t结构体
CommandMsg_t Command_ParseString(const char *cmdStr);

#ifdef __cplusplus
}
#endif

#endif /* __COMMAND_H */




// #ifndef __COMMAND_H
// #define __COMMAND_H

// #include "main.h"
// #include "cmsis_os.h"
// #include "tb6612_DC.h"
// #include "stdint.h"

// //=================== 命令类型定义 ===================//
// typedef enum {
//     CMD_NONE = 0,
//     CMD_FORWARD,
//     CMD_REVERSE,
//     CMD_STOP,
//     CMD_SET_SPEED
// } CommandType_t;

// //=================== 命令结构体定义 ===================//
// typedef struct {
//     CommandType_t type;  // 命令类型
//     int16_t value;       // 参数（例如速度值）
// } CommandMsg_t;

// //=================== 外部变量 ===================//
// // extern Motor_t motor1;
// // extern volatile uint8_t motor_enable_flag;       //20251210改动，未验证

// 这里的extern去掉了，解耦合；同时logger.c报错，显示句柄缺失；接入了app_task.h
// extern osMessageQueueId_t CommandQueueHandle;

// //=================== 函数声明 ===================//

// // 串口字符串解析函数，例如输入 "S500" → CMD_SET_SPEED, value=500
// CommandMsg_t Command_ParseString(const char *cmdStr);

// // // 单字节命令兼容函数（旧版用）
// // void Command_Parse(uint8_t cmd);

// #endif


// // #ifndef __COMMAND_H
// // #define __COMMAND_H

// // #include "main.h"
// // #include "cmsis_os.h"
// // #include "motor.h"

// // // 外部变量声明
// // extern Motor_t motor1;
// // extern volatile uint8_t motor_enable_flag;

// // // 解析串口接收到的命令
// // void Command_Parse(uint8_t cmd);

// // #endif
