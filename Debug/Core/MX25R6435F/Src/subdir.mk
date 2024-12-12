################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MX25R6435F/Src/MX25R6435F.c 

OBJS += \
./Core/MX25R6435F/Src/MX25R6435F.o 

C_DEPS += \
./Core/MX25R6435F/Src/MX25R6435F.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MX25R6435F/Src/%.o Core/MX25R6435F/Src/%.su Core/MX25R6435F/Src/%.cyclo: ../Core/MX25R6435F/Src/%.c Core/MX25R6435F/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/custom -I../Core/MX25R6435F/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-MX25R6435F-2f-Src

clean-Core-2f-MX25R6435F-2f-Src:
	-$(RM) ./Core/MX25R6435F/Src/MX25R6435F.cyclo ./Core/MX25R6435F/Src/MX25R6435F.d ./Core/MX25R6435F/Src/MX25R6435F.o ./Core/MX25R6435F/Src/MX25R6435F.su

.PHONY: clean-Core-2f-MX25R6435F-2f-Src

