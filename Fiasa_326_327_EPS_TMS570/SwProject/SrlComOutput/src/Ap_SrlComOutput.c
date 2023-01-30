/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_SrlComOutput.c
 *     Workspace:  C:/SynergyProjects/Haitec_LC_EPS_TMS570-nzx5jd/Haitec_LC_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *     SW-C Type:  Ap_SrlComOutput
 *  Generated at:  Mon Feb 17 14:18:39 2014
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_SrlComOutput>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Jul  8 10:30:00 2013
 * %version:          EA3#15 %
 * %derived_by:       mzjphh %
 * %date_modified:    Mon Feb 17 14:53:55 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date       Rev      Author   Change Description                                                               SCR #
 * --------   -------  -------  ------------------------------------------------------------------------------  -------
 * 05/27/15		3		SAH		Updates for Anomaly EA3#727
 * 07/16/15     4       PS      Updates for DSR 2A and SCIR 2A   								   	       	   CR#13482
 * 08/28/15     5       PS      Update customer service $0200 												   EA3#2837, EA3#2838, EA3#2839
								and fix Anomaly's EA3#2099, EA3#2328, EA3#2405, EA3#2407   					   EA3#2840, EA3#2841
 * 09/03/15     6       PS      Fix Anomaly EA3#2960												           EA3#2977
 * 10/30/15     7       PS      Implemented software according to SCIR 4A and DSR 3A						   EA3#4252
 * 11/06/15     8       PS      Fix Anomaly's EA3#4375, EA3#4392											   EA3#4436, EA3#4437
 * 11/16/15     9       PS      Implemented software according to SCIR 5A and DSR 5A	 					   EA3#4579
 * 12/01/15     10      PS      Implemented software according to SCIR 5A and DSR 6A	 					   EA3#4681, EA3#4686
 * 01/22/16     12      PS      Updated the stayawake signals in PDC_INFO									   EA3#5769
 * 03/16/16     13      PS      Update DES_EPS and StayActiveSource0 of PDC_INFO							   EA3#6773, EA3#6775
 * 04/01/16     14      PS      Update to StayActiveSource0 of PDC_INFO							   			   EA3#7178
 * 10/06/16		15		NS		Fixed configuration code reponse check to handle NVM_Skipped result 		   EA3#11533
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_SrlComOutput.h"

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "Com.h"
#include "CalConstants.h"
#include "GlobalMacro.h"
#include "CanNm_cfg.h"
#include "Ap_DfltConfigData.h"
#include "Ap_DiagSvc.h"

#define D_SASANGLELOLMT_HWDEG_F32			(-720.0f)
#define D_SASANGLEHILMT_HWDEG_F32			720.0f
#define D_SASANGLEOFFSET_HWDEG_F32			720.0f
#define D_SASSPEEDLOLMT_HWDEG_F32			(-2000.0f)
#define D_SASSPEEDHILMT_HWDEG_F32			2094.0f
#define D_SASSPEEDOFFSET_HWDEG_F32			2000.0f
#define D_SASANGLESCALE_HWDEGPCNT_F32		0.1f
#define D_ELECTPWRLOLMT_AMP_F32				0.0f
#define D_ELECTPWRHILMT_AMP_F32				127.0f
#define D_ELECTPWRSCALE_AMPPCNT_F32			0.5f
#define D_STEERINGTORQUELOLMT_HWNM_F32		(-22.78f)
#define D_STEERINGTORQUEHILMT_HWNM_F32		22.967f
#define D_STEERINGTORQUEOFFSET_HWNM_F32		22.78f
#define D_STEERINGTORQUESCALE_HWNMPCNT_F32	0.1794f
#define D_NMTIMEOUTTIMER_MS_M_U16			4500U
#define D_BUSOFFCOUNT_CNT_M_U8				100U
#define D_PDCINFOCOUNT_CNT_M_U8				100U

#  define RtePim_ProxiConfigurationData() \
  (&Rte_DiagSvc_ProxiConfigurationData)

