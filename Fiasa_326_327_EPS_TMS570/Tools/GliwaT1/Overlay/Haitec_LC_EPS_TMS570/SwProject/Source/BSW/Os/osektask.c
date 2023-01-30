/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osektask.c
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.68
|
|  Description: osek API-functions for controlling tasks
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

#include "T1_AppInterface.h"

#ifndef T1_ENABLE
#error "This version of osektask.c is not intended for a production build. Please replace with the official version from Vector."
#endif

/* CovComment 0:  file: osektask.c */

/* KB begin osekStartOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_CODE_SECTION(".oscode") /* TR:SPMF49:0001 */ /* TR:SPMF49:0002 */
#endif
/* KB end osekStartOfCModule */

#if (osdNumberOfAllTasks > 0)
/*-+--------------------------------------------------------------------------
 / ActivateTask
 / ============
 /
 / Syntax:          StatusType ActivateTask ( TaskType <TaskID> )
 / Parameter (In):  TaskID Task reference
 / Parameter (Out): none
 / Description:     The task <TaskID> is transferred from the suspended state
 /                  into the ready state. The operating system ensures that the 
 /                  task code is being executed from the first statement.
 / Particularities: The service may be called from interrupt level and from 
 /                  task level.
 /                  Rescheduling after the call to ActivateTask depends on the
 /                  place it is called from (ISR, non preemptable task, 
 /                  preemptable task).
 /                  If E_OS_LIMIT is returned the activation is ignored.
 /                  When an extended task is transferred from suspended state
 /                  into ready state all its events are cleared.
 / Status:
 /  -Standard:      - No error, E_OK
 /                  - Too many task activations of <TaskID>, E_OS_LIMIT
 /  -Extended:      - Task <TaskID> is invalid, E_OS_ID
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:
 /  -General:       Task, Cat2-ISR, interrupts not disabled by the 
 /                  application
 /  -SC1/SC2 only:  StartupHook (compatibility to older OSEK-OS)
 /     
 /--------------------------------------------------------------------------*/

#ifdef osdSysAPI
#undef osdSysAPI
#endif


