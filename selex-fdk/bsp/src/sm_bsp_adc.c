#include <stdlib.h>
#include <sm_hal_adc.h>
#include <sm_bsp_peripherals.h>

static sm_hal_adc_t* g_in_charger;
static sm_hal_adc_t* g_in_abp;
sm_bsp_adc_t sm_bsp_adc_read_charger_voltage(){
    g_in_charger  = sm_hal_adc_init(&adc_func, (void*)&g_adc0, 1);
    sm_hal_adc_open(g_in_charger);
    return sm_hal_adc_read(g_in_charger, ADC_CHANNEL_16);
}

sm_bsp_adc_t sm_bsp_adc_read_abp_voltage(){
    g_in_abp      = sm_hal_adc_init(&adc_func, (void*)&g_adc0, 1);
    sm_hal_adc_open(g_in_abp);
    return sm_hal_adc_read(g_in_abp, ADC_CHANNEL_11);
}
