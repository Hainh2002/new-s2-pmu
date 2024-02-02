################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../selex-fdk/bsp/src/sm_bsp_adc.c \
../selex-fdk/bsp/src/sm_bsp_can.c \
../selex-fdk/bsp/src/sm_bsp_delay.c \
../selex-fdk/bsp/src/sm_bsp_io.c \
../selex-fdk/bsp/src/sm_bsp_iwdg.c \
../selex-fdk/bsp/src/sm_bsp_system.c \
../selex-fdk/bsp/src/sm_bsp_timer.c \
../selex-fdk/bsp/src/sm_bsp_uart.c 

C_DEPS += \
./selex-fdk/bsp/src/sm_bsp_adc.d \
./selex-fdk/bsp/src/sm_bsp_can.d \
./selex-fdk/bsp/src/sm_bsp_delay.d \
./selex-fdk/bsp/src/sm_bsp_io.d \
./selex-fdk/bsp/src/sm_bsp_iwdg.d \
./selex-fdk/bsp/src/sm_bsp_system.d \
./selex-fdk/bsp/src/sm_bsp_timer.d \
./selex-fdk/bsp/src/sm_bsp_uart.d 

OBJS += \
./selex-fdk/bsp/src/sm_bsp_adc.o \
./selex-fdk/bsp/src/sm_bsp_can.o \
./selex-fdk/bsp/src/sm_bsp_delay.o \
./selex-fdk/bsp/src/sm_bsp_io.o \
./selex-fdk/bsp/src/sm_bsp_iwdg.o \
./selex-fdk/bsp/src/sm_bsp_system.o \
./selex-fdk/bsp/src/sm_bsp_timer.o \
./selex-fdk/bsp/src/sm_bsp_uart.o 


# Each subdirectory must supply rules for building sources it contributes
selex-fdk/bsp/src/%.o: ../selex-fdk/bsp/src/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RA_CORE=CM33 -D_RENESAS_RA_ -I"D:/Selex/new-s2-pmu/src" -I"D:/Selex/new-s2-pmu/ra/fsp/inc" -I"D:/Selex/new-s2-pmu/ra/fsp/inc/api" -I"D:/Selex/new-s2-pmu/ra/fsp/inc/instances" -I"D:/Selex/new-s2-pmu/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/Selex/new-s2-pmu/ra_gen" -I"D:/Selex/new-s2-pmu/ra_cfg/fsp_cfg/bsp" -I"D:/Selex/new-s2-pmu/ra_cfg/fsp_cfg" -I"D:/Selex/new-s2-pmu/selex-fdk/sm_hal/include" -I"D:/Selex/new-s2-pmu/selex-fdk/bsp/include" -I"D:/Selex/new-s2-pmu/selex-fdk/config" -I"D:/Selex/new-s2-pmu/selex-fdk/utils/include" -I"D:/Selex/new-s2-pmu/src/porting/include" -I"D:/Selex/new-s2-pmu/selex-fdk/services/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

