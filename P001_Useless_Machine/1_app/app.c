
/** \brief Source file for application
 */

/**--------------------------------------------------------------------*\
 * Included headers
\**--------------------------------------------------------------------*/
#include "standard_types.h"
#include "uln2003.h"
#include "app.h"
#include "app_cfg.h"
#include "os.h"

/**--------------------------------------------------------------------*\
 * Macros defininition
\**--------------------------------------------------------------------*/

/**--------------------------------------------------------------------*\
 * Types defininition
\**--------------------------------------------------------------------*/
typedef enum
{
	APP_IDLE,
	APP_TRANSITION_STARTED,
	APP_TRANSITION_ENDED,
} App_Status_T;

typedef struct  
{
	App_Status_T status;
	uint8_t trigger;
	App_Movement_T const *step_data;
	uint8_t delay_counter;
} App_Control_T;

/**--------------------------------------------------------------------*\
 * Local functions prototypes
\**--------------------------------------------------------------------*/
static void App_AssignNextStep(uint8_t step);

/**--------------------------------------------------------------------*\
 * Objects definition
\**--------------------------------------------------------------------*/
static App_Control_T App_Control = 
{
	.status = APP_IDLE,
	.trigger = FALSE,
	.step_data = NULL_PTR,
	.delay_counter = 0U,
};

static uint16_t App_counter = 0;

/**--------------------------------------------------------------------*\
 * Functions defininition
\**--------------------------------------------------------------------*/
/** \brief Set next step to be executed
 *  \param[in] step - index of the step to be set
 *  \returns None
 */
static void App_AssignNextStep(uint8_t step)
{
	if (APP_END_STEP == step)
	{
		App_Control.status = APP_IDLE;
	}
	else
	{
		App_Control.step_data = &App_Movement[step];
		App_Control.delay_counter = App_Control.step_data->delay;
		HALL_SET_DESIRED_POSITION(App_Control.step_data->desired_position, App_Control.step_data->speed);
	}
}

/** \brief Starts the application component
 *  \returns None
 */
void App_Start(void)
{
   OS_Activate_Task(OS_TASK_APP);
}

/** \brief Application task called from OS
 *  \returns None
 */
void App_Task(void)
{
	if(App_counter == 500)
	{
		App_Control.trigger = TRUE;
		App_counter = 0;
	}
	else
	{
		App_counter++;
	}
	
	switch(App_Control.status)
	{
		case APP_IDLE:
		{
			if(TRUE == App_Control.trigger)
			{
				App_Control.trigger = FALSE;
				App_AssignNextStep(0U);
				App_Control.status = APP_TRANSITION_STARTED;
			}
			break;	
		}
		case APP_TRANSITION_STARTED:
		{
			/* Do nothing */
			break;
		}
		case APP_TRANSITION_ENDED:
		{
			if(0U < App_Control.delay_counter)
			{
				App_Control.delay_counter--;
			}
			else
			{
				App_AssignNextStep(App_Control.step_data->next_step);
			}
		}
	}
}

/** \brief Notification callback of finished step execution
 *  \returns None
 */
void App_TransitionFinished(void)
{
	if(APP_TRANSITION_STARTED == App_Control.status)
	{
		App_Control.status = APP_TRANSITION_ENDED;
	}
}