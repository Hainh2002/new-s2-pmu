/*
 * can.c
 *
 *  Created on: Jul 10, 2023
 *      Author: Admin
 */


#include <sm_hal_can.h>
#include "hal_data.h"

static int32_t can_write(sm_hal_can_t *_this,sm_hal_can_mgs_t *mgs);
static int32_t can_set_baud(sm_hal_can_t *_this,uint32_t baud);
static int32_t can_open(sm_hal_can_t *_this);
static int32_t can_close(sm_hal_can_t *_this);

sm_hal_can_proc_t can_func = {.close = can_close,.open = can_open,.set_baudrate = can_set_baud,.write = can_write};

static int32_t can_write(sm_hal_can_t *_this,sm_hal_can_mgs_t *_mgs){
    /*User code*/
	can_instance_t* can = (can_instance_t*) _this->handle;
	can_frame_t* can_frame = NULL;
	can_frame->id = _mgs->id;
	can_frame->data_length_code = (uint8_t)_mgs->length;
	memcpy(can_frame->data, _mgs->data, 8);
	can_frame->id_mode = CAN_ID_MODE_STANDARD;
	can_frame->type = CAN_FRAME_TYPE_DATA;

	fsp_err_t err;
	err = R_CAN_Write(can->p_ctrl, CAN_MAILBOX_ID_0, can_frame);

    return (int32_t)err;
}
static int32_t can_set_baud(sm_hal_can_t *_this,uint32_t _baud){
    /*User code*/
    (void)_this;
    (void)_baud;
    return 0;
}
static int32_t can_open(sm_hal_can_t *_this){
    /*User code*/
    can_instance_t* can = (can_instance_t*) _this->handle;

    fsp_err_t err;
    err = R_CAN_Open(can->p_ctrl, can->p_cfg);

    return (int32_t)err;
}
static int32_t can_close(sm_hal_can_t *_this){
    /*User code*/
    can_instance_t* can = (can_instance_t*) _this->handle;

    fsp_err_t err;
    err = R_CAN_Close(can->p_ctrl);
    return (int32_t)err;
}
