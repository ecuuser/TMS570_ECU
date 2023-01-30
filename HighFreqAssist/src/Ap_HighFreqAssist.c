/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_HighFreqAssist.c
 *     Workspace:  C:/Workspace/HighFreqAssist-CBD_HighFreqAssist/SF28/HighFreqAssist/autosar
 *     SW-C Type:  Ap_HighFreqAssist
 *  Generated at:  Thu May  2 10:37:35 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_HighFreqAssist>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Thu Apr  5 14:00:00 2012
 * %version:          3 %
 * %derived_by:       kzdyfh %
 * %date_modified:    Wed May  1 15:16:46 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                                SCR #
 * -------   -------  --------  --------------------------------------------------------------------------------  -----
 * 04/05/12  1        OT        Initial Version                                                                   5200
 * 09/20/12  2        SSK       Checkpoint added                                                                  6228
 * 05/01/13  3        Jared     Updated to FDD ver 002                                                            7901
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_HighFreqAssist.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Ap_HighFreqAssist_Cfg.h"
#include "CalConstants.h"
#include "GlobalMacro.h"
#include "filters.h"
#include "interpolation.h"
#include "fixmath.h"


#define HYSTADD_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(HPF32KSV_Str, AP_HIGHFREQASSIST_VAR) HwTorqueHPFKSV_Cnt_M_str;
#define HYSTADD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

