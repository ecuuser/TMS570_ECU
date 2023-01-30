/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Sa_MtrDrvDiag.c
 *     Workspace:  C:/Rijvi_Synergy/Core_Component/Working/SVDiag-jzk9cc/SVDiag/autosar
 *     SW-C Type:  Sa_MtrDrvDiag
 *  Generated at:  Mon Dec  1 14:25:06 2014
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Sa_MtrDrvDiag>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Jun 20 11:22:09 2011
 * %version:          22 %
 * %derived_by:       jzk9cc %
 * %date_modified:    Thu Oct  3 16:11:39 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/20/11  5        LWW       Replaced exclusive area with suspend and resume interrupts
 * 07/18/11  6        LWW       Added osek.h include for Suspend and Resume Interrupt definition
 * 09/26/11	 7        KJS		Updated diagnostic function calls with 9bit NTC value							4500
 * 12/02/11  8        JJW       Corrected use of Rte_Call_NxtrDiagMgr_GetEventFailed in ProcBridgeFlt
 * 12/15/11  9        LWW       Used correct enum value for GetEventFailed in ProcBridgeFlt
 * 01/13/12  10       JJW       Updated NTCs API
 * 07/29/12  11       LWW       Changes to properly set FetDrvReset pin state on warm init entry
 * 09/19/12  12       OT        Moved to Component, removed IRVs, added functionality for Hardware Power Up     6280
 * 09/28/12  13       Selva    Checkpoints added and mempmap macros corrected		                        	6382
 * 09/29/12  14       LWW       Updated to latest StdDef
 * 09/29/12  15       LWW       Removed volatile from display variable for function paramter compatibility
 * 10/26/12  16       Selva     QAC fixes added.
 * 02/19/13  17       KJS       QAC corrections. 
 * 03/15/13	 18		  SP		QAC warnings fixes
 * 04/25/13	 19		  LWW		Added Per2 per anomaly 4578
 * 09/05/13  20       Selva     A4155 fixed by removing setting FetFlt2Clk                                      10020
 * 10/03/13  21       VT        Updated module and display variables with SVDiag                                10134
 * 12/01/14  22       Rijvi     Updated the module per latest FDD rev.008; and fix anomaly 7613 and 5899        12751
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

 *********************************************************************************************************************/

#include "Rte_Sa_MtrDrvDiag.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "fixmath.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "Os.h"
#include "Sa_MtrDrvDiag_Cfg.h"

#define D_PHASEALOWER_CNT_U16				0U
#define D_PHASEBLOWER_CNT_U16				1U
#define D_PHASECLOWER_CNT_U16				2U
#define D_PHASEAUPPER_CNT_U16				3U
#define D_PHASEBUPPER_CNT_U16				4U
#define D_PHASECUPPER_CNT_U16				5U
#define D_VREGUV_CNT_U16					6U
#define D_BTSTRPAUV_CNT_U16					7U
#define D_BTSTRPBUV_CNT_U16					8U
#define D_BTSTRPCUV_CNT_U16					9U
#define D_NUMOFGDSTATUSBITS_CNT_U16			10U
#define D_STATUSALOWER_CNT_B16				0x0001U
#define D_STATUSBLOWER_CNT_B16				0x0002U
#define D_STATUSCLOWER_CNT_B16				0x0004U
#define D_STATUSAUPPER_CNT_B16				0x0008U
#define D_STATUSBUPPER_CNT_B16				0x0010U
#define D_STATUSCUPPER_CNT_B16				0x0020U
#define D_STATUSVREGUV_CNT_B16				0x0040U
#define D_STATUSBTSTRPAUV_CNT_B16			0x0080U
#define D_STATUSBTSTRPBUV_CNT_B16			0x0100U
#define D_STATUSBTSTRPCUV_CNT_B16			0x0200U
#define D_STATUSVDDUV_CNT_B16				0x0400U
#define D_STATUSOVERTEMP_CNT_B16			0x8000U
#define D_FFDATACLKTIME_US_U16P0			4U
#define D_GDRESETTIME_US_U16P0				2U
#define D_MTRDRVINITDELAY_MS_U08        	10U
#define D_GATEDRVCOMMLOSSACCTHRS_CNT_U16   	100U

