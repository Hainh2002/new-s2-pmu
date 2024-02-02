################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_ioport/r_ioport.c 

C_DEPS += \
./ra/fsp/src/r_ioport/r_ioport.d 

OBJS += \
./ra/fsp/src/r_ioport/r_ioport.o 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_ioport/%.o: ../ra/fsp/src/r_ioport/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RA_CORE=CM33 -D_RENESAS_RA_ -I"D:/Selex/new-s2-pmu/src" -I"D:/Selex/new-s2-pmu/ra/fsp/inc" -I"D:/Selex/new-s2-pmu/ra/fsp/inc/api" -I"D:/Selex/new-s2-pmu/ra/fsp/inc/instances" -I"D:/Selex/new-s2-pmu/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/Selex/new-s2-pmu/ra_gen" -I"D:/Selex/new-s2-pmu/ra_cfg/fsp_cfg/bsp" -I"D:/Selex/new-s2-pmu/ra_cfg/fsp_cfg" -I"D:/Selex/new-s2-pmu/selex-fdk/sm_hal/include" -I"D:/Selex/new-s2-pmu/selex-fdk/bsp/include" -I"D:/Selex/new-s2-pmu/selex-fdk/config" -I"D:/Selex/new-s2-pmu/selex-fdk/utils/include" -I"D:/Selex/new-s2-pmu/src/porting/include" -I"D:/Selex/new-s2-pmu/selex-fdk/services/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

