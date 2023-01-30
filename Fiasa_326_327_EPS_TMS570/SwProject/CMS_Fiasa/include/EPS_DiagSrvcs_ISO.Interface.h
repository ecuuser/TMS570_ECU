/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EPS_DiagSrvcs_ISO.Interface.h file
* Module Description: Common Manufacturing Program Interface for XCP and ISO services
* Product           : Gen II Plus - EA3.0
* Author            : Kevin Smith
*
* Notes:
* This file contains the configurations for the ISO services. It should be
* modified for each program as needed.
*
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Jul 17 11:00:00 2013
 * %version:          EA3#9 %
 * %derived_by:       nzdx8v %
 * %date_modified:    Mon Feb 24 16:47:10 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * --------  -------  --------  ------------------------------------------------------------------------------  -------
 * 12/15/15   5       PS        Added XCP DAQ 0xF0 and 0xF1.
 * 								Enabled XCP DAQ 0x010E, 0x010F
 * 01/22/16   6       PS        changed NRC D_EPSNRCNOTNEXTEERPROD_CNT_U08 from 0x11 to 0x31
 * 03/16/16   7       PS        Enabled XCP DAQ 0x41, 0x42														EA3#6773, EA3#6775
 * 06/21/16   9       PS        Updared state transiitions in cdd file to fix Anomaly EA3#9073 				    EA3#9090
 */


#ifndef EPS_DIAGSRVCS_ISO_INTERFACE_H
#define EPS_DIAGSRVCS_ISO_INTERFACE_H

#include "EPS_DiagSrvcs_CommonData.h"
#include "EPS_DiagSrvcs_SrvcLUTbl.h"
#include "CalConstants.h"
#include "Lnk_Symbols.h"
#include "Ap_DiagMgr.h"
#include "Dcm.h"
#include "Dem.h"


/* --- Common Defines --- */
#define NEXTEER_SESSION						NEXTEER_MANUFACTURING_SERVICES
#define CM_MsgLenType						uint16
#define CM_Std_ReturnType					Std_ReturnType
#define CM_RESP_OK							RTE_E_OK
#define CM_GetCurrentDiagnosticMode			Dcm_GetSesCtrlType
#define D_ALLDTC_MASK_CNT_U32				0xFFFFFFU
#define CM_NULL								0x00u
#define CM_RTE_MODE_StaMd_Mode_OPERATE		RTE_MODE_StaMd_Mode_OPERATE

/* Negative Response Codes */
#define D_EPSNRCNOTNEXTEERPROD_CNT_U08		D_EPSNRCREQOUTOFRANGE_CNT_U08
#define D_EPSNRCSERVICEMISSING_CNT_U08		D_EPSNRCSERVICENOTSUPPORTED_CNT_U16

#ifndef D_CRC16SIZE_CNT_U16
#define D_CRC16SIZE_CNT_U16		2
#endif

/**********************************************************************************************************************
 * --- RTE GLOBAL DATA START ---
 *
 * This section is for variables that are external references to RTE variables. (Formally found in the RTE_GlobalData.h)
 *
 *********************************************************************************************************************/

/* XCP Variables */
extern VAR(Float, RTE_VAR_INIT) Rte_BatteryVoltage_Vecu_Volt_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_DigHwTrqSENT_HwTorque_HwNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_CurrParamComp_EstKe_VpRadpS_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_CurrParamComp_EstR_Ohm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_MtrVel_MotorVelMRF_MtrRadpS_f32;
extern VAR(Float, RTE_VAR_NOINIT) Rte_SignlCondn_VehicleSpeed_Kph_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_CtrlTemp_FiltMeasTemp_DegC_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_MtrTempEst_MagTempEst_DegC_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_CDDInterface_ModIdxFinal_Uls_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_IoHwAbstractionUsr_TemperatureADC_Volt_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_CDDInterface_MtrCurrQax_Amp_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_CDDInterface_MtrCurrDax_Amp_f32;
extern VAR(float32, AUTOMATIC) Rte_Sa_DigColPs_I2CHwAbsPos_HwDeg_f32;
//extern VAR(Float, RTE_VAR_INIT) Rte_SrlComInput_EngineSpeed_Rpm_f32;
extern VAR(uint8, AUTOMATIC) NvMP_Rte_TrqCanc_CogTrqCal[sizeof(CoggingCancTrq)+D_CRC16SIZE_CNT_U16];
extern VAR(uint8, AUTOMATIC) NvMP_Rte_TrqCanc_CogTrqRplComp[sizeof(CoggingCancTrqRplComp)+D_CRC16SIZE_CNT_U16];

/* 00FF */
extern VAR(uint8, AUTOMATIC) NvMP_Rte_DigMSB_DigMSBEOLData[sizeof(DigMSBEOLType)];

/* FD0E, XCP */
extern VAR(Float, RTE_VAR_NOINIT) Rte_CtrldDisShtdn_CntDisMtrTrqCmdMRF_MtrNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_DigMSB_CumMechMtrPosMRF_Deg_f32;

/* FD14, XCP */
extern VAR(Float, RTE_VAR_INIT) Rte_AbsHwPos_HandwheelPosition_HwDeg_f32;

