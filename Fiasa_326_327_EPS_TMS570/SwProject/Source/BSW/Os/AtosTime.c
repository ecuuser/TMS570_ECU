/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: Autosar OS 2.1 / Autosar OS 3.0
|    File Name: atostime.c
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.61
|
|  Description: functions for schedule tables and synchronisation
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

/* CovComment 0:  file: atostime.c */
/* KB begin osekStartOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_CODE_SECTION(".oscode") /* TR:SPMF49:0001 */ /* TR:SPMF49:0002 */
#endif
/* KB end osekStartOfCModule */

#define osdSTINIT_AUTO       1
#define osdSTINIT_SYNCSTART  2
#define osdSTINIT_HRST       4      

#if (osdNumberOfScheduleTables > 0)

#if (osdScheduleTableSyncUsed != 0)

/* Flags
   Note: may be OR'ed, all values must therefore be powers of 2
*/
typedef osuint8 osHRSTFlagsType;
#define osdHRST_NoSpecialInit ((osHRSTFlagsType)0)
#define osdHRST_ForceAsync    ((osHRSTFlagsType)1)  /* Keep state async, even if difference to GlobalTime is smaller than precision */

osqRAM0 static osqRAM1 osqRAM2 osHRSTFlagsType      osqRAM3 osSTFlags       [osdNumberOfScheduleTables]; /* Scheduletable time may still need a init */
osqRAM0 static osqRAM1 osqRAM2 osTickTimeDiffType   osqRAM3 osSTDiffTime    [osdNumberOfScheduleTables]; 
#endif

#if (osdNumberOfHiResSchedTabs > 0) || (osdScheduleTableSyncUsed != 0)
/* MISRA RULE 8.7 VIOLATION: Depending on the configuration, osSTTime might be used by several functions. Conditional
 * compiling of the variable for these configurations would increase the code complexity to unacceptable level (3218).
 */
osqRAM0 static osqRAM1 osqRAM2 TickType             osqRAM3 osSTTime        [osdNumberOfScheduleTables]; /* PRQA S 3218 */

#endif /* #if (osdNumberOfHiResSchedTabs > 0) || (osdScheduleTableSyncUsed != 0) */

#define osGetCurrentEP(ST)   (osSTCurrentIndex[ST])
#define osIncCurrentEP(ST)   (++(osSTCurrentIndex[ST]))
#define osResetCurrentEP(ST) (osSTCurrentIndex[ST] = oskSTStartIndex[ST])

#define osGetTargetTIPTime(TIP)            (osAlarmTime[TIP])
#define osSetTargetTIPTime(TIP, value)     (osAlarmTime[TIP] = (value))
#define osAddToTargetTIPTime(TIP, value)   (osAlarmTime[TIP] += (value))

#define osGetSTTime(ST)                  (osSTTime[ST])
#define osSetSTTime(ST,value)            osSTTime[ST]=(value); 
#define osAddToSTTime(ST, value)         osSTTime[ST] += (value); if (osSTTime[ST] >= oskSTMaxAllowed[ST]) { osSTTime[ST] -= oskSTMaxAllowed[ST]; }
#define osHRSTSetUpdateSTTime(ST,value)  osSTTime[ST]=(value); osSTTimeOfLastUpdate[ST] = osGetSystemCounter()
#define osGetTimeOfLastUpdate(ST)        (osSTTimeOfLastUpdate[ST])
#define osSetTimeOfLastUpdate(ST,value)  (osSTTimeOfLastUpdate[ST] = (value))

#define osConvertTIP2ST(TIPid) ((ScheduleTableType)((TIPid) - osdNumberOfAlarms))
#define osConvertST2TIP(STid)  ((osTIPType)((STid) + osdNumberOfAlarms))





/*-+--------------------------------------------------------------------------
 / StartScheduleTableRel
 / =====================
 /
 / Syntax: 
 /    StatusType StartScheduleTableRel(
 /                                      ScheduleTableType ScheduleTableID, 
 /                                      TickType Offset
 /                                    )
 / Parameter (In):
 /   ScheduleTableType ScheduleTableID
 /   TickType Offset
 / Parameter (Out):
 /   none
 / Description:
 /   If its input parameters are valid, StartScheduleTableRel() starts the
 /   processing of a schedule table <ScheduleTableID> at its first expiry point
 /   after offset <Offset> ticks have elapsed.
 / Return value (depends on OIL-Attribute STATUS):
 /    STANDARD:
 /       - No error, E_OK
 /       - Schedule table <ScheduleTableID> is in any other state than 
 /         SCHEDULETABLE_STOPPED, E_OS_STATE
 /    EXTENDED: 
 /       - <ScheduleTableID> not valid, or schedule table is implicitely 
           synchronized E_OS_ID
 /       - <Offset> too big or zero, E_OS_VALUE
 /       - The service has been called with interrupts disabled, 
 /         E_OS_DISABLEDINT
 / Scalability Classes:
 /    SC1, SC2, SC3, SC4
 /--------------------------------------------------------------------------*/
/* TR:SASR30:0123 Start */
/* MISRA RULE 14.1 violated: (comment 1503) In SafeContext implementations all APIs 
 * are encapsulated in wrappers. This wrappers belong to static ASIL code and must exist, 
 * even if they are not used in a project. 
 */
osqFunc1 StatusType osqFunc2 osStartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset) /* PRQA S 1503 */ /* TR:SASR30:0375 */
{
   /* CovComment 4:  Function: osStartScheduleTableRel */
   #if (osdNumberOfHiResSchedTabs>0)
   TickType HWnow;
   #endif
   OS_SR_ENTRY()
   COVER(0x0308)
   #if (osdNumberOfHiResSchedTabs>0)
   COVER(0x0309)
   HWnow = osGetSystemCounter();
   #endif

   COVER(0x030A)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in StartScheduleTableRel */
   /* TR:SASR30:0336 Start Context check in StartScheduleTableRel */
   if ((osdValidCtx_StartScheduleTableRel & osCurrentContext) == 0)
   {
      COVER(0x030B)
      osSaveStartScheduleTableRel_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableRel_Offset(Offset)
      osAPIError(E_OS_CALLEVEL, osdErrSRCallContext);
      OS_SR_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x030C)

   /* TR:SASR30:0120 Start */
   if (ScheduleTableID >= osrNumberOfScheduleTables)
   {
      /* return E_OS_ID if the schedule table id is invalid */
      COVER(0x030D)
      osSaveStartScheduleTableRel_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableRel_Offset(Offset)
      osAPIError(E_OS_ID, osdErrSRWrongID);
      OS_SR_EXIT()
      return E_OS_ID;
   }
   /* TR:SASR30:0120 End */
   ELSEWITHCOVER(0x030E)

   /* TR:SASR30:0254 Start */
   if (oskSTSyncKind[ScheduleTableID] == osdSTSyncImplicit)
   {
      /* return E_OS_ID if the schedule table is implicitely synchronized */
      COVER(0x030F)
      osSaveStartScheduleTableRel_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableRel_Offset(Offset)
      osAPIError(E_OS_ID, osdErrSRImpliciteSync);
      OS_SR_EXIT()
      return E_OS_ID;
   }
   /* TR:SASR30:0254 End */
   ELSEWITHCOVER(0x0310)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in StartScheduleTableRel */
   if (((oskApplScheduleTableAccess[ScheduleTableID] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x0311)
      osSaveStartScheduleTableRel_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableRel_Offset(Offset)
      osAPIError(E_OS_ACCESS, osdErrSRNoAccess);
      OS_SR_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x0312)

   /* TR:SASR30:0163 Start*/
   if (Offset == 0)
   {
      /* return E_OS_VALUE if offset is 0 */
      COVER(0x0313)
      osSaveStartScheduleTableRel_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableRel_Offset(Offset)
      osAPIError(E_OS_VALUE, osdErrSRZeroOffset);
      OS_SR_EXIT()
      return E_OS_VALUE;
   }
   /* TR:SASR30:0163 End */
   ELSEWITHCOVER(0x0314)
   /* check against MAXALLOWEDVALUE */

   /* TR:SASR30:0121 Start */
   if (Offset > (TickType)(oskCounterMaxAllowedValue[oskCounterOfST[ScheduleTableID]]-
                           oskScheduleTableInitialOffset[ScheduleTableID])) 
   {
      /* return E_OS_VALUE if offset is greater than OsCounterMaxAllowedValue - Initial offset */
      COVER(0x0315)
      osSaveStartScheduleTableRel_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableRel_Offset(Offset)
      osAPIError(E_OS_VALUE, osdErrSROffsetTooBig);
      OS_SR_EXIT()
      return E_OS_VALUE;
   }
   /* TR:SASR30:0121 End */
   ELSEWITHCOVER(0x0316)
   
   /* TR:SASR30:0038 Start Check disabled interrupts in StartScheduleTableRel */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x0317)
      osSaveStartScheduleTableRel_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableRel_Offset(Offset)
      osAPIError(E_OS_DISABLEDINT, osdErrSRIntAPIDisabled);
      OS_SR_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x0318)

   COVER(0x0319)

   /* TR:SASR30:0122 Start */
   if (osSTState[ScheduleTableID] != SCHEDULETABLE_STOPPED)
   {
      /* return E_OS_STATE if schedule table state is not SCHEDULETABLE_STOPPED */
      COVER(0x031A)
      osSaveStartScheduleTableRel_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableRel_Offset(Offset)
      osAPIError(E_OS_STATE, osdErrSRAlreadyRunningOrNext);
      OS_SR_EXIT()
      return E_OS_STATE;
   }
   /* TR:SASR30:0122 End */
   ELSEWITHCOVER(0x031B)
   
   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */


   osSTState[ScheduleTableID] = SCHEDULETABLE_RUNNING; /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 *//* TR:SASR30:0290 */


   #if (osdScheduleTableSyncUsed != 0)
      COVER(0x031C)
      osSTFlags[ScheduleTableID] = osdHRST_ForceAsync; /* Even though this ST has a DiffTime of 0, it must be considered Async */
      osSTDiffTime[ScheduleTableID] = 0;     /* Synchronisation rest */
   #endif

   {
      COVER(0x031D)
      /* TR:SASR30:0169 Start */
      #if (osdScheduleTableSyncUsed != 0)
         /* Do the modulo only when the schedule table maximum value is below TickType maximum value */
         if((oskSTMaxAllowed[ScheduleTableID] + 1) == 0)
         {
            TickType Zero = 0;
            COVER(0x031E)
            /* MISRA RULE 21.1 not violated: Rule 21.1 is not violated, static code checking is applied.
               And the line below is fully intended: We want to get the negative of number in a finite ring,
               and some compilers complained about the standard method (writing "-Offset").
             */
            osSTTime[ScheduleTableID] = Zero-Offset;  /* PRQA S 3372 */            
         }
         else
         {
            COVER(0x031F)
            osSTTime[ScheduleTableID] = (TickType) ((oskSTMaxAllowed[ScheduleTableID] + 1) - 
                                                    (Offset % (oskSTMaxAllowed[ScheduleTableID] + 1)));
         }
      #endif
      osSTCurrentIndex[ScheduleTableID] = oskSTStartIndex[ScheduleTableID]; /* TR:SASR30:0232 */
      /* initial offset needs no consideration as we have a fake expiry point at zero if there is no user expiry point */
      osSTCounter[ScheduleTableID]= Offset;
      /* TR:SASR30:0169 End */
   }
   COVER(0x0320)

   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_SR_END_CRITICAL()
   OS_SR_EXIT()

   return E_OK;
}
/* TR:SASR30:0123 End */

