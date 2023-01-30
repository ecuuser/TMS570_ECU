/*****************************************************************************
* Copyright 2010 Nexteer Automotive., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name : CalConstants.c
* Module Description: This file contains the definitions of calibration
* constants used in the EPS Software.
* Product : Gen II Plus EA3.0
* Author : Lucas Wendling
*****************************************************************************/
/* Version Control:
* Date Created: Wed Apr 13 12:17:00 2011
* %version: EA3#14 %
* %derived_by: nzdx8v %
* %date_modified: Fri Dec 13 12:51:58 2013 %
*/

/* NOTE:
 * THIS FILE WAS HAND MODIFIED AND NOT GENEREATED.
 * REMOVE THIS COMMENT AFTER INTEGRATION DATA DICTIONARY HAS BEEN CREATED
 */

#include "CalConstants.h"

#define D_NUMOFTUNSETS_CNT_U16 	8U
#define D_NUMOFPERS_CNT_U16 	2U

#define CALCONSTANTS_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

P2CONST(TUNING_P_Str, AUTOMATIC, AUTOMATIC) TunPer_Ptr_Str;
P2CONST(TUNING_Y_Str, AUTOMATIC, AUTOMATIC) TunSet_Ptr_Str;

#define CALCONSTANTS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

/* Put this at end of file
CONSTP2CONST(TUNING_Y_Str, AUTOMATIC, AUTOMATIC) T_TunSetSelectionTbl_Ptr_Str[D_NUMOFTUNSETS_CNT_U16] =
		{	&k_TunSet0_Cnt_Str};

CONSTP2CONST(TUNING_P_Str, AUTOMATIC, AUTOMATIC) T_TunPersSelectionTbl_Ptr_Str[D_NUMOFTUNSETS_CNT_U16][D_NUMOFPERS_CNT_U16] =
		{	{	&k_TunSet0Per0_Cnt_Str
										}};
*/


/*********************** Start of Auto Generated Code ************************/

/****************** File Generated on 10/5/2016 1:15:29 PM *******************/
/***************************** Fiasa 327- Rev 8 ******************************/



/***************************** AbsHwPos_TcI2cVd ******************************/
#pragma DATA_SECTION(k_HWAtoMtrADiffLimit_HwDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HWAtoMtrADiffLimit_HwDeg_f32 = 30.0f;

#pragma DATA_SECTION(k_HwAtoMtrAError_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_HwAtoMtrAError_str = {200, 4, 1};

#pragma DATA_SECTION(k_HwPosAuthorityStep_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HwPosAuthorityStep_Uls_f32 = 0.2f;

#pragma DATA_SECTION(k_HwPosOutputLPFCoeffFc_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HwPosOutputLPFCoeffFc_Hz_f32 = 0.21278f;

#pragma DATA_SECTION(k_HwPosOutputLPFError_HwDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HwPosOutputLPFError_HwDeg_f32 = 5.0f;

#pragma DATA_SECTION(k_I2CHwAuthority_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_I2CHwAuthority_Uls_f32 = 1.0f;

#pragma DATA_SECTION(k_MaxSensorlessAuthority_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxSensorlessAuthority_Uls_f32 = 1.0f;

#pragma DATA_SECTION(k_MaxVehCntrOffDiff_HwDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxVehCntrOffDiff_HwDeg_f32 = 5.0f;

#pragma DATA_SECTION(k_MinSensorlessAuthority_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MinSensorlessAuthority_Uls_f32 = 1.0f;

#pragma DATA_SECTION(k_TurnsCntrAuthority_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TurnsCntrAuthority_Uls_f32 = 1.0f;

#pragma DATA_SECTION(k_UseTurnsCntr_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_UseTurnsCntr_Cnt_lgc = TRUE;

#pragma DATA_SECTION(k_VehCntrOffValidLimit_HwDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VehCntrOffValidLimit_HwDeg_f32 = 1600.0f;


/************************************ Adc ************************************/
#pragma DATA_SECTION(k_MaxADCConvTime_uS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MaxADCConvTime_uS_u16 = 50U;

#pragma DATA_SECTION(k_VbattOVTransIntConfig_Cnt_u32, ".FlashCalSeg");
CONST(uint32, CAL_CONST) k_VbattOVTransIntConfig_Cnt_u32 = 190988293UL;


/********************************** Assist ***********************************/
#pragma DATA_SECTION(t_AsstThermSclX_Cnt_u16p0, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_AsstThermSclX_Cnt_u16p0[2] = 
	{FPM_InitFixedPoint_m(75.0, u16p0_T),
	 FPM_InitFixedPoint_m(100.0, u16p0_T)};

#pragma DATA_SECTION(t_AsstThermSclY_Uls_u2p14, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_AsstThermSclY_Uls_u2p14[2] = 
	{FPM_InitFixedPoint_m(1.0, u2p14_T), FPM_InitFixedPoint_m(1.0, u2p14_T)};


/****************************** AssistFirewall *******************************/
#pragma DATA_SECTION(k_AsstFWInpLimitHysComp_MtrNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AsstFWInpLimitHysComp_MtrNm_f32 = 8.8f;


/********************************* AstLmt_CM *********************************/
#pragma DATA_SECTION(k_SumLimPlCmpLimit_MtrNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SumLimPlCmpLimit_MtrNm_f32 = 8.8f;


/****************************** BatteryVoltage *******************************/
#pragma DATA_SECTION(k_MaxBattVoltDiff_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxBattVoltDiff_Volts_f32 = 0.5f;

#pragma DATA_SECTION(k_VecuCorrLim_Cnt_Str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_VecuCorrLim_Cnt_Str = {120,1,3};

#pragma DATA_SECTION(k_VecuVbatCorrLim_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VecuVbatCorrLim_Volts_f32 = 0.73f;

#pragma DATA_SECTION(k_VswitchCorrLim_Cnt_Str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_VswitchCorrLim_Cnt_Str = {120,1,3};

#pragma DATA_SECTION(k_VswitchCorrLim_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VswitchCorrLim_Volts_f32 = 0.73f;


/************************** BatteryVoltage, BkCpPc ***************************/
#pragma DATA_SECTION(k_MaxSwitchedVolt_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxSwitchedVolt_Volts_f32 = 16.0f;


/********************************** BkCpPc ***********************************/
#pragma DATA_SECTION(k_ChargeMinDeltaExtOp_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_ChargeMinDeltaExtOp_Volt_f32 = 5.0f;

#pragma DATA_SECTION(k_ChargeMinDeltaNonOp_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_ChargeMinDeltaNonOp_Volt_f32 = 0.0f;

#pragma DATA_SECTION(k_ChargeMinDeltaNormlOp_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_ChargeMinDeltaNormlOp_Volt_f32 = 6.0f;

#pragma DATA_SECTION(k_ChargePumpDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_ChargePumpDiag_Cnt_str = {100, 4, 1};

#pragma DATA_SECTION(k_MaxDischEst_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxDischEst_Uls_f32 = 0.99f;

#pragma DATA_SECTION(k_MinDischEst_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MinDischEst_Uls_f32 = 0.98f;

#pragma DATA_SECTION(k_MtrMotionThresh_MtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrMotionThresh_MtrRadpS_f32 = 100.0f;

#pragma DATA_SECTION(k_OVERRIDESIGDIAGOpenThresh_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_OVERRIDESIGDIAGOpenThresh_Volts_f32 = 0.5f;

#pragma DATA_SECTION(k_PMOSDIAGOpenThresh_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_PMOSDIAGOpenThresh_Volts_f32 = 0.5f;

#pragma DATA_SECTION(k_PMOSTError_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_PMOSTError_mS_u16 = 50U;

#pragma DATA_SECTION(k_PMOSVError_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_PMOSVError_Volts_f32 = 1.0f;

#pragma DATA_SECTION(k_PrechargeThresh_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_PrechargeThresh_mS_u16 = 400U;

#pragma DATA_SECTION(k_PwrDiscCloseThresh_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_PwrDiscCloseThresh_Volts_f32 = 0.5f;

#pragma DATA_SECTION(k_PwrDiscOpenThresh_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_PwrDiscOpenThresh_Volts_f32 = 2.0f;

#pragma DATA_SECTION(k_VbattSwitchThreshExNorm_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VbattSwitchThreshExNorm_Volt_f32 = 8.0f;

#pragma DATA_SECTION(k_VbattSwitchThreshNonExt_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VbattSwitchThreshNonExt_Volt_f32 = 7.0f;

#pragma DATA_SECTION(k_VerifyPwrDiscCloseDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_VerifyPwrDiscCloseDiag_Cnt_str = {200,4,
	2};

#pragma DATA_SECTION(k_VerifyPwrDiscCloseThresh_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_VerifyPwrDiscCloseThresh_mS_u16 = 100U;

#pragma DATA_SECTION(k_VerifyPwrDiscOpenThresh_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_VerifyPwrDiscOpenThresh_mS_u16 = 100U;

#pragma DATA_SECTION(k_VswitchDeltaThresh_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VswitchDeltaThresh_Volts_f32 = 0.5f;

#pragma DATA_SECTION(k_WaitForSqrWaveThresh_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_WaitForSqrWaveThresh_mS_u16 = 100U;


/********************************** BVDiag ***********************************/
#pragma DATA_SECTION(k_BattDiagUvMax_Volt_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_BattDiagUvMax_Volt_u10p6 = 
	FPM_InitFixedPoint_m(10.0, u10p6_T);

#pragma DATA_SECTION(k_BattDiagUvMin_Volt_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_BattDiagUvMin_Volt_u10p6 = 
	FPM_InitFixedPoint_m(9.0, u10p6_T);

#pragma DATA_SECTION(k_BattUvRecMax_Volt_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_BattUvRecMax_Volt_u10p6 = 
	FPM_InitFixedPoint_m(16.5, u10p6_T);

#pragma DATA_SECTION(k_LowDetect_ms_u16p0, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_LowDetect_ms_u16p0 = 
	FPM_InitFixedPoint_m(1000.0, u16p0_T);

#pragma DATA_SECTION(k_LowDetect_Volts_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_LowDetect_Volts_u10p6 = 
	FPM_InitFixedPoint_m(9.0, u10p6_T);

#pragma DATA_SECTION(k_LowNotDetect_ms_u16p0, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_LowNotDetect_ms_u16p0 = 
	FPM_InitFixedPoint_m(600.0, u16p0_T);

#pragma DATA_SECTION(k_LowNotDetect_Volts_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_LowNotDetect_Volts_u10p6 = 
	FPM_InitFixedPoint_m(9.0, u10p6_T);

#pragma DATA_SECTION(k_MSALowDetect_ms_u16p0, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MSALowDetect_ms_u16p0 = 
	FPM_InitFixedPoint_m(1000.0, u16p0_T);

#pragma DATA_SECTION(k_MSALowDetect_Volts_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MSALowDetect_Volts_u10p6 = 
	FPM_InitFixedPoint_m(9.0, u10p6_T);

#pragma DATA_SECTION(k_MSALowNotDetect_ms_u16p0, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MSALowNotDetect_ms_u16p0 = 
	FPM_InitFixedPoint_m(600.0, u16p0_T);

#pragma DATA_SECTION(k_MSALowNotDetect_Volts_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MSALowNotDetect_Volts_u10p6 = 
	FPM_InitFixedPoint_m(9.0, u10p6_T);

#pragma DATA_SECTION(k_OvDetect_ms_u16p0, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_OvDetect_ms_u16p0 = 
	FPM_InitFixedPoint_m(1000.0, u16p0_T);

#pragma DATA_SECTION(k_OvDetect_Volts_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_OvDetect_Volts_u10p6 = 
	FPM_InitFixedPoint_m(18.0, u10p6_T);

#pragma DATA_SECTION(k_OvNotDetect_ms_u16p0, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_OvNotDetect_ms_u16p0 = 
	FPM_InitFixedPoint_m(600.0, u16p0_T);

#pragma DATA_SECTION(k_OvNotDetect_Volts_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_OvNotDetect_Volts_u10p6 = 
	FPM_InitFixedPoint_m(18.0, u10p6_T);

#pragma DATA_SECTION(k_UvDetect_ms_u16p0, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_UvDetect_ms_u16p0 = 
	FPM_InitFixedPoint_m(15000.0, u16p0_T);

#pragma DATA_SECTION(k_UvNotDetect_ms_u16p0, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_UvNotDetect_ms_u16p0 = 
	FPM_InitFixedPoint_m(15000.0, u16p0_T);


/********************************* CmMtrCurr *********************************/
#pragma DATA_SECTION(k_CurrCorrErrFiltFc_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CurrCorrErrFiltFc_Hz_f32 = 1.7953429f;

#pragma DATA_SECTION(k_CurrCorrErrThresh_Amps_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CurrCorrErrThresh_Amps_f32 = 0.0f;

#pragma DATA_SECTION(k_CurrGainNumerator_Amps_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CurrGainNumerator_Amps_f32 = 45.0f;

#pragma DATA_SECTION(k_CurrOffGainKn_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_CurrOffGainKn_Cnt_u16 = 1462U;

#pragma DATA_SECTION(k_CurrOffNoofAvg_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_CurrOffNoofAvg_Cnt_u16 = 900U;

#pragma DATA_SECTION(k_MaxCurrOffMtrVel_RadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxCurrOffMtrVel_RadpS_f32 = 10.0f;

#pragma DATA_SECTION(k_MtrCurrEOLMaxGain_AmpspVolts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrCurrEOLMaxGain_AmpspVolts_f32 = 77.0f;

#pragma DATA_SECTION(k_MtrCurrEOLMaxOffset_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrCurrEOLMaxOffset_Volts_f32 = 2.8f;

#pragma DATA_SECTION(k_MtrCurrEOLMinGain_AmpspVolts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrCurrEOLMinGain_AmpspVolts_f32 = 67.0f;

#pragma DATA_SECTION(k_MtrCurrEOLMinOffset_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrCurrEOLMinOffset_Volts_f32 = 2.2f;

#pragma DATA_SECTION(k_MtrCurrOffLoComOff_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MtrCurrOffLoComOff_Cnt_u16 = 500U;

#pragma DATA_SECTION(k_MtrPosComputDelay_Sec_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrPosComputDelay_Sec_f32 = 0.000096f;


/******************************** CMS_Common *********************************/
#pragma DATA_SECTION(k_CMSGotoPosPol_Cnt_s08, ".FlashCalSeg");
CONST(sint8, CAL_CONST) k_CMSGotoPosPol_Cnt_s08 = 1;

#pragma DATA_SECTION(k_F00FHandsOnThres_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_F00FHandsOnThres_HwNm_f32 = 0.5f;

#pragma DATA_SECTION(k_NxtrSrvcHandsOnTime_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_NxtrSrvcHandsOnTime_mS_u16 = 5000U;

