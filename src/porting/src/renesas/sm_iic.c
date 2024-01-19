/*
 * iic.c
 *
 *  Created on: Jul 10, 2023
 *      Author: Admin
 */


/*include mcu platform*/

/*end*/

#include <sm_hal_iic.h>
#include "stm32g0xx_hal.h"

#define _impl(x) ((I2C_HandleTypeDef*)(x))

static    int32_t iic_open(sm_hal_iic_t *_this);
static    int32_t iic_close(sm_hal_iic_t *_this);
static    int32_t iic_write(sm_hal_iic_t *_this,uint8_t *data,uint32_t len);
static    int32_t iic_read(sm_hal_iic_t *_this,uint8_t *data,uint32_t len);
static    int32_t iic_abort(sm_hal_iic_t *_this);
static    int32_t iic_set_addr(sm_hal_iic_t *_this,uint8_t addr);

sm_hal_iic_proc_t iic_func = {.abort = iic_abort,.open = iic_open,.close = iic_close,.read = iic_read,.set_addr = iic_set_addr ,.write = iic_write};

static int32_t iic_open(sm_hal_iic_t *_this)
{
    /*User code*/
    return 0;
}
static int32_t iic_close(sm_hal_iic_t *_this)
{

    /*User code*/
    return 0;
}
static int32_t iic_write(sm_hal_iic_t *_this, uint8_t *data, uint32_t len)
{
    /*User code*/
    return HAL_I2C_Master_Transmit_IT(_impl(_this->handle),_this->addr,data, len);
}
static int32_t iic_read(sm_hal_iic_t *_this, uint8_t *data, uint32_t len)
{
    /*User code*/
    return HAL_I2C_Master_Receive_IT(_impl(_this->handle),_this->addr,data, len);
}
static int32_t iic_abort(sm_hal_iic_t *_this)
{
    /*User code*/
    return HAL_I2C_Master_Abort_IT(_impl(_this->handle),_this->addr);
}
static int32_t iic_set_addr(sm_hal_iic_t *_this, uint8_t addr)
{
    /*User code*/
	_this->addr = addr;
    return 0;
}
