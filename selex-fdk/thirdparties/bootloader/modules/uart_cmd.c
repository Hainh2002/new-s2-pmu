/*
 * uart_cmd.c
 *
 *  Created on: Jul 18, 2023
 *      Author: Admin
 */


#include "include/uart_cmd.h"
#include "bootloader/sm_bootloader.h"
#include "bootloader/sm_bootloader_conf.h"
#include "bootloader/sm_boot_mem.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define OPENBL_USART_COMMANDS_NB          11U       /* Number of supported commands */

#define USART_RAM_BUFFER_SIZE             1156U     /* Size of USART buffer used to store received data from the host */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Buffer used to store received data from the host */
static uint8_t USART_RAM_Buf[USART_RAM_BUFFER_SIZE];

/* Private function prototypes -----------------------------------------------*/
static void OPENBL_USART_GetCommand(void);
static void OPENBL_USART_GetVersion(void);
static void OPENBL_USART_GetID(void);
static void OPENBL_USART_ReadMemory(void);
static void OPENBL_USART_WriteMemory(void);
static void OPENBL_USART_Go(void);
static void OPENBL_USART_ReadoutProtect(void);
static void OPENBL_USART_ReadoutUnprotect(void);
static void OPENBL_USART_EraseMemory(void);
static void OPENBL_USART_WriteProtect(void);
static void OPENBL_USART_WriteUnprotect(void);

static uint8_t OPENBL_USART_GetAddress(uint32_t *Address);

extern void SM_BL_USART_SendByte(uint8_t byte);
extern uint8_t SM_BL_USART_ReadByte();
/* Exported variables --------------------------------------------------------*/
sm_bootloader_if_t SM_BL_USART_Commands =
{
  OPENBL_USART_GetCommand,
  OPENBL_USART_GetVersion,
  OPENBL_USART_GetID,
  OPENBL_USART_ReadMemory,
  OPENBL_USART_WriteMemory,
  OPENBL_USART_Go,
  OPENBL_USART_ReadoutProtect,
  OPENBL_USART_ReadoutUnprotect,
  OPENBL_USART_EraseMemory,
  OPENBL_USART_WriteProtect,
  OPENBL_USART_WriteUnprotect,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};
/**
 *
 * @return
 */
sm_bootloader_if_t *SM_BL_USART_GetCommandsList(void)
{
  return (&SM_BL_USART_Commands);
}
/**
 *
 */
static void OPENBL_USART_GetCommand(void)
{
  uint32_t counter;
  const uint8_t a_OPENBL_USART_CommandsList[OPENBL_USART_COMMANDS_NB] =
  {
    CMD_GET_COMMAND,
    CMD_GET_VERSION,
    CMD_GET_ID,
    CMD_READ_MEMORY,
    CMD_GO,
    CMD_WRITE_MEMORY,
    CMD_EXT_ERASE_MEMORY,
    CMD_WRITE_PROTECT,
    CMD_WRITE_UNPROTECT,
    CMD_READ_PROTECT,
    CMD_READ_UNPROTECT
  };

  /* Send Acknowledge byte to notify the host that the command is recognized */
  SM_BL_USART_SendByte(ACK_BYTE);

  /* Send the number of commands supported by the USART protocol */
  SM_BL_USART_SendByte(OPENBL_USART_COMMANDS_NB);

  /* Send USART protocol version */
  SM_BL_USART_SendByte(OPENBL_USART_VERSION);

  /* Send the list of supported commands */
  for (counter = 0U; counter < OPENBL_USART_COMMANDS_NB; counter++)
  {
      SM_BL_USART_SendByte(a_OPENBL_USART_CommandsList[counter]);
  }

  /* Send last Acknowledge synchronization byte */
  SM_BL_USART_SendByte(ACK_BYTE);
}
/**
 *
 */
static void OPENBL_USART_GetVersion(void)
{
  /* Send Acknowledge byte to notify the host that the command is recognized */
  SM_BL_USART_SendByte(ACK_BYTE);

  /* Send USART protocol version */
  SM_BL_USART_SendByte(OPENBL_USART_VERSION);

  SM_BL_USART_SendByte(0x00);
  SM_BL_USART_SendByte(0x00);

  /* Send last Acknowledge synchronization byte */
  SM_BL_USART_SendByte(ACK_BYTE);
}
/**
 *
 */