/* FD1A, XCP */
extern VAR(Rte_ModeType_StaMd_Mode, RTE_VAR_NOINIT) Rte_ModeMachine_StaMd_SystemState_Mode;

/* FD30 */
extern VAR(DigHwTrqSENTTrim_DataType, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_DigHwTrqSENT_DigTrqTrim;

/* FD31, XCP */
extern VAR(Float, RTE_VAR_INIT) Rte_DigHwTrqSENT_HwTorque_HwNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_Nhet1_DigHwTrqT1_HwNm_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_Nhet1_DigHwTrqT2_HwNm_f32;

/* Externs and defines for service checks */
extern VAR(Float, RTE_VAR_NOINIT) Rte_Sweep_OutputHwTrq_HwNm_f32;
extern VAR(Boolean, RTE_VAR_INIT) Rte_DiagMgr10_DiagStsDefVehSpd_Cnt_lgc;
#define CM_HwTrq_HwNm_f32				Rte_Sweep_OutputHwTrq_HwNm_f32
#define CM_DiagStsDefVehSpd_Cnt_lgc		Rte_DiagMgr10_DiagStsDefVehSpd_Cnt_lgc
#define CM_VehicleSpeed_Kph_f32			Rte_SignlCondn_VehicleSpeed_Kph_f32
#define CM_k_TrimHwTrqLimit_HwNm_f32	k_SrvcHwTrqLimit_HwNm_f32
#define CM_k_TrimVehSpdLimit_Kph_f32	k_SrvcVehSpdLimit_Kph_f32

/**********************************************************************************************************************
 * --- RTE GLOBAL DATA END ---
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * --- SERIAL COMM FUNCTION START ---
 *
 * This section is for functions that are external references to system functions. (Formally found in the SComm_Func.h)
 *
 *********************************************************************************************************************/

/* 1160 */
extern FUNC(void, RTE_AP_STAMD_APPL_CODE) StaMd_SCom_EcuReset(void);

/* F000 */
extern FUNC(void, RTE_AP_LRNEOT_APPL_CODE) LrnEOT_Scom_ResetEOT(void);
extern FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_ResetToZero(void);
extern FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_InitLearnedTables(void);
extern FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_SCom_ClearTransOvData(void);
extern FUNC(void, RTE_NTWRAP_APPL_CODE) NtWrapC_VehDyn_SCom_ResetCenter(void);
#define CM_Reset_SLP_SCom_SetSLPToInvld NtWrapC_VehDyn_SCom_ResetCenter

/* F001 (F000) */
extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_ResetNTCStatus(void);
extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_ClearBlackBox(void);

/* F003 */
extern FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) NtWrapC_DigColPs_SCom_CustClrTrim(void);
extern FUNC(Std_ReturnType, RTE_NTWRAP_APPL_CODE) NtWrapC_DigColPs_SCom_CustSetTrim(void);

/* F004 */
extern FUNC(Std_ReturnType, RTE_SA_DIGHWTRQSENT_APPL_CODE) NtWrapC_DigHwTrqSENT_SCom_SetTrqTrim(void);
extern FUNC(Std_ReturnType, RTE_SA_DIGHWTRQSENT_APPL_CODE) NtWrapC_DigHwTrqSENT_SCom_ClrTrqTrim(void);

/* F005 (FD13) */
extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_GetNTCInfo(VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																	P2VAR(uint8, AUTOMATIC, AUTOMATIC) Param_Ptr_T_u08,
																	P2VAR(uint8, AUTOMATIC, AUTOMATIC) Status_Ptr_T_u08,
																	P2VAR(uint8, AUTOMATIC, AUTOMATIC) AgingCounter_Ptr_T_u08);

/* F008 */
extern FUNC(Std_ReturnType, RTE_SA_CMMTRCURR_APPL_CODE) NtWrapC_CmMtrCurr_SCom_CalGain(void);

/* F009 */
extern FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_MtrCurrOffReadStatus(P2VAR(MtrCurrOffProcessFlag, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_VAR) CurrOffStatus);
extern FUNC(Std_ReturnType, RTE_SA_CMMTRCURR_APPL_CODE) NtWrapC_CmMtrCurr_SCom_CalOffset(void);

/* F0FF */
extern volatile CONST(boolean, AUTOMATIC) EnableTestMode_Cnt_lgc;
extern FUNC(void, NTWRAP_CODE) TWrapC_ProcessF0FF( P2VAR(uint8, AUTOMATIC, AUTOMATIC) t_SrvcData_Cnt_T_u08, VAR(uint16, AUTOMATIC) RequestDataIdx_Cnt_T_u16);
extern FUNC(void, INTERRUPT_CODE) EnableSysTickInterrupt(void);
extern FUNC(void, INTERRUPT_CODE) DisableSysTickInterrupt(void);
extern FUNC(Std_ReturnType, RTE_WDGM_APPL_CODE) WdgM_CheckpointReached(WdgM_SupervisedEntityIdType parg0, WdgM_CheckpointIdType parg1);

/* FD07 */
extern FUNC(void, RTE_AP_POLARITY_APPL_CODE) Polarity_SCom_ReadPolarity(P2VAR(UInt8, AUTOMATIC, RTE_AP_POLARITY_APPL_VAR) Polarity_Ptr_T_b08);
extern FUNC(void, RTE_AP_POLARITY_APPL_CODE) NtWrapC_Polarity_SCom_SetPolarity(UInt8 Polarity_Cnt_T_b08);

