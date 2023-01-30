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
 *          File:  Components/Rte_Ap_DiagMgr10.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_DIAGMGR10_H
# define _RTE_AP_DIAGMGR10_H

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
extern VAR(Float, RTE_VAR_INIT) Rte_DiagMgr10_DiagRampRate_XpmS_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_DiagMgr10_DiagRampValue_Uls_f32;
extern VAR(Boolean, RTE_VAR_INIT) Rte_DiagMgr10_DiagRmpToZeroActive_Cnt_lgc;
extern VAR(Boolean, RTE_VAR_INIT) Rte_DiagMgr10_DiagStsCtrldDisRmpPres_Cnt_lgc;
extern VAR(Boolean, RTE_VAR_INIT) Rte_DiagMgr10_DiagStsDefTemp_Cnt_lgc;
extern VAR(Boolean, RTE_VAR_INIT) Rte_DiagMgr10_DiagStsDefVehSpd_Cnt_lgc;
extern VAR(Boolean, RTE_VAR_INIT) Rte_DiagMgr10_DiagStsHWASbSystmFltPres_Cnt_lgc;
extern VAR(Boolean, RTE_VAR_INIT) Rte_DiagMgr10_DiagStsNonRecRmpToZeroFltPres_Cnt_lgc;
extern VAR(Boolean, RTE_VAR_INIT) Rte_DiagMgr10_DiagStsRecRmpToZeroFltPres_Cnt_lgc;
extern VAR(Boolean, RTE_VAR_INIT) Rte_DiagMgr10_DiagStsScomHWANotValid_Cnt_lgc;
extern VAR(Boolean, RTE_VAR_INIT) Rte_DiagMgr10_DiagStsWIRDisable_Cnt_lgc;
extern VAR(Float, RTE_VAR_INIT) Rte_Sweep_OutputHwTrq_HwNm_f32;
extern VAR(UInt16, RTE_VAR_INIT) Rte_CDDInterface_IgnCnt_Cnt_u16;
extern VAR(ManufModeType, RTE_VAR_INIT) Rte_CDDInterface_MEC_Cnt_enum;
extern VAR(Boolean, RTE_VAR_INIT) Rte_CDDInterface_MfgDiagInhibit_Cnt_lgc;
extern VAR(Float, RTE_VAR_INIT) Rte_CtrldDisShtdn_CntDisMtrTrqCmdMRF_MtrNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_SignlCondn_VehicleSpeed_Kph_f32;

#  define RTE_STOP_SEC_VAR_Ap_10_INIT_UNSPECIFIED
#  include "MemMap.h"

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_DiagRampRate_XpmS_f32 (0.0F)
#  define Rte_InitValue_DiagRampValue_Uls_f32 (0.0F)
#  define Rte_InitValue_DiagRmpToZeroActive_Cnt_lgc (FALSE)
#  define Rte_InitValue_DiagStsCtrldDisRmpPres_Cnt_lgc (FALSE)
#  define Rte_InitValue_DiagStsDefTemp_Cnt_lgc (FALSE)
#  define Rte_InitValue_DiagStsDefVehSpd_Cnt_lgc (FALSE)
#  define Rte_InitValue_DiagStsHWASbSystmFltPres_Cnt_lgc (FALSE)
#  define Rte_InitValue_DiagStsNonRecRmpToZeroFltPres_Cnt_lgc (FALSE)
#  define Rte_InitValue_DiagStsRecRmpToZeroFltPres_Cnt_lgc (FALSE)
#  define Rte_InitValue_DiagStsScomHWANotValid_Cnt_lgc (FALSE)
#  define Rte_InitValue_DiagStsWIRDisable_Cnt_lgc (FALSE)
#  define Rte_InitValue_HwTrq_HwNm_f32 (0.0F)
#  define Rte_InitValue_IgnCnt_Cnt_u16 (0U)
#  define Rte_InitValue_MEC_Cnt_enum (0U)
#  define Rte_InitValue_MfgDiagInhibit_Cnt_lgc (FALSE)
#  define Rte_InitValue_MtrTrq_MtrNm_f32 (0.0F)
#  define Rte_InitValue_VehSpd_Kph_f32 (0.0F)
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



# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/

# define RTE_STOP_SEC_CODE
# include "MemMap.h"


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_HwTrq_HwNm_f32 Rte_Read_Ap_DiagMgr10_HwTrq_HwNm_f32
#  define Rte_Read_Ap_DiagMgr10_HwTrq_HwNm_f32(data) (*(data) = Rte_Sweep_OutputHwTrq_HwNm_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_IgnCnt_Cnt_u16 Rte_Read_Ap_DiagMgr10_IgnCnt_Cnt_u16
#  define Rte_Read_Ap_DiagMgr10_IgnCnt_Cnt_u16(data) (*(data) = Rte_CDDInterface_IgnCnt_Cnt_u16, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_MEC_Cnt_enum Rte_Read_Ap_DiagMgr10_MEC_Cnt_enum
#  define Rte_Read_Ap_DiagMgr10_MEC_Cnt_enum(data) (*(data) = Rte_CDDInterface_MEC_Cnt_enum, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_MfgDiagInhibit_Cnt_lgc Rte_Read_Ap_DiagMgr10_MfgDiagInhibit_Cnt_lgc
#  define Rte_Read_Ap_DiagMgr10_MfgDiagInhibit_Cnt_lgc(data) (*(data) = Rte_CDDInterface_MfgDiagInhibit_Cnt_lgc, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_MtrTrq_MtrNm_f32 Rte_Read_Ap_DiagMgr10_MtrTrq_MtrNm_f32
#  define Rte_Read_Ap_DiagMgr10_MtrTrq_MtrNm_f32(data) (*(data) = Rte_CtrldDisShtdn_CntDisMtrTrqCmdMRF_MtrNm_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_VehSpd_Kph_f32 Rte_Read_Ap_DiagMgr10_VehSpd_Kph_f32
#  define Rte_Read_Ap_DiagMgr10_VehSpd_Kph_f32(data) (*(data) = Rte_SignlCondn_VehicleSpeed_Kph_f32, ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Write_DiagRampRate_XpmS_f32 Rte_Write_Ap_DiagMgr10_DiagRampRate_XpmS_f32
#  define Rte_Write_Ap_DiagMgr10_DiagRampRate_XpmS_f32(data) (Rte_DiagMgr10_DiagRampRate_XpmS_f32 = (data), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Write_DiagRampValue_Uls_f32 Rte_Write_Ap_DiagMgr10_DiagRampValue_Uls_f32
#  define Rte_Write_Ap_DiagMgr10_DiagRampValue_Uls_f32(data) (Rte_DiagMgr10_DiagRampValue_Uls_f32 = (data), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Write_DiagRmpToZeroActive_Cnt_lgc Rte_Write_Ap_DiagMgr10_DiagRmpToZeroActive_Cnt_lgc
#  define Rte_Write_Ap_DiagMgr10_DiagRmpToZeroActive_Cnt_lgc(data) (Rte_DiagMgr10_DiagRmpToZeroActive_Cnt_lgc = (data), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Write_DiagStsCtrldDisRmpPres_Cnt_lgc Rte_Write_Ap_DiagMgr10_DiagStsCtrldDisRmpPres_Cnt_lgc
#  define Rte_Write_Ap_DiagMgr10_DiagStsCtrldDisRmpPres_Cnt_lgc(data) (Rte_DiagMgr10_DiagStsCtrldDisRmpPres_Cnt_lgc = (data), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Write_DiagStsDefTemp_Cnt_lgc Rte_Write_Ap_DiagMgr10_DiagStsDefTemp_Cnt_lgc
#  define Rte_Write_Ap_DiagMgr10_DiagStsDefTemp_Cnt_lgc(data) (Rte_DiagMgr10_DiagStsDefTemp_Cnt_lgc = (data), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Write_DiagStsDefVehSpd_Cnt_lgc Rte_Write_Ap_DiagMgr10_DiagStsDefVehSpd_Cnt_lgc
#  define Rte_Write_Ap_DiagMgr10_DiagStsDefVehSpd_Cnt_lgc(data) (Rte_DiagMgr10_DiagStsDefVehSpd_Cnt_lgc = (data), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Write_DiagStsHWASbSystmFltPres_Cnt_lgc Rte_Write_Ap_DiagMgr10_DiagStsHWASbSystmFltPres_Cnt_lgc
#  define Rte_Write_Ap_DiagMgr10_DiagStsHWASbSystmFltPres_Cnt_lgc(data) (Rte_DiagMgr10_DiagStsHWASbSystmFltPres_Cnt_lgc = (data), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Write_DiagStsNonRecRmpToZeroFltPres_Cnt_lgc Rte_Write_Ap_DiagMgr10_DiagStsNonRecRmpToZeroFltPres_Cnt_lgc
#  define Rte_Write_Ap_DiagMgr10_DiagStsNonRecRmpToZeroFltPres_Cnt_lgc(data) (Rte_DiagMgr10_DiagStsNonRecRmpToZeroFltPres_Cnt_lgc = (data), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Write_DiagStsRecRmpToZeroFltPres_Cnt_lgc Rte_Write_Ap_DiagMgr10_DiagStsRecRmpToZeroFltPres_Cnt_lgc
#  define Rte_Write_Ap_DiagMgr10_DiagStsRecRmpToZeroFltPres_Cnt_lgc(data) (Rte_DiagMgr10_DiagStsRecRmpToZeroFltPres_Cnt_lgc = (data), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Write_DiagStsScomHWANotValid_Cnt_lgc Rte_Write_Ap_DiagMgr10_DiagStsScomHWANotValid_Cnt_lgc
#  define Rte_Write_Ap_DiagMgr10_DiagStsScomHWANotValid_Cnt_lgc(data) (Rte_DiagMgr10_DiagStsScomHWANotValid_Cnt_lgc = (data), ((Std_ReturnType)RTE_E_OK))
#  define Rte_Write_DiagStsWIRDisable_Cnt_lgc Rte_Write_Ap_DiagMgr10_DiagStsWIRDisable_Cnt_lgc
#  define Rte_Write_Ap_DiagMgr10_DiagStsWIRDisable_Cnt_lgc(data) (Rte_DiagMgr10_DiagStsWIRDisable_Cnt_lgc = (data), ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState_Mode() Rte_ModeMachine_StaMd_SystemState_Mode


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_DIAGMGR10_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_DIAGMGR10_APPL_CODE) DiagMgr10_Init(void);

FUNC(void, RTE_AP_DIAGMGR10_APPL_CODE) DiagMgr10_Per(void);

FUNC(void, RTE_AP_DIAGMGR10_APPL_CODE) DiagMgr10_Trns(void);

FUNC(void, RTE_AP_DIAGMGR10_APPL_CODE) DiagMgr_Per1(void);

FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_GetNTCActive(NTCNumber NTC_Cnt_T_enum, P2VAR(Boolean, AUTOMATIC, RTE_AP_DIAGMGR10_APPL_VAR) NTCActive_Ptr_T_lgc);

FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_GetNTCFailed(NTCNumber NTC_Cnt_T_enum, P2VAR(Boolean, AUTOMATIC, RTE_AP_DIAGMGR10_APPL_VAR) NTCFailed_Ptr_T_lgc);

FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_GetNTCStatus(NTCNumber NTC_Cnt_T_enum, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGMGR10_APPL_VAR) Status_Ptr_T_u08);

FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);

# define RTE_STOP_SEC_AP_DIAGMGR10_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_NxtrDiagMgr_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_DIAGMGR10_H */
