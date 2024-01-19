/*
 * mqtt_app.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Admin
 */

#ifndef APP_MQTT_APP_H_
#define APP_MQTT_APP_H_

#include "sm_mqtt_client.h"
#if USING_MQTT
void iot_client_init();
void iot_client_process();
#endif
#endif /* APP_MQTT_APP_H_ */
