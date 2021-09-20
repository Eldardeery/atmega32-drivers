/*
 * lcd.h
 *
 * Created: 19-Feb-19 7:26:33 AM
 *  Author: dardeery
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "lcd_cnfig.h"
#include "gpio.h"

void lcd_init      ();
void lcd_send_cmnd (uint8 cmnd);
void lcd_send_ch   (uint8 ch);
void lcd_send_str  (uint8 str[]);
void lcd_goto_xy   (uint8 x, uint8 y);
void lcd_send_num(int num);
void lcd_send_float(float num);

#define lcd_clear             0x01
#define lcd_home              0x02
#define decreamrnt_cursor     0x04
#define increamrnt_cursor     0x06
#define beginning_line_1_     0x80
#define beginning_line_2_     0xC0
#define shift_cursor_left     0x10
#define shift_cursor_right    0x14
#define move_cursor_right     0x06
















#endif /* LCD_H_ */
