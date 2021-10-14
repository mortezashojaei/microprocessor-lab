#include <mega16.h>
#include <delay.h>
// Declare your global variables here

void main(void)
{
    DDRA = 0x00;
    DDRB = 0xFF;

while (1)
      {
      // Place your code here
      
      if(PINA.0 == 1){  
      
        for(int i = 1; i <= 2^7; i*2){
            PORTB = i;
            delay_ms(50);
        }
        
        for(int j = 128; i >= 1; i/2){
            PORTB = i;
            delay_ms(50);
        }
       }
      }
}
