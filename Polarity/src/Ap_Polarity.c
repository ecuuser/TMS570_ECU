/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_Polarity.c
 *     Workspace:  C:/CMSynergy_Projects/Polarity/autosar
 *     SW-C Type:  Ap_Polarity
 *  Generated at:  Tue Feb 19 09:06:31 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_Polarity>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Sat Sep 24 11:57:09 2011
 * %version:          10 %
 * %derived_by:       czgng4 %
 * %date_modified:    Tue Feb 19 10:02:14 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 09/24/11  3        LWW       Added NVM fault check at init
 * 09/26/11	 4		  KJS		Updated diagnostic function calls with 9bit NTC value                        4500
 * 11/14/11  5        JJW       Updated template per module interface and structure changes for CBD implementation
 * 04/21/12  6        KJS       Updated Source code for FDD 004
 * 10/24/12  8        JWJ       Updated code for FDD v006                                                    6160
 * 11/12/12  9        JWJ       Changed Polarity type inputs to Direction type inputs (s8 vs. s08)           6794
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

 *********************************************************************************************************************/

#include "Rte_Ap_Polarity.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_Polarity_Cfg.h"
#include "Os.h"

#define D_HWTRQPOL_CNT_B08					0x01U
#define D_HWPOSPOL_CNT_B08					0x02U
#define D_MTRPOSPOL_CNT_B08					0x04U
#define D_MTRVELPOL_CNT_B08 				0x08U
#define D_ASSTASSEMPOL_CNT_B08				0x10U
#define D_MTRELECMECHPOL_CNT_B08			0x20U

