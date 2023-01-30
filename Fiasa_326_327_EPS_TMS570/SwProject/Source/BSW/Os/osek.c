/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osek.c
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=2.25
|
|  Description: osek startup, scheduler and dispatcher
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

/* CovComment 0:  file: osek.c */

/* KB begin osekHWStartupAdditional (default) */
/* KB end osekHWStartupAdditional */

/* KB begin osekHWOsekAdditionalInclude (default) */
/* KB end osekHWOsekAdditionalInclude */

/* KB begin osekStartOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_CODE_SECTION(".oscode") /* TR:SPMF49:0001 */ /* TR:SPMF49:0002 */
#endif
/* KB end osekStartOfCModule */

/* KB begin osekHWVariableSectionStart (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_DATA_SECTION(".osdata") /* TR:SPMF49:0001 */ /* TR:SPMF49:0002 */
#endif
/* KB end osekHWVariableSectionStart */

/* control variables */

/* MISRA RULE 8.10 not violated: (4 times) (comment 1504) See below at rule 8.7. */
/* MISRA RULE 8.7 not violated: (4 times) (comment 1514) The variables below are all accessed by 
 * several modules in C and/or assembly language. The MISRA checker sees only the accesses from C language, 
 * which leeds to some messages. For the variables osActiveTaskPrio, osHighReadyTaskPrio, 
 * osHighReadyTaskIndex and osStartDispatcher, the MISRA checker might see only accesses from within the 
 * function StartOSc, dependent on the implementation and configuration. So rules 8.10 and/or 8.7 might seem
 * violated for this variables. The variables osaActiveTaskIndex, osaIntNestingDepth and osaIntSaveDisableCounter
 * are accessed by several functions in this file, so the MISRA checker might see a violation of rule 8.10 only.
 */
osqRAM0 osqRAM1 osqRAM2  osPrioType osqRAM3 osActiveTaskPrio ;    /* Priority of running task */                     /* PRQA S 1504 */ /* PRQA S 1514 */
osqRAM0 osqRAM1 osqRAM2  osPrioType osqRAM3 osHighReadyTaskPrio;  /* Priority of ready task with highest priority */ /* PRQA S 1504 */ /* PRQA S 1514 */
osqRAM0 osqRAM1 osqRAM2  TaskType   osqRAM3 osHighReadyTaskIndex; /* ready task with highest priority */             /* PRQA S 1504 */ /* PRQA S 1514 */
osqBOOL1 volatile osqBOOL2 osbool   osqBOOL3 osStartDispatcher;   /* variable to request a task switch */            /* PRQA S 1504 */ /* PRQA S 1514 */

#if (osdTimingProtectionUsed)
/* MISRA RULE 8.10 VIOLATION: On some platforms, this variable could also be static. Catching all cases would 
   make the code too complex and error prone */
osqRAM0 osqRAM1 osqRAM2 osuint8 osqRAM3 osIntSaveDisableHighLevelCounter; /* PRQA S 1504 */
#endif


#if ((osdSC== SC3) || (osdSC== SC4))

osqRAM0 osqRAM1 osqRAM2 osuint16 osqRAM3 osCurrentContext;    

osqRAM0 osqRAM1 osqRAM2 osuint8 osqRAM3  osInSystemFct;

#endif /*((osdSC== SC3) || (osdSC== SC4))*/


#if osdStackCheck
/* MISRA RULE 8.7 not violated: (1514) See below at the rule 8.10 comment. */
/* MISRA RULE 8.10 not violated: (1504) The variable osLastActiveTaskIndex is accessed by 
 * several modules. On some platforms the analysis tool sees accesses by only one 
 * function (rule 8.7) or one module (rule 8.10) in C language but misses accesses from 
 * assembly language.
 */
osqRAM0 osqRAM1 osqRAM2 TaskType   osqRAM3 osLastActiveTaskIndex;    /* PRQA S 1514 */ /* PRQA S 1504*/
#endif


#if (STATUS_LEVEL == EXTENDED_STATUS)

#ifndef osdSuppressFilenames 
/* variables for error handling */
osqRAM1 osqRAM2 osLineNumberType osqRAM3 osActiveTaskLineNumber;

/* MISRA RULE 6.3 VIOLATION: The variable osActiveTaskModule is used to store the name of the 
 * file where the last OS-API-service has been called. This is performed by usage of the 
 * __FILE__ macro. Unfortunately some compilers warn if the type is not a character pointer. 
 * Usage of char* is save here as no computation on the value is intended. 
 */
osqRAM0 osqPROM1 const osqPROM2 char osqPROM3 * osqRAM1 osqRAM2 osqRAM3 osActiveTaskModule;   /* PRQA S 5013 */
#endif
#endif

#if ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0)
osqRAM0 osqRAM1 osqRAM2 osResCounterType osqRAM3 osResGlobalOccupationCounter;
#endif

#if osdSystemCounterNeeded
#if (osdUseCounterAPI==0)
osqRAM0 osqRAM1 volatile osqRAM2 TickType osqRAM3 osSystemCounter; /* TR:SOSK22:0100 */
#endif
#endif

