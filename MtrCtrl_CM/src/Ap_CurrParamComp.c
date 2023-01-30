/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_CurrParamComp.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/MtrCtrl_CM-nzt9hv/MtrCtrl_CM/autosar
 *     SW-C Type:  Ap_CurrParamComp
 *  Generated at:  Wed Nov  6 11:13:41 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_CurrParamComp>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Fri Feb 17 10:00:00 2012
 * %version:          11 %
 * %derived_by:       nzt9hv %
 * %date_modified:    Wed Nov  6 10:32:01 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 08/29/12  5        OT        Added version logging header
 * 11/20/12  6       Selva       Mempmap macros added &FDD Mapping is done	       
 * 11/01/13  7       Selva      Update the input value to the interpolations by using the following:           4245
 *                               IqRef_Amp_T_u9p7=FPM_FloatToFixed_m(Abs_f32_m(IqRef_Amp_T_f32,u9p7_T))	
 * 03/21/13  8 		 Selva      Updated to version 8 FDD SF99 B	                                                   7711	
 * 03/21/13  9 		 Selva      Updated to version 9 FDD SF99
 * 10/21/13  10      Selva      Updated to version 10 FDD SF99 B. Divide by zero fixed                             10050
 * 11/06/13  11       Selva      Updated for V11 of     FDD SF99                                                   10740 
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

#include "Rte_Ap_CurrParamComp.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_CurrParamComp_Cfg.h"
#include "fixmath.h"
#include "Interpolation.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#define MTRCTRL
#include "Ap_MtrCtrl.h"
	
#define D_SQRT3OVR2_ULS_F32					    0.866025403784F
#define  D_MINRRANGE_OHM_F32                      0.005f             
#define  D_MAXRRANGE_OHM_F32                      0.12565f
#define  D_MINKERANGE_VPRADPS_F32                 0.025f
#define  D_MAXKERANGE_VPRADPS_F32                 0.075f
#define  D_CUTEMPESTLOLMT_DEGC_F32                (-50.0f)
#define  D_CUTEMPESTHILMT_DEGC_F32                300.0f
#define  D_MAGTEMPESTLOLMT_DEGC_F32              (-50.0f)
#define  D_MAGTEMPESTHILMT_DEGC_F32                200.0f
#define  D_SITEMPESTLOLMT_DEGC_F32                (-50.0f)
#define  D_SITEMPESTHILMT_DEGC_F32                150.0f

	
#define CURRPARAMCOMP_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
/* Module level variables */
	STATIC VAR(float32, AP_CurrParamComp_VAR_NOINIT) EstKeFF_VpRadpS_M_f32;
	STATIC VAR(float32, AP_CurrParamComp_VAR_NOINIT) EstRFF_Ohm_M_f32;
/* Display variables */
	STATIC volatile VAR(float32, AP_CurrParamComp_VAR_NOINIT) KeSatSclFac_Uls_D_f32;
	STATIC volatile VAR(float32, AP_CurrParamComp_VAR_NOINIT) LqSatSclFac_Uls_D_f32;
	STATIC volatile VAR(float32, AP_CurrParamComp_VAR_NOINIT) LdSatSclFac_Uls_D_f32;
	STATIC volatile VAR(float32, AP_CurrParamComp_VAR_NOINIT) EstRfetFF_Ohm_D_f32;
	STATIC volatile VAR(float32, AP_CurrParamComp_VAR_NOINIT) EstRmtrFF_Ohm_D_f32;
	STATIC volatile VAR(float32, AP_CurrParamComp_VAR_NOINIT) PreLmtEstKe_VpRadpS_D_f32;
	STATIC volatile VAR(float32, AP_CurrParamComp_VAR_NOINIT) PreLmtEstR_Ohm_D_f32;
	STATIC volatile VAR(float32, AP_CurrParamComp_VAR_NOINIT) PreLmtEstLq_Henry_D_f32;
	STATIC volatile VAR(float32, AP_CurrParamComp_VAR_NOINIT) PreLmtEstLd_Henry_D_f32;
	VAR(float32, AP_CurrParamComp_VAR_NOINIT) MtrEstKe_VpRadpS_M_f32[2];
