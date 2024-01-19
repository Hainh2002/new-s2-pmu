/*
 * timer.c
 *
 *  Created on: Jul 10, 2023
 *      Author: Admin
 */


/*include mcu platform*/

/*end*/
#include <sm_hal_timer.h>


static    int32_t timer_start(sm_hal_timer_t *_this);
static    int32_t timer_stop(sm_hal_timer_t *_this);
static    int32_t timer_set_perios(sm_hal_timer_t *_this, uint32_t perios);
static    int32_t timer_open(sm_hal_timer_t *_this);
static    int32_t timer_close(sm_hal_timer_t *_this);

sm_hal_timer_proc_t timer_func = {.open = timer_open,.close = timer_close,.set_perios = timer_set_perios,.start = timer_start,.stop = timer_stop};

static    int32_t timer_start(sm_hal_timer_t *_this){
    /*User code*/
    return 0;
}
static    int32_t timer_stop(sm_hal_timer_t *_this){
    /*User code*/
    return 0;
}
static    int32_t timer_set_perios(sm_hal_timer_t *_this, uint32_t perios){
    /*User code*/
    return 0;
}
static    int32_t timer_open(sm_hal_timer_t *_this){
    /*User code*/
    return 0;
}
static    int32_t timer_close(sm_hal_timer_t *_this){
    /*User code*/
    return 0;
}