#pragma DATA_SECTION(k_NxtrSrvcPosTrajHoldTime_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_NxtrSrvcPosTrajHoldTime_mS_u16 = 5000U;

#pragma DATA_SECTION(k_NxtrSrvcPosTrajThres_HwDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_NxtrSrvcPosTrajThres_HwDeg_f32 = 2.0f;


/********************************* CMS_Fiasa *********************************/
#pragma DATA_SECTION(k_CalRelNum_Cnt_u8, ".FlashCalSeg");
CONST(uint8, CAL_CONST) k_CalRelNum_Cnt_u8[12] = {'D','e','f','a','u','l','t',
	' ','C','a','l','s'};

#pragma DATA_SECTION(k_SrvcHwTrqLimit_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SrvcHwTrqLimit_HwNm_f32 = 1.0f;

#pragma DATA_SECTION(k_SrvcVehSpdLimit_Kph_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SrvcVehSpdLimit_Kph_f32 = 10.0f;


/********************************* ComplErr **********************************/
#pragma DATA_SECTION(t_CompErrMtrPosNonLinComplDepTbl_HwDegpMtrNm_u8p8, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_CompErrMtrPosNonLinComplDepTbl_HwDegpMtrNm_u8p8[6] = 
	{FPM_InitFixedPoint_m(0.0, u8p8_T), FPM_InitFixedPoint_m(0.0, u8p8_T),
	 FPM_InitFixedPoint_m(0.0, u8p8_T), FPM_InitFixedPoint_m(0.0, u8p8_T),
	 FPM_InitFixedPoint_m(0.0, u8p8_T), FPM_InitFixedPoint_m(0.0, u8p8_T)};

#pragma DATA_SECTION(t_ComplErrMtrPosNonLinComplIndTbl_MtrNm_u5p11, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_ComplErrMtrPosNonLinComplIndTbl_MtrNm_u5p11[6] = 
	{FPM_InitFixedPoint_m(0.0, u5p11_T), FPM_InitFixedPoint_m(0.5, u5p11_T),
	 FPM_InitFixedPoint_m(1.5, u5p11_T), FPM_InitFixedPoint_m(3.0, u5p11_T),
	 FPM_InitFixedPoint_m(5.0, u5p11_T), FPM_InitFixedPoint_m(8.0, u5p11_T)};


/******************************* CtrldDisShtdn *******************************/
#pragma DATA_SECTION(k_CntrlDmpRampEnd_Uls_u8p8, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_CntrlDmpRampEnd_Uls_u8p8 = 
	FPM_InitFixedPoint_m(0.0, u8p8_T);

#pragma DATA_SECTION(k_CtrlDmpTmrBkptOne_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_CtrlDmpTmrBkptOne_mS_u16 = 100U;

#pragma DATA_SECTION(k_CtrlDmpTmrBkptTwo_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_CtrlDmpTmrBkptTwo_mS_u16 = 1000U;

#pragma DATA_SECTION(k_CtrlDpVelThr_MtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CtrlDpVelThr_MtrRadpS_f32 = 2.3f;

#pragma DATA_SECTION(k_F2Damping_MtrNmpRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_F2Damping_MtrNmpRadpS_f32 = 0.036f;

#pragma DATA_SECTION(k_MaxCtrlDmpLimit_MtrNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxCtrlDmpLimit_MtrNm_f32 = 3.0f;


/********************************* CtrlTemp **********************************/
#pragma DATA_SECTION(k_CustDiagAmbLowEnable_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_CustDiagAmbLowEnable_Cnt_lgc = FALSE;

#pragma DATA_SECTION(k_CustDiagAmbLowThresh_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CustDiagAmbLowThresh_DegC_f32 = -30.0f;

#pragma DATA_SECTION(k_TempSensDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_TempSensDiag_Cnt_str = {40,2,1};

#pragma DATA_SECTION(k_TempSensHighLimit_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TempSensHighLimit_DegC_f32 = 150.0f;

#pragma DATA_SECTION(k_TempSensLowLimit_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TempSensLowLimit_DegC_f32 = -40.0f;

#pragma DATA_SECTION(k_TempSnsrDefVal_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TempSnsrDefVal_DegC_f32 = 60.0f;

#pragma DATA_SECTION(k_TempSnsrFiltDft_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_TempSnsrFiltDft_Cnt_lgc = FALSE;

#pragma DATA_SECTION(k_TempSnsrLPFKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TempSnsrLPFKn_Hz_f32 = 8.0f;

#pragma DATA_SECTION(k_TempSnsrOffset_Volts_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TempSnsrOffset_Volts_f32 = 0.5f;

#pragma DATA_SECTION(k_TempSnsrScaling_DegpVolt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TempSnsrScaling_DegpVolt_f32 = 100.0f;


/********************************** Damping **********************************/
#pragma DATA_SECTION(k_HPSbaseC1_MtrNmpMtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HPSbaseC1_MtrNmpMtrRadpS_f32 = 0.000521083f;

#pragma DATA_SECTION(k_HPSbaseC2_MtrNmpMtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HPSbaseC2_MtrNmpMtrRadpS_f32 = 0.0000288893f;

#pragma DATA_SECTION(k_HPSbaseC3_MtrNmpMtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HPSbaseC3_MtrNmpMtrRadpS_f32 = 0.00618654f;

#pragma DATA_SECTION(k_HPSbaseC4_MtrNmpMtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HPSbaseC4_MtrNmpMtrRadpS_f32 = 0.00000956832f;

#pragma DATA_SECTION(k_QDDHwTrqBckLash_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_QDDHwTrqBckLash_HwNm_f32 = 0.0f;


/****************************** DampingFirewall ******************************/
#pragma DATA_SECTION(k_DampFWVBICLPF_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_DampFWVBICLPF_Hz_f32 = 10.0f;

#pragma DATA_SECTION(t_DampFWDefltDampX_MtrRadpS_u11p5, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_DampFWDefltDampX_MtrRadpS_u11p5[11] = 
	{FPM_InitFixedPoint_m(0.0, u11p5_T), FPM_InitFixedPoint_m(10.0, u11p5_T),
	 FPM_InitFixedPoint_m(25.0, u11p5_T),
	 FPM_InitFixedPoint_m(50.0, u11p5_T),
	 FPM_InitFixedPoint_m(100.0, u11p5_T),
	 FPM_InitFixedPoint_m(150.0, u11p5_T),
	 FPM_InitFixedPoint_m(200.0, u11p5_T),
	 FPM_InitFixedPoint_m(250.0, u11p5_T),
	 FPM_InitFixedPoint_m(300.0, u11p5_T),
	 FPM_InitFixedPoint_m(350.0, u11p5_T),
	 FPM_InitFixedPoint_m(400.0, u11p5_T)};

#pragma DATA_SECTION(t_DampFWDefltDampY_MtrNm_u5p11, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_DampFWDefltDampY_MtrNm_u5p11[11] = 
	{FPM_InitFixedPoint_m(0.0, u5p11_T), FPM_InitFixedPoint_m(0.05, u5p11_T),
	 FPM_InitFixedPoint_m(0.1, u5p11_T), FPM_InitFixedPoint_m(0.15, u5p11_T),
	 FPM_InitFixedPoint_m(0.5, u5p11_T), FPM_InitFixedPoint_m(1.4, u5p11_T),
	 FPM_InitFixedPoint_m(2.5, u5p11_T), FPM_InitFixedPoint_m(4.0, u5p11_T),
	 FPM_InitFixedPoint_m(6.0, u5p11_T), FPM_InitFixedPoint_m(10.0, u5p11_T),
	 FPM_InitFixedPoint_m(14.0, u5p11_T)};


/******************** FrqDepDmpnInrtCmp, DampingFirewall *********************/
#pragma DATA_SECTION(k_CmnSysKinRatio_MtrDegpHwDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CmnSysKinRatio_MtrDegpHwDeg_f32 = 22.0f;

#pragma DATA_SECTION(k_CmnTbarStiff_NmpDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CmnTbarStiff_NmpDeg_f32 = 2.5f;


/********************************** DiagMgr **********************************/
#pragma DATA_SECTION(k_FltRmpRate_UlspmS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_FltRmpRate_UlspmS_f32[13] = { 0.0005f, 0.0005f,
	 0.0005f, 0.0005f, 0.0005f, 0.0005f, 0.0005f, 0.0005f, 0.0005f, 0.0005f,
	 0.0005f, 0.0005f, 0.0005f };

#pragma DATA_SECTION(k_FltRspTbl_Cnt_str, ".FlashCalSeg");
CONST(FltRsp_Str, CAL_CONST) k_FltRspTbl_Cnt_str[512] = { {0x000000, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0},
	 {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F, 0}, {0xC0000F,
	 0}, {0xC0000F, 0}, {0xC0000F, 0}  };

