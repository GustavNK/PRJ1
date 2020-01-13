/*
 * startRestartEnd.h
 *
 * Created: 04-01-2020 11:10:33
 *  Author: andre
 */ 


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
void stop();

#endif /* STARTRESTARTEND_H_ */