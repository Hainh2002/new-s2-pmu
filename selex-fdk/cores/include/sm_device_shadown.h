/*
 * iot_sevice.h
 *
 *  Created on: Jul 17, 2023
 *      Author: Admin
 */

#ifndef CORES_IOT_SERVICE_SM_DEVICE_SHADOWN_H_
#define CORES_IOT_SERVICE_SM_DEVICE_SHADOWN_H_

#include <sm_mqtt_client.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#if USING_MQTT

typedef struct sm_device_arg{
   char* topic;
   char* data;
}sm_device_arg_t;

typedef struct sm_device_shadown sm_device_shadown_t;

typedef struct sm_iot_device sm_iot_device_t;

typedef struct sm_iot_topic sm_iot_topic_t;

typedef enum{
    SM_DS_EVENT_GET_ACCEPTED = 0,
    SM_DS_EVENT_GET_REJECTED,
    SM_DS_EVENT_UPDATE_DELTA,
    SM_DS_EVENT_UPDATE_ACCEPTED,
    SM_DS_EVENT_UPDATE_REJECTED,
    SM_DS_EVENT_DELETE_UPDATED,
    SM_DS_EVENT_DELETE_REJECTED
}sm_device_shadown_event_t;

typedef struct{
    void (*get_accepted)(sm_iot_device_t *client);
    void (*get_rejected)(sm_iot_device_t *client);
    void (*update)(sm_iot_device_t *client);
    void (*update_accepted)(sm_iot_device_t *client);
    void (*update_rejected)(sm_iot_device_t *client);
    void (*delete_updated)(sm_iot_device_t *client);
    void (*delete_rejected)(sm_iot_device_t *client);
    void (*connected)(sm_iot_device_t *client);
    void (*disconnected)(sm_iot_device_t *client);
}sm_device_shadown_func_callback_t;

struct sm_iot_topic
{
    char get_topic[100];                    // Public
    char get_accepted_topic[100];           // Sub
    char get_rejected_topic[100];           // Sub
    char update_topic[100];                 // Public
    char update_delta_topic[100];           // Sub
    char update_accepted_topic[100];        // Sub
    char update_rejected_topic[100];        // Sub
    char delete_topic[100];                 // Public
    char delete_update_topic[100];          // Sub
    char delete_rejected_topic[100];        // Sub

    // OTA


};

struct sm_iot_device
{
    sm_device_shadown_func_callback_t *callback;
    char name[20];
    char type[20];
    sm_iot_topic_t topic;
    char *data;
    sm_iot_device_t *next;
    bool connected;
};


struct sm_device_shadown{
    sm_mqtt_client_t *base;
    sm_iot_device_t *device;
};

/**
 * @brief
 * @param client
 * @param mqtt_client
 * @param name
 * @param type
 * @param iot_device_callback
 * @return  0: success | -1 : false
 */
int32_t sm_iot_init(sm_device_shadown_t *client, sm_mqtt_client_t *mqtt_client, char *name, char *type,
        sm_device_shadown_func_callback_t *iot_device_callback);
/**
 * @brief
 * @param client
 * @param name
 * @param type
 * @param iot_device_callback
 * @return  0: success | -1 : false
 */
int32_t sm_iot_device_add(sm_device_shadown_t *client, char *name, char *type,
        sm_device_shadown_func_callback_t *iot_device_callback);
/**
 * @brief
 * @param client
 * @param name
 * @return  0: success | -1 : false
 */
int32_t sm_iot_device_remove(sm_device_shadown_t *client, char *name);
/**
 * @brief
 * @param client
 * @return  0: success | -1 : false
 */
int32_t sm_iot_device_delete_all(sm_device_shadown_t *client);
/**
 * @brief
 * @param client
 * @param name
 * @return  0: success | -1 : false
 */
int32_t sm_iot_device_connect(sm_device_shadown_t *client, char *name);
/**
 * @brief
 * @param client
 * @param name
 * @return  0: success | -1 : false
 */
int32_t sm_iot_device_disconnect(sm_device_shadown_t *client, char *name);
/**
 * @brief
 * @param client
 * @param name
 * @return  0: success | -1 : false
 */
sm_iot_device_t* sm_iot_device_search(sm_device_shadown_t *client, char *name);
/**
 * @brief
 * @param client
 * @return  0: success | -1 : false
 */
int32_t sm_iot_process(sm_device_shadown_t *client);
/**
 * @brief
 * @param client
 * @param device_name
 * @param stream
 * @return  0: success | -1 : false
 */
int32_t sm_iot_get(sm_device_shadown_t *client, char *device_name, void *stream);
/**
 * @brief
 * @param client
 * @param device_name
 * @param stream
 * @return  0: success | -1 : false
 */
int32_t sm_iot_update(sm_device_shadown_t *client, char *device_name, void *stream);
/**
 * @brief
 * @param client
 * @param device_name
 * @return  0: success | -1 : false
 */
int32_t sm_iot_delete(sm_device_shadown_t *client, char *device_name);
/**
 * @brief
 * @param client
 * @return  0: success | -1 : false
 */
int32_t sm_iot_deinit(sm_device_shadown_t *client);
/**
 * @brief
 * @param client
 * @param device_name
 * @return true | false
 */
bool sm_iot_device_get_connected(sm_device_shadown_t *client, char *device_name);


#endif
#endif /* CORES_IOT_SERVICE_SM_DEVICE_SHADOWN_H_ */
