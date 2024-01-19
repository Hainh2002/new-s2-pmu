#include <stdio.h>
#include <stdlib.h>
#include "sm_bsp_system.h"
#include "sm_bsp_peripherals.h"

static sm_hal_iwdg_t* g_iwdg;

int32_t sm_bsp_iwdg_start(){
    g_iwdg = sm_hal_iwdg_init(&iwdg_func, (void*)&g_wdt_on_iwdt);
    return sm_hal_iwdg_open(g_iwdg);
}

int32_t sm_bsp_iwdg_close(){
    return sm_hal_iwdg_close(g_iwdg);
}

int32_t sm_bsp_iwdg_reset(){
    return sm_hal_iwdg_reset(g_iwdg);
}
