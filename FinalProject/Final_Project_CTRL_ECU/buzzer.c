 /******************************************************************************
 * Module: Timer
 * File Name: timer.c
 * Description: Source file for BUZZER Driver
 * Author: Mostafa Medhat
 *******************************************************************************/

#include "buzzer.h"

void BUZZER_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID,LOGIC_LOW );
}

void BUZZER_ON(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

void BUZZER_OFF(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID,LOGIC_LOW );
}
