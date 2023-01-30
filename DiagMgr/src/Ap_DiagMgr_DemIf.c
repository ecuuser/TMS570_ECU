/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_DiagMgr_DemIf.c
* Module Description: Portion of Diagnostic Manager that interfaces with DemIf
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue Sep 18 12:08:33 2012
* %version:          5.1.2 %
* %derived_by:       kzdyfh %
* %date_modified:    Fri Feb 28 09:38:34 2014 %
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
#include "fixmath.h"
#include "NvM.h"
#include "Os.h"

/*****************************************************************************
* Embedded Constants and Macros
*****************************************************************************/
#define 	D_EVTNOTPASSBITS_CNT_B8					(D_TESTFAILEDBIT_CNT_B8 | D_TESTNOTCOMPLETETHISOPCYCLEBIT_CNT_B8)
#define 	D_AGINGCOUNTERTHRESH_CNT_U08			0x40U


/*****************************************************************************
* NvM Data Definition
*****************************************************************************/
#define DIAGMGRDEMIF_START_SEC_VAR_16
#include "MemMap.h"	/* PRQA S 5087 */
VAR(uint16, AP_DIAGMGR_VAR) LatchCounter_Cnt_u16[D_MAXLATCHACTIVENTCS_CNT_U08];
#define DIAGMGRDEMIF_STOP_SEC_VAR_16
#include "MemMap.h"	/* PRQA S 5087 */

/*****************************************************************************
* Global Function Prototypes
*****************************************************************************/

/*****************************************************************************
* Local Function Prototypes
*****************************************************************************/
STATIC FUNC(void, AP_DIAGMGR_CODE) CreateStorageArray(	VAR(uint8, AUTOMATIC) AgingCounterIncrement);

