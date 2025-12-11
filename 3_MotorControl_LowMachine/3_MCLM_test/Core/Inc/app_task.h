#ifndef __APP_TASKS_H__
#define __APP_TASKS_H__

#include "cmsis_os.h"

// ========== Task Handles ==========
extern osThreadId_t MotorControl_TaHandle;
extern osThreadId_t Encoder_TaHandle;
extern osThreadId_t Logger_TaHandle;
extern osThreadId_t Command_TaHandle;
extern osThreadId_t Heartbeat_TaHandle;

// ========== Queues ==========
extern osMessageQueueId_t CommandQueueHandle;

#endif



// #ifndef __APP_TASKS_H__
// #define __APP_TASKS_H__

// #include "cmsis_os2.h"

// extern osThreadId_t MotorControlTasHandle;
// extern osThreadId_t HeartbeatTaskHandle;
// extern osThreadId_t SpeedMeasureTasHandle;
// extern osThreadId_t SerialLogTaskHandle;

// extern osMessageQueueId_t CommandQueueHandle;

// #endif



// // #ifndef __APP_TASKS_H__
// // #define __APP_TASKS_H__

// // #include "cmsis_os2.h"

// // extern osThreadId_t SerialLogTaskHandle;
// // extern osThreadId_t SpeedMeasureTaskHandle;
// // extern osThreadId_t MotorControlTaskHandle;

// // #endif
