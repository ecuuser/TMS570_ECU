/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : dma_regs.h
* Module Description: DMA (Direct Memory Access) Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
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
09/24/11   1.0      LWW      Initial Creation
06/24/14   3        KMC 	    QAC cleanup                        CR10551  
******************************************************************************/
#ifndef DMA_REGS_H
#define DMA_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct dmactrlregs
{
	uint32 GCTRL;					/* 0x00 */
	uint32 PEND;					/* 0x04 */
	uint32 : 32;					/* 0x08 */
	uint32 DMASTAT;					/* 0x0C */
	uint32 : 32;					/* 0x10 */
	uint32 HWCHENAS;				/* 0x14 */
	uint32 : 32;					/* 0x18 */
	uint32 HWCHENAR;				/* 0x1C */
	uint32 : 32;					/* 0x20 */
	uint32 SWCHENAS;				/* 0x24 */
	uint32 : 32;					/* 0x28 */
	uint32 SWCHENAR;				/* 0x2C */
	uint32 : 32;					/* 0x30 */
	uint32 CHPRIOS;					/* 0x34 */
	uint32 : 32;					/* 0x38 */
	uint32 CHPRIOR;					/* 0x3C */
	uint32 : 32;					/* 0x40 */
	uint32 GCHIENAS;				/* 0x44 */
	uint32 : 32;					/* 0x48 */
	uint32 GCHIENAR;				/* 0x4C */
	uint32 : 32;					/* 0x50 */
	uint32 					:  2U;	/* 0x54 */
    uint32 DREQASI0_CH0ASI	:  6U;
    uint32 					:  2U;
    uint32 DREQASI0_CH1ASI  :  6U;
    uint32 					:  2U;
    uint32 DREQASI0_CH2ASI	:  6U;
    uint32 					:  2U;
    uint32 DREQASI0_CH3ASI  :  6U;
	uint32 					:  2U;	/* 0x58 */
    uint32 DREQASI1_CH4ASI	:  6U;
    uint32 					:  2U;
    uint32 DREQASI1_CH5ASI  :  6U;
    uint32 					:  2U;
    uint32 DREQASI1_CH6ASI	:  6U;
    uint32 					:  2U;
    uint32 DREQASI1_CH7ASI  :  6U;
	uint32 					:  2U;	/* 0x5C */
    uint32 DREQASI2_CH8ASI	:  6U;
    uint32 					:  2U;
    uint32 DREQASI2_CH9ASI  :  6U;
    uint32 					:  2U;
    uint32 DREQASI2_CH10ASI	:  6U;
    uint32 					:  2U;
    uint32 DREQASI2_CH11ASI :  6U;
	uint32 					:  2U;	/* 0x60 */
    uint32 DREQASI3_CH12ASI	:  6U;
    uint32 					:  2U;
    uint32 DREQASI3_CH13ASI :  6U;
    uint32 					:  2U;
    uint32 DREQASI3_CH14ASI	:  6U;
    uint32 					:  2U;
    uint32 DREQASI3_CH15ASI :  6U;
	uint32 : 32;				/* 0x64 */
	uint32 : 32;				/* 0x68 */
	uint32 : 32;				/* 0x6C */
	uint32 : 32;				/* 0x70 */
	uint32 : 32;				/* 0x74 */
	uint32 : 32;				/* 0x78 */
	uint32 : 32;				/* 0x7C */
	uint32 : 32;				/* 0x80 */
	uint32 : 32;				/* 0x84 */
	uint32 : 32;				/* 0x88 */
	uint32 : 32;				/* 0x8C */
	uint32 : 32;				/* 0x90 */
	uint32 PAR0;				/* 0x94 */
	uint32 PAR1;				/* 0x98 */
	uint32 : 32;				/* 0x9C */
	uint32 : 32;				/* 0xA0 */
	uint32 : 32;				/* 0xA4 */
	uint32 : 32;				/* 0xA8 */
	uint32 : 32;				/* 0xAC */
	uint32 : 32;				/* 0xB0 */
	uint32 FTCMAP;				/* 0xB4 */
	uint32 : 32;				/* 0xB8 */
	uint32 LFSMAP;				/* 0xBC */
	uint32 : 32;				/* 0xC0 */
	uint32 HBCMAP;				/* 0xC4 */
	uint32 : 32;				/* 0xC8 */
	uint32 BTCMAP;				/* 0xCC */
	uint32 : 32;				/* 0xD0 */
	uint32 BERMAP;				/* 0xD4 */
	uint32 : 32;				/* 0xD8 */
	uint32 FTCINTENAS;			/* 0xDC */
	uint32 : 32;				/* 0xE0 */
	uint32 FTCINTENAR;			/* 0xE4 */
	uint32 : 32;				/* 0xE8 */
	uint32 LFSINTENAR;			/* 0xEC */
	uint32 : 32;				/* 0xF0 */
	uint32 LFSINTENAS;			/* 0xF4 */
	uint32 : 32;				/* 0xF8 */
	uint32 HBCINTENAR;			/* 0xFC */
	uint32 : 32;				/* 0x100 */
	uint32 HBCINTENAS;			/* 0x104 */
	uint32 : 32;				/* 0x108 */
	uint32 BTCINTENAS;			/* 0x10C */
	uint32 : 32;				/* 0x110 */
	uint32 BTCINTENAR;			/* 0x114 */
	uint32 : 32;				/* 0x118 */
	uint32 GINTFLAG;			/* 0x11C */
	uint32 : 32;				/* 0x120 */
	uint32 FTCFLAG;				/* 0x124 */
	uint32 : 32;				/* 0x128 */
	uint32 LFSFLAG;				/* 0x12C */
	uint32 : 32;				/* 0x130 */
	uint32 HBCFLAG;				/* 0x134 */
	uint32 : 32;				/* 0x138 */
	uint32 BTCFLAG;				/* 0x13C */
	uint32 : 32;				/* 0x140 */
	uint32 BERFLAG;				/* 0x144 */
	uint32 : 32;				/* 0x148 */
	uint32 FTCAOFFSET;			/* 0x14C */
	uint32 LFSAOFFSET;			/* 0x150 */
	uint32 HBCAOFFSET;			/* 0x154 */
	uint32 BTCAOFFSET;			/* 0x158 */
	uint32 BERAOFFSET;			/* 0x15C */
	uint32 FTCBOFFSET;			/* 0x160 */
	uint32 LFSBOFFSET;			/* 0x164 */
	uint32 HBCBOFFSET;			/* 0x168 */
	uint32 BTCBOFFSET;			/* 0x16C */
	uint32 BERBOFFSET;			/* 0x170 */
	uint32 : 32;				/* 0x174 */
	uint32 PTCRL;				/* 0x178 */
	uint32 RTCTRL;				/* 0x17C */
	uint32 DCTRL;				/* 0x180 */
	uint32 WPR;					/* 0x184 */
	uint32 WMR;					/* 0x188 */
	uint32 : 32;				/* 0x18C */
	uint32 : 32;				/* 0x190 */
	uint32 : 32;				/* 0x194 */
	uint32 PBACSADDR;			/* 0x198 */
	uint32 PBACDADDR;			/* 0x19C */
	uint32 PBACTC;				/* 0x1A0 */
	uint32 : 32;				/* 0x1A4 */
	uint32 DMAPCR;				/* 0x1A8 */
	uint32 DMAPAR;				/* 0x1AC */
	uint32 DMAMPCTRL;			/* 0x1B0 */
	uint32 DMAMPST;				/* 0x1B4 */
	uint32 DMAMPR0S;			/* 0x1B8 */
	uint32 DMAMPR0E;			/* 0x1BC */
	uint32 DMAMPR1S;			/* 0x1C0 */
	uint32 DMAMPR1E;			/* 0x1C4 */
	uint32 DMAMPR2S;			/* 0x1C8 */
	uint32 DMAMPR2E;			/* 0x1CC */
	uint32 DMAMPR3S;			/* 0x1D0 */
	uint32 DMAMPR3E;			/* 0x1D4 */
	
}dmactrlregs_t;

