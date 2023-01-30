/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : CalConstants.h
* Module Description: This file contains the declarations of calibration 
*                     constants used in the EPS Software.
* Product           : Gen II Plus EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          EA3#12 %
 * %derived_by:       nzdx8v %
 * %date_modified:    Fri Dec 13 12:52:16 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 */

#ifndef CALCONSTANTS_H
#define CALCONSTANTS_H

#include "Rte_Type.h"
#include "fixmath.h"
#include "filters.h"
#include "Ap_DiagMgr_Types.h"
#include "Metrics.h"

#define D_NUMOFTUNSETS_CNT_U16 	8U
#define D_NUMOFPERS_CNT_U16 	2U

/* Put this at end of file
extern P2CONST(TUNING_P_Str, AUTOMATIC, AUTOMATIC) TunPer_Ptr_Str;
extern P2CONST(TUNING_Y_Str, AUTOMATIC, AUTOMATIC) TunSet_Ptr_Str;
extern CONSTP2CONST(TUNING_P_Str, AUTOMATIC, AUTOMATIC) T_TunPersSelectionTbl_Ptr_Str[D_NUMOFTUNSETS_CNT_U16][D_NUMOFPERS_CNT_U16];
extern CONSTP2CONST(TUNING_Y_Str, AUTOMATIC, AUTOMATIC) T_TunSetSelectionTbl_Ptr_Str[D_NUMOFTUNSETS_CNT_U16];
*/
/* Manually removed the macro for the k_CalID_Cnt_u16. This was required because the tuning sets/personalities needed to be
 * looped through to find the correct offset for the tuning set and personalities. *//* <- Remove this extra comment
#ifdef k_CalID_Cnt_u16
	#undef k_CalID_Cnt_u16
#endif
*/
/*********************** Start of Auto Generated Code ************************/

/****************** File Generated on 10/5/2016 1:15:28 PM *******************/
/***************************** Fiasa 327- Rev 8 ******************************/



/************* Tuning Structure Definition for "Y" Calibrations **************/

typedef struct
{
	float32	k_KinmIntDiagMaxRackLimit_HwDeg_f32;
	float32	k_EnableHwAuthMin_Uls_f32;
	float32	k_EnableHwPosMax_HwDeg_f32;
	float32	k_EnableHwTrqMax_HwNm_f32;
	float32	k_EnableHwVelMax_DegpS_f32;
	uint32	k_EnableTime_mS_u32;
	float32	k_EnableVehSpdMax_Kph_f32;
	float32	k_EnableVehSpdMin_Kph_f32;
	float32	k_EnableVehSpdRateMax_KphpS_f32;
	float32	k_EnableYawRateMax_DegpS_f32;
	float32	k_FiltDeadband_HwNm_f32;
	float32	k_HwNmToMtrNm_Uls_f32;
	float32	k_HwTrqFilt_Hz_f32;
	float32	k_LTFilt_Hz_f32;
	float32	k_LTIntInputLimit_HwNm_f32;
	float32	k_LTLearnTime_Min_f32;
	float32	k_LTLimit_HwNm_f32;
	float32	k_OutputMaxRate_HwNmpS_f32;
	float32	k_STFilt_Hz_f32;
	float32	k_STIntInputLimit_HwNm_f32;
	float32	k_STLearnTimeDec_Sec_f32;
	float32	k_STLearnTimeInc_Sec_f32;
	float32	k_STLimit_HwNm_f32;
	uint32	k_STOppSignTime_mS_u32;
	float32	k_STRampTime_Sec_f32;
	float32	k_STResetHwPos_HwDeg_f32;
	float32	k_STResetHwTrq_HwNm_f32;
	float32	k_STResetYawRate_DegpS_f32;
	float32	k_TotalLimit_HwNm_f32;
	float32	k_YawRateFilt_Hz_f32;
	uint16	t_VehSpdScaleTblX_Kph_u9p7[4];
	uint16	t_VehSpdScaleTblY_Uls_u2p14[4];
	uint16	t_CmnVehSpd_Kph_u9p7[12];
	float32	k_AsstFWFiltKn_Hz_f32;
	float32	k_AsstFWFWActiveLPF_Hz_f32;
	float32	k_AsstFWInpLimitBaseAsst_MtrNm_f32;
	float32	k_AsstFWInpLimitHFA_MtrNm_f32;
	uint16	k_AsstFWNstep_Cnt_u16;
	uint16	k_AsstFWPstep_Cnt_u16;
	float32	k_RestoreThresh_MtrNm_f32;
	uint16	t_AsstFWDefltAssistX_HwNm_u8p8[20];
	sint16	t_AsstFWDefltAssistY_MtrNm_s4p11[20];
	uint16	t_AsstFWPstepNstepThresh_Cnt_u16[2];
	uint16	t_AsstFWVehSpd_Kph_u9p7[8];
	sint16	t2_AsstFWUprBoundX_HwNm_s4p11[8][11];
	sint16	t2_AsstFWUprBoundY_MtrNm_s4p11[8][11];
	float32	k_AvgFricLPFKn_Hz_f32;
	float32	k_BaselineEOLFric_HwNm_f32;
	float32	k_DataPrepLPFKn_Hz_f32;
	float32	k_EOLFricDiffLimitHigh_HwNm_f32;
	float32	k_EOLFricDiffLimitLow_HwNm_f32;
	float32	k_EOLFricDiffScalingFactor_Uls_f32;
	float32	k_FricOffsetLimitHigh_HwNm_f32;
	float32	k_FricOffsetLimitLow_HwNm_f32;
	float32	k_FricOffsetLPFKn_Hz_f32;
	float32	k_FrictionDiagThreshold_HwNm_f32;
	uint32	k_FrictionDiagTimer_mS_u32;
	float32	k_HwPosAuthMin_Uls_f32;
	float32	k_HwVelConstLimit_HwDegpS_f32;
	float32	k_HwVelMax_HwDegpS_f32;
	float32	k_HwVelMin_HwDegpS_f32;
	float32	k_IgnCycleFricChgLim_HwNm_f32;
	float32	k_LatAccMax_MpSecSqrd_f32;
	float32	k_LatAccMin_MpSecSqrd_f32;
	float32	k_LearningGain_Uls_f32;
	uint32	k_LearningThreshold_Cnt_u32;
	uint16	k_RangeCounterLimit_Cnt_u16;
	float32	k_SatFricChgLim_HwNm_f32;
	float32	k_TempMax_DegC_f32;
	float32	k_TempMin_DegC_f32;
	float32	t_BaselineFric_HwNm_f32[4];
	float32	t_FrHystHwAPts_HwDeg_f32[4];
	float32	t_FricChgWeight_Uls_f32[4];
	uint16	t_InvRatioX_HwDeg_u11p5[10];
	uint16	t_InvRatioY_HwNmpMtrNm_u6p10[10];
	boolean	t_MskVehSpd_Cnt_lgc[4];
	uint16	t2_BaselineRangeCounter_Cnt_u16[8][3];
	float32	t2_BaselineTheta_HwNm_f32[8][4];
	float32	t2_VehSpd_Kph_f32[4][2];
	sint16	t_TempScaleX_DegC_s8p7[11];
	uint16	t_TempScaleY_Uls_u4p12[11];
	float32	k_DampFWErrThresh_MtrNm_f32;
	float32	k_DampFWFWActiveLPF_Hz_f32;
	uint16	k_DampFWInCmpNStep_Cnt_u16;
	uint16	k_DampFWInCmpPStep_Cnt_u16;
	float32	k_DampFWInpLimitDamp_MtrNm_f32;
	uint16	k_DampFWNstep_Cnt_u16;
	uint16	k_DampFWPstep_Cnt_u16;
	float32	k_DmpBoundLPFKn_Hz_f32;
	uint16	t_DampFWAddDampAFWX_MtrRadpS_u11p5[8];
	uint16	t_DampFWAddDampAFWY_MtrNm_u5p11[8];
	uint16	t_DampFWAddDampDFWX_MtrRadpS_u11p5[8];
	uint16	t_DampFWAddDampDFWY_MtrNm_u5p11[8];
	uint16	t_DampFWDampInrtCmpPNThesh_Cnt_u16[2];
	uint16	t_DampFWPNstepThresh_Cnt_u16[2];
	sint16	t_DampFWUprBoundX_MtrRadpS_s11p4[11];
	uint16	t_DampFWVehSpd_Kph_u9p7[8];
	sint16	t2_DampFWUprBoundY_MtrNm_s7p8[8][11];
	float32	k_DmpDecelGain_Uls_f32;
	float32	k_DmpDecelGainFSlew_UlspS_f32;
	float32	k_DmpGainOffThresh_KphpS_f32;
	float32	k_DmpGainOnThresh_KphpS_f32;
	float32	k_InrtCmp_MtrInertia_KgmSq_f32;
	float32	k_InrtCmp_TBarVelLPFKn_Hz_f32;
	uint16	k_MaxRackTrvl_HwDeg_u12p4;
	uint16	k_MinRackTrvl_HwDeg_u12p4;
	float32	k_CmnSysTrqRatio_HwNmpMtrNm_f32;
	float32	k_HysCmpHwTrqLPFKn_Hz_f32;
	float32	k_HysCmpLPAstLPFKn_Hz_f32;
	float32	k_HysFinalOutLPFKn_Hz_f32;
	float32	k_HysOutLIm_HwNm_f32;
	float32	k_HysRevGain_InvHwNm_f32;
	uint16	k_LpFricIpLim_HwNm_u9p7;
	uint16	t_EffLossTblY_Uls_u4p12[12];
	uint16	t_EffOffTblY_HwNm_u9p7[12];
	sint16	t_HysCompCoulFricTempScaleX_DegC_s14p1[8];
	uint16	t_HysCompCoulFricTempScaleY_HwNm_u9p7[8];
	uint16	t_HysCompCoulFricWIRBlendX_MtrNm_u8p8[6];
	uint16	t_HysCompCoulFricWIRBlendY_Uls_u2p14[6];
	uint16	t_HysCompCoulFricY_HwNm_u9p7[2][12];
	uint16	t_HysCompHysSatY_HwNm_u9p7[12];
	uint16	t_HysCompNegHysBlendX_HwNm_u9p7[5];
	uint16	t_HysCompNegHysBlendY_Uls_u2p14[5];
	uint16	t_HysCompNegHysCompX_MtrNm_u8p8[8];
	uint16	t_HysCompNegHysCompY_HwNm_u9p7[8];
	uint16	t_HysRiseTblX_HwNm_u2p14[6];
	uint16	t_HysRiseTblY_Uls_u2p14[6];
	uint16	t2_HysHwTrqBlndTblX_HwNm_u4p12[12][8];
	uint16	t2_HysHwTrqBlndTblY_Uls_u4p12[12][8];
	float32	k_AuthorityStartLrn_Uls_f32;
	uint16	k_EOTLrnTimer_mS_u16;
	float32	k_HwTrqEOTLrn_HwNm_f32;
	float32	k_MaxRackTrvl_HwDeg_f32;
	float32	k_MinRackTrvl_HwDeg_f32;
	float32	k_MinResetAuthority_Uls_f32;
	float32	k_MtrVelEOTLrn_MtrRadpS_f32;
	uint16	t_ReturnTempScaleSclYTbl_Uls_u8p8[14];
	sint16	t_ReturnTempScaleXTbl_DegC_s11p4[14];
	sint16	t_RtrnFWUprBoundX_HwDeg_s11p4[11];
	uint16	t_RtrnFWVehSpd_Kph_u9p7[8];
	sint16	t2_RtrnFWUprBoundY_MtrNm_s4p11[8][11];
	boolean	k_StCmpCrosChkEnbl_Uls_lgc;
	float32	k_StCmpHwTrqLPFKn_Hz_f32;
	float32	k_StCmpSysCorrThresh_MtrNm_f32;
	NotchFiltK_Str	t_StCmpNFK_Str[4];
	DiagSettings_Str	k_TmprlMonPstepNstep_Cnt_str;
	float32	k_SysKinRatio_MtrDegpHwDeg_f32;

} TUNING_Y_Str;

/************* Tuning Structure Definition for "P" Calibrations **************/