#pragma DATA_SECTION(t_BlkBoxGrp_Ptr_u32, ".FlashCalSeg");
CONST(uint32* const, CAL_CONST) t_BlkBoxGrp_Ptr_u32[7][3] = {{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

#pragma DATA_SECTION(t_LatchFaults_Cnt_str, ".FlashCalSeg");
CONST(NTCLatch_Str, CAL_CONST) t_LatchFaults_Cnt_str[8] = {{0x000,{65535,1,
	1}},{0x000,{65535,1,1}},{0x000,{65535,1,1}},{0x000,{65535,1,1}},{0x000,
	{65535,1,1}},{0x000,{65535,1,1}},{0x000,{65535,1,1}},{0x000,{65535,1,1}}};

#pragma DATA_SECTION(t_SortedNTCs_Cnt_enum, ".FlashCalSeg");
CONST(NTCNumber, CAL_CONST) t_SortedNTCs_Cnt_enum[256] = { 0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
	0x000 };


/********************************** DiagSvc **********************************/
#pragma DATA_SECTION(k_HwTrqResetThresh_Kph_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HwTrqResetThresh_Kph_f32 = 5.0f;

#pragma DATA_SECTION(k_VehSpdResetThresh_Kph_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VehSpdResetThresh_Kph_f32 = 10.0f;

#pragma DATA_SECTION(k_ProxiConfigTunSet_Cnt_u08, ".FlashCalSeg");
CONST(uint8, CAL_CONST) k_ProxiConfigTunSet_Cnt_u08[8][3] = {{52,3,0}, {52,3,
	1}, {52,4,1}, {52,4,2}, {92,1,1}, {92,3,3}, {0,0,4}, {0,0,4}};


/******************************* DigHwTrqSENT ********************************/
#pragma DATA_SECTION(k_CMCLPFOutLim_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CMCLPFOutLim_HwNm_f32 = 0.544009001f;

#pragma DATA_SECTION(k_HwTrqLPFFc_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HwTrqLPFFc_Hz_f32 = 250.0f;

#pragma DATA_SECTION(k_MaxHwTrqTrim_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxHwTrqTrim_HwNm_f32 = 0.54348f;

#pragma DATA_SECTION(k_T1T2CMCLPFEnable_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_T1T2CMCLPFEnable_HwNm_f32 = 0.270677649f;

#pragma DATA_SECTION(k_T1T2CMCLPFFc_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_T1T2CMCLPFFc_Hz_f32 = 0.019894368f;

#pragma DATA_SECTION(k_T1T2SSLim_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_T1T2SSLim_HwNm_f32 = 2.609375f;

#pragma DATA_SECTION(k_T1T2SSLPFFc_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_T1T2SSLPFFc_Hz_f32 = 0.019894368f;

#pragma DATA_SECTION(k_T1T2TransFltLim_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_T1T2TransFltLim_HwNm_f32 = 2.609375f;

#pragma DATA_SECTION(k_T1vsT2TrqSum_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_T1vsT2TrqSum_HwNm_f32 = 19.021739f;

#pragma DATA_SECTION(t_T1T2DepTrsTimecon_Hz_u6p10, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_T1T2DepTrsTimecon_Hz_u6p10[17] = 
	{ FPM_InitFixedPoint_m(16.019514175835, u6p10_T),
	 FPM_InitFixedPoint_m(16.019514175835, u6p10_T),
	 FPM_InitFixedPoint_m(16.019514175835, u6p10_T),
	 FPM_InitFixedPoint_m(16.019514175835, u6p10_T),
	 FPM_InitFixedPoint_m(16.019514175835, u6p10_T),
	 FPM_InitFixedPoint_m(10.553716911786, u6p10_T),
	 FPM_InitFixedPoint_m(7.96872965761939, u6p10_T),
	 FPM_InitFixedPoint_m(6.42717395292957, u6p10_T),
	 FPM_InitFixedPoint_m(5.39722706185968, u6p10_T),
	 FPM_InitFixedPoint_m(4.65376910940811, u6p10_T),
	 FPM_InitFixedPoint_m(4.09226390842641, u6p10_T),
	 FPM_InitFixedPoint_m(3.65389865074024, u6p10_T),
	 FPM_InitFixedPoint_m(3.2999820535005, u6p10_T),
	 FPM_InitFixedPoint_m(3.00893568853267, u6p10_T),
	 FPM_InitFixedPoint_m(2.76529899113485, u6p10_T),
	 FPM_InitFixedPoint_m(2.55889942858302, u6p10_T),
	 FPM_InitFixedPoint_m(2.38077029677756, u6p10_T)};

#pragma DATA_SECTION(t_T1T2IndTrsTimecon_HwNm_u5p11, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_T1T2IndTrsTimecon_HwNm_u5p11[17] = 
	{ FPM_InitFixedPoint_m(0.0, u5p11_T),
	FPM_InitFixedPoint_m(0.870414402173913, u5p11_T),
	FPM_InitFixedPoint_m(1.73817510190217, u5p11_T),
	FPM_InitFixedPoint_m(2.60858950407609, u5p11_T),
	FPM_InitFixedPoint_m(3.47900390625, u5p11_T),
	FPM_InitFixedPoint_m(4.34676460597826, u5p11_T),
	FPM_InitFixedPoint_m(5.21717900815217, u5p11_T),
	FPM_InitFixedPoint_m(6.08759341032609, u5p11_T),
	FPM_InitFixedPoint_m(6.95535411005435, u5p11_T),
	FPM_InitFixedPoint_m(7.82576851222826, u5p11_T),
	FPM_InitFixedPoint_m(8.69618291440217, u5p11_T),
	FPM_InitFixedPoint_m(9.56394361413043, u5p11_T),
	FPM_InitFixedPoint_m(10.4343580163043, u5p11_T),
	FPM_InitFixedPoint_m(11.3047724184783, u5p11_T),
	FPM_InitFixedPoint_m(12.1751868206522, u5p11_T),
	FPM_InitFixedPoint_m(13.0429475203804, u5p11_T),
	FPM_InitFixedPoint_m(13.9133619225543, u5p11_T)};


/********************************** DigMSB ***********************************/
#pragma DATA_SECTION(k_Die1RPMMode_Cnt_u08, ".FlashCalSeg");
CONST(uint8, CAL_CONST) k_Die1RPMMode_Cnt_u08 = 0;

#pragma DATA_SECTION(k_Die1vsDie2TrnsCntrThresh_Deg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_Die1vsDie2TrnsCntrThresh_Deg_f32 = 45.0f;

#pragma DATA_SECTION(k_Die2Offset_Rev_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_Die2Offset_Rev_u3p13 = 
	FPM_InitFixedPoint_m(0.5, u3p13_T);

#pragma DATA_SECTION(k_Die2RPMMode_Cnt_u08, ".FlashCalSeg");
CONST(uint8, CAL_CONST) k_Die2RPMMode_Cnt_u08 = 0;

#pragma DATA_SECTION(k_DigMSBErrorRegGenMask_Cnt_u08, ".FlashCalSeg");
CONST(uint8, CAL_CONST) k_DigMSBErrorRegGenMask_Cnt_u08 = 127;

#pragma DATA_SECTION(k_DigMSBParity_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_DigMSBParity_Cnt_str = {256,4,1};

#pragma DATA_SECTION(k_DigMSBTCRunTimeParity_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_DigMSBTCRunTimeParity_Cnt_str = {256,4,1};

#pragma DATA_SECTION(k_ErrorRegTCAcc_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_ErrorRegTCAcc_Cnt_str = {256,4,1};

#pragma DATA_SECTION(k_ErrorRegTCMask_Cnt_u08, ".FlashCalSeg");
CONST(uint8, CAL_CONST) k_ErrorRegTCMask_Cnt_u08 = 127;

#pragma DATA_SECTION(k_ErrorRegVehMask_Cnt_u08, ".FlashCalSeg");
CONST(uint8, CAL_CONST) k_ErrorRegVehMask_Cnt_u08 = 127;

#pragma DATA_SECTION(k_MtrPos1vsMtrPos2Diag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_MtrPos1vsMtrPos2Diag_Cnt_str = {256,4,1};

#pragma DATA_SECTION(k_MtrPos1vsMtrPos2Thresh_Rev_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MtrPos1vsMtrPos2Thresh_Rev_u3p13 = 
	FPM_InitFixedPoint_m(0.194444444, u3p13_T);

#pragma DATA_SECTION(k_TurnsCntrOffset_Rev_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TurnsCntrOffset_Rev_f32 = 0.0f;


/********************************** ElePwr ***********************************/
#pragma DATA_SECTION(k_CntlrInResist_Ohm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CntlrInResist_Ohm_f32 = 0.005f;

#pragma DATA_SECTION(k_PstcPowerLoss_Watt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_PstcPowerLoss_Watt_f32 = 10.0f;


/************************** EOTActuatorMng, EtDmpFw **************************/
#pragma DATA_SECTION(k_EOTActiveRegionBypassMaxThresh_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_EOTActiveRegionBypassMaxThresh_Uls_f32 = 0.0f;

#pragma DATA_SECTION(k_EOTDynConf_Uls_u8p8, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_EOTDynConf_Uls_u8p8 = 
	FPM_InitFixedPoint_m(0.80078125, u8p8_T);


/*********************************** ePWM ************************************/
#pragma DATA_SECTION(k_ADCTrig1Offset_Cnt_s16, ".FlashCalSeg");
CONST(sint16, CAL_CONST) k_ADCTrig1Offset_Cnt_s16 = 200;

#pragma DATA_SECTION(k_HwTrqDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_HwTrqDiag_Cnt_str = {128,10,1};

#pragma DATA_SECTION(k_PwmDeadBand_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_PwmDeadBand_Cnt_u16 = 100U;

#pragma DATA_SECTION(k_PwmRelay_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_PwmRelay_Cnt_u16 = 2500U;

#pragma DATA_SECTION(k_SENTSyncDelay_Cnt_u32, ".FlashCalSeg");
CONST(uint32, CAL_CONST) k_SENTSyncDelay_Cnt_u32 = 148000UL;

#pragma DATA_SECTION(k_SENTSyncTrgMin_Cnt_u32, ".FlashCalSeg");
CONST(uint32, CAL_CONST) k_SENTSyncTrgMin_Cnt_u32 = 20000UL;

#pragma DATA_SECTION(k_SPI1mOff_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_SPI1mOff_Cnt_u16 = 700U;

#pragma DATA_SECTION(k_SPI50UOff_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_SPI50UOff_Cnt_u16 = 1152U;


/********************************** EtDmpFw **********************************/
#pragma DATA_SECTION(k_EOTDmpFWInactiveLim_MtrNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_EOTDmpFWInactiveLim_MtrNm_f32 = 8.8f;

#pragma DATA_SECTION(t_EOTDmpFWActiveBoundX_MtrRadpS_s11p4, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t_EOTDmpFWActiveBoundX_MtrRadpS_s11p4[5] = 
	{FPM_InitFixedPoint_m(-700.0, s11p4_T),
	 FPM_InitFixedPoint_m(-5.0, s11p4_T),
	 FPM_InitFixedPoint_m(10.0, s11p4_T),
	 FPM_InitFixedPoint_m(50.0, s11p4_T),
	 FPM_InitFixedPoint_m(700.0, s11p4_T)};

#pragma DATA_SECTION(t_EOTDmpFWVehSpd_Kph_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_EOTDmpFWVehSpd_Kph_u9p7[4] = 
	{FPM_InitFixedPoint_m(0.0, u9p7_T), FPM_InitFixedPoint_m(20.0, u9p7_T),
	 FPM_InitFixedPoint_m(40.0, u9p7_T), FPM_InitFixedPoint_m(60.0, u9p7_T)};

#pragma DATA_SECTION(t2_EOTDmpFWActiveBoundY_MtrNm_s7p8, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_EOTDmpFWActiveBoundY_MtrNm_s7p8[4][5] = 
	{{FPM_InitFixedPoint_m(8.8, s7p8_T),FPM_InitFixedPoint_m(8.8, s7p8_T),
	FPM_InitFixedPoint_m(8.8, s7p8_T),FPM_InitFixedPoint_m(8.8, s7p8_T),
	FPM_InitFixedPoint_m(8.8, s7p8_T)},{FPM_InitFixedPoint_m(8.8, s7p8_T),
	FPM_InitFixedPoint_m(8.8, s7p8_T),FPM_InitFixedPoint_m(8.8, s7p8_T),
	FPM_InitFixedPoint_m(8.8, s7p8_T),FPM_InitFixedPoint_m(8.8, s7p8_T)},
	{FPM_InitFixedPoint_m(8.8, s7p8_T),FPM_InitFixedPoint_m(8.8, s7p8_T),
	FPM_InitFixedPoint_m(8.8, s7p8_T),FPM_InitFixedPoint_m(8.8, s7p8_T),
	FPM_InitFixedPoint_m(8.8, s7p8_T)},{FPM_InitFixedPoint_m(8.8, s7p8_T),
	FPM_InitFixedPoint_m(8.8, s7p8_T),FPM_InitFixedPoint_m(8.8, s7p8_T),
	FPM_InitFixedPoint_m(8.8, s7p8_T),FPM_InitFixedPoint_m(8.8, s7p8_T)}};


/******************************** HiLoadStall ********************************/
#pragma DATA_SECTION(k_EOTThrmPrtLPFKn_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_EOTThrmPrtLPFKn_Cnt_u16 = 1130U;

#pragma DATA_SECTION(k_EOTThrmSlwLmtStp_MtrNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_EOTThrmSlwLmtStp_MtrNm_f32 = 0.1015625f;

#pragma DATA_SECTION(t_EOTThrmDpntTbl_MtrNm_u8p8, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_EOTThrmDpntTbl_MtrNm_u8p8[4] = 
	{ FPM_InitFixedPoint_m(8.5, u8p8_T), FPM_InitFixedPoint_m(8.0, u8p8_T),
	 FPM_InitFixedPoint_m(7.5, u8p8_T), FPM_InitFixedPoint_m(7.0, u8p8_T) };

#pragma DATA_SECTION(t_EOTThrmIndptTbl_MtrNm_u8p8, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_EOTThrmIndptTbl_MtrNm_u8p8[4] = 
	{ FPM_InitFixedPoint_m(5.75, u8p8_T), FPM_InitFixedPoint_m(6.22, u8p8_T),
	 FPM_InitFixedPoint_m(6.67, u8p8_T),
	 FPM_InitFixedPoint_m(7.125, u8p8_T) };


/************************ HiLoadStall, ThrmDutyCycle *************************/
#pragma DATA_SECTION(k_AbsMtrVelBkt_MtrRadps_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AbsMtrVelBkt_MtrRadps_f32 = 1.375f;


/**************************** IoHwAbstractionUsr *****************************/
#pragma DATA_SECTION(k_SlowADCDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_SlowADCDiag_Cnt_str = {10, 1, 1};

#pragma DATA_SECTION(k_TempSensorOffset_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TempSensorOffset_Volt_f32 = 0.0f;

#pragma DATA_SECTION(k_TempSensorScale_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TempSensorScale_Uls_f32 = 1.0f;

#pragma DATA_SECTION(k_VbattScale_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VbattScale_Uls_f32 = 6.74712643678f;

#pragma DATA_SECTION(k_VrefDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_VrefDiag_Cnt_str = {100, 4, 1};

#pragma DATA_SECTION(k_VrefMax_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VrefMax_Volt_f32 = 3.0f;

#pragma DATA_SECTION(k_VrefMin_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VrefMin_Volt_f32 = 2.0f;

#pragma DATA_SECTION(k_VrefScale_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VrefScale_Uls_f32 = 1.0f;

#pragma DATA_SECTION(k_VswitchScale_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VswitchScale_Uls_f32 = 3.36966824645f;

#pragma DATA_SECTION(k_SlowADCValidDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_SlowADCValidDiag_Cnt_str = {10,1,1};

#pragma DATA_SECTION(k_ReadAdcWaitTimeout_uS_u32, ".FlashCalSeg");
CONST(uint32, CAL_CONST) k_ReadAdcWaitTimeout_uS_u32 = 400UL;


/********************************** LmtCod ***********************************/
#pragma DATA_SECTION(k_CCLTrqRampIncSlew_UlspS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CCLTrqRampIncSlew_UlspS_f32 = 500.0f;

#pragma DATA_SECTION(k_GainDecSlew_UlspS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_GainDecSlew_UlspS_f32 = 500.0f;

#pragma DATA_SECTION(k_TorqueDecSlew_MtrNmpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TorqueDecSlew_MtrNmpS_f32 = 4400.0f;

#pragma DATA_SECTION(t_GainIncSlewTblX_Kph_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_GainIncSlewTblX_Kph_u9p7[2] = 
	{FPM_InitFixedPoint_m(10.0, u9p7_T), FPM_InitFixedPoint_m(20.0, u9p7_T)};

#pragma DATA_SECTION(t_GainIncSlewTblY_UlspS_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_GainIncSlewTblY_UlspS_u9p7[2] = 
	{FPM_InitFixedPoint_m(500.0, u9p7_T),
	 FPM_InitFixedPoint_m(500.0, u9p7_T)};

#pragma DATA_SECTION(t_TorqueIncSlewTblX_Kph_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_TorqueIncSlewTblX_Kph_u9p7[2] = 
	{FPM_InitFixedPoint_m(10.0, u9p7_T), FPM_InitFixedPoint_m(20.0, u9p7_T)};

#pragma DATA_SECTION(t_TorqueIncSlewTblY_MtrNmpS_u13p3, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_TorqueIncSlewTblY_MtrNmpS_u13p3[2] = 
	{FPM_InitFixedPoint_m(4400.0, u13p3_T),
	 FPM_InitFixedPoint_m(4400.0, u13p3_T)};


/******************************** MtrCtrl_CM *********************************/
#pragma DATA_SECTION(k_CuThermCoeff_OhmpDegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CuThermCoeff_OhmpDegC_f32 = 0.00393f;

#pragma DATA_SECTION(k_deadtimeVScale_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_deadtimeVScale_Uls_f32 = 1.0f;

#pragma DATA_SECTION(k_EstPkCurr2msLPFKn_Uls_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_EstPkCurr2msLPFKn_Uls_u16 = 6268U;

#pragma DATA_SECTION(k_EstPkCurrSlowLoopLPFKn_Uls_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_EstPkCurrSlowLoopLPFKn_Uls_u16 = 1224U;

#pragma DATA_SECTION(k_Harmonic12thElec_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_Harmonic12thElec_Uls_f32 = 12.0f;

#pragma DATA_SECTION(k_Harmonic18thElec_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_Harmonic18thElec_Uls_f32 = 18.0f;

#pragma DATA_SECTION(k_Harmonic6thElec_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_Harmonic6thElec_Uls_f32 = 6.0f;

#pragma DATA_SECTION(k_IdBoostGain_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_IdBoostGain_Uls_f32 = 0.0f;

#pragma DATA_SECTION(k_IdBoostVRThreshScl_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_IdBoostVRThreshScl_Uls_f32 = 0.25f;

#pragma DATA_SECTION(k_IdqRefIminNIter_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_IdqRefIminNIter_Cnt_u16 = 3U;

#pragma DATA_SECTION(k_IdqRefIminTol_Amp_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_IdqRefIminTol_Amp_f32 = 0.1f;

#pragma DATA_SECTION(k_IdqRefLocateRefNIter_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_IdqRefLocateRefNIter_Cnt_u16 = 10U;

#pragma DATA_SECTION(k_IdqRefTrqNIter_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_IdqRefTrqNIter_Cnt_u16 = 3U;

#pragma DATA_SECTION(k_IdqRefTrqTol_Rad_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_IdqRefTrqTol_Rad_f32 = 0.015f;

#pragma DATA_SECTION(k_InstMtrDirHyst_Deg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_InstMtrDirHyst_Deg_f32 = 2.5f;

#pragma DATA_SECTION(k_MagThrC_VpRadpSpDegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MagThrC_VpRadpSpDegC_f32 = -0.001f;

#pragma DATA_SECTION(k_MaxKeRngLmt_VpRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxKeRngLmt_VpRadpS_f32 = 0.06f;

#pragma DATA_SECTION(k_MaxLdRngLmt_Henry_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxLdRngLmt_Henry_f32 = 0.0002f;

#pragma DATA_SECTION(k_MaxLqRngLmt_Henry_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxLqRngLmt_Henry_f32 = 0.0002f;

#pragma DATA_SECTION(k_MaxRRngLmt_Ohm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxRRngLmt_Ohm_f32 = 0.06f;

#pragma DATA_SECTION(k_MaxTrqCmdScl_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MaxTrqCmdScl_Uls_f32 = 1.1f;

#pragma DATA_SECTION(k_MinKeRngLmt_VpRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MinKeRngLmt_VpRadpS_f32 = 0.026f;

#pragma DATA_SECTION(k_MinLdRngLmt_Henry_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MinLdRngLmt_Henry_f32 = 0.0001f;

#pragma DATA_SECTION(k_MinLqRngLmt_Henry_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MinLqRngLmt_Henry_f32 = 0.0001f;

#pragma DATA_SECTION(k_MinRRngLmt_Ohm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MinRRngLmt_Ohm_f32 = 0.01f;

#pragma DATA_SECTION(k_MinTrqCmdScl_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MinTrqCmdScl_Uls_f32 = 0.9f;

#pragma DATA_SECTION(k_MtrPosComputationDelay_Sec_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrPosComputationDelay_Sec_f32 = 0.00009375f;

#pragma DATA_SECTION(k_MtrVelFiltFFKn_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MtrVelFiltFFKn_Cnt_u16 = 7739U;

#pragma DATA_SECTION(k_MtrVelFiltPIKn_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MtrVelFiltPIKn_Cnt_u16 = 7739U;

#pragma DATA_SECTION(k_NomLd_Henry_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_NomLd_Henry_f32 = 0.00011889f;

#pragma DATA_SECTION(k_NomLq_Henry_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_NomLq_Henry_f32 = 0.00011889f;

#pragma DATA_SECTION(k_NomRfet_Ohm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_NomRfet_Ohm_f32 = 0.00625f;

#pragma DATA_SECTION(k_NomTemp_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_NomTemp_DegC_f32 = 25.0f;

#pragma DATA_SECTION(k_NoofPoles_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_NoofPoles_Uls_f32 = 6.0f;

#pragma DATA_SECTION(k_PIGainVspdCutoff_kph_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_PIGainVspdCutoff_kph_f32 = 3.0f;

#pragma DATA_SECTION(k_PiSamplingTs_Sec_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_PiSamplingTs_Sec_f32 = 0.000125f;

#pragma DATA_SECTION(k_SiThermCoeff_OhmpDegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SiThermCoeff_OhmpDegC_f32 = 0.005f;

#pragma DATA_SECTION(t_CommOffsetTblX_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_CommOffsetTblX_Uls_u3p13[2] = 
	{FPM_InitFixedPoint_m(0.6, u3p13_T),FPM_InitFixedPoint_m(0.95, u3p13_T)};

#pragma DATA_SECTION(t_CurrParamCompDaxRef_Amp_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_CurrParamCompDaxRef_Amp_u9p7[6] = 
	{ FPM_InitFixedPoint_m(0.0, u9p7_T),FPM_InitFixedPoint_m(25.0, u9p7_T),
	FPM_InitFixedPoint_m(50.0, u9p7_T),FPM_InitFixedPoint_m(75.0, u9p7_T),
	FPM_InitFixedPoint_m(100.0, u9p7_T),FPM_InitFixedPoint_m(125.0, u9p7_T) };

#pragma DATA_SECTION(t_CurrParamCompQaxRef_Amp_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_CurrParamCompQaxRef_Amp_u9p7[7] = 
	{ FPM_InitFixedPoint_m(0.0, u9p7_T),FPM_InitFixedPoint_m(25.0, u9p7_T),
	FPM_InitFixedPoint_m(50.0, u9p7_T),FPM_InitFixedPoint_m(75.0, u9p7_T),
	FPM_InitFixedPoint_m(100.0, u9p7_T),FPM_InitFixedPoint_m(125.0, u9p7_T),
	FPM_InitFixedPoint_m(150.0, u9p7_T) };

#pragma DATA_SECTION(t_IdBoostTrqCharSclY_Uls_u1p15, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_IdBoostTrqCharSclY_Uls_u1p15[11] = 
	{FPM_InitFixedPoint_m(0.0, u1p15_T),FPM_InitFixedPoint_m(0.5, u1p15_T),
	FPM_InitFixedPoint_m(0.6, u1p15_T),FPM_InitFixedPoint_m(0.7, u1p15_T),
	FPM_InitFixedPoint_m(0.725, u1p15_T),
	FPM_InitFixedPoint_m(0.775, u1p15_T),
	FPM_InitFixedPoint_m(0.825, u1p15_T),FPM_InitFixedPoint_m(0.85, u1p15_T),
	FPM_InitFixedPoint_m(0.9, u1p15_T),FPM_InitFixedPoint_m(0.95, u1p15_T),
	FPM_InitFixedPoint_m(1.0, u1p15_T)};

#pragma DATA_SECTION(t_IdBoostTrqCmdX_MtrNm_u4p12, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_IdBoostTrqCmdX_MtrNm_u4p12[11] = 
	{FPM_InitFixedPoint_m(0.0, u4p12_T),FPM_InitFixedPoint_m(1.5, u4p12_T),
	FPM_InitFixedPoint_m(1.75, u4p12_T),FPM_InitFixedPoint_m(2.0, u4p12_T),
	FPM_InitFixedPoint_m(2.25, u4p12_T),FPM_InitFixedPoint_m(2.5, u4p12_T),
	FPM_InitFixedPoint_m(3.0, u4p12_T),FPM_InitFixedPoint_m(3.5, u4p12_T),
	FPM_InitFixedPoint_m(4.0, u4p12_T),FPM_InitFixedPoint_m(4.5, u4p12_T),
	FPM_InitFixedPoint_m(5.0, u4p12_T)};

#pragma DATA_SECTION(t_KeSatTblX_Amp_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_KeSatTblX_Amp_u9p7[16] = 
	{ FPM_InitFixedPoint_m(0.0, u9p7_T), FPM_InitFixedPoint_m(10.0, u9p7_T),
	 FPM_InitFixedPoint_m(25.0, u9p7_T), FPM_InitFixedPoint_m(35.0, u9p7_T),
	 FPM_InitFixedPoint_m(45.0, u9p7_T), FPM_InitFixedPoint_m(55.0, u9p7_T),
	 FPM_InitFixedPoint_m(65.0, u9p7_T), FPM_InitFixedPoint_m(75.0, u9p7_T),
	 FPM_InitFixedPoint_m(85.0, u9p7_T), FPM_InitFixedPoint_m(95.0, u9p7_T),
	 FPM_InitFixedPoint_m(105.0, u9p7_T),
	 FPM_InitFixedPoint_m(115.0, u9p7_T),
	 FPM_InitFixedPoint_m(125.0, u9p7_T),
	 FPM_InitFixedPoint_m(135.0, u9p7_T),
	 FPM_InitFixedPoint_m(145.0, u9p7_T),
	 FPM_InitFixedPoint_m(150.0, u9p7_T) };

#pragma DATA_SECTION(t_KeSatTblY_Uls_u2p14, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_KeSatTblY_Uls_u2p14[16] = 
	{ FPM_InitFixedPoint_m(1.0, u2p14_T), FPM_InitFixedPoint_m(1.0, u2p14_T),
	 FPM_InitFixedPoint_m(1.0, u2p14_T),
	 FPM_InitFixedPoint_m(0.998046875, u2p14_T),
	 FPM_InitFixedPoint_m(0.998046875, u2p14_T),
	 FPM_InitFixedPoint_m(0.994140625, u2p14_T),
	 FPM_InitFixedPoint_m(0.9921875, u2p14_T),
	 FPM_InitFixedPoint_m(0.98828125, u2p14_T),
	 FPM_InitFixedPoint_m(0.982421875, u2p14_T),
	 FPM_InitFixedPoint_m(0.974609375, u2p14_T),
	 FPM_InitFixedPoint_m(0.966796875, u2p14_T),
	 FPM_InitFixedPoint_m(0.95703125, u2p14_T),
	 FPM_InitFixedPoint_m(0.9453125, u2p14_T),
	 FPM_InitFixedPoint_m(0.931640625, u2p14_T),
	 FPM_InitFixedPoint_m(0.916015625, u2p14_T),
	 FPM_InitFixedPoint_m(0.90625, u2p14_T) };

#pragma DATA_SECTION(t_KidGainX_MtrRadpSec_u12p4, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_KidGainX_MtrRadpSec_u12p4[8] = 
	{FPM_InitFixedPoint_m(0.0, u12p4_T),FPM_InitFixedPoint_m(5.0, u12p4_T),
	FPM_InitFixedPoint_m(50.0, u12p4_T),FPM_InitFixedPoint_m(100.0, u12p4_T),
	FPM_InitFixedPoint_m(200.0, u12p4_T),
	FPM_InitFixedPoint_m(300.0, u12p4_T),
	FPM_InitFixedPoint_m(400.0, u12p4_T),
	FPM_InitFixedPoint_m(500.0, u12p4_T)};

#pragma DATA_SECTION(t_KidGainY_Uls_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_KidGainY_Uls_u10p6[8] = 
	{FPM_InitFixedPoint_m(16.0, u10p6_T),FPM_InitFixedPoint_m(50.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T)};

#pragma DATA_SECTION(t_KiqGainX_MtrRadpSec_u12p4, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_KiqGainX_MtrRadpSec_u12p4[8] = 
	{FPM_InitFixedPoint_m(0.0, u12p4_T),FPM_InitFixedPoint_m(5.0, u12p4_T),
	FPM_InitFixedPoint_m(50.0, u12p4_T),FPM_InitFixedPoint_m(100.0, u12p4_T),
	FPM_InitFixedPoint_m(200.0, u12p4_T),
	FPM_InitFixedPoint_m(300.0, u12p4_T),
	FPM_InitFixedPoint_m(400.0, u12p4_T),
	FPM_InitFixedPoint_m(500.0, u12p4_T)};

#pragma DATA_SECTION(t_KiqGainY_Uls_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_KiqGainY_Uls_u10p6[8] = 
	{FPM_InitFixedPoint_m(16.0, u10p6_T),FPM_InitFixedPoint_m(50.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T),
	FPM_InitFixedPoint_m(100.0, u10p6_T)};

#pragma DATA_SECTION(t_KpdGainX_MtrRadpSec_u12p4, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_KpdGainX_MtrRadpSec_u12p4[8] = 
	{FPM_InitFixedPoint_m(0.0, u12p4_T),FPM_InitFixedPoint_m(5.0, u12p4_T),
	FPM_InitFixedPoint_m(50.0, u12p4_T),FPM_InitFixedPoint_m(100.0, u12p4_T),
	FPM_InitFixedPoint_m(200.0, u12p4_T),
	FPM_InitFixedPoint_m(300.0, u12p4_T),
	FPM_InitFixedPoint_m(400.0, u12p4_T),
	FPM_InitFixedPoint_m(500.0, u12p4_T)};

#pragma DATA_SECTION(t_KpdGainY_Uls_u6p10, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_KpdGainY_Uls_u6p10[8] = 
	{FPM_InitFixedPoint_m(0.015, u6p10_T),
	FPM_InitFixedPoint_m(0.03, u6p10_T),FPM_InitFixedPoint_m(0.03, u6p10_T),
	FPM_InitFixedPoint_m(0.05, u6p10_T),FPM_InitFixedPoint_m(0.05, u6p10_T),
	FPM_InitFixedPoint_m(0.05, u6p10_T),FPM_InitFixedPoint_m(0.05, u6p10_T),
	FPM_InitFixedPoint_m(0.05, u6p10_T)};

#pragma DATA_SECTION(t_KpqGainX_MtrRadpSec_u12p4, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_KpqGainX_MtrRadpSec_u12p4[8] = 
	{FPM_InitFixedPoint_m(0.0, u12p4_T),FPM_InitFixedPoint_m(5.0, u12p4_T),
	FPM_InitFixedPoint_m(50.0, u12p4_T),FPM_InitFixedPoint_m(100.0, u12p4_T),
	FPM_InitFixedPoint_m(200.0, u12p4_T),
	FPM_InitFixedPoint_m(300.0, u12p4_T),
	FPM_InitFixedPoint_m(400.0, u12p4_T),
	FPM_InitFixedPoint_m(500.0, u12p4_T)};

#pragma DATA_SECTION(t_KpqGainY_Uls_u6p10, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_KpqGainY_Uls_u6p10[8] = 
	{FPM_InitFixedPoint_m(0.015, u6p10_T),
	FPM_InitFixedPoint_m(0.03, u6p10_T),FPM_InitFixedPoint_m(0.03, u6p10_T),
	FPM_InitFixedPoint_m(0.05, u6p10_T),FPM_InitFixedPoint_m(0.05, u6p10_T),
	FPM_InitFixedPoint_m(0.05, u6p10_T),FPM_InitFixedPoint_m(0.05, u6p10_T),
	FPM_InitFixedPoint_m(0.05, u6p10_T)};

#pragma DATA_SECTION(t_MtrCurrDaxRpl_Amp_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrCurrDaxRpl_Amp_u9p7[10] = 
	{FPM_InitFixedPoint_m(0.0, u9p7_T),FPM_InitFixedPoint_m(10.0, u9p7_T),
	FPM_InitFixedPoint_m(25.0, u9p7_T),FPM_InitFixedPoint_m(50.0, u9p7_T),
	FPM_InitFixedPoint_m(60.0, u9p7_T),FPM_InitFixedPoint_m(75.0, u9p7_T),
	FPM_InitFixedPoint_m(90.0, u9p7_T),FPM_InitFixedPoint_m(100.0, u9p7_T),
	FPM_InitFixedPoint_m(110.0, u9p7_T),FPM_InitFixedPoint_m(125.0, u9p7_T)};

#pragma DATA_SECTION(t_MtrCurrQaxRpl_Amp_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrCurrQaxRpl_Amp_u9p7[12] = 
	{FPM_InitFixedPoint_m(0.0, u9p7_T),FPM_InitFixedPoint_m(10.0, u9p7_T),
	FPM_InitFixedPoint_m(25.0, u9p7_T),FPM_InitFixedPoint_m(50.0, u9p7_T),
	FPM_InitFixedPoint_m(60.0, u9p7_T),FPM_InitFixedPoint_m(75.0, u9p7_T),
	FPM_InitFixedPoint_m(100.0, u9p7_T),FPM_InitFixedPoint_m(105.0, u9p7_T),
	FPM_InitFixedPoint_m(110.0, u9p7_T),FPM_InitFixedPoint_m(120.0, u9p7_T),
	FPM_InitFixedPoint_m(125.0, u9p7_T),FPM_InitFixedPoint_m(135.0, u9p7_T)};

#pragma DATA_SECTION(t_MtrCurrQaxRplPIY_Amp_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrCurrQaxRplPIY_Amp_u9p7[7] = 
	{FPM_InitFixedPoint_m(0.0, u9p7_T),FPM_InitFixedPoint_m(25.0, u9p7_T),
	FPM_InitFixedPoint_m(50.0, u9p7_T),FPM_InitFixedPoint_m(75.0, u9p7_T),
	FPM_InitFixedPoint_m(100.0, u9p7_T),FPM_InitFixedPoint_m(125.0, u9p7_T),
	FPM_InitFixedPoint_m(135.0, u9p7_T)};

#pragma DATA_SECTION(t_MtrVelX_MtrRadpS_T_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrVelX_MtrRadpS_T_u16[20] = {0U, 50U, 100U, 107U,
	 114U, 150U, 303U, 500U, 700U, 800U, 1000U, 1200U, 1804U, 2620U, 2839U,
	 3200U, 3407U,5101U, 8492U, 11100U};

#pragma DATA_SECTION(t_Q13VltgSchedXTbl_MtrRadpS_u12p4, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Q13VltgSchedXTbl_MtrRadpS_u12p4[10] = 
	{FPM_InitFixedPoint_m(0.0, u12p4_T),FPM_InitFixedPoint_m(100.0, u12p4_T),
	FPM_InitFixedPoint_m(200.0, u12p4_T),
	FPM_InitFixedPoint_m(300.0, u12p4_T),
	FPM_InitFixedPoint_m(500.0, u12p4_T),
	FPM_InitFixedPoint_m(600.0, u12p4_T),
	FPM_InitFixedPoint_m(700.0, u12p4_T),
	FPM_InitFixedPoint_m(800.0, u12p4_T),
	FPM_InitFixedPoint_m(900.0, u12p4_T),
	FPM_InitFixedPoint_m(1100.0, u12p4_T)};

#pragma DATA_SECTION(t_Q13VltgSchedYTbl_Volt_u5p11, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Q13VltgSchedYTbl_Volt_u5p11[10] = 
	{FPM_InitFixedPoint_m(0.0, u5p11_T),FPM_InitFixedPoint_m(0.0, u5p11_T),
	FPM_InitFixedPoint_m(0.0, u5p11_T),FPM_InitFixedPoint_m(0.0, u5p11_T),
	FPM_InitFixedPoint_m(0.0, u5p11_T),FPM_InitFixedPoint_m(0.0, u5p11_T),
	FPM_InitFixedPoint_m(0.0, u5p11_T),FPM_InitFixedPoint_m(0.0, u5p11_T),
	FPM_InitFixedPoint_m(0.0, u5p11_T),FPM_InitFixedPoint_m(0.0, u5p11_T)};

#pragma DATA_SECTION(t_Q24VltgSchedXTbl_MtrRadpS_u12p4, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Q24VltgSchedXTbl_MtrRadpS_u12p4[10] = 
	{FPM_InitFixedPoint_m(0.0, u12p4_T),FPM_InitFixedPoint_m(100.0, u12p4_T),
	FPM_InitFixedPoint_m(200.0, u12p4_T),
	FPM_InitFixedPoint_m(300.0, u12p4_T),
	FPM_InitFixedPoint_m(500.0, u12p4_T),
	FPM_InitFixedPoint_m(600.0, u12p4_T),
	FPM_InitFixedPoint_m(700.0, u12p4_T),
	FPM_InitFixedPoint_m(800.0, u12p4_T),
	FPM_InitFixedPoint_m(900.0, u12p4_T),
	FPM_InitFixedPoint_m(1100.0, u12p4_T)};

#pragma DATA_SECTION(t_Q24VltgSchedYTbl_Volt_u5p11, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Q24VltgSchedYTbl_Volt_u5p11[10] = 
	{FPM_InitFixedPoint_m(0.0, u5p11_T),FPM_InitFixedPoint_m(0.0, u5p11_T),
	FPM_InitFixedPoint_m(0.0, u5p11_T),FPM_InitFixedPoint_m(0.0, u5p11_T),
	FPM_InitFixedPoint_m(0.0, u5p11_T),FPM_InitFixedPoint_m(0.0, u5p11_T),
	FPM_InitFixedPoint_m(0.0, u5p11_T),FPM_InitFixedPoint_m(0.0, u5p11_T),
	FPM_InitFixedPoint_m(0.0, u5p11_T),FPM_InitFixedPoint_m(0.0, u5p11_T)};

#pragma DATA_SECTION(t_RefDeltaPoints_Rad_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) t_RefDeltaPoints_Rad_f32[8] = {-3.1415926535897931f,
	-2.3561944901923448f,-1.5707963267948966f, -0.78539816339744828f, 0.0f,
	0.78539816339744828f, 1.5707963267948966f, 2.3561944901923448f};

