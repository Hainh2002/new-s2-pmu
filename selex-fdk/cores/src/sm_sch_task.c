/*
 * sm_task.c
 *
 *  Created on: Jul 14, 2023
 *      Author: Admin
 */
/*

#include <sm_link_list.h>
#include "sm_task.h"


link_list_t list = {.item = NULL,.next = NULL,.size_item = sizeof(sm_task_t)};

sm_bsp_timer_t *timer_sys = NULL;
sm_task_handle prt_task = NULL;
uint32_t num_task = 0;
static link_list_t* sm_swap_task(link_list_t *list1, link_list_t *list2);
static void sm_bubble_sort_task(link_list_t **task_list,uint32_t count);
static void sm_Scheduler(void* arg);

void sm_task_startScheduler(sm_bsp_timer_t *sys_tick){
    timer_sys = sys_tick;
    sm_bsp_timer_set_callback(timer_sys, sm_Scheduler, (void*)&list);
    sm_bsp_timer_start(sys_tick);

}
void sm_task_stopScheduler(){
    sm_bsp_timer_stop(timer_sys);
}

void sm_task_create(sm_task_func fun,char *task_name,void* arg,sm_task_handle task_handle){

    if(task_handle == NULL){
        task_handle = (sm_task_t*)malloc(sizeof(sm_task_t));
    }
    task_handle->func = fun;
    task_handle->name = task_name;
    task_handle->arg = arg;
    task_handle->time_reload_ms = 1;
    task_handle->time_tick_ms = 0;
    list_add(&list,(void*)task_handle);
    num_task++;
    link_list_t* p_list = &list;
    sm_bubble_sort_task(&p_list,num_task);
}

void sm_task_delete(sm_task_handle task_handle){
    list_remove(&list,(void*) task_handle);
    num_task--;
}
void sm_task_delay(uint32_t time_ms){
    if(prt_task == NULL) return;
    prt_task->time_reload_ms = time_ms;
}
static void sm_Scheduler(void* arg){
    link_list_t *task_list = (link_list_t*) arg;
    while(task_list != NULL){
        prt_task = (sm_task_handle)task_list->item;
        if(prt_task->func != NULL){
            prt_task->time_tick_ms++;
            if(prt_task->time_tick_ms == prt_task->time_reload_ms){
                prt_task->func(prt_task->arg);
                prt_task->time_tick_ms = 0;
            }
        }
        task_list = task_list->next;
    }
}
static link_list_t* sm_swap_task(link_list_t *list1, link_list_t *list2){
    link_list_t *tmp = list2->next;
    list2->next = list1;
    list1->next = tmp;
    return list2;
}
static void sm_bubble_sort_task(link_list_t **task_list,uint32_t count){
    link_list_t** h;
    uint32_t i, j, swapped;

    for (i = 0; i <= count; i++) {

        h = task_list;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++) {

            link_list_t* p1 = *h;
            link_list_t* p2 = p1->next;
            sm_task_handle task1 = (sm_task_handle)p1->item;
            sm_task_handle task2 = (sm_task_handle)p2->item;

            if (task1->priority > task2->priority) {

                */
/* update the link after swapping *//*

                *h = sm_swap_task(p1, p2);
                swapped = 1;
            }

            h = &(*h)->next;
        }

        */
/* break if the loop ended without any swap *//*

        if (swapped == 0)
            break;
    }
}
*/

#include <stdint.h>
#include "sm_sch_task.h"
#include "sm_elapsed_timer.h"

#define SM_SCH_TASK_REPEAT_FOREVER 10

#define _impl(p)    ((sm_scheduler_t*)(p))

typedef struct{
    struct {
        elapsed_timer_t m_timeout;
        int32_t m_count;
        sm_sch_task_t m_task;
    }m_tasks[SM_SCH_TASK_MAX_SUPPORT];
}sm_scheduler_t;

static sm_scheduler_t g_sch_default;
/**
 *
 * @return
 */
sm_sch_t* sm_sch_create(){
    sm_scheduler_t* sch = malloc (sizeof(sm_scheduler_t));
    if(!sch){
        return NULL;
    }
    for(int index = 0; index < SM_SCH_TASK_MAX_SUPPORT; ++index){
        sch->m_tasks->m_count = 0;
        sch->m_tasks->m_task.m_arg = NULL;
        sch->m_tasks[index].m_task.m_fn = NULL;
        sch->m_tasks[index].m_task.m_interval = 0;
        sch->m_tasks[index].m_task.m_repeat_count = 0;
    }

    return (sm_sch_t*)sch;
}
/**
 *
 * @return
 */