typedef struct
{
	sint16	t2_AsstAsstY0_MtrNm_s4p11[12][20];
	sint16	t2_AsstAsstY1_MtrNm_s4p11[12][20];
	uint16	t2_AsstHwtX0_HwNm_u8p8[12][20];
	uint16	t2_AsstHwtX1_HwNm_u8p8[12][20];
	uint16	t2_AsstWIRBlendY_Uls_u2p14[12][5];
	uint16	t2_AsstWIRBlndX_MtrNm_u5p11[12][5];
	float32	k_HPSOutLimit_MtrNm_f32;
	float32	k_MtrVelDampLPFKn_Hz_f32;
	float32	k_QddHwTrqDampKn_Hz_f32;
	float32	k_QDDMtrVelBckLash_MtrRadpS_f32;
	float32	k_QddMtrVelDampKn_Hz_f32;
	float32	k_QddSfLFPKn_Hz_f32;
	float32	k_Quad13DmpMult_Uls_f32;
	float32	k_Quad24DmpMult_Uls_f32;
	uint16	t_HPSAsstLimY_MtrNm_u4p12[12];
	uint16	t_HPSscaleC1Y_Uls_u4p12[12];
	uint16	t_HPSscaleC2Y_Uls_u4p12[12];
	uint16	t_HPSscaleC3Y_Uls_u4p12[12];
	uint16	t_HPSscaleC4Y_Uls_u4p12[12];
	uint16	t_HwTrqDmpTblX_HwNm_u8p8[2];
	uint16	t_HwTrqDmpTblY_Uls_u1p15[2];
	uint16	t2_MtrVelDmpTblX_MtrRadpS_u12p4[12][13];
	uint16	t2_MtrVelDmpTblY_MtrNm_u5p11[12][13];
	float32	k_InrtCmp_MtrVel_ScaleFactor_Uls_f32;
	uint16	t_DmpADDCoefX_MtrNm_u4p12[10];
	uint16	t_DmpDecelGainSlewX_MtrRadpS_u11p5[6];
	uint16	t_DmpDecelGainSlewY_UlspS_u13p3[6];
	uint16	t_DmpFiltKpWIRBlndY_Uls_u2p14[5];
	uint16	t_FDD_ADDStaticTblY_MtrNmpRadpS_um1p17[10];
	uint16	t_FDD_AttenTblX_MtrRadpS_u12p4[2];
	uint16	t_FDD_AttenTblY_Uls_u8p8[2];
	uint16	t_FDD_BlendTblY_Uls_u8p8[12];
	uint16	t_InrtCmp_ScaleFactorTblY_Uls_u9p7[12];
	uint16	t_InrtCmp_TBarVel_ScaleFactorTblY_Uls_u9p7[12];
	uint16	t_RIAstWIRBlndTblY_Uls_u2p14[5];
	uint16	t_WIRBlndTblX_MtrNm_u8p8[5];
	uint16	t2_FDD_ADDRollingTblYM_MtrNmpRadpS_um1p17[2][10];
	uint16	t2_FDD_FreqTblYM_Hz_u12p4[2][12];
	uint16	k_EOTDefltPosition_HwDeg_u12p4;
	uint16	k_EOTDeltaTrqThrsh_HwNm_u9p7;
	uint16	k_EOTEnterLPFKn_Cnt_u16;
	uint16	k_EOTExitLPFKn_Cnt_u16;
	uint16	k_EOTImpSpdEn_Kph_u9p7;
	boolean	k_EOTOriginalImpactandSoftEnd_Cnt_lgc;
	float32	k_EOTPosDepDempFinalSlew_MtrNmpS_T_f32;
	uint16	k_EOTStateHwTrqLPFKn_Cnt_u16;
	uint16	k_PosRampStep_HwDeg_u12p4;
	Boolean	k_SoftStopEOTEnable_Cnt_lgc;
	uint16	k_SpdIptScale_MtrNmpRadpS_u4p12;
	uint16	t_EOTDmpVspd_Kph_u9p7[4];
	uint16	t_EOTEnterGainVspd_Kph_u9p7[4];
	uint16	t_SpdIptTblXTbl_HwDeg_u12p4[2];
	uint16	t_SpdIptTblYTbl_MtrRadpS_u12p4[2];
	uint16	t_TrqTableX_HwNm_u8p8[2];
	uint16	t2_EOTEnterGainX_HwDeg_u12p4[4][4];
	uint16	t2_EOTEnterGainY_Uls_u1p15[4][4];
	uint16	t2_EOTExPosDepDmpTblY_MtrNmpRadps_u0p16[4][2];
	uint16	t2_EOTPosDepDmpTblY_MtrNmpRadpS_u0p16[4][2];
	uint16	t2_EOTPosDepDmpTblX_HwDeg_u12p4[4][2];
	uint16	t_LPFKnY_Hz_u7p9[12];
	uint16	t2_GainY0_MtrNmpHwNm_u3p13[12][13];
	uint16	t2_GainY1_MtrNmpHwNm_u3p13[12][13];
	uint16	t2_TorqX0_HwNm_u5p11[12][13];
	uint16	t2_TorqX1_HwNm_u5p11[12][13];
	uint16	t2_WIRBlendX_MtrNm_u4p12[12][5];
	uint16	t2_WIRBlendY_Uls_u1p15[12][5];
	uint16	t_HWAuthRetScl_X_Uls_u8p8[4];
	uint16	t_HWAuthRetScl_Y_Uls_u9p7[4];
	uint16	t_ReturnVSpdTblBS_Kph_u9p7[9];
	uint16	t2_ReturnPosTblXM_HwDeg_u12p4[9][16];
	uint16	t2_ReturnPosTblYM_MtrNm_u5p11[9][16];
	uint16	t2_ReturnSclTrqTblXM_HwNm_T_u8p8[9][8];
	uint16	t2_ReturnSclTrqTblYM_Uls_u8p8[9][8];
	uint16	t2_ReturnSclVelTblXM_HwRadpS_T_u7p9[9][4];
	uint16	t2_ReturnSclVelTblYM_Uls_u8p8[9][4];
	uint16	t_StCmpADDFBlendX_Uls_u2p14[2];
	uint16	t_StCmpADDFBlendY_Uls_u2p14[2];
	uint16	t_StCmpBlend12Trq_HwNm_u8p8[5];
	uint16	t_StCmpBlend34Trq_HwNm_u8p8[5];
	uint16	t_StCmpBlendSpdBS_Kph_u9p7[6];
	uint16	t2_StCmpBlend02TblY_Uls_u2p14[6][5];
	uint16	t2_StCmpBlend04TblY_Uls_u2p14[6][5];
	uint16	t2_StCmpBlend12TblY_Uls_u2p14[6][5];
	uint16	t2_StCmpBlend34TblY_Uls_u2p14[6][5];

} TUNING_P_Str;


/***************************** AbsHwPos_TcI2cVd ******************************/
extern CONST(float32, CAL_CONST) k_HWAtoMtrADiffLimit_HwDeg_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_HwAtoMtrAError_str;
extern CONST(float32, CAL_CONST) k_HwPosAuthorityStep_Uls_f32;
extern CONST(float32, CAL_CONST) k_HwPosOutputLPFCoeffFc_Hz_f32;
extern CONST(float32, CAL_CONST) k_HwPosOutputLPFError_HwDeg_f32;
extern CONST(float32, CAL_CONST) k_I2CHwAuthority_Uls_f32;
extern CONST(float32, CAL_CONST) k_MaxSensorlessAuthority_Uls_f32;
extern CONST(float32, CAL_CONST) k_MaxVehCntrOffDiff_HwDeg_f32;
extern CONST(float32, CAL_CONST) k_MinSensorlessAuthority_Uls_f32;
extern CONST(float32, CAL_CONST) k_TurnsCntrAuthority_Uls_f32;
extern CONST(boolean, CAL_CONST) k_UseTurnsCntr_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_VehCntrOffValidLimit_HwDeg_f32;

/************************************ Adc ************************************/
extern CONST(uint16, CAL_CONST) k_MaxADCConvTime_uS_u16;
extern CONST(uint32, CAL_CONST) k_VbattOVTransIntConfig_Cnt_u32;

/********************************** Assist ***********************************/
extern CONST(uint16, CAL_CONST) t_AsstThermSclX_Cnt_u16p0[2];
extern CONST(uint16, CAL_CONST) t_AsstThermSclY_Uls_u2p14[2];

/****************************** AssistFirewall *******************************/
extern CONST(float32, CAL_CONST) k_AsstFWInpLimitHysComp_MtrNm_f32;

/********************************* AstLmt_CM *********************************/
extern CONST(float32, CAL_CONST) k_SumLimPlCmpLimit_MtrNm_f32;

/****************************** BatteryVoltage *******************************/
extern CONST(float32, CAL_CONST) k_MaxBattVoltDiff_Volts_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_VecuCorrLim_Cnt_Str;
extern CONST(float32, CAL_CONST) k_VecuVbatCorrLim_Volts_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_VswitchCorrLim_Cnt_Str;
extern CONST(float32, CAL_CONST) k_VswitchCorrLim_Volts_f32;

/************************** BatteryVoltage, BkCpPc ***************************/
extern CONST(float32, CAL_CONST) k_MaxSwitchedVolt_Volts_f32;

/********************************** BkCpPc ***********************************/
extern CONST(float32, CAL_CONST) k_ChargeMinDeltaExtOp_Volt_f32;
extern CONST(float32, CAL_CONST) k_ChargeMinDeltaNonOp_Volt_f32;
extern CONST(float32, CAL_CONST) k_ChargeMinDeltaNormlOp_Volt_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_ChargePumpDiag_Cnt_str;
extern CONST(float32, CAL_CONST) k_MaxDischEst_Uls_f32;
extern CONST(float32, CAL_CONST) k_MinDischEst_Uls_f32;
extern CONST(float32, CAL_CONST) k_MtrMotionThresh_MtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_OVERRIDESIGDIAGOpenThresh_Volts_f32;
extern CONST(float32, CAL_CONST) k_PMOSDIAGOpenThresh_Volts_f32;
extern CONST(uint16, CAL_CONST) k_PMOSTError_mS_u16;
extern CONST(float32, CAL_CONST) k_PMOSVError_Volts_f32;
extern CONST(uint16, CAL_CONST) k_PrechargeThresh_mS_u16;
extern CONST(float32, CAL_CONST) k_PwrDiscCloseThresh_Volts_f32;
extern CONST(float32, CAL_CONST) k_PwrDiscOpenThresh_Volts_f32;
extern CONST(float32, CAL_CONST) k_VbattSwitchThreshExNorm_Volt_f32;
extern CONST(float32, CAL_CONST) k_VbattSwitchThreshNonExt_Volt_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_VerifyPwrDiscCloseDiag_Cnt_str;
extern CONST(uint16, CAL_CONST) k_VerifyPwrDiscCloseThresh_mS_u16;
extern CONST(uint16, CAL_CONST) k_VerifyPwrDiscOpenThresh_mS_u16;
extern CONST(float32, CAL_CONST) k_VswitchDeltaThresh_Volts_f32;
extern CONST(uint16, CAL_CONST) k_WaitForSqrWaveThresh_mS_u16;

/********************************** BVDiag ***********************************/
extern CONST(uint16, CAL_CONST) k_BattDiagUvMax_Volt_u10p6;
extern CONST(uint16, CAL_CONST) k_BattDiagUvMin_Volt_u10p6;
extern CONST(uint16, CAL_CONST) k_BattUvRecMax_Volt_u10p6;
extern CONST(uint16, CAL_CONST) k_LowDetect_ms_u16p0;
extern CONST(uint16, CAL_CONST) k_LowDetect_Volts_u10p6;
extern CONST(uint16, CAL_CONST) k_LowNotDetect_ms_u16p0;
extern CONST(uint16, CAL_CONST) k_LowNotDetect_Volts_u10p6;
extern CONST(uint16, CAL_CONST) k_MSALowDetect_ms_u16p0;
extern CONST(uint16, CAL_CONST) k_MSALowDetect_Volts_u10p6;
extern CONST(uint16, CAL_CONST) k_MSALowNotDetect_ms_u16p0;
extern CONST(uint16, CAL_CONST) k_MSALowNotDetect_Volts_u10p6;
extern CONST(uint16, CAL_CONST) k_OvDetect_ms_u16p0;
extern CONST(uint16, CAL_CONST) k_OvDetect_Volts_u10p6;
extern CONST(uint16, CAL_CONST) k_OvNotDetect_ms_u16p0;
extern CONST(uint16, CAL_CONST) k_OvNotDetect_Volts_u10p6;
extern CONST(uint16, CAL_CONST) k_UvDetect_ms_u16p0;
extern CONST(uint16, CAL_CONST) k_UvNotDetect_ms_u16p0;

/********************************* CmMtrCurr *********************************/
extern CONST(float32, CAL_CONST) k_CurrCorrErrFiltFc_Hz_f32;
extern CONST(float32, CAL_CONST) k_CurrCorrErrThresh_Amps_f32;
extern CONST(float32, CAL_CONST) k_CurrGainNumerator_Amps_f32;
extern CONST(uint16, CAL_CONST) k_CurrOffGainKn_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_CurrOffNoofAvg_Cnt_u16;
extern CONST(float32, CAL_CONST) k_MaxCurrOffMtrVel_RadpS_f32;
extern CONST(float32, CAL_CONST) k_MtrCurrEOLMaxGain_AmpspVolts_f32;
extern CONST(float32, CAL_CONST) k_MtrCurrEOLMaxOffset_Volts_f32;
extern CONST(float32, CAL_CONST) k_MtrCurrEOLMinGain_AmpspVolts_f32;
extern CONST(float32, CAL_CONST) k_MtrCurrEOLMinOffset_Volts_f32;
extern CONST(uint16, CAL_CONST) k_MtrCurrOffLoComOff_Cnt_u16;
extern CONST(float32, CAL_CONST) k_MtrPosComputDelay_Sec_f32;

/******************************** CMS_Common *********************************/
extern CONST(sint8, CAL_CONST) k_CMSGotoPosPol_Cnt_s08;
extern CONST(float32, CAL_CONST) k_F00FHandsOnThres_HwNm_f32;
extern CONST(uint16, CAL_CONST) k_NxtrSrvcHandsOnTime_mS_u16;
extern CONST(uint16, CAL_CONST) k_NxtrSrvcPosTrajHoldTime_mS_u16;
extern CONST(float32, CAL_CONST) k_NxtrSrvcPosTrajThres_HwDeg_f32;

