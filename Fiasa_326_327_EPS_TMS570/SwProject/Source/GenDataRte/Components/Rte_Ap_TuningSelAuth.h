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
 *          File:  Components/Rte_Ap_TuningSelAuth.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_TUNINGSELAUTH_H
# define _RTE_AP_TUNINGSELAUTH_H

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

#  define Rte_InitValue_ActiveTunOvrPtrAddr_Cnt_u32 (0U)
#  define Rte_InitValue_ActiveTunPers_Cnt_u16 (0U)
#  define Rte_InitValue_ActiveTunSet_Cnt_u16 (0U)
#  define Rte_InitValue_DesiredTunPers_Cnt_u16 (0U)
#  define Rte_InitValue_DesiredTunSet_Cnt_u16 (0U)
#  define Rte_InitValue_HwTorque_HwNm_f32 (0.0F)
#  define Rte_InitValue_TuningSessionActPtr_Cnt_u8 (255U)
#  define Rte_InitValue_VehicleSpeed_Kph_f32 (0.0F)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_Ap_10_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

extern VAR(Rte_tsTask_Init_10, RTE_VAR_NOINIT) Rte_Task_Init_10;

extern VAR(Rte_tsTask_10ms_10, RTE_VAR_NOINIT) Rte_Task_10ms_10;

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

#  define Rte_IRead_TuningSelAuth_Init1_DesiredTunPers_Cnt_u16() \
  (Rte_Task_Init_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Init1.Rte_DesiredTunPers_Cnt_u16.value)

#  define Rte_IRead_TuningSelAuth_Init1_DesiredTunSet_Cnt_u16() \
  (Rte_Task_Init_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Init1.Rte_DesiredTunSet_Cnt_u16.value)

#  define Rte_IWrite_TuningSelAuth_Init1_ActiveTunPers_Cnt_u16(data) \
  ( \
    Rte_Task_Init_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Init1.Rte_ActiveTunPers_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_TuningSelAuth_Init1_ActiveTunPers_Cnt_u16() \
  (&Rte_Task_Init_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Init1.Rte_ActiveTunPers_Cnt_u16.value)

#  define Rte_IWrite_TuningSelAuth_Init1_ActiveTunSet_Cnt_u16(data) \
  ( \
    Rte_Task_Init_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Init1.Rte_ActiveTunSet_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_TuningSelAuth_Init1_ActiveTunSet_Cnt_u16() \
  (&Rte_Task_Init_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Init1.Rte_ActiveTunSet_Cnt_u16.value)

#  define Rte_IRead_TuningSelAuth_Per1_ActiveTunOvrPtrAddr_Cnt_u32() \
  (Rte_Task_10ms_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Per1.Rte_ActiveTunOvrPtrAddr_Cnt_u32.value)

#  define Rte_IRead_TuningSelAuth_Per1_DesiredTunPers_Cnt_u16() \
  (Rte_Task_10ms_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Per1.Rte_DesiredTunPers_Cnt_u16.value)

#  define Rte_IRead_TuningSelAuth_Per1_DesiredTunSet_Cnt_u16() \
  (Rte_Task_10ms_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Per1.Rte_DesiredTunSet_Cnt_u16.value)

#  define Rte_IRead_TuningSelAuth_Per1_HwTorque_HwNm_f32() \
  (Rte_Task_10ms_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Per1.Rte_HwTorque_HwNm_f32.value)

#  define Rte_IRead_TuningSelAuth_Per1_TuningSessionActPtr_Cnt_u8() \
  (Rte_Task_10ms_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Per1.Rte_TuningSessionActPtr_Cnt_u8.value)

#  define Rte_IRead_TuningSelAuth_Per1_VehicleSpeed_Kph_f32() \
  (Rte_Task_10ms_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Per1.Rte_VehicleSpeed_Kph_f32.value)

#  define Rte_IWrite_TuningSelAuth_Per1_ActiveTunPers_Cnt_u16(data) \
  ( \
    Rte_Task_10ms_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Per1.Rte_ActiveTunPers_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_TuningSelAuth_Per1_ActiveTunPers_Cnt_u16() \
  (&Rte_Task_10ms_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Per1.Rte_ActiveTunPers_Cnt_u16.value)

#  define Rte_IWrite_TuningSelAuth_Per1_ActiveTunSet_Cnt_u16(data) \
  ( \
    Rte_Task_10ms_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Per1.Rte_ActiveTunSet_Cnt_u16.value = (data) \
  )

#  define Rte_IWriteRef_TuningSelAuth_Per1_ActiveTunSet_Cnt_u16() \
  (&Rte_Task_10ms_10.Rte_RB.Rte_Ap_TuningSelAuth_TuningSelAuth_Per1.Rte_ActiveTunSet_Cnt_u16.value)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_TUNINGSELAUTH_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_TUNINGSELAUTH_APPL_CODE) TuningSelAuth_Init1(void);

FUNC(void, RTE_AP_TUNINGSELAUTH_APPL_CODE) TuningSelAuth_Per1(void);

# define RTE_STOP_SEC_AP_TUNINGSELAUTH_APPL_CODE
# include "MemMap.h"

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_TUNINGSELAUTH_H */
