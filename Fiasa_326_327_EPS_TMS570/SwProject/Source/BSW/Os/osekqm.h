/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osekqm.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.02
|
|  Description: contains variables written from outside the save context 
|               implementation but also used within the safe context 
|               implementation
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2012 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* MISRA RULE 19.15 VIOLATION: The QAC-Tool states a violation of rule 19.15 with 
 * message 0883 below. Anyhow, there is a double include prevention and therefore,
 * the message is considered to be wrong. */
/* double include preventer */
#ifndef _OSEKQM_H      /* PRQA S 0883 EOF */ /* see MISRA comment above */
#define _OSEKQM_H

/*lint -save Messages inhibited in this file, will be re-enabled at the end of file */
/*lint -e539 Did not expect positive indentation */


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

#if defined USE_QUOTE_INCLUDES
 #include "osektype.h"
 #include "osekasrt.h"
 #include "oseksctx.h"
#else
 #include <osektype.h>
 #include <osekasrt.h>
 #include <oseksctx.h>
#endif



/* KB begin osekStartOfHModule (default) */
/* KB end osekStartOfHModule */

/* Task preemption type */
#define osdTaskTypeNonPreempt       ((osTaskPreemptionType) 0U)
#define osdTaskTypePreempt          ((osTaskPreemptionType) 1U)


/* KB begin osekHwQMConstants (overwritten) */
/* KB end osekHwQMConstants */

        extern osqBOOL1 volatile osqBOOL2 osbool               osqBOOL3 osStartDispatcher    ;
osqRAM0 extern osqRAM1           osqRAM2  osPrioType           osqRAM3  osHighReadyTaskPrio  ; 
osqRAM0 extern osqRAM1           osqRAM2  TaskType             osqRAM3  osHighReadyTaskIndex ;
osqRAM0 extern osqRAM1           osqRAM2  TaskType             osqRAM3  osLastActiveTaskIndex;
osqRAM0 extern osqRAM1           osqRAM2  osuint16             osqRAM3  osCurrentContext     ;/* current context */
osqRAM0 extern osqRAM1           osqRAM2  osuint16             osqRAM3  osLastError          ;
osqRAM0 extern osqRAM1           osqRAM2  osuint8              osqRAM3  osInSystemFct        ;
osqRAM0 extern osqRAM1           osqRAM2  osPrioType           osqRAM3  osActiveTaskPrio     ;

osqRAM0 extern osqRAM1 volatile osqRAM2 osDispatcherLockType osqRAM3 osLockDispatcher;



/* KB begin osekHwQMExternalDeclarations (overwritten) */
/* MISRA RULE 8.12 VIOLATION: (comment 3684) This arrays are generated, for this reason their size is unknown. */
extern osuint8 osaTcbValid[];                   /* PRQA S 3684 */
extern osuint8 osaTcbNTFNestingDepth[];          /* PRQA S 3684 */
extern osuint8 osaIcbNTFNestingDepth[];          /* PRQA S 3684 */
extern osuint32 osaTcbTaskSavedMPUBase[][12];    /* PRQA S 3684 */
extern osuint32 osaTcbTaskSavedMPUCfg[][12];     /* PRQA S 3684 */
extern osuint32 osaTcbTaskSavedMPUAccess[][12];  /* PRQA S 3684 */
extern osqTcbRAM1 osqTcbRAM2 osIsrStoredInfoType osqTcbRAM3 osaIsrStoredInfo[]; /* PRQA S 3684 */
extern osuint32 osIRQTable[];                   /* PRQA S 3684 */

/* KB end osekHwQMExternalDeclarations */


osqFunc1 void osqFunc2 osIdleLoop(void);


extern osqFunc1 void osqFunc2 osSysShutdownOS(StatusType Error); /* TR:SOSK22:0140 */
extern osqFunc1 void osqFunc2 osInterShutdownHook(StatusType Error);
extern osqFunc1 void osqFunc2 osAssertFailed(void);

extern void osInterErrorHook(StatusType Error);

/* hook routines */
/* TR:SOSK22:0121 Start */
/* TR:SOSK22:0145 Start This is only an example of system service interface */
extern osqFunc1 void osqFunc2 ErrorHook (StatusType Error);  /* TR:SOSK22:0205 */ /* TR:SOSK22:0234 */
extern osqFunc1 void osqFunc2 StartupHook (void); /* TR:SOSK22:0208 */ /* TR:SOSK22:0237 */
extern osqFunc1 void osqFunc2 ShutdownHook (StatusType Error); /* TR:SOSK22:0209 */ /* TR:SOSK22:0238 */
/* TR:SOSK22:0121 End */
/* TR:SOSK22:0145 End */

osqFunc1 void osqFunc2 osErrorHook(StatusType ErrorCode);

