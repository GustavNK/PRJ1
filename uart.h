/****************************************
* "uart.h":                             *
* Header file for Mega2560 UART driver. *
* Using UART 0.                         *
* Henning Hargaard, 5/4 2019            *
* Redigeret til brug i PRJ1: Rasmus		*
*****************************************/ 
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char Rx_int);
unsigned char CharReady();
char ReadChar();
void SendChar(char Tegn);
void SendString(char* Streng);
void SendInteger(int Tal);