/*-+--------------------------------------------------------------------------
 / StartScheduleTableAbs
 / =====================
 /
 / Syntax: 
 /    StatusType StartScheduleTableAbs(
 /                                      ScheduleTableType ScheduleTableID, 
 /                                      TickType Tickvalue
 /                                    )
 / Parameter (In):
 /   ScheduleTableType ScheduleTableID
 /   TickType Tickvalue
 / Parameter (Out):
 /   none
 / Description:
 /   If its input parameters are valid, StartScheduleTableAbs() starts the
 /   processing of a schedule table <ScheduleTableID> at its first expiry point
 /   when the underlaying counter reaches the value <Tickvalue>.
 / Return value (depends on OIL-Attribute STATUS):
 /    STANDARD:
 /       - No error, E_OK
 /       - Schedule table <ScheduleTableID> is in any other state than 
 /         SCHEDULETABLE_STOPPED, E_OS_STATE
 /    EXTENDED: 
 /       - <ScheduleTableID> not valid, E_OS_ID
 /       - <Tickvalue> too big, E_OS_VALUE
 /       - The service has been called with interrupts disabled, 
 /         E_OS_DISABLEDINT
 / Scalability Classes:
 /    SC1, SC2, SC3, SC4
 /--------------------------------------------------------------------------*/
/* TR:SASR30:0173 Start */
/* MISRA RULE 14.1 violated: (comment 1503) In SafeContext implementations all APIs 
 * are encapsulated in wrappers. This wrappers belong to static ASIL code and must exist, 
 * even if they are not used in a project. 
 */
osqFunc1 StatusType osqFunc2 osStartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Tickvalue) /* PRQA S 1503 *//* TR:SASR30:0376 */
{
   /* CovComment 4:  Function: osStartScheduleTableAbs */
   OS_SS_ENTRY()
   COVER(0x0321)

   COVER(0x0322)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in StartScheduleTableAbs */
   /* TR:SASR30:0336 Start Context check in StartScheduleTableAbs */
   if ((osdValidCtx_StartScheduleTableAbs & osCurrentContext) == 0)
   {
      COVER(0x0323)
      osSaveStartScheduleTableAbs_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableAbs_Tickvalue(Tickvalue)
      osAPIError(E_OS_CALLEVEL, osdErrSSCallContext);
      OS_SS_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x0324)

   /* TR:SASR30:0170 Start */
   if (ScheduleTableID >= osrNumberOfScheduleTables)
   {
      COVER(0x0325)
      osSaveStartScheduleTableAbs_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableAbs_Tickvalue(Tickvalue)
      osAPIError(E_OS_ID, osdErrSSWrongID);
      OS_SS_EXIT()
      return E_OS_ID;
   }
   /* TR:SASR30:0170 End */
   ELSEWITHCOVER(0x0326)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in ScheduleTableAbs */
   if (((oskApplScheduleTableAccess[ScheduleTableID] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x0327)
      osSaveStartScheduleTableAbs_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableAbs_Tickvalue(Tickvalue)
      osAPIError(E_OS_ACCESS, osdErrSSNoAccess);
      OS_SS_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x0328)

   /* check against MAXALLOWEDVALUE */
   /* TR:SASR30:0171 Start */
   if (Tickvalue > oskCounterMaxAllowedValue[oskCounterOfST[ScheduleTableID]]) 
   {
      /* return E_OS_VALUE if Tickvalue is greater than OsCounterMaxAllowedValue */
      COVER(0x0329)
      osSaveStartScheduleTableAbs_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableAbs_Tickvalue(Tickvalue)
      osAPIError(E_OS_VALUE, osdErrSSTickvalueTooBig);
      OS_SS_EXIT()
      return E_OS_VALUE;
   }
   /* TR:SASR30:0171 End */
   ELSEWITHCOVER(0x032A)

   /* TR:SASR30:0038 Start Check disabled interrupts in StartScheduleTableAbs */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x032B)
      osSaveStartScheduleTableAbs_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableAbs_Tickvalue(Tickvalue)
      osAPIError(E_OS_DISABLEDINT, osdErrSSIntAPIDisabled);
      OS_SS_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x032C)
   
   OS_SS_START_CRITICAL()

   /* TR:SASR30:0172 Start */
   if (osSTState[ScheduleTableID] != SCHEDULETABLE_STOPPED)
   {
      /* return E_OS_STATE if schedule table state is not SCHEDULETABLE_STOPPED */
      COVER(0x032D)
      osSaveStartScheduleTableAbs_ScheduleTableID(ScheduleTableID)
      osSaveStartScheduleTableAbs_Tickvalue(Tickvalue)
      osAPIError(E_OS_STATE, osdErrSSAlreadyRunningOrNext);
      OS_SS_EXIT()
      return E_OS_STATE;
   }
   /* TR:SASR30:0172 End */
   ELSEWITHCOVER(0x032E)
  
   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */

   {
      /* No synchronization necessary, start immediately when Tickvalue is reached */
      TickType now;
      
      #if osdUseCounterAPI
         COVER(0x032F)
         now = osCounter[oskCounterOfST[ScheduleTableID]];
      #else
         COVER(0x0330)
         now = osGetSystemCounter();
      #endif

      #if (osdUseHeap != 0)
         COVER(0x0331)
         now &= (TickType)(~osdSystemCounterMask);
      #else
         COVER(0x0332)
      #endif
      /* check, if Tickvalue is after the next overflow */
      /* initial offset needs no consideration as we have a fake expiry point at zero if there is no user expiry point */
      /* TR:SASR30:0178 Start */
      if (Tickvalue > now)
      {
         COVER(0x0333)
         /* Tickvalue is before next overflow */
         osSTCounter[ScheduleTableID] = Tickvalue - now;
      }
      else
      {
         COVER(0x0334)
         /* an overflow is necessary to reach Tickvalue time */
         osSTCounter[ScheduleTableID] = (TickType) (Tickvalue + 1 +
            ( oskCounterMaxAllowedValue[oskCounterOfST[ScheduleTableID]] - now ));
      }
      /* TR:SASR30:0178 End */
      #if (osdScheduleTableSyncUsed != 0)
      {
         TickType Offset;
         if( Tickvalue > now )
         {
            COVER(0x0335)
            Offset = Tickvalue - now;
         }
         else
         {
            COVER(0x0336)
            Offset = (TickType)(oskSTMaxAllowed[ScheduleTableID] + 1 - now + Tickvalue);
         }
         /* Do the modulo only when the schedule table maximum value is below TickType maximum value */
         if((oskSTMaxAllowed[ScheduleTableID] + 1) == 0)
         {
            TickType Zero = 0;
            COVER(0x0337)
            osSTTime[ScheduleTableID] = Zero - Offset;             
         }
         else
         {
            COVER(0x0338)
            osSTTime[ScheduleTableID] = (TickType)(oskSTMaxAllowed[ScheduleTableID] + 1 - 
                                                   (Offset % (oskSTMaxAllowed[ScheduleTableID] + 1)));
         }
      }
      #endif /* (osdScheduleTableSyncUsed != 0) */
   }

   osSTState[ScheduleTableID] = SCHEDULETABLE_RUNNING; /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 *//* TR:SASR30:0289 */

#if (osdScheduleTableSyncUsed != 0)
   COVER(0x0339)
   osSTFlags[ScheduleTableID]=osdHRST_ForceAsync; /* Even though this ST has a DiffTime of 0, it must be considered Async */
   osSTDiffTime[ScheduleTableID] = 0;
#endif

   osResetCurrentEP(ScheduleTableID); /* TR:SASR30:0232 */
   COVER(0x033A)



   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */

   OS_SS_END_CRITICAL()
   OS_SS_EXIT()

   return E_OK;
}
/* TR:SASR30:0173 End */

#if (osdScheduleTableSyncUsed != 0) /* 5011271_ISSUE_07 */ /* TR:SASR30:0093 Start */
/*-+--------------------------------------------------------------------------
 / StartScheduleTableSynchron
 / ==========================
 /
 / Syntax: 
 /    StatusType StartScheduleTableSynchron(ScheduleTableType ScheduleTableID)
 / Parameter (In):
 /   ScheduleTableType ScheduleTableID
 / Parameter (Out):
 /   none
 / Description:
 /   If its input parameters are valid, StartScheduleTableSynchron() starts
 /   the processing of schedule table <ScheduleTableID> at its first expiry 
 /   point after the global time of the schedule table is set via 
 /   SyncScheduleTable().
 / Return value (depends on OIL-Attribute STATUS):
 /    STANDARD:
 /       - No error, E_OK
 /       - Schedule table <ScheduleTableID> is in any other state than 
 /         SCHEDULETABLE_STOPPED, E_OS_STATE
 /    EXTENDED: 
 /       - <ScheduleTableID> not valid, E_OS_ID
 /       - The service has been called with interrupts disabled, 
 /         E_OS_DISABLEDINT
 / Scalability Classes:
 /     SC2, SC4
 /--------------------------------------------------------------------------*/
