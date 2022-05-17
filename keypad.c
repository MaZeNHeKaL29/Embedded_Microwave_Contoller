#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"



/*
R1 - R4 : Pins E0 - E4
C1 - C4 : Pins D0 - D4
*/


short symbol[4][4] = {
  {1,4,7,'*'},
  {2,5,8,'0'},
  {3,6,9,'#'},
  {'A','B','C','D'}
};


//Keypad 4x4 Column(Output)
void PortDInit(void)   
{
	SYSCTL_RCGCGPIO_R |= 0x08;
	while((SYSCTL_PRGPIO_R & 0x08)==0){}
	GPIO_PORTD_CR_R |= 0x0F;
	GPIO_PORTD_PDR_R |= 0x0F;
	GPIO_PORTD_DEN_R |= 0x0F;
	GPIO_PORTD_DIR_R |= 0x0F;
	GPIO_PORTD_PCTL_R &=~ 0x0F;
	GPIO_PORTD_AMSEL_R &=~ 0x0F;
	GPIO_PORTD_AFSEL_R &=~ 0x0F;
}


//Keypad 4x4 Row(Input)
void PortEInit(void)  
{
	SYSCTL_RCGCGPIO_R |= 0x10;
	while((SYSCTL_PRGPIO_R & 0x10)==0){}
	GPIO_PORTE_CR_R |= 0x0F;
	GPIO_PORTE_PDR_R |= 0x0F;
	GPIO_PORTE_DEN_R |= 0x0F;
	GPIO_PORTE_DIR_R &=~ 0x0F;
	GPIO_PORTE_PCTL_R &=~ 0x0F;
	GPIO_PORTE_AMSEL_R &=~ 0x0F;
	GPIO_PORTE_AFSEL_R &=~ 0x0F;
}


//Micro seconds delay Function
void delay(uint32_t n)
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3;j++)
 {}
}


//Function checks and returns the value of key pressed in KeyPad 4x4
char getKeyPad(void)
{
	short i,j;
	short c = 0;
	for(i = 0; i < 4; i++)    //Scan columns loop
	{
		GPIO_PORTD_DATA_R = (1U << (i));
		delay(2);
		for(j = 0; j < 4; j++)  //Scan rows loop
		{
			if((GPIO_PORTE_DATA_R & 0x0F) & (1U << (j)))
			{
				c = symbol[i][j];		//c = symbol pressed on keypad
			}
		}
	}
	return c;
}
