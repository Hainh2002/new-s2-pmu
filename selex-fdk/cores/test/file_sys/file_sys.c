#include "sm_filesystem.h"
#include "sm_fileconfig.h"

#define  BLOCK_COUNT 100
#define BLOCK_SIZE 128
#define START_SECTOR_ADDR 0
uint8_t sys_memory[BLOCK_COUNT][BLOCK_SIZE];


sm_file_sys_t sm_file = {.block_count = BLOCK_COUNT,.block_size = BLOCK_SIZE};

static int file_read(void *buff,uint32_t block,uint32_t off,uint32_t size);
static int file_write(const void *buff, uint32_t block, uint32_t off, uint32_t size);
static int file_erase(uint32_t block);

int main(int argc, char **argv) {

	sm_file.func.erase = file_erase;
	sm_file.func.write = file_write;
	sm_file.func.read = file_read;

	sm_file_system_init(&sm_file);


	FILE *file = fopen("readme.txt","w");

	if(file != NULL){
		fwrite("Hello guy\n",strlen("Hello guy\n"),file);
		fclose(file);
	}

	return 0;
}

static int file_read(void *buff,uint32_t block,uint32_t off,uint32_t size){
	if(block > BLOCK_COUNT) return -1;
	memcpy(buff,sys_memory[block]+off,size);
	return 0;
}
static int file_write(const void *buff, uint32_t block, uint32_t off, uint32_t size){
	for(uint16_t i = 0;i<size;i++){
		*sys_memory + (block*BLOCK_SIZE + off + i) = (uint8_t)buff[i];
	}
	return 0;
}
static int file_erase(uint32_t block){
    memset (sys_memory[block + START_SECTOR_ADDR], 0xff, BLOCK_SIZE);

	return 0;
}
