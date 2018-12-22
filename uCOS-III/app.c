/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : EHS
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define SERIAL_MAX_MSG_LEN 	255
#define MAX_INPUTS 			128

#define  APP_TEST_FAULT(err, err_code) 						\
	do {													\
		if ((err) != (err_code)) 							\
		{  													\
			_Error_Handler(__FILE__, __LINE__, err_code);	\
		}                                					\
	} while(0)


/*
*********************************************************************************************************
*                                            LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_MUTEX    LcdMutex;


/*
*********************************************************************************************************
*                                                 TCB
*********************************************************************************************************
*/

static  OS_TCB  StartupTaskTCB;
static  OS_TCB  MainTaskTCB;
static  OS_TCB  CommTaskTCB;
static  OS_TCB	AnalogTaskTCB;


/*
*********************************************************************************************************
*                                                STACKS
*********************************************************************************************************
*/

static  CPU_STK  StartupTaskStk[STARTUP_TASK_STK_SIZE];
static  CPU_STK  MainTaskStk[MAIN_TASK_STK_SIZE];
static  CPU_STK  CommTaskStk[COMM_TASK_STK_SIZE];
static	CPU_STK  AnalogTaskStk[ANALOG_TASK_STK_SIZE];


/*
*********************************************************************************************************
*                                                TASKS
*********************************************************************************************************
*/

static  void  StartupTask      	(void *p_arg);
static  void  MainTask       	(void *p_arg);
static  void  CommTask  		(void *p_arg);
static  void  AnalogTask		(void *p_arg);


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  CreateTasks     	(void);
static  void  CreateObjects     (void);
static 	void  StringAppend		(char cName[], char cInput);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int  main (void)
{
    OS_ERR  err;

    CPU_IntDis();                                               /* Disable all interrupts.                              */

    OSInit(&err);                                               /* Init uC/OS-III.                                      */
    
    LCD_Init();                                                 /* Init Graphical Liquid Crystal Display module         */

    USART2_Init(115200);										/* Init serial (USART2) communications					*/

    USART3_Init(115200);										/* Init serial (USART3) communications					*/

	ADC1_Configuration();										/* Init Analog-to-Digital Converter (ADC1)				*/

    OSTaskCreate((OS_TCB     *)&StartupTaskTCB,                 /* Create the startup task                              */
                 (CPU_CHAR   *)"Startup Task",
                 (OS_TASK_PTR )StartupTask,
                 (void       *)0,
                 (OS_PRIO     )STARTUP_TASK_PRIO,
                 (CPU_STK    *)&StartupTaskStk[0],
                 (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE / 10u,
                 (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE,
                 (OS_MSG_QTY  )5u,
                 (OS_TICK     )0u,
                 (void       *)0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
    APP_TEST_FAULT(err, OS_ERR_NONE);

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an startup task.
*
* Arguments   : p_arg   Unused.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  StartupTask      (void *p_arg)
{
   (void)p_arg;
   
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    OS_ERR      err;
   
    BSP_Init();                                                 /* Initialize BSP functions.                            */
    CPU_Init();                                                 /* Initialize uC/CPU services.                          */

    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
    cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        /* Determine nbr SysTick increments                     */
    OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */

    Mem_Init();                                                 /* Initialize Memory Management Module                  */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
    APP_TEST_FAULT(err, OS_ERR_NONE);
#endif
    
    CreateObjects();                                            /* Create kernel objects (semaphore, queue, etc.)       */
    CreateTasks();                                            	/* Create application tasks                             */
    
#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif
    
    OSTaskDel((OS_TCB   *)&StartupTaskTCB,                     	/* Delete task because its work is complete             */
              (OS_ERR   *)&err);
    APP_TEST_FAULT(err, OS_ERR_NONE);
    
    while (DEF_TRUE) {
        ;                                                       /* Should not get here!                                 */
    }
}


/*
*********************************************************************************************************
*                                          MAIN TASK
*
* Description : This is the main task.
*
* Arguments   : p_arg   Unused.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  MainTask       (void *p_arg)
{
    (void)p_arg;
    
    OS_ERR        err;
    OS_MSG_SIZE   mainMsg_size;
    char          *p_msg;
  
    while(DEF_TRUE) {                                          /* Task body, always written as an infinite loop.        */
        p_msg = (char *)OSTaskQPend((OS_TICK         )0,
									(OS_OPT          )OS_OPT_PEND_BLOCKING,
									(OS_MSG_SIZE    *)&mainMsg_size,
									(CPU_TS         *)NULL,
									(OS_ERR         *)&err);
        APP_TEST_FAULT(err, OS_ERR_NONE);

		USART_printf(USART3, "%s\r\n", p_msg);

		OSMutexPend((OS_MUTEX   *)&LcdMutex,
					(OS_TICK     )0,
					(OS_OPT      )OS_OPT_PEND_BLOCKING,
					(CPU_TS     *)NULL,
					(OS_ERR     *)&err);
	    APP_TEST_FAULT(err, OS_ERR_NONE);

        LCD_goto_XY(1, 1);
        LCD_printf("%s", p_msg);


        OSMutexPost((OS_MUTEX   *)&LcdMutex,
					(OS_OPT      )OS_OPT_POST_NONE,
					(OS_ERR     *)&err);
        APP_TEST_FAULT(err, OS_ERR_NONE);

        OSTimeDly((OS_TICK      )10,
                  (OS_OPT       )OS_OPT_TIME_DLY,
                  (OS_ERR      *)&err);
        APP_TEST_FAULT(err, OS_ERR_NONE);
    }
}


/*
*********************************************************************************************************
*                                          COMMUNICATION TASK
*
* Description : This is the communication task.
*
* Arguments   : p_arg   Unused.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  CommTask	    (void *p_arg)
{
    (void)p_arg;

    OS_ERR        	err;
    char 		  	cInput;
    char   			cName[MAX_INPUTS+1] = {'\0'};

    while(DEF_TRUE) {                                          /* Task body, always written as an infinite loop.        */
    	/* Wait until character received from serial port */
    	OSSemPend((OS_SEM	*)&RxSem,
    			  (OS_TICK	 )0,
    			  (OS_OPT	 )OS_OPT_POST_1,
				  (CPU_TS	*)NULL,
				  (OS_ERR	*)&err);
        APP_TEST_FAULT(err, OS_ERR_NONE);

		/* Read the character from terminal */
		cInput = USART_getchar(USART2);

		/* Append character from terminal to string */
		StringAppend(cName, cInput);

		/* Forward if ENTER was sent */
		if(cInput == '\r')
		{
			/* Forward the message to queue */
	        OSTaskQPost((OS_TCB	   *)&MainTaskTCB,
	                	(void      *)cName,
						(OS_MSG_SIZE)sizeof(void *),
						(OS_OPT     )OS_OPT_POST_FIFO,
						(OS_ERR    *)&err);
	        APP_TEST_FAULT(err, OS_ERR_NONE);
		}

        OSTimeDly((OS_TICK      )10,
                  (OS_OPT      	)OS_OPT_TIME_DLY,
                  (OS_ERR      *)&err);
        APP_TEST_FAULT(err, OS_ERR_NONE);
    }
}


