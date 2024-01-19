/*
 * example_uart.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Admin
 */


#include "sm_hal_uart.h"
#include "stdio.h"

static int32_t uart_write(sm_hal_uart_t *_this, uint8_t *buff, uint32_t len);
static int32_t uart_set_baudrate(sm_hal_uart_t *_this, uint32_t baudrate);
static int32_t uart_set_parity(sm_hal_uart_t *_this, sm_uart_parity_t parity);
static int32_t uart_set_databit(sm_hal_uart_t *_this, sm_uart_databit_t databit);
static int32_t uart_open(sm_hal_uart_t *_this);
static int32_t uart_close(sm_hal_uart_t *_this);


sm_hal_uart_t *lte_uart;

sm_hal_uart_proc_t lte_uart_proc =
{ .close = uart_close,
  .open = uart_open,
  .set_databit = uart_set_databit,
  .write = uart_write,
  .set_parity = uart_set_parity,
  .set_baudrate = uart_set_baudrate };


int main(int argc, char **argv) {


    lte_uart = sm_hal_uart_init (&lte_uart_proc,(void*) &g_uart0);

    lte_uart->m_proc->open(lte_uart);


    sm_hal_uart_write(lte_uart,(uint8_t*) "Hello world\r\n",strlen("Hello world\r\n"));

    return 0;
}

static int32_t uart_write(sm_hal_uart_t *_this, uint8_t *buff, uint32_t len){
    printf(buff);
    return 0;
}
static int32_t uart_set_baudrate(sm_hal_uart_t *_this, uint32_t baudrate){
    return 0;
}
static int32_t uart_set_parity(sm_hal_uart_t *_this, sm_uart_parity_t parity){
    return 0;
}
static int32_t uart_set_databit(sm_hal_uart_t *_this, sm_uart_databit_t databit){
    return 0;
}
static int32_t uart_open(sm_hal_uart_t *_this){
    return 0;
}
static int32_t uart_close(sm_hal_uart_t *_this){
    return 0;
}
