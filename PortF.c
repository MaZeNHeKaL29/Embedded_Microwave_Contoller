#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "functions_prototype.h"
#include "shortcut.h"


/*
	PortF Intilization
*/

char flag_SW1_Interrupt = 1;
//Intilization of PORTF
void PortFInit(void)											
{
	SYSCTL_RCGCGPIO_R |= 0x20; // activate PORTF
	while((SYSCTL_PRGPIO_R & 0x20)==0){}
	GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlock PORTF
	GPIO_PORTF_CR_R |= 0x1F; // allow changes to PF4-0
	GPIO_PORTF_AMSEL_R &=~ 0x1F; //disable analog function
	GPIO_PORTF_PCTL_R &=~ 0x000FFFFF; //allow GPIO only
	GPIO_PORTF_DIR_R &=~ 0x11;	//PF4,PF0 in
	GPIO_PORTF_DIR_R |= 0x0E;		//PF3-PF1 out
	GPIO_PORTF_AFSEL_R &=~ 0x1F; // disable alt // disable alt funct on PF7-0
	GPIO_PORTF_DEN_R |= 0x1F; // enable digital I/O on PF4-0
	GPIO_PORTF_PUR_R |= 0x11; //enable pull up resistor on PF4,PF0
}


//Check if SW1 in TivaC is pressed or not
unsigned char SW1_Input(void)							
{
	return GPIO_PORTF_DATA_R & 0x10;
}


//Check if SW2 in TivaC is pressed or not
unsigned char SW2_Input(void)							
{
	return GPIO_PORTF_DATA_R & 0x01;
}


//Check if SW1 and SW2 is pressed or not
unsigned char SW_Input(void)							
{
	return GPIO_PORTF_DATA_R & 0x11;
}


//Turn ON, Turn OFF, Change Color of LEDS in TivaC
void RGB_Output(unsigned char data)				
{
	GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & 0x11) + 0x00;
	GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & 0x11) + data;
}
