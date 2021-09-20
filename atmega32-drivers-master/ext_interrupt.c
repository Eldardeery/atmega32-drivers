/*
 * ext_interrupt.c
 *
 * Created: 2/29/2020 11:30:21 PM
 *  Author: dardeery
 */ 
#include "ext_interrupt.h"
#include <avr/interrupt.h>
static void (* my_func[3])();


void Init_ext_interrupt(str_int_cnfig * Iner_cnfig, void (*call_isr)(void))
{
	
	switch (Iner_cnfig->interrupt_num)
	{
		case My_int_0 :
		{	
			GICR |=(1<<6);
			SET_PIN_DIRECTION(PORTD_T,2,IN);		
			if (Iner_cnfig->interrupt_sense == Falling_edge)
			{
				MCUCR |=(1<<ISC01);
			} 
			else if (Iner_cnfig->interrupt_sense == Rising_edge)
			{
				MCUCR |=(1<<ISC01)|(1<<ISC00);
			}
			else if (Iner_cnfig->interrupt_sense == Any_logical_change)
			{
				MCUCR |=(1<<ISC00);
			}
			my_func[0] = call_isr;
			break;
		}
		case My_int_1 :
		{
			GICR |=(1<<7);
			SET_PIN_DIRECTION(PORTD_T,3,IN);
			if (Iner_cnfig->interrupt_sense == Falling_edge)
			{
				MCUCR |=(1<<ISC11);
			}
			else if (Iner_cnfig->interrupt_sense == Rising_edge)
			{
				MCUCR |=(1<<ISC11)|(1<<ISC10);
			}
			else if (Iner_cnfig->interrupt_sense == Any_logical_change)	
			{
				MCUCR |=(1<<ISC10);
			}	
			my_func[1] = call_isr;
			break;	
		}
		case My_int_2 :
		{
			GICR |=(1<<5);
			SET_PIN_DIRECTION(PORTB_T,2,IN);
			if (Iner_cnfig->interrupt_sense == Falling_edge)
			{
				MCUCSR &=~(1<<ISC2);	
			}
			else if (Iner_cnfig->interrupt_sense == Rising_edge)
			{
				MCUCSR |=(1<<ISC2);	
			}	
			my_func[2] = call_isr;
			break;
		}				
		
	}
}


void Enable_g_interrupt()
{
	sei();
}
void Disable_g_interrupt()
{
	cli();
}
/*
ISR(INT0_vect)
{
	my_func[0]();
}
*/
ISR(INT1_vect)
{
	my_func[1]();
}
ISR(INT2_vect)
{
	my_func[2]();
}
