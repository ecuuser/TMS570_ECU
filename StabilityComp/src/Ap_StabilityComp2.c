/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_StabilityComp2.c
 *     Workspace:  C:/CMSynergy_Projects/CBD/StabilityComp/autosar
 *     SW-C Type:  Ap_StabilityComp2
 *  Generated at:  Tue Apr 30 14:02:13 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_StabilityComp2>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Fri Feb 22 15:35:09 2013 %
 * %version:          6 %
 * %derived_by:       bz1q07 %
 * %date_modified:    Thu Dec  5 13:42:57 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 02/22/13   1		  SP		Updated to SF-29 v006 
 * 04/13/13	  2		  SP		Included fixmath.h
 * 04/27/13	  5		  LWW		Anomaly 4886 correction
 * 12/06/13   6       VT        Anomaly 5573 fix                                                               10980
*/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_StabilityComp2.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "filters.h"
#include "CalConstants.h"
#include "GlobalMacro.h"
#include "interpolation.h"
#include "Ap_StabilityComp2_Cfg.h"
#include "fixmath.h"

#define D_COMPINLIMIT_MTRNM_F32   10.275F
#define D_NUMNOTCHFILT_CNT_U08    (TableSize_m(t_StCmpNFK_Str))
#define D_NUMNFBLENDS_CNT_U08     4U
#define D_ASSISTINIT_MTRNM_F32    0.0F
#define D_COMPBLND12IDX_CNT_U08   0U
#define D_COMPBLND34IDX_CNT_U08   1U
#define D_COMPBLND02IDX_CNT_U08   2U
#define D_COMPBLND04IDX_CNT_U08   3U
#define D_ASSTSCLMT_MTRNM_F32     8.8F

#define STABILITYCOMP2_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
STATIC volatile VAR(float32, AUTOMATIC) StCmp1Out2_MtrNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) StCmp2Out2_MtrNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) StCmp3Out2_MtrNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) StCmp4Out2_MtrNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) HwTorqueSV_HwNm_M_f32;
STATIC volatile VAR(float32, AUTOMATIC) VehicleSpeedSV_Kph_M_f32;
STATIC volatile VAR(float32, AUTOMATIC) AssistDDFactorSV_Uls_M_f32;
#define STABILITYCOMP2_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define STABILITYCOMP2_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(NotchFiltSV_Str, AUTOMATIC) CombAstNFSV2_Cnt_M_Str[D_NUMNOTCHFILT_CNT_U08];
STATIC VAR(LPF32KSV_Str, AUTOMATIC) HwTrqSV2_HwNm_M_Str;
#define STABILITYCOMP2_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

