/*
 * sm_assign_slave.c
 *
 *  Created on: Sep 20, 2023
 *      Author: MinhNhan
 */


/*
 * sm_assign.c
 *
 *  Created on: Aug 10, 2023
 *      Author: Admin
 */


#include "sm_assign_slave.h"
#include <stdlib.h>
#define ASSIGN_TIMEOUT_DEFAULT_mS 3000
#define ASSIGN_TIMEOUT_AUTHEN_mS 5000

void sm_assign_init(SM_ASSIGN_t *_this,struct assign_if *_if, struct assign_config *_config){
	_this->_config = _config;
	_this->_if = _if;
    _this->_assign_time_ms = 0;
    _this->_state = ASSIGN_ST_START;
}
/**
 *
 * @param _this
 * @param _state
 */
void sm_assign_set_state(SM_ASSIGN_t *_this,enum assign_state _state){
	switch (_this->_state) {
		case ASSIGN_ST_START:
		case ASSIGN_ST_WAIT_CONFIRM:
		case ASSIGN_ST_CONFIRMED:
		case ASSIGN_ST_WAIT_SLAVE_SELECT:
			_this->_config->assign_timeout_ms = ASSIGN_TIMEOUT_DEFAULT_mS;
			break;
		case ASSIGN_ST_START_AUTHENTICATE:
		case ASSIGN_ST_AUTHENTICATING:
			_this->_config->assign_timeout_ms = ASSIGN_TIMEOUT_AUTHEN_mS;
			break;
		case ASSIGN_ST_SUCCESS:

			break;
		case ASSIGN_ST_FALSE:

			break;
		default:
			break;
	}
	_this->_state = _state;
	_this->_assign_time_ms = 0;
}
/**
 *
 * @param _this
 */
void sm_assign_process(SM_ASSIGN_t *_this){
	if(_this->_assign_time_ms > _this->_config->assign_timeout_ms){
		sm_assign_set_state(_this, ASSIGN_ST_FALSE);
	}
	switch (_this->_state) {
		case ASSIGN_ST_START:
			sm_assign_send_cob_id(_this); // Send id = 0x70 data = {0}
			sm_assign_set_state(_this, ASSIGN_ST_WAIT_CONFIRM);
			break;
		case ASSIGN_ST_WAIT_CONFIRM:
			if(sm_assign_recv_confirm(_this) == true){
				sm_assign_set_state(_this, ASSIGN_ST_CONFIRMED);
			}
			break;
		case ASSIGN_ST_CONFIRMED:
			if(sm_assign_id_selected(_this) == false){
				sm_assign_send_cob_id(_this);
				sm_assign_set_state(_this, ASSIGN_ST_WAIT_SLAVE_SELECT);
			}
			break;
		case ASSIGN_ST_WAIT_SLAVE_SELECT:
			if(sm_assign_recv_confirm(_this) == true){
				sm_assign_set_state(_this, ASSIGN_ST_START_AUTHENTICATE);
			}
			break;
		case ASSIGN_ST_START_AUTHENTICATE:
			sm_assign_set_state(_this, ASSIGN_ST_AUTHENTICATING);
			break;
		case ASSIGN_ST_AUTHENTICATING:
//            if (sm_assign_authen_success (_this))
//            {
//				sm_assign_set_state(_this, ASSIGN_ST_SUCCESS);
//            }
			break;
		case ASSIGN_ST_SUCCESS:

			break;
		case ASSIGN_ST_FALSE:

			break;
		default:
			break;
	}
	_this->_assign_time_ms++;
}
