/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_Damping.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/Damping-nzt9hv/Damping/autosar
 *     SW-C Type:  Ap_Damping
 *  Generated at:  Thu Oct  3 17:59:11 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_Damping>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          17 %
 * %derived_by:       nzt9hv %
 * %date_modified:    Thu Oct  3 14:23:51 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/13/11  5        LWW       Added Rolling Assist Damping and Filter Kp Blending interface
 * 11/08/11  6        LWW       Component template updates for FDD SF-03 rev003 implementation
 * 11/15/11  7        VK        CBD based on FDD SF-03 rev003 requirements
 * 11/18/11  8        VK		Merged version 7 and 6.1.1
 * 11/29/11  9        VK        UTP fixes
 * 09/16/12  11       BWL       Added watchdog checkpoints                                                      6218
 * 09/19/12  12       Selva     Corrected watchdog checkpoints
 * 09/24/12  13       Selva     Corrected watchdog checkpoints again                                            6218
 * 10/25/12  14       OT        Implemented SF-03 v006
 * 02/21/13  15       Selva     Implemented SF-03 v007
 * 04/25/13  16       Jared     Update to FDD ver 008                                                           7898
 * 10/04/13  17       Selva     Update to FDD ver 009                                                           10274
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_Damping.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "fixmath.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "filters.h"
#include "interpolation.h"
#include "Ap_Damping_Cfg.h"


#define D_DAMPINGCMDMIN_MTRNM_F32			(-8.8F)
#define D_DAMPINGCMDMAX_MTRNM_F32			  8.8F


#define DAMPING_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(LPF32KSV_Str, AP_DAMPING_VAR) QDDHwTorqueLPFKSV_Cnt_M_str;
STATIC VAR(LPF32KSV_Str, AP_DAMPING_VAR) QDDMtrVelLPFKSV_Cnt_M_str;
STATIC VAR(LPF32KSV_Str, AP_DAMPING_VAR) QDDStFilt_Cnt_M_str;
STATIC VAR(LPF32KSV_Str, AP_DAMPING_VAR) MtrVelLPFKSV_Cnt_M_str;
#define DAMPING_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


#define DAMPING_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, AP_DAMPING_VAR) QDDHwTrqBkLash_HwNm_M_f32;
STATIC VAR(float32, AP_DAMPING_VAR) QDDMtrVelBckLash_MtrRadpS_M_f32;
STATIC volatile VAR(float32, AP_DAMPING_VAR) QDDStFilt_Uls_D_f32;
STATIC volatile VAR(float32, AP_DAMPING_VAR) DampMtrVelDmp_MtrNm_D_f32;
STATIC volatile VAR(float32, AP_DAMPING_VAR) DampHPSc1_Uls_D_f32;
STATIC volatile VAR(float32, AP_DAMPING_VAR) DampHPSc2_Uls_D_f32;
STATIC volatile VAR(float32, AP_DAMPING_VAR) DampHPSc3_Uls_D_f32;
STATIC volatile VAR(float32, AP_DAMPING_VAR) DampHPSc4_Uls_D_f32;
STATIC volatile VAR(float32, AP_DAMPING_VAR) DampHPSDmp_MtrNm_D_f32;
#define DAMPING_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define DAMPING_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(uint16, AP_DAMPING_VAR) DampTrqScale_Uls_D_u1p15;
STATIC volatile VAR(uint16, AP_DAMPING_VAR) DampTempScale_Uls_D_u4p12;
#define DAMPING_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */


STATIC FUNC(float32, AP_DAMPING_CODE) MtrVelDepDampScale(VAR(float32, AUTOMATIC) MotorVelCRF_MtrRadpS_T_f32,
														 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32,
														 VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32,
														 VAR(float32, AUTOMATIC) TempScale_Uls_T_f32
														);

