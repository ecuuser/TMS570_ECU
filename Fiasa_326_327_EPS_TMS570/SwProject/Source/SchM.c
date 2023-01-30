/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : SchM.c
* Module Description: AUTOSAR BSW Scheduler
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*******************************************************************************
* Version Control:
* Date Created:      Wed Jul 17 12:00:00 2013
* %version:          11 %
* %derived_by:       nzx5jd %
* %date_modified:    Fri Feb 21 14:21:36 2014 %
*******************************************************************************/
/*******************************************************************************
* Change History:
* Date      Rev      Author    Change Description
* --------  -------  --------  ------------------------------------------------
* 07/17/13   1       SAH        Initial Haitec version
* 07/16/15   2       PS         Updated XCP timing Loop to improve mfg cycle time	  
* 03/16/16   3       PS         Changed the task name Task_SchM_2ms_9 to Task_SchM_10ms_9      								   	   
*******************************************************************************/


#include "Std_Types.h"
#include "Os.h"
#include "Interrupts.h"

#include "Can.h"
#include "CanSM_SchM.h"
#include "CanTp.h"
#include "Cd_NvMProxy.h"
#include "Com.h"
#include "ComM.h"
#include "Dcm.h"
#include "Dem.h"
#include "EcuM.h"
#include "EPS_DiagSrvcs_ISO.h"
#include "fee.h"
#include "FlsTst.h"
#include "T1_AppInterface.h"
#include "NtWrap.h"
#include "NvM.h"
#include "Rte_Ap_StaMd9.h"
#include "Wdg_TMS570LS3x_Lcfg.h"
#include "WdgM.h"
#include "WdgM_PBcfg.h"
#include "CanNm.h"

#pragma SET_DATA_SECTION(".ossDataAp_9:init")
STATIC VAR(uint8, AUTOMATIC) SchM2msCounter_Cnt_M_u08;
#pragma SET_DATA_SECTION()

TASK(Task_SchM_100ms_0)
{
	Fee_MainFunction();
	TerminateTask();
}


TASK(Task_SchM_100ms_9)
{
	NvMProxy_MainFunction();
	NvM_MainFunction();
	TerminateTask();
}


TASK(Task_SchM_10ms_9)
{
	if( SchM2msCounter_Cnt_M_u08 == 0u )
	{
		T1_AppHandler();
		Com_MainFunctionTx();
		EcuM_MainFunction();
	}
	
	Can_MainFunction_Read();
	
	if( SchM2msCounter_Cnt_M_u08 == 0u )
	{
		CanSM_MainFunction();
		CanTp_MainFunction();
		CanNm_MainFunction_0();
		Com_MainFunctionRx();
		ComM_MainFunction_0();
		Dem_MainFunction();
		Dcm_MainFunction();
		EPSDiagSrvcs_Task();
	}
	
	if( SchM2msCounter_Cnt_M_u08 >= 4u )
	{
		SchM2msCounter_Cnt_M_u08 = 0u;
	}
	else
	{
		SchM2msCounter_Cnt_M_u08++;
	}
	
	TerminateTask();
}


TASK(Task_SchM_4ms_0)
{
	WdgM_MainFunction();
	FlsTst_MainFunction();
	TerminateTask();
}


TASK(Task_SchM_Trns_9)
{
	StaMd9_Trns_DemShutdown();
	TerminateTask();
}


TASK(Task_SchM_Init_9)
{
	GetResource(RES_SCHEDULER);
	EcuM_StartupTwo();
	TWrapC_Wdg_TMS570LS3x_Init(&wdg_tms570ls3x_config);
	TWrapC_WdgM_Init(&WdgMConfig_Mode0);
	ReleaseResource(RES_SCHEDULER);
	ClearSysTickInterruptFlg();
	EnableSysTickInterrupt();
	TerminateTask();
}


TASK(Task_Bkgnd)
{
	while( TRUE )
	{
		T1_AppBgHandler();
	}
}