/* KB begin osekHwDeclLockDispatcher (default) */
osqRAM0 osqRAM1 volatile osqRAM2 osDispatcherLockType osqRAM3 osLockDispatcher;
/* KB end osekHwDeclLockDispatcher */

/* KB begin osekHwSavedIntLevelVariables (default) */
/* MISRA RULE 8.7 VIOLATION: (2 times) See justification for Rule 8.10 below. */
/* MISRA RULE 8.10 VIOLATION: (2 times) The variables osSavedIntLevel and osSavedIntLevelNested are accessed by
 * several modules in many configurations. Declaring this variable static in the other cases would increase code
 * complexity too much.
 */
osqRAM0 osqRAM1 osqRAM2 osIntLevelType osqRAM3 osSavedIntLevel;        /* PRQA S 1504 */ /* PRQA S 1514 */

#if (osdTimingProtectionUsed)
osqRAM0 osqRAM1 osqRAM2 osIntLevelType osqRAM3 osSavedIntHighLevel;
/* MISRA RULE 8.7 VIOLATION: See justification for Rule 8.10 below. */
/* MISRA RULE 8.10 VIOLATION: The variable osSavedIntHighLevelNested is accessed by
 * several modules in many configurations. Declaring this variable static in the other cases would increase code
 * complexity too much.
 */
osqRAM0 osqRAM1 osqRAM2 osIntLevelType osqRAM3 osSavedIntHighLevelNested;  /* PRQA S 1504 */ /* PRQA S 1514 */
#endif
/* KB end osekHwSavedIntLevelVariables */

StatusType osStatusTypeReturn;

osqBOOL1 osqBOOL2 osbool osqBOOL3 osErrorFlag;

#if osdUseHeap
osqRAM0 osqRAM1 osqRAM2 osAlarmIndexType osqRAM3 osAlarmHeapCount;    /* Number of heap elements */
#endif

osqRAM0 osqRAM1 volatile osqRAM2 osuint8 osqRAM3 osORTICurrentServiceId;

osqRAM0 osqRAM1 osqRAM2 osuint8 osqRAM3 osActiveAppMode; /* TR:SOSK22:0067 */

#if (osdParameterAccessMacros && osdErrorHook)
osqRAM0 osqRAM1 osqRAM2 osAPIParam1Type osqRAM3 osAPIParam1;
osqRAM0 osqRAM1 osqRAM2 osAPIParam2Type osqRAM3 osAPIParam2;
osqRAM0 osqRAM1 osqRAM2 osAPIParam3Type osqRAM3 osAPIParam3;
#if (osdTimingProtectionUsed != 0)
osqRAM0 osqPRAM1 osTPTimeType osqPRAM2 osqPRAM3 * osqRAM1 osqRAM2 osqRAM3 osAPIParam4;
#endif
#endif

#if (osdErrorHook!=0)
/* KB begin osekGlobalErrorVariables (overwritten) */
osqRAM1 osqRAM2 osuint16 osqRAM3 osLastError;
#if (osdORTIDebug || defined(osdGHSDebugSupport))
osqRAM1 osqRAM2 StatusType osqRAM3 osLastErrorCode;
#endif
/* KB end osekGlobalErrorVariables */
#endif

/* KB begin dummyVariables (default) */
/* KB end dummyVariables */

/* KB begin osekHWVariableDefinition (overwritten) */
/* KB end osekHWVariableDefinition */

/* KB begin osekHWVariableSectionEnd (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_DATA_SECTION()
#endif
/* KB end osekHWVariableSectionEnd */

/* KB begin osekConstSectionCodeStart (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_DATA_SECTION(".osconst") /* TR:SPMF49:0001 */ /* TR:SPMF49:0002 */
#endif
/* KB end osekConstSectionCodeStart */

/* TR:SPMF29:0002 Start */
/* MISRA RULE 8.7 VIOLATION: This constant is to be included into the binary to identify the configuration. 
 * It is not used by internal code, instead it is meant for usage by external tools. So it exists without a reference. 
 */
