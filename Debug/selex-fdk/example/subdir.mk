################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../selex-fdk/example/example_uart.c \
../selex-fdk/example/uart.c 

C_DEPS += \
./selex-fdk/example/example_uart.d \
./selex-fdk/example/uart.d 

OBJS += \
./selex-fdk/example/example_uart.o \
./selex-fdk/example/uart.o 


# Each subdirectory must supply rules for building sources it contributes
selex-fdk/example/%.o: ../selex-fdk/example/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RA_CORE=CM33 -D_RENESAS_RA_ -I"D:/Selex/test/src" -I"D:/Selex/test/ra/fsp/inc" -I"D:/Selex/test/ra/fsp/inc/api" -I"D:/Selex/test/ra/fsp/inc/instances" -I"D:/Selex/test/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/Selex/test/ra_gen" -I"D:/Selex/test/ra_cfg/fsp_cfg/bsp" -I"D:/Selex/test/ra_cfg/fsp_cfg" -I"D:/Selex/test/selex-fdk/bsp/include" -I"D:/Selex/test/selex-fdk/sm_hal/include" -I"D:/Selex/test/src/porting/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

