//#include "xil_types.h"
#include "Types.h"
#define BUFFER 0xFF

int initialize_pci();
void brmSingleRegWrite(u16 address,u16 data);
u16 brmSingleRegRead(u16 address);

void brmSingleMemWrite(u16 address,u16 data);
u16 brmSingleMemRead(u16 address);



