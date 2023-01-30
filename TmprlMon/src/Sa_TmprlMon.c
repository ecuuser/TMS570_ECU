/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Sa_TmprlMon.c
 *     Workspace:  C:/Sankar/Synergy/Working/TmprlMon-pznywf/TmprlMon/autosar
 *     SW-C Type:  Sa_TmprlMon
 *  Generated at:  Tue Jul  7 09:48:13 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Sa_TmprlMon>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Tue Mar 20 12:00:00 2012
 * %version:          16 %
 * %derived_by:       pznywf %
 * %date_modified:    Tue Jul 07 09:55:29 2015 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * -------   -------  --------  -------------------------------------------------------------------------------  ------
 * 03/22/12  1        OT        Initial Component Version
 * 03/28/12  2        JJW       MemMap constant typo correction, QAC suppression for MemMap includes,
 *                              removal of redefinitions for AUTOSAR standard types STD_LOW and STD_HIGH
 * 04/01/12  3        OT        Updated NTCStatusByte to STATIC, updated state times                             5171
 * 06/18/12  4        OT        Updated to FDD 19B v002B (added NTC parameters, changed state times)             5706
 * 07/25/12  5        OT        Changed running modes for Per3 (to avoid conflict with ShtdnMech)                5886
 * 09/19/12  6        OT        Added functionality for Hardware Power Up, removed Trns2
 * 09/27/12  7        Selva     Checkpoints added and mempmap macros corrected                                   6362
 * 09/28/12  8        NRAR      Updated to FDD Ver006a                                                           6309
 * 10/24/12  10       BWL       Fix for anomoly #3912                                                            6630
 * 10/24/12  11       BWL       Update trigger rate                                                              6630
 * 11/10/12  12       JJW       Multi-app division
 * 04/24/13  13       SP        Updated to FDD V 008 and 009                                                     7864
 * 07/26/13  15       Jared     Anomaly 5113 correction - NTC status bits incorrectly set, only on complete      9241
 *                              Anomaly 5280 correction - improper startup because NTC 0x040 set                 9242
 * 07/07/15	 16		  SV		Updated Test sequence in Warm Init to skip TMF after first run                  13474
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Operation Prototypes:
 =====================
  DtrmnElapsedTime_mS_u16 of Port Interface SystemTime
    Nexteer SystemTime Service


 Mode Declaration Groups:
 ========================
  StaMd_Mode
    EPS System State mode declaration


 Runnable Entities:
 ==================
  TmprlMon_Per1
    Periodic function intended to be placed at the beginning of the 2ms task list to create the rising edge of the WdMonitor signal.

 *********************************************************************************************************************/

#include "Rte_Sa_TmprlMon.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "CalConstants.h"
#include "GlobalMacro.h"

#define TMPMON_NUMSTATES	15U
#include "Sa_TmprlMon_Cfg.h"



typedef enum {
	TMPMON_RESET1 = 0U,  /* Step 0 */
	TMPMON_INIT_ALLOFF1, /* Step 1 */
	TMPMON_INIT_TMOFF1,  /* Step 2 */
	TMPMON_INIT_PICINIT1,/* Step 3 */
	TMPMON_INIT_SF2OFF,  /* Step 4 */
	TMPMON_INIT_ALLON2,  /* Step 5 */
	TMPMON_INIT_SF3OFF,  /* Step 6 */
	TMPMON_INIT_ALLON3,  /* Step 7 */
	TMPMON_INIT_TMOFF2,  /* Step 8 */
	TMPMON_RESET2,       /* Step 9 */
	TMPMON_INIT_ALLOFF2, /* Step 10 */
	TMPMON_INIT_SF23OFF, /* Step 11 */
	TMPMON_INIT_PICINIT2, /* Step 12 */
	TMPMON_OPERATE,      /* Step 13 */
	TMPMON_PREPCHECK		/* Step 15 */
} DT_TmprlMonSt;


typedef struct TmprlMonState{
	IoHwAb_BoolType	SysFault3Cmd_lgc;
	IoHwAb_BoolType	SysFault2Cmd_lgc;
	IoHwAb_BoolType	WdMonitorCmd_lgc;
	IoHwAb_BoolType	WdResetCmd_lgc;
	IoHwAb_BoolType	FetDrvCntlFdbk_lgc;
	IoHwAb_BoolType	PwrSwitchEnFdbk_lgc;
	uint16			StepTime_mS_u16;
} TmprlMonState_Str;


