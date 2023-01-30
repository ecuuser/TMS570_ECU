 /*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_Sweep.h
* Module Description: Header file for data communicated between Nexteer
*                      Complex Device Drivers (CDD)
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue Dec  7 20:09:21 2010
* %version:          1 %
* %derived_by:       nzt9hv %
* %date_modified:    Tue Jan  8 12:27:18 2013 % 
*---------------------------------------------------------------------------*/

#ifndef AP_SWEEP_H
#define AP_SWEEP_H
 extern VAR(boolean, AUTOMATIC) SweepModeEn_Cnt_M_lgc;
 extern VAR(uint16, AUTOMATIC) SweepConfig_Cnt_M_u16;
 extern VAR(uint16, AUTOMATIC) SweepGain_MtrNmpHwNm_M_u1p15;
 extern VAR(float32, AUTOMATIC) MtrTrqQuantization_Uls_M_f32;
 extern VAR(float32, AUTOMATIC) SweepTorque_HwNm_M_f32;
 
 #endif