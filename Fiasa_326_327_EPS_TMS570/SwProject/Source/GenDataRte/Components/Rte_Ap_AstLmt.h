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
 *          File:  Components/Rte_Ap_AstLmt.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_ASTLMT_H
# define _RTE_AP_ASTLMT_H

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
extern VAR(Float, RTE_VAR_INIT) Rte_SignlCondn_VehicleSpeed_Kph_f32;

#  define RTE_STOP_SEC_VAR_Ap_10_INIT_UNSPECIFIED
#  include "MemMap.h"

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_AssistCmd_MtrNm_f32 (0.0F)
#  define Rte_InitValue_AssistEOTDamping_MtrNm_f32 (0.0F)
#  define Rte_InitValue_AssistEOTGain_Uls_f32 (1.0F)
#  define Rte_InitValue_AssistEOTLimit_MtrNm_f32 (8.8F)
#  define Rte_InitValue_AssistStallLimit_MtrNm_f32 (8.8F)
#  define Rte_InitValue_AssistVehSpdLimit_MtrNm_f32 (8.8F)
#  define Rte_InitValue_CombinedDamping_MtrNm_f32 (0.0F)
#  define Rte_InitValue_DefeatLimitService_Cnt_lgc (FALSE)
#  define Rte_InitValue_LimitPercentFiltered_Uls_f32 (0.0F)
#  define Rte_InitValue_LimitedReturn_MtrNm_f32 (0.0F)
#  define Rte_InitValue_LrnPnCtrCCDisable_Cnt_lgc (FALSE)
#  define Rte_InitValue_LrnPnCtrEnable_Cnt_lgc (FALSE)
#  define Rte_InitValue_LrnPnCtrTCmd_MtrNm_f32 (0.0F)
#  define Rte_InitValue_OpTrqOvr_MtrNm_f32 (0.0F)
#  define Rte_InitValue_OutputRampMult_Uls_f32 (0.0F)
#  define Rte_InitValue_PosServCCDisable_Cnt_lgc (FALSE)
#  define Rte_InitValue_PowerLimitPerc_Uls_f32 (0.0F)
#  define Rte_InitValue_PreLimitForStall_MtrNm_f32 (0.0F)
#  define Rte_InitValue_PreLimitTorque_MtrNm_f32 (0.0F)
#  define Rte_InitValue_PrkAssistCmd_MtrNm_f32 (0.0F)
#  define Rte_InitValue_PullCompCmd_MtrNm_f32 (0.0F)
#  define Rte_InitValue_SumLimTrqCmd_MtrNm_f32 (0.0F)
#  define Rte_InitValue_TSMitCommand_MtrNm_f32 (0.0F)
#  define Rte_InitValue_ThermalLimit_MtrNm_f32 (8.8F)
#  define Rte_InitValue_ThermalLimitPerc_Uls_f32 (0.0F)
#  define Rte_InitValue_TrqLimitMin_MtrNm_f32 (0.0F)
#  define Rte_InitValue_VehSpd_Kph_f32 (0.0F)
#  define Rte_InitValue_WheelImbalanceCmd_MtrNm_f32 (0.0F)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_Ap_10_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

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

#  define Rte_IRead_AstLmt_Per1_AssistCmd_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_AssistCmd_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_AssistEOTDamping_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_AssistEOTDamping_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_AssistEOTGain_Uls_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_LmtCod_EOTGainLtd_Uls_f32.value)

#  define Rte_IRead_AstLmt_Per1_AssistEOTLimit_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_LmtCod_EOTLimitLtd_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_AssistStallLimit_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_LmtCod_StallLimitLtd_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_AssistVehSpdLimit_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_LmtCod_VehSpdLimitLtd_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_CombinedDamping_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_CombinedDamping_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_DefeatLimitService_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_DefeatLimitService_Cnt_lgc.value)

#  define Rte_IRead_AstLmt_Per1_LimitedReturn_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_LimitedReturn_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_LrnPnCtrCCDisable_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_LrnPnCtrCCDisable_Cnt_lgc.value)

#  define Rte_IRead_AstLmt_Per1_LrnPnCtrEnable_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_LrnPnCtrEnable_Cnt_lgc.value)

#  define Rte_IRead_AstLmt_Per1_LrnPnCtrTCmd_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_LrnPnCtrTCmd_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_OpTrqOvr_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_OpTrqOvr_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_OutputRampMult_Uls_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_LmtCod_OutputRampMultLtd_Uls_f32.value)

