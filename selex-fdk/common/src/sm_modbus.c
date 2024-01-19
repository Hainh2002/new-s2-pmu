/*
 * sm_modbus.c
 *
 *  Created on: Jul 8, 2023
 *      Author: Admin
 */

#include "sm_modbus.h"

#if USING_MODBUS

#include "mb.h"
#include "mbconfig.h"
#include "mbutils.h"
extern sm_hal_uart_t *modbus_uart;
extern sm_hal_io_t *modbus_de;
extern sm_hal_timer_t *modbus_timer;

uint16_t *nregInput;
uint16_t *nregHolding;
uint16_t *nregCoil;
uint16_t *nregDesc;

uint8_t *ucSDiscInBuf;
uint8_t *ucSCoilBuf;
uint16_t *usSRegInBuf;
uint16_t *usSRegHoldBuf;

static mb_func_cb_t mb_callback = NULL;
static void *arg = NULL;
/**
 *
 * @param _this
 * @param addr
 * @param protocol
 */
void sm_modbus_init(sm_modbus_t *_this, uint8_t addr, sm_modbus_protocol_t protocol)
{
    _this->protocol = protocol;
    _this->protocol = SM_MODBUS_RTU;
    /*    _this->uart = modbus_uart;
     _this->io = modbus_de;
     _this->timer = modbus_timer;*/
    modbus_uart = _this->uart;
    modbus_de = _this->io;
    modbus_timer = _this->timer;
    _this->addr = addr;
    eMBInit (MB_RTU, _this->addr, NULL, 115200, NULL);

    nregInput = &_this->nregInput;
    nregCoil = &_this->nregCoil;
    nregHolding = &_this->nregHolding;
    nregDesc = &_this->nregDisc;

    ucSDiscInBuf = _this->ucSDiscInBuf;
    ucSCoilBuf = _this->ucSCoilBuf;
    usSRegInBuf = _this->usSRegInBuf;
    usSRegHoldBuf = _this->usSRegHoldBuf;

}
/**
 *
 * @param _this
 */
void sm_modbus_process(sm_modbus_t *_this)
{
    (void) _this;
    eMBPoll ();
}
/**
 *
 * @param pucRegBuffer
 * @param usAddress
 * @param usNRegs
 * @return
 */
eMBErrorCode eMBRegInputCB(UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNRegs)
{
    if (*nregInput > 0)
    {
        eMBErrorCode eStatus = MB_ENOERR;
        USHORT iRegIndex;
        USHORT *pusRegInputBuf;
        USHORT REG_INPUT_START;
        USHORT REG_INPUT_NREGS;
        USHORT usRegInStart;

        pusRegInputBuf = usSRegInBuf;
        REG_INPUT_START = 0;
        REG_INPUT_NREGS = *nregInput;
        usRegInStart = 0;

        /* it already plus one in modbus function method. */
        usAddress--;

        if ((usAddress >= REG_INPUT_START) && (usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS))
        {
            iRegIndex = usAddress - usRegInStart;
            while (usNRegs > 0)
            {
                *pucRegBuffer++ = (UCHAR) (pusRegInputBuf[iRegIndex] >> 8);
                *pucRegBuffer++ = (UCHAR) (pusRegInputBuf[iRegIndex] & 0xFF);
                iRegIndex++;
                usNRegs--;
            }
        }
        else
        {
            eStatus = MB_ENOREG;
        }

        return eStatus;
    }
    else
        return MB_ENOREG;

}

eMBErrorCode eMBRegHoldingCB(UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode)
{
    if (*nregHolding > 0)
    {
        eMBErrorCode eStatus = MB_ENOERR;
        USHORT iRegIndex;
        USHORT *pusRegHoldingBuf;
        USHORT REG_HOLDING_START;
        USHORT REG_HOLDING_NREGS;
        USHORT usRegHoldStart;
        uint16_t num_reg = usNRegs;
        pusRegHoldingBuf = usSRegHoldBuf;
        REG_HOLDING_START = 0;
        REG_HOLDING_NREGS = *nregHolding;
        usRegHoldStart = 0;

        /* it already plus one in modbus function method. */
        usAddress--;

        if ((usAddress >= REG_HOLDING_START) && (usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS))
        {
            iRegIndex = usAddress - usRegHoldStart;
            switch (eMode)
            {
                /* read current register values from the protocol stack. */
                case MB_REG_READ:
                    while (usNRegs > 0)
                    {
                        *pucRegBuffer++ = (UCHAR) (pusRegHoldingBuf[iRegIndex] >> 8);
                        *pucRegBuffer++ = (UCHAR) (pusRegHoldingBuf[iRegIndex] & 0xFF);
                        iRegIndex++;
                        usNRegs--;
                    }
                break;

                    /* write current register values with new values from the protocol stack. */
                case MB_REG_WRITE:
                    while (usNRegs > 0)
                    {
                        pusRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
                        pusRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
                        iRegIndex++;
                        usNRegs--;
                    }
                    if (mb_callback != NULL)
                    {
                        mb_callback (usAddress, num_reg, arg);
                    }
                break;
            }
        }
        else
        {
            eStatus = MB_ENOREG;
        }
        return eStatus;
    }
    else
        return MB_ENOREG;

}

