#include "sm_bsp_peripherals.h"
#include "sm_bsp_system.h"
#include "sm_hal_uart.h"

static sm_hal_uart_t *g_uart;
int32_t sm_bsp_uart_init(uint32_t _baudrate, uint32_t _databit, uint32_t _parity){
    g_uart = sm_hal_uart_init(&uart_func, (void*)&g_uart0);
    sm_hal_uart_set_baurate(g_uart, _baudrate);
    sm_hal_uart_set_databit(g_uart, _databit);
    sm_hal_uart_set_parity(g_uart, _parity);
    return  sm_hal_uart_open(g_uart);
}

int32_t sm_bsp_uart_send(uint8_t *_tx_buffer, uint8_t _len){
    return sm_hal_uart_write(g_uart, _tx_buffer, _len);
}

void sm_bsp_uart_set_receive_handle(sm_bsp_uart_rx_irq_fn_t _uart_receive_handle){
    sm_hal_uart_set_rx_callback(g_uart, _uart_receive_handle);
}

