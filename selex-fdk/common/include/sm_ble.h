/*
 * sm_ble.h
 *
 *  Created on: Jul 22, 2023
 *      Author: Admin
 */

#ifndef COMMON_INCLUDE_SM_BLE_H_
#define COMMON_INCLUDE_SM_BLE_H_

#include "sm_modem.h"

#define BLE_HEAD '+'
#define BLE_END  '*'

typedef enum
{
    SM_BLE_ST_IDLE = 0, SM_BLE_ST_CONNECTED, SM_BLE_ST_DISCONNECT,
} sm_ble_state_t;

typedef struct sm_ble sm_ble_t;

typedef void (*sm_ble_cmd_process)(sm_ble_t *_this);

struct sm_ble
{
    sm_modem_t base;
    sm_hal_io_t *indicator;
    uint8_t key[6];
    uint8_t mac[6];
    char name[16];
    sm_ble_state_t state;
    sm_ble_cmd_process cmd_process;
};
/**
 * @brief
 * @param name
 * @param driver
 * @param reset_pin
 * @param indicator
 * @return  0: success | NULL : false
 */
sm_ble_t* sm_ble_init(char *name, sm_hal_uart_t *driver, sm_hal_io_t *reset_pin, sm_hal_io_t *indicator);
/**
 * @brief
 * @param ble
 */
void sm_ble_keygen(sm_ble_t *ble);
/**
 * @brief
 * @param ble
 */
void sm_ble_process(sm_ble_t *ble);
/**
 * @brief
 * @param ble
 * @param str
 * @return  0: success | -1 : false
 */
static inline int32_t sm_ble_send(sm_ble_t *ble, char *str)
{
    return sm_modem_send_data ((sm_modem_t*) ble, str, strlen (str));
}
/**
 * @brief
 * @param ble
 * @param data
 * @param len
 * @return  0: success | -1 : false
 */
static inline size_t sm_ble_recv(sm_ble_t *ble, uint8_t *data, uint32_t len)
{
    return sm_modem_read ((sm_modem_t*) ble, (char*) data, len);
}
/**
 * @brief
 * @param ble
 * @param state
 */
static inline void sm_ble_set_state(sm_ble_t *ble, sm_ble_state_t state)
{
    ble->state = state;
}
/**
 * @brief
 * @param ble
 * @return  0: success | NULL : false
 */
static inline sm_ble_state_t sm_ble_get_state(sm_ble_t *ble)
{
    return ble->state;
}
/**
 * @brief
 * @param ble
 * @param cmd_process
 */
static inline void sm_ble_set_cmd_func(sm_ble_t *ble, sm_ble_cmd_process cmd_process)
{
    ble->cmd_process = cmd_process;
}

#endif /* COMMON_INCLUDE_SM_BLE_H_ */
