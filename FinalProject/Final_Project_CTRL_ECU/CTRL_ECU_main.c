/*
 ============================================================================
 Name        : CTRL_ECU_main.c
 Author      : Mostafa Medhat
 Description : Door Locking System CTRL ECU main file
 ============================================================================
 */

#include "CTRL_application.h"
#include "uart.h"
#include <util/delay.h>
#include "avr/io.h"



int main (void)
{
	uint8 no_of_try =0;
	uint8 state=0;
	uint8 option=0;
	uint8 recievedPassword[PASSWORD_LENGTH];
	uint8 enteredPassword[PASSWORD_LENGTH];

	SREG|=(1<<7); 			//Enable I-Bit
	MODULES_init();			//Modules Initialization
	while (UART_recieveByte() != READY);
	UART_sendByte(READY);

	/*
	 *  Setting Password for the first time use :
	 * 1- Receiving password from HMI MCU
	 * 2- Saving password in the EEPROM Module
	 */
	UART_sendByte(READY);
	recievePassword_from_HMIECU(recievedPassword);
	savePassword_in_EEROM(recievedPassword);
	while(1)
	{
		/* Receive Option from User through the HMI MCU */
		option=UART_recieveByte();

		/* If the user entered '+' Open Door option*/
		if(option==Open_Door_Option)
		{
			/*
			 * Receive entered password by user from HMI MCU
			 * then retrieve application password from the EEPROM
			 * then compare between the entered password by user and the application password
			 */
			recievePassword_from_HMIECU(enteredPassword);
			retrievePassword_from_EEROM();
			state=passwordEntering_Matching(App_Password,enteredPassword);

			if(state==Passwords_Match)
			{
				/*
				 * In case of passwords match:
				 * send to HMI MCU Opening door action message to perform open door mission on LCD
				 * and call openingDoor_and_closingDoor() which performs:
				 * Opening door by rotating DcMotor CW for 15sec,
				 * holding it for 3sec
				 * and closing door by rotating motor A_CW for 15sec.
				 */
				while (UART_recieveByte() != READY);
				UART_sendByte(Opening_Door_Action);
				no_of_try=0;
				openingDoor_and_closingDoor();
			}
			else if (state==Passwords_NotMatch)
			{
				/*
				 * In case of passwords don't match:
				 * check if the number of tries reaches the Maximum number of tries or not:
				 */
				no_of_try++;

				/*
				 * If it reaches:
				 * 	- Send Danger message to HMI MCU to operate the "Danger Mission"
				 * 	- Call Danger_detected function to turn on the buzzer and LED
				 */
				if(no_of_try>=MAX_TRY)
				{
					while (UART_recieveByte() != READY);
					UART_sendByte(Danger);
					Danger_detected();
				}
				/*
				 * If not:
				 * 	- Send Password_NotMatch message to HMI MCU to operate the "Mismatch Password mission"
				 */
				else
				{
					while (UART_recieveByte() != READY);
					UART_sendByte(Passwords_NotMatch);
				}

			}
		}
		/* If the user entered '-' Change Password Option */
		else if (option==Change_Password_Option)
		{
		/*
		 * Receive entered password by user from HMI MCU
		 * then retrieve application password from the EEPROM
		 * then compare between the entered password by user and the application password
		 */
			recievePassword_from_HMIECU(enteredPassword);
			retrievePassword_from_EEROM();
			state = passwordEntering_Matching(App_Password, enteredPassword);

			if (state == Passwords_Match)
			{
			/*
			 * In case of passwords match:
			 * send to HMI MCU change password action message to perform setPassword mission on LCD
			 * and call recievePassword_from_HMIECU() which receives entered password by user from HMI MCU
			 * and call savePassword_in_EEROM() which saves password in the EEPROM Module
			 */
				while (UART_recieveByte() != READY);
				UART_sendByte(Changing_Password_Action);
				no_of_try = 0;
				UART_sendByte(READY);
				recievePassword_from_HMIECU(recievedPassword);
				savePassword_in_EEROM(recievedPassword);
			}
			else if (state == Passwords_NotMatch)
			{
			/*
			 * In case of passwords don't match:
			 * check if the number of tries reaches the Maximum number of tries or not:
			 */
				no_of_try++;
				if (no_of_try >= MAX_TRY)
				{
				/*
				 * If it reaches:
				 * 	- Send Danger message to HMI MCU to operate the "Danger Mission"
				 * 	- Call Danger_detected function to turn on the buzzer and LED
				 */
					while (UART_recieveByte() != READY);
					UART_sendByte(Danger);
					Danger_detected();
				}
				else
				{
				/*
				 * If not:
				 * 	- Send Password_NotMatch message to HMI MCU to operate the "Mismatch Password mission"
				 */
					while (UART_recieveByte() != READY);
					UART_sendByte(Passwords_NotMatch);
				}
			}
		}
	}
}
