#include "Gpio.h"
#include "stm32f4xx_hal_rcc.h"

/**
 * configureOutput:
 *
 * This function configure the pin to become an output pin.
 *
 * @direction	is the output mode
 * @pinNum		is the pin number of the port
 * @port		is the port to configure
 */
void configureOutput(int direction, int pinNum, GPIO *port){

	gpioUnresetEnableClock(port);

	port->MODER &= ~(3 << (pinNum*2));
	port->MODER |= direction << (pinNum*2);
	port->OTYPER &= ~(1 << (pinNum));
	port->OSPEED &= ~(3 << (pinNum*2));
	port->OSPEED |= GPIO_SPEED_V_HIGH << (pinNum*2);
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
	port->MODER &= ~(3 << (pinNum*2));
	port->MODER |= 0 << (pinNum*2);
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


