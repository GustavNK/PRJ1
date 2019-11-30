/*
 * motorController.h
 *
 * Created: 28-10-2019 12:06:50
 *  Author: Gustav
 */ 


#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_
class motor{
public:
	explicit motor(unsigned char port1 = 4, unsigned char port2 = 0);   //Initiates motor driver, with port "port" in PortB
	void setSpeed(unsigned char speed);	  //Set PWM on motor speed controller between 0-100%
	char getSpeed() const;
	void setDirection(unsigned char diriction);   // set direction of motor. Controlles H-bridge
	char getDirection() const;
private:
	unsigned char speed_;
	unsigned char direction_;

}
#endif /* MOTORCONTROLLER_H_ */