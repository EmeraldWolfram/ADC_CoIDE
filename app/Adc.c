#include "Adc.h"

/***************************************************************************
 * Author	: Steven Foong Ghin Yew (Emerald)
 * Course	: RMB2
 * Date		: 20 November 2015
 ***************************************************************************
 ***************************************************************************
 * This file consist of 11 functions that simplify the development
 * of software using ADC. The function are listed below:
 *
 * 1. configADC
 * 2. setResolution
 * 3. setSampleTime
 * 4. getRegularData
 * 5. getInjectedData
 * 6. startRegularConv
 * 7. startInjectedConv
 * 8. addRegularQueue
 * 9. addInjectedQueue
 * 10. enableVbat
 * 11. enableTempSensor
 * 12. enableRegularWD
 * 13. enableInjectedWD
 * 14. setContMode
 * 15. setDisconMode
 * 16. adcEnableDMA
 *
 ****************************************************************************
 ****************************************************************************
 *
 * Control that can be made but not written as function here are:
 *
 * @aDCx	can be ADC1, ADC2 or ADC3
 *
 * 1. Alignment of data (Right or Left) default set to right in configureADC
 * 	  For left align, use the following code:
 * 	  aDCx->CR2	|= LEFT_ALIGN;
 *
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 * 1. configADC:
 *
 * This function enable the ADCx by awaken the ADCx and enable the CLOCK
 * - Enabled EOC and JEOC to generate Interrupt
 * - Channel 0 set as 1st and only conversion in regular queue
 * - Channel 18 (Vbat) set as 1st and only conversion in injected queue
 * - Data obtained is right aligned
 * - Only 1 conversion will be done
 * 
 * NOTE: It call adcUnresetEnableClock in Rcc.h to enable the CLOCK
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 *****************************************************************************/
void configADC(ADC_t* aDCx, Channel regularChannel){
	adcUnresetEnableClock(aDCx);
  
	aDCx->CR2 |= AWAKEN_ADC;      //Wake up the ADC
  
  /*****Enable EOC interrupts*****/
	aDCx->CR1 |= EOC_INTERRUPT_ENB;
	aDCx->CR1 |= JEOC_INTERRUPT_ENB;
  /*******************************/
	COMMON_ADC->CCR |= ENABLE_VBAT;     //Enable Vbat for Injected Group
	aDCx->JSQR	&= ~(3 << 20);          //1 Conversion in Injected Group
	aDCx->JSQR	|= Channel_18;          //Queue Channel_18 (Vbat) to Injected Group
  
	aDCx->SQR1	&= ~(15 << 20);         //1 Conversion in Regular Group
	aDCx->SQR3	|= regularChannel;           //Queue Channel_0 (PA0) to Injected Group
  
	aDCx->CR2	&= ~CONTINUOUS_CONVERSION;  //Single Conversion and END
	aDCx->CR2	&= ~LEFT_ALIGN;             //Right Align Data
}

/**
 * 2. setResolution:
 *
 * This function configure the resolution of the converted analogue signal.
 * Define how precise the result wanted.
 *
 * NOTE: The resolution set for every channels configured for ADCx
 *
 * @aDCx	is the selection of ADC (ADC1, ADC2 or ADC3)
 * @res		is the resolution of the result, (6, 8, 10 or 12)bits
 */
void setResolution(Resolution res, ADC_t* aDCx){
	aDCx->CR1 &= ~(3 << 24);
	aDCx->CR1 |= res << 24;
}

/**
 * 3. setSampleTime:
 *
 * This function select the sample time for conversion of each channel.
 * Define the time to charge up the capacitor and stabilise the voltage
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 * @sampTime	is the resolution of the result, (6, 8, 10 or 12)bits
 */
void setSampleTime(SampleTime sampTime, ADC_t* aDCx, Channel channel){
	if(channel < 10){
		aDCx->SMPR2 &= ~(7 << channel);
		aDCx->SMPR2 |= (sampTime << channel*3);
	}
	else {
		aDCx->SMPR1 &= ~(7 << channel);
		aDCx->SMPR1 |= (sampTime << (channel - 10)*3);
	}
}

