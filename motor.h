/*
 * motorController.h
 *
 * Created: 28-10-2019 12:06:50
 *  Author: Gustav
 */ 


#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_
class Motor{
public:
	explicit Motor();   //Initiates motor driver  No arguments should be given  speed=PE3(OC3A) dir=PC0
	void setSpeed(unsigned char speed);	  //Set PWM on motor speed controller between 0-255
	unsigned char getSpeed() const;
	void setDirection(unsigned char direction);   // set direction of motor. Controlles H-bridge
	unsigned char getDirection() const;
private:
	unsigned char speed_;
	unsigned char speedPin_;
	unsigned char dir_;
	unsigned char dirPin_;
};
#endif /* MOTORCONTROLLER_H_ */