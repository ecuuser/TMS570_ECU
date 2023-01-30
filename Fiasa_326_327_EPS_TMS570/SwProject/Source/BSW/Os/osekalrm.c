/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osekalrm.c
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.57
|  Description: osek API-functions for handling alarms and counters
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2012 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/


/* next define is set in the makefile
 * switches off the include of (generated) tcb.h, includes instead
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

/* CovComment 0:  file: osekalrm.c */

/* KB begin osekStartOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_CODE_SECTION(".oscode") /* TR:SPMF49:0001 */ /* TR:SPMF49:0002 */
#endif
/* KB end osekStartOfCModule */

/* TR:SOSK22:0113 Start */
/*-+--------------------------------------------------------------------------
 / GetAlarm
 / ========
 /
 / Syntax:          StatusType GetAlarm ( AlarmType <AlarmID>, 
 /                                        TickRefType <Tick>)
 / Parameter (In):  AlarmID Reference to an alarm
 / Parameter (Out): Tick Relative value in ticks before the alarm <AlarmID> 
 /                  expires.
 / Description:     The system service GetAlarm returns the relative value in 
 /                  ticks before the alarm <AlarmID> expires.
 / Particularities: It is up to the application to decide whether for example 
 /                  a CancelAlarm may still be useful.
 /                  If <AlarmID> is not in use, <Tick> is not defined.
 /                  Allowed on task level, ISR, and in several hook routines.
 / Status:
 /  -Standard:      - No error, E_OK
 /                  - Alarm <AlarmID> is not used, E_OS_NOFUNC
 /  -Extended:      - Alarm <AlarmID> is invalid, E_OS_ID
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, Cat2-ISR, ErrorHook, PreTaskHook, PostTaskHook,
 /                  interrupts not disabled by the application
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 not violated: (comment 1503) In not SafeContext projects this function 
 * may be switched off by the OS configuration parameter OS/APIOptimization/Manual/GetAlarm 
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and exist, even if they are not used in a project. 
 */
osqFunc1 TickType osqFunc2 osGetAlarm(AlarmType alarmID, TickRefType diffTickTime) /* PRQA S 1503 */ /* TR:SOSK22:0198 */
{
   /* CovComment 4:  Function: osGetAlarm */
   
#if (osdNumberOfAlarms > 0)
   TickType retval;
   
   OS_GA_ENTRY()
   COVER(0x0055)

   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. */    
   osdDummyRead(diffTickTime) /* PRQA S 3199 */

   COVER(0x0056)
   /* check call context */
   /* TR:SOSK22:0116 Start */
   /* TR:SASR30:0035 Start Context check in GetAlarm */
   /* TR:SASR30:0336 Start Context check in GetAlarm */
   if ((osdValidCtx_GetAlarm & osCurrentContext) == 0)
   {
      COVER(0x0057)
      osSaveGetAlarm_AlarmID(alarmID)
      osSaveGetAlarm_Tick(diffTickTime)
      osAPIError(E_OS_CALLEVEL, osdErrGACallContext);
      OS_GA_EXIT()
      osStatusTypeReturn = E_OS_CALLEVEL;
      return 0;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   /* TR:SOSK22:0116 End */
   ELSEWITHCOVER(0x0058)

   /* check timer ID */
   if (alarmID >= osrNumberOfAlarms)
   {
#else
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. */    
      osdDummyRead(alarmID)     /* PRQA S 3199 */
      osdDummyRead(diffTickTime)/* PRQA S 3199 */
#endif /*(osdNumberOfAlarms > 0)*/
      COVER(0x0059)
      osSaveGetAlarm_AlarmID(alarmID)
      osSaveGetAlarm_Tick(diffTickTime)
      osAPIError(E_OS_ID, osdErrGAWrongAlarmID);
#if (osdNumberOfAlarms > 0)                           /* 5011271_ISSUE_02 */
      OS_GA_EXIT()
#endif /*(osdNumberOfAlarms > 0)*/                    /* 5011271_ISSUE_02 */
      osStatusTypeReturn = E_OS_ID; /* TR:SOSK22:0322 */
      return 0;
#if (osdNumberOfAlarms > 0)
   }
   ELSEWITHCOVER(0x005A)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in GetAlarm */
   if (((oskApplAlarmAccess[alarmID] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x005B)
      osSaveGetAlarm_AlarmID(alarmID)
      osSaveGetAlarm_Tick(diffTickTime)
      osAPIError(E_OS_ACCESS, osdErrGANoAccess);
      OS_GA_EXIT()
      osStatusTypeReturn = E_OS_ACCESS;
      return 0;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x005C)
   /* TR:SASR30:0038 Start Check disabled interrupts in GetAlarm */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x005D)
      osSaveGetAlarm_AlarmID(alarmID)
      osSaveGetAlarm_Tick(diffTickTime)
      osAPIError(E_OS_DISABLEDINT, osdErrGAIntAPIDisabled);
      OS_GA_EXIT()
      osStatusTypeReturn = E_OS_DISABLEDINT;  /* TR:SOSK22:0074 */
      return 0;
   } /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x005E)


   /* if timer is inactive, return at once */
#if (osdUseHeap != 0)
   if (osAlarmActivated[alarmID] == 0)
   {
      COVER(0x005F)
#else
   if (osAlarmTime[alarmID] == 0)
   {
      COVER(0x0060)
#endif
      osSaveGetAlarm_AlarmID(alarmID)
      osSaveGetAlarm_Tick(diffTickTime)
      osAPIError(E_OS_NOFUNC, osdErrGANotActive);
      OS_GA_EXIT()
      osStatusTypeReturn = E_OS_NOFUNC; /* TR:SOSK22:0321 */
      return 0;
   }
   ELSEWITHCOVER(0x0061)

#if (osdUseHeap != 0)
   COVER(0x0062)
   retval = osAlarmTime[alarmID] - osGetSystemCounter();
#else
   COVER(0x0063)
   retval = osAlarmTime[alarmID];
#endif

   OS_GA_EXIT()
   osStatusTypeReturn = E_OK; /* TR:SOSK22:0320 */
   return retval; /* TR:SOSK22:0317 */
#endif /*(osdNumberOfAlarms > 0)*/
} /* END OF osGetAlarm */ /* TR:SOSK22:0113 End */

