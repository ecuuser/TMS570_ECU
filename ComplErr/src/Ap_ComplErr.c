/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_ComplErr.c
 *     Workspace:  C:/Synergy_projects/ComplErr-lz4p8n/ComplErr/autosar
 *     SW-C Type:  Ap_ComplErr
 *  Generated at:  Thu Aug 22 13:45:03 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_ComplErr>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/*-----------------------------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu Aug 22 13:14:03 2013
* %version:          8 %
* %derived_by:       lz4p8n %
* %date_modified:    Thu Aug 22 13:14:03 2013
**************************************************************************************************
CHANGE HISTORY:

 Date      Rev      Author          Change Description               				SCR #
                                     (MDD Rev & Date)
-------   -------  --------  -----------------------------------   					----------
* 8/22/13 1.0 	   SP      	 Initial Creation                     					9608

*************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_ComplErr.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_ComplErr_Cfg.h"
#include "CalConstants.h"
#include "GlobalMacro.h"
#include "interpolation.h"
#include "fixmath.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Used AUTOSAR Data Types
 *
 **********************************************************************************************************************
 *
 * Primitive Types:
 * ================
 * Float: Real in interval ]-FLT_MAX...FLT_MAX[ with single precision (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Defined Constants
 *
 **********************************************************************************************************************
 *
 * Primitive Type Constants:
 * =========================
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_COMPLERR_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ComplErr_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_ComplErr_Per1_TorqueCmdCRF_MtrNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_ComplErr_Per1_ComplErr_HwDeg_f32(Float data)
 *   Float *Rte_IWriteRef_ComplErr_Per1_ComplErr_HwDeg_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_COMPLERR_APPL_CODE) ComplErr_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ComplErr_Per1
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) TrqCmdcrf_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) ComplErr_HwDeg_T_f32;
	VAR(sint16,  AUTOMATIC) TrqCmd_MtrNm_T_s4p11;
	VAR(sint32,  AUTOMATIC) ComplErr_HwDeg_T_s12p19;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_ComplErr_Per1_CP0_CheckpointReached();
	TrqCmdcrf_MtrNm_T_f32 = Rte_IRead_ComplErr_Per1_TorqueCmdCRF_MtrNm_f32();
	TrqCmd_MtrNm_T_s4p11 = FPM_FloatToFixed_m(TrqCmdcrf_MtrNm_T_f32, s4p11_T);
	ComplErr_HwDeg_T_s12p19 = TrqCmd_MtrNm_T_s4p11 * IntplVarXY_u16_u16Xu16Y_Cnt(t_ComplErrMtrPosNonLinComplIndTbl_MtrNm_u5p11,
																				 t_CompErrMtrPosNonLinComplDepTbl_HwDegpMtrNm_u8p8,
																				 TableSize_m(t_ComplErrMtrPosNonLinComplIndTbl_MtrNm_u5p11), 
																				 Abs_s16_m(TrqCmd_MtrNm_T_s4p11));

	ComplErr_HwDeg_T_f32 = FPM_FixedToFloat_m(ComplErr_HwDeg_T_s12p19, s12p19_T);
	Rte_IWrite_ComplErr_Per1_ComplErr_HwDeg_f32(ComplErr_HwDeg_T_f32);

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_ComplErr_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_COMPLERR_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
