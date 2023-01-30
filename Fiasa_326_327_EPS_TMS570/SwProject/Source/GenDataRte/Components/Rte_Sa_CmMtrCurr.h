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
 *          File:  Components/Rte_Sa_CmMtrCurr.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SA_CMMTRCURR_H
# define _RTE_SA_CMMTRCURR_H

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
extern VAR(Boolean, RTE_VAR_INIT) Rte_CmMtrCurr_CurrentGainSvc_Cnt_lgc;
extern VAR(ManufModeType, RTE_VAR_INIT) Rte_CDDInterface_MEC_Cnt_enum;
extern VAR(Float, RTE_VAR_INIT) Rte_MtrVel_MotorVelMRF_MtrRadpS_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_SignlCondn_VehicleSpeed_Kph_f32;
extern VAR(Boolean, RTE_VAR_INIT) Rte_SrlComInput_VehicleSpeedValid_Cnt_lgc;

#  define RTE_STOP_SEC_VAR_Ap_10_INIT_UNSPECIFIED
#  include "MemMap.h"

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_ADCMtrCurr1_Volts_f32 (0.0F)
#  define Rte_InitValue_ADCMtrCurr2_Volts_f32 (0.0F)
#  define Rte_InitValue_ComOffset_Cnt_u16 (0U)
#  define Rte_InitValue_CorrMtrCurrPosition_Rev_f32 (0.0F)
#  define Rte_InitValue_CurrentGainSvc_Cnt_lgc (FALSE)
#  define Rte_InitValue_FiltCntrlTemp_DegC_f32 (0.0F)
#  define Rte_InitValue_MEC_Cnt_enum (0U)
#  define Rte_InitValue_MtrCurr1TempOffset_Volt_f32 (0.0F)
#  define Rte_InitValue_MtrCurr2TempOffset_Volt_f32 (0.0F)
#  define Rte_InitValue_MtrCurrAngle_Rev_f32 (0.0F)
#  define Rte_InitValue_MtrCurrK1_Amp_f32 (0.0F)
#  define Rte_InitValue_MtrCurrK2_Amp_f32 (0.0F)
#  define Rte_InitValue_MtrVel_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_SrlComSvcDft_Cnt_b32 (0U)
#  define Rte_InitValue_Vecu_Volt_f32 (5.0F)
#  define Rte_InitValue_VehSpd_Kph_f32 (0.0F)
#  define Rte_InitValue_VhSpdValid_Cnt_lgc (FALSE)
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

extern VAR(Rte_tsTask_100ms_10, RTE_VAR_NOINIT) Rte_Task_100ms_10;

extern VAR(Rte_tsTask_2ms_10, RTE_VAR_NOINIT) Rte_Task_2ms_10;

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

#  define Rte_IRead_CmMtrCurr_Per1_FiltCntrlTemp_DegC_f32() \
  (Rte_Task_100ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per1.Rte_FiltCntrlTemp_DegC_f32.value)

#  define Rte_IWrite_CmMtrCurr_Per1_MtrCurr1TempOffset_Volt_f32(data) \
  ( \
    Rte_Task_100ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per1.Rte_MtrCurr1TempOffset_Volt_f32.value = (data) \
  )

#  define Rte_IWriteRef_CmMtrCurr_Per1_MtrCurr1TempOffset_Volt_f32() \
  (&Rte_Task_100ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per1.Rte_MtrCurr1TempOffset_Volt_f32.value)

#  define Rte_IWrite_CmMtrCurr_Per1_MtrCurr2TempOffset_Volt_f32(data) \
  ( \
    Rte_Task_100ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per1.Rte_MtrCurr2TempOffset_Volt_f32.value = (data) \
  )

#  define Rte_IWriteRef_CmMtrCurr_Per1_MtrCurr2TempOffset_Volt_f32() \
  (&Rte_Task_100ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per1.Rte_MtrCurr2TempOffset_Volt_f32.value)

#  define Rte_IRead_CmMtrCurr_Per2_ADCMtrCurr1_Volts_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per2.Rte_ADCMtrCurr1_Volts_f32.value)

#  define Rte_IRead_CmMtrCurr_Per2_ADCMtrCurr2_Volts_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per2.Rte_ADCMtrCurr2_Volts_f32.value)

#  define Rte_IRead_CmMtrCurr_Per2_CorrMtrCurrPosition_Rev_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per2.Rte_CorrMtrCurrPosition_Rev_f32.value)

#  define Rte_IRead_CmMtrCurr_Per2_MtrCurrAngle_Rev_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per2.Rte_MtrCurrAngle_Rev_f32.value)

#  define Rte_IRead_CmMtrCurr_Per2_MtrCurrK1_Amp_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per2.Rte_MtrCurrK1_Amp_f32.value)

#  define Rte_IRead_CmMtrCurr_Per2_MtrCurrK2_Amp_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per2.Rte_MtrCurrK2_Amp_f32.value)

#  define Rte_IRead_CmMtrCurr_Per3_ADCMtrCurr1_Volts_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per3.Rte_ADCMtrCurr1_Volts_f32.value)

#  define Rte_IRead_CmMtrCurr_Per3_ADCMtrCurr2_Volts_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per3.Rte_ADCMtrCurr2_Volts_f32.value)

#  define Rte_IRead_CmMtrCurr_Per3_MtrVel_MtrRadpS_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per3.Rte_MtrVel_MtrRadpS_f32.value)

