#ifndef	__Gpio_H__
#define	__Gpio_H__

#include <stdint.h>
typedef struct GPIO_t GPIO;

#include "Rcc.h"


#define	GPIO_OUTPUT	GPIO_MODE_OUTPUT_PP
#define	GPIO_INPUT	GPIO_MODE_INPUT

struct GPIO_t{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEED;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
};

#define PIN_0	0
#define PIN_1	1
#define PIN_2	2
#define PIN_3	3
#define PIN_4	4
#define PIN_5	5
#define PIN_6	6
#define PIN_7	7
#define PIN_8	8
#define PIN_9	9
#define PIN_10	10
#define PIN_11	11
#define PIN_12	12
#define PIN_13	13
#define PIN_14	14
#define PIN_15	15

#define GPIO_MODE_INPUT		0
#define GPIO_MODE_OUTPUT	1
#define GPIO_MODE_ALTFUNC	2
#define GPIO_MODE_ANALOG	3

#define	GPIO_SPEED_LOW		0
#define	GPIO_SPEED_MEDIUM	1
#define	GPIO_SPEED_HIGH		2
#define	GPIO_SPEED_V_HIGH	3

#define GPIOA_BASE_ADDRESS	0x40020000
#define GPIOB_BASE_ADDRESS	0x40020400
#define GPIOC_BASE_ADDRESS	0x40020800
#define GPIOD_BASE_ADDRESS	0x40020C00
#define GPIOE_BASE_ADDRESS	0x40021000
#define GPIOF_BASE_ADDRESS	0x40021400
#define GPIOG_BASE_ADDRESS	0x40021800

#define	PORTA	((GPIO *)GPIOA_BASE_ADDRESS)
#define	PORTB	((GPIO *)GPIOB_BASE_ADDRESS)
#define	PORTC	((GPIO *)GPIOC_BASE_ADDRESS)
#define	PORTD	((GPIO *)GPIOD_BASE_ADDRESS)
#define	PORTE	((GPIO *)GPIOE_BASE_ADDRESS)
#define	PORTF	((GPIO *)GPIOF_BASE_ADDRESS)
#define	PORTG	((GPIO *)GPIOG_BASE_ADDRESS)

#define NO_PULL		0
#define PULL_UP		1
#define PULL_DOWN	2
#define RESERVE		3

void configureOutput(int direction, int pinNum, GPIO *port);
void configureInput(int pullMeth, int pinNum, GPIO *port);
void writeOne(uint16_t pinNum, GPIO *port);
void writeZero(uint16_t pinNum, GPIO *port);

#endif	//__Gpio_H__
