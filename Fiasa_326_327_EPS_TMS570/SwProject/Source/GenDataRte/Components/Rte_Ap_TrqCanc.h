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
 *          File:  Components/Rte_Ap_TrqCanc.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_TRQCANC_H
# define _RTE_AP_TRQCANC_H

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

#  define Rte_InitValue_EstKe_VpRadpS_f32 (0.0F)
#  define Rte_InitValue_EstLd_Henry_f32 (0.0F)
#  define Rte_InitValue_EstLq_Henry_f32 (0.0F)
#  define Rte_InitValue_MRFMtrVel_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_MtrCurrDaxRef_Amp_f32 (0.0F)
#  define Rte_InitValue_MtrCurrQaxRef_Amp_f32 (0.0F)
#  define Rte_InitValue_MtrTrqCmdMRFScl_MtrNm_f32 (0.0F)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_Ap_10_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

extern VAR(Rte_tsTask_Init_10, RTE_VAR_NOINIT) Rte_Task_Init_10;

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

#  define Rte_IRead_TrqCanc_Init_EstKe_VpRadpS_f32() \
  (Rte_Task_Init_10.Rte_TB.Rte_I_CurrParamComp_EstKe_VpRadpS_f32.value)

#  define Rte_IRead_TrqCanc_Per1_EstKe_VpRadpS_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CurrParamComp_EstKe_VpRadpS_f32.value)

#  define Rte_IRead_TrqCanc_Per1_EstLd_Henry_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CurrParamComp_EstLd_Henry_f32.value)

#  define Rte_IRead_TrqCanc_Per1_EstLq_Henry_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CurrParamComp_EstLq_Henry_f32.value)

#  define Rte_IRead_TrqCanc_Per1_MRFMtrVel_MtrRadpS_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_MtrVel_MotorVelMRF_MtrRadpS_f32.value)

#  define Rte_IRead_TrqCanc_Per1_MtrCurrDaxRef_Amp_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CurrCmd_MtrCurrDaxRef_Amp_f32.value)

#  define Rte_IRead_TrqCanc_Per1_MtrCurrQaxRef_Amp_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CurrCmd_MtrCurrQaxRef_Amp_f32.value)

#  define Rte_IRead_TrqCanc_Per1_MtrTrqCmdMRFScl_MtrNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_TrqCmdScl_MRFMtrTrqCmdScl_MtrNm_f32.value)


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_NVMPROXY_APPL_CODE) NvMProxy_WriteBlock(UInt8 parg0, P2CONST(UInt8, AUTOMATIC, RTE_NVMPROXY_APPL_DATA) DstPtr);
# else
FUNC(Std_ReturnType, RTE_NVMPROXY_APPL_CODE) NvMProxy_WriteBlock(UInt8 parg0, P2CONST(NvM_DestPtr, AUTOMATIC, RTE_NVMPROXY_APPL_DATA) DstPtr);
# endif
#  define RTE_STOP_SEC_NVMPROXY_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_EOLCogTrqCanc_WriteBlock(arg1) (NvMProxy_WriteBlock((UInt8)6, arg1))
#  define Rte_Call_EOLCogTrqRplComp_WriteBlock(arg1) (NvMProxy_WriteBlock((UInt8)11, arg1))


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT
#   define RTE_START_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

extern VAR(CoggingCancTrq, RTE_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP) Rte_TrqCanc_CogTrqCal;
extern VAR(CoggingCancTrqRplComp, RTE_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP) Rte_TrqCanc_CogTrqRplComp;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_CogTrqCal() (&((*RtePim_CogTrqCal())[0]))
#  else
#   define Rte_Pim_CogTrqCal() RtePim_CogTrqCal()
#  endif
#  define RtePim_CogTrqCal() \
  (&Rte_TrqCanc_CogTrqCal)

#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
#   define Rte_Pim_CogTrqRplComp() (&((*RtePim_CogTrqRplComp())[0]))
#  else
#   define Rte_Pim_CogTrqRplComp() RtePim_CogTrqRplComp()
#  endif
#  define RtePim_CogTrqRplComp() \
  (&Rte_TrqCanc_CogTrqRplComp)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_TRQCANC_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Init(void);

FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Per1(void);

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Scom_ReadCogTrqCal(P2VAR(UInt16, AUTOMATIC, RTE_AP_TRQCANC_APPL_VAR) CogTrqCalPtr, UInt16 ID);
# else
FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Scom_ReadCogTrqCal(P2VAR(CoggingCancTrq, AUTOMATIC, RTE_AP_TRQCANC_APPL_VAR) CogTrqCalPtr, UInt16 ID);
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Scom_SetCogTrqCal(P2CONST(UInt16, AUTOMATIC, RTE_AP_TRQCANC_APPL_DATA) CogTrqCalPtr, UInt16 ID);
# else
FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Scom_SetCogTrqCal(P2CONST(CoggingCancTrq, AUTOMATIC, RTE_AP_TRQCANC_APPL_DATA) CogTrqCalPtr, UInt16 ID);
# endif

# define RTE_STOP_SEC_AP_TRQCANC_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_TRQCANC_H */
