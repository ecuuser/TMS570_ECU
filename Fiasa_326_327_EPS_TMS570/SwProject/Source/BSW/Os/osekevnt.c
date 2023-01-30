/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osekevnt.c
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.49
|
|  Description: osek API-functions for handling events
|               - SetEvent
|               - ClearEvent
|               - GetEvent
|               - WaitEvent
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2012 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/


/* next define is set in the makefile
 * switches of the include of (generated) tcb.h, includes instead
 * the library config file
 */
#ifdef osdGenerateLib
#define osdIncludeLibConfig 1
#endif

#if defined USE_QUOTE_INCLUDES
 #include "osek.h"
 #include "osekext.h"
#else
 #include <osek.h>
 #include <osekext.h>
#endif

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

/* CovComment 0:  file: osekevnt.c */

/* KB begin osekStartOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_CODE_SECTION(".oscode") /* TR:SPMF49:0001 */ /* TR:SPMF49:0002 */
#endif
/* KB end osekStartOfCModule */

/* TR:SOSK22:0220 Start  */
/* TR:SOSK22:0221 Start  */
/* TR:SOSK22:0222 Start  */
/* TR:SOSK22:0223 Start  */
#if ((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0)

/*-+--------------------------------------------------------------------------
 / SetEvent
 / ========          
 /
 / Syntax:          StatusType SetEvent ( TaskType <TaskID>
 /                                        EventMaskType <Mask> )
 / Parameter (In):  - TaskID Reference to the task for which one or 
 /                    several events are to be set.
 /                  - Mask Mask of the events to be set
 / Parameter (Out): none
 / Description:     The service might be called from an interrupt service 
 /                  routine and from the task level, but not from hook 
 /                  routines.
 /                  The events of task <TaskID> are set according to the 
 /                  event mask <Mask>. Calling SetEvent causes the task 
 /                  <TaskID> to be transferred to the ready state, if it
 /                  has been waiting for at least one of the events 
 /                  specified in <Mask>.
 / Particularities: Any events not set in the event mask remain unchanged.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Task <TaskID> is invalid, E_OS_ID
 /                  - Referenced task is no extended task, E_OS_ACCESS
 /                  - Events can not be set as the referenced task is in the
 /                    suspended state, E_OS_STATE
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     ECC1, ECC2
 / Context:         Task, Cat2-ISR, interrupts not disabled by the application
 /--------------------------------------------------------------------------*/

#ifdef osdSysAPI
#undef osdSysAPI
#endif

/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/SetEvent.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
osqFunc1 StatusType osqFunc2 osSetEvent(TaskType taskIndex, EventMaskType setMask) /* PRQA S 1503 */  /* TR:SOSK22:0193 */
{
   /* CovComment 4:  Function: osSetEvent */
/* KB begin setEventBody (default) */

   /* TR:SOSK22:0077 Start */
   /* TR:SOSK22:0287 Start */
   osPrioType priority;

   OS_SE_ENTRY()
   COVER(0x010B)

#ifndef osdSysAPI
   COVER(0x010C)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in SetEvent  */
   /* TR:SASR30:0336 Start Context check in SetEvent  */
   if ((osdValidCtx_SetEvent & osCurrentContext) == 0)
   {
      COVER(0x010D)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_CALLEVEL, osdErrSECallContext);
      OS_SE_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x010E)

   if (taskIndex >= osrNumberOfAllTasks)
   {
      COVER(0x010F)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_ID, osdErrSEWrongTaskID);
      OS_SE_EXIT()
      return E_OS_ID; /* TR:SOSK22:0358 */
   }
   ELSEWITHCOVER(0x0110)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in SetEvent */
   if (((oskApplTaskAccess[taskIndex] & (1UL << osaActiveApplicationID)) == 0)) /* TR:SASR30:0319 */
   {
      COVER(0x0111)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_ACCESS, osdErrSENoAccess);
      OS_SE_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x0112)

#if osdNumberOfExtendedTasks != osdNumberOfAllTasks
   if (taskIndex >= osrNumberOfExtendedTasks)
   {
      COVER(0x0113)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_ACCESS, osdErrSENotExtendedTask);
      OS_SE_EXIT()
      return E_OS_ACCESS; /* TR:SOSK22:0289 */
   }
   ELSEWITHCOVER(0x0114)
