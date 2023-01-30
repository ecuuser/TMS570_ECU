/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Cd_Nhet1.c
 *     Workspace:  C:/Rijvi_Synergy_EA3/Core_Component/Working/ePWM/autosar
 *     SW-C Type:  Cd_Nhet1
 *  Generated at:  Wed Nov 25 12:36:23 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Cd_Nhet1>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/*****************************************************************************
* Copyright 2015 Nexteer 
* Nexteer Confidential
*
* Module File Name: Cd_Nhet1.c
* Module Description: Implements the R4 application driver portion of the NHET1:Digital SENT HandWheel Torque
*						and NHET1:SPI and ePWM SYNCI Trigger subfunctions in ES-34B
* Project           : CBD   
* Author            : Selva Sengottaiyan
*****************************************************************************
* Version Control:
* Date Created:      Wed Jun 19 13:00:00 2013
* %version:          EA3#5 %
* %derived_by:       jzk9cc %
*---------------------------------------------------------------------------------------------------------------------
* Date       Rev      Author    Change Description                                                               SCR #
* --------   -------  --------  ------------------------------------------------------------------------------  -------
* 06/19/13    1       Selva        Initial Version (FDD 34B v003)
* 08/01/13    2       Selva        Corrected NumPulses_Cnt_T_u08 check from 8 to 7                              CR9346
* 04/07/14    3        Selva    Implemented  FDD34B v 005														CR11062
* 01/25/15    4       KMC       Changed to write adjusted PWM period per ES-34B v008; this is part of          	CR12869
*                               the fix for anomaly 7586. Corrected placement and comment block for 
*								 Nhet1_Per3 function as a non-Rte function.  QAC cleanup.
* 25/11/15    5		  Rijvi		Updated per ES-34B v009. (Removed ePWM_AdjPWMPeriod_Cnt_G_u16)                  EA3#4788
******************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Cd_Nhet1.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "GlobalMacro.h"
#include "CalConstants.h"


/* MISRA-C:2004 Rule 8.7: This deviation is required to keep the memory map intact.  Rule suppressed by line at each occurrence. */

/* MISRA-C:2004 Rule 17.4: This deviation is required because of AUTOSAR macro for passing the array.  Rule suppressed by line at each occurrence. */

/* MISRA-C:2004 Rule 19.1: This deviation is required for AUTOSAR memory map requirements.  Rule suppressed by line at each occurrence. */

#define  HTUDATATRQ
#include "Nhet.h"
#include "ePWM_Cfg.h"

#define D_NUMRAWDATA_CNT_U08		8u
#define D_STATUSFAULT_CNT_U08		0x04u
#define D_PROTOCOLFAULT_CNT_U08		0x08u
#define D_CRCFAULT_CNT_U08			0x10u
#define D_SYNCTICKS_ULS_F32			56.0f
#define D_HWTRQSCALE_HWNMPCNT_F32	(20.0f/4095.0f)
#define D_HWTRQOFFSET_HWNM_F32		10.0f


enum
{
	PULSE_MSGCOUNTST = 0u,
	PULSE_SYNC,
	PULSE_STATUS,
	PULSE_D0,
	PULSE_D1,
	PULSE_D2,
	PULSE_CRC,
	PULSE_MSGCOUNTEND
};


#define NHET1_START_SEC_CONST_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC CONST(uint8, AUTOMATIC) T_SENTCRC_CNT_U08[16] = {0u,13u,7u,10u,14u,3u,9u,4u,1u,12u,6u,11u,15u,2u,8u,5u}; /* PRQA S 3218 */
#define NHET1_STOP_SEC_CONST_8
#include "MemMap.h" /* PRQA S 5087 */


