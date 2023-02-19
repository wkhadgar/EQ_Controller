################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/NRF24L01/Src/nrf24l01p.c 

OBJS += \
./Drivers/NRF24L01/Src/nrf24l01p.o 

C_DEPS += \
./Drivers/NRF24L01/Src/nrf24l01p.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/NRF24L01/Src/%.o Drivers/NRF24L01/Src/%.su: ../Drivers/NRF24L01/Src/%.c Drivers/NRF24L01/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_NRF24L01 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/NRF24L01/Inc -I../Drivers/Display/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-NRF24L01-2f-Src

clean-Drivers-2f-NRF24L01-2f-Src:
	-$(RM) ./Drivers/NRF24L01/Src/nrf24l01p.d ./Drivers/NRF24L01/Src/nrf24l01p.o ./Drivers/NRF24L01/Src/nrf24l01p.su

.PHONY: clean-Drivers-2f-NRF24L01-2f-Src

