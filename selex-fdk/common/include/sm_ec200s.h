#ifndef COMMON_EC200S_SM_EC200S_H_
#define COMMON_EC200S_SM_EC200S_H_

#include "sm_modem.h"
#include "sm_config.h"
#include <stdbool.h>

#if USING_MODEM
typedef struct sm_ec200s sm_ec200s_t;

struct sm_ec200s
{
    sm_modem_t base;
    int rssi;
    int ber;
    int ip[4];
    char IMSI[20];
    char simNb[8];
    char name[20];
/* data */
};
/**
 * @brief
 * @param modem
 * @param reset_pin
 * @param driver
 */
void sm_ec200s_init(sm_ec200s_t *modem, sm_hal_io_t *reset_pin, sm_hal_uart_t *driver);
/**
 * @brief
 * @param modem
 */
void sm_ec200s_deinit(sm_ec200s_t *modem);
/**
 * @brief
 * @param modem
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_sync(sm_ec200s_t *modem);
/**
 * @brief
 * @param modem
 * @param mode
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_echo_mode(sm_ec200s_t *modem, uint8_t mode); // mode = 0 : disable echo mode, mode = 1 : enable echo mode
/**
 * @brief
 * @param modem
 * @param pin
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_set_pin(sm_ec200s_t *modem, char *pin);
/**
 * @brief
 * @param modem
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_get_pin(sm_ec200s_t *modem);
/**
 * @brief
 * @param modem
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_get_signal(sm_ec200s_t *modem);
/**
 * @brief
 * @param modem
 * @param name
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_get_name(sm_ec200s_t *modem, char *name);
/**
 * @brief
 * @param modem
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_get_funtion(sm_ec200s_t *modem);
/**
 * @brief
 * @param modem
 * @param apn
 * @param user
 * @param pass
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_set_apn(sm_ec200s_t *modem, char *apn, char *user, char *pass);
/**
 * @brief
 * @param modem
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_get_network_reg(sm_ec200s_t *modem);
/**
 * @brief
 * @param modem
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_get_simNb(sm_ec200s_t *modem);
/**
 * @brief
 * @param modem
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_get_ip(sm_ec200s_t *modem);
// MQTT
/**
 * @brief
 * @param modem
 * @param host
 * @param port
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_open_mqtt(sm_ec200s_t *modem, char *host, uint32_t port);
/**
 * @brief
 * @param modem
 * @param device_name
 * @param user
 * @param pass
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_connect_mqtt(sm_ec200s_t *modem, char *device_name, char *user, char *pass);
/**
 * @brief
 * @param modem
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_disconnect_mqtt(sm_ec200s_t *modem);
/**
 * @brief
 * @param modem
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_close_mqtt(sm_ec200s_t *modem);
/**
 * @brief
 * @param modem
 * @param topic
 * @param qos
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_subscribes_mqtt(sm_ec200s_t *modem,char* topic,int qos);
/**
 * @brief
 * @param modem
 * @param topic
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_unsubscribes_mqtt(sm_ec200s_t *modem,char* topic);
/**
 * @brief
 * @param modem
 * @param topic
 * @param data
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_data_iscomming_mqtt(sm_ec200s_t *modem,char *topic,char* data);
/**
 * @brief
 * @param modem
 * @param topic
 * @param data
 * @param len
 * @param qos
 * @param retain
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_public_mqtt(sm_ec200s_t *modem, char *topic, char *data, uint32_t len, int qos, int retain);
/**
 * @brief
 * @param modem
 * @param topic
 * @param qos
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_subscribes_mqtt(sm_ec200s_t *modem, char *topic, int qos);
/**
 * @brief
 * @param modem
 * @param topic
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_unsubscribes_mqtt(sm_ec200s_t *modem, char *topic);
/**
 * @brief
 * @param modem
 * @param topic
 * @param data
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_data_iscomming_mqtt(sm_ec200s_t *modem, char *topic, char *data);
/**
 * @brief
 * @param modem
 * @param host
 * @param port
 * @return  0: success | -1 : false
 */

//HTTP
//int32_t sm_ec200s_set_http_url(sm_ec200s_t *modem, char *url);
int32_t sm_ec200_http_open(sm_ec200s_t *modem, char *host, int port);
/**
 * @brief
 * @param modem
 * @return  0: success | -1 : false
 */
int32_t sm_ec200_http_close(sm_ec200s_t *modem);
/**
 * @brief
 * @param modem
 * @param data
 * @param len
 * @return  0: success | -1 : false
 */
int32_t sm_ec200_http_write(sm_ec200s_t *modem, char *data, uint32_t len);
/**
 * @brief
 * @param modem
 * @param paramater
 * @param value
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_http_config(sm_ec200s_t* modem, const char* paramater, int value);
/**
 * @brief
 * @param modem
 * @param start
 * @param range
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_http_get_range(sm_ec200s_t* modem,int start, int range);
/**
 * @brief
 * @param modem
 * @param url
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_set_http_url(sm_ec200s_t *modem, char *url);
/**
 * @brief
 * @param modem
 * @param data
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_data_iscomming_http(sm_ec200s_t* modem, char* data);
/**
 * @brief
 * @param modem
 * @param data
 * @return  0: success | -1 : false
 */
int32_t sm_ec200s_http_read(sm_ec200s_t *modem, char *data);

#endif
#endif
