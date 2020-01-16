/*======================================================================== 
FILENAME	: carControl.cpp 
CREATED		: 22-11-2019 10:05:55 
AUTHOR		: Andreas og Anders
DESCR.		: Styrer hvad der skal ske med motor, lyd og lys, hver gang en sensor mødes på banen
==========================================================================*/
#include "carControl.h"
#define SENSOR_DELAY 500
#define START_LYD 1
#define REFLEKS_LYD1 2
#define REFLEKS_LYD2 3
#define SLUT_LYD 4

char carControl(char status, Motor* motor, Led* led) {
	
	LEDCounter(status);
	
	switch(status)
	{
		//Bil begynder at køre
		case 0: 
			
			playTrack(START_LYD);
			_delay_ms(2100);
			motor->setDirection(1);
			motor->setSpeed(140);
			led->frontLight(100);
			led->backLight(15);
			break;
			
		case 1: //reflexbrik 1
			
			playTrack(REFLEKS_LYD1);
			motor->setSpeed(220);
			break;
		
		case 2: //reflexbrik 2 - Before Hill
			
			playTrack(REFLEKS_LYD2);
			motor->setSpeed(240);
			break;
		
		case 3: //reflexbrik 3 - On hill
			
			playTrack(REFLEKS_LYD1);
			motor->setSpeed(130);
			break;
		
		case 4: //reflexbrik 4 - After hill
			
			playTrack(REFLEKS_LYD2);
			motor->setSpeed(255);
			break;
			
		case 5: //reflexbrik 5
			
			playTrack(REFLEKS_LYD1);
			motor->setSpeed(80);
			break;
			
		case 6: //reflexbrik 6 - Stop / bak
	
			playTrack(REFLEKS_LYD2);
			//Vend motor
			motor->setSpeed(0);
			_delay_ms(1600);
			motor->setDirection(0);
			led->backLight(70);
			//stop
			motor->setSpeed(150);
			break;
			
		case 7: //reflexbrik 6 igen
			
			playTrack(REFLEKS_LYD1);
			motor->setSpeed(80);
			break;
			
		case 8: //reflexbrik 5 igen - Køre frem igen
			
			playTrack(REFLEKS_LYD2);
			motor->setSpeed(60);
			_delay_ms(200);
			motor->setSpeed(40);
			_delay_ms(200);
			motor->setSpeed(0);
			_delay_ms(400);
			motor->setDirection(1);
			led->backLight(15);
			motor->setSpeed(100);
			break;
			
		case 9: //reflexbrik 5 igen
		
			motor->setSpeed(200);
			playTrack(REFLEKS_LYD1);
			break;
		
		case 10: //reflexbrik 6 igen
					
			playTrack(REFLEKS_LYD2);
			motor->setSpeed(220);
			break;
		
		case 11: //reflexbrik 7 - Bil stopper

			playTrack(SLUT_LYD);
			motor->setSpeed(0);
			break;
	}
	
	_delay_ms(SENSOR_DELAY);		//sensor aktiveres kun, ved forbikørsel af reflexbrik
	
	if (status == 11) {
		status = -1;
		_delay_ms(7500);
	}
		
	else
		status++;

	return status;
		
}