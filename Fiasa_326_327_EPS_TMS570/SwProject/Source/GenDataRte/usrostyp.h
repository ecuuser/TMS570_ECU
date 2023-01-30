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
 *          File:  usrostyp.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  User Types header file (osCAN specific)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _USROSTYP_H
# define _USROSTYP_H

# include "Rte_Type.h"

# define RTE_START_SEC_CODE
# include "MemMap.h"

FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_AbsHwPos_EOLVehCntrOffset_GetErrorStatus(NvM_RequestResultType *ErrorStatus);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_AbsHwPos_EOLVehCntrOffset_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ActivePull_SystemTime_DtrmnElapsedTime_mS_u32(UInt32 InitialTime, UInt32 *ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ActivePull_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_AstLmt_SteeringAsstDefeat_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_AvgFricLrn_FltInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_AvgFricLrn_SystemTime_DtrmnElapsedTime_mS_u32(UInt32 InitialTime, UInt32 *ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_AvgFricLrn_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_BVDiag_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_BVDiag_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_BatteryVoltage_OvervoltageData_SetRamBlockStatus(Boolean RamBlockStatus);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_BatteryVoltage_OvervoltageData_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp10_ChkPtAp10_100msEnd_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp10_ChkPtAp10_100msStart_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp10_ChkPtAp10_10msEnd_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp10_ChkPtAp10_10msStart_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp10_ChkPtAp10_2msEnd_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp10_ChkPtAp10_2msStart_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp10_ChkPtAp10_4msEnd_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp10_ChkPtAp10_4msStart_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp8_ChkPtAp8_100msEnd_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp8_ChkPtAp8_100msStart_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp8_ChkPtAp8_2msEnd_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_ChkPtAp8_ChkPtAp8_2msStart_CP_CheckpointReached(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_CurrParamComp_EOLNomMtrParamBlk_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_DiagSvc_AbsHwPos_SCom_CustClrTrim(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_DiagSvc_AbsHwPos_SCom_CustSetTrim(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_DiagSvc_DigColPs_SCom_CustClearTrim(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_DiagSvc_DigColPs_SCom_CustSetTrim(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_DiagSvc_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_DiagSvc_SystemTime_DtrmnElapsedTime_mS_u32(UInt32 InitialTime, UInt32 *ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_DiagSvc_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_DiagSvc_VehDyn_SCom_ResetCenter(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_LrnEOT_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_LrnEOT_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_Polarity_Polarity_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_SrlComInput_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_SrlComInput_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_SrlComOutput_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_SrlComOutput_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_StaMd_CloseCheckData_GetErrorStatus(NvM_RequestResultType *ErrorStatus);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_StaMd_CloseCheckData_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_StaMd_TOD_OP_SET(IoHwAb_BoolType signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_StaMd_TypeHData_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_TrqCanc_EOLCogTrqCanc_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_TrqCanc_EOLCogTrqRplComp_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_TrqCmdScl_TrqCmdScl_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_VehDyn_NVM_VehDynReset_Srv_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_VehPwrMd_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Ap_VehPwrMd_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_BkCpPc_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_BkCpPc_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_CDDInterface_CDDPorts_ApplyMtrElecMechPol(SInt8 MtrElecMechPol_Cnt_s8);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_CDDInterface_CDDPorts_ClearPhsReasSum(UInt16 DataAccessBfr_Cnt_T_u16);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_CmMtrCurr_EOLCurrTempOffset_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_CmMtrCurr_EOLShCurrCal_SetRamBlockStatus(Boolean RamBlockStatus);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_CmMtrCurr_EOLShCurrCal_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_DigColPs_EOLDigColPosCals_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_DigHwTrqSENT_NvM_DigHwTrqSENTTrim_Srv_GetErrorStatus(NvM_RequestResultType *ErrorStatus);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_DigHwTrqSENT_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(const NvM_DestPtr *DstPtr);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_MtrDrvDiag_FetDrvReset_OP_SET(IoHwAb_BoolType signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_MtrDrvDiag_FetFlt1Data_OP_GET(IoHwAb_BoolType *signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_MtrDrvDiag_FetFlt2Clk_OP_GET(IoHwAb_BoolType *signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_MtrDrvDiag_FetFlt2Clk_OP_SET(IoHwAb_BoolType signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_MtrDrvDiag_IoHwAbPortConfig_SetFetFlt2ToOutput(IoHwAb_BoolType signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_OvrVoltMon_phyOvrVoltFdbk_OP_GET(IoHwAb_BoolType *signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_ShtdnMech_FetDrvReset_OP_GET(IoHwAb_BoolType *signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_ShtdnMech_SysFault2_OP_GET(IoHwAb_BoolType *signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_ShtdnMech_SysFault3_OP_GET(IoHwAb_BoolType *signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_TmprlMon2_WdMonitor_OP_SET(IoHwAb_BoolType signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_TmprlMon_FetDrvCntl_OP_GET(IoHwAb_BoolType *signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_TmprlMon_PwrSwitchEn_OP_GET(IoHwAb_BoolType *signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_TmprlMon_SysFault2_OP_GET(IoHwAb_BoolType *signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_TmprlMon_SysFault2_OP_SET(IoHwAb_BoolType signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_TmprlMon_SysFault3_OP_GET(IoHwAb_BoolType *signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_TmprlMon_SysFault3_OP_SET(IoHwAb_BoolType signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_TmprlMon_WdMonitor_OP_SET(IoHwAb_BoolType signal);
FUNC(Std_ReturnType, RTE_CODE) Rte_TrustedCall_Sa_TmprlMon_WdReset_OP_SET(IoHwAb_BoolType signal);

# define RTE_STOP_SEC_CODE
# include "MemMap.h"


#endif /* _USROSTYP_H */
