/*
 ======================================================================================
 Name        : dc_motor.c
 Author      : Mostafa Medhat
 Description : DC Motor Module Driver Source File
 ======================================================================================
 */

#include "dc_motor.h"
#include "gpio.h"

void DcMotor_Init(void)
{
	/* Setup Motor pins as Output pins and
	 * write a Logic Low on them to stop at the DC-Motor at the beginning
	 */
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, PIN_OUTPUT);

	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state)
{
	/* The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
	 * Send the required duty cycle to the PWM driver based on the required speed value.
	 */
	switch(state)
	{
	case STOP:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;
	case CW:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;
	case A_CW:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_HIGH);
		break;
	}
}