osqROM0 osqROM1 const osqROM2 osVersionVariantCodingType osqROM3 oskVersionVariant = /* PRQA S 1514 */
{
   0xAF, /* magic number */
   0xFE,
   0xDE,
   0xAD,
   (osuint8)osdVrmMajRelNumRef, /* version of operating system, Major, defined in vrm.h */
   (osuint8)osdVrmMinRelNumRef, /* version of operating system, Minor */

   (osuint8)osdVrmGenMajRelNumRef, /* version of code generator */
   (osuint8)osdVrmGenMinRelNumRef,

   /* variant used (part 1) */
   /* Bit 0..1:   Conformance Class */
   /* Bit 2:      Status level */
   /* Bit 3..4:   Scheduling policy */
   /* Bit 5:      Stackcheck */
   /* Bit 6:      API errors with file names */
   /* Bit 7:      EnableInternalAssertions */

   (osuint8)(((osdVariantCC)                    ) |
             ((osdVariantStatus)            << 2) |
             ((osdVariantSchedule)          << 3) |
             ((osdVariantStackcheck)        << 5) |
             ((osdVariantModulnamesEnabled) << 6) |
             ((osdVariantAssertionsEnabled) << 7)), /* TR:SPMF12:0005 */

   /* variant used (part 2) */
   /* Bit 0..1:   Scalability Class */
   /* Bit 2:      Schedule table(s) used (Not used in library version) */
   /* Bit 3:      High resolution schedule table(s) used (Not used in library version) */
   /* Bit 4:      Schedule table synchronization used*/
   /* Bit 5:      timing protection used */
   /* Bit 6:      Not yet used, always zero */
   /* Bit 7:      Not yet used, always zero */
   (osuint8)(((osdVariantSC)                    ) |
             ((osdVariantFeaturesUsed_ST)   << 2) |
             ((osdVariantFeaturesUsed_HRST) << 3) |
             ((osdVariantFeaturesUsed_Sync) << 4) |
             ((osdVariantFeaturesUsed_TP)   << 5)),
   
   /* ORTI variant                          */
   /* Bit 0..6: ORTI standard version       */
   /* Bit 7   : ORTI additional information */

   (osuint8)(((osdVariantORTIVersion)      ) |
             ((osdVariantORTIDebug)    << 7)), /* TR:SPMF14:0011 */ /* TR:SPMF29:0003 */

   /* KB begin osekStructSpecVersionVariant (overwritten) */
   (osuint16) ((osdVariantDerivative << 4) | (osdVariantORTI << 1) | (osdVariantThumbMode))
   /* KB end osekStructSpecVersionVariant */

}; /* TR:SPMF29:0002 End */
/* KB begin osekConstSectionCodeEnd (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_DATA_SECTION()
#endif
/* KB end osekConstSectionCodeEnd */

/* KB begin osekHWosGetHighPrioBit (overwritten) */
/* KB end osekHWosGetHighPrioBit */




#if osdStackCheck

/* KB begin osekHWosFillSystemStackSrc (overwritten) */
/* KB end osekHWosFillSystemStackSrc */
/* KB begin osekHWosInitSystemStackSrc (overwritten) */
/* KB end osekHWosInitSystemStackSrc */

 #if (osdStackModel != osdSingleStackOptimized)
  #if (osdNumberOfAllTasks > 0)
   #if osdStackUsageMeasurement
/* KB begin osekHwosFillTaskStacksSrc (overwritten) */
/* KB end osekHwosFillTaskStacksSrc */
   #else /* osdStackUsageMeasurement */
/* KB begin osekHWosInitTaskStacksSrc (overwritten) */
/* KB end osekHWosInitTaskStacksSrc */
   #endif /* osdStackUsageMeasurement */
  #endif /* (osdNumberOfAllTasks > 0) */
 #endif /* (osdStackModel != osdSingleStackOptimized) */

#endif /* osdStackCheck && (osdStackModel != osdSingleStackOptimizedCS) */

/*-+--------------------------------------------------------------------------
 / osSchedulePrio
 / Funktion:
 /   - calculate ready task with highest priority
 /   - set osHighReadyTaskPrio and osHighReadyTaskIndex for ready task with highest
 /     priority
 /   - osLockDispatcher must be unlocked (0)
 / Parameter:
 / Returnvalue: osdTRUE, if task with highest priority != active task or no task ready
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 VIOLATION: The function osSchedulePrio might be not called 
 *  in some configurations. Conditional compiling of the function 
 *  would increase the code complexity to unacceptable level (1503).
 */
osqFunc1 osbool osqFunc2 osSchedulePrio(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osSchedulePrio */
   /* calculate ready task with highest priority */
   osPrioType hiPriorTask;

#if osdRTSize > 1
   osqPRAM1 osqPRAM2 osPrioFlagType osqPRAM3 *ptr;
   osPrioFlagType uiTestPattern;
#endif

   COVER(0x0000)

#if osdRTSize > 1
   COVER(0x0001)
   ptr= osQReadyPrios;
   uiTestPattern= *ptr;
   hiPriorTask= 0;
   while (!uiTestPattern)
   {
      ptr++;
      if (ptr > &osQReadyPrios[osrRTSize-1])
      {  /* prepare for IDLE-Loop */
         COVER(0x0002)
         osHighReadyTaskPrio = osdNoActivePrio;
         osHighReadyTaskIndex = osdNoActiveTask;
         return osdTRUE;
      }
      ELSEWITHCOVER(0x0003)
      uiTestPattern = *ptr;
      hiPriorTask += osdPrioBitsPerWord;
   }
   COVER(0x0004)
   hiPriorTask += osGetHighPrioBit(uiTestPattern);
#else
   if (osQReadyPrios == 0)
   {  /* prepare for IDLE-Loop */
      COVER(0x0005)
      osHighReadyTaskPrio = osdNoActivePrio;
      osHighReadyTaskIndex = osdNoActiveTask;
      return osdTRUE;
   }
   ELSEWITHCOVER(0x0006)
   hiPriorTask= osGetHighPrioBit(osQReadyPrios);
#endif

#if ((CC == BCC2) || (CC == ECC2))
   COVER(0x0007)
   osHighReadyTaskIndex  = oskQActivationQueues[hiPriorTask][osQReadyTaskHead[hiPriorTask]];
#else
   COVER(0x0008)
   osHighReadyTaskIndex  = osQReadyTask[hiPriorTask];
#endif

   osHighReadyTaskPrio = hiPriorTask;

   /* KB begin osekHWosSchedulePrioReaction (default) */
      if (osHighReadyTaskIndex != osaActiveTaskIndex)
      {
         COVER(0x0009)
         return osdTRUE;
      }
      else
      {
         COVER(0x000A)
         return osdFALSE;
      }
   /* KB end osekHWosSchedulePrioReaction */
} /* END OF osSchedulePrio */


