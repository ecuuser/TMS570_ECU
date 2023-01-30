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
 *          File:  Components/Rte_Ap_AbsHwPos.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_ABSHWPOS_H
# define _RTE_AP_ABSHWPOS_H

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
extern VAR(UInt8, RTE_VAR_INIT) Rte_DigMSB_AlignedCumMechMtrPosStatus_Cnt_u08;

#  define RTE_STOP_SEC_VAR_Ap_10_INIT_UNSPECIFIED
#  include "MemMap.h"

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_AlignedCumMechMtrPosCRF_Deg_f32 (0.0F)
#  define Rte_InitValue_ComplError_HwDeg_f32 (0.0F)
#  define Rte_InitValue_CumMechMtrPosCRF_Deg_f32 (0.0F)
#  define Rte_InitValue_DiagStatusHwPosReducedPerf_Cnt_lgc (FALSE)
#  define Rte_InitValue_HandwheelAuthority_Uls_f32 (0.0F)
#  define Rte_InitValue_HandwheelPosition_HwDeg_f32 (0.0F)
#  define Rte_InitValue_HwPosSource_Cnt_u16 (0U)
#  define Rte_InitValue_I2CHwAbsPos_HwDeg_f32 (0.0F)
#  define Rte_InitValue_I2CHwAbsPosValid_Cnt_lgc (FALSE)
#  define Rte_InitValue_ManufMode_Cnt_enum (0U)
#  define Rte_InitValue_RelHwPos_HwDeg_f32 (0.0F)
#  define Rte_InitValue_SensorlessAuthority_Uls_f32 (0.0F)
#  define Rte_InitValue_SensorlessHwPos_HwDeg_f32 (0.0F)
#  define Rte_InitValue_SrlComHwPos_HwDeg_f32 (0.0F)
#  define Rte_InitValue_SrlComHwPosStatus_Cnt_u16 (0U)
#  define Rte_InitValue_TurnsCntrValidity_Cnt_u08 (0U)
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

#  define Rte_IRead_AbsHwPos_Init1_ManufMode_Cnt_enum() \
  (Rte_Task_Init_10.Rte_TB.Rte_I_CDDInterface_MEC_Cnt_enum.value)

#  define Rte_IWrite_AbsHwPos_Init1_HwPosSource_Cnt_u16(data) \
  ( \
    Rte_Task_Init_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Init1.Rte_HwPosSource_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_AbsHwPos_Init1_HwPosSource_Cnt_u16() \
  (&Rte_Task_Init_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Init1.Rte_HwPosSource_Cnt_u16.value)

#  define Rte_IWrite_AbsHwPos_Init1_SrlComHwPosStatus_Cnt_u16(data) \
  ( \
    Rte_Task_Init_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Init1.Rte_SrlComHwPosStatus_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_AbsHwPos_Init1_SrlComHwPosStatus_Cnt_u16() \
  (&Rte_Task_Init_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Init1.Rte_SrlComHwPosStatus_Cnt_u16.value)

#  define Rte_IRead_AbsHwPos_Per1_AlignedCumMechMtrPosCRF_Deg_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_AlignedCumMechMtrPosCRF_Deg_f32.value)

#  define Rte_IRead_AbsHwPos_Per1_ComplError_HwDeg_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_ComplErr_ComplErr_HwDeg_f32.value)

#  define Rte_IRead_AbsHwPos_Per1_CumMechMtrPosCRF_Deg_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_CumMechMtrPosCRF_Deg_f32.value)

#  define Rte_IWrite_AbsHwPos_Per1_RelHwPos_HwDeg_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_AbsHwPos_RelHwPos_HwDeg_f32.value = (data) \
  )

#  define Rte_IWriteRef_AbsHwPos_Per1_RelHwPos_HwDeg_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_AbsHwPos_RelHwPos_HwDeg_f32.value)

#  define Rte_IRead_AbsHwPos_Per2_DiagStatusHwPosReducedPerf_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_DiagMgr10_DiagStsHWASbSystmFltPres_Cnt_lgc.value)

#  define Rte_IRead_AbsHwPos_Per2_I2CHwAbsPosValid_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Per2.Rte_I2CHwAbsPosValid_Cnt_lgc.value)

#  define Rte_IRead_AbsHwPos_Per2_I2CHwAbsPos_HwDeg_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Per2.Rte_I2CHwAbsPos_HwDeg_f32.value)

#  define Rte_IRead_AbsHwPos_Per2_ManufMode_Cnt_enum() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Per2.Rte_ManufMode_Cnt_enum.value)

#  define Rte_IRead_AbsHwPos_Per2_SensorlessAuthority_Uls_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_VehDyn_SensorlessAuthority_Uls_f32.value)

#  define Rte_IRead_AbsHwPos_Per2_SensorlessHwPos_HwDeg_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_VehDyn_SensorlessHwPos_HwDeg_f32.value)

#  define Rte_IRead_AbsHwPos_Per2_TurnsCntrValidity_Cnt_u08() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_AlignedCumMechMtrPosStatus_Cnt_u08.value)

#  define Rte_IWrite_AbsHwPos_Per2_HandwheelAuthority_Uls_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_AbsHwPos_HandwheelAuthority_Uls_f32.value = (data) \
  )

