/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : ResetCause.c
* Module Description: This file contains the definition of the ResetCause variable
* Product           : Gen II Plus EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri May 11 12:17:00 2012
 * %version:          2 %
 * %derived_by:       czgng4 %
 * %date_modified:    Thu Nov 29 15:16:20 2012 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/09/12  1        LWW       Initial Version
 * 11/29/12  2        LWW       Replaced direct pragma with memmap statements
 */

#include "Platform_Types.h"
#include "Compiler.h"
#include "ResetCause.h"

#define RESETCAUSE_START_SEC_VAR_POWER_ON_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
volatile VAR(ENUM_ResetCause, CD_RESETHANDLER_VAR_NOINIT) ResetCause_Cnt_Enum;
#define RESETCAUSE_STOP_SEC_VAR_POWER_ON_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */

