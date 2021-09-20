/*
 * led.h
 *
 *  Created on: Sep 4, 2021
 *      Author: dardeery
 */

#ifndef LED_H_
#define LED_H_

#include"gpio.h"


/*EX
LED_CONFIG room11 ={PORTA_T,6};
int main(void)
{
	Init_Led(&room11);

	while (1)
	{
		Led_On(&room11);
		_delay_ms(1000);
		Led_Off(&room11);
		_delay_ms(1000);

	}
}
*/

typedef struct
{
	PORT_BASE port;
	uint8 led_num;
}LED_CONFIG;



void Init_Led(LED_CONFIG *object);
void Led_On (LED_CONFIG *object);
void Led_Off(LED_CONFIG *object);


#endif /* LED_H_ */
