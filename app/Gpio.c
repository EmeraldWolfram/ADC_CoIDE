#include "Gpio.h"

void gpioUnresetEnableClock(GPIO* port){
	int valToShift = ((int)port - (0x40020000))/(0x400);

	RCC_reg->RCC_AHB1RSTR	&= ~GPIOx_RESET(valToShift);
	RCC_reg->RCC_AHB1ENR	|= GPIOx_ENABLE_CLOCK(valToShift);
}

/**
 * configureAnalog:
 *
 * This function configure the pin to become an analogue input pin.
 *
 * @pullMeth	is the method of pull (no pull, pull-up, pull-down or reserve)
 * @pinNum		is the pin number of the port
 * @port		is the port to configure
 */
void configureAnalog(int pullMeth, int pinNum, GPIO *port){
	gpioUnresetEnableClock(port);
	port->MODER |= GPIO_MODE_ANALOG << (pinNum*2);
	port->PUPDR &= ~(3 << (pinNum*2));		//MASK PUPDR reg and clear respective bits
	port->PUPDR |= pullMeth << (pinNum*2);
}

/**
 * configureAltFunc:
 *
 * This function configure the pin to become an analogue input pin.
 *
 * @pullMeth	is the method of pull (no pull, pull-up, pull-down or reserve)
 * @pinNum		is the pin number of the port
 * @port		is the port to configure
 */
void configureAltFunc(int pullMeth, int pinNum, GPIO *port){
	gpioUnresetEnableClock(port);
	port->MODER &= ~(3 << (pinNum*2));		//MASK MODER reg and CLEAR selected bits
	port->MODER |= GPIO_MODE_ALTFUNC << (pinNum*2);
	port->PUPDR &= ~(3 << (pinNum*2));		//MASK PUPDR reg and CLEAR selected bits
	port->PUPDR |= pullMeth << (pinNum*2);
}

/**
 * configureOutput:
 *
 * This function configure the pin to become an output pin.
 *
 * @direction	is the output mode
 * @pinNum		is the pin number of the port
 * @port		is the port to configure
 */
void configureOutput(int speed, int pinNum, GPIO *port){

	gpioUnresetEnableClock(port);

	port->MODER &= ~(3 << (pinNum*2));		//MASK MODER reg and CLEAR selected bits
	port->MODER |= GPIO_MODE_OUTPUT << (pinNum*2);
	port->OTYPER &= ~(1 << (pinNum));
	port->OSPEED &= ~(3 << (pinNum*2));
	port->OSPEED |= speed << (pinNum*2);
}

/**
 * configureInput:
 *
 * This function configure the pin to become an input pin.
 *
 * @pullMeth	is the method of pull (no pull, pull-up, pull-down or reserve)
 * @pinNum		is the pin number of the port
 * @port		is the port to configure
 */
void configureInput(int pullMeth, int pinNum, GPIO *port){
	gpioUnresetEnableClock(port);
	port->MODER &= ~(3 << (pinNum*2));		//MASK MODER reg and CLEAR selected bits
	port->MODER |= GPIO_MODE_INPUT << (pinNum*2);
	port->PUPDR &= ~(3 << (pinNum*2));
	port->PUPDR |= pullMeth << (pinNum*2);
}

/**
 * writeOne:
 *
 * This function set the particular pin to 1
 *
 * @pinNum		is the pin number of the port
 * @port		is the port that have the particular pin
 */
void writeOne(uint16_t pinNum, GPIO *port){
	port->BSRR	= (uint32_t)(1 << pinNum);
}
/**
 * writeZero:
 *
 * This function set the particular pin to 0
 *
 * @pinNum		is the pin number of the port
 * @port		is the port that have the particular pin
 */
void writeZero(uint16_t pinNum, GPIO *port){
	port->BSRR = (uint32_t)(1 << (pinNum + 16));
}


