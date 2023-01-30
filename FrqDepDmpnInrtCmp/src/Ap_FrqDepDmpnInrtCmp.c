/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_FrqDepDmpnInrtCmp.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/FrqDepDmpnInrtCmp-nzt9hv/FrqDepDmpnInrtCmp/autosar
 *     SW-C Type:  Ap_FrqDepDmpnInrtCmp
 *  Generated at:  Thu Feb  7 16:55:53 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_FrqDepDmpnInrtCmp>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Sat Sep 24 11:57:09 2011
 * %version:          13 %
 * %derived_by:       gzkys7 %
 * %date_modified:    Fri Apr 12 16:44:19 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 11/23/11  1        KJS       Initial component based design release. 
 * 01/10/12  4		  KJS		Anomaly 2787 correction															4793
 * 01/13/12	 5		  KJS		Anomaly 2799 correction
 * 01/27/12  6		  KJS		Correction in FilterCoefCalc for InertiaCompCalc_MtrNm_T_f32 calc	A_2855
 * 05/02/12  7        NRAR      FaultInjectionPoint added
 * 08/09/12  8        NRAR      Added changes missed from FDD Ver003 Anom 3613                                  5965
 * 09/19/12  9        SSK       Checkpoint added                                                                6244
 * 02/08/13  10,11    Selva     Updated to version 5 FDD SF-14                                                            
 * 04/12/13  12       JJW       Corrected interpolations, anomaly 4775                                                            
 * 08/29/14  13       SB		Anomaly 6259 correction															12390
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_FrqDepDmpnInrtCmp.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_FrqDepDmpnInrtCmp_Cfg.h"
#include "fixmath.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "filters.h"
#include "interpolation.h"


#define D_FLOATONE_ULS_F32					1.0F
#define D_FLOATEIGHT_ULS_F32				8.0F
#define D_FLOATTWO_ULS_F32					2.0F
#define D_FLOATFOUR_ULS_F32					4.0F
#define D_ATTENTBLMININPUT_MTRRADPS_F32		0.0F
#define D_ATTENTBLMAXINPUT_MTRRADPS_F32		4095.9375F

typedef struct {
      float32 b0_Uls_f32;
	  float32 b1_Uls_f32;
	  float32 b2_Uls_f32;
	  float32 a0_Uls_f32;
	  float32 a1_Uls_f32;
	  float32 a2_Uls_f32;
}filterCoef_T;



#define FRQDEPDMPNINRTCMP_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* Display variables */
STATIC volatile VAR(float32, AUTOMATIC) DriverVelocity_MtrRadpS_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) ADDCoef_MtrNmSpRad_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) FDDAttenOut_MtrNm_D_f32; 
STATIC volatile VAR(float32, AUTOMATIC) InertiaCompCalc_MtrNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) FiltFreqLUBlnd_RadpS_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) TbarVelFiltVal_HwDegpSec_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) RawDecelGain_Uls_D_f32;

/* Module Internal */
STATIC VAR(float32, AUTOMATIC) PreDecelGain_Uls_M_f32;
STATIC VAR(float32, AUTOMATIC) PrevTbarAng_HwDeg_M_f32;
STATIC VAR(float32, AUTOMATIC) Prev1SclDrvVel_RadpS_M_f32;
STATIC VAR(float32, AUTOMATIC) Prev2SclDrvVel_RadpS_M_f32;
STATIC VAR(float32, AUTOMATIC) Prev1PreAttnComp_MtrNm_M_f32;
STATIC VAR(float32, AUTOMATIC) Prev2PreAttnComp_MtrNm_M_f32;
#define FRQDEPDMPNINRTCMP_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" 

#define FRQDEPDMPNINRTCMP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
STATIC VAR(LPF32KSV_Str, FRQDEPDMPNINRTCMP_VAR) TbarVelFiltSv_M_str;
#define FRQDEPDMPNINRTCMP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"


STATIC FUNC(float32, AP_FRQDEPDMPNINRTCMP_CODE) DriverVelCalc(  VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32,
																VAR(float32, AUTOMATIC) CRFMotorVel_MtrRadpS_T_f32,
																VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32 );

