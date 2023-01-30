/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_DiagMgr_Core.c
* Module Description: Core Diagnostic Manager Functionality
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue Sep 18 12:08:32 2012
* %version:          4.1.1 %
* %derived_by:       kzdyfh %
* %date_modified:    Mon Oct  7 14:45:19 2013 %
*---------------------------------------------------------------------------*/

#define DIAGMGR_C
#define DIAGMGR_DEMIF_RTEHEADER
/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"
#include "Ap_DiagMgr.h"
#include "CalConstants.h"
#include "GlobalMacro.h"
#include "Os.h"


/*****************************************************************************
* Embedded Constants and Macros
*****************************************************************************/
#define 	D_FLTRSPNTCACTIVEBIT_CNT_B32					0x00800000UL
#define 	D_FLTRSPRECOVERABLEBIT_CNT_B32					0x00400000UL
#define 	D_FLTRSPHWASBSYSTMFLTBIT_CNT_B32				0x00200000UL
#define 	D_FLTRSPDEFVEHSPDBIT_CNT_B32					0x00100000UL
#define 	D_FLTRSPDEFTEMPBIT_CNT_B32						0x00080000UL
#define 	D_FLTRSPSCOMHWANOTVALIDBIT_CNT_B32				0x00040000UL
#define 	D_FLTRSPWIRDISABLEBIT_CNT_B32					0x00008000UL
#define 	D_FLTRSPPWRCYCLTCHBIT_CNT_B32					0x00000010UL
#define 	D_FLTRSPNTCINHIBITNOTOPERATEBIT_CNT_B32			0x00000020UL
#define 	D_FLTRSPNTCINHIBITRUNBIT_CNT_B32			    0x00000040UL
#define 	D_FLTRSPRAMPBITS_CNT_B32						0x0000000FUL
#define 	D_FLTRSPBLKBOXBITS_CNT_B32						0x00003800UL
#define 	D_BLKBOXBITOFFSET_CNT_U08						11U

#define 	D_RAMPNONE_CNT_U8								0x0FU
#define 	D_RAMPF2_CNT_U8									0x0EU
#define 	D_RAMPF1_CNT_U8									0x0DU
#define		D_DIAGRMPRTLOLMT_ULSPMS_F32						0.0001F
#define		D_DIAGRMPRTHILMT_ULSPMS_F32 					0.5F

/*****************************************************************************
* NvM Data Definition
*****************************************************************************/
#define DIAGMGR_START_SEC_VAR_SAVED_ZONEHGS_UNSPECIFIED
#include "MemMap.h"
VAR(NTCStrgArray, AP_DIAGMGR_VAR) NTCStrgArray_Cnt_str;
VAR(NTCBlkBoxData, AP_DIAGMGR_VAR) NTCBlackBoxData_Cnt_str;
#define DIAGMGR_STOP_SEC_VAR_SAVED_ZONEHGS_UNSPECIFIED
#include "MemMap.h"	/* PRQA S 5087 */

/*****************************************************************************
* DiagMgr Internal Data Definition
*****************************************************************************/
#define DIAGMGR_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"	/* PRQA S 5087 */
VAR(boolean, AP_DIAGMGR_VAR) DEMEventActive_Cnt_M_lgc[D_NUMOFDEMEVENTS_CNT_U08+1U];
#define DIAGMGR_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"	/* PRQA S 5087 */

/*****************************************************************************
* Local Function Prototypes
*****************************************************************************/
STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) FailedCheckAndProcessing(	P2CONST(NTCInfo_Str, AUTOMATIC, AUTOMATIC) NTCInfo_Ptr_T_str,
																	P2VAR(uint16, AUTOMATIC, AUTOMATIC) DiagSts_Ptr_T_b16,
																	P2VAR(float32, AUTOMATIC, AUTOMATIC) MaxRampRate_Ptr_T_f32,
																	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum);

STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) ProcessRampResponse(	VAR(uint32, AUTOMATIC) FltRsp_Cnt_T_u32,
																P2VAR(float32, AUTOMATIC, AUTOMATIC) ActiveRmpRate_Ptr_T_f32,
																P2VAR(uint16, AUTOMATIC, AUTOMATIC) DiagSts_Ptr_T_b16);

STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) ProcessDiagSts(	VAR(uint32, AUTOMATIC)FltRsp_Cnt_T_u32,
															P2VAR(uint16, AUTOMATIC, AUTOMATIC) DiagSts_Ptr_T_b16);

STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) SetBits_u8(	CONSTP2VAR(uint8, AUTOMATIC, AP_DIAGMGR_CONST) Data,
														VAR(uint8, AUTOMATIC) BitMask);

STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) ClrBits_u8(	CONSTP2VAR(uint8, AUTOMATIC, AP_DIAGMGR_CONST) Data,
														VAR(uint8, AUTOMATIC) BitMask);

STATIC INLINE FUNC(boolean, AP_DIAGMGR_CODE) ReadBit_u8(	VAR(uint8, AUTOMATIC) Data,
															VAR(uint8, AUTOMATIC) BitMask);

STATIC INLINE FUNC(boolean, AP_DIAGMGR_CODE) ReadBit_u32(	VAR(uint32, AUTOMATIC) Data,
															VAR(uint32, AUTOMATIC) BitMask);

STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) SetBits_u16(	CONSTP2VAR(uint16, AUTOMATIC, AP_DIAGMGR_CONST) Data,
														VAR(uint16, AUTOMATIC) BitMask);

/*****************************************************************************
* DiagMgr Private Function Definitions
*****************************************************************************/

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_Init_Core
 * Description: This function is the stateless initialization function for a DiagMgr Application Component.  It
 * 				performs the following actions:
 * 				1) Initialize NTC status with data stored in NvM storage array if applicable
 * 				2) Start the Nexteer "Operation Cycle" by updating appropriate bits
 * 				3) Mark the application component as being initialized
 * 				4) Process NTC Report Error Queue
 * Triggered: 	Once at Init (Cold Init)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_Init_Core(	VAR(NTCInfo_Str, AUTOMATIC) NTCInfo_Cnt_T_str[],
															VAR(uint8, AUTOMATIC) NumElements_Cnt_T_u08,
															VAR(uint8, AUTOMATIC) CurrentAppIdx_Cnt_T_u08,
															P2VAR(boolean, AUTOMATIC, AUTOMATIC) DiagMgrInitComp_Ptr_T_lgc,
															CONST(NTCInfoQueue_Str, AUTOMATIC) NTCInfoQueue_Cnt_T_str[],
															P2CONST(uint8, AUTOMATIC, AUTOMATIC) NTCQueueIndex_Ptr_T_u08,
															VAR(uint16, AUTOMATIC) DiagSts_Cnt_T_b16[],
															VAR(float32, AUTOMATIC) ActiveRmpRate_UlspmS_T_f32[],
															P2CONST(uint8, AUTOMATIC, AUTOMATIC) ActDiagSts_Ptr_T_u08)
{
	VAR(uint8, AUTOMATIC) StrgIndex_Cnt_T_u08;
	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum;
	VAR(uint8, AUTOMATIC) AppIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) InfoIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) i;

	for (StrgIndex_Cnt_T_u08 = 0U; StrgIndex_Cnt_T_u08 < TableSize_m(NTCStrgArray_Cnt_str); StrgIndex_Cnt_T_u08++)
	{
		NTC_Cnt_T_enum = NTCStrgArray_Cnt_str[StrgIndex_Cnt_T_u08].NTC;
		
		if (NTC_Cnt_T_enum < TableSize_m(T_DiagMgrNtcAppInfoMap_Cnt_Str))
		{
			AppIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].AppIdx;
			/* No DET check is performed here for a valid AppIdx because the input NTC number is provided by NvM and is ignored if out of the valid range
			 * It is a possible scenario to have an NTC number supported by one sw release stored in NvM and not supported by an upgrade.
			 * In this case it is not a development error, but rather data that should simply be discarded/ignored */
			/* Initialize the NTCInfo_Cnt_M_str from the NvM data if the index is in the valid range */
			if (CurrentAppIdx_Cnt_T_u08 == AppIdx_Cnt_T_u08)
			{
				InfoIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].InfoIdx;

				NTCInfo_Cnt_T_str[InfoIdx_Cnt_T_u08].Status = NTCStrgArray_Cnt_str[StrgIndex_Cnt_T_u08].Status;
				NTCInfo_Cnt_T_str[InfoIdx_Cnt_T_u08].AgingCounter = NTCStrgArray_Cnt_str[StrgIndex_Cnt_T_u08].AgingCounter;
			}
		}
	}

	/* Start Operation Cycle */
	for (i = 0U; i < NumElements_Cnt_T_u08; i++)
	{
		ClrBits_u8(&(NTCInfo_Cnt_T_str[i].Status), D_TESTFAILEDTHISOPCYCLEBIT_CNT_B8);
		SetBits_u8(&(NTCInfo_Cnt_T_str[i].Status), D_TESTNOTCOMPLETETHISOPCYCLEBIT_CNT_B8);

		if (0U == NTCInfo_Cnt_T_str[i].AgingCounter)
		{
			NTCInfo_Cnt_T_str[i].AgingCounter = 0xFFU;
		}
	}

	*DiagMgrInitComp_Ptr_T_lgc = TRUE;

	/* Handle BSW Queue */
	if (NTCInfoQueue_Cnt_T_str != NULL_PTR)
	{
		for (i = *NTCQueueIndex_Ptr_T_u08; i > 0U; i--)
		{
			(void)NxtrDiagMgr_SetNTCStatus_Core(	NTCInfoQueue_Cnt_T_str[i-1U].NTC,
													NTCInfoQueue_Cnt_T_str[i-1U].Param,
													NTCInfoQueue_Cnt_T_str[i-1U].Status,
													NTCInfo_Cnt_T_str,
													DiagSts_Cnt_T_b16,
													ActiveRmpRate_UlspmS_T_f32,
													ActDiagSts_Ptr_T_u08);
		}
	}
}

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_Per_Core
 * Description: This function is the stateless periodic function for a DiagMgr Application Component.  It
 * 				performs the following actions:
 * 				1) Checking the Reset NTC flag and resetting all NTC status bits if indicated
 * 				2) Process status bits for recovery of NTC fail actions and ramp rates
 * Triggered: 	Periodic in all states
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_Per_Core(	VAR(NTCInfo_Str, AUTOMATIC) NTCInfo_Cnt_T_str[],
															VAR(uint8, AUTOMATIC) NumElements_Cnt_T_u08,
															VAR(uint16, AUTOMATIC) DiagSts_Cnt_T_b16[],
															VAR(float32, AUTOMATIC) ActiveRmpRate_UlspmS_T_f32[],
															P2VAR(uint8, AUTOMATIC, AUTOMATIC) ActDiagStsIdx_Ptr_T_u08,
															CONST(NTCNumber, AUTOMATIC) T_NTCMapTbl_Cnt_enum[],
															P2VAR(uint8, AUTOMATIC, AUTOMATIC) PrevResetNTCFlag_Ptr_T_u08)
{
	VAR(uint16, AUTOMATIC) TempDiagSts_Cnt_T_b16;
	VAR(float32, AUTOMATIC) MaxRampRate_UlspmS_T_f32;
	VAR(uint8, AUTOMATIC) PrevDiagStsIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) NewDiagStsIdx_Cnt_T_u08;
	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum;
	VAR(uint32, AUTOMATIC) FltRsp_Cnt_T_u32;
	VAR(uint8, AUTOMATIC) i;

	if (*PrevResetNTCFlag_Ptr_T_u08 != ResetNTCFlag_Cnt_M_u08)
	{
		for (i = 0U; i < NumElements_Cnt_T_u08; i++)
		{
			NTC_Cnt_T_enum = T_NTCMapTbl_Cnt_enum[i];
			FltRsp_Cnt_T_u32 = k_FltRspTbl_Cnt_str[NTC_Cnt_T_enum].Response;

			/* Only reset status on faults that aren't active power-cycle latched */
			if ((ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPPWRCYCLTCHBIT_CNT_B32) == FALSE) ||
				(D_NTCACTIVEBITS_CNT_B8 != (NTCInfo_Cnt_T_str[i].Status & D_NTCACTIVEBITS_CNT_B8)))
			{
				NTCInfo_Cnt_T_str[i].Status = D_TESTNOTCOMPLETETHISOPCYCLEBIT_CNT_B8;
				NTCInfo_Cnt_T_str[i].Param = 0U;
				NTCInfo_Cnt_T_str[i].AgingCounter = 0xFFU;
			}
			else
			{
				/* If power-cycle latched fault is active, flag call to DEM Event failed to maintain synch between NTC and DTC status */
				DEMEventActive_Cnt_M_lgc[k_FltRspTbl_Cnt_str[NTC_Cnt_T_enum].DEMEventID] = TRUE;
			}
		}

		*PrevResetNTCFlag_Ptr_T_u08 = ResetNTCFlag_Cnt_M_u08;
	}

	PrevDiagStsIdx_Cnt_T_u08 = *ActDiagStsIdx_Ptr_T_u08;
	NewDiagStsIdx_Cnt_T_u08 = (PrevDiagStsIdx_Cnt_T_u08 & 1U)^1U;

	SuspendAllInterrupts();
	/* Combine PrevDiagStsIdx with NewDiagStsIdx before clearing out NewDiagStsIdx */
	ActiveRmpRate_UlspmS_T_f32[PrevDiagStsIdx_Cnt_T_u08] = Max_m(ActiveRmpRate_UlspmS_T_f32[NewDiagStsIdx_Cnt_T_u08], ActiveRmpRate_UlspmS_T_f32[PrevDiagStsIdx_Cnt_T_u08]);
	DiagSts_Cnt_T_b16[PrevDiagStsIdx_Cnt_T_u08] |= DiagSts_Cnt_T_b16[NewDiagStsIdx_Cnt_T_u08];

	/* Clear Out NewDiagStsIdx */
	ActiveRmpRate_UlspmS_T_f32[NewDiagStsIdx_Cnt_T_u08] = 0.0F;
	DiagSts_Cnt_T_b16[NewDiagStsIdx_Cnt_T_u08] = 0U;

	/* Switch ActiveDigStsIdx to other buffer */
	*ActDiagStsIdx_Ptr_T_u08 = NewDiagStsIdx_Cnt_T_u08;
	ResumeAllInterrupts();

	/* Parse through current status of all faults and get overall DiagSts and RampRate*/
	MaxRampRate_UlspmS_T_f32 = D_DIAGRMPRTLOLMT_ULSPMS_F32;
	TempDiagSts_Cnt_T_b16 = 0U;

	for (i = 0U; i < NumElements_Cnt_T_u08; i++)
	{
		FailedCheckAndProcessing(&NTCInfo_Cnt_T_str[i], &TempDiagSts_Cnt_T_b16, &MaxRampRate_UlspmS_T_f32, T_NTCMapTbl_Cnt_enum[i]);
	}

	/* Overwrite PrevDiagStsIdx with results of parse... if any bits had cleared (or ramp rate slowed), the value from the parse results will reflect that */
	ActiveRmpRate_UlspmS_T_f32[PrevDiagStsIdx_Cnt_T_u08] = MaxRampRate_UlspmS_T_f32;
	DiagSts_Cnt_T_b16[PrevDiagStsIdx_Cnt_T_u08] = TempDiagSts_Cnt_T_b16;
}

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_Trns_Core
 * Description: This function is the stateless transition function for a DiagMgr Application Component.  It
 *              restarts the Nexteer "Operation Cycle" in the case in the case that "OFF" state is exited
 *              before power is removed from the controller (e.g. Quick Ignition Cycle)
 * Triggered: 	On exiting "OFF" State
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_Trns_Core(	VAR(NTCInfo_Str, AUTOMATIC) NTCInfo_Cnt_T_str[],
														VAR(uint8, AUTOMATIC) NumElements_Cnt_T_u08,
														CONST(NTCNumber, AUTOMATIC) T_NTCMapTbl_Cnt_enum[])
{
	VAR(uint8, AUTOMATIC) i;
	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum;
	VAR(uint32, AUTOMATIC) FltRsp_Cnt_T_u32;

	/* Start Operation Cycle */
	for (i = 0U; i < NumElements_Cnt_T_u08; i++)
	{
		NTC_Cnt_T_enum = T_NTCMapTbl_Cnt_enum[i];
		FltRsp_Cnt_T_u32 = k_FltRspTbl_Cnt_str[NTC_Cnt_T_enum].Response;

		/* Only clear bits on faults that aren't power-cycle latched */
		if (ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPPWRCYCLTCHBIT_CNT_B32) == FALSE)
		{
			ClrBits_u8(&(NTCInfo_Cnt_T_str[i].Status), D_TESTFAILEDTHISOPCYCLEBIT_CNT_B8);
			SetBits_u8(&(NTCInfo_Cnt_T_str[i].Status), D_TESTNOTCOMPLETETHISOPCYCLEBIT_CNT_B8);
		}
		else
		{
			/* If power-cycle latched fault is active, flag call to DEM Event failed to maintain synch between NTC and DTC status */
			if (D_NTCACTIVEBITS_CNT_B8 == (NTCInfo_Cnt_T_str[i].Status & D_NTCACTIVEBITS_CNT_B8))
			{
				DEMEventActive_Cnt_M_lgc[k_FltRspTbl_Cnt_str[NTC_Cnt_T_enum].DEMEventID] = TRUE;
			}
		}
	}
}

