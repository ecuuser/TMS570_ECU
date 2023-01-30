/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  Copyright (c) 2006-2011 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Components/Rte_NvM.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_NVM_H
# define _RTE_NVM_H

# ifndef RTE_CORE
#  ifdef RTE_APPLICATION_HEADER_FILE
#   error Multiple application header files included.
#  endif
#  define RTE_APPLICATION_HEADER_FILE
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_Type.h"


# define RTE_START_SEC_NVM_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_EraseNvBlock(NvM_BlockIdType parg0);

FUNC(void, RTE_NVM_APPL_CODE) NvM_GetErrorStatus(NvM_BlockIdType parg0, P2VAR(NvM_RequestResultType, AUTOMATIC, RTE_NVM_APPL_VAR) ErrorStatus);

FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_InvalidateNvBlock(NvM_BlockIdType parg0);

FUNC(void, RTE_NVM_APPL_CODE) NvM_MainFunction(void);

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_ReadBlock(NvM_BlockIdType parg0, P2VAR(UInt8, AUTOMATIC, RTE_NVM_APPL_VAR) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_ReadBlock(NvM_BlockIdType parg0, P2VAR(NvM_DestPtr, AUTOMATIC, RTE_NVM_APPL_VAR) DstPtr);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_RestoreBlockDefaults(NvM_BlockIdType parg0, P2VAR(UInt8, AUTOMATIC, RTE_NVM_APPL_VAR) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_RestoreBlockDefaults(NvM_BlockIdType parg0, P2VAR(NvM_DestPtr, AUTOMATIC, RTE_NVM_APPL_VAR) DstPtr);
# endif

FUNC(void, RTE_NVM_APPL_CODE) NvM_SetBlockProtection(NvM_BlockIdType parg0, Boolean ProtectionEnabled);

FUNC(void, RTE_NVM_APPL_CODE) NvM_SetRamBlockStatus(NvM_BlockIdType parg0, Boolean RamBlockStatus);

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_WriteBlock(NvM_BlockIdType parg0, P2CONST(UInt8, AUTOMATIC, RTE_NVM_APPL_DATA) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_WriteBlock(NvM_BlockIdType parg0, P2CONST(NvM_DestPtr, AUTOMATIC, RTE_NVM_APPL_DATA) DstPtr);
# endif

# define RTE_STOP_SEC_NVM_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK (1U)

#  define RTE_E_NvM_AC3_SRBS_Srv_Defs_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_NVM_H */
