/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : crc_regs.h
* Module Description: CRC (Cyclic Redundancy Check) Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue May 31 09:10:25 2011 % 
* %version:          2 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------*/
/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
09/24/11   1.0      LWW      Initial Creation
06/24/14   2        KMC 	 QAC cleanup                           10551  
******************************************************************************/

#ifndef CRC_REGS_H
#define CRC_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct crcctrlregs
{
	uint32 CRC_CTRL0;					/* 0x00 */
	uint32 : 32;						/* 0x04 */
	uint32 CRC_CTRL1;					/* 0x08 */
	uint32 : 32;						/* 0x0C */
	uint32 CRC_CTRL2;					/* 0x10 */
	uint32 : 32;						/* 0x14 */
	uint32 CRC_INTS;					/* 0x18 */
	uint32 : 32;						/* 0x1C */
	uint32 CRC_INTR;					/* 0x20 */
	uint32 : 32;						/* 0x24 */
	uint32 CRC_STATUS;					/* 0x28 */
	uint32 : 32;						/* 0x2C */
	uint32 CRC_INT_OFFSET_REG;			/* 0x30 */
	uint32 : 32;						/* 0x34 */
	uint32 CRC_BUSY;					/* 0x38 */
	uint32 : 32;						/* 0x3C */
	uint32 CRC_PCOUNT_REG1;				/* 0x40 */
	uint32 CRC_SCOUNT_REG1;				/* 0x44 */
	uint32 CRC_CURSEC_REG1;				/* 0x48 */
	uint32 CRC_WDTOPLD1;				/* 0x4C */
	uint32 CRC_BCTOPLD1;				/* 0x50 */
	uint32 : 32;						/* 0x54 */
	uint32 : 32;						/* 0x58 */
	uint32 : 32;						/* 0x5C */
	uint32 PSA_SIGREGL1;				/* 0x60 */
	uint32 PSA_SIGREGH1;				/* 0x64 */
	uint32 CRC_REGL1;					/* 0x68 */
	uint32 CRC_REGH1;					/* 0x6C */
	uint32 PSA_SECSIGREGL1;				/* 0x70 */
	uint32 PSA_SECSIGREGH1;				/* 0x74 */
	uint32 RAW_DATAREGL1;				/* 0x78 */
	uint32 RAW_DATAREGH1;				/* 0x7C */
	uint32 CRC_PCOUNT_REG2;				/* 0x80 */
	uint32 CRC_SCOUNT_REG2;				/* 0x84 */
	uint32 CRC_CURSEC_REG2;				/* 0x88 */
	uint32 CRC_WDTOPLD2;				/* 0x8C */
	uint32 CRC_BCTOPLD2;				/* 0x90 */
	uint32 : 32;						/* 0x94 */
	uint32 : 32;						/* 0x98 */
	uint32 : 32;						/* 0x9C */
	uint32 PSA_SIGREGL2;				/* 0xA0 */
	uint32 PSA_SIGREGH2;				/* 0xA4 */
	uint32 CRC_REGL2;					/* 0xA8 */
	uint32 CRC_REGH2;					/* 0xAC */
	uint32 PSA_SECSIGREGL2;				/* 0xB0 */
	uint32 PSA_SECSIGREGH2;				/* 0xB4 */
	uint32 RAW_DATAREGL2;				/* 0xB8 */
	uint32 RAW_DATAREGH2;				/* 0xBC */
	uint32 : 32;						/* 0xC0 */
	uint32 : 32;						/* 0xC4 */
	uint32 : 32;						/* 0xC8 */
	uint32 : 32;						/* 0xCC */
	uint32 : 32;						/* 0xD0 */
	uint32 : 32;						/* 0xD4 */
	uint32 : 32;						/* 0xD8 */
	uint32 : 32;						/* 0xDC */
	uint32 : 32;						/* 0xE0 */
	uint32 : 32;						/* 0xE4 */
	uint32 : 32;						/* 0xE8 */
	uint32 : 32;						/* 0xEC */
	uint32 : 32;						/* 0xF0 */
	uint32 : 32;						/* 0xF4 */
	uint32 : 32;						/* 0xF8 */
	uint32 : 32;						/* 0xFC */
	uint32 : 32;						/* 0x100 */
	uint32 : 32;						/* 0x104 */
	uint32 : 32;						/* 0x108 */
	uint32 : 32;						/* 0x10C */
	uint32 : 32;						/* 0x110 */
	uint32 : 32;						/* 0x114 */
	uint32 : 32;						/* 0x118 */
	uint32 : 32;						/* 0x11C */
	uint32 : 32;						/* 0x120 */
	uint32 : 32;						/* 0x124 */
	uint32 : 32;						/* 0x128 */
	uint32 : 32;						/* 0x12C */
	uint32 : 32;						/* 0x130 */
	uint32 : 32;						/* 0x134 */
	uint32 : 32;						/* 0x138 */
	uint32 : 32;						/* 0x13C */
	uint32 CRC_BUS_SEL;					/* 0x140 */
}crcctrlregs_t;


#define CRCCTRLREG ((crcctrlregs_t *)0xFE000000UL)


#endif

