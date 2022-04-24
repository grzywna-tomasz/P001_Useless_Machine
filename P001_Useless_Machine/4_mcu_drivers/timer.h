#ifndef TIMER_H_
#define TIMER_H_

/** \brief Configuration header file for application
 */

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/
#include "timer_cfg.h"

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/
/* Use 1024 prescaler */
#if (TIMER1_1024_PRESCALER == 0x05U)
#define TIMER1_USED_PRESCALER          TIMER1_1024_PRESCALER
#define TIMER1_USED_PRESCALER_VALUE    1024U
#else
#error "add proper timer configuration"
#endif

#define TIMER1_NO_TICKS_IN_1S (F_CPU / TIMER1_USED_PRESCALER_VALUE)
#define TIMER1_1MS            (uint16_t)(UINT16_MAX - (TIMER1_NO_TICKS_IN_1S) / 1000)
#define TIMER1_100MS          (uint16_t)(UINT16_MAX - (TIMER1_NO_TICKS_IN_1S) / 10)
#define TIMER1_1S             (uint16_t)(UINT16_MAX - TIMER1_NO_TICKS_IN_1S)

/**--------------------------------------------------------------------*\
 * Types defininition
\**--------------------------------------------------------------------*/
void Timer1_SetTime(void);
void Timer1_Init(void);

/**--------------------------------------------------------------------*\
 * Exported functions prototypes
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Objects definition
\**--------------------------------------------------------------------*/

#endif /* TIMER_H_ */
