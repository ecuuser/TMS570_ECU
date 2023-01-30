/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Sa_CmMtrCurr.c
 *     Workspace:  C:/Component/EA3/CmMtrCurr/autosar
 *     SW-C Type:  Sa_CmMtrCurr
 *  Generated at:  Tue May 24 08:59:21 2016
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Sa_CmMtrCurr>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Thu Jun 14 15:04:17 2012
 * %version:          22 %
 * %date_modified:    Fri May 20 10:03:37 2016 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/14/12   9       SAH       Set ComOffset to zero when the TrimFlag is FALSE or vehspd checks fail
 * 12/01/12   10      Selva     Added checkpoints and memory map statements, added comments
 * 03/23/13   11      OT        Implemented macros for global variable read/writes
 * 07/18/13   12      Jared     QAC and compiler warning cleanup                                                9082
 * 09/05/13	  13      Selva     A5561 and A5566 fixed 	
 * 09/06/13   14      Selva     corrected MtrCurrK1 assignment 
 * 10/07/13   15      VK		Updated to FDD 01C v006															10167
 * 11/06/13   16      SP        Anomaly 5873 and 5967 fixes														10699 and 10709
 * 11/20/13   17      KMC       Change filtering for correlation diagnostic to floating point filter to			10895
 *                              achieve desired range and resolution.
 * 01/23/14   18      LK		Updated variables and constants names to meet naming convention					11063 and 10909
 * 02/24/14   19      Selva		Deleted unused display variables & changed limit of D_CURRDQMAX_AMP_F32 		11275
 *								to 550A
 * 06/26/14	  20      Selva     Updated to FDD1C v008 and A6995
 * 05/20/16   21      NS        Updated to FDD1c v009                                                           EA3#8542
 * 05/24/16   22      NS		Updated to FDD1C v010															EA3#8586
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

#include "Rte_Sa_CmMtrCurr.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Sa_CmMtrCurr_Cfg.h"
#include "fixmath.h"
#include "Interpolation.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "filters.h"
#include <math.h>
#include <float.h>
#include "Sa_CmMtrCurr.h"
#include "CmMtrCurr_Cfg.h"


/* PRQA S 4393 EOF
   Deviation required, Library Exception, File Level Comment */
/* PRQA S 4394 EOF
   Deviation required, Library Exception, File Level Comment */
/* PRQA S 4395 EOF
   Deviation required, Library Exception, File Level Comment */

#define D_ADCREF_VOLT_F32				5.0F
#define D_ADCFULLSCALE_CNT_U16			4095U
#define D_SCALERADTOCNTS_ULS_F32		10430.3783505F
#define D_REVWITHROUND_ULS_F32			65536.5F
#define D_ROUND_ULS_F32					0.5F
#define D_ADCCOMPOFFSAMPLESIZE_CNT_U16   (256U)
#define D_SCALE_VOLTSPERCOUNT_F32		(D_ADCREF_VOLT_F32/((float32)((uint32)D_ADCFULLSCALE_CNT_U16 * (uint32)D_ADCCOMPOFFSAMPLESIZE_CNT_U16)))
#define D_CNVRTP29TOP13_CNT_U16			16U
#define D_30DEGREES_CNT_U16				5461U
#define D_ONEDIVSQRT3_F32				0.57735F
#define D_POSITIVEONE_CNT_S8			1
#define D_CURRDQMAX_AMP_F32				220.0F
#define D_MTRCURROFFHICOMOFF_CNT_U16	4000U
#define D_MTRCURROFFZEROCOMOFF_CNT_U16	0U
#define D_MINVCALCMD_CNT_F32			17500.0F
#define D_ONEHALF_ULS_F32               0.5F


enum CurrOffState{
	CURROFF_INTIALISE	= 0,
	CURROFF_HIAVERAGE	= 1,
	CURROFF_LOAVERAGE	= 2,
	CURROFF_ZEROAVERAGE	= 3,
	CURROFF_CALC		= 4
};

typedef enum CurrOffState CurrOffState_T;


#define CMMTRCURR_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
/*Display variables*/
STATIC volatile VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_CurrVectPosition_Rev_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_VectPosCosTheta_Uls_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_VectPosSinTheta_Uls_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_CurrCorrDiag_Amp_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_FiltCurrCorrDiag_Amp_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_CorrMtrCurr1_Amp_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_CorrMtrCurr2_Amp_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr1Offset_Volt_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr2Offset_Volt_D_f32; /* PRQA S 3218 */

