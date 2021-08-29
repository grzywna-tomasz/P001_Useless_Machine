/*
 * debug.h
 *
 * File containing debug  support
 *
 * Created: 16.05.2021 21:30:31
 *  Author: Grzywna
 */ 


#ifndef DEBUG_H_
#define DEBUG_H_

void Debug_Init(void);
void Debug_SerialPrintString(uint8_t *source_ptr, uint8_t length);
void Debug_SerialPrintChar(uint8_t send_byte);

#endif /* DEBUG_H_ */