static void OPENBL_USART_GetID(void)
{
  /* Send Acknowledge byte to notify the host that the command is recognized */
  SM_BL_USART_SendByte(ACK_BYTE);

  SM_BL_USART_SendByte(0x01);

  /* Send the device ID starting by the MSB byte then the LSB byte */
  SM_BL_USART_SendByte(DEVICE_ID_MSB);
  SM_BL_USART_SendByte(DEVICE_ID_LSB);

  /* Send last Acknowledge synchronization byte */
  SM_BL_USART_SendByte(ACK_BYTE);
}
/**
 *
 */
static void OPENBL_USART_ReadMemory(void)
{
  uint32_t address;
  uint32_t counter;
  uint8_t data;
  uint8_t xor;

  /* Check memory protection then send adequate response */
  if (sm_boot_mem_GetReadOutProtectionStatus() != 0)
  {
    SM_BL_USART_SendByte(NACK_BYTE);
  }
  else
  {
    SM_BL_USART_SendByte(ACK_BYTE);

    /* Get the memory address */
    if (OPENBL_USART_GetAddress(&address) == NACK_BYTE)
    {
      SM_BL_USART_SendByte(NACK_BYTE);
    }
    else
    {
      SM_BL_USART_SendByte(ACK_BYTE);

      /* Get the number of bytes to be received */
      data = SM_BL_USART_ReadByte();
      xor  = ~data;

      /* Check data integrity */
      if (SM_BL_USART_ReadByte() != xor)
      {
        SM_BL_USART_SendByte(NACK_BYTE);
      }
      else
      {
        SM_BL_USART_SendByte(ACK_BYTE);

        /* Get the memory index to know from which memory we will read */

        /* Read the data (data + 1) from the memory and send them to the host */
        for (counter = ((uint32_t)data + 1U); counter != 0U; counter--)
        {
          SM_BL_USART_SendByte(sm_boot_mem_Read(address, 0));
          address++;
        }
      }
    }
  }
}

/**
 *
 */
static void OPENBL_USART_WriteMemory(void)
{
  uint32_t address;
  uint32_t tmpXOR;
  uint32_t counter;
  uint32_t codesize;
  uint32_t mem_area;
  uint8_t *ramaddress;
  uint8_t data;

  /* Check memory protection then send adequate response */
  if (sm_boot_mem_GetReadOutProtectionStatus() != 0)
  {
    SM_BL_USART_SendByte(NACK_BYTE);
  }
  else
  {
    SM_BL_USART_SendByte(ACK_BYTE);

    /* Get the memory address */
    if (OPENBL_USART_GetAddress(&address) == NACK_BYTE)
    {
      SM_BL_USART_SendByte(NACK_BYTE);
    }
    else
    {
      SM_BL_USART_SendByte(ACK_BYTE);

      /* Read number of bytes to be written and data */
      ramaddress = (uint8_t *)USART_RAM_Buf;

      /* Read the number of bytes to be written: Max number of data = data + 1 = 256 */
      data = SM_BL_USART_ReadByte();

      /* Number of data to be written = data + 1 */
      codesize = (uint32_t)data + 1U;

      /* Checksum Initialization */
      tmpXOR = data;

      /* UART receive data and send to RAM Buffer */
      for (counter = codesize; counter != 0U ; counter--)
      {
        data    = SM_BL_USART_ReadByte();
        tmpXOR ^= data;

        *(volatile uint8_t *)(ramaddress) = data;

        ramaddress++;
      }

      /* Send NACk if Checksum is incorrect */
      if (SM_BL_USART_ReadByte() != tmpXOR)
      {
        SM_BL_USART_SendByte(NACK_BYTE);
      }
      else
      {
        /* Write data to memory */
          sm_boot_mem_Write(address, (uint8_t *)USART_RAM_Buf, codesize);

        /* Send last Acknowledge synchronization byte */
        SM_BL_USART_SendByte(ACK_BYTE);

        /* Check if the received address is an option byte address */
        mem_area = sm_boot_mem_GetAddressArea(address);

        if (mem_area == OB_AREA)
        {
          /* Launch Option Bytes reload */
            sm_boot_mem_OptionBytesLaunch();
        }
      }
    }
  }
}
/**
 *
 */