/********************************* CMS_Fiasa *********************************/
extern CONST(uint8, CAL_CONST) k_CalRelNum_Cnt_u8[12];
extern CONST(float32, CAL_CONST) k_SrvcHwTrqLimit_HwNm_f32;
extern CONST(float32, CAL_CONST) k_SrvcVehSpdLimit_Kph_f32;

/********************************* ComplErr **********************************/
extern CONST(uint16, CAL_CONST) t_CompErrMtrPosNonLinComplDepTbl_HwDegpMtrNm_u8p8[6];
extern CONST(uint16, CAL_CONST) t_ComplErrMtrPosNonLinComplIndTbl_MtrNm_u5p11[6];

/******************************* CtrldDisShtdn *******************************/
extern CONST(uint16, CAL_CONST) k_CntrlDmpRampEnd_Uls_u8p8;
extern CONST(uint16, CAL_CONST) k_CtrlDmpTmrBkptOne_mS_u16;
extern CONST(uint16, CAL_CONST) k_CtrlDmpTmrBkptTwo_mS_u16;
extern CONST(float32, CAL_CONST) k_CtrlDpVelThr_MtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_F2Damping_MtrNmpRadpS_f32;
extern CONST(float32, CAL_CONST) k_MaxCtrlDmpLimit_MtrNm_f32;

/********************************* CtrlTemp **********************************/
extern CONST(boolean, CAL_CONST) k_CustDiagAmbLowEnable_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_CustDiagAmbLowThresh_DegC_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_TempSensDiag_Cnt_str;
extern CONST(float32, CAL_CONST) k_TempSensHighLimit_DegC_f32;
extern CONST(float32, CAL_CONST) k_TempSensLowLimit_DegC_f32;
extern CONST(float32, CAL_CONST) k_TempSnsrDefVal_DegC_f32;
extern CONST(boolean, CAL_CONST) k_TempSnsrFiltDft_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_TempSnsrLPFKn_Hz_f32;
extern CONST(float32, CAL_CONST) k_TempSnsrOffset_Volts_f32;
extern CONST(float32, CAL_CONST) k_TempSnsrScaling_DegpVolt_f32;

/********************************** Damping **********************************/
extern CONST(float32, CAL_CONST) k_HPSbaseC1_MtrNmpMtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_HPSbaseC2_MtrNmpMtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_HPSbaseC3_MtrNmpMtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_HPSbaseC4_MtrNmpMtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_QDDHwTrqBckLash_HwNm_f32;

/****************************** DampingFirewall ******************************/
extern CONST(float32, CAL_CONST) k_DampFWVBICLPF_Hz_f32;
extern CONST(uint16, CAL_CONST) t_DampFWDefltDampX_MtrRadpS_u11p5[11];
extern CONST(uint16, CAL_CONST) t_DampFWDefltDampY_MtrNm_u5p11[11];

/******************** FrqDepDmpnInrtCmp, DampingFirewall *********************/
extern CONST(float32, CAL_CONST) k_CmnSysKinRatio_MtrDegpHwDeg_f32;
extern CONST(float32, CAL_CONST) k_CmnTbarStiff_NmpDeg_f32;

/********************************** DiagMgr **********************************/
extern CONST(float32, CAL_CONST) k_FltRmpRate_UlspmS_f32[13];
extern CONST(FltRsp_Str, CAL_CONST) k_FltRspTbl_Cnt_str[512];
extern CONST(uint32* const, CAL_CONST) t_BlkBoxGrp_Ptr_u32[7][3];
extern CONST(NTCLatch_Str, CAL_CONST) t_LatchFaults_Cnt_str[8];
extern CONST(NTCNumber, CAL_CONST) t_SortedNTCs_Cnt_enum[256];

/********************************** DiagSvc **********************************/
extern CONST(float32, CAL_CONST) k_HwTrqResetThresh_Kph_f32;
extern CONST(float32, CAL_CONST) k_VehSpdResetThresh_Kph_f32;
extern CONST(uint8, CAL_CONST) k_ProxiConfigTunSet_Cnt_u08[8][3];

/******************************* DigHwTrqSENT ********************************/
extern CONST(float32, CAL_CONST) k_CMCLPFOutLim_HwNm_f32;
extern CONST(float32, CAL_CONST) k_HwTrqLPFFc_Hz_f32;
extern CONST(float32, CAL_CONST) k_MaxHwTrqTrim_HwNm_f32;
extern CONST(float32, CAL_CONST) k_T1T2CMCLPFEnable_HwNm_f32;
extern CONST(float32, CAL_CONST) k_T1T2CMCLPFFc_Hz_f32;
extern CONST(float32, CAL_CONST) k_T1T2SSLim_HwNm_f32;
extern CONST(float32, CAL_CONST) k_T1T2SSLPFFc_Hz_f32;
extern CONST(float32, CAL_CONST) k_T1T2TransFltLim_HwNm_f32;
extern CONST(float32, CAL_CONST) k_T1vsT2TrqSum_HwNm_f32;
extern CONST(uint16, CAL_CONST) t_T1T2DepTrsTimecon_Hz_u6p10[17];
extern CONST(uint16, CAL_CONST) t_T1T2IndTrsTimecon_HwNm_u5p11[17];

/********************************** DigMSB ***********************************/
extern CONST(uint8, CAL_CONST) k_Die1RPMMode_Cnt_u08;
extern CONST(float32, CAL_CONST) k_Die1vsDie2TrnsCntrThresh_Deg_f32;
extern CONST(uint16, CAL_CONST) k_Die2Offset_Rev_u3p13;
extern CONST(uint8, CAL_CONST) k_Die2RPMMode_Cnt_u08;
extern CONST(uint8, CAL_CONST) k_DigMSBErrorRegGenMask_Cnt_u08;
extern CONST(DiagSettings_Str, CAL_CONST) k_DigMSBParity_Cnt_str;
extern CONST(DiagSettings_Str, CAL_CONST) k_DigMSBTCRunTimeParity_Cnt_str;
extern CONST(DiagSettings_Str, CAL_CONST) k_ErrorRegTCAcc_Cnt_str;
extern CONST(uint8, CAL_CONST) k_ErrorRegTCMask_Cnt_u08;
extern CONST(uint8, CAL_CONST) k_ErrorRegVehMask_Cnt_u08;
extern CONST(DiagSettings_Str, CAL_CONST) k_MtrPos1vsMtrPos2Diag_Cnt_str;
extern CONST(uint16, CAL_CONST) k_MtrPos1vsMtrPos2Thresh_Rev_u3p13;
extern CONST(float32, CAL_CONST) k_TurnsCntrOffset_Rev_f32;

/********************************** ElePwr ***********************************/
extern CONST(float32, CAL_CONST) k_CntlrInResist_Ohm_f32;
extern CONST(float32, CAL_CONST) k_PstcPowerLoss_Watt_f32;

/************************** EOTActuatorMng, EtDmpFw **************************/
extern CONST(float32, CAL_CONST) k_EOTActiveRegionBypassMaxThresh_Uls_f32;
extern CONST(uint16, CAL_CONST) k_EOTDynConf_Uls_u8p8;

/*********************************** ePWM ************************************/
extern CONST(sint16, CAL_CONST) k_ADCTrig1Offset_Cnt_s16;
extern CONST(DiagSettings_Str, CAL_CONST) k_HwTrqDiag_Cnt_str;
extern CONST(uint16, CAL_CONST) k_PwmDeadBand_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_PwmRelay_Cnt_u16;
extern CONST(uint32, CAL_CONST) k_SENTSyncDelay_Cnt_u32;
extern CONST(uint32, CAL_CONST) k_SENTSyncTrgMin_Cnt_u32;
extern CONST(uint16, CAL_CONST) k_SPI1mOff_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_SPI50UOff_Cnt_u16;

/********************************** EtDmpFw **********************************/
extern CONST(float32, CAL_CONST) k_EOTDmpFWInactiveLim_MtrNm_f32;
extern CONST(sint16, CAL_CONST) t_EOTDmpFWActiveBoundX_MtrRadpS_s11p4[5];
extern CONST(uint16, CAL_CONST) t_EOTDmpFWVehSpd_Kph_u9p7[4];
extern CONST(sint16, CAL_CONST) t2_EOTDmpFWActiveBoundY_MtrNm_s7p8[4][5];

/******************************** HiLoadStall ********************************/
extern CONST(uint16, CAL_CONST) k_EOTThrmPrtLPFKn_Cnt_u16;
extern CONST(float32, CAL_CONST) k_EOTThrmSlwLmtStp_MtrNm_f32;
extern CONST(uint16, CAL_CONST) t_EOTThrmDpntTbl_MtrNm_u8p8[4];
extern CONST(uint16, CAL_CONST) t_EOTThrmIndptTbl_MtrNm_u8p8[4];

/************************ HiLoadStall, ThrmDutyCycle *************************/
extern CONST(float32, CAL_CONST) k_AbsMtrVelBkt_MtrRadps_f32;

/**************************** IoHwAbstractionUsr *****************************/
extern CONST(DiagSettings_Str, CAL_CONST) k_SlowADCDiag_Cnt_str;
extern CONST(float32, CAL_CONST) k_TempSensorOffset_Volt_f32;
extern CONST(float32, CAL_CONST) k_TempSensorScale_Uls_f32;
extern CONST(float32, CAL_CONST) k_VbattScale_Uls_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_VrefDiag_Cnt_str;
extern CONST(float32, CAL_CONST) k_VrefMax_Volt_f32;
extern CONST(float32, CAL_CONST) k_VrefMin_Volt_f32;
extern CONST(float32, CAL_CONST) k_VrefScale_Uls_f32;
extern CONST(float32, CAL_CONST) k_VswitchScale_Uls_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_SlowADCValidDiag_Cnt_str;
extern CONST(uint32, CAL_CONST) k_ReadAdcWaitTimeout_uS_u32;

/********************************** LmtCod ***********************************/
extern CONST(float32, CAL_CONST) k_CCLTrqRampIncSlew_UlspS_f32;
extern CONST(float32, CAL_CONST) k_GainDecSlew_UlspS_f32;
extern CONST(float32, CAL_CONST) k_TorqueDecSlew_MtrNmpS_f32;
extern CONST(uint16, CAL_CONST) t_GainIncSlewTblX_Kph_u9p7[2];
extern CONST(uint16, CAL_CONST) t_GainIncSlewTblY_UlspS_u9p7[2];
extern CONST(uint16, CAL_CONST) t_TorqueIncSlewTblX_Kph_u9p7[2];
extern CONST(uint16, CAL_CONST) t_TorqueIncSlewTblY_MtrNmpS_u13p3[2];

