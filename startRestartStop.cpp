/*
 * startRestartEnd.cpp
 *
 * Created: 04-01-2020 11:10:21
 *  Author: andre
 */ 

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

void restartBil (Motor* motor, ledDriver* led) {
	char n, i, h, q;
	DDRB = 0;
	
	led->backLight(0);		// Sluk "back light"
	led->frontLight(0);		// Sluk "front light"
	motor->setSpeed(0);		// Sluk motor
	
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
		
		_delay_ms(75);
	}
	
	for (i = 0, q = 170; i < 4; i++) {
		if (i == 2) {
			reset();
		}
		
		PORTB = q;		_delay_ms(150);
		q = ~q;
		PORTB = 0;		_delay_ms(150);
	}
	_delay_ms(350);

}

void stop() {
	char n, i, h = 0;
	
	for (n = 255; n > 0; n--) {
		PORTB = n;
		i = 0; h += 1;
		do {
			_delay_ms(1);
			i++;
			
		} while (i != h);
		
		if (h == 128) {
			h = 0;	
		}
				
	}
	PORTB = 0;
}