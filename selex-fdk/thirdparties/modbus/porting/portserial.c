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

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#include "sm_hal_uart.h"
#include "sm_hal_io.h"
//#include "cmsis_gcc.h"

sm_hal_uart_t *modbus_uart;
sm_hal_io_t *modbus_de;

uint8_t singlechar = 0;

/* ----------------------- static functions ---------------------------------*/
static void prvvUARTTxReadyISR(sm_hal_uart_t *_this);
static void prvvUARTRxISR(sm_hal_uart_t *_this, uint8_t *data, uint32_t len);

/* ----------------------- Start implementation -----------------------------*/
/**
 *
 * @param xRxEnable
 * @param xTxEnable
 */
void vMBPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{
    /* If xRXEnable enable serial receive interrupts. If xTxENable enable
     * transmitter empty interrupts.
     */
    if (xRxEnable)
    {
        if (modbus_de->proc != NULL)
            modbus_de->proc->set_value (modbus_de, 0);
    }
    else
    {
        modbus_uart->proc->abort_rx (modbus_uart);
    }
    if (xTxEnable)
    {
        if (modbus_de->proc != NULL)
            modbus_de->proc->set_value (modbus_de, 1);
        pxMBFrameCBTransmitterEmpty ();

    }
    else
    {
        modbus_uart->proc->abort_tx (modbus_uart);
    }
}
/**
 *
 * @param dHUART
 * @param ulBaudRate
 * @param dHTIM
 * @return
 */
BOOL xMBPortSerialInit(void *dHUART, ULONG ulBaudRate, void *dHTIM)
{

    (void) dHTIM;
    (void) ulBaudRate;
    (void) dHUART;
    sm_hal_uart_set_rx_callback (modbus_uart, prvvUARTRxISR);
    sm_hal_uart_set_tx_callback (modbus_uart, prvvUARTTxReadyISR);

    modbus_uart->proc->open (modbus_uart);

    return TRUE;
}
/**
 *
 * @param ucByte
 * @return
 */
BOOL xMBPortSerialPutByte(CHAR ucByte)
{
    /* Put a byte in the UARTs transmit buffer. This function is called
     * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
     * called. */
//    sm_hal_uart_write(modbus_uart,(uint8_t*) &ucByte, 1);
    modbus_uart->proc->write (modbus_uart, (uint8_t*) &ucByte, 1);
    return TRUE;
}
/**
 *
 * @param ucByte
 * @param usSize
 * @return
 */
BOOL xMBPortSerialPutBytes(volatile UCHAR *ucByte, USHORT usSize)
{
//    sm_hal_uart_write(modbus_uart,(uint8_t*) ucByte,usSize);
    modbus_uart->proc->write (modbus_uart, (uint8_t*) ucByte, usSize);
    return TRUE;
}
/**
 *
 * @param pucByte
 * @return
 */
BOOL xMBPortSerialGetByte(CHAR *pucByte)
{
    /* Return the byte in the UARTs receive buffer. This function is called
     * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
     */
    *pucByte = (CHAR) (singlechar);
    return TRUE;
}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
/**
 *
 * @param _this
 */
static void prvvUARTTxReadyISR(sm_hal_uart_t *_this)
{
    (void) _this;
    pxMBFrameCBTransmitterEmpty ();
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
/**
 *
 * @param _this
 * @param data
 * @param len
 */
static void prvvUARTRxISR(sm_hal_uart_t *_this, uint8_t *data, uint32_t len)
{
    (void) _this;
    (void) len;
    singlechar = data[0];
    pxMBFrameCBByteReceived ();
}

static uint32_t lock_count = 0;
/**
 *
 */
void __critical_enter(void)
{
    __disable_irq ();
    lock_count++;
}
/**
 *
 */
void __critical_exit(void)
{
    lock_count--;
    if (lock_count == 0)
        __enable_irq ();
}
