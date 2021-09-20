/*
 * led.c
 *
 *  Created on: Sep 4, 2021
 *      Author: dardeery
 */

#include"led.h"

void Init_Led(LED_CONFIG *object)
{
	SET_PIN_DIRECTION(object->port, object->led_num, OUT);
}
void Led_On (LED_CONFIG* object)
{
	WRITE_PIN_HIGH(object->port, object->led_num);

}

void Led_Off(LED_CONFIG* object)
{
	WRITE_PIN_LOW(object->port, object->led_num);

}
