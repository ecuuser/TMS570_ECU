/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_PeakCurrEst.c
 *     Workspace:  C:/Users/nzt9hv/Documents/Synergy/ccm_wa/ESG_Dev_65/MtrCtrl_CM-nzt9hv/MtrCtrl_CM/autosar
 *     SW-C Type:  Ap_PeakCurrEst
 *  Generated at:  Tue Apr  7 15:35:10 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_PeakCurrEst>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/*
 * Copyright 2015 Nexteer Automotive
 * Nexteer Confidential
 *
 *  Version Control:
 * Date Created:      Mon Apr 16 00:46:49 2012
 * %version:          5 %
 * %derived_by:       nzt9hv %
 * %date_modified:    Fri Mar 22 13:02:21 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * -------   -------  --------  -------------------------------------------------------------------------------  ------
 * 11/20/12  3		 Selva 		Checkpoints and memmap statements added	
 * 03/21/12  4 		 Selva      Updated to version 8 FDD SF99 B	                                                   7711
 * 03/10/15	 5       Selva      Updated for V15 of FDD SF99B                                                       12888
 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_PeakCurrEst.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* MISRA-C:2004 Rule 3.1: Deviation is allowed till decision is made about fixing the warnings in Nexteer Libraries.  Rule suppressed by line at each occurrence. */
 
/* MISRA-C:2004 Rule 8.7: This deviation is required to keep the memory map intact.  Rule suppressed by line at each occurrence. */

/* MISRA-C:2004 Rule 10.3: This deviation is required because of Nexteer macro library.  Rule suppressed by line at each occurrence. */

/* MISRA-C:2004 Rule 10.4: This deviation is required because of Nexteer macro library.  Rule suppressed by line at each occurrence. */

/* PRQA S 4533 EOF 
 * MISRA-C:2004 Rule 12.7: This deviation is required because of Nexteer macro library.  Rule suppressed by file level. */


/* MISRA-C:2004 Rule 19.1: This deviation is required for AUTOSAR memory map requirements.  Rule suppressed by line at each occurrence. */

/* MISRA-C:2004 Rule 21.1: Deviation is allowed till decision is made about fixing the warnings in Nexteer Libraries.  Rule suppressed by line at each occurrence. */

 
#include "Ap_PeakCurrEst_Cfg.h"
#include "fixmath.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "filters.h"
#define MTRCTRL
#include "Ap_MtrCtrl.h"

#define D_ESTDAXCURRLOLMT_AMP_F32			(-220.0F)
#define D_ESTDAXCURRHILMT_AMP_F32			220.0F

#define D_ESTPKCURRLOLMT_AMPSQ_F32			0.0F
#define D_ESTPKCURRHILMT_AMPSQ_F32			48400.0F

#define D_ESTQAXCURRLOLMT_AMP_F32			0.0F
#define D_ESTQAXCURRHILMT_AMP_F32			220.0F


#define PEAKCURREST_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(sint32, AUTOMATIC) DaxCurrFiltSV_Amp_M_s11p20; /* PRQA S 3218 */
STATIC VAR(sint32, AUTOMATIC) QaxCurrFiltSV_Amp_M_s11p20; /* PRQA S 3218 */
STATIC VAR(uint32, AUTOMATIC) EstPkCurrFiltSV_AmpSq_M_u16p16; /* PRQA S 3218 */
STATIC VAR(float32, AUTOMATIC) EstPkCurr_AmpSq_M_f32; /* PRQA S 3218 */

/* Display variables */
STATIC volatile VAR(float32, AUTOMATIC) FiltMtrCurEst_Iq_Amp_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC) FiltMtrCurEst_Id_Amp_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC) MtrCurEst_Iq_AmpSq_D_f32;   /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC) MtrCurEst_Id_AmpSq_D_f32;   /* PRQA S 3218 */

#define PEAKCURREST_STOP_SEC_VAR_CLEARED_32
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
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
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
 * Float: D_2PI_ULS_F32 = 6.2831853071796
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_PI_ULS_F32 = 3.1415926535898
 * Float: D_VECUMIN_VOLTS_F32 = 5
 * Float: D_ZERO_ULS_F32 = 0
 * SInt16: D_ZERO_CNT_S16 = 0
 * SInt8: D_ONE_CNT_S8 = 1
 * SInt8: D_ZERO_CNT_S8 = 0
 * UInt16: D_ZERO_CNT_U16 = 0u
 * UInt8: D_QUADRANT1_CNT_U8 = 1u
 * UInt8: D_QUADRANT2_CNT_U8 = 2u
 * UInt8: D_QUADRANT3_CNT_U8 = 3u
 * UInt8: D_QUADRANT4_CNT_U8 = 4u
 * UInt8: D_ZERO_CNT_U8 = 0u
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_PEAKCURREST_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: PeakCurrEst_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *     and not in Mode(s) <WARMINIT>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Boolean Rte_IRead_PeakCurrEst_Per1_IvtrLoaMtgtnEn_Cnt_lgc(void)
 *   Boolean Rte_IRead_PeakCurrEst_Per1_MotCurrLoaMtgtnEn_Cnt_lgc(void)
 *   Float Rte_IRead_PeakCurrEst_Per1_MtrCurrDaxRef_Amp_f32(void)
 *   Float Rte_IRead_PeakCurrEst_Per1_MtrCurrDax_Amp_f32(void)
 *   Float Rte_IRead_PeakCurrEst_Per1_MtrCurrQaxRef_Amp_f32(void)
 *   Float Rte_IRead_PeakCurrEst_Per1_MtrCurrQax_Amp_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_PeakCurrEst_Per1_EstPkCurr_AmpSq_f32(Float data)
 *   Float *Rte_IWriteRef_PeakCurrEst_Per1_EstPkCurr_AmpSq_f32(void)
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

