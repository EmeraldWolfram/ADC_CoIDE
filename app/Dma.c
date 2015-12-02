#include "Dma.h"

void configDMA(){
  dmaUnresetEnableClock(DMA2);
  DMA2->S0CR    = 0x00022C38;
  DMA2->S0NDTR  = 5;                    //Read 5 times
  DMA2->S0PAR   = &(ADC1->DR);          //Read from ADC1.DR
  DMA2->S0M0AR  = MEMORY_0_BASE_ADDRESS;//Main Memory pg 75
  DMA2->S0FCR   = 0;                    //No Interrupt generated upon request
}

int getADC1Data(){
  int* ptrToMemory = ((int*)MEMORY_0_BASE_ADDRESS);
  return ptrToMemory;
}
