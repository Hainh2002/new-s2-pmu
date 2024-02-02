#include <stdio.h>
#include <stdlib.h>

#include "sm_bsp_io.h"
#include "sm_hal_io.h"

#include "sm_porting.h"

static sm_hal_io_t* g_in_key;
static sm_hal_io_t* g_in_horn;
static sm_hal_io_t* g_in_phase_light;
static sm_hal_io_t* g_in_head_light;
static sm_hal_io_t* g_in_turn_left_light;
static sm_hal_io_t* g_in_turn_right_light;
static sm_hal_io_t* g_in_eco_sport;
static sm_hal_io_t* g_in_parking;
static sm_hal_io_t* g_out_phase_light;
static sm_hal_io_t* g_out_turn_left_light;
static sm_hal_io_t* g_out_turn_right_light;
static sm_hal_io_t* g_out_horn;
static sm_hal_io_t* g_out_charger;
static sm_hal_io_t* g_out_mc_power;
static sm_hal_io_t* g_out_can_mode;
static sm_hal_io_t* g_out_sw_12v;
static sm_hal_io_t* g_out_abp_charger;
static sm_hal_io_t* g_out_node_id_1;
static sm_hal_io_t* g_out_node_id_2;
static sm_hal_io_t* g_out_node_id_3;

int32_t sm_bsp_io_get_value_key(){
    g_in_key = sm_hal_io_init (&io_func, (void*) &g_ioport, 0x0408);
    sm_hal_io_open(g_in_key, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(g_in_key);
}
int32_t sm_bsp_io_get_value_horn(){
    g_in_horn = sm_hal_io_init (&io_func, (void*) &g_ioport, SM_BSP_IN_HORN);
    sm_hal_io_open(g_in_horn, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(g_in_horn);
}
int32_t sm_bsp_io_get_value_phase_light(){
    g_in_phase_light = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_IN_PHASE_LIGHT);
    sm_hal_io_open( g_in_phase_light, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value( g_in_phase_light);
}
int32_t sm_bsp_io_get_value_head_light(){
    g_in_head_light = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_IN_HEAD_LIGHT);
    sm_hal_io_open(g_in_head_light, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(g_in_head_light);
}
int32_t sm_bsp_io_get_value_turn_left_light(){
    g_in_turn_left_light     = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_IN_TURN_LEFT_LIGHT);
    sm_hal_io_open(g_in_turn_left_light, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(g_in_turn_left_light);
}
int32_t sm_bsp_io_get_value_turn_right_light(){
    g_in_turn_right_light    = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_IN_TURN_RIGHT_LIGHT);
    sm_hal_io_open(g_in_turn_right_light, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(g_in_turn_right_light);
}
int32_t sm_bsp_io_get_value_eco_sport(){
    g_in_eco_sport           = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_IN_ECO_SPORT);
    sm_hal_io_open(g_in_eco_sport, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(g_in_eco_sport);
}
int32_t sm_bsp_io_get_value_parking(){
    g_in_parking             = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_IN_PARKING);
    sm_hal_io_open(g_in_parking, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(g_in_parking);
}

int32_t sm_bsp_io_set_value_phase_light(uint8_t _level){
    g_out_phase_light        = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_PHASE_LIGHT);
    sm_hal_io_open(g_out_phase_light, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_phase_light, _level);
}
int32_t sm_bsp_io_set_value_turn_left_light(uint8_t _level){
    g_out_turn_left_light    = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_TURN_LEFT_LIGHT);
    sm_hal_io_open(g_out_turn_left_light, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_turn_left_light, _level);
}
int32_t sm_bsp_io_set_value_turn_right_light(uint8_t _level){
    g_out_turn_right_light   = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_TURN_RIGHT_LIGHT);
    sm_hal_io_open(g_out_turn_right_light, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_turn_right_light, _level);
}
int32_t sm_bsp_io_set_value_horn(uint8_t _level){
    g_out_horn               = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_HORN);
    sm_hal_io_open(g_out_horn, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_horn, _level);
}
int32_t sm_bsp_io_set_value_charger(uint8_t _level){
    g_out_charger            = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_CHARGER);
    sm_hal_io_open(g_out_charger, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_charger, _level);
}
int32_t sm_bsp_io_set_value_mc_power(uint8_t _level){
    g_out_mc_power           = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_MC_POWER);
    sm_hal_io_open(g_out_mc_power, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_mc_power, _level);
}
int32_t sm_bsp_io_set_value_can_mode(uint8_t _level){
    g_out_can_mode           = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_CAN_MODE);
    sm_hal_io_open(g_out_can_mode, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_can_mode, _level);
}
int32_t sm_bsp_io_set_value_sw_12v(uint8_t _level){
    g_out_sw_12v             = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_SW_12V);
    sm_hal_io_open(g_out_sw_12v, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_sw_12v, _level);
}
int32_t sm_bsp_io_set_value_abp_charger(uint8_t _level){
    g_out_abp_charger        = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_ABP_CHARGE);
    sm_hal_io_open(g_out_abp_charger, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_abp_charger, _level);
}
int32_t sm_bsp_io_set_value_node_id_1(uint8_t _level){
    g_out_node_id_1          = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_NODE_ID1);
    sm_hal_io_open(g_out_node_id_1, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_node_id_1, _level);
}
int32_t sm_bsp_io_set_value_node_id_2(uint8_t _level){
    g_out_node_id_2          = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_NODE_ID2);
    sm_hal_io_open(g_out_node_id_2, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_node_id_2, _level);
}
int32_t sm_bsp_io_set_value_node_id_3(uint8_t _level){
    g_out_node_id_3          = sm_hal_io_init (&io_func,(void*) &g_ioport, SM_BSP_OUT_NODE_ID3);
    sm_hal_io_open(g_out_node_id_3, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(g_out_node_id_3, _level);
}
