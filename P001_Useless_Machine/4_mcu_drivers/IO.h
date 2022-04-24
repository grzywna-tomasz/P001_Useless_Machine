#ifndef IO_H_
#define IO_H_

/** \brief Header file for DIO pin handling
 */

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/
#include <avr/io.h>

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/
#define TEST_LED_INDEX	(uint8_t)(5)

/* Macro used for setting pin value */
#define IO_SetPin(port, pin, state)    \
	if (FALSE == (0x01 & state))        \
	{                                   \
		(port) &= ~(1 << (pin));         \
	}                                   \
	else                                \
	{                                   \
		(port) |= (1 << (pin));          \
	}                                   \
/* IO_SetPin */

/* Macro used for getting pin value */
#define IO_GetPin(port, pin)           (((port) >> (pin)) & 0x01)
/* IO_GetPin */

/* Macro used for setting port value */
#define IO_SetPort(port, value)        \
	(port) = (value);                   \
/* IO_SetPort */

/* Macro used for getting port value */
#define IO_GetPort(port)               (port)
/* IO_GetPort */

/**--------------------------------------------------------------------*\
 * Types defininition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Exported functions prototypes
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Objects definition
\**--------------------------------------------------------------------*/					

#endif /* IO_H_ */