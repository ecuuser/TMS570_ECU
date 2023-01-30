/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_VehDyn.c
 *     Workspace:  C:/SynergyEA3/Working/VehDyn/autosar
 *     SW-C Type:  Ap_VehDyn
 *  Generated at:  Wed Dec 16 12:52:31 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_VehDyn>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/******************************************************************************
 * Copyright 2014 Nexteer
 * Nexteer Confidential
 *
 * Module File Name: VehDyn.c
 * Module Description: Implementation of SF42
 * Project           : CBD
 * Author            : Kathleen Creager
*****************************************************************************
 * Version Control:
 * %version:          EA3#11 %
 * %derived_by:       nzx5jd %
 *---------------------------------------------------------------------------------------------------------------------
 * Date        Rev      Author         Change Description                                                        SCR #
 * -------     -------  --------  ---------------------------------------------------------------------------  ----------
 * 15-Aug-13     1      KMC         Component creation.                                                          9609
 * 11-Sep-13     2      KMC         Updated value of D_VDHWPOSMAX_HWDEG_F32 per FDD data dictionary update       9866
 * 14-Aug-14     3      SB          Implemented SF-42 VCDMotPos rev 002                                          12237
 * 31-Oct-14     4      SB          Implemented SF-42 VCDMotPos rev 003; Fixed Anom 7392                         12657
 * 20-Jan-15     5      SB          Implemented SF-42 VCDMotPos rev 004                                          12903
 * 02-Feb-15     6      SB          Implemented SF-42 VCDMotPos rev 005                                          12977
 * 31-Mar-15     7      JWJ         Added ForceCenter SCom function                                              13192
 * 13-Aug-15     8      JK          Updated to SF-42 VCDMotPos rev 006                                        EA3#2016
 * 13-Nov-15     9      SB          Updated to SF-42 VCDMotPos rev 007                                        EA3#4564
 * 11-Dec-15     10     SB          Updated to SF-42 VCDMotPos FDD rev 7.1.0,                                 EA3#5174
 *                                  module was split into functions to reduce path count                                
 * 06-Jan-16     11     OT          Corrected D_MAXAUTHORITY_ULS_F32 definition                               EA3#5474 
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


 Operation Prototypes:
 =====================
  DtrmnElapsedTime_mS_u16 of Port Interface SystemTime
    Nexteer SystemTime Service


 Mode Declaration Groups:
 ========================
  StaMd_Mode
    EPS System State mode declaration

 *********************************************************************************************************************/

#include "Rte_Ap_VehDyn.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "CalConstants.h"
#include "GlobalMacro.h"
#include "filters.h"
#include "fixmath.h"
#include "SystemTime.h"
#include <float.h>

/* MISRA-C:2004 Rule 8.7: Deviation required for the display variables and filter constants because of memory map */
/* MISRA-C:2004 Rule 19.1: Deviation required for the AUTOSAR Compliance */

#define D_QUARTERREV_MTRREV_F32         0.25F
#define D_THREEQUARTERREV_MTRREV_F32    0.75F
#define D_HALFREV_MTRREV_F32            0.5F
#define D_ONEREV_MTRDEGPERMTRREV_F32    360.0F 
#define D_FCENTROFFSCON_CNT_U08         D_ONE_CNT_U8
#define D_SRLCON_CNT_U08                D_TWO_CNT_U08
#define D_VEHDYNCON_CNT_U08             D_THREE_CNT_U08
#define D_TRVLEXCLSNCON_CNT_U08         D_FOUR_CNT_U08
#define D_LASTPOSNCON_CNT_U08           5U
#define D_HWPOSMIN_HWDEG_F32            (-1600.0F)
#define D_HWPOSMAX_HWDEG_F32            1600.0F
#define D_NOAUTHORITY_ULS_F32           D_ZERO_ULS_F32
#define D_MAXAUTHORITY_ULS_F32          1.0F

typedef struct {
    VAR(float32, AUTOMATIC) MtrVel_MtrRadpS_f32;
    VAR(float32, AUTOMATIC) VehSpd_kph_f32;
    VAR(float32, AUTOMATIC) FiltPinTrq_HwNm_f32;
    VAR(float32, AUTOMATIC) CntrWindow_HwDeg_f32;
    VAR(uint16,  AUTOMATIC) Timer1Thresh_mS_u16;
    VAR(uint16,  AUTOMATIC) Timer2Thresh_mS_u16;
    VAR(uint32,  AUTOMATIC) Timer1_mS_u32;
    VAR(uint32,  AUTOMATIC) Timer2_mS_u32;
    VAR(LPF32KSV_Str, AUTOMATIC) RelHwPosFilt1SV_HwDeg_str;
    VAR(LPF32KSV_Str, AUTOMATIC) RelHwPosFilt2SV_HwDeg_str;
    VAR(boolean, AUTOMATIC) Filter1Enable_Cnt_lgc;
    VAR(boolean, AUTOMATIC) Filter2Enable_Cnt_lgc;
    VAR(boolean, AUTOMATIC) Filter1Initialized_Cnt_lgc;
    VAR(boolean, AUTOMATIC) Filter2Initialized_Cnt_lgc;
}AUTOCNTRTYPE_Str;

#define VEHDYN_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint8, AP_VEHDYN_VAR) VehDyn_SelnCaseSt_Cnt_M_u08;                   /* PRQA S 3218 */
#define VEHDYN_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */

#define VEHDYN_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, AP_VEHDYN_VAR) VehDyn_SLPHwPos_HwDeg_M_f32;
STATIC VAR(float32, AP_VEHDYN_VAR) VehDyn_SLPHwAuth_Uls_M_f32;
STATIC VAR(float32, AP_VEHDYN_VAR) VehDyn_MinOffset_HwDeg_M_f32;                /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_VEHDYN_VAR) VehDyn_MinAbsHwPos_HwDeg_D_f32;     /* PRQA S 3218 */
STATIC VAR(float32, AP_VEHDYN_VAR) VehDyn_MaxOffset_HwDeg_M_f32;                /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_VEHDYN_VAR) VehDyn_MaxAbsHwPos_HwDeg_D_f32;     /* PRQA S 3218 */

STATIC volatile VAR(float32, AP_VEHDYN_VAR) VehDyn_RelSLPHwPos_HwDeg_D_f32;     /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_VEHDYN_VAR) VehDyn_TravelXCHwPos_HwDeg_D_f32;   /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_VEHDYN_VAR) VehDyn_TravelXCHwAuth_Uls_D_f32;    /* PRQA S 3218 */