STATIC INLINE FUNC(sint8, AP_POLARITY_CODE) GetPolarity(	VAR(uint8, AUTOMATIC) Polarity_Cnt_T_b08,
															VAR(uint8, AUTOMATIC) PolarityMask_Cnt_T_b08);

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
 * SInt32: Integer in interval [-2147483648...2147483647] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
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
 *   NTC_Num_CurrentMeas1 (84u)
 *   NTC_Num_CurrentMeas2 (85u)
 *   NTC_Num_CurrentMeasCrossChk (86u)
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
 *   NTC_Num_HWASensorRel (110u)
 *   NTC_Num_HWASensorAbs (111u)
 *   NTC_Num_PriMSB_SinCosCorr (112u)
 *   NTC_Num_SecMSB_SinCosCorr (113u)
 *   NTC_Num_PriVsSec_SinCosCorr (114u)
 *   NTC_Num_DigMSBFlt (115u)
 *   NTC_Num_MtrVelFlt (116u)
 *   NTC_Num_HWAtoMtrAngleCorr (117u)
 *   NTC_Num_TurnCntr_PosLoss (128u)
 *   NTC_Num_TurnCntr_MicroProcFlt (129u)
 *   NTC_Num_TurnCntr_SensorPosFlt (130u)
 *   NTC_Num_TurnCntr_SpiComFlt (131u)
 *   NTC_Num_TurnCntr_HighQuiescCur (132u)
 *   NTC_Num_TurnCntr_MainResets (133u)
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
 *   NTC_Num_WhlImbAlgFlt (224u)
 *   NTC_Num_PAHwVelFlt (225u)
 *   NTC_Num_AngleCntrlFltC (226u)
 *   NTC_Num_AngleCntrlFltD (227u)
 *   NTC_Num_AngleCntrlFltFG (228u)
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
 * Polarity_DataType: Record with elements
 *   Polarity_Cnt_b08 of type UInt8
 *   R_Polarity_Cnt_b08 of type UInt8
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
 * SInt32: D_ZERO_CNT_S32 = 0
 * SInt8: D_NEGONE_CNT_S8 = -1
 * SInt8: D_ONE_CNT_S8 = 1
 * SInt8: D_ZERO_CNT_S8 = 0
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   Polarity_DataType *Rte_Pim_Polarity_Cnt_Str(void)
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_POLARITY_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Polarity_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_Polarity_Init1_AssistAssyPolarity_Cnt_s08(SInt8 data)
 *   SInt8 *Rte_IWriteRef_Polarity_Init1_AssistAssyPolarity_Cnt_s08(void)
 *   void Rte_IWrite_Polarity_Init1_HwPosPolarity_Cnt_s08(SInt8 data)
 *   SInt8 *Rte_IWriteRef_Polarity_Init1_HwPosPolarity_Cnt_s08(void)
 *   void Rte_IWrite_Polarity_Init1_HwTrqPolarity_Cnt_s08(SInt8 data)
 *   SInt8 *Rte_IWriteRef_Polarity_Init1_HwTrqPolarity_Cnt_s08(void)
 *   void Rte_IWrite_Polarity_Init1_MtrElecMechPolarity_Cnt_s08(SInt8 data)
 *   SInt8 *Rte_IWriteRef_Polarity_Init1_MtrElecMechPolarity_Cnt_s08(void)
 *   void Rte_IWrite_Polarity_Init1_MtrPosPolarity_Cnt_s08(SInt8 data)
 *   SInt8 *Rte_IWriteRef_Polarity_Init1_MtrPosPolarity_Cnt_s08(void)
 *   void Rte_IWrite_Polarity_Init1_MtrVelPolarity_Cnt_s08(SInt8 data)
 *   SInt8 *Rte_IWriteRef_Polarity_Init1_MtrVelPolarity_Cnt_s08(void)
 *   void Rte_IWrite_Polarity_Init1_SysC_MtrElecMechPolarity_Cnt_s32(SInt32 data)
 *   SInt32 *Rte_IWriteRef_Polarity_Init1_SysC_MtrElecMechPolarity_Cnt_s32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_POLARITY_APPL_CODE) Polarity_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Polarity_Init1
 *********************************************************************************************************************/
	VAR(uint8, AUTOMATIC) Polarity_Cnt_T_b08;
	
	Polarity_Cnt_T_b08 = Rte_Pim_Polarity_Cnt_Str()->Polarity_Cnt_b08;

	Rte_IWrite_Polarity_Init1_HwTrqPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_HWTRQPOL_CNT_B08));
	Rte_IWrite_Polarity_Init1_HwPosPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_HWPOSPOL_CNT_B08));
	Rte_IWrite_Polarity_Init1_MtrPosPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_MTRPOSPOL_CNT_B08));
	Rte_IWrite_Polarity_Init1_MtrVelPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_MTRVELPOL_CNT_B08));
	Rte_IWrite_Polarity_Init1_AssistAssyPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_ASSTASSEMPOL_CNT_B08));
	Rte_IWrite_Polarity_Init1_MtrElecMechPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_MTRELECMECHPOL_CNT_B08));
	Rte_IWrite_Polarity_Init1_SysC_MtrElecMechPolarity_Cnt_s32((sint32)GetPolarity(Polarity_Cnt_T_b08, D_MTRELECMECHPOL_CNT_B08));
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Polarity_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   SInt8 Rte_IRead_Polarity_Per1_DiagAssistAssyPolarity_Cnt_s08(void)
 *   SInt8 Rte_IRead_Polarity_Per1_DiagHwPosPolarity_Cnt_s08(void)
 *   SInt8 Rte_IRead_Polarity_Per1_DiagHwTrqPolarity_Cnt_s08(void)
 *   SInt8 Rte_IRead_Polarity_Per1_DiagMtrElecMechPolarity_Cnt_s08(void)
 *   SInt8 Rte_IRead_Polarity_Per1_DiagMtrPosPolarity_Cnt_s08(void)
 *   SInt8 Rte_IRead_Polarity_Per1_DiagMtrVelPolarity_Cnt_s08(void)
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

