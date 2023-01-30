/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Mcu.c
* Module Description: MCU driver: Partial Autosar API implementation
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Mon Nov 05 16:33:22 2012
* %version:          1 %
* %derived_by:       xz0btk %
* %date_modified:    Wed Feb 27 13:53:55 2013 %
*---------------------------------------------------------------------------*/


#include "Std_Types.h"
#include "Mcu.h"

#include "system_regs.h"	/* defintion of system reset register */
#include "Os.h"				/* defintion of privileged register access API's */

#define MCU_START_SEC_CODE
#include "MemMap.h"

#define D_SYSECRRESET_CNT_U32	0x0080u

FUNC(Mcu_ResetType, MCU_CODE) Mcu_GetResetReason(void)
{
	/* Stub Function implementation to satisfy EcuM needs */
	/* TODO: Complete GetResetReason when use case merits */
    return MCU_RESET_UNDEFINED;
}

FUNC(void, MCU_CODE) Mcu_PerformReset(void)
{
    /* trigger a sofware reset */
	osWritePeripheral32(OS_MEM_AREA_SYSECR, (osuint32)&(systemREG1->SYSECR), D_SYSECRRESET_CNT_U32);
}

FUNC(void, MCU_CODE) Mcu_SetMode(Mcu_ModeType McuMode)
{
	/* Stub Function implementation to satisfy EcuM needs */
}

#define MCU_STOP_SEC_CODE
#include "MemMap.h"

