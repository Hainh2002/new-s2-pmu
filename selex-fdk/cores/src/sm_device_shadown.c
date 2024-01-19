/*
 * iot_sevice.c
 *
 *  Created on: Jul 17, 2023
 *      Author: Admin
 */

#include "sm_device_shadown.h"
#if USING_MQTT
#define shadown_get_topic             "selex/%s/%s/shadow/get"                    // Public
#define shadown_get_accepted_topic    "selex/%s/%s/shadow/get/accepted"      // Sub
#define shadown_get_rejected_topic    "selex/%s/%s/shadow/get/rejected"      // Sub

#define shadown_update_topic          "selex/%s/%s/shadow/update"              // Pub
#define shadown_update_delta_topic    "selex/%s/%s/shadow/update/delta"         // Sub
#define shadown_update_accepted_topic "selex/%s/%s/shadow/update/accepted"         // Sub
#define shadown_update_rejected_topic "selex/%s/%s/shadow/update/rejected"         // Sub

#define shadown_delete_topic          "selex/%s/%s/shadow/delete"         // pub
#define shadown_delete_update_topic   "selex/%s/%s/shadow/delete/updated"         // Sub
#define shadown_delete_rejected_topic "selex/%s/%s/shadow/delete/rejected" // Sub

static void mqtt_event(sm_mqtt_client_t *client, sm_mqtt_client_event_t event);

static void sm_iot_device_handle(sm_device_shadown_t *client, sm_iot_device_t *device);

static sm_iot_device_t* iot_device_new(char *name, char *type,
        sm_device_shadown_func_callback_t *iot_device_callback);
static sm_iot_device_t* iot_device_search(sm_iot_device_t *list, char *name);
/**
 *
 * @param client
 * @param mqtt_client
 * @param name
 * @param type
 * @param iot_device_callback
 * @return
 */
int32_t sm_iot_init(sm_device_shadown_t *client, sm_mqtt_client_t *mqtt_client, char *name, char *type,
        sm_device_shadown_func_callback_t *iot_device_callback)
{
	if (client == NULL)
		return -1;

	client->base = mqtt_client;
	mqtt_client->parent = (void*) client;
    client->device = iot_device_new (name, type, iot_device_callback);
//	sm_mqtt_client_set_callback_event(mqtt_client, mqtt_event);
	sm_mqtt_client_register_handle(mqtt_client, mqtt_event);
	return 0;
}
/**
 *
 * @param name
 * @param type
 * @param iot_device_callback
 * @return
 */
static sm_iot_device_t* iot_device_new(char *name, char *type,
        sm_device_shadown_func_callback_t *iot_device_callback)
{

    sm_iot_device_t *device = malloc (sizeof(sm_iot_device_t));
    if (device == NULL)
        return NULL;
    device->next = NULL;
    strcpy (device->name, name);
    device->callback = iot_device_callback;
    strcpy (device->type, type);

    sprintf (device->topic.get_topic, shadown_get_topic, device->type, device->name);          // Pub
    sprintf (device->topic.get_accepted_topic, shadown_get_accepted_topic, device->type, device->name); // Sub
    sprintf (device->topic.get_rejected_topic, shadown_get_rejected_topic, device->type, device->name); // Sub
    sprintf (device->topic.update_topic, shadown_update_topic, device->type, device->name);    // Pub
    sprintf (device->topic.update_delta_topic, shadown_update_delta_topic, device->type, device->name); // Sub
    sprintf (device->topic.update_accepted_topic, shadown_update_accepted_topic, device->type, device->name); // Sub
    sprintf (device->topic.update_rejected_topic, shadown_update_rejected_topic, device->type, device->name); // Sub
    sprintf (device->topic.delete_topic, shadown_delete_topic, device->type, device->name);    // Pub
    sprintf (device->topic.delete_update_topic, shadown_delete_update_topic, device->type, device->name); // Sub
    sprintf (device->topic.delete_rejected_topic, shadown_delete_rejected_topic, device->type, device->name); // Sub

    device->connected = false;

    return device;
}
/**
 *
 * @param client
 * @param name
 * @param type
 * @param iot_device_callback
 * @return
 */
int32_t sm_iot_device_add(sm_device_shadown_t *client, char *name, char *type,
        sm_device_shadown_func_callback_t *iot_device_callback)
{
    sm_iot_device_t *node = client->device;
    while (node->next != NULL)
    {
        node = node->next;
    }

    sm_iot_device_t *device = malloc (sizeof(sm_iot_device_t));
    if (device == NULL)
        return -1;
    device->next = NULL;
    strcpy (device->name, name);
    device->callback = iot_device_callback;
    strcpy (device->type, type);

    sprintf (device->topic.get_topic, shadown_get_topic, device->type, device->name);          // Pub
    sprintf (device->topic.get_accepted_topic, shadown_get_accepted_topic, device->type, device->name); // Sub
    sprintf (device->topic.get_rejected_topic, shadown_get_rejected_topic, device->type, device->name); // Sub
    sprintf (device->topic.update_topic, shadown_update_topic, device->type, device->name);    // Pub
    sprintf (device->topic.update_delta_topic, shadown_update_delta_topic, device->type, device->name); // Sub
    sprintf (device->topic.update_accepted_topic, shadown_update_accepted_topic, device->type, device->name); // Sub
    sprintf (device->topic.update_rejected_topic, shadown_update_rejected_topic, device->type, device->name); // Sub
    sprintf (device->topic.delete_topic, shadown_delete_topic, device->type, device->name);    // Pub
    sprintf (device->topic.delete_update_topic, shadown_delete_update_topic, device->type, device->name); // Sub
    sprintf (device->topic.delete_rejected_topic, shadown_delete_rejected_topic, device->type, device->name); // Sub
    node->next = device;

    device->connected = false;
    return 0;
}
/**
 *
 * @param client
 * @param name
 * @return
 */
int32_t sm_iot_device_remove(sm_device_shadown_t *client, char *name)
{
    if (client->device == NULL)
        return -1;
    sm_iot_device_t *node = client->device;
    sm_iot_device_t *node_next = node->next;

    if (strcmp (client->device->name, name) == 0)
    {
        client->device = client->device->next;
        free (node);
        return 0;
    }

    while (node_next != NULL)
    {
        if (strcmp (node_next->name, name) == 0)
        {
            node->next = node_next->next;
            free (node_next);
            return 0;
        }
        node = node_next;
        node_next = node_next->next;
    }
    return -1;
}
/**
 *
 * @param client
 * @return
 */
int32_t sm_iot_device_delete_all(sm_device_shadown_t *client)
{

    sm_iot_device_t *node = client->device;

    while (client->device != NULL)
    {
        node = client->device;
        client->device = client->device->next;
        free (node);
    }
    return 0;
}
/**
 *
 * @param client
 * @param name
 * @return
 */
int32_t sm_iot_device_connect(sm_device_shadown_t *client, char *name)
{
    sm_iot_device_t *device = sm_iot_device_search (client, name);
    if (device == NULL)
        return 1;
    if (sm_mqtt_client_get_state (client->base)
            == MQTT_ST_CONNECTED&& sm_iot_device_get_connected (client, name) == false)
    {

//        sm_mqtt_subscribes (client->base, device->topic.get_rejected_topic, 1);
//        sm_mqtt_subscribes (client->base, device->topic.get_accepted_topic, 1);
//        sm_mqtt_subscribes (client->base, device->topic.update_delta_topic, 1);
//        sm_mqtt_subscribes (client->base, device->topic.update_accepted_topic, 1);
//        sm_mqtt_subscribes (client->base, device->topic.update_rejected_topic, 1);
        sm_mqtt_subscribes (client->base, device->topic.delete_update_topic, 1);
        sm_mqtt_subscribes (client->base, device->topic.delete_rejected_topic, 1);
        device->connected = true;
        return 0;
    }
    return 2;
}
/**
 *
 * @param client
 * @param name
 * @return
 */
int32_t sm_iot_device_disconnect(sm_device_shadown_t *client, char *name)
{
    sm_iot_device_t *device = sm_iot_device_search (client, name);

    if (device == NULL)
        return 1;

    sm_mqtt_unsubscribes (client->base, device->topic.get_rejected_topic);
    sm_mqtt_unsubscribes (client->base, device->topic.get_accepted_topic);
    sm_mqtt_unsubscribes (client->base, device->topic.update_delta_topic);
    sm_mqtt_unsubscribes (client->base, device->topic.update_accepted_topic);
    sm_mqtt_unsubscribes (client->base, device->topic.update_rejected_topic);
    sm_mqtt_unsubscribes (client->base, device->topic.delete_update_topic);
    sm_mqtt_unsubscribes (client->base, device->topic.delete_rejected_topic);
    device->connected = false;
    return 0;
}
/**
 *
 * @param list
 * @param name
 * @return
 */
static sm_iot_device_t* iot_device_search(sm_iot_device_t *list, char *name)
{
    if (list == NULL)
        return NULL;

    if (strcmp (list->name, name) == 0)
    {
        return list;
    }
    return iot_device_search (list->next, name);
}
/**
 *
 * @param client
 * @param name
 * @return
 */
sm_iot_device_t* sm_iot_device_search(sm_device_shadown_t *client, char *name)
{
    return iot_device_search (client->device, name);
}

/**
 *
 * @param client
 * @return
 */
