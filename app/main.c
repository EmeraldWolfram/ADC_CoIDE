#include "stm32f4xx.h"

#include "Gpio.h"
#include "Adc.h"

void ADC_IRQHandler(void){
	int regStatus	= ADC1->SR;
	int injStatus	= ADC1->SR;
	int count;
	volatile int regResult, injResult;
	regStatus	&= 2;
	injStatus	&= 4;

	if((ADC1->SR & 2) != 0)
		regResult = getRegularData(ADC1);

	if((ADC1->SR & 4) != 0){
		injResult = getInjectedData(ADC1, 0);
	}
	ADC1->SR = 0;
}


int main(void){
	configureOutput(GPIO_SPEED_V_HIGH, PIN_14, PORTG);
	configureOutput(GPIO_SPEED_V_HIGH, PIN_13, PORTG);
	int queue;
	configureAnalog(NO_PULL, PIN_0, PORTA);
	enableVbat();
	configureADC(ADC1);

	setSampleTime(CYCLE_15, ADC1, Channel_0);
	setSampleTime(CYCLE_84, ADC1, Channel_18);

	setResolution(RESOLUTION_12_BITS, ADC1);
	ADC1->CR2 |= CONTINUOUS_CONVERSION;
	ADC1->CR1 |= SET_JAUTO;
	startRegularConv(ADC1);
	startInjectedConv(ADC1);

	HAL_NVIC_EnableIRQ(ADC_IRQn);

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