/*-+--------------------------------------------------------------------------
 / osInitTCBs
 / Funktion:
 /   - inits all tasks as SUSPENDED
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/

#if (osdNumberOfAllTasks>0)
static osqFunc1 void osqFunc2 osInitTCBs(void);
static osqFunc1 void osqFunc2 osInitTCBs(void)
{
   /* CovComment 4:  Function: osInitTCBs */
   osPrioType np;

#if ((CC==BCC2) || (CC==ECC2) || osdORTIDebug)
   osTaskIndexType nt;

   COVER(0x000B)
   for (nt=0; nt<osrNumberOfAllTasks; nt++)
   {
      COVER(0x000C)
      #if (CC==BCC2) || (CC==ECC2)
         COVER(0x000D)
         osTcbActivationCount[nt]= 0;
      #endif

      #if osdORTIDebug
      COVER(0x000E)
      osTcbActualPrio[nt] = oskTcbHomePrio[nt];
      osTcbORTIServiceId[nt] = osdORTINoService;
      #endif
   }
#endif /* ((CC==BCC2) || (CC==ECC2) || osdORTIDebug) */

#if (osdRTSize > 1)
   COVER(0x000F)
   for (np=0; np<osrRTSize; np++)
   {
      COVER(0x0010)
      osQReadyPrios[np] = 0;
   }
#else
   COVER(0x0011)
   osQReadyPrios = 0;
#endif

   /* all activation queues are empty */
   for (np= 0; np<osrNumberOfPriorities; np++)
   {
   #if (CC==BCC2) || (CC==ECC2)
      COVER(0x0012)
      osQReadyTaskHead[np]= osQReadyTaskTail[np]= 0;
   #else
      COVER(0x0013)
      osQReadyTask[np]= osdNoActiveTask;
   #endif
   }

   /* KB begin osekHWosInitTcbExtension (default) */
   /* KB end osekHWosInitTcbExtension */
} /* END OF osInitTCBs */

#endif

#if osdLib

/*-+--------------------------------------------------------------------------
 / osCheckLibraryVersionAndVariant
 / Funktion:
 /   - checks if version of library and the variant coding are the same
 /     as the user selected in the OIL configurator
 /   - if the variant differs, the system is shut down
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/
osqFunc1 void osqFunc2 osCheckLibraryVersionAndVariant(void)
{
   /* CovComment 4:  Function: osCheckLibraryVersionAndVariant */
   osqPROM1 osqPROM2 osuint8 osqPROM3 * ptr1;
   osqPROM1 osqPROM2 osuint8 osqPROM3 * ptr2;
   osuint8 n;

   COVER(0x0014)
   /* defined in tcb.c, generated */
   ptr1= (osqPROM1 osqPROM2 osuint8 osqPROM3 *) &oskLibVersionVariant; 
   /* defined in osek.c, always visible */
   ptr2= (osqPROM1 osqPROM2 osuint8 osqPROM3 * ) &oskVersionVariant;    
   
   for (n= 0; n < sizeof(osVersionVariantCodingType); n++)
   {
      if (*ptr1++ != *ptr2++)
      {
         COVER(0x0015)
         osAbortSystem(osdErrCLWrongLibrary);
      }
      ELSEWITHCOVER(0x0016)
   }
} /* END OF osCheckLibraryVersionAndVariant */

#endif


/* KB begin osekHWosStartOSasmSrc (overwritten) */
/* KB end osekHWosStartOSasmSrc */

 /* TR:SPMF05:0001 Start */
 /* TR:SOSK22:0133 Start */
/*-+--------------------------------------------------------------------------
 / StartOS 
 / =======
 / Syntax void StartOS ( AppModeType <Mode> )
 / Parameter (In):
 / Mode application mode
 / Parameter (Out): none
 / Description: The user can call this system service to start the operating
 / system in a specific mode, see chapter 5, Application modes.
 / Particularities: Only allowed outside of the operating system, therefore
 / implementation specific restrictions may apply. See also
 / chapter 11.3, System start-up, especially with respect to
 / systems where OSEK and OSEKtime coexist. This call does
 / not need to return.
 / Conformance: BCC1, BCC2, ECC1, ECC2
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 not violated: (command 1503) See comment for 8.10 */
/* MISRA RULE 8.10 VIOLATION: (command 1505) The function osStartOSc is general code 
 * and is called from within the implementation specific function osStartOSasm. 
 * That function might be written in assembler or C and be located in the same 
 * file as osStartOSc or another file, dependent on the implementation. Therfore 
 * MISRA checking tools might not see the call and state violation of rule 14.1 
 * wrongly or they see the call and state a violation of rule 8.10 correctly.
 * Anyhow, the function osStartOSc needs to have external linkage as some 
 * implementations have the calling function osStartOSasm in another file.
 */
