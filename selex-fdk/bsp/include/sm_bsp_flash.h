/*
 * sm_bsp_flash.h
 *
 *  Created on: Dec 25, 2023
 *      Author: hainh
 */

#ifndef BSP_INCLUDE_SM_BSP_FLASH_H_
#define BSP_INCLUDE_SM_BSP_FLASH_H_

#include <stdint.h>
#include <stdio.h>

/**
 * @fn sm_bsp_flash_init()
 * @brief
 *
 * @param _flash
 * @return
 */
int32_t sm_bsp_flash_init();
/**
 * @fn sm_bsp_flash_write(uint32_t _addr, void *_data, size_t _size)
 * @brief
 *
 * @param _flash
 * @return
 */
int32_t sm_bsp_flash_write(uint32_t _addr, void *_data, size_t _size);
/**
 * @fn sm_bsp_flash_read(uint32_t _addr, void *_data, size_t _size)
 * @brief
 *
 * @param _flash
 * @return
 */
int32_t sm_bsp_flash_read(uint32_t _addr, void *_data, size_t _size);


#endif /* BSP_INCLUDE_SM_BSP_FLASH_H_ */