osqFunc1 StatusType osqFunc2 osStartScheduleTableSynchron(ScheduleTableType ScheduleTableID)
{
   /* CovComment 4:  Function: osStartScheduleTableSynchron */
   OS_SO_ENTRY()


   COVER(0x033B)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in StartScheduleTableSynchron */
   /* TR:SASR30:0336 Start Context check in StartScheduleTableSynchron */
   if ((osdValidCtx_StartScheduleTableSynchron & osCurrentContext) == 0)
   {
      COVER(0x033C)
         osSaveStartScheduleTableSynchron_ScheduleTableID(ScheduleTableID)
      osAPIError(E_OS_CALLEVEL, osdErrTSCallContext);
      OS_SO_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x033D)

   /* TR:SASR30:0198 Start */
   if (ScheduleTableID >= osrNumberOfScheduleTables)
   {
      /* return E_OS_ID if schedule table ID is not valid */
      COVER(0x033E)
         osSaveStartScheduleTableSynchron_ScheduleTableID(ScheduleTableID)
      osAPIError(E_OS_ID, osdErrTSWrongID);
      OS_SO_EXIT()
      return E_OS_ID;
   }
   /* TR:SASR30:0198 End */
   ELSEWITHCOVER(0x033F)

   /* TR:SASR30:0198 */
   if (oskSTSyncKind[ScheduleTableID]!=osdSTSyncExplicit)
   {
      /* return E_OS_ID if schedule table is not explicitely synchronized */
      COVER(0x0340)
      osSaveStartScheduleTableSynchron_ScheduleTableID(ScheduleTableID)
      COVER(0x0341)
      osAPIError(E_OS_ID, osdErrTSSyncKindNotExplicit);
      OS_SO_EXIT()
      return E_OS_ID;   
   }
   /* TR:SASR30:0198 End */
   ELSEWITHCOVER(0x0342)


   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in StartScheduleTableSynchron */
   if (((oskApplScheduleTableAccess[ScheduleTableID] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x0343)
      osSaveStartScheduleTableSynchron_ScheduleTableID(ScheduleTableID)
      osAPIError(E_OS_ACCESS, osdErrTSNoAccess);
      OS_SO_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x0344)

   /* TR:SASR30:0038 Start Check disabled interrupts in ScheduleTableSynchron */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x0345)
      osSaveStartScheduleTableSynchron_ScheduleTableID(ScheduleTableID)
      osAPIError(E_OS_DISABLEDINT, osdErrTSIntAPIDisabled);
      OS_SO_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x0346)


   if (osSTState[ScheduleTableID] != SCHEDULETABLE_STOPPED)
   {
      COVER(0x0347)
      osSaveStartScheduleTableSynchron_ScheduleTableID(ScheduleTableID)
      osAPIError(E_OS_STATE, osdErrTSSTAlreadyRunning);
      COVER(0x0348)
      OS_SO_EXIT()
      return E_OS_STATE;
   }
   ELSEWITHCOVER(0x0349)
      
   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */
   osSTFlags[ScheduleTableID] = osdHRST_NoSpecialInit;
   osSTTime[ScheduleTableID] = 0;       /* Start Offset Local Time */
   osSTDiffTime[ScheduleTableID] = 0;   /* Start synchronized  */
   osSTState[ScheduleTableID] = SCHEDULETABLE_WAITING; /* TR:SASR30:0301 */
   osResetCurrentEP(ScheduleTableID);
   
   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */

   OS_SO_END_CRITICAL()
   OS_SO_EXIT()

   return E_OK;
} /* StartScheduleTableSynchron() */

#endif /*(osdScheduleTableSyncUsed) 5011271_ISSUE_07 */ /* TR:SASR30:0093 End */

/*-+--------------------------------------------------------------------------
 / StopScheduleTable
 / =================
 /
 / Syntax: 
 /    StatusType StopScheduleTable(ScheduleTableType ScheduleTableID)
 / Parameter (In):
 /   ScheduleTableType ScheduleTableID
 / Parameter (Out):
 /   none
 / Description:
 /   If its input parameter is valid, StopScheduleTable() stops the schedule 
 /   table <ScheduleTableID> from processing any further expiry points.
 / Return value (depends on OIL-Attribute STATUS):
 /    STANDARD:
 /       - No error, E_OK
 /       - Schedule table <ScheduleTableID> is in the state 
 /         SCHEDULETABLE_STOPPED or SCHEDULETABLE_NEXT, E_OS_NOFUNC
 /    EXTENDED: 
 /       - <ScheduleTableID> not valid, E_OS_ID
 /       - The service has been called with interrupts disabled, 
 /         E_OS_DISABLEDINT
 / Scalability Classes:
 /    SC1, SC2, SC3, SC4
 /--------------------------------------------------------------------------*/
/* TR:SASR30:0003 Start */
/* TR:SASR30:0126 Start */
/* MISRA RULE 14.1 violated: (comment 1503) In SafeContext implementations all APIs 
 * are encapsulated in wrappers. This wrappers belong to static ASIL code and must exist, 
 * even if they are not used in a project. 
 */
osqFunc1 StatusType osqFunc2 osStopScheduleTable(ScheduleTableType ScheduleTableID) /* PRQA S 1503 *//* TR:SASR30:0377 */
{
   /* CovComment 4:  Function: osStopScheduleTable */
   OS_SP_ENTRY()
   COVER(0x034A)

   COVER(0x034B)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in StopScheduleTable */
   /* TR:SASR30:0336 Start Context check in StopScheduleTable */
   if ((osdValidCtx_StopScheduleTable & osCurrentContext) == 0)
   {
      COVER(0x034C)
         osSaveStopScheduleTable_ScheduleTableID(ScheduleTableID)
      osAPIError(E_OS_CALLEVEL, osdErrSPCallContext);
      OS_SP_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x034D)

   /* TR:SASR30:0124 Start */
   if (ScheduleTableID >= osrNumberOfScheduleTables)
   {
      /* return E_OS_ID if the schedule table id is invalid */
      COVER(0x034E)
      osSaveStopScheduleTable_ScheduleTableID(ScheduleTableID)
      osAPIError(E_OS_ID, osdErrSPWrongID);
      OS_SP_EXIT()
      return E_OS_ID;
   }
   /* TR:SASR30:0124 End */
   ELSEWITHCOVER(0x034F)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in StopScheduleTable */
   if (((oskApplScheduleTableAccess[ScheduleTableID] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x0350)
      osSaveStopScheduleTable_ScheduleTableID(ScheduleTableID)
      osAPIError(E_OS_ACCESS, osdErrSPNoAccess);
      OS_SP_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x0351)

   /* TR:SASR30:0038 Start Check disabled interrupts in StopScheduleTable */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x0352)
         osSaveStopScheduleTable_ScheduleTableID(ScheduleTableID)
      osAPIError(E_OS_DISABLEDINT, osdErrSPIntAPIDisabled);
      OS_SP_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x0353)

   /* TR:SASR30:0125 Start */
   if (
       (osSTState[ScheduleTableID] == SCHEDULETABLE_STOPPED) ||
       (osSTState[ScheduleTableID] == SCHEDULETABLE_NEXT)
      )
   {
      /* return E_OS_NOFUNC if the schedule table state is SCHEDULETABLE_STOPPED */
      COVER(0x0354)
         osSaveStopScheduleTable_ScheduleTableID(ScheduleTableID)
      osAPIError(E_OS_NOFUNC, osdErrSPNotRunning);
      COVER(0x0355)
      OS_SP_EXIT()
      return E_OS_NOFUNC;
   }
   /* TR:SASR30:0125 End */
   ELSEWITHCOVER(0x0356)
   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */

   /* Stop next schedule table (if any) */
   /* TR:SASR30:0255 Start */
   if (osSTNextTable[ScheduleTableID] != INVALID_SCHEDULETABLE)
   {
      COVER(0x0357)
      osSTState[osSTNextTable[ScheduleTableID]] = SCHEDULETABLE_STOPPED; /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 *//* TR:SASR30:0292 */
   }
   /* TR:SASR30:0255 End */
   ELSEWITHCOVER(0x0358)

   osSTNextTable[ScheduleTableID]= INVALID_SCHEDULETABLE;
   osSTState[ScheduleTableID]= SCHEDULETABLE_STOPPED; /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 *//* TR:SASR30:0292 */

   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_SP_EXIT()

   return E_OK;
}
/* TR:SASR30:0126 End */
/* TR:SASR30:0003 End */

/* internal stopping of scheduletables */
/* !!! must be called with interrupts globally disabled! */
/* MISRA RULE 14.1 violated: (comment 1503) In SafeContext implementations all APIs 
 * are encapsulated in wrappers. This wrappers belong to static ASIL code and must exist, 
 * even if they are not used in a project. 
 */
osqFunc1 void osqFunc2 osSysStopScheduleTable(ScheduleTableType ScheduleTableID) /* PRQA S 1503 *//* TR:SASR30:0377 */
{
   /* CovComment 4:  Function: osSysStopScheduleTable */
   /*Exists a next schedule table?*/
   if (osSTNextTable[ScheduleTableID] != INVALID_SCHEDULETABLE)
   {
      COVER(0x0359)
      /*Yes: reset it to not started*/
      osSTState[osSTNextTable[ScheduleTableID]] = SCHEDULETABLE_STOPPED; /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 *//* TR:SASR30:0292 */
   }
   ELSEWITHCOVER(0x035A)
   
   osSTNextTable[ScheduleTableID] = INVALID_SCHEDULETABLE;

   /*reset schedule table to not started*/
   osSTState[ScheduleTableID] = SCHEDULETABLE_STOPPED; /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 *//* TR:SASR30:0292 */
   
}




