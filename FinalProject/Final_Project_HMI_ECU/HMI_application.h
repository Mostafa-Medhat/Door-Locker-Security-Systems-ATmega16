 /******************************************************************************
 * File Name: application.h
 * Description: Header file for the application functions
 * Author: Mostafa Medhat
 *******************************************************************************/

#ifndef HMI_APPLICATION_H_
#define HMI_APPLICATION_H_


#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* TIMING SPECS */
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





/*******************************************************************************
 *                              Global Variables                                *
 *******************************************************************************/
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
 * Function responsible for Setting Password in case of :
 * 1- First time to start the program
 * 2- Change password option
 */
void setPassword(uint8 *pass);


/*
 * Description:
 * Function responsible for getting password from user by using Keypads module.
 */
void getPassword_from_user(uint8 *pass);

/*
 * Description:
 * Function responsible for sending password to the Control MCU to save it in the EEPROM Module
 */
void sendPassword_to_ctrlECU (uint8 *pass);

/*
 * Description:
 * Function responsible for showing the Main Menu/options, so that the user can operate one of them
 * + : Open the Door
 * - : Change the Password
 */
void MainMenu(void);

/*
 * Description:
 * Function responsible for comparing two passwords in two cases:
 * 1- Entered Password & Confirmed Password
 * 2- Entered Password & Stored Password
 */
uint8 passwordEntering_Matching(uint8 *pass1,uint8 *pass2);

/*
 * Description:
 * Function responsible for showing Opening door messages on LCD module.
 */
void OpeningDoor_LCD(void);

/*
 * Description:
 * Function responsible for showing Danger messages on LCD module.
 */
void Danger_LCD(void);

/*
 * Description:
 * Function responsible for showing Wrong/Mis-matched passwords on LCD Module.
 */
void MisMatch_Password(void);



#endif /* HMI_APPLICATION_H_ */
