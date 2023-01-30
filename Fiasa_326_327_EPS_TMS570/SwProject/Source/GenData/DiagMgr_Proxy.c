
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : DiagMgr_Proxy.c
* Module Description: DiagMgr Proxy Interface
* Product           : Gen II Plus - EA3.0
* Generator         : artt 2.0.2.0
* Generation Time   : 24.01.2014 12:23:59
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 13 18:34:17 2012
 * %version:          5 %
 * %date_modified:    Fri Jan 24 16:25:20 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/13/12   1       JJW       Initial template creation
 */



/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#define DIAGMGR_C /* Enable visibility to Module internal definitions in DiagMgr.h*/
#define DIAGMGR_DEMIF_RTEHEADER
#include "Ap_DiagMgr.h"
#include "Os.h"

/*******************************************************************************
**                      Proxy Server Functions                                **
*******************************************************************************/

 

/* Ap_8 stateless init core function */
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr8_Init( void )
{
	/* Invoke stateless Init Function with reference to appropriate application */
	DiagMgr_Init_Core( 	DiagMgr_NTCInfo8_Cnt_M_str, 
						DIAGMGR_EVENTNUM_8,
						DIAGMGR_APID_8, 
						&DiagMgrInitComp8_Cnt_M_lgc,
						NTCInfoQueue8_Cnt_M_str,
						&NTCQueueIndex8_Cnt_M_u08,
						DiagSts8_Cnt_M_b16,
						ActiveRmpRate8_UlspmS_M_f32,
						&ActDiagSts8_Cnt_M_u08);
}

/* Ap_8 stateless periodic core function */
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr8_Per( void )
{
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_DiagMgr8_Per_CP0_CheckpointReached();
	
	/* Invoke stateless Periodic Function with reference to appropriate application */
	DiagMgr_Per_Core( 	DiagMgr_NTCInfo8_Cnt_M_str, 
						DIAGMGR_EVENTNUM_8,
						DiagSts8_Cnt_M_b16,
						ActiveRmpRate8_UlspmS_M_f32,
						&ActDiagSts8_Cnt_M_u08,
						T_NTCMapTbl8_Cnt_enum,
						&ResetNTCFlag8_Cnt_M_u08);
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_DiagMgr8_Per_CP1_CheckpointReached();
}

/* Ap_8 stateless transition core function */
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr8_Trns( void )
{
	/* Invoke stateless Transition Function with reference to appropriate application */
	DiagMgr_Trns_Core( 	DiagMgr_NTCInfo8_Cnt_M_str, 
						DIAGMGR_EVENTNUM_8,
						T_NTCMapTbl8_Cnt_enum);
}

/* Ap_8 forwarding stateless proxy functions to stateless core function */
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr8_GetNTCFailed( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, P2VAR(boolean, AUTOMATIC, AUTOMATIC) NTCFailed_Ptr_T_lgc )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_GetNTCFailed_Core( NTC_Cnt_T_enum, NTCFailed_Ptr_T_lgc));
}

/* Ap_8 forwarding stateless proxy functions to stateless core function */
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr8_GetNTCActive( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, P2VAR(boolean, AUTOMATIC, AUTOMATIC) NTCActive_Ptr_T_lgc )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_GetNTCActive_Core( NTC_Cnt_T_enum, NTCActive_Ptr_T_lgc));
}

/* Ap_8 forwarding stateless proxy functions to stateless core function */
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr8_GetNTCStatus( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, P2VAR(uint8, AUTOMATIC, AUTOMATIC) Status_Ptr_T_u08 )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_GetNTCStatus_Core( NTC_Cnt_T_enum, Status_Ptr_T_u08));
}


FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr8_SetNTCStatus( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_SetNTCStatus_Core( 	NTC_Cnt_T_enum,
											Param_Cnt_T_u08,
											Status_Cnt_T_enum,
											DiagMgr_NTCInfo8_Cnt_M_str,
											DiagSts8_Cnt_M_b16,
											ActiveRmpRate8_UlspmS_M_f32,
											&ActDiagSts8_Cnt_M_u08));
}
	
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr8_ReportNTCStatus( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum )
{
	VAR(Std_ReturnType, AUTOMATIC) RetVal;
	
	/* Forward request to stateless handler with reference to appropriate application data structures */
	SuspendAllInterrupts();
	if (FALSE == DiagMgrInitComp8_Cnt_M_lgc)
	{
		RetVal = NxtrDiagMgr_ReportNTCStatus_Core(	NTC_Cnt_T_enum,
													Param_Cnt_T_u08,
													Status_Cnt_T_enum,
													NTCInfoQueue8_Cnt_M_str,
													&NTCQueueIndex8_Cnt_M_u08);
		ResumeAllInterrupts();
	}
	else
	{
		ResumeAllInterrupts();
		RetVal = NxtrDiagMgr_SetNTCStatus_Core( NTC_Cnt_T_enum,
												Param_Cnt_T_u08,
												Status_Cnt_T_enum,
												DiagMgr_NTCInfo8_Cnt_M_str,
												DiagSts8_Cnt_M_b16,
												ActiveRmpRate8_UlspmS_M_f32,
												&ActDiagSts8_Cnt_M_u08);
	}
	
	return(RetVal);
}