/* FD0D */
extern FUNC(Std_ReturnType, RTE_AP_ASTLMT_APPL_CODE) NtWrapC_AstLmt_Scom_ManualTrqCmd(Boolean EnableManualCtrl, Float MtrTrqCmd_MtrNm_f32);

/* FD12 */
extern FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_ReadMtrCurrCals(P2VAR(PhaseCurrCal_DataType, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_VAR) ShCurrCalPtr);
extern FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) NtWrapC_CmMtrCurr_SCom_SetMtrCurrCals(P2CONST(PhaseCurrCal_DataType, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_DATA) ShCurrCalPtr);

/* FD13 */
extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_ReadStrgArray(void);

/* FD1B */
extern FUNC(void, RTE_AP_SRLCOMINPUT_APPL_CODE) SrlComInput_SCom_ManualVehSpd(Float VehSpd_Kph_f32);

/* FD20 */
extern FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_SCom_ReadTransOvData(P2VAR(UInt16, AUTOMATIC, RTE_AP_BATTERYVOLTAGE_APPL_VAR) OvervoltageCounter_Cnt_u16, P2VAR(Float, AUTOMATIC, RTE_AP_BATTERYVOLTAGE_APPL_VAR) MaxBattVoltage_Volts_f32);
extern FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_SCom_ClearTransOvData(void);

/* FD21 */
extern FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_SCom_GetTuningSet(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) TuningSet_Cnt_T_u08);
extern FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_SCom_SetTuningSet(UInt8 TuningSet_Cnt_T_u08);

/* FD25 */
extern FUNC(void, RTE_AP_TRQCMDSCL_APPL_CODE) TrqCmdScl_SCom_Get(P2VAR(Float, AUTOMATIC, RTE_AP_TRQCMDSCL_APPL_VAR) Par_f32);
extern FUNC(void, RTE_AP_TRQCMDSCL_APPL_CODE) NtWrapC_TrqCmdScl_SCom_Set(Float Par_f32);

/* FD26 */
extern FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_SetSelect(Boolean EnableFricLearning_Cnt_lgc, Boolean EnableOffsetOutput_Cnt_lgc, UInt8 OpMode_Uls_u08);
extern FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_GetSelect(P2VAR(Boolean, AUTOMATIC, RTE_AP_AVGFRICLRN_APPL_VAR) EnableFricLearning_Cnt_lgc, P2VAR(Boolean, AUTOMATIC, RTE_AP_AVGFRICLRN_APPL_VAR) EnableOffsetOutput_Cnt_lgc, P2VAR(UInt8, AUTOMATIC, RTE_AP_AVGFRICLRN_APPL_VAR) OpMode_Uls_u08);

/* FD27 */
extern FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_SetOffsetOutputDefeat(Boolean DefeatOffsetOutput_Cnt_lgc);
extern FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_GetOffsetOutputDefeat(P2VAR(Boolean, AUTOMATIC, RTE_AP_AVGFRICLRN_APPL_VAR) DefeatOffsetOutput_Cnt_lgc);

/* FD29 */
extern FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_SetEOLFric(Float EOLFric_HwNm_f32);
extern FUNC(void, RTE_AP_AVGFRICLRN_APPL_CODE) AvgFricLrn_SCom_GetEOLFric(P2VAR(Float, AUTOMATIC, RTE_AP_AVGFRICLRN_APPL_VAR) EOLFric_HwNm_f32);

/* FD30 */
extern FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_TrimData(P2VAR(Float, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) EOLHwTrqTrim_HwNm_f32, P2VAR(Boolean, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) EOLHwTrqTrimPerformed_Cnt_Lgc);
extern FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) NtWrapC_DigHwTrqSENT_SCom_WriteData(Float HwTrqTrim_HwNm_f32);

/* FDAD */
extern FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_SCom_ReadParam(P2VAR(Float, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) PullCompCmd_HwNm_f32, P2VAR(Float, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) STComp_HwNm_f32, P2VAR(Float, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) LTComp_HwNm_f32, P2VAR(Boolean, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) EnableLearn_Cnt_lgc);

/* FDB0, FDB1, FDB2, FDB3 */
extern FUNC(void, RTE_AP_TRQCANC_APPL_CODE) NtWrapC_TrqCanc_Scom_SetCogTrqCal(P2CONST(CoggingCancTrq, AUTOMATIC, RTE_AP_TRQCANC_APPL_DATA) CogTrqCalPtr, UInt16 ID);
extern FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Scom_ReadCogTrqCal(P2VAR(CoggingCancTrq, AUTOMATIC, RTE_AP_TRQCANC_APPL_VAR) CogTrqCalPtr, UInt16 ID);

/* FDB4 */
extern FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) SCom_EOLNomMtrParam_Get(P2VAR(Float, AUTOMATIC, RTE_AP_CURRPARAMCOMP_APPL_VAR) NomKe_VpRadpS_f32, P2VAR(Float, AUTOMATIC, RTE_AP_CURRPARAMCOMP_APPL_VAR) NomRmtr_Ohm_f32);
extern FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) NtWrapC_SCom_EOLNomMtrParam_Set(Float NomKe_VpRadpS_f32, Float NomRmtr_Ohm_f32);

