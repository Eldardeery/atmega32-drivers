/*
 * UASRT.C
 *
 * Created: 01-Feb-19 9:34:24 PM
 *  Author: dardeery
 */
#include "UASRT.H"

#include <avr/io.h>
 
void UASRT_init()
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);/* Turn on transmission and reception */
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);/* Use 8-bit character sizes */
	UBRRL = MY_UBBR ;		/* Load lower 8-bits of the baud rate value */
	UBRRH = (MY_UBBR  >> 8);	/* Load upper 8-bits*/
}
void UASRT_send_char(uint8 data)
{
		while (! (UCSRA & (1<<UDRE)));	
		UDR = data ;
	}

void UASRT_send_string(uint8 *str)
{
	uint8 i=0;
	while (str[i]!=0)
	{
		
	UASRT_send_char(str[i]);
	i++;
	}
}
uint8 UASRT_recieve_char()
{
		while(!(UCSRA & (1<<7)));
		return UDR; 
}