/*
 * sm_assign_slave.h
 *
 *  Created on: Sep 20, 2023
 *      Author: MinhNhan
 */

#ifndef CORES_INCLUDE_SM_ASSIGN_SLAVE_H_
#define CORES_INCLUDE_SM_ASSIGN_SLAVE_H_


#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct SM_ASSIGN SM_ASSIGN_t;

enum assign_state{
	ASSIGN_ST_START = 0,
	ASSIGN_ST_WAIT_CONFIRM,
	ASSIGN_ST_CONFIRMED,
	ASSIGN_ST_CONFIRM_ID,
	ASSIGN_ST_WAIT_SLAVE_SELECT,
	ASSIGN_ST_START_AUTHENTICATE,
	ASSIGN_ST_AUTHENTICATING,
	ASSIGN_ST_SUCCESS,
	ASSIGN_ST_FALSE
};


struct SM_ASSIGN{
	void *child;
	enum assign_state _state;
	uint8_t start_id;

	struct assign_if{
		bool (*node_id_selected)();
		bool (*node_id_deselected)();
		void (*send_cob_id)(uint16_t _cod_id);
		bool (*recv_confirm)();
		bool (*recv_node_id)();
		bool (*authen_success)();
	} *_if;
	struct assign_config{
		uint32_t assign_timeout_ms;
		uint16_t cob_id;

	} *_config;

	uint32_t _assign_time_ms;
};

/**
 * @brief
 * @param _this
 * @param _if
 * @param _config
 */
void sm_assign_init(SM_ASSIGN_t *_this,struct assign_if *_if, struct assign_config *_config);
/**
 * @brief
 * @param _this
 */
void sm_assign_process(SM_ASSIGN_t *_this);
/**
 * @brief
 * @param _this
 * @param _state
 */
void sm_assign_set_state(SM_ASSIGN_t *_this,enum assign_state _state);
/**
 * @brief
 * @param _this
 * @return
 */
static inline enum assign_state sm_assign_get_state(SM_ASSIGN_t *_this){
	return _this->_state;
}
/**
 * @brief
 * @param _this
 * @return true | false
 */
static inline bool sm_assign_id_selected(SM_ASSIGN_t *_this){
	return _this->_if->node_id_selected();
}
/**
 * @brief
 * @param _this
 */
static inline void sm_assign_send_cob_id(SM_ASSIGN_t *_this){
	_this->_if->send_cob_id(_this->_config->cob_id);
}
/**
 * @brief
 * @param _this
 * @return true  | false
 */
static inline bool sm_assign_recv_confirm(SM_ASSIGN_t *_this){
	return _this->_if->recv_confirm();
}
/**
 * @brief
 * @param _this
 * @return true | false
 */
static inline bool sm_assign_authen_success(SM_ASSIGN_t *_this){
	return _this->_if->authen_success();
}


#endif /* CORES_INCLUDE_SM_ASSIGN_SLAVE_H_ */
