################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../selex-fdk/sm_hal/src/sm_hal_adc.c \
../selex-fdk/sm_hal/src/sm_hal_can.c \
../selex-fdk/sm_hal/src/sm_hal_delay.c \
../selex-fdk/sm_hal/src/sm_hal_flash.c \
../selex-fdk/sm_hal/src/sm_hal_io.c \
../selex-fdk/sm_hal/src/sm_hal_iwdg.c \
../selex-fdk/sm_hal/src/sm_hal_system.c \
../selex-fdk/sm_hal/src/sm_hal_timer.c \
../selex-fdk/sm_hal/src/sm_hal_uart.c 

C_DEPS += \
./selex-fdk/sm_hal/src/sm_hal_adc.d \
./selex-fdk/sm_hal/src/sm_hal_can.d \
./selex-fdk/sm_hal/src/sm_hal_delay.d \
./selex-fdk/sm_hal/src/sm_hal_flash.d \
./selex-fdk/sm_hal/src/sm_hal_io.d \
./selex-fdk/sm_hal/src/sm_hal_iwdg.d \
./selex-fdk/sm_hal/src/sm_hal_system.d \
./selex-fdk/sm_hal/src/sm_hal_timer.d \
./selex-fdk/sm_hal/src/sm_hal_uart.d 

OBJS += \
./selex-fdk/sm_hal/src/sm_hal_adc.o \
./selex-fdk/sm_hal/src/sm_hal_can.o \
./selex-fdk/sm_hal/src/sm_hal_delay.o \
./selex-fdk/sm_hal/src/sm_hal_flash.o \
./selex-fdk/sm_hal/src/sm_hal_io.o \
./selex-fdk/sm_hal/src/sm_hal_iwdg.o \
./selex-fdk/sm_hal/src/sm_hal_system.o \
./selex-fdk/sm_hal/src/sm_hal_timer.o \
./selex-fdk/sm_hal/src/sm_hal_uart.o 


# Each subdirectory must supply rules for building sources it contributes
selex-fdk/sm_hal/src/%.o: ../selex-fdk/sm_hal/src/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RA_CORE=CM33 -D_RENESAS_RA_ -I"D:/Selex/pmu-v2/src" -I"D:/Selex/pmu-v2/ra/fsp/inc" -I"D:/Selex/pmu-v2/ra/fsp/inc/api" -I"D:/Selex/pmu-v2/ra/fsp/inc/instances" -I"D:/Selex/pmu-v2/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/Selex/pmu-v2/ra_gen" -I"D:/Selex/pmu-v2/ra_cfg/fsp_cfg/bsp" -I"D:/Selex/pmu-v2/ra_cfg/fsp_cfg" -I"D:/Selex/pmu-v2/selex-fdk/bsp/include" -I"D:/Selex/pmu-v2/selex-fdk/sm_hal/include" -I"D:/Selex/pmu-v2/src/porting/include" -I"D:/Selex/pmu-v2/selex-fdk/config" -I"D:/Selex/pmu-v2/selex-fdk/utils/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