/******************************** MtrCtrl_CM *********************************/
extern CONST(float32, CAL_CONST) k_CuThermCoeff_OhmpDegC_f32;
extern CONST(float32, CAL_CONST) k_deadtimeVScale_Uls_f32;
extern CONST(uint16, CAL_CONST) k_EstPkCurr2msLPFKn_Uls_u16;
extern CONST(uint16, CAL_CONST) k_EstPkCurrSlowLoopLPFKn_Uls_u16;
extern CONST(float32, CAL_CONST) k_Harmonic12thElec_Uls_f32;
extern CONST(float32, CAL_CONST) k_Harmonic18thElec_Uls_f32;
extern CONST(float32, CAL_CONST) k_Harmonic6thElec_Uls_f32;
extern CONST(float32, CAL_CONST) k_IdBoostGain_Uls_f32;
extern CONST(float32, CAL_CONST) k_IdBoostVRThreshScl_Uls_f32;
extern CONST(uint16, CAL_CONST) k_IdqRefIminNIter_Cnt_u16;
extern CONST(float32, CAL_CONST) k_IdqRefIminTol_Amp_f32;
extern CONST(uint16, CAL_CONST) k_IdqRefLocateRefNIter_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_IdqRefTrqNIter_Cnt_u16;
extern CONST(float32, CAL_CONST) k_IdqRefTrqTol_Rad_f32;
extern CONST(float32, CAL_CONST) k_InstMtrDirHyst_Deg_f32;
extern CONST(float32, CAL_CONST) k_MagThrC_VpRadpSpDegC_f32;
extern CONST(float32, CAL_CONST) k_MaxKeRngLmt_VpRadpS_f32;
extern CONST(float32, CAL_CONST) k_MaxLdRngLmt_Henry_f32;
extern CONST(float32, CAL_CONST) k_MaxLqRngLmt_Henry_f32;
extern CONST(float32, CAL_CONST) k_MaxRRngLmt_Ohm_f32;
extern CONST(float32, CAL_CONST) k_MaxTrqCmdScl_Uls_f32;
extern CONST(float32, CAL_CONST) k_MinKeRngLmt_VpRadpS_f32;
extern CONST(float32, CAL_CONST) k_MinLdRngLmt_Henry_f32;
extern CONST(float32, CAL_CONST) k_MinLqRngLmt_Henry_f32;
extern CONST(float32, CAL_CONST) k_MinRRngLmt_Ohm_f32;
extern CONST(float32, CAL_CONST) k_MinTrqCmdScl_Uls_f32;
extern CONST(float32, CAL_CONST) k_MtrPosComputationDelay_Sec_f32;
extern CONST(uint16, CAL_CONST) k_MtrVelFiltFFKn_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_MtrVelFiltPIKn_Cnt_u16;
extern CONST(float32, CAL_CONST) k_NomLd_Henry_f32;
extern CONST(float32, CAL_CONST) k_NomLq_Henry_f32;
extern CONST(float32, CAL_CONST) k_NomRfet_Ohm_f32;
extern CONST(float32, CAL_CONST) k_NomTemp_DegC_f32;
extern CONST(float32, CAL_CONST) k_NoofPoles_Uls_f32;
extern CONST(float32, CAL_CONST) k_PIGainVspdCutoff_kph_f32;
extern CONST(float32, CAL_CONST) k_PiSamplingTs_Sec_f32;
extern CONST(float32, CAL_CONST) k_SiThermCoeff_OhmpDegC_f32;
extern CONST(uint16, CAL_CONST) t_CommOffsetTblX_Uls_u3p13[2];
extern CONST(uint16, CAL_CONST) t_CurrParamCompDaxRef_Amp_u9p7[6];
extern CONST(uint16, CAL_CONST) t_CurrParamCompQaxRef_Amp_u9p7[7];
extern CONST(uint16, CAL_CONST) t_IdBoostTrqCharSclY_Uls_u1p15[11];
extern CONST(uint16, CAL_CONST) t_IdBoostTrqCmdX_MtrNm_u4p12[11];
extern CONST(uint16, CAL_CONST) t_KeSatTblX_Amp_u9p7[16];
extern CONST(uint16, CAL_CONST) t_KeSatTblY_Uls_u2p14[16];
extern CONST(uint16, CAL_CONST) t_KidGainX_MtrRadpSec_u12p4[8];
extern CONST(uint16, CAL_CONST) t_KidGainY_Uls_u10p6[8];
extern CONST(uint16, CAL_CONST) t_KiqGainX_MtrRadpSec_u12p4[8];
extern CONST(uint16, CAL_CONST) t_KiqGainY_Uls_u10p6[8];
extern CONST(uint16, CAL_CONST) t_KpdGainX_MtrRadpSec_u12p4[8];
extern CONST(uint16, CAL_CONST) t_KpdGainY_Uls_u6p10[8];
extern CONST(uint16, CAL_CONST) t_KpqGainX_MtrRadpSec_u12p4[8];
extern CONST(uint16, CAL_CONST) t_KpqGainY_Uls_u6p10[8];
extern CONST(uint16, CAL_CONST) t_MtrCurrDaxRpl_Amp_u9p7[10];
extern CONST(uint16, CAL_CONST) t_MtrCurrQaxRpl_Amp_u9p7[12];
extern CONST(uint16, CAL_CONST) t_MtrCurrQaxRplPIY_Amp_u9p7[7];
extern CONST(uint16, CAL_CONST) t_MtrVelX_MtrRadpS_T_u16[20];
extern CONST(uint16, CAL_CONST) t_Q13VltgSchedXTbl_MtrRadpS_u12p4[10];
extern CONST(uint16, CAL_CONST) t_Q13VltgSchedYTbl_Volt_u5p11[10];
extern CONST(uint16, CAL_CONST) t_Q24VltgSchedXTbl_MtrRadpS_u12p4[10];
extern CONST(uint16, CAL_CONST) t_Q24VltgSchedYTbl_Volt_u5p11[10];
extern CONST(float32, CAL_CONST) t_RefDeltaPoints_Rad_f32[8];
extern CONST(uint16, CAL_CONST) t2_CurrParamLdSatSclFac_Uls_u2p14[6][7];
extern CONST(uint16, CAL_CONST) t2_CurrParamLqSatSclFac_Uls_u2p14[6][7];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl12X_Amp_s6p9[6][7];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl12Y_Amp_s6p9[6][7];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl18X_Amp_s6p9[6][7];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl18Y_Amp_s6p9[6][7];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl6X_Amp_s6p9[6][7];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl6Y_Amp_s6p9[6][7];
extern CONST(uint16, CAL_CONST) t2_MtrTrqCancPIMagRP_Uls_u6p10[20][8];
extern CONST(uint16, CAL_CONST) t2_MtrTrqCancPIPhRP_Rev_u0p16[20][8];
extern CONST(boolean, CAL_CONST) k_MtrCtrlCurrLoopSecOrTranFcEnable_Cnt_lgc;
extern CONST(boolean, CAL_CONST) k_MtrCtrlFeedbackControlDisable_Cnt_lgc;
extern CONST(boolean, CAL_CONST) k_VoltModeDynCompEnable_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_MtrVoltDervFiltCoeffTimeCons_Sec_f32;
extern CONST(float32, CAL_CONST) k_MtrCtrlVirualResQax_Ohm_f32;
extern CONST(float32, CAL_CONST) k_MtrCtrlVirualResDax_Ohm_f32;
extern CONST(float32, CAL_CONST) k_MtrCurrDaxMaxValScl_Per_f32;
extern CONST(float32, CAL_CONST) k_MtrDampingRatioDax_Uls_f32;
extern CONST(float32, CAL_CONST) k_MtrDampingRatioQax_Uls_f32;
extern CONST(uint16, CAL_CONST) t_MtrBandwidthDaxY_Hz_u10p6[4];
extern CONST(uint16, CAL_CONST) t_MtrBandwidthQaxY_Hz_u10p6[4];
extern CONST(uint16, CAL_CONST) t_MtrVelCtrlGainX_MtrRadpSec_u12p4[4];
extern CONST(uint16, CAL_CONST) t_MtrNaturalFreqQaxY_Hz_u9p7[4];
extern CONST(uint16, CAL_CONST) t_MtrNaturalFreqDaxY_Hz_u9p7[4];
extern CONST(uint16, CAL_CONST) t_MtrTrqCmdPIY_MtrNm_u5p11[8];
extern CONST(sint16, CAL_CONST) t2_MtrTrqRpl18Y_MtrNm_s2p13[10][12];
extern CONST(sint16, CAL_CONST) t2_MtrTrqRpl18X_MtrNm_s2p13[10][12];
extern CONST(sint16, CAL_CONST) t2_MtrTrqRpl12Y_MtrNm_s2p13[10][12];
extern CONST(sint16, CAL_CONST) t2_MtrTrqRpl12X_MtrNm_s2p13[10][12];
extern CONST(sint16, CAL_CONST) t2_MtrTrqRpl6Y_MtrNm_s2p13[10][12];
extern CONST(sint16, CAL_CONST) t2_MtrTrqRpl6X_MtrNm_s2p13[10][12];
extern CONST(float32, CAL_CONST) k_VoltSatDaxPolyCoeff_Uls_f32;
extern CONST(float32, CAL_CONST) k_VoltSatQaxPolyCoeff_Uls_f32;
extern CONST(boolean, CAL_CONST) k_MtrCurrQaxRefModifDsb_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_CLOAFdbackSignalSclFacSlew_UlspS_f32;
extern CONST(float32, CAL_CONST) k_ILOAFdbackSignalSclFacSlew_UlspS_f32;
extern CONST(float32, CAL_CONST) k_MtrPosComputationDelayRpl_Sec_f32;
extern CONST(float32, CAL_CONST) k_MtrVoltQaxFiltFFKn_Hz_f32;
extern CONST(boolean, CAL_CONST) k_MtrVoltQaxFiltFFEnable_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_MtrVoltVecuFiltKn_Hz_f32;
extern CONST(boolean, CAL_CONST) k_MtrVoltVecuFiltEnable_Cnt_lgc;

/**************************** MtrCtrl_CM, SVDiag *****************************/
extern CONST(uint16, CAL_CONST) t_CommOffsetTblY_Cnt_u16[2];

/******************************** MtrTempEst *********************************/
extern CONST(float32, CAL_CONST) k_AMAmbLPFKn_Hz_f32;
extern CONST(float32, CAL_CONST) k_AMAmbMult_DegCpWatt_f32;
extern CONST(float32, CAL_CONST) k_AmbPwrMult_WtspAmpSq_f32;
extern CONST(float32, CAL_CONST) k_AmbTempScl_Uls_f32;
extern CONST(float32, CAL_CONST) k_AMCorrLmt_DegC_f32;
extern CONST(float32, CAL_CONST) k_AMDampScl_NmpRadpS_f32;
extern CONST(float32, CAL_CONST) k_AMDefaultTemp_DegC_f32;
extern CONST(float32, CAL_CONST) k_AMLLFiltCoefB0_Uls_f32;
extern CONST(float32, CAL_CONST) k_AMLLFiltCoefB1_Uls_f32;
extern CONST(float32, CAL_CONST) k_AMLLFiltPoleA1_Uls_f32;
extern CONST(float32, CAL_CONST) k_AssistMechSlew_DegCpS_f32;
extern CONST(float32, CAL_CONST) k_CuAmbLPFKn_Hz_f32;
extern CONST(float32, CAL_CONST) k_CuAmbMult_DegCpWatt_f32;
extern CONST(float32, CAL_CONST) k_CuCorrLmt_DegC_f32;
extern CONST(float32, CAL_CONST) k_CuLLFiltKA1_Uls_f32;
extern CONST(float32, CAL_CONST) k_CuLLFiltKB0_Uls_f32;
extern CONST(float32, CAL_CONST) k_CuLLFiltKB1_Uls_f32;
extern CONST(float32, CAL_CONST) k_EngTempScl_Uls_f32;
extern CONST(float32, CAL_CONST) k_MagAmbLPFKn_Hz_f32;
extern CONST(float32, CAL_CONST) k_MagAmbMult_DegCpWatt_f32;
extern CONST(float32, CAL_CONST) k_MagCorrLmt_DegC_f32;
extern CONST(float32, CAL_CONST) k_MagLLFiltKA1_Uls_f32;
extern CONST(float32, CAL_CONST) k_MagLLFiltKB0_Uls_f32;
extern CONST(float32, CAL_CONST) k_MagLLFiltKB1_Uls_f32;
extern CONST(float32, CAL_CONST) k_SiAmbLPFKn_Hz_f32;
extern CONST(float32, CAL_CONST) k_SiAmbMult_DegCpWatt_f32;
extern CONST(float32, CAL_CONST) k_SiCorrLmt_DegC_f32;
extern CONST(float32, CAL_CONST) k_SiLLFiltKA1_Uls_f32;
extern CONST(float32, CAL_CONST) k_SiLLFiltKB0_Uls_f32;
extern CONST(float32, CAL_CONST) k_SiLLFiltKB1_Uls_f32;
extern CONST(float32, CAL_CONST) k_TrimTempAM_DegC_f32;
extern CONST(float32, CAL_CONST) k_TrimTempCu_DegC_f32;
extern CONST(float32, CAL_CONST) k_TrimTempMag_DegC_f32;
extern CONST(float32, CAL_CONST) k_TrimTempSi_DegC_f32;
extern CONST(Boolean, CAL_CONST) k_WtAvgTempDFt_Cnt_lgc;

/******************* MtrVel, AbsHwPos_TcI2cVd, MtrVel_Digi *******************/
extern CONST(float32, CAL_CONST) k_GearRatio_Uls_f32;

/**************************** MtrVel, MtrVel_Digi ****************************/
extern CONST(DiagSettings_Str, CAL_CONST) k_HwVelCorrLim_Cnt_Str;
extern CONST(float32, CAL_CONST) k_HwVelCorrLim_HwRadpS_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_MtrVelCorrLim_Cnt_Str;
extern CONST(float32, CAL_CONST) k_MtrVelCorrLim_MtrRadpS_f32;
extern CONST(uint16, CAL_CONST) t_MtrVelBlendTblX_MtrRadpS_u12p4[2];

/******************************** OvrVoltMon *********************************/
extern CONST(DiagSettings_Str, CAL_CONST) k_CPUSupplyOV_Cnt_Str;

/******************************* PwrLmtFuncCr ********************************/
extern CONST(float32, CAL_CONST) k_AsstReducLPFKn_Hz_f32;
extern CONST(float32, CAL_CONST) k_FiltAsstReducTh_Uls_f32;
extern CONST(float32, CAL_CONST) k_KeStdTemp_VpRadpS_f32;
extern CONST(float32, CAL_CONST) k_LowVltAstRecTh_Volt_f32;
extern CONST(uint16, CAL_CONST) k_LowVltAstRecTime_mS_u16;
extern CONST(float32, CAL_CONST) k_PwrLmtMtrVelLPFKn_Hz_f32;
extern CONST(float32, CAL_CONST) k_PwrLmtVecuAdjSlew_VoltspL_f32;
extern CONST(float32, CAL_CONST) k_PwrLmtVecuAltFltAdj_Volt_f32;
extern CONST(float32, CAL_CONST) k_SpdAdjSlewDec_MtrRadpS_f32;
extern CONST(boolean, CAL_CONST) k_SpdAdjSlewEnable_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_SpdAdjSlewInc_MtrRadpS_f32;
extern CONST(uint16, CAL_CONST) t_DLVTblX_Volt_u5p11[10];
extern CONST(uint16, CAL_CONST) t_DLVTblY_MtrRadpS_u11p5[10];
extern CONST(sint16, CAL_CONST) t_MtrEnvTblX_MtrRadpS_s11p4[14];
extern CONST(uint16, CAL_CONST) t_MtrEnvTblY_MtrNm_u5p11[14];
extern CONST(uint16, CAL_CONST) t_StdOpMtrEnvTblX_MtrRadpS_u11p5[6];
extern CONST(uint16, CAL_CONST) t_StdOpMtrEnvTblY_MtrNm_u4p12[6];

