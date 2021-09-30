/*
 * ATmega32_UAR.c
 *
 * Created: 9/27/2021 1:49:42 PM
 *  Author: dardeery
 */ 

#include "ATmega32-UAR.h"

void(*Rxc_callBack)(void);
void(*Txc_callBack)(void);
void(*UDRE_callBack)(void);

void UART_Iniit(UART_Configuration_Struct * uart_cnfig)
{
	unsigned char UCSRA_Temp = 0;
	unsigned char UCSRB_Temp = 0;
	unsigned char UCSRC_Temp = 0;
	
	switch (uart_cnfig->Mode)
	{
		case UART_Disable:
		break;
		case UART_Tx_Enable:
			UCSRB_Temp |=(1<<TXEN);
		break;
		case UART_Rx_Enable:
			UCSRB_Temp |=(1<<RXEN);
		break;
		case UART_Tx_Rx_Enable:
		UCSRB_Temp |=(1<<TXEN)|(1<<RXEN);
		break;
		default:
		break;
	}
	switch (uart_cnfig->Speed)
	{
		case NORMAL_Speed:
			UBRRL = ((F_CPU/(Boad_Rate*16UL))-0.5);
			
		break;
		case DOUBLE_Speed:
			UCSRA_Temp |=(1<<U2X);
			UBRRL = ((F_CPU/(Boad_Rate*8UL))-0.5);
			
		break;
		default:
		break;
	}
	switch(uart_cnfig->Interrupts)
	{
		case UART_Disable_Interrupt:
		break;
		case UART_Rxcomp_Enable:
			UCSRB_Temp |=(1<<RXCIE);
		break;
		case UART_Txcomp_Enable:
			UCSRB_Temp |=(1<<TXCIE);
		break;
		case UART_UDREmpty_Enable:
			UCSRB_Temp |=(1<<UDRIE);
		break;
		case UART_Txcomp_Rxcomp_Enable:
			UCSRB_Temp |=(1<<RXCIE)|(1<<TXCIE);
		break;
		case UART_Txcomp_UDREmpty_Enable :
			UCSRB_Temp |=(1<<TXCIE)|(1<<UDRIE);
		break;
		case UART_Rxcomp_UDREmpty_Enable:
			UCSRB_Temp |=(1<<RXCIE)|(1<<UDRIE);
		break;
		case UART_Txcomp_Rxcomp_UDREmpty_Enable:
			UCSRB_Temp |=(1<<TXCIE)|(1<<RXCIE)|(1<<UDRIE);
		break;
		default:
		break;
	}
	switch (uart_cnfig->Data_bits)
	{
		case UART_5bitdata:
		break;
		case UART_6bitdata:
			UCSRC_Temp |=(1<<UCSZ0);
		break;
		case UART_7bitdata:
			UCSRC_Temp |=(1<<UCSZ1);
		break;
		case UART_8bitdata:
			UCSRC_Temp |=(1<<UCSZ0)|(1<<UCSZ1);
		break;
		case UART_9bitdata:
			UCSRC_Temp |=(1<<UCSZ0)|(1<<UCSZ1);
			UCSRB_Temp |=(1<<UCSZ2);
		break;
		default:
		break;
	}
	switch (uart_cnfig->Parity)
	{
		case UART_Even_Parity:
			UCSRC_Temp |=(1<<UPM1);
		break;
		case UART_Odd_Parity:
			UCSRC_Temp |=(1<<UPM0)|(1<<UPM1);
		break;
	}
	switch (uart_cnfig->Stop_bits)
	{
		case UART_1stop_Bit:
		break;
		case UART_2stop_Bit:
		UCSRC_Temp |=(1<<USBS);
		break;
	}
	
	
	
	
	UCSRA = UCSRA_Temp;
	UCSRB = UCSRB_Temp;
	UCSRC = UCSRC_Temp;
}

void UART_Send_Byte_Blocking_Mode(unsigned char byte)
{
	/*check if tx reg is empty*/
	while(!(UCSRA &(1<<UDRE)));
	UDR = byte;
}

void UART_Send_Byte_NonBlocking_Mode(unsigned char byte)
{
	/*just if   for safety only*/
	if(UCSRA &(1<<UDRE) != 0)
	UDR = byte;
}

unsigned char UART_ReadByte_Blocking()
{
	/*check if rx reg recieve data */
	while((UCSRA &(1<<RXC)) == 0);
	if (UCSRA &((1<<PE) | (1<<FE) | (1<<DOR)))
	{
		// handle Errors   parity  frame overrun
	} 
	else
	{
		return UDR;
	}
		
}

unsigned char UART_ReadByte_NonBlocking()
{
	/*check if rx reg recieve data */
	if((UCSRA &(1<<RXC)) != 0)
	{
	if (UCSRA &((1<<PE) | (1<<FE) | (1<<DOR)))
	{
		// handle Errors   parity  frame overrun
	}
	else
	{
		return UDR;
	}
	}
}

void UART_SendString_BlockingMode(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		UART_Send_Byte_Blocking_Mode(str[j]);
		j++;
	}
}

void UART_Trigger_RxTx_Interrupt(UART_Configuration_Struct * object )
{
	switch (object->Interrupts)
	{
		case UART_Rxcomp_Enable:
		
		break;
		case UART_Txcomp_Enable:
		
		break;
		default:
		break;
	}
}



ISR(USART_RXC_vect)
{
	UART_ReadByte_NonBlocking();
}
ISR(USART_TXC_vect)
{
	UART_Send_Byte_NonBlocking_Mode();
}
ISR(USART_UDRE_vect)
{
	(*UDRE_callBack)();
}
