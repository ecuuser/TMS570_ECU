/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Sa_DigMSB.c
 *     Workspace:  C:/Rijvi_Synergy/Core_Component/Working/DigMSB-jzk9cc/DigMSB/autosar
 *     SW-C Type:  Sa_DigMSB
 *  Generated at:  Fri Feb  6 14:11:42 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Sa_DigMSB>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu May 2 13:41:03 2013
* %version:          17 %
* %derived_by:       jzk9cc %
* %date_modified:    Fri May 30 13:41:03 2014
******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author          Change Description               							SCR #
                                     (MDD Rev & Date)
-------   -------  --------  -----------------------------------   								----------
* 07/07/13    1.0 	Selva      Initial Creation                     								N/A
* 07/25/13    2.0   Selva      Includes changes for ver2											N/A
* 08/01/13    3.0   Selva      Updated "DeltaMechMtrPos_Rev_T_s15p16" correction                 	N/A
* 08/09/13    4,5   Selva      Fixed Rx buffer position, Parity Calculation,
									updated names to match standards      						  9605
* 08/22/13    6.0   Selva      Provided Data Sync buffers
* 09/11/13    7.0   LWW        Updated per new FDD v3
* 09/12/13    8.0   LWW        Anomaly 5611 correction
* 09/22/13    9.0	Selva      Anomaly 5640 correction                                           10224
* 12/03/13    10    OT         FDD v4 update
* 12/10/13    11    OT         Unit fix (anomaly 6172)
* 3/31/14     12	KMC/Selva  Prototype of new multiple transfer group SPI transfers             
                                (v5 Prerelease) and also A5929 fixed.
* 04/04/14	  13    Selva      Updated per new FDDv6
								(Merged 50A and 51 in one component)
* 05/30/14	  14    Selva      Anomaly 6811, 6831 correction                                      12306 
* 12/03/14    15    JK         Anomaly 6855 ,6864 correction              						  12077 
* 01/26/15    16    Rijvi      Updated per FDD rev.007                                            12931
* 02/06/15    17    Rijvi      Updated per FDD rev.008. Anomaly 6855 ,6864 recorrected			  12997
******************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Sa_DigMSB.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Sa_DigMSB_Cfg.h"
#include "Sa_DigMSB.h"
#include "DigMSB_Cfg.h"
#include "GlobalMacro.h"
#include "fixmath.h"
#include "SystemTime.h"
#include "CalConstants.h"

/* PRQA S 3218 EOF */
/* MISRA-C:2004 Rule 8.7: Deviation required for the display variables and filter constants because of memory map */

/* PRQA S 4393 ,4394 EOF */
/* MISRA-C:2004 Rule 10.3: Deviation required for the AUTOSAR Compliance */

/* PRQA S 4533 EOF */
/* MISRA-C:2004 Rule 12.7: Deviation required for the AUTOSAR Compliance */

/* PRQA S 5087 EOF */
/* MISRA-C:2004 Rule 19.1: Deviation required for the AUTOSAR Compliance */

/* MISRA-C:2004 Rule 19.7: Deviation required as it runs in the faster loop */


#define D_PIREVQUATER_REV_S15P16				(FPM_InitFixedPoint_m( 0.25, s15p16_T))
#define D_PIREVQUATER_REV_U16                   (FPM_InitFixedPoint_m( 0.25, u0p16_T))
#define D_MASK16BITS_CNT_U16					0xFFFFu
#define  D_HALFREV_REV_U0P16 					32768U
#define  D_REVTODEG_DEG_F32                     360.0F
          
/**********Register Configuration ***/
#define D_PWMGRPWRD0_CNT_U16   			0x200U               /*** Read Turns Counter Register ***/
#define D_PWMGRPWRD1_CNT_U16  			0U                   /*** Read Position Register ***/
#define D_PWMGRPWRD2_CNT_U16  			0x400U   			 /*** Read Error Register ***/
#define D_ASYNCCONFIGGRPWRD0_CNT_U16 	0x8800U      /*** Write to Control Base Registers***/
#define D_ASYNCCONFIGGRPWRD1_CNT_U16  	0x800U       /*** Read the Control Register***/
#define D_ASYNCCONFIGGRPWRD2_CNT_U16 	0x400U       /*** Read Error Configuration***/
#define D_INITCUMPOS_REV_S15P16     	78643200      /*** =9830400*(2^16)/(2^13)****/


#define ParityCalculation_m(data) (((T_PARITYTABLE_CNT_U8[(data) & 0xFFu] + T_PARITYTABLE_CNT_U8[((data) >> 8u) & 0xFFu]) ^ 1u) & 1u) /* PRQA S 3453 */

typedef enum {
	NTCSTATE_INVALID		= 0x00U,
	NTCSTATE_FAILED			= 0x01U,
	NTCSTATE_PASSED    		= 0x02U
} NTCStateType_Enum;


#define DIGMSB_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

STATIC VAR(uint16, AUTOMATIC)   DigMSB_PWMGrpData_Cnt_M_u16[3];
STATIC VAR(uint16, AUTOMATIC)   DigMSB_AsyncConfigGrpDie1_Cnt_M_u16[3];
STATIC VAR(uint16, AUTOMATIC)   DigMSB_AsyncConfigGrpDie2_Cnt_M_u16[3];
STATIC VAR(uint16, AUTOMATIC)   DigMSB_MechMtrPos1UnCorrec_Rev_M_u0p16;
STATIC VAR(uint16, AUTOMATIC)   DigMSB_RxMtrPos1ParityAccum_Cnt_M_u16;
STATIC VAR(uint16, AUTOMATIC)   DigMSB_Die1UnderVoltgFltAccum_Cnt_M_u16;
STATIC VAR(uint16, AUTOMATIC)   DigMSB_Die1UnderVoltgFltAccum2_Cnt_M_u16;
STATIC VAR(uint16, AUTOMATIC)   DigMSB_Die2UnderVoltgFltAccum_Cnt_M_u16;
STATIC VAR(uint16, AUTOMATIC)   DigMSB_Die1R0ParityFault_Cnt_M_u16;
STATIC VAR(uint16, AUTOMATIC)   DigMSB_Die1R1ParityFault_Cnt_M_u16;
STATIC VAR(uint16, AUTOMATIC)   DigMSB_Die2R2ParityFault_Cnt_M_u16;
STATIC VAR(uint16, AUTOMATIC)   DigMSB_Die1ErrorOkAcc_Cnt_M_u16;
STATIC VAR(uint16, AUTOMATIC)   DigMSB_Die2ErrorOkAcc_Cnt_M_u16;
STATIC VAR(uint16,   AUTOMATIC) DigMSB_MechMtrPos2UnCorrec_Rev_M_u0p16;
STATIC VAR(uint16,   AUTOMATIC) DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_u16;
STATIC VAR(uint16,   AUTOMATIC) DigMSB_ErrorRegTCAcc_Cnt_M_u16;
STATIC VAR(uint16,   AUTOMATIC) DigMSB_ErrorRegVehMaskAcc_Cnt_M_u16;
STATIC volatile VAR(uint16,   AUTOMATIC) DigMSB_CorrectedElecMtrPos2_Rev_D_u0p16;
STATIC VAR(uint16,   AUTOMATIC) DigMSB_MtrPosErrAcc_Cnt_M_u16;
STATIC VAR(uint16,   AUTOMATIC) DigMSB_PrevMechMtrPos1_Rev_M_u0p16;
STATIC VAR(sint16,  AUTOMATIC)  DigMSB_Die2RevCntr_Cnt_M_s16;
STATIC VAR(sint16,  AUTOMATIC)  DigMSB_Die1RevCntr_Cnt_M_s16;
STATIC VAR(uint16,   AUTOMATIC) DigMSB_Die1R2ParityFault_Cnt_M_u16;
STATIC VAR(uint16,   AUTOMATIC) DigMSB_Die2R1ParityFault_Cnt_M_u16;
STATIC VAR(uint16,   AUTOMATIC) DigMSB_Die2R0ParityFault_Cnt_M_u16;
#define DIGMSB_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

#define DIGMSB_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(float32,   AUTOMATIC) DigMSB_AlignedCumMechMtrPos2CRF_Deg_D_f32;
STATIC volatile VAR(float32,   AUTOMATIC) DigMSB_AlignedCumMechMtrPos2MRF_Deg_D_f32;
STATIC VAR(sint32,  AUTOMATIC) DigMSB_CumMtrPos1MRF_Rev_M_s15p16;  /* REQ: ES050A #439 I */
STATIC VAR(sint32,  AUTOMATIC) DigMSB_AlignedCumMechMtrPos1_Rev_M_s15p16;
STATIC VAR(sint32,  AUTOMATIC) DigMSB_AlignedCumMechMtrPos2_Rev_M_s15p16;
STATIC VAR(sint32,  AUTOMATIC) DigMSB_PrevAlignedCumMechMtrPos2_Rev_M_s15p16;
STATIC VAR(sint32,  AUTOMATIC) DigMSB_PrevAlignedCumMechMtrPos1_Rev_M_s15p16;

#define DIGMSB_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define DIGMSB_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AUTOMATIC) DigMSB_ResetTC_Cnt_M_lgc;
STATIC VAR(boolean, AUTOMATIC) DigMSB_ResetIC_Cnt_M_lgc;
STATIC VAR(boolean, AUTOMATIC) DigMSB_Die1ErrorOkAccPassed_Cnt_M_lgc;
STATIC VAR(boolean, AUTOMATIC) DigMSB_Die2ErrorOkAccPassed_Cnt_M_lgc;
STATIC VAR(boolean, AUTOMATIC) DigMSB_EnableAsyncConfigGrp_Cnt_M_lgc;
STATIC VAR(boolean, AUTOMATIC) DigMSB_AlignedCumMtrPos2Init_Cnt_M_lgc;
STATIC VAR(boolean, AUTOMATIC) DigMSB_AlignedCumMtrPos1Init_Cnt_M_lgc;
#define DIGMSB_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define DIGMSB_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint8, AUTOMATIC)   DigMSB_Die2Errorflag_Cnt_M_u08;
STATIC VAR(uint8, AUTOMATIC)   DigMSB_Die1Errorflag_Cnt_M_u08;
STATIC VAR(uint8,   AUTOMATIC) DigMSB_CumMechMtrPosStatus_Cnt_M_u08;
STATIC VAR(uint8,   AUTOMATIC) DigMSB_AlignedCumMechMtrPosStatus_Cnt_M_u08;
#define DIGMSB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */

