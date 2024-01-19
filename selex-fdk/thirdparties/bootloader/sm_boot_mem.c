/*
 * sm_boot_mem.c
 *
 *  Created on: Jul 18, 2023
 *      Author: Admin
 */

#include "sm_boot_mem.h"
#include "sm_bootloader.h"
#include "sm_bootloader_conf.h"

static sm_boot_memory_t *p_memories = NULL;
/**
 *
 * @param Address
 */
void sm_boot_mem_JumpToAddress(uint32_t Address){
    if(p_memories->JumpToAddress != NULL){
        p_memories->JumpToAddress(Address);
    }
}
/**
 *
 */
void sm_boot_mem_OptionBytesLaunch(void){

}
/**
 *
 * @param State
 */
void sm_boot_mem_SetReadOutProtection(int State){
        if(p_memories->SetReadoutProtect != NULL)
            p_memories->SetReadoutProtect(State);
}
/**
 *
 * @param Address
 * @param Data
 * @param DataLength
 */
void sm_boot_mem_Write(uint32_t Address, uint8_t *Data, uint32_t DataLength){

      if (p_memories->Write != NULL)
      {
          p_memories->Write(Address, Data, DataLength);
      }
}
/**
 *
 * @param Address
 * @param MemoryIndex
 * @return
 */
uint8_t sm_boot_mem_Read(uint32_t Address, uint32_t MemoryIndex){
    (void)MemoryIndex;
    uint8_t value;

    if (p_memories->Read != NULL)
    {
        value = p_memories->Read (Address);
    }
    else
    {
        value = 0;
    }
    return value;
}
/**
 *
 * @param Address
 * @return
 */
uint32_t sm_boot_mem_GetAddressArea(uint32_t Address){
    uint32_t mem_area = 0;

      if ((Address >= p_memories->StartAddress) && (Address < p_memories->EndAddress))
      {
        mem_area = p_memories->Type;
      }
      else
      {
        mem_area = 0;
      }

    return mem_area;
}
/**
 *
 * @param Address
 * @return
 */
uint32_t sm_boot_mem_GetMemoryIndex(uint32_t Address){
    uint32_t counter = 0;


    if ((Address >= p_memories->StartAddress) && (Address < p_memories->EndAddress))
    {
    }

    return counter;
}
/**
 *
 * @return
 */
int sm_boot_mem_GetReadOutProtectionStatus(void){
    int status;

    if (1==0)
    {
      status = 1;
    }
    else
    {
      status = 0;
    }

    return status;
}
/**
 *
 * @param Address
 * @param p_Data
 * @param DataLength
 * @return
 */
int sm_boot_mem_Erase(uint32_t Address, uint8_t *p_Data, uint32_t DataLength){
    (void)Address;
    int status;

    /* Get the memory index to know from which memory interface we will used */

    if (p_memories->Erase != NULL)
    {
        status = p_memories->Erase (p_Data, DataLength);
    }
    else
    {
        status = -1;
    }

    return status;
}
/**
 *
 * @param Address
 * @param p_Data
 * @param DataLength
 * @return
 */
int sm_boot_mem_MassErase(uint32_t Address, uint8_t *p_Data, uint32_t DataLength){
    (void) Address;
    int status;

    /* Get the memory index to know from which memory interface we will used */

    if (p_memories->MassErase != NULL)
    {
        status = p_memories->MassErase (p_Data, DataLength);
    }
    else
    {
        status = -1;
    }


    return status;
}
/**
 *
 * @param Memory
 * @return
 */
int sm_boot_mem_RegisterMemory(sm_boot_memory_t *Memory){
    int status = 0;
    p_memories->StartAddress = Memory->StartAddress;
    p_memories->EndAddress = Memory->EndAddress;
    p_memories->Size = Memory->Size;
    p_memories->Type = Memory->Type;
    p_memories->Read = Memory->Read;
    p_memories->Write = Memory->Write;
    p_memories->SetReadoutProtect = Memory->SetReadoutProtect;
    p_memories->SetWriteProtect = Memory->SetWriteProtect;
    p_memories->JumpToAddress = Memory->JumpToAddress;
    p_memories->MassErase = Memory->MassErase;
    p_memories->Erase = Memory->Erase;
    return status;
}
/**
 *
 * @param State
 * @param Address
 * @param Buffer
 * @param Length
 * @return
 */
int sm_boot_mem_SetWriteProtection(int State, uint32_t Address, uint8_t *Buffer, uint32_t Length){
    (void) Address;
    int status = 0;

    if (p_memories->SetWriteProtect != NULL)
    {
        p_memories->SetWriteProtect (State, Buffer, Length);
    }
    else
    {
        status = -1;
    }


    return status;
}
