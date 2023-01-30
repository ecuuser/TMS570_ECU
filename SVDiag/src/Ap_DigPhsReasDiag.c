/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_DigPhsReasDiag.c
 *     Workspace:  C:/Rijvi_Synergy/Core_Component/Working/SVDiag-jzk9cc/SVDiag/autosar
 *     SW-C Type:  Ap_DigPhsReasDiag
 *  Generated at:  Mon Dec  1 14:24:56 2014
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_DigPhsReasDiag>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Wed Jan 26 12:00:00 2012
 * %version:          14 %
 * %date_modified:    Thu Oct  3 16:11:34 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                           SCR #
 * --------  -------  --------  ---------------------------------------------------------------------------  ----------
 * 01/26/12  1        JJW       Component Creation                                                           4846
 * 01/27/12  2        OT        Updated Input Names to Match FDD
 * 01/27/12  3        JJW       Changed states where DigPhsReasDiag_Per1 is run
 * 01/31/12  4        OT        Updated to latest FDD (002-G), consolidated common processing
 * 09/26/12  5        Selva     Checkpoints added and mempmap macros corrected		                          6335
 * 10/26/12  6        Selva     LRPR Systematic coverage added	                                              6732
 * 02/19/13  7        KJS       QAC corrections.
 * 03/15/13	 8		  SP		Updated to latest FDD V003													  7588
 * 05/08/13	 9,10		  Selva     Anamoly 4968,4953 Fixes			
 * 06/26/13  11      Selva      (Anamoly 5049 and A5010 ) FDDv4 and FDD V5	updated                           8674
 * 07/30/13  12       VT        Anomaly 5174 Fix                                                              9235
 * 10/03/13  13       VT        Updated module and display variables with SVDiag and QAC fixes               10134 
 * 12/01/14  14       Rijvi     Updated the module per the latest FDD rev.008                                12751 
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_DigPhsReasDiag.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/* Include Statements */
#include "CalConstants.h"
#include "fixmath.h"
#include "GlobalMacro.h"
#include "filters.h"
#include "Ap_DigPhsReasDiag_Cfg.h"

/* Local Constants */

#define D_RESETDIGDIAGACTIVE_CNT_U08		0x00U
#define D_LRPHSREASLOOPRATE_CNT_F32			0.002F
#define D_ERRORLIMIT_CNT_S32 262136L  /* 2^18 - 8 == 262136 */
#define D_PHASEA_CNT_U16 0U
#define D_PHASEB_CNT_U16 1U
#define D_PHASEC_CNT_U16 2U

/*D_NHETFREQUENCY_HZ_F32 should be defined in Cfg header for DigPhsReasDiag. */
#define D_NHETCTSPERLRPRLOOP_CNT_F32		(D_NHETFREQUENCY_HZ_F32 * D_LRPHSREASLOOPRATE_CNT_F32)
#define D_PHSADVCNTSPERREV_CNT_U16		6144U
#define D_PHSADVCNTS180DEG_CNT_U16		3072U /*(D_PHSADVCNTSPERREV_CNT_S16 / 2U)*/
#define D_PHSPOSADVCNTS90DEG_CNT_U16	1536U /*	(D_PHSADVCNTSPERREV_CNT_S16 / 4U)*/
#define D_PHSNEGADVCNTS90DEG_CNT_S16	(-1536) /*(-D_PHSADVCNTSPERREV_CNT_S16 / 4U)*/
#define D_0DEG_REV_U0P16				(FPM_InitFixedPoint_m(0.0, u0p16_T))
#define D_30DEG_REV_U0P16				(FPM_InitFixedPoint_m(0.0833333333, u0p16_T))
#define D_60DEG_REV_U0P16				(FPM_InitFixedPoint_m(0.1666666666, u0p16_T))
#define D_240DEG_REV_U0P16			(FPM_InitFixedPoint_m(0.6666666666, u0p16_T))
#define D_120DEG_REV_U0P16			(FPM_InitFixedPoint_m(0.3333333333, u0p16_T))
#define D_180DEG_REV_U0P16			(FPM_InitFixedPoint_m(0.5, u0p16_T))
#define D_PHASEAOFFSETNRM_REV_U0P16	D_0DEG_REV_U0P16
#define D_PHASEBOFFSETNRM_REV_U0P16	((uint16)(D_PHASEAOFFSETNRM_REV_U0P16 - D_120DEG_REV_U0P16))
#define D_PHASECOFFSETNRM_REV_U0P16	(D_PHASEAOFFSETNRM_REV_U0P16 + D_120DEG_REV_U0P16)
#define D_PHASEAOFFSETINV_REV_U0P16	D_60DEG_REV_U0P16
#define D_PHASEBOFFSETINV_REV_U0P16	(D_PHASEAOFFSETINV_REV_U0P16 + D_120DEG_REV_U0P16)
#define D_PHASECOFFSETINV_REV_U0P16	((uint16)(D_PHASEAOFFSETINV_REV_U0P16 - D_120DEG_REV_U0P16))
#define D_REVPCNT_ULS_U0P32			699051UL		/* (FPM_InitFixedPoint_m(1/D_PACNTSPREV_ULS_U16P0, u0p32_T)) */
#define D_PACNTSPREV_ULS_U16P0		6144U
#define D_SCALER16_CNT_U16              16U 
#define D_35DEG_REV_U0P16			(FPM_InitFixedPoint_m(0.0972222222, u0p16_T))
#define D_205DEG_REV_U0P16			(FPM_InitFixedPoint_m(0.5972222222, u0p16_T))
#define D_245DEG_REV_U0P16			(FPM_InitFixedPoint_m(0.6805555555, u0p16_T))
#define D_355DEG_REV_U0P16			(FPM_InitFixedPoint_m(0.9861111111, u0p16_T))
#define SETDIAGRESPHSREASACTIVEBIT_U16   6
#define D_POSITIVEONE_CNT_S8            1


