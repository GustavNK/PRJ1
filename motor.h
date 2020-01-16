/*========================================================================
FILENAME	: Motor.h
CREATED		: 28-10-2019 12:06:50
AUTHOR		: Gustav
DESCR.		: Deceleration of motor controller
==========================================================================*/
#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

class Motor
{
public:
	explicit Motor();								//Initiates motor driver
	void setSpeed(unsigned char speed);				//Set PWM on motor speed controller between 0-255
	unsigned char getSpeed() const;
	void setDirection(unsigned char direction);		//Set direction of motor. Controlles the H-bridge
	unsigned char getDirection() const;
private:
	unsigned char speed_;
	unsigned char speedPin_;
	unsigned char dir_;
	unsigned char dirPin_;
};

#endif /* MOTORCONTROLLER_H_ */