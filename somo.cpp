/*========================================================================
FILENAME	: somo.cpp
CREATED		: 06-12-2019 11:09:26
AUTHOR		: Simon og Shyn
DESCR.		: Sends funktions through the UART to SOMO-II
==========================================================================*/
#include "somo.h"
#include "uart.h"

void playSource()
{
	SendChar(0x7E);
	SendChar(0x09);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(0x02);
	SendChar(0xFF);
	SendChar(0xF5);
	SendChar(0xEF);
	_delay_ms(200);
}

void playTrack(unsigned char tracknr)
{
	SendChar(0x7E);
	SendChar(0x03);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(tracknr);
	SendChar(0xFF);
	SendChar(0xFD-tracknr);
	SendChar(0xEF);
	_delay_ms(200);
}

void reset()
{
	SendChar(0x7E);
	SendChar(0x0C);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(0xFF);
	SendChar(0xF4);
	SendChar(0xEF);
	_delay_ms(200);
}

void setVol(unsigned char vol)
{
	if(vol < 0x01 || vol > 0x1E){ // Checks if vol is inside acceptable range
		vol = 5; // standard value
	}
	SendChar(0x7E);
	SendChar(0x06);
	SendChar(0x00);
	SendChar(0x00);	
	SendChar(vol);
	SendChar(0xFF);
	SendChar(0xF9-vol);
	SendChar(0xEF);
	_delay_ms(200);
}