/*-+--------------------------------------------------------------------------
 / NextScheduleTable
 / ===================
 /
 / Syntax: 
 /   StatusType NextScheduleTable( 
 /                                 ScheduleTableType ScheduleTableID_current,
 /                                 ScheduleTableType ScheduleTableID_next 
 /                               )
 / Parameter (In):
 /   ScheduleTableType ScheduleTableID_current,
 /   ScheduleTableType ScheduleTableID_next 
 / Parameter (Out):
 /   none
 / Description:
 /   Start the schedule table <ScheduleTableID_next> after 
 /   <ScheduleTableID_current> reaches its period/length. In case, an other 
 /   schedule table is already configured to be started after 
 /   <ScheduleTableID_current> reaches its period/length, that other schedule
 /   table is replaced by <ScheduleTableID_next>.
 / Return value (depends on OIL-Attribute STATUS):
 /    STANDARD:
 /       - No error, E_OK
 /       - The schedule table <ScheduleTableID_current> is in the state
 /         SCHEDULETABLE_STOPPED, E_OS_NOFUNC
 /       - The schedule table <ScheduleTableID_current> is in the state
 /         SCHEDULETABLE_NEXT, E_OS_NOFUNC
 /    EXTENDED: 
 /       - <ScheduleTableID_current> not valid, E_OS_ID
 /       - <ScheduleTableID_nest> not valid, E_OS_ID
 /       - Schedule table <ScheduleTableID_next> is in any other state than
 /         SCHEDULETABLE_STOPPED, E_OS_STATE
 /       - The service has been called with interrupts disabled, 
 /         E_OS_DISABLEDINT
 / Scalability Classes:
 /    SC1, SC2, SC3, SC4
 /--------------------------------------------------------------------------*/
/* TR:SASR30:0065 Start */
/* TR:SASR30:0129 Start */
/* MISRA RULE 14.1 violated: (comment 1503) In SafeContext implementations all APIs 
 * are encapsulated in wrappers. This wrappers belong to static ASIL code and must exist, 
 * even if they are not used in a project. 
 */
osqFunc1 StatusType osqFunc2 osNextScheduleTable(ScheduleTableType ScheduleTableID_current, ScheduleTableType ScheduleTableID_next ) /* PRQA S 1503 *//* TR:SASR30:0378 */
{
   /* CovComment 4:  Function: osNextScheduleTable */
   OS_SN_ENTRY()
   COVER(0x035B)

   COVER(0x035C)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in NextScheduleTable */
   /* TR:SASR30:0336 Start Context check in NextScheduleTable */
   if ((osdValidCtx_NextScheduleTable & osCurrentContext) == 0)
   {
      COVER(0x035D)
         osSaveNextScheduleTable_ScheduleTableID_current(ScheduleTableID_current)
         osSaveNextScheduleTable_ScheduleTableID_next(ScheduleTableID_next)
      osAPIError(E_OS_CALLEVEL, osdErrSNCallContext);
      OS_SN_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x035E)

   /* TR:SASR30:0127 Start */
   if (ScheduleTableID_current >= osrNumberOfScheduleTables)
   {
      /* return E_OS_ID if the ST_current id is invalid */
      COVER(0x035F)
      osSaveNextScheduleTable_ScheduleTableID_current(ScheduleTableID_current)
      osSaveNextScheduleTable_ScheduleTableID_next(ScheduleTableID_next)
      osAPIError(E_OS_ID, osdErrSNWrongCurrentID);
      OS_SN_EXIT()
      return E_OS_ID;
   }
   /* TR:SASR30:0127 End*/
   ELSEWITHCOVER(0x0360)
   /* TR:SASR30:0127 Start */
   if (ScheduleTableID_next >= osrNumberOfScheduleTables)
   {
      /* return E_OS_ID if the ST_next is invalid */
      COVER(0x0361)
      osSaveNextScheduleTable_ScheduleTableID_current(ScheduleTableID_current)
      osSaveNextScheduleTable_ScheduleTableID_next(ScheduleTableID_next)
      osAPIError(E_OS_ID, osdErrSNWrongNextID);
      OS_SN_EXIT()
      return E_OS_ID;
   }
   /* TR:SASR30:0127 End */
   ELSEWITHCOVER(0x0362)
   /* check access rights for these objects */
   /* TR:SASR30:0021 Start Check access rights in NextScheduleTable */
   if (    ((oskApplScheduleTableAccess[ScheduleTableID_current] & (1UL << osaActiveApplicationID)) == 0) 
        || ((oskApplScheduleTableAccess[ScheduleTableID_next] & (1UL << osaActiveApplicationID)) == 0)
      )
   {
      COVER(0x0363)
      osSaveNextScheduleTable_ScheduleTableID_current(ScheduleTableID_current)
      osSaveNextScheduleTable_ScheduleTableID_next(ScheduleTableID_next)
      osAPIError(E_OS_ACCESS, osdErrSNNoAccess);
      OS_SN_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x0364)

#if (osdNumberOfCounters > 1)
   /* TR:SASR30:0162 Start */
   if (oskCounterOfST[ScheduleTableID_next] != 
       oskCounterOfST[ScheduleTableID_current] )
   {
      /* return E_OS_ID if the ST_next counter is different than current ST counter */
      COVER(0x0365)
      osSaveNextScheduleTable_ScheduleTableID_current(ScheduleTableID_current)
      osSaveNextScheduleTable_ScheduleTableID_next(ScheduleTableID_next)
      osAPIError(E_OS_ID, osdErrSNDifferentCounters);
      OS_SN_EXIT()
      return E_OS_ID;
   }
   /* TR:SASR30:0162 End */
   ELSEWITHCOVER(0x0366)
#endif

   /* TR:SASR30:0038 Start Check disabled interrupts in NextScheduleTable */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x0367)
      osSaveNextScheduleTable_ScheduleTableID_current(ScheduleTableID_current)
      osSaveNextScheduleTable_ScheduleTableID_next(ScheduleTableID_next)
      osAPIError(E_OS_DISABLEDINT, osdErrSNIntAPIDisabled);
      OS_SN_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x0368)
   COVER(0x0369)

   /* TR:SASR30:0128 Start */
   if (osSTState[ScheduleTableID_current] < SCHEDULETABLE_WAITING)
   {
      /* return E_OS_NOFUNC if ST_current state is STOPPED or NEXT */
      COVER(0x036A)
      osSaveNextScheduleTable_ScheduleTableID_current(ScheduleTableID_current)
      osSaveNextScheduleTable_ScheduleTableID_next(ScheduleTableID_next)
      osAPIError(E_OS_NOFUNC, osdErrSNNotRunning);
      COVER(0x036B)
      OS_SN_EXIT()
      return E_OS_NOFUNC;
   }
   /* TR:SASR30:0128 End */
   ELSEWITHCOVER(0x036C)
   COVER(0x036D)
   /* TR:SASR30:0147 Start */
   if (osSTState[ScheduleTableID_next] != SCHEDULETABLE_STOPPED)
   {
      /* return E_OS_STATE if ST_next state is not STOPPED */
      COVER(0x036E)
      osSaveNextScheduleTable_ScheduleTableID_current(ScheduleTableID_current)
      osSaveNextScheduleTable_ScheduleTableID_next(ScheduleTableID_next)
      osAPIError(E_OS_STATE, osdErrSNAlreadyRunningOrNext);
      COVER(0x036F)
      OS_SN_EXIT()
      return E_OS_STATE;
   }
   /* TR:SASR30:0147 End */
   ELSEWITHCOVER(0x0370)

   COVER(0x0371)
   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */

   /* Is there already a schedule table planned for next? */
   /* TR:SASR30:0157 Start */
   if (osSTNextTable[ScheduleTableID_current] != INVALID_SCHEDULETABLE)
   {
      COVER(0x0372)
      /* Yes: set its state back to not started */
      osSTState[osSTNextTable[ScheduleTableID_current]] = SCHEDULETABLE_STOPPED; /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 */
   }
   ELSEWITHCOVER(0x0373)

   osSTNextTable[ScheduleTableID_current]= ScheduleTableID_next;
   osSTState[ScheduleTableID_next] = SCHEDULETABLE_NEXT; /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 *//* TR:SASR30:0291 */
   /* TR:SASR30:0157 End */

   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_SN_EXIT()

   return E_OK;
}
/* TR:SASR30:0065 End */
/* TR:SASR30:0129 End */

/*-+--------------------------------------------------------------------------
 / GetScheduleTableStatus
 / ======================
 /
 / Syntax: 
 /   StatusType osGetScheduleTableStatus(
 /                                  ScheduleTableType ScheduleTableID,
 /                                  ScheduleTableStatusRefType ScheduleStatus
 /                                      )
 / Parameter (In):
 /   ScheduleTableType ScheduleTableID,
 / Parameter (Out):
 /   ScheduleTableStatusRefType ScheduleStatus
 / Description:
 /   Returns the state of the schedule table <ScheduleTableID> via the 
 /   (out) parameter ScheduleTableStatusRefType.
 / Return value (depends on OIL-Attribute STATUS):
 /    STANDARD:
 /       - No error, E_OK
 /    EXTENDED: 
 /       - <ScheduleTableID> not valid, E_OS_ID
 /       - The service has been called with interrupts disabled, 
 /         E_OS_DISABLEDINT
 / Scalability Classes:
 /    SC1, SC2, SC3, SC4
 /--------------------------------------------------------------------------*/
/* TR:SASR30:0179 Start */
/* MISRA RULE 14.1 violated: (comment 1503) In SafeContext implementations all APIs 
 * are encapsulated in wrappers. This wrappers belong to static ASIL code and must exist, 
 * even if they are not used in a project. 
 */