/*Module level variables*/
STATIC VAR(uint32,  SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr1LpFltrSV_Volt_M_u3p29; /* PRQA S 3218 */
STATIC VAR(uint32,  SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr2LpFltrSV_Volt_M_u3p29; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_FiltMtrCurr1_Volt_M_f32;
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_FiltMtrCurr2_Volt_M_f32;
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr1SumHi_Volt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr2SumHi_Volt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr1SumLo_Volt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr2SumLo_Volt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr1SumZero_Volt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr2SumZero_Volt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_VecuSum_Volt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr1OffsetHi_Volt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr2OffsetHi_Volt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr1OffsetLo_Volt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr2OffsetLo_Volt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr1OffsetZero_Volt_M_f32;
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr2OffsetZero_Volt_M_f32;
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurrValCmd_VoltCnt_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr1OffDelta_VoltpVoltCnt_M_f32;
STATIC VAR(float32, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_MtrCurr2OffDelta_VoltpVoltCnt_M_f32;
#define CMMTRCURR_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define CMMTRCURR_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
/*Module level variables*/
STATIC VAR(uint16,  SA_MTRCURR_VAR_NOINIT) CmMtrCurr_CurrOffAvgCounter_Cnt_M_u16; /* PRQA S 3218 */
#define CMMTRCURR_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */


#define CMMTRCURR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(CurrOffState_T, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_CurrOffState_Uls_M_enum; /* PRQA S 3218 */
STATIC VAR(MtrCurrOffProcessFlag, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_CurroffProcessFlag_M_enum;
STATIC VAR(LPF32KSV_Str, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_CurrCorrDiagKSV_M_str;
#define CMMTRCURR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


#define CMMTRCURR_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_CurrOffTrimFlag_Cnt_M_lgc;
STATIC VAR(boolean, SA_MTRCURR_VAR_NOINIT) CmMtrCurr_CurrentGainSvc_Cnt_M_lgc;
#define CMMTRCURR_STOP_SEC_VAR_CLEARED_BOOLEAN
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
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * ManufModeType: Enumeration of integer in interval [0...2] with enumerators
 *   ProductionMode (0u)
 *   ManufacturingMode (1u)
 *   EngineeringMode (2u)
 * MtrCurrOffProcessFlag: Enumeration of integer in interval [0...4] with enumerators
 *   CURROFF_INIT (0u)
 *   CURROFF_PROCESSING (1u)
 *   CURROFF_PASS (2u)
 *   CURROFF_FAIL (3u)
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
 * CurrTempOffsetTblType: Array with 16 element(s) of type SInt16
 * NvM_DestPtr: Array with 65535 element(s) of type UInt8
 *
 * Record Types:
 * =============
 * CurrTempOffsetType: Record with elements
 *   CurrTempOffsetX_DegC_s10p5 of type CurrTempOffsetTblType
 *   CurrOffsetY1_Volts_s4p11 of type CurrTempOffsetTblType
 *   CurrOffsetY2_Volts_s4p11 of type CurrTempOffsetTblType
 * PhaseCurrCal_DataType: Record with elements
 *   EOLMtrCurrVcalCmd_VoltCnts_f32 of type Float
 *   EOLMtrCurr1OffsetLo_Volts_f32 of type Float
 *   EOLPhscurr1Gain_AmpspVolt_f32 of type Float
 *   EOLPhscurr2Gain_AmpspVolt_f32 of type Float
 *   EOLMtrCurr2OffsetLo_Volts_f32 of type Float
 *   EOLMtrCurr1OffsetDiff_Volts_f32 of type Float
 *   EOLMtrCurr2OffsetDiff_Volts_f32 of type Float
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
 * Float: D_2PI_ULS_F32 = 6.2831853071796
 * Float: D_VECUMIN_VOLTS_F32 = 5
 * Float: D_ZERO_ULS_F32 = 0
 * UInt16: D_ZERO_CNT_U16 = 0u
 * UInt32: D_ZERO_CNT_U32 = 0u
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   CurrTempOffsetType *Rte_Pim_CurrTempOffset(void)
 *   PhaseCurrCal_DataType *Rte_Pim_ShCurrCal(void)
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_SA_CMMTRCURR_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CmMtrCurrTempOffset_Scom_Get
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Get> of PortPrototype <CmMtrCurrTempOffset_Scom>
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
 *   void CmMtrCurrTempOffset_Scom_Get(CurrTempOffsetType *CurrTempOffCal)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurrTempOffset_Scom_Get(P2VAR(CurrTempOffsetType, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_VAR) CurrTempOffCal)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CmMtrCurrTempOffset_Scom_Get
 *********************************************************************************************************************/


	*CurrTempOffCal = *Rte_Pim_CurrTempOffset();


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CmMtrCurrTempOffset_Scom_Set
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Set> of PortPrototype <CmMtrCurrTempOffset_Scom>
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
 *   Std_ReturnType Rte_Call_EOLCurrTempOffset_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLCurrTempOffset_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void CmMtrCurrTempOffset_Scom_Set(const CurrTempOffsetType *CurrTempOffCal)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurrTempOffset_Scom_Set(P2CONST(CurrTempOffsetType, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_DATA) CurrTempOffCal)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CmMtrCurrTempOffset_Scom_Set
 *********************************************************************************************************************/


	*Rte_Pim_CurrTempOffset() = *CurrTempOffCal;

	(void)Rte_Call_EOLCurrTempOffset_WriteBlock(NULL_PTR);


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CmMtrCurr_Init
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

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CmMtrCurr_Init
 *********************************************************************************************************************/

	if((Rte_Pim_ShCurrCal()->EOLMtrCurrVcalCmd_VoltCnts_f32) >= D_MINVCALCMD_CNT_F32)
	{
		CmMtrCurr_MtrCurr1OffDelta_VoltpVoltCnt_M_f32 = ((Rte_Pim_ShCurrCal()->EOLMtrCurr1OffsetDiff_Volts_f32) / (Rte_Pim_ShCurrCal()->EOLMtrCurrVcalCmd_VoltCnts_f32));
		CmMtrCurr_MtrCurr2OffDelta_VoltpVoltCnt_M_f32 = ((Rte_Pim_ShCurrCal()->EOLMtrCurr2OffsetDiff_Volts_f32) / (Rte_Pim_ShCurrCal()->EOLMtrCurrVcalCmd_VoltCnts_f32));
	}
	else
	{
		CmMtrCurr_MtrCurr1OffDelta_VoltpVoltCnt_M_f32 = D_ZERO_ULS_F32;
		CmMtrCurr_MtrCurr2OffDelta_VoltpVoltCnt_M_f32 = D_ZERO_ULS_F32;
	}

	LPF_KUpdate_f32_m(k_CurrCorrErrFiltFc_Hz_f32, D_2MS_SEC_F32, &CmMtrCurr_CurrCorrDiagKSV_M_str);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CmMtrCurr_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 100ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_CmMtrCurr_Per1_FiltCntrlTemp_DegC_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_CmMtrCurr_Per1_MtrCurr1TempOffset_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_CmMtrCurr_Per1_MtrCurr1TempOffset_Volt_f32(void)
 *   void Rte_IWrite_CmMtrCurr_Per1_MtrCurr2TempOffset_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_CmMtrCurr_Per1_MtrCurr2TempOffset_Volt_f32(void)
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

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CmMtrCurr_Per1
 *********************************************************************************************************************/



	VAR(float32, AUTOMATIC) FiltCntrlTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) MtrCurr1TempOffset_Volts_T_f32;
	VAR(float32, AUTOMATIC) MtrCurr2TempOffset_Volts_T_f32;

	VAR(sint16,  AUTOMATIC) FiltCntrlTemp_DegC_T_s10p5;
	VAR(sint16,  AUTOMATIC) MtrCurr1TempOffset_Volts_T_s4p11;
	VAR(sint16,  AUTOMATIC) MtrCurr2TempOffset_Volts_T_s4p11;


	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_CmMtrCurr_Per1_CP0_CheckpointReached();

	
	/*** Temperature Based Current Offset Adjustment ***/

	/* The independent table will be based on Filt_Meas_Temp, and the dependent tables will be an additional current offset to be added to the existing EOL_Offset */

	FiltCntrlTemp_DegC_T_f32 = Rte_IRead_CmMtrCurr_Per1_FiltCntrlTemp_DegC_f32();
	FiltCntrlTemp_DegC_T_s10p5 = FPM_FloatToFixed_m(FiltCntrlTemp_DegC_T_f32,s10p5_T);

	/* Creates two signed end of line 16 point x/y lookup tables, one for each of the measured currents */
	MtrCurr1TempOffset_Volts_T_s4p11 = IntplVarXY_s16_s16Xs16Y_Cnt(Rte_Pim_CurrTempOffset()->CurrTempOffsetX_DegC_s10p5,
																   Rte_Pim_CurrTempOffset()->CurrOffsetY1_Volts_s4p11,
																   TableSize_m(Rte_Pim_CurrTempOffset()->CurrTempOffsetX_DegC_s10p5),
																   FiltCntrlTemp_DegC_T_s10p5);


	MtrCurr2TempOffset_Volts_T_s4p11 = IntplVarXY_s16_s16Xs16Y_Cnt(Rte_Pim_CurrTempOffset()->CurrTempOffsetX_DegC_s10p5,
																   Rte_Pim_CurrTempOffset()->CurrOffsetY2_Volts_s4p11,
																   TableSize_m(Rte_Pim_CurrTempOffset()->CurrTempOffsetX_DegC_s10p5),
																   FiltCntrlTemp_DegC_T_s10p5);


	MtrCurr1TempOffset_Volts_T_f32 = FPM_FixedToFloat_m(MtrCurr1TempOffset_Volts_T_s4p11, s4p11_T);
	MtrCurr2TempOffset_Volts_T_f32 = FPM_FixedToFloat_m(MtrCurr2TempOffset_Volts_T_s4p11, s4p11_T);


	Rte_IWrite_CmMtrCurr_Per1_MtrCurr1TempOffset_Volt_f32(MtrCurr1TempOffset_Volts_T_f32);
	Rte_IWrite_CmMtrCurr_Per1_MtrCurr2TempOffset_Volt_f32(MtrCurr2TempOffset_Volts_T_f32);


	/* Configurable End of Runnable Checkpoint */
	Rte_Call_CmMtrCurr_Per1_CP1_CheckpointReached();


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CmMtrCurr_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <WARMINIT, DISABLE, OFF>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_CmMtrCurr_Per2_ADCMtrCurr1_Volts_f32(void)
 *   Float Rte_IRead_CmMtrCurr_Per2_ADCMtrCurr2_Volts_f32(void)
 *   Float Rte_IRead_CmMtrCurr_Per2_CorrMtrCurrPosition_Rev_f32(void)
 *   Float Rte_IRead_CmMtrCurr_Per2_MtrCurrAngle_Rev_f32(void)
 *   Float Rte_IRead_CmMtrCurr_Per2_MtrCurrK1_Amp_f32(void)
 *   Float Rte_IRead_CmMtrCurr_Per2_MtrCurrK2_Amp_f32(void)
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

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CmMtrCurr_Per2
 *********************************************************************************************************************/


	VAR(float32, AUTOMATIC) MtrCurrAlpha_Rev_T_f32;
	VAR(float32, AUTOMATIC) CorrMtrPosElec_Rev_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrK1_Amps_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrK2_Amps_T_f32;
	VAR(float32, AUTOMATIC) CurrVectPosition_Rev_T_f32;
	VAR(float32, AUTOMATIC) VectPosCosTheta_Uls_T_f32;
	VAR(float32, AUTOMATIC) VectPosSinTheta_Uls_T_f32;
	VAR(float32, AUTOMATIC) CurrCorrDiag_Amps_T_f32;
	VAR(float32, AUTOMATIC) FiltCurrCorrDiag_Amps_T_f32;

	VAR(float32, AUTOMATIC) ADCMtrCurr1_Volts_T_f32;
	VAR(float32, AUTOMATIC) ADCMtrCurr2_Volts_T_f32;
	VAR(uint16,  AUTOMATIC) MtrCurr1_Volts_T_u3p13;
	VAR(uint16,  AUTOMATIC) MtrCurr2_Volts_T_u3p13;
	VAR(uint16,  AUTOMATIC) FiltMtrCurr1_Volts_T_u3p13;
	VAR(uint16,  AUTOMATIC) FiltMtrCurr2_Volts_T_u3p13;


	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_CmMtrCurr_Per2_CP0_CheckpointReached();
	
	MtrCurrAlpha_Rev_T_f32 = Rte_IRead_CmMtrCurr_Per2_MtrCurrAngle_Rev_f32();
	CorrMtrPosElec_Rev_T_f32 = Rte_IRead_CmMtrCurr_Per2_CorrMtrCurrPosition_Rev_f32();
	MtrCurrK1_Amps_T_f32 = Rte_IRead_CmMtrCurr_Per2_MtrCurrK1_Amp_f32();
	MtrCurrK2_Amps_T_f32 = Rte_IRead_CmMtrCurr_Per2_MtrCurrK2_Amp_f32();

	ADCMtrCurr1_Volts_T_f32 = Rte_IRead_CmMtrCurr_Per2_ADCMtrCurr1_Volts_f32();
	ADCMtrCurr2_Volts_T_f32 = Rte_IRead_CmMtrCurr_Per2_ADCMtrCurr2_Volts_f32();

    /*** End of Line (EOL) Manufacturing Calibration ***/
	
	/* LPF - Filtering for EOL Gain Calibration */
	MtrCurr1_Volts_T_u3p13 = FPM_FloatToFixed_m(ADCMtrCurr1_Volts_T_f32, u3p13_T);
	MtrCurr2_Volts_T_u3p13 = FPM_FloatToFixed_m(ADCMtrCurr2_Volts_T_f32, u3p13_T);
	
	CmMtrCurr_MtrCurr1LpFltrSV_Volt_M_u3p29 = LPF_SvUpdate_u16InFixKTrunc_m(MtrCurr1_Volts_T_u3p13, CmMtrCurr_MtrCurr1LpFltrSV_Volt_M_u3p29, k_CurrOffGainKn_Cnt_u16);
	FiltMtrCurr1_Volts_T_u3p13 = (uint16)LPF_OpUpdate_u16InFixKTrunc_m(CmMtrCurr_MtrCurr1LpFltrSV_Volt_M_u3p29);


	CmMtrCurr_MtrCurr2LpFltrSV_Volt_M_u3p29 = LPF_SvUpdate_u16InFixKTrunc_m(MtrCurr2_Volts_T_u3p13, CmMtrCurr_MtrCurr2LpFltrSV_Volt_M_u3p29, k_CurrOffGainKn_Cnt_u16);
	FiltMtrCurr2_Volts_T_u3p13 = (uint16)LPF_OpUpdate_u16InFixKTrunc_m(CmMtrCurr_MtrCurr2LpFltrSV_Volt_M_u3p29);

	CmMtrCurr_FiltMtrCurr1_Volt_M_f32 = FPM_FixedToFloat_m(FiltMtrCurr1_Volts_T_u3p13, u3p13_T);
	CmMtrCurr_FiltMtrCurr2_Volt_M_f32 = FPM_FixedToFloat_m(FiltMtrCurr2_Volts_T_u3p13, u3p13_T);

	/*** Current Measurement Cross Check Diagnostic ***/

	/* Current Correlation Function & Current Vector Position Alignment Function */
	
	CurrVectPosition_Rev_T_f32 = MtrCurrAlpha_Rev_T_f32 + CorrMtrPosElec_Rev_T_f32;
	CmMtrCurr_CurrVectPosition_Rev_D_f32 = CurrVectPosition_Rev_T_f32;

	VectPosCosTheta_Uls_T_f32 = cosf(CurrVectPosition_Rev_T_f32 * D_2PI_ULS_F32);
	VectPosSinTheta_Uls_T_f32 = sinf(CurrVectPosition_Rev_T_f32 * D_2PI_ULS_F32);

	CmMtrCurr_VectPosCosTheta_Uls_D_f32 = VectPosCosTheta_Uls_T_f32;
	CmMtrCurr_VectPosSinTheta_Uls_D_f32 = VectPosSinTheta_Uls_T_f32;

	CurrCorrDiag_Amps_T_f32 = (MtrCurrK1_Amps_T_f32 * VectPosCosTheta_Uls_T_f32) + (MtrCurrK2_Amps_T_f32 * VectPosSinTheta_Uls_T_f32);

	CmMtrCurr_CurrCorrDiag_Amp_D_f32 = CurrCorrDiag_Amps_T_f32;

	FiltCurrCorrDiag_Amps_T_f32 = LPF_OpUpdate_f32_m(CurrCorrDiag_Amps_T_f32, &CmMtrCurr_CurrCorrDiagKSV_M_str);

	CmMtrCurr_FiltCurrCorrDiag_Amp_D_f32 = FiltCurrCorrDiag_Amps_T_f32;

	if( Abs_f32_m(FiltCurrCorrDiag_Amps_T_f32) > k_CurrCorrErrThresh_Amps_f32 )
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_CurrentMeasCrossChk, 0x01U, NTC_STATUS_FAILED);
	}
	else
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_CurrentMeasCrossChk, 0x01U, NTC_STATUS_PASSED);
	}


	/* Configurable End of Runnable Checkpoint */
	Rte_Call_CmMtrCurr_Per2_CP1_CheckpointReached();


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CmMtrCurr_Per3
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <DISABLE, WARMINIT, OFF>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_CmMtrCurr_Per3_ADCMtrCurr1_Volts_f32(void)
 *   Float Rte_IRead_CmMtrCurr_Per3_ADCMtrCurr2_Volts_f32(void)
 *   Float Rte_IRead_CmMtrCurr_Per3_MtrVel_MtrRadpS_f32(void)
 *   UInt32 Rte_IRead_CmMtrCurr_Per3_SrlComSvcDft_Cnt_b32(void)
 *   Float Rte_IRead_CmMtrCurr_Per3_Vecu_Volt_f32(void)
 *   Float Rte_IRead_CmMtrCurr_Per3_VehSpd_Kph_f32(void)
 *   Boolean Rte_IRead_CmMtrCurr_Per3_VhSpdValid_Cnt_lgc(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_CmMtrCurr_Per3_ComOffset_Cnt_u16(UInt16 data)
 *   UInt16 *Rte_IWriteRef_CmMtrCurr_Per3_ComOffset_Cnt_u16(void)
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
 *   Std_ReturnType Rte_Call_EOLShCurrCal_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLShCurrCal_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_Per3(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CmMtrCurr_Per3
 *********************************************************************************************************************/


	VAR(float32, AUTOMATIC) ADCMtrCurr1_Volts_T_f32;
	VAR(float32, AUTOMATIC) ADCMtrCurr2_Volts_T_f32;
	VAR(float32, AUTOMATIC) Vecu_Volt_T_f32;
	VAR(uint16,  AUTOMATIC) ComOffset_Cnt_T_u16;
	VAR(float32, AUTOMATIC) AverageVecu_Volts_T_f32;
	VAR(float32, AUTOMATIC) MtrCurr1offsetDiff_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrCurr2offsetDiff_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrVel_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(boolean, AUTOMATIC) VhSpdValid_Cnt_T_lgc;
	VAR(MtrCurrOffProcessFlag, AUTOMATIC) CurroffProcessFlag_T_enum;


	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_CmMtrCurr_Per3_CP0_CheckpointReached();


	/*** End of Line (EOL) Manufacturing Calibration ***/

	/*Perform EOL Offset Calibration* - Periodic Part */
	
	ADCMtrCurr1_Volts_T_f32 = Rte_IRead_CmMtrCurr_Per3_ADCMtrCurr1_Volts_f32();
	ADCMtrCurr2_Volts_T_f32 = Rte_IRead_CmMtrCurr_Per3_ADCMtrCurr2_Volts_f32();
	Vecu_Volt_T_f32 = Rte_IRead_CmMtrCurr_Per3_Vecu_Volt_f32();
	MtrVel_MtrRadpS_T_f32 = Rte_IRead_CmMtrCurr_Per3_MtrVel_MtrRadpS_f32();
	VehSpd_Kph_T_f32 = Rte_IRead_CmMtrCurr_Per3_VehSpd_Kph_f32();
	VhSpdValid_Cnt_T_lgc = Rte_IRead_CmMtrCurr_Per3_VhSpdValid_Cnt_lgc();
	
	CurroffProcessFlag_T_enum = CmMtrCurr_CurroffProcessFlag_M_enum;

	if( CmMtrCurr_CurrOffTrimFlag_Cnt_M_lgc == TRUE )
	{
		if( (Abs_f32_m(MtrVel_MtrRadpS_T_f32) < k_MaxCurrOffMtrVel_RadpS_f32) &&
			(VehSpd_Kph_T_f32 < FLT_EPSILON) &&
			(VhSpdValid_Cnt_T_lgc == TRUE) )
		{
			switch(CmMtrCurr_CurrOffState_Uls_M_enum)
			{
				case CURROFF_HIAVERAGE:
					ComOffset_Cnt_T_u16 = D_MTRCURROFFHICOMOFF_CNT_U16;
					CmMtrCurr_MtrCurr1SumHi_Volt_M_f32 = CmMtrCurr_MtrCurr1SumHi_Volt_M_f32 + ADCMtrCurr1_Volts_T_f32;
					CmMtrCurr_MtrCurr2SumHi_Volt_M_f32 = CmMtrCurr_MtrCurr2SumHi_Volt_M_f32 + ADCMtrCurr2_Volts_T_f32;
					CmMtrCurr_VecuSum_Volt_M_f32 = CmMtrCurr_VecuSum_Volt_M_f32 + Vecu_Volt_T_f32;
					CmMtrCurr_CurrOffAvgCounter_Cnt_M_u16++;
					if(CmMtrCurr_CurrOffAvgCounter_Cnt_M_u16 == k_CurrOffNoofAvg_Cnt_u16)
					{
						CmMtrCurr_MtrCurr1OffsetHi_Volt_M_f32 = CmMtrCurr_MtrCurr1SumHi_Volt_M_f32 / ((float32)k_CurrOffNoofAvg_Cnt_u16);
						CmMtrCurr_MtrCurr2OffsetHi_Volt_M_f32 = CmMtrCurr_MtrCurr2SumHi_Volt_M_f32 / ((float32)k_CurrOffNoofAvg_Cnt_u16);
						AverageVecu_Volts_T_f32 = CmMtrCurr_VecuSum_Volt_M_f32 / ((float32)k_CurrOffNoofAvg_Cnt_u16);
						CmMtrCurr_MtrCurrValCmd_VoltCnt_M_f32 = ((float32)(AverageVecu_Volts_T_f32 * ((float32)(D_MTRCURROFFHICOMOFF_CNT_U16 - k_MtrCurrOffLoComOff_Cnt_u16))));
						CmMtrCurr_CurrOffAvgCounter_Cnt_M_u16 = 0u;
						ComOffset_Cnt_T_u16 = k_MtrCurrOffLoComOff_Cnt_u16;
						CmMtrCurr_CurrOffState_Uls_M_enum = CURROFF_LOAVERAGE;
					}
					CurroffProcessFlag_T_enum = CURROFF_PROCESSING;
				break;

				case CURROFF_LOAVERAGE:
					ComOffset_Cnt_T_u16 = k_MtrCurrOffLoComOff_Cnt_u16;
					CmMtrCurr_MtrCurr1SumLo_Volt_M_f32 = CmMtrCurr_MtrCurr1SumLo_Volt_M_f32 + ADCMtrCurr1_Volts_T_f32;
					CmMtrCurr_MtrCurr2SumLo_Volt_M_f32 = CmMtrCurr_MtrCurr2SumLo_Volt_M_f32 + ADCMtrCurr2_Volts_T_f32;
					CmMtrCurr_CurrOffAvgCounter_Cnt_M_u16++;
					if(CmMtrCurr_CurrOffAvgCounter_Cnt_M_u16 == k_CurrOffNoofAvg_Cnt_u16)
					{
						CmMtrCurr_MtrCurr1OffsetLo_Volt_M_f32 = CmMtrCurr_MtrCurr1SumLo_Volt_M_f32 / ((float32)k_CurrOffNoofAvg_Cnt_u16);
						CmMtrCurr_MtrCurr2OffsetLo_Volt_M_f32 = CmMtrCurr_MtrCurr2SumLo_Volt_M_f32 / ((float32)k_CurrOffNoofAvg_Cnt_u16);
						ComOffset_Cnt_T_u16 = D_MTRCURROFFZEROCOMOFF_CNT_U16;
						CmMtrCurr_CurrOffAvgCounter_Cnt_M_u16 = 0u;
						CmMtrCurr_CurrOffState_Uls_M_enum = CURROFF_ZEROAVERAGE;
					}
					CurroffProcessFlag_T_enum = CURROFF_PROCESSING;
				break;

				case CURROFF_ZEROAVERAGE:
					CmMtrCurr_MtrCurr1SumZero_Volt_M_f32 = CmMtrCurr_MtrCurr1SumZero_Volt_M_f32 + ADCMtrCurr1_Volts_T_f32;
					CmMtrCurr_MtrCurr2SumZero_Volt_M_f32 = CmMtrCurr_MtrCurr2SumZero_Volt_M_f32 + ADCMtrCurr2_Volts_T_f32;
					CmMtrCurr_CurrOffAvgCounter_Cnt_M_u16++;
					if(CmMtrCurr_CurrOffAvgCounter_Cnt_M_u16 == k_CurrOffNoofAvg_Cnt_u16)
					{
						CmMtrCurr_MtrCurr1OffsetZero_Volt_M_f32 = CmMtrCurr_MtrCurr1SumZero_Volt_M_f32 / ((float32)k_CurrOffNoofAvg_Cnt_u16);
						CmMtrCurr_MtrCurr2OffsetZero_Volt_M_f32 = CmMtrCurr_MtrCurr2SumZero_Volt_M_f32 / ((float32)k_CurrOffNoofAvg_Cnt_u16);
						CmMtrCurr_CurrOffState_Uls_M_enum = CURROFF_CALC;
					}
					CurroffProcessFlag_T_enum = CURROFF_PROCESSING;
					ComOffset_Cnt_T_u16 = D_MTRCURROFFZEROCOMOFF_CNT_U16;
				break;

				case CURROFF_CALC:
					if( (CmMtrCurr_MtrCurr1OffsetLo_Volt_M_f32 >= k_MtrCurrEOLMinOffset_Volts_f32) &&
						(CmMtrCurr_MtrCurr1OffsetLo_Volt_M_f32 <= k_MtrCurrEOLMaxOffset_Volts_f32) &&
						(CmMtrCurr_MtrCurr2OffsetLo_Volt_M_f32 >= k_MtrCurrEOLMinOffset_Volts_f32) &&
						(CmMtrCurr_MtrCurr2OffsetLo_Volt_M_f32 <= k_MtrCurrEOLMaxOffset_Volts_f32) &&
						(CmMtrCurr_MtrCurr1OffsetHi_Volt_M_f32 >= k_MtrCurrEOLMinOffset_Volts_f32) &&
						(CmMtrCurr_MtrCurr1OffsetHi_Volt_M_f32 <= k_MtrCurrEOLMaxOffset_Volts_f32) &&
						(CmMtrCurr_MtrCurr2OffsetHi_Volt_M_f32 >= k_MtrCurrEOLMinOffset_Volts_f32) &&
						(CmMtrCurr_MtrCurr2OffsetHi_Volt_M_f32 <= k_MtrCurrEOLMaxOffset_Volts_f32) )
					{
						MtrCurr1offsetDiff_Volt_T_f32 = CmMtrCurr_MtrCurr1OffsetHi_Volt_M_f32 - CmMtrCurr_MtrCurr1OffsetLo_Volt_M_f32;
						MtrCurr2offsetDiff_Volt_T_f32 = CmMtrCurr_MtrCurr2OffsetHi_Volt_M_f32 - CmMtrCurr_MtrCurr2OffsetLo_Volt_M_f32;
						Rte_Pim_ShCurrCal()->EOLMtrCurrVcalCmd_VoltCnts_f32 = CmMtrCurr_MtrCurrValCmd_VoltCnt_M_f32;
						Rte_Pim_ShCurrCal()->EOLMtrCurr1OffsetLo_Volts_f32 = CmMtrCurr_MtrCurr1OffsetLo_Volt_M_f32;
						Rte_Pim_ShCurrCal()->EOLMtrCurr2OffsetLo_Volts_f32 = CmMtrCurr_MtrCurr2OffsetLo_Volt_M_f32;
						Rte_Pim_ShCurrCal()->EOLMtrCurr1OffsetDiff_Volts_f32 = MtrCurr1offsetDiff_Volt_T_f32;
						Rte_Pim_ShCurrCal()->EOLMtrCurr2OffsetDiff_Volts_f32 = MtrCurr2offsetDiff_Volt_T_f32;
						(void)Rte_Call_EOLShCurrCal_WriteBlock(NULL_PTR);
						CmMtrCurr_CurrOffState_Uls_M_enum = CURROFF_INTIALISE;
						CurroffProcessFlag_T_enum = CURROFF_PASS;
						CmMtrCurr_CurrOffTrimFlag_Cnt_M_lgc = FALSE;
						ComOffset_Cnt_T_u16 = D_MTRCURROFFZEROCOMOFF_CNT_U16;
					}
					else
					{
						CmMtrCurr_CurrOffState_Uls_M_enum = CURROFF_INTIALISE;
						CurroffProcessFlag_T_enum = CURROFF_FAIL;
						ComOffset_Cnt_T_u16 = D_MTRCURROFFZEROCOMOFF_CNT_U16;
						CmMtrCurr_CurrOffTrimFlag_Cnt_M_lgc = FALSE;
					}
				break;

				default:
					CmMtrCurr_MtrCurr1SumHi_Volt_M_f32 = 0.0f;
					CmMtrCurr_MtrCurr2SumHi_Volt_M_f32 = 0.0f;
					CmMtrCurr_MtrCurr1SumLo_Volt_M_f32 = 0.0f;
					CmMtrCurr_MtrCurr2SumLo_Volt_M_f32 = 0.0f;
					CmMtrCurr_VecuSum_Volt_M_f32 = 0.0f;
					CmMtrCurr_CurrOffAvgCounter_Cnt_M_u16 = 0u;
					ComOffset_Cnt_T_u16 = D_MTRCURROFFHICOMOFF_CNT_U16;
					CmMtrCurr_CurrOffState_Uls_M_enum = CURROFF_HIAVERAGE;
					CurroffProcessFlag_T_enum = CURROFF_PROCESSING;
				break;
			}
		}
		else
		{
			CurroffProcessFlag_T_enum = CURROFF_FAIL;
			CmMtrCurr_CurrOffState_Uls_M_enum = CURROFF_INTIALISE;
			CmMtrCurr_CurrOffTrimFlag_Cnt_M_lgc = FALSE;
			ComOffset_Cnt_T_u16 = D_MTRCURROFFZEROCOMOFF_CNT_U16;
		}
	}
	else
	{
		CmMtrCurr_CurrOffState_Uls_M_enum = CURROFF_INTIALISE;
		ComOffset_Cnt_T_u16 = D_MTRCURROFFZEROCOMOFF_CNT_U16;
	}


	CmMtrCurr_CurroffProcessFlag_M_enum = CurroffProcessFlag_T_enum;

	Rte_IWrite_CmMtrCurr_Per3_ComOffset_Cnt_u16(ComOffset_Cnt_T_u16);


	/* Configurable End of Runnable Checkpoint */
	Rte_Call_CmMtrCurr_Per3_CP1_CheckpointReached();


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CmMtrCurr_SCom_CalGain
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <CalGain> of PortPrototype <CmMtrCurr_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MEC_Cnt_enum(ManufModeType *data)
 *   Std_ReturnType Rte_Read_MtrVel_MtrRadpS_f32(Float *data)
 *   Std_ReturnType Rte_Read_VehSpd_Kph_f32(Float *data)
 *   Std_ReturnType Rte_Read_VhSpdValid_Cnt_lgc(Boolean *data)
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
 *   Std_ReturnType Rte_Call_EOLShCurrCal_SetRamBlockStatus(Boolean RamBlockStatus)
 *     Synchronous Service Invocation. Timeout: None
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_EOLShCurrCal_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLShCurrCal_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType CmMtrCurr_SCom_CalGain(void)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_CmMtrCurr_SCom_ConditionNotCorrect
 *   RTE_E_CmMtrCurr_SCom_CurrentOutOfRange
 *   RTE_E_CmMtrCurr_SCom_VehSpdOutofRange
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_CalGain(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CmMtrCurr_SCom_CalGain (returns application error)
 *********************************************************************************************************************/


	VAR(float32, AUTOMATIC) MtrVel_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(float32, AUTOMATIC) MtrCurr1Gain_AmpspVolt_T_f32;
	VAR(float32, AUTOMATIC) MtrCurr2Gain_AmpspVolt_T_f32;
	VAR(Std_ReturnType, AUTOMATIC) RetrunValue;
		VAR(boolean, AUTOMATIC) VhSpdValid_T_Cnt_lgc;

	(void)Rte_Read_MtrVel_MtrRadpS_f32(&MtrVel_MtrRadpS_T_f32);
	(void)Rte_Read_VehSpd_Kph_f32(&VehSpd_Kph_T_f32);
	(void)Rte_Read_VhSpdValid_Cnt_lgc(&VhSpdValid_T_Cnt_lgc);

   /*** End of Line (EOL) Manufacturing Calibration ***/
   
   /*Perform EOL Gain Calibration*/

	if ((Abs_f32_m(MtrVel_MtrRadpS_T_f32) < k_MaxCurrOffMtrVel_RadpS_f32) && (CmMtrCurr_CurrentGainSvc_Cnt_M_lgc == TRUE))
	{
		if( (VehSpd_Kph_T_f32 < FLT_EPSILON) &&
			(VhSpdValid_T_Cnt_lgc == TRUE) )
		{
			if( (Abs_f32_m(CmMtrCurr_FiltMtrCurr1_Volt_M_f32 - CmMtrCurr_MtrCurr1OffsetZero_Volt_M_f32) > FLT_EPSILON) &&
				(Abs_f32_m(CmMtrCurr_FiltMtrCurr2_Volt_M_f32 - CmMtrCurr_MtrCurr2OffsetZero_Volt_M_f32) > FLT_EPSILON))
			{
				MtrCurr1Gain_AmpspVolt_T_f32 = k_CurrGainNumerator_Amps_f32 / Abs_f32_m(CmMtrCurr_FiltMtrCurr1_Volt_M_f32 - CmMtrCurr_MtrCurr1OffsetZero_Volt_M_f32);
				MtrCurr2Gain_AmpspVolt_T_f32 = k_CurrGainNumerator_Amps_f32 / Abs_f32_m(CmMtrCurr_FiltMtrCurr2_Volt_M_f32 - CmMtrCurr_MtrCurr2OffsetZero_Volt_M_f32);

				if( (MtrCurr2Gain_AmpspVolt_T_f32 >= k_MtrCurrEOLMinGain_AmpspVolts_f32) &&
					(MtrCurr2Gain_AmpspVolt_T_f32 <= k_MtrCurrEOLMaxGain_AmpspVolts_f32) &&
					(MtrCurr1Gain_AmpspVolt_T_f32 >= k_MtrCurrEOLMinGain_AmpspVolts_f32) &&
					(MtrCurr1Gain_AmpspVolt_T_f32 <= k_MtrCurrEOLMaxGain_AmpspVolts_f32) )
				{
					Rte_Pim_ShCurrCal()->EOLPhscurr1Gain_AmpspVolt_f32 = MtrCurr1Gain_AmpspVolt_T_f32;
					Rte_Pim_ShCurrCal()->EOLPhscurr2Gain_AmpspVolt_f32 = MtrCurr2Gain_AmpspVolt_T_f32;

					RetrunValue = RTE_E_OK;
					(void)Rte_Call_EOLShCurrCal_WriteBlock(NULL_PTR);
				}
				else
				{
					RetrunValue = RTE_E_CmMtrCurr_SCom_CurrentOutOfRange;
				}
			}
			else
			{
				RetrunValue = RTE_E_CmMtrCurr_SCom_CurrentOutOfRange;
			}
		}
		else
		{
			RetrunValue = RTE_E_CmMtrCurr_SCom_VehSpdOutofRange;
		}
	}
	else
	{
		RetrunValue = RTE_E_CmMtrCurr_SCom_ConditionNotCorrect;
	}


	return RetrunValue;


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CmMtrCurr_SCom_CalOffset
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <CalOffset> of PortPrototype <CmMtrCurr_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MEC_Cnt_enum(ManufModeType *data)
 *   Std_ReturnType Rte_Read_MtrVel_MtrRadpS_f32(Float *data)
 *   Std_ReturnType Rte_Read_VehSpd_Kph_f32(Float *data)
 *   Std_ReturnType Rte_Read_VhSpdValid_Cnt_lgc(Boolean *data)
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_CurrentGainSvc_Cnt_lgc(Boolean data)
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
 *   Std_ReturnType CmMtrCurr_SCom_CalOffset(void)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_CmMtrCurr_SCom_ConditionNotCorrect
 *   RTE_E_CmMtrCurr_SCom_CurrentOutOfRange
 *   RTE_E_CmMtrCurr_SCom_VehSpdOutofRange
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_CalOffset(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CmMtrCurr_SCom_CalOffset (returns application error)
 *********************************************************************************************************************/

 
    /*** End of Line (EOL) Manufacturing Calibration ***/
	
	/*Perform EOL Offset Calibration - Event Driven Part */

	VAR(float32, AUTOMATIC) MtrVel_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(Std_ReturnType,AUTOMATIC) RetrunValue;
	VAR(boolean, AUTOMATIC) VhSpdValid_T_Cnt_lgc;

	(void)Rte_Read_MtrVel_MtrRadpS_f32(&MtrVel_MtrRadpS_T_f32);
	(void)Rte_Read_VehSpd_Kph_f32(&VehSpd_Kph_T_f32);
	(void)Rte_Read_VhSpdValid_Cnt_lgc(&VhSpdValid_T_Cnt_lgc);


	if (Abs_f32_m(MtrVel_MtrRadpS_T_f32) < k_MaxCurrOffMtrVel_RadpS_f32)
	{
		if( (VehSpd_Kph_T_f32 < FLT_EPSILON) &&
			(VhSpdValid_T_Cnt_lgc == TRUE) )
		{
			CmMtrCurr_CurrentGainSvc_Cnt_M_lgc = TRUE;
			RetrunValue = RTE_E_OK;
			CmMtrCurr_CurrOffTrimFlag_Cnt_M_lgc = TRUE;
		}
		else
		{
			RetrunValue = RTE_E_CmMtrCurr_SCom_VehSpdOutofRange;
			CmMtrCurr_CurrOffTrimFlag_Cnt_M_lgc = FALSE;
		}
	}
	else
	{
		RetrunValue = RTE_E_CmMtrCurr_SCom_ConditionNotCorrect;
		CmMtrCurr_CurrOffTrimFlag_Cnt_M_lgc = FALSE;
	}

	(void) Rte_Write_CurrentGainSvc_Cnt_lgc(CmMtrCurr_CurrentGainSvc_Cnt_M_lgc);
	
	return RetrunValue;


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CmMtrCurr_SCom_MtrCurrOffReadStatus
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <MtrCurrOffReadStatus> of PortPrototype <CmMtrCurr_SCom>
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
 *   void CmMtrCurr_SCom_MtrCurrOffReadStatus(MtrCurrOffProcessFlag *CurrOffStatus)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_MtrCurrOffReadStatus(P2VAR(MtrCurrOffProcessFlag, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_VAR) CurrOffStatus)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CmMtrCurr_SCom_MtrCurrOffReadStatus
 *********************************************************************************************************************/

	
	*CurrOffStatus = CmMtrCurr_CurroffProcessFlag_M_enum;


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CmMtrCurr_SCom_ReadMtrCurrCals
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadMtrCurrCals> of PortPrototype <CmMtrCurr_SCom>
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
 *   void CmMtrCurr_SCom_ReadMtrCurrCals(PhaseCurrCal_DataType *ShCurrCalPtr)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_ReadMtrCurrCals(P2VAR(PhaseCurrCal_DataType, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_VAR) ShCurrCalPtr)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CmMtrCurr_SCom_ReadMtrCurrCals
 *********************************************************************************************************************/


	*ShCurrCalPtr = *Rte_Pim_ShCurrCal();


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CmMtrCurr_SCom_SetMtrCurrCals
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <SetMtrCurrCals> of PortPrototype <CmMtrCurr_SCom>
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
 *   Std_ReturnType Rte_Call_EOLShCurrCal_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLShCurrCal_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void CmMtrCurr_SCom_SetMtrCurrCals(const PhaseCurrCal_DataType *ShCurrCalPtr)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_CMMTRCURR_APPL_CODE) CmMtrCurr_SCom_SetMtrCurrCals(P2CONST(PhaseCurrCal_DataType, AUTOMATIC, RTE_SA_CMMTRCURR_APPL_DATA) ShCurrCalPtr)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CmMtrCurr_SCom_SetMtrCurrCals
 *********************************************************************************************************************/


	*Rte_Pim_ShCurrCal() = *ShCurrCalPtr;

	(void)Rte_Call_EOLShCurrCal_WriteBlock(NULL_PTR);


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_SA_CMMTRCURR_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


FUNC(void, SA_CMMTRCURR_CODE) CurrDQPer1(void)
{
	
	VAR(float32, AUTOMATIC) MRFMtrVel_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) Vecu_Volt_T_f32;
	VAR(uint16,  AUTOMATIC) Phs1Curr_Cnt_T_u16;
	VAR(uint16,  AUTOMATIC) Phs2Curr_Cnt_T_u16;
	VAR(uint16,  AUTOMATIC) DCPhs1Comp_Cnt_T_u16;
	VAR(uint16,  AUTOMATIC) DCPhs2Comp_Cnt_T_u16;
	VAR(float32, AUTOMATIC) MtrCurr1TempOffset_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrCurr2TempOffset_Volt_T_f32;
	VAR(sint8,   AUTOMATIC) MtrElecPol_Cnt_T_s08;
	VAR(uint16,  AUTOMATIC) MtrPosElec_Rev_T_u0p16;
	
	VAR(float32, AUTOMATIC) ElecPosDelayComp_Rad_T_f32;
	VAR(uint16,  AUTOMATIC) ElecPosDelayComp_Rev_T_u0p16;
	VAR(float32, AUTOMATIC) Phs1Curr_Volts_T_f32;
	VAR(float32, AUTOMATIC) Phs2Curr_Volts_T_f32;
	VAR(float32, AUTOMATIC) Duty1Cnts_Cnt_T_f32;
	VAR(float32, AUTOMATIC) Duty2Cnts_Cnt_T_f32;
	VAR(float32, AUTOMATIC) MtrCurr1Offset_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrCurr2Offset_Volt_T_f32;
	VAR(float32, AUTOMATIC) CorrMtrCurr1_Amps_T_f32;
	VAR(float32, AUTOMATIC) CorrMtrCurr2_Amps_T_f32;
	VAR(uint16,  AUTOMATIC) CorrMtrPosElec_Rev_T_u0p16;
	VAR(float32, AUTOMATIC) MtrCurrK2_Amps_T_f32;
	VAR(float32, AUTOMATIC) CorrMtrPosElec_Rev_T_f32;
	VAR(float32, AUTOMATIC) CosThetaElecPos_Uls_T_f32;
	VAR(float32, AUTOMATIC) SinThetaElecPos_Uls_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrK1_Amps_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrDax_Amps_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrQax_Amps_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrFinalDax_Amps_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrFinalQax_Amps_T_f32;
	VAR(uint16,  AUTOMATIC)  ADC2OffsetComp_Cnt_T_u8p8;
	
    Phs1Curr_Volts_T_f32 = D_ZERO_ULS_F32;
	Phs2Curr_Volts_T_f32 = D_ZERO_ULS_F32;
	CmMtrCurr_Read_MRFMtrVel_MtrRadpS_f32(&MRFMtrVel_MtrRadpS_T_f32);
	CmMtrCurr_Read_Vecu_Volt_f32(&Vecu_Volt_T_f32);
	CmMtrCurr_Read_Phs1Curr_Cnt_u16(&Phs1Curr_Cnt_T_u16);
	CmMtrCurr_Read_Phs2Curr_Cnt_u16(&Phs2Curr_Cnt_T_u16);
	CmMtrCurr_Read_MtrCurr1TempOffset_Volt_f32(&MtrCurr1TempOffset_Volt_T_f32);
	CmMtrCurr_Read_MtrCurr2TempOffset_Volt_f32(&MtrCurr2TempOffset_Volt_T_f32);
	CmMtrCurr_Read_MtrElecPol_Cnt_s08(&MtrElecPol_Cnt_T_s08);
	CmMtrCurr_Read_MtrPosElec_Rev_u0p16(&MtrPosElec_Rev_T_u0p16);
	CmMtrCurr_Read_ADC2OffsetComp_Cnt_u8p8(&ADC2OffsetComp_Cnt_T_u8p8) ; 
#if defined(MTRCURRPHASEBC)
	CmMtrCurr_Read_DCPhsBComp_Cnt_u16(&DCPhs1Comp_Cnt_T_u16);
	CmMtrCurr_Read_DCPhsCComp_Cnt_u16(&DCPhs2Comp_Cnt_T_u16);
#elif defined(MTRCURRPHASECB)
	CmMtrCurr_Read_DCPhsCComp_Cnt_u16(&DCPhs1Comp_Cnt_T_u16);
	CmMtrCurr_Read_DCPhsBComp_Cnt_u16(&DCPhs2Comp_Cnt_T_u16);
#elif defined(MTRCURRPHASEAB)
	CmMtrCurr_Read_DCPhsAComp_Cnt_u16(&DCPhs1Comp_Cnt_T_u16);
	CmMtrCurr_Read_DCPhsBComp_Cnt_u16(&DCPhs2Comp_Cnt_T_u16);

#elif defined(MTRCURRPHASEBA)
	CmMtrCurr_Read_DCPhsBComp_Cnt_u16(&DCPhs1Comp_Cnt_T_u16);
	CmMtrCurr_Read_DCPhsAComp_Cnt_u16(&DCPhs2Comp_Cnt_T_u16);

#elif defined(MTRCURRPHASEAC)
	CmMtrCurr_Read_DCPhsAComp_Cnt_u16(&DCPhs1Comp_Cnt_T_u16);
	CmMtrCurr_Read_DCPhsCComp_Cnt_u16(&DCPhs2Comp_Cnt_T_u16);


#elif defined(MTRCURRPHASECA)
	CmMtrCurr_Read_DCPhsCComp_Cnt_u16(&DCPhs1Comp_Cnt_T_u16);
	CmMtrCurr_Read_DCPhsAComp_Cnt_u16(&DCPhs2Comp_Cnt_T_u16);

#else
	#error "Invalid Phase A and Phase B and Phase C configuration"
	
#endif
		
	/*** Direct and Quadrature Axes Current Computation ***/
	
	ElecPosDelayComp_Rad_T_f32 = (k_NoofPoles_Uls_f32 * D_ONEHALF_ULS_F32) * MRFMtrVel_MtrRadpS_T_f32 * k_MtrPosComputDelay_Sec_f32;
	
	if( ElecPosDelayComp_Rad_T_f32 < 0.0f )
	{
		ElecPosDelayComp_Rev_T_u0p16 = (uint16)((ElecPosDelayComp_Rad_T_f32 * D_SCALERADTOCNTS_ULS_F32) + D_REVWITHROUND_ULS_F32);
	}
	else
	{
		ElecPosDelayComp_Rev_T_u0p16 = (uint16)((ElecPosDelayComp_Rad_T_f32 * D_SCALERADTOCNTS_ULS_F32) + D_ROUND_ULS_F32);
	}

	/***Rationale behind the Phase1 and Phase 2 calculation   ***/
	/**** 
	        ADC offset calibration compensation  is added to  each Phase.
           	Since we have fixed sample size of 256, PhsXCurr_Volt is calculated by 
			(Input(counts) * No of ADC samples for used for Calibration compensation(X) - (Total ADC compensation))/(5/(4095* No of ADC samples(X))))
	****/
	if (Phs1Curr_Cnt_T_u16 > D_ZERO_CNT_U16)
	{
		Phs1Curr_Volts_T_f32 = ( (((float32)Phs1Curr_Cnt_T_u16* (float32)D_ADCCOMPOFFSAMPLESIZE_CNT_U16) - (float32)ADC2OffsetComp_Cnt_T_u8p8)) * D_SCALE_VOLTSPERCOUNT_F32;
	}
	if (Phs2Curr_Cnt_T_u16 > D_ZERO_CNT_U16)
	{
	    Phs2Curr_Volts_T_f32 = ((((float32)Phs2Curr_Cnt_T_u16 * (float32)D_ADCCOMPOFFSAMPLESIZE_CNT_U16) - (float32)ADC2OffsetComp_Cnt_T_u8p8)) * D_SCALE_VOLTSPERCOUNT_F32;
	}
	
	
	Duty1Cnts_Cnt_T_f32 = FPM_FixedToFloat_m((((sint16)DCPhs1Comp_Cnt_T_u16) - ((sint16)k_MtrCurrOffLoComOff_Cnt_u16)), s15p0_T); 
	Duty2Cnts_Cnt_T_f32 = FPM_FixedToFloat_m((((sint16)DCPhs2Comp_Cnt_T_u16) - ((sint16)k_MtrCurrOffLoComOff_Cnt_u16)), s15p0_T);
	
	
	
	MtrCurr1Offset_Volt_T_f32 = (CmMtrCurr_MtrCurr1OffDelta_VoltpVoltCnt_M_f32 * Vecu_Volt_T_f32 * Duty1Cnts_Cnt_T_f32) + Rte_Pim_ShCurrCal()->EOLMtrCurr1OffsetLo_Volts_f32 + MtrCurr1TempOffset_Volt_T_f32;
	MtrCurr2Offset_Volt_T_f32 = (CmMtrCurr_MtrCurr2OffDelta_VoltpVoltCnt_M_f32 * Vecu_Volt_T_f32 * Duty2Cnts_Cnt_T_f32) + Rte_Pim_ShCurrCal()->EOLMtrCurr2OffsetLo_Volts_f32 + MtrCurr2TempOffset_Volt_T_f32;
	
	CmMtrCurr_MtrCurr1Offset_Volt_D_f32 = MtrCurr1Offset_Volt_T_f32;
	CmMtrCurr_MtrCurr2Offset_Volt_D_f32 = MtrCurr2Offset_Volt_T_f32;
	
	CorrMtrCurr1_Amps_T_f32 = (Phs1Curr_Volts_T_f32 - MtrCurr1Offset_Volt_T_f32) * Rte_Pim_ShCurrCal()->EOLPhscurr1Gain_AmpspVolt_f32;
	CorrMtrCurr2_Amps_T_f32 = (Phs2Curr_Volts_T_f32 - MtrCurr2Offset_Volt_T_f32) * Rte_Pim_ShCurrCal()->EOLPhscurr2Gain_AmpspVolt_f32;
	
	CmMtrCurr_CorrMtrCurr1_Amp_D_f32 = CorrMtrCurr1_Amps_T_f32;
	CmMtrCurr_CorrMtrCurr2_Amp_D_f32 = CorrMtrCurr2_Amps_T_f32;


	
	
#if defined(MTRCURRPHASEBC)
		if( MtrElecPol_Cnt_T_s08 == D_POSITIVEONE_CNT_S8 )
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 - D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = -(CorrMtrCurr1_Amps_T_f32 + CorrMtrCurr2_Amps_T_f32);
		MtrCurrK2_Amps_T_f32 = (CorrMtrCurr1_Amps_T_f32 - CorrMtrCurr2_Amps_T_f32) * D_ONEDIVSQRT3_F32;

	}
	else
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 + D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = -(CorrMtrCurr1_Amps_T_f32 + CorrMtrCurr2_Amps_T_f32);
		MtrCurrK2_Amps_T_f32 = (CorrMtrCurr2_Amps_T_f32 - CorrMtrCurr1_Amps_T_f32) * D_ONEDIVSQRT3_F32;
	}
#elif defined(MTRCURRPHASECB)
	if( MtrElecPol_Cnt_T_s08 == D_POSITIVEONE_CNT_S8 )
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 - D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = -(CorrMtrCurr2_Amps_T_f32 + CorrMtrCurr1_Amps_T_f32);
		MtrCurrK2_Amps_T_f32 = (CorrMtrCurr2_Amps_T_f32 - CorrMtrCurr1_Amps_T_f32) * D_ONEDIVSQRT3_F32;

	}
	else
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 + D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = -(CorrMtrCurr2_Amps_T_f32 + CorrMtrCurr1_Amps_T_f32);
		MtrCurrK2_Amps_T_f32 = (CorrMtrCurr1_Amps_T_f32 - CorrMtrCurr2_Amps_T_f32) * D_ONEDIVSQRT3_F32;
	}
