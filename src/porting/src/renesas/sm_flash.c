/*
 * flash.c
 *
 *  Created on: Jul 10, 2023
 *      Author: Admin
 */

#include <sm_hal_flash.h>

/*Include User Code*/

/*End*/
static int32_t flash_write(sm_hal_flash_t *_this, uint32_t addr, void *data, size_t size);
static int32_t flash_read(sm_hal_flash_t *_this, uint32_t addr, void *data, size_t size);
static int32_t flash_erase(sm_hal_flash_t *_this, uint32_t addr, size_t size);
static int32_t flash_open(sm_hal_flash_t *_this);
static int32_t flash_close(sm_hal_flash_t *_this);

sm_hal_flash_proc_t flash_func =
{ .write = flash_write, .read = flash_read, .erase = flash_erase, .open = flash_open, .close = flash_close };

static int32_t flash_write(sm_hal_flash_t *_this, uint32_t addr, void *data, size_t size)
{
    /*User code*/
    return 0;
}
static int32_t flash_read(sm_hal_flash_t *_this, uint32_t addr, void *data, size_t size)
{
    /*User code*/
    return 0;
}
static int32_t flash_erase(sm_hal_flash_t *_this, uint32_t addr, size_t size)
{
    /*User code*/
    return 0;
}
static int32_t flash_open(sm_hal_flash_t *_this)
{
    /*User code*/
    return 0;
}
static int32_t flash_close(sm_hal_flash_t *_this)
{
    /*User code*/
    return 0;
}
