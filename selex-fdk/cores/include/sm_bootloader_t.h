/*
 * sm_bootloader.h
 *
 *  Created on: Sep 11, 2023
 *      Author: MinhNhan
 */

#ifndef CORES_INCLUDE_SM_BOOTLOADER_T_H_
#define CORES_INCLUDE_SM_BOOTLOADER_T_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Exported constants --------------------------------------------------------*/
#define ERROR_COMMAND                     0xECU             /* Error command */
#define ACK_BYTE                          0x79U             /* Acknowledge Byte ID */
#define NACK_BYTE                         0x1FU             /* No Acknowledge Byte ID */
#define BUSY_BYTE                         0x76U             /* Busy Byte */
#define SYNC_BYTE                         0xA5U             /* synchronization byte */

/* ---------------------- Open Bootloader Commands ---------------------------*/
#define CMD_GET_COMMAND                   0x00U             /* Get commands command */
#define CMD_GET_VERSION                   0x01U             /* Get Version command */
#define CMD_GET_ID                        0x02U             /* Get ID command */
#define CMD_READ_MEMORY                   0x11U             /* Read Memory command */
#define CMD_WRITE_MEMORY                  0x31U             /* Write Memory command */
#define CMD_GO                            0x21U             /* GO command */
#define CMD_READ_PROTECT                  0x82U             /* Readout Protect command */
#define CMD_READ_UNPROTECT                0x92U             /* Readout Unprotect command */
#define CMD_EXT_ERASE_MEMORY              0x44U             /* Erase Memory command */
#define CMD_WRITE_PROTECT                 0x63U             /* Write Protect command */
#define CMD_WRITE_UNPROTECT               0x73U             /* Write Unprotect command */
#define CMD_NS_WRITE_MEMORY               0x32U             /* No Stretch Write Memory command */
#define CMD_NS_ERASE_MEMORY               0x45U             /* No Stretch Erase Memory command */
#define CMD_NS_WRITE_PROTECT              0x64U             /* No Stretch Write Protect command */
#define CMD_NS_WRITE_UNPROTECT            0x74U             /* No Stretch Write Unprotect command */
#define CMD_NS_READ_PROTECT               0x83U             /* No Stretch Read Protect command */
#define CMD_NS_READ_UNPROTECT             0x93U             /* No Stretch Read Unprotect command */
#define CMD_CHECKSUM                      0xA1U

typedef struct sm_bootloader sm_bootloader_t;

typedef struct sm_bootloader_if sm_bootloader_if_t;

struct sm_bootloader_if{
    void (*GetCommand)(sm_bootloader_t *_this);
    void (*GetVersion)(sm_bootloader_t *_this);
    void (*GetID)(sm_bootloader_t *_this);
    void (*ReadMemory)(sm_bootloader_t *_this);
    void (*WriteMemory)(sm_bootloader_t *_this);
    void (*Go)(sm_bootloader_t *_this);
    void (*ReadoutProtect)(sm_bootloader_t *_this);
    void (*ReadoutUnprotect)(sm_bootloader_t *_this);
    void (*EraseMemory)(sm_bootloader_t *_this);
    void (*WriteProtect)(sm_bootloader_t *_this);
    void (*WriteUnprotect)(sm_bootloader_t *_this);
    void (*NsWriteMemory)(sm_bootloader_t *_this);
    void (*NsEraseMemory)(sm_bootloader_t *_this);
    void (*NsWriteProtect)(sm_bootloader_t *_this);
    void (*NsWriteUnprotect)(sm_bootloader_t *_this);
    void (*NsReadoutProtect)(sm_bootloader_t *_this);
    void (*NsReadoutUnprotect)(sm_bootloader_t *_this);
};

struct sm_bootloader{
	struct boot_info{
	uint32_t block_count;
	uint32_t block_size;
	uint32_t start_addr;
	}*info;
	struct boot_function{
		int (*fl_erase)();
		int (*fl_write)(const void *buff,uint32_t addr,uint32_t size);
		int (*fl_read)(void *buff,uint32_t addr,uint32_t size);
		void (*jump)(uint32_t addr);

		uint8_t (*getc)();
		void (*putc)(char c);
	}*func;
	sm_bootloader_if_t *p_if;
};

/**
 * @brief
 * @param buff
 * @param length
 * @return  0: success | -1 : false
 */
uint16_t sm_crc16(uint8_t *buff,uint32_t length);
/**
 * @brief
 * @param p_boot
 * @param info
 * @param func
 */
void sm_boot_init(sm_bootloader_t *p_boot,struct boot_info *info,struct boot_function *func);
/**
 * @brief
 * @param p_boot
 */
void sm_boot_process(sm_bootloader_t *p_boot);
/**
 * @brief
 * @param _this
 * @return  0: success | -1 : false
 */
uint8_t sm_boot_get_command_opcode(sm_bootloader_t *_this);
/**
 * @brief
 * @param _this
 */
void sm_boot_get_command(sm_bootloader_t *_this);
/**
 * @brief
 * @param _this
 */
void sm_boot_get_version(sm_bootloader_t *_this);
/**
 * @brief
 * @param _this
 */
void sm_boot_get_id(sm_bootloader_t *_this);
/**
 * @brief
 * @param _this
 */
void sm_boot_read_memory(sm_bootloader_t *_this);
/**
 * @brief
 * @param _this
 */
void sm_boot_write_memory(sm_bootloader_t *_this);
/**
 * @brief
 * @param _this
 */
void sm_boot_erase_memory(sm_bootloader_t *_this);
/**
 * @brief
 * @param _this
 */
void sm_boot_go(sm_bootloader_t *_this);

#endif /* CORES_INCLUDE_SM_BOOTLOADER_T_H_ */
