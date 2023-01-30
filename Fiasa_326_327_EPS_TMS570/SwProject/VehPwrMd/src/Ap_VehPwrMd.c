/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_VehPwrMd.c
 *     Workspace:  C:/Temp/Haitec_LC_EPS_TMS570/Haitec_LC_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *     SW-C Type:  Ap_VehPwrMd
 *  Generated at:  Mon Jul  8 10:51:44 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1 (Beta)
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_VehPwrMd>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Jul  8 10:30:00 2013
 * %version:          EA3#3 %
 * %derived_by:       nzdx8v %
 * %date_modified:    Thu Jan  9 16:53:32 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date       Rev      Author   Change Description                                                               SCR #
 * --------   -------  -------  ------------------------------------------------------------------------------  -------
 * 07/30/15    2       PS       Fix CmdIgnSts_Cnt_M_u16, CmdIgnFailSts_Cnt_M_u16
								and OperationalModeSts variables   								   	       		EA3#2103, EA3#2105
* 15/15/15     3       PS       Implemented software according to SCIR 3A and DSR 2A						    EA3#3742
* 11/06/15     4       PS       Fix Anomaly's EA3#4375, EA3#4392											    EA3#4436, EA3#4437
* 11/16/15     5       PS       Implemented software according to SCIR 5A and DSR 5A	 					    EA3#4579
* 12/01/15     6       PS       Implemented software according to SCIR 5A and DSR 6A	 						EA3#4681, EA3#4686
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Constants:
 ==========
  D_RACKTOVEHCNTRUNLEARNED_CNT_U16
    This constant has been added until anomaly 3744 can be corrected. Once the anomaly is corrected, this can be removed from StdDef. This should only be used by BMW as of 12Sep12.

 *********************************************************************************************************************/

#include "Rte_Ap_VehPwrMd.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "Ap_VehPwrMd_Cfg.h"
#include "CalConstants.h"


#define D_ENGINESPEEDOFFTHRESH_RPM_F32	50.0f
#define D_ENGINESPEEDONTHRESH_RPM_F32	300.0f
#define D_IGNOFF_CNT_U16				0x02U
#define D_IGNON_CNT_U16					0x04U
#define D_IGNSTART_CNT_U16				0x06U
#define D_IGNCRANKING_CNT_U16			0x07U
#define D_IGNONENGON_CNT_U16			0x08U
#define D_IGNPREOFF_CNT_U16				0x0AU
#define D_IGNSNA_CNT_U16				0x0FU

#define D_STOPSTARTENGOFF_CNT_U16			0x00U
#define D_STOPSTARTENGNOTINSTART_CNT_U16	0x01U

#define VEHPWRMD_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint32,  AP_VEHPWRMD_VAR) CtermOpModeStsTimer_mS_M_u32;
STATIC VAR(uint32,  AP_VEHPWRMD_VAR) CtermShutdownTimer_mS_M_u32;
#define VEHPWRMD_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define VEHPWRMD_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, AP_VEHPWRMD_VAR) OpModeSts_Cnt_M_u16; /* PRQA S 3218 */
STATIC VAR(uint16, AP_VEHPWRMD_VAR) PowerLatchTimeDID191D_Cnt_M_u16; /* PRQA S 3218 */
STATIC VAR(uint16, AP_VEHPWRMD_VAR) VehPwrMd2msCounter_Cnt_M_u16; /* PRQA S 3218 */
#define VEHPWRMD_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

