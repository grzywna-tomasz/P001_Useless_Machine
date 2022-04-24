#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/** \brief Configuration header file for port handling
 */

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/
#define PORTB_INIT_VALUE   0x00U
#define PORTC_INIT_VALUE   0x00U
#define PORTD_INIT_VALUE   0x00U
#define PORTE_INIT_VALUE   0x00U

/* 0 - input, 1 - OUTPUT */
#define DDRB_INIT_VALUE    0xFFU
#define DDRC_INIT_VALUE    0xFFU
#define DDRD_INIT_VALUE    0xFFU
#define DDRE_INIT_VALUE    0xFFU

/**--------------------------------------------------------------------*\
 * Types defininition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Exported functions prototypes
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Objects definition
\**--------------------------------------------------------------------*/

#endif /* PORT_CFG_H_ */