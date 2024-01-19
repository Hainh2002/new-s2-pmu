/*
 * sm_flash.c
 *
 *  Created on: Sep 26, 2023
 *      Author: MinhNhan
 */

#include "sm_flash.h"

/**
 *
 * @param _this
 * @param _block
 * @return
 */
int sm_flash_erase(sm_flash_t *_this, uint32_t _block)
{
    return _this->erase (_block);
}
/**
 *
 * @param _this
 * @param block
 * @param off
 * @param buff
 * @param size
 * @return
 */
int sm_flash_write(sm_flash_t *_this, uint32_t block, uint32_t off, void *buff, uint32_t size)
{
    return _this->write (block, off, buff, size);
}
/**
 *
 * @param _this
 * @param block
 * @param off
 * @param buff
 * @param size
 * @return
 */
int sm_flash_read(sm_flash_t *_this, uint32_t block, uint32_t off, void *buff, uint32_t size)
{
    return _this->read (block, off, buff, size);
}
