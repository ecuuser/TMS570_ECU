/*****************************************************************************
* Copyright 2014,2012 Nexteer
* Nexteer Confidential
*
* Module File Name  : iomm_regs.h
* Module Description: IOMM Multiplexing Control Module Registers
* Product           : Gen II Plus - EA3.0
* Author            : Lonnie Newton
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* %version:          3 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------*/
/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
07/03/12   1      	LN      	Initial Creation		  			CR5400
07/13/12   2      	LN      	General update for compiler			CR5400
06/24/14   3        KMC 	 	QAC cleanup                         CR10551  
******************************************************************************/
#ifndef IOMM_REGS_H
#define IOMM_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct iommregs_t
{
	uint32 REVISION_REG;				/* 0x00 */
	uint32 : 32U;          				/* 0x04 */
	uint32 : 32U;						/* 0x08 */
	uint32 : 32U;						/* 0x0C */
	uint32 : 32U;						/* 0x10 */
	uint32 : 32U;						/* 0x14 */
	uint32 : 32U;						/* 0x18 */
	uint32 : 32U;						/* 0x1C */
	uint32 BOOT_REG;					/* 0x20 */
	uint32 : 32U;						/* 0x24 */
	uint32 : 32U;						/* 0x28 */
	uint32 : 32U;						/* 0x2C */
	uint32 : 32U;						/* 0x30 */
	uint32 : 32U;						/* 0x34 */
	uint32 KICK_REG0;					/* 0x38 */
	uint32 KICK_REG1;					/* 0x3C */
	uint32 : 32U;						/* 0x40 */
	uint32 : 32U;						/* 0x44 */
	uint32 : 32U;						/* 0x48 */
	uint32 : 32U;						/* 0x4C */
	uint32 : 32U;						/* 0x50 */
	uint32 : 32U;						/* 0x54 */
	uint32 : 32U;						/* 0x58 */
	uint32 : 32U;						/* 0x5C */
	uint32 : 32U;						/* 0x60 */
	uint32 : 32U;						/* 0x64 */
	uint32 : 32U;						/* 0x68 */
	uint32 : 32U;						/* 0x6C */
	uint32 : 32U;						/* 0x70 */
	uint32 : 32U;						/* 0x74 */
	uint32 : 32U;						/* 0x78 */
	uint32 : 32U;						/* 0x7C */
	uint32 : 32U;						/* 0x80 */
	uint32 : 32U;						/* 0x84 */
	uint32 : 32U;						/* 0x88 */
	uint32 : 32U;						/* 0x8C */
	uint32 : 32U;						/* 0x90 */
	uint32 : 32U;						/* 0x94 */
	uint32 : 32U;						/* 0x98 */
	uint32 : 32U;						/* 0x9C */
	uint32 : 32U;						/* 0xA0 */
	uint32 : 32U;						/* 0xA4 */
	uint32 : 32U;						/* 0xA8 */
	uint32 : 32U;						/* 0xAC */
	uint32 : 32U;						/* 0xB0 */
	uint32 : 32U;						/* 0xB4 */
	uint32 : 32U;						/* 0xB8 */
	uint32 : 32U;						/* 0xBC */
	uint32 : 32U;						/* 0xC0 */
	uint32 : 32U;						/* 0xC4 */
	uint32 : 32U;						/* 0xC8 */
	uint32 : 32U;						/* 0xCC */
	uint32 : 32U;						/* 0xD0 */
	uint32 : 32U;						/* 0xD4 */
	uint32 : 32U;						/* 0xD8 */
	uint32 : 32U;						/* 0xDC */
	uint32 ERR_RAW_STATUS_REG;			/* 0xE0 */
	uint32 ERR_ENABLED_STATUS_REG;		/* 0xE4 */
	uint32 ERR_ENABLE_REG;				/* 0xE8 */
	uint32 ERR_ENABLE_CLR_REG;			/* 0xEC */
	uint32 : 32U;						/* 0xF0 */
	uint32 FAULT_ADDRESS_REG;			/* 0xF4 */
	uint32 FAULT_STATUS_REG;			/* 0xF8 */
	uint32 FAULT_CLEAR_REG;				/* 0xFC */
	uint32 : 32U;						/* 0x100 */
	uint32 : 32U;						/* 0x104 */
	uint32 : 32U;						/* 0x108 */
	uint32 : 32U;						/* 0x10C */
	uint32 PINMMR[31U];					/* 0x110-0x188 */
	uint32 : 32U;						/* 0x18C */
	uint32 : 32U;						/* 0x190 */
	uint32 : 32U;						/* 0x194 */
	uint32 : 32U;						/* 0x198 */
	uint32 : 32U;						/* 0x19C */
	uint32 : 32U;						/* 0x1A0 */
	uint32 : 32U;						/* 0x1A4 */
	uint32 : 32U;						/* 0x1A8 */
	uint32 : 32U;						/* 0x1AC */
	uint32 : 32U;						/* 0x1B0 */
	uint32 : 32U;						/* 0x1B4 */
	uint32 : 32U;						/* 0x1B8 */
	uint32 : 32U;						/* 0x1BC */
	uint32 : 32U;						/* 0x1C0 */
	uint32 : 32U;						/* 0x1C4 */
	uint32 : 32U;						/* 0x1C8 */
	uint32 : 32U;						/* 0x1CC */
	uint32 : 32U;						/* 0x1D0 */
	uint32 : 32U;						/* 0x1D4 */
	uint32 : 32U;						/* 0x1D8 */
	uint32 : 32U;						/* 0x1DC */
	uint32 : 32U;						/* 0x1E0 */
	uint32 : 32U;						/* 0x1E4 */
	uint32 : 32U;						/* 0x1E8 */
	uint32 : 32U;						/* 0x1EC */
	uint32 : 32U;						/* 0x1F0 */
	uint32 : 32U;						/* 0x1F4 */
	uint32 : 32U;						/* 0x1F8 */
	uint32 : 32U;						/* 0x1FC */
}iommregs_t;

#define IOMMREG ((iommregs_t *)0xFFFFEA00UL)


#endif


