/*
 * modbus_app.h
 *
 *  Created on: Jul 8, 2023
 *      Author: Admin
 */

#ifndef APP_MODBUS_APP_MODBUS_APP_H_
#define APP_MODBUS_APP_MODBUS_APP_H_

#include "modbus/sm_modbus.h"
#include "config/sm_config.h"

#if USING_MODBUS
void modbus_app_init();
void modbus_app_process();
#endif
#endif /* APP_MODBUS_APP_MODBUS_APP_H_ */
