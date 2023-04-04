#include <msp430.h> 
#include <Stepper.h>


/**
 * main.c
 */

void initGPIO();        //initialize GPIO pin for the motor and ultrasonic

void initTimer();       //initialize timer

void calibrate();       //circle the motor and get initial values

void search();          //search for the










int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	return 0;
}