STATIC FUNC(float32, AP_DAMPING_CODE) HPSDampingFn(VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32,
												   VAR(float32, AUTOMATIC) TempScale_Uls_T_f32,
												   VAR(float32, AUTOMATIC) BaseAssistStCmp_MtrNm_T_f32,
												   VAR(float32, AUTOMATIC) MotorVelCRF_MtrRadpS_T_f32
												  );


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
 * Double: Real in interval ]-DBL_MAX...DBL_MAX[ with double precision including NaN (standard type)
 * Float: Real in interval ]-FLT_MAX...FLT_MAX[ with single precision (standard type)
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * SInt32: Integer in interval [-2147483648...2147483647] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
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
 * Boolean: D_TRUE_CNT_LGC = TRUE
 * Double: D_SFINVMILLI_ULS_F32 = 1000
 * Float: D_180OVRPI_ULS_F32 = 57.295779513082
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_2PI_ULS_F32 = 6.2831853071796
 * Float: D_MSECPERSEC_ULS_F32 = 1000
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_PIOVR180_ULS_F32 = 0.0174532925199
 * Float: D_PI_ULS_F32 = 3.1415926535898
 * Float: D_RADPERREV_ULS_F32 = 6.28318530718
 * Float: D_VECUMIN_VOLTS_F32 = 5
 * Float: D_ZERO_ULS_F32 = 0
 * SInt16: D_NEGONE_CNT_S16 = -1
 * SInt16: D_ONE_CNT_S16 = 1
 * SInt16: D_ZERO_CNT_S16 = 0
 * SInt32: D_NEGONE_CNT_S32 = -1
 * SInt32: D_ONE_CNT_S32 = 1
 * SInt32: D_ZERO_CNT_S32 = 0
 * SInt8: D_NEGONE_CNT_S8 = -1
 * SInt8: D_ONE_CNT_S8 = 1
 * SInt8: D_ZERO_CNT_S8 = 0
 * UInt16: D_ONE_CNT_U16 = 1u
 * UInt16: D_ZERO_CNT_U16 = 0u
 * UInt32: D_ONE_CNT_U32 = 1u
 * UInt32: D_ZERO_CNT_U32 = 0u
 * UInt8: D_MTRPOLESDIV2_CNT_U8 = 3u
 * UInt8: D_ONE_CNT_U8 = 1u
 * UInt8: D_QUADRANT1_CNT_U8 = 1u
 * UInt8: D_QUADRANT2_CNT_U8 = 2u
 * UInt8: D_QUADRANT3_CNT_U8 = 3u
 * UInt8: D_QUADRANT4_CNT_U8 = 4u
 * UInt8: D_ZERO_CNT_U8 = 0u
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_DAMPING_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Damping_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_DAMPING_APPL_CODE) Damping_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Damping_Init1
 *********************************************************************************************************************/


	LPF_KUpdate_f32_m(k_QddHwTrqDampKn_Hz_f32, D_2MS_SEC_F32, &QDDHwTorqueLPFKSV_Cnt_M_str);
	LPF_KUpdate_f32_m(k_QddMtrVelDampKn_Hz_f32, D_2MS_SEC_F32, &QDDMtrVelLPFKSV_Cnt_M_str);
	LPF_KUpdate_f32_m(k_QddSfLFPKn_Hz_f32, D_2MS_SEC_F32, &QDDStFilt_Cnt_M_str);
	LPF_KUpdate_f32_m(k_MtrVelDampLPFKn_Hz_f32, D_2MS_SEC_F32, &MtrVelLPFKSV_Cnt_M_str);


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Damping_Per1
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
 *   Float Rte_IRead_Damping_Per1_AssistCmd_MtrNm_f32(void)
 *   Float Rte_IRead_Damping_Per1_AssistMechTempEst_DegC_f32(void)
 *   Float Rte_IRead_Damping_Per1_CustomDamp_MtrNm_f32(void)
 *   Float Rte_IRead_Damping_Per1_DampingDDFactor_Uls_f32(void)
 *   Boolean Rte_IRead_Damping_Per1_DefeatDampingSvc_Cnt_lgc(void)
 *   Float Rte_IRead_Damping_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_Damping_Per1_MotorVelCRF_MtrRadpS_f32(void)
 *   Float Rte_IRead_Damping_Per1_VehicleSpeed_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_Damping_Per1_DampingCmd_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_Damping_Per1_DampingCmd_MtrNm_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FltInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_DAMPING_APPL_CODE) Damping_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Damping_Per1
 *********************************************************************************************************************/


	VAR(float32, AUTOMATIC) AssistMechTempEst_DegC_T_f32;
 	VAR(float32, AUTOMATIC) BaseAssistStCmp_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DampingDDFactor_Uls_T_f32;
	VAR(boolean, AUTOMATIC) DefeatDampingSvc_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32;
	VAR(float32, AUTOMATIC) MotorVelCRF_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;
	VAR(float32, AUTOMATIC) ActiveDamping_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) HPSDampingCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DampingCmd_MtrNm_T_f32;
	VAR(sint16, AUTOMATIC) AssistMechTempEst_DegC_T_s8p7;
	VAR(uint16, AUTOMATIC) TempScale_Uls_T_u4p12;
	VAR(float32, AUTOMATIC) TempScale_Uls_T_f32;
	VAR(float32, AUTOMATIC) CustomDamp_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)	DampingCmdFilt_MtrRadpS_T_f32;
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_Damping_Per1_CP0_CheckpointReached();


	AssistMechTempEst_DegC_T_f32 = Rte_IRead_Damping_Per1_AssistMechTempEst_DegC_f32();
	BaseAssistStCmp_MtrNm_T_f32 = Rte_IRead_Damping_Per1_AssistCmd_MtrNm_f32();
	DampingDDFactor_Uls_T_f32 = Rte_IRead_Damping_Per1_DampingDDFactor_Uls_f32();
	DefeatDampingSvc_Cnt_T_lgc = Rte_IRead_Damping_Per1_DefeatDampingSvc_Cnt_lgc();
	HwTorque_HwNm_T_f32 = Rte_IRead_Damping_Per1_HwTorque_HwNm_f32();
	MotorVelCRF_MtrRadpS_T_f32 = Rte_IRead_Damping_Per1_MotorVelCRF_MtrRadpS_f32();
	VehicleSpeed_Kph_T_f32 = Rte_IRead_Damping_Per1_VehicleSpeed_Kph_f32();
	CustomDamp_MtrNm_T_f32 = Rte_IRead_Damping_Per1_CustomDamp_MtrNm_f32();

	AssistMechTempEst_DegC_T_s8p7 = FPM_FloatToFixed_m(AssistMechTempEst_DegC_T_f32, s8p7_T);

	/* Temperature Dependant Multiplier */
	TempScale_Uls_T_u4p12 = IntplVarXY_u16_s16Xu16Y_Cnt(	t_TempScaleX_DegC_s8p7,
															t_TempScaleY_Uls_u4p12,
															TableSize_m(t_TempScaleX_DegC_s8p7),
															AssistMechTempEst_DegC_T_s8p7
													   );
	TempScale_Uls_T_f32= FPM_FixedToFloat_m(TempScale_Uls_T_u4p12, u4p12_T);
	DampTempScale_Uls_D_u4p12 = TempScale_Uls_T_u4p12;    /* Display variable */

	ActiveDamping_MtrNm_T_f32 = MtrVelDepDampScale(MotorVelCRF_MtrRadpS_T_f32, VehicleSpeed_Kph_T_f32, HwTorque_HwNm_T_f32, TempScale_Uls_T_f32);
	HPSDampingCmd_MtrNm_T_f32 = HPSDampingFn(VehicleSpeed_Kph_T_f32, TempScale_Uls_T_f32, BaseAssistStCmp_MtrNm_T_f32, MotorVelCRF_MtrRadpS_T_f32);

	DampingCmd_MtrNm_T_f32 = ActiveDamping_MtrNm_T_f32 + HPSDampingCmd_MtrNm_T_f32;

	DampingCmd_MtrNm_T_f32 *= DampingDDFactor_Uls_T_f32;

	if( TRUE == DefeatDampingSvc_Cnt_T_lgc )
	{
		DampingCmd_MtrNm_T_f32 = D_ZERO_ULS_F32;
	}
	else 
	{
		DampingCmd_MtrNm_T_f32 = ((float32) Sign_f32_m(MotorVelCRF_MtrRadpS_T_f32)) * Max_m( Abs_f32_m(CustomDamp_MtrNm_T_f32) , Abs_f32_m(DampingCmd_MtrNm_T_f32) );
	}

	DampingCmdFilt_MtrRadpS_T_f32 = LPF_OpUpdate_f32_m(DampingCmd_MtrNm_T_f32, &MtrVelLPFKSV_Cnt_M_str);
	
	DampingCmd_MtrNm_T_f32 = Limit_m(DampingCmdFilt_MtrRadpS_T_f32, D_DAMPINGCMDMIN_MTRNM_F32, D_DAMPINGCMDMAX_MTRNM_F32);

	#if(STD_ON == BC_DAMPING_FAULTINJECTIONPOINT)
	Rte_Call_FltInjection_SCom_FltInjection(&DampingCmd_MtrNm_T_f32, FLTINJ_DAMPING);
	#endif

	Rte_IWrite_Damping_Per1_DampingCmd_MtrNm_f32(DampingCmd_MtrNm_T_f32);

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_Damping_Per1_CP1_CheckpointReached();


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_DAMPING_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

