#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "shortcut.h"
#include "functions_prototype.h"

#define IDLE					0
#define POPCORN				1
#define BEEF					2
#define CHICKEN				3
#define COOKINGTIME		4

void SystemInit(){}

int main(void)
{
	char *str;
	short c;	//variable to represent symbol pressed on keypad
	int state = IDLE;
	PortFInit();				//Intilization of PORTF
	PortDInit();				//Intilization of PORTD that is connected to columns of KeyPad 4x4
	PortEInit();				//Intilization of PORTE that is connected to rows of KeyPad 4x4
	SW3_Buzzer_Init();	//Intilization of  SW3 and Buzzer 
	LCD_init();					//Intilization of LCD
	SW1_Interrupt();		//Intilization of SW1_Interrupt
	SW3_Interrupt();		//Intilization of SW3_Interrupt
	while (1)
	{
		switch(state)
		{
			//IDLE case
			case IDLE :
				flag_resume();	// a confirmation to allow to start cooking
				c = 0;
				Write_Timer_zero();	//write time 00:00 on lcd
				RGB_Output(OFF);	//Turn off all leds
				c = getKeyPad();	//wait for user to press a symbol in KeyPad
				if (c == 'A')
					state = POPCORN;
				else if (c == 'B')
					state = BEEF;
				else if (c == 'C')
					state = CHICKEN;
				else if(c == 'D')
					state = COOKINGTIME;
				break;
			
			//POP CORN case
			case POPCORN :
				LCD_Write("POP CORN");
				str = "POP CORN";
				while(SW2_Input()){}	//wait for user to press SW2 button(Start)
				Start_Cooking(60, str);	//start cooking for 1 minute
				state = IDLE;	//return to IDLE state
				break;
			
			//BEEF case
			case BEEF :
				str = "Defrosting...";
				LCD_Cmd(clear_display);        //clear whatever is written on display 
				Enter_kilo('B', str);	//wait for user to enter kilo and then start defrosting
				state = IDLE; //return to IDLE state
				break;
			
			//CHICKEN case
			case CHICKEN :
				str = "Defrosting..";
				LCD_Cmd(clear_display);        //clear whatever is written on display 
				Enter_kilo('C', str);
				state = IDLE; //return to IDLE state
				break;
			
			//COOKING case
			case COOKINGTIME : 
				str = "Cooking Time?";
				LCD_Write("Cooking Time?");
				Cooking_time(str);	//wait for user to enter time for cooking and then start cooking
				state = IDLE; //return to IDLE state
				break;
		}
	}
}

