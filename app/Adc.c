#include "Adc.h"
#include "stm32f4xx_hal_rcc.h"

/**
 * configureADC:
 *
 * This function enable the ADCx by awaken the ADCx and enable the CLOCK
 *
 * NOTE: It call adcUnresetEnableClock in Rcc.h to enable the CLOCK
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 */
void configureADC(ADC* aDCx){
	adcUnresetEnableClock(aDCx);
	aDCx->CR2 |= AWAKEN_ADC;
	aDCx->CR1 |= EOC_INTERRUPT_ENB;
}

/**
 * setResolution:
 *
 * This function configure the resolution of the converted analogue signal.
 * Define how precise the result wanted.
 *
 * NOTE: The resolution set for every channels configured for ADCx
 *
 * @aDCx	is the selection of ADC (ADC1, ADC2 or ADC3)
 * @res		is the resolution of the result, (6, 8, 10 or 12)bits
 */
void setResolution(int res, ADC* aDCx){
	aDCx->CR1 &= ~(3 << 24);	//MASK RESOLUTION control bits
	aDCx->CR1 |= res << 24;
}

/**
 * setSampleTime:
 *
 * This function select the sample time for conversion of each channel.
 * Define the time to charge up the capacitor and stabilise the voltage
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 * @sampTime	is the resolution of the result, (6, 8, 10 or 12)bits
 */
void setSampleTime(SampleTime sampTime, ADC* aDCx, int channel){
	if(channel < 10){
		aDCx->SMPR2 &= ~(7 << channel);	//MASK SAMPLING TIME control bits
		aDCx->SMPR2 |= (sampTime << channel*3);
	}
	else {
		aDCx->SMPR1 &= ~(7 << channel);
		aDCx->SMPR1 |= (sampTime << (channel - 10)*3);
	}
}

/**
 * getRegularData:
 *
 * This function read the data of regular group and return it to the caller
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 */
int getRegularData(ADC* aDCx){
	return aDCx->DR;
}

/**
 * getInjectedData:
 *
 * This function read the data of injected group and return it to the caller
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 * @queue		is the current position in the sequence of queue in the list
 */
int getInjectedData(ADC* aDCx, int queue){
	switch(queue)
	case 0:
		return aDCx->JDR1;
		break;
	case 1:
		return aDCx->JDR2;
		break;
	case 3:
		return aDCx->JDR3;
		break;
	case 4:
		return aDCx->JDR4;
		break;
	default:
		return aDCx->JDR1;
		break;
}
