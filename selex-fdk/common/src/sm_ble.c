/*
 * sm_ble.c
 *
 *  Created on: Jul 22, 2023
 *      Author: Admin
 */


#include "sm_ble.h"
#include "cJSON.h"
sm_ble_t* sm_ble_init(char *name, sm_hal_uart_t *driver, sm_hal_io_t *reset_pin, sm_hal_io_t *indicator)
{
    sm_ble_t *_this = (sm_ble_t*) malloc (sizeof(sm_ble_t));
    sm_modem_init (&_this->base, reset_pin, driver);
    _this->indicator = indicator;
    sm_modem_hw_reset (&_this->base, 1000, 1);
//    char buff_out[128];
//    sprintf (buff_out, "AT+NAME%s\r\n", name);
//    if (sm_modem_send_cmd (&_this->base, buff_out, name, "ERROR", 1000) != 0)
//    {
//        sm_modem_deinit (&_this->base);
//        free (_this);
//        return NULL;
//    }
    strcpy (_this->name, name);
    sm_ble_set_state (_this, SM_BLE_ST_IDLE);
    _this->cmd_process = NULL;
    return _this;
}
/**
 *
 * @param ble
 */
void sm_ble_keygen(sm_ble_t *ble)
{
    for (uint16_t i = 0; i < 6; i++)
    {
        ble->key[i] = (uint8_t) (rand () % 10 + 1);
    }
}
/**
 *
 * @param ble
 */
void sm_ble_process(sm_ble_t *ble)
{

    if (ble->indicator != NULL)
    {
        uint8_t connect_status = sm_hal_io_get_value (ble->indicator);

        if (connect_status == 1 && sm_ble_get_state (ble) != SM_BLE_ST_IDLE)
        {
            sm_ble_set_state (ble, SM_BLE_ST_DISCONNECT);
        }
    }
    switch (ble->state)
    {
        case SM_BLE_ST_IDLE:

        break;
        case SM_BLE_ST_CONNECTED:

        break;
        case SM_BLE_ST_DISCONNECT:
            sm_ble_set_state (ble, SM_BLE_ST_IDLE);
        break;
        default:
        break;
    }

    if (ble->cmd_process != NULL)
    {
        ble->cmd_process (ble);
    }

}
