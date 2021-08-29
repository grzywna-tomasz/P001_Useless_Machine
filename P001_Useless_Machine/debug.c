/*
 * debug.c
 
 https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
 
 page 143
 *
 * Created: 16.05.2021 21:28:56
 *  Author: Grzywna
 */ 

#include "standard_types.h"
#include "mcu.h"
#include "debug.h"

#define F_BAUD		(uint16_t)9600

#define USART_ASYNC			(uint8_t)0x00
#define USART_SYNCH			(uint8_t)0x40
#define USART_MASTER_SPI	(uint8_t)0xC0

#define USART_PARITY_DISABLED	(uint8_t)0x00
#define USART_EVEN_PARITY		(uint8_t)0x20
#define USART_ODD_PARITY		(uint8_t)0x30

#define USART_ONE_STOP_BIT		(uint8_t)0x00
#define USART_TWO_STOP_BITS		(uint8_t)0x08

#define USART_CHAR_SIZE			8

#if (5 == USART_CHAR_SIZE)
#define USART_SIZE_C			(uint8_t)0x00
#define USART_SIZE_B			(uint8_t)0x00
#elif (6 == USART_CHAR_SIZE)
#define USART_SIZE_C			(uint8_t)0x02
#define USART_SIZE_B			(uint8_t)0x00
#elif (7 == USART_CHAR_SIZE)	
#define USART_SIZE_C			(uint8_t)0x04
#define USART_SIZE_B			(uint8_t)0x00
#elif (8 == USART_CHAR_SIZE)	
#define USART_SIZE_C			(uint8_t)0x06
#define USART_SIZE_B			(uint8_t)0x00
#elif (9 == USART_CHAR_SIZE)
#define USART_SIZE_C			(uint8_t)0x06
#define USART_SIZE_B			(uint8_t)0x01
#endif

 /* Clock parity output change / input sample in relation to clock */
#define CLOCK_RISING_FALLING	(uint8_t)0x00
#define CLOCK_FALLING_RISING	(uint8_t)0x01

#define USART_ENABLE_RX_INT		(uint8_t)0x80
#define USART_DISABLE_RX_INT	(uint8_t)0x00

#define USART_ENABLE_TX_INT		(uint8_t)0x40
#define USART_DISABLE_TX_INT	(uint8_t)0x00

#define USART_ENABLE_EMPTY_REG_INT		(uint8_t)0x20
#define USART_DISABLE_EMPTY_REG_INT		(uint8_t)0x00

#define USART_RECEIVER_ENABLE			(uint8_t)0x10
#define USART_RECEIVER_DISABLE			(uint8_t)0x00

#define USART_TRANSMITER_ENABLE			(uint8_t)0x08
#define USART_TRANSMITER_DISABLE		(uint8_t)0x00

#define USART_RECEIVE_8_BIT_SET			(uint8_t)0x02
#define USART_RECEIVE_8_BIT_CLEAR		(uint8_t)0x00

#define USART_TRANSMIT_8_BIT_SET		(uint8_t)0x01
#define USART_TRANSMIT_8_BIT_CLEAR		(uint8_t)0x00

#define USART_UDREN_MASK				(uint8_t)0x20
#define USART_UCSRNA_BUFFER_EMPTY		(uint8_t)0x01


void Debug_Init(void)
{
	/* Setup baud rate (f * 16 = f_cpu/(UBRR0 + 1)) */
	UBRR0 = (uint16_t)(F_CPU / (16UL * F_BAUD)) - 1;
	UCSR0C = (uint8_t)(USART_ASYNC | USART_PARITY_DISABLED | USART_ONE_STOP_BIT | USART_SIZE_C | CLOCK_RISING_FALLING);
	UCSR0B = (uint8_t)(USART_DISABLE_RX_INT | USART_DISABLE_TX_INT | USART_DISABLE_EMPTY_REG_INT |
			 USART_RECEIVER_DISABLE | USART_TRANSMITER_ENABLE | USART_RECEIVE_8_BIT_CLEAR | USART_TRANSMIT_8_BIT_CLEAR);			 
}

void Debug_SerialPrintString(uint8_t *source_ptr, uint8_t length)
{
	for(uint8_t char_counter = 0; char_counter < length; char_counter++)
	{
		Debug_SerialPrintChar(source_ptr[char_counter]);
	}
	Debug_SerialPrintChar('\n');
}

void Debug_SerialPrintChar(uint8_t send_byte)
{	
	while((UCSR0A & USART_UDREN_MASK) != USART_UDREN_MASK);
	UDR0 = send_byte;
}