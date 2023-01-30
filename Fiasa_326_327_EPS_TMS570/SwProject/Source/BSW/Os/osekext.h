/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osekext.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.69
|
|  Description: external declarations (only for system internal use)
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
#ifndef _OSEKEXT_H      /* PRQA S 0883 EOF */ /* see MISRA comment above */
#define _OSEKEXT_H

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

/* KB begin osekStartOfHModule (default) */
/* KB end osekStartOfHModule */

/* KB begin osekHwDefinitions (overwritten) */

#define osdOSEKTaskLevel        0     /* has to be 0! */

/* KB end osekHwDefinitions */

#if defined USE_QUOTE_INCLUDES
 #include "osekqm.h"
#else
 #include <osekqm.h>
#endif


/* prototypes for OSEK internal functions */

#if (osdNumberOfAlarms > 0)
osqFunc1 void osqFunc2 osInitAlarms(void); /* TR:SPMF20:0014 */
#if ((osdSC== SC3) || (osdSC== SC4))
osqFunc1 void osqFunc2 osSysCancelAlarm(AlarmType alarmID);
#endif
#endif

#if (osdNumberOfScheduleTables > 0)
#if ((osdSC== SC3) || (osdSC== SC4))
osqFunc1 void osqFunc2 osSysStopScheduleTable(ScheduleTableType ScheduleTableID);
#endif
#endif

osqFunc1 osbool osqFunc2 osSchedulePrio(void);
#if (osdNumberOfAllTasks > 0)
osqFunc1 StatusType osqFunc2 osSysActivateTask( TaskType taskIndex); /* TR:SOSK22:0161 */
#endif

#if ((osdNumberOfAlarmSetEvent > 0) || (osdNumberOfSTSetEvent > 0))
osqFunc1 StatusType osqFunc2 osSysSetEvent(TaskType taskIndex, EventMaskType setMask);
#endif


#if osdStackCheck
/* KB begin osekHwosFillTaskStacksPrototype (default) */
/* KB end osekHwosFillTaskStacksPrototype */
#endif

osqFunc1 void osqFunc2 osWorkAlarms(void); /* TR:SPMF24:0007 */

#if (osdUseHeap)
#define osGetHeapTime(x) (osAlarmTime[x])
#define osGetFirstAlarm() (osAlarmHeap[0])
#define osGetActiveAlarmCount() (osAlarmHeapCount)
#endif


#if osdUseHeap
osqFunc1 osuint8 osqFunc2 osRemoveItemMinHeap(osHeapType aItem);
osqFunc1 void osqFunc2 osInsertMinHeap(osHeapType newItem);
#define osInsertMinHeapWithCheck(x) osInsertMinHeap(x)
#endif


#if ((osdSC == SC3) || (osdSC == SC4))
osqFunc1 void osqFunc2 osSysDisableISRSource(ISRType isrID);
#endif


#if (STATUS_LEVEL == EXTENDED_STATUS)
osqFunc1 void osqFunc2 osMissingTerminateError(void);
#endif

/* KB begin osekHwosUnhandledExceptionPrototype (default) */
osqFunc1 void osqFunc2 osUnhandledException(void);  /* TR:SPMF78:0002 */
/* KB end osekHwosUnhandledExceptionPrototype */


#if (osdNumberOfScheduleTables > 0)
osqFunc1 void osqFunc2 osInitScheduleTables(void);
osqFunc1 void osqFunc2 osWorkScheduleTables(CounterType CounterID);
#endif

#if osdTimingProtectionUsed
/* KB begin osTPTimerPrototypesExt (default) */
osqFunc1 void          osqFunc2 osInitTimingProtection (void)                        ;
osqFunc1 osProcessType osqFunc2 osTPExeSwitchTo        (osProcessType NewProcess)    ;
osqFunc1 void          osqFunc2 osTPExeSwitchBack      (osProcessType OldProcess)    ;
osqFunc1 void          osqFunc2 osTPSuspendTimerBlock  (void)                        ;
osqFunc1 void          osqFunc2 osTPResumeTimerBlock   (osProcessType Proc)          ;
osqFunc1 osbool        osqFunc2 osTPArrivalAllowed     (osProcessType ArrivedProcess);
osqFunc1 void          osqFunc2 osTPCleanListBlock     (osProcessType proc)          ;
osqFunc1 void          osqFunc2 osTPReloadExeBudget    (osProcessType proc)          ;
/* KB end osTPTimerPrototypesExt */
#endif /* osdTimingProtectionUsed */

/* KB begin osekHwPrototypes (overwritten) */
/* This macro defines the previously declared identifier and doesn't hide it. */
#if (osdCompiler==osdCompilerGHSARM)
  #define osDispatch() __asm("   swi #0x81"); /* PRQA S 3436 */
#else
  #define osDispatch() asm("   svc #0x81"); /* PRQA S 3436 */
#endif

