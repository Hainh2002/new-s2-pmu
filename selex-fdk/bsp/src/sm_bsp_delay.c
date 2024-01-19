#include "sm_bsp_system.h"


void sm_bsp_delay_ms(uint32_t _timems){
    sm_hal_delay_ms(_timems);
}

void sm_bsp_delay_us(uint32_t _timeus){
    sm_hal_delay_us(_timeus);
}
