/** \brief Source file for port handling
 */

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/
#include "standard_types.h"
#include "port.h"
#include "port_cfg.h"
#include <avr/io.h>

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/

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
/** \brief Function initializing port configuration
 *  \returns None
 */
void Port_Init(void)
{
   DDRB = DDRB_INIT_VALUE;
   DDRC = DDRC_INIT_VALUE;
   DDRD = DDRD_INIT_VALUE;
   DDRE = DDRE_INIT_VALUE;

   PORTB = PORTB_INIT_VALUE;
   PORTC = PORTC_INIT_VALUE;
   PORTD = PORTD_INIT_VALUE;
   PORTE = PORTE_INIT_VALUE;
}
