/*========================================================================
FILENAME	: main.cpp
CREATED		: 28-10-2019 11:48:57
AUTHOR		: Andreas og Anders
DESCR.		: <Description of file contents>
==========================================================================*/
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light.h"
#include "carControl.h"
#include "motor.h"
#include "uart.h"
#include "somo.h"
#include "startRestartStop.h"

// Sætter globale variabler, til brug i interrupts
volatile unsigned char btnStatus; 
volatile signed char quitBtn;
volatile unsigned char sensorStatus;
volatile signed char statusCounter;

//INT2_vect og INT3_vect aktiveres af SW2 og SW3 på arduino shield
ISR(INT2_vect)
{
	btnStatus++;
}

ISR(INT3_vect)
{
	quitBtn = -1;
}

// INT4_vect og INT5_vect aktiveres af venstre og højre sensor
ISR(INT4_vect)
{
	sensorStatus = statusCounter;
}

ISR(INT5_vect)
{	
	sensorStatus = statusCounter;	
}

int main(void)
{	
	// Klargøring af porte
	DDRE &= 0b11001111; // Port E, pin 4 og 5 er input
	DDRB = 0xFF; // Port B er sat til output
	
	// Interrupt enable og initiering
	EIMSK |= 0b00111100;	//INT2, INT3, INT4 og INT5 interrupt enable
	EICRA |= 0b11110000;	//Rising edge af INT2 og INT3 genererer interrupt request
	EICRB |= 0b00001111;	//Rising edge af INT4 og INT5 genererer interrupt request
	sei();					//Global interrupt enable
	
	Motor carMotor;			//Klargør motor
	Led led;				//Klargør LED/lys
	
	//Klargør SOMO/lyd
	InitUART(9600, 8, 0);
	reset();				
	playSource();
	_delay_ms(300);
	setVol(0x1E);	
	
	while(quitBtn != -1)
	{	
		// Variable og funktioner klargøres
		statusCounter = 0; // statusCounter bestemmer bilens 'case'
		btnStatus = 0; // btnStatus styrer om bilen skal gå i tomgang, køre eller lave et reset
		
		led.initLED();
	
		startBil();

		//Bestemmer hvilken case bilen er i

		// Sørger for, at koden forbliver i loopet, indtil reset knappen er aktiveret (btnStatus går fra 1 til 2) - med mindre alle cases er kørt i carControl
		while (btnStatus < 2 && statusCounter != -1 && quitBtn != -1) 
		{
			// Sørger for, at SW2 aktiverer algoritmen (btnStatus går fra 0 til 1) - sensorCounter bliver reinitieret
			if (btnStatus == 1 && statusCounter == 0) 
				sensorStatus = 0;
			
			// Algoritmen køre næste 'case' når sensorCounter bliver lig med statusCounter
			if (sensorStatus == statusCounter && btnStatus == 1) 
			{
				// sensorStatus får en incrementeret værdi fra carControl, så næste stadie køres
				statusCounter = carControl(sensorStatus, &carMotor, &led);
			}
		}
		// Deinitialize - restart bil
		// if sætning, så vi sikre os restart, kun ved de specifikke betingelser 
		if (statusCounter == -1 || btnStatus > 1 || quitBtn == -1) {
			restartBil(&carMotor, &led);
			
			// afslutter program
			if (quitBtn == -1)
				stopBil();	
		}			
	}
	return 0;
}