/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_StaMd.c
* Module Description: Core States and Modes Module
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          25 %
 * %derived_by:       wz7x3j %
 * %date_modified:    Tue Oct 28 22:59:07 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 04/13/11  1        LWW       Initial K2xx Synergy Version
 * 04/14/11  2        LWW       Updates for states and modes design changes
 * 12/16/11  3        LWW       TypeH Handling, moved RequestRun out of init and changed triggering
 * 01/06/12  4        M. Story  Added Rte_IRead_StaMd_Per1_RampStatusCmp_Cnt_lgc for operate transition.
 * 01/20/12  5		  KJS		Added CtrldDmpStsCmp_Cnt_T_lgc for F2 fault anomaly
 * 03/19/12  6        VK        Updates to meet FDD 10C v006													5081
 * 04/09/12  7        VK        Updates to fix anomaly 3143														5197
 * 04/23/12  8        LWW       Updated Dem header to non program specific header
 * 04/26/12  9        LWW       Added EcuReset functionality
 * 05/07/12  10       NRAR      ANOM 3158 fix for LookUpTable OFF trans vector elements 
 * 05/27/12  11       OT        Added EEPROM Failure to Close check                                             5897
 * 07/30/12  12       LWW       Changes to querey CloseCheck block status instead of multiblock status for diagnostic
 * 09/21/12  13       LWW       Added checkpoints, new MemMap, and removed OperationCycle API
 * 10/16/12  14       LWW       Design changes for application splits, added SysC fault
 * 10/24/12  15       LWW       Moved SetNTCStatus call outside of SystemStateCheck function, moved call of
 *                              SystemStateCheck if in core application.
 * 10/27/12  16       LWW       Update to Trns1 for DemIf and Application split
 * 05/30/13  17		  KJS		Removed DemIf_Shutdown() call and replaced it with Rte_Call_DiagMgr_StaCtrl_Shutdown
 *								or activate task depending on configuration.
 * 06/06/13  19		  KJS		Applied corrections for A5108. 
 * 06/27/13  20		  LWW		Applied corrections for A5205, forced TOD pin state in toggle mode to be low at shutdown
 * 12/11/13  21		  BDO 		Add configurable macro NVMGETERRORSTATUS()                                      11065
 * 12/12/13  22		  BDO 		Added StaMd_Init0 as a trusted call to only handle ReadTypeH memory across applications   11065
 * 12/20/13  23		  BDO 		Changed StaMd_Init0 prototype to indicate non-Rte function
 * 02/06/14  24		  BDO 		Updated to FDD ES10B version 13 to address anomaly 5388                         11347
 * 10/27/14  25       BDO       Anomaly 7307 - software updates for consistency with FDD ES10B version 13, QAC  12602
 */

#define STAMD_C
/*****************************************************************************
* Include files
*****************************************************************************/
#include "Rte_Ap_StaMd.h"
#include "Std_Types.h"
#include "Ap_StaMd_Cfg.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "Os.h"

/*****************************************************************************
* Macro Definitions
*****************************************************************************/
#define D_STATELKPVCTRS_CNT_U16  16U
#define D_STATELKPSTATES_CNT_U16  4U

#define D_TVBITF_CNT_U16        0x01U
#define D_TVBITC_CNT_U16        0x02U
#define D_TVBITM_CNT_U16        0x04U
#define D_TVBITA_CNT_U16        0x08U

#define D_CLOSECHECKVALUE_CNT_U32	0x00FF00FFUL
#define D_CLOSECHECKGARBAGE_CNT_U32	0x5555AAAAUL

#define SetBits_m(var, mask)    ((var) = (var) | (mask)) /*TODO: move this to a global library */
#define ClrBits_m(var, mask)    ((var) = (var) & (mask)) /*TODO: move this to a global library */

/*****************************************************************************
* NvM Data Definition
*****************************************************************************/
#define STAMD_START_SEC_VAR_SAVED_ZONEHGS_32
#include "MemMap.h" /* PRQA S 5087 */
VAR(uint32, AP_DIAGMGR_VAR) CloseCheck_Cnt_u32;
#define STAMD_STOP_SEC_VAR_SAVED_ZONEHGS_32
#include "MemMap.h" /* PRQA S 5087 */