#elif defined(MTRCURRPHASEAB)
	if( MtrElecPol_Cnt_T_s08 == D_POSITIVEONE_CNT_S8 )
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 - D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = CorrMtrCurr1_Amps_T_f32;
		MtrCurrK2_Amps_T_f32 = (CorrMtrCurr1_Amps_T_f32 + 2.0f * CorrMtrCurr2_Amps_T_f32) * D_ONEDIVSQRT3_F32;

	}
	else
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 + D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = CorrMtrCurr1_Amps_T_f32;
		MtrCurrK2_Amps_T_f32 = -(CorrMtrCurr1_Amps_T_f32 + 2.0f * CorrMtrCurr2_Amps_T_f32) * D_ONEDIVSQRT3_F32;
	}

#elif defined(MTRCURRPHASEBA)
	if( MtrElecPol_Cnt_T_s08 == D_POSITIVEONE_CNT_S8 )
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 - D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = CorrMtrCurr2_Amps_T_f32;
		MtrCurrK2_Amps_T_f32 = (CorrMtrCurr2_Amps_T_f32 + 2.0f * CorrMtrCurr1_Amps_T_f32) * D_ONEDIVSQRT3_F32;

	}
	else
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 + D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = CorrMtrCurr2_Amps_T_f32;
		MtrCurrK2_Amps_T_f32 = -(CorrMtrCurr2_Amps_T_f32 + 2.0f * CorrMtrCurr1_Amps_T_f32) * D_ONEDIVSQRT3_F32;
	}
