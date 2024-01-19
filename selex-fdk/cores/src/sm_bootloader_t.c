/*
 * sm_bootloader_t.c
 *
 *  Created on: Sep 11, 2023
 *      Author: MinhNhan
 */

#include "sm_bootloader_t.h"
/**
 *
 * @param buff
 * @param length
 * @return
 */
uint16_t sm_crc16(uint8_t *buff, uint32_t length) {
    uint8_t crc = 0;
    for(uint16_t i = 0;i<length;i++){
        crc ^= buff[i];
    }
    crc = !crc + 1;
    return crc;
}
/**
 *
 * @param p_boot
 * @param info
 * @param func
 */
void sm_boot_init(sm_bootloader_t *p_boot,struct boot_info *info,struct boot_function *func) {
	p_boot->p_if->GetCommand = sm_boot_get_command;
	p_boot->p_if->GetVersion = sm_boot_get_version;
	p_boot->p_if->GetID = sm_boot_get_id;
	p_boot->p_if->ReadMemory = sm_boot_read_memory;
	p_boot->p_if->WriteMemory = sm_boot_write_memory;
	p_boot->p_if->EraseMemory = sm_boot_erase_memory;
	p_boot->p_if->Go = sm_boot_go;
	p_boot->info = info;
	p_boot->func = func;
}
/**
 *
 * @param p_boot
 */
void sm_boot_process(sm_bootloader_t *p_boot) {

	sm_bootloader_t *p_Interface = p_boot;

	uint8_t command_opcode = sm_boot_get_command_opcode(p_boot);

    switch (command_opcode)
    {
      case CMD_GET_COMMAND:
        if (p_Interface->p_if->GetCommand != NULL)
        {
          p_Interface->p_if->GetCommand(p_boot);
        }
        break;

      case CMD_GET_VERSION:
        if (p_Interface->p_if->GetVersion != NULL)
        {
          p_Interface->p_if->GetVersion(p_boot);
        }
        break;

      case CMD_GET_ID:
        if (p_Interface->p_if->GetID != NULL)
        {
          p_Interface->p_if->GetID(p_boot);
        }

        break;

      case CMD_READ_MEMORY:
        if (p_Interface->p_if->ReadMemory != NULL)
        {
          p_Interface->p_if->ReadMemory(p_boot);
        }
        break;

      case CMD_WRITE_MEMORY:
        if (p_Interface->p_if->WriteMemory != NULL)
        {
          p_Interface->p_if->WriteMemory(p_boot);
        }
        break;

      case CMD_GO:
        if (p_Interface->p_if->Go != NULL)
        {
          p_Interface->p_if->Go(p_boot);
        }
        break;

      case CMD_READ_PROTECT:
        if (p_Interface->p_if->ReadoutProtect != NULL)
        {
          p_Interface->p_if->ReadoutProtect(p_boot);
        }
        break;

      case CMD_READ_UNPROTECT:
        if (p_Interface->p_if->ReadoutUnprotect != NULL)
        {
          p_Interface->p_if->ReadoutUnprotect(p_boot);
        }
        break;

      case CMD_EXT_ERASE_MEMORY:
        if (p_Interface->p_if->EraseMemory != NULL)
        {
          p_Interface->p_if->EraseMemory(p_boot);
        }
        break;

      case CMD_WRITE_PROTECT:
        if (p_Interface->p_if->WriteProtect != NULL)
        {
          p_Interface->p_if->WriteProtect(p_boot);
        }
        break;

      case CMD_WRITE_UNPROTECT:
        if (p_Interface->p_if->WriteUnprotect != NULL)
        {
          p_Interface->p_if->WriteUnprotect(p_boot);
        }
        break;

      case CMD_NS_WRITE_MEMORY:
        if (p_Interface->p_if->NsWriteMemory != NULL)
        {
          p_Interface->p_if->NsWriteMemory(p_boot);
        }
        break;

      case CMD_NS_ERASE_MEMORY:
        if (p_Interface->p_if->NsEraseMemory != NULL)
        {
          p_Interface->p_if->NsEraseMemory(p_boot);
        }
        break;

      case CMD_NS_WRITE_PROTECT:
        if (p_Interface->p_if->NsWriteProtect != NULL)
        {
          p_Interface->p_if->NsWriteProtect(p_boot);
        }
        break;

      case CMD_NS_WRITE_UNPROTECT:
        if (p_Interface->p_if->NsWriteUnprotect != NULL)
        {
          p_Interface->p_if->NsWriteUnprotect(p_boot);
        }
        break;

      case CMD_NS_READ_PROTECT:
        if (p_Interface->p_if->NsReadoutProtect != NULL)
        {
          p_Interface->p_if->NsReadoutProtect(p_boot);
        }
        break;

      case CMD_NS_READ_UNPROTECT:
        if (p_Interface->p_if->NsReadoutUnprotect != NULL)
        {
          p_Interface->p_if->NsReadoutUnprotect(p_boot);
        }
        break;

      /* Unknown command opcode */
      default:
        if (p_Interface->func->putc != NULL)
        {
          p_Interface->func->putc(NACK_BYTE);
        }
        break;
    }
}
/**
 *
 * @param _this
 * @return
 */
