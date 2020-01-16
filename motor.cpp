/*========================================================================
FILENAME	: Motor.cpp
CREATED		: 28-10-2019 12:07:24
AUTHOR		: Gustav
DESCR.		: Controlls the direction and speed of the brushmotor
==========================================================================*/
#include "motor.h"
#include <avr/io.h>

#define speedPortReg DDRE
#define speedPort PORTB
#define dirPortReg DDRJ
#define dirPort PORTJ

Motor :: Motor()
{
	//Set class variables to default
	speedPin_ = 3;	//PE3(OC3A)
	dirPin_ = 1;	//PJ1
	speed_ = 0;		//0 == speed
	dir_ = 1;		//1 == forward
	
	// Setup PB5(OC1A) and PC0
	speedPortReg |= (1<<speedPin_);
	dirPortReg |= (1<<dirPin_);
	
	// Set to forward and 0 speed (Off)
	setDirection(dir_);
	setSpeed(speed_);
}

void Motor :: setSpeed(unsigned char s)
{	
	//Set PWM on motor speed controller between 0(off) - 255(maks)
	if( 0 > s || 255 < s ){
		speed_ = 0;							//set speed 0, if speed not correct
	}
	else {
		speed_ = 65536/255 * s;				//convert 8bit speed to 16bit speed
	}
	
	//Initiate PWM for OC1A
	speedPortReg |= (1<<speedPin_);
	TCCR3A |= 0b10000001;				//COM1A=10 non-inverting mode OC0A   WGM1A=0001 Non-fast PWM
	TCCR3B |= 0b00000100;				//256*clk/prescaler    16000000/(256*2*256) = 122Hz  
	//Update OCR
	OCR3A = speed_;
}

unsigned char Motor :: getSpeed() const
{
	return speed_;
}
	  
void Motor :: setDirection(unsigned char dir)
{
	dir_ = (dir == 0) ? 0 : 1;
	dirPort = (dir_ << dirPin_);
}

unsigned char Motor :: getDirection() const
{
	return dir_;
}