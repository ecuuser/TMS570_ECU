/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: emptymac.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.18
|
|  Description: empty API macro definitions
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2010 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* double include preventer */
#ifndef _EMPTYMAC_H
#define _EMPTYMAC_H

/* Vector release management */
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif
/* KB begin vrmReleaseNumber (overwritten) */
/* TR:SPMF36:0002 Start */
/* Source release number */
#define osdVrmMajRelNum 5
#define osdVrmMinRelNum 6
/* TR:SPMF36:0002 End */
/* KB end vrmReleaseNumber */
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif


/*******************/
/* Task management */
/*******************/

/* ActivateTask */
#define OS_AT_ENTRY()           
#define OS_AT_EXIT()            
#define OS_AT_START_CRITICAL()
#define OS_AT_END_CRITICAL()

/* TerminateTask */
#define OS_TT_ENTRY()           
#define OS_TT_EXIT()            
#define OS_TT_START_CRITICAL()
#define OS_TT_END_CRITICAL()

/* ChainTask */
#define OS_HT_ENTRY()           
#define OS_HT_EXIT()            
#define OS_HT_START_CRITICAL()
#define OS_HT_END_CRITICAL()

/* Schedule */
#define OS_SH_ENTRY()           
#define OS_SH_EXIT()            
#define OS_SH_START_CRITICAL()
#define OS_SH_END_CRITICAL()

/* osGetTaskID */
#define OS_GI_ENTRY()           
#define OS_GI_EXIT()            
#define OS_GI_START_CRITICAL()
#define OS_GI_END_CRITICAL()
             
/* osGetTaskState */
#define OS_GS_ENTRY()           
#define OS_GS_EXIT()            
#define OS_GS_START_CRITICAL()
#define OS_GS_END_CRITICAL()


/**********************/
/* Interrupt handling */
/**********************/

/* ResumeAllInterrupts */
#define OS_RA_ENTRY()
#define OS_RA_EXIT()
#define OS_RA_START_CRITICAL()
#define OS_RA_END_CRITICAL()

/* SuspendAllInterrupts */
#define OS_PA_ENTRY()
#define OS_PA_EXIT()
#define OS_PA_START_CRITICAL()
#define OS_PA_END_CRITICAL()

/* EnableAllInterrupts */
#define OS_EA_ENTRY()
#define OS_EA_EXIT()
#define OS_EA_START_CRITICAL()
#define OS_EA_END_CRITICAL()
 
/* DisableAllInterrupts */
#define OS_DA_ENTRY()
#define OS_DA_EXIT()
#define OS_DA_START_CRITICAL()
#define OS_DA_END_CRITICAL()

/* ResumeOSInterrupts */
#define OS_RI_ENTRY()
#define OS_RI_EXIT()
#define OS_RI_START_CRITICAL()
#define OS_RI_END_CRITICAL()

/* SuspendOSInterrupts */
#define OS_SI_ENTRY()
#define OS_SI_EXIT()
#define OS_SI_START_CRITICAL()
#define OS_SI_END_CRITICAL()


/***********************/
/* Resource management */
/***********************/

/* GetResource */
#define OS_GR_ENTRY()           
#define OS_GR_EXIT()            
#define OS_GR_START_CRITICAL()
#define OS_GR_END_CRITICAL()

/* ReleaseResource */
#define OS_RR_ENTRY()           
#define OS_RR_EXIT()            
#define OS_RR_START_CRITICAL()
#define OS_RR_END_CRITICAL()


/*****************/
/* Event control */
/*****************/

/* SetEvent */
#define OS_SE_ENTRY()
#define OS_SE_EXIT()
#define OS_SE_START_CRITICAL()
#define OS_SE_END_CRITICAL()

/* ClearEvent */
#define OS_CE_ENTRY()
#define OS_CE_EXIT()
#define OS_CE_START_CRITICAL()
#define OS_CE_END_CRITICAL()

