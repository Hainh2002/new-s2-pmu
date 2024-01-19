#include <sm_hal_iwdg.h>

static int32_t iwdg_open(sm_hal_iwdg_t *_this);
static int32_t iwdg_close(sm_hal_iwdg_t *_this);
static int32_t iwdg_reset(sm_hal_iwdg_t *_this);

sm_hal_iwdg_proc_t iwdg_fun = {.open = iwdg_open,.close = iwdg_close,.reset = iwdg_reset};


static int32_t iwdg_open(sm_hal_iwdg_t *_this)
{
    return HAL_IWDG_Init(_impl(_this->handle));
}
static int32_t iwdg_close(sm_hal_iwdg_t *_this)
{
    return -1;
}
static int32_t iwdg_reset(sm_hal_iwdg_t *_this)
{
    return HAL_IWDG_Refresh(_impl(_this->handle));
}
