#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "shortcut.h"
#include "functions_prototype.h"

char flag_continue = 1; //a flag to resume cooking or stop cooking


//a function used to resume cooking
void flag_resume(void)
{
	flag_continue = 1;
}


// a function used to stop cooking and return to IDLE state
void flag_stop(void)
{
	flag_continue = 0; //stop cooking
	Write_Timer_zero();	//clear timer
	GPIO_PORTF_ICR_R |= 0x10;	//a confirmation to clear all interrupts
}

//function to start the cooking of microwave
void Start_Cooking(short time_sec,char *str)
{
	short i;
	LCD_Cmd(moveCursorRight);     //direction of cursor to right
	LCD_Cmd(clear_display);       //clear whatever is written on display 
	LCD_Cmd(cursorBlink);         //turn on display mode and cursor blinking
	RGB_Output(RED+BLUE+GREEN);		//turn on all leds
	Start_timer(time_sec, str);				//start counting down			
	Write_Timer(0,0,0,0,"END");			//clear timer and type END in lcd
	for(i = 0; i < 3 && flag_continue; i++)	// a loop to turn on buzzer and start blinking
	{
		Buzzer_Output(BuzzerON);	//turn on buzzer
		RGB_Output(OFF);						//turn off leds
		SysTick_Wait(1000);					//wait 1 sec
		RGB_Output(RED+BLUE+GREEN);	//turn on all leds
		SysTick_Wait(1000);					//wait 1 sec
	}
	Buzzer_Output(OFF);					//turn off buzzer
	RGB_Output(OFF);							//turn off all leds
}

//function to start count down of timer and know number of minutes and seconds
void Start_timer(short time_sec,char *str)									
{
	short time4 = (time_sec/60)/10;															//varaible to know first digit in minutes (0)0:00
	short time3 = (time_sec/60 - time4*10);											//variable to know second digit in minutes 0(0):00
	short time2 = (time_sec - (((time4*10)+time3)*60))/10;			//variable to know first digit in seconds 	00:(0)0
	short time1 = (time_sec - (((time4*10)+time3)*60) - (time2*10));	//variable to know second digit in seconds 00:0(0)
	Write_Timer(time4, time3, time2, time1, str);										//write timer
	SysTick_Wait(1000);																					//wait 1 second
	while ((time4 || time1 || time2 || time3) && flag_continue)										//while loop to start count down and check if timer ends		
	{
		if (time1 != 0 && flag_continue)
		{
			time1 = time1 - 1;
			Write_Timer(time4, time3, time2, time1,str);										//write timer on lcd
			SysTick_Wait(1000);																					//wait 1 second
		}
		
		else if((time2 != 0 && time1 == 0) && flag_continue) 
		{
			time2 = time2 - 1;
			time1 = 9;
			Write_Timer(time4, time3, time2, time1,str);										//write timer on lcd
			SysTick_Wait(1000);																					//wait 1 second
		}

		else if ((time3 != 0 &&time2 == 0 && time1 == 0) && flag_continue)
		{
			time2 = 5;
			time3 = time3 - 1;
			time1 = 9;
			Write_Timer(time4, time3, time2, time1,str);										//write timer on lcd
			SysTick_Wait(1000);																					//wait 1 second
		}
		
		else if ((time4 != 0 && time3 == 0 &&time2 == 0 && time1 == 0) && flag_continue)
		{
			time3 = 9;
			time2 = 5;
			time4 = time4 - 1;
			time1 = 9;
			Write_Timer(time4, time3, time2, time1,str);										//write timer on lcd
			SysTick_Wait(1000);																					//wait 1 second
		}
	}
}

