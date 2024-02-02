#include "sm_bsp_flash.h"
#include <stdio.h>
#include <stdlib.h>

static sm_hal_flash_t* g_flash;

int32_t sm_bsp_flash_init(){
    g_flash = sm_hal_flash_init(&flash_func, &g_flash0);
    return sm_hal_flash_open(g_flash);
}

int32_t sm_bsp_flash_write(uint32_t _addr, void *_data, size_t _size){
    return sm_hal_flash_write(g_flash, _addr, _data, _size);
}

int32_t sm_bsp_flash_read(uint32_t _addr, void *_data, size_t _size){
    return sm_hal_flash_read(g_flash, _addr, _data, _size);
}
