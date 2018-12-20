/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                           (c) Copyright 2009-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      APPLICATION CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                         Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : JJL
*                 EHS
*                 DC
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  STARTUP_TASK_PRIO                        	2
#define  MAIN_TASK_PRIO                         	3
#define  COMM_TASK_PRIO                    			3
#define	 ANALOG_TASK_PRIO							4


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  STARTUP_TASK_STK_SIZE                    	1024
#define  MAIN_TASK_STK_SIZE                     	256
#define  COMM_TASK_STK_SIZE                			128
#define	 ANALOG_TASK_STK_SIZE						256


#endif
