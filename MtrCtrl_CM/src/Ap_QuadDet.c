/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_QuadDet.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/MtrCtrl_VM-nzt9hv/MtrCtrl_VM/autosar
 *     SW-C Type:  Ap_QuadDet
 *  Generated at:  Fri Oct 26 16:23:44 2012
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_QuadDet>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 /* Version Control:
 * Date Created:      Thu Jul 12 11:00:00 2012
 * %version:          9 %
 * %derived_by:       nzt9hv %
 * %date_modified:    Fri Oct 12 10:45:15 2012 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                           SCR #
 * --------  -------  --------  ---------------------------------------------------------------------------  ----------
 *        
 * 09/21/12  7        Selva      Checkpoints added and mempmap macros corrected		                          6243
 * 09/25/12  8       Selva       Mempmap macros error corrected		                          6243
 * 10/26/12	 9       Selva		Integration in MtrCtrl_VM (Refer FDD 06B Ver 4)
 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_QuadDet.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "CalConstants.h"
#include "GlobalMacro.h"
#include "Ap_QuadDet_Cfg.h"
/* Embedded Constants */
#define D_CUMMTRPOSLOLMT_DEG_F32	-11796480.0F
#define D_CUMMTRPOSHILMT_DEG_F32	 11796480.0F
#define D_MTRTRQCMDTOL_MTRNM_F32	     0.00390625F

#define QUADDET_START_SEC_VAR_INIT_32
#include "MemMap.h"

/* Static Variables */
STATIC VAR(float32, AP_QUADRANTDETECT_VAR_INIT) PrevCumMtrPos_Deg_M_f32 = 0.0F;
#define QUADDET_STOP_SEC_VAR_INIT_32
#include "MemMap.h"

#define QUADDET_START_SEC_VAR_INIT_8
#include "MemMap.h"
STATIC VAR(sint8, AP_QUADRANTDETECT_VAR_INIT) PrevInstMtrDir_Cnt_M_s08 = 0;