/**********************************************************************************************************************
 *
 * Function: 	NxtrDiagMgr_GetNTCFailed_Core
 * Description: This function is the stateless server function for a DiagMgr Application Component.  It
 *              reports out the failed bit status of given NTC
 * Triggered: 	Server function (on invocation)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr_GetNTCFailed_Core(	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																	P2VAR(boolean, AUTOMATIC, AUTOMATIC) NTCFailed_Ptr_T_lgc)
{
	VAR(uint8, AUTOMATIC) AppIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) InfoIdx_Cnt_T_u08;

	AppIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].AppIdx;

	/* DET check for valid configuration (AppIdx of 0xFF indicates the NTC is not supported)*/
	#if(STD_ON == DIAGMGR_DEV_ERROR_DETECT)

	if( AppIdx_Cnt_T_u08 >= DIAGMGR_NUMAPPS )
	{
		DiagMgr_ReportDet( D_DIAGMGRINVALIDAPPDET_CNT_U08 );
	}
	#endif

	InfoIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].InfoIdx;

	*NTCFailed_Ptr_T_lgc = ReadBit_u8(T_DiagMgrNtcInfoPtr_Cnt_Str[AppIdx_Cnt_T_u08].NTCInfoPtr[InfoIdx_Cnt_T_u08].Status, D_TESTFAILEDBIT_CNT_B8);
	
	return (E_OK);
}

