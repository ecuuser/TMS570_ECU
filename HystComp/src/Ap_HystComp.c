/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_HystComp.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/HystComp-nzt9hv/HystComp/autosar
 *     SW-C Type:  Ap_HystComp
 *  Generated at:  Sun Nov  4 13:52:13 2012
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_HystComp>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          26 %
 * %derived_by:       kzdyfh %
 * %date_modified:    Thu May  2 15:13:12 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/13/11  5        LWW       Added Negative Hysteresis and ConstFric Blending interface
 * 11/21/11  6        M. Story  Updates for FDD #SF-12 001
 * 11/29/11  7        M. Story  Fixes from component compiile project
 * 12/08/11  8        JJW       Template generation updates per model updates to match SF
 * 12/09/11  8.1.1    JJW       Design removal of state dependant execution template update
 * 12/09/11  9        M. Story  Intergation issues, removed Per1
 * 12/12/11  10       JJW       Corrected Rte access macro usage to meet SWC design
 * 01/13/12  11       M. Story  Added initialization of HwNmPerMtrNm_Uls_T_f32
 * 01/20/12  12       M. Story  Removed icorrect casting
 * 01/23/12  13       JJW       CalcHysMagnitude local var declaration correction, uint16 to uint32
 * 01/24/12  14       JJW       Updated SWC to match FDD implementation and names to correct anomaly
 * 01/24/12  14       JJW       Removed unused module var PrevRiseX_Uls_M_s8p7 that was inadvertantly left in the design
 * 05/02/12  16       NRAR      FaultInjectionPoint is added
 * 05/10/12  17       NRAR      Correct Source file checkedin
 * 05/25/12  18       Jared     Changed to floating point math (Anom #3353 & #3354)                             5496,5499
 * 05/29/12  19       LWW       Fixed duplicate temp variable declaration
 * 12/13/12  20       Jared     Added new average friction learn input FricOffset_HwNm_f32                      5600
 * 07/23/12  21       NRAR      Removed cal used for output slewrate lmt, replace 2^9 saturation blk with Max macro 5600
 * 09/25/12  22       Selva     Checkpoints added and mempmap macros corrected                                  6230
 * 11/04/12  23       Selva     Replaced 1-D AsstMagBlndTbl with  2D HwTrqBlnd Table.Six more Display variables added
 * 11/20/12  24       Blake     Increased precision of HysRiseTblX & HysRiseTblY per Anom 4021                  6855
 * 11/28/12  25       KJS       Corrected HysBlend look up resolution and dimension issues.
 * 05/01/13  25.1.1   NRAR      Anomaly 4937 correction                                                         8184
 * 04/26/13  26       Jared     Updated to FDD ver 007                                                          7899
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_HystComp.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "float.h"
#include "fixmath.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "filters.h"
#include "interpolation.h"
#include "Ap_HystComp_Cfg.h"

#define D_HYSPOSLMT_ULS_F32				1.0F
#define D_WIROFF_IDX_U16				0U
#define D_WIRON_IDX_U16					1U
#define D_WIRCMDBLNDFRC_ULS_F32			1.0F
#define D_HYSSATLOWLMT_HWNM_F32			0.0F
#define D_HYSOUTLMT_MTRNM_F32			8.8F

/* Module Internal Variables */
#define HYSTCOMP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(LPF32KSV_Str, AP_HYSTCOMP_VAR_NOINIT) AssistCmdLPFiltSV_HwNm_M_str;
STATIC VAR(LPF32KSV_Str, AP_HYSTCOMP_VAR_NOINIT) HwTrqLPFiltSV_HwNm_M_str;
STATIC VAR(LPF32KSV_Str, AP_HYSTCOMP_VAR_NOINIT) RawHystCompLPFiltSV_HwNm_M_str;
#define HYSTCOMP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

#define HYSTCOMP_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, AUTOMATIC) HwTrqLastUsed_HwNm_M_f32;
STATIC VAR(float32, AUTOMATIC) Fraction_Uls_M_f32;
STATIC VAR(float32, AUTOMATIC) RawCalc_HwNm_M_f32;
STATIC VAR(float32, AUTOMATIC) RiseX_HwNm_M_f32;
/* Display Variables */
STATIC volatile VAR(float32, AUTOMATIC) CompAvail_HwNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) HwTrqFilt_HwNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) CoulFric_HwNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) PosAvail_HwNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) NegAvail_HwNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) EffCompTrq_HwNm_D_f32;
#define HYSTCOMP_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define HYSTCOMP_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(sint16, AUTOMATIC) AstCmdLastUsed_HwNm_M_s8p7;
STATIC volatile VAR(sint16, AUTOMATIC) AssistCmdFilt_HwNm_D_s8p7;

