/*
 * SPI_Module.h
 *
 *  Created on: Sep 5, 2021
 *      Author: dardeery
 */

#ifndef SPI_MODULE_H_
#define SPI_MODULE_H_

#include "gpio.h"


#define SPR0				0	//bits 0&1 used to config the freq
#define CPHA				2	//bits 2&3 used to config the transfer mode
#define MSTR				4	//bit  4   used to config the driver mode
#define	DORD				5	//bit  5   used to config the data order
#define SPE					6	//bit  6   used to enable the driver
#define SPIE				7	//bit  7   used to enable the driver interrupts
#define ENABLE				1
#define SPIF				7

//SPI_PINS according to the atmega32,otherwise..edit this
#define MOSI		5
#define MISO		6
#define SCK			7
#define SS			4


#define SPCR	*(volatile uint8*)0x2D
#define SPSR	*(volatile uint8*)0x2E
#define SPDR	*(volatile uint8*)0x2F

typedef enum{
	SPI_MSTR,
	SPI_SLV,
}SPI_OP_MODE;

void Spi_Init(SPI_OP_MODE MODE);
void Spi_Mstr_Send(uint8 data);
uint8 Spi_Mstr_Recieve();


void Spi_Slave_Send(uint8 data);
uint8 Spi_Slave_Recieve();

#endif /* SPI_MODULE_H_ */
