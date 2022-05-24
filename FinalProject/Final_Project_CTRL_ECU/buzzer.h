 /******************************************************************************
 * Module: Timer
 * File Name: timer.c
 * Description: Header file for BUZZER Driver
 * Author: Mostafa Medhat
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "gpio.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID	PORTC_ID
#define BUZZER_PIN_ID	PIN5_ID


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void BUZZER_init(void);

void BUZZER_ON(void);

void BUZZER_OFF(void);


#endif /* BUZZER_H_ */
