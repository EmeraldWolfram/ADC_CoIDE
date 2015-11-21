#ifndef	__ADC_H__
#define	__ADC_H__

#include <stdint.h>
typedef struct ADC_t ADC;
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
  uint32_t CDR;
  uint32_t CDR;
};

#define COMMON_ADC  ((CommonADC*)0x40012300)
#define ADC1        ((ADC*)0x40012000)
#define ADC2        ((ADC*)0x40012100)
#define ADC3        ((ADC*)0x40012200)

#endif	//__Adc_H__