#endif
   /* TR:SASR30:0038 Start Check disabled interrupts in SetEvent */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x0115)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_DISABLEDINT, osdErrSEIntAPIDisabled);
      OS_SE_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x0116)

   COVER(0x0117)
#endif   /* osdSysAPI */


   if (osTcbTaskState[taskIndex] == SUSPENDED)
   {
      COVER(0x0118)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_STATE, osdErrSETaskSuspended);
#ifndef osdSysAPI
      COVER(0x0119)
#endif
      OS_SE_EXIT()
      return E_OS_STATE; /* TR:SOSK22:0290 */
   }
   ELSEWITHCOVER(0x011A)

#ifndef osdSysAPI
   COVER(0x011B)
   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */
#endif

   COVER(0x011C)
   osTcbSetEventMask[taskIndex]|= setMask; /* set event flag(s)    */

   if (osTcbTaskState[taskIndex] == WAITING) /* TR:SPMF82:0001 */
   {
      /* task is waiting */
#if osdTimingProtectionUsed
      osbool EventsRequireStateChange = osdFALSE;
      osbool StateChangeAllowed = osdFALSE;

      if ((osTcbSetEventMask[taskIndex] & osTcbWaitEventMask[taskIndex]) != 0)
      {
         COVER(0x011D)
         EventsRequireStateChange = osdTRUE;
         StateChangeAllowed = osTPArrivalAllowed(taskIndex);
      }
      ELSEWITHCOVER(0x011E)
      if ((EventsRequireStateChange == osdTRUE) && (StateChangeAllowed == osdTRUE))
      {
         COVER(0x011F)
#else
      if ((osTcbSetEventMask[taskIndex] & osTcbWaitEventMask[taskIndex]) != 0)
      {
         COVER(0x0120)
#endif
         /*  satisfied, change from waiting to ready */

         /* get priority of continuued task */
         priority = oskTcbHomePrio[taskIndex];
#if (osdNumberOfPriorities > 0)
         COVER(0x0121)
         osSysErrAssert((priority < osrNumberOfPriorities), osdErrSEWrongTaskPrio)
#endif

         osTcbTaskState[taskIndex] = READY; /* TR:SOSK22:0037 */ /* TR:SOSK22:0043 */
         
         /* KB begin osQInsertAtPrio (default) */
         #if ((CC == ECC2) || (CC == BCC2))
         COVER(0x0122)
         oskQActivationQueues[priority][osQReadyTaskTail[priority]]= taskIndex; 
         #else
         COVER(0x0123)
         osQReadyTask[priority]= taskIndex;
         #endif
         
         #if (osdRTSize > 1)
         COVER(0x0124)
         osQReadyPrios[oskTcbReadyPrioOffset[taskIndex]]|= oskTcbReadyPrioMask[taskIndex];
         #else
         COVER(0x0125)
         osQReadyPrios|= oskTcbReadyPrioMask[taskIndex];
         #endif
         
         
         #if ((CC == ECC2) || (CC == BCC2))
         COVER(0x0126)
         osQReadyTaskTail[priority]++;
         if (osQReadyTaskTail[priority] > oskQMaxActivations[priority])
         {
            COVER(0x0127)
            osQReadyTaskTail[priority]= 0;
         }
         ELSEWITHCOVER(0x0128)
         #endif
         
         
         /* KB end osQInsertAtPrio */
         /* TR:SOSK22:0006 Start */
         if (priority < osHighReadyTaskPrio)
         {
            COVER(0x0129)
            osHighReadyTaskPrio   = priority;
            osHighReadyTaskIndex  = taskIndex;
            osStartDispatcher= osdTRUE; /* TR:SOSK22:0056 */

#ifndef osdSysAPI

            COVER(0x012A)
            /* KB begin osekHWosEnableTimProtInterrupt (default) */
            #if osdTimingProtectionUsed
            #error "Timing Protection not supported"
            #endif        
            /* KB end osekHWosEnableTimProtInterrupt */

#endif
            OS_SE_EXIT()
            return E_OK; /* TR:SOSK22:0288 */
         } /* TR:SOSK22:0006 End */
         ELSEWITHCOVER(0x012B)
      }
      ELSEWITHCOVER(0x012C)
   }
   ELSEWITHCOVER(0x012D)
#ifndef osdSysAPI
   COVER(0x012E)
   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */

#endif
   OS_SE_EXIT()
   return E_OK; /* TR:SPMF82:0002 */ /* TR:SOSK22:0077 End */ /* TR:SOSK22:0287 End */ /* TR:SOSK22:0288 */


/* KB end setEventBody */
} /* END OF osSetEvent */


