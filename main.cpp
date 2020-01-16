/*========================================================================
FILENAME	: main.cpp
CREATED		: 28-10-2019 11:48:57
AUTHOR		: Andreas og Anders
DESCR.		: Main algorithm
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
volatile unsigned char btnStatus; // btnStatus styrer om bilen skal gå i tomgang, køre eller lave et reset
volatile signed char quitBtn;// quitBtn terminere programmet ved quitBtn = -1
volatile unsigned char sensorStatus; // bestemer stadie af programmet
volatile signed char statusCounter; // tæller hvor mange 'cases' der er blevet kørt

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
	DDRE &= 0b11001111;		// Port E, pin 4 og 5 er input
	DDRB = 0xFF;			// Port B er sat til output
	
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
	setVol(0x1D);
	
	while(quitBtn != -1)
	{	
		// Variabler og led initialiseres
		statusCounter = 0;
		btnStatus = 0;
		led.initLED();
	
		// Giver tegn til at bilen kan køre
		startBil();

		// While loopet stoppe ved restart, carControl er færdig eller brugeren bruger quit
		while (btnStatus < 2 && statusCounter != -1 && quitBtn != -1) 
		{
			// Sørger for, at SW2 aktiverer algoritmen
			if (btnStatus == 1 && statusCounter == 0) 
				sensorStatus = 0;
			
			// carControl kaldes når interrupt sætter sensorStatus til sensorCounter
			if (sensorStatus == statusCounter && btnStatus == 1) 
			{	
				// carControl bliver kaldt til at udføre givende case
				// sensorStatus får en incrementeret værdi fra carControl, så næste stadie køres
				statusCounter = carControl(sensorStatus, &carMotor, &led);
			}
		}
		// Deinitialize - restart bil
		if (statusCounter == -1 || btnStatus > 1 || quitBtn == -1) {
			restartBil(&carMotor, &led);
			
			// terminere programmet
			if (quitBtn == -1)
				stopBil();	
		}			
	}
	return 0;
}