/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_SrlComInput.c
 *     Workspace:  C:/SynergyProjects/Haitec_LC_EPS_TMS570-nzx5jd/Haitec_LC_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *     SW-C Type:  Ap_SrlComInput
 *  Generated at:  Fri Aug 30 12:48:45 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_SrlComInput>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Jul  8 10:30:00 2013
 * %version:          EA3#16 %
 * %derived_by:       mzjphh %
 * %date_modified:    Mon Feb 17 14:53:54 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date       Rev      Author   Change Description                                                               SCR #
 * --------   -------  -------  ------------------------------------------------------------------------------  -------
 * 05/27/15	   3	   SAH		Updates for SCIR 01C
 * 07/16/15    4       PS       Updates for DSR 2A and SCIR 2A   								   	       		CR#13482
 * 07/30/15    5       PS       Fix CmdIgnSts_Cnt_M_u16, CmdIgnFailSts_Cnt_M_u16 
								and OperationalModeSts variables   								   	       		EA3#2103, EA3#2105
* 15/15/15     6       PS       Implemented software according to SCIR 3A and DSR 2A						    EA3#3742
* 10/30/15     7       PS       Implemented software according to SCIR 4A and DSR 3A						    EA3#4252
* 11/06/15     8       PS       Fix Anomaly's EA3#4375, EA3#4392											    EA3#4436, EA3#4437
* 11/16/15     9       PS       Implemented software according to SCIR 5A and DSR 5A	 					    EA3#4579
* 12/01/15     10      PS       Implemented software according to SCIR 5A and DSR 6A	 						EA3#4681, EA3#4686
* 01/16/16     11      PS       Update to NTC $120, $121, $131 and $141	 										EA3#5629
* 01/22/16     12      PS       Implemented software according to SCIR 7A 										EA3#5746
* 03/16/16     13      PS       Implemented software according to SCIR 8A 										EA3#6773, EA3#6775
* 06/21/16     15      PS       Update to NTC 12B																EA3#9090
* 10/06/16	   16      NS       Message counter fix implemented for rollover issue								EA3#11533
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Data Element Prototypes:
 ========================
  Volt_f32 of Port Interface Voltage_Volt_f32
    This signal is intended to communicate any type voltage signal measured by the ecu.  This signal has a lower limit of 0 which reequires users of the signal to provide divide by 0 protection if it is used as a denominator in a calculation.  See Vecu port prototype if a port with a lower limit is desired.


 Operation Prototypes:
 =====================
  DtrmnElapsedTime_mS_u16 of Port Interface SystemTime
    Nexteer SystemTime Service


 Mode Declaration Groups:
 ========================
  StaMd_Mode
    EPS System State mode declaration

 *********************************************************************************************************************/

#include "Rte_Ap_SrlComInput.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "Appl_Cbk.h"
#include "CanSM.h"
#include "CalConstants.h"
#include "GlobalMacro.h"
#include "Com.h"
#include "crc.h"

#define D_VEHSPDSCALE_CNT_F32				0.0625f
#define D_BUSOFF_RESET_CNT_U8				0U
#define D_BUSOFF_FAIL_CNT_U8				19U
#define D_CRCINIT_CNT_U8					0xFFu
#define D_CRCXORVALUE_CNT_U8				0xFFu
#define D_ROLLGCNTRMAXVAL_CNT_U08           15U

typedef enum{
	INIT				= 0x00U,
	INIT_COMPLETE		= 0x01U,
	START				= 0x02U
} PreIgnitionState;

STATIC FUNC(void, AP_SRLCOMINPUT_APPL_CODE) ResetTimers(uint32 SystemTime_mS_T_u32);
STATIC FUNC(boolean, AP_IMCARBR_APPL_CODE)  VldtRollgCntr( VAR(uint8, AUTOMATIC) PrsntRollgCntr_Cnt_T_u08, VAR(uint8, AUTOMATIC) PrevRollgCntr_Cnt_T_u08);

#define SRLCOMINPUT_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) BCM_CMDInvMsgTimer_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) BCM_CMDInvMsgTimer1_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) BCM_CMDInvMsgTimer2_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) BCM_CMDMMsgTimer_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) BCM_CMDMMsgTimer1_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) BCM_CMDMMsgTimer2_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) BCM2InvMsgTimer_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) BCM2MMsgTimer_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) BSM1MMsgTimer_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) CfgCodeMsgTimer_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) CTCEnableTimer_mS_M_u32; /* PRQA S 3218 */
STATIC VAR(float32, AP_SRCOMINPUT_VAR) ManVehSpd_Kph_M_f32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) MOT1InvMsgTimer_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) MOT1MMsgTimer_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) MOT3InvMsgTimer_mS_M_u32; /* PRQA S 3218 */
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) MOT3MMsgTimer_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) NTCEnableTimer_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) IPCInvMsgTimer_mS_M_u32;
STATIC VAR(uint32,  AP_SRCOMINPUT_VAR) IPCMMsgTimer_mS_M_u32;
STATIC VAR(float32, AP_SRCOMINPUT_VAR) SrlComVehSpd_Kph_M_f32; /* PRQA S 3218 */
STATIC VAR(uint32, AP_SRCOMINPUT_VAR) SystemTime_mS_M_u32; /* PRQA S 3218 */
#define SRLCOMINPUT_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define SRLCOMINPUT_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, AP_SRCOMINPUT_VAR) BSM1CRCFltAcc_Cnt_M_u16; /* PRQA S 3218 */
STATIC VAR(uint16, AP_SRCOMINPUT_VAR) BSM1MsgCounterFltAcc_Cnt_M_u16; /* PRQA S 3218 */
STATIC VAR(uint16, AP_SRCOMINPUT_VAR) VehSpeedSigFltAcc_Cnt_M_u16; /* PRQA S 3218 */
STATIC VAR(uint16, AP_SRCOMINPUT_VAR) VehSpeed_Cnt_M_u16; /* PRQA S 3218 */
#define SRLCOMINPUT_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
	
#define SRLCOMINPUT_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) BusOffCnt_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) CmdIgnSts_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) CmdIgnStsPrev_Cnt_M_u8;
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) CmdIgnFailSts_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) CmdIgnFailStsInternal_Cnt_M_u8;
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) CRCB1_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) CalculatedCRCB1_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) EngStartStopSts_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) EngSts_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) ESLampFailSts_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) MsgCntB1_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) MsgCntB1Prev_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) NTC120Parameter_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) NTC121Parameter_Cnt_M_u8;
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) NTC141Parameter_Cnt_M_u8;
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) OpModeSts_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) OpModeFailSts_Cnt_M_u8;
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) OpModeStsPrev_Cnt_M_u8; /* PRQA S 3218 */
STATIC VAR(uint8, AP_SRCOMINPUT_VAR) StartStopSts_Cnt_M_u8; /* PRQA S 3218 */
#define SRLCOMINPUT_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */

#define SRLCOMINPUT_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) BcmNodeAbsent_Cnt_M_lgc; /* PRQA S 3218 */
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) BcmNodeFaulty_Cnt_M_lgc; /* PRQA S 3218 */
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) BCM_CheckforInvalid_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) BCM2_CheckforInvalid_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) BCMCMDMsgMissing_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) BCM2MsgMissing_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) BSMMsgMissing_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) CityModeSts_Cnt_M_lgc; /* PRQA S 3218 */
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) CfgCodeRequestReceived_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) EcmNodeAbsent_Cnt_M_lgc; /* PRQA S 3218 */
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) EcmNodeFaulty_Cnt_M_lgc; /* PRQA S 3218 */
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) InhibitNTCs_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) IgnitionPreStart_Cnt_M_lgc; /* PRQA S 3218 */
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) IPC2_CheckforInvalid_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) MOT1_CheckforInvalid_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) MOT1MsgMissing_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) OpModeStsCTCEnableCriteria_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) PrevEpsEn_Cnt_M_lgc; /* PRQA S 3218 */
STATIC VAR(boolean, AP_SRCOMINPUT_VAR) VehSpeedFailSts_Cnt_M_lgc; /* PRQA S 3218 */
#define SRLCOMINPUT_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define SRLCOMINPUT_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(PreIgnitionState, AP_SRCOMINPUT_VAR) NTC120IgnitionStartState_M_enum;
STATIC VAR(PreIgnitionState, AP_SRCOMINPUT_VAR) NTC120IgnitionOffState_M_enum;
STATIC VAR(PreIgnitionState, AP_SRCOMINPUT_VAR) NTC121IgnitionStartState_M_enum;
STATIC VAR(PreIgnitionState, AP_SRCOMINPUT_VAR) NTC121IgnitionOffState_M_enum;
#define SRLCOMINPUT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

