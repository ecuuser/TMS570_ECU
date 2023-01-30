/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_BVDiag.c
 *     Workspace:  C:/Users/sz1dx6/Documents/Synergy/ccm_wa/sz1dx6/BVDiag/autosar/Ap_BVDiag.dcf
 *     SW-C Type:  Ap_BVDiag
 *  Generated at:  Tue Aug 19 16:12:17 2014
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_BVDiag>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Tue Mar 15 17:16:01 2011
 * %version:           6 %
 * %derived_by:       sz1dx6 %
 * %date_modified:    Thu Nov 14 12:12:43 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 10/24/12   1       NRAR       Initial Ver- No FDD, Its based on BMW,K2XX SER to set NTC's for BatteryVolt   6561
 * 03/18/13   2       SP         BMW SER update for 0xB0 NTC                                                   7629
 * 09/11/13   3       NRAR       Implemented B1 for chrysler with a configuration const which will be turned   8712
                                 OFF if not required by specific customer 
 * 10/07/13   4       NRAR       Corrected naming convention of buildconstant used to execute B1 as per        8712
 *                               customer req
 * 11/14/13   5       Jared      A5329 correction to allow configurable enable of B1 fault via SrlComIn        9935
 * 08/19/14   6       M. Story   Allow configurable enable of B0 fault via SrlComIn                           12284
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

 *********************************************************************************************************************/

#include "Rte_Ap_BVDiag.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_BVDiag_Cfg.h"
#include "fixmath.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "SystemTime.h"

#define   D_ABOVEMAX_CNT_U16    		0x11U
#define   D_BELOWMIN_CNT_U16    		0x22U
#define   D_INDEADBAND_CNT_U16  		0x33U

#define   D_DIAGOV_CNT_U16       		1U
#define   D_DIAGLOW_CNT_U16       		2U

#define BVDIAG_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint32, AP_BVDIAG_VAR_NOINIT) BVDiag_LowSetInitBD_ms_M_u32p0;
STATIC VAR(uint32, AP_BVDIAG_VAR_NOINIT) BVDiag_LowClrInitBD_ms_M_u32p0;
STATIC VAR(uint32, AP_BVDIAG_VAR_NOINIT) BVDiag_OvSetInitBD_ms_M_u32p0; 
STATIC VAR(uint32, AP_BVDIAG_VAR_NOINIT) BVDiag_OvClrInitBD_ms_M_u32p0; 
STATIC VAR(uint32, AP_BVDIAG_VAR_NOINIT) BVDiag_UvSetInitBD_ms_M_u32;
STATIC VAR(uint32, AP_BVDIAG_VAR_NOINIT) BVDiag_UvClrInitBD_ms_M_u32;
#define BVDIAG_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

STATIC FUNC(uint16, AP_BVDIAG_CODE) ApplyHysteresis(	VAR(uint16, AUTOMATIC) BattIn_T_u10p6, 
																VAR(uint16, AUTOMATIC) HighCal_T_u10p6, 
																VAR(uint16, AUTOMATIC) LowCal_T_u10p6);

