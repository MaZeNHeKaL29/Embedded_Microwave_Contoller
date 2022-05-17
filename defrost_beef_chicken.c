#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "shortcut.h"
#include "functions_prototype.h"

/*



BEEF STATE

CHICKEN STATE


*/

//function to enter no. of kilo of the beef of chicken
void Enter_kilo(char s, char *str)
{
	short c;						//variable to represent symbol pressed on keypad
	short check = 1;		//variable used to check and exit while loop
	//while loop to enter no. of kilo and check if number entered is valid or not
	while (check)
	{
		if (s == 'B')								//check if the food entered is beef
		{
			LCD_Write("Beef Weight?");	//write "Beef Weight? on lcd
			delay_milli(500);
		}
		else if (s == 'C')					//check if the food entered is chicken
		{
			LCD_Write("Chicken Weight?");		//write "Chicken Weight? on lcd
			delay_milli(500);
		}
		c = 0;
		//wait for the user to enter the number if kilo
		while (c == 0)
		{
			c = getKeyPad();	//c => symbol pressed
		}
		//check if the symbol entered is a number between 1 to 9 or not
		if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == '#' || c == '0' || c == '*')
		{
			LCD_Cmd(clear_display);        //clear whatever is written on display 
			LCD_Write("Err..");			//write "Err.." on lcd
			SysTick_Wait(2000);			//wait 2 sec
		}
		//check if the symbol entered is a number between 1 to 9 or not
		else if(c > 0)
		{
			LCD_Cmd(clear_display);	//clear display on lcd
			LCD_Data(c + '0');	//write no. of kilo entered
			LCD_Write("Kilo");	//write kilo on lcd
			SysTick_Wait(2000);	//wait 2 sec
			LCD_Cmd(clear_display);	//clear display on lcd
			if (s == 'B')						//check if the food entered is beef
				Start_Cooking(30 * c,str); //Beef is defrosted at a rate of 0.5 minutes per kilo.
			else if (s == 'C')			//check if the food entered is chicken
				Start_Cooking(12 * c,str); //Chicken is defrosted at a rate of 0.2 minutes per kilo.
			check = 0;							//exit while loop
		}
	}
}
