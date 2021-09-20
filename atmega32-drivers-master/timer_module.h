/*
 * timer_module.-h
 *
 *  Created on: Mar 20, 2020
 *      Author: dardeery
 */

#ifndef TIMER_MODULE_H_
#define TIMER_MODULE_H_
#include"gpio.h"
#include <avr/interrupt.h>
/*
---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------
                          this is an example
str_time_cnfig mytimer ={timer2 ,prescaler_1024, 0x04};
void fun_ovf();
uint16 count =0;
int main(void)
{
	sei();
	timer_init(&mytimer);
	timer_interrupt_trig(timer2, fun_ovf);
	while(1);
}
void fun_ovf()
{
	count++;
	if (count == 2*31)
	{
		PORTC^=255;
		count =0;
	}
}
-------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------
*/


typedef enum
{
	TIMASK_T = 0x59,
	TIFR_t   = 0x58,
	/*timer1*/
	TCNT1_t   = 0x4C,
	TCNT1L_t  = 0x4C,
	TCNT1H_t  = 0x4D,
	TCCR1B_t  = 0x4E,
	TCCR1A_t  = 0x4F,
	/*timer0*/
	TCNT0_t   = 0x52,
	TCCR0_t   = 0x53,
	/*timer2*/
	TCNT2_t   = 0x44,
	TCCR2_t   = 0x45,
	}enum_timers_reg;

typedef enum
{
	timer0,
	timer1,
	timer2,
	}enum_timer_num;

typedef enum
{
	no_prescaler,
	prescaler_8,
	prescaler_timer2_32,
	prescaler_64,
	prescaler_timer2_128,
	prescaler_256,
	prescaler_1024,
}enum_prescaler;

typedef struct
{
	enum_timer_num timer;
	enum_prescaler prescaler;
	uint8 tcnt_inial_val;
}str_time_cnfig;

typedef enum
{
	CORRECT_PARAMETER,
	ERROR_PARAMETER,

}TIMER_ERROR;

TIMER_ERROR timer_init(str_time_cnfig *timer_cnfig);
void timer_deinit(str_time_cnfig *timer_cnfig);
void timer_interrupt_trig(enum_timer_num timer, void (*fcallback)(void));
#endif /* TIMER_MODULE_H_ */