#define MTRDRVDIAG_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
STATIC VAR(uint32, SA_MTRDRVDIAG_VAR_NOINIT) SVDiag_MtrDrvInitStartTime_mS_M_u32p0;

#define MTRDRVDIAG_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define MTRDRVDIAG_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, SA_MTRDRVDIAG_VAR_NOINIT) SVDiag_GateDriveFltAcc_Cnt_M_u16;
STATIC VAR(uint16, SA_MTRDRVDIAG_VAR_NOINIT) SVDiag_GenGateDriveFltAcc_Cnt_M_u16;
STATIC VAR(uint16, SA_MTRDRVDIAG_VAR_NOINIT) SVDiag_OnStateFltAcc_Cnt_M_u16;
STATIC VAR(uint16, SA_MTRDRVDIAG_VAR_NOINIT) SVDiag_GateDrvFltSts_Cnt_D_b16;
#define MTRDRVDIAG_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

#define MTRDRVDIAG_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, SA_MTRDRVDIAG_VAR_NOINIT) SVDiag_MtrDrvInitComp_Cnt_M_lgc;
STATIC VAR(boolean, SA_MTRDRVDIAG_VAR_NOINIT) SVDiag_ResetWaitLoop_Cnt_M_lgc;
STATIC VAR(boolean, SA_MTRDRVDIAG_VAR_NOINIT) SVDiag_MtrDrvInitActive_Cnt_M_lgc;

#define MTRDRVDIAG_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define MTRDRVDIAG_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(FETFAULTTYPE_ENUM, SA_MTRDRVDIAG_VAR_NOINIT) SVDiag_FETFaultType_Cnt_M_enum; 
STATIC VAR(FETPHASETYPE_ENUM, SA_MTRDRVDIAG_VAR_NOINIT) SVDiag_FETFaultPhase_Cnt_M_enum;
#define MTRDRVDIAG_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

STATIC INLINE FUNC(boolean, SA_MTRDRVDIAG_CODE) MotorDriverInit(void);

STATIC INLINE FUNC(void, SA_MTRDRVDIAG_CODE) ProcGateDriveFlt(	CONSTP2VAR(uint16, AUTOMATIC, SA_MTRDRVDIAG_CONST) GateDriveFltAccPtr_Cnt_T_u16,
																VAR(boolean, AUTOMATIC) FF2Set_Cnt_T_lgc);
																
STATIC INLINE FUNC(void, SA_MTRDRVDIAG_CODE) ProcBridgeFlt(	CONSTP2VAR(uint16, AUTOMATIC, SA_MTRDRVDIAG_CONST) OnStateFltAccPtr_Cnt_T_u16,
															CONSTP2VAR(uint16, AUTOMATIC, SA_MTRDRVDIAG_CONST) GenGateDriveFltAccPtr_Cnt_T_u16);

STATIC INLINE FUNC(uint16, SA_MTRDRVDIAG_CODE) ReadMtrDrvFltData(	CONSTP2VAR(uint16, AUTOMATIC, SA_MTRDRVDIAG_CONST) StatusPtr_Cnt_T_b16);

STATIC INLINE FUNC(void, SA_MTRDRVDIAG_CODE) ResetGateDrive(void);

STATIC INLINE FUNC(void, SA_MTRDRVDIAG_CODE) GateDrvWaitTime(	VAR(uint16, AUTOMATIC) TimeToWait_uS_T_u16p0);
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
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * FETFAULTTYPE_ENUM: Enumeration of integer in interval [0...255] with enumerators
 *   NOFAULT (0u)
 *   LOWER (1u)
 *   UPPER (2u)
 * FETPHASETYPE_ENUM: Enumeration of integer in interval [0...255] with enumerators
 *   NOPHASE (0u)
 *   PHASEA (1u)
 *   PHASEB (2u)
 *   PHASEC (3u)
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


