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
 *          File:  Components/Rte_Ap_AvgFricLrn.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_AVGFRICLRN_H
# define _RTE_AP_AVGFRICLRN_H

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

#  define Rte_InitValue_CRFMtrTrq_MtrNm_f32 (0.0F)
#  define Rte_InitValue_DefeatFricLearning_Cnt_lgc (FALSE)
#  define Rte_InitValue_EstFric_HwNm_f32 (0.0F)
#  define Rte_InitValue_FricOffset_HwNm_f32 (0.0F)
#  define Rte_InitValue_HwAng_HwDeg_f32 (0.0F)
#  define Rte_InitValue_HwPosAuthority_Uls_f32 (0.0F)
#  define Rte_InitValue_HwTrq_HwNm_f32 (0.0F)
#  define Rte_InitValue_HwVel_HwRadpS_f32 (0.0F)
#  define Rte_InitValue_LatAcc_g_f32 (0.0F)
#  define Rte_InitValue_SatEstFric_HwNm_f32 (0.0F)
#  define Rte_InitValue_Temperature_DegC_f32 (0.0F)
#  define Rte_InitValue_VehSpd_Kph_f32 (0.0F)
#  define Rte_InitValue_VehicleSpeedValid_Cnt_lgc (FALSE)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for Mode Management
 *********************************************************************************************************************/
extern VAR(Rte_ModeType_StaMd_Mode, RTE_VAR_NOINIT) Rte_ModeMachine_StaMd9_SystemState9_Mode;

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"
# endif /* !defined(RTE_CORE) */



# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

extern VAR(Rte_tsTask_Init_9, RTE_VAR_NOINIT) Rte_Task_Init_9;

extern VAR(Rte_tsTask_10ms_9, RTE_VAR_NOINIT) Rte_Task_10ms_9;

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

