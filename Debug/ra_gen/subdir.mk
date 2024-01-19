################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra_gen/common_data.c \
../ra_gen/hal_data.c \
../ra_gen/main.c \
../ra_gen/pin_data.c \
../ra_gen/vector_data.c 

C_DEPS += \
./ra_gen/common_data.d \
./ra_gen/hal_data.d \
./ra_gen/main.d \
./ra_gen/pin_data.d \
./ra_gen/vector_data.d 

OBJS += \
./ra_gen/common_data.o \
./ra_gen/hal_data.o \
./ra_gen/main.o \
./ra_gen/pin_data.o \
./ra_gen/vector_data.o 


# Each subdirectory must supply rules for building sources it contributes
ra_gen/%.o: ../ra_gen/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RA_CORE=CM33 -D_RENESAS_RA_ -I"D:/Selex/pmu-v2/src" -I"D:/Selex/pmu-v2/ra/fsp/inc" -I"D:/Selex/pmu-v2/ra/fsp/inc/api" -I"D:/Selex/pmu-v2/ra/fsp/inc/instances" -I"D:/Selex/pmu-v2/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/Selex/pmu-v2/ra_gen" -I"D:/Selex/pmu-v2/ra_cfg/fsp_cfg/bsp" -I"D:/Selex/pmu-v2/ra_cfg/fsp_cfg" -I"D:/Selex/pmu-v2/selex-fdk/bsp/include" -I"D:/Selex/pmu-v2/selex-fdk/sm_hal/include" -I"D:/Selex/pmu-v2/src/porting/include" -I"D:/Selex/pmu-v2/selex-fdk/config" -I"D:/Selex/pmu-v2/selex-fdk/utils/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

