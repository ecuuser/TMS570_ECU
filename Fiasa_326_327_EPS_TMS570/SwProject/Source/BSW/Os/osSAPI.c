/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osek.c
|
|  Module version: $vv$=1.02
|
|  Description: Safety wrappers for API functions
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2011-2013      Vector Informatik GmbH          All rights reserved.
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

/* CovComment 0:  file: osSAPI.c */

#if defined USE_QUOTE_INCLUDES
 #include "osektype.h"
 #include "oseksctx.h"
 #include "osekqm.h"
 #include "osekcov.h"
 #include "osekerr.h"
#else
 #include <osektype.h>
 #include <oseksctx.h>
 #include <osekqm.h>
 #include <osekcov.h>
 #include <osekerr.h>
#endif


/* MISRA RULE 14.1 not violated: (comment 1503) In SafeContext implementations 
 * all APIs are encapsulated in wrappers. This wrappers belong to static code and must exist,
 * even if they are not used in a project. */
/* MISRA RULE 8.8 violated: (comment 3408) The prototype is created only when necessary in tcb.h.
 * tcb.h must not be included here, so here is no generated code.
 */
/* TR:SASR30:0110 Start */
/* TR:SASR30:0395 Start osPsysCallTrustedFunction */
StatusType osPsysCallTrustedFunction(TrustedFunctionIndexType Param1FunctionIndex,           /* PRQA S 1503 */ /* PRQA S 3408 */
                                     TrustedFunctionParameterRefType Param2FunctionParams) 
{
   /* CovComment 4:  Function: osPsysCallTrustedFunction */

   osuint32 CallerIsTrusted;
   StatusType Status;
   osuint32 *mPtr;

   COVER(0x049E)
   /* check the privilege level of the caller and switch to system mode */
   CallerIsTrusted = osSwitchToPrivMode(); /* TR:SASR30:0111 *//* TR:SASR30:0339 *//* TR:SASR30:0340 */

   /* call the API function */
   Status = osCallTrustedFunction(Param1FunctionIndex, Param2FunctionParams);
   
   /* TR:SPMF89:0031 Start */
   /* perform stack check */
   if (osaIntNestingDepth == 0)
   {  /* we are on task stack */
      COVER(0x049F)
      if (osaTcbNTFNestingDepth[osaActiveTaskIndex] == 0)
      { /* we are on normal task stack */
         COVER(0x04A0)
         mPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressTaskStackStartAddress))[osaActiveTaskIndex]);   /* get first word of current stack */
      }
      else
      {  /* we are on NTF stack for this task */
         COVER(0x04A1)
         mPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressNTFTaskStackStartAddress))[osaActiveTaskIndex]);        
      }           
      if ((*mPtr != 0xAAAAaaaaUL))
      {
         COVER(0x04A2)
         osStackOverflow();
      }
      ELSEWITHCOVER(0x04A3)
   }
   else
   {  /* we are on ISR stack */
      COVER(0x04A4)
      if (osaIcbNTFNestingDepth[osaActiveISRID] == 0)
      {  /* we are on ISR handler stack */
         COVER(0x04A5)
         mPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressISRStackStart))[osaIntNestingDepth]);   /* get first word of current stack */
      }
      else
      {  /* we are on NTF stack for this ISR */
         COVER(0x04A6)
         mPtr = (osuint32*)(((osuint32*)(OSCFGBLOCK->uiStartAddressNTFISRStackStartAddress))[osaActiveISRID]);        
      }     
      if ((*mPtr != 0xAAAAaaaaUL))
      {
         COVER(0x04A7)
         osSystemStackOverflow(osdErrYOIntHdlStackOverflow);
      }
      ELSEWITHCOVER(0x04A8)
   }
   /* TR:SPMF89:0031 End */
     
   /* TR:SASR30:0340 Start Restore privilege of trusted function caller */
   if(CallerIsTrusted == 0)
   {
      COVER(0x04A9)
      osSwitchToUserMode();
   }
   ELSEWITHCOVER(0x04AA)
   /* TR:SASR30:0340 End */
   return Status;
} /* end of osPsysCallTrustedFunction */
/* TR:SASR30:0395 End */
/* TR:SASR30:0110 End */