/**********************************************************************************************************************
 *
 * Function: 	NxtrDiagMgr_GetNTCActive_Core
 * Description: This function is the stateless server function for a DiagMgr Application Component.  It
 *              reports out if the NTC is currently active (Failed bit,Failed This Operation Cycle bit, and Confirmed bit set)
 * Triggered: 	Server function (on invocation)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr_GetNTCActive_Core( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, P2VAR(boolean, AUTOMATIC, AUTOMATIC) NTCActive_Ptr_T_lgc )
{
	VAR(uint8, AUTOMATIC) AppIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) InfoIdx_Cnt_T_u08;

	AppIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].AppIdx;

	/* DET check for valid configuration (AppIdx of 0xFF indicates the NTC is not supported)*/
	#if(STD_ON == DIAGMGR_DEV_ERROR_DETECT)

	if( AppIdx_Cnt_T_u08 >= DIAGMGR_NUMAPPS )
	{
		DiagMgr_ReportDet( D_DIAGMGRINVALIDAPPDET_CNT_U08 );
	}
	#endif
	
	InfoIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].InfoIdx;

	if (D_NTCACTIVEBITS_CNT_B8 == (T_DiagMgrNtcInfoPtr_Cnt_Str[AppIdx_Cnt_T_u08].NTCInfoPtr[InfoIdx_Cnt_T_u08].Status & D_NTCACTIVEBITS_CNT_B8))
	{
		*NTCActive_Ptr_T_lgc = TRUE;
	}
	else
	{
		*NTCActive_Ptr_T_lgc = FALSE;
	}

	return (E_OK);
}

