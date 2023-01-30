/*****************************************************************************
* Copyright 2013 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : ePWM.h
* Module Description: eTPWM Complex Device Driver
* Product           : Gen II Plus - EA3.0
* Author            : Owen Tosh
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu Jan 31 13:14:15 2013
* %version:          2 %
* %derived_by:       nz63rn %
* %date_modified:    Mon Oct 21 12:50:35 2013 % 
*---------------------------------------------------------------------------*/
/*****************************************************************************

CHANGE HISTORY:

Date      Rev      Author    Change Description                          SCR #
--------  -------  --------  ------------------------------------------  -----
02/01/13  1        Selva     Initial Version
10/21/13  2        KMC       Moved register definitions to epwm_regs.h 	  10549
                             in StdDef\include\TMS570_HerculesRegs
******************************************************************************/

#ifndef EPWM_H
#define EPWM_H

#include "epwm_regs.h"

FUNC(void, EPWM_CODE) ePWM_Init1(void);
FUNC(void, EPWM_CODE) ePWM_Per1(void);


/* Disable PWM Outputs */
#define ePWM_DisableOutputs()        \
{                                    \
	ePWM1->AQCSFRC = 5U;         \
	ePWM1->DBCTL &= 0xFFFCU; \
	ePWM2->AQCSFRC = 5U;         \
	ePWM2->DBCTL &= 0xFFFCU; \
	ePWM3->AQCSFRC = 5U;         \
	ePWM3->DBCTL &= 0xFFFCU; \
}


/* Enable PWM Outputs */
#define ePWM_EnableOutputs() \
{                            \
	ePWM1->AQCSFRC = 0U; \
	ePWM1->DBCTL |= 3U;  \
	ePWM2->AQCSFRC = 0U; \
	ePWM2->DBCTL |= 3U;  \
	ePWM3->AQCSFRC = 0U; \
	ePWM3->DBCTL |= 3U;  \
}


#endif  /* end of EPWM_H definition */
