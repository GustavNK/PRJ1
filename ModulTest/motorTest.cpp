/*
 * testMotor.cpp
 *
 * Created: 06-12-2019 09:10:59
 * Author : Gustav
 */ 
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include "motor.h"

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		Motor myMotor;		//Declaring class 

		_delay_ms(1000);
		myMotor.setSpeed(150);
		_delay_ms(2000);
		myMotor.setSpeed(255);
		_delay_ms(2000);
		myMotor.setSpeed(0);
		_delay_ms(1000);
		myMotor.setDirection(1);
		_delay_ms(2000);
		myMotor.setSpeed(0);
		while(1){}
    }
}

