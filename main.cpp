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
volatile unsigned char sensorCounter; // sensorCounter bliver sat som en global variable

// Interrupt for knappen (btnStatus) er sat, så ved tryk på knap, vil sensoren blive aktiveret eller resat
ISR(INT2_vect) {
	
	// btnStatus incrementeres
	btnStatus++;
	
}

// Interrupt for sensor (højre side) vil blive sat
ISR(INT4_vect) {
	
	// sensorCounter incrementeres
	sensorCounter++;
	
	// Alle interrupts lukkes
	cli();
	
}

// Interrupt for sensor (venstre side) vil blive sat
ISR(INT5_vect) {
	
	// sensorCounter incrementeres
	sensorCounter++;
	
	// Alle interrupts lukkes
	cli();
	
}

int main(void)
{	
		// Klargøring af porte
		DDRE |= 0b00110000; // Port E er sat til input
		PORTE |= 0b00110000; // Port E, ben 5 og 4, er sat til aktiv high
		DDRB = 0xFF; // Port B er sat til output
		PORTB = 0x00; // Port B er sat til 0, da LED er aktiv low
		
		// Interrupt enable og initiering
		EIMSK |= 0b00110100; // Aktivere INT2 (knap), INT4 (højre sensor) og INT5 (venstre sensor)
		EICRA = 0b00100000; // Falling  edge af INT2 interrrupt generer interrupt request
		EICRB = 0b00001111; // Rising edge af INT4 og INT5 genererer interrrupt request
		
		
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
		signed char status = 0; // sensorStatus bestemmer bilens næste "case"
		btnStatus = 0; // KnapStatus styre om bilen skal gå i tomgang, køre eller lave et reset
		sei(); // Aktivere global interrupt
		
		// Her skal alt deinitialiseres!
			
		
		/*
		Ved følgende while loop, køre vore algoritme, der skal bestemme, hvilket stadie billen er i.
		*/ 
		
		// Sørger for, at bilen forbliver i loopet, indtil reset knappet er aktiveret (btnStatus går fra 1 til 2)
		while (btnStatus < 2) 
		{
			
			// Sørger for, at nr knappen aktivere algoritmen (btnStatus går fra 0 til 1) - sensorCounter bliver yderliger aktiveret
			if (btnStatus == 1 && status == 0) 
				sensorCounter = 0;
			
			// Algoritmen køre næste trin når sensorCounter bliver lig med status
			if (sensorCounter == status && btnStatus == 1) 
			{
				
				// sensorStatus for en incrementeret værdi fra carControl, så den er klar til næste stafige
				status = carControl(status, &carMotor, &led);

			}
			
			// Når algoritmen har kørt alle trin, vil bilen blive resat, og klargøres til at køre igen. 
			if (status == -1)
				break;
		}
		
	}
	
}

