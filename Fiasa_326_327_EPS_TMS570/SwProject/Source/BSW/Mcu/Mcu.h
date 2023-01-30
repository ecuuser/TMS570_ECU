/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Mcu.h
* Module Description: MCU driver: Partial Autosar API implementation
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Mon Nov 05 16:33:22 2012
* %version:          1 %
* %derived_by:       jzh87w %
* %date_modified:    Wed Feb 27 13:53:56 2013 %
*---------------------------------------------------------------------------*/

#ifndef MCU_H
#define MCU_H

/* Mcu_ResetType Values */
#define MCU_POWER_ON_RESET         0u
#define MCU_WATCHDOG_RESET         1u
#define MCU_SW_RESET               2u
#define MCU_RESET_UNDEFINED        3u

typedef uint8  Mcu_ResetType;
typedef uint8  Mcu_ModeType;

/* #include "Mcu_Cfg.h"  This include is omitted until configuration options are required for this module */

#define MCU_START_SEC_CODE
#include "MemMap.h"

FUNC(Mcu_ResetType, MCU_CODE) Mcu_GetResetReason(void);
FUNC(void, MCU_CODE) Mcu_PerformReset(void);
FUNC(void, MCU_CODE) Mcu_SetMode(Mcu_ModeType McuMode);


#define MCU_STOP_SEC_CODE
#include "MemMap.h"

#endif