#define RTE_START_SEC_SA_MTRDRVDIAG_APPL_CODE
#include "MemMap.h"	/* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: MtrDrvDiag_Per1
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
 *   Boolean Rte_IRead_MtrDrvDiag_Per1_MtrDrvrInitStart_Cnt_lgc(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_MtrDrvDiag_Per1_FETFaultPhase_Cnt_enum(FETPHASETYPE_ENUM data)
 *   FETPHASETYPE_ENUM *Rte_IWriteRef_MtrDrvDiag_Per1_FETFaultPhase_Cnt_enum(void)
 *   void Rte_IWrite_MtrDrvDiag_Per1_FETFaultType_Cnt_enum(FETFAULTTYPE_ENUM data)
 *   FETFAULTTYPE_ENUM *Rte_IWriteRef_MtrDrvDiag_Per1_FETFaultType_Cnt_enum(void)
 *   void Rte_IWrite_MtrDrvDiag_Per1_GateDriveResetActive_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_MtrDrvDiag_Per1_GateDriveResetActive_Cnt_lgc(void)
 *   void Rte_IWrite_MtrDrvDiag_Per1_MtrDrvrInitComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_MtrDrvDiag_Per1_MtrDrvrInitComplete_Cnt_lgc(void)
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
 *   Std_ReturnType Rte_Call_FetDrvReset_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_FetDrvReset_E_NOT_OK
 *   Std_ReturnType Rte_Call_FetFlt1Data_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_FetFlt1Data_E_NOT_OK
 *   Std_ReturnType Rte_Call_FetFlt2Clk_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_FetFlt2Clk_E_NOT_OK
 *   Std_ReturnType Rte_Call_FetFlt2Clk_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_FetFlt2Clk_E_NOT_OK
 *   Std_ReturnType Rte_Call_IoHwAbPortConfig_SetFetFlt2ToOutput(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_IoHwAbPortConfig_E_NOT_OK
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_GetNTCFailed(NTCNumber NTC_Cnt_T_enum, Boolean *NTCFailed_Ptr_T_lgc)
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
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_uS_u16(UInt32 InitialTime, UInt16 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_uS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_MTRDRVDIAG_APPL_CODE) MtrDrvDiag_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: MtrDrvDiag_Per1
 *********************************************************************************************************************/
	
	
	VAR(boolean, AUTOMATIC) MtrDrvrInitStart_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) MtrDrvInitComp_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) FF1Set_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) FF2Set_Cnt_T_lgc;
	VAR(uint16, AUTOMATIC) GateDriveFltAcc_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) GenGateDriveFltAcc_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) OnStateFltAcc_Cnt_T_u16;
	VAR(boolean, AUTOMATIC) GateDriveResetActive_Cnt_T_lgc;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_MtrDrvDiag_Per1_CP0_CheckpointReached();
	
	MtrDrvrInitStart_Cnt_T_lgc = Rte_IRead_MtrDrvDiag_Per1_MtrDrvrInitStart_Cnt_lgc();
	MtrDrvInitComp_Cnt_T_lgc = SVDiag_MtrDrvInitComp_Cnt_M_lgc;
	GateDriveFltAcc_Cnt_T_u16 = SVDiag_GateDriveFltAcc_Cnt_M_u16;
	GenGateDriveFltAcc_Cnt_T_u16 = SVDiag_GenGateDriveFltAcc_Cnt_M_u16;
	OnStateFltAcc_Cnt_T_u16 = SVDiag_OnStateFltAcc_Cnt_M_u16;
	
	
	GateDriveResetActive_Cnt_T_lgc = FALSE;
	
	if (TRUE == MtrDrvInitComp_Cnt_T_lgc)
	{
		if (TRUE == SVDiag_ResetWaitLoop_Cnt_M_lgc)
		{
			ResetGateDrive();
			SVDiag_ResetWaitLoop_Cnt_M_lgc = FALSE;
		}
		else
		{
			(void)Rte_Call_FetFlt1Data_OP_GET(&FF1Set_Cnt_T_lgc);
			(void)Rte_Call_FetFlt2Clk_OP_GET(&FF2Set_Cnt_T_lgc);
				
			if ((FALSE == FF1Set_Cnt_T_lgc) && (FALSE == FF2Set_Cnt_T_lgc))
			{
				GateDriveFltAcc_Cnt_T_u16 = DiagNStep_m(GateDriveFltAcc_Cnt_T_u16, k_GateDriveDiag_Cnt_str);
				OnStateFltAcc_Cnt_T_u16 = DiagNStep_m(OnStateFltAcc_Cnt_T_u16, k_OnStateDiag_Cnt_str);
					
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_GateDrvFlt, 0x00U, NTC_STATUS_PASSED);
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_OnStateSingleFET, 0x00U, NTC_STATUS_PASSED);
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_OnStateMultiFET, 0x00U, NTC_STATUS_PASSED);
			}
			else 
			{
			    GateDriveResetActive_Cnt_T_lgc = TRUE;
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_GateDrvFltInProcess, 0x01U, NTC_STATUS_FAILED);
				
				if (TRUE == FF1Set_Cnt_T_lgc)
				{						
					/* Gate Drive Fault Processing */
					ProcGateDriveFlt(&GateDriveFltAcc_Cnt_T_u16, FF2Set_Cnt_T_lgc);
				}
				else
				{				   
					/* Bridge Fault Processing */
					ProcBridgeFlt(&OnStateFltAcc_Cnt_T_u16, &GenGateDriveFltAcc_Cnt_T_u16);
				}
					
				if (TRUE != SVDiag_ResetWaitLoop_Cnt_M_lgc)
				{
					ResetGateDrive(); 
				}
			}
		}
	}
	else
	{
		if (TRUE == MtrDrvrInitStart_Cnt_T_lgc)
		{
			MtrDrvInitComp_Cnt_T_lgc = MotorDriverInit();
		}
	}
	
	
	Rte_IWrite_MtrDrvDiag_Per1_FETFaultPhase_Cnt_enum(SVDiag_FETFaultPhase_Cnt_M_enum);
	Rte_IWrite_MtrDrvDiag_Per1_FETFaultType_Cnt_enum(SVDiag_FETFaultType_Cnt_M_enum);
	Rte_IWrite_MtrDrvDiag_Per1_MtrDrvrInitComplete_Cnt_lgc(MtrDrvInitComp_Cnt_T_lgc);
	Rte_IWrite_MtrDrvDiag_Per1_GateDriveResetActive_Cnt_lgc(GateDriveResetActive_Cnt_T_lgc);
	SVDiag_MtrDrvInitComp_Cnt_M_lgc = MtrDrvInitComp_Cnt_T_lgc;
	SVDiag_GateDriveFltAcc_Cnt_M_u16 = GateDriveFltAcc_Cnt_T_u16;
	SVDiag_GenGateDriveFltAcc_Cnt_M_u16 = GenGateDriveFltAcc_Cnt_T_u16;
	SVDiag_OnStateFltAcc_Cnt_M_u16 = OnStateFltAcc_Cnt_T_u16;
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_MtrDrvDiag_Per1_CP1_CheckpointReached(); 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: MtrDrvDiag_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <WARMINIT, OPERATE>
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
 *   Std_ReturnType Rte_Call_FetDrvReset_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_FetDrvReset_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_MTRDRVDIAG_APPL_CODE) MtrDrvDiag_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: MtrDrvDiag_Per2
 *********************************************************************************************************************/

	(void)Rte_Call_FetDrvReset_OP_SET(STD_LOW);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: MtrDrvDiag_Trns1
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
 *   void Rte_IWrite_MtrDrvDiag_Trns1_MtrDrvrInitComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_MtrDrvDiag_Trns1_MtrDrvrInitComplete_Cnt_lgc(void)
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
 *   Std_ReturnType Rte_Call_FetDrvReset_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_FetDrvReset_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_MTRDRVDIAG_APPL_CODE) MtrDrvDiag_Trns1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: MtrDrvDiag_Trns1
 *********************************************************************************************************************/
	
	
	(void)Rte_Call_FetDrvReset_OP_SET(STD_HIGH);
	SVDiag_GateDriveFltAcc_Cnt_M_u16 = 0U;
	SVDiag_GenGateDriveFltAcc_Cnt_M_u16 = 0U;
	SVDiag_OnStateFltAcc_Cnt_M_u16 = 0U;
	SVDiag_MtrDrvInitComp_Cnt_M_lgc = FALSE;
	Rte_IWrite_MtrDrvDiag_Trns1_MtrDrvrInitComplete_Cnt_lgc(FALSE);
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_SA_MTRDRVDIAG_APPL_CODE
#include "MemMap.h"	/* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
STATIC INLINE FUNC(void, SA_MTRDRVDIAG_CODE) ProcGateDriveFlt(	CONSTP2VAR(uint16, AUTOMATIC, SA_MTRDRVDIAG_CONST) GateDriveFltAccPtr_Cnt_T_u16,
																VAR(boolean, AUTOMATIC) FF2Set_Cnt_T_lgc)
{
	
	
	*GateDriveFltAccPtr_Cnt_T_u16 = DiagPStep_m(*GateDriveFltAccPtr_Cnt_T_u16, k_GateDriveDiag_Cnt_str);
					
	if( TRUE== DiagFailed_m(*GateDriveFltAccPtr_Cnt_T_u16, k_GateDriveDiag_Cnt_str) )
	{
		
		if (FALSE == FF2Set_Cnt_T_lgc)
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_GateDrvFlt, 0x01U, NTC_STATUS_FAILED);
			SVDiag_GateDrvFltSts_Cnt_D_b16 |= D_STATUSOVERTEMP_CNT_B16;	
		}
		else
		{
		 	(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_GateDrvFlt, 0x04U, NTC_STATUS_FAILED);
		 	(void)ReadMtrDrvFltData(&SVDiag_GateDrvFltSts_Cnt_D_b16);
		}
	}
}


