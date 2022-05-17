#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "shortcut.h"
#include "functions_prototype.h"

//function to write timer on lcd and the state
void Write_Timer(short time4, short time3, short time2, short time1, char *str)
{
	LCD_Cmd(moveCursorRight);      //direction of cursor to right
	LCD_Cmd(clear_display);        //clear whatever is written on display 
	LCD_Data(time4 + '0');					//(0)0:00
	LCD_Data(time3 + '0');					//0(0):00
	LCD_Data(':');								//00(:)00
	LCD_Data(time2 + '0');					//00:(0)0
	LCD_Data(time1 + '0');					//00:0(0)
	LCD_Write(str);	//write string sent to show the state on lcd
}

void Write_Timer_zero(void)
{
	LCD_Cmd(moveCursorRight);      //direction of cursor to right
	LCD_Cmd(clear_display);        //clear whatever is written on display 
	LCD_Data('0');					//(0)0:00
	LCD_Data('0');					//0(0):00
	LCD_Data(':');					//00(:)00
	LCD_Data('0');					//00:(0)0
	LCD_Data('0');					//00:0(0)
	delay_milli(500);
}
