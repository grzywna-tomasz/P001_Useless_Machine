#ifndef STANDARD_TYPES_H_
#define STANDARD_TYPES_H_

/** \brief Configuration header file for standard types include
 */

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/
/* Include of disable/enable interrupt */
#include <avr/interrupt.h>
/* Include of standard typedefs */
#include <avr/cpufunc.h>

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/
#define TRUE			(uint8_t)(1)
#define FALSE			(uint8_t)(0)

#define NULL_PTR		((void *)0)

/**--------------------------------------------------------------------*\
 * Types defininition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Exported functions prototypes
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Objects definition
\**--------------------------------------------------------------------*/

#endif /* STANDARD_TYPES_H_ */