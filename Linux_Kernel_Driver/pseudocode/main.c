
#include "unistd.h"
#include "stdio.h"
//#include "xil_printf.h"
#include "1553.h"
#include "brmMaster.h"
//#include "xil_io.h"
//#include "xparameters.h"
#include "Types.h"

extern uint8_t *bar0, *bar1;
//uint32_t data1;
int main()
{
    //uint16_t *data_test = malloc(32*sizeof(uint16_t)); 
    printf( "Hello from pseudo code example\n\r" );
   
    //some memory testing
/*
    	int addr = 0x1A;
    	//Xil_Out16(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+0x20000+addr*2,0x1111);
    	//data = Xil_In16(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+0x20000+addr*2);
    	//printf("the data memory is:%0x\n\r",data);

   //some register testing
    	data = Xil_In16(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+0x00000+0x1A*2);
    	if (data == 0x0000)
    		printf("Some error in read/write registers\n\r");
*/
//    	data = Xil_In16(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+REG_OFF+0x12*2);// C0010002 ---> 0x10002 ---> memory 0x0001
//
//    	xil_printf("the data register is:%0x\n\r",data);

  //  	perform brm version and registers list
//

	  initialize_pci();
	  brmSingleRegWrite(0x0003,0x0001); //reset core registers
	  //brmSingleRegWrite(0x2,0x0280); // set timetag resolution to 2usec
    	  //printf("timetag resolution is 2usec\n\r");
    	  printf("BRM1553D version register:%0x\n\r",brmSingleRegRead(0x1A));
	 	
    	  if (brmSingleRegRead(0xE)>>15)
    		  printf("KEY is NOT attached\n\r");
    	  else
    		  printf("KEY is attached\n\n\r");

	//uint32_t data1;
	//data1 = brmSingleRegRead(0x1A);

    	//for (i = 0; i < 1; i++)  
    		//{
   		///printf("Register Address %0x Data %0x\n\r",i,brmSingleRegRead(i));
   		//}
//
	printf("Bar0: 0x%x\n\r",bar0);
    	printf("\n--Now trying to perform BC transmission--\n\r");
 	  
        brmBCexample();

	//int i;
	//i++;
	munmap(bar0,BUFFER);
	munmap(bar1,BUFFER);

	return 0;
}
