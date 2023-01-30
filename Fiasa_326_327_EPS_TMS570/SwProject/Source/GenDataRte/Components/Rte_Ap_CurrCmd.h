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
 *          File:  Components/Rte_Ap_CurrCmd.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_CURRCMD_H
# define _RTE_AP_CURRCMD_H

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

#  define Rte_InitValue_CurrentGainSvc_Cnt_lgc (FALSE)
#  define Rte_InitValue_EstKe_VpRadpS_f32 (0.0F)
#  define Rte_InitValue_EstLd_Henry_f32 (0.0F)
#  define Rte_InitValue_EstLq_Henry_f32 (0.0F)
#  define Rte_InitValue_EstR_Ohm_f32 (0.0F)
#  define Rte_InitValue_IvtrLoaMtgtnEn_Cnt_lgc (FALSE)
#  define Rte_InitValue_MRFMtrVel_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_MRFTrqCmdScl_MtrNm_f32 (0.0F)
#  define Rte_InitValue_MotCurrLoaMtgtnEn_Cnt_lgc (FALSE)
#  define Rte_InitValue_MtrCurrAngle_Rev_f32 (0.0F)
#  define Rte_InitValue_MtrCurrDaxRef_Amp_f32 (0.0F)
#  define Rte_InitValue_MtrCurrQaxRef_Amp_f32 (0.0F)
#  define Rte_InitValue_MtrQuad_Cnt_u08 (1U)
#  define Rte_InitValue_Vecu_Volt_f32 (5.0F)
#  define Rte_InitValue_VehSpd_Kph_f32 (0.0F)
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


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_IRead_<r>_<p>_<d>
 * Rte_IStatus_<r>_<p>_<d>
 * Rte_IWrite_<r>_<p>_<d>
 * Rte_IWriteRef_<r>_<p>_<d>
 * Rte_IInvalidate_<r>_<p>_<d>
 *********************************************************************************************************************/

#  define Rte_IRead_CurrCmd_Per1_CurrentGainSvc_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrCmd_CurrCmd_Per1.Rte_CurrentGainSvc_Cnt_lgc.value)

#  define Rte_IRead_CurrCmd_Per1_EstKe_VpRadpS_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CurrParamComp_EstKe_VpRadpS_f32.value)

#  define Rte_IRead_CurrCmd_Per1_EstLd_Henry_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CurrParamComp_EstLd_Henry_f32.value)

#  define Rte_IRead_CurrCmd_Per1_EstLq_Henry_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CurrParamComp_EstLq_Henry_f32.value)

#  define Rte_IRead_CurrCmd_Per1_EstR_Ohm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CurrParamComp_EstR_Ohm_f32.value)

#  define Rte_IRead_CurrCmd_Per1_IvtrLoaMtgtnEn_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrCmd_CurrCmd_Per1.Rte_IvtrLoaMtgtnEn_Cnt_lgc.value)

#  define Rte_IRead_CurrCmd_Per1_MRFMtrVel_MtrRadpS_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_MtrVel_MotorVelMRF_MtrRadpS_f32.value)

#  define Rte_IRead_CurrCmd_Per1_MRFTrqCmdScl_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_TrqCmdScl_MRFMtrTrqCmdScl_MtrNm_f32.value)

#  define Rte_IRead_CurrCmd_Per1_MotCurrLoaMtgtnEn_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrCmd_CurrCmd_Per1.Rte_MotCurrLoaMtgtnEn_Cnt_lgc.value)

#  define Rte_IRead_CurrCmd_Per1_MtrQuad_Cnt_u08() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_QuadDet_MtrQuad_Cnt_u08.value)

#  define Rte_IRead_CurrCmd_Per1_Vecu_Volt_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_BatteryVoltage_Vecu_Volt_f32.value)

#  define Rte_IRead_CurrCmd_Per1_VehSpd_Kph_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrCmd_CurrCmd_Per1.Rte_VehSpd_Kph_f32.value)

#  define Rte_IWrite_CurrCmd_Per1_MtrCurrAngle_Rev_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrCmd_CurrCmd_Per1.Rte_MtrCurrAngle_Rev_f32.value = (data) \
  )

#  define Rte_IWriteRef_CurrCmd_Per1_MtrCurrAngle_Rev_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrCmd_CurrCmd_Per1.Rte_MtrCurrAngle_Rev_f32.value)

#  define Rte_IWrite_CurrCmd_Per1_MtrCurrDaxRef_Amp_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_CurrCmd_MtrCurrDaxRef_Amp_f32.value = (data) \
  )

#  define Rte_IWriteRef_CurrCmd_Per1_MtrCurrDaxRef_Amp_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_CurrCmd_MtrCurrDaxRef_Amp_f32.value)

#  define Rte_IWrite_CurrCmd_Per1_MtrCurrQaxRef_Amp_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_CurrCmd_MtrCurrQaxRef_Amp_f32.value = (data) \
  )

#  define Rte_IWriteRef_CurrCmd_Per1_MtrCurrQaxRef_Amp_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_CurrCmd_MtrCurrQaxRef_Amp_f32.value)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_CURRCMD_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_CURRCMD_APPL_CODE) CurrCmd_Init(void);

FUNC(void, RTE_AP_CURRCMD_APPL_CODE) CurrCmd_Per1(void);

# define RTE_STOP_SEC_AP_CURRCMD_APPL_CODE
# include "MemMap.h"

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_CURRCMD_H */
