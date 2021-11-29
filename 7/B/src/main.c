
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint16_t sensor(uint8_t channel_num)
{
	ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | channel_num;

	_delay_us(10);
	ADCSRA |= (1 << ADSC);

	while ((ADCSRA & (1 << ADIF)) == 0)
		;
	ADCSRA |= (1 << ADIF);

	return ADCW;
}

unsigned char _getchar()
{
	while ((UCSRA & (1 << RXC)) == 0)
		;
	return (UDR);
}

void _putchar(char ch)
{
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = ch;
}

void _puts(char *str)
{
	while (*str)
	{
		_putchar(*str);
		str++;
	}
}
void _gets(char *str, uint8_t len)
{
	char i = 0;
	char rx = 0;
	for (i = 0; i < len; i++)
	{
		rx = _getchar();
		if (rx != 10 && rx != 13)
		{
			*str = rx;
			str++;
		}
		else
		{
			*str = '\0';
			return;
		}
		*str = '\0';
	}
}

char txt[10];
unsigned int number = 0;
unsigned char motor[4] = {0x03, 0x6, 0x0c, 0x09};

int main()
{
	DDRC = 0x0f;
	PORTC = 0x00;
	UCSRA = 0;
	UCSRB = 0x18;
	UCSRC = 0x86;
	UBRRL = 52;
	UBRRH = 0;
	ADCSRA = 0xa4;
	SFIOR = 0;
	char txtTemp[16];

	while (1)
	{
		_gets(txt, 10);
		number = atoi(txt);

		sprintf(txtTemp,"Temp: %d'c",(int)(sensor(0)*500.0/1023));
		_puts(txtTemp);
		_putchar('\n');

		for (unsigned int i = 0; i < number; i++)
		{
			for (unsigned char j = 0; j < 4; j++)
			{
				PORTC = motor[j];
				_delay_ms(50);
			}
		}
	}
}