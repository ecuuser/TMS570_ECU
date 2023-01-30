/*****************************************************************************
* Copyright 2014, 2010 Nexteer
* Nexteer Confidential
*
* Module File Name  : rti_regs.h
* Module Description: RTI (Real-Time Interrupt) Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue Dec 14 14:58:07 2010
* %version:          2 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------------------------------------------------
* Date      Rev      Author         Change Description                                                        SCR #
* -------   -------  --------  ---------------------------------------------------------------------------  ----------
* 06/24/14  2        KMC 	     QAC cleanup                                                                  10551  
*--------------------------------------------------------------------------------------------------------------------*/

#ifndef RTI_REGS_H
#define RTI_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct rtictrlregs
{
    uint32 GCTRL;          /* 0x0000: Global Control Register   */
    uint32 TBCTRL;         /* 0x0004: Timebase Control Register */
    uint32 CAPCTRL;        /* 0x0008: Capture Control Register  */
    uint32 COMPCTRL;       /* 0x000C: Compare Control Register  */
    struct
    {
        uint32 FRCx;       /* 0x0010,0x0030: Free Running Counter x Register         */
        uint32 UCx;        /* 0x0014,0x0034: Up Counter x Register                   */
        uint32 CPUCx;      /* 0x0018,0x0038: Compare Up Counter x Register           */
        uint32 : 32;       /* 0x001C,0x003C: Reserved                                */
        uint32 CAFRCx;     /* 0x0020,0x0040: Capture Free Running Counter x Register */
        uint32 CAUCx;      /* 0x0024,0x0044: Capture Up Counter x Register           */
        uint32 : 32;       /* 0x0028,0x0048: Reserved                                */
        uint32 : 32;       /* 0x002C,0x004C: Reserved                                */
    } CNT[2U];               /* Counter x selection:
                                    - 0: Counter 0
                                    - 1: Counter 1                                       */
    struct
    {
        uint32 COMPx;      /* 0x0050,0x0058,0x0060,0x0068: Compare x Register        */
        uint32 UDCPx;      /* 0x0054,0x005C,0x0064,0x006C: Update Compare x Register */
    } CMP[4U];               /* Compare x selection:
                                    - 0: Compare 0 
                                    - 1: Compare 1
                                    - 2: Compare 2
                                    - 3: Compare 3                                       */
    uint32 TBLCOMP;        /* 0x0070: External Clock Timebase Low Compare Register   */
    uint32 TBHCOMP;        /* 0x0074: External Clock Timebase High Compare Register  */
    uint32 : 32;           /* 0x0078: Reserved                                       */
    uint32 : 32;           /* 0x007C: Reserved                                       */
    uint32 SETINT;         /* 0x0080: Set/Status Interrupt Register                  */
    uint32 CLEARINT;       /* 0x0084: Clear/Status Interrupt Register                */
    uint32 INTFLAG;        /* 0x0088: Interrupt Flag Register                        */
    uint32 : 32;           /* 0x008C: Reserved                                       */
    uint32 DWDCTRL;        /* 0x0090: Digital Watchdog Control Register   */
    uint32 DWDPRLD;        /* 0x0094: Digital Watchdog Preload Register */
    uint32 WDSTATUS;       /* 0x0098: Watchdog Status Register  */
    uint32 WDKEY;          /* 0x009C: Watchdog Key Register  */
    uint32 DWDCNTR;        /* 0x00A0: Digital Watchdog Down Counter   */
    uint32 WWDRXNCTRL;     /* 0x00A4: Digital Windowed Watchdog Reaction Control */
    uint32 WWDSIZECTRL;    /* 0x00A8: Digital Windowed Watchdog Window Size Control  */
    uint32 INTCLRENABLE;   /* 0x00AC: RTI Compare Interrupt Clear Enable Register  */
    uint32 COMP0CLR;       /* 0x00B0: RTI Compare 0 Clear Register   */
    uint32 COMP1CLR;       /* 0x00B4: RTI Compare 1 Clear Register */
    uint32 COMP2CLR;       /* 0x00B8: RTI Compare 2 Clear Register  */
    uint32 COMP3CLR;       /* 0x00BC: RTI Compare 3 Clear Register  */
} rtictrlregs_t;

#define rtiREG1 ((rtictrlregs_t *)0xFFFFFC00UL)

#endif