int32_t sm_iot_process(sm_device_shadown_t *client) {
	sm_mqtt_client_process(client->base);
	return 0;
}
/**
 *
 * @param client
 * @return
 */
int32_t sm_iot_deinit(sm_device_shadown_t *client) {
    sm_iot_device_delete_all (client);
    client->base = NULL;
	return 0;
}
/**
 *
 * @param client
 * @param event
 */
static void mqtt_event(sm_mqtt_client_t *client, sm_mqtt_client_event_t event) {
	sm_device_shadown_t *p_iot = (sm_device_shadown_t*) client->parent;
	switch (event) {
	case MQTT_EVENT_NONE:
		/* User code */
		break;
	case MQTT_EVENT_CLOSE:
		/* User code */

		break;
	case MQTT_EVENT_CONNECTED:
		/* User code */

		break;
	case MQTT_EVENT_DATA:
		/* User code */
//            printf("Topic: %s\r\n",client->topic);
//            printf("Data: %s\r\n",client->data);
            sm_iot_device_handle (p_iot, p_iot->device);
		break;
	case MQTT_EVENT_DISCONNECED:
		/* User code */
		break;
	case MQTT_EVENT_ERROR:
		/* User code */
		break;
	case MQTT_EVENT_OPEN:
		/* User code */
		break;
	default:
		break;
	}
}
/**
 *
 * @param client
 * @param device_name
 * @param stream
 * @return
 */
int32_t sm_iot_get(sm_device_shadown_t *client, char *device_name, void *stream)
{

    sm_iot_device_t *device = sm_iot_device_search (client, device_name);
    if (device != NULL)
        return sm_mqtt_publics (client->base, device->topic.get_topic, (char*) stream, strlen ((char*) stream), 1, 0);

    return -1;
}
/**
 *
 * @param client
 * @param device_name
 * @param stream
 * @return
 */
int32_t sm_iot_update(sm_device_shadown_t *client, char *device_name, void *stream)
{
    sm_iot_device_t *device = sm_iot_device_search (client, device_name);
    if (device != NULL)
        return sm_mqtt_publics (client->base, device->topic.update_topic, (char*) stream, strlen ((char*) stream), 1,
                                0);

    return -1;
}
/**
 *
 * @param client
 * @param device_name
 * @return
 */
int32_t sm_iot_delete(sm_device_shadown_t *client, char *device_name)
{
    sm_iot_device_t *device = sm_iot_device_search (client, device_name);
    if (device != NULL)
        return sm_mqtt_publics (client->base, device->topic.delete_topic, NULL, 0, 1, 0);

    return -1;
}
/**
 *
 * @param client
 * @param device
 */
static void sm_iot_device_handle(sm_device_shadown_t *client, sm_iot_device_t *device)
{
    if (device == NULL)
        return;
    if (device->callback != NULL)
    {
        device->data = client->base->data;
        if (strstr (client->base->topic, device->topic.get_accepted_topic) != NULL)
        {
            if (device->callback->get_accepted != NULL)
            {
                device->callback->get_accepted (device);
                return;
            }
        }
        else if (strstr (client->base->topic, device->topic.get_rejected_topic) != NULL)
        {
            if (device->callback->get_rejected != NULL)
            {
                device->callback->get_rejected (device);
                return;
            }
        }
        else if (strstr (client->base->topic, device->topic.update_delta_topic) != NULL)
        {
            if (device->callback->update != NULL)
            {
                device->callback->update (device);
                return;
            }
        }
        else if (strstr (client->base->topic, device->topic.update_accepted_topic) != NULL)
        {
            if (device->callback->update_accepted != NULL)
            {
                device->callback->update_accepted (device);
                return;
            }
        }
        else if (strstr (client->base->topic, device->topic.update_rejected_topic) != NULL)
        {
            if (device->callback->update_rejected != NULL)
            {
                device->callback->update_rejected (device);
                return;
            }
        }
        else if (strstr (client->base->topic, device->topic.delete_rejected_topic) != NULL)
        {
            if (device->callback->delete_rejected != NULL)
            {
                device->callback->delete_rejected (device);
                return;
            }
        }
        else if (strstr (client->base->topic, device->topic.delete_update_topic) != NULL)
        {
            if (device->callback->delete_updated != NULL)
            {
                device->callback->delete_updated (device);
                return;
            }
        }
    }
    sm_iot_device_handle (client, device->next);
}
/**
 *
 * @param client
 * @param device_name
 * @return
 */
bool sm_iot_device_get_connected(sm_device_shadown_t *client, char *device_name)
{
    sm_iot_device_t *device = sm_iot_device_search (client, device_name);
    if (device != NULL)
        return device->connected;
    return false;
}


#endif
