/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include "lcd_wrapper.h"


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define LCD_MAX_MSG_LEN 	255
#define LCD_RESET_DLY_US	50


/*
*********************************************************************************************************
*                                      INITIALIZE LCD
*
* Description:  Initializes the LCD.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

extern void LCD_Init(void)
{
    GLCD_PowerUpInit((uint8_t *)0);
    GLCD_SetFont(&Terminal_9_12_6, 0x000F00, 0x00FF0);
    DelayResolution100us(LCD_RESET_DLY_US);
    GLCD_Backlight(BACKLIGHT_ON);
}


/*
*********************************************************************************************************
*                                      PRINT CHARACTER TO LCD
*
* Description:  This function is used to display a character in LCD.
*
* Arguments  :  c 			Character to print
*
* Returns    :  none
*********************************************************************************************************
*/

extern void LCD_putchar(const char c)
{
	GLCD_putchar(c);
}


/*
*********************************************************************************************************
*                                      PRINT STRING TO LCD
*
* Description:  This function prints printf formatted string to LCD.
*
* Arguments  :  fmt 		String to print with format tags
*
* Returns    :  none
*********************************************************************************************************
*/

extern void LCD_printf(const char *fmt, ...)
{
	char string[LCD_MAX_MSG_LEN];
	va_list args;

	/* Initialize variable arguments */
	va_start(args, fmt);

	/* Format string */
	if(vsprintf(string, fmt, args) > 0)
	{
		/* Send formatted string */
		for(uint32_t i = 0; i < strlen(string); i++)
		{
			LCD_putchar(string[i]);
		}
	}

	va_end(args);
}


/*
*********************************************************************************************************
*                                      CLEAR DISPLAY
*
* Description:  This function clear the LCD.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

extern void LCD_ClearDisplay(void)
{
	LCD_putchar('\f');
}


/*
*********************************************************************************************************
*                                      PRINT CHARACTER TO LCD
*
* Description:  This function moves the LCD cursor.
*
* Arguments  :  x 			X coordinate
*
* 			 :	y			Y coordinate
*
* Returns    :  none
*********************************************************************************************************
*/

extern void LCD_goto_XY(const uint8_t x, const uint8_t y)
{
	GLCD_TextSetPos(x, y);
}
