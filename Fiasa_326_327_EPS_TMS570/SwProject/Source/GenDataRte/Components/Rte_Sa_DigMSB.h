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
 *          File:  Components/Rte_Sa_DigMSB.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SA_DIGMSB_H
# define _RTE_SA_DIGMSB_H

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

#  define Rte_InitValue_AlignedCumMechMtrPosCRF_Deg_f32 (0.0F)
#  define Rte_InitValue_AlignedCumMechMtrPosMRF_Deg_f32 (0.0F)
#  define Rte_InitValue_AlignedCumMechMtrPosStatus_Cnt_u08 (0U)
#  define Rte_InitValue_AssistAssemblyPolarity_Cnt_s08 (0)
#  define Rte_InitValue_CorrectedElecMtrPos_Rev_u0p16 (0U)
#  define Rte_InitValue_CumMechMtrPos_Rev_f32 (0.0F)
#  define Rte_InitValue_CumMechMtrPosCRF_Deg_f32 (0.0F)
#  define Rte_InitValue_CumMechMtrPosMRF_Deg_f32 (0.0F)
#  define Rte_InitValue_CumMechMtrPosStatus_Cnt_u08 (0U)
#  define Rte_InitValue_Die1RxError_Cnt_u16 (0U)
#  define Rte_InitValue_Die1RxMtrPos_Cnt_u16 (0U)
#  define Rte_InitValue_Die1RxRevCtr_Cnt_u16 (0U)
#  define Rte_InitValue_Die1UnderVoltgFltAccum_Cnt_u16 (0U)
#  define Rte_InitValue_Die2RxError_Cnt_u16 (0U)
#  define Rte_InitValue_Die2RxMtrPos_Cnt_u16 (0U)
#  define Rte_InitValue_Die2RxRevCtr_Cnt_u16 (0U)
#  define Rte_InitValue_EnergyModeState_Cnt_enum (0U)
#  define Rte_InitValue_MechMtrPos2_Rev_u0p16 (0U)
#  define Rte_InitValue_MtrPosPolarity_Cnt_s08 (0)
#  define Rte_InitValue_RxMtrPosParityAccum_Cnt_u16 (0U)
#  define Rte_InitValue_SysCCumMechMtrPosMRF_Deg_f32 (0.0F)
#  define Rte_InitValue_UncorrMechMtrPos1_Rev_u0p16 (0U)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_Ap_10_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

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

#  define Rte_IRead_DigMSB_Per2_AssistAssemblyPolarity_Cnt_s08() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_Polarity_AssistAssyPolarity_Cnt_s08.value)

#  define Rte_IRead_DigMSB_Per2_CorrectedElecMtrPos_Rev_u0p16() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_CorrectedElecMtrPos_Rev_u0p16.value)

#  define Rte_IRead_DigMSB_Per2_CumMechMtrPos_Rev_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_CumMechMtrPos_Rev_f32.value)

#  define Rte_IRead_DigMSB_Per2_Die1RxError_Cnt_u16() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_Die1RxError_Cnt_u16.value)

#  define Rte_IRead_DigMSB_Per2_Die1RxMtrPos_Cnt_u16() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_Die1RxMtrPos_Cnt_u16.value)

#  define Rte_IRead_DigMSB_Per2_Die1RxRevCtr_Cnt_u16() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_Die1RxRevCtr_Cnt_u16.value)

#  define Rte_IRead_DigMSB_Per2_Die1UnderVoltgFltAccum_Cnt_u16() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_Die1UnderVoltgFltAccum_Cnt_u16.value)

#  define Rte_IRead_DigMSB_Per2_Die2RxError_Cnt_u16() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_Die2RxError_Cnt_u16.value)

#  define Rte_IRead_DigMSB_Per2_Die2RxMtrPos_Cnt_u16() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_Die2RxMtrPos_Cnt_u16.value)

#  define Rte_IRead_DigMSB_Per2_Die2RxRevCtr_Cnt_u16() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_Die2RxRevCtr_Cnt_u16.value)

#  define Rte_IRead_DigMSB_Per2_MtrPosPolarity_Cnt_s08() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Sa_DigMSB_DigMSB_Per2.Rte_MtrPosPolarity_Cnt_s08.value)

#  define Rte_IRead_DigMSB_Per2_RxMtrPosParityAccum_Cnt_u16() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_RxMtrPosParityAccum_Cnt_u16.value)

#  define Rte_IRead_DigMSB_Per2_UncorrMechMtrPos1_Rev_u0p16() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_CDDInterface_UncorrMechMtrPos1_Rev_u0p16.value)

#  define Rte_IWrite_DigMSB_Per2_AlignedCumMechMtrPosCRF_Deg_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_AlignedCumMechMtrPosCRF_Deg_f32.value = (data) \
  )

