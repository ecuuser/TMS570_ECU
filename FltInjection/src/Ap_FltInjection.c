/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_FltInjection.c
 *     Workspace:  C:/Documents and Settings/nzx5jd/Desktop/FltInjection/autosar/Ap_FltInjection.dcf
 *     SW-C Type:  Ap_FltInjection
 *  Generated at:  Tue May  1 09:21:51 2012
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1 (Beta)
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_FltInjection>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Apr 30 16:00:00 2012
 * %version:          2 %
 * %derived_by:       nzx5jd %
 * %date_modified:    Fri May 18 14:09:47 2012 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * -------   -------  --------  -------------------------------------------------------------------------------  ------
 * 04/30/12  1        OT        Initial Version                                                                  5317
 * 05/18/12  2        OT        Fixed Timer Reset Issue (anomaly 3326)
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_FltInjection.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#if(STD_ON == BC_FLTINJECTION_ENABLEFAULTINJECTION)


#include "GlobalMacro.h"


#define D_FREQUENCYTOL_KHZ_F32		0.0005f
#define D_AMPLITUDETOL_ULS_F32		0.000244140625f
#define D_MTRVELTOL_MTRRADPS_F32	0.03125f


typedef struct {
	FltInjectionLocType	FaultInjectionLocation_Cnt_enum;
	float32				PathGain_Uls_f32;
	float32				FaultOffset_Uls_f32;
	float32				SinewaveFrequency_Hz_f32;
	float32				SinewaveAmplitude_Uls_f32;
	float32				VelocityTriggerSetpoint_MtrRadpS_f32;
	boolean				EnableManualTrigger_Cnt_lgc;
	uint32				FaultDuration_mS_u32;
	float32				AssistDDFactor_Uls_f32;
} CanapeParametersType;


#define FLTINJECTION_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
STATIC volatile VAR(CanapeParametersType, FLTINJECTION_VAR) CanapeParameters_M_Str;
STATIC VAR(boolean, FLTINJECTION_VAR) FaultTrigger_Cnt_M_lgc;
STATIC VAR(boolean, FLTINJECTION_VAR) ManualTriggerHangover_Cnt_M_lgc;
STATIC VAR(FltInjectionLocType, FLTINJECTION_VAR) FaultInjectionLocation_Cnt_M_enum;
#define FLTINJECTION_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define FLTINJECTION_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
STATIC VAR(float32, FLTINJECTION_VAR) PathGain_Uls_M_f32;
STATIC VAR(float32, FLTINJECTION_VAR) FaultOffset_Uls_M_f32;
STATIC VAR(float32, FLTINJECTION_VAR) SinewaveAmplitude_Uls_M_f32;
STATIC VAR(uint32,  FLTINJECTION_VAR) FaultDuration_mS_M_u32;
STATIC VAR(uint32,  FLTINJECTION_VAR) FaultStartTime_mS_M_u32;
STATIC VAR(float32, FLTINJECTION_VAR) SineFactor_kHz_M_f32;
STATIC VAR(float32, FLTINJECTION_VAR) PathOffset_Uls_M_f32;
#define FLTINJECTION_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"


#endif /*(STD_ON == BC_FLTINJECTION_ENABLEFAULTINJECTION)*/
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
 * FltInjectionLocType: Enumeration of integer in interval [0...255] with enumerators
 *   FLTINJ_ASSIST (1U)
 *   FLTINJ_RETURN (2U)
 *   FLTINJ_DAMPING (3U)
 *   FLTINJ_ASSTSUMNLMT (4U)
 *   FLTINJ_HYSTCOMP (12U)
 *   FLTINJ_INERTIACOMP (14U)
 *   FLTINJ_STABILITYCOMP (29U)
 *   FLTINJ_TRQBASEDINRTCOMP (30U)
 *   FLTINJ_ASSTFIREWALL (34U)
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
 * Float: D_180OVRPI_ULS_F32 = 57.295779513082F
 * Float: D_2MS_SEC_F32 = 0.002F
 * Float: D_2PI_ULS_F32 = 6.2831853071796F
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8F
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8F
 * Float: D_ONE_ULS_F32 = 1.0F
 * Float: D_PIOVR180_ULS_F32 = 0.0174532925199F
 * Float: D_PI_ULS_F32 = 3.1415926535898F
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
 * UInt16: D_RACKTOVEHCNTRINVALID_CNT_U16 = 4095U
 * UInt16: D_RACKTOVEHCNTRUNLEARNED_CNT_U16 = 4094U
 * UInt16: D_ZERO_CNT_U16 = 0U
 * UInt32: D_ONE_CNT_U32 = 1U
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


#define RTE_START_SEC_AP_FLTINJECTION_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: FltInjection_Per1
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
 *   Float Rte_IRead_FltInjection_Per1_MotorVelCRF_MtrRadpS_f32(void)
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

FUNC(void, RTE_AP_FLTINJECTION_APPL_CODE) FltInjection_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: FltInjection_Per1
 *********************************************************************************************************************/