/* TR:SOSK22:0109 Start */
/* TR:SOSK22:0319 Start */
/*-+--------------------------------------------------------------------------
 / SetRelAlarm
 / ===========
 /
 / Syntax:          StatusType SetRelAlarm ( AlarmType <AlarmID>,
 /                                           TickType <increment>,
 /                                           TickType <cycle> )
 / Parameter (In):  -AlarmID Reference to the alarm element
 /                  -increment Relative value in ticks
 /                  -cycle Cycle value in case of cyclic alarm. In case of 
 /                   single alarms, cycle has to be zero.
 / Parameter (Out): none
 / Description:     The system service occupies the alarm <AlarmID> element.
 /                  After <increment> ticks have elapsed, the task assigned 
 /                  to the alarm <AlarmID> is activated or the assigned event
 /                  (only for extended tasks) is set or the alarm-callback 
 /                  routine is called.
 / Particularities: The value of <increment> must be unequal to 0.
 /                  If the relative value <increment> is very small, 
 /                  the alarm may expire, and the task may become ready or 
 /                  the alarm-callback may be called before the system 
 /                  service returns to the user.
 /                  If <cycle> is unequal zero, the alarm element is logged 
 /                  on again immediately after expiry with the relative 
 /                  value <cycle>.
 /                  The alarm <AlarmID> must not already be in use.
 /                  To change values of alarms already in use the alarm has 
 /                  to be cancelled first.
 /                  If the alarm is already in use, this call is
 /                  ignored and the error E_OS_STATE is returned.
 /                  Allowed on task level and in ISR, but not in hook 
 /                  routines.
 / Status:
 /  -Standard:      - No error, E_OK
 /                  - Alarm <AlarmID> is already in use, E_OS_STATE
 /  -Extended:      - Alarm <AlarmID> is invalid, E_OS_ID
 /                  - Value of <increment> outside of the admissible 
 /                    limits (lower or equal zero or bigger than 
 /                    maxallowedvalue), E_OS_VALUE
 /                  - Value of <cycle> unequal to 0 and outside of the 
 /                    admissible counter limits (less than mincycle 
 /                    or bigger than maxallowedvalue), E_OS_VALUE
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:       BCC1, BCC2, ECC1, ECC2, Events only ECC1, ECC2
 /  -General:       Task, Cat2-ISR, interrupts enabled
 /  -SC1/SC2 only:  StartupHook (compatibility to older OSEK-OS)
 /--------------------------------------------------------------------------*/

/* CovComment 4:  Function: osSetRelAlarm */
/* KB begin osekHWosSetRelAlarmHead (default) */
/* MISRA RULE 14.1 violated: (comment 1503) In SafeContext implementations all APIs 
 * are encapsulated in wrappers. This wrappers belong to static ASIL code and must exist, 
 * even if they are not used in a project. 
 */
