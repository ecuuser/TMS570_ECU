/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_MtrTempEst.c
 *     Workspace:  C:/CM_Synergy/ccm_wa/Working/CBD/MtrTempEst/MtrTempEst/autosar
 *     SW-C Type:  Ap_MtrTempEst
 *  Generated at:  Mon Feb 24 09:26:54 2014
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_MtrTempEst>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Nov 29 18:34:17 2011
 * %version:          23 %
 * %date_modified:    Mon Feb 24 09:03:28 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 12/20/11   7       JJW       Updated template for CBD design 
 * 12/21/11	  9       M. Story  Updated to SF06 0001
 * 01/03/12   10      M. Story  Updated with DeVinci tool
 * 01/11/12   11      M. Story  Corrected initialization of SumCurr_AmpSq_M_f32
 * 02/14/12   12      M. Story  Anomaly 2929 added CuTempEst Rte output
 * 02/20/12   13      M. Story  Anomoly 2940 Changed input to EstPKCurr
 * 03/01/12   14      M. Story  Updated to SF06 0003
 * 03/09/12   15      M. Story  Anomaly 3031 Add AssistMechFilt_DegC_D_f32
 * 05/16/12	  16	  KJS		Updated to SF06 0004															5454
 * 05/23/12	  17	  JJW		Corrected LPF KUpdate Filter execution rate parameter 
 * 09/21/12   18      Selva     Checkpoints added and mempmap macros corrected		                            6236
 * 10/22/12   19      NRAR      Updated to SF06 005                                                            6600
 * 04/11/13   20      Selva     Updated to SF06 006                                                            7829
 * 08/30/13	  21      KMC       Updated output ranges per CR9607; updated module and display variable          9607
 *                                 names per naming conventions; updated input port name per FDD SF-06 v006
 * 11/13/13   22      KMC       Added output limiting in initialization to fix anomaly 5761; corrected 			10813
 *                                 implementation of slew rate limit on AssistMechTempEst to fix anomaly 5569.  10203
 *                                 NOTE that component meets SF06 v007 (v006 to v007 changes affected only
 *                                 the CtrlTemp component; MtrTempEst functionality unchanged)
 * 02/24/14   23      VK		Anomaly 6300 fix(AssistMech Temp Est Initialization)							11465
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_MtrTempEst.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_MtrTempEst_Cfg.h" 
#include "fixmath.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "filters.h"

#define D_MAGTEMPESTLOLMT_DEGC_F32			(-50.0F)
#define D_MAGTEMPESTHILMT_DEGC_F32			150.0F
#define D_CUTEMPESTLOLMT_DEGC_F32			(-50.0F)
#define D_CUTEMPESTHILMT_DEGC_F32			300.0F
#define D_SITEMPESTLOLMT_DEGC_F32			(-50.0F)
#define D_SITEMPESTHILMT_DEGC_F32			200.0F
#define D_AMTEMPESTLOLMT_DEGC_F32			(-50.0F)
#define D_AMTEMPESTHILMT_DEGC_F32			150.0F
#define D_LOOPSPERSEC_CNT_F32				10.0F

#define MTRTEMPEST_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
/* Module Internal Variables */

