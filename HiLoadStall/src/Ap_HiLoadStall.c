/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_HiLoadStall.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/HiLoadStall-nzt9hv/HiLoadStall/autosar
 *     SW-C Type:  Ap_HiLoadStall
 *  Generated at:  Fri Sep 21 10:25:45 2012
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_HiLoadStall>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Tue Dec 20 11:13:50 2011
 * %version:          7 %
 * %date_modified:    Tue Jan 28 15:11:49 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 12/20/11    2      M. Story  Component design update for SF17 requirements
 * 01/07/12    3      M. story  Fixed Rte calls code did not match generated function names
 * 01/11/12    4      M. Story  Corrected LPF_SvUpdate_s16InFixKTrunc_m to be LPF_SvUpdate_u16InFixKTrunc_m
 * 01/27/12    5      LWW		Fixed problems found during review, QAC updates, slew limit logic changes,
 *                              Filter state variable correction, use of global constants, added legal range limit
 * 09/21/12	   6      Selva		Added checkpoint at the periodic fuctions	
 * 01/28/14	   7      KJS		Updated component to revision 4 of SF-17										CR11319
 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_HiLoadStall.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_HiLoadStall_Cfg.h"
#include "fixmath.h"
#include "interpolation.h"
#include "GlobalMacro.h"
#include "filters.h"
#include "CalConstants.h"

#define HILOADSTALL_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, AUTOMATIC) PrevAssistStallLimit_MtrNm_M_f32;
STATIC VAR(uint32, AUTOMATIC) ModPreLimitFiltSV_MtrNm_M_u8p24;
#define HILOADSTALL_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define HILOADSTALL_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(uint16, AUTOMATIC) ModPreLimit_MtrNm_D_u8p8;
STATIC volatile VAR(uint16, AUTOMATIC) FiltModPreLimit_MtrNm_D_u8p8;
STATIC volatile VAR(uint16, AUTOMATIC) StallLimit_MtrNm_D_u8p8;
#define HILOADSTALL_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
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
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_HILOADSTALL_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: HiLoadStall_Per1
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
 *   Boolean Rte_IRead_HiLoadStall_Per1_DftStallLimit_Cnt_lgc(void)
 *   Float Rte_IRead_HiLoadStall_Per1_MtrVelCRF_MtrRadpS_f32(void)
 *   Float Rte_IRead_HiLoadStall_Per1_PreLimitForStall_MtrNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_HiLoadStall_Per1_AssistStallLimit_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_HiLoadStall_Per1_AssistStallLimit_MtrNm_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_HILOADSTALL_APPL_CODE) HiLoadStall_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: HiLoadStall_Per1
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) MtrVelCRF_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) PreLimitForStall_MtrNm_T_f32;
	VAR(uint16, AUTOMATIC) PreLimitForStall_MtrNm_T_u8p8;
	VAR(uint16, AUTOMATIC) SatPreLimitForStall_MtrNm_T_u8p8;
	VAR(uint16, AUTOMATIC) ModPreLimit_MtrNm_T_u8p8;
	VAR(uint16, AUTOMATIC) FiltModPreLimit_MtrNm_T_u8p8;
	VAR(boolean, AUTOMATIC) DftStallLimit_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) AssistStallLimit_MtrNm_T_f32;
	VAR(uint16, AUTOMATIC) AssistStallLimit_MtrNm_T_u8p8;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_HiLoadStall_Per1_CP0_CheckpointReached();
	
	
	MtrVelCRF_MtrRadpS_T_f32 = Rte_IRead_HiLoadStall_Per1_MtrVelCRF_MtrRadpS_f32(); 
	PreLimitForStall_MtrNm_T_f32 = Rte_IRead_HiLoadStall_Per1_PreLimitForStall_MtrNm_f32(); 
	DftStallLimit_Cnt_T_lgc = Rte_IRead_HiLoadStall_Per1_DftStallLimit_Cnt_lgc();

	/* -- Apply saturation block limit on signal per SF -- */
	PreLimitForStall_MtrNm_T_u8p8 = FPM_FloatToFixed_m(PreLimitForStall_MtrNm_T_f32, u8p8_T);
	SatPreLimitForStall_MtrNm_T_u8p8 = Limit_m(PreLimitForStall_MtrNm_T_u8p8, 0U, t_EOTThrmDpntTbl_MtrNm_u8p8[0]);
	
	if (Abs_f32_m(MtrVelCRF_MtrRadpS_T_f32) <= k_AbsMtrVelBkt_MtrRadps_f32)
	{
		ModPreLimit_MtrNm_T_u8p8 = SatPreLimitForStall_MtrNm_T_u8p8;
	} 
	else
	{
		ModPreLimit_MtrNm_T_u8p8 = 0U;
	}
	
	ModPreLimit_MtrNm_D_u8p8 = ModPreLimit_MtrNm_T_u8p8;
	
	ModPreLimitFiltSV_MtrNm_M_u8p24 = LPF_SvUpdate_u16InFixKTrunc_m( ModPreLimit_MtrNm_T_u8p8, 
																	ModPreLimitFiltSV_MtrNm_M_u8p24, 
																	k_EOTThrmPrtLPFKn_Cnt_u16);
	
	FiltModPreLimit_MtrNm_T_u8p8 = (uint16)LPF_OpUpdate_u16InFixKTrunc_m(ModPreLimitFiltSV_MtrNm_M_u8p24);
	
	FiltModPreLimit_MtrNm_D_u8p8 = FiltModPreLimit_MtrNm_T_u8p8;

	AssistStallLimit_MtrNm_T_u8p8 = IntplVarXY_u16_u16Xu16Y_Cnt(t_EOTThrmIndptTbl_MtrNm_u8p8, 
														  t_EOTThrmDpntTbl_MtrNm_u8p8, 
														  TableSize_m(t_EOTThrmIndptTbl_MtrNm_u8p8), 
														  FiltModPreLimit_MtrNm_T_u8p8);

	StallLimit_MtrNm_D_u8p8 = AssistStallLimit_MtrNm_T_u8p8;

	AssistStallLimit_MtrNm_T_f32 = FPM_FixedToFloat_m(AssistStallLimit_MtrNm_T_u8p8, u8p8_T);

	PrevAssistStallLimit_MtrNm_M_f32 = Limit_m(	AssistStallLimit_MtrNm_T_f32, 
												(PrevAssistStallLimit_MtrNm_M_f32 - k_EOTThrmSlwLmtStp_MtrNm_f32),
												(PrevAssistStallLimit_MtrNm_M_f32 + k_EOTThrmSlwLmtStp_MtrNm_f32));

	if(TRUE == DftStallLimit_Cnt_T_lgc)
	{
		PrevAssistStallLimit_MtrNm_M_f32 = D_MTRTRQCMDHILMT_MTRNM_F32;
	}
	
	PrevAssistStallLimit_MtrNm_M_f32 = Limit_m(PrevAssistStallLimit_MtrNm_M_f32, D_ZERO_ULS_F32, D_MTRTRQCMDHILMT_MTRNM_F32);

	/* Update Output port values with newly computed values */
	Rte_IWrite_HiLoadStall_Per1_AssistStallLimit_MtrNm_f32(PrevAssistStallLimit_MtrNm_M_f32);
	
	/* Configurable End of Runnable Checkpoint */
    Rte_Call_HiLoadStall_Per1_CP1_CheckpointReached();


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_HILOADSTALL_APPL_CODE
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
