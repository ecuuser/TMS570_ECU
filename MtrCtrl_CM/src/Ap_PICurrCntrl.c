/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_PICurrCntrl.c
 *     Workspace:  C:/Users/nzt9hv/Documents/Synergy/ccm_wa/ESG_Dev_65/MtrCtrl_CM-nzt9hv/MtrCtrl_CM/autosar
 *     SW-C Type:  Ap_PICurrCntrl
 *  Generated at:  Tue Apr  7 15:36:15 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_PICurrCntrl>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/*
 * Copyright 2015 Nexteer Automotive
 * Nexteer Confidential
 *
 * ---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu Feb 2 13:41:03 2010
* %version:          14 %
* %derived_by:       nzt9hv %
* %date_modified:    Thu Feb 2 13:41:03 2010
* ******************************************************************************
* CHANGE HISTORY:
*
*  Date      Rev      Author          Change Description               							SCR #
*                                      (MDD Rev & Date)
* -------   -------  --------  -----------------------------------   								----------
* 2/2/12    1.0 	RR      	  Initial Creation                     								N/A
* 3/7/12    2.0		RR			Chnages to ComOffset during offset Srv 								N/A		
* 4/18/12	3.0		RR			Changes for IPM	
* 10/21/12	4		SAH			Assign Phase advance to global interface variable.
* 11/20/12  5	   Selva 		 MtrCurrQaxFinal_Ref is added
								 Outputs are mapped acording to FDD 99B version 4
* 02/24/13  6      Selva      Updated for SF99B -v8 with only changes needed for voltage command 
								integrity check for  torque reasonableness	
 * 03/21/13  7,8 		 Selva      Updated to version 8 FDD SF99 B	                                                   7711	
 * 10/21/13  9       Selva      Updated to version 10 FDD SF99 B                                                 10050
 * 10/21/13  10       Selva      Changed Sqrt to __Sqrt for optimisation                                         10634
 * 11/06/13  11       Selva      Updated for V11 of     FDD SF99                                                   10740 
 * 11/26/13  12       Selva      Updated for V12 of FDD SF99                                                          10950
 * 03/10/15	 13       Selva      Updated for V15 of FDD SF99                                                          12888
 * 08/19/15	 14       Selva      Updated for V17 of FDD SF99, EA3#A283,EA3#1777  fixed                                EA3#2430
 *
******************************************************************************/

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


 Mode Declaration Groups:
 ========================
  StaMd_Mode
    EPS System State mode declaration

 *********************************************************************************************************************/

#include "Rte_Ap_PICurrCntrl.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* MISRA-C:2004 Rule 8.7: This deviation is required to keep the memory map intact.  Rule suppressed by line at each occurrence. */

/* MISRA-C:2004 Rule 10.4: This deviation is required because of Nexteer macro library.  Rule suppressed by line at each occurrence. */

/* MISRA-C:2004 Rule 19.1: This deviation is required for AUTOSAR memory map requirements.  Rule suppressed by line at each occurrence. */


#include "Ap_PICurrCntrl_Cfg.h"
#include "Std_Types.h"
#include "CalConstants.h"
#include "fixmath.h"
#include "GlobalMacro.h"
#include "interpolation.h"
#define MTRCTRL
#include "Ap_MtrCtrl.h"
#include "MtrCtrl_Cfg.h"        

#define D_VECUMAX_VOLTS_F32                      31.0F
#define D_SQRT3OVR2_ULS_F32					    0.866025403784F
#define D_SCALERADTOCNTS_ULS_F32 				10430.3783505F
#define D_REVWITHROUND_ULS_F32					65536.5F
#define D_ROUND_ULS_F32							0.5F
#define D_DEG2RAD_ULS_F32						0.0174532925199F
#define D_GAIN_ULS_F32                          0.5F 
#define D_MTRCTRLISRRATE_MS_F32                 0.000125F

#define PICURRCNTRL_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
/*************************/
/* Variable Definitions  */
/*************************/
/* Module Variables */
VAR(float32, AUTOMATIC) MtrCurrQaxRpl_Amp_M_f32[2];
VAR(float32, AUTOMATIC) MtrCurrQaxCog_Amp_M_f32;
STATIC  volatile VAR (float32, AUTOMATIC) MtrVoltDax_Volt_M_f32[2];                
STATIC  volatile VAR(float32, AUTOMATIC) MtrVoltQax_Volt_M_f32[2];       
STATIC  volatile VAR(float32, AUTOMATIC) MtrCurrQaxFinalRef_Amp_M_f32[2]; 

/* Display Variables */
STATIC volatile	VAR(float32, AP_PICurrCntrl_VAR_NOINIT)  PICurrCntrl_DervLambdaQax_Volt_D_f32;      /* PRQA S 3218 */
STATIC volatile	VAR(float32, AP_PICurrCntrl_VAR_NOINIT)  PICurrCntrl_DervLambdaDax_Volt_D_f32;      /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrCurrQaxError_Amp_D_f32;                 /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrCurrDaxError_Amp_D_f32;                /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltQaxPreLimit_Volt_D_f32;            /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltQaxFinalLimit_Volt_D_f32;        /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltDaxPreLimit_Volt_D_f32;            /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltQaxProp_Volt_D_f32;              /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltDaxProp_Volt_D_f32;            /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_MtrCurrQax_Amp_D_f32;     /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_MtrCurrDax_Amp_D_f32;    /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC) MtrVoltQaxIntAntiWindup_Volt_D_f32;                 /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC) MtrVoltDaxIntAntiWindup_Volt_D_f32;                 /* PRQA S 3218 */

