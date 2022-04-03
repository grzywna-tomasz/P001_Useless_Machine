/*
 * app_cfg.c
 *
 * Created: 27.02.2022 19:46:20
 *  Author: Grzywna
 */ 

#include "app_cfg.h"


const App_Movement_T App_Movement[255] = 
{
	{
		.desired_position = 50,
		.delay = 50,
		.next_step = 1,
		.speed = 2,
	},
	{
		.desired_position = -50,
		.delay = 50,
		.next_step = APP_END_STEP,
		.speed = 2,
	},
} ;