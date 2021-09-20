


#include "EEPROM.H"


void EEprom_Init()
{

}
void EEprom_Write(uint16 address, uint8 data)
{
	
	EEARL=(unsigned char)address;
	EEARH=(unsigned char)address>>8;
	EEDR=data;
	EECR|=(1<<EEMWE);
	EECR|=(1<<EEWE);
	while(((EECR&(1<<EEWE))>>EEWE)==1);

}
uint8 EEprom_Read(uint8 address)
{
	EEARL=(unsigned char)address;
	EEARH=(unsigned char)address>>8;
	EECR|=(1<<EERE);
	return EEDR;
}


void EEprom_Write_Data(uint16 Address, uint8 data[])
{
	uint8 i =0 ;
	while(data[i]!=0)
	{
		EEprom_Write(Address,data[i]);
		Address++;
		i++;
	}
}