#if(STD_ON == BC_FLTINJECTION_ENABLEFAULTINJECTION)
	
	
	VAR(float32, AUTOMATIC) MotorVelCRF_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) AbsMotorVelCRF_MtrRadpS_T_f32;
	VAR(uint32,  AUTOMATIC) ElapsedTime_mS_T_u32;
	
	MotorVelCRF_MtrRadpS_T_f32 = Rte_IRead_FltInjection_Per1_MotorVelCRF_MtrRadpS_f32();
	AbsMotorVelCRF_MtrRadpS_T_f32 = Abs_f32_m(MotorVelCRF_MtrRadpS_T_f32);
	
	
	if( CanapeParameters_M_Str.EnableManualTrigger_Cnt_lgc == FALSE )
	{
		ManualTriggerHangover_Cnt_M_lgc = FALSE;
	}
	
	if( FaultTrigger_Cnt_M_lgc == TRUE )
	{
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(FaultStartTime_mS_M_u32, &ElapsedTime_mS_T_u32);
		
		if( (CanapeParameters_M_Str.EnableManualTrigger_Cnt_lgc == FALSE) ||
			( (FaultDuration_mS_M_u32 > D_ZERO_CNT_U32) &&
			  (ElapsedTime_mS_T_u32 > FaultDuration_mS_M_u32) ) )
		{
			FaultTrigger_Cnt_M_lgc = FALSE;
		}
		else
		{
			if( SineFactor_kHz_M_f32 > D_FREQUENCYTOL_KHZ_F32 )
			{
				PathOffset_Uls_M_f32 = (sinf(ElapsedTime_mS_T_u32 * SineFactor_kHz_M_f32) * SinewaveAmplitude_Uls_M_f32) + FaultOffset_Uls_M_f32;
			}
		}
	}
	else
	{
		if( (CanapeParameters_M_Str.EnableManualTrigger_Cnt_lgc == TRUE) &&
			(ManualTriggerHangover_Cnt_M_lgc == FALSE) &&
			( (CanapeParameters_M_Str.VelocityTriggerSetpoint_MtrRadpS_f32 < D_MTRVELTOL_MTRRADPS_F32) ||
			  (AbsMotorVelCRF_MtrRadpS_T_f32 >= CanapeParameters_M_Str.VelocityTriggerSetpoint_MtrRadpS_f32) ) )
		{
			SinewaveAmplitude_Uls_M_f32 = CanapeParameters_M_Str.SinewaveAmplitude_Uls_f32;
			if( SinewaveAmplitude_Uls_M_f32 < D_AMPLITUDETOL_ULS_F32 )
			{
				SineFactor_kHz_M_f32 = D_ZERO_ULS_F32;
			}
			else
			{
				SineFactor_kHz_M_f32 = (D_2PI_ULS_F32 * CanapeParameters_M_Str.SinewaveFrequency_Hz_f32) / D_SFINVMILLI_ULS_F32;
			}
			FaultOffset_Uls_M_f32 = CanapeParameters_M_Str.FaultOffset_Uls_f32;
			PathOffset_Uls_M_f32 = FaultOffset_Uls_M_f32;
			PathGain_Uls_M_f32 = CanapeParameters_M_Str.PathGain_Uls_f32;
			FaultDuration_mS_M_u32 = CanapeParameters_M_Str.FaultDuration_mS_u32;
			FaultInjectionLocation_Cnt_M_enum = CanapeParameters_M_Str.FaultInjectionLocation_Cnt_enum;
			Rte_Call_SystemTime_GetSystemTime_mS_u32(&FaultStartTime_mS_M_u32);
			FaultTrigger_Cnt_M_lgc = TRUE;
			ManualTriggerHangover_Cnt_M_lgc = TRUE;
		}
	}
	
	
#endif /*(STD_ON == BC_FLTINJECTION_ENABLEFAULTINJECTION)*/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: FltInjection_SCom_FltInjection
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <FltInjection> of PortPrototype <FltInjection_SCom>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void FltInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_FLTINJECTION_APPL_CODE) FltInjection_SCom_FltInjection(P2VAR(Float, AUTOMATIC, RTE_AP_FLTINJECTION_APPL_VAR) SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: FltInjection_SCom_FltInjection
 *********************************************************************************************************************/
#if(STD_ON == BC_FLTINJECTION_ENABLEFAULTINJECTION)
	
	
	if( (FaultTrigger_Cnt_M_lgc == TRUE) &&
		(LocationKey_Cnt_enum == FaultInjectionLocation_Cnt_M_enum) )
	{
		*SignalPath_Uls_f32 = ((*SignalPath_Uls_f32) * PathGain_Uls_M_f32) + PathOffset_Uls_M_f32;
	}
	
	
#endif /*(STD_ON == BC_FLTINJECTION_ENABLEFAULTINJECTION)*/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_FLTINJECTION_APPL_CODE
#include "MemMap.h"


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
