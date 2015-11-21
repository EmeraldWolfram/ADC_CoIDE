#include "stm32f4xx.h"

#include "Gpio.h"

int main(void){
	configureOutput(GPIO_MODE_OUTPUT, PIN_14, PORTG);
	configureOutput(GPIO_MODE_OUTPUT, PIN_13, PORTG);
	configureOutput(GPIO_MODE_OUTPUT, PIN_13, PORTB);
	configureOutput(GPIO_MODE_OUTPUT, PIN_5,  PORTC);
	configureInput(GPIO_MODE_INPUT,  PIN_0,  PORTA);

    while(1){
//    	writeOne(PIN_13, PORTG);
    	writeZero(PIN_14, PORTG);
    	writeOne(PIN_13, PORTB);
    	writeZero(PIN_5, PORTC);
    	_delay(100000);

    	while(PORTA->IDR & (0x00000001))
    		writeOne(PIN_13, PORTG);

    	writeZero(PIN_13, PORTG);
    	writeOne(PIN_14, PORTG);
    	writeZero(PIN_13, PORTB);
    	writeOne(PIN_5, PORTC);
    	_delay(100000);
    }
}

void _delay(int delay){
	while(delay != 0)
		delay--;
}
