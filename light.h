/*========================================================================
FILENAME	: light.h
CREATED		: 28-10-2019 12:08:01
AUTHOR		: Simon og Shyn
DESCR.		: Opsætning af klasse, der styrer front- og baglys
==========================================================================*/
#ifndef __LIGHT_H__
#define __LIGHT_H__

class Led
{
public:
	Led();
	void initLED();
	void frontLight(unsigned char duty_cycle);
	void backLight(unsigned char duty_cycle);
};

#endif //__LIGHT_H__