#  define Rte_IWrite_AvgFricLrn_Init1_FricOffset_HwNm_f32(data) \
  ( \
    Rte_Task_Init_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Init1.Rte_FricOffset_HwNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_AvgFricLrn_Init1_FricOffset_HwNm_f32() \
  (&Rte_Task_Init_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Init1.Rte_FricOffset_HwNm_f32.value)

#  define Rte_IRead_AvgFricLrn_Per1_CRFMtrTrq_MtrNm_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_CRFMtrTrq_MtrNm_f32.value)

#  define Rte_IRead_AvgFricLrn_Per1_DefeatFricLearning_Cnt_lgc() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_DefeatFricLearning_Cnt_lgc.value)

#  define Rte_IRead_AvgFricLrn_Per1_HwAng_HwDeg_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_HwAng_HwDeg_f32.value)

#  define Rte_IRead_AvgFricLrn_Per1_HwPosAuthority_Uls_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_HwPosAuthority_Uls_f32.value)

#  define Rte_IRead_AvgFricLrn_Per1_HwTrq_HwNm_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_HwTrq_HwNm_f32.value)

#  define Rte_IRead_AvgFricLrn_Per1_HwVel_HwRadpS_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_HwVel_HwRadpS_f32.value)

#  define Rte_IRead_AvgFricLrn_Per1_LatAcc_g_f32() \
  (0.0F)

#  define Rte_IRead_AvgFricLrn_Per1_Temperature_DegC_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_Temperature_DegC_f32.value)

#  define Rte_IRead_AvgFricLrn_Per1_VehSpd_Kph_f32() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_VehSpd_Kph_f32.value)

#  define Rte_IRead_AvgFricLrn_Per1_VehicleSpeedValid_Cnt_lgc() \
  (Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_VehicleSpeedValid_Cnt_lgc.value)

#  define Rte_IWrite_AvgFricLrn_Per1_EstFric_HwNm_f32(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_EstFric_HwNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_AvgFricLrn_Per1_EstFric_HwNm_f32() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_EstFric_HwNm_f32.value)

#  define Rte_IWrite_AvgFricLrn_Per1_FricOffset_HwNm_f32(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_FricOffset_HwNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_AvgFricLrn_Per1_FricOffset_HwNm_f32() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_FricOffset_HwNm_f32.value)

#  define Rte_IWrite_AvgFricLrn_Per1_SatEstFric_HwNm_f32(data) \
  ( \
    Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_SatEstFric_HwNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_AvgFricLrn_Per1_SatEstFric_HwNm_f32() \
  (&Rte_Task_10ms_9.Rte_RB.Rte_Ap_AvgFricLrn_AvgFricLrn_Per1.Rte_SatEstFric_HwNm_f32.value)


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState_Mode() Rte_ModeMachine_StaMd9_SystemState9_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h"
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_WriteBlock(NvM_BlockIdType parg0, P2CONST(UInt8, AUTOMATIC, RTE_NVM_APPL_DATA) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_WriteBlock(NvM_BlockIdType parg0, P2CONST(NvM_DestPtr, AUTOMATIC, RTE_NVM_APPL_DATA) DstPtr);
# endif
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_AvgFricLrnData_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)33, arg1))
#  define RTE_START_SEC_AP_FLTINJECTION_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_AP_FLTINJECTION_APPL_CODE) FltInjection_SCom_FltInjection(P2VAR(Float, AUTOMATIC, RTE_AP_FLTINJECTION_APPL_VAR) SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum);
#  define RTE_STOP_SEC_AP_FLTINJECTION_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_FltInjection_SCom_FltInjection(arg1, arg2) (FltInjection_SCom_FltInjection(arg1, arg2), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_DIAGMGR9_APPL_CODE) NxtrDiagMgr9_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);
#  define RTE_STOP_SEC_AP_DIAGMGR9_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_NxtrDiagMgr_SetNTCStatus NxtrDiagMgr9_SetNTCStatus
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) DtrmnElapsedTime_mS_u32(UInt32 InitialTime, P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) ElapsedTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(arg1, arg2) (DtrmnElapsedTime_mS_u32(arg1, arg2), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) GetSystemTime_mS_u32(P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) CurrentTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_GetSystemTime_mS_u32(arg1) (GetSystemTime_mS_u32(arg1), ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT
#   define RTE_START_SEC_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

extern VAR(AvgFricLrnType, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_AvgFricLrn_AvgFricLrnData;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  define Rte_Pim_AvgFricLrnData() \
  (&Rte_AvgFricLrn_AvgFricLrnData)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_AVGFRICLRN_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_Init1(void);

FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_Per1(void);

FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_GetEOLFric(P2VAR(Float, AUTOMATIC, RTE_AP_AVGFRICLRN_APPL_VAR) EOLFric_HwNm_f32);

FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_GetOffsetOutputDefeat(P2VAR(Boolean, AUTOMATIC, RTE_AP_AVGFRICLRN_APPL_VAR) DefeatOffsetOutput_Cnt_lgc);

FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_GetSelect(P2VAR(Boolean, AUTOMATIC, RTE_AP_AVGFRICLRN_APPL_VAR) EnableFricLearning_Cnt_lgc, P2VAR(Boolean, AUTOMATIC, RTE_AP_AVGFRICLRN_APPL_VAR) EnableOffsetOutput_Cnt_lgc, P2VAR(UInt8, AUTOMATIC, RTE_AP_AVGFRICLRN_APPL_VAR) OpMode_Uls_u08);

FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_InitLearnedTables(void);

FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_ResetToZero(void);

FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_SetEOLFric(Float EOLFric_HwNm_f32);

FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_SetOffsetOutputDefeat(Boolean DefeatOffsetOutput_Cnt_lgc);

FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_SetSelect(Boolean EnableFricLearning_Cnt_lgc, Boolean EnableOffsetOutput_Cnt_lgc, UInt8 OpMode_Uls_u08);

FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_Trns1(void);

# define RTE_STOP_SEC_AP_AVGFRICLRN_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK (1U)

#  define RTE_E_NxtrDiagMgr_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_AVGFRICLRN_H */
