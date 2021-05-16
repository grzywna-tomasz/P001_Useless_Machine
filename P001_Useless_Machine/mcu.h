/*
 * mcu.h
 *
 * Created: 12.05.2021 23:37:10
 *  Author: Grzywna
 */ 

#ifndef MCU_H_
#define MCU_H_

#define F_DIVIDER_1			0x00U
#define F_DIVIDER_2			0x01U
#define F_DIVIDER_4			0x02U
#define F_DIVIDER_8			0x03U
#define F_DIVIDER_16		0x04U
#define F_DIVIDER_32		0x05U
#define F_DIVIDER_64		0x06U
#define F_DIVIDER_128		0x07U
#define F_DIVIDER_256		0x08U

#define F_CLOCK				16000000UL
#define F_DIVIDER			F_DIVIDER_1
#define F_CPU				(F_CLOCK/(F_DIVIDER + 1))
#include <util/delay.h>

void Mcu_ClockInit(void);

#endif /* MCU_H_ */
