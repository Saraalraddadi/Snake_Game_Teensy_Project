#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h> 
#include "lcd_nokia5110.c"
#include <math.h> 
#include "main.h"



//Adc initialize port
void InitADC()
{
	ADMUX = (1<<REFS0);                         			// For Aref=AVcc;
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
}

//read por adc
uint16_t ReadADC(uint8_t ch)
{
   //Select ADC Channel ch must be 0-7
   ch=ch&0b00000111;
   ADMUX|=ch;

   //Start Single conversion
   ADCSRA|=(1<<ADSC);

   //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it
   //Note you may be wondering why we have write one to clear it
   //This is standard way of clearing bits in io as said in datasheets.
   //The code writes '1' but it result in setting bit to '0' !!!

   ADCSRA|=(1<<ADIF);
	
	
   return(ADC);
}


//function to draw horizontal line
void LCD_draw_hline(unsigned char x_3, unsigned char y_3)
{
	
	unsigned char X_84;
	unsigned char y_48;
	unsigned char dato_col;
	
	
	X_84 = x_3 * 3;
	y_48 = trunc(y_3 * 3 / 8) ;


		dato_col = y_3 * 3  - 8 * y_48;	


		LcdCache [ X_84 -2][ y_48] = (0x40 >> (8 - dato_col)) | LcdCache [ X_84 -2][ y_48];
		LcdCache [ X_84 -1][ y_48] = (0x40 >> (8 - dato_col)) | LcdCache [ X_84 -1][ y_48];
		LcdCache [ X_84   ][ y_48] = (0x40 >> (8 - dato_col)) | LcdCache [ X_84   ][ y_48];
			
	
		LCD_write_col(X_84 -2 , y_48,LcdCache [ X_84 -2][ y_48]);
		LCD_write_col(X_84 -1 , y_48,LcdCache [ X_84 -1][ y_48]);
		LCD_write_col(X_84    , y_48,LcdCache [ X_84   ][ y_48]);


}