sm_sch_t* sm_sch_create_default(){
    sm_sch_free(&g_sch_default);
    return (sm_sch_t*)&g_sch_default;
}
/**
 *
 * @param _this
 * @return
 */
int32_t sm_sch_free(sm_sch_t* _this){
    if(!_this){
        return -1;
    }
    for (int index = 0; index < SM_SCH_TASK_MAX_SUPPORT; ++index) {
        _impl(_this)->m_tasks[index].m_task.m_arg = NULL;
        _impl(_this)->m_tasks[index].m_task.m_fn = NULL;
        _impl(_this)->m_tasks[index].m_task.m_interval = 0;
        _impl(_this)->m_tasks[index].m_task.m_repeat_count = 0;
    }
}
/**
 *
 * @param _this
 * @param _task
 * @return
 */
int32_t sm_sch_start_task(sm_sch_t* _this, const sm_sch_task_t* _task){
    if(!_this){
        return -1;
    }
    for (int index = 0; index < SM_SCH_TASK_MAX_SUPPORT; ++index) {
        if(!_impl(_this)->m_tasks[index].m_task.m_fn){
            _impl(_this)->m_tasks[index].m_task.m_arg = _task->m_arg;
            _impl(_this)->m_tasks[index].m_task.m_fn = _task->m_fn;
            _impl(_this)->m_tasks[index].m_task.m_interval = _task->m_interval;
            _impl(_this)->m_tasks[index].m_task.m_repeat_count = _task->m_repeat_count;
            _impl(_this)->m_tasks[index].m_count = 0;
            elapsed_timer_resetz(&_impl(_this)->m_tasks[index].m_timeout, _task->m_interval);
            for (index = index + 1; index < SM_SCH_TASK_MAX_SUPPORT; index++)
                if (_impl(_this)->m_tasks[index].m_task.m_fn == _task->m_fn)
                    _impl(_this)->m_tasks[index].m_task.m_fn = NULL;
            return index;
        }
    }
    return -1;
}
/**
 *
 * @param _this
 * @param _task_id
 * @return
 */
int32_t sm_sch_cancel_task(sm_sch_t* _this,  int32_t _task_id){
    if(!_this || _task_id >= SM_SCH_TASK_MAX_SUPPORT){
        return -1;
    }
    _impl(_this)->m_tasks[_task_id].m_task.m_arg = NULL;
    _impl(_this)->m_tasks[_task_id].m_task.m_fn = NULL;
    _impl(_this)->m_tasks[_task_id].m_task.m_interval = 0;
    _impl(_this)->m_tasks[_task_id].m_task.m_repeat_count = 0;
    _impl(_this)->m_tasks[_task_id].m_count = 0;
    return 0;
}
/**
 *
 * @param _this
 * @return
 */
int32_t sm_sch_process(sm_sch_t* _this){
    sm_sch_task_fn_t callback_fn = NULL;

    if(!_this){
        return -1;
    }
    for (int index = 0; index < SM_SCH_TASK_MAX_SUPPORT; ++index) {
        if (!elapsed_timer_get_remain(&_impl(_this)->m_tasks[index].m_timeout) && _impl(_this)->m_tasks[index].m_task.m_fn) {
            callback_fn = _impl(_this)->m_tasks[index].m_task.m_fn;
            callback_fn(_impl(_this)->m_tasks[index].m_task.m_arg);

            if ((_impl(_this)->m_tasks[index].m_count < _impl(_this)->m_tasks[index].m_task.m_repeat_count - 1)
                || (_impl(_this)->m_tasks[index].m_task.m_repeat_count == SM_SCH_TASK_REPEAT_FOREVER)) {
                _impl(_this)->m_tasks[index].m_count++;
                elapsed_timer_reset(&_impl(_this)->m_tasks[index].m_timeout);
            }else{
                _impl(_this)->m_tasks[index].m_task.m_fn = NULL;
                _impl(_this)->m_tasks[index].m_task.m_arg = NULL;
            }
        }
    }
    return 0;
}
