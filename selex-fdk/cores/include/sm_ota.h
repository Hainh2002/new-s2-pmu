/*
 * sm_ota.h
 *
 *  Created on: Sep 9, 2023
 *      Author: MinhNhan
 */

#ifndef CORES_INCLUDE_SM_OTA_H_
#define CORES_INCLUDE_SM_OTA_H_

#include "sm_mqtt_client.h"

#define ota_ping_request 		"ota/%s/%s/%s/ping_request"
#define ota_ping_response 		"ota/%s/%s/%s/ping_response"
#define ota_fw_info_request 	"ota/%s/%s/%s/fw_info"
#define ota_fw_info_response 	"ota/%s/%s/%s/fw_info_response"
#define ota_downloading 		"ota/%s/%s/%s/downloading"
#define ota_download_status		"ota/%s/%s/%s/download_status"
#define ota_upgrading_status	"ota/%s/%s/%s/upgrading_status"

#define TOPIC_LENGTH 68

#define BSS_TYPE "bss"
#define VEHICAL_TYPE "ev"
#define BATTERY_TYPE "bp"

#define BSS_DEVICE "bss"
#define VEHICAL_DEVICE "s2"
#define BP_DEVICE "bpt1"

typedef sm_mqtt_client_event_handle sm_ota_callback ;

typedef struct sm_ota sm_ota_t;

struct sm_ota {
	sm_mqtt_client_t *base;
	sm_mqtt_client_event_handle handle;
	char *type;
	char *device;
	char *name;
	char sub_ping[TOPIC_LENGTH];
	char pub_ping[TOPIC_LENGTH];
	char sub_fw[TOPIC_LENGTH];
	char pub_fw[TOPIC_LENGTH];
	char pub_downloading[TOPIC_LENGTH];
	char pub_download_status[TOPIC_LENGTH];
	char pub_upgrading_status[TOPIC_LENGTH];
};
/**
 * @brief
 * @param ota
 * @param client
 * @param type
 * @param device
 * @param name
 */
void sm_ota_device_init(sm_ota_t *ota, sm_mqtt_client_t *client, char *type,
		char *device, char *name);
/**
 * @brief
 * @param ota
 * @param handle
 */
void sm_ota_set_callback(sm_ota_t *ota,sm_ota_callback handle);
/**
 * @brief
 * @param ota
 */
void sm_ota_device_deinit(sm_ota_t *ota);
/**
 * @brief
 * @param ota
 * @param type
 * @param device
 * @param name
 */
void sm_ota_change_device(sm_ota_t *ota, char *type, char *device, char *name);
/**
 * @brief
 * @param ota
 */
void sm_ota_connect(sm_ota_t *ota);
/**
 * @brief
 * @param ota
 */
void sm_ota_disconnect(sm_ota_t *ota);

#endif /* CORES_INCLUDE_SM_OTA_H_ */
