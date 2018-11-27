/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2006
 *
 *    File name   : glcd_ll.h
 *    Description : GLCD low level include file
 *
 *    History :
 *    1. Date        : December 2, 2006
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 39 $
 **************************************************************************/
#include "includes.h"

#ifndef __GLCD_LL_H
#define __GLCD_LL_H

#define BACKLIGHT_OFF     0x00
#define BACKLIGHT_ON      0x80
#define SSP_FIFO_SIZE     8

#define GLCD_SPI_CLK      1000    // [kHz]
// LCD controller reset pin - PD2
#define LCD_RST_PORT      GPIOD
#define LCD_RST_MASK      GPIO_Pin_2

// LCD controller CS pin - PB14
#define LCD_CS_PORT       GPIOB
#define LCD_CS_MASK       GPIO_Pin_14

// LCD controller SPI pins - PC10, PA6, PA7
#define LCD_SPI_PORT      GPIOC
#define LCD_SPI_SCLK_MASK GPIO_Pin_10
#define LCD_SPI_MISO_MASK GPIO_Pin_11
#define LCD_SPI_MOSI_MASK GPIO_Pin_12

#define GLCD_SPI_MOSI_H() LCD_SPI_PORT->BSRR = LCD_SPI_MOSI_MASK
#define GLCD_SPI_MOSI_L() LCD_SPI_PORT->BRR  = LCD_SPI_MOSI_MASK
#define GLCD_SPI_CLK_H()  LCD_SPI_PORT->BSRR = LCD_SPI_SCLK_MASK
#define GLCD_SPI_CLK_L()  LCD_SPI_PORT->BRR  = LCD_SPI_SCLK_MASK
#define GLCD_SPI_MIS0()   (0 != (LCD_SPI_PORT->IDR & LCD_SPI_MISO_MASK))

/*************************************************************************
 * Function Name: GLCD_SetReset
 * Parameters: bool State
 * Return: none
 *
 * Description: Set reset pin state
 *
 *************************************************************************/
void GLCD_SetReset (bool State);

/*************************************************************************
 * Function Name: GLCD_SetBacklight
 * Parameters: uint8_t Light
 * Return: none
 *
 * Description: Set backlight pin state
 *
 *************************************************************************/
void GLCD_Backlight (uint8_t Light);

/*************************************************************************
 * Function Name: GLCD_LLInit
 * Parameters: none
 * Return: none
 *
 * Description: Init Reset and Backlight control outputs
 *
 *************************************************************************/
void GLCD_LLInit (void);

/*************************************************************************
 * Function Name: LcdSpiChipSelect
 * Parameters: bool Select
 * Return: none
 *
 * Description: SPI Chip select control
 * Select = true  - Chip is enable
 * Select = false - Chip is disable
 *
 *************************************************************************/
void GLCD_SPI_ChipSelect (bool Select);

/*************************************************************************
 * Function Name: LcdSpiSetWordWidth
 * Parameters: uint32_t Width
 * Return: bool
 *
 * Description: Set SPI word width
 *
 *************************************************************************/
bool GLCD_SPI_SetWordWidth (uint32_t Width);

/*************************************************************************
 * Function Name: LcdSpiSetClockFreq
 * Parameters: uint32_t Frequency
 * Return: uint32_t
 *
 * Description: Set SPI clock
 *
 *************************************************************************/
uint32_t GLCD_SPI_SetClockFreq (uint32_t Frequency);

/*************************************************************************
 * Function Name: GLCD_SPI_Init
 * Parameters: uint32_t Clk, uint32_t Width
 * Return: none
 *
 * Description: Init SPI
 *
 *************************************************************************/
void GLCD_SPI_Init(uint32_t Clk, uint32_t Width);

/*************************************************************************
 * Function Name: GLCD_SPI_TransferByte
 * Parameters: uint32_t Data
 * Return: uint32_t
 *
 * Description: Transfer byte from SPI
 *
 *************************************************************************/
uint32_t GLCD_SPI_TransferByte (uint32_t Data);

/*************************************************************************
 * Function Name: GLCD_SPI_SendBlock
 * Parameters: uint8_t *pData, uint32_t Size
 *
 * Return: void
 *
 * Description: Write block of data to SPI
 *
 *************************************************************************/
void GLCD_SPI_SendBlock (uint8_t *pData, uint32_t Size);

/*************************************************************************
 * Function Name: GLCD_SPI_ReceiveBlock
 * Parameters: uint8_t *pData, uint32_t Size
 *
 * Return: void
 *
 * Description: Read block of data from SPI
 *
 *************************************************************************/
void GLCD_SPI_ReceiveBlock (uint8_t *pData, uint32_t Size);

#endif // __GLCD_LL_H
