/*****************************************************************************
* Copyright 2014 Nexteer
* Nexteer Confidential
*
* Module File Name  : mibspi_regs.h
* Module Description: MibSPI (Mulit-Buffered Serial Peripheral Interface) Peripheral Registers
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
* 06/24/14  2        KMC 	     QAC cleanup                                                                    10551  
*/

#ifndef MIBSPI_REGS_H
#define MIBSPI_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct mibspictrlregs
{
    uint32  GCR0;                 /* 0x0000: Global Control 0 */
    uint32                :  7U;
    uint32  ENA           :  1U;  /* 0x0004: MIBSPI Enable bit */
    uint32                :  7U;
    uint32  LB            :  1U;  /* 0x0005: Loop back bit */
    uint32                :  7U;
    uint32  PD            :  1U;  /* 0x0006: Power down bit */
    uint32  GCR1          :  8U;  /* 0x0007: Global Control 1 */
    uint32                :  7U;
    uint32  ENAHIGHZ      :  1U;  /* 0x0008: Enable HIGHZ outputs */
    uint32                :  7U;
    uint32  DMAREQEN      :  1U;  /* 0x0009: DMA Request enable */
    uint32  INT0          : 16U;  /* 0x000A: Interrupt Enable bits */
    uint32  LVL;                  /* 0x000C: Interrupt Level */
    uint32                :  7U;
    uint32  BUFINIT       :  1U;  /* 0x0010: Buffer inialisation active flag */
    uint32                :  8U;
    uint32  FLG           : 16U;  /* 0x0012: Interrupt flags */
    uint32  PCFUN;                /* 0x0014: Function Pin Enable */
    uint32  PCDIR;                /* 0x0018: Pin Direction */
    uint32  PCDIN;                /* 0x001C: Pin Input Latch */
    uint32  PCDOUT;               /* 0x0020: Pin Output Latch */
    uint32  PCSET;                /* 0x0024: Output Pin Set */
    uint32  PCCLR;                /* 0x0028: Output Pin Clr */
    uint32  PCPDR;                /* 0x002C: Open Drain Output Enable */
    uint32  PCDIS;                /* 0x0030: Pullup/Pulldown Disable */
    uint32  PCPSL;                /* 0x0034: Pullup/Pulldown Selection */
    uint32  DAT0;                 /* 0x0038: Transmit Data */
    uint32  DAT1;                 /* 0x003C: Transmit Data with Format and Chip Select */
    uint32  BUF;                  /* 0x0040: Receive Buffer */
    uint32  EMU;                  /* 0x0044: Emulation Receive Buffer */
    uint32  DELAY;                /* 0x0048: Delays */
    uint32  CSDEF;                /* 0x004C: Default Chip Select */
    uint32  FMT0;                 /* 0x0050: Data Format 0 */
    uint32  FMT1;                 /* 0x0054: Data Format 1 */
    uint32  FMT2;                 /* 0x0058: Data Format 2 */
    uint32  FMT3;                 /* 0x005C: Data Format 3 */
    uint32  INTVECT0;             /* 0x0060: Interrupt Vector 0 */
    uint32  INTVECT1;             /* 0x0064: Interrupt Vector 1 */
    uint32  SRSEL;                /* 0x0068: Slew Rate Select */
    uint32  PMCTRL;               /* 0x006C: Parrallel Mode Control */
    uint32  RAMACCESS     : 16U;  /* 0x0070: RX Ram Write Access Enable */
    uint32  MIBSPIE       : 16U;  /* 0x0072: MibSPI Enable */
    uint32  SETINTENARDY  : 16U;  /* 0x0074: Transfer Group Interrupt Enable Set Register */
    uint32  SETINTENASUS  : 16U;
    uint32  CLRINTENARDY  : 16U;  /* 0x0078: Transfer Group Interrupt Enable Clear Register */
    uint32  CLRINTENASUS  : 16U;
    uint32  SETINTLVLRDY  : 16U;  /* 0x007C: Transfer Group Interrupt Level Set Register */
    uint32  SETINTLVLSUS  : 16U;
    uint32  CLRINTLVLRDY  : 16U;  /* 0x0080: Transfer Group Interrupt Level Clear Register */
    uint32  CLRINTLVLSUS  : 16U;
    uint32  INTFLGRDY     : 16U;  /* 0x0084: Transfer Group Interrupt Flags */
    uint32  INTFLGSUS     : 16U;
    uint32                : 32U;
    uint32                : 32U;
    uint32  TICKCNT;              /* 0x0090: Tick Counter */
    uint32                :  3U;
    uint32  TGINSERVICE   :  5U;
    uint32                :  9U;
    uint32  LTGPEND       :  7U;  /* 0x0096: Transfer Group End Pointer */
    uint32                :  8U;
    uint32  TGCTRL[16U];          /* 0x0098 - 0x00D4: Transfer Group Control */
    uint32  DMACTRL[8U];          /* 0x00D8 - 0x00F4: DMA Control */
    uint32  DMACOUNT[8U];         /* 0x00F8 - 0x0114: DMA Count */
    uint32  DMACNTLEN;            /* 0x0118 - 0x0114: DMA Control length */
    uint32                : 32U;
    uint32                : 23U;
    uint32  PTESTEN       :  1U;
    uint32                :  4U;
    uint32  EDEN          :  4U;
    uint32  UERRSTAT;
    uint32  UERRADDRRX;
    uint32  UERRADDRTX;
    uint32  RXOVRN_BUF_ADDR;     /* 0x0130: */
    uint32  IOLPKTSTCR;          /* 0x0134: IO loopback */
    uint32  EXT_PRESCALE1;       /* 0x0138: */
    uint32  EXT_PRESCALE2;       /* 0x013C: */
} mibspictrlregs_t;


#define mibspiREG1 ((mibspictrlregs_t *)0xFFF7F400UL)
#define mibspiREG3 ((mibspictrlregs_t *)0xFFF7F800UL)
#define mibspiREG5 ((mibspictrlregs_t *)0xFFF7FC00UL)


typedef volatile struct mibspiRamBase
{
    struct
    {
     uint16  control;  /* tx buffer control */
     uint16  data;     /* tx buffer data    */
    } tx[128];
    struct
    {
	 uint16 flags;    /* rx buffer flags */
     uint16 data;     /* rx buffer data  */
    } rx[128];
} mibspiRAM_t;


#define mibspiRAM1 ((mibspiRAM_t *)0xFF0E0000UL)
#define mibspiRAM3 ((mibspiRAM_t *)0xFF0C0000UL)
#define mibspiRAM5 ((mibspiRAM_t *)0xFF0A0000UL)

#endif
