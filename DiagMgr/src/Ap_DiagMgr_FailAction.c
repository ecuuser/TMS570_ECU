/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_DiagMgr_FailAction.c
* Module Description: Portion of Diagnostic Manager that outputs NTC failure
* 					  action flags
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue Sep 18 12:08:34 2012
* %version:          2 %
* %derived_by:       czgng4 %
* %date_modified:    Mon Oct 22 12:28:40 2012 %
*---------------------------------------------------------------------------*/

#define DIAGMGR_C
#define DIAGMGR_FAILACTION_RTEHEADER
/*****************************************************************************
* Include files
*****************************************************************************/
#include "Std_Types.h"
#include "Ap_DiagMgr.h"
#include "CalConstants.h"
#include "GlobalMacro.h"

/*****************************************************************************
* Local Function Prototypes
*****************************************************************************/
STATIC INLINE FUNC(boolean, AP_DIAGMGR_CODE) ReadBit_u16(	VAR(uint16, AUTOMATIC) Data,
															VAR(uint16, AUTOMATIC) BitMask);

/*****************************************************************************
* Global Function Definitions
*****************************************************************************/

/**********************************************************************************************************************
 *
 * Function: 	DiagMgr_Per1
 * Description: This function consolidates all of the diagnostic status and ramp rates from every
 *              application into a single set of fault response outputs that other components
 *              can use to take appropriate failure actions
 * Triggered: 	Periodic in all states
 * Inputs: 		None
 * Outputs: 	Rte_Write_DiagStsNonRecRmpToZeroFltPres_Cnt_lgc()
 * 				Rte_Write_DiagStsCtrldDisRmpPres_Cnt_lgc()
 * 				Rte_Write_DiagStsRecRmpToZeroFltPres_Cnt_lgc()
 * 				Rte_Write_DiagStsHWASbSystmFltPres_Cnt_lgc()
 * 				Rte_Write_DiagStsDefVehSpd_Cnt_lgc()
 * 				Rte_Write_DiagStsDefTemp_Cnt_lgc()
 * 				Rte_Write_DiagStsScomHWANotValid_Cnt_lgc()
 * 				Rte_Write_DiagStsWIRDisable_Cnt_lgc()
 * 				Rte_Write_DiagRampRate_XpmS_f32()
 * 				Rte_Write_DiagRampValue_Uls_f32()
 * 				Rte_Write_DiagRmpToZeroActive_Cnt_lgc()
 *
 **********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGMGR_APPL_CODE) DiagMgr_Per1(void)
{
	VAR(float32, AUTOMATIC) DiagMgrRmpRate_UlspmS_T_f32;
	VAR(uint16, AUTOMATIC) DiagMgrDiagSts_Cnt_T_b16;
	VAR(uint16, AUTOMATIC) AppDiagSts_Cnt_T_b16;
	VAR(float32, AUTOMATIC) AppRmpRate_UlspmS_T_f32;
	VAR(boolean, AUTOMATIC) DiagStsNonRecRmpToZeroFltPres_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) DiagStsRecRmpToZeroFltPres_Cnt_T_lgc;
	VAR(uint8, AUTOMATIC) i;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_DiagMgr_Per1_CP0_CheckpointReached();

	DiagMgrRmpRate_UlspmS_T_f32 = 0.0F;
	DiagMgrDiagSts_Cnt_T_b16 = 0U;

	for (i = 0; i < DIAGMGR_NUMAPPS; i++)
	{
		AppDiagSts_Cnt_T_b16 = (T_DiagMgrDiagSts_Ptr_b16[i])[0] | (T_DiagMgrDiagSts_Ptr_b16[i])[1];
		AppRmpRate_UlspmS_T_f32 = Max_m((T_DiagMgrRmpRate_Ptr_f32[i])[0], (T_DiagMgrRmpRate_Ptr_f32[i])[1]);
		DiagMgrRmpRate_UlspmS_T_f32 = Max_m(DiagMgrRmpRate_UlspmS_T_f32, AppRmpRate_UlspmS_T_f32);
		DiagMgrDiagSts_Cnt_T_b16 |= AppDiagSts_Cnt_T_b16;
	}

	DiagStsNonRecRmpToZeroFltPres_Cnt_T_lgc = ReadBit_u16(DiagMgrDiagSts_Cnt_T_b16, D_DIAGSTSNONRECRMPTOZEROBIT_CNT_B16);
	DiagStsRecRmpToZeroFltPres_Cnt_T_lgc = ReadBit_u16(DiagMgrDiagSts_Cnt_T_b16, D_DIAGSTSRECRMPTOZEROBIT_CNT_B16);

	Rte_Write_DiagStsNonRecRmpToZeroFltPres_Cnt_lgc(DiagStsNonRecRmpToZeroFltPres_Cnt_T_lgc);
	Rte_Write_DiagStsCtrldDisRmpPres_Cnt_lgc(ReadBit_u16(DiagMgrDiagSts_Cnt_T_b16, D_DIAGSTSCTRLDDISRMPBIT_CNT_B16));
	Rte_Write_DiagStsRecRmpToZeroFltPres_Cnt_lgc(DiagStsRecRmpToZeroFltPres_Cnt_T_lgc);
	Rte_Write_DiagStsHWASbSystmFltPres_Cnt_lgc(ReadBit_u16(DiagMgrDiagSts_Cnt_T_b16, D_DIAGSTSHWASBSYSTMFLTBIT_CNT_B16));
	Rte_Write_DiagStsDefVehSpd_Cnt_lgc(ReadBit_u16(DiagMgrDiagSts_Cnt_T_b16, D_DIAGSTSDEFVEHSPDBIT_CNT_B16));
	Rte_Write_DiagStsDefTemp_Cnt_lgc(ReadBit_u16(DiagMgrDiagSts_Cnt_T_b16, D_DIAGSTSDEFTEMPBIT_CNT_B16));
	Rte_Write_DiagStsScomHWANotValid_Cnt_lgc(ReadBit_u16(DiagMgrDiagSts_Cnt_T_b16, D_DIAGSTSSCOMHWANOTVALIDBIT_CNT_B16));
	Rte_Write_DiagStsWIRDisable_Cnt_lgc(ReadBit_u16(DiagMgrDiagSts_Cnt_T_b16, D_DIAGSTSWIRDISABLEBIT_CNT_B16));

	Rte_Write_DiagRampRate_XpmS_f32(DiagMgrRmpRate_UlspmS_T_f32);

	if ((TRUE == DiagStsNonRecRmpToZeroFltPres_Cnt_T_lgc) || (TRUE == DiagStsRecRmpToZeroFltPres_Cnt_T_lgc))
	{
		Rte_Write_DiagRampValue_Uls_f32(0.0F);
		Rte_Write_DiagRmpToZeroActive_Cnt_lgc(TRUE);
	}
	else
	{
		Rte_Write_DiagRampValue_Uls_f32(1.0F);
		Rte_Write_DiagRmpToZeroActive_Cnt_lgc(FALSE);
	}

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_DiagMgr_Per1_CP1_CheckpointReached();
}

/*****************************************************************************
* Local Function Definitions
*****************************************************************************/

/**********************************************************************************************************************
 * Function: 	ReadBit_u16
 * Description: This function will return TRUE if any bits are set based on the passed BitMask for a uint16 datatype
 * Inputs: 		None
 * Outputs: 	None
 **********************************************************************************************************************/
STATIC INLINE FUNC(boolean, AP_DIAGMGR_CODE) ReadBit_u16(	VAR(uint16, AUTOMATIC) Data,
															VAR(uint16, AUTOMATIC) BitMask)
{
	return (boolean)(((Data & BitMask) == 0)?FALSE:TRUE);
}

/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
09/18/2012	1	    LWW       Initial Version
10/22/2012	2	    LWW       Removed header with checkpoint generation updates
******************************************************************************/