extern FUNC(void, RTE_AP_SRLCOMOUTPUT_APPL_CODE) SetBusOffRecovered(boolean BusOffRecovered_Cnt_T_lgc);
extern FUNC(void, RTE_AP_SRLCOMOUTPUT_APPL_CODE) CfgCodeResponse(void);
STATIC FUNC(uint8, AP_SRLCOMINPUT_APPL_CODE) BSM1MsgCalculateCRC(void);

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
 * DT_CAN_N: Integer in interval [0...65535]
 * DT_LV_CAN_N_ERR: Boolean
 * DT_VehSpeed: Integer in interval [0...2047]
 * Double: Real in interval [-DBL_MAX...DBL_MAX] with double precision including NaN (standard type)
 * Float: Real in interval [-FLT_MAX...FLT_MAX] with single precision (standard type)
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * SInt32: Integer in interval [-2147483648...2147483647] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * DT_BCM_Key_Sta: Enumeration of integer in interval [0...3] with enumerators
 *   Cx0_Lock (0U)
 *   Cx1_Acc (1U)
 *   Cx2_On (2U)
 *   Cx3_Start (3U)
 * NTCNumber: Enumeration of integer in interval [0...511] with enumerators
 *   NTC_Num_FlashWrapperLgcFlt (1U)
 *   NTC_Num_FlashECCCorr (2U)
 *   NTC_Num_FlashECCMemFlt (3U)
 *   NTC_Num_FlashCRCMemFault (4U)
 *   NTC_Num_CurrentSensorCalOutOfRange (9U)
 *   NTC_Num_EEPROMDiag (10U)
 *   NTC_Num_EEPROMDiagMtrStr (11U)
 *   NTC_Num_PriSnsrTrqStorFlt (12U)
 *   NTC_Num_EEPROMDiagPosTrimStr (13U)
 *   NTC_Num_SecSnsrTrqStorFlt (14U)
 *   NTC_Num_EEPROMDiagPolarityStr (15U)
 *   NTC_Num_RAMDiag_GeneralFlt (16U)
 *   NTC_Num_RAMDiag_WrprLgcFlt (17U)
 *   NTC_Num_RAMDiag_ECCCorrIndFlt (18U)
 *   NTC_Num_RAMDiag_ECCMemFlt (19U)
 *   NTC_Num_RAMDiag_CRCMemFlt (20U)
 *   NTC_Num_RAMDiag_VIMRamFlt (23U)
 *   NTC_Num_RAMDiag_NHET1RamFlt (24U)
 *   NTC_Num_RAMDiag_NHET2RamFlt (25U)
 *   NTC_Num_RAMDiag_ADC1RamFlt (26U)
 *   NTC_Num_RAMDiag_DCANRamFault (27U)
 *   NTC_Num_RAMDiag_ADC2RamFlt (28U)
 *   NTC_Num_RAMDiag_HETTU1RamFlt (29U)
 *   NTC_Num_RAMDiag_HETTU2RamFlt (30U)
 *   NTC_Num_CPU_RegVer (32U)
 *   NTC_Num_CPU_CoreInitFlt (33U)
 *   NTC_Num_CPU_CoreRunTimeFlt (34U)
 *   NTC_Num_CPU_ClockMon (35U)
 *   NTC_Num_CPU_eFuseFlt (36U)
 *   NTC_Num_CPU_MPUViolation (37U)
 *   NTC_Num_CPU_FactPrcsErr (40U)
 *   NTC_Num_PropExeDiag_InitDiag (41U)
 *   NTC_Num_PrgFlwDeadlnFlt (42U)
 *   NTC_Num_PropExeDiag_RunTimeDiag (43U)
 *   NTC_Num_PropExeDiag_COPTimeout (44U)
 *   NTC_Num_PropExeDiag_PrefetchAbort (48U)
 *   NTC_Num_PropExeDiag_DataAbort (49U)
 *   NTC_Num_PerDiag_ADC1Flt (50U)
 *   NTC_Num_PerDiag_ADC2Flt (51U)
 *   NTC_Num_PerDiag_ADCCrossChkFlt (52U)
 *   NTC_Num_PerDiag_IllegalAccess (53U)
 *   NTC_Num_PerDiag_DMAFlt (54U)
 *   NTC_Num_PerDiag_CPUWarning (63U)
 *   NTC_Num_TmpMonFunc (64U)
 *   NTC_Num_TmpMonRunTimeFlt (65U)
 *   NTC_Num_PowerRelayInitFlt (66U)
 *   NTC_Num_PrechargeFailure (67U)
 *   NTC_Num_PowerRelayRunFlt (68U)
 *   NTC_Num_Thermistor (69U)
 *   NTC_Num_RefSupplyVltg (70U)
 *   NTC_Num_TrcvrInterfaceFlt (71U)
 *   NTC_Num_CPUSupplyOvervoltage (72U)
 *   NTC_Num_GateDrvFlt (77U)
 *   NTC_Num_OnStateSingleFET (78U)
 *   NTC_Num_OnStateMultiFET (79U)
 *   NTC_Num_PhaseVoltageVerf (80U)
 *   NTC_Num_PhaseDscnt (81U)
 *   NTC_Num_DigPhaseVoltageVerf (82U)
 *   NTC_Num_PhaseDscntFailedDisable (83U)
 *   NTC_Num_CurrentMeas1 (84U)
 *   NTC_Num_CurrentMeas2 (85U)
 *   NTC_Num_CurrentMeasCrossChk (86U)
 *   NTC_Num_PDSupplyOverVoltage (87U)
 *   NTC_Num_ChargePumpUnderVoltage (88U)
 *   NTC_Num_HwTrqSensor (96U)
 *   NTC_Num_AnaVsDigHwTrq (97U)
 *   NTC_Num_TrqSensorRecoveryFlt (98U)
 *   NTC_Num_TrqSensorScaleInvalid (100U)
 *   NTC_Num_T1vsT2 (101U)
 *   NTC_Num_T1OutofRange (102U)
 *   NTC_Num_T2OutofRange (103U)
 *   NTC_Num_DigT1vsT2 (104U)
 *   NTC_Num_DigT1OutofRange (105U)
 *   NTC_Num_DigT2OutofRange (106U)
 *   NTC_Num_RedT1vsT2 (107U)
 *   NTC_Num_HWACrossChecks (108U)
 *   NTC_Num_HWASnsrCommFault (109U)
 *   NTC_Num_HWASensorRel (110U)
 *   NTC_Num_HWASensorAbs (111U)
 *   NTC_Num_PriMSB_SinCosCorr (112U)
 *   NTC_Num_SecMSB_SinCosCorr (113U)
 *   NTC_Num_PriVsSec_SinCosCorr (114U)
 *   NTC_Num_DigMSBFlt (115U)
 *   NTC_Num_MtrVelFlt (116U)
 *   NTC_Num_HWAtoMtrAngleCorr (117U)
 *   NTC_Num_RedPriVsSec_SinCosCorr (118U)
 *   NTC_Num_TurnCntr_PosLoss (128U)
 *   NTC_Num_TurnCntr_MicroProcFlt (129U)
 *   NTC_Num_TurnCntr_SensorPosFlt (130U)
 *   NTC_Num_TurnCntr_SpiComFlt (131U)
 *   NTC_Num_TurnCntr_HighQuiescCur (132U)
 *   NTC_Num_TurnCntr_MainResets (133U)
 *   NTC_Num_TurnCntr_PosLossNotSpdDep (134U)
 *   NTC_Num_KinematicIntDiag (144U)
 *   NTC_Num_HighFriction (145U)
 *   NTC_Num_DutyCycleExceeded (148U)
 *   NTC_Num_AbsTempThermLimit (149U)
 *   NTC_Num_LatchActive (160U)
 *   NTC_Num_OpTrqVsHwTrq (168U)
 *   NTC_Num_CurrentReas (169U)
 *   NTC_Num_OpVoltage (176U)
 *   NTC_Num_ExVoltageLow (177U)
 *   NTC_Num_ReducedAsstLowVoltage (178U)
 *   NTC_Num_ExVoltageHigh (180U)
 *   NTC_Num_OpVoltageOvrMax (181U)
 *   NTC_Num_BattTransOverVolt (182U)
 *   NTC_Num_IgnConfDiag (184U)
 *   NTC_Num_TurnCntr_LowBattery (185U)
 *   NTC_Num_EEPROMCloseFailed (191U)
 *   NTC_Num_SigPath1CrossChk (192U)
 *   NTC_Num_SigPath2CrossChk (193U)
 *   NTC_Num_SigPath3CrossChk (194U)
 *   NTC_Num_SigPath4CrossChk (195U)
 *   NTC_Num_SigPath5CrossChk (196U)
 *   NTC_Num_DampingFWReached (197U)
 *   NTC_Num_AssistFWReached (198U)
 *   NTC_Num_ReturnFWReached (199U)
 *   NTC_Num_DampingFWFltMode (200U)
 *   NTC_Num_AssistFWFltMode (201U)
 *   NTC_Num_VBICFltMode (202U)
 *   NTC_Num_StaMdsSysC (203U)
 *   NTC_NUM_SysFailureForRotVel (204U)
 *   NTC_NUM_SysFailForRedntRotVel (205U)
 *   NTC_Num_SysFailureForTrqSnsr (206U)
 *   NTC_Num_SysFailureForRedTrqSnsr (207U)
 *   NTC_NUM_SysFailureForCtrlVolt (209U)
 *   NTC_Num_GlblSgnlOvrwrtDet (223U)
 *   NTC_Num_VLF_00 (224U)
 *   NTC_Num_VLF_01 (225U)
 *   NTC_Num_VLF_02 (226U)
 *   NTC_Num_VLF_03 (227U)
 *   NTC_Num_VLF_04 (228U)
 *   NTC_Num_VLF_05 (229U)
 *   NTC_Num_VLF_06 (230U)
 *   NTC_Num_VLF_07 (231U)
 *   NTC_Num_VLF_08 (232U)
 *   NTC_Num_VLF_09 (233U)
 *   NTC_Num_VLF_10 (234U)
 *   NTC_Num_VLF_11 (235U)
 *   NTC_Num_VLF_12 (236U)
 *   NTC_Num_VLF_13 (237U)
 *   NTC_Num_VLF_14 (238U)
 *   NTC_Num_VLF_15 (239U)
 *   NTC_Num_VLF_16 (240U)
 *   NTC_Num_VLF_17 (241U)
 *   NTC_Num_VLF_18 (242U)
 *   NTC_Num_VLF_19 (243U)
 *   NTC_Num_VLF_20 (244U)
 *   NTC_Num_VLF_21 (245U)
 *   NTC_Num_VLF_22 (246U)
 *   NTC_Num_VLF_23 (247U)
 *   NTC_Num_VLF_24 (248U)
 *   NTC_Num_VLF_25 (249U)
 *   NTC_Num_VLF_26 (250U)
 *   NTC_Num_VLF_27 (251U)
 *   NTC_Num_VLF_28 (252U)
 *   NTC_Num_VLF_29 (253U)
 *   NTC_Num_VLF_30 (254U)
 *   NTC_Num_VLF_31 (255U)
 *   NTC_Num_BusOffCh1 (256U)
 *   NTC_Num_BusOffCh1NodeMute (257U)
 *   NTC_Num_Node1AAbsent (258U)
 *   NTC_Num_Node1AFaulty (259U)
 *   NTC_Num_Node1BAbsent (260U)
 *   NTC_Num_Node1BFaulty (261U)
 *   NTC_Num_Node1CAbsent (262U)
 *   NTC_Num_Node1CFaulty (263U)
 *   NTC_Num_Node1DAbsent (264U)
 *   NTC_Num_Node1DFaulty (265U)
 *   NTC_Num_Node1EAbsent (266U)
 *   NTC_Num_Node1EFaulty (267U)
 *   NTC_Num_Node1FAbsent (268U)
 *   NTC_Num_Node1FFaulty (269U)
 *   NTC_Num_Node1GAbsent (270U)
 *   NTC_Num_Node1GFaulty (271U)
 *   NTC_Num_BusOffCh2 (272U)
 *   NTC_Num_Node2AAbsent (273U)
 *   NTC_Num_Node2AFaulty (274U)
 *   NTC_Num_Node2BAbsent (275U)
 *   NTC_Num_Node2BFaulty (276U)
 *   NTC_Num_Node2CAbsent (277U)
 *   NTC_Num_Node2CFaulty (278U)
 *   NTC_Num_Node2DAbsent (279U)
 *   NTC_Num_Node2DFaulty (280U)
 *   NTC_Num_Node2EAbsent (281U)
 *   NTC_Num_Node2EFaulty (282U)
 *   NTC_Num_Node2FAbsent (283U)
 *   NTC_Num_Node2FFaulty (284U)
 *   NTC_Num_Node2GAbsent (285U)
 *   NTC_Num_Node2GFaulty (286U)
 *   NTC_Num_InvalidMsg_M (288U)
 *   NTC_Num_MissingMsg_M (289U)
 *   NTC_Num_CRCFltMsg_M (290U)
 *   NTC_Num_PgrsCntFltMsg_M (291U)
 *   NTC_Num_DataRngFltMsg_M (292U)
 *   NTC_Num_DataRateFltMsg_M (293U)
 *   NTC_Num_DataOtherFltMsg_M (294U)
 *   NTC_Num_DataOther2FltMsg_M (295U)
 *   NTC_Num_InvalidMsg_N (296U)
 *   NTC_Num_MissingMsg_N (297U)
 *   NTC_Num_CRCFltMsg_N (298U)
 *   NTC_Num_PgrsCntFltMsg_N (299U)
 *   NTC_Num_DataRngFltMsg_N (300U)
 *   NTC_Num_DataRateFltMsg_N (301U)
 *   NTC_Num_DataOtherFltMsg_N (302U)
 *   NTC_Num_DataOtherFlt2Msg_N (303U)
 *   NTC_Num_InvalidMsg_O (304U)
 *   NTC_Num_MissingMsg_O (305U)
 *   NTC_Num_CRCFltMsg_O (306U)
 *   NTC_Num_PgrsCntFltMsg_O (307U)
 *   NTC_Num_DataRngFltMsg_O (308U)
 *   NTC_Num_DataRateFltMsg_O (309U)
 *   NTC_Num_DataOtherFltMsg_O (310U)
 *   NTC_Num_InvalidMsg_P (312U)
 *   NTC_Num_MissingMsg_P (313U)
 *   NTC_Num_CRCFltMsg_P (314U)
 *   NTC_Num_PgrsCntFltMsg_P (315U)
 *   NTC_Num_DataRngFltMsg_P (316U)
 *   NTC_Num_DataRateFltMsg_P (317U)
 *   NTC_Num_DataOtherFltMsg_P (318U)
 *   NTC_Num_InvalidMsg_Q (320U)
 *   NTC_Num_MissingMsg_Q (321U)
 *   NTC_Num_CRCFltMsg_Q (322U)
 *   NTC_Num_PgrsCntFltMsg_Q (323U)
 *   NTC_Num_DataRngFltMsg_Q (324U)
 *   NTC_Num_DataRateFltMsg_Q (325U)
 *   NTC_Num_DataOtherFltMsg_Q (326U)
 *   NTC_Num_InvalidMsg_R (328U)
 *   NTC_Num_MissingMsg_R (329U)
 *   NTC_Num_CRCFltMsg_R (330U)
 *   NTC_Num_PgrsCntFltMsg_R (331U)
 *   NTC_Num_DataRngFltMsg_R (332U)
 *   NTC_Num_DataRateFltMsg_R (333U)
 *   NTC_Num_DataOtherFltMsg_R (334U)
 *   NTC_Num_DataOtherFlt2Msg_R (335U)
 *   NTC_Num_InvalidMsg_S (336U)
 *   NTC_Num_MissingMsg_S (337U)
 *   NTC_Num_CRCFltMsg_S (338U)
 *   NTC_Num_PgrsCntFltMsg_S (339U)
 *   NTC_Num_DataRngFltMsg_S (340U)
 *   NTC_Num_DataRateFltMsg_S (341U)
 *   NTC_Num_DataOtherFltMsg_S (342U)
 *   NTC_Num_InvalidMsg_T (344U)
 *   NTC_Num_MissingMsg_T (345U)
 *   NTC_Num_CRCFltMsg_T (346U)
 *   NTC_Num_PgrsCntFltMsg_T (347U)
 *   NTC_Num_DataRngFltMsg_T (348U)
 *   NTC_Num_DataRateFltMsg_T (349U)
 *   NTC_Num_DataOtherFltMsg_T (350U)
 *   NTC_Num_InvalidMsg_U (352U)
 *   NTC_Num_MissingMsg_U (353U)
 *   NTC_Num_CRCFltMsg_U (354U)
 *   NTC_Num_PgrsCntFltMsg_U (355U)
 *   NTC_Num_DataRngFltMsg_U (356U)
 *   NTC_Num_DataRateFltMsg_U (357U)
 *   NTC_Num_DataOtherFltMsg_U (358U)
 *   NTC_Num_InvalidMsg_V (360U)
 *   NTC_Num_MissingMsg_V (361U)
 *   NTC_Num_CRCFltMsg_V (362U)
 *   NTC_Num_PgrsCntFltMsg_V (363U)
 *   NTC_Num_DataRngFltMsg_V (364U)
 *   NTC_Num_DataRateFltMsg_V (365U)
 *   NTC_Num_DataOtherFltMsg_V (366U)
 *   NTC_Num_InvalidMsg_W (368U)
 *   NTC_Num_MissingMsg_W (369U)
 *   NTC_Num_CRCFltMsg_W (370U)
 *   NTC_Num_PgrsCntFltMsg_W (371U)
 *   NTC_Num_DataRngFltMsg_W (372U)
 *   NTC_Num_DataRateFltMsg_W (373U)
 *   NTC_Num_DataOtherFltMsg_W (374U)
 *   NTC_Num_InvalidMsg_X (376U)
 *   NTC_Num_MissingMsg_X (377U)
 *   NTC_Num_CRCFltMsg_X (378U)
 *   NTC_Num_PgrsCntFltMsg_X (379U)
 *   NTC_Num_DataRngFltMsg_X (380U)
 *   NTC_Num_DataRateFltMsg_X (381U)
 *   NTC_Num_DataOtherFltMsg_X (382U)
 *   NTC_Num_InvalidMsg_Y (384U)
 *   NTC_Num_MissingMsg_Y (385U)
 *   NTC_Num_CRCFltMsg_Y (386U)
 *   NTC_Num_PgrsCntFltMsg_Y (387U)
 *   NTC_Num_DataRngFltMsg_Y (388U)
 *   NTC_Num_DataRateFltMsg_Y (389U)
 *   NTC_Num_DataOtherFltMsg_Y (390U)
 *   NTC_Num_InvalidMsg_Z (392U)
 *   NTC_Num_MissingMsg_Z (393U)
 *   NTC_Num_CRCFltMsg_Z (394U)
 *   NTC_Num_PgrsCntFltMsg_Z (395U)
 *   NTC_Num_DataRngFltMsg_Z (396U)
 *   NTC_Num_DataRateFltMsg_Z (397U)
 *   NTC_Num_DataOtherFltMsg_Z (398U)
 *   NTC_Num_DSTXORActive (399U)
 *   NTC_Num_InvalidMsg_AA (400U)
 *   NTC_Num_MissingMsg_AA (401U)
 *   NTC_Num_CRCFltMsg_AA (402U)
 *   NTC_Num_PgrsCntFltMsg_AA (403U)
 *   NTC_Num_DataRngFltMsg_AA (404U)
 *   NTC_Num_DataRateFltMsg_AA (405U)
 *   NTC_Num_DataOtherFltMsg_AA (406U)
 *   NTC_Num_InvalidMsg_AB (408U)
 *   NTC_Num_MissingMsg_AB (409U)
 *   NTC_Num_CRCFltMsg_AB (410U)
 *   NTC_Num_PgrsCntFltMsg_AB (411U)
 *   NTC_Num_DataRngFltMsg_AB (412U)
 *   NTC_Num_DataRateFltMsg_AB (413U)
 *   NTC_Num_DataOtherFltMsg_AB (414U)
 *   NTC_Num_InvalidMsg_AC (416U)
 *   NTC_Num_MissingMsg_AC (417U)
 *   NTC_Num_CRCFltMsg_AC (418U)
 *   NTC_Num_PgrsCntFltMsg_AC (419U)
 *   NTC_Num_DataRngFltMsg_AC (420U)
 *   NTC_Num_DataRateFltMsg_AC (421U)
 *   NTC_Num_DataOtherFltMsg_AC (422U)
 *   NTC_Num_InvalidMsg_AD (424U)
 *   NTC_Num_MissingMsg_AD (425U)
 *   NTC_Num_CRCFltMsg_AD (426U)
 *   NTC_Num_PgrsCntFltMsg_AD (427U)
 *   NTC_Num_DataRngFltMsg_AD (428U)
 *   NTC_Num_DataRateFltMsg_AD (429U)
 *   NTC_Num_DataOtherFltMsg_AD (430U)
 *   NTC_Num_InvalidMsg_AE (432U)
 *   NTC_Num_MissingMsg_AE (433U)
 *   NTC_Num_CRCFltMsg_AE (434U)
 *   NTC_Num_PgrsCntFltMsg_AE (435U)
 *   NTC_Num_DataRngFltMsg_AE (436U)
 *   NTC_Num_DataRateFltMsg_AE (437U)
 *   NTC_Num_DataOtherFltMsg_AE (438U)
 *   NTC_Num_InvalidMsg_AF (440U)
 *   NTC_Num_MissingMsg_AF (441U)
 *   NTC_Num_CRCFltMsg_AF (442U)
 *   NTC_Num_PgrsCntFltMsg_AF (443U)
 *   NTC_Num_DataRngFltMsg_AF (444U)
 *   NTC_Num_DataRateFltMsg_AF (445U)
 *   NTC_Num_DataOtherFltMsg_AF (446U)
 *   NTC_Num_InvalidMsg_AG (448U)
 *   NTC_Num_MissingMsg_AG (449U)
 *   NTC_Num_CRCFltMsg_AG (450U)
 *   NTC_Num_PgrsCntFltMsg_AG (451U)
 *   NTC_Num_DataRngFltMsg_AG (452U)
 *   NTC_Num_DataRateFltMsg_AG (453U)
 *   NTC_Num_DataOtherFltMsg_AG (454U)
 *   NTC_Num_InvalidMsg_AH (456U)
 *   NTC_Num_MissingMsg_AH (457U)
 *   NTC_Num_CRCFltMsg_AH (458U)
 *   NTC_Num_PgrsCntFltMsg_AH (459U)
 *   NTC_Num_DataRngFltMsg_AH (460U)
 *   NTC_Num_DataRateFltMsg_AH (461U)
 *   NTC_Num_DataOtherFltMsg_AH (462U)
 *   NTC_Num_FlexrayCommunicationError (465U)
 *   NTC_Num_InvalidMsg_AI (466U)
 *   NTC_Num_MissingMsg_AI (467U)
 *   NTC_Num_MissingMsg_AJ (473U)
 *   NTC_Num_MissingMsg_AK (481U)
 *   NTC_Num_MissingMsg_AL (489U)
 *   NTC_Num_SysConsistencyVerf (496U)
 *   NTC_Num_ConfigMisMatch (497U)
 *   NTC_Num_CalNotPrgmd (498U)
 *   NTC_Num_EOLVehTunNtPerf (501U)
 *   NTC_Num_MtrSensorNotTrimmed (502U)
 *   NTC_Num_HWASensorNotTrimmed (504U)
 *   NTC_Num_HWASensorTrimNoAttempt (505U)
 *   NTC_Num_TrqSensorScaleNotSet (506U)
 *   NTC_Num_TrqSensorNotTrimmed (507U)
 *   NTC_Num_DigTrqSensorScaleNotSet (509U)
 *   NTC_Num_DigTrqSensorNotTrimmed (510U)
 * NxtrDiagMgrStatus: Enumeration of integer in interval [0...255] with enumerators
 *   NTC_STATUS_PASSED (0U)
 *   NTC_STATUS_FAILED (1U)
 *   NTC_STATUS_PREPASSED (2U)
 *   NTC_STATUS_PREFAILED (3U)
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
 * Double: D_SFINVMILLI_ULS_F32 = 1000
 * Float: D_100MS_SEC_F32 = 0.1F
 * Float: D_180OVRPI_ULS_F32 = 57.295779513082F
 * Float: D_2MS_SEC_F32 = 0.002F
 * Float: D_2PI_ULS_F32 = 6.2831853071796F
 * Float: D_MSECPERSEC_ULS_F32 = 1000.0F
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8F
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8F
 * Float: D_ONE_ULS_F32 = 1.0F
 * Float: D_PIOVR180_ULS_F32 = 0.0174532925199F
 * Float: D_PI_ULS_F32 = 3.1415926535898F
 * Float: D_RADPERREV_ULS_F32 = 6.28318530718F
 * Float: D_VECUMIN_VOLTS_F32 = 5.0F
 * Float: D_ZERO_ULS_F32 = 0.0F
 * SInt16: D_NEGONE_CNT_S16 = -1
 * SInt16: D_ONE_CNT_S16 = 1
 * SInt16: D_ZERO_CNT_S16 = 0
 * SInt32: D_NEGONE_CNT_S32 = -1
 * SInt32: D_ONE_CNT_S32 = 1
 * SInt32: D_ZERO_CNT_S32 = 0
 * SInt8: D_NEGONE_CNT_S8 = -1
 * SInt8: D_ONE_CNT_S8 = 1
 * SInt8: D_ZERO_CNT_S8 = 0
 * UInt16: D_ONE_CNT_U16 = 1U
 * UInt16: D_ZERO_CNT_U16 = 0U
 * UInt32: D_ONE_CNT_U32 = 1U
 * UInt32: D_ZERO_CNT_U32 = 0U
 * UInt8: D_MTRPOLESDIV2_CNT_U8 = 3U
 * UInt8: D_ONE_CNT_U8 = 1U
 * UInt8: D_QUADRANT1_CNT_U8 = 1U
 * UInt8: D_QUADRANT2_CNT_U8 = 2U
 * UInt8: D_QUADRANT3_CNT_U8 = 3U
 * UInt8: D_QUADRANT4_CNT_U8 = 4U
 * UInt8: D_ZERO_CNT_U8 = 0U
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_SRLCOMINPUT_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SrlComInput_Init
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
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_SRLCOMINPUT_APPL_CODE) SrlComInput_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SrlComInput_Init
 *********************************************************************************************************************/
	
	VAR(uint32, AUTOMATIC) SystemTime_mS_T_u32;
	
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&SystemTime_mS_T_u32);
	
	NTCEnableTimer_mS_M_u32 = SystemTime_mS_T_u32;

	(void) ResetTimers(SystemTime_mS_T_u32);
	
	CmdIgnStsPrev_Cnt_M_u8 = 0x00U;
	CfgCodeRequestReceived_Cnt_M_lgc = FALSE;
	OpModeStsCTCEnableCriteria_Cnt_M_lgc = FALSE;
	
	BCM_CheckforInvalid_Cnt_M_lgc = TRUE;
	BCM2_CheckforInvalid_Cnt_M_lgc = TRUE;
	MOT1_CheckforInvalid_Cnt_M_lgc = TRUE;
	IPC2_CheckforInvalid_Cnt_M_lgc = TRUE;
	
	NTC120IgnitionStartState_M_enum = INIT;
	NTC120IgnitionOffState_M_enum = INIT;
	NTC121IgnitionStartState_M_enum = INIT;
	NTC121IgnitionOffState_M_enum = INIT;

	InhibitNTCs_Cnt_M_lgc = TRUE;

	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SrlComInput_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------

 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_SrlComInput_Per1_Batt_Volt_f32(void)
 *   DT_BCM_Key_Sta Rte_IRead_SrlComInput_Per1_Com_BCM_Key_Sta_Cnt_enum(void)
 *   DT_CAN_N Rte_IRead_SrlComInput_Per1_Com_CAN_N_Cnt_u16(void)
 *   DT_LV_CAN_N_ERR Rte_IRead_SrlComInput_Per1_Com_LV_CAN_N_ERR_Cnt_lgc(void)
 *   DT_VehSpeed Rte_IRead_SrlComInput_Per1_Com_VehSpeed_Cnt_u16(void)
 *   Boolean Rte_IRead_SrlComInput_Per1_DefaultVehSpd_Cnt_lgc(void)
 *   Boolean Rte_IRead_SrlComInput_Per1_RxMsgsSrlComSvcDft_Cnt_lgc(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_SrlComInput_Per1_EngineSpeedSignalFailure_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_SrlComInput_Per1_EngineSpeedSignalFailure_Cnt_lgc(void)
 *   void Rte_IWrite_SrlComInput_Per1_EngineSpeed_Rpm_f32(Float data)
 *   Float *Rte_IWriteRef_SrlComInput_Per1_EngineSpeed_Rpm_f32(void)
 *   void Rte_IWrite_SrlComInput_Per1_SrlComVehSpd_Kph_f32(Float data)
 *   Float *Rte_IWriteRef_SrlComInput_Per1_SrlComVehSpd_Kph_f32(void)
 *   void Rte_IWrite_SrlComInput_Per1_VehicleSpeedValid_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_SrlComInput_Per1_VehicleSpeedValid_Cnt_lgc(void)
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
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_SRLCOMINPUT_APPL_CODE) SrlComInput_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SrlComInput_Per1
 *********************************************************************************************************************/
	
	VAR(boolean, AUTOMATIC) BCMCmdMMsg_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) BCM2MMsg_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) BSMMMsg_Cnt_T_lgc = FALSE;
	VAR(boolean, AUTOMATIC) BusOffCh1_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) CityModeSts_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) DisableFailSafeReaction_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) EpsEn_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) MOT1MMsg_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) MOT3MMsg_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) IPCMMsg_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) InvalidCmdIgnSts_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) InvalidEngSts_Cnt_T_u8;
	VAR(boolean, AUTOMATIC) InvalidOpModeSts_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) InvalidVehSpd_Cnt_T_lgc = FALSE;
	VAR(boolean, AUTOMATIC) RxMsgsSrlComSvcDft_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) VehicleSpeedValid_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) VehSpeedFailSts_Cnt_T_lgc;
	
	VAR(uint8,  AUTOMATIC) CRCB1_Cnt_T_u8;
	VAR(uint8,  AUTOMATIC) CmdIgnFailSts_Cnt_T_u8;
	VAR(uint8,  AUTOMATIC) EngSts_Cnt_T_u8;
	VAR(uint8,  AUTOMATIC) EngStartStopSts_Cnt_T_u8;
	VAR(uint8,  AUTOMATIC) ESLampFailSts_Cnt_T_u8;
	VAR(uint8,  AUTOMATIC) MsgCntB1_Cnt_T_u8;
	VAR(uint8,  AUTOMATIC) OpModeFailSts_Cnt_T_u8;
	VAR(uint8,  AUTOMATIC) StartStopSts_Cnt_T_u8;

	VAR(uint16,  AUTOMATIC) ElapsedTime_mS_T_u16;
	VAR(uint16,  AUTOMATIC) VehSpeed_Cnt_T_u16;

	VAR(uint16,  AUTOMATIC) BCM2IgnitionCounter_T_u32;

	VAR(uint32,  AUTOMATIC) SystemTime_mS_T_u32;
	VAR(uint32,  AUTOMATIC) TotalOdometer_Cnt_T_u32;
		
	VAR(float32, AUTOMATIC) Batt_Volt_T_f32;
	VAR(float32, AUTOMATIC) DefaultVehSpd_Cnt_T_lgc;
	
	VAR(DT_CmdIgnSts,  AUTOMATIC) CmdIgnSts_Cnt_T_u8;
	VAR(DT_OperationalModeSts,  AUTOMATIC) OpModeSts_Cnt_T_u8;
	VAR(DT_OperationalModeSts,  AUTOMATIC) OpModeStsInternal_Cnt_T_u8;
	VAR(ManufModeType, AUTOMATIC) MEC_Cnt_T_enum;
	VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC) SystemState_Cnt_T_enum;
	VAR(CityUserEnableDisable,  AUTOMATIC) CityUserEnableDisable_Cnt_T_enum;

	/* Read RTE signals */
	Batt_Volt_T_f32 = Rte_IRead_SrlComInput_Per1_Batt_Volt_f32();
	CityUserEnableDisable_Cnt_T_enum = Rte_IRead_SrlComInput_Per1_CityUserEnableDisable_Cnt_enum();
	DefaultVehSpd_Cnt_T_lgc = Rte_IRead_SrlComInput_Per1_DefaultVehSpd_Cnt_lgc();
	DisableFailSafeReaction_Cnt_T_lgc	= Rte_IRead_SrlComInput_Per1_DisableFailSafeReaction_Cnt_lgc();
	IgnitionPreStart_Cnt_M_lgc = Rte_IRead_SrlComInput_Per1_IgnitionPreStart_Cnt_lgc();
	MEC_Cnt_T_enum = Rte_IRead_SrlComInput_Per1_MEC_Cnt_enum();
	RxMsgsSrlComSvcDft_Cnt_T_lgc = Rte_IRead_SrlComInput_Per1_RxMsgsSrlComSvcDft_Cnt_lgc();
	(void)Rte_Call_EpsEn_OP_GET(&EpsEn_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_BusOffCh1, &BusOffCh1_Cnt_T_lgc);
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&SystemTime_mS_T_u32);
	SystemState_Cnt_T_enum = Rte_Mode_SystemState_Mode();

	/* Read Serial communication Messages */
	Com_ReceiveSignal(Com_CmdIgnSts__STATUS_C_BCM2__CCAN, &CmdIgnSts_Cnt_T_u8);
	Com_ReceiveSignal(Com_CmdIgn_FailSts__STATUS_C_BCM2__CCAN, &CmdIgnFailSts_Cnt_T_u8);
	Com_ReceiveSignal(Com_CRC_B1__BSM1__CCAN, &CRCB1_Cnt_T_u8);
	Com_ReceiveSignal(Com_ElectricSteeringLamp_FailSts__STATUS_C_IPC__CCAN, &ESLampFailSts_Cnt_T_u8);
	Com_ReceiveSignal(Com_EngineStopStartSts__MOT3__CCAN, &EngStartStopSts_Cnt_T_u8);
	Com_ReceiveSignal(Com_EngineSts__MOT1__CCAN, &EngSts_Cnt_T_u8);
	Com_ReceiveSignal(Com_MessageCounter_B1__BSM1__CCAN, &MsgCntB1_Cnt_T_u8);
	Com_ReceiveSignal(Com_OperationalModeSts__BCM_COMMAND__CCAN, &OpModeSts_Cnt_T_u8);
	Com_ReceiveSignal(Com_StopStartSts__MOT3__CCAN, &StartStopSts_Cnt_T_u8);
	Com_ReceiveSignal(Com_TotalOdometer__STATUS_C_IPC__CCAN, &TotalOdometer_Cnt_T_u32);
	Com_ReceiveSignal(Com_VehicleSpeedVSOSig__BSM1__CCAN, &VehSpeed_Cnt_T_u16);
	Com_ReceiveSignal(Com_VehicleSpeedVSOSigFailSts__BSM1__CCAN, &VehSpeedFailSts_Cnt_T_lgc);

	/* CityModeSts */
	switch(CityUserEnableDisable_Cnt_T_enum)
	{
		case ReturnControlToECU:
			/* $2F service - DidServices_0x5aab_ReturnControlToECU */
			Com_ReceiveSignal(Com_CityModeSts__STATUS_C_BCM2__CCAN, &CityModeSts_Cnt_T_lgc);
			break;

		case ResetToDefault:
			/* $2F service - DidServices_0x5aab_ResetToDefault */
			CityModeSts_Cnt_T_lgc = FALSE;
			break;

		case ShortTermAdjustment:
			/* $2F service - DidServices_0x5aab_ShortTermAdjustment */
			CityModeSts_Cnt_T_lgc = TRUE;
			break;

		default:
			Com_ReceiveSignal(Com_CityModeSts__STATUS_C_BCM2__CCAN, &CityModeSts_Cnt_T_lgc);
			break;
	}

	SystemTime_mS_M_u32 = SystemTime_mS_T_u32;
	OpModeStsInternal_Cnt_T_u8 = OpModeSts_Cnt_T_u8;

	MsgCntB1Prev_Cnt_M_u8 = MsgCntB1_Cnt_M_u8;
	(CmdIgnSts_Cnt_T_u8 != CmdIgnSts_Cnt_M_u8) ? (CmdIgnStsPrev_Cnt_M_u8 = CmdIgnSts_Cnt_M_u8) : (CmdIgnStsPrev_Cnt_M_u8 = CmdIgnStsPrev_Cnt_M_u8);
	(OpModeSts_Cnt_T_u8 != OpModeSts_Cnt_M_u8) ? (OpModeStsPrev_Cnt_M_u8 = OpModeSts_Cnt_M_u8) : (OpModeStsPrev_Cnt_M_u8 = OpModeStsPrev_Cnt_M_u8);
	
	if( BCM2MsgMissing_Cnt_M_lgc == TRUE )
	{
		CmdIgnFailSts_Cnt_T_u8 = CmdIgnFailStsInternal_Cnt_M_u8;
	}

	/* CTC Enable TImer */
	if( (OpModeStsPrev_Cnt_M_u8 == 0x07U) && (OpModeSts_Cnt_T_u8 == 0x08U) )
	{
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(CTCEnableTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( ElapsedTime_mS_T_u16 > k_CTCEnableTimeout_mS_u16)
		{
			CTCEnableTimer_mS_M_u32 = SystemTime_mS_T_u32;
			OpModeStsCTCEnableCriteria_Cnt_M_lgc = TRUE;
		}
	}

	else
	{
		CTCEnableTimer_mS_M_u32 = SystemTime_mS_T_u32;
	}

	/*	Check for Invalid Messages */
	/* Reset the Invalid Msg Timer */

	/* Invalid BCM_COMMAND Message (Msg ID $0FA) */
	if( (OpModeSts_Cnt_T_u8 == 0x0FU) && (BCM_CheckforInvalid_Cnt_M_lgc == TRUE) )
	{
		Rte_Call_SystemTime_GetSystemTime_mS_u32(&BCM_CMDInvMsgTimer_mS_M_u32);
		BCM_CheckforInvalid_Cnt_M_lgc = FALSE;
	}

	/* Invalid MOT1 Message (Msg ID $0E6) */
	if( (EngSts_Cnt_T_u8 == 0x03U) && (MOT1_CheckforInvalid_Cnt_M_lgc == TRUE) )
	{
		Rte_Call_SystemTime_GetSystemTime_mS_u32(&MOT1InvMsgTimer_mS_M_u32);
		MOT1_CheckforInvalid_Cnt_M_lgc = FALSE;
	}
	
	/* Invalid STATUS_C_BCM2 Message (Msg ID $4B4) */
	if( ( (CmdIgnSts_Cnt_T_u8 == 0x07U) || (CmdIgnFailSts_Cnt_T_u8 != 0x00U) ) && (BCM2_CheckforInvalid_Cnt_M_lgc == TRUE) )
	{
		Rte_Call_SystemTime_GetSystemTime_mS_u32(&BCM2InvMsgTimer_mS_M_u32);
		BCM2_CheckforInvalid_Cnt_M_lgc = FALSE;
	}

	/* Invalid Status_C_IPC Message (Msg ID $419) */
	if( (ESLampFailSts_Cnt_T_u8 == 0x03U) && (IPC2_CheckforInvalid_Cnt_M_lgc == TRUE) )
	{
		Rte_Call_SystemTime_GetSystemTime_mS_u32(&IPCInvMsgTimer_mS_M_u32);
		IPC2_CheckforInvalid_Cnt_M_lgc = FALSE;
	}
	
	/* COM Enable */
	if( EpsEn_Cnt_T_lgc != PrevEpsEn_Cnt_M_lgc )
	{
		if( EpsEn_Cnt_T_lgc == TRUE )
		{
			(void)Rte_Call_ComM_UserRequest_RequestComMode(COMM_FULL_COMMUNICATION);
		}
		else
		{
			(void)Rte_Call_ComM_UserRequest_RequestComMode(COMM_NO_COMMUNICATION);
		}
		
		PrevEpsEn_Cnt_M_lgc = EpsEn_Cnt_T_lgc;
	}
	
	if( FALSE == RxMsgsSrlComSvcDft_Cnt_T_lgc )
	{
		/*** BCM_COMMAND -- 0x0FA ***/

		/*** BSM1 -- 0x0F2 ***/
		VehSpeed_Cnt_M_u16 = VehSpeed_Cnt_T_u16;
		VehSpeedFailSts_Cnt_M_lgc = VehSpeedFailSts_Cnt_T_lgc;
		CRCB1_Cnt_M_u8 = CRCB1_Cnt_T_u8;
		
		/*** MOT1 -- 0x0E6 ***/

		/*** MOT3 -- 0x2EE ***/
		EngStartStopSts_Cnt_M_u8 = EngStartStopSts_Cnt_T_u8;
		StartStopSts_Cnt_M_u8 = StartStopSts_Cnt_T_u8;

		/*** Status C BCM2 -- 0x4B4 ***/
		CityModeSts_Cnt_M_lgc = CityModeSts_Cnt_T_lgc;
		CmdIgnFailSts_Cnt_M_u8 = CmdIgnFailSts_Cnt_T_u8;

		/*** Status_C_IPC -- 0x419 ***/
		ESLampFailSts_Cnt_M_u8 = ESLampFailSts_Cnt_T_u8;
		
		if( VehSpeed_Cnt_T_u16 <= 0x1FFF )
		{
			SrlComVehSpd_Kph_M_f32 = ((float32)VehSpeed_Cnt_T_u16) * D_VEHSPDSCALE_CNT_F32;
		}
	}
	else
	{		
		/* ABS2 Defaults */
		SrlComVehSpd_Kph_M_f32 = ManVehSpd_Kph_M_f32;
		VehicleSpeedValid_Cnt_T_lgc = TRUE;
	}
	
	/* NTC Enable Criteria */
	if( (Batt_Volt_T_f32 > 9.0f) &&
		(BusOffCh1_Cnt_T_lgc == FALSE) &&
		(MEC_Cnt_T_enum != ManufacturingMode) &&
		((SystemState_Cnt_T_enum == RTE_MODE_StaMd_Mode_OPERATE) || (SystemState_Cnt_T_enum ==RTE_MODE_StaMd_Mode_DISABLE) 
		|| (SystemState_Cnt_T_enum ==RTE_MODE_StaMd_Mode_WARMINIT)) )
	{
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(NTCEnableTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( ElapsedTime_mS_T_u16 >= k_NTCEnableTimeout_mS_u16 )
		{
			InhibitNTCs_Cnt_M_lgc = FALSE;
		}
	}
	else
	{
		NTCEnableTimer_mS_M_u32 = SystemTime_mS_M_u32;
		InhibitNTCs_Cnt_M_lgc = TRUE;
		OpModeSts_Cnt_T_u8 = OpModeStsPrev_Cnt_M_u8;
	}
	
	if( InhibitNTCs_Cnt_M_lgc == FALSE )
	{
		/* NTC $120 - Invalid OpModeSts */
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(BCM_CMDInvMsgTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( (OpModeSts_Cnt_T_u8 == 0x0FU) )
		{
			if ( ElapsedTime_mS_T_u16 > k_BCMInvMsgTimeout_mS_u16 )
			{
				BCM_CMDInvMsgTimer_mS_M_u32 = SystemTime_mS_M_u32 + k_BCMInvMsgTimeout_mS_u16;

				NTC120Parameter_Cnt_M_u8 = 0x00U;

				/* NTC $120 Parameter 2 */
				if( ( (CmdIgnStsPrev_Cnt_M_u8 == 0x01U) || (CmdIgnStsPrev_Cnt_M_u8 == 0x04U) ) &&
						(CmdIgnSts_Cnt_T_u8 == 0x05U) && (CmdIgnFailSts_Cnt_T_u8 != 0x01U) && (EngSts_Cnt_T_u8 == 0x00U) && (IgnitionPreStart_Cnt_M_lgc == TRUE) )  
				{
					NTC120Parameter_Cnt_M_u8 = 0x04U;
						
					switch(NTC120IgnitionStartState_M_enum)
					{
						case INIT: 
							OpModeStsInternal_Cnt_T_u8 = 0x05U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
							Rte_Call_SystemTime_GetSystemTime_mS_u32(&BCM_CMDInvMsgTimer1_mS_M_u32);
							NTC120IgnitionStartState_M_enum = INIT_COMPLETE;
							break;
							
						case INIT_COMPLETE: 
							OpModeStsInternal_Cnt_T_u8 = 0x05U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
							Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(BCM_CMDInvMsgTimer1_mS_M_u32, &ElapsedTime_mS_T_u16);
							if( (ElapsedTime_mS_T_u16 > k_BCMMsgPreIgnitionStart_ms_u16) )
							{
								BCM_CMDInvMsgTimer1_mS_M_u32 = SystemTime_mS_M_u32;
								NTC120IgnitionStartState_M_enum = START;
							}
							break;
							
						case START:
							OpModeStsInternal_Cnt_T_u8 = 0x06U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
							break;

            default:
              break;
					}
				}
					
				/* NTC $120 Parameter 3 */
				else if( (CmdIgnSts_Cnt_T_u8 == 0x05U) && (CmdIgnFailSts_Cnt_T_u8 != 0x01U) && (EngSts_Cnt_T_u8 == 0x00U) && (OpModeStsInternal_Cnt_T_u8 != 0x05U) ) 
				{
					NTC120Parameter_Cnt_M_u8 = 0x08U;
					OpModeStsInternal_Cnt_T_u8 = 0x06U;
					OpModeFailSts_Cnt_T_u8 = 0x00U;
				}
					
				else
				{
					NTC120IgnitionStartState_M_enum = INIT;
					/* NTC $120 Parameter 5 */
					if( ( (CmdIgnStsPrev_Cnt_M_u8 == 0x04U) || (CmdIgnStsPrev_Cnt_M_u8 == 0x05U) ) && (CmdIgnSts_Cnt_T_u8 == 0x01U) )
					{
						NTC120Parameter_Cnt_M_u8 = 0x20U;
					
						switch(NTC120IgnitionOffState_M_enum)
						{
							case INIT:
								OpModeStsInternal_Cnt_T_u8 = 0x0AU;
								OpModeFailSts_Cnt_T_u8 = 0x00U;
								Rte_Call_SystemTime_GetSystemTime_mS_u32(&BCM_CMDInvMsgTimer2_mS_M_u32);
								NTC120IgnitionOffState_M_enum = INIT_COMPLETE;
								break;

							case INIT_COMPLETE:
								OpModeStsInternal_Cnt_T_u8 = 0x0AU;
								OpModeFailSts_Cnt_T_u8 = 0x00U;
								Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(BCM_CMDInvMsgTimer2_mS_M_u32, &ElapsedTime_mS_T_u16);
								if( (ElapsedTime_mS_T_u16 > k_BCMMsgPreIgnitionStart_ms_u16) )
								{
									BCM_CMDInvMsgTimer2_mS_M_u32 = SystemTime_mS_M_u32;
									NTC120IgnitionOffState_M_enum = START;
								}
								break;

							case START:
								OpModeStsInternal_Cnt_T_u8 = 0x02U;
								OpModeFailSts_Cnt_T_u8 = 0x00U;
								break;

              default:
                break;
						}
					}

					/* NTC $120 Parameter 6 */
					else if( (CmdIgnSts_Cnt_T_u8 == 0x01U) && (OpModeStsInternal_Cnt_T_u8 != 0x0AU) )
					{
						NTC120Parameter_Cnt_M_u8 = 0x40U;
						OpModeStsInternal_Cnt_T_u8 = 0x02U;
						OpModeFailSts_Cnt_T_u8 = 0x00U;
					}

					else
					{
						NTC120IgnitionOffState_M_enum = INIT;

						/* NTC $120 Parameter 0 */
						if( (CmdIgnSts_Cnt_T_u8 == 0x04U) && (EngSts_Cnt_T_u8 == 0x02U) )
						{
							NTC120Parameter_Cnt_M_u8 = 0x01U;
							OpModeStsInternal_Cnt_T_u8 = 0x08U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
						}

						/* NTC $120 Parameter 1 */
						if( ( (CmdIgnSts_Cnt_T_u8 == 0x05U) || (CmdIgnSts_Cnt_T_u8 == 0x04U) ) && (EngSts_Cnt_T_u8 == 0x01U) )
						{
							NTC120Parameter_Cnt_M_u8 = 0x02U;
							OpModeStsInternal_Cnt_T_u8 = 0x07U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
						}
						
						/* NTC $120 Parameter 4 */
						if( ( (CmdIgnSts_Cnt_T_u8 == 0x04U) || (CmdIgnFailSts_Cnt_T_u8 == 0x01U) ) && (EngSts_Cnt_T_u8 == 0x00U) )
						{
							NTC120Parameter_Cnt_M_u8 = 0x10U;
							OpModeStsInternal_Cnt_T_u8 = 0x04U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
						}

						/* NTC $120 Parameter 7 */
						if( ( (CmdIgnSts_Cnt_T_u8 == 0x04U) || (CmdIgnSts_Cnt_T_u8 == 0x05U) ) && (EngSts_Cnt_T_u8 == 0x03U) )
						{
							NTC120Parameter_Cnt_M_u8 = 0x80U;
							OpModeStsInternal_Cnt_T_u8 = 0x0FU;
							OpModeFailSts_Cnt_T_u8 = 0x01U;
						}
					}
				}

				if( NTC120Parameter_Cnt_M_u8 == 0x00U)
				{
					OpModeStsInternal_Cnt_T_u8 = OpModeSts_Cnt_T_u8;
					OpModeFailSts_Cnt_T_u8 = 0x00U;
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_InvalidMsg_M, NTC120Parameter_Cnt_M_u8, NTC_STATUS_PASSED);
				}

				else
				{
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_InvalidMsg_M, NTC120Parameter_Cnt_M_u8, NTC_STATUS_FAILED);
				}
			}
			else
			{
				OpModeStsInternal_Cnt_T_u8 = OpModeSts_Cnt_M_u8;
				OpModeFailSts_Cnt_T_u8 = OpModeFailSts_Cnt_M_u8;
			}
		}

		else
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_InvalidMsg_M, NTC120Parameter_Cnt_M_u8, NTC_STATUS_PASSED);
			OpModeStsInternal_Cnt_T_u8 = OpModeSts_Cnt_T_u8;
			OpModeFailSts_Cnt_T_u8 = 0x00U;
			
			BCM_CheckforInvalid_Cnt_M_lgc = TRUE;
			BCM_CMDInvMsgTimer_mS_M_u32 = SystemTime_mS_M_u32;
			BCM_CMDInvMsgTimer1_mS_M_u32 = SystemTime_mS_M_u32;
			BCM_CMDInvMsgTimer2_mS_M_u32 = SystemTime_mS_M_u32;
			NTC120Parameter_Cnt_M_u8 = 0x00U;
			NTC120IgnitionStartState_M_enum = INIT;
			NTC120IgnitionOffState_M_enum = INIT;
		}

		/* NTC $121 - Missing BCM_COMMAND Message (Msg ID $0FA) */
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(BCM_CMDMMsgTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( ElapsedTime_mS_T_u16 > k_BCM_CMDMsgTimeout_mS_u16 )
		{
			BCMCMDMsgMissing_Cnt_M_lgc = TRUE;
			BCM_CMDMMsgTimer_mS_M_u32 = SystemTime_mS_M_u32 + k_BCM_CMDMsgTimeout_mS_u16;

			NTC121Parameter_Cnt_M_u8 = 0x00U;

			/* Parameter 2 */
			if( ( (CmdIgnStsPrev_Cnt_M_u8 == 0x01U) || (CmdIgnStsPrev_Cnt_M_u8 == 0x04U) ) &&
					(CmdIgnSts_Cnt_T_u8 == 0x05U) && (CmdIgnFailSts_Cnt_T_u8 != 0x01U) && (EngSts_Cnt_T_u8 == 0x00U) && (IgnitionPreStart_Cnt_M_lgc == TRUE) )
			{
				NTC121Parameter_Cnt_M_u8 = 0x04U;

				switch(NTC121IgnitionStartState_M_enum)
				{
					case INIT:
						if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
						{
							OpModeStsInternal_Cnt_T_u8 = 0x05U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
						}
						Rte_Call_SystemTime_GetSystemTime_mS_u32(&BCM_CMDMMsgTimer1_mS_M_u32);
						NTC121IgnitionStartState_M_enum = INIT_COMPLETE;
						break;

					case INIT_COMPLETE:
						if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
						{
							OpModeStsInternal_Cnt_T_u8 = 0x05U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
						}
						Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(BCM_CMDMMsgTimer1_mS_M_u32, &ElapsedTime_mS_T_u16);
						if( (ElapsedTime_mS_T_u16 > k_BCMMsgPreIgnitionStart_ms_u16) )
						{
							BCM_CMDMMsgTimer1_mS_M_u32 = SystemTime_mS_M_u32;
							NTC121IgnitionStartState_M_enum = START;
						}
						break;

					case START:
						if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
						{
							OpModeStsInternal_Cnt_T_u8 = 0x06U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
						}
						break;

          default:
            break;
				}
			}
				
			/* NTC $121 Parameter 3 */
			else if( (CmdIgnSts_Cnt_T_u8 == 0x05U) && (CmdIgnFailSts_Cnt_T_u8 != 0x01U) && (EngSts_Cnt_T_u8 == 0x00U) && (OpModeStsInternal_Cnt_T_u8 != 0x05U) )
			{
				NTC121Parameter_Cnt_M_u8 = 0x08U;
				if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
				{
					OpModeStsInternal_Cnt_T_u8 = 0x06U;
					OpModeFailSts_Cnt_T_u8 = 0x00U;
				}
			}

			else
			{
				NTC121IgnitionStartState_M_enum = INIT;
				
				/* NTC $121 Parameter 5 */
				if( ( (CmdIgnStsPrev_Cnt_M_u8 == 0x04U) || (CmdIgnStsPrev_Cnt_M_u8 == 0x05U) ) && (CmdIgnSts_Cnt_T_u8 == 0x01U) )
				{
					NTC121Parameter_Cnt_M_u8 = 0x20U;
					
					switch(NTC121IgnitionOffState_M_enum)
					{
						case INIT:
							if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
							{
								OpModeStsInternal_Cnt_T_u8 = 0x0AU;
								OpModeFailSts_Cnt_T_u8 = 0x00U;
							}
							Rte_Call_SystemTime_GetSystemTime_mS_u32(&BCM_CMDMMsgTimer2_mS_M_u32);
							NTC121IgnitionOffState_M_enum = INIT_COMPLETE;
							break;

						case INIT_COMPLETE:
							if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
							{
								OpModeStsInternal_Cnt_T_u8 = 0x0AU;
								OpModeFailSts_Cnt_T_u8 = 0x00U;
							}
							Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(BCM_CMDMMsgTimer2_mS_M_u32, &ElapsedTime_mS_T_u16);
							if( (ElapsedTime_mS_T_u16 > k_BCMMsgPreIgnitionStart_ms_u16) )
							{
								BCM_CMDMMsgTimer2_mS_M_u32 = SystemTime_mS_M_u32;
								NTC121IgnitionOffState_M_enum = START;
							}
							break;

						case START:
							if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
							{
								OpModeStsInternal_Cnt_T_u8 = 0x02U;
								OpModeFailSts_Cnt_T_u8 = 0x00U;
							}
							break;

            default:
              break;
					}
				}

				/* NTC $121 Parameter 6 */
				else if( (CmdIgnSts_Cnt_T_u8 == 0x01U) && (OpModeStsInternal_Cnt_T_u8 != 0x0AU) )
				{
					NTC121Parameter_Cnt_M_u8 = 0x40U;
					if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
					{
						OpModeStsInternal_Cnt_T_u8 = 0x02U;
						OpModeFailSts_Cnt_T_u8 = 0x00U;
					}
				}
				
				else
				{
					NTC121IgnitionOffState_M_enum = INIT;

					/* NTC $121 Parameter 0 */
					if( (CmdIgnSts_Cnt_T_u8 == 0x04U) && (EngSts_Cnt_T_u8 == 0x02U) )
					{
						NTC121Parameter_Cnt_M_u8 = 0x01U;
						if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
						{
							OpModeStsInternal_Cnt_T_u8 = 0x08U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
						}
					}

					/* NTC $121 Parameter 1 */
					if( ( (CmdIgnSts_Cnt_T_u8 == 0x05U) || (CmdIgnSts_Cnt_T_u8 == 0x04U) ) && (EngSts_Cnt_T_u8 == 0x01U) )
					{
						NTC121Parameter_Cnt_M_u8 = 0x02U;
						if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
							{
							OpModeStsInternal_Cnt_T_u8 = 0x07U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
						}
					}

					/* NTC $121 Parameter 4 */
					if( ( (CmdIgnSts_Cnt_T_u8 == 0x04U) || (CmdIgnFailSts_Cnt_T_u8 == 0x01U) ) && (EngSts_Cnt_T_u8 == 0x00U) )
					{
						NTC121Parameter_Cnt_M_u8 = 0x10U;
						if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
						{
							OpModeStsInternal_Cnt_T_u8 = 0x04U;
							OpModeFailSts_Cnt_T_u8 = 0x00U;
						}
					}

					/* NTC $121 Parameter 7 */
					if( ( (CmdIgnSts_Cnt_T_u8 == 0x04U) || (CmdIgnSts_Cnt_T_u8 == 0x05U) ) && (EngSts_Cnt_T_u8 == 0x03U) )
					{
						NTC121Parameter_Cnt_M_u8 = 0x80U;
						if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
						{
							OpModeStsInternal_Cnt_T_u8 = 0x0FU;
							OpModeFailSts_Cnt_T_u8 = 0x01U;
						}
					}
				}
			}

			if( NTC121Parameter_Cnt_M_u8 == 0x00U)
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_M, NTC121Parameter_Cnt_M_u8, NTC_STATUS_PASSED);
			}

			else
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_M, NTC121Parameter_Cnt_M_u8, NTC_STATUS_FAILED);
			}

		}

		/* NTC $128 - Invalid Vehicle Speed */
		if( (VehSpeed_Cnt_T_u16 == 0x1FFFU) || (TRUE == VehSpeedFailSts_Cnt_T_lgc) )
		{
			VehSpeedSigFltAcc_Cnt_M_u16 = DiagPStep_m(VehSpeedSigFltAcc_Cnt_M_u16, k_VehSpeedSigDiag_Cnt_str);
			if( DiagFailed_m(VehSpeedSigFltAcc_Cnt_M_u16, k_VehSpeedSigDiag_Cnt_str) == TRUE )
			{
				if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
				{
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_InvalidMsg_N, 0x01, NTC_STATUS_FAILED);
				}
			}
		}

		else
		{
			VehSpeedSigFltAcc_Cnt_M_u16 = DiagNStep_m(VehSpeedSigFltAcc_Cnt_M_u16, k_VehSpeedSigDiag_Cnt_str);
			if( VehSpeedSigFltAcc_Cnt_M_u16 == 0u )
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_InvalidMsg_N, 0x01, NTC_STATUS_PASSED);
			}
		}

		/* NTC $129 - Missing BSM1 Message (Msg ID $0F2) */
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(BSM1MMsgTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( ElapsedTime_mS_T_u16 > k_BSM1MsgTimeout_mS_u16 )
		{
			BSMMsgMissing_Cnt_M_lgc = TRUE;
			BSM1MMsgTimer_mS_M_u32 = SystemTime_mS_M_u32 + k_BSM1MsgTimeout_mS_u16;
			if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_N, 0x01, NTC_STATUS_FAILED);
			}
		}
		
		/* NTC $12A - BSM1 CRC Fault (Msg ID $0F2) */
		CalculatedCRCB1_Cnt_M_u8 = BSM1MsgCalculateCRC();
		if( BSMMsgMissing_Cnt_M_lgc == FALSE )
		{
			if( CalculatedCRCB1_Cnt_M_u8 != CRCB1_Cnt_T_u8 )
			{
				BSM1CRCFltAcc_Cnt_M_u16 = DiagPStep_m(BSM1CRCFltAcc_Cnt_M_u16, k_BSM1CRCDiag_Cnt_str);
				if( DiagFailed_m(BSM1CRCFltAcc_Cnt_M_u16, k_BSM1CRCDiag_Cnt_str) == TRUE )
				{
					if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
					{
						(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_CRCFltMsg_N, 0x01, NTC_STATUS_FAILED);
					}
				}
			}

			else
			{
				BSM1CRCFltAcc_Cnt_M_u16 = DiagNStep_m(BSM1CRCFltAcc_Cnt_M_u16, k_BSM1CRCDiag_Cnt_str);
				if( BSM1CRCFltAcc_Cnt_M_u16 == 0u )
				{
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_CRCFltMsg_N, 0x01, NTC_STATUS_PASSED);
				}
			}
		}


		/* NTC $12B - BSM1 Progress Counter Fault (Msg ID $0F2) */
		if( BSMMsgMissing_Cnt_M_lgc == FALSE )
		{
			if( VldtRollgCntr(MsgCntB1_Cnt_T_u8, MsgCntB1Prev_Cnt_M_u8) == FALSE )
			{
				BSM1MsgCounterFltAcc_Cnt_M_u16 = DiagPStep_m(BSM1MsgCounterFltAcc_Cnt_M_u16, k_BSM1MsgCounterDiag_Cnt_str);
				if( DiagFailed_m(BSM1MsgCounterFltAcc_Cnt_M_u16, k_BSM1MsgCounterDiag_Cnt_str) == TRUE )
				{
					if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
					{
						(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PgrsCntFltMsg_N, 0x01, NTC_STATUS_FAILED);
					}
				}
			}

			else
			{
				BSM1MsgCounterFltAcc_Cnt_M_u16 = DiagNStep_m(BSM1MsgCounterFltAcc_Cnt_M_u16, k_BSM1MsgCounterDiag_Cnt_str);
				if( BSM1MsgCounterFltAcc_Cnt_M_u16 == 0u )
				{
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PgrsCntFltMsg_N, 0x01, NTC_STATUS_PASSED);
				}
			}
		}


		/* NTC $130 - Invalid Engine Status */
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(MOT1InvMsgTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( EngSts_Cnt_T_u8 == 0x03U )
		{
			if( ElapsedTime_mS_T_u16 > k_MOT1InvMsgTimeout_mS_u16 )
			{
				MOT1InvMsgTimer_mS_M_u32 = SystemTime_mS_M_u32 + k_MOT1InvMsgTimeout_mS_u16;
				if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
				{
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_InvalidMsg_O, 0x01, NTC_STATUS_FAILED);
					EngSts_Cnt_T_u8 = 0x0U;
				}
			}

			else
			{
				EngSts_Cnt_T_u8 = EngSts_Cnt_M_u8;
			}
		}

		else
		{
			MOT1_CheckforInvalid_Cnt_M_lgc = TRUE;
			MOT1InvMsgTimer_mS_M_u32 = SystemTime_mS_M_u32;
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_InvalidMsg_O, 0x01, NTC_STATUS_PASSED);
		}


		/* NTC $131 - Missing MOT1 Message (Msg ID $0E6) */
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(MOT1MMsgTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( (ElapsedTime_mS_T_u16 > k_MOT1MsgTimeout_mS_u16) && (OpModeSts_Cnt_T_u8 == 0x0FU) )
		{
			MOT1MsgMissing_Cnt_M_lgc = TRUE;
			MOT1MMsgTimer_mS_M_u32 = SystemTime_mS_M_u32 + k_MOT1MsgTimeout_mS_u16;

			if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
			{
				OpModeStsInternal_Cnt_T_u8 = 0x0FU;
				OpModeFailSts_Cnt_T_u8 = 0x01;
			}
				
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_O, 0x01, NTC_STATUS_FAILED);
		}
		
		/* NTC $139 - Missing MOT3 Message (Msg ID $2EE) */
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(MOT3MMsgTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( ElapsedTime_mS_T_u16 > k_MOT3MsgTimeout_mS_u16 )
		{
			MOT3MMsgTimer_mS_M_u32 = SystemTime_mS_M_u32 + k_MOT3MsgTimeout_mS_u16;
			if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_P, 0x01, NTC_STATUS_FAILED);
			}
		}


		/* NTC $140 - Invalid CmdIgn Status */
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(BCM2InvMsgTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( (CmdIgnFailSts_Cnt_T_u8 != 0x00U) || (CmdIgnSts_Cnt_T_u8 == 0x07U) )
		{
			if( ElapsedTime_mS_T_u16 > k_BCM2InvMsgTimeout_mS_u16 )
			{
				BCM2InvMsgTimer_mS_M_u32 = SystemTime_mS_M_u32 + k_BCM2InvMsgTimeout_mS_u16;
				if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
				{
					CmdIgnSts_Cnt_T_u8 = 0x07U;
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_InvalidMsg_Q, 0x01, NTC_STATUS_FAILED);
				}
			}

			else
			{
				CmdIgnSts_Cnt_T_u8 = CmdIgnSts_Cnt_M_u8;
			}
		}

		else
		{
			BCM2_CheckforInvalid_Cnt_M_lgc = TRUE;
			BCM2InvMsgTimer_mS_M_u32 = SystemTime_mS_M_u32;
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_InvalidMsg_Q, 0x01, NTC_STATUS_PASSED);
		}


		/* NTC $141 - Missing STATUS_C_BCM2 Message (Msg ID $4B4) */
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(BCM2MMsgTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( ElapsedTime_mS_T_u16 > k_BCM2MsgTimeout_mS_u16 )
		{
			BCM2MsgMissing_Cnt_M_lgc = TRUE;
			BCM2MMsgTimer_mS_M_u32 = SystemTime_mS_M_u32 + k_BCM2MsgTimeout_mS_u16;
			
			CmdIgnSts_Cnt_T_u8 = 0x07U;

			if (OpModeSts_Cnt_T_u8 == 0x0Fu)
			{
				if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
				{
					OpModeFailSts_Cnt_M_u8 = 0x01U;
				}
				NTC141Parameter_Cnt_M_u8 = 0x02U;
			}

			else
			{
				if(DisableFailSafeReaction_Cnt_T_lgc == FALSE)
				{
					CmdIgnFailStsInternal_Cnt_M_u8 = 0x03U;
				}
				NTC141Parameter_Cnt_M_u8 = 0x01U;
			}

			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_Q, NTC141Parameter_Cnt_M_u8, NTC_STATUS_FAILED);
		}
		
		/* NTC $148 - Invalid Electric Steering Lamp Fail Status */
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(IPCInvMsgTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( ESLampFailSts_Cnt_T_u8 == 0x03U )
		{
			if( ElapsedTime_mS_T_u16 > k_IPCInvMsgTimeout_mS_u16 )
			{
				IPCInvMsgTimer_mS_M_u32 = SystemTime_mS_M_u32 + k_IPCInvMsgTimeout_mS_u16;
				if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
				{
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_InvalidMsg_R, 0x01, NTC_STATUS_FAILED);
				}
			}
		}

		else
		{
			IPC2_CheckforInvalid_Cnt_M_lgc = TRUE;
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_InvalidMsg_R, 0x01, NTC_STATUS_PASSED);
		}


		/* NTC $149 - Missing STATUS_C_IPC Message (Msg ID $419) */
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(IPCMMsgTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( ElapsedTime_mS_T_u16 > k_IPCMsgTimeout_mS_u16 )
		{
			IPCMMsgTimer_mS_M_u32 = SystemTime_mS_M_u32 + k_IPCMsgTimeout_mS_u16;
			if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_R, 0x01, NTC_STATUS_FAILED);
			}
		}
		

		/* NTC 151 - Missing BCM_CMD, MOT1 message and Missing BCM2 message */
		if ( (BCMCMDMsgMissing_Cnt_M_lgc == TRUE) && ( (BCM2MsgMissing_Cnt_M_lgc == TRUE) || (MOT1MsgMissing_Cnt_M_lgc == TRUE) ) )
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_S, 0x01, NTC_STATUS_FAILED);
		}
		else
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_S, 0x01, NTC_STATUS_PASSED);
		}

		/* NTC $159 - CmdIgn Sts is Run and no Proxi */
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(CfgCodeMsgTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( (CfgCodeRequestReceived_Cnt_M_lgc == FALSE) && (CmdIgnSts_Cnt_T_u8 == 0x04U) )
		{
			if( ElapsedTime_mS_T_u16 > k_CfgCodeMsgTimeout_mS_u16 )
			{
				CfgCodeMsgTimer_mS_M_u32 = SystemTime_mS_M_u32 + k_CfgCodeMsgTimeout_mS_u16;
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_T, 0x01, NTC_STATUS_FAILED);
			}
		}

		else
		{
			CfgCodeMsgTimer_mS_M_u32 = SystemTime_mS_M_u32;
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_T, 0x01, NTC_STATUS_PASSED);
		}

		(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_MissingMsg_M, &BCMCmdMMsg_Cnt_T_lgc);
		(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_MissingMsg_N, &BSMMMsg_Cnt_T_lgc);
		(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_MissingMsg_O, &MOT1MMsg_Cnt_T_lgc);
		(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_MissingMsg_P, &MOT3MMsg_Cnt_T_lgc);
		(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_MissingMsg_Q, &BCM2MMsg_Cnt_T_lgc);
		(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_MissingMsg_R, &IPCMMsg_Cnt_T_lgc);
		(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_InvalidMsg_N, &InvalidVehSpd_Cnt_T_lgc);
		
		/* NTC $102 and $103 BCM Node Faulty/Absent */
		if( (TRUE == BCMCmdMMsg_Cnt_T_lgc) && (TRUE == BCM2MMsg_Cnt_T_lgc) )
		{
			if( (FALSE == BcmNodeAbsent_Cnt_M_lgc) && (FALSE == BcmNodeFaulty_Cnt_M_lgc) )
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1AAbsent, 0x01, NTC_STATUS_FAILED);
				BcmNodeAbsent_Cnt_M_lgc = TRUE;
			}
			else
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1AFaulty, 0x01, NTC_STATUS_PASSED);
				BcmNodeFaulty_Cnt_M_lgc = FALSE;
			}

		}

		else
		{
			if( (TRUE == BCMCmdMMsg_Cnt_T_lgc) || (TRUE == BCM2MMsg_Cnt_T_lgc) )
			{
				if( (FALSE == BcmNodeAbsent_Cnt_M_lgc) && (FALSE == BcmNodeFaulty_Cnt_M_lgc) )
				{
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1AFaulty, 0x01, NTC_STATUS_FAILED);
					BcmNodeFaulty_Cnt_M_lgc = TRUE;
				}
			}
			else
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1AFaulty, 0x01, NTC_STATUS_PASSED);
				BcmNodeFaulty_Cnt_M_lgc = FALSE;
			}
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1AAbsent, 0x01, NTC_STATUS_PASSED);
			BcmNodeAbsent_Cnt_M_lgc = FALSE;

		}

		/* NTC $104 and $105 ECM Node Faulty/Absent */
		if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
		{
			if( (TRUE == MOT1MMsg_Cnt_T_lgc) && (TRUE == MOT3MMsg_Cnt_T_lgc) )
			{
				if( (FALSE == EcmNodeAbsent_Cnt_M_lgc) && (FALSE == EcmNodeFaulty_Cnt_M_lgc) )
				{
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1BAbsent, 0x01, NTC_STATUS_FAILED);
					EcmNodeAbsent_Cnt_M_lgc = TRUE;
				}
				else
				{
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1BFaulty, 0x01, NTC_STATUS_PASSED);
					EcmNodeFaulty_Cnt_M_lgc = FALSE;
				}
			}
			else
			{
				if( (TRUE == MOT1MMsg_Cnt_T_lgc) || (TRUE == MOT3MMsg_Cnt_T_lgc) )
				{
					if( (FALSE == EcmNodeAbsent_Cnt_M_lgc) && (FALSE == EcmNodeFaulty_Cnt_M_lgc) )
					{
						(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1BFaulty, 0x01, NTC_STATUS_FAILED);
						EcmNodeFaulty_Cnt_M_lgc = TRUE;
					}
				}
				else
				{
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1BFaulty, 0x01, NTC_STATUS_PASSED);
					EcmNodeFaulty_Cnt_M_lgc = FALSE;
				}
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1BAbsent, 0x01, NTC_STATUS_PASSED);
				EcmNodeAbsent_Cnt_M_lgc = FALSE;
			}
		}

		/* NTC $106 BSM Node Absent */
		if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
		{
			if(TRUE == BSMMMsg_Cnt_T_lgc)
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1CAbsent, 0x01, NTC_STATUS_FAILED);
			}
			else
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1CAbsent, 0x01, NTC_STATUS_PASSED);
			}
		}

		/* NTC $108 IPC Node Absent */
		if( (OpModeSts_Cnt_T_u8 == 0x04U) || (OpModeSts_Cnt_T_u8 == 0x08U) )
		{
			if(TRUE == IPCMMsg_Cnt_T_lgc)
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1DAbsent, 0x01, NTC_STATUS_FAILED);
			}
			else
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_Node1DAbsent, 0x01, NTC_STATUS_PASSED);
			}
		}
	}
	
	else
	{
		(void) ResetTimers(SystemTime_mS_T_u32);
	}
	
	/* Vehicle Speed and Validity */
	
	if( TRUE == RxMsgsSrlComSvcDft_Cnt_T_lgc )
	{
		/* do nothing */
	}
	else if( (DefaultVehSpd_Cnt_T_lgc == TRUE) ||
			 (BSMMMsg_Cnt_T_lgc == TRUE) )
	{
		SrlComVehSpd_Kph_M_f32 = k_DefaultVehSpd_Kph_f32;
		VehicleSpeedValid_Cnt_T_lgc = FALSE;
	}
	else if( InvalidVehSpd_Cnt_T_lgc == TRUE )
	{
		VehicleSpeedValid_Cnt_T_lgc = FALSE;
	}
	else
	{
		VehicleSpeedValid_Cnt_T_lgc = TRUE;
	}

	OpModeSts_Cnt_M_u8 = OpModeStsInternal_Cnt_T_u8;
	OpModeFailSts_Cnt_M_u8 = OpModeFailSts_Cnt_T_u8;
	EngSts_Cnt_M_u8 = EngSts_Cnt_T_u8;
	CmdIgnSts_Cnt_M_u8 = CmdIgnSts_Cnt_T_u8;
	MsgCntB1_Cnt_M_u8 = MsgCntB1_Cnt_T_u8;
	
	/* Tuning personality selection using CityModeSts */
	Rte_IWrite_SrlComInput_Per1_DesiredTunPers_Cnt_u16(CityModeSts_Cnt_T_lgc);
	
	Rte_IWrite_SrlComInput_Per1_CityModeSts_Cnt_lgc(CityModeSts_Cnt_T_lgc);
	Rte_IWrite_SrlComInput_Per1_SrlComVehSpd_Kph_f32(SrlComVehSpd_Kph_M_f32);
	Rte_IWrite_SrlComInput_Per1_VehicleSpeedValid_Cnt_lgc(VehicleSpeedValid_Cnt_T_lgc);
	Rte_IWrite_SrlComInput_Per1_CmdIgnSts_Cnt_u16(CmdIgnSts_Cnt_T_u8);
	Rte_IWrite_SrlComInput_Per1_OperationalModeSts_Cnt_u16(OpModeStsInternal_Cnt_T_u8);
	Rte_IWrite_SrlComInput_Per1_EngStartStopSts_Cnt_u8(EngStartStopSts_Cnt_M_u8);
	Rte_IWrite_SrlComInput_Per1_StartStopSts_Cnt_u8(StartStopSts_Cnt_M_u8);
	Rte_IWrite_SrlComInput_Per1_OpModeStsCTCEnableCriteria_Cnt_lgc(OpModeStsCTCEnableCriteria_Cnt_M_lgc);
	Rte_IWrite_SrlComInput_Per1_TotalOdometerIPC_Cnt_u32(TotalOdometer_Cnt_T_u32);
	Rte_IWrite_SrlComInput_Per1_CmdIgnFailSts_Cnt_u8(CmdIgnFailSts_Cnt_T_u8);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SrlComInput_SCom_ManualVehSpd
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ManualVehSpd> of PortPrototype <SrlComInput_SCom>
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
 *   void SrlComInput_SCom_ManualVehSpd(Float VehSpd_Kph_T_f32)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_SRLCOMINPUT_APPL_CODE) SrlComInput_SCom_ManualVehSpd(Float VehSpd_Kph_T_f32)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SrlComInput_SCom_ManualVehSpd
 *********************************************************************************************************************/
	
	
	ManVehSpd_Kph_M_f32 = VehSpd_Kph_T_f32;
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_SRLCOMINPUT_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

 /* NTC $121 - Missing BCM_COMMAND Message (Msg ID $0FA) */
FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_OperationalModeSts__BCM_COMMAND__CCAN(void)
{
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&BCM_CMDMMsgTimer_mS_M_u32);
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&BCM_CMDMMsgTimer1_mS_M_u32);
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&BCM_CMDMMsgTimer2_mS_M_u32);
	BCMCMDMsgMissing_Cnt_M_lgc = FALSE;
	NTC121IgnitionStartState_M_enum = INIT;
	NTC121IgnitionOffState_M_enum = INIT;

	if( InhibitNTCs_Cnt_M_lgc == FALSE )
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_M, NTC121Parameter_Cnt_M_u8, NTC_STATUS_PASSED);
		NTC121Parameter_Cnt_M_u8 = 0x00U;
	}
}

/* NTC $129 - Missing BSM1 Message (Msg ID $0F2) */
FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_VehicleSpeedVSOSig__BSM1__CCAN(void)
{
	BSMMsgMissing_Cnt_M_lgc = FALSE;
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&BSM1MMsgTimer_mS_M_u32);
	if( InhibitNTCs_Cnt_M_lgc == FALSE )
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_N, 0x01U, NTC_STATUS_PASSED);
	}
}

/* NTC $129 - Missing BSM1 Message (Msg ID $0F2) */
FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_VehicleSpeedVSOSigFailSts__BSM1__CCAN(void)
{
	BSMMsgMissing_Cnt_M_lgc = FALSE;
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&BSM1MMsgTimer_mS_M_u32);
	if( InhibitNTCs_Cnt_M_lgc == FALSE )
	{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_N, 0x01U, NTC_STATUS_PASSED);
	}
}

