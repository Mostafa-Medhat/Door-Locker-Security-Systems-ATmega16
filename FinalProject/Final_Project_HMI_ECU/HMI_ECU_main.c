/*
 ============================================================================
 Name        : HMI_ECU_main.c
 Author      : Mostafa Medhat
 Description : Door Locking System HMI ECU main file
 ============================================================================
 */

#include "HMI_application.h"
#include "lcd.h"
#include "uart.h"
#include "keypad.h"
#include "avr/io.h"
#include <util/delay.h>


int main (void)
{
	uint8 Keypad_PressedKey=0;
	uint8 state=0;
	uint8 enteredPassword[PASSWORD_LENGTH];

	SREG|=(1<<7);				//Enable I-Bit
	MODULES_init();				//Modules Initialization

	/*
	 * Intro/Welcoming Messages
	 */
	LCD_moveCursor(0, 6);
	LCD_displayString("Welcome !");
	LCD_moveCursor(1, 6);
	LCD_displayString("MR. Admin");
	_delay_ms(1000);

	/* Setting Password for the first time use*/
	UART_sendByte(READY);
	while (UART_recieveByte() != READY);
	setPassword(enteredPassword);
	while(1)
	{
		/* Show the main menu on LCD Module so that the user can make his choice */
		MainMenu();
		Keypad_PressedKey = KEYPAD_getPressedKey();

		/* If the user enters '+' to open the door */
		if (Keypad_PressedKey == Open_Door_Option)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Enter The Password");

			/*
			 * get 5 numbers password from the user to check
			 * only accept numbers [0:9]
			 */
			getPassword_from_user(enteredPassword);



			/*
			 * send desired option which the user needed to execute
			 * in this case the option is Open_Door_Option
			 */
			UART_sendByte(Open_Door_Option);

			/*send password to Control ECU to check if the entered password is same as the real application
			 * 		password that stored in the  Control-Ecu in the memory (EEPROM)
			 */
			sendPassword_to_ctrlECU(enteredPassword);

			/*
			 * Receive from Control-Ecu if the password entered by the user is the same as real application password
			 * 		the received byte  may be 3 cases
			 */
			UART_sendByte(READY);
			state = UART_recieveByte();

			if (state == Opening_Door_Action) {
				/*
				 * in case of matching of 2 passwords
				 * start execution of opening and hold and closing Door mission
				 * LCD will display the state of the door in the Control-Ecu
				 */
				OpeningDoor_LCD();

			} else if (state == Passwords_NotMatch) {
				/*
				 * in case of mis-matching of 2 passwords for first and second try
				 * start execution of Mismatching Password Mission
				 * LCD will display " Wrong Password" so that the user knows that
				 * the entered password is not the same of application password
				 */
				MisMatch_Password();
			} else if (state == Danger) {
				/*
				 * in case of mis-matching of 2 passwords for third try
				 * start execution of Danger Mission
				 * LCD will display some string to show that someone try thieving
				 */
				Danger_LCD();
			}

		}
		/* if the user enters '-' to change password*/
		else if (Keypad_PressedKey == Change_Password_Option)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Enter The Password");

			/*
			 * get 5 numbers password from the user to check
			 * only accept numbers [0:9]
			 */
			getPassword_from_user(enteredPassword);


			/*
			 * send desired option which the user needed to execute
			 * in this case the option is Change_Password_Option
			 */
			UART_sendByte(Change_Password_Option);


			/* send password to Control ECU to check if the entered password is same as the real application
			 * password that stored in the  Control-Ecu in the memory (EEPROM)
			 */
			sendPassword_to_ctrlECU(enteredPassword);

			/*
			 * Receive from Control-Ecu if the password entered by the user is the same as real application password
			 * 		the received byte  may be 3 cases
			 */
			UART_sendByte(READY);
			state = UART_recieveByte();
			if (state == Changing_Password_Action)
			{
				/*
				 * in case of matching of 2 passwords
				 * start execution of Set Password mission to change application password
				 * and store it again in EEPROM in CONTROL ECU
				 * LCD will display the states of setting password mission
				 */
				setPassword(enteredPassword);
			}

			else if (state == Passwords_NotMatch)
			{
				/*
				 * in case of mis-matching of 2 passwords for first and second try
				 * start execution of Mismatching Password Mission
				 * LCD will display "Wrong Password" so that the user knows that
				 * the entered password is not the same of the application password
				 */
				MisMatch_Password();
			}
			else if (state == Danger)
			{
				/*
				 * in case of mis-matching of 2 passwords for third try
				 * start execution of Danger Mission
				 * LCD will display some string to show that someone try thieving
				 */
				Danger_LCD();
			}
		}
	}
}