STATIC FUNC(float32, AP_DAMPING_CODE) MtrVelDepDampScale(VAR(float32, AUTOMATIC) MotorVelCRF_MtrRadpS_T_f32,
														 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32,
														 VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32,
														 VAR(float32, AUTOMATIC) TempScale_Uls_T_f32
													    )
{

	VAR(float32, AUTOMATIC) QDDHwTorqueFilt_HwNm_T_f32;
	VAR(float32, AUTOMATIC) QDDMotorVelCRFFilt_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) QDDStFiltInput_Uls_T_f32;
	VAR(float32, AUTOMATIC) QDDStFilt_Uls_T_f32;

	VAR(uint16,  AUTOMATIC) AbsMotorVelCRFFilt_MtrRadpS_T_u12p4;
	VAR(uint16,  AUTOMATIC) VehSpd_Kph_T_u9p7;
	VAR(uint16,  AUTOMATIC) HwVelDepDmp_MtrNm_T_u5p11;
	VAR(float32, AUTOMATIC) MtrVelDampingCmd_MtrNm_T_f32;

	VAR(uint16,  AUTOMATIC) HwTrq_HwNm_T_u8p8;
	VAR(uint16,  AUTOMATIC) HwTrqScaleDamping_Uls_T_u1p15;
	VAR(float32, AUTOMATIC) HwTrqScaleDamping_Uls_T_f32;

	VAR(float32, AUTOMATIC) ActiveDamping_MtrNm_T_f32;


	/** Motor Velocity Dependent Damping **/

	/* Enhanced QDD */

	QDDHwTorqueFilt_HwNm_T_f32 = LPF_OpUpdate_f32_m(HwTorque_HwNm_T_f32, &QDDHwTorqueLPFKSV_Cnt_M_str);

	QDDHwTrqBkLash_HwNm_M_f32 = Limit_m(QDDHwTrqBkLash_HwNm_M_f32,
										QDDHwTorqueFilt_HwNm_T_f32 - k_QDDHwTrqBckLash_HwNm_f32,
										QDDHwTorqueFilt_HwNm_T_f32 + k_QDDHwTrqBckLash_HwNm_f32);

	QDDMotorVelCRFFilt_MtrRadpS_T_f32 = LPF_OpUpdate_f32_m(MotorVelCRF_MtrRadpS_T_f32, &QDDMtrVelLPFKSV_Cnt_M_str);

	QDDMtrVelBckLash_MtrRadpS_M_f32 = Limit_m(QDDMtrVelBckLash_MtrRadpS_M_f32,
											  QDDMotorVelCRFFilt_MtrRadpS_T_f32 - k_QDDMtrVelBckLash_MtrRadpS_f32,
											  QDDMotorVelCRFFilt_MtrRadpS_T_f32 + k_QDDMtrVelBckLash_MtrRadpS_f32);

	if( (QDDHwTrqBkLash_HwNm_M_f32 * QDDMtrVelBckLash_MtrRadpS_M_f32) >= D_ZERO_ULS_F32 )
	{
		QDDStFiltInput_Uls_T_f32 = k_Quad13DmpMult_Uls_f32;
	}
	else
	{
		QDDStFiltInput_Uls_T_f32 = k_Quad24DmpMult_Uls_f32;
	}

	QDDStFilt_Uls_T_f32 = LPF_OpUpdate_f32_m(QDDStFiltInput_Uls_T_f32, &QDDStFilt_Cnt_M_str);
	QDDStFilt_Uls_D_f32 = QDDStFilt_Uls_T_f32;    /* Display variable */


	/* Damping Based on Motor Velocity */

	

	AbsMotorVelCRFFilt_MtrRadpS_T_u12p4 = FPM_FloatToFixed_m(Abs_f32_m(MotorVelCRF_MtrRadpS_T_f32), u12p4_T);
	VehSpd_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);

	HwVelDepDmp_MtrNm_T_u5p11 = BilinearXMYM_u16_u16XMu16YM_Cnt(VehSpd_Kph_T_u9p7,
																AbsMotorVelCRFFilt_MtrRadpS_T_u12p4,
																t_CmnVehSpd_Kph_u9p7,
																TableSize_m(t_CmnVehSpd_Kph_u9p7),
																t2_MtrVelDmpTblX_MtrRadpS_u12p4[0],
																t2_MtrVelDmpTblY_MtrNm_u5p11[0],
																TableSize_m(t2_MtrVelDmpTblX_MtrRadpS_u12p4[0]) );

	MtrVelDampingCmd_MtrNm_T_f32 = FPM_FixedToFloat_m(HwVelDepDmp_MtrNm_T_u5p11, u5p11_T) * ((float32)Sign_f32_m(MotorVelCRF_MtrRadpS_T_f32));
	DampMtrVelDmp_MtrNm_D_f32 = MtrVelDampingCmd_MtrNm_T_f32;    /* Display variable */


	/* Handwheel Torque Dependent Multiplier */

	HwTrq_HwNm_T_u8p8 = FPM_FloatToFixed_m(Abs_f32_m(HwTorque_HwNm_T_f32), u8p8_T);

	HwTrqScaleDamping_Uls_T_u1p15 = IntplVarXY_u16_u16Xu16Y_Cnt(t_HwTrqDmpTblX_HwNm_u8p8,
																t_HwTrqDmpTblY_Uls_u1p15,
																TableSize_m(t_HwTrqDmpTblX_HwNm_u8p8),
																HwTrq_HwNm_T_u8p8 );

	HwTrqScaleDamping_Uls_T_f32 = FPM_FixedToFloat_m(HwTrqScaleDamping_Uls_T_u1p15, u1p15_T);
	DampTrqScale_Uls_D_u1p15 = HwTrqScaleDamping_Uls_T_u1p15;    /* Display variable */


	ActiveDamping_MtrNm_T_f32 = QDDStFilt_Uls_T_f32 * HwTrqScaleDamping_Uls_T_f32 * TempScale_Uls_T_f32 * MtrVelDampingCmd_MtrNm_T_f32;


	return(ActiveDamping_MtrNm_T_f32);

}


