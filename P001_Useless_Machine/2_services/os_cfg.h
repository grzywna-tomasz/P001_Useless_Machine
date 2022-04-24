#ifndef OS_CFG_H_
#define OS_CFG_H_

/** \brief Configuration header file for OS
 */

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/
#include "standard_types.h"

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/
/* Task configuration table */
#define OS_TASK_CFG_TABLE()	\
	OS_TASK_DEF(OS_TASK_LED_TOGGLE, 0, 500, &Led_Toggle)	\
	OS_TASK_DEF(OS_TASK_ULN2003, 0, 3, &Uln2003_Task)	\
	OS_TASK_DEF(OS_TASK_APP, 0, 10, &App_Task)	\
/* OS_TASK_CFG_TABLE */

#define OS_EnableInterrupts()    sei();
#define OS_DisableInterrupts()   cli();

/**--------------------------------------------------------------------*\
 * Types defininition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Exported functions prototypes
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Objects definition
\**--------------------------------------------------------------------*/

#endif /* OS_CFG_H_ */