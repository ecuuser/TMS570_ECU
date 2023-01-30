/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osekrsrc.c
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.67
|
|  Description: osek API-functions for handling resources
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
/* TR:SOSK22:0084 Start */
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

/* CovComment 0:  file: osekrsrc.c */

/* KB begin osekStartOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_CODE_SECTION(".oscode") /* TR:SPMF49:0001 */ /* TR:SPMF49:0002 */
#endif
/* KB end osekStartOfCModule */
/* TR:SOSK22:0049 Start */
/* TR:SOSK22:0095 Start */
/*-+--------------------------------------------------------------------------
 / GetResource
 / ===========
 /
 / Syntax:          StatusType GetResource ( ResourceType <ResID> )
 / Parameter (In):  ResID Reference to resource
 / Parameter (Out): none
 / Description:     This call serves to enter critical sections in the code 
 /                  that are assigned to the resource referenced by <ResID>. 
 /                  A critical section must always be left using 
 /                  ReleaseResource.
 / Particularities: Nested resource occupation is only allowed if the 
 /                  inner critical sections are completely executed within 
 /                  the surrounding critical section. Occupation of an already
 /                  occupied resource is also strictly forbidden!
 /                  Corresponding calls to GetResource and ReleaseResource
 /                  should appear within the same function on the same function
 /                  level.
 /                  Services which are points of rescheduling for non preemptable
 /                  tasks (TerminateTask, ChainTask, Schedule and WaitEvent,
 /                  must not be used in critical sections.
 /                  Additionally, critical sections must be left before 
 /                  completion of an interrupt service routine.
 /                  Generally speaking, critical sections should be short.
 /                  The service may be called from an ISR and from task level.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Resource <ResID> is invalid, E_OS_ID
 /                  - Attempt to get resource which is already occupied by any 
 /                    task or ISR, or the statically assigned priority of the
 /                    calling task or interrupt routine is higher than the 
 /                    calculated ceiling priority, E_OS_ACCESS
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, Cat2-ISR, interrupts not disabled by the application
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/GetResource.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
/* TR:SOSK22:0083 Start */
/* TR:SOSK22:0269 Start */
/* TR:SOSK22:0270 Start */
osqFunc1 StatusType osqFunc2 osGetResource(ResourceType ResId) /* PRQA S 1503 */ /* TR:SOSK22:0191 */
{
#if ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0)

   /* CovComment 4:  Function: osGetResource */
   /* KB begin osekHWosGRLocalCeilingPrioDecl (default) */
   osPrioType ceilingPrio; /* task priority or interrupt level depending on type of resource */ /* TR:SOSK22:0093 */
   /* KB end osekHWosGRLocalCeilingPrioDecl */
#if (osdNumberOfInterruptResources > 0)
   /* KB begin osekHWosGRLocalLevelDecl (default) */
   osIntLevelType currentLevel;
   /* KB end osekHWosGRLocalLevelDecl */
#endif

   OS_GR_ENTRY()

   COVER(0x0193)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in GetResource */
   /* TR:SASR30:0336 Start Context check in GetResource */
   if ((osdValidCtx_GetResource & osCurrentContext) == 0)
   {
      COVER(0x0194)
      osSaveGetResource_ResID(ResId)
      osAPIError(E_OS_CALLEVEL, osdErrGRCallContext);
      OS_GR_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x0195)

   if ((ResId >= osrNumberOfAllResources)  
 #if osdNumberOfInternalResources>0
  #if (osdNumberOfTaskResources != osdNumberOfAllResources) /* just keep lint happy! */
       /* if osrNumberOfTaskResources == osrNumberOfAllResources the sub-condition below 
        * causes lint to expect ResId might be >= osrNumberOfAllResources in the main 
        * part of the function and therfore out of bound array accesses might occur. 
        * Anyhow, the sub-condition above guarantees that this is detected, an error 
        * message is send and the function returns, so that no out of bounds array
        * accesses can ever occur.*/
       ||  (((ResId < osrNumberOfTaskResources)
   #if  (((osdNumberOfTaskResources - osdNumberOfInternalResources) > 0) || osdLib)
               &&  (ResId >= (osrNumberOfTaskResources - osrNumberOfInternalResources))
   #endif
           ))
  #else /* the lint preprocessor if */
   #if  (((osdNumberOfTaskResources - osdNumberOfInternalResources) > 0) || osdLib)
               ||  (ResId >= (osrNumberOfTaskResources - osrNumberOfInternalResources))
   #endif /* osdNumberOfTaskResources - ... */
  #endif /* the lint preprocessor if */
 #endif /* osdNumberOfInternalResources>0 */
      )
   {
#endif /* ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) */
      COVER(0x0196)
      osSaveGetResource_ResID(ResId)
      osAPIError(E_OS_ID, osdErrGRWrongResourceID);
      OS_GR_EXIT()
      /* osdDummyRead might intentionally assign a value to an unused variable on 
       * some platforms to avoid compiler warnings. This is no MISRA error. (3199) */
      osdDummyRead(ResId) /* PRQA S 3199 */
      return  E_OS_ID;  /* TR:SOSK22:0273 */
/* TR:SOSK22:0096 Start */
#if ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0)
   }
   ELSEWITHCOVER(0x0197)

   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in GetResource */
   if (((oskApplResourceAccess[ResId] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x0198)
      osSaveGetResource_ResID(ResId)
      osAPIError(E_OS_ACCESS, osdErrGRNoAccess);
      OS_GR_EXIT()
      return E_OS_ACCESS; 
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x0199)
   /* TR:SASR30:0038 Start Check disabled interrupts in GetResource */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x019A)
      osSaveGetResource_ResID(ResId)
      osAPIError(E_OS_DISABLEDINT, osdErrGRIntAPIDisabled);
      OS_GR_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x019B)

   /* checks if resource is already occupied */
   if (osResOccupationCounter[ResId] != 0)/* TR:SOSK22:0082 */ /* TR:SOSK22:0086 */ /* TR:SOSK22:0090 */
   {
      COVER(0x019C)
      osSaveGetResource_ResID(ResId)
      osAPIError(E_OS_ACCESS, osdErrGRResourceOccupied);
      OS_GR_EXIT()
      return  E_OS_ACCESS; /* TR:SOSK22:0274 */
   }
   ELSEWITHCOVER(0x019D)


   /* KB begin osekHWosGRCeilingPrioAssignment (default) */
   COVER(0x019E)
   ceilingPrio= oskResCeilingPrio[ResId]; /* TR:SOSK22:0093 */
   /* KB end osekHWosGRCeilingPrioAssignment */

