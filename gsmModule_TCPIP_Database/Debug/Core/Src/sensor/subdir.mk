################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/sensor/sensor.c 

OBJS += \
./Core/Src/sensor/sensor.o 

C_DEPS += \
./Core/Src/sensor/sensor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/sensor/%.o Core/Src/sensor/%.su: ../Core/Src/sensor/%.c Core/Src/sensor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"D:/svn_data/projeler/elzEnerji/gsm/sw/branch/r1/Core/Src/gsm" -I"D:/svn_data/projeler/elzEnerji/gsm/sw/branch/r1/Core/Src/sensor" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-sensor

clean-Core-2f-Src-2f-sensor:
	-$(RM) ./Core/Src/sensor/sensor.d ./Core/Src/sensor/sensor.o ./Core/Src/sensor/sensor.su

.PHONY: clean-Core-2f-Src-2f-sensor

