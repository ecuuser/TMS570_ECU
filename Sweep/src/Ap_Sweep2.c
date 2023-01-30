/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_Sweep2.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/Sweep-nzt9hv/Sweep/autosar
 *     SW-C Type:  Ap_Sweep2
 *  Generated at:  Mon Jan 14 11:24:25 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_Sweep2>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Oct 8 10:28:32 2012
 * %version:          2 %
 * %derived_by:       nzt9hv %
 * %date_modified:    Mon Jan 14 10:53:33 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 1/8/12   1        Selva   Initial component creation                                                   6480
 * 1/14/12  2        Selva    Corrected for sweep2 periodic  6480   
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_Sweep2.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_Sweep2_Cfg.h"
#include "Ap_Sweep.h"
#include  "fixmath.h"
#include "GlobalMacro.h"

#define D_SWEEPMTRTRQ_CNT_U16		1U


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
 * Boolean: Boolean (standard type)
 * Float: Real in interval ]-FLT_MAX...FLT_MAX[ with single precision (standard type)
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
 * Boolean: D_FALSE_CNT_LGC = FALSE
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_SWEEP2_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Sweep2_Per1
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
 *   Float Rte_IRead_Sweep2_Per1_InputMtrTrq_MtrNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_Sweep2_Per1_OutputMtrTrq_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_Sweep2_Per1_OutputMtrTrq_MtrNm_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_SWEEP2_APPL_CODE) Sweep2_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Sweep2_Per1
 *********************************************************************************************************************/
#ifdef SWEEPBUILD

	VAR(float32, AUTOMATIC) InputMtrTrq_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) OutputMtrTrq_MtrNm_T_f32;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_Sweep2_Per1_CP0_CheckpointReached();

	InputMtrTrq_MtrNm_T_f32 = Rte_IRead_Sweep2_Per1_InputMtrTrq_MtrNm_f32();

	if ((TRUE == SweepModeEn_Cnt_M_lgc) && (D_SWEEPMTRTRQ_CNT_U16 == SweepConfig_Cnt_M_u16))
    {
    	OutputMtrTrq_MtrNm_T_f32 = SweepTorque_HwNm_M_f32 * FPM_FixedToFloat_m(SweepGain_MtrNmpHwNm_M_u1p15, u1p15_T);
    	OutputMtrTrq_MtrNm_T_f32 = (float32)((sint32)((OutputMtrTrq_MtrNm_T_f32 / MtrTrqQuantization_Uls_M_f32)+ ((float32)Sign_f32_m(OutputMtrTrq_MtrNm_T_f32) * 0.5F))) * MtrTrqQuantization_Uls_M_f32;
    }
	else
	{
		OutputMtrTrq_MtrNm_T_f32 = InputMtrTrq_MtrNm_T_f32;
	}
	Rte_IWrite_Sweep2_Per1_OutputMtrTrq_MtrNm_f32(OutputMtrTrq_MtrNm_T_f32);

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_Sweep2_Per1_CP1_CheckpointReached();

#else
	
	VAR(float32, AUTOMATIC) OutputMtrTrq_MtrNm_T_f32;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_Sweep2_Per1_CP0_CheckpointReached();

	OutputMtrTrq_MtrNm_T_f32 = Rte_IRead_Sweep2_Per1_InputMtrTrq_MtrNm_f32();
	Rte_IWrite_Sweep2_Per1_OutputMtrTrq_MtrNm_f32(OutputMtrTrq_MtrNm_T_f32);
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_Sweep2_Per1_CP1_CheckpointReached();

#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_SWEEP2_APPL_CODE
#include "MemMap.h"


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
