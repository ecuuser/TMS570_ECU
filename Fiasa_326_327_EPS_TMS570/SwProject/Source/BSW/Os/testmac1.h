/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 Autosar OS 3.0
|    File Name: testmac1.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.33
|
|  Description: test API macro definitions
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2011 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/


/* double include preventer */
#ifndef _TESTMAC1_H
#define _TESTMAC1_H

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

#if osdORTIDebug 

#define osdORTINoService              0

/*******************/
/* Task management */
/*******************/
#define osdORTIActivateTask           1
#define osdORTITerminateTask          2
#define osdORTIChainTask              3
#define osdORTISchedule               4
#define osdORTIGetTaskID              5
#define osdORTIGetTaskState           6

/**********************/
/* Interrupt handling */
/**********************/
#define osdORTIResumeAllInterrupts    7
#define osdORTISuspendAllInterrupts   8
#define osdORTIEnableAllInterrupts    12
#define osdORTIDisableAllInterrupts   13
#define osdORTIResumeOSInterrupts     14
#define osdORTISuspendOSInterrupts    15

/***********************/
/* Resource management */
/***********************/
#define osdORTIGetResource            16
#define osdORTIReleaseResource        17

/*****************/
/* Event control */
/*****************/
#define osdORTISetEvent               18
#define osdORTIClearEvent             19
#define osdORTIGetEvent               20
#define osdORTIWaitEvent              21

/**********/
/* Alarms */
/**********/
#define osdORTIGetAlarmBase           22
#define osdORTIGetAlarm               23
#define osdORTISetRelAlarm            24
#define osdORTISetAbsAlarm            25
#define osdORTICancelAlarm            26


/************/
/* Counters */
/************/

#define osdORTIIncrementCounter       27

/*******************/
/* Schedule tables */
/*******************/

#define osdORTIStartScheduleTableRel  28
#define osdORTIStartScheduleTableAbs  29
#define osdORTIStopScheduleTable      30
#define osdORTIGetScheduleTableStatus 31
#define osdORTINextScheduleTable      32

/**************************************/
/* Operating system execution control */
/**************************************/
#define osdORTIGetActiveApplicationMode 33
#define osdORTIStartOS                34
#define osdORTIShutdownOS             35

/*****************/
/* Hook routines */
/*****************/
#define osdORTIErrorHook              36
#define osdORTIPreTaskHook            37 
#define osdORTIPostTaskHook           38
#define osdORTIStartupHook            39
#define osdORTIShutdownHook           40

/*********************/
/* OSEK COM messages */
/*********************/
#define osdORTIStartCOM               41
#define osdORTIStopCOM                42
#define osdORTISendMessage            43
#define osdORTIReceiveMessage         44
#define osdORTIGetMessageStatus       47
#define osdORTIReadFlag               48
#define osdORTIResetFlag              49
#define osdORTIInitMessage            50
#define osdORTIComErrorHook           51
/*****************/
/* Misc routines */
/*****************/
#define osdORTIIdleEntry              52
#define osdORTISytemTimer             53 
#define osdORTIStartDispatch          54
#define osdORTIGetISRID               55

#if ((osdSC== SC3) || (osdSC== SC4))
/********************/
/* SC3/SC4 routines */
/********************/
#define osdORTIGetApplicationID       56
#define osdORTITerminateApplication   57
#define osdORTICallTrustedFunction    58
#define osdORTICheckObjectAccess      59
#define osdORTICheckObjectOwnership   60
#define osdORTICallNonTrustedFunction 70
#endif /* ((osdSC== SC3) || (osdSC== SC4)) */

/********************/
/* SC2/SC4 routines */
/********************/
#define osdORTISyncScheduleTable      63
#define osdORTISetScheduleTableAsync  64
#define osdORTIStartScheduleTableSynchron  67


#endif /* osdORTIDebug */

