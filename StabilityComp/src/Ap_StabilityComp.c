/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_StabilityComp.c
 *     Workspace:  C:/CMSynergy_Projects/CBD/StabilityComp/autosar
 *     SW-C Type:  Ap_StabilityComp
 *  Generated at:  Tue Apr 30 14:02:02 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_StabilityComp>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Wed Jun 14 09:14:52 2011
 * %version:          16 %
 * %derived_by:       bz1q07 %
 * %date_modified:    Thu Dec  5 13:42:54 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 11/28/11   1       JJW       Initial Component Creation
 * 11/30/11   1.1     VK        Add display variables as per the FDD
 * 02/02/12   2       M. Story  Limit outputs
 * 05/02/12   3       OT        Updated to SF-29 rev 3                                                         5315
 * 09/23/12   4        Selva    Checkpoints added and mempmap macros corrected		                          6249
 * 09/26/12   5        Selva    Regenerated C file for memmap corrections		                              6249
 * 10/15/12	  6		  LN		Addition of LPF of handwheel torque to the compensator blend tables.
 * 								Added functionality to allow compensators 2 and 4 to blend to zero.			   6482
 * 10/24/12	  7		  LN		Template Regeneration, no source code changes.								   6482
 * 02/11/13   8       Selva     anamoly 4402 fixed		
 * 02/22/13   9		  SP		Updated to SF-29 v006 
 * 03/08/13	 10		  SP		Removed the #define NTC_Num_StCmpCorr which was added for QAC purpose
 * 04/02/13  12       NRAR      Anom 4609- fixed Wrong function call of FaultInjection                         #7776
 * 04/12/13	 13		  SP		Anomaly fixed																   #7857
 * 04/13/13  14	  	  SP		Updated to SF-29 v007														   #7893
 * 04/30/13  15	  	  LWW		Corrected NTC enum name per standard definition
 * 12/06/13  16       VT        Anomaly 5573 fix                                                               10980
*/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_StabilityComp.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "filters.h"
#include "CalConstants.h"
#include "GlobalMacro.h"
#include "interpolation.h"
#include "Ap_StabilityComp_Cfg.h"
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

#define STABILITYCOMP_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
STATIC VAR(uint16, AP_DAMPINGFIREWALL_VAR_NOINIT) StCmpPNAccum_Cnt_M_u16;
#define STABILITYCOMP_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

#define STABILITYCOMP_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(float32, AUTOMATIC) StCmpAsstFctrCmpBlnd_Uls_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) StCmp12Blend_Uls_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) StCmp34Blend_Uls_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) StCmp02Blend_Uls_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) StCmp04Blend_Uls_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) StCmp1Out_MtrNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) StCmp2Out_MtrNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) StCmp3Out_MtrNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) StCmp4Out_MtrNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) AssistCmdSV_MtrNm_M_f32;
#define STABILITYCOMP_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define STABILITYCOMP_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(boolean, AUTOMATIC) StabCompOverThresh_Cnt_D_lgc;
STATIC VAR(boolean, AUTOMATIC) StCmpPNStatus_Cnt_M_lgc;
#define STABILITYCOMP_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define STABILITYCOMP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(NotchFiltSV_Str, AUTOMATIC) CombAstNFSV_Cnt_M_Str[D_NUMNOTCHFILT_CNT_U08];
STATIC VAR(LPF32KSV_Str, AUTOMATIC) HwTrqSV_HwNm_M_Str;
#define STABILITYCOMP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

