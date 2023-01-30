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
 *          File:  Components/Rte_WdgM.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_WDGM_H
# define _RTE_WDGM_H

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


# define RTE_START_SEC_WDGM_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_WDGM_APPL_CODE) WdgM_ActivateSupervisionEntity(WdgM_SupervisedEntityIdType parg0);

FUNC(Std_ReturnType, RTE_WDGM_APPL_CODE) WdgM_CheckpointReached(WdgM_SupervisedEntityIdType parg0, WdgM_CheckpointIdType parg1);

FUNC(Std_ReturnType, RTE_WDGM_APPL_CODE) WdgM_DeactivateSupervisionEntity(WdgM_SupervisedEntityIdType parg0);

FUNC(Std_ReturnType, RTE_WDGM_APPL_CODE) WdgM_GetGlobalStatus(P2VAR(WdgM_GlobalStatusType, AUTOMATIC, RTE_WDGM_APPL_VAR) Status);

FUNC(Std_ReturnType, RTE_WDGM_APPL_CODE) WdgM_GetLocalStatus(WdgM_SupervisedEntityIdType parg0, P2VAR(WdgM_LocalStatusType, AUTOMATIC, RTE_WDGM_APPL_VAR) Status);

FUNC(Std_ReturnType, RTE_WDGM_APPL_CODE) WdgM_GetMode(P2VAR(WdgM_ModeType, AUTOMATIC, RTE_WDGM_APPL_VAR) Mode);

FUNC(Std_ReturnType, RTE_WDGM_APPL_CODE) GlobalStateChangeCbk(WdgM_GlobalStatusType Status);

FUNC(void, RTE_WDGM_APPL_CODE) WdgM_MainFunction(void);

FUNC(Std_ReturnType, RTE_WDGM_APPL_CODE) WdgM_PerformReset(void);

FUNC(Std_ReturnType, RTE_WDGM_APPL_CODE) WdgM_SetMode(WdgM_ModeType parg0, UInt16 parg1);

# define RTE_STOP_SEC_WDGM_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_WdgM_AliveSupervision_E_NOT_OK (1U)

#  define RTE_E_WdgM_GlobalMode_E_NOT_OK (1U)

#  define RTE_E_WdgM_IndividualMode_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_WDGM_H */
