/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osekerr.c
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.43
|
|  Description: functions for handling of errors
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

/* CovComment 0:  file: osekerr.c */

/* KB begin osekStartOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_CODE_SECTION(".oscode") /* TR:SPMF49:0001 */ /* TR:SPMF49:0002 */
#endif
/* KB end osekStartOfCModule */

/*-+--------------------------------------------------------------------------
 / osAbortSystem
 / Funktion:
 /              - called from system assertion osSysErrFail
 / Parameter:   uiError  error code
 / Returnvalue:
 / Context:     any, this function is meant for OS internal use
 /--------------------------------------------------------------------------*/
/* MISRA RULE 8.10 VIOLATION: Depending on the configuration, this function may be called only in this module.
 * Declaring this function static for some configurations would increase code complexity, too much.
 */
osqFunc1 void osqFunc2 osAbortSystem(osuint16 uiError) /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osAbortSystem */
   osDisableGlobal();

   #if osdErrorHook
   COVER(0x00FA)
   osLastError = uiError; 
   osErrorHook(E_OS_SYS_ABORT);
   #else
   COVER(0x00FB)
   /* KB begin dummyAssignAbortSystem (default) */
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. (3199) */
   osdDummyRead(uiError)   /* PRQA S 3199 */
   /* KB end dummyAssignAbortSystem */
   #endif

   #if (osdShutdownHook || (osdNumberOfApplications > 0))
   COVER(0x00FC)
   osSysShutdownOS(E_OS_SYS_ABORT); /* TR:SOSK22:0150 */
   #else
   COVER(0x00FD)
   osSysShutdownOS(); /* TR:SOSK22:0150 */
   #endif

} /* END OF osAbortSystem */

/*-+--------------------------------------------------------------------------
 / osAssertFailed
 / Funktion:
 /              - called if assertion failed, interrupts are disabled in 
 /                assertion
 / Parameter:    
 / Returnvalue:
 / Context:     any, this function is meant for OS internal use
 /--------------------------------------------------------------------------*/
#if (STATUS_LEVEL == EXTENDED_STATUS) && (osdEnableAssertions==1)
osqFunc1 void osqFunc2 osAssertFailed(void)
{
   /* CovComment 4:  Function: osAssertFailed */
   COVER(0x00FE)
   #if osdErrorHook
   COVER(0x00FF)
   osErrorHook(E_OS_SYS_ASSERTION);
   #endif
   COVER(0x0100)
   /* system is now shut down */

   #if (osdShutdownHook || (osdNumberOfApplications > 0))
   COVER(0x0101)
   osSysShutdownOS(E_OS_SYS_ASSERTION);
   #else
   COVER(0x0102)
   osSysShutdownOS();
   #endif

} /* END OF osAssertFailed */
#endif

/*-+--------------------------------------------------------------------------
 / osErrorHook
 / Funktion:
 /              - wrap Errorhook: disable interrupts and prevent recursive call
 / Parameter:   StatusType ErrorCode
 / Returnvalue:
 / Context:     any, this function is meant for OS internal use
 /--------------------------------------------------------------------------*/