FUNC(void, RTE_AP_POLARITY_APPL_CODE) Polarity_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Polarity_Per1
 *********************************************************************************************************************/
	VAR(sint8, AUTOMATIC) AssistAssyPolarity_Cnt_T_s08;
	VAR(sint8, AUTOMATIC) HwPosPolarity_Cnt_T_s08;
	VAR(sint8, AUTOMATIC) HwTrqPolarity_Cnt_T_s08;
	VAR(sint8, AUTOMATIC) MtrElecMechPolarity_Cnt_T_s08;
	VAR(sint8, AUTOMATIC) MtrPosPolarity_Cnt_T_s08;
	VAR(sint8, AUTOMATIC) MtrVelPolarity_Cnt_T_s08;
	VAR(uint8, AUTOMATIC) RedPolarity_Cnt_T_b08;
	VAR(sint8, AUTOMATIC) RedHwTrqPolarity_Cnt_T_s08;
	VAR(sint8, AUTOMATIC) RedHwPosPolarity_Cnt_T_s08;
	VAR(sint8, AUTOMATIC) RedMtrPosPolarity_Cnt_T_s08;
	VAR(sint8, AUTOMATIC) RedMtrVelPolarity_Cnt_T_s08;
	VAR(sint8, AUTOMATIC) RedAssistAssyPolarity_Cnt_T_s08;
	VAR(sint8, AUTOMATIC) RedMtrElecMechPolarity_Cnt_T_s08;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_Polarity_Per1_CP0_CheckpointReached();

	HwTrqPolarity_Cnt_T_s08 = Rte_IRead_Polarity_Per1_DiagHwTrqPolarity_Cnt_s08();
	HwPosPolarity_Cnt_T_s08 = Rte_IRead_Polarity_Per1_DiagHwPosPolarity_Cnt_s08();
	MtrPosPolarity_Cnt_T_s08 = Rte_IRead_Polarity_Per1_DiagMtrPosPolarity_Cnt_s08();
	MtrVelPolarity_Cnt_T_s08 = Rte_IRead_Polarity_Per1_DiagMtrVelPolarity_Cnt_s08();
	AssistAssyPolarity_Cnt_T_s08 = Rte_IRead_Polarity_Per1_DiagAssistAssyPolarity_Cnt_s08();
	MtrElecMechPolarity_Cnt_T_s08 = Rte_IRead_Polarity_Per1_DiagMtrElecMechPolarity_Cnt_s08();
	
	RedPolarity_Cnt_T_b08 = ~Rte_Pim_Polarity_Cnt_Str()->R_Polarity_Cnt_b08;

	RedHwTrqPolarity_Cnt_T_s08 = GetPolarity(RedPolarity_Cnt_T_b08, D_HWTRQPOL_CNT_B08);
	RedHwPosPolarity_Cnt_T_s08 = GetPolarity(RedPolarity_Cnt_T_b08, D_HWPOSPOL_CNT_B08);
	RedMtrPosPolarity_Cnt_T_s08 = GetPolarity(RedPolarity_Cnt_T_b08, D_MTRPOSPOL_CNT_B08);
	RedMtrVelPolarity_Cnt_T_s08 = GetPolarity(RedPolarity_Cnt_T_b08, D_MTRVELPOL_CNT_B08);
	RedAssistAssyPolarity_Cnt_T_s08 = GetPolarity(RedPolarity_Cnt_T_b08, D_ASSTASSEMPOL_CNT_B08);
	RedMtrElecMechPolarity_Cnt_T_s08 = GetPolarity(RedPolarity_Cnt_T_b08, D_MTRELECMECHPOL_CNT_B08);

	if ((RedHwTrqPolarity_Cnt_T_s08 != HwTrqPolarity_Cnt_T_s08) ||
		(RedHwPosPolarity_Cnt_T_s08 != HwPosPolarity_Cnt_T_s08) ||
		(RedMtrPosPolarity_Cnt_T_s08 != MtrPosPolarity_Cnt_T_s08) ||
		(RedMtrVelPolarity_Cnt_T_s08 != MtrVelPolarity_Cnt_T_s08) ||
		(RedAssistAssyPolarity_Cnt_T_s08 != AssistAssyPolarity_Cnt_T_s08) ||
		(RedMtrElecMechPolarity_Cnt_T_s08 != MtrElecMechPolarity_Cnt_T_s08))
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EEPROMDiagPolarityStr, 0x01U, NTC_STATUS_FAILED);
	}
	else
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EEPROMDiagPolarityStr, 0x00U, NTC_STATUS_PASSED);
	}

	/* Configurable End of Runnable Checkpoint */
    Rte_Call_Polarity_Per1_CP1_CheckpointReached();

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Polarity_SCom_ReadPolarity
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadPolarity> of PortPrototype <Polarity_SCom>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void Polarity_SCom_ReadPolarity(UInt8 *Polarity_Ptr_T_b08)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_POLARITY_APPL_CODE) Polarity_SCom_ReadPolarity(P2VAR(UInt8, AUTOMATIC, RTE_AP_POLARITY_APPL_VAR) Polarity_Ptr_T_b08)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Polarity_SCom_ReadPolarity
 *********************************************************************************************************************/

	*Polarity_Ptr_T_b08 = Rte_Pim_Polarity_Cnt_Str()->Polarity_Cnt_b08;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Polarity_SCom_SetPolarity
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <SetPolarity> of PortPrototype <Polarity_SCom>
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_AssistAssyPolarity_Cnt_s08(SInt8 data)
 *   Std_ReturnType Rte_Write_HwPosPolarity_Cnt_s08(SInt8 data)
 *   Std_ReturnType Rte_Write_HwTrqPolarity_Cnt_s08(SInt8 data)
 *   Std_ReturnType Rte_Write_MtrElecMechPolarity_Cnt_s08(SInt8 data)
 *   Std_ReturnType Rte_Write_MtrPosPolarity_Cnt_s08(SInt8 data)
 *   Std_ReturnType Rte_Write_MtrVelPolarity_Cnt_s08(SInt8 data)
 *   Std_ReturnType Rte_Write_SysC_MtrElecMechPolarity_Cnt_s32(SInt32 data)
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_Polarity_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_Polarity_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void Polarity_SCom_SetPolarity(UInt8 Polarity_Cnt_T_b08)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_POLARITY_APPL_CODE) Polarity_SCom_SetPolarity(UInt8 Polarity_Cnt_T_b08)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Polarity_SCom_SetPolarity
 *********************************************************************************************************************/

	SuspendAllInterrupts();
	Rte_Pim_Polarity_Cnt_Str()->Polarity_Cnt_b08 = Polarity_Cnt_T_b08;
	Rte_Pim_Polarity_Cnt_Str()->R_Polarity_Cnt_b08 = ~Polarity_Cnt_T_b08;
	
	(void)Rte_Write_HwTrqPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_HWTRQPOL_CNT_B08));
	(void)Rte_Write_HwPosPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_HWPOSPOL_CNT_B08));
	(void)Rte_Write_MtrPosPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_MTRPOSPOL_CNT_B08));
	(void)Rte_Write_MtrVelPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_MTRVELPOL_CNT_B08));
	(void)Rte_Write_AssistAssyPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_ASSTASSEMPOL_CNT_B08));
	(void)Rte_Write_MtrElecMechPolarity_Cnt_s08(GetPolarity(Polarity_Cnt_T_b08, D_MTRELECMECHPOL_CNT_B08));
	(void)Rte_Write_SysC_MtrElecMechPolarity_Cnt_s32((sint32)GetPolarity(Polarity_Cnt_T_b08, D_MTRELECMECHPOL_CNT_B08));
	ResumeAllInterrupts();

	(void)Rte_Call_Polarity_WriteBlock(NULL_PTR);
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_POLARITY_APPL_CODE
#include "MemMap.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

STATIC INLINE FUNC(sint8, AP_POLARITY_CODE) GetPolarity(	VAR(uint8, AUTOMATIC) Polarity_Cnt_T_b08,
															VAR(uint8, AUTOMATIC) PolarityMask_Cnt_T_b08)
{
	VAR(sint8, AUTOMATIC) Polarity_Cnt_T_s08;

	if ( (Polarity_Cnt_T_b08 & PolarityMask_Cnt_T_b08) == PolarityMask_Cnt_T_b08 )
	{
		Polarity_Cnt_T_s08 = D_ONE_CNT_S8;
	}
	else
	{
		Polarity_Cnt_T_s08 = D_NEGONE_CNT_S8;
	}

	return(Polarity_Cnt_T_s08);
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
