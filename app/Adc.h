#ifndef	__ADC_H__
#define	__ADC_H__

#include <stdint.h>
typedef struct ADC_t ADC;
#include "Rcc.h"
struct ADC_t{
	uint32_t  SR;
	uint32_t  CR1;
	uint32_t  CR2;
	uint32_t  SMPR1;
	uint32_t  SMPR2;
	uint32_t  JOFR1;
	uint32_t  JOFR2;
	uint32_t  JOFR3;
	uint32_t  JOFR4;
	uint32_t  HTR;
	uint32_t  LTR;
	uint32_t  SQR1;
	uint32_t  SQR2;
	uint32_t  SQR3;
	uint32_t  JSQR;
	uint32_t  JDR1;
	uint32_t  JDR2;
	uint32_t  JDR3;
	uint32_t  JDR4;
	uint32_t  DR;
};

typedef struct CommonADC_t CommonADC;
struct CommonADC_t{
  uint32_t CSR;
  uint32_t CCR;
  uint32_t CDR;
};

#define COMMON_ADC  ((CommonADC*)0x40012300)
#define ADC1        ((ADC*)0x40012000)
#define ADC2        ((ADC*)0x40012100)
#define ADC3        ((ADC*)0x40012200)

#define AWAKEN_ADC	1

#define START_REGULAR_CONVERSION	(1 << 30)
#define START_INJECT_CONVERSION		(1 << 22)

#define EOC_INTERRUPT_ENB		(1 << 5)
#define JEOC_INTERRUPT_ENB		(1 << 7)
//********************************************
#define ENABLE_WATCHDOG			(1 << 23)
#define ENABLE_JWATCHDOG		(1 << 22)
//Mode (Single Mode or ContinuousMode)********
#define CONTINUOUS_CONVERSION	(1 << 1)
//Resolution**********************************
#define RESOLUTION_12_BITS	0
#define RESOLUTION_10_BITS	1
#define RESOLUTION_8_BITS	2
#define RESOLUTION_6_BITS	3

typedef enum{
	CYCLE_3,
	CYCLE_15,
	CYCLE_28,
	CYCLE_56,
	CYCLE_84,
	CYCLE_112,
	CYCLE_114,
	CYCLE_480
}SampleTime;

void configureADC(ADC* aDCx);

void setResolution(int res, ADC* aDCx);
void setSampleTime(SampleTime sampTime, ADC* aDCx, int channel);

//void setRegularQueue(int numOfChannel);	//SET QUEUE (TO DO)

int getRegularData(ADC* aDCx);
int getInjectedData(ADC* aDCx, int queue);


#endif	//__Adc_H__
