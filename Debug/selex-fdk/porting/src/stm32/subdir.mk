################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../selex-fdk/porting/src/stm32/sm_adc.c \
../selex-fdk/porting/src/stm32/sm_can.c \
../selex-fdk/porting/src/stm32/sm_delay.c \
../selex-fdk/porting/src/stm32/sm_flash.c \
../selex-fdk/porting/src/stm32/sm_gpio.c \
../selex-fdk/porting/src/stm32/sm_iic.c \
../selex-fdk/porting/src/stm32/sm_iwdg.c \
../selex-fdk/porting/src/stm32/sm_pwm.c \
../selex-fdk/porting/src/stm32/sm_spi.c \
../selex-fdk/porting/src/stm32/sm_timer.c \
../selex-fdk/porting/src/stm32/sm_uart.c 

C_DEPS += \
./selex-fdk/porting/src/stm32/sm_adc.d \
./selex-fdk/porting/src/stm32/sm_can.d \
./selex-fdk/porting/src/stm32/sm_delay.d \
./selex-fdk/porting/src/stm32/sm_flash.d \
./selex-fdk/porting/src/stm32/sm_gpio.d \
./selex-fdk/porting/src/stm32/sm_iic.d \
./selex-fdk/porting/src/stm32/sm_iwdg.d \
./selex-fdk/porting/src/stm32/sm_pwm.d \
./selex-fdk/porting/src/stm32/sm_spi.d \
./selex-fdk/porting/src/stm32/sm_timer.d \
./selex-fdk/porting/src/stm32/sm_uart.d 

OBJS += \
./selex-fdk/porting/src/stm32/sm_adc.o \
./selex-fdk/porting/src/stm32/sm_can.o \
./selex-fdk/porting/src/stm32/sm_delay.o \
./selex-fdk/porting/src/stm32/sm_flash.o \
./selex-fdk/porting/src/stm32/sm_gpio.o \
./selex-fdk/porting/src/stm32/sm_iic.o \
./selex-fdk/porting/src/stm32/sm_iwdg.o \
./selex-fdk/porting/src/stm32/sm_pwm.o \
./selex-fdk/porting/src/stm32/sm_spi.o \
./selex-fdk/porting/src/stm32/sm_timer.o \
./selex-fdk/porting/src/stm32/sm_uart.o 


# Each subdirectory must supply rules for building sources it contributes
selex-fdk/porting/src/stm32/%.o: ../selex-fdk/porting/src/stm32/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RA_CORE=CM33 -D_RENESAS_RA_ -I"D:/Selex/test/src" -I"D:/Selex/test/ra/fsp/inc" -I"D:/Selex/test/ra/fsp/inc/api" -I"D:/Selex/test/ra/fsp/inc/instances" -I"D:/Selex/test/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/Selex/test/ra_gen" -I"D:/Selex/test/ra_cfg/fsp_cfg/bsp" -I"D:/Selex/test/ra_cfg/fsp_cfg" -I"D:/Selex/test/selex-fdk/bsp/include" -I"D:/Selex/test/selex-fdk/sm_hal/include" -I"D:/Selex/test/src/porting/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

