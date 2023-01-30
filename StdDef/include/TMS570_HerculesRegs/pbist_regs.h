/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : pbist_regs.h
* Module Description: PBIST (Programmable Built-In Self-Test) Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue May 31 09:10:25 2011 % 
* %version:          3 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------------------------------------------------
* Date      Rev      Author         Change Description                                                        SCR #
* -------   -------  --------  ---------------------------------------------------------------------------  ----------
* 06/24/14  3        KMC 	     QAC cleanup                                                                  10551  
*--------------------------------------------------------------------------------------------------------------------*/

#ifndef PBIST_REGS_H
#define PBIST_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct pbistctrlregs
{
    uint32 RAMT;		/* 0x0160: RAM Configuration Register */
    uint32 DLR;			/* 0x0164: Datalogger Register */
    uint32 rsvd1[6U];	/* 0x0168, 0x016C, 0x0170, 0x0174, 0x0178, 0x017C */
    uint32 PACT;		/* 0x0180: PBIST Activate Register */
    uint32 PBISTID;		/* 0x0184: PBIST ID Register */
    uint32 OVER;		/* 0x0188: Override Register */
    uint32 rsvd2;		/* 0x018C */
    uint32 FSRF0;		/* 0x0190: Fail Status Fail Register 0 */
	uint32 FSRF1;		/* 0x0194: Fail Status Fail Register 1 */
    uint32 FSRC0;		/* 0x0198: Fail Status Count Register 0 */
    uint32 FSRC1;		/* 0x019C: Fail Status Count Register 1 */
    uint32 FSRA0;		/* 0x01A0: Fail Status Address 0 Register */
    uint32 FSRA1;		/* 0x01A4: Fail Status Address 1 Register */
    uint32 FSRDL0;		/* 0x01A8: Fail Status Data Register 0 */
    uint32 rsvd3;		/* 0x01AC */
    uint32 FSRDL1;		/* 0x01B0: Fail Status Data Register 1 */
    uint32 rsvd4[3U];	/* 0x01B4, 0x01B8, 0x01BC */
    uint32 ROM;			/* 0x01C0: ROM Mask Register */
    uint32 ALGO;		/* 0x01C4: Algorithm Mask Register */
    uint32 RINFOL;		/* 0x01C8: RAM Info Mask Lower Register */
    uint32 RINFOU;		/* 0x01CC: RAM Info Mask Upper Register */
} pbistctrlregs_t;

#define pbistREG   ((pbistctrlregs_t *)0xFFFFE560UL)

#endif
