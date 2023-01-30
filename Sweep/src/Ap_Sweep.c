/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_Sweep.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/Sweep-nzt9hv/Sweep/autosar
 *     SW-C Type:  Ap_Sweep
 *  Generated at:  Tue Jan  8 15:55:34 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_Sweep>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Oct 8 10:28:32 2012
 * %version:          2 %
 * %derived_by:       nzt9hv %
 * %date_modified:    Tue Jan  8 12:28:18 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 10/08/12   1        LN       Initial component creation                                                   6480
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Operation Prototypes:
 =====================
  DtrmnElapsedTime_mS_u16 of Port Interface SystemTime
    Nexteer SystemTime Service

 *********************************************************************************************************************/

#include "Rte_Ap_Sweep.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_Sweep_Cfg.h"
#include "Ap_Sweep.h"
#include  "fixmath.h"
#include "GlobalMacro.h"

#ifdef SWEEPBUILD
	
	#define D_SWEEPHWTRQ_CNT_U16		2U
	#define D_SWEEPMTRTRQ_CNT_U16		1U

	#define D_SWEEPSTART_CNT_U16		0U
	#define D_SWEEPTRANSITION_CNT_U16	1U
	#define D_SWEEPDWELL_CNT_U16		2U
	#define D_SWEEPSTOP_CNT_U16			3U
	#define D_SWEEPRAMP_CNT_U16			4U
	#define D_SWEEPDONE_CNT_U16			5U


	#define SWEEP_START_SEC_VAR_CLEARED_32
	#include "MemMap.h"/* PRQA S 5087 */
	STATIC VAR(float32, AUTOMATIC) HwTrqQuantization_Uls_M_f32;
	STATIC VAR(float32, AUTOMATIC) CosSweepTorque_HwNm_M_f32;
	STATIC VAR(float32, AUTOMATIC) SweepVehSpdMax_Kph_M_f32;
	STATIC VAR(uint32, AUTOMATIC) DwellStartTime_mS_M_u32p0;
	STATIC VAR(float32, AUTOMATIC) LastStateSinArg_Uls_M_f32;
	STATIC VAR(uint32, AUTOMATIC) TransStartTime_mS_M_u32p0;
	VAR(float32, AUTOMATIC) MtrTrqQuantization_Uls_M_f32;
    VAR(float32, AUTOMATIC) SweepTorque_HwNm_M_f32;
	
	#define SWEEP_STOP_SEC_VAR_CLEARED_32
    #include "MemMap.h"/* PRQA S 5087 */

	#define SWEEP_START_SEC_VAR_CLEARED_16
	#include "MemMap.h"/* PRQA S 5087 */
	STATIC volatile VAR(sint16, AUTOMATIC) CosSweepTorque_HwNm_D_s10p5;
	STATIC volatile VAR(uint16, AUTOMATIC) InstFrequency_Hz_D_u7p9;
	STATIC volatile VAR(sint16, AUTOMATIC) RespTorque_HwNm_D_s10p5;
	STATIC volatile VAR(sint16, AUTOMATIC) SweepTorque_HwNm_D_s10p5;
	STATIC VAR(uint16, AUTOMATIC) SweepAmplitude_HwNm_M_u5p11;
	STATIC VAR(sint16, AUTOMATIC) SweepOffset_HwNm_M_s4p11;
	STATIC VAR(uint16, AUTOMATIC) SweepState_Cnt_M_u16;
	STATIC VAR(uint16, AUTOMATIC) FreqIndex_Cnt_M_u16;
	STATIC VAR(uint16, AUTOMATIC) k_N_SweepConfig_Cnt_u16;
	STATIC VAR(uint16, AUTOMATIC) k_N_SweepGain_MtrNmpHwNm_u1p15;
	STATIC VAR(sint16, AUTOMATIC) L5_N_SweepOffset_HwNm_M_s4p11;
	STATIC VAR(uint16, AUTOMATIC) L5_N_SweepAmplitude_HwNm_M_u5p11;
	
	STATIC volatile VAR(sint16, AUTOMATIC) L5_N_CosSweepTorque_HwNm_M_s10p5;
	STATIC volatile VAR(sint16, AUTOMATIC) L5_N_RespTorque_HwNm_G_s10p5;
	STATIC volatile VAR(uint16, AUTOMATIC) L5_N_SweepState_Cnt_M_u16;
	STATIC volatile VAR(sint16, AUTOMATIC) L5_N_SweepTorque_HwNm_G_s10p5;
	STATIC volatile VAR(uint16, AUTOMATIC) L5_N_InstFrequency_Hz_G_u7p9;
	VAR(uint16, AUTOMATIC) SweepConfig_Cnt_M_u16;
	VAR(uint16, AUTOMATIC) SweepGain_MtrNmpHwNm_M_u1p15;
	#define SWEEP_STOP_SEC_VAR_CLEARED_16
    #include "MemMap.h"/* PRQA S 5087 */

	#define SWEEP_START_SEC_VAR_CLEARED_BOOLEAN
    #include "MemMap.h"/* PRQA S 5087 */
	/* PSR Additions for existing tool compatibility */
	STATIC VAR(boolean, AUTOMATIC) L5_N_GenHwTrq_Cnt_M_lgc;
	STATIC VAR(boolean, AUTOMATIC) k_N_EnVehSpdCheck_Cnt_lgc;
	STATIC VAR(boolean, AUTOMATIC) k_N_SweepModeEn_Cnt_lgc;
	STATIC VAR(boolean, AUTOMATIC) EnVehSpdCheck_Cnt_M_lgc;
	STATIC VAR(boolean, AUTOMATIC) GenHwTrq_Cnt_M_lgc;
	VAR(boolean, AUTOMATIC) SweepModeEn_Cnt_M_lgc;
	#define SWEEP_STOP_SEC_VAR_CLEARED_BOOLEAN
    #include "MemMap.h"/* PRQA S 5087 */
	
	


	
	STATIC CONST(float32, AUTOMATIC) T_SweepFreq_Hz_f32[100] =
	{
	0.0F, 1.0F, 1.2F, 1.4F, 1.6F, 1.8F, 2.0F, 2.25F, 2.5F, 2.75F, 3.0F, 3.25F, 3.5F, 3.75F, 4.0F, 4.25F, 4.5F, 4.75F, 5.0F, 5.25F, 5.5F, 5.75F, 6.0F, 6.25F, 6.5F, 6.75F, 7.0F, 7.25F, 7.5F, 7.75F, 8.0F, 8.25F, 8.5F, 8.75F, 9.0F, 9.25F, 9.5F, 9.75F, 10.0F, 10.25F, 10.5F, 10.75F, 11.0F, 11.25F, 11.5F, 11.75F, 12.0F, 12.25F, 12.5F, 12.75F, 13.0F, 13.25F, 13.5F, 13.75F, 14.0F, 14.25F, 14.5F, 14.75F, 15.0F, 15.5F, 16.0F, 16.5F, 17.0F, 17.5F, 18.0F, 18.5F, 19.0F, 19.5F, 20.0F, 21.0F, 22.0F, 23.0F, 24.0F, 25.0F, 26.0F, 27.0F, 28.0F, 29.0F, 30.0F, 32.0F, 34.0F, 36.0F, 38.0F, 40.0F, 42.0F, 44.0F, 46.0F, 48.0F, 50.0F, 55.0F, 60.0F, 65.0F, 70.0F, 75.0F, 80.0F, 85.0F, 90.0F, 95.0F, 100.0F, 105.0F
	};

	STATIC CONST(uint16, AUTOMATIC) T_TransTime_mS_u16p0[100] =
	{
	2000U, 500U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 250U, 1000U
	};

	STATIC CONST(uint16, AUTOMATIC) T_DwellTime_mS_u16p0[100] =
	{
	0U, 32000U, 18333U, 10714U, 9375U, 8333U, 7500U, 6667U, 6000U, 5455U, 4667U, 4308U, 3714U, 3467U, 3000U, 2824U, 2667U, 2526U, 2400U, 2286U, 2182U, 2087U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U, 2000U
	};

