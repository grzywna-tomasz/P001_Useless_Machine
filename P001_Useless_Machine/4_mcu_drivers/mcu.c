/*
 * mcu.c
 *
 * Created: 12.05.2021 23:36:56
 *  Author: Grzywna
 */ 

#include "standard_types.h"
#include "mcu.h"

#include <avr/power.h>

void Mcu_ClockInit(void)
{
	/* Setup clock divider */
	CLKPR = 0x80;
	CLKPR = F_DIVIDER_1;
}