#if (osdNumberOfInterruptResources > 0)

 #if (osdNumberOfTaskResources > 0)
   if(ResId>=osrNumberOfTaskResources)
   {
      COVER(0x019F)
 #else
   COVER(0x01A0)
 #endif /* (osdNumberOfTaskResources > 0) */
      /* switch to higher processing level */
      #if STATUS_LEVEL == EXTENDED_STATUS
      COVER(0x01A1)
      /* KB begin osekHWosGRCompareIntLevel (overwritten) */
      /* KB end osekHWosGRCompareIntLevel */

      #endif /* STATUS_LEVEL == EXTENDED_STATUS */

      /* KB begin osekHWosSaveCurrentLevelLocal (default) */
      COVER(0x01A2)
      currentLevel = osGetLevel();
      /* KB end osekHWosSaveCurrentLevelLocal */

      /* KB begin osekHWosDisableTimProtInterrupt (default) */
      #if osdTimingProtectionUsed
      #error "Timing Protection not supported"
      #endif        
      /* KB end osekHWosDisableTimProtInterrupt */

      #if osdTimingProtectionUsed
      COVER(0x01A3)
      osTPStartTimerBlock(ResId);
      #endif /* osdTimingProtectionUsed */

      /* KB begin osekHWosSaveCurrentLevelGlobal (default) */
      COVER(0x01A4)
      osResSavedPrio[ResId] = (osPrioType)currentLevel;
      /* KB end osekHWosSaveCurrentLevelGlobal */

      /* KB begin osekIncDispatcherLock (default) */
         COVER(0x01A5)
         osLockDispatcher++; /* TR:SOSK22:0004 */
      /* KB end osekIncDispatcherLock */      
      #if STATUS_LEVEL == EXTENDED_STATUS
      COVER(0x01A6)
      osResGlobalOccupationCounter++;
      osResOccupationCounter[ResId] = osResGlobalOccupationCounter;   /* TR:SOSK22:0090 */
      #endif /* STATUS_LEVEL == EXTENDED_STATUS */

      #if STATUS_LEVEL == EXTENDED_STATUS
      /* counter needed only for mixed resource system (task, interrupt and internal) */
      
      /* increment counter only if task is accessing */
      if (osaIntNestingDepth == 0)
      {
         COVER(0x01A7)
         osTcbResourceCounter[osaActiveTaskIndex]++;
      }
      ELSEWITHCOVER(0x01A8)
      #endif /* STATUS_LEVEL == EXTENDED_STATUS */
   

      #if osdORTIDebug
      if (osaIntNestingDepth == 0)
      {
         COVER(0x01A9)
         /* save taskindex */
         osResActualTask[ResId]= osaActiveTaskIndex;
      }
      ELSEWITHCOVER(0x01AA)
      #endif /* osdORTIDebug */

 #if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
      COVER(0x01AB)
      if (osaIntNestingDepth == 0)
      {    /* Called from task level */
           COVER(0x01AC)
           /* link all previously locked resources to new one */
           osResNextLockedResource[ResId] = osTcbLockedResource[osaActiveTaskIndex];
           /* new one is the last locked resource */
           osTcbLockedResource[osaActiveTaskIndex] = ResId;
      }
      else
      {    /* Called from ISR level */
           COVER(0x01AD)
           /* link all previously locked resources to new one */
           osResNextLockedResource[ResId] = osIcbLockedResource[osaActiveISRID];
           /* new one is the last locked resource */
           osIcbLockedResource[osaActiveISRID] = ResId;
      }
 #endif /* (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4)) */

      COVER(0x01AE)
      /* KB begin osekHWosEnableTimProtInterrupt (default) */
      #if osdTimingProtectionUsed
      #error "Timing Protection not supported"
      #endif        
      /* KB end osekHWosEnableTimProtInterrupt */
      OS_GR_END_CRITICAL()
      /* KB begin osekHWosSetCeilingLevel (default) */
      /* set level if ceiling level is above current level */
      if(currentLevel < (osIntLevelType)ceilingPrio)
      {
         COVER(0x01AF)
         osSetLevel((osIntLevelType)ceilingPrio);
      }
      else
      {
         COVER(0x01B0)
         osSetLevel(currentLevel);
      }
      /* KB end osekHWosSetCeilingLevel */      
 #if (osdNumberOfTaskResources > 0) 
   }
   else
   {
      COVER(0x01B1)
      /* stay on task level - business as usual */
      
 #endif /* (osdNumberOfTaskResources > 0) */
#endif /* (osdNumberOfInterruptResources > 0) */

#if (osdNumberOfTaskResources > 0)

 #if STATUS_LEVEL == EXTENDED_STATUS
      if (osaIntNestingDepth != 0)
      {
         COVER(0x01B2)
         osSaveGetResource_ResID(ResId)
         osAPIError(E_OS_ACCESS, osdErrGRISRNoAccessRights);
         OS_GR_EXIT()
         return E_OS_ACCESS; 
      }
      ELSEWITHCOVER(0x01B3)
      /* TR:SOSK22:0081 Start */
      if (oskTcbHomePrio[osaActiveTaskIndex] < ceilingPrio)
      {
         COVER(0x01B4)
         osSaveGetResource_ResID(ResId)
         osAPIError(E_OS_ACCESS, osdErrGRWrongPrio);
         OS_GR_EXIT()
         return  E_OS_ACCESS;  /* TR:SOSK22:0275 */
      } /* TR:SOSK22:0081 End */
      ELSEWITHCOVER(0x01B5)

   COVER(0x01B6)
   #if !osdLib
   COVER(0x01B7)
      /* checks access-rights of the task */
      if ((oskResAccessMask[ResId][osaActiveTaskIndex/osdResAccessMaskBits] &
           ((((osResAccessMaskType)1U) << (osdResAccessMaskBits-1U)) >> 
            (osuint8)(osaActiveTaskIndex % osdResAccessMaskBits))) == 0U)
      {
         COVER(0x01B8)
         osSaveGetResource_ResID(ResId)
         osAPIError(E_OS_SYS_API_ERROR, osdErrGRNoAccessRights); /* TR:SPMF12:0009 */
         OS_GR_EXIT()
         return  E_OS_SYS_API_ERROR;
      }
      ELSEWITHCOVER(0x01B9)
   #else /* osdLib */
   {
      const osResAccessMaskType *maskPtr;
      osResAccessMaskType mask;

      COVER(0x01BA)
      maskPtr= &oskResAccessMask[0][0];
      maskPtr+= ResId * (((osrNumberOfAllTasks-1)/osdResAccessMaskBits)+1)
                + osaActiveTaskIndex/osdResAccessMaskBits;

      mask= *maskPtr;
      if ((mask & ((((osResAccessMaskType)1U) << (osdResAccessMaskBits-1U)) >> 
                   (osuint8)(osaActiveTaskIndex % osdResAccessMaskBits))) == 0)
      {
         COVER(0x01BB)
         osSaveGetResource_ResID(ResId)
         osAPIError(E_OS_SYS_API_ERROR, osdErrGRNoAccessRights); /* TR:SPMF12:0010 */
         OS_GR_EXIT()
         return  E_OS_SYS_API_ERROR;
      }
      ELSEWITHCOVER(0x01BC)
   }
   #endif /* osdLib */

 #else /* STATUS_LEVEL == STANDARD_STATUS */
   if (osaIntNestingDepth != 0)
   {
      COVER(0x01BD)
      return E_OK; /* TR:SOSK22:0272 */
   }
   ELSEWITHCOVER(0x01BE)
 #endif /* STANDARD_STATUS */

   /* next assertion checks if there is no bit set in the ready bits */
 #if osdRTSize == 1
   COVER(0x01BF)
   osSysErrAssert(((osQReadyPrios & oskResCeilingPrioMask[ResId]) == 0U), osdErrGRPriorityOccupied)
 #else /* osdRTSize == 0 */
   COVER(0x01C0)
   osSysErrAssert(((osQReadyPrios[oskResCeilingPrioOffset[ResId]] & 
                    oskResCeilingPrioMask[ResId]) == 0U), osdErrGRPriorityOccupied)  /* NOCOV */
 #endif /* osdRTSize == 1 */

   COVER(0x01C1)
   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */

   #if osdTimingProtectionUsed
   COVER(0x01C2)
   osTPStartTimerBlock(ResId);
   #endif /* osdTimingProtectionUsed */
/* TR:SOSK22:0091 Start */
 #if (CC==BCC2) || (CC==ECC2)
   COVER(0x01C3)
   oskQActivationQueues[ceilingPrio][0]= osaActiveTaskIndex;
 #else /* BCC1 || ECC1 */
   COVER(0x01C4)
   osQReadyTask[ceilingPrio]= osaActiveTaskIndex;
 #endif /* (CC==BCC2) || (CC==ECC2) */

   osResSavedPrio[ResId]= osActiveTaskPrio;  /* TR:SOSK22:0094 */
   /* TR:SOSK22:0093 Start */
   if (ceilingPrio < osActiveTaskPrio)
   {
      COVER(0x01C5)
      osActiveTaskPrio= ceilingPrio;
   }
   ELSEWITHCOVER(0x01C6)

   if (ceilingPrio < osHighReadyTaskPrio)
   {
      COVER(0x01C7)
      osHighReadyTaskPrio = ceilingPrio;
      osHighReadyTaskIndex = osaActiveTaskIndex;
   } /* TR:SOSK22:0093 End */
   ELSEWITHCOVER(0x01C8)

 #if osdORTIDebug
   COVER(0x01C9)
   osTcbActualPrio[osaActiveTaskIndex]=osActiveTaskPrio;
 #endif /* osdORTIDebug */
/* TR:SOSK22:0091 End */
 #if osdRTSize == 1
   COVER(0x01CA)
   osQReadyPrios |= oskResCeilingPrioMask[ResId];
 #else /* osdRTSize == 0 */
   COVER(0x01CB)
   osQReadyPrios[oskResCeilingPrioOffset[ResId]] |= oskResCeilingPrioMask[ResId];
 #endif /* osdRTSize == 1 */

 #if STATUS_LEVEL == EXTENDED_STATUS
   COVER(0x01CC)
   #if (osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0)
   COVER(0x01CD)
   /* counter needed only for mixed resource system (task, interrupt and internal) */
   
   /* osaIntNestingDepth == 0 is assured by code above (ESOS00003402) */
   osTcbResourceCounter[osaActiveTaskIndex]++;


   #endif /* (osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0) */

   osResGlobalOccupationCounter++;
 #endif /* STATUS_LEVEL == EXTENDED_STATUS */

 #if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
   COVER(0x01CE)
   /* link all previously locked resources to new one */
   osResNextLockedResource[ResId] = osTcbLockedResource[osaActiveTaskIndex];
   /* new one is the last locked resource */
   osTcbLockedResource[osaActiveTaskIndex] = ResId;
 #endif /* (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4)) */

   COVER(0x01CF)
   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */

 #if ((STATUS_LEVEL == EXTENDED_STATUS) && osdEnableAssertions) || osdORTIDebug
   COVER(0x01D0)
   osResActualTask[ResId]= osaActiveTaskIndex;
 #endif /* ((STATUS_LEVEL == EXTENDED_STATUS) && osdEnableAssertions) || osdORTIDebug */
 #if STATUS_LEVEL == EXTENDED_STATUS
   COVER(0x01D1)
   osResOccupationCounter[ResId]= osResGlobalOccupationCounter;  /* TR:SOSK22:0090 */
 #endif /* STATUS_LEVEL == EXTENDED_STATUS */

 #if (osdNumberOfInterruptResources > 0)

   }
      
 #endif /* (osdNumberOfInterruptResources > 0) */
