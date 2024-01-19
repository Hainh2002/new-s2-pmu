/*
 * sm_bootloader_conf.h
 *
 *  Created on: Jul 19, 2023
 *      Author: Admin
 */

#ifndef COMMON_BOOTLOADER_SM_BOOTLOADER_CONF_H_
#define COMMON_BOOTLOADER_SM_BOOTLOADER_CONF_H_

#define DEVICE_ID_MSB                     0x04              /* MSB byte of device ID */
#define DEVICE_ID_LSB                     0x67              /* LSB byte of device ID */

/* -------------------------- Definitions for Memories ---------------------- */

#define FLASH_BASE                        0x00

#define FLASH_START_ADDRESS               FLASH_BASE
#define FLASH_END_ADDRESS                 (FLASH_BASE + (512 * 1024))

#define RAM_START_ADDRESS                 SRAM_BASE
#define RAM_END_ADDRESS                   (SRAM_BASE + (128 * 1024))   /* Size of SRAM 128kB */

#define OB_START_ADDRESS                  0x1FFF7800U                /* Option bytes registers address */
#define OB_END_ADDRESS                    0x1FFF787FU                /* Option bytes end address (128 bytes) */

#define OTP_START_ADDRESS                 0x1FFF7000U                   /* OTP registers address */
#define OTP_END_ADDRESS                   0x1FFF74FFU                   /* OTP end address (1024 bytes) */

#define ICP1_START_ADDRESS                0x1FFF0000U                  /* System memory registers address */
#define ICP1_END_ADDRESS                  0x1FFF6FFFU                  /* System memory registers end address */

#define ICP2_START_ADDRESS                0x1FFF8000U                  /* System memory registers address */
#define ICP2_END_ADDRESS                  0x1FFFEFFFU                  /* System memory registers end address */

#define EB_START_ADDRESS                  0x1FFF7500U                /* engi bytes start address */
#define EB_END_ADDRESS                    0x1FFF753FU                /* engi bytes end address  */

#define OPENBL_RAM_SIZE                   0x00003000U               /* RAM used by the Open Bootloader */

#define RDP_LEVEL_0                       OB_RDP_LEVEL_0
#define RDP_LEVEL_1                       OB_RDP_LEVEL_1
#define RDP_LEVEL_2                       OB_RDP_LEVEL_2

#define AREA_ERROR                        0x0U              /* Error Address Area */
#define FLASH_AREA                        0x1U              /* Flash Address Area */
#define RAM_AREA                          0x2U              /* RAM Address area */
#define OB_AREA                           0x3U              /* Option bytes Address area */
#define OTP_AREA                          0x4U              /* OTP Address area */
#define ICP1_AREA                         0x5U              /* System memory area */
#define ICP2_AREA                         0x6U              /* System memory area */
#define EB_AREA                           0x7U              /* Engi bytes Address area */

#define FLASH_MASS_ERASE                  0xFFFF
#define FLASH_BANK1_ERASE                 0xFFFE
#define FLASH_BANK2_ERASE                 0xFFFD

#define INTERFACES_SUPPORTED              6U

#endif /* COMMON_BOOTLOADER_SM_BOOTLOADER_CONF_H_ */
