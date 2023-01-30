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
 *          File:  Components/Rte_Ap_VehDyn.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_VEHDYN_H
# define _RTE_AP_VEHDYN_H

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
extern VAR(Float, RTE_VAR_INIT) Rte_AbsHwPos_RelHwPos_HwDeg_f32;

#  define RTE_STOP_SEC_VAR_Ap_10_INIT_UNSPECIFIED
#  include "MemMap.h"

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_CcwEOT_HwDeg_f32 (0.0F)
#  define Rte_InitValue_CwEOT_HwDeg_f32 (0.0F)
#  define Rte_InitValue_HandwheelPosition_HwDeg_f32 (0.0F)
#  define Rte_InitValue_HwAuth_Uls_f32 (0.0F)
#  define Rte_InitValue_HwTorque_HwNm_f32 (0.0F)
#  define Rte_InitValue_MechMtrPos_Rev_f32 (0.0F)
#  define Rte_InitValue_MotorVelCRF_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_RelHwPos_HwDeg_f32 (0.0F)
#  define Rte_InitValue_SensorlessAuthority_Uls_f32 (0.0F)
#  define Rte_InitValue_SensorlessHwPos_HwDeg_f32 (0.0F)
#  define Rte_InitValue_SrlHwAg_HwDeg_f32 (0.0F)
#  define Rte_InitValue_SrlHwAgVld_Cnt_lgc (FALSE)
#  define Rte_InitValue_TorqueCmdCRF_MtrNm_f32 (0.0F)
#  define Rte_InitValue_VehicleSpeed_Kph_f32 (0.0F)
#  define Rte_InitValue_VehicleSpeedValid_Cnt_lgc (FALSE)
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

extern VAR(Rte_tsTask_Init_10, RTE_VAR_NOINIT) Rte_Task_Init_10;

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

#  define Rte_IRead_VehDyn_Init1_RelHwPos_HwDeg_f32() \
  (Rte_Task_Init_10.Rte_RB.Rte_Ap_VehDyn_VehDyn_Init1.Rte_RelHwPos_HwDeg_f32.value)

#  define Rte_IRead_VehDyn_Per1_CcwEOT_HwDeg_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_VehDyn_VehDyn_Per1.Rte_CcwEOT_HwDeg_f32.value)

#  define Rte_IRead_VehDyn_Per1_CwEOT_HwDeg_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_VehDyn_VehDyn_Per1.Rte_CwEOT_HwDeg_f32.value)

#  define Rte_IRead_VehDyn_Per1_HwTorque_HwNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_Sweep_OutputHwTrq_HwNm_f32.value)

#  define Rte_IRead_VehDyn_Per1_MotorVelCRF_MtrRadpS_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_MtrVel_MotorVelCRF_MtrRadpS_f32.value)

#  define Rte_IRead_VehDyn_Per1_RelHwPos_HwDeg_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_AbsHwPos_RelHwPos_HwDeg_f32.value)

#  define Rte_IRead_VehDyn_Per1_SrlHwAgVld_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_VehDyn_VehDyn_Per1.Rte_SrlHwAgVld_Cnt_lgc.value)

#  define Rte_IRead_VehDyn_Per1_SrlHwAg_HwDeg_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_VehDyn_VehDyn_Per1.Rte_SrlHwAg_HwDeg_f32.value)

#  define Rte_IRead_VehDyn_Per1_TorqueCmdCRF_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CtrldDisShtdn_CntDisMtrTrqCmdCRF_MtrNm_f32.value)

#  define Rte_IRead_VehDyn_Per1_VehicleSpeedValid_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_SrlComInput_VehicleSpeedValid_Cnt_lgc.value)

#  define Rte_IRead_VehDyn_Per1_VehicleSpeed_Kph_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_SignlCondn_VehicleSpeed_Kph_f32.value)

#  define Rte_IWrite_VehDyn_Per1_SensorlessAuthority_Uls_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_VehDyn_SensorlessAuthority_Uls_f32.value = (data) \
  )

#  define Rte_IWriteRef_VehDyn_Per1_SensorlessAuthority_Uls_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_VehDyn_SensorlessAuthority_Uls_f32.value)

#  define Rte_IWrite_VehDyn_Per1_SensorlessHwPos_HwDeg_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_VehDyn_SensorlessHwPos_HwDeg_f32.value = (data) \
  )

#  define Rte_IWriteRef_VehDyn_Per1_SensorlessHwPos_HwDeg_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_VehDyn_SensorlessHwPos_HwDeg_f32.value)

#  define Rte_IRead_VehDyn_Trns1_HandwheelPosition_HwDeg_f32() \
  (Rte_Task_Trns_10.Rte_RB.Rte_Ap_VehDyn_VehDyn_Trns1.Rte_HandwheelPosition_HwDeg_f32.value)

#  define Rte_IRead_VehDyn_Trns1_HwAuth_Uls_f32() \
  (Rte_Task_Trns_10.Rte_RB.Rte_Ap_VehDyn_VehDyn_Trns1.Rte_HwAuth_Uls_f32.value)

#  define Rte_IRead_VehDyn_Trns1_MechMtrPos_Rev_f32() \
  (Rte_Task_Trns_10.Rte_RB.Rte_Ap_VehDyn_VehDyn_Trns1.Rte_MechMtrPos_Rev_f32.value)


/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_RelHwPos_HwDeg_f32 Rte_Read_Ap_VehDyn_RelHwPos_HwDeg_f32
#  define Rte_Read_Ap_VehDyn_RelHwPos_HwDeg_f32(data) (*(data) = Rte_AbsHwPos_RelHwPos_HwDeg_f32, ((Std_ReturnType)RTE_E_OK))


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

#  define Rte_Call_NVM_VehDynReset_Srv_WriteBlock(arg1) (NvMProxy_WriteBlock((UInt8)14, arg1))
#  define RTE_START_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_GetNTCActive(NTCNumber NTC_Cnt_T_enum, P2VAR(Boolean, AUTOMATIC, RTE_AP_DIAGMGR10_APPL_VAR) NTCActive_Ptr_T_lgc);
#  define RTE_STOP_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_GetNTCActive NxtrDiagMgr10_GetNTCActive
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


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT
#   define RTE_START_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

extern VAR(VehDyn_DataType, RTE_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP) Rte_VehDyn_MotPosReset;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  define Rte_Pim_MotPosReset() \
  (&Rte_VehDyn_MotPosReset)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_VEHDYN_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_Init1(void);

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_Per1(void);

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_SCom_ForceCenter(void);

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_SCom_ResetCenter(void);

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_Trns1(void);

# define RTE_STOP_SEC_AP_VEHDYN_APPL_CODE
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


#endif /* _RTE_AP_VEHDYN_H */