/********************************** Return ***********************************/
extern CONST(float32, CAL_CONST) k_RtnHWAuthSlew_UlspS_f32;
extern CONST(float32, CAL_CONST) k_RtnLimit_MtrNm_f32;
extern CONST(float32, CAL_CONST) k_RtnOffsetRange_HWDeg_f32;
extern CONST(float32, CAL_CONST) k_RtnOffsetSlew_HwDegpS_f32;

/********************************* SgnlCond **********************************/
extern CONST(float32, CAL_CONST) k_VehAccelSlewRate_KphpSecSq_f32;
extern CONST(float32, CAL_CONST) k_VehSpdSlewRate_KphpSec_f32;

/******************************** SrlComInput ********************************/
extern CONST(uint16, CAL_CONST) k_BCM2MsgTimeout_mS_u16;
extern CONST(DiagSettings_Str, CAL_CONST) k_BSM1MsgDiag_Cnt_str;
extern CONST(uint16, CAL_CONST) k_BSM1MsgTimeout_mS_u16;
extern CONST(uint16, CAL_CONST) k_MOT1MsgTimeout_mS_u16;
extern CONST(uint16, CAL_CONST) k_MOT3MsgTimeout_mS_u16;
extern CONST(uint16, CAL_CONST) k_IPCMsgTimeout_mS_u16;
extern CONST(uint16, CAL_CONST) k_BCM_CMDMsgTimeout_mS_u16;
extern CONST(DiagSettings_Str, CAL_CONST) k_VehSpeedSigDiag_Cnt_str;
extern CONST(uint16, CAL_CONST) k_NTCEnableTimeout_mS_u16;
extern CONST(float32, CAL_CONST) k_DefaultVehSpd_Kph_f32;
extern CONST(uint16, CAL_CONST) k_BCMMsgPreIgnitionStart_ms_u16;
extern CONST(uint16, CAL_CONST) k_BCMInvMsgTimeout_mS_u16;
extern CONST(uint16, CAL_CONST) k_BCM2InvMsgTimeout_mS_u16;
extern CONST(uint16, CAL_CONST) k_BSMInvMsgTimeout_mS_u16;
extern CONST(uint16, CAL_CONST) k_MOT1InvMsgTimeout_mS_u16;
extern CONST(uint16, CAL_CONST) k_MOT3InvMsgTimeout_mS_u16;
extern CONST(uint16, CAL_CONST) k_IPCInvMsgTimeout_mS_u16;
extern CONST(DiagSettings_Str, CAL_CONST) k_BSM1CRCDiag_Cnt_str;
extern CONST(DiagSettings_Str, CAL_CONST) k_BSM1MsgCounterDiag_Cnt_str;
extern CONST(uint16, CAL_CONST) k_CfgCodeMsgTimeout_mS_u16;
extern CONST(uint16, CAL_CONST) k_CTCEnableTimeout_mS_u16;
extern CONST(uint8, CAL_CONST) k_SrlComMsgCntrMissThreshold_Cnt_u08;

/******************************* SrlComOutput ********************************/
extern CONST(float32, CAL_CONST) k_SASCALAuthorityThresh_Uls_f32;
extern CONST(float32, CAL_CONST) k_ScomVelPolarity_Cnt_T_f32;
extern CONST(sint8, CAL_CONST) k_ScomAngPolarity_Cnt_T_s8;

/******************************* StabilityComp *******************************/
extern CONST(uint16, CAL_CONST) k_StCmpStabCmpNstep_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_StCmpStabCmpPNThresh_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_StCmpStabCmpPstep_Cnt_u16;

/*********************************** StaMd ***********************************/
extern CONST(DiagSettings_Str, CAL_CONST) k_StaMdsSysCDiag_Cnt_str;

/********************************** SVDiag ***********************************/
extern CONST(uint16, CAL_CONST) k_ErrorFiltKn_Cnt_u16;
extern CONST(uint32, CAL_CONST) k_ErrorThresh_Cnt_u32;
extern CONST(DiagSettings_Str, CAL_CONST) k_GateDriveDiag_Cnt_str;
extern CONST(DiagSettings_Str, CAL_CONST) k_LowResPhsReas_Cnt_str;
extern CONST(float32, CAL_CONST) k_LowResPhsReasMaxTol_Uls_f32;
extern CONST(float32, CAL_CONST) k_LowResPhsReasMinTol_Uls_f32;
extern CONST(float32, CAL_CONST) k_LRPRCommOffsetMargin_Uls_f32;
extern CONST(float32, CAL_CONST) k_LRPRMtrVelDiagEnable_MtrRadpS_T_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_OnStateDiag_Cnt_str;
extern CONST(uint32, CAL_CONST) k_PhsReasEnableThresh_Cnt_u32;
extern CONST(sint16, CAL_CONST) k_PhsReasErrorTerm_Cnt_s16;

/********************************* SVDrvr_CM *********************************/
extern CONST(uint16, CAL_CONST) k_DitherLPFKn_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_PWMBaseFrequency_Hz_u16;

/******************************* ThrmDutyCycle *******************************/
extern CONST(DiagSettings_Str, CAL_CONST) k_AbsTempDiag_Cnt_str;
extern CONST(float32, CAL_CONST) k_AbsTmpTrqSlewLmt_MtrNm_f32;
extern CONST(boolean, CAL_CONST) k_CtrlTempSlc_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_DefaultIgnOffTime_Sec_f32;
extern CONST(uint16, CAL_CONST) k_DutyCycFltTrshld_Uls_u16p0;
extern CONST(float32, CAL_CONST) k_EOCCtrlTemp_DegC_f32;
extern CONST(boolean, CAL_CONST) k_IgnOffCntrEnb_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_IgnOffMsgWaitTime_Sec_f32;
extern CONST(boolean, CAL_CONST) k_MtrPrTempSlc_Cnt_lgc;
extern CONST(boolean, CAL_CONST) k_MultTempSlc_Cnt_lgc;
extern CONST(boolean, CAL_CONST) k_SlowFltTempSlc_Cnt_lgc;
extern CONST(uint16, CAL_CONST) k_TrqCmdSlewDown_MtrNm_u9p7;
extern CONST(uint16, CAL_CONST) k_TrqCmdSlewUp_MtrNm_u9p7;
extern CONST(sint16, CAL_CONST) t_AbsCtrlTmpTblX_DegC_s15p0[4];
extern CONST(uint16, CAL_CONST) t_AbsCtrlTmpTblY_MtrNm_u9p7[4];
extern CONST(sint16, CAL_CONST) t_AbsCuTmpTblX_DegC_s15p0[4];
extern CONST(uint16, CAL_CONST) t_AbsCuTmpTblY_MtrNm_u9p7[4];
extern CONST(uint16, CAL_CONST) t_LastTblValNS_MtrNm_u9p7[5];
extern CONST(uint16, CAL_CONST) t_LastTblValS_MtrNm_u9p7[5];
extern CONST(uint16, CAL_CONST) t_Mult1NSTblY_Uls_u3p13[5];
extern CONST(uint16, CAL_CONST) t_Mult1STblY_Uls_u3p13[5];
extern CONST(uint16, CAL_CONST) t_Mult2NSTblY_Uls_u3p13[5];
extern CONST(uint16, CAL_CONST) t_Mult2STblY_Uls_u3p13[5];
extern CONST(uint16, CAL_CONST) t_Mult3NSTblY_Uls_u3p13[5];
extern CONST(uint16, CAL_CONST) t_Mult3STblY_Uls_u3p13[5];
extern CONST(uint16, CAL_CONST) t_Mult4NSTblY_Uls_u3p13[5];
extern CONST(uint16, CAL_CONST) t_Mult4STblY_Uls_u3p13[5];
extern CONST(uint16, CAL_CONST) t_Mult5NSTblY_Uls_u3p13[5];
extern CONST(uint16, CAL_CONST) t_Mult5STblY_Uls_u3p13[5];
extern CONST(uint16, CAL_CONST) t_Mult6NSTblY_Uls_u3p13[5];
extern CONST(uint16, CAL_CONST) t_Mult6STblY_Uls_u3p13[5];
extern CONST(sint16, CAL_CONST) t_MultTblX_DegC_s15p0[5];
extern CONST(uint16, CAL_CONST) t_ThrmLoadLmtTblX_Uls_u16p0[8];
extern CONST(uint16, CAL_CONST) t_ThrmLoadLmtTblY_MtrNm_u9p7[8];

/******************************* TMS570_uDiag ********************************/
extern CONST(DiagSettings_Str, CAL_CONST) k_FlashECCDiag_Cnt_str;
extern CONST(uint16, CAL_CONST) k_MtrCtrlMaxCount_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_MtrCtrlMinCount_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_OneMsLoopMaxCount_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_OneMsLoopMinCount_Cnt_u16;
extern CONST(DiagSettings_Str, CAL_CONST) k_RAMECCDiag_Cnt_str;
extern CONST(uint16, CAL_CONST) k_VIMParErrThrsh_Cnt_u16;

/********************************** TqRsDg ***********************************/
extern CONST(float32, CAL_CONST) k_CurrDiagLambdaMinMax_Volt_f32;
extern CONST(float32, CAL_CONST) k_CurrDiagMtrEnvTblMax_MtrNm_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_CurrDiagPrim_Cnt_Str;
extern CONST(float32, CAL_CONST) k_CurrDiagPrimErrorThresh_Volt_f32;
extern CONST(float32, CAL_CONST) k_CurrDiagPrimLPFKn_Hz_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_CurrDiagSec_Cnt_Str;
extern CONST(float32, CAL_CONST) k_CurrDiagSecErrorThresh_Volt_f32;
extern CONST(float32, CAL_CONST) k_CurrDiagSecLPFKn_Hz_f32;
extern CONST(float32, CAL_CONST) k_CurrDiagSecTrqLmtThresh_Uls_f32;

/******************************* TuningSelAuth *******************************/
extern CONST(float32, CAL_CONST) k_TunSelHwTrqLPFKn_Hz_f32;
extern CONST(float32, CAL_CONST) k_TunSelHwTrqThresh_HwNm_f32;
extern CONST(float32, CAL_CONST) k_TunSelVehSpdThresh_Kph_f32;

/********************************** VehDyn ***********************************/
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdCntrWindow_HwDeg_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdFilt1Kn_Hz_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdFilt2Kn_Hz_f32;
extern CONST(uint16, CAL_CONST) k_AutoCntrHiSpdTimer1_mS_u16;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer1MtrVel_MtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer1PinTrq_HwNm_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer1VehSpd_kph_f32;
extern CONST(uint16, CAL_CONST) k_AutoCntrHiSpdTimer2_mS_u16;
extern CONST(uint16, CAL_CONST) k_AutoCntrHiSpdTimer4_mS_u16;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4CntrWindow_HwDeg_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4MtrVel_MtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4PinTrq_HwNm_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4VehSpd_kph_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdCntrWindow_HwDeg_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdFilt1Kn_Hz_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdFilt2Kn_Hz_f32;
extern CONST(uint16, CAL_CONST) k_AutoCntrLoSpdTimer1_mS_u16;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdTimer1MtrVel_MtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdTimer1PinTrq_HwNm_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdTimer1VehSpd_kph_f32;
extern CONST(uint16, CAL_CONST) k_AutoCntrLoSpdTimer2_mS_u16;
extern CONST(float32, CAL_CONST) k_AutoCntrPinTrqLPFCoeffKn_Hz_f32;
extern CONST(float32, CAL_CONST) k_HiSpdVDAuthority_Uls_f32;
extern CONST(float32, CAL_CONST) k_LoSpdVDAuthority_Uls_f32;
extern CONST(boolean, CAL_CONST) k_SLPEnableBFCheck_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_SLPHwAuthority_Uls_f32;
extern CONST(float32, CAL_CONST) k_SLPMinHwAuthToStoreHwPos_Uls_f32;
extern CONST(float32, CAL_CONST) k_TravelXCDeadband_Uls_f32;
extern CONST(float32, CAL_CONST) k_TravelXCHwAuthority_Uls_f32;
extern CONST(float32, CAL_CONST) k_HwTqMgnThd_HwNm_f32;
extern CONST(float32, CAL_CONST) k_VehDyn_TravelXCDeadbandTolr_Uls_f32;
extern CONST(float32, CAL_CONST) k_VehDyn_ErrTolr_HwDeg_f32;
extern CONST(float32, CAL_CONST) k_VehDyn_SmoothCoeff_Uls_f32;
extern CONST(uint32, CAL_CONST) k_SrlHwAgVldTiThd_mS_u32;

