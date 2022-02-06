#include <lpc214x.h>
#include "LPC2148_delay.h"
#include "LPC2148_LCD_4_BIT_HEADER_FILE.h"

char SPI_Receive_Data()
{
	IO0CLR = (1<<7);										/* SSEL = 0, enable SPI communication with slave */
	S0SPCR = 0x058C;										/* Transmit Flush byte */
	while (!((S0SPSR & 0x80) == 0X80));	/* Wait till data transmission is completed */
	IO0SET = (1<<7);										/* SSEL = 1, disable SPI communication with slave */
	return S0SPDR;											/* Return the data received */
}

int main()
{
	PINSEL0=0X00005500;
	PINSEL1=0X00000000;
	PINSEL2 = 0x00000000;
	IODIR0=0Xffff0000;
	IODIR1 = 0x3F0 << 16;
	
	Lcd_Intialization();
	
	Lcd_Command(0x80);
	Lcd_String("LYCASOFT");
	
	Lcd_Command(0xC0);
	while(1)
	{
		char Ch = SPI_Receive_Data();
		Lcd_Data(Ch);
		delay(5);
	}
}