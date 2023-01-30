/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EcuStartup.c
* Module Description: AUTOSAR Startup Sequence
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************************/
/****************************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EcuStartup.c
* Module Description: AUTOSAR Startup Sequence
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************************/
/****************************************************************************************
* Version Control:
* Date Created:      Wed Jan  9 10:00:00 2014
* %version:          3 %
* %derived_by:       jzh87w %
* %date_modified:    Fri Jan 24 16:24:38 2014 %
*****************************************************************************************/
/****************************************************************************************
* Change History:
* Date      Rev      Author    Change Description								SCR #
* --------  -------  --------  ----------------------------------------------------------
* 02/27/15   2		 SAH       Added FEE suspend and resume calls.
* 07/16/15   3       SAH       Added uDiagPeriphMPU_Init         				
* 07/16/15   4       PS        Updated to latest Fiasa SIP (CBD1300649)	       CR#13482
****************************************************************************************/


/****************************************************************************************
* Include files
****************************************************************************************/

#include "T1_AppInterface.h"
#include "Os.h"
#include "EcuM.h"

#include "Nhet.h"
#include "Ap_DfltConfigData.h"
#include "Interrupts.h"
#include "SystemTime.h"
#include "FlsTst.h"
#include "Lnk_Symbols.h"
#include "CDD_Func.h"
#include "ePWM.h"
#include "Gpt.h"
#include "Port.h"
#include "Fee.h"
#include "ApplCallbacks.h"
#include "Can.h"
#include "CanIf.h"
#include "Com.h"
#include "ComM.h"
#include "PduR.h"
#include "Dcm.h"
#include "CanSM_EcuM.h"
#include "CanTp.h"
#include "XcpProf.h"
#include "CanXcp.h"
#include "Cd_FeeIf.h"
#include "SpiNxt.h"
#include "Ap_ApXcp.h"
#include "NtWrap.h"
#include "uDiag.h"
#include "Dma.h"
#include "Nm.h"
#include "CanNm.h"


/*******************************************************************************
  * Name:        main
  * Description: 
  * Inputs:      None 
  * Outputs:     None
  *
*******************************************************************************/
int main(void)
{
	T1_AppInit();
	osInitialize();
	EcuM_Init();
}


/*******************************************************************************
  * Name:        EcuStartup_Init1
  * Description: Initialization executed prior to OS start  
  * Inputs:      None 
  * Outputs:     None
  *
*******************************************************************************/
void EcuStartup_Init1(void) 
{
	Det_Init();
	ComM_InitMemory();
	Com_InitMemory();
	Dma_Init();
	FlsTst_Init(&FlsTst_Runtime);
	uDiagCCRM_Init();
	uDiagClockMonitor_Init();
	uDiagECC_Init();
	uDiagESM_Init();
	uDiagIOMM_Init();
	uDiagParity_Init();
	uDiagPeriphMPU_Init();
	uDiagStaticRegs_Init();
	uDiagVIM_Init();
	Nhet_Init1();
	ePWM_Init1();
	SpiNxt_Init();
	Dma_SetupMtrCtrlGroups();
}


/*******************************************************************************
  * Name:        EcuStartup_Init2
  * Description: Initialization executed after OS start, prior to RTE start
  * Inputs:      None 
  * Outputs:     None
  *
*******************************************************************************/
void EcuStartup_Init2(void)
{
	ApXcp_Init();
	Dem_PreInit();
	Gpt_Init(&Gpt_Runtime);
	SystemTime_Init();
	TWrapC_Adc_Init(NULL_PTR);
	TWrapC_Adc2_Init1();
	TWrapC_PwmCdd_Init();
	Gpt_EnableNotification(SystemTime_uS);
	EnableCRCInterrupt();
	TWrapC_FeeIf_Init();
	Port_Init(&Port_Runtime);
	NvM_Init();
	TWrapC_TI_Fee_SuspendResumeErase(Suspend_Erase);
	NvM_ReadAll();
	Appl_WaitNvMReady(0, TRUE);
	TWrapC_TI_Fee_SuspendResumeErase(Resume_Erase);
	TWrapC_StaMd_Init0();
	DfltConfigData_Init1();
	TWrapC_NvMProxy_Init();
    EnableOverVoltThreshInterrupt();
	Dem_Init();
	Can_Init(&CanConfigSet);
	CanIf_Init(&CanIf_Config);
	CanSM_Init();
	CanNm_Init(&CanNm_Configuration0);	
	Nm_Init(NULL_PTR);	
	CanTp_Init();
	Com_Init(&ComConfig);
	ComM_Init(&ComMConfig);
	XcpInit();
	CanXcp_Init(NULL_PTR);
	PduR_InitMemory();
	PduR_Init(&PduRGlobalConfig);
	Dcm_Init();
	EnableCanInterrupt();
}

