/*
 * sm_filesystem.c
 *
 *  Created on: Jul 12, 2023
 *      Author: Admin
 */

#include <sm_filesystem.h>

lfs_t *lfs;

int sm_littlefs_flash_read (const struct lfs_config * c,
                            lfs_block_t               block,
                            lfs_off_t                 off,
                            void                    * buffer,
                            lfs_size_t                size);
int sm_littlefs_flash_write (const struct lfs_config * c,
                             lfs_block_t               block,
                             lfs_off_t                 off,
                             const void              * buffer,
                             lfs_size_t                size);
int sm_littlefs_flash_erase (const struct lfs_config * c, lfs_block_t block);
int sm_littlefs_flash_sync (const struct lfs_config * c);
/**
 *
 * @param file_sys
 * @return
 */
int sm_file_system_init(sm_file_sys_t *file_sys)
{
//    W25qxx_Begin (&flash->base, spi, nss);
//    if (W25qxx_Init (&flash->base) != true)
//    {
//        return LFS_ERR_IO;
//    }
    file_sys->p_config.read = &sm_littlefs_flash_read;
	file_sys->p_config.prog = &sm_littlefs_flash_write;
	file_sys->p_config.erase = &sm_littlefs_flash_erase;
	file_sys->p_config.sync = &sm_littlefs_flash_sync;
	file_sys->p_config.block_cycles = 1024;
	file_sys->p_config.cache_size = 64;
	file_sys->p_config.lookahead_size = 16;
	file_sys->p_config.read_size = 1;
	file_sys->p_config.prog_size = 1;
	file_sys->p_config.name_max = 24;
	file_sys->p_config.block_count = file_sys->block_count;
	file_sys->p_config.block_size = file_sys->block_size;
	file_sys->p_config.context = file_sys;
	lfs = &file_sys->p_lfs;
    int lfs_err = lfs_mount(&file_sys->p_lfs,&file_sys->p_config);
    if(lfs_err != LFS_ERR_OK){
        lfs_err = lfs_format(&file_sys->p_lfs,&file_sys->p_config);
        lfs_err = lfs_mount(&file_sys->p_lfs,&file_sys->p_config);
        lfs_err = lfs_mkdir(&file_sys->p_lfs, "SM:/");
    }
    return LFS_ERR_OK;
}
/**
 *
 * @param file_sys
 * @return
 */
int sm_file_switch_disk(sm_file_sys_t *file_sys){
	lfs = &file_sys->p_lfs;
	return 0;
}
/**
 *
 * @param c
 * @param block
 * @param off
 * @param buffer
 * @param size
 * @return
 */
int sm_littlefs_flash_read (const struct lfs_config * c,
                            lfs_block_t               block,
                            lfs_off_t                 off,
                            void                    * buffer,
                            lfs_size_t                size){

	sm_file_sys_t *file_sys = (sm_file_sys_t*) c->context;
	if(file_sys->func.read != NULL){
		int res = file_sys->func.read(buffer,block,off,size);
		return (res == 0 ? LFS_ERR_OK : LFS_ERR_INVAL);
	}

    return LFS_ERR_INVAL;
}
/**
 *
 * @param c
 * @param block
 * @param off
 * @param buffer
 * @param size
 * @return
 */
int sm_littlefs_flash_write (const struct lfs_config * c,
                             lfs_block_t               block,
                             lfs_off_t                 off,
                             const void              * buffer,
                             lfs_size_t                size){

	sm_file_sys_t *file_sys = (sm_file_sys_t*) c->context;
	if(file_sys->func.write != NULL){
		int res = file_sys->func.write(buffer,block,off,size);
		return (res == 0 ? LFS_ERR_OK : LFS_ERR_INVAL);
	}
    return LFS_ERR_INVAL;
}
/**
 *
 * @param c
 * @param block
 * @return
 */
int sm_littlefs_flash_erase (const struct lfs_config * c, lfs_block_t block){

	sm_file_sys_t *file_sys = (sm_file_sys_t*) c->context;
	if(file_sys->func.erase != NULL){
		int res = file_sys->func.erase(block);
		return (res == 0 ? LFS_ERR_OK : LFS_ERR_INVAL);
	}
    return LFS_ERR_INVAL;
}
/**
 *
 * @param c
 * @return
 */
int sm_littlefs_flash_sync (const struct lfs_config * c){
    (void)(c);
    return LFS_ERR_OK;
}
