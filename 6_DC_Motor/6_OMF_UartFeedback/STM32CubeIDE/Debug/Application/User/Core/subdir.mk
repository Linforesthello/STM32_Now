################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/dma.c \
C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/freertos.c \
C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/gpio.c \
C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/main.c \
../Application/User/Core/motor.c \
C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/stm32f1xx_hal_msp.c \
C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/stm32f1xx_hal_timebase_tim.c \
C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/stm32f1xx_it.c \
../Application/User/Core/syscalls.c \
../Application/User/Core/sysmem.c \
C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/tim.c \
C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/usart.c 

OBJS += \
./Application/User/Core/dma.o \
./Application/User/Core/freertos.o \
./Application/User/Core/gpio.o \
./Application/User/Core/main.o \
./Application/User/Core/motor.o \
./Application/User/Core/stm32f1xx_hal_msp.o \
./Application/User/Core/stm32f1xx_hal_timebase_tim.o \
./Application/User/Core/stm32f1xx_it.o \
./Application/User/Core/syscalls.o \
./Application/User/Core/sysmem.o \
./Application/User/Core/tim.o \
./Application/User/Core/usart.o 

C_DEPS += \
./Application/User/Core/dma.d \
./Application/User/Core/freertos.d \
./Application/User/Core/gpio.d \
./Application/User/Core/main.d \
./Application/User/Core/motor.d \
./Application/User/Core/stm32f1xx_hal_msp.d \
./Application/User/Core/stm32f1xx_hal_timebase_tim.d \
./Application/User/Core/stm32f1xx_it.d \
./Application/User/Core/syscalls.d \
./Application/User/Core/sysmem.d \
./Application/User/Core/tim.d \
./Application/User/Core/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/dma.o: C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/dma.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/freertos.o: C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/freertos.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/gpio.o: C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/gpio.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/main.o: C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/main.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/%.o Application/User/Core/%.su Application/User/Core/%.cyclo: ../Application/User/Core/%.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/stm32f1xx_hal_msp.o: C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/stm32f1xx_hal_msp.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/stm32f1xx_hal_timebase_tim.o: C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/stm32f1xx_hal_timebase_tim.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/stm32f1xx_it.o: C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/stm32f1xx_it.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/tim.o: C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/tim.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/usart.o: C:/Users/86173/Desktop/ProjectRequirement/MCU_Now/Lin_STM32/STM32_F103C8T6/6_DC_Motor/6_OMF_UartFeedback/Core/Src/usart.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../../Core/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc -I../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Core

clean-Application-2f-User-2f-Core:
	-$(RM) ./Application/User/Core/dma.cyclo ./Application/User/Core/dma.d ./Application/User/Core/dma.o ./Application/User/Core/dma.su ./Application/User/Core/freertos.cyclo ./Application/User/Core/freertos.d ./Application/User/Core/freertos.o ./Application/User/Core/freertos.su ./Application/User/Core/gpio.cyclo ./Application/User/Core/gpio.d ./Application/User/Core/gpio.o ./Application/User/Core/gpio.su ./Application/User/Core/main.cyclo ./Application/User/Core/main.d ./Application/User/Core/main.o ./Application/User/Core/main.su ./Application/User/Core/motor.cyclo ./Application/User/Core/motor.d ./Application/User/Core/motor.o ./Application/User/Core/motor.su ./Application/User/Core/stm32f1xx_hal_msp.cyclo ./Application/User/Core/stm32f1xx_hal_msp.d ./Application/User/Core/stm32f1xx_hal_msp.o ./Application/User/Core/stm32f1xx_hal_msp.su ./Application/User/Core/stm32f1xx_hal_timebase_tim.cyclo ./Application/User/Core/stm32f1xx_hal_timebase_tim.d ./Application/User/Core/stm32f1xx_hal_timebase_tim.o ./Application/User/Core/stm32f1xx_hal_timebase_tim.su ./Application/User/Core/stm32f1xx_it.cyclo ./Application/User/Core/stm32f1xx_it.d ./Application/User/Core/stm32f1xx_it.o ./Application/User/Core/stm32f1xx_it.su ./Application/User/Core/syscalls.cyclo ./Application/User/Core/syscalls.d ./Application/User/Core/syscalls.o ./Application/User/Core/syscalls.su ./Application/User/Core/sysmem.cyclo ./Application/User/Core/sysmem.d ./Application/User/Core/sysmem.o ./Application/User/Core/sysmem.su ./Application/User/Core/tim.cyclo ./Application/User/Core/tim.d ./Application/User/Core/tim.o ./Application/User/Core/tim.su ./Application/User/Core/usart.cyclo ./Application/User/Core/usart.d ./Application/User/Core/usart.o ./Application/User/Core/usart.su

.PHONY: clean-Application-2f-User-2f-Core