STATIC VAR(LPF32KSV_Str, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_CuAmbLPFiltSV_Watts_M_str;
STATIC VAR(LPF32KSV_Str, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_MagAmbLPFiltSV_Watts_M_str;
STATIC VAR(LPF32KSV_Str, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_SiAmbLPFiltSV_Watts_M_str;
STATIC VAR(LPF32KSV_Str, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_AsstMechLPFiltSV_Watts_M_str;
#define MTRTEMPEST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


#define MTRTEMPEST_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_MTRTEMPEST_VAR_NOINIT)  MtrTempEst_AssMechInitComp_Cnt_M_lgc;
STATIC VAR(boolean, AP_MTRTEMPEST_VAR_NOINIT)  MtrTempEst_PrevScomTempDataRcvd_Cnt_M_lgc;
#define MTRTEMPEST_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define MTRTEMPEST_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_CuLLFiltSV_DegC_M_f32;
STATIC VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_MagLLFiltSV_DegC_M_f32;
STATIC VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_SiLLFiltSV_DegC_M_f32;
STATIC VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_AMTempEst_DegC_M_f32;
STATIC VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_AssMechFiltSV_DegC_M_f32;
STATIC VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_AssistMechSlew_DegC_M_f32;

/* Display Variable Test Points */
STATIC volatile VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_AmbPwr_Watts_D_f32;
STATIC volatile VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_ScaledAmbTemp_DegC_D_f32;
STATIC volatile VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_ScaledEngTemp_DegC_D_f32;
STATIC volatile VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_EstMech_Watts_D_f32;
STATIC volatile VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_SiCorr_DegC_D_f32;
STATIC volatile VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_MagCorr_DegC_D_f32;
STATIC volatile VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_CuCorr_DegC_D_f32;
STATIC volatile VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_AMCorr_DegC_D_f32;
STATIC volatile VAR(float32, AP_MTRTEMPEST_VAR_NOINIT) MtrTempEst_AssistMechFilt_DegC_D_f32;
#define MTRTEMPEST_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


STATIC FUNC(float32, AP_MTRTEMPEST_CODE) LeadLagFilt(	VAR(float32, AUTOMATIC) InputTemp_DegC_T_f32, 
														CONSTP2VAR(float32, AUTOMATIC, AP_MTRTEMPEST_CONST) FiltSVPtr_DegC_T_f32, 
														VAR(float32, AUTOMATIC) LLFiltKB0_Uls_T_f32, 
                           								VAR(float32, AUTOMATIC) LLFiltKB1_Uls_T_f32, 
                           								VAR(float32, AUTOMATIC) LLFiltKA1_Uls_T_f32);

STATIC FUNC(void, AP_MTRTEMPEST_CODE) LeadLagFiltInit(VAR(float32, AUTOMATIC) CtrlTempFinal_DegC_T_f32,
									VAR(float32, AUTOMATIC) AmbTemp_DegC_T_f32,
									VAR(float32, AUTOMATIC) EngTemp_DegC_T_f32);

STATIC FUNC(void, AP_MTRTEMPEST_CODE) AssMechFiltInit(VAR(float32, AUTOMATIC) AmbTemp_DegC_T_f32,
									VAR(float32, AUTOMATIC) EngTemp_DegC_T_f32);

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
 * Float: D_100MS_SEC_F32 = 0.1
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_MTRTEMPEST_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: MtrTempEst_Init1
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
 *   Float Rte_IRead_MtrTempEst_Init1_AmbTemp_DegC_f32(void)
 *   Float Rte_IRead_MtrTempEst_Init1_CtrlTempFinal_DegC_f32(void)
 *   Float Rte_IRead_MtrTempEst_Init1_EngTemp_DegC_f32(void)
 *   Boolean Rte_IRead_MtrTempEst_Init1_ScomTempDataRcvd_Cnt_lgc(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_MtrTempEst_Init1_AssistMechTempEst_DegC_f32(Float data)
 *   Float *Rte_IWriteRef_MtrTempEst_Init1_AssistMechTempEst_DegC_f32(void)
 *   void Rte_IWrite_MtrTempEst_Init1_CuTempEst_DegC_f32(Float data)
 *   Float *Rte_IWriteRef_MtrTempEst_Init1_CuTempEst_DegC_f32(void)
 *   void Rte_IWrite_MtrTempEst_Init1_MagTempEst_DegC_f32(Float data)
 *   Float *Rte_IWriteRef_MtrTempEst_Init1_MagTempEst_DegC_f32(void)
 *   void Rte_IWrite_MtrTempEst_Init1_SiTempEst_DegC_f32(Float data)
 *   Float *Rte_IWriteRef_MtrTempEst_Init1_SiTempEst_DegC_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_MTRTEMPEST_APPL_CODE) MtrTempEst_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: MtrTempEst_Init1
 *********************************************************************************************************************/
	
	VAR(float32, AUTOMATIC) CtrlTempFinal_DegC_T_f32;
	VAR(float32, AUTOMATIC) AmbTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) EngTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) ScaledEngTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) ScaledAmbTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) AMTempEst_DegC_T_f32;
	VAR(float32, AUTOMATIC) SiTempEst_DegC_T_f32;
	VAR(float32, AUTOMATIC) MagTempEst_DegC_T_f32;
	VAR(float32, AUTOMATIC) CuTempEst_DegC_T_f32;
	VAR(boolean, AUTOMATIC) ScomTempDataRcvd_Cnt_T_lgc;
				
	CtrlTempFinal_DegC_T_f32 = Rte_IRead_MtrTempEst_Init1_CtrlTempFinal_DegC_f32();
	AmbTemp_DegC_T_f32 = Rte_IRead_MtrTempEst_Init1_AmbTemp_DegC_f32();
	EngTemp_DegC_T_f32 = Rte_IRead_MtrTempEst_Init1_EngTemp_DegC_f32();
	ScomTempDataRcvd_Cnt_T_lgc = Rte_IRead_MtrTempEst_Init1_ScomTempDataRcvd_Cnt_lgc();
	
	if ((ScomTempDataRcvd_Cnt_T_lgc == TRUE) && (k_WtAvgTempDFt_Cnt_lgc == FALSE))
	{
		ScaledEngTemp_DegC_T_f32 = EngTemp_DegC_T_f32 * k_EngTempScl_Uls_f32;
		ScaledAmbTemp_DegC_T_f32 = AmbTemp_DegC_T_f32 * k_AmbTempScl_Uls_f32;

		AMTempEst_DegC_T_f32 = ScaledAmbTemp_DegC_T_f32 + ScaledEngTemp_DegC_T_f32;
	}
	else
	{
		AMTempEst_DegC_T_f32 = CtrlTempFinal_DegC_T_f32;
	}

	SiTempEst_DegC_T_f32 = Limit_m(CtrlTempFinal_DegC_T_f32, D_SITEMPESTLOLMT_DEGC_F32, D_SITEMPESTHILMT_DEGC_F32);
	MagTempEst_DegC_T_f32 = Limit_m(CtrlTempFinal_DegC_T_f32, D_MAGTEMPESTLOLMT_DEGC_F32, D_MAGTEMPESTHILMT_DEGC_F32);
	CuTempEst_DegC_T_f32 = Limit_m(CtrlTempFinal_DegC_T_f32, D_CUTEMPESTLOLMT_DEGC_F32, D_CUTEMPESTHILMT_DEGC_F32);
	MtrTempEst_AMTempEst_DegC_M_f32 = Limit_m(AMTempEst_DegC_T_f32, D_AMTEMPESTLOLMT_DEGC_F32, D_AMTEMPESTHILMT_DEGC_F32);
	
	Rte_IWrite_MtrTempEst_Init1_AssistMechTempEst_DegC_f32(MtrTempEst_AMTempEst_DegC_M_f32);
	Rte_IWrite_MtrTempEst_Init1_SiTempEst_DegC_f32(SiTempEst_DegC_T_f32);
	Rte_IWrite_MtrTempEst_Init1_MagTempEst_DegC_f32(MagTempEst_DegC_T_f32);
	Rte_IWrite_MtrTempEst_Init1_CuTempEst_DegC_f32(CuTempEst_DegC_T_f32);

	LeadLagFiltInit (CtrlTempFinal_DegC_T_f32, AmbTemp_DegC_T_f32, EngTemp_DegC_T_f32);

	/* Low pass filter init */
	LPF_KUpdate_f32_m(k_SiAmbLPFKn_Hz_f32, D_100MS_SEC_F32, &MtrTempEst_SiAmbLPFiltSV_Watts_M_str);
	LPF_KUpdate_f32_m(k_MagAmbLPFKn_Hz_f32, D_100MS_SEC_F32, &MtrTempEst_MagAmbLPFiltSV_Watts_M_str);
	LPF_KUpdate_f32_m(k_CuAmbLPFKn_Hz_f32, D_100MS_SEC_F32, &MtrTempEst_CuAmbLPFiltSV_Watts_M_str);
	LPF_KUpdate_f32_m(k_AMAmbLPFKn_Hz_f32, D_100MS_SEC_F32, &MtrTempEst_AsstMechLPFiltSV_Watts_M_str);


	MtrTempEst_AssMechInitComp_Cnt_M_lgc = FALSE;

	MtrTempEst_AssistMechSlew_DegC_M_f32 = (k_AssistMechSlew_DegCpS_f32 / D_LOOPSPERSEC_CNT_F32);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: MtrTempEst_Per1
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
 *   Float Rte_IRead_MtrTempEst_Per1_AmbTemp_DegC_f32(void)
 *   Float Rte_IRead_MtrTempEst_Per1_CtrlTempFinal_DegC_f32(void)
 *   Float Rte_IRead_MtrTempEst_Per1_EngTemp_DegC_f32(void)
 *   Float Rte_IRead_MtrTempEst_Per1_EstPkCurr_AmpSq_f32(void)
 *   Float Rte_IRead_MtrTempEst_Per1_HwVel_HwRadpS_f32(void)
 *   Boolean Rte_IRead_MtrTempEst_Per1_ScomAMDefeat_Cnt_lgc(void)
 *   Boolean Rte_IRead_MtrTempEst_Per1_ScomTempDataRcvd_Cnt_lgc(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_MtrTempEst_Per1_AssistMechTempEst_DegC_f32(Float data)
 *   Float *Rte_IWriteRef_MtrTempEst_Per1_AssistMechTempEst_DegC_f32(void)
 *   void Rte_IWrite_MtrTempEst_Per1_CuTempEst_DegC_f32(Float data)
 *   Float *Rte_IWriteRef_MtrTempEst_Per1_CuTempEst_DegC_f32(void)
 *   void Rte_IWrite_MtrTempEst_Per1_MagTempEst_DegC_f32(Float data)
 *   Float *Rte_IWriteRef_MtrTempEst_Per1_MagTempEst_DegC_f32(void)
 *   void Rte_IWrite_MtrTempEst_Per1_SiTempEst_DegC_f32(Float data)
 *   Float *Rte_IWriteRef_MtrTempEst_Per1_SiTempEst_DegC_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_MTRTEMPEST_APPL_CODE) MtrTempEst_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: MtrTempEst_Per1
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) AmbPwr_Watts_T_f32;
	VAR(float32, AUTOMATIC) SiAmbPwr_Watts_T_f32;
	VAR(float32, AUTOMATIC) MagAmbPwr_Watts_T_f32;
	VAR(float32, AUTOMATIC) CuAmbPwr_Watts_T_f32;
	VAR(float32, AUTOMATIC) EstPkCurr_AmpSq_T_f32;
	VAR(float32, AUTOMATIC)	CtrlTempFinal_DegC_T_f32;
	VAR(float32, AUTOMATIC)	EngTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC)	AmbTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC)	HwVel_HwRadpS_T_f32;
	VAR(boolean, AUTOMATIC)	ScomTempDataRcvd_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) SiLLFiltOut_DegC_T_f32;
	VAR(float32, AUTOMATIC) MagLLFiltOut_DegC_T_f32;
	VAR(float32, AUTOMATIC) CuLLFiltOut_DegC_T_f32;
	VAR(float32, AUTOMATIC) SiTempEst_DegC_T_f32;
	VAR(float32, AUTOMATIC) MagTempEst_DegC_T_f32;
	VAR(float32, AUTOMATIC) CuTempEst_DegC_T_f32;
	VAR(float32, AUTOMATIC) SiTrimTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) MagTrimTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) CuTrimTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) ScaledAmbTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) ScaledEngTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) AsstMechTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) ScaledTempTrim_DegC_T_f32;
	VAR(float32, AUTOMATIC) EstMech_Watts_T_f32;
	VAR(float32, AUTOMATIC) AMCorr_DegC_T_f32;
	VAR(float32, AUTOMATIC) AMTempEst_DegC_T_f32;
	VAR(float32, AUTOMATIC) AMAmbPwr_Watts_T_f32;
	VAR(float32, AUTOMATIC) SiCorr_DegC_T_f32;
	VAR(float32, AUTOMATIC) MagCorr_DegC_T_f32;
	VAR(float32, AUTOMATIC) CuCorr_DegC_T_f32;
	VAR(boolean, AUTOMATIC) AMTempEstDisable_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) InpTempTrim_DegC_T_f32;
    /* Configurable Start of Runnable Checkpoint */
	Rte_Call_MtrTempEst_Per1_CP0_CheckpointReached();
	
	EstPkCurr_AmpSq_T_f32 = Rte_IRead_MtrTempEst_Per1_EstPkCurr_AmpSq_f32();
	CtrlTempFinal_DegC_T_f32 = Rte_IRead_MtrTempEst_Per1_CtrlTempFinal_DegC_f32();
	EngTemp_DegC_T_f32 = Rte_IRead_MtrTempEst_Per1_EngTemp_DegC_f32();
	AmbTemp_DegC_T_f32 = Rte_IRead_MtrTempEst_Per1_AmbTemp_DegC_f32();
	HwVel_HwRadpS_T_f32 = Rte_IRead_MtrTempEst_Per1_HwVel_HwRadpS_f32();
	ScomTempDataRcvd_Cnt_T_lgc = Rte_IRead_MtrTempEst_Per1_ScomTempDataRcvd_Cnt_lgc();
	AMTempEstDisable_Cnt_T_lgc = Rte_IRead_MtrTempEst_Per1_ScomAMDefeat_Cnt_lgc();

	/* START- SF06-(FDD name)Temperature Estimation-
			       (Sub func)Temperature Estimation Sub Function-
				   (Internal func) Delta Compensation ********************************************************************/
	AmbPwr_Watts_T_f32 = EstPkCurr_AmpSq_T_f32 * k_AmbPwrMult_WtspAmpSq_f32;
	MtrTempEst_AmbPwr_Watts_D_f32 = AmbPwr_Watts_T_f32;

	SiAmbPwr_Watts_T_f32 = LPF_OpUpdate_f32_m(AmbPwr_Watts_T_f32, &MtrTempEst_SiAmbLPFiltSV_Watts_M_str);
	MagAmbPwr_Watts_T_f32 = LPF_OpUpdate_f32_m(AmbPwr_Watts_T_f32, &MtrTempEst_MagAmbLPFiltSV_Watts_M_str);
	CuAmbPwr_Watts_T_f32 = LPF_OpUpdate_f32_m(AmbPwr_Watts_T_f32, &MtrTempEst_CuAmbLPFiltSV_Watts_M_str);
	
	SiCorr_DegC_T_f32 = SiAmbPwr_Watts_T_f32 * k_SiAmbMult_DegCpWatt_f32;
	MagCorr_DegC_T_f32 = MagAmbPwr_Watts_T_f32 * k_MagAmbMult_DegCpWatt_f32;
	CuCorr_DegC_T_f32 = CuAmbPwr_Watts_T_f32 * k_CuAmbMult_DegCpWatt_f32;
	
	SiCorr_DegC_T_f32 = Limit_m(SiCorr_DegC_T_f32, -k_SiCorrLmt_DegC_f32, k_SiCorrLmt_DegC_f32);
	MagCorr_DegC_T_f32 = Limit_m(MagCorr_DegC_T_f32, -k_MagCorrLmt_DegC_f32, k_MagCorrLmt_DegC_f32);
	CuCorr_DegC_T_f32 = Limit_m(CuCorr_DegC_T_f32, -k_CuCorrLmt_DegC_f32, k_CuCorrLmt_DegC_f32);
	
	MtrTempEst_SiCorr_DegC_D_f32 = SiCorr_DegC_T_f32;
	MtrTempEst_MagCorr_DegC_D_f32 = MagCorr_DegC_T_f32;
	MtrTempEst_CuCorr_DegC_D_f32 = CuCorr_DegC_T_f32;             											                             							
	/* STOP- SF06-(FDD name)Temperature Estimation-
			       (Sub func)Temperature Estimation Sub Function-
				   (Internal func) Delta Compensation***********************************************************************/
	
	
	/*START- SF06-(FDD name) Temperature Estimation- 
				  (Sub function) Temperature Estimation Subfunction- 
				  (Internal function) Lead/Lag filter func for Motor Circuit Parameter Temperature Estimates(Cfg Option 2) */
	SiTrimTemp_DegC_T_f32 = CtrlTempFinal_DegC_T_f32 + k_TrimTempSi_DegC_f32;
	
	SiLLFiltOut_DegC_T_f32 = LeadLagFilt(	SiTrimTemp_DegC_T_f32,
											&MtrTempEst_SiLLFiltSV_DegC_M_f32,
											k_SiLLFiltKB0_Uls_f32,
											k_SiLLFiltKB1_Uls_f32,
											k_SiLLFiltKA1_Uls_f32);
											
	MagTrimTemp_DegC_T_f32 = CtrlTempFinal_DegC_T_f32 + k_TrimTempMag_DegC_f32;
	
	MagLLFiltOut_DegC_T_f32 = LeadLagFilt(	MagTrimTemp_DegC_T_f32,
											&MtrTempEst_MagLLFiltSV_DegC_M_f32,
											k_MagLLFiltKB0_Uls_f32,
											k_MagLLFiltKB1_Uls_f32,
											k_MagLLFiltKA1_Uls_f32);
											
	CuTrimTemp_DegC_T_f32 = CtrlTempFinal_DegC_T_f32 + k_TrimTempCu_DegC_f32;
	
	CuLLFiltOut_DegC_T_f32 = LeadLagFilt(	CuTrimTemp_DegC_T_f32,
											&MtrTempEst_CuLLFiltSV_DegC_M_f32,
											k_CuLLFiltKB0_Uls_f32,
											k_CuLLFiltKB1_Uls_f32,
											k_CuLLFiltKA1_Uls_f32);
	
	SiTempEst_DegC_T_f32 = SiLLFiltOut_DegC_T_f32 + SiCorr_DegC_T_f32;
	MagTempEst_DegC_T_f32 = MagLLFiltOut_DegC_T_f32 + MagCorr_DegC_T_f32;
	CuTempEst_DegC_T_f32 = CuLLFiltOut_DegC_T_f32 + CuCorr_DegC_T_f32;
	
	SiTempEst_DegC_T_f32 = Limit_m(SiTempEst_DegC_T_f32, D_SITEMPESTLOLMT_DEGC_F32, D_SITEMPESTHILMT_DEGC_F32);
	MagTempEst_DegC_T_f32 = Limit_m(MagTempEst_DegC_T_f32, D_MAGTEMPESTLOLMT_DEGC_F32, D_MAGTEMPESTHILMT_DEGC_F32);
	CuTempEst_DegC_T_f32 = Limit_m(CuTempEst_DegC_T_f32, D_CUTEMPESTLOLMT_DEGC_F32, D_CUTEMPESTHILMT_DEGC_F32);	
	/*STOP- SF06-(FDD name) Temperature Estimation- 
				 (Sub function) Temperature Estimation Subfunction- 
				 (Internal function) Lead/Lag filter func for Motor Circuit Parameter Temperature Estimates(Cfg Option 2) */

	
	if((MtrTempEst_AssMechInitComp_Cnt_M_lgc == FALSE))
	{ /* Temperature estimation function executes for the first time*/
		
		if ((ScomTempDataRcvd_Cnt_T_lgc == TRUE) && (k_WtAvgTempDFt_Cnt_lgc == FALSE))
		{		/*  The filter output is set to  WtAvgTemp
					depending on the status of k_WtAvgTempDft_Uls and ScomTempDataRcvd. */
				AssMechFiltInit(AmbTemp_DegC_T_f32, EngTemp_DegC_T_f32);
				
				
		}
		else
		{		
				/*The filter output is set to either CtrlTemp depending on the status of 
				k_WtAvgTempDft_Uls and ScomTempDataRcvd.*/
				MtrTempEst_AssMechFiltSV_DegC_M_f32 = (CtrlTempFinal_DegC_T_f32 * (k_AMLLFiltPoleA1_Uls_f32 + k_AMLLFiltCoefB1_Uls_f32)) + (k_TrimTempAM_DegC_f32 * k_AMLLFiltCoefB1_Uls_f32);
		}
		/* Initialise the TempRcvd previous values*/
		MtrTempEst_AssMechInitComp_Cnt_M_lgc = TRUE;
		MtrTempEst_PrevScomTempDataRcvd_Cnt_M_lgc = ScomTempDataRcvd_Cnt_T_lgc;
	}
	/* ReInitialise Assist mech LLF based if there is change in ScomTempDataRcvd data received*/
	if ((k_WtAvgTempDFt_Cnt_lgc ==FALSE) &&(MtrTempEst_PrevScomTempDataRcvd_Cnt_M_lgc != ScomTempDataRcvd_Cnt_T_lgc))
	{
		if(ScomTempDataRcvd_Cnt_T_lgc == TRUE)
		{       /* Use WtAvgTemp as input*/
				AssMechFiltInit(AmbTemp_DegC_T_f32, EngTemp_DegC_T_f32);
		}
		else
		{      /* Use CtrlTempFinal as input*/ 
		       MtrTempEst_AssMechFiltSV_DegC_M_f32 = (CtrlTempFinal_DegC_T_f32 * (k_AMLLFiltPoleA1_Uls_f32 + k_AMLLFiltCoefB1_Uls_f32)) + (k_TrimTempAM_DegC_f32 * k_AMLLFiltCoefB1_Uls_f32);
		}
	}

	/*START- SF06- (FDD name)Temperature Estimation- 
				   (Sub func) Temperature Estimation Subfucnction- 
				   (Internal Func) Lead/Lag filter func for AssistMehcnaism temp estimation(Cfg Option 1) ******************/
	ScaledAmbTemp_DegC_T_f32 = AmbTemp_DegC_T_f32 * k_AmbTempScl_Uls_f32;
	MtrTempEst_ScaledAmbTemp_DegC_D_f32 = ScaledAmbTemp_DegC_T_f32;

	ScaledEngTemp_DegC_T_f32 = EngTemp_DegC_T_f32 * k_EngTempScl_Uls_f32;
	MtrTempEst_ScaledEngTemp_DegC_D_f32 = ScaledEngTemp_DegC_T_f32;
	
	ScaledTempTrim_DegC_T_f32 = ScaledAmbTemp_DegC_T_f32 + ScaledEngTemp_DegC_T_f32 + k_TrimTempAM_DegC_f32;
	
	if ((ScomTempDataRcvd_Cnt_T_lgc == TRUE) && (k_WtAvgTempDFt_Cnt_lgc == FALSE))
		{
		InpTempTrim_DegC_T_f32	=	ScaledTempTrim_DegC_T_f32;										
		}
	else
		{
		InpTempTrim_DegC_T_f32 	= 	CtrlTempFinal_DegC_T_f32+ k_TrimTempAM_DegC_f32;
		}
	AsstMechTemp_DegC_T_f32 = LeadLagFilt( InpTempTrim_DegC_T_f32,
												&MtrTempEst_AssMechFiltSV_DegC_M_f32,
												k_AMLLFiltCoefB0_Uls_f32,
												k_AMLLFiltCoefB1_Uls_f32,
												k_AMLLFiltPoleA1_Uls_f32);									
	EstMech_Watts_T_f32 = HwVel_HwRadpS_T_f32 * HwVel_HwRadpS_T_f32 * k_AMDampScl_NmpRadpS_f32;
	MtrTempEst_EstMech_Watts_D_f32 = EstMech_Watts_T_f32;

	AMAmbPwr_Watts_T_f32 = LPF_OpUpdate_f32_m(EstMech_Watts_T_f32, &MtrTempEst_AsstMechLPFiltSV_Watts_M_str);
	
	AMCorr_DegC_T_f32 = AMAmbPwr_Watts_T_f32 * k_AMAmbMult_DegCpWatt_f32;
	AMCorr_DegC_T_f32 = Limit_m(AMCorr_DegC_T_f32, -k_AMCorrLmt_DegC_f32, k_AMCorrLmt_DegC_f32);
	MtrTempEst_AMCorr_DegC_D_f32 = AMCorr_DegC_T_f32;
	AMTempEst_DegC_T_f32 = AsstMechTemp_DegC_T_f32 + AMCorr_DegC_T_f32;

	MtrTempEst_AssistMechFilt_DegC_D_f32 = AMTempEst_DegC_T_f32;
	
	if( TRUE == AMTempEstDisable_Cnt_T_lgc )
	{
		AMTempEst_DegC_T_f32 = k_AMDefaultTemp_DegC_f32;
	}

	AMTempEst_DegC_T_f32 = Limit_m(AMTempEst_DegC_T_f32, 
									(MtrTempEst_AMTempEst_DegC_M_f32 - MtrTempEst_AssistMechSlew_DegC_M_f32), 
									(MtrTempEst_AMTempEst_DegC_M_f32 + MtrTempEst_AssistMechSlew_DegC_M_f32));
								

	/*STOP SF06- (FDD name)Temperature Estimation- 
				 (Sub func) Temperature Estimation Subfucnction- 
				 (Internal Func) Lead/Lag filter func for AssistMehcnaism temp estimation(Cfg Option 1) **********************/	
				   
	MtrTempEst_AMTempEst_DegC_M_f32 = Limit_m(AMTempEst_DegC_T_f32, D_AMTEMPESTLOLMT_DEGC_F32, D_AMTEMPESTHILMT_DEGC_F32);
	
	MtrTempEst_PrevScomTempDataRcvd_Cnt_M_lgc = ScomTempDataRcvd_Cnt_T_lgc;
	Rte_IWrite_MtrTempEst_Per1_AssistMechTempEst_DegC_f32(MtrTempEst_AMTempEst_DegC_M_f32);
	Rte_IWrite_MtrTempEst_Per1_SiTempEst_DegC_f32(SiTempEst_DegC_T_f32);		
	Rte_IWrite_MtrTempEst_Per1_MagTempEst_DegC_f32(MagTempEst_DegC_T_f32);
	Rte_IWrite_MtrTempEst_Per1_CuTempEst_DegC_f32(CuTempEst_DegC_T_f32);
    /* Configurable End of Runnable Checkpoint */
    Rte_Call_MtrTempEst_Per1_CP1_CheckpointReached();


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_MTRTEMPEST_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
STATIC FUNC(float32, AP_MTRTEMPEST_CODE) LeadLagFilt(	VAR(float32, AUTOMATIC) InputTemp_DegC_T_f32, 
														CONSTP2VAR(float32, AUTOMATIC, AP_MTRTEMPEST_CONST) FiltSVPtr_DegC_T_f32, 
														VAR(float32, AUTOMATIC) LLFiltKB0_Uls_T_f32, 
                           								VAR(float32, AUTOMATIC) LLFiltKB1_Uls_T_f32, 
                           								VAR(float32, AUTOMATIC) LLFiltKA1_Uls_T_f32)
{
	VAR(float32, AUTOMATIC) FiltOutput_DegC_T_f32;
	
	FiltOutput_DegC_T_f32 = ((InputTemp_DegC_T_f32 * LLFiltKB0_Uls_T_f32) + *FiltSVPtr_DegC_T_f32);
	
	*FiltSVPtr_DegC_T_f32 = (InputTemp_DegC_T_f32 * LLFiltKB1_Uls_T_f32) + (LLFiltKA1_Uls_T_f32 * FiltOutput_DegC_T_f32);
	
	return(FiltOutput_DegC_T_f32);
}

