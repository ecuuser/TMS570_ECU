/*****************************************************************************
* Copyright 2014,2011 Nexteer
* Nexteer Confidential
*
* Module File Name  : gio_regs.h
* Module Description: GIO (General-Purpose Input Output) Peripheral Registers
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue May 31 09:10:21 2011
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

#ifndef GIO_REGS_H
#define GIO_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct gioctrlregs
{
	uint32 GCR0;      /* 0x0000: Global Control Register */
	uint32 PWDN;      /* 0x0004: Power Down Register */
	uint32 INTDET;    /* 0x0008: Interrupt Detect Regsiter*/
	uint32 POL;       /* 0x000C: Interrupt Polarity Register */
	uint32 INTENASET; /* 0x0010: Interrupt Enable Set Register */
	uint32 INTENACLR; /* 0x0014: Interrupt Enable Clear Register */
	uint32 LVLSET;    /* 0x0018: Interrupt Priority Set Register */
	uint32 LVLCLR;    /* 0x001C: Interrupt Priority Clear Register */
	uint32 FLG;       /* 0x0020: Interrupt Flag Register */
	uint32 OFFA;      /* 0x0024: Interrupt Offset A Register */
	uint32 OFFB;      /* 0x0028: Interrupt Offset B Register */
	uint32 EMUA;      /* 0x002C: Emulation A Register */
	uint32 EMUB;      /* 0x0030: Emulation B Register */
} gioctrlregs_t;

typedef volatile struct gioPort
{
    uint32 DIR;    /**< 0x0000: Data Direction Register */
    uint32 DIN;    /**< 0x0004: Data Input Register */
    uint32 DOUT;   /**< 0x0008: Data Output Register */
    uint32 DSET;   /**< 0x000C: Data Output Set Register */
    uint32 DCLR;   /**< 0x0010: Data Output Clear Register */
    uint32 PDR;    /**< 0x0014: Open Drain Regsiter */
    uint32 PULDIS; /**< 0x0018: Pullup Disable Register */
    uint32 PSL;    /**< 0x001C: Pull Up/Down Selection Register */
} gioPORT_t;

#define gioCTRL ((gioctrlregs_t *)0xFFF7BC00UL)
#define gioPORTA ((gioPORT_t *)0xFFF7BC34UL)
#define gioPORTB ((gioPORT_t *)0xFFF7BC54UL)

#endif