/* MISRA RULE 14.1 not violated: (comment 1503) In SafeContext implementations 
 * all APIs are encapsulated in wrappers. This wrappers belong to static code and must exist,
 * even if they are not used in a project. */
/* MISRA RULE 8.8 violated: (comment 3408) The prototype is created only when necessary in tcb.h.
 * tcb.h must not be included here, so here is no generated code.
 */
StatusType osPsysCallNonTrustedFunction(NonTrustedFunctionIndexType Param1FunctionIndex,           /* PRQA S 1503 */ /* PRQA S 3408 */
                                        NonTrustedFunctionParameterRefType Param2FunctionParams) 
{
   /* CovComment 4:  Function: osPsysCallNonTrustedFunction */
   /* TR:SPMF89:01.0046 Start */
   osuint32 CallerIsTrusted;
   StatusType Status;

   COVER(0x04AB)
   /* check the privilege level of the caller and switch to system mode */
   CallerIsTrusted = osSwitchToPrivMode();

   /* call the API function */
   
   /* TR:SPMF89:01.0046 End */
   Status = osCallNonTrustedFunction(Param1FunctionIndex, Param2FunctionParams);
   
   /* TR:SPMF89:01.0047 Start */
   if(CallerIsTrusted == 0)
   {
      COVER(0x04AC)
      osSwitchToUserMode();
   }
   ELSEWITHCOVER(0x04AD)
   return Status;
   /* TR:SPMF89:01.0047 End */
} /* end of osPsysCallNonTrustedFunction */

/* TR:SOSK22:0071 Start */
/* TR:SOSK22:0072 Start */
/* MISRA RULE 8.8 violated: (comment 3408) The prototype is created only when necessary in tcb.h.
 * tcb.h must not be included here, so here is no generated code.
 */
void osPsysDisableAllInterrupts(void) /* PRQA S 3408 */
{
   /* CovComment 4:  Function: osPsysDisableAllInterrupts */
   /* TR:SPMF89:01.0043 Start */
   osuint32 CallerIsTrusted;

   COVER(0x04AE)
   /* check the privilege level of the caller and switch to system mode */
   CallerIsTrusted = osSwitchToPrivMode();

   /* call the API function */
   osDisableAllInterrupts();
   /* TR:SPMF89:01.0043 End */
   /* TR:SPMF89:01.0044 Start */
   if(CallerIsTrusted == 0)
   {
      COVER(0x04AF)
      osSwitchToUserMode();
   }
   ELSEWITHCOVER(0x04B0)
   /* TR:SPMF89:01.0044 End */
} /* end of osPsysDisableAllInterrupts */

/* MISRA RULE 8.8 violated: (comment 3408) The prototype is created only when necessary in tcb.h.
 * tcb.h must not be included here, so here is no generated code.
 */
void osPsysEnableAllInterrupts(void) /* PRQA S 3408 */
{
   /* CovComment 4:  Function: osPsysEnableAllInterrupts */
   /* TR:SPMF89:01.0043 Start */
   osuint32 CallerIsTrusted;
   
   COVER(0x04B1)
   /* check the privilege level of the caller and switch to system mode */
   CallerIsTrusted = osSwitchToPrivMode();

   /* call the API function */
   osEnableAllInterrupts();
   /* TR:SPMF89:01.0043 End */
   /* TR:SPMF89:01.0044 Start */
   if(CallerIsTrusted == 0)
   {
      COVER(0x04B2)
      osSwitchToUserMode();
   }
   ELSEWITHCOVER(0x04B3)
   /* TR:SPMF89:01.0044 End */
} /* end of osPsysEnableAllInterrupts */
/* TR:SOSK22:0071 End */
/* TR:SOSK22:0072 End */


