/*
 * mqtt_app.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Admin
 */

#include "mqtt_app.h"
#include <sm_device_shadown.h>
#if USING_MQTT
#include "sm_ec200s.h"
#include "hal_data.h"
#include "sm_porting.h"

#include "app/hmi/hmi_app.h"

extern hmi_app_t hmi_app;

// Example MQTT Client using EC200N

/*define mqtt client funtion*/
static sm_mqtt_client_error_t mqtt_open(sm_mqtt_client_t *client, char *host, uint32_t port);
static sm_mqtt_client_error_t mqtt_close(sm_mqtt_client_t *client);
static sm_mqtt_client_error_t mqtt_connect(sm_mqtt_client_t *client, char *name, char *user, char *pass);
static sm_mqtt_client_error_t mqtt_disconnect(sm_mqtt_client_t *client);
static sm_mqtt_client_error_t mqtt_publics(sm_mqtt_client_t *client, const char *topic, const char *data, uint32_t len,
        uint8_t qos, uint8_t retain);
static sm_mqtt_client_error_t mqtt_subscribes(sm_mqtt_client_t *client, const char *topic, uint8_t qos);
static sm_mqtt_client_error_t mqtt_unsubscribes(sm_mqtt_client_t *client, const char *topic);
static sm_mqtt_client_error_t mqtt_data_iscomming(sm_mqtt_client_t *client, char *topic, char *data);
static sm_mqtt_client_error_t mqtt_reconnect(sm_mqtt_client_t *client);
/*end define mqtt client funtion*/

/*define variable*/

#define BUFF_LENGTH 1024
sm_ec200s_t ec200s;

char topic_mqtt[128];
char data_mqtt[BUFF_LENGTH];
char out_buff[BUFF_LENGTH];

sm_mqtt_client_proc_t client_proc =
{ .open = mqtt_open, .close = mqtt_close, .connect = mqtt_connect, .disconnect = mqtt_disconnect, .publics =
          mqtt_publics,
  .subscribes = mqtt_subscribes, .unsubscribes = mqtt_unsubscribes, .data_iscomming = mqtt_data_iscomming, .reconnect =
          mqtt_reconnect };

static void iot_get_accepted(sm_iot_device_t *client);
static void iot_get_rejected(sm_iot_device_t *client);
static void iot_update(sm_iot_device_t *client);
static void iot_update_accepted(sm_iot_device_t *client);
static void iot_update_rejected(sm_iot_device_t *client);
static void iot_delete_updated(sm_iot_device_t *client);
static void iot_delete_rejected(sm_iot_device_t *client);
static void iot_disconnected(sm_iot_device_t *client);
sm_device_shadown_func_callback_t iot_callback =
{ .get_accepted = iot_get_accepted,
  .get_rejected = iot_get_rejected,
  .update = iot_update,
  .update_accepted = iot_update_accepted,
  .update_rejected = iot_update_rejected,
  .delete_updated = iot_delete_updated,
  .delete_rejected = iot_delete_rejected,
  .disconnected = iot_disconnected };