osqFunc1 void osqFunc2 osStartOSc(void)     /* PRQA S 1503 *//* PRQA S 1505 */
{
   /* CovComment 4:  Function: osStartOSc */
   /* is called (from osStartOSasm) with interrupts disabled up to system level */
#if (osdNumberOfAllTasks > 0)
   osTaskIndexType nt;
#endif

#if (osdNumberOfAllResources > 0) 
#if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
#if (osdNumberOfCat2ISRs > 0)
   ISRType ni;
#endif
#endif
#endif

#if (STATUS_LEVEL == EXTENDED_STATUS) ||        \
    osdORTIDebug                      ||        \
    osdKillTaskIsrPossible            ||        \
    (osdSC== SC3)                     ||        \
    (osdSC== SC4)
#if (osdNumberOfAllResources > 0)
   osResourceIndexType nr;
#endif
#endif

   #if (osdNumberOfCounters > 0)
      #if osdUseCounterAPI
         osuint8 nc;
      #endif
   #endif

#ifdef osdEnableCoverage
   osuint16 i;

   /* during initialization of the coverage array no coverage is possible */
   /* initialize the coverage array */
   for(i=0; i<osdCoverageArraySize; i++)
   {
      osCoverage[i] = 0;
   }
#endif

   COVER(0x0017)

   /* initialise trace if in use */
#ifdef osdUseTrace
   COVER(0x0018)
   osInitTrace();
#endif

   OS_ST_ENTRY()
   OS_ST_START_CRITICAL()

   COVER(0x0019)

/* KB begin dummyVariablesInit (default) */
/* KB end dummyVariablesInit */

#if STATUS_LEVEL == EXTENDED_STATUS
   /* Error checking is done in the define-macro StartOS, of only OSDEFAULTAPPMODE exists */
   /* Parameter checking, Mode is a bit-mask with only just one bit set */
   if (((osActiveAppMode & ((AppModeType)(osActiveAppMode-((AppModeType)1)))) != 0)  ||   /* more than one bit set   */
       (osActiveAppMode == 0)                                         ||   /* zero                    */
       (osActiveAppMode > (1U << (osrNumberOfAppModes - 1)))             ) /* exceeding maximum value */
   {
      COVER(0x001A)
      #if osdErrorHook
      COVER(0x001B)
      osLastError = osdErrSTWrongAppMode; 
      osErrorHook(E_OS_SYS_ABORT);
      #endif

      #if (osdShutdownHook || (osdNumberOfApplications > 0))
      COVER(0x001C)
      osSysShutdownOS(E_OS_SYS_ABORT);
      #else
      COVER(0x001D)
      osSysShutdownOS();
      #endif
   }
   ELSEWITHCOVER(0x001E)
#endif

#if osdLib
   COVER(0x001F)
   osCheckLibraryVersionAndVariant();
#endif

#if (osdNumberOfAllTasks>0)
   COVER(0x0020)
   osInitTCBs();
#else
   COVER(0x0021)
   osQReadyPrios = 0;
#endif



#if (osdStackModel != osdSingleStackOptimized) && (osdStackModel != osdSingleStackOptimizedCS)
 #if osdStackCheck
   COVER(0x0022)
  #if (osdNumberOfAllTasks > 0)
   COVER(0x0023)
   #if osdStackUsageMeasurement
   COVER(0x0024)
   /* TR:SPMF08:0003 Start */
   /* TR:SPMF08:0005 Start */
   /* KB begin osekHWosFillTaskStacks (overwritten) */
   /* KB end osekHWosFillTaskStacks */
   /* TR:SPMF08:0003 End */
   /* TR:SPMF08:0005 End */
   #else
   COVER(0x0025)
   /* TR:SPMF07:0002 Start */
   /* TR:SPMF07:0004 Start */
   /* KB begin osekHWosInitTaskStacks (overwritten) */
   /* KB end osekHWosInitTaskStacks */
   /* TR:SPMF07:0002 End */
   /* TR:SPMF07:0004 End */
   #endif
  #endif
   osLastActiveTaskIndex = 0;
 #endif
#endif

   osActiveTaskPrio = osHighReadyTaskPrio = osdNoActivePrio; /* mark as invalid for a nested interrupt */
   osHighReadyTaskIndex = osdNoActiveTask;

#if ((osdSC == SC3) || (osdSC == SC4))
   COVER(0x0026)
   osInSystemFct = 0;
#endif

#if (osdErrorHook!=0)
   COVER(0x0027)
   osErrorFlag=osdFALSE;   
   /* KB begin osekInitGlobalError (overwritten) */
   #if (osdORTIDebug || defined(osdGHSDebugSupport))
   osLastErrorCode=0;
   #ifndef osdOSEK2_2
   osLastError=0;
   #endif
   #endif
   /* KB end osekInitGlobalError */
#endif

   osStartDispatcher = 0;
   osLockDispatcher = 1; /* lock dispatcher during StartOS */



#if STATUS_LEVEL == EXTENDED_STATUS
   COVER(0x0028)
/* TR:SPMF12:0006 Start */
#if osdEnableAssertions
   COVER(0x0029)
   /* check memory access */
   osSysErrAssert((osStartDispatcher==0), osdErrSTMemoryError)
   COVER(0x002A)
   osSysErrAssert((osLockDispatcher==1), osdErrSTMemoryError)
#endif
/* TR:SPMF12:0006 End */
 #if ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0)
   osResGlobalOccupationCounter = 0;
 #endif
#endif /* STATUS_LEVEL == EXTENDED_STATUS */

#if (osdNumberOfAllResources > 0)
   COVER(0x002B)
#if (STATUS_LEVEL == EXTENDED_STATUS) || osdORTIDebug
   COVER(0x002C)
   for (nr=0; nr<osrNumberOfAllResources; nr++)
   {
      COVER(0x002D)
         COVER(0x002E)
         osResOccupationCounter[nr] = 0;
         COVER(0x002F)
         osResActualTask[nr] = osdNoActiveTask;
   }

#endif /* (STATUS_LEVEL == EXTENDED_STATUS) || osdORTIDebug */
#endif /* (osdNumberOfAllResources > 0) */

#if (osdTimingProtectionUsed != 0)
   COVER(0x0030)
   osInitTimingProtection();
#endif

/* TR:SOSK22:0067 Start */   
#if (osdNumberOfAllTasks > 0)
   COVER(0x0031)
   /* activate all autostart tasks */
   for (nt= 0; nt < osrNumberOfAllTasks; nt++)
   {
      COVER(0x0032)
      osTcbTaskState[nt] = SUSPENDED; /* TR:SOSK22:0039 */

      #if STATUS_LEVEL == EXTENDED_STATUS
      COVER(0x0033)
      #if (osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0)
      COVER(0x0034)
      osTcbResourceCounter[nt]=0;
      #endif
      #endif
   /* TR:SOSK22:0134 Start */
   /* TR:SOSK22:0138 Start */
   /* TR:SOSK22:0040 Start */
      if ((oskTcbAutoStart[nt] & osActiveAppMode) != 0)
      {
         COVER(0x0035)
         (void) osSysActivateTask(nt); 
      }/* TR:SOSK22:0134 End */    /* TR:SOSK22:0138 End */    /* TR:SOSK22:0040 End */
      ELSEWITHCOVER(0x0036)
   } 
 /* TR:SOSK22:0067 End */
#endif

   /* TR:SOSK22:0101 Start */
   #if (osdNumberOfCounters > 0)
      COVER(0x0037)
      #if osdUseCounterAPI
         COVER(0x0038)
         for(nc = 0; nc < osrNumberOfCounters; nc++)
         {
            COVER(0x0039)
            osCounter[nc] = 0;
         }
      #else
         #if (osdSystemCounterNeeded)
            COVER(0x003A)
            osSystemCounter = 0;
         #endif   
      #endif   
	  /* TR:SOSK22:0101 End */
   #endif   
/* TR:SOSK22:0138 Start */
#if (osdNumberOfAlarms > 0)
   COVER(0x003B)
   osInitAlarms(); /* TR:SPMF20:0014 */
#endif
/* TR:SOSK22:0138 End */

#if (osdNumberOfScheduleTables > 0)
   COVER(0x003C)
   osInitScheduleTables();
#endif

   /* KB begin osekHWStartupSpecial (overwritten) */
   /* KB end osekHWStartupSpecial */


#if (osdNumberOfAllResources > 0)
   COVER(0x003D)
#if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
#if (osdNumberOfCat2ISRs > 0)
   COVER(0x003E)
   for (ni=0; ni<osdNumberOfCat2ISRs; ni++)
   {
      COVER(0x003F)
      osIcbLockedResource[ni] = osdNoResource;
   }
#endif /*osdNumberOfCat2ISRs*/
#if (osdNumberOfAllTasks > 0)
   COVER(0x0040)
   for (nt=0; nt<osdNumberOfAllTasks; nt++)
   {
      COVER(0x0041)
      osTcbLockedResource[nt] = osdNoResource;
   }
#endif /*osdNumberOfAllTasks*/

   for (nr=0; nr<osdNumberOfAllResources; nr++)
   {
      COVER(0x0042)
      osResNextLockedResource[nr] = osdNoResource;
   }

#endif /*(osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4)) */
#endif /* (osdNumberOfAllResources > 0) */

#if ((osdSC== SC3) || (osdSC== SC4))
   COVER(0x0043)
   /* KB begin osekHWInitProtection (overwritten) */
   /* KB end osekHWInitProtection */
#endif   /* ((osdSC== SC3) || (osdSC== SC4)) */

/* TR:SOSK22:0135 Start */
#if osdStartupHook
   COVER(0x0044)
   /* call hook-routine for system startup (initialization of drivers etc.) */
#if ((osdSC== SC3) || (osdSC== SC4))
   COVER(0x0045)
   osCurrentContext = osdCtxStartupHook;
#endif   

   OS_STHOOK_ENTRY()
   osInterStartupHook();
   OS_STHOOK_EXIT()
#endif
/* TR:SOSK22:0135 End */
#if ((osdSC== SC3) || (osdSC== SC4))
   COVER(0x0046)
   osCurrentContext = osdCtxTask;
#endif /*((osdSC== SC3) || (osdSC== SC4))*/
   /* TR:SOSK22:0137 Start */
   /* free dispatcher (after osSysActivateTask for AutoStart-Tasks and after StartupHook */
   osLockDispatcher = 0; 

   OS_ST_END_CRITICAL()
   OS_ST_EXIT()
   /* KB begin osekHWosEnableLevelInStartOS (overwritten) */
      osEnableLevel();
   /* KB end osekHWosEnableLevelInStartOS */

   OS_START_DISPATCH()

   osLockDispatcher = 1; /* TR:SOSK22:0004 */
   /* TR:SOSK22:0137 End */

} /* END OF osStartOSc */
/* TR:SPMF05:0001 End */
/* TR:SOSK22:0133 End */

