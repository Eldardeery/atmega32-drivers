/*
 * EEPROM_25AA010A.h
 *
 * Created: 9/30/2021 11:33:25 PM
 *  Author: dardeery
 */ 


#ifndef EEPROM_25AA010A_H_
#define EEPROM_25AA010A_H_

#include "ATMEGA32_SPI.h"
#include <util/delay.h>

#define  CHIP_Select_Pin          0          
#define  CHIP_Select_Port         PORTB_T


void EEPROM25AA_Init();
void EEPROM25AA_WriteByte(uint16 address, uint8 data);
uint8 EEPROM25AA_ReadByte(uint16 address);

#endif /* EEPROM_25AA010A_H_ */