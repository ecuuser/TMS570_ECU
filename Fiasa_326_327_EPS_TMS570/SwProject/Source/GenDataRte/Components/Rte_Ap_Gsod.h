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
 *          File:  Components/Rte_Ap_Gsod.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_GSOD_H
# define _RTE_AP_GSOD_H

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
extern VAR(Float, RTE_VAR_INIT) Rte_DigHwTrqSENT_HwTorque_HwNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_CDDInterface_CorrMtrPosElec_Rev_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_DigMSB_CumMechMtrPosMRF_Deg_f32;
extern VAR(SInt8, RTE_VAR_INIT) Rte_Polarity_MtrElecMechPolarity_Cnt_s08;
extern VAR(Float, RTE_VAR_INIT) Rte_DigHwTrqSENT_SysCHwTorque_HwNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_CDDInterface_SysCCorrMtrPosElec_Rev_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_DigMSB_SysCCumMechMtrPosMRF_Deg_f32;
extern VAR(SInt32, RTE_VAR_INIT) Rte_Polarity_SysC_MtrElecMechPolarity_Cnt_s32;
extern VAR(Float, RTE_VAR_INIT) Rte_CtrldDisShtdn_SysC_CRFMtrTrqCmd_MtrNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_CtrldDisShtdn_SysC_MRFMtrTrqCmd_MtrNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_BatteryVoltage_SysC_Vecu_Volt_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_CtrldDisShtdn_CntDisMtrTrqCmdCRF_MtrNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_CtrldDisShtdn_CntDisMtrTrqCmdMRF_MtrNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_BatteryVoltage_Vecu_Volt_f32;