/*****************************************************************************
* Global Function Definitions
*****************************************************************************/

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_Init1
 * Description: This function is called once at init to setup the latch counters for the Latch Active NTC.
 * Triggered: 	On Init
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_Init1(void)
{
	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum;
	VAR(uint8, AUTOMATIC) Status_Cnt_T_u08;
	VAR(ManufModeType, AUTOMATIC) MEC_Cnt_T_enum;
	VAR(uint8, AUTOMATIC) FailedLatchFault_Cnt_T_u08 = 0U;
	VAR(uint8, AUTOMATIC) i;
	VAR(uint8, AUTOMATIC) j;

	/* Note: This assumes MEC counter is initialized before calling DiagMgr_Init1 */
	(void)Rte_Read_MEC_Cnt_enum(&MEC_Cnt_T_enum);

	/* Update Latch Fault counters */
	for (i = 0U; i < D_MAXLATCHACTIVENTCS_CNT_U08; i++)
	{
		/* Get status of corresponding NRC */
		NTC_Cnt_T_enum = t_LatchFaults_Cnt_str[i].NTC;

		/* Only set fault when MEC == 0 and ignore non-configured latches */
		if ( (ProductionMode == MEC_Cnt_T_enum) && (0U != NTC_Cnt_T_enum) )
		{
			Status_Cnt_T_u08 = 0U;

			/* Check if NTC is in storage array */
			for (j = 0U; (j < TableSize_m(NTCStrgArray_Cnt_str)) && (Status_Cnt_T_u08 == 0U); j++)
			{
				if (NTCStrgArray_Cnt_str[j].NTC == NTC_Cnt_T_enum)
				{
					Status_Cnt_T_u08 = NTCStrgArray_Cnt_str[j].Status;
				}
			}

			/* If "currently" failed (from previous ignition cycle), or if previously latched */
			if ( (D_NTCACTIVEBITS_CNT_B8 == (Status_Cnt_T_u08 & D_NTCACTIVEBITS_CNT_B8)) ||
				 (DiagFailed_m(LatchCounter_Cnt_u16[i], t_LatchFaults_Cnt_str[i].DiagSettings) == TRUE) )
			{
				LatchCounter_Cnt_u16[i] = DiagPStep_m(LatchCounter_Cnt_u16[i], t_LatchFaults_Cnt_str[i].DiagSettings);

				/* If failed, set latch fault */
				if (DiagFailed_m(LatchCounter_Cnt_u16[i], t_LatchFaults_Cnt_str[i].DiagSettings) == TRUE)
				{
					/* Set corresponding bit in param byte through use of FailedLatchFault_Cnt_T_u08 */
					FailedLatchFault_Cnt_T_u08 |= (uint8)(1U << i);
				}
			}
			else
			{
				/* N Step if not in storage array or not active and not latched */
				LatchCounter_Cnt_u16[i] = DiagNStep_m(LatchCounter_Cnt_u16[i], t_LatchFaults_Cnt_str[i].DiagSettings);
			}
		}
		else
		{
			/* All latch counters shall be deactivated and reset to zero while the MEC != 0 */
			LatchCounter_Cnt_u16[i] = 0U;
		}
	}

	NvM_SetRamBlockStatus(NVM_BLOCK_DIAGMGR_LATCHCNTRS, TRUE);

	/* Set latch fault if requested */
	if (FailedLatchFault_Cnt_T_u08 != 0U)
	{
		(void)NxtrDiagMgrDemIf_ReportNTCStatus(NTC_Num_LatchActive, FailedLatchFault_Cnt_T_u08, NTC_STATUS_FAILED);
	}
	else
	{
		(void)NxtrDiagMgrDemIf_ReportNTCStatus(NTC_Num_LatchActive, 0U, NTC_STATUS_PASSED);
	}
}

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_Trns1
 * Description: This function will call a function restart the DEM and start the DEM operation cycle in the case that
 *              "OFF" state is exited before power is removed from the controller (e.g. Quick Ignition Cycle)
 * Triggered: 	On Exiting "OFF" State
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_Trns1(void)
{
	(void)Rte_Call_DemIf_RestartDem();
	(void)Rte_Call_DemIf_SetOperationCycleState(NxtrDefaultOpCycle, NXTR_CYCLE_STATE_START);
}

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_StaCtrl_Shutdown
 * Description: This function will End the DEM operation cycle, prepare the NTC storage array to be written to NvM,
 * 				and inform NvM stack to write the storage array and black box data during NvM WriteAll processing
 * Triggered: 	Called from StaMd transition function
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_StaCtrl_Shutdown(void)
{
	(void)Rte_Call_DemIf_SetOperationCycleState(NxtrDefaultOpCycle, NXTR_CYCLE_STATE_END);
	(void)Rte_Call_DemIf_DemShutdown();
	CreateStorageArray(1U);
	NvM_SetRamBlockStatus(NVM_BLOCK_DIAGMGR_NTCSTRG, TRUE);
	NvM_SetRamBlockStatus(NVM_BLOCK_DIAGMGR_BLACKBOX, TRUE);
}

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_Per2
 * Description: This function cycle through the DEM Event failed Queue and call the failed event status API, in addition
 *              it will parse through the sorted NTC list to call the passed event status API on any DEM events in which
 *              all corresponding NTCs have passed.
 * Triggered: 	Periodic in all states except "OFF"
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_Per2(void)
{
	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum;
	VAR(uint8, AUTOMATIC) AppIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) InfoIdx_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) SortedNTCIndex_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) CurrentEvtID_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) EvtIDCombinedStatus_Cnt_T_u08;
	VAR(boolean, AUTOMATIC) DEMEventActive_Cnt_T_lgc;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_DiagMgr_Per2_CP0_CheckpointReached();

	for (CurrentEvtID_Cnt_T_u08 = 1U; CurrentEvtID_Cnt_T_u08 <= D_NUMOFDEMEVENTS_CNT_U08; CurrentEvtID_Cnt_T_u08++)
	{
		SuspendAllInterrupts();
		DEMEventActive_Cnt_T_lgc = DEMEventActive_Cnt_M_lgc[CurrentEvtID_Cnt_T_u08];
		DEMEventActive_Cnt_M_lgc[CurrentEvtID_Cnt_T_u08] = FALSE;
		ResumeAllInterrupts();

		if (TRUE == DEMEventActive_Cnt_T_lgc)
		{
			(void)Rte_Call_DemIf_SetEventStatus(CurrentEvtID_Cnt_T_u08, NTC_STATUS_FAILED);
		}
	}

	CurrentEvtID_Cnt_T_u08 = k_FltRspTbl_Cnt_str[t_SortedNTCs_Cnt_enum[0]].DEMEventID;
	SortedNTCIndex_Cnt_T_u08 = 0U;

	while (CurrentEvtID_Cnt_T_u08 != 0U)
	{
		NTC_Cnt_T_enum = t_SortedNTCs_Cnt_enum[SortedNTCIndex_Cnt_T_u08];
		AppIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].AppIdx;
		InfoIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].InfoIdx;
		
		/* DET check for valid configuration (AppIdx of 0xFF indicates the NTC is not supported)*/
		#if(STD_ON == DIAGMGR_DEV_ERROR_DETECT)

		if( AppIdx_Cnt_T_u08 >= DIAGMGR_NUMAPPS )
		{
			DiagMgr_ReportDet( D_DIAGMGRINVALIDAPPDET_CNT_U08 );
		}
		#endif
  
		EvtIDCombinedStatus_Cnt_T_u08 = T_DiagMgrNtcInfoPtr_Cnt_Str[AppIdx_Cnt_T_u08].NTCInfoPtr[InfoIdx_Cnt_T_u08].Status;
		
		SortedNTCIndex_Cnt_T_u08++;
		while (CurrentEvtID_Cnt_T_u08 == k_FltRspTbl_Cnt_str[t_SortedNTCs_Cnt_enum[SortedNTCIndex_Cnt_T_u08]].DEMEventID)
		{
			NTC_Cnt_T_enum = t_SortedNTCs_Cnt_enum[SortedNTCIndex_Cnt_T_u08];
			AppIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].AppIdx;
			InfoIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].InfoIdx;

			/* DET check for valid configuration (AppIdx of 0xFF indicates the NTC is not supported)*/
			#if(STD_ON == DIAGMGR_DEV_ERROR_DETECT)
	
			if( AppIdx_Cnt_T_u08 >= DIAGMGR_NUMAPPS )
			{
				DiagMgr_ReportDet( D_DIAGMGRINVALIDAPPDET_CNT_U08 );
			}
			#endif

			EvtIDCombinedStatus_Cnt_T_u08 |=  T_DiagMgrNtcInfoPtr_Cnt_Str[AppIdx_Cnt_T_u08].NTCInfoPtr[InfoIdx_Cnt_T_u08].Status;

			SortedNTCIndex_Cnt_T_u08++;
		}

		if (0U == (D_EVTNOTPASSBITS_CNT_B8 & EvtIDCombinedStatus_Cnt_T_u08))
		{
			(void)Rte_Call_DemIf_SetEventStatus(CurrentEvtID_Cnt_T_u08, NTC_STATUS_PASSED);
		}

		CurrentEvtID_Cnt_T_u08 = k_FltRspTbl_Cnt_str[t_SortedNTCs_Cnt_enum[SortedNTCIndex_Cnt_T_u08]].DEMEventID;
	}

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_DiagMgr_Per2_CP1_CheckpointReached();
}

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_SCom_GetNTCInfo
 * Description: This function reports out the current parameter byte, status byte, and Aging Counter of a given NTC
 * Triggered: 	Server function (on invocation)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_GetNTCInfo(	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum,
																P2VAR(uint8, AUTOMATIC, AUTOMATIC) Param_Ptr_T_u08,
																P2VAR(uint8, AUTOMATIC, AUTOMATIC) Status_Ptr_T_u08,
																P2VAR(uint8, AUTOMATIC, AUTOMATIC) AgingCounter_Ptr_T_u08)
{
	VAR(uint8, AUTOMATIC) AppIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) InfoIdx_Cnt_T_u08;

	AppIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].AppIdx;
	
	if (AppIdx_Cnt_T_u08 < DIAGMGR_NUMAPPS)
	{
		InfoIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].InfoIdx;
		*Param_Ptr_T_u08 = T_DiagMgrNtcInfoPtr_Cnt_Str[AppIdx_Cnt_T_u08].NTCInfoPtr[InfoIdx_Cnt_T_u08].Param;
		*Status_Ptr_T_u08 = T_DiagMgrNtcInfoPtr_Cnt_Str[AppIdx_Cnt_T_u08].NTCInfoPtr[InfoIdx_Cnt_T_u08].Status;
		*AgingCounter_Ptr_T_u08 = T_DiagMgrNtcInfoPtr_Cnt_Str[AppIdx_Cnt_T_u08].NTCInfoPtr[InfoIdx_Cnt_T_u08].AgingCounter;
	}
	else
	{
		*Param_Ptr_T_u08 = 0U;
		*Status_Ptr_T_u08 = 0U;
		*AgingCounter_Ptr_T_u08 = 0xFFU;
	}
}

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_SCom_ResetNTCStatus
 * Description: This will flag for reseting status bits for all NTCs
 * Triggered: 	Server function (on invocation)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_ResetNTCStatus(void)
{
	ResetNTCFlag_Cnt_M_u08 = ~ResetNTCFlag_Cnt_M_u08;
}

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_SCom_ReadStrgArray
 * Description: This function will populate the NTC storage array (in preparation for a read)
 * Triggered: 	Server function (on invocation)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_ReadStrgArray(void)
{
	CreateStorageArray(0U);
}

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_SCom_ClearBlackBox
 * Description: This function will clear all NTC black box information
 * Triggered: 	Server function (on invocation)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_ClearBlackBox(void)
{
	VAR(uint8, AUTOMATIC) i;

	for (i = 0U; i < TableSize_m(NTCBlackBoxData_Cnt_str); i++)
	{
		NTCBlackBoxData_Cnt_str[i].NTC_Cnt_u08 = 0U;
		NTCBlackBoxData_Cnt_str[i].Param_Cnt_u08 = 0U;
		NTCBlackBoxData_Cnt_str[i].SystemState_Cnt_u08 = 0U;
		NTCBlackBoxData_Cnt_str[i].VehSpd_Kph_u8p0 = 0U;
		NTCBlackBoxData_Cnt_str[i].Param1_Cnt_s16 = 0;
		NTCBlackBoxData_Cnt_str[i].Param2_Cnt_s16 = 0;
		NTCBlackBoxData_Cnt_str[i].IgnCtr_Cnt_u16 = 0U;
		NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData1 = 0U;
		NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData2 = 0U;
		NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData3 = 0U;
	}
}

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_SCom_ClearLatchCounters
 * Description: This function will clear all NTC latch counter information
 * Triggered: 	Server function (on invocation)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_SCom_ClearLatchCounters(void)
{
	VAR(uint8, AUTOMATIC) i;

	for (i = 0U; i < D_MAXLATCHACTIVENTCS_CNT_U08; i++)
	{
		LatchCounter_Cnt_u16[i] = 0U;
	}

	(void)NxtrDiagMgrDemIf_ReportNTCStatus(NTC_Num_LatchActive, 0U, NTC_STATUS_PASSED);
}