/* FDB5 */
extern FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_SCom_SetSTComp(Float STComp_HwNm_f32);

/* FDB6 (F000) */
extern FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_SCom_SetLTComp(Float LTComp_HwNm_f32);

/**********************************************************************************************************************
 * --- SERIAL COMM FUNCTION END ---
 *********************************************************************************************************************/

/* --- Common Manufacturing Services Selection ---
 * This block of defines control which services are to be included for the program at the time of build.
 * Unused or not defined services should be set to D_DIAGSRVC_DISABLED.
 */
/****************************** BEGIN CMS GENERATION - DO NOT CHANGE/REMOVE THIS COMMENT ******************************/
#define D_EPSDIAGSRVPID0000_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0001_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0002_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0003_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0004_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0005_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0006_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0007_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0008_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0009_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP000A_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP000B_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP000C_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP000D_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP000E_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP000F_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0010_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0011_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0012_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0013_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0014_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0015_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0016_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0017_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0018_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0019_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP001A_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP001B_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP001C_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP001D_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP001E_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP001F_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0020_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0021_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0022_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0023_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0024_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0025_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0026_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0027_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0028_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0029_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP002A_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP002B_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP002C_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP002D_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP002E_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP002F_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0030_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0031_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0032_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0033_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0034_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0035_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0036_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0037_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0038_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0039_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP003A_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP003B_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP003C_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP003D_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP003E_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP003F_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0040_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0041_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0042_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0043_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0044_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0045_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0046_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0047_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0048_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0049_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0050_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0051_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0052_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0053_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP00F0_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP00F1_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP00FF_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP0100_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0101_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0102_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0103_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0104_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0105_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0106_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0107_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0108_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP0109_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP010A_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP010B_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP010C_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP010D_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVXCP010E_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVXCP010F_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVRESET1160_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVRIDF000_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVRIDF001_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVRIDF002_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVRIDF003_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVRIDF004_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVRIDF005_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVRIDF006_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVRIDF007_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVRIDF008_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVRIDF009_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVRIDF00A_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVRIDF00B_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVRIDF00C_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVRIDF00D_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVRIDF00E_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVRIDF00F_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVRIDF0FF_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD01_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD02_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD03_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD04_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD05_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD06_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD07_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD08_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD09_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD0A_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD0B_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD0C_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVIOCFD0D_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD0E_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD0F_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD10_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVIOCFD11_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD12_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD13_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD14_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD15_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD16_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD17_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD18_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD19_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD1A_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD1B_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD1C_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD1D_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD1E_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD1F_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD20_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD21_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD22_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD23_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD24_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD25_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD26_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD27_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD28_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFD29_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD30_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD31_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFD41_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFDA0_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFDA1_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDA2_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDA3_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDA4_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFDA5_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFDA7_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFDA8_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFDA9_CNT_ENUM	D_DIAGSRVC_DISABLED
#define D_EPSDIAGSRVPIDFDAC_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDAD_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDAE_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDAF_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDB0_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDB1_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDB2_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDB3_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDB4_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDB5_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDB6_CNT_ENUM	D_DIAGSRVC_ENABLED
#define D_EPSDIAGSRVPIDFDB7_CNT_ENUM	D_DIAGSRVC_ENABLED