FUNC(void, RTE_AP_PEAKCURREST_APPL_CODE) PeakCurrEst_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: PeakCurrEst_Per1
 *********************************************************************************************************************/
VAR(float32, AUTOMATIC) EstMtrCurrQax_Amp_T_f32;
VAR(sint16, AUTOMATIC) EstMtrCurrQax_Amp_T_s11p4;
VAR(sint16, AUTOMATIC) FiltQaxCurr_Amp_T_s11p4;
VAR(float32, AUTOMATIC) FiltQaxCurr_Amp_T_f32;
VAR(float32, AUTOMATIC) EstMtrCurrDax_Amp_T_f32;
VAR(sint16, AUTOMATIC) EstMtrCurrDax_Amp_T_s11p4;
VAR(sint16, AUTOMATIC) FiltDaxCurr_Amp_T_s11p4;
VAR(float32, AUTOMATIC) FiltDaxCurr_Amp_T_f32;
VAR(float32, AUTOMATIC) QaxCurrSqr_AmpSq_T_f32;
VAR(float32, AUTOMATIC) DaxCurrSqr_AmpSq_T_f32;

VAR(float32, AUTOMATIC) EstPkCurr_AmpSq_T_f32;
VAR(boolean, AUTOMATIC) IvtrLoaMtgtnEn_Cnt_T_lgc;
VAR(boolean, AUTOMATIC) MotCurrLoaMtgtnEn_Cnt_T_lgc;


	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_PeakCurrEst_Per1_CP0_CheckpointReached();
	IvtrLoaMtgtnEn_Cnt_T_lgc   =  Rte_IRead_PeakCurrEst_Per1_IvtrLoaMtgtnEn_Cnt_lgc()   ;
	MotCurrLoaMtgtnEn_Cnt_T_lgc=  Rte_IRead_PeakCurrEst_Per1_MotCurrLoaMtgtnEn_Cnt_lgc();

	if ((IvtrLoaMtgtnEn_Cnt_T_lgc == TRUE) ||(MotCurrLoaMtgtnEn_Cnt_T_lgc ==TRUE))
	{
			EstMtrCurrQax_Amp_T_f32=Rte_IRead_PeakCurrEst_Per1_MtrCurrQaxRef_Amp_f32();
			EstMtrCurrDax_Amp_T_f32=Rte_IRead_PeakCurrEst_Per1_MtrCurrDaxRef_Amp_f32();
	}
	else
	{
			EstMtrCurrQax_Amp_T_f32=Rte_IRead_PeakCurrEst_Per1_MtrCurrQax_Amp_f32();
			EstMtrCurrDax_Amp_T_f32=Rte_IRead_PeakCurrEst_Per1_MtrCurrDax_Amp_f32();

	}

	/****Anti aliasing filter Iq (2ms loop)****/
	EstMtrCurrQax_Amp_T_s11p4 = FPM_FloatToFixed_m(EstMtrCurrQax_Amp_T_f32, s11p4_T);                             /* PRQA S 4395 */
	
	QaxCurrFiltSV_Amp_M_s11p20 = LPF_SvUpdate_s16InFixKTrunc_m(	EstMtrCurrQax_Amp_T_s11p4,                        /* PRQA S 2856 */  /* PRQA S 2896 */ /* PRQA S 4394 */
																QaxCurrFiltSV_Amp_M_s11p20,
                                      							k_EstPkCurr2msLPFKn_Uls_u16);  
                                      							
    FiltQaxCurr_Amp_T_s11p4 = (sint16)LPF_OpUpdate_s16InFixKTrunc_m(QaxCurrFiltSV_Amp_M_s11p20);                 /* PRQA S 4394 */
   	FiltQaxCurr_Amp_T_f32 = FPM_FixedToFloat_m(FiltQaxCurr_Amp_T_s11p4, s11p4_T);                                 
	
	
	/**** Anti aliasing filter Id (2ms loop)****/
	EstMtrCurrDax_Amp_T_s11p4 = FPM_FloatToFixed_m(EstMtrCurrDax_Amp_T_f32, s11p4_T);                                /* PRQA S 4395 */
	
	DaxCurrFiltSV_Amp_M_s11p20 = LPF_SvUpdate_s16InFixKTrunc_m(	EstMtrCurrDax_Amp_T_s11p4,                         /* PRQA S 2856 */  /* PRQA S 2896 */ /* PRQA S 4394 */
                                      							DaxCurrFiltSV_Amp_M_s11p20, 
                                      							k_EstPkCurr2msLPFKn_Uls_u16);
                                      							
    FiltDaxCurr_Amp_T_s11p4 = (sint16)LPF_OpUpdate_s16InFixKTrunc_m(DaxCurrFiltSV_Amp_M_s11p20);                  /* PRQA S 4394 */
   	FiltDaxCurr_Amp_T_f32 = FPM_FixedToFloat_m(FiltDaxCurr_Amp_T_s11p4, s11p4_T);                                 /* PRQA S 4395 */
   	
	/**** Motor peak current estimation(2ms loop)****/
   	QaxCurrSqr_AmpSq_T_f32 = FiltQaxCurr_Amp_T_f32 * FiltQaxCurr_Amp_T_f32;
   	DaxCurrSqr_AmpSq_T_f32 = FiltDaxCurr_Amp_T_f32 * FiltDaxCurr_Amp_T_f32;
   	
   	EstPkCurr_AmpSq_T_f32 = QaxCurrSqr_AmpSq_T_f32 + DaxCurrSqr_AmpSq_T_f32;                      								
	EstPkCurr_AmpSq_T_f32 = Limit_m(EstPkCurr_AmpSq_T_f32, D_ESTPKCURRLOLMT_AMPSQ_F32, D_ESTPKCURRHILMT_AMPSQ_F32);
	EstPkCurr_AmpSq_M_f32=EstPkCurr_AmpSq_T_f32;
	/* update display variables */
	FiltMtrCurEst_Iq_Amp_D_f32 = FiltQaxCurr_Amp_T_f32;
	FiltMtrCurEst_Id_Amp_D_f32 = FiltDaxCurr_Amp_T_f32;
	MtrCurEst_Iq_AmpSq_D_f32 = QaxCurrSqr_AmpSq_T_f32;
	MtrCurEst_Id_AmpSq_D_f32 = DaxCurrSqr_AmpSq_T_f32;
	
	Rte_IWrite_PeakCurrEst_Per1_EstPkCurr_AmpSq_f32(EstPkCurr_AmpSq_T_f32);
	


	/* Configurable End of Runnable Checkpoint */
	Rte_Call_PeakCurrEst_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: PeakCurrEst_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 100ms
 *     and not in Mode(s) <WARMINIT>
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_PeakCurrEst_Per2_FiltEstPkCurr_AmpSq_f32(Float data)
 *   Float *Rte_IWriteRef_PeakCurrEst_Per2_FiltEstPkCurr_AmpSq_f32(void)
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

