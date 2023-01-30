/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  Copyright (c) 2006-2010 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Rte_Sa_TmprlMon.h
 *     Workspace:  C:/Sankar/Synergy/Working/TmprlMon-pznywf/TmprlMon/autosar
 *     SW-C Type:  Sa_TmprlMon
 *  Generated at:  Tue Jul  7 09:48:21 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  Application header file for SW-C <Sa_TmprlMon> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SA_TMPRLMON_H
# define _RTE_SA_TMPRLMON_H

# ifdef RTE_APPLICATION_HEADER_FILE
#  error Multiple application header files included.
# endif
# define RTE_APPLICATION_HEADER_FILE

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_Type.h"

typedef P2CONST(struct Rte_CDS_Sa_TmprlMon, TYPEDEF, RTE_CONST) Rte_Instance;


/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

# define Rte_InitValue_TMFTestComplete_Cnt_lgc ((Boolean)FALSE)
# define Rte_InitValue_TMFTestStart_Cnt_lgc ((Boolean)FALSE)


# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Rte_ModeType_StaMd_Mode, RTE_CODE) Rte_Mode_Sa_TmprlMon_SystemState_Mode(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon_FetDrvCntl_OP_GET(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_SA_TMPRLMON_APPL_VAR) signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon_PwrSwitchEn_OP_GET(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_SA_TMPRLMON_APPL_VAR) signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon_SysFault2_OP_GET(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_SA_TMPRLMON_APPL_VAR) signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon_SysFault2_OP_SET(IoHwAb_BoolType signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon_SysFault3_OP_GET(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_SA_TMPRLMON_APPL_VAR) signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon_SysFault3_OP_SET(IoHwAb_BoolType signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, P2VAR(UInt16, AUTOMATIC, RTE_SA_TMPRLMON_APPL_VAR) ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon_SystemTime_GetSystemTime_mS_u32(P2VAR(UInt32, AUTOMATIC, RTE_SA_TMPRLMON_APPL_VAR) CurrentTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon_WdMonitor_OP_SET(IoHwAb_BoolType signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon_WdReset_OP_SET(IoHwAb_BoolType signal);

# define RTE_STOP_SEC_CODE
# include "MemMap.h"



/**********************************************************************************************************************
 * Rte_IRead_<r>_<p>_<d>
 * Rte_IStatus_<r>_<p>_<d>
 * Rte_IWrite_<r>_<p>_<d>
 * Rte_IWriteRef_<r>_<p>_<d>
 * Rte_IInvalidate_<r>_<p>_<d>
 *********************************************************************************************************************/

# define Rte_IRead_TmprlMon_Per2_TMFTestStart_Cnt_lgc() \
  (Rte_Inst_Sa_TmprlMon->TmprlMon_Per2_TMFTestStart_Cnt_lgc->value)

# define Rte_IWrite_TmprlMon_Per2_TMFTestComplete_Cnt_lgc(data) \
  ( \
  Rte_Inst_Sa_TmprlMon->TmprlMon_Per2_TMFTestComplete_Cnt_lgc->value = (data) \
  )

# define Rte_IWriteRef_TmprlMon_Per2_TMFTestComplete_Cnt_lgc() \
  (&Rte_Inst_Sa_TmprlMon->TmprlMon_Per2_TMFTestComplete_Cnt_lgc->value)


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
# define Rte_Mode_SystemState_Mode Rte_Mode_Sa_TmprlMon_SystemState_Mode


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (C/S invocation)
 *********************************************************************************************************************/
