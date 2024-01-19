/*
 * sm_event.h
 *
 *  Created on: Jul 18, 2023
 *      Author: Admin
 */

#ifndef CORES_EVENT_SM_EVENT_H_
#define CORES_EVENT_SM_EVENT_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sm_fifo.h>
#include <sm_hal_timer.h>

typedef sm_fifo_handle_t *SM_SIGNAL;

typedef void (*SM_SLOT)();

typedef bool sm_signal_event;

typedef struct sm_event sm_event_t;

struct sm_event
{
    int event;
};
/**
 * @brief
 */
void sm_event_init();
/**
 * @brief
 */
void sm_event_process();
/**
 * @brief
 * @param object1
 * @param signal
 * @param object2
 * @param slot
 * @return event
 */
sm_event_t* sm_event_connect(void *object1, SM_SIGNAL signal, void *object2, SM_SLOT slot);
/**
 * @brief
 * @param event
 */
void sm_event_disconnect(sm_event_t *event);
/**
 * @brief
 * @param signal
 * @param length
 */
void sm_signal_init(SM_SIGNAL signal, uint32_t length);
/**
 * @brief
 * @param signal
 * @param signal_event
 * @return true | false
 */
bool sm_signal_push(SM_SIGNAL signal, sm_signal_event signal_event);


#endif /* CORES_EVENT_SM_EVENT_H_ */