/*
*********************************************************************************************************
*                                          ANALOG TASK
*
* Description : This is the task for analog functionalities. ADC1 is connected to kits potentiometer.
*
* Arguments   : p_arg   Unused.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AnalogTask	(void *p_arg)
{
	OS_ERR err;

	uint16_t ADC_Result;

	while(DEF_TRUE) {                                          /* Task body, always written as an infinite loop.        */
		ADC_Result = ADC_GetConversionValue(ADC1);

		OSMutexPend((OS_MUTEX   *)&LcdMutex,
					(OS_TICK     )500,
					(OS_OPT      )OS_OPT_PEND_BLOCKING,
					(CPU_TS     *)NULL,
					(OS_ERR     *)&err);
		APP_TEST_FAULT(err, (OS_ERR_NONE && OS_ERR_TIMEOUT));


		/* TODO: Figure out why LCD_printf (and GLCD_printf) won't print integers */
        LCD_goto_XY(1, 4);
        LCD_printf("ADC1: %u", ADC_Result);

        OSMutexPost((OS_MUTEX   *)&LcdMutex,
				(OS_OPT      )OS_OPT_POST_NONE,
				(OS_ERR     *)&err);
        APP_TEST_FAULT(err, OS_ERR_NONE);

		/* 100 ms delay between readings */
		OSTimeDlyHMSM((CPU_INT16U 	)0,
					  (CPU_INT16U 	)0,
					  (CPU_INT16U 	)0,
					  (CPU_INT16U 	)100,
	                  (OS_OPT      	)OS_OPT_TIME_HMSM_STRICT,
	                  (OS_ERR      *)&err);
	    APP_TEST_FAULT(err, OS_ERR_NONE);
	}
}


