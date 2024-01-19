#include <stdio.h>
#include <stdlib.h>
#include "sm_bsp_system.h"
#include "sm_bsp_peripherals.h"
//#include "hal_data.h"

static sm_hal_timer_t *g_timer_1ms;
static sm_hal_timer_t *g_timer_10ms;

void sm_bsp_timer_1ms_init(){
    g_timer_1ms = sm_hal_timer_init(&timer_func, NULL, "timer_1ms", NULL, (void*)&g_timer0);
    sm_hal_timer_open(g_timer_1ms);
    sm_hal_timer_start(g_timer_1ms);
}

void sm_bsp_timer_10ms_init(){
    g_timer_10ms = sm_hal_timer_init(&timer_func, NULL, "timer_10ms", NULL, (void*)&g_timer1);
    sm_hal_timer_open(g_timer_10ms);
    sm_hal_timer_start(g_timer_10ms);
}

void sm_bsp_timer_1ms_set_irq_handle(sm_bsp_timer_irq_fn_t _1ms_irq_handle){
    sm_hal_timer_set_callback(g_timer_1ms, _1ms_irq_handle, NULL);
}

void sm_bsp_timer_10ms_set_irq_handle(sm_bsp_timer_irq_fn_t _10ms_irq_handle){
    sm_hal_timer_set_callback(g_timer_1ms, _10ms_irq_handle, NULL);
}