/* Static Variables */
#define DIGPHSREASDIAG_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
STATIC VAR(sint32, AP_DIGPHSREASDIAG_VAR) SVDiag_FilterSV_Cnt_M_s18p13[D_PHASEC_CNT_U16 + 1U];
STATIC VAR(float32, AP_DIGPHSREASDIAG_VAR) SVDiag_LRPRAdjModldAComp_Cnt_M_f32;
STATIC VAR(float32, AP_DIGPHSREASDIAG_VAR) SVDiag_PrevLRPRAdjModldComp_Cnt_M_f32;
STATIC VAR(float32, AP_DIGPHSREASDIAG_VAR) SVDiag_MaxNrCommOffVltg_Cnt_M_f32;
STATIC volatile VAR(float32, AP_DIGPHSREASDIAG_VAR) SVDiag_LRPRHighLimit_Cnt_D_f32[D_PHASEC_CNT_U16 + 1U];
STATIC volatile VAR(float32, AP_DIGPHSREASDIAG_VAR) SVDiag_LRPRLowLimit_Cnt_D_f32[D_PHASEC_CNT_U16 + 1U];
#define DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define DIGPHSREASDIAG_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_DIGPHSREASDIAG_VAR) SVDiag_PrevLRPRHighSector_Cnt_M_lgc[D_PHASEC_CNT_U16 + 1U];
STATIC VAR(boolean, AP_DIGPHSREASDIAG_VAR) SVDiag_LRPRHighSector_Cnt_M_lgc[D_PHASEC_CNT_U16 + 1U];
STATIC VAR(boolean, AP_DIGPHSREASDIAG_VAR) SVDiag_PrevLRPRLowSector_Cnt_M_lgc[D_PHASEC_CNT_U16 + 1U];
STATIC VAR(boolean, AP_DIGPHSREASDIAG_VAR) SVDiag_LRPRLowSector_Cnt_M_lgc[D_PHASEC_CNT_U16 + 1U];

#define DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */


#define DIGPHSREASDIAG_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, AP_DIGPHSREASDIAG_VAR) SVDiag_PrevLRPRPhsAdvComp_Cnt_M_u16;
STATIC VAR(uint16, AP_DIGPHSREASDIAG_VAR) SVDiag_LRPRPhsAdvComp_Cnt_M_u16;
STATIC VAR(uint16, AP_DIGPHSREASDIAG_VAR) SVDiag_PhaseOffset_Rev_M_u0p16[D_PHASEC_CNT_U16+1U];
STATIC VAR(uint16, AP_DIGPHSREASDIAG_VAR) SVDiag_LowPhReasErrorAcc_Cnt_M_u16;
#define DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