eMBErrorCode eMBRegCoilsCB(UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode)
{
    if (*nregCoil > 0)
    {
        eMBErrorCode eStatus = MB_ENOERR;
        USHORT iRegIndex, iRegBitIndex, iNReg;
        UCHAR *pucCoilBuf;
        USHORT COIL_START;
        USHORT COIL_NCOILS;
        USHORT usCoilStart;
        iNReg = usNCoils / 8 + 1;

        pucCoilBuf = ucSCoilBuf;
        COIL_START = 0;
        COIL_NCOILS = *nregCoil;
        usCoilStart = 0;
        uint16_t num_reg = usNCoils;
        /* it already plus one in modbus function method. */
        usAddress--;

        if ((usAddress >= COIL_START) && (usAddress + usNCoils <= COIL_START + COIL_NCOILS))
        {
            iRegIndex = (USHORT) (usAddress - usCoilStart) / 8;
            iRegBitIndex = (USHORT) (usAddress - usCoilStart) % 8;
            switch (eMode)
            {
                /* read current coil values from the protocol stack. */
                case MB_REG_READ:
                    while (iNReg > 0)
                    {
                        *pucRegBuffer++ = xMBUtilGetBits (&pucCoilBuf[iRegIndex++], iRegBitIndex, 8);
                        iNReg--;
                    }
                    pucRegBuffer--;
                    /* last coils */
                    usNCoils = usNCoils % 8;
                    /* filling zero to high bit */
                    *pucRegBuffer = *pucRegBuffer << (8 - usNCoils);
                    *pucRegBuffer = *pucRegBuffer >> (8 - usNCoils);
                break;

                    /* write current coil values with new values from the protocol stack. */
                case MB_REG_WRITE:
                    while (iNReg > 1)
                    {
                        xMBUtilSetBits (&pucCoilBuf[iRegIndex++], iRegBitIndex, 8, *pucRegBuffer++);
                        iNReg--;
                    }
                    /* last coils */
                    usNCoils = usNCoils % 8;
                    /* xMBUtilSetBits has bug when ucNBits is zero */
                    if (usNCoils != 0)
                    {
                        xMBUtilSetBits (&pucCoilBuf[iRegIndex++], iRegBitIndex, usNCoils, *pucRegBuffer++);
                    }
                    if (mb_callback != NULL)
                    {
                        mb_callback (usAddress, num_reg, arg);
                    }
                break;
            }
        }
        else
        {
            eStatus = MB_ENOREG;
        }
        return eStatus;
    }
    else
        return MB_ENOREG;

}

eMBErrorCode eMBRegDiscreteCB(UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNDiscrete)
{
    if (*nregDesc > 0)
    {
        eMBErrorCode eStatus = MB_ENOERR;
        USHORT iRegIndex, iRegBitIndex, iNReg;
        UCHAR *pucDiscreteInputBuf;
        USHORT DISCRETE_INPUT_START;
        USHORT DISCRETE_INPUT_NDISCRETES;
        USHORT usDiscreteInputStart;
        iNReg = usNDiscrete / 8 + 1;

        pucDiscreteInputBuf = ucSDiscInBuf;
        DISCRETE_INPUT_START = 0;
        DISCRETE_INPUT_NDISCRETES = *nregDesc;
        usDiscreteInputStart = 0;

        /* it already plus one in modbus function method. */
        usAddress--;

        if ((usAddress >= DISCRETE_INPUT_START)
                && (usAddress + usNDiscrete <= DISCRETE_INPUT_START + DISCRETE_INPUT_NDISCRETES))
        {
            iRegIndex = (USHORT) (usAddress - usDiscreteInputStart) / 8;
            iRegBitIndex = (USHORT) (usAddress - usDiscreteInputStart) % 8;

            while (iNReg > 0)
            {
                *pucRegBuffer++ = xMBUtilGetBits (&pucDiscreteInputBuf[iRegIndex++], iRegBitIndex, 8);
                iNReg--;
            }
            pucRegBuffer--;
            /* last discrete */
            usNDiscrete = usNDiscrete % 8;
            /* filling zero to high bit */
            *pucRegBuffer = *pucRegBuffer << (8 - usNDiscrete);
            *pucRegBuffer = *pucRegBuffer >> (8 - usNDiscrete);
        }
        else
        {
            eStatus = MB_ENOREG;
        }

        return eStatus;
    }
    else
        return MB_ENOREG;
}
/**
 *
 * @param _cb_func
 * @param _arg
 */
void sm_modbus_set_cb(mb_func_cb_t _cb_func, void *_arg)
{
    mb_callback = _cb_func;
    arg = _arg;
}

#endif
