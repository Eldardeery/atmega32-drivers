/*
 * password.h
 *
 * Created: 9/12/2021 5:33:46 PM
 *  Author: dardeery
 */ 
#ifndef PASSWORD_H_
#define PASSWORD_H_
#include "lcd.h"
#include "EEPROM.h"
#include "common.h"
#include <util/delay.h>




void password_init();
void get_password(void);
bool_t check_password();
void change_password();

#endif /* PASSWORD_H_ */