#define HYSTCOMP_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

STATIC INLINE FUNC(sint16, AP_HYSTCOMP_CODE) MoreCompensation(	VAR(float32, AUTOMATIC) TrqChange_HwNm_T_f32,
																CONSTP2VAR(float32, AUTOMATIC, AP_HYSTCOMP_CONST) RiseXPtr_HwNm_T_f32);

STATIC INLINE FUNC(float32, AP_HYSTCOMP_CODE) LessCompensation(	VAR(float32, AUTOMATIC) TrqChange_HwNm_T_f32,
																VAR(float32, AUTOMATIC) PrevRiseY_Uls_T_f32,
																CONSTP2VAR(float32, AUTOMATIC, AP_HYSTCOMP_CONST) RiseXPtr_HwNm_T_f32);

STATIC FUNC(float32, AP_HYSTCOMP_CODE) CalcAvailComp(	VAR(float32, AUTOMATIC) HwTrqFilt_HwNm_T_f32,
														VAR(sint16, AUTOMATIC) AssistCmdFilt_HwNm_T_s8p7,
														VAR(uint16, AUTOMATIC) VehSpd_Kph_T_u9p7);

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
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_HYSTCOMP_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: HystComp_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_HYSTCOMP_APPL_CODE) HystComp_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: HystComp_Init1
 *********************************************************************************************************************/

	/* Low pass filter init */
	LPF_KUpdate_f32_m(k_HysCmpLPAstLPFKn_Hz_f32, D_2MS_SEC_F32, &AssistCmdLPFiltSV_HwNm_M_str);
	LPF_KUpdate_f32_m(k_HysCmpHwTrqLPFKn_Hz_f32, D_2MS_SEC_F32, &HwTrqLPFiltSV_HwNm_M_str);
	LPF_KUpdate_f32_m(k_HysFinalOutLPFKn_Hz_f32, D_2MS_SEC_F32, &RawHystCompLPFiltSV_HwNm_M_str);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: HystComp_Per1
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
 *   Float Rte_IRead_HystComp_Per1_AssistMechTempEst_DegC_f32(void)
 *   Float Rte_IRead_HystComp_Per1_BaseAssistCmd_MtrNm_f32(void)
 *   Boolean Rte_IRead_HystComp_Per1_DefeatHystService_Cnt_lgc(void)
 *   Float Rte_IRead_HystComp_Per1_FricOffset_HwNm_f32(void)
 *   Float Rte_IRead_HystComp_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_HystComp_Per1_VehicleSpeed_Kph_f32(void)
 *   Float Rte_IRead_HystComp_Per1_WIRCmdAmpBlnd_MtrNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_HystComp_Per1_HysteresisComp_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_HystComp_Per1_HysteresisComp_MtrNm_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FltInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_HYSTCOMP_APPL_CODE) HystComp_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: HystComp_Per1
 *********************************************************************************************************************/
	VAR(boolean, AUTOMATIC) DefeatHystService_Cnt_lgc;
	VAR(uint16, AUTOMATIC) VehSpd_Kph_T_u9p7;
	VAR(float32, AUTOMATIC) AssistCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) HwTrq_HwNm_T_f32;
	VAR(float32, AUTOMATIC) AssistCmd_HwNm_T_f32;
	VAR(sint16, AUTOMATIC) AssistCmdFilt_HwNm_T_s8p7;
	VAR(float32, AUTOMATIC) AssistCmdFilt_HwNm_T_f32;
	VAR(float32, AUTOMATIC) HwTrqFilt_HwNm_T_f32;
	VAR(float32, AUTOMATIC) RawHysComp_HwNm_T_f32;
	VAR(float32, AUTOMATIC) HysComp_HwNm_T_f32;
	VAR(float32, AUTOMATIC) HysComp_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) Fraction_Uls_T_f32;
	VAR(float32, AUTOMATIC) CompAvail_HwNm_T_f32;
	VAR(float32, AUTOMATIC) TrqChange_HwNm_T_f32;
	VAR(float32, AUTOMATIC) PrevRiseY_Uls_T_f32 = Fraction_Uls_M_f32; /* This variable is declared to clearly link back to the simulink model signals */
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_HystComp_Per1_CP0_CheckpointReached();

	DefeatHystService_Cnt_lgc = Rte_IRead_HystComp_Per1_DefeatHystService_Cnt_lgc();
	VehSpd_Kph_T_u9p7 = FPM_FloatToFixed_m(Rte_IRead_HystComp_Per1_VehicleSpeed_Kph_f32(), u9p7_T);
	AssistCmd_MtrNm_T_f32 = Rte_IRead_HystComp_Per1_BaseAssistCmd_MtrNm_f32();
	HwTrq_HwNm_T_f32 = Rte_IRead_HystComp_Per1_HwTorque_HwNm_f32();

	/**
	 * SF-12: Filter and Limit Inputs - FDD BLOCK BEGIN
	 **/
	AssistCmd_HwNm_T_f32 = AssistCmd_MtrNm_T_f32 * k_CmnSysTrqRatio_HwNmpMtrNm_f32;

	AssistCmdFilt_HwNm_T_f32 = LPF_OpUpdate_f32_m(AssistCmd_HwNm_T_f32, &AssistCmdLPFiltSV_HwNm_M_str);

	HwTrqFilt_HwNm_T_f32 = LPF_OpUpdate_f32_m(HwTrq_HwNm_T_f32, &HwTrqLPFiltSV_HwNm_M_str);

	if(Abs_f32_m(AssistCmdFilt_HwNm_T_f32) > FPM_FixedToFloat_m(k_LpFricIpLim_HwNm_u9p7, u9p7_T))
	{
		/* Hold previous block outputs */
		HwTrqFilt_HwNm_T_f32 = HwTrqLastUsed_HwNm_M_f32;
		AssistCmdFilt_HwNm_T_s8p7 = AstCmdLastUsed_HwNm_M_s8p7;
	}
	else
	{
		AssistCmdFilt_HwNm_T_s8p7 = FPM_FloatToFixed_m(AssistCmdFilt_HwNm_T_f32, s8p7_T);
	}
	/** SF-12: Filter and Limit Inputs - FDD BLOCK END **/

	HwTrqFilt_HwNm_D_f32 = HwTrqFilt_HwNm_T_f32;
	AssistCmdFilt_HwNm_D_s8p7 = AssistCmdFilt_HwNm_T_s8p7;

	/**
	 * SF-12: Torque Diff - FDD BLOCK BEGIN
	 **/
	TrqChange_HwNm_T_f32 = HwTrqFilt_HwNm_T_f32 - HwTrqLastUsed_HwNm_M_f32;
	/** SF-12: Torque Diff - FDD BLOCK END **/


	/**
	 * SF-12: Determine Fractional Output - FDD BLOCK BEGIN
	 **/
	if(Abs_f32_m(TrqChange_HwNm_T_f32) < FLT_EPSILON)
	{
		/* Hold state variables (i.e. do not mofiy RiseX_HwNm_M_s1p14) and hold previous block output */
		Fraction_Uls_T_f32 = Fraction_Uls_M_f32;
	}
	else
	{
		if (Sign_f32_m(TrqChange_HwNm_T_f32) == Sign_f32_m(PrevRiseY_Uls_T_f32))
		{
			Fraction_Uls_T_f32 = FPM_FixedToFloat_m(
									MoreCompensation(TrqChange_HwNm_T_f32, &RiseX_HwNm_M_f32),
									s1p14_T);
		}
		else
		{
			Fraction_Uls_T_f32 = LessCompensation(TrqChange_HwNm_T_f32, PrevRiseY_Uls_T_f32, &RiseX_HwNm_M_f32);
		}
	}

	Fraction_Uls_T_f32 = Limit_m(Fraction_Uls_T_f32, -D_HYSPOSLMT_ULS_F32, D_HYSPOSLMT_ULS_F32);
	/** SF-12: Determine Fractional Output - FDD BLOCK END **/

	/**
	* SF-12: Calculate Available Compensation - FDD BLOCK BEGIN
	**/
	CompAvail_HwNm_T_f32 = CalcAvailComp(HwTrqFilt_HwNm_T_f32, AssistCmdFilt_HwNm_T_s8p7, VehSpd_Kph_T_u9p7);
	/** SF-12: Calculate Available Compensation - FDD BLOCK END **/

	RawHysComp_HwNm_T_f32 = CompAvail_HwNm_T_f32 * Fraction_Uls_T_f32;


	/**
	* SF-12: Filter and Limit Output - FDD BLOCK BEGIN
	**/

	/* SF12: 1LP1-B Filter1 */
	HysComp_HwNm_T_f32 = LPF_OpUpdate_f32_m(RawHysComp_HwNm_T_f32, &RawHystCompLPFiltSV_HwNm_M_str);

	HysComp_HwNm_T_f32 = Limit_m(HysComp_HwNm_T_f32, -k_HysOutLIm_HwNm_f32, k_HysOutLIm_HwNm_f32);

	/* SF12: HW2Motor */
	HysComp_MtrNm_T_f32 = HysComp_HwNm_T_f32 / k_CmnSysTrqRatio_HwNmpMtrNm_f32;

	/* SF12: Switch */
	if (FALSE != DefeatHystService_Cnt_lgc)
	{
		HysComp_MtrNm_T_f32 = D_ZERO_ULS_F32;
	}
	/** SF-12: Filter and Limit Output - FDD BLOCK END **/

	AstCmdLastUsed_HwNm_M_s8p7 = AssistCmdFilt_HwNm_T_s8p7;
	HwTrqLastUsed_HwNm_M_f32 = HwTrqFilt_HwNm_T_f32;
	Fraction_Uls_M_f32 = Fraction_Uls_T_f32; 		/* HysComp_Fraction */
	RawCalc_HwNm_M_f32 = RawHysComp_HwNm_T_f32; 	/* HysComp_RawCalc */
	CompAvail_HwNm_D_f32 = CompAvail_HwNm_T_f32; 	/* HysComp_CompAvail */

	HysComp_MtrNm_T_f32 = Limit_m(HysComp_MtrNm_T_f32, -D_HYSOUTLMT_MTRNM_F32, D_HYSOUTLMT_MTRNM_F32);

	/* Fault Injection Point */
	#if(STD_ON == BC_HYSTCOMP_FAULTINJECTIONPOINT)
	Rte_Call_FltInjection_SCom_FltInjection(&HysComp_MtrNm_T_f32,FLTINJ_HYSTCOMP);
	#endif

	Rte_IWrite_HystComp_Per1_HysteresisComp_MtrNm_f32(HysComp_MtrNm_T_f32);
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_HystComp_Per1_CP1_CheckpointReached();

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_HYSTCOMP_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
STATIC INLINE FUNC(sint16, AP_HYSTCOMP_CODE) MoreCompensation(	VAR(float32, AUTOMATIC) TrqChange_HwNm_T_f32,
															CONSTP2VAR(float32, AUTOMATIC, AP_HYSTCOMP_CONST) RiseXPtr_HwNm_T_f32)
{
	VAR(sint16, AUTOMATIC) RiseX_HwNm_T_s1p14;
	VAR(sint16, AUTOMATIC) RiseY_Uls_T_s1p14;
	VAR(float32, AUTOMATIC) RiseX_HwNm_T_f32;

	RiseX_HwNm_T_f32 = TrqChange_HwNm_T_f32 + *RiseXPtr_HwNm_T_f32;

	RiseX_HwNm_T_f32 = Limit_m(	RiseX_HwNm_T_f32,
										-(FPM_FixedToFloat_m((t_HysRiseTblX_HwNm_u2p14[TableSize_m(t_HysRiseTblX_HwNm_u2p14)-1U]),u2p14_T)),
										(FPM_FixedToFloat_m((t_HysRiseTblX_HwNm_u2p14[TableSize_m(t_HysRiseTblX_HwNm_u2p14)-1U]),u2p14_T)));


	RiseX_HwNm_T_s1p14 = FPM_FloatToFixed_m(RiseX_HwNm_T_f32, s1p14_T);
	RiseY_Uls_T_s1p14 = (sint16)IntplVarXY_u16_u16Xu16Y_Cnt(t_HysRiseTblX_HwNm_u2p14,
															t_HysRiseTblY_Uls_u2p14,
															TableSize_m(t_HysRiseTblX_HwNm_u2p14),
															Abs_s16_m(RiseX_HwNm_T_s1p14));

	RiseY_Uls_T_s1p14 = RiseY_Uls_T_s1p14 * Sign_s16_m(RiseX_HwNm_T_s1p14);

	/* Write calculated RiseX to passed buffer location and return Rise Y*/
	*RiseXPtr_HwNm_T_f32 = RiseX_HwNm_T_f32;
	return(RiseY_Uls_T_s1p14);
}

