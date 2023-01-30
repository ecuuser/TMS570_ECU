/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_Assist.c
 *     Workspace:  C:/Workspace/Assist-CBD_Assist/SF01_008.0/Assist/autosar
 *     SW-C Type:  Ap_Assist
 *  Generated at:  Thu May  2 11:27:33 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_Assist>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Nov 29 18:34:17 2011
 * %version:          26 %
 * %date_modified:    Wed Apr 24 07:28:01 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 05/26/11   5       JJW       Updated template for DrvDyn scale factor addition
 * 05/31/11   7       JJW       RTE Access changes for new port interface definition
 * 06/03/11   8       SAH       All pass design updates. Remove Per 3()
 * 06/03/11   9       SAH       Merged version 8 with version 7.1.1 template update
 * 06/14/11  10       SAH       Updates for A_2372, always positive assist.
 * 06/16/11  11       JJW       Added HPAssist_MtrNm_D_f32 Display variable to meet FDD
 * 07/13/11  12       LWW       Made base assist tables signed, added base assist and HP gain blending interface
 * 11/07/11  13       JJW       Component template updates for SF01_008 implementation
 * 11/10/11  14       M. Story  Component design update for SF01 008 requirements
 * 11/14/11  15       JJW       Created Component project.
 * 11/28/11  16       NA        Updeted to match new naming standard for Cal arrays.
 * 11/29/11  17       M. Story  Updated to correct compiler errors after sandbox was created.
 * 01/05/12  18       KJS       Anomaly 3246 correction and QAC warning for WIR0.
 * 05/02/12  19       NRAR      FaultInjection point is added
 * 05/04/12  20       NRAR      added Kevin changes to this version
 * 06/20/12  21       OT        Update to SF-01 v010 (use DutyCycleLevel instead of ThermalAssistScl)           5707
 * 07/23/12  22       LWW       Updated resolution of lookup Y table for interpolation issue
 * 07/23/12  23       LWW       Updated resolution of lookup X table for interpolation issue
 * 09/17/12  24       JJW       Added checkpoints
 * 10/03/12  25       NRAR      Updated to FDD Ver 011                                                          6425
 * 04/24/13  26       Jared     Updated to FDD ver 012                                                          7897
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_Assist.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Ap_Assist_Cfg.h"
#include "GlobalMacro.h"
#include "fixmath.h"
#include "interpolation.h"
#include "filters.h"
#include "CalConstants.h"


#define D_WIRBLENDFRAC_ULS_U2P14		FPM_InitFixedPoint_m(1.0,u2p14_T)
#define D_ASSTTRQLLMT_MTRNM_F32         (-0.1F)


