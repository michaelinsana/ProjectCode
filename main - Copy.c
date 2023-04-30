
#include <msp430.h>
#include <stdint.h>
#include <stdio.h>


void init_HC_SR04(void);
int measure_distance(void);

#define MCLK_FREQ_MHZ 8                     // MCLK = 8MHz

#define TRIG_PIN    BIT4    // P1.4
#define ECHO_PIN    BIT5    // P1.5

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                // Stop watchdog timer


  PM5CTL0 &= ~LOCKLPM5;                    // Disable the GPIO power-on default high-impedance mode
                                           // to activate 1previously configured port settings
  init_HC_SR04();



  while(1) {

      int distance = measure_distance();   // Measure the distance

  }

}



void init_HC_SR04(void) {
    // Set TRIG_PIN as an output and ECHO_PIN as an input
    P1DIR |= TRIG_PIN;
    P1DIR &= ~ECHO_PIN;

    // Configure the Timer_B0 to count up to 65535 with a clock source of SMCLK
    TB0CTL |= TBSSEL_2 ;


}

int measure_distance(void) {
    // Send a pulse to the HC-SR04 trigger pin
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

    return time_us;
}