/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/ActivateTask.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
osqFunc1 StatusType osqFunc2 osActivateTask(TaskType taskIndex) /* PRQA S 1503 */  /* TR:SOSK22:0161 */
{
   /* CovComment 4:  Function: osActivateTask */
   /* KB begin actTaskBody (default) */
   /* TR:SOSK22:0001 Start */
   /* TR:SOSK22:0016 Start */
   /* TR:SOSK22:0017 Start */
   /* TR:SOSK22:0018 Start */
   /* TR:SOSK22:0019 Start */
   /* TR:SOSK22:0020 Start */ 
   /* TR:SOSK22:0029 Start */
   /* TR:SOSK22:0030 Start */
   /* TR:SOSK22:0047 Start */
   /* TR:SOSK22:0050 Start */
      osPrioType priority;
   
      OS_AT_ENTRY()
      COVER(0x0203)
   #if (!defined osdSysAPI)
      /* check call context */
      /* TR:SASR30:0035 Start Context check in ActivateTask */
      /* TR:SASR30:0336 Start Context check in ActivateTask */
      if ((osdValidCtx_ActivateTask & osCurrentContext) == 0) /* TR:SOSK22:0120 */
      {
         COVER(0x0204)
         osSaveActivateTask_TaskID(taskIndex)
         osAPIError(E_OS_CALLEVEL, osdErrATCallContext); /* TR:SOSK22:0129 */
         OS_AT_EXIT()
         return E_OS_CALLEVEL;
      }
      /* TR:SASR30:0336 End */
      /* TR:SASR30:0035 End */
      ELSEWITHCOVER(0x0205)
   
      if (taskIndex >= osrNumberOfAllTasks)
      {
         COVER(0x0206)
         osSaveActivateTask_TaskID(taskIndex)
         osAPIError(E_OS_ID, osdErrATWrongTaskID);
         OS_AT_EXIT()
         return E_OS_ID; /* TR:SOSK22:0164 */
      }
      ELSEWITHCOVER(0x0207)
      /* TR:SASR30:0038 Start Check disabled interrupts in ActivateTask */
      if (osaIntAPIStatus != 0) /* TR:SOSK22:0254 */
      {
         COVER(0x0208)
         osSaveActivateTask_TaskID(taskIndex)
         osAPIError(E_OS_DISABLEDINT, osdErrATIntAPIDisabled);
         OS_AT_EXIT()
         return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
      }
      /* TR:SASR30:0038 End */
      ELSEWITHCOVER(0x0209)
      /* check access rights for this object */
      /* TR:SASR30:0021 Start Check access rights in ActivateTask */
      if (((oskApplTaskAccess[taskIndex] & (1UL << osaActiveApplicationID)) == 0))
      {
         COVER(0x020A)
         osSaveActivateTask_TaskID(taskIndex)
         osAPIError(E_OS_ACCESS, osdErrATNoAccess);
         OS_AT_EXIT()
         return E_OS_ACCESS;
      }
      /* TR:SASR30:0021 End */
      ELSEWITHCOVER(0x020B)
   #endif /* (!defined osdSysAPI) */
   
      COVER(0x020C)
      priority = oskTcbHomePrio[taskIndex];
      osSysErrAssert((priority < osrNumberOfPriorities), osdErrATWrongTaskPrio)
   
   
   #if ((CC == ECC2) || (CC == BCC2))
      if (osTcbActivationCount[taskIndex] >= oskTcbAllowedActivations[taskIndex])
      {
         COVER(0x020D)
   #else
      if (osTcbTaskState[taskIndex] != SUSPENDED)
      {
         COVER(0x020E)
   #endif
         osSaveActivateTask_TaskID(taskIndex)
   #ifndef osdSysAPI
         COVER(0x020F)
         osAPIError(E_OS_LIMIT, osdErrATMultipleActivation);
   #else
         COVER(0x0210)
         osAPIError(E_OS_LIMIT, osdErrATAlarmMultipleActivation);
   #endif
         OS_AT_EXIT()
         return E_OS_LIMIT; /* TR:SOSK22:0163 */
      } 
      ELSEWITHCOVER(0x0211)
   
   /* TR:SOSK22:0014 Start This is just informal example which is desribed in UPMF0015 */
   #if osdTimingProtectionUsed
      if (osTPArrivalAllowed(taskIndex)==osdTRUE)
      {
         COVER(0x0212)
   #endif
   /* TR:SOSK22:0014 End */
   #ifndef osdSysAPI
         COVER(0x0213)
         /* KB begin osekHWosDisableTimProtInterrupt (default) */
         #if osdTimingProtectionUsed
         #error "Timing Protection not supported"
         #endif        
         /* KB end osekHWosDisableTimProtInterrupt */
   #endif
   
   #if ((CC == ECC2) || (CC == BCC2))
         if (osTcbActivationCount[taskIndex] == 0)
         {
            COVER(0x0214)
            osTcbTaskState[taskIndex] = PRE_READY;
         }
         ELSEWITHCOVER(0x0215)
         osTcbActivationCount[taskIndex]++;
   #else
         COVER(0x0216)
         osTcbTaskState[taskIndex] = PRE_READY;
   #endif
   
   	  /* TR:SOSK22:0076 Start */
   #if (osdNumberOfExtendedTasks > 0)
   #if ((osdNumberOfExtendedTasks < osdNumberOfAllTasks) || (osdLib))
         if(taskIndex<osrNumberOfExtendedTasks)
         {
            COVER(0x0217)
            osTcbSetEventMask[taskIndex]= 0;    /* with extended tasks clear event field */ /* TR:SOSK22:0076 */
         }
         ELSEWITHCOVER(0x0218)
   #else
         /*all tasks are extended*/
         COVER(0x0219)
         osTcbSetEventMask[taskIndex]= 0;    /* with extended tasks clear event field */
   #endif
   #endif /* (osdNumberOfExtendedTasks > 0) */
   	  /* TR:SOSK22:0076 End */
   
         /* KB begin osQInsertAtPrio (default) */
         #if ((CC == ECC2) || (CC == BCC2))
         COVER(0x021A)
         oskQActivationQueues[priority][osQReadyTaskTail[priority]]= taskIndex; 
         #else
         COVER(0x021B)
         osQReadyTask[priority]= taskIndex;
         #endif
         
         #if (osdRTSize > 1)
         COVER(0x021C)
         osQReadyPrios[oskTcbReadyPrioOffset[taskIndex]]|= oskTcbReadyPrioMask[taskIndex];
         #else
         COVER(0x021D)
         osQReadyPrios|= oskTcbReadyPrioMask[taskIndex];
         #endif
         
         
         #if ((CC == ECC2) || (CC == BCC2))
         COVER(0x021E)
         osQReadyTaskTail[priority]++;
         if (osQReadyTaskTail[priority] > oskQMaxActivations[priority])
         {
            COVER(0x021F)
            osQReadyTaskTail[priority]= 0;
         }
         ELSEWITHCOVER(0x0220)
         #endif
         
         
         /* KB end osQInsertAtPrio */
   
         /* start dispatcher only if new task has greater prio */
         /* TR:SOSK22:0006 Start */
         if (priority < osHighReadyTaskPrio)
         {
   
            COVER(0x0221)
            osHighReadyTaskPrio   = priority;
            osHighReadyTaskIndex  = taskIndex;
            osStartDispatcher= osdTRUE;     /* for return from idle loop */ /* TR:SOSK22:0054 */
         } /* TR:SOSK22:0006 End */
         ELSEWITHCOVER(0x0222)
   #ifndef osdSysAPI
   
         /* KB begin osekHWosEnableTimProtInterrupt (default) */
         #if osdTimingProtectionUsed
         #error "Timing Protection not supported"
         #endif        
         /* KB end osekHWosEnableTimProtInterrupt */
   
   #endif
   
   #if osdTimingProtectionUsed
   
      }/*if (osTPArrivalAllowed(taskIndex))*/
      ELSEWITHCOVER(0x0223)
   #endif
   
   
      OS_AT_EXIT()
      COVER(0x0224)
      return E_OK; /* TR:SOSK22:0147 This is only an example of corectly executed services in the OS */
   /* TR:SOSK22:0001 End */
   /* TR:SOSK22:0016 End */
   /* TR:SOSK22:0017 End */
   /* TR:SOSK22:0018 End */
   /* TR:SOSK22:0019 End */
   /* TR:SOSK22:0020 End */
   /* TR:SOSK22:0029 End */
   /* TR:SOSK22:0030 End */
   /* TR:SOSK22:0047 End */
   /* TR:SOSK22:0050 End */
   /* KB end actTaskBody */
}



#define osdSysAPI
/* version for OS internal use, not using osDisable/osEnable */
/*
 * MISRA RULE 14.1 VIOLATION: The function osSysActivateTask is unused in some configurations. In order to keep the code 
 * simple and error free, it is available in more configurations than necessary.
 */
osqFunc1 StatusType osqFunc2 osSysActivateTask(TaskType taskIndex) /* PRQA S 1503 */ /* TR:SOSK22:0161 */
{
	T1_uint32_t CallerIsTrusted_Cnt_T_u32;
   /* CovComment 4:  Function: osSysActivateTask */
   /* KB begin actTaskBody (default) */
   /* TR:SOSK22:0001 Start */
   /* TR:SOSK22:0016 Start */
   /* TR:SOSK22:0017 Start */
   /* TR:SOSK22:0018 Start */
   /* TR:SOSK22:0019 Start */
   /* TR:SOSK22:0020 Start */ 
   /* TR:SOSK22:0029 Start */
   /* TR:SOSK22:0030 Start */
   /* TR:SOSK22:0047 Start */
   /* TR:SOSK22:0050 Start */
      osPrioType priority;
   
      OS_AT_ENTRY()
      COVER(0x0225)
   #if (!defined osdSysAPI)
      /* check call context */
      /* TR:SASR30:0035 Start Context check in ActivateTask */
      /* TR:SASR30:0336 Start Context check in ActivateTask */
      if ((osdValidCtx_ActivateTask & osCurrentContext) == 0) /* TR:SOSK22:0120 */
      {
         COVER(0x0226)
         osSaveActivateTask_TaskID(taskIndex)
         osAPIError(E_OS_CALLEVEL, osdErrATCallContext); /* TR:SOSK22:0129 */
         OS_AT_EXIT()
         return E_OS_CALLEVEL;
      }
      /* TR:SASR30:0336 End */
      /* TR:SASR30:0035 End */
      ELSEWITHCOVER(0x0227)
   
      if (taskIndex >= osrNumberOfAllTasks)
      {
         COVER(0x0228)
         osSaveActivateTask_TaskID(taskIndex)
         osAPIError(E_OS_ID, osdErrATWrongTaskID);
         OS_AT_EXIT()
         return E_OS_ID; /* TR:SOSK22:0164 */
      }
      ELSEWITHCOVER(0x0229)
      /* TR:SASR30:0038 Start Check disabled interrupts in ActivateTask */
      if (osaIntAPIStatus != 0) /* TR:SOSK22:0254 */
      {
         COVER(0x022A)
         osSaveActivateTask_TaskID(taskIndex)
         osAPIError(E_OS_DISABLEDINT, osdErrATIntAPIDisabled);
         OS_AT_EXIT()
         return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
      }
      /* TR:SASR30:0038 End */
      ELSEWITHCOVER(0x022B)
      /* check access rights for this object */
      /* TR:SASR30:0021 Start Check access rights in ActivateTask */
      if (((oskApplTaskAccess[taskIndex] & (1UL << osaActiveApplicationID)) == 0))
      {
         COVER(0x022C)
         osSaveActivateTask_TaskID(taskIndex)
         osAPIError(E_OS_ACCESS, osdErrATNoAccess);
         OS_AT_EXIT()
         return E_OS_ACCESS;
      }
      /* TR:SASR30:0021 End */
      ELSEWITHCOVER(0x022D)
   #endif /* (!defined osdSysAPI) */
   
      COVER(0x022E)
      priority = oskTcbHomePrio[taskIndex];
      osSysErrAssert((priority < osrNumberOfPriorities), osdErrATWrongTaskPrio)
   
   
   #if ((CC == ECC2) || (CC == BCC2))
      if (osTcbActivationCount[taskIndex] >= oskTcbAllowedActivations[taskIndex])
      {
         COVER(0x022F)
   #else
      if (osTcbTaskState[taskIndex] != SUSPENDED)
      {
         COVER(0x0230)
   #endif
         osSaveActivateTask_TaskID(taskIndex)
   #ifndef osdSysAPI
         COVER(0x0231)
         osAPIError(E_OS_LIMIT, osdErrATMultipleActivation);
   #else
         COVER(0x0232)
         osAPIError(E_OS_LIMIT, osdErrATAlarmMultipleActivation);
   #endif
         OS_AT_EXIT()
         return E_OS_LIMIT; /* TR:SOSK22:0163 */
      } 
      ELSEWITHCOVER(0x0233)
   
   /* TR:SOSK22:0014 Start This is just informal example which is desribed in UPMF0015 */
   #if osdTimingProtectionUsed
      if (osTPArrivalAllowed(taskIndex)==osdTRUE)
      {
         COVER(0x0234)
   #endif
   /* TR:SOSK22:0014 End */
   #ifndef osdSysAPI
         COVER(0x0235)
         /* KB begin osekHWosDisableTimProtInterrupt (default) */
         #if osdTimingProtectionUsed
         #error "Timing Protection not supported"
         #endif        
         /* KB end osekHWosDisableTimProtInterrupt */
   #endif
   
   #if ((CC == ECC2) || (CC == BCC2))
         if (osTcbActivationCount[taskIndex] == 0)
         {
            COVER(0x0236)
            osTcbTaskState[taskIndex] = PRE_READY;
         }
         ELSEWITHCOVER(0x0237)
         osTcbActivationCount[taskIndex]++;
   #else
         COVER(0x0238)
         osTcbTaskState[taskIndex] = PRE_READY;
   #endif
   
   	  /* TR:SOSK22:0076 Start */
   #if (osdNumberOfExtendedTasks > 0)
   #if ((osdNumberOfExtendedTasks < osdNumberOfAllTasks) || (osdLib))
         if(taskIndex<osrNumberOfExtendedTasks)
         {
            COVER(0x0239)
            osTcbSetEventMask[taskIndex]= 0;    /* with extended tasks clear event field */ /* TR:SOSK22:0076 */
         }
         ELSEWITHCOVER(0x023A)
   #else
         /*all tasks are extended*/
         COVER(0x023B)
         osTcbSetEventMask[taskIndex]= 0;    /* with extended tasks clear event field */
   #endif
   #endif /* (osdNumberOfExtendedTasks > 0) */
   	  /* TR:SOSK22:0076 End */
   
         /* KB begin osQInsertAtPrio (default) */
         #if ((CC == ECC2) || (CC == BCC2))
         COVER(0x023C)
         oskQActivationQueues[priority][osQReadyTaskTail[priority]]= taskIndex; 
         #else
         COVER(0x023D)
         osQReadyTask[priority]= taskIndex;
         #endif
         
         #if (osdRTSize > 1)
         COVER(0x023E)
         osQReadyPrios[oskTcbReadyPrioOffset[taskIndex]]|= oskTcbReadyPrioMask[taskIndex];
         #else
         COVER(0x023F)
         osQReadyPrios|= oskTcbReadyPrioMask[taskIndex];
         #endif
         
         
         #if ((CC == ECC2) || (CC == BCC2))
         COVER(0x0240)
         osQReadyTaskTail[priority]++;
         if (osQReadyTaskTail[priority] > oskQMaxActivations[priority])
         {
            COVER(0x0241)
            osQReadyTaskTail[priority]= 0;
         }
         ELSEWITHCOVER(0x0242)
         #endif
         
         
         /* KB end osQInsertAtPrio */
   
         /* start dispatcher only if new task has greater prio */
         /* TR:SOSK22:0006 Start */
         if (priority < osHighReadyTaskPrio)
         {
   
            COVER(0x0243)
            osHighReadyTaskPrio   = priority;
            osHighReadyTaskIndex  = taskIndex;
            osStartDispatcher= osdTRUE;     /* for return from idle loop */ /* TR:SOSK22:0054 */
         } /* TR:SOSK22:0006 End */
         ELSEWITHCOVER(0x0244)
   #ifndef osdSysAPI
   
         /* KB begin osekHWosEnableTimProtInterrupt (default) */
         #if osdTimingProtectionUsed
         #error "Timing Protection not supported"
         #endif        
         /* KB end osekHWosEnableTimProtInterrupt */
   
   #endif
   
   #if osdTimingProtectionUsed
   
      }/*if (osTPArrivalAllowed(taskIndex))*/
      ELSEWITHCOVER(0x0245)
   #endif
   

      CallerIsTrusted_Cnt_T_u32 = osSwitchToPrivMode();
      T1_TraceEvent(T1_ACTIVATION, taskIndex);
      if(0u == CallerIsTrusted_Cnt_T_u32)
      {
            osSwitchToUserMode();
      }
   
      OS_AT_EXIT()
      COVER(0x0246)
      return E_OK; /* TR:SOSK22:0147 This is only an example of corectly executed services in the OS */
   /* TR:SOSK22:0001 End */
   /* TR:SOSK22:0016 End */
   /* TR:SOSK22:0017 End */
   /* TR:SOSK22:0018 End */
   /* TR:SOSK22:0019 End */
   /* TR:SOSK22:0020 End */
   /* TR:SOSK22:0029 End */
   /* TR:SOSK22:0030 End */
   /* TR:SOSK22:0047 End */
   /* TR:SOSK22:0050 End */
   /* KB end actTaskBody */
}

/*-+--------------------------------------------------------------------------
 / TerminateTask
 / =============
 /
 / Syntax:          StatusType TerminateTask ( void )
 / Parameter (In):  none
 / Parameter (Out): none
 / Description:     This service causes the termination of the calling task. 
 /                  The calling task is transferred from the running state 
 /                  into the suspended state.
 / Particularities: An internal resource assigned to the calling task is
 /                  automatically released. Other resources occupied by the 
 /                  task must have been released before the call of 
 /                  TerminateTask. If a resource is still occupied in standard 
 /                  status the behaviour is undefined.
 /                  If the call was successful, TerminateTask does not return 
 /                  to the call level and the status can not be evaluated.
 /                  If the version with extended status is used, the service 
 /                  returns in case of error, and provides a status which 
 /                  can be evaluated in the application.
 /                  If the service TerminateTask is called successfully, 
 /                  it enforces a rescheduling.
 /  -SC1/SC2 only:  Ending a task function without call of TerminateTask or
 /                  ChainTask is strictly forbidden and may leave the system 
 /                  in an undefined state. This error is detected and reported
 /                  by osCAN in extended status.
 /  -SC3/SC4 only:  Ending a task function without call of TerminateTask or
 /                  ChainTask is reported by a call of the ErrorHook, 
 /                  afterwards interrupts are enabled, resources released
 /                  and a task switch is performed like TerminateTask had
 /                  been called.
 / Status:
 /  -Standard:      No return to call level
 /  -Extended:      - Task still occupies resources, E_OS_RESOURCE
 /                  - Call at interrupt level, E_OS_CALLEVEL
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, interrupts enabled, no resources occupied
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/TerminateTask.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
osqFunc1 StatusType osqFunc2 osTerminateTask (void) /* PRQA S 1503 */ /* TR:SOSK22:0166 */
{
   /* CovComment 4:  Function: osTerminateTask */
   OS_TT_ENTRY()
   COVER(0x0247)

   if (osaIntNestingDepth != 0)
   {
      COVER(0x0248)
      osAPIError(E_OS_CALLEVEL, osdErrTTOnInterruptLevel);
      OS_TT_EXIT()
      return E_OS_CALLEVEL; /* TR:SOSK22:0173 */
   }
   ELSEWITHCOVER(0x0249)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in TerminateTask  */
   /* TR:SASR30:0336 Start Context check in TerminateTask  */
   if ((osdValidCtx_TerminateTask & osCurrentContext) == 0)
   {
      COVER(0x024A)
      osAPIError(E_OS_CALLEVEL, osdErrTTCallContext);
      OS_TT_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x024B)
/* TR:SOSK22:0088 Start */
 #if (osdNumberOfInternalResources == 0) && (osdNumberOfInterruptResources == 0)
   /* check for task resources only system */
   if (osActiveTaskPrio != oskTcbHomePrio[osaActiveTaskIndex])
   {
      COVER(0x024C)
 #else
   /* check for mixed resource system (task, interrupt and internal) */
   if (osTcbResourceCounter[osaActiveTaskIndex] != 0)
   {
      COVER(0x024D)
 #endif
      osAPIError(E_OS_RESOURCE, osdErrTTResourcesOccupied);
      OS_TT_EXIT()
      return E_OS_RESOURCE;  /* TR:SOSK22:0168 */ /* TR:SOSK22:0181 */ /* TR:SOSK22:0269 */
   } /* TR:SOSK22:0088 End */
   ELSEWITHCOVER(0x024E)

   /* TR:SASR30:0038 Start Check disabled interrupts in TerminateTask */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x024F)
      osAPIError(E_OS_DISABLEDINT, osdErrTTDisabledInterrupts);
      OS_TT_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x0250)

   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */

#if osdPostTaskHook
   COVER(0x0251)
   /* call PostTaskHook before clearing osRunTaskIndex! */
   osPostTaskHook(); /* TR:SOSK22:0141  */
#endif

#if (osdTimingProtectionUsed != 0)
   COVER(0x0252)
   /* Stop execution time measurement/monitoring */
   osTPExeSwitchBack(INVALID_PROCESS);
#endif

   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */

#if osdNumberOfInternalResources > 0
   COVER(0x0253)
   /* KB begin osReleaseInternalResource (default) */
   /* TR:SOSK22:0099 Start */
   if (oskResInternalCeilingPrioMask[osaActiveTaskIndex] != 0)
   {
   #if osdRTSize == 1
      COVER(0x0254)
      osQReadyPrios &= ~oskResInternalCeilingPrioMask[osaActiveTaskIndex];
   #else
      COVER(0x0255)
      osQReadyPrios[oskResInternalCeilingPrioOffset[osaActiveTaskIndex]] &= /*;*/
         ~oskResInternalCeilingPrioMask[osaActiveTaskIndex];
   #endif
   #if ((CC == ECC2) || (CC == BCC2))
      COVER(0x0256)
      osActiveTaskPrio=oskTcbHomePrio[osaActiveTaskIndex];
   #endif
   
   #if osdORTIDebug
      COVER(0x0257)
      osTcbActualPrio[osaActiveTaskIndex]=oskTcbHomePrio[osaActiveTaskIndex];
   #endif
   
   }
   /* TR:SOSK22:0099 End */
   ELSEWITHCOVER(0x0258)
   
   
   /* KB end osReleaseInternalResource */
#endif

#if ((CC == ECC2) || (CC == BCC2))
   osSysErrAssert(osTcbActivationCount[osaActiveTaskIndex], osdErrTTNotActivated)
   
   COVER(0x0259)
   osTcbActivationCount[osaActiveTaskIndex]--;
   
   if (osTcbActivationCount[osaActiveTaskIndex] != 0)
   {  
      COVER(0x025A)
      osTcbTaskState[osaActiveTaskIndex] = PRE_READY; /* TR:SOSK22:0171 */
   }
   else
   {
      COVER(0x025B)
      osTcbTaskState[osaActiveTaskIndex] = SUSPENDED; /* TR:SOSK22:0039 */ /* TR:SOSK22:0045 */ /* TR:SOSK22:0032 */ /* TR:SOSK22:0033 */
   }
#else
   COVER(0x025C)
   osTcbTaskState[osaActiveTaskIndex] = SUSPENDED; /* TR:SOSK22:0039 */ /* TR:SOSK22:0045 */  /* TR:SOSK22:0032 */ /* TR:SOSK22:0033 */
#endif

   /* KB begin osQDeleteFromPrio (default) */
   
   #if ((CC == ECC2) || (CC == BCC2))
   /* delete task out of the prio queue */
   osQReadyTaskHead[osActiveTaskPrio]++;
   if (osQReadyTaskHead[osActiveTaskPrio] > oskQMaxActivations[osActiveTaskPrio])
   {
      COVER(0x025D)
      osQReadyTaskHead[osActiveTaskPrio]= 0;
   }
   ELSEWITHCOVER(0x025E)
   
   if (osQReadyTaskHead[osActiveTaskPrio] == osQReadyTaskTail[osActiveTaskPrio])
   {  /* queue empty */
      COVER(0x025F)
   #endif
   
   #if (osdRTSize > 1)
      COVER(0x0260)
      osQReadyPrios[oskTcbReadyPrioOffset[osaActiveTaskIndex]]&= ~oskTcbReadyPrioMask[osaActiveTaskIndex];
   #else
      COVER(0x0261)
      osQReadyPrios&= ~oskTcbReadyPrioMask[osaActiveTaskIndex];
   #endif
   
   #if ((CC == ECC2) || (CC == BCC2))
   }
   ELSEWITHCOVER(0x0262)
   #endif
   
   /* KB end osQDeleteFromPrio */

   COVER(0x0263)
   /* KB begin osPrepareForStackCorrection (default) */
   /* KB end osPrepareForStackCorrection */

 #if osdStackCheck
   COVER(0x0264)
   osLastActiveTaskIndex = osaActiveTaskIndex;
 #endif

   /* In safe context, we cannot reset osaActiveTaskIndex and osActivePrio here, so this is done in he osPsys... wrapper */

   /* for TerminateTask, osSchedulePrio returns always osdTRUE! */
   /* (same task is never running after TerminateTask) */
   (void) osSchedulePrio(); 

   OS_TT_EXIT()


   /* TR:SOSK22:0052 Start */
   /* start dispatcher */
   OS_START_DISPATCH()
   osStartDispatcher= osdTRUE;
   osLockDispatcher= osdFALSE;/* TerminateTask() is a scheduling point */
   /* TR:SOSK22:0052 End */
   return E_OK; 


} /* END OF osTerminateTask */


/* TR:SOSK22:0047 Start */
/* TR:SOSK22:0050 Start */
/* TR:SOSK22:0065 Start */
/* TR:SOSK22:0066 Start */
/*-+--------------------------------------------------------------------------
 / ChainTask
 / =========
 /
 / Syntax:          StatusType ChainTask ( TaskType <TaskID> )
 / Parameter (In):  TaskID Reference to the task to be activated after the 
 /                  current task has been terminated.
 / Parameter (Out): none
 / Description:     This service causes the termination of the calling task. 
 /                  After termination of the calling task a succeeding 
 /                  task <TaskID> is activated. Using this service 
 /                  ensures that the succeeding task starts to run 
 /                  earliest after the calling task has been terminated.
 / Particularities: If the succeeding task is identical with the current task, 
 /                  this does not result in multiple requests. The task is not 
 /                  transferred to the suspended state. An internal resource 
 /                  assigned to the calling task is automatically released, 
 /                  even if the succeeding task is identical with the current 
 /                  task. Other resources occupied by the calling task must 
 /                  have been released before ChainTask is called. If a 
 /                  resource is still occupied in standard status the 
 /                  behaviour is undefined.
 /                  If called successfully, ChainTask does not return to the 
 /                  call level and the status can not be evaluated.
 /                  In case of error the service returns to the calling task 
 /                  and provides a status which can then be evaluated in the
 /                  application.
 /                  If the service ChainTask is called successfully, this 
 /                  enforces a rescheduling.
 /                  If E_OS_LIMIT is returned the activation is ignored.
 /                  When an extended task is transferred from suspended state
 /                  into ready state all its events are cleared.
 /  -SC1/SC2 only:  Ending a task function without call of TerminateTask or
 /                  ChainTask is strictly forbidden and may leave the system 
 /                  in an undefined state. This error is detected and reported
 /                  by osCAN in extended status.
 /  -SC3/SC4 only:  Ending a task function without call of TerminateTask or
 /                  ChainTask is reported by a call of the ErrorHook, 
 /                  afterwards interrupts are enabled, resources released
 /                  and a task switch is performed like TerminateTask had
 /                  been called.
 / Status:
 /  -Standard:      - No return to call level
 /                  - Too many task activations of <TaskID>, E_OS_LIMIT
 /  -Extended:      - Task <TaskID> is invalid, E_OS_ID
 /                  - Calling task still occupies resources, E_OS_RESOURCE
 /                  - Call at interrupt level, E_OS_CALLEVEL
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, interrupts enabled, no resources occupied
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/ChainTask.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
osqFunc1 StatusType osqFunc2 osChainTask(TaskType taskIndex) /* PRQA S 1503 */ /* TR:SOSK22:0170 */
{
   /* CovComment 4:  Function: osChainTask */
   osPrioType priority;
#if (osdTimingProtectionUsed != 0)
   osbool ActivationAllowed;
#endif

   OS_HT_ENTRY()
   COVER(0x0265)

   if (osaIntNestingDepth != 0)
   {
      COVER(0x0266)
      osSaveChainTask_TaskID(taskIndex)
      osAPIError(E_OS_CALLEVEL, osdErrHTOnInterruptLevel);
      OS_HT_EXIT()
      return E_OS_CALLEVEL; /* TR:SOSK22:0177 */
   }
   ELSEWITHCOVER(0x0267)

   /* check call context */
   /* TR:SASR30:0035 Start Context check in ChainTask  */
   /* TR:SASR30:0336 Start Context check in ChainTask  */
   if ((osdValidCtx_ChainTask & osCurrentContext) == 0)
   {
      COVER(0x0268)
      osSaveChainTask_TaskID(taskIndex)
      osAPIError(E_OS_CALLEVEL, osdErrHTCallContext);
      OS_HT_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x0269)
/* TR:SOSK22:0088 Start */
#if (osdNumberOfInternalResources == 0) && (osdNumberOfInterruptResources == 0)
   /* check for task resources only system */
   if (osActiveTaskPrio != oskTcbHomePrio[osaActiveTaskIndex])
   {
      COVER(0x026A)
#else
   /* check for mixed resource system (task, interrupt and internal) */
   if (osTcbResourceCounter[osaActiveTaskIndex] != 0)
   {
      COVER(0x026B)
#endif
      osSaveChainTask_TaskID(taskIndex)
      osAPIError(E_OS_RESOURCE, osdErrHTResourcesOccupied);
      OS_HT_EXIT()
      return E_OS_RESOURCE; /* TR:SOSK22:0176 */ /* TR:SOSK22:0269 */
   } /* TR:SOSK22:0088 End */
   ELSEWITHCOVER(0x026C)


   if (taskIndex >= osrNumberOfAllTasks)
   {
      COVER(0x026D)
      osSaveChainTask_TaskID(taskIndex)
      osAPIError(E_OS_ID, osdErrHTWrongTaskID);
      OS_HT_EXIT()
      return E_OS_ID; /* TR:SOSK22:0175 */
   }
   ELSEWITHCOVER(0x026E)
   /* TR:SASR30:0038 Start Check disabled interrupts in ChainTask */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x026F)
      osSaveChainTask_TaskID(taskIndex)
      osAPIError(E_OS_DISABLEDINT, osdErrHTInterruptsDisabled);
      OS_HT_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x0270)

   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in ChainTask */
   if (((oskApplTaskAccess[taskIndex] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x0271)
      osSaveChainTask_TaskID(taskIndex)
      osAPIError(E_OS_ACCESS, osdErrHTNoAccess);
      OS_HT_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x0272)

   if (taskIndex != osaActiveTaskIndex)
   {
#if ((CC == ECC2) || (CC == BCC2))
      if (osTcbActivationCount[taskIndex] >= oskTcbAllowedActivations[taskIndex])
      {
         COVER(0x0273)
#else
      if (osTcbTaskState[taskIndex] != SUSPENDED)
      {
         COVER(0x0274)
#endif
         osSaveChainTask_TaskID(taskIndex)
         osAPIError(E_OS_LIMIT, osdErrHTMultipleActivation);
         OS_HT_EXIT()
         return E_OS_LIMIT; /* TR:SOSK22:0174 */
      }
      ELSEWITHCOVER(0x0275)
   }
   ELSEWITHCOVER(0x0276)

   /*************************************************************************
    * terminate old task
    *************************************************************************/

   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */

   /* call hook routine for the terminated task */
#if osdPostTaskHook
   COVER(0x0277)
   /* call PostTaskHook before clearing osaActiveTaskIndex! */
   osPostTaskHook(); /* TR:SOSK22:0141  */
#endif

   T1_TraceStop(osaActiveTaskIndex);

#if osdNumberOfInternalResources > 0
   COVER(0x0278)
   /* KB begin osReleaseInternalResource (default) */
   /* TR:SOSK22:0099 Start */
   if (oskResInternalCeilingPrioMask[osaActiveTaskIndex] != 0)
   {
   #if osdRTSize == 1
      COVER(0x0279)
      osQReadyPrios &= ~oskResInternalCeilingPrioMask[osaActiveTaskIndex];
   #else
      COVER(0x027A)
      osQReadyPrios[oskResInternalCeilingPrioOffset[osaActiveTaskIndex]] &= /*;*/
         ~oskResInternalCeilingPrioMask[osaActiveTaskIndex];
   #endif
   #if ((CC == ECC2) || (CC == BCC2))
      COVER(0x027B)
      osActiveTaskPrio=oskTcbHomePrio[osaActiveTaskIndex];
   #endif
   
   #if osdORTIDebug
      COVER(0x027C)
      osTcbActualPrio[osaActiveTaskIndex]=oskTcbHomePrio[osaActiveTaskIndex];
   #endif
   
   }
   /* TR:SOSK22:0099 End */
   ELSEWITHCOVER(0x027D)
   
   
   /* KB end osReleaseInternalResource */
#endif

#if ((CC == ECC2) || (CC == BCC2))
#if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x027E)
   osSysErrAssert(osTcbActivationCount[osaActiveTaskIndex], osdErrHTNotActivated)
#endif

   osTcbActivationCount[osaActiveTaskIndex]--;

   if (osTcbActivationCount[osaActiveTaskIndex] != 0)
   {  
      COVER(0x027F)
      osTcbTaskState[osaActiveTaskIndex] = PRE_READY;
   }
   else
   {
      COVER(0x0280)
      osTcbTaskState[osaActiveTaskIndex] = SUSPENDED; /* TR:SOSK22:0039 */ /* TR:SOSK22:0045 */
   }
#else /* ((CC == ECC2) || (CC == BCC2)) */
   COVER(0x0281)
   osTcbTaskState[osaActiveTaskIndex] = SUSPENDED; /* TR:SOSK22:0039 */ /* TR:SOSK22:0045 */
#endif /* ((CC == ECC2) || (CC == BCC2)) else */

   COVER(0x0282)
   /* KB begin osQDeleteFromPrio (default) */
   
   #if ((CC == ECC2) || (CC == BCC2))
   /* delete task out of the prio queue */
   osQReadyTaskHead[osActiveTaskPrio]++;
   if (osQReadyTaskHead[osActiveTaskPrio] > oskQMaxActivations[osActiveTaskPrio])
   {
      COVER(0x0283)
      osQReadyTaskHead[osActiveTaskPrio]= 0;
   }
   ELSEWITHCOVER(0x0284)
   
   if (osQReadyTaskHead[osActiveTaskPrio] == osQReadyTaskTail[osActiveTaskPrio])
   {  /* queue empty */
      COVER(0x0285)
   #endif
   
   #if (osdRTSize > 1)
      COVER(0x0286)
      osQReadyPrios[oskTcbReadyPrioOffset[osaActiveTaskIndex]]&= ~oskTcbReadyPrioMask[osaActiveTaskIndex];
   #else
      COVER(0x0287)
      osQReadyPrios&= ~oskTcbReadyPrioMask[osaActiveTaskIndex];
   #endif
   
   #if ((CC == ECC2) || (CC == BCC2))
   }
   ELSEWITHCOVER(0x0288)
   #endif
   
   /* KB end osQDeleteFromPrio */


   /* KB begin osPrepareForStackCorrection (default) */
   /* KB end osPrepareForStackCorrection */

 #if osdStackCheck
   COVER(0x0289)
   osLastActiveTaskIndex = osaActiveTaskIndex;
 #endif

#if (osdTimingProtectionUsed != 0)
   if (osaActiveTaskIndex == taskIndex)
   {
      COVER(0x028A)
      /* Stop execution time measurement/monitoring */
      (void)osTPExeSwitchTo(INVALID_PROCESS);
      /* self activation always possible, no new budget, not considered as an arrival */
      ActivationAllowed = osdTRUE;
   }
   else
   {
      COVER(0x028B)
      /* Stop execution time measurement/monitoring, refresh execution time budget */
      osTPExeSwitchBack(INVALID_PROCESS);
      /* check whether the activation is allowed, considering the time since last activation */
      ActivationAllowed = osTPArrivalAllowed(taskIndex);
   }
#endif

   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */

   /* In safe context, we cannot reset osaActiveTaskIndex and osActivePrio here, so this is done in he osPsys... wrapper */

   
#if (osdTimingProtectionUsed != 0)
   if (ActivationAllowed == osdTRUE)
   {
      COVER(0x028C)
#endif

      /*************************************************************************
       * now activate the new task
       *************************************************************************/

#if (STATUS_LEVEL == STANDARD_STATUS)
      #if ((CC == ECC2) || (CC == BCC2))
      if (osTcbActivationCount[taskIndex] < oskTcbAllowedActivations[taskIndex])
      {
         COVER(0x028D)
      #else
      if (osTcbTaskState[taskIndex] == SUSPENDED)
      {
         COVER(0x028E)
      #endif
#endif
         priority = oskTcbHomePrio[taskIndex];
         osSysErrAssert((priority < osrNumberOfPriorities), osdErrHTWrongTaskPrio)

#if (osdNumberOfExtendedTasks > 0)
 #if ((osdNumberOfExtendedTasks < osdNumberOfAllTasks) || (osdLib))
         /* with extended tasks clear event field */
         if(taskIndex < osrNumberOfExtendedTasks)
         {
            COVER(0x028F)
            osTcbSetEventMask[taskIndex]= 0;
         }
         ELSEWITHCOVER(0x0290)
 #else /* ((osdNumberOfExtendedTasks < osdNumberOfAllTasks) || (osdLib)) */
         COVER(0x0291)
         /* no basic tasks, so for all tasks clear event field */
         osTcbSetEventMask[taskIndex] = 0;
 #endif /* ((osdNumberOfExtendedTasks < osdNumberOfAllTasks) || (osdLib)) */
#endif /* (osdNumberOfExtendedTasks > 0) */

#if ((CC == ECC2) || (CC == BCC2))
         if (osTcbActivationCount[taskIndex] == 0)
         {
            COVER(0x0292)
            osTcbTaskState[taskIndex] = PRE_READY; /* TR:SOSK22:0171 */
         }
         ELSEWITHCOVER(0x0293)
         osTcbActivationCount[taskIndex]++;
#else
         COVER(0x0294)
         osTcbTaskState[taskIndex] = PRE_READY; /* TR:SOSK22:0171 */
#endif

         COVER(0x0295)
         /* KB begin osQInsertAtPrio (default) */
         #if ((CC == ECC2) || (CC == BCC2))
         COVER(0x0296)
         oskQActivationQueues[priority][osQReadyTaskTail[priority]]= taskIndex; 
         #else
         COVER(0x0297)
         osQReadyTask[priority]= taskIndex;
         #endif
         
         #if (osdRTSize > 1)
         COVER(0x0298)
         osQReadyPrios[oskTcbReadyPrioOffset[taskIndex]]|= oskTcbReadyPrioMask[taskIndex];
         #else
         COVER(0x0299)
         osQReadyPrios|= oskTcbReadyPrioMask[taskIndex];
         #endif
         
         
         #if ((CC == ECC2) || (CC == BCC2))
         COVER(0x029A)
         osQReadyTaskTail[priority]++;
         if (osQReadyTaskTail[priority] > oskQMaxActivations[priority])
         {
            COVER(0x029B)
            osQReadyTaskTail[priority]= 0;
         }
         ELSEWITHCOVER(0x029C)
         #endif
         
         
         /* KB end osQInsertAtPrio */
#if (STATUS_LEVEL == STANDARD_STATUS)
      }
      ELSEWITHCOVER(0x029D)
#endif
#if (osdTimingProtectionUsed != 0)

   }/*if (ActivationAllowed == osdTRUE)*/
   ELSEWITHCOVER(0x029E)
#endif
   COVER(0x029F)
   (void) osSchedulePrio(); 

   OS_HT_END_CRITICAL()
   OS_HT_EXIT()


   /* TR:SOSK22:0053 Start */
   /* start dispatcher */ 
   OS_START_DISPATCH()
   osStartDispatcher= osdTRUE;
   osLockDispatcher= osdFALSE;/* ChainTask is a scheduling point */ /* TR:SOSK22:0053 End */
   return E_OK;


} /* END OF osChainTask */ /* TR:SOSK22:0047 End */ /* TR:SOSK22:0050 End */ /* TR:SOSK22:0065 End */
  /* TR:SOSK22:0066 End */

/* TR:SOSK22:0049 Start */
/*-+--------------------------------------------------------------------------
 / Schedule
 / ========
 /
 / Syntax:          StatusType Schedule ( void )
 / Parameter (In):  none
 / Parameter (Out): none
 / Description:     If a higher-priority task is ready, the internal resource 
 /                  of the current task is released, the current task is put 
 /                  into the ready state, its context is saved and the 
 /                  higher-priority task is executed.
 /                  Otherwise the calling task is continued.
 / Particularities: Rescheduling can only take place if an internal resource is
 /                  assigned to the calling task during system generation.
 /                  (A non-preemptable task is seen as a task with a resource
 /                  of highest task priority assigned.) For these tasks, Schedule 
 /                  enables a processor assignment to other tasks with lower 
 /                  priority than the ceiling priority of the internal
 /                  resource and higher priority than the priority of the 
 /                  calling task in application-specific locations. 
 /                  When returning from Schedule, the internal resource has 
 /                  been taken again.
 /                  This service has no influence on tasks with no internal 
 /                  resource assigned (preemptable tasks).
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Call at interrupt level, E_OS_CALLEVEL
 /                  - Calling task occupies resources, E_OS_RESOURCE
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, interrupts enabled, no resources occupied
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/Schedule.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
/* TR:SOSK22:0059 Start */
osqFunc1 StatusType osqFunc2 osSchedule(void) /* PRQA S 1503 */  /* TR:SOSK22:0179 */
{
   /* CovComment 4:  Function: osSchedule */

   OS_SH_ENTRY()
   COVER(0x02A0)
   if (osaIntNestingDepth != 0)
   {
      COVER(0x02A1)
      osAPIError(E_OS_CALLEVEL, osdErrSHOnInterruptLevel);
      OS_SH_EXIT()
      return E_OS_CALLEVEL; /* TR:SOSK22:0180 */
   }
   ELSEWITHCOVER(0x02A2)

   /* check call context */
   /* TR:SASR30:0035 Start Context check in Schedule  */
   /* TR:SASR30:0336 Start Context check in Schedule  */
   if ((osdValidCtx_Schedule & osCurrentContext) == 0)
   {
      COVER(0x02A3)
      osAPIError(E_OS_CALLEVEL, osdErrSHCallContext);
      OS_SH_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x02A4)
   /* TR:SASR30:0038 Start Check disabled interrupts in Schedule */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x02A5)
      osAPIError(E_OS_DISABLEDINT, osdErrSHInterruptsDisabled);
      OS_SH_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x02A6)
/* TR:SOSK22:0088 Start */
#if (osdNumberOfInternalResources == 0) && (osdNumberOfInterruptResources == 0)
   /* check for task resources only system */
   if (osActiveTaskPrio != oskTcbHomePrio[osaActiveTaskIndex])
   {
      COVER(0x02A7)
#else
   /* check for mixed resource system (task, interrupt and internal) */
   if (osTcbResourceCounter[osaActiveTaskIndex] != 0)
   {
      COVER(0x02A8)
#endif
      osAPIError(E_OS_RESOURCE, osdErrSHResourcesOccupied);
      OS_SH_EXIT()
      return E_OS_RESOURCE; /* TR:SOSK22:0181 */ /* TR:SOSK22:0269 */
   } /* TR:SOSK22:0088 End */
   ELSEWITHCOVER(0x02A9)

   osSysErrAssert(((oskTcbTaskFlags[osaActiveTaskIndex] & osdTaskFlagNotUsingSchedule) == 0U),
       osdErrSHScheduleNotAllowed)   /* NOCOV */     


   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */

#if osdNumberOfInternalResources > 0
   COVER(0x02AA)
   /* KB begin osReleaseInternalResourceSchedule (default) */
   if (oskResInternalCeilingPrioMask[osaActiveTaskIndex] != 0)
   {
   #if osdRTSize == 1
      COVER(0x02AB)
      osQReadyPrios &= ~oskResInternalCeilingPrioMask[osaActiveTaskIndex];
   #else
      COVER(0x02AC)
      osQReadyPrios[oskResInternalCeilingPrioOffset[osaActiveTaskIndex]] &= /*;*/
         ~oskResInternalCeilingPrioMask[osaActiveTaskIndex];
   #endif
   
   #if osdORTIDebug
      COVER(0x02AD)
      osTcbActualPrio[osaActiveTaskIndex]=oskTcbHomePrio[osaActiveTaskIndex];
   #endif
   }
   ELSEWITHCOVER(0x02AE)
   
   /* KB end osReleaseInternalResourceSchedule */
#endif

   if (osSchedulePrio() != 0)
   {
      COVER(0x02AF)
      OS_SH_EXIT()
      /* KB begin osekHWosEnableTimProtInterrupt (default) */
      #if osdTimingProtectionUsed
      #error "Timing Protection not supported"
      #endif        
      /* KB end osekHWosEnableTimProtInterrupt */

      /* start dispatcher */
      OS_START_DISPATCH()
      osStartDispatcher= osdTRUE;
      osLockDispatcher= osdFALSE;/* Schedule() is a scheduling point */ /* TR:SOSK22:0048 */

      return E_OK;
   }
   ELSEWITHCOVER(0x02B0)

#if osdNumberOfInternalResources > 0
   COVER(0x02B1)
   /* KB begin osGetInternalResourceSchedule (default) */
   if (oskResInternalCeilingPrioMask[osaActiveTaskIndex] != 0)
   {
   #if osdRTSize == 1
      COVER(0x02B2)
      osQReadyPrios |= oskResInternalCeilingPrioMask[osaActiveTaskIndex];
   #else
      COVER(0x02B3)
      osQReadyPrios[oskResInternalCeilingPrioOffset[osaActiveTaskIndex]] |= /*;*/
         oskResInternalCeilingPrioMask[osaActiveTaskIndex];
   #endif
   
      /* osHighReadyTaskPrio is modified in osSchedulePrio */
      osHighReadyTaskPrio = oskResInternalCeilingPrio[osaActiveTaskIndex];
   
   #if osdORTIDebug
      COVER(0x02B4)
      osTcbActualPrio[osaActiveTaskIndex]=osActiveTaskPrio;
   #endif
   
   }
   ELSEWITHCOVER(0x02B5)
   /* KB end osGetInternalResourceSchedule */
#endif

   COVER(0x02B6)
   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_SH_EXIT()
   return E_OK;
} /* END OF osSchedule */ /* TR:SOSK22:0049 End */ /* TR:SOSK22:0059 End */



/*-+--------------------------------------------------------------------------
 / GetTaskID
 / =========
 /
 / Syntax:          StatusType GetTaskID ( TaskRefType <TaskID> )
 / Parameter (In):  none
 / Parameter (Out): TaskID Reference to the task which is currently running
 / Description:     GetTaskID writes the information about the TaskID of the 
 /                  task which is currently running to the location, defined
 /                  by the reference TaskID.
 / Particularities: Allowed on task level, ISR level and in several hook 
 /                  routines.
 /                  This service is intended to be used by library functions 
 /                  and hook routines.
 /                  If <TaskID> can't be evaluated (no task currently 
 /                  running), the service returns INVALID_TASK as TaskID.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - No error, E_OK
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, Cat2-ISR, ErrorHook, PreTaskHook, PostTaskHook,
 /                  ProtectionHook, interrupts not disabled by the 
 /                  application
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/GetTaskID.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
osqFunc1 TaskType osqFunc2 osGetTaskID (TaskRefType TaskId) /* PRQA S 1503 */ /* TR:SOSK22:0183 */
{
   /* CovComment 4:  Function: osGetTaskID */
   
   OS_GI_ENTRY()
   COVER(0x02B7)

   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. (3199) */
   osdDummyRead(TaskId) /* PRQA S 3199 */
   
   /* check call context */
   /* TR:SASR30:0035 Start Context check in GetTaskID  */
   /* TR:SASR30:0336 Start Context check in GetTaskID  */
   if ((osdValidCtx_GetTaskID & osCurrentContext) == 0)
   {
      COVER(0x02B8)
      osSaveGetTaskID_TaskID(TaskId)
      osAPIError(E_OS_CALLEVEL, osdErrGICallContext);
      OS_GI_EXIT()
      osStatusTypeReturn = E_OS_CALLEVEL;
      return 0;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x02B9)
   /* TR:SASR30:0038 Start Check disabled interrupts in GetTaskID */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x02BA)
      osSaveGetTaskID_TaskID(TaskId)
      osAPIError(E_OS_DISABLEDINT, osdErrGIIntAPIDisabled);
      OS_GI_EXIT()
      osStatusTypeReturn = E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
      return 0;
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x02BB)

   COVER(0x02BC)

   OS_GI_EXIT()
   /* TR:SOSK22:0239 Start */
   osStatusTypeReturn = E_OK;   
   return osaActiveTaskIndex;  
   /* TR:SOSK22:0239 End */
} /* END OF osGetTaskID */



