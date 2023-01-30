/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: AUTOSAR OS 3.0
|    File Name: oseksctx.c/osekmpu.c
|
|  Module version: $vv$=1.03
|
|  Description: Safety related OSEK code
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2012 Vector Informatik GmbH               All rights reserved.
|****************************************************************************/

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

/* CovComment 0:  file: osekstcx.c */

/* Activate include preventers for tcb.h to avoid include of generated headers */
#define osdPreTCB  1
#define osdPostTCB 1
#define _PRE_TCB_H
#define OS_TCB_POST_INVARIANT
#define _POST_TCB_H


#if defined USE_QUOTE_INCLUDES
 #include "osektype.h"
 #include "osekqm.h"
 #include "oseksctx.h"
 #include "osekcov.h"
 #include "osekerr.h"
#else
 #include <osektype.h>
 #include <osekqm.h>
 #include <oseksctx.h>
 #include <osekcov.h>
 #include <osekerr.h>
#endif


/* KB begin osekStartOfSctxCModule (overwritten) */
#pragma SET_DATA_SECTION(".ossctxdata")
/* KB end osekStartOfSctxCModule */

/* Safe Context Variables */
/* MISRA RULE 8.10 not violated: (comment 1504) The variables below are accessed by 
 * several modules in C and/or assembly language. The MISRA checker sees only the accesses from C language. */
/* TR:SPMF89:0037 Start */
osqScRAM0        osqScRAM1          osqScRAM2 osuint8        osqScRAM3 osaIntNestingDepth            ;
osqScRAM0        osqScRAM1          osqScRAM2 TaskType       osqScRAM3 osaActiveTaskIndex            ; /* TR:SPMF89:0028 */
osqScRAM0        osqScRAM1 volatile osqScRAM2 ISRType        osqScRAM3 osaActiveISRID                ; /* PRQA S 1504 */
osqScRAM0        osqScRAM1 volatile osqScRAM2 osuint8        osqScRAM3 osaIntAPIStatus               ; /* TR:SOSK22:0254 */
osqScRAM0        osqScRAM1          osqScRAM2 osuint8        osqScRAM3 osaIntSaveDisableCounter      ;
osqScRAM0        osqScRAM1          osqScRAM2 osIntLevelType osqScRAM3 osaSavedIntLevelNested        ;
osqScRAM0        osqScRAM1          osqScRAM2 ApplicationType osqScRAM3 osaActiveApplicationID       ;
/* TR:SPMF89:0037 End */
/* KB begin osekHWSctxVariableDefinition (overwritten) */
/* TR:SPMF89:0019 Start */
/* TR:SPMF89:0037 Start */
osqScRAM0        osqScRAM1          osqScRAM2 osuint8        osqScRAM3 osaIntSaveDisableCounterGlobal;  
static osqScRAM0        osqScRAM1 volatile osqScRAM2 osuint8        osqScRAM3 osaSavedGlobalInt             ;
osqScRAM0        osqScRAM1 volatile osqScRAM2 osuint8        osqScRAM3 osaSavedIntGlobalNested       ;
/* TR:SPMF89:0019 End */
/* MISRA RULE 8.10 not violated: (comment 1504) The variable below is accessed by 
 * several modules in C and/or assembly language. The MISRA checker sees only the accesses from C language. */
osqScRAM0        osqScRAM1          osqScRAM2 osuint8        osqScRAM3 osaOnAPIStack                 ;  /* PRQA S 1504 */
/* TR:SPMF89:0037 End */
/* KB end osekHWSctxVariableDefinition */


/* Prototypes */
static osuint8 osCheckConfigBlock(void);

/* KB begin osekHWSctxPrototypes (overwritten) */
static inline void osSetMPUFromOSConfig(osuint8 regionNr, osuint8 areaID);
static inline void osSetMPUFromTaskConfig(TaskType taskID, osuint8 regionNr, osuint8 areaID);
static inline void osSetMPUFromISRConfig(ISRType isrID, osuint8 regionNr, osuint8 areaID);
static inline void osSetMPUFromApplConfig(ApplicationType applID, osuint8 regionNr, osuint8 areaID);

static inline void osSetMPUFromOSConfig(osuint8 regionNr, osuint8 areaID)
{
   /* CovComment 4:  Function: osSetMPUFromOSConfig */
   COVER(0x03F1)
   osSetupMPURegion(regionNr, 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressOSMPUSettings))->aulMPUSectionStartAddress[areaID], 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressOSMPUSettings))->aulMPUSectionSize[areaID], 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressOSMPUSettings))->aulMPUSectionAccess[areaID]);
}

static inline void osSetMPUFromTaskConfig(TaskType taskID, osuint8 regionNr, osuint8 areaID)
{
   /* CovComment 4:  Function: osSetMPUFromTaskConfig */
   COVER(0x03F2)
   osSetupMPURegion(regionNr, 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressTaskMPUSettings))[taskID].aulMPUSectionStartAddress[areaID], 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressTaskMPUSettings))[taskID].aulMPUSectionSize[areaID], 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressTaskMPUSettings))[taskID].aulMPUSectionAccess[areaID]);
}

static inline void osSetMPUFromISRConfig(ISRType isrID, osuint8 regionNr, osuint8 areaID)
{
   /* CovComment 4:  Function: osSetMPUFromISRConfig */
   COVER(0x03F3)
   osSetupMPURegion(regionNr, 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressISRMPUSettings))[isrID].aulMPUSectionStartAddress[areaID], 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressISRMPUSettings))[isrID].aulMPUSectionSize[areaID], 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressISRMPUSettings))[isrID].aulMPUSectionAccess[areaID]);
}

static inline void osSetMPUFromApplConfig(ApplicationType applID, osuint8 regionNr, osuint8 areaID)
{
   /* CovComment 4:  Function: osSetMPUFromApplConfig */
   COVER(0x03F4)
   osSetupMPURegion(regionNr, 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressApplMPUSettings))[applID].aulMPUSectionStartAddress[areaID], 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressApplMPUSettings))[applID].aulMPUSectionSize[areaID], 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressApplMPUSettings))[applID].aulMPUSectionAccess[areaID]);
}

static osqFunc1 void osqFunc2 osRestoreEnableLevelNested(void);
static osqFunc1 void osqFunc2 osSaveDisableLevelNested(void);

/* KB end osekHWSctxPrototypes */

static osuint16 crc16(const osuint8 * const ptr, osuint16 length);

/* MISRA RULE 14.1 not violated: (comment 1503) The function 'osInitSctx' is called in some implementations 
 * in assembler files. The MISRA checker sees only the accesses from C language. */  
osqFunc1 void osqFunc2 osInitSctx(void)  /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osInitSctx */

   osuint8 crcOK;
   COVER(0x03F5)
   /* KB begin osekHWInitSctxVars (overwritten) */
   osTaskIndexType nt;
   ISRType ni;
   /* KB end osekHWInitSctxVars */

   osaIntNestingDepth             = 0              ;
   osaActiveTaskIndex             = osdNoActiveTask;
   osaActiveISRID                 = INVALID_ISR    ; /* TR:SASR30:0109 */
   osaIntAPIStatus                = 0              ;
   osaIntSaveDisableCounter       = 0              ;
   osaActiveApplicationID         = INVALID_OSAPPLICATION; /* TR:SASR30:0107 */
   
   crcOK = osCheckConfigBlock();
   if (crcOK == 0)
   {
      COVER(0x03F6)
      osEnterSafeState(E_OS_SYS_ASSERTION, osdErrSTConfigCRCError);
   }
   ELSEWITHCOVER(0x03F7)
   
   /* KB begin osekHWInitSctxCode (overwritten) */
      COVER(0x03F8)
      osaIntSaveDisableCounterGlobal = 0;
   
      osaOnAPIStack = 0;
   
      for (nt= 0; nt < osConfigBlock.uiNumberOfTasks; nt++)
      {
         osaTcbValid[nt] = 0;
      }  
      for (nt= 0; nt < osConfigBlock.uiNumberOfTasks; nt++)
      {
         osaTcbNTFNestingDepth[nt] = 0;
      }   
      for (ni= 0; ni < osConfigBlock.uiNumberOfCat2ISRs; ni++)
      {
         osaIcbNTFNestingDepth[ni] = 0;
      }   
      /* First 1GB R/W for privileged mode and read-only for non-privileged modes (remaining part by background region for privileged mode) */
      osSetMPUFromOSConfig(osdMPURegionNr_DEFAULT, osdConstAreaID);  /* TR:SPMF89:01.0074 */
      osSetMPUFromOSConfig(osdMPURegionNr_CODE, osdCodeAreaID);      /* TR:SPMF89:01.0075 */
      osSetMPUFromOSConfig(osdMPURegionNr_SHAREDGLOBAL, osdAreaSharedGlobal);  /* TR:SPMF89:01.0081 */
   /* KB end osekHWInitSctxCode */  
}


/*----------------------------------------------------------------------------
 / osInitialize
 / Funktion:
 /   - Initialize all OS-variables, that are used by OS-API-functions which 
 /     might be used before StartOS() is called. This function should be used,
 /     if variables are not initialized by the startup-code, delivered with
 /     the compiler.
 / Parameter:   none
 / Returnvalue: none
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 not violated: (command 1503) The function osInitialize is general 
 * code, called from within the function osStartOSasm, which might be implemented 
 * in assembly language or in C language dependend on the implementation. Therefore the
 * MISRA checker might not see the call and wrongly state a violation of rule 14.1 */
/* MISRA RULE 8.10 VIOLATION: (command 1505) The function osInitialize is part of the 
 * described API of the OS. Therefore external linkage is required and it depends
 * on the application whether or not the function is ever called. */
/* TR:SASR30:0139 Start */
osqFunc1 void osqFunc2 osInitialize(void) /* PRQA S 1503 */ /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osInitialize */
   COVER(0x03F9)
   /* KB begin osekHWosInitialize (overwritten) */
   /* KB end osekHWosInitialize */
   osaIntSaveDisableCounter = 0;
   osaIntAPIStatus = 0;
   osaActiveApplicationID = INVALID_OSAPPLICATION; /* TR:SASR30:0107 */
} 
/* TR:SASR30:0139 End */

/* MISRA RULE 8.10 VIOLATION: The function osProtectionHookWrapper is a general implementation which is used 
 * identically on different plattforms. On some of them, it is called only in osek.c, on others it 
 * is called also from other files. Therefore it is made globally visible. The risk of potential 
 * name collisions is expected to be low.*/