//function draw one sprite 3x3 "+" form
void LCD_write_sprite(unsigned char x_3, unsigned char y_3)
{
	
	unsigned char X_84;
	unsigned char y_48;
	unsigned char dato_col;
	
	char str1[3], str2[3];
	
	
	X_84 = x_3 * 3 -1;
	y_48 = trunc((y_3 -1) * 3 / 8) ;


	if ((y_3 == 3) || (y_3 == 6) || (y_3 == 11) || (y_3 == 14)) 
	{
		
		switch(y_3)
		{
			case 3: //case sprite is in the midle of two column
				
				LcdCache [ X_84 -2][ 0] = 0x80 | LcdCache [ X_84 -2][ 0];
				LcdCache [ X_84 -1][ 0] = 0xc0 | LcdCache [ X_84 -1][ 0];
				LcdCache [ X_84   ][ 0] = 0x80 | LcdCache [ X_84   ][ 0];
				
				LcdCache [ X_84 -1][ 1] = 0x01 | LcdCache [ X_84 -1][ 1];
								
				
				LCD_write_col(X_84 -2 , 0, LcdCache [ X_84 -2][ 0]);
				LCD_write_col(X_84 -1 , 0, LcdCache [ X_84 -1][ 0]);
				LCD_write_col(X_84    , 0, LcdCache [ X_84   ][ 0]);
				
				
				LCD_write_col(X_84 -1 , 1, LcdCache [ X_84 -1][ 1]);
					

				
				break; //case sprite is in the midle of two column
			case 6:	
			
				
				LcdCache [ X_84 -1][ 1] = 0x80 | LcdCache [ X_84 -1][ 1];
				
				
				LcdCache [ X_84 -2][ 2] = 0x01 | LcdCache [ X_84 -2][ 2];
				LcdCache [ X_84 -1][ 2] = 0x03 | LcdCache [ X_84 -1][ 2];
				LcdCache [ X_84   ][ 2] = 0x01 | LcdCache [ X_84   ][ 2];		
			
			
			
				
				LCD_write_col(X_84 -1 , 1,LcdCache [ X_84 -1][ 1]);
				
				
				LCD_write_col(X_84 -2 , 2, LcdCache [ X_84 -2][ 2]);
				LCD_write_col(X_84 -1 , 2, LcdCache [ X_84 -1][ 2]);
				LCD_write_col(X_84    , 2, LcdCache [ X_84   ][ 2]);			
				break;
			

			case 11:	//case sprite is in the midle of two column
			
				LcdCache [ X_84 -2][ 3] = 0x80 | LcdCache [ X_84 -2][ 3];
				LcdCache [ X_84 -1][ 3] = 0xc0 | LcdCache [ X_84 -1][ 3];
				LcdCache [ X_84   ][ 3] = 0x80 | LcdCache [ X_84   ][ 3];
				
				
				LcdCache [ X_84 -1][ 4] = 0x01 | LcdCache [ X_84 -1][ 4];
								
			
				LCD_write_col(X_84 -2 , 3,LcdCache [ X_84 -2][ 3] );
				LCD_write_col(X_84 -1 , 3,LcdCache [ X_84 -1][ 3] );
				LCD_write_col(X_84    , 3,LcdCache [ X_84   ][ 3] );
				
				
				LCD_write_col(X_84 -1 , 4, LcdCache [ X_84 -1][ 4]);
								
				break;
			
			case 14:	//case sprite is in the midle of two column
			
				
				LcdCache [ X_84 -1][ 4] = 0x80 | LcdCache [ X_84 -1][ 4];
				
				
				LcdCache [ X_84 -2][ 5] = 0x01 | LcdCache [ X_84 -2][ 5];
				LcdCache [ X_84 -1][ 5] = 0x03 | LcdCache [ X_84 -1][ 5];
				LcdCache [ X_84   ][ 5] = 0x01 | LcdCache [ X_84   ][ 5];				
			
				
				LCD_write_col(X_84 -1 , 4,LcdCache [ X_84 -1][ 4] );
				
				
				LCD_write_col(X_84 -2 , 5, LcdCache [ X_84 -2][ 5]);
				LCD_write_col(X_84 -1 , 5, LcdCache [ X_84 -1][ 5]);
				LCD_write_col(X_84    , 5, LcdCache [ X_84   ][ 5]);					
				break;
				
				//default:
	
		}
	
	}
	else //case sprite is into one column
	{
		dato_col = y_3 * 3  - 8 * y_48 ;		
		
		if (dato_col == 0)
		{
				
				
		}
		else 
		{
			dato_col = dato_col -3;	
		}
		
				
		LcdCache [ X_84 -2][ y_48] = (0x02 <<  dato_col) | LcdCache [ X_84 -2][ y_48];
		LcdCache [ X_84 -1][ y_48] = (0x07 <<  dato_col) | LcdCache [ X_84 -1][ y_48];
		LcdCache [ X_84   ][ y_48] = (0x02 <<  dato_col) | LcdCache [ X_84   ][ y_48];
				
		
		LCD_write_col(X_84 -2 , y_48,LcdCache [ X_84 -2][ y_48]);
		LCD_write_col(X_84 -1 , y_48,LcdCache [ X_84 -1][ y_48]);
		LCD_write_col(X_84    , y_48,LcdCache [ X_84   ][ y_48]);
		
	}

}

//function delete horizontal line
void LCD_delete_hline(unsigned char x_3, unsigned char y_3)
{
	unsigned char X_84;
	unsigned char y_48;
	unsigned char dato_col;
	
	
	X_84 = x_3 * 3;
	y_48 = trunc(y_3 * 3 / 8) ;


	
		dato_col = y_3 * 3  - 8 * y_48;		


		LcdCache [ X_84 -2][ y_48] = ~(0x40 >> (8 - dato_col)) & LcdCache [ X_84 -2][ y_48];
		LcdCache [ X_84 -1][ y_48] = ~(0x40 >> (8 - dato_col)) & LcdCache [ X_84 -1][ y_48];
		LcdCache [ X_84   ][ y_48] = ~(0x40 >> (8 - dato_col)) & LcdCache [ X_84   ][ y_48];
				
		LCD_write_col(X_84 -2 , y_48,LcdCache [ X_84 -2][ y_48]);
		LCD_write_col(X_84 -1 , y_48,LcdCache [ X_84 -1][ y_48]);
		LCD_write_col(X_84    , y_48,LcdCache [ X_84   ][ y_48]);
		
		
		
}


