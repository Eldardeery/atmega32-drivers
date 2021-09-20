/*
 * lcd_cnfig.h
 *
 * Created: 19-Feb-19 7:27:16 AM
 *  Author: dardeery
 */ 


#ifndef LCD_CNFIG_H_
#define LCD_CNFIG_H_

#define EN                                    4
#define RS                                    5

#define DATA_BIT_MODE                         4
//   #if(DATA_BIT_MODE == 8) here we should define the ctrl port
//#define LCD_CTRL_PORT                        PORTD_T
//  #elif (DATA_BIT_MODE ==4) if 4bit mode should define higher or lower pins
//#define HIGHER_PINS                            1
#define LOWER_PINS                           1       
#define LCD_DATA_PORT                   PORTA_T
#endif /* LCD_CNFIG_H_ */