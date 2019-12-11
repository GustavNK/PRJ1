/*
 * knap.c
 *
 * Created: 15-11-2019 11:27:17
 *  Author: andre
 */ 

#include <avr/interrupt.h>
#include "init.h"

void init() {
	
	//Klargør sensor
	EICRA |= 0b00001111;
	EIMSK |= 0b00000011;
	sei();
	
}

void deinit() {
	
	
	
}
