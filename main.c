#include "msp430g2553.h"

int a = BIT0;		//Segment A on P1.0
int b = BIT1;		//Segment B on P1.1
int c = BIT2;		//Segment C on P1.2
int d = BIT3;		//Segment D on P1.3
int e = BIT4;		//Segment E on P1.4
int f = BIT5;		//Segment F on P1.5
int g = BIT6;		//Segment G on P1.6

// Digit Variables - O is the ones digit, T is the tens digit
const int O0 = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT6;
const int O1 = 0x06;
const int O2 = BIT0 + BIT1 + BIT3 + BIT4 + BIT5;
const int O3 = BIT0 + BIT1 + BIT2 + BIT3 + BIT5;
const int O4 = BIT1 + BIT2 + BIT5 + BIT6;
const int O5 = BIT0 + BIT2 + BIT3 + BIT5 + BIT6;
const int O6 = BIT0 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6;
const int O7 = BIT0 + BIT1 + BIT2;
const int O8 = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6;
const int O9 = BIT0 + BIT1 + BIT2 + BIT3 + BIT5 + BIT6;

void delay(void);

void main(void)
{

  unsigned int timeperiod;						//Will be used to change timing on digits

  WDTCTL = WDTPW + WDTHOLD;						// Stop watchdog timer

  P1DIR |= a;								// Set P1.0 to output direction
  P1DIR |= b;								// Set P1.1 to output direction
  P1DIR |= c;								// Set P1.2 to output direction
  P1DIR |= d;								// Set P1.3 to output direction
  P1DIR |= e;								// Set P1.4 to output direction
  P1DIR |= f;								// Set P1.5 to output direction
  P1DIR |= g;								// Set P1.6 to output direction



	for (;;) {

	    P1OUT &= ~(a + b + c + d + e + f + g);	//Makes sure all segments are off

        for (timeperiod=0; timeperiod<1; timeperiod++) 		        //Number 0
        {
            P1OUT |= O0;
            delay();
            P1OUT &= ~(a + b + c + d + e + g);
        }


        for (timeperiod=0; timeperiod<1; timeperiod++)                 //Number 1
        {
            P1OUT |= O1;
            delay();
            P1OUT &= ~(b + c);
        }

	for (timeperiod=0; timeperiod<1; timeperiod++)                 //Number 2
	{
            P1OUT |= O2;
            delay();
            P1OUT &= ~(a + b + d + e + f);
        }

	for (timeperiod=0; timeperiod<1; timeperiod++)                 //Number 3
	{
            P1OUT |= O3;
            delay();
            P1OUT &= ~(a + b + c + d + f);
	}

	for (timeperiod=0; timeperiod<1; timeperiod++)                 //Number 4
	{
            P1OUT |= O4;
            delay();
            P1OUT &= ~(b + c + f + g);
	}

	for (timeperiod=0; timeperiod<1; timeperiod++)                 //Number 5
	{
            P1OUT |= O5;
            delay();
            P1OUT &= ~(a + c + d + f + g);
        }

	for (timeperiod=0; timeperiod<1; timeperiod++)                 //Number 6
	{
            P1OUT |= O6;
            delay();
            P1OUT &= ~(a + c + d + e + f + g);
        }

        for (timeperiod=0; timeperiod<1; timeperiod++)                 //Number 7
        {
            P1OUT |= O7;
            delay();
            P1OUT &= ~(a + b +  c);
        }

	for (timeperiod=0; timeperiod<1; timeperiod++)                 //Number 8
	{
            P1OUT |= O8;
            delay();
            P1OUT &= ~(a + b + c + d + e + f + g);
        }

	for (timeperiod=0; timeperiod<1; timeperiod++)                 //Number 9
	{
            P1OUT |= O9;
            delay();
            P1OUT &= ~(a + b + c + d + f + g);
        }

    }
} // main

void delay(void) {

    BCSCTL3 |= XCAP_3;					// xtal has 12.5 pF caps
    TACCR0 = 16383*2;					// f_xtal / 2 - 1 gives 2 Hz *2 = 1 second
    TACTL = TASSEL_1 + MC_1 + TACLR;	                // ACLK + Up Mode + Clear timer
    TACTL &= ~BIT0;					// reset TAIFG
    while ((TACTL & BIT0) == 0) { 		        // wait for timer to reach TACCR0
    }
} // delay
