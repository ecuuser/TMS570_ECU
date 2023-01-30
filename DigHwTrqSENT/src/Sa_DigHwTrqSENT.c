/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Sa_DigHwTrqSENT.c
 *     Workspace:  C:/_00_Working_Files/_19_EA3.0_Work/03_Component_Development/DigHwTrqSENT/autosar
 *     SW-C Type:  Sa_DigHwTrqSENT
 *  Generated at:  Thu Jul 31 15:06:28 2014
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Sa_DigHwTrqSENT>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/*****************************************************************************
* Copyright 2014 Nexteer 
* Nexteer Confidential
*
* Module File Name: DigHwTrqSENT.c
* Module Description: Implementation of ES04C
* Project           : CBD   
* Author            : Kathleen Creager
*****************************************************************************
* Version Control:
* Date Created:      Thu Jun 20 15:26:25 2013
* %version:          8 %
* %derived_by:       gzkys7 %
*---------------------------------------------------------------------------------------------------------------------
* Date      Rev      Author         Change Description                                                          SCR #
* -------   -------  --------  ---------------------------------------------------------------------------------------
* 07/01/13  1        KMC       Initial Version																     8492
* 07/31/13	 2		  KMC		Corrected reads from SCom functions to be direct rather than buffered            8835
* 01/14/13  3		  LK		Added SVC input for read trim data                                              10872
* 03/20/13	 4	      SB        Updated per Design Review                                                       11619
* 03/27/13  5        SB        Updated per Design Review														11619
* 06/09/14	 6		  SB		Implemented ES04C Rev 006														12078
* 07/31/14  7        VS        Implemented ES04C Rev 007 and Added the Function DigHwTrq_Scomm_WriteData		12179                                                    
* 08/04/14	8		 SB		   Correction in Fault OInjection SCom name FaultInjection_SCom_FltInjection		12242
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

#include "Rte_Sa_DigHwTrqSENT.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "CalConstants.h"
#include "fixmath.h"
#include "GlobalMacro.h"
#include "filters.h"
#include "interpolation.h"
#include "Sa_DigHwTrqSENT_Cfg.h"
#include "Ap_DiagMgr.h"

/* MISRA-C:2004 Rule 8.7: Deviation required for the display variables and filter constants because of memory map */ 

/* PRQA S 4395 EOF 
* MISRA-C: 2004 Rule 10.4: This deviation is required for library macros.  The rule is suppressed for the entire file */

/* MISRA-C:2004 Rule 19.1: Deviation required for the AUTOSAR Compliance */ 

/* PRQA S 3332 EOF 
* MISRA-C: 2004 Rule 19.11: This deviation is required for fault injection points 
* Warning 3332 is not seen in current file because constant BC_DIGHWTRQSENT_FAULTINJECTIONPOINT is defined in compiler_cfg header file */

#define D_DIFFTRQSCALE_ULS_F32					  2.0F 
#define D_HWTRQMAXRANGE_HWNM_F32				  10.0F
#define D_TRIMPERFORMED_CNT_LGC			  	      TRUE	
#define D_TRIMNOTPERFORMED_CNT_LGC			      FALSE	
#define D_MFGMODE_CNT_ENUM						  ManufacturingMode
#define D_ONERESOLUTIONCOUNT_HWNM_F32			  0.00390625f

#define D_DEFDIGHWTRQTRIM_HWNM_F32				  0.0F
#define D_DEFSSDIAGFILTOUT_HWNM_F32			  	  0.0F
#define D_HWTRQLPFSAMPLEINT_SEC_F32				  D_2MS_SEC_F32
#define D_TDIAGLPFSAMPLEINT_SEC_F32				  0.004F
#define D_CMCLPFSAMPLEINT_SEC_F32				  0.1F
#define D_SSLPFSAMPLEINT_SEC_F32				  0.1F
#define D_SSFILTSVLMT_HWNM_F32				  	  (k_T1T2SSLim_HwNm_f32 + D_ONERESOLUTIONCOUNT_HWNM_F32) 
#define D_FAILEDANDFAILEDTHISOPCYCLE_CNT_U08      (D_TESTFAILEDBIT_CNT_B8 | D_TESTFAILEDTHISOPCYCLEBIT_CNT_B8) 

