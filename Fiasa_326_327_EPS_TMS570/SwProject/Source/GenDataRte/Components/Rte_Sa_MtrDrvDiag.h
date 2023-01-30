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
 *          File:  Components/Rte_Sa_MtrDrvDiag.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SA_MTRDRVDIAG_H
# define _RTE_SA_MTRDRVDIAG_H

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


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_FETFaultPhase_Cnt_enum (0U)
#  define Rte_InitValue_FETFaultType_Cnt_enum (0U)
#  define Rte_InitValue_GateDriveResetActive_Cnt_lgc (FALSE)
#  define Rte_InitValue_MtrDrvrInitComplete_Cnt_lgc (FALSE)
#  define Rte_InitValue_MtrDrvrInitStart_Cnt_lgc (FALSE)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for Mode Management
 *********************************************************************************************************************/
extern VAR(Rte_ModeType_StaMd_Mode, RTE_VAR_NOINIT) Rte_ModeMachine_StaMd_SystemState_Mode;

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"
# endif /* !defined(RTE_CORE) */



# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_Ap_10_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

extern VAR(Rte_tsTask_2ms_10, RTE_VAR_NOINIT) Rte_Task_2ms_10;

extern VAR(Rte_tsTask_Trns_10, RTE_VAR_NOINIT) Rte_Task_Trns_10;

#  define RTE_STOP_SEC_VAR_Ap_10_NOINIT_UNSPECIFIED
#  include "MemMap.h"
# endif


# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/

# define RTE_STOP_SEC_CODE
# include "MemMap.h"


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_IRead_<r>_<p>_<d>
 * Rte_IStatus_<r>_<p>_<d>
 * Rte_IWrite_<r>_<p>_<d>
 * Rte_IWriteRef_<r>_<p>_<d>
 * Rte_IInvalidate_<r>_<p>_<d>
 *********************************************************************************************************************/

#  define Rte_IRead_MtrDrvDiag_Per1_MtrDrvrInitStart_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrDrvDiag_MtrDrvDiag_Per1.Rte_MtrDrvrInitStart_Cnt_lgc.value)

#  define Rte_IWrite_MtrDrvDiag_Per1_FETFaultPhase_Cnt_enum(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrDrvDiag_MtrDrvDiag_Per1.Rte_FETFaultPhase_Cnt_enum.value = (data) \
  )

#  define Rte_IWriteRef_MtrDrvDiag_Per1_FETFaultPhase_Cnt_enum() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrDrvDiag_MtrDrvDiag_Per1.Rte_FETFaultPhase_Cnt_enum.value)

#  define Rte_IWrite_MtrDrvDiag_Per1_FETFaultType_Cnt_enum(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrDrvDiag_MtrDrvDiag_Per1.Rte_FETFaultType_Cnt_enum.value = (data) \
  )

#  define Rte_IWriteRef_MtrDrvDiag_Per1_FETFaultType_Cnt_enum() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrDrvDiag_MtrDrvDiag_Per1.Rte_FETFaultType_Cnt_enum.value)

#  define Rte_IWrite_MtrDrvDiag_Per1_GateDriveResetActive_Cnt_lgc(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrDrvDiag_MtrDrvDiag_Per1.Rte_GateDriveResetActive_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_MtrDrvDiag_Per1_GateDriveResetActive_Cnt_lgc() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrDrvDiag_MtrDrvDiag_Per1.Rte_GateDriveResetActive_Cnt_lgc.value)

#  define Rte_IWrite_MtrDrvDiag_Per1_MtrDrvrInitComplete_Cnt_lgc(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrDrvDiag_MtrDrvDiag_Per1.Rte_MtrDrvrInitComplete_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_MtrDrvDiag_Per1_MtrDrvrInitComplete_Cnt_lgc() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrDrvDiag_MtrDrvDiag_Per1.Rte_MtrDrvrInitComplete_Cnt_lgc.value)

