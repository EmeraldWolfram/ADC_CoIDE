#include "Dma.h"

/****************************************************************************
 * 1. configDMA2ForADC1:
 *
 * This function enable the ADCx by awaken the ADCx and enable the CLOCK
 * - Enabled EOC and JEOC to generate Interrupt
 * - Channel 0 set as 1st and only conversion in regular queue
 * - Channel 18 (Vbat) set as 1st and only conversion in injected queue
 * - Data obtained is right aligned
 * - Only 1 conversion will be done
 *
 * NOTE: It call adcUnresetEnableClock in Rcc.h to enable the CLOCK
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 *****************************************************************************/
uint16_t buffer[256];

void configDMA2ForADC1(){
  dmaUnresetEnableClock(DMA2);
  DMA2->S0.CR   &= SELECT_CHANNEL_0;		//Stream 0 Channel 0 ~ (ADC1)
  DMA2->S0.CR   &= ~CT_TARGET_MEM1;		//Target MEMORY 0
  DMA2->S0.CR   &= ~DOUBLE_BUFFER_MODE;	//Disable Double Buffer Mode

  DMA2->S0.CR   &= ~(3 << 16);					//MASK PRIORITY SET Bits
  DMA2->S0.CR   |= PRIORITY_HIGH;

  DMA2->S0.CR   &= (3 << 13);
  DMA2->S0.CR   |= DEST_H_WORD_SIZE_DATA;
  DMA2->S0.CR   &= (3 << 11);
  DMA2->S0.CR   |= PERIPHERAL_H_WORD_SIZE_DATA;

  DMA2->S0.CR   |= DESTINATION_MEM_INCRMENT;	//Increment to Destination Memory
  DMA2->S0.CR   &= ~PERIPHERAL_MEM_INCRMENT;	//Disable increment to peripheral
  DMA2->S0.CR	&= PERIPHERAL_TO_MEMORY_MODE;
  DMA2->S0.CR	&= ~PERIPHERAL_CONTROL_FLOW;
  DMA2->S0.CR   |= ENABLE_ALL_INTERRUPTS;

  DMA2->S0.NDTR  = 5;                    		//Read 5 times
  DMA2->S0.PAR   = (uint32_t)(&(ADC1->DR));     //Departure from ADC1.DR
  DMA2->S0.M0AR  = (uint32_t)buffer;			//Destination Memory
  DMA2->S0.FCR   = FIFO_DISABLE;                //Disable FIFO
}

int* getADC1Data(){
  int *ptrToMemory = buffer;

  return ptrToMemory;
}
void enableDMA(){
	DMA2->S0.CR   |=DMAx_ENABLE;
}