#define DIGHWTRQSENT_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_TDiagFiltOut_HwNm_M_f32;
STATIC VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_SSDiagFiltOut_HwNm_M_f32;
STATIC VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_CMCFiltOut_HwNm_M_f32;
STATIC volatile VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_SumFiltOut_HwNm_D_f32;/* PRQA S 3218 */
STATIC volatile VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_CorrDiagFiltOut_HwNm_D_f32;/* PRQA S 3218 */
STATIC VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_T1_HwNm_M_f32;
STATIC VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_T2_HwNm_M_f32;
STATIC volatile VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_DigHwTrq_HwNm_D_f32;/* PRQA S 3218 */
STATIC VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_HwTrq_HwNm_M_f32;
STATIC VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_TrqSum_HwNm_M_f32;
STATIC volatile VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_HwTrqTrim_HwNm_D_f32;/* PRQA S 3218 */
STATIC volatile VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_TmpDigHwTrq_HwNm_D_f32;/* PRQA S 3218 */
#define DIGHWTRQSENT_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define DIGHWTRQSENT_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(LPF32KSV_Str, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_DigHwTrqKSV_M_str;
STATIC VAR(LPF32KSV_Str, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_TDiagFiltKSV_M_str;/* PRQA S 3218 */
STATIC VAR(LPF32KSV_Str, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_SSFiltKSV_M_str;
STATIC VAR(LPF32KSV_Str, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_CMCFiltKSV_M_str;
#define DIGHWTRQSENT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

#define DIGHWTRQSENT_START_SEC_VAR_SAVED_ZONEH_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, SA_DIGHWTRQSENT_VAR_NOINIT) DigHwTrqSENT_CMCFiltSV_HwNm_M_f32;
#define DIGHWTRQSENT_STOP_SEC_VAR_SAVED_ZONEH_32
#include "MemMap.h" /* PRQA S 5087 */


/* Local Functions */
STATIC FUNC(void, SA_DIGHWTRQSENT_CODE) TrimNotPerfDiag(VAR(ManufModeType, AUTOMATIC) MECCounter_Cnt_T_enum);



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
 * SInt16: Integer in interval [-32768...32767] (standard type)
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
 *   FLTINJ_DIGHWTRQSENT_T1FAULT (41u)
 *   FLTINJ_DIGHWTRQSENT_T2FAULT (42u)
 *   FLTINJ_TRQOVLSTA_LKAFAULT (91u)
 *   FLTINJ_TRQARBLIM_LKACMD (101u)
 *   FLTINJ_DDASTFACTRQST_DRVDYNCTRL (150u)
 *   FLTINJ_DDDMPFACTRQST_DRVDYNCTRL (151u)
 *   FLTINJ_DDRTNFACTRQST_DRVDYNCTRL (152u)
 *   FLTINJ_OUTPUTRAMPMULT_LMTCOD (153u)
 *   FLTINJ_ASSTEOTLIMIT_LMTCOD (154u)
 *   FLTINJ_SRLCOMVEHLONACCEL_SGNLCOND (155u)
 *   FLTINJ_ANAHWTORQUE (156u)
 *   FLTINJ_MTRVEL (160u)
 *   FLTINJ_PRKASTMFGSERVCH2_PRKASSISTCMD (200u)
 *   FLTINJ_PRKASTMFGSERVCH2_LRNPNCNTR (201u)
 * ManufModeType: Enumeration of integer in interval [0...2] with enumerators
 *   ProductionMode (0u)
 *   ManufacturingMode (1u)
 *   EngineeringMode (2u)
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
 * DigHwTrqSENTTrim_DataType: Record with elements
 *   k_EOLHwTrqTrim_HwNm_f32 of type Float
 *   k_EOLHwTrqTrimPerformed_Cnt_Lgc of type Boolean
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
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_ZERO_ULS_F32 = 0
 * SInt16: D_ZERO_CNT_S16 = 0
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   DigHwTrqSENTTrim_DataType *Rte_Pim_DigTrqTrim(void)
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_SA_DIGHWTRQSENT_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   ManufModeType Rte_IRead_DigHwTrqSENT_Init1_MECCounter_Cnt_enum(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_NvM_DigHwTrqSENTTrim_Srv_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigHwTrqSENT_Init1
 *********************************************************************************************************************/


	VAR(ManufModeType, AUTOMATIC) MECCounter_Cnt_T_enum;
	VAR(NvM_RequestResultType, AUTOMATIC) NvMBlkStatus_Cnt_T_u8;

	/*** Initialize Static Variables ***/

	/* Initialize filters */

	LPF_Init_f32_m(0.0f, k_HwTrqLPFFc_Hz_f32, D_HWTRQLPFSAMPLEINT_SEC_F32, &DigHwTrqSENT_DigHwTrqKSV_M_str);
	LPF_Init_f32_m(0.0f, k_T1T2SSLPFFc_Hz_f32, D_SSLPFSAMPLEINT_SEC_F32, &DigHwTrqSENT_SSFiltKSV_M_str);

	/* CMC filter state variable is stored in EEPROM on powerdown and restored on powerup */
	/* initialize CMC filter and filter output using restored value of state variable */
	LPF_Init_f32_m(DigHwTrqSENT_CMCFiltSV_HwNm_M_f32, k_T1T2CMCLPFFc_Hz_f32, D_CMCLPFSAMPLEINT_SEC_F32, &DigHwTrqSENT_CMCFiltKSV_M_str);
	DigHwTrqSENT_CMCFiltOut_HwNm_M_f32 = DigHwTrqSENT_CMCFiltSV_HwNm_M_f32;

	DigHwTrqSENT_SSDiagFiltOut_HwNm_M_f32 = D_DEFSSDIAGFILTOUT_HWNM_F32;

	/*** Initialize Module Internal Variables ***/

	MECCounter_Cnt_T_enum = Rte_IRead_DigHwTrqSENT_Init1_MECCounter_Cnt_enum();

	/* Torque Trim Calibration Failure Diagnostic */
	(void)Rte_Call_NvM_DigHwTrqSENTTrim_Srv_GetErrorStatus(&NvMBlkStatus_Cnt_T_u8);

	if (NVM_REQ_OK != NvMBlkStatus_Cnt_T_u8)
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PriSnsrTrqStorFlt, 0x02U, NTC_STATUS_FAILED);
	}
	else
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PriSnsrTrqStorFlt, 0x02U, NTC_STATUS_PASSED);
	}

	TrimNotPerfDiag(MECCounter_Cnt_T_enum);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_Per1
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
 *   Float Rte_IRead_DigHwTrqSENT_Per1_T1_HwNm_f32(void)
 *   Float Rte_IRead_DigHwTrqSENT_Per1_T2_HwNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_DigHwTrqSENT_Per1_HwTorque_HwNm_f32(Float data)
 *   Float *Rte_IWriteRef_DigHwTrqSENT_Per1_HwTorque_HwNm_f32(void)
 *   void Rte_IWrite_DigHwTrqSENT_Per1_SysCHwTorque_HwNm_f32(Float data)
 *   Float *Rte_IWriteRef_DigHwTrqSENT_Per1_SysCHwTorque_HwNm_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FaultInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigHwTrqSENT_Per1
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) DigDiffHwTrq_HwNm_T_f32;
	VAR(float32, AUTOMATIC) TmpDigHwTrq_HwNm_T_f32;
	VAR(float32, AUTOMATIC) DigHwTrq_HwNm_T_f32;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_DigHwTrqSENT_Per1_CP0_CheckpointReached();

	DigHwTrqSENT_T1_HwNm_M_f32 = Rte_IRead_DigHwTrqSENT_Per1_T1_HwNm_f32();
	DigHwTrqSENT_T2_HwNm_M_f32 = Rte_IRead_DigHwTrqSENT_Per1_T2_HwNm_f32();

