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
 *          File:  Components/Rte_ComM.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_COMM_H
# define _RTE_COMM_H

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


# define RTE_START_SEC_COMM_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_COMM_APPL_CODE) ComM_MainFunction_0(void);

FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_GetCurrentComMode(ComM_UserHandleType parg0, P2VAR(ComM_ModeType, AUTOMATIC, RTE_COMM_APPL_VAR) ComMode);

FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_GetInhibitionStatus(ComM_NetworkHandleType parg0, P2VAR(ComM_InhibitionStatusType, AUTOMATIC, RTE_COMM_APPL_VAR) Status);

FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_GetMaxComMode(ComM_UserHandleType parg0, P2VAR(ComM_ModeType, AUTOMATIC, RTE_COMM_APPL_VAR) ComMode);

FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_GetRequestedComMode(ComM_UserHandleType parg0, P2VAR(ComM_ModeType, AUTOMATIC, RTE_COMM_APPL_VAR) ComMode);

FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_ServiceLimitChannelToNoComMode(ComM_NetworkHandleType parg0, Boolean Status);

FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_LimitECUToNoComMode(Boolean Status);

FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_ServicePreventWakeUp(ComM_NetworkHandleType parg0, Boolean Status);

FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_ReadInhibitCounter(P2VAR(UInt16, AUTOMATIC, RTE_COMM_APPL_VAR) CounterValue);

FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_RequestComMode(ComM_UserHandleType parg0, ComM_ModeType ComMode);

FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_ResetInhibitCounter(void);

FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_SetECUGroupClassification(ComM_InhibitionStatusType Status);

# define RTE_STOP_SEC_COMM_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_ComM_ChannelLimitation_E_NOT_OK (1U)

#  define RTE_E_ComM_ChannelWakeUp_E_NOT_OK (1U)

#  define RTE_E_ComM_ECUModeLimitation_E_NOT_OK (1U)

#  define RTE_E_ComM_UserRequest_E_MODE_LIMITATION (2U)

#  define RTE_E_ComM_UserRequest_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_COMM_H */