STATIC FUNC(float32, AP_DAMPING_CODE) HPSDampingFn(VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32,
												   VAR(float32, AUTOMATIC) TempScale_Uls_T_f32,
												   VAR(float32, AUTOMATIC) BaseAssistStCmp_MtrNm_T_f32,
												   VAR(float32, AUTOMATIC) MotorVelCRF_MtrRadpS_T_f32
												  )
{

	VAR(uint16, AUTOMATIC) VehSpd_Kph_T_u9p7;
	VAR(uint16, AUTOMATIC) Cylinderln1Scaling_Uls_T_u4p12;
	VAR(float32, AUTOMATIC) Cylinderln1Scaling_Uls_T_f32;
	VAR(float32, AUTOMATIC) C1Term_Uls_T_f32;
	VAR(uint16, AUTOMATIC) Cylinderln2Scaling_Uls_T_u4p12;
	VAR(float32, AUTOMATIC) Cylinderln2Scaling_Uls_T_f32;
	VAR(float32, AUTOMATIC) C2Term_Uls_T_f32;
	VAR(uint16, AUTOMATIC) ValveFlw1Scaling_Uls_T_u4p12;
	VAR(float32, AUTOMATIC) ValveFlw1Scaling_Uls_T_f32;
	VAR(float32, AUTOMATIC) C3Term_Uls_T_f32;
	VAR(uint16, AUTOMATIC) ValveFlw2Scaling_Uls_T_u4p12;
	VAR(float32, AUTOMATIC) ValveFlw2Scaling_Uls_T_f32;
	VAR(float32, AUTOMATIC) C4Term_Uls_T_f32;
	VAR(uint16, AUTOMATIC) AsstLimitSclng_MtrNm_T_u4p12;
	VAR(float32, AUTOMATIC) AsstLimit_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) LimitedAssist_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DampingForceTrmA_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DampingForceTrmB_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DampingForce_MtrNm_T_f32;

	VehSpd_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);

	/* Applying scale factors to HPS based C1, C2, C3, C4 constants */
	Cylinderln1Scaling_Uls_T_u4p12 = IntplVarXY_u16_u16Xu16Y_Cnt(	t_CmnVehSpd_Kph_u9p7,
																	t_HPSscaleC1Y_Uls_u4p12,
																	TableSize_m(t_CmnVehSpd_Kph_u9p7),
																	VehSpd_Kph_T_u9p7
															    );
	Cylinderln1Scaling_Uls_T_f32 = FPM_FixedToFloat_m(Cylinderln1Scaling_Uls_T_u4p12, u4p12_T);

	C1Term_Uls_T_f32 = Cylinderln1Scaling_Uls_T_f32 * TempScale_Uls_T_f32 * k_HPSbaseC1_MtrNmpMtrRadpS_f32;
	DampHPSc1_Uls_D_f32 = C1Term_Uls_T_f32;  /* Display variable */

	Cylinderln2Scaling_Uls_T_u4p12 = IntplVarXY_u16_u16Xu16Y_Cnt(	t_CmnVehSpd_Kph_u9p7,
																	t_HPSscaleC2Y_Uls_u4p12,
																	TableSize_m(t_CmnVehSpd_Kph_u9p7),
																	VehSpd_Kph_T_u9p7
															    );
	Cylinderln2Scaling_Uls_T_f32 = FPM_FixedToFloat_m(Cylinderln2Scaling_Uls_T_u4p12, u4p12_T);

	C2Term_Uls_T_f32 = Cylinderln2Scaling_Uls_T_f32 * TempScale_Uls_T_f32 * k_HPSbaseC2_MtrNmpMtrRadpS_f32;
	DampHPSc2_Uls_D_f32 = C2Term_Uls_T_f32;  /* Display variable */

	ValveFlw1Scaling_Uls_T_u4p12 = IntplVarXY_u16_u16Xu16Y_Cnt(		t_CmnVehSpd_Kph_u9p7,
																	t_HPSscaleC3Y_Uls_u4p12,
																	TableSize_m(t_CmnVehSpd_Kph_u9p7),
																	VehSpd_Kph_T_u9p7
															  );
	ValveFlw1Scaling_Uls_T_f32 = FPM_FixedToFloat_m(ValveFlw1Scaling_Uls_T_u4p12, u4p12_T);

	C3Term_Uls_T_f32 = ValveFlw1Scaling_Uls_T_f32 * k_HPSbaseC3_MtrNmpMtrRadpS_f32;
	DampHPSc3_Uls_D_f32 = C3Term_Uls_T_f32;  /* Display variable */

	ValveFlw2Scaling_Uls_T_u4p12 = IntplVarXY_u16_u16Xu16Y_Cnt(		t_CmnVehSpd_Kph_u9p7,
																	t_HPSscaleC4Y_Uls_u4p12,
																	TableSize_m(t_CmnVehSpd_Kph_u9p7),
																	VehSpd_Kph_T_u9p7
															  );
	ValveFlw2Scaling_Uls_T_f32 = FPM_FixedToFloat_m(ValveFlw2Scaling_Uls_T_u4p12, u4p12_T);

	C4Term_Uls_T_f32 = ValveFlw2Scaling_Uls_T_f32 * k_HPSbaseC4_MtrNmpMtrRadpS_f32;
	DampHPSc4_Uls_D_f32 = C4Term_Uls_T_f32;  /* Display variable */

	/* Limit the effect of Assist */
	AsstLimitSclng_MtrNm_T_u4p12 = IntplVarXY_u16_u16Xu16Y_Cnt(		t_CmnVehSpd_Kph_u9p7,
																	t_HPSAsstLimY_MtrNm_u4p12,
																	TableSize_m(t_CmnVehSpd_Kph_u9p7),
																	VehSpd_Kph_T_u9p7
															  );
	AsstLimit_MtrNm_T_f32 = FPM_FixedToFloat_m(AsstLimitSclng_MtrNm_T_u4p12, u4p12_T);

	LimitedAssist_MtrNm_T_f32 = Limit_m(BaseAssistStCmp_MtrNm_T_f32, -AsstLimit_MtrNm_T_f32, AsstLimit_MtrNm_T_f32);

	/* Applying equation */
	DampingForceTrmA_MtrNm_T_f32 = ((Abs_f32_m(LimitedAssist_MtrNm_T_f32) * C3Term_Uls_T_f32) + C1Term_Uls_T_f32) * MotorVelCRF_MtrRadpS_T_f32;

	DampingForceTrmB_MtrNm_T_f32 = ((C2Term_Uls_T_f32 * ((float32)Sign_f32_m(MotorVelCRF_MtrRadpS_T_f32))) - (LimitedAssist_MtrNm_T_f32 * C4Term_Uls_T_f32)) * (MotorVelCRF_MtrRadpS_T_f32 * MotorVelCRF_MtrRadpS_T_f32);

	DampingForce_MtrNm_T_f32 = DampingForceTrmA_MtrNm_T_f32 + DampingForceTrmB_MtrNm_T_f32;

	DampingForce_MtrNm_T_f32 = Limit_m(DampingForce_MtrNm_T_f32, -k_HPSOutLimit_MtrNm_f32, k_HPSOutLimit_MtrNm_f32);
	DampHPSDmp_MtrNm_D_f32 = DampingForce_MtrNm_T_f32;  /* Display variable */

	return(DampingForce_MtrNm_T_f32);

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