STATIC volatile VAR(float32, AUTOMATIC)  MtrVoltQaxDirectFeedback_Volt_D_f32        ;              /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC)  MtrVoltDaxDirectFeedback_Volt_D_f32        ;              /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC)  MtrVoltQaxDamping_Volt_D_f32		        ;            /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC)  MtrVoltDaxDamping_Volt_D_f32               ;            /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC)  MtrVoltQaxDecouplingfdb_Volt_D_f32         ;            /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC)  MtrVoltDaxDecouplingfdb_Volt_D_f32         ;           /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC)  PICurrCntrl_MtrCurrQaxRefModif_Amp_D_f32   ;        /* PRQA S 3218 */
STATIC volatile VAR(float32, AUTOMATIC)  PICurrCntrl_MtrCurrDaxRefModif_Amp_D_f32   ;        /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT)  MtrCurrQaxTrackErr_Amp_D_f32 ;   /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT)  MtrCurrDaxTrackErr_Amp_D_f32 ;   /* PRQA S 3218 */

STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_MtrVolt_Volt_D_f32                    ;  /* PRQA S 3218 */
STATIC  VAR(float32, AP_PICurrCntrl_VAR_NOINIT)         PICurrCntrl_InverterFailSclFac_Uls_M_f32          ;   /* PRQA S 3218 */
STATIC  VAR(float32, AP_PICurrCntrl_VAR_NOINIT)         PICurrCntrl_CurrSensFailSclFac_Uls_M_f32          ;    /* PRQA S 3218 */
STATIC  VAR(float32, AP_PICurrCntrl_VAR_NOINIT)         PICurrCntrl_MtrCurrDaxSatFluxRatio_Uls_M_f32  	  ;    /* PRQA S 3218 */
STATIC  VAR(float32, AP_PICurrCntrl_VAR_NOINIT)         PICurrCntrl_MtrCurrQaxSatFluxRatio_Uls_M_f32      ;    /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_MtrVoltQaxPreLimit_Volt_D_f32         ; /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_MtrVoltCmdPreLimit_Volt_D_f32 	      ; /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_MtrVoltDaxPreLimit_Volt_D_f32         ; /* PRQA S 3218 */
STATIC VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrCurrQaxPrevIntg_Volt_M_f32                     ;         /* PRQA S 3218 */
STATIC VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrCurrDaxPrevIntg_Volt_M_f32                     ;        /* PRQA S 3218 */

STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT)  MtrVoltDaxError_Volt_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT)  MtrVoltQaxError_Volt_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_VoltInvSatnRatio_Uls_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_VoltSatnRatio_Uls_D_f32;   /* PRQA S 3218 */

STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_MtrVoltQaxFFFilt_Volt_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_MtrVoltVecuFilt_Volt_D_f32; /* PRQA S 3218 */
#define PICURRCNTRL_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define PICURRCNTRL_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(LowPassFiltBilinear_Str, AUTOMATIC)   PICurrCntrl_MtrVecuFilt_M_str;
STATIC VAR(LowPassFiltBilinear_Str, AUTOMATIC)   PICurrCntrl_MtrVoltQaxFFFilt_M_str;
#define PICURRCNTRL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

STATIC FUNC(void, AP_CurrCmd_VAR_NOINIT) CalLowPassFiltBilinearTerm( VAR(float32, AUTOMATIC) Freq_Hz_T_f32  , VAR(float32, AUTOMATIC) TimeCons_Sec_T_f32 , P2VAR(LowPassFiltBilinear_Str, AUTOMATIC, AUTOMATIC) LowPassFiltBilinear_T_Str);
STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) CalLowPassFiltBilinearOut( VAR(float32, AUTOMATIC) Input_Uls_T_f32 , P2VAR(LowPassFiltBilinear_Str, AUTOMATIC, AUTOMATIC ) LowPassFiltBilinear_T_Str);


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


#define RTE_START_SEC_AP_PICURRCNTRL_APPL_CODE
#include "MemMap.h"  /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: PICurrCntrl_Init
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

FUNC(void, RTE_AP_PICURRCNTRL_APPL_CODE) PICurrCntrl_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: PICurrCntrl_Init
 *********************************************************************************************************************/
	PICurrCntrl_MtrCurrDaxSatFluxRatio_Uls_M_f32 =D_ONE_ULS_F32;
	PICurrCntrl_MtrCurrQaxSatFluxRatio_Uls_M_f32 =D_ONE_ULS_F32;

    CalLowPassFiltBilinearTerm(k_MtrVoltVecuFiltKn_Hz_f32, k_PiSamplingTs_Sec_f32 ,&PICurrCntrl_MtrVecuFilt_M_str);
	CalLowPassFiltBilinearTerm(k_MtrVoltQaxFiltFFKn_Hz_f32, k_PiSamplingTs_Sec_f32 ,&PICurrCntrl_MtrVoltQaxFFFilt_M_str);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: PICurrCntrl_Per2
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
 *   Float Rte_IRead_PICurrCntrl_Per2_CorrMtrPosElec_Rev_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_EstKe_VpRadpS_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_EstR_Ohm_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_MRFMtrVel_MtrRadpS_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_MtrCurrDaxRef_Amp_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32(void)
 *   void Rte_IWrite_PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32(void)
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