STATIC FUNC(float32, RTE_AP_STABILITYCOMP_APPL_CODE) ApplyStabilityComp(VAR(float32, AUTOMATIC) Assist_MtrNm_T_f32,
																 P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) FiltSVPtr_Uls_T_Str, 
																 P2CONST(float32, AUTOMATIC, AUTOMATIC) CompBlnd_Uls_T_f32, 
																 VAR(float32, AUTOMATIC) ADDFBlend_Uls_T_f32,
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
 * Boolean: Boolean (standard type)
 * Float: Real in interval ]-FLT_MAX...FLT_MAX[ with single precision (standard type)
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
 * NTCNumber: Enumeration of integer in interval [0...511] with enumerators
 *   NTC_Num_FlashWrapperLgcFlt (1u)
 *   NTC_Num_FlashECCCorr (2u)
 *   NTC_Num_FlashECCMemFlt (3u)
 *   NTC_Num_FlashCRCMemFault (4u)
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
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_STABILITYCOMP_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StabilityComp_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_STABILITYCOMP_APPL_CODE) StabilityComp_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: StabilityComp_Init1
 *********************************************************************************************************************/
	VAR(uint8, AUTOMATIC)   i;

	for ( i = 0U; i < D_NUMNOTCHFILT_CNT_U08; i++)
	{
		NF_Init_f32(D_ASSISTINIT_MTRNM_F32, &(CombAstNFSV_Cnt_M_Str[i]), &(t_StCmpNFK_Str[i]));
	}

	LPF_Init_f32_m(D_ZERO_ULS_F32, k_StCmpHwTrqLPFKn_Hz_f32, D_2MS_SEC_F32, &HwTrqSV_HwNm_M_Str);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StabilityComp_Per1
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
 *   Float Rte_IRead_StabilityComp_Per1_AssistDDFactor_Uls_f32(void)
 *   Float Rte_IRead_StabilityComp_Per1_AsstFWActive_Uls_f32(void)
 *   Float Rte_IRead_StabilityComp_Per1_CombinedAssist_MtrNm_f32(void)
 *   Float Rte_IRead_StabilityComp_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_StabilityComp_Per1_SysAssistCmd_MtrNm_MtrNm_f32(void)
 *   Float Rte_IRead_StabilityComp_Per1_VehicleSpeed_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_StabilityComp_Per1_AssistCmd_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_StabilityComp_Per1_AssistCmd_MtrNm_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FaultInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_STABILITYCOMP_APPL_CODE) StabilityComp_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: StabilityComp_Per1
 *********************************************************************************************************************/
	/* Input Signals */
	VAR(float32, AUTOMATIC) AssistDDFactor_Uls_T_f32;
	VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32;
	VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;
	VAR(float32, AUTOMATIC) CombinedAssist_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) AssistCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) SysAssistCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) AsstFWActive_Uls_T_f32;

	/* FPM Intermediates */
	VAR(uint16, AUTOMATIC) AssistDDFactor_Uls_T_u2p14;
	VAR(uint16, AUTOMATIC) HwTrq_HwNm_T_u8p8;
	VAR(uint16, AUTOMATIC) VehSpd_Kph_T_u9p7;

	/* Intermediate Variables */
	VAR(uint16, AUTOMATIC) CompBlnd_Uls_T_u2p14;
	VAR(float32, AUTOMATIC) CompBlnd_Uls_T_f32[D_NUMNFBLENDS_CNT_U08];
	VAR(uint16, AUTOMATIC) ADDFBlend_Uls_T_u2p14;
	VAR(float32, AUTOMATIC) ADDFBlend_Uls_T_f32;
	VAR(float32, AUTOMATIC) HwTrqFilt_HwNm_T_f32;
	
	VAR(DiagSettings_Str, AUTOMATIC) StCmpFWPstepNstep_Cnt_T_str;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_StabilityComp_Per1_CP0_CheckpointReached();
	
	StCmpFWPstepNstep_Cnt_T_str.PStep = k_StCmpStabCmpPstep_Cnt_u16;
	StCmpFWPstepNstep_Cnt_T_str.NStep = k_StCmpStabCmpNstep_Cnt_u16;
	StCmpFWPstepNstep_Cnt_T_str.Threshold = k_StCmpStabCmpPNThresh_Cnt_u16; 


	/* Store RTE elements to local variables for convienience */
	AssistDDFactor_Uls_T_f32 = Rte_IRead_StabilityComp_Per1_AssistDDFactor_Uls_f32();
	AsstFWActive_Uls_T_f32 = Rte_IRead_StabilityComp_Per1_AsstFWActive_Uls_f32();
	AssistDDFactor_Uls_T_u2p14 = FPM_FloatToFixed_m((AssistDDFactor_Uls_T_f32 + AsstFWActive_Uls_T_f32), u2p14_T);
	SysAssistCmd_MtrNm_T_f32 = Rte_IRead_StabilityComp_Per1_SysAssistCmd_MtrNm_MtrNm_f32();
	CombinedAssist_MtrNm_T_f32 = Rte_IRead_StabilityComp_Per1_CombinedAssist_MtrNm_f32();


	HwTorque_HwNm_T_f32 = Rte_IRead_StabilityComp_Per1_HwTorque_HwNm_f32();
	HwTrqFilt_HwNm_T_f32 = LPF_OpUpdate_f32_m(Abs_f32_m(HwTorque_HwNm_T_f32), &HwTrqSV_HwNm_M_Str);
	HwTrq_HwNm_T_u8p8 = FPM_FloatToFixed_m(HwTrqFilt_HwNm_T_f32, u8p8_T);

	VehicleSpeed_Kph_T_f32 = Rte_IRead_StabilityComp_Per1_VehicleSpeed_Kph_f32();
	VehSpd_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);


	CombinedAssist_MtrNm_T_f32 = Limit_m(CombinedAssist_MtrNm_T_f32, -D_COMPINLIMIT_MTRNM_F32, D_COMPINLIMIT_MTRNM_F32);

	/* Calculate Blend Fractions that are common to both compensator executions */
	/* Interpolate the ADDF_Blend */
	ADDFBlend_Uls_T_u2p14 = IntplVarXY_u16_u16Xu16Y_Cnt(
							t_StCmpADDFBlendX_Uls_u2p14,
							t_StCmpADDFBlendY_Uls_u2p14,
							TableSize_m(t_StCmpADDFBlendX_Uls_u2p14),
							AssistDDFactor_Uls_T_u2p14);

	ADDFBlend_Uls_T_f32 = FPM_FixedToFloat_m(ADDFBlend_Uls_T_u2p14, u2p14_T);

	StCmpAsstFctrCmpBlnd_Uls_D_f32 = ADDFBlend_Uls_T_f32;
							
	/* Interpolate the CompBlndFraction for Notch filters 1 and 2 */
	CompBlnd_Uls_T_u2p14 = BilinearXYM_u16_u16Xu16YM_Cnt(
		VehSpd_Kph_T_u9p7,
		HwTrq_HwNm_T_u8p8,
		t_StCmpBlendSpdBS_Kph_u9p7,
		TableSize_m(t_StCmpBlendSpdBS_Kph_u9p7),
		t_StCmpBlend12Trq_HwNm_u8p8,
		(P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_StCmpBlend12TblY_Uls_u2p14,
		TableSize_m(t_StCmpBlend12Trq_HwNm_u8p8));

	CompBlnd_Uls_T_f32[D_COMPBLND12IDX_CNT_U08] = FPM_FixedToFloat_m(CompBlnd_Uls_T_u2p14, u2p14_T);

	StCmp12Blend_Uls_D_f32 = CompBlnd_Uls_T_f32[D_COMPBLND12IDX_CNT_U08];

	/* Interpolate the CompBlndFraction for zero and Notch filter 2 */
	CompBlnd_Uls_T_u2p14 = BilinearXYM_u16_u16Xu16YM_Cnt(
		VehSpd_Kph_T_u9p7,
		HwTrq_HwNm_T_u8p8,
		t_StCmpBlendSpdBS_Kph_u9p7,
		TableSize_m(t_StCmpBlendSpdBS_Kph_u9p7),
		t_StCmpBlend12Trq_HwNm_u8p8,
		(P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_StCmpBlend02TblY_Uls_u2p14,
		TableSize_m(t_StCmpBlend12Trq_HwNm_u8p8));

	CompBlnd_Uls_T_f32[D_COMPBLND02IDX_CNT_U08] = FPM_FixedToFloat_m(CompBlnd_Uls_T_u2p14, u2p14_T);

	StCmp02Blend_Uls_D_f32 = CompBlnd_Uls_T_f32[D_COMPBLND02IDX_CNT_U08];

	/* Interpolate the CompBlndFraction for Notch filters 3 and 4 */
	CompBlnd_Uls_T_u2p14 = BilinearXYM_u16_u16Xu16YM_Cnt(
		VehSpd_Kph_T_u9p7,
		HwTrq_HwNm_T_u8p8,
		t_StCmpBlendSpdBS_Kph_u9p7,
		TableSize_m(t_StCmpBlendSpdBS_Kph_u9p7),
		t_StCmpBlend34Trq_HwNm_u8p8,
		(P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_StCmpBlend34TblY_Uls_u2p14,
		TableSize_m(t_StCmpBlend34Trq_HwNm_u8p8));

	CompBlnd_Uls_T_f32[D_COMPBLND34IDX_CNT_U08] = FPM_FixedToFloat_m(CompBlnd_Uls_T_u2p14, u2p14_T);

	StCmp34Blend_Uls_D_f32 = CompBlnd_Uls_T_f32[D_COMPBLND34IDX_CNT_U08];

	/* Interpolate the CompBlndFraction for zero and Notch filter 4 */
	CompBlnd_Uls_T_u2p14 = BilinearXYM_u16_u16Xu16YM_Cnt(
		VehSpd_Kph_T_u9p7,
		HwTrq_HwNm_T_u8p8,
		t_StCmpBlendSpdBS_Kph_u9p7,
		TableSize_m(t_StCmpBlendSpdBS_Kph_u9p7),
		t_StCmpBlend34Trq_HwNm_u8p8,
		(P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_StCmpBlend04TblY_Uls_u2p14,
		TableSize_m(t_StCmpBlend34Trq_HwNm_u8p8));

	CompBlnd_Uls_T_f32[D_COMPBLND04IDX_CNT_U08] = FPM_FixedToFloat_m(CompBlnd_Uls_T_u2p14, u2p14_T);

	StCmp04Blend_Uls_D_f32 = CompBlnd_Uls_T_f32[D_COMPBLND04IDX_CNT_U08];

	/* Execute compensator routines */
	AssistCmd_MtrNm_T_f32 = ApplyStabilityComp(CombinedAssist_MtrNm_T_f32, &(CombAstNFSV_Cnt_M_Str[0U]), CompBlnd_Uls_T_f32, ADDFBlend_Uls_T_f32, TRUE);

	/* Limit ouput values */
	AssistCmd_MtrNm_T_f32 = Limit_m(AssistCmd_MtrNm_T_f32, -D_ASSTSCLMT_MTRNM_F32, D_ASSTSCLMT_MTRNM_F32);

	/* Fault Injection */

	#if (STD_ON == BC_ASSISTCMD_FAULTINJECTIONPOINT)
	Rte_Call_FaultInjection_SCom_FltInjection(&AssistCmd_MtrNm_T_f32,FLTINJ_STABILITYCOMP);
	#endif

		
	/* Stability Compensation Correlation Diagnostic */
	
	if(Abs_f32_m(AssistCmdSV_MtrNm_M_f32 - SysAssistCmd_MtrNm_T_f32) >= k_StCmpSysCorrThresh_MtrNm_f32)
	{
		StCmpPNAccum_Cnt_M_u16 =  DiagPStep_m(StCmpPNAccum_Cnt_M_u16, StCmpFWPstepNstep_Cnt_T_str);
		StabCompOverThresh_Cnt_D_lgc = TRUE;
	}
	else
	{
		StCmpPNAccum_Cnt_M_u16 =  DiagNStep_m(StCmpPNAccum_Cnt_M_u16, StCmpFWPstepNstep_Cnt_T_str);
		StabCompOverThresh_Cnt_D_lgc = FALSE;
	}
	if(StCmpPNAccum_Cnt_M_u16 >= k_StCmpStabCmpPNThresh_Cnt_u16)
	{
		StCmpPNStatus_Cnt_M_lgc = TRUE;
	}
	else
	{
		StCmpPNStatus_Cnt_M_lgc = FALSE;
	}

	if((TRUE == StCmpPNStatus_Cnt_M_lgc) && (TRUE == k_StCmpCrosChkEnbl_Uls_lgc))
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_SigPath1CrossChk, 1U, NTC_STATUS_FAILED);
	}
	else
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_SigPath1CrossChk, 1U, NTC_STATUS_PASSED);
	}

	AssistCmdSV_MtrNm_M_f32 = AssistCmd_MtrNm_T_f32; /* Load 1/z SV for AssistCmd_MtrNm_T_f32 */

	/* Update output port values */
	Rte_IWrite_StabilityComp_Per1_AssistCmd_MtrNm_f32(AssistCmd_MtrNm_T_f32);


	/* Configurable End of Runnable Checkpoint */
	Rte_Call_StabilityComp_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_STABILITYCOMP_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