/* NTC $131 - Missing MOT1 Message (Msg ID $0E6) */
FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_EngineSts__MOT1__CCAN(void)
{
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&MOT1MMsgTimer_mS_M_u32);
	MOT1MsgMissing_Cnt_M_lgc = FALSE;
	if( InhibitNTCs_Cnt_M_lgc == FALSE )
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_O, 0x01U, NTC_STATUS_PASSED);
	}
}

/* NTC $139 - Missing MOT3 Message (Msg ID $2EE) */
FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_EngineStopStartSts__MOT3__CCAN(void)
{
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&MOT3MMsgTimer_mS_M_u32);
	if( InhibitNTCs_Cnt_M_lgc == FALSE )
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_P, 0x01U, NTC_STATUS_PASSED);
	}
}

/* NTC $141 - Missing STATUS_C_BCM2 Message (Msg ID $4B4) */
FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_CmdIgnSts__STATUS_C_BCM2__CCAN(void)
{
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&BCM2MMsgTimer_mS_M_u32);
	BCM2MsgMissing_Cnt_M_lgc = FALSE;
	OpModeFailSts_Cnt_M_u8 = 0x00U;
	CmdIgnFailStsInternal_Cnt_M_u8 = 0x00U;

	if( InhibitNTCs_Cnt_M_lgc == FALSE )
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_Q, 0x03U, NTC_STATUS_PASSED);
	}
}