/**
 * 4. getRegularData:
 *
 * This function read the data of regular group and return it to the caller
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 */
int getRegularData(ADC_t* aDCx){
	int data = (aDCx->DR);
	return data;
}

/**
 * 5. getInjectedData:
 *
 * This function read the data of injected group and return it to the caller
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 * @queue		is the current position in the sequence of queue in the list
 */
int getInjectedData(ADC_t* aDCx, int queue){
	switch(queue){
	case 0:
		return aDCx->JDR1;
		break;
	case 1:
		return aDCx->JDR2;
		break;
	case 2:
		return aDCx->JDR3;
		break;
	case 3:
		return aDCx->JDR4;
		break;
	default:
		return aDCx->JDR1;
		break;
	}
}

/**
 * 6. startRegularConv:
 *
 * This function start the conversion of the regular group
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 */
void startRegularConv(ADC_t* aDCx){
	aDCx->CR2 |= START_REGULAR_CONVERSION;
}

/**
 * 7. startInjectedConv:
 *
 * This function start the conversion of the Injected group
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 */
void startInjectedConv(ADC_t* aDCx){
	aDCx->CR2 |= START_INJECT_CONVERSION;
}

/**
 * 8. addRegularQueue:
 *
 * This function add the input channel into the current regular
 * conversion group queue. Note that there is a default channel_0
 * set as the 1st ADC conversion. The 1st channel in the queue can
 * be modified manually. Please refer to datasheet if wanted to
 * change the 1st conversion channel in the queue.
 *
 * If the queue is FULL with 16 channel queue,
 * the function will not do anything
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 * @channel		is the channel to add to the current queue
 */
void addRegularQueue(ADC_t* aDCx, Channel channel){
	int numOfConversion = (aDCx->SQR1) >> 20;
	if(numOfConversion < 6){
		numOfConversion++;
		aDCx->SQR3 &= ~(31 << (numOfConversion * 5));
		aDCx->SQR3 |= channel << (numOfConversion * 5);
	}
	else if(numOfConversion < 12){
		numOfConversion++;
		aDCx->SQR2 &= ~(31 << ((numOfConversion - 6) * 5));
		aDCx->SQR2 |= channel << ((numOfConversion - 6) * 5);
	}
	else if(numOfConversion < 15){
		numOfConversion++;
		aDCx->SQR1 &= ~(31 << ((numOfConversion - 12) * 5));
		aDCx->SQR1 |= channel << ((numOfConversion - 12) * 5);
	}
	aDCx->SQR1 &= ~(15 << 20);
	aDCx->SQR1 |= numOfConversion << 20;
}

/**
 * 9. addInjectedQueue:
 *
 * This function add the input channel into the current injected
 * conversion group queue. Note that there is a default channel_0
 * set as the 1st ADC conversion. The 1st channel in the queue can
 * be modified manually. Please refer to datasheet if wanted to
 * change the 1st conversion channel in the queue.
 *
 * If the queue is FULL with 4 channel queue,
 * the function will not do anything
 *
 * @aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 * @channel		is the channel to add to the current queue
 */
void addInjectedQueue(ADC_t* aDCx, Channel channel){
	int numOfConversion = (aDCx->JSQR) >> 20;
	if(numOfConversion < 4){
		numOfConversion++;
		aDCx->JSQR &= ~(31 << (numOfConversion * 5));
		aDCx->JSQR |= channel << (numOfConversion * 5);
	}
	aDCx->JSQR &= ~(15 << 20);
	aDCx->JSQR |= numOfConversion << 20;
}

/**
 * 10. enableVbat & 11. enableTempSensor :
 *
 *	This two functions enable the internal sensors Vbat (battery voltage)
 *	& TempSensor (temperature degree celcius)
 *
 *	Both sensors are connected to channel 18 in stm32f42x & stm32f43x
 *	Both sensors are connected to channel 16 in stm32f40x & stm32f41x
 */
void enableVbat(void){
	COMMON_ADC->CCR |= ENABLE_VBAT;
	COMMON_ADC->CCR &= ~ENABLE_TEMP_AND_VREFINT;
}

void enableTempSensor(){
	COMMON_ADC->CCR |= ENABLE_TEMP_AND_VREFINT;
	COMMON_ADC->CCR &= ~ENABLE_VBAT;
}

