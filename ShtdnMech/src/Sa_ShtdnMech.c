/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Sa_ShtdnMech.c
 *     Workspace:  C:/SynergyProjects/CBD/ShtdnMech/autosar/Sa_ShtdnMech.dcf
 *     SW-C Type:  Sa_ShtdnMech
 *  Generated at:  Wed Oct 17 10:16:14 2012
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Sa_ShtdnMech>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Tue Jul 24 16:00:00 2012
 * %version:          6 %
 * %derived_by:       nzx5jd %
 * %date_modified:    Wed Oct 17 11:07:02 2012 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                           SCR #
 * --------  -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/25/12  1        OT        Initial Version (ES-18 v001)                                                 5801
 * 07/29/12  2        LWW       Updates to handle disconnects differently
 * 07/29/12  3        LWW       Removed HETPINDIS register writing
 * 08/22/12  4        LWW       Anomaly 3640 Correction
 * 09/27/12	 5	      SSK       Checkpoint added                                                             6363
 * 10/17/12	 6        OT        Implemented FDD 18B v003                                                     6475
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Sa_ShtdnMech.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "n2het_regs.h"
#include "Sa_ShtdnMech_Cfg.h"


#define D_ESMERROUTSTAT_CNT_U08		0x01U
#define D_SYSFAULT2STAT_CNT_U08		0x08U
#define D_GATEDRVRESETSTAT_CNT_U32	0x00080000UL
#define D_NHETPWMSTAT_CNT_U32		0x01540044UL


#define SHTDNMECH_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(uint8,  SA_SHTDNMECH_VAR) ESMErrOutStat_Cnt_D_u08;
STATIC volatile VAR(uint8,  SA_SHTDNMECH_VAR) SysFault2Stat_Cnt_D_u08;
#define SHTDNMECH_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */


#define SHTDNMECH_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(uint32, SA_SHTDNMECH_VAR) GateDrvResetStat_Cnt_D_u32;
STATIC volatile VAR(uint32, SA_SHTDNMECH_VAR) NHETPwmStat_Cnt_D_u32;
#define SHTDNMECH_STOP_SEC_VAR_CLEARED_32
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
 * IoHwAb_BoolType: Integer in interval [0...1]
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
 * UInt32: D_ONE_CNT_U32 = 1U
 * UInt32: D_ZERO_CNT_U32 = 0U
 * UInt8: D_ONE_CNT_U8 = 1U
 * UInt8: D_ZERO_CNT_U8 = 0U
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_SA_SHTDNMECH_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ShtdnMech_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FetDrvReset_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_FetDrvReset_E_NOT_OK
 *   Std_ReturnType Rte_Call_SysFault2_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault2_E_NOT_OK
 *   Std_ReturnType Rte_Call_SysFault3_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_SysFault3_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_SHTDNMECH_APPL_CODE) ShtdnMech_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ShtdnMech_Per1
 *********************************************************************************************************************/
	
	
	VAR(IoHwAb_BoolType, AUTOMATIC) FetDrvReset_Cnt_T_lgc;
	VAR(IoHwAb_BoolType, AUTOMATIC) SysFault2_Cnt_T_lgc;
	VAR(IoHwAb_BoolType, AUTOMATIC) SysFault3_Cnt_T_lgc;
	
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_ShtdnMech_Per1_CP0_CheckpointReached();
	
	
	Rte_Call_FetDrvReset_OP_GET(&FetDrvReset_Cnt_T_lgc);
	Rte_Call_SysFault2_OP_GET(&SysFault2_Cnt_T_lgc);
	Rte_Call_SysFault3_OP_GET(&SysFault3_Cnt_T_lgc);
	
	
	if( SysFault3_Cnt_T_lgc == STD_LOW )
	{
		ESMErrOutStat_Cnt_D_u08 = D_ZERO_CNT_U8;
	}
	else
	{
		ESMErrOutStat_Cnt_D_u08 = D_ESMERROUTSTAT_CNT_U08;
	}
	
	if( SysFault2_Cnt_T_lgc == STD_LOW )
	{
		SysFault2Stat_Cnt_D_u08 = D_ZERO_CNT_U8;
	}
	else
	{
		SysFault2Stat_Cnt_D_u08 = D_SYSFAULT2STAT_CNT_U08;
	}
	
	if( FetDrvReset_Cnt_T_lgc == STD_LOW )
	{
		GateDrvResetStat_Cnt_D_u32 = D_ZERO_CNT_U32;
	}
	else
	{
		GateDrvResetStat_Cnt_D_u32 = D_GATEDRVRESETSTAT_CNT_U32;
	}
	
	NHETPwmStat_Cnt_D_u32 = NHET0->NHETDIR & D_NHETPWMSTAT_CNT_U32;
	
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_ShtdnMech_Per1_CP1_CheckpointReached();
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_SA_SHTDNMECH_APPL_CODE
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
