/*
 * carControl.cpp
 *
 * Created: 22-11-2019 10:05:55
 *  Author: andre
 */ 

// SENSOR_DELAY sørger for, at kun en sensor aktiveres, ved forbikørsel af reflexbrik
#include "carControl.h"
#define SENSOR_DELAY 500

/*
Følgende funktion (carControl) bestemmer, udfra sensorCounter, hvad bilen skal gøre
status stiger per sensorCOounter, så algoritmen køre så sensorCounter, først aktiveres ved næste interrupt - ved n = -1, vil algoritmen blive resat
sei bruges til at åbne alle global interrupts, siden vores sensor interrupts bliver lukket ved sensor interrupt
*/

char carControl(char status, Motor* motor, ledDriver* led) {
	
	switch(status)
	{
		
		//Bil begynder at køre
		case 0: 
			PORTB = 0b00000001;
			
			motor->setDirection(1);
			motor->setSpeed(150);
			led->frontLight(80);
			led->backLight(30);
			
			status++;
			break;
		//reflexbrik 1 
		case 1:
			PORTB = 0b00000010;
			
			playTrack(1);
			
			_delay_ms(SENSOR_DELAY); 

			status++;
			break;
		case 2: //reflexbrik 2
			PORTB = 0b00000100;
			
			playTrack(1);
			motor->setSpeed(180);
			
			_delay_ms(SENSOR_DELAY); 

			status++;
			break;
		
		case 3: //reflexbrik 3
			PORTB = 0b00001000;
			
			playTrack(1);
			
			_delay_ms(SENSOR_DELAY); 

			status++;
			break;
		
		case 4: //reflexbrik 4
			PORTB = 0b00010000;
			
			playTrack(1);
			motor->setSpeed(255);
			
			_delay_ms(SENSOR_DELAY); 

			status++;
			break;
		case 5: //reflexbrik 5 - Siger lyd
			PORTB = 0b00100000;
			
			playTrack(1);
			motor->setSpeed(150);
			
			_delay_ms(SENSOR_DELAY); 
			status++;
			break;
		case 6: //reflexbrik 6 - Stop / bak
			PORTB = 0b01000000;
	
			playTrack(1);
			//Vend motor
			motor->setSpeed(0);
			_delay_ms(100);
			motor->setDirection(0);
			led->backLight(100);
			_delay_ms(100);
			//stop
			motor->setSpeed(180);
			_delay_ms(400);
			motor->setSpeed(0);
			_delay_ms(500);
			motor->setSpeed(180);
			
			_delay_ms(SENSOR_DELAY); 
			
			status++; 
			break;
			
		case 7: //reflexbrik 6 igen - Lyd
			PORTB = 0b10000000;
			
			playTrack(1);
			
			_delay_ms(SENSOR_DELAY); 
			
			status++;  
			break;
			
		case 8: //reflexbrik 5 igen - Køre frem igen
			PORTB = 0b10000001;
			
			playTrack(1);
			motor->setSpeed(0);
			_delay_ms(100);
			motor->setDirection(1);
			led->backLight(30);
			_delay_ms(100);
			motor->setSpeed(150);
			_delay_ms(500);
			motor->setSpeed(255);
			
			_delay_ms(SENSOR_DELAY); 

			status++;
			break;
			
		case 9: //reflexbrik 5 igen - Køre frem igen
				
			PORTB = 0b10000011;
			
			playTrack(1);
			_delay_ms(SENSOR_DELAY);
				
			status++;
			break;
		
		case 10: //reflexbrik 6 igen - siger lyd
			
			PORTB = 0b10000111;
			
			playTrack(1);
			_delay_ms(SENSOR_DELAY);
			
			status++;
			break;
		
		case 11: //reflexbrik 7 - Bil stopper
			PORTB = 0b10001111;
			
			playTrack(1);
			motor->setSpeed(0);

			status = -1;
			break;
		
	}
	
	return status;
		
}