/*
 * carControl.h
 *
 * Created: 22-11-2019 10:06:12
 *  Author: andre
 */ 


#ifndef CARCONTROL_H_
#define CARCONTROL_H_
#include "motor.h"
#include "light.h"

char carControl(char sensorCounter, Motor* motor, ledDriver* led);

#endif /* CARCONTROL_H_ */