osqFunc1 ScheduleTableStatusType osqFunc2 osGetScheduleTableStatus(ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus) /* PRQA S 1503 *//* TR:SASR30:0382 */
{
   /* CovComment 4:  Function: osGetScheduleTableStatus */
   OS_SG_ENTRY()
   COVER(0x0374)

   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. */    
   osdDummyRead(ScheduleStatus) /* PRQA S 3199 */ /* TR:SASR30:0134 *//* TR:SASR30:0135 *//* TR:SASR30:0136 *//* TR:SASR30:0174 *//* TR:SASR30:0175 */

   COVER(0x0375)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in GetScheduleTableStatus */
   /* TR:SASR30:0336 Start Context check in GetScheduleTableStatus */
   if ((osdValidCtx_GetScheduleTableStatus & osCurrentContext) == 0)
   {
      COVER(0x0376)
        osSaveGetScheduleTableStatus_ScheduleID(ScheduleTableID)
        osSaveGetScheduleTableStatus_ScheduleStatus(ScheduleStatus)
      osAPIError(E_OS_CALLEVEL, osdErrSGCallContext);
      osStatusTypeReturn = E_OS_CALLEVEL;
      OS_SG_EXIT()
      return 0;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x0377)

   /* TR:SASR30:0138 Start*/
   if (ScheduleTableID >= osrNumberOfScheduleTables)
   {
      /* return E_OS_ID if the schedule table id is invalid */
      COVER(0x0378)
      osSaveGetScheduleTableStatus_ScheduleID(ScheduleTableID)
      osSaveGetScheduleTableStatus_ScheduleStatus(ScheduleStatus)
      osAPIError(E_OS_ID, osdErrSGWrongID);
      OS_SG_EXIT()
      osStatusTypeReturn = E_OS_ID;
      return 0;
   }
   /* TR:SASR30:0138 End */
   ELSEWITHCOVER(0x0379)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in GetScheduleTableStatus */
   if (((oskApplScheduleTableAccess[ScheduleTableID] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x037A)
        osSaveGetScheduleTableStatus_ScheduleID(ScheduleTableID)
        osSaveGetScheduleTableStatus_ScheduleStatus(ScheduleStatus)
      osAPIError(E_OS_ACCESS, osdErrSGNoAccess);
      OS_SG_EXIT()
      osStatusTypeReturn = E_OS_ACCESS;
      return 0;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x037B)
   /* TR:SASR30:0038 Start Check disabled interrupts in GetScheduleTableStatus */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x037C)
        osSaveGetScheduleTableStatus_ScheduleID(ScheduleTableID)
        osSaveGetScheduleTableStatus_ScheduleStatus(ScheduleStatus)
      osAPIError(E_OS_DISABLEDINT, osdErrSGIntAPIDisabled);
      OS_SG_EXIT()
      osStatusTypeReturn = E_OS_DISABLEDINT;
      return 0;
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x037D)

   OS_SG_EXIT()

   osStatusTypeReturn = E_OK;         /* TR:SASR30:0134 Start *//* TR:SASR30:0135 Start *//* TR:SASR30:0136 Start *//* TR:SASR30:0174 Start *//* TR:SASR30:0175 Start */
   return osSTState[ScheduleTableID]; /* TR:SASR30:0134 End */  /* TR:SASR30:0135 End */  /* TR:SASR30:0136 End */  /* TR:SASR30:0174 End */  /* TR:SASR30:0175 End */  
}
/* TR:SASR30:0179 End */

/*-+--------------------------------------------------------------------------
 / osInitScheduleTables
 /
 / Funktion:
 /   Initializes the variables, used for schedule tables.
 / Context:
 /   Interrupts have to be disabled up to the system level at least.
 / Parameter:
 /   none
 / Returnvalue:
 /   none
 /--------------------------------------------------------------------------*/

osqFunc1 void osqFunc2 osInitScheduleTables(void)
{
   /* CovComment 4:  Function: osInitScheduleTables */
   ScheduleTableType stID;
   
   /* loop through all schedule tables */
   for (stID = 0; stID < osrNumberOfScheduleTables; stID++)
   {
      COVER(0x037E)
               
      if ((oskScheduleTableAutoStart[stID] & osActiveAppMode) == 0)
      {
         /* No Autostart */
         osSTNextTable[stID]     = INVALID_SCHEDULETABLE;
         osSTState[stID]         = SCHEDULETABLE_STOPPED; /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 */
         #if (osdScheduleTableSyncUsed != 0)
         osSTFlags[stID]         = osdHRST_NoSpecialInit;
         osSTDiffTime[stID]      = 0;
         COVER(0x037F)
         #endif
         COVER(0x0380)
      }
      else if (oskScheduleTableAutoStartType[stID] == osdScheduleTableAutostartRELATIVE)
      {
         /* Relative Autostart */
         osSTNextTable[stID]     = INVALID_SCHEDULETABLE;
         osSTState[stID]         = SCHEDULETABLE_RUNNING; /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 */
         #if (osdScheduleTableSyncUsed != 0)
         osSTFlags[stID]         = osdHRST_ForceAsync;
         osSTDiffTime[stID]      = 0;
         COVER(0x0381)
         #endif
         osResetCurrentEP(stID);
         COVER(0x0382)
         
         #if (osdNumberOfHiResSchedTabs > 0)
         #if (osdNumberOfScheduleTables > osdNumberOfHiResSchedTabs)
         COVER(0x0383)
         if (stID < osdNumberOfHiResSchedTabs)
         #endif
         {
            /* Set ST time */
            osSetSTTime(stID, (1 + oskSTMaxAllowed[stID]) - oskAutostartScheduleTableOffset[stID] )
            osSetTimeOfLastUpdate(stID, now); /* PRQA S 3682 */
            /* Insert into heap */
            osSetTargetTIPTime(osConvertST2TIP(stID), now);
            osAddToTargetTIPTime(osConvertST2TIP(stID), oskAutostartScheduleTableOffset[stID]);
            osInsertMinHeap(osConvertST2TIP(stID));
            COVER(0x0384)
         }
         #if (osdNumberOfScheduleTables > osdNumberOfHiResSchedTabs)
         else
         #endif
         #endif /* #if (osdNumberOfHiResSchedTabs > 0) */
         #if (osdNumberOfScheduleTables > osdNumberOfHiResSchedTabs)
         {         
            #if (osdScheduleTableSyncUsed != 0)
               /* Do the modulo only when the schedule table maximum value is below TickType maximum value */
               if((oskSTMaxAllowed[stID] + (TickType)1) == (TickType)0)
               {
                  TickType Zero = 0;
                  /* MISRA RULE 21.1 not violated: Rule 21.1 is not violated, static code checking is applied.
                     And the line below is fully intended: We want to get the negative of number in a finite ring,
                     and some compilers complained about the standard method (writing "-Offset").
                   */
                  osSTTime[stID] = Zero - oskAutostartScheduleTableOffset[stID];  /* PRQA S 3372 */
                  COVER(0x0385)
               }
               else
               {
                  osSTTime[stID] = (TickType) ((oskSTMaxAllowed[stID] + 1) - 
                                  (oskAutostartScheduleTableOffset[stID] % (oskSTMaxAllowed[stID] + 1)));
                  COVER(0x0386)
               }
            #endif
            /* initial offset needs no consideration here as we have a fake expiry point at zero
               if there is no user expiry point */
            osSTCounter[stID] = oskAutostartScheduleTableOffset[stID];
         }
         #endif /* #if (osdNumberOfScheduleTables > osdNumberOfHiResSchedTabs) */
      }
      else if (oskScheduleTableAutoStartType[stID] == osdScheduleTableAutostartABSOLUT)  
      {
         /* Absolute Autostart */
         osSTNextTable[stID]     = INVALID_SCHEDULETABLE;
         osSTState[stID]         = SCHEDULETABLE_RUNNING; /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 */
         #if (osdScheduleTableSyncUsed != 0)
         osSTFlags[stID]         = osdHRST_ForceAsync;
         osSTDiffTime[stID]      = 0;
         COVER(0x0387)
         #endif
         osResetCurrentEP(stID);
         COVER(0x0388)
         #if (osdNumberOfHiResSchedTabs > 0)
         #if (osdNumberOfScheduleTables > osdNumberOfHiResSchedTabs)
         COVER(0x0389)
         if (stID < osdNumberOfHiResSchedTabs)
         #endif
         {
            /* Set ST time */
            osSetSTTime(stID, (1 + oskSTMaxAllowed[stID]) - (oskAutostartScheduleTableOffset[stID] - now))
            osSetTimeOfLastUpdate(stID, now); /* PRQA S 3682 */
            /* Insert into heap */
            osSetTargetTIPTime(osConvertST2TIP(stID), (oskAutostartScheduleTableOffset[stID]));
            osInsertMinHeap(osConvertST2TIP(stID));
            COVER(0x038A)
         }
         #if (osdNumberOfScheduleTables > osdNumberOfHiResSchedTabs)
         else
         #endif
         #endif /* #if (osdNumberOfHiResSchedTabs > 0) */
         #if (osdNumberOfScheduleTables > osdNumberOfHiResSchedTabs)
         {
            #if (osdScheduleTableSyncUsed != 0)
               /* Do the modulo only when the schedule table maximum value is below TickType maximum value */
               if((oskSTMaxAllowed[stID] + (TickType)1) == (TickType)0)
               {
                  TickType Zero = 0;
                  /* MISRA RULE 21.1 not violated: Rule 21.1 is not violated, static code checking is applied.
                     And the line below is fully intended: We want to get the negative of number in a finite ring,
                     and some compilers complained about the standard method (writing "-Offset").
                   */
                  osSTTime[stID] = Zero - oskAutostartScheduleTableOffset[stID];  /* PRQA S 3372 */
                  COVER(0x038B)
               }
               else
               {
                  osSTTime[stID] = (TickType)((oskSTMaxAllowed[stID] + 1) - 
                                  (oskAutostartScheduleTableOffset[stID] % (oskSTMaxAllowed[stID] + 1)));
                  COVER(0x038C)
               }
            #endif
            /* System starts counters at 0, so this is equivalent with the relative start */
            osSTCounter[stID]  = oskAutostartScheduleTableOffset[stID]; 
         }
         #endif /* #if (osdNumberOfScheduleTables > osdNumberOfHiResSchedTabs) */
      }
      #if (osdScheduleTableSyncUsed != 0)
      else if (oskScheduleTableAutoStartType[stID] == osdScheduleTableAutostartSYNCHRON)  
      {
         /* Synchronous Autostart */
         osSTNextTable[stID]   = INVALID_SCHEDULETABLE;
         osSTState[stID]       = SCHEDULETABLE_WAITING; /* TR:SASR30:0295 *//* TR:SASR30:0301 */
         osSTFlags[stID]       = osdHRST_NoSpecialInit;
         osSTTime[stID]        = 0;      
         osSTDiffTime[stID]    = 0;
         osResetCurrentEP(stID);
         COVER(0x038D)

      } 
      #endif
      else 
      {
         /* This else is only here for MISRA, Rule 60. Intenionally left blank. */
         COVER(0x038E)
         ;
      }

   } /* for (all schedule tables) */
   
}


