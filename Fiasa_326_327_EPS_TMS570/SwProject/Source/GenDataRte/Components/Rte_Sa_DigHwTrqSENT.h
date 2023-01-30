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
 *          File:  Components/Rte_Sa_DigHwTrqSENT.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SA_DIGHWTRQSENT_H
# define _RTE_SA_DIGHWTRQSENT_H

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

#  define RTE_START_SEC_VAR_Ap_10_INIT_UNSPECIFIED
#  include "MemMap.h"

/************************************************************************/
/* extern declaration of RTE buffers for optimized macro implementation */
/************************************************************************/
extern VAR(ManufModeType, RTE_VAR_INIT) Rte_CDDInterface_MEC_Cnt_enum;
extern VAR(Float, RTE_VAR_INIT) Rte_Nhet1_DigHwTrqT1_HwNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_Nhet1_DigHwTrqT2_HwNm_f32;

#  define RTE_STOP_SEC_VAR_Ap_10_INIT_UNSPECIFIED
#  include "MemMap.h"

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_HwTorque_HwNm_f32 (0.0F)
#  define Rte_InitValue_MECCounter_Cnt_enum (0U)
#  define Rte_InitValue_SrlComHwTrq_HwNm_f32 (0.0F)
#  define Rte_InitValue_SrlComHwTrqValid_Cnt_lgc (FALSE)
#  define Rte_InitValue_SysCHwTorque_HwNm_f32 (0.0F)
#  define Rte_InitValue_T1_HwNm_f32 (0.0F)
#  define Rte_InitValue_T2_HwNm_f32 (0.0F)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_Ap_10_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

extern VAR(Rte_tsTask_Init_10, RTE_VAR_NOINIT) Rte_Task_Init_10;

extern VAR(Rte_tsTask_2ms_10, RTE_VAR_NOINIT) Rte_Task_2ms_10;

extern VAR(Rte_tsTask_4ms_10, RTE_VAR_NOINIT) Rte_Task_4ms_10;

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

#  define Rte_IRead_DigHwTrqSENT_Init1_MECCounter_Cnt_enum() \
  (Rte_Task_Init_10.Rte_TB.Rte_I_CDDInterface_MEC_Cnt_enum.value)

#  define Rte_IRead_DigHwTrqSENT_Per1_T1_HwNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_Nhet1_DigHwTrqT1_HwNm_f32.value)

#  define Rte_IRead_DigHwTrqSENT_Per1_T2_HwNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_Nhet1_DigHwTrqT2_HwNm_f32.value)

#  define Rte_IWrite_DigHwTrqSENT_Per1_HwTorque_HwNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_DigHwTrqSENT_HwTorque_HwNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_DigHwTrqSENT_Per1_HwTorque_HwNm_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_DigHwTrqSENT_HwTorque_HwNm_f32.value)

#  define Rte_IWrite_DigHwTrqSENT_Per1_SysCHwTorque_HwNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_DigHwTrqSENT_DigHwTrqSENT_Per1.Rte_SysCHwTorque_HwNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_DigHwTrqSENT_Per1_SysCHwTorque_HwNm_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_DigHwTrqSENT_DigHwTrqSENT_Per1.Rte_SysCHwTorque_HwNm_f32.value)

