#include "stdint.h"

//Prototypes of Functions
void Start_Program(void);;								//Function to start program and intiliaze all ports
void PortFInit(void);											//Intilization of PORTF
unsigned char SW1_Input(void);						//Check if SW1 in TivaC is pressed or not
unsigned char SW2_Input(void);						//Check if SW2 in TivaC is pressed or not
unsigned char SW_Input(void);							//Check if SW1 and SW2 is pressed or not
void RGB_Output(unsigned char data);			//Turn ON, Turn OFF, Change Color of LEDS in TivaC
void SysTick_Wait_1ms(void);							//1ms Timer
void SysTick_Wait(uint32_t delay);				//1ms*delay Timer
void SW3_Buzzer_Init(void);								//Intilization of  SW3 and Buzzer
unsigned char SW3_Input(void);						//Check if SW3 is pressed or not
void Buzzer_Output(unsigned char data);		//Turn ON, Turn OFF Buzzer
void PortDInit(void);											//Intilization of PORTD that is connected to columns of KeyPad 4x4
void PortEInit(void);											//Intilization of PORTE that is connected to rows of KeyPad 4x4
void delay(uint32_t n);										//Micro seconds delay Function
char getKeyPad(void);											//Function checks and returns the value of key pressed in KeyPad 4x4
void delay_milli(int n);                // make delay n mile second
void delay_micro(int n);                // make delay n micro second
void LCD_init(void);                    // must for initialize LCD (without it any function of LCD has no effect)
void LCD_Cmd(unsigned char command);    // send certain command to lcd
void LCD_Data(unsigned char data);      // send letter to be appeared in lcd 
void LCD_String (char *str);            // send string to be appeared in lcd
void LCD_Write(char *str);							//function to clear what is on lcd and write new string
void Start_Cooking(short time_sec,char *str);			//function to start the cooking of microwave
void Start_timer(short time_sec,char *str);				//function to start count down of timer and know number of minutes and seconds
void Write_Timer(short time4, short time3, short time2, short time1, char *str);	//function to write timer on lcd and the state
void Write_Timer_zero(void);						//function to write zeros whether in IDLE state or clearing time
void Enter_kilo(char s, char *str);								//function to enter no. of kilo of the beef of chicken
void Cooking_time(char *str);						//function used in state of cooking time "D" to let user enter time for cooking
void flag_stop(void);							// a function used to stop cooking and return to IDLE state
void flag_resume(void);						//a function used to resume cooking
char flag_restart(void);				// a function used in cooking time state to restart entering time
void SW1_Interrupt(void);				//function to intiliaze interrupt for SW1
void SW3_Interrupt(void);		//function to intiliaze interrupt in SW3
