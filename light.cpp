/*========================================================================
FILENAME	: light.cpp
CREATED		: 28-10-2019 12:08:01
AUTHOR		: Simon og Shyn
DESCR.		: Styrer hvor kraftigt lyset skal lyse
				1023 = TOP af PWM 10bit
				Hvis ORC1n = 1023 er LED slukket
				Hvis ORC1n = meget lille tal f.eks. 0.1 er det tændt
==========================================================================*/
#include <avr/io.h>
#define MAX_LED_NR 7
#include "light.h"

Led::Led(){
		DDRH |= 0b00110000;  // Port b direction output
		PORTH &= 0b11001111;   // Begin with turning off all pins
		
		//INIT timer4
		TCCR4A = 0b00111111;  // Fast PWM mode 10 bit, Enable B+C systemerne (OCR4A,B og C)
		// On compare match set OUTPUT til HIGH
		TCCR4B = 0b00001001;  // no prescaler Fast PWM
		TCCR4C = 0b00000000; // Normal port operation
		//Default 0% duty cyle / Full off
		OCR4B = 1023;
		OCR4C = 1023;
}

void Led::initLED()
{
	DDRH |= 0b00110000;  // Port b direction output
	PORTH &= 0b11001111;   // Begin with turning off all pins
	
	//INIT timer4
	TCCR4A = 0b00111111;  // Fast PWM mode 10 bit, Enable B+C systemerne (OCR4A,B og C)
	// On compare match set OUTPUT til HIGH
	TCCR4B = 0b00001001;  // no prescaler Fast PWM
	TCCR4C = 0b00000000; // Normal port operation
	//Default 0% duty cyle / Full off
	OCR4B = 1023;
	OCR4C = 1023;
}

void Led::backLight(unsigned char duty_cycle){
	// PH4
	if (duty_cycle >= 1 && duty_cycle <= 100)
	{
		OCR4B = (1023/100)*(100-duty_cycle);   // Dutycycle * TOP = OCRn
	}

	else if (duty_cycle == 0)
	OCR4B = 1023;
}

void Led::frontLight(unsigned char duty_cycle)
{
	// PH5
	if (duty_cycle >= 1 && duty_cycle <= 100)
	{
		OCR4C = (1023/100)*(100-duty_cycle);  ;  // Dutycycle * TOP = OCRn
	}
	
	else if (duty_cycle == 0)
		OCR4C = 1023;
}