#define DIGMSB_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(NTCStateType_Enum,  AUTOMATIC) DigMSB_Die1ErrorOk_Cnt_M_enum;
STATIC VAR(NTCStateType_Enum,  AUTOMATIC) DigMSB_Die2ErrorOk_Cnt_M_enum;
STATIC VAR(NTCStateType_Enum,  AUTOMATIC) DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_enum;
STATIC VAR(NTCStateType_Enum,  AUTOMATIC) DigMSB_MtrPosErrAcc_Cnt_M_enum;
STATIC VAR(NTCStateType_Enum,  AUTOMATIC) DigMSB_ErrorRegTC_Cnt_M_enum;
STATIC VAR(NTCStateType_Enum, AUTOMATIC)  DigMSB_ErrorRegVehMask_Cnt_M_enum;

#define DIGMSB_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

STATIC INLINE FUNC(uint16, SA_DIGMSB_CODE) MtrPosProcessing( VAR(uint16, AUTOMATIC) RxData_Cnt_T_u16,
															 P2VAR(uint8, AUTOMATIC, AUTOMATIC) DiexRx2Parity_Cnt_T_u08,
                                                             P2VAR(uint8, AUTOMATIC, AUTOMATIC) DiexUnderVoltgFault_Cnt_T_u08 );

STATIC INLINE FUNC(uint8, SA_DIGMSB_CODE) ErrorRegisterProcessing( VAR(uint16, AUTOMATIC) RxData_Cnt_T_u16	,
																   P2VAR(uint8, AUTOMATIC, AUTOMATIC) DiexRx0Parity_Cnt_T_u08 );

STATIC INLINE FUNC(sint16, SA_DIGMSB_CODE) RevCntrProcessing( VAR(uint16, AUTOMATIC) RxData_Cnt_T_u16,
															  P2VAR(uint8, AUTOMATIC, AUTOMATIC) DiexRx1Parity_Cnt_T_u08 );

#define DIGMSB_START_SEC_CONST_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC CONST(uint8, AUTOMATIC) T_PARITYTABLE_CNT_U8[256]  = { 0u,1u,1u,0u,1u,0u,0u,1u,1u,0u,0u,1u,0u,1u,1u,0u,
															  1u,0u,0u,1u,0u,1u,1u,0u,0u,1u,1u,0u,1u,0u,0u,1u,
															  1u,0u,0u,1u,0u,1u,1u,0u,0u,1u,1u,0u,1u,0u,0u,1u,
															  0u,1u,1u,0u,1u,0u,0u,1u,1u,0u,0u,1u,0u,1u,1u,0u,
															  1u,0u,0u,1u,0u,1u,1u,0u,0u,1u,1u,0u,1u,0u,0u,1u,
															  0u,1u,1u,0u,1u,0u,0u,1u,1u,0u,0u,1u,0u,1u,1u,0u,
															  0u,1u,1u,0u,1u,0u,0u,1u,1u,0u,0u,1u,0u,1u,1u,0u,
															  1u,0u,0u,1u,0u,1u,1u,0u,0u,1u,1u,0u,1u,0u,0u,1u,
															  1u,0u,0u,1u,0u,1u,1u,0u,0u,1u,1u,0u,1u,0u,0u,1u,
															  0u,1u,1u,0u,1u,0u,0u,1u,1u,0u,0u,1u,0u,1u,1u,0u,
															  0u,1u,1u,0u,1u,0u,0u,1u,1u,0u,0u,1u,0u,1u,1u,0u,
															  1u,0u,0u,1u,0u,1u,1u,0u,0u,1u,1u,0u,1u,0u,0u,1u,
															  0u,1u,1u,0u,1u,0u,0u,1u,1u,0u,0u,1u,0u,1u,1u,0u,
															  1u,0u,0u,1u,0u,1u,1u,0u,0u,1u,1u,0u,1u,0u,0u,1u,
															  1u,0u,0u,1u,0u,1u,1u,0u,0u,1u,1u,0u,1u,0u,0u,1u,
															  0u,1u,1u,0u,1u,0u,0u,1u,1u,0u,0u,1u,0u,1u,1u,0u };
#define DIGMSB_STOP_SEC_CONST_8
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
 * SInt32: Integer in interval [-2147483648...2147483647] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * EnergyModeStateType: Enumeration of integer in interval [0...3] with enumerators
 *   NORMAL (0u)
 *   PRODUCTION (1u)
 *   TRANSPORTATION (2u)
 *   FLASH (3u)
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
 * Array Types:
 * ============
 * HarCompTbl: Array with 1024 element(s) of type SInt16
 *
 * Record Types:
 * =============
 * DigMSBEOLType: Record with elements
 *   MtrPosBEMF_Rev_u0p16 of type UInt16
 *   MtrPosBEMFRedundant_Rev_u0p16 of type UInt16
 *   MtrPos1HarCompTbl_Rev_s2p13 of type HarCompTbl
 *   MtrPos2HarCompTbl_Rev_s2p13 of type HarCompTbl
 *   CRC_Cnt_u16 of type UInt16
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
 * Float: D_ZERO_ULS_F32 = 0
 * SInt32: D_NEGONE_CNT_S32 = -1
 * SInt8: D_ZERO_CNT_S8 = 0
 * UInt16: D_ONE_CNT_U16 = 1u
 * UInt16: D_ZERO_CNT_U16 = 0u
 * UInt8: D_ONE_CNT_U8 = 1u
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
 *   DigMSBEOLType *Rte_Pim_DigMSBEOLData(void)
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_SA_DIGMSB_APPL_CODE
#include "MemMap.h"  /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigMSB_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
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

