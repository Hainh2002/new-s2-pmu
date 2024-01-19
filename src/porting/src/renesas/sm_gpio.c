/*
 * io.c
 *
 *  Created on: Jul 10, 2023
 *      Author: Admin
 */

/*include mcu platform*/

/*end*/

#include <sm_hal_io.h>
#include "hal_data.h"

static int32_t gpio_open(sm_hal_io_t *_this, sm_hal_io_mode_t _mode);
static int32_t gpio_close(sm_hal_io_t *_this);
static int32_t gpio_set_value(sm_hal_io_t*, uint8_t);
static uint8_t gpio_get_value(sm_hal_io_t*);

sm_hal_io_proc_t io_func = { .close = gpio_close, .open = gpio_open,
		.set_value = gpio_set_value, .get_value = gpio_get_value };

static int32_t gpio_open(sm_hal_io_t *_this, sm_hal_io_mode_t _mode) {
	/*User code*/
	_this->mode = _mode;
	ioport_instance_t *io_port = (ioport_instance_t*) _this->handle;
	fsp_err_t err;
	err = R_IOPORT_Open(io_port->p_ctrl, io_port->p_cfg);
	return (int32_t)err;
}
static int32_t gpio_close(sm_hal_io_t *_this) {
	/*User code*/
	ioport_instance_t *io_port = (ioport_instance_t*) _this->handle;
	fsp_err_t err;
	err = R_IOPORT_Close(io_port->p_ctrl);
	return (int32_t)err;
}
static int32_t gpio_set_value(sm_hal_io_t *_this, uint8_t value) {
	/*User code*/
    ioport_instance_t *io_port = (ioport_instance_t*) _this->handle;
    fsp_err_t err;
    err = R_IOPORT_PinWrite(io_port->p_ctrl, _this->pin, value);
	return (int32_t)err;
}
static uint8_t gpio_get_value(sm_hal_io_t *_this) {
	/*User code*/
	ioport_instance_t *io_port = (ioport_instance_t*) _this->handle;
	uint8_t value ;
	fsp_err_t err;
	err = R_IOPORT_PinRead(io_port->p_ctrl, _this->pin, &value);
	(void)err;
	return value;
}
