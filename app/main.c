#include "stm32f4xx.h"

#include "Gpio.h"
#include "Adc.h"

//	int result;

//void ADC_IRQHandler(void){
//
//
//	result = getRegularData(ADC1);
//	//********************************
//	ADC1->SR = 0;
//	ADC2->SR = 0;
//	ADC3->SR = 0;
//}


int main(void){
	configureOutput(GPIO_SPEED_V_HIGH, PIN_14, PORTG);
	configureOutput(GPIO_SPEED_V_HIGH, PIN_13, PORTG);


	configureAnalog(NO_PULL, PIN_0, PORTA);
	configureADC(ADC1);
	setSampleTime(CYCLE_15, ADC1, 0);
	setResolution(RESOLUTION_8_BITS, ADC1);

	int result;
	int status = ADC1->SR;


	startRegularConv(ADC1);
//	HAL_NVIC_EnableIRQ(ADC_IRQn);

    while(1){
    	writeOne(PIN_13, PORTG);
    	writeZero(PIN_14, PORTG);
    	_delay(100000);
    	status = ADC1->SR;
    	result = ADC1->DR;
    	writeZero(PIN_13, PORTG);
    	writeOne(PIN_14, PORTG);
    	_delay(100000);
    }
}

void _delay(int delay){
	while(delay != 0)
		delay--;
}
