#include "sm_hal_adc.h"
#include "sm_bsp_peripherals.h"
#include "sm_hal_can.h"
#include "sm_bsp_io.h"
#include "sm_porting.h"

static sm_hal_can_t* g_can_port ;
static int32_t can_mode_enable();

int32_t sm_bsp_can_init(){
    if (can_mode_enable() != 0)
        return -1;
    g_can_port = sm_hal_can_init(&can_func, (void*)&g_can0);
    return sm_hal_can_open(g_can_port);
}

int32_t sm_bsp_can_send(uint32_t _id, uint8_t *_tx_buffer, uint8_t _len){
    sm_hal_can_mgs_t msg;
    msg.id = _id;
    memcpy(msg.data, _tx_buffer, _len);
    return sm_hal_can_write(g_can_port, &msg);
}

void sm_bsp_can_set_receive_handle(sm_bsp_can_rx_irq_fn_t _can_receive_handle){
    sm_hal_can_set_rx_callback(g_can_port, (func_can_rx_callback)_can_receive_handle);
}

static int32_t can_mode_enable(){
    return sm_bsp_io_set_value_can_mode(SM_BSP_IO_OFF);
}