//function delete one sprite
void LCD_delete_sprite(unsigned char x_3, unsigned char y_3)
{
	unsigned char X_84;
	unsigned char y_48;
	unsigned char dato_col;
	
	
	X_84 = x_3 * 3 -1;
	y_48 = trunc((y_3 -1)* 3 / 8) ;

	if ((y_3 == 3) || (y_3 == 6) || (y_3 == 11) || (y_3 == 14)) 
	{
		
		switch(y_3)
		{
			case 3:
				
				LcdCache [ X_84 -2][ 0] = ~0xc0 & LcdCache [ X_84 -2][ 0];
				LcdCache [ X_84 -1][ 0] = ~0xc0 & LcdCache [ X_84 -1][ 0];
				LcdCache [ X_84   ][ 0] = ~0xc0 & LcdCache [ X_84   ][ 0];
				
				LcdCache [ X_84 -2][ 1] = ~0x01 & LcdCache [ X_84 -2][ 1];
				LcdCache [ X_84 -1][ 1] = ~0x01 & LcdCache [ X_84 -1][ 1];
				LcdCache [ X_84   ][ 1] = ~0x01 & LcdCache [ X_84   ][ 1];
				
				
				LCD_write_col(X_84 -2 , 0, LcdCache [ X_84 -2][ 0]);
				LCD_write_col(X_84 -1 , 0, LcdCache [ X_84 -1][ 0]);
				LCD_write_col(X_84    , 0, LcdCache [ X_84   ][ 0]);
				
				LCD_write_col(X_84 -2 , 1, LcdCache [ X_84 -2][ 1]);
				LCD_write_col(X_84 -1 , 1, LcdCache [ X_84 -1][ 1]);
				LCD_write_col(X_84    , 1, LcdCache [ X_84   ][ 1]);	


				
				
				break;
			case 6:	
			
				LcdCache [ X_84 -2][ 1] = ~0x80 & LcdCache [ X_84 -2][ 1];
				LcdCache [ X_84 -1][ 1] = ~0x80 & LcdCache [ X_84 -1][ 1];
				LcdCache [ X_84   ][ 1] = ~0x80 & LcdCache [ X_84   ][ 1];
				
				LcdCache [ X_84 -2][ 2] = ~0x03 & LcdCache [ X_84 -2][ 2];
				LcdCache [ X_84 -1][ 2] = ~0x03 & LcdCache [ X_84 -1][ 2];
				LcdCache [ X_84   ][ 2] = ~0x03 & LcdCache [ X_84   ][ 2];		
			
			
			
				LCD_write_col(X_84 -2 , 1,LcdCache [ X_84 -2][ 1]);
				LCD_write_col(X_84 -1 , 1,LcdCache [ X_84 -1][ 1]);
				LCD_write_col(X_84    , 1,LcdCache [ X_84   ][ 1]);
				
				LCD_write_col(X_84 -2 , 2, LcdCache [ X_84 -2][ 2]);
				LCD_write_col(X_84 -1 , 2, LcdCache [ X_84 -1][ 2]);
				LCD_write_col(X_84    , 2, LcdCache [ X_84   ][ 2]);			
				break;
			case 11:	
			
				LcdCache [ X_84 -2][ 3] = ~0xc0 & LcdCache [ X_84 -2][ 3];
				LcdCache [ X_84 -1][ 3] = ~0xc0 & LcdCache [ X_84 -1][ 3];
				LcdCache [ X_84   ][ 3] = ~0xc0 & LcdCache [ X_84   ][ 3];
				
				LcdCache [ X_84 -2][ 4] = ~0x01 & LcdCache [ X_84 -2][ 4];
				LcdCache [ X_84 -1][ 4] = ~0x01 & LcdCache [ X_84 -1][ 4];
				LcdCache [ X_84   ][ 4] = ~0x01 & LcdCache [ X_84   ][ 4];				
			
				LCD_write_col(X_84 -2 , 3,LcdCache [ X_84 -2][ 3] );
				LCD_write_col(X_84 -1 , 3,LcdCache [ X_84 -1][ 3] );
				LCD_write_col(X_84    , 3,LcdCache [ X_84   ][ 3] );
				
				LCD_write_col(X_84 -2 , 4, LcdCache [ X_84 -2][ 4]);
				LCD_write_col(X_84 -1 , 4, LcdCache [ X_84 -1][ 4]);
				LCD_write_col(X_84    , 4, LcdCache [ X_84   ][ 4]);				
				break;
			case 14:	
			
				LcdCache [ X_84 -2][ 4] = ~0x80 & LcdCache [ X_84 -2][ 4];
				LcdCache [ X_84 -1][ 4] = ~0x80 & LcdCache [ X_84 -1][ 4];
				LcdCache [ X_84   ][ 4] = ~0x80 & LcdCache [ X_84   ][ 4];
				
				LcdCache [ X_84 -2][ 5] = ~0x03 & LcdCache [ X_84 -2][ 5];
				LcdCache [ X_84 -1][ 5] = ~0x03 & LcdCache [ X_84 -1][ 5];
				LcdCache [ X_84   ][ 5] = ~0x03 & LcdCache [ X_84   ][ 5];				
			
				LCD_write_col(X_84 -2 , 4, LcdCache [ X_84 -2][ 4]);
				LCD_write_col(X_84 -1 , 4, LcdCache [ X_84 -1][ 4]);
				LCD_write_col(X_84    , 4, LcdCache [ X_84   ][ 4]);
				
				LCD_write_col(X_84 -2 , 5, LcdCache [ X_84 -2][ 5]);
				LCD_write_col(X_84 -1 , 5, LcdCache [ X_84 -1][ 5]);
				LCD_write_col(X_84    , 5, LcdCache [ X_84   ][ 5]);					
				break;
				
				//default:
	
		}
	
	}
	else
	{
		dato_col = y_3 * 3  - 8 * y_48;		
		
		if (dato_col ==0)
		{
		
		}
		else
		{

			dato_col = dato_col -3; //offset Location
		}

		LcdCache [ X_84 -2][ y_48] = ~(0x07 << dato_col) & LcdCache [ X_84 -2][ y_48];
		LcdCache [ X_84 -1][ y_48] = ~(0x07 << dato_col) & LcdCache [ X_84 -1][ y_48];
		LcdCache [ X_84   ][ y_48] = ~(0x07 << dato_col) & LcdCache [ X_84   ][ y_48];
				
		LCD_write_col(X_84 -2 , y_48,LcdCache [ X_84 -2][ y_48]);
		LCD_write_col(X_84 -1 , y_48,LcdCache [ X_84 -1][ y_48]);
		LCD_write_col(X_84    , y_48,LcdCache [ X_84   ][ y_48]);
		
		
		
	}


}

