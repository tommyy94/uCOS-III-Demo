/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2006
 *
 *    File name   : Terminal_6_8x6.c
 *    Description : Font Terminal 6 (8x6)
 *
 *    History :
 *    1. Date        : December 2, 2006
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 39 $
 **************************************************************************/
#include "drv_glcd.h"

static const unsigned char TextStream [] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x1c, 0x22, 0x36, 0x22, 0x2a, 0x22, 0x1c, 0x00,
		0x1c, 0x3e, 0x2a, 0x3e, 0x22, 0x3e, 0x1c, 0x00,
		0x00, 0x14, 0x3e, 0x3e, 0x3e, 0x1c, 0x08, 0x00,
		0x00, 0x08, 0x1c, 0x3e, 0x3e, 0x1c, 0x08, 0x00,
		0x08, 0x1c, 0x1c, 0x08, 0x3e, 0x3e, 0x08, 0x00,
		0x00, 0x08, 0x1c, 0x3e, 0x3e, 0x08, 0x1c, 0x00,
		0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00,
		0x3f, 0x3f, 0x3f, 0x33, 0x33, 0x3f, 0x3f, 0x3f,
		0x00, 0x00, 0x1e, 0x12, 0x12, 0x1e, 0x00, 0x00,
		0x3f, 0x3f, 0x21, 0x2d, 0x2d, 0x21, 0x3f, 0x3f,
		0x00, 0x38, 0x30, 0x2c, 0x12, 0x12, 0x0c, 0x00,
		0x1c, 0x22, 0x22, 0x1c, 0x08, 0x1c, 0x08, 0x00,
		0x08, 0x18, 0x28, 0x08, 0x0c, 0x0e, 0x06, 0x00,
		0x30, 0x2c, 0x34, 0x2c, 0x34, 0x36, 0x06, 0x00,
		0x00, 0x2a, 0x1c, 0x36, 0x1c, 0x2a, 0x00, 0x00,
		0x04, 0x0c, 0x1c, 0x3c, 0x1c, 0x0c, 0x04, 0x00,
		0x10, 0x18, 0x1c, 0x1e, 0x1c, 0x18, 0x10, 0x00,
		0x08, 0x1c, 0x3e, 0x08, 0x3e, 0x1c, 0x08, 0x00,
		0x14, 0x14, 0x14, 0x14, 0x14, 0x00, 0x14, 0x00,
		0x3c, 0x2a, 0x2a, 0x2c, 0x28, 0x28, 0x28, 0x00,
		0x1c, 0x22, 0x0c, 0x14, 0x18, 0x22, 0x1c, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x1e, 0x00,
		0x08, 0x1c, 0x3e, 0x08, 0x3e, 0x1c, 0x08, 0x1c,
		0x08, 0x1c, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x00,
		0x08, 0x08, 0x08, 0x08, 0x3e, 0x1c, 0x08, 0x00,
		0x00, 0x08, 0x18, 0x3e, 0x18, 0x08, 0x00, 0x00,
		0x00, 0x08, 0x0c, 0x3e, 0x0c, 0x08, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x3e, 0x00,
		0x00, 0x14, 0x14, 0x3e, 0x14, 0x14, 0x00, 0x00,
		0x08, 0x08, 0x1c, 0x1c, 0x3e, 0x3e, 0x00, 0x00,
		0x3e, 0x3e, 0x1c, 0x1c, 0x08, 0x08, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x08, 0x1c, 0x1c, 0x08, 0x08, 0x00, 0x08, 0x00,
		0x36, 0x36, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x14, 0x3e, 0x14, 0x14, 0x3e, 0x14, 0x00,
		0x04, 0x1c, 0x02, 0x0c, 0x10, 0x0e, 0x08, 0x00,
		0x26, 0x26, 0x10, 0x08, 0x04, 0x32, 0x32, 0x00,
		0x04, 0x0a, 0x0a, 0x04, 0x2a, 0x12, 0x2c, 0x00,
		0x0c, 0x0c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x00,
		0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x00,
		0x00, 0x14, 0x1c, 0x3e, 0x1c, 0x14, 0x00, 0x00,
		0x00, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x04,
		0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00,
		0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00,
		0x1c, 0x22, 0x32, 0x2a, 0x26, 0x22, 0x1c, 0x00,
		0x08, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x00,
		0x1c, 0x22, 0x20, 0x18, 0x04, 0x02, 0x3e, 0x00,
		0x1c, 0x22, 0x20, 0x1c, 0x20, 0x22, 0x1c, 0x00,
		0x10, 0x18, 0x14, 0x12, 0x3e, 0x10, 0x10, 0x00,
		0x3e, 0x02, 0x02, 0x1e, 0x20, 0x22, 0x1c, 0x00,
		0x18, 0x04, 0x02, 0x1e, 0x22, 0x22, 0x1c, 0x00,
		0x3e, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x00,
		0x1c, 0x22, 0x22, 0x1c, 0x22, 0x22, 0x1c, 0x00,
		0x1c, 0x22, 0x22, 0x3c, 0x20, 0x10, 0x0c, 0x00,
		0x00, 0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00,
		0x00, 0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x04,
		0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00,
		0x00, 0x00, 0x3e, 0x00, 0x00, 0x3e, 0x00, 0x00,
		0x04, 0x08, 0x10, 0x20, 0x10, 0x08, 0x04, 0x00,
		0x1c, 0x22, 0x20, 0x18, 0x08, 0x00, 0x08, 0x00,
		0x1c, 0x22, 0x3a, 0x2a, 0x3a, 0x02, 0x1c, 0x00,
		0x1c, 0x22, 0x22, 0x22, 0x3e, 0x22, 0x22, 0x00,
		0x1e, 0x22, 0x22, 0x1e, 0x22, 0x22, 0x1e, 0x00,
		0x1c, 0x22, 0x02, 0x02, 0x02, 0x22, 0x1c, 0x00,
		0x1e, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1e, 0x00,
		0x3e, 0x02, 0x02, 0x1e, 0x02, 0x02, 0x3e, 0x00,
		0x3e, 0x02, 0x02, 0x1e, 0x02, 0x02, 0x02, 0x00,
		0x1c, 0x22, 0x02, 0x3a, 0x22, 0x22, 0x3c, 0x00,
		0x22, 0x22, 0x22, 0x3e, 0x22, 0x22, 0x22, 0x00,
		0x1c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x00,
		0x20, 0x20, 0x20, 0x20, 0x22, 0x22, 0x1c, 0x00,
		0x22, 0x12, 0x0a, 0x06, 0x0a, 0x12, 0x22, 0x00,
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x3e, 0x00,
		0x22, 0x36, 0x2a, 0x22, 0x22, 0x22, 0x22, 0x00,
		0x22, 0x26, 0x2a, 0x32, 0x22, 0x22, 0x22, 0x00,
		0x1c, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x00,
		0x1e, 0x22, 0x22, 0x1e, 0x02, 0x02, 0x02, 0x00,
		0x1c, 0x22, 0x22, 0x22, 0x2a, 0x12, 0x2c, 0x00,
		0x1e, 0x22, 0x22, 0x1e, 0x12, 0x22, 0x22, 0x00,
		0x1c, 0x22, 0x02, 0x1c, 0x20, 0x22, 0x1c, 0x00,
		0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00,
		0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x00,
		0x22, 0x22, 0x22, 0x22, 0x22, 0x14, 0x08, 0x00,
		0x22, 0x22, 0x2a, 0x2a, 0x2a, 0x2a, 0x14, 0x00,
		0x22, 0x22, 0x14, 0x08, 0x14, 0x22, 0x22, 0x00,
		0x22, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x00,
		0x1e, 0x10, 0x08, 0x04, 0x02, 0x02, 0x1e, 0x00,
		0x1c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1c, 0x00,
		0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00,
		0x1c, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1c, 0x00,
		0x08, 0x14, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
		0x0c, 0x0c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x1c, 0x20, 0x3c, 0x22, 0x3c, 0x00,
		0x02, 0x02, 0x1e, 0x22, 0x22, 0x22, 0x1e, 0x00,
		0x00, 0x00, 0x1c, 0x22, 0x02, 0x22, 0x1c, 0x00,
		0x20, 0x20, 0x3c, 0x22, 0x22, 0x22, 0x3c, 0x00,
		0x00, 0x00, 0x1c, 0x22, 0x1e, 0x02, 0x1c, 0x00,
		0x18, 0x04, 0x04, 0x1e, 0x04, 0x04, 0x04, 0x00,
		0x00, 0x00, 0x3c, 0x22, 0x22, 0x3c, 0x20, 0x1c,
		0x02, 0x02, 0x0e, 0x12, 0x12, 0x12, 0x12, 0x00,
		0x08, 0x00, 0x08, 0x08, 0x08, 0x08, 0x18, 0x00,
		0x10, 0x00, 0x18, 0x10, 0x10, 0x10, 0x12, 0x0c,
		0x02, 0x02, 0x12, 0x0a, 0x06, 0x0a, 0x12, 0x00,
		0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x18, 0x00,
		0x00, 0x00, 0x16, 0x2a, 0x2a, 0x22, 0x22, 0x00,
		0x00, 0x00, 0x0e, 0x12, 0x12, 0x12, 0x12, 0x00,
		0x00, 0x00, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x00,
		0x00, 0x00, 0x1e, 0x22, 0x22, 0x22, 0x1e, 0x02,
		0x00, 0x00, 0x3c, 0x22, 0x22, 0x22, 0x3c, 0x20,
		0x00, 0x00, 0x1a, 0x24, 0x04, 0x04, 0x0e, 0x00,
		0x00, 0x00, 0x1c, 0x02, 0x1c, 0x20, 0x1c, 0x00,
		0x00, 0x04, 0x1e, 0x04, 0x04, 0x14, 0x08, 0x00,
		0x00, 0x00, 0x12, 0x12, 0x12, 0x1a, 0x14, 0x00,
		0x00, 0x00, 0x22, 0x22, 0x22, 0x14, 0x08, 0x00,
		0x00, 0x00, 0x22, 0x22, 0x2a, 0x3e, 0x14, 0x00,
		0x00, 0x00, 0x12, 0x12, 0x0c, 0x12, 0x12, 0x00,
		0x00, 0x00, 0x12, 0x12, 0x12, 0x1c, 0x08, 0x06,
		0x00, 0x00, 0x1e, 0x10, 0x0c, 0x02, 0x1e, 0x00,
		0x18, 0x04, 0x04, 0x06, 0x04, 0x04, 0x18, 0x00,
		0x08, 0x08, 0x08, 0x00, 0x08, 0x08, 0x08, 0x00,
		0x0c, 0x10, 0x10, 0x30, 0x10, 0x10, 0x0c, 0x00,
		0x14, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x08, 0x1c, 0x36, 0x22, 0x22, 0x3e, 0x00, 0x00,
		0x1c, 0x22, 0x02, 0x02, 0x22, 0x1c, 0x08, 0x0c,
		0x12, 0x00, 0x12, 0x12, 0x12, 0x1a, 0x14, 0x00,
		0x30, 0x00, 0x1c, 0x22, 0x1e, 0x02, 0x1c, 0x00,
		0x1c, 0x00, 0x1c, 0x20, 0x3c, 0x22, 0x3c, 0x00,
		0x14, 0x00, 0x1c, 0x20, 0x3c, 0x22, 0x3c, 0x00,
		0x0c, 0x00, 0x1c, 0x20, 0x3c, 0x22, 0x3c, 0x00,
		0x1c, 0x14, 0x1c, 0x20, 0x3c, 0x22, 0x3c, 0x00,
		0x00, 0x1c, 0x22, 0x02, 0x22, 0x1c, 0x08, 0x0c,
		0x1c, 0x00, 0x1c, 0x22, 0x1e, 0x02, 0x1c, 0x00,
		0x14, 0x00, 0x1c, 0x22, 0x1e, 0x02, 0x1c, 0x00,
		0x0c, 0x00, 0x1c, 0x22, 0x1e, 0x02, 0x1c, 0x00,
		0x14, 0x00, 0x08, 0x08, 0x08, 0x08, 0x18, 0x00,
		0x08, 0x14, 0x00, 0x08, 0x08, 0x08, 0x18, 0x00,
		0x04, 0x00, 0x08, 0x08, 0x08, 0x08, 0x18, 0x00,
		0x14, 0x00, 0x08, 0x14, 0x22, 0x3e, 0x22, 0x00,
		0x1c, 0x14, 0x1c, 0x36, 0x22, 0x3e, 0x22, 0x00,
		0x30, 0x00, 0x3e, 0x02, 0x1e, 0x02, 0x3e, 0x00,
		0x00, 0x00, 0x1e, 0x28, 0x3e, 0x0a, 0x3c, 0x00,
		0x3c, 0x0a, 0x0a, 0x3e, 0x0a, 0x0a, 0x3a, 0x00,
		0x1c, 0x00, 0x0c, 0x12, 0x12, 0x12, 0x0c, 0x00,
		0x14, 0x00, 0x0c, 0x12, 0x12, 0x12, 0x0c, 0x00,
		0x06, 0x00, 0x0c, 0x12, 0x12, 0x12, 0x0c, 0x00,
		0x1c, 0x00, 0x12, 0x12, 0x12, 0x1a, 0x14, 0x00,
		0x06, 0x00, 0x12, 0x12, 0x12, 0x1a, 0x14, 0x00,
		0x14, 0x00, 0x12, 0x12, 0x12, 0x1c, 0x08, 0x06,
		0x12, 0x0c, 0x12, 0x12, 0x12, 0x12, 0x0c, 0x00,
		0x14, 0x00, 0x12, 0x12, 0x12, 0x12, 0x0c, 0x00,
		0x00, 0x08, 0x1c, 0x02, 0x02, 0x1c, 0x08, 0x00,
		0x18, 0x24, 0x04, 0x1e, 0x04, 0x24, 0x3a, 0x00,
		0x22, 0x14, 0x08, 0x3e, 0x08, 0x3e, 0x08, 0x00,
		0x06, 0x0a, 0x0a, 0x16, 0x3a, 0x12, 0x12, 0x00,
		0x10, 0x28, 0x08, 0x1c, 0x08, 0x08, 0x0a, 0x04,
		0x18, 0x00, 0x1c, 0x20, 0x3c, 0x22, 0x3c, 0x00,
		0x18, 0x00, 0x08, 0x08, 0x08, 0x08, 0x18, 0x00,
		0x18, 0x00, 0x0c, 0x12, 0x12, 0x12, 0x0c, 0x00,
		0x18, 0x00, 0x12, 0x12, 0x12, 0x1a, 0x14, 0x00,
		0x14, 0x0a, 0x00, 0x0e, 0x12, 0x12, 0x12, 0x00,
		0x14, 0x0a, 0x00, 0x12, 0x16, 0x1a, 0x12, 0x00,
		0x1c, 0x20, 0x3c, 0x22, 0x3c, 0x00, 0x3c, 0x00,
		0x0c, 0x12, 0x12, 0x12, 0x0c, 0x00, 0x1e, 0x00,
		0x08, 0x00, 0x08, 0x0c, 0x02, 0x22, 0x1c, 0x00,
		0x00, 0x00, 0x3e, 0x02, 0x02, 0x02, 0x00, 0x00,
		0x00, 0x00, 0x3f, 0x20, 0x20, 0x00, 0x00, 0x00,
		0x02, 0x12, 0x0a, 0x1c, 0x22, 0x10, 0x38, 0x00,
		0x02, 0x12, 0x0a, 0x34, 0x2a, 0x38, 0x20, 0x00,
		0x08, 0x00, 0x08, 0x08, 0x1c, 0x1c, 0x08, 0x00,
		0x00, 0x00, 0x24, 0x12, 0x24, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x12, 0x24, 0x12, 0x00, 0x00, 0x00,
		0x2a, 0x00, 0x15, 0x00, 0x2a, 0x00, 0x15, 0x00,
		0x2a, 0x15, 0x2a, 0x15, 0x2a, 0x15, 0x2a, 0x15,
		0x15, 0x3f, 0x2a, 0x3f, 0x15, 0x3f, 0x2a, 0x3f,
		0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
		0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08,
		0x08, 0x0f, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08,
		0x0a, 0x0a, 0x0a, 0x0b, 0x0a, 0x0a, 0x0a, 0x0a,
		0x00, 0x00, 0x00, 0x0f, 0x0a, 0x0a, 0x0a, 0x0a,
		0x00, 0x0f, 0x08, 0x0f, 0x08, 0x08, 0x08, 0x08,
		0x0a, 0x0b, 0x08, 0x0b, 0x0a, 0x0a, 0x0a, 0x0a,
		0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
		0x00, 0x0f, 0x08, 0x0b, 0x0a, 0x0a, 0x0a, 0x0a,
		0x0a, 0x0b, 0x08, 0x0f, 0x00, 0x00, 0x00, 0x00,
		0x0a, 0x0a, 0x0a, 0x0f, 0x00, 0x00, 0x00, 0x00,
		0x08, 0x0f, 0x08, 0x0f, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x08,
		0x08, 0x08, 0x08, 0x38, 0x00, 0x00, 0x00, 0x00,
		0x08, 0x08, 0x08, 0x3f, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x3f, 0x08, 0x08, 0x08, 0x08,
		0x08, 0x08, 0x08, 0x38, 0x08, 0x08, 0x08, 0x08,
		0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00,
		0x08, 0x08, 0x08, 0x3f, 0x08, 0x08, 0x08, 0x08,
		0x08, 0x38, 0x08, 0x38, 0x08, 0x08, 0x08, 0x08,
		0x0a, 0x0a, 0x0a, 0x3a, 0x0a, 0x0a, 0x0a, 0x0a,
		0x0a, 0x3a, 0x02, 0x3e, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x3e, 0x02, 0x3a, 0x0a, 0x0a, 0x0a, 0x0a,
		0x0a, 0x3b, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x3f, 0x00, 0x3b, 0x0a, 0x0a, 0x0a, 0x0a,
		0x0a, 0x3a, 0x02, 0x3a, 0x0a, 0x0a, 0x0a, 0x0a,
		0x00, 0x3f, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00,
		0x0a, 0x3b, 0x00, 0x3b, 0x0a, 0x0a, 0x0a, 0x0a,
		0x08, 0x3f, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00,
		0x0a, 0x0a, 0x0a, 0x3f, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x3f, 0x00, 0x3f, 0x08, 0x08, 0x08, 0x08,
		0x00, 0x00, 0x00, 0x3f, 0x0a, 0x0a, 0x0a, 0x0a,
		0x0a, 0x0a, 0x0a, 0x3e, 0x00, 0x00, 0x00, 0x00,
		0x08, 0x38, 0x08, 0x38, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x38, 0x08, 0x38, 0x08, 0x08, 0x08, 0x08,
		0x00, 0x00, 0x00, 0x3e, 0x0a, 0x0a, 0x0a, 0x0a,
		0x0a, 0x0a, 0x0a, 0x3b, 0x0a, 0x0a, 0x0a, 0x0a,
		0x08, 0x3f, 0x00, 0x3f, 0x08, 0x08, 0x08, 0x08,
		0x08, 0x08, 0x08, 0x0f, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x38, 0x08, 0x08, 0x08, 0x08,
		0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
		0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f,
		0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
		0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
		0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x2c, 0x12, 0x12, 0x2c, 0x00, 0x00,
		0x00, 0x0e, 0x12, 0x0e, 0x12, 0x12, 0x0e, 0x02,
		0x1e, 0x12, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00,
		0x00, 0x3e, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00,
		0x1e, 0x12, 0x04, 0x08, 0x04, 0x12, 0x1e, 0x00,
		0x00, 0x00, 0x3c, 0x12, 0x12, 0x0c, 0x00, 0x00,
		0x00, 0x00, 0x12, 0x12, 0x12, 0x0e, 0x02, 0x02,
		0x00, 0x00, 0x14, 0x0a, 0x08, 0x08, 0x08, 0x00,
		0x1c, 0x08, 0x1c, 0x22, 0x1c, 0x08, 0x1c, 0x00,
		0x0c, 0x12, 0x12, 0x1e, 0x12, 0x12, 0x0c, 0x00,
		0x00, 0x1c, 0x22, 0x22, 0x14, 0x14, 0x36, 0x00,
		0x0c, 0x02, 0x04, 0x08, 0x1c, 0x12, 0x0c, 0x00,
		0x00, 0x00, 0x14, 0x2a, 0x2a, 0x14, 0x00, 0x00,
		0x00, 0x08, 0x1c, 0x2a, 0x2a, 0x1c, 0x08, 0x00,
		0x00, 0x1c, 0x02, 0x1e, 0x02, 0x1c, 0x00, 0x00,
		0x00, 0x0c, 0x12, 0x12, 0x12, 0x12, 0x00, 0x00,
		0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x00,
		0x00, 0x08, 0x1c, 0x08, 0x00, 0x1c, 0x00, 0x00,
		0x02, 0x0c, 0x10, 0x0c, 0x02, 0x00, 0x1e, 0x00,
		0x10, 0x0c, 0x02, 0x0c, 0x10, 0x00, 0x1e, 0x00,
		0x00, 0x10, 0x28, 0x08, 0x08, 0x08, 0x08, 0x08,
		0x08, 0x08, 0x08, 0x08, 0x08, 0x0a, 0x04, 0x00,
		0x00, 0x08, 0x00, 0x3e, 0x00, 0x08, 0x00, 0x00,
		0x00, 0x14, 0x0a, 0x00, 0x14, 0x0a, 0x00, 0x00,
		0x0c, 0x12, 0x12, 0x0c, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x38, 0x08, 0x08, 0x0a, 0x0a, 0x04, 0x00,
		0x0a, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00,
		0x06, 0x08, 0x04, 0x0e, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x1e, 0x1e, 0x1e, 0x1e, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

FontType_t Terminal_6_8_6 =
{
  6,
  8,
  0,
  255,
  (uint8_t *)TextStream,
  (uint8_t *)"Terminal 6 (8x6)"
};