/* TR:SASR30:0043 Start ProtectionHook reaction - osProtectionHookWrapper */ 
/* TR:SASR30:0388 Start ProtectionHook reaction - osProtectionHookWrapper */ 
/* TR:SASR30:0397 Start osProtectionHookWrapper */ 
osqFunc1 ProtectionReturnType osqFunc2 osProtectionHookWrapper(StatusType argErr)  /* PRQA S 1505 */
{
    /* CovComment 4:  Function: osProtectionHookWrapper */
    ProtectionReturnType proRet;
    osuint16 savedCtxt;

    COVER(0x03FA)
    savedCtxt = osCurrentContext;
    osCurrentContext = osdCtxProtectionHook;
    osInSystemFct++;
    osaIntAPIStatus = 0;
    proRet = ProtectionHook(argErr); /* TR:SASR30:0342 */
    osCurrentContext = savedCtxt;
    osInSystemFct--;

    /*
     * Check, if the desired action can be performed and change to another action
     * (in accordance with the standard) if necessary.
     */

    /* OS243: If the reaction is to kill the Task/Category 2 ISR ... */
    if (proRet == PRO_TERMINATETASKISR)
    {
       /* ... and no Task or ISR can be associated with the error, ... */
       if ((osaIntNestingDepth == 0) && (osaActiveTaskIndex == osdNoActiveTask))
       {
          /* ... the running OS-Application is killed.*/
          COVER(0x03FB)
          proRet = PRO_TERMINATEAPPL;
       }
       ELSEWITHCOVER(0x03FC)
    }
    ELSEWITHCOVER(0x03FD)

    /* OS244: If the reaction is to kill the faulty OS-Application ... */
    if ((proRet == PRO_TERMINATEAPPL) || (proRet == PRO_TERMINATEAPPL_RESTART))
    {
       COVER(0x03FE)
       /* ... and no OS-Application can be assigned, ... */
       if (osaActiveApplicationID == INVALID_OSAPPLICATION)
       {
          COVER(0x03FF)
          /* ... ShutdownOS()is called. */
          proRet = PRO_SHUTDOWN;
       }
       ELSEWITHCOVER(0x0400)
    }
    ELSEWITHCOVER(0x0401)

    if ((proRet == PRO_IGNORE) && (argErr != E_OS_PROTECTION_ARRIVAL))
    {
       /* PRO_IGNORE allowed only for protection error E_OS_PROTECTION_ARRIVAL */
       COVER(0x0402)
       proRet = PRO_SHUTDOWN;
    }
    ELSEWITHCOVER(0x0403)

    /* Has the protection error occurred in an application specific shutdown hook? */
    if (osCurrentContext == osdCtxShutdownHook)
    {
       /* Yes: Only shutdown possible */
       COVER(0x0404)
          proRet = PRO_SHUTDOWN;
       /* (prevent the system from running further, if the shutdown-decision is already taken) */       
    }
    ELSEWITHCOVER(0x0405)
    return proRet;
}
/* TR:SASR30:0397 End */ 
/* TR:SASR30:0388 End */ 
/* TR:SASR30:0043 End */ 

/* osSysShutdownOS is called internally by the OS, osShutdownOS is the user */
/* API and contains additional checks */

/* MISRA RULE 8.10 VIOLATION: (2 times) The function osSysShutdownOS is a general implementation which is used 
 * identically on different plattforms. On some of them, it is called only in osek.c, on others it 
 * is called also from other files. Therefore it is made globally visible. The risk of potential 
 * name collisions is expected to be low.*/
/* TR:SOSK22:0140 Start */
/* TR:SOSK22:0029 Start */
/* TR:SASR30:0185 Start No error hook in osSysShutdownOS */
osqFunc1 void osqFunc2 osSysShutdownOS(StatusType Error)                  /* PRQA S 1505 */ 
{
   /* CovComment 4:  Function: osSysShutdownOS */

   /* from now on, there is only trusted code executed, no return to non-trusted code */
   /* caller osShutdownOS is non-privileged, which requests the switch below */
   COVER(0x0406)
   /* KB begin osekHWSctxSwitchToPrivModeNoStore (overwritten) */
   (void)osSwitchToPrivMode();   
   /* KB end osekHWSctxSwitchToPrivModeNoStore */

   /* KB begin osekHWosDisableGlobal (overwritten) */
   osDisableGlobal();        /* disable all interrupts, no nesting */
   /* KB end osekHWosDisableGlobal */ /* disable all interrupts */

   /* Necessary to allow interrupt API functions in the shutdown hook 
    * together with timing protection */
   osaActiveTaskIndex = osdNoActiveTask;
   osaIntNestingDepth = 0;

   /* call shutdown hook routine */
   /* prevent recursive calls of application error hooks */
   if (osCurrentContext != osdCtxShutdownHook)
   {
      COVER(0x0407)
      osCurrentContext = osdCtxShutdownHook;
   
      osaActiveApplicationID = INVALID_OSAPPLICATION; /* TR:SASR30:0107 */
   }
   ELSEWITHCOVER(0x0408)

   COVER(0x0409)
   /* call system shutdown hook */
   osInterShutdownHook(Error);
   
   for(;;)  /* TR:SASR30:229 Start */
   {
      ; /* TR:SOSK22:0354 */
   }        /* TR:SASR30:229 End */
} /* END OF osSysShutdownOS */ 
/* TR:SASR30:0185 End */
/* TR:SOSK22:0029 End */ 
/* TR:SOSK22:0140 End */


/*-+--------------------------------------------------------------------------
 / osHandleProtectionErrors
 / ====================
 /
 / Syntax: void osHandleProtectionErrors(ProtectionReturnType proRet, 
 /                                       StatusType Fatalerror)
 / Parameter (In): proRet: Protection hook reaction to be executed. 
 /                 Fatalerror: Error code for handled error
 / Return value: none 
 / Description: 
 / Handles the error reaction for a protection error 
 / Scalability Classes: SC2, SC3, SC4
 /--------------------------------------------------------------------------*/

 /* MISRA RULE 8.10 VIOLATION: The function osHandleProtectionErrors is a general implementation which is used 
 * identically on different plattforms. On some of them, it is called only in osek.c, on others it 
 * is called also from other files. Therefore it is made globally visible. The risk of potential 
 * name collisions is expected to be low.*/
/* TR:SASR30:0043 Start ProtectionHook reaction - osHandleProtectionErrors */ 
/* TR:SASR30:0388 Start ProtectionHook reaction - osHandleProtectionErrors */ 
/* TR:SASR30:0397 Start osHandleProtectionErrors */ 
osqFunc1 void osqFunc2 osHandleProtectionErrors(ProtectionReturnType proRet, StatusType Fatalerror)  /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osHandleProtectionErrors */

   COVER(0x040A)
   if ((((osdCtxErrorHookFromStartupHook | osdCtxStartupHook) & osCurrentContext) != 0)
       && (proRet != PRO_IGNORE))
   {  /* always Shutdown for protection errors in StartupHook */
      COVER(0x040B)
      /* Value of proRet might be unused in some configurations.
       * To reduce code complexity this assignment is not removed for complex configurations.
       * This is no MISRA error. (3199)
       */
       
      proRet = PRO_SHUTDOWN;   /* PRQA S 3199 */
   }
   ELSEWITHCOVER(0x040C)
   
   switch (proRet)
   {
         case PRO_IGNORE:
            return;
      
         case PRO_SHUTDOWN:
         default:
               COVER(0x040D)
               osSysShutdownOS(Fatalerror); /* TR:SASR30:0146 */

   }/* switch (proRet) */
}
/* TR:SASR30:0397 End */
/* TR:SASR30:0388 End */
/* TR:SASR30:0043 End */

/*-+--------------------------------------------------------------------------
 / osStackOverflow
 / Funktion:
 /   - called on task stack overflow: abort system
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 VIOLATION: See below at the 8.10 violation */
/* MISRA RULE 8.10 VIOLATION: The function osStackOverflow is a general implementation for different plattforms. 
 * It is called from the task dispatcher (in this file) and from the interrupt wrappers of category 2 ISRs. 
 * Both might be implemented in C or assembly language, dependent on the plattform. For this reason, 
 * MISRA checkers might see only calls from within osek.c or see no call at all. Therefore they wrongly 
 * state a violation of rule 14.1 or 8.10. */
/* TR:SASR30:0025 Start */
osqFunc1 void osqFunc2 osStackOverflow(void)      /* PRQA S 1505 */ /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osStackOverflow */

   ProtectionReturnType proRet;
   
   /* CovComment 4:  Function: osStackOverflow */
   COVER(0x040E)
   osDisableGlobal();
   /* TR:SPMF07:0006 Start */ 
   /* TR:SPMF07:0007 Start */ 
   osLastError = osdErrSOStackOverflow; 

   proRet = osProtectionHookWrapper(E_OS_STACKFAULT); /* TR:SASR30:0077 *//* TR:SASR30:0204 */
   osHandleProtectionErrors(proRet, E_OS_STACKFAULT);
   /* TR:SPMF07:0006 End */ 
   /* TR:SPMF07:0007 End */ 
}
/* TR:SASR30:0025 End */

osqFunc1 void osqFunc2 osShutdownHookWrapper(StatusType ErrorCode)
{
   /* CovComment 4:  Function: osShutdownHookWrapper */
   /* osSysShutdownOS has already switched to privileged mode */
   COVER(0x040F)
   ShutdownHook(ErrorCode);    /* TR:SPMF89:01.0028 */
}

osqFunc1 void osqFunc2 osErrorHookWrapper(StatusType ErrorCode)
{
   /* CovComment 4:  Function: osErrorHookWrapper */

   /* TR:SPMF89:01.0039 Start */
   osuint8 osSavedAPIStatus;
   /* KB begin osekHWSctxPrivModeVariable (overwritten) */
   osuint32 trust;
   /* KB end osekHWSctxPrivModeVariable */

   COVER(0x0410)
   /* KB begin osekHWSctxSwitchToPrivModeStore (overwritten) */
   trust = osSwitchToPrivMode();   
   /* KB end osekHWSctxSwitchToPrivModeStore */

   /* save and reset API status to prevent IntAPI errors inside errorhook */
   osSavedAPIStatus = osaIntAPIStatus;
   osSetIntAPIStatus(0);

   ErrorHook(ErrorCode);  /* TR:SPMF89:01.0025 */ /* TR:SPMF89:01.0026 */
   /* TR:SPMF89:01.0039 End */

   /* TR:SPMF89:01.0040 Start */
   /* restore old IntAPI status */
   osSetIntAPIStatus(osSavedAPIStatus);

   /* KB begin osekHWSctxRestorePrivMode (overwritten) */
   if (trust == 0)
   {
      COVER(0x0411)
      osSwitchToUserMode();
   }
   ELSEWITHCOVER(0x0412)
   /* KB end osekHWSctxRestorePrivMode */
   /* TR:SPMF89:01.0040 End */
}

osqFunc1 void osqFunc2 osStartupHookWrapper(void)
{
   /* CovComment 4:  Function: osStartupHookWrapper */
   
   /* KB begin osekHWSctxPrivModeVariable (overwritten) */
   osuint32 trust;
   /* KB end osekHWSctxPrivModeVariable */

   COVER(0x0413)
   /* KB begin osekHWSctxSwitchToPrivModeStore (overwritten) */
   trust = osSwitchToPrivMode();   
   /* KB end osekHWSctxSwitchToPrivModeStore */

   StartupHook();

   /* KB begin osekHWSctxRestorePrivMode (overwritten) */
   if (trust == 0)
   {
      COVER(0x0414)
      osSwitchToUserMode();
   }
   ELSEWITHCOVER(0x0415)
   /* KB end osekHWSctxRestorePrivMode */
}