/*****************************************************************************
* Local Function Definitions
*****************************************************************************/

/**********************************************************************************************************************
 * Function: 	CreateStorageArray
 * Description: This function will populate the NTC storage array based on the latest status of the NTCs, if required
 *              it will update the aging counter during this process
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC FUNC(void, AP_DIAGMGR_CODE) CreateStorageArray(	VAR(uint8, AUTOMATIC) AgingCounterIncrement)
{
	VAR(uint8, AUTOMATIC) AppIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) InfoIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) Status_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) AgingCounter_Cnt_T_u08;
	VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum;
	VAR(uint8, AUTOMATIC) HistoryIndexCounter;
	VAR(uint8, AUTOMATIC) CurrentFltStrgIndex;
	VAR(uint8, AUTOMATIC) HistoryFltStrgIndex;
	VAR(NTCStrgArray, AUTOMATIC) HistoryFltStrgArray;

	CurrentFltStrgIndex = 0U;
	HistoryFltStrgIndex = 0U;

	for (NTC_Cnt_T_enum = 1U; NTC_Cnt_T_enum < TableSize_m(k_FltRspTbl_Cnt_str); NTC_Cnt_T_enum++)
	{
		AppIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].AppIdx;

		/* Is NTC Applicable based on configuration */
		if (AppIdx_Cnt_T_u08 < DIAGMGR_NUMAPPS)
		{
			InfoIdx_Cnt_T_u08 = T_DiagMgrNtcAppInfoMap_Cnt_Str[NTC_Cnt_T_enum].InfoIdx;

			/* TODO: See if we care about consistancy on these two */
			Status_Cnt_T_u08 = T_DiagMgrNtcInfoPtr_Cnt_Str[AppIdx_Cnt_T_u08].NTCInfoPtr[InfoIdx_Cnt_T_u08].Status;
			AgingCounter_Cnt_T_u08 = T_DiagMgrNtcInfoPtr_Cnt_Str[AppIdx_Cnt_T_u08].NTCInfoPtr[InfoIdx_Cnt_T_u08].AgingCounter;

			/* Is NTC set this ignition cycle? */
			if (	(AgingCounter_Cnt_T_u08 == 0U) &&
					(CurrentFltStrgIndex < TableSize_m(NTCStrgArray_Cnt_str)))
			{
				NTCStrgArray_Cnt_str[CurrentFltStrgIndex].NTC = NTC_Cnt_T_enum;
				NTCStrgArray_Cnt_str[CurrentFltStrgIndex].Status = Status_Cnt_T_u08;
				NTCStrgArray_Cnt_str[CurrentFltStrgIndex].AgingCounter = AgingCounterIncrement;
				CurrentFltStrgIndex++;
			}
			else if (	(((uint16)AgingCounter_Cnt_T_u08 + (uint16)AgingCounterIncrement) <= (uint16)D_AGINGCOUNTERTHRESH_CNT_U08) &&
						(HistoryFltStrgIndex < TableSize_m(HistoryFltStrgArray)))
			{
				HistoryFltStrgArray[HistoryFltStrgIndex].NTC = NTC_Cnt_T_enum;
				HistoryFltStrgArray[HistoryFltStrgIndex].Status = Status_Cnt_T_u08;
				HistoryFltStrgArray[HistoryFltStrgIndex].AgingCounter = AgingCounter_Cnt_T_u08 + AgingCounterIncrement;
				HistoryFltStrgIndex++;
			}
			else
			{
				/* NTC has either aged or wasn't in history, so don't store in storage array */
			}
		}
	}

	HistoryIndexCounter = 0U;

	/* Update Rest of NTCStrgArray_Cnt_str with the History Items or Blank Entries*/
	while (CurrentFltStrgIndex < TableSize_m(NTCStrgArray_Cnt_str))
	{
		if (HistoryIndexCounter < HistoryFltStrgIndex)
		{
			NTCStrgArray_Cnt_str[CurrentFltStrgIndex].NTC = HistoryFltStrgArray[HistoryIndexCounter].NTC;
			NTCStrgArray_Cnt_str[CurrentFltStrgIndex].Status = HistoryFltStrgArray[HistoryIndexCounter].Status;
			NTCStrgArray_Cnt_str[CurrentFltStrgIndex].AgingCounter = HistoryFltStrgArray[HistoryIndexCounter].AgingCounter;
			CurrentFltStrgIndex++;
			HistoryIndexCounter++;
		}
		else
		{
			NTCStrgArray_Cnt_str[CurrentFltStrgIndex].NTC = 0U;
			NTCStrgArray_Cnt_str[CurrentFltStrgIndex].Status = 0U;
			NTCStrgArray_Cnt_str[CurrentFltStrgIndex].AgingCounter = 0U;
			CurrentFltStrgIndex++;
		}
	}
}

