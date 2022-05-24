/*
 ======================================================================================
 Name        : dc_motor.h
 Author      : Mostafa Medhat
 Description : DC Motor Module Driver Header File
 ======================================================================================
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"
#include "gpio.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_PORT_ID 		PORTC_ID
#define	DC_MOTOR_IN1_PIN_ID 	PIN6_ID
#define	DC_MOTOR_IN2_PIN_ID 	PIN7_ID


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	STOP, CW , A_CW
}DcMotor_State;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description:
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 */
void DcMotor_Init(void);

/* Description:
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state);



#endif /* DC_MOTOR_H_ */