#pragma DATA_SECTION(t2_CurrParamLdSatSclFac_Uls_u2p14, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t2_CurrParamLdSatSclFac_Uls_u2p14[6][7] = 
	{{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)},
	{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)},
	{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)},
	{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)},
	{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)},
	{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)}};

#pragma DATA_SECTION(t2_CurrParamLqSatSclFac_Uls_u2p14, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t2_CurrParamLqSatSclFac_Uls_u2p14[6][7] = 
	{{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)},
	{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)},
	{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)},
	{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)},
	{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)},
	{FPM_InitFixedPoint_m(1.0, u2p14_T),FPM_InitFixedPoint_m(1.0, u2p14_T),
	FPM_InitFixedPoint_m(0.9961, u2p14_T),
	FPM_InitFixedPoint_m(0.9883, u2p14_T),
	FPM_InitFixedPoint_m(0.9707, u2p14_T),
	FPM_InitFixedPoint_m(0.9453, u2p14_T),
	FPM_InitFixedPoint_m(0.9063, u2p14_T)}};

#pragma DATA_SECTION(t2_MtrCurrQaxRpl12X_Amp_s6p9, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl12X_Amp_s6p9[6][7] = 
	{{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)}, {FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)}};

#pragma DATA_SECTION(t2_MtrCurrQaxRpl12Y_Amp_s6p9, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl12Y_Amp_s6p9[6][7] = 
	{{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)}, {FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)}};