#define CURRPARAMCOMP_STOP_SEC_VAR_CLEARED_32
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
 * Record Types:
 * =============
 * EOLNomMtrParamType: Record with elements
 *   NomKe_VpRadpS_f32 of type Float
 *   NomRmtr_Ohm_f32 of type Float
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


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   EOLNomMtrParamType *Rte_Pim_EOLNomMtrParam(void)
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_CURRPARAMCOMP_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CurrParamComp_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_CurrParamComp_Init_EstKe_VpRadpS_f32(Float data)
 *   Float *Rte_IWriteRef_CurrParamComp_Init_EstKe_VpRadpS_f32(void)
 *   void Rte_IWrite_CurrParamComp_Init_EstLd_Henry_f32(Float data)
 *   Float *Rte_IWriteRef_CurrParamComp_Init_EstLd_Henry_f32(void)
 *   void Rte_IWrite_CurrParamComp_Init_EstLq_Henry_f32(Float data)
 *   Float *Rte_IWriteRef_CurrParamComp_Init_EstLq_Henry_f32(void)
 *   void Rte_IWrite_CurrParamComp_Init_EstR_Ohm_f32(Float data)
 *   Float *Rte_IWriteRef_CurrParamComp_Init_EstR_Ohm_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) CurrParamComp_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CurrParamComp_Init
 *********************************************************************************************************************/

	VAR(float32, AUTOMATIC) NomKe_VpRadpS_T_f32;
	VAR(float32, AUTOMATIC) NomRmtr_Ohm_T_f32;
	NomRmtr_Ohm_T_f32 = Rte_Pim_EOLNomMtrParam()->NomRmtr_Ohm_f32;
	NomKe_VpRadpS_T_f32  = Rte_Pim_EOLNomMtrParam()->NomKe_VpRadpS_f32;
	NomKe_VpRadpS_T_f32 = Limit_m(NomKe_VpRadpS_T_f32, k_MinKeRngLmt_VpRadpS_f32, k_MaxKeRngLmt_VpRadpS_f32);
	NomRmtr_Ohm_T_f32 = Limit_m( NomRmtr_Ohm_T_f32, D_MINRRANGE_OHM_F32, D_MAXRRANGE_OHM_F32);
	Rte_IWrite_CurrParamComp_Init_EstR_Ohm_f32(NomRmtr_Ohm_T_f32);
	Rte_IWrite_CurrParamComp_Init_EstLd_Henry_f32(k_NomLd_Henry_f32);
	Rte_IWrite_CurrParamComp_Init_EstLq_Henry_f32(k_NomLq_Henry_f32);
	Rte_IWrite_CurrParamComp_Init_EstKe_VpRadpS_f32(NomKe_VpRadpS_T_f32);
	MtrEstKe_VpRadpS_M_f32[0] = NomKe_VpRadpS_T_f32;
	MtrEstKe_VpRadpS_M_f32[1] = NomKe_VpRadpS_T_f32;
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CurrParamComp_Per1
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
 *   Float Rte_IRead_CurrParamComp_Per1_MtrCurrDaxRef_Amp_f32(void)
 *   Float Rte_IRead_CurrParamComp_Per1_MtrCurrQaxRef_Amp_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_CurrParamComp_Per1_EstKe_VpRadpS_f32(Float data)
 *   Float *Rte_IWriteRef_CurrParamComp_Per1_EstKe_VpRadpS_f32(void)
 *   void Rte_IWrite_CurrParamComp_Per1_EstLd_Henry_f32(Float data)
 *   Float *Rte_IWriteRef_CurrParamComp_Per1_EstLd_Henry_f32(void)
 *   void Rte_IWrite_CurrParamComp_Per1_EstLq_Henry_f32(Float data)
 *   Float *Rte_IWriteRef_CurrParamComp_Per1_EstLq_Henry_f32(void)
 *   void Rte_IWrite_CurrParamComp_Per1_EstR_Ohm_f32(Float data)
 *   Float *Rte_IWriteRef_CurrParamComp_Per1_EstR_Ohm_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) CurrParamComp_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CurrParamComp_Per1
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) IqRef_Amp_T_f32;
	VAR(float32, AUTOMATIC) IdRef_Amp_T_f32;
	VAR(uint16, AUTOMATIC) KeSatSclFac_Uls_T_u2p14;

	VAR(float32, AUTOMATIC) KeSatSclFac_Uls_T_f32;
	VAR(float32, AUTOMATIC) LqSatSclFac_Uls_T_f32;
	VAR(float32, AUTOMATIC) LdSatSclFac_Uls_T_f32;
	VAR(float32, AUTOMATIC) EstKe_VpRadpS_T_f32;
	VAR(float32, AUTOMATIC) EstR_Ohm_T_f32;
	VAR(float32, AUTOMATIC) EstLq_Henry_T_f32;
	VAR(float32, AUTOMATIC) EstLd_Henry_T_f32;
	VAR(uint16, AUTOMATIC) IqRef_Amp_T_u9p7;
	VAR(uint16, AUTOMATIC) IdRef_Amp_T_u9p7;
	VAR(uint16, AUTOMATIC) LdSatSclFac_Uls_T_u2p14;
	VAR(uint16, AUTOMATIC) LqSatSclFac_Uls_T_u2p14;
	
	

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_CurrParamComp_Per1_CP0_CheckpointReached();
	/**** Reading Inputs ****/
	

	IqRef_Amp_T_f32=Rte_IRead_CurrParamComp_Per1_MtrCurrQaxRef_Amp_f32();
	IdRef_Amp_T_f32=Rte_IRead_CurrParamComp_Per1_MtrCurrDaxRef_Amp_f32();

	
    /**** Feedforward path estimation (Ke) Saturation scale factor ****/	

	IqRef_Amp_T_u9p7=FPM_FloatToFixed_m(Abs_f32_m(IqRef_Amp_T_f32),u9p7_T);

	IdRef_Amp_T_u9p7=FPM_FloatToFixed_m(Abs_f32_m(IdRef_Amp_T_f32), u9p7_T);
	

	KeSatSclFac_Uls_T_u2p14 = IntplVarXY_u16_u16Xu16Y_Cnt(t_KeSatTblX_Amp_u9p7,
                          									t_KeSatTblY_Uls_u2p14,
                          									TableSize_m(t_KeSatTblX_Amp_u9p7), 
                          									IqRef_Amp_T_u9p7);

															
	 /**** Feedforward path estimation (Q axis inductance) Saturation scale factor ****/															
	LdSatSclFac_Uls_T_u2p14 = BilinearXYM_u16_u16Xu16YM_Cnt(IdRef_Amp_T_u9p7,
															IqRef_Amp_T_u9p7,
															t_CurrParamCompDaxRef_Amp_u9p7,
															TableSize_m(t_CurrParamCompDaxRef_Amp_u9p7),
															t_CurrParamCompQaxRef_Amp_u9p7,
															(P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_CurrParamLdSatSclFac_Uls_u2p14,
															TableSize_m(t_CurrParamCompQaxRef_Amp_u9p7));
	
	/**** Feedforward path estimation (D axis inductance) Saturation scale factor ****/	
	LqSatSclFac_Uls_T_u2p14 = BilinearXYM_u16_u16Xu16YM_Cnt(IdRef_Amp_T_u9p7,
															IqRef_Amp_T_u9p7,
															t_CurrParamCompDaxRef_Amp_u9p7,
															TableSize_m(t_CurrParamCompDaxRef_Amp_u9p7),
															t_CurrParamCompQaxRef_Amp_u9p7,
															(P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_CurrParamLqSatSclFac_Uls_u2p14,
															TableSize_m(t_CurrParamCompQaxRef_Amp_u9p7));
   									
	KeSatSclFac_Uls_T_f32 = FPM_FixedToFloat_m(KeSatSclFac_Uls_T_u2p14, u2p14_T);
	LqSatSclFac_Uls_T_f32 = FPM_FixedToFloat_m(LqSatSclFac_Uls_T_u2p14, u2p14_T);
	LdSatSclFac_Uls_T_f32 = FPM_FixedToFloat_m(LdSatSclFac_Uls_T_u2p14, u2p14_T);
	/* Mapping the Saturation scale factor to display variables */
	KeSatSclFac_Uls_D_f32 = KeSatSclFac_Uls_T_f32;
	LqSatSclFac_Uls_D_f32 = LqSatSclFac_Uls_T_f32;
	LdSatSclFac_Uls_D_f32 = LdSatSclFac_Uls_T_f32;
	
	/**** Feedforward path estimation ****/
	EstKe_VpRadpS_T_f32 = (EstKeFF_VpRadpS_M_f32 * KeSatSclFac_Uls_T_f32);
	EstR_Ohm_T_f32 = EstRFF_Ohm_M_f32;
	EstLq_Henry_T_f32 = k_NomLq_Henry_f32 * LqSatSclFac_Uls_T_f32;
	EstLd_Henry_T_f32 = k_NomLd_Henry_f32 * LdSatSclFac_Uls_T_f32;
	
	/*Mapping Output to display variables*/
	PreLmtEstKe_VpRadpS_D_f32 = EstKe_VpRadpS_T_f32;
	PreLmtEstR_Ohm_D_f32 = EstR_Ohm_T_f32;
	PreLmtEstLq_Henry_D_f32 = EstLq_Henry_T_f32;
	PreLmtEstLd_Henry_D_f32 = EstLd_Henry_T_f32;
	/**** Parameter Limits Saturation  ****/	
	EstKe_VpRadpS_T_f32 = Limit_m(EstKe_VpRadpS_T_f32, k_MinKeRngLmt_VpRadpS_f32, k_MaxKeRngLmt_VpRadpS_f32);
	EstR_Ohm_T_f32 = Limit_m(EstR_Ohm_T_f32, k_MinRRngLmt_Ohm_f32, k_MaxRRngLmt_Ohm_f32);
	EstLq_Henry_T_f32 = Limit_m(EstLq_Henry_T_f32, k_MinLqRngLmt_Henry_f32, k_MaxLqRngLmt_Henry_f32);
	EstLd_Henry_T_f32 = Limit_m(EstLd_Henry_T_f32, k_MinLdRngLmt_Henry_f32, k_MaxLdRngLmt_Henry_f32);
	
	/*Writing the outputs */
	Rte_IWrite_CurrParamComp_Per1_EstKe_VpRadpS_f32(EstKe_VpRadpS_T_f32);
	Rte_IWrite_CurrParamComp_Per1_EstR_Ohm_f32(EstR_Ohm_T_f32);
	Rte_IWrite_CurrParamComp_Per1_EstLq_Henry_f32(EstLq_Henry_T_f32);
	Rte_IWrite_CurrParamComp_Per1_EstLd_Henry_f32(EstLd_Henry_T_f32);
	MtrEstKe_VpRadpS_M_f32[(FastDataAccessBufIndex_Cnt_M_u16 & 1u)^1u] = EstKe_VpRadpS_T_f32;
	FastDataAccessBufIndex_Cnt_M_u16 = (FastDataAccessBufIndex_Cnt_M_u16 & 1u)^1u;
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_CurrParamComp_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CurrParamComp_Per2
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
 *   Float Rte_IRead_CurrParamComp_Per2_CuTempEst_DegC_f32(void)
 *   Float Rte_IRead_CurrParamComp_Per2_MagTempEst_DegC_f32(void)
 *   Float Rte_IRead_CurrParamComp_Per2_SiTempEst_DegC_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) CurrParamComp_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CurrParamComp_Per2
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) NomKe_VpRadpS_T_f32;
	VAR(float32, AUTOMATIC) NomRmtr_Ohm_T_f32;
	VAR(float32, AUTOMATIC) CuTempEst_DegC_T_f32;
	VAR(float32, AUTOMATIC) MagTempEst_DegC_T_f32;
	VAR(float32, AUTOMATIC) SiTempEst_DegC_T_f32;
	VAR(float32, AUTOMATIC) EstKeFF_VpRadpS_T_f32;
	VAR(float32, AUTOMATIC) EstRfetFF_Ohm_T_f32;
	VAR(float32, AUTOMATIC) EstRmtrFF_Ohm_T_f32;
	VAR(float32, AUTOMATIC) EstRFF_Ohm_T_f32;

	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_CurrParamComp_Per2_CP0_CheckpointReached();
	/**** Reading Inputs ****/
	NomKe_VpRadpS_T_f32 = Rte_Pim_EOLNomMtrParam()->NomKe_VpRadpS_f32;
	NomRmtr_Ohm_T_f32 = Rte_Pim_EOLNomMtrParam()->NomRmtr_Ohm_f32;
	CuTempEst_DegC_T_f32 = Rte_IRead_CurrParamComp_Per2_CuTempEst_DegC_f32();
	MagTempEst_DegC_T_f32 = Rte_IRead_CurrParamComp_Per2_MagTempEst_DegC_f32();
	SiTempEst_DegC_T_f32 = Rte_IRead_CurrParamComp_Per2_SiTempEst_DegC_f32();
	/**** Resistance Feedforward path estimation ****/
	/*** Limit the EEPROM***/
	NomRmtr_Ohm_T_f32 = Limit_m( NomRmtr_Ohm_T_f32, D_MINRRANGE_OHM_F32, D_MAXRRANGE_OHM_F32);
	NomKe_VpRadpS_T_f32 =  Limit_m(NomKe_VpRadpS_T_f32,D_MINKERANGE_VPRADPS_F32,D_MAXKERANGE_VPRADPS_F32);
	CuTempEst_DegC_T_f32 = Limit_m(CuTempEst_DegC_T_f32,D_CUTEMPESTLOLMT_DEGC_F32, D_CUTEMPESTHILMT_DEGC_F32);
	MagTempEst_DegC_T_f32 = Limit_m(MagTempEst_DegC_T_f32, D_MAGTEMPESTLOLMT_DEGC_F32, D_MAGTEMPESTHILMT_DEGC_F32 );
	SiTempEst_DegC_T_f32 = Limit_m(SiTempEst_DegC_T_f32, D_SITEMPESTLOLMT_DEGC_F32, D_SITEMPESTHILMT_DEGC_F32);
	
	EstKeFF_VpRadpS_T_f32 = NomKe_VpRadpS_T_f32 + ((MagTempEst_DegC_T_f32 - k_NomTemp_DegC_f32) * k_MagThrC_VpRadpSpDegC_f32 * NomKe_VpRadpS_T_f32);
	EstKeFF_VpRadpS_M_f32 = Limit_m(EstKeFF_VpRadpS_T_f32, k_MinKeRngLmt_VpRadpS_f32, k_MaxKeRngLmt_VpRadpS_f32);

	
	EstRfetFF_Ohm_T_f32 = k_NomRfet_Ohm_f32 + ((SiTempEst_DegC_T_f32 - k_NomTemp_DegC_f32) * k_SiThermCoeff_OhmpDegC_f32 * k_NomRfet_Ohm_f32);
	EstRmtrFF_Ohm_T_f32 = NomRmtr_Ohm_T_f32 + ((CuTempEst_DegC_T_f32 - k_NomTemp_DegC_f32) * k_CuThermCoeff_OhmpDegC_f32 * NomRmtr_Ohm_T_f32);

	EstRfetFF_Ohm_D_f32 = EstRfetFF_Ohm_T_f32;
	EstRmtrFF_Ohm_D_f32 = EstRmtrFF_Ohm_T_f32;

	EstRFF_Ohm_T_f32 = EstRfetFF_Ohm_T_f32 + EstRmtrFF_Ohm_T_f32;
	EstRFF_Ohm_M_f32 = Limit_m(EstRFF_Ohm_T_f32, k_MinRRngLmt_Ohm_f32, k_MaxRRngLmt_Ohm_f32);

	/* Configurable End of Runnable Checkpoint */
	Rte_Call_CurrParamComp_Per2_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SCom_EOLNomMtrParam_Get
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Get> of PortPrototype <SCom_EOLNomMtrParam>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void SCom_EOLNomMtrParam_Get(Float *NomKe_VpRadpS_f32, Float *NomRmtr_Ohm_f32)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) SCom_EOLNomMtrParam_Get(P2VAR(Float, AUTOMATIC, RTE_AP_CURRPARAMCOMP_APPL_VAR) NomKe_VpRadpS_f32, P2VAR(Float, AUTOMATIC, RTE_AP_CURRPARAMCOMP_APPL_VAR) NomRmtr_Ohm_f32)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SCom_EOLNomMtrParam_Get
 *********************************************************************************************************************/


	*NomKe_VpRadpS_f32 = Rte_Pim_EOLNomMtrParam()->NomKe_VpRadpS_f32;
	*NomRmtr_Ohm_f32 = Rte_Pim_EOLNomMtrParam()->NomRmtr_Ohm_f32;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SCom_EOLNomMtrParam_Set
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Set> of PortPrototype <SCom_EOLNomMtrParam>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_EOLNomMtrParamBlk_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLNomMtrParamBlk_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void SCom_EOLNomMtrParam_Set(Float NomKe_VpRadpS_f32, Float NomRmtr_Ohm_f32)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_CURRPARAMCOMP_APPL_CODE) SCom_EOLNomMtrParam_Set(Float NomKe_VpRadpS_f32, Float NomRmtr_Ohm_f32)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SCom_EOLNomMtrParam_Set
 *********************************************************************************************************************/

	Rte_Pim_EOLNomMtrParam()->NomKe_VpRadpS_f32 = NomKe_VpRadpS_f32;
	Rte_Pim_EOLNomMtrParam()->NomRmtr_Ohm_f32 = NomRmtr_Ohm_f32;

	(void)Rte_Call_EOLNomMtrParamBlk_WriteBlock(NULL_PTR);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_CURRPARAMCOMP_APPL_CODE
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