#define STAMD_START_SEC_VAR_SAVED_ZONEHGS_8
#include "MemMap.h" /* PRQA S 5087 */
VAR(uint8, AP_DIAGMGR_VAR) TypeHData_Cnt_u08[D_TYPEHDATASIZE_CNT_U16];
#define STAMD_STOP_SEC_VAR_SAVED_ZONEHGS_8
#include "MemMap.h" /* PRQA S 5087 */

/*****************************************************************************
* Constant Definitions
*****************************************************************************/
#define STAMD_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC CONST(Rte_ModeType_StaMd_Mode, AUTOMATIC) t_StateLkpTbl_Cnt_u8[D_STATELKPSTATES_CNT_U16][D_STATELKPVCTRS_CNT_U16] = {
{   /* Disable Trans Vectors */
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_DISABLE
},
{   /* OFF Trans Vectors */	
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_OFF,
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_WARMINIT
	
},
{   /* Operate Trans Vectors */  	
	RTE_MODE_StaMd_Mode_OPERATE,
	RTE_MODE_StaMd_Mode_OPERATE,
	RTE_MODE_StaMd_Mode_OPERATE,
	RTE_MODE_StaMd_Mode_OPERATE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_OPERATE,
	RTE_MODE_StaMd_Mode_OPERATE,
	RTE_MODE_StaMd_Mode_OPERATE,
	RTE_MODE_StaMd_Mode_OPERATE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE
},
{   /* Warm Init Trans Vectors */
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE, 
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_DISABLE, 
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_WARMINIT,
	RTE_MODE_StaMd_Mode_DISABLE,
	RTE_MODE_StaMd_Mode_OPERATE,
	RTE_MODE_StaMd_Mode_DISABLE
}
};
#define STAMD_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

/*****************************************************************************
* Local Function Prototypes
*****************************************************************************/
STATIC INLINE FUNC(uint8, RTE_AP_STAMD_APPL_CODE) BldTranVctr(	VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC) SysState_Cnt_T_Enum,
																VAR(boolean, AUTOMATIC) FTermActive_Cnt_T_lgc,
																VAR(boolean, AUTOMATIC) CTermActive_Cnt_T_lgc,
																VAR(boolean, AUTOMATIC) ATermActive_Cnt_T_lgc,
																VAR(boolean, AUTOMATIC) RampStatusCmp_Cnt_T_lgc,
																VAR(boolean, AUTOMATIC) CtrldDmpStsCmp_Cnt_T_lgc);

STATIC INLINE FUNC(void, RTE_AP_STAMD_APPL_CODE) ReadTypeH(void);
STATIC INLINE FUNC(void, RTE_AP_STAMD_APPL_CODE) WriteTypeH(void);
STATIC INLINE FUNC(boolean, RTE_AP_STAMD_APPL_CODE) CheckWarmInitComplete(void);

/*****************************************************************************
* Global Function Definitions
*****************************************************************************/