#define SRLCOMOUTPUT_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_SRLCOMOUTPUT_VAR) BusOffRecovered_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRLCOMOUTPUT_VAR) NMTimerEnabled_Cnt_M_lgc; /* PRQA S 3218 */
STATIC VAR(boolean, AP_SRLCOMOUTPUT_VAR) StayActiveSourceEPS0_Cnt_M_lgc; /* PRQA S 3218 */
STATIC VAR(boolean, AP_SRLCOMOUTPUT_VAR) StayActiveMsgTransmitted_Cnt_M_lgc; /* PRQA S 3218 */
#define SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define SRLCOMOUTPUT_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, AP_SRLCOMOUTPUT_VAR) DESEPSAcc_Cnt_M_u16; /* PRQA S 3218 */
STATIC VAR(uint16, AP_SRLCOMOUTPUT_VAR) PrevLwsAngle_Cnt_M_u16; /* PRQA S 3218 */
STATIC VAR(uint16, AP_SRLCOMOUTPUT_VAR) StayActiveFirstMsgAcc_Cnt_M_u16; /* PRQA S 3218 */
#define SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

#define SRLCOMOUTPUT_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint32, AP_SRLCOMOUTPUT_VAR) NMTimeoutTimer_mS_M_u32; /* PRQA S 3218 */
#define SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

