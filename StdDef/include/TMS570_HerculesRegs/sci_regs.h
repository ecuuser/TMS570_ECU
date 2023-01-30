/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : sci_regs.h
* Module Description: SCI (Serial Communication Interface) Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu May 23 14:59:11 2013 % 
* %version:          2 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------*/
/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
05/23/13   1.0      LWW      Initial Creation
06/24/14   2        KMC 	 QAC cleanup                           10551  
******************************************************************************/

#ifndef SCI_REGS_H
#define SCI_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct scictrlregs
{
	uint32 GCR0;					/* 0x00 */
	uint32 GCR1;					/* 0x04 */
	uint32 GCR2;					/* 0x08 */
	uint32 SETINT;					/* 0x0C */
	uint32 CLRINT;					/* 0x10 */
	uint32 SETINTLVL;				/* 0x14 */
	uint32 CLRINTLVL;				/* 0x18 */
	uint32 FLR;						/* 0x1C */
	uint32 INTVECT0;				/* 0x20 */
	uint32 INTVECT1;				/* 0x24 */
	uint32 LENGTH;					/* 0x28 */
	uint32 BAUD;					/* 0x2C */
	uint32 : 24U;					/* 0x30 */
    uint8 ED;						/* 0x33 */
    uint32 : 24U;					/* 0x34 */
    uint8 RD;						/* 0x37 */
    uint32 : 24U;					/* 0x38 */
    uint8 TD;						/* 0x3B */
	uint32 FUN;						/* 0x3C */
	uint32 DIR;						/* 0x40 */
	uint32 DIN;						/* 0x44 */
	uint32 DOUT;					/* 0x48 */
	uint32 SET;						/* 0x4C */
	uint32 CLR;						/* 0x50 */
	uint32 ODR;						/* 0x54 */
	uint32 PD;						/* 0x58 */
	uint32 PSL;						/* 0x5C */	
}scictrlregs_t;

#define sciREG1 ((scictrlregs_t *)0xFFF7E400UL)
#define sciREG2 ((scictrlregs_t *)0xFFF7E500UL)

#endif

