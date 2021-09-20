/*
 * smart home.c
 *
 * Created: 8/25/2021 1:34:37 PM
 * Author : dardeery
 */ 

#include "main.h"

/*--------------------------------------------------------------------------------------------

---------------------------------------------------------------------------------------------*/
int main(void)
{
	//INIT_SYSTEM();
	Spi_Init(SPI_MSTR);
	
	while (1) 
    {
		Spi_Mstr_Send(1);
		//control_dispatcher();
    }
}