#if ((osdNumberOfAlarmSetEvent > 0) || (osdNumberOfSTSetEvent > 0))
#define osdSysAPI
/*
 * MISRA RULE 14.1 VIOLATION: The function osSysSetEvent is unused in some configurations. In order to keep the code 
 * simple and error free, it is available in more configurations than necessary.
 */
osqFunc1 StatusType osqFunc2  osSysSetEvent(TaskType taskIndex, EventMaskType setMask) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osSysSetEvent */
/* KB begin setEventBody (default) */

   /* TR:SOSK22:0077 Start */
   /* TR:SOSK22:0287 Start */
   osPrioType priority;

   OS_SE_ENTRY()
   COVER(0x012F)

#ifndef osdSysAPI
   COVER(0x0130)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in SetEvent  */
   /* TR:SASR30:0336 Start Context check in SetEvent  */
   if ((osdValidCtx_SetEvent & osCurrentContext) == 0)
   {
      COVER(0x0131)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_CALLEVEL, osdErrSECallContext);
      OS_SE_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x0132)

   if (taskIndex >= osrNumberOfAllTasks)
   {
      COVER(0x0133)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_ID, osdErrSEWrongTaskID);
      OS_SE_EXIT()
      return E_OS_ID; /* TR:SOSK22:0358 */
   }
   ELSEWITHCOVER(0x0134)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in SetEvent */
   if (((oskApplTaskAccess[taskIndex] & (1UL << osaActiveApplicationID)) == 0)) /* TR:SASR30:0319 */
   {
      COVER(0x0135)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_ACCESS, osdErrSENoAccess);
      OS_SE_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x0136)

#if osdNumberOfExtendedTasks != osdNumberOfAllTasks
   if (taskIndex >= osrNumberOfExtendedTasks)
   {
      COVER(0x0137)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_ACCESS, osdErrSENotExtendedTask);
      OS_SE_EXIT()
      return E_OS_ACCESS; /* TR:SOSK22:0289 */
   }
   ELSEWITHCOVER(0x0138)
#endif
   /* TR:SASR30:0038 Start Check disabled interrupts in SetEvent */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x0139)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_DISABLEDINT, osdErrSEIntAPIDisabled);
      OS_SE_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x013A)

   COVER(0x013B)
#endif   /* osdSysAPI */


   if (osTcbTaskState[taskIndex] == SUSPENDED)
   {
      COVER(0x013C)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_STATE, osdErrSETaskSuspended);
#ifndef osdSysAPI
      COVER(0x013D)
#endif
      OS_SE_EXIT()
      return E_OS_STATE; /* TR:SOSK22:0290 */
   }
   ELSEWITHCOVER(0x013E)

#ifndef osdSysAPI
   COVER(0x013F)
   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */
