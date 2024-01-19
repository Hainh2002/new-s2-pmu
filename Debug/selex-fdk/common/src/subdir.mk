################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../selex-fdk/common/src/sm_ble.c \
../selex-fdk/common/src/sm_button.c \
../selex-fdk/common/src/sm_ec200s.c \
../selex-fdk/common/src/sm_flash.c \
../selex-fdk/common/src/sm_http.c \
../selex-fdk/common/src/sm_http_header.c \
../selex-fdk/common/src/sm_led.c \
../selex-fdk/common/src/sm_modbus.c \
../selex-fdk/common/src/sm_modem.c \
../selex-fdk/common/src/sm_mqtt_client.c \
../selex-fdk/common/src/sm_security.c 

C_DEPS += \
./selex-fdk/common/src/sm_ble.d \
./selex-fdk/common/src/sm_button.d \
./selex-fdk/common/src/sm_ec200s.d \
./selex-fdk/common/src/sm_flash.d \
./selex-fdk/common/src/sm_http.d \
./selex-fdk/common/src/sm_http_header.d \
./selex-fdk/common/src/sm_led.d \
./selex-fdk/common/src/sm_modbus.d \
./selex-fdk/common/src/sm_modem.d \
./selex-fdk/common/src/sm_mqtt_client.d \
./selex-fdk/common/src/sm_security.d 

OBJS += \
./selex-fdk/common/src/sm_ble.o \
./selex-fdk/common/src/sm_button.o \
./selex-fdk/common/src/sm_ec200s.o \
./selex-fdk/common/src/sm_flash.o \
./selex-fdk/common/src/sm_http.o \
./selex-fdk/common/src/sm_http_header.o \
./selex-fdk/common/src/sm_led.o \
./selex-fdk/common/src/sm_modbus.o \
./selex-fdk/common/src/sm_modem.o \
./selex-fdk/common/src/sm_mqtt_client.o \
./selex-fdk/common/src/sm_security.o 


# Each subdirectory must supply rules for building sources it contributes
selex-fdk/common/src/%.o: ../selex-fdk/common/src/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RA_CORE=CM33 -D_RENESAS_RA_ -I"D:/Selex/test/src" -I"D:/Selex/test/ra/fsp/inc" -I"D:/Selex/test/ra/fsp/inc/api" -I"D:/Selex/test/ra/fsp/inc/instances" -I"D:/Selex/test/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/Selex/test/ra_gen" -I"D:/Selex/test/ra_cfg/fsp_cfg/bsp" -I"D:/Selex/test/ra_cfg/fsp_cfg" -I"D:/Selex/test/selex-fdk/bsp/include" -I"D:/Selex/test/selex-fdk/sm_hal/include" -I"D:/Selex/test/src/porting/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

