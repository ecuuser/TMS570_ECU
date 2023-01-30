/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Sa_BkCpPc.c
 *     Workspace:  C:/_Synergy_Projects/Working/BkCpPc-nz63rn/BkCpPc/autosar
 *     SW-C Type:  Sa_BkCpPc
 *  Generated at:  Fri Nov  1 11:45:16 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Sa_BkCpPc>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Wed Sep 12 10:31:35 2012
 * %version:          11 %
 * %derived_by:       gz7pm0 %
 * %date_modified:    Fri Dec 13 14:08:05 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                           SCR #
 * --------  -------  --------  ---------------------------------------------------------------------------  ----------
 * 09/12/12  1        OT        Initial Version (FDD 11B v001)                                               6165
 * 09/27/12  2        OT        Added Trns2 (Warm Init state reset)                                          6365
 * 10/24/12  3        OT        Anomaly 3912 - write outputs in all branches                                 6632
 * 27/02/13	 4       Selva      Updated to version 3 FDD 11B                                                      
 * 03/01/13	 5	     Selva      Set RunTimeFaultAcc_Cnt_M_u16 to zero  in tans 2
 * 05/29/13	 6	      BDO       Anomaly 5092 - add power disconnect configurable parameter                   8486
 * 06/04/13  7        BDO       Anomaly 5122 - updates to support Configuration A integration                8543
 * 06/05/13  8        BDO       Set PwrDiscATestComplete in BULKCAP_PRECHARGE state for Configuration A      8543
 * 10/16/13  9        VK/KMC	A5150 fix(clearing NTC 44 during on entering warm init)						 10183
 *								Updated to version 4 FDD 11B for anomaly 5763 fix							 10515
 * 12/13/13  10		  LK        Updated to remove trailing else statements found in unit tests			     10682
 * 03/17/14	 11		  LK		Updated to revision 05 of FDD 11B											 11581
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
  Volt_f32 of Port Interface Voltage_Volt_f32
    This signal is intended to communicate any type voltage signal measured by the ecu.  This signal has a lower limit of 0 which reequires users of the signal to provide divide by 0 protection if it is used as a denominator in a calculation.  See Vecu port prototype if a port with a lower limit is desired.


 Operation Prototypes:
 =====================
  DtrmnElapsedTime_mS_u16 of Port Interface SystemTime
    Nexteer SystemTime Service


 Mode Declaration Groups:
 ========================
  StaMd_Mode
    EPS System State mode declaration

 *********************************************************************************************************************/

#include "Rte_Sa_BkCpPc.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "Sa_BkCpPc_Cfg.h"
#include "GlobalMacro.h"
#include "CalConstants.h"


#define D_VDISCHMAXFACTOR_ULS_F32	1.05f
#define D_VDISCHMINFACTOR_ULS_F32	0.95f
#define D_PWRDISCCONFIGB_CNT_U08    2U    /* Power Disconnect configuration A = 1, B = 2 */

typedef enum {
	BULKCAP_WAITFORSTARTA = 0u,
	BULKCAP_VERIFYDISCOPEN,
	BULKCAP_WAITFORSQRWAVE,
	BULKCAP_PRECHARGE,
	BULKCAP_WAITFORSTARTB,
	BULKCAP_POSTCLOSE,
	BULKCAP_VERIFYCLOSE,
	BULKCAP_RUNTIMEDIAG
} BulkCapPrechargeSequenceType;


#define BKCPPC_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, SA_BKCPPC_VAR) FirstRunComplete_Cnt_M_lgc;
STATIC VAR(boolean, SA_BKCPPC_VAR) PowerRelayInitFltFailed_Cnt_M_lgc;
STATIC VAR(boolean, SA_BKCPPC_VAR) PwrDiscATestComplete_Cnt_M_lgc;
STATIC VAR(boolean, SA_BKCPPC_VAR) PwrDiscBTestComplete_Cnt_M_lgc;
STATIC VAR(boolean, SA_BKCPPC_VAR) PwrDiscClosed_Cnt_M_lgc;
STATIC VAR(BulkCapPrechargeSequenceType, SA_BKCPPC_VAR) BulkCapPrechargeState_Cnt_M_enum;
STATIC volatile VAR(boolean, SA_BKCPPC_VAR) MotionDetected_Cnt_D_lgc;
#define BKCPPC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