/* -----[ Begin XCP Variables ]----- */
#define CM_ModeMachine_StaMd_SystemState_Mode    &Rte_ModeMachine_StaMd_SystemState_Mode
#define CM_BatteryVoltage_Vecu_Volts_f32         &Rte_BatteryVoltage_Vecu_Volt_f32
#define CM_HwTrqArb_HwTrq_HwNm_f32               &Rte_DigHwTrqSENT_HwTorque_HwNm_f32
#define CM_FinalHwPos_FinHwPos_HwDeg_f32         &Rte_AbsHwPos_HandwheelPosition_HwDeg_f32
#define CM_KeFBckTyH_VpRadpS_f32                 &Rte_CurrParamComp_EstKe_VpRadpS_f32
#define CM_RFBckTyH_Ohm_f32                      &Rte_CurrParamComp_EstR_Ohm_f32
#define CM_MtrTrqLmt_MRFMtrTrqCmd_MtrNm_f32      &Rte_CtrldDisShtdn_CntDisMtrTrqCmdMRF_MtrNm_f32
#define CM_MtrPos_MRFCumMtrPos_Deg_f32           &Rte_DigMSB_CumMechMtrPosMRF_Deg_f32
#define CM_MtrVel_MRFMtrVel_MtrRadpS_f32         &Rte_MtrVel_MotorVelMRF_MtrRadpS_f32
#define CM_VehicleSpeed_VehSpd_Kph_f32           &Rte_SignlCondn_VehicleSpeed_Kph_f32
#define CM_Rte_DigHwTrq_DigHwTrq_HwNm_f32        &Rte_DigHwTrqSENT_HwTorque_HwNm_f32
#define CM_k_TbarStiff_NmpDeg_F32                &k_CmnTbarStiff_NmpDeg_f32
#define CM_T1_Trim_Volts_Digital                 &Rte_Nhet1_DigHwTrqT1_HwNm_f32
#define CM_T2_Trim_Volts_Digital                 &Rte_Nhet1_DigHwTrqT2_HwNm_f32
#define CM_HwTrq_Trim_Volts_Digital              &Rte_DigHwTrqSENT_HwTorque_HwNm_f32
#define CM_CtrlTemp_FiltMeasTemp_DegC_f32        &Rte_CtrlTemp_FiltMeasTemp_DegC_f32
#define CM_MtrTempEst_MagTempEst_DegC_f32        &Rte_MtrTempEst_MagTempEst_DegC_f32
#define CM_VltgCtrl_ModIdx_Uls_f32               &Rte_CDDInterface_ModIdxFinal_Uls_f32
#define CM_TemperatureADC_Volt_f32               &Rte_IoHwAbstractionUsr_TemperatureADC_Volt_f32
//#define CM_SrlComEngineSpeed_Rpm_f32          &Rte_SrlComInput_EngineSpeed_Rpm_f32
#define CM_MtrCurrQax_Amp_f32                    &Rte_CDDInterface_MtrCurrQax_Amp_f32
#define CM_MtrCurrDax_Amp_f32                    &Rte_CDDInterface_MtrCurrDax_Amp_f32
#define CM_Nhet1_DigHwTrqT1_HwNm_S16             &Rte_Nhet1_DigHwTrqT1_HwNm_f32
#define CM_Nhet1_DigHwTrqT2_HwNm_S16             &Rte_Nhet1_DigHwTrqT2_HwNm_f32
#define CM_DigColPs_VernDiagError_Deg_D_F32      NULL_PTR
#define CM_Rte_Cd_Nhet_DigHwTrqT1_HwNm_f32       &Rte_Nhet1_DigHwTrqT1_HwNm_f32
#define CM_Rte_Cd_Nhet_DigHwTrqT2_HwNm_f32       &Rte_Nhet1_DigHwTrqT2_HwNm_f32
#define CM_Rte_Sa_DigColPs_I2CHwAbsPos_HwDeg_f32 &Rte_Sa_DigColPs_I2CHwAbsPos_HwDeg_f32
#define CM_NvMP_Rte_TrqCanc_CogTrqCal            NvMP_Rte_TrqCanc_CogTrqCal
#define CM_NvMP_Rte_TrqCanc_CogTrqRplComp        NvMP_Rte_TrqCanc_CogTrqRplComp
#define CM_Rte_DigMSB_DigMSBEOLData              NvMP_Rte_DigMSB_DigMSBEOLData
/* -----[ End XCP Variables ]----- */

#if (D_EPSDIAGSRVRESET1160_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_StaMd_SCom_EcuReset                  StaMd_SCom_EcuReset
#endif

#if (D_EPSDIAGSRVRIDF000_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define D_F000NMEC_CNT_LGC                      TRUE
	#define D_F000IGNCNTR_CNT_LGC                   TRUE
	#define D_F000STOREDLASTPOSINVALD_CNT_LGC       TRUE
	#define D_F000LEARNEDEOT_CNT_LGC                TRUE
	#define D_F000ACTIVEPULLCOMP_CNT_LGC            TRUE
	#define D_F000NXTRDTCTBL_CNT_LGC                TRUE
	#define D_F000NXTRDTCBLACKBOX_CNT_LGC           TRUE
	#define D_F000CUSTDTCTBL_CNT_LGC                TRUE
	#define D_F000FRICTIONDETECTPARAM_CNT_LGC       TRUE
	#define D_F000INITLRNDTBLS_CNT_LGC              TRUE
	#define D_F000TRANSOVDATA_CNT_LGC               TRUE
	#define CM_Reset_LrnEOT_Scom_ResetEOT           LrnEOT_Scom_ResetEOT
	#define CM_Reset_ActivePull_SCom_SetLTComp      ActivePull_SCom_SetLTComp
	#define CM_Reset_ClearNTCs_SComm                DiagMgr_SCom_ResetNTCStatus
	#define CM_DiagMgr_SCom_ClearBlackBox           DiagMgr_SCom_ClearBlackBox
	#define CM_Reset_ClearCustDTCs_SComm            Dem_ClearDTC
	#define CM_AvgFricLrn_SCom_ResetToZero          AvgFricLrn_SCom_ResetToZero
	#define CM_AvgFricLrn_SCom_InitLearnedTables    AvgFricLrn_SCom_InitLearnedTables
	#define CM_BatteryVoltage_SCom_ClearTransOvData BatteryVoltage_SCom_ClearTransOvData
#endif

#if (D_EPSDIAGSRVRIDF001_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_ClearNTCs_SComm                      DiagMgr_SCom_ResetNTCStatus
	#define CM_DiagMgr_SCom_ClearBlackBox           DiagMgr_SCom_ClearBlackBox
	#define CM_ClearCustDTCs_SComm                  Dem_ClearDTC
#endif

#if (D_EPSDIAGSRVRIDF002_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to RID: F002 */
#endif