STATIC INLINE FUNC(void, SA_MTRDRVDIAG_CODE) ProcBridgeFlt(	CONSTP2VAR(uint16, AUTOMATIC, SA_MTRDRVDIAG_CONST) OnStateFltAccPtr_Cnt_T_u16,
															CONSTP2VAR(uint16, AUTOMATIC, SA_MTRDRVDIAG_CONST) GenGateDriveFltAccPtr_Cnt_T_u16)
{
	VAR(boolean, AUTOMATIC)  OnStateFltActive_Cnt_T_lgc;
	VAR(uint16, AUTOMATIC)   FaultedPhases_Cnt_T_u16;
	VAR(uint8, AUTOMATIC)    SingleFETFltNTCParam_Cnt_T_u08;
	
	*OnStateFltAccPtr_Cnt_T_u16 = DiagPStep_m(*OnStateFltAccPtr_Cnt_T_u16, k_OnStateDiag_Cnt_str);
	
	if (TRUE == DiagFailed_m(*OnStateFltAccPtr_Cnt_T_u16, k_OnStateDiag_Cnt_str))
	{
		(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_OnStateSingleFET, &OnStateFltActive_Cnt_T_lgc);
		
		if (TRUE == OnStateFltActive_Cnt_T_lgc) /* Multi FET fault if TRUE */
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_OnStateMultiFET, 0x01U, NTC_STATUS_FAILED);
		}
		else
		{
			FaultedPhases_Cnt_T_u16 = ReadMtrDrvFltData(&SVDiag_GateDrvFltSts_Cnt_D_b16);
			if	(FaultedPhases_Cnt_T_u16 > 1U) /* Multi FET fault if TRUE */
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_OnStateMultiFET, 0x01U, NTC_STATUS_FAILED); 
			}
			else if (FaultedPhases_Cnt_T_u16 == 1U)  /* Single FET fault if TRUE*/
			{
				SVDiag_ResetWaitLoop_Cnt_M_lgc = TRUE;
				
				/* Determine the NTC parameter for On-State single FET fault */
				SingleFETFltNTCParam_Cnt_T_u08 =   (uint8)(((uint8)(SVDiag_GateDrvFltSts_Cnt_D_b16 & 0x0001U)) << 1U ); /* Vds exceeded on A phase high-side FET */
				SingleFETFltNTCParam_Cnt_T_u08 |=  (uint8)(((uint8)(SVDiag_GateDrvFltSts_Cnt_D_b16 & 0x0002U)) << 2U ); /* Vds exceeded on B phase high-side FET */
				SingleFETFltNTCParam_Cnt_T_u08 |=  (uint8)(((uint8)(SVDiag_GateDrvFltSts_Cnt_D_b16 & 0x0004U)) << 3U ); /* Vds exceeded on C phase high-side FET */
				SingleFETFltNTCParam_Cnt_T_u08 |=  (((uint8)(SVDiag_GateDrvFltSts_Cnt_D_b16 & 0x0008U)) >> 3U ); /* Vds exceeded on A phase low-side FET */
				SingleFETFltNTCParam_Cnt_T_u08 |=  (((uint8)(SVDiag_GateDrvFltSts_Cnt_D_b16 & 0x0010U)) >> 2U ); /* Vds exceeded on B phase low-side FET */
				SingleFETFltNTCParam_Cnt_T_u08 |=  (((uint8)(SVDiag_GateDrvFltSts_Cnt_D_b16 & 0x0020U)) >> 1U ); /* Vds exceeded on C phase low-side FET */
				
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_OnStateSingleFET, SingleFETFltNTCParam_Cnt_T_u08, NTC_STATUS_FAILED);  
				*OnStateFltAccPtr_Cnt_T_u16 = 0U;
			}
			else  /* Gate Drive communication loss if TRUE*/
			{
				*OnStateFltAccPtr_Cnt_T_u16 = 0U;
				*GenGateDriveFltAccPtr_Cnt_T_u16 = *GenGateDriveFltAccPtr_Cnt_T_u16 + 1U;
				if(*GenGateDriveFltAccPtr_Cnt_T_u16 >= D_GATEDRVCOMMLOSSACCTHRS_CNT_U16)  
				{
					*GenGateDriveFltAccPtr_Cnt_T_u16 = D_GATEDRVCOMMLOSSACCTHRS_CNT_U16;  
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_GateDrvFlt, 0x02U, NTC_STATUS_FAILED);
			    }
			}
		}
	}
}



