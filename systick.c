#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"

// The delay parameter is in units of the 16 core clock (62.5 ns)


//1ms Timer
void SysTick_Wait_1ms(void)							
{
	NVIC_ST_CTRL_R = 0;										// disable sysTick during setup
	NVIC_ST_RELOAD_R = 16000 - 1;					// number of counts
	NVIC_ST_CURRENT_R = 0;								// any write to CURRENT clears it
	NVIC_ST_CTRL_R = 0x05;								// enable SysTick with core clock
	while ((NVIC_ST_CTRL_R & 0x00010000) == 0){}		//wait for flag
	NVIC_ST_CTRL_R = 0;										// disable sysTick
}


//1ms*delay Timer
void SysTick_Wait(uint32_t delay)
{
	uint32_t i;
	for (i = 0; i < delay; i++)
	{
		SysTick_Wait_1ms();					// wait 1ms
	}
}