/* GetEvent */
#define OS_GE_ENTRY()
#define OS_GE_EXIT()
#define OS_GE_START_CRITICAL()
#define OS_GE_END_CRITICAL()

/* WaitEvent */
#define OS_WE_ENTRY()
#define OS_WE_EXIT()
#define OS_WE_START_CRITICAL()
#define OS_WE_END_CRITICAL()


/**********/
/* Alarms */
/**********/

/* GetAlarmBase */
#define OS_GB_ENTRY()
#define OS_GB_EXIT()
#define OS_GB_START_CRITICAL()
#define OS_GB_END_CRITICAL()

/* SetRelAlarm */
#define OS_SA_ENTRY()
#define OS_SA_EXIT()
#define OS_SA_START_CRITICAL()
#define OS_SA_END_CRITICAL()

/* SetAbsAlarm */
#define OS_SL_ENTRY()
#define OS_SL_EXIT()
#define OS_SL_START_CRITICAL()
#define OS_SL_END_CRITICAL()

/* CancelAlarm */
#define OS_CA_ENTRY()
#define OS_CA_EXIT()
#define OS_CA_START_CRITICAL()
#define OS_CA_END_CRITICAL()

/* GetAlarm */
#define OS_GA_ENTRY()
#define OS_GA_EXIT()
#define OS_GA_START_CRITICAL()
#define OS_GA_END_CRITICAL()



/************/
/* Counters */
/************/

#define OS_IC_ENTRY()
#define OS_IC_EXIT()

/*x = counter index*/
#define OS_IC_START_CRITICAL(x)
#define OS_IC_END_CRITICAL(x)

/*******************/
/* Schedule tables */
/*******************/

/* StartScheduleTableRel */
#define OS_SR_ENTRY()
#define OS_SR_EXIT()
#define OS_SR_START_CRITICAL()
#define OS_SR_END_CRITICAL()

/* StartScheduleTableAbs */
#define OS_SS_ENTRY()
#define OS_SS_EXIT()
#define OS_SS_START_CRITICAL()
#define OS_SS_END_CRITICAL()

/* StopScheduleTable */
#define OS_SP_ENTRY()
#define OS_SP_EXIT()
#define OS_SP_START_CRITICAL()
#define OS_SP_END_CRITICAL()

/* GetScheduleTableStatus */
#define OS_SG_ENTRY()
#define OS_SG_EXIT()
#define OS_SG_START_CRITICAL()
#define OS_SG_END_CRITICAL()

/* NextScheduleTable */
#define OS_SN_ENTRY()
#define OS_SN_EXIT()
#define OS_SN_START_CRITICAL()
#define OS_SN_END_CRITICAL()

#if (osdScheduleTableSyncUsed)
/* SyncScheduleTable */
#define OS_SY_ENTRY()
#define OS_SY_EXIT()
#define OS_SY_START_CRITICAL()
#define OS_SY_END_CRITICAL()
/* StartScheduleTableSynchron */
#define OS_SO_ENTRY()
#define OS_SO_EXIT()
#define OS_SO_START_CRITICAL()
#define OS_SO_END_CRITICAL()
/* SetScheduleTableAsync */
#define OS_AY_ENTRY()
#define OS_AY_EXIT()
#define OS_AY_START_CRITICAL()
#define OS_AY_END_CRITICAL()
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
/*******************/
/* Applications */
/*******************/

/* GetApplicationID */
#define OS_AI_ENTRY()
#define OS_AI_EXIT()
#define OS_AI_START_CRITICAL()
#define OS_AI_END_CRITICAL()

/* TerminateApplication */
#define OS_TA_ENTRY()
#define OS_TA_EXIT()
#define OS_TA_START_CRITICAL()
#define OS_TA_END_CRITICAL()

/* CallTrustedFunction */
#define OS_CT_ENTRY()
#define OS_CT_EXIT()
#define OS_CT_START_CRITICAL()
#define OS_CT_END_CRITICAL()

