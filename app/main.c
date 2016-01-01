#include "stm32f429xx.h"
#include "Gpio.h"
#include "Adc.h"
#include "Dma.h"

int count = 0;
int i = 0;
uint16_t *dataRead1, *dataRead2, *dataRead3;

void ADC_IRQHandler(void){
	int data = 0;
	data = COMMON_ADC->CDR;
	ADC1->SR = 0;
	count++;
}

void DMA2_Stream0_IRQHandler(void){
	int data1 = 0;
	int data2 = 0;
	int data3 = 0;

	dataRead1 = getADC1Data();
	dataRead2 = getADC2Data();
	dataRead3 = getADC3Data();
	data1 	  = dataRead1[0];
	data2 	  = dataRead2[0];
	data3 	  = dataRead3[0];


	int a = ADC1->DR;
	int b = ADC2->DR;
	int c = ADC3->DR;
	int d = COMMON_ADC->CDR;

	DMA2->LIFCR	= 0;
	DMA2->HIFCR	= 0;
	i++;
}

void DMA2_Stream2_IRQHandler(void){
	int data2 = 0;
	dataRead2 = getADC2Data();
	data2 	  = dataRead2[0];

	DMA2->LIFCR	= 0;
	DMA2->HIFCR	= 0;
	i++;
}

void DMA2_Stream1_IRQHandler(void){
	int data3 = 0;
	dataRead3 = getADC3Data();
	data3 = dataRead3[0];

	DMA2->LIFCR	= 0;
	DMA2->HIFCR	= 0;
	i++;
}

int main(void){
	uint32_t sysCLK = getSystemClock();
	uint32_t p2CLK	= getAPB2Clock(sysCLK);

	configureOutput(GPIO_SPEED_V_HIGH, PIN_14, PORTG);
	configureOutput(GPIO_SPEED_V_HIGH, PIN_13, PORTG);
	configureAnalog(NO_PULL, PIN_0, PORTA);
	// configureAnalog(NO_PULL, PIN_3, PORTA);
	// configureAnalog(NO_PULL, PIN_6, PORTA);

	configDMA2ForADC1();
	// configDMA2ForADC2();
	// configDMA2ForADC3();

	configADC(ADC1, Channel_0);   //Change to Channel 6 when Multi Mode test
	// configADC(ADC2, Channel_3);
	// configADC(ADC3, Channel_0);
//	addRegularQueue(ADC1, Channel_3);
//	addRegularQueue(ADC1, Channel_6);

	setSampleTime(CYCLE_15, ADC1, Channel_0);
	// setSampleTime(CYCLE_15, ADC2, Channel_3);
	// setSampleTime(CYCLE_15, ADC3, Channel_0);

  //CHANGE RESOLUTION HERE *************************************************************
	setResolution(RESOLUTION_8_BITS, ADC1);
	// setResolution(RESOLUTION_8_BITS, ADC2);
	// setResolution(RESOLUTION_8_BITS, ADC3);

//	adcEnableSignleDMA(ADC1);
//	adcEnableSignleDMA(ADC2);
//	adcEnableSignleDMA(ADC3);
	adcEnableMultiADC();
  
  setAllOffset(0x80);
	setContMode(ADC1);
	// setContMode(ADC2);
	// setContMode(ADC3);

	enableDMA();
	startRegularConv(ADC1);
	// startRegularConv(ADC2);
	// startRegularConv(ADC3);

	HAL_NVIC_EnableIRQ(ADC_IRQn);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
	HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

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
