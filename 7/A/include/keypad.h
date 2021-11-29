#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>

#define KEY_DDR DDRC
#define KEY_PIN PINC
#define KEY_PORT PORTC

void KeyPad_init(void);
uint8_t Read_keyPad(void);

#endif