#ifndef	__Dma_H__
#define	__Dma_H__

#include <stdint.h>
typedef struct DMA_Type DMA_t;
#include "Rcc.h"
#include "Adc.h"

/**
 * This DMA file only use for ADC and therefore ONLY consist code
 * necessary for ADC.
 *
 * DMA2
 * =========================================================
 * Stream	 	|	0	|	1	|	2	|	3	|	4	|...
 * =============|=======|=======|=======|=======|=======|===
 * Channel_0	| ADC1	|		|		|		|  ADC1	|
 * Channel_1	|		|		|  ADC2	|  ADC2	|		|
 * Channel_2	| ADC3	| ADC3	|		|		|		|
 * =========================================================
 *
 * DMA2 is the DMA that in charge on the ADC in stm32f429xx.
 * Streams and channels that are use to transfer data from ADCx.DR
 * to the Memory is listed in the table above.
 *
 * Other streams and channels are use for other peripherals.
 *
 **********************************************/

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
};

#define DMA1   ((DMA_t*)0x40026000)
#define DMA2   ((DMA_t*)0x40026400)

#define DMAx_ENABLE		1
#define FIFO_DISABLE	0

#define	SELECT_CHANNEL_0	~(7 << 25)
#define	SELECT_CHANNEL_1	(1 << 25)
#define	SELECT_CHANNEL_2	(2 << 25)

#define CT_TARGET_MEM1		(1 << 19)
#define DOUBLE_BUFFER_MODE	(1 << 18)

#define PRIORITY_LOW		(0 << 16)
#define PRIORITY_MEDIUM		(1 << 16)
#define PRIORITY_HIGH		(2 << 16)
#define PRIORITY_V_HIGH		(3 << 16)

#define PERIPHERAL_MEM_INCRMENT		(1 << 9)
#define DESTINATION_MEM_INCRMENT	(1 << 10)

#define DEST_BYTE_SIZE_DATA		(0 << 13)
#define DEST_H_WORD_SIZE_DATA	(1 << 13)
#define DEST_WORD_SIZE_DATA		(2 << 13)

#define PERIPHERAL_BYTE_SIZE_DATA	(0 << 11)
#define PERIPHERAL_H_WORD_SIZE_DATA	(1 << 11)
#define PERIPHERAL_WORD_SIZE_DATA	(2 << 11)

#define	PERIPHERAL_TO_MEMORY_MODE	~(3 << 6)
#define PERIPHERAL_CONTROL_FLOW		(1 << 5)
#define ENABLE_ALL_INTERRUPTS		(15 << 1)

void configDMA2ForADC1();
int* getADC1Data();
void enableDMA();

#endif  //__Dma_H__
