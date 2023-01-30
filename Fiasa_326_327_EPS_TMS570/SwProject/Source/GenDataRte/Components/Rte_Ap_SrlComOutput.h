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
 *          File:  Components/Rte_Ap_SrlComOutput.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_SRLCOMOUTPUT_H
# define _RTE_AP_SRLCOMOUTPUT_H

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

#  define Rte_InitValue_ElectricStrFailSts_Cnt_lgc (FALSE)
#  define Rte_InitValue_HandwheelAuthority_Uls_f32 (0.0F)
#  define Rte_InitValue_HandwheelPosition_HwDeg_f32 (0.0F)
#  define Rte_InitValue_ProxiValid_Cnt_lgc (FALSE)
#  define Rte_InitValue_SrlComHwPosStatus_Cnt_u16 (0U)
#  define Rte_InitValue_SrlComHwTrq_HwNm_f32 (0.0F)
#  define Rte_InitValue_SrlComHwTrqValid_Cnt_lgc (FALSE)
#  define Rte_InitValue_SupplyCurrent_Amp_f32 (0.0F)
# endif


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



# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

extern VAR(Rte_tsTask_10ms_9, RTE_VAR_NOINIT) Rte_Task_10ms_9;

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
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

#  define Rte_IRead_SrlComOutput_Per1_HandwheelAuthority_Uls_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComOutput_SrlComOutput_Per1.Rte_HandwheelAuthority_Uls_f32.value)

#  define Rte_IRead_SrlComOutput_Per1_HandwheelPosition_HwDeg_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComOutput_SrlComOutput_Per1.Rte_HandwheelPosition_HwDeg_f32.value)

#  define Rte_IRead_SrlComOutput_Per1_ProxiValid_Cnt_lgc() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComOutput_SrlComOutput_Per1.Rte_ProxiValid_Cnt_lgc.value)

#  define Rte_IRead_SrlComOutput_Per1_SrlComHwPosStatus_Cnt_u16() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComOutput_SrlComOutput_Per1.Rte_SrlComHwPosStatus_Cnt_u16.value)

#  define Rte_IRead_SrlComOutput_Per1_SrlComHwTrqValid_Cnt_lgc() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComOutput_SrlComOutput_Per1.Rte_SrlComHwTrqValid_Cnt_lgc.value)

#  define Rte_IRead_SrlComOutput_Per1_SrlComHwTrq_HwNm_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComOutput_SrlComOutput_Per1.Rte_SrlComHwTrq_HwNm_f32.value)

#  define Rte_IRead_SrlComOutput_Per1_SupplyCurrent_Amp_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComOutput_SrlComOutput_Per1.Rte_SupplyCurrent_Amp_f32.value)

#  define Rte_IWrite_SrlComOutput_Per1_ElectricStrFailSts_Cnt_lgc(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComOutput_SrlComOutput_Per1.Rte_ElectricStrFailSts_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_SrlComOutput_Per1_ElectricStrFailSts_Cnt_lgc() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComOutput_SrlComOutput_Per1.Rte_ElectricStrFailSts_Cnt_lgc.value)


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState_Mode() Rte_ModeMachine_StaMd9_SystemState9_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_GetEpsEn(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);
#  define RTE_STOP_SEC_IOHWABSTRACTION_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_EpsEn_OP_GET IoHwAb_GetEpsEn
#  define RTE_START_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR9_APPL_CODE) NxtrDiagMgr9_GetNTCFailed(NTCNumber NTC_Cnt_T_enum, P2VAR(Boolean, AUTOMATIC, RTE_AP_DIAGMGR9_APPL_VAR) NTCFailed_Ptr_T_lgc);
#  define RTE_STOP_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_GetNTCFailed NxtrDiagMgr9_GetNTCFailed
#  define RTE_START_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR9_APPL_CODE) NxtrDiagMgr9_GetNTCStatus(NTCNumber NTC_Cnt_T_enum, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGMGR9_APPL_VAR) Status_Ptr_T_u08);
#  define RTE_STOP_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_GetNTCStatus NxtrDiagMgr9_GetNTCStatus
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) DtrmnElapsedTime_mS_u16(UInt32 InitialTime, P2VAR(UInt16, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) ElapsedTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(arg1, arg2) (DtrmnElapsedTime_mS_u16(arg1, arg2), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) GetSystemTime_mS_u32(P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) CurrentTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_GetSystemTime_mS_u32(arg1) (GetSystemTime_mS_u32(arg1), ((Std_ReturnType)RTE_E_OK))


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_SRLCOMOUTPUT_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_SRLCOMOUTPUT_APPL_CODE) SrlComOutput_Per1(void);

# define RTE_STOP_SEC_AP_SRLCOMOUTPUT_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_EpsEn_E_NOT_OK (1U)

#  define RTE_E_NxtrDiagMgr_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_SRLCOMOUTPUT_H */