static void OPENBL_USART_Go(void)
{
  uint32_t address;
  uint32_t mem_area;

  /* Check memory protection then send adequate response */
  if (sm_boot_mem_GetReadOutProtectionStatus() != 0)
  {
    SM_BL_USART_SendByte(NACK_BYTE);
  }
  else
  {
    SM_BL_USART_SendByte(ACK_BYTE);

    /* Get memory address */
    if (OPENBL_USART_GetAddress(&address) == NACK_BYTE)
    {
      SM_BL_USART_SendByte(NACK_BYTE);
    }
    else
    {
      /* Check if received address is valid or not */
      mem_area = sm_boot_mem_GetAddressArea(address);

      if ((mem_area != FLASH_AREA) && (mem_area != RAM_AREA))
      {
        SM_BL_USART_SendByte(NACK_BYTE);
      }
      else
      {
        /* If the jump address is valid then send ACK */
        SM_BL_USART_SendByte(ACK_BYTE);

        sm_boot_mem_JumpToAddress(address);
      }
    }
  }
}

static void OPENBL_USART_ReadoutProtect(void)
{
  /* Check memory protection then send adequate response */
  if (sm_boot_mem_GetReadOutProtectionStatus() != 0)
  {
    SM_BL_USART_SendByte(NACK_BYTE);
  }
  else
  {
    SM_BL_USART_SendByte(ACK_BYTE);

    /* Enable the read protection */
    sm_boot_mem_SetReadOutProtection(1);

    SM_BL_USART_SendByte(ACK_BYTE);

    /* Launch Option Bytes reload */
    sm_boot_mem_OptionBytesLaunch();
  }
}

static void OPENBL_USART_ReadoutUnprotect(void)
{
  SM_BL_USART_SendByte(ACK_BYTE);

  /* Once the option bytes modification start bit is set in FLASH CR register,
     all the RAM is erased, this causes the erase of the Open Bootloader RAM.
     This is why the last ACK is sent before the call of sm_boot_mem_SetReadOutProtection */
  SM_BL_USART_SendByte(ACK_BYTE);

  /* Disable the read protection */
  sm_boot_mem_SetReadOutProtection(0);

  /* Launch Option Bytes reload and reset system */
  sm_boot_mem_OptionBytesLaunch();
}

static void OPENBL_USART_EraseMemory(void)
{
  uint32_t xor;
  uint32_t counter;
  uint32_t numpage;
  uint16_t data;
  int error_value;
  uint8_t status = ACK_BYTE;
  uint8_t *ramaddress;

  ramaddress = (uint8_t *) USART_RAM_Buf;

  /* Check if the memory is not protected */
  if (sm_boot_mem_GetReadOutProtectionStatus() != 0)
  {
    SM_BL_USART_SendByte(NACK_BYTE);
  }
  else
  {
    SM_BL_USART_SendByte(ACK_BYTE);

    /* Read number of pages to be erased */
    data = SM_BL_USART_ReadByte();
    data = (uint16_t)(data << 8) | SM_BL_USART_ReadByte();

    /* Checksum initialization */
    xor  = ((uint32_t)data & 0xFF00U) >> 8;
    xor ^= (uint32_t)data & 0x00FFU;

    /* All commands in range 0xFFFZ are reserved for special erase features */
    if ((data & 0xFFF0U) == 0xFFF0U)
    {
      /* Check data integrity */
      if (SM_BL_USART_ReadByte() != (uint8_t) xor)
      {
        status = NACK_BYTE;
      }
      else
      {
        if ((data == 0xFFFFU) || (data == 0xFFFEU) || (data == 0xFFFDU))
        {
          ramaddress[0] = (uint8_t)(data & 0x00FFU);
          ramaddress[1] = (uint8_t)((data & 0xFF00U) >> 8);

          error_value = sm_boot_mem_MassErase(FLASH_START_ADDRESS, (uint8_t *) USART_RAM_Buf, USART_RAM_BUFFER_SIZE);

          if (error_value == 0)
          {
            status = ACK_BYTE;
          }
          else
          {
            status = NACK_BYTE;
          }
        }
        else
        {
          /* This sub-command is not supported */
          status = NACK_BYTE;
        }
      }
    }
    else
    {
      ramaddress = (uint8_t *) USART_RAM_Buf;

      /* Number of pages to be erased (data + 1) */
      numpage = (uint32_t)data + 1U;

      *ramaddress = (uint8_t)(numpage & 0x00FFU);
      ramaddress++;

      *ramaddress = (uint8_t)((numpage & 0xFF00U) >> 8);
      ramaddress++;

      /* Get the pages to be erased */
      for (counter = numpage; counter != 0U ; counter--)
      {
        /* Receive the MSB byte */
        data  = SM_BL_USART_ReadByte();
        xor  ^= data;
        data  = (uint16_t)((data & 0x00FFU) << 8);

        /* Receive the LSB byte */
        data |= (uint8_t)(SM_BL_USART_ReadByte() & 0x00FFU);
        xor  ^= ((uint32_t)data & 0x00FFU);

        /* Only store data that fit in the buffer length */
        if (counter < (USART_RAM_BUFFER_SIZE / 2U))
        {
          *ramaddress = (uint8_t)(data & 0x00FFU);
          ramaddress++;

          *ramaddress = (uint8_t)((data & 0xFF00U) >> 8);
          ramaddress++;
        }
        else
        {
          /* Continue to read data from USART */
        }

      }

      /* Check data integrity */
      if (SM_BL_USART_ReadByte() != (uint8_t) xor)
      {
        status = NACK_BYTE;
      }
      else
      {
        error_value = sm_boot_mem_Erase(FLASH_START_ADDRESS, (uint8_t *) USART_RAM_Buf, USART_RAM_BUFFER_SIZE);

        /* Errors from memory erase are not managed, always return ACK */
        if (error_value == 0)
        {
          status = ACK_BYTE;
        }
      }
    }

    SM_BL_USART_SendByte(status);
  }
}

