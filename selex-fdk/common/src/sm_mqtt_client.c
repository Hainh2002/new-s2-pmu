#include <sm_fifo.h>
#include "sm_mqtt_client.h"
#include "sm_modem.h"
#include <stdio.h>

#if USING_MQTT

#define MAX_HANDLE 10

sm_mqtt_client_event_handle mqtt_list_handle[MAX_HANDLE] = {NULL};


typedef struct sm_mqtt_client_impl sm_mqtt_client_impl_t;

struct sm_mqtt_client_impl
{
    /* data */
    sm_mqtt_client_t base;
    sm_fifo_handle_t event;
	sm_mqtt_client_st_t state;
};
/**
 *
 * @param p_mqtt
 * @param state
 */
void sm_mqtt_client_set_state(sm_mqtt_client_t *p_mqtt,
		sm_mqtt_client_st_t state) {
	sm_mqtt_client_impl_t *parent = (sm_mqtt_client_impl_t*) p_mqtt;
	parent->state = state;
}
/**
 *
 * @param p_mqtt
 * @return
 */
sm_mqtt_client_st_t sm_mqtt_client_get_state(
		sm_mqtt_client_t *p_mqtt) {
	sm_mqtt_client_impl_t *parent = (sm_mqtt_client_impl_t*) p_mqtt;
	return parent->state;
}
/**
 *
 * @param p_mqtt
 * @param event
 */
static inline void mqtt_client_set_event(sm_mqtt_client_impl_t *p_mqtt, sm_mqtt_client_event_t event)
{
    sm_fifo_push(&p_mqtt->event, (void *)&event);
}
/**
 *
 * @param p_mqtt
 * @return
 */
static inline sm_mqtt_client_event_t mqtt_client_get_event(sm_mqtt_client_impl_t *p_mqtt)
{
    sm_mqtt_client_event_t event = MQTT_EVENT_NONE;
    sm_fifo_pop(&p_mqtt->event, (void *)&event);
    return event;
}
/**
 *
 * @param m_proc
 * @param arg
 * @param host
 * @param port
 * @param user
 * @param pass
 * @return
 */
sm_mqtt_client_t *sm_mqtt_client_init(sm_mqtt_client_proc_t *m_proc, void *arg, char *host, uint32_t port, char *user, char *pass)
{
    sm_mqtt_client_impl_t *client = (sm_mqtt_client_impl_t *)malloc(sizeof(sm_mqtt_client_impl_t));

    client->base.arg = arg;
    client->base.event_handle = NULL;
    client->base.num_handle = 0;
    client->base.m_proc = m_proc;
    client->base.host = host;
    client->base.port = port;
    client->base.username = user;
    client->base.pass = pass;
    client->base.num_handle = 0;
    sm_fifo_init(&client->event, 10, sizeof(sm_mqtt_client_event_t));
    sm_mqtt_client_set_state (&client->base, MQTT_ST_OPEN);
    return &client->base;
}
/**
 *
 * @param client
 */
void sm_mqtt_client_deinit(sm_mqtt_client_t *client)
{
    sm_mqtt_client_impl_t *parent = (sm_mqtt_client_impl_t *)client;

    free(parent);
}
/**
 *
 * @param client
 * @param handle
 */
void sm_mqtt_client_register_handle(sm_mqtt_client_t *client,sm_mqtt_client_event_handle handle){
	if(client->num_handle < MAX_HANDLE){
		mqtt_list_handle[client->num_handle] = handle;
		client->num_handle++;
	}
	return;
}
/**
 *
 * @param client
 * @param handle
 */
void sm_mqtt_client_unregister_handle(sm_mqtt_client_t *client,sm_mqtt_client_event_handle handle){
	uint32_t i = 0;

	for(i = 0;i<client->num_handle;i++){
		if(mqtt_list_handle[i] == handle){
			mqtt_list_handle[i] = NULL;

		}
	}
	if(i == client->num_handle) {
		client->num_handle--;
		return;
	}

	for(uint32_t j = i;j<client->num_handle;j++){
		mqtt_list_handle[j] = mqtt_list_handle[j+1];
	}
	client->num_handle--;
	return;
}
/**
 *
 * @param client
 */
void sm_mqtt_client_process(sm_mqtt_client_t *client)
{
    sm_mqtt_client_impl_t *parent = (sm_mqtt_client_impl_t *)client;
	int result = -1;
    switch (sm_mqtt_client_get_state (client))
    {
    case MQTT_ST_CONNECT:
        /* code */
        if(client->m_proc->connect(client,"selex_device",client->username,client->pass) == MQTT_ERROR_NO){
                sm_mqtt_client_set_state (client, MQTT_ST_CONNECTED);
			mqtt_client_set_event(parent, MQTT_EVENT_CONNECTED);
        }
        else{
                sm_mqtt_client_set_state (client, MQTT_ST_DISCONNECT);
        }
        break;
    case MQTT_ST_CONNECTED:
        /* code */
		result = client->m_proc->data_iscomming(client, client->topic,
				client->data);
		if (result == 0) {
            mqtt_client_set_event(parent,MQTT_EVENT_DATA);
        }
		else if (result == -2) {
                sm_mqtt_client_set_state (client, MQTT_ST_DISCONNECT);
		}

		else if(result == 2){
		}

        break;
    case MQTT_ST_DISCONNECT:
        /* code */
        mqtt_client_set_event(parent, MQTT_EVENT_DISCONNECED);
        client->m_proc->disconnect(client);
            sm_mqtt_client_set_state (client, MQTT_ST_CLOSE);
        break;
    case MQTT_ST_OPEN:
        /* code */
        if(client->m_proc->open(client,client->host,client->port) == MQTT_ERROR_NO){
            mqtt_client_set_event(parent,MQTT_EVENT_OPEN);
                sm_mqtt_client_set_state (client, MQTT_ST_CONNECT);
        }
        break;
    case MQTT_ST_CLOSE:
        /* code */
        client->m_proc->close(client);
            sm_mqtt_client_set_state (client, MQTT_ST_CLOSED);
        mqtt_client_set_event(parent,MQTT_EVENT_CLOSE);
        break;
	case MQTT_ST_CLOSED:
		break;
    default:
        break;
    }

    sm_mqtt_client_event_t event = mqtt_client_get_event(parent);
    for(uint32_t i = 0;i<client->num_handle;i++){
    	client->event_handle = mqtt_list_handle[i];
        if(client->event_handle != NULL)
            client->event_handle(client,event);
    }

}
#endif
