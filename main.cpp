/*
 * Projekt1IKT.cpp
 *
 * Created: 28-10-2019 11:48:57
 * Author : Rasmus
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light.h"
#include "carControl.h"
#include "motor.h"
#include "uart.h"
#include "somo.h"
#include "startRestartStop.h"

/*
Ved f�lgende kode, f�r main, bliver: 
Vores globale variabler (sensorCounter og btnStatus) bliver sat
Interrupt for knap (ISR(INT2_vect)) sat
Interrupt for sensor (ISR(INT4_vect) og ISR(INT5_vect)) sat
cli() bruges til at lukke alle interrupts - dette sker, s� kun 1 af sensorene vil blive p�virket af reflexbrikkerne
*/

// S�tter globale variabler, til brug i interrupts
volatile unsigned char btnStatus; 
volatile signed char quitBtn;
volatile unsigned char sensorStatus;
volatile signed char statusCounter;

// Interrupt for knappen (btnStatus) er sat, s� ved tryk p� knap, vil sensoren blive aktiveret eller resat
ISR(INT2_vect) {
	
	// btnStatus incrementeres
	btnStatus++;
}

// Interrupt for knappen (btnStatus) er sat, s� ved tryk p� knap, vil koden afslutte
ISR(INT3_vect) {
	
	// btnStatus incrementeres
	quitBtn = -1;
	
}

// Interrupt for sensor (h�jre side) vil blive sat
ISR(INT4_vect) {
	// sensorStatus s�ttes til statusCounter, for at s�tte n�ste case i carControl, til at k�re ved INT4_vect (h�jre)
	sensorStatus = statusCounter;
}

// Interrupt for sensor (venstre side) vil blive sat
ISR(INT5_vect) {
	
	// sensorStatus s�ttes til statusCounter, for at s�tte n�ste case i carControl, til at k�re ved INT4_vect (venstre)
	sensorStatus = statusCounter;	
}

int main(void)
{	
	// Klarg�ring af porte
	DDRE &= 0b11001111; // Port E, pin 4 og 5 er sat til input
	DDRB = 0xFF; // Port B er sat til output
	
	// Interrupt enable og initiering
	EIMSK |= 0b00111100; // Aktivere INT2 (knap), INT4 (h�jre sensor) og INT5 (venstre sensor)
	EICRA = 0b10100000; // Falling  edge af INT2 interrrupt generer interrupt request
	EICRB = 0b00001111; // Rising edge af INT4 og INT5 genererer interrrupt request
	sei(); // Aktivere global interrupt
	
	//Klarg�r motor
	Motor carMotor;
	
	//Klarg�r SOMO/lyd
	InitUART(9600, 8, 0);	
	PORTB = 170; //10101010
	reset();				
	PORTB = 0;
	playSource();			
	PORTB = 85; //01010101
	setVol(30);				
	PORTB = 0;
	_delay_ms(150);
	
	//Klarg�r LED/lys
	Led led;

	while(quitBtn != -1)
	{	
		//Alle variabler / funktioner / porte, vil blive sat klar til start 
		statusCounter = 0; // statusCounter bestemmer bilens n�ste "case"
		btnStatus = 0; // KnapStatus styre om bilen skal g� i tomgang, k�re eller lave et reset
		led.initLED();
		
		startBil();
		
		/*
		Ved f�lgende while loop, k�re vore algoritme, der skal bestemme, hvilket stadie bilen er i.
		*/ 
		
		// S�rger for, at koden forbliver i loopet, indtil reset knappet er aktiveret (btnStatus g�r fra 1 til 2) - med mindre alle cases er k�rt i carControl
		while (btnStatus < 2 && statusCounter != -1 && quitBtn != -1) 
		{
			
			// S�rger for, at nr knappen aktivere algoritmen (btnStatus g�r fra 0 til 1) - sensorCounter bliver yderliger aktiveret
			if (btnStatus == 1 && statusCounter == 0) 
				sensorStatus = 0;
			
			// Algoritmen k�re n�ste trin n�r sensorCounter bliver lig med status
			if (sensorStatus == statusCounter && btnStatus == 1) 
			{
				// sensorStatus for en incrementeret v�rdi fra carControl, s� den er klar til n�ste stadige
				statusCounter = carControl(sensorStatus, &carMotor, &led);
			}
			
		}
		
		// Deinitialize - restart bil
		if (statusCounter == -1 || btnStatus > 1 || quitBtn == -1) {
			restartBil(&carMotor, &led);
			
			// stop bil helt
			if (quitBtn == -1)
				stop();
		}			
		
	}
	return 0;
}