#endif

   COVER(0x0140)
   osTcbSetEventMask[taskIndex]|= setMask; /* set event flag(s)    */

   if (osTcbTaskState[taskIndex] == WAITING) /* TR:SPMF82:0001 */
   {
      /* task is waiting */
#if osdTimingProtectionUsed
      osbool EventsRequireStateChange = osdFALSE;
      osbool StateChangeAllowed = osdFALSE;

      if ((osTcbSetEventMask[taskIndex] & osTcbWaitEventMask[taskIndex]) != 0)
      {
         COVER(0x0141)
         EventsRequireStateChange = osdTRUE;
         StateChangeAllowed = osTPArrivalAllowed(taskIndex);
      }
      ELSEWITHCOVER(0x0142)
      if ((EventsRequireStateChange == osdTRUE) && (StateChangeAllowed == osdTRUE))
      {
         COVER(0x0143)
#else
      if ((osTcbSetEventMask[taskIndex] & osTcbWaitEventMask[taskIndex]) != 0)
      {
         COVER(0x0144)
#endif
         /*  satisfied, change from waiting to ready */

         /* get priority of continuued task */
         priority = oskTcbHomePrio[taskIndex];
#if (osdNumberOfPriorities > 0)
         COVER(0x0145)
         osSysErrAssert((priority < osrNumberOfPriorities), osdErrSEWrongTaskPrio)
#endif

         osTcbTaskState[taskIndex] = READY; /* TR:SOSK22:0037 */ /* TR:SOSK22:0043 */
         
         /* KB begin osQInsertAtPrio (default) */
         #if ((CC == ECC2) || (CC == BCC2))
         COVER(0x0146)
         oskQActivationQueues[priority][osQReadyTaskTail[priority]]= taskIndex; 
         #else
         COVER(0x0147)
         osQReadyTask[priority]= taskIndex;
         #endif
         
         #if (osdRTSize > 1)
         COVER(0x0148)
         osQReadyPrios[oskTcbReadyPrioOffset[taskIndex]]|= oskTcbReadyPrioMask[taskIndex];
         #else
         COVER(0x0149)
         osQReadyPrios|= oskTcbReadyPrioMask[taskIndex];
         #endif
         
         
         #if ((CC == ECC2) || (CC == BCC2))
         COVER(0x014A)
         osQReadyTaskTail[priority]++;
         if (osQReadyTaskTail[priority] > oskQMaxActivations[priority])
         {
            COVER(0x014B)
            osQReadyTaskTail[priority]= 0;
         }
         ELSEWITHCOVER(0x014C)
         #endif
         
         
         /* KB end osQInsertAtPrio */
         /* TR:SOSK22:0006 Start */
         if (priority < osHighReadyTaskPrio)
         {
            COVER(0x014D)
            osHighReadyTaskPrio   = priority;
            osHighReadyTaskIndex  = taskIndex;
            osStartDispatcher= osdTRUE; /* TR:SOSK22:0056 */

#ifndef osdSysAPI

            COVER(0x014E)
            /* KB begin osekHWosEnableTimProtInterrupt (default) */
            #if osdTimingProtectionUsed
            #error "Timing Protection not supported"
            #endif        
            /* KB end osekHWosEnableTimProtInterrupt */

#endif
            OS_SE_EXIT()
            return E_OK; /* TR:SOSK22:0288 */
         } /* TR:SOSK22:0006 End */
         ELSEWITHCOVER(0x014F)
      }
      ELSEWITHCOVER(0x0150)
   }
   ELSEWITHCOVER(0x0151)
#ifndef osdSysAPI
   COVER(0x0152)
   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */

#endif
   OS_SE_EXIT()
   return E_OK; /* TR:SPMF82:0002 */ /* TR:SOSK22:0077 End */ /* TR:SOSK22:0287 End */ /* TR:SOSK22:0288 */


/* KB end setEventBody */
} /* END OF osSysSetEvent */
#endif

/* TR:SOSK22:0078 Start */
/*-+--------------------------------------------------------------------------
 / ClearEvent
 / =========
 /
 / Syntax:          StatusType ClearEvent ( EventMaskType <Mask> )
 / Parameter (In):  Mask Mask of the events to be cleared
 / Parameter (Out): none
 / Description:     The events of the extended task calling ClearEvent are 
 /                  cleared according to the event mask <Mask>.
 / Particularities: The system service ClearEvent is restricted to extended 
 /                  tasks which own the event.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Call not from extended task, E_OS_ACCESS
 /                  - Call at interrupt level, E_OS_CALLEVEL
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     ECC1, ECC2
 / Context:         Extended task, interrupts enabled
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/ClearEvent.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
osqFunc1 StatusType osqFunc2 osClearEvent (EventMaskType Mask) /* PRQA S 1503 */ /* TR:SOSK22:0194 */
{
   /* CovComment 4:  Function: osClearEvent */
   OS_CE_ENTRY()
   COVER(0x0153)

   COVER(0x0154)
   COVER(0x0155)
   /* TR:SOSK22:0291 Start */
   /* check call context */
   /* TR:SASR30:0035 Start Context check in ClearEvent */
   /* TR:SASR30:0336 Start Context check in ClearEvent */
   if ((osdValidCtx_ClearEvent & osCurrentContext) == 0)
   {
      COVER(0x0156)
      osSaveClearEvent_Mask(Mask)
      osAPIError(E_OS_CALLEVEL, osdErrCECallContext);
      OS_CE_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x0157)

   if (osaIntNestingDepth != 0)
   {
      COVER(0x0158)
      osSaveClearEvent_Mask(Mask)
      osAPIError(E_OS_CALLEVEL, osdErrCEOnInterruptLevel);
      OS_CE_EXIT()
      return E_OS_CALLEVEL; /* TR:SOSK22:0294 */
   }
   ELSEWITHCOVER(0x0159)

   if (osaActiveTaskIndex >= osrNumberOfExtendedTasks)
   {
      COVER(0x015A)
      osSaveClearEvent_Mask(Mask)
      osAPIError(E_OS_ACCESS, osdErrCENotExtendedTask);
      OS_CE_EXIT()
      return E_OS_ACCESS; /* TR:SOSK22:0293 */
   }
   ELSEWITHCOVER(0x015B)
   /* TR:SASR30:0038 Start Check disabled interrupts in ClearEvent */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x015C)
      osSaveClearEvent_Mask(Mask)
      osAPIError(E_OS_DISABLEDINT, osdErrCEIntAPIDisabled);
      OS_CE_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x015D)

   osTcbSetEventMask[osaActiveTaskIndex]&=(EventMaskType)(~Mask);
   /* TR:SOSK22:0291 End */
   COVER(0x015E)
   OS_CE_EXIT()
   return E_OK; /* TR:SOSK22:0292 */
} /* END OF osClearEvent */ /* TR:SOSK22:0078 End */


