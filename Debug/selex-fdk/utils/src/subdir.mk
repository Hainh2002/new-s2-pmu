################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../selex-fdk/utils/src/sm_fifo.c \
../selex-fdk/utils/src/sm_link_list.c \
../selex-fdk/utils/src/sm_logger.c \
../selex-fdk/utils/src/sm_map.c \
../selex-fdk/utils/src/sm_math.c \
../selex-fdk/utils/src/sm_stack.c 

C_DEPS += \
./selex-fdk/utils/src/sm_fifo.d \
./selex-fdk/utils/src/sm_link_list.d \
./selex-fdk/utils/src/sm_logger.d \
./selex-fdk/utils/src/sm_map.d \
./selex-fdk/utils/src/sm_math.d \
./selex-fdk/utils/src/sm_stack.d 

OBJS += \
./selex-fdk/utils/src/sm_fifo.o \
./selex-fdk/utils/src/sm_link_list.o \
./selex-fdk/utils/src/sm_logger.o \
./selex-fdk/utils/src/sm_map.o \
./selex-fdk/utils/src/sm_math.o \
./selex-fdk/utils/src/sm_stack.o 


# Each subdirectory must supply rules for building sources it contributes
selex-fdk/utils/src/%.o: ../selex-fdk/utils/src/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RA_CORE=CM33 -D_RENESAS_RA_ -I"D:/Selex/pmu-v2/src" -I"D:/Selex/pmu-v2/ra/fsp/inc" -I"D:/Selex/pmu-v2/ra/fsp/inc/api" -I"D:/Selex/pmu-v2/ra/fsp/inc/instances" -I"D:/Selex/pmu-v2/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/Selex/pmu-v2/ra_gen" -I"D:/Selex/pmu-v2/ra_cfg/fsp_cfg/bsp" -I"D:/Selex/pmu-v2/ra_cfg/fsp_cfg" -I"D:/Selex/pmu-v2/selex-fdk/bsp/include" -I"D:/Selex/pmu-v2/selex-fdk/sm_hal/include" -I"D:/Selex/pmu-v2/src/porting/include" -I"D:/Selex/pmu-v2/selex-fdk/config" -I"D:/Selex/pmu-v2/selex-fdk/utils/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

