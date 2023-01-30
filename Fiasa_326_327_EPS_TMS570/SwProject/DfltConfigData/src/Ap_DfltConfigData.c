/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_DfltConfigData.c
* Module Description:
* Product           : Gen II Plus - EA3.0
* Author            : Owen Tosh
*****************************************************************************/
/* Version Control:
 * %version:          EA3#24 %
 * %derived_by:       mzjphh %
 *---------------------------------------------------------------------------------------------------------------------
 * Date       Rev     Author   Change Description                                                               SCR #
 * --------   ------  -------  ------------------------------------------------------------------------------  -------
 * 02/10/15	  1		  SAH		Initial Fiasa software based on Haitec(only message map changes).
 * 02/27/15	  2		  SAH		Initial Fiasa software for Archer micro(still based on Haitec.
 * 03/12/15	  3		  SAH		Updated software release number to 01.00.02
 * 05/26/15	  4		  SAH		Updated software release number to 01.01.00
 * 07/16/15   5       PS        Updated software release to 02.00.00  										  CR#13482
 * 07/30/15   6       PS        Fix CmdIgnSts_Cnt_M_u16, CmdIgnFailSts_Cnt_M_u16
								and OperationalModeSts variables   								   	       	  EA3#2103, EA3#2105
 * 08/28/15   7       PS        Update customer service $0200 												  EA3#2837, EA3#2838, EA3#2839
								and fix Anomaly's EA3#2099, EA3#2328, EA3#2405, EA3#2407   					  EA3#2840, EA3#2841
 * 09/03/15   8       PS        Fix Anomaly EA3#2960												          EA3#2977
 * 10/15/15   9       PS        Implemented software according to SCIR 3A and DSR 2A						  EA3#3742
 * 10/30/15   9       PS        Implemented software according to SCIR 4A and DSR 3A						  EA3#4252
 * 11/16/15   10      PS        Implemented software according to SCIR 5A and DSR 5A	 					  EA3#4579
 * 12/01/15   13      PS        Implemented software according to SCIR 5A and DSR 6A	 					  EA3#4681, EA3#4686
 * 12/01/15   14      PS        Update to DID F188										 					  EA3#5037
 * 01/05/16   15      OT        Updated software release number and block version check	 					  EA3#5438
 * 01/07/16   16      OT        Updated software release number and block version check	 					  EA3#5488
 * 01/16/16   17      PS        Updated software release number and block version check	 					  EA3#5625
 * 01/22/16   18      PS        Updated software release number and block version check	 					  EA3#5768
 * 03/16/16   19      PS        Updated software release number and block version check	 					  EA3#6773, EA3#6775
 * 03/16/16   20      PS        Updated DID 0xF181 					  										  EA3#7178
 * 06/21/16   21      PS        Updated state transiitions in cdd file to fix Anomaly EA3#9073 				  EA3#9090
 * 08/01/16   22      PS        Updated RID 0x0200 to fix anomaly EA3#9955					 				  EA3#9969
 * 08/01/16   23      PS        Updated response code of RID 0x0200 (Request results) 	 				 	  EA3#9996
 * 10/14/16   24      NS        Updated release numbers and incrememnted boot compatibility number            EA3#11533
 * 11/03/16   25      NS        Updated release number for FlsTest fix										  EA3#12174
 * 03/06/17	  26      NS        Updated release number for F187 write addition								  EA3#14544
 */

#include "Ap_DfltConfigData.h"
#include "EPS_DiagSrvcs_SrvcLUTbl.h"


/* Select the release suffix based on the build type*/
#if	defined(ENABLE_UTILIZATION_MONITOR)
	#define D_SUFFIX    "_U"
#elif defined(ENABLE_CPUUSE_METRICS)
	#define D_SUFFIX    "_T"
#elif defined(ENABLE_METRICS)
	#define D_SUFFIX    "_O"
#elif defined(SWEEPBUILD)
	#define D_SUFFIX    "_SWP1"
#else
	#define D_SUFFIX
#endif


#define D_BLOCKVERSIONCHECK_CNT_U16		17u
#define D_BOOTCOMPATIBILITY_CNT_U16		0x03u

#define T_PRESENCEPATTERN_CNT_U08		{ 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, \
										  0x5A,0xF0,0xA5,0x0F,0x11,0x22,0x33,0x44, \
										  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF }

#define T_STARTTAG_CNT_U08				{ 0x74,0xEB,0xE6,0x12 }


