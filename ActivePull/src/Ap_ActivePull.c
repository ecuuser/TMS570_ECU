/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_ActivePull.c
 *     Workspace:  C:/CMSynergy_Projects/ActivePull/autosar
 *     SW-C Type:  Ap_ActivePull
 *  Generated at:  Sat Oct 20 10:02:16 2012
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_ActivePull>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Tue Aug  2 09:49:53 2011
 * %version:          13 %
 * %derived_by:       gz7pm0 %
 * %date_modified:    Wed Aug  7 16:30:51 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 08/02/11   1       LWW       Initial EA3.0 Design
 * 01/06/12   2       LWW       Added defeat mask defined locally until component implementation is done
 * 04/02/12   3       OT        Implementation of SF-13 rev 001 (started from scratch)                         4801
 * 04/18/12   4       OT        Fixed Reset SCom function to use direct reads instead of buffered reads        4801
 * 04/22/12	  5       VK        Removed PIM from Scom and made LT learned variable to a typH				   5267
 *								Added support for FDAD Common manufacturing srvc DID
 * 06/26/12   6       VK		Updates to meet SF-13 rev 002												   5744
 * 06/26/12   7       VK        Changes to the logic to update decremental integral gain					   5744
 * 07/24/12   8       NRAR      Updated as per Ver 003 and also changed fixed type LPF to floating type        5861
 * 09/16/12   9       BWL       Added watchdog checkpoints.                                                    6211
 * 10/20/12   11      LWW       Changed table datatype to u2p14 for anomaly correction, removed condition
 *                              checks and return value of SCom Reset function
 * 08/07/13	  12	  SP		Anomaly 5379 fix															   9443
 * 04/16/14	  13	  LK		Anomaly 5764 fix (reverted 5379 fix changes made in version 12)				   11759
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_ActivePull.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "Ap_ActivePull_Cfg.h"
#include "CalConstants.h"
#include "GlobalMacro.h"
#include "fixmath.h"
#include "filters.h"
#include "interpolation.h"


/* Embedded Constants */
#define D_MINTOSEC_SECPMIN_F32			60.0f

/* System-defined Embedded Constants */
#define D_STINTSCALER_ULS_F32			 1.35f
#define D_STSAMPLETIME_SEC_F32	 		 0.002f
#define D_LTINTSCALER_ULS_F32	 		 1.35f
#define D_LTSAMPLETIME_SEC_F32	 		 0.1f
#define D_PULLCOMPSAMPLETIME_SEC_F32	 0.002f




#define ACTIVEPULL_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, ACTIVEPULL_VAR) DecGain_Uls_M_f32;
STATIC VAR(float32, ACTIVEPULL_VAR) IncGain_Uls_M_f32;
STATIC VAR(float32, ACTIVEPULL_VAR) LTIntGain_Uls_M_f32;
STATIC VAR(float32, ACTIVEPULL_VAR) LTWindUpLimit_HwNm_M_f32;
STATIC VAR(float32, ACTIVEPULL_VAR) STStepSize_HwNm_M_f32;
STATIC VAR(float32, ACTIVEPULL_VAR) PullCompStepSize_HwNm_M_f32;
STATIC VAR(uint32, ACTIVEPULL_VAR) EnableTime_mS_M_u32;
STATIC VAR(float32, ACTIVEPULL_VAR) STComp_HwNm_M_f32;
STATIC VAR(uint32, ACTIVEPULL_VAR) STOppSignTime_mS_M_u32;
STATIC VAR(float32, ACTIVEPULL_VAR) PullCompCmd_HwNm_M_f32;
STATIC VAR(float32, ACTIVEPULL_VAR) SComLTComp_HwNm_M_f32;
STATIC VAR(float32, ACTIVEPULL_VAR) SComSTComp_HwNm_M_f32;
STATIC volatile VAR(float32, ACTIVEPULL_VAR) HwTrqFilt_HwNm_D_f32;
STATIC volatile VAR(float32, ACTIVEPULL_VAR) YawRateFilt_DegpS_D_f32;
STATIC volatile VAR(float32, ACTIVEPULL_VAR) STError_HwNm_D_f32;
STATIC volatile VAR(float32, ACTIVEPULL_VAR) STIntGain_Uls_D_f32;
STATIC volatile VAR(float32, ACTIVEPULL_VAR) LTError_HwNm_D_f32;