FUNC(void, RTE_SA_DIGMSB_APPL_CODE) DigMSB_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigMSB_Init
 *********************************************************************************************************************/
	VAR(uint16, AUTOMATIC) BEMFRedundant_Rev_T_u0p16;
	VAR(uint16, AUTOMATIC) BEMFMtrPos_Rev_u0p16;
	
	/* REQ: ES050A #620 I */ /* REQ: ES050A #596 I */ /* REQ: ES050A #594 I : Actual function is implemented inside the CMS (Common Manufacturing Service) component */
	BEMFMtrPos_Rev_u0p16 = Rte_Pim_DigMSBEOLData()->MtrPosBEMF_Rev_u0p16; 
	/* REQ: ES050A #620 I */ /* REQ: ES050A #596 I */ /* REQ: ES050A #594 I : Actual function is implemented inside the CMS (Common Manufacturing Service) component */
	BEMFRedundant_Rev_T_u0p16 = Redundant_Format_1_m(Rte_Pim_DigMSBEOLData()->MtrPosBEMFRedundant_Rev_u0p16); 
	
	/* REQ: ES050A #634 I */  /* REQ: ES050A #646 I */  /* REQ: ES050A #547 I */
	if (BEMFMtrPos_Rev_u0p16  != BEMFRedundant_Rev_T_u0p16)  /* REQ: ES050A #549 I */
		{
		 (void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EEPROMDiagMtrStr, 1U, NTC_STATUS_FAILED); /* REQ: ES050A #609 I */ /* REQ: ES050A #551 I */
		
		}
	else  /* REQ: ES050A #555 I */
		{
		 (void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EEPROMDiagMtrStr, 0U, NTC_STATUS_PASSED); /* REQ: ES050A #609 I */ /* REQ: ES050A #555 I */
		}
	/* ENDREQ: ES050A #634 */  /* ENDREQ: ES050A #646 */  /* ENDREQ: ES050A #547 */
		
	DigMSB_PWMGrpData_Cnt_M_u16[0] = D_PWMGRPWRD0_CNT_U16;
	DigMSB_PWMGrpData_Cnt_M_u16[1] = D_PWMGRPWRD1_CNT_U16;
	DigMSB_PWMGrpData_Cnt_M_u16[2] = D_PWMGRPWRD2_CNT_U16;
	
	DigMSB_AsyncConfigGrpDie1_Cnt_M_u16[1] = D_ASYNCCONFIGGRPWRD1_CNT_U16 ;
	DigMSB_AsyncConfigGrpDie2_Cnt_M_u16[1] = D_ASYNCCONFIGGRPWRD1_CNT_U16 ;
	DigMSB_AsyncConfigGrpDie1_Cnt_M_u16[2] = D_ASYNCCONFIGGRPWRD2_CNT_U16 ;
	DigMSB_AsyncConfigGrpDie2_Cnt_M_u16[2] = D_ASYNCCONFIGGRPWRD2_CNT_U16 ;

	/* Set Tx Buffer for MSB1 */
	MSB1SetData(DigMSB_PWMGrpData_Cnt_M_u16); /* REQ: ES050A #416 I : The actual function is implemented in SpiNxt component */
	MSB1EnableDataTransfer(); /* REQ: ES050A #416 I : The actual function is implemented in SpiNxt component */
	
	MSB2SetData(DigMSB_PWMGrpData_Cnt_M_u16); /* REQ: ES050A #416 I : The actual function is implemented in SpiNxt component */
	MSB2EnableDataTransfer(); /* REQ: ES050A #416 I : The actual function is implemented in SpiNxt component */
	
	DigMSB_Die1ErrorOkAcc_Cnt_M_u16 = k_DigMSBParity_Cnt_str.Threshold/2u; /* REQ: ES050A #611 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should varies between (-)Threshold to (+)Threshold  */
	DigMSB_Die2ErrorOkAcc_Cnt_M_u16 = k_DigMSBParity_Cnt_str.Threshold/2u;
	DigMSB_MtrPosErrAcc_Cnt_M_u16   = k_MtrPos1vsMtrPos2Diag_Cnt_str.Threshold/2u;
	DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_u16= k_DigMSBTCRunTimeParity_Cnt_str.Threshold/2u;
	DigMSB_ErrorRegTCAcc_Cnt_M_u16= k_ErrorRegTCAcc_Cnt_str.Threshold/2u;
	DigMSB_ErrorRegVehMaskAcc_Cnt_M_u16=k_ErrorRegTCAcc_Cnt_str.Threshold/2u;

	
	DigMSB_PrevAlignedCumMechMtrPos2_Rev_M_s15p16 = D_INITCUMPOS_REV_S15P16 ;
    DigMSB_PrevAlignedCumMechMtrPos1_Rev_M_s15p16 = D_INITCUMPOS_REV_S15P16 ;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigMSB_Per2
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
 *   SInt8 Rte_IRead_DigMSB_Per2_AssistAssemblyPolarity_Cnt_s08(void)
 *   UInt16 Rte_IRead_DigMSB_Per2_CorrectedElecMtrPos_Rev_u0p16(void)
 *   Float Rte_IRead_DigMSB_Per2_CumMechMtrPos_Rev_f32(void)
 *   UInt16 Rte_IRead_DigMSB_Per2_Die1RxError_Cnt_u16(void)
 *   UInt16 Rte_IRead_DigMSB_Per2_Die1RxMtrPos_Cnt_u16(void)
 *   UInt16 Rte_IRead_DigMSB_Per2_Die1RxRevCtr_Cnt_u16(void)
 *   UInt16 Rte_IRead_DigMSB_Per2_Die1UnderVoltgFltAccum_Cnt_u16(void)
 *   UInt16 Rte_IRead_DigMSB_Per2_Die2RxError_Cnt_u16(void)
 *   UInt16 Rte_IRead_DigMSB_Per2_Die2RxMtrPos_Cnt_u16(void)
 *   UInt16 Rte_IRead_DigMSB_Per2_Die2RxRevCtr_Cnt_u16(void)
 *   SInt8 Rte_IRead_DigMSB_Per2_MtrPosPolarity_Cnt_s08(void)
 *   UInt16 Rte_IRead_DigMSB_Per2_RxMtrPosParityAccum_Cnt_u16(void)
 *   UInt16 Rte_IRead_DigMSB_Per2_UncorrMechMtrPos1_Rev_u0p16(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_DigMSB_Per2_AlignedCumMechMtrPosCRF_Deg_f32(Float data)
 *   Float *Rte_IWriteRef_DigMSB_Per2_AlignedCumMechMtrPosCRF_Deg_f32(void)
 *   void Rte_IWrite_DigMSB_Per2_AlignedCumMechMtrPosMRF_Deg_f32(Float data)
 *   Float *Rte_IWriteRef_DigMSB_Per2_AlignedCumMechMtrPosMRF_Deg_f32(void)
 *   void Rte_IWrite_DigMSB_Per2_AlignedCumMechMtrPosStatus_Cnt_u08(UInt8 data)
 *   UInt8 *Rte_IWriteRef_DigMSB_Per2_AlignedCumMechMtrPosStatus_Cnt_u08(void)
 *   void Rte_IWrite_DigMSB_Per2_CumMechMtrPosCRF_Deg_f32(Float data)
 *   Float *Rte_IWriteRef_DigMSB_Per2_CumMechMtrPosCRF_Deg_f32(void)
 *   void Rte_IWrite_DigMSB_Per2_CumMechMtrPosMRF_Deg_f32(Float data)
 *   Float *Rte_IWriteRef_DigMSB_Per2_CumMechMtrPosMRF_Deg_f32(void)
 *   void Rte_IWrite_DigMSB_Per2_CumMechMtrPosStatus_Cnt_u08(UInt8 data)
 *   UInt8 *Rte_IWriteRef_DigMSB_Per2_CumMechMtrPosStatus_Cnt_u08(void)
 *   void Rte_IWrite_DigMSB_Per2_MechMtrPos2_Rev_u0p16(UInt16 data)
 *   UInt16 *Rte_IWriteRef_DigMSB_Per2_MechMtrPos2_Rev_u0p16(void)
 *   void Rte_IWrite_DigMSB_Per2_SysCCumMechMtrPosMRF_Deg_f32(Float data)
 *   Float *Rte_IWriteRef_DigMSB_Per2_SysCCumMechMtrPosMRF_Deg_f32(void)
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
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGMSB_APPL_CODE) DigMSB_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigMSB_Per2
 *********************************************************************************************************************/


	VAR(uint16,  AUTOMATIC) Die2RxError_Cnt_T_u16;
	VAR(uint16,  AUTOMATIC) Die2RxMtrPos_Cnt_T_u16;
	VAR(uint16,  AUTOMATIC) Die2RxRevCtr_Cnt_T_u16;
	VAR(uint16,  AUTOMATIC) Die1RxRevCtr_Cnt_T_u16;
	VAR(uint16,  AUTOMATIC) Die1RxError_Cnt_T_u16;
	VAR(uint8,   AUTOMATIC) Die2Rx2Parity_Cnt_T_u08;
	VAR(uint8,   AUTOMATIC) Die2Errorflag_Cnt_T_u08;
	VAR(sint16,  AUTOMATIC) Die2RevCntr_Cnt_T_s16;
	VAR(uint16,  AUTOMATIC) MechMtrPos2UnCorrec_Rev_T_u0p16;
	VAR(uint16,  AUTOMATIC) Die1ErrorOkParamByte_Cnt_T_u16;
	VAR(boolean,  AUTOMATIC) Die1ErrorOkLgc_Cnt_T_lgc;
	VAR(sint16,  AUTOMATIC) Die1RevCntr_Cnt_T_s16;
	VAR(uint8,   AUTOMATIC) Die1R1ParityFault_Cnt_T_u08;
	VAR(uint8,   AUTOMATIC) Die1R0ParityFault_Cnt_T_u08;
	VAR(uint16,  AUTOMATIC) Die2ErrorOkParamByte_Cnt_T_u16;
	VAR(boolean,  AUTOMATIC) Die2ErrorOkLgc_Cnt_T_lgc;
	VAR(uint8,   AUTOMATIC) Die2R1ParityFault_Cnt_T_u08;
	VAR(uint8,   AUTOMATIC) Die2R0ParityFault_Cnt_T_u08;
	VAR(uint8,   AUTOMATIC) Die2UnderVoltgFault_Cnt_T_u08;

	VAR(float32, AUTOMATIC)  CumMechMtrPosMRF_Rev_T_f32;
	VAR(float32, AUTOMATIC) CumMechMtrPosMRF_Deg_T_f32;
	VAR(uint8,   AUTOMATIC)  Die1Errorflag_Cnt_T_u08;
	VAR(sint32,  AUTOMATIC)  AlignedCumMechMtrPos_Rev_T_s15p16;
	VAR(uint32,  AUTOMATIC)  AbsDiffAlignedCumMechMtrPos_Rev_T_u32;
	VAR(float32, AUTOMATIC) 	AlignedCumMechMtrPos1MRF_Deg_T_f32;
	VAR(float32, AUTOMATIC) 	AlignedCumMechMtrPos1CRF_Deg_T_f32;
	VAR(float32, AUTOMATIC) 	AlignedCumMechMtrPos2MRF_Deg_T_f32;
	VAR(float32, AUTOMATIC) 	DiffAlignedCumMechMtrPos1MRF_Deg_T_f32;
	VAR(float32, AUTOMATIC) 	AbsDiffAlignedCumMechMtrPos1MRF_Deg_T_f32;
	 VAR(uint16, AUTOMATIC) MechMtrPosLookup_Cnt_T_u16;
    VAR(sint16, AUTOMATIC) HarmonicCompensation_Rev_T_sm1p16;
    VAR(sint16, AUTOMATIC) HarmonicCompensation_Rev_T_s2p13;
    VAR(uint16, AUTOMATIC) MechMtrPos2_Rev_T_u0p16;
    VAR(uint16, AUTOMATIC) BEMFRedundant_Rev_T_u0p16;
    VAR(uint16, AUTOMATIC) CorrectedElecMtrPos2_Rev_T_u0p16;
    VAR(uint16, AUTOMATIC) CorrectedElecMtrPos_Rev_T_u0p16;
    VAR(uint16, AUTOMATIC) AbsDeltaElecMtrPos_Rev_T_u0p16;
	VAR(uint8, AUTOMATIC) TcErrorRegParam_Cnt_T_u08;
	VAR(sint8, AUTOMATIC) AssistAssemblyPolarity_Cnt_T_s08;
	VAR(sint8, AUTOMATIC) MtrPosPolarity_Cnt_T_s08;
	VAR(uint16, AUTOMATIC) RxMtrPosParityAccum_Cnt_T_u16;
	VAR(uint8, AUTOMATIC) DieErrorflag_Cnt_T_u08;
	VAR(float32, AUTOMATIC) CumMechMtrPosCRF_Deg_T_f32;
	VAR(uint16, AUTOMATIC) 	UncorrMechMtrPos1_Rev_T_u0p16;
	VAR(uint16, AUTOMATIC) Die1UnderVoltgFltAccum_Cnt_T_u16;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_DigMSB_Per2_CP0_CheckpointReached();

	UncorrMechMtrPos1_Rev_T_u0p16 = Rte_IRead_DigMSB_Per2_UncorrMechMtrPos1_Rev_u0p16();
	Die2RxError_Cnt_T_u16 = Rte_IRead_DigMSB_Per2_Die2RxError_Cnt_u16();
	Die2RxRevCtr_Cnt_T_u16 = Rte_IRead_DigMSB_Per2_Die2RxRevCtr_Cnt_u16();
	Die2RxMtrPos_Cnt_T_u16 = Rte_IRead_DigMSB_Per2_Die2RxMtrPos_Cnt_u16();
	Die1RxError_Cnt_T_u16 = Rte_IRead_DigMSB_Per2_Die1RxError_Cnt_u16();
	Die1RxRevCtr_Cnt_T_u16 = Rte_IRead_DigMSB_Per2_Die1RxRevCtr_Cnt_u16();
	CumMechMtrPosMRF_Rev_T_f32 = Rte_IRead_DigMSB_Per2_CumMechMtrPos_Rev_f32() ;
	RxMtrPosParityAccum_Cnt_T_u16 = Rte_IRead_DigMSB_Per2_RxMtrPosParityAccum_Cnt_u16()	;
	AssistAssemblyPolarity_Cnt_T_s08 = Rte_IRead_DigMSB_Per2_AssistAssemblyPolarity_Cnt_s08(); /* REQ: ES050A #623 I */
	MtrPosPolarity_Cnt_T_s08 =  Rte_IRead_DigMSB_Per2_MtrPosPolarity_Cnt_s08(); /* REQ: ES050A #624 I */
	CorrectedElecMtrPos_Rev_T_u0p16 =  Rte_IRead_DigMSB_Per2_CorrectedElecMtrPos_Rev_u0p16();
	Die1UnderVoltgFltAccum_Cnt_T_u16 = Rte_IRead_DigMSB_Per2_Die1UnderVoltgFltAccum_Cnt_u16(); /* REQ: ES050A #654 I */
	
	/**** Initialise AlignedCumulative & Cumulative Position  ***/
	AlignedCumMechMtrPos1MRF_Deg_T_f32 = D_ZERO_ULS_F32;
	AlignedCumMechMtrPos2MRF_Deg_T_f32 = D_ZERO_ULS_F32;
	AlignedCumMechMtrPos1CRF_Deg_T_f32 = D_ZERO_ULS_F32;
	
	/*Die1 Calculation*/
	/**** Die1 Processing ****/
	/**** Process ErrorReg and DieRevCtr****/
	
	Die1ErrorOkParamByte_Cnt_T_u16 = D_ZERO_CNT_U16;
	Die1ErrorOkLgc_Cnt_T_lgc = TRUE; /* REQ: ES050A #556 I */
	Die2ErrorOkLgc_Cnt_T_lgc = TRUE;
	
	
	/* REQ: ES050A #428 I */  /* REQ: ES050A #556 I */ /* REQ: ES050A #389 I */ /* REQ: ES050A #657 I */
	if (DigMSB_Die1R2ParityFault_Cnt_M_u16 != RxMtrPosParityAccum_Cnt_T_u16)
		{
			
			Die1ErrorOkParamByte_Cnt_T_u16 = D_ONE_CNT_U16 << 5u;
			Die1ErrorOkLgc_Cnt_T_lgc =  FALSE; 
		}
	DigMSB_Die1R2ParityFault_Cnt_M_u16 = RxMtrPosParityAccum_Cnt_T_u16;
	/* ENDREQ: ES050A #428 */
	
	
	/*** RevCntr Processing***/  /* REQ: ES050A #430 I */
	Die1RevCntr_Cnt_T_s16 = RevCntrProcessing(Die1RxRevCtr_Cnt_T_u16, &Die1R1ParityFault_Cnt_T_u08);
	
	if (Die1R1ParityFault_Cnt_T_u08 == D_ZERO_CNT_U8)
		{
		    DigMSB_Die1RevCntr_Cnt_M_s16 = Die1RevCntr_Cnt_T_s16;
			
			
		}
	else
		{
			DigMSB_Die1R1ParityFault_Cnt_M_u16 ++ ;
			Die1ErrorOkParamByte_Cnt_T_u16  |= (uint16) ((uint32)D_ONE_CNT_U16 << 6u); 
			Die1ErrorOkLgc_Cnt_T_lgc =  FALSE; 
		}
	/* ENDREQ: ES050A #430 */
		
		
	/*** Error Register Processing***/ /* REQ: ES050A #588 I */
	Die1Errorflag_Cnt_T_u08 = ErrorRegisterProcessing(Die1RxError_Cnt_T_u16, &Die1R0ParityFault_Cnt_T_u08);		
	
	if (Die1R0ParityFault_Cnt_T_u08  ==	D_ZERO_CNT_U8)
		{
			DigMSB_Die1Errorflag_Cnt_M_u08 = Die1Errorflag_Cnt_T_u08;
			if ((k_DigMSBErrorRegGenMask_Cnt_u08 & DigMSB_Die1Errorflag_Cnt_M_u08) != D_ZERO_CNT_U8)
				{
					Die1ErrorOkLgc_Cnt_T_lgc =  FALSE; 
				}
			
		}
	else
		{
			Die1ErrorOkLgc_Cnt_T_lgc =  FALSE;
			DigMSB_Die1R0ParityFault_Cnt_M_u16 = DigMSB_Die1R0ParityFault_Cnt_M_u16 + (uint16)Die1R0ParityFault_Cnt_T_u08 ; /* Increment Parity accumulator */ 
			Die1ErrorOkParamByte_Cnt_T_u16 |= D_ONE_CNT_U16 << 7u;
			
		}
	Die1ErrorOkParamByte_Cnt_T_u16 |= ((uint16)DigMSB_Die1Errorflag_Cnt_M_u08 & (uint16)k_DigMSBErrorRegGenMask_Cnt_u08);
	/* ENDREQ: ES050A #588 */  /* ENDREQ: ES050A #556 */ /* ENDREQ: ES050A #389 */
		
	/* REQ: ES050A #654 I */  /* REQ: ES050A #656 I */
	if( Die1UnderVoltgFltAccum_Cnt_T_u16 != DigMSB_Die1UnderVoltgFltAccum2_Cnt_M_u16 )
	{
		Die1ErrorOkLgc_Cnt_T_lgc =  FALSE;
		Die1ErrorOkParamByte_Cnt_T_u16  |= D_ONE_CNT_U16; 
		DigMSB_Die1UnderVoltgFltAccum2_Cnt_M_u16 = Die1UnderVoltgFltAccum_Cnt_T_u16;
	}
	/* ENDREQ: ES050A #654 */  /* ENDREQ: ES050A #656 */ /* ENDREQ: ES050A #657 */
		
	/* REQ: ES050A #400 I */ /* REQ: ES050A #428 I */  /* REQ: ES050A #588 I */  /* REQ: ES050A #430 I */
	if(Die1ErrorOkLgc_Cnt_T_lgc == FALSE)
	{
	
				DigMSB_Die1ErrorOkAcc_Cnt_M_u16 = DiagPStep_m(DigMSB_Die1ErrorOkAcc_Cnt_M_u16, k_DigMSBParity_Cnt_str); /* REQ: ES050A #611 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should vary between (-)Threshold to (+)Threshold  */
				
				if (DiagFailed_m(DigMSB_Die1ErrorOkAcc_Cnt_M_u16, k_DigMSBParity_Cnt_str) ==TRUE)
					{
						DigMSB_Die1ErrorOk_Cnt_M_enum = NTCSTATE_FAILED;	
						(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PriMSB_SinCosCorr, (uint8)Die1ErrorOkParamByte_Cnt_T_u16, NTC_STATUS_FAILED); /* REQ: ES050A #633 I */
					}
	}
	/* ENDREQ: ES050A #428 */  /* ENDREQ: ES050A #588 */  /* ENDREQ: ES050A #430 */
	else   /* REQ: ES050A #556 I */
	{
				DigMSB_Die1ErrorOkAcc_Cnt_M_u16 = DiagNStep_m(DigMSB_Die1ErrorOkAcc_Cnt_M_u16, k_DigMSBParity_Cnt_str); /* REQ: ES050A #611 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should vary between (-)Threshold to (+)Threshold  */
				if (DigMSB_Die1ErrorOkAcc_Cnt_M_u16 == D_ZERO_CNT_U16)
					{
					 DigMSB_Die1ErrorOk_Cnt_M_enum = NTCSTATE_PASSED;
					 (void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PriMSB_SinCosCorr, 0U, NTC_STATUS_PASSED); /* REQ: ES050A #633 I */
					 DigMSB_Die1ErrorOkAccPassed_Cnt_M_lgc = TRUE;
					}
	 
	}   /* ENDREQ: ES050A #556 */
	/* ENDREQ: ES050A #400 */
	
	
	
	/*** Die1 Error Determination ***/
	
	if ((DigMSB_Die1ErrorOkAccPassed_Cnt_M_lgc == TRUE))
	{
	
		AlignedCumMechMtrPos_Rev_T_s15p16 = (sint32)(UncorrMechMtrPos1_Rev_T_u0p16 & 0x7FFFU) + ((sint32) DigMSB_Die1RevCntr_Cnt_M_s16 << 15U);
	    AbsDiffAlignedCumMechMtrPos_Rev_T_u32 = (Abs_s32_m(AlignedCumMechMtrPos_Rev_T_s15p16 - DigMSB_PrevAlignedCumMechMtrPos1_Rev_M_s15p16));
		
		 if (AbsDiffAlignedCumMechMtrPos_Rev_T_u32 < (uint32)D_PIREVQUATER_REV_U16)
		 {
			DigMSB_AlignedCumMechMtrPos1_Rev_M_s15p16 = AlignedCumMechMtrPos_Rev_T_s15p16;
			DigMSB_AlignedCumMtrPos1Init_Cnt_M_lgc = TRUE;
		 }
		 else
		{
			/*** Do nothing***/
		
		} 
		DigMSB_PrevAlignedCumMechMtrPos1_Rev_M_s15p16 =AlignedCumMechMtrPos_Rev_T_s15p16 ;
		AlignedCumMechMtrPos1MRF_Deg_T_f32 = (FPM_FixedToFloat_m(DigMSB_AlignedCumMechMtrPos1_Rev_M_s15p16,s15p16_T)) * D_REVTODEG_DEG_F32 * (float32)MtrPosPolarity_Cnt_T_s08; /* REQ: ES050A #529 I */
		AlignedCumMechMtrPos1CRF_Deg_T_f32 =  AlignedCumMechMtrPos1MRF_Deg_T_f32 * (float32)AssistAssemblyPolarity_Cnt_T_s08; /* REQ: ES050A #424 I */
	}
	else
	{
	/*** Do nothing***/
	}
	

	/**** Die2 Processing ****/
	/**** Process ErrorReg and DieRevCtr****/
	
	Die2ErrorOkParamByte_Cnt_T_u16 = D_ZERO_CNT_U16;
	
	/* REQ: ES050A #582 I */ /* REQ: ES050A #526 I */ /* REQ: ES050A #651 I */ /* REQ: ES050A #589 I */ /* REQ: ES050A #584 I */ /* REQ: ES050A #585 I */
	MechMtrPos2UnCorrec_Rev_T_u0p16 = MtrPosProcessing(Die2RxMtrPos_Cnt_T_u16, &Die2Rx2Parity_Cnt_T_u08, &Die2UnderVoltgFault_Cnt_T_u08);  
	
	if ( (Die2Rx2Parity_Cnt_T_u08 + Die2UnderVoltgFault_Cnt_T_u08) == D_ZERO_CNT_U8 ) 
	{
		DigMSB_MechMtrPos2UnCorrec_Rev_M_u0p16 = MechMtrPos2UnCorrec_Rev_T_u0p16; /* REQ: ES050A #651 I */
	}
	else
	{
		/* REQ: ES050A #655 I */
		if(Die2UnderVoltgFault_Cnt_T_u08 != D_ZERO_CNT_U8)
		{
			DigMSB_Die2UnderVoltgFltAccum_Cnt_M_u16 = DigMSB_Die2UnderVoltgFltAccum_Cnt_M_u16 + (uint16)Die2UnderVoltgFault_Cnt_T_u08;
			Die2ErrorOkLgc_Cnt_T_lgc =  FALSE;
			Die2ErrorOkParamByte_Cnt_T_u16 = D_ONE_CNT_U16; 
		}
		/* ENDREQ: ES050A #655 */


		if( Die2Rx2Parity_Cnt_T_u08 != D_ZERO_CNT_U8 )
		{
			DigMSB_Die2R2ParityFault_Cnt_M_u16 = DigMSB_Die2R2ParityFault_Cnt_M_u16 + (uint16)Die2Rx2Parity_Cnt_T_u08;
			Die2ErrorOkLgc_Cnt_T_lgc =  FALSE;
			Die2ErrorOkParamByte_Cnt_T_u16 |= D_ONE_CNT_U16 << 5u; 
		}
	}
		
	
	
	/*** RevCntr Processing***/
	Die2RevCntr_Cnt_T_s16 = RevCntrProcessing(Die2RxRevCtr_Cnt_T_u16, &Die2R1ParityFault_Cnt_T_u08);
	
	if (Die2R1ParityFault_Cnt_T_u08 == D_ZERO_CNT_U8)
		{
		    DigMSB_Die2RevCntr_Cnt_M_s16 = Die2RevCntr_Cnt_T_s16;
		}
	else
		{
			DigMSB_Die2R1ParityFault_Cnt_M_u16 ++ ;
			Die2ErrorOkParamByte_Cnt_T_u16 |= D_ONE_CNT_U16 << 6u;
			Die2ErrorOkLgc_Cnt_T_lgc =  FALSE; 
		}
		
		
	/*** Error Register Processing***/
	Die2Errorflag_Cnt_T_u08 = ErrorRegisterProcessing(Die2RxError_Cnt_T_u16, &Die2R0ParityFault_Cnt_T_u08);		
	
	if (Die2R0ParityFault_Cnt_T_u08  ==	D_ZERO_CNT_U8)
		{
			DigMSB_Die2Errorflag_Cnt_M_u08 = Die2Errorflag_Cnt_T_u08;
			if ((k_DigMSBErrorRegGenMask_Cnt_u08 & DigMSB_Die2Errorflag_Cnt_M_u08) != D_ZERO_CNT_U8)
				{
					Die2ErrorOkLgc_Cnt_T_lgc =  FALSE; 
				}
		}
	else
		{
			DigMSB_Die2R0ParityFault_Cnt_M_u16 ++ ;
			Die2ErrorOkLgc_Cnt_T_lgc =  FALSE;
			Die2ErrorOkParamByte_Cnt_T_u16 |= D_ONE_CNT_U16 << 7u; 
		}
	Die2ErrorOkParamByte_Cnt_T_u16 |= ((uint16)DigMSB_Die2Errorflag_Cnt_M_u08 & (uint16)k_DigMSBErrorRegGenMask_Cnt_u08);
		
	/* REQ: ES050A #580 I */
	if(Die2ErrorOkLgc_Cnt_T_lgc == FALSE)
	{
	
				/* REQ: ES050A #612 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should vary between (-)Threshold to (+)Threshold  */
				DigMSB_Die2ErrorOkAcc_Cnt_M_u16 = DiagPStep_m(DigMSB_Die2ErrorOkAcc_Cnt_M_u16, k_DigMSBParity_Cnt_str);
				if (DiagFailed_m(DigMSB_Die2ErrorOkAcc_Cnt_M_u16, k_DigMSBParity_Cnt_str)==TRUE)
					{	
						DigMSB_Die2ErrorOk_Cnt_M_enum = NTCSTATE_FAILED;	
						(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_SecMSB_SinCosCorr, (uint8)Die2ErrorOkParamByte_Cnt_T_u16, NTC_STATUS_FAILED); /* REQ: ES050A #632 I */ 
					}
	} /* ENDREQ: ES050A #584 */ /* ENDREQ: ES050A #585 */
	else
	{
				
				/* REQ: ES050A #612 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should vary between (-)Threshold to (+)Threshold  */
				DigMSB_Die2ErrorOkAcc_Cnt_M_u16 = DiagNStep_m(DigMSB_Die2ErrorOkAcc_Cnt_M_u16, k_DigMSBParity_Cnt_str);
				if (DigMSB_Die2ErrorOkAcc_Cnt_M_u16 == D_ZERO_CNT_U16)
					{
					 DigMSB_Die2ErrorOk_Cnt_M_enum = NTCSTATE_PASSED;
					 (void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_SecMSB_SinCosCorr, 0U, NTC_STATUS_PASSED); /* REQ: ES050A #632 I */ /* REQ: ES050A #587 I */
					 DigMSB_Die2ErrorOkAccPassed_Cnt_M_lgc = TRUE;
					}
	 
	} /* ENDREQ: ES050A #580 */ /* ENDREQ: ES050A #582 */ /* ENDREQ: ES050A #589 */
	
	
	if (DigMSB_Die2ErrorOkAccPassed_Cnt_M_lgc == TRUE)
	{
	    /**** RevCentre is of resolution s14p1 resolution ***/
		AlignedCumMechMtrPos_Rev_T_s15p16 = (sint32)(DigMSB_MechMtrPos2UnCorrec_Rev_M_u0p16 & 0x7FFFU) + (((sint32)DigMSB_Die2RevCntr_Cnt_M_s16) << 15U); /*** To Convert to s15p16 resolution ***/
	    AbsDiffAlignedCumMechMtrPos_Rev_T_u32 = (Abs_s32_m(AlignedCumMechMtrPos_Rev_T_s15p16 - DigMSB_PrevAlignedCumMechMtrPos2_Rev_M_s15p16));
		
		 if (AbsDiffAlignedCumMechMtrPos_Rev_T_u32 < (uint32)(D_PIREVQUATER_REV_U16))
		 {
			DigMSB_AlignedCumMechMtrPos2_Rev_M_s15p16 = AlignedCumMechMtrPos_Rev_T_s15p16;
			DigMSB_AlignedCumMtrPos2Init_Cnt_M_lgc = TRUE;
		 }
		 else
		{
			/*** Do nothing***/
		
		} 
		 DigMSB_PrevAlignedCumMechMtrPos2_Rev_M_s15p16 =  AlignedCumMechMtrPos_Rev_T_s15p16;

		AlignedCumMechMtrPos2MRF_Deg_T_f32 = (FPM_FixedToFloat_m(DigMSB_AlignedCumMechMtrPos2_Rev_M_s15p16,s15p16_T)) * D_REVTODEG_DEG_F32 * (float32)MtrPosPolarity_Cnt_T_s08; /* REQ: ES050A #650 I */
		DigMSB_AlignedCumMechMtrPos2MRF_Deg_D_f32 = AlignedCumMechMtrPos2MRF_Deg_T_f32; /* REQ: ES050A #650 I */
		DigMSB_AlignedCumMechMtrPos2CRF_Deg_D_f32 = AlignedCumMechMtrPos2MRF_Deg_T_f32* (float32)AssistAssemblyPolarity_Cnt_T_s08;
	}
	else
	{
	/*** Do nothing***/
	}
	
	/*** Turns Counter 1 vs 2 Diagnostics ***/
	/* REQ: ES050A #499 I */ /* REQ: ES050A #495 I */ /* REQ: ES050A #493 I */ /* REQ: ES050A #491 I */
	if ((DigMSB_AlignedCumMtrPos2Init_Cnt_M_lgc == TRUE) &&(DigMSB_AlignedCumMtrPos1Init_Cnt_M_lgc == TRUE))
	{
			DiffAlignedCumMechMtrPos1MRF_Deg_T_f32 =AlignedCumMechMtrPos1MRF_Deg_T_f32 - AlignedCumMechMtrPos2MRF_Deg_T_f32 - (k_TurnsCntrOffset_Rev_f32*D_REVTODEG_DEG_F32);
			AbsDiffAlignedCumMechMtrPos1MRF_Deg_T_f32 = Abs_f32_m(DiffAlignedCumMechMtrPos1MRF_Deg_T_f32);
			if (AbsDiffAlignedCumMechMtrPos1MRF_Deg_T_f32 >= k_Die1vsDie2TrnsCntrThresh_Deg_f32 )
			{
				
				/* REQ: ES050A #616 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should varies between (-)Threshold to (+)Threshold  */
				DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_u16 = DiagPStep_m(DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_u16, k_DigMSBTCRunTimeParity_Cnt_str);
				if (DiagFailed_m(DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_u16, k_DigMSBTCRunTimeParity_Cnt_str) ==TRUE)
				{
					DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_enum =NTCSTATE_FAILED;
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TurnCntr_MainResets, 1U, NTC_STATUS_FAILED);
				}
			}
			else
			{ 
			
				/* REQ: ES050A #616 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should varies between (-)Threshold to (+)Threshold  */
				DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_u16 = DiagNStep_m(DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_u16, k_DigMSBTCRunTimeParity_Cnt_str);
				if (DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_u16 ==D_ZERO_CNT_U16)
					{
					DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_enum =NTCSTATE_PASSED;
					(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TurnCntr_MainResets, 0U, NTC_STATUS_PASSED);
					}
			}
	}  
	else
	{
		/***do nothing***/
	}
	/* ENDREQ: ES050A #499 */ /* ENDREQ: ES050A #495 */ /* ENDREQ: ES050A #493 */ /* ENDREQ: ES050A #491 */
	
	
	/* REQ: ES050A #643 I */
	MechMtrPosLookup_Cnt_T_u16 =  ((DigMSB_MechMtrPos2UnCorrec_Rev_M_u0p16 >> 6u) & 0x3FFu);
	/* REQ: ES050A #620 I */ /* REQ: ES050A #596 I */ /* REQ: ES050A #594 I : Actual function is implemented inside the CMS (Common Manufacturing Service) component */
    HarmonicCompensation_Rev_T_s2p13 = Rte_Pim_DigMSBEOLData()->MtrPos2HarCompTbl_Rev_s2p13[MechMtrPosLookup_Cnt_T_u16]; 
	
	HarmonicCompensation_Rev_T_sm1p16 = FPM_Fix_m(HarmonicCompensation_Rev_T_s2p13 ,s2p13_T, sm1p16_T);
    

    MechMtrPos2_Rev_T_u0p16 = (DigMSB_MechMtrPos2UnCorrec_Rev_M_u0p16 - (uint16)HarmonicCompensation_Rev_T_sm1p16) & 0xFFFFU; /* REQ: ES050A #535 I */

	/* REQ: ES050A #591 I */
	if( MtrPosPolarity_Cnt_T_s08 == D_NEGONE_CNT_S32)
	{
		MechMtrPos2_Rev_T_u0p16 = 65535U - MechMtrPos2_Rev_T_u0p16;
	}
	/* ENDREQ: ES050A #643 */ /* ENDREQ: ES050A #591 */
	
	/* REQ: ES050A #620 I */ /* REQ: ES050A #596 I */ /* REQ: ES050A #594 I : Actual function is implemented inside the CMS (Common Manufacturing Service) component */
    BEMFRedundant_Rev_T_u0p16 = Redundant_Format_1_m(Rte_Pim_DigMSBEOLData()->MtrPosBEMFRedundant_Rev_u0p16); 
    /* Rollover is expected and desired */
	CorrectedElecMtrPos2_Rev_T_u0p16 = MechMtrPos2_Rev_T_u0p16 -(k_Die2Offset_Rev_u3p13<<3U); /* REQ: ES050A #536 I */ /* REQ: ES050A #652 I */
    CorrectedElecMtrPos2_Rev_T_u0p16 =(uint16)((3U * (CorrectedElecMtrPos2_Rev_T_u0p16)) - BEMFRedundant_Rev_T_u0p16) & 0xFFFFU; /* REQ: ES050A #536 I */ /* REQ: ES050A #652 I */

	DigMSB_CorrectedElecMtrPos2_Rev_D_u0p16 = CorrectedElecMtrPos2_Rev_T_u0p16;
	
	
    /*** MtrPos1 Vs MtrPos2 Runtime Check ***/
	/* REQ: ES050A #466 I */ /* REQ: ES050A #468 I */ /* REQ: ES050A #472 I */
    AbsDeltaElecMtrPos_Rev_T_u0p16 = (uint16)Abs_s32_m((sint32)CorrectedElecMtrPos_Rev_T_u0p16 - (sint32)CorrectedElecMtrPos2_Rev_T_u0p16);

	if (AbsDeltaElecMtrPos_Rev_T_u0p16 > D_HALFREV_REV_U0P16)
	{
	    AbsDeltaElecMtrPos_Rev_T_u0p16 = (65535U - AbsDeltaElecMtrPos_Rev_T_u0p16 );
	}
	
	/* REQ: ES050A #631 I */
    if (AbsDeltaElecMtrPos_Rev_T_u0p16 > (k_MtrPos1vsMtrPos2Thresh_Rev_u3p13 <<3U))
    {
        DigMSB_MtrPosErrAcc_Cnt_M_u16 = DiagPStep_m(DigMSB_MtrPosErrAcc_Cnt_M_u16, k_MtrPos1vsMtrPos2Diag_Cnt_str); /* REQ: ES050A #614 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should vary between (-)Threshold to (+)Threshold */
		if (DiagFailed_m(DigMSB_MtrPosErrAcc_Cnt_M_u16, k_MtrPos1vsMtrPos2Diag_Cnt_str) ==TRUE)
			{	
				DigMSB_MtrPosErrAcc_Cnt_M_enum = NTCSTATE_FAILED;
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PriVsSec_SinCosCorr, 1U, NTC_STATUS_FAILED); /* REQ: ES050A #464 I */
			}
	}  
    else
    {
        DigMSB_MtrPosErrAcc_Cnt_M_u16 = DiagNStep_m(DigMSB_MtrPosErrAcc_Cnt_M_u16, k_MtrPos1vsMtrPos2Diag_Cnt_str); /* REQ: ES050A #614 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should vary between (-)Threshold to (+)Threshold */
		if (DigMSB_MtrPosErrAcc_Cnt_M_u16 == 0U)
		{	
			DigMSB_MtrPosErrAcc_Cnt_M_enum = NTCSTATE_PASSED;
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_PriVsSec_SinCosCorr, 0U, NTC_STATUS_PASSED);  /* REQ: ES050A #464 I */
		}
    }
	/* ENDREQ: ES050A #631 */ /* ENDREQ: ES050A #466 */ /* ENDREQ: ES050A #468 */ /* ENDREQ: ES050A #472 */

    	
	
	/****Turns Ctr Error Register Fault Processing****/	
	/* REQ: ES050A #422 I */ /* REQ: ES050A #480 I */ /* REQ: ES050A #482 I */ /* REQ: ES050A #484 I */ /* REQ: ES050A #504 I */ /* REQ: ES050A #506 I */
	DieErrorflag_Cnt_T_u08= Die2Errorflag_Cnt_T_u08 | Die1Errorflag_Cnt_T_u08;	
	TcErrorRegParam_Cnt_T_u08 = D_ZERO_CNT_U8;
	if 	(DieErrorflag_Cnt_T_u08 > D_ZERO_CNT_U8)
		{
		  TcErrorRegParam_Cnt_T_u08 = DieErrorflag_Cnt_T_u08;
		  if (Die1Errorflag_Cnt_T_u08 > 	D_ZERO_CNT_U8)
		  {
			TcErrorRegParam_Cnt_T_u08 |=  (uint8)((uint16)D_ONE_CNT_U8<< 5u);
		  }
		  if (Die2Errorflag_Cnt_T_u08 > 	D_ZERO_CNT_U8)
		  {
			TcErrorRegParam_Cnt_T_u08 |=  (uint8)((uint16)D_ONE_CNT_U8<< 6u);
		  }
		}
	
	/* REQ: ES050A #630 I */
	if ((DieErrorflag_Cnt_T_u08 & k_ErrorRegTCMask_Cnt_u08) > D_ZERO_CNT_U8)
	{
		/* REQ: ES050A #615 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should varies between (-)Threshold to (+)Threshold  */
	   DigMSB_ErrorRegTCAcc_Cnt_M_u16 = DiagPStep_m(DigMSB_ErrorRegTCAcc_Cnt_M_u16, k_ErrorRegTCAcc_Cnt_str);
	   if (DiagFailed_m(DigMSB_ErrorRegTCAcc_Cnt_M_u16, k_ErrorRegTCAcc_Cnt_str) ==TRUE)
				{
				DigMSB_ErrorRegTC_Cnt_M_enum = NTCSTATE_FAILED;
				(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TurnCntr_SensorPosFlt, TcErrorRegParam_Cnt_T_u08, NTC_STATUS_FAILED);
				}
	} /* ENDREQ: ES050A #484 */ /* ENDREQ: ES050A #506 */
	else
	{
		/* REQ: ES050A #615 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should varies between (-)Threshold to (+)Threshold  */
		DigMSB_ErrorRegTCAcc_Cnt_M_u16 = DiagNStep_m(DigMSB_ErrorRegTCAcc_Cnt_M_u16, k_ErrorRegTCAcc_Cnt_str);
		if (DigMSB_ErrorRegTCAcc_Cnt_M_u16 ==D_ZERO_CNT_U16)
		{
			DigMSB_ErrorRegTC_Cnt_M_enum = NTCSTATE_PASSED;
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TurnCntr_SensorPosFlt, 0U, NTC_STATUS_PASSED); /* REQ: ES050A #488 I */
		}
	}
	/* ENDREQ: ES050A #630 */ /* ENDREQ: ES050A #482 */ /* ENDREQ: ES050A #504 */
	
	/* REQ: ES050A #628 I */ /* REQ: ES050A #502 I */
	if ((DieErrorflag_Cnt_T_u08 & k_ErrorRegVehMask_Cnt_u08) > D_ZERO_CNT_U8)
	{
		/* REQ: ES050A #617 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should varies between (-)Threshold to (+)Threshold  */
	   DigMSB_ErrorRegVehMaskAcc_Cnt_M_u16 = DiagPStep_m(DigMSB_ErrorRegVehMaskAcc_Cnt_M_u16, k_ErrorRegTCAcc_Cnt_str);
	   if (DiagFailed_m(DigMSB_ErrorRegVehMaskAcc_Cnt_M_u16, k_ErrorRegTCAcc_Cnt_str) ==TRUE)
	   {
			DigMSB_ErrorRegVehMask_Cnt_M_enum = NTCSTATE_FAILED;
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TurnCntr_LowBattery, TcErrorRegParam_Cnt_T_u08, NTC_STATUS_FAILED);	
	   }
	}
	else
	{
		/* REQ: ES050A #617 P : Accumulator varies between Zero to the (+)2*Threshold, though according to ISO it should varies between (-)Threshold to (+)Threshold  */
		DigMSB_ErrorRegVehMaskAcc_Cnt_M_u16 = DiagNStep_m(DigMSB_ErrorRegVehMaskAcc_Cnt_M_u16, k_ErrorRegTCAcc_Cnt_str);
		if (DigMSB_ErrorRegVehMaskAcc_Cnt_M_u16 ==D_ZERO_CNT_U16)
		{
			DigMSB_ErrorRegVehMask_Cnt_M_enum = NTCSTATE_PASSED;
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_TurnCntr_LowBattery, 0U, NTC_STATUS_PASSED); /* REQ: ES050A #510 I */	
		}
	}
	/* ENDREQ: ES050A #628 */ /* ENDREQ: ES050A #422 */ /* ENDREQ: ES050A #480 */ /* ENDREQ: ES050A #502 */
	
	
	/* REQ: ES050A #541 I */
	/* REQ: ES050A #635 I */
	/****Aligned CumMtrPos Status Processing****/
	if ((DigMSB_Die1ErrorOk_Cnt_M_enum ==NTCSTATE_FAILED) ||(DigMSB_Die2ErrorOk_Cnt_M_enum ==NTCSTATE_FAILED) 
			||(DigMSB_MtrPosErrAcc_Cnt_M_enum ==NTCSTATE_FAILED) || (DigMSB_ErrorRegVehMask_Cnt_M_enum ==NTCSTATE_FAILED)
			||(DigMSB_ErrorRegTC_Cnt_M_enum==NTCSTATE_FAILED)||(DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_enum==NTCSTATE_FAILED))
	{
			DigMSB_AlignedCumMechMtrPosStatus_Cnt_M_u08 = 255u;
			DigMSB_ResetTC_Cnt_M_lgc = TRUE;
		
	}
	else if ((DigMSB_Die1ErrorOk_Cnt_M_enum ==NTCSTATE_PASSED) && (DigMSB_Die2ErrorOk_Cnt_M_enum ==NTCSTATE_PASSED) 
		&&(DigMSB_MtrPosErrAcc_Cnt_M_enum ==NTCSTATE_PASSED) && (DigMSB_ErrorRegVehMask_Cnt_M_enum ==NTCSTATE_PASSED) 
		&&(DigMSB_ErrorRegTC_Cnt_M_enum==NTCSTATE_PASSED)&&(DigMSB_Die1vsDie2TrnsCntrAcc_Cnt_M_enum==NTCSTATE_PASSED))
	{	
			DigMSB_AlignedCumMechMtrPosStatus_Cnt_M_u08 |= 100u;
			DigMSB_ResetTC_Cnt_M_lgc = FALSE;
	}
	else
	{
		 DigMSB_ResetTC_Cnt_M_lgc = FALSE;
		 
	}
	/* ENDREQ: ES050A #635 */
	/* ENDREQ: ES050A #541 */
	
	
	/* REQ: ES050A #540 I */
	/* REQ: ES050A #638 I */
	/****CumMtrPos Status Processing****/
	if ((DigMSB_Die1ErrorOk_Cnt_M_enum ==NTCSTATE_FAILED) ||(DigMSB_Die2ErrorOk_Cnt_M_enum ==NTCSTATE_FAILED) 
			||(DigMSB_MtrPosErrAcc_Cnt_M_enum ==NTCSTATE_FAILED))
		{
			DigMSB_CumMechMtrPosStatus_Cnt_M_u08 = 255u;
			DigMSB_ResetIC_Cnt_M_lgc = TRUE;
			
		}
	else if ((DigMSB_Die1ErrorOk_Cnt_M_enum ==NTCSTATE_PASSED) && (DigMSB_Die2ErrorOk_Cnt_M_enum ==NTCSTATE_PASSED) 
			&&(DigMSB_MtrPosErrAcc_Cnt_M_enum ==NTCSTATE_PASSED))
		{	
			DigMSB_CumMechMtrPosStatus_Cnt_M_u08 |= 100u;
			DigMSB_ResetIC_Cnt_M_lgc = FALSE;
		}
	
	else
		{	  
		  DigMSB_ResetTC_Cnt_M_lgc = FALSE;
		
		}
	/* ENDREQ: ES050A #638 */
	/* ENDREQ: ES050A #540 */
	
	
    CumMechMtrPosMRF_Deg_T_f32 = CumMechMtrPosMRF_Rev_T_f32 * D_REVTODEG_DEG_F32; /* REQ: ES050A #640 I */
	CumMechMtrPosCRF_Deg_T_f32 = CumMechMtrPosMRF_Deg_T_f32 * (float32)AssistAssemblyPolarity_Cnt_T_s08; /* REQ: ES050A #641 I */ /* REQ: ES050A #539 I */
	
	
	Rte_IWrite_DigMSB_Per2_AlignedCumMechMtrPosCRF_Deg_f32(AlignedCumMechMtrPos1CRF_Deg_T_f32); /* REQ: ES050A #637 I */
	Rte_IWrite_DigMSB_Per2_AlignedCumMechMtrPosMRF_Deg_f32(AlignedCumMechMtrPos1MRF_Deg_T_f32); /* REQ: ES050A #636 I */
	Rte_IWrite_DigMSB_Per2_CumMechMtrPosCRF_Deg_f32(CumMechMtrPosCRF_Deg_T_f32); /* REQ: ES050A #641 I */ /* REQ: ES050A #539 I */
    Rte_IWrite_DigMSB_Per2_CumMechMtrPosMRF_Deg_f32(CumMechMtrPosMRF_Deg_T_f32); /* REQ: ES050A #640 I */
	Rte_IWrite_DigMSB_Per2_MechMtrPos2_Rev_u0p16(MechMtrPos2_Rev_T_u0p16); /* REQ: ES050A #643 I */
	Rte_IWrite_DigMSB_Per2_SysCCumMechMtrPosMRF_Deg_f32(CumMechMtrPosMRF_Deg_T_f32); /* REQ: ES050A #639 I */
	Rte_IWrite_DigMSB_Per2_AlignedCumMechMtrPosStatus_Cnt_u08(DigMSB_AlignedCumMechMtrPosStatus_Cnt_M_u08); /* ENDREQ: ES050A #635 */
	Rte_IWrite_DigMSB_Per2_CumMechMtrPosStatus_Cnt_u08(DigMSB_CumMechMtrPosStatus_Cnt_M_u08); /* REQ: ES050A #638 I */
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_DigMSB_Per2_CP1_CheckpointReached();

	/* REQ: ES050A #595 N : This service is implemented inside the CMS (Common Manufacturing Service) component*/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigMSB_Per3
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
 *   EnergyModeStateType Rte_IRead_DigMSB_Per3_EnergyModeState_Cnt_enum(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGMSB_APPL_CODE) DigMSB_Per3(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DigMSB_Per3
 *********************************************************************************************************************/
	
	VAR(boolean, AUTOMATIC) ResetTC_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) ResetIC_Cnt_T_lgc;
	VAR(EnergyModeStateType, AUTOMATIC) EnergyModeState_Cnt_T_enum;
	VAR(uint16,  AUTOMATIC) EnergyModeState_Cnt_T_u16;
	VAR(uint16,  AUTOMATIC) ResetTC_Cnt_T_u08; 
	VAR(uint16,  AUTOMATIC) ResetIC_Cnt_T_u08;
	
	/* REQ: ES050A #621 I */ /* REQ: ES050A #622 I */
	ResetTC_Cnt_T_lgc = DigMSB_ResetTC_Cnt_M_lgc;
	ResetIC_Cnt_T_lgc = DigMSB_ResetIC_Cnt_M_lgc;
	EnergyModeState_Cnt_T_enum = Rte_IRead_DigMSB_Per3_EnergyModeState_Cnt_enum();  /* REQ: ES050A #625 I */
	/* Tx Data */
	
	if( EnergyModeState_Cnt_T_enum == TRANSPORTATION )
	{
		EnergyModeState_Cnt_T_u16 = D_ONE_CNT_U16;
	}
	else
	{
		EnergyModeState_Cnt_T_u16 = D_ZERO_CNT_U16;
	}
	
	
	/* REQ: ES050A #432 I : According to FDD faults are determined in 2ms loop; but the reset is done in 100ms loop */
	/* REQ: ES050A #542 I : According to FDD faults are determined in 2ms loop; but the reset is done in 100ms loop */
	if( ResetTC_Cnt_T_lgc == TRUE )
	{
		ResetTC_Cnt_T_u08 = D_ONE_CNT_U8;
		ResetIC_Cnt_T_u08  =D_ONE_CNT_U8;
	}
	else if (ResetIC_Cnt_T_lgc == TRUE)
	{
		ResetTC_Cnt_T_u08 = D_ZERO_CNT_U8;
		ResetIC_Cnt_T_u08 = D_ONE_CNT_U8;
	}
	else
	{
		ResetTC_Cnt_T_u08 = D_ZERO_CNT_U8;
		ResetIC_Cnt_T_u08 = D_ZERO_CNT_U8;
	}
	
	DigMSB_AsyncConfigGrpDie1_Cnt_M_u16[0] = ((D_ASYNCCONFIGGRPWRD0_CNT_U16 )) |
								((uint16)ResetTC_Cnt_T_u08 << 3U) |
								(((uint16)k_Die1RPMMode_Cnt_u08) << 2U) |
								(EnergyModeState_Cnt_T_u16 << 1U) |
								(uint16)ResetIC_Cnt_T_u08;
	
	DigMSB_AsyncConfigGrpDie2_Cnt_M_u16[0] = ((D_ASYNCCONFIGGRPWRD0_CNT_U16)) |
								((uint16)ResetTC_Cnt_T_u08 << 3U) |
								(((uint16)k_Die2RPMMode_Cnt_u08) << 2U) |
								(EnergyModeState_Cnt_T_u16 << 1U) |
								(uint16)ResetIC_Cnt_T_u08;	
	MSB1SetConfig(DigMSB_AsyncConfigGrpDie1_Cnt_M_u16); /* REQ: ES050A #416 I : The actual function is implemented in SpiNxt component */
	MSB2SetConfig(DigMSB_AsyncConfigGrpDie2_Cnt_M_u16); /* REQ: ES050A #416 I : The actual function is implemented in SpiNxt component */
	/* ENDREQ: ES050A #432 */  /* ENDREQ: ES050A #542 */
	
	DigMSB_EnableAsyncConfigGrp_Cnt_M_lgc = TRUE;
	/* ENDREQ: ES050A #621 */  /* ENDREQ: ES050A #622 */
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_SA_DIGMSB_APPL_CODE
#include "MemMap.h"  /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/******************************************************
Function: DigMSB_Per1
Trigger 50us - MtrCtrl ISR
Output: MechMtrPos1UnCorr
		MechMtrPos1UnCorrTimeStamp