#endif /* (osdNumberOfTaskResources > 0) */

   COVER(0x01D2)
   OS_GR_EXIT()
   return E_OK; /* TR:SOSK22:0272 */

#endif /* ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) */ /* TR:SOSK22:0096 End */

} /* END OF osGetResource */ /* TR:SOSK22:0049 End */ /* TR:SOSK22:0095 End */ 
                             /* TR:SOSK22:0269 End */ /* TR:SOSK22:0270 End */  

/* TR:SOSK22:0057 Start */
/* TR:SOSK22:0095 Start */
/*-+--------------------------------------------------------------------------
 / ReleaseResource
 / ===============
 /
 / Syntax:          StatusType ReleaseResource ( ResourceType <ResID> )
 / Parameter (In):  ResID Reference to resource
 / Parameter (Out): none
 / Description:     ReleaseResource is the counterpart of GetResource and
 /                  serves to leave critical sections in the code that are 
 /                  assigned to the resource referenced by <ResID>.
 / Particularities: Resources have to be released in the opposit order of
 /                  occupation.  
 /                  Corresponding calls to GetResource and ReleaseResource
 /                  should appear within the same function on the same function
 /                  level.
 /                  Services which are points of rescheduling for non preemptable
 /                  tasks (TerminateTask, ChainTask, Schedule and WaitEvent,
 /                  must not be used in critical sections.
 /                  Additionally, critical sections must be left before 
 /                  completion of an interrupt service routine.
 /                  Generally speaking, critical sections should be short.
 /                  The service may be called from an ISR and from task level.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Resource <ResID> is invalid, E_OS_ID
 /                  - Attempt to release a resource which is not occupied by 
 /                    any task or ISR, or another resource has to be released 
 /                    before, E_OS_NOFUNC
 /                  - Attempt to release a resource which has a lower ceiling 
 /                    priority than the statically assigned priority of the 
 /                    calling task or interrupt servide routine, E_OS_ACCESS
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, Cat2-ISR, interrupts not disabled by the application
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 violated: (comment 1503) The API function may be switched off 
 * by the OS configuration parameter OS/APIOptimization/Manual/ReleaseResource.
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and must exist, even if they are not 
 * used in a project. 
 */