osqFunc1 StatusType osqFunc2 osSetRelAlarm(AlarmType alarmID, TickType deltaTicks, TickType cycle) /* PRQA S 1503 */ /* TR:SOSK22:0199 */
{
   COVER(0x0064)
/* KB end osekHWosSetRelAlarmHead */
 {/* extra curly brace to allow coverage code above and variable declarations inside OS_SA_ENTRY below */
#if (osdNumberOfAlarms > 0)
   OS_SA_ENTRY()
   COVER(0x0065)
#if (osdNumberOfVarAlarms == 0)
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. */    
   osdDummyRead(deltaTicks)   /* PRQA S 3199 */
   osdDummyRead(cycle)        /* PRQA S 3199 */
#endif
   /* check call context */
   /* TR:SOSK22:0116 Start */
   /* TR:SASR30:0035 Start Context check in SetRelAlarm */
   /* TR:SASR30:0336 Start Context check in SetRelAlarm */
   if ((osdValidCtx_SetRelAlarm & osCurrentContext) == 0)
   {
      COVER(0x0066)
      osSaveSetRelAlarm_AlarmID(alarmID)
      #if (osdNumberOfVarAlarms > 0)
      COVER(0x0067)
      osSaveSetRelAlarm_increment(deltaTicks)
      osSaveSetRelAlarm_cycle(cycle)
      #endif
      osAPIError(E_OS_CALLEVEL, osdErrSACallContext);
      OS_SA_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   /* TR:SOSK22:0116 End */
   ELSEWITHCOVER(0x0068)

   /* check timer ID */
   if (alarmID >= osrNumberOfAlarms)
   {
#else
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. */    
      osdDummyRead(alarmID)    /* PRQA S 3199 */
      osdDummyRead(deltaTicks) /* PRQA S 3199 */
      osdDummyRead(cycle)      /* PRQA S 3199 */
#endif /*(osdNumberOfAlarms > 0)*/
      COVER(0x0069)
      osSaveSetRelAlarm_AlarmID(alarmID)
      #if (osdNumberOfVarAlarms > 0)
      COVER(0x006A)
      osSaveSetRelAlarm_increment(deltaTicks)
      osSaveSetRelAlarm_cycle(cycle)
      #endif
      osAPIError(E_OS_ID, osdErrSAWrongAlarmID); 
#if (osdNumberOfAlarms > 0)            /* 5011271_ISSUE_02 */
      OS_SA_EXIT()
#endif /*(osdNumberOfAlarms > 0)*/     /* 5011271_ISSUE_02 */
      return  E_OS_ID; /* TR:SOSK22:0327 */
#if (osdNumberOfAlarms > 0)
   }
   ELSEWITHCOVER(0x006B)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in SetRelAlarm */
   if (((oskApplAlarmAccess[alarmID] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x006C)
      osSaveSetRelAlarm_AlarmID(alarmID)
      #if (osdNumberOfVarAlarms > 0)
      COVER(0x006D)
      osSaveSetRelAlarm_increment(deltaTicks)
      osSaveSetRelAlarm_cycle(cycle)
      #endif
      osAPIError(E_OS_ACCESS, osdErrSANoAccess);
      OS_SA_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x006E)
   
/* TR:SOSK22:0323 Start */
#if (osdNumberOfVarAlarms > 0)
   COVER(0x006F)
#if (osdNumberOfVarAlarms < osdNumberOfAlarms)
   COVER(0x0070)
   if (alarmID < osrNumberOfVarAlarms)
   {
      COVER(0x0071)
#endif
      /* TR:SPMF09:0012 Start *//* TR:SASR30:0144 Start */
      /* delta ticks must not be zero according to AutosarOS */
      if (deltaTicks == 0)
      {
         COVER(0x0072)
         osSaveSetRelAlarm_AlarmID(alarmID)
          #if (osdNumberOfVarAlarms > 0)
          COVER(0x0073)
          osSaveSetRelAlarm_increment(deltaTicks)
          osSaveSetRelAlarm_cycle(cycle)
          #endif
         osAPIError(E_OS_VALUE, osdErrSAZeroIncrement);
         OS_SA_EXIT()
         return  E_OS_VALUE;
      }/* TR:SPMF09:0012 End *//* TR:SASR30:0144 End */
      ELSEWITHCOVER(0x0074)
      COVER(0x0075)
      /* check timer limits */
      #if osdUseCounterAPI
      if (cycle != 0)
      {
         if ((cycle > oskCounterMaxAllowedValue[oskAlarmCounterRef[alarmID]])
             || (cycle < oskCounterMinCycle[oskAlarmCounterRef[alarmID]]))
         {
            COVER(0x0076)
            osSaveSetRelAlarm_AlarmID(alarmID)
            #if (osdNumberOfVarAlarms > 0)
            COVER(0x0077)
            osSaveSetRelAlarm_increment(deltaTicks)
            osSaveSetRelAlarm_cycle(cycle)
            #endif
            osAPIError(E_OS_VALUE, osdErrSAWrongCycle);  
            OS_SA_EXIT()
            return E_OS_VALUE; /* TR:SOSK22:0329 */
         }
         ELSEWITHCOVER(0x0078)
      }
      ELSEWITHCOVER(0x0079)
      if (deltaTicks > oskCounterMaxAllowedValue[oskAlarmCounterRef[alarmID]]) 
      {
         COVER(0x007A)
         osSaveSetRelAlarm_AlarmID(alarmID)
         #if (osdNumberOfVarAlarms > 0)
         COVER(0x007B)
         osSaveSetRelAlarm_increment(deltaTicks)
         osSaveSetRelAlarm_cycle(cycle)
         #endif
         osAPIError(E_OS_VALUE, osdErrSAWrongDelta);
         OS_SA_EXIT()
         return E_OS_VALUE; /* TR:SOSK22:0328 */
      }
      ELSEWITHCOVER(0x007C)
      #else /* osdUseCounterAPI */
      COVER(0x007D)
      #if ((OSMAXALLOWEDVALUE < TICKTYPE_MAX) || (OSMINCYCLE > 1))
      if (cycle != 0)
      {
         if (
           #if (OSMAXALLOWEDVALUE < TICKTYPE_MAX) 
              cycle > oskAlarmDefinitions.maxallowedvalue
           #else
              0
           #endif
           #if ((OSMINCYCLE > 1) || (TICKTYPE_MIN !=0))
              || (cycle < oskAlarmDefinitions.mincycle)
           #endif
         )
         {
            COVER(0x007E)
            osSaveSetRelAlarm_AlarmID(alarmID)
            #if (osdNumberOfVarAlarms > 0)
            COVER(0x007F)
            osSaveSetRelAlarm_increment(deltaTicks)
            osSaveSetRelAlarm_cycle(cycle)
            #endif
            osAPIError(E_OS_VALUE, osdErrSAWrongCycle);  
            OS_SA_EXIT()
            return E_OS_VALUE; /* TR:SOSK22:0329 */
         }
         ELSEWITHCOVER(0x0080)
      }
      ELSEWITHCOVER(0x0081)
      #endif
      #if (OSMAXALLOWEDVALUE < TICKTYPE_MAX) 
      if (deltaTicks > oskAlarmDefinitions.maxallowedvalue)
      {
         COVER(0x0082)
         osSaveSetRelAlarm_AlarmID(alarmID)
         #if (osdNumberOfVarAlarms > 0)
         COVER(0x0083)
         osSaveSetRelAlarm_increment(deltaTicks)
         osSaveSetRelAlarm_cycle(cycle)
         #endif
         osAPIError(E_OS_VALUE, osdErrSAWrongDelta);
         OS_SA_EXIT()
         return E_OS_VALUE; /* TR:SOSK22:0328 */
      }
      ELSEWITHCOVER(0x0084)
      #endif
      #endif /* osdUseCounterAPI */

#if (osdNumberOfVarAlarms < osdNumberOfAlarms)
      COVER(0x0085)
   }
   else /*(alarmID < osrNumberOfVarAlarms)*/
   {
      COVER(0x0086)
#endif
#endif /* (osdNumberOfVarAlarms > 0) */

#if (osdNumberOfVarAlarms < osdNumberOfAlarms)
      /* TR:SPMF20:0016 Start *//* TR:SASR30:0144 Start */
      /* check for increment 0 for static alarm */
      /* cannot be checked in the generator as it must be allowed for SetAbsAlarm */
      if (oskStaticAlarmTime[alarmID] == 0)
      {
         COVER(0x0087)
         osSaveSetRelAlarm_AlarmID(alarmID)
         #if (osdNumberOfVarAlarms > 0)
         COVER(0x0088)
         osSaveSetRelAlarm_increment(deltaTicks)
         osSaveSetRelAlarm_cycle(cycle)
         #endif
         osAPIError(E_OS_VALUE, osdErrSAZeroIncrement);
         OS_SA_EXIT()
         return  E_OS_VALUE;
      } /* TR:SPMF20:0016 End *//* TR:SASR30:0144 End */
      ELSEWITHCOVER(0x0089)
#if (osdNumberOfVarAlarms > 0)
      COVER(0x008A)
   }
#endif /* (osdNumberOfVarAlarms > 0) */
#endif /*(osdNumberOfVarAlarms < osdNumberOfAlarms)*/


   /* TR:SASR30:0038 Start Check disabled interrupts in SetRelAlarm */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x008B)
      osSaveSetRelAlarm_AlarmID(alarmID)
      #if (osdNumberOfVarAlarms > 0)
      COVER(0x008C)
      osSaveSetRelAlarm_increment(deltaTicks)
      osSaveSetRelAlarm_cycle(cycle)
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrSAIntAPIDisabled);
      OS_SA_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   } /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x008D)

   COVER(0x008E)

   /* timer running? */