#if (osdScheduleTableSyncUsed != 0) /* TR:SASR30:0093 Start */

static osqFunc1 void osqFunc2 osSTUpdateTime(ScheduleTableType currentST, osTickTimeDiffType DiffToSet);
static osqFunc1 void osqFunc2 osSTUpdateTime(ScheduleTableType currentST, osTickTimeDiffType DiffToSet)
{
   /* CovComment 4:  Function: osSTUpdateTime */
   /*Correct the schedule table time*/
   TickType NewTime;
   if (DiffToSet>=0)   
   {
      NewTime = osSTTime[currentST] + ((TickType)DiffToSet);
   }
   else
   {
      NewTime = osSTTime[currentST] - ((TickType)-DiffToSet);
   }
   /*Detect value over/underflow*/
   if (DiffToSet >= 0) /* Actually, will never be called with (DiffSet==0) */
   {
      if (NewTime > oskSTMaxAllowed[currentST])
      {
         COVER(0x038F)
         /*correct the overflow of maxallowedvalue*/
         NewTime = NewTime - (TickType)oskSTMaxAllowed[currentST] - 1;
      }
      else if (NewTime < osSTTime[currentST])
      {
         COVER(0x0390)
         /*correct overflow of the maximum value in TickType*/
         NewTime = NewTime - (TickType)oskSTMaxAllowed[currentST] - 1;
      }
      else 
      { 
         /* This else is only here for MISRA, Rule 60. Intentionally left blank */
         COVER(0x0391)
         ;
      } 
   }
   else 
   {
      /*DiffToSet < 0 here, as it is !=0 and not >0*/
      if (NewTime > osSTTime[currentST])
      {
         COVER(0x0392)
         /*correct underflow*/
         NewTime += oskSTMaxAllowed[currentST] + 1;
      }
      ELSEWITHCOVER(0x0393)
   }
   /*Set the corrected time*/
   osSTTime[currentST] = NewTime;
}

/*
 *  Function: osSTCalculateSyncState
 *    Checks for the given schedule table, whether or not it is synchronous and
 *    stores the result in the variable osSTState[].
 *  Parameters:
 *    currentST:  Index of the current schedule table
 *  Return value:
 *    none
 *  Call context:
 *    Called inside the functions osSTWorkActions and osSyncScheduleTable only. 
 *    Interrupts are disabled up to the system level at least. The function is 
 *    called only for schedule tables that are running or running and synchronous. 
 *    All schedule tables, this function is called for, are explicitely synchronized 
 *    schedule tables.
 */

 /* MISRA RULE 8.10 VIOLATION: In some configurations, this function might be used from the same file only.
    Catching all these configurations is complex and error prone */
osqFunc1 void osqFunc2 osSTCalculateSyncState(ScheduleTableType currentST) /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osSTCalculateSyncState */

   /* Has the schedule table been set to asynchronous? */
   if ((osSTFlags[currentST] & osdHRST_ForceAsync) == 0)
   {
      /* NO: calculate the new status */
      if (osSTDiffTime[currentST] >=  (osTickTimeDiffType)oskPrecision[currentST]) 
      {
         COVER(0x0394)
         osSTState[currentST] = SCHEDULETABLE_RUNNING; /* TR:SASR30:0301 */
      }
      else if (osSTDiffTime[currentST] <= (-(osTickTimeDiffType)oskPrecision[currentST]))
      {
         COVER(0x0395)
         osSTState[currentST] = SCHEDULETABLE_RUNNING; /* TR:SASR30:0301 */
      }
      else
      {
         COVER(0x0396)
         osSTState[currentST] = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS; /* TR:SASR30:0301 */
      }
   }
   ELSEWITHCOVER(0x0397)
}

/*
 *  Function: osSTDoSyncStep
 *    Performs a synchronization step
 *  Parameters:
 *    currentST:  Index of the current schedule table
 *    RelOffs:    The relative offset to the next expiry point
 *    MaxRetard:  The value of the attribute MAXRETARD for this expiry point
 *    MaxAdvance: The value of the attribure MAXADVANCE for this expiry point
 *  Return value:
 *    The corrected relative offset to the next expity point
 *  Call context:
 *    Called inside the function osSTWorkActions only. Interrupts are disabled 
 *    up to the system level at least. The function is called only for schedule
 *    tables that are running or running and synchronous. All schedule tables,
 *    this function is called for, are explicitely synchronized schedule tables.
 */
/* MISRA RULE 14.1 VIOLATION: In some configurations, this function might be unused. Catching 
   all these cases is too complex and error prone 
 */
osqFunc1 TickType osqFunc2 osSTDoSyncStep(ScheduleTableType currentST, TickType RelOffs, TickType MaxRetard, TickType MaxAdvance) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osSTDoSyncStep */
   osTickTimeDiffType DiffToSet = osSTDiffTime[currentST];/* current deviation to global time */
   if(DiffToSet == 0)
   {
      COVER(0x0398)
      /* nothing to do, really */
      return RelOffs;
   }
   ELSEWITHCOVER(0x0399)

   if (DiffToSet>0)
   {
      if ((TickType)DiffToSet > MaxRetard)
      {
         COVER(0x039A)
         DiffToSet = (osTickTimeDiffType)MaxRetard; 
      }
      ELSEWITHCOVER(0x039B)
      RelOffs=(RelOffs - (TickType)DiffToSet);
   }
   else
   {
      /* this is the case (DiffToSet<0), 
        the case (DiffToSet==0) is handled above 
      */
      /* -MaxAdvance is always possible, checked by the generator */
      if (DiffToSet < -((osTickTimeDiffType)MaxAdvance))
      {
         COVER(0x039C)
         DiffToSet= - ((osTickTimeDiffType)MaxAdvance); 
      }
      ELSEWITHCOVER(0x039D)
      RelOffs=(RelOffs + (TickType)-DiffToSet);
   }

   /* Update schedule table time */
   osSTUpdateTime(currentST, DiffToSet);   
   /*Correct the remaining difference to the global time*/
   osSTDiffTime[currentST] -= DiffToSet;
        
   return RelOffs;
}

#endif /* #if (osdScheduleTableSyncUsed != 0) */ /* TR:SASR30:0093 End */
 
/* If there is a next schedule table for the currentST, copy all state from 
   currentST to the next - except osSTCounter and osSTCurrentIndex.
   State is corrected. 
 */ 
static osqFunc1 ScheduleTableType osqFunc2 osSTSwitchToNext(ScheduleTableType currentST);

static osqFunc1 ScheduleTableType osqFunc2 osSTSwitchToNext(ScheduleTableType currentST)
{
   /* CovComment 4:  Function: osSTSwitchToNext */
   ScheduleTableType next = osSTNextTable[currentST];
   if (next != INVALID_SCHEDULETABLE)
   {
      /* activate the next table */
      osSTNextTable[currentST] = INVALID_SCHEDULETABLE;
      
      #if (osdScheduleTableSyncUsed != 0)
         /* TR:SASR30:0182 Start The next schedule table derives synchrony from the current table */
         osSTTime[next]        = osSTTime[currentST];
         if (next>currentST)
         {
            COVER(0x039E)
            osSTUpdateTime(next,-1);
         }
         ELSEWITHCOVER(0x039F)
         osSTDiffTime[next]    = osSTDiffTime[currentST];
         osSTState[next]       = osSTState[currentST];
         /* TR:SASR30:0182 End */
      #else
         COVER(0x03A0)
         osSTState[next]       = SCHEDULETABLE_RUNNING; /* TR:SASR30:0288 *//* TR:SASR30:0294 */
      #endif
      
      /* stop the current schedule table*/
      osSTState[currentST]     = SCHEDULETABLE_STOPPED; /* TR:SASR30:0005 *//* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 *//* TR:SASR30:0293 */
   }
   else
   {
      COVER(0x03A1)
      next = currentST;
   }
   return next;
}



/*-+--------------------------------------------------------------------------
 / osWorkScheduleTables
 /
 / Funktion:
 /   Checks for schedule table actions and performs them if necessary. This
 /   function is called from the system timer ISR and from IncrementCounter().
 / Context:
 /   Interrupts are enabled. On level based systems, interrupts might be
 /   disabled up to the level of the caller.
 / Parameter:
 /   CounterID : The name of the counter, the schedule tables shall be 
 /               checked for.
 / Returnvalue:
 /   none
 /--------------------------------------------------------------------------*/
/* TR:SASR30:0002 Start */
/* TR:SASR30:0004 Start */
/* TR:SASR30:0129 Start */
/* TR:SASR30:0215 Start */
/* TR:SASR30:0219 Start */

/* MISRA RULE 14.1 VIOLATION: osWorkScheduleTables might be not called in some
 * configuration. Conditional compiling of the function would increase
 * the code complexity to unacceptable level (1503) */ 
osqFunc1 void osqFunc2 osWorkScheduleTables(CounterType CounterID) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osWorkScheduleTables */
   ScheduleTableType  StIdx;
   ScheduleTableType  currentST;
   ScheduleTableType  next;
   osbool             restart;
   osSTReactionType   react;
   TickType           diff;
#ifndef osdIncludeLibConfig
   osuint8 osHasBeenNexted[osrNumberOfScheduleTables];
#else
   /* declared in tcb.h */