FUNC(void, RTE_AP_PEAKCURREST_APPL_CODE) PeakCurrEst_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: PeakCurrEst_Per2
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) EstPkCurr_AmpSq_T_f32;
	VAR(uint16, AUTOMATIC) 	EstPkCurr_AmpSq_T_u16p0;
	VAR(uint16, AUTOMATIC)	FiltEstPkCurr_AmpSq_T_u16p0;
	VAR(float32, AUTOMATIC) FiltEstPkCurr_AmpSq_T_f32;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_PeakCurrEst_Per2_CP0_CheckpointReached();
	
	/**** Anti aliasing filter Peak current(slower loop)****/
		EstPkCurr_AmpSq_T_f32 = EstPkCurr_AmpSq_M_f32;
	EstPkCurr_AmpSq_T_u16p0 = FPM_FloatToFixed_m(EstPkCurr_AmpSq_T_f32, u16p0_T); /* PRQA S 4395 */
	
	EstPkCurrFiltSV_AmpSq_M_u16p16 = LPF_SvUpdate_u16InFixKTrunc_m(	EstPkCurr_AmpSq_T_u16p0,
                                      								EstPkCurrFiltSV_AmpSq_M_u16p16, 
                                      								k_EstPkCurrSlowLoopLPFKn_Uls_u16);
                                      								
	FiltEstPkCurr_AmpSq_T_u16p0 = (uint16)LPF_OpUpdate_u16InFixKTrunc_m(EstPkCurrFiltSV_AmpSq_M_u16p16);
	
	FiltEstPkCurr_AmpSq_T_f32 = FPM_FixedToFloat_m(FiltEstPkCurr_AmpSq_T_u16p0, u16p0_T);

  	FiltEstPkCurr_AmpSq_T_f32 = Limit_m(FiltEstPkCurr_AmpSq_T_f32, D_ESTPKCURRLOLMT_AMPSQ_F32, D_ESTPKCURRHILMT_AMPSQ_F32);

	Rte_IWrite_PeakCurrEst_Per2_FiltEstPkCurr_AmpSq_f32(FiltEstPkCurr_AmpSq_T_f32);

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_PeakCurrEst_Per2_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_PEAKCURREST_APPL_CODE
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