#define DIGPHSREASDIAG_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint8, AP_DIGPHSREASDIAG_VAR) SVDiag_HighResPhsReasDisable_M_u8;
STATIC VAR(uint8, AP_DIGPHSREASDIAG_VAR) SVDiag_LowResPhsReasDisable_M_u8;
#define DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */

STATIC INLINE FUNC(void, RTE_AP_DIGPHSREASDIAG_APPL_CODE) PhaseGroundTabLookupoffset(VAR(sint8, AUTOMATIC) MtrElecMechPol_Cnt_T_s08);
STATIC INLINE FUNC(uint16, RTE_AP_DIGPHSREASDIAG_APPL_CODE) Read_CountToRev(VAR(uint16, AUTOMATIC) Var_Cnt_T_u16);
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
 * SInt8: Integer in interval [-128...127] (standard type)
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
 * SInt16: D_ZERO_CNT_S16 = 0
 * SInt8: D_ZERO_CNT_S8 = 0
 * UInt32: D_ZERO_CNT_U32 = 0u
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_DIGPHSREASDIAG_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigPhsReasDiag_Init
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

FUNC(void, RTE_AP_DIGPHSREASDIAG_APPL_CODE) DigPhsReasDiag_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigPhsReasDiag_Init
 *********************************************************************************************************************/
SVDiag_MaxNrCommOffVltg_Cnt_M_f32=  ((float32)D_MAXPWMFREQ_HZ_U32 * D_LRPHSREASLOOPRATE_CNT_F32 * (float32)t_CommOffsetTblY_Cnt_u16[0] *k_LRPRCommOffsetMargin_Uls_f32
 );

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigPhsReasDiag_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <OFF, DISABLE, WARMINIT>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   UInt32 Rte_IRead_DigPhsReasDiag_Per1_ExpectedOnTimeA_Cnt_u32(void)
 *   UInt32 Rte_IRead_DigPhsReasDiag_Per1_ExpectedOnTimeB_Cnt_u32(void)
 *   UInt32 Rte_IRead_DigPhsReasDiag_Per1_ExpectedOnTimeC_Cnt_u32(void)
 *   Boolean Rte_IRead_DigPhsReasDiag_Per1_GateDriveResetActive_Cnt_lgc(void)
 *   Float Rte_IRead_DigPhsReasDiag_Per1_LRPRCorrectedMtrPosCaptured_Rev_f32(void)
 *   Float Rte_IRead_DigPhsReasDiag_Per1_LRPRModulationIndexCaptured_Uls_f32(void)
 *   SInt16 Rte_IRead_DigPhsReasDiag_Per1_LRPRPhaseadvanceCaptured_Cnt_s16(void)
 *   UInt32 Rte_IRead_DigPhsReasDiag_Per1_MeasuredOnTimeA_Cnt_u32(void)
 *   UInt32 Rte_IRead_DigPhsReasDiag_Per1_MeasuredOnTimeB_Cnt_u32(void)
 *   UInt32 Rte_IRead_DigPhsReasDiag_Per1_MeasuredOnTimeC_Cnt_u32(void)
 *   Float Rte_IRead_DigPhsReasDiag_Per1_MotorVelMRFUnfiltered_MtrRadpS_f32(void)
 *   SInt8 Rte_IRead_DigPhsReasDiag_Per1_MtrElecMechPolarity_Cnt_s08(void)
 *   Boolean Rte_IRead_DigPhsReasDiag_Per1_PDActivateTest_Cnt_lgc(void)
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