#pragma DATA_SECTION(t2_MtrCurrQaxRpl18X_Amp_s6p9, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl18X_Amp_s6p9[6][7] = 
	{{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)}, {FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)}};

#pragma DATA_SECTION(t2_MtrCurrQaxRpl18Y_Amp_s6p9, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl18Y_Amp_s6p9[6][7] = 
	{{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)}, {FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)}};

#pragma DATA_SECTION(t2_MtrCurrQaxRpl6X_Amp_s6p9, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl6X_Amp_s6p9[6][7] = 
	{{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)}, {FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)}};

#pragma DATA_SECTION(t2_MtrCurrQaxRpl6Y_Amp_s6p9, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl6Y_Amp_s6p9[6][7] = 
	{{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)}, {FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)},
	{FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T)},{FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T),
	FPM_InitFixedPoint_m(0.0, s6p9_T),FPM_InitFixedPoint_m(0.0, s6p9_T)}};

#pragma DATA_SECTION(t2_MtrTrqCancPIMagRP_Uls_u6p10, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t2_MtrTrqCancPIMagRP_Uls_u6p10[20][8] = 
	{{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)},
	{FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T),
	FPM_InitFixedPoint_m(0.0, u6p10_T),FPM_InitFixedPoint_m(0.0, u6p10_T)}};

#pragma DATA_SECTION(t2_MtrTrqCancPIPhRP_Rev_u0p16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t2_MtrTrqCancPIPhRP_Rev_u0p16[20][8] = 
	{{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)},
	{FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T),
	FPM_InitFixedPoint_m(0.0, u0p16_T),FPM_InitFixedPoint_m(0.0, u0p16_T)}};

#pragma DATA_SECTION(k_MtrCtrlCurrLoopSecOrTranFcEnable_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_MtrCtrlCurrLoopSecOrTranFcEnable_Cnt_lgc = FALSE;

#pragma DATA_SECTION(k_MtrCtrlFeedbackControlDisable_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_MtrCtrlFeedbackControlDisable_Cnt_lgc = FALSE;

#pragma DATA_SECTION(k_VoltModeDynCompEnable_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_VoltModeDynCompEnable_Cnt_lgc = FALSE;

#pragma DATA_SECTION(k_MtrVoltDervFiltCoeffTimeCons_Sec_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrVoltDervFiltCoeffTimeCons_Sec_f32 = 0.00318f;

#pragma DATA_SECTION(k_MtrCtrlVirualResQax_Ohm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrCtrlVirualResQax_Ohm_f32 = 0.0f;

#pragma DATA_SECTION(k_MtrCtrlVirualResDax_Ohm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrCtrlVirualResDax_Ohm_f32 = 0.0f;

#pragma DATA_SECTION(k_MtrCurrDaxMaxValScl_Per_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrCurrDaxMaxValScl_Per_f32 = 0.0f;

#pragma DATA_SECTION(k_MtrDampingRatioDax_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrDampingRatioDax_Uls_f32 = 1.0f;

#pragma DATA_SECTION(k_MtrDampingRatioQax_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrDampingRatioQax_Uls_f32 = 1.0f;

#pragma DATA_SECTION(t_MtrBandwidthDaxY_Hz_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrBandwidthDaxY_Hz_u10p6[4] = 
	{FPM_InitFixedPoint_m(300.0, u10p6_T),
	 FPM_InitFixedPoint_m(300.0, u10p6_T),
	 FPM_InitFixedPoint_m(300.0, u10p6_T),
	 FPM_InitFixedPoint_m(300.0, u10p6_T)};

#pragma DATA_SECTION(t_MtrBandwidthQaxY_Hz_u10p6, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrBandwidthQaxY_Hz_u10p6[4] = 
	{FPM_InitFixedPoint_m(300.0, u10p6_T),
	 FPM_InitFixedPoint_m(300.0, u10p6_T),
	 FPM_InitFixedPoint_m(300.0, u10p6_T),
	 FPM_InitFixedPoint_m(300.0, u10p6_T)};

#pragma DATA_SECTION(t_MtrVelCtrlGainX_MtrRadpSec_u12p4, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrVelCtrlGainX_MtrRadpSec_u12p4[4] = 
	{FPM_InitFixedPoint_m(0.0, u12p4_T), FPM_InitFixedPoint_m(1.0, u12p4_T),
	 FPM_InitFixedPoint_m(5.0, u12p4_T), FPM_InitFixedPoint_m(10.0, u12p4_T)};

#pragma DATA_SECTION(t_MtrNaturalFreqQaxY_Hz_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrNaturalFreqQaxY_Hz_u9p7[4] = 
	{FPM_InitFixedPoint_m(300.0, u9p7_T),
	 FPM_InitFixedPoint_m(300.0, u9p7_T),
	 FPM_InitFixedPoint_m(300.0, u9p7_T),
	 FPM_InitFixedPoint_m(300.0, u9p7_T)};

#pragma DATA_SECTION(t_MtrNaturalFreqDaxY_Hz_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrNaturalFreqDaxY_Hz_u9p7[4] = 
	{FPM_InitFixedPoint_m(300.0, u9p7_T),
	 FPM_InitFixedPoint_m(300.0, u9p7_T),
	 FPM_InitFixedPoint_m(300.0, u9p7_T),
	 FPM_InitFixedPoint_m(300.0, u9p7_T)};

#pragma DATA_SECTION(t_MtrTrqCmdPIY_MtrNm_u5p11, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrTrqCmdPIY_MtrNm_u5p11[8] = 
	{FPM_InitFixedPoint_m(0.0, u5p11_T), FPM_InitFixedPoint_m(1.0, u5p11_T),
	FPM_InitFixedPoint_m(2.0, u5p11_T), FPM_InitFixedPoint_m(2.5, u5p11_T),
	 FPM_InitFixedPoint_m(3.0, u5p11_T), FPM_InitFixedPoint_m(4.0, u5p11_T),
	 FPM_InitFixedPoint_m(4.5, u5p11_T), FPM_InitFixedPoint_m(5.0, u5p11_T)};

#pragma DATA_SECTION(t2_MtrTrqRpl18Y_MtrNm_s2p13, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrTrqRpl18Y_MtrNm_s2p13[10][12] = 
	{{FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)}};

#pragma DATA_SECTION(t2_MtrTrqRpl18X_MtrNm_s2p13, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrTrqRpl18X_MtrNm_s2p13[10][12] = 
	{{FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)}};

#pragma DATA_SECTION(t2_MtrTrqRpl12Y_MtrNm_s2p13, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrTrqRpl12Y_MtrNm_s2p13[10][12] = 
	{{FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)}};

#pragma DATA_SECTION(t2_MtrTrqRpl12X_MtrNm_s2p13, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrTrqRpl12X_MtrNm_s2p13[10][12] = 
	{{FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)}};

#pragma DATA_SECTION(t2_MtrTrqRpl6Y_MtrNm_s2p13, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrTrqRpl6Y_MtrNm_s2p13[10][12] = 
	{{FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)}};

#pragma DATA_SECTION(t2_MtrTrqRpl6X_MtrNm_s2p13, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t2_MtrTrqRpl6X_MtrNm_s2p13[10][12] = 
	{{FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)},
	 {FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T),
	FPM_InitFixedPoint_m(0.0, s2p13_T),FPM_InitFixedPoint_m(0.0, s2p13_T)}};

#pragma DATA_SECTION(k_VoltSatDaxPolyCoeff_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VoltSatDaxPolyCoeff_Uls_f32 = 0.0f;

#pragma DATA_SECTION(k_VoltSatQaxPolyCoeff_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VoltSatQaxPolyCoeff_Uls_f32 = 0.0f;

#pragma DATA_SECTION(k_MtrCurrQaxRefModifDsb_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_MtrCurrQaxRefModifDsb_Cnt_lgc = FALSE;

#pragma DATA_SECTION(k_CLOAFdbackSignalSclFacSlew_UlspS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CLOAFdbackSignalSclFacSlew_UlspS_f32 = 100.0f;

#pragma DATA_SECTION(k_ILOAFdbackSignalSclFacSlew_UlspS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_ILOAFdbackSignalSclFacSlew_UlspS_f32 = 100.0f;

#pragma DATA_SECTION(k_MtrPosComputationDelayRpl_Sec_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrPosComputationDelayRpl_Sec_f32 = 0.00009375f;

#pragma DATA_SECTION(k_MtrVoltQaxFiltFFKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrVoltQaxFiltFFKn_Hz_f32 = 500.0f;

#pragma DATA_SECTION(k_MtrVoltQaxFiltFFEnable_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_MtrVoltQaxFiltFFEnable_Cnt_lgc = TRUE;

#pragma DATA_SECTION(k_MtrVoltVecuFiltKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrVoltVecuFiltKn_Hz_f32 = 200.0f;

#pragma DATA_SECTION(k_MtrVoltVecuFiltEnable_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_MtrVoltVecuFiltEnable_Cnt_lgc = TRUE;


/**************************** MtrCtrl_CM, SVDiag *****************************/
#pragma DATA_SECTION(t_CommOffsetTblY_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_CommOffsetTblY_Cnt_u16[2] = {63U,0U};


/******************************** MtrTempEst *********************************/
#pragma DATA_SECTION(k_AMAmbLPFKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AMAmbLPFKn_Hz_f32 = 0.024f;

#pragma DATA_SECTION(k_AMAmbMult_DegCpWatt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AMAmbMult_DegCpWatt_f32 = 0.01f;

