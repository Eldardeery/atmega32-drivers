/*
 * SPI_Module.c
 *
 *  Created on: Sep 5, 2021
 *      Author: dardeery
 */

#include"SPI_Module.h"

void Spi_Init(SPI_OP_MODE MODE)
{
	if(MODE == SPI_MSTR)
	{
		SET_PIN_DIRECTION(PORTB_T, SS, OUT);
		SET_PIN_DIRECTION(PORTB_T, MOSI, OUT);
		SET_PIN_DIRECTION(PORTB_T, MISO, IN);
		SET_PIN_DIRECTION(PORTB_T, SCK, OUT);

		//set ss high
		SET_BIT(*(volatile uint8*)PORTB_T,SS);

		 //Enable the SPI,master mode ,Set the clock speed to F/16
		SET_BIT(SPCR, SPE);
		SET_BIT(SPCR, SPR0);
		SET_BIT(SPCR, MSTR);

	}
	else
	{
		SET_PIN_DIRECTION(PORTB_T, SS, IN);
		SET_PIN_DIRECTION(PORTB_T, MOSI, IN);
		SET_PIN_DIRECTION(PORTB_T, MISO, OUT);
		SET_PIN_DIRECTION(PORTB_T, SCK, IN);

		 //Enable the SPI,Slave
		SET_BIT(SPCR, SPE);
	}

}
void Spi_Mstr_Send(uint8 data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}
uint8 Spi_Mstr_Recieve()
{
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));
	return(SPDR);

}


void Spi_Slave_Send(uint8 data)
{

}
uint8 Spi_Slave_Recieve()
{
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}
