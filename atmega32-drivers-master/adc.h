/*
 * adc.h
 *
 * Created: 05-Sep-19 5:44:43 PM
 *  Author: dardeery
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "gpio.h"


/*					 ex for lm35
#define channel_num       0
volatile float temp = 0.0;

int main(void)
{

	lcd_init();
	ADC_Init(channel_num);
	lcd_goto_xy(1,1);
	lcd_send_str("LM35 sensor");
	
    while (1) 
    {
		lcd_goto_xy(1,2);
		temp = (((ADC_Read(channel_num))*(0.488))-49);  // 49 is 1 asci code
		lcd_send_num(temp);
    }
}
*/

void ADC_Init(char channel)	;
uint8 ADC_Read(char channel);


#endif /* ADC_H_ */