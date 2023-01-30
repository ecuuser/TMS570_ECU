/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_HwPwUp.c
 *     Workspace:  C:/Users/nzt9hv/Documents/Synergy/ccm_wa/ESG_Dev_65/HwPwUp-nzt9hv1/HwPwUp/autosar
 *     SW-C Type:  Ap_HwPwUp
 *  Generated at:  Wed Jun  4 14:18:45 2014
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_HwPwUp>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Tue Sep 11 12:12:26 2012
 * %version:          6 %
 * %derived_by:       nzt9hv %
 * %date_modified:    Thu Mar 14 13:33:41 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * -------   -------  --------  -------------------------------------------------------------------------------  ------
 * 09/11/12  1        OT        Initial Version (FDD 13B v001)
 * 09/28/12  2        Selva     Checkpoints added and mempmap macros corrected		                             6383
 * 10/24/12  3        OT        Anomaly 3912 - fixed writing outputs in all paths                                6631
 * 11/08/12  4        JJW       Changed k_PgmSpecMask_Cnt_u16 to D_PGMSPECMASK_CNT_U16 (compile-time config)   
 * 06/04/14  6	      Selva     Updated for v5 of FDD and Changed to match the design standards					 12052   
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_HwPwUp.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "CalConstants.h"
#include "Ap_HwPwUp_Cfg.h"

#define D_PWRDISCSTEPAMASK_CNT_U16	0x0001u
#define D_PWRDISCSTEPBMASK_CNT_U16	0x0004u


typedef enum {
	PWRUP_PWRDISCSTEPA = 0U,
	PWRUP_TMFINIT,
	PWRUP_PWRDISCSTEPB,
	PWRUP_MTRDRIVERINIT,
	PWRUP_WARMINITCOMPLETE,
	PWRUP_RUN,
	PWRUP_DISABLE
} PowerUpSequenceType;


#define HWPWUP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(PowerUpSequenceType, AP_HWPWUP_VAR) HwPwUp_PowerUpState_Cnt_M_enum;
#define HWPWUP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


