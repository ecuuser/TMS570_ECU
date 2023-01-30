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
 *          File:  Components/Rte_Ap_DiagSvc.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_DIAGSVC_H
# define _RTE_AP_DIAGSVC_H

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

#  define RTE_START_SEC_VAR_INIT_UNSPECIFIED
#  include "MemMap.h"

/************************************************************************/
/* extern declaration of RTE buffers for optimized macro implementation */
/************************************************************************/
extern VAR(CityUserEnableDisable, RTE_VAR_INIT) Rte_DiagSvc_CityUserEnableDisable_Cnt_enum;
extern VAR(Boolean, RTE_VAR_INIT) Rte_DiagSvc_DisableFailSafeReaction_Cnt_lgc;
extern VAR(Boolean, RTE_VAR_INIT) Rte_SrlComInput_CityModeSts_Cnt_lgc;
extern VAR(DT_CmdIgn_FailSts, RTE_VAR_INIT) Rte_SrlComInput_CmdIgnFailSts_Cnt_u8;
extern VAR(DT_CmdIgnSts, RTE_VAR_INIT) Rte_SrlComInput_CmdIgnSts_Cnt_u16;
extern VAR(Boolean, RTE_VAR_INIT) Rte_SrlComOutput_ElectricStrFailSts_Cnt_lgc;
extern VAR(Float, RTE_VAR_INIT) Rte_AbsHwPos_HandwheelPosition_HwDeg_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_Sweep_OutputHwTrq_HwNm_f32;
extern VAR(ManufModeType, RTE_VAR_INIT) Rte_CDDInterface_MEC_Cnt_enum;
extern VAR(DT_OperationalModeSts, RTE_VAR_INIT) Rte_SrlComInput_OperationalModeSts_Cnt_u16;
extern VAR(UInt16, RTE_VAR_INIT) Rte_VehPwrMd_PowerLatchTimeDID191D_Cnt_u16;
extern VAR(Float, RTE_VAR_INIT) Rte_CtrlTemp_FiltMeasTemp_DegC_f32;
extern VAR(UInt32, RTE_VAR_INIT) Rte_SrlComInput_TotalOdometerIPC_Cnt_u32;
extern VAR(Float, RTE_VAR_INIT) Rte_BatteryVoltage_Vecu_Volt_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_SignlCondn_VehicleSpeed_Kph_f32;
extern VAR(Boolean, RTE_VAR_INIT) Rte_SrlComInput_VehicleSpeedValid_Cnt_lgc;

#  define RTE_STOP_SEC_VAR_INIT_UNSPECIFIED
#  include "MemMap.h"

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_CityModeSts_Cnt_lgc (FALSE)
#  define Rte_InitValue_CityUserEnableDisable_Cnt_enum (0U)
#  define Rte_InitValue_CmdIgnFailSts_Cnt_u8 (0U)
#  define Rte_InitValue_CmdIgnSts_Cnt_u16 (0U)
#  define Rte_InitValue_DesiredTunSet_Cnt_u16 (0U)
#  define Rte_InitValue_DisableFailSafeReaction_Cnt_lgc (FALSE)
#  define Rte_InitValue_ElectricStrFailSts_Cnt_lgc (FALSE)
#  define Rte_InitValue_HwPos_HwDeg_f32 (0.0F)
#  define Rte_InitValue_HwTrq_HwNm_f32 (0.0F)
#  define Rte_InitValue_IgnitionPreStart_Cnt_lgc (FALSE)
#  define Rte_InitValue_MEC_Cnt_enum (0U)
#  define Rte_InitValue_OperationalModeSts_Cnt_u16 (0U)
#  define Rte_InitValue_PowerLatchTimeDID191D_Cnt_u16 (0U)
#  define Rte_InitValue_ProxiValid_Cnt_lgc (FALSE)
#  define Rte_InitValue_StartStopLogicEnable_Cnt_lgc (FALSE)
#  define Rte_InitValue_Temperature_DegC_f32_DegC_f32 (0.0F)
#  define Rte_InitValue_TotalOdometerIPC_Cnt_u32 (0U)
#  define Rte_InitValue_Vecu_Volt_f32_Volt_f32 (5.0F)
#  define Rte_InitValue_VehSpd_Kph_f32 (0.0F)
#  define Rte_InitValue_VehicleSpeedValid_Cnt_lgc (FALSE)
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

extern VAR(Rte_tsTask_Init_9, RTE_VAR_NOINIT) Rte_Task_Init_9;

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

#  define Rte_IRead_DiagSvc_Init1_MEC_Cnt_enum() \
  (Rte_Task_Init_9.Rte_RB.Rte_Ap_DiagSvc_DiagSvc_Init1.Rte_MEC_Cnt_enum.value)

