/*
 * lcd.c
 *
 * Created: 19-Feb-19 7:27:35 AM
 *  Author: dardeery
 */ 
#include "lcd.h"
#include <util/delay.h>

void lcd_init      (void)
{	
#if (DATA_BIT_MODE == 8)
	SET_PIN_DIRECTION(LCD_CTRL_PORT,RS,OUT);
	SET_PIN_DIRECTION(LCD_CTRL_PORT,EN,OUT);
	SET_PORT_DIRECTION(LCD_DATA_PORT,OUT);
	WRITE_PIN_LOW(LCD_CTRL_PORT,EN);
	lcd_send_cmnd(0x38);
	lcd_send_cmnd(0x0E);
	lcd_send_cmnd(0x01);
	_delay_ms(1000);
	lcd_send_cmnd(0x06);
	////////////////////////////////////////////////////////////////
	#elif (DATA_BIT_MODE == 4)
	SET_PIN_DIRECTION(LCD_DATA_PORT,EN,OUT);
	SET_PIN_DIRECTION(LCD_DATA_PORT,RS,OUT);
		
	#ifdef LOWER_PINS
	SET_PIN_DIRECTION(LCD_DATA_PORT,0,OUT);
	SET_PIN_DIRECTION(LCD_DATA_PORT,1,OUT);	
	SET_PIN_DIRECTION(LCD_DATA_PORT,2,OUT);
	SET_PIN_DIRECTION(LCD_DATA_PORT,3,OUT);	
	
	WRITE_PIN_LOW(LCD_DATA_PORT,EN);
	lcd_send_cmnd(0x33);
	lcd_send_cmnd(0x32);
	lcd_send_cmnd(0x28);
	//lcd_send_cmnd(0x0E);    //display on cursor blink
	lcd_send_cmnd(0x0C);		//display on cursor off
	lcd_send_cmnd(0x01);
	_delay_ms(1000);
	lcd_send_cmnd(0x06);	
	#endif
	
		#ifdef HIGHER_PINS
		SET_PIN_DIRECTION(LCD_DATA_PORT,4,OUT);
		SET_PIN_DIRECTION(LCD_DATA_PORT,5,OUT);
		SET_PIN_DIRECTION(LCD_DATA_PORT,6,OUT);
		SET_PIN_DIRECTION(LCD_DATA_PORT,7,OUT);	 
		
		WRITE_PIN_LOW(LCD_DATA_PORT,EN);
		lcd_send_cmnd(0x33);
		lcd_send_cmnd(0x32);
		lcd_send_cmnd(0x28);
		lcd_send_cmnd(0x0E);
		lcd_send_cmnd(0x01);
		_delay_ms(1000);
		lcd_send_cmnd(0x06);		
		#endif

#endif
}
void lcd_send_cmnd (uint8 cmnd)
{
#if (DATA_BIT_MODE==8)
		WRITE_PORT_VAL(LCD_DATA_PORT ,cmnd);
		WRITE_PIN_LOW(LCD_CTRL_PORT ,RS);
		WRITE_PIN_HIGH(LCD_CTRL_PORT ,EN);
		_delay_ms(1);
		WRITE_PIN_LOW(LCD_CTRL_PORT ,EN);
		_delay_ms(100);		
	
#elif (DATA_BIT_MODE==4)	
  #ifdef LOWER_PINS
		WRITE_PORT_VAL(LCD_DATA_PORT ,cmnd>>4);
		WRITE_PIN_LOW(LCD_DATA_PORT ,RS);
		WRITE_PIN_HIGH(LCD_DATA_PORT ,EN);
		_delay_ms(1);
		WRITE_PIN_LOW(LCD_DATA_PORT ,EN);
		_delay_ms(100);
		WRITE_PORT_VAL(LCD_DATA_PORT ,cmnd & 0x0f);
		WRITE_PIN_LOW(LCD_DATA_PORT ,RS);
		WRITE_PIN_HIGH(LCD_DATA_PORT ,EN);
		_delay_ms(1);
		WRITE_PIN_LOW(LCD_DATA_PORT ,EN);
		_delay_ms(100); 

	#else 
	 		WRITE_PORT_VAL(LCD_DATA_PORT ,cmnd&0xf0);
	 		WRITE_PIN_LOW(LCD_DATA_PORT ,RS);
	 		WRITE_PIN_HIGH(LCD_DATA_PORT ,EN);
	 		_delay_ms(1);
	 		WRITE_PIN_LOW(LCD_DATA_PORT ,EN);
	 		_delay_ms(100);
	 		WRITE_PORT_VAL(LCD_DATA_PORT ,cmnd<<4);
	 		WRITE_PIN_LOW(LCD_DATA_PORT ,RS);
	 		WRITE_PIN_HIGH(LCD_DATA_PORT ,EN);
	 		_delay_ms(1);
	 		WRITE_PIN_LOW(LCD_DATA_PORT ,EN);
	 		_delay_ms(100);
	#endif
	 
  #endif
  	
}
void lcd_send_ch   (uint8 ch)
{
	
#if (DATA_BIT_MODE==8)
		WRITE_PORT_VAL(LCD_DATA_PORT,ch);
		WRITE_PIN_HIGH(LCD_CTRL_PORT ,RS);
		WRITE_PIN_HIGH(LCD_CTRL_PORT ,EN);
		_delay_ms(1);
		WRITE_PIN_LOW(LCD_CTRL_PORT ,EN);
		_delay_ms(100);	
#elif (DATA_BIT_MODE==4)
	#ifdef LOWER_PINS
		WRITE_PORT_VAL(LCD_DATA_PORT,ch>>4);
		WRITE_PIN_HIGH(LCD_DATA_PORT ,RS);
		WRITE_PIN_HIGH(LCD_DATA_PORT ,EN);
		_delay_ms(1);
		WRITE_PIN_LOW(LCD_DATA_PORT ,EN);
		_delay_ms(100);
		WRITE_PORT_VAL(LCD_DATA_PORT ,ch & 0x0f);
		WRITE_PIN_HIGH(LCD_DATA_PORT ,RS);
		WRITE_PIN_HIGH(LCD_DATA_PORT ,EN);
		_delay_ms(1);
		WRITE_PIN_LOW(LCD_DATA_PORT ,EN);
		_delay_ms(100);	
	
		
#endif					
		#ifdef HIGHER_PINS
		WRITE_PORT_VAL(LCD_DATA_PORT,ch&0xf0);
		WRITE_PIN_HIGH(LCD_DATA_PORT ,RS);
		WRITE_PIN_HIGH(LCD_DATA_PORT ,EN);
		_delay_ms(1);
		WRITE_PIN_LOW(LCD_DATA_PORT ,EN);
		_delay_ms(100);
		WRITE_PORT_VAL(LCD_DATA_PORT ,ch<<4);
		WRITE_PIN_HIGH(LCD_DATA_PORT ,RS);
		WRITE_PIN_HIGH(LCD_DATA_PORT ,EN);
		_delay_ms(1);
		WRITE_PIN_LOW(LCD_DATA_PORT ,EN);
		_delay_ms(100);				
		#endif
			
#endif	
}
void lcd_send_str  (uint8 str[])
{
	uint8 i =0;
	while(str [i] !=0)
	{
		lcd_send_ch(str[i]);
		i++;
	}
}
void lcd_goto_xy   (uint8 x, uint8 y)
{
	uint8 first_char_adr[] = {0x80, 0xC0, 0x94, 0xD4};
	lcd_send_cmnd(first_char_adr[y-1]+x-1);
	_delay_ms(100);	
}


void lcd_send_num(int num)
{
	char s[4];
	sprintf(s,"%d",num);
	lcd_send_str(s);
}

void lcd_send_float(float num)
{
	char s[6];
	int inte ,frac;
	inte = (int) num;
	frac = (int)((num - inte)*10000);
	sprintf(s,"%d.%d",inte ,frac);
	lcd_send_str(s);
}