#pragma DATA_SECTION(k_AmbPwrMult_WtspAmpSq_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AmbPwrMult_WtspAmpSq_f32 = 0.01f;

#pragma DATA_SECTION(k_AmbTempScl_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AmbTempScl_Uls_f32 = 0.9f;

#pragma DATA_SECTION(k_AMCorrLmt_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AMCorrLmt_DegC_f32 = 60.0f;

#pragma DATA_SECTION(k_AMDampScl_NmpRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AMDampScl_NmpRadpS_f32 = 0.0001f;

#pragma DATA_SECTION(k_AMDefaultTemp_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AMDefaultTemp_DegC_f32 = 50.0f;

#pragma DATA_SECTION(k_AMLLFiltCoefB0_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AMLLFiltCoefB0_Uls_f32 = 0.4761987f;

#pragma DATA_SECTION(k_AMLLFiltCoefB1_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AMLLFiltCoefB1_Uls_f32 = -0.4761673f;

#pragma DATA_SECTION(k_AMLLFiltPoleA1_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AMLLFiltPoleA1_Uls_f32 = 0.99996858f;

#pragma DATA_SECTION(k_AssistMechSlew_DegCpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AssistMechSlew_DegCpS_f32 = 1.0f;

#pragma DATA_SECTION(k_CuAmbLPFKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CuAmbLPFKn_Hz_f32 = 0.024f;

#pragma DATA_SECTION(k_CuAmbMult_DegCpWatt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CuAmbMult_DegCpWatt_f32 = 0.75f;

#pragma DATA_SECTION(k_CuCorrLmt_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CuCorrLmt_DegC_f32 = 80.0f;

#pragma DATA_SECTION(k_CuLLFiltKA1_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CuLLFiltKA1_Uls_f32 = 0.99994282f;

#pragma DATA_SECTION(k_CuLLFiltKB0_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CuLLFiltKB0_Uls_f32 = 0.86667048f;

#pragma DATA_SECTION(k_CuLLFiltKB1_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CuLLFiltKB1_Uls_f32 = -0.8666133f;

#pragma DATA_SECTION(k_EngTempScl_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_EngTempScl_Uls_f32 = 0.1f;

#pragma DATA_SECTION(k_MagAmbLPFKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MagAmbLPFKn_Hz_f32 = 0.024f;

#pragma DATA_SECTION(k_MagAmbMult_DegCpWatt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MagAmbMult_DegCpWatt_f32 = 0.01f;

#pragma DATA_SECTION(k_MagCorrLmt_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MagCorrLmt_DegC_f32 = 60.0f;

#pragma DATA_SECTION(k_MagLLFiltKA1_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MagLLFiltKA1_Uls_f32 = 0.9999623f;

#pragma DATA_SECTION(k_MagLLFiltKB0_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MagLLFiltKB0_Uls_f32 = 0.57143665f;

#pragma DATA_SECTION(k_MagLLFiltKB1_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MagLLFiltKB1_Uls_f32 = -0.571399f;

#pragma DATA_SECTION(k_SiAmbLPFKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SiAmbLPFKn_Hz_f32 = 0.024f;

#pragma DATA_SECTION(k_SiAmbMult_DegCpWatt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SiAmbMult_DegCpWatt_f32 = 0.0f;

#pragma DATA_SECTION(k_SiCorrLmt_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SiCorrLmt_DegC_f32 = 60.0f;

#pragma DATA_SECTION(k_SiLLFiltKA1_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SiLLFiltKA1_Uls_f32 = 0.99988879f;

#pragma DATA_SECTION(k_SiLLFiltKB0_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SiLLFiltKB0_Uls_f32 = 1.68567616f;

#pragma DATA_SECTION(k_SiLLFiltKB1_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SiLLFiltKB1_Uls_f32 = -1.685565f;

#pragma DATA_SECTION(k_TrimTempAM_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TrimTempAM_DegC_f32 = 0.0f;

#pragma DATA_SECTION(k_TrimTempCu_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TrimTempCu_DegC_f32 = 0.0f;

#pragma DATA_SECTION(k_TrimTempMag_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TrimTempMag_DegC_f32 = 0.0f;

#pragma DATA_SECTION(k_TrimTempSi_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TrimTempSi_DegC_f32 = 0.0f;

#pragma DATA_SECTION(k_WtAvgTempDFt_Cnt_lgc, ".FlashCalSeg");
CONST(Boolean, CAL_CONST) k_WtAvgTempDFt_Cnt_lgc = FALSE;


/******************* MtrVel, AbsHwPos_TcI2cVd, MtrVel_Digi *******************/
#pragma DATA_SECTION(k_GearRatio_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_GearRatio_Uls_f32 = 4.54545454545454E-02f;


/**************************** MtrVel, MtrVel_Digi ****************************/
#pragma DATA_SECTION(k_HwVelCorrLim_Cnt_Str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_HwVelCorrLim_Cnt_Str = {12, 3, 1};

#pragma DATA_SECTION(k_HwVelCorrLim_HwRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HwVelCorrLim_HwRadpS_f32 = 6.4f;

#pragma DATA_SECTION(k_MtrVelCorrLim_Cnt_Str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_MtrVelCorrLim_Cnt_Str = {12, 3, 1};

#pragma DATA_SECTION(k_MtrVelCorrLim_MtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_MtrVelCorrLim_MtrRadpS_f32 = 225.0f;

#pragma DATA_SECTION(t_MtrVelBlendTblX_MtrRadpS_u12p4, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrVelBlendTblX_MtrRadpS_u12p4[2] = 
	{FPM_InitFixedPoint_m(0.0, u12p4_T), FPM_InitFixedPoint_m(0.0, u12p4_T)};


/******************************** OvrVoltMon *********************************/
#pragma DATA_SECTION(k_CPUSupplyOV_Cnt_Str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_CPUSupplyOV_Cnt_Str = {10,10,1};


/******************************* PwrLmtFuncCr ********************************/
#pragma DATA_SECTION(k_AsstReducLPFKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AsstReducLPFKn_Hz_f32 = 0.365f;

#pragma DATA_SECTION(k_FiltAsstReducTh_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_FiltAsstReducTh_Uls_f32 = 0.6f;

#pragma DATA_SECTION(k_KeStdTemp_VpRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_KeStdTemp_VpRadpS_f32 = 0.033599854f;

#pragma DATA_SECTION(k_LowVltAstRecTh_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_LowVltAstRecTh_Volt_f32 = 13.5f;

#pragma DATA_SECTION(k_LowVltAstRecTime_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_LowVltAstRecTime_mS_u16 = 2000U;

#pragma DATA_SECTION(k_PwrLmtMtrVelLPFKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_PwrLmtMtrVelLPFKn_Hz_f32 = 100.0f;

#pragma DATA_SECTION(k_PwrLmtVecuAdjSlew_VoltspL_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_PwrLmtVecuAdjSlew_VoltspL_f32 = 0.001f;

#pragma DATA_SECTION(k_PwrLmtVecuAltFltAdj_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_PwrLmtVecuAltFltAdj_Volt_f32 = 1.0f;

#pragma DATA_SECTION(k_SpdAdjSlewDec_MtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SpdAdjSlewDec_MtrRadpS_f32 = 0.0625f;

#pragma DATA_SECTION(k_SpdAdjSlewEnable_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_SpdAdjSlewEnable_Cnt_lgc = TRUE;

#pragma DATA_SECTION(k_SpdAdjSlewInc_MtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SpdAdjSlewInc_MtrRadpS_f32 = 6.25f;

#pragma DATA_SECTION(t_DLVTblX_Volt_u5p11, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_DLVTblX_Volt_u5p11[10] = 
	{FPM_InitFixedPoint_m(8.54296875, u5p11_T),
	 FPM_InitFixedPoint_m(9.14453125, u5p11_T),
	 FPM_InitFixedPoint_m(9.2421875, u5p11_T),
	 FPM_InitFixedPoint_m(9.34375, u5p11_T),
	 FPM_InitFixedPoint_m(9.44140625, u5p11_T),
	 FPM_InitFixedPoint_m(9.54296875, u5p11_T),
	 FPM_InitFixedPoint_m(10.04296875, u5p11_T),
	 FPM_InitFixedPoint_m(10.54296875, u5p11_T),
	 FPM_InitFixedPoint_m(10.84375, u5p11_T),
	 FPM_InitFixedPoint_m(12.34375, u5p11_T)};

#pragma DATA_SECTION(t_DLVTblY_MtrRadpS_u11p5, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_DLVTblY_MtrRadpS_u11p5[10] = 
	{FPM_InitFixedPoint_m(106.09375, u11p5_T),
	 FPM_InitFixedPoint_m(89.34375, u11p5_T),
	 FPM_InitFixedPoint_m(86.53125, u11p5_T),
	 FPM_InitFixedPoint_m(83.75, u11p5_T),
	 FPM_InitFixedPoint_m(80.96875, u11p5_T),
	 FPM_InitFixedPoint_m(78.15625, u11p5_T),
	FPM_InitFixedPoint_m(64.1875, u11p5_T),
	FPM_InitFixedPoint_m(50.25, u11p5_T),
	FPM_InitFixedPoint_m(41.875, u11p5_T),FPM_InitFixedPoint_m(0.0, u11p5_T)};

#pragma DATA_SECTION(t_MtrEnvTblX_MtrRadpS_s11p4, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t_MtrEnvTblX_MtrRadpS_s11p4[14] = 
	{FPM_InitFixedPoint_m(-1100.0, s11p4_T),
	 FPM_InitFixedPoint_m(-800.0, s11p4_T),
	 FPM_InitFixedPoint_m(-650.0, s11p4_T),
	 FPM_InitFixedPoint_m(-550.0, s11p4_T),
	 FPM_InitFixedPoint_m(-353.5625, s11p4_T),
	 FPM_InitFixedPoint_m(-287.46875, s11p4_T),
	 FPM_InitFixedPoint_m(-218.65625, s11p4_T),
	 FPM_InitFixedPoint_m(-108.1875, s11p4_T),
	 FPM_InitFixedPoint_m(0.0, s11p4_T),
	 FPM_InitFixedPoint_m(108.1875, s11p4_T),
	 FPM_InitFixedPoint_m(218.65625, s11p4_T),
	 FPM_InitFixedPoint_m(287.46875, s11p4_T),
	 FPM_InitFixedPoint_m(353.5625, s11p4_T),
	 FPM_InitFixedPoint_m(550.0, s11p4_T)};

#pragma DATA_SECTION(t_MtrEnvTblY_MtrNm_u5p11, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MtrEnvTblY_MtrNm_u5p11[14] = 
	{FPM_InitFixedPoint_m(0.720, u5p11_T),
	 FPM_InitFixedPoint_m(1.400, u5p11_T),
	 FPM_InitFixedPoint_m(1.900, u5p11_T),
	 FPM_InitFixedPoint_m(2.300, u5p11_T),
	 FPM_InitFixedPoint_m(3.500, u5p11_T),
	 FPM_InitFixedPoint_m(4.100, u5p11_T),
	 FPM_InitFixedPoint_m(4.632, u5p11_T),
	 FPM_InitFixedPoint_m(4.632, u5p11_T),
	 FPM_InitFixedPoint_m(4.632, u5p11_T),
	 FPM_InitFixedPoint_m(4.632, u5p11_T),
	 FPM_InitFixedPoint_m(3.553, u5p11_T),
	 FPM_InitFixedPoint_m(2.927, u5p11_T),
	 FPM_InitFixedPoint_m(2.200, u5p11_T),
	 FPM_InitFixedPoint_m(0.0, u5p11_T)};

#pragma DATA_SECTION(t_StdOpMtrEnvTblX_MtrRadpS_u11p5, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_StdOpMtrEnvTblX_MtrRadpS_u11p5[6] = 
	{FPM_InitFixedPoint_m(0.0, u11p5_T),
	 FPM_InitFixedPoint_m(68.1875, u11p5_T),
	FPM_InitFixedPoint_m(178.656, u11p5_T),
	FPM_InitFixedPoint_m(247.468, u11p5_T),
	FPM_InitFixedPoint_m(313.5625, u11p5_T),
	FPM_InitFixedPoint_m(510.0, u11p5_T)};

#pragma DATA_SECTION(t_StdOpMtrEnvTblY_MtrNm_u4p12, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_StdOpMtrEnvTblY_MtrNm_u4p12[6] = 
	{FPM_InitFixedPoint_m(4.632, u4p12_T),
	 FPM_InitFixedPoint_m(4.632, u4p12_T),
	 FPM_InitFixedPoint_m(3.553, u4p12_T),
	 FPM_InitFixedPoint_m(2.927, u4p12_T),
	 FPM_InitFixedPoint_m(2.200, u4p12_T),
	 FPM_InitFixedPoint_m(0.000, u4p12_T)};


/********************************** Return ***********************************/
#pragma DATA_SECTION(k_RtnHWAuthSlew_UlspS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_RtnHWAuthSlew_UlspS_f32 = 0.5f;

#pragma DATA_SECTION(k_RtnLimit_MtrNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_RtnLimit_MtrNm_f32 = 0.1f;

#pragma DATA_SECTION(k_RtnOffsetRange_HWDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_RtnOffsetRange_HWDeg_f32 = 17.0f;

#pragma DATA_SECTION(k_RtnOffsetSlew_HwDegpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_RtnOffsetSlew_HwDegpS_f32 = 0.04f;


/********************************* SgnlCond **********************************/
#pragma DATA_SECTION(k_VehAccelSlewRate_KphpSecSq_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VehAccelSlewRate_KphpSecSq_f32 = 150.0f;

#pragma DATA_SECTION(k_VehSpdSlewRate_KphpSec_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VehSpdSlewRate_KphpSec_f32 = 35.0f;


/******************************** SrlComInput ********************************/
#pragma DATA_SECTION(k_BCM2MsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_BCM2MsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_BSM1MsgDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_BSM1MsgDiag_Cnt_str = {1, 1, 1};

#pragma DATA_SECTION(k_BSM1MsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_BSM1MsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_MOT1MsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MOT1MsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_MOT3MsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MOT3MsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_IPCMsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_IPCMsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_BCM_CMDMsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_BCM_CMDMsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_VehSpeedSigDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_VehSpeedSigDiag_Cnt_str = {1, 1, 1};

#pragma DATA_SECTION(k_NTCEnableTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_NTCEnableTimeout_mS_u16 = 1000U;

#pragma DATA_SECTION(k_DefaultVehSpd_Kph_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_DefaultVehSpd_Kph_f32 = 100.0f;

#pragma DATA_SECTION(k_BCMMsgPreIgnitionStart_ms_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_BCMMsgPreIgnitionStart_ms_u16 = 5000U;

