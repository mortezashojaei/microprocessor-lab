
#include <io.h>   
#include <delay.h> 

int i = 0;
int motor[] = {0x06, 0x03, 0x09, 0x0c};

interrupt[TIM0_OVF] void tim0(void) {

    if(i > 3) i = 0;
       
    PORTA = motor[i++];
    TCNT0 = 215;
}

void main(void)
{
    DDRA = 0x0f;
    PORTA = 0x00;
    DDRC.2=0;
    PORTC.2=1;
    #asm("sei")
    TCCR0 = 0x05;
    
    while (1)
    {
        if (PINC.2==0)
        {   
            TCNT0 = 215;
            TIMSK = 0x01;
        }
    }
}