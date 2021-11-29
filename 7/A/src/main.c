
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "keypad.h"

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

char txt[32];
char numberOfUsers = 0;
char passwordOfAdmin[4] = {0, 0, 0, 0}, dataOfAdmin[4];

int main()
{
	DDRB = 0x03;
	PORTB = 0x00;
	DDRC = 0xff;

	KeyPad_init();
	lcd_init(LCD_DISP_ON);
	UCSRA = 0;
	UCSRB = 0x18;
	UCSRC = 0x86;
	UBRRL = 52;
	UBRRH = 0;

	while (1)
	{
		PORTB = 0;
		lcd_clrscr();
		lcd_puts_P("Hi Admin...");
		lcd_gotoxy(0, 1);
		lcd_puts_P("password?");

		for (uint8_t i = 0; i < 4; i++)
		{
			dataOfAdmin[i] = Read_keyPad();
			lcd_putc(dataOfAdmin[i] + 48);
		}
		while (Read_keyPad() != '=')
			;

		lcd_clrscr();
		if (dataOfAdmin[0] == passwordOfAdmin[0] && dataOfAdmin[1] == passwordOfAdmin[1] &&
			dataOfAdmin[2] == passwordOfAdmin[2] && dataOfAdmin[3] == passwordOfAdmin[3])
		{
			lcd_puts_P("admin entered :)");
			PORTB = 1;

			lcd_clrscr();
			lcd_puts_P("how many users");
			numberOfUsers = Read_keyPad();
			lcd_putc(numberOfUsers + 48);

			while (Read_keyPad() != '=')
				;
			PORTB = 0;

			uint8_t passwordOfUser[numberOfUsers][4];
			uint8_t dataOfUser[numberOfUsers][4];
			uint8_t user_id = 0;

			for (uint8_t i = 0; i < numberOfUsers; i++)
			{
				sprintf(txt, "user %d pass:", i + 1);
				lcd_clrscr();
				lcd_puts(txt);

				lcd_gotoxy(0, 1);
				for (uint8_t j = 0; j < 4; j++)
				{
					passwordOfUser[i][j] = Read_keyPad();
					lcd_putc(passwordOfUser[i][j] + 48);
				}
				while (Read_keyPad() != '=')
					;
			}

			lcd_clrscr();
			lcd_puts_P("enter user id?");
			user_id = Read_keyPad();
			lcd_putc(user_id + 48);
			user_id--;
			while (Read_keyPad() != '=')
				;

			lcd_clrscr();
			sprintf(txt, "user %d pass:", user_id + 1);
			lcd_clrscr();
			lcd_puts(txt);
			lcd_gotoxy(0, 1);
			for (uint8_t i = 0; i < 4; i++)
			{
				dataOfUser[user_id][i] = Read_keyPad();
				lcd_putc(dataOfUser[user_id][i] + 48);
			}
			while (Read_keyPad() != '=')
				;

			lcd_clrscr();
			if (dataOfUser[user_id][0] == passwordOfUser[user_id][0] &&
				dataOfUser[user_id][1] == passwordOfUser[user_id][1] &&
				dataOfUser[user_id][2] == passwordOfUser[user_id][2] &&
				dataOfUser[user_id][3] == passwordOfUser[user_id][3])
			{
				sprintf(txt, "user%d entered...", user_id+1);
				lcd_clrscr();
				lcd_puts(txt);
				PORTB = 1;

				lcd_clrscr();
				lcd_puts_P("Rotations Count?");
				lcd_gotoxy(0, 1);

				uint8_t s[10], i = 0, data[10];
				uint8_t rotationDigit = Read_keyPad();
				s[i++] = rotationDigit + 48;
				lcd_putc(rotationDigit + 48);
				PORTB = 0;
				while (1)
				{
					uint8_t rotationDigit = Read_keyPad();
					if (rotationDigit != '=')
					{
						s[i++] = rotationDigit + 48;
						lcd_putc(rotationDigit + 48);
					}
					else
					{
						s[i] = '\0';
						break;
					}
				}
				_puts((char *)s);
				_putchar('\n');
				_gets((char *)data, 10);
				lcd_clrscr();
				lcd_puts((char *)data);
			}
			else
			{
				lcd_puts_P("Forbidden");
				PORTB = 2;
			}
		}

		else
		{
			lcd_puts_P("Forbidden");
			PORTB = 2;
			_delay_ms(500);
		}
	}
}