/**********************************************************************************************************************
 *
 * Function: 	StaMd_Init0
 * Description: This function reads the TypeH global shared memory and copies it to the respective RAM location in
 *			    each application and also monitors for failure to write eeprom diagnostic. This function is "trusted" and
 *			    called outside of the Rte since the ReadTypeH will write different application memory.
 * Triggered: 	Once at Init (Cold Init)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, AP_STAMD_CODE) StaMd_Init0(void)
{
	ReadTypeH();
}


/**********************************************************************************************************************
 *
 * Function: 	StaMd_Init1
 * Description: StaMd init tasks are handled here. This function is called from the Rte
 * Triggered: 	Once at Init (Cold Init)
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_STAMD_APPL_CODE) StaMd_Init1(void)
{
	if( CloseCheck_Cnt_u32 == D_CLOSECHECKVALUE_CNT_U32 )
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EEPROMCloseFailed, 1U, NTC_STATUS_PASSED);
	}
	else
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EEPROMCloseFailed, 1U, NTC_STATUS_FAILED);
	}
	
	CloseCheck_Cnt_u32 = D_CLOSECHECKGARBAGE_CNT_U32;
	
	(void)Rte_Call_CloseCheckData_WriteBlock(NULL_PTR);
	
}

/**********************************************************************************************************************
 *
 * Function: 	StaMd_Per1
 * Description: 
 * Triggered: 	Periodic in all states
 * Inputs: 		ATerm_Cnt_lgc
 * 				ControlledDampStatusComplete_Cnt_lgc
 *				CTerm_Cnt_lgc
 *				FTerm_Cnt_lgc
 *				RampStatusComplete_Cnt_lgc
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_STAMD_APPL_CODE) StaMd_Per1(void)
{
	VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC) SysState_Cnt_T_enum;
	VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC) NxtSysState_Cnt_T_enum;
	VAR(uint8, AUTOMATIC) TransVec_Cnt_T_u8;
	VAR(boolean, AUTOMATIC) FTermActive_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) CTermActive_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) ATermActive_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) RampStatusCmp_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) CtrldDmpStsCmp_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) TMFTestComplete_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) TransitionComplete_Cnt_T_lgc;
#if (STD_ON == BC_STAMD_SYSCHKINCOREAPP)
	VAR(NxtrDiagMgrStatus, AUTOMATIC) FaultStatus_Cnt_T_enum;
#endif
	VAR(uint8, AUTOMATIC) i;

	/* Configurable Start of Runnable Checkpoint */
	(void)Rte_Call_StaMd_Per1_CP0_CheckpointReached();

	FTermActive_Cnt_T_lgc = Rte_IRead_StaMd_Per1_FTerm_Cnt_lgc();
	CTermActive_Cnt_T_lgc = Rte_IRead_StaMd_Per1_CTerm_Cnt_lgc();
	ATermActive_Cnt_T_lgc = Rte_IRead_StaMd_Per1_ATerm_Cnt_lgc();
	RampStatusCmp_Cnt_T_lgc = Rte_IRead_StaMd_Per1_RampStatusComplete_Cnt_lgc();
	CtrldDmpStsCmp_Cnt_T_lgc = Rte_IRead_StaMd_Per1_ControlledDampStatusComplete_Cnt_lgc();
	TMFTestComplete_Cnt_T_lgc = Rte_IRead_StaMd_Per1_TMFTestComplete_Cnt_lgc();
	 
	SysState_Cnt_T_enum = Rte_Mode_SystemState_Mode();

	#if ((STD_ON == BC_STAMD_TODSTEADYSTATE) || (STD_ON == BC_STAMD_TOD2MSTOGGLE))
		if (FALSE == StopTODPerOperation_Cnt_M_lgc)
		{
			#if (STD_ON == BC_STAMD_TODSTEADYSTATE)
				(void)Rte_Call_TOD_OP_SET(TRUE);
			#else
				if (TRUE == TODState_Cnt_M_lgc)
				{
					TODState_Cnt_M_lgc = FALSE;
				}
				else
				{
					TODState_Cnt_M_lgc = TRUE;
				}
				(void)Rte_Call_TOD_OP_SET(TODState_Cnt_M_lgc);
			#endif
		}
	#endif

	switch(SysState_Cnt_T_enum)
	{
		case RTE_MODE_StaMd_Mode_OPERATE:
		case RTE_MODE_StaMd_Mode_DISABLE:
		case RTE_MODE_StaMd_Mode_WARMINIT:
		case RTE_MODE_StaMd_Mode_OFF:
			
			TransitionComplete_Cnt_T_lgc = TRUE;
			for (i = 0U; i<TableSize_m(T_CurrentSystemState_Ptr_enum); i++)
			{
				if (*(T_CurrentSystemState_Ptr_enum[i]) != SysState_Cnt_T_enum)
				{
					TransitionComplete_Cnt_T_lgc = FALSE;
				}
			}
			
			/* Log Transition Status for Systematic Check */
			TransitionComplete_Cnt_M_lgc = TransitionComplete_Cnt_T_lgc;

			/* Only check for state change if all applications are in the same state */
			if (TRUE == TransitionComplete_Cnt_T_lgc)
			{
				TransVec_Cnt_T_u8 = BldTranVctr(SysState_Cnt_T_enum,
							   FTermActive_Cnt_T_lgc,
							   CTermActive_Cnt_T_lgc,
							   ATermActive_Cnt_T_lgc,
							   RampStatusCmp_Cnt_T_lgc,
							   CtrldDmpStsCmp_Cnt_T_lgc);

				StTrnsVctr_Cnt_D_b08 = TransVec_Cnt_T_u8;

				NxtSysState_Cnt_T_enum = t_StateLkpTbl_Cnt_u8[SysState_Cnt_T_enum][TransVec_Cnt_T_u8];
				
				if ((TRUE == EcuResetActive_Cnt_M_lgc) || (TRUE == FBLTransitionActive_Cnt_M_lgc))
				{
					NxtSysState_Cnt_T_enum = RTE_MODE_StaMd_Mode_OFF;
					ForceToOff_Cnt_M_lgc = TRUE;
				}
				
				/* Protect against going into disable until TMF test is completed to protect TOD signal */
				if ((RTE_MODE_StaMd_Mode_DISABLE == NxtSysState_Cnt_T_enum) &&
					(RTE_MODE_StaMd_Mode_WARMINIT == SysState_Cnt_T_enum) &&
					(FALSE == TMFTestComplete_Cnt_T_lgc))
				{
					NxtSysState_Cnt_T_enum = RTE_MODE_StaMd_Mode_WARMINIT;
				}

				if (NxtSysState_Cnt_T_enum != SysState_Cnt_T_enum)
				{
					#if ((STD_ON == BC_STAMD_TODSTEADYSTATE) || (STD_ON == BC_STAMD_TOD2MSTOGGLE))
						if (NxtSysState_Cnt_T_enum != RTE_MODE_StaMd_Mode_OFF)
						{
							StopTODPerOperation_Cnt_M_lgc = FALSE;
						}
					#endif

					/* Set the new system state for other applications to monitor */
					SystemState_Cnt_M_enum = NxtSysState_Cnt_T_enum;
					(void)Rte_Switch_SystemState_Mode(NxtSysState_Cnt_T_enum);
				}

				#if (STD_ON == BC_STAMD_SYSCHKINCOREAPP)
					FaultStatus_Cnt_T_enum = SystemStateCheck(	FTermActive_Cnt_T_lgc,
																CTermActive_Cnt_T_lgc,
																ATermActive_Cnt_T_lgc,
																RampStatusCmp_Cnt_T_lgc,
																CtrldDmpStsCmp_Cnt_T_lgc,
																TMFTestComplete_Cnt_T_lgc,
																&StaMdsSysCFltCntr_Cnt_M_u16);

					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_StaMdsSysC, 1U, FaultStatus_Cnt_T_enum);
				#endif
			}
			
			break;
		default:
			/* Do Nothing, Wait for Transition to Pass */
			TransitionComplete_Cnt_M_lgc = FALSE; /* Manually set to false since a transition is being called for: A_5108 */
			break;
	}

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_StaMd_Per1_CP1_CheckpointReached();
	
}