#  define Rte_IWriteRef_AbsHwPos_Per2_HandwheelAuthority_Uls_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_AbsHwPos_HandwheelAuthority_Uls_f32.value)

#  define Rte_IWrite_AbsHwPos_Per2_HandwheelPosition_HwDeg_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_AbsHwPos_HandwheelPosition_HwDeg_f32.value = (data) \
  )

#  define Rte_IWriteRef_AbsHwPos_Per2_HandwheelPosition_HwDeg_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_AbsHwPos_HandwheelPosition_HwDeg_f32.value)

#  define Rte_IWrite_AbsHwPos_Per2_HwPosSource_Cnt_u16(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Per2.Rte_HwPosSource_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_AbsHwPos_Per2_HwPosSource_Cnt_u16() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Per2.Rte_HwPosSource_Cnt_u16.value)

#  define Rte_IWrite_AbsHwPos_Per2_SrlComHwPosStatus_Cnt_u16(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Per2.Rte_SrlComHwPosStatus_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_AbsHwPos_Per2_SrlComHwPosStatus_Cnt_u16() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Per2.Rte_SrlComHwPosStatus_Cnt_u16.value)

#  define Rte_IWrite_AbsHwPos_Per2_SrlComHwPos_HwDeg_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Per2.Rte_SrlComHwPos_HwDeg_f32.value = (data) \
  )

#  define Rte_IWriteRef_AbsHwPos_Per2_SrlComHwPos_HwDeg_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Per2.Rte_SrlComHwPos_HwDeg_f32.value)

#  define Rte_IRead_AbsHwPos_Per3_I2CHwAbsPosValid_Cnt_lgc() \
  (Rte_Task_4ms_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Per3.Rte_I2CHwAbsPosValid_Cnt_lgc.value)

#  define Rte_IRead_AbsHwPos_Per3_I2CHwAbsPos_HwDeg_f32() \
  (Rte_Task_4ms_10.Rte_RB.Rte_Ap_AbsHwPos_AbsHwPos_Per3.Rte_I2CHwAbsPos_HwDeg_f32.value)


/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_ManufMode_Cnt_enum Rte_Read_Ap_AbsHwPos_ManufMode_Cnt_enum
#  define Rte_Read_Ap_AbsHwPos_ManufMode_Cnt_enum(data) (*(data) = Rte_CDDInterface_MEC_Cnt_enum, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_TurnsCntrValidity_Cnt_u08 Rte_Read_Ap_AbsHwPos_TurnsCntrValidity_Cnt_u08
#  define Rte_Read_Ap_AbsHwPos_TurnsCntrValidity_Cnt_u08(data) (*(data) = Rte_DigMSB_AlignedCumMechMtrPosStatus_Cnt_u08, ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NVMPROXY_APPL_CODE) NvMProxy_GetErrorStatus(UInt8 parg0, P2VAR(NvM_RequestResultType, AUTOMATIC, RTE_NVMPROXY_APPL_VAR) ErrorStatus);
#  define RTE_STOP_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_EOLVehCntrOffset_GetErrorStatus(arg1) (NvMProxy_GetErrorStatus((UInt8)10, arg1), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVMPROXY_APPL_CODE) NvMProxy_WriteBlock(UInt8 parg0, P2CONST(UInt8, AUTOMATIC, RTE_NVMPROXY_APPL_DATA) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVMPROXY_APPL_CODE) NvMProxy_WriteBlock(UInt8 parg0, P2CONST(NvM_DestPtr, AUTOMATIC, RTE_NVMPROXY_APPL_DATA) DstPtr);
# endif
#  define RTE_STOP_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_EOLVehCntrOffset_WriteBlock(arg1) (NvMProxy_WriteBlock((UInt8)10, arg1))
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

extern VAR(EOLHwPosTrimType, RTE_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP) Rte_AbsHwPos_EOLVehCntrOffset;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  define Rte_Pim_EOLVehCntrOffset() \
  (&Rte_AbsHwPos_EOLVehCntrOffset)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_ABSHWPOS_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_Init1(void);

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_Per1(void);

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_Per2(void);

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_Per3(void);

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_Per4(void);

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_SCom_CustClrTrim(void);

FUNC(Std_ReturnType, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_SCom_CustSetTrim(void);

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_SCom_NxtClearTrim(void);

FUNC(Std_ReturnType, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_SCom_NxtSetTrim(Float Offset_HwDeg_T_f32);

# define RTE_STOP_SEC_AP_ABSHWPOS_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_AbsHwPos_SCom_TrimNotPerformed (34U)

#  define RTE_E_AbsHwPos_SCom_ValueNotAccepted (49U)

#  define RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK (1U)

#  define RTE_E_NxtrDiagMgr_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_ABSHWPOS_H */