#  define Rte_IWrite_MtrDrvDiag_Trns1_MtrDrvrInitComplete_Cnt_lgc(data) \
  ( \
    Rte_Task_Trns_10.Rte_RB.Rte_Sa_MtrDrvDiag_MtrDrvDiag_Trns1.Rte_MtrDrvrInitComplete_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_MtrDrvDiag_Trns1_MtrDrvrInitComplete_Cnt_lgc() \
  (&Rte_Task_Trns_10.Rte_RB.Rte_Sa_MtrDrvDiag_MtrDrvDiag_Trns1.Rte_MtrDrvrInitComplete_Cnt_lgc.value)


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState_Mode() Rte_ModeMachine_StaMd_SystemState_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_SetFetDrvReset(IoHwAb_BoolType signal);
#  define RTE_STOP_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_FetDrvReset_OP_SET IoHwAb_SetFetDrvReset
#  define RTE_START_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_GetFetFlt1Data(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);
#  define RTE_STOP_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_FetFlt1Data_OP_GET IoHwAb_GetFetFlt1Data
#  define RTE_START_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_GetFetFlt2Clk(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);
#  define RTE_STOP_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_FetFlt2Clk_OP_GET IoHwAb_GetFetFlt2Clk
#  define RTE_START_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_SetFetFlt2Clk(IoHwAb_BoolType signal);
#  define RTE_STOP_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_FetFlt2Clk_OP_SET IoHwAb_SetFetFlt2Clk
#  define RTE_START_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_OutputSetFetFlt2ToOutput(IoHwAb_BoolType signal);
#  define RTE_STOP_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_IoHwAbPortConfig_SetFetFlt2ToOutput IoHwAb_OutputSetFetFlt2ToOutput
#  define RTE_START_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_GetNTCFailed(NTCNumber NTC_Cnt_T_enum, P2VAR(Boolean, AUTOMATIC, RTE_AP_DIAGMGR10_APPL_VAR) NTCFailed_Ptr_T_lgc);
#  define RTE_STOP_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_GetNTCFailed NxtrDiagMgr10_GetNTCFailed
#  define RTE_START_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);
#  define RTE_STOP_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_SetNTCStatus NxtrDiagMgr10_SetNTCStatus
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) DtrmnElapsedTime_mS_u16(UInt32 InitialTime, P2VAR(UInt16, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) ElapsedTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(arg1, arg2) (DtrmnElapsedTime_mS_u16(arg1, arg2), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) DtrmnElapsedTime_uS_u16(UInt32 InitialTime, P2VAR(UInt16, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) ElapsedTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_DtrmnElapsedTime_uS_u16(arg1, arg2) (DtrmnElapsedTime_uS_u16(arg1, arg2), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) GetSystemTime_mS_u32(P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) CurrentTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_GetSystemTime_mS_u32(arg1) (GetSystemTime_mS_u32(arg1), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) GetSystemTime_uS_u32(P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) CurrentTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_GetSystemTime_uS_u32(arg1) (GetSystemTime_uS_u32(arg1), ((Std_ReturnType)RTE_E_OK))


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_SA_MTRDRVDIAG_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_SA_MTRDRVDIAG_APPL_CODE) MtrDrvDiag_Per1(void);

FUNC(void, RTE_SA_MTRDRVDIAG_APPL_CODE) MtrDrvDiag_Per2(void);

FUNC(void, RTE_SA_MTRDRVDIAG_APPL_CODE) MtrDrvDiag_Trns1(void);

# define RTE_STOP_SEC_SA_MTRDRVDIAG_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_FetDrvReset_E_NOT_OK (1U)

#  define RTE_E_FetFlt1Data_E_NOT_OK (1U)

#  define RTE_E_FetFlt2Clk_E_NOT_OK (1U)

#  define RTE_E_IoHwAbPortConfig_E_NOT_OK (1U)

#  define RTE_E_NxtrDiagMgr_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_SA_MTRDRVDIAG_H */