/* Current Sw Release Number (from CM Synergy) - multiple strings are combined at compile time */
#pragma DATA_SECTION(k_SWRelNum_Cnt_u8,".SWRelNum");
CONST(uint8, AP_DFLTCONFIGDATA_CONST) k_SWRelNum_Cnt_u8[] = "Fiasa_05.01.00" D_SUFFIX;

/* Customer DID calibrations */
#pragma DATA_SECTION(k_CustDIDCals_Cnt_u08, ".CustDIDCals");
CONST(CustDIDCals_str, CAL_CONST) k_CustDIDCals_Cnt_u08 = {
		/* 0xF100 - Diagnostic Identification */
		{0xFFU, 0x00U, 0x00U, 0x00U, 0x02U, 0x00U, 0xD2U},

		/* DID 0xF181 - Application Software Identification */
		/* Number of modules 	Year 	Week 	Patch 			Software Identification */
		{		0x01U, 			17U, 	10U, 	0U, 	'F', 'i', 'a', 's', 'a', '0', '5', '.', '0', '1'},

		/* 0xF182 - Application Software Data Identification */
		/* Number of modules 	Year 	Week 	Patch 			Software Identification */
		{		0x01U, 			17U, 	10U, 	0U, 	'F', 'i', 'a', 's', 'a', '5', '.', '1', '.', '0'},

		/* 0xF187 - ECU Spare Part Number - TAS */
		{'5', '2', '0', '3', '3', '7', '8', '7', ' ', ' ', ' '},

		/* 0xF187 - ECU Spare Part Number - TOS */
		{'5', '2', '0', '3', '3', '7', '8', '6', ' ', ' ', ' '},

		/* 0xF188 - Vehicle Manufacturer ECU Software Number */
		{'F', 'i', 'a', 's', 'a', ' ', '5', ' ', '1', ' ', '0'},

		/* 0xF191 - Vehicle Manufacturer ECU Hardware Number */
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},

		/* 0xF192 - Supplier Manufacturer ECU Hardware Part Number */
		{'3', '8', '0', '0', '8', '2', '7', '5', '0', '0', '0'},

		/* 0xF192 - Supplier Manufacturer ECU Hardware Version NUmber */
		'3',

		/* Angle Sensor Type - TRUE (TAS), FALSE (TOS) */
		TRUE
};

/* Set up headers for logical blocks */
#pragma DATA_SECTION(T_AppPresencePattern_Cnt_u08,".AppPresencePattern");
CONST(uint8,  AP_DFLTCONFIGDATA_CONST) T_AppPresencePattern_Cnt_u08[24] = T_PRESENCEPATTERN_CNT_U08;
#pragma DATA_SECTION(T_AppBlockVersionCheck_Cnt_u16,".AppBlockVersionCheck");
CONST(uint16, AP_DFLTCONFIGDATA_CONST) T_AppBlockVersionCheck_Cnt_u16 = D_BLOCKVERSIONCHECK_CNT_U16;
#pragma DATA_SECTION(T_CalPresencePattern_Cnt_u08,".CalPresencePattern");
CONST(uint8,  AP_DFLTCONFIGDATA_CONST) T_CalPresencePattern_Cnt_u08[24] = T_PRESENCEPATTERN_CNT_U08;
#pragma DATA_SECTION(T_CalBlockVersionCheck_Cnt_u16,".CalBlockVersionCheck");
CONST(uint16, AP_DFLTCONFIGDATA_CONST) T_CalBlockVersionCheck_Cnt_u16 = D_BLOCKVERSIONCHECK_CNT_U16;


/* Set up boot validity table for dynamic block mapping */

typedef struct
{
	uint8	StartTag_Cnt_u08[4];
	uint16	BlockCount_Cnt_u16;
	uint16	BootCompatibility_Cnt_u16;
	uint32	AppBlockInfo_Cnt_u32[2];
	uint32	CalBlockInfo_Cnt_u32[2];
} BootValTableType;

#pragma DATA_SECTION(T_BootValidityTable_Cnt_str,".bootvaltable");
CONST(BootValTableType, AP_DFLTCONFIGDATA_CONST) T_BootValidityTable_Cnt_str = {
													T_STARTTAG_CNT_U08,
													2u,
													D_BOOTCOMPATIBILITY_CNT_U16,
													{(uint32)&Lnk_AppBlock_Start, (uint32)&Lnk_AppBlock_Length},
													{(uint32)&Lnk_CalBlock_Start, (uint32)&Lnk_CalBlock_Length} };

