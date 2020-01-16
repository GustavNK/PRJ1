/*========================================================================
FILENAME	: startRestartEnd.cpp
CREATED		: 04-01-2020 11:10:21
AUTHOR		: Andreas
DESCR.		: Laver et "lysshow" på PORTB, og kan starte/stoppe/restarte bilens tilstand
==========================================================================*/
#include "startRestartStop.h"

void startBil() {
	
	PORTB = 0;
	
	for (char n = 0; n < 9; n++) {
		PORTB = (1 << (7-n));
		_delay_ms(150);
	}
	
	PORTB = 2; _delay_ms(150);
	
	for (char n = 0; n < 3; n++) {
		PORTB = 4;
		_delay_ms(150);		
		PORTB = 8;
		_delay_ms(150);
	}

	PORTB = 12;
}

void restartBil (Motor* motor, Led* led) {
	char n, i, h/*, q*/;
	DDRB = 0;
		
	led->backLight(0);		// Sluk "back light"
	led->frontLight(0);		// Sluk "front light"
	motor->setSpeed(0);		// Sluk motor
	reset();				// Reset lyd
	
	for (n = 0, i = 0, h = 0; n < 36 ; n++ && i++) {

		if (h == 0 || h == 2) {
			PORTB |= (1 << (7 - i));
			DDRB = (1 << (7 - i));
		}
		else if (h == 1 || h == 3) {
			PORTB |= (1 << i);
			DDRB = (1 << i);
		}
		else {
			PORTB = 0;
			DDRB = 255;
		}
		
		if (i == 7) {
			h++;
			i = 0;
		}
		_delay_ms(100);			
	}
}

void stopBil() {
	char n, i= 0;
	
	for (n = 0; n < 44; n++ && i++) {
		
		PORTB = (1 << i);
		PORTB |= (1 << (7 - i));
		
		_delay_ms(150);
		
		if (i == 7)
			i = 0;
			
		else if (i == 3)
			i++;	
					
	}
	
	PORTB = 0xFF;
	_delay_ms(500);
	PORTB = 0;
}

void LEDCounter(char status) {
	
	if (status == 0)
	PORTB = 1;
	
	else if (status < 8) 
		PORTB = (1 << status);
	
	else if (status > 7){
		PORTB = (1 << (status - 8));
		PORTB |= (1 << (status - 4));
	}	
}	