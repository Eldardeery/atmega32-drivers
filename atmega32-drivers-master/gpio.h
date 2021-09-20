/*
 * gpio.h
 *
 * Created: 18-Feb-19 9:10:25 PM
 *  Author: dardeery
 */ 


#ifndef GPIO_H_
#define GPIO_H_
#include "common.h"

typedef enum
{
	
	PORTA_T =0x39,
	PORTB_T =0x36,
	PORTC_T =0x33,
	PORTD_T =0x30,
	
	}PORT_BASE;
 

void SET_PORT_DIRECTION(PORT_BASE port ,DIRECTION state);               //EX---> SET_PORT_DIRECTION(PORTA_T,OUT)
void SET_PIN_DIRECTION (PORT_BASE port,uint8 pin_num, DIRECTION state); //EX---> SET_PIN_DIRECTION(PORTB_T,0,OUT) 
void WRITE_PORT_VAL    (PORT_BASE port ,uint8 val);                     // EX---> WRITE_PORT_VAL(PORTA_T,0xf0)
void WRITE_PIN_HIGH    (PORT_BASE port ,uint8 pin_num);                // EX---> WRITE_PIN_HIGH(PORTB_T,0)
void WRITE_PIN_LOW     (PORT_BASE port ,uint8 pin_num);                // EX--->WRITE_PIN_LOW(PORTB_T,0)
uint8 READ_PORT        (PORT_BASE port);                               //EX--->READ_PORT(PORTC_T)
uint8 READ_PIN         (PORT_BASE port ,uint8 pin_num);                //EX---> READ_PIN(PORTA_T,0)

#endif /* GPIO_H_ */
