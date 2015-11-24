#include "stm32f4xx.h"

#include "Gpio.h"
#include "Adc.h"



void ADC_IRQHandler(void){
	int regResult	= ADC1->SR;
	int injResult	= ADC1->SR;
	int count;
	regStatus	&= 2;
	injStatus	&= 4;

	if(regularStatus != 0)
		result = getRegularData(ADC1);

	if(injResult != 0){
		if(count > 4)
			count = 0;
		result = getInjectedData(ADC1, count);
		count++;
	}
	//********************************
	ADC1->SR = 0;
}


int main(void){
	configureOutput(GPIO_SPEED_V_HIGH, PIN_14, PORTG);
	configureOutput(GPIO_SPEED_V_HIGH, PIN_13, PORTG);

	configureAnalog(NO_PULL, PIN_0, PORTA);
	configureADC(ADC1);

	setSampleTime(CYCLE_15, ADC1, Channel_0);
	setResolution(RESOLUTION_8_BITS, ADC1);

	startRegularConv(ADC1);
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