/*-+--------------------------------------------------------------------------
 / CallTrustedFunction
 / ====================
 /
 / Syntax: StatusType CallTrustedFunction (TrustedFunctionIndexType FunctionIndex,
 /                                         TrustedFunctionParameterRefType FunctionParams)
 / Parameter (In): FunctionIndex: Index of the function to be called. 
 /                 FunctionParams or NULL:
 /                 Pointer to the parameters for the function – specified by
 /                 the FunctionIndex - to be called. If no parameters are
 /                 provided, a NULL pointer has to be passed.
 / Parameter (Out): none
 / Return value: E_OK: No Error 
 /               E_OS_SERVICEID: No function defined for this index.
 / Description: 
 / OS265: If <FunctionIndex> is a defined function index, CallTrustedFunction shall
 /        switch the processor into privileged mode AND shall call the function
 /        <FunctionIndex> out of a list of implementation specific trusted functions AND
 /        shall return E_OK after completion.
 / OS312: The called trusted function must conform to the following C prototype:
 /        void TRUSTED_<name_of_the_trusted_service>(
 /        TrustedFunctionIndexType,TrustedFunctionParameterRefType);
 /        (The argument is the same as the argument of CallTrustedFunction).
 / OS266: When the function <FunctionIndex> is called, it shall get the same
 /        permissions (access rights) than the associated trusted OS-Application.
 / OS292: If the function index <FunctionIndex> is undefined, CallTrustedFunction
 /        shall return E_OS_SERVICEID.
 / Scalability Classes: SC3, SC4
 /--------------------------------------------------------------------------*/
/* TR:SASR30:0040 Start */
/* TR:SASR30:0110 Start */
/* TR:SASR30:0183 Start No change of interrupt priority or osCurrentContext */
/* TR:SASR30:0395 Start osCallTrustedFunction */
osqFunc1 StatusType osqFunc2 osCallTrustedFunction(TrustedFunctionIndexType FunctionIndex,         /* TR:SASR30:0370 Start */
                                                   TrustedFunctionParameterRefType FunctionParams) /* TR:SASR30:0370 End */
{
   /* CovComment 4:  Function: osCallTrustedFunction */
   /* check call context */
   /* TR:SASR30:0035 Start Context check in CallTrustedFunction  */
   /* TR:SASR30:0336 Start Context check in CallTrustedFunction  */
   COVER(0x0416)
   if ((osdValidCtx_CallTrustedFunction & osCurrentContext) == 0)
   {
      COVER(0x0417)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osAPIError(E_OS_CALLEVEL, osdErrCTCallContext);
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      return E_OS_CALLEVEL;
   }
   ELSEWITHCOVER(0x0418)
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   /* TR:SASR30:0038 Start Check disabled interrupts in CallTrustedFunction */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x0419)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osAPIError(E_OS_DISABLEDINT, osdErrCTIntAPIDisabled);
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   ELSEWITHCOVER(0x041A)
   /* TR:SASR30:0038 End */
   /* TR:SASR30:0137 Start */
   if (FunctionIndex >= osConfigBlock.uiNumberOfTrustedFunctions)
   {
      COVER(0x041B)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osAPIError(E_OS_SERVICEID, osdErrCTWrongFctIdx); /* TR:SASR30:0042 */
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      return E_OS_SERVICEID;
   }
   ELSEWITHCOVER(0x041C)
   /* TR:SASR30:0137 End */
   /* TR:SPMF89:01.0041 Start */
   COVER(0x041D)
   osInSystemFct++;
   
   /* KB begin osekHWSctxCallTrustedFctCall (overwritten) */
   (*((TrustedFunctionType*)(OSCFGBLOCK->uiStartAddressTrustedFct))[FunctionIndex])(FunctionIndex, FunctionParams); 
   /* KB end osekHWSctxCallTrustedFctCall */
   /* TR:SPMF89:01.0041 End */
   
   /* TR:SPMF89:01.0042 Start */
   osInSystemFct--;

   return E_OK;
   /* TR:SPMF89:01.0042 End */
} /* END OF osCallTrustedFunction */
/* TR:SASR30:0395 End */
/* TR:SASR30:0183 End */
/* TR:SASR30:0110 End */
/* TR:SASR30:0040 End */


/*-+--------------------------------------------------------------------------
 / GetApplicationID
 / ================
 /
 / Syntax: ApplicationType GetApplicationID (void)
 / Parameter (In): none
 / Parameter (Out): none
 / Return value: Identifier of running OS-Application or INVALID_OSAPPLICATION
 / Description: 
 / OS261: If an OS-Application is running, GetApplicationID shall return its identifier.
 / OS262: If no OS-Application is running, GetApplicationID shall return
 /        INVALID_OSAPPLICATION.
 / Scalability Classes: SC3, SC4
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 VIOLATED: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/GetApplicationID. 
 */
/* TR:SASR30:0007 Start */
/* TR:SASR30:0106 Start */
/* TR:SASR30:0185 Start No error hook in GetApplicationID */
/* TR:SASR30:0368 Start */
osqFunc1 ApplicationType osqFunc2 osGetApplicationID(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osGetApplicationID */
   COVER(0x041E)

   return osaActiveApplicationID; /* TR:SASR30:0107 */
} /* END OF osGetApplicationID */
/* TR:SASR30:0368 End */
/* TR:SASR30:0185 End */
/* TR:SASR30:0106 End */
/* TR:SASR30:0007 End */



/*-+--------------------------------------------------------------------------
 / osGetStackUsage
 / Funktion:
 /   - calculate maximum stack usage of task <taskId>
 / Parameter:
 / Returnvalue: calculated stack usage (in byte)
 /--------------------------------------------------------------------------*/
/* TR:SPMF08:0007 Start */
osqFunc1 osStackUsageType osqFunc2 osGetStackUsage(TaskType taskId)
{
   /* CovComment 4:  Function: osGetStackUsage */
   osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *stack;

   COVER(0x041F)
   if (taskId >= OSCFGBLOCK->uiNumberOfTasks)
   {
      COVER(0x0420)
      osEnterSafeState(E_OS_SYS_ASSERTION, osdErrSUWrongTaskID); /* TR:SOSK22:0074 */
   }
   ELSEWITHCOVER(0x0421)

   stack = (osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *)(((osuint32*)(OSCFGBLOCK->uiStartAddressTaskStackStartAddress))[taskId]);

   while ((stack < (osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *)(((osuint32*)(OSCFGBLOCK->uiStartAddressTaskStackEndAddress))[taskId])) && (*stack == 0xAA))
   {
      COVER(0x0422)
      stack++;
   }
   return (osStackUsageType)((osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *)(((osuint32*)(OSCFGBLOCK->uiStartAddressTaskStackEndAddress))[taskId]) - stack);
} /* end of osGetStackUsage */ /* TR:SPMF08:0007 End */



/* KB begin osekHWosDisableLevelSrc (overwritten) */
/* KB end osekHWosDisableLevelSrc */

/* KB begin osekHWosEnableLevelSrc (overwritten) */
/* KB end osekHWosEnableLevelSrc */

/* KB begin osekHWosSetAlarmLevelSrc (overwritten) */
/* KB end osekHWosSetAlarmLevelSrc */

/* KB begin osekHWosSaveDisableLevelSrc (overwritten) */
/* KB end osekHWosSaveDisableLevelSrc */

/* KB begin osekHWosRestoreEnableLevelSrc (overwritten) */
/* KB end osekHWosRestoreEnableLevelSrc */

/* KB begin osekHWosDisableGlobalSrc (overwritten) */
void osDisableGlobal(void)
{
   /* CovComment 4:  Function: osDisableGlobal */

   COVER(0x0423)
   (void)_disable_IRQ();
}
/* KB end osekHWosDisableGlobalSrc */

/* KB begin osekHWosEnableGlobalSrc (overwritten) */
void osEnableGlobal(void)
{
   /* CovComment 4:  Function: osEnableGlobal */

   COVER(0x0424)
   (void)_enable_IRQ();
}
/* KB end osekHWosEnableGlobalSrc */

/* KB begin osekHWosSaveDisableLevelNestedSrc (overwritten) */
static osqFunc1 void osqFunc2 osSaveDisableLevelNested(void)
{
   /* CovComment 4:  Function: osSaveDisableLevelNested */

   osuint8 SavedLevel;
   COVER(0x0425)
   if (osaIntSaveDisableCounter == 0U) 
   {
      COVER(0x0426)
      if ((_get_CPSR() & 0x80) != 0)
      { 
         COVER(0x0427)
         SavedLevel = (osIntLevelType)1;
      }
      else
      {
         COVER(0x0428)
         SavedLevel = (osIntLevelType)0;
      }
      (void)_disable_IRQ();
      osaSavedIntLevelNested = SavedLevel;
   }
   ELSEWITHCOVER(0x0429)
   osaIntSaveDisableCounter++;
}
/* KB end osekHWosSaveDisableLevelNestedSrc */

/* KB begin osekHWosRestoreEnableLevelNestedSrc (overwritten) */
static osqFunc1 void osqFunc2 osRestoreEnableLevelNested(void)
{
   /* CovComment 4:  Function: osRestoreEnableLevelNested */

   COVER(0x042A)
   osaIntSaveDisableCounter--;
   if (osaIntSaveDisableCounter == 0U)
   {  
      COVER(0x042B)
      if(osaSavedIntLevelNested==0) 
      {
         COVER(0x042C)
         (void)_enable_IRQ(); 
      }
      else 
      {
         COVER(0x042D)
         (void)_disable_IRQ();
      }
      COVER(0x042E)
   }
   ELSEWITHCOVER(0x042F)
}
/* KB end osekHWosRestoreEnableLevelNestedSrc */

/* KB begin osekHWosSaveDisableGlobalNestedSrc (overwritten) */
/* KB end osekHWosSaveDisableGlobalNestedSrc */

/* KB begin osekHWosRestoreEnableGlobalNestedSrc (overwritten) */
/* KB end osekHWosRestoreEnableGlobalNestedSrc */
/* TR:SOSK22:0071 Start */
/* TR:SOSK22:0072 Start */
/*-+--------------------------------------------------------------------------
 / osEnableAllInterrupts
 / Function:    implementation of API function EnableAllInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/EnableAllInterrupts
 */
osqFunc1 void osqFunc2 osEnableAllInterrupts(void) /* TR:SOSK22:0185 */
{ 
   /* CovComment 4:  Function: osEnableAllInterrupts */
   COVER(0x0430)
   /* TR:SOSK22:0254 Start */
   /* TR:SOSK22:0256 Start */
   /* TR:SASR30:0037 Start */
   osSysErrAssert(osaIntAPIStatus==osdIntAPIDisableAll,osdErrEAIntAPIWrongSequence)

   if (osaIntAPIStatus!=osdIntAPIDisableAll)
   {
      COVER(0x0431)
      return;
   }
   /* TR:SASR30:0037 End */
   ELSEWITHCOVER(0x0432)

   osSetIntAPIStatus(0);
   /* TR:SOSK22:0254 End */
   /* KB begin osekHWosRestoreEnableGlobalBody (overwritten) */
   {
      /* TR:SOSK22:0252 Start */
      osuint32 tmp;
   
      tmp = _get_CPSR();
      _set_CPSR((tmp & 0x7fUL) | (osaSavedGlobalInt & 0x80UL));   /* TR:SPMF89:01.0011 */
      /* TR:SOSK22:0252 End */
   }
   /* KB end osekHWosRestoreEnableGlobalBody */
   /* TR:SOSK22:0256 End */
}


/*-+--------------------------------------------------------------------------
 / osDisableAllInterrupts
 / Function:    implementation of API function DisableAllInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/DisableAllInterrupts
 */