#pragma DATA_SECTION(k_BCMInvMsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_BCMInvMsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_BCM2InvMsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_BCM2InvMsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_BSMInvMsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_BSMInvMsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_MOT1InvMsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MOT1InvMsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_MOT3InvMsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MOT3InvMsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_IPCInvMsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_IPCInvMsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_BSM1CRCDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_BSM1CRCDiag_Cnt_str = {1, 1, 1};

#pragma DATA_SECTION(k_BSM1MsgCounterDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_BSM1MsgCounterDiag_Cnt_str = {1, 1, 1};

#pragma DATA_SECTION(k_CfgCodeMsgTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_CfgCodeMsgTimeout_mS_u16 = 5000U;

#pragma DATA_SECTION(k_CTCEnableTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_CTCEnableTimeout_mS_u16 = 1000U;

#pragma DATA_SECTION(k_SrlComMsgCntrMissThreshold_Cnt_u08, ".FlashCalSeg");
CONST(uint8, CAL_CONST) k_SrlComMsgCntrMissThreshold_Cnt_u08 = 5;


/******************************* SrlComOutput ********************************/
#pragma DATA_SECTION(k_SASCALAuthorityThresh_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SASCALAuthorityThresh_Uls_f32 = 1.0f;

#pragma DATA_SECTION(k_ScomVelPolarity_Cnt_T_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_ScomVelPolarity_Cnt_T_f32 = 1.0f;

#pragma DATA_SECTION(k_ScomAngPolarity_Cnt_T_s8, ".FlashCalSeg");
CONST(sint8, CAL_CONST) k_ScomAngPolarity_Cnt_T_s8 = 1;


/******************************* StabilityComp *******************************/
#pragma DATA_SECTION(k_StCmpStabCmpNstep_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_StCmpStabCmpNstep_Cnt_u16 = 0U;

#pragma DATA_SECTION(k_StCmpStabCmpPNThresh_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_StCmpStabCmpPNThresh_Cnt_u16 = 5000U;

#pragma DATA_SECTION(k_StCmpStabCmpPstep_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_StCmpStabCmpPstep_Cnt_u16 = 0U;


/*********************************** StaMd ***********************************/
#pragma DATA_SECTION(k_StaMdsSysCDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_StaMdsSysCDiag_Cnt_str = {21,10,1};


/********************************** SVDiag ***********************************/
#pragma DATA_SECTION(k_ErrorFiltKn_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_ErrorFiltKn_Cnt_u16 = 1462U;

#pragma DATA_SECTION(k_ErrorThresh_Cnt_u32, ".FlashCalSeg");
CONST(uint32, CAL_CONST) k_ErrorThresh_Cnt_u32 = 14400UL;

#pragma DATA_SECTION(k_GateDriveDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_GateDriveDiag_Cnt_str = {1500, 512, 1};

#pragma DATA_SECTION(k_LowResPhsReas_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_LowResPhsReas_Cnt_str = {100,1,500};

#pragma DATA_SECTION(k_LowResPhsReasMaxTol_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_LowResPhsReasMaxTol_Uls_f32 = 1.2f;

#pragma DATA_SECTION(k_LowResPhsReasMinTol_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_LowResPhsReasMinTol_Uls_f32 = 0.4f;

#pragma DATA_SECTION(k_LRPRCommOffsetMargin_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_LRPRCommOffsetMargin_Uls_f32 = 1.05f;

#pragma DATA_SECTION(k_LRPRMtrVelDiagEnable_MtrRadpS_T_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_LRPRMtrVelDiagEnable_MtrRadpS_T_f32 = 300.0f;

#pragma DATA_SECTION(k_OnStateDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_OnStateDiag_Cnt_str = {1500, 512, 1};

#pragma DATA_SECTION(k_PhsReasEnableThresh_Cnt_u32, ".FlashCalSeg");
CONST(uint32, CAL_CONST) k_PhsReasEnableThresh_Cnt_u32 = 5760UL;

#pragma DATA_SECTION(k_PhsReasErrorTerm_Cnt_s16, ".FlashCalSeg");
CONST(sint16, CAL_CONST) k_PhsReasErrorTerm_Cnt_s16 = 0;


/********************************* SVDrvr_CM *********************************/
#pragma DATA_SECTION(k_DitherLPFKn_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_DitherLPFKn_Cnt_u16 = 20U;

#pragma DATA_SECTION(k_PWMBaseFrequency_Hz_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_PWMBaseFrequency_Hz_u16 = 16000U;


/******************************* ThrmDutyCycle *******************************/
#pragma DATA_SECTION(k_AbsTempDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_AbsTempDiag_Cnt_str = {140, 2, 1};

#pragma DATA_SECTION(k_AbsTmpTrqSlewLmt_MtrNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AbsTmpTrqSlewLmt_MtrNm_f32 = 0.023438f;

#pragma DATA_SECTION(k_CtrlTempSlc_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_CtrlTempSlc_Cnt_lgc = TRUE;

#pragma DATA_SECTION(k_DefaultIgnOffTime_Sec_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_DefaultIgnOffTime_Sec_f32 = 5000.0f;

#pragma DATA_SECTION(k_DutyCycFltTrshld_Uls_u16p0, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_DutyCycFltTrshld_Uls_u16p0 = 
	FPM_InitFixedPoint_m(92.0, u16p0_T);

#pragma DATA_SECTION(k_EOCCtrlTemp_DegC_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_EOCCtrlTemp_DegC_f32 = 70.0f;

#pragma DATA_SECTION(k_IgnOffCntrEnb_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_IgnOffCntrEnb_Cnt_lgc = FALSE;

#pragma DATA_SECTION(k_IgnOffMsgWaitTime_Sec_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_IgnOffMsgWaitTime_Sec_f32 = 0.5f;

#pragma DATA_SECTION(k_MtrPrTempSlc_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_MtrPrTempSlc_Cnt_lgc = TRUE;

#pragma DATA_SECTION(k_MultTempSlc_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_MultTempSlc_Cnt_lgc = TRUE;

#pragma DATA_SECTION(k_SlowFltTempSlc_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_SlowFltTempSlc_Cnt_lgc = FALSE;

#pragma DATA_SECTION(k_TrqCmdSlewDown_MtrNm_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_TrqCmdSlewDown_MtrNm_u9p7 = 
	FPM_InitFixedPoint_m(0.0390625, u9p7_T);

#pragma DATA_SECTION(k_TrqCmdSlewUp_MtrNm_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_TrqCmdSlewUp_MtrNm_u9p7 = 
	FPM_InitFixedPoint_m(0.0390625, u9p7_T);

#pragma DATA_SECTION(t_AbsCtrlTmpTblX_DegC_s15p0, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t_AbsCtrlTmpTblX_DegC_s15p0[4] = 
	{FPM_InitFixedPoint_m(122.0, s15p0_T),
	 FPM_InitFixedPoint_m(123.0, s15p0_T),
	 FPM_InitFixedPoint_m(125.0, s15p0_T),
	 FPM_InitFixedPoint_m(127.0, s15p0_T)};

#pragma DATA_SECTION(t_AbsCtrlTmpTblY_MtrNm_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_AbsCtrlTmpTblY_MtrNm_u9p7[4] = 
	{FPM_InitFixedPoint_m(2.703125, u9p7_T),
	 FPM_InitFixedPoint_m(2.242188, u9p7_T),
	 FPM_InitFixedPoint_m(1.828125, u9p7_T),
	 FPM_InitFixedPoint_m(0.0, u9p7_T)};

#pragma DATA_SECTION(t_AbsCuTmpTblX_DegC_s15p0, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t_AbsCuTmpTblX_DegC_s15p0[4] = 
	{FPM_InitFixedPoint_m(122.0, s15p0_T),
	 FPM_InitFixedPoint_m(123.0, s15p0_T),
	 FPM_InitFixedPoint_m(125.0, s15p0_T),
	 FPM_InitFixedPoint_m(127.0, s15p0_T)};

#pragma DATA_SECTION(t_AbsCuTmpTblY_MtrNm_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_AbsCuTmpTblY_MtrNm_u9p7[4] = 
	{FPM_InitFixedPoint_m(2.703125, u9p7_T),
	 FPM_InitFixedPoint_m(2.242188, u9p7_T),
	 FPM_InitFixedPoint_m(1.828125, u9p7_T),
	 FPM_InitFixedPoint_m(0.0, u9p7_T)};

#pragma DATA_SECTION(t_LastTblValNS_MtrNm_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_LastTblValNS_MtrNm_u9p7[5] = 
	{FPM_InitFixedPoint_m(1.0, u9p7_T), FPM_InitFixedPoint_m(1.0, u9p7_T),
	 FPM_InitFixedPoint_m(1.0, u9p7_T),
	 FPM_InitFixedPoint_m(0.34375, u9p7_T),
	 FPM_InitFixedPoint_m(0.34375, u9p7_T)};

#pragma DATA_SECTION(t_LastTblValS_MtrNm_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_LastTblValS_MtrNm_u9p7[5] = 
	{FPM_InitFixedPoint_m(0.96875, u9p7_T),
	 FPM_InitFixedPoint_m(0.96875, u9p7_T),
	 FPM_InitFixedPoint_m(0.96875, u9p7_T),
	 FPM_InitFixedPoint_m(0.3125, u9p7_T),
	 FPM_InitFixedPoint_m(0.3125, u9p7_T)};

#pragma DATA_SECTION(t_Mult1NSTblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult1NSTblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.0155029, u3p13_T),
	 FPM_InitFixedPoint_m(0.0155029, u3p13_T),
	 FPM_InitFixedPoint_m(0.0155029, u3p13_T),
	 FPM_InitFixedPoint_m(0.198975, u3p13_T),
	 FPM_InitFixedPoint_m(0.198975, u3p13_T)};

#pragma DATA_SECTION(t_Mult1STblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult1STblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.016235, u3p13_T),
	 FPM_InitFixedPoint_m(0.016235, u3p13_T),
	 FPM_InitFixedPoint_m(0.016235, u3p13_T),
	 FPM_InitFixedPoint_m(0.021973, u3p13_T),
	 FPM_InitFixedPoint_m(0.021973, u3p13_T)};

#pragma DATA_SECTION(t_Mult2NSTblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult2NSTblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.019409, u3p13_T),
	 FPM_InitFixedPoint_m(0.019409, u3p13_T),
	 FPM_InitFixedPoint_m(0.019409, u3p13_T),
	 FPM_InitFixedPoint_m(0.034302, u3p13_T),
	 FPM_InitFixedPoint_m(0.034302, u3p13_T)};

#pragma DATA_SECTION(t_Mult2STblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult2STblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.020386, u3p13_T),
	 FPM_InitFixedPoint_m(0.020386, u3p13_T),
	 FPM_InitFixedPoint_m(0.020386, u3p13_T),
	 FPM_InitFixedPoint_m(0.037842, u3p13_T),
	 FPM_InitFixedPoint_m(0.037842, u3p13_T)};

#pragma DATA_SECTION(t_Mult3NSTblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult3NSTblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.024292, u3p13_T),
	 FPM_InitFixedPoint_m(0.024292, u3p13_T),
	 FPM_InitFixedPoint_m(0.024292, u3p13_T),
	 FPM_InitFixedPoint_m(0.1564941, u3p13_T),
	 FPM_InitFixedPoint_m(0.1564941, u3p13_T)};

#pragma DATA_SECTION(t_Mult3STblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult3STblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.025635, u3p13_T),
	 FPM_InitFixedPoint_m(0.025635, u3p13_T),
	 FPM_InitFixedPoint_m(0.025635, u3p13_T),
	 FPM_InitFixedPoint_m(0.208374, u3p13_T),
	 FPM_InitFixedPoint_m(0.208374, u3p13_T)};

#pragma DATA_SECTION(t_Mult4NSTblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult4NSTblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T)};

#pragma DATA_SECTION(t_Mult4STblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult4STblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T)};

#pragma DATA_SECTION(t_Mult5NSTblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult5NSTblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.121826, u3p13_T),
	 FPM_InitFixedPoint_m(0.121826, u3p13_T),
	 FPM_InitFixedPoint_m(0.121826, u3p13_T),
	 FPM_InitFixedPoint_m(1.16394, u3p13_T),
	 FPM_InitFixedPoint_m(1.16394, u3p13_T)};

#pragma DATA_SECTION(t_Mult5STblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult5STblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.121826, u3p13_T),
	 FPM_InitFixedPoint_m(0.121826, u3p13_T),
	 FPM_InitFixedPoint_m(0.121826, u3p13_T),
	 FPM_InitFixedPoint_m(1.16394, u3p13_T),
	 FPM_InitFixedPoint_m(1.16394, u3p13_T)};

#pragma DATA_SECTION(t_Mult6NSTblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult6NSTblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T)};

#pragma DATA_SECTION(t_Mult6STblY_Uls_u3p13, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_Mult6STblY_Uls_u3p13[5] = 
	{FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T),
	 FPM_InitFixedPoint_m(0.000122, u3p13_T)};

#pragma DATA_SECTION(t_MultTblX_DegC_s15p0, ".FlashCalSeg");
CONST(sint16, CAL_CONST) t_MultTblX_DegC_s15p0[5] = 
	{FPM_InitFixedPoint_m(-40.0, s15p0_T),
	 FPM_InitFixedPoint_m(0.0, s15p0_T), FPM_InitFixedPoint_m(83.0, s15p0_T),
	 FPM_InitFixedPoint_m(84.0, s15p0_T),
	 FPM_InitFixedPoint_m(85.0, s15p0_T)};

#pragma DATA_SECTION(t_ThrmLoadLmtTblX_Uls_u16p0, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_ThrmLoadLmtTblX_Uls_u16p0[8] = 
	{FPM_InitFixedPoint_m(0.0, u16p0_T), FPM_InitFixedPoint_m(76.0, u16p0_T),
	 FPM_InitFixedPoint_m(80.0, u16p0_T),
	 FPM_InitFixedPoint_m(84.0, u16p0_T),
	 FPM_InitFixedPoint_m(88.0, u16p0_T),
	 FPM_InitFixedPoint_m(92.0, u16p0_T),
	 FPM_InitFixedPoint_m(96.0, u16p0_T),
	 FPM_InitFixedPoint_m(100.0, u16p0_T)};

#pragma DATA_SECTION(t_ThrmLoadLmtTblY_MtrNm_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_ThrmLoadLmtTblY_MtrNm_u9p7[8] = 
	{FPM_InitFixedPoint_m(2.703125, u9p7_T),
	 FPM_InitFixedPoint_m(2.703125, u9p7_T),
	 FPM_InitFixedPoint_m(2.703125, u9p7_T),
	 FPM_InitFixedPoint_m(2.703125, u9p7_T),
	 FPM_InitFixedPoint_m(2.242188, u9p7_T),
	 FPM_InitFixedPoint_m(1.828125, u9p7_T),
	 FPM_InitFixedPoint_m(1.414063, u9p7_T),
	 FPM_InitFixedPoint_m(1.0, u9p7_T)};