/**********************************************************************************************************************
 *
 * Function: 	StaMd_Trns1
 * Description: This function writes the application typeH data to the global NvM Buffer
 * Triggered: 	On Entering OFF state
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_STAMD_APPL_CODE) StaMd_Trns1(void)
{
	if (TRUE == ForceToOff_Cnt_M_lgc)
	{
		(void)Rte_Write_InitiatePwrDnFastWrite_Cnt_lgc(TRUE);
	}
	else
	{
		(void)Rte_Write_InitiatePwrDnNormalWrite_Cnt_lgc(TRUE);
	}

	WriteTypeH();
	/* Implementation of Post Run Requirements, which can not be met by the normal EcuM Shutdown design */

	/* Depending on the OS applications selected in configurator for StaMd and DemIf, the call will be a client/server (same application)
	 * or a task activation (different tasks) */

	#if(D_STAMD_DIAGMGR_CLIENTSERVER_CALL == STD_ON)
		(void)Rte_Call_DiagMgr_StaCtrl_Shutdown();
	#else
		ActivateTask(D_DIAGMGR_SHUTDOWN_TASK);
	#endif

	NVMWRITEALLFUNC();
	FinalNvMWriteInProgress_Cnt_M_lgc = TRUE;
}


/**********************************************************************************************************************
 *
 * Function: 	MilestoneRqst_WarmInitMilestoneComplete
 * Description: This function indicates milestone complete for a user
 * Triggered: 	On Invocation
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_STAMD_APPL_CODE) MilestoneRqst_WarmInitMilestoneComplete(StaMd_Users user)
{
	VAR(uint32, AUTOMATIC) MilestoneRqst_Cnt_T_u32;

	Rte_Enter_StaMds_MilestoneRqst_WARMINIT_ExclArea();
	
	MilestoneRqst_Cnt_T_u32 = WarmInitMilestoneRqst_Cnt_M_u32;
	ClrBits_m(MilestoneRqst_Cnt_T_u32, (~(1U << user)));
	WarmInitMilestoneRqst_Cnt_M_u32 = MilestoneRqst_Cnt_T_u32;
	
	Rte_Exit_StaMds_MilestoneRqst_WARMINIT_ExclArea();
}

/**********************************************************************************************************************
 *
 * Function: 	MilestoneRqst_WarmInitMilestoneNotComplete
 * Description: This function indicates milestone not complete for a user
 * Triggered: 	On Invocation
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_STAMD_APPL_CODE) MilestoneRqst_WarmInitMilestoneNotComplete(StaMd_Users user)
{
	VAR(uint32, AUTOMATIC) MilestoneRqst_Cnt_T_u32;

	Rte_Enter_StaMds_MilestoneRqst_WARMINIT_ExclArea();
	
	MilestoneRqst_Cnt_T_u32 = WarmInitMilestoneRqst_Cnt_M_u32;
	SetBits_m(MilestoneRqst_Cnt_T_u32, (1U << user));
	WarmInitMilestoneRqst_Cnt_M_u32 = MilestoneRqst_Cnt_T_u32;
	
	Rte_Exit_StaMds_MilestoneRqst_WARMINIT_ExclArea();
}

/**********************************************************************************************************************
 *
 * Function: 	StaMd_SCom_EcuReset
 * Description: This function sets a flag to perform an ECU Reset
 * Triggered: 	On Invocation
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_STAMD_APPL_CODE) StaMd_SCom_EcuReset( void )
{
	EcuResetActive_Cnt_M_lgc = TRUE;
}

/**********************************************************************************************************************
 *
 * Function: 	StaMd_SCom_FBLTransitionReq
 * Description: This function sets a flag to perform an transition to OFF and NVM update
 * Triggered: 	On Invocation
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_STAMD_APPL_CODE) StaMd_SCom_FBLTransitionReq( void )
{
	FBLTransitionActive_Cnt_M_lgc = TRUE;
}

/**********************************************************************************************************************
 *
 * Function: 	SystemStateCheck
 * Description: This function performs the safety check for systematic coverage
 * Triggered: 	On Invocation
 * Inputs: 		None
 * Outputs: 	None
 *
 **********************************************************************************************************************/
