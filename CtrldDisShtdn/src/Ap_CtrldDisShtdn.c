/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_CtrldDisShtdn.c
 *     Workspace:  C:/SynergyProjects/CBD/CtrldDisShtdn/autosar/Ap_CtrldDisShtdn.dcf
 *     SW-C Type:  Ap_CtrldDisShtdn
 *  Generated at:  Thu Jan 24 16:21:51 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_CtrldDisShtdn>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Tue Jan 03 18:34:17 2012
 * %version:          15 %
 * %date_modified:    Thu Jan 24 16:38:55 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 01/03/12   1       LWW       Initial Creation
 * 01/04/12   2       M. Story  Update to #SF-26
 * 01/19/12   3       M. Story  Corrected values in t_CtrlDmpTmrY_T_u8P8
 * 01/19/12   4       M. Story  Remove extra display variables
 * 01/19/12   5       M. Story  Removed to many
 * 01/19/12   6       M. Story  Added use of FPM_InitFixedPoint_m
 * 05/15/12   7       NRAR      Changed to using CRF Mtr Trq from MRF, fixed units in var names
 * 05/16/12   8       NRAR      Added system mode consideration
 * 06/07/12   9       OT        Updated to SF-26 v003                                                          5609
 * 09/16/12   10      BWL       Added watchdog checkpoints.                                                    6215
 * 09/23/12   12      Selva     Corrected watchdog checkpoints.                                                6215
 * 10/04/12   13      NRAR      Updated to FDD 005                                                             6308
 * 11/12/12   14      BWL       Added redundant output for MRF.                                                6308
 * 01/24/13   15      OT        Updated to SF-26 v006 (changed input/output names)                             7168
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


 Mode Declaration Groups:
 ========================
  StaMd_Mode
    EPS System State mode declaration

 *********************************************************************************************************************/

#include "Rte_Ap_CtrldDisShtdn.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "fixmath.h"
#include "interpolation.h"
#include "GlobalMacro.h"
#include "filters.h"
#include "CalConstants.h"
#include "Ap_CtrldDisShtdn_Cfg.h"


#define D_CNTRLDMPTMRSZ_CNT_U16			2U 
#define D_CTRLDMPRES_MTRNM_F32			0.007813F


#define CTRLDDISSHTDN_START_SEC_VAR_CLEARED_32
#include "MemMap.h"/* PRQA S 5087 */
STATIC VAR(uint32, AUTOMATIC) LastF2Fault_mS_M_u32;
STATIC volatile VAR(float32, AUTOMATIC) CntrlDampVelTrq_MtrNm_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) CntrlDampTrq_MtrNm_D_f32;
#define CTRLDDISSHTDN_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"/* PRQA S 5087 */


