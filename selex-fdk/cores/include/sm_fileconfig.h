/*
 * sm_fileconfig.h
 *
 *  Created on: Jul 12, 2023
 *      Author: Admin
 */

#ifndef CORES_FS_SM_FILECONFIG_H_
#define CORES_FS_SM_FILECONFIG_H_

#include "lfs.h"
#include "lfs_util.h"
#include <stdio.h>
#include <sm_filesystem.h>

extern lfs_t *lfs;


#define MBEDTLS_CONFIG_LFS    lfs

static inline FILE * rm_littlefs_fopen (const char * path, const char * mode)
{
    /* Allocate a LittleFS file instance. */
    lfs_file_t * file = malloc(sizeof(lfs_file_t));
    int          lfs_status;
    if (NULL != file)
    {
        /* Check if the file is being opened for read or write and set the LittleFS flags. */
        int flags = ('r' == mode[0]) ? LFS_O_RDONLY : LFS_O_WRONLY | LFS_O_CREAT;

        lfs_status = lfs_file_open(MBEDTLS_CONFIG_LFS, file, path, flags);

        /* If the file failed to open free the memory and return NULL. */
        if (lfs_status != LFS_ERR_OK)
        {
            free(file);
            file = NULL;
        }
    }

    return (FILE *) file;
}
static inline int sm_fs_puts(char *s, lfs_file_t* file){
    return lfs_file_write(MBEDTLS_CONFIG_LFS, (lfs_file_t *) file,(void*) s, sizeof(char) * strlen(s));
}
/* Use the above inline function to replace fopen. */
#define fopen    rm_littlefs_fopen

#define fwrite(data, n, len, stream)    lfs_file_write(MBEDTLS_CONFIG_LFS, (lfs_file_t *) stream, data, n * len)

#define fread(data, n, len, stream)     lfs_file_read(MBEDTLS_CONFIG_LFS, (lfs_file_t *) stream, data, n * len)

#define fseek(stream, offset,                                                                              \
              seek)                     ((lfs_file_seek(MBEDTLS_CONFIG_LFS, (lfs_file_t *) stream, offset, \
                                                        seek) >= 0) ? 0 : -1)

#define remove(file)                    lfs_remove(MBEDTLS_CONFIG_LFS, file)

/* Free the memory associated with this file after it is closed. */
#define fclose(stream)                  lfs_file_close(MBEDTLS_CONFIG_LFS, (lfs_file_t *) stream); free(stream)

#define rename(oldpath, newpath)        lfs_rename(MBEDTLS_CONFIG_LFS, oldpath, newpath)

#define fputs(data,stream)              sm_fs_puts(data,(lfs_file_t *) stream)
#endif /* CORES_FS_SM_FILECONFIG_H_ */