FUNC(void, RTE_AP_PICURRCNTRL_APPL_CODE) PICurrCntrl_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: PICurrCntrl_Per2
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) EstKe_VpRadpS_T_f32;
	VAR(float32, AUTOMATIC) EstR_Ohm_T_f32;
	VAR(float32, AUTOMATIC) MtrVoltDax_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrVoltQax_Volt_T_f32;
	VAR(float32, AUTOMATIC) MRFMtrVel_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrDaxRef_Amp_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrQaxFinalRef_Amp_T_f32;
	VAR(float32, AUTOMATIC) NomR_Ohm_T_f32;
	VAR(float32, AUTOMATIC) CorrMtrPosElec_Rev_T_f32;
	VAR(float32, AUTOMATIC) CorrMtrPosElec_Rad_T_f32;
	VAR(float32, AUTOMATIC) SinCorrMtrPosElec_Uls_T_f32;
	VAR(float32, AUTOMATIC)  CosCorrMtrPosElec_Uls_T_f32;
	VAR(float32, AUTOMATIC)  DervLambdaQax_Volt_T_f32;
	VAR(float32, AUTOMATIC)  DervLambdaDax_Volt_T_f32;
	VAR(uint16, AUTOMATIC)  ReadBuffer_Cnt_T_u16;
	VAR(uint16, AUTOMATIC)  WriteBuffer_Cnt_T_u16;
	VAR(float32, AUTOMATIC) DervLambdaAlphaDiag_Volt_T_f32;
	VAR(float32, AUTOMATIC) DervLambdaBetaDiag_Volt_T_f32;
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_PICurrCntrl_Per2_CP0_CheckpointReached();
	
	ReadBuffer_Cnt_T_u16 = SlowDataAccessBufIndex_Cnt_M_u16;	
	WriteBuffer_Cnt_T_u16 = (ReadBuffer_Cnt_T_u16 & 1U) ^ 1U;
	SlowDataAccessBufIndex_Cnt_M_u16 = WriteBuffer_Cnt_T_u16;
	
	EstKe_VpRadpS_T_f32= Rte_IRead_PICurrCntrl_Per2_EstKe_VpRadpS_f32();
	EstR_Ohm_T_f32 = Rte_IRead_PICurrCntrl_Per2_EstR_Ohm_f32();
	MRFMtrVel_MtrRadpS_T_f32 = Rte_IRead_PICurrCntrl_Per2_MRFMtrVel_MtrRadpS_f32();
	CorrMtrPosElec_Rev_T_f32 = Rte_IRead_PICurrCntrl_Per2_CorrMtrPosElec_Rev_f32();
	MtrCurrDaxRef_Amp_T_f32 = Rte_IRead_PICurrCntrl_Per2_MtrCurrDaxRef_Amp_f32();
	
	
	MtrVoltDax_Volt_T_f32 = MtrVoltDax_Volt_M_f32[ReadBuffer_Cnt_T_u16];
	MtrVoltQax_Volt_T_f32 = MtrVoltQax_Volt_M_f32[ReadBuffer_Cnt_T_u16];
	MtrCurrQaxFinalRef_Amp_T_f32 = MtrCurrQaxFinalRef_Amp_M_f32[ReadBuffer_Cnt_T_u16];

	
	NomR_Ohm_T_f32 = EstR_Ohm_T_f32 * D_SQRT3OVR2_ULS_F32 ;
	DervLambdaQax_Volt_T_f32 = MtrVoltQax_Volt_T_f32 -((EstKe_VpRadpS_T_f32*MRFMtrVel_MtrRadpS_T_f32) +(MtrCurrQaxFinalRef_Amp_T_f32*NomR_Ohm_T_f32));
	DervLambdaDax_Volt_T_f32 = MtrVoltDax_Volt_T_f32 -(MtrCurrDaxRef_Amp_T_f32*NomR_Ohm_T_f32);
	
	CorrMtrPosElec_Rad_T_f32 = CorrMtrPosElec_Rev_T_f32 *  D_2PI_ULS_F32;
	
	SinCorrMtrPosElec_Uls_T_f32 = sinf(CorrMtrPosElec_Rad_T_f32);
	CosCorrMtrPosElec_Uls_T_f32 = cosf(CorrMtrPosElec_Rad_T_f32);
	
	
	
	DervLambdaAlphaDiag_Volt_T_f32 = (SinCorrMtrPosElec_Uls_T_f32 * DervLambdaQax_Volt_T_f32) +(CosCorrMtrPosElec_Uls_T_f32*DervLambdaDax_Volt_T_f32);
	DervLambdaBetaDiag_Volt_T_f32 = (SinCorrMtrPosElec_Uls_T_f32 * DervLambdaDax_Volt_T_f32) -(DervLambdaQax_Volt_T_f32*CosCorrMtrPosElec_Uls_T_f32);
	
	
	PICurrCntrl_DervLambdaQax_Volt_D_f32 = DervLambdaQax_Volt_T_f32;
	PICurrCntrl_DervLambdaDax_Volt_D_f32 = DervLambdaDax_Volt_T_f32;
	

	

	
	Rte_IWrite_PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32(DervLambdaAlphaDiag_Volt_T_f32);
	Rte_IWrite_PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32(DervLambdaBetaDiag_Volt_T_f32);
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_PICurrCntrl_Per2_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_PICURRCNTRL_APPL_CODE
#include "MemMap.h"  /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/



/*****************************************************************************
 *
 *  Function Name:     PICurrCntrlPer1
 *	
 *  Description:       PICurrCntrl
 *
 *  Inputs:            None
 *
 *  Outputs:           None
 *
 *****************************************************************************/