#elif defined(MTRCURRPHASEAC)
	if( MtrElecPol_Cnt_T_s08 == D_POSITIVEONE_CNT_S8 )
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 - D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = CorrMtrCurr1_Amps_T_f32;
		MtrCurrK2_Amps_T_f32 = -(CorrMtrCurr1_Amps_T_f32 + 2.0f * CorrMtrCurr2_Amps_T_f32) * D_ONEDIVSQRT3_F32;

	}
	else
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 + D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = CorrMtrCurr1_Amps_T_f32;
		MtrCurrK2_Amps_T_f32 = (CorrMtrCurr1_Amps_T_f32 + 2.0f * CorrMtrCurr2_Amps_T_f32) * D_ONEDIVSQRT3_F32;
	}


#elif defined(MTRCURRPHASECA)
	if( MtrElecPol_Cnt_T_s08 == D_POSITIVEONE_CNT_S8 )
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 - D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = CorrMtrCurr2_Amps_T_f32;
		MtrCurrK2_Amps_T_f32 = -(CorrMtrCurr2_Amps_T_f32 + 2.0f * CorrMtrCurr1_Amps_T_f32) * D_ONEDIVSQRT3_F32;

	}
	else
	{
		CorrMtrPosElec_Rev_T_u0p16 = (uint16)((MtrPosElec_Rev_T_u0p16 + D_30DEGREES_CNT_U16) + ElecPosDelayComp_Rev_T_u0p16);
		MtrCurrK1_Amps_T_f32 = CorrMtrCurr2_Amps_T_f32;
		MtrCurrK2_Amps_T_f32 = (CorrMtrCurr2_Amps_T_f32 + 2.0f * CorrMtrCurr1_Amps_T_f32) * D_ONEDIVSQRT3_F32;
	}

