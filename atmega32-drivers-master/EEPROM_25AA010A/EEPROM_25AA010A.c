/*
 * EEPROM_25AA010A.c
 *
 * Created: 9/30/2021 11:33:35 PM
 *  Author: dardeery
 */ 
#include "EEPROM_25AA010A.h"
#include "gpio.h"

#define   EEPROM_WR_en_cmd          (0x06)
#define   EEPROM_Writ_cmd           (0x02)
#define   EEPROM_Read_Cmd           (0x03)

#define DUMMY_Data                  (0x00)

SPI_Configuration_Struct * spi_eeprom ={SPI_Enable,
									SPI_Master_Mode,
									FCPU_By4,
									SPI_Clock_Mode3,
									SPI_Msb,
									SPI_Intrrupt_Disable
									};	
void EEPROM25AA_Init()
{
	SPI_Init(&spi_eeprom);
	SET_PIN_DIRECTION(CHIP_Select_Port, CHIP_Select_Pin,OUT);
}
void EEPROM25AA_WriteByte(uint16 address, uint8 data)
{
	WRITE_PIN_LOW(CHIP_Select_Port, CHIP_Select_Pin);
	SPI_ReadWrite_ByteBlocking(EEPROM_WR_en_cmd);
	WRITE_PIN_HIGH(CHIP_Select_Port, CHIP_Select_Pin);
	_delay_ms(50);
	WRITE_PIN_LOW(CHIP_Select_Port, CHIP_Select_Pin);
	SPI_ReadWrite_ByteBlocking(EEPROM_Writ_cmd);
	SPI_ReadWrite_ByteBlocking(address);
	SPI_ReadWrite_ByteBlocking(data);
	WRITE_PIN_HIGH(CHIP_Select_Port, CHIP_Select_Pin);
	_delay_ms(50);
}
uint8 EEPROM25AA_ReadByte(uint16 address)
{
	uint8 readData =0;
	WRITE_PIN_LOW(CHIP_Select_Port, CHIP_Select_Pin);
	SPI_ReadWrite_ByteBlocking(EEPROM_Read_Cmd);
	SPI_ReadWrite_ByteBlocking(address);
	readData = SPI_ReadWrite_ByteBlocking(DUMMY_Data);
	WRITE_PIN_HIGH(CHIP_Select_Port, CHIP_Select_Pin);
	return readData;
}