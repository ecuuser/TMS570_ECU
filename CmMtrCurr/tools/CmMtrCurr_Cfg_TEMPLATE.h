/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : CmMtrCurr_Cfg.h
* Module Description: CmMtrCurr Complex Driver configuration
* Product           : Gen II Plus - EA3.0
* Author            : Owen Tosh
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sat Mar 23 13:00:00 2013
* %version:          1 %
* %derived_by:       mzjphh %
* %date_modified:    Thu Sep  5 13:17:06 2013 %
*---------------------------------------------------------------------------*/


#ifndef CMMTRCURR_CFG_H
#define CMMTRCURR_CFG_H


#include "CDD_Data.h"
#include "Adc2.h"
#include "Sa_MtrPos.h"

#define CmMtrCurr_Read_MRFMtrVel_MtrRadpS_f32(ptr)		*(ptr) = CDD_MRFMtrVel_MtrRadpS_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define CmMtrCurr_Read_Vecu_Volt_f32(ptr)				*(ptr) = CDD_Vecu_Volt_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define CmMtrCurr_Read_Phs1Curr_Cnt_u16(ptr)			*(ptr) = Adc2_GetPhsBCurr_Cnt_u16_m
#define CmMtrCurr_Read_Phs2Curr_Cnt_u16(ptr)			*(ptr) = Adc2_GetPhsCCurr_Cnt_u16_m
#define CmMtrCurr_Read_DCPhsAComp_Cnt_u16(ptr)			*(ptr) = CDD_DCPhsBComp_Cnt_G_u16p0
#define CmMtrCurr_Read_DCPhsBComp_Cnt_u16(ptr)			*(ptr) = CDD_DCPhsBComp_Cnt_G_u16p0
#define CmMtrCurr_Read_DCPhsCComp_Cnt_u16(ptr)			*(ptr) = CDD_DCPhsCComp_Cnt_G_u16p0
#define CmMtrCurr_Read_MtrCurr1TempOffset_Volt_f32(ptr)	*(ptr) = CDD_MtrCurr1TempOffset_Volt_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define CmMtrCurr_Read_MtrCurr2TempOffset_Volt_f32(ptr)	*(ptr) = CDD_MtrCurr2TempOffset_Volt_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define CmMtrCurr_Read_MtrElecPol_Cnt_s08(ptr)			*(ptr) = CDD_MtrElecPol_Cnt_G_s8
#define CmMtrCurr_Read_MtrPosElec_Rev_u0p16(ptr)		*(ptr) = MtrPos_CorrectedMtrPos_Rev_G_u0p16

/***Added for FDD 1C V8***/
#define CmMtrCurr_Read_ADC2OffsetComp_Cnt_u8p8(ptr)     *(ptr) = CDD_ADC2OffsetComp_Cnt_G_u8p8 /* Map the output to the ADC2 calibration compensation */


#define CmMtrCurr_Write_ElecPosDelayComp_Rad_f32(val)	CDD_ElecPosDelayComp_Rad_G_f32 = (val)
#define CmMtrCurr_Write_MtrCurrQax_Amp_f32(val)			CDD_MtrCurrQax_Amp_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_MtrCurrDax_Amp_f32(val)			CDD_MtrCurrDax_Amp_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_CorrMtrCurrPosition_Rev_f32(val)		CDD_CorrMtrPosElec_Rev_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_MtrCurrK1_Amps_f32(val)			CDD_MtrCurrK1_Amps_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_MtrCurrK2_Amps_f32(val)			CDD_MtrCurrK2_Amps_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_MtrCurr1_Volts_f32(val)			CDD_MtrCurr1_Volts_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_MtrCurr2_Volts_f32(val)			CDD_MtrCurr2_Volts_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)


#endif