#if (STD_ON == BC_DIGHWTRQSENT_FAULTINJECTIONPOINT)
	(void) Rte_Call_FaultInjection_SCom_FltInjection(&DigHwTrqSENT_T1_HwNm_M_f32, FLTINJ_DIGHWTRQSENT_T1FAULT);
	(void) Rte_Call_FaultInjection_SCom_FltInjection(&DigHwTrqSENT_T2_HwNm_M_f32, FLTINJ_DIGHWTRQSENT_T2FAULT);
#endif

	/*** Handwheel Torque Calculation ***/

	DigDiffHwTrq_HwNm_T_f32 = DigHwTrqSENT_T1_HwNm_M_f32 - DigHwTrqSENT_T2_HwNm_M_f32;

	TmpDigHwTrq_HwNm_T_f32 = (DigDiffHwTrq_HwNm_T_f32 / D_DIFFTRQSCALE_ULS_F32) - Rte_Pim_DigTrqTrim()->k_EOLHwTrqTrim_HwNm_f32;

	DigHwTrq_HwNm_T_f32 = LPF_OpUpdate_f32_m(TmpDigHwTrq_HwNm_T_f32, &DigHwTrqSENT_DigHwTrqKSV_M_str);

	DigHwTrqSENT_HwTrq_HwNm_M_f32 = Limit_m(DigHwTrq_HwNm_T_f32, -D_HWTRQMAXRANGE_HWNM_F32, D_HWTRQMAXRANGE_HWNM_F32);

	DigHwTrqSENT_TmpDigHwTrq_HwNm_D_f32 = TmpDigHwTrq_HwNm_T_f32;
	DigHwTrqSENT_DigHwTrq_HwNm_D_f32 = DigHwTrq_HwNm_T_f32;

	Rte_IWrite_DigHwTrqSENT_Per1_HwTorque_HwNm_f32(DigHwTrqSENT_HwTrq_HwNm_M_f32);
	Rte_IWrite_DigHwTrqSENT_Per1_SysCHwTorque_HwNm_f32(DigHwTrqSENT_HwTrq_HwNm_M_f32);

	/* Configurable End of Runnable Checkpoint */
    Rte_Call_DigHwTrqSENT_Per1_CP1_CheckpointReached();

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 4ms
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_DigHwTrqSENT_Per2_SrlComHwTrqValid_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_DigHwTrqSENT_Per2_SrlComHwTrqValid_Cnt_lgc(void)
 *   void Rte_IWrite_DigHwTrqSENT_Per2_SrlComHwTrq_HwNm_f32(Float data)
 *   Float *Rte_IWriteRef_DigHwTrqSENT_Per2_SrlComHwTrq_HwNm_f32(void)
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
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigHwTrqSENT_Per2
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) TmpTrqSum_HwNm_T_f32;
	VAR(float32, AUTOMATIC) AbsSSFiltOut_HwNm_T_f32;
	VAR(float32, AUTOMATIC) AbsSumFiltOut_HwNm_T_f32;
	VAR(float32, AUTOMATIC) SumFiltOut_HwNm_T_f32;
	VAR(float32, AUTOMATIC) CorrDiagFiltOut_HwNm_T_f32;
	VAR(float32, AUTOMATIC) TDiagFiltFc_Hz_T_f32;
	VAR(uint16, AUTOMATIC)  AbsTrqSum_HwNm_T_u5p11;
	VAR(uint16, AUTOMATIC)  TDiagFiltFc_Hz_T_u6p10;
	VAR(uint8, AUTOMATIC)   T1vsT2Status_Cnt_T_u08;
	VAR(uint8, AUTOMATIC)   TrqSensorNotTrimmedStatus_Cnt_T_u08;
	VAR(uint8, AUTOMATIC)   PriSnsrTrqStorStatus_Cnt_T_u08;
	VAR(boolean, AUTOMATIC) SrlComHwTrqValid_Cnt_T_lgc;


	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_DigHwTrqSENT_Per2_CP0_CheckpointReached();

	/*** T1 vs T2 Comparison Diagnostic ***/

	TmpTrqSum_HwNm_T_f32 = DigHwTrqSENT_T1_HwNm_M_f32 + DigHwTrqSENT_T2_HwNm_M_f32;
	
	TmpTrqSum_HwNm_T_f32 = TmpTrqSum_HwNm_T_f32 / D_DIFFTRQSCALE_ULS_F32;

	DigHwTrqSENT_TrqSum_HwNm_M_f32 = Limit_m(TmpTrqSum_HwNm_T_f32, -k_T1vsT2TrqSum_HwNm_f32, k_T1vsT2TrqSum_HwNm_f32);

	AbsTrqSum_HwNm_T_u5p11 = FPM_FloatToFixed_m(Abs_f32_m(DigHwTrqSENT_TrqSum_HwNm_M_f32), u5p11_T);

	TDiagFiltFc_Hz_T_u6p10 = IntplVarXY_u16_u16Xu16Y_Cnt(
									t_T1T2IndTrsTimecon_HwNm_u5p11,
									t_T1T2DepTrsTimecon_Hz_u6p10,
									TableSize_m(t_T1T2IndTrsTimecon_HwNm_u5p11),
									AbsTrqSum_HwNm_T_u5p11);

	TDiagFiltFc_Hz_T_f32 = FPM_FixedToFloat_m(TDiagFiltFc_Hz_T_u6p10, u6p10_T);

	LPF_KUpdate_f32_m(TDiagFiltFc_Hz_T_f32, D_TDIAGLPFSAMPLEINT_SEC_F32, &DigHwTrqSENT_TDiagFiltKSV_M_str);

	DigHwTrqSENT_TDiagFiltOut_HwNm_M_f32 = LPF_OpUpdate_f32_m(DigHwTrqSENT_TrqSum_HwNm_M_f32, &DigHwTrqSENT_TDiagFiltKSV_M_str);

	/*** Fault Detection ***/

	CorrDiagFiltOut_HwNm_T_f32 = Limit_m(DigHwTrqSENT_CMCFiltOut_HwNm_M_f32, -k_CMCLPFOutLim_HwNm_f32, k_CMCLPFOutLim_HwNm_f32);
	SumFiltOut_HwNm_T_f32 = DigHwTrqSENT_TDiagFiltOut_HwNm_M_f32 - CorrDiagFiltOut_HwNm_T_f32;
	AbsSumFiltOut_HwNm_T_f32 = Abs_f32_m(SumFiltOut_HwNm_T_f32);
	AbsSSFiltOut_HwNm_T_f32 = Abs_f32_m(DigHwTrqSENT_SSDiagFiltOut_HwNm_M_f32);

	if( (AbsSSFiltOut_HwNm_T_f32 >= k_T1T2SSLim_HwNm_f32)
	 || (AbsSumFiltOut_HwNm_T_f32 >= k_T1T2TransFltLim_HwNm_f32) )
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_T1vsT2, 0x01U, NTC_STATUS_FAILED);
	}
	else
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_T1vsT2, 0x01U, NTC_STATUS_PASSED);
	}

	/* Set display variables */
	DigHwTrqSENT_SumFiltOut_HwNm_D_f32 = SumFiltOut_HwNm_T_f32;
	DigHwTrqSENT_CorrDiagFiltOut_HwNm_D_f32 = CorrDiagFiltOut_HwNm_T_f32;

	/* Serial Comm outputs */


	(void)Rte_Call_NxtrDiagMgr_GetNTCStatus (NTC_Num_T1vsT2, &T1vsT2Status_Cnt_T_u08);
	(void)Rte_Call_NxtrDiagMgr_GetNTCStatus (NTC_Num_TrqSensorNotTrimmed, &TrqSensorNotTrimmedStatus_Cnt_T_u08);
	(void)Rte_Call_NxtrDiagMgr_GetNTCStatus (NTC_Num_PriSnsrTrqStorFlt, &PriSnsrTrqStorStatus_Cnt_T_u08);

	if ( ((T1vsT2Status_Cnt_T_u08 & D_FAILEDANDFAILEDTHISOPCYCLE_CNT_U08) == D_FAILEDANDFAILEDTHISOPCYCLE_CNT_U08) ||
		 ((TrqSensorNotTrimmedStatus_Cnt_T_u08 & D_FAILEDANDFAILEDTHISOPCYCLE_CNT_U08) == D_FAILEDANDFAILEDTHISOPCYCLE_CNT_U08) ||
		 ((PriSnsrTrqStorStatus_Cnt_T_u08& D_FAILEDANDFAILEDTHISOPCYCLE_CNT_U08) == D_FAILEDANDFAILEDTHISOPCYCLE_CNT_U08) )
	{
		SrlComHwTrqValid_Cnt_T_lgc = FALSE;
	}
	else
	{
		SrlComHwTrqValid_Cnt_T_lgc = TRUE;
	}

	Rte_IWrite_DigHwTrqSENT_Per2_SrlComHwTrq_HwNm_f32 (DigHwTrqSENT_HwTrq_HwNm_M_f32);
	Rte_IWrite_DigHwTrqSENT_Per2_SrlComHwTrqValid_Cnt_lgc (SrlComHwTrqValid_Cnt_T_lgc);



	/* Configurable End of Runnable Checkpoint */
    Rte_Call_DigHwTrqSENT_Per2_CP1_CheckpointReached();

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_Per3
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 100ms
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Per3(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigHwTrqSENT_Per3
 *********************************************************************************************************************/
	
	VAR(float32, AUTOMATIC) AbsHwTrq_HwNm_T_f32;

  	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_DigHwTrqSENT_Per3_CP0_CheckpointReached();

	/* Limit the SV */
	DigHwTrqSENT_SSFiltKSV_M_str.SV_Uls_f32 = Limit_m(DigHwTrqSENT_SSDiagFiltOut_HwNm_M_f32, -D_SSFILTSVLMT_HWNM_F32, D_SSFILTSVLMT_HWNM_F32);
	/*** Steady State Filter ***/
	DigHwTrqSENT_SSDiagFiltOut_HwNm_M_f32 = LPF_OpUpdate_f32_m(DigHwTrqSENT_TDiagFiltOut_HwNm_M_f32, &DigHwTrqSENT_SSFiltKSV_M_str);

	/*** Common Mode Compensation ***/
	AbsHwTrq_HwNm_T_f32 = Abs_f32_m(DigHwTrqSENT_HwTrq_HwNm_M_f32);
	if ( AbsHwTrq_HwNm_T_f32 <= k_T1T2CMCLPFEnable_HwNm_f32 )
	{
		DigHwTrqSENT_CMCFiltOut_HwNm_M_f32 = LPF_OpUpdate_f32_m (DigHwTrqSENT_TrqSum_HwNm_M_f32, &DigHwTrqSENT_CMCFiltKSV_M_str);
		/* save the SV */
		DigHwTrqSENT_CMCFiltSV_HwNm_M_f32 = DigHwTrqSENT_CMCFiltKSV_M_str.SV_Uls_f32;
	}


	/* Configurable End of Runnable Checkpoint */
    Rte_Call_DigHwTrqSENT_Per3_CP1_CheckpointReached();


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_SCom_ClrTrqTrim
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ClrTrqTrim> of PortPrototype <DigHwTrqSENT_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MECCounter_Cnt_enum(ManufModeType *data)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DigHwTrqSENT_SCom_ClrTrqTrim(void)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DigHwTrqSENT_SCom_ConditionsNotCorrect
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_ClrTrqTrim(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigHwTrqSENT_SCom_ClrTrqTrim (returns application error)
 *********************************************************************************************************************/
	VAR(ManufModeType, AUTOMATIC) MECCounter_Cnt_T_enum;
	
	(void) Rte_Read_MECCounter_Cnt_enum(&MECCounter_Cnt_T_enum);
	
	Rte_Pim_DigTrqTrim()->k_EOLHwTrqTrim_HwNm_f32= D_DEFDIGHWTRQTRIM_HWNM_F32;
	Rte_Pim_DigTrqTrim()->k_EOLHwTrqTrimPerformed_Cnt_Lgc = D_TRIMNOTPERFORMED_CNT_LGC;
	(void)Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(NULL_PTR);
	
	TrimNotPerfDiag(MECCounter_Cnt_T_enum);
	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_SCom_SetTrqTrim
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <SetTrqTrim> of PortPrototype <DigHwTrqSENT_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MECCounter_Cnt_enum(ManufModeType *data)
 *   Std_ReturnType Rte_Read_T1_HwNm_f32(Float *data)
 *   Std_ReturnType Rte_Read_T2_HwNm_f32(Float *data)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DigHwTrqSENT_SCom_SetTrqTrim(void)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DigHwTrqSENT_SCom_ConditionsNotCorrect
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_SetTrqTrim(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigHwTrqSENT_SCom_SetTrqTrim (returns application error)
 *********************************************************************************************************************/

	VAR(float32, AUTOMATIC) T1_HwNm_T_f32;
	VAR(float32, AUTOMATIC) T2_HwNm_T_f32;
	VAR(float32, AUTOMATIC) HwTrqTrim_HwNm_T_f32;
	VAR(Std_ReturnType, AUTOMATIC) RetValue;
	VAR(ManufModeType, AUTOMATIC) MECCounter_Cnt_T_enum;
	
	(void) Rte_Read_MECCounter_Cnt_enum(&MECCounter_Cnt_T_enum);
	(void) Rte_Read_T1_HwNm_f32 (&T1_HwNm_T_f32);
	(void) Rte_Read_T2_HwNm_f32 (&T2_HwNm_T_f32);
	HwTrqTrim_HwNm_T_f32 = (T1_HwNm_T_f32 - T2_HwNm_T_f32) / D_DIFFTRQSCALE_ULS_F32;
	
	if( k_MaxHwTrqTrim_HwNm_f32 < Abs_f32_m(HwTrqTrim_HwNm_T_f32) )
	{
		RetValue = RTE_E_DigHwTrqSENT_SCom_ConditionsNotCorrect;
	}
	else
	{
		Rte_Pim_DigTrqTrim()->k_EOLHwTrqTrim_HwNm_f32 = HwTrqTrim_HwNm_T_f32;
		Rte_Pim_DigTrqTrim()->k_EOLHwTrqTrimPerformed_Cnt_Lgc = D_TRIMPERFORMED_CNT_LGC;
		(void)Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(NULL_PTR); 
		RetValue = RTE_E_OK;
	}
	
	TrimNotPerfDiag(MECCounter_Cnt_T_enum);
	
	DigHwTrqSENT_HwTrqTrim_HwNm_D_f32 = HwTrqTrim_HwNm_T_f32;

	return RetValue;
	

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_SCom_TrimData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <TrimData> of PortPrototype <DigHwTrqSENT_SCom>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void DigHwTrqSENT_SCom_TrimData(Float *EOLHwTrqTrim_HwNm_f32, Boolean *EOLHwTrqTrimPerformed_Cnt_Lgc)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_TrimData(P2VAR(Float, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) EOLHwTrqTrim_HwNm_f32, P2VAR(Boolean, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) EOLHwTrqTrimPerformed_Cnt_Lgc)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigHwTrqSENT_SCom_TrimData
 *********************************************************************************************************************/
   
   *EOLHwTrqTrim_HwNm_f32 = Rte_Pim_DigTrqTrim()->k_EOLHwTrqTrim_HwNm_f32;
   *EOLHwTrqTrimPerformed_Cnt_Lgc = Rte_Pim_DigTrqTrim()->k_EOLHwTrqTrimPerformed_Cnt_Lgc;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_SCom_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DigHwTrqSENT_SCom>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void DigHwTrqSENT_SCom_WriteData(Float HwTrqTrim_HwNm_f32)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_WriteData(Float HwTrqTrim_HwNm_f32)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigHwTrqSENT_SCom_WriteData
 *********************************************************************************************************************/
	Rte_Pim_DigTrqTrim()->k_EOLHwTrqTrim_HwNm_f32 = HwTrqTrim_HwNm_f32;
	Rte_Pim_DigTrqTrim()->k_EOLHwTrqTrimPerformed_Cnt_Lgc = D_TRIMPERFORMED_CNT_LGC;
	(void)Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(NULL_PTR); 

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_SA_DIGHWTRQSENT_APPL_CODE
#include "MemMap.h"/* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


STATIC FUNC(void, SA_DIGHWTRQSENT_CODE) TrimNotPerfDiag(VAR(ManufModeType, AUTOMATIC) MECCounter_Cnt_T_enum)
{

	if(( D_TRIMNOTPERFORMED_CNT_LGC == Rte_Pim_DigTrqTrim()->k_EOLHwTrqTrimPerformed_Cnt_Lgc ) && (D_MFGMODE_CNT_ENUM != MECCounter_Cnt_T_enum))
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TrqSensorNotTrimmed, 0x01U, NTC_STATUS_FAILED);
	}
	else
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TrqSensorNotTrimmed, 0x01U, NTC_STATUS_PASSED);
	}
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