#pragma DATA_SECTION(T_BootValidityCRC_Cnt_u16,".bootvalcrc");
CONST(uint16, AP_DFLTCONFIGDATA_CONST) T_BootValidityCRC_Cnt_u16 = 0u;


/* Dummy TypeH variables to remove compiler warnings */
#pragma DATA_SECTION(TypeHDummyAp0_Cnt_G_u08, ".ossDataAp_0:noinit:typeH")
VAR(uint8, AP_DFLTCONFIGDATA_VAR) TypeHDummyAp0_Cnt_G_u08;
#pragma DATA_SECTION(TypeHDummyAp8_Cnt_G_u08, ".ossDataAp_8:noinit:typeH")
VAR(uint8, AP_DFLTCONFIGDATA_VAR) TypeHDummyAp8_Cnt_G_u08;
#pragma DATA_SECTION(TypeHDummyAp9_Cnt_G_u08, ".ossDataAp_9:noinit:typeH")
VAR(uint8, AP_DFLTCONFIGDATA_VAR) TypeHDummyAp9_Cnt_G_u08;
#pragma DATA_SECTION(TypeHDummyAp10_Cnt_G_u08, ".ossDataAp_10:noinit:typeH")
VAR(uint8, AP_DFLTCONFIGDATA_VAR) TypeHDummyAp10_Cnt_G_u08;


/* Initialized locally */

static CONST(uint8, AP_DFLTCONFIGDATA_CONST) T_InitNMEC_Cnt_u8 = 0xFEu;

static CONST(uint8, AP_DFLTCONFIGDATA_CONST) T_InitSystemPolarity_Cnt_b08[2] = { 0x30u, 0x00u };


/* Initialized in driver */

CONST(PhaseCurrCal_DataType, AP_DFLTCONFIGDATA_CONST) T_ShCurrCalInit_Cnt_str =
					{ 53200.0f, 2.5f, 100.0f, 100.0f, 2.5f, 0.0f, 0.0f };