/* do-while-macro, no error */
#define osSetLevel(lvl) \
do{                     \
   if((lvl)==1)         \
   {                    \
      osDisableLevel(); \
   }                    \
   else                 \
   {                    \
      osEnableLevel();  \
   }                    \
}while(0)   /* PRQA S 3459 */


#if (osdCompiler==osdCompilerGHSARM)

#if (defined(__THUMB) && (osdThumbMode != 1))
   #error "OSEK configured for ARM mode but compiled for THUMB mode"
#endif
#if (!defined(__THUMB) && (osdThumbMode == 1))
   #error "OSEK configured for THUMB mode but compiled for ARM mode"
#endif

#else

#if (defined(__16bis__) && (osdThumbMode != 1))
   #error "OSEK configured for ARM mode but compiled for THUMB mode"
#endif
#if (!defined(__16bis__) && (osdThumbMode == 1))
   #error "OSEK configured for THUMB mode but compiled for ARM mode"
#endif

osuint8 osGetHighPrioBit(osPrioFlagType uiReadyTasks);

#if (osdPreTaskHook == 1)
void osAsmToCPreTaskHook(void);
#endif
#if (osdPostTaskHook == 1)
void osAsmToCPostTaskHook(void);
#endif
#endif



#if (osdNumberOfInternalResources > 0)
void osOccupyInternalResource(void);
#endif

#if ((osdSC == SC3) || (osdSC == SC4))

extern osuint8 osProtectionTrap(void);

osqFunc1 void osqFunc2 osSysDisableInterruptSource (ISRType DisableISR);
void osCallApplHook(osuint32 errCode, osuint32 hookFct, osuint32 stackAddr);

#endif

/* KB end osekHwPrototypes */


/* OSEK internal defines */

/* Task flags */
#define osdTaskFlagScheduleAllowed  ((osTaskFlagType)0U)
#define osdTaskFlagNotUsingSchedule ((osTaskFlagType)2U)





/* alarm action */
#define osdAlarmActionSetEvent     ((osuint8)0U)
#define osdAlarmActionActivateTask ((osuint8)1U)
#define osdAlarmActionCallback     ((osuint8)2U)
#define osdAlarmActionIncrementCounter ((osuint8)3U)
/* KB begin osekHWosDiffTickTypeComparison (overwritten) */
typedef union
{
   TickType           unsignedNumber;
   osTickTimeDiffType signedNumber;
}TickTypeTmp;

/*
 * Macro osdIF_COUNTER( min, op, sub ):
 *
 * Do a comparison of counter values according to the operator "op".
 * A counter is considered to cyclically increase its n-bit value.
 * The counter overflows from the value (2^n)-1 to 0. Future values
 * are considered to be bigger than current values. Past values are 
 * smaller. A future value can be reached within 2^(n-1)-1 increments
 * from an current value, this is guaranteed externally.
 */
/* MISRA RULE 19.10 VIOLATION: (few lines below at PRQA-comment 3410) 
 * The second parameter (op) of this macro is meant to be a binary 
 * comparison operator, so it cannot be put into paranteses. This is 
 * no problem as putting in anything but a binary operator must lead 
 * to compile time errors which are easily found in the release tests 
 * of the OS. In case, the binary operator is not a comparison operator, 
 * the MISRA checker would have to find the problem with another message. 
 */
#define osdIF_COUNTER( min, op, sub ) \
{\
   volatile osTickTimeDiffType Tmp;\
   TickTypeTmp osHeapDiffCaster;\
   osHeapDiffCaster.unsignedNumber = (min) - (sub);\
   Tmp = osHeapDiffCaster.signedNumber;\
   if( Tmp op ((osTickTimeDiffType) 0))   /* PRQA S 3410 */ /* see MISRA comment above */

#define osdENDIF_COUNTER \
}
/* KB end osekHWosDiffTickTypeComparison */

#if (osdUseHeap != 0)
   #define osdSystemCounterMask    ((TickType)(0x80000000UL))

