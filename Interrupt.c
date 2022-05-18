#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "functions_prototype.h"
#include "shortcut.h"

//function to intiliaze interrupt for SW1
void SW1_Interrupt(void)
{
	GPIO_PORTF_IS_R &= ~0x10; // PF4,PF0 is edge-sensitive
	GPIO_PORTF_IBE_R &= ~0x10; // PF4,PF0 is not both edges
	GPIO_PORTF_IBE_R &= ~0x10; // PF4,PF0 is not both edges
	GPIO_PORTF_IEV_R &= ~0x10; // PF4,PF0 falling edge event
	GPIO_PORTF_ICR_R &= ~0x10; // clear flag4
	GPIO_PORTF_IM_R |= 0x10; // arm interrupt on PF4,PF0
	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
	NVIC_EN0_R |= 0x40000000; // (h) enable interrupt 30 in NVIC
	__enable_irq(); /* global enable IRQs */
}

//function to intiliaze interrupt in SW3
void SW3_Interrupt(void)
{
	GPIO_PORTA_IS_R &= ~0x08; // PA3 is edge-sensitive
	GPIO_PORTA_IBE_R &= ~0x08; // PA3 is not both edges
	GPIO_PORTA_IBE_R &= ~0x08; // PA3 is not both edges
	GPIO_PORTA_IEV_R &= ~0x08; // PA3 falling edge event
	GPIO_PORTA_ICR_R &= ~0x08; // clear flag3
	GPIO_PORTA_IM_R |= 0x08; // arm interrupt on PA3
	NVIC_PRI0_R = (NVIC_PRI0_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
	NVIC_EN0_R |= 0x00000001; // (h) enable interrupt 0 in NVIC
	__enable_irq(); /* global enable IRQs */
}