#endif
   
   for(StIdx=0; StIdx<osrNumberOfScheduleTables; StIdx++)
   {
      COVER(0x03A2)
      osHasBeenNexted[StIdx] = 0;
   }
   
   StIdx = 0;/* Start with first schedule table */
   while (StIdx < osrNumberOfScheduleTables)
   {
      if(osHasBeenNexted[StIdx] == 0)
      {
         /* this if checks if the current ST has already been nexted to the previous one */
         /* then its potential action has already been performed (if initial offset is zero) */
         /* this if prevents the incrementation of the counter for a just nexted ST */
         if (oskCounterOfST[StIdx] == CounterID)
         {
            /* is the schedule table running? */
            if (osSTState[StIdx] >= SCHEDULETABLE_RUNNING)
            {
               COVER(0x03A3)
               #if (osdScheduleTableSyncUsed != 0)
               COVER(0x03A4)
               osSTUpdateTime(StIdx,1);
               #endif           
            
               /*Yes: decrement the counter*/
               osSTCounter[StIdx]--; /* TR:SASR30:0216 */
                        
               /*expiry point reached?*/
               if (osSTCounter[StIdx] == 0)
               {
                  COVER(0x03A5)
                  /* Yes: perform all actions of this expiry point */
                  currentST = StIdx;
                  do 
                  {
                     COVER(0x03A6)
                     restart=0;
                     /*loop for all actions at this expiry point*/
                     react = osSTWorkActions(&diff, osSTCurrentIndex[currentST]);
    
                     /* Now what? */   
                     switch (react)
                     {
                        case osdSTReact_Continue   :  
                        case osdSTReact_InitialDelay :
                        case osdSTReact_FinalDelay :
                           /* Normal EP of a table 
                           Just add the time offset to next ep to current time and continue */
                           COVER(0x03A7)
                           osSTCounter[currentST] = diff; /* TR:SASR30:0005 */ /* TR:SASR30:0066 */
                           /* point to the next expiry point action */
                           osSTCurrentIndex[currentST]++;
                           break;
                        
                        case osdSTReact_Repeat     :  
                        /* this is the end of a repeating non-sync table 
                           reset values and restart
                        */
                           /* TR:SASR30:0066 Start */
                           next = osSTSwitchToNext(currentST);
                           if (next != currentST)
                           {
                              COVER(0x03A8)
                              /* there is a next'ed schedule table */
                              /* mark the next schedule table as the current one */
                              currentST = next;
                              /* store the information that the current ST has been nexted */
                              osHasBeenNexted[currentST] = 1;
                           }
                           ELSEWITHCOVER(0x03A9)

                           /* initialize the expiry point action pointer */
                           osSTCurrentIndex[currentST] = oskSTStartIndex[currentST];
                           /* set restart to execute osSTWorkActions again on the expiry point at offset zero */
                           restart = 1;
                           /* TR:SASR30:0066 End */
                           break;
    
                        case osdSTReact_Stop       :  
                        /* this is the end of a non-repeating non-sync table 
                           if it has a next schedule, do the same as for a repeating schedule table
                           otherwise, stop the schedule table
                        */
                           /* get ID of a potentially next'ed scheduletable */
                           next = osSTSwitchToNext(currentST); /* TR:SASR30:0182 Call of osSTSwitchToNext */
                           if (next == currentST)
                           {
                              COVER(0x03AA)
                              /* a next scheduletable does not exist -> simple stop the current one */
                              osSTState[currentST] = SCHEDULETABLE_STOPPED;   /* TR:SASR30:0005 *//* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 *//* TR:SASR30:0293 */
                           }
                           else
                           {
                              COVER(0x03AB)
                              /* there is a next'ed schedule table */
                              /* mark the next schedule table as the current one */
                              currentST = next;
                              /* TR:SASR30:0182 Start Initialize the expiry point action pointer */
                              osSTCurrentIndex[currentST] = oskSTStartIndex[currentST];
                              osHasBeenNexted[currentST] = 1;
                              /* set restart to execute osSTWorkActions again on the expiry point at offset zero */
                              restart = 1;
                              /* TR:SASR30:0182 End */ 
                           }
                           break;

                        default:
                           COVER(0x03AC)
                           osSysErrAssertFailed(osdErrWSUnknownReaction) 
                           /* MISRA RULE 14.1 VIOLATION: break is never reached because osSysErrAssertFailed
                            * never returns (3201)
                            */
                           break;    /* PRQA S 3201 */
                        
                     } /* switch */
                    
                  } while (restart != 0);
               } /* if (osSTState[StIdx] >= SCHEDULETABLE_RUNNING) */
               ELSEWITHCOVER(0x03AD)
            } /* if (osSTCounter[StIdx] == 0) */
            ELSEWITHCOVER(0x03AE)
         } /* if (oskCounterOfST[StIdx] == CounterID) */
         ELSEWITHCOVER(0x03AF)
      } /* (osHasBeenNexted[StIdx] == 0) */
      ELSEWITHCOVER(0x03B0)
      StIdx++; /* increment schedule table index */

      
   }/*while (StIdx < osrNumberOfScheduleTables) */
}
/* TR:SASR30:0219 End */
/* TR:SASR30:0215 End */
/* TR:SASR30:0129 End */
/* TR:SASR30:0004 End */
/* TR:SASR30:0002 End */

#if (osdScheduleTableSyncUsed != 0)



/*-+--------------------------------------------------------------------------
 / SyncScheduleTable
 / =================
 /
 / Syntax: 
 /    StatusType SyncScheduleTable(
 /                                  ScheduleTableType SchedTableID, 
 /                                  GlobalTimeTickType GlobalTime
 /                                )
 / Parameter (In):
 /   ScheduleTableType ScheTableID,
 /   GlobalTimeTickType GlobalTime
 / Parameter (Out):
 /   none
 / Description:
 /   This service provides the operating system with the current global time.
 /   It is used to synchronize the processing of the schedule table to global
 /   time.
 / Return value (depends on OIL-Attribute STATUS):
 /    STANDARD:
 /       - No error, E_OK
 /    EXTENDED: 
 /       - <ScheduleTableID> is not valid or cannot be synchronized, E_OS_ID
 /       - <GlobalTime> is too big, E_OS_VALUE
 /       - The state of the schedule table is so that in cannot be synchronized,
 /         E_OS_STATE
 /       - The service has been called with interrupts disabled, 
 /         E_OS_DISABLEDINT
 / Scalability Classes:
 /    SC2, SC4
 /--------------------------------------------------------------------------*/
osqFunc1 StatusType osqFunc2 osSyncScheduleTable(ScheduleTableType SchedTableID, GlobalTimeTickType GlobalTime)
{
   /* CovComment 4:  Function: osSyncScheduleTable */
#if (osdNumberOfScheduleTables != osdNumberOfHiResSchedTabs)   
   TickTypeTmp osHeapDiffCaster     ;
   TickType    Zero; /*This variable is needed to prevent from compiler warnings only*/
#endif

   OS_SY_ENTRY()
#if (osdNumberOfScheduleTables != osdNumberOfHiResSchedTabs)   
   Zero = 0;
   COVER(0x03B1)
#endif
   
   COVER(0x03B2)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in SyncScheduleTable */
   /* TR:SASR30:0336 Start Context check in SyncScheduleTable */
   if ((osdValidCtx_SyncScheduleTable & osCurrentContext) == 0)
   {
      COVER(0x03B3)
        osSaveSyncScheduleTable_ScheduleID(SchedTableID)
        osSaveSyncScheduleTable_GlobalTime(GlobalTime)
      osAPIError(E_OS_CALLEVEL, osdErrSYCallContext);
      OS_SY_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x03B4)

   if (SchedTableID >= osrNumberOfScheduleTables)
   {
      COVER(0x03B5)
        osSaveSyncScheduleTable_ScheduleID(SchedTableID)
        osSaveSyncScheduleTable_GlobalTime(GlobalTime)
      osAPIError(E_OS_ID, osdErrSYWrongID);
      OS_SY_EXIT()
      return E_OS_ID;
   }
   ELSEWITHCOVER(0x03B6)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in SyncScheduleTable */
   if (((oskApplScheduleTableAccess[SchedTableID] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x03B7)
      osSaveSyncScheduleTable_ScheduleID(SchedTableID)
      osSaveSyncScheduleTable_GlobalTime(GlobalTime)
      osAPIError(E_OS_ACCESS, osdErrSYNoAccess);
      OS_SY_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x03B8)

#ifndef osdSyncScheduleTableAllowsDisabledInterrupts
   /* TR:SASR30:0038 Start Check disabled interrupts in SyncScheduleTable */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x03B9)
      osSaveSyncScheduleTable_ScheduleID(SchedTableID)
      osSaveSyncScheduleTable_GlobalTime(GlobalTime)
      osAPIError(E_OS_DISABLEDINT, osdErrSYIntAPIDisabled);
      OS_SY_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x03BA)
