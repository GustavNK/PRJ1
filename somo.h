/*========================================================================
FILENAME	: carControl.cpp
CREATED		: 22-11-2019 10:05:55
AUTHOR		: Andreas og Anders
DESCR.		: Methods for SOMO funktions
==========================================================================*/
/*
 * somo.h
 *
 * Created: 06-12-2019 11:09:37
 *  Author: Rasmus
 */ 


#ifndef SOMO_H_
#define SOMO_H_

#define F_CPU 16000000
#include <util/delay.h>

void playTrack(unsigned char tracknr); // Plays track between 1-3
void reset(); // Resets the SOMO
void setVol(unsigned char vol); // Sets the volume between 0-30
void playSource(); // sets source to SD-card

#endif /* SOMO_H_ */