Functionality: Main 50us processing
******************************************************/
FUNC(void, SA_DIGMSB_CODE) DigMSB_Per1(void)
{
	
	VAR(uint32,  AUTOMATIC) SampleTime1_uSec_T_u32;
	VAR(uint16,  AUTOMATIC) MSB1RxData_Cnt_T_u16[3];
	VAR(uint8,   AUTOMATIC) Die1Rx2Parity_Cnt_T_u08;
	VAR(uint8,   AUTOMATIC) Die1UnderVoltgFault_Cnt_T_u08;
	VAR(uint16,  AUTOMATIC) MSB2RxData_Cnt_T_u16[3];
	VAR(uint16,  AUTOMATIC) MechMtrPos1UnCorrec_Rev_T_u0p16;
	VAR(sint8,  AUTOMATIC) MtrPosPolarity_Cnt_T_s08;
	/* Inputs */
	VAR(uint16, AUTOMATIC) CorrectedElecMtrPos_Rev_T_u0p16;
    VAR(uint16, AUTOMATIC) MechMtrPosLookup_Cnt_T_u16;
    VAR(sint16, AUTOMATIC) HarmonicCompensation_Rev_T_sm1p16;
    VAR(sint16, AUTOMATIC) HarmonicCompensation_Rev_T_s2p13;
    /* Outputs */
    VAR(uint16, AUTOMATIC) MechMtrPos1_Rev_T_u0p16;
	VAR(sint32, AUTOMATIC) DiffMechMtrPos_Rev_T_s15p16;
	
	
	DigMSB_Read_MtrPosPolarity_Cnt_s08(&MtrPosPolarity_Cnt_T_s08); /* REQ: ES050A #624 I */
	GetSystemTime_uS_u32(&SampleTime1_uSec_T_u32); /* REQ: ES050A #537 I */  /* REQ: ES050A #538 I */
		
	/* Rx Data */
	/**** Address of Start of Array is passed inside the macro ****/
	/**** QAC-MISRA Warning for uninitialized objects since QAC did not recognize the function ****/
	/* REQ: ES050A #543 I */  /* REQ: ES050A #618 I */	/* REQ: ES050A #597 I */ 
	MSB1GetData(MSB1RxData_Cnt_T_u16);  /* REQ: ES050A #416 I : The actual function is implemented in SpiNxt component */
	MSB2GetData(MSB2RxData_Cnt_T_u16); /* REQ: ES050A #416 I : The actual function is implemented in SpiNxt component */
	/* ENDREQ: ES050A #543 */  /* ENDREQ: ES050A #618 */  /* ENDREQ: ES050A #597 */   
	
	if (DigMSB_EnableAsyncConfigGrp_Cnt_M_lgc == TRUE)
	{
		MSB1EnableConfigTransfer(); /* REQ: ES050A #416 I : The actual function is implemented in SpiNxt component */
		MSB2EnableConfigTransfer(); /* REQ: ES050A #416 I : The actual function is implemented in SpiNxt component */
		DigMSB_EnableAsyncConfigGrp_Cnt_M_lgc = FALSE;
	}
	
	/*Process the SPI received data
	Rx Buffer contains 3 messages
	Rx Buffer Message order depends the Transmit Buffer Messages
	Message at array position  "0" is used for Error Register Processing
	Message at array position  "1" is used for Rev Centre Processing
	Message at array position  "2" is used for Motor Position Processing  	  */
	
	
	MechMtrPos1UnCorrec_Rev_T_u0p16 = MtrPosProcessing(MSB1RxData_Cnt_T_u16[2], &Die1Rx2Parity_Cnt_T_u08, &Die1UnderVoltgFault_Cnt_T_u08); /* REQ: ES050A #543 I */ /* REQ: ES050A #597 I */ /* REQ: ES050A #526 I */
	
	/* REQ: ES050A #533 I */
	if ( (Die1Rx2Parity_Cnt_T_u08 + Die1UnderVoltgFault_Cnt_T_u08) == D_ZERO_CNT_U8 ) 
		{   /*** p13 output converted to p16 for mathematical calculation purposes ***/
			DigMSB_MechMtrPos1UnCorrec_Rev_M_u0p16 = MechMtrPos1UnCorrec_Rev_T_u0p16; /* REQ: ES050A #653 I */
		}
	else
		{
			DigMSB_RxMtrPos1ParityAccum_Cnt_M_u16 = DigMSB_RxMtrPos1ParityAccum_Cnt_M_u16 + (uint16)Die1Rx2Parity_Cnt_T_u08;
			DigMSB_Die1UnderVoltgFltAccum_Cnt_M_u16 = DigMSB_Die1UnderVoltgFltAccum_Cnt_M_u16 + (uint16)Die1UnderVoltgFault_Cnt_T_u08;
	
		}
		
	
	/*** MtrPos1_SignalProcessing ***/
	/*** Look up table index range from 0 - 1024.
         If the polarity is negative , we will be calculating the equivalent positive angle***/ 	
	MechMtrPosLookup_Cnt_T_u16 =  ((DigMSB_MechMtrPos1UnCorrec_Rev_M_u0p16 >> 6u) & 0x3FFu);

	/* REQ: ES050A #620 I */ /* REQ: ES050A #596 I */ /* REQ: ES050A #594 I : Actual function is implemented inside the CMS (Common Manufacturing Service) component */
    HarmonicCompensation_Rev_T_s2p13 = Rte_Pim_DigMSBEOLData()->MtrPos1HarCompTbl_Rev_s2p13[MechMtrPosLookup_Cnt_T_u16]; 
	
	HarmonicCompensation_Rev_T_sm1p16 = FPM_Fix_m(HarmonicCompensation_Rev_T_s2p13 ,s2p13_T, sm1p16_T);
	
	/* REQ: ES050A #648 I */
    MechMtrPos1_Rev_T_u0p16 = (DigMSB_MechMtrPos1UnCorrec_Rev_M_u0p16 - (uint16)HarmonicCompensation_Rev_T_sm1p16) & D_MASK16BITS_CNT_U16;

	/* REQ: ES050A #590 I */
	if( MtrPosPolarity_Cnt_T_s08 == D_NEGONE_CNT_S32)
	{
		MechMtrPos1_Rev_T_u0p16 = 65535U - MechMtrPos1_Rev_T_u0p16;
	}
	/* ENDREQ: ES050A #648 */ /* ENDREQ: ES050A #533 */ /* ENDREQ: ES050A #590 */
	
	
    /* Rollover is expected and desired */
	/* REQ: ES050A #645 I */ /* REQ: ES050A #596 I */ /* REQ: ES050A #534 I */ /* REQ: ES050A #620 I */
	/* REQ: ES050A #594 I : Actual function is implemented inside the CMS (Common Manufacturing Service) component */
    CorrectedElecMtrPos_Rev_T_u0p16 = (uint16)((3U * MechMtrPos1_Rev_T_u0p16) - Rte_Pim_DigMSBEOLData()->MtrPosBEMF_Rev_u0p16) & D_MASK16BITS_CNT_U16;  

	DiffMechMtrPos_Rev_T_s15p16= (((sint32)MechMtrPos1_Rev_T_u0p16 - (sint32)DigMSB_PrevMechMtrPos1_Rev_M_u0p16));
	
	if (DiffMechMtrPos_Rev_T_s15p16 > 32768)
	{
		DiffMechMtrPos_Rev_T_s15p16  =  DiffMechMtrPos_Rev_T_s15p16 - 65536;
	}
	else if (DiffMechMtrPos_Rev_T_s15p16 < -32768 )
	{
	    DiffMechMtrPos_Rev_T_s15p16  =  DiffMechMtrPos_Rev_T_s15p16 + 65536;
	}
	else
	{ 
	    /*** Do nothing***/	
	}
	
	DigMSB_CumMtrPos1MRF_Rev_M_s15p16 += DiffMechMtrPos_Rev_T_s15p16; /* REQ: ES050A #439 I */
	DigMSB_PrevMechMtrPos1_Rev_M_u0p16 =  MechMtrPos1_Rev_T_u0p16;
	
	
	DigMSB_Write_UncorrMechMtrPos1_Rev_u0p16(DigMSB_MechMtrPos1UnCorrec_Rev_M_u0p16); /* REQ: ES050A #543 I */ /* REQ: ES050A #653 I */
	DigMSB_Write_CumMechMtrPos_Rev_s15p16(DigMSB_CumMtrPos1MRF_Rev_M_s15p16); /* REQ: ES050A #439 I */
	DigMSB_Write_MechMtrPos1_Rev_u0p16(MechMtrPos1_Rev_T_u0p16); /* REQ: ES050A #648 I */
	DigMSB_Write_SysCMechMtrPos1_Rev_u0p16(MechMtrPos1_Rev_T_u0p16); /* REQ: ES050A #647 I */
	DigMSB_Write_CorrectedElecMtrPos_Rev_u0p16(CorrectedElecMtrPos_Rev_T_u0p16); /* REQ: ES050A #645 I */ /* REQ: ES050A #534 I */
	DigMSB_Write_SysCorrectedElecMtrPos_Rev_u0p16(CorrectedElecMtrPos_Rev_T_u0p16); /* REQ: ES050A #644 I */
	DigMSB_Write_MechMtrPos1TimeStamp_uSec_u32(SampleTime1_uSec_T_u32); /* REQ: ES050A #537 I */
	DigMSB_Write_MechMtrPos2TimeStamp_uSec_u32(SampleTime1_uSec_T_u32); /* REQ: ES050A #538 I */ /* REQ: ES050A #642 I */
	DigMSB_Write_RxMtrPos1ParityAccum_Cnt_u16(DigMSB_RxMtrPos1ParityAccum_Cnt_M_u16);
	DigMSB_Write_RxMtrPos1UnderVoltgFltAccum_Cnt_u16(DigMSB_Die1UnderVoltgFltAccum_Cnt_M_u16);
	
	/* REQ: ES050A #543 I */
	DigMSB_Write_Die1RxError_Cnt_u16((MSB1RxData_Cnt_T_u16[0]));  
	DigMSB_Write_Die1RxRevCtr_Cnt_u16((MSB1RxData_Cnt_T_u16[1]));
	DigMSB_Write_Die1RxMtrPos_Cnt_u16((MSB1RxData_Cnt_T_u16[2]));
	DigMSB_Write_Die2RxError_Cnt_u16((MSB2RxData_Cnt_T_u16[0]));  
	DigMSB_Write_Die2RxRevCtr_Cnt_u16((MSB2RxData_Cnt_T_u16[1]));
	DigMSB_Write_Die2RxMtrPos_Cnt_u16((MSB2RxData_Cnt_T_u16[2]));
	/* ENDREQ: ES050A #543 */
	
}

