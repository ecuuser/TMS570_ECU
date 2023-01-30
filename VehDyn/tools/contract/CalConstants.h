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
 * Date Created:      Sun Feb 26 18:00:00 2012
 * %version:          EA3#4 %
 * %derived_by:       gzkys7 %
 * %date_modified:    Fri Aug 23 15:11:55 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 */

#ifndef CALCONSTANTS_H
#define CALCONSTANTS_H

#include "Std_Types.h"

/*********************** Start of Auto Generated Code ************************/

/****************** File Generated on 11/30/2015 5:04:29 PM ******************/
/************************* Vehicle Dynamics - Rev 11 *************************/



extern CONST(float32, CAL_CONST) k_SysKinRatio_MtrDegpHwDeg_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrPinTrqLPFCoeffKn_Hz_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdTimer1MtrVel_MtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdTimer1VehSpd_kph_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdTimer1PinTrq_HwNm_f32;
extern CONST(uint16, CAL_CONST) k_AutoCntrLoSpdTimer1_mS_u16;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdFilt1Kn_Hz_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdCntrWindow_HwDeg_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrLoSpdFilt2Kn_Hz_f32;
extern CONST(uint16, CAL_CONST) k_AutoCntrLoSpdTimer2_mS_u16;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer1MtrVel_MtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer1VehSpd_kph_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer1PinTrq_HwNm_f32;
extern CONST(uint16, CAL_CONST) k_AutoCntrHiSpdTimer1_mS_u16;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdFilt1Kn_Hz_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdCntrWindow_HwDeg_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdFilt2Kn_Hz_f32;
extern CONST(uint16, CAL_CONST) k_AutoCntrHiSpdTimer2_mS_u16;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4MtrVel_MtrRadpS_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4VehSpd_kph_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4PinTrq_HwNm_f32;
extern CONST(float32, CAL_CONST) k_AutoCntrHiSpdTimer4CntrWindow_HwDeg_f32;
extern CONST(uint16, CAL_CONST) k_AutoCntrHiSpdTimer4_mS_u16;
extern CONST(float32, CAL_CONST) k_LoSpdVDAuthority_Uls_f32;
extern CONST(float32, CAL_CONST) k_HiSpdVDAuthority_Uls_f32;
extern CONST(boolean, CAL_CONST) k_SLPEnableBFCheck_Cnt_lgc;
extern CONST(float32, CAL_CONST) k_SLPHwAuthority_Uls_f32;
extern CONST(float32, CAL_CONST) k_TravelXCDeadband_Uls_f32;
extern CONST(float32, CAL_CONST) k_TravelXCHwAuthority_Uls_f32;
extern CONST(float32, CAL_CONST) k_SLPMinHwAuthToStoreHwPos_Uls_f32;
extern CONST(float32, CAL_CONST) k_HwTqMgnThd_HwNm_f32;
extern CONST(uint32, CAL_CONST) k_SrlHwAgVldTiThd_mS_u32;
extern CONST(float32, CAL_CONST) k_VehDyn_TravelXCDeadbandTolr_Uls_f32;
extern CONST(float32, CAL_CONST) k_VehDyn_ErrTolr_HwDeg_f32;
extern CONST(float32, CAL_CONST) k_VehDyn_SmoothCoeff_Uls_f32;
#endif


