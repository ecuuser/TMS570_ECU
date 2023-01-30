/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_AstLmt.c
 *     Workspace:  C:/SynergyWorkspace/WorkingProjects/AstLmt_CM-gzkys7/AstLmt_CM/autosar
 *     SW-C Type:  Ap_AstLmt
 *  Generated at:  Mon Aug 25 22:45:33 2014
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_AstLmt>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Thu Aug  2 11:00:00 2012
 * %version:          9 %
 * %derived_by:       gzkys7 %
 * %date_modified:    Mon Nov 25 09:44:26 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                           SCR #
 * --------  -------  --------  ---------------------------------------------------------------------------  ----------
 * 08/07/12  1        OT        Initial Version (SF-04B v001)                                                5940
 * 08/16/12  2        OT        Added ManualTrqCmd service            
 * 09/11/12	 3		  SAH		Replaced HwTrq Polarity with AssistAssembly Polarity
 * 30/11/12	 4		  Selva		Removed Inputs: MRFMtrVel, AssistAssembly_Polarity, Assist_PowerLimit
								Removed Output: PostLimit_ForAssistSumCC
								Renamed Output: PreLimit_for_Power to SumLimTrqCmd_MtrNm
								Removed calibration: k_OvrSpdMtrTrq2QLmt_MtrNm
 * 01/14/13  5		  SAH		Updated limit on sumlimtrqcmd output
 * 06/03/13	 6        VK		Added Scom calls to set and read steering assist status						  8312
 * 11/23/13	 7        Selva		Updated FDD v4 -Added output TrqLimitMin 						              10951
 * 06/12/14  8        VT        Updated to SF-04B v5, modified PreLimitForStall, AssistCmd, AbsLimitedTorque  12083
 * 25/08/14	 9		  SB		Updated to SF-04B version 006, added input TSMitCommand						  12370
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

#include "Rte_Ap_AstLmt.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_AstLmt_Cfg.h"


#include "GlobalMacro.h"
#include "CalConstants.h"
#include <float.h>

