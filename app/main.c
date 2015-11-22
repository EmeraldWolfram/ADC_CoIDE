#include "stm32f4xx.h"

#include "Gpio.h"

int main(void){
	configureOutput(GPIO_SPEED_V_HIGH, PIN_14, PORTG);
	configureOutput(GPIO_SPEED_V_HIGH, PIN_13, PORTG);
	configureAnalog(NO_PULL, PIN_13, PORTB);

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
