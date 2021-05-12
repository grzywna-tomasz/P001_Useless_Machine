/*
 * P001_Useless_Machine.c
 *
 * Created: 12.05.2021 20:49:36
 * Author : Grzywna
 */ 
#include <util/delay.h>
#include "standard_types.h"
#include "IO.h"


#define TEST_LED_INDEX	(uint8_t)(5)

int main (void)
{
	DDRB = 0b11111111;
	
	while(TRUE)
	{
		IO_SetPin(PORTB, TEST_LED_INDEX, TRUE);
		_delay_ms(10000);
		IO_SetPin(PORTB, TEST_LED_INDEX, FALSE);
		_delay_ms(10000);
	}
}

