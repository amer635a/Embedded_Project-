################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTG/Src/HAL_callback_functions.c \
../RTG/Src/RTG.c \
../RTG/Src/Tools.c \
../RTG/Src/myMessage_tools.c \
../RTG/Src/server_ETH._tools.c 

OBJS += \
./RTG/Src/HAL_callback_functions.o \
./RTG/Src/RTG.o \
./RTG/Src/Tools.o \
./RTG/Src/myMessage_tools.o \
./RTG/Src/server_ETH._tools.o 

C_DEPS += \
./RTG/Src/HAL_callback_functions.d \
./RTG/Src/RTG.d \
./RTG/Src/Tools.d \
./RTG/Src/myMessage_tools.d \
./RTG/Src/server_ETH._tools.d 


# Each subdirectory must supply rules for building sources it contributes
RTG/Src/%.o RTG/Src/%.su: ../RTG/Src/%.c RTG/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"C:/Users/ameer/git/Embedded_Project-/F7_ADC_DAC/RTG/Inc" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ameer/git/Embedded_Project-/F7_ADC_DAC/LWIP" -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/BSP/Components/lan8742 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-RTG-2f-Src

clean-RTG-2f-Src:
	-$(RM) ./RTG/Src/HAL_callback_functions.d ./RTG/Src/HAL_callback_functions.o ./RTG/Src/HAL_callback_functions.su ./RTG/Src/RTG.d ./RTG/Src/RTG.o ./RTG/Src/RTG.su ./RTG/Src/Tools.d ./RTG/Src/Tools.o ./RTG/Src/Tools.su ./RTG/Src/myMessage_tools.d ./RTG/Src/myMessage_tools.o ./RTG/Src/myMessage_tools.su ./RTG/Src/server_ETH._tools.d ./RTG/Src/server_ETH._tools.o ./RTG/Src/server_ETH._tools.su

.PHONY: clean-RTG-2f-Src

