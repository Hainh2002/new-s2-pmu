################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../selex-fdk/cores/src/sm_assign_master.c \
../selex-fdk/cores/src/sm_assign_slave.c \
../selex-fdk/cores/src/sm_bootloader_t.c \
../selex-fdk/cores/src/sm_bootmaster.c \
../selex-fdk/cores/src/sm_device_shadown.c \
../selex-fdk/cores/src/sm_event.c \
../selex-fdk/cores/src/sm_filesystem.c \
../selex-fdk/cores/src/sm_ota.c \
../selex-fdk/cores/src/sm_sch_task.c \
../selex-fdk/cores/src/sm_shell.c \
../selex-fdk/cores/src/sm_shell_command.c 

C_DEPS += \
./selex-fdk/cores/src/sm_assign_master.d \
./selex-fdk/cores/src/sm_assign_slave.d \
./selex-fdk/cores/src/sm_bootloader_t.d \
./selex-fdk/cores/src/sm_bootmaster.d \
./selex-fdk/cores/src/sm_device_shadown.d \
./selex-fdk/cores/src/sm_event.d \
./selex-fdk/cores/src/sm_filesystem.d \
./selex-fdk/cores/src/sm_ota.d \
./selex-fdk/cores/src/sm_sch_task.d \
./selex-fdk/cores/src/sm_shell.d \
./selex-fdk/cores/src/sm_shell_command.d 

OBJS += \
./selex-fdk/cores/src/sm_assign_master.o \
./selex-fdk/cores/src/sm_assign_slave.o \
./selex-fdk/cores/src/sm_bootloader_t.o \
./selex-fdk/cores/src/sm_bootmaster.o \
./selex-fdk/cores/src/sm_device_shadown.o \
./selex-fdk/cores/src/sm_event.o \
./selex-fdk/cores/src/sm_filesystem.o \
./selex-fdk/cores/src/sm_ota.o \
./selex-fdk/cores/src/sm_sch_task.o \
./selex-fdk/cores/src/sm_shell.o \
./selex-fdk/cores/src/sm_shell_command.o 


# Each subdirectory must supply rules for building sources it contributes
selex-fdk/cores/src/%.o: ../selex-fdk/cores/src/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RA_CORE=CM33 -D_RENESAS_RA_ -I"D:/Selex/new-s2-pmu/src" -I"D:/Selex/new-s2-pmu/ra/fsp/inc" -I"D:/Selex/new-s2-pmu/ra/fsp/inc/api" -I"D:/Selex/new-s2-pmu/ra/fsp/inc/instances" -I"D:/Selex/new-s2-pmu/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/Selex/new-s2-pmu/ra_gen" -I"D:/Selex/new-s2-pmu/ra_cfg/fsp_cfg/bsp" -I"D:/Selex/new-s2-pmu/ra_cfg/fsp_cfg" -I"D:/Selex/new-s2-pmu/selex-fdk/sm_hal/include" -I"D:/Selex/new-s2-pmu/selex-fdk/bsp/include" -I"D:/Selex/new-s2-pmu/selex-fdk/config" -I"D:/Selex/new-s2-pmu/selex-fdk/utils/include" -I"D:/Selex/new-s2-pmu/src/porting/include" -I"D:/Selex/new-s2-pmu/selex-fdk/services/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