#if (osdUseHeap != 0)
   if (osAlarmActivated[alarmID] != 0)
   {
      COVER(0x008F)
#else
   if (osAlarmTime[alarmID] != 0)
   {
      COVER(0x0090)
#endif
      osSaveSetRelAlarm_AlarmID(alarmID)
      #if (osdNumberOfVarAlarms > 0)
      COVER(0x0091)
      osSaveSetRelAlarm_increment(deltaTicks)
      osSaveSetRelAlarm_cycle(cycle)
      #endif
      osAPIError(E_OS_STATE, osdErrSAAlreadyActive);
      OS_SA_EXIT()
      return E_OS_STATE; /* TR:SOSK22:0326 */
   }
   ELSEWITHCOVER(0x0092)

   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */

   /*start alarm*/
#if (osdNumberOfVarAlarms > 0)
   COVER(0x0093)
#if (osdNumberOfVarAlarms < osdNumberOfAlarms)
   COVER(0x0094)
   if (alarmID < osrNumberOfVarAlarms)
   {
      COVER(0x0095)
#endif
      /*alarm time is variable*/
      osAlarmCycleTime[alarmID] = cycle;
#if (osdUseHeap != 0)
      COVER(0x0096)
      osAlarmTime[alarmID] = deltaTicks + osGetSystemCounter();
      osAlarmActivated[alarmID] = 1;
      osInsertMinHeapWithCheck(alarmID);
#else
      COVER(0x0097)
      osAlarmTime[alarmID] = deltaTicks;
#endif
#endif /* (osdNumberOfVarAlarms > 0) */

#if (osdNumberOfVarAlarms < osdNumberOfAlarms)
   COVER(0x0098)
#if (osdNumberOfVarAlarms > 0)
   COVER(0x0099)
   }
   else
#endif
   {
      COVER(0x009A)
      /* start timer */
#if (osdUseHeap != 0)
      COVER(0x009B)
      osAlarmTime[alarmID] = oskStaticAlarmTime[alarmID] + osGetSystemCounter(); /* TR:SPMF20:0017 */
      osAlarmActivated[alarmID] = 1;
      osInsertMinHeapWithCheck(alarmID);
#else
      COVER(0x009C)
      osAlarmTime[alarmID] = oskStaticAlarmTime[alarmID];  /* TR:SPMF20:0017 */
#endif
   }
#endif


   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_SA_EXIT()
   COVER(0x009D)
   return E_OK;  /* TR:SOSK22:0325 */
#endif /*(osdNumberOfAlarms > 0)*/
 }/* extra curly brace (see start of osSetRelAlarm) */
} /* END OF osSetRelAlarm */ /* TR:SOSK22:0109 End */ /* TR:SOSK22:0319 End */ /* TR:SOSK22:0323 End */



