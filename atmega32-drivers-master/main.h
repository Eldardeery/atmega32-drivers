/*
 * main.h
 *
 * Created: 9/8/2021 3:08:23 PM
 *  Author: dardeery
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <util/delay.h>
#include <avr/io.h>

#include "gpio.h"
#include "ext_interrupt.h"
#include "lcd.h"
#include "SPI_Module.h"
#include "timer_module.h"
#include "led.h"
#include "EEPROM.H"
#include "password.h"
#include "keypad.h"


LED_CONFIG air_cond = {PORTD_T,4};
LED_CONFIG t_v      = {PORTD_T,5};
LED_CONFIG room1    = {PORTD_T,6};
LED_CONFIG room2    = {PORTD_T,7};


void INIT_SYSTEM(void)
{
	lcd_init();
	Init_Led(&room1);
	Init_Led(&room2);
	EEprom_Init();
	welcome_message();
	password_init();
}
void welcome_message()
{
	/*---------------------------first welcome -------------------------------*/
	lcd_send_cmnd(lcd_clear);
	lcd_goto_xy(4,1);
	lcd_send_str("welcome to");
	lcd_goto_xy(4,2);
	lcd_send_str("smart home");
	_delay_ms(5000);
	/*-------------------------------end of welcome------------------------------- */

}
void control_dispatcher()
{
uint8 pressed_key = 48;   // ascii code   for 1
bool_t check = E_FALSE;


/*------------------------------ask user to the password------------------------ */
lcd_send_cmnd(lcd_clear);
lcd_goto_xy(1,1);
lcd_send_str("Enter password");

/*-------------------------------check if pass is correct or not------------------------------- */
get_password();
check = check_password();
if (check == E_FALSE)
{
lcd_send_cmnd(lcd_clear);
lcd_goto_xy(1,1);
lcd_send_str("wrong password");
} 
else if (check == E_TRUE)
{
lcd_send_cmnd(lcd_clear);
lcd_goto_xy(1,1);
lcd_send_str("1 control Rooms");
lcd_goto_xy(1,2);
lcd_send_str("2 Change password");
/*-------------------------------check if control or change password------------------------------- */
/*---------------------------control rooms---------------------------- */
pressed_key =keyfind();
if (pressed_key == 49)
{
lcd_send_cmnd(lcd_clear);
lcd_goto_xy(1,1);
lcd_send_str("1:Room1  2:Room2");
lcd_goto_xy(1,2);
lcd_send_str("3:aircon  4:t.v");
/*---------------------check room1 or2-------------------- */
/*---------------------control room1 -------------------- */
pressed_key =keyfind();
if (pressed_key == 49)
{
control_room1();
} 
/*---------------------control room2 -------------------- */
else if (pressed_key == 50)
{
control_room2();
}
} 
/*---------------------air conditional ----------------- */
else if (pressed_key == 51)
{
	
}
/*---------------------t.v -------------------- */
else if (pressed_key == 52)
{
	
}

/*---------------------------change password--------------------------- */
else if (pressed_key == 50)
{
change_password();
}
}
/*-------------------------------end check if pass is correct or not------------------------------- */
}

void control_room1(void)
{
	uint8 pressed = 0;
	lcd_send_cmnd(lcd_clear);			   // clear lcd
	lcd_goto_xy(1,1);
	lcd_send_str("press 1=off 2=on");
	pressed =keyfind();
	
	if (pressed == 49)
	{
		Led_Off(&room1);
		lcd_send_str("room off");
		_delay_ms(2000);
	} 
	else if(pressed == 50)
	{
		Led_On(&room1);
		lcd_goto_xy(1,2);
		lcd_send_str("room on");
		_delay_ms(2000);		
	}
}

void control_room2(void)
{
	uint8 pressed = 0;
	
	lcd_send_cmnd(lcd_clear);
	lcd_goto_xy(1,1);
	lcd_send_str("press 1=off 2=on");
	pressed =keyfind();
	
	if (pressed == 49)
	{
		Led_Off(&room2);
		lcd_send_cmnd(lcd_clear);
		lcd_goto_xy(1,1);
		lcd_send_str("room off");
		_delay_ms(2000);
	}
	else if(pressed == 50)
	{
		Led_On(&room2);
		lcd_send_cmnd(lcd_clear);
		lcd_goto_xy(1,1);
		lcd_send_str("room on");
		_delay_ms(2000);
	}
	
}



#endif /* MAIN_H_ */