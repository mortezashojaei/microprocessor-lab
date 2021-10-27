/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Alphabets
Version : 
Date    : 12/28/2020
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
#include <alcd.h>
#include <stdio.h>

// Declare your global variables here
char Alphabets[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
int counter;
int i;
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{

    ++counter;
    
    if(counter == 500){
        
        lcd_putchar(Alphabets[i]);
        
        if(i == 25){
        TCCR0=0x00;
        TIMSK=0x00;
        }      
        
        counter = 0;
        i++;
    }
}


void main(void)
{
// Declare your local variables here

counter = 0;
i = 0;
TCCR0=0x01;
TCNT0=0x00;
OCR0=0x00;
TIMSK=0x01;
lcd_init(20);
lcd_gotoxy(0,0);
#asm("sei")



while (1)
      {
      // Place your code here

      }
}