//function to draw all snake
void LCD_write_snake()
{
	int s;
	
		for (s=0;s<=snake_len-1;s++)
		{
			LCD_write_sprite(Lcd_snake_x3[s],Lcd_snake_y3[s]);	
				
		}

}

//function ini port input/output
void port_ini()
{
	DDRF = 0b10001110;
	DDRB = 0x7c;
	DDRD = 0xfc;

}

//function to ini var game
void snake_game_ini()
{
	int i,j; //auxiliar var

	x_game = 10;
	y_game = 10;
	
	snake_len = 2; //size ini of snake
		
	//the two firt sprite location	
	Lcd_snake_x3[0] = 10;
	Lcd_snake_y3[0] = 9;
	
	Lcd_snake_x3[1] = 11;
	Lcd_snake_y3[1] = 9;
	
		
	//save the cache to cero	
	for (i=0;i<=83;i++)
	{
		for (j=0;j<=5;j++)
		{
			LcdCache [ i][ j] = 0;
		
		}
	
	
	}
	
	
	LCD_write_snake();


}

//function draw the food
void ramdom_food()
{
	int i, cont =0;

		while (1)
		{
			srand(seed+x_rand_food);
				
			x_rand_food = trunc ( rand() % 27 + 1);
			y_rand_food = trunc ( rand() % 16 + 1 );
			
			
			if ((x_rand_food <27) && (y_rand_food <16) && (y_rand_food >3))
			{
					
					if (lines_walls == 1)
					{
						cont = 0;
					
						for (i=1;i<=12;i++)
						{
							if ((x_rand_food == i) && (y_rand_food == 7))
							{
								cont ++;

							}
						}	
							
							if (cont == 0)
							{														
								for (i=13;i<=26;i++)
								{
									if ((x_rand_food == i) && (y_rand_food == 12))
									{
										cont ++;
										
									}
							
								}

								if (cont == 0)
								{
								
									break;
									
								}
							
							
							}
							

							
						}

					
					else 
					{
						break;
					}

				
			}
			
		}		
		//draw sprite food	
		LCD_write_sprite(x_rand_food,y_rand_food);
		

}

