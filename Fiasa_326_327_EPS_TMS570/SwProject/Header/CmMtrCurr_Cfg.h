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
* %version:          6 %
* %derived_by:       nzx5jd %
* %date_modified:    Thu Sep 12 11:40:34 2013 %
*---------------------------------------------------------------------------*/


#ifndef CMMTRCURR_CFG_H
#define CMMTRCURR_CFG_H


#include "CDD_Data.h"
#include "Dma.h"
#include "Adc2.h"


#define CmMtrCurr_Read_MRFMtrVel_MtrRadpS_f32(ptr)		*(ptr) = CDD_MRFMtrVel_MtrRadpS_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define CmMtrCurr_Read_Vecu_Volt_f32(ptr)				*(ptr) = CDD_Vecu_Volt_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define CmMtrCurr_Read_Phs1Curr_Cnt_u16(ptr)			*(ptr) = DMAData_G_str.FastADC_Cnt_u16[D_PHASEBCHN_CNT_U16] & 0x0FFFu
#define CmMtrCurr_Read_Phs2Curr_Cnt_u16(ptr)			*(ptr) = DMAData_G_str.FastADC_Cnt_u16[D_PHASEACHN_CNT_U16] & 0x0FFFu
#define CmMtrCurr_Read_DCPhsAComp_Cnt_u16(ptr)			*(ptr) = CDD_DCPhsComp_Cnt_G_u16[0u]
#define CmMtrCurr_Read_DCPhsBComp_Cnt_u16(ptr)			*(ptr) = CDD_DCPhsComp_Cnt_G_u16[1u]
#define CmMtrCurr_Read_DCPhsCComp_Cnt_u16(ptr)			*(ptr) = CDD_DCPhsComp_Cnt_G_u16[2u]
#define CmMtrCurr_Read_MtrCurr1TempOffset_Volt_f32(ptr)	*(ptr) = CDD_MtrCurr1TempOffset_Volt_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define CmMtrCurr_Read_MtrCurr2TempOffset_Volt_f32(ptr)	*(ptr) = CDD_MtrCurr2TempOffset_Volt_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define CmMtrCurr_Read_MtrElecPol_Cnt_s08(ptr)			*(ptr) = CDD_MtrElecPol_Cnt_G_s8
#define CmMtrCurr_Read_MtrPosElec_Rev_u0p16(ptr)		*(ptr) = CDD_CorrectedElecMtrPos_Rev_G_u0p16[CDD_CDDDataAccessBfr_Cnt_G_u16]
#define CmMtrCurr_Read_ADC2OffsetComp_Cnt_u8p8(ptr)		*(ptr) = CDD_ADC2OffsetComp_Cnt_G_u8p8

#define CmMtrCurr_Write_ElecPosDelayComp_Rad_f32(val)	(void)0
#define CmMtrCurr_Write_MtrCurrQax_Amp_f32(val)			CDD_MtrCurrQax_Amp_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_MtrCurrDax_Amp_f32(val)			CDD_MtrCurrDax_Amp_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_CorrMtrCurrPosition_Rev_f32(val) CDD_CorrMtrCurrPosition_Rev_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_MtrCurrK1_Amps_f32(val)			CDD_MtrCurrK1_Amps_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_MtrCurrK2_Amps_f32(val)			CDD_MtrCurrK2_Amps_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_MtrCurr1_Volts_f32(val)			CDD_MtrCurr1_Volts_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)
#define CmMtrCurr_Write_MtrCurr2_Volts_f32(val)			CDD_MtrCurr2_Volts_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16] = (val)


#endif
