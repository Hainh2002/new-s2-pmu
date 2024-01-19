/*
 * sm_bsp_peripherals.h
 *
 *  Created on: Dec 25, 2023
 *      Author: hainh
 */

#ifndef BSP_INCLUDE_SM_BSP_PERIPHERALS_H_
#define BSP_INCLUDE_SM_BSP_PERIPHERALS_H_

#include <stdint.h>
#include <stdlib.h>

#include "hal_data.h"

#include "sm_hal_can.h"
#include "sm_hal_uart.h"
#include "sm_hal_timer.h"

#include "sm_porting.h"
/* ADC */
/**
 * @fn sm_bsp_adc_read_charger_voltage()
 * @brief
 *
 * @param
 * @return
 */
uint16_t sm_bsp_adc_read_charger_voltage();
/**
 * @fn sm_bsp_adc_read_charger_voltage()
 * @brief
 *
 * @param
 * @return
 */
uint16_t sm_bsp_adc_read_abp_voltage();

/* CAN */
typedef func_can_rx_callback sm_bsp_can_rx_irq_fn_t;
/**
 * @fn sm_bsp_can_init()
 * @brief
 *
 * @param
 * @return
 */
int32_t sm_bsp_can_init();
/**
 * @fn sm_bsp_can_send(uint32_t _id, uint8_t *_tx_buffer, uint8_t _len)
 * @brief
 *
 * @param _id
 * @param _tx_buffer
 * @param _len
 * @return 0 success | -1 error
 */
int32_t sm_bsp_can_send(uint32_t _id, uint8_t *_tx_buffer, uint8_t _len);
/**
 * @fn sm_bsp_can_set_receive_handle(sm_hal_can_t *_can,void (*_handler)(sm_hal_can_t *_can))
 * @brief
 *
 * @param _can
 * @param _handler
 * @return
 */
void sm_bsp_can_set_receive_handle(sm_bsp_can_rx_irq_fn_t _can_receive_handle);

/* UART */
typedef sm_hal_uart_rx_irq sm_bsp_uart_rx_irq_fn_t;
/**
 * @fn sm_bsp_uart_init(uint32_t _baudrate, uint32_t _databit, uint32_t _parity)
 * @brief
 *
 * @param _baudrate
 * @param _databit
 * @param _parity
 * @return
 */
int32_t sm_bsp_uart_init(uint32_t _baudrate, uint32_t _databit, uint32_t _parity);
/**
 * @fn sm_bsp_uart_send(uint8_t *_tx_buffer, uint8_t _len)
 * @brief
 *
 * @param tx_buffer
 * @param len
 * @return 0 success | -1 error
 */
int32_t sm_bsp_uart_send(uint8_t *_tx_buffer, uint8_t _len);
/**
 * @fn void sm_bsp_uart_set_receive_handle(sm_bsp_uart_rx_irq _uart_receive_handle)
 * @brief
 *
 * @param _uart
 * @param _handler
 * @return
 */
void sm_bsp_uart_set_receive_handle(sm_bsp_uart_rx_irq_fn_t _uart_receive_handle);


/* TIMER */
typedef timerfuntion_t sm_bsp_timer_irq_fn_t;
/**
 * @fn sm_bsp_timer_1ms_init()
 * @brief
 *
 * @param
 * @return
 */
void sm_bsp_timer_1ms_init();
/**
 * @fn sm_bsp_timer_10ms_init()
 * @brief
 *
 * @param
 * @return
 */
void sm_bsp_timer_10ms_init();
/**
 * @fn sm_bsp_timer_1ms_set_irq_handle(void (*_handler)(void))
 * @brief
 *
 * @param _timer
 * @param _handler
 * @return
 */
void sm_bsp_timer_1ms_set_irq_handle(sm_bsp_timer_irq_fn_t _1ms_irq_handle);
/**
 * @fn sm_bsp_timer_10ms_set_irq_handle(void (*_handler)(void))
 * @brief
 *
 * @param _timer
 * @param _handler
 * @return
 */
void sm_bsp_timer_10ms_set_irq_handle(sm_bsp_timer_irq_fn_t _10ms_irq_handle);

/* IWDG */
/**
 * @fn sm_bsp_iwdg_open()
 * @brief
 *
 * @param _iwdg
 * @return
 */
int32_t sm_bsp_iwdg_start();
/**
 * @fn sm_bsp_iwdg_close()
 * @brief
 *
 * @param _iwdg
 * @return
 */
int32_t sm_bsp_iwdg_close();
/**
 * @fn sm_bsp_iwdg_reset()
 * @brief
 *
 * @param _iwdg
 * @return
 */
int32_t sm_bsp_iwdg_reset();

/* PWM */

/* SPI */

/* IIC */

/* SPI */

/* USB */

#endif /* BSP_INCLUDE_SM_BSP_PERIPHERALS_H_ */
