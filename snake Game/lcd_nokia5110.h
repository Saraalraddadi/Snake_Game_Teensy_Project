
#ifndef NOKIA_5110_
#define NOKIA_5110_


#define LCD_RST_high  	PORTB |=  (1<<4)    //external reset input
#define LCD_RST_low  	PORTB &=~ (1<<4)

#define LCD_DC_high   	PORTB |=  (1<<5)    //data/commande
#define LCD_DC_low   	PORTB &=~ (1<<5)

#define LCD_SDIN_high   PORTB |=  (1<<6)    //serial data input
#define LCD_SDIN_low    PORTB &=~ (1<<6)

//#define LCD_SCLK_high   PORTA |=  (1<<7)    //serial clock input
//#define LCD_SCLK_low   	PORTA &= ~(1<<7)
#define LCD_SCLK_high   PORTF |=  (1<<7)    //serial clock input
#define LCD_SCLK_low   	PORTF &= ~(1<<7)


#define LCD_SCE_high 	PORTD |=  (1<<7)    //chip select input
#define LCD_SCE_low     PORTD &= ~(1<<7)

// define  Lcd screen size 
#define LCD_WIDTH 		84
#define LCD_HEIGHT 		48






void LCD_write_byte(unsigned char data, unsigned char command);
void LCD_init();
void LCD_clear();
void LCD_gotoXY(unsigned char x, unsigned char y_col);
void LCD_write_char(unsigned char c);
void LCD_write_string(char *s);
void LCD_write_column(unsigned char x, unsigned char y_col, unsigned char data);


#endif

