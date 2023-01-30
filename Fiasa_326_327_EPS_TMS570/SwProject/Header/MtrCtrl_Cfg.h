/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : MtrCtrl_Cfg.h
* Module Description: Motor control Complex Driver configuration
* Product           : Gen II Plus - EA3.0
* Author            : Selva Sengottaiyan
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sat Mar 23 13:00:00 2013
* %version:          EA3#3 %
* %derived_by:       nzdx8v %
* %date_modified:    Fri Aug 30 10:52:35 2013 %
*---------------------------------------------------------------------------*/


#ifndef MTRCTRL_CFG_H
#define MTRCTRL_CFG_H


#include "CDD_Data.h"


#define MtrCntrl_Read_MtrCurrQax_Amp_f32(ptr)    			*(ptr) = CDD_MtrCurrQax_Amp_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16]
#define MtrCntrl_Read_MtrCurrDax_Amp_f32(ptr)    			*(ptr) = CDD_MtrCurrDax_Amp_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16]
#define MtrCntrl_Read_Vecu_Volt_f32(ptr)    				*(ptr) = CDD_Vecu_Volt_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define MtrCntrl_Read_ModIdxSrlComSvcDft_Cnt_lgc(ptr)    	*(ptr) = CDD_ModIdxSrlComSvcDft_Cnt_G_u16
#define MtrCntrl_Read_SysState_Cnt_Enum(ptr)    			*(ptr) = CDD_SysState_Cnt_G_Enum[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define MtrCntrl_Read_MtrCurrOffComOffset_Cnt_u16(ptr)   	*(ptr) = CDD_MtrCurrOffComOffset_Cnt_G_u16[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define MtrCntrl_Read_MtrElecPol_Cnt_s8(ptr)    			*(ptr) = CDD_MtrElecPol_Cnt_G_s8
#define MtrCntrl_Read_MtrPosElec_Rev_u0p16(ptr)   			*(ptr) = CDD_CorrectedElecMtrPos_Rev_G_u0p16[CDD_CDDDataAccessBfr_Cnt_G_u16]
#define MtrCntrl_Read_IvtrLoaMtgtnEn_Cnt_lgc(ptr)   		*(ptr) = CDD_IvtrLoaMtgtnEn_Cnt_G_u16         /********* Default Value **********/
#define MtrCntrl_Read_MotCurrLoaMtgtnEn_Cnt_lgc(ptr)   		*(ptr) = CDD_MotCurrLoaMtgtnEn_Cnt_G_u16      /********* Default Value **********/


#define MtrCntrl_Write_MtrCurrQaxFinalRef_Amp_f32(val)		CDD_MtrCurrQaxFinalRef_Amp_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16]	= (val)
#define MtrCntrl_Write_MtrDaxVoltage_Volt_f32(val)			CDD_MtrVoltDax_Volt_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16]			= (val)
#define MtrCntrl_Write_MtrQaxVoltage_Volt_f32(val)			CDD_MtrVoltQax_Volt_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16]			= (val)
#define MtrCntrl_Write_ModIdx_Uls_u16p16(val)               CDD_ModIndexFinal_Uls_G_u16p16           							= (val)
#define MtrCntrl_Write_PhaseAdvanceFinal_Rev_u0p16(val)   	CDD_PhaseAdvanceFinal_Cnt_G_u16										= (val)
#define MtrCntrl_Write_CommOffset_Cnt_u16(val)				CDD_CommOffset_Cnt_G_u16											= (val)




#endif