STATIC FUNC(void, AP_MTRTEMPEST_CODE) LeadLagFiltInit(VAR(float32, AUTOMATIC) CtrlTempFinal_DegC_T_f32,
									VAR(float32, AUTOMATIC) AmbTemp_DegC_T_f32,
									VAR(float32, AUTOMATIC) EngTemp_DegC_T_f32)
{
	MtrTempEst_SiLLFiltSV_DegC_M_f32 = (CtrlTempFinal_DegC_T_f32 * (k_SiLLFiltKA1_Uls_f32 + k_SiLLFiltKB1_Uls_f32)) + (k_TrimTempSi_DegC_f32 * k_SiLLFiltKB1_Uls_f32);
	MtrTempEst_MagLLFiltSV_DegC_M_f32 = (CtrlTempFinal_DegC_T_f32 * (k_MagLLFiltKA1_Uls_f32 + k_MagLLFiltKB1_Uls_f32)) + (k_TrimTempMag_DegC_f32 * k_MagLLFiltKB1_Uls_f32);
	MtrTempEst_CuLLFiltSV_DegC_M_f32 = (CtrlTempFinal_DegC_T_f32 * (k_CuLLFiltKA1_Uls_f32 + k_CuLLFiltKB1_Uls_f32)) + (k_TrimTempCu_DegC_f32 * k_CuLLFiltKB1_Uls_f32);
	AssMechFiltInit(AmbTemp_DegC_T_f32, EngTemp_DegC_T_f32);
}