#  define Rte_IWriteRef_DigMSB_Per2_AlignedCumMechMtrPosCRF_Deg_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_AlignedCumMechMtrPosCRF_Deg_f32.value)

#  define Rte_IWrite_DigMSB_Per2_AlignedCumMechMtrPosMRF_Deg_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_DigMSB_DigMSB_Per2.Rte_AlignedCumMechMtrPosMRF_Deg_f32.value = (data) \
  )

#  define Rte_IWriteRef_DigMSB_Per2_AlignedCumMechMtrPosMRF_Deg_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_DigMSB_DigMSB_Per2.Rte_AlignedCumMechMtrPosMRF_Deg_f32.value)

#  define Rte_IWrite_DigMSB_Per2_AlignedCumMechMtrPosStatus_Cnt_u08(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_AlignedCumMechMtrPosStatus_Cnt_u08.value = (data) \
  )

#  define Rte_IWriteRef_DigMSB_Per2_AlignedCumMechMtrPosStatus_Cnt_u08() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_AlignedCumMechMtrPosStatus_Cnt_u08.value)

#  define Rte_IWrite_DigMSB_Per2_CumMechMtrPosCRF_Deg_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_CumMechMtrPosCRF_Deg_f32.value = (data) \
  )

#  define Rte_IWriteRef_DigMSB_Per2_CumMechMtrPosCRF_Deg_f32() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_CumMechMtrPosCRF_Deg_f32.value)

#  define Rte_IWrite_DigMSB_Per2_CumMechMtrPosMRF_Deg_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_DigMSB_DigMSB_Per2.Rte_CumMechMtrPosMRF_Deg_f32.value = (data) \
  )

#  define Rte_IWriteRef_DigMSB_Per2_CumMechMtrPosMRF_Deg_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_DigMSB_DigMSB_Per2.Rte_CumMechMtrPosMRF_Deg_f32.value)

#  define Rte_IWrite_DigMSB_Per2_CumMechMtrPosStatus_Cnt_u08(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_DigMSB_DigMSB_Per2.Rte_CumMechMtrPosStatus_Cnt_u08.value = (data) \
  )

#  define Rte_IWriteRef_DigMSB_Per2_CumMechMtrPosStatus_Cnt_u08() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_DigMSB_DigMSB_Per2.Rte_CumMechMtrPosStatus_Cnt_u08.value)

#  define Rte_IWrite_DigMSB_Per2_MechMtrPos2_Rev_u0p16(data) \
  ( \
    Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_MechMtrPos2_Rev_u0p16.value = (data) \
  )

#  define Rte_IWriteRef_DigMSB_Per2_MechMtrPos2_Rev_u0p16() \
  (&Rte_Task_2ms_10.Rte_TB.Rte_I_DigMSB_MechMtrPos2_Rev_u0p16.value)

#  define Rte_IWrite_DigMSB_Per2_SysCCumMechMtrPosMRF_Deg_f32(data) \
  ( \
    Rte_Task_2ms_10.Rte_RB.Rte_Sa_DigMSB_DigMSB_Per2.Rte_SysCCumMechMtrPosMRF_Deg_f32.value = (data) \
  )

#  define Rte_IWriteRef_DigMSB_Per2_SysCCumMechMtrPosMRF_Deg_f32() \
  (&Rte_Task_2ms_10.Rte_RB.Rte_Sa_DigMSB_DigMSB_Per2.Rte_SysCCumMechMtrPosMRF_Deg_f32.value)

#  define Rte_IRead_DigMSB_Per3_EnergyModeState_Cnt_enum() \
  (Rte_Task_100ms_10.Rte_RB.Rte_Sa_DigMSB_DigMSB_Per3.Rte_EnergyModeState_Cnt_enum.value)


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


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

#  ifndef RTE_MICROSAR_PIM_EXPORT
#   define RTE_START_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

extern VAR(DigMSBEOLType, RTE_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP) Rte_DigMSB_DigMSBEOLData;

#   define RTE_STOP_SEC_VAR_DEFAULT_RTE_Ap_10_PIM_GROUP_UNSPECIFIED
#   include "MemMap.h"

#  endif

#  define Rte_Pim_DigMSBEOLData() \
  (&Rte_DigMSB_DigMSBEOLData)


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_SA_DIGMSB_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGMSB_APPL_CODE) DigMSB_Init(void);

FUNC(void, RTE_SA_DIGMSB_APPL_CODE) DigMSB_Per2(void);

FUNC(void, RTE_SA_DIGMSB_APPL_CODE) DigMSB_Per3(void);

# define RTE_STOP_SEC_SA_DIGMSB_APPL_CODE
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


#endif /* _RTE_SA_DIGMSB_H */
