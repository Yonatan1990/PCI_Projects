#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


#define REG_OFF 0x800

#define MMAP_SIZE 4096

int main(int argc,char *argv[]) {

uint16_t i;
int fd;
uint32_t offset,config[5];
uint8_t *bar0, *bar1, value;


// open bar's resource file
fd = open("/sys/bus/pci/devices/0000:02:0a.0/resource0",O_RDWR | O_SYNC);
if (fd < 0){
	perror("error opening BAR's resource file");
	return -1;
}

bar0 = mmap(NULL,MMAP_SIZE,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
close (fd);

//let's check of we have a valid pointers
if(bar0 == MAP_FAILED){
	perror ("memory mapping of bar failed");
	return -1;
}

	
//let's take care of the offset
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

char signature[40];

for (i=0;i<0x64;i++){

	printf("Byte %x on BAR0: %x \n",i,*(bar0 + i));
	if (*(bar0 + i) != 0)
		signature[i] = *(bar0 + i);
}

printf("\n%s\n",signature);

printf("\nSital Registers\n");
for (i=0;i<32;i++){

	printf("Register %x on BAR0: %x \n",i,*(uint16_t*)(bar0 + REG_OFF + i*2));

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
for (i=0;i<0x16;i++){

	*(uint16_t*)(bar1 + i*2) = i;
}

for (i=0;i<16;i++){

	printf("Memory %x on BAR1: %x \n",i,*(uint16_t*)(bar1 + i*2));

}


/*
//lets access the cards
*(car0 + REG_OFF) = 0x0; // set all byte to input

value = *(bar0 + 0xa);

*/

munmap(bar0,MMAP_SIZE);
munmap(bar1,MMAP_SIZE);
return 0 ;
}