FUNC(void, PICurrCntrl_CODE) PICurrCntrl_Per1(void)
{
	VAR(float32, AUTOMATIC) MtrCurrQax_Amp_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrDax_Amp_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrQaxRef_Amp_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrDaxRef_Amp_T_f32;
	VAR(float32, AUTOMATIC) PIDaxIntegralGain_Ohm_T_f32;
	VAR(float32, AUTOMATIC) PIDaxPropotionalGain_Ohm_T_f32;
	VAR(float32, AUTOMATIC) PIQaxIntegralGain_Ohm_T_f32;
	VAR(float32, AUTOMATIC) PIQaxPropotionalGain_Ohm_T_f32;
	VAR(float32, AUTOMATIC) ElecPosDelayComp_Rad_T_f32;
	VAR(float32, AUTOMATIC) MtrVoltDaxFF_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrVoltQaxFF_Volt_T_f32;
	VAR(float32, AUTOMATIC) Vecu_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrQaxError_Amp_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrDaxError_Amp_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrQaxProptional_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrDaxProptional_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrQaxIntg_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrDaxIntg_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrVoltSq_VoltSq_T_f32;
	VAR(float32, AUTOMATIC) MtrVoltCmd_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrVoltCmdFinal_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrQaxVoltage_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrDaxVoltage_Volt_T_f32;
	VAR(float32, AUTOMATIC) ModIdx_Uls_T_f32;
	VAR(float32, AUTOMATIC) PhaseAdvance_Rad_T_f32;
	VAR(float32, AUTOMATIC) PhaseAdvanceFinal_Rad_T_f32;
	VAR(uint16, AUTOMATIC) PhaseAdvanceFinal_Rev_T_u0p16;
	VAR(uint16, AUTOMATIC) AbsModIdx_Uls_T_u3p13;
	VAR(uint16, AUTOMATIC) CommOffset_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) FwdDataAcessBuffer_Cnt_T_u16;
	VAR(float32, AUTOMATIC) MtrCurrQaxFinalRef_Amp_T_f32;
	VAR(boolean, AUTOMATIC) ModIdxSrlComSvcDft_Cnt_T_lgc;
	VAR(Rte_ModeType_StaMd_Mode, AP_PICurrCntrl_VAR_NOINIT) SysState_Cnt_T_Enum;
	VAR(uint32, AUTOMATIC) ModIdx_Uls_T_u16p16;
	VAR(float32, AUTOMATIC) MtrDampTermDax_Ohm_T_f32;
	VAR(float32, AUTOMATIC) MtrDampTermQax_Ohm_T_f32;
	VAR(float32, AUTOMATIC) MtrImpedDax_Ohm_T_f32;
	VAR(float32, AUTOMATIC) MtrImpedQax_Ohm_T_f32;
	VAR(float32, AUTOMATIC) MtrVoltQaxDirectFeedback_Volt_T_f32 ;
	VAR(float32, AUTOMATIC) MtrVoltDaxDirectFeedback_Volt_T_f32 ;
	VAR(float32, AUTOMATIC) MtrVoltQaxDamping_Volt_T_f32 	  	;
	VAR(float32, AUTOMATIC) MtrVoltDaxDamping_Volt_T_f32 		;
	VAR(float32, AUTOMATIC) MtrVoltQaxDecouplingfdb_Volt_T_f32 	;
	VAR(float32, AUTOMATIC) MtrVoltDaxDecouplingfdb_Volt_T_f32	;
	VAR(float32, AUTOMATIC) MtrCurrQaxRefModif_Amp_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrDaxMaxVal_Amp_T_f32;
	VAR(float32, AUTOMATIC)  MtrCurrDaxRefModif_Amp_T_f32;
	VAR(boolean, AUTOMATIC) MotCurrLoaMtgtnEn_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) IvtrLoaMtgtnEn_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) MtrCurrQaxCogRpl_Amp_T_f32  	 ;
	VAR(float32, AUTOMATIC) CurrSensFailSclFacBuff_Uls_T_f32 ;
	VAR(float32, AUTOMATIC) VoltInvSatnRatio_Uls_T_f32       ;
	VAR(float32, AUTOMATIC) VoltSatnRatio_Uls_T_f32          ;
	VAR(float32, AUTOMATIC) InverterFailSclFacBuff_Uls_T_f32 ;
	VAR(float32, AUTOMATIC) MtrVoltQaxPreLimit_Volt_T_f32    ;
	VAR(float32, AUTOMATIC) LOAFailSclFacBuff_Uls_T_f32      ;
	VAR(float32, AUTOMATIC) MtrVoltDaxPreLimit_Volt_T_f32    ;
	VAR(float32, AUTOMATIC) SqrdVoltInvSatnRatio_Uls_T_f32   ;

	MtrCntrl_Read_MtrCurrQax_Amp_f32(&MtrCurrQax_Amp_T_f32);
	MtrCntrl_Read_MtrCurrDax_Amp_f32(&MtrCurrDax_Amp_T_f32);
	MtrCntrl_Read_ModIdxSrlComSvcDft_Cnt_lgc(&ModIdxSrlComSvcDft_Cnt_T_lgc);
	MtrCntrl_Read_SysState_Cnt_Enum(&SysState_Cnt_T_Enum);
	FwdDataAcessBuffer_Cnt_T_u16 = (FastDataAccessBufIndex_Cnt_M_u16) ;
	MtrCntrl_Read_MotCurrLoaMtgtnEn_Cnt_lgc(&MotCurrLoaMtgtnEn_Cnt_T_lgc);
	MtrCntrl_Read_IvtrLoaMtgtnEn_Cnt_lgc(&IvtrLoaMtgtnEn_Cnt_T_lgc);

	Vecu_Volt_T_f32 = MtrCtrl_Vecu_Volt_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
	MtrCurrQaxRef_Amp_T_f32=MtrCurrQaxRef_Amp_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
	MtrCurrDaxRef_Amp_T_f32=MtrCurrDaxRef_Amp_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
	PIDaxIntegralGain_Ohm_T_f32= MtrCtrl_MtrDaxIntegralGain_Ohm_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
	PIDaxPropotionalGain_Ohm_T_f32= MtrCtrl_MtrDaxPropotionalGain_Ohm_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
	PIQaxIntegralGain_Ohm_T_f32= MtrCtrl_MtrQaxIntegralGain_Ohm_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
	PIQaxPropotionalGain_Ohm_T_f32=MtrCtrl_MtrQaxPropotionalGain_Ohm_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
	ElecPosDelayComp_Rad_T_f32=MtrPosComputationDelay_Rad_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
	MtrVoltDaxFF_Volt_T_f32=MtrCtrl_MtrVoltDaxFF_Volt_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
	MtrVoltQaxFF_Volt_T_f32=MtrCtrl_MtrVoltQaxFF_Volt_M_f32[FwdDataAcessBuffer_Cnt_T_u16];

	MtrDampTermDax_Ohm_T_f32   = MtrCtrl_MtrDampTermDax_Ohm_M_f32[FwdDataAcessBuffer_Cnt_T_u16] ;
	MtrDampTermQax_Ohm_T_f32   = MtrCtrl_MtrDampTermQax_Ohm_M_f32[FwdDataAcessBuffer_Cnt_T_u16] ;
	MtrImpedDax_Ohm_T_f32      = MtrCtrl_MtrImpedDax_Ohm_M_f32[FwdDataAcessBuffer_Cnt_T_u16] ;
	MtrImpedQax_Ohm_T_f32      = MtrCtrl_MtrImpedQax_Ohm_M_f32[FwdDataAcessBuffer_Cnt_T_u16] ;


	MtrCurrDaxMaxVal_Amp_T_f32 = MtrCtrl_MtrCurrDaxMaxVal_Amp_M_f32[FwdDataAcessBuffer_Cnt_T_u16];


	/*Range limit Vecu */
	if(k_MtrVoltVecuFiltEnable_Cnt_lgc == TRUE)
	{
		Vecu_Volt_T_f32 = CalLowPassFiltBilinearOut(Vecu_Volt_T_f32, &PICurrCntrl_MtrVecuFilt_M_str);
		Vecu_Volt_T_f32 = Limit_m(Vecu_Volt_T_f32, D_VECUMIN_VOLTS_F32, D_VECUMAX_VOLTS_F32);
	}
	PICurrCntrl_MtrVoltVecuFilt_Volt_D_f32 = Vecu_Volt_T_f32;

		
	/* Error Signal Inputs to PI Control blocks */
	/* F01_2_1_QaxisMtrCurrErrorCalc*/
	/* I error Calculation */
	/* MtrCurrQAXErrorCalc*/
	MtrCurrQaxCogRpl_Amp_T_f32       =  MtrCurrQaxRpl_Amp_M_f32[SlowDataAccessBufIndex_Cnt_M_u16] + MtrCurrQaxCog_Amp_M_f32;
	MtrCurrQaxFinalRef_Amp_T_f32  =  MtrCurrQaxRef_Amp_T_f32 - MtrCurrQaxCogRpl_Amp_T_f32;
	MtrCurrQaxRefModif_Amp_T_f32  =  (PICurrCntrl_MtrCurrQaxSatFluxRatio_Uls_M_f32 *  MtrCurrQaxRef_Amp_T_f32);
	PICurrCntrl_MtrCurrQaxRefModif_Amp_D_f32 =  MtrCurrQaxRefModif_Amp_T_f32;
	MtrCurrQaxError_Amp_T_f32     =  MtrCurrQaxRefModif_Amp_T_f32 - (MtrCurrQaxCogRpl_Amp_T_f32 + MtrCurrQax_Amp_T_f32);


	/* F01_2_4_DaxisMtrCurrErrorCalc*/
	/*DAX Error Calc*/
	MtrCurrDaxRefModif_Amp_T_f32 = (MtrCurrDaxRef_Amp_T_f32 * PICurrCntrl_MtrCurrDaxSatFluxRatio_Uls_M_f32) + ((D_ONE_ULS_F32 - PICurrCntrl_MtrCurrDaxSatFluxRatio_Uls_M_f32)*MtrCurrDaxMaxVal_Amp_T_f32);
	PICurrCntrl_MtrCurrDaxRefModif_Amp_D_f32= MtrCurrDaxRefModif_Amp_T_f32;
	MtrCurrDaxError_Amp_T_f32 =  MtrCurrDaxRefModif_Amp_T_f32 - MtrCurrDax_Amp_T_f32;

	MtrCurrQaxError_Amp_D_f32=MtrCurrQaxError_Amp_T_f32;
	MtrCurrDaxError_Amp_D_f32=MtrCurrDaxError_Amp_T_f32;


	/****  F01_2_2_QAxisProportionalIntegralControl****/
	MtrCurrQaxProptional_Volt_T_f32=MtrCurrQaxError_Amp_T_f32*PIQaxPropotionalGain_Ohm_T_f32;

	/**** F01_2_5_QAxisProportionalIntegralControl****/
	MtrCurrQaxIntg_Volt_T_f32=((MtrCurrQaxError_Amp_T_f32*PIQaxIntegralGain_Ohm_T_f32)+MtrCurrQaxPrevIntg_Volt_M_f32);
	MtrCurrQaxPrevIntg_Volt_M_f32=MtrCurrQaxIntg_Volt_T_f32;
	MtrVoltQaxProp_Volt_D_f32=MtrCurrQaxProptional_Volt_T_f32;


	/**** F01_2_5_DAxisProportionalIntegralControl****/

	MtrCurrDaxProptional_Volt_T_f32= MtrCurrDaxError_Amp_T_f32*PIDaxPropotionalGain_Ohm_T_f32;
	MtrVoltDaxProp_Volt_D_f32      = MtrCurrDaxProptional_Volt_T_f32;

	/**** D axis Integral  Control ****/

	MtrCurrDaxIntg_Volt_T_f32     = ((MtrCurrDaxError_Amp_T_f32*PIDaxIntegralGain_Ohm_T_f32) + MtrCurrDaxPrevIntg_Volt_M_f32);
	MtrCurrDaxPrevIntg_Volt_M_f32 = MtrCurrDaxIntg_Volt_T_f32;

	/* The output Dax, Qax must be zero if not in operate state*/
	if(SysState_Cnt_T_Enum != RTE_MODE_StaMd_Mode_OPERATE)
	{
		MtrCurrDaxPrevIntg_Volt_M_f32=D_ZERO_ULS_F32;
		MtrCurrQaxPrevIntg_Volt_M_f32=D_ZERO_ULS_F32;
	}

	/* F01_2_7_DirectFeedbackVoltageComputation*/
	/*** Direct feedback voltage computation***/
	if(k_MtrCtrlFeedbackControlDisable_Cnt_lgc == TRUE)
	{
	   MtrVoltQaxDirectFeedback_Volt_T_f32 = 0.0f;
	   MtrVoltDaxDirectFeedback_Volt_T_f32 = 0.0f;
	   MtrVoltQaxDamping_Volt_T_f32 = 0.0f;
	   MtrVoltDaxDamping_Volt_T_f32 = 0.0f;
	   MtrVoltQaxDecouplingfdb_Volt_T_f32 =0.0f;
	   MtrVoltDaxDecouplingfdb_Volt_T_f32=0.0f;
	}
	else
	{

		if(k_MtrCtrlCurrLoopSecOrTranFcEnable_Cnt_lgc == FALSE)
			{
				MtrVoltQaxDamping_Volt_T_f32 =k_MtrCtrlVirualResQax_Ohm_f32  * MtrCurrQax_Amp_T_f32;
				MtrVoltDaxDamping_Volt_T_f32 =k_MtrCtrlVirualResDax_Ohm_f32  * MtrCurrDax_Amp_T_f32;
			}
		else
			{
				MtrVoltQaxDamping_Volt_T_f32 = MtrDampTermQax_Ohm_T_f32 * MtrCurrQax_Amp_T_f32;
				MtrVoltDaxDamping_Volt_T_f32 = MtrDampTermDax_Ohm_T_f32 * MtrCurrDax_Amp_T_f32;
			}
		MtrVoltDaxDecouplingfdb_Volt_T_f32 = MtrCurrQax_Amp_T_f32* MtrImpedQax_Ohm_T_f32;
		MtrVoltQaxDecouplingfdb_Volt_T_f32 = MtrCurrDax_Amp_T_f32* MtrImpedDax_Ohm_T_f32;

		MtrVoltQaxDirectFeedback_Volt_T_f32 = -MtrVoltQaxDecouplingfdb_Volt_T_f32-MtrVoltQaxDamping_Volt_T_f32;
		MtrVoltDaxDirectFeedback_Volt_T_f32 = MtrVoltDaxDecouplingfdb_Volt_T_f32-MtrVoltDaxDamping_Volt_T_f32;
	}


	   MtrVoltQaxDirectFeedback_Volt_D_f32 = MtrVoltQaxDirectFeedback_Volt_T_f32;
	   MtrVoltDaxDirectFeedback_Volt_D_f32 = MtrVoltDaxDirectFeedback_Volt_T_f32;
	   MtrVoltQaxDamping_Volt_D_f32 = MtrVoltQaxDamping_Volt_T_f32;
	   MtrVoltDaxDamping_Volt_D_f32 =MtrVoltDaxDamping_Volt_T_f32;
	   MtrVoltQaxDecouplingfdb_Volt_D_f32 =MtrVoltQaxDecouplingfdb_Volt_T_f32;
	   MtrVoltDaxDecouplingfdb_Volt_D_f32=MtrVoltDaxDecouplingfdb_Volt_T_f32;


	/*************  F01_2_8_CurrSensAndInvFailOper**********/
	if(MotCurrLoaMtgtnEn_Cnt_T_lgc == TRUE)
	{
		CurrSensFailSclFacBuff_Uls_T_f32 = Limit_m (D_ZERO_ULS_F32 ,(D_MTRCTRLISRRATE_MS_F32 * -k_CLOAFdbackSignalSclFacSlew_UlspS_f32)+ PICurrCntrl_CurrSensFailSclFac_Uls_M_f32, (D_MTRCTRLISRRATE_MS_F32 * k_CLOAFdbackSignalSclFacSlew_UlspS_f32)+PICurrCntrl_CurrSensFailSclFac_Uls_M_f32);
	}
	else
	{
		CurrSensFailSclFacBuff_Uls_T_f32 = Limit_m(D_ONE_ULS_F32 ,(D_MTRCTRLISRRATE_MS_F32 * -k_CLOAFdbackSignalSclFacSlew_UlspS_f32)+ PICurrCntrl_CurrSensFailSclFac_Uls_M_f32, (D_MTRCTRLISRRATE_MS_F32 * k_CLOAFdbackSignalSclFacSlew_UlspS_f32)+PICurrCntrl_CurrSensFailSclFac_Uls_M_f32 );

	}
	PICurrCntrl_CurrSensFailSclFac_Uls_M_f32 =  CurrSensFailSclFacBuff_Uls_T_f32;

	if(IvtrLoaMtgtnEn_Cnt_T_lgc == TRUE)
	{
		InverterFailSclFacBuff_Uls_T_f32 = Limit_m (D_ZERO_ULS_F32 ,(D_MTRCTRLISRRATE_MS_F32 * -k_ILOAFdbackSignalSclFacSlew_UlspS_f32)+ PICurrCntrl_InverterFailSclFac_Uls_M_f32, (D_MTRCTRLISRRATE_MS_F32 * k_ILOAFdbackSignalSclFacSlew_UlspS_f32)+PICurrCntrl_InverterFailSclFac_Uls_M_f32);
	}
	else
	{
		InverterFailSclFacBuff_Uls_T_f32 = Limit_m(D_ONE_ULS_F32 ,(D_MTRCTRLISRRATE_MS_F32 * -k_ILOAFdbackSignalSclFacSlew_UlspS_f32)+ PICurrCntrl_InverterFailSclFac_Uls_M_f32, (D_MTRCTRLISRRATE_MS_F32 * k_ILOAFdbackSignalSclFacSlew_UlspS_f32)+PICurrCntrl_InverterFailSclFac_Uls_M_f32 );

	}

	PICurrCntrl_InverterFailSclFac_Uls_M_f32 =  InverterFailSclFacBuff_Uls_T_f32;

	/********QAxisVoltageSummation**********************/
	LOAFailSclFacBuff_Uls_T_f32 =  InverterFailSclFacBuff_Uls_T_f32*CurrSensFailSclFacBuff_Uls_T_f32;

	/************Else part of the FDD is implemented to skip Dont Care if condition*************/
	if((k_MtrVoltQaxFiltFFEnable_Cnt_lgc==TRUE) && (IvtrLoaMtgtnEn_Cnt_T_lgc==FALSE) &&(MotCurrLoaMtgtnEn_Cnt_T_lgc==FALSE) &&(k_MtrCtrlFeedbackControlDisable_Cnt_lgc == FALSE))
	{
		MtrVoltQaxFF_Volt_T_f32 = CalLowPassFiltBilinearOut(MtrVoltQaxFF_Volt_T_f32 , &PICurrCntrl_MtrVoltQaxFFFilt_M_str); 
	}

	PICurrCntrl_MtrVoltQaxFFFilt_Volt_D_f32 = MtrVoltQaxFF_Volt_T_f32;

	/**** Qax voltage computation and Limit ****/	 
	MtrVoltQaxPreLimit_Volt_T_f32= ((MtrCurrQaxProptional_Volt_T_f32+MtrCurrQaxIntg_Volt_T_f32+MtrVoltQaxDirectFeedback_Volt_T_f32) *LOAFailSclFacBuff_Uls_T_f32) + MtrVoltQaxFF_Volt_T_f32;
	PICurrCntrl_MtrVoltQaxPreLimit_Volt_D_f32=MtrVoltQaxPreLimit_Volt_T_f32;

	/**** Dax voltage computation and Limit****/
	MtrVoltDaxPreLimit_Volt_T_f32=((MtrCurrDaxProptional_Volt_T_f32+MtrCurrDaxIntg_Volt_T_f32+MtrVoltDaxDirectFeedback_Volt_D_f32 )* (LOAFailSclFacBuff_Uls_T_f32)) + MtrVoltDaxFF_Volt_T_f32;
	PICurrCntrl_MtrVoltDaxPreLimit_Volt_D_f32=MtrVoltDaxPreLimit_Volt_T_f32;



	/**** Final motor output command computation and Limit -Final DQ Voltage ****/

	MtrVoltSq_VoltSq_T_f32=((MtrVoltQaxPreLimit_Volt_T_f32*MtrVoltQaxPreLimit_Volt_T_f32)+(MtrVoltDaxPreLimit_Volt_T_f32*MtrVoltDaxPreLimit_Volt_T_f32));
	MtrVoltCmd_Volt_T_f32 =__sqrtf(MtrVoltSq_VoltSq_T_f32);
	PICurrCntrl_MtrVoltCmdPreLimit_Volt_D_f32 = MtrVoltCmd_Volt_T_f32;


	/*VoltSatnRatioCalc*/

	VoltSatnRatio_Uls_T_f32 = MtrVoltCmd_Volt_T_f32 /(Vecu_Volt_T_f32* k_deadtimeVScale_Uls_f32);
	PICurrCntrl_VoltSatnRatio_Uls_D_f32 = VoltSatnRatio_Uls_T_f32;
	if (VoltSatnRatio_Uls_T_f32 > D_ONE_ULS_F32)
	{
		VoltInvSatnRatio_Uls_T_f32 = D_ONE_ULS_F32 / VoltSatnRatio_Uls_T_f32;
	}
	else
	{
		VoltInvSatnRatio_Uls_T_f32 = D_ONE_ULS_F32;
	}
	PICurrCntrl_VoltInvSatnRatio_Uls_D_f32 = VoltInvSatnRatio_Uls_T_f32;

	/*FinalVoltCalc*/
	MtrQaxVoltage_Volt_T_f32 = VoltInvSatnRatio_Uls_T_f32* MtrVoltQaxPreLimit_Volt_T_f32;
	MtrDaxVoltage_Volt_T_f32 = VoltInvSatnRatio_Uls_T_f32* MtrVoltDaxPreLimit_Volt_T_f32 ;
	MtrVoltCmdFinal_Volt_T_f32 = VoltInvSatnRatio_Uls_T_f32 *  MtrVoltCmd_Volt_T_f32;

	PICurrCntrl_MtrVolt_Volt_D_f32 =  MtrVoltCmdFinal_Volt_T_f32;

	ModIdx_Uls_T_f32=(MtrVoltCmdFinal_Volt_T_f32/Vecu_Volt_T_f32);
		
	/*MtrVolt_Volt used in torque Reasonableness */	



	PhaseAdvance_Rad_T_f32=atan2f(MtrVoltDaxPreLimit_Volt_T_f32,MtrVoltQaxPreLimit_Volt_T_f32);
	/*Correct the Calculated Phase Advance*/
	PhaseAdvanceFinal_Rad_T_f32=PhaseAdvance_Rad_T_f32+ElecPosDelayComp_Rad_T_f32;


	if (PhaseAdvanceFinal_Rad_T_f32 < D_ZERO_ULS_F32)
	{
		PhaseAdvanceFinal_Rev_T_u0p16 = (uint16)(uint32)(float32)((PhaseAdvanceFinal_Rad_T_f32 * D_SCALERADTOCNTS_ULS_F32) + D_REVWITHROUND_ULS_F32); /* PRQA S 4395 */
	}
	else
	{
		PhaseAdvanceFinal_Rev_T_u0p16 = (uint16)(uint32)(float32)((PhaseAdvanceFinal_Rad_T_f32 * D_SCALERADTOCNTS_ULS_F32) + D_ROUND_ULS_F32);      /* PRQA S 4395 */
	}

	/* Note: The following code is part of implementation of FDD-15D. */ 	
	AbsModIdx_Uls_T_u3p13 = FPM_FloatToFixed_m(ModIdx_Uls_T_f32, u3p13_T); /* PRQA S 4395 */

	CommOffset_Cnt_T_u16 = IntplVarXY_u16_u16Xu16Y_Cnt(
										 t_CommOffsetTblX_Uls_u3p13,
										 t_CommOffsetTblY_Cnt_u16,
										 TableSize_m(t_CommOffsetTblX_Uls_u3p13), 
										 AbsModIdx_Uls_T_u3p13);
										 

	if (ModIdxSrlComSvcDft_Cnt_T_lgc==TRUE)
	{
			
		ModIdx_Uls_T_f32 = D_ZERO_ULS_F32;
		MtrCntrl_Read_MtrCurrOffComOffset_Cnt_u16(&CommOffset_Cnt_T_u16);
		
	}


	ModIdx_Uls_T_u16p16=FPM_FloatToFixed_m(ModIdx_Uls_T_f32, u16p16_T);  /* PRQA S 4395 */

	SqrdVoltInvSatnRatio_Uls_T_f32 = VoltInvSatnRatio_Uls_T_f32* VoltInvSatnRatio_Uls_T_f32;

	if (k_MtrCurrQaxRefModifDsb_Cnt_lgc == FALSE)
	{

		PICurrCntrl_MtrCurrQaxSatFluxRatio_Uls_M_f32 = (VoltInvSatnRatio_Uls_T_f32 * (D_ONE_ULS_F32 - k_VoltSatQaxPolyCoeff_Uls_f32 )) + (SqrdVoltInvSatnRatio_Uls_T_f32 * k_VoltSatQaxPolyCoeff_Uls_f32);

	}
	else
	{
		PICurrCntrl_MtrCurrQaxSatFluxRatio_Uls_M_f32 = D_ONE_ULS_F32;
	}

	PICurrCntrl_MtrCurrDaxSatFluxRatio_Uls_M_f32 = (VoltInvSatnRatio_Uls_T_f32 * (D_ONE_ULS_F32 - k_VoltSatDaxPolyCoeff_Uls_f32)) + (SqrdVoltInvSatnRatio_Uls_T_f32 * k_VoltSatDaxPolyCoeff_Uls_f32);




	MtrCntrl_Write_MtrCurrQaxFinalRef_Amp_f32(MtrCurrQaxFinalRef_Amp_T_f32);
	MtrCntrl_Write_MtrDaxVoltage_Volt_f32(MtrDaxVoltage_Volt_T_f32);
	MtrCntrl_Write_MtrQaxVoltage_Volt_f32(MtrQaxVoltage_Volt_T_f32);
	MtrCntrl_Write_ModIdx_Uls_u16p16(ModIdx_Uls_T_u16p16);
	MtrCntrl_Write_PhaseAdvanceFinal_Rev_u0p16(PhaseAdvanceFinal_Rev_T_u0p16);
	MtrCntrl_Write_CommOffset_Cnt_u16(CommOffset_Cnt_T_u16);	
	MtrCurrQaxFinalRef_Amp_M_f32[SlowDataAccessBufIndex_Cnt_M_u16]= MtrCurrQaxFinalRef_Amp_T_f32;
	MtrVoltDax_Volt_M_f32[SlowDataAccessBufIndex_Cnt_M_u16] = MtrDaxVoltage_Volt_T_f32;
	MtrVoltQax_Volt_M_f32[SlowDataAccessBufIndex_Cnt_M_u16] = MtrQaxVoltage_Volt_T_f32;


} 

