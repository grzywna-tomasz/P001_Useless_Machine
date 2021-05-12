/*
 * IO.h
 *
 * Created: 12.05.2021 21:41:59
 *  Author: Grzywna
 */ 


#ifndef IO_H_
#define IO_H_

/* Macro used for setting pin value */
#define IO_SetPin(port, pin, state)			\
	if (FALSE == state)						\
	{										\
		(port) &= ~(1 << (pin));			\
	}										\
	else									\
	{										\
		(port) |= (1 << (pin));				\
	}										\
/* IO_SetPin */

/* Macro used for getting pin value */
#define IO_GetPin(port, pin)				((port) >> (pin))
/* IO_GetPin */

/* Macro used for setting port value */
#define IO_SetPort(port, value)				\
	(port) &= (value);						\
/* IO_SetPort */

/* Macro used for getting port value */
#define IO_GetPort(port)						(port)
/* IO_GetPort */
					

#endif /* IO_H_ */