#if osdORTIDebug 
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
  #define osORTISetCurrentServiceId(x)   (osORTICurrentServiceId = (((x)<<1)+1) )
  #define osORTIResetCurrentServiceId(x) (osORTICurrentServiceId = ( (x)<<1   ) )
 #else
   #ifndef osdORTIDebugTest
      #define osORTISetCurrentServiceId(x) (osORTICurrentServiceId = (x))
      #define osORTISaveCurrentServiceId() (osORTISavedServiceId = osORTICurrentServiceId)
      #define osORTIRestoreCurrentServiceId() (osORTICurrentServiceId = osORTISavedServiceId)
   #else
      #define osORTISetCurrentServiceId(x) (osORTICurrentServiceId = (osuint8)(( (x) == 0)? osORTICurrentServiceId : (x) ))
      #define osORTISaveCurrentServiceId() (osORTISavedServiceId = osORTICurrentServiceId)
      #define osORTIRestoreCurrentServiceId() (osORTISavedServiceId++,--osORTISavedServiceId)
   #endif
 #endif
#else
 #if osdORTIStdVersion == 200
   #define osORTISetCurrentServiceId(x) ((void) 0)
   #define osORTISaveCurrentServiceId() ((void) 0)
   #define osORTIRestoreCurrentServiceId() ((void) 0)
 #endif
#endif



#if osdORTIDebug 

/*******************/
/* Task management */
/*******************/

/* ActivateTask */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_AT_ENTRY()            osORTISetCurrentServiceId(osdORTIActivateTask);
#define OS_AT_EXIT()             osORTIResetCurrentServiceId(osdORTIActivateTask);
#else
#define OS_AT_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIActivateTask);
#define OS_AT_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_AT_START_CRITICAL()
#define OS_AT_END_CRITICAL()

/* TerminateTask */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_TT_ENTRY()            osORTISetCurrentServiceId(osdORTITerminateTask);
#define OS_TT_EXIT()             osORTIResetCurrentServiceId(osdORTITerminateTask);
#else
#define OS_TT_ENTRY()            osORTISetCurrentServiceId(osdORTITerminateTask);
#define OS_TT_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_TT_START_CRITICAL()
#define OS_TT_END_CRITICAL()

/* ChainTask */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_HT_ENTRY()            osORTISetCurrentServiceId(osdORTIChainTask);
#define OS_HT_EXIT()             osORTIResetCurrentServiceId(osdORTIChainTask);
#else
#define OS_HT_ENTRY()            osORTISetCurrentServiceId(osdORTIChainTask);
#define OS_HT_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_HT_START_CRITICAL()
#define OS_HT_END_CRITICAL()

/* Schedule */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SH_ENTRY()            osORTISetCurrentServiceId(osdORTISchedule);
#define OS_SH_EXIT()             osORTIResetCurrentServiceId(osdORTISchedule);
#else
#define OS_SH_ENTRY()            osORTISetCurrentServiceId(osdORTISchedule);
#define OS_SH_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_SH_START_CRITICAL()
#define OS_SH_END_CRITICAL()

/* osGetTaskID */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GI_ENTRY()            osORTISetCurrentServiceId(osdORTIGetTaskID);
#define OS_GI_EXIT()             osORTIResetCurrentServiceId(osdORTIGetTaskID);
#else
#define OS_GI_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetTaskID);
#define OS_GI_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GI_START_CRITICAL()
#define OS_GI_END_CRITICAL()
             
/* osGetTaskState */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GS_ENTRY()            osORTISetCurrentServiceId(osdORTIGetTaskState);
#define OS_GS_EXIT()             osORTIResetCurrentServiceId(osdORTIGetTaskState);
#else
#define OS_GS_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetTaskState);
#define OS_GS_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GS_START_CRITICAL()
#define OS_GS_END_CRITICAL()


/**********************/
/* Interrupt handling */
/**********************/

/* ResumeAllInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_RA_ENTRY()            osORTISetCurrentServiceId(osdORTIResumeAllInterrupts);
#define OS_RA_EXIT()             osORTIResetCurrentServiceId(osdORTIResumeAllInterrupts);
#else
#define OS_RA_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTIResumeAllInterrupts);
#define OS_RA_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_RA_START_CRITICAL()
#define OS_RA_END_CRITICAL()

/* SuspendAllInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_PA_ENTRY()            osORTISetCurrentServiceId(osdORTISuspendAllInterrupts);
#define OS_PA_EXIT()             osORTIResetCurrentServiceId(osdORTISuspendAllInterrupts);
#else
#define OS_PA_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTISuspendAllInterrupts);
#define OS_PA_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_PA_START_CRITICAL()
#define OS_PA_END_CRITICAL()

/* EnableAllInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_EA_ENTRY()            osORTISetCurrentServiceId(osdORTIEnableAllInterrupts);
#define OS_EA_EXIT()             osORTIResetCurrentServiceId(osdORTIEnableAllInterrupts);
#else
#define OS_EA_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTIEnableAllInterrupts);
#define OS_EA_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_EA_START_CRITICAL()
#define OS_EA_END_CRITICAL()
 
/* DisableAllInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_DA_ENTRY()            osORTISetCurrentServiceId(osdORTIDisableAllInterrupts);
#define OS_DA_EXIT()             osORTIResetCurrentServiceId(osdORTIDisableAllInterrupts);
#else
#define OS_DA_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTIDisableAllInterrupts);
#define OS_DA_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_DA_START_CRITICAL()
#define OS_DA_END_CRITICAL()

/* ResumeOSInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_RI_ENTRY()            osORTISetCurrentServiceId(osdORTIResumeOSInterrupts);
#define OS_RI_EXIT()             osORTIResetCurrentServiceId(osdORTIResumeOSInterrupts);
#else
#define OS_RI_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTIResumeOSInterrupts);
#define OS_RI_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_RI_START_CRITICAL()
#define OS_RI_END_CRITICAL()

/* SuspendOSInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SI_ENTRY()            osORTISetCurrentServiceId(osdORTISuspendOSInterrupts);
#define OS_SI_EXIT()             osORTIResetCurrentServiceId(osdORTISuspendOSInterrupts);
#else
#define OS_SI_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTISuspendOSInterrupts);
#define OS_SI_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_SI_START_CRITICAL()
#define OS_SI_END_CRITICAL()


/***********************/
/* Resource management */
/***********************/

/* GetResource */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GR_ENTRY()            osORTISetCurrentServiceId(osdORTIGetResource);
#define OS_GR_EXIT()             osORTIResetCurrentServiceId(osdORTIGetResource);
#else
#define OS_GR_ENTRY()            osORTISetCurrentServiceId(osdORTIGetResource);
#define OS_GR_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_GR_START_CRITICAL()
#define OS_GR_END_CRITICAL()

/* ReleaseResource */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_RR_ENTRY()            osORTISetCurrentServiceId(osdORTIReleaseResource);
#define OS_RR_EXIT()             osORTIResetCurrentServiceId(osdORTIReleaseResource);
#else
#define OS_RR_ENTRY()            osORTISetCurrentServiceId(osdORTIReleaseResource);
#define OS_RR_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_RR_START_CRITICAL()
#define OS_RR_END_CRITICAL()



/*****************/
/* Event control */
/*****************/

/* SetEvent */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SE_ENTRY()            osORTISetCurrentServiceId(osdORTISetEvent);
#define OS_SE_EXIT()             osORTIResetCurrentServiceId(osdORTISetEvent);
#else
#define OS_SE_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTISetEvent);
#define OS_SE_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SE_START_CRITICAL()
#define OS_SE_END_CRITICAL()
                           
/* ClearEvent */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_CE_ENTRY()            osORTISetCurrentServiceId(osdORTIClearEvent);
#define OS_CE_EXIT()             osORTIResetCurrentServiceId(osdORTIClearEvent);
#else
#define OS_CE_ENTRY()            osORTISetCurrentServiceId(osdORTIClearEvent);
#define OS_CE_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_CE_START_CRITICAL()
#define OS_CE_END_CRITICAL()
                           
/* GetEvent */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GE_ENTRY()            osORTISetCurrentServiceId(osdORTIGetEvent);
#define OS_GE_EXIT()             osORTIResetCurrentServiceId(osdORTIGetEvent);
#else
#define OS_GE_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetEvent);
#define OS_GE_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GE_START_CRITICAL()
#define OS_GE_END_CRITICAL()
                           
/* WaitEvent */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_WE_ENTRY()            osORTISetCurrentServiceId(osdORTIWaitEvent);
#define OS_WE_EXIT()             osORTIResetCurrentServiceId(osdORTIWaitEvent);
#else
#define OS_WE_ENTRY()            osORTISetCurrentServiceId(osdORTIWaitEvent);
#define OS_WE_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_WE_START_CRITICAL()
#define OS_WE_END_CRITICAL()


