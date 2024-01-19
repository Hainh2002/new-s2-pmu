/*
 * sm_ota.c
 *
 *  Created on: Sep 9, 2023
 *      Author: MinhNhan
 */

#include "sm_ota.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 *
 * @param ota
 * @param client
 * @param type
 * @param device
 * @param name
 */
void sm_ota_device_init(sm_ota_t *ota, sm_mqtt_client_t *client, char *type,
		char *device, char *name) {
	ota->base = client;
	ota->device = device;
	ota->type = type;
	ota->name = name;
	memset(ota->sub_ping,0,TOPIC_LENGTH);
	memset(ota->pub_ping,0,TOPIC_LENGTH);
	memset(ota->sub_fw,0,TOPIC_LENGTH);
	memset(ota->pub_fw,0,TOPIC_LENGTH);

	memset(ota->pub_downloading,0,TOPIC_LENGTH);
	memset(ota->pub_download_status,0,TOPIC_LENGTH);
	memset(ota->pub_upgrading_status,0,TOPIC_LENGTH);

	sprintf(ota->sub_ping,ota_ping_request,type,device,ota->name);
//	printf("topic: %s\n",ota->sub_ping);
	sprintf(ota->pub_ping,ota_ping_response,type,device,ota->name);
//	printf("topic: %s\n",ota->pub_ping);
	sprintf(ota->sub_fw,ota_fw_info_request,type,device,ota->name);
//	printf("topic: %s\n",ota->sub_fw);
	sprintf(ota->pub_fw,ota_fw_info_response,type,device,ota->name);
//	printf("topic: %s\n",ota->pub_fw);
	sprintf(ota->pub_downloading,ota_downloading,type,device,ota->name);
//	printf("topic: %s\n",ota->pub_downloading);
	sprintf(ota->pub_download_status,ota_download_status,type,device,ota->name);
//	printf("topic: %s\n",ota->pub_download_status);
	sprintf(ota->pub_upgrading_status,ota_upgrading_status,type,device,ota->name);


//	printf("topic: %s\n",ota->pub_upgrading_status);
}
/**
 *
 * @param ota
 * @param handle
 */
void sm_ota_set_callback(sm_ota_t *ota,sm_ota_callback handle){
	sm_mqtt_client_register_handle(ota->base, handle);
}
/**
 *
 * @param ota
 */
void sm_ota_device_deinit(sm_ota_t *ota) {
	sm_ota_disconnect(ota);
	ota->base = NULL;
	ota->device = NULL;
	ota->type = NULL;
	ota->name = NULL;
	memset(ota->sub_ping,0,TOPIC_LENGTH);
	memset(ota->pub_ping,0,TOPIC_LENGTH);
	memset(ota->sub_fw,0,TOPIC_LENGTH);
	memset(ota->pub_fw,0,TOPIC_LENGTH);
	memset(ota->pub_downloading,0,TOPIC_LENGTH);
	memset(ota->pub_download_status,0,TOPIC_LENGTH);
	memset(ota->pub_upgrading_status,0,TOPIC_LENGTH);
	sm_mqtt_client_unregister_handle(ota->base, ota->handle);
}
/**
 *
 * @param ota
 * @param type
 * @param device
 * @param name
 */
void sm_ota_change_device(sm_ota_t *ota, char *type, char *device, char *name) {
	ota->device = device;
	ota->type = type;
	ota->name = name;
}
/**
 *
 * @param ota
 */
void sm_ota_connect(sm_ota_t *ota) {
//	sm_mqtt_subscribes(ota->base,ota->sub_download,1);
	sm_mqtt_subscribes(ota->base,ota->sub_fw,1);
	sm_mqtt_subscribes(ota->base,ota->sub_ping,1);
}
/**
 *
 * @param ota
 */
void sm_ota_disconnect(sm_ota_t *ota) {
//	sm_mqtt_unsubscribes(ota->base,ota->sub_download);
	sm_mqtt_unsubscribes(ota->base,ota->sub_fw);
	sm_mqtt_unsubscribes(ota->base,ota->sub_ping);
}
