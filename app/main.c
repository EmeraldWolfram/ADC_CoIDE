#include "stm32f429xx.h"
#include "Gpio.h"
#include "Adc.h"
#include "Dma.h"

int count = 0;
int i = 0;
uint16_t dataRead[256];

void ADC_IRQHandler(void){
	uint32_t regStatus	= ADC1->SR;
	uint32_t injStatus	= ADC1->SR;

	volatile int regResult, injResult;
	regStatus	&= 2;
	injStatus	&= 4;

	if((ADC1->SR & 2) != 0)
		regResult = getRegularData(ADC1);

	if((ADC1->SR & 4) != 0){
		injResult = getInjectedData(ADC1, 0);
	}
	ADC1->SR = 0;
	count++;
}

void DMA2_Stream0_IRQHandler(void){

	int data1, data2;

	data1 = 0;
	dataRead[0] = *getADC1Data();
	data1 = dataRead[0];

	dataRead[1] = getXdata();
	data2 = dataRead[1];

	DMA2->LIFCR	= 0;
	DMA2->HIFCR	= 0;
	i++;
}


int main(void){
	uint32_t sysCLK = getSystemClock();
	uint32_t p2CLK	= getAPB2Clock(sysCLK);
	int dmaStatus = DMA2->LISR;

	dataRead[0] = *getADC1Data();


	configureOutput(GPIO_SPEED_V_HIGH, PIN_14, PORTG);
	configureOutput(GPIO_SPEED_V_HIGH, PIN_13, PORTG);
	uint16_t dmaData;
	configureAnalog(NO_PULL, PIN_0, PORTA);
	configDMA();
	configADC(ADC1);
	dmaData = dataRead[0];
	setSampleTime(CYCLE_15, ADC1, Channel_0);
	setSampleTime(CYCLE_84, ADC1, Channel_18);
	setResolution(RESOLUTION_12_BITS, ADC1);
	setContMode(ADC1);

	ADC1->CR2 |= 3 << 8;	//ENABLE DMA and DDS
	DMA2->S0.CR |= 1;		//START DMA

	startRegularConv(ADC1);
	startInjectedConv(ADC1);

	HAL_NVIC_EnableIRQ(ADC_IRQn);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  
    while(1){
    	writeOne(PIN_13, PORTG);
    	writeZero(PIN_14, PORTG);
    	_delay(100000);

    	dmaStatus = DMA2->LISR;
    	dmaData = *getADC1Data();
    	dmaData = getXdata();


    	writeZero(PIN_13, PORTG);
    	writeOne(PIN_14, PORTG);
    	_delay(100000);
    }
}

void _delay(int delay){
	while(delay != 0)
		delay--;
}
