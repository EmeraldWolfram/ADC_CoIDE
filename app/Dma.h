#ifndef	__Dma_H__
#define	__Dma_H__

#include <stdint.h>
typedef struct DMA_Type DMA_t;
#include "Rcc.h"
#include "Adc.h"

typedef struct{
	  volatile uint32_t CR;
	  volatile uint32_t NDTR;
	  volatile uint32_t PAR;
	  volatile uint32_t M0AR;
	  volatile uint32_t M1AR;
	  volatile uint32_t FCR;
}Stream_t;



struct DMA_Type{
  volatile uint32_t LISR;
  volatile uint32_t HISR;
  volatile uint32_t LIFCR;
  volatile uint32_t HIFCR;
  Stream_t	S0;
  Stream_t	S1;
  Stream_t	S2;
  Stream_t	S3;
  Stream_t	S4;
  Stream_t	S5;
  Stream_t	S6;
  Stream_t	S7;
//  volatile uint32_t S0CR;
//  volatile uint32_t S0NDTR;
//  volatile uint32_t S0PAR;
//  volatile uint32_t S0M0AR;
//  volatile uint32_t S0M1AR;
//  volatile uint32_t S0FCR;
//  volatile uint32_t S1CR;
//  volatile uint32_t S1NDTR;
//  volatile uint32_t S1PAR;
//  volatile uint32_t S1M0AR;
//  volatile uint32_t S1M1AR;
//  volatile uint32_t S1FCR;
//  volatile uint32_t S2CR;
//  volatile uint32_t S2NDTR;
//  volatile uint32_t S2PAR;
//  volatile uint32_t S2M0AR;
//  volatile uint32_t S2M1AR;
//  volatile uint32_t S2FCR;
//  volatile uint32_t S3CR;
//  volatile uint32_t S3NDTR;
//  volatile uint32_t S3PAR;
//  volatile uint32_t S3M0AR;
//  volatile uint32_t S3M1AR;
//  volatile uint32_t S3FCR;
//  volatile uint32_t S4CR;
//  volatile uint32_t S4NDTR;
//  volatile uint32_t S4PAR;
//  volatile uint32_t S4M0AR;
//  volatile uint32_t S4M1AR;
//  volatile uint32_t S4FCR;
//  volatile uint32_t S5CR;
//  volatile uint32_t S5NDTR;
//  volatile uint32_t S5PAR;
//  volatile uint32_t S5M0AR;
//  volatile uint32_t S5M1AR;
//  volatile uint32_t S5FCR;
//  volatile uint32_t S6CR;
//  volatile uint32_t S6NDTR;
//  volatile uint32_t S6PAR;
//  volatile uint32_t S6M0AR;
//  volatile uint32_t S6M1AR;
//  volatile uint32_t S6FCR;
//  volatile uint32_t S7CR;
//  volatile uint32_t S7NDTR;
//  volatile uint32_t S7PAR;
//  volatile uint32_t S7M0AR;
//  volatile uint32_t S7M1AR;
//  volatile uint32_t S7FCR;
};

#define DMA1   ((DMA_t*)0x40026000)
#define DMA2   ((DMA_t*)0x40026400)

#define DMA1_ENABLE   1

void configDMA();
int* getADC1Data();
int* getXdata();


#endif  //__Dma_H__
