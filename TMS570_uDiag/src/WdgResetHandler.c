/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : WdgResetHandler.c
* Module Description: Determines specific type of watchdog failure
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Fri Jun 29 10:22:39 2012
* %version:          1 %
* %derived_by:       czgng4 %
* %date_modified:    Thu Nov 29 15:27:16 2012 % 
*---------------------------------------------------------------------------*/

/*****************************************************************************
* Include files
*****************************************************************************/
#define UDIAG_C
#include "Std_Types.h"
#include "ResetCause.h"
#include "uDiag.h"

#if (STD_OFF == BC_WDGM_NONE)
	#include "rti_regs.h"
	#include "WdgM.h"
#endif

#if (STD_ON == BC_WDGM_TTTECH_V2_0_3)

	#define WDGRESETHANDLER_START_SEC_VAR_POWER_ON_CLEARED_8
	#include "MemMap.h" /* PRQA S 5087 */
	STATIC volatile VAR(uint8, CD_WDGRESETHANDLER_VAR_NOINIT) FailedSupervisedEntityID_Cnt_D_u08;
	#define WDGRESETHANDLER_STOP_SEC_VAR_POWER_ON_CLEARED_8
	#include "MemMap.h" /* PRQA S 5087 */

	extern P2CONST (WdgM_ConfigType, AUTOMATIC, WDGM_APPL_CONST) g_wdgm_cfg_ptr; /* PRQA S 3447 */

#endif
/*****************************************************************************
* Global Functions
*****************************************************************************/
FUNC(void, WDGRESETHANDLER_CODE) WdgResetHandler(void)
{

#if (STD_ON == BC_WDGM_TTTECH_V2_0_3)

	uint8 SupervisedEntityID_Cnt_T_u08;

	FailedSupervisedEntityID_Cnt_D_u08 = 0xFF;

	/* Check for reset due to bad key write.  If not, the hardware WWD failed and ResetCause_Cnt_Enum remains WDGFAIL */
	if (4U == (rtiREG1->WDSTATUS & 4U))
	{
		for (SupervisedEntityID_Cnt_T_u08 = 0U; ((SupervisedEntityID_Cnt_T_u08 < D_NUMOFSUPERVISEDENTITIES_CNT_U08) && (0xFF == FailedSupervisedEntityID_Cnt_D_u08)); SupervisedEntityID_Cnt_T_u08++)
		{
			if (0U != g_wdgm_cfg_ptr->WdgMSupervisedEntityRef[SupervisedEntityID_Cnt_T_u08].EntityStatusGRef->ProgramFlowViolationCnt)
			{
				ResetCause_Cnt_Enum = WDGPROGFLOWFAIL;
				FailedSupervisedEntityID_Cnt_D_u08 = SupervisedEntityID_Cnt_T_u08;
			}
			else if (0U != g_wdgm_cfg_ptr->WdgMSupervisedEntityRef[SupervisedEntityID_Cnt_T_u08].EntityStatusGRef->DeadlineViolationCnt)
			{
				ResetCause_Cnt_Enum = WDGDEADLINEFAIL;
				FailedSupervisedEntityID_Cnt_D_u08 = SupervisedEntityID_Cnt_T_u08;
			}
			else if (0U != g_wdgm_cfg_ptr->WdgMSupervisedEntityRef[SupervisedEntityID_Cnt_T_u08].EntityStatusGRef->FailedSupervisionRefCycles)
			{
				ResetCause_Cnt_Enum = WDGALIVEMONFAIL;
				FailedSupervisedEntityID_Cnt_D_u08 = SupervisedEntityID_Cnt_T_u08;
			}
			else
			{
				/* Do Nothing */
			}
		}

		/* If not program flow, deadline, or alive failure, must be the software window violation */
		if (FailedSupervisedEntityID_Cnt_D_u08 == 0xFF)
		{
			ResetCause_Cnt_Enum = SWWDGFAIL;
		}
	}
#endif

}
/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
                                    (MDD Rev & Date)
-------   -------  --------  -----------------------------------  ----------
11/29/12   1        LWW      Initial file creation
******************************************************************************/