STATIC FUNC(sint16, RTE_AP_STABILITYCOMP_APPL_CODE) ApplyStabilityComp2(VAR(float32, AUTOMATIC) Assist_MtrNm_T_f32,
																 P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) FiltSVPtr_Uls_T_Str, 
																 P2CONST(uint16, AUTOMATIC, AUTOMATIC) CompBlnd_Uls_T_u2p14, 
																 VAR(uint16, AUTOMATIC) ADDFBlend_Uls_T_u2p14,
																 VAR(boolean, AUTOMATIC) WriteDisplayVars_Cnt_T_lgc);

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
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_STABILITYCOMP2_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StabilityComp2_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_STABILITYCOMP2_APPL_CODE) StabilityComp2_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: StabilityComp2_Init1
 *********************************************************************************************************************/
	VAR(uint8, AUTOMATIC)   i;

	for ( i = 0U; i < D_NUMNOTCHFILT_CNT_U08; i++)
	{
		NF_Init_f32(D_ASSISTINIT_MTRNM_F32, &(CombAstNFSV2_Cnt_M_Str[i]), &(t_StCmpNFK_Str[i]));
	}

	LPF_Init_f32_m(D_ZERO_ULS_F32, k_StCmpHwTrqLPFKn_Hz_f32, D_2MS_SEC_F32, &HwTrqSV2_HwNm_M_Str);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StabilityComp2_Per1
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
 *   Float Rte_IRead_StabilityComp2_Per1_AssistDDFactor_Uls_f32(void)
 *   Float Rte_IRead_StabilityComp2_Per1_AsstFWActive_Uls_f32(void)
 *   Float Rte_IRead_StabilityComp2_Per1_CombinedAssist_MtrNm_f32(void)
 *   Float Rte_IRead_StabilityComp2_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_StabilityComp2_Per1_VehicleSpeed_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_StabilityComp2_Per1_SysAssistCmd_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_StabilityComp2_Per1_SysAssistCmd_MtrNm_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_STABILITYCOMP2_APPL_CODE) StabilityComp2_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: StabilityComp2_Per1
 *********************************************************************************************************************/

	/* Input Signals */
	VAR(float32, AUTOMATIC) AssistDDFactor_Uls_T_f32;
	VAR(float32, AUTOMATIC) AsstFWActive_Uls_T_f32;
	VAR(float32, AUTOMATIC) CombinedAssist_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32;
	VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;
	VAR(float32, AUTOMATIC) SysAssistCmd_MtrNm_T_f32;


	/* FPM Intermediates */
	VAR(uint16, AUTOMATIC) AssistDDFactor_Uls_T_u2p14;
	VAR(uint16, AUTOMATIC) AsstFWActive_Uls_T_u2p14;
	VAR(sint16, AUTOMATIC) SysAssistCmd_MtrNm_T_s4p11;
	VAR(uint16, AUTOMATIC) HwTrq_HwNm_T_u8p8;
	VAR(uint16, AUTOMATIC) VehSpd_Kph_T_u9p7;

	/* Intermediate Variables */
	VAR(uint16, AUTOMATIC) CompBlnd_Uls_T_u2p14[D_NUMNFBLENDS_CNT_U08];
	VAR(uint16, AUTOMATIC) ADDFBlend_Uls_T_u2p14;
	VAR(float32, AUTOMATIC) HwTrqFilt_HwNm_T_f32;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_StabilityComp2_Per1_CP0_CheckpointReached();
	
	/* Store RTE elements to local variables for convienience */
	AssistDDFactor_Uls_T_f32 = Rte_IRead_StabilityComp2_Per1_AssistDDFactor_Uls_f32();
	AsstFWActive_Uls_T_f32 = Rte_IRead_StabilityComp2_Per1_AsstFWActive_Uls_f32();
	CombinedAssist_MtrNm_T_f32 = Rte_IRead_StabilityComp2_Per1_CombinedAssist_MtrNm_f32();
	HwTorque_HwNm_T_f32 = Rte_IRead_StabilityComp2_Per1_HwTorque_HwNm_f32();
	VehicleSpeed_Kph_T_f32 = Rte_IRead_StabilityComp2_Per1_VehicleSpeed_Kph_f32();
	
	AssistDDFactor_Uls_T_u2p14 = FPM_FloatToFixed_m (AssistDDFactorSV_Uls_M_f32, u2p14_T);	/* Range 0 to 1.9921875 */
	AsstFWActive_Uls_T_u2p14 = FPM_FloatToFixed_m (AsstFWActive_Uls_T_f32, u2p14_T); /* Range 0 to 1 */
	AssistDDFactor_Uls_T_u2p14 = AssistDDFactor_Uls_T_u2p14 + AsstFWActive_Uls_T_u2p14;	/* Worst case is 1.9921875 + 1 = 2.9921875 so u2p14 is sufficient to hold the data upto 3.99 */
	
	HwTrqFilt_HwNm_T_f32 = LPF_OpUpdate_f32_m(Abs_f32_m(HwTorqueSV_HwNm_M_f32), &HwTrqSV2_HwNm_M_Str);
	HwTrq_HwNm_T_u8p8 = FPM_FloatToFixed_m(HwTrqFilt_HwNm_T_f32, u8p8_T);
	
	VehSpd_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
		
	CombinedAssist_MtrNm_T_f32 = Limit_m(CombinedAssist_MtrNm_T_f32, -D_COMPINLIMIT_MTRNM_F32, D_COMPINLIMIT_MTRNM_F32);

	/* Calculate Blend Fractions that are common to both compensator executions */
	/* Interpolate the ADDF_Blend */
	ADDFBlend_Uls_T_u2p14 = IntplVarXY_u16_u16Xu16Y_Cnt(
							t_StCmpADDFBlendX_Uls_u2p14,
							t_StCmpADDFBlendY_Uls_u2p14,
							TableSize_m(t_StCmpADDFBlendX_Uls_u2p14),
							AssistDDFactor_Uls_T_u2p14);
							
	/* Interpolate the CompBlndFraction for Notch filters 1 and 2 */
	CompBlnd_Uls_T_u2p14[D_COMPBLND12IDX_CNT_U08] = BilinearXYM_u16_u16Xu16YM_Cnt(
		VehSpd_Kph_T_u9p7,
		HwTrq_HwNm_T_u8p8,
		t_StCmpBlendSpdBS_Kph_u9p7,
		TableSize_m(t_StCmpBlendSpdBS_Kph_u9p7),
		t_StCmpBlend12Trq_HwNm_u8p8,
		(P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_StCmpBlend12TblY_Uls_u2p14,
		TableSize_m(t_StCmpBlend12Trq_HwNm_u8p8));

	/* Interpolate the CompBlndFraction for zero and Notch filter 2 */
	CompBlnd_Uls_T_u2p14[D_COMPBLND02IDX_CNT_U08] = BilinearXYM_u16_u16Xu16YM_Cnt(
		VehSpd_Kph_T_u9p7,
		HwTrq_HwNm_T_u8p8,
		t_StCmpBlendSpdBS_Kph_u9p7,
		TableSize_m(t_StCmpBlendSpdBS_Kph_u9p7),
		t_StCmpBlend12Trq_HwNm_u8p8,
		(P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_StCmpBlend02TblY_Uls_u2p14,
		TableSize_m(t_StCmpBlend12Trq_HwNm_u8p8));

	/* Interpolate the CompBlndFraction for Notch filters 3 and 4 */
	CompBlnd_Uls_T_u2p14[D_COMPBLND34IDX_CNT_U08] = BilinearXYM_u16_u16Xu16YM_Cnt(
		VehSpd_Kph_T_u9p7,
		HwTrq_HwNm_T_u8p8,
		t_StCmpBlendSpdBS_Kph_u9p7,
		TableSize_m(t_StCmpBlendSpdBS_Kph_u9p7),
		t_StCmpBlend34Trq_HwNm_u8p8,
		(P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_StCmpBlend34TblY_Uls_u2p14,
		TableSize_m(t_StCmpBlend34Trq_HwNm_u8p8));

	/* Interpolate the CompBlndFraction for zero and Notch filter 4 */
	CompBlnd_Uls_T_u2p14[D_COMPBLND04IDX_CNT_U08] = BilinearXYM_u16_u16Xu16YM_Cnt(
		VehSpd_Kph_T_u9p7,
		HwTrq_HwNm_T_u8p8,
		t_StCmpBlendSpdBS_Kph_u9p7,
		TableSize_m(t_StCmpBlendSpdBS_Kph_u9p7),
		t_StCmpBlend34Trq_HwNm_u8p8,
		(P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_StCmpBlend04TblY_Uls_u2p14,
		TableSize_m(t_StCmpBlend34Trq_HwNm_u8p8));

	/* Execute compensator routines */
	SysAssistCmd_MtrNm_T_s4p11 = ApplyStabilityComp2(CombinedAssist_MtrNm_T_f32, &(CombAstNFSV2_Cnt_M_Str[0U]), CompBlnd_Uls_T_u2p14, ADDFBlend_Uls_T_u2p14, TRUE);
	SysAssistCmd_MtrNm_T_f32 = FPM_FixedToFloat_m(SysAssistCmd_MtrNm_T_s4p11, s4p11_T);

	/* Store the state variables for use in this function */
	HwTorqueSV_HwNm_M_f32 = HwTorque_HwNm_T_f32;
	VehicleSpeedSV_Kph_M_f32 = VehicleSpeed_Kph_T_f32;
	AssistDDFactorSV_Uls_M_f32 = AssistDDFactor_Uls_T_f32;
	
	/* Update output port values */
	Rte_IWrite_StabilityComp2_Per1_SysAssistCmd_MtrNm_f32(SysAssistCmd_MtrNm_T_f32);

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_StabilityComp2_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_STABILITYCOMP2_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
STATIC FUNC(sint16, RTE_AP_STABILITYCOMP_APPL_CODE) ApplyStabilityComp2(VAR(float32, AUTOMATIC) Assist_MtrNm_T_f32,
																 P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) FiltSVPtr_Uls_T_Str, 
																 P2CONST(uint16, AUTOMATIC, AUTOMATIC) CompBlnd_Uls_T_u2p14, 
																 VAR(uint16, AUTOMATIC) ADDFBlend_Uls_T_u2p14,
																 VAR(boolean, AUTOMATIC) WriteDisplayVars_Cnt_T_lgc)
{
	VAR(uint8, AUTOMATIC)           i;
	VAR(float32, AUTOMATIC)			StCmp02Out_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)			StCmp04Out_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)			StCmp12Out_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)			StCmp34Out_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)			FilteredOutput_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)         AssistFilt_MtrNm_T_f32[D_NUMNOTCHFILT_CNT_U08];
	VAR(sint16, AUTOMATIC)			FilteredOutput_MtrNm_T_s4p11;
	VAR(float32, AUTOMATIC) 		ADDFBlend_Uls_T_f32;
	VAR(float32, AUTOMATIC) 		CompBlnd_Uls_T_f32[D_NUMNFBLENDS_CNT_U08];
	
	for ( i = 0U; i < D_NUMNFBLENDS_CNT_U08; i++)
	{
		CompBlnd_Uls_T_f32[i] = FPM_FixedToFloat_m(CompBlnd_Uls_T_u2p14[i], u2p14_T);
	}
	
	/* Execute Notch Filters */
	for ( i = 0U; i < D_NUMNOTCHFILT_CNT_U08; i++)
	{
		AssistFilt_MtrNm_T_f32[i] = NF_FullUpdate_f32(Assist_MtrNm_T_f32, &(FiltSVPtr_Uls_T_Str[i]), &(t_StCmpNFK_Str[i]));
	}

	/* Blend between Raw Input and Notch Filter 2 */
	StCmp02Out_MtrNm_T_f32 = Blend_f32(Assist_MtrNm_T_f32, AssistFilt_MtrNm_T_f32[1U], CompBlnd_Uls_T_f32[D_COMPBLND02IDX_CNT_U08]);
	/* Blend Notch Filter Outputs */
	StCmp12Out_MtrNm_T_f32 = Blend_f32(AssistFilt_MtrNm_T_f32[0U], StCmp02Out_MtrNm_T_f32, CompBlnd_Uls_T_f32[D_COMPBLND12IDX_CNT_U08]);

	/* Blend between Raw Input and Notch Filter 4 */
	StCmp04Out_MtrNm_T_f32 = Blend_f32(Assist_MtrNm_T_f32, AssistFilt_MtrNm_T_f32[3U], CompBlnd_Uls_T_f32[D_COMPBLND04IDX_CNT_U08]);
	/* Blend Notch Filter 3 and 4 Outputs */
	StCmp34Out_MtrNm_T_f32 = Blend_f32(AssistFilt_MtrNm_T_f32[2U], StCmp04Out_MtrNm_T_f32, CompBlnd_Uls_T_f32[D_COMPBLND34IDX_CNT_U08]);
	
	if( WriteDisplayVars_Cnt_T_lgc == TRUE )
	{
		StCmp1Out2_MtrNm_D_f32 = AssistFilt_MtrNm_T_f32[0U];
		StCmp2Out2_MtrNm_D_f32 = StCmp02Out_MtrNm_T_f32;
		StCmp3Out2_MtrNm_D_f32 = AssistFilt_MtrNm_T_f32[2U];
		StCmp4Out2_MtrNm_D_f32 = StCmp04Out_MtrNm_T_f32;
	}

	ADDFBlend_Uls_T_f32 = FPM_FixedToFloat_m(ADDFBlend_Uls_T_u2p14, u2p14_T); 
	
	/* Apply Drive Dynamics Blending */
	FilteredOutput_MtrNm_T_f32 = Blend_f32(StCmp12Out_MtrNm_T_f32, StCmp34Out_MtrNm_T_f32, ADDFBlend_Uls_T_f32);
	/* Limit ouput values */
	FilteredOutput_MtrNm_T_f32 = Limit_m(FilteredOutput_MtrNm_T_f32, -D_ASSTSCLMT_MTRNM_F32, D_ASSTSCLMT_MTRNM_F32);

	FilteredOutput_MtrNm_T_s4p11 = FPM_FloatToFixed_m(FilteredOutput_MtrNm_T_f32, s4p11_T);
	return(FilteredOutput_MtrNm_T_s4p11);
}
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
