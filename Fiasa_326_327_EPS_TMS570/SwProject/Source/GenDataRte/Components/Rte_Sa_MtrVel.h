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
 *          File:  Components/Rte_Sa_MtrVel.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SA_MTRVEL_H
# define _RTE_SA_MTRVEL_H

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

#  define Rte_InitValue_AsstAssemblyPolarity_Cnt_s08 (0)
#  define Rte_InitValue_HandwheelVel_HwRadpS_f32 (0.0F)
#  define Rte_InitValue_HwVelValid_Cnt_lgc (FALSE)
#  define Rte_InitValue_MechMtrPos2_Rev_u0p16 (0U)
#  define Rte_InitValue_MechMtrPos2Timestamp_USec_u32 (0U)
#  define Rte_InitValue_MotorVelCRF_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_MotorVelMRF_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_SysCDiagHwVel_HwRadpS_f32 (0.0F)
#  define Rte_InitValue_SysCDiagMtrVelMRF_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_SysCHandwheelVel_HwRadpS_f32 (0.0F)
#  define Rte_InitValue_SysCMotorVelMRF_MtrRadpS_f32 (0.0F)
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

#  define Rte_IRead_MtrVel_Per1_AsstAssemblyPolarity_Cnt_s08() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_Polarity_AssistAssyPolarity_Cnt_s08.value)

#  define Rte_IRead_MtrVel_Per1_MechMtrPos2Timestamp_USec_u32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_MechMtrPos2TimeStamp_USec_u32.value)

#  define Rte_IRead_MtrVel_Per1_MechMtrPos2_Rev_u0p16() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_MechMtrPos2_Rev_u0p16.value)

#  define Rte_IWrite_MtrVel_Per1_HandwheelVel_HwRadpS_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_MtrVel_HandwheelVel_HwRadpS_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrVel_Per1_HandwheelVel_HwRadpS_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_MtrVel_HandwheelVel_HwRadpS_f32.value)

#  define Rte_IWrite_MtrVel_Per1_MotorVelCRF_MtrRadpS_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_MtrVel_MotorVelCRF_MtrRadpS_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrVel_Per1_MotorVelCRF_MtrRadpS_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_MtrVel_MotorVelCRF_MtrRadpS_f32.value)

#  define Rte_IWrite_MtrVel_Per1_MotorVelMRF_MtrRadpS_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrVel_MtrVel_Per1.Rte_MotorVelMRF_MtrRadpS_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrVel_Per1_MotorVelMRF_MtrRadpS_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrVel_MtrVel_Per1.Rte_MotorVelMRF_MtrRadpS_f32.value)

#  define Rte_IWrite_MtrVel_Per1_SysCHandwheelVel_HwRadpS_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrVel_MtrVel_Per1.Rte_SysCHandwheelVel_HwRadpS_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrVel_Per1_SysCHandwheelVel_HwRadpS_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrVel_MtrVel_Per1.Rte_SysCHandwheelVel_HwRadpS_f32.value)

#  define Rte_IWrite_MtrVel_Per1_SysCMotorVelMRF_MtrRadpS_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrVel_MtrVel_Per1.Rte_SysCMotorVelMRF_MtrRadpS_f32.value = (data) \
  )

#  define Rte_IWriteRef_MtrVel_Per1_SysCMotorVelMRF_MtrRadpS_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrVel_MtrVel_Per1.Rte_SysCMotorVelMRF_MtrRadpS_f32.value)

#  define Rte_IRead_MtrVel_Per2_SysCDiagHwVel_HwRadpS_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrVel_MtrVel_Per2.Rte_SysCDiagHwVel_HwRadpS_f32.value)

#  define Rte_IRead_MtrVel_Per2_SysCDiagMtrVelMRF_MtrRadpS_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrVel_MtrVel_Per2.Rte_SysCDiagMtrVelMRF_MtrRadpS_f32.value)

#  define Rte_IWrite_MtrVel_Per2_HwVelValid_Cnt_lgc(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrVel_MtrVel_Per2.Rte_HwVelValid_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_MtrVel_Per2_HwVelValid_Cnt_lgc() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_MtrVel_MtrVel_Per2.Rte_HwVelValid_Cnt_lgc.value)


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_GetNTCFailed(NTCNumber NTC_Cnt_T_enum, P2VAR(Boolean, AUTOMATIC, RTE_AP_DIAGMGR10_APPL_VAR) NTCFailed_Ptr_T_lgc);
#  define RTE_STOP_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_GetNTCFailed NxtrDiagMgr10_GetNTCFailed
#  define RTE_START_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR10_APPL_CODE) NxtrDiagMgr10_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);
#  define RTE_STOP_SEC_AP_DIAGMGR10_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_SetNTCStatus NxtrDiagMgr10_SetNTCStatus


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_SA_MTRVEL_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_SA_MTRVEL_APPL_CODE) MtrVel_Init(void);

FUNC(void, RTE_SA_MTRVEL_APPL_CODE) MtrVel_Per1(void);

FUNC(void, RTE_SA_MTRVEL_APPL_CODE) MtrVel_Per2(void);

# define RTE_STOP_SEC_SA_MTRVEL_APPL_CODE
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


#endif /* _RTE_SA_MTRVEL_H */
