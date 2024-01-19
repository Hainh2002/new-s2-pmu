/*
 * pwm.c
 *
 *  Created on: Jul 10, 2023
 *      Author: Admin
 */


/*include mcu platform*/

/*end*/

#include <sm_hal_pwm.h>

static    int32_t pwm_set_frequency(sm_hal_pwm_t *_this,uint32_t freq);
static    int32_t pwm_set_dutycycles(sm_hal_pwm_t *_this, uint32_t dutycycle);
static    int32_t pwm_start(sm_hal_pwm_t *_this);
static    int32_t pwm_stop(sm_hal_pwm_t *_this);
static    int32_t pwm_open(sm_hal_pwm_t *_this);
static    int32_t pwm_close(sm_hal_pwm_t *_this);

sm_hal_pwm_proc_t pwm_func ={.set_dutycycles = pwm_set_dutycycles,.set_frequency = pwm_set_frequency,.start = pwm_start,.stop = pwm_stop,.open = pwm_open,.close = pwm_close};

static    int32_t pwm_set_frequency(sm_hal_pwm_t *_this,uint32_t freq){
    /*User code*/
    return 0;
}
static    int32_t pwm_set_dutycycles(sm_hal_pwm_t *_this, uint32_t dutycycle){
    /*User code*/
    return 0;
}
static    int32_t pwm_start(sm_hal_pwm_t *_this){
    /*User code*/
    return 0;
}
static    int32_t pwm_stop(sm_hal_pwm_t *_this){
    /*User code*/
    return 0;
}
static    int32_t pwm_open(sm_hal_pwm_t *_this){
    /*User code*/
    return 0;
}
static    int32_t pwm_close(sm_hal_pwm_t *_this){
    /*User code*/
    return 0;
}
