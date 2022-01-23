/*
 * os.h
 *
 * Created: 19.09.2021 18:51:10
 *  Author: Grzywna
 */ 

#ifndef OS_H_
#define OS_H_

#include "led.h"
#include "uln2003.h"

#define OS_TASK_CFG_TABLE()	\
	OS_TASK_DEF(OS_TASK_LED_TOGGLE, 0, 500, &LedToggle)	\
	OS_TASK_DEF(OS_TASK_STEP_RIGHT, 0, 1, &Uln2003_StepRight)	\
/* OS_TASK_CFG_TABLE */

#ifdef OS_TASK_DEF
#undef OS_TASK_DEF
#endif
#define OS_TASK_DEF(id, cfg_offset, cfg_period, cfg_task_ptr)	id,

typedef enum
{
	OS_TASK_CFG_TABLE()
	OS_Task_No
} OS_Task_Id_T;

void OS_Reset(void);
void OS_Init(void);
void OS_Run(void);
void OS_Tick_Handler(void);
void OS_Deactivate_Task(OS_Task_Id_T task_id);
void OS_Activate_Task(OS_Task_Id_T task_id);

#endif /* OS_H_ */
