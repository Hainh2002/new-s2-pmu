/*
 * sm_bootmaster.h
 *
 *  Created on: Jul 24, 2023
 *      Author: Admin
 */

#ifndef CORES_INCLUDE_SM_BOOTMASTER_H_
#define CORES_INCLUDE_SM_BOOTMASTER_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum BOOT_STATE_t BOOT_STATE;
enum BOOT_STATE_t
{
    BOOT_ST_INIT = 0,
    BOOT_ST_PREPARING,
    BOOT_ST_LOADING_SERVER,
    BOOT_ST_LOADING_LOCAL,
    BOOT_ST_DOWNLOAD_COMPLETED,
    BOOT_ST_FINISH,
    BOOT_ST_FAIL,
    BOOT_ST_VALIDATING,
    BOOT_ST_WAITING_EXT_BOOT,
    BOOT_ST_WRITE_VERSION,
    BOOT_ST_READ_INFO,
    BOOT_ST_PRE_INIT
};

typedef struct sm_boot_master sm_boot_master_t;

struct sm_boot_master
{

    uint32_t boot_id_src;                // Node ID of CAN

    struct Signature_t
    {
        uint8_t version[3];
        uint32_t addr;
        uint32_t size;
        uint16_t crc;
        bool is_valid;
    };
    BOOT_STATE state;

};




#endif /* CORES_INCLUDE_SM_BOOTMASTER_H_ */