/* CallNonTrustedFunction */
#define OS_NT_ENTRY()
#define OS_NT_EXIT()
#define OS_NT_START_CRITICAL()
#define OS_NT_END_CRITICAL()

/* CheckObjectAccess */
#define OS_OA_ENTRY()
#define OS_OA_EXIT()
#define OS_OA_START_CRITICAL()
#define OS_OA_END_CRITICAL()

/* CheckObjectOwnership */
#define OS_OO_ENTRY()
#define OS_OO_EXIT()
#define OS_OO_START_CRITICAL()
#define OS_OO_END_CRITICAL()

#endif /*((osdSC== SC3) || (osdSC== SC4))*/


/**************************************/
/* Operating system execution control */
/**************************************/

/* StartOS */
#define OS_ST_ENTRY()
#define OS_ST_EXIT()
#define OS_ST_START_CRITICAL()
#define OS_ST_END_CRITICAL()

/* ShutdownOS */
#define OS_SD_ENTRY()            
#define OS_SD_EXIT()             
#define OS_SD_START_CRITICAL()
#define OS_SD_END_CRITICAL()
                                 

/*****************/
/* Hook routines */
/*****************/

/* ErrorHook */
#define OS_ERHOOK_ENTRY()        
#define OS_ERHOOK_EXIT()         
                                 
/* StartupHook */
#define OS_STHOOK_ENTRY()        
#define OS_STHOOK_EXIT()         
                                 
/* ShutdownHook */               
#define OS_SDHOOK_ENTRY()        
#define OS_SDHOOK_EXIT()         
                                 
/* PreTaskHook */
#define OS_PREHOOK_ENTRY()       
#define OS_PREHOOK_EXIT()        
                                 
/* PostTaskHook */
#define OS_POSTHOOK_ENTRY()      
#define OS_POSTHOOK_EXIT()       
                                 

/*********************/
/* OSEK COM messages */
/*********************/

/* StartCOM */
#define OS_SC_ENTRY()           
#define OS_SC_EXIT()            
#define OS_SC_START_CRITICAL()
#define OS_SC_END_CRITICAL()
                           
/* StopCOM */
#define OS_TC_ENTRY()            
#define OS_TC_EXIT()             
                           
/* SendMessage */
#define OS_SM_ENTRY()
#define OS_SM_EXIT()             
#define OS_SM_START_CRITICAL()
#define OS_SM_END_CRITICAL()
                           
/* ReceiveMessage */
#define OS_RM_ENTRY()            
#define OS_RM_EXIT()             
#define OS_RM_START_CRITICAL()
#define OS_RM_END_CRITICAL()

/* GetMessageStatus */
#define OS_MS_ENTRY()            
#define OS_MS_EXIT()             
                           
/* InitMessage */
#define OS_IM_ENTRY()
#define OS_IM_EXIT()
#define OS_IM_START_CRITICAL()
#define OS_IM_END_CRITICAL()

/* ComErrorHook */
#define OS_CRHOOK_ENTRY()
#define OS_CRHOOK_EXIT()

/**************************/
/* miscellaneous routines */
/**************************/

/* osTimerInterrupt */           
#define OS_TI_ENTRY()            
#define OS_TI_EXIT()
#define OS_TI_START_CRITICAL()
#define OS_TI_END_CRITICAL()

/* GetISRID */           
#define OS_II_ENTRY()            
#define OS_II_EXIT()
#define OS_II_START_CRITICAL()
#define OS_II_END_CRITICAL()

/* dispatcher */
#define OS_START_DISPATCH()

/* idle loop */
#define OS_IDLE_ENTRY()
#define OS_IDLE_PROC()

/* Hardware specific macro */
/* KB begin osekHwEmptyMacro (default) */
/* KB end osekHwEmptyMacro */

#endif /* _EMPTYMAC_H */
