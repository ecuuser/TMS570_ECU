/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_PwrLmtFuncCr.c
 *     Workspace:  C:/_Synergy_Projects/Working/PwrLmtFuncCr-nz63rn/PwrLmtFuncCr/autosar
 *     SW-C Type:  Ap_PwrLmtFuncCr
 *  Generated at:  Thu Sep  5 08:54:43 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_PwrLmtFuncCr>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Thu Jul 12 11:00:00 2012
 * %version:          12 %
 * %derived_by:       gz7pm0 %
 * %date_modified:    Wed Sep 11 13:17:39 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                           SCR #
 * --------  -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/12/12  1        OT        Initial Version                                                              5823
 * 09/21/12  2        Selva      Checkpoints added and mempmap macros corrected		                         6241
 * 01/24/12  3        Selva     Updated for version 2 fdd 19 B												 7118	
 * 01/28/12  4   	  Selva	    Apply limit else in Power Limit function corrected                           7194 
 * 01/29/12  5  	  Selva	    Created local copies to module level variables in per2                       7194
 * 02/04/13	 6		  LN		Added LPF to MtrVel. Minor MISRA corrections.								 7255
 * 04/13/13	 7		  SP		Anomaly fix 4686, update to v004 of FDD									  	 7904
 * 05/17/13  8		  SP		Updated to SF-19B v006														 8274
 * 07/22/13  9        VT        Anomaly fix 5271, corrected Power Limit function slew rate                   9138 
 * 08/28/13	10        KMC		Updated to SF-19B v007: Mapped Threshold_Exceeded signal to NTC 0x0B2        9627
 *                                (Reduced Assist due to Low Voltage) and update to TrqEnvLmt1_MtrNm 
 *                                calculation. Also updated input, output, cal, and module and display 
 *                                variable names per FDD and naming conventions.  Added output limiting, 
 *                                divide by zero protection and overflow protection.
 * 09/11/13 11        KMC       Removed unnecessary divide by zero protection (that was added in version 10) 10082
 *                                Type casting update for QAC.
 * 03/11/14 12		  LK		Added logic to limit final MtrTrqCmd with TrqEnvLowVltgLmt_MtrNm_T_f32 		 11568
*/ 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Data Element Prototypes:
 ========================
  Volt_f32 of Port Interface Vecu_Volt_f32
    This port prototype is intended to communicate voltage signals that represent the ecu supplied voltage.  This signal has a 
	lower limit, which is non-zero, to allow users of the signal to use it as a denominator in an expression without requiring 
	a divide by 0 check.


 Operation Prototypes:
 =====================
  DtrmnElapsedTime_mS_u16 of Port Interface SystemTime
    Nexteer SystemTime Service


 Mode Declaration Groups:
 ========================
  StaMd_Mode
    EPS System State mode declaration

 *********************************************************************************************************************/

#include "Rte_Ap_PwrLmtFuncCr.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Ap_PwrLmtFuncCr_Cfg.h"
#include "CalConstants.h"
#include "fixmath.h"
#include "filters.h"
#include "interpolation.h"
#include "GlobalMacro.h"
#include "float.h"
#include "Ap_DiagMgr.h"

#define D_10MS_SEC_F32 		(0.010F)
#define D_FLTTRQLMTLOLMT_F32     0.0f
#define D_FLTTRQLMTHILMT_F32     1.0f


