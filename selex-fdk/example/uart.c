/*
 * uart.c
 *
 *  Created on: Sep 29, 2023
 *      Author: MinhNhan
 */


#include "sm_hal_uart.h"

#define UART0 0x232342514 // UART address



void int main(int argc, char **argv) {

	sm_hal_uart_proc_t uart_func = {
			// START USER CODE
			// END USER CODE
	};

	// dynamic
	sm_hal_uart_t *uart = sm_hal_uart_init(&uart_func,(void*)UART0);

	// static

	sm_uart_static_t uart_buff;
	sm_hal_uart_t *uart = sm_hal_uart_init_static(&uart_func,(void*)UART0, &uart_buff);
	return 0;
}




