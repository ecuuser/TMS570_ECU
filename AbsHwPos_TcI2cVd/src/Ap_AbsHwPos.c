/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_AbsHwPos.c
 *     Workspace:  C:/SynergyWorkspace/WorkingProjects/AbsHwPos_TcI2cVd-4.1/AbsHwPos_TcI2cVd/autosar
 *     SW-C Type:  Ap_AbsHwPos
 *  Generated at:  Wed Aug 27 13:48:27 2014
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_AbsHwPos>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Thu Jul 19 13:00:00 2012
 * %version:          9 %
 * %derived_by:       gzkys7 %
 * %date_modified:    Mon Nov 18 10:15:26 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                           SCR #
 * --------  -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/16/13  1        Jared     Implement ES-05G v002 as initial component                                      8493
 * 08/07/13  2        Jared     Port interface updates to StdDef                                                9564
 * 08/29/13  3        OT        Split 2ms periodic, check NvM busy before write                              9739,9926
 * 09/22/12  4        KMC       Changed constant values used for TurnsCounterValidity to fix anomaly 5641.   10216, 10217
 *                              Changed data type and constant values used for EOLHwPosTrimPerformed to fix 
 *                              anomaly 5643.  Added limits on global outputs.
 * 11/18/13  5        KMC       Changed input name TurnsCounterValidity to TurnsCntrValidity to match FDD;		9995
 *                              changed module level variable names to meet naming conventions; set authority 
 *								VdAuthority_Uls_T_f32 instead of k_VdAuthority_Uls_f32 when using Vehicle
 *                              Dynamics position; updated state variable to new position when skipping LPF
 *                              filter update; before periodic NVM write calls add check for changed value;
 *                              changed representation of SrlComHwPosStatus to match FDD data dictionary;
 *								updated "sensor invalid state" logic for fix of anomaly 5864					10858
 *                              added periodic and cold init processing of "trim not performed" diagnostic 		10871
 *                              for fix of anomaly 5863
 * 04/17/2014 6		  LK		A#6439 fix - Change line 1001 and line 1069 of Ap_AbsHwPos.c					11764
 * 05/02/2014 7		  SB		Anom 6633 fix - for CN200 project												11860
 * 07/01/14   8       BWL		Update NTC 0x75 algorithm per ES-05G v005										12156
 * 08/25/14	  9		  SB		Updated to ES-05G version 006													12367
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

#include "Rte_Ap_AbsHwPos.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_AbsHwPos_Cfg.h"

#include "CalConstants.h"
#include "GlobalMacro.h"
#include "filters.h"
#include <float.h>

/* MISRA-C:2004 Rule 8.7: Deviation required for the display variables and filter constants because of memory map */
/* MISRA-C:2004 Rule 19.1: Deviation required for the AUTOSAR Compliance */

#define D_HWPOSMAX_HWDEG_F32            1600.0f
#define D_RELHWPOSMAX_HWDEG_F32			3200.0f
#define D_INVALIDOFFSET_HWDEG_F32       ((float32)0xFFFFU)
#define D_NOAUTHORITY_ULS_F32           0.0f
#define D_MAXAUTHORITY_ULS_F32			1.0f
#define D_SRCUNKNOWN_CNT_U16            0xFFFEU
#define D_SRCTURNSCNTR_CNT_U16          0x01U
#define D_SRCI2CSENSOR_CNT_U16          0x02U
#define D_SRCSENSORLESS_CNT_U16			0x03U

#define D_HWPOSSTATUSVALID_CNT_U16      0x5555U
#define D_HWPOSSTATUSFAULT_CNT_U16      0xFFFFU
#define D_HWPOSSTATUSUNKNOWN_CNT_U16    0xFFFEU

#define D_TCVCOMPUTING_CNT_U08          0U
#define D_TCVVALID_CNT_U08              100U
#define D_TCVINVALID_CNT_U08            255U

#define D_TRIMNOTPERFORMED_CNT_U16 		0U
#define D_TRIMPERFORMED_CNT_U16 		0xAAAAU


typedef enum {
    HWPOS_STATE_INIT            = 0x08U,
    HWPOS_STATE_SENSORINVALID   = 0x04U,
    HWPOS_STATE_SENSORVALID     = 0x02U,
    HWPOS_STATE_INPUTINVALID    = 0x0EU
} HwPosStateType;


#define ABSHWPOS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(HwPosStateType, AP_ABSHWPOS_VAR) AbsHwPos_HwPosState_Cnt_M_enum;
STATIC VAR(LPF32KSV_Str, AP_ABSHWPOS_VAR) AbsHwPos_HandwheelPositionLPF_M_str;
#define ABSHWPOS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

#define ABSHWPOS_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_ABSHWPOS_VAR) AbsHwPos_VehCntrValid_Cnt_M_lgc;
STATIC VAR(boolean, AP_ABSHWPOS_VAR) AbsHwPos_VehCntrOfstLearn_Cnt_M_lgc; /* PRQA S 3218 */
STATIC VAR(boolean, AP_ABSHWPOS_VAR) AbsHwPos_MtrToHwAOfstLearnt_Cnt_M_lgc; /* PRQA S 3218 */
#define ABSHWPOS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define ABSHWPOS_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, AP_ABSHWPOS_VAR) AbsHwPos_SrlComHwPosStatus_Cnt_M_u16;
STATIC VAR(uint16, AP_ABSHWPOS_VAR) AbsHwPos_HwAtoMtrAFltAcc_Cnt_M_u16; /* PRQA S 3218 */
STATIC VAR(uint16, AP_ABSHWPOS_VAR) AbsHwPos_HwPosSource_Cnt_M_u16;
#define ABSHWPOS_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