//function to draw tree line wall
void draw_lines_walls()
{
	int i,j;

	for (i=1;i<=12;i++)
	{
		LCD_draw_hline(i,7);
	}
	
	for (i=13;i<=26;i++)
	{
		LCD_draw_hline(i,12);
	}	
	
	
	for (j=0;j<=2;j++)
	{
		LCD_write_col(48,j,0xff);
	}
	
}

//function delete tree line wall

void delete_lines_walls()
{
	int i,j;

	for (i=1;i<=12;i++)
	{
		LCD_delete_hline(i,7);
	}
	
	for (i=13;i<=26;i++)
	{
		LCD_delete_hline(i,12);
	}	
	
	for (j=0;j<=2;j++)
	{
		LCD_write_col(48,j,0x00);
	}
	
	
}


//function show ini message
void initial_message()
{

	LCD_gotoXY(0,0);
	LCD_write_string("**WEllcome** ");
	
	LCD_gotoXY(0,1);
	LCD_write_string(" Snake Game ");
	
	LCD_gotoXY(0,3);
	LCD_write_string(" Hatim Daniel");
	
	
	LCD_gotoXY(0,4);
	LCD_write_string(" ID: N8779333 ");
	
	
}

//function to show game over and ini var game
void game_over()
{
	direc = ini;

	LCD_clear();
	LCD_gotoXY(0,2);
	LCD_write_string(" Game ");
	
	LCD_gotoXY(0,3);
	LCD_write_string("       Over");

	
	_delay_ms(2000);
	LCD_clear();
	
	snake_game_ini();
	seed = 100;
	
	ini_ramdom =0;
	
	 
	
	x_game = 10;
	y_game = 10;
	
	score_uni = 0;
	score_ten = 0;
	score =0;
	
	live = 5;	
	
		
	LCD_gotoXY(0,0);
	LCD_write_char(score_ten + 0x30);
	LCD_write_char(score_uni + 0x30);
	
	LCD_gotoXY(13,0);
	LCD_write_char('(');
	LCD_write_char(live + 0x30);
	LCD_write_char(')');
	
	lines_walls =0;
	
	
	
}


//function decremented live
void live_lose()
{

	live = live -1;
					
	LCD_gotoXY(13,0);
	LCD_write_char('(');
	LCD_write_char(live + 0x30);
	LCD_write_char(')');
					
					
				
	if (live == 0)
	{
		game_over();
	}
	
	
}

//function show score
void draw_score()			
{

	score = score + 1 + lines_walls;


	if ((score < 10) || (score >10))
	{
		score_uni = score_uni + 1 + lines_walls;
		
	}	
	else if  (score == 10)
	{
		
		score_uni = 0;
		score_ten = 1;
	}
			
	LCD_gotoXY(0,0);
	LCD_write_char(score_ten + 0x30); //ten score
	LCD_write_char(score_uni + 0x30); //unid score

}

