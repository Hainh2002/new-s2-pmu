################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/porting/src/renesas/sm_adc.c \
../src/porting/src/renesas/sm_can.c \
../src/porting/src/renesas/sm_delay.c \
../src/porting/src/renesas/sm_flash.c \
../src/porting/src/renesas/sm_gpio.c \
../src/porting/src/renesas/sm_iwdg.c \
../src/porting/src/renesas/sm_timer.c \
../src/porting/src/renesas/sm_uart.c 

C_DEPS += \
./src/porting/src/renesas/sm_adc.d \
./src/porting/src/renesas/sm_can.d \
./src/porting/src/renesas/sm_delay.d \
./src/porting/src/renesas/sm_flash.d \
./src/porting/src/renesas/sm_gpio.d \
./src/porting/src/renesas/sm_iwdg.d \
./src/porting/src/renesas/sm_timer.d \
./src/porting/src/renesas/sm_uart.d 

OBJS += \
./src/porting/src/renesas/sm_adc.o \
./src/porting/src/renesas/sm_can.o \
./src/porting/src/renesas/sm_delay.o \
./src/porting/src/renesas/sm_flash.o \
./src/porting/src/renesas/sm_gpio.o \
./src/porting/src/renesas/sm_iwdg.o \
./src/porting/src/renesas/sm_timer.o \
./src/porting/src/renesas/sm_uart.o 


# Each subdirectory must supply rules for building sources it contributes
src/porting/src/renesas/%.o: ../src/porting/src/renesas/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RA_CORE=CM33 -D_RENESAS_RA_ -I"D:/Selex/pmu-v2/src" -I"D:/Selex/pmu-v2/ra/fsp/inc" -I"D:/Selex/pmu-v2/ra/fsp/inc/api" -I"D:/Selex/pmu-v2/ra/fsp/inc/instances" -I"D:/Selex/pmu-v2/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/Selex/pmu-v2/ra_gen" -I"D:/Selex/pmu-v2/ra_cfg/fsp_cfg/bsp" -I"D:/Selex/pmu-v2/ra_cfg/fsp_cfg" -I"D:/Selex/pmu-v2/selex-fdk/bsp/include" -I"D:/Selex/pmu-v2/selex-fdk/sm_hal/include" -I"D:/Selex/pmu-v2/src/porting/include" -I"D:/Selex/pmu-v2/selex-fdk/config" -I"D:/Selex/pmu-v2/selex-fdk/utils/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

