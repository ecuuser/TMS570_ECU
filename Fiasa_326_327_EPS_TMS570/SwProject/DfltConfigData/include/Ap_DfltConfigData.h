/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_DfltConfigData.h
* Module Description:
* Product           : Gen II Plus - EA3.0
* Author            : Owen Tosh
*****************************************************************************/
/* Version Control:
 * Date Created:      Thu Jun 20 10:00:00 2013
 * %version:          EA3#7 %
 * %derived_by:       nzdx8v %
 * %date_modified:    Tue Sep 24 11:27:18 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date       Rev     Author   Change Description                                                               SCR #
 * --------   ------  -------  ------------------------------------------------------------------------------  -------
 * 07/16/15    2      PS       Added T_SwVer_Cnt_u8 and T_SwDataVer_Cnt_u8 for DID's 0xF181 and 0xF182		  CR#13482
 * 10/30/15    3      PS       Implemented software according to SCIR 4A and DSR 3A						  	  EA3#4252
 * 11/16/15    4      PS       Implemented software according to SCIR 5A and DSR 5A	 						  EA3#4579
 * 12/01/15    5      PS       Implemented software according to SCIR 7A and DSR 6A	 						  EA3#4681, EA3#4686
 * 03/16/16    6      PS       Implemented software according to SCIR 8A and DSR 7A	 						  EA3#6773, EA3#6775
 * 04/01/16    7      PS       Update to DID 0xF181	 						  								  EA3#7178
 */

 
#ifndef RTE_AP_DFLTCONFIGDATA_H
#define RTE_AP_DFLTCONFIGDATA_H


#include "Std_Types.h"
#include "Rte_Type.h"


typedef struct
{
  float32 EOLVehCntrOffset_HwDeg_f32;
  boolean EOLHwPosTrimPerformed_Cnt_lgc;
} Deprecated_EOLHwPosTrimType;

typedef struct
{
  float32 k_EOLHwTrqTrim_HwNm_f32;
  boolean k_EOLHwTrqTrimPerformed_Cnt_Lgc;
} Deprecated_DigHwTrqSENTTrim_DataType;

typedef struct
{
  sint16 CurrTempOffsetX_DegC_s10p5[16];
  sint16 CurrOffsetY1_Volts_s4p11[16];
  sint16 CurrOffsetY2_Volts_s4p11[16];
  uint8 CRC_Cnt_u08[2];
} Deprecated_CurrTempOffsetType;

typedef struct
{
  float32 EOLMtrCurrVcalCmd_VoltCnts_f32;
  float32 EOLMtrCurr1OffsetLo_Volts_f32;
  float32 EOLPhscurr1Gain_AmpspVolt_f32;
  float32 EOLPhscurr2Gain_AmpspVolt_f32;
  float32 EOLMtrCurr2OffsetLo_Volts_f32;
  float32 EOLMtrCurr1OffsetDiff_Volts_f32;
  float32 EOLMtrCurr2OffsetDiff_Volts_f32;
} Deprecated_PhaseCurrCal_DataType;

typedef struct
{
  float32 CWEOTPosition_HwDeg_f32;
  float32 CCWEOTPosition_HwDeg_f32;
  boolean CWEOTFound_Cnt_lgc;
  boolean CCWEOTFound_Cnt_lgc;
} Deprecated_EOTLearned_DataType;

typedef struct
{
  float32 FricOffset_HwNm_f32;
  float32 EOLFric_HwNm_f32;
  boolean EnableFricOffsetOutput_Cnt_lgc;
  boolean EnableFricLearning_Cnt_lgc;
  uint8   OpMode_Cnt_enum;
  uint16  RangeCounter_Cnt_u16[8][3];
  float32 Theta_HwNm_f32[8][4];
  float32 VehLearnedFric_HwNm_f32[4];
} Deprecated_AvgFricLrnType;

typedef struct
{
  float32 EOLVehCntrOffset_HwDeg_f32;
  uint16  EOLHwPosTrimPerformed_Cnt_u16;
} Deprecated_EOLHwPosTrimType1;

typedef uint16 Deprecated_Dem_EventIdType;

typedef struct Deprecated_Dem_NvAdminDataType
{
  uint32 activeVersion;
  uint16 cycleCounter[4];
} Deprecated_Dem_NvAdminDataType;

typedef struct Deprecated_Dem_NvStatusDataType
{
  uint8 eventStatus[62 + 1];
  Deprecated_Dem_EventIdType firstFailedEvent;
  Deprecated_Dem_EventIdType firstConfirmedEvent;
  Deprecated_Dem_EventIdType mostRecentFailedEvent;
  Deprecated_Dem_EventIdType mostRecentConfirmedEvent;
} Deprecated_Dem_NvStatusDataType;

typedef VAR(uint8, TYPEDEF) Deprecated_Dem_NvPrimaryEntryType[2 + 4 + 2 + 1 + (2*15) + 1];


