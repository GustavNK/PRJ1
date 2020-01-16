#include "somo.h"
#include "uart.h"
#include <utilities/delay>
#define F_CPU 16000000

int main(void){
	/* Replace with your application code*/
	initUART(9600,8,0); // 9600 baudrate, 8 bit, no interrupt
	reset(); // resets SOMO-II
	playSource(); // Plays from SD-card
	setVol(30); // Volume to max (0x1E)
	playTrack(1); // plays first track
	_delay_ms(5000); // 5 sec delay to hear the sound
	playTrack(2); // plays second track
	_delay_ms(5000);
	playTrack(3); // plays third track
	_delay_ms(5000);
	playTrack(4); // plays fourth track
	_delay_ms(5000);
	while(1){}
}