static void OPENBL_USART_WriteProtect(void)
{
  uint32_t counter;
  uint32_t length;
  uint32_t data;
  uint32_t xor;
  int error_value;
  uint8_t *ramaddress;

  /* Check if the memory is not protected */
  if (sm_boot_mem_GetReadOutProtectionStatus() != 0)
  {
    SM_BL_USART_SendByte(NACK_BYTE);
  }
  else
  {
    SM_BL_USART_SendByte(ACK_BYTE);

    /* Get the data length */
    data = SM_BL_USART_ReadByte();

    ramaddress = (uint8_t *) USART_RAM_Buf;
    length     = data + 1U;

    /* Checksum Initialization */
    xor = data;

    /* Receive data and write to RAM Buffer */
    for (counter = length; counter != 0U ; counter--)
    {
      data  = SM_BL_USART_ReadByte();
      xor  ^= data;

      *(volatile uint8_t *)(ramaddress) = (uint8_t) data;

      ramaddress++;
    }

    /* Check data integrity and send NACK if Checksum is incorrect */
    if (SM_BL_USART_ReadByte() != (uint8_t) xor)
    {
      SM_BL_USART_SendByte(NACK_BYTE);
    }
    else
    {
      ramaddress = (uint8_t *) USART_RAM_Buf;

      /* Enable the write protection */
      error_value = sm_boot_mem_SetWriteProtection(1, FLASH_START_ADDRESS, ramaddress, length);

      SM_BL_USART_SendByte(ACK_BYTE);

      if (error_value == 0)
      {
        sm_boot_mem_OptionBytesLaunch();
      }
    }
  }
}

static void OPENBL_USART_WriteUnprotect(void)
{
  int error_value;

  /* Check if the memory is not protected */
  if (sm_boot_mem_GetReadOutProtectionStatus() != 0)
  {
    SM_BL_USART_SendByte(NACK_BYTE);
  }
  else
  {
    SM_BL_USART_SendByte(ACK_BYTE);

    /* Disable write protection */
    error_value = sm_boot_mem_SetWriteProtection(0, FLASH_START_ADDRESS, NULL, 0);

    SM_BL_USART_SendByte(ACK_BYTE);

    if (error_value == 1)
    {
      sm_boot_mem_OptionBytesLaunch();
    }
  }
}

static uint8_t OPENBL_USART_GetAddress(uint32_t *Address)
{
  uint8_t data[4] = {0, 0, 0, 0};
  uint8_t status;
  uint8_t xor;

  data[3] = SM_BL_USART_ReadByte();
  data[2] = SM_BL_USART_ReadByte();
  data[1] = SM_BL_USART_ReadByte();
  data[0] = SM_BL_USART_ReadByte();

  xor = data[3] ^ data[2] ^ data[1] ^ data[0];

  /* Check the integrity of received data */
  if (SM_BL_USART_ReadByte() != xor)
  {
    status = NACK_BYTE;
  }
  else
  {
    *Address = ((uint32_t)data[3] << 24) | ((uint32_t)data[2] << 16) | ((uint32_t)data[1] << 8) | (uint32_t)data[0];

    /* Check if received address is valid or not */
    if (sm_boot_mem_GetAddressArea(*Address) == AREA_ERROR)
    {
      status = NACK_BYTE;
    }
    else
    {
      status = ACK_BYTE;
    }
  }

  return status;
}