STATIC VAR(float32, ACTIVEPULL_VAR) PrevVehSpd_Kph_M_f32;
STATIC VAR(float32, ACTIVEPULL_VAR) VehSpdRate_KphpS_M_f32;
#define ACTIVEPULL_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define ACTIVEPULL_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, ACTIVEPULL_VAR) PrevSTLearnTimeInc_Sec_M_u12p4;
STATIC VAR(uint16, ACTIVEPULL_VAR) PrevSTLearnTimeDec_Sec_M_u12p4;
STATIC VAR(uint16, ACTIVEPULL_VAR) PrevLTLearnTime_Min_M_u16;
#define ACTIVEPULL_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

#define ACTIVEPULL_START_SEC_VAR_SAVED_ZONEH_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, ACTIVEPULL_VAR) LTComp_HwNm_M_f32;

#define ACTIVEPULL_STOP_SEC_VAR_SAVED_ZONEH_32
#include "MemMap.h" /* PRQA S 5087 */

#define ACTIVEPULL_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, ACTIVEPULL_VAR) ResetPer1_Cnt_M_lgc;
STATIC VAR(boolean, ACTIVEPULL_VAR) ResetPer2_Cnt_M_lgc;
STATIC VAR(boolean, ACTIVEPULL_VAR) ResetPer3_Cnt_M_lgc;
STATIC VAR(boolean, ACTIVEPULL_VAR) SComLTCompSet_Cnt_M_lgc;
STATIC VAR(boolean, ACTIVEPULL_VAR) SComSTCompSet_Cnt_M_lgc;
STATIC VAR(boolean, ACTIVEPULL_VAR) EnableLearn_Cnt_M_lgc;
STATIC volatile VAR(boolean, ACTIVEPULL_VAR) STReset_Cnt_D_lgc;
#define ACTIVEPULL_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define ACTIVEPULL_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(LPF32KSV_Str, AP_ACTIVEPULL_VAR_NOINIT) HwTorqueSV_HwNm_M_Str;
STATIC VAR(LPF32KSV_Str, AP_ACTIVEPULL_VAR_NOINIT) SrlComYawRateSV_DegpS_M_Str;
STATIC VAR(LPF32KSV_Str, AP_ACTIVEPULL_VAR_NOINIT) HwTorqueSTSV_HwNm_M_Str;
STATIC VAR(LPF32KSV_Str, AP_ACTIVEPULL_VAR_NOINIT) HwTorqueLTSV_HwNm_M_Str;
#define ACTIVEPULL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
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
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
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
 * Float: D_180OVRPI_ULS_F32 = 57.295779513082
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_ACTIVEPULL_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ActivePull_Init1
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

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ActivePull_Init1
 *********************************************************************************************************************/

	LTWindUpLimit_HwNm_M_f32 = Min_m(k_TotalLimit_HwNm_f32, k_LTLimit_HwNm_f32);
	STStepSize_HwNm_M_f32 = (D_STSAMPLETIME_SEC_F32 * k_STLimit_HwNm_f32) / k_STRampTime_Sec_f32;
	PullCompStepSize_HwNm_M_f32 = k_OutputMaxRate_HwNmpS_f32 * D_PULLCOMPSAMPLETIME_SEC_F32;
	

	LPF_Init_f32_m(D_ZERO_ULS_F32, k_HwTrqFilt_Hz_f32, D_2MS_SEC_F32, &HwTorqueSV_HwNm_M_Str);
	LPF_Init_f32_m(D_ZERO_ULS_F32, k_YawRateFilt_Hz_f32, D_2MS_SEC_F32, &SrlComYawRateSV_DegpS_M_Str);
	LPF_Init_f32_m(D_ZERO_ULS_F32, k_STFilt_Hz_f32, D_2MS_SEC_F32, &HwTorqueSTSV_HwNm_M_Str);
	LPF_Init_f32_m(D_ZERO_ULS_F32, k_LTFilt_Hz_f32, D_LTSAMPLETIME_SEC_F32, &HwTorqueLTSV_HwNm_M_Str);

	

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ActivePull_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <OFF, DISABLE, WARMINIT>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Boolean Rte_IRead_ActivePull_Per1_DisableLearning_Cnt_lgc(void)
 *   Boolean Rte_IRead_ActivePull_Per1_DisableOutput_Cnt_lgc(void)
 *   Float Rte_IRead_ActivePull_Per1_HandwheelAuthority_Uls_f32(void)
 *   Float Rte_IRead_ActivePull_Per1_HandwheelPosition_HwDeg_f32(void)
 *   Float Rte_IRead_ActivePull_Per1_HandwheelVelocity_HwRadpS_f32(void)
 *   Float Rte_IRead_ActivePull_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_ActivePull_Per1_SrlComYawRate_DegpS_f32(void)
 *   Boolean Rte_IRead_ActivePull_Per1_VehicleSpeedValid_Cnt_lgc(void)
 *   Float Rte_IRead_ActivePull_Per1_VehicleSpeed_Kph_f32(void)
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
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(UInt32 InitialTime, UInt32 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ActivePull_Per1
 *********************************************************************************************************************/
	
	VAR(boolean, AUTOMATIC) DisableLearning_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) DisableOutput_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) HandwheelAuthority_Uls_T_f32;
	VAR(float32, AUTOMATIC) HandwheelPosition_HwDeg_T_f32;
	VAR(float32, AUTOMATIC) HandwheelVelocity_HwRadpS_T_f32;
	VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32;
	VAR(float32, AUTOMATIC) SrlComYawRate_DegpS_T_f32;
	VAR(boolean, AUTOMATIC) VehicleSpeedValid_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;
	
	VAR(float32, AUTOMATIC) LTComp_HwNm_T_f32;
	VAR(float32, AUTOMATIC) PrevSTComp_HwNm_T_f32;
	VAR(boolean, AUTOMATIC) EnableLearning_Cnt_T_lgc;
	
	
	VAR(boolean, AUTOMATIC) ResetSvc_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) HwTrqFilt_HwNm_T_f32;
	VAR(float32, AUTOMATIC) YawRateFilt_DegpS_T_f32;
	
	VAR(float32, AUTOMATIC) HwTorqAbs_HwNm_T_f32;
	VAR(float32, AUTOMATIC) YawRateAbs_DegpS_T_f32;
	VAR(float32, AUTOMATIC) HwPosAbs_HwDeg_T_f32;
	VAR(boolean, AUTOMATIC) STReset_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) HandwheelVelocityAbs_DegpS_T_f32;
	VAR(float32, AUTOMATIC) VehicleSpeedRateAbs_KphpS_T_f32;
	VAR(uint32,  AUTOMATIC) ElapsedTime_mS_T_u32;
	
	VAR(float32, AUTOMATIC) STError_HwNm_T_f32;
	VAR(float32, AUTOMATIC) STIntGain_Uls_T_f32;
	VAR(float32, AUTOMATIC) PosWindUpLimit_HwNm_T_f32;
	VAR(float32, AUTOMATIC) NegWindUpLimit_HwNm_T_f32;
	VAR(float32, AUTOMATIC) STComp_HwNm_T_f32;
	VAR(float32, AUTOMATIC) STErrorTerm_HwNm_T_f32;
	VAR(float32, AUTOMATIC) STCompPrelim_HwNm_T_f32;

	VAR(uint16, AUTOMATIC) STLearnTimeIncCal_Sec_T_u12p4;
	VAR(uint16, AUTOMATIC) STLearnTimeDecCal_Sec_T_u12p4;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_ActivePull_Per1_CP0_CheckpointReached();
	
	
	
	DisableLearning_Cnt_T_lgc = Rte_IRead_ActivePull_Per1_DisableLearning_Cnt_lgc();
	DisableOutput_Cnt_T_lgc = Rte_IRead_ActivePull_Per1_DisableOutput_Cnt_lgc();
	HandwheelAuthority_Uls_T_f32 = Rte_IRead_ActivePull_Per1_HandwheelAuthority_Uls_f32();
	HandwheelPosition_HwDeg_T_f32 = Rte_IRead_ActivePull_Per1_HandwheelPosition_HwDeg_f32();
	HandwheelVelocity_HwRadpS_T_f32 = Rte_IRead_ActivePull_Per1_HandwheelVelocity_HwRadpS_f32();
	HwTorque_HwNm_T_f32 = Rte_IRead_ActivePull_Per1_HwTorque_HwNm_f32();
	SrlComYawRate_DegpS_T_f32 = Rte_IRead_ActivePull_Per1_SrlComYawRate_DegpS_f32();
	VehicleSpeedValid_Cnt_T_lgc = Rte_IRead_ActivePull_Per1_VehicleSpeedValid_Cnt_lgc();
	VehicleSpeed_Kph_T_f32 = Rte_IRead_ActivePull_Per1_VehicleSpeed_Kph_f32();
	
	LTComp_HwNm_T_f32 = LTComp_HwNm_M_f32;
	PrevSTComp_HwNm_T_f32 = STComp_HwNm_M_f32;
	
	
	
	
	/* Check for SCom Functions */
	
	if( ResetPer1_Cnt_M_lgc == TRUE )
	{
		ResetPer1_Cnt_M_lgc = FALSE;
		ResetSvc_Cnt_T_lgc = TRUE;
	}
	else
	{
		ResetSvc_Cnt_T_lgc = FALSE;
	}
	
	if( SComSTCompSet_Cnt_M_lgc == TRUE )
	{
		SComSTCompSet_Cnt_M_lgc = FALSE;
		PrevSTComp_HwNm_T_f32 = SComSTComp_HwNm_M_f32;
	}
	
	
	/* Filter Inputs */
	

	HwTrqFilt_HwNm_T_f32 = LPF_OpUpdate_f32_m(HwTorque_HwNm_T_f32, &HwTorqueSV_HwNm_M_Str);

	
	YawRateFilt_DegpS_T_f32 = LPF_OpUpdate_f32_m(SrlComYawRate_DegpS_T_f32, &SrlComYawRateSV_DegpS_M_Str);
	
	
	/*** Active Compensation Enable ***/
	
	HwTorqAbs_HwNm_T_f32 = Abs_f32_m(HwTrqFilt_HwNm_T_f32);
	YawRateAbs_DegpS_T_f32 = Abs_f32_m(YawRateFilt_DegpS_T_f32);
	HwPosAbs_HwDeg_T_f32 = Abs_f32_m(HandwheelPosition_HwDeg_T_f32);
	
	if( (HwTorqAbs_HwNm_T_f32 >= k_STResetHwTrq_HwNm_f32) ||
		(HwPosAbs_HwDeg_T_f32 >= k_STResetHwPos_HwDeg_f32) ||
		(YawRateAbs_DegpS_T_f32 >= k_STResetYawRate_DegpS_f32) )
	{
		STReset_Cnt_T_lgc = TRUE;
	}
	else
	{
		STReset_Cnt_T_lgc = FALSE;
	}
	
	
	HandwheelVelocityAbs_DegpS_T_f32 = Abs_f32_m(HandwheelVelocity_HwRadpS_T_f32 * D_180OVRPI_ULS_F32);
	VehicleSpeedRateAbs_KphpS_T_f32 = Abs_f32_m(VehSpdRate_KphpS_M_f32);
	
	if( (STReset_Cnt_T_lgc == TRUE) ||
		(HwTorqAbs_HwNm_T_f32 >= k_EnableHwTrqMax_HwNm_f32) ||
		(HwPosAbs_HwDeg_T_f32 >= k_EnableHwPosMax_HwDeg_f32) ||
		(YawRateAbs_DegpS_T_f32 >= k_EnableYawRateMax_DegpS_f32) ||
		(HandwheelAuthority_Uls_T_f32 < k_EnableHwAuthMin_Uls_f32) ||
		(VehicleSpeed_Kph_T_f32 < k_EnableVehSpdMin_Kph_f32) ||
		(VehicleSpeed_Kph_T_f32 >= k_EnableVehSpdMax_Kph_f32) ||
		(VehicleSpeedValid_Cnt_T_lgc == FALSE) ||
		(HandwheelVelocityAbs_DegpS_T_f32 >= k_EnableHwVelMax_DegpS_f32) ||
		(VehicleSpeedRateAbs_KphpS_T_f32 >= k_EnableVehSpdRateMax_KphpS_f32) ||
		(DisableLearning_Cnt_T_lgc == TRUE) ||
		(DisableOutput_Cnt_T_lgc == TRUE) )
	{
		(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&EnableTime_mS_M_u32);
	}
	
	(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(EnableTime_mS_M_u32, &ElapsedTime_mS_T_u32);
	
	if( ElapsedTime_mS_T_u32 >= k_EnableTime_mS_u32 )
	{
		EnableLearning_Cnt_T_lgc = TRUE;
	}
	else
	{
		EnableLearning_Cnt_T_lgc = FALSE;
	}
	
	
	
	/*** Short Term Compensation ***/
	
	/* Short Term Compensation Filter */
	
	STError_HwNm_T_f32 = LPF_OpUpdate_f32_m(HwTorque_HwNm_T_f32, &HwTorqueSTSV_HwNm_M_Str);
	
	if( (Abs_f32_m(STError_HwNm_T_f32) < k_FiltDeadband_HwNm_f32) ||
		(EnableLearning_Cnt_T_lgc == FALSE) ||
		(STReset_Cnt_T_lgc == TRUE) ||
		(ResetSvc_Cnt_T_lgc == TRUE) )
	{
		STError_HwNm_T_f32 = 0.0f;
	}
	
	
	/* Calculate Integrator Gains */
	/* Update the integrator gains when cal value is updated while tuning on the fly */
	STLearnTimeIncCal_Sec_T_u12p4 = FPM_FloatToFixed_m(k_STLearnTimeInc_Sec_f32, u12p4_T);
	STLearnTimeDecCal_Sec_T_u12p4 = FPM_FloatToFixed_m(k_STLearnTimeDec_Sec_f32, u12p4_T);

	if (STLearnTimeIncCal_Sec_T_u12p4 != PrevSTLearnTimeInc_Sec_M_u12p4)
	{
		IncGain_Uls_M_f32 = (D_STINTSCALER_ULS_F32 / k_STLearnTimeInc_Sec_f32) * D_STSAMPLETIME_SEC_F32;
		PrevSTLearnTimeInc_Sec_M_u12p4 = STLearnTimeIncCal_Sec_T_u12p4;
	}

	if (STLearnTimeDecCal_Sec_T_u12p4 != PrevSTLearnTimeDec_Sec_M_u12p4)
	{
		DecGain_Uls_M_f32 = (D_STINTSCALER_ULS_F32 / k_STLearnTimeDec_Sec_f32) * D_STSAMPLETIME_SEC_F32;
		PrevSTLearnTimeDec_Sec_M_u12p4 = STLearnTimeDecCal_Sec_T_u12p4;
	}

	if( Sign_f32_m(HwTorque_HwNm_T_f32) == Sign_f32_m(PrevSTComp_HwNm_T_f32) )
	{
		(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&STOppSignTime_mS_M_u32);
	}
	
	(void)Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(STOppSignTime_mS_M_u32, &ElapsedTime_mS_T_u32);
	
	if( ElapsedTime_mS_T_u32 >= k_STOppSignTime_mS_u32 )
	{
		STIntGain_Uls_T_f32 = DecGain_Uls_M_f32;
	}
	else
	{
		STIntGain_Uls_T_f32 = IncGain_Uls_M_f32;
	}
	
	
	/* Error Integrator & Active Limit */
	
	if( ResetSvc_Cnt_T_lgc == TRUE )
	{
		STComp_HwNm_T_f32 = 0.0f;
	}
	else
	{
		PosWindUpLimit_HwNm_T_f32 = Min_m(k_STLimit_HwNm_f32, k_TotalLimit_HwNm_f32 - LTComp_HwNm_T_f32);
		NegWindUpLimit_HwNm_T_f32 = Max_m(-k_STLimit_HwNm_f32, -k_TotalLimit_HwNm_f32 - LTComp_HwNm_T_f32);
		
		if( STReset_Cnt_T_lgc == TRUE )
		{
			STErrorTerm_HwNm_T_f32 = ((float32) -Sign_f32_m(PrevSTComp_HwNm_T_f32)) * Min_m(STStepSize_HwNm_M_f32, Abs_f32_m(PrevSTComp_HwNm_T_f32));
		}
		else
		{
			STErrorTerm_HwNm_T_f32 = STIntGain_Uls_T_f32 * (Limit_m(STError_HwNm_T_f32, -k_STIntInputLimit_HwNm_f32, k_STIntInputLimit_HwNm_f32));
		}
		
		STCompPrelim_HwNm_T_f32 = STErrorTerm_HwNm_T_f32 + PrevSTComp_HwNm_T_f32;
		
		STComp_HwNm_T_f32 = Limit_m(STCompPrelim_HwNm_T_f32, NegWindUpLimit_HwNm_T_f32, PosWindUpLimit_HwNm_T_f32);
	}
	
	
	
	HwTrqFilt_HwNm_D_f32 = HwTrqFilt_HwNm_T_f32;
	YawRateFilt_DegpS_D_f32 = YawRateFilt_DegpS_T_f32;
	STError_HwNm_D_f32 = STError_HwNm_T_f32;
	STIntGain_Uls_D_f32 = STIntGain_Uls_T_f32;
	STReset_Cnt_D_lgc = STReset_Cnt_T_lgc;
	
	STComp_HwNm_M_f32 = STComp_HwNm_T_f32;
	EnableLearn_Cnt_M_lgc = EnableLearning_Cnt_T_lgc;
	
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_ActivePull_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ActivePull_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <OFF>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Boolean Rte_IRead_ActivePull_Per2_DisableOutput_Cnt_lgc(void)
 *   Float Rte_IRead_ActivePull_Per2_VehicleSpeed_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_ActivePull_Per2_PullCompCmd_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_ActivePull_Per2_PullCompCmd_MtrNm_f32(void)
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

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ActivePull_Per2
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;
	VAR(boolean, AUTOMATIC) ResetSvc_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) DisableOutput_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) STComp_HwNm_T_f32;
	VAR(float32, AUTOMATIC) LTComp_HwNm_T_f32;
	
	VAR(float32, AUTOMATIC) PullCompCmd_HwNm_T_f32;
	VAR(float32, AUTOMATIC) PrevPullCompCmd_HwNm_T_f32;
	VAR(uint16,  AUTOMATIC) VehicleSpeed_Kph_T_u9p7;
	VAR(uint16,  AUTOMATIC) VehSpdScale_Uls_T_u2p14;
	VAR(float32, AUTOMATIC) VehSpdScale_Uls_T_f32;
	
	VAR(float32, AUTOMATIC) PullCompCmd_MtrNm_T_f32;
	
	
	VehicleSpeed_Kph_T_f32 = Rte_IRead_ActivePull_Per2_VehicleSpeed_Kph_f32();
	DisableOutput_Cnt_T_lgc = Rte_IRead_ActivePull_Per2_DisableOutput_Cnt_lgc();
	PrevPullCompCmd_HwNm_T_f32 = PullCompCmd_HwNm_M_f32;
	STComp_HwNm_T_f32 = STComp_HwNm_M_f32;
	LTComp_HwNm_T_f32 = LTComp_HwNm_M_f32;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_ActivePull_Per2_CP0_CheckpointReached();
	
	
	/* Check for Reset */
	
	if( ResetPer2_Cnt_M_lgc == TRUE )
	{
		ResetPer2_Cnt_M_lgc = FALSE;
		ResetSvc_Cnt_T_lgc = TRUE;
	}
	else
	{
		ResetSvc_Cnt_T_lgc = FALSE;
	}
	
	
	
	/*** Calculate Active Compensation ***/
	
	if( (ResetSvc_Cnt_T_lgc == TRUE) ||
		(DisableOutput_Cnt_T_lgc == TRUE) )
	{
		PullCompCmd_HwNm_T_f32 = 0.0f;
	}
	else
	{
		VehicleSpeed_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
		
		VehSpdScale_Uls_T_u2p14 = IntplVarXY_u16_u16Xu16Y_Cnt(t_VehSpdScaleTblX_Kph_u9p7,
															  t_VehSpdScaleTblY_Uls_u2p14,
															  TableSize_m(t_VehSpdScaleTblX_Kph_u9p7),
															  VehicleSpeed_Kph_T_u9p7);
		
		VehSpdScale_Uls_T_f32 = FPM_FixedToFloat_m(VehSpdScale_Uls_T_u2p14, u2p14_T);
		
		PullCompCmd_HwNm_T_f32 = (STComp_HwNm_T_f32 + LTComp_HwNm_T_f32) * VehSpdScale_Uls_T_f32;
	}
	
	PullCompCmd_HwNm_T_f32 = Limit_m(PullCompCmd_HwNm_T_f32,
	                                (PrevPullCompCmd_HwNm_T_f32 - PullCompStepSize_HwNm_M_f32),
	                                (PrevPullCompCmd_HwNm_T_f32 + PullCompStepSize_HwNm_M_f32));
	
	PullCompCmd_MtrNm_T_f32 = PullCompCmd_HwNm_T_f32 * k_HwNmToMtrNm_Uls_f32;
	PullCompCmd_MtrNm_T_f32 = Limit_m(PullCompCmd_MtrNm_T_f32, D_MTRTRQCMDLOLMT_MTRNM_F32, D_MTRTRQCMDHILMT_MTRNM_F32);
	
	
	PullCompCmd_HwNm_M_f32 = PullCompCmd_HwNm_T_f32;
	Rte_IWrite_ActivePull_Per2_PullCompCmd_MtrNm_f32(PullCompCmd_MtrNm_T_f32);
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_ActivePull_Per2_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ActivePull_Per3
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 100ms
 *     and not in Mode(s) <WARMINIT, DISABLE, OFF>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_ActivePull_Per3_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_ActivePull_Per3_VehicleSpeed_Kph_f32(void)
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

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_Per3(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ActivePull_Per3
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32;
	VAR(boolean, AUTOMATIC) EnableLearning_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) ResetSvc_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) STComp_HwNm_T_f32;
	VAR(float32, AUTOMATIC) PrevLTComp_HwNm_T_f32;
	
	VAR(float32, AUTOMATIC) LTError_HwNm_T_f32;
	
	VAR(float32, AUTOMATIC) LTErrorTerm_HwNm_T_f32;
	VAR(float32, AUTOMATIC) LTCompPrelim_HwNm_T_f32;
	VAR(float32, AUTOMATIC) LTComp_HwNm_T_f32;
	VAR(uint16, AUTOMATIC) LTLearnTimeCal_Min_T_u16;

	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	
	VehSpd_Kph_T_f32 = Rte_IRead_ActivePull_Per3_VehicleSpeed_Kph_f32();
	HwTorque_HwNm_T_f32 = Rte_IRead_ActivePull_Per3_HwTorque_HwNm_f32();
	EnableLearning_Cnt_T_lgc = EnableLearn_Cnt_M_lgc;
	STComp_HwNm_T_f32 = STComp_HwNm_M_f32;
	PrevLTComp_HwNm_T_f32 = LTComp_HwNm_M_f32;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_ActivePull_Per3_CP0_CheckpointReached();
	
	
	/* Check for SCom Functions */
	
	if( ResetPer3_Cnt_M_lgc == TRUE )
	{
		ResetPer3_Cnt_M_lgc = FALSE;
		ResetSvc_Cnt_T_lgc = TRUE;
	}
	else
	{
		ResetSvc_Cnt_T_lgc = FALSE;
	}
	
	if( SComLTCompSet_Cnt_M_lgc == TRUE )
	{
		SComLTCompSet_Cnt_M_lgc = FALSE;
		PrevLTComp_HwNm_T_f32 = SComLTComp_HwNm_M_f32;
	}
	
	
	/*** Long Term Compensation ***/
	
	/* Long Term Compensation Filter */
	
	LTError_HwNm_T_f32 = LPF_OpUpdate_f32_m((HwTorque_HwNm_T_f32 + STComp_HwNm_T_f32), &HwTorqueLTSV_HwNm_M_Str);

	
	if( (Abs_f32_m(LTError_HwNm_T_f32) < k_FiltDeadband_HwNm_f32) ||
		(EnableLearning_Cnt_T_lgc == FALSE) ||
		(ResetSvc_Cnt_T_lgc == TRUE) )
	{
		LTError_HwNm_T_f32 = 0.0f;
	}

	/* Update the integrator gains when cal value is updated while tuning on the fly */
	LTLearnTimeCal_Min_T_u16 = (uint16)FPM_FloatToFixed_m(k_LTLearnTime_Min_f32, u16p0_T);
	if (LTLearnTimeCal_Min_T_u16 != PrevLTLearnTime_Min_M_u16)
	{
		LTIntGain_Uls_M_f32 = (D_LTSAMPLETIME_SEC_F32 * D_LTINTSCALER_ULS_F32) / (k_LTLearnTime_Min_f32 * D_MINTOSEC_SECPMIN_F32);
		PrevLTLearnTime_Min_M_u16 = LTLearnTimeCal_Min_T_u16;
	}
	
	/* Error Integrator */
	
	if( ResetSvc_Cnt_T_lgc == TRUE )
	{
		LTComp_HwNm_T_f32 = 0.0f;
	}
	else
	{
		LTErrorTerm_HwNm_T_f32 = Limit_m(LTError_HwNm_T_f32, -k_LTIntInputLimit_HwNm_f32, k_LTIntInputLimit_HwNm_f32);
		
		LTCompPrelim_HwNm_T_f32 = (LTIntGain_Uls_M_f32 * LTErrorTerm_HwNm_T_f32) + PrevLTComp_HwNm_T_f32;
		
		LTComp_HwNm_T_f32 = Limit_m(LTCompPrelim_HwNm_T_f32, -LTWindUpLimit_HwNm_M_f32, LTWindUpLimit_HwNm_M_f32);
	}
	
	/*Vehicle Speed Rate */
	VehSpdRate_KphpS_M_f32 = (VehSpd_Kph_T_f32 - PrevVehSpd_Kph_M_f32) / D_LTSAMPLETIME_SEC_F32;
	PrevVehSpd_Kph_M_f32 = VehSpd_Kph_T_f32;
	


	LTError_HwNm_D_f32 = LTError_HwNm_T_f32;
	LTComp_HwNm_M_f32 = LTComp_HwNm_T_f32;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_ActivePull_Per3_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ActivePull_SCom_ReadParam
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadParam> of PortPrototype <ActivePull_SCom>
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
 *   void ActivePull_SCom_ReadParam(Float *PullCompCmd_HwNm_f32, Float *STComp_HwNm_f32, Float *LTComp_HwNm_f32, Boolean *EnableLearn_Cnt_lgc)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_SCom_ReadParam(P2VAR(Float, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) PullCompCmd_HwNm_f32, P2VAR(Float, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) STComp_HwNm_f32, P2VAR(Float, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) LTComp_HwNm_f32, P2VAR(Boolean, AUTOMATIC, RTE_AP_ACTIVEPULL_APPL_VAR) EnableLearn_Cnt_lgc)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ActivePull_SCom_ReadParam
 *********************************************************************************************************************/