STATIC FUNC(float32, RTE_AP_STABILITYCOMP_APPL_CODE) ApplyStabilityComp(VAR(float32, AUTOMATIC) Assist_MtrNm_T_f32,
																 P2VAR(NotchFiltSV_Str, AUTOMATIC, AUTOMATIC) FiltSVPtr_Uls_T_Str, 
																 P2CONST(float32, AUTOMATIC, AUTOMATIC) CompBlnd_Uls_T_f32, 
																 VAR(float32, AUTOMATIC) ADDFBlend_Uls_T_f32,
																 VAR(boolean, AUTOMATIC) WriteDisplayVars_Cnt_T_lgc)
{
	VAR(uint8, AUTOMATIC)           i;
	VAR(float32, AUTOMATIC)			StCmp02Out_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)			StCmp04Out_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)			StCmp12Out_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)			StCmp34Out_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)			FilteredOutput_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)         AssistFilt_MtrNm_T_f32[D_NUMNOTCHFILT_CNT_U08];

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
		StCmp1Out_MtrNm_D_f32 = AssistFilt_MtrNm_T_f32[0U];
		StCmp2Out_MtrNm_D_f32 = StCmp02Out_MtrNm_T_f32;
		StCmp3Out_MtrNm_D_f32 = AssistFilt_MtrNm_T_f32[2U];
		StCmp4Out_MtrNm_D_f32 = StCmp04Out_MtrNm_T_f32;
	}

	/* Apply Drive Dynamics Blending */
	FilteredOutput_MtrNm_T_f32 = Blend_f32(StCmp12Out_MtrNm_T_f32, StCmp34Out_MtrNm_T_f32, ADDFBlend_Uls_T_f32);
	
	return(FilteredOutput_MtrNm_T_f32);
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
