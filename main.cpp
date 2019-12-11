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
Ved f�lgende kode, f�r main, bliver: 
Vores globale variabler (sensorCounter og btnStatus) bliver sat
Interrupt for knap (ISR(INT2_vect)) sat
Interrupt for sensor (ISR(INT4_vect) og ISR(INT5_vect)) sat
cli() bruges til at lukke alle interrupts - dette sker, s� kun 1 af sensorene vil blive p�virket af reflexbrikkerne
*/

volatile unsigned char btnStatus; // btnStatus bliver sat som en global variable
volatile unsigned char sensorCounter; // sensorCounter bliver sat som en global variable

// Interrupt for knappen (btnStatus) er sat, s� ved tryk p� knap, vil sensoren blive aktiveret eller resat
ISR(INT2_vect) {
	
	// btnStatus incrementeres
	btnStatus++;
	
}

// Interrupt for sensor (h�jre side) vil blive sat
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
		// Klarg�ring af porte
		DDRE |= 0b00110000; // Port E er sat til input
		PORTE |= 0b00110000; // Port E, ben 5 og 4, er sat til aktiv high
		DDRB = 0xFF; // Port B er sat til output
		PORTB = 0x00; // Port B er sat til 0, da LED er aktiv low
		
		// Interrupt enable og initiering
		EIMSK |= 0b00110100; // Aktivere INT2 (knap), INT4 (h�jre sensor) og INT5 (venstre sensor)
		EICRA = 0b00100000; // Falling  edge af INT2 interrrupt generer interrupt request
		EICRB = 0b00001111; // Rising edge af INT4 og INT5 genererer interrrupt request
		
		
		InitUART(9600, 8, 0);
		
		//Klarg�r motor
		Motor carMotor;
		
		//Klarg�r SOMO/lyd
		reset();
		playSource();
		setVol(30);
		
		
		//Klarg�r LED/lys
		ledDriver led;
		led.initLEDport();
		led.initTimer4();

	while (1)
	{	
		/*
		Alle variabler / funktioner / porte, vil blive sat, klar til start 
		*/
		signed char status = 0; // sensorStatus bestemmer bilens n�ste "case"
		btnStatus = 0; // KnapStatus styre om bilen skal g� i tomgang, k�re eller lave et reset
		sei(); // Aktivere global interrupt
		
		// Her skal alt deinitialiseres!
			
		
		/*
		Ved f�lgende while loop, k�re vore algoritme, der skal bestemme, hvilket stadie billen er i.
		*/ 
		
		// S�rger for, at bilen forbliver i loopet, indtil reset knappet er aktiveret (btnStatus g�r fra 1 til 2)
		while (btnStatus < 2) 
		{
			
			// S�rger for, at nr knappen aktivere algoritmen (btnStatus g�r fra 0 til 1) - sensorCounter bliver yderliger aktiveret
			if (btnStatus == 1 && status == 0) 
				sensorCounter = 0;
			
			// Algoritmen k�re n�ste trin n�r sensorCounter bliver lig med status
			if (sensorCounter == status && btnStatus == 1) 
			{
				
				// sensorStatus for en incrementeret v�rdi fra carControl, s� den er klar til n�ste stafige
				status = carControl(status, &carMotor, &led);

			}
			
			// N�r algoritmen har k�rt alle trin, vil bilen blive resat, og klarg�res til at k�re igen. 
			if (status == -1)
				break;
		}
		
	}
	
}

