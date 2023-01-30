
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : StaMd_Proxy.c
* Module Description: StaMd Proxy Interface
* Product           : Gen II Plus - EA3.0
* Generator         : artt 2.0.2.0
* Generation Time   : 13.01.2014 15:10:06
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 13 18:34:17 2012
 * %version:          1 %
 * %date_modified:    Tue Jul 23 12:28:16 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 10/11/12   1       LWW       Initial template creation
 * 10/24/12   2       LWW       Added exclude configuration for applications to skip generation
 * 10/24/12   3       LWW       Fixed header generation logic
 * 05/30/13   4       KJS       Added support for StaMd and DiagMgr interfacing.
 * 06/05/13   5       KJS       Added support for P/N step to set SysC faults for StaMd
 */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#define STAMD_C /* Enable visibility to Module internal definitions in StaMd.h*/
#include "Ap_StaMd_Cfg.h"
 
	
	
	
#include "Rte_Ap_StaMd8.h"
#undef RTE_APPLICATION_HEADER_FILE
	
	
#include "Rte_Ap_StaMd9.h"
#undef RTE_APPLICATION_HEADER_FILE

#define SetBits_m(var, mask)    ((var) = (var) | (mask))
#define ClrBits_m(var, mask)    ((var) = (var) & (mask))
/*******************************************************************************
**                      Proxy Functions                                       **
*******************************************************************************/
	
	
	
/* Ap_8 periodic function */
FUNC(void, RTE_AP_STAMD_APPL_CODE) StaMd8_Per1( void )
{
	
	VAR(boolean, AUTOMATIC) FTermActive_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) CTermActive_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) ATermActive_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) RampStatusCmp_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) CtrldDmpStsCmp_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) TMFTestComplete_Cnt_T_lgc;
	VAR(NxtrDiagMgrStatus, AUTOMATIC) FaultStatus_Cnt_T_enum;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_StaMd8_Per1_CP0_CheckpointReached();
	
	FTermActive_Cnt_T_lgc = Rte_IRead_StaMd8_Per1_FTerm_Cnt_lgc();
	CTermActive_Cnt_T_lgc = Rte_IRead_StaMd8_Per1_CTerm_Cnt_lgc();
	ATermActive_Cnt_T_lgc = Rte_IRead_StaMd8_Per1_ATerm_Cnt_lgc();
	RampStatusCmp_Cnt_T_lgc = Rte_IRead_StaMd8_Per1_RampStatusComplete_Cnt_lgc();
	CtrldDmpStsCmp_Cnt_T_lgc = Rte_IRead_StaMd8_Per1_ControlledDampStatusComplete_Cnt_lgc();
	TMFTestComplete_Cnt_T_lgc = Rte_IRead_StaMd8_Per1_TMFTestComplete_Cnt_lgc();
	
	FaultStatus_Cnt_T_enum = SystemStateCheck(	FTermActive_Cnt_T_lgc,
												CTermActive_Cnt_T_lgc,
												ATermActive_Cnt_T_lgc,
												RampStatusCmp_Cnt_T_lgc,
												CtrldDmpStsCmp_Cnt_T_lgc,
												TMFTestComplete_Cnt_T_lgc,
												&StaMdsSysCFltCntr_Cnt_M_u16);
						
	Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_StaMdsSysC, 1U, FaultStatus_Cnt_T_enum);
	
	SystemState8_Cnt_M_enum = Rte_Mode_SystemState8_Mode();
	
	if ((SystemState_Cnt_M_enum != SystemState8_Cnt_M_enum) && (SystemState8_Cnt_M_enum != RTE_TRANSITION_StaMd_Mode))
	{
		Rte_Switch_Ap_StaMd8_SystemState8_Mode(SystemState_Cnt_M_enum);
	}
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_StaMd8_Per1_CP1_CheckpointReached();
}