#define ABSHWPOS_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, AP_ABSHWPOS_VAR) AbsHwPos_VehCntrOffset_HwDeg_M_f32;
STATIC VAR(float32, AP_ABSHWPOS_VAR) AbsHwPos_AlignedHwPos_HwDeg_M_f32;
STATIC VAR(float32, AP_ABSHWPOS_VAR) AbsHwPos_AlignedCumMtrPos_HwDeg_M_f32;
STATIC VAR(float32, AP_ABSHWPOS_VAR) AbsHwPos_PrevHandwheelPosition_HwDeg_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, AP_ABSHWPOS_VAR) AbsHwPos_HandwheelAuthority_Uls_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, AP_ABSHWPOS_VAR) AbsHwPos_TempHwPos_HwDeg_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, AP_ABSHWPOS_VAR) AbsHwPos_SrlComHwPos_HwDeg_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, AP_ABSHWPOS_VAR) AbsHwPos_TargetHwAuthority_Uls_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, AP_ABSHWPOS_VAR) AbsHwPos_RelHwPos_HwDeg_M_f32;
STATIC VAR(float32, AP_ABSHWPOS_VAR) AbsHwPos_MtrtoHwAOfst_HwDeg_M_f32; /* PRQA S 3218 */
#define ABSHWPOS_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