/* MISRA RULE 8.8 violated: (comment 3408) The prototype is generated on demand in tcb.h.
 * tcb.h must not be included here, so here is no generated code.
 */
void osPsysSuspendAllInterrupts(void) /* PRQA S 3408 */
{
   /* CovComment 4:  Function: osPsysSuspendAllInterrupts */
   /* TR:SPMF89:01.0043 Start */
   osuint32 CallerIsTrusted;
   
   COVER(0x04B4)
   /* check the privilege level of the caller and switch to system mode */
   CallerIsTrusted = osSwitchToPrivMode();

   /* call the API function */
   osSuspendAllInterrupts();
   /* TR:SPMF89:01.0043 End */
   /* TR:SPMF89:01.0044 Start */
   if(CallerIsTrusted == 0)
   {
      COVER(0x04B5)
      osSwitchToUserMode();
   }
   ELSEWITHCOVER(0x04B6)
   /* TR:SPMF89:01.0044 End */
} /* end of osPsysSuspendAllInterrupts */


/* MISRA RULE 8.8 violated: (comment 3408) The prototype is created only when necessary in tcb.h.
 * tcb.h must not be included here, so here is no generated code.
 */
void osPsysResumeAllInterrupts(void) /* PRQA S 3408 */
{
   /* CovComment 4:  Function: osPsysResumeAllInterrupts */
   /* TR:SPMF89:01.0043 Start */
   osuint32 CallerIsTrusted;
   
   COVER(0x04B7)
   /* check the privilege level of the caller and switch to system mode */
   CallerIsTrusted = osSwitchToPrivMode();

   /* call the API function */
   osResumeAllInterrupts();
   /* TR:SPMF89:01.0043 End */
   /* TR:SPMF89:01.0044 Start */
   if(CallerIsTrusted == 0)
   {
      COVER(0x04B8)
      osSwitchToUserMode();
   }
   ELSEWITHCOVER(0x04B9)
   /* TR:SPMF89:01.0044 End */
} /* end of osPsysResumeAllInterrupts */


/* MISRA RULE 8.8 violated: (comment 3408) The prototype is created only when necessary in tcb.h.
 * tcb.h must not be included here, so here is no generated code.
 */
void osPsysSuspendOSInterrupts(void) /* PRQA S 3408 */
{
   /* CovComment 4:  Function: osPsysSuspendOSInterrupts */
   /* TR:SPMF89:01.0043 Start */
   osuint32 CallerIsTrusted;
   
   COVER(0x04BA)
   /* check the privilege level of the caller and switch to system mode */
   CallerIsTrusted = osSwitchToPrivMode();

   /* call the API function */
   osSuspendOSInterrupts();
   /* TR:SPMF89:01.0043 End */
   /* TR:SPMF89:01.0044 Start */
   if(CallerIsTrusted == 0)
   {
      COVER(0x04BB)
      osSwitchToUserMode();
   }
   ELSEWITHCOVER(0x04BC)
   /* TR:SPMF89:01.0044 End */
} /* end of osPsysSuspendOSInterrupts */


/* MISRA RULE 8.8 violated: (comment 3408) The prototype is created only when necessary in tcb.h.
 * tcb.h must not be included here, so here is no generated code.
 */
void osPsysResumeOSInterrupts(void) /* PRQA S 3408 */
{
   /* CovComment 4:  Function: osPsysResumeOSInterrupts */
   /* TR:SPMF89:01.0043 Start */
   osuint32 CallerIsTrusted;
   
   COVER(0x04BD)
   /* check the privilege level of the caller and switch to system mode */
   CallerIsTrusted = osSwitchToPrivMode();

   /* call the API function */
   osResumeOSInterrupts();
   /* TR:SPMF89:01.0043 End */
   /* TR:SPMF89:01.0044 Start */
   if(CallerIsTrusted == 0)
   {
      COVER(0x04BE)
      osSwitchToUserMode();
   }
   ELSEWITHCOVER(0x04BF)
   /* TR:SPMF89:01.0044 End */
} /* end of osPsysResumeOSInterrupts */
