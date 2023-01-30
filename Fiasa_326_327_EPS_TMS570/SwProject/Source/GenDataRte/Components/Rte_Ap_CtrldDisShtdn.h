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
 *          File:  Components/Rte_Ap_CtrldDisShtdn.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_CTRLDDISSHTDN_H
# define _RTE_AP_CTRLDDISSHTDN_H

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

#  define Rte_InitValue_AssistAssyPolarity_Cnt_s08 (0)
#  define Rte_InitValue_CRFMtrVel_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_CntDisMtrTrqCmdCRF_MtrNm_f32 (0.0F)
#  define Rte_InitValue_CntDisMtrTrqCmdMRF_MtrNm_f32 (0.0F)
#  define Rte_InitValue_CtrldDmpStsCmp_Cnt_lgc (FALSE)
#  define Rte_InitValue_DiagStsF2Active_Cnt_lgc (FALSE)
#  define Rte_InitValue_SumLimTrqCmd_MtrNm_f32 (0.0F)
#  define Rte_InitValue_SysC_CRFMtrTrqCmd_MtrNm_f32 (0.0F)
#  define Rte_InitValue_SysC_MRFMtrTrqCmd_MtrNm_f32 (0.0F)
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

#  define Rte_IRead_CtrldDisShtdn_Per1_AssistAssyPolarity_Cnt_s08() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_AssistAssyPolarity_Cnt_s08.value)

#  define Rte_IRead_CtrldDisShtdn_Per1_CRFMtrVel_MtrRadpS_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_CRFMtrVel_MtrRadpS_f32.value)

#  define Rte_IRead_CtrldDisShtdn_Per1_DiagStsF2Active_Cnt_lgc() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_DiagStsF2Active_Cnt_lgc.value)

#  define Rte_IRead_CtrldDisShtdn_Per1_SumLimTrqCmd_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_Sweep2_OutputMtrTrq_MtrNm_f32.value)

#  define Rte_IWrite_CtrldDisShtdn_Per1_CntDisMtrTrqCmdCRF_MtrNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_CntDisMtrTrqCmdCRF_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_CtrldDisShtdn_Per1_CntDisMtrTrqCmdCRF_MtrNm_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_CntDisMtrTrqCmdCRF_MtrNm_f32.value)

#  define Rte_IWrite_CtrldDisShtdn_Per1_CntDisMtrTrqCmdMRF_MtrNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_CntDisMtrTrqCmdMRF_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_CtrldDisShtdn_Per1_CntDisMtrTrqCmdMRF_MtrNm_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_CntDisMtrTrqCmdMRF_MtrNm_f32.value)

#  define Rte_IWrite_CtrldDisShtdn_Per1_CtrldDmpStsCmp_Cnt_lgc(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_CtrldDmpStsCmp_Cnt_lgc.value = (data) \
  )

#  define Rte_IWriteRef_CtrldDisShtdn_Per1_CtrldDmpStsCmp_Cnt_lgc() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_CtrldDmpStsCmp_Cnt_lgc.value)

#  define Rte_IWrite_CtrldDisShtdn_Per1_SysC_CRFMtrTrqCmd_MtrNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_SysC_CRFMtrTrqCmd_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_CtrldDisShtdn_Per1_SysC_CRFMtrTrqCmd_MtrNm_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_SysC_CRFMtrTrqCmd_MtrNm_f32.value)

#  define Rte_IWrite_CtrldDisShtdn_Per1_SysC_MRFMtrTrqCmd_MtrNm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_SysC_MRFMtrTrqCmd_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_CtrldDisShtdn_Per1_SysC_MRFMtrTrqCmd_MtrNm_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_CtrldDisShtdn_CtrldDisShtdn_Per1.Rte_SysC_MRFMtrTrqCmd_MtrNm_f32.value)


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState_Mode() Rte_ModeMachine_StaMd_SystemState_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) DtrmnElapsedTime_mS_u16(UInt32 InitialTime, P2VAR(UInt16, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) ElapsedTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(arg1, arg2) (DtrmnElapsedTime_mS_u16(arg1, arg2), ((Std_ReturnType)RTE_E_OK))
#  define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"
FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) GetSystemTime_mS_u32(P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) CurrentTime);
#  define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_SystemTime_GetSystemTime_mS_u32(arg1) (GetSystemTime_mS_u32(arg1), ((Std_ReturnType)RTE_E_OK))


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_CTRLDDISSHTDN_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_CTRLDDISSHTDN_APPL_CODE) CtrldDisShtdn_Per1(void);

# define RTE_STOP_SEC_AP_CTRLDDISSHTDN_APPL_CODE
# include "MemMap.h"

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_CTRLDDISSHTDN_H */
