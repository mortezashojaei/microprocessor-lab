/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : LCDHelloWorld
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

// Declare your global variables here

void main(void)
{
    
     lcd_init(20);
     lcd_gotoxy(0,0);
     lcd_putsf("Hello world");

while (1)
      {
      // Place your code here
     
      }
}