FUNC(void, RTE_AP_SRLCOMOUTPUT_APPL_CODE) CfgCodeResponse(void);
FUNC(void, RTE_AP_SRLCOMOUTPUT_APPL_CODE) SetBusOffRecovered(boolean BusOffRecovered_Cnt_T_lgc);
extern FUNC(NvM_RequestResultType, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_ProxiConfigurationGetErrorStatus(void);

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
 * DT_ElectricSteeringFailSts: Boolean
 * DT_LwsAngle: Integer in interval [0...14400]
 * DT_LwsCalibration: Boolean
 * DT_LwsSpeed: Integer in interval [0...4095]
 * DT_SteeringLoad: Boolean
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
 * DT_LwsAngleType: Enumeration of integer in interval [0...3] with enumerators
 *   Cx0_Absolute (0U)
 *   Cx1_Relative (1U)
 *   Cx2_SNA (2U)
 * DT_LwsFailSts: Enumeration of integer in interval [0...3] with enumerators
 *   Cx0_Fail_Not_Present (0U)
 *   Cx1_Fail_Present_Ignition_Latched (1U)
 *   Cx2_Fail_Present_Recoverable (2U)
 *   Cx3_Fail_Present_Battery_Discon (3U)
 * NTCNumber: Enumeration of integer in interval [0...511] with enumerators
 *   NTC_Num_FlashWrapperLgcFlt (1U)
 *   NTC_Num_FlashECCCorr (2U)
 *   NTC_Num_FlashECCMemFlt (3U)
 *   NTC_Num_FlashCRCMemFault (4U)
 *   NTC_Num_NvMBlkDftActA (6U)
 *   NTC_Num_NvMBlkDftActB (7U)
 *   NTC_Num_NvMBlkDftActC (8U)
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
 *   NTC_Num_GateDrvFltInProcess (76U)
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
 *   NTC_Num_InvalidMsg_ParkAssistParallel (464U)
 *   NTC_Num_FlexrayCommunicationError (465U)
 *   NTC_Num_InvalidMsg_AI (466U)
 *   NTC_Num_MissingMsg_AI (467U)
 *   NTC_Num_InvalidMsg_AJ (472U)
 *   NTC_Num_MissingMsg_AJ (473U)
 *   NTC_Num_InvalidMsg_AK (480U)
 *   NTC_Num_MissingMsg_AK (481U)
 *   NTC_Num_MissingMsg_AL (489U)
 *   NTC_Num_SysConsistencyVerf (496U)
 *   NTC_Num_ConfigMisMatch (497U)
 *   NTC_Num_CalNotPrgmd (498U)
 *   NTC_Num_TunSetNotPrgmd (499U)
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


#define RTE_START_SEC_AP_SRLCOMOUTPUT_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SrlComOutput_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *     and not in Mode(s) <OFF>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_SrlComOutput_Per1_HandwheelAuthority_Uls_f32(void)
 *   Float Rte_IRead_SrlComOutput_Per1_HandwheelPosition_HwDeg_f32(void)
 *   UInt16 Rte_IRead_SrlComOutput_Per1_SrlComHwPosStatus_Cnt_u16(void)
 *   Boolean Rte_IRead_SrlComOutput_Per1_SrlComHwTrqValid_Cnt_lgc(void)
 *   Float Rte_IRead_SrlComOutput_Per1_SrlComHwTrq_HwNm_f32(void)
 *   Float Rte_IRead_SrlComOutput_Per1_SupplyCurrent_Amp_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_SrlComOutput_Per1_Com_ElecStrFailSts_Cnt_lgc(DT_ElectricSteeringFailSts data)
 *   DT_ElectricSteeringFailSts *Rte_IWriteRef_SrlComOutput_Per1_Com_ElecStrFailSts_Cnt_lgc(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_LwsAngleType_Cnt_lgc(DT_LwsAngleType data)
 *   DT_LwsAngleType *Rte_IWriteRef_SrlComOutput_Per1_Com_LwsAngleType_Cnt_lgc(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_LwsAngle_Cnt_u16(DT_LwsAngle data)
 *   DT_LwsAngle *Rte_IWriteRef_SrlComOutput_Per1_Com_LwsAngle_Cnt_u16(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_LwsCal_Cnt_lgc(DT_LwsCalibration data)
 *   DT_LwsCalibration *Rte_IWriteRef_SrlComOutput_Per1_Com_LwsCal_Cnt_lgc(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_LwsFailSts_Cnt_lgc(DT_LwsFailSts data)
 *   DT_LwsFailSts *Rte_IWriteRef_SrlComOutput_Per1_Com_LwsFailSts_Cnt_lgc(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_LwsSpeed_f32(DT_LwsSpeed data)
 *   DT_LwsSpeed *Rte_IWriteRef_SrlComOutput_Per1_Com_LwsSpeed_f32(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_SteeringLoad_Cnt_u16(DT_SteeringLoad data)
 *   DT_SteeringLoad *Rte_IWriteRef_SrlComOutput_Per1_Com_SteeringLoad_Cnt_u16(void)
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
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(UInt32 InitialTime, UInt32 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_SRLCOMOUTPUT_APPL_CODE) SrlComOutput_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SrlComOutput_Per1
 *********************************************************************************************************************/

	VAR(boolean, AUTOMATIC) BusOffCh1_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) CfgDataCodeRequestActive_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) CurrentFailSts_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) DES_EPS_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) ElecStrFailSts_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) EOL_EPS_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) EpsEn_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) GenericFailSts_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) LwsCal_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) LwsFailSts_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC6C_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC6D_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC6E_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC6F_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC70_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC71_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC72_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC73_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC74_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC76_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC94_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC120_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC128_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC129_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC131_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC139_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC159_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTC1F8_Cnt_T_lgc;
	VAR(boolean,  AUTOMATIC) SteeringLoad_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) SrlCommuncationFailSts_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS0_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS1_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS2_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS3_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS4_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS5_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS6_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS7_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS8_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS9_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS10_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS11_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS12_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS13_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS14_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StayActiveSourceEPS15_Cnt_T_lgc;

	VAR(float32, AUTOMATIC) HandwheelPosition_HwDeg_T_f32;
	VAR(float32, AUTOMATIC) LwsAngle_HwDeg_T_f32;
	VAR(float32, AUTOMATIC) LwsSpeed_Cnt_T_f32;
	
	VAR(uint32, AUTOMATIC) SystemTime_mS_T_u32;

	VAR(uint16,  AUTOMATIC) ElapsedTime_mS_T_u16;
	VAR(uint16,  AUTOMATIC) LwsAngle_Cnt_T_u16;
	VAR(uint16,  AUTOMATIC) LwsSpeed_Cnt_T_u16;
	
	VAR(uint8,  AUTOMATIC) LwsAngleType_Cnt_T_u8;

	HandwheelPosition_HwDeg_T_f32 = Rte_IRead_SrlComOutput_Per1_HandwheelPosition_HwDeg_f32();

	(void)Rte_Call_EpsEn_OP_GET(&EpsEn_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_HWASensorNotTrimmed, &NTC1F8_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_HWACrossChecks, &NTC6C_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_HWASnsrCommFault, &NTC6D_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_HWASensorRel, &NTC6E_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_HWASensorAbs, &NTC6F_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_PriMSB_SinCosCorr, &NTC70_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_SecMSB_SinCosCorr, &NTC71_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_PriVsSec_SinCosCorr, &NTC72_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_DigMSBFlt, &NTC73_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_MtrVelFlt, &NTC74_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_RedPriVsSec_SinCosCorr, &NTC76_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_DutyCycleExceeded, &NTC94_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_InvalidMsg_M, &NTC120_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_InvalidMsg_N, &NTC128_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_MissingMsg_N, &NTC129_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_MissingMsg_O, &NTC131_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_MissingMsg_P, &NTC139_Cnt_T_lgc);
	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_MissingMsg_T, &NTC159_Cnt_T_lgc);

	/*** GE -- 0xDE ***/

	LwsAngle_HwDeg_T_f32 = Limit_m(HandwheelPosition_HwDeg_T_f32, D_SASANGLELOLMT_HWDEG_F32, D_SASANGLEHILMT_HWDEG_F32);

	LwsAngle_HwDeg_T_f32 = LwsAngle_HwDeg_T_f32 * k_ScomAngPolarity_Cnt_T_s8;

	LwsAngle_Cnt_T_u16 = (DT_LwsAngle)((LwsAngle_HwDeg_T_f32 + D_SASANGLEOFFSET_HWDEG_F32) / D_SASANGLESCALE_HWDEGPCNT_F32);

	if(TRUE == NTC1F8_Cnt_T_lgc)
	{
		LwsCal_Cnt_T_lgc = FALSE;
	}
	else
	{
		LwsCal_Cnt_T_lgc = TRUE;
	}

	if( k_CustDIDCals_Cnt_u08.AbsAngleSensorType_Cnt_lgc == TRUE)
	{
		LwsAngleType_Cnt_T_u8 = 0x00U;
	}
	else
	{
		LwsAngleType_Cnt_T_u8 = 0x01U;
	}

	if( TRUE == NTC94_Cnt_T_lgc )
	{
		SteeringLoad_Cnt_T_lgc = FALSE;
	}
	else
	{
		SteeringLoad_Cnt_T_lgc = TRUE;
	}

	if( (TRUE == NTC70_Cnt_T_lgc) || (TRUE == NTC71_Cnt_T_lgc) || (TRUE == NTC72_Cnt_T_lgc) || (TRUE == NTC73_Cnt_T_lgc) ||
			(TRUE == NTC74_Cnt_T_lgc) || (TRUE == NTC76_Cnt_T_lgc) )
	{
		LwsSpeed_Cnt_T_u16 = 0xFFFu;
	}
	else
	{
		LwsSpeed_Cnt_T_f32 = Abs_f32_m(LwsAngle_Cnt_T_u16 - PrevLwsAngle_Cnt_M_u16) * k_ScomVelPolarity_Cnt_T_f32;
		LwsSpeed_Cnt_T_u16 = (uint16) ( Limit_m(LwsSpeed_Cnt_T_f32, D_SASSPEEDLOLMT_HWDEG_F32, D_SASSPEEDHILMT_HWDEG_F32) + D_SASSPEEDOFFSET_HWDEG_F32 );
	}

	if( (TRUE == NTC6C_Cnt_T_lgc) || (TRUE == NTC6D_Cnt_T_lgc) || (TRUE == NTC6E_Cnt_T_lgc) || (TRUE == NTC6F_Cnt_T_lgc) )
	{
		LwsFailSts_Cnt_T_lgc = TRUE;
	}
	else
	{
		LwsFailSts_Cnt_T_lgc = FALSE;
	}

	if( (TRUE == NTC120_Cnt_T_lgc) || (TRUE == NTC128_Cnt_T_lgc) || (TRUE == NTC129_Cnt_T_lgc) || (TRUE == NTC131_Cnt_T_lgc) || (TRUE == NTC139_Cnt_T_lgc) || (TRUE == NTC159_Cnt_T_lgc) )
	{
		SrlCommuncationFailSts_Cnt_T_lgc = TRUE;
	}
	else
	{
		SrlCommuncationFailSts_Cnt_T_lgc = FALSE;
	}

	if((TRUE == LwsFailSts_Cnt_T_lgc) ||
		(0xFFFF == LwsSpeed_Cnt_T_f32) ||
		(FALSE == LwsCal_Cnt_T_lgc) ||
		(TRUE == SrlCommuncationFailSts_Cnt_T_lgc) )
	{
		ElecStrFailSts_Cnt_T_lgc = TRUE;
	}
	else
	{
		ElecStrFailSts_Cnt_T_lgc = FALSE;
	}

	if((TRUE == LwsFailSts_Cnt_T_lgc) || (FALSE == LwsCal_Cnt_T_lgc))
	{
		LwsAngle_Cnt_T_u16 = 0xFFFF; /* SNA */
	}
	
	PrevLwsAngle_Cnt_M_u16 = LwsAngle_Cnt_T_u16;
	

	/*** PDC INFO -- 0x1E360002 ***/
	

	if( BusOffRecovered_Cnt_M_lgc == FALSE )
	{
		DESEPSAcc_Cnt_M_u16 = 0x00U;
		DES_EPS_Cnt_T_lgc = FALSE;
	}
	
	else
	{
		DES_EPS_Cnt_T_lgc = TRUE;
		DESEPSAcc_Cnt_M_u16++;
	}
	
	if( DESEPSAcc_Cnt_M_u16 >= D_BUSOFFCOUNT_CNT_M_U8 )
	{
		SetBusOffRecovered(FALSE);
	}

	CurrentFailSts_Cnt_T_lgc = 0x00U;
	EOL_EPS_Cnt_T_lgc =  TRUE;
	GenericFailSts_Cnt_T_lgc = 0x00U;
	
	StayActiveSourceEPS1_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS2_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS3_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS4_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS5_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS6_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS7_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS8_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS9_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS10_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS11_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS12_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS13_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS14_Cnt_T_lgc = TRUE;
	StayActiveSourceEPS15_Cnt_T_lgc = TRUE;

	if(	TRUE == EpsEn_Cnt_T_lgc )
	{
		StayActiveSourceEPS0_Cnt_M_lgc = TRUE;

		/* Initialization */
		if( NMTimerEnabled_Cnt_M_lgc == FALSE )
		{
			Rte_Call_SystemTime_GetSystemTime_mS_u32(&NMTimeoutTimer_mS_M_u32);
			NMTimerEnabled_Cnt_M_lgc = TRUE;
		}
	}

	else
	{
		NMTimerEnabled_Cnt_M_lgc = FALSE;

		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(NMTimeoutTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		if( ElapsedTime_mS_T_u16 >= D_NMTIMEOUTTIMER_MS_M_U16 )
		{
			if ( CanNm_TimeoutTimer[0] == 800u )
			{
				StayActiveSourceEPS0_Cnt_M_lgc = FALSE;
				StayActiveFirstMsgAcc_Cnt_M_u16 = 0x00U;
				StayActiveMsgTransmitted_Cnt_M_lgc = TRUE;
			}

			if( StayActiveMsgTransmitted_Cnt_M_lgc == TRUE )
			{
				StayActiveSourceEPS0_Cnt_M_lgc = FALSE;
				StayActiveFirstMsgAcc_Cnt_M_u16++;
				if( StayActiveFirstMsgAcc_Cnt_M_u16 >= D_PDCINFOCOUNT_CNT_M_U8)
				{
					StayActiveSourceEPS0_Cnt_M_lgc = TRUE;
					StayActiveMsgTransmitted_Cnt_M_lgc = FALSE;
				}
			}

			else
			{
				StayActiveSourceEPS0_Cnt_M_lgc = TRUE;
			}
		}
		else
		{
			StayActiveSourceEPS0_Cnt_M_lgc = TRUE;
		}
	}

	StayActiveSourceEPS0_Cnt_T_lgc = StayActiveSourceEPS0_Cnt_M_lgc;

	Com_SendSignal(Com_ElectricSteeringFailSts__GE__CCAN, &ElecStrFailSts_Cnt_T_lgc);
	Com_SendSignal(Com_LwsAngle__GE__CCAN, &LwsAngle_Cnt_T_u16);
	Com_SendSignal(Com_LwsAngleType__GE__CCAN, &LwsAngleType_Cnt_T_u8);
	Com_SendSignal(Com_LwsCalibration__GE__CCAN, &LwsCal_Cnt_T_lgc);
	Com_SendSignal(Com_LWSFailSts__GE__CCAN, &LwsFailSts_Cnt_T_lgc);
	Com_SendSignal(Com_LwsSpeed__GE__CCAN, &LwsSpeed_Cnt_T_u16);
	Com_SendSignal(Com_SteeringLoad__GE__CCAN, &SteeringLoad_Cnt_T_lgc);

	Com_SendSignal(Com_CurrentFailSts_EPS__PDC_INFO_EPS__CCAN, &CurrentFailSts_Cnt_T_lgc);
	Com_SendSignal(Com_DES_EPS__PDC_INFO_EPS__CCAN, &DES_EPS_Cnt_T_lgc);
	Com_SendSignal(Com_EOL_EPS__PDC_INFO_EPS__CCAN, &EOL_EPS_Cnt_T_lgc);
	Com_SendSignal(Com_GenericFailSts_EPS__PDC_INFO_EPS__CCAN, &GenericFailSts_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_0__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS0_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_1__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS1_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_2__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS2_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_3__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS3_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_4__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS4_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_5__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS5_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_6__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS6_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_7__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS7_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_8__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS8_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_9__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS9_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_10__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS10_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_11__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS11_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_12__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS12_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_13__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS13_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_14__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS14_Cnt_T_lgc);
	Com_SendSignal(Com_StayActiveSource_EPS_15__PDC_INFO_EPS__CCAN, &StayActiveSourceEPS15_Cnt_T_lgc);

	Rte_IWrite_SrlComOutput_Per1_ElectricStrFailSts_Cnt_lgc(ElecStrFailSts_Cnt_T_lgc);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

FUNC(void, RTE_AP_SRLCOMOUTPUT_APPL_CODE) CfgCodeResponse(void)
{

	VAR(uint8, AUTOMATIC) CfgRepsonse_Digit_01_T_u8;
	VAR(uint8, AUTOMATIC) CfgRepsonse_Digit_02_T_u8;
	VAR(uint8, AUTOMATIC) CfgRepsonse_Digit_03_T_u8;
	VAR(uint8, AUTOMATIC) CfgRepsonse_Digit_04_T_u8;
	VAR(uint8, AUTOMATIC) CfgRepsonse_Digit_05_T_u8;
	VAR(uint8, AUTOMATIC) CfgRepsonse_Digit_06_T_u8;
	VAR(uint8, AUTOMATIC) CfgRepsonse_Digit_07_T_u8;
	VAR(uint8, AUTOMATIC) CfgRepsonse_Digit_08_T_u8;
	VAR(uint8, AUTOMATIC) CfgRepsonse_Digit_09_T_u8;
	VAR(uint8, AUTOMATIC) CfgRepsonse_Digit_10_T_u8;
	VAR(uint8, AUTOMATIC) CfgRepsonse_Digit_11_T_u8;

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;

	ErrorStatus_Cnt_T_enum = DiagSvc_ProxiConfigurationGetErrorStatus();
	
	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		CfgRepsonse_Digit_01_T_u8 = ((*RtePim_ProxiConfigurationData())[10]) - 0x30U;
		CfgRepsonse_Digit_02_T_u8 = ((*RtePim_ProxiConfigurationData())[9]) - 0x30U;
		CfgRepsonse_Digit_03_T_u8 = ((*RtePim_ProxiConfigurationData())[8]) - 0x30U;
		CfgRepsonse_Digit_04_T_u8 = ((*RtePim_ProxiConfigurationData())[7]) - 0x30U;
		CfgRepsonse_Digit_05_T_u8 = ((*RtePim_ProxiConfigurationData())[6]) - 0x30U;
		CfgRepsonse_Digit_06_T_u8 = ((*RtePim_ProxiConfigurationData())[5]) - 0x30U;
		CfgRepsonse_Digit_07_T_u8 = ((*RtePim_ProxiConfigurationData())[4]) - 0x30U;
		CfgRepsonse_Digit_08_T_u8 = ((*RtePim_ProxiConfigurationData())[3]) - 0x30U;
		CfgRepsonse_Digit_09_T_u8 = ((*RtePim_ProxiConfigurationData())[2]) - 0x30U;
		CfgRepsonse_Digit_10_T_u8 = ((*RtePim_ProxiConfigurationData())[1]) - 0x30U;
		CfgRepsonse_Digit_11_T_u8 = ((*RtePim_ProxiConfigurationData())[0]) - 0x30U;

		DiagSvc_ProxiCheckData_Cnt_u08[0] = (*RtePim_ProxiConfigurationData())[0];
		DiagSvc_ProxiCheckData_Cnt_u08[1] = (*RtePim_ProxiConfigurationData())[1];
		DiagSvc_ProxiCheckData_Cnt_u08[2] = (*RtePim_ProxiConfigurationData())[2];
		DiagSvc_ProxiCheckData_Cnt_u08[3] = (*RtePim_ProxiConfigurationData())[3];
		DiagSvc_ProxiCheckData_Cnt_u08[4] = (*RtePim_ProxiConfigurationData())[4];
		DiagSvc_ProxiCheckData_Cnt_u08[5] = (*RtePim_ProxiConfigurationData())[5];
		DiagSvc_ProxiCheckData_Cnt_u08[6] = (*RtePim_ProxiConfigurationData())[6];
		DiagSvc_ProxiCheckData_Cnt_u08[7] = (*RtePim_ProxiConfigurationData())[7];
		DiagSvc_ProxiCheckData_Cnt_u08[8] = (*RtePim_ProxiConfigurationData())[8];
		DiagSvc_ProxiCheckData_Cnt_u08[9] = (*RtePim_ProxiConfigurationData())[9];
		DiagSvc_ProxiCheckData_Cnt_u08[10] = (*RtePim_ProxiConfigurationData())[10];
	}
	else if( ErrorStatus_Cnt_T_enum == NVM_REQ_BLOCK_SKIPPED)
	{
		if (((*RtePim_ProxiConfigurationData())[0] == DiagSvc_ProxiCheckData_Cnt_u08[0]) &&
			((*RtePim_ProxiConfigurationData())[1] == DiagSvc_ProxiCheckData_Cnt_u08[1]) &&
			((*RtePim_ProxiConfigurationData())[2] == DiagSvc_ProxiCheckData_Cnt_u08[2]) &&
			((*RtePim_ProxiConfigurationData())[3] == DiagSvc_ProxiCheckData_Cnt_u08[3]) &&
			((*RtePim_ProxiConfigurationData())[4] == DiagSvc_ProxiCheckData_Cnt_u08[4]) &&
			((*RtePim_ProxiConfigurationData())[5] == DiagSvc_ProxiCheckData_Cnt_u08[5]) &&
			((*RtePim_ProxiConfigurationData())[6] == DiagSvc_ProxiCheckData_Cnt_u08[6]) &&
			((*RtePim_ProxiConfigurationData())[7] == DiagSvc_ProxiCheckData_Cnt_u08[7]) &&
			((*RtePim_ProxiConfigurationData())[9] == DiagSvc_ProxiCheckData_Cnt_u08[9]) &&
			((*RtePim_ProxiConfigurationData())[10] == DiagSvc_ProxiCheckData_Cnt_u08[10]))
		{
			CfgRepsonse_Digit_01_T_u8 = ((*RtePim_ProxiConfigurationData())[10]) - 0x30U;
			CfgRepsonse_Digit_02_T_u8 = ((*RtePim_ProxiConfigurationData())[9]) - 0x30U;
			CfgRepsonse_Digit_03_T_u8 = ((*RtePim_ProxiConfigurationData())[8]) - 0x30U;
			CfgRepsonse_Digit_04_T_u8 = ((*RtePim_ProxiConfigurationData())[7]) - 0x30U;
			CfgRepsonse_Digit_05_T_u8 = ((*RtePim_ProxiConfigurationData())[6]) - 0x30U;
			CfgRepsonse_Digit_06_T_u8 = ((*RtePim_ProxiConfigurationData())[5]) - 0x30U;
			CfgRepsonse_Digit_07_T_u8 = ((*RtePim_ProxiConfigurationData())[4]) - 0x30U;
			CfgRepsonse_Digit_08_T_u8 = ((*RtePim_ProxiConfigurationData())[3]) - 0x30U;
			CfgRepsonse_Digit_09_T_u8 = ((*RtePim_ProxiConfigurationData())[2]) - 0x30U;
			CfgRepsonse_Digit_10_T_u8 = ((*RtePim_ProxiConfigurationData())[1]) - 0x30U;
			CfgRepsonse_Digit_11_T_u8 = ((*RtePim_ProxiConfigurationData())[0]) - 0x30U;
		}
		else
		{
			CfgRepsonse_Digit_01_T_u8 = 0x0Au;
			CfgRepsonse_Digit_02_T_u8 = 0x0Au;
			CfgRepsonse_Digit_03_T_u8 = 0x0Au;
			CfgRepsonse_Digit_04_T_u8 = 0x0Au;
			CfgRepsonse_Digit_05_T_u8 = 0x0Au;
			CfgRepsonse_Digit_06_T_u8 = 0x0Au;
			CfgRepsonse_Digit_07_T_u8 = 0x0Au;
			CfgRepsonse_Digit_08_T_u8 = 0x0Au;
			CfgRepsonse_Digit_09_T_u8 = 0x0Au;
			CfgRepsonse_Digit_10_T_u8 = 0x0Au;
			CfgRepsonse_Digit_11_T_u8 = 0x0Au;
		}
	}
	else
	{
		CfgRepsonse_Digit_01_T_u8 = 0x0Au;
		CfgRepsonse_Digit_02_T_u8 = 0x0Au;
		CfgRepsonse_Digit_03_T_u8 = 0x0Au;
		CfgRepsonse_Digit_04_T_u8 = 0x0Au;
		CfgRepsonse_Digit_05_T_u8 = 0x0Au;
		CfgRepsonse_Digit_06_T_u8 = 0x0Au;
		CfgRepsonse_Digit_07_T_u8 = 0x0Au;
		CfgRepsonse_Digit_08_T_u8 = 0x0Au;
		CfgRepsonse_Digit_09_T_u8 = 0x0Au;
		CfgRepsonse_Digit_10_T_u8 = 0x0Au;
		CfgRepsonse_Digit_11_T_u8 = 0x0Au;
	}

	Com_SendSignal(Com_Digit_01_EPS__CFG_DATA_CODE_RSP_EPS__CCAN, &CfgRepsonse_Digit_01_T_u8);
	Com_SendSignal(Com_Digit_02_EPS__CFG_DATA_CODE_RSP_EPS__CCAN, &CfgRepsonse_Digit_02_T_u8);
	Com_SendSignal(Com_Digit_03_EPS__CFG_DATA_CODE_RSP_EPS__CCAN, &CfgRepsonse_Digit_03_T_u8);
	Com_SendSignal(Com_Digit_04_EPS__CFG_DATA_CODE_RSP_EPS__CCAN, &CfgRepsonse_Digit_04_T_u8);
	Com_SendSignal(Com_Digit_05_EPS__CFG_DATA_CODE_RSP_EPS__CCAN, &CfgRepsonse_Digit_05_T_u8);
	Com_SendSignal(Com_Digit_06_EPS__CFG_DATA_CODE_RSP_EPS__CCAN, &CfgRepsonse_Digit_06_T_u8);
	Com_SendSignal(Com_Digit_07_EPS__CFG_DATA_CODE_RSP_EPS__CCAN, &CfgRepsonse_Digit_07_T_u8);
	Com_SendSignal(Com_Digit_08_EPS__CFG_DATA_CODE_RSP_EPS__CCAN, &CfgRepsonse_Digit_08_T_u8);
	Com_SendSignal(Com_Digit_09_EPS__CFG_DATA_CODE_RSP_EPS__CCAN, &CfgRepsonse_Digit_09_T_u8);
	Com_SendSignal(Com_Digit_10_EPS__CFG_DATA_CODE_RSP_EPS__CCAN, &CfgRepsonse_Digit_10_T_u8);
	Com_SendSignal(Com_Digit_11_EPS__CFG_DATA_CODE_RSP_EPS__CCAN, &CfgRepsonse_Digit_11_T_u8);
	
}

FUNC(void, RTE_AP_SRLCOMOUTPUT_APPL_CODE) SetBusOffRecovered(boolean BusOffRecovered_Cnt_T_lgc)
{
	BusOffRecovered_Cnt_M_lgc = BusOffRecovered_Cnt_T_lgc;
}

#define RTE_STOP_SEC_AP_SRLCOMOUTPUT_APPL_CODE
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