#  define Rte_IWrite_DigHwTrqSENT_Per2_SrlComHwTrqValid_Cnt_lgc(data) \
  ( \
    Rte_Task_4ms_10.Rte_RB.Rte_Sa_DigHwTrqSENT_DigHwTrqSENT_Per2.Rte_SrlComHwTrqValid_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_DigHwTrqSENT_Per2_SrlComHwTrqValid_Cnt_lgc() \
  (&Rte_Task_4ms_10.Rte_RB.Rte_Sa_DigHwTrqSENT_DigHwTrqSENT_Per2.Rte_SrlComHwTrqValid_Cnt_lgc.value)

#  define Rte_IWrite_DigHwTrqSENT_Per2_SrlComHwTrq_HwNm_f32(data) \
  ( \
    Rte_Task_4ms_10.Rte_RB.Rte_Sa_DigHwTrqSENT_DigHwTrqSENT_Per2.Rte_SrlComHwTrq_HwNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_DigHwTrqSENT_Per2_SrlComHwTrq_HwNm_f32() \
  (&Rte_Task_4ms_10.Rte_RB.Rte_Sa_DigHwTrqSENT_DigHwTrqSENT_Per2.Rte_SrlComHwTrq_HwNm_f32.value)


/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_MECCounter_Cnt_enum Rte_Read_Sa_DigHwTrqSENT_MECCounter_Cnt_enum
#  define Rte_Read_Sa_DigHwTrqSENT_MECCounter_Cnt_enum(data) (*(data) = Rte_CDDInterface_MEC_Cnt_enum, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_T1_HwNm_f32 Rte_Read_Sa_DigHwTrqSENT_T1_HwNm_f32
#  define Rte_Read_Sa_DigHwTrqSENT_T1_HwNm_f32(data) (*(data) = Rte_Nhet1_DigHwTrqT1_HwNm_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_T2_HwNm_f32 Rte_Read_Sa_DigHwTrqSENT_T2_HwNm_f32
#  define Rte_Read_Sa_DigHwTrqSENT_T2_HwNm_f32(data) (*(data) = Rte_Nhet1_DigHwTrqT2_HwNm_f32, ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_AP_FLTINJECTION_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_AP_FLTINJECTION_APPL_CODE) FltInjection_SCom_FltInjection(P2VAR(Float, AUTOMATIC, RTE_AP_FLTINJECTION_APPL_VAR) SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum);
#  define RTE_STOP_SEC_AP_FLTINJECTION_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_FaultInjection_SCom_FltInjection(arg1, arg2) (FltInjection_SCom_FltInjection(arg1, arg2), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NVMPROXY_APPL_CODE) NvMProxy_GetErrorStatus(UInt8 parg0, P2VAR(NvM_RequestResultType, AUTOMATIC, RTE_NVMPROXY_APPL_VAR) ErrorStatus);
#  define RTE_STOP_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NvM_DigHwTrqSENTTrim_Srv_GetErrorStatus(arg1) (NvMProxy_GetErrorStatus((UInt8)8, arg1), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVMPROXY_APPL_CODE) NvMProxy_WriteBlock(UInt8 parg0, P2CONST(UInt8, AUTOMATIC, RTE_NVMPROXY_APPL_DATA) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVMPROXY_APPL_CODE) NvMProxy_WriteBlock(UInt8 parg0, P2CONST(NvM_DestPtr, AUTOMATIC, RTE_NVMPROXY_APPL_DATA) DstPtr);
# endif
#  define RTE_STOP_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(arg1) (NvMProxy_WriteBlock((UInt8)8, arg1))
#  define RTE_START_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_GetNTCStatus(NTCNumber NTC_Cnt_T_enum, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGMGR10_APPL_VAR) Status_Ptr_T_u08);
#  define RTE_STOP_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_GetNTCStatus NxtrDiagMgr10_GetNTCStatus
#  define RTE_START_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);
#  define RTE_STOP_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_SetNTCStatus NxtrDiagMgr10_SetNTCStatus


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT
#   define RTE_START_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

extern VAR(DigHwTrqSENTTrim_DataType, RTE_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP) Rte_DigHwTrqSENT_DigTrqTrim;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  define Rte_Pim_DigTrqTrim() \
  (&Rte_DigHwTrqSENT_DigTrqTrim)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_SA_DIGHWTRQSENT_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Init1(void);

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Per1(void);

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Per2(void);

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Per3(void);

FUNC(Std_ReturnType, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_ClrTrqTrim(void);

FUNC(Std_ReturnType, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_SetTrqTrim(void);

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_TrimData(P2VAR(Float, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) EOLHwTrqTrim_HwNm_f32, P2VAR(Boolean, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) EOLHwTrqTrimPerformed_Cnt_Lgc);

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_WriteData(Float HwTrqTrim_HwNm_f32);

# define RTE_STOP_SEC_SA_DIGHWTRQSENT_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_DigHwTrqSENT_SCom_ConditionsNotCorrect (34U)

#  define RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK (1U)

#  define RTE_E_NxtrDiagMgr_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_SA_DIGHWTRQSENT_H */