osqFunc1 StatusType osqFunc2 osReleaseResource(ResourceType ResId) /* PRQA S 1503 */  /* TR:SOSK22:0192 */
{
#if ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0)
   /* CovComment 4:  Function: osReleaseResource */
   OS_RR_ENTRY()
   COVER(0x01D3)

   /* check call context */
   /* TR:SASR30:0035 Start Context check in ReleaseResource */
   /* TR:SASR30:0336 Start Context check in ReleaseResource */
   if ((osdValidCtx_ReleaseResource & osCurrentContext) == 0)
   {
      COVER(0x01D4)
      osSaveReleaseResource_ResID(ResId)
      osAPIError(E_OS_CALLEVEL, osdErrRRCallContext);
      OS_RR_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x01D5)

   if ((ResId >= osrNumberOfAllResources)  
#if osdNumberOfInternalResources>0
#if (osdNumberOfTaskResources != osdNumberOfAllResources) /* just keep lint happy! */
       /* if osrNumberOfTaskResources == osrNumberOfAllResources the sub-condition below 
        * causes lint to expect ResId might be >= osrNumberOfAllResources in the main 
        * part of the function and therfore out of bound array accesses might occur. 
        * Anyhow, the sub-condition above guarantees that this is detected, an error 
        * message is send and the function returns, so that no out of bounds array
        * accesses can ever occur.*/
       ||  (((ResId < osrNumberOfTaskResources)
#if  (((osdNumberOfTaskResources - osdNumberOfInternalResources) > 0) || osdLib)
               &&  (ResId >= (osrNumberOfTaskResources - osrNumberOfInternalResources))
#endif
           ))
#else /* the lint preprocessor if */
#if  (((osdNumberOfTaskResources - osdNumberOfInternalResources) > 0) || osdLib)
               ||  (ResId >= (osrNumberOfTaskResources - osrNumberOfInternalResources))
#endif /* osdNumberOfTaskResources - ... */
#endif /* the lint preprocessor if */
#endif /* osdNumberOfInternalResources>0 */
      )
   {
#endif /* ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) */
      COVER(0x01D6)
      osSaveReleaseResource_ResID(ResId)
      osAPIError(E_OS_ID, osdErrRRWrongResourceID);
      OS_RR_EXIT()
      /* osdDummyRead might intentionally assign a value to an unused variable on 
       * some platforms to avoid compiler warnings. This is no MISRA error. (3199) */
      osdDummyRead(ResId) /* PRQA S 3199 */
      return  E_OS_ID; /* TR:SOSK22:0279 */
#if ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0)
   }
   ELSEWITHCOVER(0x01D7)

   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in ReleaseResource */
   if (((oskApplResourceAccess[ResId] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x01D8)
      osSaveReleaseResource_ResID(ResId)
      osAPIError(E_OS_ACCESS, osdErrRRNoAccess);
      OS_RR_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x01D9)
   /* TR:SASR30:0038 Start Check disabled interrupts in ReleaseResource */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x01DA)
      osSaveReleaseResource_ResID(ResId)
      osAPIError(E_OS_DISABLEDINT, osdErrRRIntAPIDisabled);
      OS_RR_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x01DB)


   if (osResOccupationCounter[ResId] == 0) /* TR:SOSK22:0082 */  /* TR:SOSK22:0090 */
   {
      COVER(0x01DC)
      osSaveReleaseResource_ResID(ResId)
      osAPIError(E_OS_NOFUNC, osdErrRRNotOccupied);
      OS_RR_EXIT()
      return E_OS_NOFUNC;  /* TR:SOSK22:0280 */
   }
   ELSEWITHCOVER(0x01DD)
   
   if (osResOccupationCounter[ResId] != osResGlobalOccupationCounter)
   {
      COVER(0x01DE)
      osSaveReleaseResource_ResID(ResId)
      osAPIError(E_OS_NOFUNC, osdErrRRWrongSequence);
      OS_RR_EXIT()
      return E_OS_NOFUNC; /* TR:SOSK22:0281 */
   }
   ELSEWITHCOVER(0x01DF)

