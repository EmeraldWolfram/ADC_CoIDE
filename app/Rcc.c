#include "Rcc.h"

void gpioUnresetEnableClock(GPIO* port){
	int valToShift = ((int)port - (0x40020000))/(0x400);

	RCC_reg->RCC_AHB1RSTR	&= ~GPIOx_RESET(valToShift);
	RCC_reg->RCC_AHB1ENR	|= GPIOx_ENABLE_CLOCK(valToShift);
}

void adcUnresetEnableClock(ADC* aDCx){
	int x = ((int)aDCx - 0x40012000)/(0x100);

	RCC_reg->RCC_APB2ENR	|= ADCx_ENABLE_CLOCK(x);
	RCC_reg->RCC_APB2RSTR	&= ~ADC_RESET;
}
