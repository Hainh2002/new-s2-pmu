/*
 * ota_test.c
 *
 *  Created on: Sep 9, 2023
 *      Author: MinhNhan
 */

#include "sm_ota.h"


sm_mqtt_client_t *client;
sm_mqtt_client_proc_t mqtt_func;
sm_ota_t ota;

static void mqtt_event(sm_mqtt_client_t *client, sm_mqtt_client_event_t event);

void main(){
	client = sm_mqtt_client_init(&mqtt_func, NULL,"hub.dev.selex.vn", 1883,NULL,NULL);
	sm_ota_device_init(&ota, client, VEHICAL_TYPE, VEHICAL_DEVICE,"CM003");
	sm_ota_set_callback(&ota, mqtt_event);
	while(1){
		sm_mqtt_client_process(client);
	}
}

static void mqtt_event(sm_mqtt_client_t *client, sm_mqtt_client_event_t event) {
	sm_device_shadown_t *p_iot = (sm_device_shadown_t*) client->parent;
	switch (event) {
	case MQTT_EVENT_NONE:
		/* User code */
		break;
	case MQTT_EVENT_CLOSE:
		/* User code */

		break;
	case MQTT_EVENT_CONNECTED:
		/* User code */
		sm_ota_connect(&ota);
		break;
	case MQTT_EVENT_DATA:
		/* User code */
//            printf("Topic: %s\r\n",client->topic);
//            printf("Data: %s\r\n",client->data);jk.
		break;
	case MQTT_EVENT_DISCONNECED:
		/* User code */
		break;
	case MQTT_EVENT_ERROR:
		/* User code */
		break;
	case MQTT_EVENT_OPEN:
		/* User code */
		break;
	default:
		break;
	}
}
