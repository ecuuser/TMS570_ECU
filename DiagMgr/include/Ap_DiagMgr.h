 /*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_DiagMgr.h
* Module Description: This file contains diagmgr function prototypes
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Fri Dec  2 07:36:54 2011
* %version:          6.1.1 %
* %derived_by:       kzdyfh %
* %date_modified:    Mon Oct  7 14:45:17 2013 %
*---------------------------------------------------------------------------*/
#ifndef AP_DIAGMGR_H
#define AP_DIAGMGR_H

#include "Std_Types.h" 
#include "Rte_Type.h"
#include "DiagMgr_Cfg.h"
#include "Ap_DiagMgr_Types.h"
#include "Det.h"

/*** Public Part *************************************/

/* Globally Accessible Status Bits */
#define 	D_TESTFAILEDBIT_CNT_B8							0x01U
#define 	D_TESTFAILEDTHISOPCYCLEBIT_CNT_B8				0x02U
#define 	D_PENDINGDTCBIT_CNT_B8							0x04U
#define 	D_CONFIRMEDDTCBIT_CNT_B8						0x08U
#define 	D_TESTNOTCOMPLETESINCELASTCLEARBIT_CNT_B8		0x10U
#define 	D_TESTFAILEDSINCELASTCLEARBIT_CNT_B8			0x20U
#define 	D_TESTNOTCOMPLETETHISOPCYCLEBIT_CNT_B8			0x40U
#define 	D_WARNINGINDICATORBIT_CNT_B8					0x80U

#define 	D_NTCACTIVEBITS_CNT_B8							(D_TESTFAILEDBIT_CNT_B8 | D_TESTFAILEDTHISOPCYCLEBIT_CNT_B8 | D_CONFIRMEDDTCBIT_CNT_B8)
#define		D_MAXLATCHACTIVENTCS_CNT_U08					8U

/* DiagMgr NvM Data */
extern VAR(NTCStrgArray, AP_DIAGMGR_VAR) NTCStrgArray_Cnt_str;
extern VAR(NTCBlkBoxData, AP_DIAGMGR_VAR) NTCBlackBoxData_Cnt_str;
extern VAR(uint16, AP_DIAGMGR_VAR) LatchCounter_Cnt_u16[D_MAXLATCHACTIVENTCS_CNT_U08];

/* DiagMgr SCom Global Functions */
extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_ClearBlackBox(void);
extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_ClearLatchCounters(void);
extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_ResetNTCStatus(void);
extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_ReadStrgArray(void);
extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_GetNTCInfo(	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																		P2VAR(uint8, AUTOMATIC, AUTOMATIC) Param_Ptr_T_u08,
																		P2VAR(uint8, AUTOMATIC, AUTOMATIC) Status_Ptr_T_u08,
																		P2VAR(uint8, AUTOMATIC, AUTOMATIC) AgingCounter_Ptr_T_u08);
extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_Init1(void);

/*** Private Part (DiagMgr Internal) *************************************/
#ifdef DIAGMGR_C

#define 	DiagMgr_ReportDet( errorId )			Det_ReportError( 0u /*ModuleId*/, 0u /*InstanceId*/, 0u /*ApiId*/, errorId )
#define		D_DIAGMGRINVALIDAPPDET_CNT_U08			0x00U

#define 	D_DIAGSTSNONRECRMPTOZEROBIT_CNT_B16		0x0001U
#define 	D_DIAGSTSCTRLDDISRMPBIT_CNT_B16			0x0002U
#define 	D_DIAGSTSRECRMPTOZEROBIT_CNT_B16		0x0004U
#define 	D_DIAGSTSHWASBSYSTMFLTBIT_CNT_B16		0x0008U
#define 	D_DIAGSTSDEFVEHSPDBIT_CNT_B16			0x0010U
#define 	D_DIAGSTSDEFTEMPBIT_CNT_B16				0x0020U
#define 	D_DIAGSTSSCOMHWANOTVALIDBIT_CNT_B16		0x0040U
#define 	D_DIAGSTSWIRDISABLEBIT_CNT_B16			0x0080U

extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_Init_Core(	VAR(NTCInfo_Str, AUTOMATIC) NTCInfo_Cnt_T_str[],
															VAR(uint8, AUTOMATIC) NumElements_Cnt_T_u08,
															VAR(uint8, AUTOMATIC) CurrentAppIdx_Cnt_T_u08,
															P2VAR(boolean, AUTOMATIC, AUTOMATIC) DiagMgrInitComp_Ptr_T_lgc,
															CONST(NTCInfoQueue_Str, AUTOMATIC) NTCInfoQueue_Cnt_T_str[],
															P2CONST(uint8, AUTOMATIC, AUTOMATIC) NTCQueueIndex_Ptr_T_u08,
															VAR(uint16, AUTOMATIC) DiagSts_Cnt_T_b16[],
															VAR(float32, AUTOMATIC) ActiveRmpRate_UlspmS_T_f32[],
															P2CONST(uint8, AUTOMATIC, AUTOMATIC) ActDiagSts_Ptr_T_u08);

extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_Per_Core(	VAR(NTCInfo_Str, AUTOMATIC) NTCInfo_Cnt_T_str[],
															VAR(uint8, AUTOMATIC) NumElements_Cnt_T_u08,
															VAR(uint16, AUTOMATIC) DiagSts_Cnt_T_b16[],
															VAR(float32, AUTOMATIC) ActiveRmpRate_UlspmS_T_f32[],
															P2VAR(uint8, AUTOMATIC, AUTOMATIC) ActDiagStsIdx_Ptr_T_u08,
															CONST(NTCNumber, AUTOMATIC) T_NTCMapTbl_Cnt_enum[],
															P2VAR(uint8, AUTOMATIC, AUTOMATIC) PrevResetNTCFlag_Ptr_T_u08);

extern FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_Trns_Core(	VAR(NTCInfo_Str, AUTOMATIC) NTCInfo_Cnt_T_str[],
														VAR(uint8, AUTOMATIC) NumElements_Cnt_T_u08,
														CONST(NTCNumber, AUTOMATIC) T_NTCMapTbl_Cnt_enum[]);


extern FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr_SetNTCStatus_Core(	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																				VAR(uint8, AUTOMATIC) Param_Cnt_T_u08,
																				VAR(NxtrDiagMgrStatus, AUTOMATIC) Status_Cnt_T_enum,
																				VAR(NTCInfo_Str, AUTOMATIC) NTCInfo_Cnt_T_str[],
																				VAR(uint16, AUTOMATIC) DiagSts_Cnt_T_b16[],
																				VAR(float32, AUTOMATIC) ActiveRmpRate_Cnt_T_f32[],
																				P2CONST(uint8, AUTOMATIC, AUTOMATIC) ActDiagSts_Ptr_T_u08);


extern FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr_GetNTCFailed_Core(	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																						P2VAR(boolean, AUTOMATIC, AUTOMATIC) NTCFailed_Ptr_T_lgc);

extern FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr_GetNTCActive_Core( 	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																						P2VAR(boolean, AUTOMATIC, AUTOMATIC) NTCActive_Ptr_T_lgc );

extern FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr_GetNTCStatus_Core(	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																						P2VAR(UInt8, AUTOMATIC, AUTOMATIC) Status_Ptr_T_u08);

extern FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr_ReportNTCStatus_Core(	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																						VAR(uint8, AUTOMATIC) Param_Cnt_T_u08,
																						VAR(NxtrDiagMgrStatus, AUTOMATIC) Status_Cnt_T_enum,
																						VAR(NTCInfoQueue_Str, AUTOMATIC) NTCInfoQueue_Cnt_T_str[],
																						P2VAR(uint8, AUTOMATIC, AUTOMATIC) NTCQueueIndex_Ptr_T_u08);

extern FUNC(void, AP_DIAGMGR_CODE) UpdateBlkBox(	VAR(uint8, AUTOMATIC) NTC_Cnt_T_u08,
													VAR(uint8, AUTOMATIC) Param_Cnt_T_u08,
													VAR(uint8, AUTOMATIC) BlkBoxGrpIdx_Cnt_T_u08);

extern FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgrDemIf_ReportNTCStatus(	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																						VAR(uint8, AUTOMATIC) Param_Ptr_T_u08,
																						VAR(NxtrDiagMgrStatus, AUTOMATIC) Status_Ptr_T_u08);

extern VAR(boolean, AP_DIAGMGR_VAR) DEMEventActive_Cnt_M_lgc[D_NUMOFDEMEVENTS_CNT_U08+1U];
#else

#endif


#endif


/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
07/20/2012	1	    LWW       Initial Version
09/20/2012	2	    LWW       Initial version with application support
09/23/2012	3	    LWW       Changed DiagMgr_SCom_GetNTCParamByte to DiagMgr_SCom_GetNTCInfo
11/07/2012	4	    JJW       Initial Det error Id and macro support
02/26/2013	6	    LWW       Made DEMEventActive array size explicit
10/04/2013  7       Jared     Updates to support latch active diagnostic
******************************************************************************/