/* NTC $141 - Missing STATUS_C_BCM2 Message (Msg ID $4B4) */
FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_CmdIgn_FailSts__STATUS_C_BCM2__CCAN(void)
{
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&BCM2MMsgTimer_mS_M_u32);
	BCM2MsgMissing_Cnt_M_lgc = FALSE;
	if( InhibitNTCs_Cnt_M_lgc == FALSE )
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_Q, NTC141Parameter_Cnt_M_u8, NTC_STATUS_PASSED);
		NTC141Parameter_Cnt_M_u8 = 0x00U;
	}
}

/* NTC $149 - Missing STATUS_C_IPC Message (Msg ID $419) */
FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_ElectricSteeringLamp_FailSts__STATUS_C_IPC__CCAN(void)
{
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&IPCMMsgTimer_mS_M_u32);
	if( InhibitNTCs_Cnt_M_lgc == FALSE )
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_R, 0x01U, NTC_STATUS_PASSED);
	}
}

FUNC(void, CANSM_APPL_CODE) Appl_CanSM_BusOffBegin(NetworkHandleType CanSm_NetworkHandle, CanSM_BorCounterType CanSM_BusOffNotificationCounter)
{
	if(BusOffCnt_Cnt_M_u8 > D_BUSOFF_FAIL_CNT_U8)
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_BusOffCh1, 1u, NTC_STATUS_FAILED);
		BusOffCnt_Cnt_M_u8 = D_BUSOFF_RESET_CNT_U8;
		SetBusOffRecovered(FALSE);
	}
	else
	{
		BusOffCnt_Cnt_M_u8++;
	}
}