#define HIGHFREQASSIST_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(float32, AP_HIGHFREQASSIST_VAR) GainBlend_Uls_D_f32;
STATIC volatile VAR(float32, AP_HIGHFREQASSIST_VAR) GainWIRZero_MtrNmpHwNm_D_f32;
STATIC volatile VAR(float32, AP_HIGHFREQASSIST_VAR) GainVal_MtrNmpHwNm_D_f32;
#define HIGHFREQASSIST_STOP_SEC_VAR_CLEARED_32
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
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_HIGHFREQASSIST_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: HighFreqAssist_Per1
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
 *   Float Rte_IRead_HighFreqAssist_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_HighFreqAssist_Per1_VehicleSpeed_Kph_f32(void)
 *   Float Rte_IRead_HighFreqAssist_Per1_WIRCmdAmpBlnd_MtrNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_HighFreqAssist_Per1_HighFreqAssist_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_HighFreqAssist_Per1_HighFreqAssist_MtrNm_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_HIGHFREQASSIST_APPL_CODE) HighFreqAssist_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: HighFreqAssist_Per1
 *********************************************************************************************************************/

	VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32;
	VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;
	VAR(float32, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_f32;

	VAR(sint16,  AUTOMATIC) HwTorque_HwNm_T_s4p11;
	VAR(uint16,  AUTOMATIC) AbsHwTorque_HwNm_T_u5p11;
	VAR(uint16,  AUTOMATIC) VehicleSpeed_Kph_T_u9p7;
	VAR(uint16,  AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_u4p12;
	VAR(uint16,  AUTOMATIC) HPFFreq_Hz_T_u7p9;
	VAR(float32,  AUTOMATIC) HPFFreq_Hz_T_f32;
	VAR(float32, AUTOMATIC) HighFrequencyTorque_HwNm_T_f32;
	VAR(uint16,  AUTOMATIC) GainBlend_Uls_T_u1p15;
	VAR(float32, AUTOMATIC) GainBlend_Uls_T_f32;
	VAR(uint16,  AUTOMATIC) GainWIRZero_MtrNmpHwNm_T_u3p13;
	VAR(float32, AUTOMATIC) GainWIRZero_MtrNmpHwNm_T_f32;
	VAR(uint16,  AUTOMATIC) GainWIRMax_MtrNmpHwNm_T_u3p13;
	VAR(float32, AUTOMATIC) GainWIRMax_MtrNmpHwNm_T_f32;
	VAR(float32, AUTOMATIC) GainVal_MtrNmpHwNm_T_f32;

	VAR(float32, AUTOMATIC) HighFreqAssist_MtrNm_T_f32;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_HighFreqAssist_Per1_CP0_CheckpointReached();

	HwTorque_HwNm_T_f32 = Rte_IRead_HighFreqAssist_Per1_HwTorque_HwNm_f32();
	VehicleSpeed_Kph_T_f32 = Rte_IRead_HighFreqAssist_Per1_VehicleSpeed_Kph_f32();
	WIRCmdAmpBlnd_MtrNm_T_f32 = Rte_IRead_HighFreqAssist_Per1_WIRCmdAmpBlnd_MtrNm_f32();

	HwTorque_HwNm_T_s4p11 = FPM_FloatToFixed_m(HwTorque_HwNm_T_f32, s4p11_T);
	AbsHwTorque_HwNm_T_u5p11 = Abs_s16_m(HwTorque_HwNm_T_s4p11);
	VehicleSpeed_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
	WIRCmdAmpBlnd_MtrNm_T_u4p12 = FPM_FloatToFixed_m(WIRCmdAmpBlnd_MtrNm_T_f32, u4p12_T);

	HPFFreq_Hz_T_u7p9 = IntplVarXY_u16_u16Xu16Y_Cnt(t_CmnVehSpd_Kph_u9p7,
													t_LPFKnY_Hz_u7p9,
													TableSize_m(t_CmnVehSpd_Kph_u9p7),
													VehicleSpeed_Kph_T_u9p7);

	HPFFreq_Hz_T_f32 = FPM_FixedToFloat_m(HPFFreq_Hz_T_u7p9, u7p9_T);
	HPF_KUpdate_f32_m(HPFFreq_Hz_T_f32, D_2MS_SEC_F32, &HwTorqueHPFKSV_Cnt_M_str);
	HighFrequencyTorque_HwNm_T_f32 = HPF_OpUpdate_f32_m(HwTorque_HwNm_T_f32, &HwTorqueHPFKSV_Cnt_M_str);


	/* Determine Gain */
	GainBlend_Uls_T_u1p15 = BilinearXMYM_u16_u16XMu16YM_Cnt(VehicleSpeed_Kph_T_u9p7,
															WIRCmdAmpBlnd_MtrNm_T_u4p12,
															t_CmnVehSpd_Kph_u9p7,
															TableSize_m(t_CmnVehSpd_Kph_u9p7),
															t2_WIRBlendX_MtrNm_u4p12[0],
															t2_WIRBlendY_Uls_u1p15[0],
															TableSize_m(t2_WIRBlendX_MtrNm_u4p12[0]));

	GainBlend_Uls_T_f32 = FPM_FixedToFloat_m(GainBlend_Uls_T_u1p15, u1p15_T);


	GainWIRZero_MtrNmpHwNm_T_u3p13 = BilinearXMYM_u16_u16XMu16YM_Cnt(VehicleSpeed_Kph_T_u9p7,
																	 AbsHwTorque_HwNm_T_u5p11,
																	 t_CmnVehSpd_Kph_u9p7,
																	 TableSize_m(t_CmnVehSpd_Kph_u9p7),
																	 t2_TorqX0_HwNm_u5p11[0],
																	 t2_GainY0_MtrNmpHwNm_u3p13[0],
																	 TableSize_m(t2_TorqX0_HwNm_u5p11[0]));

	GainWIRZero_MtrNmpHwNm_T_f32 = FPM_FixedToFloat_m(GainWIRZero_MtrNmpHwNm_T_u3p13, u3p13_T);


	GainWIRMax_MtrNmpHwNm_T_u3p13 = BilinearXMYM_u16_u16XMu16YM_Cnt(VehicleSpeed_Kph_T_u9p7,
																	AbsHwTorque_HwNm_T_u5p11,
																	t_CmnVehSpd_Kph_u9p7,
																	TableSize_m(t_CmnVehSpd_Kph_u9p7),
																	t2_TorqX1_HwNm_u5p11[0],
																	t2_GainY1_MtrNmpHwNm_u3p13[0],
																	TableSize_m(t2_TorqX1_HwNm_u5p11[0]));

	GainWIRMax_MtrNmpHwNm_T_f32 = FPM_FixedToFloat_m(GainWIRMax_MtrNmpHwNm_T_u3p13, u3p13_T);

	GainVal_MtrNmpHwNm_T_f32 = Blend_f32(GainWIRZero_MtrNmpHwNm_T_f32, GainWIRMax_MtrNmpHwNm_T_f32, GainBlend_Uls_T_f32);

	HighFreqAssist_MtrNm_T_f32 = HighFrequencyTorque_HwNm_T_f32 * GainVal_MtrNmpHwNm_T_f32;


	GainBlend_Uls_D_f32 = GainBlend_Uls_T_f32;
	GainWIRZero_MtrNmpHwNm_D_f32 = GainWIRZero_MtrNmpHwNm_T_f32;
	GainVal_MtrNmpHwNm_D_f32 = GainVal_MtrNmpHwNm_T_f32;
	Rte_IWrite_HighFreqAssist_Per1_HighFreqAssist_MtrNm_f32(HighFreqAssist_MtrNm_T_f32);

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_HighFreqAssist_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_HIGHFREQASSIST_APPL_CODE
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
