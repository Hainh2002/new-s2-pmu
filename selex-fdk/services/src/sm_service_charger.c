/*
 * sm_charger_service.c
 *
 *  Created on: Jan 31, 2024
 *      Author: DELL 5425
 */
#include <sm_service_charger.h>
#include "sm_bsp_peripherals.h"
#include "sm_bsp_io.h"

typedef struct sm_service_charger_prof_t {
	uint32_t 	m_max_volt;
	uint32_t	m_min_volt;
	uint32_t	m_max_cur;
	uint32_t	m_power_stable_time;
	uint16_t	m_max_temp;

}sm_service_charger_prof_t;

struct sm_service_charger_t {
	sm_service_charger_prof_t 	m_info;
	uint32_t					m_adc;
	uint32_t 					m_volt_charger;
	uint32_t					m_cur_charger;
	uint8_t						m_state;
	uint8_t						m_plugged_in_state;
	uint8_t						m_bp_num;
	sm_service_charger_if_t* 	m_if;
	sm_service_bp_if_t* 		m_bp_if;
};