/**
 * 12. enableRegularWD & 13. enableInjectedWD :
 *
 *	This two functions enable the Watchdog feature to guard the input signal
 *	referencing to the Threshold set in aDCx->HTR and aDCx->LTR.
 *
 *	AWD flag will be raised in aDCx->SR when the input signal exceed the limit
 *
 *	@aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 *	@useIRQ		is the selection of interrupt generation
 *				YES	= 	generate interrupt when AWD rise
 *				NO	= 	do not generate interrupt when AWD rise
 */
void enableRegularWD(ADC_t* aDCx, Question useIRQ){
	aDCx->CR1	|= ENABLE_REGULAR_WATCHDOG;
	if(useIRQ == YES)
		aDCx->CR1 |= AWD_INTERRUPT_ENB;
	else
		aDCx->CR1 &= ~AWD_INTERRUPT_ENB;
}

void enableInjectedWD(ADC_t* aDCx, Question useIRQ){
	aDCx->CR1	|= ENABLE_INJECTED_WATCHDOG;
	if(useIRQ == YES)
		aDCx->CR1 |= AWD_INTERRUPT_ENB;
	else
		aDCx->CR1 &= ~AWD_INTERRUPT_ENB;
}

/**
 * 14. setContMode
 *
 *	This function enable both the Regular Group and Injected Group to
 *  perform ADC continuosly. However, it remove the higher priority of
 *  Injected Group to Regular Group, making both Group sharing the same
 *  priority. To DISABLE the auto conversion on Injected Group, enter
 *    aDCx->CR1 &= ~SET_JAUTO;
 *  into your function.
 *
 *	@aDCx		is the selection of ADC (ADC1, ADC2 or ADC3)
 */

void setContMode(ADC_t* aDCx){
  aDCx->CR2 |= CONTINUOUS_CONVERSION;
  aDCx->CR1 |= SET_JAUTO;
}

/**
 * 15. setDisconMode
 *
 *	This function enable the selected group to chop the queue into
 *  smaller group of channels queue. Eg. Regular Group queued 
 *  1. Channel_0
 *  2. Channel_1
 *  3. Channel_6
 *  4. Channel_7
 *  5. Channel_12
 *
 *  with grp = REGULAR_GRP and numOfChnDiscon = 3
 *  the conversion will perform when triggered
 *  1. Channel_0
 *  2. Channel_1
 *  3. Channel_6
 *  Then, it wait for second trigger and convert
 *  1. Channel_7
 *  2. Channel_12
 *  Then restart from Channel_0 upon the 3rd time trigger
 *
 *	@aDCx		          is the selection of ADC (ADC1, ADC2 or ADC3)
 *	@grp		          is the selection of Group (REGULAR_GRP or INJECTED_GRP)
 *	@numOfChnDiscon		is the number of channel to be chop into a small group
 */
void setDisconMode(ADC_t* aDCx, int grp, int numOfChnDiscon){
  if(grp == REGULAR_GRP){
    aDCx->CR1 |= ENABLE_REGULAR_DISCON;
    aDCx->CR1 |= numOfChnDiscon << 13;
  }
  else{
    aDCx->CR1 |= ENABLE_INJECTED_DISCON;
    aDCx->CR1 |= numOfChnDiscon << 13;
    aDCx->CR1 &= ~SET_JAUTO;            //JAUTO cannot be set together with DISCON, check datasheet
  }
}

/**
 * 16. adcEnableSignleDMA	&		17. adcEnableMultiADC
 *
 *	These function enable the use of DMA to transfer data from DR register to Memory Located
 *
 *	@aDCx		          is the selection of ADC (ADC1, ADC2 or ADC3)
 */

void adcEnableSignleDMA(ADC_t* aDCx){
	aDCx->CR2 |= 3 << 8;	//ENABLE DMA and DDS
}

void adcEnableMultiADC(){
	COMMON_ADC->CCR |= ~(7 << 13);	//MASKED DMA config bits
	COMMON_ADC->CCR |= 4 << 13;		//Triple ADC Mode
	COMMON_ADC->CCR |= 0x15;	//ADC1, ADC2, ADC3 working together on Regular Simultaneous Mode.

}
