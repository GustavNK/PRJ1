/*
 * carControl.cpp
 *
 * Created: 22-11-2019 10:05:55
 *  Author: andre
 */ 

// SENSOR_DELAY sørger for, at kun en sensor aktiveres, ved forbikørsel af reflexbrik
#include "carControl.h"
#define SENSOR_DELAY 500
#define START_LYD 1
#define REFLEKS_LYD1 2
#define REFLEKS_LYD2 3
#define SLUT_LYD 4
/*
Følgende funktion (carControl) bestemmer, ved at main.cpp sender sensorStatus vidre, som bestemmer hvilken case der skal køres
Algoritmen for sensorCounter til at incrementere efter case. Ved næste interrupt i main.cpp, vil carControl blive aktiveret, nu med den nye sensorStatus værdi.
*/

char carControl(char status, Motor* motor, Led* led) {
	
	LEDCounter(status);
	
	switch(status)
	{
		
		//Bil begynder at køre
		case 0: 
			
			playTrack(START_LYD);
			motor->setDirection(1);
			motor->setSpeed(180);
			led->frontLight(100);
			led->backLight(30);
			break;
			
		case 1: //reflexbrik 1
			
			playTrack(REFLEKS_LYD1);
			break;
			
		case 2: //reflexbrik 2
			
			playTrack(REFLEKS_LYD2);
			//motor->setSpeed(180);
			break;
		
		case 3: //reflexbrik 3
			
			playTrack(REFLEKS_LYD1);
			break;
		
		case 4: //reflexbrik 4
			
			playTrack(REFLEKS_LYD2);
			//motor->setSpeed(255);
			break;
			
		case 5: //reflexbrik 5 - Siger lyd
			
			playTrack(REFLEKS_LYD1);
			//motor->setSpeed(150);
			break;
			
		case 6: //reflexbrik 6 - Stop / bak
	
			playTrack(REFLEKS_LYD2);
			//Vend motor
			motor->setSpeed(0);
			_delay_ms(100);
			motor->setDirection(0);
			led->backLight(100);
			_delay_ms(100);
			//stop
			motor->setSpeed(180);
			_delay_ms(200);
			motor->setSpeed(0);
			_delay_ms(800);
			motor->setSpeed(200);
			break;
			
		case 7: //reflexbrik 6 igen - Lyd
			
			playTrack(REFLEKS_LYD1);
			break;
			
		case 8: //reflexbrik 5 igen - Køre frem igen
			
			playTrack(REFLEKS_LYD2);
			motor->setSpeed(0);
			_delay_ms(100);
			motor->setDirection(1);
			led->backLight(30);
			_delay_ms(100);
			motor->setSpeed(150);
			_delay_ms(200);
			break;
			
		case 9: //reflexbrik 5 igen - Køre frem igen
				
			motor->setSpeed(255);
			playTrack(REFLEKS_LYD1);
			break;
		
		case 10: //reflexbrik 6 igen - siger lyd
						
			playTrack(REFLEKS_LYD2);
			break;
		
		case 11: //reflexbrik 7 - Bil stopper
			
			playTrack(SLUT_LYD);
			motor->setSpeed(0);
			break;
		
	}
	
	_delay_ms(SENSOR_DELAY);
	
	if (status == 12)
		status = -1;
		
	else
		status++;
		
	return status;
		
}