osqFunc1 void osqFunc2 osDisableAllInterrupts(void) /* TR:SOSK22:0186 */
{
   /* TR:SOSK22:0256 Start */
   /* CovComment 4:  Function: osDisableAllInterrupts */
   COVER(0x0433)
/*   osSysErrAssert(!osaIntAPIStatus,osdErrDAIntAPIDisabled) */
   if (osaIntAPIStatus!=0)
   {
      COVER(0x0434)
      osEnterSafeState(E_OS_SYS_ASSERTION, osdErrDAIntAPIDisabled); /* TR:SOSK22:0074 */
      return;
   }
   ELSEWITHCOVER(0x0435)
   /* KB begin osekHWosSaveDisableGlobalBody (overwritten) */
   {
      /* TR:SOSK22:0255 Start */
      osaSavedGlobalInt = (osIntLevelType)_disable_IRQ();  /* TR:SPMF89:01.0010 */
      /* TR:SOSK22:0255 End */
   }
   /* KB end osekHWosSaveDisableGlobalBody */
   osSetIntAPIStatus(osdIntAPIDisableAll);  
   /* TR:SOSK22:0256  End*/ 
}
/* TR:SOSK22:0071 End */
/* TR:SOSK22:0072 End */
/*-+--------------------------------------------------------------------------
 / osResumeOSInterrupts
 / Function:    implementation of API function ResumeOSInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/ResumeOSInterrupts
 */
osqFunc1 void osqFunc2 osResumeOSInterrupts(void) /* TR:SOSK22:0189 */
{
   /* TR:SOSK22:0266 Start */
   /* CovComment 4:  Function: osResumeOSInterrupts */
   COVER(0x0436)
   /* TR:SASR30:0037 Start */
   if (osaIntSaveDisableCounter==0)
   {
      COVER(0x0437)
      return;
   }
   /* TR:SASR30:0037 End */
   ELSEWITHCOVER(0x0438)
   
   osDecIntAPIStatus();
   /* KB begin osekHWosRestoreEnableLevelNestedBody (overwritten) */
   /* TR:SOSK22:0258 Start */
   /* TR:SOSK22:0263 Start */
   /* TR:SPMF89:01.0013 Start */
   /* TR:SPMF89:01.0015 Start */
   osaIntSaveDisableCounter--;
   if (osaIntSaveDisableCounter == 0U)
   {  
      if(osaSavedIntLevelNested==0) 
      {
         osEnableLevel(); 
      }
      else 
      {
         osDisableLevel();
      }
      COVER(0x0439)
   } /* TR:SOSK22:0258 End */ /* TR:SOSK22:0263 End */
   /* TR:SPMF89:01.0013 End */
   /* TR:SPMF89:01.0015 End */
   ELSEWITHCOVER(0x043A)
   /* KB end osekHWosRestoreEnableLevelNestedBody */
   /* TR:SOSK22:0266 End */
}


/*-+--------------------------------------------------------------------------
 / osSuspendOSInterrupts
 / Function:    implementation of API function SuspendOSInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/SuspendOSInterrupts
 */
osqFunc1 void osqFunc2 osSuspendOSInterrupts(void) /* TR:SOSK22:0190 */
{
   /* TR:SOSK22:0266 Start */
   /* CovComment 4:  Function: osSuspendOSInterrupts */
   COVER(0x043B)
   if (osaIntSaveDisableCounter==255)
   {
      COVER(0x043C)
      return;
   }
   ELSEWITHCOVER(0x043D)
   /* KB begin osekHWosSaveDisableLevelNestedBody (overwritten) */
   {
      /* TR:SOSK22:0260 Start */
      /* TR:SOSK22:0265 Start */
      osuint8 SavedLevel;
      osSysErrAssert(osaIntSaveDisableCounter < 63U, osdErrSDWrongCounter)
      /* TR:SPMF89:01.0012 Start */
      /* TR:SPMF89:01.0014 Start */
      if (osaIntSaveDisableCounter == 0U) 
      {
         COVER(0x043E)
         SavedLevel = (osIntLevelType)osGetLevel();
         osDisableLevel();
         osaSavedIntLevelNested = SavedLevel;
      }
      ELSEWITHCOVER(0x043F)
      osaIntSaveDisableCounter++;
      /* TR:SPMF89:01.0012 End */
      /* TR:SPMF89:01.0014 End */
      /* TR:SOSK22:0260 End */
      /* TR:SOSK22:0265 End */
   }
   /* KB end osekHWosSaveDisableLevelNestedBody */
   osIncIntAPIStatus();
   /* TR:SOSK22:0266 End */
}

/* TR:SOSK22:0072 Start */
/*-+--------------------------------------------------------------------------
 / osResumeAllInterrupts
 / Function:    implementation of API function ResumeAllInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/ResumeAllInterrupts
 */
osqFunc1 void osqFunc2 osResumeAllInterrupts(void) /* TR:SOSK22:0187 */
{
   /* TR:SOSK22:0261 Start */
   /* CovComment 4:  Function: osResumeAllInterrupts */
   COVER(0x0440)
   /* TR:SASR30:0037 Start */
   if (osaIntSaveDisableCounter==0)
   {
      COVER(0x0441)
      return;
   }
   ELSEWITHCOVER(0x0442)
   /* TR:SASR30:0037 End */

   osDecIntAPIStatus();
   /* KB begin osekHWosRestoreEnableLevelNestedBody (overwritten) */
   /* TR:SOSK22:0258 Start */
   /* TR:SOSK22:0263 Start */
   /* TR:SPMF89:01.0013 Start */
   /* TR:SPMF89:01.0015 Start */
   osaIntSaveDisableCounter--;
   if (osaIntSaveDisableCounter == 0U)
   {  
      if(osaSavedIntLevelNested==0) 
      {
         osEnableLevel(); 
      }
      else 
      {
         osDisableLevel();
      }
      COVER(0x0443)
   } /* TR:SOSK22:0258 End */ /* TR:SOSK22:0263 End */
   /* TR:SPMF89:01.0013 End */
   /* TR:SPMF89:01.0015 End */
   ELSEWITHCOVER(0x0444)
   /* KB end osekHWosRestoreEnableLevelNestedBody */
   /* TR:SOSK22:0261 End */
}


/*-+--------------------------------------------------------------------------
 / osSuspendAllInterrupts
 / Function:    implementation of API function SuspendAllInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/SuspendAllInterrupts
 */
osqFunc1 void osqFunc2 osSuspendAllInterrupts(void) /* TR:SOSK22:0188 */
{
   /* TR:SOSK22:0261 Start */
   /* CovComment 4:  Function: osSuspendAllInterrupts */
   COVER(0x0445)
   if (osaIntSaveDisableCounter==255)
   {
      COVER(0x0446)
      return;
   }
   ELSEWITHCOVER(0x0447)

   /* KB begin osekHWosSaveDisableLevelNestedBody (overwritten) */
   {
      /* TR:SOSK22:0260 Start */
      /* TR:SOSK22:0265 Start */
      osuint8 SavedLevel;
      osSysErrAssert(osaIntSaveDisableCounter < 63U, osdErrSDWrongCounter)
      /* TR:SPMF89:01.0012 Start */
      /* TR:SPMF89:01.0014 Start */
      if (osaIntSaveDisableCounter == 0U) 
      {
         COVER(0x0448)
         SavedLevel = (osIntLevelType)osGetLevel();
         osDisableLevel();
         osaSavedIntLevelNested = SavedLevel;
      }
      ELSEWITHCOVER(0x0449)
      osaIntSaveDisableCounter++;
      /* TR:SPMF89:01.0012 End */
      /* TR:SPMF89:01.0014 End */
      /* TR:SOSK22:0260 End */
      /* TR:SOSK22:0265 End */
   }
   /* KB end osekHWosSaveDisableLevelNestedBody */
   osIncIntAPIStatus();
   /* TR:SOSK22:0261 End */
}
/* TR:SOSK22:0072 End */

osqFunc1 void osqFunc2 osEnterSafeState(StatusType ErrorCode, osuint16 OSErrorCode)
{
   /* CovComment 4:  Function: osEnterSafeState */

   osLastError = OSErrorCode;
   osSysShutdownOS(ErrorCode);
}

static osuint16 crc16(const osuint8 * const ptr, osuint16 length)
{
   /* CovComment 4:  Function: crc16 */
   const osuint16 POLY= 0x1021; /* Polynom 0x1021 */

   osuint16 crc;
   osuint16 n,i;
   osuint8 b;


   COVER(0x044A)
   crc= 0xFFFFU; /* set initial value */

   for (i= 0; i < length; i++)
   {
      b= ptr[i];

      crc= crc ^ (((osuint16)b)<<8); /* crc xor b; */

      for (n= 1; n <= 8; n++)
      {
         if ((crc & 0x8000U) != 0)
         {
            crc= (osuint16)((crc << 1) ^ POLY); /* SHR */
         }
         else
         {
            crc= (osuint16)(crc << 1);
         }
      }
   }

   return crc;
}


static osuint8 osCheckConfigBlock(void)
{
   /* CovComment 4:  Function: osCheckConfigBlock */

   osuint16 uiConfigBlockLength;
   osuint16 uiMagicCheck;
   const osuint8 * const ptr = (const osuint8 *) &osConfigBlock;
   /* 1. Check Magicnumber */

   COVER(0x044B)
   if (ptr[0] != 0x82)
   {
   	return 0;
   }
   ELSEWITHCOVER(0x044C)

   if (ptr[1] != 0x2A)
   {
   	return 0;
   }
   ELSEWITHCOVER(0x044D)

   if (ptr[2] != 0x0C)
   {
   	return 0;
   }
   ELSEWITHCOVER(0x044E)

   if (ptr[3] != 0xC4)
   {
   	return 0;
   }
   ELSEWITHCOVER(0x044F)

   /* 2. Get Length */
   uiConfigBlockLength= (osuint16)(((osuint32)ptr[4]) + ((osuint32)(ptr[5]) << 8));

   /* Calculate Magic Checkword */
   uiMagicCheck= crc16(ptr, uiConfigBlockLength); /* TR:SPMF89:0006 */

   if (uiMagicCheck != 0x0000)
   {
   	return 0;
   }
   ELSEWITHCOVER(0x0450)

   return 1;
}


/* TR:SPMF89:0040 Start */
/* MISRA RULE 14.1 VIOLATION: The function osGetConfigBlockVersion() belongs to static ASIL code.
 * For this reason, its always existing, even if its not needed. */
osuint16 osGetConfigBlockVersion(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osGetConfigBlockVersion */
   COVER(0x0451)
   return osConfigBlock.uiUserConfigurationVersion;
}
/* TR:SPMF89:0040 End */


/* KB begin osekHWSctxCode (overwritten) */

#define osdVIMbase 0xFFFFfe00UL
#define osdVIMRAM  0xFFF82000UL

/* MISRA RULE 14.1 not violated: (comment 1503) The function 'osInitISRs' is called from assembler code.
 * The MISRA checker sees only the accesses from C language. */  
osqFunc1 void osqFunc2 osInitISRs(void)  /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osInitISRs */
   osuint16 i;

   COVER(0x0452)
   /* set FIRQPR (0s are IRQ - 1s are FIQ): */
   *((volatile osuint32*)(osdVIMbase + 0x10)) = ((osuint32*)(OSCFGBLOCK->uiStartAddressIRQFIQSetting))[0];
   *((volatile osuint32*)(osdVIMbase + 0x14)) = ((osuint32*)(OSCFGBLOCK->uiStartAddressIRQFIQSetting))[1];
   *((volatile osuint32*)(osdVIMbase + 0x18)) = ((osuint32*)(OSCFGBLOCK->uiStartAddressIRQFIQSetting))[2];

   /* set CHANCTRLx (1byte per prio): */
   for (i=0; i<24; i++)
   {
      *((volatile osuint32*)(osdVIMbase + 0x80 + (i*4))) = ((osuint32*)(OSCFGBLOCK->uiStartAddressINTChannelMap))[i];
   }

   /* Initialize VIMRAM */
   osDisableHWVector();    /* disable hardware vectored interrupt mode */
   for (i=0; i<96; i++)
   {
      *((volatile osuint32*)(osdVIMRAM + (i*4))) = osaIRQTable[i];
   }
   osEnableHWVector();    /* enable hardware vectored interrupt mode */
}