/*-+--------------------------------------------------------------------------
 / GetEvent
 / ========
 /
 / Syntax:          StatusType GetEvent ( TaskType <TaskID>, 
 /                                        EventMaskRefType <Event> )
 / Parameter (In):  TaskID Task whose event mask is to be returned.
 / Parameter (Out): Event Reference to the memory of the return data.
 / Description:     This service returns the current state of all event bits 
 /                  of the task <TaskID>, not the events that the task is 
 /                  waiting for.
 /                  The service might be called from interrupt service 
 /                  routines, task level and some hook routines.
 /                  The current status of the event mask of task <TaskID> is
 /                  copied to <Event>.
 / Particularities: The referenced task must be an extended task.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Task <TaskID> is invalid, E_OS_ID
 /                  - Referenced task <TaskID> is not an extended task, 
 /                    E_OS_ACCESS
 /                  - Referenced task <TaskID> is in the suspended state, 
 /                    E_OS_STATE
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     ECC1, ECC2
 / Context:         Task, Cat2-ISR, ErrorHook, PreTaskHook, PostTaskHook,
 /                  interrupts not disabled by the application
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/GetEvent.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
osqFunc1 EventMaskType osqFunc2 osGetEvent(TaskType taskIndex, EventMaskRefType Event) /* PRQA S 1503 */ /* TR:SOSK22:0195 */
{
   /* CovComment 4:  Function: osGetEvent */

   OS_GE_ENTRY()
   COVER(0x015F)

   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. (3199) */
   osdDummyRead(Event) /* PRQA S 3199 */

   /* check call context */
   /* TR:SASR30:0035 Start Context check in GetEvent */
   /* TR:SASR30:0336 Start Context check in GetEvent */
   if ((osdValidCtx_GetEvent & osCurrentContext) == 0)
   {
      COVER(0x0160)
      osSaveGetEvent_TaskID(taskIndex)
      osSaveGetEvent_Event(Event)
      osAPIError(E_OS_CALLEVEL, osdErrGECallContext);
      OS_GE_EXIT()
      osStatusTypeReturn = E_OS_CALLEVEL;
      return 0;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x0161)

   if (taskIndex >= osrNumberOfAllTasks)
   {
      COVER(0x0162)
      osSaveGetEvent_TaskID(taskIndex)
      osSaveGetEvent_Event(Event)
      osAPIError(E_OS_ID, osdErrGEWrongTaskID);
      OS_GE_EXIT()
      osStatusTypeReturn = E_OS_ID; /* TR:SOSK22:0298 */
      return 0;
   }
   ELSEWITHCOVER(0x0163)
   COVER(0x0164)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in GetEvent */
   if (((oskApplTaskAccess[taskIndex] & (1UL << osaActiveApplicationID)) == 0)) /* TR:SASR30:0319 */
   {
      COVER(0x0165)
      osSaveGetEvent_TaskID(taskIndex)
      osSaveGetEvent_Event(Event)
      osAPIError(E_OS_ACCESS, osdErrGENoAccess);
      OS_GE_EXIT()
      osStatusTypeReturn = E_OS_ACCESS;
      return 0;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x0166)

#if osdNumberOfExtendedTasks != osdNumberOfAllTasks
   COVER(0x0167)
   if (taskIndex >= osrNumberOfExtendedTasks)
   {
      COVER(0x0168)
      osSaveGetEvent_TaskID(taskIndex)
      osSaveGetEvent_Event(Event)
      osAPIError(E_OS_ACCESS, osdErrGENotExtendedTask);
      OS_GE_EXIT()
      osStatusTypeReturn = E_OS_ACCESS; /* TR:SOSK22:0299 */
      return 0;
   }
   ELSEWITHCOVER(0x0169)
#endif

   if (osTcbTaskState[taskIndex] == SUSPENDED)
   {
      COVER(0x016A)
      osSaveGetEvent_TaskID(taskIndex)
      osSaveGetEvent_Event(Event)
      osAPIError(E_OS_STATE, osdErrGETaskSuspended);
      OS_GE_EXIT()
      osStatusTypeReturn = E_OS_STATE; /* TR:SOSK22:0300 */
      return 0;
   }
   ELSEWITHCOVER(0x016B)
   /* TR:SASR30:0038 Start Check disabled interrupts in GetEvent */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x016C)
      osSaveGetEvent_TaskID(taskIndex)
      osSaveGetEvent_Event(Event)
      osAPIError(E_OS_DISABLEDINT, osdErrGEIntAPIDisabled);
      OS_GE_EXIT()
      osStatusTypeReturn = E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
      return 0;
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x016D)

   COVER(0x016E)
   OS_GE_EXIT()
   osStatusTypeReturn = E_OK;            /* TR:SOSK22:0297 */
   return osTcbSetEventMask[taskIndex];  /* TR:SOSK22:0295 */
} /* END OF osGetEvent */


