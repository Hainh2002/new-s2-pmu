/*
 * sm_event.c
 *
 *  Created on: Jul 18, 2023
 *      Author: Admin
 */


#include <sm_hal_timer.h>
#include "sm_event.h"
#include "assert.h"
#include "sm_link_list.h"

link_list_t *sm_event_list = NULL;

#define _impl(x) ((sm_event_impl_t*)(x))

typedef struct sm_event_impl sm_event_impl_t;

struct sm_event_impl
{
    sm_event_t base;
    void *object1;
    SM_SIGNAL signal;
    void *object2;
    SM_SLOT slot;
};

static void sm_event_run(void *arg);
/**
 *
 */
void sm_event_init()
{
    sm_event_list = list_new (NULL, sizeof(sm_event_impl_t));
}

void sm_event_process()
{
    sm_event_run (NULL);
}
/**
 *
 * @param object1
 * @param signal
 * @param object2
 * @param slot
 * @return
 */
sm_event_t* sm_event_connect(void *object1, SM_SIGNAL signal, void *object2, SM_SLOT slot)
{
    sm_event_impl_t *event = malloc (sizeof(sm_event_impl_t));

    event->object1 = object1;
    event->object2 = object2;
    event->signal = signal;
    event->slot = slot;
    assert(event != NULL);
    list_add (sm_event_list, (void*) event);
    return &event->base;

}
/**
 *
 * @param event
 */
void sm_event_disconnect(sm_event_t *event)
{
    list_remove (sm_event_list, (void*) event);
}
/**
 *
 * @param arg
 */
static void sm_event_run(void *arg)
{

    (void) arg;
    link_list_t *list = sm_event_list;

    while (list != NULL)
    {
        sm_event_impl_t *event = (sm_event_impl_t*) list->item;
        if (event != NULL)
            if (event->signal != NULL)
            {
                bool signal = false;
                if (sm_fifo_pop (event->signal, (void*) &signal) == true)
                {
                    if (signal)
                    {
                        event->slot ();
                    }
                }
            }
        list = list->next;
    }
}
/**
 *
 * @param signal
 * @param length
 */
void sm_signal_init(SM_SIGNAL signal, uint32_t length)
{
	sm_fifo_init (signal, length, sizeof(bool));
}
/**
 *
 * @param signal
 * @param signal_event
 * @return
 */
bool sm_signal_push(SM_SIGNAL signal, sm_signal_event signal_event)
{
    return sm_fifo_push (signal, (void*) &signal_event);
}
