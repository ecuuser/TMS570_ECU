/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_Return.c
 *     Workspace:  C:/Synergy_projects/Return-lz4p8n/Return/autosar/Ap_Return.dcf
 *     SW-C Type:  Ap_Return
 *  Generated at:  Thu May 23 16:08:39 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_Return>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Wed Jun 14 09:14:52 2011
 * %version:          22 %
 * %derived_by:       lz4p8n %
 * %date_modified:    Thu May 23 13:43:11 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/01/11   4       JJW       Template update to provide access to Park Assist Scale Factor
 * 06/01/11   5       JJW       Template update to replace MtrVel port access with HwVel
 * 06/01/11   6       YY        Applied park-assist and driving-dynamics scale factors; replaced calculated  3611, 3648
 *                              handwheel velocity with new input.
 * 11/21/11   8       M. Story  Upgraded to FDD #SF-02 001H
 * 11/29/11   9       M. Story  Made fixes after componet project created and compiled.
 * 12/4/11    10     SMW        Updated calibration and temp variable to be signed for temperature values
 * 12/5/11    11     SMW        Updated component implementation to use the standard port definitions
 * 12/7/11    13      M. Story  Updated Globals based on UTP issue
 * 12/20/11   14      M. Story  Fixed Display variable issue
 * 1/14/12    15     SMW        Fixed issue with RTE accesss - source did not match model or template.
 * 4/16/12    16      M. Story  Anomaly 3155 changed Pim ReturnRange from Uin16 to float
 * 5/10/12    17      NRAR      changes as per FDD SF02 Ver 004
 * 5/16/12    18      NRAR      Anom Fix 3317 for RateLimiter logic
 * 5/16/12    19      BDO       Move EOLRtnRange_MtrNm_f32 from EEPROM to flash, adding k_RtnLimit_MtrNm_f32 CR5873
 * 09/23/12   20      Selva     Checkpoints added and mempmap macros corrected		                          	6244
 * 04/27/13   21      KJS	    Corrected anomaly 4893															8129
 * 05/23/13	  22	  SP		Update to Sf-02 ver 006															8352
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_Return.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "fixmath.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "interpolation.h"
#include "Ap_Return_Cfg.h"

#define D_RETURNCMDLOLMT_MTRNM_F32		(-8.8F)
#define D_RETURNCMDHILMT_MTRNM_F32		8.8F

#define RETURN_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, AUTOMATIC) HwPosReturnCmd_MtrNm_D_f32;
STATIC VAR(float32, AUTOMATIC) HwTrqReturnScl_Uls_D_f32;
STATIC VAR(float32, AUTOMATIC) HwVelReturnScl_Uls_D_f32;
STATIC VAR(float32, AUTOMATIC) TempReturnScl_Uls_D_f32;
STATIC VAR(float32, AUTOMATIC) CrntHandWheelAthScl_Uls_M_f32;
STATIC VAR(float32, AUTOMATIC) CurrentOffset_HwDeg_M_f32;
STATIC VAR(float32, AUTOMATIC) SgnHwPosReturn_HwDeg_D_f32;
STATIC VAR(float32, AUTOMATIC) RtrnBasicReturn_MtrNm_D_f32;