STATIC INLINE FUNC(float32, AP_HYSTCOMP_CODE) LessCompensation(	VAR(float32, AUTOMATIC) TrqChange_HwNm_T_f32,
																VAR(float32, AUTOMATIC) PrevRiseY_Uls_T_f32,
																CONSTP2VAR(float32, AUTOMATIC, AP_HYSTCOMP_CONST) RiseXPtr_HwNm_T_f32)
{
	VAR(float32, AUTOMATIC) RiseY_Uls_T_f32;
	VAR(sint16, AUTOMATIC) RiseX_HwNm_T_s1p14;
	VAR(float32, AUTOMATIC) ModTrqChange_Uls_T_f32;
	VAR(float32, AUTOMATIC) RiseX_HwNm_T_f32;

	ModTrqChange_Uls_T_f32 =  TrqChange_HwNm_T_f32 * k_HysRevGain_InvHwNm_f32;

	if(Abs_f32_m(ModTrqChange_Uls_T_f32) < Abs_f32_m(PrevRiseY_Uls_T_f32))
	{
		RiseY_Uls_T_f32 = PrevRiseY_Uls_T_f32 + ModTrqChange_Uls_T_f32;

		RiseY_Uls_T_f32 = Limit_m(	RiseY_Uls_T_f32,
												-(FPM_FixedToFloat_m((t_HysRiseTblY_Uls_u2p14[TableSize_m(t_HysRiseTblY_Uls_u2p14)-1U]),u2p14_T)),
												(FPM_FixedToFloat_m((t_HysRiseTblY_Uls_u2p14[TableSize_m(t_HysRiseTblY_Uls_u2p14)-1U]),u2p14_T)));


		RiseX_HwNm_T_s1p14 = (sint16)IntplVarXY_u16_u16Xu16Y_Cnt(t_HysRiseTblY_Uls_u2p14,
																t_HysRiseTblX_HwNm_u2p14,
																TableSize_m(t_HysRiseTblX_HwNm_u2p14),
																Abs_s16_m(FPM_FloatToFixed_m(RiseY_Uls_T_f32, s1p14_T)));

		RiseX_HwNm_T_s1p14 = RiseX_HwNm_T_s1p14 * Sign_f32_m(RiseY_Uls_T_f32);

		RiseX_HwNm_T_f32 = FPM_FixedToFloat_m(RiseX_HwNm_T_s1p14, s1p14_T);
	}
	else
	{
		RiseX_HwNm_T_f32 = (PrevRiseY_Uls_T_f32 / k_HysRevGain_InvHwNm_f32) + TrqChange_HwNm_T_f32;

		RiseX_HwNm_T_f32 = Limit_m( RiseX_HwNm_T_f32,
									-(FPM_FixedToFloat_m((t_HysRiseTblX_HwNm_u2p14[TableSize_m(t_HysRiseTblX_HwNm_u2p14)-1U]),u2p14_T )),
									(FPM_FixedToFloat_m((t_HysRiseTblX_HwNm_u2p14[TableSize_m(t_HysRiseTblX_HwNm_u2p14)-1U]), u2p14_T)));

		RiseX_HwNm_T_s1p14 = FPM_FloatToFixed_m(RiseX_HwNm_T_f32, s1p14_T);
		RiseY_Uls_T_f32 = FPM_FixedToFloat_m(
								IntplVarXY_u16_u16Xu16Y_Cnt(t_HysRiseTblX_HwNm_u2p14,
															t_HysRiseTblY_Uls_u2p14,
															TableSize_m(t_HysRiseTblX_HwNm_u2p14),
															Abs_s16_m((RiseX_HwNm_T_s1p14))),
								u2p14_T);

		RiseY_Uls_T_f32 = RiseY_Uls_T_f32 * (float32)Sign_s16_m(RiseX_HwNm_T_s1p14);

	}

	/* Write calculated RiseX to passed buffer location and return Rise Y*/
	*RiseXPtr_HwNm_T_f32 = RiseX_HwNm_T_f32;
	return(RiseY_Uls_T_f32);
}


