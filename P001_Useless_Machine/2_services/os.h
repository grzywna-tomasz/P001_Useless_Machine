#ifndef OS_H_
#define OS_H_

/** \brief Configuration header file for OS
 */

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/
#include "os_internal.h"

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Types defininition
\**--------------------------------------------------------------------*/
/* Reconfiguration of task config macro */
#ifdef OS_TASK_DEF
#undef OS_TASK_DEF
#endif
#define OS_TASK_DEF(id, cfg_offset, cfg_period, cfg_task_ptr)	id,

typedef enum
{
	OS_TASK_CFG_TABLE()
	OS_Task_No
} OS_Task_Id_T;

/**--------------------------------------------------------------------*\
 * Exported functions prototypes
\**--------------------------------------------------------------------*/
void OS_Reset(void);
void OS_Init(void);
void OS_Run(void);
void OS_Tick_Handler(void);
void OS_Deactivate_Task(OS_Task_Id_T task_id);
void OS_Activate_Task(OS_Task_Id_T task_id);

/**--------------------------------------------------------------------*\
 * Objects definition
\**--------------------------------------------------------------------*/

#endif /* OS_H_ */
