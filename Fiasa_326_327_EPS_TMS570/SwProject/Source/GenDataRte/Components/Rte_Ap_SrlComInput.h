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
 *          File:  Components/Rte_Ap_SrlComInput.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_SRLCOMINPUT_H
# define _RTE_AP_SRLCOMINPUT_H

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

#  define Rte_InitValue_Batt_Volt_f32 (0.0F)
#  define Rte_InitValue_CityModeSts_Cnt_lgc (FALSE)
#  define Rte_InitValue_CityUserEnableDisable_Cnt_enum (0U)
#  define Rte_InitValue_CmdIgnFailSts_Cnt_u8 (0U)
#  define Rte_InitValue_CmdIgnSts_Cnt_u16 (0U)
#  define Rte_InitValue_DefaultVehSpd_Cnt_lgc (FALSE)
#  define Rte_InitValue_DesiredTunPers_Cnt_u16 (0U)
#  define Rte_InitValue_DisableFailSafeReaction_Cnt_lgc (FALSE)
#  define Rte_InitValue_EngStartStopSts_Cnt_u8 (0U)
#  define Rte_InitValue_IgnitionPreStart_Cnt_lgc (FALSE)
#  define Rte_InitValue_MEC_Cnt_enum (0U)
#  define Rte_InitValue_OpModeStsCTCEnableCriteria_Cnt_lgc (FALSE)
#  define Rte_InitValue_OperationalModeSts_Cnt_u16 (0U)
#  define Rte_InitValue_RxMsgsSrlComSvcDft_Cnt_lgc (FALSE)
#  define Rte_InitValue_SrlComVehSpd_Kph_f32 (0.0F)
#  define Rte_InitValue_StartStopSts_Cnt_u8 (0U)
#  define Rte_InitValue_TotalOdometerIPC_Cnt_u32 (0U)
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

#  define Rte_IRead_SrlComInput_Per1_Batt_Volt_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_Batt_Volt_f32.value)

#  define Rte_IRead_SrlComInput_Per1_CityUserEnableDisable_Cnt_enum() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_CityUserEnableDisable_Cnt_enum.value)

#  define Rte_IRead_SrlComInput_Per1_DefaultVehSpd_Cnt_lgc() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_DefaultVehSpd_Cnt_lgc.value)

#  define Rte_IRead_SrlComInput_Per1_DisableFailSafeReaction_Cnt_lgc() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_DisableFailSafeReaction_Cnt_lgc.value)

#  define Rte_IRead_SrlComInput_Per1_IgnitionPreStart_Cnt_lgc() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_IgnitionPreStart_Cnt_lgc.value)

#  define Rte_IRead_SrlComInput_Per1_MEC_Cnt_enum() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_MEC_Cnt_enum.value)

#  define Rte_IRead_SrlComInput_Per1_RxMsgsSrlComSvcDft_Cnt_lgc() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_RxMsgsSrlComSvcDft_Cnt_lgc.value)

#  define Rte_IWrite_SrlComInput_Per1_CityModeSts_Cnt_lgc(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_CityModeSts_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_SrlComInput_Per1_CityModeSts_Cnt_lgc() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_CityModeSts_Cnt_lgc.value)

#  define Rte_IWrite_SrlComInput_Per1_CmdIgnFailSts_Cnt_u8(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_CmdIgnFailSts_Cnt_u8.value = (data) \
  )

#  define Rte_IWriteRef_SrlComInput_Per1_CmdIgnFailSts_Cnt_u8() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_CmdIgnFailSts_Cnt_u8.value)

#  define Rte_IWrite_SrlComInput_Per1_CmdIgnSts_Cnt_u16(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_CmdIgnSts_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_SrlComInput_Per1_CmdIgnSts_Cnt_u16() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_CmdIgnSts_Cnt_u16.value)