#define PWRLMTFUNCCR_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_SpdAdj_MtrRadpS_M_f32;
STATIC VAR(uint32,  AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_VoltageRecoveryTimer_mS_M_u32;
STATIC VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_MtrEnvSpd_MtrRadpS_M_f32;
STATIC VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_MinStdOpLmt_MtrNm_M_f32;
STATIC VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_TrqEnvLmt1_MtrNm_M_f32;
STATIC volatile VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_TrqLmt1_MtrNm_D_f32;
STATIC volatile VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_OPVelOffset_MtrRadpS_D_f32;
STATIC volatile VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_TLimitMaxCurr_MtrNm_D_f32;
STATIC volatile VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_MinStdOpLmt_MtrNm_D_f32;
STATIC volatile VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_LimitDifference_MtrNm_D_f32;
STATIC volatile VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_TrqLmt_Uls_D_f32;
STATIC volatile VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_TrqEnvLmt4_MtrNm_D_f32;
STATIC volatile VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_TrqLmt4_MtrNm_D_f32;
STATIC volatile VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_MtrVelFilt_MtrRadpS_D_f32;
STATIC volatile VAR(float32, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_VecuSlewAdj_Volt_M_f32;

#define PWRLMTFUNCCR_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define PWRLMTFUNCCR_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_ThresholdExceeded_Cnt_M_lgc;
#define PWRLMTFUNCCR_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define PWRLMTFUNCCR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(LPF32KSV_Str, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_TrqLmtKSV_M_str;
STATIC VAR(LPF32KSV_Str, AP_PWRLMTFUNCCR_VAR) PwrLmtFuncCr_MtrVelKSV_M_str;
#define PWRLMTFUNCCR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
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
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * NTCNumber: Enumeration of integer in interval [0...511] with enumerators
 *   NTC_Num_FlashWrapperLgcFlt (1u)
 *   NTC_Num_FlashECCCorr (2u)
 *   NTC_Num_FlashECCMemFlt (3u)
 *   NTC_Num_FlashCRCMemFault (4u)
 *   NTC_Num_CurrentSensorCalOutOfRange (9u)
 *   NTC_Num_EEPROMDiag (10u)
 *   NTC_Num_EEPROMDiagMtrStr (11u)
 *   NTC_Num_PriSnsrTrqStorFlt (12u)
 *   NTC_Num_EEPROMDiagPosTrimStr (13u)
 *   NTC_Num_SecSnsrTrqStorFlt (14u)
 *   NTC_Num_EEPROMDiagPolarityStr (15u)
 *   NTC_Num_RAMDiag_GeneralFlt (16u)
 *   NTC_Num_RAMDiag_WrprLgcFlt (17u)
 *   NTC_Num_RAMDiag_ECCCorrIndFlt (18u)
 *   NTC_Num_RAMDiag_ECCMemFlt (19u)
 *   NTC_Num_RAMDiag_CRCMemFlt (20u)
 *   NTC_Num_RAMDiag_VIMRamFlt (23u)
 *   NTC_Num_RAMDiag_NHET1RamFlt (24u)
 *   NTC_Num_RAMDiag_NHET2RamFlt (25u)
 *   NTC_Num_RAMDiag_ADC1RamFlt (26u)
 *   NTC_Num_RAMDiag_DCANRamFault (27u)
 *   NTC_Num_RAMDiag_ADC2RamFlt (28u)
 *   NTC_Num_RAMDiag_HETTU1RamFlt (29u)
 *   NTC_Num_RAMDiag_HETTU2RamFlt (30u)
 *   NTC_Num_CPU_RegVer (32u)
 *   NTC_Num_CPU_CoreInitFlt (33u)
 *   NTC_Num_CPU_CoreRunTimeFlt (34u)
 *   NTC_Num_CPU_ClockMon (35u)
 *   NTC_Num_CPU_eFuseFlt (36u)
 *   NTC_Num_CPU_MPUViolation (37u)
 *   NTC_Num_CPU_FactPrcsErr (40u)
 *   NTC_Num_PropExeDiag_InitDiag (41u)
 *   NTC_Num_PrgFlwDeadlnFlt (42u)
 *   NTC_Num_PropExeDiag_RunTimeDiag (43u)
 *   NTC_Num_PropExeDiag_COPTimeout (44u)
 *   NTC_Num_PropExeDiag_PrefetchAbort (48u)
 *   NTC_Num_PropExeDiag_DataAbort (49u)
 *   NTC_Num_PerDiag_ADC1Flt (50u)
 *   NTC_Num_PerDiag_ADC2Flt (51u)
 *   NTC_Num_PerDiag_ADCCrossChkFlt (52u)
 *   NTC_Num_PerDiag_IllegalAccess (53u)
 *   NTC_Num_PerDiag_DMAFlt (54u)
 *   NTC_Num_PerDiag_CPUWarning (63u)
 *   NTC_Num_TmpMonFunc (64u)
 *   NTC_Num_TmpMonRunTimeFlt (65u)
 *   NTC_Num_PowerRelayInitFlt (66u)
 *   NTC_Num_PrechargeFailure (67u)
 *   NTC_Num_PowerRelayRunFlt (68u)
 *   NTC_Num_Thermistor (69u)
 *   NTC_Num_RefSupplyVltg (70u)
 *   NTC_Num_TrcvrInterfaceFlt (71u)
 *   NTC_Num_CPUSupplyOvervoltage (72u)
 *   NTC_Num_GateDrvFlt (77u)
 *   NTC_Num_OnStateSingleFET (78u)
 *   NTC_Num_OnStateMultiFET (79u)
 *   NTC_Num_PhaseVoltageVerf (80u)
 *   NTC_Num_PhaseDscnt (81u)
 *   NTC_Num_DigPhaseVoltageVerf (82u)
 *   NTC_Num_PhaseDscntFailedDisable (83u)
 *   NTC_Num_CurrentMeas1 (84u)
 *   NTC_Num_CurrentMeas2 (85u)
 *   NTC_Num_CurrentMeasCrossChk (86u)
 *   NTC_Num_PDSupplyOverVoltage (87u)
 *   NTC_Num_ChargePumpUnderVoltage (88u)
 *   NTC_Num_HwTrqSensor (96u)
 *   NTC_Num_AnaVsDigHwTrq (97u)
 *   NTC_Num_TrqSensorRecoveryFlt (98u)
 *   NTC_Num_TrqSensorScaleInvalid (100u)
 *   NTC_Num_T1vsT2 (101u)
 *   NTC_Num_T1OutofRange (102u)
 *   NTC_Num_T2OutofRange (103u)
 *   NTC_Num_DigT1vsT2 (104u)
 *   NTC_Num_DigT1OutofRange (105u)
 *   NTC_Num_DigT2OutofRange (106u)
 *   NTC_Num_RedT1vsT2 (107u)
 *   NTC_Num_HWACrossChecks (108u)
 *   NTC_Num_HWASnsrCommFault (109u)
 *   NTC_Num_HWASensorRel (110u)
 *   NTC_Num_HWASensorAbs (111u)
 *   NTC_Num_PriMSB_SinCosCorr (112u)
 *   NTC_Num_SecMSB_SinCosCorr (113u)
 *   NTC_Num_PriVsSec_SinCosCorr (114u)
 *   NTC_Num_DigMSBFlt (115u)
 *   NTC_Num_MtrVelFlt (116u)
 *   NTC_Num_HWAtoMtrAngleCorr (117u)
 *   NTC_Num_RedPriVsSec_SinCosCorr (118u)
 *   NTC_Num_TurnCntr_PosLoss (128u)
 *   NTC_Num_TurnCntr_MicroProcFlt (129u)
 *   NTC_Num_TurnCntr_SensorPosFlt (130u)
 *   NTC_Num_TurnCntr_SpiComFlt (131u)
 *   NTC_Num_TurnCntr_HighQuiescCur (132u)
 *   NTC_Num_TurnCntr_MainResets (133u)
 *   NTC_Num_TurnCntr_PosLossNotSpdDep (134u)
 *   NTC_Num_KinematicIntDiag (144u)
 *   NTC_Num_HighFriction (145u)
 *   NTC_Num_DutyCycleExceeded (148u)
 *   NTC_Num_AbsTempThermLimit (149u)
 *   NTC_Num_LatchActive (160u)
 *   NTC_Num_OpTrqVsHwTrq (168u)
 *   NTC_Num_CurrentReas (169u)
 *   NTC_Num_OpVoltage (176u)
 *   NTC_Num_ExVoltageLow (177u)
 *   NTC_Num_ReducedAsstLowVoltage (178u)
 *   NTC_Num_ExVoltageHigh (180u)
 *   NTC_Num_OpVoltageOvrMax (181u)
 *   NTC_Num_BattTransOverVolt (182u)
 *   NTC_Num_IgnConfDiag (184u)
 *   NTC_Num_TurnCntr_LowBattery (185u)
 *   NTC_Num_EEPROMCloseFailed (191u)
 *   NTC_Num_SigPath1CrossChk (192u)
 *   NTC_Num_SigPath2CrossChk (193u)
 *   NTC_Num_SigPath3CrossChk (194u)
 *   NTC_Num_SigPath4CrossChk (195u)
 *   NTC_Num_SigPath5CrossChk (196u)
 *   NTC_Num_DampingFWReached (197u)
 *   NTC_Num_AssistFWReached (198u)
 *   NTC_Num_ReturnFWReached (199u)
 *   NTC_Num_DampingFWFltMode (200u)
 *   NTC_Num_AssistFWFltMode (201u)
 *   NTC_Num_VBICFltMode (202u)
 *   NTC_Num_StaMdsSysC (203u)
 *   NTC_NUM_SysFailureForRotVel (204u)
 *   NTC_NUM_SysFailForRedntRotVel (205u)
 *   NTC_Num_SysFailureForTrqSnsr (206u)
 *   NTC_Num_SysFailureForRedTrqSnsr (207u)
 *   NTC_NUM_SysFailureForCtrlVolt (209u)
 *   NTC_Num_GlblSgnlOvrwrtDet (223u)
 *   NTC_Num_VLF_00 (224u)
 *   NTC_Num_VLF_01 (225u)
 *   NTC_Num_VLF_02 (226u)
 *   NTC_Num_VLF_03 (227u)
 *   NTC_Num_VLF_04 (228u)
 *   NTC_Num_VLF_05 (229u)
 *   NTC_Num_VLF_06 (230u)
 *   NTC_Num_VLF_07 (231u)
 *   NTC_Num_VLF_08 (232u)
 *   NTC_Num_VLF_09 (233u)
 *   NTC_Num_VLF_10 (234u)
 *   NTC_Num_VLF_11 (235u)
 *   NTC_Num_VLF_12 (236u)
 *   NTC_Num_VLF_13 (237u)
 *   NTC_Num_VLF_14 (238u)
 *   NTC_Num_VLF_15 (239u)
 *   NTC_Num_VLF_16 (240u)
 *   NTC_Num_VLF_17 (241u)
 *   NTC_Num_VLF_18 (242u)
 *   NTC_Num_VLF_19 (243u)
 *   NTC_Num_VLF_20 (244u)
 *   NTC_Num_VLF_21 (245u)
 *   NTC_Num_VLF_22 (246u)
 *   NTC_Num_VLF_23 (247u)
 *   NTC_Num_VLF_24 (248u)
 *   NTC_Num_VLF_25 (249u)
 *   NTC_Num_VLF_26 (250u)
 *   NTC_Num_VLF_27 (251u)
 *   NTC_Num_VLF_28 (252u)
 *   NTC_Num_VLF_29 (253u)
 *   NTC_Num_VLF_30 (254u)
 *   NTC_Num_VLF_31 (255u)
 *   NTC_Num_BusOffCh1 (256u)
 *   NTC_Num_BusOffCh1NodeMute (257u)
 *   NTC_Num_Node1AAbsent (258u)
 *   NTC_Num_Node1AFaulty (259u)
 *   NTC_Num_Node1BAbsent (260u)
 *   NTC_Num_Node1BFaulty (261u)
 *   NTC_Num_Node1CAbsent (262u)
 *   NTC_Num_Node1CFaulty (263u)
 *   NTC_Num_Node1DAbsent (264u)
 *   NTC_Num_Node1DFaulty (265u)
 *   NTC_Num_Node1EAbsent (266u)
 *   NTC_Num_Node1EFaulty (267u)
 *   NTC_Num_Node1FAbsent (268u)
 *   NTC_Num_Node1FFaulty (269u)
 *   NTC_Num_Node1GAbsent (270u)
 *   NTC_Num_Node1GFaulty (271u)
 *   NTC_Num_BusOffCh2 (272u)
 *   NTC_Num_Node2AAbsent (273u)
 *   NTC_Num_Node2AFaulty (274u)
 *   NTC_Num_Node2BAbsent (275u)
 *   NTC_Num_Node2BFaulty (276u)
 *   NTC_Num_Node2CAbsent (277u)
 *   NTC_Num_Node2CFaulty (278u)
 *   NTC_Num_Node2DAbsent (279u)
 *   NTC_Num_Node2DFaulty (280u)
 *   NTC_Num_Node2EAbsent (281u)
 *   NTC_Num_Node2EFaulty (282u)
 *   NTC_Num_Node2FAbsent (283u)
 *   NTC_Num_Node2FFaulty (284u)
 *   NTC_Num_Node2GAbsent (285u)
 *   NTC_Num_Node2GFaulty (286u)
 *   NTC_Num_InvalidMsg_M (288u)
 *   NTC_Num_MissingMsg_M (289u)
 *   NTC_Num_CRCFltMsg_M (290u)
 *   NTC_Num_PgrsCntFltMsg_M (291u)
 *   NTC_Num_DataRngFltMsg_M (292u)
 *   NTC_Num_DataRateFltMsg_M (293u)
 *   NTC_Num_DataOtherFltMsg_M (294u)
 *   NTC_Num_DataOther2FltMsg_M (295u)
 *   NTC_Num_InvalidMsg_N (296u)
 *   NTC_Num_MissingMsg_N (297u)
 *   NTC_Num_CRCFltMsg_N (298u)
 *   NTC_Num_PgrsCntFltMsg_N (299u)
 *   NTC_Num_DataRngFltMsg_N (300u)
 *   NTC_Num_DataRateFltMsg_N (301u)
 *   NTC_Num_DataOtherFltMsg_N (302u)
 *   NTC_Num_DataOtherFlt2Msg_N (303u)
 *   NTC_Num_InvalidMsg_O (304u)
 *   NTC_Num_MissingMsg_O (305u)
 *   NTC_Num_CRCFltMsg_O (306u)
 *   NTC_Num_PgrsCntFltMsg_O (307u)
 *   NTC_Num_DataRngFltMsg_O (308u)
 *   NTC_Num_DataRateFltMsg_O (309u)
 *   NTC_Num_DataOtherFltMsg_O (310u)
 *   NTC_Num_InvalidMsg_P (312u)
 *   NTC_Num_MissingMsg_P (313u)
 *   NTC_Num_CRCFltMsg_P (314u)
 *   NTC_Num_PgrsCntFltMsg_P (315u)
 *   NTC_Num_DataRngFltMsg_P (316u)
 *   NTC_Num_DataRateFltMsg_P (317u)
 *   NTC_Num_DataOtherFltMsg_P (318u)
 *   NTC_Num_InvalidMsg_Q (320u)
 *   NTC_Num_MissingMsg_Q (321u)
 *   NTC_Num_CRCFltMsg_Q (322u)
 *   NTC_Num_PgrsCntFltMsg_Q (323u)
 *   NTC_Num_DataRngFltMsg_Q (324u)
 *   NTC_Num_DataRateFltMsg_Q (325u)
 *   NTC_Num_DataOtherFltMsg_Q (326u)
 *   NTC_Num_InvalidMsg_R (328u)
 *   NTC_Num_MissingMsg_R (329u)
 *   NTC_Num_CRCFltMsg_R (330u)
 *   NTC_Num_PgrsCntFltMsg_R (331u)
 *   NTC_Num_DataRngFltMsg_R (332u)
 *   NTC_Num_DataRateFltMsg_R (333u)
 *   NTC_Num_DataOtherFltMsg_R (334u)
 *   NTC_Num_DataOtherFlt2Msg_R (335u)
 *   NTC_Num_InvalidMsg_S (336u)
 *   NTC_Num_MissingMsg_S (337u)
 *   NTC_Num_CRCFltMsg_S (338u)
 *   NTC_Num_PgrsCntFltMsg_S (339u)
 *   NTC_Num_DataRngFltMsg_S (340u)
 *   NTC_Num_DataRateFltMsg_S (341u)
 *   NTC_Num_DataOtherFltMsg_S (342u)
 *   NTC_Num_InvalidMsg_T (344u)
 *   NTC_Num_MissingMsg_T (345u)
 *   NTC_Num_CRCFltMsg_T (346u)
 *   NTC_Num_PgrsCntFltMsg_T (347u)
 *   NTC_Num_DataRngFltMsg_T (348u)
 *   NTC_Num_DataRateFltMsg_T (349u)
 *   NTC_Num_DataOtherFltMsg_T (350u)
 *   NTC_Num_InvalidMsg_U (352u)
 *   NTC_Num_MissingMsg_U (353u)
 *   NTC_Num_CRCFltMsg_U (354u)
 *   NTC_Num_PgrsCntFltMsg_U (355u)
 *   NTC_Num_DataRngFltMsg_U (356u)
 *   NTC_Num_DataRateFltMsg_U (357u)
 *   NTC_Num_DataOtherFltMsg_U (358u)
 *   NTC_Num_InvalidMsg_V (360u)
 *   NTC_Num_MissingMsg_V (361u)
 *   NTC_Num_CRCFltMsg_V (362u)
 *   NTC_Num_PgrsCntFltMsg_V (363u)
 *   NTC_Num_DataRngFltMsg_V (364u)
 *   NTC_Num_DataRateFltMsg_V (365u)
 *   NTC_Num_DataOtherFltMsg_V (366u)
 *   NTC_Num_InvalidMsg_W (368u)
 *   NTC_Num_MissingMsg_W (369u)
 *   NTC_Num_CRCFltMsg_W (370u)
 *   NTC_Num_PgrsCntFltMsg_W (371u)
 *   NTC_Num_DataRngFltMsg_W (372u)
 *   NTC_Num_DataRateFltMsg_W (373u)
 *   NTC_Num_DataOtherFltMsg_W (374u)
 *   NTC_Num_InvalidMsg_X (376u)
 *   NTC_Num_MissingMsg_X (377u)
 *   NTC_Num_CRCFltMsg_X (378u)
 *   NTC_Num_PgrsCntFltMsg_X (379u)
 *   NTC_Num_DataRngFltMsg_X (380u)
 *   NTC_Num_DataRateFltMsg_X (381u)
 *   NTC_Num_DataOtherFltMsg_X (382u)
 *   NTC_Num_InvalidMsg_Y (384u)
 *   NTC_Num_MissingMsg_Y (385u)
 *   NTC_Num_CRCFltMsg_Y (386u)
 *   NTC_Num_PgrsCntFltMsg_Y (387u)
 *   NTC_Num_DataRngFltMsg_Y (388u)
 *   NTC_Num_DataRateFltMsg_Y (389u)
 *   NTC_Num_DataOtherFltMsg_Y (390u)
 *   NTC_Num_InvalidMsg_Z (392u)
 *   NTC_Num_MissingMsg_Z (393u)
 *   NTC_Num_CRCFltMsg_Z (394u)
 *   NTC_Num_PgrsCntFltMsg_Z (395u)
 *   NTC_Num_DataRngFltMsg_Z (396u)
 *   NTC_Num_DataRateFltMsg_Z (397u)
 *   NTC_Num_DataOtherFltMsg_Z (398u)
 *   NTC_Num_DSTXORActive (399u)
 *   NTC_Num_InvalidMsg_AA (400u)
 *   NTC_Num_MissingMsg_AA (401u)
 *   NTC_Num_CRCFltMsg_AA (402u)
 *   NTC_Num_PgrsCntFltMsg_AA (403u)
 *   NTC_Num_DataRngFltMsg_AA (404u)
 *   NTC_Num_DataRateFltMsg_AA (405u)
 *   NTC_Num_DataOtherFltMsg_AA (406u)
 *   NTC_Num_InvalidMsg_AB (408u)
 *   NTC_Num_MissingMsg_AB (409u)
 *   NTC_Num_CRCFltMsg_AB (410u)
 *   NTC_Num_PgrsCntFltMsg_AB (411u)
 *   NTC_Num_DataRngFltMsg_AB (412u)
 *   NTC_Num_DataRateFltMsg_AB (413u)
 *   NTC_Num_DataOtherFltMsg_AB (414u)
 *   NTC_Num_InvalidMsg_AC (416u)
 *   NTC_Num_MissingMsg_AC (417u)
 *   NTC_Num_CRCFltMsg_AC (418u)
 *   NTC_Num_PgrsCntFltMsg_AC (419u)
 *   NTC_Num_DataRngFltMsg_AC (420u)
 *   NTC_Num_DataRateFltMsg_AC (421u)
 *   NTC_Num_DataOtherFltMsg_AC (422u)
 *   NTC_Num_InvalidMsg_AD (424u)
 *   NTC_Num_MissingMsg_AD (425u)
 *   NTC_Num_CRCFltMsg_AD (426u)
 *   NTC_Num_PgrsCntFltMsg_AD (427u)
 *   NTC_Num_DataRngFltMsg_AD (428u)
 *   NTC_Num_DataRateFltMsg_AD (429u)
 *   NTC_Num_DataOtherFltMsg_AD (430u)
 *   NTC_Num_InvalidMsg_AE (432u)
 *   NTC_Num_MissingMsg_AE (433u)
 *   NTC_Num_CRCFltMsg_AE (434u)
 *   NTC_Num_PgrsCntFltMsg_AE (435u)
 *   NTC_Num_DataRngFltMsg_AE (436u)
 *   NTC_Num_DataRateFltMsg_AE (437u)
 *   NTC_Num_DataOtherFltMsg_AE (438u)
 *   NTC_Num_InvalidMsg_AF (440u)
 *   NTC_Num_MissingMsg_AF (441u)
 *   NTC_Num_CRCFltMsg_AF (442u)
 *   NTC_Num_PgrsCntFltMsg_AF (443u)
 *   NTC_Num_DataRngFltMsg_AF (444u)
 *   NTC_Num_DataRateFltMsg_AF (445u)
 *   NTC_Num_DataOtherFltMsg_AF (446u)
 *   NTC_Num_InvalidMsg_AG (448u)
 *   NTC_Num_MissingMsg_AG (449u)
 *   NTC_Num_CRCFltMsg_AG (450u)
 *   NTC_Num_PgrsCntFltMsg_AG (451u)
 *   NTC_Num_DataRngFltMsg_AG (452u)
 *   NTC_Num_DataRateFltMsg_AG (453u)
 *   NTC_Num_DataOtherFltMsg_AG (454u)
 *   NTC_Num_InvalidMsg_AH (456u)
 *   NTC_Num_MissingMsg_AH (457u)
 *   NTC_Num_CRCFltMsg_AH (458u)
 *   NTC_Num_PgrsCntFltMsg_AH (459u)
 *   NTC_Num_DataRngFltMsg_AH (460u)
 *   NTC_Num_DataRateFltMsg_AH (461u)
 *   NTC_Num_DataOtherFltMsg_AH (462u)
 *   NTC_Num_FlexrayCommunicationError (465u)
 *   NTC_Num_InvalidMsg_AI (466u)
 *   NTC_Num_MissingMsg_AI (467u)
 *   NTC_Num_MissingMsg_AJ (473u)
 *   NTC_Num_MissingMsg_AK (481u)
 *   NTC_Num_MissingMsg_AL (489u)
 *   NTC_Num_SysConsistencyVerf (496u)
 *   NTC_Num_ConfigMisMatch (497u)
 *   NTC_Num_CalNotPrgmd (498u)
 *   NTC_Num_EOLVehTunNtPerf (501u)
 *   NTC_Num_MtrSensorNotTrimmed (502u)
 *   NTC_Num_HWASensorNotTrimmed (504u)
 *   NTC_Num_HWASensorTrimNoAttempt (505u)
 *   NTC_Num_TrqSensorScaleNotSet (506u)
 *   NTC_Num_TrqSensorNotTrimmed (507u)
 *   NTC_Num_DigTrqSensorScaleNotSet (509u)
 *   NTC_Num_DigTrqSensorNotTrimmed (510u)
 * NxtrDiagMgrStatus: Enumeration of integer in interval [0...255] with enumerators
 *   NTC_STATUS_PASSED (0u)
 *   NTC_STATUS_FAILED (1u)
 *   NTC_STATUS_PREPASSED (2u)
 *   NTC_STATUS_PREFAILED (3u)
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
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8
 * Float: D_VECUMIN_VOLTS_F32 = 5
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_PWRLMTFUNCCR_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: PwrLmtFuncCr_Init1
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
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_PWRLMTFUNCCR_APPL_CODE) PwrLmtFuncCr_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: PwrLmtFuncCr_Init1
 *********************************************************************************************************************/
	
	
	LPF_KUpdate_f32_m(k_AsstReducLPFKn_Hz_f32, D_10MS_SEC_F32, &PwrLmtFuncCr_TrqLmtKSV_M_str);
	LPF_KUpdate_f32_m(k_PwrLmtMtrVelLPFKn_Hz_f32, D_2MS_SEC_F32, &PwrLmtFuncCr_MtrVelKSV_M_str);
	
	(void) Rte_Call_SystemTime_GetSystemTime_mS_u32(&PwrLmtFuncCr_VoltageRecoveryTimer_mS_M_u32);
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: PwrLmtFuncCr_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <DISABLE, WARMINIT, OFF>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Boolean Rte_IRead_PwrLmtFuncCr_Per1_AltFaultActive_Cnt_lgc(void)
 *   Float Rte_IRead_PwrLmtFuncCr_Per1_CntDisMtrTrqCmdMRF_MtrNm_f32(void)
 *   Float Rte_IRead_PwrLmtFuncCr_Per1_EstKe_VpRadpS_f32(void)
 *   Float Rte_IRead_PwrLmtFuncCr_Per1_MotorVelMRF_MtrRadpS_f32(void)
 *   Boolean Rte_IRead_PwrLmtFuncCr_Per1_PosServEnable_Cnt_lgc(void)
 *   Float Rte_IRead_PwrLmtFuncCr_Per1_Vecu_Volt_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_PwrLmtFuncCr_Per1_MRFMtrTrqCmd_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_PwrLmtFuncCr_Per1_MRFMtrTrqCmd_MtrNm_f32(void)
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

FUNC(void, RTE_AP_PWRLMTFUNCCR_APPL_CODE) PwrLmtFuncCr_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: PwrLmtFuncCr_Per1
 *********************************************************************************************************************/
	
	
	VAR(float32, AUTOMATIC) EstKe_VpRadpS_T_f32;
	VAR(float32, AUTOMATIC) MotorVelMRF_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) AbsMtrVel_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) TLimitMaxCurr_MtrNm_T_f32;
	VAR(uint16,  AUTOMATIC) Vecu_Volt_T_u5p11;
	VAR(uint16,  AUTOMATIC) OPVelOffset_MtrRadpS_T_u11p5;
	VAR(float32, AUTOMATIC) OPVelOffset_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) SpdAdj_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) MRFMtrTrq_MtrNm_T_f32;
	VAR(uint16,  AUTOMATIC) AbsMtrEnvSpd_MtrRadpS_T_u12p4;
	VAR(sint32,  AUTOMATIC) Tmp1MtrEnv_MtrRadpS_T_s27p4;
	VAR(sint32,  AUTOMATIC) TmpEnvLmt1_MtrNm_T_s20p11;
	VAR(sint32,  AUTOMATIC) TrqEnvLmt1_MtrNm_T_s20p11;
	VAR(float32, AUTOMATIC) TrqEnvLmt1_MtrNm_T_f32 ;
	VAR(uint16, AUTOMATIC) TrqEnvLmt1_MtrNm_T_u5p11;
	VAR(uint32,  AUTOMATIC) Tmp2MtrEnv_MtrNm_T_u21p11;
	VAR(sint32,  AUTOMATIC) DenMtrEnv_MtrRadpS_T_s27p4;
	VAR(uint16,  AUTOMATIC) AbsMtrVel_MtrRadpS_T_u11p5;
	VAR(uint16,  AUTOMATIC) MinStdOpLmt_MtrNm_T_u4p12;
	VAR(sint32,  AUTOMATIC) SignMtrVel_MtrRadpS_T_s32;
	VAR(sint32,  AUTOMATIC) SignMtrEnvSpd_Uls_T_s32;
	VAR(float32, AUTOMATIC) AbsMtrEnvSpd_MtrRadpS_T_f32;
	VAR(uint16,  AUTOMATIC) TrqEnvLmt4_MtrNm_T_u5p11;
	VAR(float32,  AUTOMATIC) TrqEnvLmt4_MtrNm_T_f32;
	VAR(float32,  AUTOMATIC) TrqLmt4_MtrNm_T_f32;
	VAR(float32,  AUTOMATIC) TrqLmt1_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) CntDisMtrCmdMRF_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) Vecu_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrVelFilt_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) PwrLmtVecuSlewAdj_Volt_T_f32;
	VAR(float32, AUTOMATIC) PwrLmtVecu1SlewAdj_Volt_T_f32;
	VAR(uint16,  AUTOMATIC) AbsSpdAdj_MtrRadpS_T_u12p4;
	VAR(uint16,  AUTOMATIC)	TrqEnvLowVltgLmt_MtrNm_T_u5p11;
	VAR(float32, AUTOMATIC)	TrqEnvLowVltgLmt_MtrNm_T_f32;
	VAR(boolean, AUTOMATIC) AltFaultActive_Cnt_T_lgc;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_PwrLmtFuncCr_Per1_CP0_CheckpointReached();
	
	CntDisMtrCmdMRF_MtrNm_T_f32 = Rte_IRead_PwrLmtFuncCr_Per1_CntDisMtrTrqCmdMRF_MtrNm_f32();
	EstKe_VpRadpS_T_f32 = Rte_IRead_PwrLmtFuncCr_Per1_EstKe_VpRadpS_f32();
	MotorVelMRF_MtrRadpS_T_f32 = Rte_IRead_PwrLmtFuncCr_Per1_MotorVelMRF_MtrRadpS_f32();
	Vecu_Volt_T_f32 = Rte_IRead_PwrLmtFuncCr_Per1_Vecu_Volt_f32();
	
	/** MtrVel_Filter **/
	MtrVelFilt_MtrRadpS_T_f32 = LPF_OpUpdate_f32_m(MotorVelMRF_MtrRadpS_T_f32, &PwrLmtFuncCr_MtrVelKSV_M_str);

	/*** Nexteer Power Limit ***/
	
	AbsMtrVel_MtrRadpS_T_f32 = Abs_f32_m(MtrVelFilt_MtrRadpS_T_f32);
	SignMtrVel_MtrRadpS_T_s32 = Sign_f32_m(MtrVelFilt_MtrRadpS_T_f32);
	
	/** Max_Mtr_Curr_Lmt_Fn **/
	if (k_KeStdTemp_VpRadpS_f32 > 0.0F)
	{
		TLimitMaxCurr_MtrNm_T_f32 = (EstKe_VpRadpS_T_f32 / k_KeStdTemp_VpRadpS_f32) * FPM_FixedToFloat_m(t_MtrEnvTblY_MtrNm_u5p11[8], u5p11_T);
	}
	else
	{
		TLimitMaxCurr_MtrNm_T_f32 = 0.0F;
	}
	
	/** Battery_Voltage_Fn **/
	
	AltFaultActive_Cnt_T_lgc = Rte_IRead_PwrLmtFuncCr_Per1_AltFaultActive_Cnt_lgc();
	
	if(AltFaultActive_Cnt_T_lgc == TRUE)
	{
		PwrLmtVecuSlewAdj_Volt_T_f32 = k_PwrLmtVecuAltFltAdj_Volt_f32;
	}
	else
	{
		PwrLmtVecuSlewAdj_Volt_T_f32 = 0.0F;
	}
	
	PwrLmtVecu1SlewAdj_Volt_T_f32 = Limit_m(PwrLmtVecuSlewAdj_Volt_T_f32, (PwrLmtFuncCr_VecuSlewAdj_Volt_M_f32 - k_PwrLmtVecuAdjSlew_VoltspL_f32), (PwrLmtFuncCr_VecuSlewAdj_Volt_M_f32 + k_PwrLmtVecuAdjSlew_VoltspL_f32));
		
	Vecu_Volt_T_f32 = Vecu_Volt_T_f32 - PwrLmtVecu1SlewAdj_Volt_T_f32;
	
	Vecu_Volt_T_u5p11 = FPM_FloatToFixed_m(Vecu_Volt_T_f32, u5p11_T);
		
	OPVelOffset_MtrRadpS_T_u11p5 = IntplVarXY_u16_u16Xu16Y_Cnt(t_DLVTblX_Volt_u5p11,
															   t_DLVTblY_MtrRadpS_u11p5,
								                               TableSize_m(t_DLVTblX_Volt_u5p11),
								                               Vecu_Volt_T_u5p11);
	
	OPVelOffset_MtrRadpS_T_f32 = FPM_FixedToFloat_m(OPVelOffset_MtrRadpS_T_u11p5, u11p5_T);
	
	
	/** OpVel_Offset_Slew_Rate_Lmt **/
	
	if( k_SpdAdjSlewEnable_Cnt_lgc == TRUE )
	{
		SpdAdj_MtrRadpS_T_f32 = Limit_m(OPVelOffset_MtrRadpS_T_f32, PwrLmtFuncCr_SpdAdj_MtrRadpS_M_f32 - k_SpdAdjSlewDec_MtrRadpS_f32, PwrLmtFuncCr_SpdAdj_MtrRadpS_M_f32 + k_SpdAdjSlewInc_MtrRadpS_f32);
	}
	else
	{
		SpdAdj_MtrRadpS_T_f32 = OPVelOffset_MtrRadpS_T_f32;
	}
	
	
	PwrLmtFuncCr_MtrEnvSpd_MtrRadpS_M_f32 = MtrVelFilt_MtrRadpS_T_f32 +(SpdAdj_MtrRadpS_T_f32 * (float32)SignMtrVel_MtrRadpS_T_s32);
	
	
	/** Output Velocity Function **/
	SignMtrEnvSpd_Uls_T_s32 = Sign_f32_m(PwrLmtFuncCr_MtrEnvSpd_MtrRadpS_M_f32);
	AbsMtrEnvSpd_MtrRadpS_T_f32 = Abs_f32_m(PwrLmtFuncCr_MtrEnvSpd_MtrRadpS_M_f32);
	
	
	AbsMtrEnvSpd_MtrRadpS_T_u12p4 = FPM_FloatToFixed_m(AbsMtrEnvSpd_MtrRadpS_T_f32, u12p4_T);
	
	/* * TrqEnvLmt4 calculation  **/
	
	TrqEnvLmt4_MtrNm_T_u5p11 = IntplVarXY_u16_s16Xu16Y_Cnt(t_MtrEnvTblX_MtrRadpS_s11p4,
																	 t_MtrEnvTblY_MtrNm_u5p11,
																	 TableSize_m(t_MtrEnvTblX_MtrRadpS_s11p4),
																	 (-1 * (sint16)(AbsMtrEnvSpd_MtrRadpS_T_u12p4)));
	TrqEnvLmt4_MtrNm_T_f32 = FPM_FixedToFloat_m(TrqEnvLmt4_MtrNm_T_u5p11, u5p11_T);	 
	TrqEnvLmt4_MtrNm_T_f32  = 	- TrqEnvLmt4_MtrNm_T_f32;
	
    /** Choose MAX TrqLmt4 **/
	TrqLmt4_MtrNm_T_f32=	Max_m(TrqEnvLmt4_MtrNm_T_f32, -TLimitMaxCurr_MtrNm_T_f32);	
    	
	
	if (Abs_s16_m(t_MtrEnvTblX_MtrRadpS_s11p4[2]) >= AbsMtrEnvSpd_MtrRadpS_T_u12p4)
	{
		if (AbsMtrEnvSpd_MtrRadpS_T_u12p4 > Abs_s16_m(t_MtrEnvTblX_MtrRadpS_s11p4[13]))
		{
			/* Calculation of TrqEnvLmt1_1 */
			
			Tmp1MtrEnv_MtrRadpS_T_s27p4 = (sint32)((uint32)AbsMtrEnvSpd_MtrRadpS_T_u12p4) - (sint32)t_MtrEnvTblX_MtrRadpS_s11p4[13];
			Tmp2MtrEnv_MtrNm_T_u21p11= (uint32)t_MtrEnvTblY_MtrNm_u5p11[2] + (uint32)t_MtrEnvTblY_MtrNm_u5p11[13];
			DenMtrEnv_MtrRadpS_T_s27p4= (sint32)t_MtrEnvTblX_MtrRadpS_s11p4[2] + (sint32)t_MtrEnvTblX_MtrRadpS_s11p4[13];
			TmpEnvLmt1_MtrNm_T_s20p11 = (Tmp1MtrEnv_MtrRadpS_T_s27p4 * (sint32)Tmp2MtrEnv_MtrNm_T_u21p11) / DenMtrEnv_MtrRadpS_T_s27p4;
			TrqEnvLmt1_MtrNm_T_s20p11 = TmpEnvLmt1_MtrNm_T_s20p11 + (sint32)((uint32)t_MtrEnvTblY_MtrNm_u5p11[13]);
			TrqEnvLmt1_MtrNm_T_f32 = FPM_FixedToFloat_m(TrqEnvLmt1_MtrNm_T_s20p11, s20p11_T);
		}
		else
		{
			/* Calculation of TrqEnvLmt1_2 */
			TrqEnvLmt1_MtrNm_T_u5p11 = IntplVarXY_u16_s16Xu16Y_Cnt(t_MtrEnvTblX_MtrRadpS_s11p4,
																		 t_MtrEnvTblY_MtrNm_u5p11,
																		 TableSize_m(t_MtrEnvTblX_MtrRadpS_s11p4),
																		 (sint16)AbsMtrEnvSpd_MtrRadpS_T_u12p4);
			
			TrqEnvLmt1_MtrNm_T_f32 = FPM_FixedToFloat_m(TrqEnvLmt1_MtrNm_T_u5p11, u5p11_T);
		}
		
		/** choose minimum if **/
		TrqLmt1_MtrNm_T_f32 =	Min_m(TrqEnvLmt1_MtrNm_T_f32, TLimitMaxCurr_MtrNm_T_f32);
		
		MRFMtrTrq_MtrNm_T_f32= ((float32)SignMtrEnvSpd_Uls_T_s32) * CntDisMtrCmdMRF_MtrNm_T_f32;
		MRFMtrTrq_MtrNm_T_f32 = Limit_m(MRFMtrTrq_MtrNm_T_f32, TrqLmt4_MtrNm_T_f32, TrqLmt1_MtrNm_T_f32);
		MRFMtrTrq_MtrNm_T_f32 = MRFMtrTrq_MtrNm_T_f32 * ((float32)SignMtrEnvSpd_Uls_T_s32); 
	}	
	else
	{
		/*** Choose apply limit else ***/
		TrqEnvLmt1_MtrNm_T_f32 = TrqEnvLmt4_MtrNm_T_f32;
		TrqLmt1_MtrNm_T_f32=	Min_m(TrqEnvLmt4_MtrNm_T_f32, TLimitMaxCurr_MtrNm_T_f32);
		MRFMtrTrq_MtrNm_T_f32 = TrqLmt1_MtrNm_T_f32 * ((float32)SignMtrEnvSpd_Uls_T_s32); 
	}
	

	/** Final MRFMtrTrq_MtrNm_T_f32 limit calculation **/
	
	AbsSpdAdj_MtrRadpS_T_u12p4 = FPM_FloatToFixed_m(Abs_f32_m(SpdAdj_MtrRadpS_T_f32), u12p4_T);
	TrqEnvLowVltgLmt_MtrNm_T_u5p11 = IntplVarXY_u16_s16Xu16Y_Cnt(t_MtrEnvTblX_MtrRadpS_s11p4,
																		 t_MtrEnvTblY_MtrNm_u5p11,
																		 TableSize_m(t_MtrEnvTblX_MtrRadpS_s11p4),
																		 (sint16)AbsSpdAdj_MtrRadpS_T_u12p4);
			
	TrqEnvLowVltgLmt_MtrNm_T_f32 = FPM_FixedToFloat_m(TrqEnvLowVltgLmt_MtrNm_T_u5p11, u5p11_T);															 
	MRFMtrTrq_MtrNm_T_f32 = Limit_m(MRFMtrTrq_MtrNm_T_f32, -TrqEnvLowVltgLmt_MtrNm_T_f32, TrqEnvLowVltgLmt_MtrNm_T_f32);
		
		
	/** MinStdOp_Volt_Max_Net_Assist **/

	AbsMtrVel_MtrRadpS_T_u11p5 = FPM_FloatToFixed_m(AbsMtrVel_MtrRadpS_T_f32, u11p5_T);
	
	MinStdOpLmt_MtrNm_T_u4p12 = IntplVarXY_u16_u16Xu16Y_Cnt(t_StdOpMtrEnvTblX_MtrRadpS_u11p5,
															   t_StdOpMtrEnvTblY_MtrNm_u4p12,
															   TableSize_m(t_StdOpMtrEnvTblX_MtrRadpS_u11p5),
															   AbsMtrVel_MtrRadpS_T_u11p5);
	
	PwrLmtFuncCr_MinStdOpLmt_MtrNm_M_f32 = FPM_FixedToFloat_m(MinStdOpLmt_MtrNm_T_u4p12, u4p12_T);
	PwrLmtFuncCr_TrqEnvLmt1_MtrNm_M_f32 = TrqEnvLmt1_MtrNm_T_f32;
	PwrLmtFuncCr_TrqLmt1_MtrNm_D_f32 = TrqLmt1_MtrNm_T_f32;
	PwrLmtFuncCr_OPVelOffset_MtrRadpS_D_f32 = OPVelOffset_MtrRadpS_T_f32;
	PwrLmtFuncCr_TLimitMaxCurr_MtrNm_D_f32 = TLimitMaxCurr_MtrNm_T_f32;
	PwrLmtFuncCr_MinStdOpLmt_MtrNm_D_f32 = PwrLmtFuncCr_MinStdOpLmt_MtrNm_M_f32;
	PwrLmtFuncCr_SpdAdj_MtrRadpS_M_f32 = SpdAdj_MtrRadpS_T_f32;
	PwrLmtFuncCr_TrqEnvLmt4_MtrNm_D_f32 = TrqEnvLmt4_MtrNm_T_f32;
	PwrLmtFuncCr_TrqLmt4_MtrNm_D_f32 = TrqLmt4_MtrNm_T_f32;
	PwrLmtFuncCr_MtrVelFilt_MtrRadpS_D_f32 = MtrVelFilt_MtrRadpS_T_f32;
	PwrLmtFuncCr_VecuSlewAdj_Volt_M_f32 = PwrLmtVecu1SlewAdj_Volt_T_f32;

	Rte_IWrite_PwrLmtFuncCr_Per1_MRFMtrTrqCmd_MtrNm_f32(MRFMtrTrq_MtrNm_T_f32);

	
	/* Configurable End of Runnable Checkpoint */
    Rte_Call_PwrLmtFuncCr_Per1_CP1_CheckpointReached();

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: PwrLmtFuncCr_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *     and not in Mode(s) <WARMINIT, OFF, DISABLE>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_PwrLmtFuncCr_Per2_CntDisMtrTrqCmdMRF_MtrNm_f32(void)
 *   Float Rte_IRead_PwrLmtFuncCr_Per2_Vecu_Volt_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_PwrLmtFuncCr_Per2_FltTrqLmt_Uls_f32(Float data)
 *   Float *Rte_IWriteRef_PwrLmtFuncCr_Per2_FltTrqLmt_Uls_f32(void)
 *   void Rte_IWrite_PwrLmtFuncCr_Per2_ThresholdExceeded_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_PwrLmtFuncCr_Per2_ThresholdExceeded_Cnt_lgc(void)
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
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_GetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 *Status_Ptr_T_u08)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_PWRLMTFUNCCR_APPL_CODE) PwrLmtFuncCr_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: PwrLmtFuncCr_Per2
 *********************************************************************************************************************/

	VAR(float32, AUTOMATIC) LimitDifference_MtrNm_T_f32;	
	VAR(float32, AUTOMATIC) TrqLmt_Uls_T_f32;
	VAR(float32, AUTOMATIC) FltTrqLmt_Uls_T_f32;
	VAR(uint16,  AUTOMATIC) ElapsedTime_mS_T_u16;
	VAR(float32, AUTOMATIC) CntDisMtrCmdMRF_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) Vecu_Volt_T_f32;
	VAR(float32, AUTOMATIC) AbsMtrEnvSpd_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) AbsCntDisMtrCmdMRF_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) MinStdOpLmt_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) MtrEnvSpd_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) TrqEnvLmt1_MtrNm_T_f32;
	VAR(uint8, AUTOMATIC) 	LVAsstNTCStatus_Cnt_T_u08;
	
	/*** Power Limit Status ***/ 
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_PwrLmtFuncCr_Per2_CP0_CheckpointReached();
	
	CntDisMtrCmdMRF_MtrNm_T_f32 = Rte_IRead_PwrLmtFuncCr_Per2_CntDisMtrTrqCmdMRF_MtrNm_f32();
	Vecu_Volt_T_f32 = Rte_IRead_PwrLmtFuncCr_Per2_Vecu_Volt_f32();
	MinStdOpLmt_MtrNm_T_f32 = PwrLmtFuncCr_MinStdOpLmt_MtrNm_M_f32;
	TrqEnvLmt1_MtrNm_T_f32 = PwrLmtFuncCr_TrqEnvLmt1_MtrNm_M_f32;
	MtrEnvSpd_MtrRadpS_T_f32 = PwrLmtFuncCr_MtrEnvSpd_MtrRadpS_M_f32;
	
	LimitDifference_MtrNm_T_f32 = TrqEnvLmt1_MtrNm_T_f32 - MinStdOpLmt_MtrNm_T_f32;
	AbsMtrEnvSpd_MtrRadpS_T_f32 = Abs_f32_m(MtrEnvSpd_MtrRadpS_T_f32); 
	AbsCntDisMtrCmdMRF_MtrNm_T_f32= Abs_f32_m(CntDisMtrCmdMRF_MtrNm_T_f32);
	/** Assist_Lmt_Determination_and_Mag_Calc **/
	if ((Sign_f32_m(MtrEnvSpd_MtrRadpS_T_f32) == Sign_f32_m(CntDisMtrCmdMRF_MtrNm_T_f32)) && 
	(AbsMtrEnvSpd_MtrRadpS_T_f32< FPM_FixedToFloat_m(t_MtrEnvTblX_MtrRadpS_s11p4[13],s11p4_T)))
	{		   
		if( (Abs_f32_m(MinStdOpLmt_MtrNm_T_f32)>FLT_EPSILON ) &&
			 (LimitDifference_MtrNm_T_f32 < D_ZERO_ULS_F32) &&
			( AbsCntDisMtrCmdMRF_MtrNm_T_f32> TrqEnvLmt1_MtrNm_T_f32) 
			)
		{
			TrqLmt_Uls_T_f32 = Abs_f32_m(LimitDifference_MtrNm_T_f32) / MinStdOpLmt_MtrNm_T_f32;
		}
		else
		{
			TrqLmt_Uls_T_f32 = D_ZERO_ULS_F32;
		}
	}
	else
	{
		TrqLmt_Uls_T_f32 = D_ZERO_ULS_F32;
	}
	
	/** Assist_Limit_Mag_Filter **/
	FltTrqLmt_Uls_T_f32 = LPF_OpUpdate_f32_m(TrqLmt_Uls_T_f32, &PwrLmtFuncCr_TrqLmtKSV_M_str);

	/** Assist_Limit_Cond_Determination **/
	
	if( FltTrqLmt_Uls_T_f32 > k_FiltAsstReducTh_Uls_f32 )
	{
		PwrLmtFuncCr_ThresholdExceeded_Cnt_M_lgc = TRUE;
		(void) Rte_Call_SystemTime_GetSystemTime_mS_u32(&PwrLmtFuncCr_VoltageRecoveryTimer_mS_M_u32);
		(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_ReducedAsstLowVoltage, 0x01U, NTC_STATUS_FAILED);
	}
	else
	{
		if( PwrLmtFuncCr_ThresholdExceeded_Cnt_M_lgc == TRUE )
		{
			if( Vecu_Volt_T_f32 >= k_LowVltAstRecTh_Volt_f32 )
			{
				(void) Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(PwrLmtFuncCr_VoltageRecoveryTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
				
				if( ElapsedTime_mS_T_u16 >= k_LowVltAstRecTime_mS_u16 )
				{
					PwrLmtFuncCr_ThresholdExceeded_Cnt_M_lgc = FALSE;
					(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_ReducedAsstLowVoltage, 0x01U, NTC_STATUS_PASSED);
				}
			}
			else
			{
				(void) Rte_Call_SystemTime_GetSystemTime_mS_u32(&PwrLmtFuncCr_VoltageRecoveryTimer_mS_M_u32);
			}
		}
		else
		{
			(void)Rte_Call_NxtrDiagMgr_GetNTCStatus(NTC_Num_ReducedAsstLowVoltage, &LVAsstNTCStatus_Cnt_T_u08);
			if (D_TESTNOTCOMPLETETHISOPCYCLEBIT_CNT_B8 == (D_TESTNOTCOMPLETETHISOPCYCLEBIT_CNT_B8 & LVAsstNTCStatus_Cnt_T_u08))
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_ReducedAsstLowVoltage, 0x01U, NTC_STATUS_PASSED);	
			}
		}
	}

	FltTrqLmt_Uls_T_f32 = Limit_m(FltTrqLmt_Uls_T_f32, D_FLTTRQLMTLOLMT_F32, D_FLTTRQLMTHILMT_F32);

	PwrLmtFuncCr_LimitDifference_MtrNm_D_f32 = LimitDifference_MtrNm_T_f32;
	PwrLmtFuncCr_TrqLmt_Uls_D_f32 = TrqLmt_Uls_T_f32;
	
	
	Rte_IWrite_PwrLmtFuncCr_Per2_FltTrqLmt_Uls_f32(FltTrqLmt_Uls_T_f32);
	Rte_IWrite_PwrLmtFuncCr_Per2_ThresholdExceeded_Cnt_lgc(PwrLmtFuncCr_ThresholdExceeded_Cnt_M_lgc);
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_PwrLmtFuncCr_Per2_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_PWRLMTFUNCCR_APPL_CODE
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
