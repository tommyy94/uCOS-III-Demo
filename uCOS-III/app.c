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


/*
*********************************************************************************************************
*                                            LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_Q        AppQ;
static  OS_MUTEX    AppMutex;


/*
*********************************************************************************************************
*                                                 TCB
*********************************************************************************************************
*/

static  OS_TCB  AppTaskStartTCB;
static  OS_TCB  AppTaskMainTCB;
static  OS_TCB  AppTaskSecondaryTCB;
static  OS_TCB  AppTaskCommTCB;


/*
*********************************************************************************************************
*                                                STACKS
*********************************************************************************************************
*/

static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];
static  CPU_STK  AppTaskMainStk[APP_TASK_MAIN_STK_SIZE];
static  CPU_STK  AppTaskSecondaryStk[APP_TASK_SECONDARY_STK_SIZE];
static  CPU_STK  AppTaskCommStk[APP_TASK_COMM_STK_SIZE];


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskCreate     (void);
static  void  AppObjCreate      (void);
static  void  AppTaskStart      (void *p_arg);
static  void  AppTaskMain       (void *p_arg);
static  void  AppTaskSecondary  (void *p_arg);
static  void  AppTaskComm  		(void *p_arg);


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

    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task Start",
                 (OS_TASK_PTR )AppTaskStart,
                 (void       *)0,
                 (OS_PRIO     )APP_TASK_START_PRIO,
                 (CPU_STK    *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE)APP_TASK_START_STK_SIZE / 10u,
                 (CPU_STK_SIZE)APP_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  )5u,
                 (OS_TICK     )0u,
                 (void       *)0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
    if(err != OS_ERR_NONE) {
        _Error_Handler(__FILE__, __LINE__, &err);
    }

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart      (void *p_arg)
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
    if(err != OS_ERR_NONE) {
        _Error_Handler(__FILE__, __LINE__, &err);
    }
#endif
    
    AppObjCreate();                                             /* Create kernel objects (semaphore, queue, etc.)       */
    AppTaskCreate();                                            /* Create application tasks                             */
    
#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif
    
    OSTaskDel((OS_TCB   *)&AppTaskStartTCB,                     /* Delete task because its work is complete             */
              (OS_ERR   *)&err);
    if(err != OS_ERR_NONE) {
        _Error_Handler(__FILE__, __LINE__, &err);
    }
    
    while (DEF_TRUE) {
        ;                                                       /* Should not get here!                                 */
    }
}


static  void  AppTaskMain       (void *p_arg)
{
    (void)p_arg;
    
    OS_ERR  err;
    
    char msg[] = "Message passing by..";
  
    while(DEF_TRUE) {                                          /* Task body, always written as an infinite loop.        */
        OSQPost((OS_Q      *)&AppQ,
                (void      *)msg,
                (OS_MSG_SIZE)sizeof(void *),
                (OS_OPT     )OS_OPT_POST_FIFO,
                (OS_ERR    *)&err);
        if(err != OS_ERR_NONE) {
            _Error_Handler(__FILE__, __LINE__, &err);
        }
        
        OSTimeDly((OS_TICK      )10,
                  (OS_OPT       )OS_OPT_TIME_DLY,
                  (OS_ERR      *)&err);
        if(err != OS_ERR_NONE) {
            _Error_Handler(__FILE__, __LINE__, &err);
        }
    }
}


static  void  AppTaskSecondary  (void *p_arg)
{
    (void)p_arg;
    
    OS_ERR        err;
    CPU_TS        ts;
    CPU_TS        ts_delta;
    OS_MSG_SIZE   mainMsg_size;
    void          *p_msg;
  
    while(DEF_TRUE) {                                          /* Task body, always written as an infinite loop.        */
        p_msg = OSQPend((OS_Q           *)&AppQ,
                        (OS_TICK         )0,
                        (OS_OPT          )OS_OPT_PEND_BLOCKING,
                        (OS_MSG_SIZE    *)&mainMsg_size,
                        (CPU_TS         *)&ts,
                        (OS_ERR         *)&err);
        if(err != OS_ERR_NONE) {
            _Error_Handler(__FILE__, __LINE__, &err);
        }
        
        ts_delta = OS_TS_GET() - ts;

		USART3_printf("%s\r\n", p_msg);

		OSMutexPend((OS_MUTEX   *)&AppMutex,
					(OS_TICK     )0,
					(OS_OPT      )OS_OPT_PEND_BLOCKING,
					(CPU_TS     *)&ts,
					(OS_ERR     *)&err);
		if(err != OS_ERR_NONE) {
			_Error_Handler(__FILE__, __LINE__, &err);
		}

        LCD_goto_XY(1, 1);
        LCD_printf("%s", p_msg);

        OSMutexPost((OS_MUTEX   *)&AppMutex,
				(OS_OPT      )OS_OPT_POST_NONE,
				(OS_ERR     *)&err);
		if(err != OS_ERR_NONE) {
			_Error_Handler(__FILE__, __LINE__, &err);
		}

        OSTimeDly((OS_TICK      )10,
                  (OS_OPT       )OS_OPT_TIME_DLY,
                  (OS_ERR      *)&err);
    }
}


