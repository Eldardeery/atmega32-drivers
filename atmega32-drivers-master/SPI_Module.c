/*
 * ATMEGA32_SPI.c
 *
 * Created: 9/30/2021 11:59:56 AM
 *  Author: dardeery
 */ 


#include "ATMEGA32_SPI.h"


void SPI_Init(SPI_Configuration_Struct * SPI_Object)
{
	SPSR =0;
	SPDR =0;
	switch (SPI_Object->spi_Conrtol)
	{
		case SPI_Enable:
		SPCR |=(1<<SPE);
		
		break;
		
		case SPI_Disable:
		SPCR &=~(1<<SPE);
		break;
		default:
		break;
	}
	switch (SPI_Object->spi_Select_Mode)
	{
		case SPI_Master_Mode:
		SPCR |=(1<<MSTR);
		SET_PIN_DIRECTION(PORTB_T,4,OUT);
		SET_PIN_DIRECTION(PORTB_T,5,OUT);
		SET_PIN_DIRECTION(PORTB_T,6,OUT);
		SET_PIN_DIRECTION(PORTB_T,7,OUT);
		break;
		
		case SPI_Slave_Mode:
		SPCR &=~(1<<MSTR);
		SET_PIN_DIRECTION(PORTB_T,6,IN);
		break;
		default:
		break;
	}
	
	switch (SPI_Object->spi_Clck_Mode)
	{
		case SPI_Clock_Mode0:
		
		break;
		case SPI_Clock_Mode1:
		SPCR |=(1<<CPHA);
		break;
		case SPI_Clock_Mode2:
		SPCR |=(1<<CPOL);
		break;
		case SPI_Clock_Mode3:
		SPCR |=(1<<CPHA)|(1<<CPOL);
		break;
	}
	switch (SPI_Object->spi_Clock_Freq)
	{
		case FCPU_By2:
		SPSR |=(1<<SPI2X);
		break;
		case FCPU_By4:
		
		break;
		case FCPU_By8:
		SPSR |=(1<<SPI2X);
		SPCR |=(1<<SPR0);
		break;
		case FCPU_By16:
		SPCR |=(1<<SPR0);
		break;
		case FCPU_By32:
		SPSR |=(1<<SPI2X);
		SPCR |=(1<<SPR1);
		break;
		case FCPU_By64:
		SPSR |=(1<<SPI2X);
		SPCR |=(1<<SPR0);
		SPCR |=(1<<SPR1);
		break;
		case FCPU_By128:
		SPCR |=(1<<SPR0);
		SPCR |=(1<<SPR1);
		break;
		
		default:
		break;
	}
	
	switch (SPI_Object->spi_data_order)
	{
		case SPI_Msb:
		SPCR &=~(1<<DORD);
		break;
		case SPI_Lsb:
		SPCR |=(1<<DORD);
		break;
	}
	switch (SPI_Object->spi_Interrupt)
	{
		case SPI_Intrrupt_Enable:
		SPCR |=(1<<SPIE);
		break;
		
		case SPI_Intrrupt_Disable:
		SPCR &=~(1<<SPIE);
		break;
	}
	
}
uint8 SPI_ReadWrite_ByteBlocking(uint8 data)
{
	SPDR = data;
	while ((SPSR &(1<<SPIF))==0);
	return SPDR;
}
uint8 SPI_ReadWrite_ByteNonBlocking(uint8 data);
