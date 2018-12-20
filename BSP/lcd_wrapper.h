/*
*********************************************************************************************************
*
*                                        LIQUID CRYSTAL DISPLAY FUNCTIONS
*
* Filename      : serial.h
*********************************************************************************************************
* Note(s)       : (1) This module abstracts GLCD.
*
*********************************************************************************************************
* Notice(s)     : (1) None.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include "drv_glcd.h"


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifndef LCD_WRAPPER_H_
#define LCD_WRAPPER_H_


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

extern void LCD_Init(void);
extern void LCD_putchar(const char c);
extern void LCD_printf(const char *fmt, ...);
extern void LCD_ClearDisplay(void);
extern void LCD_goto_XY(const uint8_t x, const uint8_t y);


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#endif                                                          /* End of LCD_WRAPPER_H_                                 */

