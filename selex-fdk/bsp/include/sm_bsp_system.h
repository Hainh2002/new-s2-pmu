/*
 * sm_bsp_system.h
 *
 *  Created on: Dec 25, 2023
 *      Author: hainh
 */

#ifndef BSP_INCLUDE_SM_BSP_SYSTEM_H_
#define BSP_INCLUDE_SM_BSP_SYSTEM_H_

#include "sm_bsp_peripherals.h"
#include "sm_bsp_flash.h"
#include "sm_bsp_io.h"

/**
 * @fn sm_bsp_system_init()
 * @brief
 *
 * @param
 * @return
 */
void sm_bsp_system_init();
/**
 * @fn sm_bsp_system_reset()
 * @brief
 *
 * @param
 * @return
 */
void sm_bsp_system_reset();
/**
 * @fn sm_bsp_delay_us()
 * @brief
 *
 * @param
 * @return
 */
void sm_bsp_delay_us(uint32_t timeus);
/**
 * @fn sm_bsp_delay_ms()
 * @brief
 *
 * @param
 * @return
 */
void sm_bsp_delay_ms(uint32_t timems);

#endif /* BSP_INCLUDE_SM_BSP_SYSTEM_H_ */