#  define Rte_IWrite_SrlComInput_Per1_DesiredTunPers_Cnt_u16(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_DesiredTunPers_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_SrlComInput_Per1_DesiredTunPers_Cnt_u16() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_DesiredTunPers_Cnt_u16.value)

#  define Rte_IWrite_SrlComInput_Per1_EngStartStopSts_Cnt_u8(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_EngStartStopSts_Cnt_u8.value = (data) \
  )

#  define Rte_IWriteRef_SrlComInput_Per1_EngStartStopSts_Cnt_u8() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_EngStartStopSts_Cnt_u8.value)

#  define Rte_IWrite_SrlComInput_Per1_OpModeStsCTCEnableCriteria_Cnt_lgc(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_OpModeStsCTCEnableCriteria_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_SrlComInput_Per1_OpModeStsCTCEnableCriteria_Cnt_lgc() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_OpModeStsCTCEnableCriteria_Cnt_lgc.value)

#  define Rte_IWrite_SrlComInput_Per1_OperationalModeSts_Cnt_u16(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_OperationalModeSts_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_SrlComInput_Per1_OperationalModeSts_Cnt_u16() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_OperationalModeSts_Cnt_u16.value)

#  define Rte_IWrite_SrlComInput_Per1_SrlComVehSpd_Kph_f32(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_SrlComVehSpd_Kph_f32.value = (data) \
  )

#  define Rte_IWriteRef_SrlComInput_Per1_SrlComVehSpd_Kph_f32() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_SrlComVehSpd_Kph_f32.value)

#  define Rte_IWrite_SrlComInput_Per1_StartStopSts_Cnt_u8(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_StartStopSts_Cnt_u8.value = (data) \
  )

#  define Rte_IWriteRef_SrlComInput_Per1_StartStopSts_Cnt_u8() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_StartStopSts_Cnt_u8.value)

#  define Rte_IWrite_SrlComInput_Per1_TotalOdometerIPC_Cnt_u32(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_TotalOdometerIPC_Cnt_u32.value = (data) \
  )

#  define Rte_IWriteRef_SrlComInput_Per1_TotalOdometerIPC_Cnt_u32() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_TotalOdometerIPC_Cnt_u32.value)

#  define Rte_IWrite_SrlComInput_Per1_VehicleSpeedValid_Cnt_lgc(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_VehicleSpeedValid_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_SrlComInput_Per1_VehicleSpeedValid_Cnt_lgc() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_SrlComInput_SrlComInput_Per1.Rte_VehicleSpeedValid_Cnt_lgc.value)


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState_Mode() Rte_ModeMachine_StaMd9_SystemState9_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_COMM_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_RequestComMode(ComM_UserHandleType parg0, ComM_ModeType ComMode);
#  define RTE_STOP_SEC_COMM_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_ComM_UserRequest_RequestComMode(arg1) (ComM_RequestComMode((ComM_UserHandleType)0, arg1))
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
FUNC(Std_ReturnType, RTE_AP_DIAGMGR9_APPL_CODE) NxtrDiagMgr9_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);
#  define RTE_STOP_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_SetNTCStatus NxtrDiagMgr9_SetNTCStatus
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


# define RTE_START_SEC_AP_SRLCOMINPUT_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_SRLCOMINPUT_APPL_CODE) SrlComInput_Init(void);

FUNC(void, RTE_AP_SRLCOMINPUT_APPL_CODE) SrlComInput_Per1(void);

FUNC(void, RTE_AP_SRLCOMINPUT_APPL_CODE) SrlComInput_SCom_ManualVehSpd(Float VehSpd_Kph_T_f32);

# define RTE_STOP_SEC_AP_SRLCOMINPUT_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_ComM_UserRequest_E_MODE_LIMITATION (2U)

#  define RTE_E_ComM_UserRequest_E_NOT_OK (1U)

#  define RTE_E_EpsEn_E_NOT_OK (1U)

#  define RTE_E_NxtrDiagMgr_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_SRLCOMINPUT_H */