/*end define variable*/
void iot_client_init()
{
    sm_ec200s_init (&hmi_app.ec200s, hmi_app.board.lte.lte_en, hmi_app.board.lte.lte_uart);
    sm_ec200s_set_apn (&hmi_app.ec200s, "m3-world", "mms", "mms");
    sm_ec200s_get_ip (&hmi_app.ec200s);
    hmi_app.mqtt_client = sm_mqtt_client_init (&client_proc, (void*) &hmi_app.ec200s, "hub.dev.selex.vn", 1883, NULL,
    NULL,
                                               NULL);
    hmi_app.mqtt_client->topic = topic_mqtt;
    hmi_app.mqtt_client->data = data_mqtt;
    sm_iot_init (&hmi_app.iot_client, hmi_app.mqtt_client, "CM003", "EV", &iot_callback);
    sm_iot_device_add (&hmi_app.iot_client, "101BE1N00034", "BATTERRY", &iot_callback);
    sm_iot_device_add (&hmi_app.iot_client, "101BE1N00035", "BATTERRY", &iot_callback);
    sm_iot_device_add (&hmi_app.iot_client, "101BE1N00033", "BATTERRY", &iot_callback);
    sm_iot_device_remove (&hmi_app.iot_client, "101BE1N00035");
    sm_iot_device_add (&hmi_app.iot_client, "101BE1N00036", "BATTERRY", &iot_callback);
}
void iot_client_process()
{
    sm_mqtt_client_process (hmi_app.mqtt_client);
    sm_iot_device_connect (&hmi_app.iot_client, "CM003");
    sm_iot_device_connect (&hmi_app.iot_client, "101BE1N00034");

    if (sm_mqtt_client_get_state (hmi_app.mqtt_client) == MQTT_ST_CLOSED)
    {
        sm_mqtt_client_set_state (hmi_app.mqtt_client, MQTT_ST_OPEN);
    }
}
static sm_mqtt_client_error_t mqtt_open(sm_mqtt_client_t *client, char *host, uint32_t port)
{
    sm_ec200s_t *p_ec = (sm_ec200s_t*) client->arg;
    return sm_ec200s_open_mqtt (p_ec, host, port);
}
static sm_mqtt_client_error_t mqtt_close(sm_mqtt_client_t *client)
{
    sm_ec200s_t *p_ec = (sm_ec200s_t*) client->arg;
    return sm_ec200s_close_mqtt (p_ec);
}
static sm_mqtt_client_error_t mqtt_connect(sm_mqtt_client_t *client, char *name, char *user, char *pass)
{
    sm_ec200s_t *p_ec = (sm_ec200s_t*) client->arg;
    return sm_ec200s_connect_mqtt (p_ec, name, user, pass);
}
static sm_mqtt_client_error_t mqtt_disconnect(sm_mqtt_client_t *client)
{
    sm_ec200s_t *p_ec = (sm_ec200s_t*) client->arg;
    return sm_ec200s_disconnect_mqtt (p_ec);
}
static sm_mqtt_client_error_t mqtt_publics(sm_mqtt_client_t *client, const char *topic, const char *data, uint32_t len,
        uint8_t qos, uint8_t retain)
{
    sm_ec200s_t *p_ec = (sm_ec200s_t*) client->arg;
    return sm_ec200s_public_mqtt (p_ec, (char*) topic, (char*) data, len, qos, retain);
}
static sm_mqtt_client_error_t mqtt_subscribes(sm_mqtt_client_t *client, const char *topic, uint8_t qos)
{
    sm_ec200s_t *p_ec = (sm_ec200s_t*) client->arg;
    return sm_ec200s_subscribes_mqtt (p_ec, (char*) topic, qos);
}
static sm_mqtt_client_error_t mqtt_unsubscribes(sm_mqtt_client_t *client, const char *topic)
{
    sm_ec200s_t *p_ec = (sm_ec200s_t*) client->arg;
    return sm_ec200s_unsubscribes_mqtt (p_ec, (char*) topic);
}
static sm_mqtt_client_error_t mqtt_data_iscomming(sm_mqtt_client_t *client, char *topic, char *data)
{
    sm_ec200s_t *p_ec = (sm_ec200s_t*) client->arg;
    return sm_ec200s_data_iscomming_mqtt (p_ec, topic, data);
}
static sm_mqtt_client_error_t mqtt_reconnect(sm_mqtt_client_t *client)
{
    (void) client;
    sm_ec200s_init (&hmi_app.ec200s, hmi_app.board.lte.lte_en, hmi_app.board.lte.lte_uart);
    return sm_ec200s_set_apn (&hmi_app.ec200s, "m3-world", "mms", "mms");
}
static void iot_get_accepted(sm_iot_device_t *client)
{

    /*USER CODE*/
    printf (client->data);
    printf ("\r\n");
    /*END USER CODE*/
}
static void iot_get_rejected(sm_iot_device_t *client)
{

    /*USER CODE*/
    printf (client->data);
    printf ("\r\n");
    /*END USER CODE*/
}
static void iot_update(sm_iot_device_t *client)
{

    /*USER CODE*/
    printf (client->data);
    printf ("\r\n");
    /*END USER CODE*/
}
static void iot_update_accepted(sm_iot_device_t *client)
{
    /*USER CODE*/
    printf (client->data);
    printf ("\r\n");
    /*END USER CODE*/
}
static void iot_update_rejected(sm_iot_device_t *client)
{
    /*USER CODE*/
    printf (client->data);
    printf ("\r\n");
    /*END USER CODE*/
}
static void iot_delete_updated(sm_iot_device_t *client)
{
    /*USER CODE*/
    printf (client->data);
    printf ("\r\n");
    /*END USER CODE*/
}
static void iot_delete_rejected(sm_iot_device_t *client)
{
    /*USER CODE*/
    printf (client->data);
    printf ("\r\n");
    /*END USER CODE*/
}
static void iot_disconnected(sm_iot_device_t *client)
{
    sprintf (out_buff, "Disconnected\r\nReconnect...\n");
    printf (client->data);
    printf ("\r\n");
}
#endif
