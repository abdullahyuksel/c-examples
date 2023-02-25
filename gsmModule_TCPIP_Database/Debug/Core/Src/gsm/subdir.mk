################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/gsm/gsm.c 

OBJS += \
./Core/Src/gsm/gsm.o 

C_DEPS += \
./Core/Src/gsm/gsm.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/gsm/%.o Core/Src/gsm/%.su: ../Core/Src/gsm/%.c Core/Src/gsm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32L051xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"D:/svn_data/projeler/elzEnerji/gsm/sw/branch/r1/Core/Src/gsm" -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-gsm

clean-Core-2f-Src-2f-gsm:
	-$(RM) ./Core/Src/gsm/gsm.d ./Core/Src/gsm/gsm.o ./Core/Src/gsm/gsm.su

.PHONY: clean-Core-2f-Src-2f-gsm

