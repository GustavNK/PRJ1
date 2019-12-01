/*
 * Motor.cpp
 *
 * Created: 28-10-2019 12:07:24
 *  Author: Gustav
 */ 

#include <avr/io.h>
#include "motor.h"

Motor :: Motor(unsigned char port1, unsigned char port2){			//Set port B nr. (PWM) og set port C nr.
	if ( ( DDRB & (1<<port1) ) && ( DDRC & (1<<port2) ) )
	{
	}
	else
	{
		DDRB |= (1<<port1);
		DDRC |= (1<<port2);
	}
}

void Motor :: setSpeed(unsigned char speed){						//Set PWM on motor speed controller between 0-100%
	
	
}

char Motor :: getSpeed(){

	return '0';
}
	  
void Motor :: setDirection(unsigned char diriction){   // set direction of motor. Controlle H-bridge

	
}  

char Motor :: getDirection(){
	return '0';
}
