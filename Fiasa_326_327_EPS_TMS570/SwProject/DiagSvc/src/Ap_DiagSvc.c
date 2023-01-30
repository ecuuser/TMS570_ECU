/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_DiagSvc.c
 *     Workspace:  C:/SynergyProjects/Fiasa_326_327_EPS_TMS570-nzx5jd/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *     SW-C Type:  Ap_DiagSvc
 *  Generated at:  Fri Jun  5 12:07:22 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_DiagSvc>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Tue Jul  9 10:30:00 2013
 * %version:          EA3#18 %
 * %derived_by:       mzjphh %
 * %date_modified:    Thu Jan  9 16:51:25 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date       Rev      Author   Change Description                                                               SCR #
 * --------   -------  -------  ------------------------------------------------------------------------------  -------
 * 02/27/15    2       SAH      Added condition around jump to boot code
 * 08/28/15    4       PS        Update customer service 0x0200 											  EA3#2837, EA3#2838, EA3#2839
								and fix Anomaly's EA3#2099, EA3#2328, EA3#2405, EA3#2407   					  EA3#2840, EA3#2841
* 15/15/15     5       PS       Implemented software according to SCIR 3A and DSR 2A						  EA3#3742
* 10/30/15     6       PS       Implemented software according to SCIR 4A and DSR 3A						  EA3#4252
* 11/06/15     7       PS       Fix Anomaly's EA3#4375, EA3#4392											  EA3#4436, EA3#4437
* 11/16/15     8       PS       Implemented software according to SCIR 5A and DSR 5A	 					  EA3#4579
* 12/01/15     11      PS       Implemented software according to SCIR 5A and DSR 6A	 					  EA3#4681, EA3#4686
* 01/16/16     12      PS       Update to DID 5AAB and fix for NTC 0x100	 					  			  EA3#5629, EA3#5628
* 01/22/16     13      PS       Update to DID's 5051, 5052, 5AAB and FD03 					  				  EA3#5746
* 03/16/16     14      PS       Update to DID's 0x2003,0x200A,0x5051,0x5AAB and RID 0x0200
								Added DID's 0x2001, 0x2002													  EA3#6773, EA3#6775
* 04/01/16     15      PS       Update to DID F181 and RID 0x0200 					  				  		  EA3#7178
* 08/01/16     16      PS       Updated RID 0x0200 to fix anomaly EA3#9955					 				  EA3#9969
* 08/01/16     17      PS       Replace response of RID 0x0200 (Request results) to 0x04					  EA3#9996
* 10/06/16     18      NS       Changed Proxi valid check 													  EA3#11533
* 03/06/17	   19      NS       Added F187 write service													  EA3#14544
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

#include "Rte_Ap_DiagSvc.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Ap_DiagSvc.h"

#define DIAGSVC_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_DIAGSVC_VAR) DiagSvc_FirstDTCDetected_Cnt_M_lgc;
STATIC VAR(boolean, AP_DIAGSVC_VAR) DiagSvc_HardReset_Cnt_M_lgc;
STATIC VAR(boolean, AP_DIAGSVC_VAR) DiagSvc_IOCtrl5051Enable_Cnt_M_lgc;
STATIC VAR(boolean, AP_DIAGSVC_VAR) DiagSvc_IOCtrl5aabEnable_Cnt_M_lgc;
STATIC VAR(boolean, AP_DIAGSVC_VAR) DiagSvc_Routine0200ClrTrimEn_Cnt_M_lgc;
STATIC VAR(boolean, AP_DIAGSVC_VAR) DiagSvc_Routine0200FailReason_Cnt_M_u08;
STATIC VAR(boolean, AP_DIAGSVC_VAR) DiagSvc_Routine0200SetTrimEn_Cnt_M_lgc;
STATIC VAR(boolean, AP_DIAGSVC_VAR) DiagSvc_SoftReset_Cnt_M_lgc;
#define DIAGSVC_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define DIAGSVC_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint8, AP_DIAGSVC_VAR) DiagSvc_ProxiErrorCount_Cnt_M_u08;
STATIC VAR(uint8, AP_DIAGSVC_VAR) DiagSvc_ProxiErrorStatus_Cnt_M_u08[9];
#define DIAGSVC_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */

#define DIAGSVC_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint32,  AP_DIAGSVC_VAR) DiagSvc_Timer_mS_M_u32;
STATIC VAR(uint32,  AP_DIAGSVC_VAR) DiagSvc_ECULifeTimeMinsInitial_Cnt_M_u32;
STATIC VAR(uint32,  AP_DIAGSVC_VAR) DiagSvc_IOCtrlTimer1_mS_M_u32;
STATIC VAR(uint32,  AP_DIAGSVC_VAR) DiagSvc_IOCtrlTimer2_mS_M_u32;
#define DIAGSVC_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

/* Global Proxi check data - used in SrlComOutput */
VAR(uint8, AP_DIAGSVC_VAR) DiagSvc_ProxiCheckData_Cnt_u08[11] = {0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au};

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
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * SInt32: Integer in interval [-2147483648...2147483647] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * Dcm_ConfirmationStatusType: Enumeration of integer in interval [0...3] with enumerators
 *   DCM_RES_POS_OK (0U)
 *   DCM_RES_POS_NOT_OK (1U)
 *   DCM_RES_NEG_OK (2U)
 *   DCM_RES_NEG_NOT_OK (3U)
 * Dcm_NegativeResponseCodeType: Enumeration of integer in interval [0...255] with enumerators
 *   DCM_E_GENERALREJECT (16U)
 *   DCM_E_SERVICENOTSUPPORTED (17U)
 *   DCM_E_SUBFUNCTIONNOTSUPPORTED (18U)
 *   DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT (19U)
 *   DCM_E_RESPONSE_TOO_LONG (20U)
 *   DCM_E_BUSYREPEATREQUEST (33U)
 *   DCM_E_CONDITIONSNOTCORRECT (34U)
 *   DCM_E_REQUESTSEQUENCEERROR (36U)
 *   DCM_E_REQUESTOUTOFRANGE (49U)
 *   DCM_E_SECURITYACCESSDENIED (51U)
 *   DCM_E_INVALIDKEY (53U)
 *   DCM_E_EXCEEDNUMBEROFATTEMPTS (54U)
 *   DCM_E_REQUIREDTIMEDELAYNOTEXPIRED (55U)
 *   DCM_E_UPLOADDOWNLOADNOTACCEPTED (112U)
 *   DCM_E_TRANSFERDATASUSPENDED (113U)
 *   DCM_E_GENERALPROGRAMMINGFAILURE (114U)
 *   DCM_E_WRONGBLOCKSEQUENCECOUNTER (115U)
 *   DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING (120U)
 *   DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION (126U)
 *   DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION (127U)
 *   DCM_E_RPMTOOHIGH (129U)
 *   DCM_E_RPMTOOLOW (130U)
 *   DCM_E_ENGINEISRUNNING (131U)
 *   DCM_E_ENGINEISNOTRUNNING (132U)
 *   DCM_E_ENGINERUNTIMETOOLOW (133U)
 *   DCM_E_TEMPERATURETOOHIGH (134U)
 *   DCM_E_TEMPERATURETOOLOW (135U)
 *   DCM_E_VEHICLESPEEDTOOHIGH (136U)
 *   DCM_E_VEHICLESPEEDTOOLOW (137U)
 *   DCM_E_THROTTLE_PEDALTOOHIGH (138U)
 *   DCM_E_THROTTLE_PEDALTOOLOW (139U)
 *   DCM_E_TRANSMISSIONRANGENOTINNEUTRAL (140U)
 *   DCM_E_TRANSMISSIONRANGENOTINGEAR (141U)
 *   DCM_E_BRAKESWITCH_NOTCLOSED (143U)
 *   DCM_E_SHIFTERLEVERNOTINPARK (144U)
 *   DCM_E_TORQUECONVERTERCLUTCHLOCKED (145U)
 *   DCM_E_VOLTAGETOOHIGH (146U)
 *   DCM_E_VOLTAGETOOLOW (147U)
 * Dcm_SecLevelType: Enumeration of integer in interval [0...255] with enumerators
 *   DCM_SEC_LEV_LOCKED (0U)
 *   DCM_SEC_LEV_L1 (1U)
 *   DCM_SEC_LEV_ALL (255U)
 * Dcm_SesCtrlType: Enumeration of integer in interval [1...255] with enumerators
 *   DCM_DEFAULT_SESSION (1U)
 *   DCM_PROGRAMMING_SESSION (2U)
 *   DCM_EXTENDED_DIAGNOSTIC_SESSION (3U)
 *   DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION (4U)
 *   NEXTEER (126U)
 *   DCM_ALL_SESSION_LEVEL (255U)
 * ManufModeType: Enumeration of integer in interval [0...2] with enumerators
 *   ProductionMode (0U)
 *   ManufacturingMode (1U)
 *   EngineeringMode (2U)
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
 * NvM_RequestResultType: Enumeration of integer in interval [0...5] with enumerators
 *   NVM_REQ_OK (0U)
 *   NVM_REQ_NOT_OK (1U)
 *   NVM_REQ_PENDING (2U)
 *   NVM_REQ_INTEGRITY_FAILED (3U)
 *   NVM_REQ_BLOCK_SKIPPED (4U)
 *   NVM_REQ_NV_INVALIDATED (5U)
 * NxtrDiagMgrStatus: Enumeration of integer in interval [0...255] with enumerators
 *   NTC_STATUS_PASSED (0U)
 *   NTC_STATUS_FAILED (1U)
 *   NTC_STATUS_PREPASSED (2U)
 *   NTC_STATUS_PREFAILED (3U)
 *
 * Array Types:
 * ============
 * Dcm_0Byte_Type: Array with 1 element(s) of type UInt8
 * Dcm_10Byte_Type: Array with 10 element(s) of type UInt8
 * Dcm_12Byte_Type: Array with 12 element(s) of type UInt8
 * Dcm_16Byte_Type: Array with 16 element(s) of type UInt8
 * Dcm_176Byte_Type: Array with 176 element(s) of type UInt8
 * Dcm_18Byte_Type: Array with 18 element(s) of type UInt8
 * Dcm_1Byte_Type: Array with 1 element(s) of type UInt8
 * Dcm_256Byte_Type: Array with 256 element(s) of type UInt8
 * Dcm_25Byte_Type: Array with 25 element(s) of type UInt8
 * Dcm_28Byte_Type: Array with 28 element(s) of type UInt8
 * Dcm_2Byte_Type: Array with 2 element(s) of type UInt8
 * Dcm_322Byte_Type: Array with 322 element(s) of type UInt8
 * Dcm_3Byte_Type: Array with 3 element(s) of type UInt8
 * Dcm_4Byte_Type: Array with 4 element(s) of type UInt8
 * Dcm_5Byte_Type: Array with 5 element(s) of type UInt8
 * Dcm_64Byte_Type: Array with 64 element(s) of type UInt8
 * Dcm_6Byte_Type: Array with 6 element(s) of type UInt8
 * Dcm_75Byte_Type: Array with 75 element(s) of type UInt8
 * Dcm_7Byte_Type: Array with 7 element(s) of type UInt8
 * Dcm_8Byte_Type: Array with 8 element(s) of type UInt8
 * Dcm_SecAccess_1_DataRecType: Array with 1 element(s) of type UInt8
 * Dcm_SecAccess_1_KeyType: Array with 4 element(s) of type UInt8
 * Dcm_SecAccess_1_SeedType: Array with 4 element(s) of type UInt8
 * NvM_DestPtr: Array with 65535 element(s) of type UInt8
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


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   UInt16 *Rte_Pim_TuningSetSelectData(void)
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   UInt8 *Rte_Pim_SparePartNumberData(void)
#else
 *   Dcm_10Byte_Type *Rte_Pim_SparePartNumberData(void)
#endif
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   UInt8 *Rte_Pim_SupplierIdentifierData(void)
#else
 *   Dcm_10Byte_Type *Rte_Pim_SupplierIdentifierData(void)
