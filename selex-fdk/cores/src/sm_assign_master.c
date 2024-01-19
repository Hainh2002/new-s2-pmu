/*
 * sm_assign_master.c
 *
 *  Created on: Sep 20, 2023
 *      Author: MinhNhan
 */


#include "sm_assign_master.h"


void sm_m_assign_init(sm_assign_master_t *_this,sm_m_assign_func_t *_func,SM_ASSIGN_t **_array_sl,uint32_t _num_sl){
	_this->func = _func;
	_this->p_slave = _array_sl;
	_this->num_slave = _num_sl;
	_this->p_assign = NULL;
	_this->index = 0;
}
/**
 *
 * @param _this
 * @param _time_step_ms
 */
void sm_m_assign_process(sm_assign_master_t *_this,uint32_t _time_step_ms){

	if(_this->p_assign == NULL) goto END_ASSIGN;

	SM_ASSIGN_t *sl = _this->p_assign;

	if(sl->_assign_time_ms > sl->_config->assign_timeout_ms){
		sm_assign_set_state(sl, ASSIGN_ST_FALSE);
	}
	switch (sl->_state) {
		case ASSIGN_ST_START:
			sl->_if->node_id_selected();
			sm_assign_set_state(sl, ASSIGN_ST_WAIT_CONFIRM);
			break;
		case ASSIGN_ST_WAIT_CONFIRM:
			if(sm_assign_recv_confirm(sl) == true){
				sl->_if->node_id_deselected();
				sm_assign_set_state(sl, ASSIGN_ST_CONFIRMED);
			}
			break;
		case ASSIGN_ST_CONFIRMED:
			if(sm_assign_recv_confirm(sl) == true){
				_this->func->send_node_id(sl,_this->start_node_id+_this->index);
				sm_assign_set_state(sl, ASSIGN_ST_CONFIRM_ID);
			}
			break;
		case ASSIGN_ST_CONFIRM_ID:
			if(sl->_if->recv_node_id() == true){
				sm_assign_set_state(sl, ASSIGN_ST_START_AUTHENTICATE);
			}
			break;
		case ASSIGN_ST_START_AUTHENTICATE:
			sm_assign_set_state(sl, ASSIGN_ST_AUTHENTICATING);
			_this->func->request_sn(sl);
			sl->_if->node_id_selected();
			break;
		case ASSIGN_ST_AUTHENTICATING:
			if(_this->func->request_sn_callback(sl) == true){
				sm_assign_set_state(sl, ASSIGN_ST_SUCCESS);
			}
			break;
		case ASSIGN_ST_SUCCESS:
			_this->p_assign = NULL;
			break;
		case ASSIGN_ST_FALSE:
			sl->_if->node_id_deselected();
			sm_assign_set_state(sl, ASSIGN_ST_START);
			break;
		default:
			break;
	}

END_ASSIGN:

	sl->_assign_time_ms += _time_step_ms;
}