typedef volatile struct dmactrlpkt
{
	uint32 ISADDR;				/* 0x00 */
	uint32 IDADDR;				/* 0x04 */
	uint32 ITCOUNT;				/* 0x08 */
	uint32 : 32;				/* 0x0C */
	uint32 CHCTRL;				/* 0x10 */
	uint32 EIOFF;				/* 0x14 */
	uint32 FIOFF;				/* 0x18 */
	uint32 : 32;				/* 0x1C */
}dmactrlpkt_t;

#define DMACTRLREG   ((dmactrlregs_t *)0xFFFFF000UL)
#define DMACTRLPKT00 ((dmactrlpkt_t *)0xFFF80000UL)
#define DMACTRLPKT01 ((dmactrlpkt_t *)0xFFF80020UL)
#define DMACTRLPKT02 ((dmactrlpkt_t *)0xFFF80040UL)
#define DMACTRLPKT03 ((dmactrlpkt_t *)0xFFF80060UL)
#define DMACTRLPKT04 ((dmactrlpkt_t *)0xFFF80080UL)
#define DMACTRLPKT05 ((dmactrlpkt_t *)0xFFF800A0UL)
#define DMACTRLPKT06 ((dmactrlpkt_t *)0xFFF800C0UL)
#define DMACTRLPKT07 ((dmactrlpkt_t *)0xFFF800E0UL)
#define DMACTRLPKT08 ((dmactrlpkt_t *)0xFFF80100UL)
#define DMACTRLPKT09 ((dmactrlpkt_t *)0xFFF80120UL)
#define DMACTRLPKT10 ((dmactrlpkt_t *)0xFFF80140UL)
#define DMACTRLPKT11 ((dmactrlpkt_t *)0xFFF80160UL)
#define DMACTRLPKT12 ((dmactrlpkt_t *)0xFFF80180UL)
#define DMACTRLPKT13 ((dmactrlpkt_t *)0xFFF801A0UL)
#define DMACTRLPKT14 ((dmactrlpkt_t *)0xFFF801C0UL)
#define DMACTRLPKT15 ((dmactrlpkt_t *)0xFFF801E0UL)

#endif