#define VEHPWRMD_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_VEHPWRMD_VAR) CTermActive_Cnt_M_lgc; /* PRQA S 3218 */
STATIC VAR(boolean, AP_VEHPWRMD_VAR) StartStopLogicEnable_Cnt_M_lgc; /* PRQA S 3218 */
#define VEHPWRMD_STOP_SEC_VAR_CLEARED_BOOLEAN
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
 * Double: Real in interval [-DBL_MAX...DBL_MAX] with double precision including NaN (standard type)
 * Float: Real in interval [-FLT_MAX...FLT_MAX] with single precision (standard type)
 * IoHwAb_BoolType: Integer in interval [0...1]
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * SInt32: Integer in interval [-2147483648...2147483647] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * EcuM_StateType: Enumeration of integer in interval [16...255] with enumerators
 *   ECUM_STATE_STARTUP (16U)
 *   ECUM_STATE_STARTUP_ONE (17U)
 *   ECUM_STATE_STARTUP_TWO (18U)
 *   ECUM_STATE_WAKEUP (32U)
 *   ECUM_STATE_WAKEUP_ONE (33U)
 *   ECUM_STATE_WAKEUP_VALIDATION (34U)
 *   ECUM_STATE_WAKEUP_REACTION (35U)
 *   ECUM_STATE_WAKEUP_TWO (36U)
 *   ECUM_STATE_WAKEUP_WAKESLEEP (37U)
 *   ECUM_STATE_WAKEUP_TTII (38U)
 *   ECUM_STATE_RUN (48U)
 *   ECUM_STATE_APP_RUN (50U)
 *   ECUM_STATE_APP_POST_RUN (51U)
 *   ECUM_STATE_SHUTDOWN (64U)
 *   ECUM_STATE_PREP_SHUTDOWN (68U)
 *   ECUM_STATE_GO_SLEEP (73U)
 *   ECUM_STATE_GO_OFF_ONE (77U)
 *   ECUM_STATE_GO_OFF_TWO (78U)
 *   ECUM_STATE_SLEEP (80U)
 *   ECUM_STATE_OFF (128U)
 *   ECUM_STATE_RESET (144U)
 *   ECUM_STATE_ERROR (255U)
 * NTCNumber: Enumeration of integer in interval [0...511] with enumerators
 *   NTC_Num_FlashWrapperLgcFlt (1U)
 *   NTC_Num_FlashECCCorr (2U)
 *   NTC_Num_FlashECCMemFlt (3U)
 *   NTC_Num_FlashCRCMemFault (4U)
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
 *   NTC_Num_InvalidMsg_ESP_A6 (464U)
 *   NTC_Num_MissingMsg_ESP_A6 (465U)
 *   NTC_Num_InvalidMsg_Wheel_Speed_2 (466U)
 *   NTC_Num_MissingMsg_Wheel_Speed_2 (467U)
 *   NTC_Num_InvalidMsg_GW_LIN_I_C2 (468U)
 *   NTC_Num_MissingMsg_GW_LIN_I_C2 (469U)
 *   NTC_Num_InvalidMsg_EcuCfg6 (470U)
 *   NTC_Num_MissingMsg_EcuCfg6 (471U)
 *   NTC_Num_InvalidMsg_VehCfg7 (472U)
 *   NTC_Num_MissingMsg_VehCfg7 (473U)
 *   NTC_Num_MissingMsg_CFG_RQ (474U)
 *   NTC_Num_MissingMsg_CFG_RQ_C (475U)
 *   NTC_Num_MissingMsg_ORC_YRS_DATA (476U)
 *   NTC_Num_InvalidMsg_ORC_YRS_DATA (477U)
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
 * Float: D_2MS_MS_F32 = 0.002F
 * Float: D_2MS_SEC_F32 = 0.002F
 * Float: D_2PI_ULS_F32 = 6.2831853071796F
 * Float: D_MSECPERSEC_ULS_F32 = 1000.0F
 * Float: D_MTRCTRLHIGHLMT_VOLTS_F32 = 18.0F
 * Float: D_MTRCTRLLOWLMT_VOLTS_F32 = 9.0F
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8F
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8F
 * Float: D_MTRTRQCMLOLMT_MTRNM_F32 = -8.8F
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
 * UInt16: D_DELTAROLLASST_MTRNM_U5P11 = 512U
 * UInt16: D_MAXCONF_ULS_U8P8 = 256U
 * UInt16: D_MTRPOLESDIV2_CNT_U16 = 3U
 * UInt16: D_ONE_CNT_U16 = 1U
 * UInt16: D_QUADRANT1_CNT_U16 = 1U
 * UInt16: D_QUADRANT2_CNT_U16 = 2U
 * UInt16: D_QUADRANT3_CNT_U16 = 3U
 * UInt16: D_QUADRANT4_CNT_U16 = 4U
 * UInt16: D_RACKCNTRUNLEARNED_CNT_U16 = 65535U
 * UInt16: D_RACKTOVEHCNTRINVALID_CNT_U16 = 4095U
 * UInt16: D_RACKTOVEHCNTRUNLEARNED_CNT_U16 = 4095U
 * UInt16: D_ZERO_CNT_U16 = 0U
 * UInt32: D_ONE_CNT_U32 = 1U
 * UInt32: D_SVCDFTKININTDIAG_CNT_B32 = 4U
 * UInt32: D_ZERO_CNT_U32 = 0U
 * UInt8: D_MTRPOLESDIV2_CNT_U8 = 3U
 * UInt8: D_ONE_CNT_U8 = 1U
 * UInt8: D_QUADRANT1_CNT_U8 = 1U
 * UInt8: D_QUADRANT2_CNT_U8 = 2U
 * UInt8: D_QUADRANT3_CNT_U8 = 3U
 * UInt8: D_QUADRANT4_CNT_U8 = 4U
 * UInt8: D_TURNSCNTRPARTNUMINIT_CNT_U08 = 255U
 * UInt8: D_ZERO_CNT_U8 = 0U
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_VEHPWRMD_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehPwrMd_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_VehPwrMd_Init1_OperRampRate_XpmS_f32(Float data)
 *   Float *Rte_IWriteRef_VehPwrMd_Init1_OperRampRate_XpmS_f32(void)
 *   void Rte_IWrite_VehPwrMd_Init1_OperRampValue_Uls_f32(Float data)
 *   Float *Rte_IWriteRef_VehPwrMd_Init1_OperRampValue_Uls_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHPWRMD_APPL_CODE) VehPwrMd_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: VehPwrMd_Init1
 *********************************************************************************************************************/

	VAR(uint32, AUTOMATIC) SystemTime_mS_T_u32;
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&SystemTime_mS_T_u32);
	Rte_IWrite_VehPwrMd_Init1_OperRampRate_XpmS_f32(k_RampDnRt_UlspmS_f32);
	Rte_IWrite_VehPwrMd_Init1_OperRampValue_Uls_f32(D_ZERO_ULS_F32);
	
	CtermOpModeStsTimer_mS_M_u32 = SystemTime_mS_T_u32;
	CtermShutdownTimer_mS_M_u32 = SystemTime_mS_T_u32;

	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehPwrMd_Per1
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
 *   Boolean Rte_IRead_VehPwrMd_Per1_EngONSrlComSvcDft_Cnt_lgc(void)
 *   Boolean Rte_IRead_VehPwrMd_Per1_EngineSpeedSignalFailure_Cnt_lgc(void)
 *   Float Rte_IRead_VehPwrMd_Per1_EngineSpeed_Rpm_f32(void)
 *   Boolean Rte_IRead_VehPwrMd_Per1_VehicleSpeedValid_Cnt_lgc(void)
 *   Float Rte_IRead_VehPwrMd_Per1_VehicleSpeed_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_VehPwrMd_Per1_ATermActive_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_VehPwrMd_Per1_ATermActive_Cnt_lgc(void)
 *   void Rte_IWrite_VehPwrMd_Per1_CTermActive_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_VehPwrMd_Per1_CTermActive_Cnt_lgc(void)
 *   void Rte_IWrite_VehPwrMd_Per1_OperRampRate_XpmS_f32(Float data)
 *   Float *Rte_IWriteRef_VehPwrMd_Per1_OperRampRate_XpmS_f32(void)
 *   void Rte_IWrite_VehPwrMd_Per1_OperRampValue_Uls_f32(Float data)
 *   Float *Rte_IWriteRef_VehPwrMd_Per1_OperRampValue_Uls_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_EpsEn_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_EpsEn_E_NOT_OK
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_GetNTCFailed(NTCNumber NTC_Cnt_T_enum, Boolean *NTCFailed_Ptr_T_lgc)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHPWRMD_APPL_CODE) VehPwrMd_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: VehPwrMd_Per1
 *********************************************************************************************************************/
	
	VAR(float32, AUTOMATIC) OperRampRate_XpmS_T_f32;
	VAR(float32, AUTOMATIC) OperRampValue_Uls_T_f32;
	VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;
	
	VAR(uint32,  AUTOMATIC) SystemTime_mS_T_u32;

	VAR(uint8,  AUTOMATIC) EngStartStopSts_Cnt_T_u8;
	VAR(uint8,  AUTOMATIC) StartStopSts_Cnt_T_u8;

	VAR(uint16,  AUTOMATIC) ElapsedTime1_mS_T_u16;
	VAR(uint16,  AUTOMATIC) ElapsedTime2_mS_T_u16;
	VAR(uint16,  AUTOMATIC) OpModeSts_Cnt_T_U16;

	VAR(boolean, AUTOMATIC) ATermActive_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) EngONSrlComSvcDft_Cnt_T_lgc;

	VAR(boolean, AUTOMATIC) EPSEn_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) INTInfoActive_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) VehicleSpeedValid_Cnt_T_lgc;
	
	VAR(ComM_ModeType, AUTOMATIC) ComM_ModeStatus_T_Enum;
	VAR(ManufModeType, AUTOMATIC) MEC_Cnt_T_enum;
	VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC) SysState_Cnt_T_Enum;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_VehPwrMd_Per1_CP0_CheckpointReached();
	

	EngONSrlComSvcDft_Cnt_T_lgc = Rte_IRead_VehPwrMd_Per1_EngONSrlComSvcDft_Cnt_lgc();
	EngStartStopSts_Cnt_T_u8 = Rte_IRead_VehPwrMd_Per1_EngStartStopSts_Cnt_u8();
	StartStopLogicEnable_Cnt_M_lgc = Rte_IRead_VehPwrMd_Per1_StartStopLogicEnable_Cnt_lgc();
	StartStopSts_Cnt_T_u8 = Rte_IRead_VehPwrMd_Per1_StartStopSts_Cnt_u8();
	VehicleSpeedValid_Cnt_T_lgc = Rte_IRead_VehPwrMd_Per1_VehicleSpeedValid_Cnt_lgc();
	VehicleSpeed_Kph_T_f32 = Rte_IRead_VehPwrMd_Per1_VehicleSpeed_Kph_f32();
	OpModeSts_Cnt_T_U16 = Rte_IRead_VehPwrMd_Per1_OperationalModeSts_Cnt_u16();
	MEC_Cnt_T_enum = Rte_IRead_VehPwrMd_Per1_MEC_Cnt_enum();

	SysState_Cnt_T_Enum = Rte_Mode_SystemState_Mode();
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&SystemTime_mS_T_u32);
	(void)Rte_Call_EpsEn_OP_GET(&EPSEn_Cnt_T_lgc);

    (void)Rte_Call_ComM_UserRequest_GetCurrentComMode(&ComM_ModeStatus_T_Enum);

    /* Reset the OpModeSts check timer */
    if ( (OpModeSts_Cnt_T_U16 != D_IGNONENGON_CNT_U16) || (OpModeSts_Cnt_T_U16 != OpModeSts_Cnt_M_u16) )
    {
    	CtermOpModeStsTimer_mS_M_u32 = SystemTime_mS_T_u32;
    }

	/* A Term */
	if( (TRUE == EPSEn_Cnt_T_lgc) || ( (MEC_Cnt_T_enum == ProductionMode) && (ComM_ModeStatus_T_Enum != COMM_NO_COMMUNICATION) ) )
	{
		ATermActive_Cnt_T_lgc = TRUE;
		INTInfoActive_Cnt_T_lgc = TRUE;
		VehPwrMd2msCounter_Cnt_M_u16 = 0u;
		PowerLatchTimeDID191D_Cnt_M_u16 = 0u;
	}
	
	else
	{
		ATermActive_Cnt_T_lgc = FALSE;
		INTInfoActive_Cnt_T_lgc = FALSE;

		/* DID 191D - Time of Power Latch */
		if( VehPwrMd2msCounter_Cnt_M_u16 < 500u )
		{
			VehPwrMd2msCounter_Cnt_M_u16++;
		}

		else
		{
			VehPwrMd2msCounter_Cnt_M_u16 = 0u;
		}
	}

	/* C Term */
	if( TRUE == EngONSrlComSvcDft_Cnt_T_lgc )
	{
		CTermActive_Cnt_M_lgc = TRUE;
	}

	else
	{
		/* Shutdown criteria */
		if ( (INTInfoActive_Cnt_T_lgc == FALSE)
			&& ( (D_IGNPREOFF_CNT_U16 == OpModeSts_Cnt_T_U16) || (D_IGNOFF_CNT_U16 == OpModeSts_Cnt_T_U16) || (D_IGNSNA_CNT_U16 == OpModeSts_Cnt_T_U16) ) )
		{
			Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(CtermShutdownTimer_mS_M_u32, &ElapsedTime2_mS_T_u16);
			if( ElapsedTime2_mS_T_u16 > k_CTermShutdownTimeout_mS_u16)
			{
				CTermActive_Cnt_M_lgc = FALSE;
			}
		}

		else
		{
			/* Reset Shutdown Timer */
			CtermShutdownTimer_mS_M_u32 = SystemTime_mS_T_u32;
			Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(CtermOpModeStsTimer_mS_M_u32, &ElapsedTime1_mS_T_u16);

			/* StopStart Logic */
			if( (StartStopLogicEnable_Cnt_M_lgc == TRUE) && (SysState_Cnt_T_Enum == RTE_MODE_StaMd_Mode_OPERATE)
					&& ( (StartStopSts_Cnt_T_u8 != D_STOPSTARTENGOFF_CNT_U16) && (EngStartStopSts_Cnt_T_u8 != D_STOPSTARTENGNOTINSTART_CNT_U16) )
					&& ( (D_IGNON_CNT_U16 == OpModeSts_Cnt_T_U16) || (D_IGNSTART_CNT_U16 == OpModeSts_Cnt_T_U16) || (D_IGNCRANKING_CNT_U16 == OpModeSts_Cnt_T_U16) ) )
			{
				CTermActive_Cnt_M_lgc = TRUE;

			}

			/* Operational Mode Status and VehicleSpeed check */
			else if( (D_IGNONENGON_CNT_U16 == OpModeSts_Cnt_T_U16)
				|| ((SysState_Cnt_T_Enum == RTE_MODE_StaMd_Mode_OPERATE) && (TRUE == VehicleSpeedValid_Cnt_T_lgc) &&
				 (VehicleSpeed_Kph_T_f32 > k_VehSpdEngOn_Kph_f32)))
			{
				if( ElapsedTime1_mS_T_u16 > k_CTermOpModeStsTimeout_mS_u16 )
				{
					CtermOpModeStsTimer_mS_M_u32 = SystemTime_mS_T_u32;
					CTermActive_Cnt_M_lgc = TRUE;
				}
			}

			else
			{
				CTermActive_Cnt_M_lgc = FALSE;
			}
		}
	}
	
	/* Ramp Logic */
	if( FALSE == CTermActive_Cnt_M_lgc )
	{
		OperRampRate_XpmS_T_f32 = k_RampDnRt_UlspmS_f32;
		OperRampValue_Uls_T_f32 = D_ZERO_ULS_F32;
	}

	else
	{
		OperRampRate_XpmS_T_f32 = k_RampUpRtLoSpd_UlspmS_f32;
		OperRampValue_Uls_T_f32 = D_ONE_ULS_F32;
	}
	
	if( (ATermActive_Cnt_T_lgc == FALSE) && (VehPwrMd2msCounter_Cnt_M_u16 == 500u) )
	{
		if(PowerLatchTimeDID191D_Cnt_M_u16 >= 255u)
		{
			PowerLatchTimeDID191D_Cnt_M_u16 = 255u;
		}

		else
		{
			PowerLatchTimeDID191D_Cnt_M_u16++;
		}
	}

	OpModeSts_Cnt_M_u16 = OpModeSts_Cnt_T_U16;
	
	Rte_IWrite_VehPwrMd_Per1_ATermActive_Cnt_lgc(ATermActive_Cnt_T_lgc);
	Rte_IWrite_VehPwrMd_Per1_CTermActive_Cnt_lgc(CTermActive_Cnt_M_lgc);
	Rte_IWrite_VehPwrMd_Per1_OperRampRate_XpmS_f32(OperRampRate_XpmS_T_f32);
	Rte_IWrite_VehPwrMd_Per1_OperRampValue_Uls_f32(OperRampValue_Uls_T_f32);
	Rte_IWrite_VehPwrMd_Per1_PowerLatchTimeDID191D_Cnt_u16(PowerLatchTimeDID191D_Cnt_M_u16);
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_VehPwrMd_Per1_CP1_CheckpointReached();
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_VEHPWRMD_APPL_CODE
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
