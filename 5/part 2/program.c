#include <mega16.h>

int T1[4] = {1, 0, 0, 1};
int T2[4] = {1, 0, 1, 0};
int T3[4] = {0, 1, 1, 0};
int T4[4] = {0, 1, 0, 1};
int buttonPressed;
int num = 1;
int delay_ms = -1;

interrupt [TIM0_OVF] void timer0_ovf_isr(void){
    TCNT0 = 0x0C;

    if(buttonPressed == 1){
      delay_ms++;
      if(delay_ms  ==  0){
        switch(num){
          case 1:
            PORTA.0 = T1[0];  
            PORTA.1 = T1[1];
            PORTA.2 = T1[2];
            PORTA.3 = T1[3];
            break;
          case 2:
            PORTA.0 = T2[0];  
            PORTA.1 = T2[1];
            PORTA.2 = T2[2];
            PORTA.3 = T2[3];
            break;     
          case 3:
            PORTA.0 = T3[0];  
            PORTA.1 = T3[1];
            PORTA.2 = T3[2];
            PORTA.3 = T3[3];
            break;     
          case 4:
            PORTA.0 = T4[0];  
            PORTA.1 = T4[1];
            PORTA.2 = T4[2];
            PORTA.3 = T4[3];
            break;
          default:
            break;
        }          
      }
     
      if(delay_ms>5 && delay_ms<=10) {
        PORTA = 0x00;
      }  
        
      if(delay_ms == 10){
        delay_ms = -1;  
        num++;
        if(num == 5){
          num = 1;
          buttonPressed = 0;
        }
      } 
    }
}

void main(void){   
  buttonPressed=0;
    
  DDRC = 0x00;   
  PINC = 0x04;  
       
  DDRA = 0xFF;  
  PORTA = 0x00;

  TCCR0=0x04;
  TCNT0=0x0C;
  
  TIMSK=0x01;

  #asm("sei")

  while (1){
    if(buttonPressed == 0 && PINC == 0x00){
      buttonPressed = 1; 
      delay_ms = -1;
    }
  }
}