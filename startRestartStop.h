/*========================================================================
FILENAME	: startRestartEnd.h
CREATED		: 04-01-2020 11:10:33
AUTHOR		: Andreas
DESCR.		: Methods for funktioner til at styre bilens genstart funktioner
==========================================================================*/
#ifndef STARTRESTARTEND_H_
#define STARTRESTARTEND_H_
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include "somo.h"
#include "motor.h"
#include "light.h"

void startBil();
void restartBil(Motor* motor, Led* led);
void stopBil();
void LEDCounter(char status);

#endif /* STARTRESTARTEND_H_ */