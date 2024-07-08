
//#include "mem_rw.h"
#include "unistd.h"
//#include "stdio.h"
#include "Types.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
//#include <unistd.h>

//using namespace std;
#include "brmMaster.h"

#define REG_OFF 0x0800
#define MEM_OFF 0x0000


//perf myPerf("/dev/lpciedemo");

uint8_t *bar0, *bar1, value;
//extern uint8_t *bar0, *bar1;

int initialize_pci(){

	uint16_t i;
	int fd;
	uint32_t offset,config[5];

// open bar's resource file
	fd = open("/sys/bus/pci/devices/0000:02:0a.0/resource0",O_RDWR | O_SYNC);
	if (fd < 0){
		perror("error opening BAR's resource file");
		return -1;
	}

	bar0 = mmap(NULL,MMAP_SIZE,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
	close (fd);

	//lets check of we have a valid pointers
	if(bar0 == MAP_FAILED){
	perror ("memory mapping of bar failed");
	return -1;
}

	
	//lets tahe cars of the offset
	fd = open("/sys/bus/pci/devices/0000:02:0a.0/config",O_RDONLY);
	if (fd < 0){
		perror("error opening BAR's resource file");
		return -1;
	}

	i = read(fd, config, 0x14);
	close(fd);
	if(i != 0x14) {
		perror("error reading pci config header");
		munmap(bar0,256);
	}	

	//calculate the offset
	offset = (config[4] & 0xfffffff0) % 4096;
 
	//adjust bars pointer
	bar0 = bar0 + offset;

	//iowrite16(0xb000, parport_bar0 + 0x56);

	*(uint16_t*)(bar0 + 0x56) = 0xb000;

	char signature[64];

	for (i=0;i<64;i++){

		printf("Byte %x on BAR0: %x \n",i,*(bar0 + i));
		if (*(bar0 + i) != 0)
			signature[i] = *(bar0 + i);
	}

	printf("\n%s\n",signature);

	printf("\nSital Registers\n");
	for (i=0;i<32;i++){
		printf("Register %x on BAR0: %x \n",i,*(uint16_t*)(bar0 + 0x800 + i*2));
	}

	// open bar's resource file
	fd = open("/sys/bus/pci/devices/0000:02:0a.0/resource1",O_RDWR | O_SYNC);
	if (fd < 0){
		perror("error opening BAR's resource file");
		return -1;
	}

	bar1 = mmap(NULL,MMAP_SIZE,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
	close (fd);

	//lets check of we have a valid pointers
	if(bar0 == MAP_FAILED){
		perror ("memory mapping of bar failed");
		return -1;
	}

	//write values to first 32 memory locations
	for (i=0;i<16;i++){
	
		*(uint16_t*)(bar1 + i*2) = i;
	}

 	for (i=0;i<16;i++){

  		printf("Memory %x on BAR1: %x \n",i,*(uint16_t*)(bar1 + i*2));
}


//	munmap(bar0,BUFFER);
//	munmap(bar1,BUFFER);
//munmap(bar0,256);
//munmap(bar1,256);
return 0 ;
}



void brmSingleRegWrite(u16 address,u16 data)
{
	
	*(uint16_t*)(bar0 + REG_OFF + address*2) = data;
	//myPerf.write16(address*2+REG_OFF,data); 

}

u16 brmSingleRegRead(u16 address)
{
 	u16 data;

	//u16 data_read[1];
	//myPerf.read16(address*2+REG_OFF,data_read,2);
	//data = *data_read;

	data = *(uint16_t*)(bar0 + REG_OFF + address*2);
        return data;
}


void brmSingleMemWrite(u16 address,u16 data)
        {

	
	//myPerf.write16(address*2+MEM_OFF,data); 
	*(uint16_t*)(bar1 + MEM_OFF + address*2) = data;


		}

u16 brmSingleMemRead(u16 address)
{
 	u16 data;
	//data = myPerf.read16(address*2+MEM_OFF);

	//u16 data_read[1];
	//myPerf.read16(address*2+MEM_OFF,data_read,2);
	//data = *data_read;
	
	data = *(uint16_t*)(bar1 + MEM_OFF + address*2);
        return data;

}


//void brmBurstMemWrite(u16 startAddress,u16 length, u16* data)
//{


//	u16 BytesLength = length*2;
//	void* bram_addr = (void*)(/*XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+*/startAddress*2);
//	memcpy(bram_addr,data,BytesLength );

//}


//void brmBurstMemRead(u16 startAddress,u16 length, u16* data)
//{
//	u16 BytesLength = length*2;
//	void* bram_addr = (void*)(/*XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+*/startAddress*2);
//	memcpy(data,bram_addr,BytesLength );

//}