/*
*********************************************************************************************************
*                                      CREATE APPLICATION TASKS
*
* Description:  This function creates the application tasks.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

static  void  CreateTasks (void)
{
    OS_ERR err;
    
    OSTaskCreate((OS_TCB         *)&MainTaskTCB,
                 (CPU_CHAR       *)"Main Task",
                 (OS_TASK_PTR     )MainTask,
                 (void           *)0,
                 (OS_PRIO         )MAIN_TASK_PRIO,
                 (CPU_STK        *)&MainTaskStk[0],
                 (CPU_STK_SIZE    )MAIN_TASK_STK_SIZE / 10u,
                 (CPU_STK_SIZE    )MAIN_TASK_STK_SIZE,
                 (OS_MSG_QTY      )5u,
                 (OS_TICK         )0u,
                 (void           *)0,
                 (OS_OPT          )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR         *)&err);
    APP_TEST_FAULT(err, OS_ERR_NONE);
    
    OSTaskCreate((OS_TCB         *)&CommTaskTCB,
                 (CPU_CHAR       *)"Communication Task",
                 (OS_TASK_PTR     )CommTask,
                 (void           *)0,
                 (OS_PRIO         )COMM_TASK_PRIO,
                 (CPU_STK        *)&CommTaskStk[0],
                 (CPU_STK_SIZE    )COMM_TASK_STK_SIZE / 10u,
                 (CPU_STK_SIZE    )COMM_TASK_STK_SIZE,
                 (OS_MSG_QTY      )5u,
                 (OS_TICK         )0u,
                 (void           *)0,
                 (OS_OPT          )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR         *)&err);
    APP_TEST_FAULT(err, OS_ERR_NONE);

    OSTaskCreate((OS_TCB         *)&AnalogTaskTCB,
                 (CPU_CHAR       *)"Analog Task",
                 (OS_TASK_PTR     )AnalogTask,
                 (void           *)0,
                 (OS_PRIO         )ANALOG_TASK_PRIO,
                 (CPU_STK        *)&AnalogTaskStk[0],
                 (CPU_STK_SIZE    )ANALOG_TASK_STK_SIZE / 10u,
                 (CPU_STK_SIZE    )ANALOG_TASK_STK_SIZE,
                 (OS_MSG_QTY      )5u,
                 (OS_TICK         )0u,
                 (void           *)0,
                 (OS_OPT          )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR         *)&err);
    APP_TEST_FAULT(err, OS_ERR_NONE);
}


/*
*********************************************************************************************************
*                                      CREATE APPLICATION EVENTS
*
* Description:  This function creates the application kernel objects.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

static  void  CreateObjects (void)
{
    OS_ERR err;
    
    OSMutexCreate((OS_MUTEX  *)&LcdMutex,
                  (CPU_CHAR  *)"LCD Mutex",
                  (OS_ERR    *)&err);
    APP_TEST_FAULT(err, OS_ERR_NONE);

    OSSemCreate((OS_SEM	   *)&RxSem,
    			(CPU_CHAR  *)"Terminal RX Binary Semaphore",
				(OS_SEM_CTR	)0,
				(OS_ERR	   *)&err);
    APP_TEST_FAULT(err, OS_ERR_NONE);
}


/*
*********************************************************************************************************
*                                      APPEND CHARACTER TO STRING
*
* Description:  This function appends character to end of the string.
*
* Arguments   : cName   String to append to
*
* 				cInput	Character to append
*
* Returns     : none
*********************************************************************************************************
*/

static void StringAppend(char cName[], char cInput)
{
	/* Keep index value between function calls */
    static uint8_t iIndex = 0;

	/* Roll back the array if it's full */
	if(iIndex >= MAX_INPUTS)
	{
		/* Insert character to the array
		 * and reset index
		 */
		cName[iIndex] = cInput;
		iIndex = 0;
	}
	/* Else read character to the array */
	else
	{
		/* Insert character to the array
		 * and increment index by one
		 */
		cName[iIndex] = cInput;
		iIndex++;
	}
}
