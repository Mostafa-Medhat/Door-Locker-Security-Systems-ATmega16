 /******************************************************************************
 * Module: Timer
 * File Name: timer.c
 * Description: Source file for the Timer AVR driver
 * Author: Mostafa Medhat
 *******************************************************************************/



#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXTERNAL_CLOCK_FALLING_EDGE,EXTERNAL_CLOCK_RISING_EDGE
}Timer0_Clock;

typedef enum
{
	NORMAL_MODE, PHASE_PWM,COMPARE_MODE,FAST_PWM
}Timer0_Mode;

typedef struct
{
	Timer0_Mode mode;
	Timer0_Clock clock;
	uint8 initialValue;
	uint8 compareValue;
}Timer0_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Function responsible for initializing Timer0 Module.
 */
void Timer0_init(const Timer0_ConfigType *Config_ptr);

/*
 * Description:
 * Function responsible for setting the CallBack Function of Timer0
 */
void Timer0_setCallBack(void(*a_ptr)(void));

/*
 * Description:
 * Function responsible for turning off (De-initalizing) Timer0
 */
void Timer0_DeInit(void);



#endif /* TIMER_H_ */