/**********************************************************************************************************************
 *
 * Function: 	NxtrDiagMgr_GetNTCStatus_Core
 * Description: This function is the stateless server function for a DiagMgr Application Component.  It
 *              reports out the status bits for a given NTC
 * Triggered: 	Server function (on invocation)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr_GetNTCStatus_Core(	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																				P2VAR(UInt8, AUTOMATIC, AUTOMATIC) Status_Ptr_T_u08)
{
	VAR(uint8, AUTOMATIC) AppIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) InfoIdx_Cnt_T_u08;

	AppIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].AppIdx;

	/* DET check for valid configuration (AppIdx of 0xFF indicates the NTC is not supported)*/
	#if(STD_ON == DIAGMGR_DEV_ERROR_DETECT)

	if( AppIdx_Cnt_T_u08 >= DIAGMGR_NUMAPPS )
	{
		DiagMgr_ReportDet( D_DIAGMGRINVALIDAPPDET_CNT_U08 );
	}
	#endif

	InfoIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].InfoIdx;

	*Status_Ptr_T_u08 = T_DiagMgrNtcInfoPtr_Cnt_Str[AppIdx_Cnt_T_u08].NTCInfoPtr[InfoIdx_Cnt_T_u08].Status;

	return (E_OK);
}

/**********************************************************************************************************************
 *
 * Function: 	NxtrDiagMgr_SetNTCStatus_Core
 * Description: This function is the stateless server function for a DiagMgr Application Component.  It
 * 				performs the following actions:
 * 				1) Takes Failed Action on NTC
 * 					a) Checks for NTC Inhibit Conditions
 * 					b) Updates NTC Status, Parameter Byte, and resets Aging Counter to 0
 * 					c) Updates Application's DiagStatus and RampRate if applicable
 * 					d) Logs NTC BlackBox data if applicable
 * 					e) Queues DEM Event for failure if one is mapped to the NTC
 * 				2) Takes Passed Action on NTC
 * 					a) Update NTC Status
 * Triggered: 	Server function (on invocation)
 * Inputs: 		Rte_Read_MEC_Cnt_enum()
 * 				Rte_Read_MfgDiagInhibit_Cnt_lgc()
 * 				Rte_Mode_SystemState_Mode()
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr_SetNTCStatus_Core(	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																				VAR(uint8, AUTOMATIC) Param_Cnt_T_u08,
																				VAR(NxtrDiagMgrStatus, AUTOMATIC) Status_Cnt_T_enum,
																				VAR(NTCInfo_Str, AUTOMATIC) NTCInfo_Cnt_T_str[],
																				VAR(uint16, AUTOMATIC) DiagSts_Cnt_T_b16[],
																				VAR(float32, AUTOMATIC) ActiveRmpRate_Cnt_T_f32[],
																				P2CONST(uint8, AUTOMATIC, AUTOMATIC) ActDiagSts_Ptr_T_u08)
{
	VAR(uint32, AUTOMATIC) FltRsp_Cnt_T_u32;
	VAR(uint16, AUTOMATIC) TempDiagSts_Cnt_T_b16;
	VAR(float32, AUTOMATIC) RmpRate_UlspmS_T_f32;
	VAR(uint8, AUTOMATIC) NTCEventId_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) BlkBoxGrp_Cnt_T_u08;
	VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC) SysState_Cnt_T_Enum;
	VAR(boolean, AUTOMATIC) MfgDiagInhibit_Cnt_T_lgc;
	VAR(ManufModeType, AUTOMATIC) MEC_Cnt_T_enum;
	VAR(boolean, AUTOMATIC) FailedThisCycleBitSet_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) RecBitSet_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) InihibitRun_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) InihibitNotOperate_Cnt_T_lgc;
	VAR(Std_ReturnType, AUTOMATIC) RetVal = E_NOT_OK;

	(void)Rte_Read_MEC_Cnt_enum(&MEC_Cnt_T_enum);
	(void)Rte_Read_MfgDiagInhibit_Cnt_lgc(&MfgDiagInhibit_Cnt_T_lgc);
	SysState_Cnt_T_Enum = Rte_Mode_SystemState_Mode();
	FltRsp_Cnt_T_u32 = k_FltRspTbl_Cnt_str[NTC_Cnt_T_enum].Response;
	NTCEventId_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].InfoIdx;

	/* DET check for valid configuration ( Ntc Info pointer looked up must match the configured pointer )*/
	#if(STD_ON == DIAGMGR_DEV_ERROR_DETECT)

	if( NTCInfo_Cnt_T_str !=  (T_DiagMgrNtcInfoPtr_Cnt_Str[T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].AppIdx].NTCInfoPtr))
	{
		DiagMgr_ReportDet( D_DIAGMGRINVALIDAPPDET_CNT_U08 );
	}
	#endif

	if ((ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPNTCACTIVEBIT_CNT_B32) == TRUE) && (SysState_Cnt_T_Enum != RTE_MODE_StaMd_Mode_OFF))
	{
		if (NTC_STATUS_FAILED == Status_Cnt_T_enum)
		{
			InihibitRun_Cnt_T_lgc = ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPNTCINHIBITRUNBIT_CNT_B32);
			InihibitNotOperate_Cnt_T_lgc = ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPNTCINHIBITNOTOPERATEBIT_CNT_B32);

			if (((TRUE == InihibitNotOperate_Cnt_T_lgc) && (MEC_Cnt_T_enum == ManufacturingMode) && (SysState_Cnt_T_Enum != RTE_MODE_StaMd_Mode_OPERATE)) ||
				((TRUE == InihibitRun_Cnt_T_lgc) && (MfgDiagInhibit_Cnt_T_lgc == TRUE) && (MEC_Cnt_T_enum == ManufacturingMode)))
			{
				/* Do Nothing */
			}
			else
			{
				/* Update Fault Parameter Byte */
				NTCInfo_Cnt_T_str[NTCEventId_Cnt_T_u08].Param |= Param_Cnt_T_u08;
				/* Set Aging Counter to 0 */
				NTCInfo_Cnt_T_str[NTCEventId_Cnt_T_u08].AgingCounter = 0U;

				BlkBoxGrp_Cnt_T_u08 = (uint8)((FltRsp_Cnt_T_u32 & D_FLTRSPBLKBOXBITS_CNT_B32) >> (uint32)D_BLKBOXBITOFFSET_CNT_U08);
				if ((0U != BlkBoxGrp_Cnt_T_u08) && (NTC_Cnt_T_enum <= 0xFFU))
				{
					/* Only update blackbox if NTC isn't already in failed state (i.e. blackbox updated on transition from not-failed to failed)  */
					if (FALSE == ReadBit_u8(NTCInfo_Cnt_T_str[NTCEventId_Cnt_T_u08].Status, D_TESTFAILEDBIT_CNT_B8))
					{
						UpdateBlkBox((uint8)NTC_Cnt_T_enum, Param_Cnt_T_u08, BlkBoxGrp_Cnt_T_u08-1U);
					}
				}

				/* Update Status Bits */
				SetBits_u8(&(NTCInfo_Cnt_T_str[NTCEventId_Cnt_T_u08].Status), D_NTCACTIVEBITS_CNT_B8);
				ClrBits_u8(&(NTCInfo_Cnt_T_str[NTCEventId_Cnt_T_u08].Status), D_TESTNOTCOMPLETETHISOPCYCLEBIT_CNT_B8);

				TempDiagSts_Cnt_T_b16 = 0U;
				RmpRate_UlspmS_T_f32 = 0.0F;

				ProcessDiagSts(FltRsp_Cnt_T_u32, &TempDiagSts_Cnt_T_b16);
				ProcessRampResponse(FltRsp_Cnt_T_u32, &RmpRate_UlspmS_T_f32, &TempDiagSts_Cnt_T_b16);


				DEMEventActive_Cnt_M_lgc[k_FltRspTbl_Cnt_str[NTC_Cnt_T_enum].DEMEventID] = TRUE;

				SuspendAllInterrupts();
				if (RmpRate_UlspmS_T_f32 > ActiveRmpRate_Cnt_T_f32[*ActDiagSts_Ptr_T_u08])
				{
					RmpRate_UlspmS_T_f32 = Limit_m(RmpRate_UlspmS_T_f32, D_DIAGRMPRTLOLMT_ULSPMS_F32, D_DIAGRMPRTHILMT_ULSPMS_F32);
					ActiveRmpRate_Cnt_T_f32[*ActDiagSts_Ptr_T_u08] = RmpRate_UlspmS_T_f32;
				}
				DiagSts_Cnt_T_b16[*ActDiagSts_Ptr_T_u08] |= TempDiagSts_Cnt_T_b16;
				ResumeAllInterrupts();
			}

			RetVal = E_OK;
		}
		else
		{
			if (NTC_STATUS_PASSED == Status_Cnt_T_enum)
			{
				ClrBits_u8(&(NTCInfo_Cnt_T_str[NTCEventId_Cnt_T_u08].Status), D_TESTNOTCOMPLETETHISOPCYCLEBIT_CNT_B8);

				RecBitSet_Cnt_T_lgc = ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPRECOVERABLEBIT_CNT_B32);
				FailedThisCycleBitSet_Cnt_T_lgc = ReadBit_u8(NTCInfo_Cnt_T_str[NTCEventId_Cnt_T_u08].Status, D_TESTFAILEDTHISOPCYCLEBIT_CNT_B8);

				/* Update status bits */
				if ((TRUE == RecBitSet_Cnt_T_lgc) ||
					(FALSE == FailedThisCycleBitSet_Cnt_T_lgc))
				{
					ClrBits_u8(&(NTCInfo_Cnt_T_str[NTCEventId_Cnt_T_u08].Status), D_TESTFAILEDBIT_CNT_B8);
				}

				RetVal = E_OK;
			}
		}
	}

	return (RetVal);
}