#if (osdNumberOfInterruptResources > 0)
#if (osdNumberOfTaskResources > 0)
   if(ResId>=osrNumberOfTaskResources)
   {
      COVER(0x01E0)
#else
   COVER(0x01E1)
#endif
      /* switch from higher processing level */
      #if STATUS_LEVEL == EXTENDED_STATUS
      COVER(0x01E2)
      /* KB begin osekHWosRRCompareIntLevel (overwritten) */
      /* KB end osekHWosRRCompareIntLevel */
      #endif

      /* KB begin osekHWosDisableTimProtInterrupt (default) */
      #if osdTimingProtectionUsed
      #error "Timing Protection not supported"
      #endif        
      /* KB end osekHWosDisableTimProtInterrupt */

      #if osdTimingProtectionUsed
      COVER(0x01E3)
      osTPStopTimerBlock(ResId);
      #endif

      /* KB begin osekDecDispatcherLock (default) */
         COVER(0x01E4)
         osLockDispatcher--;
      /* KB end osekDecDispatcherLock */

#if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
      if (osaIntNestingDepth == 0)
      {  /* called from task level */
         COVER(0x01E5)
         /* remove resource from linked list */
         osTcbLockedResource[osaActiveTaskIndex] = osResNextLockedResource[ResId];
      }
      else
      {  /* called from ISR level */
         COVER(0x01E6)
         /* remove resource from linked list */
         osIcbLockedResource[osaActiveISRID] = osResNextLockedResource[ResId];
      }
#endif /* (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4)) */

      #if STATUS_LEVEL == EXTENDED_STATUS
      /* counter needed only for mixed resource system (task, interrupt and internal) */
      
      /* increment counter only if task is accessing */
      if (osaIntNestingDepth == 0)
      {
         COVER(0x01E7)
         osTcbResourceCounter[osaActiveTaskIndex]--;
      }
      ELSEWITHCOVER(0x01E8)

      osResGlobalOccupationCounter--;
      osResOccupationCounter[ResId]= 0; /* TR:SOSK22:0276 */  /* TR:SOSK22:0090 */
      #endif
      
      #if osdORTIDebug
      COVER(0x01E9)
      osResActualTask[ResId]= osdNoActiveTask;
      #endif
      
      #if osdFullPreempt || osdMixedPreempt
      COVER(0x01EA)
      if (osSchedulePrio() != 0)
      {
         COVER(0x01EB)
         /* KB begin osekHWosSetStartDispatcherRR (default) */
         osStartDispatcher=osdTRUE;
         /* KB end osekHWosSetStartDispatcherRR */
      }
      ELSEWITHCOVER(0x01EC)
      #endif

      OS_RR_END_CRITICAL()
      /* KB begin osekHWosEnableTimProtInterrupt (default) */
      #if osdTimingProtectionUsed
      #error "Timing Protection not supported"
      #endif        
      /* KB end osekHWosEnableTimProtInterrupt */
      /* KB begin osekHWosRestoreSavedLevel (default) */
      COVER(0x01ED)
      osSetLevel((osIntLevelType)osResSavedPrio[ResId]);
      /* KB end osekHWosRestoreSavedLevel */      
#if (osdNumberOfTaskResources > 0)
   }
   else
   {
      COVER(0x01EE)
      /* stay on task level - business as usual */
      
#endif
#endif

#if (osdNumberOfTaskResources > 0)
   if (osaIntNestingDepth != 0)
   {
      COVER(0x01EF)
      osSaveReleaseResource_ResID(ResId)
      osAPIError(E_OS_ACCESS, osdErrRRISRNoAccessRights);
      OS_RR_EXIT()
      return E_OS_ACCESS;
   }
   ELSEWITHCOVER(0x01F0)

   if (oskTcbHomePrio[osaActiveTaskIndex] < oskResCeilingPrio[ResId])
   {
      COVER(0x01F1)
      osSaveReleaseResource_ResID(ResId)
      osAPIError(E_OS_ACCESS, osdErrRRWrongPrio);
      OS_RR_EXIT()
      return  E_OS_ACCESS; /* TR:SOSK22:0282 */
   }
   ELSEWITHCOVER(0x01F2)

   COVER(0x01F3)
   /* next assertion checks if releasing task is the same as the occupiing task */
   osSysErrAssert(osResActualTask[ResId] == osaActiveTaskIndex, osdErrRRWrongTask)

   /* next assertion checks if there is a bit set in the ready bits */
#if osdRTSize == 1
   COVER(0x01F4)
   osSysErrAssert(((osQReadyPrios & oskResCeilingPrioMask[ResId]) != 0U), 
      osdErrRRCeilingPriorityNotSet) /* NOCOV */
#else
   COVER(0x01F5)
   osSysErrAssert(((osQReadyPrios[oskResCeilingPrioOffset[ResId]] &
      oskResCeilingPrioMask[ResId]) != 0U), osdErrRRCeilingPriorityNotSet) /* NOCOV */
#endif

   COVER(0x01F6)
   osResActualTask[ResId]= osdNoActiveTask;

   COVER(0x01F7)

   #if (osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0)
   COVER(0x01F8)
   /* counter needed only for mixed resource system (task, interrupt and internal) */
   
   /* decrement counter always, task level is assured by osdErrRRISRNoAccessRights above */
   osTcbResourceCounter[osaActiveTaskIndex]--;
   #endif /* (osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0) */

   osResOccupationCounter[ResId]= 0; /* not occupied */ /* TR:SOSK22:0276 */  /* TR:SOSK22:0090 */
   
   COVER(0x01F9)
   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */

   #if osdTimingProtectionUsed
   COVER(0x01FA)
   osTPStopTimerBlock(ResId);
   #endif
   
#if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
   COVER(0x01FB)
   /* remove resource from linked list */
   osTcbLockedResource[osaActiveTaskIndex] = osResNextLockedResource[ResId];
#endif /* (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4)) */

#if STATUS_LEVEL == EXTENDED_STATUS
   COVER(0x01FC)
   osResGlobalOccupationCounter--;
#endif

   osActiveTaskPrio= osResSavedPrio[ResId]; /* TR:SOSK22:0092 */ /* TR:SOSK22:0094 */ /* TR:SOSK22:0276 */

#if osdORTIDebug
   COVER(0x01FD)
   osTcbActualPrio[osaActiveTaskIndex]=osActiveTaskPrio;
#endif

#if osdRTSize == 1
   COVER(0x01FE)
   osQReadyPrios&= ~oskResCeilingPrioMask[ResId];
#else
   COVER(0x01FF)
   osQReadyPrios[oskResCeilingPrioOffset[ResId]]&= ~oskResCeilingPrioMask[ResId];
#endif


#if osdFullPreempt || osdMixedPreempt
   COVER(0x0200)
   if (osSchedulePrio() != 0)
   {
      COVER(0x0201)
      osStartDispatcher = osdTRUE; /* TR:SOSK22:0057 */
   }
   ELSEWITHCOVER(0x0202)
#endif
   OS_RR_EXIT()

   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */

#if (osdNumberOfInterruptResources > 0)

   }
      
#endif
#endif

   return E_OK;  /* TR:SOSK22:0278 */

#endif /* ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) */

} /* END OF osReleaseResource */ /* TR:SOSK22:0057 End */ /* TR:SOSK22:0095 End */
/* TR:SOSK22:0083 End */


/* TR:SOSK22:0084 End */
/* KB begin osekEndOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
/* Reset to default section TR:SPMF49:0004 */
#pragma SET_CODE_SECTION()
#endif
/* KB end osekEndOfCModule */

/* END OF MODULE osekrsrc.c */