#define hasVarHeap  (osdNumberOfVarHeapAlarms > 0)
#define hasVarGen   (osdNumberOfVarAlarms > osdNumberOfVarHeapAlarms)
#define hasStatHeap (osdNumberOfStatHeapAlarms >0 )
#define hasStatGen  (osdNumberOfAlarms > (osdNumberOfStatHeapAlarms+osdNumberOfVarAlarms))

 #if    (!hasVarHeap) && (!hasStatHeap) && (osdNumberOfHiResSchedTabs == 0)  /* No heap alarms */
   #define isAlarmOnHeap(x) Always FALSE, so please handle your "if" different
   
 #elif  (!hasVarGen) && (!hasStatGen) /* No generated alarms */
   #define isAlarmOnHeap(x) Always TRUE, so please handle your "if" different
   
 #elif  (hasVarHeap) && (!hasStatHeap) /* only VarHeap, GenAlarms irrelevant */
    #define isAlarmOnHeap(x)    ((x) < osdNumberOfVarHeapAlarms)
    
 #elif  (!hasVarGen) && (hasStatHeap)  /* no VarGen, StatGen irrelevant */
    #define isAlarmOnHeap(x)    ((x) < (osdNumberOfVarAlarms + osdNumberOfStatHeapAlarms))  
    
 #elif  (!hasVarHeap) && (hasStatHeap) && (hasVarGen) && (!hasStatGen) /* No VarHeap and no StatGen */
    #define isAlarmOnHeap(x)    ((x) >= osdNumberOfVarAlarms)
    
 #elif  (!hasVarHeap) && (hasStatHeap) && (hasVarGen) && (hasStatGen) /* No VarHeap */ 
    #define isAlarmOnHeap(x)  (  ((x) >= osdNumberOfVarAlarms) && ((x) < (osdNumberOfVarAlarms + osdNumberOfStatHeapAlarms)) ) 
    
 #elif  (hasVarHeap) && (hasStatHeap) && (hasVarGen) && (!hasStatGen) /* No StatGen */ 
    #define isAlarmOnHeap(x)  (  ((x) < osdNumberOfVarHeapAlarms) ||  ((x) >= osdNumberOfVarAlarms)  )
    
 #else /* all types of alarms exist */
   #define isAlarmOnHeap(x)  (  ((x) < osdNumberOfVarHeapAlarms) || ( ((x) >= osdNumberOfVarAlarms) && ((x) < (osdNumberOfVarAlarms + osdNumberOfStatHeapAlarms))) )
 #endif
 
#endif /* end of if(osdUseHeap != 0) */

/* KB begin osekAssignStack (default) */
/* stack grows from high to lower addresses; decrement before push */
#define osAssignStack(stack)    ((osStackDataType*)((&(stack)[0])+(sizeof(stack)/sizeof((stack)[0])))) 
/* KB end osekAssignStack */
/* KB begin osekBottomofStack (default) */
#define osBottomOfStack(stack)  ((osStackDataType*)(stack))
/* KB end osekBottomofStack */


/* KB begin osekHWVariableSectionStartHeader (default) */
/* KB end osekHWVariableSectionStartHeader */

/****************************************************************************/
/* schedule table synchronization */
#define osdSTSyncNon           ((osuint8)0U)
#define osdSTSyncImplicit      ((osuint8)1U) /* "Implicit" and "Non" need to be distinguished in StartScheduleTableRel */
#define osdSTSyncExplicit      ((osuint8)2U)


#if osdUseHeap
osqRAM0 extern osqRAM1 osqRAM2 osAlarmIndexType osqRAM3 osAlarmHeapCount;    /* Number of heap elements */
#endif

/* KB begin osekGlobalOccCounterDecl (default) */
#if ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0)
osqRAM0 extern osqRAM1 osqRAM2 osResCounterType osqRAM3 osResGlobalOccupationCounter;
#endif /* ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) */
/* KB end osekGlobalOccCounterDecl */

/* KB begin osekHwExternDeclLockDispatcher (default) */
/* KB end osekHwExternDeclLockDispatcher */

/* KB begin osekHwExternSavedIntLevelVariables (overwritten) */
/* KB end osekHwExternSavedIntLevelVariables */

extern osqBOOL1 osqBOOL2 osbool osqBOOL3 osErrorFlag;


/* KB begin osekHwExternalDeclarations (overwritten) */
/* KB end osekHwExternalDeclarations */


#if (osdNumberOfScheduleTables>0)
typedef osuint8 osSTReactionType;
#define osdSTReact_Continue     ((osSTReactionType)0U)
#define osdSTReact_FinalDelay   ((osSTReactionType)1U)
#define osdSTReact_InitialDelay ((osSTReactionType)2U)
#define osdSTReact_Repeat       ((osSTReactionType)3U)
#define osdSTReact_Stop         ((osSTReactionType)4U)


osqFunc1 osSTReactionType osqFunc2 osSTWorkActions(GlobalTimeTickType* diff, 
                                                   osSTIndexType CurrentEP   );
#if (osdScheduleTableSyncUsed != 0)
osqFunc1 TickType osqFunc2 osSTDoSyncStep(ScheduleTableType currentST, 
                                          TickType RelOffs, 
                                          TickType MaxRetard, 
                                          TickType MaxAdvance          );
osqFunc1 void osqFunc2 osSTCalculateSyncState(ScheduleTableType currentST);
#endif

#endif /*if (osdNumberOfScheduleTables>0)*/




/* KB begin osekHWVariableSectionEndHeader (overwritten) */
/* KB end osekHWVariableSectionEndHeader */

/* KB begin osekEndOfHModule (overwritten) */
/* KB end osekEndOfHModule */

/*lint -restore re-enable messages*/

#endif /* _OSEKEXT_H, double include preventer */

/* END OF HEADER osekext.h */