/* TR:SOSK22:0139 Start */
/*-+--------------------------------------------------------------------------
 / ShutdownOS
 / ==========
 /
 / Syntax void ShutdownOS ( StatusType <Error> )
 / Parameter (In):
 / Error error occurred
 / Parameter (Out): none
 / Description: The user can call this system service to abort the overall
 / system (e.g. emergency off). The operating system also calls
 / this function internally, if it has reached an undefined internal
 / state and is no longer ready to run.
 / If a ShutdownHook is configured the hook routine
 / ShutdownHook is always called (with <Error> as argument)
 / before shutting down the operating system.
 / If ShutdownHook returns, further behaviour of ShutdownOS is
 / implementation specific.
 / In case of a system where OSEK OS and OSEKtime OS
 / coexist, ShutdownHook must return.
 / <Error> must be a valid error code supported by OSEK OS. In
 / case of a system where OSEK OS and OSEKtime OS coexist,
 / <Error> might also be a value accepted by OSEKtime OS. In
 / this case, if enabled by an OSEKtime configuration parameter,
 / OSEKtime OS will be shut down after OSEK OS shutdown.
 / Particularities: After this service the operating system is shut down.
 / Allowed at task level, ISR level, in ErrorHook and StartupHook,
 / and also called internally by the operating system.
 / If the operating system calls ShutdownOS it never uses E_OK
 / as the passed parameter value.
 / Conformance: BCC1, BCC2, ECC1, ECC2
 /--------------------------------------------------------------------------*/

