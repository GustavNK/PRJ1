/*
 * PRJ1.cpp
 *
 * Created: 30-11-2019 23:22:16
 * Author : Gustav
 */ 

#include <avr/io.h>
#include "motor.h"

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		Motor motor(2,2);
		int x = 1;
		motor.setDirection(x);
    }
}