/* MISRA RULE 14.1 not violated: The function osAsmAssertFailed() is called from 
 * assembly language. Typical MISRA checkers are not able to see the call. */
void osAsmAssertFailed(osuint16 err) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osAsmAssertFailed */
   
   COVER(0x0453)
   osEnterSafeState(E_OS_SYS_ASSERTION, err);
}

/* MISRA RULE 14.1 not violated: The function osSetMPUForOS() is called from 
 * assembly language. Typical MISRA checkers are not able to see the call. */
void osSetMPUForOS(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osSetMPUForOS */

   COVER(0x0454)
   osMPUDisable();
   osSetMPUFromOSConfig(osdMPURegionNr_STACK, osdStackAreaID); /* TR:SPMF89:01.0076 */  /* TR:SPMF89:0018 */
   osSetMPUFromOSConfig(osdMPURegionNr_APPLDATA_NOINIT, osdApplDataAreaID); /* TR:SPMF89:01.0077 */ 
   
   osSetupMPURegion(osdMPURegionNr_APPLDATA_INIT, 0, 0, 0);
   osSetupMPURegion(osdMPURegionNr_AREA4, 0, 0, 0);
   osSetupMPURegion(osdMPURegionNr_AREA6, 0, 0, 0);
   osSetupMPURegion(osdMPURegionNr_AREA8, 0, 0, 0);
   osSetupMPURegion(osdMPURegionNr_AREA9, 0, 0, 0);
   osSetupMPURegion(osdMPURegionNr_AREA10, 0, 0, 0);
   osSetupMPURegion(osdMPURegionNr_AREA11, 0, 0, 0);
   osMPUEnable();
}




/* MISRA RULE 14.1 not violated: (comment 1503) The function osSetMPUForTask() is called from 
 * assembly language. Typical MISRA checkers are not able to see the call. */
void osSetMPUForTask(void)     /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osSetMPUForTask */

   TaskType idx;
   ApplicationType appl;

   COVER(0x0455)
   if ((osaOnAPIStack > 1) || (osaActiveApplicationID == INVALID_OSAPPLICATION))
   {
      return;
   }
   ELSEWITHCOVER(0x0456)
   
   if (osaIntNestingDepth == 0)
   {
      COVER(0x0457)
      if (osaActiveTaskIndex == INVALID_TASK)
      {
         return;
      }
      ELSEWITHCOVER(0x0458)
      
      idx = osaActiveTaskIndex;
      
      /* TR:SASR30:0034 Start *//* TR:SASR30:0323 Start */ /* TR:SASR30:0177 Start */ /* TR:SASR30:0069 Start */ /* TR:SASR30:0073 Start */
      if (osaTcbNTFNestingDepth[idx] == 0)
      {
         COVER(0x0459)
         if (((osuint8*)(OSCFGBLOCK->uiStartAddressTaskTrusted))[idx] == 0) /* TR:SASR30:0321 */ /* TR:SASR30:0075 */
         {
            COVER(0x045A)
            osMPUDisable();
            osSetMPUFromTaskConfig(idx, osdMPURegionNr_STACK, osdStackAreaID); /* TR:SASR30:0068 */ /* TR:SASR30:0074 */ /* TR:SASR30:0176 */ /* TR:SASR30:315 */ /* TR:SPMF89:01.0076 */ /* TR:SPMF89:0018 */
            osSetMPUFromTaskConfig(idx, osdMPURegionNr_APPLDATA_NOINIT, osdApplDataAreaID);  /* TR:SPMF89:01.0077 */
            osSetMPUFromTaskConfig(idx, osdMPURegionNr_APPLDATA_INIT, osdApplInitDataAreaID); /* TR:SPMF89:01.0079 */
            osSetMPUFromTaskConfig(idx, osdMPURegionNr_AREA4, osdArea4ID);     /* TR:SPMF89:01.0078 */
            osSetMPUFromTaskConfig(idx, osdMPURegionNr_AREA6, osdArea6ID);     /* TR:SPMF89:01.0080 */
            osSetMPUFromTaskConfig(idx, osdMPURegionNr_AREA8, osdArea8ID);     /* TR:SPMF89:01.0082 */
            osSetMPUFromTaskConfig(idx, osdMPURegionNr_AREA9, osdArea9ID);     /* TR:SPMF89:01.0083 */
            osSetMPUFromTaskConfig(idx, osdMPURegionNr_AREA10, osdArea10ID);   /* TR:SPMF89:01.0084 */
            osSetMPUFromTaskConfig(idx, osdMPURegionNr_AREA11, osdArea11ID);   /* TR:SPMF89:01.0085 */
            osMPUEnable();
         }
         ELSEWITHCOVER(0x045B)
      }
      else
      {
         osMPUDisable();
         osSetupMPURegion(osdMPURegionNr_STACK, 
                          ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFTaskStackMPUSetting))[idx].aulMPUSectionStartAddress, 
                          ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFTaskStackMPUSetting))[idx].aulMPUSectionSize, 
                          ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFTaskStackMPUSetting))[idx].aulMPUSectionAccess);
         
         appl = osaActiveApplicationID;
         osSetMPUFromApplConfig(appl, osdMPURegionNr_APPLDATA_NOINIT, osdApplDataAreaID); /* TR:SPMF89:01.0077 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_APPLDATA_INIT, osdApplInitDataAreaID); /* TR:SPMF89:01.0079 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA4, osdArea4ID);   /* TR:SPMF89:01.0078 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA6, osdArea6ID);   /* TR:SPMF89:01.0080 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA8, osdArea8ID);   /* TR:SPMF89:01.0082 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA9, osdArea9ID);   /* TR:SPMF89:01.0083 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA10, osdArea10ID); /* TR:SPMF89:01.0084 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA11, osdArea11ID); /* TR:SPMF89:01.0085 */
         osMPUEnable();
      }
      /* TR:SASR30:0034 End *//* TR:SASR30:0323 End */ /* TR:SASR30:0177 End */ /* TR:SASR30:0069 End */ /* TR:SASR30:0073 End */
   }
   else
   {
      COVER(0x045C)
      idx = osaActiveISRID;
      /* TR:SASR30:0034 Start *//* TR:SASR30:0323 Start */ /* TR:SASR30:0177 Start */ /* TR:SASR30:0069 Start */ /* TR:SASR30:0073 Start */
      if (osaIcbNTFNestingDepth[idx] == 0)
      {
         COVER(0x045D)
         if (((osuint8*)(OSCFGBLOCK->uiStartAddressISRTrusted))[idx] == 0) /* TR:SASR30:0321 */ /* TR:SASR30:0075 */
         {
            COVER(0x045E)
            osMPUDisable();
            /* TR:SASR30:0068 Start *//* TR:SASR30:0074 Start *//* TR:SASR30:0176 Start *//* TR:SASR30:0315 Start */
            osSetupMPURegion(osdMPURegionNr_STACK, 
                    ((osuint32*)(OSCFGBLOCK->uiStartAddressISRStackStart))[osaIntNestingDepth-1], 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressISRMPUSettings))[idx].aulMPUSectionSize[osdStackAreaID], 
                    ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressISRMPUSettings))[idx].aulMPUSectionAccess[osdStackAreaID]);  /* TR:SPMF89:01.0076 */
            /* TR:SASR30:0068 End *//* TR:SASR30:0074 End *//* TR:SASR30:0176 End *//* TR:SASR30:0315 End */  /* TR:SPMF89:0018 */
            osSetMPUFromISRConfig(idx, osdMPURegionNr_APPLDATA_NOINIT, osdApplDataAreaID); /* TR:SPMF89:01.0077 */
            osSetMPUFromISRConfig(idx, osdMPURegionNr_APPLDATA_INIT, osdApplInitDataAreaID); /* TR:SPMF89:01.0079 */
            osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA4, osdArea4ID);      /* TR:SPMF89:01.0078 */
            osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA6, osdArea6ID);      /* TR:SPMF89:01.0080 */
            osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA8, osdArea8ID);      /* TR:SPMF89:01.0082 */
            osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA9, osdArea9ID);      /* TR:SPMF89:01.0083 */
            osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA10, osdArea10ID);    /* TR:SPMF89:01.0084 */
            osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA11, osdArea11ID);    /* TR:SPMF89:01.0085 */
            osMPUEnable();
         }
      }
      else
      {
         COVER(0x045F)
         osMPUDisable();
         
         osSetupMPURegion(osdMPURegionNr_STACK, 
                          ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFISRStackMPUSetting))[idx].aulMPUSectionStartAddress, 
                          ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFISRStackMPUSetting))[idx].aulMPUSectionSize, 
                          ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFISRStackMPUSetting))[idx].aulMPUSectionAccess); /* TR:SPMF89:01.0076 */
         
         appl = osaActiveApplicationID;
         osSetMPUFromApplConfig(appl, osdMPURegionNr_APPLDATA_NOINIT, osdApplDataAreaID); /* TR:SPMF89:01.0077 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_APPLDATA_INIT, osdApplInitDataAreaID); /* TR:SPMF89:01.0079 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA4, osdArea4ID);     /* TR:SPMF89:01.0078 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA6, osdArea6ID);     /* TR:SPMF89:01.0080 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA8, osdArea8ID);     /* TR:SPMF89:01.0082 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA9, osdArea9ID);     /* TR:SPMF89:01.0083 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA10, osdArea10ID);   /* TR:SPMF89:01.0084 */
         osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA11, osdArea11ID);   /* TR:SPMF89:01.0085 */
         osMPUEnable();
      }
      /* TR:SASR30:0034 End *//* TR:SASR30:0323 End */ /* TR:SASR30:0177 End */ /* TR:SASR30:0069 End */ /* TR:SASR30:0073 End */
   }
}


/* MISRA RULE 14.1 not violated: (comment 1503) The function osSaveTaskMPUSettings() is called from 
 * assembly language. Typical MISRA checkers are not able to see the call. */
void osSaveTaskMPUSettings(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osSaveTaskMPUSettings */

   TaskType idx;
   
   COVER(0x0460)
   idx = osaActiveTaskIndex;
   osStoreRegionSettings(osdMPURegionNr_STACK, &(osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_STACK]), &(osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_STACK]), 0);
   osStoreRegionSettings(osdMPURegionNr_APPLDATA_NOINIT, &(osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_APPLDATA_NOINIT]), &(osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_APPLDATA_NOINIT]), 0);
   osStoreRegionSettings(osdMPURegionNr_APPLDATA_INIT, &(osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_APPLDATA_INIT]), &(osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_APPLDATA_INIT]), 0);
   osStoreRegionSettings(osdMPURegionNr_AREA4, &(osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA4]), &(osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA4]), &(osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA4]));
   osStoreRegionSettings(osdMPURegionNr_AREA6, &(osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA6]), &(osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA6]), &(osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA6]));
   osStoreRegionSettings(osdMPURegionNr_AREA8, &(osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA8]), &(osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA8]), &(osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA8]));
   osStoreRegionSettings(osdMPURegionNr_AREA9, &(osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA9]), &(osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA9]), &(osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA9]));
   osStoreRegionSettings(osdMPURegionNr_AREA10, &(osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA10]), &(osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA10]), &(osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA10]));
   osStoreRegionSettings(osdMPURegionNr_AREA11, &(osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA11]), &(osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA11]), &(osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA11]));
}


