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
 *          File:  Components/Rte_Ap_StaMd9.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_STAMD9_H
# define _RTE_AP_STAMD9_H

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

# include "Rte_Hook.h"


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for Mode Management
 *********************************************************************************************************************/
extern VAR(Rte_ModeType_StaMd_Mode, RTE_VAR_NOINIT) Rte_ModeMachine_StaMd9_SystemState9_Mode;

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"
# endif /* !defined(RTE_CORE) */



# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Ap_StaMd9_SystemState9_Mode(Rte_ModeType_StaMd_Mode nextMode);


# define RTE_STOP_SEC_CODE
# include "MemMap.h"


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState9_Mode() Rte_ModeMachine_StaMd9_SystemState9_Mode


/**********************************************************************************************************************
 * Rte_Switch_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Switch_SystemState9_Mode Rte_Switch_Ap_StaMd9_SystemState9_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_AP_DIAGMGR9_APPL_CODE) DiagMgr_StaCtrl_Shutdown(void);
#  define RTE_STOP_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_DiagMgr_StaCtrl_Shutdown() (DiagMgr_StaCtrl_Shutdown(), ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Exclusive Areas
 *********************************************************************************************************************/

#  define Rte_Enter_StaMds9_MilestoneRqst_WARMINIT_ExclArea() \
  { \
    Rte_EnterHook_Ap_StaMd9_StaMds9_MilestoneRqst_WARMINIT_ExclArea_Start(); \
    Rte_EnterHook_Ap_StaMd9_StaMds9_MilestoneRqst_WARMINIT_ExclArea_Return(); \
  }

#  define Rte_Exit_StaMds9_MilestoneRqst_WARMINIT_ExclArea() \
  { \
    Rte_ExitHook_Ap_StaMd9_StaMds9_MilestoneRqst_WARMINIT_ExclArea_Start(); \
    Rte_ExitHook_Ap_StaMd9_StaMds9_MilestoneRqst_WARMINIT_ExclArea_Return(); \
  }


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_STAMD9_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_STAMD9_APPL_CODE) MilestoneRqst9_WarmInitMilestoneComplete(StaMd_Users user);

FUNC(void, RTE_AP_STAMD9_APPL_CODE) MilestoneRqst9_WarmInitMilestoneNotComplete(StaMd_Users user);

FUNC(void, RTE_AP_STAMD9_APPL_CODE) StaMd9_Per1(void);

FUNC(void, RTE_AP_STAMD9_APPL_CODE) StaMd9_Trns_DemShutdown(void);

FUNC(void, RTE_AP_STAMD9_APPL_CODE) StaMd_SCom_EcuReset(void);

FUNC(void, RTE_AP_STAMD9_APPL_CODE) StaMd_SCom_FBLTransitionReq(void);

# define RTE_STOP_SEC_AP_STAMD9_APPL_CODE
# include "MemMap.h"

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_STAMD9_H */
