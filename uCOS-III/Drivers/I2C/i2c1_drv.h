/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2009
 *
 *    File name   : i2c1_drv.h
 *    Description : I2C1 Master mode driver include file
 *
 *    History :
 *    1. Date        : September 8, 2009
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 4262 $
 **************************************************************************/
#include "includes.h"
#include "atomic_operations.h"

#ifndef __I2C1_DRV_H
#define __I2C1_DRV_H

#ifdef  I2C1_DRV_GLOBAL
#define I2C1_DRV_EXTERN
#else
#define I2C1_DRV_EXTERN  extern
#endif

#define I2C1_SPEED          100000
#define I2C1_INTR_SUBPRIO   1
#define I2C1_INTR_PRIO      0


/*************************************************************************
 * Function Name: I2C1_ErrIntrHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: I2C1 error interrupt handler
 *
 *************************************************************************/
void I2C1_ErrIntrHandler(void);

/*************************************************************************
 * Function Name: I2C1_EvnIntrHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: I2C1 event interrupt handler
 *
 *************************************************************************/
void I2C1_EvnIntrHandler(void);

/*************************************************************************
 * Function Name: I2C1_Init
 * Parameters: none
 *
 * Return: none
 *
 * Description: Init I2C1 interface
 *
 *************************************************************************/
void I2C1_Init (void);

/*************************************************************************
 * Function Name: I2C1_Open
 * Parameters: none
 *
 * Return: bool
 *
 * Description: Init I2C1 interface open
 *
 *************************************************************************/
bool I2C1_Open (void);

/*************************************************************************
 * Function Name: I2C1_Close
 * Parameters: none
 *
 * Return: none
 *
 * Description: Init I2C1 interface release
 *
 *************************************************************************/
void I2C1_Close (void);

/*************************************************************************
 * Function Name: I2C1_DataTransfer
 * Parameters: uint8_t SlaveAddr, uint8_t *pData, uint32_t Size
 *
 * Return: none
 *
 * Description: I2C1 transfer data to/from slave
 *
 *************************************************************************/
bool I2C1_DataTransfer (uint8_t SlaveAddr, uint8_t *pData, uint32_t Size);

#endif // __I2C1_DRV_H
