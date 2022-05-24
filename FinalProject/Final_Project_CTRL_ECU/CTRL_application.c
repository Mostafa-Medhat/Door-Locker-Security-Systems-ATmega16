 /******************************************************************************
 * File Name: CTRL_application.c
 * Description: Source file for the application functions
 * Author: Mostafa Medhat
 *******************************************************************************/

#include "timer.h"
#include "external_eeprom.h"
#include "twi.h"
#include "uart.h"
#include "dc_motor.h"
#include "buzzer.h"
#include "util/delay.h"
#include "CTRL_application.h"


uint32 g_ticks = 0;
uint8 App_Password[PASSWORD_LENGTH]; /*global variable to store Password*/


void MODULES_init (void)
{

	/* Uart Configuration & Initialization*/
	Uart_ConfigType Uart_Config = {9600,EIGHT_DATABITS,PARITY_DISABLED,ONE_STOPBIT};
	UART_init(&Uart_Config);


	/*
	 *  Timer0 Configuration & Initialization
	 */
	Timer0_ConfigType Timer0_Config = { COMPARE_MODE, F_CPU_1024, 0, 245 }; //for counting 0.25 second
	Timer0_init(&Timer0_Config);
	Timer0_SetCallBack(Timer0_Tick_Increment);

	TWI_ConfigType TWI_Config={ 0x02, TWI_Prescaler_1, 0x01};
	TWI_init(&TWI_Config);

	/* Buzzer Initialization*/
	BUZZER_init();

	/* DcMotor Initialization*/
	DcMotor_Init();

}

void Timer0_Tick_Increment(void)
{
	g_ticks++;
}



void recievePassword_from_HMIECU (uint8 *pass)
{
	for (uint8 i=0;i<PASSWORD_LENGTH;i++)
	{
		pass[i]=UART_recieveByte();
	}
}

void savePassword_in_EEROM(uint8 *pass){
	/*
	 * looping on every number in (array parameter)password and store this number in specific
	 * 		address in memory
	 */
	for(uint8 i=0;i<PASSWORD_LENGTH;i++){
		EEPROM_writeByte(PASSWORD_STORED_ADRESS+i, pass[i]);
		_delay_ms(50);
	}

}

void retrievePassword_from_EEROM(void){
	/*
	 * looping on every number in (array parameter)password and store this number in specific
	 * 		address in memory
	 */
	for(uint8 i=0;i<PASSWORD_LENGTH;i++){
		EEPROM_readByte(PASSWORD_STORED_ADRESS+i, App_Password+i);
		_delay_ms(50);
	}

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

void openingDoor_and_closingDoor(void)
{
	g_ticks = 0;
	DcMotor_Rotate(CW);
	/*
	 * wait until door next state
	 */
	while (g_ticks < DOOR_OPENNING_TIME);

	DcMotor_Rotate(STOP);

	while (g_ticks < DOOR_OPENNING_TIME + DOOR_LEFT_OPEN_TIME);

	DcMotor_Rotate(A_CW);

	while (g_ticks	< DOOR_OPENNING_TIME + DOOR_LEFT_OPEN_TIME + DOOR_CLOSING_TIME);

	DcMotor_Rotate(STOP);

}

void Danger_detected(void)
{
	g_ticks=0;
	BUZZER_ON();
	/*
	 * wait until finishing danger time
	 */
	while(g_ticks < DANGER_TIME);

	BUZZER_OFF();
}