/******************************************************
Function: ErrorRegisterProcessing
Input :  Rx Motor Position
Output: DiexErrorFlag and Parity
Functionality: Process the error register data from SPI
******************************************************/
STATIC INLINE FUNC(uint8, SA_DIGMSB_CODE) ErrorRegisterProcessing( VAR(uint16, AUTOMATIC) RxData_Cnt_T_u16,
																   P2VAR(uint8, AUTOMATIC, AUTOMATIC) DiexRx0Parity_Cnt_T_u08 )
{
	VAR(uint8, AUTOMATIC) DiexErrorReg_Cnt_T_u08;

	*DiexRx0Parity_Cnt_T_u08 = ParityCalculation_m(RxData_Cnt_T_u16);
	DiexErrorReg_Cnt_T_u08 = (uint8)((RxData_Cnt_T_u16 >> 1u) & 0x1Fu);

	return(DiexErrorReg_Cnt_T_u08);
}

/******************************************************
Function: RevCntrProcessing
Input :  Rx Motor Position , Offset
Output: Rev Center and Parity
Functionality:  Process  the Motor Position from the SPI data
******************************************************/
STATIC INLINE FUNC(sint16, SA_DIGMSB_CODE) RevCntrProcessing( VAR(uint16, AUTOMATIC) RxData_Cnt_T_u16,
															  P2VAR(uint8, AUTOMATIC, AUTOMATIC) DiexRx1Parity_Cnt_T_u08 )
{
	
	VAR(sint16, AUTOMATIC) DiexRevCntr_Cnt_T_s16;
	/* Odd parity calculation */
	*DiexRx1Parity_Cnt_T_u08 = ParityCalculation_m( RxData_Cnt_T_u16);
	DiexRevCntr_Cnt_T_s16 = (sint16)(((RxData_Cnt_T_u16>>1u) & 0x3FFu));
	if (DiexRevCntr_Cnt_T_s16 > 511)
		{
			DiexRevCntr_Cnt_T_s16 = DiexRevCntr_Cnt_T_s16 - 1024;
		}
	
	return(DiexRevCntr_Cnt_T_s16);
}