/**********/
/* Alarms */
/**********/

/* GetAlarmBase */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GB_ENTRY()            osORTISetCurrentServiceId(osdORTIGetAlarmBase);
#define OS_GB_EXIT()             osORTIResetCurrentServiceId(osdORTIGetAlarmBase);
#else
#define OS_GB_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetAlarmBase);
#define OS_GB_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GB_START_CRITICAL()
#define OS_GB_END_CRITICAL()
                  
/* SetRelAlarm */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SA_ENTRY()            osORTISetCurrentServiceId(osdORTISetRelAlarm);
#define OS_SA_EXIT()             osORTIResetCurrentServiceId(osdORTISetRelAlarm);
#else
#define OS_SA_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTISetRelAlarm);
#define OS_SA_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SA_START_CRITICAL()
#define OS_SA_END_CRITICAL()

/* SetAbsAlarm */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SL_ENTRY()            osORTISetCurrentServiceId(osdORTISetAbsAlarm);
#define OS_SL_EXIT()             osORTIResetCurrentServiceId(osdORTISetAbsAlarm);
#else
#define OS_SL_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTISetAbsAlarm);
#define OS_SL_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SL_START_CRITICAL()
#define OS_SL_END_CRITICAL()

/* CancelAlarm */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_CA_ENTRY()            osORTISetCurrentServiceId(osdORTICancelAlarm);
#define OS_CA_EXIT()             osORTIResetCurrentServiceId(osdORTICancelAlarm);
#else
#define OS_CA_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTICancelAlarm);
#define OS_CA_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_CA_START_CRITICAL()
#define OS_CA_END_CRITICAL()

/* GetAlarm */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GA_ENTRY()            osORTISetCurrentServiceId(osdORTIGetAlarm);
#define OS_GA_EXIT()             osORTIResetCurrentServiceId(osdORTIGetAlarm);
#else
#define OS_GA_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetAlarm);
#define OS_GA_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GA_START_CRITICAL()
#define OS_GA_END_CRITICAL()

/************/
/* Counters */
/************/

/* IncrementCounter */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_IC_ENTRY()            osORTISetCurrentServiceId(osdORTIIncrementCounter);
#define OS_IC_EXIT()             osORTIResetCurrentServiceId(osdORTIIncrementCounter);
#else
#define OS_IC_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIIncrementCounter);
#define OS_IC_EXIT()             osORTIRestoreCurrentServiceId();
#endif

/*x = counter index*/
#define OS_IC_START_CRITICAL(x)
#define OS_IC_END_CRITICAL(x)


               
/*******************/
/* Schedule tables */
/*******************/

/* StartScheduleTableRel */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SR_ENTRY()            osORTISetCurrentServiceId(osdORTIStartScheduleTableRel);
#define OS_SR_EXIT()             osORTIResetCurrentServiceId(osdORTIStartScheduleTableRel);
#else
#define OS_SR_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIStartScheduleTableRel);
#define OS_SR_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SR_START_CRITICAL()
#define OS_SR_END_CRITICAL()

/* StartScheduleTableAbs */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SS_ENTRY()            osORTISetCurrentServiceId(osdORTIStartScheduleTableAbs);
#define OS_SS_EXIT()             osORTIResetCurrentServiceId(osdORTIStartScheduleTableAbs);
#else
#define OS_SS_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIStartScheduleTableAbs);
#define OS_SS_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SS_START_CRITICAL()
#define OS_SS_END_CRITICAL()


/* StopScheduleTable */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SP_ENTRY()            osORTISetCurrentServiceId(osdORTIStopScheduleTable);
#define OS_SP_EXIT()             osORTIResetCurrentServiceId(osdORTIStopScheduleTable);
#else
#define OS_SP_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIStopScheduleTable);
#define OS_SP_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SP_START_CRITICAL()
#define OS_SP_END_CRITICAL()

/* GetScheduleTableStatus */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SG_ENTRY()            osORTISetCurrentServiceId(osdORTIGetScheduleTableStatus);
#define OS_SG_EXIT()             osORTIResetCurrentServiceId(osdORTIGetScheduleTableStatus);
#else
#define OS_SG_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetScheduleTableStatus);
#define OS_SG_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SG_START_CRITICAL()
#define OS_SG_END_CRITICAL()