STATIC FUNC(void, AP_ABSHWPOS_CODE) TrimNotPerfDiag(VAR(ManufModeType, AUTOMATIC) ManufMode_Cnt_T_enum);

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
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * ManufModeType: Enumeration of integer in interval [0...2] with enumerators
 *   ProductionMode (0u)
 *   ManufacturingMode (1u)
 *   EngineeringMode (2u)
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
 * EOLHwPosTrimType: Record with elements
 *   EOLVehCntrOffset_HwDeg_f32 of type Float
 *   EOLHwPosTrimPerformed_Cnt_u16 of type UInt16
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
 * Float: D_ZERO_ULS_F32 = 0
 * UInt16: D_ZERO_CNT_U16 = 0u
 * UInt8: D_ZERO_CNT_U8 = 0u
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   EOLHwPosTrimType *Rte_Pim_EOLVehCntrOffset(void)
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_ABSHWPOS_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AbsHwPos_Init1
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
 *   ManufModeType Rte_IRead_AbsHwPos_Init1_ManufMode_Cnt_enum(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_AbsHwPos_Init1_HwPosSource_Cnt_u16(UInt16 data)
 *   UInt16 *Rte_IWriteRef_AbsHwPos_Init1_HwPosSource_Cnt_u16(void)
 *   void Rte_IWrite_AbsHwPos_Init1_SrlComHwPosStatus_Cnt_u16(UInt16 data)
 *   UInt16 *Rte_IWriteRef_AbsHwPos_Init1_SrlComHwPosStatus_Cnt_u16(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AbsHwPos_Init1
 *********************************************************************************************************************/

	VAR (ManufModeType, AUTOMATIC) ManufMode_Cnt_T_enum;
	
	ManufMode_Cnt_T_enum = Rte_IRead_AbsHwPos_Init1_ManufMode_Cnt_enum();
	
    if (Abs_f32_m(Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32) <= k_VehCntrOffValidLimit_HwDeg_f32)
    {
        AbsHwPos_VehCntrValid_Cnt_M_lgc = TRUE;
        AbsHwPos_VehCntrOffset_HwDeg_M_f32 = Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32;
    }
    else
    {
        AbsHwPos_VehCntrValid_Cnt_M_lgc = FALSE;
        AbsHwPos_VehCntrOffset_HwDeg_M_f32 = D_INVALIDOFFSET_HWDEG_F32;
    }

	TrimNotPerfDiag(ManufMode_Cnt_T_enum);
	
    AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_INIT;
    LPF_KUpdate_f32_m(k_HwPosOutputLPFCoeffFc_Hz_f32, D_2MS_SEC_F32, &AbsHwPos_HandwheelPositionLPF_M_str);
	
	AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSUNKNOWN_CNT_U16;
	AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCUNKNOWN_CNT_U16;
	Rte_IWrite_AbsHwPos_Init1_SrlComHwPosStatus_Cnt_u16 (AbsHwPos_SrlComHwPosStatus_Cnt_M_u16);
	Rte_IWrite_AbsHwPos_Init1_HwPosSource_Cnt_u16 (AbsHwPos_HwPosSource_Cnt_M_u16);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AbsHwPos_Per1
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
 *   Float Rte_IRead_AbsHwPos_Per1_AlignedCumMechMtrPosCRF_Deg_f32(void)
 *   Float Rte_IRead_AbsHwPos_Per1_ComplError_HwDeg_f32(void)
 *   Float Rte_IRead_AbsHwPos_Per1_CumMechMtrPosCRF_Deg_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_AbsHwPos_Per1_RelHwPos_HwDeg_f32(Float data)
 *   Float *Rte_IWriteRef_AbsHwPos_Per1_RelHwPos_HwDeg_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AbsHwPos_Per1
 *********************************************************************************************************************/
	
    VAR(float32, AUTOMATIC) AlignedCumMechMtrPosCRF_Deg_T_f32;
    VAR(float32, AUTOMATIC) ComplError_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) CumMechMtrPosCRF_Deg_T_f32;
	VAR(float32, AUTOMATIC) RelHwPosLimited_HwDeg_T_f32;
	
	
    /* Configurable Start of Runnable Checkpoint */
    Rte_Call_AbsHwPos_Per1_CP0_CheckpointReached();
	
	
    /*** Store inputs to local copies ***/
    AlignedCumMechMtrPosCRF_Deg_T_f32 = Rte_IRead_AbsHwPos_Per1_AlignedCumMechMtrPosCRF_Deg_f32();
    ComplError_HwDeg_T_f32 = Rte_IRead_AbsHwPos_Per1_ComplError_HwDeg_f32();
    CumMechMtrPosCRF_Deg_T_f32 = Rte_IRead_AbsHwPos_Per1_CumMechMtrPosCRF_Deg_f32();
	
    /*** Scale and Compensate Mtr Pos Signals used in Calculation ***/
    AbsHwPos_AlignedCumMtrPos_HwDeg_M_f32 = (AlignedCumMechMtrPosCRF_Deg_T_f32 * k_GearRatio_Uls_f32) - ComplError_HwDeg_T_f32;
    AbsHwPos_RelHwPos_HwDeg_M_f32 = (CumMechMtrPosCRF_Deg_T_f32 * k_GearRatio_Uls_f32) - ComplError_HwDeg_T_f32;
	
	/*** Limit and write global output ***/
	RelHwPosLimited_HwDeg_T_f32 = Limit_m(AbsHwPos_RelHwPos_HwDeg_M_f32, -D_RELHWPOSMAX_HWDEG_F32, D_RELHWPOSMAX_HWDEG_F32);
    Rte_IWrite_AbsHwPos_Per1_RelHwPos_HwDeg_f32(RelHwPosLimited_HwDeg_T_f32);
	
    /* Configurable End of Runnable Checkpoint */
    Rte_Call_AbsHwPos_Per1_CP1_CheckpointReached();
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AbsHwPos_Per2
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
 *   Boolean Rte_IRead_AbsHwPos_Per2_DiagStatusHwPosReducedPerf_Cnt_lgc(void)
 *   Boolean Rte_IRead_AbsHwPos_Per2_I2CHwAbsPosValid_Cnt_lgc(void)
 *   Float Rte_IRead_AbsHwPos_Per2_I2CHwAbsPos_HwDeg_f32(void)
 *   ManufModeType Rte_IRead_AbsHwPos_Per2_ManufMode_Cnt_enum(void)
 *   Float Rte_IRead_AbsHwPos_Per2_SensorlessAuthority_Uls_f32(void)
 *   Float Rte_IRead_AbsHwPos_Per2_SensorlessHwPos_HwDeg_f32(void)
 *   UInt8 Rte_IRead_AbsHwPos_Per2_TurnsCntrValidity_Cnt_u08(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_AbsHwPos_Per2_HandwheelAuthority_Uls_f32(Float data)
 *   Float *Rte_IWriteRef_AbsHwPos_Per2_HandwheelAuthority_Uls_f32(void)
 *   void Rte_IWrite_AbsHwPos_Per2_HandwheelPosition_HwDeg_f32(Float data)
 *   Float *Rte_IWriteRef_AbsHwPos_Per2_HandwheelPosition_HwDeg_f32(void)
 *   void Rte_IWrite_AbsHwPos_Per2_HwPosSource_Cnt_u16(UInt16 data)
 *   UInt16 *Rte_IWriteRef_AbsHwPos_Per2_HwPosSource_Cnt_u16(void)
 *   void Rte_IWrite_AbsHwPos_Per2_SrlComHwPosStatus_Cnt_u16(UInt16 data)
 *   UInt16 *Rte_IWriteRef_AbsHwPos_Per2_SrlComHwPosStatus_Cnt_u16(void)
 *   void Rte_IWrite_AbsHwPos_Per2_SrlComHwPos_HwDeg_f32(Float data)
 *   Float *Rte_IWriteRef_AbsHwPos_Per2_SrlComHwPos_HwDeg_f32(void)
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_EOLVehCntrOffset_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_EOLVehCntrOffset_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLVehCntrOffset_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AbsHwPos_Per2
 *********************************************************************************************************************/
	
	
    VAR(boolean, AUTOMATIC) DiagStatusHwPosReducedPerf_Cnt_T_lgc;
    VAR(boolean, AUTOMATIC) I2CHwAbsPosValid_Cnt_T_lgc;
    VAR(float32, AUTOMATIC) I2CHwAbsPos_HwDeg_T_f32;
    VAR(uint8,   AUTOMATIC) TurnsCntrValidity_Cnt_T_u08;
    VAR(float32, AUTOMATIC) SnsrlessAuthority_Uls_T_f32;
    VAR(float32, AUTOMATIC) SnsrlessHwPos_HwDeg_T_f32;
	
	VAR(NvM_RequestResultType, AUTOMATIC) NvMStatus_Cnt_T_enum;
    VAR(float32, AUTOMATIC) HandwheelPosition_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) VehCntrOffset_HwDeg_T_f32;
	
	VAR(float32, AUTOMATIC) HandwheelAuthorityLimited_Uls_T_f32;
	VAR(float32, AUTOMATIC) SrlComHwPosLimited_HwDeg_T_f32;
	
	VAR(ManufModeType, AUTOMATIC) ManufMode_Cnt_T_enum;
	
    /* Configurable Start of Runnable Checkpoint */
    Rte_Call_AbsHwPos_Per2_CP0_CheckpointReached();
	
	
    DiagStatusHwPosReducedPerf_Cnt_T_lgc = Rte_IRead_AbsHwPos_Per2_DiagStatusHwPosReducedPerf_Cnt_lgc();
    I2CHwAbsPosValid_Cnt_T_lgc = Rte_IRead_AbsHwPos_Per2_I2CHwAbsPosValid_Cnt_lgc();
    I2CHwAbsPos_HwDeg_T_f32 = Rte_IRead_AbsHwPos_Per2_I2CHwAbsPos_HwDeg_f32();
    TurnsCntrValidity_Cnt_T_u08 = Rte_IRead_AbsHwPos_Per2_TurnsCntrValidity_Cnt_u08();
    SnsrlessAuthority_Uls_T_f32 = Rte_IRead_AbsHwPos_Per2_SensorlessAuthority_Uls_f32();
    SnsrlessHwPos_HwDeg_T_f32 = Rte_IRead_AbsHwPos_Per2_SensorlessHwPos_HwDeg_f32();
	ManufMode_Cnt_T_enum = Rte_IRead_AbsHwPos_Per2_ManufMode_Cnt_enum();
	
    if ( (DiagStatusHwPosReducedPerf_Cnt_T_lgc == TRUE) ||
         (AbsHwPos_HwPosState_Cnt_M_enum == HWPOS_STATE_INPUTINVALID) )
    {
        /*-----[ Input Invalid State ]------------------------------------------------------------------------*/
        if (DiagStatusHwPosReducedPerf_Cnt_T_lgc == TRUE)
        {
            /* ES-05G v002 - Section 5.1.2.2.4 - Column 1 */
            AbsHwPos_SrlComHwPos_HwDeg_M_f32 = 0.0f;
            AbsHwPos_TargetHwAuthority_Uls_M_f32 = D_NOAUTHORITY_ULS_F32;
            AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSFAULT_CNT_U16;
            AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_INPUTINVALID;
            AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCUNKNOWN_CNT_U16;
        }
        else
        {
            /* ES-05G v002 - Section 5.1.2.2.4 - Column 2 */
            AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_INIT;
        }
    }
    else if (AbsHwPos_HwPosState_Cnt_M_enum == HWPOS_STATE_INIT)
    {
        /*-----[ Init State ]---------------------------------------------------------------------------------*/
        if (k_UseTurnsCntr_Cnt_lgc == TRUE)
        {
            if (TurnsCntrValidity_Cnt_T_u08 == D_TCVCOMPUTING_CNT_U08)
            {
                /* ES-05G v002 - Section 5.1.2.2.1 - Column 1 */
                AbsHwPos_TargetHwAuthority_Uls_M_f32 = D_NOAUTHORITY_ULS_F32;
                AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSUNKNOWN_CNT_U16;
                AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCUNKNOWN_CNT_U16;
            }
            else if (TurnsCntrValidity_Cnt_T_u08 == D_TCVVALID_CNT_U08)
            {
                if (AbsHwPos_VehCntrValid_Cnt_M_lgc == TRUE)
                {
                    /* ES-05G v002 - Section 5.1.2.2.1 - Column 5 */
                    AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_SENSORVALID;
                    AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCTURNSCNTR_CNT_U16;
                    AbsHwPos_TempHwPos_HwDeg_M_f32 = AbsHwPos_AlignedCumMtrPos_HwDeg_M_f32 - AbsHwPos_VehCntrOffset_HwDeg_M_f32;
                    AbsHwPos_SrlComHwPos_HwDeg_M_f32 = AbsHwPos_TempHwPos_HwDeg_M_f32;
                    AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSVALID_CNT_U16;
                    AbsHwPos_TargetHwAuthority_Uls_M_f32 = k_TurnsCntrAuthority_Uls_f32;
                }
                else
                {
                    /* ES-05G v002 - Section 5.1.2.2.1 - Column 4 */
                    AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_SENSORVALID;
                    AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSUNKNOWN_CNT_U16;
                    AbsHwPos_TargetHwAuthority_Uls_M_f32 = D_NOAUTHORITY_ULS_F32;
                    AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCUNKNOWN_CNT_U16;
                }
            }
            else
            {
                /* ES-05G v002 - Section 5.1.2.2.1 - Column 3 */
                AbsHwPos_TargetHwAuthority_Uls_M_f32 = D_NOAUTHORITY_ULS_F32;
                AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_SENSORINVALID;
                AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSUNKNOWN_CNT_U16;
                AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCUNKNOWN_CNT_U16;
            }
        }
        else
        {
            if (I2CHwAbsPosValid_Cnt_T_lgc == TRUE)
            {
                /* ES-05G v002 - Section 5.1.2.2.1 - Column 2 */
                AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_SENSORVALID;
                AbsHwPos_TempHwPos_HwDeg_M_f32 = I2CHwAbsPos_HwDeg_T_f32;
                AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCI2CSENSOR_CNT_U16;
                AbsHwPos_SrlComHwPos_HwDeg_M_f32 = AbsHwPos_TempHwPos_HwDeg_M_f32;
                AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSVALID_CNT_U16;
                AbsHwPos_TargetHwAuthority_Uls_M_f32 = k_I2CHwAuthority_Uls_f32;
            }
            else
            {
                /* ES-05G v002 - Section 5.1.2.2.1 - Column 3 (Duplicate) */
                AbsHwPos_TargetHwAuthority_Uls_M_f32 = D_NOAUTHORITY_ULS_F32;
                AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_SENSORINVALID;
                AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSUNKNOWN_CNT_U16;
                AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCUNKNOWN_CNT_U16;
            }
        }
    }
    else if (AbsHwPos_HwPosState_Cnt_M_enum == HWPOS_STATE_SENSORVALID)
    {
        /*-----[ Sensor Valid State ]-------------------------------------------------------------------------*/
        if (k_UseTurnsCntr_Cnt_lgc == FALSE)
        {
            if (I2CHwAbsPosValid_Cnt_T_lgc == TRUE)
            {
                /* ES-05G v002 - Section 5.1.2.2.3 - Column 1 */
                AbsHwPos_TempHwPos_HwDeg_M_f32 = I2CHwAbsPos_HwDeg_T_f32;
                AbsHwPos_TargetHwAuthority_Uls_M_f32 = k_I2CHwAuthority_Uls_f32;
                AbsHwPos_SrlComHwPos_HwDeg_M_f32 = AbsHwPos_TempHwPos_HwDeg_M_f32;
                AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSVALID_CNT_U16;
                AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCI2CSENSOR_CNT_U16;
            }
            else
            {
                /* ES-05G v002 - Section 5.1.2.2.3 - Column 2 */
                AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_SENSORINVALID;
                AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSUNKNOWN_CNT_U16;
            }
        }
        else
        {
            if (TurnsCntrValidity_Cnt_T_u08 == D_TCVVALID_CNT_U08)
            {
                if (AbsHwPos_VehCntrValid_Cnt_M_lgc == TRUE)
                {
                    /* ES-05G v002 - Section 5.1.2.2.3 - Column 5 Top */
                    AbsHwPos_TempHwPos_HwDeg_M_f32 = AbsHwPos_AlignedCumMtrPos_HwDeg_M_f32 - AbsHwPos_VehCntrOffset_HwDeg_M_f32;
                    AbsHwPos_TargetHwAuthority_Uls_M_f32 = k_TurnsCntrAuthority_Uls_f32;
                    AbsHwPos_SrlComHwPos_HwDeg_M_f32 = AbsHwPos_TempHwPos_HwDeg_M_f32;
                    AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSVALID_CNT_U16;
                    AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCTURNSCNTR_CNT_U16;
					
                    if (SnsrlessAuthority_Uls_T_f32 >= k_MaxSensorlessAuthority_Uls_f32)
                    {
                        /* ES-05G v002 - Section 5.1.2.2.3 - Column 5 Bottom Left */
                        AbsHwPos_VehCntrOfstLearn_Cnt_M_lgc = TRUE;
                    }
                    else
                    {
                        /* ES-05G v002 - Section 5.1.2.2.3 - Column 5 Bottom Right */
                        AbsHwPos_VehCntrOfstLearn_Cnt_M_lgc = FALSE;
                    }
                }
                else
                {
                    if (SnsrlessAuthority_Uls_T_f32 >= k_MinSensorlessAuthority_Uls_f32)
                    {
                        /* ES-05G v002 - Section 5.1.2.2.3 - Column 4 Top */
                        AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSVALID_CNT_U16;
                        AbsHwPos_TempHwPos_HwDeg_M_f32 = SnsrlessHwPos_HwDeg_T_f32;
                        AbsHwPos_TargetHwAuthority_Uls_M_f32 = SnsrlessAuthority_Uls_T_f32;

                        AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCSENSORLESS_CNT_U16;
						
                        if (SnsrlessAuthority_Uls_T_f32 >= k_MaxSensorlessAuthority_Uls_f32)
                        {
                            /* ES-05G v002 - Section 5.1.2.2.3 - Column 4 Bottom Left */
                            AbsHwPos_VehCntrOfstLearn_Cnt_M_lgc = TRUE;
                        }
                        else
                        {
                            /* ES-05G v002 - Section 5.1.2.2.3 - Column 4 Bottom Right */
                            AbsHwPos_VehCntrOfstLearn_Cnt_M_lgc = FALSE;
                        }
                    }
                    else
                    {
                        /* ES-05G v002 - Section 5.1.2.2.3 - Column 3 */
                        AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSUNKNOWN_CNT_U16;
                        AbsHwPos_TargetHwAuthority_Uls_M_f32 = D_NOAUTHORITY_ULS_F32;

                    }
                }
            }
            else
            {
                /* ES-05G v002 - Section 5.1.2.2.3 - Column 2 (Duplicate) */
                AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_SENSORINVALID;
                AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSUNKNOWN_CNT_U16;
            }
        }
    }
    else if (AbsHwPos_HwPosState_Cnt_M_enum == HWPOS_STATE_SENSORINVALID)
    {
        /*-----[ Sensor Invalid State ]-----------------------------------------------------------------------*/
        if ( (k_UseTurnsCntr_Cnt_lgc == FALSE) &&
             (I2CHwAbsPosValid_Cnt_T_lgc == TRUE) )
        {
            /* ES-05G v002 - Section 5.1.2.2.2 - Column 1 */
            AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_SENSORVALID;
            AbsHwPos_TempHwPos_HwDeg_M_f32 = I2CHwAbsPos_HwDeg_T_f32;
            AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCI2CSENSOR_CNT_U16;
            AbsHwPos_SrlComHwPos_HwDeg_M_f32 = AbsHwPos_TempHwPos_HwDeg_M_f32;
            AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSVALID_CNT_U16;
            AbsHwPos_TargetHwAuthority_Uls_M_f32 = k_I2CHwAuthority_Uls_f32;
        }
        else
        {
            if (k_UseTurnsCntr_Cnt_lgc == TRUE)
            {
                /* ES-05G v002 - Section 5.1.2.2.2 - Column 2 Top */
				AbsHwPos_VehCntrOfstLearn_Cnt_M_lgc = FALSE;
                AbsHwPos_VehCntrOffset_HwDeg_M_f32 = D_INVALIDOFFSET_HWDEG_F32;
				/* QAC/MISRA does not allow == or != comparison on floats so check for difference >= FLT_EPSILON */
				/* Because D_INVALIDOFFSET_HWDEG is assigned to the variables (not calculated) they WILL be     */
				/* exactly equal when the assignment has been done and the difference will be 0.0f              */
				if ((Abs_f32_m(Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32 - D_INVALIDOFFSET_HWDEG_F32)) >= FLT_EPSILON)
				{
					(void)Rte_Call_EOLVehCntrOffset_GetErrorStatus(&NvMStatus_Cnt_T_enum);
					if( NvMStatus_Cnt_T_enum != NVM_REQ_PENDING )
					{
						Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32 = AbsHwPos_VehCntrOffset_HwDeg_M_f32;
						(void)Rte_Call_EOLVehCntrOffset_WriteBlock(NULL_PTR);
					}
				}
                AbsHwPos_VehCntrValid_Cnt_M_lgc = FALSE;
            }
			
            if (SnsrlessAuthority_Uls_T_f32 >= k_MinSensorlessAuthority_Uls_f32)
            {
                /* ES-05G v002 - Section 5.1.2.2.2 - Column 3 */
                AbsHwPos_TargetHwAuthority_Uls_M_f32 = SnsrlessAuthority_Uls_T_f32;
                AbsHwPos_TempHwPos_HwDeg_M_f32 = SnsrlessHwPos_HwDeg_T_f32;
                AbsHwPos_SrlComHwPos_HwDeg_M_f32 = AbsHwPos_TempHwPos_HwDeg_M_f32;
                AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSVALID_CNT_U16;
                AbsHwPos_HwPosSource_Cnt_M_u16 = D_SRCSENSORLESS_CNT_U16;

            }
            else
            {
                /* ES-05G v002 - Section 5.1.2.2.2 - Column 2 Bottom */
                AbsHwPos_TargetHwAuthority_Uls_M_f32 = D_NOAUTHORITY_ULS_F32;
                AbsHwPos_SrlComHwPosStatus_Cnt_M_u16 = D_HWPOSSTATUSUNKNOWN_CNT_U16;
			}
        }
    }
    else
    {
        AbsHwPos_HwPosState_Cnt_M_enum = HWPOS_STATE_INPUTINVALID;
    }
	
	
    /*** Calculate and Update VehCntr_Offset in EEPROM (used with Turns Counter Only) ***/
    if (AbsHwPos_VehCntrOfstLearn_Cnt_M_lgc == TRUE)
    {
        VehCntrOffset_HwDeg_T_f32 = AbsHwPos_AlignedCumMtrPos_HwDeg_M_f32 - SnsrlessHwPos_HwDeg_T_f32;
		
        if (Abs_f32_m(VehCntrOffset_HwDeg_T_f32) <= k_VehCntrOffValidLimit_HwDeg_f32)
        {
            AbsHwPos_VehCntrValid_Cnt_M_lgc = TRUE;
            AbsHwPos_VehCntrOffset_HwDeg_M_f32 = VehCntrOffset_HwDeg_T_f32;
			
			(void)Rte_Call_EOLVehCntrOffset_GetErrorStatus(&NvMStatus_Cnt_T_enum);
            if( (Abs_f32_m(Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32 - AbsHwPos_VehCntrOffset_HwDeg_M_f32) > k_MaxVehCntrOffDiff_HwDeg_f32) &&
				(NvMStatus_Cnt_T_enum != NVM_REQ_PENDING) )
            {
                Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32 = AbsHwPos_VehCntrOffset_HwDeg_M_f32;
                (void)Rte_Call_EOLVehCntrOffset_WriteBlock(NULL_PTR);
            }
        }
        else
        {
			/* QAC/MISRA does not allow == or != comparison on floats so check for difference >= FLT_EPSILON */
			/* Because D_INVALIDOFFSET_HWDEG is assigned to the variable (not calculated) they WILL be      */
			/* exactly equal when the assignment has been done and the difference will be 0.0f              */
            if ((Abs_f32_m(Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32 - D_INVALIDOFFSET_HWDEG_F32)) >= FLT_EPSILON)
			{
				(void)Rte_Call_EOLVehCntrOffset_GetErrorStatus(&NvMStatus_Cnt_T_enum);
				if( NvMStatus_Cnt_T_enum != NVM_REQ_PENDING )
				{
					Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32 = D_INVALIDOFFSET_HWDEG_F32;
					(void)Rte_Call_EOLVehCntrOffset_WriteBlock(NULL_PTR);
				}
				AbsHwPos_VehCntrValid_Cnt_M_lgc = FALSE;
			}
		}
    }
	
	
    /*** Output Smoothing Low Pass Filter ***/
	
    if (Abs_f32_m(AbsHwPos_TempHwPos_HwDeg_M_f32 - AbsHwPos_PrevHandwheelPosition_HwDeg_M_f32) >= k_HwPosOutputLPFError_HwDeg_f32)
    {
        HandwheelPosition_HwDeg_T_f32 = LPF_OpUpdate_f32_m(AbsHwPos_TempHwPos_HwDeg_M_f32, &AbsHwPos_HandwheelPositionLPF_M_str);
    }
    else
    {
        HandwheelPosition_HwDeg_T_f32 = AbsHwPos_TempHwPos_HwDeg_M_f32;
		AbsHwPos_HandwheelPositionLPF_M_str.SV_Uls_f32 = AbsHwPos_TempHwPos_HwDeg_M_f32;
    }
	
    /*** Handwheel Position Authority Calculation ***/
    AbsHwPos_HandwheelAuthority_Uls_M_f32 = Limit_m(AbsHwPos_TargetHwAuthority_Uls_M_f32,
                                           AbsHwPos_HandwheelAuthority_Uls_M_f32 - k_HwPosAuthorityStep_Uls_f32,
                                           AbsHwPos_HandwheelAuthority_Uls_M_f32 + k_HwPosAuthorityStep_Uls_f32);
	
    /* NOTE: AbsHwPos_AlignedHwPos_HwDeg_M_f32 "subfunction output" should not be limited */
    AbsHwPos_AlignedHwPos_HwDeg_M_f32 = AbsHwPos_RelHwPos_HwDeg_M_f32;
    AbsHwPos_PrevHandwheelPosition_HwDeg_M_f32 = HandwheelPosition_HwDeg_T_f32;
	
	/*** Limit global output values ***/
	HandwheelAuthorityLimited_Uls_T_f32 = Limit_m(AbsHwPos_HandwheelAuthority_Uls_M_f32, D_NOAUTHORITY_ULS_F32, D_MAXAUTHORITY_ULS_F32);
	HandwheelPosition_HwDeg_T_f32 = Limit_m(HandwheelPosition_HwDeg_T_f32, -D_HWPOSMAX_HWDEG_F32, D_HWPOSMAX_HWDEG_F32);
	SrlComHwPosLimited_HwDeg_T_f32 = Limit_m(AbsHwPos_SrlComHwPos_HwDeg_M_f32, -D_HWPOSMAX_HWDEG_F32, D_HWPOSMAX_HWDEG_F32);
	
	/*** HW Angle Not Trimmed Diagnostic Sub-function ***/
	TrimNotPerfDiag(ManufMode_Cnt_T_enum);

    /*** Store local copies to outputs ***/
    Rte_IWrite_AbsHwPos_Per2_HandwheelAuthority_Uls_f32(HandwheelAuthorityLimited_Uls_T_f32);
    Rte_IWrite_AbsHwPos_Per2_HandwheelPosition_HwDeg_f32(HandwheelPosition_HwDeg_T_f32);
    Rte_IWrite_AbsHwPos_Per2_HwPosSource_Cnt_u16(AbsHwPos_HwPosSource_Cnt_M_u16);
    Rte_IWrite_AbsHwPos_Per2_SrlComHwPosStatus_Cnt_u16(AbsHwPos_SrlComHwPosStatus_Cnt_M_u16);
    Rte_IWrite_AbsHwPos_Per2_SrlComHwPos_HwDeg_f32(SrlComHwPosLimited_HwDeg_T_f32);
	
	
    /* Configurable End of Runnable Checkpoint */
    Rte_Call_AbsHwPos_Per2_CP1_CheckpointReached();
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AbsHwPos_Per3
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 4ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Boolean Rte_IRead_AbsHwPos_Per3_I2CHwAbsPosValid_Cnt_lgc(void)
 *   Float Rte_IRead_AbsHwPos_Per3_I2CHwAbsPos_HwDeg_f32(void)
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

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_Per3(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AbsHwPos_Per3
 *********************************************************************************************************************/
    
    /* Temporary Variable Declarations */
    VAR(boolean, AUTOMATIC) I2CHwAbsPosValid_Cnt_T_lgc;
    VAR(float32, AUTOMATIC) I2CHwAbsPos_HwDeg_T_f32;
	VAR(float32, AUTOMATIC) NewRelHwPos_HwDeg_T_f32;
	
	/* Configurable Start of Runnable Checkpoint */
    Rte_Call_AbsHwPos_Per3_CP0_CheckpointReached();
	
    /* Read inputs to local copies */
    I2CHwAbsPosValid_Cnt_T_lgc = Rte_IRead_AbsHwPos_Per3_I2CHwAbsPosValid_Cnt_lgc();
    I2CHwAbsPos_HwDeg_T_f32 = Rte_IRead_AbsHwPos_Per3_I2CHwAbsPos_HwDeg_f32();
	
    /* Sub Function: HWA to Motor Angle Correlation Diagnostic */
    if (I2CHwAbsPosValid_Cnt_T_lgc == TRUE)
    {
        if(FALSE == AbsHwPos_MtrToHwAOfstLearnt_Cnt_M_lgc)
		{
			AbsHwPos_MtrtoHwAOfst_HwDeg_M_f32 = AbsHwPos_RelHwPos_HwDeg_M_f32 - I2CHwAbsPos_HwDeg_T_f32;
			AbsHwPos_MtrToHwAOfstLearnt_Cnt_M_lgc = TRUE;
		}
		NewRelHwPos_HwDeg_T_f32 = AbsHwPos_RelHwPos_HwDeg_M_f32 - AbsHwPos_MtrtoHwAOfst_HwDeg_M_f32;
		
		if (Abs_f32_m(I2CHwAbsPos_HwDeg_T_f32 - NewRelHwPos_HwDeg_T_f32) >= k_HWAtoMtrADiffLimit_HwDeg_f32)
        {
            AbsHwPos_HwAtoMtrAFltAcc_Cnt_M_u16 = DiagPStep_m(AbsHwPos_HwAtoMtrAFltAcc_Cnt_M_u16, k_HwAtoMtrAError_str);
			
            if (DiagFailed_m(AbsHwPos_HwAtoMtrAFltAcc_Cnt_M_u16, k_HwAtoMtrAError_str) == TRUE)
            {
                (void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_HWAtoMtrAngleCorr, 1U, NTC_STATUS_FAILED);
            }
        }
        else
        {
            AbsHwPos_HwAtoMtrAFltAcc_Cnt_M_u16 = DiagNStep_m(AbsHwPos_HwAtoMtrAFltAcc_Cnt_M_u16, k_HwAtoMtrAError_str);
			
            if (AbsHwPos_HwAtoMtrAFltAcc_Cnt_M_u16 == 0U)
            {
                (void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_HWAtoMtrAngleCorr, 0U, NTC_STATUS_PASSED);
            }
        }
    }
    else
    {
        AbsHwPos_HwAtoMtrAFltAcc_Cnt_M_u16 = 0U;
		AbsHwPos_MtrToHwAOfstLearnt_Cnt_M_lgc = FALSE;
    }
	
	
    /* Configurable End of Runnable Checkpoint */
    Rte_Call_AbsHwPos_Per3_CP1_CheckpointReached();
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AbsHwPos_Per4
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
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

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_Per4(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AbsHwPos_Per4
 *********************************************************************************************************************/
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_AbsHwPos_Per4_CP0_CheckpointReached();
	
    /* Sub-Function: Kinematic Integrity Diagnostic */
    if (Abs_f32_m(AbsHwPos_AlignedHwPos_HwDeg_M_f32) > k_KinmIntDiagMaxRackLimit_HwDeg_f32)
    {
        (void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_KinematicIntDiag, 1U, NTC_STATUS_FAILED);
    }
    else
    {
        (void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_KinematicIntDiag, 0U, NTC_STATUS_PASSED);
    }
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_AbsHwPos_Per4_CP1_CheckpointReached();
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AbsHwPos_SCom_CustClrTrim
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <CustClrTrim> of PortPrototype <AbsHwPos_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_ManufMode_Cnt_enum(ManufModeType *data)
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
 *   Std_ReturnType Rte_Call_EOLVehCntrOffset_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLVehCntrOffset_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void AbsHwPos_SCom_CustClrTrim(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_SCom_CustClrTrim(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AbsHwPos_SCom_CustClrTrim
 *********************************************************************************************************************/

    VAR(ManufModeType, AUTOMATIC) ManufMode_Cnt_T_enum;

    (void)Rte_Read_ManufMode_Cnt_enum(&ManufMode_Cnt_T_enum);

    AbsHwPos_VehCntrOffset_HwDeg_M_f32 = D_INVALIDOFFSET_HWDEG_F32;
    Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32 = AbsHwPos_VehCntrOffset_HwDeg_M_f32;
    Rte_Pim_EOLVehCntrOffset()->EOLHwPosTrimPerformed_Cnt_u16 = D_TRIMNOTPERFORMED_CNT_U16;
    (void)Rte_Call_EOLVehCntrOffset_WriteBlock(NULL_PTR);
    AbsHwPos_VehCntrValid_Cnt_M_lgc = FALSE;

	TrimNotPerfDiag(ManufMode_Cnt_T_enum);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AbsHwPos_SCom_CustSetTrim
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <CustSetTrim> of PortPrototype <AbsHwPos_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_ManufMode_Cnt_enum(ManufModeType *data)
 *   Std_ReturnType Rte_Read_TurnsCntrValidity_Cnt_u08(UInt8 *data)
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
 *   Std_ReturnType Rte_Call_EOLVehCntrOffset_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLVehCntrOffset_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType AbsHwPos_SCom_CustSetTrim(void)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_AbsHwPos_SCom_TrimNotPerformed
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_SCom_CustSetTrim(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AbsHwPos_SCom_CustSetTrim (returns application error)
 *********************************************************************************************************************/

    VAR(uint8, AUTOMATIC) TurnsCntrValidity_Cnt_T_u08;
    VAR(ManufModeType, AUTOMATIC) ManufMode_Cnt_T_enum;
    VAR(Std_ReturnType, AUTOMATIC) RespCode_Cnt_T_u08 = 0U;

    (void)Rte_Read_ManufMode_Cnt_enum(&ManufMode_Cnt_T_enum);
    (void)Rte_Read_TurnsCntrValidity_Cnt_u08(&TurnsCntrValidity_Cnt_T_u08);

    AbsHwPos_VehCntrValid_Cnt_M_lgc = FALSE;

    if (TurnsCntrValidity_Cnt_T_u08 == D_TCVVALID_CNT_U08)
    {
        if (Abs_f32_m(AbsHwPos_AlignedCumMtrPos_HwDeg_M_f32) <= k_VehCntrOffValidLimit_HwDeg_f32)
        {
            AbsHwPos_VehCntrOffset_HwDeg_M_f32 = AbsHwPos_AlignedCumMtrPos_HwDeg_M_f32;
            Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32 = AbsHwPos_VehCntrOffset_HwDeg_M_f32;
            Rte_Pim_EOLVehCntrOffset()->EOLHwPosTrimPerformed_Cnt_u16 = D_TRIMPERFORMED_CNT_U16;
            AbsHwPos_VehCntrValid_Cnt_M_lgc = TRUE;
        }
    }
    else
    {
        RespCode_Cnt_T_u08 = RTE_E_AbsHwPos_SCom_TrimNotPerformed;
    }

    if (AbsHwPos_VehCntrValid_Cnt_M_lgc == FALSE)
    {
        AbsHwPos_VehCntrOffset_HwDeg_M_f32 = D_INVALIDOFFSET_HWDEG_F32;
        Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32 = AbsHwPos_VehCntrOffset_HwDeg_M_f32;
        Rte_Pim_EOLVehCntrOffset()->EOLHwPosTrimPerformed_Cnt_u16 = D_TRIMNOTPERFORMED_CNT_U16;
    }

    (void)Rte_Call_EOLVehCntrOffset_WriteBlock(NULL_PTR);

	TrimNotPerfDiag(ManufMode_Cnt_T_enum);
	
    return RespCode_Cnt_T_u08;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AbsHwPos_SCom_NxtClearTrim
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <NxtClearTrim> of PortPrototype <AbsHwPos_SCom>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_EOLVehCntrOffset_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLVehCntrOffset_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void AbsHwPos_SCom_NxtClearTrim(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_SCom_NxtClearTrim(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AbsHwPos_SCom_NxtClearTrim
 *********************************************************************************************************************/

    AbsHwPos_VehCntrOffset_HwDeg_M_f32 = D_INVALIDOFFSET_HWDEG_F32;
    Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32 = AbsHwPos_VehCntrOffset_HwDeg_M_f32;
    (void)Rte_Call_EOLVehCntrOffset_WriteBlock(NULL_PTR);
    AbsHwPos_VehCntrValid_Cnt_M_lgc = FALSE;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AbsHwPos_SCom_NxtSetTrim
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <NxtSetTrim> of PortPrototype <AbsHwPos_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_TurnsCntrValidity_Cnt_u08(UInt8 *data)
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_EOLVehCntrOffset_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLVehCntrOffset_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType AbsHwPos_SCom_NxtSetTrim(Float Offset_HwDeg_T_f32)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_AbsHwPos_SCom_TrimNotPerformed
 *   RTE_E_AbsHwPos_SCom_ValueNotAccepted
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_ABSHWPOS_APPL_CODE) AbsHwPos_SCom_NxtSetTrim(Float Offset_HwDeg_T_f32)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AbsHwPos_SCom_NxtSetTrim (returns application error)
 *********************************************************************************************************************/

    VAR(uint8, AUTOMATIC) TurnsCntrValidity_Cnt_T_u08;
    VAR(Std_ReturnType, AUTOMATIC) RespCode_Cnt_T_u08 = 0U;
    VAR(float32, AUTOMATIC) TmpOffset_HwDeg_T_f32;

    (void)Rte_Read_TurnsCntrValidity_Cnt_u08(&TurnsCntrValidity_Cnt_T_u08);

    if (TurnsCntrValidity_Cnt_T_u08 == D_TCVVALID_CNT_U08)
    {
        TmpOffset_HwDeg_T_f32 = AbsHwPos_AlignedCumMtrPos_HwDeg_M_f32 - Offset_HwDeg_T_f32;

        if (Abs_f32_m(TmpOffset_HwDeg_T_f32) <= k_VehCntrOffValidLimit_HwDeg_f32)
        {
            AbsHwPos_VehCntrOffset_HwDeg_M_f32 = TmpOffset_HwDeg_T_f32;
            Rte_Pim_EOLVehCntrOffset()->EOLVehCntrOffset_HwDeg_f32 = AbsHwPos_VehCntrOffset_HwDeg_M_f32;
            (void)Rte_Call_EOLVehCntrOffset_WriteBlock(NULL_PTR);
            AbsHwPos_VehCntrValid_Cnt_M_lgc = TRUE;
        }
        else
        {
            RespCode_Cnt_T_u08 = RTE_E_AbsHwPos_SCom_ValueNotAccepted;
        }

    }
    else
    {
        RespCode_Cnt_T_u08 = RTE_E_AbsHwPos_SCom_TrimNotPerformed;
    }

    return RespCode_Cnt_T_u08;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_ABSHWPOS_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
STATIC FUNC(void, AP_ABSHWPOS_CODE) TrimNotPerfDiag(VAR(ManufModeType, AUTOMATIC) ManufMode_Cnt_T_enum)
{
	if(k_UseTurnsCntr_Cnt_lgc == TRUE)
	{
	
		if ( (ManufMode_Cnt_T_enum != ManufacturingMode) &&
			 (Rte_Pim_EOLVehCntrOffset()->EOLHwPosTrimPerformed_Cnt_u16 != D_TRIMPERFORMED_CNT_U16) )
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_HWASensorNotTrimmed, 1U, NTC_STATUS_FAILED);
		}
		else
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_HWASensorNotTrimmed, 0U, NTC_STATUS_PASSED);
		}
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
