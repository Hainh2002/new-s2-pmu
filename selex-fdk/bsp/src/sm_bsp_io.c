#include <stdio.h>
#include <stdlib.h>

#include "sm_bsp_io.h"
#include "sm_hal_io.h"

#include "sm_porting.h"

sm_hal_io_t* in_key;
sm_hal_io_t* in_horn;
sm_hal_io_t* in_phase_light;
sm_hal_io_t* in_head_light;
sm_hal_io_t* in_turn_left_light;
sm_hal_io_t* in_turn_right_light;
sm_hal_io_t* in_eco_sport;
sm_hal_io_t* in_parking;
sm_hal_io_t* out_phase_light;
sm_hal_io_t* out_turn_left_light;
sm_hal_io_t* out_turn_right_light;
sm_hal_io_t* out_horn;
sm_hal_io_t* out_charger;
sm_hal_io_t* out_mc_power;
sm_hal_io_t* out_can_mode;
sm_hal_io_t* out_sw_12v;
sm_hal_io_t* out_abp_charger;
sm_hal_io_t* out_node_id_1;
sm_hal_io_t* out_node_id_2;
sm_hal_io_t* out_node_id_3;

int32_t sm_bsp_io_get_value_key(){
    in_key = sm_hal_io_init (&io_func, (void*) &g_ioport, 0x0408);
    sm_hal_io_open(in_key, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(in_key);
}
int32_t sm_bsp_io_get_value_horn(){
    in_horn = sm_hal_io_init (&io_func, (void*) &g_ioport, IN_HORN);
    sm_hal_io_open(in_horn, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(in_horn);
}
int32_t sm_bsp_io_get_value_phase_light(){
    in_phase_light = sm_hal_io_init (&io_func,(void*) &g_ioport, IN_PHASE_LIGHT);
    sm_hal_io_open( in_phase_light, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value( in_phase_light);
}
int32_t sm_bsp_io_get_value_head_light(){
    in_head_light = sm_hal_io_init (&io_func,(void*) &g_ioport, IN_HEAD_LIGHT);
    sm_hal_io_open(in_head_light, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(in_head_light);
}
int32_t sm_bsp_io_get_value_turn_left_light(){
    in_turn_left_light     = sm_hal_io_init (&io_func,(void*) &g_ioport, IN_TURN_LEFT_LIGHT);

    sm_hal_io_open(in_turn_left_light, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(in_turn_left_light);
}
int32_t sm_bsp_io_get_value_turn_right_light(){
    in_turn_right_light    = sm_hal_io_init (&io_func,(void*) &g_ioport, IN_TURN_RIGHT_LIGHT);

    sm_hal_io_open(in_turn_right_light, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(in_turn_right_light);
}
int32_t sm_bsp_io_get_value_eco_sport(){
    in_eco_sport           = sm_hal_io_init (&io_func,(void*) &g_ioport, IN_ECO_SPORT);
    sm_hal_io_open(in_eco_sport, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(in_eco_sport);
}
int32_t sm_bsp_io_get_value_parking(){
    in_parking             = sm_hal_io_init (&io_func,(void*) &g_ioport, IN_PARKING);
    sm_hal_io_open(in_parking, SM_HAL_IO_INPUT);
    return sm_hal_io_get_value(in_parking);
}

int32_t sm_bsp_io_set_value_phase_light(uint8_t _level){
    out_phase_light        = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_PHASE_LIGHT);
    sm_hal_io_open(out_phase_light, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_phase_light, _level);
}
int32_t sm_bsp_io_set_value_turn_left_light(uint8_t _level){
    out_turn_left_light    = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_TURN_LEFT_LIGHT);
    sm_hal_io_open(out_turn_left_light, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_turn_left_light, _level);
}
int32_t sm_bsp_io_set_value_turn_right_light(uint8_t _level){
    out_turn_right_light   = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_TURN_RIGHT_LIGHT);
    sm_hal_io_open(out_turn_right_light, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_turn_right_light, _level);
}
int32_t sm_bsp_io_set_value_horn(uint8_t _level){
    out_horn               = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_HORN);
    sm_hal_io_open(out_horn, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_horn, _level);
}
int32_t sm_bsp_io_set_value_charger(uint8_t _level){
    out_charger            = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_CHARGER);
    sm_hal_io_open(out_charger, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_charger, _level);
}
int32_t sm_bsp_io_set_value_mc_power(uint8_t _level){
    out_mc_power           = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_MC_POWER);
    sm_hal_io_open(out_mc_power, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_mc_power, _level);
}
int32_t sm_bsp_io_set_value_can_mode(uint8_t _level){
    out_can_mode           = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_CAN_MODE);
    sm_hal_io_open(out_can_mode, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_can_mode, _level);
}
int32_t sm_bsp_io_set_value_sw_12v(uint8_t _level){
    out_sw_12v             = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_SW_12V);
    sm_hal_io_open(out_sw_12v, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_sw_12v, _level);
}
int32_t sm_bsp_io_set_value_abp_charger(uint8_t _level){
    out_abp_charger        = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_ABP_CHARGE);
    sm_hal_io_open(out_abp_charger, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_abp_charger, _level);
}
int32_t sm_bsp_io_set_value_node_id_1(uint8_t _level){
    out_node_id_1          = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_NODE_ID1);
    sm_hal_io_open(out_node_id_1, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_node_id_1, _level);
}
int32_t sm_bsp_io_set_value_node_id_2(uint8_t _level){
    out_node_id_2          = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_NODE_ID2);
    sm_hal_io_open(out_node_id_2, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_node_id_2, _level);
}
int32_t sm_bsp_io_set_value_node_id_3(uint8_t _level){
    out_node_id_3          = sm_hal_io_init (&io_func,(void*) &g_ioport, OUT_NODE_ID3);
    sm_hal_io_open(out_node_id_3, SM_HAL_IO_OUTPUT);
    return sm_hal_io_set_value(out_node_id_3, _level);
}