#define TMPRLMON_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC CONST(TmprlMonState_Str, SA_TMPRLMON_CONST) TmprlMonStateTbl_Cnt_M_Str[TMPMON_NUMSTATES] =
	/* State          FDD Step    SysFlt3   SysFlt2   WdMonitor  Reset   FetDrvCntl PwrSwEn  TrnstTime */
	/* RESET1       - Step 0 */ {{STD_LOW,  STD_LOW,  STD_LOW,  STD_LOW,  STD_LOW,  STD_LOW,  4U},	/* 4ms to ensure execution of one 2ms loop */
	/* INIT_ALLOFF1 - Step 1 */  {STD_LOW,  STD_LOW,  STD_LOW,  STD_HIGH, STD_LOW,  STD_LOW,  31U},
	/* INIT_TMOFF1  - Step 2 */  {STD_HIGH, STD_HIGH, STD_LOW,  STD_HIGH, STD_LOW,  STD_LOW,  1U},
	/* INIT_PICINIT1- Step 3 */  {STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, 40U},
	/* INIT_SF2OFF  - Step 4 */  {STD_HIGH, STD_LOW,  STD_HIGH, STD_HIGH, STD_LOW,  STD_LOW,  1U},
	/* INIT_ALLON2  - Step 5 */  {STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, 1U},
	/* INIT_SF3OFF  - Step 6 */  {STD_LOW,  STD_HIGH, STD_HIGH, STD_HIGH, STD_LOW,  STD_LOW,  1U},
	/* INIT_ALLON3  - Step 7 */  {STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, 1U},
	/* INIT_TMOFF2  - Step 8 */  {STD_HIGH, STD_HIGH, STD_LOW,  STD_HIGH, STD_LOW,  STD_LOW,  24U},
	/* RESET2       - Step 9 */  {STD_LOW,  STD_LOW,  STD_LOW,  STD_LOW,  STD_LOW,  STD_LOW,  1U},
	/* INIT_ALLOFF2 - Step 10 */ {STD_LOW,  STD_LOW,  STD_LOW,  STD_HIGH, STD_LOW,  STD_LOW,  31U},
	/* INIT_SF23OFF - Step 11 */ {STD_LOW,  STD_LOW,  STD_HIGH, STD_HIGH, STD_LOW,  STD_LOW,  24U},
	/* INIT_PICINIT2- Step 12 */ {STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, 16U},
	/* OPERATE      - Step 13 */ {STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, STD_HIGH, 0U}, /* SysFlt3 is high intentionally - we don't want to drive it low */
	/* PREPCHECK	- Step 15 */ {STD_LOW,  STD_LOW,  STD_LOW,  STD_LOW,  STD_HIGH, STD_LOW,  0U}};
#define TMPRLMON_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


#define TMPRLMON_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(DT_TmprlMonSt, TMPRLMON_VAR) TmprlMonSt_Cnt_M_enum;
STATIC VAR(NxtrDiagMgrStatus, TMPRLMON_VAR) InitTestStatus_Cnt_M_enum;
#define TMPRLMON_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


#define TMPRLMON_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint32, TMPRLMON_VAR) InitialTime_mS_M_u32;
#define TMPRLMON_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define TMPRLMON_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint8,  TMPRLMON_VAR) NTCStatusByte_Cnt_M_u08;
#define TMPRLMON_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */

#define TMPRLMON_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, TMPRLMON_VAR) TMFTestComplete_Cnt_M_lgc;
STATIC VAR(boolean, TMPRLMON_VAR) TMFPrepCheckFlag_Cnt_M_lgc;
#define TMPRLMON_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define TMPRLMON_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, AP_DAMPINGFIREWALL_VAR_NOINIT) TmprlMonPNAccum_Cnt_M_u16;
#define TMPRLMON_STOP_SEC_VAR_CLEARED_16
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
 *   NTC_Num_StaMdsSysC (203u)
 *   NTC_NUM_SysFailureForRotVel (204u)
 *   NTC_NUM_SysFailForRedntRotVel (205u)
 *   NTC_Num_SysFailureForTrqSnsr (206u)
 *   NTC_Num_SysFailureForRedTrqSnsr (207u)
 *   NTC_NUM_SysFailureForCtrlVolt (209u)
 *   NTC_Num_GlblSgnlOvrwrtDet (223u)
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
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_SA_TMPRLMON_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TmprlMon_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
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
 *   Std_ReturnType Rte_Call_WdMonitor_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_WdMonitor_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_TMPRLMON_APPL_CODE) TmprlMon_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TmprlMon_Per1
 *********************************************************************************************************************/
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_TmprlMon_Per1_CP0_CheckpointReached();

	(void)Rte_Call_WdMonitor_OP_SET(TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_M_enum].WdMonitorCmd_lgc);

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_TmprlMon_Per1_CP1_CheckpointReached();

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TmprlMon_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <OPERATE, OFF, DISABLE>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Boolean Rte_IRead_TmprlMon_Per2_TMFTestStart_Cnt_lgc(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_TmprlMon_Per2_TMFTestComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_TmprlMon_Per2_TMFTestComplete_Cnt_lgc(void)
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
 *   Std_ReturnType Rte_Call_FetDrvCntl_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_FetDrvCntl_E_NOT_OK
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *   Std_ReturnType Rte_Call_PwrSwitchEn_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_PwrSwitchEn_E_NOT_OK
 *   Std_ReturnType Rte_Call_SysFault2_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault2_E_NOT_OK
 *   Std_ReturnType Rte_Call_SysFault3_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault3_E_NOT_OK
 *   Std_ReturnType Rte_Call_WdReset_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_WdReset_E_NOT_OK
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

FUNC(void, RTE_SA_TMPRLMON_APPL_CODE) TmprlMon_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TmprlMon_Per2
 *********************************************************************************************************************/


	VAR(boolean, AUTOMATIC)				TMFTestStart_Cnt_T_lgc;
	VAR(DT_TmprlMonSt, AUTOMATIC)		TmprlMonSt_Cnt_T_enum;
	VAR(IoHwAb_BoolType, AUTOMATIC)		FetDrvCntlFdbk_Cnt_T_lgc;
	VAR(IoHwAb_BoolType, AUTOMATIC)		PwrSwitchEnFdbk_Cnt_T_lgc;
	VAR(uint16, AUTOMATIC)				ElapsedTime_T_mS_u16;
	VAR(IoHwAb_BoolType, AUTOMATIC)		SysFault3_Cnt_T_lgc;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_TmprlMon_Per2_CP0_CheckpointReached();

	TMFTestStart_Cnt_T_lgc = Rte_IRead_TmprlMon_Per2_TMFTestStart_Cnt_lgc();
	TmprlMonSt_Cnt_T_enum = TmprlMonSt_Cnt_M_enum; /* Local Copy for consistency */
	(void) Rte_Call_FetDrvCntl_OP_GET(&FetDrvCntlFdbk_Cnt_T_lgc);
	(void) Rte_Call_PwrSwitchEn_OP_GET(&PwrSwitchEnFdbk_Cnt_T_lgc);

	/* This changes per v008 */
	if(TMFPrepCheckFlag_Cnt_M_lgc == FALSE)
	{
		(void) Rte_Call_SystemTime_GetSystemTime_mS_u32(&InitialTime_mS_M_u32);
		(void) Rte_Call_SysFault3_OP_GET(&SysFault3_Cnt_T_lgc);
		TMFPrepCheckFlag_Cnt_M_lgc = TRUE;
		if(SysFault3_Cnt_T_lgc == FALSE)
		{
			/* DTC " TMF circuitry Init" active */
			NTCStatusByte_Cnt_M_u08 = (uint8)((TMPMON_PREPCHECK + 1U) << 4U);
			InitTestStatus_Cnt_M_enum = NTC_STATUS_FAILED;
		}
	}
	/* Temporal Monitor Control Circuit Fault */
	else if( (TmprlMonSt_Cnt_T_enum < TMPMON_OPERATE) &&
		(TMFTestStart_Cnt_T_lgc == TRUE) )
	{
		(void) Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(InitialTime_mS_M_u32, &ElapsedTime_T_mS_u16);

		if( (ElapsedTime_T_mS_u16 >= TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].StepTime_mS_u16) ||
			( ( (TmprlMonSt_Cnt_T_enum == TMPMON_INIT_PICINIT1) ||
			    (TmprlMonSt_Cnt_T_enum == TMPMON_INIT_PICINIT2) ) &&
			(TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].FetDrvCntlFdbk_lgc == FetDrvCntlFdbk_Cnt_T_lgc) &&
			  (TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].PwrSwitchEnFdbk_lgc == PwrSwitchEnFdbk_Cnt_T_lgc)))
			{
				if( (TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].FetDrvCntlFdbk_lgc != FetDrvCntlFdbk_Cnt_T_lgc) ||
						(TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].PwrSwitchEnFdbk_lgc != PwrSwitchEnFdbk_Cnt_T_lgc) )
				{
					/* Record DTC Parameter data */
					NTCStatusByte_Cnt_M_u08 = ((TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].FetDrvCntlFdbk_lgc & ((uint8)~FetDrvCntlFdbk_Cnt_T_lgc)) |
											 ((uint8)((TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].PwrSwitchEnFdbk_lgc & ((uint8)~PwrSwitchEnFdbk_Cnt_T_lgc)) << 1U)) |
											 ((uint8)((((uint8)~TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].FetDrvCntlFdbk_lgc) & FetDrvCntlFdbk_Cnt_T_lgc) << 2U)) |
											 ((uint8)((((uint8)~TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].PwrSwitchEnFdbk_lgc) & PwrSwitchEnFdbk_Cnt_T_lgc) << 3U)) ) |
											 NTCStatusByte_Cnt_M_u08;
					if (InitTestStatus_Cnt_M_enum == NTC_STATUS_PASSED)
					{
						NTCStatusByte_Cnt_M_u08 = NTCStatusByte_Cnt_M_u08 | ((uint8)((uint8)TmprlMonSt_Cnt_T_enum << 4U));
						InitTestStatus_Cnt_M_enum = NTC_STATUS_FAILED;
					}
				}
				TmprlMonSt_Cnt_T_enum++;
				TmprlMonSt_Cnt_M_enum = TmprlMonSt_Cnt_T_enum;
				(void) Rte_Call_SystemTime_GetSystemTime_mS_u32(&InitialTime_mS_M_u32);
			}

		if(TMPMON_OPERATE == TmprlMonSt_Cnt_T_enum)
		{
			TMFTestComplete_Cnt_M_lgc = TRUE;
			(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TmpMonFunc, NTCStatusByte_Cnt_M_u08, InitTestStatus_Cnt_M_enum);
		}

	}
	else
	{
		(void) Rte_Call_SystemTime_GetSystemTime_mS_u32(&InitialTime_mS_M_u32);
	}
	Rte_IWrite_TmprlMon_Per2_TMFTestComplete_Cnt_lgc(TMFTestComplete_Cnt_M_lgc);

	(void) Rte_Call_WdReset_OP_SET(TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].WdResetCmd_lgc);
	(void) Rte_Call_SysFault2_OP_SET(TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].SysFault2Cmd_lgc);
	(void) Rte_Call_SysFault3_OP_SET(TmprlMonStateTbl_Cnt_M_Str[TmprlMonSt_Cnt_T_enum].SysFault3Cmd_lgc);

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_TmprlMon_Per2_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TmprlMon_Per3
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *     and not in Mode(s) <WARMINIT, OFF>
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
 *   Std_ReturnType Rte_Call_FetDrvCntl_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_FetDrvCntl_E_NOT_OK
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *   Std_ReturnType Rte_Call_PwrSwitchEn_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_PwrSwitchEn_E_NOT_OK
 *   Std_ReturnType Rte_Call_SysFault2_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault2_E_NOT_OK
 *   Std_ReturnType Rte_Call_SysFault3_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault3_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_TMPRLMON_APPL_CODE) TmprlMon_Per3(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TmprlMon_Per3
 *********************************************************************************************************************/

	VAR(IoHwAb_BoolType, AUTOMATIC)		SysFault2_Cnt_T_lgc;
	VAR(IoHwAb_BoolType, AUTOMATIC)		SysFault3_Cnt_T_lgc;
	VAR(IoHwAb_BoolType, AUTOMATIC)		FetDrvCntl_Cnt_T_lgc;
	VAR(IoHwAb_BoolType, AUTOMATIC)		PwrSwitchEn_Cnt_T_lgc;
	VAR(NxtrDiagMgrStatus, AUTOMATIC)	NTCStatus_Cnt_T_enum;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_TmprlMon_Per3_CP0_CheckpointReached();

	(void) Rte_Call_SysFault2_OP_GET(&SysFault2_Cnt_T_lgc);
	(void) Rte_Call_SysFault3_OP_GET(&SysFault3_Cnt_T_lgc);
	(void) Rte_Call_PwrSwitchEn_OP_GET(&PwrSwitchEn_Cnt_T_lgc);
	(void) Rte_Call_FetDrvCntl_OP_GET(&FetDrvCntl_Cnt_T_lgc);


	/* TMF Run Time Control Circuit Fault */ /* This changes per v009 */

	if( (SysFault2_Cnt_T_lgc == TRUE) && (SysFault3_Cnt_T_lgc == TRUE) )
	{
		if( (PwrSwitchEn_Cnt_T_lgc == TRUE) && (FetDrvCntl_Cnt_T_lgc == TRUE) )
		{
			TmprlMonPNAccum_Cnt_M_u16 =  DiagNStep_m(TmprlMonPNAccum_Cnt_M_u16, k_TmprlMonPstepNstep_Cnt_str);
			NTCStatus_Cnt_T_enum = NTC_STATUS_PASSED;
			(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TmpMonRunTimeFlt, 0U, NTCStatus_Cnt_T_enum);
		}
		else
		{
			/* Record appropriate "Stuck Low" Status Bit(s) */
			NTCStatusByte_Cnt_M_u08 = ((uint8)(~FetDrvCntl_Cnt_T_lgc) & 0x1U) |
			                          ((uint8)(((uint8)~PwrSwitchEn_Cnt_T_lgc) << 1U) & 0x2U) |
			                          NTCStatusByte_Cnt_M_u08;
			TmprlMonPNAccum_Cnt_M_u16 =  DiagPStep_m(TmprlMonPNAccum_Cnt_M_u16, k_TmprlMonPstepNstep_Cnt_str);
			if (DiagFailed_m( TmprlMonPNAccum_Cnt_M_u16, k_TmprlMonPstepNstep_Cnt_str) == TRUE)
			{
				NTCStatus_Cnt_T_enum = NTC_STATUS_FAILED;
				(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TmpMonRunTimeFlt, NTCStatusByte_Cnt_M_u08, NTCStatus_Cnt_T_enum);
			}
		}
	}
	else
	{
		if( (PwrSwitchEn_Cnt_T_lgc == TRUE) || (FetDrvCntl_Cnt_T_lgc == TRUE) )
		{
			/* Record appropriate "Stuck High" Status Bit(s) */
			NTCStatusByte_Cnt_M_u08 = ((uint8)(((uint8)FetDrvCntl_Cnt_T_lgc) << 2U) & 0x4U) |
			                          ((uint8)(((uint8)PwrSwitchEn_Cnt_T_lgc) << 3U)& 0x8U) |
			                          NTCStatusByte_Cnt_M_u08;
			TmprlMonPNAccum_Cnt_M_u16 =  DiagPStep_m(TmprlMonPNAccum_Cnt_M_u16, k_TmprlMonPstepNstep_Cnt_str);
			if (DiagFailed_m( TmprlMonPNAccum_Cnt_M_u16, k_TmprlMonPstepNstep_Cnt_str) == TRUE)
			{
				NTCStatus_Cnt_T_enum = NTC_STATUS_FAILED;
				(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TmpMonRunTimeFlt, NTCStatusByte_Cnt_M_u08, NTCStatus_Cnt_T_enum);
			}
		}
		else
		{
			TmprlMonPNAccum_Cnt_M_u16 =  DiagNStep_m(TmprlMonPNAccum_Cnt_M_u16, k_TmprlMonPstepNstep_Cnt_str);
			NTCStatus_Cnt_T_enum = NTC_STATUS_PASSED;
			(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TmpMonRunTimeFlt, 0U, NTCStatus_Cnt_T_enum);
		}
	}

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_TmprlMon_Per3_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TmprlMon_Trns1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on entering of Mode <WARMINIT> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
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

FUNC(void, RTE_SA_TMPRLMON_APPL_CODE) TmprlMon_Trns1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TmprlMon_Trns1
 *********************************************************************************************************************/

	if (TMFTestComplete_Cnt_M_lgc == FALSE)
	{
		InitTestStatus_Cnt_M_enum = NTC_STATUS_PASSED;
		NTCStatusByte_Cnt_M_u08 = 0U;
		(void) Rte_Call_SystemTime_GetSystemTime_mS_u32(&InitialTime_mS_M_u32);
		TmprlMonSt_Cnt_M_enum = TMPMON_RESET1;
	}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TmprlMon_Trns2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on entering of Mode <DISABLE> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
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
 *   Std_ReturnType Rte_Call_SysFault2_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault2_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_TMPRLMON_APPL_CODE) TmprlMon_Trns2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TmprlMon_Trns2
 *********************************************************************************************************************/
/* Disable Gate Drive Enable and Power */
(void) Rte_Call_SysFault2_OP_SET(STD_LOW);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_SA_TMPRLMON_APPL_CODE
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
