/*
*********************************************************************************************************
*
*                                        SERIAL FUNCTIONS
*
* Filename      : serial.c
*********************************************************************************************************
* Note(s)       : (1) This module abstracts STM32F107VC UART.
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

#include "serial.h"


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define SERIAL_MAX_MSG_LEN 	255


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

OS_Q		TermQ;
OS_SEM		RxSem;


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

__STATIC_INLINE void USART2_NVIC_Configuration(void);
__STATIC_INLINE void USART3_NVIC_Configuration(void);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      INITIALIZE USART2
*
* Description:  Initializes USART2.
*
* Arguments  :  baudrate		Used baudrate.
*
* Returns    :  none
*********************************************************************************************************
*/

void USART2_Init(const uint32_t ulBaudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* Release reset and enable clock */
    USART_DeInit(USART2);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /* Enable GPIO clock and release reset */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, DISABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);

    /* Assign PD5 to UART2 (Tx) */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* USART2 configured as follow:
     - BaudRate = x baud
     - Word Length = 8 Bits
     - One Stop Bit
     - No parity
     - HW flow control disabled
     - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = ulBaudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);

    USART2_NVIC_Configuration();

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}


/*
*********************************************************************************************************
*                                      INITIALIZE USART3
*
* Description:  Initializes USART3.
*
* Arguments  :  baudrate		Used baudrate.
*
* Returns    :  none
*********************************************************************************************************
*/

void USART3_Init(const uint32_t ulBaudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* Release reset and enable clock */
    USART_DeInit(USART3);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    /* Enable GPIO clock and release reset */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, DISABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);

    /* Assign PD8 to UART3 (Tx) */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* USART3 configured as follow:
     - BaudRate = x baud
     - Word Length = 8 Bits
     - One Stop Bit
     - No parity
     - HW flow control disabled
     - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = ulBaudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);

    USART3_NVIC_Configuration();

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}


/*
*********************************************************************************************************
*                                      CONFIGURE NESTED VECTORED INTERRUPT CONTROLLER
*
* Description:  This function configures NVIC for USART2.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/
__STATIC_INLINE void USART2_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


/*
*********************************************************************************************************
*                                      CONFIGURE NESTED VECTORED INTERRUPT CONTROLLER
*
* Description:  This function configures NVIC for USART3.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/
__STATIC_INLINE void USART3_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the USART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


/*
*********************************************************************************************************
*                                      SEND CHARACTER TO SERIAL PORT
*
* Description:  This function sends character via USART2. It is blocking function.
*
* Arguments  :  c 			Character to send
*
* Returns    :  none
*********************************************************************************************************
*/

void USART_putchar(USART_TypeDef* USARTx, const char cCharacter)
{
	/* Wait until TX buffer is empty */
    while (!(USARTx->SR & USART_FLAG_TXE));

    /* Send character */
    USARTx->DR = (cCharacter & 0x1FF);
}


/*
*********************************************************************************************************
*                                      SEND STRING TO SERIAL PORT
*
* Description:  This function sends printf formatted string to serial port via USART2.
*
* Arguments  :  fmt 		String to send with format tags
*
* Returns    :  none
*********************************************************************************************************
*/

void USART_printf(USART_TypeDef* USARTx, const char *p_fmt, ...)
{
    char string[SERIAL_MAX_MSG_LEN];
    va_list xArgp;

	/* Initialize variable arguments */
    va_start(xArgp, p_fmt);

	/* Format string */
    if(vsprintf(string, p_fmt, xArgp) > 0)
    {
		/* Send the formatted string */
    	for(uint8_t i = 0; i < strlen(string); i++)
    	{
    		USART_putchar(USARTx, string[i]);
    	}
    }

    va_end(xArgp);
}


/*
*********************************************************************************************************
*                                      READ CHARACTER FROM SERIAL PORT
*
* Description:  This function reads character from serial port via USART2.
*
* Arguments  :  none
*
* Returns    :  c				Character read from serial port.
*********************************************************************************************************
*/

char USART_getchar(USART_TypeDef* USARTx)
{
	/* Read terminal */
	char cInput = USART_ReceiveData(USARTx);

	/* Echo back typed character */
	USART_putchar(USARTx, cInput);

	/* Send newline as well if ENTER is sent */
	if(cInput == '\r')
	{
		USART_putchar(USART2, '\n');
	}

	return (cInput);
}


/*
*********************************************************************************************************
*                                      USART2 INTERRUPT REQUEST HANDLER
*
* Description:  This IRQ Handler reads character from terminal and forwards it to a task
* 				if it detects carriage return (\r).
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

void USART2_IRQHandler(void)
{
    OS_ERR        		err;

    /* Save the CPU registers */
    CPU_SR_ALLOC();

    /* Enter a critical section */
    CPU_CRITICAL_ENTER();

    /* Tell the kernel that the interrupt has started */
    OSIntEnter();

    CPU_CRITICAL_EXIT();

	/* Check for RX interrupt */
    if ((USART2->SR & USART_FLAG_RXNE) != (u16)RESET)
    {
    	/* Signal RX */
    	OSSemPost((OS_SEM 	*)&RxSem,
    			  (OS_OPT	 )OS_OPT_POST_1,
				  (OS_ERR 	*)&err);
		if(err != OS_ERR_NONE) {
			_Error_Handler(__FILE__, __LINE__, &err);
		}

		/* Clear the peripheral pending bit */
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }

    /* Tell the kernel that the interrupt has ended */
    OSIntExit();
}


/*
*********************************************************************************************************
*                                      USART2 INTERRUPT REQUEST HANDLER
*
* Description:  This IRQ Handler reads character from terminal and forwards it to a task
* 				if it detects carriage return (\r).
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

void USART3_IRQHandler(void)
{
    OS_ERR        		err;

    /* Save the CPU registers */
    CPU_SR_ALLOC();

    /* Enter a critical section */
    CPU_CRITICAL_ENTER();

    /* Tell the kernel that the interrupt has started */
    OSIntEnter();

    CPU_CRITICAL_EXIT();

	/* Check for RX interrupt */
    if ((USART3->SR & USART_FLAG_RXNE) != (u16)RESET)
    {
    	/* Signal RX */
    	OSSemPost((OS_SEM 	*)&RxSem,
    			  (OS_OPT	 )OS_OPT_POST_1,
				  (OS_ERR 	*)&err);
		if(err != OS_ERR_NONE) {
			_Error_Handler(__FILE__, __LINE__, &err);
		}

		/* Clear the peripheral pending bit */
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }

    /* Tell the kernel that the interrupt has ended */
    OSIntExit();
}