#define BKCPPC_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, SA_BKCPPC_VAR) RunTimeFaultAcc_Cnt_M_u16;
STATIC VAR(uint16, SA_BKCPPC_VAR) VerifyPwrDiscCloseErrAcc_Cnt_M_u16;
#define BKCPPC_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */


#define BKCPPC_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint32,  SA_BKCPPC_VAR) VerifyDiscOpenDiagTimer_mS_M_u32;
STATIC VAR(uint32,  SA_BKCPPC_VAR) WaitForSqrWaveDiagTimer_mS_M_u32;
STATIC VAR(uint32,  SA_BKCPPC_VAR) PrechargeDiagTimer_mS_M_u32;
STATIC VAR(uint32,  SA_BKCPPC_VAR) PostCloseDiagTimer_mS_M_u32;
STATIC VAR(uint32,  SA_BKCPPC_VAR) VerifyCloseDiagTimer_mS_M_u32;
STATIC VAR(float32, SA_BKCPPC_VAR) VdischMax_Volts_M_f32;
STATIC VAR(float32, SA_BKCPPC_VAR) VdischMin_Volts_M_f32;
STATIC VAR(float32, SA_BKCPPC_VAR) VbattStart_Volts_M_f32;
STATIC VAR(float32, SA_BKCPPC_VAR) VswitchStart_Volts_M_f32;
STATIC volatile VAR(float32, SA_BKCPPC_VAR) DeltaV_Volts_D_f32;
STATIC volatile VAR(float32, SA_BKCPPC_VAR) VswitchCorrected_Volts_D_f32;
#define BKCPPC_STOP_SEC_VAR_CLEARED_32
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
 * IoHwAb_BoolType: Integer in interval [0...1]
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
 *   NTC_Num_TunSetNotPrgmd (499u)
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
 * Float: D_ZERO_ULS_F32 = 0
 * UInt16: D_ZERO_CNT_U16 = 0u
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_SA_BKCPPC_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: BkCpPc_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <OFF, DISABLE>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_BkCpPc_Per1_BattSwitched_Volt_f32(void)
 *   Float Rte_IRead_BkCpPc_Per1_Batt_Volt_f32(void)
 *   Float Rte_IRead_BkCpPc_Per1_MotorVelocityMRFUnfiltered_MtrRadpS_f32(void)
 *   Float Rte_IRead_BkCpPc_Per1_OVERRIDESIGDIAGADC_Volt_f32(void)
 *   Float Rte_IRead_BkCpPc_Per1_PMOSDIAGADC_Volt_f32(void)
 *   Boolean Rte_IRead_BkCpPc_Per1_PwrDiscATestStart_Cnt_lgc(void)
 *   Boolean Rte_IRead_BkCpPc_Per1_PwrDiscBTestStart_Cnt_lgc(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_BkCpPc_Per1_PwrDiscATestComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_BkCpPc_Per1_PwrDiscATestComplete_Cnt_lgc(void)
 *   void Rte_IWrite_BkCpPc_Per1_PwrDiscBTestComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_BkCpPc_Per1_PwrDiscBTestComplete_Cnt_lgc(void)
 *   void Rte_IWrite_BkCpPc_Per1_PwrDiscClosed_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_BkCpPc_Per1_PwrDiscClosed_Cnt_lgc(void)
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
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *   Std_ReturnType Rte_Call_PhyCapDischarge_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DigitalOut_E_NOT_OK
 *   Std_ReturnType Rte_Call_PhyCapPrecharge_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DigitalOut_E_NOT_OK
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

FUNC(void, RTE_SA_BKCPPC_APPL_CODE) BkCpPc_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: BkCpPc_Per1
 *********************************************************************************************************************/
	
	
	VAR(float32, AUTOMATIC) MotorVelocityMRFUnfiltered_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) OVERRIDESIGDIAGADC_Volt_T_f32;
	VAR(float32, AUTOMATIC) PMOSDIAGADC_Volt_T_f32;
	VAR(boolean, AUTOMATIC) PwrDiscATestStart_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) PwrDiscBTestStart_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) Vbatt_Volts_T_f32;
	VAR(float32, AUTOMATIC) Vswitch_Volts_T_f32;
	
	VAR(boolean, AUTOMATIC) MotionDetected_Cnt_T_lgc;
	
	VAR(float32, AUTOMATIC) DeltaV_Volts_T_f32;
	
	VAR(uint16,  AUTOMATIC) ElapsedTime_mS_T_u16;
	
	VAR(float32, AUTOMATIC) AbsDeltaVswitch_Volts_T_f32;
	VAR(float32, AUTOMATIC) ChargeMinDelta_Volts_T_f32;
	
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_BkCpPc_Per1_CP0_CheckpointReached();
	
	
	MotorVelocityMRFUnfiltered_MtrRadpS_T_f32 = Rte_IRead_BkCpPc_Per1_MotorVelocityMRFUnfiltered_MtrRadpS_f32();
	OVERRIDESIGDIAGADC_Volt_T_f32 = Rte_IRead_BkCpPc_Per1_OVERRIDESIGDIAGADC_Volt_f32();
	PMOSDIAGADC_Volt_T_f32 = Rte_IRead_BkCpPc_Per1_PMOSDIAGADC_Volt_f32();
	PwrDiscATestStart_Cnt_T_lgc = Rte_IRead_BkCpPc_Per1_PwrDiscATestStart_Cnt_lgc();
	PwrDiscBTestStart_Cnt_T_lgc = Rte_IRead_BkCpPc_Per1_PwrDiscBTestStart_Cnt_lgc();
	Vbatt_Volts_T_f32 = Rte_IRead_BkCpPc_Per1_Batt_Volt_f32();
	Vswitch_Volts_T_f32 = Rte_IRead_BkCpPc_Per1_BattSwitched_Volt_f32();
	
	
	/*** Motor Motion Check ***/
	if (D_PWRDISCCONFIGURATION_CNT_U08 == D_PWRDISCCONFIGB_CNT_U08)
	{
		if( Abs_f32_m(MotorVelocityMRFUnfiltered_MtrRadpS_T_f32) > k_MtrMotionThresh_MtrRadpS_f32 )
		{
			MotionDetected_Cnt_T_lgc = TRUE;
		}
		else
		{
			MotionDetected_Cnt_T_lgc = FALSE;
		}
	}
	else
	{   /* Default to PWRDISCCONFIGA */
		MotionDetected_Cnt_T_lgc = FALSE;
	}
	
	MotionDetected_Cnt_D_lgc = MotionDetected_Cnt_T_lgc;
	
	
	
	/*** Calculate Delta Voltage ***/
	
	DeltaV_Volts_T_f32 = Min_m(k_MaxSwitchedVolt_Volts_f32, Vbatt_Volts_T_f32) - Vswitch_Volts_T_f32;
	
	DeltaV_Volts_D_f32 = DeltaV_Volts_T_f32;
	
	
	
	/*** State Determination and Power Disconnect Sequence A Control ***/
	
	switch( BulkCapPrechargeState_Cnt_M_enum )
	{
		case BULKCAP_WAITFORSTARTA:
			if( PwrDiscATestStart_Cnt_T_lgc == TRUE )
			{
				PowerRelayInitFltFailed_Cnt_M_lgc = FALSE;
				if( FirstRunComplete_Cnt_M_lgc == FALSE )
				{
					BulkCapPrechargeState_Cnt_M_enum = BULKCAP_VERIFYDISCOPEN;
					(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&VerifyDiscOpenDiagTimer_mS_M_u32);
					FirstRunComplete_Cnt_M_lgc = TRUE;

					if (D_PWRDISCCONFIGURATION_CNT_U08 == D_PWRDISCCONFIGB_CNT_U08)
					{
						(void)Rte_Call_PhyCapPrecharge_OP_SET(STD_LOW);
						(void)Rte_Call_PhyCapDischarge_OP_SET(STD_HIGH);
					}
				}
				else
				{
					BulkCapPrechargeState_Cnt_M_enum = BULKCAP_WAITFORSQRWAVE;
					(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&WaitForSqrWaveDiagTimer_mS_M_u32);

					if (D_PWRDISCCONFIGURATION_CNT_U08 == D_PWRDISCCONFIGB_CNT_U08)
					{
						(void)Rte_Call_PhyCapPrecharge_OP_SET(STD_LOW);
						(void)Rte_Call_PhyCapDischarge_OP_SET(STD_LOW);
					}
				}
			}
			break;
		
		case BULKCAP_VERIFYDISCOPEN:
			if (D_PWRDISCCONFIGURATION_CNT_U08 == D_PWRDISCCONFIGB_CNT_U08)
			{
				if( (DeltaV_Volts_T_f32 >= k_PwrDiscOpenThresh_Volts_f32) &&
					(PMOSDIAGADC_Volt_T_f32 <= k_PMOSDIAGOpenThresh_Volts_f32) &&
					(OVERRIDESIGDIAGADC_Volt_T_f32 <= k_OVERRIDESIGDIAGOpenThresh_Volts_f32) )
				{	/* transition to wait for charge pump square wave state */
					BulkCapPrechargeState_Cnt_M_enum = BULKCAP_WAITFORSQRWAVE;
					(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&WaitForSqrWaveDiagTimer_mS_M_u32);
					(void)Rte_Call_PhyCapPrecharge_OP_SET(STD_LOW);
					(void)Rte_Call_PhyCapDischarge_OP_SET(STD_LOW);
				}
				else if( MotionDetected_Cnt_T_lgc == TRUE )
				{
					(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&VerifyDiscOpenDiagTimer_mS_M_u32);
				}
				else
				{
					(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(VerifyDiscOpenDiagTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
					if( ElapsedTime_mS_T_u16 > k_VerifyPwrDiscOpenThresh_mS_u16 )
					{
						if( DeltaV_Volts_T_f32 < k_PwrDiscOpenThresh_Volts_f32 )
						{
							(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayInitFlt, 0x01u, NTC_STATUS_FAILED);
							PowerRelayInitFltFailed_Cnt_M_lgc = TRUE;
						}
						else if( PMOSDIAGADC_Volt_T_f32 > k_PMOSDIAGOpenThresh_Volts_f32 )
						{
							(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayInitFlt, 0x04u, NTC_STATUS_FAILED);
							PowerRelayInitFltFailed_Cnt_M_lgc = TRUE;
						}
						else 
						{
						     /* only case left is (OVERRIDESIGDIAGADC_Volt_T_f32 > k_OVERRIDESIGDIAGOpenThresh_Volts_f32) */
							(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayInitFlt, 0x08u, NTC_STATUS_FAILED);
							PowerRelayInitFltFailed_Cnt_M_lgc = TRUE;
						}
						
						
						/* transition to wait for charge pump square wave state */
						BulkCapPrechargeState_Cnt_M_enum = BULKCAP_WAITFORSQRWAVE;
						(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&WaitForSqrWaveDiagTimer_mS_M_u32);
						(void)Rte_Call_PhyCapPrecharge_OP_SET(STD_LOW);
						(void)Rte_Call_PhyCapDischarge_OP_SET(STD_LOW);
				
					}
				}
			}
			else
			{ /* Default to PWRDISCCONFIGA */
				if(DeltaV_Volts_T_f32 >= k_PwrDiscOpenThresh_Volts_f32)
				{
					BulkCapPrechargeState_Cnt_M_enum = BULKCAP_WAITFORSQRWAVE;
				}
				else
				{
					(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(VerifyDiscOpenDiagTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
					if( ElapsedTime_mS_T_u16 > k_VerifyPwrDiscOpenThresh_mS_u16 )
					{
						(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayInitFlt, 0x01u, NTC_STATUS_FAILED);
						PowerRelayInitFltFailed_Cnt_M_lgc = TRUE;
						
						/** transition to wait for charge pump square wave state **/
						 BulkCapPrechargeState_Cnt_M_enum = BULKCAP_WAITFORSQRWAVE;
					}
				}
			}
			break;
		
		case BULKCAP_WAITFORSQRWAVE:
			if (D_PWRDISCCONFIGURATION_CNT_U08 == D_PWRDISCCONFIGB_CNT_U08)
			{
				(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(WaitForSqrWaveDiagTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
				if( ElapsedTime_mS_T_u16 >= k_WaitForSqrWaveThresh_mS_u16 )
				{
					BulkCapPrechargeState_Cnt_M_enum = BULKCAP_PRECHARGE;
					(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&PrechargeDiagTimer_mS_M_u32);
					(void)Rte_Call_PhyCapPrecharge_OP_SET(STD_HIGH);
					(void)Rte_Call_PhyCapDischarge_OP_SET(STD_LOW);
				}
			}
			else
			{ /* Default to PWRDISCCONFIGA */
				BulkCapPrechargeState_Cnt_M_enum = BULKCAP_PRECHARGE;
			}
			break;
		
		case BULKCAP_PRECHARGE:
			if (D_PWRDISCCONFIGURATION_CNT_U08 == D_PWRDISCCONFIGB_CNT_U08)
			{
				if( (DeltaV_Volts_T_f32 <= k_PwrDiscCloseThresh_Volts_f32) &&
					(PMOSDIAGADC_Volt_T_f32 <= k_PMOSDIAGOpenThresh_Volts_f32) &&
					(OVERRIDESIGDIAGADC_Volt_T_f32 <= k_OVERRIDESIGDIAGOpenThresh_Volts_f32) &&
					(Vbatt_Volts_T_f32 < k_MaxSwitchedVolt_Volts_f32) )
				{
					BulkCapPrechargeState_Cnt_M_enum = BULKCAP_WAITFORSTARTB;
					PwrDiscATestComplete_Cnt_M_lgc = TRUE;
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PrechargeFailure, 0u, NTC_STATUS_PASSED);
				}
				else
				{
					(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(PrechargeDiagTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
					if( ElapsedTime_mS_T_u16 > k_PrechargeThresh_mS_u16 )
					{
						if( DeltaV_Volts_T_f32 > k_PwrDiscCloseThresh_Volts_f32 )
						{
							(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PrechargeFailure, 0x01u, NTC_STATUS_FAILED);
						}
						else if( PMOSDIAGADC_Volt_T_f32 > k_PMOSDIAGOpenThresh_Volts_f32 )
						{
							(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PrechargeFailure, 0x04u, NTC_STATUS_FAILED);
						}
						else if( OVERRIDESIGDIAGADC_Volt_T_f32 > k_OVERRIDESIGDIAGOpenThresh_Volts_f32 )
						{
							(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PrechargeFailure, 0x08u, NTC_STATUS_FAILED);
						}
						else 
						{
							/*only case left is( Vbatt_Volts_T_f32 >= k_MaxSwitchedVolt_Volts_f32) */
							(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PrechargeFailure, 0x10u, NTC_STATUS_FAILED);
						}				
						BulkCapPrechargeState_Cnt_M_enum = BULKCAP_WAITFORSTARTB;
						PwrDiscATestComplete_Cnt_M_lgc = TRUE;
					}
				}
			}
			else
			{ /* Default to PWRDISCCONFIGA */
				BulkCapPrechargeState_Cnt_M_enum = BULKCAP_WAITFORSTARTB;
				PwrDiscATestComplete_Cnt_M_lgc = TRUE;
			}
			break;
		
		case BULKCAP_WAITFORSTARTB:
			if( PwrDiscBTestStart_Cnt_T_lgc == TRUE )
			{
				BulkCapPrechargeState_Cnt_M_enum = BULKCAP_POSTCLOSE;
				(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&PostCloseDiagTimer_mS_M_u32);
			}
			break;
		
		case BULKCAP_POSTCLOSE:
			if (D_PWRDISCCONFIGURATION_CNT_U08 == D_PWRDISCCONFIGB_CNT_U08)
			{
				(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(PostCloseDiagTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
				if(( (Abs_f32_m(Vbatt_Volts_T_f32 - PMOSDIAGADC_Volt_T_f32)) < k_PMOSVError_Volts_f32 )&& (ElapsedTime_mS_T_u16 > (k_PMOSTError_mS_u16>>2)) )
				{ /* transition to verify power disconnect close state */
					BulkCapPrechargeState_Cnt_M_enum = BULKCAP_VERIFYCLOSE;
					(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&VerifyCloseDiagTimer_mS_M_u32);
					VdischMax_Volts_M_f32 = Vswitch_Volts_T_f32 * D_VDISCHMAXFACTOR_ULS_F32;
					VdischMin_Volts_M_f32 = Vswitch_Volts_T_f32 * D_VDISCHMINFACTOR_ULS_F32;
					VbattStart_Volts_M_f32 = Vbatt_Volts_T_f32;
					VswitchStart_Volts_M_f32 = Vswitch_Volts_T_f32;
					(void)Rte_Call_PhyCapPrecharge_OP_SET(STD_LOW);
					(void)Rte_Call_PhyCapDischarge_OP_SET(STD_HIGH);
				}
				else
				{
					if( ElapsedTime_mS_T_u16 > k_PMOSTError_mS_u16 )
					{
						(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayInitFlt, 0x10u, NTC_STATUS_FAILED);
						PowerRelayInitFltFailed_Cnt_M_lgc = TRUE;
						/* transition to verify power disconnect close state */
						BulkCapPrechargeState_Cnt_M_enum = BULKCAP_VERIFYCLOSE;
						(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&VerifyCloseDiagTimer_mS_M_u32);
						VdischMax_Volts_M_f32 = Vswitch_Volts_T_f32 * D_VDISCHMAXFACTOR_ULS_F32;
						VdischMin_Volts_M_f32 = Vswitch_Volts_T_f32 * D_VDISCHMINFACTOR_ULS_F32;
						VbattStart_Volts_M_f32 = Vbatt_Volts_T_f32;
						VswitchStart_Volts_M_f32 = Vswitch_Volts_T_f32;
						(void)Rte_Call_PhyCapPrecharge_OP_SET(STD_LOW);
						(void)Rte_Call_PhyCapDischarge_OP_SET(STD_HIGH);
					}
				}
			}
			else
			{ /* Default to PWRDISCCONFIGA */
				BulkCapPrechargeState_Cnt_M_enum = BULKCAP_VERIFYCLOSE;
			}
			break;
		
		case BULKCAP_VERIFYCLOSE:
			if (D_PWRDISCCONFIGURATION_CNT_U08 == D_PWRDISCCONFIGB_CNT_U08)
			{
				VdischMax_Volts_M_f32 *= k_MaxDischEst_Uls_f32;
				VdischMin_Volts_M_f32 *= k_MinDischEst_Uls_f32;
				AbsDeltaVswitch_Volts_T_f32 = Abs_f32_m(VswitchStart_Volts_M_f32 - VbattStart_Volts_M_f32);
				
				if( ( (Vswitch_Volts_T_f32 > VdischMax_Volts_M_f32) ||
					  (Vswitch_Volts_T_f32 < VdischMin_Volts_M_f32) ) &&
				(AbsDeltaVswitch_Volts_T_f32 <= k_VswitchDeltaThresh_Volts_f32) )
				{
					PwrDiscBTestComplete_Cnt_M_lgc = TRUE;
					PwrDiscClosed_Cnt_M_lgc = TRUE;
					
					VerifyPwrDiscCloseErrAcc_Cnt_M_u16 = DiagNStep_m(VerifyPwrDiscCloseErrAcc_Cnt_M_u16, k_VerifyPwrDiscCloseDiag_Cnt_str);

					if(( VerifyPwrDiscCloseErrAcc_Cnt_M_u16 == D_ZERO_CNT_U16 ))
					{
						BulkCapPrechargeState_Cnt_M_enum = BULKCAP_RUNTIMEDIAG;
						
						if( PowerRelayInitFltFailed_Cnt_M_lgc == FALSE )
						{
							(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayInitFlt, 0x0U, NTC_STATUS_PASSED);
						}
					}
					(void)Rte_Call_PhyCapPrecharge_OP_SET(STD_LOW);
					(void)Rte_Call_PhyCapDischarge_OP_SET(STD_LOW);
				}
				else
				{
					(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(VerifyCloseDiagTimer_mS_M_u32, &ElapsedTime_mS_T_u16);

					if(AbsDeltaVswitch_Volts_T_f32 > k_VswitchDeltaThresh_Volts_f32)
					{
						VerifyPwrDiscCloseErrAcc_Cnt_M_u16 = DiagPStep_m(VerifyPwrDiscCloseErrAcc_Cnt_M_u16, k_VerifyPwrDiscCloseDiag_Cnt_str);

						if( DiagFailed_m(VerifyPwrDiscCloseErrAcc_Cnt_M_u16, k_VerifyPwrDiscCloseDiag_Cnt_str) == TRUE )
						{
							(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayInitFlt, 0x02U, NTC_STATUS_FAILED); /*Bit 1*/
							PowerRelayInitFltFailed_Cnt_M_lgc = TRUE;
							PwrDiscBTestComplete_Cnt_M_lgc = TRUE;
						}
					}
					
					else if(ElapsedTime_mS_T_u16 >= k_VerifyPwrDiscCloseThresh_mS_u16)
					{
					
							(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayInitFlt, 0x20u, NTC_STATUS_FAILED);/*Bit 5*/
							PowerRelayInitFltFailed_Cnt_M_lgc = TRUE;
							PwrDiscBTestComplete_Cnt_M_lgc = TRUE;
					}
					else
					{
							/*do nothing*/
					}
				}
			}
			else
			{ /* Default to PWRDISCCONFIGA */
				BulkCapPrechargeState_Cnt_M_enum = BULKCAP_RUNTIMEDIAG;
				PwrDiscBTestComplete_Cnt_M_lgc = TRUE;
				PwrDiscClosed_Cnt_M_lgc = TRUE;

				if( PowerRelayInitFltFailed_Cnt_M_lgc == FALSE )
				{
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayInitFlt, 0u, NTC_STATUS_PASSED);
				}
			}
			break;
		
		case BULKCAP_RUNTIMEDIAG:
			if (D_PWRDISCCONFIGURATION_CNT_U08 == D_PWRDISCCONFIGB_CNT_U08)
			{
				if (Vbatt_Volts_T_f32 < k_VbattSwitchThreshNonExt_Volt_f32)
				{
					ChargeMinDelta_Volts_T_f32 = k_ChargeMinDeltaNonOp_Volt_f32;
				}
				else if (Vbatt_Volts_T_f32 <  k_VbattSwitchThreshExNorm_Volt_f32 )
				{
					ChargeMinDelta_Volts_T_f32 = k_ChargeMinDeltaExtOp_Volt_f32 ;
				}
				else
				{
					ChargeMinDelta_Volts_T_f32 = k_ChargeMinDeltaNormlOp_Volt_f32 ;
				}
				if( (OVERRIDESIGDIAGADC_Volt_T_f32 - Vbatt_Volts_T_f32) <= ChargeMinDelta_Volts_T_f32 )
				{
					RunTimeFaultAcc_Cnt_M_u16 = DiagPStep_m(RunTimeFaultAcc_Cnt_M_u16, k_ChargePumpDiag_Cnt_str);
					if( DiagFailed_m(RunTimeFaultAcc_Cnt_M_u16, k_ChargePumpDiag_Cnt_str) == TRUE )
					{
						(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayRunFlt, 0x01u, NTC_STATUS_FAILED);
					}
				}
				else
				{
					RunTimeFaultAcc_Cnt_M_u16 = DiagNStep_m(RunTimeFaultAcc_Cnt_M_u16, k_ChargePumpDiag_Cnt_str);
					if( RunTimeFaultAcc_Cnt_M_u16 == D_ZERO_CNT_U16 )
					{
						(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayRunFlt, 0u, NTC_STATUS_PASSED);
					}
				}
			}
			break;
		
		default:
			break;
	}
	
	Rte_IWrite_BkCpPc_Per1_PwrDiscATestComplete_Cnt_lgc(PwrDiscATestComplete_Cnt_M_lgc);
	Rte_IWrite_BkCpPc_Per1_PwrDiscBTestComplete_Cnt_lgc(PwrDiscBTestComplete_Cnt_M_lgc);
	Rte_IWrite_BkCpPc_Per1_PwrDiscClosed_Cnt_lgc(PwrDiscClosed_Cnt_M_lgc);
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_BkCpPc_Per1_CP1_CheckpointReached();
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: BkCpPc_Trns1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on entering of Mode <DISABLE> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_BkCpPc_Trns1_PwrDiscATestComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_BkCpPc_Trns1_PwrDiscATestComplete_Cnt_lgc(void)
 *   void Rte_IWrite_BkCpPc_Trns1_PwrDiscBTestComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_BkCpPc_Trns1_PwrDiscBTestComplete_Cnt_lgc(void)
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
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *   Std_ReturnType Rte_Call_PhyCapDischarge_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DigitalOut_E_NOT_OK
 *   Std_ReturnType Rte_Call_PhyCapPrecharge_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DigitalOut_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_BKCPPC_APPL_CODE) BkCpPc_Trns1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: BkCpPc_Trns1
 *********************************************************************************************************************/
	
	if (D_PWRDISCCONFIGURATION_CNT_U08 == D_PWRDISCCONFIGB_CNT_U08)
	{
		(void)Rte_Call_PhyCapPrecharge_OP_SET(STD_LOW);
		(void)Rte_Call_PhyCapDischarge_OP_SET(STD_LOW);
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PowerRelayRunFlt, 0u, NTC_STATUS_PASSED);
	}
	
	PwrDiscATestComplete_Cnt_M_lgc = FALSE;
	Rte_IWrite_BkCpPc_Trns1_PwrDiscATestComplete_Cnt_lgc(FALSE);
	PwrDiscBTestComplete_Cnt_M_lgc = FALSE;
	Rte_IWrite_BkCpPc_Trns1_PwrDiscBTestComplete_Cnt_lgc(FALSE);
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: BkCpPc_Trns2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on entering of Mode <WARMINIT> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_BkCpPc_Trns2_PwrDiscATestComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_BkCpPc_Trns2_PwrDiscATestComplete_Cnt_lgc(void)
 *   void Rte_IWrite_BkCpPc_Trns2_PwrDiscBTestComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_BkCpPc_Trns2_PwrDiscBTestComplete_Cnt_lgc(void)
 *   void Rte_IWrite_BkCpPc_Trns2_PwrDiscClosed_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_BkCpPc_Trns2_PwrDiscClosed_Cnt_lgc(void)
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
 *   Std_ReturnType Rte_Call_PhyCapDischarge_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DigitalOut_E_NOT_OK
 *   Std_ReturnType Rte_Call_PhyCapPrecharge_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DigitalOut_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_BKCPPC_APPL_CODE) BkCpPc_Trns2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: BkCpPc_Trns2
 *********************************************************************************************************************/
	
	if (D_PWRDISCCONFIGURATION_CNT_U08 == D_PWRDISCCONFIGB_CNT_U08)
	{
		(void)Rte_Call_PhyCapDischarge_OP_SET(STD_LOW);
		(void)Rte_Call_PhyCapPrecharge_OP_SET(STD_LOW);
	}
	
	PwrDiscATestComplete_Cnt_M_lgc = FALSE;
	Rte_IWrite_BkCpPc_Trns2_PwrDiscATestComplete_Cnt_lgc(FALSE);
	PwrDiscBTestComplete_Cnt_M_lgc = FALSE;
	Rte_IWrite_BkCpPc_Trns2_PwrDiscBTestComplete_Cnt_lgc(FALSE);
	PwrDiscClosed_Cnt_M_lgc = FALSE;
	Rte_IWrite_BkCpPc_Trns2_PwrDiscClosed_Cnt_lgc(FALSE);
	BulkCapPrechargeState_Cnt_M_enum = BULKCAP_WAITFORSTARTA;
	RunTimeFaultAcc_Cnt_M_u16 = D_ZERO_CNT_U16;
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CapPcDcStub_OP_SET
 *
 * This runnable can be invoked concurrently (reentrant implementation).
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <OP_SET> of PortPrototype <CapPcDcStub>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType CapPcDcStub_OP_SET(IoHwAb_BoolType signal)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DigitalOut_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_SA_BKCPPC_APPL_CODE) CapPcDcStub_OP_SET(IoHwAb_BoolType signal)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CapPcDcStub_OP_SET (returns application error)
 *********************************************************************************************************************/

  /* Capacitor Discharge/Precharge server stub for Configuration A - See '6.8.1.1 Design Rationale' in MDD for details */
  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_SA_BKCPPC_APPL_CODE
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
