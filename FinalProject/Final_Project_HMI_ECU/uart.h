 /******************************************************************************
 * Module: UART
 * File Name: uart.c
 * Description: Header file for the UART AVR driver
 * Author: Mostafa Medhat
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	RATE_10 	= 10,
	RATE_300 	= 300,
	RATE_600 	= 600,
	RATE_1200 	= 1200,
	RATE_2400 	= 2400,
	RATE_4800 	= 4800,
	RATE_9600 	= 9600,
	RATE_14400 	= 14400,
	RATE_19200 	= 19200,
	RATE_38400 	= 38400,
	RATE_57600 	= 57600,
	RATE_115200 = 115200,
	RATE_128000 = 128000,
	RATE_256000 = 256000
}Uart_Baudrate;

typedef enum
{
	PARITY_DISABLED=0,EVEN_PARITY=2,ODD_PARITY=3
}Uart_Parity;

typedef enum
{
	ONE_STOPBIT=0,TWO_STOPBIT=1
}Uart_StopBits;

typedef enum
{
	FIVE_DATABITS=0,SIX_DATABITS=1,SEVEN_DATABITS=2,EIGHT_DATABITS=3,NINE_DATABITS=7
}Uart_DataBits;

typedef struct
{
	Uart_Baudrate baudrate;
	Uart_DataBits data;
	Uart_Parity parity;
	Uart_StopBits stopBit;
}Uart_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const Uart_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