#  define Rte_IRead_CmMtrCurr_Per3_SrlComSvcDft_Cnt_b32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per3.Rte_SrlComSvcDft_Cnt_b32.value)

#  define Rte_IRead_CmMtrCurr_Per3_Vecu_Volt_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per3.Rte_Vecu_Volt_f32.value)

#  define Rte_IRead_CmMtrCurr_Per3_VehSpd_Kph_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per3.Rte_VehSpd_Kph_f32.value)

#  define Rte_IRead_CmMtrCurr_Per3_VhSpdValid_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per3.Rte_VhSpdValid_Cnt_lgc.value)

#  define Rte_IWrite_CmMtrCurr_Per3_ComOffset_Cnt_u16(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per3.Rte_ComOffset_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_CmMtrCurr_Per3_ComOffset_Cnt_u16() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_CmMtrCurr_CmMtrCurr_Per3.Rte_ComOffset_Cnt_u16.value)


/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_MEC_Cnt_enum Rte_Read_Sa_CmMtrCurr_MEC_Cnt_enum
#  define Rte_Read_Sa_CmMtrCurr_MEC_Cnt_enum(data) (*(data) = Rte_CDDInterface_MEC_Cnt_enum, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_MtrVel_MtrRadpS_f32 Rte_Read_Sa_CmMtrCurr_MtrVel_MtrRadpS_f32
#  define Rte_Read_Sa_CmMtrCurr_MtrVel_MtrRadpS_f32(data) (*(data) = Rte_MtrVel_MotorVelMRF_MtrRadpS_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_VehSpd_Kph_f32 Rte_Read_Sa_CmMtrCurr_VehSpd_Kph_f32
#  define Rte_Read_Sa_CmMtrCurr_VehSpd_Kph_f32(data) (*(data) = Rte_SignlCondn_VehicleSpeed_Kph_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_VhSpdValid_Cnt_lgc Rte_Read_Sa_CmMtrCurr_VhSpdValid_Cnt_lgc
#  define Rte_Read_Sa_CmMtrCurr_VhSpdValid_Cnt_lgc(data) (*(data) = Rte_SrlComInput_VehicleSpeedValid_Cnt_lgc, ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Write_CurrentGainSvc_Cnt_lgc Rte_Write_Sa_CmMtrCurr_CurrentGainSvc_Cnt_lgc
#  define Rte_Write_Sa_CmMtrCurr_CurrentGainSvc_Cnt_lgc(data) (Rte_CmMtrCurr_CurrentGainSvc_Cnt_lgc = (data), ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState_Mode() Rte_ModeMachine_StaMd_SystemState_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVMPROXY_APPL_CODE) NvMProxy_WriteBlock(UInt8 parg0, P2CONST(UInt8, AUTOMATIC, RTE_NVMPROXY_APPL_DATA) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVMPROXY_APPL_CODE) NvMProxy_WriteBlock(UInt8 parg0, P2CONST(NvM_DestPtr, AUTOMATIC, RTE_NVMPROXY_APPL_DATA) DstPtr);
# endif
#  define RTE_STOP_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_EOLCurrTempOffset_WriteBlock(arg1) (NvMProxy_WriteBlock((UInt8)12, arg1))
#  define RTE_START_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NVMPROXY_APPL_CODE) NvMProxy_SetRamBlockStatus(UInt8 parg0, Boolean RamBlockStatus);
#  define RTE_STOP_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_EOLShCurrCal_SetRamBlockStatus(arg1) (NvMProxy_SetRamBlockStatus((UInt8)1, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_EOLShCurrCal_WriteBlock(arg1) (NvMProxy_WriteBlock((UInt8)1, arg1))
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

extern VAR(CurrTempOffsetType, RTE_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP) Rte_CmMtrCurr_CurrTempOffset;
extern VAR(PhaseCurrCal_DataType, RTE_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP) Rte_CmMtrCurr_ShCurrCal;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  define Rte_Pim_CurrTempOffset() \
  (&Rte_CmMtrCurr_CurrTempOffset)

#  define Rte_Pim_ShCurrCal() \
  (&Rte_CmMtrCurr_ShCurrCal)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_SA_CMMTRCURR_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurrTempOffset_Scom_Get(P2VAR(CurrTempOffsetType, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_VAR) CurrTempOffCal);

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurrTempOffset_Scom_Set(P2CONST(CurrTempOffsetType, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_DATA) CurrTempOffCal);

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_Init(void);

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_Per1(void);

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_Per2(void);

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_Per3(void);

FUNC(Std_ReturnType, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_CalGain(void);

FUNC(Std_ReturnType, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_CalOffset(void);

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_MtrCurrOffReadStatus(P2VAR(MtrCurrOffProcessFlag, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_VAR) CurrOffStatus);

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_ReadMtrCurrCals(P2VAR(PhaseCurrCal_DataType, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_VAR) ShCurrCalPtr);

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_SetMtrCurrCals(P2CONST(PhaseCurrCal_DataType, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_DATA) ShCurrCalPtr);

# define RTE_STOP_SEC_SA_CMMTRCURR_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_CmMtrCurr_SCom_ConditionNotCorrect (34U)

#  define RTE_E_CmMtrCurr_SCom_CurrentOutOfRange (20U)

#  define RTE_E_CmMtrCurr_SCom_VehSpdOutofRange (21U)

#  define RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK (1U)

#  define RTE_E_NxtrDiagMgr_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_SA_CMMTRCURR_H */
