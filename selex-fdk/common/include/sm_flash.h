/*
 * sm_spi_flash.h
 *
 *  Created on: Sep 26, 2023
 *      Author: MinhNhan
 */

#ifndef COMMON_INCLUDE_SM_FLASH_H_
#define COMMON_INCLUDE_SM_FLASH_H_


#include <stdio.h>
#include <stdint.h>

typedef struct sm_flash sm_flash_t;

struct sm_flash{
	int (*erase)(uint32_t block);
	int (*write)(uint32_t block,uint32_t off,void *buff,uint32_t size);
	int (*read)(uint32_t block,uint32_t off,void *buff,uint32_t size);
};
/**
 * @brief
 * @param _this
 * @param _block
 * @return
 */
int sm_flash_erase(sm_flash_t *_this,uint32_t _block);
/**
 * @brief
 * @param _this
 * @param block
 * @param off
 * @param buff
 * @param size
 * @return
 */
int sm_flash_write(sm_flash_t *_this,uint32_t block,uint32_t off,void *buff,uint32_t size);
/**
 * @brief
 * @param _this
 * @param block
 * @param off
 * @param buff
 * @param size
 * @return
 */
int sm_flash_read(sm_flash_t *_this,uint32_t block,uint32_t off,void *buff,uint32_t size);

#endif /* COMMON_INCLUDE_SM_FLASH_H_ */
