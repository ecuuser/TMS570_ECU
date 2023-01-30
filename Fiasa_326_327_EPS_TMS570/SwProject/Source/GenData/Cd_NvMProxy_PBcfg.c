
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Cd_NvMProxy_PBcfg.h
* Module Description: Configuration of the Cd_NvMProxy BSW
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
 * Version Control:
 * Date Created:      Tue Feb  7 11:23:49 2012
 * %version:          EA3#5 %
 * %derived_by:       nzdx8v %
 * %date_modified:    Thu Jan  9 16:51:14 2014 % 
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 02/07/12   1        JJW       Initial creation
 * 10/17/12   2        JJW       Generated output file
 * 11/20/12   3        JJW       Removed generation of Block status mirror array.  It is defined in the static SWC
 * 05/30/13   4        JJW       Removed unsuported config feature, added multi-block support
 * 11/21/13   5        LWW       Added Redundant and CRC block checking
 */

#include "Std_Types.h"
#define NVMPROXY_C
#include "Cd_NvMProxy_Cfg.h"
#undef NVMPROXY_C


/* Global data buffers to be used in NvM cfg for Read All destinations */
#define NVMPROXY_START_SEC_VAR_NOINIT_8
#include "MemMap.h"


	
#pragma DATA_ALIGN (NvMP_Rte_CmMtrCurr_ShCurrCal, 4U); 
VAR(uint8, AUTOMATIC) NvMP_Rte_CmMtrCurr_ShCurrCal[sizeof(Rte_CmMtrCurr_ShCurrCal)+D_CRC16SIZE_CNT_U16];	
	
#pragma DATA_ALIGN (NvMP_Rte_TrqCmdScl_TorqueCmdSF_Uls_f32, 4U);
VAR(uint8, AUTOMATIC) NvMP_Rte_TrqCmdScl_TorqueCmdSF_Uls_f32[sizeof(Rte_TrqCmdScl_TorqueCmdSF_Uls_f32)+sizeof(Rte_TrqCmdScl_TorqueCmdSF_Uls_f32)];	
	
#pragma DATA_ALIGN (NvMP_Rte_Polarity_Polarity_Cnt_Str, 4U);
VAR(uint8, AUTOMATIC) NvMP_Rte_Polarity_Polarity_Cnt_Str[sizeof(Rte_Polarity_Polarity_Cnt_Str)];	
	
#pragma DATA_ALIGN (NvMP_CloseCheck_Cnt_u32, 4U);
VAR(uint8, AUTOMATIC) NvMP_CloseCheck_Cnt_u32[sizeof(CloseCheck_Cnt_u32)];	
	
	
	
#pragma DATA_ALIGN (NvMP_Rte_TrqCanc_CogTrqCal, 4U); 
VAR(uint8, AUTOMATIC) NvMP_Rte_TrqCanc_CogTrqCal[sizeof(Rte_TrqCanc_CogTrqCal)+D_CRC16SIZE_CNT_U16];	
	
#pragma DATA_ALIGN (NvMP_Rte_CurrParamComp_EOLNomMtrParam, 4U);
VAR(uint8, AUTOMATIC) NvMP_Rte_CurrParamComp_EOLNomMtrParam[sizeof(Rte_CurrParamComp_EOLNomMtrParam)];	
	
#pragma DATA_ALIGN (NvMP_Rte_DigHwTrqSENT_DigTrqTrim, 4U); 
VAR(uint8, AUTOMATIC) NvMP_Rte_DigHwTrqSENT_DigTrqTrim[sizeof(Rte_DigHwTrqSENT_DigTrqTrim)+D_CRC16SIZE_CNT_U16];	
	
#pragma DATA_ALIGN (NvMP_Rte_DigMSB_DigMSBEOLData, 4U);
VAR(uint8, AUTOMATIC) NvMP_Rte_DigMSB_DigMSBEOLData[sizeof(Rte_DigMSB_DigMSBEOLData)];	
	
#pragma DATA_ALIGN (NvMP_Rte_AbsHwPos_EOLVehCntrOffset, 4U); 
VAR(uint8, AUTOMATIC) NvMP_Rte_AbsHwPos_EOLVehCntrOffset[sizeof(Rte_AbsHwPos_EOLVehCntrOffset)+D_CRC16SIZE_CNT_U16];	
	
