 /******************************************************************************
 * Module: Timer
 * File Name: timer.c
 * Description: Source file for the Timer AVR driver
 * Author: Mostafa Medhat
 *******************************************************************************/

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>


/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
		/* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{

		(*g_callBackPtr)();
		/* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
void Timer0_init(const Timer0_ConfigType *Config_ptr)
{
	TCNT0 = Config_ptr->initialValue;
	if (Config_ptr->mode == NORMAL_MODE)
	{
		TCCR0|=(1<<FOC0);
		TIMSK|=(1<<TOIE0);
		TCCR0 = (TCCR0 & 0xF8) | (Config_ptr->clock);
	}
	else if (Config_ptr->mode == COMPARE_MODE)
	{
		TCCR0 |= (1 << FOC0);
		TCCR0 |= (1 << WGM01);
		TIMSK |= (1 << OCIE0);
		OCR0 = Config_ptr->compareValue;
		TCCR0 = (TCCR0 & 0xF8) | (Config_ptr->clock);
	}
}

void Timer0_SetCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr = a_ptr;
}

void Timer0_DeInit(void)
{
	TCCR0=0;
	TIMSK=0;
	g_callBackPtr=NULL_PTR;
}
