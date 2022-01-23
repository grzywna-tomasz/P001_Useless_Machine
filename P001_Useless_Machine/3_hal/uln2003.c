/*
 * uln2003.c
 *
 * Created: 23.01.2022 18:50:12
 *  Author: Grzywna
 */
#include "IO.h"
#include "standard_types.h"

static uint8_t Uln2003_CurrentPin = 0;

void Uln2003_StepRight(void)
{
	IO_SetPort(PORTC, 0x00);
	IO_SetPin(PORTC, Uln2003_CurrentPin, ~IO_GetPin(PORTC, Uln2003_CurrentPin));
	Uln2003_CurrentPin++;
	Uln2003_CurrentPin %= 4;
}