STATIC FUNC(void, AP_MTRTEMPEST_CODE) AssMechFiltInit(VAR(float32, AUTOMATIC) AmbTemp_DegC_T_f32,
									VAR(float32, AUTOMATIC) EngTemp_DegC_T_f32)
{
	VAR(float32, AUTOMATIC) ScaledEngTemp_DegC_T_f32;
	VAR(float32, AUTOMATIC) ScaledAmbTemp_DegC_T_f32;

	ScaledAmbTemp_DegC_T_f32 = AmbTemp_DegC_T_f32 * k_AmbTempScl_Uls_f32;
	ScaledEngTemp_DegC_T_f32 = EngTemp_DegC_T_f32 * k_EngTempScl_Uls_f32;
	MtrTempEst_AssMechFiltSV_DegC_M_f32 = ScaledAmbTemp_DegC_T_f32 + ScaledEngTemp_DegC_T_f32;
	MtrTempEst_AssMechFiltSV_DegC_M_f32 = (MtrTempEst_AssMechFiltSV_DegC_M_f32 * (k_AMLLFiltPoleA1_Uls_f32 + k_AMLLFiltCoefB1_Uls_f32)) + (k_TrimTempAM_DegC_f32 * k_AMLLFiltCoefB1_Uls_f32);
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
