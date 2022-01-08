#include <avr/io.h>
#include <util/delay.h>
#include <avr\interrupt.h>
#include "lcd.h"

#define S1 ((PINA & 0X01) >> 0)
#define S2 ((PINA & 0X02) >> 1)
#define S3 ((PINA & 0X04) >> 2)
#define S4 ((PINA & 0X08) >> 3)
#define S5 ((PINA & 0X10) >> 4)

void timer_init()
{
	TCNT0 = 0;
	OCR0 = 50;
	TCCR0 = 0;
	TCNT2 = 0;
	OCR2 = 50;
	TCCR2 = 0;
	TIMSK = 0x41;
}

int main()
{
	DDRA = 0;
	PORTA |= 0x1f;
	DDRB |= 1 << 3;
	DDRD = 0xff;
	timer_init();
	lcd_init(LCD_DISP_ON);

	while (1)
	{
		lcd_clrscr();

		if (S1 == 0) // motor1,2 active
		{
			TCCR0 = TCCR2 = 0x6a;
			OCR0 = OCR2 = 255;
			lcd_puts("2 motors are active");
		}
		else if (S2 == 0) // motor 1 active with low speed
		{
			TCCR0 = 0x6a;
			TCCR2 = 0;
			OCR0 = 120;
			lcd_puts("motor1 low speed");
		}
		else if (S3 == 0) // motor 2 active with low speed
		{
			TCCR2 = 0x6a;
			TCCR0 = 0;
			OCR2 = 120;
			lcd_puts("motor2 low speed");
		}
		else if (S4 == 0) // motor 1 active with High speed
		{
			TCCR0 = 0x6a;
			TCCR2 = 0;
			OCR0 = 255;
			lcd_puts("motor1 High speed");
		}
		else if (S5 == 0) // motor 2 active with High speed
		{
			TCCR2 = 0x6a;
			TCCR0 = 0;
			OCR2 = 255;
			lcd_puts("motor2 High speed");
		}
		else
		{
			TCCR0 = 0;
			TCCR2 = 0;
			OCR0=OCR2=0;
			lcd_puts("No line is detect");
		}
		_delay_ms(20);
	}
}