#endif /* osdSyncScheduleTableAllowsDisabledInterrupts */
   
   if (oskSTSyncKind[SchedTableID]!=osdSTSyncExplicit)
   {
      COVER(0x03BB)
      osSaveSyncScheduleTable_ScheduleID(SchedTableID)
      osSaveSyncScheduleTable_GlobalTime(GlobalTime)
      osAPIError(E_OS_ID, osdErrSYSyncKindNotExplicit);
      OS_SY_EXIT()
      return E_OS_ID;   
   }
   ELSEWITHCOVER(0x03BC)

   if (GlobalTime>oskSTMaxAllowed[SchedTableID])
   {
      COVER(0x03BD)
      osSaveSyncScheduleTable_ScheduleID(SchedTableID)
      osSaveSyncScheduleTable_GlobalTime(GlobalTime)
      osAPIError(E_OS_VALUE, osdErrSYGlobalTimeTooBig);
      OS_SY_EXIT()
      return E_OS_VALUE;
   }
   ELSEWITHCOVER(0x03BE)
   
   if (osSTState[SchedTableID] < SCHEDULETABLE_WAITING)
   {
      COVER(0x03BF)
      osSaveSyncScheduleTable_ScheduleID(SchedTableID)
      osSaveSyncScheduleTable_GlobalTime(GlobalTime)
      osAPIError(E_OS_STATE, osdErrSYSTNotRunning);
      COVER(0x03C0)
      OS_SY_EXIT()
      return E_OS_STATE;
   }
   ELSEWITHCOVER(0x03C1)

   /*Is the schedule table running?*/
   if ((osSTState[SchedTableID] == SCHEDULETABLE_RUNNING) || 
       (osSTState[SchedTableID] == SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS))
   {
      #if (osdNumberOfScheduleTables != osdNumberOfHiResSchedTabs)
      {          
         osSTFlags[SchedTableID] &= (osHRSTFlagsType)~osdHRST_ForceAsync;
          
         /*Yes: compute time difference between global and local time*/
         /*Difference between global time and local time is in the range (-maxallowedvalue ... +maxallowedvalue)*/
         /*This difference might not fit into TickType, so first check the sign.*/
         if(GlobalTime > osSTTime[SchedTableID])
         {
            /*Result will be positive*/
            osHeapDiffCaster.unsignedNumber = GlobalTime - osSTTime[SchedTableID];
            /*Result > maxallowedvalue/2?*/
            if( osHeapDiffCaster.unsignedNumber > (oskSTMaxAllowed[SchedTableID] / 2))
            {
               COVER(0x03C2)
                /*Yes: Correction into the opposite direction is faster*/
               osHeapDiffCaster.unsignedNumber -= oskSTMaxAllowed[SchedTableID] + 1;
            }
            ELSEWITHCOVER(0x03C3)
         }
         else
         {
            /*Result will be negative, consider the absolute value*/
            osHeapDiffCaster.unsignedNumber = osSTTime[SchedTableID] - GlobalTime;
            /*Abs(Result) > maxallowedvalue/2 + maxallowedvalue%2 ?*/
            if( (osHeapDiffCaster.unsignedNumber) > 
                ((oskSTMaxAllowed[SchedTableID] / 2) + (oskSTMaxAllowed[SchedTableID] % 2))
              )
            {
               COVER(0x03C4)
                /*Yes: Correction into the opposite direction is faster*/
                osHeapDiffCaster.unsignedNumber -= oskSTMaxAllowed[SchedTableID] + 1;
            }
            ELSEWITHCOVER(0x03C5)
            /*now flip the sign*/
            osHeapDiffCaster.unsignedNumber = Zero - osHeapDiffCaster.unsignedNumber;
         }
    
         COVER(0x03C6)
         /* KB begin osekHWosDisableTimProtInterrupt (default) */
         #if osdTimingProtectionUsed
         #error "Timing Protection not supported"
         #endif        
         /* KB end osekHWosDisableTimProtInterrupt */
    
         /* Interpret the difference as a signed number now */
         osSTDiffTime[SchedTableID] = osHeapDiffCaster.signedNumber;
          
         /* Now check, whether the schedule table is sychronous and update the state accordingly*/
         osSTCalculateSyncState(SchedTableID);
         COVER(0x03C7)
      }
      #endif /* (osdNumberOfScheduleTables != osdNumberOfHiResSchedTabs) */
   }
   /*Is the schedule table waiting?*/
   else if (osSTState[SchedTableID] == SCHEDULETABLE_WAITING)
   {
      COVER(0x03C8)
      /*Yes: synchronize and start it */

      /* KB begin osekHWosDisableTimProtInterrupt (default) */
      #if osdTimingProtectionUsed
      #error "Timing Protection not supported"
      #endif        
      /* KB end osekHWosDisableTimProtInterrupt */
      #if (osdNumberOfScheduleTables != osdNumberOfHiResSchedTabs)
      {
         osSTState[SchedTableID] = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS; /* TR:SASR30:0301 */
         osSTFlags[SchedTableID] = osdHRST_NoSpecialInit;
         osSTTime[SchedTableID]  = GlobalTime;
 
         /* maximum value for osSTCounter: oskSTMaxAllowed + 1, so overflow to 0 possible */
         /* osWorkScheduleTables correctly considers this overflow */
         osSTCounter[SchedTableID] = (1 + oskSTMaxAllowed[SchedTableID]) - GlobalTime;
 
         osSTCurrentIndex[SchedTableID]= oskSTStartIndex[SchedTableID];         
      } /* if ((oskCounterOfST[ScheduleTableID]!=HiResSchedTabCounter) ... else ... */
      #endif
        
   } /*   else if (osSTState[SchedTableID] == SCHEDULETABLE_WAITING) ... else ...*/ 
   else
   { 
      /* This else is only here for MISRA, Rule 60. Intenionally left blank. */
      COVER(0x03C9)
      ;
   }
    /* else: in standard status, simply ignore the call. */

   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_SY_EXIT()
   
   return E_OK;
} /* end of osSyncScheduleTable */


/*-+--------------------------------------------------------------------------
 / SetScheduleTableAsync
 / =====================
 /
 / Syntax: 
 /   StatusType SetScheduleTableAsync(ScheduleTableType ScheduleID)
 / Parameter (In):
 /   ScheduleTableType ScheduleID,
 / Parameter (Out):
 /   none
 / Description:
 /   The schedule table, defined by ScheduleID, is set asynchronous. If the
 /   schedule table is running, it keeps running.
 / Return value (depends on OIL-Attribute STATUS):
 /    STANDARD:
 /       - No error, E_OK
 /    EXTENDED: 
 /       - <ScheduleID> is not valid, E_OS_ID
 /       - The service has been called with interrupts disabled, 
 /         E_OS_DISABLEDINT
 / Scalability Classes:
 /    SC2, SC4
 /--------------------------------------------------------------------------*/
osqFunc1 StatusType osqFunc2 osSetScheduleTableAsync(ScheduleTableType ScheduleID)
{
   /* CovComment 4:  Function: osSetScheduleTableAsync */

   OS_AY_ENTRY()
   COVER(0x03CA)

   COVER(0x03CB)
   /* check call context */
   /* TR:SASR30:0035 Start Context check in SetScheduleTableAsync */
   /* TR:SASR30:0336 Start Context check in SetScheduleTableAsync */
   if ((osdValidCtx_SetScheduleTableAsync & osCurrentContext) == 0)
   {
      COVER(0x03CC)
      osSaveSetScheduleTableAsync_ScheduleID(ScheduleID)
      osAPIError(E_OS_CALLEVEL, osdErrAYCallContext);
      OS_AY_EXIT()
      return E_OS_CALLEVEL;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x03CD)

   if (ScheduleID >= osrNumberOfScheduleTables)
   {
      COVER(0x03CE)
      osSaveSetScheduleTableAsync_ScheduleID(ScheduleID)
      osAPIError(E_OS_ID, osdErrAYWrongID);
      OS_AY_EXIT()
      return E_OS_ID;
   }
   ELSEWITHCOVER(0x03CF)
   /* check access rights for this object */
   /* TR:SASR30:0021 Start Check access rights in SetScheduleTableAsync */
   if (((oskApplScheduleTableAccess[ScheduleID] & (1UL << osaActiveApplicationID)) == 0))
   {
      COVER(0x03D0)
      osSaveSetScheduleTableAsync_ScheduleID(ScheduleID)
      osAPIError(E_OS_ACCESS, osdErrAYNoAccess);
      OS_AY_EXIT()
      return E_OS_ACCESS;
   }
   /* TR:SASR30:0021 End */
   ELSEWITHCOVER(0x03D1)

   /* TR:SASR30:0038 Start Check disabled interrupts in SetScheduleTableAsync */
   if (osaIntAPIStatus != 0)
   {
      COVER(0x03D2)
      osSaveSetScheduleTableAsync_ScheduleID(ScheduleID)
      osAPIError(E_OS_DISABLEDINT, osdErrAYIntAPIDisabled);
      OS_AY_EXIT()
      return E_OS_DISABLEDINT; /* TR:SOSK22:0074 */
   }
   /* TR:SASR30:0038 End */
   ELSEWITHCOVER(0x03D3)

   /* KB begin osekHWosDisableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosDisableTimProtInterrupt */


   if((osSTState[ScheduleID] == SCHEDULETABLE_RUNNING) || 
      (osSTState[ScheduleID] == SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS))
   {
      /*set asynchronous*/
      osSTState[ScheduleID]     = SCHEDULETABLE_RUNNING; /* TR:SASR30:0295 *//* TR:SASR30:0301 */
      osSTFlags[ScheduleID]    |= osdHRST_ForceAsync;
      osSTDiffTime[ScheduleID]  = 0;
   }
   ELSEWITHCOVER(0x03D4)
   /*else: simply ignore the call in all other states*/

   /* KB begin osekHWosEnableTimProtInterrupt (default) */
   #if osdTimingProtectionUsed
   #error "Timing Protection not supported"
   #endif        
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_AY_EXIT()

   return E_OK;
}

#endif /* #if (osdScheduleTableSyncUsed != 0)*/

#else /*(osdNumberOfScheduleTables > 0)*/

/* API functions must be available even without schedule tables as the safety wrappers do not kow about the configuration */

/* MISRA RULE 14.1 violated: (comment 1503) In SafeContext implementations all APIs 
 * are encapsulated in wrappers. This wrappers belong to static ASIL code and must exist, 
 * even if they are not used in a project. 
 */
osqFunc1 StatusType osqFunc2 osStartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset) /* PRQA S 1503 */
{
   osdDummyRead(ScheduleTableID) /* PRQA S 3199 */
   osdDummyRead(Offset)          /* PRQA S 3199 */
   return E_OK;
}
osqFunc1 StatusType osqFunc2 osStartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Tickvalue) /* PRQA S 1503 */
{
   osdDummyRead(ScheduleTableID) /* PRQA S 3199 */
   osdDummyRead(Tickvalue)       /* PRQA S 3199 */
   return E_OK;
}
osqFunc1 StatusType osqFunc2 osStopScheduleTable(ScheduleTableType ScheduleTableID) /* PRQA S 1503 */
{
   osdDummyRead(ScheduleTableID) /* PRQA S 3199 */
   return E_OK;
}
osqFunc1 StatusType osqFunc2 osNextScheduleTable(ScheduleTableType ScheduleTableID_current, ScheduleTableType ScheduleTableID_next ) /* PRQA S 1503 */
{
   osdDummyRead(ScheduleTableID_current)  /* PRQA S 3199 */
   osdDummyRead(ScheduleTableID_next)     /* PRQA S 3199 */
   return E_OK;
}
osqFunc1 ScheduleTableStatusType osqFunc2 osGetScheduleTableStatus(ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus) /* PRQA S 1503 */
{
   osdDummyRead(ScheduleTableID) /* PRQA S 3199 */
   osdDummyRead(ScheduleStatus)  /* PRQA S 3199 */
   return E_OK;
}
#endif /*(osdNumberOfScheduleTables > 0)*/


/* KB begin osekEndOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
/* Reset to default section TR:SPMF49:0004 */
#pragma SET_CODE_SECTION()
#endif
/* KB end osekEndOfCModule */

/* END OF MODULE atostime.c */