/**********************************************************************************************************************
 *
 * Function: 	NxtrDiagMgr_ReportNTCStatus_Core
 * Description: This function is the stateless server function for a DiagMgr Application Component.  It
 * 				updates the NTC Fault Queue for NTCs called prior to initialization of the DiagMgr
 * Triggered: 	Server function (on invocation)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr_ReportNTCStatus_Core(	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																					VAR(uint8, AUTOMATIC) Param_Cnt_T_u08,
																					VAR(NxtrDiagMgrStatus, AUTOMATIC) Status_Cnt_T_enum,
																					VAR(NTCInfoQueue_Str, AUTOMATIC) NTCInfoQueue_Cnt_T_str[],
																					P2VAR(uint8, AUTOMATIC, AUTOMATIC) NTCQueueIndex_Ptr_T_u08)
{
	VAR(uint16, AUTOMATIC) ActiveIndex_Cnt_T_u16;
	VAR(boolean, AUTOMATIC) NTCFound_Cnt_T_lgc = FALSE;

	if (0U == *NTCQueueIndex_Ptr_T_u08)
	{
		NTCInfoQueue_Cnt_T_str[*NTCQueueIndex_Ptr_T_u08].NTC = NTC_Cnt_T_enum;
		NTCInfoQueue_Cnt_T_str[*NTCQueueIndex_Ptr_T_u08].Param = Param_Cnt_T_u08;
		NTCInfoQueue_Cnt_T_str[*NTCQueueIndex_Ptr_T_u08].Status = Status_Cnt_T_enum;

		(*NTCQueueIndex_Ptr_T_u08)++;

	}
	else
	{
		for (ActiveIndex_Cnt_T_u16 = 0U; ((ActiveIndex_Cnt_T_u16 < *NTCQueueIndex_Ptr_T_u08) && (FALSE == NTCFound_Cnt_T_lgc)); ActiveIndex_Cnt_T_u16++)
		{
			if (NTCInfoQueue_Cnt_T_str[ActiveIndex_Cnt_T_u16].NTC == NTC_Cnt_T_enum)
			{
				NTCFound_Cnt_T_lgc = TRUE;
				NTCInfoQueue_Cnt_T_str[ActiveIndex_Cnt_T_u16].Param |= Param_Cnt_T_u08;
				NTCInfoQueue_Cnt_T_str[ActiveIndex_Cnt_T_u16].Status = Status_Cnt_T_enum;
			}
		}

		if (FALSE == NTCFound_Cnt_T_lgc)
		{
			NTCInfoQueue_Cnt_T_str[*NTCQueueIndex_Ptr_T_u08].NTC = NTC_Cnt_T_enum;
			NTCInfoQueue_Cnt_T_str[*NTCQueueIndex_Ptr_T_u08].Param = Param_Cnt_T_u08;
			NTCInfoQueue_Cnt_T_str[*NTCQueueIndex_Ptr_T_u08].Status = Status_Cnt_T_enum;

			(*NTCQueueIndex_Ptr_T_u08)++;
		}
	}

	return (E_OK);
}

/*****************************************************************************
* Local Function Definitions
*****************************************************************************/

