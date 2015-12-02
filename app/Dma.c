#include "Dma.h"

uint16_t buffer[256];

void configDMA(){
  dmaUnresetEnableClock(DMA2);
  DMA2->S0.CR    = 0x00022C1E;
  DMA2->S0.NDTR  = 5;                    //Read 5 times
  DMA2->S0.PAR   = (uint32_t)(&(ADC1->DR));          //Read from ADC1.DR
  DMA2->S0.M0AR  = (uint32_t)buffer;				//Main Memory pg 75
  DMA2->S0.FCR   = 0;                    //Not using FIFO
}

int* getADC1Data(){
  int *ptrToMemory = buffer;

  return ptrToMemory;
}

int* getXdata(){
	int *d2nd = buffer + 1;
	return d2nd;
}