#  define Rte_IWrite_DiagSvc_Init1_DesiredTunSet_Cnt_u16(data) \
  ( \
    Rte_Task_Init_9.Rte_RB.Rte_Ap_DiagSvc_DiagSvc_Init1.Rte_DesiredTunSet_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_DiagSvc_Init1_DesiredTunSet_Cnt_u16() \
  (&Rte_Task_Init_9.Rte_RB.Rte_Ap_DiagSvc_DiagSvc_Init1.Rte_DesiredTunSet_Cnt_u16.value)

#  define Rte_IWrite_DiagSvc_Init1_IgnitionPreStart_Cnt_lgc(data) \
  ( \
    Rte_Task_Init_9.Rte_RB.Rte_Ap_DiagSvc_DiagSvc_Init1.Rte_IgnitionPreStart_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_DiagSvc_Init1_IgnitionPreStart_Cnt_lgc() \
  (&Rte_Task_Init_9.Rte_RB.Rte_Ap_DiagSvc_DiagSvc_Init1.Rte_IgnitionPreStart_Cnt_lgc.value)

#  define Rte_IWrite_DiagSvc_Init1_ProxiValid_Cnt_lgc(data) \
  ( \
    Rte_Task_Init_9.Rte_RB.Rte_Ap_DiagSvc_DiagSvc_Init1.Rte_ProxiValid_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_DiagSvc_Init1_ProxiValid_Cnt_lgc() \
  (&Rte_Task_Init_9.Rte_RB.Rte_Ap_DiagSvc_DiagSvc_Init1.Rte_ProxiValid_Cnt_lgc.value)

#  define Rte_IWrite_DiagSvc_Init1_StartStopLogicEnable_Cnt_lgc(data) \
  ( \
    Rte_Task_Init_9.Rte_RB.Rte_Ap_DiagSvc_DiagSvc_Init1.Rte_StartStopLogicEnable_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_DiagSvc_Init1_StartStopLogicEnable_Cnt_lgc() \
  (&Rte_Task_Init_9.Rte_RB.Rte_Ap_DiagSvc_DiagSvc_Init1.Rte_StartStopLogicEnable_Cnt_lgc.value)


/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_CityModeSts_Cnt_lgc Rte_Read_Ap_DiagSvc_CityModeSts_Cnt_lgc
#  define Rte_Read_Ap_DiagSvc_CityModeSts_Cnt_lgc(data) (*(data) = Rte_SrlComInput_CityModeSts_Cnt_lgc, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_CmdIgnFailSts_Cnt_u8 Rte_Read_Ap_DiagSvc_CmdIgnFailSts_Cnt_u8
#  define Rte_Read_Ap_DiagSvc_CmdIgnFailSts_Cnt_u8(data) (*(data) = Rte_SrlComInput_CmdIgnFailSts_Cnt_u8, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_CmdIgnSts_Cnt_u16 Rte_Read_Ap_DiagSvc_CmdIgnSts_Cnt_u16
#  define Rte_Read_Ap_DiagSvc_CmdIgnSts_Cnt_u16(data) (*(data) = Rte_SrlComInput_CmdIgnSts_Cnt_u16, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_ElectricStrFailSts_Cnt_lgc Rte_Read_Ap_DiagSvc_ElectricStrFailSts_Cnt_lgc
#  define Rte_Read_Ap_DiagSvc_ElectricStrFailSts_Cnt_lgc(data) (*(data) = Rte_SrlComOutput_ElectricStrFailSts_Cnt_lgc, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_HwPos_HwDeg_f32 Rte_Read_Ap_DiagSvc_HwPos_HwDeg_f32
#  define Rte_Read_Ap_DiagSvc_HwPos_HwDeg_f32(data) (*(data) = Rte_AbsHwPos_HandwheelPosition_HwDeg_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_HwTrq_HwNm_f32 Rte_Read_Ap_DiagSvc_HwTrq_HwNm_f32
#  define Rte_Read_Ap_DiagSvc_HwTrq_HwNm_f32(data) (*(data) = Rte_Sweep_OutputHwTrq_HwNm_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_MEC_Cnt_enum Rte_Read_Ap_DiagSvc_MEC_Cnt_enum
#  define Rte_Read_Ap_DiagSvc_MEC_Cnt_enum(data) (*(data) = Rte_CDDInterface_MEC_Cnt_enum, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_OperationalModeSts_Cnt_u16 Rte_Read_Ap_DiagSvc_OperationalModeSts_Cnt_u16
#  define Rte_Read_Ap_DiagSvc_OperationalModeSts_Cnt_u16(data) (*(data) = Rte_SrlComInput_OperationalModeSts_Cnt_u16, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_PowerLatchTimeDID191D_Cnt_u16 Rte_Read_Ap_DiagSvc_PowerLatchTimeDID191D_Cnt_u16
#  define Rte_Read_Ap_DiagSvc_PowerLatchTimeDID191D_Cnt_u16(data) (*(data) = Rte_VehPwrMd_PowerLatchTimeDID191D_Cnt_u16, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_Temperature_DegC_f32_DegC_f32 Rte_Read_Ap_DiagSvc_Temperature_DegC_f32_DegC_f32
#  define Rte_Read_Ap_DiagSvc_Temperature_DegC_f32_DegC_f32(data) (*(data) = Rte_CtrlTemp_FiltMeasTemp_DegC_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_TotalOdometerIPC_Cnt_u32 Rte_Read_Ap_DiagSvc_TotalOdometerIPC_Cnt_u32
#  define Rte_Read_Ap_DiagSvc_TotalOdometerIPC_Cnt_u32(data) (*(data) = Rte_SrlComInput_TotalOdometerIPC_Cnt_u32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_Vecu_Volt_f32_Volt_f32 Rte_Read_Ap_DiagSvc_Vecu_Volt_f32_Volt_f32
#  define Rte_Read_Ap_DiagSvc_Vecu_Volt_f32_Volt_f32(data) (*(data) = Rte_BatteryVoltage_Vecu_Volt_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_VehSpd_Kph_f32 Rte_Read_Ap_DiagSvc_VehSpd_Kph_f32
#  define Rte_Read_Ap_DiagSvc_VehSpd_Kph_f32(data) (*(data) = Rte_SignlCondn_VehicleSpeed_Kph_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_VehicleSpeedValid_Cnt_lgc Rte_Read_Ap_DiagSvc_VehicleSpeedValid_Cnt_lgc
#  define Rte_Read_Ap_DiagSvc_VehicleSpeedValid_Cnt_lgc(data) (*(data) = Rte_SrlComInput_VehicleSpeedValid_Cnt_lgc, ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Write_CityUserEnableDisable_Cnt_enum Rte_Write_Ap_DiagSvc_CityUserEnableDisable_Cnt_enum
#  define Rte_Write_Ap_DiagSvc_CityUserEnableDisable_Cnt_enum(data) (Rte_DiagSvc_CityUserEnableDisable_Cnt_enum = (data), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Write_DisableFailSafeReaction_Cnt_lgc Rte_Write_Ap_DiagSvc_DisableFailSafeReaction_Cnt_lgc
#  define Rte_Write_Ap_DiagSvc_DisableFailSafeReaction_Cnt_lgc(data) (Rte_DiagSvc_DisableFailSafeReaction_Cnt_lgc = (data), ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState_Mode() Rte_ModeMachine_StaMd9_SystemState9_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_NTWRAP_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NTWRAP_APPL_CODE) NtWrapC_AbsHwPos_SCom_CustClrTrim(void);
#  define RTE_STOP_SEC_NTWRAP_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_AbsHwPos_SCom_CustClrTrim() (NtWrapC_AbsHwPos_SCom_CustClrTrim(), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NTWRAP_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_NTWRAP_APPL_CODE) NtWrapC_AbsHwPos_SCom_CustSetTrim(void);
#  define RTE_STOP_SEC_NTWRAP_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_AbsHwPos_SCom_CustSetTrim NtWrapC_AbsHwPos_SCom_CustSetTrim
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NVM_APPL_CODE) NvM_GetErrorStatus(NvM_BlockIdType parg0, P2VAR(NvM_RequestResultType, AUTOMATIC, RTE_NVM_APPL_VAR) ErrorStatus);
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_AppSwFingerPrint_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)46, arg1), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h"
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_ReadBlock(NvM_BlockIdType parg0, P2VAR(UInt8, AUTOMATIC, RTE_NVM_APPL_VAR) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_ReadBlock(NvM_BlockIdType parg0, P2VAR(NvM_DestPtr, AUTOMATIC, RTE_NVM_APPL_VAR) DstPtr);
# endif
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_AppSwFingerPrint_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)46, arg1))
#  define Rte_Call_BootSwFingerPrint_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)45, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_BootSwFingerPrint_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)45, arg1))
#  define Rte_Call_CalSwFingerPrint_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)94, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_CalSwFingerPrint_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)94, arg1))
#  define RTE_START_SEC_DCM_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_DCM_APPL_CODE) Dcm_GetSecurityLevel(P2VAR(Dcm_SecLevelType, AUTOMATIC, RTE_DCM_APPL_VAR) SecLevel);
#  define RTE_STOP_SEC_DCM_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_DCMServices_GetSecurityLevel Dcm_GetSecurityLevel
#  define RTE_START_SEC_NTWRAP_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NTWRAP_APPL_CODE) NtWrapC_DigColPs_SCom_CustClrTrim(void);
#  define RTE_STOP_SEC_NTWRAP_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_DigColPs_SCom_CustClearTrim() (NtWrapC_DigColPs_SCom_CustClrTrim(), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NTWRAP_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_NTWRAP_APPL_CODE) NtWrapC_DigColPs_SCom_CustSetTrim(void);
#  define RTE_STOP_SEC_NTWRAP_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_DigColPs_SCom_CustSetTrim NtWrapC_DigColPs_SCom_CustSetTrim
#  define Rte_Call_ECULifeTimeMins_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)95, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_ECULifeTimeMins_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)95, arg1))
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h"
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_WriteBlock(NvM_BlockIdType parg0, P2CONST(UInt8, AUTOMATIC, RTE_NVM_APPL_DATA) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_WriteBlock(NvM_BlockIdType parg0, P2CONST(NvM_DestPtr, AUTOMATIC, RTE_NVM_APPL_DATA) DstPtr);
# endif
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_ECULifeTimeMins_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)95, arg1))
#  define Rte_Call_ECUSerialNumberData_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)101, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_ECUSerialNumberData_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)101, arg1))
#  define Rte_Call_ECUSerialNumberData_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)101, arg1))
#  define Rte_Call_ECUSparePartNo_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)48, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_ECUSparePartNo_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)48, arg1))
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NVM_APPL_CODE) NvM_SetRamBlockStatus(NvM_BlockIdType parg0, Boolean RamBlockStatus);
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_ECUSparePartNo_SetRamBlockStatus(arg1) (NvM_SetRamBlockStatus((NvM_BlockIdType)48, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_EOLConfiguration_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)98, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_EOLConfiguration_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)98, arg1))
#  define Rte_Call_EOLConfiguration_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)98, arg1))
#  define Rte_Call_EraseRoutineStatus_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)57, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_EraseRoutineStatus_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)57, arg1))
#  define Rte_Call_FirstDTCDetectMins_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)96, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_FirstDTCDetectMins_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)96, arg1))
#  define Rte_Call_FirstDTCDetectMins_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)96, arg1))
#  define Rte_Call_FirstDTCDetectSecs_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)97, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_FirstDTCDetectSecs_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)97, arg1))
#  define Rte_Call_FirstDTCDetectSecs_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)97, arg1))
#  define RTE_START_SEC_AP_LRNEOT_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_AP_LRNEOT_APPL_CODE) LrnEOT_Scom_ResetEOT(void);
#  define RTE_STOP_SEC_AP_LRNEOT_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_LrnEOT_Scom_ResetEOT() (LrnEOT_Scom_ResetEOT(), ((Std_ReturnType)RTE_E_OK))
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
#  define Rte_Call_OdometerFlashProg_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)103, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_OdometerFlashProg_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)103, arg1))
#  define Rte_Call_ProgrammingAttemptCounter_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)99, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_ProgrammingAttemptCounter_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)99, arg1))
#  define Rte_Call_ProgrammingStatus_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)58, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_ProgrammingStatus_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)58, arg1))
#  define Rte_Call_ProxiConfiguration_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)92, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_ProxiConfiguration_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)92, arg1))
#  define Rte_Call_ProxiConfiguration_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)92, arg1))
#  define Rte_Call_ProxiCounter_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)93, arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_ProxiCounter_ReadBlock(arg1) (NvM_ReadBlock((NvM_BlockIdType)93, arg1))
#  define Rte_Call_ProxiCounter_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)93, arg1))
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) DtrmnElapsedTime_mS_u16(UInt32 InitialTime, P2VAR(UInt16, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) ElapsedTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(arg1, arg2) (DtrmnElapsedTime_mS_u16(arg1, arg2), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) DtrmnElapsedTime_mS_u32(UInt32 InitialTime, P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) ElapsedTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(arg1, arg2) (DtrmnElapsedTime_mS_u32(arg1, arg2), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) GetSystemTime_mS_u32(P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) CurrentTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_GetSystemTime_mS_u32(arg1) (GetSystemTime_mS_u32(arg1), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Call_TotalOdometer_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)102, arg1))
#  define Rte_Call_TuningSetSelect_GetErrorStatus(arg1) (NvM_GetErrorStatus((NvM_BlockIdType)26, arg1), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_InvalidateNvBlock(NvM_BlockIdType parg0);
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_TuningSetSelect_InvalidateNvBlock() (NvM_InvalidateNvBlock((NvM_BlockIdType)26))
#  define Rte_Call_TuningSetSelect_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)26, arg1))
#  define RTE_START_SEC_NTWRAP_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NTWRAP_APPL_CODE) NtWrapC_VehDyn_SCom_ResetCenter(void);
#  define RTE_STOP_SEC_NTWRAP_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_VehDyn_SCom_ResetCenter() (NtWrapC_VehDyn_SCom_ResetCenter(), ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT
#   define RTE_START_SEC_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