/* QAC messages 3206,3199: The parameter 'Error' is intentionally used only in certain 
 * configurations. In other configurations, it depends on the plattform specific 
 * definition of osdDummyRead, which of the messages is stated. Both messages are 
 * not relevant for MISRA */
/* MISRA RULE 14.1 VIOLATION: osShutdownOS might be not called in some
 * configuration. Conditional compiling of the function would increase
 * the code complexity to unacceptable level (1503) */ 
/* TR:SOSK22:0029 Start */
/* TR:SASR30:0185 Start No error hook in ShutdownOS */
osqFunc1 void osqFunc2 osShutdownOS(StatusType Error) /* PRQA S 1503 */ /* PRQA S 3206 */ /* PRQA S 3199 */ /* TR:SOSK22:0140 */ /* TR:SOSK22:0204 */
{
/* TR:SOSK22:0354 Start */
   /* CovComment 4:  Function: osShutdownOS */
   OS_SD_ENTRY()
   COVER(0x0047)
   
/* TR:SASR30:0020 Start */
/* TR:SASR30:0323 Start */
#if ((osdSC == SC3) || (osdSC == SC4))
 #if (osdNumberOfApplications > 0)
   if ((osaActiveApplicationID != INVALID_OSAPPLICATION) && (oskApplIsTrusted[osaActiveApplicationID] == 0))
   {  /* ignore calls to ShutdownOS from non trusted applications */
      COVER(0x0048)
      return;
   }
   ELSEWITHCOVER(0x0049)
 #endif
#endif /*((osdSC == SC3) || (osdSC == SC4))*/
/* TR:SASR30:0323 End */
/* TR:SASR30:0020 End */
   
#if (osdShutdownHook || (osdNumberOfApplications > 0))
   COVER(0x004A)
   osSysShutdownOS(Error); /* TR:SOSK22:0140 */
#else
   COVER(0x004B)
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. (3199) */
   osdDummyRead(Error)   /* PRQA S 3199 */
   osSysShutdownOS(); /* TR:SOSK22:0140 */
#endif
/* TR:SOSK22:0354 End */
} 
/* TR:SASR30:0185 End */ 
/* TR:SOSK22:0029 End */
/* TR:SOSK22:0139 End */ 


/* KB begin BNCdispatcherSrc (default) */
/* KB end BNCdispatcherSrc */

#if osdStackCheck

#if osdStackUsageMeasurement

/* stack usage measurement is not availble in SingleStackOptimizedCS */
/* KB begin osekStackUsageSrc (overwritten) */
/*-+--------------------------------------------------------------------------
 / osGetSystemStackUsage
 / Funktion:
 /   - calculate maximum system stack usage
 / Parameter:
 / Returnvalue: calculated stack usage (in byte)
 /--------------------------------------------------------------------------*/

