################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/custom/custom.c 

OBJS += \
./Drivers/BSP/custom/custom.o 

C_DEPS += \
./Drivers/BSP/custom/custom.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/custom/%.o Drivers/BSP/custom/%.su Drivers/BSP/custom/%.cyclo: ../Drivers/BSP/custom/%.c Drivers/BSP/custom/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/custom -I../Core/MX25R6435F/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-custom

clean-Drivers-2f-BSP-2f-custom:
	-$(RM) ./Drivers/BSP/custom/custom.cyclo ./Drivers/BSP/custom/custom.d ./Drivers/BSP/custom/custom.o ./Drivers/BSP/custom/custom.su

.PHONY: clean-Drivers-2f-BSP-2f-custom