#endif
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
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_SWEEP_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Sweep_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_SWEEP_APPL_CODE) Sweep_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Sweep_Init
 *********************************************************************************************************************/
#ifdef SWEEPBUILD

	SweepAmplitude_HwNm_M_u5p11 = FPM_FloatToFixed_m(D_ONE_ULS_F32, u5p11_T);
	SweepOffset_HwNm_M_s4p11 = 0;
	SweepModeEn_Cnt_M_lgc = TRUE;
	EnVehSpdCheck_Cnt_M_lgc = TRUE;
	HwTrqQuantization_Uls_M_f32 = 0.03125F;
	GenHwTrq_Cnt_M_lgc = FALSE;
	SweepGain_MtrNmpHwNm_M_u1p15 = FPM_FloatToFixed_m(0.1F, u1p15_T);
	MtrTrqQuantization_Uls_M_f32 = 0.00390625F;
	SweepConfig_Cnt_M_u16 = D_SWEEPMTRTRQ_CNT_U16;
	SweepVehSpdMax_Kph_M_f32 = 30.0F;

	/* PSR Additions for existing tool compatibility */
	L5_N_GenHwTrq_Cnt_M_lgc = GenHwTrq_Cnt_M_lgc;
	k_N_EnVehSpdCheck_Cnt_lgc = EnVehSpdCheck_Cnt_M_lgc;
	k_N_SweepConfig_Cnt_u16 = SweepConfig_Cnt_M_u16;
	k_N_SweepGain_MtrNmpHwNm_u1p15 = SweepGain_MtrNmpHwNm_M_u1p15;
	L5_N_SweepOffset_HwNm_M_s4p11 = SweepOffset_HwNm_M_s4p11;
	L5_N_SweepAmplitude_HwNm_M_u5p11 = SweepAmplitude_HwNm_M_u5p11;
	k_N_SweepModeEn_Cnt_lgc = SweepModeEn_Cnt_M_lgc;