#define NHET1_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint8,  AUTOMATIC) Nhet1_NTCParamT1_Cnt_M_u08; /* PRQA S 3218 */
STATIC VAR(uint8,  AUTOMATIC) Nhet1_NTCParamT2_Cnt_M_u08; /* PRQA S 3218 */
STATIC volatile VAR(uint8,   AUTOMATIC) Nhet1_T1CalcCRC_Cnt_D_u08; /* PRQA S 3218 */
STATIC volatile VAR(uint8,   AUTOMATIC) Nhet1_T2CalcCRC_Cnt_D_u08; /* PRQA S 3218 */
#define NHET1_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */


#define NHET1_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16,  AUTOMATIC) Nhet1_FltAccT1_Cnt_M_u16; /* PRQA S 3218 */
STATIC VAR(uint16,  AUTOMATIC) Nhet1_FltAccT2_Cnt_M_u16; /* PRQA S 3218 */
#define NHET1_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */


#define NHET1_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, AUTOMATIC) 	Nhet1_HwTrqT1_HwNm_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, AUTOMATIC)  Nhet1_HwTrqT2_HwNm_M_f32; /* PRQA S 3218 */
STATIC VAR(uint32,   AUTOMATIC) Nhet1_PrevPulseCountT1_Cnt_M_u32; /* PRQA S 3218 */
STATIC VAR(uint32,   AUTOMATIC) Nhet1_PrevPulseCountT2_Cnt_M_u32; /* PRQA S 3218 */
STATIC VAR(uint32,   AUTOMATIC) Nhet1_TotalMsg_Cnt_M_u32 ; /* PRQA S 3218 */
STATIC VAR(uint32,   AUTOMATIC) Nhet1_T1MissMsg_Cnt_M_u32 ; /* PRQA S 3218 */
STATIC VAR(uint32,   AUTOMATIC) Nhet1_T2MissMsg_Cnt_M_u32 ; /* PRQA S 3218 */
STATIC VAR(uint32,   AUTOMATIC) Nhet1_TotalUpdates_Cnt_M_u32; /* PRQA S 3218 */

#define NHET1_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */




STATIC FUNC(uint8, Nhet1_CODE) Nhet1_ProcessSENTData(P2CONST(uint32,  AUTOMATIC, AUTOMATIC) RawData_Cnt_T_u32,
													P2VAR(uint32,   AUTOMATIC, AUTOMATIC) PrevPulseCount_Cnt_T_u32,
													P2VAR(float32, AUTOMATIC, AUTOMATIC) HwTrq_HwNm_T_f32,
													P2VAR(uint8, AUTOMATIC, AUTOMATIC) TxCalcCRC_Cnt_T_u08);

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
 *   NTC_Num_PeripheralStartupFlt (55u)
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
 *   NTC_Num_BattVltgMeasdCorrlnFlt (73u)
 *   NTC_Num_IvtrPwrDiscnctFailr (74u)
 *   NTC_Num_PowerRelayInit2Flt (75u)
 *   NTC_Num_GateDrvFltInProcess (76u)
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
 *   NTC_Num_Inv2GateDrvFltInProcess (92u)
 *   NTC_Num_Inv2GateDrvFlt (93u)
 *   NTC_Num_Inv2OnStateSingleFET (94u)
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
 *   NTC_Num_LoaRpdShutdn (170u)
 *   NTC_Num_LoaCtrldShutdn (171u)
 *   NTC_Num_LoaMgr_HwTqIdptSigTooLow (172u)
 *   NTC_Num_LoaMgr_MotAgIdptSigTooLow (173u)
 *   NTC_Num_LoaMgr_MotCurrIdptSigTooLow (174u)
 *   NTC_Num_LoaMgr_IvtrIdptSigTooLow (175u)
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
 *   NTC_Num_InvalidMsg_ParkAssistParallel (464u)
 *   NTC_Num_FlexrayCommunicationError (465u)
 *   NTC_Num_InvalidMsg_AI (466u)
 *   NTC_Num_MissingMsg_AI (467u)
 *   NTC_Num_InvalidMsg_AJ (472u)
 *   NTC_Num_MissingMsg_AJ (473u)
 *   NTC_Num_InvalidMsg_AK (480u)
 *   NTC_Num_MissingMsg_AK (481u)
 *   NTC_Num_MissingMsg_AL (489u)
 *   NTC_Num_SysConsistencyVerf (496u)
 *   NTC_Num_ConfigMisMatch (497u)
 *   NTC_Num_CalNotPrgmd (498u)
 *   NTC_Num_TunSetNotPrgmd (499u)
 *   NTC_Num_EEPROMtoFeeCpyError (500u)
 *   NTC_Num_EOLVehTunNtPerf (501u)
 *   NTC_Num_MtrSensorNotTrimmed (502u)
 *   NTC_Num_HWASensorNotTrimmed (504u)
 *   NTC_Num_HWASensorTrimNoAttempt (505u)
 *   NTC_Num_TrqSensorScaleNotSet (506u)
 *   NTC_Num_TrqSensorNotTrimmed (507u)
 *   NTC_Num_AnaHWDiffTqOfstNotTrmd (508u)
 *   NTC_Num_DigTrqSensorScaleNotSet (509u)
 *   NTC_Num_DigTrqSensorNotTrimmed (510u)
 *   NTC_Num_SENTHWDiffTqOfstNotTrmd (511u)
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
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_CD_NHET1_APPL_CODE
#include "MemMap.h"  /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Nhet1_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CD_NHET1_APPL_CODE) Nhet1_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Nhet1_Per1
 *********************************************************************************************************************/
	/* 	The trigger for HET sync word is  written directly in memory  */
	HET_SYNCRST_0.memory.data_word = 0x80u;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Nhet1_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_Nhet1_Per2_DigHwTrqT1_HwNm_f32(Float data)
 *   Float *Rte_IWriteRef_Nhet1_Per2_DigHwTrqT1_HwNm_f32(void)
 *   void Rte_IWrite_Nhet1_Per2_DigHwTrqT2_HwNm_f32(Float data)
 *   Float *Rte_IWriteRef_Nhet1_Per2_DigHwTrqT2_HwNm_f32(void)
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