/*-+--------------------------------------------------------------------------
 / WaitEvent
 / =========
 /
 / Syntax:          StatusType WaitEvent ( EventMaskType <Mask> )
 / Parameter (In):  Mask Mask of the events waited for.
 / Parameter (Out): none
 / Description:     The state of the calling task is set to waiting, unless 
 /                  at least one of the events specified in <Mask> has 
 /                  already been set.
 / Particularities: This call enforces rescheduling, if the wait condition 
 /                  occurs. If rescheduling takes place, the internal 
 /                  resource of the task is released while the task is in 
 /                  the waiting state.
 /                  This service must only be called from the extended task 
 /                  owning the event.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Calling task is not an extended task, E_OS_ACCESS
 /                  - Calling task occupies resources, E_OS_RESOURCE
 /                  - Call at interrupt level, E_OS_CALLEVEL
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     ECC1, ECC2
 / Context:         Extended task, interrupts enabled, no resources occupied
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/WaitEvent.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
osqFunc1 StatusType osqFunc2 osWaitEvent(EventMaskType mask) /* PRQA S 1503 */ /* TR:SOSK22:0196 */
{
   /* TR:SOSK22:0301 */
   /* CovComment 4:  Function: osWaitEvent */
#if osdTimingProtectionUsed
   osbool EventsRequireWait = osdFALSE;
   osbool ArrivalAllowed = osdTRUE;
#endif
   OS_WE_ENTRY()
   COVER(0x016F)

   COVER(0x0170)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in WaitEvent */
   /* TR:SASR30:0336 Start Context check in WaitEvent */
   if ((osdValidCtx_WaitEvent & osCurrentContext) == 0)
   {
      COVER(0x0171)
      osSaveWaitEvent_Mask(mask)
      osAPIError(E_OS_CALLEVEL, osdErrWECallContext);
      OS_WE_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x0172)

   if (osaIntNestingDepth != 0)
   {
      COVER(0x0173)
      osSaveWaitEvent_Mask(mask)
      osAPIError(E_OS_CALLEVEL, osdErrWEOnInterruptLevel);
      OS_WE_EXIT()
      return E_OS_CALLEVEL; /* TR:SOSK22:0305 */
   }
   ELSEWITHCOVER(0x0174)

   if (osaActiveTaskIndex >= osrNumberOfExtendedTasks)
   {
      COVER(0x0175)
      osSaveWaitEvent_Mask(mask)
      osAPIError(E_OS_ACCESS, osdErrWENotExtendedTask);
      OS_WE_EXIT()
      return E_OS_ACCESS; /* TR:SOSK22:0303 */
   }
   ELSEWITHCOVER(0x0176)

#if (osdNumberOfInternalResources == 0) && (osdNumberOfInterruptResources == 0)
   COVER(0x0177)
   /* check for task resources only system */
   if (osActiveTaskPrio != oskTcbHomePrio[osaActiveTaskIndex])
#else
   COVER(0x0178)
   /* check for mixed resource system (task, interrupt and internal) */
   if (osTcbResourceCounter[osaActiveTaskIndex] != 0)
#endif
   {
      COVER(0x0179)
      osSaveWaitEvent_Mask(mask)
      osAPIError(E_OS_RESOURCE, osdErrWEResourcesOccupied);
      OS_WE_EXIT()
      return E_OS_RESOURCE; /* TR:SOSK22:0304 */
   }
   ELSEWITHCOVER(0x017A)
   /* TR:SASR30:0038 Start Check disabled interrupts in WaitEvent */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x017B)
      osSaveWaitEvent_Mask(mask)
      osAPIError(E_OS_DISABLEDINT, osdErrWEInterruptsDisabled);
      OS_WE_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x017C)
   COVER(0x017D)
   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */

   osTcbWaitEventMask[osaActiveTaskIndex]= mask;  /* TR:SOSK22:0079 */ /* TR:SOSK22:0080 */