#define HWPWUP_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_HWPWUP_VAR) HwPwUp_PwrDiscATestStart_Cnt_M_lgc;
STATIC VAR(boolean, AP_HWPWUP_VAR) HwPwUp_TMFTestStart_Cnt_M_lgc;
STATIC VAR(boolean, AP_HWPWUP_VAR) HwPwUp_PwrDiscBTestStart_Cnt_M_lgc;
STATIC VAR(boolean, AP_HWPWUP_VAR) HwPwUp_MtrDrvrInitStart_Cnt_M_lgc;
#define HWPWUP_STOP_SEC_VAR_CLEARED_BOOLEAN
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
 *
 * Enumeration Types:
 * ==================
 * StaMd_Users: Enumeration of integer in interval [0...15] with enumerators
 *   STAMD_STOPCTRL (0u)
 *   STAMD_VEHPWRMD (1u)
 *   STAMD_DIAGMGR (2u)
 *   STAMD_PHSDSCNCT (3u)
 *   STAMD_MTRDRVR (4u)
 *   STAMD_TMPRLMON (5u)
 *   STAMD_HWPWUP (6u)
 *   STAMD_MTRPOSDIAG (7u)
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
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_HWPWUP_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: HwPwUp_Per1
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
 *   Boolean Rte_IRead_HwPwUp_Per1_MtrDrvrInitComplete_Cnt_lgc(void)
 *   Boolean Rte_IRead_HwPwUp_Per1_PwrDiscATestComplete_Cnt_lgc(void)
 *   Boolean Rte_IRead_HwPwUp_Per1_PwrDiscBTestComplete_Cnt_lgc(void)
 *   Boolean Rte_IRead_HwPwUp_Per1_TMFTestComplete_Cnt_lgc(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_HwPwUp_Per1_MtrDrvrInitStart_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_HwPwUp_Per1_MtrDrvrInitStart_Cnt_lgc(void)
 *   void Rte_IWrite_HwPwUp_Per1_PwrDiscATestStart_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_HwPwUp_Per1_PwrDiscATestStart_Cnt_lgc(void)
 *   void Rte_IWrite_HwPwUp_Per1_PwrDiscBTestStart_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_HwPwUp_Per1_PwrDiscBTestStart_Cnt_lgc(void)
 *   void Rte_IWrite_HwPwUp_Per1_TMFTestStart_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_HwPwUp_Per1_TMFTestStart_Cnt_lgc(void)
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
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_MilestoneRqst_WarmInitMilestoneComplete(StaMd_Users user)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_HWPWUP_APPL_CODE) HwPwUp_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: HwPwUp_Per1
 *********************************************************************************************************************/
	
	
	VAR(boolean, AUTOMATIC) PwrDiscATestComplete_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) TMFTestComplete_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) PwrDiscBTestComplete_Cnt_T_lgc;
	VAR(boolean, AUTOMATIC) MtrDrvrInitComplete_Cnt_T_lgc;
	
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_HwPwUp_Per1_CP0_CheckpointReached();
	
	
	PwrDiscATestComplete_Cnt_T_lgc = Rte_IRead_HwPwUp_Per1_PwrDiscATestComplete_Cnt_lgc();
	TMFTestComplete_Cnt_T_lgc = Rte_IRead_HwPwUp_Per1_TMFTestComplete_Cnt_lgc();
	PwrDiscBTestComplete_Cnt_T_lgc = Rte_IRead_HwPwUp_Per1_PwrDiscBTestComplete_Cnt_lgc();
	MtrDrvrInitComplete_Cnt_T_lgc = Rte_IRead_HwPwUp_Per1_MtrDrvrInitComplete_Cnt_lgc();
	
	
	switch(HwPwUp_PowerUpState_Cnt_M_enum)
	{
		case PWRUP_PWRDISCSTEPA:
			if( ((D_PGMSPECMASK_CNT_U16 & D_PWRDISCSTEPAMASK_CNT_U16) == D_PWRDISCSTEPAMASK_CNT_U16) ||
				(PwrDiscATestComplete_Cnt_T_lgc == TRUE) )
			{
				HwPwUp_PowerUpState_Cnt_M_enum = PWRUP_TMFINIT;
			}
			else
			{
				HwPwUp_PwrDiscATestStart_Cnt_M_lgc = TRUE;
			}
			break;
		
		case PWRUP_TMFINIT:
			if( TMFTestComplete_Cnt_T_lgc == TRUE )
			{
				HwPwUp_PowerUpState_Cnt_M_enum=PWRUP_PWRDISCSTEPB;
			}
			else
			{
				HwPwUp_TMFTestStart_Cnt_M_lgc = TRUE;
			}
			break;
		
		case PWRUP_PWRDISCSTEPB:
			if( ((D_PGMSPECMASK_CNT_U16 & D_PWRDISCSTEPBMASK_CNT_U16) == D_PWRDISCSTEPBMASK_CNT_U16) ||
				(PwrDiscBTestComplete_Cnt_T_lgc == TRUE) )
			{
				HwPwUp_PowerUpState_Cnt_M_enum=PWRUP_MTRDRIVERINIT;
			}
			else
			{
				HwPwUp_PwrDiscBTestStart_Cnt_M_lgc = TRUE;
			}
			break;
		
		case PWRUP_MTRDRIVERINIT:
			if( MtrDrvrInitComplete_Cnt_T_lgc == TRUE )
			{
				HwPwUp_PowerUpState_Cnt_M_enum=PWRUP_WARMINITCOMPLETE;
			}
			else
			{
				HwPwUp_MtrDrvrInitStart_Cnt_M_lgc = TRUE;
			}
			break;
			
		case PWRUP_WARMINITCOMPLETE:
			HwPwUp_PowerUpState_Cnt_M_enum=PWRUP_RUN;
			(void) Rte_Call_MilestoneRqst_WarmInitMilestoneComplete(STAMD_HWPWUP);
			break;
		
		case PWRUP_RUN:
		case PWRUP_DISABLE:
		default:
			/* do nothing */
			break;
	}
	
	
	Rte_IWrite_HwPwUp_Per1_PwrDiscATestStart_Cnt_lgc(HwPwUp_PwrDiscATestStart_Cnt_M_lgc);
	Rte_IWrite_HwPwUp_Per1_TMFTestStart_Cnt_lgc(HwPwUp_TMFTestStart_Cnt_M_lgc);
	Rte_IWrite_HwPwUp_Per1_PwrDiscBTestStart_Cnt_lgc(HwPwUp_PwrDiscBTestStart_Cnt_M_lgc);
	Rte_IWrite_HwPwUp_Per1_MtrDrvrInitStart_Cnt_lgc(HwPwUp_MtrDrvrInitStart_Cnt_M_lgc);
	
	
	/* Configurable End of Runnable Checkpoint */
    Rte_Call_HwPwUp_Per1_CP1_CheckpointReached();
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: HwPwUp_Trns1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on exiting of Mode <DISABLE> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
 *   - triggered on entering of Mode <WARMINIT> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_HwPwUp_Trns1_MtrDrvrInitStart_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_HwPwUp_Trns1_MtrDrvrInitStart_Cnt_lgc(void)
 *   void Rte_IWrite_HwPwUp_Trns1_PwrDiscATestStart_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_HwPwUp_Trns1_PwrDiscATestStart_Cnt_lgc(void)
 *   void Rte_IWrite_HwPwUp_Trns1_PwrDiscBTestStart_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_HwPwUp_Trns1_PwrDiscBTestStart_Cnt_lgc(void)
 *   void Rte_IWrite_HwPwUp_Trns1_TMFTestStart_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_HwPwUp_Trns1_TMFTestStart_Cnt_lgc(void)
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
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_MilestoneRqst_WarmInitMilestoneNotComplete(StaMd_Users user)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_HWPWUP_APPL_CODE) HwPwUp_Trns1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: HwPwUp_Trns1
 *********************************************************************************************************************/
	
	
	(void) Rte_Call_MilestoneRqst_WarmInitMilestoneNotComplete(STAMD_HWPWUP);
	
	HwPwUp_PowerUpState_Cnt_M_enum = PWRUP_PWRDISCSTEPA;
	
	HwPwUp_MtrDrvrInitStart_Cnt_M_lgc = FALSE;
	Rte_IWrite_HwPwUp_Trns1_MtrDrvrInitStart_Cnt_lgc(FALSE);
	HwPwUp_PwrDiscATestStart_Cnt_M_lgc = FALSE;
	Rte_IWrite_HwPwUp_Trns1_PwrDiscATestStart_Cnt_lgc(FALSE);
	HwPwUp_PwrDiscBTestStart_Cnt_M_lgc = FALSE;
	Rte_IWrite_HwPwUp_Trns1_PwrDiscBTestStart_Cnt_lgc(FALSE);
	HwPwUp_TMFTestStart_Cnt_M_lgc = FALSE;
	Rte_IWrite_HwPwUp_Trns1_TMFTestStart_Cnt_lgc(FALSE);
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: HwPwUp_Trns2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on entering of Mode <DISABLE> of ModeDeclarationGroupPrototype <Mode> of PortPrototype <SystemState>
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

FUNC(void, RTE_AP_HWPWUP_APPL_CODE) HwPwUp_Trns2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: HwPwUp_Trns2
 *********************************************************************************************************************/
	
	
	HwPwUp_PowerUpState_Cnt_M_enum = PWRUP_DISABLE;
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_HWPWUP_APPL_CODE
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