FUNC(void, RTE_CD_NHET1_APPL_CODE) Nhet1_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Nhet1_Per2
 *********************************************************************************************************************/
	
	
	VAR(uint32, AUTOMATIC) RawDataT1_Cnt_T_u32[D_NUMRAWDATA_CNT_U08];
	VAR(uint32, AUTOMATIC) RawDataT2_Cnt_T_u32[D_NUMRAWDATA_CNT_U08];
	VAR(uint8, AUTOMATIC) NTCParamT1_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) NTCParamT2_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) T1CalcCRC_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) T2CalcCRC_Cnt_T_u08;
	
	RawDataT1_Cnt_T_u32[PULSE_MSGCOUNTST]   = Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq1_Cnt_u32[0];
	RawDataT1_Cnt_T_u32[PULSE_SYNC]     	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq1_Cnt_u32[1];
	RawDataT1_Cnt_T_u32[PULSE_STATUS]   	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq1_Cnt_u32[2];
	RawDataT1_Cnt_T_u32[PULSE_D0]       	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq1_Cnt_u32[3];
	RawDataT1_Cnt_T_u32[PULSE_D1]       	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq1_Cnt_u32[4];
	RawDataT1_Cnt_T_u32[PULSE_D2]       	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq1_Cnt_u32[5];
	RawDataT1_Cnt_T_u32[PULSE_CRC]      	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq1_Cnt_u32[6];
	RawDataT1_Cnt_T_u32[PULSE_MSGCOUNTEND] 	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq1_Cnt_u32[7];




	RawDataT2_Cnt_T_u32[PULSE_MSGCOUNTST]   = Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq2_Cnt_u32[0];
	RawDataT2_Cnt_T_u32[PULSE_SYNC]     	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq2_Cnt_u32[1];
	RawDataT2_Cnt_T_u32[PULSE_STATUS]   	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq2_Cnt_u32[2];
	RawDataT2_Cnt_T_u32[PULSE_D0]       	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq2_Cnt_u32[3];
	RawDataT2_Cnt_T_u32[PULSE_D1]       	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq2_Cnt_u32[4];
	RawDataT2_Cnt_T_u32[PULSE_D2]       	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq2_Cnt_u32[5];
	RawDataT2_Cnt_T_u32[PULSE_CRC]      	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq2_Cnt_u32[6];
	RawDataT2_Cnt_T_u32[PULSE_MSGCOUNTEND] 	= Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq2_Cnt_u32[7];

	
	/* Process SENT data */
	NTCParamT1_Cnt_T_u08 = Nhet1_ProcessSENTData(RawDataT1_Cnt_T_u32, &Nhet1_PrevPulseCountT1_Cnt_M_u32, &Nhet1_HwTrqT1_HwNm_M_f32, &T1CalcCRC_Cnt_T_u08);
	NTCParamT2_Cnt_T_u08 = Nhet1_ProcessSENTData(RawDataT2_Cnt_T_u32, &Nhet1_PrevPulseCountT2_Cnt_M_u32, &Nhet1_HwTrqT2_HwNm_M_f32, &T2CalcCRC_Cnt_T_u08);
	/**** Calc Display variable****/
	Nhet1_T1CalcCRC_Cnt_D_u08 = T1CalcCRC_Cnt_T_u08;
	Nhet1_T2CalcCRC_Cnt_D_u08 = T2CalcCRC_Cnt_T_u08;
	
	
	Nhet1_NTCParamT1_Cnt_M_u08 |= NTCParamT1_Cnt_T_u08;
	Nhet1_NTCParamT2_Cnt_M_u08 |= NTCParamT2_Cnt_T_u08;
	
	

	/* Total Torque Message Counter */
	Nhet1_TotalMsg_Cnt_M_u32 ++ ;
	
	if( NTCParamT1_Cnt_T_u08 > 0u )
	{
		Nhet1_T1MissMsg_Cnt_M_u32 ++ ;

		Nhet1_FltAccT1_Cnt_M_u16 = DiagPStep_m(Nhet1_FltAccT1_Cnt_M_u16, k_HwTrqDiag_Cnt_str);

		if( DiagFailed_m(Nhet1_FltAccT1_Cnt_M_u16, k_HwTrqDiag_Cnt_str) == TRUE )
		{
			(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_T1OutofRange, Nhet1_NTCParamT1_Cnt_M_u08, NTC_STATUS_FAILED);
		}
	}
	else
	{
		Nhet1_FltAccT1_Cnt_M_u16 = DiagNStep_m(Nhet1_FltAccT1_Cnt_M_u16, k_HwTrqDiag_Cnt_str);
		
		if( Nhet1_FltAccT1_Cnt_M_u16 == 0u )
		{
			Nhet1_NTCParamT1_Cnt_M_u08 = 0u;
			(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_T1OutofRange, 0u, NTC_STATUS_PASSED);
		}
	}
	
	if( NTCParamT2_Cnt_T_u08 > 0u )
	{
		Nhet1_T2MissMsg_Cnt_M_u32 ++ ;

		Nhet1_FltAccT2_Cnt_M_u16 = DiagPStep_m(Nhet1_FltAccT2_Cnt_M_u16, k_HwTrqDiag_Cnt_str);

		if( DiagFailed_m(Nhet1_FltAccT2_Cnt_M_u16, k_HwTrqDiag_Cnt_str) == TRUE )
		{
			(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_T2OutofRange, Nhet1_NTCParamT2_Cnt_M_u08, NTC_STATUS_FAILED);
		}
	}
	else
	{
		Nhet1_FltAccT2_Cnt_M_u16 = DiagNStep_m(Nhet1_FltAccT2_Cnt_M_u16, k_HwTrqDiag_Cnt_str);
		
		if( Nhet1_FltAccT2_Cnt_M_u16 == 0u )
		{
			Nhet1_NTCParamT2_Cnt_M_u08 = 0u;
			(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_T2OutofRange, 0u, NTC_STATUS_PASSED);
		}
	}
	
	(void) Rte_IWrite_Nhet1_Per2_DigHwTrqT1_HwNm_f32(Nhet1_HwTrqT1_HwNm_M_f32);
	(void) Rte_IWrite_Nhet1_Per2_DigHwTrqT2_HwNm_f32(Nhet1_HwTrqT2_HwNm_M_f32);
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_CD_NHET1_APPL_CODE
#include "MemMap.h"  /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/*****************************************************************************
  * Name:        Nhet1_ProcessSENTData
  * Description: Created for common processing between T1 and T2
  * Inputs:      *RawData_Cnt_T_u32			- raw input data array
  *              *PrevPulseCount_Cnt_T_u32	- state variable for pulse count
  *              *HwTrq_HwNm_T_f32			- calculated handwheel torque
  * Outputs:     NTCParam_Cnt_T_u08			- if non-zero, HwTrq not updated
  *