/* NextScheduleTable */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SN_ENTRY()            osORTISetCurrentServiceId(osdORTINextScheduleTable);
#define OS_SN_EXIT()             osORTIResetCurrentServiceId(osdORTINextScheduleTable);
#else
#define OS_SN_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTINextScheduleTable);
#define OS_SN_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SN_START_CRITICAL()
#define OS_SN_END_CRITICAL()

#if (osdScheduleTableSyncUsed)
/* SyncScheduleTable */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SY_ENTRY()            osORTISetCurrentServiceId(osdORTISyncScheduleTable);
#define OS_SY_EXIT()             osORTIResetCurrentServiceId(osdORTISyncScheduleTable);
#else
#define OS_SY_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTISyncScheduleTable);
#define OS_SY_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SY_START_CRITICAL()
#define OS_SY_END_CRITICAL()

/* StartScheduleTableSynchron */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SO_ENTRY()            osORTISetCurrentServiceId(osdORTIStartScheduleTableSynchron);
#define OS_SO_EXIT()             osORTIResetCurrentServiceId(osdORTIStartScheduleTableSynchron);
#else
#define OS_SO_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIStartScheduleTableSynchron);
#define OS_SO_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SO_START_CRITICAL()
#define OS_SO_END_CRITICAL()

/* SetScheduleTableAsync */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_AY_ENTRY()            osORTISetCurrentServiceId(osdORTISetScheduleTableAsync);
#define OS_AY_EXIT()             osORTIResetCurrentServiceId(osdORTISetScheduleTableAsync);
#else
#define OS_AY_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTISetScheduleTableAsync);
#define OS_AY_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_AY_START_CRITICAL()
#define OS_AY_END_CRITICAL()
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
/********************/
/* SC3/SC4 routines */
/********************/
/* GetApplicationID */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_AI_ENTRY()            osORTISetCurrentServiceId(osdORTIGetApplicationID);
#define OS_AI_EXIT()             osORTIResetCurrentServiceId(osdORTIGetApplicationID);
#else
#define OS_AI_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetApplicationID);
#define OS_AI_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_AI_START_CRITICAL()
#define OS_AI_END_CRITICAL()

/* TerminateApplication */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_TA_ENTRY()            osORTISetCurrentServiceId(osdORTITerminateApplication);
#define OS_TA_EXIT()             osORTIResetCurrentServiceId(osdORTITerminateApplication);
#else
#define OS_TA_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTITerminateApplication);
#define OS_TA_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_TA_START_CRITICAL()
#define OS_TA_END_CRITICAL()

/* CallTrustedFunction */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_CT_ENTRY()            osORTISetCurrentServiceId(osdORTICallTrustedFunction);
#define OS_CT_EXIT()             osORTIResetCurrentServiceId(osdORTICallTrustedFunction);
#else
#define OS_CT_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTICallTrustedFunction);
#define OS_CT_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_CT_START_CRITICAL()
#define OS_CT_END_CRITICAL()

/* CallNonTrustedFunction */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_NT_ENTRY()            osORTISetCurrentServiceId(osdORTICallNonTrustedFunction);
#define OS_NT_EXIT()             osORTIResetCurrentServiceId(osdORTICallNonTrustedFunction);
#else
#define OS_NT_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTICallNonTrustedFunction);
#define OS_NT_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_NT_START_CRITICAL()
#define OS_NT_END_CRITICAL()

/* CheckObjectAccess */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_OA_ENTRY()            osORTISetCurrentServiceId(osdORTICheckObjectAccess);
#define OS_OA_EXIT()             osORTIResetCurrentServiceId(osdORTICheckObjectAccess);
#else
#define OS_OA_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTICheckObjectAccess);
#define OS_OA_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_OA_START_CRITICAL()
#define OS_OA_END_CRITICAL()

/* CheckObjectOwnership */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_OO_ENTRY()            osORTISetCurrentServiceId(osdORTICheckObjectOwnership);
#define OS_OO_EXIT()             osORTIResetCurrentServiceId(osdORTICheckObjectOwnership);
#else
#define OS_OO_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTICheckObjectOwnership);
#define OS_OO_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_OO_START_CRITICAL()
#define OS_OO_END_CRITICAL()

