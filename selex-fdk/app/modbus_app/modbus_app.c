/*
 * modbus_app.c
 *
 *  Created on: Jul 8, 2023
 *      Author: Admin
 */


#include "modbus_app.h"

#if USING_MODBUS

extern sm_bsp_io_t *de_pin; //user define on board layer
extern sm_bsp_uart_t *uart1; //user define on board layer
extern sm_bsp_timer_t *timer1; //user define on board layer

#define N_REG_COIL 10
#define N_REG_DIS  10
#define N_REG_INPUT 20
#define N_REG_HOLDING 20

uint8_t coil_reg[N_REG_COIL];
uint8_t dis_reg[N_REG_DIS];
uint16_t input_reg[N_REG_INPUT];
uint16_t holding_reg[N_REG_HOLDING];

void task(void* arg);


sm_modbus_t mb_app = {
    .nregCoil = N_REG_COIL,
    .nregDisc = N_REG_DIS,
    .nregInput = N_REG_INPUT,
    .nregHolding = N_REG_HOLDING,
    .ucSCoilBuf = coil_reg,
    .ucSDiscInBuf = dis_reg,
    .usSRegHoldBuf = holding_reg,
    .usSRegInBuf = input_reg,
    .timer = timer1, // timer1
    .uart = uart1, // uart1
    .io = de_pin, // de_pin
};

void modbus_app_init(){
    sm_modbus_init(&mb_app, 1,SM_MODBUS_RTU);
}
void modbus_app_process(){
    sm_modbus_process(&mb_app);
}
#endif