FUNC(NxtrDiagMgrStatus, RTE_AP_STAMD_APPL_CODE) SystemStateCheck(	VAR(boolean, AUTOMATIC) FTermActive_Cnt_T_lgc,
																	VAR(boolean, AUTOMATIC) CTermActive_Cnt_T_lgc,
																	VAR(boolean, AUTOMATIC) ATermActive_Cnt_T_lgc,
																	VAR(boolean, AUTOMATIC) RampStatusCmp_Cnt_T_lgc,
																	VAR(boolean, AUTOMATIC) CtrldDmpStsCmp_Cnt_T_lgc,
																	VAR(boolean, AUTOMATIC) TMFTestComplete_Cnt_T_lgc,
																	P2VAR(uint16, AUTOMATIC, AUTOMATIC) SysCFltCntr_Ptr_T_u16)
{
	VAR(NxtrDiagMgrStatus, AUTOMATIC) FaultStatus_Cnt_T_enum = NTC_STATUS_PREPASSED;

	/* Only run state check if master mode has not detected any application being in the process of transitioning */
	if (TRUE == TransitionComplete_Cnt_M_lgc)
	{
		switch(SysCSystemState_Cnt_M_enum)
		{

			case RTE_MODE_StaMd_Mode_OPERATE:
				if ((TRUE == RampStatusCmp_Cnt_T_lgc) || (TRUE == CtrldDmpStsCmp_Cnt_T_lgc))
				{
					SysCSystemState_Cnt_M_enum = RTE_MODE_StaMd_Mode_DISABLE;
				}
				break;
			case RTE_MODE_StaMd_Mode_DISABLE:
				if ((FALSE == FTermActive_Cnt_T_lgc) &&
					(TRUE == CTermActive_Cnt_T_lgc) &&
					(TRUE == ATermActive_Cnt_T_lgc))
				{
					SysCSystemState_Cnt_M_enum = RTE_MODE_StaMd_Mode_WARMINIT;
				}
				else if (FALSE == ATermActive_Cnt_T_lgc)
				{
					SysCSystemState_Cnt_M_enum = RTE_MODE_StaMd_Mode_OFF;
				}
				else
				{
					/* SysCSystemState_Cnt_M_enum stays in RTE_MODE_StaMd_Mode_DISABLE */
				}
				break;
			case RTE_MODE_StaMd_Mode_WARMINIT:
				if ((CheckWarmInitComplete() == TRUE) &&
					(FALSE == FTermActive_Cnt_T_lgc) &&
					(TRUE == CTermActive_Cnt_T_lgc) &&
					(TRUE == ATermActive_Cnt_T_lgc))
				{
					SysCSystemState_Cnt_M_enum = RTE_MODE_StaMd_Mode_OPERATE;
				}
				else if (((FALSE == ATermActive_Cnt_T_lgc) ||
						  (TRUE == FTermActive_Cnt_T_lgc)) &&
						  (TRUE == TMFTestComplete_Cnt_T_lgc))
				{
					SysCSystemState_Cnt_M_enum = RTE_MODE_StaMd_Mode_DISABLE;
				}
				else
				{
					/* SysCSystemState_Cnt_M_enum stays in RTE_MODE_StaMd_Mode_WARMINIT */
				}
				break;
			default: /*RTE_MODE_StaMd_Mode_OFF*/
				if (TRUE == ATermActive_Cnt_T_lgc)
				{
					SysCSystemState_Cnt_M_enum = RTE_MODE_StaMd_Mode_WARMINIT;
				}
				break;
		}

		if ((TRUE == EcuResetActive_Cnt_M_lgc) || (TRUE == FBLTransitionActive_Cnt_M_lgc))
		{
			SysCSystemState_Cnt_M_enum = RTE_MODE_StaMd_Mode_OFF; /* ForceToOff */
		}

		if (SysCSystemState_Cnt_M_enum != SystemState_Cnt_M_enum)
		{
			*SysCFltCntr_Ptr_T_u16 = DiagPStep_m(*SysCFltCntr_Ptr_T_u16, k_StaMdsSysCDiag_Cnt_str);
		}
		else
		{
			*SysCFltCntr_Ptr_T_u16 = DiagNStep_m(*SysCFltCntr_Ptr_T_u16, k_StaMdsSysCDiag_Cnt_str);
		}

		if( (DiagFailed_m(*SysCFltCntr_Ptr_T_u16, k_StaMdsSysCDiag_Cnt_str)) == TRUE)
		{
			/* Set fault */
			FaultStatus_Cnt_T_enum = NTC_STATUS_FAILED;
		}
		else
		{
			/* Clear Fault */
			if(*SysCFltCntr_Ptr_T_u16 == 0u)
			{
				FaultStatus_Cnt_T_enum = NTC_STATUS_PASSED;
			}
		}

	}

	return(FaultStatus_Cnt_T_enum);
}
/*****************************************************************************
* Local Function Definitions
*****************************************************************************/