/**********************************************************************************************************************
 * Function: 	FailedCheckAndProcessing
 * Description: This function will update Ramp Rate and DiagStatus bits based on the fault response of an NTC that is
 *              currently active
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) FailedCheckAndProcessing(	P2CONST(NTCInfo_Str, AUTOMATIC, AUTOMATIC) NTCInfo_Ptr_T_str,
																	P2VAR(uint16, AUTOMATIC, AUTOMATIC) DiagSts_Ptr_T_b16,
																	P2VAR(float32, AUTOMATIC, AUTOMATIC) MaxRampRate_Ptr_T_f32,
																	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum)
{
	VAR(uint32, AUTOMATIC) FltRsp_Cnt_T_u32;
	VAR(float32, AUTOMATIC) RampRate_UlspmS_T_f32;

	if (D_NTCACTIVEBITS_CNT_B8 == (D_NTCACTIVEBITS_CNT_B8 & NTCInfo_Ptr_T_str->Status))
	{
		FltRsp_Cnt_T_u32 = k_FltRspTbl_Cnt_str[NTC_Cnt_T_enum].Response;

		RampRate_UlspmS_T_f32 = D_DIAGRMPRTLOLMT_ULSPMS_F32;
		ProcessRampResponse(FltRsp_Cnt_T_u32, &RampRate_UlspmS_T_f32, DiagSts_Ptr_T_b16);
		*MaxRampRate_Ptr_T_f32 = Max_m(RampRate_UlspmS_T_f32, *MaxRampRate_Ptr_T_f32);
		ProcessDiagSts(	FltRsp_Cnt_T_u32, DiagSts_Ptr_T_b16);
	}
}

/**********************************************************************************************************************
 * Function: 	ProcessRampResponse
 * Description: This function will update Ramp Rate and Ramp Related DiagStatus bits based on passed fault response
 *              currently active
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) ProcessRampResponse(	VAR(uint32, AUTOMATIC) FltRsp_Cnt_T_u32,
																P2VAR(float32, AUTOMATIC, AUTOMATIC) ActiveRmpRate_Ptr_T_f32,
																P2VAR(uint16, AUTOMATIC, AUTOMATIC) DiagSts_Ptr_T_b16)
{
	VAR(uint8, AUTOMATIC) Ramp_Cnt_T_u08;

	Ramp_Cnt_T_u08 = (uint8)(D_FLTRSPRAMPBITS_CNT_B32 & FltRsp_Cnt_T_u32);

	switch(Ramp_Cnt_T_u08)
	{
		case D_RAMPF1_CNT_U8:
			*ActiveRmpRate_Ptr_T_f32 = D_DIAGRMPRTHILMT_ULSPMS_F32;

			if (ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPRECOVERABLEBIT_CNT_B32) == TRUE)
			{
				SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSRECRMPTOZEROBIT_CNT_B16);
			}
			else
			{
				SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSNONRECRMPTOZEROBIT_CNT_B16);
			}
			break;
		case D_RAMPF2_CNT_U8:
			SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSCTRLDDISRMPBIT_CNT_B16);

			if (ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPRECOVERABLEBIT_CNT_B32) == TRUE)
			{
				SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSRECRMPTOZEROBIT_CNT_B16);
			}
			else
			{
				SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSNONRECRMPTOZEROBIT_CNT_B16);
			}
			break;
		case D_RAMPNONE_CNT_U8:
			/* Do Nothing */
			break;
		default:
			*ActiveRmpRate_Ptr_T_f32 = k_FltRmpRate_UlspmS_f32[Ramp_Cnt_T_u08];

			if (ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPRECOVERABLEBIT_CNT_B32) == TRUE)
			{
				SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSRECRMPTOZEROBIT_CNT_B16);
			}
			else
			{
				SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSNONRECRMPTOZEROBIT_CNT_B16);
			}
			break;
	}
}