#if (D_EPSDIAGSRVRIDF003_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define D_F003CLRTRIMNORET_CNT_LGC              TRUE
	#define CM_HwPos_SCom_ClrHwPosTrim              NtWrapC_DigColPs_SCom_CustClrTrim
	#define D_F003DISABLELRNTRIM_CNT_LGC            TRUE
	/* --- The following are custom definitions not defined in configuration. ---
	 * They may be deprecated data or something that should be configured in the tool.
	 * Please revise and REMOVE any UNNEEDED definitions. */
	#define CM_HwPos_SCom_SetHwPosTrim              NtWrapC_DigColPs_SCom_CustSetTrim
#endif

#if (D_EPSDIAGSRVRIDF004_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define D_SENTBASEDSENSOR_CNT_LGC               TRUE
	#define CM_DigHwTrq_SCom_ClrHwTrqTrim           NtWrapC_DigHwTrqSENT_SCom_ClrTrqTrim
	#define CM_DigHwTrq_SCom_SetHwTrqTrim           NtWrapC_DigHwTrqSENT_SCom_SetTrqTrim
#endif

#if (D_EPSDIAGSRVRIDF005_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_DiagMgr_SCom_GetNTCInfo              DiagMgr_SCom_GetNTCInfo
#endif

#if (D_EPSDIAGSRVRIDF006_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to RID: F006 */
#endif

#if (D_EPSDIAGSRVRIDF007_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to RID: F007 */
#endif

#if (D_EPSDIAGSRVRIDF008_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_CmMtrCurr_SCom_CalGain               NtWrapC_CmMtrCurr_SCom_CalGain
#endif

#if (D_EPSDIAGSRVRIDF009_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_CmMtrCurr_SCom_MtrCurrOffReadStatus  CmMtrCurr_SCom_MtrCurrOffReadStatus
	#define CM_CmMtrCurr_SCom_CalOffset             NtWrapC_CmMtrCurr_SCom_CalOffset
	#define MtrCurrOffProcessFlag                   boolean
	#define D_RIDF009SVCDFTBITSSET_CNT_U16          0x301
	#define D_RIDF009SVCDFTBITSCLR_CNT_U16          (~D_RIDF009SVCDFTBITSSET_CNT_U16)
#endif

#if (D_EPSDIAGSRVRIDF00A_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to RID: F00A */
#endif

#if (D_EPSDIAGSRVRIDF00B_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to RID: F00B */
#endif

#if (D_EPSDIAGSRVRIDF00C_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to RID: F00C */
#endif

#if (D_EPSDIAGSRVRIDF00D_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to RID: F00D */
#endif

#if (D_EPSDIAGSRVRIDF00E_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define D_RIDF00ESVCDFTBITSSET_CNT_U16          0x301
#endif

#if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_k_SComTrqPosPol_Cnt_s08              k_SComTrqPosPol_Cnt_s08
#endif

#if (D_EPSDIAGSRVRIDF0FF_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_EnableTestMode_Cnt_lgc               EnableTestMode_Cnt_lgc
	#define CM_ProcessF0FF                          TWrapC_ProcessF0FF
	#define CM_WdgM_CheckpointReached               WdgM_CheckpointReached
	#define CM_DisableSysTickInterrupt              DisableSysTickInterrupt
	#define CM_EnableSysTickInterrupt               EnableSysTickInterrupt
	#define CM_GetAlarm                             GetAlarm
	#define CM_CancelAlarm                          CancelAlarm
	#define CM_SetRelAlarm                          SetRelAlarm
#endif

#if (D_EPSDIAGSRVPIDFD01_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_SwRelNum_Cnt_u08                     k_SWRelNum_Cnt_u8
	#define CM_CalRelNum_Cnt_u08                    k_CalRelNum_Cnt_u8
	#define CM_BootRelNum_Cnt_u08                   Lnk_BootRelNum_Addr
#endif

#if (D_EPSDIAGSRVPIDFD02_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_SrlComSvcDft_Cnt_b32                 CDD_EOLSrlComSvcDft_Cnt_G_b32
#endif

#if (D_EPSDIAGSRVPIDFD03_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD03 */
#endif

#if (D_EPSDIAGSRVPIDFD04_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_MtrPosCal_DataType                   MtrPosCal_DataType
	#define D_HARTBLSIZE_CNT_U16                    144
#endif

#if (D_EPSDIAGSRVPIDFD05_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD05 */
#endif

#if (D_EPSDIAGSRVPIDFD06_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD06 */
#endif

#if (D_EPSDIAGSRVPIDFD07_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define D_FD07_USE8BITPOLARITY_CNT_LGC          TRUE
	#define CM_Polarity_SCom_SetPolarity            NtWrapC_Polarity_SCom_SetPolarity
	#define CM_Polarity_SCom_ReadPolarity           Polarity_SCom_ReadPolarity
#endif

#if (D_EPSDIAGSRVPIDFD08_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD08 */
#endif

#if (D_EPSDIAGSRVPIDFD09_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD09 */
#endif

#if (D_EPSDIAGSRVPIDFD0A_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD0A */
#endif

#if (D_EPSDIAGSRVPIDFD0B_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD0B */
#endif

#if (D_EPSDIAGSRVPIDFD0C_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define D_PIDFD0CIGNORELPARAM_CNT_LGC           TRUE
#endif

#if (D_EPSDIAGSRVIOCFD0D_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_MtrTrqLmt_SCom_ManualTrqCmd          NtWrapC_AstLmt_Scom_ManualTrqCmd
#endif

