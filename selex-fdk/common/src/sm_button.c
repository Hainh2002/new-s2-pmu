/*
 * sm_button.c
 *
 *  Created on: Aug 17, 2023
 *      Author: Admin
 */

#include "sm_button.h"
#include "assert.h"

#define MAX_TIME_CLICK_DEFAULT_mS 80
#define TIME_OUT_CLICK_mS           200
#define MAX_TIME_HOLD_DEFAULT_mS 2000
#define RESET_VALUE 0

#define TIMEOUT_HOLD_mS 50


void sm_button_init(sm_button_t *key, sm_hal_io_t *io)
{
    assert(key != NULL);
    key->io = io;
    key->state = BT_ST_RELEASE;

}
/**
 *
 * @param button
 * @param time_diff_mS
 * @return
 */
button_st_t sm_button_update(sm_button_t *button, uint16_t time_diff_mS)

{
    button_st_t event = BT_ST_RELEASE;
    if (button->timeout_click > 0)
    {
        button->timeout_click -= time_diff_mS;
    }
    if (button->timeout_hold > 0)
        button->timeout_hold -= time_diff_mS;
    if (button->timeout_click == 0 && button->time_driff == 0)
    {
        if (button->time_click > 0)
            if (button->time_click == 1)
            {
                button->time_click = 0;
                return BT_ST_CLICK;
            }
        if (button->time_click == 2)
        {
            button->time_click = 0;
            return BT_ST_DOUBLE_CLICK;
        }
    }
    if (button->timeout_hold == 0)
    {
        if (button->time_hold >= MAX_TIME_HOLD_DEFAULT_mS)
        {
            event = BT_ST_HOLD_AND_RELEASE;
            button->time_hold = 0;
            return event;
        }
        button->time_hold = 0;
    }
    if (sm_hal_io_get_value (button->io) == BUTTON_RELEASE)
    {
        if (button->time_driff > MAX_TIME_CLICK_DEFAULT_mS && button->time_driff < MAX_TIME_CLICK_DEFAULT_mS * 2)
        {
            button->time_click += 1;
            button->timeout_click = TIME_OUT_CLICK_mS;
        }
        button->time_driff = 0;
    }
    else
    {
        button->time_driff += time_diff_mS;
        button->time_hold += time_diff_mS;
        if (button->time_hold == MAX_TIME_HOLD_DEFAULT_mS)
            return BT_ST_HOLD;
        button->timeout_hold = TIMEOUT_HOLD_mS;
    }
    return event;
}