/* MISRA RULE 14.1 not violated: (comment 1503) The function osRestoreTaskMPUSettings() is called from 
 * assembly language. Typical MISRA checkers are not able to see the call. */
void osRestoreTaskMPUSettings(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osRestoreTaskMPUSettings */

   TaskType idx;
   
   COVER(0x0461)
   osMPUDisable();
   idx = osaActiveTaskIndex;
   osSetupMPURegion(osdMPURegionNr_STACK, osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_STACK], osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_STACK], osdMPUAccessCtrlData);
   osSetupMPURegion(osdMPURegionNr_APPLDATA_NOINIT, osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_APPLDATA_NOINIT], osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_APPLDATA_NOINIT], osdMPUAccessCtrlData);
   osSetupMPURegion(osdMPURegionNr_APPLDATA_INIT, osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_APPLDATA_INIT], osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_APPLDATA_INIT], osdMPUAccessCtrlData);
   osSetupMPURegion(osdMPURegionNr_AREA4, osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA4], osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA4], osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA4]);
   osSetupMPURegion(osdMPURegionNr_AREA6, osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA6], osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA6], osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA6]);
   osSetupMPURegion(osdMPURegionNr_AREA8, osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA8], osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA8], osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA8]);
   osSetupMPURegion(osdMPURegionNr_AREA9, osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA9], osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA9], osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA9]);
   osSetupMPURegion(osdMPURegionNr_AREA10, osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA10], osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA10], osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA10]);
   osSetupMPURegion(osdMPURegionNr_AREA11, osaTcbTaskSavedMPUBase[idx][osdMPURegionNr_AREA11], osaTcbTaskSavedMPUCfg[idx][osdMPURegionNr_AREA11], osaTcbTaskSavedMPUAccess[idx][osdMPURegionNr_AREA11]);
   osMPUEnable();
}


/* MISRA RULE 14.1 not violated: The function osEnterProtectedISR is called from 
 * assembly language. Typical MISRA checkers are not able to see the call.
 */
osuint32 osEnterProtectedISR(osuint32 sp, osuint32 nestDepth)     /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osEnterProtectedISR */

   ISRType idx;
   osuint8 nestLevel;

   COVER(0x0462)
   idx = osaActiveISRID;    
   
   if (OSCFGBLOCK->uiNumberOfCat2ISRs > 0)
   {
      COVER(0x0463)
      nestLevel = (osuint8)(nestDepth-1);
      osaIsrStoredInfo[nestLevel].savedApplID = osaActiveApplicationID;
      osaIsrStoredInfo[nestLevel].stackstart = sp;
      osaActiveApplicationID = ((osuint8*)(OSCFGBLOCK->uiStartAddressISRToAppl))[idx]; 
      osaIsrStoredInfo[nestLevel].prevContext = osCurrentContext;
      osCurrentContext = osdCtxISRCat2;
      osaIsrStoredInfo[nestLevel].InSystemFct = osInSystemFct;
      osaIsrStoredInfo[nestLevel].isKilled = 0;
      osaIsrStoredInfo[nestLevel].reqMask0 = *((volatile osuint32*)osdREQMSKCLR0);
      osaIsrStoredInfo[nestLevel].reqMask1 = *((volatile osuint32*)osdREQMSKCLR1);
      osInSystemFct = 0;

      osaIsrStoredInfo[nestLevel].currentISRID = idx;  
      
      /* save protection registers */
      osStoreRegionSettings(osdMPURegionNr_STACK, &(osaIsrStoredInfo[nestLevel].reg2start), &(osaIsrStoredInfo[nestLevel].reg2sizecfg), 0);
      osStoreRegionSettings(osdMPURegionNr_APPLDATA_NOINIT, &(osaIsrStoredInfo[nestLevel].reg3start), &(osaIsrStoredInfo[nestLevel].reg3sizecfg), 0);
      osStoreRegionSettings(osdMPURegionNr_APPLDATA_INIT, &(osaIsrStoredInfo[nestLevel].reg5start), &(osaIsrStoredInfo[nestLevel].reg5sizecfg), 0);
      osStoreRegionSettings(osdMPURegionNr_AREA4, &(osaIsrStoredInfo[nestLevel].reg4start), &(osaIsrStoredInfo[nestLevel].reg4sizecfg), &(osaIsrStoredInfo[nestLevel].reg4access));
      osStoreRegionSettings(osdMPURegionNr_AREA6, &(osaIsrStoredInfo[nestLevel].reg6start), &(osaIsrStoredInfo[nestLevel].reg6sizecfg), &(osaIsrStoredInfo[nestLevel].reg6access));
      osStoreRegionSettings(osdMPURegionNr_AREA8, &(osaIsrStoredInfo[nestLevel].reg8start), &(osaIsrStoredInfo[nestLevel].reg8sizecfg), &(osaIsrStoredInfo[nestLevel].reg8access));
      osStoreRegionSettings(osdMPURegionNr_AREA9, &(osaIsrStoredInfo[nestLevel].reg9start), &(osaIsrStoredInfo[nestLevel].reg9sizecfg), &(osaIsrStoredInfo[nestLevel].reg9access));
      osStoreRegionSettings(osdMPURegionNr_AREA10, &(osaIsrStoredInfo[nestLevel].reg10start), &(osaIsrStoredInfo[nestLevel].reg10sizecfg), &(osaIsrStoredInfo[nestLevel].reg10access));
      osStoreRegionSettings(osdMPURegionNr_AREA11, &(osaIsrStoredInfo[nestLevel].reg11start), &(osaIsrStoredInfo[nestLevel].reg11sizecfg), &(osaIsrStoredInfo[nestLevel].reg11access));

      /* TR:SASR30:0034 Start *//* TR:SASR30:0323 Start */ /* TR:SASR30:0177 Start */ /* TR:SASR30:0069 Start */ /* TR:SASR30:0073 Start */
      if (((osuint8*)(OSCFGBLOCK->uiStartAddressISRTrusted))[idx] == 0) /* TR:SASR30:0075 */
      {
         COVER(0x0464)
         /* configure memory protection areas */
         osMPUDisable();
         /* TR:SASR30:0068 Start *//* TR:SASR30:0074 Start *//* TR:SASR30:0176 Start *//* TR:SASR30:0315 Start */
         osSetupMPURegion(osdMPURegionNr_STACK, 
                 ((osuint32*)(OSCFGBLOCK->uiStartAddressISRStackStart))[nestLevel], 
                 ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressISRMPUSettings))[idx].aulMPUSectionSize[osdStackAreaID], 
                 ((tsMPUSetting*)(OSCFGBLOCK->uiStartAddressISRMPUSettings))[idx].aulMPUSectionAccess[osdStackAreaID]); /* TR:SPMF89:01.0076 */
         /* TR:SASR30:0068 End *//* TR:SASR30:0074 End *//* TR:SASR30:0176 End *//* TR:SASR30:0315 End */ /* TR:SPMF89:0018 */
         osSetMPUFromISRConfig(idx, osdMPURegionNr_APPLDATA_NOINIT, osdApplDataAreaID); /* TR:SPMF89:01.0077 */
         osSetMPUFromISRConfig(idx, osdMPURegionNr_APPLDATA_INIT, osdApplInitDataAreaID); /* TR:SPMF89:01.0079 */
         osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA4, osdArea4ID);      /* TR:SPMF89:01.0078 */
         osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA6, osdArea6ID);      /* TR:SPMF89:01.0080 */
         osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA8, osdArea8ID);      /* TR:SPMF89:01.0082 */
         osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA9, osdArea9ID);      /* TR:SPMF89:01.0083 */
         osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA10, osdArea10ID);    /* TR:SPMF89:01.0084 */
         osSetMPUFromISRConfig(idx, osdMPURegionNr_AREA11, osdArea11ID);    /* TR:SPMF89:01.0085 */     
         osMPUEnable();
      }
      ELSEWITHCOVER(0x0465)
     /* TR:SASR30:0034 End */ /* TR:SASR30:0323 End *//* TR:SASR30:0177 End *//* TR:SASR30:0069 End *//* TR:SASR30:0073 End */
   }
   ELSEWITHCOVER(0x0466)
   if (((osuint8*)(OSCFGBLOCK->uiStartAddressISRTrusted))[idx] == 0)
   {
      COVER(0x0467)
      return 0;
   }
   ELSEWITHCOVER(0x0468)
   {
      COVER(0x0469)
      return 1;
   }
}


/* MISRA RULE 14.1 not violated: The function osLeaveProtectedISR is called from 
 * assembly language. Typical MISRA checkers are not able to see the call.
 */
void osLeaveProtectedISR(void)     /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osLeaveProtectedISR */

   osuint8 nestLevel;

   COVER(0x046A)
   if (OSCFGBLOCK->uiNumberOfCat2ISRs > 0)
   {  
      COVER(0x046B)
      /* TR:SASR30:0186 Start */
      if (osaIntAPIStatus != 0)
      {
         COVER(0x046C)
         osAPIError(E_OS_DISABLEDINT, osdErrIXIntAPIDisabled);
         osaIntAPIStatus = 0;
         osaIntSaveDisableCounter = 0;
         osaIntSaveDisableCounterGlobal = 0;
      }
      ELSEWITHCOVER(0x046D)
      /* TR:SASR30:0186 End */

      nestLevel = osaIntNestingDepth-1;
      
      osaActiveApplicationID = osaIsrStoredInfo[nestLevel].savedApplID;
      osCurrentContext = osaIsrStoredInfo[nestLevel].prevContext;

      osInSystemFct = osaIsrStoredInfo[nestLevel].InSystemFct;

      /* restore protection registers */
      osMPUDisable();
      osSetupMPURegion(osdMPURegionNr_STACK, osaIsrStoredInfo[nestLevel].reg2start, osaIsrStoredInfo[nestLevel].reg2sizecfg, osdMPUAccessCtrlData);
      osSetupMPURegion(osdMPURegionNr_APPLDATA_NOINIT, osaIsrStoredInfo[nestLevel].reg3start, osaIsrStoredInfo[nestLevel].reg3sizecfg, osdMPUAccessCtrlData);
      osSetupMPURegion(osdMPURegionNr_APPLDATA_INIT, osaIsrStoredInfo[nestLevel].reg5start, osaIsrStoredInfo[nestLevel].reg5sizecfg, osdMPUAccessCtrlData);
      osSetupMPURegion(osdMPURegionNr_AREA4, osaIsrStoredInfo[nestLevel].reg4start, osaIsrStoredInfo[nestLevel].reg4sizecfg, osaIsrStoredInfo[nestLevel].reg4access);
      osSetupMPURegion(osdMPURegionNr_AREA6, osaIsrStoredInfo[nestLevel].reg6start, osaIsrStoredInfo[nestLevel].reg6sizecfg, osaIsrStoredInfo[nestLevel].reg6access);
      osSetupMPURegion(osdMPURegionNr_AREA8, osaIsrStoredInfo[nestLevel].reg8start, osaIsrStoredInfo[nestLevel].reg8sizecfg, osaIsrStoredInfo[nestLevel].reg8access);
      osSetupMPURegion(osdMPURegionNr_AREA9, osaIsrStoredInfo[nestLevel].reg9start, osaIsrStoredInfo[nestLevel].reg9sizecfg, osaIsrStoredInfo[nestLevel].reg9access);
      osSetupMPURegion(osdMPURegionNr_AREA10, osaIsrStoredInfo[nestLevel].reg10start, osaIsrStoredInfo[nestLevel].reg10sizecfg, osaIsrStoredInfo[nestLevel].reg10access);
      osSetupMPURegion(osdMPURegionNr_AREA11, osaIsrStoredInfo[nestLevel].reg11start, osaIsrStoredInfo[nestLevel].reg11sizecfg, osaIsrStoredInfo[nestLevel].reg11access);

      osMPUEnable();
   }
   ELSEWITHCOVER(0x046E)
}

