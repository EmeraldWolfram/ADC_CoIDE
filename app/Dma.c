#include "Dma.h"

void adc1DmaConfig(){
  DMA1->S0CR    = 0x00022C38;
  DMA1->S0NDTR  = 5;          //Read 5 times
  DMA1->S0PAR   = 0x4001204C; //Read from ADC1.DR
  DMA1_>S0M0AR  = 0x08000000; //Main Memory pg 75
  DMA1->S0FCR   = 0;          //No Interrupt generated upon request
}
