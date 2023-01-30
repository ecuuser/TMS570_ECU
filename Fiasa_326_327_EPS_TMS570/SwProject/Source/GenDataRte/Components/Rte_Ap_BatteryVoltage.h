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
 *          File:  Components/Rte_Ap_BatteryVoltage.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_BATTERYVOLTAGE_H
# define _RTE_AP_BATTERYVOLTAGE_H

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
#  define Rte_InitValue_BattSwitched_Volt_f32 (0.0F)
#  define Rte_InitValue_SysCVSwitch_Volt_f32 (0.0F)
#  define Rte_InitValue_SysC_Vecu_Volt_f32 (5.0F)
#  define Rte_InitValue_Vecu_Volt_f32 (5.0F)
#  define Rte_InitValue_VswitchClosed_Cnt_lgc (FALSE)
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

#  define Rte_IRead_BatteryVoltage_Per1_BattSwitched_Volt_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_IoHwAbstractionUsr_BattSwitched_Volt_f32.value)

#  define Rte_IRead_BatteryVoltage_Per1_Batt_Volt_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_IoHwAbstractionUsr_Batt_Volt_f32.value)

#  define Rte_IWrite_BatteryVoltage_Per1_SysC_Vecu_Volt_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_BatteryVoltage_BatteryVoltage_Per1.Rte_SysC_Vecu_Volt_f32.value = (data) \
  )

#  define Rte_IWriteRef_BatteryVoltage_Per1_SysC_Vecu_Volt_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_BatteryVoltage_BatteryVoltage_Per1.Rte_SysC_Vecu_Volt_f32.value)

#  define Rte_IWrite_BatteryVoltage_Per1_Vecu_Volt_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_BatteryVoltage_BatteryVoltage_Per1.Rte_Vecu_Volt_f32.value = (data) \
  )

#  define Rte_IWriteRef_BatteryVoltage_Per1_Vecu_Volt_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_BatteryVoltage_BatteryVoltage_Per1.Rte_Vecu_Volt_f32.value)

#  define Rte_IWrite_BatteryVoltage_Per1_VswitchClosed_Cnt_lgc(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_BatteryVoltage_BatteryVoltage_Per1.Rte_VswitchClosed_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_BatteryVoltage_Per1_VswitchClosed_Cnt_lgc() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_BatteryVoltage_BatteryVoltage_Per1.Rte_VswitchClosed_Cnt_lgc.value)

#  define Rte_IRead_BatteryVoltage_Per2_BattSwitched_Volt_f32() \
  (Rte_Task_4ms_10.Rte_RB.Rte_Ap_BatteryVoltage_BatteryVoltage_Per2.Rte_BattSwitched_Volt_f32.value)

#  define Rte_IRead_BatteryVoltage_Per2_SysCVSwitch_Volt_f32() \
  (Rte_Task_4ms_10.Rte_RB.Rte_Ap_BatteryVoltage_BatteryVoltage_Per2.Rte_SysCVSwitch_Volt_f32.value)


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState_Mode() Rte_ModeMachine_StaMd_SystemState_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_AP_FLTINJECTION_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_AP_FLTINJECTION_APPL_CODE) FltInjection_SCom_FltInjection(P2VAR(Float, AUTOMATIC, RTE_AP_FLTINJECTION_APPL_VAR) SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum);
#  define RTE_STOP_SEC_AP_FLTINJECTION_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_FltInjection_SCom_FltInjection(arg1, arg2) (FltInjection_SCom_FltInjection(arg1, arg2), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);
#  define RTE_STOP_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_SetNTCStatus NxtrDiagMgr10_SetNTCStatus
#  define RTE_START_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NVMPROXY_APPL_CODE) NvMProxy_SetRamBlockStatus(UInt8 parg0, Boolean RamBlockStatus);
#  define RTE_STOP_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_OvervoltageData_SetRamBlockStatus(arg1) (NvMProxy_SetRamBlockStatus((UInt8)16, arg1), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVMPROXY_APPL_CODE) NvMProxy_WriteBlock(UInt8 parg0, P2CONST(UInt8, AUTOMATIC, RTE_NVMPROXY_APPL_DATA) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVMPROXY_APPL_CODE) NvMProxy_WriteBlock(UInt8 parg0, P2CONST(NvM_DestPtr, AUTOMATIC, RTE_NVMPROXY_APPL_DATA) DstPtr);
# endif
#  define RTE_STOP_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_OvervoltageData_WriteBlock(arg1) (NvMProxy_WriteBlock((UInt8)16, arg1))


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT
#   define RTE_START_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

extern VAR(OvervoltageDataType, RTE_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP) Rte_BatteryVoltage_OvervoltageData;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  define Rte_Pim_OvervoltageData() \
  (&Rte_BatteryVoltage_OvervoltageData)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_BATTERYVOLTAGE_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_Init1(void);

FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_Per1(void);

FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_Per2(void);

FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_SCom_ClearTransOvData(void);

FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_SCom_ReadTransOvData(P2VAR(UInt16, AUTOMATIC, RTE_AP_BATTERYVOLTAGE_APPL_VAR) OvervoltageCounter_Cnt_u16, P2VAR(Float, AUTOMATIC, RTE_AP_BATTERYVOLTAGE_APPL_VAR) MaxBattVoltage_Volts_f32);

# define RTE_STOP_SEC_AP_BATTERYVOLTAGE_APPL_CODE
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


#endif /* _RTE_AP_BATTERYVOLTAGE_H */
