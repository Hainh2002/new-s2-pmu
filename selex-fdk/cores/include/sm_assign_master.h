/*
 * sm_assign_master.h
 *
 *  Created on: Sep 20, 2023
 *      Author: MinhNhan
 */

#ifndef CORES_INCLUDE_SM_ASSIGN_MASTER_H_
#define CORES_INCLUDE_SM_ASSIGN_MASTER_H_


#include "sm_assign_slave.h"

/**
 */
typedef struct sm_assign_master sm_assign_master_t;

/**
 * @brief
 */
typedef struct sm_m_assign_func{
	void (*send_node_id)(SM_ASSIGN_t *_this,uint32_t id);
	void (*request_sn)(SM_ASSIGN_t *_this);
	bool (*request_sn_callback)(SM_ASSIGN_t *_this);
}sm_m_assign_func_t;

/**
 * @brief
 */
struct sm_assign_master{
	SM_ASSIGN_t **p_slave;
	uint32_t num_slave;
	SM_ASSIGN_t *p_assign;
	uint32_t index;
	sm_m_assign_func_t *func;
	uint32_t start_node_id;
};

/**
 * @brief
 * @param _this
 * @param _func
 * @param _array_sl
 * @param _num_sl
 */
void sm_m_assign_init(sm_assign_master_t *_this,sm_m_assign_func_t *_func,SM_ASSIGN_t **_array_sl,uint32_t _num_sl);
/**
 * @brief
 * @param _this
 * @param _time_step_ms
 */
void sm_m_assign_process(sm_assign_master_t *_this,uint32_t _time_step_ms);

#endif /* CORES_INCLUDE_SM_ASSIGN_MASTER_H_ */