/**********************************************************************************************************************
 * Function: 	UpdateBlkBox
 * Description: This function is called when an NTC becomes failed which is configured to log black box data
 * Inputs: 		Rte_Read_IgnCnt_Cnt_u16()
 * 				Rte_Read_MtrTrq_MtrNm_f32()
 * 				Rte_Read_VehSpd_Kph_f32()
 * 				Rte_Read_HwTrq_HwNm_f32()
 * 				Rte_Mode_SystemState_Mode()
 * Outputs: 	None
 **********************************************************************************************************************/
FUNC(void, AP_DIAGMGR_CODE) UpdateBlkBox(	VAR(uint8, AUTOMATIC) NTC_Cnt_T_u08,
											VAR(uint8, AUTOMATIC) Param_Cnt_T_u08,
											VAR(uint8, AUTOMATIC) BlkBoxGrpIdx_Cnt_T_u08)
{
	VAR(uint8, AUTOMATIC) i;
	VAR(uint8, AUTOMATIC) BlkBoxIdx_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) OldestIgnCntr_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) IgnCtr_Cnt_T_u16;
	VAR(float32, AUTOMATIC) Param1_Cnt_T_f32;
	VAR(float32, AUTOMATIC) Param2_Cnt_T_f32;
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(uint8, AUTOMATIC) VehSpd_Kph_T_u8p0;
	VAR(sint16, AUTOMATIC) Param1_Cnt_T_s16;
	VAR(sint16, AUTOMATIC) Param2_Cnt_T_s16;
	VAR(boolean, AUTOMATIC) BlkBoxIdxFound_Cnt_T_lgc;

	(void)Rte_Read_IgnCnt_Cnt_u16(&IgnCtr_Cnt_T_u16);
	(void)Rte_Read_VehSpd_Kph_f32(&VehSpd_Kph_T_f32);