/*-+--------------------------------------------------------------------------
 / GetTaskState
 / ============
 /
 / Syntax:          StatusType GetTaskState ( TaskType <TaskID>,
 /                                            TaskStateRefType <State> )
 / Parameter (In):  TaskID Task reference
 / Parameter (Out): State Reference to the state of the task <TaskID>
 / Description:     Writes the current state of a task (RUNNING, READY, WAITING, 
 /                  SUSPENDED) to the location, defined by the parameter
 /                  State.
 / Particularities: The service may be called from interrupt service routines, 
 /                  task level, and some hook routines.
 /                  When a call is made from a task in a full preemptive system,
 /                  the result may already be incorrect at the time of 
 /                  evaluation.
 /                  When the service is called for a task, which is multiply
 /                  activated, the state is set to running if any instance 
 /                  of the task is running.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Task <TaskID> is invalid, E_OS_ID
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, Cat2-ISR, ErrorHook, PreTaskHook, PostTaskHook,
 /                  interrupts not disabled by the application
/--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/GetTaskState.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
osqFunc1 TaskStateType osqFunc2 osGetTaskState(TaskType TaskId, TaskStateRefType State) /* PRQA S 1503 */ /* TR:SOSK22:0184 */
{
   /* CovComment 4:  Function: osGetTaskState */

   OS_GS_ENTRY()
   COVER(0x02BD)

   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. (3199) */
   osdDummyRead(State) /* PRQA S 3199 */
   
   /* check call context */
   /* TR:SASR30:0035 Start Context check in GetTaskState  */
   /* TR:SASR30:0336 Start Context check in GetTaskState  */
   if ((osdValidCtx_GetTaskState & osCurrentContext) == 0)
   {
      COVER(0x02BE)
      osSaveGetTaskState_TaskID(TaskId)
      osSaveGetTaskState_State(State)
      osAPIError(E_OS_CALLEVEL, osdErrGSCallContext);
      OS_GS_EXIT()
      osStatusTypeReturn = E_OS_CALLEVEL;
      return 0;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x02BF)

   /* 5011271_ISSUE_12 (ESOS00003678): Moved the following code here so that the access of oskApplTaskAccess becomes save */
   if (TaskId >= osrNumberOfAllTasks)
   {
      COVER(0x02C0)
      osSaveGetTaskState_TaskID(TaskId)
      osSaveGetTaskState_State(State)
      osAPIError(E_OS_ID, osdErrGSWrongTaskID);
      OS_GS_EXIT()
      osStatusTypeReturn = E_OS_ID; /* TR:SOSK22:0244 */
      return 0;
   }
   ELSEWITHCOVER(0x02C1)
   /* 5011271_ISSUE_12 (ESOS00003678): End change */

   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in GetTaskState */
   if (((oskApplTaskAccess[TaskId] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x02C2)
      osSaveGetTaskState_TaskID(TaskId)
      osSaveGetTaskState_State(State)
      osAPIError(E_OS_ACCESS, osdErrGSNoAccess);
      OS_GS_EXIT()
      osStatusTypeReturn = E_OS_ACCESS;
      return 0;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x02C3)

   /* 5011271_ISSUE_12 (ESOS00003678): Moved check of TaskId to the marked place above */
   /* TR:SASR30:0038 Start Check disabled interrupts in GetTaskState */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x02C4)
      osSaveGetTaskState_TaskID(TaskId)
      osSaveGetTaskState_State(State)
      osAPIError(E_OS_DISABLEDINT, osdErrGSIntAPIDisabled);
      OS_GS_EXIT()
      osStatusTypeReturn = E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
      return 0;
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x02C5)


   COVER(0x02C6)
   OS_GS_EXIT()
   osStatusTypeReturn = E_OK; /* TR:SOSK22:0243 */
   /* TR:SOSK22:0241 Start */
   /* change PRE_READY to READY */
   if (osTcbTaskState[TaskId] == PRE_READY)
   {
      COVER(0x02C7)
      return READY;
   }
   ELSEWITHCOVER(0x02C8)
   return osTcbTaskState[TaskId];  /* TR:SOSK22:0241 End */
} /* END OF osGetTaskState */


