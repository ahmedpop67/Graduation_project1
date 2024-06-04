################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/AFIO_program.c \
../Core/Src/EXTI_program.c \
../Core/Src/GPIO_program.c \
../Core/Src/NVIC_program.c \
../Core/Src/PWM_DCmotor_prog.c \
../Core/Src/RCC_program.c \
../Core/Src/SPI_program.c \
../Core/Src/STK_program.c \
../Core/Src/Timer_prog.c \
../Core/Src/UART_conf.c \
../Core/Src/UART_program.c \
../Core/Src/Ultrasonic_prog.c \
../Core/Src/main.c \
../Core/Src/nrf24l01_program.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/AFIO_program.o \
./Core/Src/EXTI_program.o \
./Core/Src/GPIO_program.o \
./Core/Src/NVIC_program.o \
./Core/Src/PWM_DCmotor_prog.o \
./Core/Src/RCC_program.o \
./Core/Src/SPI_program.o \
./Core/Src/STK_program.o \
./Core/Src/Timer_prog.o \
./Core/Src/UART_conf.o \
./Core/Src/UART_program.o \
./Core/Src/Ultrasonic_prog.o \
./Core/Src/main.o \
./Core/Src/nrf24l01_program.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/AFIO_program.d \
./Core/Src/EXTI_program.d \
./Core/Src/GPIO_program.d \
./Core/Src/NVIC_program.d \
./Core/Src/PWM_DCmotor_prog.d \
./Core/Src/RCC_program.d \
./Core/Src/SPI_program.d \
./Core/Src/STK_program.d \
./Core/Src/Timer_prog.d \
./Core/Src/UART_conf.d \
./Core/Src/UART_program.d \
./Core/Src/Ultrasonic_prog.d \
./Core/Src/main.d \
./Core/Src/nrf24l01_program.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/AFIO_program.cyclo ./Core/Src/AFIO_program.d ./Core/Src/AFIO_program.o ./Core/Src/AFIO_program.su ./Core/Src/EXTI_program.cyclo ./Core/Src/EXTI_program.d ./Core/Src/EXTI_program.o ./Core/Src/EXTI_program.su ./Core/Src/GPIO_program.cyclo ./Core/Src/GPIO_program.d ./Core/Src/GPIO_program.o ./Core/Src/GPIO_program.su ./Core/Src/NVIC_program.cyclo ./Core/Src/NVIC_program.d ./Core/Src/NVIC_program.o ./Core/Src/NVIC_program.su ./Core/Src/PWM_DCmotor_prog.cyclo ./Core/Src/PWM_DCmotor_prog.d ./Core/Src/PWM_DCmotor_prog.o ./Core/Src/PWM_DCmotor_prog.su ./Core/Src/RCC_program.cyclo ./Core/Src/RCC_program.d ./Core/Src/RCC_program.o ./Core/Src/RCC_program.su ./Core/Src/SPI_program.cyclo ./Core/Src/SPI_program.d ./Core/Src/SPI_program.o ./Core/Src/SPI_program.su ./Core/Src/STK_program.cyclo ./Core/Src/STK_program.d ./Core/Src/STK_program.o ./Core/Src/STK_program.su ./Core/Src/Timer_prog.cyclo ./Core/Src/Timer_prog.d ./Core/Src/Timer_prog.o ./Core/Src/Timer_prog.su ./Core/Src/UART_conf.cyclo ./Core/Src/UART_conf.d ./Core/Src/UART_conf.o ./Core/Src/UART_conf.su ./Core/Src/UART_program.cyclo ./Core/Src/UART_program.d ./Core/Src/UART_program.o ./Core/Src/UART_program.su ./Core/Src/Ultrasonic_prog.cyclo ./Core/Src/Ultrasonic_prog.d ./Core/Src/Ultrasonic_prog.o ./Core/Src/Ultrasonic_prog.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/nrf24l01_program.cyclo ./Core/Src/nrf24l01_program.d ./Core/Src/nrf24l01_program.o ./Core/Src/nrf24l01_program.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