*PullCompCmd_HwNm_f32 = PullCompCmd_HwNm_M_f32;
*STComp_HwNm_f32 = STComp_HwNm_M_f32;
*LTComp_HwNm_f32 = LTComp_HwNm_M_f32;
*EnableLearn_Cnt_lgc = EnableLearn_Cnt_M_lgc;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ActivePull_SCom_Reset
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Reset> of PortPrototype <ActivePull_SCom>
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
 *   void ActivePull_SCom_Reset(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_SCom_Reset(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ActivePull_SCom_Reset
 *********************************************************************************************************************/
	
		ResetPer1_Cnt_M_lgc = TRUE;
		ResetPer2_Cnt_M_lgc = TRUE;
		ResetPer3_Cnt_M_lgc = TRUE;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ActivePull_SCom_SetLTComp
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <SetLTComp> of PortPrototype <ActivePull_SCom>
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
 *   void ActivePull_SCom_SetLTComp(Float LTComp_HwNm_f32)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_SCom_SetLTComp(Float LTComp_HwNm_f32)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ActivePull_SCom_SetLTComp
 *********************************************************************************************************************/
	
	SComLTComp_HwNm_M_f32 = LTComp_HwNm_f32;
	SComLTCompSet_Cnt_M_lgc = TRUE;

	LTComp_HwNm_M_f32 = LTComp_HwNm_f32;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ActivePull_SCom_SetSTComp
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <SetSTComp> of PortPrototype <ActivePull_SCom>
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
 *   void ActivePull_SCom_SetSTComp(Float STComp_HwNm_f32)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_SCom_SetSTComp(Float STComp_HwNm_f32)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ActivePull_SCom_SetSTComp
 *********************************************************************************************************************/
	
	
	SComSTComp_HwNm_M_f32 = STComp_HwNm_f32;
	SComSTCompSet_Cnt_M_lgc = TRUE;
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ActivePull_Trns1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on entering of Mode <OPERATE> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
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

FUNC(void, RTE_AP_ACTIVEPULL_APPL_CODE) ActivePull_Trns1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ActivePull_Trns1
 *********************************************************************************************************************/
	
	(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&EnableTime_mS_M_u32);
	(void)Rte_Call_SystemTime_GetSystemTime_mS_u32(&STOppSignTime_mS_M_u32);
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_ACTIVEPULL_APPL_CODE
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