/* Ap_9 stateless init core function */
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr9_Init( void )
{
	/* Invoke stateless Init Function with reference to appropriate application */
	DiagMgr_Init_Core( 	DiagMgr_NTCInfo9_Cnt_M_str, 
						DIAGMGR_EVENTNUM_9,
						DIAGMGR_APID_9, 
						&DiagMgrInitComp9_Cnt_M_lgc,
						NTCInfoQueue9_Cnt_M_str,
						&NTCQueueIndex9_Cnt_M_u08,
						DiagSts9_Cnt_M_b16,
						ActiveRmpRate9_UlspmS_M_f32,
						&ActDiagSts9_Cnt_M_u08);
					
	Rte_Call_DemIf_SetOperationCycleState(NxtrDefaultOpCycle, NXTR_CYCLE_STATE_START);
}

/* Ap_9 stateless periodic core function */
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr9_Per( void )
{
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_DiagMgr9_Per_CP0_CheckpointReached();
	
	/* Invoke stateless Periodic Function with reference to appropriate application */
	DiagMgr_Per_Core( 	DiagMgr_NTCInfo9_Cnt_M_str, 
						DIAGMGR_EVENTNUM_9,
						DiagSts9_Cnt_M_b16,
						ActiveRmpRate9_UlspmS_M_f32,
						&ActDiagSts9_Cnt_M_u08,
						T_NTCMapTbl9_Cnt_enum,
						&ResetNTCFlag9_Cnt_M_u08);
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_DiagMgr9_Per_CP1_CheckpointReached();
}

/* Ap_9 stateless transition core function */
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr9_Trns( void )
{
	/* Invoke stateless Transition Function with reference to appropriate application */
	DiagMgr_Trns_Core( 	DiagMgr_NTCInfo9_Cnt_M_str, 
						DIAGMGR_EVENTNUM_9,
						T_NTCMapTbl9_Cnt_enum);
}

/* Ap_9 forwarding stateless proxy functions to stateless core function */
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr9_GetNTCFailed( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, P2VAR(boolean, AUTOMATIC, AUTOMATIC) NTCFailed_Ptr_T_lgc )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_GetNTCFailed_Core( NTC_Cnt_T_enum, NTCFailed_Ptr_T_lgc));
}

/* Ap_9 forwarding stateless proxy functions to stateless core function */
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr9_GetNTCActive( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, P2VAR(boolean, AUTOMATIC, AUTOMATIC) NTCActive_Ptr_T_lgc )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_GetNTCActive_Core( NTC_Cnt_T_enum, NTCActive_Ptr_T_lgc));
}

/* Ap_9 forwarding stateless proxy functions to stateless core function */
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr9_GetNTCStatus( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, P2VAR(uint8, AUTOMATIC, AUTOMATIC) Status_Ptr_T_u08 )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_GetNTCStatus_Core( NTC_Cnt_T_enum, Status_Ptr_T_u08));
}


FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr9_SetNTCStatus( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_SetNTCStatus_Core( 	NTC_Cnt_T_enum,
											Param_Cnt_T_u08,
											Status_Cnt_T_enum,
											DiagMgr_NTCInfo9_Cnt_M_str,
											DiagSts9_Cnt_M_b16,
											ActiveRmpRate9_UlspmS_M_f32,
											&ActDiagSts9_Cnt_M_u08));
}
	
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr9_ReportNTCStatus( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum )
{
	VAR(Std_ReturnType, AUTOMATIC) RetVal;
	
	/* Forward request to stateless handler with reference to appropriate application data structures */
	SuspendAllInterrupts();
	if (FALSE == DiagMgrInitComp9_Cnt_M_lgc)
	{
		RetVal = NxtrDiagMgr_ReportNTCStatus_Core(	NTC_Cnt_T_enum,
													Param_Cnt_T_u08,
													Status_Cnt_T_enum,
													NTCInfoQueue9_Cnt_M_str,
													&NTCQueueIndex9_Cnt_M_u08);
		ResumeAllInterrupts();
	}
	else
	{
		ResumeAllInterrupts();
		RetVal = NxtrDiagMgr_SetNTCStatus_Core( NTC_Cnt_T_enum,
												Param_Cnt_T_u08,
												Status_Cnt_T_enum,
												DiagMgr_NTCInfo9_Cnt_M_str,
												DiagSts9_Cnt_M_b16,
												ActiveRmpRate9_UlspmS_M_f32,
												&ActDiagSts9_Cnt_M_u08);
	}
	
	return(RetVal);
}

