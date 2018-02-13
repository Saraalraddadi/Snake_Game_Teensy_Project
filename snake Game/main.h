#ifndef MAIN_H
#define MAIN_H

#define F_CPU 8000000UL

#define input_SWC_pd1  		PIND & (1<<PIND1)	//butom up
#define input_SWD_pd0  		PIND & (1<<PIND0)	//butom right
#define input_SWB_pb1  		PINB & (1<<PINB1)	//butom left
#define input_SWA_pb7  		PINB & (1<<PINB7)	//butom	down
#define input_SWCENTER_pb0  PINB & (1<<PINB0)	//butom center

//#define input_SW2_pda5		PINA & (1<<PINA5)
//#define input_SW3_pda6		PINA & (1<<PINA6)
#define input_SW2_pda5		PINF & (1<<PINF5)
#define input_SW3_pda6		PINF & (1<<PINF6)

#define LCD_WIDTH_3x3 	30
#define LCD_HEIGHT_3x3	20
#define COLUMN_NUMBER 	6
#define LCD_WIDTH 		84

static int delay_game;

static char lines_walls, n=0 ;

static long seed;

static char ini_ramdom =0;


static unsigned char score_uni, score_ten, score, live;

static unsigned char x_rand_food = 50 ,y_rand_food, aux_rand;

static enum direction {up, down, right, left, ini};
static enum direction direc = ini;

static unsigned char x_game, y_game,last_position_x,last_position_y;

static char LcdCache [ LCD_WIDTH][ COLUMN_NUMBER];
static char Lcd_snake [ LCD_WIDTH_3x3][ LCD_HEIGHT_3x3];
static char Lcd_snake_x3[30];
static int  Lcd_snake_y3[20];
static unsigned char snake_len;


void LCD_write_pixel3x3(unsigned char x_3, unsigned char y_3);
void LCD_wdelete_pixel3x3(unsigned char x_3, unsigned char y_3);
void snake_game_ini();
void LCD_write_snake();
void ramdom_food();

#endif