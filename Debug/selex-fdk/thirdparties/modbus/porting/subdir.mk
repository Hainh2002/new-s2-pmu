################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../selex-fdk/thirdparties/modbus/porting/portevent.c \
../selex-fdk/thirdparties/modbus/porting/portserial.c \
../selex-fdk/thirdparties/modbus/porting/porttimer.c 

C_DEPS += \
./selex-fdk/thirdparties/modbus/porting/portevent.d \
./selex-fdk/thirdparties/modbus/porting/portserial.d \
./selex-fdk/thirdparties/modbus/porting/porttimer.d 

OBJS += \
./selex-fdk/thirdparties/modbus/porting/portevent.o \
./selex-fdk/thirdparties/modbus/porting/portserial.o \
./selex-fdk/thirdparties/modbus/porting/porttimer.o 


# Each subdirectory must supply rules for building sources it contributes
selex-fdk/thirdparties/modbus/porting/%.o: ../selex-fdk/thirdparties/modbus/porting/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RA_CORE=CM33 -D_RENESAS_RA_ -I"D:/Selex/test/src" -I"D:/Selex/test/ra/fsp/inc" -I"D:/Selex/test/ra/fsp/inc/api" -I"D:/Selex/test/ra/fsp/inc/instances" -I"D:/Selex/test/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/Selex/test/ra_gen" -I"D:/Selex/test/ra_cfg/fsp_cfg/bsp" -I"D:/Selex/test/ra_cfg/fsp_cfg" -I"D:/Selex/test/selex-fdk/bsp/include" -I"D:/Selex/test/selex-fdk/sm_hal/include" -I"D:/Selex/test/src/porting/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