#define osdSetAlarmTimeCorrected( dest, src )                          \
{                                                                      \
   TickType actualTime = osGetSystemCounter();                         \
   if ((src) > (actualTime & ~(osdSystemCounterMask)))                 \
   {                                                                   \
      (dest) = (src) | ( actualTime & (TickType)osdSystemCounterMask); \
      COVER(0x009E)                                                          \
   }                                                                   \
   else                                                                \
   {                                                                   \
      (dest) = (src) | ((actualTime-(TickType)osdSystemCounterMask) & (TickType)osdSystemCounterMask);\
      COVER(0x009F)                                                          \
   }                                                                   \
}
/* TR:SOSK22:0110 Start */
/*-+--------------------------------------------------------------------------
 / SetAbsAlarm
 / ===========
 /
 / Syntax:          StatusType SetAbsAlarm ( AlarmType <AlarmID>, 
 /                                           TickType <start>,
 /                                           TickType <cycle> )
 / Parameter (In):  -AlarmID Reference to the alarm element
 /                  -start Absolute value in ticks
 /                  -cycle Cycle value in case of cyclic alarm. In case 
 /                   of single alarms, cycle has to be zero.
 / Parameter (Out): none
 / Description:     The system service occupies the alarm <AlarmID> element.
 /                  When <start> ticks are reached, the task assigned to 
 /                  the alarm <AlarmID> is activated or the assigned event
 /                  (only for extended tasks) is set or the alarm-callback 
 /                  routine is called.
 / Particularities: If the absolute value <start> is very close to the 
 /                  current counter value, the alarm may expire, and the 
 /                  task may become ready or the alarm-callback may be 
 /                  called before the system service returns to the user.
 /                  If the absolute value <start> was already reached 
 /                  before the system call, the alarm will only expire 
 /                  when the absolute value <start> is reached again,
 /                  i.e. after the next overrun of the counter.
 /                  If <cycle> is unequal zero, the alarm element is 
 /                  logged on again immediately after expiry with the 
 /                  relative value <cycle>.
 /                  The alarm <AlarmID> must not be already in use.
 /                  To change values of alarms already in use the alarm 
 /                  has to be cancelled first.
 /                  If the alarm is already in use, this call is ignored 
 /                  and the error E_OS_STATE is returned.
 /                  Allowed on task level and in ISR, but not in hook 
 /                  routines.
 / Status:
 /  -Standard:      - No error, E_OK
 /                  - Alarm <AlarmID> is already in use, E_OS_STATE
 /  -Extended:      - Alarm <AlarmID> is invalid, E_OS_ID
 /                  - Value of <start> outside of the admissible counter 
 /                    limit (less than zero or bigger than maxallowedvalue),
 /                    E_OS_VALUE
 /                  - Value of <cycle> unequal to 0 and outside of the 
 /                    admissible counter limits (less than mincycle or 
 /                    bigger than maxallowedvalue), E_OS_VALUE
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2, Events only ECC1, ECC2
 / Context:
 /  -General:       Task, Cat2-ISR, interrupts not disabled by the 
 /                  application
 /  -SC1/SC2 only:  StartupHook (compatibility to older OSEK-OS)
 /--------------------------------------------------------------------------*/

/* CovComment 4:  Function: osSetAbsAlarm */
/* KB begin osekHWosSetAbsAlarmHead (default) */
/* MISRA RULE 14.1 violated: (comment 1503) In SafeContext implementations all APIs 
 * are encapsulated in wrappers. This wrappers belong to static ASIL code and must exist, 
 * even if they are not used in a project. 
 */
