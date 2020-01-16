/*********************************************
* Projekt 1 - bil                       *
* Testprogram for LEDdriver         *
* Simon 22-11-2019                 *
**********************************************/
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include "light.h"

int main()
{
	// Class definitions
	Led frontLight; // PH5
	Led backLight; // PH4

	// initiering
	frontLight.initLED();
	
	while (1)
	{ 

		frontLight.frontLight(100);
		backLight.backLight(100);
		_delay_ms(500);
		frontLight.frontLight(0);
		backLight.backLight(20);
		
	}
	
}