STATIC FUNC(float32, AP_FRQDEPDMPNINRTCMP_CODE) ADDCoefCalc( VAR(float32, AUTOMATIC) BaseAssistCmd_MtrNm_T_f32,
															 VAR(float32, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_f32,
															 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32 );

STATIC FUNC(void, AP_FRQDEPDMPNINRTCMP_CODE) FilterCoefCalc( VAR(float32, AUTOMATIC) ADDCoef_MtrNmSpRad_T_f32, 
															 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32, 
															 VAR(float32, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_f32, 
															 CONSTP2VAR(filterCoef_T, AUTOMATIC, AUTOMATIC) filtCoef_Uls_T_Str);

STATIC FUNC(float32, AP_FRQDEPDMPNINRTCMP_CODE) GenFddIcCmd( VAR(float32, AUTOMATIC) ScaledDriverVel_MtrRadpS_T_f32, 
																  CONSTP2CONST(filterCoef_T, AUTOMATIC, AUTOMATIC) filtCoef_Uls_T_Str);

STATIC FUNC(float32, AP_FRQDEPDMPNINRTCMP_CODE) DecelGain( VAR(float32, AUTOMATIC) VehicleLonAccel_KphpS_T_f32, 
															 VAR(float32, AUTOMATIC) CRFMotorVel_MtrRadpS_T_f32) ;

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
 *   FLTINJ_VECU_BATTERYVOLTAGE (8u)
 *   FLTINJ_HYSTCOMP (12u)
 *   FLTINJ_INERTIACOMP (14u)
 *   FLTINJ_EOTDAMPING_ETDMPFW (27u)
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
 * Float: D_2PI_ULS_F32 = 6.2831853071796
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_PIOVR180_ULS_F32 = 0.0174532925199
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_FRQDEPDMPNINRTCMP_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: FrqDepDmpnInrtCmp_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_FRQDEPDMPNINRTCMP_APPL_CODE) FrqDepDmpnInrtCmp_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: FrqDepDmpnInrtCmp_Init
 *********************************************************************************************************************/
	PreDecelGain_Uls_M_f32 = D_FLOATONE_ULS_F32;
	LPF_Init_f32_m(0.0f, k_InrtCmp_TBarVelLPFKn_Hz_f32, D_2MS_SEC_F32, &TbarVelFiltSv_M_str);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: FrqDepDmpnInrtCmp_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <DISABLE>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_FrqDepDmpnInrtCmp_Per1_BaseAssistCmd_MtrNm_f32(void)
 *   Float Rte_IRead_FrqDepDmpnInrtCmp_Per1_CRFMotorVel_MtrRadpS_f32(void)
 *   Boolean Rte_IRead_FrqDepDmpnInrtCmp_Per1_FreqDepDmpSrlComSvcDft_Cnt_lgc(void)
 *   Float Rte_IRead_FrqDepDmpnInrtCmp_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_FrqDepDmpnInrtCmp_Per1_VehicleLonAccel_KphpS_f32(void)
 *   Float Rte_IRead_FrqDepDmpnInrtCmp_Per1_VehicleSpeed_Kph_f32(void)
 *   Float Rte_IRead_FrqDepDmpnInrtCmp_Per1_WIRCmdAmpBlnd_MtrNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_FrqDepDmpnInrtCmp_Per1_FrqDepDmpnInrtCmp_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_FrqDepDmpnInrtCmp_Per1_FrqDepDmpnInrtCmp_MtrNm_f32(void)
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FltInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_FRQDEPDMPNINRTCMP_APPL_CODE) FrqDepDmpnInrtCmp_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: FrqDepDmpnInrtCmp_Per1
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32;
	VAR(float32, AUTOMATIC) CRFMotorVel_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) BaseAssistCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;
	VAR(float32, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_f32;
	VAR(boolean, AUTOMATIC) FDDDefSrvFlg_Cnt_T_lgc;

	VAR(float32, AUTOMATIC) FrqDepDmpnInrtCmp_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) ADDCoef_MtrNmSpRad_T_f32;
	VAR(float32, AUTOMATIC) ScaledDriverVel_MtrRadpS_T_f32;
	VAR(filterCoef_T, AUTOMATIC) FilterCoef_T_Str;
	VAR(float32, AUTOMATIC) VehicleLonAccel_KphpS_T_f32;
	VAR(float32, AUTOMATIC) DecelGain_Uls_T_f32;