osqFunc1 StatusType osqFunc2 osSetAbsAlarm(AlarmType alarmID, TickType start, TickType cycle) /* PRQA S 1503 */  /* TR:SOSK22:0200 */
{
   COVER(0x00A0)
/* KB end osekHWosSetAbsAlarmHead */
 {
/* TR:SOSK22:0330 Start */
/* extra curly brace to allow coverage code above and variable declarations inside OS_SL_ENTRY below */
#if (osdNumberOfAlarms > 0)
   OS_SL_ENTRY()
   COVER(0x00A1)
#if (osdNumberOfVarAlarms == 0)
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. */    
   osdDummyRead(start)  /* PRQA S 3199 */
   osdDummyRead(cycle)  /* PRQA S 3199 */
#endif
   /* check call context */
   /* TR:SOSK22:0116 Start */
   /* TR:SASR30:0035 Start Context check in SetAbsAlarm */
   /* TR:SASR30:0336 Start Context check in SetAbsAlarm */
   if ((osdValidCtx_SetAbsAlarm & osCurrentContext) == 0)
   {
      COVER(0x00A2)
      osSaveSetAbsAlarm_AlarmID(alarmID)
      #if (osdNumberOfVarAlarms > 0)
      COVER(0x00A3)
      osSaveSetAbsAlarm_start(start)
      osSaveSetAbsAlarm_cycle(cycle)
      #endif
      osAPIError(E_OS_CALLEVEL, osdErrSLCallContext);
      OS_SL_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   /* TR:SOSK22:0116 End */
   ELSEWITHCOVER(0x00A4)

   /* check timer ID */
   if (alarmID >= osrNumberOfAlarms)
   {
#else
      COVER(0x00A5)
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. */    
      osdDummyRead(alarmID) /* PRQA S 3199 */
      osdDummyRead(start)   /* PRQA S 3199 */
      osdDummyRead(cycle)   /* PRQA S 3199 */
#endif /*(osdNumberOfAlarms > 0)*/
      COVER(0x00A6)
      osSaveSetAbsAlarm_AlarmID(alarmID)
      #if (osdNumberOfVarAlarms > 0)
      COVER(0x00A7)
      osSaveSetAbsAlarm_start(start)
      osSaveSetAbsAlarm_cycle(cycle)
      #endif
      osAPIError(E_OS_ID, osdErrSLWrongAlarmID);
#if (osdNumberOfAlarms > 0)            /* 5011271_ISSUE_02 */
      OS_SL_EXIT()
#endif /*(osdNumberOfAlarms > 0)*/     /* 5011271_ISSUE_02 */
      return  E_OS_ID; /* TR:SOSK22:0335 */
#if (osdNumberOfAlarms > 0)
   }
   ELSEWITHCOVER(0x00A8)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in SetAbsAlarm */
   if (((oskApplAlarmAccess[alarmID] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x00A9)
      osSaveSetAbsAlarm_AlarmID(alarmID)
      #if (osdNumberOfVarAlarms > 0)
      COVER(0x00AA)
      osSaveSetAbsAlarm_start(start)
      osSaveSetAbsAlarm_cycle(cycle)
      #endif
      osAPIError(E_OS_ACCESS, osdErrSLNoAccess);
      OS_SL_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x00AB)
/* TR:SOSK22:0331 Start */
#if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x00AC)
#if (osdNumberOfVarAlarms > 0)
   COVER(0x00AD)
#if (osdNumberOfVarAlarms < osdNumberOfAlarms)
   COVER(0x00AE)
   if (alarmID < osrNumberOfVarAlarms)
   {
      COVER(0x00AF)
#endif
      /* check timer limits */
      #if osdUseCounterAPI
      if (cycle != 0)
      {
         if ((cycle > oskCounterMaxAllowedValue[oskAlarmCounterRef[alarmID]])
             || (cycle < oskCounterMinCycle[oskAlarmCounterRef[alarmID]]))
         {
            COVER(0x00B0)
            osSaveSetAbsAlarm_AlarmID(alarmID)
            #if (osdNumberOfVarAlarms > 0)
            COVER(0x00B1)
            osSaveSetAbsAlarm_start(start)
            osSaveSetAbsAlarm_cycle(cycle)
            #endif
            osAPIError(E_OS_VALUE, osdErrSLWrongCycle);  
            OS_SA_EXIT()
            return E_OS_VALUE; /* TR:SOSK22:0337 */
         }
         ELSEWITHCOVER(0x00B2)
      }
      ELSEWITHCOVER(0x00B3)
      if (start > oskCounterMaxAllowedValue[oskAlarmCounterRef[alarmID]]) 
      {
         COVER(0x00B4)
         osSaveSetAbsAlarm_AlarmID(alarmID)
         #if (osdNumberOfVarAlarms > 0)
         COVER(0x00B5)
         osSaveSetAbsAlarm_start(start)
         osSaveSetAbsAlarm_cycle(cycle)
         #endif
         osAPIError(E_OS_VALUE, osdErrSLWrongStart);
         OS_SA_EXIT()
         return E_OS_VALUE; /* TR:SOSK22:0336 */
      }
      ELSEWITHCOVER(0x00B6)
      #else /* osdUseCounterAPI */
      COVER(0x00B7)
      #if ((OSMAXALLOWEDVALUE < TICKTYPE_MAX) || (OSMINCYCLE > 1))
      COVER(0x00B8)
      if (cycle != 0)
      {
         if (
           #if (OSMAXALLOWEDVALUE < TICKTYPE_MAX) 
              cycle > oskAlarmDefinitions.maxallowedvalue
           #else
              0
           #endif
           #if ((OSMINCYCLE > 1) || (TICKTYPE_MIN !=0))
              || (cycle < oskAlarmDefinitions.mincycle)
           #endif
            )
         {
            COVER(0x00B9)
            osSaveSetAbsAlarm_AlarmID(alarmID)
            #if (osdNumberOfVarAlarms > 0)
            COVER(0x00BA)
            osSaveSetAbsAlarm_start(start)
            osSaveSetAbsAlarm_cycle(cycle)
            #endif
            osAPIError(E_OS_VALUE, osdErrSLWrongCycle);  
            OS_SL_EXIT()
            return E_OS_VALUE; /* TR:SOSK22:0337 */
         }
         ELSEWITHCOVER(0x00BB)
      }
      ELSEWITHCOVER(0x00BC)
      #endif /* ((OSMAXALLOWEDVALUE < TICKTYPE_MAX) || (OSMINCYCLE > 1)) */
      #if (OSMAXALLOWEDVALUE < TICKTYPE_MAX)  
      if (start > oskAlarmDefinitions.maxallowedvalue)
      {
         COVER(0x00BD)
         osSaveSetAbsAlarm_AlarmID(alarmID)
         #if (osdNumberOfVarAlarms > 0)
         COVER(0x00BE)
         osSaveSetAbsAlarm_start(start)
         osSaveSetAbsAlarm_cycle(cycle)
         #endif
         osAPIError(E_OS_VALUE, osdErrSLWrongStart);
         OS_SL_EXIT()
         return E_OS_VALUE; /* TR:SOSK22:0336 */
      }
      ELSEWITHCOVER(0x00BF)
      #endif
      #endif /* osdUseCounterAPI */

#if (osdNumberOfVarAlarms < osdNumberOfAlarms)
   }
#endif
#endif /* (osdNumberOfVarAlarms > 0) */
   /* TR:SASR30:0038 Start Check disabled interrupts in SetAbsAlarm */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x00C0)
      osSaveSetAbsAlarm_AlarmID(alarmID)
      #if (osdNumberOfVarAlarms > 0)
      COVER(0x00C1)
      osSaveSetAbsAlarm_start(start)
      osSaveSetAbsAlarm_cycle(cycle)
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrSLIntAPIDisabled);
      OS_SL_EXIT()
      return E_OS_DISABLEDINT;  /* TR:SOSK22:0074 */
   }/* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x00C2)
#endif

   /* timer running? */
#if (osdUseHeap != 0)
   if (osAlarmActivated[alarmID] != 0)
   {
      COVER(0x00C3)
#else
   if (osAlarmTime[alarmID] != 0)
   {
      COVER(0x00C4)
#endif
      osSaveSetAbsAlarm_AlarmID(alarmID)
      #if (osdNumberOfVarAlarms > 0)
      COVER(0x00C5)
      osSaveSetAbsAlarm_start(start)
      osSaveSetAbsAlarm_cycle(cycle)
      #endif
      osAPIError(E_OS_STATE, osdErrSLAlreadyActive);
      OS_SL_EXIT()
      return E_OS_STATE; /* TR:SOSK22:0334 */
   }
   ELSEWITHCOVER(0x00C6)

   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */
   /* start alarm */
#if (osdNumberOfVarAlarms > 0)
   COVER(0x00C7)
#if (osdNumberOfVarAlarms < osdNumberOfAlarms)
   COVER(0x00C8)
   if (alarmID < osrNumberOfVarAlarms)
   {
      COVER(0x00C9)
#endif
      /*alarm time is variable*/
      osAlarmCycleTime[alarmID] = cycle;
#if (osdUseHeap != 0)
      if (start > (osdSystemCounterVar &~ (osdSystemCounterMask)))
      {
         COVER(0x00CA)
         start|= (osSystemCounter & (TickType)osdSystemCounterMask);
      }
      else
      {
         COVER(0x00CB)
         start|= (~osSystemCounter & (TickType)osdSystemCounterMask);
      }
      osAlarmTime[alarmID] = start;
      osAlarmActivated[alarmID] = 1;
      osInsertMinHeapWithCheck(alarmID);
      COVER(0x00CC)
#else /*!osdUseHeap*/
      /*all alarms are generated alarms (no heap)*/
   {
      TickType now;
      COVER(0x00CD)
      #if osdUseCounterAPI
      COVER(0x00CE)
      now = osCounter[oskAlarmCounterRef[alarmID]];
      #else
      COVER(0x00CF)
      now = osGetSystemCounter();
      #endif

      /*check, if start is after the next overflow*/
      if( start > now )
      {
         COVER(0x00D0)
         /*start is before next overflow*/
         osAlarmTime[alarmID] = start - now;
      }
      else
      {
         COVER(0x00D1)
         /*an overflow is necessary to reach start time*/
         #if osdUseCounterAPI
         COVER(0x00D2)
         osAlarmTime[alarmID] = (TickType) (start + 1 +
                                ( oskCounterMaxAllowedValue[oskAlarmCounterRef[alarmID]] -
                                  now
                                ));
         /* Has an overflow to zero occured? */
         if (osAlarmTime[alarmID] == 0)
         {
            /* YES: Take the maximum value */
            osAlarmTime[alarmID] = oskCounterMaxAllowedValue[oskAlarmCounterRef[alarmID]];
            COVER(0x00D3)
         }
         ELSEWITHCOVER(0x00D4)
         #else
         COVER(0x00D5)
         osAlarmTime[alarmID] = (TickType) (start + 1 + (((TickType)OSMAXALLOWEDVALUE) - now));
         /* Has an overflow to zero occured? */
         if (osAlarmTime[alarmID] == 0)
         {
            /* YES: Take the maximum value */
            osAlarmTime[alarmID] = (TickType)OSMAXALLOWEDVALUE;
            COVER(0x00D6)
         }
         ELSEWITHCOVER(0x00D7)
         #endif
      }
   }
   #endif
#endif /* (osdNumberOfVarAlarms > 0) */

#if (osdNumberOfVarAlarms < osdNumberOfAlarms)
   COVER(0x00D8)
#if (osdNumberOfVarAlarms > 0)
   COVER(0x00D9)
   }
   else
#endif
   {
      /*alarm time is statically defined in the OIL-file*/
#if (osdUseHeap != 0)
      if ( oskStaticAlarmTime[alarmID] > (osdSystemCounterVar &~ (osdSystemCounterMask)))
      {
         COVER(0x00DA)
         osAlarmTime[alarmID] = ( osSystemCounter & (TickType)osdSystemCounterMask) | oskStaticAlarmTime[alarmID];  /* TR:SPMF20:0018 */
      }
      else
      {
         COVER(0x00DB)
         osAlarmTime[alarmID] = (~osSystemCounter & (TickType)osdSystemCounterMask) | oskStaticAlarmTime[alarmID];  /* TR:SPMF20:0018 */
      }
      osAlarmActivated[alarmID] = 1;
      osInsertMinHeapWithCheck(alarmID);
#else /*!osdUseHeap*/
      /*all alarms are generated alarms (no heap)*/
   {
      TickType now;
      COVER(0x00DC)

      #if osdUseCounterAPI
      COVER(0x00DD)
      now = osCounter[oskAlarmCounterRef[alarmID]];
      #else
      COVER(0x00DE)
      now = osGetSystemCounter();
      #endif

      /*check, if alarm time is after the next overflow*/
      if( oskStaticAlarmTime[alarmID] > now )
      {
         COVER(0x00DF)
         /*alarm time is before next overflow*/
         osAlarmTime[alarmID] = oskStaticAlarmTime[alarmID] - now;  /* TR:SPMF20:0018 */
      }
      else
      {
         COVER(0x00E0)
         /*an overflow is necessary to reach alarm time*/
         #if osdUseCounterAPI
         COVER(0x00E1)
         osAlarmTime[alarmID] = oskStaticAlarmTime[alarmID] + 1 + 
                                ( oskCounterMaxAllowedValue[oskAlarmCounterRef[alarmID]] -
                                  now
                                );  /* TR:SPMF20:0018 */
         /* Has an overflow to zero occured? */
         if (osAlarmTime[alarmID] == 0)
         {
            /* YES: Take the maximum value */
            osAlarmTime[alarmID] = oskCounterMaxAllowedValue[oskAlarmCounterRef[alarmID]];
            COVER(0x00E2)
         }
         ELSEWITHCOVER(0x00E3)
         #else
         COVER(0x00E4)
            osAlarmTime[alarmID] = (TickType) oskStaticAlarmTime[alarmID] + 1 + 
                                   (((TickType)OSMAXALLOWEDVALUE) - now );  /* TR:SPMF20:0018 */
         /* Has an overflow to zero occured? */
         if (osAlarmTime[alarmID] == 0)
         {
            /* YES: Take the maximum value */
            osAlarmTime[alarmID] = (TickType) OSMAXALLOWEDVALUE;
            COVER(0x00E5)
         }
         ELSEWITHCOVER(0x00E6)
         #endif
      }
   }
   #endif
   }
#endif

   COVER(0x00E7)
   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_SL_EXIT()

   return E_OK;  /* TR:SOSK22:0333 */
#endif /*(osdNumberOfAlarms > 0)*/
 }/* extra curly brace (see start of osSetAbsAlarm) */
} /* END OF SetAbsAlarm */ /* TR:SOSK22:0110 End */ /* TR:SOSK22:0330 End */  /* TR:SOSK22:0331 End */