STATIC VAR(float32, AP_VEHDYN_VAR) VehDyn_ForceCenterOffset_HwDeg_M_f32;
STATIC VAR(float32, AP_VEHDYN_VAR) VehDyn_PrevLearnedHwPos_HwDeg_M_f32;             /* PRQA S 3218 */
STATIC VAR(uint32, AP_VEHDYN_VAR) VehDyn_SrlHwAgVldTimer_mS_M_u32;                  /* PRQA S 3218 */ 
STATIC VAR(float32, AP_VEHDYN_VAR) VehDyn_TravelXCHwPos_HwDeg_M_f32;
STATIC VAR(float32, AP_VEHDYN_VAR) VehDyn_TravelXCHwAuth_Uls_M_f32;             
STATIC VAR(float32, AP_VEHDYN_VAR) VehDyn_SnsrlessHwAuth_Uls_M_f32; 
#define VEHDYN_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define VEHDYN_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(LPF32KSV_Str, AP_VEHDYN_VAR) VehDyn_PinTrqSV_M_str;
STATIC VAR(AUTOCNTRTYPE_Str, AP_VEHDYN_VAR) VehDyn_AutoCntrLoSpd_M_str;
STATIC VAR(AUTOCNTRTYPE_Str, AP_VEHDYN_VAR) VehDyn_AutoCntrDetSpd_M_str;
STATIC VAR(AUTOCNTRTYPE_Str, AP_VEHDYN_VAR) VehDyn_AutoCntrHiSpd_M_str;
#define VEHDYN_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

#define VEHDYN_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_VEHDYN_VAR) VehDyn_AllowHiSpdAutoCntr_Cnt_M_lgc;         /* PRQA S 3218 */
STATIC VAR(boolean, AP_VEHDYN_VAR) VehDyn_LoSpdLearnt_Cnt_M_lgc;                /* PRQA S 3218 */
STATIC VAR(boolean, AP_VEHDYN_VAR) VehDyn_HiSpdLearnt_Cnt_M_lgc;                /* PRQA S 3218 */
STATIC VAR(boolean, AP_VEHDYN_VAR) VehDyn_Initialize_Cnt_M_lgc;                 /* PRQA S 3218 */
STATIC VAR(boolean, AP_VEHDYN_VAR) VehDyn_ForceCenterEnabled_Cnt_M_lgc;         
STATIC VAR(boolean, AP_VEHDYN_VAR) VehDyn_SelnCaseSwitch_Cnt_M_lgc;                 
#define VEHDYN_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

STATIC INLINE FUNC(float32, AP_VEHDYN_CODE) Autocenter_f32( VAR(float32, AUTOMATIC) FiltPinTrq_HwNm_T_f32,
															VAR(float32, AUTOMATIC) MotorVelCRF_MtrRadpS_T_f32,
															VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32,
															VAR(boolean, AUTOMATIC) VehSpdValid_Cnt_T_lgc,
															VAR(float32, AUTOMATIC) RelHwPos_HwDeg_T_f32,
															P2VAR(AUTOCNTRTYPE_Str, AUTOMATIC, AUTOMATIC) AutoCntr_Cnt_T_str);

STATIC FUNC(void, AP_VEHDYN_CODE) TrvlExclsn(VAR(float32, AUTOMATIC) CwEOTPosition_HwDeg_T_f32, 
											 VAR(float32, AUTOMATIC) CcwEOTPosition_HwDeg_T_f32,                                                 
											 VAR(float32, AUTOMATIC) RelHwPos_HwDeg_T_f32);
                                                 
STATIC FUNC(float32, AP_VEHDYN_CODE) Arbn_f32(VAR(float32, AUTOMATIC) RelHwPos_HwDeg_T_f32,
											  VAR(boolean, AUTOMATIC) SrlHwAgVldMdfy_Cnt_T_lgc,
											  VAR(float32, AUTOMATIC) SrlHwAg_HwDeg_T_f32,
											  VAR(float32, AUTOMATIC) VDHwPos_HwDeg_T_f32,
											  VAR(float32, AUTOMATIC) VDAuthority_Uls_T_f32,
											  VAR(float32, AUTOMATIC) RelSLPHwPos_HwDeg_T_f32);

