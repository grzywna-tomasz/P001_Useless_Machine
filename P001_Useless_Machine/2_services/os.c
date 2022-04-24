/** \brief Source file for OS implementation
 */

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/
#include "standard_types.h"
#include "os.h"

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/
#define OS_TASK_INACTIVE	FALSE
#define OS_TASK_ACTIVE		TRUE

/**--------------------------------------------------------------------*\
 * Types defininition
\**--------------------------------------------------------------------*/
typedef void(*OS_Task_Ptr_T)();

typedef struct 
{
	uint8_t state;
	uint16_t next_call; 
	uint8_t next_call_overflow;
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

/**--------------------------------------------------------------------*\
 * Local functions prototypes
\**--------------------------------------------------------------------*/
static void OS_ExecuteTask(void);
static void OS_SetNextCall(uint8_t task_id);

/**--------------------------------------------------------------------*\
 * Objects definition
\**--------------------------------------------------------------------*/
/* Reconfiguration of task config macro */
#ifdef OS_TASK_DEF
#undef OS_TASK_DEF
#endif
#define	OS_TASK_DEF(id, cfg_offset, cfg_period, cfg_task_ptr) {.offset = cfg_offset, .period = cfg_period, .task_pointer = cfg_task_ptr},

const static OS_Task_Cfg_T OS_Task_Cfg[OS_Task_No] = 
{
	OS_TASK_CFG_TABLE()
};

/* Reconfiguration of task config macro */
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
static uint8_t OS_OverflowOccured = FALSE;

/**--------------------------------------------------------------------*\
 * Functions defininition
\**--------------------------------------------------------------------*/
/** \brief Reset the microcontroller
 *  \returns None
 */
void OS_Reset(void)
{
	// TODO fill it with reset using watchdog.
	while(TRUE)
	{
		_NOP();
	}
}

/** \brief Function initialize OS
 *  \returns None
 */
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

/** \brief Function Setting next call counter
 *  \param[in] task_id - identifier of task to be modified
 *  \returns None
 */
static void OS_SetNextCall(uint8_t task_id)
{
	OS_Task_Desc[task_id].next_call = OS_Task_Desc[task_id].next_call + OS_Task_Cfg[task_id].period;
	
	if (OS_Task_Desc[task_id].next_call < OS_Task_Cfg[task_id].period)
	{
		OS_Task_Desc[task_id].next_call_overflow = TRUE;
	}
}

/** \brief Execute OS tasks
 *  \returns None
 */
static void OS_ExecuteTask(void)
{
   /* Handle overflow of the OS counter */
	OS_DisableInterrupts();
	if (TRUE == OS_OverflowOccured)
	{
		for (uint8_t task_id = 0; (uint8_t)OS_Task_No > task_id; task_id++)
		{
			OS_Task_Desc[task_id].next_call_overflow = FALSE;
		}
		OS_OverflowOccured = FALSE;
	}
   OS_EnableInterrupts();

   /* Handle task execution */
	for (uint8_t task_id = 0; (uint8_t)OS_Task_No > task_id; task_id++)
	{
		if (OS_TASK_ACTIVE == OS_Task_Desc[task_id].state)
		{
			/* Determine if task need to be executed. Greater or equal in case something took longer time 
         and OS "skipped" task. It will be executed one after another */
			if (OS_Tick_Counter >= OS_Task_Desc[task_id].next_call)
			{
				if (FALSE == OS_Task_Desc[task_id].next_call_overflow)
				{
					OS_Task_Cfg[task_id].task_pointer();
					OS_SetNextCall(task_id);
				}
			}
		}
	}
}

/** \brief Main function handling OS functionality
 *  \returns None
 */
void OS_Run(void)
{
	if (Initialized == OS_State)
	{
		OS_ExecuteTask();
	}
	else
	{
		OS_Reset();
	}
}

/** \brief Handler for OS timer interrupt
 *  \returns None
 */
void OS_Tick_Handler(void)
{
	if (Initialized == OS_State)
	{
		OS_Tick_Counter++;
		if (OS_Tick_Counter == 0)
		{
			OS_OverflowOccured = TRUE;
		}
	}
	else
	{
		OS_Reset();
	}
}

/** \brief Function for deactivating task
 *  \param[in] task_id - identifier of task to be stopped
 *  \returns None
 */
void OS_Deactivate_Task(OS_Task_Id_T task_id)
{
	OS_Task_Desc[task_id].state = OS_TASK_INACTIVE;
}

/** \brief Function for activating task
 *  \param[in] task_id - identifier of task to be activated
 *  \returns None
 */
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
