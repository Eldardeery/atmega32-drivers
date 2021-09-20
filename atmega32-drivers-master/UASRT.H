/*
 * UASRT.h
 *
 * Created: 01-Feb-19 9:33:55 PM
 *  Author: dardeery
 */ 


#ifndef UASRT_H_
#define UASRT_H_

#include "gpio.h"
#include "UASRTCONFIG.h"

#define MY_UBBR  ((FOSC/(16*BUADE_RATE))-1)
void UASRT_init();
void UASRT_send_char(uint8 data);
void UASRT_send_string(uint8 *str);
uint8 UASRT_recieve_char();




#endif /* UASRT_H_ */