/* Ap_10 stateless init core function */
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr10_Init( void )
{
	/* Invoke stateless Init Function with reference to appropriate application */
	DiagMgr_Init_Core( 	DiagMgr_NTCInfo10_Cnt_M_str, 
						DIAGMGR_EVENTNUM_10,
						DIAGMGR_APID_10, 
						&DiagMgrInitComp10_Cnt_M_lgc,
						NTCInfoQueue10_Cnt_M_str,
						&NTCQueueIndex10_Cnt_M_u08,
						DiagSts10_Cnt_M_b16,
						ActiveRmpRate10_UlspmS_M_f32,
						&ActDiagSts10_Cnt_M_u08);
}

/* Ap_10 stateless periodic core function */
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr10_Per( void )
{
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_DiagMgr10_Per_CP0_CheckpointReached();
	
	/* Invoke stateless Periodic Function with reference to appropriate application */
	DiagMgr_Per_Core( 	DiagMgr_NTCInfo10_Cnt_M_str, 
						DIAGMGR_EVENTNUM_10,
						DiagSts10_Cnt_M_b16,
						ActiveRmpRate10_UlspmS_M_f32,
						&ActDiagSts10_Cnt_M_u08,
						T_NTCMapTbl10_Cnt_enum,
						&ResetNTCFlag10_Cnt_M_u08);
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_DiagMgr10_Per_CP1_CheckpointReached();
}

/* Ap_10 stateless transition core function */
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr10_Trns( void )
{
	/* Invoke stateless Transition Function with reference to appropriate application */
	DiagMgr_Trns_Core( 	DiagMgr_NTCInfo10_Cnt_M_str, 
						DIAGMGR_EVENTNUM_10,
						T_NTCMapTbl10_Cnt_enum);
}

/* Ap_10 forwarding stateless proxy functions to stateless core function */
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr10_GetNTCFailed( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, P2VAR(boolean, AUTOMATIC, AUTOMATIC) NTCFailed_Ptr_T_lgc )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_GetNTCFailed_Core( NTC_Cnt_T_enum, NTCFailed_Ptr_T_lgc));
}

/* Ap_10 forwarding stateless proxy functions to stateless core function */
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr10_GetNTCActive( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, P2VAR(boolean, AUTOMATIC, AUTOMATIC) NTCActive_Ptr_T_lgc )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_GetNTCActive_Core( NTC_Cnt_T_enum, NTCActive_Ptr_T_lgc));
}

/* Ap_10 forwarding stateless proxy functions to stateless core function */
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr10_GetNTCStatus( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, P2VAR(uint8, AUTOMATIC, AUTOMATIC) Status_Ptr_T_u08 )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_GetNTCStatus_Core( NTC_Cnt_T_enum, Status_Ptr_T_u08));
}


FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr10_SetNTCStatus( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum )
{
	/* Forward request to stateless handler with reference to appropriate application data structures */
	return(NxtrDiagMgr_SetNTCStatus_Core( 	NTC_Cnt_T_enum,
											Param_Cnt_T_u08,
											Status_Cnt_T_enum,
											DiagMgr_NTCInfo10_Cnt_M_str,
											DiagSts10_Cnt_M_b16,
											ActiveRmpRate10_UlspmS_M_f32,
											&ActDiagSts10_Cnt_M_u08));
}
	
FUNC(Std_ReturnType, RTE_AP_DIAGMGR_APPL_CODE) NxtrDiagMgr10_ReportNTCStatus( VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum )
{
	VAR(Std_ReturnType, AUTOMATIC) RetVal;
	
	/* Forward request to stateless handler with reference to appropriate application data structures */
	SuspendAllInterrupts();
	if (FALSE == DiagMgrInitComp10_Cnt_M_lgc)
	{
		RetVal = NxtrDiagMgr_ReportNTCStatus_Core(	NTC_Cnt_T_enum,
													Param_Cnt_T_u08,
													Status_Cnt_T_enum,
													NTCInfoQueue10_Cnt_M_str,
													&NTCQueueIndex10_Cnt_M_u08);
		ResumeAllInterrupts();
	}
	else
	{
		ResumeAllInterrupts();
		RetVal = NxtrDiagMgr_SetNTCStatus_Core( NTC_Cnt_T_enum,
												Param_Cnt_T_u08,
												Status_Cnt_T_enum,
												DiagMgr_NTCInfo10_Cnt_M_str,
												DiagSts10_Cnt_M_b16,
												ActiveRmpRate10_UlspmS_M_f32,
												&ActDiagSts10_Cnt_M_u08);
	}
	
	return(RetVal);
}