/*
	FilterCoef_T_Str.b0_Uls_f32 = 0;
	FilterCoef_T_Str.b1_Uls_f32 = 0;
	FilterCoef_T_Str.b2_Uls_f32 = 0;
	FilterCoef_T_Str.a0_Uls_f32 = 0;
	FilterCoef_T_Str.a1_Uls_f32 = 0;
	FilterCoef_T_Str.a2_Uls_f32 = 0;*/
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_FrqDepDmpnInrtCmp_Per1_CP0_CheckpointReached();

	#ifdef RTE_INIT_IMPLICIT_BUFFERS
		Rte_IWrite_FrqDepDmpnInrtCmp_Per1_FrqDepDmpnInrtCmp_MtrNm_f32(Rte_InitValue_FrqDepDmpnInrtCmp_MtrNm_f32);
	#endif

	HwTorque_HwNm_T_f32 = Rte_IRead_FrqDepDmpnInrtCmp_Per1_HwTorque_HwNm_f32();
	CRFMotorVel_MtrRadpS_T_f32 = Rte_IRead_FrqDepDmpnInrtCmp_Per1_CRFMotorVel_MtrRadpS_f32();
	BaseAssistCmd_MtrNm_T_f32 = Rte_IRead_FrqDepDmpnInrtCmp_Per1_BaseAssistCmd_MtrNm_f32();
	VehicleSpeed_Kph_T_f32 = Rte_IRead_FrqDepDmpnInrtCmp_Per1_VehicleSpeed_Kph_f32();
	WIRCmdAmpBlnd_MtrNm_T_f32 = Rte_IRead_FrqDepDmpnInrtCmp_Per1_WIRCmdAmpBlnd_MtrNm_f32();
	FDDDefSrvFlg_Cnt_T_lgc = Rte_IRead_FrqDepDmpnInrtCmp_Per1_FreqDepDmpSrlComSvcDft_Cnt_lgc();
	VehicleLonAccel_KphpS_T_f32 = Rte_IRead_FrqDepDmpnInrtCmp_Per1_VehicleLonAccel_KphpS_f32();
	/* Calc ADD Coefficient */
	ADDCoef_MtrNmSpRad_T_f32 = ADDCoefCalc(BaseAssistCmd_MtrNm_T_f32, WIRCmdAmpBlnd_MtrNm_T_f32, VehicleSpeed_Kph_T_f32);
	DecelGain_Uls_T_f32 = DecelGain( VehicleLonAccel_KphpS_T_f32, CRFMotorVel_MtrRadpS_T_f32);
	ADDCoef_MtrNmSpRad_T_f32  = ADDCoef_MtrNmSpRad_T_f32 *  DecelGain_Uls_T_f32;
	ADDCoef_MtrNmSpRad_D_f32 = ADDCoef_MtrNmSpRad_T_f32; /* Update display variable */
	
	/* Calc Scaled Driver Velocity */
	ScaledDriverVel_MtrRadpS_T_f32 = DriverVelCalc(HwTorque_HwNm_T_f32, CRFMotorVel_MtrRadpS_T_f32, VehicleSpeed_Kph_T_f32);

	/* Calc Filter Coef */
	FilterCoefCalc(ADDCoef_MtrNmSpRad_T_f32, VehicleSpeed_Kph_T_f32, WIRCmdAmpBlnd_MtrNm_T_f32, &FilterCoef_T_Str);
	
	/* Generate Command */
	FrqDepDmpnInrtCmp_MtrNm_T_f32 = GenFddIcCmd(ScaledDriverVel_MtrRadpS_T_f32, &FilterCoef_T_Str);

	if (FDDDefSrvFlg_Cnt_T_lgc == TRUE)
	{
		FrqDepDmpnInrtCmp_MtrNm_T_f32 = D_ZERO_ULS_F32;
	}

	FrqDepDmpnInrtCmp_MtrNm_T_f32 = Limit_m( FrqDepDmpnInrtCmp_MtrNm_T_f32, -D_MTRTRQCMDHILMT_MTRNM_F32, D_MTRTRQCMDHILMT_MTRNM_F32);


	/* Fault Injection Point */
	#if(STD_ON == BC_FREQDEPDAMPING_FAULTINJECTIONPOINT)
	Rte_Call_FltInjection_SCom_FltInjection(&FrqDepDmpnInrtCmp_MtrNm_T_f32,FLTINJ_INERTIACOMP);
	#endif
	
	Rte_IWrite_FrqDepDmpnInrtCmp_Per1_FrqDepDmpnInrtCmp_MtrNm_f32(FrqDepDmpnInrtCmp_MtrNm_T_f32);
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_FrqDepDmpnInrtCmp_Per1_CP1_CheckpointReached();
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_FRQDEPDMPNINRTCMP_APPL_CODE
#include "MemMap.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function: DriverVelCalc
 * 
 * Inputs: Hw_Torque, Motor_Vel_CRF, Vehicle_Speed
 * 
 * Outputs: Scaled Driver Velocity
 * 
 **********************************************************************************************************************/
