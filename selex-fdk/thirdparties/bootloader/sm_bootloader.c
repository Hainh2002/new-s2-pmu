/*
 * sm_bootloader.c
 *
 *  Created on: Jul 18, 2023
 *      Author: Admin
 */


#include "sm_bootloader.h"

static uint32_t NumberOfInterfaces = 0U;
static sm_bootloader_t a_InterfacesTable[INTERFACES_SUPPORTED];
static sm_bootloader_t *p_Interface;
/**
 *
 */
void sm_boot_init(){
    uint32_t counter;

    for (counter = 0U; counter < NumberOfInterfaces; counter++)
    {
      if (a_InterfacesTable[counter].p_ops->Init != NULL)
      {
        a_InterfacesTable[counter].p_ops->Init();
      }
    }
}
/**
 *
 */
void sm_boot_deinit(){
    uint32_t counter;

    for (counter = 0U; counter < NumberOfInterfaces; counter++)
    {
      if (a_InterfacesTable[counter].p_ops->DeInit != NULL)
      {
        a_InterfacesTable[counter].p_ops->DeInit();
      }
    }
}
/**
 *
 * @return
 */
uint32_t sm_boot_detect_if(){
    uint32_t counter;
    uint8_t detected = 0U;

    for (counter = 0U; counter < NumberOfInterfaces; counter++)
    {
      if (a_InterfacesTable[counter].p_ops->Detection != NULL)
      {
        detected = a_InterfacesTable[counter].p_ops->Detection();

        if (detected == 1U)
        {
          p_Interface = &(a_InterfacesTable[counter]);
          break;
        }
      }
    }

    return detected;
}
/**
 *
 */
void sm_boot_process(){
    uint8_t command_opcode;

    /* Get the user command opcode */
    if (p_Interface->p_ops->GetCommandOpcode != NULL)
    {
      command_opcode = p_Interface->p_ops->GetCommandOpcode();

      switch (command_opcode)
      {
        case CMD_GET_COMMAND:
          if (p_Interface->p_if->GetCommand != NULL)
          {
            p_Interface->p_if->GetCommand();
          }
          break;

        case CMD_GET_VERSION:
          if (p_Interface->p_if->GetVersion != NULL)
          {
            p_Interface->p_if->GetVersion();
          }
          break;

        case CMD_GET_ID:
          if (p_Interface->p_if->GetID != NULL)
          {
            p_Interface->p_if->GetID();
          }

          break;

        case CMD_READ_MEMORY:
          if (p_Interface->p_if->ReadMemory != NULL)
          {
            p_Interface->p_if->ReadMemory();
          }
          break;

        case CMD_WRITE_MEMORY:
          if (p_Interface->p_if->WriteMemory != NULL)
          {
            p_Interface->p_if->WriteMemory();
          }
          break;

        case CMD_GO:
          if (p_Interface->p_if->Go != NULL)
          {
            p_Interface->p_if->Go();
          }
          break;

        case CMD_READ_PROTECT:
          if (p_Interface->p_if->ReadoutProtect != NULL)
          {
            p_Interface->p_if->ReadoutProtect();
          }
          break;

        case CMD_READ_UNPROTECT:
          if (p_Interface->p_if->ReadoutUnprotect != NULL)
          {
            p_Interface->p_if->ReadoutUnprotect();
          }
          break;

        case CMD_EXT_ERASE_MEMORY:
          if (p_Interface->p_if->EraseMemory != NULL)
          {
            p_Interface->p_if->EraseMemory();
          }
          break;

        case CMD_WRITE_PROTECT:
          if (p_Interface->p_if->WriteProtect != NULL)
          {
            p_Interface->p_if->WriteProtect();
          }
          break;

        case CMD_WRITE_UNPROTECT:
          if (p_Interface->p_if->WriteUnprotect != NULL)
          {
            p_Interface->p_if->WriteUnprotect();
          }
          break;

        case CMD_NS_WRITE_MEMORY:
          if (p_Interface->p_if->NsWriteMemory != NULL)
          {
            p_Interface->p_if->NsWriteMemory();
          }
          break;

        case CMD_NS_ERASE_MEMORY:
          if (p_Interface->p_if->NsEraseMemory != NULL)
          {
            p_Interface->p_if->NsEraseMemory();
          }
          break;

        case CMD_NS_WRITE_PROTECT:
          if (p_Interface->p_if->NsWriteProtect != NULL)
          {
            p_Interface->p_if->NsWriteProtect();
          }
          break;

        case CMD_NS_WRITE_UNPROTECT:
          if (p_Interface->p_if->NsWriteUnprotect != NULL)
          {
            p_Interface->p_if->NsWriteUnprotect();
          }
          break;

        case CMD_NS_READ_PROTECT:
          if (p_Interface->p_if->NsReadoutProtect != NULL)
          {
            p_Interface->p_if->NsReadoutProtect();
          }
          break;

        case CMD_NS_READ_UNPROTECT:
          if (p_Interface->p_if->NsReadoutUnprotect != NULL)
          {
            p_Interface->p_if->NsReadoutUnprotect();
          }
          break;

        /* Unknown command opcode */
        default:
          if (p_Interface->p_ops->SendByte != NULL)
          {
            p_Interface->p_ops->SendByte(NACK_BYTE);
          }
          break;
      }
    }
}
/**
 *
 * @param p_boot
 * @return
 */
int32_t sm_boot_register_interface(sm_bootloader_t *p_boot){
    int32_t status = 0;

    if (NumberOfInterfaces < INTERFACES_SUPPORTED)
    {
      a_InterfacesTable[NumberOfInterfaces].p_ops = p_boot->p_ops;
      a_InterfacesTable[NumberOfInterfaces].p_if = p_boot->p_if;

      NumberOfInterfaces++;
    }
    else
    {
      status = -1;
    }

    return status;
}
