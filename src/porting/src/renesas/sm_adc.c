/*
 * adc.c
 *
 *  Created on: Jul 10, 2023
 *      Author: Admin
 */


#include <sm_hal_adc.h>
#include "hal_data.h"
static int32_t adc_start(sm_hal_adc_t *_this);
static int32_t adc_stop(sm_hal_adc_t *_this);
static int32_t adc_open(sm_hal_adc_t *_this);
static int32_t adc_close(sm_hal_adc_t *_this);

sm_hal_adc_proc_t adc_func = {.start = adc_start,.stop = adc_stop,.open = adc_open,.close = adc_close};


static int32_t adc_start(sm_hal_adc_t *_this){
    /*User code*/
	adc_instance_t *adc = (adc_instance_t*) _this->handle;
	fsp_err_t err;
	err = R_ADC_ScanStart(adc->p_ctrl);
    return (int32_t)err;
}
static int32_t adc_stop(sm_hal_adc_t *_this){
    /*User code*/
	adc_instance_t *adc = (adc_instance_t*) _this->handle;
	fsp_err_t err;
	err = R_ADC_ScanStop(adc->p_ctrl);
    return (int32_t)err;
}
static int32_t adc_open(sm_hal_adc_t *_this){
    /*User code*/
	adc_instance_t *adc = (adc_instance_t*) _this->handle;
	fsp_err_t err;
	err = R_ADC_Open(adc->p_ctrl, adc->p_cfg);
    return (int32_t)err;
}
static int32_t adc_close(sm_hal_adc_t *_this){
    /*User code*/
	adc_instance_t *adc = (adc_instance_t*) _this->handle;
	fsp_err_t err;
	err = R_ADC_Close(adc->p_ctrl);
    return (int32_t)err;
}