#if (DIAGMGR_IS_MTO_PROGRAM == STD_OFF)
	(void)Rte_Read_HwTrq_HwNm_f32(&Param1_Cnt_T_f32);
	(void)Rte_Read_MtrTrq_MtrNm_f32(&Param2_Cnt_T_f32);
	Param1_Cnt_T_s16 = FPM_FloatToFixed_m(Param1_Cnt_T_f32, s4p11_T);
	Param2_Cnt_T_s16 = FPM_FloatToFixed_m(Param2_Cnt_T_f32, s4p11_T);
#else
	(void)Rte_Read_DiffPres_bar_f32(&Param1_Cnt_T_f32);
	(void)Rte_Read_CoilCurCmd_Amp_f32(&Param2_Cnt_T_f32);
	Param1_Cnt_T_s16 = FPM_FloatToFixed_m(Param1_Cnt_T_f32, s7p8_T);
	Param2_Cnt_T_s16 = FPM_FloatToFixed_m(Param2_Cnt_T_f32, s2p13_T);
#endif

	VehSpd_Kph_T_u8p0 = (uint8)FPM_FloatToFixed_m(Limit_m(VehSpd_Kph_T_f32, 0.0F, 255.0F), u16p0_T);

	i = 0U;
	BlkBoxIdx_Cnt_T_u08 = 0xFFU;
	BlkBoxIdxFound_Cnt_T_lgc = FALSE;
	OldestIgnCntr_Cnt_T_u16 = IgnCtr_Cnt_T_u16;

	while ((i < TableSize_m(NTCBlackBoxData_Cnt_str)) && (BlkBoxIdxFound_Cnt_T_lgc == FALSE))
	{
		if ((NTCBlackBoxData_Cnt_str[i].NTC_Cnt_u08 == NTC_Cnt_T_u08) ||
			(0U == NTCBlackBoxData_Cnt_str[i].NTC_Cnt_u08))
		{
			BlkBoxIdxFound_Cnt_T_lgc = TRUE;
			BlkBoxIdx_Cnt_T_u08 = i;
		}
		else if (NTCBlackBoxData_Cnt_str[i].IgnCtr_Cnt_u16 < OldestIgnCntr_Cnt_T_u16)
		{
			OldestIgnCntr_Cnt_T_u16 = NTCBlackBoxData_Cnt_str[i].IgnCtr_Cnt_u16;
			BlkBoxIdx_Cnt_T_u08 = i;
		}
		else
		{
		}
		i++;
	}

	if (0xFFU != BlkBoxIdx_Cnt_T_u08)
	{
		NTCBlackBoxData_Cnt_str[BlkBoxIdx_Cnt_T_u08].NTC_Cnt_u08 = NTC_Cnt_T_u08;
		NTCBlackBoxData_Cnt_str[BlkBoxIdx_Cnt_T_u08].Param_Cnt_u08 = Param_Cnt_T_u08;
		NTCBlackBoxData_Cnt_str[BlkBoxIdx_Cnt_T_u08].SystemState_Cnt_u08 = Rte_Mode_SystemState_Mode();
		NTCBlackBoxData_Cnt_str[BlkBoxIdx_Cnt_T_u08].VehSpd_Kph_u8p0 = VehSpd_Kph_T_u8p0;
		NTCBlackBoxData_Cnt_str[BlkBoxIdx_Cnt_T_u08].Param1_Cnt_s16 = Param1_Cnt_T_s16;
		NTCBlackBoxData_Cnt_str[BlkBoxIdx_Cnt_T_u08].Param2_Cnt_s16 = Param2_Cnt_T_s16;
		NTCBlackBoxData_Cnt_str[BlkBoxIdx_Cnt_T_u08].IgnCtr_Cnt_u16 = IgnCtr_Cnt_T_u16;
		NTCBlackBoxData_Cnt_str[BlkBoxIdx_Cnt_T_u08].BlkBoxCfgData1 = *(t_BlkBoxGrp_Ptr_u32[BlkBoxGrpIdx_Cnt_T_u08][0]);
		NTCBlackBoxData_Cnt_str[BlkBoxIdx_Cnt_T_u08].BlkBoxCfgData2 = *(t_BlkBoxGrp_Ptr_u32[BlkBoxGrpIdx_Cnt_T_u08][1]);
		NTCBlackBoxData_Cnt_str[BlkBoxIdx_Cnt_T_u08].BlkBoxCfgData3 = *(t_BlkBoxGrp_Ptr_u32[BlkBoxGrpIdx_Cnt_T_u08][2]);
	}
}

/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
09/18/2012	1	    LWW       Initial Version
09/23/2012	2	    LWW       Changed DiagMgr_SCom_GetNTCParamByte to DiagMgr_SCom_GetNTCInfo
10/22/2012	3	    LWW       Removed header with checkpoint generation updates
11/07/2012	4	    JJW       Det for valid app Id detection
							  Stricter check on AppIdx validity to use < DIAGMGR_NUMAPPS
05/30/2013	5	    KJS       Removed Trns2 triggered function on state change with a
						      client/server method and QAC corrections.
10/03/2013  5.1.1   Jared     Added NTC latch functionality
02/28/2014  5.1.2   Jared     Added configurable support for MTO parameters inputs DiffPressure and CoilCurCmd
******************************************************************************/
