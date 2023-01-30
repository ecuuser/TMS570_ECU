/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_BatteryVoltage.c
 *     Workspace:  C:/Workspace/BatteryVoltage-CBD_BatteryVoltage/FDD08B/BatteryVoltage/autosar
 *     SW-C Type:  Ap_BatteryVoltage
 *  Generated at:  Fri Jan  3 12:57:35 2014
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_BatteryVoltage>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Apr 30 17:16:01 2012
 * %version:          10 %
 * %derived_by:       wz7x3j %
 * %date_modified:    Wed Jan  8 18:18:58 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 04/30/12   1       Jared     Initial component created from BMW project                                    5201
 * 10/17/12   2       NRAR      (ver after component is created)                                              6217
 * 10/17/12   3       NRAR      Updated to FDD Ver 04, Per2 with B1,B4 diag is deleted.                       6217
 * 10/29/12   4       NRAR      changed from client server port type to Sender/Receiver port                  6217
 * 10/29/12   5       NRAR      Updated Per2 SYSTEMSTATE                                                      6217
 * 10/29/12   6       NRAR      Removed unused constants from dcf                                             6217
 * 04/16/13   7       Jared     Updated to FDD Ver 005 - new overvoltage SCom functions                       7860
 * 06/26/13   8       SR        Updated to FDD Ver 006 and anomaly 5138 correction                            8558
 * 12/18/13   9       Jared     Added missing ISR to solve A5789                                              11068
 * 01/08/14	  10      BDO       Use NxtrDiagMgr???_ReportNTCStatus when setting NTC $B6, anomaly 6204         11173
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Data Types:
 ===========
  NvM_DestPtr
    DataPtr Type to be used by WriteBlock, ReadBlock and RestoreBlockDefaults operations. 	This type is used for all NVRAM blocks


 Data Element Prototypes:
 ========================
  Volt_f32 of Port Interface Voltage_Volt_f32
    This signal is intended to communicate any type voltage signal measured by the ecu.  This signal has a lower limit of 0 which reequires users of the signal to provide divide by 0 protection if it is used as a denominator in a calculation.  See Vecu port prototype if a port with a lower limit is desired.

  Volt_f32 of Port Interface Vecu_Volt_f32
    This port prototype is inteded to communicate voltage signals that represent the ecu supplied voltage.  This signal has a lower limit, which is non-zero, to allow users of the signal to use it as a denominator in an expression without requiring a divide by 0 check.


 Mode Declaration Groups:
 ========================
  StaMd_Mode
    EPS System State mode declaration

 *********************************************************************************************************************/

#include "Rte_Ap_BatteryVoltage.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_BatteryVoltage_Cfg.h"
#include "fixmath.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "Os.h"
#include "adc_regs.h"
#include "BatteryVoltage_Cfg.h"


#define   D_VSWITCHEDTHRESH_ULS_F32     0.8f
#define   D_VECUMAX_VOLTS_F32          31.0f


#define BATTERYVOLTAGE_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, AP_BATTERYVOLTAGE_VAR) Vecu_Volts_M_f32;
STATIC VAR(float32, AP_BATTERYVOLTAGE_VAR) Vbatt_Volts_M_f32;
STATIC volatile VAR(float32, AP_BATTERYVOLTAGE_VAR) VswitchCorrLimDiff_Volts_D_f32;
STATIC volatile VAR(float32, AP_BATTERYVOLTAGE_VAR) VecuVbatCorrLimDiff_Volts_D_f32;
#define BATTERYVOLTAGE_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define BATTERYVOLTAGE_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, AP_BATTERYVOLTAGE_VAR) VswitchCorrErrAcc_Cnt_M_u16;
STATIC VAR(uint16, AP_BATTERYVOLTAGE_VAR) VecuVbatCorrErrAcc_Cnt_M_u16;
#define BATTERYVOLTAGE_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */


