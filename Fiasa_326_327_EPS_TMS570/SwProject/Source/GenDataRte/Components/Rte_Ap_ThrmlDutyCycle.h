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
 *          File:  Components/Rte_Ap_ThrmlDutyCycle.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_THRMLDUTYCYCLE_H
# define _RTE_AP_THRMLDUTYCYCLE_H

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

#  define Rte_InitValue_CuTempEst_DegC_f32 (0.0F)
#  define Rte_InitValue_DefeatDutySvc_Cnt_lgc (FALSE)
#  define Rte_InitValue_DutyCycleLevel_Uls_f32 (0.0F)
#  define Rte_InitValue_FiltMeasTemp_DegC_f32 (0.0F)
#  define Rte_InitValue_FilteredPkCurr_AmpSq_f32 (0.0F)
#  define Rte_InitValue_IgnTimeOff_Cnt_u32 (0U)
#  define Rte_InitValue_MagTempEst_DegC_f32 (0.0F)
#  define Rte_InitValue_MotorVelCRF_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_MtrPkCurr_AmpSq_f32 (0.0F)
#  define Rte_InitValue_SiTempEst_DegC_f32 (0.0F)
#  define Rte_InitValue_ThermLimitPerc_Uls_f32 (0.0F)
#  define Rte_InitValue_ThermalLimit_MtrNm_f32 (8.8F)
#  define Rte_InitValue_VehTimeValid_Cnt_lgc (FALSE)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

extern VAR(Rte_tsTask_Init_9, RTE_VAR_NOINIT) Rte_Task_Init_9;

extern VAR(Rte_tsTask_100ms_9, RTE_VAR_NOINIT) Rte_Task_100ms_9;

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

#  define Rte_IRead_ThrmlDutyCycle_Init1_DefeatDutySvc_Cnt_lgc() \
  (Rte_Task_Init_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Init1.Rte_DefeatDutySvc_Cnt_lgc.value)

#  define Rte_IRead_ThrmlDutyCycle_Init1_IgnTimeOff_Cnt_u32() \
  (Rte_Task_Init_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Init1.Rte_IgnTimeOff_Cnt_u32.value)

#  define Rte_IRead_ThrmlDutyCycle_Init1_VehTimeValid_Cnt_lgc() \
  (Rte_Task_Init_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Init1.Rte_VehTimeValid_Cnt_lgc.value)

#  define Rte_IRead_ThrmlDutyCycle_Per1_CuTempEst_DegC_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_CuTempEst_DegC_f32.value)

#  define Rte_IRead_ThrmlDutyCycle_Per1_DefeatDutySvc_Cnt_lgc() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_DefeatDutySvc_Cnt_lgc.value)

#  define Rte_IRead_ThrmlDutyCycle_Per1_FiltMeasTemp_DegC_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_FiltMeasTemp_DegC_f32.value)

#  define Rte_IRead_ThrmlDutyCycle_Per1_FilteredPkCurr_AmpSq_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_FilteredPkCurr_AmpSq_f32.value)

#  define Rte_IRead_ThrmlDutyCycle_Per1_IgnTimeOff_Cnt_u32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_IgnTimeOff_Cnt_u32.value)

#  define Rte_IRead_ThrmlDutyCycle_Per1_MagTempEst_DegC_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_MagTempEst_DegC_f32.value)

#  define Rte_IRead_ThrmlDutyCycle_Per1_MotorVelCRF_MtrRadpS_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_MotorVelCRF_MtrRadpS_f32.value)

#  define Rte_IRead_ThrmlDutyCycle_Per1_MtrPkCurr_AmpSq_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_MtrPkCurr_AmpSq_f32.value)

#  define Rte_IRead_ThrmlDutyCycle_Per1_SiTempEst_DegC_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_SiTempEst_DegC_f32.value)

#  define Rte_IRead_ThrmlDutyCycle_Per1_VehTimeValid_Cnt_lgc() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_VehTimeValid_Cnt_lgc.value)

#  define Rte_IWrite_ThrmlDutyCycle_Per1_DutyCycleLevel_Uls_f32(data) \
  ( \
    Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_DutyCycleLevel_Uls_f32.value = (data) \
  )

#  define Rte_IWriteRef_ThrmlDutyCycle_Per1_DutyCycleLevel_Uls_f32() \
  (&Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_DutyCycleLevel_Uls_f32.value)

#  define Rte_IWrite_ThrmlDutyCycle_Per1_ThermLimitPerc_Uls_f32(data) \
  ( \
    Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_ThermLimitPerc_Uls_f32.value = (data) \
  )

#  define Rte_IWriteRef_ThrmlDutyCycle_Per1_ThermLimitPerc_Uls_f32() \
  (&Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_ThermLimitPerc_Uls_f32.value)

#  define Rte_IWrite_ThrmlDutyCycle_Per1_ThermalLimit_MtrNm_f32(data) \
  ( \
    Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_ThermalLimit_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_ThrmlDutyCycle_Per1_ThermalLimit_MtrNm_f32() \
  (&Rte_Task_100ms_9.Rte_RB.Rte_Ap_ThrmlDutyCycle_ThrmlDutyCycle_Per1.Rte_ThermalLimit_MtrNm_f32.value)


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR9_APPL_CODE) NxtrDiagMgr9_GetNTCFailed(NTCNumber NTC_Cnt_T_enum, P2VAR(Boolean, AUTOMATIC, RTE_AP_DIAGMGR9_APPL_VAR) NTCFailed_Ptr_T_lgc);
#  define RTE_STOP_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_GetNTCFailed NxtrDiagMgr9_GetNTCFailed
#  define RTE_START_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR9_APPL_CODE) NxtrDiagMgr9_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);
#  define RTE_STOP_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_SetNTCStatus NxtrDiagMgr9_SetNTCStatus
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NVM_APPL_CODE) NvM_GetErrorStatus(NvM_BlockIdType parg0, P2VAR(NvM_RequestResultType, AUTOMATIC, RTE_NVM_APPL_VAR) ErrorStatus);
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_ThrmlDutyCycle_FltStVar_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)30, arg1), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h"
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_ReadBlock(NvM_BlockIdType parg0, P2VAR(UInt8, AUTOMATIC, RTE_NVM_APPL_VAR) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_ReadBlock(NvM_BlockIdType parg0, P2VAR(NvM_DestPtr, AUTOMATIC, RTE_NVM_APPL_VAR) DstPtr);
# endif
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_ThrmlDutyCycle_FltStVar_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)30, arg1))
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NVM_APPL_CODE) NvM_SetRamBlockStatus(NvM_BlockIdType parg0, Boolean RamBlockStatus);
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_ThrmlDutyCycle_FltStVar_SetRamBlockStatus(arg1) (NvM_SetRamBlockStatus((NvM_BlockIdType)30, arg1), ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT
#   define RTE_START_SEC_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

extern VAR(ThrmlDutyCycle_FltStVal_Datatype, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_ThrmlDutyCycle_ThrmlDutyCycle_FltStVal;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  define Rte_Pim_ThrmlDutyCycle_FltStVal() \
  (&Rte_ThrmlDutyCycle_ThrmlDutyCycle_FltStVal)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_THRMLDUTYCYCLE_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_THRMLDUTYCYCLE_APPL_CODE) ThrmlDutyCycle_Init1(void);

FUNC(void, RTE_AP_THRMLDUTYCYCLE_APPL_CODE) ThrmlDutyCycle_Per1(void);

# define RTE_STOP_SEC_AP_THRMLDUTYCYCLE_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK (1U)

#  define RTE_E_NxtrDiagMgr_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_THRMLDUTYCYCLE_H */
