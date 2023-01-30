
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_StaMd_Cfg.h
* Module Description: Configuration file of StaMd module
* Product           : Gen II Plus - EA3.0
* Generator         : artt 2.0.2.0
* Generation Time   : 15.12.2014 10:45:40
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 13 18:34:17 2012
 * %version:          8 %
 * %date_modified:    Tues Oct 28 22:58:46 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 10/10/12   1       LWW       Initial template creation
 * 10/24/12   3       LWW       Added exclude configuration for applications to skip generation
 * 10/27/12   4       LWW       Added configurable NvM Writeall define
 * 05/30/13   5       KJS       Added support for client/server or task/runnable support for DiagMgr calls
 * 06/05/13   6       KJS       Changed prototype for the system state check function.
 * 06/27/13   7	      LWW       Anomaly 5205 fix
 * 12/11/13   8	      BDO       Updates to add configurable parameter: staMdNvMGetErrorStatusAPI               11065
 * 02/03/14   9       BDO       Add FBLTransitionActive to support FDD ES10B v13                               9674 
 * 10/27/14  10       BDO       Anomaly 7307 fix (add ForceToOff_Cnt_M_lgc)                                    12602 
 */

#ifndef AP_STAMD_CFG_H
#define AP_STAMD_CFG_H


/*** Public Part (used by StaMd API) *****************************************/
#include "Std_Types.h"                   /* Standard type definitions      */
#include "Rte_Type.h"                    /* RTE type definitions      */

	#define D_TYPEHDATASIZE_CNT_U16                100U
	#define NVMWRITEALLFUNC                        NvMProxy_WriteAll
	#define NVMGETERRORSTATUS                      NvMProxy_GetErrorStatus	
	
	#define D_STAMD_DIAGMGR_CLIENTSERVER_CALL		STD_OFF
	#define D_DIAGMGR_SHUTDOWN_TASK                 Task_SchM_Trns_9
	
	
	#define BC_STAMD_TOD2MSTOGGLE					STD_OFF
	#define BC_STAMD_TODSTEADYSTATE					STD_ON
	

	#define BC_STAMD_SYSCHKINCOREAPP				STD_OFF
	

	extern VAR(uint32, AP_DIAGMGR_VAR) CloseCheck_Cnt_u32;
	extern VAR(uint8, AP_DIAGMGR_VAR) TypeHData_Cnt_u08[D_TYPEHDATASIZE_CNT_U16];
	
/*** Private Part (used by StaMd.c only) *************************************/
#ifdef STAMD_C

typedef struct {
   	uint8* Start;
	uint32 Size;
} TypeHInfoType_Str;

 
	extern uint8 Lnk_TypeH0_Start;
	extern uint32* Lnk_TypeH0_Size;
	extern uint8 Lnk_TypeH8_Start;
	extern uint32* Lnk_TypeH8_Size;
	
	
	extern VAR(Rte_ModeType_StaMd_Mode, AP_STAMD_VAR) SysCSystemState_Cnt_M_enum;
	extern VAR(uint16, AP_STAMD_VAR) StaMdsSysCFltCntr_Cnt_M_u16;
	extern VAR(Rte_ModeType_StaMd_Mode, AP_STAMD_VAR) SystemState8_Cnt_M_enum;
	extern VAR(uint32, AP_STAMD_VAR) WarmInitMilestoneRqst8_Cnt_M_u32;
	extern uint8 Lnk_TypeH9_Start;
	extern uint32* Lnk_TypeH9_Size;
	
	
	
	extern VAR(boolean, AP_STAMD_VAR) EcuResetActive_Cnt_M_lgc;
	extern VAR(boolean, AP_STAMD_VAR) FBLTransitionActive_Cnt_M_lgc;
	extern VAR(Rte_ModeType_StaMd_Mode, AP_STAMD_VAR) SystemState9_Cnt_M_enum;
	extern VAR(uint32, AP_STAMD_VAR) WarmInitMilestoneRqst9_Cnt_M_u32;
	extern uint8 Lnk_TypeH10_Start;
	extern uint32* Lnk_TypeH10_Size;
	
	
	
	
	extern VAR(boolean, AP_STAMD_VAR) StopTODPerOperation_Cnt_M_lgc;
	extern VAR(Rte_ModeType_StaMd_Mode, AP_STAMD_VAR) SystemState_Cnt_M_enum;
	
	extern VAR(uint32, AP_STAMD_VAR) WarmInitMilestoneRqst_Cnt_M_u32;
	extern CONST(TypeHInfoType_Str, AP_STAMD_CONST) T_TypeHInfo_Cnt_Str[4];
	extern CONSTP2VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC, AP_STAMD_CONST) T_CurrentSystemState_Ptr_enum[3];
	extern CONSTP2VAR(uint32, AUTOMATIC, AP_STAMD_CONST) T_WarmInitMilestoneRqst_Ptr_enum[3];
	extern volatile VAR(uint8, AP_STAMD_VAR) StTrnsVctr_Cnt_D_b08;
	extern VAR(boolean, AP_STAMD_VAR) FinalNvMWriteInProgress_Cnt_M_lgc;
	extern VAR(boolean, AP_STAMD_VAR) TransitionComplete_Cnt_M_lgc;
	extern VAR(boolean, AP_STAMD_VAR) ForceToOff_Cnt_M_lgc;
	extern FUNC(void, DEM_CODE) Dem_Shutdown(void);
	extern FUNC(void, NVM_PUBLIC_CODE) NvMProxy_WriteAll(void);
	extern FUNC(void, RTE_NVMPROXY_APPL_CODE) NvMProxy_GetErrorStatus(UInt8 parg0, P2VAR(NvM_RequestResultType, AUTOMATIC, RTE_NVMPROXY_APPL_VAR) ErrorStatus);
	extern FUNC(void, MCU_CODE) Mcu_PerformReset(void);
	extern FUNC(NxtrDiagMgrStatus, RTE_AP_STAMD_APPL_CODE) SystemStateCheck(	VAR(boolean, AUTOMATIC) FTermActive_Cnt_T_lgc,
																				VAR(boolean, AUTOMATIC) CTermActive_Cnt_T_lgc,
																				VAR(boolean, AUTOMATIC) ATermActive_Cnt_T_lgc,
																				VAR(boolean, AUTOMATIC) RampStatusCmp_Cnt_T_lgc,
																				VAR(boolean, AUTOMATIC) CtrldDmpStsCmp_Cnt_T_lgc,
																				VAR(boolean, AUTOMATIC) TMFTestComplete_Cnt_T_lgc,
																				P2VAR(uint16, AUTOMATIC, AUTOMATIC) SysCFltCntr_Ptr_T_u16);


/* Disable all checkpoints that are not enabled */
#define Rte_Call_StaMd8_Per1_CP0_CheckpointReached()		(void)0 /* Checkpoint disabled */	 
#define Rte_Call_StaMd8_Per1_CP1_CheckpointReached()		(void)0 /* Checkpoint disabled */	 
#define Rte_Call_StaMd9_Per1_CP0_CheckpointReached()		(void)0 /* Checkpoint disabled */	 
#define Rte_Call_StaMd9_Per1_CP1_CheckpointReached()		(void)0 /* Checkpoint disabled */	 
#define Rte_Call_StaMd_Per1_CP0_CheckpointReached()		(void)0 /* Checkpoint disabled */	 
#define Rte_Call_StaMd_Per1_CP1_CheckpointReached()		(void)0 /* Checkpoint disabled */	 
#endif    
#endif /* AP_STAMD_CFG_H */

/*** End of file **************************************************************/