#if (D_EPSDIAGSRVPIDFD0E_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_MtrTrqCmd_MtrNm_f32                  Rte_CtrldDisShtdn_CntDisMtrTrqCmdMRF_MtrNm_f32
	#define CM_CumMtrPos_Deg_f32                    Rte_DigMSB_CumMechMtrPosMRF_Deg_f32
#endif

#if (D_EPSDIAGSRVPIDFD0F_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD0F */
#endif

#if (D_EPSDIAGSRVPIDFD10_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD10 */
#endif

#if (D_EPSDIAGSRVIOCFD11_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_DFTASSTTBL_CNT_LGC                   CDD_DftAsstTbl_Cnt_G_lgc
	#define CM_DWNLDASSTGAIN_ULS_F32                CDD_DwnldAsstGain_Uls_G_f32
#endif

#if (D_EPSDIAGSRVPIDFD12_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_PhaseCurrCal_DataType                PhaseCurrCal_DataType
	#define CM_CmMtrCurr_SCom_SetMtrCurrCals        NtWrapC_CmMtrCurr_SCom_SetMtrCurrCals
	#define CM_CmMtrCurr_SCom_ReadMtrCurrCals       CmMtrCurr_SCom_ReadMtrCurrCals
#endif

#if (D_EPSDIAGSRVPIDFD13_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_DiagMgr_SCom_ReadStrgArray           DiagMgr_SCom_ReadStrgArray
	#define CM_DTCMaxStorage_Cnt_u16                15u
	#define CM_NTCStrgArray_Type                    NTCStrgArray
	#define CM_DiagMgr_SCom_GetNTCInfo              DiagMgr_SCom_GetNTCInfo
#endif

#if (D_EPSDIAGSRVPIDFD14_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_AbsHwPos_SCom_VehicleSystemStatus(ptr) *(ptr) = FPM_FloatToFixed_m(Rte_AbsHwPos_HandwheelPosition_HwDeg_f32, s11p4_T)
#endif

#if (D_EPSDIAGSRVPIDFD15_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_HwTrqTrim_Datatype                   CM_HwTrqTrim_Datatype
#endif

#if (D_EPSDIAGSRVPIDFD16_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD16 */
#endif

#if (D_EPSDIAGSRVPIDFD17_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD17 */
#endif

#if (D_EPSDIAGSRVPIDFD18_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD18 */
#endif

#if (D_EPSDIAGSRVPIDFD19_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_NxtrMEC_Cnt_G_u8                     Nvm_NMEC_Cnt_u8
#endif

#if (D_EPSDIAGSRVPIDFD1A_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_Rte_ModeType_StaMd_Mode              Rte_ModeType_StaMd_Mode
	#define CM_SystemState_Cnt_enum                 Rte_ModeMachine_StaMd_SystemState_Mode
#endif

#if (D_EPSDIAGSRVPIDFD1B_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_ManualVehSpd_SCom                    SrlComInput_SCom_ManualVehSpd
#endif

#if (D_EPSDIAGSRVPIDFD1C_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD1C */
#endif

#if (D_EPSDIAGSRVPIDFD1D_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD1D */
#endif

#if (D_EPSDIAGSRVPIDFD1E_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_MfgDiagInhibit_Cnt_lgc               MfgDiagInhibit_Uls_G_lgc
#endif

#if (D_EPSDIAGSRVPIDFD1F_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD1F */
#endif

#if (D_EPSDIAGSRVPIDFD20_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_BatteryVoltage_SCom_ReadTransOvData  BatteryVoltage_SCom_ReadTransOvData
	#define CM_BatteryVoltage_SCom_WriteTransOvData BatteryVoltage_SCom_ClearTransOvData
#endif

#if (D_EPSDIAGSRVPIDFD21_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_VehicleTune_SCom_SetSelect           DiagSvc_SCom_SetTuningSet
	#define CM_VehicleTune_SCom_GetSelect           DiagSvc_SCom_GetTuningSet
	#define D_TUNINGSETMAXLIM_CNT_U08               D_NUMOFTUNSETS_CNT_U16
#endif

#if (D_EPSDIAGSRVPIDFD22_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_TcPartNumType                        TcPartNumType
	#define D_PIDFD22STRLEN_CNT_U08                 D_TcPNArraySize_Cnt_U16
#endif

#if (D_EPSDIAGSRVPIDFD23_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_Vsm_Scom_SetOperatingMode(val)       (CDD_EnergyModeState_Cnt_G_u08 = (val))
	#define CM_Vsm_OperatingModeType                uint8
	#define CM_Rte_VehCfg_EnergyModeState_Cnt_enum  CDD_EnergyModeState_Cnt_G_u08
#endif

#if (D_EPSDIAGSRVPIDFD24_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_EOLTurnsCntrCals_Datatype            EOLTurnsCntrCals_Datatype
#endif

#if (D_EPSDIAGSRVPIDFD25_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_TrqCmdScl_SCom_Set                   NtWrapC_TrqCmdScl_SCom_Set
	#define CM_TrqCmdScl_SCom_Get                   TrqCmdScl_SCom_Get
#endif

