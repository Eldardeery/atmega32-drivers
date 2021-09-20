/*
 * gpio.c
 *
 * Created: 18-Feb-19 9:10:52 PM
 *  Author: dardeery
 */ 
#include "gpio.h"
void SET_PORT_DIRECTION(PORT_BASE port ,DIRECTION state)
{
	if (state ==OUT)
	{
		*(volatile uint8*)(port+1) =0xff;
	}
	else if (state ==IN)
	{
		*(volatile uint8*)(port+1) =0x00;
	}	
}
void SET_PIN_DIRECTION (PORT_BASE port,uint8 pin_num, DIRECTION state)
{
	if (state ==OUT)
	{
		*(volatile uint8*)(port+1) |=(1<<pin_num);
	}
	else if (state ==IN)
	{
		*(volatile uint8*)(port+1) &=(~(1<<pin_num));
	}
	
}
void WRITE_PORT_VAL    (PORT_BASE port ,uint8 val)
{
	*(volatile uint8*)(port+2) =val;
}
void WRITE_PIN_HIGH    (PORT_BASE port ,uint8 pin_num)
{
	*(volatile uint8*)(port+2) |=(1<<pin_num);
}
void WRITE_PIN_LOW     (PORT_BASE port ,uint8 pin_num)
{
	*(volatile uint8*)(port+2) &=(~(1<<pin_num));
}
uint8 READ_PORT        (PORT_BASE port)
{
	uint8 x=0xff;
	return (x & *(volatile uint8*)port );
}
uint8 READ_PIN         (PORT_BASE port ,uint8 pin_num)
{
	uint8 x =1;
	return (x & *(volatile uint8*)(port));
}