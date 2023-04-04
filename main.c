#include <msp430.h> 
#include "Stepper.h"


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

            StepperMotor.step(1);
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




}




void initTimer() {


}




int pulse() {





}
}
