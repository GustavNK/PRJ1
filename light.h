/* 
* light.h
*
* Created: 28-10-2019 12:08:01
* Author: Rasmus
*/


#ifndef __LIGHT_H__
#define __LIGHT_H__


class ledDriver
{
	public:
	ledDriver();
	void initLED();
	void frontLight(unsigned char duty_cycle);
	void backLight(unsigned char duty_cycle);
};




#endif //__LIGHT_H__