STATIC INLINE FUNC(uint16, SA_MTRDRVDIAG_CODE) ReadMtrDrvFltData(	CONSTP2VAR(uint16, AUTOMATIC, SA_MTRDRVDIAG_CONST) StatusPtr_Cnt_T_b16)
{
	VAR(FETFAULTTYPE_ENUM, AUTOMATIC) FETFaultType_Cnt_T_enum; 
	VAR(FETPHASETYPE_ENUM, AUTOMATIC) FETFaultPhase_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) FaultedPhases_Cnt_T_u16;
	VAR(boolean, AUTOMATIC) DataHigh_Cnt_T_lgc;
	VAR(uint16, AUTOMATIC) ClockBit_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) Status_Cnt_T_b16;
	
	(void)Rte_Call_IoHwAbPortConfig_SetFetFlt2ToOutput(TRUE);
	
	FaultedPhases_Cnt_T_u16 = 0U;
	Status_Cnt_T_b16 = 0U;
	FETFaultType_Cnt_T_enum = NOFAULT; 
	FETFaultPhase_Cnt_T_enum = NOPHASE;
	
	for (ClockBit_Cnt_T_u16 = 0U; ClockBit_Cnt_T_u16 < D_NUMOFGDSTATUSBITS_CNT_U16; ClockBit_Cnt_T_u16++)
	{
		(void)Rte_Call_FetFlt2Clk_OP_SET(STD_LOW);
		GateDrvWaitTime(D_FFDATACLKTIME_US_U16P0);
		
		(void)Rte_Call_FetFlt1Data_OP_GET(&DataHigh_Cnt_T_lgc);
		
		if (TRUE == DataHigh_Cnt_T_lgc)
		{
			switch(ClockBit_Cnt_T_u16)
			{
				case D_PHASEALOWER_CNT_U16:
					FaultedPhases_Cnt_T_u16++;
					FETFaultType_Cnt_T_enum = LOWER;
					FETFaultPhase_Cnt_T_enum = PHASEA;
					Status_Cnt_T_b16 |= D_STATUSALOWER_CNT_B16;
					break;
				case D_PHASEBLOWER_CNT_U16:
					FaultedPhases_Cnt_T_u16++;
					FETFaultType_Cnt_T_enum = LOWER;
					FETFaultPhase_Cnt_T_enum = PHASEB;
					Status_Cnt_T_b16 |= D_STATUSBLOWER_CNT_B16;
					break;
				case D_PHASECLOWER_CNT_U16:
					FaultedPhases_Cnt_T_u16++;
                   	FETFaultType_Cnt_T_enum = LOWER;
					FETFaultPhase_Cnt_T_enum = PHASEC;
					Status_Cnt_T_b16 |= D_STATUSCLOWER_CNT_B16;
					break;
				case D_PHASEAUPPER_CNT_U16:
					FaultedPhases_Cnt_T_u16++;
					FETFaultType_Cnt_T_enum = UPPER;
					FETFaultPhase_Cnt_T_enum = PHASEA;
					Status_Cnt_T_b16 |= D_STATUSAUPPER_CNT_B16;
					break;
				case D_PHASEBUPPER_CNT_U16:
					FaultedPhases_Cnt_T_u16++;
					FETFaultType_Cnt_T_enum = UPPER;
					FETFaultPhase_Cnt_T_enum = PHASEB;
					Status_Cnt_T_b16 |= D_STATUSBUPPER_CNT_B16;
					break;
				case D_PHASECUPPER_CNT_U16:
					FaultedPhases_Cnt_T_u16++;
					FETFaultType_Cnt_T_enum = UPPER;
					FETFaultPhase_Cnt_T_enum = PHASEC;
					Status_Cnt_T_b16 |= D_STATUSCUPPER_CNT_B16;
					break;
				case D_VREGUV_CNT_U16:
					Status_Cnt_T_b16 |= D_STATUSVREGUV_CNT_B16;
					break;
				case D_BTSTRPAUV_CNT_U16:
					Status_Cnt_T_b16 |= D_STATUSBTSTRPAUV_CNT_B16;
					break;
				case D_BTSTRPBUV_CNT_U16:
					Status_Cnt_T_b16 |= D_STATUSBTSTRPBUV_CNT_B16;
					break;
				default: /* D_BTSTRPCUV_CNT_U16 */
					Status_Cnt_T_b16 |= D_STATUSBTSTRPCUV_CNT_B16;
					break;
			}
		}
		
		(void)Rte_Call_FetFlt2Clk_OP_SET(STD_HIGH);
		GateDrvWaitTime(D_FFDATACLKTIME_US_U16P0);
	}
	
	if (0U == Status_Cnt_T_b16)
	{
		Status_Cnt_T_b16 = D_STATUSVDDUV_CNT_B16;
	}
		
	if (FaultedPhases_Cnt_T_u16 == 1U)
	{
		if (PHASEA == FETFaultPhase_Cnt_T_enum)
		{
			/* TODO: Turn NHET output to GPIO and manually set output */
		}
		else if (PHASEB == FETFaultPhase_Cnt_T_enum)
		{
			/* TODO: Turn NHET output to GPIO and manually set output */
		}
		else
		{
			/* TODO: Turn NHET output to GPIO and manually set output */
		}
	}
	
	(void)Rte_Call_IoHwAbPortConfig_SetFetFlt2ToOutput(FALSE);
	
	*StatusPtr_Cnt_T_b16 = Status_Cnt_T_b16;  
	SVDiag_FETFaultPhase_Cnt_M_enum = FETFaultPhase_Cnt_T_enum;
	SVDiag_FETFaultType_Cnt_M_enum = FETFaultType_Cnt_T_enum;
	
	return(FaultedPhases_Cnt_T_u16);
}

 /* MISRA Comment: Msg(4:3112) This statement has no side-effect - it can be removed.
MISRA-C:2004 Rule 14.2 as osek.h is just a stub so no return values or conditions specified*/ 
STATIC INLINE FUNC(void, SA_MTRDRVDIAG_CODE) ResetGateDrive(void)
{
	SuspendAllInterrupts(); /* PRQA S 3112 EOF */ /* see MISRA comment above */
				
	(void)Rte_Call_FetDrvReset_OP_SET(STD_LOW);
	GateDrvWaitTime(D_GDRESETTIME_US_U16P0);
	(void)Rte_Call_FetDrvReset_OP_SET(STD_HIGH);
	
	ResumeAllInterrupts();/* PRQA S 3112 EOF */ /* see MISRA comment above */
}

