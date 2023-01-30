/*****************************************************************************
* Copyright 2014,2011 Nexteer
* Nexteer Confidential
*
* Module File Name  : esm_regs.h
* Module Description: ESM (Error Signaling Module) Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue May 31 09:10:19 2011
* %version:          2 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------*/
/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
05/31/11   1.0      LWW      Initial Creation
06/24/14   2        KMC 	 QAC cleanup                           10551  
******************************************************************************/

#ifndef ESM_REGS_H
#define ESM_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct esmregs
{
	uint32 ESMEEPAPR1;			/* 0x0000                 */
	uint32 ESMDEPAPR1;			/* 0x0004                 */
	uint32 ESMIESR1;			/* 0x0008                 */
	uint32 ESMIECR1;			/* 0x000C                 */
	uint32 ESMILSR1;			/* 0x0010                 */
	uint32 ESMILCR1;			/* 0x0014                 */
	uint32 ESMSR1;				/* 0x0018                 */
	uint32 ESMSR2;				/* 0x001C                 */
	uint32 ESMSR3;				/* 0x0020                 */
	uint32 ESMEPSR;				/* 0x0024                 */
	uint32 ESMIOFFHR;			/* 0x0028                 */
	uint32 ESMIOFFLR;			/* 0x002C                 */
	uint32 ESMLTCR;				/* 0x0030                 */
	uint32 ESMLTCPR;			/* 0x0034                 */
	uint32 ESMEKR;				/* 0x0038                 */
	uint32 ESMSSR2;				/* 0x003C                 */
	uint32 EPENASET4;			/* 0x0040                 */
	uint32 EPENACLR4;			/* 0x0044                 */
	uint32 INTENASET4;			/* 0x0048                 */
	uint32 INTENACLR4;			/* 0x004C                 */
	uint32 INTLVLSET4;			/* 0x0050                 */
	uint32 INTLVLCLR4;			/* 0x0054                 */
	uint32 ESTATUS4[3U];		/* 0x0058, 0x005C, 0x0060 */
	uint32 ESTATUS5EMU;			/* 0x0064                 */
	
} esmregs_t;

#define ESMREGS ((esmregs_t *)0xFFFFF500UL)

#endif

