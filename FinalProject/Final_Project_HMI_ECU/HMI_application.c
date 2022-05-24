 /******************************************************************************
 * File Name: HMI_application.c
 * Description: Source file for the application functions
 * Author: Mostafa Medhat
 *******************************************************************************/

#include "HMI_application.h"
#include "lcd.h"
#include "keypad.h"
#include "timer.h"
#include "uart.h"
#include "util/delay.h"

uint32 g_ticks = 0;

void Timer0_Tick_Increment(void)
{
	g_ticks++;
}

void MODULES_init (void)
{

	LCD_init();
	/* Uart Configuration & Initialization*/
	Uart_ConfigType Uart_Config = { 9600, EIGHT_DATABITS, PARITY_DISABLED,ONE_STOPBIT };
	UART_init(&Uart_Config);

	/*
	 *  Timer0 Configuration & Initialization
	 */
	Timer0_ConfigType Timer0_Config = { COMPARE_MODE, F_CPU_1024, 0, 245 }; //for counting 0.25 second
	Timer0_init(&Timer0_Config);
	Timer0_SetCallBack(Timer0_Tick_Increment);
}


void setPassword(uint8 *pass)
{
	/*
	 * 2 temporary arrays to use them to get password from the user
	 *  PasswordTemp1: Entering of password(first password)
	 *  PasswordTemp2: confirmation of password
	 */
	uint8 PasswordTemp1[PASSWORD_LENGTH];
	uint8 PasswordTemp2[PASSWORD_LENGTH];
	/*
	 * variable used to store the state of 2 passwords entered by the user
	 * it will be initialized as a Not Matching first
	 */
	uint8 Password_State = Passwords_NotMatch;

	/* exit from the while only if case of matching of 2 passwords */
	while(Password_State == Passwords_NotMatch){
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0,"Enter New Password");

			/* get 5 numbers first password from the user */
			getPassword_from_user(PasswordTemp1);

			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Confirm The Password");

			/* get 5 numbers confirm password from the user */
			getPassword_from_user(PasswordTemp2);

			/* Compare between the two passwords*/
			Password_State=passwordEntering_Matching(PasswordTemp1,PasswordTemp2);


			if(Password_State == Passwords_Match)
			{
				/*communications between the 2 ECUs(HMI and Control )to check the Readiness   */
				while (UART_recieveByte() != READY);
				/*
				 * send first password to Control-Ecu in preparation to compare it
				 *  with the confirmation password to check Matching
				 */
				sendPassword_to_ctrlECU(PasswordTemp1);

				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Passwords Match");
				LCD_displayStringRowColumn(1,0,"Password saved");
				_delay_ms(500);
			}
			else if(Password_State == Passwords_NotMatch){
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Passwords Mismatch");
				LCD_displayStringRowColumn(1,0,"Try Again");
				_delay_ms(500);
			}
		}

	LCD_clearScreen();
}

void getPassword_from_user(uint8 *pass)
{
	LCD_moveCursor(1, 0);
	/*variable used to get the keypad button pressed by user */
	uint8 key;

	for(uint8 i=0;i<PASSWORD_LENGTH;i++){
		key = KEYPAD_getPressedKey();
		/*password must be numbers only*/
		if (key >= 0 && key <= 9) {
			LCD_displayCharacter('*');
			pass[i]= key;
		}else{
			/*in case of pressing not a number button
			 * i will decrement the i counter to get 5 number password only
			 */
			i--;
		}
		/* Delay for 300ms between keypad presses */
		_delay_ms(300);
	}
	/*
	 * do not exit from the function without pressing a ENTER button
	 */
}


void sendPassword_to_ctrlECU (uint8 *pass)
{
	for (uint8 i=0;i<PASSWORD_LENGTH;i++){
			UART_sendByte(pass[i]);
		}
}


void MainMenu (void)
{
	LCD_clearScreen ();
	LCD_moveCursor(0, 0);
	LCD_displayString ("+: Open Door");
	LCD_moveCursor(1, 0);
	LCD_displayString ("-: Change Password");
}

uint8 passwordEntering_Matching(uint8 *pass1,uint8 *pass2)
{
	uint8 matchFlag=Passwords_NotMatch;
	for(uint8 i =0; i<PASSWORD_LENGTH; i++)
	{
		if (pass1[i]==pass2[i])
		{
			matchFlag=Passwords_Match;
		}
		else
		{
			matchFlag=Passwords_NotMatch;
			break;
		}
	}
	return matchFlag;
}

void OpeningDoor_LCD(void){

	/*
	 * make g_ticks zero to start calculation and comparison of time
	 */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Opening the Door...");
	g_ticks = 0;
	/*
	 * wait until door next state
	 */
	while (g_ticks < DOOR_OPENNING_TIME){};

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door is open");
	/*
	 * wait until door next state
	 */
	while (g_ticks < (DOOR_LEFT_OPEN_TIME+DOOR_OPENNING_TIME)){};

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Closing the Door...");
	/*
	 * wait until door next state
	 */
	while (g_ticks < (DOOR_CLOSING_TIME+DOOR_LEFT_OPEN_TIME + DOOR_OPENNING_TIME)){};

	//now door is closed
}

void MisMatch_Password(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Wrong Password !");
	_delay_ms(500);
}

void Danger_LCD(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 6, "DANGER !");
	LCD_displayStringRowColumn(1, 1, "Emsk Haraamyyyy !");
	/*
	 * wait until finishing danger time
	 */
	g_ticks = 0;
	while (g_ticks < DANGER_TIME){};
}