FUNC(void, RTE_AP_STAMD_APPL_CODE) MilestoneRqst8_WarmInitMilestoneComplete(StaMd_Users user)
{
	VAR(uint32, AUTOMATIC) MilestoneRqst_Cnt_T_u32;

	Rte_Enter_StaMds8_MilestoneRqst_WARMINIT_ExclArea();
	
	MilestoneRqst_Cnt_T_u32 = WarmInitMilestoneRqst8_Cnt_M_u32;
	ClrBits_m(MilestoneRqst_Cnt_T_u32, (~(1U << user)));
	WarmInitMilestoneRqst8_Cnt_M_u32 = MilestoneRqst_Cnt_T_u32;
	
	Rte_Exit_StaMds8_MilestoneRqst_WARMINIT_ExclArea();
}

FUNC(void, RTE_AP_STAMD_APPL_CODE) MilestoneRqst8_WarmInitMilestoneNotComplete(StaMd_Users user)
{
	VAR(uint32, AUTOMATIC) MilestoneRqst_Cnt_T_u32;

	Rte_Enter_StaMds8_MilestoneRqst_WARMINIT_ExclArea();
	
	MilestoneRqst_Cnt_T_u32 = WarmInitMilestoneRqst8_Cnt_M_u32;
	SetBits_m(MilestoneRqst_Cnt_T_u32, (1U << user));
	WarmInitMilestoneRqst8_Cnt_M_u32 = MilestoneRqst_Cnt_T_u32;
	
	Rte_Exit_StaMds8_MilestoneRqst_WARMINIT_ExclArea();
}


	
	
/* Ap_9 periodic function */
FUNC(void, RTE_AP_STAMD_APPL_CODE) StaMd9_Per1( void )
{

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_StaMd9_Per1_CP0_CheckpointReached();
	
	SystemState9_Cnt_M_enum = Rte_Mode_SystemState9_Mode();
	
	if ((SystemState_Cnt_M_enum != SystemState9_Cnt_M_enum) && (SystemState9_Cnt_M_enum != RTE_TRANSITION_StaMd_Mode))
	{
		Rte_Switch_Ap_StaMd9_SystemState9_Mode(SystemState_Cnt_M_enum);
	}
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_StaMd9_Per1_CP1_CheckpointReached();
}

FUNC(void, RTE_AP_STAMD_APPL_CODE) MilestoneRqst9_WarmInitMilestoneComplete(StaMd_Users user)
{
	VAR(uint32, AUTOMATIC) MilestoneRqst_Cnt_T_u32;

	Rte_Enter_StaMds9_MilestoneRqst_WARMINIT_ExclArea();
	
	MilestoneRqst_Cnt_T_u32 = WarmInitMilestoneRqst9_Cnt_M_u32;
	ClrBits_m(MilestoneRqst_Cnt_T_u32, (~(1U << user)));
	WarmInitMilestoneRqst9_Cnt_M_u32 = MilestoneRqst_Cnt_T_u32;
	
	Rte_Exit_StaMds9_MilestoneRqst_WARMINIT_ExclArea();
}

FUNC(void, RTE_AP_STAMD_APPL_CODE) MilestoneRqst9_WarmInitMilestoneNotComplete(StaMd_Users user)
{
	VAR(uint32, AUTOMATIC) MilestoneRqst_Cnt_T_u32;

	Rte_Enter_StaMds9_MilestoneRqst_WARMINIT_ExclArea();
	
	MilestoneRqst_Cnt_T_u32 = WarmInitMilestoneRqst9_Cnt_M_u32;
	SetBits_m(MilestoneRqst_Cnt_T_u32, (1U << user));
	WarmInitMilestoneRqst9_Cnt_M_u32 = MilestoneRqst_Cnt_T_u32;
	
	Rte_Exit_StaMds9_MilestoneRqst_WARMINIT_ExclArea();
}

FUNC(void, RTE_AP_STAMD_APPL_CODE) StaMd9_Trns_DemShutdown(void)
{
	Rte_Call_DiagMgr_StaCtrl_Shutdown();
}