//function check adc if modified
void check_adc()
{

	if (ReadADC(0) < 250)
	{
		
		delay_game = 100;
	}
	else if (ReadADC(0) < 512)
	{
		delay_game = 200;
	}
	else if (ReadADC(0) < 750)
	{
		
		delay_game = 500;
	}	
	else if (ReadADC(0) < 1024)
	{
		
		delay_game = 800;
	}

}

//function main
int main(void)
{
	static int i,j,c,s;
	
	port_ini();
	LCD_init();       //LCD initialization
	LCD_clear();
	
	initial_message();	
		
	_delay_ms(2000);		
	LCD_clear(); 	
		
	snake_game_ini();
	seed = 100;		
	ini_ramdom =0;	//ini ramdom off
	
	x_game = 10;
	y_game = 10;
	
	score_uni = 0;
	score_ten = 0;
	score =0;
	
	lines_walls =0;  //ini wall off
	
	live = 5;	//live in 5
	
	delay_game = 200;
		
	//show ini display score and live	
	LCD_gotoXY(0,0);
	LCD_write_char(score_ten + 0x30);
	LCD_write_char(score_uni + 0x30);
	
	LCD_gotoXY(13,0);
	LCD_write_char('(');
	LCD_write_char(live + 0x30);
	LCD_write_char(')');
	
	
	InitADC();

//while main all the program run here
    while(1)
    {
		 
		seed = seed + 1;
		
		if (seed> 100000)
		{
			seed = 0;
		}
		
		if ((direc != ini) && (ini_ramdom ==0))
		{
			ramdom_food();
			ini_ramdom = 1;
		}
		
	if (direc != ini) //if no ini nothin happens
	{
	
		check_adc();
	
	
		//verified if snake take food
		if ((Lcd_snake_x3[0] == x_rand_food ) && (Lcd_snake_y3[0] == y_rand_food))
		{
			
			last_position_y = Lcd_snake_y3[snake_len-1]; 	
			last_position_x = Lcd_snake_x3[snake_len-1];	
			
			for (s=0;s<snake_len-1;s++)
			{
				Lcd_snake_y3[snake_len-1 -s] = Lcd_snake_y3[snake_len-2-s];
				Lcd_snake_x3[snake_len-1 -s] = Lcd_snake_x3[snake_len-2-s];

			}
	
			
			snake_len = snake_len +1; //snake grow
			
			LCD_write_snake();
			LCD_delete_sprite(last_position_x,last_position_y);
			_delay_ms(100);				
			
			
			draw_score(); //update score
			
			
			ramdom_food(); //new food
		}
		
		//check cross body happens
		for (s=2;s<snake_len-1;s++)
		{
			if ((Lcd_snake_x3[0] == Lcd_snake_x3[s] ) && (Lcd_snake_y3[0] == Lcd_snake_y3[s])) 
			{
				
				live_lose(); //lose one live
				
			}
		}
		
		if (lines_walls == 1) //check if wall is present display
		{
		
			draw_lines_walls(); //update wall in display
		
			for (i=1;i<=12;i++)
			{
				
				if ((Lcd_snake_x3[0] == i) && (Lcd_snake_y3[0] == 7))
				{
					live_lose();
				}
			}
	
			for (i=13;i<=26;i++)
			{
				if ((Lcd_snake_x3[0] == i) && (Lcd_snake_y3[0] == 12))
				{
									
					live_lose();
				}
			}

			for (j=4;j<=8;j++)
			{
				
				if ((Lcd_snake_x3[0] == 16) && (Lcd_snake_y3[0] == j))
				{
									
					live_lose();
				}

				
			}
		
		
		}
		
		
		if (direc == up) //in direction up process move 		
		{
		
			last_position_y = Lcd_snake_y3[snake_len-1]; 	
			last_position_x = Lcd_snake_x3[snake_len-1];	
			
			for (s=0;s<snake_len-1;s++)
			{
				Lcd_snake_y3[snake_len-1 -s] = Lcd_snake_y3[snake_len-2-s];
				Lcd_snake_x3[snake_len-1 -s] = Lcd_snake_x3[snake_len-2-s];

			}
			
			Lcd_snake_y3[0]--;
			if (Lcd_snake_y3[0] < 4)
			{
				Lcd_snake_y3[0] = 16;
			}			
			
			
			LCD_write_snake();
			LCD_delete_sprite(last_position_x,last_position_y);
			_delay_ms(delay_game);				
		
		}
		else if (direc == down) //in direction down process move 		
		{
		
			//save the last position to delete	
			last_position_y = Lcd_snake_y3[snake_len-1]; 	
			last_position_x = Lcd_snake_x3[snake_len-1];
	
			
			//fill the snake new value
			for (s=0;s<snake_len-1;s++)
			{
				Lcd_snake_y3[snake_len-1 -s] = Lcd_snake_y3[snake_len-2-s];
				Lcd_snake_x3[snake_len-1 -s] = Lcd_snake_x3[snake_len-2-s];

			}			

			//the head position of the snake
			Lcd_snake_y3[0]++;
			if (Lcd_snake_y3[0] >= 16)
			{
				Lcd_snake_y3[0] = 4;
			}
			
			
			LCD_write_snake();
			LCD_delete_sprite(last_position_x,last_position_y);
			_delay_ms(delay_game);				
		
		}		
		
		else if (direc == left) 	//in direction left process move 		
		{
		
			last_position_y = Lcd_snake_y3[snake_len-1]; 	
			last_position_x = Lcd_snake_x3[snake_len-1];
	
			
			for (s=0;s<snake_len-1;s++) 	
			{
				Lcd_snake_y3[snake_len-1 -s] = Lcd_snake_y3[snake_len-2-s];
				Lcd_snake_x3[snake_len-1 -s] = Lcd_snake_x3[snake_len-2-s];

			}			

			Lcd_snake_x3[0]--;
			if (Lcd_snake_x3[0] <= 0)
			{
				Lcd_snake_x3[0] = 27;
			}
			
			
			LCD_write_snake();
			LCD_delete_sprite(last_position_x,last_position_y);
			_delay_ms(delay_game);				
		
		}		
		
		else if (direc == right) 	//in direction right process move 	
		{
		
			last_position_y = Lcd_snake_y3[snake_len-1]; 	
			last_position_x = Lcd_snake_x3[snake_len-1];
	
			
			for (s=0;s<snake_len-1;s++)
			{
				Lcd_snake_y3[snake_len-1 -s] = Lcd_snake_y3[snake_len-2-s];
				Lcd_snake_x3[snake_len-1 -s] = Lcd_snake_x3[snake_len-2-s];
			}			

			Lcd_snake_x3[0]++;
			if (Lcd_snake_x3[0] >= 27)
			{
				Lcd_snake_x3[0] = 1;
			}
			
			
			LCD_write_snake();
			LCD_delete_sprite(last_position_x,last_position_y);
			_delay_ms(delay_game);			
		
		}			
		
		
		
	}	
		
		
		
		if (input_SW2_pda5) //input button wall on
		{
			
			draw_lines_walls();
			
			lines_walls = 1;
			
			_delay_ms(100);
			
			
		}	
		if (input_SW3_pda6) //input button wall off
		{
			
			delete_lines_walls();
			
			_delay_ms(100);
			
			lines_walls = 0;
			
			
		}				
	
		if (input_SWC_pd1) //input button up
		{


			
			if (direc == down)
			{
				live_lose();
				_delay_ms(500);
			}
			//else
			{
				direc = up;
				_delay_ms(100);
			}

			
			
		}
		else if (input_SWA_pb7)		//input button down
		{
			

			
			if (direc == up)
			{
				live_lose();
				_delay_ms(500);
			}
			//else
			{
				direc = down;
				_delay_ms(100);
			}	
			

		}		
		
		else if (input_SWD_pd0) //input button right
		{
			

			
			if (direc == left)
			{
				live_lose();
				_delay_ms(500);
			}			
			//else
			{
				direc = right;
				_delay_ms(100);
			
			}
			

		}
		else if (input_SWB_pb1)		//input buttonleft
		{

			
			if (direc == right)
			{
				live_lose();
				_delay_ms(500);
			}
			//else 
			{
				direc = left;
				_delay_ms(100);
			}
			


		}		

		
		
			

	
    }
}