FUNC( void, CANSM_APPL_CODE ) Appl_CanSM_BusOffEnd(NetworkHandleType CanSm_NetworkHandle)
{
	(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_BusOffCh1, 1u, NTC_STATUS_PASSED);
	SetBusOffRecovered(TRUE);
}

FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_Digit_01__CFG_DATA_CODE_REQUEST__CCAN(void)
{
	/* Enable CFG_CODE_RESPONSE */
	CfgCodeResponse();

	Rte_Call_SystemTime_GetSystemTime_mS_u32(&CfgCodeMsgTimer_mS_M_u32);
	if( InhibitNTCs_Cnt_M_lgc == FALSE )
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_MissingMsg_T, 0x01U, NTC_STATUS_PASSED);
	}

	CfgCodeRequestReceived_Cnt_M_lgc = TRUE;
}

FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_Digit_02__CFG_DATA_CODE_REQUEST__CCAN(void)
{
	Appl_COMCbk_Com_Digit_01__CFG_DATA_CODE_REQUEST__CCAN();
}

FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_Digit_03__CFG_DATA_CODE_REQUEST__CCAN(void)
{
	Appl_COMCbk_Com_Digit_01__CFG_DATA_CODE_REQUEST__CCAN();
}

FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_Digit_04__CFG_DATA_CODE_REQUEST__CCAN(void)
{
	Appl_COMCbk_Com_Digit_01__CFG_DATA_CODE_REQUEST__CCAN();
}

FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_Digit_05__CFG_DATA_CODE_REQUEST__CCAN(void)
{
	Appl_COMCbk_Com_Digit_01__CFG_DATA_CODE_REQUEST__CCAN();
}

FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_Digit_06__CFG_DATA_CODE_REQUEST__CCAN(void)
{
	Appl_COMCbk_Com_Digit_01__CFG_DATA_CODE_REQUEST__CCAN();
}

FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_Digit_07__CFG_DATA_CODE_REQUEST__CCAN(void)
{
	Appl_COMCbk_Com_Digit_01__CFG_DATA_CODE_REQUEST__CCAN();
}

FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_Digit_08__CFG_DATA_CODE_REQUEST__CCAN(void)
{
	Appl_COMCbk_Com_Digit_01__CFG_DATA_CODE_REQUEST__CCAN();
}

FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_Digit_09__CFG_DATA_CODE_REQUEST__CCAN(void)
{
	Appl_COMCbk_Com_Digit_01__CFG_DATA_CODE_REQUEST__CCAN();
}

FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_Digit_10__CFG_DATA_CODE_REQUEST__CCAN(void)
{
	Appl_COMCbk_Com_Digit_01__CFG_DATA_CODE_REQUEST__CCAN();
}

FUNC(void, COM_APPL_CODE) Appl_COMCbk_Com_Digit_11__CFG_DATA_CODE_REQUEST__CCAN(void)
{
	Appl_COMCbk_Com_Digit_01__CFG_DATA_CODE_REQUEST__CCAN();
}

