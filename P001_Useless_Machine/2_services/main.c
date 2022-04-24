/** \brief File containing entry point for the program. 
 *        Initialize and starts components. Then starts OS 
 */

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/
#include <avr/interrupt.h>
#include "standard_types.h"
#include "IO.h"
#include "mcu.h"
#include "timer.h"
#include "os.h"
#include "led.h"

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Types defininition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Local functions prototypes
\**--------------------------------------------------------------------*/
static void Main_Initialize(void);
static void Main_Start(void);

/**--------------------------------------------------------------------*\
 * Objects definition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Functions defininition
\**--------------------------------------------------------------------*/

/** \brief Function for initializing components
 *  \returns None
 */
static void Main_Initialize(void)
{
   Mcu_ClockInit();
   OS_Init();
   Timer1_Init();
}

/** \brief Function for starting components
 *  \returns None
 */
static void Main_Start(void)
{
   /* Start Components */
   Led_Start();
   Uln2003_Start();
   App_Start();

   /* Start OS timer */
	Timer1_SetTime();
}

/** \brief Main function of the program. Should never exit
 *  \returns None
 */
int main (void)
{
   Main_Initialize();
	
	Main_Start();
	
	OS_EnableInterrupts();
	
	while(TRUE)
	{		
		OS_Run();
	}
}