#pragma DATA_ALIGN (NvMP_Rte_TrqCanc_CogTrqRplComp, 4U); 
VAR(uint8, AUTOMATIC) NvMP_Rte_TrqCanc_CogTrqRplComp[sizeof(Rte_TrqCanc_CogTrqRplComp)+D_CRC16SIZE_CNT_U16];	
	
#pragma DATA_ALIGN (NvMP_Rte_CmMtrCurr_CurrTempOffset, 4U);
VAR(uint8, AUTOMATIC) NvMP_Rte_CmMtrCurr_CurrTempOffset[sizeof(Rte_CmMtrCurr_CurrTempOffset)];	
	
#pragma DATA_ALIGN (NvMP_Rte_AstLmt_SteerAsstDefeat, 4U);
VAR(uint8, AUTOMATIC) NvMP_Rte_AstLmt_SteerAsstDefeat[sizeof(Rte_AstLmt_SteerAsstDefeat)];	
	
#pragma DATA_ALIGN (NvMP_Rte_VehDyn_MotPosReset, 4U);
VAR(uint8, AUTOMATIC) NvMP_Rte_VehDyn_MotPosReset[sizeof(Rte_VehDyn_MotPosReset)];	
	
#pragma DATA_ALIGN (NvMP_Rte_Sa_DigColPs_DigColPsEOL, 4U);
VAR(uint8, AUTOMATIC) NvMP_Rte_Sa_DigColPs_DigColPsEOL[sizeof(Rte_Sa_DigColPs_DigColPsEOL)];	
	
#pragma DATA_ALIGN (NvMP_Rte_BatteryVoltage_OvervoltageData, 4U);
VAR(uint8, AUTOMATIC) NvMP_Rte_BatteryVoltage_OvervoltageData[sizeof(Rte_BatteryVoltage_OvervoltageData)];	

#define NVMPROXY_STOP_SEC_VAR_NOINIT_8
#include "MemMap.h"

