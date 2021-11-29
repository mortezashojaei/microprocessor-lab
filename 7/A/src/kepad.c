#include "keypad.h"
#include <avr/io.h>
#include <util/delay.h>

void KeyPad_init()
{
    KEY_DDR=0x0f;
	KEY_PORT=0xff;
}

uint8_t Read_keyPad(void)
{
    while(1)
    {
        KEY_PORT|=0x0f;
        KEY_PORT&=~0x01;
        if(! (KEY_PIN & 0x10) ) {_delay_ms(300); return 7;}
        if(! (KEY_PIN & 0x20) ) {_delay_ms(300); return 8;}
        if(! (KEY_PIN & 0x40) ) {_delay_ms(300); return 9;}
        if(! (KEY_PIN & 0x80) ) {_delay_ms(300); return 'A';}
        
        KEY_PORT|=0x0f;
        KEY_PORT&=~0x02;
        if(! (KEY_PIN & 0x10) ) {_delay_ms(300); return 4;}
        if(! (KEY_PIN & 0x20) ) {_delay_ms(300); return 5;}
        if(! (KEY_PIN & 0x40) ) {_delay_ms(300); return 6;}
        if(! (KEY_PIN & 0x80) ) {_delay_ms(300); return 'B';}

        KEY_PORT|=0x0f;
        KEY_PORT&=~0x04;
        if(! (KEY_PIN & 0x10) ) {_delay_ms(300); return 1;}
        if(! (KEY_PIN & 0x20) ) {_delay_ms(300); return 2;}
        if(! (KEY_PIN & 0x40) ) {_delay_ms(300); return 3;}
        if(! (KEY_PIN & 0x80) ) {_delay_ms(300); return 'C';}

        KEY_PORT|=0x0f;
        KEY_PORT&=~0x08;
        if(! (KEY_PIN & 0x10) ) {_delay_ms(300); return 'c';}
        if(! (KEY_PIN & 0x20) ) {_delay_ms(300); return 0;}
        if(! (KEY_PIN & 0x40) ) {_delay_ms(300); return '=';}
        if(! (KEY_PIN & 0x80) ) {_delay_ms(300); return 'D';}
    }
}