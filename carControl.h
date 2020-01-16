/*========================================================================
FILENAME	: carControl.h
CREATED		: 22-11-2019 10:06:12
AUTHOR		: Andreas og Anders
DESCR.		: Method for carControl(), som styrer det meste af bilen
==========================================================================*/
/*
 * carControl.h
 *
 * Created: 22-11-2019 10:06:12
 *  Author: andre
 */ 


#ifndef CARCONTROL_H_
#define CARCONTROL_H_
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include "somo.h"
#include "uart.h"
#include "motor.h"
#include "light.h"
#include "startRestartStop.h"

char carControl(char sensorCounter, Motor* motor, Led* led);

#endif /* CARCONTROL_H_ */