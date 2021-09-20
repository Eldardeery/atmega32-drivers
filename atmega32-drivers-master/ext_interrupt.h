/*
 * ext_interrupt.h
 *
 * Created: 2/29/2020 11:30:58 PM
 *  Author: dardeery
 */ 


#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_
#include <avr/interrupt.h>
#include <avr/io.h>
#include "gpio.h"
typedef enum 
{
	My_int_0,
	My_int_1,
	My_int_2,
	}enum_Int_num;
	
typedef enum
{
	low_level,
	Rising_edge,
	Falling_edge,
	Any_logical_change,
	
	}enum_Int_sense;	
	
typedef struct
{
	enum_Int_num   interrupt_num;
	enum_Int_sense interrupt_sense;
	}str_int_cnfig;
void callback(void (* my_func)(void));
void Init_ext_interrupt(str_int_cnfig * Iner_cnfig, void (*call_isr)(void));
void Enable_g_interrupt();
void Disable_g_interrupt();



#endif /* EXT_INTERRUPT_H_ */