STATIC FUNC ( void, AP_SRLCOMINPUT_APPL_CODE) ResetTimers( uint32 SystemTime_mS_T_u32 )
{
	/* BCM_COMMAND Message (Msg ID $0FA) */
	BCM_CMDInvMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;
	BCM_CMDInvMsgTimer1_mS_M_u32 = SystemTime_mS_T_u32;
	BCM_CMDInvMsgTimer2_mS_M_u32 = SystemTime_mS_T_u32;
	BCM_CMDMMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;
	BCM_CMDMMsgTimer1_mS_M_u32 = SystemTime_mS_T_u32;
	BCM_CMDMMsgTimer2_mS_M_u32 = SystemTime_mS_T_u32;
	
	/* BSM1 Message (Msg ID $0F2) */
	BSM1MMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;
	
	/* MOT1 Message (Msg ID $0E6) */
	MOT1InvMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;
	MOT1MMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;
	
	/* MOT3 Message (Msg ID $2EE) */
	MOT3InvMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;
	MOT3MMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;
	
	/* STATUS_C_BCM2 Message (Msg ID $4B4) */
	BCM2InvMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;
	BCM2MMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;
	
	/* Status_C_IPC Message (Msg ID $419) */
	IPCInvMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;
	IPCMMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;
	
	/* CFG_DATA_CODE_REQUEST (Msg ID $1E114000) */
	CfgCodeMsgTimer_mS_M_u32 = SystemTime_mS_T_u32;

}

STATIC FUNC(uint8, AP_SRLCOMINPUT_APPL_CODE) BSM1MsgCalculateCRC(void)
{
	VAR(uint8, AUTOMATIC) BSM1Msg_Cnt_T_u8[8];
	VAR(uint8, AUTOMATIC) CalculatedCRCB1_T_u8;
	VAR(uint8, AUTOMATIC) i;

	/* Read BSM1 Msg */
	for(i=0u; i<8u; i++)
	{
		BSM1Msg_Cnt_T_u8[i] = com_UnionBuffer.str.pdu_Pdu_BSM1__CCAN[i];
	}

	/* Calculate CRC */
	CalculatedCRCB1_T_u8 = Crc_CalculateCRC8(BSM1Msg_Cnt_T_u8, 7U, D_CRCINIT_CNT_U8);
	CalculatedCRCB1_T_u8 ^= D_CRCXORVALUE_CNT_U8;

	return CalculatedCRCB1_T_u8;
}

/*****************************************************************************************************************
  * Name        :   VldtRollgCntr
  * Description :   Validates rolling counter
  * Inputs      :   PrsntRollgCntr_Cnt_T_u08, PrevRollgCntr_Cnt_T_u08
  * Outputs     :   RollgCntrVld_Cnt_T_lgc
  * Usage Notes :   None
******************************************************************************************************************/
STATIC FUNC(boolean, AP_IMCARBR_APPL_CODE)  VldtRollgCntr( VAR(uint8, AUTOMATIC) PrsntRollgCntr_Cnt_T_u08, VAR(uint8, AUTOMATIC) PrevRollgCntr_Cnt_T_u08)
{
    VAR(boolean, uint8) RollgCntrVld_Cnt_T_lgc;

    if((PrsntRollgCntr_Cnt_T_u08  > PrevRollgCntr_Cnt_T_u08) &&
      (PrsntRollgCntr_Cnt_T_u08  <= (PrevRollgCntr_Cnt_T_u08 + k_SrlComMsgCntrMissThreshold_Cnt_u08)) )
    {
        RollgCntrVld_Cnt_T_lgc =  TRUE;
    }
    else if(PrevRollgCntr_Cnt_T_u08 > PrsntRollgCntr_Cnt_T_u08)
    {
        if(((PrevRollgCntr_Cnt_T_u08 + k_SrlComMsgCntrMissThreshold_Cnt_u08)%D_ROLLGCNTRMAXVAL_CNT_U08) >= PrsntRollgCntr_Cnt_T_u08)
        {
            RollgCntrVld_Cnt_T_lgc =  TRUE;
        }
        else
        {
            RollgCntrVld_Cnt_T_lgc =  FALSE;
        }
    }
    else
    {
        RollgCntrVld_Cnt_T_lgc =  FALSE;
    }

    return RollgCntrVld_Cnt_T_lgc;
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