/********************************* VehPwrMd **********************************/
extern CONST(float32, CAL_CONST) k_RampDnRt_UlspmS_f32;
extern CONST(float32, CAL_CONST) k_RampUpRtLoSpd_UlspmS_f32;
extern CONST(float32, CAL_CONST) k_VehSpdAstLmt_Kph_f32;
extern CONST(float32, CAL_CONST) k_VehSpdEngOn_Kph_f32;
extern CONST(uint16, CAL_CONST) k_CTermOpModeStsTimeout_mS_u16;
extern CONST(uint16, CAL_CONST) k_CTermShutdownTimeout_mS_u16;

/********************************* VehSpdLmt *********************************/
extern CONST(uint16, CAL_CONST) k_PosMaxOfstOne_HwDeg_u12p4;
extern CONST(uint16, CAL_CONST) k_PosMaxOfstTwo_HwDeg_u12p4;
extern CONST(uint16, CAL_CONST) t_MaxAsstTblX_Kph_u9p7[5];
extern CONST(uint16, CAL_CONST) t_MaxAsstTblY_MtrNm_u5p11[5];

/********************************* DigColPs **********************************/
extern CONST(float32, CAL_CONST) k_ColAngSenseLPFFc_Hz_f32;
extern CONST(float32, CAL_CONST) k_SpurAngSenseLPFFc_Hz_f32;
extern CONST(boolean, CAL_CONST) k_SelectFromColumn_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_StepDetect_Deg_f32;
extern CONST(float32, CAL_CONST) k_VernCorrErrorThresh_Deg_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_VernCorrErrorDiag_Cnt_str;
extern CONST(DiagSettings_Str, CAL_CONST) k_SkipStepErrDiag_Cnt_str;
extern CONST(float32, CAL_CONST) k_VernOORangeThresh_Deg_f32;
extern CONST(DiagSettings_Str, CAL_CONST) k_SenseDetErrDiag_Cnt_str;
extern CONST(DiagSettings_Str, CAL_CONST) k_SenseParityErrDiag_Cnt_str;
extern CONST(uint8, CAL_CONST) k_ColSensorI2CAddress_Cnt_u08;
extern CONST(uint8, CAL_CONST) k_SpurSensorI2CAddress_Cnt_u08;
extern CONST(float32, CAL_CONST) k_I2CHWInitTransactionTime_Sec_f32;

/***************************** AbsHwPos_TcI2cVd ******************************/
#define k_KinmIntDiagMaxRackLimit_HwDeg_f32	TunSet_Ptr_Str->k_KinmIntDiagMaxRackLimit_HwDeg_f32

/******************************** ActivePull *********************************/
#define k_EnableHwAuthMin_Uls_f32	TunSet_Ptr_Str->k_EnableHwAuthMin_Uls_f32
#define k_EnableHwPosMax_HwDeg_f32	TunSet_Ptr_Str->k_EnableHwPosMax_HwDeg_f32
#define k_EnableHwTrqMax_HwNm_f32	TunSet_Ptr_Str->k_EnableHwTrqMax_HwNm_f32
#define k_EnableHwVelMax_DegpS_f32	TunSet_Ptr_Str->k_EnableHwVelMax_DegpS_f32
#define k_EnableTime_mS_u32	TunSet_Ptr_Str->k_EnableTime_mS_u32
#define k_EnableVehSpdMax_Kph_f32	TunSet_Ptr_Str->k_EnableVehSpdMax_Kph_f32
#define k_EnableVehSpdMin_Kph_f32	TunSet_Ptr_Str->k_EnableVehSpdMin_Kph_f32
#define k_EnableVehSpdRateMax_KphpS_f32	TunSet_Ptr_Str->k_EnableVehSpdRateMax_KphpS_f32
#define k_EnableYawRateMax_DegpS_f32	TunSet_Ptr_Str->k_EnableYawRateMax_DegpS_f32
#define k_FiltDeadband_HwNm_f32	TunSet_Ptr_Str->k_FiltDeadband_HwNm_f32
#define k_HwNmToMtrNm_Uls_f32	TunSet_Ptr_Str->k_HwNmToMtrNm_Uls_f32
#define k_HwTrqFilt_Hz_f32	TunSet_Ptr_Str->k_HwTrqFilt_Hz_f32
#define k_LTFilt_Hz_f32	TunSet_Ptr_Str->k_LTFilt_Hz_f32
#define k_LTIntInputLimit_HwNm_f32	TunSet_Ptr_Str->k_LTIntInputLimit_HwNm_f32
#define k_LTLearnTime_Min_f32	TunSet_Ptr_Str->k_LTLearnTime_Min_f32
#define k_LTLimit_HwNm_f32	TunSet_Ptr_Str->k_LTLimit_HwNm_f32
#define k_OutputMaxRate_HwNmpS_f32	TunSet_Ptr_Str->k_OutputMaxRate_HwNmpS_f32
#define k_STFilt_Hz_f32	TunSet_Ptr_Str->k_STFilt_Hz_f32
#define k_STIntInputLimit_HwNm_f32	TunSet_Ptr_Str->k_STIntInputLimit_HwNm_f32
#define k_STLearnTimeDec_Sec_f32	TunSet_Ptr_Str->k_STLearnTimeDec_Sec_f32
#define k_STLearnTimeInc_Sec_f32	TunSet_Ptr_Str->k_STLearnTimeInc_Sec_f32
#define k_STLimit_HwNm_f32	TunSet_Ptr_Str->k_STLimit_HwNm_f32
#define k_STOppSignTime_mS_u32	TunSet_Ptr_Str->k_STOppSignTime_mS_u32
#define k_STRampTime_Sec_f32	TunSet_Ptr_Str->k_STRampTime_Sec_f32
#define k_STResetHwPos_HwDeg_f32	TunSet_Ptr_Str->k_STResetHwPos_HwDeg_f32
#define k_STResetHwTrq_HwNm_f32	TunSet_Ptr_Str->k_STResetHwTrq_HwNm_f32
#define k_STResetYawRate_DegpS_f32	TunSet_Ptr_Str->k_STResetYawRate_DegpS_f32
#define k_TotalLimit_HwNm_f32	TunSet_Ptr_Str->k_TotalLimit_HwNm_f32
#define k_YawRateFilt_Hz_f32	TunSet_Ptr_Str->k_YawRateFilt_Hz_f32
#define t_VehSpdScaleTblX_Kph_u9p7	TunSet_Ptr_Str->t_VehSpdScaleTblX_Kph_u9p7
#define t_VehSpdScaleTblY_Uls_u2p14	TunSet_Ptr_Str->t_VehSpdScaleTblY_Uls_u2p14

/* Assist, Damping, FrqDepDmpnInrtCmp, HighFreqAssist, HystComp, DampingFirewall ********************************************************************************/
#define t_CmnVehSpd_Kph_u9p7	TunSet_Ptr_Str->t_CmnVehSpd_Kph_u9p7

/****************************** AssistFirewall *******************************/
#define k_AsstFWFiltKn_Hz_f32	TunSet_Ptr_Str->k_AsstFWFiltKn_Hz_f32
#define k_AsstFWFWActiveLPF_Hz_f32	TunSet_Ptr_Str->k_AsstFWFWActiveLPF_Hz_f32
#define k_AsstFWInpLimitBaseAsst_MtrNm_f32	TunSet_Ptr_Str->k_AsstFWInpLimitBaseAsst_MtrNm_f32
#define k_AsstFWInpLimitHFA_MtrNm_f32	TunSet_Ptr_Str->k_AsstFWInpLimitHFA_MtrNm_f32
#define k_AsstFWNstep_Cnt_u16	TunSet_Ptr_Str->k_AsstFWNstep_Cnt_u16
#define k_AsstFWPstep_Cnt_u16	TunSet_Ptr_Str->k_AsstFWPstep_Cnt_u16
#define k_RestoreThresh_MtrNm_f32	TunSet_Ptr_Str->k_RestoreThresh_MtrNm_f32
#define t_AsstFWDefltAssistX_HwNm_u8p8	TunSet_Ptr_Str->t_AsstFWDefltAssistX_HwNm_u8p8
#define t_AsstFWDefltAssistY_MtrNm_s4p11	TunSet_Ptr_Str->t_AsstFWDefltAssistY_MtrNm_s4p11
#define t_AsstFWPstepNstepThresh_Cnt_u16	TunSet_Ptr_Str->t_AsstFWPstepNstepThresh_Cnt_u16
#define t_AsstFWVehSpd_Kph_u9p7	TunSet_Ptr_Str->t_AsstFWVehSpd_Kph_u9p7
#define t2_AsstFWUprBoundX_HwNm_s4p11	TunSet_Ptr_Str->t2_AsstFWUprBoundX_HwNm_s4p11
#define t2_AsstFWUprBoundY_MtrNm_s4p11	TunSet_Ptr_Str->t2_AsstFWUprBoundY_MtrNm_s4p11

/******************************** AvgFricLrn *********************************/
#define k_AvgFricLPFKn_Hz_f32	TunSet_Ptr_Str->k_AvgFricLPFKn_Hz_f32
#define k_BaselineEOLFric_HwNm_f32	TunSet_Ptr_Str->k_BaselineEOLFric_HwNm_f32
#define k_DataPrepLPFKn_Hz_f32	TunSet_Ptr_Str->k_DataPrepLPFKn_Hz_f32
#define k_EOLFricDiffLimitHigh_HwNm_f32	TunSet_Ptr_Str->k_EOLFricDiffLimitHigh_HwNm_f32
#define k_EOLFricDiffLimitLow_HwNm_f32	TunSet_Ptr_Str->k_EOLFricDiffLimitLow_HwNm_f32
#define k_EOLFricDiffScalingFactor_Uls_f32	TunSet_Ptr_Str->k_EOLFricDiffScalingFactor_Uls_f32
#define k_FricOffsetLimitHigh_HwNm_f32	TunSet_Ptr_Str->k_FricOffsetLimitHigh_HwNm_f32
#define k_FricOffsetLimitLow_HwNm_f32	TunSet_Ptr_Str->k_FricOffsetLimitLow_HwNm_f32
#define k_FricOffsetLPFKn_Hz_f32	TunSet_Ptr_Str->k_FricOffsetLPFKn_Hz_f32
#define k_FrictionDiagThreshold_HwNm_f32	TunSet_Ptr_Str->k_FrictionDiagThreshold_HwNm_f32
#define k_FrictionDiagTimer_mS_u32	TunSet_Ptr_Str->k_FrictionDiagTimer_mS_u32
#define k_HwPosAuthMin_Uls_f32	TunSet_Ptr_Str->k_HwPosAuthMin_Uls_f32
#define k_HwVelConstLimit_HwDegpS_f32	TunSet_Ptr_Str->k_HwVelConstLimit_HwDegpS_f32
#define k_HwVelMax_HwDegpS_f32	TunSet_Ptr_Str->k_HwVelMax_HwDegpS_f32
#define k_HwVelMin_HwDegpS_f32	TunSet_Ptr_Str->k_HwVelMin_HwDegpS_f32
#define k_IgnCycleFricChgLim_HwNm_f32	TunSet_Ptr_Str->k_IgnCycleFricChgLim_HwNm_f32
#define k_LatAccMax_MpSecSqrd_f32	TunSet_Ptr_Str->k_LatAccMax_MpSecSqrd_f32
#define k_LatAccMin_MpSecSqrd_f32	TunSet_Ptr_Str->k_LatAccMin_MpSecSqrd_f32
#define k_LearningGain_Uls_f32	TunSet_Ptr_Str->k_LearningGain_Uls_f32
#define k_LearningThreshold_Cnt_u32	TunSet_Ptr_Str->k_LearningThreshold_Cnt_u32
#define k_RangeCounterLimit_Cnt_u16	TunSet_Ptr_Str->k_RangeCounterLimit_Cnt_u16
#define k_SatFricChgLim_HwNm_f32	TunSet_Ptr_Str->k_SatFricChgLim_HwNm_f32
#define k_TempMax_DegC_f32	TunSet_Ptr_Str->k_TempMax_DegC_f32
#define k_TempMin_DegC_f32	TunSet_Ptr_Str->k_TempMin_DegC_f32
#define t_BaselineFric_HwNm_f32	TunSet_Ptr_Str->t_BaselineFric_HwNm_f32
#define t_FrHystHwAPts_HwDeg_f32	TunSet_Ptr_Str->t_FrHystHwAPts_HwDeg_f32
#define t_FricChgWeight_Uls_f32	TunSet_Ptr_Str->t_FricChgWeight_Uls_f32
#define t_InvRatioX_HwDeg_u11p5	TunSet_Ptr_Str->t_InvRatioX_HwDeg_u11p5
#define t_InvRatioY_HwNmpMtrNm_u6p10	TunSet_Ptr_Str->t_InvRatioY_HwNmpMtrNm_u6p10
#define t_MskVehSpd_Cnt_lgc	TunSet_Ptr_Str->t_MskVehSpd_Cnt_lgc
#define t2_BaselineRangeCounter_Cnt_u16	TunSet_Ptr_Str->t2_BaselineRangeCounter_Cnt_u16
#define t2_BaselineTheta_HwNm_f32	TunSet_Ptr_Str->t2_BaselineTheta_HwNm_f32
#define t2_VehSpd_Kph_f32	TunSet_Ptr_Str->t2_VehSpd_Kph_f32