FUNC(void, RTE_AP_DIGPHSREASDIAG_APPL_CODE) DigPhsReasDiag_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigPhsReasDiag_Per1
 *********************************************************************************************************************/


	VAR(uint32, AUTOMATIC) MeasuredOnTime_Cnt_T_u32[D_PHASEC_CNT_U16 + 1U];
	VAR(uint32, AUTOMATIC) ExpectedOnTime_Cnt_T_u32[D_PHASEC_CNT_U16 + 1U];
	VAR(sint32, AUTOMATIC) HighResError_Cnt_T_s32[D_PHASEC_CNT_U16 + 1U];
	VAR(sint32, AUTOMATIC) Error_Cnt_T_s18pm3[D_PHASEC_CNT_U16 + 1U];
	VAR(sint16, AUTOMATIC) ErrorFiltOut_Cnt_T_s18pm3[D_PHASEC_CNT_U16 + 1U];
	VAR(sint32, AUTOMATIC) ErrorFiltOut_Cnt_T_s32[D_PHASEC_CNT_U16 + 1U];
	VAR(uint8, AUTOMATIC) ParamBits_Cnt_T_u08;
	
	VAR(sint16, AUTOMATIC) LRPRPhaseadvanceCaptured_Cnt_T_s16;
	VAR(float32, AUTOMATIC) LRPRModIdx_Uls_T_f32;
	VAR(uint16, AUTOMATIC) LRPRPhaseAdvAdj_Cnt_T_u16;
	VAR(boolean, AUTOMATIC) SetFaultCounter_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) LRPRMtrPosCaptured_Rev_T_f32;
	VAR(float32, AUTOMATIC) MotorVelMRFUnfilt_MtrRadpS_T_f32;
	VAR(uint16, AUTOMATIC) LRPRMtrPosNor_rev_T_u0p16[D_PHASEC_CNT_U16 + 1U];
	VAR(uint16, AUTOMATIC) i;
	VAR(float32, AUTOMATIC) LRPRHighLimit_Cnt_T_f32;
	VAR(float32, AUTOMATIC) LRPRLowLimit_Cnt_T_f32;
	VAR(sint8, AUTOMATIC) MtrElecMechPolarity_Cnt_T_s08;
	VAR(sint16, AUTOMATIC) PhsAdvComp_Cnt_T_s16;
	VAR(sint16, AUTOMATIC) PrevPhsAdvComp_Cnt_T_s16;
	VAR(boolean, AUTOMATIC) PDActivateTest_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) GateDriveResetActive_Cnt_T_lgc;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_DigPhsReasDiag_Per1_CP0_CheckpointReached(); /* PRQA S 3112 */

	
	MeasuredOnTime_Cnt_T_u32[D_PHASEA_CNT_U16] = Rte_IRead_DigPhsReasDiag_Per1_MeasuredOnTimeA_Cnt_u32();
	MeasuredOnTime_Cnt_T_u32[D_PHASEB_CNT_U16] = Rte_IRead_DigPhsReasDiag_Per1_MeasuredOnTimeB_Cnt_u32();
	MeasuredOnTime_Cnt_T_u32[D_PHASEC_CNT_U16] = Rte_IRead_DigPhsReasDiag_Per1_MeasuredOnTimeC_Cnt_u32();
	/* LRPR Expected On time is same as HRPR*/
	ExpectedOnTime_Cnt_T_u32[D_PHASEA_CNT_U16] = Rte_IRead_DigPhsReasDiag_Per1_ExpectedOnTimeA_Cnt_u32();
	ExpectedOnTime_Cnt_T_u32[D_PHASEB_CNT_U16] = Rte_IRead_DigPhsReasDiag_Per1_ExpectedOnTimeB_Cnt_u32();
	ExpectedOnTime_Cnt_T_u32[D_PHASEC_CNT_U16] = Rte_IRead_DigPhsReasDiag_Per1_ExpectedOnTimeC_Cnt_u32();
	
	/* Data collection for this subfunction is performed here (refer 6.1.2.2 in FDD)
	 * The values collected are MotorvelocityMRF, ElectricMachanicalpolarity */
	LRPRMtrPosCaptured_Rev_T_f32=Rte_IRead_DigPhsReasDiag_Per1_LRPRCorrectedMtrPosCaptured_Rev_f32();
	LRPRPhaseadvanceCaptured_Cnt_T_s16 =Rte_IRead_DigPhsReasDiag_Per1_LRPRPhaseadvanceCaptured_Cnt_s16(); 
	LRPRModIdx_Uls_T_f32 = Rte_IRead_DigPhsReasDiag_Per1_LRPRModulationIndexCaptured_Uls_f32();
	MotorVelMRFUnfilt_MtrRadpS_T_f32 = Rte_IRead_DigPhsReasDiag_Per1_MotorVelMRFUnfiltered_MtrRadpS_f32();
	MtrElecMechPolarity_Cnt_T_s08 = Rte_IRead_DigPhsReasDiag_Per1_MtrElecMechPolarity_Cnt_s08();
	PDActivateTest_Cnt_T_lgc = Rte_IRead_DigPhsReasDiag_Per1_PDActivateTest_Cnt_lgc();
	GateDriveResetActive_Cnt_T_lgc = Rte_IRead_DigPhsReasDiag_Per1_GateDriveResetActive_Cnt_lgc();

	/*Resetting Diagnostic bits*/
	ParamBits_Cnt_T_u08 = D_RESETDIGDIAGACTIVE_CNT_U08;
	
	/* 200ms delay counter */	
	SVDiag_HighResPhsReasDisable_M_u8++;
	if(SVDiag_HighResPhsReasDisable_M_u8 > 100U)
		{
			SVDiag_HighResPhsReasDisable_M_u8 = 100U;
		}
	SVDiag_LowResPhsReasDisable_M_u8++;
	if(SVDiag_LowResPhsReasDisable_M_u8 > 100U)
		{
			SVDiag_LowResPhsReasDisable_M_u8 = 100U;
		}
		
	/*Error Signal Determination and Filtering */
	for(i = D_PHASEA_CNT_U16; i <= D_PHASEC_CNT_U16; i++)
	{
		if( (MeasuredOnTime_Cnt_T_u32[i] >= k_PhsReasEnableThresh_Cnt_u32) ||
		    (ExpectedOnTime_Cnt_T_u32[i] >= k_PhsReasEnableThresh_Cnt_u32) )
		{
			if ( (SVDiag_HighResPhsReasDisable_M_u8 < 50U) || ( (TRUE == PDActivateTest_Cnt_T_lgc) && (SVDiag_HighResPhsReasDisable_M_u8 < 100U) ) || (GateDriveResetActive_Cnt_T_lgc == TRUE) )
				{
					HighResError_Cnt_T_s32[i] = 0;
				}
			else
				{
					HighResError_Cnt_T_s32[i] = ((sint32)ExpectedOnTime_Cnt_T_u32[i]) - ((sint32)MeasuredOnTime_Cnt_T_u32[i]) - k_PhsReasErrorTerm_Cnt_s16;
					HighResError_Cnt_T_s32[i] = Limit_m(HighResError_Cnt_T_s32[i], -D_ERRORLIMIT_CNT_S32, D_ERRORLIMIT_CNT_S32);
				}
			

			Error_Cnt_T_s18pm3[i] = FPM_Fix_m(HighResError_Cnt_T_s32[i], s31p0_T, s18pm3_T);
			
			SVDiag_FilterSV_Cnt_M_s18p13[i] = LPF_SvUpdate_s16InFixKTrunc_m (
										  Error_Cnt_T_s18pm3[i], 
										  SVDiag_FilterSV_Cnt_M_s18p13[i],
										  k_ErrorFiltKn_Cnt_u16);
			
			ErrorFiltOut_Cnt_T_s18pm3[i] = LPF_OpUpdate_s16InFixKTrunc_m(SVDiag_FilterSV_Cnt_M_s18p13[i]);
			
			ErrorFiltOut_Cnt_T_s32[i] = FPM_Fix_m(ErrorFiltOut_Cnt_T_s18pm3[i], s18pm3_T, s31p0_T);
			
			if( ErrorFiltOut_Cnt_T_s32[i] > ((sint32)k_ErrorThresh_Cnt_u32) ) /* Phase i: Measured Less than Expected */
			{
				ParamBits_Cnt_T_u08 |= (uint8) (1U << (i*2U));
			}
			else if( (-ErrorFiltOut_Cnt_T_s32[i]) > ((sint32)k_ErrorThresh_Cnt_u32) ) /* Phase i: Measured Greater than Expected */
			{
				ParamBits_Cnt_T_u08 |= (uint8) (1U << ((i*2U) + 1U));
			}
			else { }
		}
	}
	
	/*	Systematic Coverage Sub-Function Design for Low Res Phase Reasonableness :
	*  Assign the previous outputs*/
	SVDiag_PrevLRPRAdjModldComp_Cnt_M_f32 = SVDiag_LRPRAdjModldAComp_Cnt_M_f32;	
	SVDiag_PrevLRPRPhsAdvComp_Cnt_M_u16 = SVDiag_LRPRPhsAdvComp_Cnt_M_u16;
	/*Phase Grounding Table Lookup Offset is the implementation specific offset for each phase compensated for motor electromechanical polarity*/
	PhaseGroundTabLookupoffset(MtrElecMechPolarity_Cnt_T_s08);
	/* Perform the Absolute Function operation in the Sine Voltage Generation sub-function on the following pair of signals */
	/*Firewall Phase_Advance to +/- 90 ElecDeg */
	LRPRPhaseadvanceCaptured_Cnt_T_s16=Limit_m(LRPRPhaseadvanceCaptured_Cnt_T_s16,	
											D_PHSNEGADVCNTS90DEG_CNT_S16,(sint16)D_PHSPOSADVCNTS90DEG_CNT_U16);
	
	
	
	/*Torque direction can be controlled by advancing motor position, or in this case Phase Advance, by 180 ElecDeg */
	if (LRPRModIdx_Uls_T_f32 < 0.0F)
	{
		LRPRPhaseAdvAdj_Cnt_T_u16 = (uint16)(sint16)(LRPRPhaseadvanceCaptured_Cnt_T_s16 + (sint16)D_PHSADVCNTS180DEG_CNT_U16);
	}
	/*To assist with future table lookups the phase advance signal is normalized to 1 electrical revolution */
	else if (LRPRPhaseadvanceCaptured_Cnt_T_s16 < (sint16)0U)
	{
		LRPRPhaseAdvAdj_Cnt_T_u16 = (uint16)(sint16)(LRPRPhaseadvanceCaptured_Cnt_T_s16 + (sint16)D_PHSADVCNTSPERREV_CNT_U16);
	}
	else
	{
		LRPRPhaseAdvAdj_Cnt_T_u16 = (uint16)LRPRPhaseadvanceCaptured_Cnt_T_s16;
	}
	/* - Sign is accounted for the absolute value of Modulation_Index is taken	*/
	LRPRModIdx_Uls_T_f32 = Abs_f32_m(LRPRModIdx_Uls_T_f32);
	SVDiag_LRPRAdjModldAComp_Cnt_M_f32 =LRPRModIdx_Uls_T_f32;
	
	
	SVDiag_LRPRPhsAdvComp_Cnt_M_u16 =LRPRPhaseAdvAdj_Cnt_T_u16;
	SetFaultCounter_Cnt_T_lgc= TRUE;
	/*Calculate and Normalize Motor Position for all three phases*/
	for(i = D_PHASEA_CNT_U16; i <= D_PHASEC_CNT_U16; i++)
	{	
		 /*LRPR_MtrPos_Normalized normalized to 0-360 Electrical Degrees.*/
		LRPRMtrPosNor_rev_T_u0p16[i] = (FPM_FloatToFixed_m(LRPRMtrPosCaptured_Rev_T_f32, u0p16_T)) + 
									Read_CountToRev(LRPRPhaseAdvAdj_Cnt_T_u16) 
									+SVDiag_PhaseOffset_Rev_M_u0p16[i];
		
		/*Determination of Motor Position Sector */
		
		SVDiag_PrevLRPRHighSector_Cnt_M_lgc[i]=SVDiag_LRPRHighSector_Cnt_M_lgc[i];
		SVDiag_PrevLRPRLowSector_Cnt_M_lgc[i]=SVDiag_LRPRLowSector_Cnt_M_lgc[i];
		/*The current sector determination */
		if (( LRPRMtrPosNor_rev_T_u0p16[i] >= D_35DEG_REV_U0P16) && ( LRPRMtrPosNor_rev_T_u0p16[i] <=D_205DEG_REV_U0P16))
			{
			SVDiag_LRPRHighSector_Cnt_M_lgc[i]=TRUE;
			SVDiag_LRPRLowSector_Cnt_M_lgc[i]=FALSE;
			}
		else if(( LRPRMtrPosNor_rev_T_u0p16[i] >= D_245DEG_REV_U0P16) && ( LRPRMtrPosNor_rev_T_u0p16[i] <=D_355DEG_REV_U0P16))
			{
			SVDiag_LRPRHighSector_Cnt_M_lgc[i]=FALSE;
			SVDiag_LRPRLowSector_Cnt_M_lgc[i]=TRUE;
			}
		
		else
			{
			SVDiag_LRPRHighSector_Cnt_M_lgc[i]=FALSE;
			SVDiag_LRPRLowSector_Cnt_M_lgc[i]=FALSE;
			}
		 /*Determines the sector based high and low limits	*/
		 /* Adjust the limits if the previous and last sector has remained the same */
		 if ( (SVDiag_LowResPhsReasDisable_M_u8 < 50U) || ((TRUE == PDActivateTest_Cnt_T_lgc) && (SVDiag_LowResPhsReasDisable_M_u8 < 100U)) )
			{
			LRPRHighLimit_Cnt_T_f32= D_NHETCTSPERLRPRLOOP_CNT_F32;
			LRPRLowLimit_Cnt_T_f32= 0.0F;
			}
		else if((TRUE == SVDiag_PrevLRPRHighSector_Cnt_M_lgc[i] ) && (TRUE == SVDiag_LRPRHighSector_Cnt_M_lgc[i]))
			{
			LRPRHighLimit_Cnt_T_f32 = (Max_m(SVDiag_LRPRAdjModldAComp_Cnt_M_f32,SVDiag_PrevLRPRAdjModldComp_Cnt_M_f32) * D_NHETCTSPERLRPRLOOP_CNT_F32*k_LowResPhsReasMaxTol_Uls_f32)+SVDiag_MaxNrCommOffVltg_Cnt_M_f32;
			LRPRLowLimit_Cnt_T_f32 =(Min_m(SVDiag_LRPRAdjModldAComp_Cnt_M_f32,SVDiag_PrevLRPRAdjModldComp_Cnt_M_f32) * D_NHETCTSPERLRPRLOOP_CNT_F32*k_LowResPhsReasMinTol_Uls_f32);
			}
		else if ((TRUE == SVDiag_PrevLRPRLowSector_Cnt_M_lgc[i] ) && (TRUE == SVDiag_LRPRLowSector_Cnt_M_lgc[i]))
			{
			LRPRHighLimit_Cnt_T_f32= SVDiag_MaxNrCommOffVltg_Cnt_M_f32;
			LRPRLowLimit_Cnt_T_f32= 0.0F;
			}
		else
			{
			LRPRHighLimit_Cnt_T_f32= D_NHETCTSPERLRPRLOOP_CNT_F32;
			LRPRLowLimit_Cnt_T_f32= 0.0F;
			}
		
		/* Verify Diagnostic Run Conditions by checking if the motor position has remained within a high or low sector 
		during the previous loop*/	
		PrevPhsAdvComp_Cnt_T_s16=(sint16)SVDiag_PrevLRPRPhsAdvComp_Cnt_M_u16 - (sint16)D_PHSADVCNTS180DEG_CNT_U16 ;
		PhsAdvComp_Cnt_T_s16= (sint16)SVDiag_LRPRPhsAdvComp_Cnt_M_u16 -(sint16)D_PHSADVCNTS180DEG_CNT_U16; 
		/*.  This determination can be skipped if motor velocity is high enough to jump between sectors in 
		a diagnostic loop or when the phase advance jumps to compensate for a negative modulation index*/
		if (((Abs_f32_m(MotorVelMRFUnfilt_MtrRadpS_T_f32) < k_LRPRMtrVelDiagEnable_MtrRadpS_T_f32)) &&
		 (( Abs_s16_m(PrevPhsAdvComp_Cnt_T_s16) > D_PHSPOSADVCNTS90DEG_CNT_U16 ) 
			== (Abs_s16_m(PhsAdvComp_Cnt_T_s16) > D_PHSPOSADVCNTS90DEG_CNT_U16 )))
		{
			/* Diagnostic increment fault counter by k_LowResPhsReas_Pstep if 6.1.2.3.6.	Diagnostic Execution criteria not met*/
			if (((float32)ExpectedOnTime_Cnt_T_u32[i] > LRPRHighLimit_Cnt_T_f32 ) || ((float32)ExpectedOnTime_Cnt_T_u32[i] <
																				LRPRLowLimit_Cnt_T_f32))
			{
				SVDiag_LowPhReasErrorAcc_Cnt_M_u16 = DiagPStep_m(SVDiag_LowPhReasErrorAcc_Cnt_M_u16, k_LowResPhsReas_Cnt_str);
				SetFaultCounter_Cnt_T_lgc= FALSE;
			}
																				
			
		}
		
		SVDiag_LRPRHighLimit_Cnt_D_f32[i] = LRPRHighLimit_Cnt_T_f32;
		SVDiag_LRPRLowLimit_Cnt_D_f32[i] = LRPRLowLimit_Cnt_T_f32;	
	}
	

	if (TRUE == SetFaultCounter_Cnt_T_lgc) 
		{
		 SVDiag_LowPhReasErrorAcc_Cnt_M_u16 = DiagNStep_m(SVDiag_LowPhReasErrorAcc_Cnt_M_u16, k_LowResPhsReas_Cnt_str);
		}
	
	/*If the fault accumulator exceeds k_LowResPhsReas_Threshold then set ParamBits_Cnt_T_u08 bit6 True. Refer FDD 49A*/ 
	if (DiagFailed_m( SVDiag_LowPhReasErrorAcc_Cnt_M_u16, k_LowResPhsReas_Cnt_str) == TRUE)
		{
		ParamBits_Cnt_T_u08|= (uint8) (1U << SETDIAGRESPHSREASACTIVEBIT_U16);
		}
	
	/*Run Rte_Call_NxtrDiagMgr_SetNTCStatus with Diagnostic bits*/
	if( ParamBits_Cnt_T_u08 == D_RESETDIGDIAGACTIVE_CNT_U08 )
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_DigPhaseVoltageVerf, 0x00U, NTC_STATUS_PASSED);
		}
	else
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_DigPhaseVoltageVerf, ParamBits_Cnt_T_u08, NTC_STATUS_FAILED);
		}
	/* Configurable End of Runnable Checkpoint */
    Rte_Call_DigPhsReasDiag_Per1_CP1_CheckpointReached(); /* PRQA S 3112 */

	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigPhsReasDiag_Trans1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on entering of Mode <OPERATE> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
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