osqFunc1 StatusType osqFunc2 osActivateTask( TaskType taskIndex); /* TR:SOSK22:0161 */
osqFunc1 StatusType osqFunc2 osTerminateTask ( void );            /* TR:SOSK22:0166 */
osqFunc1 StatusType osqFunc2 osChainTask ( TaskType taskIndex );  /* TR:SOSK22:0170 */
osqFunc1 StatusType osqFunc2 osSchedule ( void );                 /* TR:SOSK22:0179 */  /* TR:SOSK22:0059 */
osqFunc1 TaskType osqFunc2 osGetTaskID ( TaskRefType TaskId);     /* TR:SOSK22:0183 */
osqFunc1 TaskStateType osqFunc2 osGetTaskState(TaskType TaskId, TaskStateRefType State); /* TR:SOSK22:0184 */
osqFunc1 void osqFunc2 osEnableAllInterrupts(void); /* TR:SOSK22:0071 */ /* TR:SOSK22:0072 */ /* TR:SOSK22:0185 */
osqFunc1 void osqFunc2 osDisableAllInterrupts(void);/* TR:SOSK22:0071 */ /* TR:SOSK22:0072 */ /* TR:SOSK22:0186 */
osqFunc1 void osqFunc2 osResumeOSInterrupts(void);  /* TR:SOSK22:0189 */
osqFunc1 void osqFunc2 osSuspendOSInterrupts(void); /* TR:SOSK22:0190 */
osqFunc1 void osqFunc2 osResumeAllInterrupts(void); /* TR:SOSK22:0071 */ /* TR:SOSK22:0072 */ /* TR:SOSK22:0187 */
osqFunc1 void osqFunc2 osSuspendAllInterrupts(void);/* TR:SOSK22:0071 */ /* TR:SOSK22:0072 */ /* TR:SOSK22:0188 */
osqFunc1 StatusType osqFunc2 osGetResource(ResourceType ResId);     /* TR:SOSK22:0191 */
osqFunc1 StatusType osqFunc2 osReleaseResource(ResourceType ResId); /* TR:SOSK22:0192 */  
osqFunc1 StatusType osqFunc2 osSetEvent(TaskType taskIndex, EventMaskType setMask);      /* TR:SOSK22:0193 */
osqFunc1 StatusType osqFunc2 osClearEvent (EventMaskType Mask );                         /* TR:SOSK22:0194 */
osqFunc1 EventMaskType osqFunc2 osGetEvent(TaskType taskIndex, EventMaskRefType Event);  /* TR:SOSK22:0195 */
osqFunc1 StatusType osqFunc2 osWaitEvent(EventMaskType mask);                            /* TR:SOSK22:0196 */
/* KB begin osekHWosSetRelAlarmPrototype (default) */
osqFunc1 StatusType osqFunc2 osSetRelAlarm(AlarmType alarmID, 
                                           TickType deltaTicks,
                                           TickType cycle); /* TR:SOSK22:0199 */
/* KB end osekHWosSetRelAlarmPrototype */
/* KB begin osekHWosSetAbsAlarmPrototype (default) */
osqFunc1 StatusType osqFunc2 osSetAbsAlarm(AlarmType alarmID, 
                                           TickType start,
                                           TickType cycle); /* TR:SOSK22:0200 */
/* KB end osekHWosSetAbsAlarmPrototype */
osqFunc1 StatusType osqFunc2 osCancelAlarm(AlarmType alarmID); /* TR:SOSK22:0201 */
osqFunc1 StatusType osqFunc2 osIncrementCounter(CounterType CounterID);
osqFunc1 TickType osqFunc2 osGetAlarm(AlarmType alarmID, TickRefType diffTickTime); /* TR:SOSK22:0198 */
osqFunc1 StatusType osqFunc2 osStartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset);
osqFunc1 StatusType osqFunc2 osStartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Tickvalue);
osqFunc1 StatusType osqFunc2 osNextScheduleTable(ScheduleTableType ScheduleTableID_current, 
                                                 ScheduleTableType  ScheduleTableID_next);
osqFunc1 ScheduleTableStatusType osqFunc2 osGetScheduleTableStatus(ScheduleTableType ScheduleTableID, 
                                                                   ScheduleTableStatusRefType ScheduleStatus);
osqFunc1 StatusType osqFunc2 osStopScheduleTable(ScheduleTableType ScheduleTableID);
osqFunc1 ApplicationType osqFunc2 osCheckObjectOwnership(ObjectTypeType ObjectType,
                                                         ObjectIDType ObjectID);
osqFunc1 ObjectAccessType osqFunc2 osCheckObjectAccess(ApplicationType   ApplID,
                                                       ObjectTypeType    ObjectType,
                                                       ObjectIDType      ObjectId);
osqFunc1 StatusType osqFunc2 osCallTrustedFunction(TrustedFunctionIndexType FunctionIndex,
                                                   TrustedFunctionParameterRefType FunctionParams);
osqFunc1 StatusType osqFunc2 osCallNonTrustedFunction(NonTrustedFunctionIndexType        FunctionIndex  ,
                                                      NonTrustedFunctionParameterRefType FunctionParams  );

osqFunc1 void osqFunc2 osStartOSc(void);
osqFunc1 void osqFunc2 osShutdownOS(StatusType Error); /* TR:SOSK22:0204 */
extern StatusType osStatusTypeReturn;

/* KB begin osekEndOfHModule (overwritten) */
/* KB end osekEndOfHModule */

/*lint -restore re-enable messages*/

#endif/* double include preventer */

/* END OF HEADER osektype.h */

