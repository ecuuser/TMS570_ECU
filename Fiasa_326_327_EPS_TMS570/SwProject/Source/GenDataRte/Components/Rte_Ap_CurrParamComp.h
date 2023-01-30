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
 *          File:  Components/Rte_Ap_CurrParamComp.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_CURRPARAMCOMP_H
# define _RTE_AP_CURRPARAMCOMP_H

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

#  define Rte_InitValue_CuTempEst_DegC_f32 (0.0F)
#  define Rte_InitValue_EstKe_VpRadpS_f32 (0.0F)
#  define Rte_InitValue_EstLd_Henry_f32 (0.0F)
#  define Rte_InitValue_EstLq_Henry_f32 (0.0F)
#  define Rte_InitValue_EstR_Ohm_f32 (0.0F)
#  define Rte_InitValue_MagTempEst_DegC_f32 (0.0F)
#  define Rte_InitValue_MtrCurrDaxRef_Amp_f32 (0.0F)
#  define Rte_InitValue_MtrCurrQaxRef_Amp_f32 (0.0F)
#  define Rte_InitValue_SiTempEst_DegC_f32 (0.0F)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_Ap_10_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

extern VAR(Rte_tsTask_Init_10, RTE_VAR_NOINIT) Rte_Task_Init_10;

extern VAR(Rte_tsTask_2ms_10, RTE_VAR_NOINIT) Rte_Task_2ms_10;

extern VAR(Rte_tsTask_100ms_10, RTE_VAR_NOINIT) Rte_Task_100ms_10;

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

#  define Rte_IWrite_CurrParamComp_Init_EstKe_VpRadpS_f32(data) \
  ( \
    Rte_Task_Init_10.Rte_TB.Rte_I_CurrParamComp_EstKe_VpRadpS_f32.value = (data) \
  )

#  define Rte_IWriteRef_CurrParamComp_Init_EstKe_VpRadpS_f32() \
  (&Rte_Task_Init_10.Rte_TB.Rte_I_CurrParamComp_EstKe_VpRadpS_f32.value)

#  define Rte_IWrite_CurrParamComp_Init_EstLd_Henry_f32(data) \
  ( \
    Rte_Task_Init_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Init.Rte_EstLd_Henry_f32.value = (data) \
  )

#  define Rte_IWriteRef_CurrParamComp_Init_EstLd_Henry_f32() \
  (&Rte_Task_Init_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Init.Rte_EstLd_Henry_f32.value)

#  define Rte_IWrite_CurrParamComp_Init_EstLq_Henry_f32(data) \
  ( \
    Rte_Task_Init_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Init.Rte_EstLq_Henry_f32.value = (data) \
  )

#  define Rte_IWriteRef_CurrParamComp_Init_EstLq_Henry_f32() \
  (&Rte_Task_Init_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Init.Rte_EstLq_Henry_f32.value)

#  define Rte_IWrite_CurrParamComp_Init_EstR_Ohm_f32(data) \
  ( \
    Rte_Task_Init_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Init.Rte_EstR_Ohm_f32.value = (data) \
  )

#  define Rte_IWriteRef_CurrParamComp_Init_EstR_Ohm_f32() \
  (&Rte_Task_Init_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Init.Rte_EstR_Ohm_f32.value)

#  define Rte_IRead_CurrParamComp_Per1_MtrCurrDaxRef_Amp_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CurrCmd_MtrCurrDaxRef_Amp_f32.value)

#  define Rte_IRead_CurrParamComp_Per1_MtrCurrQaxRef_Amp_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CurrCmd_MtrCurrQaxRef_Amp_f32.value)

#  define Rte_IWrite_CurrParamComp_Per1_EstKe_VpRadpS_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Per1.Rte_EstKe_VpRadpS_f32.value = (data) \
  )

#  define Rte_IWriteRef_CurrParamComp_Per1_EstKe_VpRadpS_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Per1.Rte_EstKe_VpRadpS_f32.value)

#  define Rte_IWrite_CurrParamComp_Per1_EstLd_Henry_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Per1.Rte_EstLd_Henry_f32.value = (data) \
  )

#  define Rte_IWriteRef_CurrParamComp_Per1_EstLd_Henry_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Per1.Rte_EstLd_Henry_f32.value)

#  define Rte_IWrite_CurrParamComp_Per1_EstLq_Henry_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Per1.Rte_EstLq_Henry_f32.value = (data) \
  )

#  define Rte_IWriteRef_CurrParamComp_Per1_EstLq_Henry_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Per1.Rte_EstLq_Henry_f32.value)

#  define Rte_IWrite_CurrParamComp_Per1_EstR_Ohm_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Per1.Rte_EstR_Ohm_f32.value = (data) \
  )

#  define Rte_IWriteRef_CurrParamComp_Per1_EstR_Ohm_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Per1.Rte_EstR_Ohm_f32.value)

#  define Rte_IRead_CurrParamComp_Per2_CuTempEst_DegC_f32() \
  (Rte_Task_100ms_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Per2.Rte_CuTempEst_DegC_f32.value)

#  define Rte_IRead_CurrParamComp_Per2_MagTempEst_DegC_f32() \
  (Rte_Task_100ms_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Per2.Rte_MagTempEst_DegC_f32.value)

#  define Rte_IRead_CurrParamComp_Per2_SiTempEst_DegC_f32() \
  (Rte_Task_100ms_10.Rte_RB.Rte_Ap_CurrParamComp_CurrParamComp_Per2.Rte_SiTempEst_DegC_f32.value)


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

#  define Rte_Call_EOLNomMtrParamBlk_WriteBlock(arg1) (NvMProxy_WriteBlock((UInt8)7, arg1))


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT
#   define RTE_START_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

extern VAR(EOLNomMtrParamType, RTE_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP) Rte_CurrParamComp_EOLNomMtrParam;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  define Rte_Pim_EOLNomMtrParam() \
  (&Rte_CurrParamComp_EOLNomMtrParam)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_CURRPARAMCOMP_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) CurrParamComp_Init(void);

FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) CurrParamComp_Per1(void);

FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) CurrParamComp_Per2(void);

FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) SCom_EOLNomMtrParam_Get(P2VAR(Float, AUTOMATIC, RTE_AP_CURRPARAMCOMP_APPL_VAR) NomKe_VpRadpS_f32, P2VAR(Float, AUTOMATIC, RTE_AP_CURRPARAMCOMP_APPL_VAR) NomRmtr_Ohm_f32);

FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) SCom_EOLNomMtrParam_Set(Float NomKe_VpRadpS_f32, Float NomRmtr_Ohm_f32);

# define RTE_STOP_SEC_AP_CURRPARAMCOMP_APPL_CODE
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


#endif /* _RTE_AP_CURRPARAMCOMP_H */