/********************************** Damping **********************************/
#define t_TempScaleX_DegC_s8p7	TunSet_Ptr_Str->t_TempScaleX_DegC_s8p7
#define t_TempScaleY_Uls_u4p12	TunSet_Ptr_Str->t_TempScaleY_Uls_u4p12

/****************************** DampingFirewall ******************************/
#define k_DampFWErrThresh_MtrNm_f32	TunSet_Ptr_Str->k_DampFWErrThresh_MtrNm_f32
#define k_DampFWFWActiveLPF_Hz_f32	TunSet_Ptr_Str->k_DampFWFWActiveLPF_Hz_f32
#define k_DampFWInCmpNStep_Cnt_u16	TunSet_Ptr_Str->k_DampFWInCmpNStep_Cnt_u16
#define k_DampFWInCmpPStep_Cnt_u16	TunSet_Ptr_Str->k_DampFWInCmpPStep_Cnt_u16
#define k_DampFWInpLimitDamp_MtrNm_f32	TunSet_Ptr_Str->k_DampFWInpLimitDamp_MtrNm_f32
#define k_DampFWNstep_Cnt_u16	TunSet_Ptr_Str->k_DampFWNstep_Cnt_u16
#define k_DampFWPstep_Cnt_u16	TunSet_Ptr_Str->k_DampFWPstep_Cnt_u16
#define k_DmpBoundLPFKn_Hz_f32	TunSet_Ptr_Str->k_DmpBoundLPFKn_Hz_f32
#define t_DampFWAddDampAFWX_MtrRadpS_u11p5	TunSet_Ptr_Str->t_DampFWAddDampAFWX_MtrRadpS_u11p5
#define t_DampFWAddDampAFWY_MtrNm_u5p11	TunSet_Ptr_Str->t_DampFWAddDampAFWY_MtrNm_u5p11
#define t_DampFWAddDampDFWX_MtrRadpS_u11p5	TunSet_Ptr_Str->t_DampFWAddDampDFWX_MtrRadpS_u11p5
#define t_DampFWAddDampDFWY_MtrNm_u5p11	TunSet_Ptr_Str->t_DampFWAddDampDFWY_MtrNm_u5p11
#define t_DampFWDampInrtCmpPNThesh_Cnt_u16	TunSet_Ptr_Str->t_DampFWDampInrtCmpPNThesh_Cnt_u16
#define t_DampFWPNstepThresh_Cnt_u16	TunSet_Ptr_Str->t_DampFWPNstepThresh_Cnt_u16
#define t_DampFWUprBoundX_MtrRadpS_s11p4	TunSet_Ptr_Str->t_DampFWUprBoundX_MtrRadpS_s11p4
#define t_DampFWVehSpd_Kph_u9p7	TunSet_Ptr_Str->t_DampFWVehSpd_Kph_u9p7
#define t2_DampFWUprBoundY_MtrNm_s7p8	TunSet_Ptr_Str->t2_DampFWUprBoundY_MtrNm_s7p8

/******************** FrqDepDmpnInrtCmp, DampingFirewall *********************/
#define k_DmpDecelGain_Uls_f32	TunSet_Ptr_Str->k_DmpDecelGain_Uls_f32
#define k_DmpDecelGainFSlew_UlspS_f32	TunSet_Ptr_Str->k_DmpDecelGainFSlew_UlspS_f32
#define k_DmpGainOffThresh_KphpS_f32	TunSet_Ptr_Str->k_DmpGainOffThresh_KphpS_f32
#define k_DmpGainOnThresh_KphpS_f32	TunSet_Ptr_Str->k_DmpGainOnThresh_KphpS_f32
#define k_InrtCmp_MtrInertia_KgmSq_f32	TunSet_Ptr_Str->k_InrtCmp_MtrInertia_KgmSq_f32
#define k_InrtCmp_TBarVelLPFKn_Hz_f32	TunSet_Ptr_Str->k_InrtCmp_TBarVelLPFKn_Hz_f32

/****************************** EOTActuatorMng *******************************/
#define k_MaxRackTrvl_HwDeg_u12p4	TunSet_Ptr_Str->k_MaxRackTrvl_HwDeg_u12p4

/************************** EOTActuatorMng, EtDmpFw **************************/
#define k_MinRackTrvl_HwDeg_u12p4	TunSet_Ptr_Str->k_MinRackTrvl_HwDeg_u12p4

/********************************* HystComp **********************************/
#define k_CmnSysTrqRatio_HwNmpMtrNm_f32	TunSet_Ptr_Str->k_CmnSysTrqRatio_HwNmpMtrNm_f32
#define k_HysCmpHwTrqLPFKn_Hz_f32	TunSet_Ptr_Str->k_HysCmpHwTrqLPFKn_Hz_f32
#define k_HysCmpLPAstLPFKn_Hz_f32	TunSet_Ptr_Str->k_HysCmpLPAstLPFKn_Hz_f32
#define k_HysFinalOutLPFKn_Hz_f32	TunSet_Ptr_Str->k_HysFinalOutLPFKn_Hz_f32
#define k_HysOutLIm_HwNm_f32	TunSet_Ptr_Str->k_HysOutLIm_HwNm_f32
#define k_HysRevGain_InvHwNm_f32	TunSet_Ptr_Str->k_HysRevGain_InvHwNm_f32
#define k_LpFricIpLim_HwNm_u9p7	TunSet_Ptr_Str->k_LpFricIpLim_HwNm_u9p7
#define t_EffLossTblY_Uls_u4p12	TunSet_Ptr_Str->t_EffLossTblY_Uls_u4p12
#define t_EffOffTblY_HwNm_u9p7	TunSet_Ptr_Str->t_EffOffTblY_HwNm_u9p7
#define t_HysCompCoulFricTempScaleX_DegC_s14p1	TunSet_Ptr_Str->t_HysCompCoulFricTempScaleX_DegC_s14p1
#define t_HysCompCoulFricTempScaleY_HwNm_u9p7	TunSet_Ptr_Str->t_HysCompCoulFricTempScaleY_HwNm_u9p7
#define t_HysCompCoulFricWIRBlendX_MtrNm_u8p8	TunSet_Ptr_Str->t_HysCompCoulFricWIRBlendX_MtrNm_u8p8
#define t_HysCompCoulFricWIRBlendY_Uls_u2p14	TunSet_Ptr_Str->t_HysCompCoulFricWIRBlendY_Uls_u2p14
#define t_HysCompCoulFricY_HwNm_u9p7	TunSet_Ptr_Str->t_HysCompCoulFricY_HwNm_u9p7
#define t_HysCompHysSatY_HwNm_u9p7	TunSet_Ptr_Str->t_HysCompHysSatY_HwNm_u9p7
#define t_HysCompNegHysBlendX_HwNm_u9p7	TunSet_Ptr_Str->t_HysCompNegHysBlendX_HwNm_u9p7
#define t_HysCompNegHysBlendY_Uls_u2p14	TunSet_Ptr_Str->t_HysCompNegHysBlendY_Uls_u2p14
#define t_HysCompNegHysCompX_MtrNm_u8p8	TunSet_Ptr_Str->t_HysCompNegHysCompX_MtrNm_u8p8
#define t_HysCompNegHysCompY_HwNm_u9p7	TunSet_Ptr_Str->t_HysCompNegHysCompY_HwNm_u9p7
#define t_HysRiseTblX_HwNm_u2p14	TunSet_Ptr_Str->t_HysRiseTblX_HwNm_u2p14
#define t_HysRiseTblY_Uls_u2p14	TunSet_Ptr_Str->t_HysRiseTblY_Uls_u2p14
#define t2_HysHwTrqBlndTblX_HwNm_u4p12	TunSet_Ptr_Str->t2_HysHwTrqBlndTblX_HwNm_u4p12
#define t2_HysHwTrqBlndTblY_Uls_u4p12	TunSet_Ptr_Str->t2_HysHwTrqBlndTblY_Uls_u4p12

/********************************** LrnEOT ***********************************/
#define k_AuthorityStartLrn_Uls_f32	TunSet_Ptr_Str->k_AuthorityStartLrn_Uls_f32
#define k_EOTLrnTimer_mS_u16	TunSet_Ptr_Str->k_EOTLrnTimer_mS_u16
#define k_HwTrqEOTLrn_HwNm_f32	TunSet_Ptr_Str->k_HwTrqEOTLrn_HwNm_f32
#define k_MaxRackTrvl_HwDeg_f32	TunSet_Ptr_Str->k_MaxRackTrvl_HwDeg_f32
#define k_MinRackTrvl_HwDeg_f32	TunSet_Ptr_Str->k_MinRackTrvl_HwDeg_f32
#define k_MinResetAuthority_Uls_f32	TunSet_Ptr_Str->k_MinResetAuthority_Uls_f32
#define k_MtrVelEOTLrn_MtrRadpS_f32	TunSet_Ptr_Str->k_MtrVelEOTLrn_MtrRadpS_f32

/********************************** Return ***********************************/
#define t_ReturnTempScaleSclYTbl_Uls_u8p8	TunSet_Ptr_Str->t_ReturnTempScaleSclYTbl_Uls_u8p8
#define t_ReturnTempScaleXTbl_DegC_s11p4	TunSet_Ptr_Str->t_ReturnTempScaleXTbl_DegC_s11p4

/****************************** ReturnFirewall *******************************/
#define t_RtrnFWUprBoundX_HwDeg_s11p4	TunSet_Ptr_Str->t_RtrnFWUprBoundX_HwDeg_s11p4
#define t_RtrnFWVehSpd_Kph_u9p7	TunSet_Ptr_Str->t_RtrnFWVehSpd_Kph_u9p7
#define t2_RtrnFWUprBoundY_MtrNm_s4p11	TunSet_Ptr_Str->t2_RtrnFWUprBoundY_MtrNm_s4p11

/******************************* StabilityComp *******************************/
#define k_StCmpCrosChkEnbl_Uls_lgc	TunSet_Ptr_Str->k_StCmpCrosChkEnbl_Uls_lgc
#define k_StCmpHwTrqLPFKn_Hz_f32	TunSet_Ptr_Str->k_StCmpHwTrqLPFKn_Hz_f32
#define k_StCmpSysCorrThresh_MtrNm_f32	TunSet_Ptr_Str->k_StCmpSysCorrThresh_MtrNm_f32
#define t_StCmpNFK_Str	TunSet_Ptr_Str->t_StCmpNFK_Str

/********************************* TmprlMon **********************************/
#define k_TmprlMonPstepNstep_Cnt_str	TunSet_Ptr_Str->k_TmprlMonPstepNstep_Cnt_str

/********************************** VehDyn ***********************************/
#define k_SysKinRatio_MtrDegpHwDeg_f32	TunSet_Ptr_Str->k_SysKinRatio_MtrDegpHwDeg_f32

/********************************** Assist ***********************************/
#define t2_AsstAsstY0_MtrNm_s4p11	TunPer_Ptr_Str->t2_AsstAsstY0_MtrNm_s4p11
#define t2_AsstAsstY1_MtrNm_s4p11	TunPer_Ptr_Str->t2_AsstAsstY1_MtrNm_s4p11
#define t2_AsstHwtX0_HwNm_u8p8	TunPer_Ptr_Str->t2_AsstHwtX0_HwNm_u8p8
#define t2_AsstHwtX1_HwNm_u8p8	TunPer_Ptr_Str->t2_AsstHwtX1_HwNm_u8p8
#define t2_AsstWIRBlendY_Uls_u2p14	TunPer_Ptr_Str->t2_AsstWIRBlendY_Uls_u2p14
#define t2_AsstWIRBlndX_MtrNm_u5p11	TunPer_Ptr_Str->t2_AsstWIRBlndX_MtrNm_u5p11

/********************************** Damping **********************************/
#define k_HPSOutLimit_MtrNm_f32	TunPer_Ptr_Str->k_HPSOutLimit_MtrNm_f32
#define k_MtrVelDampLPFKn_Hz_f32	TunPer_Ptr_Str->k_MtrVelDampLPFKn_Hz_f32
#define k_QddHwTrqDampKn_Hz_f32	TunPer_Ptr_Str->k_QddHwTrqDampKn_Hz_f32
#define k_QDDMtrVelBckLash_MtrRadpS_f32	TunPer_Ptr_Str->k_QDDMtrVelBckLash_MtrRadpS_f32
#define k_QddMtrVelDampKn_Hz_f32	TunPer_Ptr_Str->k_QddMtrVelDampKn_Hz_f32
#define k_QddSfLFPKn_Hz_f32	TunPer_Ptr_Str->k_QddSfLFPKn_Hz_f32
#define k_Quad13DmpMult_Uls_f32	TunPer_Ptr_Str->k_Quad13DmpMult_Uls_f32
#define k_Quad24DmpMult_Uls_f32	TunPer_Ptr_Str->k_Quad24DmpMult_Uls_f32
#define t_HPSAsstLimY_MtrNm_u4p12	TunPer_Ptr_Str->t_HPSAsstLimY_MtrNm_u4p12
#define t_HPSscaleC1Y_Uls_u4p12	TunPer_Ptr_Str->t_HPSscaleC1Y_Uls_u4p12
#define t_HPSscaleC2Y_Uls_u4p12	TunPer_Ptr_Str->t_HPSscaleC2Y_Uls_u4p12
#define t_HPSscaleC3Y_Uls_u4p12	TunPer_Ptr_Str->t_HPSscaleC3Y_Uls_u4p12
#define t_HPSscaleC4Y_Uls_u4p12	TunPer_Ptr_Str->t_HPSscaleC4Y_Uls_u4p12
#define t_HwTrqDmpTblX_HwNm_u8p8	TunPer_Ptr_Str->t_HwTrqDmpTblX_HwNm_u8p8
#define t_HwTrqDmpTblY_Uls_u1p15	TunPer_Ptr_Str->t_HwTrqDmpTblY_Uls_u1p15
#define t2_MtrVelDmpTblX_MtrRadpS_u12p4	TunPer_Ptr_Str->t2_MtrVelDmpTblX_MtrRadpS_u12p4
#define t2_MtrVelDmpTblY_MtrNm_u5p11	TunPer_Ptr_Str->t2_MtrVelDmpTblY_MtrNm_u5p11

