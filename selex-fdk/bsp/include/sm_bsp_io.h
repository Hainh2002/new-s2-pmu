/*
 * sm_bsp_io.h
 *
 *  Created on: Dec 25, 2023
 *      Author: hainh
 */

#ifndef SM_BSP_IO_H
#define SM_BSP_IO_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdlib.h>

#include "r_ioport.h"
#include "hal_data.h"

#include "sm_hal_io.h"

#include "sm_porting.h"


#define    IN_KEY                   IOPORT_PORT_04_PIN_08
#define    IN_HORN                  IOPORT_PORT_04_PIN_07
#define    IN_PHASE_LIGHT           IOPORT_PORT_04_PIN_09
#define    IN_HEAD_LIGHT            IOPORT_PORT_02_PIN_00
#define    IN_TURN_LEFT_LIGHT       IOPORT_PORT_03_PIN_01
#define    IN_TURN_RIGHT_LIGHT      IOPORT_PORT_00_PIN_15
#define    IN_ECO_SPORT             IOPORT_PORT_02_PIN_06
#define    IN_PARKING               IOPORT_PORT_02_PIN_07

#define    OUT_PHASE_LIGHT          IOPORT_PORT_00_PIN_00
#define    OUT_TURN_LEFT_LIGHT      IOPORT_PORT_04_PIN_02
#define    OUT_TURN_RIGHT_LIGHT     IOPORT_PORT_01_PIN_09
#define    OUT_HORN                 IOPORT_PORT_00_PIN_01
#define    OUT_CHARGER              IOPORT_PORT_00_PIN_02
#define    OUT_MC_POWER             IOPORT_PORT_00_PIN_14
#define    OUT_CAN_MODE             IOPORT_PORT_02_PIN_01
#define    OUT_SW_12V               IOPORT_PORT_01_PIN_00
#define    OUT_NODE_ID1             IOPORT_PORT_01_PIN_11
#define    OUT_NODE_ID2             IOPORT_PORT_01_PIN_04
#define    OUT_NODE_ID3             IOPORT_PORT_01_PIN_12
#define    OUT_ABP_CHARGE           IOPORT_PORT_03_PIN_02

#define    SM_BSP_IO_OFF            0
#define    SM_BSP_IO_ON             1


/**
 * @fn sm_bsp_io_get_value_key()
 * @brief
 * sm_bsp_io_get_value_key
 * @param
 * @return 0 | 1
 */
int32_t sm_bsp_io_get_value_key();
/**
 * @fn sm_bsp_io_get_value_horn()
 * @brief
 * sm_bsp_io_get_value_horn
 * @param
 * @return
 */
int32_t sm_bsp_io_get_value_horn();
/**
 * @fn sm_bsp_io_get_value_phase_light()
 * @brief
 * sm_bsp_io_get_value_phase_light
 * @param
 * @return
 */
int32_t sm_bsp_io_get_value_phase_light();
/**
 * @fn sm_bsp_io_get_value_head_light()
 * @brief
 * sm_bsp_io_get_value_head_light
 * @param
 * @return
 */
int32_t sm_bsp_io_get_value_head_light();
/**
 * @fn sm_bsp_io_get_value_turn_left_light()
 * @brief
 * sm_bsp_io_get_value_turn_left_light
 * @param
 * @return
 */
int32_t sm_bsp_io_get_value_turn_left_light();
/**
 * @fn sm_bsp_io_get_value_turn_right_light()
 * @brief
 * sm_bsp_io_get_value_turn_right_light
 * @param
 * @return
 */
int32_t sm_bsp_io_get_value_turn_right_light();
/**
 * @fn sm_bsp_io_get_value_eco_sport()
 * @brief
 * sm_bsp_io_get_value_eco_sport
 * @param
 * @return
 */
int32_t sm_bsp_io_get_value_eco_sport();
/**
 * @fn sm_bsp_io_get_value_parking()
 * @brief
 * sm_bsp_io_get_value_parking
 * @param
 * @return
 */
int32_t sm_bsp_io_get_value_parking();
/**
 * @fn sm_bsp_io_get_value_abp_charger()
 * @brief
 * sm_bsp_io_get_value_abp_charger
 * @param
 * @return
 */
int32_t sm_bsp_io_get_value_abp_charger();

/**
 * @fn sm_bsp_io_set_value_phase_light(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_phase_light
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_phase_light(uint8_t _level);
/**
 * @fn sm_bsp_io_set_value_turn_left_light(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_turn_left_light
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_turn_left_light(uint8_t _level);
/**
 * @fn sm_bsp_io_set_value_turn_right_light(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_turn_right_light
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_turn_right_light(uint8_t _level);
/**
 * @fn sm_bsp_io_set_value_horn(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_horn
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_horn(uint8_t _level);
/**
 * @fn sm_bsp_io_set_value_charger(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_charger
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_charger(uint8_t _level);
/**
 * @fn sm_bsp_io_set_value_mc_power(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_mc_power
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_mc_power(uint8_t _level);
/**
 * @fn sm_bsp_io_set_value_can_mode(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_can_mode
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_can_mode(uint8_t _level);
/**
 * @fn sm_bsp_io_set_value_abp_charger(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_abp_charger
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_abp_charger(uint8_t _level);
/**
 * @fn sm_bsp_io_set_value_abp_charger(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_abp_charger
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_sw_12v(uint8_t _level);
/**
 * @fn  sm_bsp_io_set_value_node_id_1(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_node_id_1
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_node_id_1(uint8_t _level);
/**
 * @fn sm_bsp_io_set_value_node_id_2(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_node_id_2
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_node_id_2(uint8_t _level);
/**
 * @fn sm_bsp_io_set_value_node_id_3(uint8_t _level)
 * @brief
 * sm_bsp_io_set_value_node_id_3
 * @param _level
 * @return
 */
int32_t sm_bsp_io_set_value_node_id_3(uint8_t _level);


#ifdef __cplusplus
};
#endif

#endif //SM_BSP_IO_H