/* nesting level exceeds configured nesting limit */
/* MISRA RULE 14.1 not violated: The function osIntNestingOverflow is called from 
 * assembly language. Typical MISRA checkers are not able to see the call.
 */
void osIntNestingOverflow(void)      /* PRQA S 1503 */ 
{
   /* CovComment 4:  Function: osIntNestingOverflow */
   COVER(0x046F)
   osEnterSafeState(E_OS_SYS_ASSERTION, osdErrNOIntNestingOverflow);
}

/*-+--------------------------------------------------------------------------
 / CallNonTrustedFunction
 / ====================
 /
 / Syntax: StatusType CallNonTrustedFunction (NonTrustedFunctionIndexType FunctionIndex,
 /                                         NonTrustedFunctionParameterRefType FunctionParams)
 / Parameter (In): FunctionIndex: Index of the function to be called. 
 /                 FunctionParams or NULL:
 /                 Pointer to the parameters for the function – specified by
 /                 the FunctionIndex - to be called. If no parameters are
 /                 provided, a NULL pointer has to be passed.
 / Parameter (Out): none
 / Return value: E_OK: No Error 
 /               E_OS_SERVICEID: No function defined for this index.
 / Scalability Classes: SC3, SC4
 /--------------------------------------------------------------------------*/
osqFunc1 StatusType osqFunc2 osCallNonTrustedFunction(NonTrustedFunctionIndexType FunctionIndex,
                                                   NonTrustedFunctionParameterRefType FunctionParams)
{
   /* CovComment 4:  Function: osCallNonTrustedFunction */

   /* TR:SPMF89:01.0048 Start */
   osuint32 newStackPtr;
   ApplicationType savedApplicationID;
   osuint32 idx;
   ApplicationType appl;
   osuint32 *mPtr;
   
   osuint32 sreg2start;
   osuint32 sreg2sizecfg;
   osuint32 sreg3start;
   osuint32 sreg3sizecfg;
   osuint32 sreg4start;
   osuint32 sreg4sizecfg;
   osuint32 sreg4access;
   osuint32 sreg5start;
   osuint32 sreg5sizecfg;
   osuint32 sreg6start;
   osuint32 sreg6sizecfg;
   osuint32 sreg6access;
   osuint32 sreg8start;
   osuint32 sreg8sizecfg;
   osuint32 sreg8access;
   osuint32 sreg9start;
   osuint32 sreg9sizecfg;
   osuint32 sreg9access;
   osuint32 sreg10start;
   osuint32 sreg10sizecfg;
   osuint32 sreg10access;
   osuint32 sreg11start;
   osuint32 sreg11sizecfg;
   osuint32 sreg11access;

   COVER(0x0470)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in CallNonTrustedFunction  */
   /* TR:SASR30:0336 Start Context check in CallNonTrustedFunction  */
   if ((osdValidCtx_CallNonTrustedFunction & osCurrentContext) == 0)
   {
      COVER(0x0471)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osAPIError(E_OS_CALLEVEL, osdErrNTCallContext);
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      return E_OS_CALLEVEL;
   }
   ELSEWITHCOVER(0x0472)
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   /* TR:SASR30:0038 Start Check disabled interrupts in CallNonTrustedFunction */
   if (osaIntAPIStatus != 0)  
   {
      COVER(0x0473)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osAPIError(E_OS_DISABLEDINT, osdErrNTIntAPIDisabled);
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   ELSEWITHCOVER(0x0474)
   /* TR:SASR30:0038 End */

   if (FunctionIndex >= OSCFGBLOCK->uiNumberOfNonTrustedFunctions)
   {
      COVER(0x0475)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osAPIError(E_OS_SERVICEID, osdErrNTWrongFctIdx);
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      return E_OS_SERVICEID;
   }
   ELSEWITHCOVER(0x0476)
   
   osSaveDisableLevelNested();
   
   savedApplicationID = osaActiveApplicationID;
   osaActiveApplicationID = ((osuint8*)(OSCFGBLOCK->uiStartAddressNonTrustedFctToAppl))[FunctionIndex];
   
   /* TR:SPMF89:0020 Start */
   osMPUDisable();
   osStoreRegionSettings(osdMPURegionNr_STACK, &sreg2start, &sreg2sizecfg, 0);
   osStoreRegionSettings(osdMPURegionNr_APPLDATA_NOINIT, &sreg3start, &sreg3sizecfg, 0);
   osStoreRegionSettings(osdMPURegionNr_APPLDATA_INIT, &sreg5start, &sreg5sizecfg, 0);
   osStoreRegionSettings(osdMPURegionNr_AREA4, &sreg4start, &sreg4sizecfg, &sreg4access);
   osStoreRegionSettings(osdMPURegionNr_AREA6, &sreg6start, &sreg6sizecfg, &sreg6access);
   osStoreRegionSettings(osdMPURegionNr_AREA8, &sreg8start, &sreg8sizecfg, &sreg8access);
   osStoreRegionSettings(osdMPURegionNr_AREA9, &sreg9start, &sreg9sizecfg, &sreg9access);
   osStoreRegionSettings(osdMPURegionNr_AREA10, &sreg10start, &sreg10sizecfg, &sreg10access);
   osStoreRegionSettings(osdMPURegionNr_AREA11, &sreg11start, &sreg11sizecfg, &sreg11access);

   if (osaIntNestingDepth == 0)
   {
      COVER(0x0477)
      idx = osaActiveTaskIndex;
      osSetupMPURegion(osdMPURegionNr_STACK, 
                       ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFTaskStackMPUSetting))[idx].aulMPUSectionStartAddress, 
                       ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFTaskStackMPUSetting))[idx].aulMPUSectionSize, 
                       ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFTaskStackMPUSetting))[idx].aulMPUSectionAccess);

      if (osaTcbNTFNestingDepth[osaActiveTaskIndex] == 0)
      { /* first nesting level, switch to NTF stack */
        COVER(0x0478)
         newStackPtr = ((osuint32*)(OSCFGBLOCK->uiStartAddressNTFTaskStackEndAddress))[idx];        
      }
      else
      {
         COVER(0x0479)
         newStackPtr = 0;
      }     
   }
   else
   {
      COVER(0x047A)
      idx = osaActiveISRID;
      
      osSetupMPURegion(osdMPURegionNr_STACK, 
                       ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFISRStackMPUSetting))[idx].aulMPUSectionStartAddress, 
                       ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFISRStackMPUSetting))[idx].aulMPUSectionSize, 
                       ((tsSingleMPUSetting*)(OSCFGBLOCK->uiStartAddressNTFISRStackMPUSetting))[idx].aulMPUSectionAccess);

      if (osaIcbNTFNestingDepth[osaActiveISRID] == 0)
      { /* first nesting level, switch to NTF stack */
         COVER(0x047B)
         newStackPtr = ((osuint32*)(OSCFGBLOCK->uiStartAddressNTFISRStackEndAddress))[idx];        
      }
      else
      {
         COVER(0x047C)
         newStackPtr = 0;
      }     
   }
   
   COVER(0x047D)
   appl = osaActiveApplicationID;
   osSetMPUFromApplConfig(appl, osdMPURegionNr_APPLDATA_NOINIT, osdApplDataAreaID); /* TR:SPMF89:01.0077 */
   osSetMPUFromApplConfig(appl, osdMPURegionNr_APPLDATA_INIT, osdApplInitDataAreaID); /* TR:SPMF89:01.0079 */
   osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA4, osdArea4ID);     /* TR:SPMF89:01.0078 */
   osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA6, osdArea6ID);     /* TR:SPMF89:01.0080 */
   osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA8, osdArea8ID);     /* TR:SPMF89:01.0082 */
   osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA9, osdArea9ID);     /* TR:SPMF89:01.0083 */
   osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA10, osdArea10ID);   /* TR:SPMF89:01.0084 */
   osSetMPUFromApplConfig(appl, osdMPURegionNr_AREA11, osdArea11ID);   /* TR:SPMF89:01.0085 */
   osMPUEnable();
   /* TR:SPMF89:0020 End */
   
   osInSystemFct++;
   if (osaIntNestingDepth == 0)
   {
      COVER(0x047E)
      osaTcbNTFNestingDepth[osaActiveTaskIndex]++;
   }
   else
   {
      COVER(0x047F)
      osaIcbNTFNestingDepth[osaActiveISRID]++;
   }
   osRestoreEnableLevelNested();
   osCallNTF(FunctionIndex, FunctionParams, (NonTrustedFunctionType)(((NonTrustedFunctionType*)(OSCFGBLOCK->uiStartAddressNonTrustedFct))[FunctionIndex]), newStackPtr);
   /* TR:SPMF89:01.0048 End */
   /* TR:SPMF89:01.0049 Start */
   osSaveDisableLevelNested();

   if (osaIntNestingDepth == 0)
   {
      COVER(0x0480)
      osaTcbNTFNestingDepth[osaActiveTaskIndex]--;
      mPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressNTFTaskStackStartAddress))[osaActiveTaskIndex]);   /* get first word of current stack */
   }
   else
   {
      COVER(0x0481)
      osaIcbNTFNestingDepth[osaActiveISRID]--;
      mPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressNTFISRStackStartAddress))[osaActiveISRID]);   /* get first word of current stack */
   }
   if ((*mPtr != 0xAAAAaaaaUL))
   {
      COVER(0x0482)
      osStackOverflow();
   }
   ELSEWITHCOVER(0x0483)
   osInSystemFct--;
   osaActiveApplicationID = savedApplicationID;

   /* restore protection registers */
   osMPUDisable();
   osSetupMPURegion(osdMPURegionNr_STACK, sreg2start, sreg2sizecfg, osdMPUAccessCtrlData);
   osSetupMPURegion(osdMPURegionNr_APPLDATA_NOINIT, sreg3start, sreg3sizecfg, osdMPUAccessCtrlData);
   osSetupMPURegion(osdMPURegionNr_APPLDATA_INIT, sreg5start, sreg5sizecfg, osdMPUAccessCtrlData);
   osSetupMPURegion(osdMPURegionNr_AREA4, sreg4start, sreg4sizecfg, sreg4access);
   osSetupMPURegion(osdMPURegionNr_AREA6, sreg6start, sreg6sizecfg, sreg6access);
   osSetupMPURegion(osdMPURegionNr_AREA8, sreg8start, sreg8sizecfg, sreg8access);
   osSetupMPURegion(osdMPURegionNr_AREA9, sreg9start, sreg9sizecfg, sreg9access);
   osSetupMPURegion(osdMPURegionNr_AREA10, sreg10start, sreg10sizecfg, sreg10access);
   osSetupMPURegion(osdMPURegionNr_AREA11, sreg11start, sreg11sizecfg, sreg11access);
   osMPUEnable();

   osRestoreEnableLevelNested();

   /* TR:SPMF89:01.0049 End */  
   return E_OK;
} /* END OF osCallNonTrustedFunction */


