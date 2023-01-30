/*****************************************************************************
* Copyright 2014, 2010 Nexteer
* Nexteer Confidential
*
* Module File Name  : stc_regs.h
* Module Description: STC (CPU Self-Test Controller) Peripheral Registers
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

#ifndef STC_REGS_H
#define STC_REGS_H

/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"

typedef volatile struct stcctrlregs
{
    uint32 STCGCR0;		/**< 0x0000: STC Control Register 0	*/
    uint32 STCGCR1;		/**< 0x0004: STC Control Register 1 */
    uint32 STCTPR;		/**< 0x0008: STC Self-Test Run Timeout Counter Preload Register	*/
    uint32 STCCADDR;		/**< 0x000C: STC Self-Test Current ROM Address Register */
    uint32 STCCICR;		/**< 0x0010: STC Self-Test Current Interval Count Register */
    uint32 STCGSTAT;		/**< 0x0014: STC Self-Test Global Status Register */
	uint32 STCFSTAT;		/**< 0x0018: STC Self-Test Fail Status Register */
    uint32 CPU1_CURMISR3;	/**< 0x001C: STC CPU1 Current MISR Register */
    uint32 CPU1_CURMISR2;	/**< 0x0020: STC CPU1 Current MISR Register */
    uint32 CPU1_CURMISR1;	/**< 0x0024: STC CPU1 Current MISR Register */
    uint32 CPU1_CURMISR0;	/**< 0x0028: STC CPU1 Current MISR Register */
    uint32 CPU2_CURMISR3;	/**< 0x002C: STC CPU1 Current MISR Register */
    uint32 CPU2_CURMISR2;	/**< 0x0030: STC CPU1 Current MISR Register */
    uint32 CPU2_CURMISR1;	/**< 0x0034: STC CPU1 Current MISR Register */
    uint32 CPU2_CURMISR0;	/**< 0x0038: STC CPU1 Current MISR Register */
    uint32 STCSCSCR;		/**< 0x003C: STC Signature Compare Self-Check Register */
} stcctrlregs_t;

#define stcREG   ((stcctrlregs_t *)0xFFFFE600UL)

#endif
