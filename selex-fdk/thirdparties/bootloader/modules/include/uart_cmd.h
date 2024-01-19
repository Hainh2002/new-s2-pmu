/*
 * uart_cmd.h
 *
 *  Created on: Jul 18, 2023
 *      Author: Admin
 */

#ifndef COMMON_BOOTLOADER_MODULES_UART_CMD_H_
#define COMMON_BOOTLOADER_MODULES_UART_CMD_H_

#include "bootloader/sm_bootloader.h"


#define OPENBL_USART_VERSION                 0x31U               /* Open Bootloader USART protocol V3.1 */

extern sm_bootloader_if_t SM_BL_USART_Commands;

sm_bootloader_if_t *SM_BL_USART_GetCommandsList(void);


#endif /* COMMON_BOOTLOADER_MODULES_UART_CMD_H_ */