#define BATTERYVOLTAGE_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_BATTERYVOLTAGE_VAR) VswitchClosed_Cnt_M_lgc;
STATIC VAR(boolean, AP_BATTERYVOLTAGE_VAR) OvervoltageFaultSet_Cnt_M_lgc;
#define BATTERYVOLTAGE_STOP_SEC_VAR_CLEARED_BOOLEAN
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
 *   FLTINJ_SRLCOMVEHLONACCEL_SGNLCOND (155u)
 *   FLTINJ_ANAHWTORQUE (156u)
 * NTCNumber: Enumeration of integer in interval [0...511] with enumerators
 *   NTC_Num_FlashWrapperLgcFlt (1u)
 *   NTC_Num_FlashECCCorr (2u)
 *   NTC_Num_FlashECCMemFlt (3u)
 *   NTC_Num_FlashCRCMemFault (4u)
 *   NTC_Num_NvMBlkDftActA (6u)
 *   NTC_Num_NvMBlkDftActB (7u)
 *   NTC_Num_NvMBlkDftActC (8u)
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
 * NvM_RequestResultType: Enumeration of integer in interval [0...5] with enumerators
 *   NVM_REQ_OK (0u)
 *   NVM_REQ_NOT_OK (1u)
 *   NVM_REQ_PENDING (2u)
 *   NVM_REQ_INTEGRITY_FAILED (3u)
 *   NVM_REQ_BLOCK_SKIPPED (4u)
 *   NVM_REQ_NV_INVALIDATED (5u)
 * NxtrDiagMgrStatus: Enumeration of integer in interval [0...255] with enumerators
 *   NTC_STATUS_PASSED (0u)
 *   NTC_STATUS_FAILED (1u)
 *   NTC_STATUS_PREPASSED (2u)
 *   NTC_STATUS_PREFAILED (3u)
 *
 * Array Types:
 * ============
 * NvM_DestPtr: Array with 65535 element(s) of type UInt8
 *
 * Record Types:
 * =============
 * OvervoltageDataType: Record with elements
 *   MaxBattVoltage_Volts_f32 of type Float
 *   OvervoltageCounter_Cnt_u16 of type UInt16
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
 * Float: D_VECUMIN_VOLTS_F32 = 5
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   OvervoltageDataType *Rte_Pim_OvervoltageData(void)
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_BATTERYVOLTAGE_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: BatteryVoltage_Init1
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
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: BatteryVoltage_Init1
 *********************************************************************************************************************/

	if (OvervoltageFaultSet_Cnt_M_lgc == FALSE)
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_BattTransOverVolt, 0U, NTC_STATUS_PASSED);
	}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: BatteryVoltage_Per1
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
 *   Float Rte_IRead_BatteryVoltage_Per1_BattSwitched_Volt_f32(void)
 *   Float Rte_IRead_BatteryVoltage_Per1_Batt_Volt_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_BatteryVoltage_Per1_SysC_Vecu_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_BatteryVoltage_Per1_SysC_Vecu_Volt_f32(void)
 *   void Rte_IWrite_BatteryVoltage_Per1_Vecu_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_BatteryVoltage_Per1_Vecu_Volt_f32(void)
 *   void Rte_IWrite_BatteryVoltage_Per1_VswitchClosed_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_BatteryVoltage_Per1_VswitchClosed_Cnt_lgc(void)
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

FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: BatteryVoltage_Per1
 *********************************************************************************************************************/
    VAR(boolean, AUTOMATIC) VswitchClosed_Cnt_T_lgc;
    VAR(float32, AUTOMATIC) Vbatt_Volts_T_f32;
    VAR(float32, AUTOMATIC) Vswitched_Volts_T_f32;
    VAR(float32, AUTOMATIC) Vecu_Volts_T_f32;

    Rte_Call_BatteryVoltage_Per1_CP0_CheckpointReached();

    /* Store Module Inputs to Local Copies */
    Vbatt_Volts_T_f32 = Rte_IRead_BatteryVoltage_Per1_Batt_Volt_f32();
    Vswitched_Volts_T_f32 = Rte_IRead_BatteryVoltage_Per1_BattSwitched_Volt_f32();

    if (Vbatt_Volts_T_f32 < k_MaxSwitchedVolt_Volts_f32)
    {
        /* Determine battery switch state and Vecu combined signal */
        if (Abs_f32_m(Vbatt_Volts_T_f32 - Vswitched_Volts_T_f32) < k_MaxBattVoltDiff_Volts_f32)
        {
            Vecu_Volts_T_f32 = Vswitched_Volts_T_f32;
            VswitchClosed_Cnt_T_lgc = TRUE;
        }
        else
        {
            Vecu_Volts_T_f32 = Max_m(Vbatt_Volts_T_f32, Vswitched_Volts_T_f32);
            if (Vswitched_Volts_T_f32 > (D_VSWITCHEDTHRESH_ULS_F32 * Vbatt_Volts_T_f32))
            {
                VswitchClosed_Cnt_T_lgc = TRUE;
            }
            else
            {
                VswitchClosed_Cnt_T_lgc = FALSE;
            }
        }
    }
    else
    {
        Vecu_Volts_T_f32 = Vbatt_Volts_T_f32;
        if (Vswitched_Volts_T_f32 > (D_VSWITCHEDTHRESH_ULS_F32 * k_MaxSwitchedVolt_Volts_f32))
        {
            VswitchClosed_Cnt_T_lgc = TRUE;
        }
        else
        {
            VswitchClosed_Cnt_T_lgc = FALSE;
        }
    }

    VswitchClosed_Cnt_M_lgc = VswitchClosed_Cnt_T_lgc;

    /* Limit Output */
    Vecu_Volts_T_f32 = Limit_m(Vecu_Volts_T_f32, D_VECUMIN_VOLTS_F32, D_VECUMAX_VOLTS_F32);

    /* Fault Injection */
    #if(STD_ON == BC_BATTERYVOLTAGE_FAULTINJECTIONPOINT)
    (void)Rte_Call_FltInjection_SCom_FltInjection(&Vecu_Volts_T_f32,FLTINJ_VECU_BATTERYVOLTAGE);
    #endif
    Vecu_Volts_M_f32 = Vecu_Volts_T_f32;
    Vbatt_Volts_M_f32 = Vbatt_Volts_T_f32;
    /* Store Module Outputs */
    Rte_IWrite_BatteryVoltage_Per1_Vecu_Volt_f32(Vecu_Volts_T_f32);
    Rte_IWrite_BatteryVoltage_Per1_VswitchClosed_Cnt_lgc(VswitchClosed_Cnt_T_lgc);
    Rte_IWrite_BatteryVoltage_Per1_SysC_Vecu_Volt_f32(Vecu_Volts_M_f32);

    Rte_Call_BatteryVoltage_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: BatteryVoltage_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 4ms
 *     and not in Mode(s) <DISABLE, OFF, WARMINIT>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_BatteryVoltage_Per2_BattSwitched_Volt_f32(void)
 *   Float Rte_IRead_BatteryVoltage_Per2_SysCVSwitch_Volt_f32(void)
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
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: BatteryVoltage_Per2
 *********************************************************************************************************************/
    VAR(float32, AUTOMATIC) VbattLmtd_Volts_T_f32;
    VAR(float32, AUTOMATIC) Vswitched_Volts_T_f32;
    VAR(float32, AUTOMATIC) SysCVswitch_Volts_T_f32;
    VAR(float32, AUTOMATIC) VswitchCorrLimDiff_Volts_T_f32;
    VAR(float32, AUTOMATIC) VecuVbatCorrLimDiff_Volts_T_f32;
    VAR(boolean, AUTOMATIC) NTCSysFailCtrlV_T_lgc;

    Rte_Call_BatteryVoltage_Per2_CP0_CheckpointReached();
    VecuVbatCorrLimDiff_Volts_T_f32 = 0.0f;
    NTCSysFailCtrlV_T_lgc = FALSE;


    Vswitched_Volts_T_f32 = Rte_IRead_BatteryVoltage_Per2_BattSwitched_Volt_f32();
    SysCVswitch_Volts_T_f32 = Rte_IRead_BatteryVoltage_Per2_SysCVSwitch_Volt_f32();


    /* Vswicth CrossCheck Diag */
    VswitchCorrLimDiff_Volts_T_f32 = Abs_f32_m(Vswitched_Volts_T_f32 - SysCVswitch_Volts_T_f32);

    if (VswitchCorrLimDiff_Volts_T_f32 > k_VswitchCorrLim_Volts_f32)
    {
        VswitchCorrErrAcc_Cnt_M_u16 = DiagPStep_m(VswitchCorrErrAcc_Cnt_M_u16, k_VswitchCorrLim_Cnt_Str);
        if (DiagFailed_m(VswitchCorrErrAcc_Cnt_M_u16, k_VswitchCorrLim_Cnt_Str) ==  TRUE)
        {
            (void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_NUM_SysFailureForCtrlVolt, 0x01U, NTC_STATUS_FAILED);
        }
    }
    else
    {
        VswitchCorrErrAcc_Cnt_M_u16 = DiagNStep_m(VswitchCorrErrAcc_Cnt_M_u16, k_VswitchCorrLim_Cnt_Str);
        if (VswitchCorrErrAcc_Cnt_M_u16 == 0U)
        {
            NTCSysFailCtrlV_T_lgc = TRUE;
        }
    }


    /* VECU CrossCheck Diag */
    VbattLmtd_Volts_T_f32 = Min_m(Vbatt_Volts_M_f32, D_VECUMAX_VOLTS_F32);
    if (TRUE == VswitchClosed_Cnt_M_lgc)
    {
        VecuVbatCorrLimDiff_Volts_T_f32 = Abs_f32_m(Vecu_Volts_M_f32 - VbattLmtd_Volts_T_f32);
        if (VecuVbatCorrLimDiff_Volts_T_f32 > k_VecuVbatCorrLim_Volts_f32)
        {
            VecuVbatCorrErrAcc_Cnt_M_u16 = DiagPStep_m(VecuVbatCorrErrAcc_Cnt_M_u16, k_VecuCorrLim_Cnt_Str);
            if (DiagFailed_m(VecuVbatCorrErrAcc_Cnt_M_u16, k_VecuCorrLim_Cnt_Str) ==  TRUE)
            {
                (void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_NUM_SysFailureForCtrlVolt, 0x02U, NTC_STATUS_FAILED);
            }
        }
        else
        {
            VecuVbatCorrErrAcc_Cnt_M_u16 = DiagNStep_m(VecuVbatCorrErrAcc_Cnt_M_u16, k_VecuCorrLim_Cnt_Str);
            if ( (VecuVbatCorrErrAcc_Cnt_M_u16 == 0U) &&
                 (TRUE == NTCSysFailCtrlV_T_lgc) )
            {
                (void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_NUM_SysFailureForCtrlVolt, 0x00U, NTC_STATUS_PASSED);
            }
        }
    }

    VswitchCorrLimDiff_Volts_D_f32 = VswitchCorrLimDiff_Volts_T_f32;
    VecuVbatCorrLimDiff_Volts_D_f32 = VecuVbatCorrLimDiff_Volts_T_f32;

    Rte_Call_BatteryVoltage_Per2_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: BatteryVoltage_SCom_ClearTransOvData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ClearTransOvData> of PortPrototype <BatteryVoltage_SCom>
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
 *   Std_ReturnType Rte_Call_OvervoltageData_SetRamBlockStatus(Boolean RamBlockStatus)
 *     Synchronous Service Invocation. Timeout: None
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_OvervoltageData_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_OvervoltageData_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void BatteryVoltage_SCom_ClearTransOvData(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_SCom_ClearTransOvData(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: BatteryVoltage_SCom_ClearTransOvData
 *********************************************************************************************************************/

    Rte_Pim_OvervoltageData()->OvervoltageCounter_Cnt_u16 = 0U;
    Rte_Pim_OvervoltageData()->MaxBattVoltage_Volts_f32 = 0.0f;
    (void)Rte_Call_OvervoltageData_WriteBlock(NULL_PTR);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: BatteryVoltage_SCom_ReadTransOvData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadTransOvData> of PortPrototype <BatteryVoltage_SCom>
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
 *   void BatteryVoltage_SCom_ReadTransOvData(UInt16 *OvervoltageCounter_Cnt_u16, Float *MaxBattVoltage_Volts_f32)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_BATTERYVOLTAGE_APPL_CODE) BatteryVoltage_SCom_ReadTransOvData(P2VAR(UInt16, AUTOMATIC, RTE_AP_BATTERYVOLTAGE_APPL_VAR) OvervoltageCounter_Cnt_u16, P2VAR(Float, AUTOMATIC, RTE_AP_BATTERYVOLTAGE_APPL_VAR) MaxBattVoltage_Volts_f32)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: BatteryVoltage_SCom_ReadTransOvData
 *********************************************************************************************************************/

    *OvervoltageCounter_Cnt_u16 = Rte_Pim_OvervoltageData()->OvervoltageCounter_Cnt_u16;
    *MaxBattVoltage_Volts_f32   = Rte_Pim_OvervoltageData()->MaxBattVoltage_Volts_f32;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_BATTERYVOLTAGE_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

ISR(Isr_OvervoltThresh)
{
	adcREG1->MAGTHRINTFLG = 1U;

	if (OvervoltageFaultSet_Cnt_M_lgc == FALSE)
	{
		(void)BATTERYVOLTAGE_REPORTERRORSTATUS(NTC_Num_BattTransOverVolt, 1U, NTC_STATUS_FAILED);
		OvervoltageFaultSet_Cnt_M_lgc = TRUE;
	}

	if (Rte_Pim_OvervoltageData()->OvervoltageCounter_Cnt_u16 < 0xFFFFU)
	{
		Rte_Pim_OvervoltageData()->OvervoltageCounter_Cnt_u16 += 1U;
	}

	if (Vbatt_Volts_M_f32 > Rte_Pim_OvervoltageData()->MaxBattVoltage_Volts_f32)
	{
		Rte_Pim_OvervoltageData()->MaxBattVoltage_Volts_f32 = Vbatt_Volts_M_f32;
	}

	(void)Rte_Call_OvervoltageData_SetRamBlockStatus(TRUE);
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
