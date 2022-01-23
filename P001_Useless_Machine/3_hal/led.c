/*
 * led.c
 *
 * Created: 23.01.2022 18:06:42
 *  Author: Grzywna
 */ 

#include "IO.h"
#include "standard_types.h"

void LedToggle(void)
{
	IO_SetPin(PORTB, TEST_LED_INDEX, ~IO_GetPin(PORTB, TEST_LED_INDEX));
}