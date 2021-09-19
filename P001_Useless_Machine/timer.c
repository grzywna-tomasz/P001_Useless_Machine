/*
 * Timer.c
 *
 * Created: 05.09.2021 14:00:51
 *  Author: Grzywna
 */ 

#include "standard_types.h"
#include "mcu.h"
#include "timer.h"

#include "IO.h"

#define TIMER1_NORMAL_MODE		0x00U
#define TIMER1_OVF_INT_MODE		0x01U

volatile uint8_t test;
volatile uint8_t test3;

void Timer1_Init(void)
{
	TCCR1A = TIMER1_NORMAL_MODE;
	TCCR1B = TIMER1_USED_PRESCALER;
	TIMSK1 = TIMER1_OVF_INT_MODE;
}

void Timer1_SetTime(void)
{
	TCNT1 = TIMER1_PERIOD;
}

ISR(TIMER1_OVF_vect)
{
	IO_SetPin(PORTB, TEST_LED_INDEX, ~IO_GetPin(PORTB, TEST_LED_INDEX));
	Timer1_SetTime();
}
