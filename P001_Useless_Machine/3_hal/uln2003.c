/** \brief Source file for ULN2003 driver functionality
 */

//todo fix port setting
//todo add speed support

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/
#include "IO.h"
#include "standard_types.h"
#include "uln2003.h"
#include "uln2003_cfg.h"
#include "os.h"

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Types defininition
\**--------------------------------------------------------------------*/
typedef enum
{
	ULN2003_ARM_MOTOR,
	ULN2003_MOTRO_NO,
	ULN2003_MOTOR_ZERO_ID = 0,
} Uln2003_MotorId_T;

typedef struct  
{
	Uln2003_State_T state;
	uint8_t *port;
	int16_t current_position;
	int16_t desired_position;
	uint8_t current_enabled_pin;
} Uln2003_Desc_T;

/**--------------------------------------------------------------------*\
 * Local functions prototypes
\**--------------------------------------------------------------------*/
static void Uln2003_Step(uint8_t motor_id);
static void Uln2003_StepRight(uint8_t motor_id);
static void Uln2003_StepLeft(uint8_t motor_id);

/**--------------------------------------------------------------------*\
 * Objects definition
\**--------------------------------------------------------------------*/
static Uln2003_Desc_T Uln2003_Desc[ULN2003_MOTRO_NO];
//static Uln2003_Desc_T Uln2003_Desc[ULN2003_MOTRO_NO] = 
//{
	//{
		//.state = ULN2003_IDLE,
		//.port = &PORTC,
		//.current_position = 0,
		//.desired_position = 0,
		//.current_enabled_pin = 0,
	//}
//};

/**--------------------------------------------------------------------*\
 * Functions defininition
\**--------------------------------------------------------------------*/
/** \brief Function starting ULN2003 driver
 *  \returns None
 */
void Uln2003_Start(void)
{
   OS_Activate_Task(OS_TASK_ULN2003);
}

/** \brief Main task for ULN2003 driver handling
 *  \returns None
 */
void Uln2003_Task(void)
{
	for (uint8_t motor_id = ULN2003_MOTOR_ZERO_ID; ULN2003_MOTRO_NO > motor_id; motor_id++)
	{
		switch (Uln2003_Desc[motor_id].state)
		{
			case ULN2003_IDLE:
			{
				if (Uln2003_Desc[motor_id].current_position != Uln2003_Desc[motor_id].desired_position)
				{
					Uln2003_Desc[motor_id].state = ULN2003_STEP;
				}
				break;
			}
			case ULN2003_STEP:
			{
				Uln2003_Step(motor_id);
				if (Uln2003_Desc[motor_id].current_position == Uln2003_Desc[motor_id].desired_position)
				{
					Uln2003_Desc[motor_id].state = ULN2003_IDLE;
					ULN2003_COMPLETED_CALLBACK();
				}
				break;
			}
			default:
			{
				/* Do nothing */
				break;
			}
		}
	}
}

/** \brief Function returning specific motor state
 *  \param[in] motor_id - id of requested motor
 *  \returns Uln2003_State_T - state of current motor
 */
Uln2003_State_T Uln2003_GetState(uint8_t motor_id)
{
	return Uln2003_Desc[motor_id].state;
}

/** \brief Function for setting desired motor position
 *  \param[in] motor_id - id of requested motor
 *  \param[in] position - desired position to be set
 *  \param[in] speed - speed to be used for transition
 *  \returns None
 */
void uln2003_SetDesiredPosition(uint8_t motor_id, int16_t position, uint8_t speed)
{
	Uln2003_Desc[motor_id].desired_position = position;
}

/** \brief Function executing stepping functionality
 *  \param[in] motor_id - id of requested motor
 *  \returns None
 */
static void Uln2003_Step(uint8_t motor_id)
{
	Uln2003_Desc_T *desc = &Uln2003_Desc[motor_id];
		
	//IO_SetPin(*desc.port, desc.current_enabled_pin, FALSE);
	IO_SetPin(PORTC, desc->current_enabled_pin, FALSE);
	
	if (desc->current_position > desc->desired_position)
	{
		Uln2003_StepLeft(motor_id);
	}
	else if (desc->current_position < desc->desired_position)
	{
		Uln2003_StepRight(motor_id);
	}
	else
	{
		/* Do nothing */
	}	
	
	//IO_SetPin(*desc.port, desc.current_enabled_pin, TRUE);
	IO_SetPin(PORTC, desc->current_enabled_pin, TRUE);
}

/** \brief Function executing one step left
 *  \param[in] motor_id - id of requested motor
 *  \returns None
 */
static void Uln2003_StepLeft(uint8_t motor_id)
{
	Uln2003_Desc_T *desc = &Uln2003_Desc[motor_id];

	desc->current_enabled_pin--;
	desc->current_enabled_pin %= 4;
	desc->current_position--;
}

/** \brief Function executing one step right
 *  \param[in] motor_id - id of requested motor
 *  \returns None
 */
static void Uln2003_StepRight(uint8_t motor_id)
{
	Uln2003_Desc_T *desc = &Uln2003_Desc[motor_id];
	
	desc->current_enabled_pin++;
	desc->current_enabled_pin %= 4;
	desc->current_position++;
}