/******************************* TMS570_uDiag ********************************/
#pragma DATA_SECTION(k_FlashECCDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_FlashECCDiag_Cnt_str = {100, 5, 1};

#pragma DATA_SECTION(k_MtrCtrlMaxCount_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MtrCtrlMaxCount_Cnt_u16 = 120U;

#pragma DATA_SECTION(k_MtrCtrlMinCount_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_MtrCtrlMinCount_Cnt_u16 = 10U;

#pragma DATA_SECTION(k_OneMsLoopMaxCount_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_OneMsLoopMaxCount_Cnt_u16 = 11U;

#pragma DATA_SECTION(k_OneMsLoopMinCount_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_OneMsLoopMinCount_Cnt_u16 = 1U;

#pragma DATA_SECTION(k_RAMECCDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_RAMECCDiag_Cnt_str = {100, 5, 1};

#pragma DATA_SECTION(k_VIMParErrThrsh_Cnt_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_VIMParErrThrsh_Cnt_u16 = 20U;


/********************************** TqRsDg ***********************************/
#pragma DATA_SECTION(k_CurrDiagLambdaMinMax_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CurrDiagLambdaMinMax_Volt_f32 = 3.0f;

#pragma DATA_SECTION(k_CurrDiagMtrEnvTblMax_MtrNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CurrDiagMtrEnvTblMax_MtrNm_f32 = 4.6f;

#pragma DATA_SECTION(k_CurrDiagPrim_Cnt_Str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_CurrDiagPrim_Cnt_Str = {200,2,1};

#pragma DATA_SECTION(k_CurrDiagPrimErrorThresh_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CurrDiagPrimErrorThresh_Volt_f32 = 20.0f;

#pragma DATA_SECTION(k_CurrDiagPrimLPFKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CurrDiagPrimLPFKn_Hz_f32 = 1.0f;

#pragma DATA_SECTION(k_CurrDiagSec_Cnt_Str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_CurrDiagSec_Cnt_Str = {200,2,1};

#pragma DATA_SECTION(k_CurrDiagSecErrorThresh_Volt_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CurrDiagSecErrorThresh_Volt_f32 = 20.0f;

#pragma DATA_SECTION(k_CurrDiagSecLPFKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CurrDiagSecLPFKn_Hz_f32 = 1.0f;

#pragma DATA_SECTION(k_CurrDiagSecTrqLmtThresh_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_CurrDiagSecTrqLmtThresh_Uls_f32 = 0.0f;


/******************************* TuningSelAuth *******************************/
#pragma DATA_SECTION(k_TunSelHwTrqLPFKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TunSelHwTrqLPFKn_Hz_f32 = 5.0f;

#pragma DATA_SECTION(k_TunSelHwTrqThresh_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TunSelHwTrqThresh_HwNm_f32 = 2.0f;

#pragma DATA_SECTION(k_TunSelVehSpdThresh_Kph_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TunSelVehSpdThresh_Kph_f32 = 100.0f;


/********************************** VehDyn ***********************************/
#pragma DATA_SECTION(k_AutoCntrHiSpdCntrWindow_HwDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrHiSpdCntrWindow_HwDeg_f32 = 5.0f;

#pragma DATA_SECTION(k_AutoCntrHiSpdFilt1Kn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrHiSpdFilt1Kn_Hz_f32 = 0.025f;

#pragma DATA_SECTION(k_AutoCntrHiSpdFilt2Kn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrHiSpdFilt2Kn_Hz_f32 = 0.0002f;

#pragma DATA_SECTION(k_AutoCntrHiSpdTimer1_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_AutoCntrHiSpdTimer1_mS_u16 = 1500U;

#pragma DATA_SECTION(k_AutoCntrHiSpdTimer1MtrVel_MtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer1MtrVel_MtrRadpS_f32 = 20.0f;

#pragma DATA_SECTION(k_AutoCntrHiSpdTimer1PinTrq_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer1PinTrq_HwNm_f32 = 4.0f;

#pragma DATA_SECTION(k_AutoCntrHiSpdTimer1VehSpd_kph_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer1VehSpd_kph_f32 = 65.0f;

#pragma DATA_SECTION(k_AutoCntrHiSpdTimer2_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_AutoCntrHiSpdTimer2_mS_u16 = 2000U;

#pragma DATA_SECTION(k_AutoCntrHiSpdTimer4_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_AutoCntrHiSpdTimer4_mS_u16 = 2000U;

#pragma DATA_SECTION(k_AutoCntrHiSpdTimer4CntrWindow_HwDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4CntrWindow_HwDeg_f32 = 5.0f;

#pragma DATA_SECTION(k_AutoCntrHiSpdTimer4MtrVel_MtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4MtrVel_MtrRadpS_f32 = 20.0f;

#pragma DATA_SECTION(k_AutoCntrHiSpdTimer4PinTrq_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4PinTrq_HwNm_f32 = 3.0f;

#pragma DATA_SECTION(k_AutoCntrHiSpdTimer4VehSpd_kph_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4VehSpd_kph_f32 = 65.0f;

#pragma DATA_SECTION(k_AutoCntrLoSpdCntrWindow_HwDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrLoSpdCntrWindow_HwDeg_f32 = 8.0f;

#pragma DATA_SECTION(k_AutoCntrLoSpdFilt1Kn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrLoSpdFilt1Kn_Hz_f32 = 0.1f;

#pragma DATA_SECTION(k_AutoCntrLoSpdFilt2Kn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrLoSpdFilt2Kn_Hz_f32 = 0.005f;

#pragma DATA_SECTION(k_AutoCntrLoSpdTimer1_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_AutoCntrLoSpdTimer1_mS_u16 = 500U;

#pragma DATA_SECTION(k_AutoCntrLoSpdTimer1MtrVel_MtrRadpS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrLoSpdTimer1MtrVel_MtrRadpS_f32 = 30.0f;

#pragma DATA_SECTION(k_AutoCntrLoSpdTimer1PinTrq_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrLoSpdTimer1PinTrq_HwNm_f32 = 4.0f;

#pragma DATA_SECTION(k_AutoCntrLoSpdTimer1VehSpd_kph_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrLoSpdTimer1VehSpd_kph_f32 = 20.0f;

#pragma DATA_SECTION(k_AutoCntrLoSpdTimer2_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_AutoCntrLoSpdTimer2_mS_u16 = 2000U;

#pragma DATA_SECTION(k_AutoCntrPinTrqLPFCoeffKn_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_AutoCntrPinTrqLPFCoeffKn_Hz_f32 = 0.035f;

#pragma DATA_SECTION(k_HiSpdVDAuthority_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HiSpdVDAuthority_Uls_f32 = 1.0f;

#pragma DATA_SECTION(k_LoSpdVDAuthority_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_LoSpdVDAuthority_Uls_f32 = 1.0f;

#pragma DATA_SECTION(k_SLPEnableBFCheck_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_SLPEnableBFCheck_Cnt_lgc = TRUE;

#pragma DATA_SECTION(k_SLPHwAuthority_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SLPHwAuthority_Uls_f32 = 0.3f;

#pragma DATA_SECTION(k_SLPMinHwAuthToStoreHwPos_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SLPMinHwAuthToStoreHwPos_Uls_f32 = 0.1f;

#pragma DATA_SECTION(k_TravelXCDeadband_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TravelXCDeadband_Uls_f32 = 20.0f;

#pragma DATA_SECTION(k_TravelXCHwAuthority_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_TravelXCHwAuthority_Uls_f32 = 0.3f;

#pragma DATA_SECTION(k_HwTqMgnThd_HwNm_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_HwTqMgnThd_HwNm_f32 = 0.05f;

#pragma DATA_SECTION(k_VehDyn_TravelXCDeadbandTolr_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VehDyn_TravelXCDeadbandTolr_Uls_f32 = 5.0f;

#pragma DATA_SECTION(k_VehDyn_ErrTolr_HwDeg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VehDyn_ErrTolr_HwDeg_f32 = 5.0f;

#pragma DATA_SECTION(k_VehDyn_SmoothCoeff_Uls_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VehDyn_SmoothCoeff_Uls_f32 = 0.2f;

#pragma DATA_SECTION(k_SrlHwAgVldTiThd_mS_u32, ".FlashCalSeg");
CONST(uint32, CAL_CONST) k_SrlHwAgVldTiThd_mS_u32 = 500UL;


/********************************* VehPwrMd **********************************/
#pragma DATA_SECTION(k_RampDnRt_UlspmS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_RampDnRt_UlspmS_f32 = 0.0005f;

#pragma DATA_SECTION(k_RampUpRtLoSpd_UlspmS_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_RampUpRtLoSpd_UlspmS_f32 = 0.0005f;

#pragma DATA_SECTION(k_VehSpdAstLmt_Kph_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VehSpdAstLmt_Kph_f32 = 5.0f;

#pragma DATA_SECTION(k_VehSpdEngOn_Kph_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VehSpdEngOn_Kph_f32 = 5.0f;

#pragma DATA_SECTION(k_CTermOpModeStsTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_CTermOpModeStsTimeout_mS_u16 = 0U;

#pragma DATA_SECTION(k_CTermShutdownTimeout_mS_u16, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_CTermShutdownTimeout_mS_u16 = 0U;


/********************************* VehSpdLmt *********************************/
#pragma DATA_SECTION(k_PosMaxOfstOne_HwDeg_u12p4, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_PosMaxOfstOne_HwDeg_u12p4 = 
	FPM_InitFixedPoint_m(140.0, u12p4_T);

#pragma DATA_SECTION(k_PosMaxOfstTwo_HwDeg_u12p4, ".FlashCalSeg");
CONST(uint16, CAL_CONST) k_PosMaxOfstTwo_HwDeg_u12p4 = 
	FPM_InitFixedPoint_m(120.0, u12p4_T);

#pragma DATA_SECTION(t_MaxAsstTblX_Kph_u9p7, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MaxAsstTblX_Kph_u9p7[5] = 
	{ FPM_InitFixedPoint_m(0.0, u9p7_T), FPM_InitFixedPoint_m(25.0, u9p7_T),
	 FPM_InitFixedPoint_m(50.0, u9p7_T), FPM_InitFixedPoint_m(65.0, u9p7_T),
	 FPM_InitFixedPoint_m(75.0, u9p7_T) };

#pragma DATA_SECTION(t_MaxAsstTblY_MtrNm_u5p11, ".FlashCalSeg");
CONST(uint16, CAL_CONST) t_MaxAsstTblY_MtrNm_u5p11[5] = 
	{ FPM_InitFixedPoint_m(8.8, u5p11_T),FPM_InitFixedPoint_m(8.8, u5p11_T),
	FPM_InitFixedPoint_m(8.8, u5p11_T),FPM_InitFixedPoint_m(8.8, u5p11_T),
	FPM_InitFixedPoint_m(8.8, u5p11_T) };


/********************************* DigColPs **********************************/
#pragma DATA_SECTION(k_ColAngSenseLPFFc_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_ColAngSenseLPFFc_Hz_f32 = 10.0f;

#pragma DATA_SECTION(k_SpurAngSenseLPFFc_Hz_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_SpurAngSenseLPFFc_Hz_f32 = 10.0f;

#pragma DATA_SECTION(k_SelectFromColumn_Cnt_lgc, ".FlashCalSeg");
CONST(boolean, CAL_CONST) k_SelectFromColumn_Cnt_lgc = FALSE;

#pragma DATA_SECTION(k_StepDetect_Deg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_StepDetect_Deg_f32 = 240.0f;

#pragma DATA_SECTION(k_VernCorrErrorThresh_Deg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VernCorrErrorThresh_Deg_f32 = 4.8f;

#pragma DATA_SECTION(k_VernCorrErrorDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_VernCorrErrorDiag_Cnt_str = {20,4,1};

#pragma DATA_SECTION(k_SkipStepErrDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_SkipStepErrDiag_Cnt_str = {21,20,1};

#pragma DATA_SECTION(k_VernOORangeThresh_Deg_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_VernOORangeThresh_Deg_f32 = 1200.0f;

#pragma DATA_SECTION(k_SenseDetErrDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_SenseDetErrDiag_Cnt_str = {2,1,1};

#pragma DATA_SECTION(k_SenseParityErrDiag_Cnt_str, ".FlashCalSeg");
CONST(DiagSettings_Str, CAL_CONST) k_SenseParityErrDiag_Cnt_str = {2,1,1};

#pragma DATA_SECTION(k_ColSensorI2CAddress_Cnt_u08, ".FlashCalSeg");
CONST(uint8, CAL_CONST) k_ColSensorI2CAddress_Cnt_u08 = 14;

#pragma DATA_SECTION(k_SpurSensorI2CAddress_Cnt_u08, ".FlashCalSeg");
CONST(uint8, CAL_CONST) k_SpurSensorI2CAddress_Cnt_u08 = 13;

#pragma DATA_SECTION(k_I2CHWInitTransactionTime_Sec_f32, ".FlashCalSeg");
CONST(float32, CAL_CONST) k_I2CHWInitTransactionTime_Sec_f32 = 2.0f;



/*********************** Start of Code Footer ************************/

CONSTP2CONST(TUNING_Y_Str, AUTOMATIC, AUTOMATIC) T_TunSetSelectionTbl_Ptr_Str[D_NUMOFTUNSETS_CNT_U16] =
		{	&k_TunSet0_Cnt_Str,
			&k_TunSet1_Cnt_Str,
			&k_TunSet2_Cnt_Str,
			&k_TunSet3_Cnt_Str,
			&k_TunSet4_Cnt_Str,
			&k_TunSet5_Cnt_Str,
			&k_TunSet6_Cnt_Str,
			&k_TunSet7_Cnt_Str			};

CONSTP2CONST(TUNING_P_Str, AUTOMATIC, AUTOMATIC) T_TunPersSelectionTbl_Ptr_Str[D_NUMOFTUNSETS_CNT_U16][D_NUMOFPERS_CNT_U16] =
		{	{
				&k_TunSet0Per0_Cnt_Str,
				&k_TunSet0Per1_Cnt_Str},
				{&k_TunSet1Per0_Cnt_Str,
				&k_TunSet1Per1_Cnt_Str},
				{&k_TunSet2Per0_Cnt_Str,
				&k_TunSet2Per1_Cnt_Str},
				{&k_TunSet3Per0_Cnt_Str,
				&k_TunSet3Per1_Cnt_Str},
				{&k_TunSet4Per0_Cnt_Str,
				&k_TunSet4Per1_Cnt_Str},
				{&k_TunSet5Per0_Cnt_Str,
				&k_TunSet5Per1_Cnt_Str},
				{&k_TunSet6Per0_Cnt_Str,
				&k_TunSet6Per1_Cnt_Str},
				{&k_TunSet7Per0_Cnt_Str,
				&k_TunSet7Per1_Cnt_Str}
										};












































