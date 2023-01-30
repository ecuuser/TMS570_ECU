/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  Copyright (c) 2006-2010 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Rte_Ap_VehDyn.h
 *     Workspace:  C:/SynergyEA3/Working/VehDyn/autosar
 *     SW-C Type:  Ap_VehDyn
 *  Generated at:  Wed Dec 16 12:52:35 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  Application header file for SW-C <Ap_VehDyn> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_VEHDYN_H
# define _RTE_AP_VEHDYN_H

# ifdef RTE_APPLICATION_HEADER_FILE
#  error Multiple application header files included.
# endif
# define RTE_APPLICATION_HEADER_FILE

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_Type.h"

typedef P2CONST(struct Rte_CDS_Ap_VehDyn, TYPEDEF, RTE_CONST) Rte_Instance;


/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

# define Rte_InitValue_CcwEOT_HwDeg_f32 ((Float)-360)
# define Rte_InitValue_CwEOT_HwDeg_f32 ((Float)360)
# define Rte_InitValue_HandwheelPosition_HwDeg_f32 ((Float)0)
# define Rte_InitValue_HwAuth_Uls_f32 ((Float)0)
# define Rte_InitValue_HwTorque_HwNm_f32 ((Float)0)
# define Rte_InitValue_MechMtrPos_Rev_f32 ((Float)0)
# define Rte_InitValue_MotorVelCRF_MtrRadpS_f32 ((Float)0)
# define Rte_InitValue_RelHwPos_HwDeg_f32 ((Float)0)
# define Rte_InitValue_SensorlessAuthority_Uls_f32 ((Float)0)
# define Rte_InitValue_SensorlessHwPos_HwDeg_f32 ((Float)0)
# define Rte_InitValue_SrlHwAg_HwDeg_f32 ((Float)0)
# define Rte_InitValue_SrlHwAgVld_Cnt_lgc ((Boolean)FALSE)
# define Rte_InitValue_TorqueCmdCRF_MtrNm_f32 ((Float)0)
# define Rte_InitValue_VehicleSpeed_Kph_f32 ((Float)0)
# define Rte_InitValue_VehicleSpeedValid_Cnt_lgc ((Boolean)FALSE)


# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Ap_VehDyn_RelHwPos_HwDeg_f32(P2VAR(Float, AUTOMATIC, RTE_AP_VEHDYN_APPL_VAR) data);
FUNC(Rte_ModeType_StaMd_Mode, RTE_CODE) Rte_Mode_Ap_VehDyn_SystemState_Mode(void);
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Ap_VehDyn_NVM_VehDynReset_Srv_WriteBlock(P2CONST(UInt8, AUTOMATIC, RTE_AP_VEHDYN_APPL_DATA) DstPtr);
# else
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Ap_VehDyn_NVM_VehDynReset_Srv_WriteBlock(P2CONST(NvM_DestPtr, AUTOMATIC, RTE_AP_VEHDYN_APPL_DATA) DstPtr);
# endif
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Ap_VehDyn_NxtrDiagMgr_GetNTCActive(NTCNumber NTC_Cnt_T_enum, P2VAR(Boolean, AUTOMATIC, RTE_AP_VEHDYN_APPL_VAR) NTCActive_Ptr_T_lgc);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Ap_VehDyn_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, P2VAR(UInt16, AUTOMATIC, RTE_AP_VEHDYN_APPL_VAR) ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Ap_VehDyn_SystemTime_DtrmnElapsedTime_mS_u32(UInt32 InitialTime, P2VAR(UInt32, AUTOMATIC, RTE_AP_VEHDYN_APPL_VAR) ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Ap_VehDyn_SystemTime_GetSystemTime_mS_u32(P2VAR(UInt32, AUTOMATIC, RTE_AP_VEHDYN_APPL_VAR) CurrentTime);

# define RTE_STOP_SEC_CODE
# include "MemMap.h"



/**********************************************************************************************************************
 * Rte_IRead_<r>_<p>_<d>
 * Rte_IStatus_<r>_<p>_<d>
 * Rte_IWrite_<r>_<p>_<d>
 * Rte_IWriteRef_<r>_<p>_<d>
 * Rte_IInvalidate_<r>_<p>_<d>
 *********************************************************************************************************************/

# define Rte_IRead_VehDyn_Init1_RelHwPos_HwDeg_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Init1_RelHwPos_HwDeg_f32->value)

# define Rte_IRead_VehDyn_Per1_CcwEOT_HwDeg_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Per1_CcwEOT_HwDeg_f32->value)

# define Rte_IRead_VehDyn_Per1_CwEOT_HwDeg_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Per1_CwEOT_HwDeg_f32->value)

# define Rte_IRead_VehDyn_Per1_HwTorque_HwNm_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Per1_HwTorque_HwNm_f32->value)

# define Rte_IRead_VehDyn_Per1_MotorVelCRF_MtrRadpS_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Per1_MotorVelCRF_MtrRadpS_f32->value)

# define Rte_IRead_VehDyn_Per1_RelHwPos_HwDeg_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Per1_RelHwPos_HwDeg_f32->value)

# define Rte_IRead_VehDyn_Per1_SrlHwAgVld_Cnt_lgc() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Per1_SrlHwAgVld_Cnt_lgc->value)

# define Rte_IRead_VehDyn_Per1_SrlHwAg_HwDeg_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Per1_SrlHwAg_HwDeg_f32->value)

# define Rte_IRead_VehDyn_Per1_TorqueCmdCRF_MtrNm_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Per1_TorqueCmdCRF_MtrNm_f32->value)

# define Rte_IRead_VehDyn_Per1_VehicleSpeedValid_Cnt_lgc() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Per1_VehicleSpeedValid_Cnt_lgc->value)

# define Rte_IRead_VehDyn_Per1_VehicleSpeed_Kph_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Per1_VehicleSpeed_Kph_f32->value)

# define Rte_IWrite_VehDyn_Per1_SensorlessAuthority_Uls_f32(data) \
  ( \
  Rte_Inst_Ap_VehDyn->VehDyn_Per1_SensorlessAuthority_Uls_f32->value = (data) \
  )

# define Rte_IWriteRef_VehDyn_Per1_SensorlessAuthority_Uls_f32() \
  (&Rte_Inst_Ap_VehDyn->VehDyn_Per1_SensorlessAuthority_Uls_f32->value)

# define Rte_IWrite_VehDyn_Per1_SensorlessHwPos_HwDeg_f32(data) \
  ( \
  Rte_Inst_Ap_VehDyn->VehDyn_Per1_SensorlessHwPos_HwDeg_f32->value = (data) \
  )

# define Rte_IWriteRef_VehDyn_Per1_SensorlessHwPos_HwDeg_f32() \
  (&Rte_Inst_Ap_VehDyn->VehDyn_Per1_SensorlessHwPos_HwDeg_f32->value)

# define Rte_IRead_VehDyn_Trns1_HandwheelPosition_HwDeg_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Trns1_HandwheelPosition_HwDeg_f32->value)

# define Rte_IRead_VehDyn_Trns1_HwAuth_Uls_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Trns1_HwAuth_Uls_f32->value)

# define Rte_IRead_VehDyn_Trns1_MechMtrPos_Rev_f32() \
  (Rte_Inst_Ap_VehDyn->VehDyn_Trns1_MechMtrPos_Rev_f32->value)


/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
# define Rte_Read_RelHwPos_HwDeg_f32 Rte_Read_Ap_VehDyn_RelHwPos_HwDeg_f32


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
# define Rte_Mode_SystemState_Mode Rte_Mode_Ap_VehDyn_SystemState_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (C/S invocation)
 *********************************************************************************************************************/
# define Rte_Call_NVM_VehDynReset_Srv_WriteBlock Rte_Call_Ap_VehDyn_NVM_VehDynReset_Srv_WriteBlock
# define Rte_Call_NxtrDiagMgr_GetNTCActive Rte_Call_Ap_VehDyn_NxtrDiagMgr_GetNTCActive
# define Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16 Rte_Call_Ap_VehDyn_SystemTime_DtrmnElapsedTime_mS_u16
# define Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32 Rte_Call_Ap_VehDyn_SystemTime_DtrmnElapsedTime_mS_u32
# define Rte_Call_SystemTime_GetSystemTime_mS_u32 Rte_Call_Ap_VehDyn_SystemTime_GetSystemTime_mS_u32


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

# define Rte_Pim_MotPosReset() (Rte_Inst_Ap_VehDyn->Pim_MotPosReset)




/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   VehDyn_DataType *Rte_Pim_MotPosReset(void)
 *
 *********************************************************************************************************************/


# define RTE_START_SEC_AP_VEHDYN_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehDyn_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_VehDyn_Init1_RelHwPos_HwDeg_f32(void)
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_GetNTCActive(NTCNumber NTC_Cnt_T_enum, Boolean *NTCActive_Ptr_T_lgc)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_Init1(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehDyn_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_VehDyn_Per1_CcwEOT_HwDeg_f32(void)
 *   Float Rte_IRead_VehDyn_Per1_CwEOT_HwDeg_f32(void)
 *   Float Rte_IRead_VehDyn_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_VehDyn_Per1_MotorVelCRF_MtrRadpS_f32(void)
 *   Float Rte_IRead_VehDyn_Per1_RelHwPos_HwDeg_f32(void)
 *   Boolean Rte_IRead_VehDyn_Per1_SrlHwAgVld_Cnt_lgc(void)
 *   Float Rte_IRead_VehDyn_Per1_SrlHwAg_HwDeg_f32(void)
 *   Float Rte_IRead_VehDyn_Per1_TorqueCmdCRF_MtrNm_f32(void)
 *   Boolean Rte_IRead_VehDyn_Per1_VehicleSpeedValid_Cnt_lgc(void)
 *   Float Rte_IRead_VehDyn_Per1_VehicleSpeed_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_VehDyn_Per1_SensorlessAuthority_Uls_f32(Float data)
 *   Float *Rte_IWriteRef_VehDyn_Per1_SensorlessAuthority_Uls_f32(void)
 *   void Rte_IWrite_VehDyn_Per1_SensorlessHwPos_HwDeg_f32(Float data)
 *   Float *Rte_IWriteRef_VehDyn_Per1_SensorlessHwPos_HwDeg_f32(void)
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(UInt32 InitialTime, UInt32 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_Per1(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehDyn_SCom_ForceCenter
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ForceCenter> of PortPrototype <VehDyn_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_RelHwPos_HwDeg_f32(Float *data)
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void VehDyn_SCom_ForceCenter(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_SCom_ForceCenter(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehDyn_SCom_ResetCenter
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ResetCenter> of PortPrototype <VehDyn_SCom>
 *
 **********************************************************************************************************************
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_NVM_VehDynReset_Srv_WriteBlock(const UInt8 *DstPtr)
# else
 *   Std_ReturnType Rte_Call_NVM_VehDynReset_Srv_WriteBlock(const NvM_DestPtr *DstPtr)
# endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void VehDyn_SCom_ResetCenter(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_SCom_ResetCenter(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehDyn_Trns1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on entering of Mode <OFF> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_VehDyn_Trns1_HandwheelPosition_HwDeg_f32(void)
 *   Float Rte_IRead_VehDyn_Trns1_HwAuth_Uls_f32(void)
 *   Float Rte_IRead_VehDyn_Trns1_MechMtrPos_Rev_f32(void)
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_NVM_VehDynReset_Srv_WriteBlock(const UInt8 *DstPtr)
# else
 *   Std_ReturnType Rte_Call_NVM_VehDynReset_Srv_WriteBlock(const NvM_DestPtr *DstPtr)
# endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_Trns1(void);

# define RTE_STOP_SEC_AP_VEHDYN_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

# define RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK (1u)

# define RTE_E_NxtrDiagMgr_E_NOT_OK (1u)

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1450282354
#    error "The magic number of the generated file <C:/SynergyEA3/Working/VehDyn/tools/contract/Ap_VehDyn/Rte_Ap_VehDyn.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1450282354
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_AP_VEHDYN_H */
