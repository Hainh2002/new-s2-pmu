/*
 * sm_led.c
 *
 *  Created on: Aug 18, 2023
 *      Author: Admin
 */

#include "sm_led.h"

void sm_led_init(sm_led_t *_this, sm_hal_io_t *_io)
{
    _this->_io = _io;
    sm_led_set_state (_this, LED_ST_OFF);
}
/**
 *
 * @param _this
 * @param _state
 * @return
 */
int32_t sm_led_set_state(sm_led_t *_this, enum led_state _state)
{
    return sm_hal_io_set_value (_this->_io, _state);
}
