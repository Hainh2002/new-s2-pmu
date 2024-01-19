/*
 * task.h
 *
 *  Created on: Jul 14, 2023
 *      Author: Admin
 */

#ifndef CORES_TASK_sm_sch_task_H_
#define CORES_TASK_sm_sch_task_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#if USING_RTOS

#include <FreeRTOS.h>
#include <task.h>

#define sm_tskKERNEL_VERSION_NUMBER tskKERNEL_VERSION_NUMBER
#define sm_tskKERNEL_VERSION_MAJOR tskKERNEL_VERSION_MAJOR
#define sm_tskKERNEL_VERSION_MINOR tskKERNEL_VERSION_MINOR
#define sm_tskKERNEL_VERSION_BUILD tskKERNEL_VERSION_BUILD

/* MPU region parameters passed in ulParameters
 * of MemoryRegion_t struct. */
#define sm_tskMPU_REGION_READ_ONLY tskMPU_REGION_READ_ONLY
#define sm_tskMPU_REGION_READ_WRITE tskMPU_REGION_READ_WRITE
#define sm_tskMPU_REGION_EXECUTE_NEVER tskMPU_REGION_EXECUTE_NEVER
#define sm_tskMPU_REGION_NORMAL_MEMORY tskMPU_REGION_NORMAL_MEMORY
#define sm_tskMPU_REGION_DEVICE_MEMORY tskMPU_REGION_DEVICE_MEMORY

#define sm_tskDEFAULT_INDEX_TO_NOTIFY     tskDEFAULT_INDEX_TO_NOTIFY

typedef TaskHandle_t sm_sch_taskHandle_t;

typedef eTaskState sm_eTaskState;

typedef eNotifyAction sm_eNotifyAction;

typedef TimeOut_t sm_TimeOut_t;

typedef MemoryRegion_t sm_MemoryRegion_t;

#define sm_tskIDLE_PRIORITY tskIDLE_PRIORITY;
#define sm_sch_taskYIELD() taskYIELD()
#define sm_sch_taskENTER_CRITICAL() taskENTER_CRITICAL()
#define sm_sch_taskENTER_CRITICAL_FROM_ISR() taskENTER_CRITICAL_FROM_ISR()
#define sm_sch_taskEXIT_CRITICAL() taskEXIT_CRITICAL()
#define sm_sch_taskEXIT_CRITICAL_FROM_ISR( x ) taskEXIT_CRITICAL_FROM_ISR( x )
#define sm_sch_taskDISABLE_INTERRUPTS() taskDISABLE_INTERRUPTS()
#define sm_sch_taskENABLE_INTERRUPTS() taskENABLE_INTERRUPTS()
#define sm_sch_taskSCHEDULER_SUSPENDED taskSCHEDULER_SUSPENDED
#define sm_sch_taskSCHEDULER_NOT_STARTED taskSCHEDULER_NOT_STARTED
#define sm_sch_taskSCHEDULER_RUNNING taskSCHEDULER_RUNNING

#define sm_xTaskCreate(taskcode,name,stack,parameter,priority,handle) xTaskCreate(taskcode,name,stack,parameter,priority,handle)
#define sm_vTaskAllocateMPURegions(handle,Regions) vTaskAllocateMPURegions(handle,Regions)
#define sm_vTaskDelete(handle) vTaskDelete(handle)
#define sm_vTaskDelay(x) vTaskDelay(x)
#define sm_xTaskDelayUntil(wake_time,x)  xTaskDelayUntil(wake_time,x)
#define sm_vTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement ) vTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement )

#else /// NO RTOS

#include <sm_hal_timer.h>
#include "sm_elapsed_timer.h"

#define SM_SCH_TASK_MAX_SUPPORT		32
#define TIMER_REPEAT_FOREVER        0xffff

typedef void sm_sch_t;

typedef void (*sm_sch_task_fn_t)(void *arg);

typedef struct {
    int32_t m_repeat_count;
    int32_t m_interval;
    sm_sch_task_fn_t m_fn;
    void* m_arg;
}sm_sch_task_t;
/**
 * @brief
 * @return  0: success | -1 : false
 */
sm_sch_t* sm_sch_create();
/**
 * @brief
 * @return 0: success | -1 : false
 */
sm_sch_t* sm_sch_create_default();
/**
 * @brief
 * @param _this
 * @return 0: success | -1 : false
 */
int32_t sm_sch_free(sm_sch_t* _this);
/**
 * @brief
 * @param _this
 * @param _task
 * @return 0: success | -1 : false
 */
int32_t sm_sch_start_task(sm_sch_t* _this, const sm_sch_task_t* _task);
/**
 * @brief
 * @param _this
 * @param _task_id
 * @return 0: success | -1 : false
 */
int32_t sm_sch_cancel_task(sm_sch_t* _this, int32_t _task_id);
/**
 * @brief
 * @param _this
 * @return 0: success | -1 : false
 */
int32_t sm_sch_process(sm_sch_t* _this);

/*void sm_sch_task_startScheduler(sm_bsp_timer_t *sys_tick);
void sm_sch_task_stopScheduler();

void sm_sch_task_create(sm_sch_task_func fun, char *task_name, void *arg, sm_sch_task_handle task_handle);

void sm_sch_task_delete(sm_sch_task_handle task_handle);
void sm_sch_task_delay(uint32_t time_ms);*/

#endif



#endif /* CORES_TASK_sm_sch_task_H_ */