/* Block Test and Copy Configuration */
#define NVMPROXY_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(NvMProxyCfg_Type, AUTOMATIC) NvMProxyCfg[ D_NUMPRXYBLOCKS_CNT_U16 ] = {
	{0, NULL_PTR,  NULL_PTR, 0, NVMPROXY_NONE, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR}, /* Multi-block fixed config */
	{Rte_NvmBlock_CmMtrCurr_ShCurrCal, (uint8*)&NvMP_Rte_CmMtrCurr_ShCurrCal,  (uint8*)&Rte_CmMtrCurr_ShCurrCal, sizeof(Rte_CmMtrCurr_ShCurrCal), NVMPROXY_CRC16, NVMPROXY_NTC_07_ROMDEF, T_ShCurrCalInit_Cnt_str, NULL_PTR},
	{Rte_NvmBlock_TrqCmdScl_TorqueCmdSF_Uls_f32, (uint8*)&NvMP_Rte_TrqCmdScl_TorqueCmdSF_Uls_f32,  (uint8*)&Rte_TrqCmdScl_TorqueCmdSF_Uls_f32, sizeof(Rte_TrqCmdScl_TorqueCmdSF_Uls_f32), NVMPROXY_REDUNDANT, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR},
	{Rte_NvmBlock_Polarity_Polarity_Cnt_Str, (uint8*)&NvMP_Rte_Polarity_Polarity_Cnt_Str,  (uint8*)&Rte_Polarity_Polarity_Cnt_Str, sizeof(Rte_Polarity_Polarity_Cnt_Str), NVMPROXY_NONE, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR},
	{Rte_NvmBlock_StaMd_CloseCheckData, (uint8*)&NvMP_CloseCheck_Cnt_u32,  (uint8*)&CloseCheck_Cnt_u32, sizeof(CloseCheck_Cnt_u32), NVMPROXY_NONE, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR},
	{Rte_NvmBlock_StaMd_TypeHRamBuffer, (uint8*)&TypeHData_Cnt_u08,  (uint8*)&TypeHData_Cnt_u08, sizeof(TypeHData_Cnt_u08), NVMPROXY_NONE, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR},
	{Rte_NvmBlock_TrqCanc_CogTrqCal, (uint8*)&NvMP_Rte_TrqCanc_CogTrqCal,  (uint8*)&Rte_TrqCanc_CogTrqCal, sizeof(Rte_TrqCanc_CogTrqCal), NVMPROXY_CRC16, NVMPROXY_NTC_07_ROMDEF, T_CogTrqCalInit_Cnt_u16, NULL_PTR},
	{Rte_NvmBlock_CurrParamComp_EOLNomMtrParam, (uint8*)&NvMP_Rte_CurrParamComp_EOLNomMtrParam,  (uint8*)&Rte_CurrParamComp_EOLNomMtrParam, sizeof(Rte_CurrParamComp_EOLNomMtrParam), NVMPROXY_NONE, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR},
	{Rte_NvmBlock_DigHwTrqSENT_DigTrqTrim, (uint8*)&NvMP_Rte_DigHwTrqSENT_DigTrqTrim,  (uint8*)&Rte_DigHwTrqSENT_DigTrqTrim, sizeof(Rte_DigHwTrqSENT_DigTrqTrim), NVMPROXY_CRC16, NVMPROXY_NTC_0A, NULL_PTR, NULL_PTR},
	{Rte_NvmBlock_DigMSB_DigMSBEOLData, (uint8*)&NvMP_Rte_DigMSB_DigMSBEOLData,  (uint8*)&Rte_DigMSB_DigMSBEOLData, sizeof(Rte_DigMSB_DigMSBEOLData), NVMPROXY_NONE, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR},
	{Rte_NvmBlock_AbsHwPos_EOLVehCntrOffset, (uint8*)&NvMP_Rte_AbsHwPos_EOLVehCntrOffset,  (uint8*)&Rte_AbsHwPos_EOLVehCntrOffset, sizeof(Rte_AbsHwPos_EOLVehCntrOffset), NVMPROXY_CRC16, NVMPROXY_NTC_08_ROMDEF, T_EOLVehCntrOffsetInit_Cnt_str, NULL_PTR},
	{Rte_NvmBlock_TrqCanc_CogTrqRplComp, (uint8*)&NvMP_Rte_TrqCanc_CogTrqRplComp,  (uint8*)&Rte_TrqCanc_CogTrqRplComp, sizeof(Rte_TrqCanc_CogTrqRplComp), NVMPROXY_CRC16, NVMPROXY_NTC_07_ROMDEF, T_CogTrqRplCompInit_Cnt_u16, NULL_PTR},
	{Rte_NvmBlock_CmMtrCurr_CurrTempOffset, (uint8*)&NvMP_Rte_CmMtrCurr_CurrTempOffset,  (uint8*)&Rte_CmMtrCurr_CurrTempOffset, sizeof(Rte_CmMtrCurr_CurrTempOffset), NVMPROXY_ZERODATA, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR},
	{Rte_NvmBlock_AstLmt_SteerAsstDefeat, (uint8*)&NvMP_Rte_AstLmt_SteerAsstDefeat,  (uint8*)&Rte_AstLmt_SteerAsstDefeat, sizeof(Rte_AstLmt_SteerAsstDefeat), NVMPROXY_ZERODATA, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR},
	{Rte_NvmBlock_VehDyn_MotPosReset, (uint8*)&NvMP_Rte_VehDyn_MotPosReset,  (uint8*)&Rte_VehDyn_MotPosReset, sizeof(Rte_VehDyn_MotPosReset), NVMPROXY_NONE, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR},
	{Rte_NvmBlock_Sa_DigColPs_DigColPsEOL, (uint8*)&NvMP_Rte_Sa_DigColPs_DigColPsEOL,  (uint8*)&Rte_Sa_DigColPs_DigColPsEOL, sizeof(Rte_Sa_DigColPs_DigColPsEOL), NVMPROXY_NONE, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR},
	{Rte_NvmBlock_BatteryVoltage_OvervoltageData, (uint8*)&NvMP_Rte_BatteryVoltage_OvervoltageData,  (uint8*)&Rte_BatteryVoltage_OvervoltageData, sizeof(Rte_BatteryVoltage_OvervoltageData), NVMPROXY_NONE, NVMPROXY_NOTAPPLICABLE, NULL_PTR, NULL_PTR},
};
#define NVMPROXY_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


