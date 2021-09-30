/*
 * ATmega32_UAR.h
 *
 * Created: 9/27/2021 1:50:57 PM
 *  Author: dardeery
 */ 


#ifndef ATMEGA32-UAR_H_
#define ATMEGA32-UAR_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>


#define Boad_Rate  (9600)
#define NULL_Ptr    ((void*)0x00) 
typedef enum
{
	UART_Disable,
	UART_Tx_Enable,
	UART_Rx_Enable,
	UART_Tx_Rx_Enable,
}UART_Mode;


typedef enum
{
	NORMAL_Speed,
	DOUBLE_Speed,	
}UART_Speed;


typedef enum
{
	UART_Disable_Interrupt,
	UART_Rxcomp_Enable,	
	UART_Txcomp_Enable,	
	UART_UDREmpty_Enable,
	UART_Txcomp_Rxcomp_Enable,	
	UART_Txcomp_UDREmpty_Enable,
	UART_Rxcomp_UDREmpty_Enable,
	UART_Txcomp_Rxcomp_UDREmpty_Enable,
}UART_Interrupts;

typedef enum 
{
	UART_5bitdata,
	UART_6bitdata,
	UART_7bitdata,
	UART_8bitdata,
	UART_9bitdata,
}UART_Data_Bits_Num;

typedef enum
{
	UART_No_Parity,
	UART_Even_Parity,
	UART_Odd_Parity,
	
}UART_Parity;
typedef enum
{
	UART_1stop_Bit,
	UART_2stop_Bit,
}UART_Stop_Bit;


typedef struct
{
	unsigned short      Boad_rate;
	UART_Mode           Mode;
	UART_Speed          Speed;
	UART_Interrupts     Interrupts;
	UART_Data_Bits_Num  Data_bits;
	UART_Parity         Parity;
	UART_Stop_Bit       Stop_bits;
}UART_Configuration_Struct;



void UART_Iniit(UART_Configuration_Struct * uart_cnfig);
void UART_Send_Byte_Blocking_Mode(unsigned char byte);
void UART_Send_Byte_NonBlocking_Mode(unsigned char byte);
unsigned char UART_ReadByte_Blocking();
unsigned char UART_ReadByte_NonBlocking();
void UART_SendString_BlockingMode(char *str);
void UART_Trigger_Interrupt(UART_Configuration_Struct * object ,void(*Callback_Fun)(void));


#endif /* ATMEGA32-UAR_H_ */