typedef struct
{
	uint8 DiagnosticIdentification_DIDF100_ASCII_u08[7];
	uint8 CalibrationSwIdentification_DIDF181_ASCII_u08[14];
	uint8 CalibrationSwIdentification_DIDF182_ASCII_u08[14];
	uint8 ECUSparePartNoTAS_DIDF187_ASCII_u08[11];
	uint8 ECUSparePartNoTOS_DIDF187_ASCII_u08[11];
	uint8 VehicleManfECUSwNo_DIDF188_ASCII_u08[11];
	uint8 VehicleManfECUHwNo_DIDF191_ASCII_u08[11];
	uint8 SupplierManfECUHwPartNo_DIDF192_ASCII_u08[11];
	uint8 SupplierManfECUHwVerNo_DIDF193_ASCII_u08;
	boolean AbsAngleSensorType_Cnt_lgc;
} CustDIDCals_str;


extern VAR(Deprecated_EOLHwPosTrimType,          AP_DFLTCONFIGDATA_VAR) Deprecated_AbsHwPos_EOLVehCntrOffset;
extern VAR(Deprecated_DigHwTrqSENTTrim_DataType, AP_DFLTCONFIGDATA_VAR) Deprecated_DigHwTrqSENT_DigTrqTrim;
extern VAR(Deprecated_CurrTempOffsetType,        AP_DFLTCONFIGDATA_VAR) Deprecated_CmMtrCurr_CurrTempOffset;
extern VAR(Deprecated_PhaseCurrCal_DataType,     AP_DFLTCONFIGDATA_VAR) Deprecated_CmMtrCurr_ShCurrCal;
extern VAR(uint16,                               AP_DFLTCONFIGDATA_VAR) Deprecated_TrqCanc_CogTrqCal[512];
extern VAR(uint16,                               AP_DFLTCONFIGDATA_VAR) Deprecated_TrqCanc_CogTrqRplComp[9];
extern VAR(boolean,                              AP_DFLTCONFIGDATA_VAR) Deprecated_AstLmt_SteerAsstDefeat[2];
extern VAR(float32,                              AP_DFLTCONFIGDATA_VAR) Deprecated_TrqCmdScl_TorqueCmdSF_Uls_f32;
extern VAR(Deprecated_EOTLearned_DataType,       AP_DFLTCONFIGDATA_VAR) Deprecated_LrnEOT_LearnedEOT;
extern VAR(Deprecated_AvgFricLrnType,            AP_DFLTCONFIGDATA_VAR) Deprecated_AvgFricLrn_AvgFricLrnData;
extern VAR(Deprecated_EOLHwPosTrimType1,         AP_DFLTCONFIGDATA_VAR) Deprecated_AbsHwPos_EOLVehCntrOffset1;
extern VAR(Deprecated_Dem_NvAdminDataType, 		 AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvAdminData;
extern VAR(Deprecated_Dem_NvStatusDataType, 	 AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvEventStatusData;
extern VAR(Deprecated_Dem_NvPrimaryEntryType, 	 AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_1;
extern VAR(Deprecated_Dem_NvPrimaryEntryType, 	 AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_2;
extern VAR(Deprecated_Dem_NvPrimaryEntryType, 	 AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_3;
extern VAR(Deprecated_Dem_NvPrimaryEntryType, 	 AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_4;
extern VAR(Deprecated_Dem_NvPrimaryEntryType, 	 AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_5;
extern VAR(Deprecated_Dem_NvPrimaryEntryType, 	 AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_6;
extern VAR(Deprecated_Dem_NvPrimaryEntryType, 	 AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_7;
extern VAR(Deprecated_Dem_NvPrimaryEntryType, 	 AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_8;
extern VAR(uint8, 								 AP_DFLTCONFIGDATA_VAR) Deprecated_Rte_DiagSvc_ProxiConfigurationData;

extern CONST(PhaseCurrCal_DataType, AP_DFLTCONFIGDATA_CONST) T_ShCurrCalInit_Cnt_str;
extern CONST(uint16,                AP_DFLTCONFIGDATA_CONST) T_CogTrqCalInit_Cnt_u16[512];
extern CONST(uint16,                AP_DFLTCONFIGDATA_CONST) T_CogTrqRplCompInit_Cnt_u16[9];
extern CONST(float32,               AP_DFLTCONFIGDATA_CONST) T_TorqueCmdSFInit_Uls_f32;
extern CONST(EOTLearned_DataType,   AP_DFLTCONFIGDATA_CONST) T_LearnedEOTInit_Cnt_str;
extern CONST(AvgFricLrnType,        AP_DFLTCONFIGDATA_CONST) T_AvgFricLrnDataInit_Cnt_str;

extern CONST(uint8, CDD_PARTNUMBER) k_SWRelNum_Cnt_u8[50];
extern CONST(CustDIDCals_str, CAL_CONST) k_CustDIDCals_Cnt_u08;


extern FUNC(void, CDD_PARTNUMBER_CODE) DfltConfigData_Init1(void);


#endif /* RTE_AP_DFLTCONFIGDATA_H */
