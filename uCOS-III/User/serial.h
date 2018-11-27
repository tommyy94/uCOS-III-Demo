/*
*********************************************************************************************************
*
*                                        SERIAL FUNCTIONS
*
* Filename      : serial.h
*********************************************************************************************************
* Note(s)       : (1) This module abstracts STM32F107VC UART. It aims to make it so simple that even
* 					  untrained monkey is capable of using it. Therefore it has seemingly duplicate
* 					  functions.
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

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include "stm32f10x.h"

#include <os.h>
#include <bsp.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/
#ifndef SERIAL_H_
#define SERIAL_H_


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

extern OS_Q		TermQ;


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

extern void USART2_Init(const uint32_t ulBaudrate);
extern void USART2_putchar(const char c);
extern void USART2_printf(const char *p_fmt, ...);
extern char USART2_getc(void);
extern void USART2_IRQHandler(void);

extern void USART3_Init(const uint32_t ulBaudrate);
extern void USART3_putchar(const char c);
extern void USART3_printf(const char *p_fmt, ...);
extern char USART3_getc(void);


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/


#endif                                                          /* End of SERIAL_H_                                     */