#endif
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_DIAGSVC_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ComControlService_CheckCondition
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <CheckCondition> of PortPrototype <ComControlService>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType ComControlService_CheckCondition(UInt8 subNetId, UInt8 msgType, Boolean rxState, Boolean txState)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_ComControlService_E_COM_CTRL_NOT_ACCEPTED
 *   RTE_E_ComControlService_E_PENDING
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) ComControlService_CheckCondition(UInt8 subNetId, UInt8 msgType, Boolean rxState, Boolean txState)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ComControlService_CheckCondition (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DiagSvc_Init1
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
 *   ManufModeType Rte_IRead_DiagSvc_Init1_MEC_Cnt_enum(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_DiagSvc_Init1_DesiredTunSet_Cnt_u16(UInt16 data)
 *   UInt16 *Rte_IWriteRef_DiagSvc_Init1_DesiredTunSet_Cnt_u16(void)
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
 *   Std_ReturnType Rte_Call_TuningSetSelect_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DiagSvc_Init1
 *********************************************************************************************************************/
	
	VAR(ManufModeType, AUTOMATIC) MEC_Cnt_T_enum;
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;

	VAR(uint32, AUTOMATIC) SystemTime_mS_T_u32;

	VAR(uint16, AUTOMATIC) i;
	VAR(uint16, AUTOMATIC) TuningSet_Cnt_T_u16;

	VAR(uint8,  AUTOMATIC) IgnitionPreStartData_T_u08;
	VAR(uint8,  AUTOMATIC) StartStopEnablea_T_u08;

	VAR(boolean, AUTOMATIC) IgnitionPreStart_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) StartStopLogicEnable_Cnt_T_lgc;

	
	MEC_Cnt_T_enum = Rte_IRead_DiagSvc_Init1_MEC_Cnt_enum();
	
	/* Tuning set */
	(void)Rte_Call_TuningSetSelect_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum != NVM_REQ_OK )
	{
		TuningSet_Cnt_T_u16 = 0u;
		*Rte_Pim_TuningSetSelectData() = 0u;
		if( MEC_Cnt_T_enum == ProductionMode )
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_FAILED);
		}
	}

	else
	{
		TuningSet_Cnt_T_u16 = *Rte_Pim_TuningSetSelectData();
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_PASSED);
	}
	
	/* Ignition Pre Start logic - PROXI Config data & StartStop Logic */
	(void)Rte_Call_ProxiConfiguration_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum != NVM_REQ_OK )
	{
		IgnitionPreStartData_T_u08 = D_DATAFILLER_CNT_U08;
		StartStopEnablea_T_u08 = 0xFFU;
	}

	else
	{
		IgnitionPreStartData_T_u08 = (uint8) ( (((*Rte_Pim_ProxiConfigurationData())[93]) & 0x80U) >> 0x07U);
		StartStopEnablea_T_u08 = (uint8) ( ((*Rte_Pim_ProxiConfigurationData())[133U]) & 0x03U );
	}
	
	(IgnitionPreStartData_T_u08 == D_DATAFILLER_CNT_U08) ? (IgnitionPreStart_Cnt_T_lgc = FALSE) : (IgnitionPreStart_Cnt_T_lgc = TRUE);
	(StartStopEnablea_T_u08 == D_DATAFILLER_CNT_U08) ? (StartStopLogicEnable_Cnt_T_lgc = TRUE) : (StartStopLogicEnable_Cnt_T_lgc = FALSE);

	
	/* ECU LIfe Time */
	(void)Rte_Call_ECULifeTimeMins_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		DiagSvc_ECULifeTimeMinsInitial_Cnt_M_u32 = *Rte_Pim_ECULifeTimeMinsData();
	}
	
	else
	{
		DiagSvc_ECULifeTimeMinsInitial_Cnt_M_u32 = 0x00000000U;
	}
		
	DiagSvc_FirstDTCDetected_Cnt_M_lgc = FALSE;
	(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&SystemTime_mS_T_u32);
	DiagSvc_Timer_mS_M_u32 = SystemTime_mS_T_u32;

	DiagSvc_IOCtrl5051Enable_Cnt_M_lgc = FALSE;
	DiagSvc_IOCtrl5aabEnable_Cnt_M_lgc = FALSE;

	DiagSvc_Routine0200ClrTrimEn_Cnt_M_lgc = FALSE;
	DiagSvc_Routine0200FailReason_Cnt_M_u08 = 0x00U;
	DiagSvc_Routine0200SetTrimEn_Cnt_M_lgc = FALSE;

	Rte_IWrite_DiagSvc_Init1_IgnitionPreStart_Cnt_lgc(IgnitionPreStart_Cnt_T_lgc);
	Rte_IWrite_DiagSvc_Init1_DesiredTunSet_Cnt_u16(TuningSet_Cnt_T_u16);
    Rte_IWrite_DiagSvc_Init1_StartStopLogicEnable_Cnt_lgc(StartStopLogicEnable_Cnt_T_lgc);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DiagSvc_Per1
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
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *
 *********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_Per1(void)
{
	VAR(uint32, AUTOMATIC) SystemTime_mS_T_u32;

	VAR(uint16, AUTOMATIC) ElapsedTime_mS_T_u16;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;

	VAR(uint8,  AUTOMATIC) data_Cnt_T_u08[4] = { 0x00U, 0x00U, 0x00U, 0x00U };

	VAR(CityUserEnableDisable,  AUTOMATIC) CityUserEnableDisable_Cnt_T_enum;

	VAR(Std_ReturnType, AUTOMATIC) RetVal_Cnt_T_enum;

	VAR(uint8,  AUTOMATIC) NvMProxiStatusDigColPs_Cnt_T_u08;

	/* 0x2F service - 0x5051 Return back the control to ECU after 30s */
	if( DiagSvc_IOCtrl5051Enable_Cnt_M_lgc == FALSE )
	{
		ResetIOCtrlTimer(&DiagSvc_IOCtrlTimer1_mS_M_u32);
	}

	Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(DiagSvc_IOCtrlTimer1_mS_M_u32, &ElapsedTime_mS_T_u16);
	if(ElapsedTime_mS_T_u16 >= D_IOCONTROLTIMEOUT_MS_U16)
	{
		DiagSvc_IOCtrl5051Enable_Cnt_M_lgc = FALSE;
		(void)EPSInternal_PID_FD02 (0x2Eu, &data_Cnt_T_u08[0], 0x4U, &RespLen_Cnt_T_u16);
	}

	/* 0x2F service - 0x5AAB Return back the control to ECU after 30s */
	if( DiagSvc_IOCtrl5aabEnable_Cnt_M_lgc == FALSE )
	{
		ResetIOCtrlTimer(&DiagSvc_IOCtrlTimer2_mS_M_u32);
	}

	(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(DiagSvc_IOCtrlTimer2_mS_M_u32, &ElapsedTime_mS_T_u16);
	if(ElapsedTime_mS_T_u16 >= D_IOCONTROLTIMEOUT_MS_U16)
	{
		DiagSvc_IOCtrl5aabEnable_Cnt_M_lgc = FALSE;
		CityUserEnableDisable_Cnt_T_enum = ReturnControlToECU;
		Rte_Write_CityUserEnableDisable_Cnt_enum(CityUserEnableDisable_Cnt_T_enum);
	}


	/* Routine 0x0200 - Steering Angle Calibration */
	if(DiagSvc_Routine0200ClrTrimEn_Cnt_M_lgc == TRUE)
	{
		/* Clear Trim NvM Error Status Check */
		NvMProxy_GetErrorStatus(D_NVMPXYDIGCOLPSBLK_CNT_U08, &NvMProxiStatusDigColPs_Cnt_T_u08);

		if( NvMProxiStatusDigColPs_Cnt_T_u08 == NVM_REQ_PENDING )
		{
			/* Continue monitoring error status */
			DiagSvc_Routine0200FailReason_Cnt_M_u08 = DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING;
		}

		else
		{
			/* Set Trim */
			RetVal_Cnt_T_enum = Rte_Call_DigColPs_SCom_CustSetTrim();
			DiagSvc_Routine0200ClrTrimEn_Cnt_M_lgc = FALSE;
			if( RetVal_Cnt_T_enum == RTE_E_OK)
			{
				DiagSvc_Routine0200SetTrimEn_Cnt_M_lgc = TRUE;
			}
			else
			{
				DiagSvc_Routine0200SetTrimEn_Cnt_M_lgc = FALSE;
			}

		}
	}

	if( DiagSvc_Routine0200SetTrimEn_Cnt_M_lgc == TRUE )
	{
		/* Set Trim NvM Error Status Check */
		NvMProxy_GetErrorStatus(D_NVMPXYDIGCOLPSBLK_CNT_U08, &NvMProxiStatusDigColPs_Cnt_T_u08);

		if( NvMProxiStatusDigColPs_Cnt_T_u08 == RTE_CONST_NVM_REQ_OK )
		{
			DiagSvc_Routine0200FailReason_Cnt_M_u08 = D_EPSNRCNOERROR_CNT_U08;
			DiagSvc_Routine0200SetTrimEn_Cnt_M_lgc = FALSE;
		}

		else if( NvMProxiStatusDigColPs_Cnt_T_u08 == NVM_REQ_PENDING )
		{
			/* Continue monitoring error status */
			DiagSvc_Routine0200FailReason_Cnt_M_u08 = DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING;
		}

		else
		{
			DiagSvc_Routine0200FailReason_Cnt_M_u08 = DCM_E_CONDITIONSNOTCORRECT;
			DiagSvc_Routine0200SetTrimEn_Cnt_M_lgc = FALSE;
		}
	}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DiagSvc_Trns1
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
 *
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
 *   Std_ReturnType Rte_Call_ECULifeTimeMins_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_ECULifeTimeMins_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 *********************************************************************************************************************/
FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_Trns1(void)
{
	VAR(uint32,  AUTOMATIC) ElapsedTime_mS_T_u32;
	VAR(uint32,  AUTOMATIC) ElapsedTime_min_T_u32;
	VAR(uint32, AUTOMATIC) TotalOdometer_Cnt_T_u32;

	VAR(uint16, AUTOMATIC) TotalOdometer_Cnt_T_u16;

	/* ECU Life TIme */
	(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(DiagSvc_Timer_mS_M_u32, &ElapsedTime_mS_T_u32);
	ElapsedTime_min_T_u32 = ElapsedTime_mS_T_u32 / (1000u * 60u); /* converting ms to min */
	ElapsedTime_min_T_u32 += DiagSvc_ECULifeTimeMinsInitial_Cnt_M_u32;
	*Rte_Pim_ECULifeTimeMinsData() = ElapsedTime_min_T_u32;
	(void)Rte_Call_ECULifeTimeMins_WriteBlock(NULL_PTR);

	/* Ignition counter - DID 0x2001 */
	Rte_Read_TotalOdometerIPC_Cnt_u32(&TotalOdometer_Cnt_T_u32);
	TotalOdometer_Cnt_T_u16 = (uint16) (TotalOdometer_Cnt_T_u32 / 16U);
	*Rte_Pim_TotalOdometerData() = TotalOdometer_Cnt_T_u16;
	(void)Rte_Call_TotalOdometer_WriteBlock(NULL_PTR);
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DiagSvc_SCom_GetTuningSet
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <GetTuningSet> of PortPrototype <DiagSvc_SCom>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_TuningSetSelect_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void DiagSvc_SCom_GetTuningSet(UInt8 *TuningSet_Cnt_T_u08)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_SCom_GetTuningSet(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) TuningSet_Cnt_T_u08)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DiagSvc_SCom_GetTuningSet
 *********************************************************************************************************************/
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	
	(void)Rte_Call_TuningSetSelect_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum != NVM_REQ_OK )
	{
		*TuningSet_Cnt_T_u08 = 0u;
	}
	else
	{
		*TuningSet_Cnt_T_u08 = (uint8)(*Rte_Pim_TuningSetSelectData() + 1u);
	}
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DiagSvc_SCom_SetTuningSet
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <SetTuningSet> of PortPrototype <DiagSvc_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MEC_Cnt_enum(ManufModeType *data)
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
 *   Std_ReturnType Rte_Call_TuningSetSelect_InvalidateNvBlock(void)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_TuningSetSelect_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_TuningSetSelect_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DiagSvc_SCom_SetTuningSet(UInt8 TuningSet_Cnt_T_u08)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DiagSvc_SCom_E_OUTOFRANGE
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_SCom_SetTuningSet(UInt8 TuningSet_Cnt_T_u08)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DiagSvc_SCom_SetTuningSet (returns application error)
 *********************************************************************************************************************/
	
	VAR(Std_ReturnType, AUTOMATIC) RetVal_Cnt_T_enum;
	VAR(ManufModeType, AUTOMATIC) MEC_Cnt_T_enum;
	
	Rte_Read_MEC_Cnt_enum(&MEC_Cnt_T_enum);
	
	if( TuningSet_Cnt_T_u08 > D_NUMOFTUNSETS_CNT_U16 )
	{
		RetVal_Cnt_T_enum = D_EPSNRCREQUESTDATAOUTOFRANGE_CNT_U08;
	}
	else if( TuningSet_Cnt_T_u08 == 0u )
	{
		*Rte_Pim_TuningSetSelectData() = 0u;
		(void)Rte_Call_TuningSetSelect_InvalidateNvBlock();
		if( MEC_Cnt_T_enum == ProductionMode )
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_FAILED);
		}
		
		RetVal_Cnt_T_enum = RTE_E_OK;
	}
	else
	{
		*Rte_Pim_TuningSetSelectData() = (uint8) (TuningSet_Cnt_T_u08 - 1u);
		(void)Rte_Call_TuningSetSelect_WriteBlock(NULL_PTR);
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_PASSED);
		
		RetVal_Cnt_T_enum = RTE_E_OK;
	}
	
	return RetVal_Cnt_T_enum;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x0100_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x0100>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_TuningSetSelect_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x0100_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x0100_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0100_E_NOT_OK
 *   RTE_E_DidServices_0x0100_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x0100_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	
	(void)Rte_Call_TuningSetSelect_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum != NVM_REQ_OK )
	{
		(*data)[0] = 0u;
	}
	else
	{
		(*data)[0] = (uint8)(*Rte_Pim_TuningSetSelectData() + 1u);
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x0100_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0x0100>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MEC_Cnt_enum(ManufModeType *data)
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
 *   Std_ReturnType Rte_Call_TuningSetSelect_InvalidateNvBlock(void)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_TuningSetSelect_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_TuningSetSelect_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x0100_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0x0100_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0100_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x0100_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(ManufModeType, AUTOMATIC) MEC_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) TuningSet_Cnt_T_u16;
	
	Rte_Read_MEC_Cnt_enum(&MEC_Cnt_T_enum);
	
	TuningSet_Cnt_T_u16 = (uint16)((*data)[0]);
	
	if( TuningSet_Cnt_T_u16 > D_NUMOFTUNSETS_CNT_U16 )
	{
		*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
	}
	else if( TuningSet_Cnt_T_u16 == 0u )
	{
		*Rte_Pim_TuningSetSelectData() = 0u;
		(void)Rte_Call_TuningSetSelect_InvalidateNvBlock();
		if( MEC_Cnt_T_enum == ProductionMode )
		{
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_FAILED);
		}
	}
	else
	{
		*Rte_Pim_TuningSetSelectData() = TuningSet_Cnt_T_u16 - 1u;
		(void)Rte_Call_TuningSetSelect_WriteBlock(NULL_PTR);
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_PASSED);
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x0885_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x0100>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x0885_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x0885_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0885_E_NOT_OK
 *   RTE_E_DidServices_0x0885_E_PENDING
 *
 *********************************************************************************************************************/

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0885_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0885_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x0885_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(float32, AUTOMATIC) HwDeg_T_f32;
	VAR(UInt16, AUTOMATIC) HwDeg_T_u16;

	(void)Rte_Read_HwPos_HwDeg_f32(&HwDeg_T_f32);

	HwDeg_T_f32 = Limit_m(HwDeg_T_f32, -2048.0f, 2047.9f);

	HwDeg_T_f32 = HwDeg_T_f32 / D_STEERINGANGLESENSOR_CNT_F32;

	HwDeg_T_u16 = (UInt16) Abs_f32_m(HwDeg_T_f32);

	/* 2's complement */
	if(HwDeg_T_f32 < 0.0f)
	{
		HwDeg_T_u16 = Redundant_Format_1_m(HwDeg_T_u16) + 1U;
	}

	(*data)[0] = (UInt8) ((HwDeg_T_u16 & 0xFF00U) >> 0x08U);
	(*data)[1] = (UInt8) (HwDeg_T_u16 & 0x00FFU);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x0ad9_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x0ad9>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x0ad9_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x0ad9_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0ad9_E_NOT_OK
 *   RTE_E_DidServices_0x0ad9_E_PENDING
 *
 *********************************************************************************************************************/

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ad9_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ad9_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x0ad9_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(UInt8, AUTOMATIC) TuningSet_Cnt_T_u08;
	
	DiagSvc_SCom_GetTuningSet(&TuningSet_Cnt_T_u08);
	
	(*data)[0] = TuningSet_Cnt_T_u08;
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x0ada_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x0adb>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x0ada_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x0ada_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0ada_E_NOT_OK
 *   RTE_E_DidServices_0x0ada_E_PENDING
 *
 *********************************************************************************************************************/

 # ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ada_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ada_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif

{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x0ada_ReadData (returns application error)
 *********************************************************************************************************************/

    VAR(boolean, AUTOMATIC) ElecStrFailSts_Cnt_T_lgc;
	
	(void)Rte_Read_ElectricStrFailSts_Cnt_lgc(&ElecStrFailSts_Cnt_T_lgc);

	(*data)[0] = D_DATAFILLER_CNT_U08;
	
	/* Angler Sensor Type */
	if( k_CustDIDCals_Cnt_u08.AbsAngleSensorType_Cnt_lgc == TRUE )
	{
		(*data)[0] |= 0x08U;
	}
	
	/* GE (0xDE) - ElectricSteeringFailSts */
	if( ElecStrFailSts_Cnt_T_lgc == TRUE )
	{
		(*data)[0] |= 0x20U;
	}
	
	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x0adb_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x0adb>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x0adb_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x0adb_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0adb_E_NOT_OK
 *   RTE_E_DidServices_0x0adb_E_PENDING
 *
 *********************************************************************************************************************/

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0adb_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0adb_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x0adb_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(float32, AUTOMATIC) HwNm_T_f32;
	VAR(UInt16, AUTOMATIC) HwNm_T_u16;

	(void)Rte_Read_HwTrq_HwNm_f32(&HwNm_T_f32);

	HwNm_T_f32 = Limit_m(HwNm_T_f32, -16.0f, 15.88f);

	HwNm_T_f32 = HwNm_T_f32 / D_DRIVERTORQUE_CNT_F32;

	HwNm_T_u16 = (UInt16) Abs_f32_m(HwNm_T_f32);

	/* 2's complement */
	if(HwNm_T_f32 < 0.0f)
	{
		HwNm_T_u16 = Redundant_Format_1_m(HwNm_T_u16) + 1U;
	}

	(*data)[0] = (UInt8) (HwNm_T_u16 & 0xFFU);
	
	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x0adc_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x0adb>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x0adc_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x0adc_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0adc_E_NOT_OK
 *   RTE_E_DidServices_0x0adc_E_PENDING
 *
 *********************************************************************************************************************/

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0adc_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0adc_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x0adc_ReadData (returns application error)
 *********************************************************************************************************************/
 
	VAR(boolean, AUTOMATIC) CityModeSts_Cnt_T_lgc;
	
	(void)Rte_Read_CityModeSts_Cnt_lgc(&CityModeSts_Cnt_T_lgc);
	
	if( CityModeSts_Cnt_T_lgc == TRUE )
	{
		(*data)[0] = 0x01U;
	}
	
	else
	{
		(*data)[0] = D_DATAFILLER_CNT_U08;
	}
	
	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x0ade_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x0adb>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x0ade_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x0ade_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0ade_E_NOT_OK
 *   RTE_E_DidServices_0x0ade_E_PENDING
 *
 *********************************************************************************************************************/

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ade_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0ade_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x0ade_ReadData (returns application error)
 *********************************************************************************************************************/

	VAR(float32, AUTOMATIC) ECUTemperature_T_f32;
	VAR(uint16, AUTOMATIC) ECUTemperature_T_u16;
	
	(void)Rte_Read_Temperature_DegC_f32_DegC_f32(&ECUTemperature_T_f32);

	ECUTemperature_T_f32 = Limit_m(ECUTemperature_T_f32, -328.0f, 328.0f);

	ECUTemperature_T_f32 = ECUTemperature_T_f32 / D_ECUTEMPERATURE_CNT_F32;

	ECUTemperature_T_u16 = (UInt16) Abs_f32_m(ECUTemperature_T_f32);

	/* 2's complement */
	if(ECUTemperature_T_f32 < 0.0f)
	{
		ECUTemperature_T_u16 = Redundant_Format_1_m(ECUTemperature_T_u16) + 1U;
	}

	(*data)[0] = (UInt8) ((ECUTemperature_T_u16 & 0xFF00U) >> 8U);
	(*data)[1] = (UInt8) (ECUTemperature_T_u16 & 0x00FFU);
	
	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x1002_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1002>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x1002_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x1002_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x1002_E_NOT_OK
 *   RTE_E_DidServices_0x1002_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1002_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1002_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x1002_ReadData (returns application error)
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(UInt16, AUTOMATIC) VehSpd_Kph_T_u16;

	(void)Rte_Read_VehSpd_Kph_f32(&VehSpd_Kph_T_f32);

	VehSpd_Kph_T_f32 = Limit_m(VehSpd_Kph_T_f32, 0.0f, 255.0f);

	VehSpd_Kph_T_u16 = (UInt16) VehSpd_Kph_T_f32;

	(*data)[0] = (UInt8) (VehSpd_Kph_T_u16 & 0x00FFU);
 
	return RTE_E_OK;
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x1004_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x1004_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x1004_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x1004_E_NOT_OK
 *   RTE_E_DidServices_0x1004_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1004_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1004_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x1004_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(Float, AUTOMATIC) BattVoltage_Volts_T_f32;
	VAR(UInt16, AUTOMATIC) BattVoltage_Volts_T_u16;

    (void) Rte_Read_Vecu_Volt_f32_Volt_f32(&BattVoltage_Volts_T_f32);

    BattVoltage_Volts_T_f32 = Limit_m(BattVoltage_Volts_T_f32, 0.0f, 25.5f);

	BattVoltage_Volts_T_f32 = BattVoltage_Volts_T_f32 / D_BATTERYVOLTAGE_CNT_F32;

	BattVoltage_Volts_T_u16 = (UInt16) BattVoltage_Volts_T_f32;

	(*data)[0] = (UInt8) (BattVoltage_Volts_T_u16 & 0x00FFU);

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x1006_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x1006_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x1006_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x1006_E_NOT_OK
 *   RTE_E_DidServices_0x1006_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1006_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1006_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x1006_ReadData (returns application error)
*********************************************************************************************************************/
	
	VAR(Float, AUTOMATIC) BattVoltage_Volts_T_f32;
	VAR(UInt16, AUTOMATIC) BattVoltage_Volts_T_u16;

    (void) Rte_Read_Vecu_Volt_f32_Volt_f32(&BattVoltage_Volts_T_f32);

	BattVoltage_Volts_T_f32 = BattVoltage_Volts_T_f32 / D_BATTERYVOLTAGE_CNT_F32;

	BattVoltage_Volts_T_u16 = (UInt16) BattVoltage_Volts_T_f32;

	(*data)[0] = (UInt8) (BattVoltage_Volts_T_u16 & 0x00FFU);

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x1008_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1008>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x1008_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x1008_ReadData(Dcm_3Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x1008_E_NOT_OK
 *   RTE_E_DidServices_0x1008_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1008_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1008_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x1008_ReadData (returns application error)
*********************************************************************************************************************/
	
	VAR(uint32,  AUTOMATIC) ElapsedTime_mS_T_u32;
	VAR(uint32,  AUTOMATIC) ElapsedTime_min_T_u32;

	(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(DiagSvc_Timer_mS_M_u32, &ElapsedTime_mS_T_u32);

	ElapsedTime_min_T_u32 = ElapsedTime_mS_T_u32 / (1000u * 60u); /* converting ms to min */

	ElapsedTime_min_T_u32 += DiagSvc_ECULifeTimeMinsInitial_Cnt_M_u32;

	(*data)[0] = (UInt8) ( (ElapsedTime_min_T_u32 & 0x00FF0000U) >> 16U );
	(*data)[1] = (UInt8) ( (ElapsedTime_min_T_u32 & 0x0000FF00U) >> 8U );
	(*data)[2] = (UInt8) ( (ElapsedTime_min_T_u32 & 0x000000FFU) );

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x1009_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x1009_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x1009_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x1009_E_NOT_OK
 *   RTE_E_DidServices_0x1009_E_PENDING
 *
 *********************************************************************************************************************/ 
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1009_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1009_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x1009_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;
	VAR(uint16,  AUTOMATIC) ElapsedTime_sec_T_u16;
	VAR(uint32,  AUTOMATIC) ElapsedTime_mS_T_u32;
	VAR(uint32,  AUTOMATIC) ElapsedTime_sec_T_u32;

	(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(DiagSvc_Timer_mS_M_u32, &ElapsedTime_mS_T_u32);

	ElapsedTime_sec_T_u32 = ElapsedTime_mS_T_u32 / (1000u * D_ECULIFETIMESECS_CNT_F32); /* converting ms to sec */

	ElapsedTime_sec_T_u16 = (uint16) ElapsedTime_sec_T_u32;

	(*data)[0] = (UInt8) ( (ElapsedTime_sec_T_u16 & 0xFF00U) >> 8U );
	(*data)[1] = (UInt8) ( (ElapsedTime_sec_T_u16 & 0x00FFU) );

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x102a_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x102a_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x102a_ReadData(Dcm_9Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x102a_E_NOT_OK
 *   RTE_E_DidServices_0x102a_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x102a_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x102a_ReadData(P2VAR(Dcm_9Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x102a_ReadData (returns application error)
*********************************************************************************************************************/
	VAR(uint16, AUTOMATIC) i;
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;

	(void)Rte_Call_EOLConfiguration_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = (*RtePim_EOLConfigurationData())[i];
		}
	}

	else
	{
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_DATAFILLER_CNT_U08;
		}
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x191d_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x191d_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x191d_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x191d_E_NOT_OK
 *   RTE_E_DidServices_0x191d_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x191d_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x191d_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x191d_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) VehPwrMd2msCounter_Cnt_T_u16;

	Rte_Read_PowerLatchTimeDID191D_Cnt_u16(&VehPwrMd2msCounter_Cnt_T_u16);

	(*data)[0] = (uint8) VehPwrMd2msCounter_Cnt_T_u16;

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x1921_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1921>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x1921_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x1921_ReadData(Dcm_9Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x1921_E_NOT_OK
 *   RTE_E_DidServices_0x1921_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1921_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x1921_ReadData(P2VAR(Dcm_9Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x1921_ReadData (returns application error)
 *********************************************************************************************************************/
	VAR(UInt16, AUTOMATIC) OpModeSts_Cnt_T_u16;
	VAR(UInt16, AUTOMATIC) CmdIgn_Cnt_T_u16;
	VAR(UInt16, AUTOMATIC) CmdIgnFailSts_Cnt_T_u8;

	(void)Rte_Read_OperationalModeSts_Cnt_u16(&OpModeSts_Cnt_T_u16);
	(void)Rte_Read_CmdIgnSts_Cnt_u16(&CmdIgn_Cnt_T_u16);
	(void)Rte_Read_CmdIgnFailSts_Cnt_u8(&CmdIgnFailSts_Cnt_T_u8);

	switch (OpModeSts_Cnt_T_u16)
	{
		case 0x0002u:	/* Ignition_Off */
			(*data)[0] = 0x01U;
			(*data)[1] = D_DATAFILLER_CNT_U08;
			break;

		case 0x0003u:	/* Ignition_Acc */
			(*data)[0] = 0x02U;
			(*data)[1] = D_DATAFILLER_CNT_U08;
			break;

		case 0x0004u:	/* Ignition_On */
			(*data)[0] = 0x04U;
			(*data)[1] = D_DATAFILLER_CNT_U08;
			break;

		case 0x0005u:	/* Ignition_Pre_Start  */
			(*data)[0] = 0x08U;
			(*data)[1] = D_DATAFILLER_CNT_U08;
			break;

		case 0x0006u:	/* Ignition_Start  */
			(*data)[0] = 0x10U;
			(*data)[1] = D_DATAFILLER_CNT_U08;
			break;

		case 0x0007u:	/* Ignition_Cranking */
			(*data)[0] = 0x20U;
			(*data)[1] = D_DATAFILLER_CNT_U08;
			break;

		case 0x0008u:	/* Ignition_On_EngOn  */
			(*data)[0] = 0x40U;
			(*data)[1] = D_DATAFILLER_CNT_U08;
			break;

		case 0x0009u:	/* Ignition_Pre_Acc  */
			(*data)[0] = D_DATAFILLER_CNT_U08;
			(*data)[1] = 0x01U;
			break;

		case 0x000Au:	/* Ignition_Pre_Off  */
			(*data)[0] = 0x80U;
			(*data)[1] = D_DATAFILLER_CNT_U08;
			break;

		case 0x000Fu:	/* SNA  */
			(*data)[0] = D_DATAFILLER_CNT_U08;
			(*data)[1] = 0x80U;
			break;

		default:
			(*data)[0] = D_DATAFILLER_CNT_U08;
			(*data)[1] = D_DATAFILLER_CNT_U08;
			break;
	}

	(*data)[2] = D_DATAFILLER_CNT_U08;	/* Relay Activation #1 */
	(*data)[3] = D_DATAFILLER_CNT_U08;	/* Relay Activation #2 */
	(*data)[4] = D_DATAFILLER_CNT_U08;	/* Relay Failure #1 */
	(*data)[5] = D_DATAFILLER_CNT_U08;	/* Key Selector Switch #1 */
	(*data)[6] = D_DATAFILLER_CNT_U08;	/* Key Selector Switch #2 */

	switch( CmdIgn_Cnt_T_u16 )
	{
		case 0x0001u:	/* IGN_LK */
			(*data)[7] = 0x01U;
			break;

		case 0x0003u:	/* ACC  */
			(*data)[7] = 0x02U;
			break;

		case 0x0004u:	/* RUN  */
			(*data)[7] = 0x04U;
			break;

		case 0x0005u:	/* START  */
			(*data)[7] = 0x08U;
			break;

		default:
			(*data)[7] = D_DATAFILLER_CNT_U08;
			break;
	}

	if( CmdIgnFailSts_Cnt_T_u8 == 0x01U )
	{
		(*data)[8] = 0x01U;
	}
	
	else
	{
		(*data)[8] = D_DATAFILLER_CNT_U08;
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x2001_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x2001_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x2001_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x2001_E_NOT_OK
 *   RTE_E_DidServices_0x2001_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2001_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2001_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x2001_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(uint32, AUTOMATIC) TotalOdometer_Cnt_T_u32;
	VAR(uint16, AUTOMATIC) TotalOdometer_Cnt_T_u16;

	Rte_Read_TotalOdometerIPC_Cnt_u32(&TotalOdometer_Cnt_T_u32);

	TotalOdometer_Cnt_T_u16 = (uint16) (TotalOdometer_Cnt_T_u32 / 16U);

	(*data)[0] = (uint8) (TotalOdometer_Cnt_T_u16 >> 0x08U);
	(*data)[1] = (uint8) (TotalOdometer_Cnt_T_u16 & 0x00FFU);

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x2002_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x2002_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x2002_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x2002_E_NOT_OK
 *   RTE_E_DidServices_0x2002_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2002_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2002_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x2002_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) OdometerFlashProgData_Cnt_T_u16;

	OdometerFlashProgData_Cnt_T_u16 = *Rte_Pim_OdometerFlashProgData();

	(*data)[0] = (uint8) (OdometerFlashProgData_Cnt_T_u16 >> 0x08U);
	(*data)[1] = (uint8) (OdometerFlashProgData_Cnt_T_u16 & 0x00FFU);

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x2003_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x2003_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x2003_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x2003_E_NOT_OK
 *   RTE_E_DidServices_0x2003_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2003_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2003_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x2003_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;
	VAR(uint16, AUTOMATIC) TempValue_T_u16;

	(void)Rte_Call_ProgrammingAttemptCounter_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
        /* Application programming attempt counter */
		TempValue_T_u16 = (uint16) (((*RtePim_ProgrammingAttemptCounterData())[0] << 0x08U) & 0xFF00U);
		TempValue_T_u16 |= (uint16) ((*RtePim_ProgrammingAttemptCounterData())[1] & 0x00FFU);
		TempValue_T_u16 = ~TempValue_T_u16;

		(*data)[0] = (uint8)(TempValue_T_u16 >> 8U);
		(*data)[1] = (uint8)(TempValue_T_u16);
		(*data)[2] = 0xFFU;
		(*data)[3] = 0xFFU;

		/* Calibration programming attempt counter */
		TempValue_T_u16 = (uint16) (((*RtePim_ProgrammingAttemptCounterData())[2] << 0x08U) & 0xFF00U);
		TempValue_T_u16 |= (uint16) ((*RtePim_ProgrammingAttemptCounterData())[3] & 0x00FFU);
		TempValue_T_u16 = ~TempValue_T_u16;

		(*data)[4] = (uint8)(TempValue_T_u16 >> 8U);
		(*data)[5] = (uint8)(TempValue_T_u16);
		(*data)[6] = 0xFFU;
		(*data)[7] = 0xFFU;
	}

	else
	{
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = 0xFFU;
		}
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x2008_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x2008_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x2008_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x2008_E_NOT_OK
 *   RTE_E_DidServices_0x2008_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2008_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2008_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x2008_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) i;
	VAR(uint32, AUTOMATIC) ECULifeTimeMins_T_u32;

	ECULifeTimeMins_T_u32 = DiagSvc_ECULifeTimeMinsInitial_Cnt_M_u32;

	(*data)[0] = (UInt8) ( (ECULifeTimeMins_T_u32 & 0x00FF0000U) >> 16U );
	(*data)[1] = (UInt8) ( (ECULifeTimeMins_T_u32 & 0x0000FF00U) >> 8U );
	(*data)[2] = (UInt8) ( (ECULifeTimeMins_T_u32 & 0x000000FFU) );

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x200a_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x200a>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x200a_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x200a_ReadData(Dcm_3Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x200a_E_NOT_OK
 *   RTE_E_DidServices_0x200a_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200a_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200a_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x200a_ReadData (returns application error)
 *********************************************************************************************************************/

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;

	(*data)[0] = MSB(Nvm_IgnCntr_Cnt_u16);
	(*data)[1] = LSB(Nvm_IgnCntr_Cnt_u16);
	(*data)[2] = D_DATAFILLER_CNT_U08;

	return RTE_E_OK;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x200b_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x200b_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x200b_ReadData(Dcm_3Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x200b_E_NOT_OK
 *   RTE_E_DidServices_0x200b_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200b_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200b_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x200b_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;

	VAR(uint16, AUTOMATIC) i;

	VAR(uint32,  AUTOMATIC) ElapsedTime_mS_T_u32;
	VAR(uint32,  AUTOMATIC) ElapsedTime_min_T_u32;
	VAR(uint32, AUTOMATIC) FirstDTCDetectMins_T_u32;

	(void)Rte_Call_FirstDTCDetectMins_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		FirstDTCDetectMins_T_u32 = *Rte_Pim_FirstDTCDetectMinsData();

		if( FirstDTCDetectMins_T_u32 == 0xFFFFFFFFU)
		{
			FirstDTCDetectMins_T_u32 = 0x00000000U;
		}

		else
		{
			(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(DiagSvc_Timer_mS_M_u32, &ElapsedTime_mS_T_u32);
			ElapsedTime_min_T_u32 = ElapsedTime_mS_T_u32 / (1000u * 60u); /* converting ms to min */
			ElapsedTime_min_T_u32 += DiagSvc_ECULifeTimeMinsInitial_Cnt_M_u32;

			FirstDTCDetectMins_T_u32 = (uint32) (ElapsedTime_min_T_u32 - *Rte_Pim_FirstDTCDetectMinsData());
		}

		(*data)[0] = (UInt8) ( (FirstDTCDetectMins_T_u32 & 0x00FF0000U) >> 16U );
		(*data)[1] = (UInt8) ( (FirstDTCDetectMins_T_u32 & 0x0000FF00U) >> 8U );
		(*data)[2] = (UInt8) ( (FirstDTCDetectMins_T_u32 & 0x000000FFU) );
	}

	else
	{
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_DATAFILLER_CNT_U08;
		}
	}


	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x200c_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x200c_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x200c_ReadData(Dcm_2Byte_Type)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x200c_E_NOT_OK
 *   RTE_E_DidServices_0x200c_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200c_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x200c_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x200c_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) FirstDTCDetectSecs_T_u16;
	VAR(uint16, AUTOMATIC) i;
	VAR(uint32, AUTOMATIC) FirstDTCDetectMins_T_u32;

	(void)Rte_Call_FirstDTCDetectSecs_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		FirstDTCDetectMins_T_u32 = *Rte_Pim_FirstDTCDetectMinsData();

		if( FirstDTCDetectMins_T_u32 == 0xFFFFFFFFU)
		{
			FirstDTCDetectSecs_T_u16 = 0x0000U;
		}

		else
		{
			FirstDTCDetectSecs_T_u16 = *Rte_Pim_FirstDTCDetectSecsData();
		}

		(*data)[0] = (UInt8) ( (FirstDTCDetectSecs_T_u16 & 0xFF00U) >> 8U );
		(*data)[1] = (UInt8) (FirstDTCDetectSecs_T_u16 & 0x00FFU);
	}

	else
	{
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_DATAFILLER_CNT_U08;
		}
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x2010_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x2010_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x2010_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x2010_E_NOT_OK
 *   RTE_E_DidServices_0x2010_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2010_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2010_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x2010_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;

	(void)Rte_Call_ProgrammingStatus_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = (*RtePim_ProgrammingStatusData())[i];
		}
	}
	else
	{
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_DATAFILLER_CNT_U08;
		}
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x2014_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x2014_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x2014_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x2014_E_NOT_OK
 *   RTE_E_DidServices_0x2014_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2014_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2014_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x2014_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;

	(void)Rte_Call_EraseRoutineStatus_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		*(data)[0] = (*RtePim_EraseRoutineStatusData())[0];
	}
	else
	{
		(*data)[0] = D_DATAFILLER_CNT_U08;
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x2023_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x2023_WriteData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x2023_WriteData(Dcm_255Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x1006_E_NOT_OK
 *   RTE_E_DidServices_0x1006_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2023_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2023_WriteData(P2VAR(Dcm_255Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x2023_WriteData (returns application error)
*********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) CRCCalculatedHex_T_u16;
	VAR(uint16, AUTOMATIC) Index_T_u16;
	VAR(uint16, AUTOMATIC) TuningSet_Cnt_T_u16;

	VAR(uint8, AUTOMATIC) CarConfiguration1_StopAndStart_T_u08;
	VAR(uint8, AUTOMATIC) CarConfiguration1_FrontFogLight_T_u08;
	VAR(uint8, AUTOMATIC) CarConfiguration1_FrontFogLightStrategy_T_u08;
	VAR(uint8, AUTOMATIC) InfoConfiguration3_PowerDoorLock_T_u08;
	VAR(uint8, AUTOMATIC) CarConfiguration6_Battery_Type_T_u08;
	VAR(uint8, AUTOMATIC) CarConfiguration12_AlarmSystem_T_u08;
	VAR(uint8, AUTOMATIC) CarConfiguration12_RemoteControlKey_T_u08;
	VAR(uint8, AUTOMATIC) CarConfiguration12_Siren_T_u08;
	VAR(uint8, AUTOMATIC) CarConfiguration12_UltrasonicSensor_T_u08;
	VAR(uint8, AUTOMATIC) CarConfiguration12_AntinclinationSensor_T_u08;
	VAR(uint8, AUTOMATIC) CarConfiguration15_VehicleLineConfig_T_u08;
	VAR(uint8, AUTOMATIC) CRCCalculated_T_u08[PROXIMSG_CRC_LENGTH];
	VAR(uint8, AUTOMATIC) CRCProxiMsg_T_u08[PROXIMSG_CRC_LENGTH];
	VAR(uint8, AUTOMATIC) EngineType_T_u08;
	VAR(uint8, AUTOMATIC) DiagSvc_HextoASCIILookup_Cnt_T_u08[10] = { 0x30u, 0x31u, 0x32u, 0x33u, 0x34u, 0x35u, 0x36u, 0x37u, 0x38u, 0x39u };
	VAR(uint8, AUTOMATIC) i;
	VAR(uint8, AUTOMATIC) Index_T_u08;
	VAR(uint8, AUTOMATIC) MaskIndex_T_u08;
	VAR(uint8, AUTOMATIC) Result_T_u08;
	VAR(uint8, AUTOMATIC) SuspensionConfig_T_u08;
	VAR(uint8, AUTOMATIC) VehicleConfig_T_u08;
	
	

	/* Read Proxi Msg's for Coherence check */
	CarConfiguration1_StopAndStart_T_u08 = (uint8) (((*data)[PROXIMSG_CAR_CONFIGURATION_1]) & 0x01U);
	CarConfiguration1_FrontFogLight_T_u08 = (uint8) ( (((*data)[PROXIMSG_CAR_CONFIGURATION_1]) & 0x10U) >> 0x04U );
	CarConfiguration1_FrontFogLightStrategy_T_u08 = (uint8) ( (((*data)[PROXIMSG_CAR_CONFIGURATION_1]) & 0x20U) >> 0x05U );
	InfoConfiguration3_PowerDoorLock_T_u08 = (uint8) (((*data)[PROXIMSG_INFO_CONFIGURATION_3]) & 0x01U);
	CarConfiguration6_Battery_Type_T_u08 = (uint8) (((*data)[PROXIMSG_CAR_CONFIGURATION_6]) & 0x0FU);
	CarConfiguration12_AlarmSystem_T_u08 = (uint8) (((*data)[PROXIMSG_CAR_CONFIGURATION_12]) & 0x01U);
	CarConfiguration12_RemoteControlKey_T_u08 = (uint8) ( (((*data)[PROXIMSG_CAR_CONFIGURATION_12]) & 0x02U) >> 0x01U );
	CarConfiguration12_Siren_T_u08 = (uint8) ( (((*data)[PROXIMSG_CAR_CONFIGURATION_12] & 0x0CU)) >> 0x02U );
	CarConfiguration12_UltrasonicSensor_T_u08 = (uint8) ( (((*data)[PROXIMSG_CAR_CONFIGURATION_12]) & 0x10U) >> 0x04U );
	CarConfiguration12_AntinclinationSensor_T_u08 = (uint8) ( (((*data)[PROXIMSG_CAR_CONFIGURATION_12]) & 0x20U) >> 0x05U );
	CarConfiguration15_VehicleLineConfig_T_u08 	 = (uint8) ((*data)[PROXIMSG_CAR_CONFIGURATION_15]);

	*ErrorCode = RTE_E_OK;

	/* Initialize PROXI Error Status with 0x00's */
	DiagSvc_ProxiErrorCount_Cnt_M_u08 = 0x00U;
	for(i=0u; i < sizeof(DiagSvc_ProxiErrorStatus_Cnt_M_u08); i++)
	{
		DiagSvc_ProxiErrorStatus_Cnt_M_u08[i] = D_DATAFILLER_CNT_U08;
	}

	/* Check CONFIGURATION CODE field */
	/* Only ASCII character strings (from 30 to 39 hex) are accepted in the CONFIGURATION CODE field */
	for(i=0u; i < PROXIMSG_CONFIGCODE_LENGTH; i++)
	{
		if( (((*data)[i]) < 0x30U) || (((*data)[i]) > 0x39U) )
		{
			*ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;

			if( (*data)[i] < 0x30U)
			{
				MaskIndex_T_u08 = (*data)[i] ^ 0x30U;
			}
			else
			{
				MaskIndex_T_u08 = (*data)[i] ^ 0x39U;
			}

			UpdateProxiErrorStatus(*ErrorCode, i , MaskIndex_T_u08);
		}
	}

	/* Check Production Month of PROXI Msg */
	if ( (*data)[PROXIMSG_PRODCUTION_MONTH] > 0x12U )
	{
		*ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
		MaskIndex_T_u08 = (*data)[PROXIMSG_PRODCUTION_MONTH] ^ 12U;
		UpdateProxiErrorStatus(*ErrorCode, PROXIMSG_PRODCUTION_MONTH , MaskIndex_T_u08);
	}

	/* Check Production Date of PROXI Msg*/
	if ( (*data)[PROXIMSG_PRODCUTION_DATA] > 0x31U )
	{
		*ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
		MaskIndex_T_u08 = (*data)[PROXIMSG_PRODCUTION_DATA] ^ 0x1FU;
		UpdateProxiErrorStatus(*ErrorCode, PROXIMSG_PRODCUTION_DATA , MaskIndex_T_u08);
	}

	/* Calculate CRC of the received data */
	CRCCalculatedHex_T_u16 = PROXICRC_CCIT16(&(*data)[25U], (dataLength - 25U));

	/* Hexadecimal to Decimal conversion */
	/* The converted decimal is stored in ASCII format in the form of array */
	for(i=0u; i < PROXIMSG_CRC_LENGTH; i++)
	{
		CRCProxiMsg_T_u08[i] = (*data)[6U + i];
		Result_T_u08 = (uint8)fmod((float64)CRCCalculatedHex_T_u16, (float64)(10.0f));
		CRCCalculated_T_u08[(PROXIMSG_CRC_LENGTH - 1u) - i] = (uint8) DiagSvc_HextoASCIILookup_Cnt_T_u08[Result_T_u08];
		CRCCalculatedHex_T_u16 = CRCCalculatedHex_T_u16 / 10U;
	}

	/* Check the calculated CRC with PROXI Msg CRC */
	for(i=0u; i < PROXIMSG_CRC_LENGTH; i++)
	{
		if(CRCCalculated_T_u08[i] != CRCProxiMsg_T_u08[i])
		{
			*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
			MaskIndex_T_u08 = CRCCalculated_T_u08[i] ^ CRCProxiMsg_T_u08[i];
			UpdateProxiErrorStatus(*ErrorCode, (6U+i) , MaskIndex_T_u08);
		}
	}

	/* Coherence check */
	if( (CarConfiguration1_StopAndStart_T_u08 == 0x01U) && (CarConfiguration6_Battery_Type_T_u08 != 0x04U) )
	{
		*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		MaskIndex_T_u08 = 0x01U;
		UpdateProxiErrorStatus(*ErrorCode, PROXIMSG_CAR_CONFIGURATION_1 , MaskIndex_T_u08);
		MaskIndex_T_u08 = CarConfiguration6_Battery_Type_T_u08 ^ 0x04U;
		UpdateProxiErrorStatus(*ErrorCode, PROXIMSG_CAR_CONFIGURATION_6 , MaskIndex_T_u08);
	}

	if ( (CarConfiguration1_FrontFogLightStrategy_T_u08 == 0x01U) && (CarConfiguration1_FrontFogLight_T_u08 == 0x00U) )
	{
		*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		MaskIndex_T_u08 = 0x30U;
		UpdateProxiErrorStatus(*ErrorCode, PROXIMSG_CAR_CONFIGURATION_1 , MaskIndex_T_u08);
	}

	if( (CarConfiguration12_RemoteControlKey_T_u08 == 0x01U) && (InfoConfiguration3_PowerDoorLock_T_u08 == 0x00U) )
	{
		*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		MaskIndex_T_u08 = 0x02U;
		UpdateProxiErrorStatus(*ErrorCode, PROXIMSG_CAR_CONFIGURATION_12 , MaskIndex_T_u08);
		MaskIndex_T_u08 = 0x01U;
		UpdateProxiErrorStatus(*ErrorCode, PROXIMSG_INFO_CONFIGURATION_3 , MaskIndex_T_u08);
	}

	if( (CarConfiguration12_AlarmSystem_T_u08 == 0x00U) && (CarConfiguration12_Siren_T_u08 == 0x02U) )
	{
		*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		MaskIndex_T_u08 = 0x01U;
		UpdateProxiErrorStatus(*ErrorCode, PROXIMSG_CAR_CONFIGURATION_12 , MaskIndex_T_u08);
	}

	if( (CarConfiguration12_AlarmSystem_T_u08 == 0x00U) && (CarConfiguration12_UltrasonicSensor_T_u08 == 0x01U) )
	{
		*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		MaskIndex_T_u08 = 0x11U;
		UpdateProxiErrorStatus(*ErrorCode, PROXIMSG_CAR_CONFIGURATION_12 , MaskIndex_T_u08);
	}

	if( (CarConfiguration12_AlarmSystem_T_u08 == 0x00U) && (CarConfiguration12_AntinclinationSensor_T_u08 == 0x01U) )
	{
		*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		MaskIndex_T_u08 = 0x21U;
		UpdateProxiErrorStatus(*ErrorCode, PROXIMSG_CAR_CONFIGURATION_12 , MaskIndex_T_u08);
	}

	if( CarConfiguration15_VehicleLineConfig_T_u08 != 0x34U )
	{
		if( CarConfiguration15_VehicleLineConfig_T_u08 != 0x5CU )
		{
			*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
			MaskIndex_T_u08 = 0xFFU;
			UpdateProxiErrorStatus(*ErrorCode, PROXIMSG_CAR_CONFIGURATION_15 , MaskIndex_T_u08);
		}

		else
		{
			/* Do Nothing */
		}
	}

	if( *ErrorCode != RTE_E_OK )
	{
		/* PROXI Msg rejected */
		/* Reject reasons are filled in ErrorCode */
		for(i=0u; i < sizeof(DiagSvc_ProxiErrorStatus_Cnt_M_u08); i++)
		{
			(*RtePim_EOLConfigurationData())[i] = DiagSvc_ProxiErrorStatus_Cnt_M_u08[i];
		}
		(void)Rte_Call_EOLConfiguration_WriteBlock(NULL_PTR);
	}

	else
	{
		/* PROXI Msg accepted */
		VehicleConfig_T_u08 = (uint8) ((*data)[PROXIMSG_VEHICLE_CONFIG]);	/* Read Vehicle configuration Type */
		EngineType_T_u08 = (uint8) (((*data)[PROXIMSG_ENGINE_TYPE] & 0xF0U) >> 0x04U );	/* Read Engine Type */
		SuspensionConfig_T_u08 = (uint8) (((*data)[PROXIMSG_SUSPENSION_CONFIG] & 0xE0U) >> 0x05U);	/* Read Suspension configuration Type */

		if ( VehicleConfig_T_u08 == k_ProxiConfigTunSet_Cnt_u08[0][0])
		{
			TuningSet_Cnt_T_u16 = 0x0000U; /* Default Tuning Set */
			for (i =0u; i <= 3U; i++)
			{
				if( (EngineType_T_u08 == k_ProxiConfigTunSet_Cnt_u08[i][1]) && (SuspensionConfig_T_u08 == k_ProxiConfigTunSet_Cnt_u08[i][2]) )
				{
					TuningSet_Cnt_T_u16 = i;
				}
			}
			/* Write Tuning data */
			*Rte_Pim_TuningSetSelectData() = TuningSet_Cnt_T_u16;
			(void)Rte_Call_TuningSetSelect_WriteBlock(NULL_PTR);
		}

		else if ( VehicleConfig_T_u08 == k_ProxiConfigTunSet_Cnt_u08[4][0])
		{
			TuningSet_Cnt_T_u16 = 0x0004U; /* Default Tuning Set */
			for (i =4u; i <= 7U; i++)
			{
				if( (EngineType_T_u08 == k_ProxiConfigTunSet_Cnt_u08[i][1]) && (SuspensionConfig_T_u08 == k_ProxiConfigTunSet_Cnt_u08[i][2]) )
				{
					TuningSet_Cnt_T_u16 = i;
				}
			}
			/* Write Tuning data */
			*Rte_Pim_TuningSetSelectData() = TuningSet_Cnt_T_u16;
			(void)Rte_Call_TuningSetSelect_WriteBlock(NULL_PTR);
		}

		else
		{
			*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
			/* Do not change Tuning Set */
		}

		/* Write PROXI Data */
		for( Index_T_u16 = 0U; Index_T_u16 < dataLength; Index_T_u16++ )
		{
			(*Rte_Pim_ProxiConfigurationData())[Index_T_u16] = ((*data)[Index_T_u16]);

			if(Index_T_u16 < PROXIMSG_CONFIGCODE_LENGTH)
			{
				DiagSvc_ProxiCheckData_Cnt_u08[Index_T_u16] = ((*data)[Index_T_u16]);
			}
		}

		for( Index_T_u16 = dataLength; Index_T_u16 < TableSize_m(*data); Index_T_u16++ )
		{
			(*Rte_Pim_ProxiConfigurationData())[Index_T_u16] = D_ASCIIFILLER_CNT_U08;
		}

		/* Clear the EOL Proxi data */
		for(i=0u; i < sizeof(DiagSvc_ProxiErrorStatus_Cnt_M_u08); i++)
		{
			(*RtePim_EOLConfigurationData())[i] = D_DATAFILLER_CNT_U08;
		}

		/* Write Proxi Counter Data */
		(*RtePim_ProxiCounterData())[0] = (*RtePim_ProxiCounterData())[0] + 0x01U;

		(void)Rte_Call_ProxiConfiguration_WriteBlock(NULL_PTR);
		(void)Rte_Call_EOLConfiguration_WriteBlock(NULL_PTR);
		(void)Rte_Call_ProxiCounter_WriteBlock(NULL_PTR);
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x2024_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x2024_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x2024_ReadData(Dcm_6Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x2024_E_NOT_OK
 *   RTE_E_DidServices_0x2024_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2024_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x2024_ReadData(P2VAR(Dcm_6Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x2024_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) i;

	VAR(uint8, AUTOMATIC) SteeringRackPinionType_T_u08;
	VAR(uint8, AUTOMATIC) DSTPresence_T_u08;
	VAR(uint8, AUTOMATIC) CANNode30HALF_T_u08;
	VAR(uint8, AUTOMATIC) EngineType_T_u08;
	VAR(uint8, AUTOMATIC) IgnitionPreStartLogic_T_u08;
	VAR(uint8, AUTOMATIC) SemiAutomaticParkingSystem_T_u08;
	VAR(uint8, AUTOMATIC) StopStartType_T_u08;
	VAR(uint8, AUTOMATIC) StopStartPresence_T_u08;
	VAR(uint8, AUTOMATIC) DriveStyleSelector_T_u08;
	VAR(uint8, AUTOMATIC) CANNodeDTCM_T_u08;
	VAR(uint8, AUTOMATIC) VehicleLineConfiguration_T_u08;
	VAR(uint8, AUTOMATIC) GearBoxType_T_u08;
	VAR(uint8, AUTOMATIC) TerrainSelectorModes_T_u08;

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;

	(void)Rte_Call_ProxiConfiguration_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = D_DATAFILLER_CNT_U08;
	}

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		SteeringRackPinionType_T_u08 = ((*Rte_Pim_ProxiConfigurationData())[87] & 0x03U);
		DSTPresence_T_u08 = ( ((*Rte_Pim_ProxiConfigurationData())[87] & 0x80U) >> 0x07U );
		CANNode30HALF_T_u08 = ( ((*Rte_Pim_ProxiConfigurationData())[28] & 0x40U) >> 0x06U);
		EngineType_T_u08 = ( ((*Rte_Pim_ProxiConfigurationData())[65] & 0xF0U) >> 0x04U);

		(*data)[0] = (uint8) ( (EngineType_T_u08) << 0x04U );
		(*data)[0] |= (uint8) ( (CANNode30HALF_T_u08) << 0x03U );
		(*data)[0] |= (uint8) ( (DSTPresence_T_u08) << 0x02U );
		(*data)[0] |= (uint8) ( SteeringRackPinionType_T_u08) ;


		IgnitionPreStartLogic_T_u08 = ( ((*Rte_Pim_ProxiConfigurationData())[93] & 0x80U) >> 0x07U);
		SemiAutomaticParkingSystem_T_u08 = ( ((*Rte_Pim_ProxiConfigurationData())[93] & 0x08U) >> 0x03U);
		StopStartType_T_u08 = ((*Rte_Pim_ProxiConfigurationData())[133] & 0x03U);
		StopStartPresence_T_u08 = ((*Rte_Pim_ProxiConfigurationData())[57] & 0x01U);
		DriveStyleSelector_T_u08 = ( ((*Rte_Pim_ProxiConfigurationData())[87] & 0x60U) >> 0x05U);
		CANNodeDTCM_T_u08 = ( ((*Rte_Pim_ProxiConfigurationData())[33] & 0x08U) >> 0x03U);

		(*data)[1] |= (uint8) ( (CANNodeDTCM_T_u08) << 0x07U );
		(*data)[1] |= (uint8) ( (DriveStyleSelector_T_u08) << 0x05U );
		(*data)[1] |= (uint8) ( (StopStartPresence_T_u08) << 0x04U );
		(*data)[1] |= (uint8) ( (StopStartType_T_u08) << 0x02U );
		(*data)[1] |= (uint8) ( (SemiAutomaticParkingSystem_T_u08) << 0x01U );
		(*data)[1] |= (uint8) ( IgnitionPreStartLogic_T_u08);

		VehicleLineConfiguration_T_u08 = ((*Rte_Pim_ProxiConfigurationData())[104]);
		(*data)[2] = (uint8) VehicleLineConfiguration_T_u08;

		GearBoxType_T_u08 = ((*Rte_Pim_ProxiConfigurationData())[100] & 0x07U);
		TerrainSelectorModes_T_u08 = ( ((*Rte_Pim_ProxiConfigurationData())[100] & 0x70U) >> 0x04U);
		(*data)[5] |= (uint8) ( (TerrainSelectorModes_T_u08) << 0x03U );
		(*data)[5] |= (uint8) GearBoxType_T_u08;
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x292e_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x292e_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x292e_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x292e_E_NOT_OK
 *   RTE_E_DidServices_0x292e_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x292e_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x292e_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x292e_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;

	(void)Rte_Call_ProxiCounter_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		(*data)[0] = (*RtePim_ProxiCounterData())[0];
	}
	else
	{
		(*data)[0] = D_DATAFILLER_CNT_U08;
	}

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x5051_ResetToDefault
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x5051_ResetToDefault>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x5051_ResetToDefault(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x5051_ResetToDefault(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x5051_E_NOT_OK
 *   RTE_E_DidServices_0x5051_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ResetToDefault(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ResetToDefault(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x5051_ResetToDefault (returns application error)
*********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(uint8,  AUTOMATIC) data_Cnt_T_u08[4] = { 0x00U, 0x00U, 0x00U, 0x00U };

	VAR(Dcm_SesCtrlType, AUTOMATIC) Session_Cnt_T_enum;

	(void)Dcm_GetSesCtrlType(&Session_Cnt_T_enum);

	if(DCM_DEFAULT_SESSION == Session_Cnt_T_enum)
	{
		*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
	}

	else
	{
		DiagSvc_IOCtrl5051Enable_Cnt_M_lgc = TRUE;
		ResetIOCtrlTimer(&DiagSvc_IOCtrlTimer1_mS_M_u32);
		(void)EPSInternal_PID_FD02 (0x2Eu, &data_Cnt_T_u08[0], 0x4U, &RespLen_Cnt_T_u16);
	}

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x5051_ReturnControlToECU
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x5051_ReturnControlToECU>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x5051_ReturnControlToECU(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x5051_ReturnControlToECU(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x5051_E_NOT_OK
 *   RTE_E_DidServices_0x5051_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x5051_ReturnControlToECU (returns application error)
*********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(uint8,  AUTOMATIC) data_Cnt_T_u08[4] = { 0x00U, 0x00U, 0x00U, 0x00U };

	VAR(Dcm_SesCtrlType, AUTOMATIC) Session_Cnt_T_enum;

	(void)Dcm_GetSesCtrlType(&Session_Cnt_T_enum);

	if(DCM_DEFAULT_SESSION == Session_Cnt_T_enum)
	{
		*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
	}

	else
	{
		(void)EPSInternal_PID_FD02 (0x2Eu, &data_Cnt_T_u08[0], 0x4U, &RespLen_Cnt_T_u16);
	}

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x5051_ShortTermAdjustment
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x5051_ShortTermAdjustment>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x5051_ShortTermAdjustment(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x5051_ShortTermAdjustment(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x5051_E_NOT_OK
 *   RTE_E_DidServices_0x5051_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5051_ShortTermAdjustment(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x5051_ShortTermAdjustment (returns application error)
*********************************************************************************************************************/
{

	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(uint8,  AUTOMATIC) data_Cnt_T_u08[4] = { 0x00U, 0x00U, 0x00U, 0x01U };

	VAR(Dcm_SesCtrlType, AUTOMATIC) Session_Cnt_T_enum;

	(void)Dcm_GetSesCtrlType(&Session_Cnt_T_enum);

	if(DCM_DEFAULT_SESSION == Session_Cnt_T_enum)
	{
		*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
	}

	else
	{
		DiagSvc_IOCtrl5051Enable_Cnt_M_lgc = TRUE;
		ResetIOCtrlTimer(&DiagSvc_IOCtrlTimer1_mS_M_u32);
		(void)EPSInternal_PID_FD02 (0x2Eu, &data_Cnt_T_u08[0], 0x4U, &RespLen_Cnt_T_u16);
	}

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x5052_ReturnControlToECU
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x5052_ReturnControlToECU>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x5052_ReturnControlToECU(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x5052_ReturnControlToECU(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x5052_E_NOT_OK
 *   RTE_E_DidServices_0x5052_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5052_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5052_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x5052_ReturnControlToECU (returns application error)
*********************************************************************************************************************/

	VAR(Dcm_SesCtrlType, AUTOMATIC) Session_Cnt_T_enum;

	(void)Dcm_GetSesCtrlType(&Session_Cnt_T_enum);

	if(DCM_DEFAULT_SESSION == Session_Cnt_T_enum)
	{
		*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
	}

	else
	{
		StaMd_SCom_EcuReset();
	}

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x5052_ShortTermAdjustment
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x5052_ShortTermAdjustment>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x5052_ShortTermAdjustment(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x5052_ShortTermAdjustment(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x5052_E_NOT_OK
 *   RTE_E_DidServices_0x5052_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5052_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5052_ShortTermAdjustment(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
/**************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x5052_ShortTermAdjustment (returns application error)
*********************************************************************************************************************/
{
	VAR(uint16,  AUTOMATIC) i;

	VAR(Dcm_SesCtrlType, AUTOMATIC) Session_Cnt_T_enum;

	(void)Dcm_GetSesCtrlType(&Session_Cnt_T_enum);

	if(DCM_DEFAULT_SESSION == Session_Cnt_T_enum)
	{
		*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
	}

	else
	{
		for(i=0U; i< 255U; i++)
		{
			(*Rte_Pim_ProxiConfigurationData())[i] = D_DATAFILLER_CNT_U08;
		}
	}

	return RTE_E_OK;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x5aab_ResetToDefault
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x5aab_ResetToDefault>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x5aab_ResetToDefault(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x5aab_ResetToDefault(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x5052_E_NOT_OK
 *   RTE_E_DidServices_0x5052_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ResetToDefault(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ResetToDefault(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x5aab_ResetToDefault (returns application error)
*********************************************************************************************************************/

	VAR(Dcm_SesCtrlType, AUTOMATIC) Session_Cnt_T_enum;
	VAR(CityUserEnableDisable,  AUTOMATIC) CityUserEnableDisable_Cnt_T_enum;

	(void)Dcm_GetSesCtrlType(&Session_Cnt_T_enum);

	if(DCM_DEFAULT_SESSION == Session_Cnt_T_enum)
	{
		*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
	}

	else
	{
		DiagSvc_IOCtrl5aabEnable_Cnt_M_lgc = TRUE;
		ResetIOCtrlTimer(&DiagSvc_IOCtrlTimer2_mS_M_u32);
		CityUserEnableDisable_Cnt_T_enum = ResetToDefault;
		Rte_Write_CityUserEnableDisable_Cnt_enum(CityUserEnableDisable_Cnt_T_enum);
	}

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x5aab_ReturnControlToECU
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x5aab_ResetToDefault>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x5aab_ReturnControlToECU(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x5aab_ReturnControlToECU(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x5052_E_NOT_OK
 *   RTE_E_DidServices_0x5052_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x5aab_ReturnControlToECU (returns application error)
*********************************************************************************************************************/

	VAR(Dcm_SesCtrlType, AUTOMATIC) Session_Cnt_T_enum;
	VAR(CityUserEnableDisable,  AUTOMATIC) CityUserEnableDisable_Cnt_T_enum;

	(void)Dcm_GetSesCtrlType(&Session_Cnt_T_enum);

	if(DCM_DEFAULT_SESSION == Session_Cnt_T_enum)
	{
		*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
	}

	else
	{
		CityUserEnableDisable_Cnt_T_enum = ReturnControlToECU;
		Rte_Write_CityUserEnableDisable_Cnt_enum(CityUserEnableDisable_Cnt_T_enum);
	}

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x5aab_ShortTermAdjustment
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x5aab_ShortTermAdjustment>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x5aab_ShortTermAdjustment(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x5aab_ShortTermAdjustment(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x5052_E_NOT_OK
 *   RTE_E_DidServices_0x5052_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x5aab_ShortTermAdjustment(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0x5aab_ShortTermAdjustment (returns application error)
*********************************************************************************************************************/

	VAR(Dcm_SesCtrlType, AUTOMATIC) Session_Cnt_T_enum;
	VAR(CityUserEnableDisable,  AUTOMATIC) CityUserEnableDisable_Cnt_T_enum;

	(void)Dcm_GetSesCtrlType(&Session_Cnt_T_enum);

	if(DCM_DEFAULT_SESSION == Session_Cnt_T_enum)
	{
		*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
	}

	else
	{
		if( (*RequestData)[0] == 0x00U )
		{
			DiagSvc_IOCtrl5aabEnable_Cnt_M_lgc = TRUE;
			ResetIOCtrlTimer(&DiagSvc_IOCtrlTimer2_mS_M_u32);
			CityUserEnableDisable_Cnt_T_enum = ResetToDefault;
			Rte_Write_CityUserEnableDisable_Cnt_enum(CityUserEnableDisable_Cnt_T_enum);
		}

		else if( (*RequestData)[0] == 0xFFU )
		{
			DiagSvc_IOCtrl5aabEnable_Cnt_M_lgc = TRUE;
			ResetIOCtrlTimer(&DiagSvc_IOCtrlTimer2_mS_M_u32);
			CityUserEnableDisable_Cnt_T_enum = ShortTermAdjustment;
			Rte_Write_CityUserEnableDisable_Cnt_enum(CityUserEnableDisable_Cnt_T_enum);
		}

		else
		{
			*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		}
	}

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf100_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf100>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf100_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf100_ReadData(Dcm_7Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf100_E_NOT_OK
 *   RTE_E_DidServices_0xf100_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf100_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf100_ReadData(P2VAR(Dcm_7Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf100_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(uint8, AUTOMATIC) i;

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = k_CustDIDCals_Cnt_u08.DiagnosticIdentification_DIDF100_ASCII_u08[i];
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf10b_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf10b_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf10b_ReadData(Dcm_4092Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf10b_E_NOT_OK
 *   RTE_E_DidServices_0xf10b_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf10b_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf10b_ReadData(P2VAR(Dcm_4092Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf10b_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(uint8, AUTOMATIC) StopStart_T_u08;
	VAR(uint8, AUTOMATIC) AdvanceDriverProgramKind_T_u08;
	VAR(uint8, AUTOMATIC) EngineType_T_u08;
	VAR(uint8, AUTOMATIC) SteeringRackPinionType_T_u08;
	VAR(uint8, AUTOMATIC) SuspensionConfiguration_T_u08;
	VAR(uint8, AUTOMATIC) IgnitionPreStartLogic_T_u08;
	VAR(uint8, AUTOMATIC) GearBoxType_T_u08;
	VAR(uint8, AUTOMATIC) StopStartType_T_u08;
	VAR(uint8, AUTOMATIC) VehicleLineConfiguration_T_u08;

	VAR(uint16, AUTOMATIC) i;

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;

	(void)Rte_Call_ProxiConfiguration_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = D_DATAFILLER_CNT_U08;
	}

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		StopStart_T_u08 = ((*Rte_Pim_ProxiConfigurationData())[57] & 0x01U);
		AdvanceDriverProgramKind_T_u08 = ( ((*Rte_Pim_ProxiConfigurationData())[62] & 0x70U) >> 0x04U);
		EngineType_T_u08 = ( ((*Rte_Pim_ProxiConfigurationData())[65] & 0xF0U) >> 0x04U);
		(*data)[0] |= (uint8) ( EngineType_T_u08 << 0x04U );
		(*data)[0] |= (uint8) ( AdvanceDriverProgramKind_T_u08 << 0x01U );
		(*data)[0] |= StopStart_T_u08;

		SteeringRackPinionType_T_u08 = ((*Rte_Pim_ProxiConfigurationData())[87] & 0x03U);
		SuspensionConfiguration_T_u08 = (uint8) (((*data)[PROXIMSG_SUSPENSION_CONFIG] & 0xE0U) >> 0x05U);
		IgnitionPreStartLogic_T_u08 = ( ((*Rte_Pim_ProxiConfigurationData())[93] & 0x80U) >> 0x07U);
		(*data)[1] |= (uint8) ( IgnitionPreStartLogic_T_u08 << 0x05U );
		(*data)[1] |= (uint8) ( SuspensionConfiguration_T_u08 << 0x02U );
		(*data)[1] |= SteeringRackPinionType_T_u08 ;

		GearBoxType_T_u08 = ( (*Rte_Pim_ProxiConfigurationData())[100] & 0x03U );
		StopStartType_T_u08 = ((*Rte_Pim_ProxiConfigurationData())[133] & 0x03U);
		(*data)[2] |= (uint8) ( StopStartType_T_u08 << 0x03U );
		(*data)[2] |= GearBoxType_T_u08;

		VehicleLineConfiguration_T_u08 = ((*Rte_Pim_ProxiConfigurationData())[104]);
		(*data)[3] = VehicleLineConfiguration_T_u08;
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf10b_ReadDataLength
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf10b_ReadDataLength(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf10b_ReadDataLength(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf10b_E_NOT_OK
 *   RTE_E_DidServices_0xf10b_E_PENDING
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf10b_ReadDataLength(P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) DidLength)
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf10b_ReadDataLength (returns application error)
*********************************************************************************************************************/

	*DidLength = 0x04U;

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf10d_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf10d_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf10d_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf10d_E_NOT_OK
 *   RTE_E_DidServices_0xf10d_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf10d_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf10d_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf10d_ReadData (returns application error)
*********************************************************************************************************************/

	(*data)[0] = 0x82U;	/* Standard Unified Diagnostic Services */
	(*data)[1] = 0x81U;	/* General Programming Requirements for NVM */
	(*data)[2] = 0x81U;	/* Standard Diagnostic Data UDS */
	(*data)[3] = 0x81U;	/* Standard Diagnostic Requirements on UDS FGA/ CG */

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf154_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf154_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf154_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf154_E_NOT_OK
 *   RTE_E_DidServices_0xf154_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf154_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf154_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf154_ReadData (returns application error)
*********************************************************************************************************************/

	(*data)[0] = D_DATAFILLER_CNT_U08;	/* Hardware Supplier Identification */
	(*data)[1] = 0xD2U;	/* Hardware Supplier Identification */

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf155_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf155_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf155_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf155_E_NOT_OK
 *   RTE_E_DidServices_0xf155_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf155_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf155_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf155_ReadData (returns application error)
*********************************************************************************************************************/

	(*data)[0] = D_DATAFILLER_CNT_U08;	/* Software Supplier Identification */
	(*data)[1] = 0xD2U;	/* Software Supplier Identification */

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf158_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf158_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf158_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf158_E_NOT_OK
 *   RTE_E_DidServices_0xf158_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf158_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf158_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf158_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;

	(void)Rte_Call_ProxiConfiguration_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = D_DATAFILLER_CNT_U08;
	}

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		(*data)[0] = (*Rte_Pim_ProxiConfigurationData())[124];
		(*data)[1] = (*Rte_Pim_ProxiConfigurationData())[104];
		(*data)[2] = ( (*Rte_Pim_ProxiConfigurationData())[67] & 0x1Fu);
		(*data)[3] = (*Rte_Pim_ProxiConfigurationData())[106];
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf180_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf180>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf180_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf180_ReadData(Dcm_14Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf180_E_NOT_OK
 *   RTE_E_DidServices_0xf180_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf180_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf180_ReadData(P2VAR(Dcm_14Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf180_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) i;

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = (&Lnk_BootSwIdentificationDIDF180_Addr)[i];
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf181_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf181>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf181_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf181_ReadData(Dcm_14Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf181_E_NOT_OK
 *   RTE_E_DidServices_0xf181_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf181_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf181_ReadData(P2VAR(Dcm_14Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf181_ReadData (returns application error)
 *********************************************************************************************************************/
	VAR(uint8, AUTOMATIC) i;

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = k_CustDIDCals_Cnt_u08.CalibrationSwIdentification_DIDF181_ASCII_u08[i];
	}

	return RTE_E_OK;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf182_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf182>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf182_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf182_ReadData(Dcm_14Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf182_E_NOT_OK
 *   RTE_E_DidServices_0xf182_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf182_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf182_ReadData(P2VAR(Dcm_14Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf182_ReadData (returns application error)
 *********************************************************************************************************************/
	VAR(uint8, AUTOMATIC) i;

	for( i = 0u; i < TableSize_m(*data) > 0u; i++ )
	{
		(*data)[i] = k_CustDIDCals_Cnt_u08.CalibrationSwIdentification_DIDF182_ASCII_u08[i];
	}

	return RTE_E_OK;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf183_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf183_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf183_ReadData(Dcm_15Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf183_E_NOT_OK
 *   RTE_E_DidServices_0xf183_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf183_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf183_ReadData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf183_ReadData (returns application error)
*********************************************************************************************************************/
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;

	(void)Rte_Call_BootSwFingerPrint_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		(*data)[0] = 0x01U;

		for( i = 1u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = (*RtePim_BootSwFingerPrintData())[i-1U];
		}
	}

	else
	{
		(*data)[0] = 0x01U;
		(*data)[1] = 0x00U;
		for( i = 2u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_ASCIIFILLER_CNT_U08;
		}
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf183_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf183_WriteData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf183_WriteData(Dcm_15Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf183_E_NOT_OK
 *   RTE_E_DidServices_0xf183_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf183_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf183_WriteData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf183_WriteData (returns application error)
*********************************************************************************************************************/

	*ErrorCode = DCM_E_SERVICENOTSUPPORTED;
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf184_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf184_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf184_ReadData(Dcm_15Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf184_E_NOT_OK
 *   RTE_E_DidServices_0xf184_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf184_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf184_ReadData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf184_ReadData (returns application error)
*********************************************************************************************************************/
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;

	(void)Rte_Call_AppSwFingerPrint_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		(*data)[0] = 0x01U;

		for( i = 1u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = (*RtePim_AppSwFingerPrintData())[i-1U];
		}
	}

	else
	{
		(*data)[0] = 0x01U;
		(*data)[1] = 0x01U;
		for( i = 2u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_ASCIIFILLER_CNT_U08;
		}
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf184_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf184_WriteData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf184_WriteData(Dcm_15Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf184_E_NOT_OK
 *   RTE_E_DidServices_0xf184_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf184_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf184_WriteData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf184_WriteData (returns application error)
*********************************************************************************************************************/

	*ErrorCode = DCM_E_SERVICENOTSUPPORTED;
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf185_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf185_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf185_ReadData(Dcm_15Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf185_E_NOT_OK
 *   RTE_E_DidServices_0xf185_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf185_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf185_ReadData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf185_ReadData (returns application error)
*********************************************************************************************************************/
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;

	(void)Rte_Call_CalSwFingerPrint_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		(*data)[0] = 0x01U;

		for( i = 1u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = (*RtePim_CalSwFingerPrintData())[i-1U];
		}
	}

	else
	{
		(*data)[0] = 0x01U;
		(*data)[1] = 0x02U;
		for( i = 2u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_ASCIIFILLER_CNT_U08;
		}
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf185_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf185_WriteData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf185_WriteData(Dcm_15Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf185_E_NOT_OK
 *   RTE_E_DidServices_0xf185_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf185_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf185_WriteData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf185_WriteData (returns application error)
*********************************************************************************************************************/

	*ErrorCode = DCM_E_SERVICENOTSUPPORTED;
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf186_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf186_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf186_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf186_E_NOT_OK
 *   RTE_E_DidServices_0xf186_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf186_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf186_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf186_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(Dcm_SesCtrlType, AUTOMATIC) Session_Cnt_T_enum;

	(void)Dcm_GetSesCtrlType(&Session_Cnt_T_enum);
	(*data)[0] = (uint8) Session_Cnt_T_enum;

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf187_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf187>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SparePartNumber_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf187_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf187_ReadData(Dcm_11Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf187_E_NOT_OK
 *   RTE_E_DidServices_0xf187_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf187_ReadData (returns application error)
 *********************************************************************************************************************/
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;
    
	(void)Rte_Call_ECUSparePartNo_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
    
    if ( (ErrorStatus_Cnt_T_enum != NVM_REQ_NOT_OK) && (ErrorStatus_Cnt_T_enum != NVM_REQ_NV_INVALIDATED) )
    {
        for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = (*Rte_Pim_ECUSparePartNoData())[i];
		}
    }
    else
    {
        for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = 0x20u;
		}
    }

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf187_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xf187>
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
 *   Std_ReturnType Rte_Call_ECUSparePartNo_SetRamBlockStatus(Boolean RamBlockStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf187_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xf187_WriteData(Dcm_11Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf187_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_WriteData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf187_WriteData (returns application error)
 *********************************************************************************************************************/

  VAR(uint16, AUTOMATIC) i;

  for( i = 0u; i < TableSize_m(*data); i++ )
  {
      (*Rte_Pim_ECUSparePartNoData())[i] = (*data)[i];
  }

  (void)Rte_Call_ECUSparePartNo_SetRamBlockStatus(TRUE);
    
  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf188_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf188_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf188_ReadData(Dcm_11Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf188_E_NOT_OK
 *   RTE_E_DidServices_0xf188_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf188_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf188_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf188_ReadData (returns application error)
*********************************************************************************************************************/
	VAR(uint8, AUTOMATIC) i;

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = k_CustDIDCals_Cnt_u08.VehicleManfECUSwNo_DIDF188_ASCII_u08[i];
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf18c_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf18c>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_ECUSerialNumber_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf18c_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf18c_ReadData(Dcm_15Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf18c_E_NOT_OK
 *   RTE_E_DidServices_0xf18c_E_PENDING
 *
 *********************************************************************************************************************/
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18c_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18c_ReadData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf18c_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;

	(void)Rte_Call_ECUSerialNumberData_GetErrorStatus(&ErrorStatus_Cnt_T_enum);

	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = (*Rte_Pim_ECUSerialNumberData())[i];
		}
	}
	else
	{
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = 0x30U;
		}
	}

	return RTE_E_OK;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf18c_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf18c>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_ECUSerialNumber_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf18c_WriteData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf18c_WriteData(Dcm_15Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf18c_E_NOT_OK
 *   RTE_E_DidServices_0xf18c_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18c_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18c_WriteData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf18c_WriteData (returns application error)
 *********************************************************************************************************************/
	VAR(uint16, AUTOMATIC) i;

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*Rte_Pim_ECUSerialNumberData())[i] = (*data)[i];
	}

	(void)Rte_Call_ECUSerialNumberData_WriteBlock(NULL_PTR);

	return RTE_E_OK;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf191_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf191>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_ECUHardwareNumber_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf191_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf191_ReadData(Dcm_11Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf191_E_NOT_OK
 *   RTE_E_DidServices_0xf191_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf191_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf191_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf191_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8, AUTOMATIC) i;

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = k_CustDIDCals_Cnt_u08.VehicleManfECUHwNo_DIDF191_ASCII_u08[i];
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf192_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf192_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf192_ReadData(Dcm_11Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf192_E_NOT_OK
 *   RTE_E_DidServices_0xf192_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf192_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf192_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf192_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(uint8, AUTOMATIC) i;

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = k_CustDIDCals_Cnt_u08.SupplierManfECUHwPartNo_DIDF192_ASCII_u08[i];
	}

	return RTE_E_OK;
	

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf193_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf193>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_ECUHardwareNumber_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf193_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf193_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf193_E_NOT_OK
 *   RTE_E_DidServices_0xf193_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf193_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf193_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf193_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8, AUTOMATIC) i;

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = k_CustDIDCals_Cnt_u08.SupplierManfECUHwVerNo_DIDF193_ASCII_u08;
	}

	return RTE_E_OK;
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf194_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf194>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf194_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf194_ReadData(Dcm_11Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf194_E_NOT_OK
 *   RTE_E_DidServices_0xf194_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf194_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf194_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf194_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8, AUTOMATIC) i;

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = k_CustDIDCals_Cnt_u08.VehicleManfECUSwNo_DIDF188_ASCII_u08[i];
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf195_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf195>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf195_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf195_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf195_E_NOT_OK
 *   RTE_E_DidServices_0xf195_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf195_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf195_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf195_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8, AUTOMATIC) i;

	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = k_SWRelNum_Cnt_u8[i + 12U];
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf1a0_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf1a0_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf1a0_ReadData(Dcm_6Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf1a0_E_NOT_OK
 *   RTE_E_DidServices_0xf1a0_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a0_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a0_ReadData(P2VAR(Dcm_67Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf1a0_ReadData (returns application error)
*********************************************************************************************************************/

	VAR(uint8, AUTOMATIC) i;
	VAR(uint8, AUTOMATIC) DIDf187data_T_u08[11];
	VAR(uint8, AUTOMATIC) DIDf194data_T_u08[11];
	VAR(uint8, AUTOMATIC) DIDf192data_T_u08[11];
	VAR(uint8, AUTOMATIC) DIDf158data_T_u08[4];
	VAR(uint8, AUTOMATIC) DIDf100data_T_u08[7];

	(void)DidServices_0xf187_ReadData(&DIDf187data_T_u08);
	(void)DidServices_0xf194_ReadData(&DIDf194data_T_u08);
	(void)DidServices_0xf192_ReadData(&DIDf192data_T_u08);
	(void)DidServices_0xf158_ReadData(&DIDf158data_T_u08);
	(void)DidServices_0xf100_ReadData(&DIDf100data_T_u08);

	for(i= 0u; i< TableSize_m(DIDf187data_T_u08); i++)
	{
		(*data)[i] = DIDf187data_T_u08[i];
	}

	for(i= 0u; i< TableSize_m(DIDf194data_T_u08); i++)
	{
		(*data)[i + 11u] = DIDf194data_T_u08[i];
	}

	for(i= 0u; i< TableSize_m(DIDf192data_T_u08); i++)
	{
		(*data)[i + 22u] = DIDf192data_T_u08[i];
	}

	for(i=33u ; i< 50u; i++)
	{
		(*data)[i] = 0x30U;
	}

	for(i=0u ; i< TableSize_m(DIDf158data_T_u08); i++)
	{
		(*data)[i+50u] = DIDf158data_T_u08[i];
	}

	for(i= 0u; i< TableSize_m(DIDf100data_T_u08); i++)
	{
		(*data)[i+54u] = DIDf100data_T_u08[i];
	}

	for(i= 61u; i< TableSize_m(*data); i++)
	{
		(*data)[i] = 0x30U;
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf1a3_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x1004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf1a3_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf1a3_ReadData(Dcm_6Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf1a3_E_NOT_OK
 *   RTE_E_DidServices_0xf1a3_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a3_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a3_ReadData(P2VAR(Dcm_6Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
/**********************************************************************************************************************
* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
* Symbol: DidServices_0xf1a3_ReadData (returns application error)
*********************************************************************************************************************/

	/* Mode 0x03 */
	(*data)[0] = 0xFFU;	/* Algorithm ID Number (MSB) */
	(*data)[1] = 0xFFU;	/* Algorithm ID Number (LSB) */

	/* Mode 0x05 */
	(*data)[2] = 0x07U;	/* Algorithm ID Number (MSB) */
	(*data)[3] = 0xD3U;	/* Algorithm ID Number (LSB) */

	/* Mode 0x09 */
	(*data)[4] = 0xFFU;	/* Algorithm ID Number (MSB) */
	(*data)[5] = 0xFFU;	/* Algorithm ID Number (LSB) */

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a4_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf1a4_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
# endif
{
	(*data)[0] = 0x07U;
	(*data)[1] = 0xDCU;

	return RTE_E_OK;
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd01_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd01>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd01_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd01_ReadData(Dcm_322Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd01_E_NOT_OK
 *   RTE_E_DidServices_0xfd01_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd01_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd01_ReadData(P2VAR(Dcm_322Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd01_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD01u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd01_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd02_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd02>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd02_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd02_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd02_E_NOT_OK
 *   RTE_E_DidServices_0xfd02_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd02_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD02u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd02_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd02_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd02>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd02_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd02_WriteData(Dcm_4Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd02_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd02_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD02u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd03_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd03>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd03_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd03_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd03_E_NOT_OK
 *   RTE_E_DidServices_0xfd03_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd03_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd03_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd03_ReadData (returns application error)
 *********************************************************************************************************************/

	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;

	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD03u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);

	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd03_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}

	return RetValue_Cnt_T_u08;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd03_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd03>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd03_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd03_WriteData(Dcm_4Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd03_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd03_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd03_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd03_WriteData (returns application error)
 *********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;

	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD03u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd07_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd07>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd07_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd07_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd07_E_NOT_OK
 *   RTE_E_DidServices_0xfd07_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd07_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD07u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd07_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd07_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd07>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd07_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd07_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd07_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd07_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD07u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd0d_ReturnControlToECU
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReturnControlToECU> of PortPrototype <DidServices_0xfd0d>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd0d_ReturnControlToECU(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd0d_ReturnControlToECU(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd0d_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd0d_ReturnControlToECU (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD0Du, 0u, (uint8*)RequestData, RequestDataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd0d_ShortTermAdjustment
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ShortTermAdjustment> of PortPrototype <DidServices_0xfd0d>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd0d_ShortTermAdjustment(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd0d_ShortTermAdjustment(Dcm_2Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd0d_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ShortTermAdjustment(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd0d_ShortTermAdjustment (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) i;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD0Du, 3u, (uint8*)RequestData, RequestDataLength, &RespLen_Cnt_T_u16);
	
	if( *ErrorCode > 0u )
	{
		for( i = 0u; i < RequestDataLength; i++ )
		{
			*ResponseData[i] = *RequestData[i];
		}
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd0e_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd0e>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd0e_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd0e_ReadData(Dcm_8Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd0e_E_NOT_OK
 *   RTE_E_DidServices_0xfd0e_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0e_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0e_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd0e_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD0Eu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd0e_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd10_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd10>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd10_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd10_ReadData(Dcm_10Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd10_E_NOT_OK
 *   RTE_E_DidServices_0xfd10_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd10_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd10_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd10_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD10u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd10_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd11_ReturnControlToECU
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReturnControlToECU> of PortPrototype <DidServices_0xfd11>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd11_ReturnControlToECU(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd11_ReturnControlToECU(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd11_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd11_ReturnControlToECU (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD11u, 0u, (uint8*)RequestData, RequestDataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd11_ShortTermAdjustment
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ShortTermAdjustment> of PortPrototype <DidServices_0xfd11>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd11_ShortTermAdjustment(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd11_ShortTermAdjustment(Dcm_2Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd11_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ShortTermAdjustment(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd11_ShortTermAdjustment (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) i;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD11u, 3u, (uint8*)RequestData, RequestDataLength, &RespLen_Cnt_T_u16);
	
	if( *ErrorCode > 0u )
	{
		for( i = 0u; i < RequestDataLength; i++ )
		{
			*ResponseData[i] = *RequestData[i];
		}
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd12_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd12>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd12_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd12_ReadData(Dcm_28Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd12_E_NOT_OK
 *   RTE_E_DidServices_0xfd12_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_ReadData(P2VAR(Dcm_28Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd12_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD12u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd12_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd12_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd12>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd12_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd12_WriteData(Dcm_28Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd12_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_WriteData(P2VAR(Dcm_28Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd12_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD12u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd13_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd13>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd13_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd13_ReadData(Dcm_75Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd13_E_NOT_OK
 *   RTE_E_DidServices_0xfd13_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd13_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd13_ReadData(P2VAR(Dcm_75Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd13_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD13u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd19_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd14_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd14>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd14_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd14_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd14_E_NOT_OK
 *   RTE_E_DidServices_0xfd14_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd14_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd14_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd14_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD14u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd14_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd17_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd17>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd17_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd17_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd17_E_NOT_OK
 *   RTE_E_DidServices_0xfd17_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd17_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd17_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd17_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD17u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd17_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd19_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd19>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd19_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd19_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd19_E_NOT_OK
 *   RTE_E_DidServices_0xfd19_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd19_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD19u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd19_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd19_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd19>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd19_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd19_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd19_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd19_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD19u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1a_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd1a>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1a_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd1a_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1a_E_NOT_OK
 *   RTE_E_DidServices_0xfd1a_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1a_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1a_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1a_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD1Au, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd1a_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1b_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd1b>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1b_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd1b_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1b_E_NOT_OK
 *   RTE_E_DidServices_0xfd1b_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1b_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD1Bu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd1b_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1b_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd1b>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1b_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd1b_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1b_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1b_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD1Bu, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1c_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd1c>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1c_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd1c_ReadData(Dcm_3Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1c_E_NOT_OK
 *   RTE_E_DidServices_0xfd1c_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1c_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1c_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1c_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD1Cu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd1c_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1e_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd1e>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1e_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd1e_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1e_E_NOT_OK
 *   RTE_E_DidServices_0xfd1e_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1e_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD1Eu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd1e_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1e_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd1e>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1e_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd1e_WriteData(Dcm_2Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1e_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1e_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD1Eu, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd20_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd20>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd20_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd20_ReadData(Dcm_3Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd20_E_NOT_OK
 *   RTE_E_DidServices_0xfd20_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd20_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd20_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd20_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD20u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd20_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd21_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd21>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd21_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd21_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd21_E_NOT_OK
 *   RTE_E_DidServices_0xfd21_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd21_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD21u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd21_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd21_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd21>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd21_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd21_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd21_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd21_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD21u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd23_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd23>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd23_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd23_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd23_E_NOT_OK
 *   RTE_E_DidServices_0xfd23_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd23_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD23u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd23_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd23_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd23>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd23_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd23_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd23_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd23_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD23u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd25_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd25>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd25_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd25_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd25_E_NOT_OK
 *   RTE_E_DidServices_0xfd25_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd25_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD25u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd25_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd25_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd25>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd25_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd25_WriteData(Dcm_2Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd25_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd25_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD25u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd26_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd26>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd26_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd26_ReadData(Dcm_3Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd26_E_NOT_OK
 *   RTE_E_DidServices_0xfd26_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd26_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD26u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd26_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd26_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd26>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd26_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd26_WriteData(Dcm_3Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd26_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_WriteData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd26_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD26u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd27_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd27>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd27_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd27_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd27_E_NOT_OK
 *   RTE_E_DidServices_0xfd27_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd27_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD27u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd27_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd27_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd27>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd27_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd27_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd27_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd27_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD27u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd29_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd29>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd29_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd29_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd29_E_NOT_OK
 *   RTE_E_DidServices_0xfd29_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd29_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD29u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd29_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd29_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd29>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd29_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd29_WriteData(Dcm_2Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd29_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd29_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD29u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd30_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd30>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd30_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd30_ReadData(Dcm_5Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd30_E_NOT_OK
 *   RTE_E_DidServices_0xfd30_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_ReadData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd30_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD30u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd30_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd30_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd30>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd30_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd30_WriteData(Dcm_5Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd30_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_WriteData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd30_WriteData (returns application error)
 *********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD30u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd31_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd31>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd31_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd31_ReadData(Dcm_12Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd31_E_NOT_OK
 *   RTE_E_DidServices_0xfd31_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd31_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd31_ReadData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd31_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD31u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd31_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda1_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfda1>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda1_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfda1_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda1_E_NOT_OK
 *   RTE_E_DidServices_0xfda1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda1_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDA1u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfda1_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda1_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfda1>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda1_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfda1_WriteData(Dcm_4Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda1_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDA1u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda2_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfda2>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda2_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfda2_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda2_E_NOT_OK
 *   RTE_E_DidServices_0xfda2_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda2_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDA2u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfda2_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda2_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfda2>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda2_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfda2_WriteData(Dcm_4Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda2_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda2_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDA2u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda3_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfda3>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda3_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfda3_ReadData(Dcm_12Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda3_E_NOT_OK
 *   RTE_E_DidServices_0xfda3_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_ReadData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda3_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDA3u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfda3_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda3_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfda3>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda3_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfda3_WriteData(Dcm_12Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda3_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_WriteData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda3_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDA3u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdac_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdac>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdac_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdac_ReadData(Dcm_64Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdac_E_NOT_OK
 *   RTE_E_DidServices_0xfdac_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_ReadData(P2VAR(Dcm_64Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdac_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDACu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdac_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdac_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdac>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdac_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdac_WriteData(Dcm_64Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdac_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_WriteData(P2VAR(Dcm_64Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdac_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDACu, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdad_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdad>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdad_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdad_ReadData(Dcm_7Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdad_E_NOT_OK
 *   RTE_E_DidServices_0xfdad_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdad_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdad_ReadData(P2VAR(Dcm_7Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdad_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDADu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdad_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdae_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdae>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdae_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdae_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdae_E_NOT_OK
 *   RTE_E_DidServices_0xfdae_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdae_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDAEu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdae_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdae_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdae>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdae_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdae_WriteData(Dcm_2Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdae_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdae_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDAEu, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdaf_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdaf>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdaf_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdaf_ReadData(Dcm_176Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdaf_E_NOT_OK
 *   RTE_E_DidServices_0xfdaf_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdaf_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdaf_ReadData(P2VAR(Dcm_176Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdaf_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDAFu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdaf_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb0_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb0>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb0_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb0_ReadData(Dcm_256Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb0_E_NOT_OK
 *   RTE_E_DidServices_0xfdb0_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb0_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB0u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb0_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb0_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb0>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb0_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb0_WriteData(Dcm_256Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb0_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb0_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB0u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb1_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb1>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb1_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb1_ReadData(Dcm_256Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb1_E_NOT_OK
 *   RTE_E_DidServices_0xfdb1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb1_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB1u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb1_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb1_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb1>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb1_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb1_WriteData(Dcm_256Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb1_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB1u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb2_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb2>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb2_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb2_ReadData(Dcm_256Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb2_E_NOT_OK
 *   RTE_E_DidServices_0xfdb2_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb2_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB2u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb2_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb2_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb2>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb2_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb2_WriteData(Dcm_256Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb2_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb2_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB2u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb3_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb3>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb3_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb3_ReadData(Dcm_256Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb3_E_NOT_OK
 *   RTE_E_DidServices_0xfdb3_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb3_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB3u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb3_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb3_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb3>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb3_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb3_WriteData(Dcm_256Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb3_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb3_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB3u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb4_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb4>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb4_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb4_ReadData(Dcm_8Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb4_E_NOT_OK
 *   RTE_E_DidServices_0xfdb4_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb4_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB4u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb4_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb4_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb4>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb4_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb4_WriteData(Dcm_8Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb4_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_WriteData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb4_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB4u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb5_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb5>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb5_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb5_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb5_E_NOT_OK
 *   RTE_E_DidServices_0xfdb5_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb5_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB5u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb5_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb5_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb5>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb5_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb5_WriteData(Dcm_4Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb5_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb5_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB5u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb6_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb6>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb6_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb6_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb6_E_NOT_OK
 *   RTE_E_DidServices_0xfdb6_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb6_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB6u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb6_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb6_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb6>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb6_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb6_WriteData(Dcm_4Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb6_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb6_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB6u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb7_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb7>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb7_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb7_ReadData(Dcm_18Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb7_E_NOT_OK
 *   RTE_E_DidServices_0xfdb7_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_ReadData(P2VAR(Dcm_18Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb7_ReadData (returns application error)
 *********************************************************************************************************************/

	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;

	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB7u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);

	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb7_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}

	return RetValue_Cnt_T_u08;


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb7_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb7>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb7_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb7_WriteData(Dcm_18Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb7_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_WriteData(P2VAR(Dcm_18Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb7_WriteData (returns application error)
 *********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;

	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB7u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);

	return RTE_E_OK;


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0x0100>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf180>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf187>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf18a>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf18c>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf191>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf193>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf194>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf195>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd01>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd02>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd03>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd07>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd0e>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd10>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd12>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd13>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd14>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd17>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd19>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd1a>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd1b>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd1c>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd1e>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd20>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd21>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd23>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd25>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd26>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd27>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd29>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd30>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd31>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfda1>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfda2>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfda3>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdac>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdad>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdae>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdaf>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb0>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb1>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb2>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb3>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb4>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb5>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb6>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb7>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DidServices_ConditionCheckRead(Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0100_E_PENDING
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_ConditionCheckWrite
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0x0100>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xf187>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xf18a>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd02>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd07>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd12>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd19>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd1b>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd1e>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd21>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd23>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd25>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd26>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd27>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd29>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd30>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfda1>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfda2>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfda3>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdac>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdae>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb0>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb1>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb2>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb3>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb4>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb5>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb6>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb7>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DidServices_ConditionCheckWrite(Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0100_E_PENDING
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_ConditionCheckWrite (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ResetService_EcuReset
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <EcuReset> of PortPrototype <ResetService>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType ResetService_EcuReset(UInt8 resetType, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_ResetService_E_NOT_OK
 *   RTE_E_ResetService_E_PENDING
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) ResetService_EcuReset(UInt8 resetType, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ResetService_EcuReset (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0x0200_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0x0200>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0x0200_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0x0200_Start(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0x0200_E_PENDING
 *
 *********************************************************************************************************************/

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0x0200_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0x0200_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0x0200_Start (returns application error)
 *********************************************************************************************************************/

	VAR(Std_ReturnType, AUTOMATIC) RetVal_Cnt_T_enum = E_OK;

	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
    VAR(float32, AUTOMATIC) HwNm_T_f32;

    VAR(boolean, AUTOMATIC) VehicleSpeedValid_Cnt_T_lgc;
	
	(void)Rte_Read_VehSpd_Kph_f32(&VehSpd_Kph_T_f32);
	(void)Rte_Read_HwTrq_HwNm_f32(&HwNm_T_f32);
	(void)Rte_Read_VehicleSpeedValid_Cnt_lgc(&VehicleSpeedValid_Cnt_T_lgc);
	
	if (VehSpd_Kph_T_f32 > k_SrvcVehSpdLimit_Kph_f32)
	{
		RetVal_Cnt_T_enum = E_NOT_OK;
		DiagSvc_Routine0200FailReason_Cnt_M_u08 = D_EPSNRCVEHSPDTHRSHOLD_CNT_U08;
	}

	if (RetVal_Cnt_T_enum == E_OK)
	{
		if (Abs_f32_m(HwNm_T_f32) > k_SrvcHwTrqLimit_HwNm_f32)
		{
			RetVal_Cnt_T_enum = E_NOT_OK;
			DiagSvc_Routine0200FailReason_Cnt_M_u08 = D_EPSNRCHWTRQTHRSHOLD_CNT_U08;
		}
	}

	if (RetVal_Cnt_T_enum == E_OK)
	{
		if( VehicleSpeedValid_Cnt_T_lgc != TRUE )
		{
			RetVal_Cnt_T_enum = E_NOT_OK;
			DiagSvc_Routine0200FailReason_Cnt_M_u08 = D_EPSNRCVEHSPDINVALID_CNT_U08;
		}
	}

	if (RetVal_Cnt_T_enum == E_OK)
	{
		(void)Rte_Call_DigColPs_SCom_CustClearTrim();
		DiagSvc_Routine0200ClrTrimEn_Cnt_M_lgc = TRUE;
	}

	return RetVal_Cnt_T_enum;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0x0200_RequestResults
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0x0200>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0x0200_RequestResults(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0x0200_RequestResults(Dcm_3Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0x0200_E_PENDING
 *
 *********************************************************************************************************************/

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0x0200_RequestResults(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0x0200_RequestResults(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0x0200_RequestResults (returns application error)
 *********************************************************************************************************************/
{
	VAR(boolean, AUTOMATIC) NTC1F8_Cnt_T_lgc;

	*ResponseDataLength = 0x01U;

	(void)Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_HWASensorNotTrimmed, &NTC1F8_Cnt_T_lgc);

	if( (NTC1F8_Cnt_T_lgc == TRUE) || (DiagSvc_Routine0200FailReason_Cnt_M_u08 != 0x00U) )
	{
		if( DiagSvc_Routine0200FailReason_Cnt_M_u08 == D_EPSNRCVEHSPDTHRSHOLD_CNT_U08 )
		{
			(*ResponseData)[0] = 0x01U;
		}

		else if( DiagSvc_Routine0200FailReason_Cnt_M_u08 == D_EPSNRCVEHSPDINVALID_CNT_U08 )
		{
			(*ResponseData)[0] = 0x02U;
		}

		else if( DiagSvc_Routine0200FailReason_Cnt_M_u08 == D_EPSNRCHWTRQTHRSHOLD_CNT_U08 )
		{
			(*ResponseData)[0] = 0x03U;
		}

		else
		{
			(*ResponseData)[0] = 0x04U;
		}
	}

	else
	{
		(*ResponseData)[0] = 0xFFU;
	}

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xd001_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xd001>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xd001_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xd001_Start(Dcm_3Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xd001_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd001_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd001_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xd001_Start (returns application error)
 *********************************************************************************************************************/

	VAR(boolean, AUTOMATIC) DisableFailSafeReaction_Cnt_T_lgc;

	DisableFailSafeReaction_Cnt_T_lgc = TRUE;

	Rte_Write_DisableFailSafeReaction_Cnt_lgc(DisableFailSafeReaction_Cnt_T_lgc);

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xd001_Stop
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Stop> of PortPrototype <RoutineServices_0xd001>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xd001_Stop(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xd001_Stop(Dcm_3Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xd001_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd001_Stop(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd001_Stop(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Stop of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xd001_Stop (returns application error)
 *********************************************************************************************************************/

	VAR(boolean, AUTOMATIC) DisableFailSafeReaction_Cnt_T_lgc;

	DisableFailSafeReaction_Cnt_T_lgc = FALSE;

	Rte_Write_DisableFailSafeReaction_Cnt_lgc(DisableFailSafeReaction_Cnt_T_lgc);

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xd002_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xd002>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xd002_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xd002_Start(Dcm_3Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xd002_E_PENDING
 *
 *********************************************************************************************************************/
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd002_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xd002_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
# endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xd002_Start (returns application error)
 *********************************************************************************************************************/

	(*ResponseData)[0] = 0x00U;
	*ResponseDataLength = 0x01U;

	return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf000_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf000>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf000_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf000_Start(Dcm_3Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf000_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf000_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf000_Start(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf000_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF000u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf001_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf001>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf001_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf001_Start(Dcm_2Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf001_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf001_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf001_Start(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf001_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF001u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf003_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf003>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf003_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf003_Start(Dcm_1Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf003_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf003_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf003_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf003_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF003u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf004_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf004>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf004_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf004_Start(Dcm_1Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf004_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf004_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf004_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf004_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF004u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf005_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf005>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf005_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf005_Start(Dcm_2Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_3Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf005_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf005_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf005_Start(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf005_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF005u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf008_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf008>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf008_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf008_Start(Dcm_1Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf008_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf008_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf008_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf008_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF008u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf009_RequestResults
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <RequestResults> of PortPrototype <RoutineServices_0xf009>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf009_RequestResults(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf009_RequestResults(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf009_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_RequestResults(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_RequestResults(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf009_RequestResults (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF009u, 0x03u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf009_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf009>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf009_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf009_Start(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf009_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf009_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF009u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf009_Stop
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Stop> of PortPrototype <RoutineServices_0xf009>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf009_Stop(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf009_Stop(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf009_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Stop(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Stop(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf009_Stop (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF009u, 0x02u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf0ff_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf0ff>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf0ff_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf0ff_Start(Dcm_6Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf0ff_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf0ff_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf0ff_Start(P2VAR(Dcm_6Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf0ff_Start (returns application error)
 *********************************************************************************************************************/

	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF0FFu, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xfee0_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xfee0>
 *
 **********************************************************************************************************************
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_AbsHwPos_SCom_CustClrTrim(void)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_AbsHwPos_SCom_CustSetTrim(void)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_AbsHwPos_SCom_TrimNotPerformed
 *   Std_ReturnType Rte_Call_LrnEOT_Scom_ResetEOT(void)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_VehDyn_SCom_ResetCenter(void)
 *     Synchronous Server Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xfee0_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xfee0_Start(Dcm_1Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xfee0_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xfee0_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xfee0_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xfee0_Start (returns application error)
 *********************************************************************************************************************/
	
	VAR(Std_ReturnType, AUTOMATIC) RetVal_Cnt_T_enum;
	
	if( (*RequestData)[0] == 1u )
	{
		RetVal_Cnt_T_enum = Rte_Call_AbsHwPos_SCom_CustSetTrim();
		
		if( RetVal_Cnt_T_enum != RTE_E_OK )
		{
			*ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
		}
	}
	else if( (*RequestData)[0] == 2u )
	{
		Rte_Call_AbsHwPos_SCom_CustClrTrim();
		Rte_Call_LrnEOT_Scom_ResetEOT();
		Rte_Call_VehDyn_SCom_ResetCenter();
	}
	else
	{
		*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SecurityAccess_1_CompareKey
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <CompareKey> of PortPrototype <SecurityAccess_1>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType SecurityAccess_1_CompareKey(UInt8 *Key)
#else
 *   Std_ReturnType SecurityAccess_1_CompareKey(Dcm_SecAccess_1_KeyType *Key)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SecurityAccess_1_E_COMPARE_KEY_FAILED
 *   RTE_E_SecurityAccess_1_E_NOT_OK
 *   RTE_E_SecurityAccess_1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_CompareKey(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Key)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_CompareKey(P2VAR(Dcm_SecAccess_1_KeyType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Key)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_1_CompareKey (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SecurityAccess_1_GetSeed
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <GetSeed> of PortPrototype <SecurityAccess_1>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_DCMServices_GetSecurityLevel(Dcm_SecLevelType *SecLevel)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DCMServices_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType SecurityAccess_1_GetSeed(UInt8 *securityAccessDataRecord, UInt8 *Seed, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType SecurityAccess_1_GetSeed(Dcm_SecAccess_1_DataRecType *securityAccessDataRecord, Dcm_SecAccess_1_SeedType *Seed, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SecurityAccess_1_E_NOT_OK
 *   RTE_E_SecurityAccess_1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_GetSeed(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) securityAccessDataRecord, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_GetSeed(P2VAR(Dcm_SecAccess_1_DataRecType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) securityAccessDataRecord, P2VAR(Dcm_SecAccess_1_SeedType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_1_GetSeed (returns application error)
 *********************************************************************************************************************/
	
	VAR(Dcm_SecLevelType, AUTOMATIC) SecLevel_Cnt_T_enum;
	
	(void)Rte_Call_DCMServices_GetSecurityLevel(&SecLevel_Cnt_T_enum);
	
	if( SecLevel_Cnt_T_enum == DCM_SEC_LEV_LOCKED )
	{
		(*Seed)[0] = 0x11U;
		(*Seed)[1] = 0x22U;
		(*Seed)[2] = 0x33U;
		(*Seed)[3] = 0x44U;
	}
	else
	{
		(*Seed)[0] = D_DATAFILLER_CNT_U08;
		(*Seed)[1] = D_DATAFILLER_CNT_U08;
		(*Seed)[2] = D_DATAFILLER_CNT_U08;
		(*Seed)[3] = D_DATAFILLER_CNT_U08;
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SessionControl_ChangeIndication
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ChangeIndication> of PortPrototype <SessionControl>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SessionControl_ChangeIndication(Dcm_SesCtrlType SesCtrlTypeOld, Dcm_SesCtrlType SesCtrlTypeNew)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SessionControl_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SessionControl_ChangeIndication(Dcm_SesCtrlType SesCtrlTypeOld, Dcm_SesCtrlType SesCtrlTypeNew)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SessionControl_ChangeIndication (returns application error)
 *********************************************************************************************************************/
	VAR(uint32,  AUTOMATIC) ElapsedTime_mS_T_u32;
	VAR(uint32,  AUTOMATIC) ElapsedTime_min_T_u32;
	VAR(uint32, AUTOMATIC) TotalOdometer_Cnt_T_u32;

	VAR(uint16, AUTOMATIC) TotalOdometer_Cnt_T_u16;
	
	(void) Dem_EnableDTCSetting((uint32)DEM_DTC_GROUP_ALL_DTCS, (uint8)DEM_DTC_KIND_ALL_DTCS);
	if( SesCtrlTypeNew == DCM_PROGRAMMING_SESSION )
	{
		/* Write ECU Life TIme before jumping to Bootloader */
		(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(DiagSvc_Timer_mS_M_u32, &ElapsedTime_mS_T_u32);
		ElapsedTime_min_T_u32 = ElapsedTime_mS_T_u32 / (1000u * 60u); /* converting ms to min */
		ElapsedTime_min_T_u32 += DiagSvc_ECULifeTimeMinsInitial_Cnt_M_u32;
		*Rte_Pim_ECULifeTimeMinsData() = ElapsedTime_min_T_u32;
		(void)Rte_Call_ECULifeTimeMins_WriteBlock(NULL_PTR);

		/* Ignition counter - DID 0x2001 */
		Rte_Read_TotalOdometerIPC_Cnt_u32(&TotalOdometer_Cnt_T_u32);
		TotalOdometer_Cnt_T_u16 = (uint16) (TotalOdometer_Cnt_T_u32 / 16U);
		*Rte_Pim_TotalOdometerData() = TotalOdometer_Cnt_T_u16;
		(void)Rte_Call_TotalOdometer_WriteBlock(NULL_PTR);

		Appl_WaitNvMReady(0U, TRUE);

		TWrapC_CallFblStart();
	}

	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SessionControl_ConfirmationRespPending
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConfirmationRespPending> of PortPrototype <SessionControl>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SessionControl_ConfirmationRespPending(Dcm_ConfirmationStatusType status)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SessionControl_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SessionControl_ConfirmationRespPending(Dcm_ConfirmationStatusType status)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SessionControl_ConfirmationRespPending (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SessionControl_GetSesChgPermission
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <GetSesChgPermission> of PortPrototype <SessionControl>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SessionControl_GetSesChgPermission(Dcm_SesCtrlType SesCtrlTypeActive, Dcm_SesCtrlType SesCtrlTypeNew)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SessionControl_E_FORCE_RCRRP
 *   RTE_E_SessionControl_E_NOT_OK
 *   RTE_E_SessionControl_E_PENDING
 *   RTE_E_SessionControl_E_SESSION_NOT_ALLOWED
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SessionControl_GetSesChgPermission(Dcm_SesCtrlType SesCtrlTypeActive, Dcm_SesCtrlType SesCtrlTypeNew)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SessionControl_GetSesChgPermission (returns application error)
 *********************************************************************************************************************/
	VAR(uint32,  AUTOMATIC) ElapsedTime_mS_T_u32;
	VAR(uint32,  AUTOMATIC) ElapsedTime_min_T_u32;
	VAR(uint32, AUTOMATIC) TotalOdometer_Cnt_T_u32;

	VAR(uint16, AUTOMATIC) TotalOdometer_Cnt_T_u16;
	
	if( SesCtrlTypeNew == DCM_PROGRAMMING_SESSION )
	{
		/* Write ECU Life TIme before jumping to Bootloader */
		(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(DiagSvc_Timer_mS_M_u32, &ElapsedTime_mS_T_u32);
		ElapsedTime_min_T_u32 = ElapsedTime_mS_T_u32 / (1000u * 60u); /* converting ms to min */
		ElapsedTime_min_T_u32 += DiagSvc_ECULifeTimeMinsInitial_Cnt_M_u32;
		*Rte_Pim_ECULifeTimeMinsData() = ElapsedTime_min_T_u32;
		(void)Rte_Call_ECULifeTimeMins_WriteBlock(NULL_PTR);

		/* Ignition counter - DID 0x2001 */
		Rte_Read_TotalOdometerIPC_Cnt_u32(&TotalOdometer_Cnt_T_u32);
		TotalOdometer_Cnt_T_u16 = (uint16) (TotalOdometer_Cnt_T_u32 / 16U);
		*Rte_Pim_TotalOdometerData() = TotalOdometer_Cnt_T_u16;
		(void)Rte_Call_TotalOdometer_WriteBlock(NULL_PTR);

		Appl_WaitNvMReady(0U, TRUE);

		TWrapC_CallFblStart();
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_DIAGSVC_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_CheckUnspecifiedService(uint8 sid, P2VAR(boolean,AUTOMATIC,DCM_VAR_NOINIT) hasSprmib)
{
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	switch( sid )
	{
		case 0x11u:
			*hasSprmib = TRUE;
			RetValue_Cnt_T_u08 = DCM_E_OK;
			break;

		case 0x34u:
		case 0x36u:
		case 0x37u:
			RetValue_Cnt_T_u08 = DCM_E_OK;
			break;
		
		default:
			RetValue_Cnt_T_u08 = DCM_E_NOT_OK;
			break;
	}
	
	return RetValue_Cnt_T_u08;
}


FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_HandleUnspecifiedService(uint8                           sid
																,Dcm_MsgType                     requestPtr
																,Dcm_MsgLenType                  reqDataLen
																,Dcm_MsgType                     responsePtr
																,Dcm_MsgLenPtrType               resDataLenPtr
																,Dcm_NegativeResponseCodePtrType errorPtr)
{
	VAR(Dcm_SesCtrlType, AUTOMATIC) Session_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;
	
	switch( sid )
	{
		case 0x11u:
		case 0x81u:
			if( reqDataLen != 1u )
			{
				*errorPtr = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
			}

			else if( (requestPtr[0] == 0x01u) ||
					 (requestPtr[0] == 0x03u) )
			{
				
				if( Rte_SignlCondn_VehicleSpeed_Kph_f32 < k_VehSpdResetThresh_Kph_f32 ) 
				{
					if( Abs_f32_m(Rte_Sweep_OutputHwTrq_HwNm_f32) < k_HwTrqResetThresh_Kph_f32 )
					{
						if( requestPtr[0] == 0x01u )
						{
						DiagSvc_HardReset_Cnt_M_lgc = TRUE;
							responsePtr[0] = 0x01u;
							*resDataLenPtr = 1u;
						}
						else
						{
						DiagSvc_SoftReset_Cnt_M_lgc = TRUE;
							responsePtr[0] = 0x03u;
							*resDataLenPtr = 1u;
						}
					}
					else
					{
						*errorPtr = DCM_E_CONDITIONSNOTCORRECT;
					}
				}
				else
				{
					*errorPtr = DCM_E_CONDITIONSNOTCORRECT;
				}
			}
			else if( requestPtr[0] == 0x60u )
			{
				*errorPtr = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0x1160u, requestPtr[0], (uint8*)responsePtr, 0u, resDataLenPtr);
			}
			else
			{
				*errorPtr = DCM_E_SUBFUNCTIONNOTSUPPORTED;
			}
			
			break;
		
		case 0x34u:
		case 0x36u:
		case 0x37u:
			*errorPtr = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
			break;
		
		default:
			*errorPtr = DCM_E_SERVICENOTSUPPORTED;
			break;
	}
	
	return DCM_E_OK;
}


FUNC(void, DCM_APPL_CODE) Dcm_PostHandleUnspecifiedService(uint8 sid, Dcm_ConfirmationStatusType status)
{
	switch( sid )
	{
		case 0x11u:
			if( DiagSvc_HardReset_Cnt_M_lgc == TRUE )
			{
				Mcu_PerformReset();
			}
			else if( DiagSvc_SoftReset_Cnt_M_lgc == TRUE )
			{
				StaMd_SCom_EcuReset();
			}
			else
			{
				/* do nothing */
			}
			break;
		
		default:
			break;
	}
}


FUNC(void, DEM_APPL_CODE) Appl_Dem_GenericFailStateChangeNotification(boolean failState)
{
	/* do nothing */
}


FUNC(void, DEM_APPL_CODE) Appl_Dem_CurrentFailStateChangeNotification(boolean failState)
{
	/* do nothing */
}


FUNC(Std_ReturnType, DEM_APPL_CODE) Appl_Dem_CBValByDID_0x1008(P2VAR(Dem_MaxDataValueType, AUTOMATIC, DEM_APPL_DATA) DemDataValueByDataIDBuffer)
{
	(void)DidServices_0x1008_ReadData(DemDataValueByDataIDBuffer);
	return E_OK;
}


FUNC(Std_ReturnType, DEM_APPL_CODE) Appl_Dem_CBValByDID_0x1009(P2VAR(Dem_MaxDataValueType, AUTOMATIC, DEM_APPL_DATA) DemDataValueByDataIDBuffer)
{
	(void)DidServices_0x1009_ReadData(DemDataValueByDataIDBuffer);
	return E_OK;
}


FUNC(Std_ReturnType, DEM_APPL_CODE) Appl_Dem_CBValByDID_0x200a(P2VAR(Dem_MaxDataValueType, AUTOMATIC, DEM_APPL_DATA) DemDataValueByDataIDBuffer)
{
	(void)DidServices_0x200a_ReadData(DemDataValueByDataIDBuffer);
	return E_OK;
}


FUNC(Std_ReturnType, DEM_APPL_CODE) Appl_Dem_CBValByDID_0x2001(P2VAR(Dem_MaxDataValueType, AUTOMATIC, DEM_APPL_DATA) DemDataValueByDataIDBuffer)
{
	(void)DidServices_0x2001_ReadData(DemDataValueByDataIDBuffer);
	return E_OK;
}


FUNC(Std_ReturnType, DEM_APPL_CODE) Appl_Dem_CBValByDID_0x1004(P2VAR(Dem_MaxDataValueType, AUTOMATIC, DEM_APPL_DATA) DemDataValueByDataIDBuffer)
{
	(void)DidServices_0x1004_ReadData(DemDataValueByDataIDBuffer);
	return E_OK;
}


FUNC(Std_ReturnType, DEM_APPL_CODE) Appl_Dem_CBValByDID_0x1002(P2VAR(Dem_MaxDataValueType, AUTOMATIC, DEM_APPL_DATA) DemDataValueByDataIDBuffer)
{
	(void)DidServices_0x1002_ReadData(DemDataValueByDataIDBuffer);
	return E_OK;
}


FUNC(Std_ReturnType, DEM_APPL_CODE) Appl_Dem_CBValByDID_0x0885(P2VAR(Dem_MaxDataValueType, AUTOMATIC, DEM_APPL_DATA) DemDataValueByDataIDBuffer)
{
	(void)DidServices_0x0885_ReadData(DemDataValueByDataIDBuffer);
	return E_OK;
}


FUNC(Std_ReturnType, DEM_APPL_CODE) Appl_Dem_CBValByDID_0x0ad8(P2VAR(Dem_MaxDataValueType, AUTOMATIC, DEM_APPL_DATA) DemDataValueByDataIDBuffer)
{
	(*DemDataValueByDataIDBuffer)[0] = D_DATAFILLER_CNT_U08;

	return E_OK;
}


FUNC(Std_ReturnType, DEM_APPL_CODE) Appl_Dem_CBExtDataRec_0x01(P2VAR(Dem_MaxExtendedDataRecordType, AUTOMATIC, DEM_APPL_DATA) ExtendedDataRecordBuffer)
{
	return E_OK;
}


STATIC FUNC(uint16, RTE_AP_DIAGSVC_APPL_CODE) PROXICRC_CCIT16(P2VAR(uint8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 length)
{
	VAR(uint16, AUTOMATIC) i;
	VAR(uint16, AUTOMATIC) CrcValue_T_u16 = 0x0000U;
	VAR(uint16, AUTOMATIC) CrcValue1_T_u16;
	VAR(uint16, AUTOMATIC) CrcValue2_T_u16;
	
	VAR(uint8, AUTOMATIC) ReverseData_T_u08;
	
	while ( length > 0x00U )
	{
		ReverseData_T_u08 = Reverse_8bit(*(data));
		CrcValue_T_u16 ^= ( ((uint16)ReverseData_T_u08) << 8U);

		for (i = 0U; i < 8U; i++)
		{
			if ( (CrcValue_T_u16 & 0x8000U) != 0x00U )
			{
				CrcValue_T_u16 = (CrcValue_T_u16 << 1U) ^ CRC_POLYNOMIAL_16;
			}
			else
			{
				CrcValue_T_u16 <<= 1U;
			}
		}
		data++;
		length = length - 0x01U;
	}
	
	CrcValue1_T_u16 = (uint16) (Reverse_8bit((uint8)(CrcValue_T_u16 & 0x00FFU))) << 8U;
	CrcValue2_T_u16 = (uint16) (Reverse_8bit((uint8)((CrcValue_T_u16 & 0xFF00U) >> 8U)));
	CrcValue_T_u16 = (CrcValue1_T_u16 | CrcValue2_T_u16);

	return CrcValue_T_u16;
}

STATIC FUNC(uint8, RTE_AP_DIAGSVC_APPL_CODE) Reverse_8bit(uint8 value)
{
	VAR(uint8, AUTOMATIC) ReverseValue_T_u08;
	VAR(uint8, AUTOMATIC) CCIT16Lookup_Cnt_T_u08[16] = { 0x00u, 0x08u, 0x04u, 0x0Cu, 0x02u, 0x0Au, 0x06u, 0x0Eu, 0x01u, 0x09u, 0x05u, 0x0Du, 0x03u, 0x0Bu, 0x07u, 0x0Fu };
	
   /* Reverse the top and bottom nibble then swap them */
   ReverseValue_T_u08 = ( (uint8)(CCIT16Lookup_Cnt_T_u08[value & 0x0FU] << 4U) | (uint8)(CCIT16Lookup_Cnt_T_u08[value >> 4U]) );
   
   return ReverseValue_T_u08;
}

STATIC FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) UpdateProxiErrorStatus(uint8 Errorcode, uint8 Byte , uint8 BitInfoMask)
{
	if( DiagSvc_ProxiErrorCount_Cnt_M_u08 < 0x03U)
	{
		DiagSvc_ProxiErrorStatus_Cnt_M_u08[(3U*DiagSvc_ProxiErrorCount_Cnt_M_u08)] = Errorcode;
		DiagSvc_ProxiErrorStatus_Cnt_M_u08[(3U*DiagSvc_ProxiErrorCount_Cnt_M_u08) + 1u] = (Byte + 1U);
		DiagSvc_ProxiErrorStatus_Cnt_M_u08[(3U*DiagSvc_ProxiErrorCount_Cnt_M_u08) + 2u] = BitInfoMask;
		DiagSvc_ProxiErrorCount_Cnt_M_u08++;
	}
}

FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) UpdateFirstDTCDetect(void)
{
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;

	VAR(uint32,  AUTOMATIC) ElapsedTime_min_T_u32;
	VAR(uint32,  AUTOMATIC) ElapsedTime_sec_T_u32;
	VAR(uint16,  AUTOMATIC) ElapsedTime_sec_T_u16;

	VAR(uint32,  AUTOMATIC) ElapsedTime_mS_T_u32;
	VAR(uint32,  AUTOMATIC) FirstDTCDetectMinsData_T_u32;

	/* Check enabled only for First DTC */
	if( DiagSvc_FirstDTCDetected_Cnt_M_lgc == FALSE )
	{
		DiagSvc_FirstDTCDetected_Cnt_M_lgc = TRUE;

		(void)Rte_Call_FirstDTCDetectMins_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
		FirstDTCDetectMinsData_T_u32 = *Rte_Pim_FirstDTCDetectMinsData();

		if( (ErrorStatus_Cnt_T_enum != NVM_REQ_OK)  || (FirstDTCDetectMinsData_T_u32 == 0xFFFFFFFFU) )
		{
			(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(DiagSvc_Timer_mS_M_u32, &ElapsedTime_mS_T_u32);
			/* Write First DTC Detect Time in Mins */
			ElapsedTime_min_T_u32 = ElapsedTime_mS_T_u32 / (1000u * 60u); /* converting ms to min */

			*Rte_Pim_FirstDTCDetectMinsData() = ElapsedTime_min_T_u32 + DiagSvc_ECULifeTimeMinsInitial_Cnt_M_u32;
			(void)Rte_Call_FirstDTCDetectMins_WriteBlock(NULL_PTR);

			/* Write First DTC Detect Time in Secs */
			ElapsedTime_sec_T_u32 = ElapsedTime_mS_T_u32 / (1000u * D_ECULIFETIMESECS_CNT_F32); /* converting ms to sec */
			ElapsedTime_sec_T_u16 = (uint16) ElapsedTime_sec_T_u32;

			*Rte_Pim_FirstDTCDetectSecsData() = ElapsedTime_sec_T_u16;
			(void)Rte_Call_FirstDTCDetectSecs_WriteBlock(NULL_PTR);
		}
	}

	else
	{
		/* Do Nothing */
		/* Time of First DTC already stored */
	}
}

STATIC FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) ClearFirstDTCDetect(void)
{
	DiagSvc_FirstDTCDetected_Cnt_M_lgc = FALSE;

	*Rte_Pim_FirstDTCDetectMinsData() = 0xFFFFFFFFU;
	(void)Rte_Call_FirstDTCDetectMins_WriteBlock(NULL_PTR);
}

FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_DspPostClearDiagInfo(Dcm_ConfirmationStatusType status)
{
	Dcm_DspPostClearDiagInfo(status);
	ClearFirstDTCDetect();
}

STATIC FUNC(void,	RTE_AP_DIAGSVC_APPL_CODE) ResetIOCtrlTimer(P2VAR(uint32, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) IOControlTimer_mS_T_u32)
{
	(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(IOControlTimer_mS_T_u32);
}

FUNC(NvM_RequestResultType, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_ProxiConfigurationGetErrorStatus(void)
{
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;

	(void)Rte_Call_ProxiConfiguration_GetErrorStatus(&ErrorStatus_Cnt_T_enum); /* PRQA S 3417 */ /* PRQA S 3426 */

	return ErrorStatus_Cnt_T_enum;
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