osStackUsageType osGetSystemStackUsage(void)
{
   osuint8 *stack;

   stack = (osuint8*)osSystemStack;
   while ((stack < (osuint8*)(((osuint32)osSystemStack) + ((osuint32)osdSystemStackSize )))
	   && (*stack == 0xAA))
   {
      stack++;
   }
   return (osStackUsageType)((osuint8*)(((osuint32)osSystemStack) + ((osuint32)osdSystemStackSize )) - stack);
} /* end of osGetSystemStackUsage */

/* KB end osekStackUsageSrc */
#endif /* osdStackUsageMeasurement */

#endif /* osdStackCheck */



#if (STATUS_LEVEL == EXTENDED_STATUS)
 #if (osdNumberOfAllTasks > 0)
/* KB begin osekHWosCheckInterruptsEnabledSrc (overwritten) */
/* KB end osekHWosCheckInterruptsEnabledSrc */
 #endif

 #if osdEnableAssertions
/* KB begin osekHWosCheckInterruptsDisabledSrc (overwritten) */
osqFunc1 osbool osqFunc2 osCheckInterruptsDisabled(void)
{
   if ((_get_CPSR() & 0x80) != 0)
   { 
      return 1;
   }
   else
   {
      return 0;
   }
}
/* KB end osekHWosCheckInterruptsDisabledSrc */
 #endif
#endif

/* KB begin osekHWosDispatcherSrc (overwritten) */
#if (osdNumberOfInternalResources > 0)
/* MISRA RULE 14.1 not violated: The function osOccupyInternalResource is called from 
 * assembly language. Typical MISRA checkers are not able to see the call.
 */
void osOccupyInternalResource(void)      /* PRQA S 1503 */
{
   /* KB begin osOccupyInternalResource (default) */
   /* TR:SOSK22:0098 Start */
   #if (osdNumberOfInternalResources > 0)
   if (oskResInternalCeilingPrioMask[osaActiveTaskIndex] != 0)
   {
      osPrioType IntResCeilingPrio= oskResInternalCeilingPrio[osaActiveTaskIndex];
   #if (CC==BCC2) || (CC==ECC2)
      COVER(0x004C)
      oskQActivationQueues[IntResCeilingPrio][0]= osaActiveTaskIndex;
   #else
      COVER(0x004D)
      osQReadyTask[IntResCeilingPrio]= osaActiveTaskIndex;
   #endif
   
   #if osdRTSize == 1
      COVER(0x004E)
      osQReadyPrios |= oskResInternalCeilingPrioMask[osaActiveTaskIndex];
   #else
      COVER(0x004F)
      osQReadyPrios[oskResInternalCeilingPrioOffset[osaActiveTaskIndex]] |= /*;*/
         oskResInternalCeilingPrioMask[osaActiveTaskIndex];
   #endif
   
      /* correct osHighReadyTaskPrio if required */
      if(IntResCeilingPrio<osHighReadyTaskPrio)
      {
         COVER(0x0050)
         osHighReadyTaskPrio = IntResCeilingPrio;
         osActiveTaskPrio  =   IntResCeilingPrio;
      }
      else
      {
         COVER(0x0051)
         osActiveTaskPrio  = osHighReadyTaskPrio;
      }
   
   }
   else
   {
      COVER(0x0052)
   #endif /* (osdNumberOfInternalResources > 0) */
   
      COVER(0x0053)
      osActiveTaskPrio  = osHighReadyTaskPrio;
   
   #if (osdNumberOfInternalResources > 0)
   }
   
   #if osdORTIDebug
   COVER(0x0054)
   osTcbActualPrio[osaActiveTaskIndex]=osActiveTaskPrio;
   #endif
   
   #endif /*(osdNumberOfInternalResources > 0)*/
   /* TR:SOSK22:0098 End */
   
   /* KB end osOccupyInternalResource */
}
#endif

#if (osdPreTaskHook == 1)
/* MISRA RULE 14.1 not violated: The function osAsmToCPreTaskHook is called from 
 * assembly language. Typical MISRA checkers are not able to see the call.
 */
void osAsmToCPreTaskHook(void)      /* PRQA S 1503 */
{
   osPreTaskHook();
}
#endif

#if (osdPostTaskHook == 1)
/* MISRA RULE 14.1 not violated: The function osAsmToCPostTaskHook is called from 
 * assembly language. Typical MISRA checkers are not able to see the call.
 */
void osAsmToCPostTaskHook(void)      /* PRQA S 1503 */
{
   osPostTaskHook();
}
#endif
/* KB end osekHWosDispatcherSrc */

/* KB begin osekHWAdditionalAPIFunctions (overwritten) */
/* KB end osekHWAdditionalAPIFunctions */

/* KB begin osekHWdelayTilEnableTookEffectSrc (default) */
/* KB end osekHWdelayTilEnableTookEffectSrc */



/* KB begin osekHWosProtectionTrapSrc (overwritten) */
/* KB end osekHWosProtectionTrapSrc */

   
   

/* KB begin osekEndOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
/* Reset to default section TR:SPMF49:0004 */
#pragma SET_CODE_SECTION()
#endif
/* KB end osekEndOfCModule */

/* END OF MODULE osek.c */