#endif /* ((osdSC== SC3) || (osdSC== SC4)) */


/**************************************/
/* Operating system execution control */
/**************************************/
                 
/* StartOS */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_ST_ENTRY()            osORTISetCurrentServiceId(osdORTIStartOS);
#define OS_ST_EXIT()             osORTIResetCurrentServiceId(osdORTIStartOS);
#else
#define OS_ST_ENTRY()            osORTISetCurrentServiceId(osdORTIStartOS);
#define OS_ST_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_ST_START_CRITICAL()
#define OS_ST_END_CRITICAL()

/* ShutdownOS */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SD_ENTRY()            osORTISetCurrentServiceId(osdORTIShutdownOS);
#define OS_SD_EXIT()             osORTIResetCurrentServiceId(osdORTIShutdownOS);
#else
#define OS_SD_ENTRY()            osORTISetCurrentServiceId(osdORTIShutdownOS);
#define OS_SD_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_SD_START_CRITICAL()
#define OS_SD_END_CRITICAL()


/*****************/
/* Hook routines */
/*****************/

/* ErrorHook */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_ERHOOK_ENTRY()        osORTISetCurrentServiceId(osdORTIErrorHook);
#define OS_ERHOOK_EXIT()         osORTIResetCurrentServiceId(osdORTIErrorHook);
                                                
/* StartupHook */
#define OS_STHOOK_ENTRY()        osORTISetCurrentServiceId(osdORTIStartupHook);
#define OS_STHOOK_EXIT()         osORTIResetCurrentServiceId(osdORTIStartupHook);

/* ShutdownHook */               
#define OS_SDHOOK_ENTRY()        osORTISetCurrentServiceId(osdORTIShutdownHook);
#define OS_SDHOOK_EXIT()         osORTIResetCurrentServiceId(osdORTIShutdownHook);

/* PreTaskHook */
#define OS_PREHOOK_ENTRY()       osORTISetCurrentServiceId(osdORTIPreTaskHook);
#define OS_PREHOOK_EXIT()        osORTIResetCurrentServiceId(osdORTIPreTaskHook);

/* PostTaskHook */
#define OS_POSTHOOK_ENTRY()      osORTISetCurrentServiceId(osdORTIPostTaskHook);
#define OS_POSTHOOK_EXIT()       osORTIResetCurrentServiceId(osdORTIPostTaskHook);
#else
#define OS_ERHOOK_ENTRY()        {  \
                                    osuint8 osORTISavedServiceId; \
                                    osORTISaveCurrentServiceId(); \
                                    osORTISetCurrentServiceId(osdORTIErrorHook);
#define OS_ERHOOK_EXIT()            osORTIRestoreCurrentServiceId(); \
                                 }
                                                
/* StartupHook */
#define OS_STHOOK_ENTRY()        {  \
                                    osuint8 osORTISavedServiceId; \
                                    osORTISaveCurrentServiceId(); \
                                    osORTISetCurrentServiceId(osdORTIStartupHook);
#define OS_STHOOK_EXIT()            osORTIRestoreCurrentServiceId(); \
                                 }

/* ShutdownHook */               
#define OS_SDHOOK_ENTRY()        {  \
                                    osuint8 osORTISavedServiceId; \
                                    osORTISaveCurrentServiceId(); \
                                    osORTISetCurrentServiceId(osdORTIShutdownHook);
#define OS_SDHOOK_EXIT()            osORTIRestoreCurrentServiceId(); \
                                 }

/* PreTaskHook */
#define OS_PREHOOK_ENTRY()       {  \
                                    osuint8 osORTISavedServiceId; \
                                    osORTISaveCurrentServiceId(); \
                                    osORTISetCurrentServiceId(osdORTIPreTaskHook); 
#define OS_PREHOOK_EXIT()           osORTIRestoreCurrentServiceId(); \
                                 }

/* PostTaskHook */
#define OS_POSTHOOK_ENTRY()      {  \
                                    osuint8 osORTISavedServiceId; \
                                    osORTISaveCurrentServiceId(); \
                                    osORTISetCurrentServiceId(osdORTIPostTaskHook); 
