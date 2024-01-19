/*
 * sm_filesystem.h
 *
 *  Created on: Jul 12, 2023
 *      Author: Admin
 */

#ifndef CORES_FS_SM_FILESYSTEM_H_
#define CORES_FS_SM_FILESYSTEM_H_

//#include <sm_fileconfig.h>
#include <sm_hal_flash.h>
#include <sm_hal_io.h>
#include <sm_hal_spi.h>
#include "lfs.h"
#include "lfs_util.h"
#include "sm_spi_flash.h"

typedef struct sm_file_sys {

	lfs_t p_lfs;
	struct lfs_config p_config;
	uint32_t block_size;
	uint32_t block_count;

	struct sm_file_func {
		int (*erase)(uint32_t block);
		int (*write)(const void *buff, uint32_t block, uint32_t off, uint32_t size);
		int (*read)(void *buff, uint32_t block, uint32_t off, uint32_t size);
	} func;

} sm_file_sys_t;
/**
 * @brief
 * @param file_sys
 * @return
 */
int sm_file_system_init(sm_file_sys_t *file_sys);
/**
 * @brief
 * @param file_sys
 * @return
 */
int sm_file_switch_disk(sm_file_sys_t *file_sys);
#endif /* CORES_FS_SM_FILESYSTEM_H_ */
