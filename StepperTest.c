#include <msp430.h>

#define HBRIDGE_PIN1 BIT4 // GPIO pin connected to H-bridge input 1
#define HBRIDGE_PIN2 BIT5 // GPIO pin connected to H-bridge input 2
#define HBRIDGE_PIN3 BIT6 // GPIO pin connected to H-bridge input 3
#define HBRIDGE_PIN4 BIT7 // GPIO pin connected to H-bridge input 4



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

int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= HBRIDGE_PIN1 | HBRIDGE_PIN2 | HBRIDGE_PIN3 | HBRIDGE_PIN4; // Set GPIO pins as outputs

    while (1) {
        // Take one step forward
        step_forward();
        __delay_cycles(1000);
        step_backward();
        __delay_cycles(1000);
    }

    return 0;
}
