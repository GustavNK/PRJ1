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
	Motor(unsigned char port1 = 4, unsigned char port2 = 0);   //Initiates motor driver, with port "port" in PortB
	void setSpeed(unsigned char speed);	  //Set PWM on motor speed controller between 0-100%
	char getSpeed();
	void setDirection(unsigned char diriction);   // set direction of motor. Controlles H-bridge
	char getDirection();
private:
	unsigned char speed_;
	unsigned char direction_;
	//21312312312

}
#endif /* MOTORCONTROLLER_H_ */