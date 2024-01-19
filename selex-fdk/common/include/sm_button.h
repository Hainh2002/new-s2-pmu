/*
 * sm_button.h
 *
 *  Created on: Aug 17, 2023
 *      Author: Admin
 */

#ifndef COMMON_INCLUDE_SM_BUTTON_H_
#define COMMON_INCLUDE_SM_BUTTON_H_

#include <sm_hal_io.h>
#include "sm_fifo.h"
#include <stdbool.h>

#define BUTTON_RELEASE 1
#define BUTTON_PRESS   0

typedef enum key_st
{
    BT_ST_RELEASE = 0,
    BT_ST_PRESS = 1,
    BT_ST_CLICK = 2,
    BT_ST_DOUBLE_CLICK = 3,
    BT_ST_HOLD_AND_RELEASE = 4,
    BT_ST_HOLD = 5
} button_st_t;

typedef struct sm_button sm_button_t;

struct sm_button
{
    sm_hal_io_t *io;
    button_st_t state;
    uint16_t time_driff;
    uint16_t time_hold;
    uint16_t timeout_hold;
    uint16_t timeout_click;
    uint16_t time_click;
};
/**
 * @brief
 * @param key
 * @param io
 */
void sm_button_init(sm_button_t *key, sm_hal_io_t *io);
/**
 * @brief
 * @param button
 * @param time_diff_mS
 * @return  0: success | NULL : false
 */
button_st_t sm_button_update(sm_button_t *button, uint16_t time_diff_mS);

#endif /* COMMON_INCLUDE_SM_BUTTON_H_ */