extern VAR(UInt32, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_ECULifeTimeMinsData;
extern VAR(UInt32, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_FirstDTCDetectMinsData;
extern VAR(UInt16, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_FirstDTCDetectSecsData;
extern VAR(UInt16, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_OdometerFlashProgData;
extern VAR(UInt16, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_TotalOdometerData;
extern VAR(UInt16, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_TuningSetSelectData;
extern VAR(Dcm_14Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_AppSwFingerPrintData;
extern VAR(Dcm_14Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_BootSwFingerPrintData;
extern VAR(Dcm_14Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_CalSwFingerPrintData;
extern VAR(Dcm_16Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_ECUSerialNumberData;
extern VAR(Dcm_11Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_ECUSparePartNoData;
extern VAR(Dcm_9Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_EOLConfigurationData;
extern VAR(Dcm_1Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_EraseRoutineStatusData;
extern VAR(Dcm_8Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_ProgrammingAttemptCounterData;
extern VAR(Dcm_1Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_ProgrammingStatusData;
extern VAR(Dcm_255Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_ProxiConfigurationData;
extern VAR(Dcm_1Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_ProxiCounterData;
extern VAR(Dcm_17Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_VINCurrentData;
extern VAR(Dcm_17Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_VINOriginalData;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  define Rte_Pim_ECULifeTimeMinsData() \
  (&Rte_DiagSvc_ECULifeTimeMinsData)

#  define Rte_Pim_FirstDTCDetectMinsData() \
  (&Rte_DiagSvc_FirstDTCDetectMinsData)

#  define Rte_Pim_FirstDTCDetectSecsData() \
  (&Rte_DiagSvc_FirstDTCDetectSecsData)

#  define Rte_Pim_OdometerFlashProgData() \
  (&Rte_DiagSvc_OdometerFlashProgData)

#  define Rte_Pim_TotalOdometerData() \
  (&Rte_DiagSvc_TotalOdometerData)

#  define Rte_Pim_TuningSetSelectData() \
  (&Rte_DiagSvc_TuningSetSelectData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_AppSwFingerPrintData() (&((*RtePim_AppSwFingerPrintData())[0]))
#  else
#   define Rte_Pim_AppSwFingerPrintData() RtePim_AppSwFingerPrintData()
#  endif
#  define RtePim_AppSwFingerPrintData() \
  (&Rte_DiagSvc_AppSwFingerPrintData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_BootSwFingerPrintData() (&((*RtePim_BootSwFingerPrintData())[0]))
#  else
#   define Rte_Pim_BootSwFingerPrintData() RtePim_BootSwFingerPrintData()
#  endif
#  define RtePim_BootSwFingerPrintData() \
  (&Rte_DiagSvc_BootSwFingerPrintData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_CalSwFingerPrintData() (&((*RtePim_CalSwFingerPrintData())[0]))
#  else
#   define Rte_Pim_CalSwFingerPrintData() RtePim_CalSwFingerPrintData()
#  endif
#  define RtePim_CalSwFingerPrintData() \
  (&Rte_DiagSvc_CalSwFingerPrintData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_ECUSerialNumberData() (&((*RtePim_ECUSerialNumberData())[0]))
#  else
#   define Rte_Pim_ECUSerialNumberData() RtePim_ECUSerialNumberData()
#  endif
#  define RtePim_ECUSerialNumberData() \
  (&Rte_DiagSvc_ECUSerialNumberData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_ECUSparePartNoData() (&((*RtePim_ECUSparePartNoData())[0]))
#  else
#   define Rte_Pim_ECUSparePartNoData() RtePim_ECUSparePartNoData()
#  endif
#  define RtePim_ECUSparePartNoData() \
  (&Rte_DiagSvc_ECUSparePartNoData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_EOLConfigurationData() (&((*RtePim_EOLConfigurationData())[0]))
#  else
#   define Rte_Pim_EOLConfigurationData() RtePim_EOLConfigurationData()
#  endif
#  define RtePim_EOLConfigurationData() \
  (&Rte_DiagSvc_EOLConfigurationData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_EraseRoutineStatusData() (&((*RtePim_EraseRoutineStatusData())[0]))
#  else
#   define Rte_Pim_EraseRoutineStatusData() RtePim_EraseRoutineStatusData()
#  endif
#  define RtePim_EraseRoutineStatusData() \
  (&Rte_DiagSvc_EraseRoutineStatusData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_ProgrammingAttemptCounterData() (&((*RtePim_ProgrammingAttemptCounterData())[0]))
#  else
#   define Rte_Pim_ProgrammingAttemptCounterData() RtePim_ProgrammingAttemptCounterData()
#  endif
#  define RtePim_ProgrammingAttemptCounterData() \
  (&Rte_DiagSvc_ProgrammingAttemptCounterData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_ProgrammingStatusData() (&((*RtePim_ProgrammingStatusData())[0]))
#  else
#   define Rte_Pim_ProgrammingStatusData() RtePim_ProgrammingStatusData()
#  endif
#  define RtePim_ProgrammingStatusData() \
  (&Rte_DiagSvc_ProgrammingStatusData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_ProxiConfigurationData() (&((*RtePim_ProxiConfigurationData())[0]))
#  else
#   define Rte_Pim_ProxiConfigurationData() RtePim_ProxiConfigurationData()
#  endif
#  define RtePim_ProxiConfigurationData() \
  (&Rte_DiagSvc_ProxiConfigurationData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_ProxiCounterData() (&((*RtePim_ProxiCounterData())[0]))
#  else
#   define Rte_Pim_ProxiCounterData() RtePim_ProxiCounterData()
#  endif
#  define RtePim_ProxiCounterData() \
  (&Rte_DiagSvc_ProxiCounterData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_VINCurrentData() (&((*RtePim_VINCurrentData())[0]))
#  else
#   define Rte_Pim_VINCurrentData() RtePim_VINCurrentData()
#  endif
#  define RtePim_VINCurrentData() \
  (&Rte_DiagSvc_VINCurrentData)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_VINOriginalData() (&((*RtePim_VINOriginalData())[0]))
#  else
#   define Rte_Pim_VINOriginalData() RtePim_VINOriginalData()
#  endif
#  define RtePim_VINOriginalData() \
  (&Rte_DiagSvc_VINOriginalData)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_DIAGSVC_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) ComControlService_CheckCondition(UInt8 subNetId, UInt8 msgType, Boolean rxState, Boolean txState);

FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_Init1(void);

FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_Per1(void);

FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_SCom_GetTuningSet(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) TuningSet_Cnt_T_u08);

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_SCom_SetTuningSet(UInt8 TuningSet_Cnt_T_u08);

FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_Trns1(void);

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0885_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0885_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ad9_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ad9_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ada_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ada_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0adb_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0adb_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0adc_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0adc_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ade_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ade_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1002_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1002_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1004_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1004_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1006_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1006_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1008_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1008_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1009_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1009_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x102a_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x102a_ReadData(P2VAR(Dcm_9Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x191d_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x191d_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1921_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1921_ReadData(P2VAR(Dcm_9Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2001_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2001_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2002_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2002_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2003_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2003_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2008_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2008_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200a_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200a_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200b_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200b_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200c_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200c_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2010_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2010_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2014_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2014_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2023_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2023_WriteData(P2VAR(Dcm_255Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2024_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2024_ReadData(P2VAR(Dcm_6Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x292e_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x292e_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ResetToDefault(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ResetToDefault(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ShortTermAdjustment(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5052_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5052_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5052_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5052_ShortTermAdjustment(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ResetToDefault(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ResetToDefault(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ShortTermAdjustment(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf100_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf100_ReadData(P2VAR(Dcm_7Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf10b_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf10b_ReadData(P2VAR(Dcm_4092Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf10b_ReadDataLength(P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) DidLength);

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf10d_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf10d_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf154_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf154_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf155_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf155_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf158_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf158_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf180_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf180_ReadData(P2VAR(Dcm_14Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf181_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf181_ReadData(P2VAR(Dcm_14Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf182_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf182_ReadData(P2VAR(Dcm_14Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf183_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf183_ReadData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf183_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf183_WriteData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf184_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf184_ReadData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf184_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf184_WriteData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf185_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf185_ReadData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf185_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf185_WriteData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf186_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf186_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_WriteData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf188_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf188_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18c_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18c_ReadData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18c_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18c_WriteData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf191_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf191_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf192_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf192_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf193_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf193_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf194_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf194_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf195_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf195_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a0_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a0_ReadData(P2VAR(Dcm_67Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a3_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a3_ReadData(P2VAR(Dcm_6Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a4_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a4_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd01_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd01_ReadData(P2VAR(Dcm_322Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd03_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd03_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd03_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd03_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ShortTermAdjustment(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0e_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0e_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd10_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd10_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ShortTermAdjustment(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_ReadData(P2VAR(Dcm_28Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_WriteData(P2VAR(Dcm_28Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd13_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd13_ReadData(P2VAR(Dcm_75Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd14_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd14_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd17_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd17_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1a_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1a_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1c_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1c_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd20_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd20_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_WriteData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_ReadData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_WriteData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd31_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd31_ReadData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_ReadData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_WriteData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_ReadData(P2VAR(Dcm_64Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_WriteData(P2VAR(Dcm_64Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdad_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdad_ReadData(P2VAR(Dcm_7Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdaf_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdaf_ReadData(P2VAR(Dcm_176Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_WriteData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_ReadData(P2VAR(Dcm_18Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_WriteData(P2VAR(Dcm_18Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) ResetService_EcuReset(UInt8 resetType, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0x0200_RequestResults(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0x0200_RequestResults(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0x0200_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0x0200_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd001_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd001_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd001_Stop(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd001_Stop(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd002_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd002_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf000_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf000_Start(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf001_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf001_Start(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf003_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf003_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf004_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf004_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf005_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf005_Start(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf008_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf008_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_RequestResults(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_RequestResults(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Stop(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Stop(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf0ff_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf0ff_Start(P2VAR(Dcm_6Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xfee0_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xfee0_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_CompareKey(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Key);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_CompareKey(P2VAR(Dcm_SecAccess_1_KeyType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Key);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_GetSeed(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) securityAccessDataRecord, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_GetSeed(P2VAR(Dcm_SecAccess_1_DataRecType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) securityAccessDataRecord, P2VAR(Dcm_SecAccess_1_SeedType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode);
# endif

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SessionControl_ChangeIndication(Dcm_SesCtrlType SesCtrlTypeOld, Dcm_SesCtrlType SesCtrlTypeNew);

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SessionControl_ConfirmationRespPending(Dcm_ConfirmationStatusType status);

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SessionControl_GetSesChgPermission(Dcm_SesCtrlType SesCtrlTypeActive, Dcm_SesCtrlType SesCtrlTypeNew);

# define RTE_STOP_SEC_AP_DIAGSVC_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_AbsHwPos_SCom_TrimNotPerformed (34U)

#  define RTE_E_ComControlService_E_COM_CTRL_NOT_ACCEPTED (40U)

#  define RTE_E_ComControlService_E_PENDING (10U)

#  define RTE_E_DCMServices_E_NOT_OK (1U)

#  define RTE_E_DiagSvc_SCom_E_OUTOFRANGE (49U)

#  define RTE_E_DidServices_0x0100_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x0100_E_PENDING (10U)

#  define RTE_E_DidServices_0x0885_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x0885_E_PENDING (10U)

#  define RTE_E_DidServices_0x0ad9_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x0ad9_E_PENDING (10U)

#  define RTE_E_DidServices_0x0ada_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x0ada_E_PENDING (10U)

#  define RTE_E_DidServices_0x0adb_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x0adb_E_PENDING (10U)

#  define RTE_E_DidServices_0x0adc_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x0adc_E_PENDING (10U)

#  define RTE_E_DidServices_0x0ade_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x0ade_E_PENDING (10U)

#  define RTE_E_DidServices_0x1002_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x1002_E_PENDING (10U)

#  define RTE_E_DidServices_0x1004_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x1004_E_PENDING (10U)

#  define RTE_E_DidServices_0x1006_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x1006_E_PENDING (10U)

#  define RTE_E_DidServices_0x1008_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x1008_E_PENDING (10U)

#  define RTE_E_DidServices_0x1009_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x1009_E_PENDING (10U)

#  define RTE_E_DidServices_0x102a_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x102a_E_PENDING (10U)

#  define RTE_E_DidServices_0x191d_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x191d_E_PENDING (10U)

#  define RTE_E_DidServices_0x1921_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x1921_E_PENDING (10U)

#  define RTE_E_DidServices_0x2001_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x2001_E_PENDING (10U)

#  define RTE_E_DidServices_0x2002_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x2002_E_PENDING (10U)

#  define RTE_E_DidServices_0x2003_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x2003_E_PENDING (10U)

#  define RTE_E_DidServices_0x2008_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x2008_E_PENDING (10U)

#  define RTE_E_DidServices_0x200a_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x200a_E_PENDING (10U)

#  define RTE_E_DidServices_0x200b_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x200b_E_PENDING (10U)

#  define RTE_E_DidServices_0x200c_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x200c_E_PENDING (10U)

#  define RTE_E_DidServices_0x2010_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x2010_E_PENDING (10U)

#  define RTE_E_DidServices_0x2014_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x2014_E_PENDING (10U)

#  define RTE_E_DidServices_0x2023_E_PENDING (10U)

#  define RTE_E_DidServices_0x2024_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x2024_E_PENDING (10U)

#  define RTE_E_DidServices_0x292e_E_NOT_OK (1U)

#  define RTE_E_DidServices_0x292e_E_PENDING (10U)

#  define RTE_E_DidServices_0x5051_E_PENDING (10U)

#  define RTE_E_DidServices_0x5052_E_PENDING (10U)

#  define RTE_E_DidServices_0x5aab_E_PENDING (10U)

#  define RTE_E_DidServices_0xf100_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf100_E_PENDING (10U)

#  define RTE_E_DidServices_0xf10b_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf10b_E_PENDING (10U)

#  define RTE_E_DidServices_0xf10d_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf10d_E_PENDING (10U)

#  define RTE_E_DidServices_0xf154_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf154_E_PENDING (10U)

#  define RTE_E_DidServices_0xf155_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf155_E_PENDING (10U)

#  define RTE_E_DidServices_0xf158_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf158_E_PENDING (10U)

#  define RTE_E_DidServices_0xf180_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf180_E_PENDING (10U)

#  define RTE_E_DidServices_0xf181_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf181_E_PENDING (10U)

#  define RTE_E_DidServices_0xf182_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf182_E_PENDING (10U)

#  define RTE_E_DidServices_0xf183_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf183_E_PENDING (10U)

#  define RTE_E_DidServices_0xf184_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf184_E_PENDING (10U)

#  define RTE_E_DidServices_0xf185_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf185_E_PENDING (10U)

#  define RTE_E_DidServices_0xf186_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf186_E_PENDING (10U)

#  define RTE_E_DidServices_0xf187_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf187_E_PENDING (10U)

#  define RTE_E_DidServices_0xf188_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf188_E_PENDING (10U)

#  define RTE_E_DidServices_0xf18c_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf18c_E_PENDING (10U)

#  define RTE_E_DidServices_0xf191_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf191_E_PENDING (10U)

#  define RTE_E_DidServices_0xf192_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf192_E_PENDING (10U)

#  define RTE_E_DidServices_0xf193_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf193_E_PENDING (10U)

#  define RTE_E_DidServices_0xf194_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf194_E_PENDING (10U)

#  define RTE_E_DidServices_0xf195_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf195_E_PENDING (10U)

#  define RTE_E_DidServices_0xf1a0_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf1a0_E_PENDING (10U)

#  define RTE_E_DidServices_0xf1a3_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf1a3_E_PENDING (10U)

#  define RTE_E_DidServices_0xf1a4_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xf1a4_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd01_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd01_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd02_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd02_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd03_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd03_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd07_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd07_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd0d_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd0e_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd0e_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd10_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd10_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd11_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd12_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd12_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd13_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd13_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd14_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd14_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd17_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd17_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd19_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd19_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd1a_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd1a_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd1b_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd1b_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd1c_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd1c_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd1e_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd1e_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd20_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd20_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd21_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd21_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd23_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd23_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd25_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd25_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd26_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd26_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd27_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd27_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd29_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd29_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd30_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd30_E_PENDING (10U)

#  define RTE_E_DidServices_0xfd31_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfd31_E_PENDING (10U)

#  define RTE_E_DidServices_0xfda1_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfda1_E_PENDING (10U)

#  define RTE_E_DidServices_0xfda2_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfda2_E_PENDING (10U)

#  define RTE_E_DidServices_0xfda3_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfda3_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdac_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdac_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdad_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdad_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdae_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdae_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdaf_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdaf_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdb0_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdb0_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdb1_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdb1_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdb2_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdb2_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdb3_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdb3_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdb4_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdb4_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdb5_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdb5_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdb6_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdb6_E_PENDING (10U)

#  define RTE_E_DidServices_0xfdb7_E_NOT_OK (1U)

#  define RTE_E_DidServices_0xfdb7_E_PENDING (10U)

#  define RTE_E_DigColPs_SCom_ConditionsNotCorrect (34U)

#  define RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK (1U)

#  define RTE_E_NxtrDiagMgr_E_NOT_OK (1U)

#  define RTE_E_ResetService_E_NOT_OK (1U)

#  define RTE_E_ResetService_E_PENDING (10U)

#  define RTE_E_RoutineServices_0x0200_E_PENDING (10U)

#  define RTE_E_RoutineServices_0xd001_E_PENDING (10U)

#  define RTE_E_RoutineServices_0xd002_E_PENDING (10U)

#  define RTE_E_RoutineServices_0xf000_E_PENDING (10U)

#  define RTE_E_RoutineServices_0xf001_E_PENDING (10U)

#  define RTE_E_RoutineServices_0xf003_E_PENDING (10U)

#  define RTE_E_RoutineServices_0xf004_E_PENDING (10U)

#  define RTE_E_RoutineServices_0xf005_E_PENDING (10U)

#  define RTE_E_RoutineServices_0xf008_E_PENDING (10U)

#  define RTE_E_RoutineServices_0xf009_E_PENDING (10U)

#  define RTE_E_RoutineServices_0xf0ff_E_PENDING (10U)

#  define RTE_E_RoutineServices_0xfee0_E_PENDING (10U)

#  define RTE_E_SecurityAccess_1_E_COMPARE_KEY_FAILED (11U)

#  define RTE_E_SecurityAccess_1_E_NOT_OK (1U)

#  define RTE_E_SecurityAccess_1_E_PENDING (10U)

#  define RTE_E_SessionControl_E_FORCE_RCRRP (12U)

#  define RTE_E_SessionControl_E_NOT_OK (1U)

#  define RTE_E_SessionControl_E_PENDING (10U)

#  define RTE_E_SessionControl_E_SESSION_NOT_ALLOWED (4U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_DIAGSVC_H */