#if osdTimingProtectionUsed
   if ((osTcbSetEventMask[osaActiveTaskIndex] & mask) == 0) /* TR:SOSK22:0079 */ /* TR:SOSK22:0080 */
   {
      EventsRequireWait = osdTRUE;
      COVER(0x017E)
   }
   else
   {
      ArrivalAllowed = osTPArrivalAllowed(osaActiveTaskIndex);
      COVER(0x017F)
   }
   if ((EventsRequireWait == osdTRUE) || (ArrivalAllowed == osdFALSE))
   {
      COVER(0x0180)
#else
   if ((osTcbSetEventMask[osaActiveTaskIndex] & mask) == 0) /* TR:SOSK22:0079 */ /* TR:SOSK22:0080 */
   {
      COVER(0x0181)
#endif
      /* no expected event set, set task into waiting state */

      /* call hook routine for the waiting task */
#if osdPostTaskHook
      COVER(0x0182)
      osPostTaskHook();
#endif

#if osdTimingProtectionUsed
      COVER(0x0183)
      /* stop execution time monitoring/measurement for this task, reload execution time budget */
      osTPExeSwitchBack(INVALID_PROCESS);
#endif

#if osdNumberOfInternalResources > 0
      COVER(0x0184)
      /* KB begin osReleaseInternalResource (default) */
      /* TR:SOSK22:0099 Start */
      if (oskResInternalCeilingPrioMask[osaActiveTaskIndex] != 0)
      {
      #if osdRTSize == 1
         COVER(0x0185)
         osQReadyPrios &= ~oskResInternalCeilingPrioMask[osaActiveTaskIndex];
      #else
         COVER(0x0186)
         osQReadyPrios[oskResInternalCeilingPrioOffset[osaActiveTaskIndex]] &= /*;*/
            ~oskResInternalCeilingPrioMask[osaActiveTaskIndex];
      #endif
      #if ((CC == ECC2) || (CC == BCC2))
         COVER(0x0187)
         osActiveTaskPrio=oskTcbHomePrio[osaActiveTaskIndex];
      #endif
      
      #if osdORTIDebug
         COVER(0x0188)
         osTcbActualPrio[osaActiveTaskIndex]=oskTcbHomePrio[osaActiveTaskIndex];
      #endif
      
      }
      /* TR:SOSK22:0099 End */
      ELSEWITHCOVER(0x0189)
      
      
      /* KB end osReleaseInternalResource */
#endif

      COVER(0x018A)
      /* change task state from ready to waiting */
      osTcbTaskState[osaActiveTaskIndex] = WAITING; /* TR:SOSK22:0037 */ /* TR:SOSK22:0042 */

      /* KB begin osQDeleteFromPrio (default) */
      
      #if ((CC == ECC2) || (CC == BCC2))
      /* delete task out of the prio queue */
      osQReadyTaskHead[osActiveTaskPrio]++;
      if (osQReadyTaskHead[osActiveTaskPrio] > oskQMaxActivations[osActiveTaskPrio])
      {
         COVER(0x018B)
         osQReadyTaskHead[osActiveTaskPrio]= 0;
      }
      ELSEWITHCOVER(0x018C)
      
      if (osQReadyTaskHead[osActiveTaskPrio] == osQReadyTaskTail[osActiveTaskPrio])
      {  /* queue empty */
         COVER(0x018D)
      #endif
      
      #if (osdRTSize > 1)
         COVER(0x018E)
         osQReadyPrios[oskTcbReadyPrioOffset[osaActiveTaskIndex]]&= ~oskTcbReadyPrioMask[osaActiveTaskIndex];
      #else
         COVER(0x018F)
         osQReadyPrios&= ~oskTcbReadyPrioMask[osaActiveTaskIndex];
      #endif
      
      #if ((CC == ECC2) || (CC == BCC2))
      }
      ELSEWITHCOVER(0x0190)
      #endif
      
      /* KB end osQDeleteFromPrio */
      /* TR:SOSK22:0055 Start */
      /* for WaitEvent, osSchedulePrio returns always osdTRUE! */
      /* (same task is never running when reaching this point of code) */
      osStartDispatcher= osdTRUE;     
      (void) osSchedulePrio();
      osLockDispatcher= osdFALSE; /* WaitEvent is a scheduling point */
	  /* TR:SOSK22:0055 End */

      /* KB begin osekHWosEnableTimProtInterrupt (default) */
      #if osdTimingProtectionUsed
      #error "Timing Protection not supported"
      #endif        
      /* KB end osekHWosEnableTimProtInterrupt */
      OS_WE_EXIT()
      
      /* start dispatcher */
      OS_START_DISPATCH()
      return E_OK; /* TR:SOSK22:0302 */
   }
#if osdTimingProtectionUsed
   else
   {
      COVER(0x0191)
      /* stop execution time monitoring/measurement for this task , reload execution time budget */
      osTPExeSwitchBack(osaActiveTaskIndex);
   }
#else
   ELSEWITHCOVER(0x0192)
#endif

   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_WE_EXIT()

   return E_OK; /* TR:SOSK22:0302 */
   /* TR:SOSK22:0301 */
} /* END OF osWaitEvent */