#  define RTE_STOP_SEC_VAR_Ap_10_INIT_UNSPECIFIED
#  include "MemMap.h"

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_Ana_Hw_Torque_HwNm_f32 (0.0F)
#  define Rte_InitValue_Corrected_MtrPos_Rev_f32 (0.0F)
#  define Rte_InitValue_Cum_Mtr_Pos_CRF_Deg_f32 (0.0F)
#  define Rte_InitValue_MtrElecMech_Polarity_Cnt_s08 (0)
#  define Rte_InitValue_SysC_Ana_Hw_Torque_HwNm_f32 (0.0F)
#  define Rte_InitValue_SysC_Corrected_MtrPos_Rev_f32 (0.0F)
#  define Rte_InitValue_SysC_Cum_Mtr_Pos_CRF_Deg_f32 (0.0F)
#  define Rte_InitValue_SysC_MtrElecMech_Polarity_Cnt_s32 (0)
#  define Rte_InitValue_SysC_Torque_Cmd_CRF_MtrNm_f32 (0.0F)
#  define Rte_InitValue_SysC_Torque_Cmd_MRF_MtrNm_f32 (0.0F)
#  define Rte_InitValue_SysC_Vecu_Volt_f32 (5.0F)
#  define Rte_InitValue_Torque_Cmd_CRF_MtrNm_f32 (0.0F)
#  define Rte_InitValue_Torque_Cmd_MRF_MtrNm_f32 (0.0F)
#  define Rte_InitValue_Vecu_Volt_f32 (5.0F)
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
#  define Rte_Read_Ana_Hw_Torque_HwNm_f32 Rte_Read_Ap_Gsod_Ana_Hw_Torque_HwNm_f32
#  define Rte_Read_Ap_Gsod_Ana_Hw_Torque_HwNm_f32(data) (*(data) = Rte_DigHwTrqSENT_HwTorque_HwNm_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_Corrected_MtrPos_Rev_f32 Rte_Read_Ap_Gsod_Corrected_MtrPos_Rev_f32
#  define Rte_Read_Ap_Gsod_Corrected_MtrPos_Rev_f32(data) (*(data) = Rte_CDDInterface_CorrMtrPosElec_Rev_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_Cum_Mtr_Pos_CRF_Deg_f32 Rte_Read_Ap_Gsod_Cum_Mtr_Pos_CRF_Deg_f32
#  define Rte_Read_Ap_Gsod_Cum_Mtr_Pos_CRF_Deg_f32(data) (*(data) = Rte_DigMSB_CumMechMtrPosMRF_Deg_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_MtrElecMech_Polarity_Cnt_s08 Rte_Read_Ap_Gsod_MtrElecMech_Polarity_Cnt_s08
#  define Rte_Read_Ap_Gsod_MtrElecMech_Polarity_Cnt_s08(data) (*(data) = Rte_Polarity_MtrElecMechPolarity_Cnt_s08, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_SysC_Ana_Hw_Torque_HwNm_f32 Rte_Read_Ap_Gsod_SysC_Ana_Hw_Torque_HwNm_f32
#  define Rte_Read_Ap_Gsod_SysC_Ana_Hw_Torque_HwNm_f32(data) (*(data) = Rte_DigHwTrqSENT_SysCHwTorque_HwNm_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_SysC_Corrected_MtrPos_Rev_f32 Rte_Read_Ap_Gsod_SysC_Corrected_MtrPos_Rev_f32
#  define Rte_Read_Ap_Gsod_SysC_Corrected_MtrPos_Rev_f32(data) (*(data) = Rte_CDDInterface_SysCCorrMtrPosElec_Rev_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_SysC_Cum_Mtr_Pos_CRF_Deg_f32 Rte_Read_Ap_Gsod_SysC_Cum_Mtr_Pos_CRF_Deg_f32
#  define Rte_Read_Ap_Gsod_SysC_Cum_Mtr_Pos_CRF_Deg_f32(data) (*(data) = Rte_DigMSB_SysCCumMechMtrPosMRF_Deg_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_SysC_MtrElecMech_Polarity_Cnt_s32 Rte_Read_Ap_Gsod_SysC_MtrElecMech_Polarity_Cnt_s32
#  define Rte_Read_Ap_Gsod_SysC_MtrElecMech_Polarity_Cnt_s32(data) (*(data) = Rte_Polarity_SysC_MtrElecMechPolarity_Cnt_s32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_SysC_Torque_Cmd_CRF_MtrNm_f32 Rte_Read_Ap_Gsod_SysC_Torque_Cmd_CRF_MtrNm_f32
#  define Rte_Read_Ap_Gsod_SysC_Torque_Cmd_CRF_MtrNm_f32(data) (*(data) = Rte_CtrldDisShtdn_SysC_CRFMtrTrqCmd_MtrNm_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_SysC_Torque_Cmd_MRF_MtrNm_f32 Rte_Read_Ap_Gsod_SysC_Torque_Cmd_MRF_MtrNm_f32
#  define Rte_Read_Ap_Gsod_SysC_Torque_Cmd_MRF_MtrNm_f32(data) (*(data) = Rte_CtrldDisShtdn_SysC_MRFMtrTrqCmd_MtrNm_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_SysC_Vecu_Volt_f32 Rte_Read_Ap_Gsod_SysC_Vecu_Volt_f32
#  define Rte_Read_Ap_Gsod_SysC_Vecu_Volt_f32(data) (*(data) = Rte_BatteryVoltage_SysC_Vecu_Volt_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_Torque_Cmd_CRF_MtrNm_f32 Rte_Read_Ap_Gsod_Torque_Cmd_CRF_MtrNm_f32
#  define Rte_Read_Ap_Gsod_Torque_Cmd_CRF_MtrNm_f32(data) (*(data) = Rte_CtrldDisShtdn_CntDisMtrTrqCmdCRF_MtrNm_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_Torque_Cmd_MRF_MtrNm_f32 Rte_Read_Ap_Gsod_Torque_Cmd_MRF_MtrNm_f32
#  define Rte_Read_Ap_Gsod_Torque_Cmd_MRF_MtrNm_f32(data) (*(data) = Rte_CtrldDisShtdn_CntDisMtrTrqCmdMRF_MtrNm_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_Vecu_Volt_f32 Rte_Read_Ap_Gsod_Vecu_Volt_f32
#  define Rte_Read_Ap_Gsod_Vecu_Volt_f32(data) (*(data) = Rte_BatteryVoltage_Vecu_Volt_f32, ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState_Mode() Rte_ModeMachine_StaMd_SystemState_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);
#  define RTE_STOP_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_SetNTCStatus NxtrDiagMgr10_SetNTCStatus


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_GSOD_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_GSOD_APPL_CODE) Gsod_Per1(void);

# define RTE_STOP_SEC_AP_GSOD_APPL_CODE
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


#endif /* _RTE_AP_GSOD_H */
