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
 *          File:  Components/Rte_Ap_EOTActuatorMng.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_EOTACTUATORMNG_H
# define _RTE_AP_EOTACTUATORMNG_H

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

#  define Rte_InitValue_AssistEOTDamping_MtrNm_f32 (0.0F)
#  define Rte_InitValue_AssistEOTGain_Uls_f32 (1.0F)
#  define Rte_InitValue_AssistEOTLimit_MtrNm_f32 (8.8F)
#  define Rte_InitValue_CcwEOT_HwDeg_f32 (0.0F)
#  define Rte_InitValue_CcwFound_Cnt_lgc (FALSE)
#  define Rte_InitValue_CwEOT_HwDeg_f32 (0.0F)
#  define Rte_InitValue_CwFound_Cnt_lgc (FALSE)
#  define Rte_InitValue_EOTDisable_Cnt_lgc (FALSE)
#  define Rte_InitValue_HandWheelAuth_Uls_f32 (0.0F)
#  define Rte_InitValue_HandWheelPos_HwDeg_f32 (0.0F)
#  define Rte_InitValue_HwTorque_HwNm_f32 (0.0F)
#  define Rte_InitValue_MotorVel_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_OutputRampMultLtd_Uls_f32 (0.0F)
#  define Rte_InitValue_PreLimitTorque_MtrNm_f32 (0.0F)
#  define Rte_InitValue_VehicleSpeed_Kph_f32 (0.0F)
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

#  define Rte_IRead_EOTActuatorMng_Per1_CcwEOT_HwDeg_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_CcwEOT_HwDeg_f32.value)

#  define Rte_IRead_EOTActuatorMng_Per1_CcwFound_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_CcwFound_Cnt_lgc.value)

#  define Rte_IRead_EOTActuatorMng_Per1_CwEOT_HwDeg_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_CwEOT_HwDeg_f32.value)

#  define Rte_IRead_EOTActuatorMng_Per1_CwFound_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_CwFound_Cnt_lgc.value)

#  define Rte_IRead_EOTActuatorMng_Per1_EOTDisable_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_EOTDisable_Cnt_lgc.value)

#  define Rte_IRead_EOTActuatorMng_Per1_HandWheelAuth_Uls_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_HandWheelAuth_Uls_f32.value)

#  define Rte_IRead_EOTActuatorMng_Per1_HandWheelPos_HwDeg_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_HandWheelPos_HwDeg_f32.value)

#  define Rte_IRead_EOTActuatorMng_Per1_HwTorque_HwNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_Sweep_OutputHwTrq_HwNm_f32.value)

#  define Rte_IRead_EOTActuatorMng_Per1_MotorVel_MtrRadpS_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_MtrVel_MotorVelCRF_MtrRadpS_f32.value)

#  define Rte_IRead_EOTActuatorMng_Per1_OutputRampMultLtd_Uls_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_OutputRampMultLtd_Uls_f32.value)

#  define Rte_IRead_EOTActuatorMng_Per1_PreLimitTorque_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_PreLimitTorque_MtrNm_f32.value)

#  define Rte_IRead_EOTActuatorMng_Per1_VehicleSpeed_Kph_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_SignlCondn_VehicleSpeed_Kph_f32.value)

#  define Rte_IWrite_EOTActuatorMng_Per1_AssistEOTDamping_MtrNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_AssistEOTDamping_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_EOTActuatorMng_Per1_AssistEOTDamping_MtrNm_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_AssistEOTDamping_MtrNm_f32.value)

#  define Rte_IWrite_EOTActuatorMng_Per1_AssistEOTGain_Uls_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_AssistEOTGain_Uls_f32.value = (data) \
  )

#  define Rte_IWriteRef_EOTActuatorMng_Per1_AssistEOTGain_Uls_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_AssistEOTGain_Uls_f32.value)

#  define Rte_IWrite_EOTActuatorMng_Per1_AssistEOTLimit_MtrNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_AssistEOTLimit_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_EOTActuatorMng_Per1_AssistEOTLimit_MtrNm_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_EOTActuatorMng_EOTActuatorMng_Per1.Rte_AssistEOTLimit_MtrNm_f32.value)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_EOTACTUATORMNG_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_EOTACTUATORMNG_APPL_CODE) EOTActuatorMng_Per1(void);

# define RTE_STOP_SEC_AP_EOTACTUATORMNG_APPL_CODE
# include "MemMap.h"

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_EOTACTUATORMNG_H */