#  define Rte_IRead_AstLmt_Per1_PosServCCDisable_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_PosServCCDisable_Cnt_lgc.value)

#  define Rte_IRead_AstLmt_Per1_PowerLimitPerc_Uls_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_PowerLimitPerc_Uls_f32.value)

#  define Rte_IRead_AstLmt_Per1_PrkAssistCmd_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_PrkAssistCmd_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_PullCompCmd_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_PullCompCmd_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_TSMitCommand_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_TSMitCommand_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_ThermalLimitPerc_Uls_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_ThermalLimitPerc_Uls_f32.value)

#  define Rte_IRead_AstLmt_Per1_ThermalLimit_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_LmtCod_ThermalLimitLtd_MtrNm_f32.value)

#  define Rte_IRead_AstLmt_Per1_VehSpd_Kph_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_SignlCondn_VehicleSpeed_Kph_f32.value)

#  define Rte_IRead_AstLmt_Per1_WheelImbalanceCmd_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_WheelImbalanceCmd_MtrNm_f32.value)

#  define Rte_IWrite_AstLmt_Per1_LimitPercentFiltered_Uls_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_LimitPercentFiltered_Uls_f32.value = (data) \
  )

#  define Rte_IWriteRef_AstLmt_Per1_LimitPercentFiltered_Uls_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_LimitPercentFiltered_Uls_f32.value)

#  define Rte_IWrite_AstLmt_Per1_PreLimitForStall_MtrNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_PreLimitForStall_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_AstLmt_Per1_PreLimitForStall_MtrNm_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_PreLimitForStall_MtrNm_f32.value)

#  define Rte_IWrite_AstLmt_Per1_PreLimitTorque_MtrNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_PreLimitTorque_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_AstLmt_Per1_PreLimitTorque_MtrNm_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_PreLimitTorque_MtrNm_f32.value)

#  define Rte_IWrite_AstLmt_Per1_SumLimTrqCmd_MtrNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_AstLmt_SumLimTrqCmd_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_AstLmt_Per1_SumLimTrqCmd_MtrNm_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_AstLmt_SumLimTrqCmd_MtrNm_f32.value)

#  define Rte_IWrite_AstLmt_Per1_TrqLimitMin_MtrNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_TrqLimitMin_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_AstLmt_Per1_TrqLimitMin_MtrNm_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_AstLmt_AstLmt_Per1.Rte_TrqLimitMin_MtrNm_f32.value)


/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_VehSpd_Kph_f32 Rte_Read_Ap_AstLmt_VehSpd_Kph_f32
#  define Rte_Read_Ap_AstLmt_VehSpd_Kph_f32(data) (*(data) = Rte_SignlCondn_VehicleSpeed_Kph_f32, ((Std_ReturnType)RTE_E_OK))


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

#  define Rte_Call_SteeringAsstDefeat_WriteBlock(arg1) (NvMProxy_WriteBlock((UInt8)13, arg1))


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT
#   define RTE_START_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

extern VAR(Boolean, RTE_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP) Rte_AstLmt_SteerAsstDefeat;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  define Rte_Pim_SteerAsstDefeat() \
  (&Rte_AstLmt_SteerAsstDefeat)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_ASTLMT_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ASTLMT_APPL_CODE) AstLmt_Init(void);

FUNC(void, RTE_AP_ASTLMT_APPL_CODE) AstLmt_Per1(void);

FUNC(void, RTE_AP_ASTLMT_APPL_CODE) AstLmt_Scom_GetSteeringAssistDefeat(P2VAR(Boolean, AUTOMATIC, RTE_AP_ASTLMT_APPL_VAR) SteeringAsstDefeat_Cnt_lgc);

FUNC(Std_ReturnType, RTE_AP_ASTLMT_APPL_CODE) AstLmt_Scom_ManualTrqCmd(Boolean EnableManualCtrl, Float MtrTrqCmd_MtrNm_f32);

FUNC(void, RTE_AP_ASTLMT_APPL_CODE) AstLmt_Scom_SetSteeringAssistDefeat(Boolean SteeringAsstDefeat_Cnt_lgc);

# define RTE_STOP_SEC_AP_ASTLMT_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_AssistLmtFunc_Scom_RTE_E_MtrTrqLmt_SCom_VSTH (34U)

#  define RTE_E_AssistLmtFunc_Scom_RTE_E_OK (1U)

#  define RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_ASTLMT_H */