/*-+--------------------------------------------------------------------------
 / osInitTaskStacks
 / Funktion:
 /   - init the lowest byte of all task stacks with a certain pattern (0xAA)
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 not violated: The function osLeaveProtectedISR is called from 
 * assembly language. Typical MISRA checkers are not able to see the call.
 */
osqFunc1 void osqFunc2 osInitTaskStacks(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osInitTaskStacks */

   osTaskIndexType n;

   COVER(0x0484)
   /* fill task stacks */
   for (n= 0; n < OSCFGBLOCK->uiNumberOfTasks; n++)
   {
      *((osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressTaskStackStartAddress))[n])) = 0xAAAAAAAAUL; /* TR:SPMF07:0008 */
   }
} /* END OF osInitTaskStacks */


/*-+--------------------------------------------------------------------------
 / osFillSystemStack
 / Funktion:
 /   - fill system stack with empty pattern
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 not violated: The function osFillSystemStack is called from 
 * assembly language. Typical MISRA checkers are not able to see the call.
 */
void osFillSystemStack(void)      /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osFillSystemStack */
/* TR:SPMF08:0005 Start */
   osuint32 i;
   osuint32 *intStackPtr;
   osuint32 *endOfStack;
  
   COVER(0x0485)

   /* initialize ISR handler stacks */ 
   for (i=0; i<OSCFGBLOCK->uiNumberOfIRQNestings; i++)
   {
      COVER(0x0486)
      intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressISRStackStart))[i]);
      endOfStack = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressISRStackEnd))[i]);
      while (intStackPtr < endOfStack)
      {
         COVER(0x0487)
         (*intStackPtr) = 0xAAAAAAAAUL;
         intStackPtr++;
      }
   }
      
   /* initialize non-trusted function stacks for tsaks */ 
   for (i=0; i<OSCFGBLOCK->uiNumberOfTasks; i++)
   {
      COVER(0x0488)
      intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressNTFTaskStackStartAddress))[i]);
      endOfStack = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressNTFTaskStackEndAddress))[i]);
      while (intStackPtr < endOfStack)
      {
         COVER(0x0489)
         (*intStackPtr) = 0xAAAAAAAAUL;
         intStackPtr++;
      }
   }
      
   /* initialize non-trusted function stacks for ISRs */ 
   for (i=0; i<OSCFGBLOCK->uiNumberOfCat2ISRs; i++)
   {
      COVER(0x048A)
      intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressNTFISRStackStartAddress))[i]);
      endOfStack = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressNTFISRStackEndAddress))[i]);
      while (intStackPtr < endOfStack)
      {
         COVER(0x048B)
         (*intStackPtr) = 0xAAAAAAAAUL;
         intStackPtr++;
      }
   }
      
   /* initialize abort stack */ 
   intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackStart))[osdSpecialStack_AbortStack]);
   endOfStack = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackEnd))[osdSpecialStack_AbortStack]);
   while (intStackPtr < endOfStack)
   {
      COVER(0x048C)
      (*intStackPtr) = 0xAAAAAAAAUL;
      intStackPtr++;
   }
   
   /* initialize supervisor stack */ 
   intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackStart))[osdSpecialStack_SupervisorStack]);
   endOfStack = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackEnd))[osdSpecialStack_SupervisorStack]);
   while (intStackPtr < endOfStack)
   {
      (*intStackPtr) = 0xAAAAAAAAUL;
      intStackPtr++;
   }
   
   /* initialize API stack */ 
   intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackStart))[osdSpecialStack_APIStack]);
   endOfStack = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackEnd))[osdSpecialStack_APIStack]);
   while (intStackPtr < endOfStack)
   {
      COVER(0x048D)
      (*intStackPtr) = 0xAAAAAAAAUL;
      intStackPtr++;
   }  
} /* TR:SPMF08:0005 End */


/* MISRA RULE 14.1 not violated: The function osInitSystemStack() is called from 
 * assembly language. Typical MISRA checkers are not able to see the call.
 */
void osInitSystemStack(void) /* PRQA S 1503 */ /* TR:SPMF07:0004 Start */
{
   /* CovComment 4:  Function: osInitSystemStack */
   osuint32 i;
   osuint32 *intStackPtr;
   
   COVER(0x048E)

   /* initialize ISR handler stacks */ 
   for (i=0; i<OSCFGBLOCK->uiNumberOfIRQNestings; i++)
   {
      COVER(0x048F)
      intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressISRStackStart))[i]);
      (*intStackPtr) = 0xAAAAAAAAUL;
   }
      
   /* initialize non-trusted function stacks for tsaks */ 
   for (i=0; i<OSCFGBLOCK->uiNumberOfTasks; i++)
   {
      COVER(0x0490)
      intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressNTFTaskStackStartAddress))[i]);
      if(intStackPtr != (osuint32*)0)
      {
         COVER(0x0491)
         (*intStackPtr) = 0xAAAAAAAAUL;
      }
      ELSEWITHCOVER(0x0492)
}
      
   /* initialize non-trusted function stacks for ISRs */ 
   for (i=0; i<OSCFGBLOCK->uiNumberOfCat2ISRs; i++)
   {
      COVER(0x0493)
      intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressNTFISRStackStartAddress))[i]);
      if(intStackPtr != (osuint32*)0)
      {
         COVER(0x0494)
         (*intStackPtr) = 0xAAAAAAAAUL;
      }
      ELSEWITHCOVER(0x0495)
  }
      
   /* initialize abort stack */ 
   intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackStart))[osdSpecialStack_AbortStack]);
   (*intStackPtr) = 0xAAAAAAAAUL;
   
   /* initialize supervisor stack */ 
   intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackStart))[osdSpecialStack_SupervisorStack]);
   (*intStackPtr) = 0xAAAAAAAAUL;
   
   /* initialize API stack */ 
   intStackPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackStart))[osdSpecialStack_APIStack]);
   (*intStackPtr) = 0xAAAAAAAAUL;
} /* TR:SPMF07:0004 End */


/*-+--------------------------------------------------------------------------
 / osGetSupervisorStackUsage
 / Funktion:
 /   - calculate maximum supervisor stack usage
 / Parameter:
 / Returnvalue: calculated stack usage (in byte)
 /--------------------------------------------------------------------------*/
/* TR:SPMF89:0002 Start */
osqFunc1 osStackUsageType osqFunc2 osGetSupervisorStackUsage(void)
{
   /* CovComment 4:  Function: osGetSupervisorStackUsage */
   osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *stack;

   COVER(0x0496)
   stack = (osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackStart))[osdSpecialStack_SupervisorStack]);

   while ((stack < (osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackEnd))[osdSpecialStack_SupervisorStack])) && (*stack == 0xAA))
   {
      COVER(0x0497)
      stack++;
   }
   return (osStackUsageType)((osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackEnd))[osdSpecialStack_SupervisorStack]) - stack);
} /* end of osGetSupervisorStackUsage */
/* TR:SPMF89:0002 End */

/*-+--------------------------------------------------------------------------
 / osGetAPIStackUsage
 / Funktion:
 /   - calculate maximum supervisor stack usage
 / Parameter:
 / Returnvalue: calculated stack usage (in byte)
 /--------------------------------------------------------------------------*/
osqFunc1 osStackUsageType osqFunc2 osGetAPIStackUsage(void)
{
   /* CovComment 4:  Function: osGetAPIStackUsage */
   osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *stack;

   COVER(0x0498)
   stack = (osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackStart))[osdSpecialStack_APIStack]);

   while ((stack < (osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackEnd))[osdSpecialStack_APIStack])) && (*stack == 0xAA))
   {
      COVER(0x0499)
      stack++;
   }
   return (osStackUsageType)((osqPRAM1 osqPRAM2 osuint8 osqPRAM3 *)(((osuint32*)(OSCFGBLOCK->uiStartAddressSpecStackEnd))[osdSpecialStack_APIStack]) - stack);
} /* end of osGetAPIStackUsage */


/*-+--------------------------------------------------------------------------
 / osSystemStackOverflow
 / Funktion:
 /   - called on system stack overflow: abort system
 / Parameter: osuint16 cause Error code
 / Returnvalue:
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 not violated: The function osSystemStackOverflow() is called from 
 * assembly language. Typical MISRA checkers are not able to see the call.
 */
/* TR:SASR30:0025 Start */
void osSystemStackOverflow(osuint16 cause)      /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osSystemStackOverflow */

   ProtectionReturnType proRet;
   
   COVER(0x049A)
   osDisableGlobal();

   osLastError = cause; 

   proRet = osProtectionHookWrapper(E_OS_STACKFAULT); /* TR:SASR30:0204 *//* TR:SASR30:0077 */
   osHandleProtectionErrors(proRet, E_OS_STACKFAULT);

   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. */    
   osdDummyRead(cause) /* PRQA S 3199 */
}
/* TR:SASR30:0025 End */

/* MISRA RULE 14.1 not violated: The function osPeripheralError() is called from 
 * assembly language. Typical MISRA checkers are not able to see the call.
 */
/* TR:SASR30:0031 Start */
void osPeripheralError(void) /* PRQA S 1503 */
{ 
   /* CovComment 4:  Function: osPeripheralError */

   osuint16 savedContext;
   StatusType proCause;
   ProtectionReturnType proRet;

   COVER(0x049B)
   proCause = E_OS_PROTECTION_PERIPHERAL; /* TR:SPMF95:0012 */

   savedContext = osCurrentContext;
   osCurrentContext = osdCtxProtectionHook;
   proRet = osProtectionHookWrapper(proCause);/* TR:SASR30:0077 */
   osCurrentContext = savedContext;
   osHandleProtectionErrors(proRet, proCause);
}
/* TR:SASR30:0031 End */


static osqFunc1 osuint8 osqFunc2 osProtectionTrapHandler(void);

static osqFunc1 osuint8 osqFunc2 osProtectionTrapHandler(void)
{
   /* CovComment 4:  Function: osProtectionTrapHandler */
   ProtectionReturnType proRet;
   osuint16 savedContext;
   StatusType proCause;

   COVER(0x049C)
   proCause = E_OS_PROTECTION_MEMORY; /* TR:SASR30:0014 */

   savedContext = osCurrentContext;
   osCurrentContext = osdCtxProtectionHook;
   proRet = osProtectionHookWrapper(proCause); /* TR:SASR30:0014 *//* TR:SASR30:0077 */
   osCurrentContext = savedContext;
   osHandleProtectionErrors(proRet, proCause);
   
   return 1;
}

/* memory protection error */
/* MISRA RULE 14.1 not violated: The function osProtectionTrap is called from assembly language.
 * Therefore typical MISRA checkers are  not able to see the call and complain.
 */
osqFunc1 osuint8 osqFunc2 osProtectionTrap(void)   /* PRQA S 1503 */   
{
   /* CovComment 4:  Function: osProtectionTrap */

   COVER(0x049D)
   return osProtectionTrapHandler();
}

/* KB end osekHWSctxCode */
