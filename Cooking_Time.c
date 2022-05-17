#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "shortcut.h"
#include "functions_prototype.h"




char flag2_continue = 1;	// a flag used in cooking time state to know if user pressed SW1 or not to restart entering cooking time
char flag_cooking_time = 0;	// a flag to indicate whether we are in state Cooking Time or not

// a function used in cooking time state to restart entering time
char flag_restart(void)
{
	if (flag_cooking_time)	//check if user is in Cooking Time state or not
	{
			flag2_continue = 0;	//restart entering cooking time
	}
	return flag_cooking_time;		//return 0 or 1 to interrupt to know if the user is in Cooking Time State or not
}


/*


COOKING TIME STATE



*/


//function used in state of cooking time "D" to let user enter time for cooking
void Cooking_time(char *str)
{
	short i;	//variable for outer loop
	short j;	//variable for inner loop				
	short time_sec;	//total time in sec
	short c = 0;	//variable to represent symbol pressed on keypad
	short flag1 = 1;	//a flag to check if time entered is valid or not
	short flag2 = 1;	//a flag to check is SW2(start) is pressed or not
	short times[4] = {0,0,0,0};	//an array representing time in 00:00
	short size = sizeof(times) / sizeof(short);	//a variable to determine size of array
	while(flag1)
	{
		RGB_Output(OFF);	//Turn of all leds
		flag2_continue = 1;	 // a flag used in cooking time state to know if user pressed SW1(stop) or not to restart entering cooking time
		flag_cooking_time = 1; // a flag to indicate whether we are in state Cooking Time or not
		flag2 = 1;		//set flag2 to 1, a flag to check is SW2 is pressed or not
		//a loop to set time to zero
		for(i=0;i<size;i++)	//set zero to all times
		{
			times[i] = 0;
		}
		Write_Timer(times[3], times[2], times[1], times[0], str); //write timer on lcd
		delay_milli(500);	//wait
		
		//a loop to let user enter time, and check if SW2(Start) is pressed or not, and to know if user pressed SW1(stop) or not
		for(i=0; i<size && flag2 && flag2_continue; i++)
		{
			c = 0;
			//wait for the user to enter the number
			while(c == 0 && flag2_continue)
			{
				c = getKeyPad();	//c => symbol pressed
				//check if the symbol entered is a number or not
				if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == '#' || c == '*')
				{
					LCD_Cmd(clear_display);
					LCD_Write("Err..");			//write "Err.." on lcd
					SysTick_Wait(2000);			//wait 2 sec
					c = 0;
					Write_Timer(times[3], times[2], times[1], times[0], str); //write timer on lcd
					delay_milli(500);	//wait
				}
				//check if the user pressed start button or not
				if (!SW2_Input())
				{
					flag2 = 0;	//user pressed start button
					break;			//exit from loop
				}
			}
			//check if the user pressed start button or not
			if (flag2 && flag2_continue)
			{
				//if user pressed c is set to '0' not 0, so if user pressed '0' in this case let c => 0
				if (c == '0')
					c = 0; 
				//a  loop to set timer values
				for(j=(size-1);j>=0;j--)
				{
					if(j==0)
						times[j] = c;
					else
						times[j] = times[j-1];
				}
				Write_Timer(times[3], times[2], times[1], times[0], str); //write timer on lcd
				delay_milli(500);	//wait
			}
		}
		time_sec = ((times[3]*10) + times[2])*60 + ((times[1]*10) + times[0]);	//calculate total no. of seconds
		// if time is more than 30 minutes
		if (time_sec > 1800 && flag2_continue)
		{
			LCD_Write("Max Time is 30");	//write "Max Time is 30" on lcd
			SysTick_Wait(2000);						//wait 2 sec
		}
		//if time is 00
		else if(time_sec == 0 && flag2_continue)
		{
			LCD_Write("Time is 0???");	//write	"Time is 0???" on lcd
			SysTick_Wait(2000);					//wait 2 sec
		}
		else if(flag2_continue)
		{
			flag_cooking_time = 0;	//exit Cooking Time and start counting down
			str = "Cooking...";	
			while (SW2_Input()){}		//wait for user to press start button(SW2)
			Start_Cooking(time_sec, str);	//start cooking
			flag1 = 0;	//exit loop
		}		
	}
	flag_cooking_time = 0; //exit Cooking Time
}