#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Sweep_Per1
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
 *   Float Rte_IRead_Sweep_Per1_InputHwTrq_HwNm_f32(void)
 *   Boolean Rte_IRead_Sweep_Per1_VehSpdValid_Cnt_lgc(void)
 *   Float Rte_IRead_Sweep_Per1_VehSpd_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_Sweep_Per1_OutputHwTrq_HwNm_f32(Float data)
 *   Float *Rte_IWriteRef_Sweep_Per1_OutputHwTrq_HwNm_f32(void)
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

FUNC(void, RTE_AP_SWEEP_APPL_CODE) Sweep_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Sweep_Per1
 *********************************************************************************************************************/
	
	
	/*	Variables Written by tool:
			EnVehSpdCheck_Cnt_M_lgc
			GenHwTrq_Cnt_M_lgc
			HwTrqQuantization_Uls_M_f32
			SweepAmplitude_HwNm_M_u5p11
			SweepOffset_HwNm_M_s4p11
			SweepGain_MtrNmpHwNm_M_u1p15

		Variables Read by tool:
			SweepState_Cnt_M_u16
			InstFrequency_Hz_D_u7p9
			RespTorque_HwNm_D_s10p5
			SweepTorque_HwNm_D_s10p5
			CosSweepTorque_HwNm_D_s10p5
	*/

	#ifdef SWEEPBUILD
	
	/* Note for Software guideline deviation:
	     The following variables 
               SweepModeEn_Cnt_M_lgc,
               SweepConfig_Cnt_M_u16,
               SweepGain_MtrNmpHwNm_M_u1p15,
               MtrTrqQuantization_Uls_M_f32,
               SweepTorque_HwNm_M_f32
                  are shared between Sweep.C and Sweep2.C as global variables instead of actual RTE sharing.
                This is done to ensure the compatability of sweep code with the existing tool set and also reduce the unused code if predefined compiler directive "SWEEPBUILD" is not used. This deviation exists only for Sweep build. */ 				  

	VAR(float32, AUTOMATIC) InputHwTrq_HwNm_T_f32;
	VAR(float32, AUTOMATIC) OutputHwTrq_HwNm_T_f32;
	VAR(boolean, AUTOMATIC) VehSpdValid_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(float32, AUTOMATIC) FreqSpan_Hz_T_f32;
	VAR(float32, AUTOMATIC) TimeScale_Uls_T_f32;
	VAR(float32, AUTOMATIC) ScaleFactor_Uls_T_f32;
	VAR(float32, AUTOMATIC) DeltaFreq_Hz_T_f32;
	VAR(float32, AUTOMATIC) InstFrequency_Hz_T_f32;
	VAR(float32, AUTOMATIC) Freq_Hz_T_f32;
	VAR(float32, AUTOMATIC) SinArg_Uls_T_f32;
	VAR(float32, AUTOMATIC) SweepTorque_HwNm_T_f32;
	VAR(float32, AUTOMATIC) CosSweepTorque_HwNm_T_f32;
	VAR(uint16, AUTOMATIC) ElapsedTime_mS_T_u16p0;
	VAR(uint16, AUTOMATIC) StateTime_mS_T_u16p0;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_Sweep_Per1_CP0_CheckpointReached();

	InputHwTrq_HwNm_T_f32 = Rte_IRead_Sweep_Per1_InputHwTrq_HwNm_f32();
	VehSpdValid_Cnt_T_lgc = Rte_IRead_Sweep_Per1_VehSpdValid_Cnt_lgc();
	VehSpd_Kph_T_f32 = Rte_IRead_Sweep_Per1_VehSpd_Kph_f32();
	
	/* PSR Additions for existing tool compatibility */
	GenHwTrq_Cnt_M_lgc = L5_N_GenHwTrq_Cnt_M_lgc;
	EnVehSpdCheck_Cnt_M_lgc = k_N_EnVehSpdCheck_Cnt_lgc;
	SweepConfig_Cnt_M_u16 = k_N_SweepConfig_Cnt_u16;
	SweepGain_MtrNmpHwNm_M_u1p15 = k_N_SweepGain_MtrNmpHwNm_u1p15;
	SweepOffset_HwNm_M_s4p11 = L5_N_SweepOffset_HwNm_M_s4p11;
	SweepAmplitude_HwNm_M_u5p11 = L5_N_SweepAmplitude_HwNm_M_u5p11;
	SweepModeEn_Cnt_M_lgc = k_N_SweepModeEn_Cnt_lgc;

	if (GenHwTrq_Cnt_M_lgc == TRUE)
	{
		/* Check for vehicle speed criteria */
		if ((EnVehSpdCheck_Cnt_M_lgc == TRUE) &&
			((VehSpd_Kph_T_f32 > SweepVehSpdMax_Kph_M_f32) ||
			(FALSE == VehSpdValid_Cnt_T_lgc)))
		{
			if (SweepState_Cnt_M_u16 != D_SWEEPDONE_CNT_U16)
			{
				if (SweepState_Cnt_M_u16 != D_SWEEPRAMP_CNT_U16)
				{
					SweepState_Cnt_M_u16 = D_SWEEPRAMP_CNT_U16;
					Rte_Call_SystemTime_GetSystemTime_mS_u32(&TransStartTime_mS_M_u32p0);
				}
			}
		}

		switch (SweepState_Cnt_M_u16)
		{
			case D_SWEEPSTART_CNT_U16:
			case D_SWEEPTRANSITION_CNT_U16:

				Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(TransStartTime_mS_M_u32p0, &ElapsedTime_mS_T_u16p0);
				FreqSpan_Hz_T_f32 = T_SweepFreq_Hz_f32[FreqIndex_Cnt_M_u16+1U] - T_SweepFreq_Hz_f32[FreqIndex_Cnt_M_u16];
				TimeScale_Uls_T_f32 = (float32)ElapsedTime_mS_T_u16p0/(float32)T_TransTime_mS_u16p0[FreqIndex_Cnt_M_u16];

				if (FreqIndex_Cnt_M_u16 == 0U)
				{
					ScaleFactor_Uls_T_f32 = TimeScale_Uls_T_f32;
				}
				else
				{
					ScaleFactor_Uls_T_f32 = D_ONE_ULS_F32;
				}

				DeltaFreq_Hz_T_f32 = FreqSpan_Hz_T_f32 * TimeScale_Uls_T_f32;

				InstFrequency_Hz_T_f32 = DeltaFreq_Hz_T_f32 + T_SweepFreq_Hz_f32[FreqIndex_Cnt_M_u16];
				InstFrequency_Hz_D_u7p9 = FPM_FloatToFixed_m(InstFrequency_Hz_T_f32, u7p9_T);

				Freq_Hz_T_f32 = (DeltaFreq_Hz_T_f32 * 0.5F) + T_SweepFreq_Hz_f32[FreqIndex_Cnt_M_u16];
				SinArg_Uls_T_f32 = ((Freq_Hz_T_f32 * (float32)ElapsedTime_mS_T_u16p0) * 0.001F) + LastStateSinArg_Uls_M_f32;
				
				SweepTorque_HwNm_T_f32 = FPM_FixedToFloat_m(SweepAmplitude_HwNm_M_u5p11, u5p11_T) * sinf(SinArg_Uls_T_f32 * D_2PI_ULS_F32);
				SweepTorque_HwNm_T_f32 = SweepTorque_HwNm_T_f32 + FPM_FixedToFloat_m(SweepOffset_HwNm_M_s4p11, s4p11_T);
				SweepTorque_HwNm_T_f32 = SweepTorque_HwNm_T_f32 * ScaleFactor_Uls_T_f32;

				CosSweepTorque_HwNm_T_f32 = FPM_FixedToFloat_m(SweepAmplitude_HwNm_M_u5p11, u5p11_T) * cosf(SinArg_Uls_T_f32 * D_2PI_ULS_F32);
				CosSweepTorque_HwNm_T_f32 = CosSweepTorque_HwNm_T_f32 + FPM_FixedToFloat_m(SweepOffset_HwNm_M_s4p11, s4p11_T);
				CosSweepTorque_HwNm_T_f32 = CosSweepTorque_HwNm_T_f32 * ScaleFactor_Uls_T_f32;
				
				if (ElapsedTime_mS_T_u16p0 >= T_TransTime_mS_u16p0[FreqIndex_Cnt_M_u16])
				{
					SweepState_Cnt_M_u16 = D_SWEEPDWELL_CNT_U16;
					LastStateSinArg_Uls_M_f32 = SinArg_Uls_T_f32;
					Rte_Call_SystemTime_GetSystemTime_mS_u32(&DwellStartTime_mS_M_u32p0);
					FreqIndex_Cnt_M_u16++; 
				}
			break;

			case D_SWEEPSTOP_CNT_U16:
			case D_SWEEPDWELL_CNT_U16:

				Freq_Hz_T_f32 = T_SweepFreq_Hz_f32[FreqIndex_Cnt_M_u16];
				InstFrequency_Hz_D_u7p9 = FPM_FloatToFixed_m(Freq_Hz_T_f32, u7p9_T);
				
				Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(DwellStartTime_mS_M_u32p0, &ElapsedTime_mS_T_u16p0);
				
				if (D_SWEEPSTOP_CNT_U16 == SweepState_Cnt_M_u16)
				{
					TimeScale_Uls_T_f32 = (float32)ElapsedTime_mS_T_u16p0/(float32)T_TransTime_mS_u16p0[FreqIndex_Cnt_M_u16];
					ScaleFactor_Uls_T_f32 = D_ONE_ULS_F32 - TimeScale_Uls_T_f32;
					StateTime_mS_T_u16p0 = T_TransTime_mS_u16p0[FreqIndex_Cnt_M_u16];
				}
				else
				{
					ScaleFactor_Uls_T_f32 = D_ONE_ULS_F32;
					StateTime_mS_T_u16p0 = T_DwellTime_mS_u16p0[FreqIndex_Cnt_M_u16];
				}

				SinArg_Uls_T_f32 = ((Freq_Hz_T_f32 * (float32)ElapsedTime_mS_T_u16p0) * 0.001F) + LastStateSinArg_Uls_M_f32;
				
				SweepTorque_HwNm_T_f32 = FPM_FixedToFloat_m(SweepAmplitude_HwNm_M_u5p11, u5p11_T) * sinf(SinArg_Uls_T_f32 * D_2PI_ULS_F32);
				SweepTorque_HwNm_T_f32 = SweepTorque_HwNm_T_f32 + FPM_FixedToFloat_m(SweepOffset_HwNm_M_s4p11, s4p11_T);
				SweepTorque_HwNm_T_f32 = SweepTorque_HwNm_T_f32 * ScaleFactor_Uls_T_f32;

				CosSweepTorque_HwNm_T_f32 = FPM_FixedToFloat_m(SweepAmplitude_HwNm_M_u5p11, u5p11_T) * cosf(SinArg_Uls_T_f32 * D_2PI_ULS_F32);
				CosSweepTorque_HwNm_T_f32 = CosSweepTorque_HwNm_T_f32 + FPM_FixedToFloat_m(SweepOffset_HwNm_M_s4p11, s4p11_T);
				CosSweepTorque_HwNm_T_f32 = CosSweepTorque_HwNm_T_f32 * ScaleFactor_Uls_T_f32;

				if (ElapsedTime_mS_T_u16p0 >= StateTime_mS_T_u16p0)
				{
					
					if (D_SWEEPSTOP_CNT_U16 == SweepState_Cnt_M_u16)
					{
						SweepState_Cnt_M_u16 = D_SWEEPDONE_CNT_U16;
					}
					else if (FreqIndex_Cnt_M_u16 == (TableSize_m(T_SweepFreq_Hz_f32)-1))
					{
						SweepState_Cnt_M_u16 = D_SWEEPSTOP_CNT_U16;
						LastStateSinArg_Uls_M_f32 = SinArg_Uls_T_f32;
						Rte_Call_SystemTime_GetSystemTime_mS_u32(&DwellStartTime_mS_M_u32p0);
					}
					else
					{
						SweepState_Cnt_M_u16 = D_SWEEPTRANSITION_CNT_U16;
						LastStateSinArg_Uls_M_f32 = SinArg_Uls_T_f32;
						Rte_Call_SystemTime_GetSystemTime_mS_u32(&TransStartTime_mS_M_u32p0);
					}
				}
			break;

			case D_SWEEPRAMP_CNT_U16:
				Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(TransStartTime_mS_M_u32p0, &ElapsedTime_mS_T_u16p0);
				TimeScale_Uls_T_f32 = (float32)ElapsedTime_mS_T_u16p0/(float32)T_TransTime_mS_u16p0[FreqIndex_Cnt_M_u16];
				ScaleFactor_Uls_T_f32 = D_ONE_ULS_F32 - TimeScale_Uls_T_f32;
				
				if (ElapsedTime_mS_T_u16p0 >= T_TransTime_mS_u16p0[(TableSize_m(T_SweepFreq_Hz_f32)-1)])
				{
					SweepTorque_HwNm_T_f32 = 0.0F;
					CosSweepTorque_HwNm_T_f32 = 0.0F;
					SweepState_Cnt_M_u16 = D_SWEEPDONE_CNT_U16;
				}
				else
				{
					SweepTorque_HwNm_T_f32 = SweepTorque_HwNm_M_f32 * ScaleFactor_Uls_T_f32;
					CosSweepTorque_HwNm_T_f32 = CosSweepTorque_HwNm_M_f32 * ScaleFactor_Uls_T_f32;
				}
			break;
			default:
				GenHwTrq_Cnt_M_lgc = FALSE;
				SweepTorque_HwNm_T_f32 = 0.0F;
				CosSweepTorque_HwNm_T_f32 = 0.0F;
			break;
		}
	}
	else
	{
		SweepTorque_HwNm_T_f32 = 0.0F;
		CosSweepTorque_HwNm_T_f32 = 0.0F;
		Rte_Call_SystemTime_GetSystemTime_mS_u32(&TransStartTime_mS_M_u32p0);
		SweepState_Cnt_M_u16 = D_SWEEPSTART_CNT_U16;
		FreqIndex_Cnt_M_u16 = 0U;
		LastStateSinArg_Uls_M_f32 = 0.0F;
		InstFrequency_Hz_D_u7p9 = 0U;
	}

	
	SweepTorque_HwNm_M_f32 = SweepTorque_HwNm_T_f32;
	CosSweepTorque_HwNm_M_f32 = CosSweepTorque_HwNm_T_f32;
	SweepTorque_HwNm_D_s10p5 = FPM_FloatToFixed_m(SweepTorque_HwNm_T_f32, s10p5_T);
	CosSweepTorque_HwNm_D_s10p5 = FPM_FloatToFixed_m(CosSweepTorque_HwNm_T_f32, s10p5_T);
	RespTorque_HwNm_D_s10p5 = FPM_FloatToFixed_m(InputHwTrq_HwNm_T_f32, s10p5_T);

	/* PSR Additions for existing tool compatibility */
	L5_N_RespTorque_HwNm_G_s10p5 = RespTorque_HwNm_D_s10p5;
	L5_N_SweepTorque_HwNm_G_s10p5 = SweepTorque_HwNm_D_s10p5;
	L5_N_CosSweepTorque_HwNm_M_s10p5 = CosSweepTorque_HwNm_D_s10p5;
	L5_N_SweepState_Cnt_M_u16 = SweepState_Cnt_M_u16;
	L5_N_InstFrequency_Hz_G_u7p9 = InstFrequency_Hz_D_u7p9;
	L5_N_GenHwTrq_Cnt_M_lgc = GenHwTrq_Cnt_M_lgc;

	if ((TRUE == SweepModeEn_Cnt_M_lgc) && (D_SWEEPHWTRQ_CNT_U16 == SweepConfig_Cnt_M_u16))
    {
		SweepTorque_HwNm_T_f32 = (float32)((sint32)((SweepTorque_HwNm_T_f32 / HwTrqQuantization_Uls_M_f32)+ ((float32)Sign_f32_m(SweepTorque_HwNm_T_f32) * 0.5F))) * HwTrqQuantization_Uls_M_f32;
		OutputHwTrq_HwNm_T_f32 = SweepTorque_HwNm_T_f32;

	}
	else
	{
		OutputHwTrq_HwNm_T_f32 = InputHwTrq_HwNm_T_f32;
	}
	
	Rte_IWrite_Sweep_Per1_OutputHwTrq_HwNm_f32(OutputHwTrq_HwNm_T_f32);

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_Sweep_Per1_CP1_CheckpointReached();

	#else

	VAR(float32, AUTOMATIC) OutputHwTrq_HwNm_T_f32;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_Sweep_Per1_CP0_CheckpointReached();

	OutputHwTrq_HwNm_T_f32 = Rte_IRead_Sweep_Per1_InputHwTrq_HwNm_f32();
	Rte_IWrite_Sweep_Per1_OutputHwTrq_HwNm_f32(OutputHwTrq_HwNm_T_f32);

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_Sweep_Per1_CP1_CheckpointReached();
	#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_SWEEP_APPL_CODE
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
