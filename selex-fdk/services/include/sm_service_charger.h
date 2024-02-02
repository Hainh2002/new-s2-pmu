/*
 * sm_charger_service.h
 *
 *  Created on: Jan 30, 2024
 *      Author: DELL 5425
 */

#ifndef SERVICES_INCLUDE_SM_SERVICE_CHARGER_H_
#define SERVICES_INCLUDE_SM_SERVICE_CHARGER_H_

#include <stdint.h>
#include "sm_bsp_peripherals.h"
#include "sm_bsp_io.h"

typedef enum {
	SM_SERVICE_CHARGER_STATE_IDLE = 0,
	SM_SERVICE_CHARGER_STATE_ACTIVE,
	SM_SERVICE_CHARGER_STATE_PROTECT_OVER_VOLTAGE,
	SM_SERVICE_CHARGER_STATE_PROTECT_OVER_CURRENT,
	SM_SERVICE_CHARGER_STATE_PROTECT_SHORT_CIRCUIT,
	SM_SERVICE_CHARGER_STATE_PROTECT_OVER_HEAT,
} sm_service_charger_state_t;

typedef enum {
	SM_SERVICE_CHARGER_EVENT_ST_IDLE = 0,
	SM_SERVICE_CHARGER_EVENT_ST_SUCCESS,
	SM_SERVICE_CHARGER_EVENT_ST_FAIL
}sm_service_charger_event_state_t;

typedef void sm_service_charger_t;

typedef struct sm_service_charger_if_t {
	uint16_t 	(*get_adc_charger_fn_t)(sm_service_charger_t* _this);
	uint8_t		(*check_charger_plugged_in_fn_t)(sm_service_charger_t* _this);
	int32_t 	(*set_fet_charger_fn_t)(uint8_t _value);
}sm_service_charger_if_t;

typedef void (*sm_service_charger_event_callback_fn_t)(sm_service_charger_t *_this, void* arg);

typedef void sm_service_bp_if_t;
/**
 * @brief sm_service_charger_create(sm_service_charger_if_t* _if, sm_bsp_adc_t* _adc_if, sm_service_bp_if_t* _bp_if)
 *
 * @param sm_service_charger_if_t* _if
 * @param sm_bsp_adc_t* _adc_if
 * @param sm_bsp_io_t* _io_if
 * @param sm_service_bp_if_t* _bp_if
 *
 * */
sm_service_charger_t* sm_service_charger_create(sm_service_charger_if_t* _if,
											sm_bsp_adc_t* _adc_if,
											sm_bsp_io_t* _io_if,
											sm_service_bp_if_t* _bp_if);
/**
 * @brief sm_service_charger_destroy(sm_service_charger_t* _this)
 *
 * @param sm_service_charger_t* _this
 *
 * */
int32_t sm_service_charger_destroy(sm_service_charger_t* _this);
/**
 * @brief sm_service_charger_reg_event(sm_service_charger_t* _this, sm_service_charger_event_callback_fn_t _fn_callback)
 *
 * @param sm_service_charger_t* _this
 * @param sm_service_charger_event_callback_fn_t _fn_callback
 *
 * */
int32_t sm_service_charger_reg_event(sm_service_charger_t* _this, sm_service_charger_event_callback_fn_t _fn_callback);
/**
 * @brief sm_service_charger_get_bp_num(sm_service_charger_t* _this)
 *
 * @param sm_service_charger_t* _this
 *
 * */
int32_t sm_service_charger_get_bp_num(sm_service_charger_t* _this);
/**
 * @brief sm_service_charger_get_cur(sm_service_charger_t* _this)
 *
 * @param sm_service_charger_t* _this
 *
 * */
int32_t sm_service_charger_get_cur(sm_service_charger_t* _this);
/**
 * @brief sm_service_charger_get_volt(sm_service_charger_t* _this)
 *
 * @param sm_service_charger_t* _this
 *
 * */
int32_t sm_service_charger_get_volt(sm_service_charger_t* _this);
/**
 * @brief sm_service_charger_get_state(sm_service_charger_t* _this)
 *
 * @param sm_service_charger_t* _this
 *
 * */
int32_t sm_service_charger_get_state(sm_service_charger_t* _this);
/**
 * @brief sm_service_charger_set_charge(sm_service_charger_t* _this, uint8_t _bp)
 *
 * @param sm_service_charger_t* _this
 *
 * */
int32_t sm_service_charger_set_charge(sm_service_charger_t* _this, uint8_t _bp);
/**
 * @brief sm_service_charger_set_discharge(sm_service_charger_t* _this, uint8_t _bp)
 *
 * @param sm_service_charger_t* _this
 *
 * */
int32_t sm_service_charger_set_discharge(sm_service_charger_t* _this, uint8_t _bp);
/**
 * @brief sm_service_charger_process(sm_service_charger_t* _this)
 *
 * @param sm_service_charger_t* _this
 *
 * */
void sm_service_charger_process(sm_service_charger_t* _this);
#endif /* SERVICES_INCLUDE_SM_SERVICE_CHARGER_H_ */
