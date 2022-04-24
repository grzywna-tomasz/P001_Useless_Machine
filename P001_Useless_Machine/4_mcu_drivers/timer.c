/** \brief Source file for timer implementation
 */

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/
#include <avr/interrupt.h>
#include "standard_types.h"
#include "mcu.h"
#include "timer.h"
#include "os.h"
#include "IO.h"

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/
#define TIMER1_NORMAL_MODE       0x00U
#define TIMER1_OVF_INT_MODE      0x01U

/**--------------------------------------------------------------------*\
 * Types defininition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Local functions prototypes
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Objects definition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Functions defininition
\**--------------------------------------------------------------------*/
/** \brief Initialization of the timer1
 *  \returns None
 */
void Timer1_Init(void)
{
	TCCR1A = TIMER1_NORMAL_MODE;
	TCCR1B = TIMER1_USED_PRESCALER;
	TIMSK1 = TIMER1_OVF_INT_MODE;
}

/** \brief Set timer1 counting time
 *  \returns None
 */
void Timer1_SetTime(void)
{
	TCNT1 = TIMER1_PERIOD;
}

/** \brief Timer1 overflow interrupt
 *  \returns None
 */
ISR(TIMER1_OVF_vect)
{
	OS_Tick_Handler();
	Timer1_SetTime();
}