/*****************************************************************************
  * Name:        CalLowPassFiltBilinearTerm
  * Description: Calculate Terms used in low pass filter 
  * Inputs:      Freq_Hz_T_f32			 - Frequency
  *              TimeCons_Sec_T_f32      - TimeConstant
  *				          
  * Outputs:     LowPassFiltBilinear_T_Str      	     - 
					TermN               - Term Numerator
					TermD               - Term Denominator  
  ******************************************************************************/
STATIC FUNC(void, AP_CurrCmd_VAR_NOINIT) CalLowPassFiltBilinearTerm( VAR(float32, AUTOMATIC) Freq_Hz_T_f32  , VAR(float32, AUTOMATIC) TimeCons_Sec_T_f32 , P2VAR(LowPassFiltBilinear_Str, AUTOMATIC, AUTOMATIC) LowPassFiltBilinear_T_Str)
{
  
	  VAR(float32, AUTOMATIC) TimeConst_Uls_T_f32;
	  
	  TimeConst_Uls_T_f32	= 1.0F /(TimeCons_Sec_T_f32 * Freq_Hz_T_f32 * D_PI_ULS_F32);
	  LowPassFiltBilinear_T_Str->TermD_Uls_f32 = 1.0F/(1.0F + TimeConst_Uls_T_f32);
	  LowPassFiltBilinear_T_Str->TermN_Uls_f32 = TimeConst_Uls_T_f32 - 1.0F;
  
}


