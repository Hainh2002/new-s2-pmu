/*
 * ota_app.c
 *
 *  Created on: Jul 26, 2023
 *      Author: Admin
 */

#include "http_app.h"
#include "sm_ec200s.h"

#include "app/hmi/hmi_app.h"

extern hmi_app_t hmi_app;

static int32_t http_open(sm_http_client_t *client)
{
    return sm_ec200_http_open (&hmi_app.ec200s, (char*) client->config->host);
}
static int32_t http_close(sm_http_client_t *client)
{
    (void) client;
    return sm_ec200_http_close (&hmi_app.ec200s);
}
static int32_t http_write(sm_http_client_t *client, uint8_t *data, uint32_t len)
{
    (void) client;
    return sm_ec200_http_write (&hmi_app.ec200s, (char*) data, len);
}
static uint32_t http_read(sm_http_client_t *client, uint8_t *data, uint32_t len)
{
    (void) client;
    return sm_ec200_http_read (&hmi_app.ec200s, (char*) data, len);
}
char http_buff[1024];
sm_http_client_t http_client;
sm_http_client_funtion_t http_client_fun =
{ .close = http_close, .open = http_open, .read = http_read, .write = http_write };
sm_http_client_config_t http_client_conf =
{ .host = "www.google.com", .path = "\0", .port = 80, .buff = http_buff, .buff_len = 1024, .method = HTTP_GET, .header =
NULL,
  .content = "\0" };

void ota_app_init()
{

    sm_ec200s_init (&ec200s, hmi_app.board.lte.lte_en, hmi_app.board.lte.lte_uart);
    sm_ec200s_set_apn (&ec200s, "m3-world", "mms", "mms");
    sm_ec200s_get_ip (&ec200s);

    sm_http_client_init (&http_client, &http_client_conf, &http_client_fun);
    if (sm_http_client_perform (&http_client) == 0)
    {

    }
}
