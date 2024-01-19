/*
 * sm_boot_mem.h
 *
 *  Created on: Jul 18, 2023
 *      Author: Admin
 */

#ifndef COMMON_BOOTLOADER_SM_BOOT_MEM_H_
#define COMMON_BOOTLOADER_SM_BOOT_MEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
  uint32_t  StartAddress;
  uint32_t  EndAddress;
  uint32_t  Size;
  uint32_t  Type;
  uint8_t   (*Read)(uint32_t Address);
  void      (*Write)(uint32_t Address, uint8_t *Data, uint32_t DataLength);
  void      (*SetReadoutProtect)(uint32_t State);
  int32_t   (*SetWriteProtect)(int State, uint8_t *Buffer, uint32_t Length);
  void      (*JumpToAddress)(uint32_t Address);
  int32_t   (*MassErase)(uint8_t *p_Data, uint32_t DataLength);
  int32_t   (*Erase)(uint8_t *p_Data, uint32_t DataLength);
} sm_boot_memory_t;

void sm_boot_mem_JumpToAddress(uint32_t Address);
void sm_boot_mem_OptionBytesLaunch(void);
void sm_boot_mem_SetReadOutProtection(int State);
void sm_boot_mem_Write(uint32_t Address, uint8_t *Data, uint32_t DataLength);

uint8_t sm_boot_mem_Read(uint32_t Address, uint32_t MemoryIndex);
uint32_t sm_boot_mem_GetAddressArea(uint32_t Address);
uint32_t sm_boot_mem_GetMemoryIndex(uint32_t Address);

int sm_boot_mem_GetReadOutProtectionStatus(void);

int sm_boot_mem_Erase(uint32_t Address, uint8_t *p_Data, uint32_t DataLength);
int sm_boot_mem_MassErase(uint32_t Address, uint8_t *p_Data, uint32_t DataLength);
int sm_boot_mem_RegisterMemory(sm_boot_memory_t *Memory);
int sm_boot_mem_SetWriteProtection(int State, uint32_t Address, uint8_t *Buffer, uint32_t Length);

#endif /* COMMON_BOOTLOADER_SM_BOOT_MEM_H_ */
