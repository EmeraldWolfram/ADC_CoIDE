#ifndef	__Register_H__
#define	__Register_H__

#include <stdint.h>

#ifndef HOST
#define RCC_BASE_ADDRESS        0x40023800

#define COMMON_ADC_BASE_ADDRESS 0x40012300
#define ADC1_BASE_ADDRESS       0x40012000
#define ADC2_BASE_ADDRESS       0x40012100
#define ADC3_BASE_ADDRESS       0x40012200

#define DMA1_BASE_ADDRESS       0x40026000
#define DMA2_BASE_ADDRESS       0x40026400

#define GPIOA_BASE_ADDRESS      0x40020000
#define GPIOB_BASE_ADDRESS      0x40020400
#define GPIOC_BASE_ADDRESS      0x40020800
#define GPIOD_BASE_ADDRESS      0x40020C00
#define GPIOE_BASE_ADDRESS      0x40021000
#define GPIOF_BASE_ADDRESS      0x40021400
#define GPIOG_BASE_ADDRESS      0x40021800

#else

#define RCC_BASE_ADDRESS    (&HostRcc)
#include "HostRcc.h"
//#error I am trying to be genius



#endif  //HOST


#endif	//__Register_H__
