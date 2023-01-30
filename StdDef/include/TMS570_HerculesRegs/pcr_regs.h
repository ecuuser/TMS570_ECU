/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : pcr_regs.h
* Module Description: PCR (Peripheral Central Resource) Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue May 31 09:10:25 2011 % 
* %version:          2 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------------------------------------------------
* Date      Rev      Author         Change Description                                                        SCR #
* -------   -------  --------  ---------------------------------------------------------------------------  ----------
* 06/24/14  2        KMC 	     QAC cleanup                                                                  10551  
*--------------------------------------------------------------------------------------------------------------------*/

#ifndef PCR_REGS_H
#define PCR_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct pcrctrlregs
{
    uint32 PMPROTSET0;    /* 0x0000 */
    uint32 PMPROTSET1;    /* 0x0004 */
    uint32 : 32U;         /* 0x0008 */
    uint32 : 32U;         /* 0x000C */
    uint32 PMPROTCLR0;    /* 0x0010 */
    uint32 PMPROTCLR1;    /* 0x0014 */
    uint32 : 32U;         /* 0x0018 */
    uint32 : 32U;         /* 0x001C */
    uint32 PPROTSET0;     /* 0x0020 */
    uint32 PPROTSET1;     /* 0x0024 */
    uint32 PPROTSET2;     /* 0x0028 */
    uint32 PPROTSET3;     /* 0x002C */
    uint32 : 32U;         /* 0x0030 */
    uint32 : 32U;         /* 0x0034 */
    uint32 : 32U;         /* 0x0038 */
    uint32 : 32U;         /* 0x003C */
    uint32 PPROTCLR0;     /* 0x0040 */
    uint32 PPROTCLR1;     /* 0x0044 */
    uint32 PPROTCLR2;     /* 0x0048 */
    uint32 PPROTCLR3;     /* 0x004C */
    uint32 : 32U;         /* 0x0050 */
    uint32 : 32U;         /* 0x0054 */
    uint32 : 32U;         /* 0x0058 */
    uint32 : 32U;         /* 0x005C */
    uint32 PCSPWRDWNSET0; /* 0x0060 */
    uint32 PCSPWRDWNSET1; /* 0x0064 */
    uint32 : 32U;         /* 0x0068 */
    uint32 : 32U;         /* 0x006C */
    uint32 PCSPWRDWNCLR0; /* 0x0070 */
    uint32 PCSPWRDWNCLR1; /* 0x0074 */
    uint32 : 32U;         /* 0x0078 */
    uint32 : 32U;         /* 0x007C */
    uint32 PSPWRDWNSET0;  /* 0x0080 */
    uint32 PSPWRDWNSET1;  /* 0x0084 */
    uint32 PSPWRDWNSET2;  /* 0x0088 */
    uint32 PSPWRDWNSET3;  /* 0x008C */
    uint32 : 32U;         /* 0x0090 */
    uint32 : 32U;         /* 0x0094 */
    uint32 : 32U;         /* 0x0098 */
    uint32 : 32U;         /* 0x009C */
    uint32 PSPWRDWNCLR0;  /* 0x00A0 */
    uint32 PSPWRDWNCLR1;  /* 0x00A4 */
    uint32 PSPWRDWNCLR2;  /* 0x00A8 */
    uint32 PSPWRDWNCLR3;  /* 0x00AC */
} pcrctrlregs_t;

#define pcrREG ((pcrctrlregs_t *)0xFFFFE000UL)

#endif