/******************************************************
Function:MtrPosProcessing
Input :  Rx Motor Position , Offset 
Output: Motor Position, Parity and under voltage fault
Functionality:  Process the Motor Position from the SPI
******************************************************/
STATIC INLINE FUNC(uint16, SA_DIGMSB_CODE) MtrPosProcessing( VAR(uint16, AUTOMATIC) RxData_Cnt_T_u16,
															 P2VAR(uint8, AUTOMATIC, AUTOMATIC) DiexRx2Parity_Cnt_T_u08,
															 P2VAR(uint8, AUTOMATIC, AUTOMATIC) DiexUnderVoltgFault_Cnt_T_u08 )
{
	VAR(uint16, AUTOMATIC) MechMtrPos_Rev_T_u0p16;
	VAR(uint16, AUTOMATIC) MechMtrPos_Rev_T_u3p13;

	*DiexRx2Parity_Cnt_T_u08 = ParityCalculation_m( RxData_Cnt_T_u16);
	MechMtrPos_Rev_T_u3p13 = (uint16)((RxData_Cnt_T_u16 >> 1u) & 0x1FFFu);
	MechMtrPos_Rev_T_u0p16 = FPM_Fix_m(MechMtrPos_Rev_T_u3p13, u3p13_T, u0p16_T);
	
	/* Reading the under voltage fault at the appropriate bit position */
	if( (RxData_Cnt_T_u16 & 0x4000U) > D_ZERO_CNT_U16 )
	{
		*DiexUnderVoltgFault_Cnt_T_u08 = D_ONE_CNT_U8;
	}
	else
	{
		*DiexUnderVoltgFault_Cnt_T_u08 = D_ZERO_CNT_U8;
	}

	return(MechMtrPos_Rev_T_u0p16);
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
