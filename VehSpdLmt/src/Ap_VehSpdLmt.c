/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_VehSpdLmt.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/VehSpdLmt-nzt9hv/VehSpdLmt/autosar
 *     SW-C Type:  Ap_VehSpdLmt
 *  Generated at:  Mon Sep 24 12:53:11 2012
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_VehSpdLmt>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* Version Control:
 * Date Created:      Fri Nov 11 09:28:51 2011
 * %version:          3 %
 * %date_modified:    Mon Sep 24 12:38:50 2012 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 11/11/11	 1		  LWW		Initial Stub
 * 11/15/11	 2	  LWW		Initial component design
 * 09/23/12  3        Selva      Checkpoints added and mempmap macros corrected		                          6254
 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_VehSpdLmt.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "fixmath.h"
#include "interpolation.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "Ap_VehSpdLmt_Cfg.h"

#define D_MAXCONF_ULS_F32						1.0F
#define D_ASTVEHSPDLMTLOLMT_MTRNM_F32			0.0F
#define D_ASTVEHSPDLMTHILMT_MTRNM_F32			8.8F

#define VEHSPDLMT_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
STATIC volatile VAR(uint16, SA_MTRCURR_VAR_NOINIT) ZeroVehSpd_MtrNm_D_u5p11;
STATIC volatile VAR(uint16, SA_MTRCURR_VAR_NOINIT) LimitTerm_MtrNm_D_u5p11;
STATIC volatile VAR(uint16, SA_MTRCURR_VAR_NOINIT) BkPtOne_HwDeg_D_u12p4;
STATIC volatile VAR(uint16, SA_MTRCURR_VAR_NOINIT) BkPtTwo_HwDeg_D_u12p4 ;
#define VEHSPDLMT_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

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
 * Float: Real in interval ]-FLT_MAX...FLT_MAX[ with single precision (standard type)
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
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_VEHSPDLMT_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VehSpdLmt_Per1
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
 *   Float Rte_IRead_VehSpdLmt_Per1_CCWPosition_HwDeg_f32(void)
 *   Float Rte_IRead_VehSpdLmt_Per1_CWPosition_HwDeg_f32(void)
 *   Float Rte_IRead_VehSpdLmt_Per1_HwPosAuth_Uls_f32(void)
 *   Float Rte_IRead_VehSpdLmt_Per1_HwPos_HwDeg_f32(void)
 *   Float Rte_IRead_VehSpdLmt_Per1_VehSpd_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_VehSpdLmt_Per1_AstVehSpdLimit_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_VehSpdLmt_Per1_AstVehSpdLimit_MtrNm_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_VEHSPDLMT_APPL_CODE) VehSpdLmt_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: VehSpdLmt_Per1
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) HwPosAuth_Uls_T_f32;
	VAR(float32, AUTOMATIC) HwPos_HwDeg_T_f32;
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(float32, AUTOMATIC) CCWEOTPos_HwDeg_T_f32;
	VAR(float32, AUTOMATIC) CWEOTPos_HwDeg_T_f32;
	VAR(sint16, AUTOMATIC) HwPos_HwDeg_T_s11p4;
	VAR(uint16, AUTOMATIC) VehSpd_Kph_T_u9p7;
	VAR(sint16, AUTOMATIC) CCWEOTPos_HwDeg_T_s11p4;
	VAR(sint16, AUTOMATIC) CWEOTPos_HwDeg_T_s11p4;
	VAR(uint16, AUTOMATIC) t_AssistLimTblX_HwDeg_T_u12p4[2];
	VAR(uint16, AUTOMATIC) t_AssistLimTblY_MtrNm_T_u5p11[2];
	VAR(uint16, AUTOMATIC) AstVehSpdLimit_MtrNm_T_u5p11;
	VAR(float32, AUTOMATIC) AstVehSpdLimit_MtrNm_f32;
    /* Configurable Start of Runnable Checkpoint */
	Rte_Call_VehSpdLmt_Per1_CP0_CheckpointReached();

	HwPosAuth_Uls_T_f32 = Rte_IRead_VehSpdLmt_Per1_HwPosAuth_Uls_f32();
 	HwPos_HwDeg_T_f32 = Rte_IRead_VehSpdLmt_Per1_HwPos_HwDeg_f32();
 	VehSpd_Kph_T_f32 = Rte_IRead_VehSpdLmt_Per1_VehSpd_Kph_f32();
 	CCWEOTPos_HwDeg_T_f32 = Rte_IRead_VehSpdLmt_Per1_CCWPosition_HwDeg_f32();
 	CWEOTPos_HwDeg_T_f32 = Rte_IRead_VehSpdLmt_Per1_CWPosition_HwDeg_f32();
 
	HwPos_HwDeg_T_s11p4 = FPM_FloatToFixed_m(HwPos_HwDeg_T_f32, s11p4_T);	
	CCWEOTPos_HwDeg_T_s11p4 = FPM_FloatToFixed_m(CCWEOTPos_HwDeg_T_f32, s11p4_T);	
	CWEOTPos_HwDeg_T_s11p4 = FPM_FloatToFixed_m(CWEOTPos_HwDeg_T_f32, s11p4_T);	
	VehSpd_Kph_T_u9p7 = FPM_FloatToFixed_m(VehSpd_Kph_T_f32, u9p7_T);
	
	t_AssistLimTblY_MtrNm_T_u5p11[0] = t_MaxAsstTblY_MtrNm_u5p11[0];
	t_AssistLimTblY_MtrNm_T_u5p11[1] = IntplVarXY_u16_u16Xu16Y_Cnt(	t_MaxAsstTblX_Kph_u9p7, 
	                                 								t_MaxAsstTblY_MtrNm_u5p11, 
	                                 								TableSize_m(t_MaxAsstTblX_Kph_u9p7), 
	                                 								VehSpd_Kph_T_u9p7);

	if (HwPos_HwDeg_T_s11p4 < 0)
	{
		t_AssistLimTblX_HwDeg_T_u12p4[0] = Abs_s16_m((CCWEOTPos_HwDeg_T_s11p4 + (sint16)k_PosMaxOfstOne_HwDeg_u12p4));
		t_AssistLimTblX_HwDeg_T_u12p4[1] = Abs_s16_m((CCWEOTPos_HwDeg_T_s11p4 + (sint16)k_PosMaxOfstTwo_HwDeg_u12p4));
	}
	else
	{
		t_AssistLimTblX_HwDeg_T_u12p4[0] = (uint16)(CWEOTPos_HwDeg_T_s11p4 - (sint16)k_PosMaxOfstOne_HwDeg_u12p4);
		t_AssistLimTblX_HwDeg_T_u12p4[1] = (uint16)(CWEOTPos_HwDeg_T_s11p4 - (sint16)k_PosMaxOfstTwo_HwDeg_u12p4);
	}

	if (HwPosAuth_Uls_T_f32 >= D_MAXCONF_ULS_F32)
	{
		AstVehSpdLimit_MtrNm_T_u5p11 = IntplVarXY_u16_u16Xu16Y_Cnt(	t_AssistLimTblX_HwDeg_T_u12p4, 
	                                 								t_AssistLimTblY_MtrNm_T_u5p11, 
	                                 								TableSize_m(t_AssistLimTblX_HwDeg_T_u12p4), 
	                                 								Abs_s16_m(HwPos_HwDeg_T_s11p4));
	}
	else
	{
		AstVehSpdLimit_MtrNm_T_u5p11 = t_AssistLimTblY_MtrNm_T_u5p11[0];
	}

	AstVehSpdLimit_MtrNm_f32 = FPM_FixedToFloat_m(AstVehSpdLimit_MtrNm_T_u5p11, u5p11_T);
	AstVehSpdLimit_MtrNm_f32 = Limit_m(AstVehSpdLimit_MtrNm_f32, D_ASTVEHSPDLMTLOLMT_MTRNM_F32, D_ASTVEHSPDLMTHILMT_MTRNM_F32);

	ZeroVehSpd_MtrNm_D_u5p11 = t_AssistLimTblY_MtrNm_T_u5p11[0];
	LimitTerm_MtrNm_D_u5p11 = t_AssistLimTblY_MtrNm_T_u5p11[1];
	BkPtOne_HwDeg_D_u12p4 = t_AssistLimTblX_HwDeg_T_u12p4[0];
	BkPtTwo_HwDeg_D_u12p4 = t_AssistLimTblX_HwDeg_T_u12p4[1];

	Rte_IWrite_VehSpdLmt_Per1_AstVehSpdLimit_MtrNm_f32(AstVehSpdLimit_MtrNm_f32);
	/* Configurable End of Runnable Checkpoint */
    Rte_Call_VehSpdLmt_Per1_CP1_CheckpointReached();


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_VEHSPDLMT_APPL_CODE
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