*****************************************************************************/
STATIC FUNC(uint8, Nhet1_CODE) Nhet1_ProcessSENTData(P2CONST(uint32,  AUTOMATIC, AUTOMATIC) RawData_Cnt_T_u32,
													P2VAR(uint32,   AUTOMATIC, AUTOMATIC) PrevPulseCount_Cnt_T_u32,
													P2VAR(float32, AUTOMATIC, AUTOMATIC) HwTrq_HwNm_T_f32,
													P2VAR(uint8, AUTOMATIC, AUTOMATIC) TxCalcCRC_Cnt_T_u08)
{
	
	VAR(uint8,   AUTOMATIC) NTCParam_Cnt_T_u08;
	VAR(uint32,   AUTOMATIC) PulseCount_Cnt_T_u32;
	VAR(float32, AUTOMATIC) SyncFactor_Uls_T_f32;
	VAR(float32, AUTOMATIC) RawDataTicks_Cnt_T_f32;
	VAR(uint32,  AUTOMATIC) RawDataTicks_Cnt_T_u32[D_NUMRAWDATA_CNT_U08];
	VAR(uint8,   AUTOMATIC) Data_Cnt_T_u08[D_NUMRAWDATA_CNT_U08];
	VAR(uint16,  AUTOMATIC) i;
	VAR(uint8,   AUTOMATIC) CRC_Cnt_T_u08;
	VAR(uint16,  AUTOMATIC) HwTrq_Cnt_T_u16;
	
	
	NTCParam_Cnt_T_u08 = 0u;
	CRC_Cnt_T_u08 =0u;
	
	PulseCount_Cnt_T_u32 = RawData_Cnt_T_u32[PULSE_MSGCOUNTEND]; /* PRQA S 492 */
	
	if (RawData_Cnt_T_u32[PULSE_MSGCOUNTST] != PulseCount_Cnt_T_u32) /* PRQA S 492 */
	{
		NTCParam_Cnt_T_u08 = D_PROTOCOLFAULT_CNT_U08;
	}
	else if (PulseCount_Cnt_T_u32 <= (*PrevPulseCount_Cnt_T_u32))
	{
		NTCParam_Cnt_T_u08 = D_PROTOCOLFAULT_CNT_U08;
	}

	else
	{
		SyncFactor_Uls_T_f32 = D_SYNCTICKS_ULS_F32 / ((float32)RawData_Cnt_T_u32[PULSE_SYNC]); /* PRQA S 492 */

		for( i = (uint16)PULSE_STATUS; i <= (uint16)PULSE_CRC; i++ )
		{    /* To make sure "RawDataTicks" is rounded off, the type of RawData is converted to float and used in the RawDataTicks calculation.
           		 RawDataTicks is converted again to the nearest fixed point.
		 	 	 RawDataTicks should be a ratio of RawData to ticks per PULSE_SYNC of RawData */
			RawDataTicks_Cnt_T_f32 = (((float32)RawData_Cnt_T_u32[i]) * SyncFactor_Uls_T_f32) + 0.5f; /* PRQA S 492 */
			RawDataTicks_Cnt_T_u32[i] = (uint32)RawDataTicks_Cnt_T_f32; 

			if( (RawDataTicks_Cnt_T_u32[i] < 12u) ||
					(RawDataTicks_Cnt_T_u32[i] > 27u) )
			{
				NTCParam_Cnt_T_u08 = D_PROTOCOLFAULT_CNT_U08;
				Data_Cnt_T_u08[i] = 0u;
			}
			else
			{
				Data_Cnt_T_u08[i] = (uint8)(RawDataTicks_Cnt_T_u32[i] - 12u);
			}
		}
		
		CRC_Cnt_T_u08 = T_SENTCRC_CNT_U08[ T_SENTCRC_CNT_U08[ T_SENTCRC_CNT_U08[ T_SENTCRC_CNT_U08[5u] ^
																						 Data_Cnt_T_u08[PULSE_D0] ] ^
																	  Data_Cnt_T_u08[PULSE_D1] ] ^
												   Data_Cnt_T_u08[PULSE_D2] ];
												   
		if( NTCParam_Cnt_T_u08 == 0u )
		{
			if( Data_Cnt_T_u08[PULSE_STATUS] > 0u )
			{
				NTCParam_Cnt_T_u08 = D_STATUSFAULT_CNT_U08;
			}
			else
			{
								
				if( CRC_Cnt_T_u08 != Data_Cnt_T_u08[PULSE_CRC] )
				{
					NTCParam_Cnt_T_u08 = D_CRCFAULT_CNT_U08;
				}
				
			}
		}

	}
	*TxCalcCRC_Cnt_T_u08 = CRC_Cnt_T_u08;

	*PrevPulseCount_Cnt_T_u32 = PulseCount_Cnt_T_u32;

	if( NTCParam_Cnt_T_u08 == 0u )
	{
		HwTrq_Cnt_T_u16 =  ((uint16)Data_Cnt_T_u08[PULSE_D0] << 8u) |
						   ((uint16)Data_Cnt_T_u08[PULSE_D1] << 4u) |
						   ((uint16)Data_Cnt_T_u08[PULSE_D2] );
		
		*HwTrq_HwNm_T_f32 = (((float32)HwTrq_Cnt_T_u16) * D_HWTRQSCALE_HWNMPCNT_F32) - D_HWTRQOFFSET_HWNM_F32;
	}
	
	return NTCParam_Cnt_T_u08;
	
}


