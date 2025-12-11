#include "command.h"
#include "usart.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

//20251210,为什么这里加入了死定义？明明motor.h结构体内定义了Maxspeed
// #define MAX_SPEED 1000
// #define MIN_SPEED -1000

//=================== 新版：字符串命令解析 ===================//
// 例如：
// "S500" → CMD_SET_SPEED, value=500
// "F"    → CMD_FORWARD
// "R"    → CMD_REVERSE
// "X"    → CMD_STOP
CommandMsg_t Command_ParseString(const char *cmdStr)
{
    CommandMsg_t msg = {CMD_NONE, 0};

    if (cmdStr == NULL || cmdStr[0] == '\0')
        return msg;

    // 格式 1: S500 → 设置速度
    if (cmdStr[0] == 'S' || cmdStr[0] == 's') {
        msg.type = CMD_SET_SPEED;
        msg.value = atoi(&cmdStr[1]);  // 提取数值

        if (msg.value > motor1.MaxSpeed) msg.value = motor1.MaxSpeed;
        if (msg.value < -motor1.MaxSpeed) msg.value = -motor1.MaxSpeed;

    }
    // 格式 2: F → Forward
    else if (cmdStr[0] == 'F' || cmdStr[0] == 'f') {
        msg.type = CMD_FORWARD;
    }
    // 格式 3: R → Reverse
    else if (cmdStr[0] == 'R' || cmdStr[0] == 'r') {
        msg.type = CMD_REVERSE;
    }
    // 格式 4: X → Stop
    else if (cmdStr[0] == 'X' || cmdStr[0] == 'x') {
        msg.type = CMD_STOP;
    }

    return msg;
}