#else /* (osdNumberOfAllTasks > 0) */

/* Start fix of 5011271_ISSUE_14 (empty functions for task API if no tasks are configured) */

/* MISRA RULE 14.1 violated: (comment 1503) In SafeContext implementations all APIs are
 * encapsulated in wrappers. This wrappers belong to static ASIL code and must exist,
 * even if they are not used in a project.
 */
osqFunc1 StatusType osqFunc2 osActivateTask(TaskType taskIndex) /* PRQA S 1503 */
{
   osdDummyRead(taskIndex) /* PRQA S 3199 */
   return E_OK;
}

osqFunc1 StatusType osqFunc2 osTerminateTask (void) /* PRQA S 1503 */
{
   return E_OK;
}
osqFunc1 StatusType osqFunc2 osChainTask(TaskType taskIndex) /* PRQA S 1503 */
{
   osdDummyRead(taskIndex) /* PRQA S 3199 */
   return E_OK;
}
osqFunc1 StatusType osqFunc2 osSchedule(void) /* PRQA S 1503 */
{
   return E_OK;
}
osqFunc1 TaskType osqFunc2 osGetTaskID (TaskRefType TaskId) /* PRQA S 1503 */
{
   osdDummyRead(TaskId)    /* PRQA S 3199 */
   return E_OK;
}
osqFunc1 TaskStateType osqFunc2 osGetTaskState(TaskType TaskId, TaskStateRefType State) /* PRQA S 1503 */
{
   osdDummyRead(TaskId)    /* PRQA S 3199 */
   osdDummyRead(State)     /* PRQA S 3199 */
   return E_OK;
}

/* End fix of 5011271_ISSUE_14 (empty functions for task API if no tasks are configured) */

#endif /* (osdNumberOfAllTasks > 0) */


/* KB begin osekEndOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
/* Reset to default section TR:SPMF49:0004 */
#pragma SET_CODE_SECTION()
#endif
/* KB end osekEndOfCModule */

/* END OF MODULE osektask.c */
