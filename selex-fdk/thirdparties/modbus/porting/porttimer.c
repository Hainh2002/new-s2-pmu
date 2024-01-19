/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#include "sm_hal_timer.h"

/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR(void *arg);

/* ----------------------- Start implementation -----------------------------*/

sm_hal_timer_t *modbus_timer;
static uint16_t timeout = 0;
volatile uint16_t counter = 0;
/**
 *
 * @param usTim1Timerout50us
 * @param dHTIM
 * @return
 */
BOOL xMBPortTimersInit(USHORT usTim1Timerout50us, void *dHTIM)
{
    (void) dHTIM;
    sm_hal_timer_set_callback (modbus_timer, prvvTIMERExpiredISR, NULL);
    modbus_timer->proc->open (modbus_timer);
    timeout = usTim1Timerout50us;
    return TRUE;
}
/**
 *
 */
inline void vMBPortTimersEnable()
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
    counter = 0;
    modbus_timer->proc->start (modbus_timer);
}

inline void vMBPortTimersDisable()
{
    /* Disable any pending timers. */
    modbus_timer->proc->stop (modbus_timer);
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
/**
 *
 * @param arg
 */
static void prvvTIMERExpiredISR(void *arg)
{
    (void) arg;
    if ((++counter) >= timeout)
        pxMBPortCBTimerExpired ();
}