/**********************************************************************************************************************
 * Function: 	BldTranVctr
 * Description: This function will build the system state transition vector for table lookup
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(uint8, RTE_AP_STAMD_APPL_CODE) BldTranVctr(	VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC) SysState_Cnt_T_Enum,
																VAR(boolean, AUTOMATIC) FTermActive_Cnt_T_lgc,
																VAR(boolean, AUTOMATIC) CTermActive_Cnt_T_lgc,
																VAR(boolean, AUTOMATIC) ATermActive_Cnt_T_lgc,
																VAR(boolean, AUTOMATIC) RampStatusCmp_Cnt_T_lgc,
																VAR(boolean, AUTOMATIC) CtrldDmpStsCmp_Cnt_T_lgc)
{
	VAR(uint8, AUTOMATIC) TransVec_Cnt_T_u8 = 0U;
	VAR(NvM_RequestResultType, AUTOMATIC) NVMErrorStatus_Cnt_T_u8;
	

	/* Evaluate the state request bitfields */
	if (TRUE == FTermActive_Cnt_T_lgc)
	{
		SetBits_m(TransVec_Cnt_T_u8, D_TVBITF_CNT_U16);
	}
	if (TRUE == CTermActive_Cnt_T_lgc)
	{
		SetBits_m(TransVec_Cnt_T_u8, D_TVBITC_CNT_U16);
	}
	if (TRUE == ATermActive_Cnt_T_lgc)
	{
		SetBits_m(TransVec_Cnt_T_u8, D_TVBITA_CNT_U16);
	}

	/* State Dependant M Bit Determination */
	switch (SysState_Cnt_T_Enum){
	case RTE_MODE_StaMd_Mode_OPERATE:	
		if ((TRUE == RampStatusCmp_Cnt_T_lgc) || (CtrldDmpStsCmp_Cnt_T_lgc == TRUE))
		{
			SetBits_m(TransVec_Cnt_T_u8, D_TVBITM_CNT_U16);
		}
		break;
	case RTE_MODE_StaMd_Mode_WARMINIT:	
		if (CheckWarmInitComplete() == TRUE)
		{
			SetBits_m(TransVec_Cnt_T_u8, D_TVBITM_CNT_U16);
		}
		break;
	case RTE_MODE_StaMd_Mode_OFF:	
		NVMGETERRORSTATUS(0U, &NVMErrorStatus_Cnt_T_u8);
		if (NVM_REQ_PENDING != NVMErrorStatus_Cnt_T_u8)
		{
			if( FinalNvMWriteInProgress_Cnt_M_lgc == TRUE )
			{
				FinalNvMWriteInProgress_Cnt_M_lgc = FALSE;
				(void)Rte_Write_InitiatePwrDnNormalWrite_Cnt_lgc(FALSE); /* Normal Write Complete - protect against quick ignition cycle */
				
				CloseCheck_Cnt_u32 = D_CLOSECHECKVALUE_CNT_U32;
				(void)Rte_Call_CloseCheckData_WriteBlock(NULL_PTR);
			}
			else
			{
				(void)Rte_Call_CloseCheckData_GetErrorStatus(&NVMErrorStatus_Cnt_T_u8);
				if (NVM_REQ_PENDING != NVMErrorStatus_Cnt_T_u8)
				{
					SetBits_m(TransVec_Cnt_T_u8, D_TVBITM_CNT_U16);

					ForceToOff_Cnt_M_lgc = FALSE;
					(void)Rte_Write_InitiatePwrDnFastWrite_Cnt_lgc(FALSE); /* Fast Write Complete - only after all Blocks, including CloseCheckData, are written */

					if (TRUE == EcuResetActive_Cnt_M_lgc)
					{
						Mcu_PerformReset();
					}
					else if (TRUE == FBLTransitionActive_Cnt_M_lgc)
					{
						(void)Rte_Write_PwrDnFastWriteComplete_Cnt_lgc(TRUE); /* Not in FDD rev. 13 - write complete status flag added to complete FBL transition */
					}
					else
					{
						#if ((STD_ON == BC_STAMD_TODSTEADYSTATE) || (STD_ON == BC_STAMD_TOD2MSTOGGLE))
							(void)Rte_Call_TOD_OP_SET(FALSE);
							StopTODPerOperation_Cnt_M_lgc  = TRUE;
						#endif
					}
				}
				
			}
		}
		break;
	default:
		/* Do nothing */
		break;
	}		

	return(TransVec_Cnt_T_u8);
}

