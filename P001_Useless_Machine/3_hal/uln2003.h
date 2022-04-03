/*
 * uln2003.h
 *
 * Created: 23.01.2022 18:49:51
 *  Author: Grzywna
 */ 


#ifndef ULN2003_H_
#define ULN2003_H_

typedef enum
{
	ULN2003_IDLE,
	ULN2003_STEP,
} Uln2003_State_T;

void Uln2003_Task(void);
Uln2003_State_T Uln2003_GetState(uint8_t motor_id);
void uln2003_SetDesiredPosition(uint8_t motor_id, int16_t position, uint8_t speed);

#endif /* ULN2003_H_ */