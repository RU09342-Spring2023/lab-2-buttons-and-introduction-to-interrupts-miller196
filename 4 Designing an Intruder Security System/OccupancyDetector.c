*
 *  Created on: Feb 6, 2023
 *      Author: David Miller
 */
#include <msp430.h>
#include <time.h>
#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2
int main(void)
{
        P1OUT &= ~BIT0;
        P1DIR |=BIT0;
        PM5CTL0 &=~LOCKLPM5;
        WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
        P6OUT &= ~BIT6;
        P6DIR |=BIT6;
        PM5CTL0 &=~LOCKLPM5;
        P4REN |= BIT1;
        P4OUT |=BIT1;
        P6OUT ^=BIT6; //Initializes all of the LED and timers

char state = WARNING_STATE;
int y = 0; //initialize y as zero for a counter in the case statement
int x = 0; // same for x
while(1)
{
  switch (state) {
    case WARNING_STATE: //warning state which blinks red LED for 10 seconds
    {
        while (!(P4IN & BIT1))
        {
            P1OUT^=BIT0;
            P6OUT &= ~BIT6;
                if (x > 19) //Count if statement that runs when the loop cycles 20 times
                {
                y = 1;
                break;
                }
            x++;
            __delay_cycles(500000); //delay 0.5 seconds
        }
    }
    case ALERT_STATE: // alert state that holds a constant LED while the button is still being held
    { // as soon as the button is released the cycles resets to the default case loop
        while ( y > 0)
            {
            P1OUT|=BIT0;
            P6OUT &= ~BIT6;
                   if(!(P4IN & BIT1)==0x00)
                    {
                    __delay_cycles(500000);
                    break;
                    }
            }
    }
    default : //ARMED_STATE cycles the LED green in 3 second intervals and resets x to zero so that it can count through the warning state
    {
        while (1)
            {
            x=0;
            P6OUT^=BIT6;
            P1OUT &= ~BIT0;
            __delay_cycles(3000000);
                if (!(P4IN & BIT1))
                    {
            break;
        }
  }
  }

}
}
}
