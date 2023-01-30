/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : MtrCtrl_Irq.h
* Module Description: Motor Control Interupt 
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          1 %
 * %derived_by:       tzj9qy %
 * %date_modified:    Tue Jul 10 16:42:14 2012 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 04/13/11  1        LWW       Initial K2xx Synergy Version
 */

#ifndef MTRCTRL_IRQ_H
#define MTRCTRL_IRQ_H

/*****************************************************************************
 *  GLOBAL CONSTANT MACROS
 ******************************************************************************/
#define MTRCTRL_COMPILER_ISR    interrupt

/*****************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 ******************************************************************************/
MTRCTRL_COMPILER_ISR void Isr_MtrCtrl(void);


#endif