/******************************************************************************
  * Name:        Nhet1_Per3
  * Description: Updates PWM Period for Nhet use and sets BUF_RDY flag
  * Inputs:      None
  *                   
  * Outputs:     Nhet1 PWM Period written by Nhet1_Write_PWMPeriod_Cnt_u16 macro 
  *              HET_BUF_RDY_FLAG_0.memory.data_word
  *				 Nhet1_TotalUpdates_Cnt_M_u32
  * Usage Notes:  Motor Control task periodic
  ****************************************************************************/
FUNC(void, Nhet1_CODE) Nhet1_Per3(void)
{
	VAR(uint16, AUTOMATIC)  PWMPeriod_Cnt_T_u16;
	
	/***Increment the counter***/
	Nhet1_TotalUpdates_Cnt_M_u32++;
	
	/* The order of PWMPeriod write to HET memory (or buffer for DMA transfer to Nhet)
    	and buffer ready data word write must be maintained; implemented by use of volatiles */ 
        
	ePWM_Read_PWMPeriod_u16(&PWMPeriod_Cnt_T_u16);
	
	Nhet1_Write_PWMPeriod_Cnt_u16(PWMPeriod_Cnt_T_u16);
	/* 	The trigger for HET buffer ready flag memory word is  written directly in memory  */
	HET_BUF_RDY_FLAG_0.memory.data_word = 0x80u;
	
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