STATIC FUNC(float32, AP_FRQDEPDMPNINRTCMP_CODE) DriverVelCalc(  VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32,
																VAR(float32, AUTOMATIC) CRFMotorVel_MtrRadpS_T_f32,
																VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32 )
{
	VAR(float32, AUTOMATIC) ScaledDriverVel_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) TbarAngle_HwDeg_T_f32;
	VAR(float32, AUTOMATIC) TbarVel_HwDegpSec_T_f32;
	
	VAR(float32, AUTOMATIC) TbarVel_MtrRadpSec_T_f32;
	VAR(float32, AUTOMATIC) TbarVel_ScaleFactor_Uls_T_f32;
	VAR(float32, AUTOMATIC) TbarVelFiltVal_HwDegpSec_T_f32;
	VAR(uint16, AUTOAMTIC) VehicleSpeed_Kph_T_u9p7;

	
	VehicleSpeed_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);

	TbarAngle_HwDeg_T_f32 = HwTorque_HwNm_T_f32 / k_CmnTbarStiff_NmpDeg_f32;
	TbarVel_HwDegpSec_T_f32 = (TbarAngle_HwDeg_T_f32 - PrevTbarAng_HwDeg_M_f32) / D_2MS_SEC_F32;
	
	PrevTbarAng_HwDeg_M_f32 = TbarAngle_HwDeg_T_f32; /* Update previous Tbar value */


	TbarVelFiltVal_HwDegpSec_T_f32 = LPF_OpUpdate_f32_m(TbarVel_HwDegpSec_T_f32, &TbarVelFiltSv_M_str);
	TbarVelFiltVal_HwDegpSec_D_f32 = TbarVelFiltVal_HwDegpSec_T_f32;
	
	TbarVel_MtrRadpSec_T_f32 = ((TbarVelFiltVal_HwDegpSec_T_f32 * D_PIOVR180_ULS_F32) * k_CmnSysKinRatio_MtrDegpHwDeg_f32);

	DriverVelocity_MtrRadpS_D_f32 = TbarVel_MtrRadpSec_T_f32 + CRFMotorVel_MtrRadpS_T_f32; /* Update Display Variable */

	
	TbarVel_ScaleFactor_Uls_T_f32 = FPM_FixedToFloat_m( IntplVarXY_u16_u16Xu16Y_Cnt(t_CmnVehSpd_Kph_u9p7, 
																				t_InrtCmp_TBarVel_ScaleFactorTblY_Uls_u9p7, 
																				TableSize_m(t_CmnVehSpd_Kph_u9p7),
																				VehicleSpeed_Kph_T_u9p7), u9p7_T);	

	ScaledDriverVel_MtrRadpS_T_f32 = (TbarVel_MtrRadpSec_T_f32 * TbarVel_ScaleFactor_Uls_T_f32) + (CRFMotorVel_MtrRadpS_T_f32 * k_InrtCmp_MtrVel_ScaleFactor_Uls_f32);

	return(ScaledDriverVel_MtrRadpS_T_f32);
}

/**********************************************************************************************************************
 * Function: ADDCoefCalc
 * 
 * Inputs: Base Assist Cmd, Vehicle_Speed, WIRCmdAmpBlnd
 * 
 * Outputs: ADD Coefficient 
 * 
 **********************************************************************************************************************/