STATIC FUNC(float32, AP_HYSTCOMP_CODE) CalcAvailComp(	VAR(float32, AUTOMATIC) HwTrqFilt_HwNm_T_f32,
														VAR(sint16, AUTOMATIC) AssistCmdFilt_HwNm_T_s8p7,
														VAR(uint16, AUTOMATIC) VehSpd_Kph_T_u9p7)
{
	VAR(float32, AUTOMATIC) AbsCombinedTrq_HwNm_T_f32;
	VAR(float32, AUTOMATIC) EffOff_HwNm_T_f32;
	VAR(float32, AUTOMATIC) EffLoss_Uls_T_f32;
	VAR(float32, AUTOMATIC) HysTrq_HwNm_T_f32;
	VAR(float32, AUTOMATIC) HysBlend_Uls_T_f32;
	VAR(float32, AUTOMATIC) WIROffFric_HwNm_T_f32;
	VAR(float32, AUTOMATIC) WIROnFric_HwNm_T_f32;
	VAR(float32, AUTOMATIC) CoulFricHysBlend_HwNm_T_f32;
	VAR(float32, AUTOMATIC) HysNegBlend_Uls_T_f32;
	VAR(float32, AUTOMATIC) TempScale_HwNm_T_f32;
	VAR(float32, AUTOMATIC) CoulFric_HwNm_T_f32;
	VAR(float32, AUTOMATIC) HysSat_HwNm_T_f32;
	VAR(float32, AUTOMATIC) HysNegBlndCmp_HwNm_T_f32;
	VAR(uint16, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_u8p8;
	VAR(float32, AUTOMATIC) WIRCmdBlnd_Uls_T_f32;
	VAR(float32, AUTOMATIC) HysNegComp_HwNm_T_f32;
	VAR(float32, AUTOMATIC) WIRFric_HwNm_T_f32;
	VAR(sint16, AUTOMATIC) AssistMechTempEst_DegC_T_s14p1;
	VAR(float32, AUTOMATIC) CompAvail_HwNm_T_f32;
	VAR(uint16, AUTOMATIC) AbsHwTrqFilt_HwNm_T_u4p12;

	WIRCmdAmpBlnd_MtrNm_u8p8 = FPM_FloatToFixed_m(Rte_IRead_HystComp_Per1_WIRCmdAmpBlnd_MtrNm_f32(), u8p8_T);
	AssistMechTempEst_DegC_T_s14p1 = FPM_FloatToFixed_m(Rte_IRead_HystComp_Per1_AssistMechTempEst_DegC_f32(), s14p1_T);

	EffOff_HwNm_T_f32 = FPM_FixedToFloat_m(
							IntplVarXY_u16_u16Xu16Y_Cnt(t_CmnVehSpd_Kph_u9p7,
														t_EffOffTblY_HwNm_u9p7,
														TableSize_m(t_CmnVehSpd_Kph_u9p7),
														VehSpd_Kph_T_u9p7),
							u9p7_T);

	AbsCombinedTrq_HwNm_T_f32 = Abs_f32_m(HwTrqFilt_HwNm_T_f32 + FPM_FixedToFloat_m(AssistCmdFilt_HwNm_T_s8p7, s8p7_T));

	EffLoss_Uls_T_f32 = FPM_FixedToFloat_m(
							IntplVarXY_u16_u16Xu16Y_Cnt(	t_CmnVehSpd_Kph_u9p7,
															t_EffLossTblY_Uls_u4p12,
															TableSize_m(t_CmnVehSpd_Kph_u9p7),
															VehSpd_Kph_T_u9p7),
							u4p12_T);

	HysTrq_HwNm_T_f32 = (AbsCombinedTrq_HwNm_T_f32 - EffOff_HwNm_T_f32);

	HysTrq_HwNm_T_f32 = Max_m(HysTrq_HwNm_T_f32, D_ZERO_ULS_F32);

	HysTrq_HwNm_T_f32 = HysTrq_HwNm_T_f32 * EffLoss_Uls_T_f32;

	EffCompTrq_HwNm_D_f32 = HysTrq_HwNm_T_f32;

	/*Coulomb Friction */

	WIROffFric_HwNm_T_f32 = FPM_FixedToFloat_m(
								IntplVarXY_u16_u16Xu16Y_Cnt(	t_CmnVehSpd_Kph_u9p7,
																t_HysCompCoulFricY_HwNm_u9p7[D_WIROFF_IDX_U16],
																TableSize_m(t_CmnVehSpd_Kph_u9p7),
																VehSpd_Kph_T_u9p7),
								u9p7_T);

	WIROnFric_HwNm_T_f32  = FPM_FixedToFloat_m(
								IntplVarXY_u16_u16Xu16Y_Cnt(	t_CmnVehSpd_Kph_u9p7,
																t_HysCompCoulFricY_HwNm_u9p7[D_WIRON_IDX_U16],
																TableSize_m(t_CmnVehSpd_Kph_u9p7),
																VehSpd_Kph_T_u9p7),
								u9p7_T);

	WIRCmdBlnd_Uls_T_f32  = FPM_FixedToFloat_m(
								IntplVarXY_u16_u16Xu16Y_Cnt(	t_HysCompCoulFricWIRBlendX_MtrNm_u8p8,
																t_HysCompCoulFricWIRBlendY_Uls_u2p14,
																TableSize_m(t_HysCompCoulFricWIRBlendX_MtrNm_u8p8),
																WIRCmdAmpBlnd_MtrNm_u8p8),
								u2p14_T);

	WIROnFric_HwNm_T_f32 = WIROnFric_HwNm_T_f32 * WIRCmdBlnd_Uls_T_f32;
	WIROffFric_HwNm_T_f32 = WIROffFric_HwNm_T_f32 * (D_WIRCMDBLNDFRC_ULS_F32 - WIRCmdBlnd_Uls_T_f32);

	WIRFric_HwNm_T_f32 = WIROnFric_HwNm_T_f32 + WIROffFric_HwNm_T_f32;

	TempScale_HwNm_T_f32  = FPM_FixedToFloat_m(
								IntplVarXY_u16_s16Xu16Y_Cnt(	t_HysCompCoulFricTempScaleX_DegC_s14p1,
																t_HysCompCoulFricTempScaleY_HwNm_u9p7,
																TableSize_m(t_HysCompCoulFricTempScaleX_DegC_s14p1),
																AssistMechTempEst_DegC_T_s14p1),
								u9p7_T);

	CoulFric_HwNm_T_f32 = TempScale_HwNm_T_f32 * WIRFric_HwNm_T_f32;

	CoulFric_HwNm_T_f32 = CoulFric_HwNm_T_f32 + Rte_IRead_HystComp_Per1_FricOffset_HwNm_f32();


	CoulFric_HwNm_D_f32 = CoulFric_HwNm_T_f32;

	/* Saturation */

	HysSat_HwNm_T_f32 = FPM_FixedToFloat_m(
							IntplVarXY_u16_u16Xu16Y_Cnt(	t_CmnVehSpd_Kph_u9p7,
														t_HysCompHysSatY_HwNm_u9p7,
														TableSize_m(t_CmnVehSpd_Kph_u9p7),
														VehSpd_Kph_T_u9p7),
							u9p7_T);

	CoulFric_HwNm_T_f32 = CoulFric_HwNm_T_f32 + HysTrq_HwNm_T_f32;
	CoulFric_HwNm_T_f32 = Limit_m(CoulFric_HwNm_T_f32 , D_HYSSATLOWLMT_HWNM_F32, HysSat_HwNm_T_f32);
	/* Saturation block ends  */
	/*Handwheel trq table*/
	AbsHwTrqFilt_HwNm_T_u4p12 = FPM_FloatToFixed_m(Abs_f32_m(HwTrqFilt_HwNm_T_f32), u4p12_T);
	HysBlend_Uls_T_f32 = FPM_FixedToFloat_m(BilinearXMYM_u16_u16XMu16YM_Cnt(
								VehSpd_Kph_T_u9p7,
								AbsHwTrqFilt_HwNm_T_u4p12,
								t_CmnVehSpd_Kph_u9p7,
								TableSize_m(t_CmnVehSpd_Kph_u9p7),
								(P2CONST(uint16, AUTOMATIC, AP_HYSTCOMP_CONST))t2_HysHwTrqBlndTblX_HwNm_u4p12,
								(P2CONST(uint16, AUTOMATIC, AP_HYSTCOMP_CONST))t2_HysHwTrqBlndTblY_Uls_u4p12,
								TableSize_m(t2_HysHwTrqBlndTblX_HwNm_u4p12[0])),u4p12_T);



	CoulFricHysBlend_HwNm_T_f32 = HysBlend_Uls_T_f32 * CoulFric_HwNm_T_f32;
	PosAvail_HwNm_D_f32 = CoulFricHysBlend_HwNm_T_f32;

	HysNegBlend_Uls_T_f32 = FPM_FixedToFloat_m(
								IntplVarXY_u16_u16Xu16Y_Cnt(t_HysCompNegHysBlendX_HwNm_u9p7,
															t_HysCompNegHysBlendY_Uls_u2p14,
															TableSize_m(t_HysCompNegHysBlendX_HwNm_u9p7),
															Abs_s16_m(AssistCmdFilt_HwNm_T_s8p7)),
								u2p14_T);

	HysNegComp_HwNm_T_f32 = FPM_FixedToFloat_m(
								IntplVarXY_u16_u16Xu16Y_Cnt(t_HysCompNegHysCompX_MtrNm_u8p8,
															t_HysCompNegHysCompY_HwNm_u9p7,
															TableSize_m(t_HysCompNegHysCompX_MtrNm_u8p8),
															WIRCmdAmpBlnd_MtrNm_u8p8),
								u9p7_T);

	HysNegBlndCmp_HwNm_T_f32 = HysNegBlend_Uls_T_f32 * HysNegComp_HwNm_T_f32;

	NegAvail_HwNm_D_f32 = HysNegBlndCmp_HwNm_T_f32;
	CompAvail_HwNm_T_f32 = CoulFricHysBlend_HwNm_T_f32 - HysNegBlndCmp_HwNm_T_f32;

	return(CompAvail_HwNm_T_f32);
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
