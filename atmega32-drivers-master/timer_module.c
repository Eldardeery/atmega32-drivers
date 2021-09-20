/*
 * timer_module.c
 *
 *  Created on: Mar 20, 2020
 *      Author: dardeery
 */
#include<avr/interrupt.h>
#include "avr/io.h"
#include"timer_module.h"



static void (*my_isr[3])(void);

TIMER_ERROR timer_init(str_time_cnfig *timer_cnfig)
{
	TIMER_ERROR return_value = CORRECT_PARAMETER;
	switch (timer_cnfig->timer)
	{
	case timer0:
	{
		*(volatile uint8 *)TCCR0_t =0x5;
		
		*(volatile uint8*)(TIMASK_T) |= 0x01;
		*(volatile uint8 *)(TCNT0_t) = timer_cnfig->tcnt_inial_val;
		

		if (timer_cnfig->prescaler == no_prescaler)
		{
			*(volatile uint8*)(TCCR0_t) = 0x01;
		}
		else if (timer_cnfig->prescaler == prescaler_8)
		{
			*(volatile uint8*)(TCCR0_t) = 0x02;
		}
		else if (timer_cnfig->prescaler == prescaler_64)
		{
			*(volatile uint8*)(TCCR0_t) = 0x03;
		}
		else if (timer_cnfig->prescaler == prescaler_256)
		{
			*(volatile uint8*)(TCCR0_t) = 0x04;
		}
		else if (timer_cnfig->prescaler == prescaler_1024)
		{
				*(volatile uint8 *)TCCR0_t =(1<<0);
				*(volatile uint8 *)TCCR0_t =(1<<2);;
		}
		else 
		return_value =ERROR_PARAMETER;
		break;
	}
	case timer1:
	{
		*(volatile uint8*)(TIMASK_T) |= 0x04;
		*(volatile uint8 *)(TCNT1_t) = timer_cnfig->tcnt_inial_val;
		if (timer_cnfig->prescaler == no_prescaler)
		{
			*(volatile uint8*)(TCCR1B_t) = 0x01;
		}
		else if (timer_cnfig->prescaler == prescaler_8)
		{
			*(volatile uint8*)(TCCR1B_t) = 0x02;
		}
		else if (timer_cnfig->prescaler == prescaler_64)
		{
			*(volatile uint8*)(TCCR1B_t) = 0x03;
		}
		else if (timer_cnfig->prescaler == prescaler_256)
		{
			*(volatile uint8*)(TCCR1B_t) = 0x04;
		}
		else if (timer_cnfig->prescaler == prescaler_1024)
		{
			*(volatile uint8*)(TCCR1B_t) = 0x05;
		}
		else
		return_value =ERROR_PARAMETER;		
		break;
	}
	case timer2:
	{
		*(volatile uint8*)(TIMASK_T) |= 0x40;
		*(volatile uint8 *)(TCNT2_t) = timer_cnfig->tcnt_inial_val;
		if (timer_cnfig->prescaler == no_prescaler)
		{
			*(volatile uint8*)(TCCR2_t) = 0x01;
		}
		else if (timer_cnfig->prescaler == prescaler_8)
		{
			*(volatile uint8*)(TCCR0_t) = 0x02;
		}
		else if (timer_cnfig->prescaler == prescaler_timer2_32)
		{
			*(volatile uint8*)(TCCR0_t) = 0x03;
		}
		else if (timer_cnfig->prescaler == prescaler_64)
		{
			*(volatile uint8*)(TCCR0_t) = 0x04;
		}
		else if (timer_cnfig->prescaler == prescaler_timer2_128)
		{
			*(volatile uint8*)(TCCR0_t) = 0x05;
		}
		else if (timer_cnfig->prescaler == prescaler_256)
		{
			*(volatile uint8*)(TCCR0_t) = 0x06;
		}
		else if (timer_cnfig->prescaler == prescaler_1024)
		{
			*(volatile uint8*)(TCCR0_t) = 0x07;
		}
		else
		return_value =ERROR_PARAMETER;		
		break;
		
	}
}
return return_value;
}
void timer_deinit(str_time_cnfig *timer_cnfig)
{
	if(timer_cnfig->timer == timer0)
	{
		/*stop clock source timer off*/
		*(volatile uint8*)TCCR0_t = 0x00;
	}
	else if(timer_cnfig->timer == timer1)
	{
		/*stop clock source timer off*/
		*(volatile uint8*)TCCR1B_t = 0x00;
	}
	else if(timer_cnfig->timer == timer2)
	{
		/*stop clock source timer off*/
		*(volatile uint8*)TCCR2_t = 0x00;
	}
}

void timer_interrupt_trig(enum_timer_num timer, void (*fcallback)(void))
{
	if (timer == timer0)
	{
		my_isr[0] = fcallback;
	}
	else if (timer == timer1)
	{
		my_isr[1] = fcallback;
	}
	else if (timer == timer2)
	{
		my_isr[2] = fcallback;
	}
}

ISR(TIMER0_OVF_vect)
{
	(*my_isr[0])();
	*(volatile uint8 *)(TIFR_t) |= 0x01;
}

ISR(TIMER1_OVF_vect)
{
	(*my_isr[1])();
	*(volatile uint8 *)(TIFR_t) |= 0x04;
}

ISR(TIMER2_OVF_vect)
{
	(*my_isr[2])();
	*(volatile uint8 *)(TIFR_t) |= 0x40;
}