uint8_t sm_boot_get_command_opcode(sm_bootloader_t *_this){
	uint8_t byte1 = _this->func->getc();
	uint8_t byte2 = _this->func->getc();
	if(byte1 == 0x01 && byte2 == 0xFE) return CMD_GET_VERSION;

	if(byte1 == 0x11 && byte2 == 0xEE) return CMD_READ_MEMORY;

	if(byte1 == 0x21 && byte2 == 0xDE) return CMD_GO;

	if(byte1 == 0x31 && byte2 == 0xCE) return CMD_WRITE_MEMORY;

	if(byte1 == 0x43 && byte2 == 0xBC) return CMD_NS_ERASE_MEMORY;

	return 0x00;
}
/**
 *
 * @param _this
 */
void sm_boot_get_command(sm_bootloader_t *_this) {
	_this->func->putc(ACK_BYTE);
	_this->func->putc(ACK_BYTE);
}
/**
 *
 * @param _this
 */
void sm_boot_get_version(sm_bootloader_t *_this) {
	_this->func->putc(ACK_BYTE);
	_this->func->putc(0x10);
	_this->func->putc(0x00);
	_this->func->putc(0x00);
	_this->func->putc(ACK_BYTE);
}
/**
 *
 * @param _this
 */
void sm_boot_get_id(sm_bootloader_t *_this) {
	_this->func->putc(ACK_BYTE);
	_this->func->putc(0x01);
	_this->func->putc(0x01);
	_this->func->putc(0x02);
	_this->func->putc(ACK_BYTE);
}
/**
 *
 * @param _this
 */
void sm_boot_read_memory(sm_bootloader_t *_this) {

}
/**
 *
 * @param _this
 */
void sm_boot_write_memory(sm_bootloader_t *_this) {
	_this->func->putc(ACK_BYTE);
	uint8_t p_addr[4];
	p_addr[0] = _this->func->getc();
	p_addr[1] = _this->func->getc();
	p_addr[2] = _this->func->getc();
	p_addr[3] = _this->func->getc();

	uint32_t addr = ((uint32_t)p_addr[0] << 24) | ((uint32_t)p_addr[1] << 16) | ((uint32_t)p_addr[2] << 8) | ((uint32_t)p_addr[3]);

	uint8_t p_length[2];

	p_length[0] = _this->func->getc();
	p_length[1] = _this->func->getc();

	uint16_t length = ((uint16_t)p_length[0] << 8) | ((uint16_t)p_length[1]);
	uint8_t crc = _this->func->getc();

	uint8_t data[6] = {0};

	memcpy(data,p_addr,4);
	memcpy(data+4,p_length,2);

	uint8_t checksum = sm_crc16(data,6);
	if(checksum != crc ){
		_this->func->putc(NACK_BYTE);
		return;
	}
	_this->func->putc(ACK_BYTE);

	uint8_t *p_data = (uint8_t*)malloc(length * sizeof(uint8_t));

	for(uint16_t i = 0;i<length;i++){
		p_data[i] = _this->func->getc();
	}

	crc = _this->func->getc();

	checksum = sm_crc16(p_data, length);

	if(checksum != crc){
		_this->func->putc(NACK_BYTE);
		free(p_data);
		return;
	}

	if(_this->func->fl_write(p_data,addr,length) == 0){
		_this->func->putc(ACK_BYTE);
	}
	else{
		_this->func->putc(NACK_BYTE);
	}
	free(p_data);
}
/**
 *
 * @param _this
 */
void sm_boot_erase_memory(sm_bootloader_t *_this) {
	_this->func->putc(ACK_BYTE);

	uint8_t byte[2] = {0};
	byte[0] = _this->func->getc();
	byte[1] = _this->func->getc();

	if(byte[0] == 0x00 && byte[1] == 0xff){
		if(_this->func->fl_erase() == 0){
			_this->func->putc(ACK_BYTE);
			return;
		}
	}
	_this->func->putc(NACK_BYTE);
}
/**
 *
 * @param _this
 */
void sm_boot_go(sm_bootloader_t *_this) {

}