/* TR:SOSK22:0112 Start */
/*-+--------------------------------------------------------------------------
 / CancelAlarm
 / ===========
 /
 / Syntax:          StatusType CancelAlarm ( AlarmType <AlarmID> )
 / Parameter (In):  AlarmID Reference to an alarm
 / Parameter (Out): none
 / Description:     The system service cancels the alarm <AlarmID>.
 / Particularities: Allowed on task level and in ISR, but not in hook routines.
 / Status:
 /  -Standard:      - No error, E_OK
 /                  - Alarm <AlarmID> not in use, E_OS_NOFUNC
 /  -Extended:      - Alarm <AlarmID> is invalid, E_OS_ID
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, Cat2-ISR, interrupts not disabled by the application
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 not violated: (comment 1503) In not SafeContext projects this function 
 * may be switched off by the OS configuration parameter OS/APIOptimization/Manual/CancelAlarm
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and exist, even if they are not used in a project. 
 */
osqFunc1 StatusType osqFunc2 osCancelAlarm(AlarmType alarmID) /* PRQA S 1503 */ /* TR:SOSK22:0201 */
{
#if (osdNumberOfAlarms > 0)
   /* CovComment 4:  Function: osCancelAlarm */
   OS_CA_ENTRY()
   COVER(0x00E8)

   COVER(0x00E9)
   /* check call context */
   /* TR:SOSK22:0116 Start */
   /* TR:SASR30:0035 Start Context check in CancelAlarm */
   /* TR:SASR30:0336 Start Context check in CancelAlarm */
   if ((osdValidCtx_CancelAlarm & osCurrentContext) == 0)
   {
      COVER(0x00EA)
      osSaveCancelAlarm_AlarmID(alarmID)
      osAPIError(E_OS_CALLEVEL, osdErrCACallContext);
      OS_CA_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   /* TR:SOSK22:0116 End */
   ELSEWITHCOVER(0x00EB)

   /* check alarm ID */
#ifdef osHiResMiliSecAlarm
   if ((alarmID >= osrNumberOfAlarms) || (alarmID == osHiResMiliSecAlarm))
#else
   if (alarmID >= osrNumberOfAlarms)
#endif
   {
#else
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. */    
      osdDummyRead(alarmID) /* PRQA S 3199 */
#endif /*(osdNumberOfAlarms > 0)*/
      COVER(0x00EC)
      osSaveCancelAlarm_AlarmID(alarmID)
      osAPIError(E_OS_ID, osdErrCAWrongAlarmID);
#if (osdNumberOfAlarms > 0)            /* 5011271_ISSUE_02 */
      OS_CA_EXIT()
#endif /*(osdNumberOfAlarms > 0)*/     /* 5011271_ISSUE_02 */
      return E_OS_ID;  /* TR:SOSK22:0342 */
#if (osdNumberOfAlarms > 0)
   }
   ELSEWITHCOVER(0x00ED)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in CancelAlarm */
   if (((oskApplAlarmAccess[alarmID] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x00EE)
      osSaveCancelAlarm_AlarmID(alarmID)
      osAPIError(E_OS_ACCESS, osdErrCANoAccess);
      OS_CA_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x00EF)
   /* TR:SASR30:0038 Start Check disabled interrupts in CancelAlarm */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x00F0)
      osSaveCancelAlarm_AlarmID(alarmID)
      osAPIError(E_OS_DISABLEDINT, osdErrCAIntAPIDisabled);
      OS_CA_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }/* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x00F1)

#if (0 == osdUseHeap)
   /* if timer is inactive, return at once */
   if (osAlarmTime[alarmID] == 0)
   {
      COVER(0x00F2)
      osSaveCancelAlarm_AlarmID(alarmID)
      osAPIError(E_OS_NOFUNC, osdErrCANotActive);
      OS_CA_EXIT()
      return E_OS_NOFUNC;  /* TR:SOSK22:0341 */
   }
   ELSEWITHCOVER(0x00F3)

   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */
   osAlarmTime[alarmID] = 0;
#else /*osdUseHeap*/
   /* if timer is inactive, return at once */
   if (osAlarmActivated[alarmID] == 0)
   {
      COVER(0x00F4)
      osSaveCancelAlarm_AlarmID(alarmID)
      osAPIError(E_OS_NOFUNC, osdErrCANotActive);
      OS_CA_EXIT()
      return E_OS_NOFUNC;  /* TR:SOSK22:0341 */
   }
   ELSEWITHCOVER(0x00F5)

   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */

#if osdEnableAssertions
   if (osRemoveItemMinHeap(alarmID) != 0)
   {
      COVER(0x00F6)
      osAlarmActivated[alarmID] = 0; /* set alarm inactive */ /* TR:SOSK22:0338 */
   }
   else
   {
      COVER(0x00F7)
      /* KB begin osekHWosEnableTimProtInterrupt (default) */
      #if osdTimingProtectionUsed
      #error "Timing Protection not supported"
      #endif        
      /* KB end osekHWosEnableTimProtInterrupt */
      OS_CA_EXIT()
      osAbortSystem(osdErrCAAlarmInternal); /* TR:SPMF12:0008 */
      /* MISRA RULE 14.1 VIOLATION: The return statement below is unreacheable. Anyhow, 
       * it is necessary as most compilers would warn about a missing return statement 
       * otherwise. (3201) */
      return E_OS_NOFUNC; /* PRQA S 3201 */
   }
#else
   COVER(0x00F8)
   (void) osRemoveItemMinHeap(alarmID);
   osAlarmActivated[alarmID] = 0; /* set alarm inactive */ /* TR:SOSK22:0338 */
#endif

#endif /*osdUseHeap*/

   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_CA_EXIT()
   COVER(0x00F9)
   return E_OK; /* TR:SOSK22:0340 */
#endif /*(osdNumberOfAlarms > 0)*/

} /* END OF osCancelAlarm */ /* TR:SOSK22:0112 End */


/* KB begin osekEndOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
/* Reset to default section TR:SPMF49:0004 */
#pragma SET_CODE_SECTION()
#endif
/* KB end osekEndOfCModule */
/* END OF MODULE osekalrm.c */