/*****************************************************************************
  * Name:        CalLowPassFiltBilinearOut
  * Description: Calculate output from low pass filter 
  * Inputs:      Input_Uls_T_f32			 - Input for the filter
  *              LowPassFiltBilinear_T_Str  
  *				          
  * Outputs:     LowPassFiltBilinear_T_Str      	     - 
					
  ******************************************************************************/

STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) CalLowPassFiltBilinearOut( VAR(float32, AUTOMATIC) Input_Uls_T_f32  , P2VAR(LowPassFiltBilinear_Str, AUTOMATIC, AUTOMATIC ) LowPassFiltBilinear_T_Str)
{
	    VAR(float32, AUTOMATIC) Output_Uls_T_f32;
		
	    Output_Uls_T_f32 =  ((Input_Uls_T_f32 + LowPassFiltBilinear_T_Str-> PrevInput_Uls_f32)+ (LowPassFiltBilinear_T_Str->TermN_Uls_f32 * LowPassFiltBilinear_T_Str-> PrevOutput_Uls_f32))* LowPassFiltBilinear_T_Str->TermD_Uls_f32 ;
		LowPassFiltBilinear_T_Str-> PrevInput_Uls_f32  = Input_Uls_T_f32;
		LowPassFiltBilinear_T_Str-> PrevOutput_Uls_f32 = Output_Uls_T_f32;
	    return (Output_Uls_T_f32);
	   
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
