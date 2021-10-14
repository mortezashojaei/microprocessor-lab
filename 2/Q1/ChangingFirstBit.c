/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : ChangingFirstBit
Version : 
Date    : 12/12/2020
Author  : 
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 12.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
static unsigned int time_count; 
interrupt [TIM0_OVF] void timer0_ovf_isr(void) 
{
    TCNT0 = 31; 
    ++time_count; 
    if (time_count == 3332)
  {
        PORTC.0 = (PORTC.0 ^ 1); 
        time_count = 0; 
     }
}
void main (void) {
    DDRC = 0x01; 
    TCCR0=0x02;
    TCNT0=31;
   

    TIMSK=0x01;

    #asm(“sei")

    while(1) 
    {
        ; /*do nothing in here */
    }
}

