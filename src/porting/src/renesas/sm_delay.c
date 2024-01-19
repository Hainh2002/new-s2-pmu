/*
 * delay.c
 *
 *  Created on: Jul 10, 2023
 *      Author: Admin
 */


/*Include mcu platform*/
/*End include mcu platform*/

#include <sm_hal_delay.h>
#include "bsp_api.h"

void sm_hal_delay_ms(uint32_t timems){
    /*User code*/
	R_BSP_SoftwareDelay(timems, BSP_DELAY_UNITS_MILLISECONDS);
}
void sm_hal_delay_us(uint32_t timeus){
    /*User code*/
	R_BSP_SoftwareDelay(timeus, BSP_DELAY_UNITS_MICROSECONDS);
}

