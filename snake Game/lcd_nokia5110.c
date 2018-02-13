#include <avr/io.h>
#include <util/delay.h>
#include "english_font.h"

#include "lcd_nokia5110.h"



void LCD_write_col(unsigned char x, unsigned char y_col, unsigned char data)
{
	unsigned char i;
	
	LCD_gotoXY(x,y_col);
	
	LCD_DC_high;		//data

	for(i=0;i<8;i++)
	{
		if(data&0x80)
		LCD_SDIN_high;
		else
		LCD_SDIN_low;
		LCD_SCLK_low;
		data = data << 1;
		LCD_SCLK_high;
	}
}



void LCD_write_byte(unsigned char data, unsigned char command)
{
	unsigned char i;
	
	if (command == 1)
	LCD_DC_low;
	else
	LCD_DC_high;

	for(i=0;i<8;i++)
	{
		if(data&0x80)
		LCD_SDIN_high;
		else
		LCD_SDIN_low;
		LCD_SCLK_low;
		data = data << 1;
		LCD_SCLK_high;
	}
}

void LCD_init() 
{
	LCD_SCE_low; //active in low lcd

	LCD_RST_low;
	_delay_us(1);
	LCD_RST_high;

	_delay_us(1);

	LCD_write_byte(0x21, 1);	// set LCD mode
	LCD_write_byte(0xc8, 1);	// set bias voltage
	LCD_write_byte(0x06, 1);	// temperature correction
	LCD_write_byte(0x13, 1);	// 1:48
	LCD_write_byte(0x20, 1);	// use bias command, vertical
	LCD_write_byte(0x0c, 1);	// set LCD mode,display normally
	LCD_clear();	                // clear the LCD
}

void LCD_clear() 
{
	unsigned int i;

	LCD_write_byte(0x0c, 1);
	LCD_write_byte(0x80, 1);

	for (i=0; i<504; i++)
	{
		LCD_write_byte(0, 0);
	}
}

void LCD_gotoXY(unsigned char x, unsigned char y_col)
{
	LCD_write_byte(0x40 | y_col, 1);	// column
	LCD_write_byte(0x80 | x, 1);    // row
}

void LCD_write_char(unsigned char c)
{
	unsigned char line;

	c -= 32;

	for (line=0; line<6; line++)
	LCD_write_byte(font6x8[c][line], 0);
}

void LCD_write_string(char *s)
{
	
	while (*s)
	{
		LCD_write_char(*s);
		s++;
	}
}