STATIC FUNC(float32, AP_VEHDYN_CODE) SmoothHwPos_f32(VAR(float32, AUTOMATIC) LearnedHwPos_HwDeg_T_f32);
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
 * VehDyn_DataType: Record with elements
 *   NVMStoredLastPos_HwDeg_f32 of type Float
 *   NVMStoredLastPosValid_Cnt_lgc of type Boolean
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
 * Float: D_CCWEOTINIT_HWDEG_F32 = -360
 * Float: D_CWEOTINIT_HWDEG_F32 = 360
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_ZERO_ULS_F32 = 0
 * UInt8: D_FOUR_CNT_U08 = 4u
 * UInt8: D_ONE_CNT_U8 = 1u
 * UInt8: D_THREE_CNT_U08 = 3u
 * UInt8: D_TWO_CNT_U08 = 2u
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   VehDyn_DataType *Rte_Pim_MotPosReset(void)
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_VEHDYN_APPL_CODE
#include "MemMap.h"/* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehDyn_Init1
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
 *   Float Rte_IRead_VehDyn_Init1_RelHwPos_HwDeg_f32(void)
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
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_GetNTCActive(NTCNumber NTC_Cnt_T_enum, Boolean *NTCActive_Ptr_T_lgc)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: VehDyn_Init1
 *********************************************************************************************************************/

    VAR(uint32, AUTOMATIC) StartTime_mS_T_u32;
    VAR(LPF32KSV_Str, AUTOMATIC) LPFSV_Cnt_T_Str;
    VAR(boolean, AUTOMATIC) FaultBFActive_Cnt_T_lgc;

    /* read global inputs */

    (void)Rte_Call_NxtrDiagMgr_GetNTCActive(NTC_Num_EEPROMCloseFailed, &FaultBFActive_Cnt_T_lgc);

    /* Initialize Pinion Torque Low Pass Filter */
    LPF_KUpdate_f32_m(k_AutoCntrPinTrqLPFCoeffKn_Hz_f32, D_2MS_SEC_F32, &VehDyn_PinTrqSV_M_str);

    /* Initialize Timers */
    GetSystemTime_mS_u32(&StartTime_mS_T_u32);

    /* Initialize Autocentering Structures */
    VehDyn_AutoCntrLoSpd_M_str.MtrVel_MtrRadpS_f32  = k_AutoCntrLoSpdTimer1MtrVel_MtrRadpS_f32;
    VehDyn_AutoCntrLoSpd_M_str.VehSpd_kph_f32       = k_AutoCntrLoSpdTimer1VehSpd_kph_f32;
    VehDyn_AutoCntrLoSpd_M_str.FiltPinTrq_HwNm_f32  = k_AutoCntrLoSpdTimer1PinTrq_HwNm_f32;
    VehDyn_AutoCntrLoSpd_M_str.CntrWindow_HwDeg_f32 = k_AutoCntrLoSpdCntrWindow_HwDeg_f32;
    VehDyn_AutoCntrLoSpd_M_str.Timer1Thresh_mS_u16  = k_AutoCntrLoSpdTimer1_mS_u16;
    VehDyn_AutoCntrLoSpd_M_str.Timer2Thresh_mS_u16  = k_AutoCntrLoSpdTimer2_mS_u16;
    LPF_KUpdate_f32_m(k_AutoCntrLoSpdFilt1Kn_Hz_f32, D_2MS_SEC_F32, &LPFSV_Cnt_T_Str);
    VehDyn_AutoCntrLoSpd_M_str.RelHwPosFilt1SV_HwDeg_str = LPFSV_Cnt_T_Str;
    LPF_KUpdate_f32_m(k_AutoCntrLoSpdFilt2Kn_Hz_f32, D_2MS_SEC_F32, &LPFSV_Cnt_T_Str);
    VehDyn_AutoCntrLoSpd_M_str.RelHwPosFilt2SV_HwDeg_str = LPFSV_Cnt_T_Str;
    VehDyn_AutoCntrLoSpd_M_str.Timer1_mS_u32        = StartTime_mS_T_u32;
    VehDyn_AutoCntrLoSpd_M_str.Timer2_mS_u32        = StartTime_mS_T_u32;

    VehDyn_AutoCntrDetSpd_M_str.MtrVel_MtrRadpS_f32  = k_AutoCntrHiSpdTimer4MtrVel_MtrRadpS_f32;
    VehDyn_AutoCntrDetSpd_M_str.VehSpd_kph_f32       = k_AutoCntrHiSpdTimer4VehSpd_kph_f32;
    VehDyn_AutoCntrDetSpd_M_str.FiltPinTrq_HwNm_f32  = k_AutoCntrHiSpdTimer4PinTrq_HwNm_f32;
    VehDyn_AutoCntrDetSpd_M_str.CntrWindow_HwDeg_f32 = k_AutoCntrHiSpdTimer4CntrWindow_HwDeg_f32;
    VehDyn_AutoCntrDetSpd_M_str.Timer1Thresh_mS_u16  = k_AutoCntrHiSpdTimer1_mS_u16;
    VehDyn_AutoCntrDetSpd_M_str.Timer2Thresh_mS_u16  = k_AutoCntrHiSpdTimer4_mS_u16;
    LPF_KUpdate_f32_m(k_AutoCntrLoSpdFilt1Kn_Hz_f32, D_2MS_SEC_F32, &LPFSV_Cnt_T_Str);
    VehDyn_AutoCntrDetSpd_M_str.RelHwPosFilt1SV_HwDeg_str = LPFSV_Cnt_T_Str;
    LPF_KUpdate_f32_m(k_AutoCntrLoSpdFilt2Kn_Hz_f32, D_2MS_SEC_F32, &LPFSV_Cnt_T_Str);
    VehDyn_AutoCntrDetSpd_M_str.RelHwPosFilt2SV_HwDeg_str = LPFSV_Cnt_T_Str;
    VehDyn_AutoCntrDetSpd_M_str.Timer1_mS_u32        = StartTime_mS_T_u32;
    VehDyn_AutoCntrDetSpd_M_str.Timer2_mS_u32        = StartTime_mS_T_u32;

    VehDyn_AutoCntrHiSpd_M_str.MtrVel_MtrRadpS_f32  = k_AutoCntrHiSpdTimer1MtrVel_MtrRadpS_f32;
    VehDyn_AutoCntrHiSpd_M_str.VehSpd_kph_f32       = k_AutoCntrHiSpdTimer1VehSpd_kph_f32;
    VehDyn_AutoCntrHiSpd_M_str.FiltPinTrq_HwNm_f32  = k_AutoCntrHiSpdTimer1PinTrq_HwNm_f32;
    VehDyn_AutoCntrHiSpd_M_str.CntrWindow_HwDeg_f32 = k_AutoCntrHiSpdCntrWindow_HwDeg_f32;
    VehDyn_AutoCntrHiSpd_M_str.Timer1Thresh_mS_u16  = k_AutoCntrHiSpdTimer1_mS_u16;
    VehDyn_AutoCntrHiSpd_M_str.Timer2Thresh_mS_u16  = k_AutoCntrHiSpdTimer2_mS_u16;
    LPF_KUpdate_f32_m(k_AutoCntrHiSpdFilt1Kn_Hz_f32, D_2MS_SEC_F32, &LPFSV_Cnt_T_Str);
    VehDyn_AutoCntrHiSpd_M_str.RelHwPosFilt1SV_HwDeg_str = LPFSV_Cnt_T_Str;
    LPF_KUpdate_f32_m(k_AutoCntrHiSpdFilt2Kn_Hz_f32, D_2MS_SEC_F32, &LPFSV_Cnt_T_Str);
    VehDyn_AutoCntrHiSpd_M_str.RelHwPosFilt2SV_HwDeg_str = LPFSV_Cnt_T_Str;
    VehDyn_AutoCntrHiSpd_M_str.Timer1_mS_u32        = StartTime_mS_T_u32;
    VehDyn_AutoCntrHiSpd_M_str.Timer2_mS_u32        = StartTime_mS_T_u32;


    /* Stored Last Position & Authority */
    if (((Rte_Pim_MotPosReset()->NVMStoredLastPosValid_Cnt_lgc) == TRUE) && (((FaultBFActive_Cnt_T_lgc & k_SLPEnableBFCheck_Cnt_lgc) == FALSE)))
    {
        VehDyn_SLPHwPos_HwDeg_M_f32 = Rte_Pim_MotPosReset()->NVMStoredLastPos_HwDeg_f32;
        VehDyn_SLPHwAuth_Uls_M_f32 = k_SLPHwAuthority_Uls_f32;
    }
    else
    {
        VehDyn_SLPHwPos_HwDeg_M_f32 = D_ZERO_ULS_F32;
        VehDyn_SLPHwAuth_Uls_M_f32 = D_NOAUTHORITY_ULS_F32;
    }


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehDyn_Per1
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
 *   Float Rte_IRead_VehDyn_Per1_CcwEOT_HwDeg_f32(void)
 *   Float Rte_IRead_VehDyn_Per1_CwEOT_HwDeg_f32(void)
 *   Float Rte_IRead_VehDyn_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_VehDyn_Per1_MotorVelCRF_MtrRadpS_f32(void)
 *   Float Rte_IRead_VehDyn_Per1_RelHwPos_HwDeg_f32(void)
 *   Boolean Rte_IRead_VehDyn_Per1_SrlHwAgVld_Cnt_lgc(void)
 *   Float Rte_IRead_VehDyn_Per1_SrlHwAg_HwDeg_f32(void)
 *   Float Rte_IRead_VehDyn_Per1_TorqueCmdCRF_MtrNm_f32(void)
 *   Boolean Rte_IRead_VehDyn_Per1_VehicleSpeedValid_Cnt_lgc(void)
 *   Float Rte_IRead_VehDyn_Per1_VehicleSpeed_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_VehDyn_Per1_SensorlessAuthority_Uls_f32(Float data)
 *   Float *Rte_IWriteRef_VehDyn_Per1_SensorlessAuthority_Uls_f32(void)
 *   void Rte_IWrite_VehDyn_Per1_SensorlessHwPos_HwDeg_f32(Float data)
 *   Float *Rte_IWriteRef_VehDyn_Per1_SensorlessHwPos_HwDeg_f32(void)
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
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(UInt32 InitialTime, UInt32 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: VehDyn_Per1
 *********************************************************************************************************************/
    VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;
    VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32;
    VAR(float32, AUTOMATIC) TorqueCmdCRF_MtrNm_T_f32;
    VAR(boolean, AUTOMATIC) VehicleSpeedValid_Cnt_T_lgc;
    VAR(float32, AUTOMATIC) MotorVelCRF_MtrRadpS_T_f32;
    VAR(float32, AUTOMATIC) RelSLPHwPos_HwDeg_T_f32;

    VAR(float32, AUTOMATIC) VDHwPos_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) VDAuthority_Uls_T_f32;

    VAR(float32, AUTOMATIC) PinionTrq_HwNm_T_f32;
    VAR(float32, AUTOMATIC) FiltPinionTrq_HwNm_T_f32;
    VAR(float32, AUTOMATIC) VDHiSpdHwPos_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) VDLoSpdHwPos_HwDeg_T_f32; 

    VAR(float32, AUTOMATIC) CwEOTPosition_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) CcwEOTPosition_HwDeg_T_f32;

    VAR(float32, AUTOMATIC) SnsrlessHwPos_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) RelHwPos_HwDeg_T_f32;

    VAR(float32, AUTOMATIC) SrlHwAg_HwDeg_T_f32;
    VAR(boolean, AUTOMATIC) SrlHwAgVld_Cnt_T_lgc;
    VAR(float32, AUTOMATIC) AbsHwTorque_HwNm_T_f32;
    VAR(float32, AUTOMATIC) LearnedHwPos_HwDeg_T_f32;
    VAR(uint32,  AUTOMATIC) ElapsedTime_mS_T_u32;
    VAR(boolean, AUTOMATIC) SrlHwAgVldMdfy_Cnt_T_lgc;
    
    /* read global inputs */
    VehicleSpeed_Kph_T_f32 = Rte_IRead_VehDyn_Per1_VehicleSpeed_Kph_f32();
    HwTorque_HwNm_T_f32 = Rte_IRead_VehDyn_Per1_HwTorque_HwNm_f32();
    TorqueCmdCRF_MtrNm_T_f32 = Rte_IRead_VehDyn_Per1_TorqueCmdCRF_MtrNm_f32();
    VehicleSpeedValid_Cnt_T_lgc = Rte_IRead_VehDyn_Per1_VehicleSpeedValid_Cnt_lgc();
    MotorVelCRF_MtrRadpS_T_f32 = Rte_IRead_VehDyn_Per1_MotorVelCRF_MtrRadpS_f32();
    RelHwPos_HwDeg_T_f32 = Rte_IRead_VehDyn_Per1_RelHwPos_HwDeg_f32();
    CwEOTPosition_HwDeg_T_f32 = Rte_IRead_VehDyn_Per1_CwEOT_HwDeg_f32();
    CcwEOTPosition_HwDeg_T_f32 = Rte_IRead_VehDyn_Per1_CcwEOT_HwDeg_f32();
    SrlHwAgVld_Cnt_T_lgc = Rte_IRead_VehDyn_Per1_SrlHwAgVld_Cnt_lgc();
    SrlHwAg_HwDeg_T_f32 = Rte_IRead_VehDyn_Per1_SrlHwAg_HwDeg_f32();
    /* code never follows a path where a garbage value gets assigned but,
    to get rid of polyspace red defects, the temp variables are initialized to zero */
    VDHiSpdHwPos_HwDeg_T_f32 = 0.0f;
    VDLoSpdHwPos_HwDeg_T_f32 = 0.0f;

    AbsHwTorque_HwNm_T_f32 = Abs_f32_m(HwTorque_HwNm_T_f32);

    /* Handwheel Torque Time Check */
    if(AbsHwTorque_HwNm_T_f32 < k_HwTqMgnThd_HwNm_f32)
    {
        (void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(VehDyn_SrlHwAgVldTimer_mS_M_u32, &ElapsedTime_mS_T_u32);
    }
    else
    {
        (void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&VehDyn_SrlHwAgVldTimer_mS_M_u32);
        ElapsedTime_mS_T_u32 = 0u;
    }

    if( ElapsedTime_mS_T_u32 > k_SrlHwAgVldTiThd_mS_u32 )
    {
        SrlHwAgVldMdfy_Cnt_T_lgc = SrlHwAgVld_Cnt_T_lgc;
    }
    else
    {
        SrlHwAgVldMdfy_Cnt_T_lgc = FALSE;
    }

    /* Calculate and Filter Pinion Torque */
    PinionTrq_HwNm_T_f32 = HwTorque_HwNm_T_f32 + (TorqueCmdCRF_MtrNm_T_f32 / k_SysKinRatio_MtrDegpHwDeg_f32);
    FiltPinionTrq_HwNm_T_f32 = LPF_OpUpdate_f32_m(PinionTrq_HwNm_T_f32, &VehDyn_PinTrqSV_M_str);

    /* High Vehicle Speed Autocentering */
    if (VehDyn_AllowHiSpdAutoCntr_Cnt_M_lgc == TRUE)
    {
        VDHiSpdHwPos_HwDeg_T_f32 = Autocenter_f32(FiltPinionTrq_HwNm_T_f32,
                                                  MotorVelCRF_MtrRadpS_T_f32,
                                                  VehicleSpeed_Kph_T_f32,
                                                  VehicleSpeedValid_Cnt_T_lgc,
                                                  RelHwPos_HwDeg_T_f32,
                                                  &VehDyn_AutoCntrHiSpd_M_str);
    }

    /* Low Vehicle Speed Autocentering */
    if (VehDyn_HiSpdLearnt_Cnt_M_lgc == FALSE)
    {
        VDLoSpdHwPos_HwDeg_T_f32 = Autocenter_f32(FiltPinionTrq_HwNm_T_f32,
                                                  MotorVelCRF_MtrRadpS_T_f32,
                                                  VehicleSpeed_Kph_T_f32,
                                                  VehicleSpeedValid_Cnt_T_lgc,
                                                  RelHwPos_HwDeg_T_f32,
                                                  &VehDyn_AutoCntrLoSpd_M_str);
    }

    /* Determine switching to High Speed Autocentering */
    if ((VehDyn_AllowHiSpdAutoCntr_Cnt_M_lgc == FALSE) &&
        (VehDyn_LoSpdLearnt_Cnt_M_lgc == TRUE))
    {
        (void)Autocenter_f32(FiltPinionTrq_HwNm_T_f32,
							 MotorVelCRF_MtrRadpS_T_f32,
							 VehicleSpeed_Kph_T_f32,
							 VehicleSpeedValid_Cnt_T_lgc,
							 RelHwPos_HwDeg_T_f32,
							 &VehDyn_AutoCntrDetSpd_M_str);
    }

    if (VehDyn_HiSpdLearnt_Cnt_M_lgc == TRUE)
    {
        VDHwPos_HwDeg_T_f32 = VDHiSpdHwPos_HwDeg_T_f32;
        VDAuthority_Uls_T_f32 = k_HiSpdVDAuthority_Uls_f32;
    }
    else if ( VehDyn_AllowHiSpdAutoCntr_Cnt_M_lgc == TRUE)
    {
        if ( VehDyn_AutoCntrHiSpd_M_str.Filter2Enable_Cnt_lgc == TRUE)
        {
            VehDyn_HiSpdLearnt_Cnt_M_lgc = TRUE;
            VDHwPos_HwDeg_T_f32 = VDHiSpdHwPos_HwDeg_T_f32;
            VDAuthority_Uls_T_f32 = k_HiSpdVDAuthority_Uls_f32;
        }
        else
        {
            VDHwPos_HwDeg_T_f32 = VDLoSpdHwPos_HwDeg_T_f32;
            VDAuthority_Uls_T_f32 = k_LoSpdVDAuthority_Uls_f32;
        }
    }
    else if (VehDyn_LoSpdLearnt_Cnt_M_lgc == TRUE)
    {
        VDHwPos_HwDeg_T_f32 = VDLoSpdHwPos_HwDeg_T_f32;
        VDAuthority_Uls_T_f32 = k_LoSpdVDAuthority_Uls_f32;

        if (VehDyn_AutoCntrDetSpd_M_str.Filter2Enable_Cnt_lgc == TRUE)
        {
            VehDyn_AllowHiSpdAutoCntr_Cnt_M_lgc = TRUE;
            GetSystemTime_mS_u32(&(VehDyn_AutoCntrHiSpd_M_str.Timer1_mS_u32));
        }
    }
    else
    {
        if (VehDyn_AutoCntrLoSpd_M_str.Filter2Enable_Cnt_lgc == TRUE)
        {
            VehDyn_LoSpdLearnt_Cnt_M_lgc = TRUE;
            VDHwPos_HwDeg_T_f32 = VDLoSpdHwPos_HwDeg_T_f32;
            VDAuthority_Uls_T_f32 = k_LoSpdVDAuthority_Uls_f32;
            GetSystemTime_mS_u32(&(VehDyn_AutoCntrDetSpd_M_str.Timer1_mS_u32));
        }
        else
        {
            VDHwPos_HwDeg_T_f32 = D_ZERO_ULS_F32;
            VDAuthority_Uls_T_f32 = D_NOAUTHORITY_ULS_F32;
        }
    }

    /* Travel Exclusion */
    (void)TrvlExclsn(CwEOTPosition_HwDeg_T_f32, CcwEOTPosition_HwDeg_T_f32, RelHwPos_HwDeg_T_f32);
    VehDyn_TravelXCHwPos_HwDeg_D_f32 = VehDyn_TravelXCHwPos_HwDeg_M_f32;
    VehDyn_TravelXCHwAuth_Uls_D_f32 = VehDyn_TravelXCHwAuth_Uls_M_f32;

    RelSLPHwPos_HwDeg_T_f32 = RelHwPos_HwDeg_T_f32 + VehDyn_SLPHwPos_HwDeg_M_f32;
    VehDyn_RelSLPHwPos_HwDeg_D_f32 = RelSLPHwPos_HwDeg_T_f32;
    
    LearnedHwPos_HwDeg_T_f32 = Arbn_f32(RelHwPos_HwDeg_T_f32, 
                                    SrlHwAgVldMdfy_Cnt_T_lgc, 
                                    SrlHwAg_HwDeg_T_f32, 
                                    VDHwPos_HwDeg_T_f32, 
                                    VDAuthority_Uls_T_f32, 
                                    RelSLPHwPos_HwDeg_T_f32);
    
    /* Smooth HwPos */  
	SnsrlessHwPos_HwDeg_T_f32 = SmoothHwPos_f32(LearnedHwPos_HwDeg_T_f32);  
    
     /* limit global outputs */
    SnsrlessHwPos_HwDeg_T_f32 = Limit_m(SnsrlessHwPos_HwDeg_T_f32, D_HWPOSMIN_HWDEG_F32, D_HWPOSMAX_HWDEG_F32);    

    /* write global outputs */
    Rte_IWrite_VehDyn_Per1_SensorlessHwPos_HwDeg_f32(SnsrlessHwPos_HwDeg_T_f32);
    Rte_IWrite_VehDyn_Per1_SensorlessAuthority_Uls_f32(VehDyn_SnsrlessHwAuth_Uls_M_f32);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehDyn_SCom_ForceCenter
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ForceCenter> of PortPrototype <VehDyn_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_RelHwPos_HwDeg_f32(Float *data)
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
 *   void VehDyn_SCom_ForceCenter(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_SCom_ForceCenter(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: VehDyn_SCom_ForceCenter
 *********************************************************************************************************************/

    VehDyn_ForceCenterEnabled_Cnt_M_lgc = TRUE;
    (void)Rte_Read_RelHwPos_HwDeg_f32(&VehDyn_ForceCenterOffset_HwDeg_M_f32);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehDyn_SCom_ResetCenter
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ResetCenter> of PortPrototype <VehDyn_SCom>
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
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_NVM_VehDynReset_Srv_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_NVM_VehDynReset_Srv_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void VehDyn_SCom_ResetCenter(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_SCom_ResetCenter(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: VehDyn_SCom_ResetCenter
 *********************************************************************************************************************/

    Rte_Pim_MotPosReset()->NVMStoredLastPosValid_Cnt_lgc = FALSE;
    Rte_Pim_MotPosReset()->NVMStoredLastPos_HwDeg_f32 = D_ZERO_ULS_F32;
    (void)Rte_Call_NVM_VehDynReset_Srv_WriteBlock(NULL_PTR);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehDyn_Trns1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on entering of Mode <OFF> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_VehDyn_Trns1_HandwheelPosition_HwDeg_f32(void)
 *   Float Rte_IRead_VehDyn_Trns1_HwAuth_Uls_f32(void)
 *   Float Rte_IRead_VehDyn_Trns1_MechMtrPos_Rev_f32(void)
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
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_NVM_VehDynReset_Srv_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_NVM_VehDynReset_Srv_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHDYN_APPL_CODE) VehDyn_Trns1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: VehDyn_Trns1
 *********************************************************************************************************************/

    VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) HandWheelAuth_Uls_T_f32;
    VAR(float32, AUTOMATIC) MechMtrPos1_Rev_T_f32;
    VAR(float32, AUTOMATIC) MechMtrPos_MtrDeg_T_f32;
    VAR(float32, AUTOMATIC) MtrPos_HwDeg_T_f32;

    /* read global inputs */
    HandWheelPos_HwDeg_T_f32 = Rte_IRead_VehDyn_Trns1_HandwheelPosition_HwDeg_f32();
    HandWheelAuth_Uls_T_f32 = Rte_IRead_VehDyn_Trns1_HwAuth_Uls_f32();
    MechMtrPos1_Rev_T_f32 = Rte_IRead_VehDyn_Trns1_MechMtrPos_Rev_f32();
    
	/* Shutdown */
    if (HandWheelAuth_Uls_T_f32 >= k_SLPMinHwAuthToStoreHwPos_Uls_f32)
    {
        /* Case Valid */
        if (((MechMtrPos1_Rev_T_f32 > D_QUARTERREV_MTRREV_F32) && (MechMtrPos1_Rev_T_f32 < D_HALFREV_MTRREV_F32)) ||
           ((MechMtrPos1_Rev_T_f32 > D_THREEQUARTERREV_MTRREV_F32) && (MechMtrPos1_Rev_T_f32 < D_ONE_ULS_F32)))
        {
            MechMtrPos1_Rev_T_f32 = MechMtrPos1_Rev_T_f32 - D_ONE_ULS_F32;
        }       
        MechMtrPos_MtrDeg_T_f32 = MechMtrPos1_Rev_T_f32 * D_ONEREV_MTRDEGPERMTRREV_F32;
        MtrPos_HwDeg_T_f32 = MechMtrPos_MtrDeg_T_f32 / k_SysKinRatio_MtrDegpHwDeg_f32;

        Rte_Pim_MotPosReset()-> NVMStoredLastPos_HwDeg_f32 = (HandWheelPos_HwDeg_T_f32 - MtrPos_HwDeg_T_f32);
        Rte_Pim_MotPosReset ()->NVMStoredLastPosValid_Cnt_lgc = TRUE;
    }
    else
    {
        Rte_Pim_MotPosReset()-> NVMStoredLastPos_HwDeg_f32 = D_ZERO_ULS_F32;
        Rte_Pim_MotPosReset ()->NVMStoredLastPosValid_Cnt_lgc = FALSE;
    }

    (void)Rte_Call_NVM_VehDynReset_Srv_WriteBlock(NULL_PTR);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_VEHDYN_APPL_CODE
#include "MemMap.h"/* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

STATIC INLINE FUNC(float32, AP_VEHDYN_CODE) Autocenter_f32( VAR(float32, AUTOMATIC) FiltPinTrq_HwNm_T_f32,
                                                              VAR(float32, AUTOMATIC) MotorVelCRF_MtrRadpS_T_f32,
                                                              VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32,
                                                              VAR(boolean, AUTOMATIC) VehSpdValid_Cnt_T_lgc,
                                                              VAR(float32, AUTOMATIC) RelHwPos_HwDeg_T_f32,
                                                              P2VAR(AUTOCNTRTYPE_Str, AUTOMATIC, AUTOMATIC) AutoCntr_Cnt_T_str)
{
    VAR(uint32,  AUTOMATIC) Timer1Elapsed_mS_T_u32;
    VAR(uint32,  AUTOMATIC) Timer2Elapsed_mS_T_u32;
    VAR(float32, AUTOMATIC) AutoCntrHwPos_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) AbsFiltPinTrq_HwNm_T_f32;

    AbsFiltPinTrq_HwNm_T_f32 = Abs_f32_m(FiltPinTrq_HwNm_T_f32);

    /* Determine Filter One Enable */
    if ((Abs_f32_m(MotorVelCRF_MtrRadpS_T_f32) <= AutoCntr_Cnt_T_str->MtrVel_MtrRadpS_f32) &&
        (VehicleSpeed_Kph_T_f32 >= AutoCntr_Cnt_T_str->VehSpd_kph_f32) &&
        (VehSpdValid_Cnt_T_lgc == D_TRUE_CNT_LGC) &&
        (AbsFiltPinTrq_HwNm_T_f32 <= (AutoCntr_Cnt_T_str->FiltPinTrq_HwNm_f32)))
    {
        DtrmnElapsedTime_mS_u32(AutoCntr_Cnt_T_str->Timer1_mS_u32, &Timer1Elapsed_mS_T_u32);

        if ((AutoCntr_Cnt_T_str->Filter1Enable_Cnt_lgc == D_FALSE_CNT_LGC) &&
            (Timer1Elapsed_mS_T_u32 >= AutoCntr_Cnt_T_str->Timer1Thresh_mS_u16))
        {
            if (AutoCntr_Cnt_T_str->Filter1Initialized_Cnt_lgc == D_FALSE_CNT_LGC)
            {
                /* initialize filter state variable on first enable */
                AutoCntr_Cnt_T_str->RelHwPosFilt1SV_HwDeg_str.SV_Uls_f32 = RelHwPos_HwDeg_T_f32;
                AutoCntr_Cnt_T_str->Filter1Initialized_Cnt_lgc = D_TRUE_CNT_LGC;
            }
            GetSystemTime_mS_u32(&(AutoCntr_Cnt_T_str->Timer2_mS_u32));
            AutoCntr_Cnt_T_str->Filter2Enable_Cnt_lgc = D_FALSE_CNT_LGC;
            AutoCntr_Cnt_T_str->Filter1Enable_Cnt_lgc = D_TRUE_CNT_LGC;
        }
    }
    else
    {
        GetSystemTime_mS_u32(&(AutoCntr_Cnt_T_str->Timer1_mS_u32));
        AutoCntr_Cnt_T_str->Filter1Enable_Cnt_lgc = D_FALSE_CNT_LGC;
    }

    if (AutoCntr_Cnt_T_str->Filter1Enable_Cnt_lgc == D_TRUE_CNT_LGC)
    {
        /* Low Pass Filter One */
        LPF_OpUpdate_f32_m(RelHwPos_HwDeg_T_f32, &(AutoCntr_Cnt_T_str->RelHwPosFilt1SV_HwDeg_str));

        /* Determine Filter Two Enable */
        if (Abs_f32_m(RelHwPos_HwDeg_T_f32 - AutoCntr_Cnt_T_str->RelHwPosFilt1SV_HwDeg_str.SV_Uls_f32) <= AutoCntr_Cnt_T_str->CntrWindow_HwDeg_f32)
        {
            DtrmnElapsedTime_mS_u32(AutoCntr_Cnt_T_str->Timer2_mS_u32, &Timer2Elapsed_mS_T_u32);

            if ((AutoCntr_Cnt_T_str->Filter2Enable_Cnt_lgc == D_FALSE_CNT_LGC) &&
                (Timer2Elapsed_mS_T_u32 >= AutoCntr_Cnt_T_str->Timer2Thresh_mS_u16))
            {
                if (AutoCntr_Cnt_T_str->Filter2Initialized_Cnt_lgc == D_FALSE_CNT_LGC)
                {
                    /* initialize filter state variable on first enable */
                    AutoCntr_Cnt_T_str->RelHwPosFilt2SV_HwDeg_str.SV_Uls_f32 = AutoCntr_Cnt_T_str->RelHwPosFilt1SV_HwDeg_str.SV_Uls_f32;
                    AutoCntr_Cnt_T_str->Filter2Initialized_Cnt_lgc = D_TRUE_CNT_LGC;
                }
                AutoCntr_Cnt_T_str->Filter2Enable_Cnt_lgc = D_TRUE_CNT_LGC;
            }
        }
        else
        {
            GetSystemTime_mS_u32(&(AutoCntr_Cnt_T_str->Timer2_mS_u32));
            AutoCntr_Cnt_T_str->Filter2Enable_Cnt_lgc = D_FALSE_CNT_LGC;
        }

        /* Low Pass Filter Two */
        if (AutoCntr_Cnt_T_str->Filter2Enable_Cnt_lgc == D_TRUE_CNT_LGC)
        {
            LPF_OpUpdate_f32_m(RelHwPos_HwDeg_T_f32, &(AutoCntr_Cnt_T_str->RelHwPosFilt2SV_HwDeg_str));
        }
    }

    /* Compute Auto Center Position Output */
    AutoCntrHwPos_HwDeg_T_f32 = RelHwPos_HwDeg_T_f32 - AutoCntr_Cnt_T_str->RelHwPosFilt2SV_HwDeg_str.SV_Uls_f32;

    return AutoCntrHwPos_HwDeg_T_f32;
}
/* Travel Exclusion */
/*******************************************************************************
  * Name        :   TrvlExclsn
  * Description :   Implementation of "TrvlExclsn" section.
  * Inputs      :   CwEOTPosition_HwDeg_T_f32, CcwEOTPosition_HwDeg_T_f32,
                    RelHwPos_HwDeg_T_f32
  * Outputs     :   VehDyn_TravelXCHwPos_HwDeg_M_f32, VehDyn_TravelXCHwAuth_Uls_M_f32
  * Usage Notes :   None
  *****************************************************************************/
 STATIC FUNC(void, AP_VEHDYN_CODE) TrvlExclsn(VAR(float32, AUTOMATIC) CwEOTPosition_HwDeg_T_f32,
                                                 VAR(float32, AUTOMATIC) CcwEOTPosition_HwDeg_T_f32,                                                 
                                                 VAR(float32, AUTOMATIC) RelHwPos_HwDeg_T_f32)
{   
    VAR(float32, AUTOMATIC) MaxAbsHwPos_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) MinAbsHwPos_HwDeg_T_f32;    
    VAR(float32, AUTOMATIC) Deadband_Uls_T_f32;    
    
    if (VehDyn_Initialize_Cnt_M_lgc == FALSE)
    {
        VehDyn_MaxOffset_HwDeg_M_f32 = CwEOTPosition_HwDeg_T_f32;
        VehDyn_MinOffset_HwDeg_M_f32 = CcwEOTPosition_HwDeg_T_f32;
        VehDyn_Initialize_Cnt_M_lgc  = TRUE;
    }
    else
    {
        VehDyn_MaxOffset_HwDeg_M_f32 = Min_m(VehDyn_MaxOffset_HwDeg_M_f32, (CwEOTPosition_HwDeg_T_f32 - RelHwPos_HwDeg_T_f32));
        VehDyn_MinOffset_HwDeg_M_f32 = Max_m(VehDyn_MinOffset_HwDeg_M_f32, (CcwEOTPosition_HwDeg_T_f32 - RelHwPos_HwDeg_T_f32));
    }
    MaxAbsHwPos_HwDeg_T_f32 = Min_m(CwEOTPosition_HwDeg_T_f32, (VehDyn_MaxOffset_HwDeg_M_f32 + RelHwPos_HwDeg_T_f32));
    MinAbsHwPos_HwDeg_T_f32 = Max_m(CcwEOTPosition_HwDeg_T_f32, (VehDyn_MinOffset_HwDeg_M_f32 + RelHwPos_HwDeg_T_f32));
    VehDyn_MaxAbsHwPos_HwDeg_D_f32 = MaxAbsHwPos_HwDeg_T_f32;
    VehDyn_MinAbsHwPos_HwDeg_D_f32 = MinAbsHwPos_HwDeg_T_f32;

    if (MaxAbsHwPos_HwDeg_T_f32 <  D_ZERO_ULS_F32)
    {
        VehDyn_TravelXCHwPos_HwDeg_M_f32 = MaxAbsHwPos_HwDeg_T_f32;
    }
    else if (MinAbsHwPos_HwDeg_T_f32 > D_ZERO_ULS_F32)
    {
        VehDyn_TravelXCHwPos_HwDeg_M_f32 = MinAbsHwPos_HwDeg_T_f32;
    }
    else
    {
        VehDyn_TravelXCHwPos_HwDeg_M_f32 = D_ZERO_ULS_F32;
    }

    Deadband_Uls_T_f32 = MaxAbsHwPos_HwDeg_T_f32 - MinAbsHwPos_HwDeg_T_f32;

    if ((Deadband_Uls_T_f32 > k_TravelXCDeadband_Uls_f32) || (Deadband_Uls_T_f32 < (-k_VehDyn_TravelXCDeadbandTolr_Uls_f32)))
    {
        VehDyn_TravelXCHwAuth_Uls_M_f32 = D_NOAUTHORITY_ULS_F32;
        VehDyn_TravelXCHwPos_HwDeg_M_f32 = D_ZERO_ULS_F32;
    }
    else
    {
        VehDyn_TravelXCHwAuth_Uls_M_f32 = k_TravelXCHwAuthority_Uls_f32;
    }
}
 /* Arbitrator */
/*******************************************************************************
  * Name        :   Arbn_f32
  * Description :   Implementation of "Arbitrator" section.
  * Inputs      :   RelHwPos_HwDeg_T_f32, SrlHwAgVldMdfy_Cnt_T_lgc, 
                    SrlHwAg_HwDeg_T_f32, VDHwPos_HwDeg_T_f32, 
                    VDAuthority_Uls_T_f32, RelSLPHwPos_HwDeg_T_f32
  * Outputs     :   LearnedHwPos_HwDeg_T_f32, VehDyn_SnsrlessHwAuth_Uls_M_f32
  * Usage Notes :   None
  *****************************************************************************/
 STATIC FUNC(float32, AP_VEHDYN_CODE) Arbn_f32(VAR(float32, AUTOMATIC) RelHwPos_HwDeg_T_f32,
											   VAR(boolean, AUTOMATIC) SrlHwAgVldMdfy_Cnt_T_lgc,
											   VAR(float32, AUTOMATIC) SrlHwAg_HwDeg_T_f32,
											   VAR(float32, AUTOMATIC) VDHwPos_HwDeg_T_f32,
											   VAR(float32, AUTOMATIC) VDAuthority_Uls_T_f32,
											   VAR(float32, AUTOMATIC) RelSLPHwPos_HwDeg_T_f32) 
 {
    VAR(float32, AUTOMATIC) LearnedHwPos_HwDeg_T_f32;
    VAR(uint8, AUTOMATIC) SelnCaseSt_Cnt_T_u08;
     
    /* Case ForceCenter */          
    if (VehDyn_ForceCenterEnabled_Cnt_M_lgc == TRUE)
    {       
        LearnedHwPos_HwDeg_T_f32 = RelHwPos_HwDeg_T_f32 - VehDyn_ForceCenterOffset_HwDeg_M_f32;
        VehDyn_SnsrlessHwAuth_Uls_M_f32 = D_MAXAUTHORITY_ULS_F32;
        SelnCaseSt_Cnt_T_u08 = D_FCENTROFFSCON_CNT_U08;              
    }           
    /* Case Srl Msg */          
    else if (SrlHwAgVldMdfy_Cnt_T_lgc == TRUE)
    {               
        LearnedHwPos_HwDeg_T_f32 = SrlHwAg_HwDeg_T_f32;
        VehDyn_SnsrlessHwAuth_Uls_M_f32 = D_MAXAUTHORITY_ULS_F32;
        SelnCaseSt_Cnt_T_u08 = D_SRLCON_CNT_U08;          
    }
    /* Case VD */       
    else if (VDAuthority_Uls_T_f32 > D_NOAUTHORITY_ULS_F32)
    {       
        LearnedHwPos_HwDeg_T_f32 = VDHwPos_HwDeg_T_f32;
        VehDyn_SnsrlessHwAuth_Uls_M_f32 = VDAuthority_Uls_T_f32;
        SelnCaseSt_Cnt_T_u08 = D_VEHDYNCON_CNT_U08;
    }
    /* Case TravelXC */
    else if (VehDyn_TravelXCHwAuth_Uls_M_f32 > D_NOAUTHORITY_ULS_F32)
    {       
        LearnedHwPos_HwDeg_T_f32 = VehDyn_TravelXCHwPos_HwDeg_M_f32;
        VehDyn_SnsrlessHwAuth_Uls_M_f32 = VehDyn_TravelXCHwAuth_Uls_M_f32;
        SelnCaseSt_Cnt_T_u08 = D_TRVLEXCLSNCON_CNT_U08;
    }
    /* Case SLP */
    else                 
    {
        LearnedHwPos_HwDeg_T_f32 = RelSLPHwPos_HwDeg_T_f32;
        VehDyn_SnsrlessHwAuth_Uls_M_f32 = VehDyn_SLPHwAuth_Uls_M_f32;
        SelnCaseSt_Cnt_T_u08 = D_LASTPOSNCON_CNT_U08;
    }       
    if(SelnCaseSt_Cnt_T_u08 != VehDyn_SelnCaseSt_Cnt_M_u08)         
    {
        VehDyn_SelnCaseSwitch_Cnt_M_lgc = TRUE;     
    }       
    VehDyn_SelnCaseSt_Cnt_M_u08 = SelnCaseSt_Cnt_T_u08; 
    
    LearnedHwPos_HwDeg_T_f32 = Limit_m(LearnedHwPos_HwDeg_T_f32, D_HWPOSMIN_HWDEG_F32, D_HWPOSMAX_HWDEG_F32);
    VehDyn_SnsrlessHwAuth_Uls_M_f32 = Limit_m(VehDyn_SnsrlessHwAuth_Uls_M_f32, D_NOAUTHORITY_ULS_F32, D_MAXAUTHORITY_ULS_F32);
    
    return LearnedHwPos_HwDeg_T_f32;
 }
 /* Arbitrator */
/*******************************************************************************
  * Name        :   SmoothHwPos_f32
  * Description :   Implementation of "Smooth_HwPos" section.
  * Inputs      :   LearnedHwPos_HwDeg_T_f32
  * Outputs     :   SnsrlessHwPos_HwDeg_T_f32, VehDyn_PrevLearnedHwPos_HwDeg_M_f32
  * Usage Notes :   None
  *****************************************************************************/
 STATIC FUNC(float32, AP_VEHDYN_CODE) SmoothHwPos_f32(VAR(float32, AUTOMATIC) LearnedHwPos_HwDeg_T_f32) 
 {
    VAR(float32, AUTOMATIC) AbsLearnedHwPosdlta_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) SnsrlessHwPos_HwDeg_T_f32;
     
    AbsLearnedHwPosdlta_HwDeg_T_f32 = Abs_f32_m(LearnedHwPos_HwDeg_T_f32 - VehDyn_PrevLearnedHwPos_HwDeg_M_f32);
    if((VehDyn_SelnCaseSwitch_Cnt_M_lgc == TRUE) && (AbsLearnedHwPosdlta_HwDeg_T_f32 > k_VehDyn_ErrTolr_HwDeg_f32))
    {
        SnsrlessHwPos_HwDeg_T_f32 = ((k_VehDyn_SmoothCoeff_Uls_f32 * 
                                    (float32)(Sign_f32_m(LearnedHwPos_HwDeg_T_f32 - VehDyn_PrevLearnedHwPos_HwDeg_M_f32)) *
                                    AbsLearnedHwPosdlta_HwDeg_T_f32) + VehDyn_PrevLearnedHwPos_HwDeg_M_f32);
    }
    else
    {           
        SnsrlessHwPos_HwDeg_T_f32 = LearnedHwPos_HwDeg_T_f32;
    }
    VehDyn_PrevLearnedHwPos_HwDeg_M_f32 = SnsrlessHwPos_HwDeg_T_f32; 
    
    return SnsrlessHwPos_HwDeg_T_f32;
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