STATIC FUNC(void, AP_BVDIAG_CODE) ControlTimers(	VAR(uint16, AUTOMATIC) BattVoltage_Volts_T_u10p6,
															VAR(uint16, AUTOMATIC) CompareType_T_u16, 
															VAR(uint16, AUTOMATIC) UpperCal_T_u10p6, 
															VAR(uint16, AUTOMATIC) LowerCal_T_u10p6, 
															CONSTP2VAR(uint32, AUTOMATIC, AP_BVDIAG_CONST) SetTimer_T_ptr, 
															CONSTP2VAR(uint32, AUTOMATIC, AP_BVDIAG_CONST) ClrTimer_T_ptr, 
															VAR(uint16, AUTOMATIC) SetTimer_ms_T_u16p0, 
															VAR(uint16, AUTOMATIC) ClrTimer_ms_T_u16p0, 
															VAR(uint16, AUTOMATIC) Option_T_u16,
															VAR(boolean, AUTOMATIC) NTCB0Enbl_Cnt_T_lgc);

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
 * Float: Real in interval [-FLT_MAX...FLT_MAX] with single precision (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
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
 *   NTC_Num_PAHwVelFlt (225U)
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
 * Float: D_ZERO_ULS_F32 = 0.0F
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_BVDIAG_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: BVDiag_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_BVDiag_Per1_Batt_Volt_f32(void)
 *   Boolean Rte_IRead_BVDiag_Per1_CCLMSAActive_Cnt_lgc(void)
 *   Boolean Rte_IRead_BVDiag_Per1_NTCB0Enbl_Cnt_lgc(void)
 *   Boolean Rte_IRead_BVDiag_Per1_NTCB1Enbl_Cnt_lgc(void)
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
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_BVDIAG_APPL_CODE) BVDiag_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: BVDiag_Per1
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) BattVoltage_Volts_T_f32;
	VAR(uint16, AUTOMATIC) BattVoltage_Volts_T_u10p6;
	VAR(boolean, AUTOMATIC) MSAActive_T_lgc;
	VAR(uint16, AUTOMATIC) LowNotDetect_Volts_T_u10p6;
	VAR(uint16, AUTOMATIC) LowDetect_Volts_T_u10p6;
	VAR(uint16, AUTOMATIC) LowDetect_ms_T_u16p0;
	VAR(uint16, AUTOMATIC) LowNotDetect_ms_T_u16p0;
	VAR(uint16, AUTOMATIC) ElapsedTime_T_u16p0;
	VAR(boolean, AUTOMATIC) NTCB1Enbl_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) NTCB0Enbl_Cnt_T_lgc;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_BVDiag_Per1_CP0_CheckpointReached();

	/* MSAACTIVE is a customer provided input for BMW and will be FALSE in rest all programs */
	MSAActive_T_lgc =  Rte_IRead_BVDiag_Per1_CCLMSAActive_Cnt_lgc();
	NTCB1Enbl_Cnt_T_lgc = Rte_IRead_BVDiag_Per1_NTCB1Enbl_Cnt_lgc();
	NTCB0Enbl_Cnt_T_lgc = Rte_IRead_BVDiag_Per1_NTCB0Enbl_Cnt_lgc();

	if(MSAActive_T_lgc == FALSE)
	{
		LowNotDetect_Volts_T_u10p6 = k_LowNotDetect_Volts_u10p6;
		LowDetect_Volts_T_u10p6 = k_LowDetect_Volts_u10p6;
		LowDetect_ms_T_u16p0 = k_LowDetect_ms_u16p0;
		LowNotDetect_ms_T_u16p0 = k_LowNotDetect_ms_u16p0;
	}
	else
	{
		LowNotDetect_Volts_T_u10p6 = k_MSALowNotDetect_Volts_u10p6;
		LowDetect_Volts_T_u10p6 = k_MSALowDetect_Volts_u10p6;
		LowDetect_ms_T_u16p0 = k_MSALowDetect_ms_u16p0;
		LowNotDetect_ms_T_u16p0 = k_MSALowNotDetect_ms_u16p0;
	}
	
	
	BattVoltage_Volts_T_f32 = Rte_IRead_BVDiag_Per1_Batt_Volt_f32();
	
	BattVoltage_Volts_T_u10p6 = FPM_FloatToFixed_m(BattVoltage_Volts_T_f32, u10p6_T);
	
		/* B5 NTC- Perform Overvoltage diagnostics - uses voltage and time based hysteresis */
	ControlTimers(	BattVoltage_Volts_T_u10p6,
					D_BELOWMIN_CNT_U16,  
					k_OvDetect_Volts_u10p6,
					k_OvNotDetect_Volts_u10p6,
					&BVDiag_OvSetInitBD_ms_M_u32p0,  
					&BVDiag_OvClrInitBD_ms_M_u32p0, 
					k_OvDetect_ms_u16p0,
					k_OvNotDetect_ms_u16p0,
					D_DIAGOV_CNT_U16,
					NTCB0Enbl_Cnt_T_lgc);
		
	/* B0 NTC- Perform low voltage diagnostics - uses voltage and time based hysteresis */
	ControlTimers(	BattVoltage_Volts_T_u10p6,
					D_ABOVEMAX_CNT_U16, 
					LowNotDetect_Volts_T_u10p6,
					LowDetect_Volts_T_u10p6,
					&BVDiag_LowSetInitBD_ms_M_u32p0, 
					&BVDiag_LowClrInitBD_ms_M_u32p0, 
					LowDetect_ms_T_u16p0, 
					LowNotDetect_ms_T_u16p0, 
					D_DIAGLOW_CNT_U16,
					NTCB0Enbl_Cnt_T_lgc);
	

	/* B1 NTC - Is required by Chrysler- For other customers it is turned OFF if not required */
	#if (STD_ON == BC_B1_BATTVOLTDIAG)
	if((BattVoltage_Volts_T_u10p6 >= k_BattDiagUvMax_Volt_u10p6) && (BattVoltage_Volts_T_u10p6 < k_BattUvRecMax_Volt_u10p6) )
	{
		(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&BVDiag_UvSetInitBD_ms_M_u32);
		(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(BVDiag_UvClrInitBD_ms_M_u32, &ElapsedTime_T_u16p0);


		if(k_UvNotDetect_ms_u16p0 < ElapsedTime_T_u16p0)
		{
			#if (STD_ON == BC_B1_BATTVOLTDIAG_ELPW)
			if (NTCB1Enbl_Cnt_T_lgc == TRUE)
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_ExVoltageLow, 0x0U, NTC_STATUS_PASSED);
			}
			#else
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_ExVoltageLow, 0x0U, NTC_STATUS_PASSED);
			#endif

		}
		
	}	
	else if ((BattVoltage_Volts_T_u10p6 > k_BattDiagUvMin_Volt_u10p6) && (BattVoltage_Volts_T_u10p6 <k_BattDiagUvMax_Volt_u10p6))
	{
	 	/* If inside of voltage range, initialize "Clear" timer, run set timer.  Set fault if timer exceeds calibration */
		 (void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&BVDiag_UvClrInitBD_ms_M_u32);
		 (void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(BVDiag_UvSetInitBD_ms_M_u32, &ElapsedTime_T_u16p0);


		if(k_UvDetect_ms_u16p0 < ElapsedTime_T_u16p0)
		{
			#if (STD_ON == BC_B1_BATTVOLTDIAG_ELPW)
			if (NTCB1Enbl_Cnt_T_lgc == TRUE)
			{
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_ExVoltageLow, 0x0U, NTC_STATUS_FAILED);
			}
			#else
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_ExVoltageLow, 0x0U, NTC_STATUS_FAILED);
			#endif

		}
	}
	else
	{
		(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&BVDiag_UvSetInitBD_ms_M_u32);
		(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&BVDiag_UvClrInitBD_ms_M_u32);
	}
	#endif
	

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_BVDiag_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_BVDIAG_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
STATIC FUNC(void, AP_BVDIAG_CODE) ControlTimers(	VAR(uint16, AUTOMATIC) BattVoltage_Volts_T_u10p6,
															VAR(uint16, AUTOMATIC) CompareType_T_u16, 
															VAR(uint16, AUTOMATIC) UpperCal_T_u10p6, 
															VAR(uint16, AUTOMATIC) LowerCal_T_u10p6, 
															CONSTP2VAR(uint32, AUTOMATIC, AP_BATTERYVOLTAGE_CONST) SetTimer_T_ptr, 
															CONSTP2VAR(uint32, AUTOMATIC, AP_BATTERYVOLTAGE_CONST) ClrTimer_T_ptr, 
															VAR(uint16, AUTOMATIC) SetTimer_ms_T_u16p0, 
															VAR(uint16, AUTOMATIC) ClrTimer_ms_T_u16p0, 
															VAR(uint16, AUTOMATIC) Option_T_u16,
															VAR(boolean, AUTOMATIC) NTCB0Enbl_Cnt_T_lgc)
{
	VAR(uint16, AUTOMATIC) ElapsedTime_T_u16p0;
	VAR(uint16, AUTOMATIC) Zone_T_u16;

	/* Apply voltage hysteresis to input signal, return hysteresis state */
	Zone_T_u16 = ApplyHysteresis(BattVoltage_Volts_T_u10p6, UpperCal_T_u10p6, LowerCal_T_u10p6);
	
	/* If in "hysteresis deadband", reset both set and clear timers */
	if(Zone_T_u16 == D_INDEADBAND_CNT_U16)
	{
		(void) Rte_Call_SystemTime_GetSystemTime_mS_u32(SetTimer_T_ptr);
		(void) Rte_Call_SystemTime_GetSystemTime_mS_u32(ClrTimer_T_ptr);
	}
	else
	{
		/* Compare hysteresis state to either d_AboveMax or d_BelowMin (passed data) */
		if(Zone_T_u16 == CompareType_T_u16) 
		{
			/* Reset "set" timer.  Compute timing on "clear" signal. */
			(void) Rte_Call_SystemTime_GetSystemTime_mS_u32(SetTimer_T_ptr);
			(void) Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(*ClrTimer_T_ptr, &ElapsedTime_T_u16p0);
			
			/* Take action if timer value exceeded.  Action is a f(Option_T_u16) */
			if (ElapsedTime_T_u16p0 > ClrTimer_ms_T_u16p0)
			{
				if (Option_T_u16 == D_DIAGOV_CNT_U16)
				{
					(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_OpVoltageOvrMax, 0x0U, NTC_STATUS_PASSED);
				}
				else
				{
					#if (STD_ON == BC_B0_BATTVOLTDIAG_ELPW)
					if (NTCB0Enbl_Cnt_T_lgc == TRUE)
					{
							(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_OpVoltage, 0x0U, NTC_STATUS_PASSED);
					}
					#else
							(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_OpVoltage, 0x0U, NTC_STATUS_PASSED);
					#endif
				}	
			}
		}
		else
		{
			/* Reset "clear" timer.  Compute timing on "set" signal. */
			(void) Rte_Call_SystemTime_GetSystemTime_mS_u32(ClrTimer_T_ptr);
			(void) Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(*SetTimer_T_ptr, &ElapsedTime_T_u16p0);
			
			/* Take action if timer value exceeded.  Action is a f(Option_T_u16) */
			if (ElapsedTime_T_u16p0 > SetTimer_ms_T_u16p0)
			{
				if (Option_T_u16 == D_DIAGOV_CNT_U16)
				{
					(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_OpVoltageOvrMax, 0x01U, NTC_STATUS_FAILED);
				}
				else
				{					
					#if (STD_ON == BC_B0_BATTVOLTDIAG_ELPW)
					if (NTCB0Enbl_Cnt_T_lgc == TRUE)
					{
						(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_OpVoltage, 0x01U, NTC_STATUS_FAILED);
					}
					#else
						(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_OpVoltage, 0x01U, NTC_STATUS_FAILED);
					#endif
				}	
			}
		}
	}
}

STATIC FUNC(uint16, AP_BVDIAG_CODE) ApplyHysteresis(	VAR(uint16, AUTOMATIC) BattIn_T_u10p6, 
																VAR(uint16, AUTOMATIC) HighCal_T_u10p6, 
																VAR(uint16, AUTOMATIC) LowCal_T_u10p6)
{
	VAR(uint16, AUTOMATIC) OutputZone_T_u16;
	
	/* Set state to "above max" if input exceeds higher of the two voltage calibrations */
	if(BattIn_T_u10p6 > HighCal_T_u10p6)
	{
		OutputZone_T_u16 = D_ABOVEMAX_CNT_U16;
	}
	/* Set state to "below min" if input is less than the lower of the two voltage calibrations */
	else if(BattIn_T_u10p6 < LowCal_T_u10p6)
	{
		OutputZone_T_u16 = D_BELOWMIN_CNT_U16;
	}
	/* Otherwise, no change.  Use last value (input to function) */
	else
	{
		OutputZone_T_u16 = D_INDEADBAND_CNT_U16;
	}
	
	return(OutputZone_T_u16);
	
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
