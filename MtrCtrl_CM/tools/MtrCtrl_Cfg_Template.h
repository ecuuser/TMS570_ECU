/*****************************************************************************
/*****************************************************************************
* Copyright 2015 Nexteer Automotive
* Nexteer Confidential
*
* Module File Name  : MtrCtrl_Cfg.h
* Module Description: Configuration file of DiagMgr module
* Product           : Gen II Plus - EA3.0
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sat Mar 23 13:00:00 2013
* %version:          3 %
* %derived_by:       nzt9hv %
* %date_modified:    Wed Jun  5 11:31:23 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 03/11/15   2       Selva      Initial template creation                                                    CR12888
 */


#ifndef MTRCTRL_CFG_H
#define MTRCTRL_CFG_H


#include "CDD_Data.h"



#define 	MtrCntrl_Read_MtrCurrQax_Amp_f32(ptr)    			*(ptr) =  CDD_MtrCurrQax_Amp_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16]
#define 	MtrCntrl_Read_MtrCurrDax_Amp_f32(ptr)    			*(ptr) =  CDD_MtrCurrDax_Amp_G_f32[CDD_CDDDataAccessBfr_Cnt_G_u16]
#define 	MtrCntrl_Read_ModIdxSrlComSvcDft_Cnt_lgc(ptr)    	*(ptr) =  CDD_ModIdxSrlComSvcDft_Cnt_G_u16
#define 	MtrCntrl_Read_SysState_Cnt_Enum(ptr)    			*(ptr) =  CDD_SysState_Cnt_G_Enum
#define 	MtrCntrl_Read_MtrCurrOffComOffset_Cnt_u16(ptr)   	*(ptr) =  CDD_MtrCurrOffComOffset_Cnt_G_u16[CDD_CDDDataAccessBfr_Cnt_G_u16]
#define 	MtrCntrl_Read_MtrElecPol_Cnt_s8(ptr)    			*(ptr) =  CDD_MtrElecPol_Cnt_G_s8
#define 	MtrCntrl_Read_MtrPosElec_Rev_u0p16(ptr)   			*(ptr) =   CDD_MtrPosElec_Rev_G_u0p16[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]
#define 	MtrCntrl_Read_IvtrLoaMtgtnEn_Cnt_lgc(ptr)   			*(ptr) =                           /********* from LOA manager through CDD interface**********/       
#define 	MtrCntrl_Read_MotCurrLoaMtgtnEn_Cnt_lgc(ptr)   			*(ptr) =                           /********* from LOA manager through CDD interface**********/ 


#define MtrCntrl_Write_MtrCurrQaxFinalRef_Amp_f32(val)           CDD_MtrCurrQaxFinalRef_Amp_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]        = (val)
#define MtrCntrl_Write_MtrDaxVoltage_Volt_f32(val)               CDD_MtrVoltDax_Volt_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]            = (val)
#define MtrCntrl_Write_MtrQaxVoltage_Volt_f32(val)               CDD_MtrVoltQax_Volt_G_f32[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]            = (val)
#define MtrCntrl_Write_ModIdx_Uls_u16p16(val)                    CDD_ModIdxFinal_Uls_G_u16p16           = (val)
#define MtrCntrl_Write_PhaseAdvanceFinal_Rev_u0p16(val)   		 CDD_PhaseAdvFinal_Cnt_G_u16=(val)
															
#define MtrCntrl_Write_CommOffset_Cnt_u16(val)	                 CDD_PhaseAdvFinal_Cnt_G_u16[CDD_AppDataFwdPthAccessBfr_Cnt_G_u16]             = (val)

#endif
