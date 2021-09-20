#ifndef EEPROM_H_
#define EEPROM_H_


#include "gpio.h"


#define  EEAR                  *((volatile unsigned short*)(0x003E))
#define  EEARH                 *((volatile unsigned char*)(0x003F))
#define  EEARL                 *((volatile unsigned char*)(0x003E))
#define  EEDR                  *((volatile unsigned char*)(0x003D))
#define  EECR                  *((volatile unsigned char*)(0x003C))

#define EEAR0			0
#define EEAR1			1
#define EEAR2			2
#define EEAR3			3
#define EEAR4			4
#define EEAR5			5
#define EEAR6			6
#define EEAR7			7


#define EERE			0
#define EEWE			1
#define EEMWE			2
#define EERIE			3



void EEprom_Init();
void EEprom_Write(uint16 address, uint8 data);
uint8 EEprom_Read(uint8 address);
void EEprom_Write_Data(uint16 Address, uint8 data[]);
#endif