/*
 * app_co_init.c
 *
 *  Created on: Jun 17, 2022
 *      Author: Dakaka
 */

#include "app_co_init.h"
#include "app/canopen_app/od/od.h"
#include <stdbool.h>
#include "sm_bsp_can.h"
#include "sm_bsp_flash.h"


CO app_co;

sm_bsp_can_t *can_if;

/********************************************************************************************
 * 									MANDATORY: Edit carefully !!!
 * *******************************************************************************************/
/* Declare for build TPDO message function when using "tpdo_build_data_manually" mode*/

void app_co_set_can_baudrate_impl(uint32_t br_khz);
void app_co_flash_error_handle_impl(void);
int8_t app_co_erase_and_write_data_to_flash_impl(uint32_t addr, uint32_t buff,
        uint32_t len);

static void tpdo1_build_data_impl(uint8_t *buffer);
static void tpdo2_build_data_impl(uint8_t *buffer);
static void tpdo3_build_data_impl(uint8_t *buffer);
static void tpdo4_build_data_impl(uint8_t *buffer);

void *tpdo_build_data_impl[TPDO_NUMBER] = { tpdo1_build_data_impl,
		tpdo2_build_data_impl, tpdo3_build_data_impl, tpdo4_build_data_impl };
/**
 *
 * @param buffer
 */
static void tpdo1_build_data_impl(uint8_t *buffer) {
	(void) buffer;
}
/**
 *
 * @param buffer
 */
static void tpdo2_build_data_impl(uint8_t *buffer) {
	(void) buffer;
}
/**
 *
 * @param buffer
 */
static void tpdo3_build_data_impl(uint8_t *buffer) {
	(void) buffer;
}
/**
 *
 * @param buffer
 */
static void tpdo4_build_data_impl(uint8_t *buffer) {
	(void) buffer;
}

/* Define can_send message function */
/**
 *
 * @param p_msg
 */
static void app_co_can_send_impl(CO_CAN_Msg *p_msg) {
    sm_bsp_can_mgs_t msg;
    msg.id = p_msg->id.cob_id;
    msg.length = p_msg->data_len;
    memcpy(msg.data,p_msg->data,msg.length);
    sm_bsp_can_write(can_if,&msg);
}
/**
 *
 */
void app_co_process(void){
    sm_bsp_can_mgs_t msg;
    if( sm_bsp_can_read(can_if, &msg) == 1){
        uint32_t cob_id = msg.id;
        if (CO_can_receive_basic_handle(&CO_DEVICE, cob_id, msg.data)
                == 1) {
        }
        /* USER CODE BEGIN */

        /* USER CODE END */
    }
}

/* Define erase_and_write_data_to_flash function
 * Return: success(0), fail(-1)
 */
/**
 *
 * @param addr
 * @param buff
 * @param len
 * @return
 */
int8_t app_co_erase_and_write_data_to_flash_impl(uint32_t addr, uint32_t buff,
		uint32_t len) {

	return 0;
}

/* Define flash_error_handle function */
/**
 *
 */
void app_co_flash_error_handle_impl(void) {

}

/* Define set CAN baud-rate function */
/**
 *
 * @param br_khz
 */
void app_co_set_can_baudrate_impl(uint32_t br_khz) {
    sm_bsp_can_set_baudrate(can_if, br_khz);
}
/**
 *
 */
void app_co_init(void) {
	/* [Mandatory] Set CO_CAN_send interface */
	CO_CAN_set_can_send_interface(app_co_can_send_impl);
	/* [Mandatory] Init CO object */
#if CO_FLASH__USE
	CO_FLASH_init(&CO_DEVICE.flash,
			app_co_erase_and_write_data_to_flash_impl,
			app_co_flash_error_handle_impl);
#endif
#if APP_OD_STORAGE__USE
#if CO_FLASH__USE & (SW_VERSION != 0)
	CO_OD_STORAGE_init(&CO_DEVICE.storage,
			APP_OD_STORAGE__STORAGE_REGION__ADDR,
			APP_OD_STORAGE__STORAGE_REGION__SIZE,
			&od_temp_comm_profile_para,
			&od_temp_manu_profile_para,
			sizeof(OD_Temp_Manufacturer_Profile_Para_t),
			&CO_DEVICE.flash,
			p_co_od,
			SW_VERSION,
			IS_MAIN_APP);
#else
	while(1); /* Code fail */
#endif
#endif

	CO_init_basic(&CO_DEVICE, od_temp_comm_profile_para.x1000_device_type,
			&od_temp_comm_profile_para.x1018_identity, p_co_od);

	CO_SYNC_init(&CO_DEVICE.sync, &od_temp_comm_profile_para);

	for (uint8_t i = 0; i < TPDO_NUMBER; i++) {
		CO_TPDO_init(&CO_DEVICE.tpdos[i], &CO_DEVICE.sync,
				&od_temp_comm_profile_para.x1A0x_tpdo_map_para[i],
				CO_DEVICE.p_od,
				&od_temp_comm_profile_para.x180x_tpdo_comm_para[i],
				tpdo_build_data_impl[i]);
	}
	CO_SDOserver_init(&CO_DEVICE.sdo_server, &od_temp_comm_profile_para,
			&CO_DEVICE.sync,
			CO_DEVICE.p_od);
	CO_SDOclient_init(&CO_DEVICE.sdo_client, &od_temp_comm_profile_para,
			&CO_DEVICE.sync);

	CO_set_node_id(&CO_DEVICE, od_temp_manu_profile_para.x500300_node_ID);
	app_co_set_can_baudrate_impl(
			od_temp_manu_profile_para.x500301_baud_rate_kHz);

	/* USER CODE BEGIN */

	/* USER CODE END */
}

/********************************************************************************************
 * 									USER CODE
 * *******************************************************************************************/
/*void co_send_ex_boot_request(CAN_Hw *p_hw){
    p_hw->tx_msg.identifier = 0x02;
    p_hw->tx_msg.data[0] = 1;
    p_hw->tx_msg.data_length_code = 1;
    p_hw->send(p_hw);
}*/
