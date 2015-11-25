#ifndef	__ADC_H__
#define	__ADC_H__

/* ADC Channel Table with input GPIO & internal pins
 *
 * =====|===========================|
 *	CHN	| 	ADC1	ADC2	ADC3	|
 * =====|===========================|
 * IN0	|	PA0		PA0		PA0		|
 * IN1	|	PA1		PA1		PA1		|
 * IN2	|	PA2		PA2		PA2		|
 * IN3	|	PA3		PA3		PA3		|
 * =====|===========================|
 * IN4	|	PA4		PA4		PF6		|
 * IN5	|	PA5		PA5		PF7		|
 * IN6	|	PA6		PA6		PF8		|
 * IN7	|	PA7		PA7		PF9		|
 * =====|===========================|
 * IN8	|	PB0		PB0		PF10	|
 * IN9	|	PB1		PB1		PF3		|
 * IN10	|	PC0		PC0		PC0		|
 * IN11	|	PC1		PC1		PC1		|
 * =====|===========================|
 * IN12	|	PC2		PB2		PC2		|
 * IN13	|	PC3		PB3		PC3		|
 * IN14	|	PC4		PC4		PC4		|
 * IN15	|	PC5		PC5		PC5		|
 * =====|===========================|
 *
 */


#include <stdint.h>
typedef struct ADC_Type ADC_t;
#include "Rcc.h"
struct ADC_Type{
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
#define ADC1    	((ADC_t*)0x40012000)
#define ADC2    	((ADC_t*)0x40012100)
#define ADC3    	((ADC_t*)0x40012200)

typedef enum{
	Channel_0,
	Channel_1,
	Channel_2,
	Channel_3,
	Channel_4,
	Channel_5,
	Channel_6,
	Channel_7,
	Channel_8,
	Channel_9,
	Channel_10,
	Channel_11,
	Channel_12,
	Channel_13,
	Channel_14,
	Channel_15,
	Channel_16,
	Channel_17,
	Channel_18
}Channel;
//**************************************************************
#define AWAKEN_ADC	1
#define LEFT_ALIGN	(1 << 11)

#define START_REGULAR_CONVERSION	(1 << 30)
#define START_INJECT_CONVERSION		(1 << 22)

#define EOC_INTERRUPT_ENB		(1 << 5)
#define JEOC_INTERRUPT_ENB		(1 << 7)
#define AWD_INTERRUPT_ENB		(1 << 6)

#define ENABLE_WATCHDOG			(1 << 23)
#define ENABLE_JWATCHDOG		(1 << 22)
//Mode (Single Mode or ContinuousMode)********
#define CONTINUOUS_CONVERSION	(1 << 1)
#define SET_JAUTO				(1 << 10)
//Resolution**********************************
typedef enum{
	RESOLUTION_12_BITS,
	RESOLUTION_10_BITS,
	RESOLUTION_8_BITS,
	RESOLUTION_6_BITS
}Resolution;
//********************************************
#define ENABLE_VBAT				(1 << 22)
#define ENABLE_TEMP_AND_VREFINT	(1 << 23)

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

typedef enum{
	NO,
	YES
}Question;

void configureADC(ADC_t* aDCx);

void setResolution(Resolution res, ADC_t* aDCx);
void setSampleTime(SampleTime sampTime, ADC_t* aDCx, Channel channel);

int getRegularData(ADC_t* aDCx);
int getInjectedData(ADC_t* aDCx, int queue);

void startRegularConv(ADC_t* aDCx);
void startInjectedConv(ADC_t* aDCx);

void addRegularQueue(ADC_t* aDCx, Channel channel);	//Add a queue to the regular group
void addInjectedQueue(ADC_t* aDCx, Channel channel);

void enableVbat();
void enableTempSensor();

void enableRegularWD(ADC_t* aDCx, Question useIRQ);
void enableInjectedWD(ADC_t* aDCx, Question useIRQ);

#endif	//__Adc_H__