osqFunc1 void osqFunc2 osErrorHook(StatusType ErrorCode) 
{  
   /* CovComment 4:  Function: osErrorHook */
   osuint16 savedContext;
   
/* KB begin osekHWosErrorHookAddVars (default) */
/* KB end osekHWosErrorHookAddVars */
   COVER(0x0103)
   OS_ERHOOK_ENTRY()

   /* KB begin osekAssignGlobalError (overwritten) */
   #if (osdORTIDebug || defined(osdGHSDebugSupport))
   osLastErrorCode=ErrorCode;
   #endif
   /* KB end osekAssignGlobalError */

   if (osErrorFlag == osdFALSE)
   {
      COVER(0x0104)
      osErrorFlag=osdTRUE; /* first entry in ErrorHook, lock ErrorHook */ /* TR:SOSK22:0128 */

      COVER(0x0105)
/* MISRA RULE 16.2 VIOLATION: The (indirectly) recursive call of function osErrorHook is prevented
 * by the variable osErrorFlag.
 */
      osSysErrAssert((osCheckInterruptsDisabled() != 0), osdErrEHInterruptsEnabled) /* PRQA S 1580, 1520 */

      /* KB begin osekHWosErrorHookStartActions (default) */
      /* KB end osekHWosErrorHookStartActions */

      savedContext = osCurrentContext;
      /* osCurrentContext might be sometimes used in the ErrorHook.
       * Therefore it must be initialized here, even if it is not always 
       * used before the next assignment. This is no MISRA error. (3198) */
      if (savedContext == osdCtxStartupHook)
      {
         COVER(0x0106)
         osCurrentContext = osdCtxErrorHook | osdCtxErrorHookFromStartupHook;   /* PRQA S 3198 */ /* TR:SOSK22:0120 */
      }
      else
      {
         COVER(0x0107)
         osCurrentContext = osdCtxErrorHook;   /* PRQA S 3198 */ /* TR:SOSK22:0120 */
      }

      osInterErrorHook(ErrorCode);

      osCurrentContext = savedContext;

      /* KB begin osekHWosErrorHookEndActions (default) */
      /* KB end osekHWosErrorHookEndActions */

      osErrorFlag=osdFALSE; /* unlock ErrorHook */
   }
   ELSEWITHCOVER(0x0108)

   COVER(0x0109)
   OS_ERHOOK_EXIT()
} /* END OF osErrorHook */
                  

/*-+--------------------------------------------------------------------------
 / osMissingTerminateError
 / Funktion:
 /              - called on return from task function without TerminateTask
 /              - shutdown system
 / Parameter:
 / Returnvalue:
 / Context:     any, this function is meant for OS internal use
 /--------------------------------------------------------------------------*/
#if (STATUS_LEVEL == EXTENDED_STATUS) 
/* MISRA RULE 14.1 not violated: The OS sets the return addresses of all tasks to the 
 * address of the function osMissingTerminateError, so it becomes active whenever 
 * a tasks returns without calling TerminateTask(). MISRA-checkers will typcally 
 * be unable to detect this.
 */
osqFunc1 void osqFunc2 osMissingTerminateError(void)      /* PRQA S 1503 */ 
{
   /* CovComment 4:  Function: osMissingTerminateError */

   osEnterSafeState(E_OS_MISSINGEND, osdErrMTMissingTerminateTask);
}
#endif

/*-+--------------------------------------------------------------------------
 / osUnhandledException
 / Funktion:
 /              - called if an unhandled exception occures
 / Parameter:
 / Returnvalue:
 / Context:     any, this function is meant for OS internal use
 /--------------------------------------------------------------------------*/
/* MISRA RULE 8.10 not violated: see justification for rule 14.1 below */
/* MISRA RULE 14.1 not violated: The function osUnhandledException is a general handler 
 * for all unconfigured interrupts. MISRA-checkers can typically not evaluate the 
 * link from the interrupt vector table to this function.
 */
/* TR:SPMF78:0002 Start */
osqFunc1 void osqFunc2 osUnhandledException(void)      /* PRQA S 1503 */ /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osUnhandledException */
   COVER(0x010A)
   osAbortSystem(osdErrUEUnhandledException); /* TR:SPMF78:0003 */ /* TR:SOSK22:0150 */

} /* END OF osUnhandledException */
/* TR:SPMF78:0002 End */

/* KB begin osekHWosISRUnhandledExeptionSrc (overwritten) */
/* KB end osekHWosISRUnhandledExeptionSrc */


/* KB begin osekEndOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
/* Reset to default section TR:SPMF49:0004 */
#pragma SET_CODE_SECTION()
#endif
/* KB end osekEndOfCModule */

/* END OF MODULE osekerr.c */