STATIC INLINE FUNC(void, SA_MTRDRVDIAG_CODE) GateDrvWaitTime(	VAR(uint16, AUTOMATIC) TimeToWait_uS_T_u16p0)
{
	VAR(uint32, AUTOMATIC) WaitStartTime_uS_T_u32p0;
	VAR(uint16, AUTOMATIC) WaitElapsedTime_uS_T_u16p0;

	(void)Rte_Call_SystemTime_GetSystemTime_uS_u32(&WaitStartTime_uS_T_u32p0);
	do 
	{
		(void)Rte_Call_SystemTime_DtrmnElapsedTime_uS_u16(WaitStartTime_uS_T_u32p0, &WaitElapsedTime_uS_T_u16p0);
	}
	while(WaitElapsedTime_uS_T_u16p0 < TimeToWait_uS_T_u16p0);
}

STATIC INLINE FUNC(boolean, SA_MTRDRVDIAG_CODE) MotorDriverInit(void)
{
	VAR(uint16, AUTOMATIC) ElapsedTime_mS_T_u16p0;
	VAR(boolean, AUTOMATIC) MtrDrvInitComp_Cnt_T_lgc;
	
	if (FALSE == SVDiag_MtrDrvInitActive_Cnt_M_lgc)
	{
		(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&SVDiag_MtrDrvInitStartTime_mS_M_u32p0);
		SVDiag_MtrDrvInitActive_Cnt_M_lgc = TRUE;
	}
	
	(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(SVDiag_MtrDrvInitStartTime_mS_M_u32p0, &ElapsedTime_mS_T_u16p0);	
	if (ElapsedTime_mS_T_u16p0  > D_MTRDRVINITDELAY_MS_U08) 
	{
		ResetGateDrive();
		MtrDrvInitComp_Cnt_T_lgc = TRUE;
		SVDiag_MtrDrvInitActive_Cnt_M_lgc = FALSE;
	}
	else
	{
		MtrDrvInitComp_Cnt_T_lgc = FALSE;
	}
	
	return(MtrDrvInitComp_Cnt_T_lgc);
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