CONST(uint16, AP_DFLTCONFIGDATA_CONST) T_CogTrqCalInit_Cnt_u16[512] =
					  { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

CONST(uint16, AP_DFLTCONFIGDATA_CONST) T_CogTrqRplCompInit_Cnt_u16[9] =
					  { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

CONST(float32, AP_DFLTCONFIGDATA_CONST) T_TorqueCmdSFInit_Uls_f32 = 1.0f;

CONST(EOTLearned_DataType, AP_DFLTCONFIGDATA_CONST) T_LearnedEOTInit_Cnt_str =
					  { 0.0f, 0.0f, FALSE, FALSE };

CONST(AvgFricLrnType, AP_DFLTCONFIGDATA_CONST) T_AvgFricLrnDataInit_Cnt_str =
					  { 0.0f,
						0.0f,
						FALSE,
						TRUE,
						1u,
						{ {0u, 0u, 0u}, {0u, 0u, 0u}, {0u, 0u, 0u}, {0u, 0u, 0u},
						  {0u, 0u, 0u}, {0u, 0u, 0u}, {0u, 0u, 0u}, {0u, 0u, 0u} },
						{ {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},
						  {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},
						  {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},
						  {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f} },
						{0.0f, 0.0f, 0.0f, 0.0f} };

CONST(EOLHwPosTrimType, AP_DFLTCONFIGDATA_CONST) T_EOLVehCntrOffsetInit_Cnt_str =
					  { 20000.0f, 0u };


/* Rte-defined per instance memory buffers */
extern VAR(uint8, RTE_VAR_DEFAULT_RTE_PIM_GROUP) NvMP_Rte_TrqCmdScl_TorqueCmdSF_Uls_f32[4];
extern VAR(uint8, RTE_VAR_DEFAULT_RTE_PIM_GROUP) NvMP_Rte_Polarity_Polarity_Cnt_Str[2];


/* Deprecated NvM Blocks */
#define DFLTCONFIGDATA_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
VAR(Deprecated_EOLHwPosTrimType,          AP_DFLTCONFIGDATA_VAR) Deprecated_AbsHwPos_EOLVehCntrOffset;
VAR(Deprecated_DigHwTrqSENTTrim_DataType, AP_DFLTCONFIGDATA_VAR) Deprecated_DigHwTrqSENT_DigTrqTrim;
VAR(Deprecated_CurrTempOffsetType,        AP_DFLTCONFIGDATA_VAR) Deprecated_CmMtrCurr_CurrTempOffset;
VAR(Deprecated_PhaseCurrCal_DataType,     AP_DFLTCONFIGDATA_VAR) Deprecated_CmMtrCurr_ShCurrCal;
VAR(uint16,                               AP_DFLTCONFIGDATA_VAR) Deprecated_TrqCanc_CogTrqCal[512];
VAR(uint16,                               AP_DFLTCONFIGDATA_VAR) Deprecated_TrqCanc_CogTrqRplComp[9];
VAR(boolean,                              AP_DFLTCONFIGDATA_VAR) Deprecated_AstLmt_SteerAsstDefeat[2];
VAR(float32,                              AP_DFLTCONFIGDATA_VAR) Deprecated_TrqCmdScl_TorqueCmdSF_Uls_f32;
VAR(Deprecated_EOTLearned_DataType,       AP_DFLTCONFIGDATA_VAR) Deprecated_LrnEOT_LearnedEOT;
VAR(Deprecated_AvgFricLrnType,            AP_DFLTCONFIGDATA_VAR) Deprecated_AvgFricLrn_AvgFricLrnData;
VAR(Deprecated_EOLHwPosTrimType1,         AP_DFLTCONFIGDATA_VAR) Deprecated_AbsHwPos_EOLVehCntrOffset1;
VAR(Deprecated_Dem_NvAdminDataType, 	  AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvAdminData;
VAR(Deprecated_Dem_NvStatusDataType, 	  AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvEventStatusData;
VAR(Deprecated_Dem_NvPrimaryEntryType,    AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_1;
VAR(Deprecated_Dem_NvPrimaryEntryType, 	  AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_2;
VAR(Deprecated_Dem_NvPrimaryEntryType, 	  AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_3;
VAR(Deprecated_Dem_NvPrimaryEntryType, 	  AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_4;
VAR(Deprecated_Dem_NvPrimaryEntryType, 	  AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_5;
VAR(Deprecated_Dem_NvPrimaryEntryType, 	  AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_6;
VAR(Deprecated_Dem_NvPrimaryEntryType, 	  AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_7;
VAR(Deprecated_Dem_NvPrimaryEntryType, 	  AP_DFLTCONFIGDATA_VAR) Deprecated_Dem_Cfg_NvPrimaryEntry_8;
VAR(uint8, 								  AP_DFLTCONFIGDATA_VAR) Deprecated_Rte_DiagSvc_ProxiConfigurationData;
#define DFLTCONFIGDATA_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


/* Processing Functions */
FUNC(void, CDD_PARTNUMBER_CODE) DfltConfigData_Init1(void)
{
	VAR(NvM_RequestResultType, AUTOMATIC) BlockStatus = 0;
	VAR(ManufModeType, AUTOMATIC) NxtrMEC_Uls_T_enum;
	
	/* Nexteer MEC */
	NvM_GetErrorStatus(NVM_BLOCK_CMS_NXTRMEC, &BlockStatus);
	if (BlockStatus != NVM_REQ_OK)
	{
		Nvm_NMEC_Cnt_u8 = T_InitNMEC_Cnt_u8;
	}
	
	if( Nvm_NMEC_Cnt_u8 == 0u )
	{
		CDD_EOLSrlComSvcDft_Cnt_G_b32 = 0ul;
	}
	
	EPS_DiagSrvcs_Init();
	
	/* Read MEC */
	NxtrMEC_Uls_T_enum = NxtrMEC_Uls_G_enum;
	
	/* The following section are block checks that require the MEC to be set in Manufacturing Mode */
	if (NxtrMEC_Uls_T_enum == ManufacturingMode )
	{
		
		/* EOL Polarity */
		NvM_GetErrorStatus(Rte_NvmBlock_Polarity_Polarity_Cnt_Str, &BlockStatus);
		if (BlockStatus != NVM_REQ_OK)
		{
			NvMP_Rte_Polarity_Polarity_Cnt_Str[0] = T_InitSystemPolarity_Cnt_b08[0];
			NvMP_Rte_Polarity_Polarity_Cnt_Str[1] = T_InitSystemPolarity_Cnt_b08[1];
			NvM_SetRamBlockStatus(Rte_NvmBlock_Polarity_Polarity_Cnt_Str, TRUE);
		}
		
	}
	
}