/**********************************************************************************************************************
 * Function: 	ReadTypeH
 * Description: This function will read the TypeH block and distribute it to each application
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(void, RTE_AP_STAMD_APPL_CODE) ReadTypeH(void)
{
	VAR(uint8, AUTOMATIC) TypeHInfoIdx_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) AppTypeHIdx_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) TypeHIdx_Cnt_T_u16 = 0U;

	SuspendAllInterrupts();
	for (TypeHInfoIdx_Cnt_T_u08 = 0U; TypeHInfoIdx_Cnt_T_u08 < TableSize_m(T_TypeHInfo_Cnt_Str); TypeHInfoIdx_Cnt_T_u08++)
	{
		if (T_TypeHInfo_Cnt_Str[TypeHInfoIdx_Cnt_T_u08].Size != 0U)
		{
			for (AppTypeHIdx_Cnt_T_u16 = 0U; AppTypeHIdx_Cnt_T_u16 < T_TypeHInfo_Cnt_Str[TypeHInfoIdx_Cnt_T_u08].Size; AppTypeHIdx_Cnt_T_u16++)
			{
				T_TypeHInfo_Cnt_Str[TypeHInfoIdx_Cnt_T_u08].Start[AppTypeHIdx_Cnt_T_u16] = TypeHData_Cnt_u08[TypeHIdx_Cnt_T_u16];
				TypeHIdx_Cnt_T_u16++;
			}
		}
	}
	ResumeAllInterrupts();
}

/**********************************************************************************************************************
 * Function: 	WriteTypeH
 * Description: This function will read the TypeH from each application and write it to the TypeH block
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(void, RTE_AP_STAMD_APPL_CODE) WriteTypeH(void)
{
	VAR(uint8, AUTOMATIC) TypeHInfoIdx_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) AppTypeHIdx_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) TypeHIdx_Cnt_T_u16 = 0U;

	SuspendAllInterrupts();
	for (TypeHInfoIdx_Cnt_T_u08 = 0U; TypeHInfoIdx_Cnt_T_u08 < TableSize_m(T_TypeHInfo_Cnt_Str); TypeHInfoIdx_Cnt_T_u08++)
	{
		if (T_TypeHInfo_Cnt_Str[TypeHInfoIdx_Cnt_T_u08].Size != 0U)
		{
			for (AppTypeHIdx_Cnt_T_u16 = 0U; AppTypeHIdx_Cnt_T_u16 < T_TypeHInfo_Cnt_Str[TypeHInfoIdx_Cnt_T_u08].Size; AppTypeHIdx_Cnt_T_u16++)
			{
				TypeHData_Cnt_u08[TypeHIdx_Cnt_T_u16] = T_TypeHInfo_Cnt_Str[TypeHInfoIdx_Cnt_T_u08].Start[AppTypeHIdx_Cnt_T_u16];
				TypeHIdx_Cnt_T_u16++;
			}
		}
	}
	ResumeAllInterrupts();

	(void)Rte_Call_TypeHData_WriteBlock(NULL_PTR);
}

/**********************************************************************************************************************
 * Function: 	CheckWarmInitComplete
 * Description: This function determine if WarmInit milestones are completed
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(boolean, RTE_AP_STAMD_APPL_CODE) CheckWarmInitComplete(void)
{
	VAR(uint32, AUTOMATIC) WarmInitMilestoneRqst_Cnt_T_u32;
	VAR(boolean, AUTOMATIC) WarmInitMilestoneComp_Cnt_T_lgc;
	VAR(uint8, AUTOMATIC) i;

	WarmInitMilestoneRqst_Cnt_T_u32 = 0U;
	for (i = 0U; i < TableSize_m(T_WarmInitMilestoneRqst_Ptr_enum); i++)
	{
		WarmInitMilestoneRqst_Cnt_T_u32 |= *(T_WarmInitMilestoneRqst_Ptr_enum[i]);
	}

	if(0U == WarmInitMilestoneRqst_Cnt_T_u32)
	{
		WarmInitMilestoneComp_Cnt_T_lgc = TRUE;
	}
	else
	{
		WarmInitMilestoneComp_Cnt_T_lgc = FALSE;
	}

	return(WarmInitMilestoneComp_Cnt_T_lgc);
}