#if (D_EPSDIAGSRVPIDFD26_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_AvgFricLrn_SCom_SetSelect            AvgFricLrn_SCom_SetSelect
	#define CM_AvgFricLrn_SCom_GetSelect            AvgFricLrn_SCom_GetSelect
#endif

#if (D_EPSDIAGSRVPIDFD27_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_AvgFricLrn_SCom_SetOffsetOutputDefeat AvgFricLrn_SCom_SetOffsetOutputDefeat
	#define CM_AvgFricLrn_SCom_GetOffsetOutputDefeat AvgFricLrn_SCom_GetOffsetOutputDefeat
#endif

#if (D_EPSDIAGSRVPIDFD28_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD28 */
#endif

#if (D_EPSDIAGSRVPIDFD29_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_AvgFricLrn_SCom_SetEOLFric           AvgFricLrn_SCom_SetEOLFric
	#define CM_AvgFricLrn_SCom_GetEOLFric           AvgFricLrn_SCom_GetEOLFric
#endif

#if (D_EPSDIAGSRVPIDFD30_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_DigHwTrqSENT_SCom_ReadTrim           DigHwTrqSENT_SCom_TrimData
	#define CM_DigHwTrqSENT_SCom_WriteTrim          NtWrapC_DigHwTrqSENT_SCom_WriteData
#endif

#if (D_EPSDIAGSRVPIDFD31_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_Rte_Sa_DigHwTrqSENT_HwTorque_HwNm_f32 Rte_DigHwTrqSENT_HwTorque_HwNm_f32
	#define CM_Rte_Cd_Nhet1_DigHwTrqT1_HwNm_f32     Rte_Nhet1_DigHwTrqT1_HwNm_f32
	#define CM_Rte_Cd_Nhet1_DigHwTrqT2_HwNm_f32     Rte_Nhet1_DigHwTrqT2_HwNm_f32
#endif

#if (D_EPSDIAGSRVPIDFD41_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD41 */
#endif

#if (D_EPSDIAGSRVPIDFDA0_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDA0 */
#endif

#if (D_EPSDIAGSRVPIDFDA1_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_ECUSerialNumber                      Nvm_EcuSrlNum_Cnt_u8
#endif

#if (D_EPSDIAGSRVPIDFDA2_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_EPSSerialNumber                      Nvm_EpsSrlNum_Cnt_u8
#endif

#if (D_EPSDIAGSRVPIDFDA3_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_ECUHardwarePN                        Nvm_EcuHwPn_Cnt_u8
#endif

#if (D_EPSDIAGSRVPIDFDA4_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDA4 */
#endif

#if (D_EPSDIAGSRVPIDFDA5_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_ShCurrCal_DataType                   ShCurrCal_DataType
#endif

#if (D_EPSDIAGSRVPIDFDA7_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_HwPosRelCal_DataType                 HwPosRelCal_DataType
#endif

#if (D_EPSDIAGSRVPIDFDA8_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDA8 */
#endif

#if (D_EPSDIAGSRVPIDFDA9_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDA9 */
#endif

#if (D_EPSDIAGSRVPIDFDAC_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_MfgScratchPad_Cnt_G_u8               Nvm_NxtrManfScrpd_Cnt_u8
#endif

#if (D_EPSDIAGSRVPIDFDAD_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_ActivePull_SCom_ReadParam            ActivePull_SCom_ReadParam
#endif

#if (D_EPSDIAGSRVPIDFDAE_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDAE */
#endif

#if (D_EPSDIAGSRVPIDFDAF_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define D_ENABLEGENERICPARAMS_CNT_LGC           TRUE
#endif

#if (D_EPSDIAGSRVPIDFDB0_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_IPMCoggingCancTrq                    CoggingCancTrq
	#define CM_IPMTrqCanc_Scom_SetCogTrqCal         NtWrapC_TrqCanc_Scom_SetCogTrqCal
	#define CM_IPMTrqCanc_Scom_ReadCogTrqCal        TrqCanc_Scom_ReadCogTrqCal
#endif

#if (D_EPSDIAGSRVPIDFDB1_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDB1 */
#endif

#if (D_EPSDIAGSRVPIDFDB2_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDB2 */
#endif

#if (D_EPSDIAGSRVPIDFDB3_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDB3 */
#endif

#if (D_EPSDIAGSRVPIDFDB4_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define D_RANDKESUPPORTONLY_CNT_LGC             TRUE
	#define CM_SCom_EOLNomMtrParam_Set_FDB4         NtWrapC_SCom_EOLNomMtrParam_Set
	#define CM_SCom_EOLNomMtrParam_Get_FDB4         SCom_EOLNomMtrParam_Get
#endif

#if (D_EPSDIAGSRVPIDFDB5_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_ActivePull_SCom_SetSTComp            ActivePull_SCom_SetSTComp
#endif

#if (D_EPSDIAGSRVPIDFDB6_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define CM_ActivePull_SCom_SetLTComp            ActivePull_SCom_SetLTComp
#endif

#if (D_EPSDIAGSRVPIDFDB7_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDB7 */
#endif

/******************************* END CMS GENERATION - DO NOT CHANGE/REMOVE THIS COMMENT *******************************/


#endif /* EPS_DIAGSRVCS_ISO_INTERFACE_H */
