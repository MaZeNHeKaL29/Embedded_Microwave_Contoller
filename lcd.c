#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "lcd.h"

/* initialization of LCD */
void LCD_init(void)
{
	//step1 enable clock of ports we will use and waiting util execution
	SYSCTL_RCGCGPIO_R |= 0x03; // ENABLE CLOCK FOR PORTA , PORTB 
	while( (SYSCTL_PRGPIO_R & 0X03) != 0X03);			// waiting until execution of enabling clock
	
	//step2 configure the pins we will use
	GPIO_PORTA_DIR_R |=0xE0; // configure A5,A6,A7  as output   (RS,RW,E)
	GPIO_PORTA_DEN_R |=0xE0;	// configure A5,A6,A7  as digital  (RS,RW,E)
	
	GPIO_PORTB_DIR_R |=0xFF; // configure B0,B1,B2,B3,B4,B5,B6,B7  as output     (D0,D1,D2,D3,D4,D5,D6,D7)
	GPIO_PORTB_DEN_R |=0xFF; // configure B0,B1,B2,B3,B4,B5,B6,B7  as digital    (D0,D1,D2,D3,D4,D5,D6,D7)
	
	
	LCD_Cmd(Set5x7FontSize);       //select font 5*7 of LCD
	LCD_Cmd(mode_8bit);            //select 8-bits mode of LCD                    (must after configure lcd pins)	
	LCD_Cmd(moveCursorRight);      //direction of cursor to right                 (must)   (without it sometimes doenot work)
	LCD_Cmd(clear_display);        //clear whatever is written on display         (optional)
	LCD_Cmd(cursorBlink);          //turn on display mode and cursor blinking     (must)   (without it sometimes doenot work)
}

/* select command of LCD */
void LCD_Cmd(unsigned char command)
{
	GPIO_PORTA_DATA_R = 0x00;       //  PA5 PA6 A7 = 00     --> E=0,RW = 0,RS=0       ACTIVATE COMMAND MODE
	GPIO_PORTB_DATA_R =command;	//  make B0-B7 carry certain command equivalent value
	GPIO_PORTA_DATA_R =0x80; 	//  PA7 PA6 A5 = 10     --> E=1,RW = 0,RS=0      upping E 
	delay_micro(1);			//  waiting
	GPIO_PORTA_DATA_R =0x00;        //  PA7 PA6 A5 = 000    --> E=0,RW = 0,RS=0       droping E to pass values on D0-D7 inside LCD
	
	if(command <4) 
		delay_milli(2);
	else 
		delay_micro(37); 
}


/* send charater to LCD */
void LCD_Data(unsigned char data)
{
	GPIO_PORTA_DATA_R =0x20;    //  PA7 PA6 A5 = 001 -->  E=0,RW = 0,RS=1        ACTIVATE DATA MODE
	GPIO_PORTB_DATA_R =data;    //  make B0-B7 carry the character
	GPIO_PORTA_DATA_R |= 0x80;  //  PA7 PA6 A5 = 101 -->  E=1,RW = 0,RS=1        upping E 
	delay_micro(1);	       	    //  waiting
	GPIO_PORTA_DATA_R =0x00;    //  PA7 PA6 A5 = 000 -->  E=0,RW = 0,RS=0        droping E to pass values on D0-D7 inside LCD
	delay_milli(1);		 
}

/* send String to LCD */
void LCD_String (char *str)	
{
	int i;
	for(i=0;str[i]!=0;i++)    // Send each char of string till the NULL
	{
		LCD_Data(str[i]);   
	}
}


/* delay */
void delay_milli(int n)
{
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<3180;j++){}
}
 
void delay_micro(int n)
{
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<3;j++){}
}

//function to clear what is on lcd and write new string
void LCD_Write(char *str) 
{
	LCD_Cmd(cursorBlink);
	LCD_Cmd(SecondRowPosition0);         //Force cusor to begining of Second row  
	LCD_String(str);
}
