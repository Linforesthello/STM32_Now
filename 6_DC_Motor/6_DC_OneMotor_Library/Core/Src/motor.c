#include "motor.h"
#include "stdlib.h"

void Motor_Init(Motor_t *motor, TIM_HandleTypeDef *htim, uint32_t Channel,
                GPIO_TypeDef *IN1_Port, uint16_t IN1_Pin,
                GPIO_TypeDef *IN2_Port, uint16_t IN2_Pin,
                GPIO_TypeDef *EN_Port, uint16_t EN_Pin,
                uint16_t MaxPWM, int16_t MaxSpeed, uint16_t DeadZone,
                uint8_t Polarity, MotorStopMode_t StopMode) {

    motor->htim = htim;
    motor->Channel = Channel;
    motor->IN1_Port = IN1_Port;
    motor->IN1_Pin = IN1_Pin;
    motor->IN2_Port = IN2_Port;
    motor->IN2_Pin = IN2_Pin;
    motor->EN_Port = EN_Port;
    motor->EN_Pin = EN_Pin;

    motor->MaxPWM = MaxPWM;
    motor->MaxSpeed = MaxSpeed;
    motor->DeadZone = DeadZone;
    motor->Polarity = Polarity;
    motor->StopMode = StopMode;

    // 启动PWM
    HAL_TIM_PWM_Start(motor->htim, motor->Channel);

    // 如果有 EN 引脚，拉高
    if (motor->EN_Port != NULL) {
        HAL_GPIO_WritePin(motor->EN_Port, motor->EN_Pin, GPIO_PIN_SET);
    }
}

void Motor_SetSpeed(Motor_t *motor, int16_t speed) {
    // 限幅
    if (speed > motor->MaxSpeed) speed = motor->MaxSpeed;
    if (speed < -motor->MaxSpeed) speed = -motor->MaxSpeed;

    // 极性反转
    if (motor->Polarity) speed = -speed;

    // 死区
    if (speed > 0 && speed < motor->DeadZone) speed = motor->DeadZone;
    if (speed < 0 && speed > -(motor->DeadZone)) speed = -(motor->DeadZone);

    // 换算成 PWM 占空比
    uint16_t pwmVal = (uint16_t)((abs(speed) * motor->MaxPWM) / motor->MaxSpeed);

    if (speed > 0) {
        HAL_GPIO_WritePin(motor->IN1_Port, motor->IN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor->IN2_Port, motor->IN2_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(motor->htim, motor->Channel, pwmVal);
    } else if (speed < 0) {
        HAL_GPIO_WritePin(motor->IN1_Port, motor->IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->IN2_Port, motor->IN2_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(motor->htim, motor->Channel, pwmVal);
    } else {
        Motor_Stop(motor);
    }
}

void Motor_Stop(Motor_t *motor) {
    __HAL_TIM_SET_COMPARE(motor->htim, motor->Channel, 0);
    if (motor->StopMode == MOTOR_STOP_COAST) {
        HAL_GPIO_WritePin(motor->IN1_Port, motor->IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->IN2_Port, motor->IN2_Pin, GPIO_PIN_RESET);
    } else { // BRAKE
        HAL_GPIO_WritePin(motor->IN1_Port, motor->IN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor->IN2_Port, motor->IN2_Pin, GPIO_PIN_SET);
    }
}