#define ASSIST_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(uint16,  AP_ASSIST_VAR) WIRBlend_Uls_D_u2p14;
STATIC volatile VAR(uint16,  AP_ASSIST_VAR) ThermalAssistScl_Uls_D_u2p14;
#define ASSIST_STOP_SEC_VAR_CLEARED_16
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
 * Enumeration Types:
 * ==================
 * FltInjectionLocType: Enumeration of integer in interval [0...255] with enumerators
 *   FLTINJ_ASSIST (1u)
 *   FLTINJ_RETURN (2u)
 *   FLTINJ_DAMPING (3u)
 *   FLTINJ_ASSTSUMNLMT (4u)
 *   FLTINJ_AVGFRICLRN (7u)
 *   FLTINJ_HYSTCOMP (12u)
 *   FLTINJ_INERTIACOMP (14u)
 *   FLTINJ_STABILITYCOMP (29u)
 *   FLTINJ_TRQBASEDINRTCOMP (30u)
 *   FLTINJ_SRLCOMVEHSPD_SGNLCOND (33u)
 *   FLTINJ_ASSTFIREWALL (34u)
 *   FLTINJ_ASSTEOTGAIN_LMTCOD (38u)
 *   FLTINJ_DDASTFACTRQST_DRVDYNCTRL (150u)
 *   FLTINJ_DDDMPFACTRQST_DRVDYNCTRL (151u)
 *   FLTINJ_DDRTNFACTRQST_DRVDYNCTRL (152u)
 *   FLTINJ_OUTPUTRAMPMULT_LMTCOD (153u)
 *   FLTINJ_ASSTEOTLIMIT_LMTCOD (154u)
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
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_ASSIST_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Assist_Per1
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
 *   Float Rte_IRead_Assist_Per1_AssistDDFactor_Uls_f32(void)
 *   Boolean Rte_IRead_Assist_Per1_DftAsstTbl_Cnt_lgc(void)
 *   Float Rte_IRead_Assist_Per1_DutyCycleLevel_Uls_f32(void)
 *   Float Rte_IRead_Assist_Per1_DwnldAsstGain_Uls_f32(void)
 *   Float Rte_IRead_Assist_Per1_HwTrqHysAdd_HwNm_f32(void)
 *   Float Rte_IRead_Assist_Per1_HwTrq_HwNm_f32(void)
 *   Float Rte_IRead_Assist_Per1_IpTrqOvr_HwNm_f32(void)
 *   Float Rte_IRead_Assist_Per1_VehSpd_Kph_f32(void)
 *   Float Rte_IRead_Assist_Per1_WIRCmdAmpBlnd_MtrNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_Assist_Per1_BaseAssistCmd_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_Assist_Per1_BaseAssistCmd_MtrNm_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FltInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ASSIST_APPL_CODE) Assist_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Assist_Per1
 *********************************************************************************************************************/

	VAR(float32, AUTOMATIC) HwTrq_HwNm_T_f32;
	VAR(uint16, AUTOMATIC) VehSpd_Kph_T_u9p7;
	VAR(float32, AUTOMATIC) HystAdd_HwNm_T_f32;
	VAR(uint16, AUTOMATIC) DutyCycleLevel_Cnt_T_u16p0;
	VAR(float32, AUTOMATIC) IpTrqOvr_HwNm_T_f32;
	VAR(float32, AUTOMATIC) AssistDDFactor_Uls_T_f32;
	VAR(uint16, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_u5p11;
	VAR(float32, AUTOMATIC) DwnldAsstGain_Uls_T_f32;
	VAR(boolean, AUTOMATIC) DftAsstTbl_Cnt_T_lgc;

	VAR(sint32, AUTOMATIC) SignModTrq_Uls_T_s32;
	VAR(uint16, AUTOMATIC) ModTrq_HwNm_T_u8p8;
	VAR(sint16, AUTOMATIC) WIR0_MtrNm_T_s4p11;
	VAR(uint16, AUTOMATIC) WIRBlend_Uls_T_u2p14;
	VAR(sint16, AUTOMATIC) WIR1_MtrNm_T_s4p11;
	VAR(sint32, AUTOMATIC) WIR0_MtrNm_T_s6p25;
	VAR(sint32, AUTOMATIC) WIR1_MtrNm_T_s6p25;
	VAR(sint32, AUTOMATIC) AssistTrq_MtrNm_T_s6p25;
	VAR(float32, AUTOMATIC) AssistTrq_MtrNm_T_f32;
	VAR(uint16, AUTOMATIC) ThermalAssistScl_Uls_T_u2p14;
	VAR(float32, AUTOMATIC) ThermalAssistScl_Uls_T_f32;
	VAR(float32, AUTOMATIC) BaseAssistCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) ModTrq_HwNm_T_f32;
	VAR(float32, AUTOMATIC) AbsModTrq_HwNm_T_f32;


	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_Assist_Per1_CP0_CheckpointReached();

	HwTrq_HwNm_T_f32 = Rte_IRead_Assist_Per1_HwTrq_HwNm_f32();
	VehSpd_Kph_T_u9p7 = FPM_FloatToFixed_m((Rte_IRead_Assist_Per1_VehSpd_Kph_f32()), u9p7_T);
	HystAdd_HwNm_T_f32 = Rte_IRead_Assist_Per1_HwTrqHysAdd_HwNm_f32();
	DutyCycleLevel_Cnt_T_u16p0 = FPM_FloatToFixed_m(Rte_IRead_Assist_Per1_DutyCycleLevel_Uls_f32(), u16p0_T);
	IpTrqOvr_HwNm_T_f32 = Rte_IRead_Assist_Per1_IpTrqOvr_HwNm_f32();
	AssistDDFactor_Uls_T_f32 = Rte_IRead_Assist_Per1_AssistDDFactor_Uls_f32();
	WIRCmdAmpBlnd_MtrNm_T_u5p11 = FPM_FloatToFixed_m((Rte_IRead_Assist_Per1_WIRCmdAmpBlnd_MtrNm_f32()), u5p11_T);
	DwnldAsstGain_Uls_T_f32 = Rte_IRead_Assist_Per1_DwnldAsstGain_Uls_f32();
	DftAsstTbl_Cnt_T_lgc = Rte_IRead_Assist_Per1_DftAsstTbl_Cnt_lgc();


	ModTrq_HwNm_T_f32 = HwTrq_HwNm_T_f32 + IpTrqOvr_HwNm_T_f32 + HystAdd_HwNm_T_f32;
	SignModTrq_Uls_T_s32 = Sign_f32_m(ModTrq_HwNm_T_f32);
	AbsModTrq_HwNm_T_f32 = Abs_f32_m(ModTrq_HwNm_T_f32);
	ModTrq_HwNm_T_u8p8 = FPM_FloatToFixed_m(AbsModTrq_HwNm_T_f32, u8p8_T);


	if ( TRUE == DftAsstTbl_Cnt_T_lgc)
	{
		AssistTrq_MtrNm_T_f32 = AbsModTrq_HwNm_T_f32 * DwnldAsstGain_Uls_T_f32;
	}
	else
	{
		WIR0_MtrNm_T_s4p11 = BilinearXMYM_s16_u16XMs16YM_Cnt(VehSpd_Kph_T_u9p7,
																ModTrq_HwNm_T_u8p8,
																t_CmnVehSpd_Kph_u9p7,
																TableSize_m(t_CmnVehSpd_Kph_u9p7),
																(P2CONST(uint16, AUTOMATIC, AP_ASSIST_CONST))t2_AsstHwtX0_HwNm_u8p8,
																(P2CONST(sint16, AUTOMATIC, AP_ASSIST_CONST))t2_AsstAsstY0_MtrNm_s4p11,
																TableSize_m(t2_AsstHwtX0_HwNm_u8p8[0]));

		WIRBlend_Uls_T_u2p14 = BilinearXMYM_u16_u16XMu16YM_Cnt(VehSpd_Kph_T_u9p7,
																WIRCmdAmpBlnd_MtrNm_T_u5p11,
																t_CmnVehSpd_Kph_u9p7,
																TableSize_m(t_CmnVehSpd_Kph_u9p7),
																(P2CONST(uint16, AUTOMATIC, AP_ASSIST_CONST))t2_AsstWIRBlndX_MtrNm_u5p11,
																(P2CONST(uint16, AUTOMATIC, AP_ASSIST_CONST))t2_AsstWIRBlendY_Uls_u2p14,
																TableSize_m(t2_AsstWIRBlndX_MtrNm_u5p11[0]));

		WIRBlend_Uls_D_u2p14 = WIRBlend_Uls_T_u2p14;

		WIR1_MtrNm_T_s4p11 = BilinearXMYM_s16_u16XMs16YM_Cnt(VehSpd_Kph_T_u9p7,
																ModTrq_HwNm_T_u8p8 ,
																t_CmnVehSpd_Kph_u9p7,
																TableSize_m(t_CmnVehSpd_Kph_u9p7),
																(P2CONST(uint16, AUTOMATIC, AP_ASSIST_CONST))t2_AsstHwtX1_HwNm_u8p8,
																(P2CONST(sint16, AUTOMATIC, AP_ASSIST_CONST))t2_AsstAsstY1_MtrNm_s4p11,
																TableSize_m(t2_AsstHwtX1_HwNm_u8p8[0]));

		WIR0_MtrNm_T_s6p25 = ((sint32)WIR0_MtrNm_T_s4p11 * ((sint32)D_WIRBLENDFRAC_ULS_U2P14 - (sint32)WIRBlend_Uls_T_u2p14));
		WIR1_MtrNm_T_s6p25 = (sint32)WIR1_MtrNm_T_s4p11 * (sint32)WIRBlend_Uls_T_u2p14;

		AssistTrq_MtrNm_T_s6p25 = WIR0_MtrNm_T_s6p25 + WIR1_MtrNm_T_s6p25;
		AssistTrq_MtrNm_T_f32 = FPM_FixedToFloat_m(AssistTrq_MtrNm_T_s6p25, s6p25_T);

		ThermalAssistScl_Uls_T_u2p14 = IntplVarXY_u16_u16Xu16Y_Cnt( t_AsstThermSclX_Cnt_u16p0,
																	t_AsstThermSclY_Uls_u2p14,
																	TableSize_m(t_AsstThermSclX_Cnt_u16p0),
																	DutyCycleLevel_Cnt_T_u16p0);

		ThermalAssistScl_Uls_D_u2p14 = ThermalAssistScl_Uls_T_u2p14;

		ThermalAssistScl_Uls_T_f32 = FPM_FixedToFloat_m(ThermalAssistScl_Uls_T_u2p14, u2p14_T);

		AssistTrq_MtrNm_T_f32 = AssistTrq_MtrNm_T_f32 * ThermalAssistScl_Uls_T_f32;

	}

	AssistTrq_MtrNm_T_f32 = Limit_m(AssistTrq_MtrNm_T_f32, D_ASSTTRQLLMT_MTRNM_F32, D_MTRTRQCMDHILMT_MTRNM_F32);
	AssistTrq_MtrNm_T_f32 = AssistTrq_MtrNm_T_f32 * (float32)SignModTrq_Uls_T_s32;

	BaseAssistCmd_MtrNm_T_f32 = AssistTrq_MtrNm_T_f32  * AssistDDFactor_Uls_T_f32;

	BaseAssistCmd_MtrNm_T_f32 = Limit_m(BaseAssistCmd_MtrNm_T_f32, D_MTRTRQCMDLOLMT_MTRNM_F32, D_MTRTRQCMDHILMT_MTRNM_F32);

	#if (STD_ON == BC_ASSIST_FAULTINJECTIONPOINT)
	Rte_Call_FltInjection_SCom_FltInjection(&BaseAssistCmd_MtrNm_T_f32,FLTINJ_ASSIST);
	#endif

	/* Update Output port values with newly computed values */
	Rte_IWrite_Assist_Per1_BaseAssistCmd_MtrNm_f32(BaseAssistCmd_MtrNm_T_f32);

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_Assist_Per1_CP1_CheckpointReached();

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_ASSIST_APPL_CODE
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
