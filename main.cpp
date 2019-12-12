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

/*
Ved følgende kode, før main, bliver: 
Vores globale variabler (sensorCounter og btnStatus) bliver sat
Interrupt for knap (ISR(INT2_vect)) sat
Interrupt for sensor (ISR(INT4_vect) og ISR(INT5_vect)) sat
cli() bruges til at lukke alle interrupts - dette sker, så kun 1 af sensorene vil blive påvirket af reflexbrikkerne
*/

volatile unsigned char btnStatus; // btnStatus bliver sat som en global variable
volatile unsigned char sensorStatus; // sensorCounter bliver sat som en global variable
volatile signed char statusCounter; // statusCounter bliver sat som global variable

// Interrupt for knappen (btnStatus) er sat, så ved tryk på knap, vil sensoren blive aktiveret eller resat
ISR(INT2_vect) {
	
	// btnStatus incrementeres
	btnStatus++;
	
}

// Interrupt for sensor (højre side) vil blive sat
ISR(INT4_vect) {
	
	sensorStatus = statusCounter;
	
}

// Interrupt for sensor (venstre side) vil blive sat
ISR(INT5_vect) {
	
	sensorStatus = statusCounter;
	
}

int main(void)
{	
		// Klargøring af porte
		DDRE &= 0b11001111; // Port E er sat til input
		DDRB = 0xFF; // Port B er sat til output
		PORTB = 0x00; // Port B er sat til 0, da LED er aktiv low
		
		// Interrupt enable og initiering
		EIMSK |= 0b00110100; // Aktivere INT2 (knap), INT4 (højre sensor) og INT5 (venstre sensor)
		EICRA = 0b00100000; // Falling  edge af INT2 interrrupt generer interrupt request
		EICRB = 0b00001111; // Rising edge af INT4 og INT5 genererer interrrupt request
		sei(); // Aktivere global interrupt
		
		InitUART(9600, 8, 0);
		
		//Klargør motor
		Motor carMotor;
		
		//Klargør SOMO/lyd
		reset();
		playSource();
		setVol(30);
		//Klargør LED/lys
		ledDriver led;
		led.initLEDport();
		led.initTimer4();

	while (1)
	{	
		/*
		Alle variabler / funktioner / porte, vil blive sat, klar til start 
		*/
		statusCounter = 0; // statusCounter bestemmer bilens næste "case"
		btnStatus = 0; // KnapStatus styre om bilen skal gå i tomgang, køre eller lave et reset
		PORTB = 0b00000100;
		
		// Her skal alt deinitialiseres!
			
		
		/*
		Ved følgende while loop, køre vore algoritme, der skal bestemme, hvilket stadie billen er i.
		*/ 
		
		// Sørger for, at bilen forbliver i loopet, indtil reset knappet er aktiveret (btnStatus går fra 1 til 2)
		while (btnStatus < 2) 
		{
			
			// Sørger for, at nr knappen aktivere algoritmen (btnStatus går fra 0 til 1) - sensorCounter bliver yderliger aktiveret
			if (btnStatus == 1 && statusCounter == 0) 
				sensorStatus = 0;
			
			// Algoritmen køre næste trin når sensorCounter bliver lig med status
			if (sensorStatus == statusCounter && btnStatus == 1) 
			{
				
				// sensorStatus for en incrementeret værdi fra carControl, så den er klar til næste stafige
				statusCounter = carControl(statusCounter, &carMotor, &led);

			}
			
			// Når algoritmen har kørt alle trin, vil bilen blive resat, og klargøres til at køre igen. 
			if (statusCounter == -1)
				break;
		}
		//Deinitialize
		led.backLight(0);
		led.frontLight(0);
		reset();  //Reset sound
PORTB = 0b00000100;	}
	
}

