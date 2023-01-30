/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Sa_MtrVel3.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/MtrVel_Digi-nzt9hv1/MtrVel_Digi/autosar
 *     SW-C Type:  Sa_MtrVel3
 *  Generated at:  Thu Aug 29 11:25:21 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Sa_MtrVel3>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Thu Jun 16 14:56:11 2011
 * %version:          3 %
 * %derived_by:       nzt9hv %
 * %date_modified:    Thu Aug 22 12:54:24 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 01/29/13   1      JJW      Initial component   
 * 07/30/13   2      Selva     Updated for UTP and QAC    
  * 8/22/2013 3       Selva    Updated the port interface names/FDDV4
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Sa_MtrVel3.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#define MTRVEL_C

#include "MtrVel_Cfg.h"
#include "Sa_MtrVel.h"	/* Include own header for internal definitions */
#include "fixmath.h"


#define D_BUFFERMASK_CNT_U08					(D_MTRVELOSBUFSZ_CNT_U08 - 1U)

#define MTRVEL3_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
	VAR(uint8,  AUTOMATIC) MtrVel3_OsBufPos_Cnt_M_u08[D_MTRVELOSBUFNUM_CNT_U08];
#define MTRVEL3_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */

#define MTRVEL3_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

	VAR(float32, AUTOMATIC) MtrVel3_PosBuffer_Rad_M_f32[D_MTRVELOSBUFNUM_CNT_U08][D_MTRVELOSBUFSZ_CNT_U08];
	
#define MTRVEL3_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define MTRVEL3_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

	
	VAR(uint16, AUTOMATIC) MtrVel3_TimeBuffer_uS_M_u16p0[D_MTRVELOSBUFNUM_CNT_U08][D_MTRVELOSBUFSZ_CNT_U08];
#define MTRVEL3_STOP_SEC_VAR_CLEARED_16
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
 * Float: D_180OVRPI_ULS_F32 = 57.295779513082
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_2PI_ULS_F32 = 6.2831853071796
 * Float: D_PIOVR180_ULS_F32 = 0.0174532925199
 * Float: D_PI_ULS_F32 = 3.1415926535898
 * Float: D_ZERO_ULS_F32 = 0
 * SInt8: D_ZERO_CNT_S8 = 0
 * UInt16: D_ZERO_CNT_U16 = 0u
 * UInt32: D_ZERO_CNT_U32 = 0u
 * UInt8: D_ZERO_CNT_U8 = 0u
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_SA_MTRVEL3_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: MtrVel3_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_MTRVEL3_APPL_CODE) MtrVel3_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: MtrVel3_Init
 *********************************************************************************************************************/
	VAR(uint8, AUTOMATIC) pos;
	VAR(uint8, AUTOMATIC) buf;
	VAR(uint32, AUTOMATIC) 	MtrPos_SampleTime_uS_T_u32;
	VAR(uint16, AUTOMATIC) 	MtrPos_MechMtrPos_Rev_T_u0p16;
	VAR(float32, AUTOMATIC) MtrVel_PosBuffer_Rad_T_f32;
	
	MtrVel_Read_MechMtrPos1_Rev_u0p16(&MtrPos_MechMtrPos_Rev_T_u0p16);
	MtrVel_Read_MechMtrPos1TimeStamp_uS_u32(&MtrPos_SampleTime_uS_T_u32);
	MtrVel_PosBuffer_Rad_T_f32 =(FPM_FixedToFloat_m(MtrPos_MechMtrPos_Rev_T_u0p16, u0p16_T))*D_2PI_ULS_F32;
	
	
	for (buf = 0u; buf < D_MTRVELOSBUFNUM_CNT_U08; buf++)
	{
		MtrVel3_OsBufPos_Cnt_M_u08[buf] = D_MTRVELOSBUFSZ_CNT_U08 - 1u;
	
		for (pos = 1U; pos < D_MTRVELOSBUFSZ_CNT_U08; pos++)
		{

			MtrVel3_PosBuffer_Rad_M_f32[buf][pos] = MtrVel_PosBuffer_Rad_T_f32;
			MtrVel3_TimeBuffer_uS_M_u16p0[buf][pos] = (uint16)MtrPos_SampleTime_uS_T_u32;
		}
	}
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_SA_MTRVEL3_APPL_CODE
#include "MemMap.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
FUNC(void, SA_MTRVEL_CODE) MtrVel3_Per1(void)
{
	/* In order to ensure minimal run-time, capture local consistent copy of the volatile declared variable to ensure 
	 * the compiler doesn't read the variable on every use throughout this function.
     * Since this function is running in a higher priority context than the process modifying MtrVel_OsBufSelect_Cnt_M_u08,
	 * we don't need to be concerned with the value of MtrVel_OsBufSelect_Cnt_M_u08 changing during this process and this 
	 * function is designed to only funciton properly when MtrVel_OsBufSelect_Cnt_M_u08 is a constant value for the duration
	 * of this function execution.
	 */
	VAR(uint8, AUTOMATIC) BufSelect_Cnt_T_u08 = MtrVel_OsBufSelect_Cnt_M_u08;
	VAR(uint32, AUTOMATIC) 	MtrPos_SampleTime_uS_T_u32;
	VAR(uint16, AUTOMATIC) 	MtrPos_MechMtrPos_Rev_T_u0p16;
	
	MtrVel_Read_MechMtrPos1_Rev_u0p16(&MtrPos_MechMtrPos_Rev_T_u0p16);
	MtrVel_Read_MechMtrPos1TimeStamp_uS_u32(&MtrPos_SampleTime_uS_T_u32);
	
	if (BufSelect_Cnt_T_u08 < D_MTRVELOSBUFNUM_CNT_U08)
	{
		MtrVel3_OsBufPos_Cnt_M_u08[BufSelect_Cnt_T_u08] = (MtrVel3_OsBufPos_Cnt_M_u08[BufSelect_Cnt_T_u08] + 1U) & D_BUFFERMASK_CNT_U08;		
		MtrVel3_PosBuffer_Rad_M_f32[BufSelect_Cnt_T_u08][MtrVel3_OsBufPos_Cnt_M_u08[BufSelect_Cnt_T_u08]] = (FPM_FixedToFloat_m(MtrPos_MechMtrPos_Rev_T_u0p16, u0p16_T))*D_2PI_ULS_F32;
		MtrVel3_TimeBuffer_uS_M_u16p0[BufSelect_Cnt_T_u08][MtrVel3_OsBufPos_Cnt_M_u08[BufSelect_Cnt_T_u08]] = (uint16)MtrPos_SampleTime_uS_T_u32;
	}	
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
