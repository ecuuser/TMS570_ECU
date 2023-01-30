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
 *          File:  Components/Rte_Ap_ActivePull.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_ACTIVEPULL_H
# define _RTE_AP_ACTIVEPULL_H

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

#  define Rte_InitValue_DisableLearning_Cnt_lgc (FALSE)
#  define Rte_InitValue_DisableOutput_Cnt_lgc (FALSE)
#  define Rte_InitValue_HandwheelAuthority_Uls_f32 (0.0F)
#  define Rte_InitValue_HandwheelPosition_HwDeg_f32 (0.0F)
#  define Rte_InitValue_HandwheelVelocity_HwRadpS_f32 (0.0F)
#  define Rte_InitValue_HwTorque_HwNm_f32 (0.0F)
#  define Rte_InitValue_PullCompCmd_MtrNm_f32 (0.0F)
#  define Rte_InitValue_SrlComYawRate_DegpS_f32 (0.0F)
#  define Rte_InitValue_VehicleSpeed_Kph_f32 (0.0F)
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

#  define Rte_IRead_ActivePull_Per1_DisableLearning_Cnt_lgc() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per1.Rte_DisableLearning_Cnt_lgc.value)

#  define Rte_IRead_ActivePull_Per1_DisableOutput_Cnt_lgc() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per1.Rte_DisableOutput_Cnt_lgc.value)

#  define Rte_IRead_ActivePull_Per1_HandwheelAuthority_Uls_f32() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per1.Rte_HandwheelAuthority_Uls_f32.value)

#  define Rte_IRead_ActivePull_Per1_HandwheelPosition_HwDeg_f32() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per1.Rte_HandwheelPosition_HwDeg_f32.value)

#  define Rte_IRead_ActivePull_Per1_HandwheelVelocity_HwRadpS_f32() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per1.Rte_HandwheelVelocity_HwRadpS_f32.value)

#  define Rte_IRead_ActivePull_Per1_HwTorque_HwNm_f32() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per1.Rte_HwTorque_HwNm_f32.value)

#  define Rte_IRead_ActivePull_Per1_SrlComYawRate_DegpS_f32() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per1.Rte_SrlComYawRate_DegpS_f32.value)

#  define Rte_IRead_ActivePull_Per1_VehicleSpeedValid_Cnt_lgc() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per1.Rte_VehicleSpeedValid_Cnt_lgc.value)

#  define Rte_IRead_ActivePull_Per1_VehicleSpeed_Kph_f32() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per1.Rte_VehicleSpeed_Kph_f32.value)

#  define Rte_IRead_ActivePull_Per2_DisableOutput_Cnt_lgc() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per2.Rte_DisableOutput_Cnt_lgc.value)

#  define Rte_IRead_ActivePull_Per2_VehicleSpeed_Kph_f32() \
  (Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per2.Rte_VehicleSpeed_Kph_f32.value)

#  define Rte_IWrite_ActivePull_Per2_PullCompCmd_MtrNm_f32(data) \
  ( \
    Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per2.Rte_PullCompCmd_MtrNm_f32.value = (data) \
  )

#  define Rte_IWriteRef_ActivePull_Per2_PullCompCmd_MtrNm_f32() \
  (&Rte_Task_2ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per2.Rte_PullCompCmd_MtrNm_f32.value)

#  define Rte_IRead_ActivePull_Per3_HwTorque_HwNm_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per3.Rte_HwTorque_HwNm_f32.value)

#  define Rte_IRead_ActivePull_Per3_VehicleSpeed_Kph_f32() \
  (Rte_Task_100ms_9.Rte_RB.Rte_Ap_ActivePull_ActivePull_Per3.Rte_VehicleSpeed_Kph_f32.value)


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_SystemState_Mode() Rte_ModeMachine_StaMd9_SystemState9_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
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


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_ACTIVEPULL_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_Init1(void);

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_Per1(void);

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_Per2(void);

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_Per3(void);

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_SCom_ReadParam(P2VAR(Float, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) PullCompCmd_HwNm_f32, P2VAR(Float, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) STComp_HwNm_f32, P2VAR(Float, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) LTComp_HwNm_f32, P2VAR(Boolean, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) EnableLearn_Cnt_lgc);

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_SCom_Reset(void);

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_SCom_SetLTComp(Float LTComp_HwNm_f32);

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_SCom_SetSTComp(Float STComp_HwNm_f32);

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_Trns1(void);

# define RTE_STOP_SEC_AP_ACTIVEPULL_APPL_CODE
# include "MemMap.h"

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_ACTIVEPULL_H */
