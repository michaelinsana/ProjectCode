#include <msp430.h> 

#define HBRIDGE_PIN1 BIT4 // GPIO pin connected to H-bridge input 1
#define HBRIDGE_PIN2 BIT5 // GPIO pin connected to H-bridge input 2
#define HBRIDGE_PIN3 BIT6 // GPIO pin connected to H-bridge input 3
#define HBRIDGE_PIN4 BIT7 // GPIO pin connected to H-bridge input 4



/**
 * main.c
 */

void initGPIO();        //initialize GPIO pin for the motor and ultrasonic

void initTimer();       //initialize timer

void calibrate();       //circle the motor and get initial values

int pulse();

int mode = 0;   /*    0 = search
                      1 = focus   */

const int MAX_DIST = 300;



int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	             // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                    // Disable the GPIO power-on default high-impedance mode

    //calibrate();              Use after Proof of Concept


    while (1) {

        switch (mode) {
        case 0:                                     //search

            step_forward();
            int dist = pulse();

            if (dist < MAX_DIST)
                mode = 1;

            else
                mode = 0;

            break;

        case 1:                                     //focus



            if (dist < MAX_DIST)


            break;

        }

   }
	
	return 0;

}



void initGPIO() {        //initialize GPIO pin for the motor and ultrasonic

	P1DIR |= HBRIDGE_PIN1 | HBRIDGE_PIN2 | HBRIDGE_PIN3 | HBRIDGE_PIN4; // Set GPIO pins as outputs
	

	// Set TRIG_PIN as an output and ECHO_PIN as an input
   	 P1DIR |= TRIG_PIN;
   	 P1DIR &= ~ECHO_PIN;

    	// Configure the Timer_B0 to count up to 65535 with a clock source of SMCLK
   	 TB0CTL |= TBSSEL_2 ;
}




void initTimer() {


}

void step_forward() {
    P1OUT |= HBRIDGE_PIN1; // Set input 1
    P1OUT &= ~HBRIDGE_PIN2; // Clear input 2
    P1OUT |= HBRIDGE_PIN3; // Set input 3
    P1OUT &= ~HBRIDGE_PIN4; // Clear input 4
}

void step_backward() {
    P1OUT &= ~HBRIDGE_PIN1; // Clear input 1
    P1OUT |= HBRIDGE_PIN2; // Set input 2
    P1OUT &= ~HBRIDGE_PIN3; // Clear input 3
    P1OUT |= HBRIDGE_PIN4; // Set input 4
}




int pulse() {

    P1OUT |= TRIG_PIN;
    __delay_cycles(10);
    P1OUT &= ~TRIG_PIN;

    // Reset the timer and start counting
    TB0CTL |= TBCLR | MC_2;

    // Wait for the echo pin to go high
    while ((P1IN & ECHO_PIN) == 0);

    // Wait for the echo pin to go low
    while (P1IN & ECHO_PIN);

    // Stop the timer and calculate the time
    TB0CTL &= ~MC_2;
    int time_us = TB0R;

    return time_us/58;


}

