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
 *          File:  Components/Rte_Ap_DigPhsReasDiag.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_DIGPHSREASDIAG_H
# define _RTE_AP_DIGPHSREASDIAG_H

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

#  define Rte_InitValue_ExpectedOnTimeA_Cnt_u32 (0U)
#  define Rte_InitValue_ExpectedOnTimeB_Cnt_u32 (0U)
#  define Rte_InitValue_ExpectedOnTimeC_Cnt_u32 (0U)
#  define Rte_InitValue_GateDriveResetActive_Cnt_lgc (FALSE)
#  define Rte_InitValue_LRPRCorrectedMtrPosCaptured_Rev_f32 (0.0F)
#  define Rte_InitValue_LRPRModulationIndexCaptured_Uls_f32 (0.0F)
#  define Rte_InitValue_LRPRPhaseadvanceCaptured_Cnt_s16 (0)
#  define Rte_InitValue_MeasuredOnTimeA_Cnt_u32 (0U)
#  define Rte_InitValue_MeasuredOnTimeB_Cnt_u32 (0U)
#  define Rte_InitValue_MeasuredOnTimeC_Cnt_u32 (0U)
#  define Rte_InitValue_MotorVelMRFUnfiltered_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_MtrElecMechPolarity_Cnt_s08 (0)
#  define Rte_InitValue_PDActivateTest_Cnt_lgc (FALSE)
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

#  define Rte_IRead_DigPhsReasDiag_Per1_ExpectedOnTimeA_Cnt_u32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_ExpectedOnTimeA_Cnt_u32.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_ExpectedOnTimeB_Cnt_u32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_ExpectedOnTimeB_Cnt_u32.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_ExpectedOnTimeC_Cnt_u32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_ExpectedOnTimeC_Cnt_u32.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_GateDriveResetActive_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_GateDriveResetActive_Cnt_lgc.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_LRPRCorrectedMtrPosCaptured_Rev_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_LRPRCorrectedMtrPosCaptured_Rev_f32.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_LRPRModulationIndexCaptured_Uls_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_LRPRModulationIndexCaptured_Uls_f32.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_LRPRPhaseadvanceCaptured_Cnt_s16() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_LRPRPhaseadvanceCaptured_Cnt_s16.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_MeasuredOnTimeA_Cnt_u32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_MeasuredOnTimeA_Cnt_u32.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_MeasuredOnTimeB_Cnt_u32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_MeasuredOnTimeB_Cnt_u32.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_MeasuredOnTimeC_Cnt_u32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_MeasuredOnTimeC_Cnt_u32.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_MotorVelMRFUnfiltered_MtrRadpS_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_MotorVelMRFUnfiltered_MtrRadpS_f32.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_MtrElecMechPolarity_Cnt_s08() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_MtrElecMechPolarity_Cnt_s08.value)

#  define Rte_IRead_DigPhsReasDiag_Per1_PDActivateTest_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_DigPhsReasDiag_DigPhsReasDiag_Per1.Rte_PDActivateTest_Cnt_lgc.value)


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


# define RTE_START_SEC_AP_DIGPHSREASDIAG_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_DIGPHSREASDIAG_APPL_CODE) DigPhsReasDiag_Init(void);

FUNC(void, RTE_AP_DIGPHSREASDIAG_APPL_CODE) DigPhsReasDiag_Per1(void);

FUNC(void, RTE_AP_DIGPHSREASDIAG_APPL_CODE) DigPhsReasDiag_Trans1(void);

# define RTE_STOP_SEC_AP_DIGPHSREASDIAG_APPL_CODE
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


#endif /* _RTE_AP_DIGPHSREASDIAG_H */
