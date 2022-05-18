#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "functions_prototype.h"
#include "shortcut.h"

char flag1 = 1; //flag to indicate whether to stay in interrupt or not
char flag2 = 1;	//flag used to indicate that SW2 stop case is pressed, so to enter enter another interrupt


//Handler function to deal with interrupt caused by SW3_Button
void GPIOA_Handler(void)
{
	int i;	//variable used in loop delay
	flag1 = 1;	//flag to indicate whether to stay in interrupt or not
	flag2 = 1;	//flag used to indicate that SW2 stop case is pressed, so to enter enter another interrupt
	while(!SW3_Input()){}	//wait for user to stop pressing SW3_button
	GPIO_PORTA_DATA_R |= 0x08;	//confirm that SW3 is not pressed
	RGB_Output(RED+GREEN+BLUE);	//Turn on all leds
	//while loop to indicate whether to stay in interrupt or not
	while(flag1)
	{
		GPIO_PORTF_DATA_R ^= RED+GREEN+BLUE;	//blinking leds
		for(i=0;i<300000 && flag1;i++) //a loop used for delay(wait time on and wait time off)
		{
			if(!SW1_Input())	//check if the user pressed SW1 or not
			{
				while(!SW1_Input()){}	//wait for user to stop pressing SW1_button
				flag_stop();	//function flag stop used to clear timer and stop all operations
				RGB_Output(RED+BLUE+GREEN);	//Turn on all leds
				flag2 = 0;	//clear flag2 to indicate that SW2 stop case is pressed, so to enter enter another interrupt
			}
			else if(!SW3_Input())	//check if the user pressed SW3 or not
			{
				while(!SW3_Input()){} //wait for user to stop pressing SW3_button
				GPIO_PORTA_ICR_R |= 0x08;	//clear interrupt
				RGB_Output(RED+BLUE+GREEN);	//Turn on all leds
				flag1 = 0;	//clear flag1 to exit interrupt
				break; //exit for loop
			}
		}
	}
	GPIO_PORTA_DATA_R |= 0x08;	//confirm that SW3 is not pressed
	GPIO_PORTF_DATA_R |= 0x10;	//a confirmation to clear all interrupts
	GPIO_PORTA_ICR_R |= 0x08;	//a confirmation to clear all interrupts
}

//Handler function to deal with interrupt caused by SW1_Button(Pause Operation)
void GPIOF_Handler(void)
{ 
	int i; //variable used in loop delay
	flag1 = 1; //flag to indicate whether to stay in interrupt or not
	while(!SW1_Input()){} //wait for user to stop pressing SW1_button
	GPIO_PORTF_DATA_R |= 0x10;  //confirm that SW1 is not pressed
	RGB_Output(RED+GREEN+BLUE); //Turn on all leds
	//while loop to indicate whether to stay in interrupt or not, and flag2 to exit interrupt if it caused by interrupt in SW3
	while(flag1 && flag2)
	{
		/*function flag_restart used to restart timer in cooking time case and
		returns 0 or 1 to indicate whether we are in case cooking time or not*/
		if(flag_restart())
		{
			break;	//exit while loop to restart only timer in cooking time and not stop the operation
		}
		GPIO_PORTF_DATA_R ^= RED+GREEN+BLUE; //blink leds
		for(i=0;i<300000 && flag1 && !flag_restart();i++)	//a loop used for delay(wait time on and wait time off)
		{
			if(!SW2_Input()) //check if the user pressed SW2 or not(Resume Operation)
			{
				while(!SW2_Input()){} 	//wait for user to stop pressing SW2_button
				GPIO_PORTF_ICR_R |= 0x10;  //confirm that SW1 is not pressed
				RGB_Output(RED+BLUE+GREEN); //Turn on all leds
				flag1 = 0; //clear flag1 to exit interrupt
				break; //exit for loop
			}
			else if(!SW1_Input()) //check if the user pressed SW1 or not(Stop Operation)
			{
				while(!SW1_Input()){}	//wait for user to stop pressing SW1_button
				flag_stop();  //function flag stop used to clear timer and stop all operations
				flag1 = 0; //clear flag1 to exit interrupt
				break; //exit for loop
			}
		}
	}
	GPIO_PORTF_DATA_R |= 0x10; //confirm that SW1 is not pressed
	GPIO_PORTF_ICR_R |= 0x10; //a confirmation to clear all interrupts
}
