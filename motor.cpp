/*
 * Motor.cpp
 *
 * Created: 28-10-2019 12:07:24
 *  Author: Gustav
 */ 

#include "motor.h"

motor :: motor(unsigned char port1, unsigned char port2){  //Set port B nr. (PWM) og set port C nr.
	if ( !( DDRB & (1<<port1) ) && !( DDRC & (1<<port2) ) ){
	}
	DDRB |= (1<<port1);
	DDRC |= (1<<port2)
}

void setSpeed(unsigned char speed){  //Set PWM on motor speed controller between 0-100%
	
	
}

char getSpeed(){

}
	  
void setDirection(unsigned char diriction){   // set direction of motor. Controlles H-bridge

	
}  

char getDirrection(){
	
}
