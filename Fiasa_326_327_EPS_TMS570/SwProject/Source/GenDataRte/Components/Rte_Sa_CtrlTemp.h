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
 *          File:  Components/Rte_Sa_CtrlTemp.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SA_CTRLTEMP_H
# define _RTE_SA_CTRLTEMP_H

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
#  define Rte_InitValue_DiagStsTempRdPrf_Cnt_lgc (FALSE)
#  define Rte_InitValue_FiltMeasTemp_DegC_f32 (0.0F)
#  define Rte_InitValue_TemperatureADC_Volt_f32 (0.0F)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

extern VAR(Rte_tsTask_Init_9, RTE_VAR_NOINIT) Rte_Task_Init_9;

extern VAR(Rte_tsTask_2ms_9, RTE_VAR_NOINIT) Rte_Task_2ms_9;

extern VAR(Rte_tsTask_100ms_9, RTE_VAR_NOINIT) Rte_Task_100ms_9;

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
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

#  define Rte_IRead_CtrlTemp_Init1_TemperatureADC_Volt_f32() \
  (Rte_Task_Init_9.Rte_RB.Rte_Sa_CtrlTemp_CtrlTemp_Init1.Rte_TemperatureADC_Volt_f32.value)

#  define Rte_IWrite_CtrlTemp_Init1_FiltMeasTemp_DegC_f32(data) \
  ( \
    Rte_Task_Init_9.Rte_TB.Rte_I_CtrlTemp_FiltMeasTemp_DegC_f32.value = (data) \
  )

#  define Rte_IWriteRef_CtrlTemp_Init1_FiltMeasTemp_DegC_f32() \
  (&Rte_Task_Init_9.Rte_TB.Rte_I_CtrlTemp_FiltMeasTemp_DegC_f32.value)

#  define Rte_IRead_CtrlTemp_Per1_DiagStsTempRdPrf_Cnt_lgc() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Sa_CtrlTemp_CtrlTemp_Per1.Rte_DiagStsTempRdPrf_Cnt_lgc.value)

#  define Rte_IRead_CtrlTemp_Per1_TemperatureADC_Volt_f32() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Sa_CtrlTemp_CtrlTemp_Per1.Rte_TemperatureADC_Volt_f32.value)

#  define Rte_IWrite_CtrlTemp_Per1_FiltMeasTemp_DegC_f32(data) \
  ( \
    Rte_Task_2ms_9.Rte_RB.Rte_Sa_CtrlTemp_CtrlTemp_Per1.Rte_FiltMeasTemp_DegC_f32.value = (data) \
  )

#  define Rte_IWriteRef_CtrlTemp_Per1_FiltMeasTemp_DegC_f32() \
  (&Rte_Task_2ms_9.Rte_RB.Rte_Sa_CtrlTemp_CtrlTemp_Per1.Rte_FiltMeasTemp_DegC_f32.value)

#  define Rte_IRead_CtrlTemp_Per2_AmbTemp_DegC_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Sa_CtrlTemp_CtrlTemp_Per2.Rte_AmbTemp_DegC_f32.value)


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR9_APPL_CODE) NxtrDiagMgr9_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);
#  define RTE_STOP_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_SetNTCStatus NxtrDiagMgr9_SetNTCStatus


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_SA_CTRLTEMP_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_SA_CTRLTEMP_APPL_CODE) CtrlTemp_Init1(void);

FUNC(void, RTE_SA_CTRLTEMP_APPL_CODE) CtrlTemp_Per1(void);

FUNC(void, RTE_SA_CTRLTEMP_APPL_CODE) CtrlTemp_Per2(void);

# define RTE_STOP_SEC_SA_CTRLTEMP_APPL_CODE
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


#endif /* _RTE_SA_CTRLTEMP_H */
