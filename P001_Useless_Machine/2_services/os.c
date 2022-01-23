/*
 * os.c
 *
 * Created: 19.09.2021 18:50:52
 *  Author: Grzywna
 */

#include "standard_types.h"
#include "os.h"

#define OS_TASK_INACTIVE	FALSE
#define OS_TASK_ACTIVE		TRUE

typedef void(*OS_Task_Ptr_T)();

typedef struct 
{
	uint8_t state;
	uint16_t next_call; 
} OS_Task_Desc_T;

typedef struct  
{
	uint16_t offset;
	uint16_t period;
	OS_Task_Ptr_T task_pointer;
} OS_Task_Cfg_T;

typedef enum
{
	Uninitialized,
	Initialized,	
} OS_State_T;

#ifdef OS_TASK_DEF
#undef OS_TASK_DEF
#endif
#define	OS_TASK_DEF(id, cfg_offset, cfg_period, cfg_task_ptr) {.offset = cfg_offset, .period = cfg_period, .task_pointer = cfg_task_ptr},

static const OS_Task_Cfg_T OS_Task_Cfg[OS_Task_No] = 
{
	OS_TASK_CFG_TABLE()
};

#ifdef OS_TASK_DEF
#undef OS_TASK_DEF
#endif
#define	OS_TASK_DEF(id, cfg_offset, cfg_period, cfg_task_ptr) {.state = OS_TASK_INACTIVE, .next_call = 0},

static OS_Task_Desc_T OS_Task_Desc[OS_Task_No] = 
{
	OS_TASK_CFG_TABLE()
};

static OS_State_T OS_State = Uninitialized;
static uint16_t OS_Tick_Counter = 0;

void OS_Reset(void)
{
	// TODO fill it with reset using watchdog.
	while(TRUE)
	{
		_NOP();
	}
}

void OS_Init(void)
{
	if (Uninitialized == OS_State)
	{
		for (uint8_t task_id = 0; (uint8_t)OS_Task_No > task_id; task_id++)
		{
			OS_Task_Desc[task_id].state = OS_TASK_INACTIVE;
			OS_Task_Desc[task_id].next_call = OS_Task_Cfg[task_id].offset;
		}
		OS_State = Initialized;
	}
	else
	{
		OS_Reset();
	}
}

void OS_Run(void)
{
	if (Initialized == OS_State)
	{
		for (uint8_t task_id = 0; (uint8_t)OS_Task_No > task_id; task_id++)
		{
			if (OS_TASK_ACTIVE == OS_Task_Desc[task_id].state)
			{
				/* Determine if task need to be executed. Greater or equal in case something took longer time and OS "skipped" task. It will be executed one after another */
				if (OS_Tick_Counter >= OS_Task_Desc[task_id].next_call)		
				{
					OS_Task_Cfg[task_id].task_pointer();
					OS_Task_Desc[task_id].next_call = OS_Task_Desc[task_id].next_call + OS_Task_Cfg[task_id].period;
				}
			}
		}
	}
	else
	{
		OS_Reset();
	}
}

void OS_Tick_Handler(void)
{
	if (Initialized == OS_State)
	{
		OS_Tick_Counter++;
	}
	else
	{
		OS_Reset();
	}
}

void OS_Deactivate_Task(OS_Task_Id_T task_id)
{
	OS_Task_Desc[task_id].state = OS_TASK_INACTIVE;
}

void OS_Activate_Task(OS_Task_Id_T task_id)
{
	if (Initialized == OS_State)
	{
		OS_Task_Desc[task_id].state = OS_TASK_ACTIVE;
	}
	else
	{
		OS_Reset();
	}
}
