/*
 * P001_Useless_Machine.c
 
 https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
 *
 * Created: 12.05.2021 20:49:36
 * Author : Grzywna
 */ 

#include "standard_types.h"
#include "IO.h"
#include "mcu.h"
#include "timer.h"
#include "os.h"

int main (void)
{
	Mcu_ClockInit();
	//Debug_Init();
	OS_Init();
	Timer1_Init();
	
	OS_Activate_Task(OS_TASK_LED_TOGGLE);
	OS_Activate_Task(OS_TASK_STEP_RIGHT);
	OS_Activate_Task(OS_TASK_APP);
	Timer1_SetTime();

	DDRB = 0b11111111;
	DDRC = 0b00001111;
		
	sei();
	
	while(TRUE)
	{		
		OS_Run();
	}
}

