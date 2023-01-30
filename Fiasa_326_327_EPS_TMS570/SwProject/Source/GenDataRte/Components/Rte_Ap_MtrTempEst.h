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
 *          File:  Components/Rte_Ap_MtrTempEst.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_MTRTEMPEST_H
# define _RTE_AP_MTRTEMPEST_H

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

#  define Rte_InitValue_AmbTemp_DegC_f32 (0.0F)
#  define Rte_InitValue_AssistMechTempEst_DegC_f32 (0.0F)
#  define Rte_InitValue_CtrlTempFinal_DegC_f32 (0.0F)
#  define Rte_InitValue_CuTempEst_DegC_f32 (0.0F)
#  define Rte_InitValue_EngTemp_DegC_f32 (0.0F)
#  define Rte_InitValue_EstPkCurr_AmpSq_f32 (0.0F)
#  define Rte_InitValue_HwVel_HwRadpS_f32 (0.0F)
#  define Rte_InitValue_MagTempEst_DegC_f32 (0.0F)
#  define Rte_InitValue_ScomAMDefeat_Cnt_lgc (FALSE)
#  define Rte_InitValue_ScomTempDataRcvd_Cnt_lgc (FALSE)
#  define Rte_InitValue_SiTempEst_DegC_f32 (0.0F)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

extern VAR(Rte_tsTask_Init_9, RTE_VAR_NOINIT) Rte_Task_Init_9;

extern VAR(Rte_tsTask_100ms_9, RTE_VAR_NOINIT) Rte_Task_100ms_9;

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
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

#  define Rte_IRead_MtrTempEst_Init1_AmbTemp_DegC_f32() \
  (Rte_Task_Init_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Init1.Rte_AmbTemp_DegC_f32.value)

#  define Rte_IRead_MtrTempEst_Init1_CtrlTempFinal_DegC_f32() \
  (Rte_Task_Init_9.Rte_TB.Rte_I_CtrlTemp_FiltMeasTemp_DegC_f32.value)

#  define Rte_IRead_MtrTempEst_Init1_EngTemp_DegC_f32() \
  (Rte_Task_Init_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Init1.Rte_EngTemp_DegC_f32.value)

#  define Rte_IRead_MtrTempEst_Init1_ScomTempDataRcvd_Cnt_lgc() \
  (Rte_Task_Init_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Init1.Rte_ScomTempDataRcvd_Cnt_lgc.value)

#  define Rte_IWrite_MtrTempEst_Init1_AssistMechTempEst_DegC_f32(data) \
  ( \
    Rte_Task_Init_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Init1.Rte_AssistMechTempEst_DegC_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrTempEst_Init1_AssistMechTempEst_DegC_f32() \
  (&Rte_Task_Init_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Init1.Rte_AssistMechTempEst_DegC_f32.value)

#  define Rte_IWrite_MtrTempEst_Init1_CuTempEst_DegC_f32(data) \
  ( \
    Rte_Task_Init_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Init1.Rte_CuTempEst_DegC_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrTempEst_Init1_CuTempEst_DegC_f32() \
  (&Rte_Task_Init_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Init1.Rte_CuTempEst_DegC_f32.value)

#  define Rte_IWrite_MtrTempEst_Init1_MagTempEst_DegC_f32(data) \
  ( \
    Rte_Task_Init_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Init1.Rte_MagTempEst_DegC_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrTempEst_Init1_MagTempEst_DegC_f32() \
  (&Rte_Task_Init_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Init1.Rte_MagTempEst_DegC_f32.value)

#  define Rte_IWrite_MtrTempEst_Init1_SiTempEst_DegC_f32(data) \
  ( \
    Rte_Task_Init_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Init1.Rte_SiTempEst_DegC_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrTempEst_Init1_SiTempEst_DegC_f32() \
  (&Rte_Task_Init_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Init1.Rte_SiTempEst_DegC_f32.value)

#  define Rte_IRead_MtrTempEst_Per1_AmbTemp_DegC_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_AmbTemp_DegC_f32.value)

#  define Rte_IRead_MtrTempEst_Per1_CtrlTempFinal_DegC_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_CtrlTempFinal_DegC_f32.value)

#  define Rte_IRead_MtrTempEst_Per1_EngTemp_DegC_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_EngTemp_DegC_f32.value)

#  define Rte_IRead_MtrTempEst_Per1_EstPkCurr_AmpSq_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_EstPkCurr_AmpSq_f32.value)

#  define Rte_IRead_MtrTempEst_Per1_HwVel_HwRadpS_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_HwVel_HwRadpS_f32.value)

#  define Rte_IRead_MtrTempEst_Per1_ScomAMDefeat_Cnt_lgc() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_ScomAMDefeat_Cnt_lgc.value)

#  define Rte_IRead_MtrTempEst_Per1_ScomTempDataRcvd_Cnt_lgc() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_ScomTempDataRcvd_Cnt_lgc.value)

#  define Rte_IWrite_MtrTempEst_Per1_AssistMechTempEst_DegC_f32(data) \
  ( \
    Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_AssistMechTempEst_DegC_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrTempEst_Per1_AssistMechTempEst_DegC_f32() \
  (&Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_AssistMechTempEst_DegC_f32.value)

#  define Rte_IWrite_MtrTempEst_Per1_CuTempEst_DegC_f32(data) \
  ( \
    Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_CuTempEst_DegC_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrTempEst_Per1_CuTempEst_DegC_f32() \
  (&Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_CuTempEst_DegC_f32.value)

#  define Rte_IWrite_MtrTempEst_Per1_MagTempEst_DegC_f32(data) \
  ( \
    Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_MagTempEst_DegC_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrTempEst_Per1_MagTempEst_DegC_f32() \
  (&Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_MagTempEst_DegC_f32.value)

#  define Rte_IWrite_MtrTempEst_Per1_SiTempEst_DegC_f32(data) \
  ( \
    Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_SiTempEst_DegC_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrTempEst_Per1_SiTempEst_DegC_f32() \
  (&Rte_Task_100ms_9.Rte_RB.Rte_Ap_MtrTempEst_MtrTempEst_Per1.Rte_SiTempEst_DegC_f32.value)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_MTRTEMPEST_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_MTRTEMPEST_APPL_CODE) MtrTempEst_Init1(void);

FUNC(void, RTE_AP_MTRTEMPEST_APPL_CODE) MtrTempEst_Per1(void);

# define RTE_STOP_SEC_AP_MTRTEMPEST_APPL_CODE
# include "MemMap.h"

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_MTRTEMPEST_H */
