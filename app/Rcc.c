#include "Rcc.h"








uint32_t getSystemClock(){
	int divM, xN, divP, divAHB;
	int sysClock;
	int enbAHBPrescale = RCC_reg->RCC_CFGR & 256;

	if(enbAHBPrescale == 0)
		divAHB = 1;
	else
		divAHB = 1 << (((RCC_reg->RCC_CFGR >> 4) & 7) + 1);

	xN = (RCC_reg->RCC_PLLCFGR >> 6) & 511;
	divM = (RCC_reg->RCC_PLLCFGR & 63);
	divP = 1 << (((RCC_reg->RCC_PLLCFGR >> 16) & 3) + 1);

	if(((RCC_reg->RCC_CFGR & 0xC) >> 2) == 0)
		sysClock = INTERNAL_CLOCK / divAHB;
	else if(((RCC_reg->RCC_CFGR & 0xC) >> 2) == 1)
		sysClock = CRYSTAL_CLOCK / divAHB;
	else {
		if(((RCC_reg->RCC_PLLCFGR >> 22) & 1) == 0)
			sysClock = (INTERNAL_CLOCK * xN) / (divM * divP * divAHB);
		else
			sysClock = (CRYSTAL_CLOCK) / (divM * divP * divAHB) * xN;
	}

	return sysClock;
}

uint32_t getAPB2Clock(uint32_t sysClock){
	int divAPB2, aPB2Clock;

	if(ENABLE_APB2_PRESCALE)
		divAPB2 = 1 << (((RCC_reg->RCC_CFGR >> 13) & 3) + 1);
	else
		divAPB2 = 1;

	aPB2Clock = sysClock / divAPB2;

	return aPB2Clock;
}