/******************** FrqDepDmpnInrtCmp, DampingFirewall *********************/
#define k_InrtCmp_MtrVel_ScaleFactor_Uls_f32	TunPer_Ptr_Str->k_InrtCmp_MtrVel_ScaleFactor_Uls_f32
#define t_DmpADDCoefX_MtrNm_u4p12	TunPer_Ptr_Str->t_DmpADDCoefX_MtrNm_u4p12
#define t_DmpDecelGainSlewX_MtrRadpS_u11p5	TunPer_Ptr_Str->t_DmpDecelGainSlewX_MtrRadpS_u11p5
#define t_DmpDecelGainSlewY_UlspS_u13p3	TunPer_Ptr_Str->t_DmpDecelGainSlewY_UlspS_u13p3
#define t_DmpFiltKpWIRBlndY_Uls_u2p14	TunPer_Ptr_Str->t_DmpFiltKpWIRBlndY_Uls_u2p14
#define t_FDD_ADDStaticTblY_MtrNmpRadpS_um1p17	TunPer_Ptr_Str->t_FDD_ADDStaticTblY_MtrNmpRadpS_um1p17
#define t_FDD_AttenTblX_MtrRadpS_u12p4	TunPer_Ptr_Str->t_FDD_AttenTblX_MtrRadpS_u12p4
#define t_FDD_AttenTblY_Uls_u8p8	TunPer_Ptr_Str->t_FDD_AttenTblY_Uls_u8p8
#define t_FDD_BlendTblY_Uls_u8p8	TunPer_Ptr_Str->t_FDD_BlendTblY_Uls_u8p8
#define t_InrtCmp_ScaleFactorTblY_Uls_u9p7	TunPer_Ptr_Str->t_InrtCmp_ScaleFactorTblY_Uls_u9p7
#define t_InrtCmp_TBarVel_ScaleFactorTblY_Uls_u9p7	TunPer_Ptr_Str->t_InrtCmp_TBarVel_ScaleFactorTblY_Uls_u9p7
#define t_RIAstWIRBlndTblY_Uls_u2p14	TunPer_Ptr_Str->t_RIAstWIRBlndTblY_Uls_u2p14
#define t_WIRBlndTblX_MtrNm_u8p8	TunPer_Ptr_Str->t_WIRBlndTblX_MtrNm_u8p8
#define t2_FDD_ADDRollingTblYM_MtrNmpRadpS_um1p17	TunPer_Ptr_Str->t2_FDD_ADDRollingTblYM_MtrNmpRadpS_um1p17
#define t2_FDD_FreqTblYM_Hz_u12p4	TunPer_Ptr_Str->t2_FDD_FreqTblYM_Hz_u12p4

/****************************** EOTActuatorMng *******************************/
#define k_EOTDefltPosition_HwDeg_u12p4	TunPer_Ptr_Str->k_EOTDefltPosition_HwDeg_u12p4
#define k_EOTDeltaTrqThrsh_HwNm_u9p7	TunPer_Ptr_Str->k_EOTDeltaTrqThrsh_HwNm_u9p7
#define k_EOTEnterLPFKn_Cnt_u16	TunPer_Ptr_Str->k_EOTEnterLPFKn_Cnt_u16
#define k_EOTExitLPFKn_Cnt_u16	TunPer_Ptr_Str->k_EOTExitLPFKn_Cnt_u16
#define k_EOTImpSpdEn_Kph_u9p7	TunPer_Ptr_Str->k_EOTImpSpdEn_Kph_u9p7
#define k_EOTOriginalImpactandSoftEnd_Cnt_lgc	TunPer_Ptr_Str->k_EOTOriginalImpactandSoftEnd_Cnt_lgc
#define k_EOTPosDepDempFinalSlew_MtrNmpS_T_f32	TunPer_Ptr_Str->k_EOTPosDepDempFinalSlew_MtrNmpS_T_f32
#define k_EOTStateHwTrqLPFKn_Cnt_u16	TunPer_Ptr_Str->k_EOTStateHwTrqLPFKn_Cnt_u16
#define k_PosRampStep_HwDeg_u12p4	TunPer_Ptr_Str->k_PosRampStep_HwDeg_u12p4
#define k_SoftStopEOTEnable_Cnt_lgc	TunPer_Ptr_Str->k_SoftStopEOTEnable_Cnt_lgc
#define k_SpdIptScale_MtrNmpRadpS_u4p12	TunPer_Ptr_Str->k_SpdIptScale_MtrNmpRadpS_u4p12
#define t_EOTDmpVspd_Kph_u9p7	TunPer_Ptr_Str->t_EOTDmpVspd_Kph_u9p7
#define t_EOTEnterGainVspd_Kph_u9p7	TunPer_Ptr_Str->t_EOTEnterGainVspd_Kph_u9p7
#define t_SpdIptTblXTbl_HwDeg_u12p4	TunPer_Ptr_Str->t_SpdIptTblXTbl_HwDeg_u12p4
#define t_SpdIptTblYTbl_MtrRadpS_u12p4	TunPer_Ptr_Str->t_SpdIptTblYTbl_MtrRadpS_u12p4
#define t_TrqTableX_HwNm_u8p8	TunPer_Ptr_Str->t_TrqTableX_HwNm_u8p8
#define t2_EOTEnterGainX_HwDeg_u12p4	TunPer_Ptr_Str->t2_EOTEnterGainX_HwDeg_u12p4
#define t2_EOTEnterGainY_Uls_u1p15	TunPer_Ptr_Str->t2_EOTEnterGainY_Uls_u1p15
#define t2_EOTExPosDepDmpTblY_MtrNmpRadps_u0p16	TunPer_Ptr_Str->t2_EOTExPosDepDmpTblY_MtrNmpRadps_u0p16
#define t2_EOTPosDepDmpTblY_MtrNmpRadpS_u0p16	TunPer_Ptr_Str->t2_EOTPosDepDmpTblY_MtrNmpRadpS_u0p16

/************************** EOTActuatorMng, EtDmpFw **************************/
#define t2_EOTPosDepDmpTblX_HwDeg_u12p4	TunPer_Ptr_Str->t2_EOTPosDepDmpTblX_HwDeg_u12p4

/****************************** HighFreqAssist *******************************/
#define t_LPFKnY_Hz_u7p9	TunPer_Ptr_Str->t_LPFKnY_Hz_u7p9
#define t2_GainY0_MtrNmpHwNm_u3p13	TunPer_Ptr_Str->t2_GainY0_MtrNmpHwNm_u3p13
#define t2_GainY1_MtrNmpHwNm_u3p13	TunPer_Ptr_Str->t2_GainY1_MtrNmpHwNm_u3p13
#define t2_TorqX0_HwNm_u5p11	TunPer_Ptr_Str->t2_TorqX0_HwNm_u5p11
#define t2_TorqX1_HwNm_u5p11	TunPer_Ptr_Str->t2_TorqX1_HwNm_u5p11
#define t2_WIRBlendX_MtrNm_u4p12	TunPer_Ptr_Str->t2_WIRBlendX_MtrNm_u4p12
#define t2_WIRBlendY_Uls_u1p15	TunPer_Ptr_Str->t2_WIRBlendY_Uls_u1p15

/********************************** Return ***********************************/
#define t_HWAuthRetScl_X_Uls_u8p8	TunPer_Ptr_Str->t_HWAuthRetScl_X_Uls_u8p8
#define t_HWAuthRetScl_Y_Uls_u9p7	TunPer_Ptr_Str->t_HWAuthRetScl_Y_Uls_u9p7
#define t_ReturnVSpdTblBS_Kph_u9p7	TunPer_Ptr_Str->t_ReturnVSpdTblBS_Kph_u9p7
#define t2_ReturnPosTblXM_HwDeg_u12p4	TunPer_Ptr_Str->t2_ReturnPosTblXM_HwDeg_u12p4
#define t2_ReturnPosTblYM_MtrNm_u5p11	TunPer_Ptr_Str->t2_ReturnPosTblYM_MtrNm_u5p11
#define t2_ReturnSclTrqTblXM_HwNm_T_u8p8	TunPer_Ptr_Str->t2_ReturnSclTrqTblXM_HwNm_T_u8p8
#define t2_ReturnSclTrqTblYM_Uls_u8p8	TunPer_Ptr_Str->t2_ReturnSclTrqTblYM_Uls_u8p8
#define t2_ReturnSclVelTblXM_HwRadpS_T_u7p9	TunPer_Ptr_Str->t2_ReturnSclVelTblXM_HwRadpS_T_u7p9
#define t2_ReturnSclVelTblYM_Uls_u8p8	TunPer_Ptr_Str->t2_ReturnSclVelTblYM_Uls_u8p8

/******************************* StabilityComp *******************************/
#define t_StCmpADDFBlendX_Uls_u2p14	TunPer_Ptr_Str->t_StCmpADDFBlendX_Uls_u2p14
#define t_StCmpADDFBlendY_Uls_u2p14	TunPer_Ptr_Str->t_StCmpADDFBlendY_Uls_u2p14
#define t_StCmpBlend12Trq_HwNm_u8p8	TunPer_Ptr_Str->t_StCmpBlend12Trq_HwNm_u8p8
#define t_StCmpBlend34Trq_HwNm_u8p8	TunPer_Ptr_Str->t_StCmpBlend34Trq_HwNm_u8p8
#define t_StCmpBlendSpdBS_Kph_u9p7	TunPer_Ptr_Str->t_StCmpBlendSpdBS_Kph_u9p7
#define t2_StCmpBlend02TblY_Uls_u2p14	TunPer_Ptr_Str->t2_StCmpBlend02TblY_Uls_u2p14
#define t2_StCmpBlend04TblY_Uls_u2p14	TunPer_Ptr_Str->t2_StCmpBlend04TblY_Uls_u2p14
#define t2_StCmpBlend12TblY_Uls_u2p14	TunPer_Ptr_Str->t2_StCmpBlend12TblY_Uls_u2p14
#define t2_StCmpBlend34TblY_Uls_u2p14	TunPer_Ptr_Str->t2_StCmpBlend34TblY_Uls_u2p14
#endif

/*********************** Start of Code Footer ************************/

extern P2CONST(TUNING_P_Str, AUTOMATIC, AUTOMATIC) TunPer_Ptr_Str;
extern P2CONST(TUNING_Y_Str, AUTOMATIC, AUTOMATIC) TunSet_Ptr_Str;
extern CONSTP2CONST(TUNING_P_Str, AUTOMATIC, AUTOMATIC) T_TunPersSelectionTbl_Ptr_Str[D_NUMOFTUNSETS_CNT_U16][D_NUMOFPERS_CNT_U16];
extern CONSTP2CONST(TUNING_Y_Str, AUTOMATIC, AUTOMATIC) T_TunSetSelectionTbl_Ptr_Str[D_NUMOFTUNSETS_CNT_U16];

extern CONST(TUNING_Y_Str, CAL_CONST) k_TunSet0_Cnt_Str;
extern CONST(TUNING_Y_Str, CAL_CONST) k_TunSet1_Cnt_Str;
extern CONST(TUNING_Y_Str, CAL_CONST) k_TunSet2_Cnt_Str;
extern CONST(TUNING_Y_Str, CAL_CONST) k_TunSet3_Cnt_Str;
extern CONST(TUNING_Y_Str, CAL_CONST) k_TunSet4_Cnt_Str;
extern CONST(TUNING_Y_Str, CAL_CONST) k_TunSet5_Cnt_Str;
extern CONST(TUNING_Y_Str, CAL_CONST) k_TunSet6_Cnt_Str;
extern CONST(TUNING_Y_Str, CAL_CONST) k_TunSet7_Cnt_Str;

extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet0Per0_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet0Per1_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet1Per0_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet1Per1_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet2Per0_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet2Per1_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet3Per0_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet3Per1_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet4Per0_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet4Per1_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet5Per0_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet5Per1_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet6Per0_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet6Per1_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet7Per0_Cnt_Str;
extern CONST(TUNING_P_Str, CAL_CONST)k_TunSet7Per1_Cnt_Str;








