/**********************************************************************************************************************
 * Function: 	ProcessDiagSts
 * Description: This function will update Non-Ramp Related DiagStatus bits based on passed fault response
 *              currently active
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) ProcessDiagSts(	VAR(uint32, AUTOMATIC)FltRsp_Cnt_T_u32,
															P2VAR(uint16, AUTOMATIC, AUTOMATIC) DiagSts_Ptr_T_b16)
{
	if (ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPDEFVEHSPDBIT_CNT_B32) == TRUE)
	{
		SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSDEFVEHSPDBIT_CNT_B16);
	}
	if (ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPHWASBSYSTMFLTBIT_CNT_B32) == TRUE)
	{
		SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSHWASBSYSTMFLTBIT_CNT_B16);
	}
	if (ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPDEFTEMPBIT_CNT_B32) == TRUE)
	{
		SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSDEFTEMPBIT_CNT_B16);
	}
	if (ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPSCOMHWANOTVALIDBIT_CNT_B32) == TRUE)
	{
		SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSSCOMHWANOTVALIDBIT_CNT_B16);
	}
	if (ReadBit_u32(FltRsp_Cnt_T_u32, D_FLTRSPWIRDISABLEBIT_CNT_B32) == TRUE)
	{
		SetBits_u16(DiagSts_Ptr_T_b16, D_DIAGSTSWIRDISABLEBIT_CNT_B16);
	}
}

/**********************************************************************************************************************
 * Function: 	SetBits_u8
 * Description: This function will set bits based on the passed BitMask for a uint8 datatype
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) SetBits_u8(	CONSTP2VAR(uint8, AUTOMATIC, AP_DIAGMGR_CONST) Data,
														VAR(uint8, AUTOMATIC) BitMask)
{
	*Data |= BitMask;
}

/**********************************************************************************************************************
 * Function: 	ClrBits_u8
 * Description: This function will clear bits based on the passed BitMask for a uint8 datatype
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) ClrBits_u8(	CONSTP2VAR(uint8, AUTOMATIC, AP_DIAGMGR_CONST) Data,
														VAR(uint8, AUTOMATIC) BitMask)
{
	*Data &= (uint8)(~BitMask);
}

/**********************************************************************************************************************
 * Function: 	ReadBit_u8
 * Description: This function will return TRUE if any bits are set based on the passed BitMask for a uint8 datatype
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(boolean, AP_DIAGMGR_CODE) ReadBit_u8(	VAR(uint8, AUTOMATIC) Data,
															VAR(uint8, AUTOMATIC) BitMask)
{
	return (boolean)(((Data & BitMask) == 0U)?FALSE:TRUE);
}

/**********************************************************************************************************************
 * Function: 	SetBits_u16
 * Description: This function will set bits based on the passed BitMask for a uint16 datatype
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(void, AP_DIAGMGR_CODE) SetBits_u16(	CONSTP2VAR(uint16, AUTOMATIC, AP_DIAGMGR_CONST) Data,
														VAR(uint16, AUTOMATIC) BitMask)
{
	*Data |= BitMask;
}

/**********************************************************************************************************************
 * Function: 	ReadBit_u32
 * Description: This function will return TRUE if any bits are set based on the passed BitMask for a uint32 datatype
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(boolean, AP_DIAGMGR_CODE) ReadBit_u32(	VAR(uint32, AUTOMATIC) Data,
															VAR(uint32, AUTOMATIC) BitMask)
{
	return  (boolean)(((Data & BitMask) == 0U)?FALSE:TRUE);
}

/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
09/18/2012	1	    LWW       Initial Version
10/22/2012	2	    LWW       Anomaly 3896 correction
11/07/2012	3	    JJW       Det check for valid Ntc App configuration
04/26/2013	4	    LWW       Anomaly 4137 correction
10/03/2013  5       Jared     Added NvM and moved constant to support addition of latch active diagnostic
******************************************************************************/
