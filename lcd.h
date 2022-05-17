
/////////////////symbolic names for LCD commands////////////////
#define clear_display              0x01 
#define returnHome                 0x02 
#define cursorBlink                0x0F 
#define cursorOff                  0x0C 
#define cursorOn                   0x0E 
#define mode_4bit 				         0x28 
#define mode_8bit					         0x38          
#define FirstRowPosition0          0x80
#define FirstRowPosition1          0x81
#define FirstRowPosition2          0x82  // and so on
#define SecondRowPosition0         0xC0
#define SecondRowPosition1         0xC1
#define SecondRowPosition2         0xC2  // and so on
#define moveCursorRight            0x06
#define Set5x7FontSize    				 0x20
///////////////////////////////////////////////////////////////

/* LCD functions prototypes  */
void delay_milli(int n);                // make delay n mile second
void delay_micro(int n);                // make delay n micro second
void LCD_init(void);                    // must for initialize LCD (without it any function of LCD has no effect)
void LCD_Cmd(unsigned char command);    // send certain command to lcd
void LCD_Data(unsigned char data);      // send letter to be appeared in lcd 
void LCD_String (char *str);            // send string to be appeared in lcd
void LCD_Write(char *str);							//Function to write on LCD

