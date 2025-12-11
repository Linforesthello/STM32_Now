#include "cmsis_os.h"
#include "tb6612_DC.h"
#include "command.h"
#include "app_task.h"


void MotorControl_Task(void *argument)
{
  /* USER CODE BEGIN Start_MotorControl */

  // uint8_t cmd;
  CommandMsg_t cmdMsg;

  /* Infinite loop */
  for(;;)
  {
    if (osMessageQueueGet(CommandQueueHandle, &cmdMsg, NULL, osWaitForever) == osOK)
    {
      switch (cmdMsg.type)
      {
        case CMD_FORWARD:
            Motor_SetSpeed(&motor1, 800);
            // UART2_Print("CMD: Forward\r\n");
            break;
        case CMD_REVERSE:
            Motor_SetSpeed(&motor1, -800);
            // UART2_Print("CMD: Reverse\r\n");
            break;
        case CMD_STOP:
            Motor_Stop(&motor1);
            // UART2_Print("CMD: Stop\r\n");
            break;
        case CMD_SET_SPEED:
            // 用的最多
            Motor_SetSpeed(&motor1, cmdMsg.value);
            break;

        default:
            // Motor_Stop(&motor1);
            break;
      }
    }
    osDelay(10);
  }
  /* USER CODE END Start_MotorControl */
}
