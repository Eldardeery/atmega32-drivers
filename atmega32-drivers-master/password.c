/*
 * password.c
 *
 * Created: 9/12/2021 5:34:02 PM
 *  Author: dardeery
 */ 
#include "password.h"

//uint8 initial_password[4] = {"0000"};
uint16 eeprom_address = 100;

uint8 saved_password[4] = {"0000"};;
uint8 user_password[4];


void password_init()
{
	EEprom_Write_Data(eeprom_address,saved_password);
}


void get_password(void)
{
	uint8 i,j;
	
	lcd_goto_xy(1,2);
	for (i=0; i<4; i++)
	{
		user_password[i] =keyfind();
		lcd_send_ch(user_password[i]);
		_delay_ms(700);
		lcd_send_cmnd(shift_cursor_left);
		lcd_send_ch('*');
	}
	
}

bool_t check_password()
{
	bool_t return_value = E_FALSE;
	uint8 i,j;	
	for (j=0; j<4; j++)
	{
		if (saved_password[j] !=user_password[j])
		{
			return_value = E_FALSE;
			break;
		}
		else
		{
			return_value = E_TRUE;
		}
	}
	return return_value;
}

void change_password()
{
		uint8 i;
		lcd_send_cmnd(lcd_clear);
		lcd_goto_xy(1,1);
		lcd_send_str("Enter new pass");
		get_password();
		lcd_send_cmnd(lcd_clear);
		lcd_goto_xy(1,1);
		lcd_send_str("save new password");
		EEprom_Write_Data(eeprom_address,user_password);
		for(i=0; i<4; i++)
		{
			saved_password[i]=EEprom_Read(eeprom_address);
			eeprom_address++;
		}

}