STATIC FUNC(float32, AP_FRQDEPDMPNINRTCMP_CODE) ADDCoefCalc( VAR(float32, AUTOMATIC) BaseAssistCmd_MtrNm_T_f32,
															 VAR(float32, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_f32,
															 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32 )
{
	VAR(float32, AUTOMATIC) ADDCoefCalc_MtrNmSpRad_T_f32;
	VAR(float32, AUTOMATIC) AbsBaseAssistCmd_MtrNm_T_f32;
	VAR(uint16, AUTOMATIC) AbsBaseAssistCmd_MtrNm_T_u4p12;
	VAR(uint16, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_u8p8;
	VAR(uint16, AUTOMATIC) VehicleSpeed_Kph_T_u9p7;
	
	VAR(float32, AUTOMATIC) RollingFDD0_MtrNmSpRad_T_f32;
	VAR(float32, AUTOMATIC) RollingFDD1_MtrNmSpRad_T_f32;
	VAR(float32, AUTOMATIC) StaticFDD_MtrNmSpRad_T_f32;
	VAR(float32, AUTOMATIC) RIAstWIRBlnd_MtrNmSpRad_T_f32;
	VAR(float32, AUTOMATIC) FDDBlnd_Uls_T_f32;
	VAR(float32, AUTOMATIC) FinRollingFDD_MtrNmSpRad_T_f32;
	
	AbsBaseAssistCmd_MtrNm_T_f32 = Abs_f32_m(BaseAssistCmd_MtrNm_T_f32);
	AbsBaseAssistCmd_MtrNm_T_u4p12 = FPM_FloatToFixed_m(AbsBaseAssistCmd_MtrNm_T_f32, u4p12_T);
	WIRCmdAmpBlnd_MtrNm_T_u8p8 = FPM_FloatToFixed_m(WIRCmdAmpBlnd_MtrNm_T_f32, u8p8_T);
	VehicleSpeed_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
	
	RollingFDD0_MtrNmSpRad_T_f32 = FPM_FixedToFloat_m( IntplVarXY_u16_u16Xu16Y_Cnt(t_DmpADDCoefX_MtrNm_u4p12, 
																					t2_FDD_ADDRollingTblYM_MtrNmpRadpS_um1p17[0], 
																					TableSize_m(t_DmpADDCoefX_MtrNm_u4p12),
																					AbsBaseAssistCmd_MtrNm_T_u4p12), um1p17_T);
	
	RollingFDD1_MtrNmSpRad_T_f32 = FPM_FixedToFloat_m( IntplVarXY_u16_u16Xu16Y_Cnt(t_DmpADDCoefX_MtrNm_u4p12, 
																					t2_FDD_ADDRollingTblYM_MtrNmpRadpS_um1p17[1], 
																					TableSize_m(t_DmpADDCoefX_MtrNm_u4p12),
																					AbsBaseAssistCmd_MtrNm_T_u4p12), um1p17_T);
	
	StaticFDD_MtrNmSpRad_T_f32 = FPM_FixedToFloat_m( IntplVarXY_u16_u16Xu16Y_Cnt(t_DmpADDCoefX_MtrNm_u4p12, 
																					t_FDD_ADDStaticTblY_MtrNmpRadpS_um1p17, 
																					TableSize_m(t_DmpADDCoefX_MtrNm_u4p12),
																					AbsBaseAssistCmd_MtrNm_T_u4p12), um1p17_T);
	
	RIAstWIRBlnd_MtrNmSpRad_T_f32 = FPM_FixedToFloat_m( IntplVarXY_u16_u16Xu16Y_Cnt(t_WIRBlndTblX_MtrNm_u8p8, 
																					t_RIAstWIRBlndTblY_Uls_u2p14, 
																					TableSize_m(t_WIRBlndTblX_MtrNm_u8p8),
																					WIRCmdAmpBlnd_MtrNm_T_u8p8), u2p14_T);
	
	FDDBlnd_Uls_T_f32 = FPM_FixedToFloat_m( IntplVarXY_u16_u16Xu16Y_Cnt(t_CmnVehSpd_Kph_u9p7, 
																		t_FDD_BlendTblY_Uls_u8p8, 
																		TableSize_m(t_CmnVehSpd_Kph_u9p7),
																		VehicleSpeed_Kph_T_u9p7), u8p8_T);	
	
	FinRollingFDD_MtrNmSpRad_T_f32 = (RollingFDD1_MtrNmSpRad_T_f32 * RIAstWIRBlnd_MtrNmSpRad_T_f32) + (RollingFDD0_MtrNmSpRad_T_f32 * (D_ONE_ULS_F32 - RIAstWIRBlnd_MtrNmSpRad_T_f32));
	
	ADDCoefCalc_MtrNmSpRad_T_f32 = (FinRollingFDD_MtrNmSpRad_T_f32 * FDDBlnd_Uls_T_f32) + (StaticFDD_MtrNmSpRad_T_f32 * (D_ONE_ULS_F32 - FDDBlnd_Uls_T_f32));

	return(ADDCoefCalc_MtrNmSpRad_T_f32);
}

/**********************************************************************************************************************
 * Function: DecelGain
 * 
 * Inputs: Motor_Vel_CRF, VehicleLonAccel									
 * 
 * Outputs: DecelGain
 * 
 **********************************************************************************************************************/
STATIC FUNC(float32, AP_FRQDEPDMPNINRTCMP_CODE) DecelGain( VAR(float32, AUTOMATIC) VehicleLonAccel_KphpS_T_f32, 
															 VAR(float32, AUTOMATIC) CRFMotorVel_MtrRadpS_T_f32) 
															 
															 
{

VAR(float32, AUTOMATIC) RawDecelGain_Uls_T_f32 ;
VAR(float32, AUTOMATIC) DecelGain_Uls_T_f32;
VAR(float32, AUTOMATIC) MaxDecelGain_UlspS_T_f32;
VAR(uint16, AUTOMATIC) CRFMotorVel_MtrRadpS_T_u11p5;

/*** Calc Decelgain ***/
	if ( -VehicleLonAccel_KphpS_T_f32 > k_DmpGainOnThresh_KphpS_f32 )
		{
		RawDecelGain_Uls_T_f32 = k_DmpDecelGain_Uls_f32;
		}
	else if ( -VehicleLonAccel_KphpS_T_f32 < k_DmpGainOffThresh_KphpS_f32)
		{
		RawDecelGain_Uls_T_f32 = D_ONE_ULS_F32;
		}

	else
		{
		RawDecelGain_Uls_T_f32 =  PreDecelGain_Uls_M_f32;
		}

RawDecelGain_Uls_D_f32	= RawDecelGain_Uls_T_f32;
/*** Calc Decelgain ***/
	
CRFMotorVel_MtrRadpS_T_u11p5 = FPM_FloatToFixed_m((Abs_f32_m(CRFMotorVel_MtrRadpS_T_f32)),u11p5_T);

MaxDecelGain_UlspS_T_f32 = FPM_FixedToFloat_m(IntplVarXY_u16_u16Xu16Y_Cnt(t_DmpDecelGainSlewX_MtrRadpS_u11p5, 
																				t_DmpDecelGainSlewY_UlspS_u13p3, 
																				TableSize_m(t_DmpDecelGainSlewX_MtrRadpS_u11p5),
																				CRFMotorVel_MtrRadpS_T_u11p5), u13p3_T);
/***Rate limiter***/																				
DecelGain_Uls_T_f32= Limit_m(RawDecelGain_Uls_T_f32, (D_2MS_SEC_F32 * -k_DmpDecelGainFSlew_UlspS_f32)+ PreDecelGain_Uls_M_f32, (D_2MS_SEC_F32 * MaxDecelGain_UlspS_T_f32)+ PreDecelGain_Uls_M_f32);

PreDecelGain_Uls_M_f32 = DecelGain_Uls_T_f32;
return (DecelGain_Uls_T_f32);

}

/**********************************************************************************************************************

 * Function: FilterCoefCalc
 * 
 * Inputs: ADDCoef_MtrNmSpRad_T_f32, Vehicle_Speed, WIRCmdAmpBlnd, *FilterCoef_T_Str
 * 
 * Outputs: Create filter coefs (b0 -> b2, a0 -> a2)
 * 
 **********************************************************************************************************************/
STATIC FUNC(void, AP_FRQDEPDMPNINRTCMP_CODE) FilterCoefCalc( VAR(float32, AUTOMATIC) ADDCoef_MtrNmSpRad_T_f32, 
															 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32, 
															 VAR(float32, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_f32, 
															 CONSTP2VAR(filterCoef_T, AUTOMATIC, AUTOMATIC) filtCoef_Uls_T_Str)
{
	VAR(uint16, AUTOMATIC)	VehicleSpeed_Kph_T_u9p7;
	VAR(uint16, AUTOMATIC)  WIRCmdAmpBlnd_MtrNm_T_u8p8;

	VAR(float32, AUTOMATIC) FreqFilt0_Hz_T_f32;
	VAR(float32, AUTOMATIC) FreqFilt1_Hz_T_f32;
	VAR(float32, AUTOMATIC) DampFiltKpWIR_Hz_T_f32;
	VAR(float32, AUTOMATIC) FiltFreqLUBlnd_RadpS_T_f32;
	VAR(float32, AUTOMATIC) InrtCmpScaleFactor_Uls_T_f32;
	VAR(float32, AUTOMATIC)	FiltFreqLUBlnd_RadSqpSSq_T_f32;
	VAR(float32, AUTOMATIC) FiltFreqLUBlndSqrt_RadpS_T_f32;
	VAR(float32, AUTOMATIC) InertiaCompCalc_MtrNm_T_f32;

	VAR(float32, AUTOMATIC)	filtCoefA0TmpCalc_Uls_T_f32;
	VAR(float32, AUTOMATIC)	filtCoefA1TmpCalc_Uls_T_f32;
	VAR(float32, AUTOMATIC)	filtCoefA2TmpCalc_Uls_T_f32;
	VAR(float32, AUTOMATIC)	filtCoefAxTmpCalc_Uls_T_f32;

	VAR(float32, AUTOMATIC) filtCoefBx1TmpCalc_Uls_T_f32;
	VAR(float32, AUTOMATIC) filtCoefBx2TmpCalc_Uls_T_f32;
	VAR(float32, AUTOMATIC) filtCoefBx3TmpCalc_Uls_T_f32;



	VehicleSpeed_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
	WIRCmdAmpBlnd_MtrNm_T_u8p8 = FPM_FloatToFixed_m(WIRCmdAmpBlnd_MtrNm_T_f32, u8p8_T);

	/* Filter feq lookup and blending */
	FreqFilt0_Hz_T_f32 = FPM_FixedToFloat_m( IntplVarXY_u16_u16Xu16Y_Cnt(t_CmnVehSpd_Kph_u9p7, 
																		t2_FDD_FreqTblYM_Hz_u12p4[0], 
																		TableSize_m(t_CmnVehSpd_Kph_u9p7),
																		VehicleSpeed_Kph_T_u9p7), u12p4_T);	

	FreqFilt1_Hz_T_f32 = FPM_FixedToFloat_m( IntplVarXY_u16_u16Xu16Y_Cnt(t_CmnVehSpd_Kph_u9p7, 
																		t2_FDD_FreqTblYM_Hz_u12p4[1], 
																		TableSize_m(t_CmnVehSpd_Kph_u9p7),
																		VehicleSpeed_Kph_T_u9p7), u12p4_T);

	DampFiltKpWIR_Hz_T_f32 = FPM_FixedToFloat_m( IntplVarXY_u16_u16Xu16Y_Cnt(t_WIRBlndTblX_MtrNm_u8p8, 
																		t_DmpFiltKpWIRBlndY_Uls_u2p14, 
																		TableSize_m(t_WIRBlndTblX_MtrNm_u8p8),
																		WIRCmdAmpBlnd_MtrNm_T_u8p8), u2p14_T);

	/* FDD value [w] */
	FiltFreqLUBlnd_RadpS_T_f32 = D_2PI_ULS_F32 * ( (FreqFilt1_Hz_T_f32 * DampFiltKpWIR_Hz_T_f32) + (FreqFilt0_Hz_T_f32 * (D_ONE_ULS_F32 - DampFiltKpWIR_Hz_T_f32)) );
	FiltFreqLUBlnd_RadpS_D_f32 = FiltFreqLUBlnd_RadpS_T_f32; /* Update display varialbe */

	
	InrtCmpScaleFactor_Uls_T_f32 = FPM_FixedToFloat_m( IntplVarXY_u16_u16Xu16Y_Cnt(t_CmnVehSpd_Kph_u9p7, 
																		t_InrtCmp_ScaleFactorTblY_Uls_u9p7, 
																		TableSize_m(t_CmnVehSpd_Kph_u9p7),
																		VehicleSpeed_Kph_T_u9p7), u9p7_T);

	FiltFreqLUBlnd_RadSqpSSq_T_f32 = (FiltFreqLUBlnd_RadpS_T_f32 * FiltFreqLUBlnd_RadpS_T_f32) + D_ONE_ULS_F32; 
	FiltFreqLUBlndSqrt_RadpS_T_f32 = sqrtf(FiltFreqLUBlnd_RadSqpSSq_T_f32); 

	/* FDD value [k] */
	InertiaCompCalc_MtrNm_T_f32 = InrtCmpScaleFactor_Uls_T_f32 * FiltFreqLUBlnd_RadSqpSSq_T_f32 * ((ADDCoef_MtrNmSpRad_T_f32 / FiltFreqLUBlndSqrt_RadpS_T_f32) + k_InrtCmp_MtrInertia_KgmSq_f32);
	InertiaCompCalc_MtrNm_D_f32 = InertiaCompCalc_MtrNm_T_f32; /* Update display variable */

	/* B Terms */
	filtCoefBx1TmpCalc_Uls_T_f32 = InertiaCompCalc_MtrNm_T_f32 * D_2MS_SEC_F32;
	filtCoefBx2TmpCalc_Uls_T_f32 = D_2MS_SEC_F32 * ADDCoef_MtrNmSpRad_T_f32 * FiltFreqLUBlnd_RadpS_T_f32;
	filtCoefBx3TmpCalc_Uls_T_f32 = ADDCoef_MtrNmSpRad_T_f32 * D_FLOATTWO_ULS_F32;

	/* b0 Calc */
	filtCoef_Uls_T_Str->b0_Uls_f32 = (filtCoefBx2TmpCalc_Uls_T_f32 - filtCoefBx1TmpCalc_Uls_T_f32 - filtCoefBx3TmpCalc_Uls_T_f32) * D_FLOATTWO_ULS_F32;
	
	/* b1 Calc */
	filtCoef_Uls_T_Str->b1_Uls_f32 = ADDCoef_MtrNmSpRad_T_f32 * D_FLOATEIGHT_ULS_F32;

	/* b2 Calc */
	filtCoef_Uls_T_Str->b2_Uls_f32 = (filtCoefBx1TmpCalc_Uls_T_f32 - filtCoefBx2TmpCalc_Uls_T_f32 - filtCoefBx3TmpCalc_Uls_T_f32) * D_FLOATTWO_ULS_F32;


	/* A terms */
	filtCoefAxTmpCalc_Uls_T_f32 = (FiltFreqLUBlnd_RadpS_T_f32 * D_2MS_SEC_F32);

	/* a0 TmpCalc */
	filtCoefA0TmpCalc_Uls_T_f32 = filtCoefAxTmpCalc_Uls_T_f32 - D_FLOATTWO_ULS_F32;
	filtCoefA0TmpCalc_Uls_T_f32 = filtCoefA0TmpCalc_Uls_T_f32 * filtCoefA0TmpCalc_Uls_T_f32;
	filtCoef_Uls_T_Str->a0_Uls_f32 = filtCoefA0TmpCalc_Uls_T_f32;
	
	/* a1 TmpCalc */
	filtCoefA1TmpCalc_Uls_T_f32 = ((filtCoefAxTmpCalc_Uls_T_f32 * filtCoefAxTmpCalc_Uls_T_f32) - D_FLOATFOUR_ULS_F32) * D_FLOATTWO_ULS_F32;
	filtCoef_Uls_T_Str->a1_Uls_f32 = filtCoefA1TmpCalc_Uls_T_f32;
	
	/* a2 TmpCalc */
	filtCoefA2TmpCalc_Uls_T_f32 = filtCoefAxTmpCalc_Uls_T_f32 + D_FLOATTWO_ULS_F32;
	filtCoefA2TmpCalc_Uls_T_f32 = filtCoefA2TmpCalc_Uls_T_f32 * filtCoefA2TmpCalc_Uls_T_f32;
	filtCoef_Uls_T_Str->a2_Uls_f32 = filtCoefA2TmpCalc_Uls_T_f32;

}


/**********************************************************************************************************************
 * Function: GenFddIcCmd
 * 
 * Inputs: ScaledDriverVel_MtrRadpS_T_f32, *FilterCoef_T_Str
 * 
 * Outputs: Compenstation_MtrNm_T_f32;
 * 
 **********************************************************************************************************************/
STATIC FUNC(float32, AP_FRQDEPDMPNINRTCMP_CODE) GenFddIcCmd( VAR(float32, AUTOMATIC) ScaledDriverVel_MtrRadpS_T_f32, 
																 CONSTP2CONST(filterCoef_T, AUTOMATIC, AUTOMATIC) filtCoef_Uls_T_Str)
{
	VAR(float32, AUTOMATIC) Compenstation_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) PreAttnComp_MtrNm_T_f32;

	VAR(uint16, AUTOMATIC) LimScaledDriverVel_MtrRadpS_T_u12p4;
	VAR(float32, AUTOMATIC) FDDAtten_Uls_T_f32; 

	VAR(float32, AUTOMATIC) GenCmdB0_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) GenCmdB1_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) GenCmdB2_MtrNm_T_f32;
	
	VAR(float32, AUTOMATIC) GenCmdAx_Uls_T_f32;
	VAR(float32, AUTOMATIC) LimScaledDriverVel_MtrRadpS_T_f32; 


	/* limited value only used for the lookup, floating point used in the rest of the function */
	LimScaledDriverVel_MtrRadpS_T_f32 = Limit_m(Abs_f32_m(ScaledDriverVel_MtrRadpS_T_f32), D_ATTENTBLMININPUT_MTRRADPS_F32, D_ATTENTBLMAXINPUT_MTRRADPS_F32);
	
	LimScaledDriverVel_MtrRadpS_T_u12p4 = FPM_FloatToFixed_m(LimScaledDriverVel_MtrRadpS_T_f32, u12p4_T);
	FDDAtten_Uls_T_f32 = FPM_FixedToFloat_m( IntplVarXY_u16_u16Xu16Y_Cnt(t_FDD_AttenTblX_MtrRadpS_u12p4, 
																		t_FDD_AttenTblY_Uls_u8p8, 
																		TableSize_m(t_FDD_AttenTblX_MtrRadpS_u12p4),
																		LimScaledDriverVel_MtrRadpS_T_u12p4), u8p8_T);

	FDDAttenOut_MtrNm_D_f32 = FDDAtten_Uls_T_f32; /* Update display variable */
	
	GenCmdB0_MtrNm_T_f32 = filtCoef_Uls_T_Str->b0_Uls_f32* Prev2SclDrvVel_RadpS_M_f32;
	GenCmdB1_MtrNm_T_f32 = filtCoef_Uls_T_Str->b1_Uls_f32 * Prev1SclDrvVel_RadpS_M_f32;
	GenCmdB2_MtrNm_T_f32 = filtCoef_Uls_T_Str->b2_Uls_f32 * ScaledDriverVel_MtrRadpS_T_f32;

	GenCmdAx_Uls_T_f32 = (Prev1PreAttnComp_MtrNm_M_f32 * filtCoef_Uls_T_Str->a1_Uls_f32) + (Prev2PreAttnComp_MtrNm_M_f32 * filtCoef_Uls_T_Str->a0_Uls_f32);
	

	PreAttnComp_MtrNm_T_f32 = ((GenCmdB0_MtrNm_T_f32 + GenCmdB1_MtrNm_T_f32 + GenCmdB2_MtrNm_T_f32) - GenCmdAx_Uls_T_f32) / filtCoef_Uls_T_Str->a2_Uls_f32;
	
	
	/* Update previous values */
	Prev2SclDrvVel_RadpS_M_f32 = Prev1SclDrvVel_RadpS_M_f32;
	Prev1SclDrvVel_RadpS_M_f32 = ScaledDriverVel_MtrRadpS_T_f32;
	Prev2PreAttnComp_MtrNm_M_f32 = Prev1PreAttnComp_MtrNm_M_f32;
	Prev1PreAttnComp_MtrNm_M_f32 = PreAttnComp_MtrNm_T_f32;

	Compenstation_MtrNm_T_f32 = PreAttnComp_MtrNm_T_f32 * FDDAtten_Uls_T_f32;

	return(Compenstation_MtrNm_T_f32);
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