FUNC(void, RTE_AP_DIGPHSREASDIAG_APPL_CODE) DigPhsReasDiag_Trans1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigPhsReasDiag_Trans1
 *********************************************************************************************************************/
	/* Reset the delay counter */
	SVDiag_HighResPhsReasDisable_M_u8 = 0U;
	SVDiag_LowResPhsReasDisable_M_u8 = 0U;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_DIGPHSREASDIAG_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
STATIC INLINE FUNC(void, RTE_AP_DIGPHSREASDIAG_APPL_CODE) PhaseGroundTabLookupoffset(VAR(sint8, AUTOMATIC) MtrElecMechPol_Cnt_T_s08)
{
/*The implementation specific offset for each phase 
compensated for motor electromechanical polarity. */ 
	if (D_POSITIVEONE_CNT_S8 == MtrElecMechPol_Cnt_T_s08)
	{
		SVDiag_PhaseOffset_Rev_M_u0p16[D_PHASEA_CNT_U16] = D_PHASEAOFFSETNRM_REV_U0P16;
		SVDiag_PhaseOffset_Rev_M_u0p16[D_PHASEB_CNT_U16] = D_PHASEBOFFSETNRM_REV_U0P16;
		SVDiag_PhaseOffset_Rev_M_u0p16[D_PHASEC_CNT_U16] = D_PHASECOFFSETNRM_REV_U0P16;
	}
	else
	{
		SVDiag_PhaseOffset_Rev_M_u0p16[D_PHASEA_CNT_U16] = D_PHASEAOFFSETINV_REV_U0P16;
		SVDiag_PhaseOffset_Rev_M_u0p16[D_PHASEB_CNT_U16] = D_PHASEBOFFSETINV_REV_U0P16;
		SVDiag_PhaseOffset_Rev_M_u0p16[D_PHASEC_CNT_U16] = D_PHASECOFFSETINV_REV_U0P16;
	}
}


STATIC INLINE FUNC(uint16, RTE_AP_DIGPHSREASDIAG_APPL_CODE) Read_CountToRev(VAR(uint16, AUTOMATIC) Var_Cnt_T_u16)
{
  VAR(uint16, AP_DIGPHSREASDIAG_VAR)  CountToRev_Rev_T_u16;
  /*Convert Electrical degree in Count units to Rev units*/
  CountToRev_Rev_T_u16=((uint16)(((uint32)(Var_Cnt_T_u16)*D_REVPCNT_ULS_U0P32)>>D_SCALER16_CNT_U16));
  return CountToRev_Rev_T_u16;
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