#else
	#error "Invalid Phase A and Phase B and Phase C configuration"

#endif

	
	CorrMtrPosElec_Rev_T_f32 = FPM_FixedToFloat_m(CorrMtrPosElec_Rev_T_u0p16, u0p16_T);

	
	
	CosThetaElecPos_Uls_T_f32 = cosf(CorrMtrPosElec_Rev_T_f32 * D_2PI_ULS_F32);
	SinThetaElecPos_Uls_T_f32 = sinf(CorrMtrPosElec_Rev_T_f32 * D_2PI_ULS_F32);
	
	
	


	
	
	MtrCurrDax_Amps_T_f32 = (MtrCurrK1_Amps_T_f32 * CosThetaElecPos_Uls_T_f32) + (MtrCurrK2_Amps_T_f32 * SinThetaElecPos_Uls_T_f32);
	MtrCurrQax_Amps_T_f32 = (MtrCurrK1_Amps_T_f32 * SinThetaElecPos_Uls_T_f32) - (MtrCurrK2_Amps_T_f32 * CosThetaElecPos_Uls_T_f32);
	
	MtrCurrFinalDax_Amps_T_f32 = Limit_m(MtrCurrDax_Amps_T_f32, -D_CURRDQMAX_AMP_F32, D_CURRDQMAX_AMP_F32);
	MtrCurrFinalQax_Amps_T_f32 = Limit_m(MtrCurrQax_Amps_T_f32, -D_CURRDQMAX_AMP_F32, D_CURRDQMAX_AMP_F32);
	
	
	CmMtrCurr_Write_ElecPosDelayComp_Rad_f32(ElecPosDelayComp_Rad_T_f32);
	
	CmMtrCurr_Write_MtrCurrQax_Amp_f32(MtrCurrFinalQax_Amps_T_f32);
	CmMtrCurr_Write_MtrCurrDax_Amp_f32(MtrCurrFinalDax_Amps_T_f32);
	CmMtrCurr_Write_CorrMtrCurrPosition_Rev_f32(CorrMtrPosElec_Rev_T_f32);
	
	CmMtrCurr_Write_MtrCurrK1_Amps_f32(MtrCurrK1_Amps_T_f32);
	CmMtrCurr_Write_MtrCurrK2_Amps_f32(MtrCurrK2_Amps_T_f32);

	
	CmMtrCurr_Write_MtrCurr1_Volts_f32(Phs1Curr_Volts_T_f32);
	CmMtrCurr_Write_MtrCurr2_Volts_f32(Phs2Curr_Volts_T_f32);
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
