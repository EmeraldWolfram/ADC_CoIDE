#include "stm32f429xx.h"
#include "Gpio.h"
#include "Adc.h"
#include "Dma.h"



int count = 0;
int i = 0;
uint16_t *dataRead1, *dataRead2, *dataRead3;

void ADC_IRQHandler(void){
	int status = ADC1->SR;
	int regResult = 0;
	int injResult0 = 0;
	int injResult1 = 0;
	int injResult2 = 0;
	int injResult3 = 0;


	if((ADC1->SR & 2) != 0)
		regResult = getRegularData(ADC1);

	if((ADC1->SR & 4) != 0){
		injResult0 = getInjectedData(ADC1, 0);
		injResult1 = getInjectedData(ADC1, 1);
		injResult2 = getInjectedData(ADC1, 2);
		injResult3 = getInjectedData(ADC1, 3);
	}

	ADC1->SR = 0;
	count++;
}

void DMA2_Stream0_IRQHandler(void){

	int data1, data2, data3;
  
	data1 = 0;
	data2 = 0;
	data3 = 0;
	dataRead1 = getADC1Data();
	dataRead2 = getADC2Data();
	dataRead3 = getADC3Data();
	data1 = dataRead1[0];
  data2 = dataRead2[0];
  data3 = dataRead3[0];

	DMA2->LIFCR	= 0;
	DMA2->HIFCR	= 0;
	i++;
}

int main(void){
	uint32_t sysCLK = getSystemClock();
	uint32_t p2CLK	= getAPB2Clock(sysCLK);
	int dmaStatus = DMA2->LISR;
	int adc1Status = ADC1->SR;
	int adcData;

	uint16_t dmaData;

	dataRead[0] = *getADC1Data();
	dmaData = dataRead[0];

	configureOutput(GPIO_SPEED_V_HIGH, PIN_14, PORTG);
	configureOutput(GPIO_SPEED_V_HIGH, PIN_13, PORTG);
	configureAnalog(NO_PULL, PIN_0, PORTA);
	configureAnalog(NO_PULL, PIN_3, PORTA);
	configureAnalog(NO_PULL, PIN_6, PORTA);

	configDMA2ForADC1();
	configDMA2ForADC2();
	configDMA2ForADC3();

	configADC(ADC1, Channel_6);   //Change to Channel 6 when Multi Mode test
	configADC(ADC2, Channel_3);
	configADC(ADC3, Channel_0);

	setSampleTime(CYCLE_15, ADC1, Channel_6);
	setSampleTime(CYCLE_15, ADC2, Channel_3);
	setSampleTime(CYCLE_15, ADC3, Channel_0);

  //CHANGE RESOLUTION HERE *************************************************************
	setResolution(RESOLUTION_8_BITS, ADC1);
	setResolution(RESOLUTION_8_BITS, ADC2);
	setResolution(RESOLUTION_8_BITS, ADC3);
  
	adcEnableMultiADC();
  
	setContHigh();
	setJautoHigh();
	setScanHigh();

  enableDMA();
	startRegularConv(ADC1);
	startInjectedConv(ADC1);

	HAL_NVIC_EnableIRQ(ADC_IRQn);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

    while(1){
    	writeOne(PIN_13, PORTG);
    	writeZero(PIN_14, PORTG);
    	_delay(100000);

    	writeZero(PIN_13, PORTG);
    	writeOne(PIN_14, PORTG);
    	_delay(100000);
    }
}

void _delay(int delay){
	while(delay != 0)
		delay--;
}


  
void setContHigh(){
	ADC1->CR2 |= CONTINUOUS_CONVERSION;
}
void setJautoHigh(){
	ADC1->CR1 |= SET_JAUTO;
}
void setScanHigh(){
	ADC1->CR1 |= (1 << 8);
}

void setContLow(){
	ADC1->CR2 &= ~CONTINUOUS_CONVERSION;
}
void setJautoLow(){
	ADC1->CR1 &= ~SET_JAUTO;
}
void setScanLow(){
	ADC1->CR1 &= ~(1 << 8);
}