/* Display Variables */
STATIC volatile VAR(sint8, AP_QUADRANTDETECT_VAR_INIT) MtrTrqCmdSign_Cnt_D_s08 = 1;
#define QUADDET_STOP_SEC_VAR_INIT_8
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
 * Boolean: Boolean (standard type)
 * Float: Real in interval ]-FLT_MAX...FLT_MAX[ with single precision (standard type)
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
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
 * Float: D_2PI_ULS_F32 = 6.2831853071796
 * Float: D_VECUMIN_VOLTS_F32 = 5
 * Float: D_ZERO_ULS_F32 = 0
 * SInt16: D_ZERO_CNT_S16 = 0
 * SInt8: D_ZERO_CNT_S8 = 0
 * UInt8: D_MTRPOLESDIV2_CNT_U8 = 3u
 * UInt8: D_QUADRANT1_CNT_U8 = 1u
 * UInt8: D_QUADRANT2_CNT_U8 = 2u
 * UInt8: D_QUADRANT3_CNT_U8 = 3u
 * UInt8: D_QUADRANT4_CNT_U8 = 4u
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_QUADDET_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: QuadDet_Per1
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
 *   Float Rte_IRead_QuadDet_Per1_MRFCumMtrPos_Deg_f32(void)
 *   Float Rte_IRead_QuadDet_Per1_MRFMtrTrqCmdScl_MtrNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_QuadDet_Per1_InstMtrDir_Cnt_s08(SInt8 data)
 *   SInt8 *Rte_IWriteRef_QuadDet_Per1_InstMtrDir_Cnt_s08(void)
 *   void Rte_IWrite_QuadDet_Per1_MtrQuad_Cnt_u08(UInt8 data)
 *   UInt8 *Rte_IWriteRef_QuadDet_Per1_MtrQuad_Cnt_u08(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_QUADDET_APPL_CODE) QuadDet_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: QuadDet_Per1
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) MtrTrqCmdScl_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) CumMtrPos_Deg_T_f32;
	VAR(float32, AUTOMATIC) DeltaMotPos_Deg_T_f32;
	VAR(float32, AUTOMATIC) CumMtrPosLmt_Deg_T_f32;
	VAR(float32, AUTOMATIC) AbsDeltaMotPos_Deg_T_f32;
	VAR(sint8, AUTOMATIC) SignDeltaMotPos_Cnt_T_s08;
	VAR(uint8, AUTOMATIC) MtrQuad_Cnt_T_u08;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_QuadDet_Per1_CP0_CheckpointReached();

	MtrTrqCmdScl_MtrNm_T_f32 = Rte_IRead_QuadDet_Per1_MRFMtrTrqCmdScl_MtrNm_f32();
	CumMtrPos_Deg_T_f32 = Rte_IRead_QuadDet_Per1_MRFCumMtrPos_Deg_f32();
	
	
	/*** Determine Motor Direction ***/
	
	DeltaMotPos_Deg_T_f32 = CumMtrPos_Deg_T_f32 - PrevCumMtrPos_Deg_M_f32;
	CumMtrPosLmt_Deg_T_f32 = D_CUMMTRPOSHILMT_DEG_F32 - D_CUMMTRPOSLOLMT_DEG_F32;
	
	/* Consider Rollover */
	if( DeltaMotPos_Deg_T_f32 > (CumMtrPosLmt_Deg_T_f32/2.0F))
	{
		DeltaMotPos_Deg_T_f32 -= CumMtrPosLmt_Deg_T_f32;
	}
	else if( DeltaMotPos_Deg_T_f32 < -(CumMtrPosLmt_Deg_T_f32/2.0F) )
	{
		DeltaMotPos_Deg_T_f32 += CumMtrPosLmt_Deg_T_f32;
	}
	else
	{
		
	}
	
	AbsDeltaMotPos_Deg_T_f32 = Abs_f32_m(DeltaMotPos_Deg_T_f32);
	SignDeltaMotPos_Cnt_T_s08 = (sint8)Sign_f32_m(DeltaMotPos_Deg_T_f32);
	
	if( PrevInstMtrDir_Cnt_M_s08 == SignDeltaMotPos_Cnt_T_s08 )
	{
		PrevCumMtrPos_Deg_M_f32 = CumMtrPos_Deg_T_f32;
	}
	else if( AbsDeltaMotPos_Deg_T_f32 >= k_InstMtrDirHyst_Deg_f32 )
	{
		PrevInstMtrDir_Cnt_M_s08 = SignDeltaMotPos_Cnt_T_s08;
		PrevCumMtrPos_Deg_M_f32 = CumMtrPos_Deg_T_f32;
	}
	else
	{
		
	}
	
	
	/*** Determine Instananeous Torque Command Sign ***/
	
	if( Abs_f32_m(MtrTrqCmdScl_MtrNm_T_f32) > D_MTRTRQCMDTOL_MTRNM_F32 )
	{
		MtrTrqCmdSign_Cnt_D_s08 = (sint8)Sign_f32_m(MtrTrqCmdScl_MtrNm_T_f32);
	}
	
	
	/*** Determine Motor Quadrant ***/
	
	if( MtrTrqCmdSign_Cnt_D_s08 == PrevInstMtrDir_Cnt_M_s08 )
	{
		if( 1 == MtrTrqCmdSign_Cnt_D_s08 )
		{
			MtrQuad_Cnt_T_u08 = D_QUADRANT1_CNT_U8;
		}
		else
		{
			MtrQuad_Cnt_T_u08 = D_QUADRANT3_CNT_U8;
		}
	}
	else
	{
		if( 1 == MtrTrqCmdSign_Cnt_D_s08 )
		{
			MtrQuad_Cnt_T_u08 = D_QUADRANT2_CNT_U8;
		}
		else
		{
			MtrQuad_Cnt_T_u08 = D_QUADRANT4_CNT_U8;
		}
	}
	

	Rte_IWrite_QuadDet_Per1_InstMtrDir_Cnt_s08(PrevInstMtrDir_Cnt_M_s08);
	Rte_IWrite_QuadDet_Per1_MtrQuad_Cnt_u08(MtrQuad_Cnt_T_u08);
	
	/* Configurable End of Runnable Checkpoint */
    Rte_Call_QuadDet_Per1_CP1_CheckpointReached();

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_QUADDET_APPL_CODE
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