#define CTRLDDISSHTDN_START_SEC_VAR_CLEARED_16	
#include "MemMap.h"/* PRQA S 5087 */
STATIC volatile VAR(uint16, AUTOMATIC) CntrlDampElpsdTime_mS_D_u16;
#define CTRLDDISSHTDN_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"/* PRQA S 5087 */

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
 * Float: D_MSECPERSEC_ULS_F32 = 1000.0F
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8F
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8F
 * Float: D_ONE_ULS_F32 = 1.0F
 * Float: D_PIOVR180_ULS_F32 = 0.0174532925199F
 * Float: D_PI_ULS_F32 = 3.1415926535898F
 * Float: D_RADPERREV_ULS_F32 = 6.28318530718F
 * Float: D_VECUMIN_VOLTS_F32 = 5.0F
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
 * UInt16: D_ZERO_CNT_U16 = 0U
 * UInt32: D_ONE_CNT_U32 = 1U
 * UInt32: D_ZERO_CNT_U32 = 0U
 * UInt8: D_MTRPOLESDIV2_CNT_U8 = 3U
 * UInt8: D_ONE_CNT_U8 = 1U
 * UInt8: D_QUADRANT1_CNT_U8 = 1U
 * UInt8: D_QUADRANT2_CNT_U8 = 2U
 * UInt8: D_QUADRANT3_CNT_U8 = 3U
 * UInt8: D_QUADRANT4_CNT_U8 = 4U
 * UInt8: D_ZERO_CNT_U8 = 0U
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_CTRLDDISSHTDN_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CtrldDisShtdn_Per1
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
 *   SInt8 Rte_IRead_CtrldDisShtdn_Per1_AssistAssyPolarity_Cnt_s08(void)
 *   Float Rte_IRead_CtrldDisShtdn_Per1_CRFMtrVel_MtrRadpS_f32(void)
 *   Boolean Rte_IRead_CtrldDisShtdn_Per1_DiagStsF2Active_Cnt_lgc(void)
 *   Float Rte_IRead_CtrldDisShtdn_Per1_SumLimTrqCmd_MtrNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_CtrldDisShtdn_Per1_CntDisMtrTrqCmdCRF_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_CtrldDisShtdn_Per1_CntDisMtrTrqCmdCRF_MtrNm_f32(void)
 *   void Rte_IWrite_CtrldDisShtdn_Per1_CntDisMtrTrqCmdMRF_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_CtrldDisShtdn_Per1_CntDisMtrTrqCmdMRF_MtrNm_f32(void)
 *   void Rte_IWrite_CtrldDisShtdn_Per1_CtrldDmpStsCmp_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_CtrldDisShtdn_Per1_CtrldDmpStsCmp_Cnt_lgc(void)
 *   void Rte_IWrite_CtrldDisShtdn_Per1_SysC_CRFMtrTrqCmd_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_CtrldDisShtdn_Per1_SysC_CRFMtrTrqCmd_MtrNm_f32(void)
 *   void Rte_IWrite_CtrldDisShtdn_Per1_SysC_MRFMtrTrqCmd_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_CtrldDisShtdn_Per1_SysC_MRFMtrTrqCmd_MtrNm_f32(void)
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
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_CTRLDDISSHTDN_APPL_CODE) CtrldDisShtdn_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CtrldDisShtdn_Per1
 *********************************************************************************************************************/
	
	VAR(float32, AUTOMATIC) CRFMtrVelSign_T_f32;
	VAR(float32, AUTOMATIC) AbsCRFMtrVel_T_MtrRadpS_f32;
	VAR(float32, AUTOMATIC) CntrlDampVelTrq_MtrNm_T_f32;
	VAR(uint16,  AUTOMATIC) ElapsedTime_mS_T_u16;
	VAR(boolean, AUTOMATIC) CntrlDampComp_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) DiagStsF2Active_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) CntrlDamp_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) SumLimTrqCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) CRFMtrVel_MtrRadpS_T_f32;
	VAR(uint16,  AUTOMATIC) CntrlDmpMult_Uls_T_u8p8;
	VAR(float32, AUTOMATIC) CntrlDmpMult_Uls_T_f32;
	VAR(sint8,   AUTOMATIC) AssistAssyPolarity_Cnt_T_s08;
	VAR(float32, AUTOMATIC) MRFMtrTrqCmd_MtrNm_T_f32;
	VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC) SysState_Cnt_T_Enum;
	VAR(float32, AUTOMATIC) CRFMtrTrqCmd_MtrNm_T_f32;
	
	VAR(uint16, AUTOMATIC) t_CtrlDmpTmrX_T_u16[D_CNTRLDMPTMRSZ_CNT_U16];
	VAR(uint16, AUTOMATIC) t_CtrlDmpTmrY_T_u8P8[D_CNTRLDMPTMRSZ_CNT_U16];
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_CtrldDisShtdn_Per1_CP0_CheckpointReached();
	
	SysState_Cnt_T_Enum = Rte_Mode_SystemState_Mode();
	
	t_CtrlDmpTmrX_T_u16[0] = k_CtrlDmpTmrBkptOne_mS_u16;
	t_CtrlDmpTmrX_T_u16[1] = k_CtrlDmpTmrBkptTwo_mS_u16;
	t_CtrlDmpTmrY_T_u8P8[0] = FPM_InitFixedPoint_m(1.0, u8p8_T);
	t_CtrlDmpTmrY_T_u8P8[1] = k_CntrlDmpRampEnd_Uls_u8p8;
	
	SumLimTrqCmd_MtrNm_T_f32 = Rte_IRead_CtrldDisShtdn_Per1_SumLimTrqCmd_MtrNm_f32(); 
	CRFMtrVel_MtrRadpS_T_f32 = Rte_IRead_CtrldDisShtdn_Per1_CRFMtrVel_MtrRadpS_f32();
	DiagStsF2Active_Cnt_T_lgc = Rte_IRead_CtrldDisShtdn_Per1_DiagStsF2Active_Cnt_lgc();
	AssistAssyPolarity_Cnt_T_s08 = Rte_IRead_CtrldDisShtdn_Per1_AssistAssyPolarity_Cnt_s08();
	
	
	/*** Compute Damping Torque ***/
	
	CRFMtrVelSign_T_f32 = (float32)Sign_f32_m(CRFMtrVel_MtrRadpS_T_f32);
	AbsCRFMtrVel_T_MtrRadpS_f32 = Abs_f32_m(CRFMtrVel_MtrRadpS_T_f32);		
	
	CntrlDampVelTrq_MtrNm_T_f32 = AbsCRFMtrVel_T_MtrRadpS_f32 * k_F2Damping_MtrNmpRadpS_f32;
	
	CRFMtrVelSign_T_f32 = CRFMtrVelSign_T_f32 * (float32)-1;
	CntrlDampVelTrq_MtrNm_T_f32 = CntrlDampVelTrq_MtrNm_T_f32 * CRFMtrVelSign_T_f32;
	CntrlDampVelTrq_MtrNm_D_f32 = CntrlDampVelTrq_MtrNm_T_f32;
	
	
	
	/*** Controlled Damping Factor ***/
	
	if(TRUE == DiagStsF2Active_Cnt_T_lgc)
	{
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(LastF2Fault_mS_M_u32, &ElapsedTime_mS_T_u16);
	}
	else
	{
		Rte_Call_SystemTime_GetSystemTime_mS_u32(&LastF2Fault_mS_M_u32);
		ElapsedTime_mS_T_u16 =  0U;
	}
	
	if(ElapsedTime_mS_T_u16 > k_CtrlDmpTmrBkptTwo_mS_u16)
	{
		CntrlDmpMult_Uls_T_f32 = D_ZERO_ULS_F32;
	}
	else
	{
		CntrlDmpMult_Uls_T_u8p8 = IntplVarXY_u16_u16Xu16Y_Cnt ( t_CtrlDmpTmrX_T_u16, 
																t_CtrlDmpTmrY_T_u8P8, 
																TableSize_m(t_CtrlDmpTmrX_T_u16), 
																ElapsedTime_mS_T_u16);
		
		CntrlDmpMult_Uls_T_f32 = FPM_FixedToFloat_m(CntrlDmpMult_Uls_T_u8p8, u8p8_T);
	}
	
	CntrlDamp_MtrNm_T_f32 = CntrlDampVelTrq_MtrNm_T_f32 * CntrlDmpMult_Uls_T_f32;
	CntrlDamp_MtrNm_T_f32 = Limit_m(CntrlDamp_MtrNm_T_f32, -k_MaxCtrlDmpLimit_MtrNm_f32, k_MaxCtrlDmpLimit_MtrNm_f32);
	
	CntrlDampTrq_MtrNm_D_f32 = CntrlDamp_MtrNm_T_f32;
	CntrlDampElpsdTime_mS_D_u16 = ElapsedTime_mS_T_u16;
	
	
	
	/*** Switch Output Control ***/
	
	if( (ElapsedTime_mS_T_u16 >= k_CtrlDmpTmrBkptTwo_mS_u16) ||
		( (ElapsedTime_mS_T_u16 > k_CtrlDmpTmrBkptOne_mS_u16) &&
		  (AbsCRFMtrVel_T_MtrRadpS_f32 < k_CtrlDpVelThr_MtrRadpS_f32) ) )
	{
		CntrlDampComp_Cnt_T_lgc = TRUE;
	}
	else
	{
		CntrlDampComp_Cnt_T_lgc = FALSE;
	}
	
	if( (SysState_Cnt_T_Enum != RTE_MODE_StaMd_Mode_OPERATE) ||
		(CntrlDampComp_Cnt_T_lgc == TRUE) )
	{
		CRFMtrTrqCmd_MtrNm_T_f32 = D_ZERO_ULS_F32;
	}
	else if( TRUE == DiagStsF2Active_Cnt_T_lgc )
	{
		CRFMtrTrqCmd_MtrNm_T_f32 = CntrlDamp_MtrNm_T_f32;
	}
	else
	{
		CRFMtrTrqCmd_MtrNm_T_f32 = SumLimTrqCmd_MtrNm_T_f32;
	}
	
	MRFMtrTrqCmd_MtrNm_T_f32 = CRFMtrTrqCmd_MtrNm_T_f32 * ((float32)AssistAssyPolarity_Cnt_T_s08);
	
		
	Rte_IWrite_CtrldDisShtdn_Per1_CntDisMtrTrqCmdMRF_MtrNm_f32(MRFMtrTrqCmd_MtrNm_T_f32);
	Rte_IWrite_CtrldDisShtdn_Per1_CntDisMtrTrqCmdCRF_MtrNm_f32(CRFMtrTrqCmd_MtrNm_T_f32); 
	Rte_IWrite_CtrldDisShtdn_Per1_CtrldDmpStsCmp_Cnt_lgc(CntrlDampComp_Cnt_T_lgc);
	Rte_IWrite_CtrldDisShtdn_Per1_SysC_MRFMtrTrqCmd_MtrNm_f32(MRFMtrTrqCmd_MtrNm_T_f32);
	Rte_IWrite_CtrldDisShtdn_Per1_SysC_CRFMtrTrqCmd_MtrNm_f32(CRFMtrTrqCmd_MtrNm_T_f32);
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_CtrldDisShtdn_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_CTRLDDISSHTDN_APPL_CODE
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