/* MISRA-C:2004 Rule 19.1: Deviation required for the AUTOSAR Compliance */
#define ASTLMT_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, AP_ASTLMT_VAR) AstLmt_ManualTrqCmd_MtrNm_M_f32;
#define ASTLMT_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define ASTLMT_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_ASTLMT_VAR) AstLmt_ManualTrqCmdEn_Cnt_M_lgc;
STATIC VAR(boolean, AP_ASTLMT_VAR) AstLmt_SteeringAsstDefeat_Cnt_M_lgc;
#define ASTLMT_STOP_SEC_VAR_CLEARED_BOOLEAN
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
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * NvM_RequestResultType: Enumeration of integer in interval [0...5] with enumerators
 *   NVM_REQ_OK (0u)
 *   NVM_REQ_NOT_OK (1u)
 *   NVM_REQ_PENDING (2u)
 *   NVM_REQ_INTEGRITY_FAILED (3u)
 *   NVM_REQ_BLOCK_SKIPPED (4u)
 *   NVM_REQ_NV_INVALIDATED (5u)
 *
 * Array Types:
 * ============
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
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   Boolean *Rte_Pim_SteerAsstDefeat(void)
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_ASTLMT_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AstLmt_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ASTLMT_APPL_CODE) AstLmt_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AstLmt_Init
 *********************************************************************************************************************/

	AstLmt_SteeringAsstDefeat_Cnt_M_lgc = *Rte_Pim_SteerAsstDefeat();
 

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AstLmt_Per1
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
 *   Float Rte_IRead_AstLmt_Per1_AssistCmd_MtrNm_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_AssistEOTDamping_MtrNm_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_AssistEOTGain_Uls_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_AssistEOTLimit_MtrNm_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_AssistStallLimit_MtrNm_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_AssistVehSpdLimit_MtrNm_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_CombinedDamping_MtrNm_f32(void)
 *   Boolean Rte_IRead_AstLmt_Per1_DefeatLimitService_Cnt_lgc(void)
 *   Float Rte_IRead_AstLmt_Per1_LimitedReturn_MtrNm_f32(void)
 *   Boolean Rte_IRead_AstLmt_Per1_LrnPnCtrCCDisable_Cnt_lgc(void)
 *   Boolean Rte_IRead_AstLmt_Per1_LrnPnCtrEnable_Cnt_lgc(void)
 *   Float Rte_IRead_AstLmt_Per1_LrnPnCtrTCmd_MtrNm_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_OpTrqOvr_MtrNm_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_OutputRampMult_Uls_f32(void)
 *   Boolean Rte_IRead_AstLmt_Per1_PosServCCDisable_Cnt_lgc(void)
 *   Float Rte_IRead_AstLmt_Per1_PowerLimitPerc_Uls_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_PrkAssistCmd_MtrNm_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_PullCompCmd_MtrNm_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_TSMitCommand_MtrNm_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_ThermalLimitPerc_Uls_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_ThermalLimit_MtrNm_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_VehSpd_Kph_f32(void)
 *   Float Rte_IRead_AstLmt_Per1_WheelImbalanceCmd_MtrNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_AstLmt_Per1_LimitPercentFiltered_Uls_f32(Float data)
 *   Float *Rte_IWriteRef_AstLmt_Per1_LimitPercentFiltered_Uls_f32(void)
 *   void Rte_IWrite_AstLmt_Per1_PreLimitForStall_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_AstLmt_Per1_PreLimitForStall_MtrNm_f32(void)
 *   void Rte_IWrite_AstLmt_Per1_PreLimitTorque_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_AstLmt_Per1_PreLimitTorque_MtrNm_f32(void)
 *   void Rte_IWrite_AstLmt_Per1_SumLimTrqCmd_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_AstLmt_Per1_SumLimTrqCmd_MtrNm_f32(void)
 *   void Rte_IWrite_AstLmt_Per1_TrqLimitMin_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_AstLmt_Per1_TrqLimitMin_MtrNm_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ASTLMT_APPL_CODE) AstLmt_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AstLmt_Per1
 *********************************************************************************************************************/
	
	
	VAR(float32, AUTOMATIC) AssistCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) AssistEOTDamping_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) AssistEOTGain_Uls_T_f32;
	VAR(float32, AUTOMATIC) AssistEOTLimit_MtrNm_T_f32;

	VAR(float32, AUTOMATIC) AssistStallLimit_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) AssistVehSpdLimit_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) CombinedDamping_MtrNm_T_f32;
	VAR(boolean, AUTOMATIC) DefeatLimitService_Cnt_T_lgc;
	
	VAR(float32, AUTOMATIC) LimitedReturn_MtrNm_T_f32;
	VAR(boolean, AUTOMATIC) LrnPnCtrCCDisable_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) LrnPnCtrEnable_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) LrnPnCtrTCmd_MtrNm_T_f32;
	
	VAR(float32, AUTOMATIC) OpTrqOvr_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) OutputRampMult_Uls_T_f32;
	VAR(boolean, AUTOMATIC) PosServCCDisable_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) PowerLimitPerc_Uls_T_f32;
	VAR(float32, AUTOMATIC) PrkAssistCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) PullCompCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) ThermalLimitPerc_Uls_T_f32;
	VAR(float32, AUTOMATIC) ThermalLimit_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(float32, AUTOMATIC) WheelImbalanceCmd_MtrNm_T_f32;
	
	VAR(float32, AUTOMATIC) PreLimitTorque_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) AbsPreLimitTorque_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) SignPreLimitTorque_Cnt_T_f32;
	VAR(float32, AUTOMATIC) PreLimitForStall_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) AbsLimitedTorque_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) SumLimTrqCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) LimitPercentFiltered_Uls_T_f32;
	VAR(float32, AUTOMATIC)  TrqLimitMin_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) AbsAssistCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) TSMitCommand_MtrNm_T_f32;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_AstLmt_Per1_CP0_CheckpointReached();
	AssistCmd_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_AssistCmd_MtrNm_f32();
	AssistEOTDamping_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_AssistEOTDamping_MtrNm_f32();
	AssistEOTGain_Uls_T_f32 = Rte_IRead_AstLmt_Per1_AssistEOTGain_Uls_f32();
	AssistEOTLimit_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_AssistEOTLimit_MtrNm_f32();

	AssistStallLimit_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_AssistStallLimit_MtrNm_f32();
	AssistVehSpdLimit_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_AssistVehSpdLimit_MtrNm_f32();
	CombinedDamping_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_CombinedDamping_MtrNm_f32();
	DefeatLimitService_Cnt_T_lgc = Rte_IRead_AstLmt_Per1_DefeatLimitService_Cnt_lgc();
	
	LimitedReturn_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_LimitedReturn_MtrNm_f32();
	LrnPnCtrCCDisable_Cnt_T_lgc = Rte_IRead_AstLmt_Per1_LrnPnCtrCCDisable_Cnt_lgc();
	LrnPnCtrEnable_Cnt_T_lgc = Rte_IRead_AstLmt_Per1_LrnPnCtrEnable_Cnt_lgc();
	LrnPnCtrTCmd_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_LrnPnCtrTCmd_MtrNm_f32();

	OpTrqOvr_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_OpTrqOvr_MtrNm_f32();
	OutputRampMult_Uls_T_f32 = Rte_IRead_AstLmt_Per1_OutputRampMult_Uls_f32();
	PosServCCDisable_Cnt_T_lgc = Rte_IRead_AstLmt_Per1_PosServCCDisable_Cnt_lgc();
	PowerLimitPerc_Uls_T_f32 = Rte_IRead_AstLmt_Per1_PowerLimitPerc_Uls_f32();
	PrkAssistCmd_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_PrkAssistCmd_MtrNm_f32();
	PullCompCmd_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_PullCompCmd_MtrNm_f32();
	ThermalLimitPerc_Uls_T_f32 = Rte_IRead_AstLmt_Per1_ThermalLimitPerc_Uls_f32();
	ThermalLimit_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_ThermalLimit_MtrNm_f32();
	VehSpd_Kph_T_f32=Rte_IRead_AstLmt_Per1_VehSpd_Kph_f32();
	WheelImbalanceCmd_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_WheelImbalanceCmd_MtrNm_f32();
	TSMitCommand_MtrNm_T_f32 = Rte_IRead_AstLmt_Per1_TSMitCommand_MtrNm_f32();
	
	
	
	/*** Preconditioning ***/
	
	if( PosServCCDisable_Cnt_T_lgc == TRUE )
	{
		PrkAssistCmd_MtrNm_T_f32 = D_ZERO_ULS_F32;
	}
	
	if( LrnPnCtrCCDisable_Cnt_T_lgc == TRUE )
	{
		LrnPnCtrTCmd_MtrNm_T_f32 = D_ZERO_ULS_F32;
	}
	
	PullCompCmd_MtrNm_T_f32 = Limit_m(PullCompCmd_MtrNm_T_f32, -k_SumLimPlCmpLimit_MtrNm_f32, k_SumLimPlCmpLimit_MtrNm_f32);
	
	
	
	/*** Command Summation ***/
	
    if( (AstLmt_ManualTrqCmdEn_Cnt_M_lgc == TRUE) && (VehSpd_Kph_T_f32 < FLT_EPSILON) )
	{
		PreLimitTorque_MtrNm_T_f32 = AstLmt_ManualTrqCmd_MtrNm_M_f32;
	}
	else if( LrnPnCtrEnable_Cnt_T_lgc == TRUE )
	{
		PreLimitTorque_MtrNm_T_f32 = LrnPnCtrTCmd_MtrNm_T_f32;
	}
	else if (AstLmt_SteeringAsstDefeat_Cnt_M_lgc == TRUE)
	{
		PreLimitTorque_MtrNm_T_f32 = D_ZERO_ULS_F32;
	}
	else
	{
		PreLimitTorque_MtrNm_T_f32 = (AssistCmd_MtrNm_T_f32 * AssistEOTGain_Uls_T_f32) +
									 (-LimitedReturn_MtrNm_T_f32) +
									 (-CombinedDamping_MtrNm_T_f32) +
									 PullCompCmd_MtrNm_T_f32 +
									 OpTrqOvr_MtrNm_T_f32 +
									 PrkAssistCmd_MtrNm_T_f32 +
									 WheelImbalanceCmd_MtrNm_T_f32 +
									 (-AssistEOTDamping_MtrNm_T_f32)+ 
									 TSMitCommand_MtrNm_T_f32;
	}
	
	
	
	/*** Apply Gain and Limit ***/
	
	AbsAssistCmd_MtrNm_T_f32 = Abs_f32_m(AssistCmd_MtrNm_T_f32);
	SignPreLimitTorque_Cnt_T_f32 = (float32)Sign_f32_m(PreLimitTorque_MtrNm_T_f32);
	AbsPreLimitTorque_MtrNm_T_f32 = Abs_f32_m(PreLimitTorque_MtrNm_T_f32);
	
	PreLimitForStall_MtrNm_T_f32 = Max_m(AbsPreLimitTorque_MtrNm_T_f32, AbsAssistCmd_MtrNm_T_f32);	

	/****Calculation of the TrqLimit Minimum ****/
	TrqLimitMin_MtrNm_T_f32 = Min_m(AssistEOTLimit_MtrNm_T_f32,AssistVehSpdLimit_MtrNm_T_f32);
	TrqLimitMin_MtrNm_T_f32 = Min_m(AssistStallLimit_MtrNm_T_f32,TrqLimitMin_MtrNm_T_f32);
	TrqLimitMin_MtrNm_T_f32 = Min_m(ThermalLimit_MtrNm_T_f32,TrqLimitMin_MtrNm_T_f32);

	if( DefeatLimitService_Cnt_T_lgc == TRUE )
	{
		AbsLimitedTorque_MtrNm_T_f32 = AbsPreLimitTorque_MtrNm_T_f32;
	}
	else
	{
		AbsLimitedTorque_MtrNm_T_f32 = Min_m(AbsPreLimitTorque_MtrNm_T_f32, TrqLimitMin_MtrNm_T_f32);
	}
	
	SumLimTrqCmd_MtrNm_T_f32 = AbsLimitedTorque_MtrNm_T_f32 * OutputRampMult_Uls_T_f32 * SignPreLimitTorque_Cnt_T_f32;
	
	
	
	/*** Assist Reduction Level ***/
	
	LimitPercentFiltered_Uls_T_f32 = Max_m(ThermalLimitPerc_Uls_T_f32, PowerLimitPerc_Uls_T_f32);
	
	
	
	PreLimitTorque_MtrNm_T_f32 = Limit_m(PreLimitTorque_MtrNm_T_f32, D_MTRTRQCMDLOLMT_MTRNM_F32, D_MTRTRQCMDHILMT_MTRNM_F32);
	PreLimitForStall_MtrNm_T_f32 = Limit_m(PreLimitForStall_MtrNm_T_f32, D_ZERO_ULS_F32, D_MTRTRQCMDHILMT_MTRNM_F32);
	SumLimTrqCmd_MtrNm_T_f32 = Limit_m(SumLimTrqCmd_MtrNm_T_f32, D_MTRTRQCMDLOLMT_MTRNM_F32, D_MTRTRQCMDHILMT_MTRNM_F32);
	TrqLimitMin_MtrNm_T_f32 = Limit_m(TrqLimitMin_MtrNm_T_f32, D_ZERO_ULS_F32, D_MTRTRQCMDHILMT_MTRNM_F32);
	
	LimitPercentFiltered_Uls_T_f32 = Limit_m(LimitPercentFiltered_Uls_T_f32, D_ZERO_ULS_F32, D_ONE_ULS_F32);
	
	Rte_IWrite_AstLmt_Per1_TrqLimitMin_MtrNm_f32(TrqLimitMin_MtrNm_T_f32);
	Rte_IWrite_AstLmt_Per1_LimitPercentFiltered_Uls_f32(LimitPercentFiltered_Uls_T_f32);
	Rte_IWrite_AstLmt_Per1_SumLimTrqCmd_MtrNm_f32(SumLimTrqCmd_MtrNm_T_f32);
	Rte_IWrite_AstLmt_Per1_PreLimitForStall_MtrNm_f32(PreLimitForStall_MtrNm_T_f32);
	Rte_IWrite_AstLmt_Per1_PreLimitTorque_MtrNm_f32(PreLimitTorque_MtrNm_T_f32);
	
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_AstLmt_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AstLmt_Scom_GetSteeringAssistDefeat
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <GetSteeringAssistDefeat> of PortPrototype <AstLmt_Scom>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void AstLmt_Scom_GetSteeringAssistDefeat(Boolean *SteeringAsstDefeat_Cnt_lgc)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ASTLMT_APPL_CODE) AstLmt_Scom_GetSteeringAssistDefeat(P2VAR(Boolean, AUTOMATIC, RTE_AP_ASTLMT_APPL_VAR) SteeringAsstDefeat_Cnt_lgc)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AstLmt_Scom_GetSteeringAssistDefeat
 *********************************************************************************************************************/

	*SteeringAsstDefeat_Cnt_lgc = *Rte_Pim_SteerAsstDefeat();
 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AstLmt_Scom_ManualTrqCmd
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ManualTrqCmd> of PortPrototype <AstLmt_Scom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_VehSpd_Kph_f32(Float *data)
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType AstLmt_Scom_ManualTrqCmd(Boolean EnableManualCtrl, Float MtrTrqCmd_MtrNm_f32)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_AssistLmtFunc_Scom_RTE_E_MtrTrqLmt_SCom_VSTH
 *   RTE_E_AssistLmtFunc_Scom_RTE_E_OK
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_ASTLMT_APPL_CODE) AstLmt_Scom_ManualTrqCmd(Boolean EnableManualCtrl, Float MtrTrqCmd_MtrNm_f32)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AstLmt_Scom_ManualTrqCmd (returns application error)
 *********************************************************************************************************************/
  	
	
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(Std_ReturnType, AUTOMATIC) RetCode;
	
	
	(void)Rte_Read_VehSpd_Kph_f32(&VehSpd_Kph_T_f32);
	
	
	if( TRUE == EnableManualCtrl )
	{
		if( VehSpd_Kph_T_f32 < FLT_EPSILON )
		{
			AstLmt_ManualTrqCmd_MtrNm_M_f32 = MtrTrqCmd_MtrNm_f32;
			AstLmt_ManualTrqCmdEn_Cnt_M_lgc = TRUE;
			RetCode = RTE_E_AssistLmtFunc_Scom_RTE_E_OK;
		}
		else
		{
			RetCode = RTE_E_AssistLmtFunc_Scom_RTE_E_MtrTrqLmt_SCom_VSTH;
		}
	}
	else
	{
		AstLmt_ManualTrqCmdEn_Cnt_M_lgc = FALSE;
		AstLmt_ManualTrqCmd_MtrNm_M_f32 = D_ZERO_ULS_F32;
		RetCode = RTE_E_AssistLmtFunc_Scom_RTE_E_OK;
	}
	
	
	return RetCode;
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: AstLmt_Scom_SetSteeringAssistDefeat
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <SetSteeringAssistDefeat> of PortPrototype <AstLmt_Scom>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_SteeringAsstDefeat_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_SteeringAsstDefeat_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void AstLmt_Scom_SetSteeringAssistDefeat(Boolean SteeringAsstDefeat_Cnt_lgc)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ASTLMT_APPL_CODE) AstLmt_Scom_SetSteeringAssistDefeat(Boolean SteeringAsstDefeat_Cnt_lgc)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: AstLmt_Scom_SetSteeringAssistDefeat
 *********************************************************************************************************************/
	
	*Rte_Pim_SteerAsstDefeat() = SteeringAsstDefeat_Cnt_lgc;
	(void) Rte_Call_SteeringAsstDefeat_WriteBlock(NULL_PTR);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_ASTLMT_APPL_CODE
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
