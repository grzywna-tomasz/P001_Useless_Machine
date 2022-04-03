/*
 * app_cfg.h
 *
 * Created: 27.02.2022 19:48:36
 *  Author: Grzywna
 */ 


#ifndef APP_CFG_H_
#define APP_CFG_H_

#include "standard_types.h"

#define APP_END_STEP		0xFFU
#define HALL_SET_DESIRED_POSITION(desired_position, speed)	uln2003_SetDesiredPosition(0, (desired_position), (speed));

typedef struct  
{
	uint8_t speed;
	uint8_t delay;		/* Delay between actual step and next step */
	uint8_t next_step;
	int16_t desired_position;
} App_Movement_T;

extern const App_Movement_T App_Movement[255];

#endif /* APP_CFG_H_ */