# define Rte_Call_FetDrvCntl_OP_GET Rte_Call_Sa_TmprlMon_FetDrvCntl_OP_GET
# define Rte_Call_NxtrDiagMgr_SetNTCStatus Rte_Call_Sa_TmprlMon_NxtrDiagMgr_SetNTCStatus
# define Rte_Call_PwrSwitchEn_OP_GET Rte_Call_Sa_TmprlMon_PwrSwitchEn_OP_GET
# define Rte_Call_SysFault2_OP_GET Rte_Call_Sa_TmprlMon_SysFault2_OP_GET
# define Rte_Call_SysFault2_OP_SET Rte_Call_Sa_TmprlMon_SysFault2_OP_SET
# define Rte_Call_SysFault3_OP_GET Rte_Call_Sa_TmprlMon_SysFault3_OP_GET
# define Rte_Call_SysFault3_OP_SET Rte_Call_Sa_TmprlMon_SysFault3_OP_SET
# define Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16 Rte_Call_Sa_TmprlMon_SystemTime_DtrmnElapsedTime_mS_u16
# define Rte_Call_SystemTime_GetSystemTime_mS_u32 Rte_Call_Sa_TmprlMon_SystemTime_GetSystemTime_mS_u32
# define Rte_Call_WdMonitor_OP_SET Rte_Call_Sa_TmprlMon_WdMonitor_OP_SET
# define Rte_Call_WdReset_OP_SET Rte_Call_Sa_TmprlMon_WdReset_OP_SET




# define RTE_START_SEC_SA_TMPRLMON_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 *
 * Runnable Entity Name: TmprlMon_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *
 **********************************************************************************************************************
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_WdMonitor_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_WdMonitor_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_TMPRLMON_APPL_CODE) TmprlMon_Per1(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TmprlMon_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <OFF, DISABLE, OPERATE>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Boolean Rte_IRead_TmprlMon_Per2_TMFTestStart_Cnt_lgc(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_TmprlMon_Per2_TMFTestComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_TmprlMon_Per2_TMFTestComplete_Cnt_lgc(void)
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FetDrvCntl_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_FetDrvCntl_E_NOT_OK
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *   Std_ReturnType Rte_Call_PwrSwitchEn_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_PwrSwitchEn_E_NOT_OK
 *   Std_ReturnType Rte_Call_SysFault2_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault2_E_NOT_OK
 *   Std_ReturnType Rte_Call_SysFault3_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault3_E_NOT_OK
 *   Std_ReturnType Rte_Call_WdReset_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_WdReset_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_TMPRLMON_APPL_CODE) TmprlMon_Per2(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TmprlMon_Per3
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *     and not in Mode(s) <WARMINIT, OFF>
 *
 **********************************************************************************************************************
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FetDrvCntl_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_FetDrvCntl_E_NOT_OK
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *   Std_ReturnType Rte_Call_PwrSwitchEn_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_PwrSwitchEn_E_NOT_OK
 *   Std_ReturnType Rte_Call_SysFault2_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault2_E_NOT_OK
 *   Std_ReturnType Rte_Call_SysFault3_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault3_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_TMPRLMON_APPL_CODE) TmprlMon_Per3(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TmprlMon_Trns1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on entering of Mode <WARMINIT> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
 *
 **********************************************************************************************************************
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_TMPRLMON_APPL_CODE) TmprlMon_Trns1(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TmprlMon_Trns2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on entering of Mode <DISABLE> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
 *
 **********************************************************************************************************************
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_SysFault2_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault2_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_TMPRLMON_APPL_CODE) TmprlMon_Trns2(void);

# define RTE_STOP_SEC_SA_TMPRLMON_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

# define RTE_E_FetDrvCntl_E_NOT_OK (1u)

# define RTE_E_NxtrDiagMgr_E_NOT_OK (1u)

# define RTE_E_PwrSwitchEn_E_NOT_OK (1u)

# define RTE_E_SysFault2_E_NOT_OK (1u)

# define RTE_E_SysFault3_E_NOT_OK (1u)

# define RTE_E_WdMonitor_E_NOT_OK (1u)

# define RTE_E_WdReset_E_NOT_OK (1u)

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1436273839
#    error "The magic number of the generated file <C:/Sankar/Synergy/Working/TmprlMon-pznywf/TmprlMon/tools/contract/Sa_TmprlMon/Rte_Sa_TmprlMon.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1436273839
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_SA_TMPRLMON_H */