#define MAX_INPUTS 			128
static  void  AppTaskComm	    (void *p_arg)
{
    (void)p_arg;

    OS_ERR        	err;
    CPU_TS        	ts;
    CPU_TS        	ts_delta;
    OS_MSG_SIZE	  	termMsg_size;
    void          	*p_termMsg;

    while(DEF_TRUE) {                                          /* Task body, always written as an infinite loop.        */
        p_termMsg = OSQPend((OS_Q           *)&TermQ,
                        	(OS_TICK         )0,
							(OS_OPT          )OS_OPT_PEND_BLOCKING,
							(OS_MSG_SIZE    *)&termMsg_size,
							(CPU_TS         *)&ts,
							(OS_ERR         *)&err);
        if(err != OS_ERR_NONE)
        {
            _Error_Handler(__FILE__, __LINE__, &err);
        }

		OSMutexPend((OS_MUTEX   *)&AppMutex,
					(OS_TICK     )0,
					(OS_OPT      )OS_OPT_PEND_BLOCKING,
					(CPU_TS     *)&ts,
					(OS_ERR     *)&err);
		if(err != OS_ERR_NONE) {
			_Error_Handler(__FILE__, __LINE__, &err);
		}

		LCD_goto_XY(1, 3);
		LCD_printf("%s", p_termMsg);

		OSMutexPost((OS_MUTEX   *)&AppMutex,
					(OS_OPT      )OS_OPT_POST_NONE,
					(OS_ERR     *)&err);
		if(err != OS_ERR_NONE) {
			_Error_Handler(__FILE__, __LINE__, &err);
		}

        ts_delta = OS_TS_GET() - ts;

        OSTimeDly((OS_TICK      )10,
                  (OS_OPT       )OS_OPT_TIME_DLY,
                  (OS_ERR      *)&err);
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

static  void  AppTaskCreate (void)
{
    OS_ERR err;
    
    OSTaskCreate((OS_TCB         *)&AppTaskMainTCB,
                 (CPU_CHAR       *)"App Task Main",
                 (OS_TASK_PTR     )AppTaskMain,
                 (void           *)0,
                 (OS_PRIO         )APP_TASK_MAIN_PRIO,
                 (CPU_STK        *)&AppTaskMainStk[0],
                 (CPU_STK_SIZE    )APP_TASK_MAIN_STK_SIZE / 10u,
                 (CPU_STK_SIZE    )APP_TASK_MAIN_STK_SIZE,
                 (OS_MSG_QTY      )5u,
                 (OS_TICK         )0u,
                 (void           *)0,
                 (OS_OPT          )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR         *)&err);
    if(err != OS_ERR_NONE) {
            _Error_Handler(__FILE__, __LINE__, &err);
    }
    
    OSTaskCreate((OS_TCB         *)&AppTaskSecondaryTCB,
                 (CPU_CHAR       *)"App Task Secondary",
                 (OS_TASK_PTR     )AppTaskSecondary,
                 (void           *)0,
                 (OS_PRIO         )APP_TASK_SECONDARY_PRIO,
                 (CPU_STK        *)&AppTaskSecondaryStk[0],
                 (CPU_STK_SIZE    )APP_TASK_SECONDARY_STK_SIZE / 10u,
                 (CPU_STK_SIZE    )APP_TASK_SECONDARY_STK_SIZE,
                 (OS_MSG_QTY      )5u,
                 (OS_TICK         )0u,
                 (void           *)0,
                 (OS_OPT          )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR         *)&err);
    if(err != OS_ERR_NONE) {
        _Error_Handler(__FILE__, __LINE__, &err);
    }

    OSTaskCreate((OS_TCB         *)&AppTaskCommTCB,
                 (CPU_CHAR       *)"App Task Communication",
                 (OS_TASK_PTR     )AppTaskComm,
                 (void           *)0,
                 (OS_PRIO         )APP_TASK_COMM_PRIO,
                 (CPU_STK        *)&AppTaskCommStk[0],
                 (CPU_STK_SIZE    )APP_TASK_COMM_STK_SIZE / 10u,
                 (CPU_STK_SIZE    )APP_TASK_COMM_STK_SIZE,
                 (OS_MSG_QTY      )5u,
                 (OS_TICK         )0u,
                 (void           *)0,
                 (OS_OPT          )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR         *)&err);
    if(err != OS_ERR_NONE) {
        _Error_Handler(__FILE__, __LINE__, &err);
    }
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

static  void  AppObjCreate (void)
{
    OS_ERR err;
    
    OSMutexCreate((OS_MUTEX  *)&AppMutex,
                  (CPU_CHAR  *)"My AppMutex",
                  (OS_ERR    *)&err);
    if(err != OS_ERR_NONE) {
        _Error_Handler(__FILE__, __LINE__, &err);
    }
    
    OSQCreate((OS_Q        *)&AppQ,
              (CPU_CHAR    *)"Main queue",
              (OS_MSG_QTY   )10,
              (OS_ERR      *)&err);
    if(err != OS_ERR_NONE) {
        _Error_Handler(__FILE__, __LINE__, &err);
    }

    OSQCreate((OS_Q        *)&TermQ,
              (CPU_CHAR    *)"Terminal queue",
              (OS_MSG_QTY   )10,
              (OS_ERR      *)&err);
    if(err != OS_ERR_NONE) {
        _Error_Handler(__FILE__, __LINE__, &err);
    }
}
