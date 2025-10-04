#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"

typedef enum {
    MOTOR_STOP_COAST = 0,   // 悬空停止（两相低电平）
    MOTOR_STOP_BRAKE        // 快速刹车（两相高电平）
} MotorStopMode_t;

typedef struct {
    TIM_HandleTypeDef *htim;  // PWM 定时器
    uint32_t Channel;         // PWM 通道
    GPIO_TypeDef *IN1_Port;   // IN1 引脚端口
    uint16_t IN1_Pin;         // IN1 引脚
    GPIO_TypeDef *IN2_Port;   // IN2 引脚端口
    uint16_t IN2_Pin;         // IN2 引脚
    GPIO_TypeDef *EN_Port;    // 使能端口（可选，没有则 NULL）
    uint16_t EN_Pin;          // 使能引脚

    uint16_t MaxPWM;          // 最大 PWM 值 (CubeMX TIM ARR)
    int16_t MaxSpeed;         // 最大速度（用户逻辑范围，例 ±1000）
    uint16_t DeadZone;        // 死区PWM（避免小值电机不动）
    uint8_t Polarity;         // 极性(0=默认,1=反转)
    MotorStopMode_t StopMode; // 停止模式
} Motor_t;

// 初始化电机
void Motor_Init(Motor_t *motor, TIM_HandleTypeDef *htim, uint32_t Channel,
                GPIO_TypeDef *IN1_Port, uint16_t IN1_Pin,
                GPIO_TypeDef *IN2_Port, uint16_t IN2_Pin,
                GPIO_TypeDef *EN_Port, uint16_t EN_Pin,
                uint16_t MaxPWM, int16_t MaxSpeed, uint16_t DeadZone,
                uint8_t Polarity, MotorStopMode_t StopMode);

// 设置速度
void Motor_SetSpeed(Motor_t *motor, int16_t speed);

// 停止电机
void Motor_Stop(Motor_t *motor);

#endif