#define OS_POSTHOOK_EXIT()          osORTIRestoreCurrentServiceId(); \
                                 }
#endif

/*********************/
/* OSEK COM messages */
/*********************/

/* StartCOM */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SC_ENTRY()            osORTISetCurrentServiceId(osdORTIStartCOM);
#define OS_SC_EXIT()             osORTIResetCurrentServiceId(osdORTIStartCOM);
#else
#define OS_SC_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIStartCOM);          
#define OS_SC_EXIT()             osORTIRestoreCurrentServiceId();            
#endif
#define OS_SC_START_CRITICAL()
#define OS_SC_END_CRITICAL()
                           
/* StopCOM */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_TC_ENTRY()            osORTISetCurrentServiceId(osdORTIStopCOM);
#define OS_TC_EXIT()             osORTIResetCurrentServiceId(osdORTIStopCOM);
#else
#define OS_TC_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIStopCOM);            
#define OS_TC_EXIT()             osORTIRestoreCurrentServiceId();             
#endif
                           
/* SendMessage */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SM_ENTRY()            osORTISetCurrentServiceId(osdORTISendMessage);
#define OS_SM_EXIT()             osORTIResetCurrentServiceId(osdORTISendMessage);
#else
#define OS_SM_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTISendMessage);            
#define OS_SM_EXIT()             osORTIRestoreCurrentServiceId();             
#endif
#define OS_SM_START_CRITICAL()
#define OS_SM_END_CRITICAL()
                           
/* ReceiveMessage */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_RM_ENTRY()            osORTISetCurrentServiceId(osdORTIReceiveMessage);
#define OS_RM_EXIT()             osORTIResetCurrentServiceId(osdORTIReceiveMessage);
#else
#define OS_RM_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIReceiveMessage);            
#define OS_RM_EXIT()             osORTIRestoreCurrentServiceId();             
#endif
#define OS_RM_START_CRITICAL()
#define OS_RM_END_CRITICAL()

#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
/* GetMessageStatus */
#define OS_MS_ENTRY()            osORTISetCurrentServiceId(osdORTIGetMessageStatus);
#define OS_MS_EXIT()             osORTIResetCurrentServiceId(osdORTIGetMessageStatus);      
                           
#else
/* GetMessageStatus */
#define OS_MS_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetMessageStatus);
#define OS_MS_EXIT()             osORTIRestoreCurrentServiceId();
                           
#endif
                           
/* InitMessage */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_IM_ENTRY()            osORTISetCurrentServiceId(osdORTIInitMessage);
#define OS_IM_EXIT()             osORTIResetCurrentServiceId(osdORTIInitMessage);
#else
#define OS_IM_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIInitMessage);
#define OS_IM_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_IM_START_CRITICAL()
#define OS_IM_END_CRITICAL()

/* ComErrorHook */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_CRHOOK_ENTRY()        osORTISetCurrentServiceId(osdORTIComErrorHook);
#define OS_CRHOOK_EXIT()         osORTIResetCurrentServiceId(osdORTIComErrorHook);
#else
#define OS_CRHOOK_ENTRY()        osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIComErrorHook);
#define OS_CRHOOK_EXIT()         osORTIRestoreCurrentServiceId();
#endif


/**************************/
/* miscellaneous routines */
/**************************/

/* osTimerInterrupt */             
#define OS_TI_ENTRY()            
#define OS_TI_EXIT()
#define OS_TI_START_CRITICAL()
#define OS_TI_END_CRITICAL()

/* GetISRID */           
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_II_ENTRY()            osORTISetCurrentServiceId(osdORTIGetISRID);
#define OS_II_EXIT()             osORTIResetCurrentServiceId(osdORTIGetISRID);
#else
#define OS_II_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetISRID);
#define OS_II_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_II_START_CRITICAL()
#define OS_II_END_CRITICAL()

/* dispatcher */
#define OS_START_DISPATCH()

/* idle loop */
#define OS_IDLE_ENTRY()
#define OS_IDLE_PROC()      

/* Hardware specific macro */
/* KB begin osekHwTestMacro1 (default) */
/* KB end osekHwTestMacro1 */

#endif /* osdORTIDebug */

#endif /* _TESTMAC1_H */