#else  /* End of ((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) */

/* MISRA RULE 14.1 violated: (comment 1503) In SafeContext implementations all APIs are
 * encapsulated in wrappers. This wrappers belong to static ASIL code and must exist,
 * even if they are not used in a project.
 */
osqFunc1 StatusType osqFunc2 osSetEvent(TaskType taskIndex, EventMaskType setMask) /* PRQA S 1503 */ /* TR:SOSK22:0193 */
{
   osdDummyRead(taskIndex) /* PRQA S 3199 */
   osdDummyRead(setMask)   /* PRQA S 3199 */
   return E_OK;
}
osqFunc1 StatusType osqFunc2 osClearEvent (EventMaskType Mask ) /* PRQA S 1503 */ /* TR:SOSK22:0194 */
{
   osdDummyRead(Mask)      /* PRQA S 3199 */
   return E_OK;
}
osqFunc1 EventMaskType osqFunc2 osGetEvent(TaskType taskIndex, EventMaskRefType Event) /* PRQA S 1503 */ /* TR:SOSK22:0195 */
{
   osdDummyRead(taskIndex) /* PRQA S 3199 */
   osdDummyRead(Event)     /* PRQA S 3199 */
   return E_OK;  /* TR:SOSK22:0297 */
}
osqFunc1 StatusType osqFunc2 osWaitEvent(EventMaskType mask) /* PRQA S 1503 */ /* TR:SOSK22:0196 */
{
   osdDummyRead(mask)      /* PRQA S 3199 */
   return E_OK; /* TR:SOSK22:0302 */
}

#endif  /* End of ((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) */
/* TR:SOSK22:0220 End  */
/* TR:SOSK22:0221 End  */
/* TR:SOSK22:0222 End  */
/* TR:SOSK22:0223 End  */
/* KB begin osekEndOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
/* Reset to default section TR:SPMF49:0004 */
#pragma SET_CODE_SECTION()
#endif
/* KB end osekEndOfCModule */

/* END OF MODULE osekevnt.c */

