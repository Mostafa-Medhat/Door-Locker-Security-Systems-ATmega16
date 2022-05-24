 /******************************************************************************
 * File Name: CTRL_application.c
 * Description: Header file for the application functions
 * Author: Mostafa Medhat
 *******************************************************************************/

#ifndef CTRL_APPLICATION_H_
#define CTRL_APPLICATION_H_


#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*TIMING SPECS*/
#define DOOR_OPENNING_TIME	(60) //15sec
#define DOOR_CLOSING_TIME	(60) //15sec
#define DOOR_LEFT_OPEN_TIME	(12) //3sec
#define DANGER_TIME (240) //60sec

/* Shared/Common messages between MCU1 & MCU2 */
#define Open_Door_Option '+'
#define Change_Password_Option '-'
#define Opening_Door_Action 88
#define Changing_Password_Action 44
#define Danger 0x33


/* PASS SPECS */
#define PASSWORD_LENGTH 	 5
#define MAX_TRY            	 3
#define Passwords_Match		 1
#define Passwords_NotMatch	 0

/*UART SPECS*/
#define READY 0x10

/*EEPROM SPECS*/
#define PASSWORD_STORED_ADRESS 0x0311



/*******************************************************************************
 *                              Global Variables                                *
 *******************************************************************************/
extern uint8 App_Password[PASSWORD_LENGTH];
extern uint32 g_ticks;



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialization Modules :
 * UART, LCD, Timer
 */
void MODULES_init(void);

/*
 * Description:
 * CallBack Function of the Timer ISR
 */
void Timer0_Tick_Increment(void);

/*
 * Description:
 * Function responsible for receiving password from the HMI MCU.
 */
void recievePassword_from_HMIECU(uint8 *pass);

/*
 * Description:
 * Function responsible for saving password in the EEPROM Module.
 */
void savePassword_in_EEROM(uint8 *pass);

/*
 * Description:
 * Function responsible for retrieving password from the EEPROM Module.
 */
void retrievePassword_from_EEROM(void);

/*
 * Description:
 * Function responsible for comparing two passwords in two cases:
 * 1- Entered Password & Confirmed Password
 * 2- Entered Password & Stored Password
 */
uint8 passwordEntering_Matching(uint8 *pass1,uint8 *pass2);

/*
 * Description:
 * Function responsible for Opening door, holding it then closing it using DcMotor.
 */
void openingDoor_and_closingDoor(void);

/*
 * Description:
 * Function responsible for turn on buzzer and led as in danger cases
 * case: Entering passwords wrong three times or more.
 */
void Danger_detected(void);



#endif /* CTRL_APPLICATION_H_ */