#define RETURN_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define RETURN_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, AUTOMATIC) AbsHwPosReturn_HwDeg_D_u12p4;
#define RETURN_STOP_SEC_VAR_CLEARED_16
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
 * Float: Real in interval [-FLT_MAX...FLT_MAX] with single precision (standard type)
 *
 * Enumeration Types:
 * ==================
 * FltInjectionLocType: Enumeration of integer in interval [0...255] with enumerators
 *   FLTINJ_ASSIST (1U)
 *   FLTINJ_RETURN (2U)
 *   FLTINJ_DAMPING (3U)
 *   FLTINJ_ASSTSUMNLMT (4U)
 *   FLTINJ_AVGFRICLRN (7U)
 *   FLTINJ_HYSTCOMP (12U)
 *   FLTINJ_INERTIACOMP (14U)
 *   FLTINJ_STABILITYCOMP (29U)
 *   FLTINJ_TRQBASEDINRTCOMP (30U)
 *   FLTINJ_SRLCOMVEHSPD_SGNLCOND (33U)
 *   FLTINJ_ASSTFIREWALL (34U)
 *   FLTINJ_ASSTEOTGAIN_LMTCOD (38U)
 *   FLTINJ_DDASTFACTRQST_DRVDYNCTRL (150U)
 *   FLTINJ_DDDMPFACTRQST_DRVDYNCTRL (151U)
 *   FLTINJ_DDRTNFACTRQST_DRVDYNCTRL (152U)
 *   FLTINJ_OUTPUTRAMPMULT_LMTCOD (153U)
 *   FLTINJ_ASSTEOTLIMIT_LMTCOD (154U)
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
 * Float: D_2MS_SEC_F32 = 0.002F
 * Float: D_ONE_ULS_F32 = 1.0F
 * Float: D_ZERO_ULS_F32 = 0.0F
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_RETURN_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Return_Per1
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
 *   Float Rte_IRead_Return_Per1_AssistMechTempEst_DegC_f32(void)
 *   Boolean Rte_IRead_Return_Per1_DefeatReturnSvc_Cnt_lgc(void)
 *   Boolean Rte_IRead_Return_Per1_DiagStsHwPosDis_Cnt_lgc(void)
 *   Float Rte_IRead_Return_Per1_HandwheelAuthority_Uls_f32(void)
 *   Float Rte_IRead_Return_Per1_HandwheelPosition_HwDeg_f32(void)
 *   Float Rte_IRead_Return_Per1_HandwheelVel_HwRadpS_f32(void)
 *   Float Rte_IRead_Return_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_Return_Per1_PAReturnSclFct_Uls_f32(void)
 *   Float Rte_IRead_Return_Per1_ReturnDDFactor_Uls_f32(void)
 *   Float Rte_IRead_Return_Per1_ReturnOffset_HwDeg_f32(void)
 *   Float Rte_IRead_Return_Per1_VehicleSpeed_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_Return_Per1_ReturnCmd_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_Return_Per1_ReturnCmd_MtrNm_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FltInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_RETURN_APPL_CODE) Return_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Return_Per1
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) HwVel_HwRadpS_T_f32;
	VAR(float32, AUTOMATIC) FinHwPosAuth_Uls_T_f32;
	VAR(float32, AUTOMATIC) FinHwPos_HwDeg_T_f32;
	VAR(float32, AUTOMATIC) HwTrq_HwNm_T_f32;
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(uint16, AUTOMATIC) VehSpd_Kph_T_u9p7;
	VAR(sint16, AUTOMATIC) FinHwPos_HwDeg_T_s11p4;
	VAR(sint16, AUTOMATIC) HwTrq_HwNm_T_s7p8;
	VAR(sint16, AUTOMATIC) HwVel_HwRadpS_T_s6p9;
	VAR(uint16, AUTOMATIC) HwPosReturnCmd_MtrNm_T_u5p11;
	VAR(uint16, AUTOMATIC) HwTrqReturnScl_Uls_T_u8p8;
	VAR(float32, AUTOMATIC) HwTrqReturnScl_Uls_T_f32;
	VAR(uint16, AUTOMATIC) HwVelReturnScl_Uls_T_u8p8;
	VAR(float32, AUTOMATIC) HwVelReturnScl_Uls_T_f32;
	VAR(float32, AUTOMATIC) ReturnCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DrvDynSclFct_Uls_T_f32;
	VAR(float32, AUTOMATIC) PrkAstSclFct_Uls_T_f32;
	VAR(float32, AUTOMATIC) AssistMechTempEst_T_DegC_f32;
	VAR(float32, AUTOMATIC) ReturnOffset_HwDeg_T_f32;
	VAR(uint16, AUTOMATIC) FinHwPosAuth_Uls_T_u8p8; 
	VAR(sint16, AUTOMATIC) AssistMechTempEst_DegC_T_s11p4; 
	VAR(uint16, AUTOMATIC) TempReturnScl_Uls_T_u8p8;
	VAR(float32, AUTOMATIC) TempReturnScl_Uls_f32;
	VAR(float32, AUTOMATIC) ScaledReturn_MtrNm_f32;
	VAR(uint16, AUTOMATIC) HandWheelAthScl_Uls_T_u9p7;
	VAR(boolean, AUTOMATIC) DiagStsHwPosDis_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) HwPosReturnCmd_MtrNm_T_f32;
	VAR(sint16, AUTOMATIC) 	CurrentOffset_HwDeg_T_s11p4;
	VAR(float32, AUTOMATIC) RtrnBasicReturn_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) HandWheelAthScl_Uls_T_f32;
	VAR(float32, AUTOMATIC) CrntHandWheelAthScl_Uls_T_f32;
	VAR(Boolean, AUTOMATIC) DefeatReturnSvc_Cnt_T_lgc;
	
    /* Configurable Start of Runnable Checkpoint */
	Rte_Call_Return_Per1_CP0_CheckpointReached();

	HwVel_HwRadpS_T_f32 = Rte_IRead_Return_Per1_HandwheelVel_HwRadpS_f32();
	FinHwPosAuth_Uls_T_f32 = Rte_IRead_Return_Per1_HandwheelAuthority_Uls_f32();
	FinHwPos_HwDeg_T_f32 = Rte_IRead_Return_Per1_HandwheelPosition_HwDeg_f32();
	HwTrq_HwNm_T_f32 = Rte_IRead_Return_Per1_HwTorque_HwNm_f32();
	ReturnOffset_HwDeg_T_f32 = Rte_IRead_Return_Per1_ReturnOffset_HwDeg_f32();
    AssistMechTempEst_T_DegC_f32 = Rte_IRead_Return_Per1_AssistMechTempEst_DegC_f32();
	DrvDynSclFct_Uls_T_f32 = Rte_IRead_Return_Per1_ReturnDDFactor_Uls_f32();
	PrkAstSclFct_Uls_T_f32 = Rte_IRead_Return_Per1_PAReturnSclFct_Uls_f32();	
	VehSpd_Kph_T_f32 = Rte_IRead_Return_Per1_VehicleSpeed_Kph_f32();
	DiagStsHwPosDis_Cnt_T_lgc = Rte_IRead_Return_Per1_DiagStsHwPosDis_Cnt_lgc();
	DefeatReturnSvc_Cnt_T_lgc = Rte_IRead_Return_Per1_DefeatReturnSvc_Cnt_lgc();
	
	VehSpd_Kph_T_u9p7 = FPM_FloatToFixed_m(VehSpd_Kph_T_f32, u9p7_T);
	FinHwPos_HwDeg_T_s11p4 = FPM_FloatToFixed_m(FinHwPos_HwDeg_T_f32, s11p4_T);
	HwTrq_HwNm_T_s7p8 = FPM_FloatToFixed_m(HwTrq_HwNm_T_f32, s7p8_T);
	HwVel_HwRadpS_T_s6p9 = FPM_FloatToFixed_m(HwVel_HwRadpS_T_f32, s6p9_T);
	FinHwPosAuth_Uls_T_u8p8 = FPM_FloatToFixed_m(FinHwPosAuth_Uls_T_f32, u8p8_T);
	AssistMechTempEst_DegC_T_s11p4 = FPM_FloatToFixed_m(AssistMechTempEst_T_DegC_f32, s11p4_T);


	ReturnOffset_HwDeg_T_f32 = Limit_m(ReturnOffset_HwDeg_T_f32, -k_RtnOffsetRange_HWDeg_f32, k_RtnOffsetRange_HWDeg_f32);


	/*Rate Limiter */
	CurrentOffset_HwDeg_M_f32  = Limit_m(ReturnOffset_HwDeg_T_f32,(CurrentOffset_HwDeg_M_f32 -(k_RtnOffsetSlew_HwDegpS_f32*D_2MS_SEC_F32 )), (CurrentOffset_HwDeg_M_f32+(k_RtnOffsetSlew_HwDegpS_f32*D_2MS_SEC_F32) ));

	CurrentOffset_HwDeg_T_s11p4 = FPM_FloatToFixed_m(CurrentOffset_HwDeg_M_f32, s11p4_T);


	FinHwPos_HwDeg_T_s11p4 = FinHwPos_HwDeg_T_s11p4 - CurrentOffset_HwDeg_T_s11p4;

	AbsHwPosReturn_HwDeg_D_u12p4 = (uint16)Abs_s16_m(FinHwPos_HwDeg_T_s11p4);
	SgnHwPosReturn_HwDeg_D_f32 = (float32)Sign_s16_m(FinHwPos_HwDeg_T_s11p4);
	
	HwPosReturnCmd_MtrNm_T_u5p11 = BilinearXMYM_u16_u16XMu16YM_Cnt(	VehSpd_Kph_T_u9p7, 
																	Abs_s16_m(FinHwPos_HwDeg_T_s11p4), 
																	t_ReturnVSpdTblBS_Kph_u9p7, 
																	TableSize_m(t_ReturnVSpdTblBS_Kph_u9p7), 
																	(P2CONST(uint16, AUTOMATIC, AP_RETURN_CONST))t2_ReturnPosTblXM_HwDeg_u12p4, 
																	(P2CONST(uint16, AUTOMATIC, AP_RETURN_CONST))t2_ReturnPosTblYM_MtrNm_u5p11, 
																	TableSize_m(t2_ReturnPosTblXM_HwDeg_u12p4[0]));

	HwPosReturnCmd_MtrNm_T_f32 = FPM_FixedToFloat_m(HwPosReturnCmd_MtrNm_T_u5p11, u5p11_T);
	
	HwTrqReturnScl_Uls_T_u8p8 = BilinearXMYM_u16_u16XMu16YM_Cnt(	VehSpd_Kph_T_u9p7, 
																	Abs_s16_m(HwTrq_HwNm_T_s7p8), 
																	t_ReturnVSpdTblBS_Kph_u9p7, 
																	TableSize_m(t_ReturnVSpdTblBS_Kph_u9p7), 
																	(P2CONST(uint16, AUTOMATIC, AP_RETURN_CONST))t2_ReturnSclTrqTblXM_HwNm_T_u8p8, 
																	(P2CONST(uint16, AUTOMATIC, AP_RETURN_CONST))t2_ReturnSclTrqTblYM_Uls_u8p8, 
																	TableSize_m(t2_ReturnSclTrqTblXM_HwNm_T_u8p8[0]));
																	
	HwTrqReturnScl_Uls_T_f32 = FPM_FixedToFloat_m(HwTrqReturnScl_Uls_T_u8p8, u8p8_T);
	
	HwVelReturnScl_Uls_T_u8p8 = BilinearXMYM_u16_u16XMu16YM_Cnt(	VehSpd_Kph_T_u9p7, 
																	Abs_s16_m(HwVel_HwRadpS_T_s6p9), 
																	t_ReturnVSpdTblBS_Kph_u9p7, 
																	TableSize_m(t_ReturnVSpdTblBS_Kph_u9p7), 
																	(P2CONST(uint16, AUTOMATIC, AP_RETURN_CONST))t2_ReturnSclVelTblXM_HwRadpS_T_u7p9, 
																	(P2CONST(uint16, AUTOMATIC, AP_RETURN_CONST))t2_ReturnSclVelTblYM_Uls_u8p8, 
																	TableSize_m(t2_ReturnSclVelTblXM_HwRadpS_T_u7p9[0]));
																	
	HwVelReturnScl_Uls_T_f32 = FPM_FixedToFloat_m(HwVelReturnScl_Uls_T_u8p8, u8p8_T);	
	
	
	
	TempReturnScl_Uls_T_u8p8 = IntplVarXY_u16_s16Xu16Y_Cnt( t_ReturnTempScaleXTbl_DegC_s11p4, 
															t_ReturnTempScaleSclYTbl_Uls_u8p8, 
															TableSize_m(t_ReturnTempScaleXTbl_DegC_s11p4), 
															AssistMechTempEst_DegC_T_s11p4);
															
	TempReturnScl_Uls_f32 = FPM_FixedToFloat_m(TempReturnScl_Uls_T_u8p8, u8p8_T);
	
	ScaledReturn_MtrNm_f32 = (HwPosReturnCmd_MtrNm_T_f32 * HwTrqReturnScl_Uls_T_f32 * HwVelReturnScl_Uls_T_f32 * TempReturnScl_Uls_f32);
	
	HandWheelAthScl_Uls_T_u9p7 = IntplVarXY_u16_u16Xu16Y_Cnt(	t_HWAuthRetScl_X_Uls_u8p8, 
																t_HWAuthRetScl_Y_Uls_u9p7, 
																TableSize_m(t_HWAuthRetScl_X_Uls_u8p8), 
																FinHwPosAuth_Uls_T_u8p8);
																
	/*Rate Limiter */
	
	HandWheelAthScl_Uls_T_f32 = FPM_FixedToFloat_m(HandWheelAthScl_Uls_T_u9p7, u9p7_T);
	CrntHandWheelAthScl_Uls_M_f32 = Limit_m(HandWheelAthScl_Uls_T_f32, (CrntHandWheelAthScl_Uls_M_f32-(k_RtnHWAuthSlew_UlspS_f32*D_2MS_SEC_F32)) ,(CrntHandWheelAthScl_Uls_M_f32+(k_RtnHWAuthSlew_UlspS_f32*D_2MS_SEC_F32)));

	CrntHandWheelAthScl_Uls_T_f32 = CrntHandWheelAthScl_Uls_M_f32;
	
	RtrnBasicReturn_MtrNm_T_f32 = (float32)Sign_s16_m(FinHwPos_HwDeg_T_s11p4) * ScaledReturn_MtrNm_f32 * CrntHandWheelAthScl_Uls_T_f32;

	RtrnBasicReturn_MtrNm_D_f32 = RtrnBasicReturn_MtrNm_T_f32;

	if ((TRUE == DiagStsHwPosDis_Cnt_T_lgc) || (TRUE == DefeatReturnSvc_Cnt_T_lgc))
	{
		ReturnCmd_MtrNm_T_f32 = 0.0F;
	}
	else
	{
		ReturnCmd_MtrNm_T_f32 =RtrnBasicReturn_MtrNm_T_f32 * DrvDynSclFct_Uls_T_f32 * PrkAstSclFct_Uls_T_f32;
	}
	
	ReturnCmd_MtrNm_T_f32 = Limit_m(ReturnCmd_MtrNm_T_f32, -k_RtnLimit_MtrNm_f32, k_RtnLimit_MtrNm_f32);
	
	#if (STD_ON == BC_RETURN_FAULTINJECTIONPOINT)
	Rte_Call_FltInjection_SCom_FltInjection(&ReturnCmd_MtrNm_T_f32,FLTINJ_RETURN);
	#endif
	
	Rte_IWrite_Return_Per1_ReturnCmd_MtrNm_f32(ReturnCmd_MtrNm_T_f32);		
	
	HwPosReturnCmd_MtrNm_D_f32 = HwPosReturnCmd_MtrNm_T_f32;
	HwTrqReturnScl_Uls_D_f32 = HwTrqReturnScl_Uls_T_f32;
	HwVelReturnScl_Uls_D_f32 = HwVelReturnScl_Uls_T_f32;
	TempReturnScl_Uls_D_f32 = TempReturnScl_Uls_f32;
    /* Configurable End of Runnable Checkpoint */
    Rte_Call_Return_Per1_CP1_CheckpointReached();


		
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_RETURN_APPL_CODE
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
