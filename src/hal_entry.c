#include "hal_data.h"
//#include "sm_bsp_io.h"
//#include "sm_bsp_peripherals.h"
//#include "sm_bsp_system.h"
#include "sm_porting.h"
#include "sm_hal_io.h"
FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
uint32_t key_value;
uint32_t time=0;
void hal_entry(void)
{
    /* TODO: add your own code here */
	R_IOPORT_Open (g_ioport.p_ctrl, g_ioport.p_cfg);
	sm_hal_io_t *in_key = sm_hal_io_init (&io_func, (void*)&g_ioport, 0x0408);
	while (1){
		R_BSP_SoftwareDelay(1000, BSP_DELAY_UNITS_MILLISECONDS);
		key_value = sm_hal_io_get_value(in_key);
		time++;
	}
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open (&g_ioport_ctrl, g_ioport.p_cfg);
    }
}


