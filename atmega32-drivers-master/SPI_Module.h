/*
 * ATMEGA32_SPI.h
 *
 * Created: 9/30/2021 12:00:08 PM
 *  Author: dardeery
 */ 


#ifndef ATMEGA32_SPI_H_
#define ATMEGA32_SPI_H_

#include <avr/io.h>
#include "gpio.h"


typedef enum
{
	SPI_Enable,
	SPI_Disable,
}SPI_Control;
typedef enum 
{
	SPI_Master_Mode,
	SPI_Slave_Mode,
	}SPI_Mode;
	

	
typedef enum
{
	SPI_Clock_Mode0,
	SPI_Clock_Mode1,
	SPI_Clock_Mode2,
	SPI_Clock_Mode3,
}SPI_Clock_Mode;
typedef enum
{
	FCPU_By2,
	FCPU_By4,
	FCPU_By8,
	FCPU_By16,
	FCPU_By32,
	FCPU_By64,
	FCPU_By128,
	}SPI_FReq;
	
typedef enum
{
	SPI_Intrrupt_Enable,
	SPI_Intrrupt_Disable,
	}SPI_Intrrupt;
	
typedef enum
{
	SPI_Msb,
	SPI_Lsb,
	}SPI_DtaOrder;	
	
	
typedef struct
{
	SPI_Control             spi_Conrtol;
	SPI_Mode                spi_Select_Mode;
	SPI_Clock_Mode          spi_Clck_Mode;
	SPI_FReq                spi_Clock_Freq;
	SPI_DtaOrder            spi_data_order;
	SPI_Intrrupt            spi_Interrupt;
}SPI_Configuration_Struct;



void SPI_Init(SPI_Configuration_Struct * SPI_Object);
uint8 SPI_ReadWrite_ByteBlocking(uint8 data);
uint8 SPI_ReadWrite_ByteNonBlocking(uint8 data);
#endif /* ATMEGA32_SPI_H_ */
