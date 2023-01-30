/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osektime.c
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.45
|
|  Description: osek timer handling
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2012 Vector Informatik GmbH        All rights reserved.
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

/* CovComment 0:  file: osektime.c */

/* KB begin osekStartOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_CODE_SECTION(".oscode") /* TR:SPMF49:0001 */ /* TR:SPMF49:0002 */
#endif
/* KB end osekStartOfCModule */

#if (osdUseHeap) && (osdNumberOfAlarms + osdNumberOfHiResSchedTabs > 0)

/*-+--------------------------------------------------------------------------
 / osInitMinHeap
 / Funktion:
 /   - initialize empty minimum heap
 / Context:
 /   OS initialization.
 /   This function is meant to be OS internal.
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/
static osqFunc1 void osqFunc2 osInitMinHeap(void);
static osqFunc1 void osqFunc2 osInitMinHeap(void)
{
   /* CovComment 4:  Function: osInitMinHeap */
   COVER(0x02C9)
   osAlarmHeapCount = 0;
}

/*-+--------------------------------------------------------------------------
 / osClimbUpMinHeap
 / Funktion:
 /   - move last element up to correct position
 / Context:
 /   Interrupts are disabled up to the system level at least.
 /   This function is meant to be OS internal.
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/

static osqFunc1 void osqFunc2 osClimbUpMinHeap(osAlarmIndexType i);
static osqFunc1 void osqFunc2 osClimbUpMinHeap(osAlarmIndexType i)
{
   /* CovComment 4:  Function: osClimbUpMinHeap */
   osHeapType hItem;
   osAlarmIndexType iPreIdx;

   COVER(0x02CA)
   hItem = osAlarmHeap[i];  /* copy (last) item */
   while (i != 0)
   {
      COVER(0x02CB)
      /* calculate index of predecessor */
      iPreIdx = (osAlarmIndexType)(((osAlarmIndexType)(i-1)) >> 1U);
   
      osdIF_COUNTER( osGetHeapTime(hItem), >=, osGetHeapTime(osAlarmHeap[iPreIdx]))
      {
         COVER(0x02CC)
         break;   /* correct position found */
      }
      ELSEWITHCOVER(0x02CD)
      osdENDIF_COUNTER

      /* swap items */
      osAlarmHeap[i] = osAlarmHeap[iPreIdx];
      i = iPreIdx;
      COVER(0x02CE)
   }
   osAlarmHeap[i] = hItem;   /* insert at correct position */
   COVER(0x02CF)
}


/*-+--------------------------------------------------------------------------
 / osClimbDownMinHeap
 / Funktion:
 /   - move element i down to correct position
 / Context:
 /   Interrupts are disabled up to the system level at least.
 /   This function is meant to be OS internal.
 / Parameter:     i = element index
 / Returnvalue:
 /--------------------------------------------------------------------------*/

static osqFunc1 void osqFunc2 osClimbDownMinHeap(osAlarmIndexType i);
static osqFunc1 void osqFunc2 osClimbDownMinHeap(osAlarmIndexType i)
{
   /* CovComment 4:  Function: osClimbDownMinHeap */
   osHeapType hItem;
   osAlarmIndexType iPostIdx;
   COVER(0x02D0)
   iPostIdx = (osAlarmIndexType)(((osAlarmIndexType)2*i) + (osAlarmIndexType)1);/*lint !e734*/
   /*
    * Info 734 Loss of precision (assignment)
    * The number of alarms is checked to be less than 2^(sizeof(osAlarmIndexType)-1).
    * So no overflow can occur here.
    */
   hItem = osAlarmHeap[i];  /* copy root item */
   while (iPostIdx < osAlarmHeapCount)
   {
      COVER(0x02D1)
      /* MISRA RULE 21.1 not violated: (3 times) QAC may state that the array osAlarmHeap is definitely (3685) or 
       * appropriately (3689) indexed with an out or bounds value. However, QAC cannot see that this is prevented 
       * by the comparison of iPostIdx with osAlarmHeapCount above. The variable osAlarmHeapCount is in the range 
       * of 0..NumberOfAlarms while osAlarmHeap has size NumberOfAlarms+1. */
      osdIF_COUNTER(osGetHeapTime(osAlarmHeap[iPostIdx]), > , osGetHeapTime(osAlarmHeap[iPostIdx+1])) /* PRQA S 3685 */
      {
         COVER(0x02D2)
         iPostIdx++;   /* set iPostIdx to smaller successor */

      }
      ELSEWITHCOVER(0x02D3)
      osdENDIF_COUNTER

      osdIF_COUNTER(osGetHeapTime(osAlarmHeap[iPostIdx]), >= , osGetHeapTime(hItem)) /* PRQA S 3689 */
      {
         COVER(0x02D4)
         break;        /* correct position found */

      }
      ELSEWITHCOVER(0x02D5)
      osdENDIF_COUNTER

      osAlarmHeap[i] = osAlarmHeap[iPostIdx]; /* PRQA S 3689 */
      i = iPostIdx;
      iPostIdx = (osAlarmIndexType)(((osAlarmIndexType)2*i) + (osAlarmIndexType)1);/*lint !e734, same arguments as above*/
   }
   COVER(0x02D6)
   osAlarmHeap[i] = hItem;
}


/*-+--------------------------------------------------------------------------
 / osInsertMinHeap
 / Funktion:
 /   - insert new item
 / Context:
 /   Interrupts are disabled up to the system level at least.
 /   This function is meant to be OS internal.
 / Parameter:     newItem = item to insert
 / Returnvalue:
 /--------------------------------------------------------------------------*/

/* MISRA RULE 8.10 VIOLATION: Depending on the configuration the function osInsertMinHeap is called by several modules
 * or only by this module. A static implementation in these cases would increase code complexity, too much.
 */
osqFunc1 void osqFunc2 osInsertMinHeap(osHeapType newItem) /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osInsertMinHeap */
   osAlarmHeap[osAlarmHeapCount] = newItem;  /* insert new item at last position */
   osAlarmHeapCount++;
   osClimbUpMinHeap((osAlarmIndexType)(osAlarmHeapCount-1));  /* climb up until correct position reached */
   COVER(0x02D7)
}



/*-+--------------------------------------------------------------------------
 / osRemoveMinItemMinHeap
 / Funktion:
 /   - get minimum item and remove item from heap
 / Context:
 /   Interrupts are disabled up to the system level at least.
 /   This function is meant to be OS internal.
 / Parameter:
 / Returnvalue: index of minimum item
 /--------------------------------------------------------------------------*/

static osqFunc1 osHeapType osqFunc2 osRemoveMinItemMinHeap(void);
static osqFunc1 osHeapType osqFunc2 osRemoveMinItemMinHeap(void)
{
   /* CovComment 4:  Function: osRemoveMinItemMinHeap */
   osHeapType hItem;

   hItem = osAlarmHeap[0];   /* copy first = minimum item */
   osAlarmHeapCount--;
   osAlarmHeap[0] = osAlarmHeap[osAlarmHeapCount];   /* move last element to first position */
   osClimbDownMinHeap(0);   /* climb down until correct position reached */
   COVER(0x02D8)
   return hItem;
}

/*-+--------------------------------------------------------------------------
 / osRemoveItemMinHeap
 / Funktion:
 /   - find and remove Item
 / Context:
 /   Interrupts are disabled up to the system level at least.
 /   This function is meant to be OS internal.
 / Parameter:    aItem   = Item to remove
 / Returnvalue:   osdFALSE = Item not found
 /                osdTRUE = Item found
 /                (for HiRes:)
 /                1 = Min Item did not change
 /                2 = Min Item did change (call osSetTimerInterruptPoint)
 /                3 = Heap is empty now (call osClearTimerInterruptPoint)
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 VIOLATION: The function osRemoveItemMinHeap might not be 
 *  called in some configurations. Conditional compiling of the function 
 *  would increase the code complexity to unacceptable level (1503).
 */
osqFunc1 osuint8 osqFunc2 osRemoveItemMinHeap(osHeapType aItem) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osRemoveItemMinHeap */
   osAlarmIndexType iPreIdx;
   osAlarmIndexType i = 0;

   COVER(0x02D9)
   osAlarmHeap[osAlarmHeapCount] = aItem;
   /* now the following loop will always terminate without range control */

   for (;;)
   {
      if (osAlarmHeap[i] == aItem)
      {
         COVER(0x02DA)
         break;   /* found! */
      }
      ELSEWITHCOVER(0x02DB)
      i++;
   }
#if osdEnableAssertions
   if (i >= osAlarmHeapCount)
   {
      COVER(0x02DC)
       return 0;/*heap item not found*/
   }
   ELSEWITHCOVER(0x02DD)
#endif
   COVER(0x02DE)
   osAlarmHeapCount--;
   osAlarmHeap[i] = osAlarmHeap[osAlarmHeapCount];  /* move last item to found item */
   if (i > 0) /* (if heap element has predecessor) check array boundaries */
   {
      COVER(0x02DF)
      iPreIdx =  (osAlarmIndexType)(((osAlarmIndexType)(i-1)) >> 1U);

      osdIF_COUNTER(osGetHeapTime(osAlarmHeap[i]), < , osGetHeapTime(osAlarmHeap[iPreIdx]))
      {
         (void) osClimbUpMinHeap(i);
         COVER(0x02E0)
         return 1;
      }
      ELSEWITHCOVER(0x02E1)
      osdENDIF_COUNTER
   }
   ELSEWITHCOVER(0x02E2)
   
   osClimbDownMinHeap(i);  /* climb down until correct position reached */
   COVER(0x02E3)
   return 1;
}


/* TR:SPMF24:0007 Start */
#if ((0 == osdUserDefinedSystemTimer) && ((osdUseHighResolutionTimer == 0) || (osdAlarmsOnHiResSystemTimer > 0)))
/*-+--------------------------------------------------------------------------
 / osWorkAlarms
 / Funktion:
 /   - execute Alarms
 / Context:
 /   Interrupts are enabled.
 /   This function is meant to be OS internal.
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/
/* MISRA RULE 8.10 VIOLATION: (2 times) The function osWorkAlarms is general code for 
 * differend platform specific OS implementations. Depending on the implementation,
 * the calling function might be located in the same file or be generated 
 * (i.e. in tcb.c). Making the function static for only some implementations would
 * increase code complexity too much. */
#if (osdUseHighResolutionTimer == 0)
osqFunc1 void osqFunc2 osWorkAlarms(void)   /* PRQA S 1505 */
#else
osqFunc1 void osqFunc2 osWorkAlarm(osTIPType alarmID)   /* PRQA S 1505 */
#endif
{
   /* CovComment 4:  Function: osWorkAlarms */
#if (osdUseHighResolutionTimer == 0)
   AlarmType alarmID;

   while (osGetActiveAlarmCount() != 0)
   {
      COVER(0x02E4)
      alarmID = osGetFirstAlarm();

      /* is timer expired? */
      osdIF_COUNTER(osGetSystemCounter(), >= , osAlarmTime[alarmID])
      {
         COVER(0x02E5)
         (void)osRemoveMinItemMinHeap();  /* remove alarm */
         /* alarm has become due now: work actions */
#endif
#if (osdNumberOfVarAlarms > 0)
         COVER(0x02E6)
#if (osdNumberOfVarAlarms < osdNumberOfAlarms)
         COVER(0x02E7)
         if (alarmID < osrNumberOfVarAlarms)
         {
            COVER(0x02E8)
#endif
            if (osAlarmCycleTime[alarmID] != 0)
            {
               COVER(0x02E9)
               /* cyclic alarm */
               osAlarmTime[alarmID] += osAlarmCycleTime[alarmID];
               osInsertMinHeap(alarmID);      /* reinsert  TR:SPMF20:0015 */
            }
            else
            {
               COVER(0x02EA)
               osAlarmActivated[alarmID]= 0;
            }
#endif
#if (osdNumberOfVarAlarms < osdNumberOfAlarms)
            COVER(0x02EB)
#if (osdNumberOfVarAlarms > 0)
            COVER(0x02EC)
         }
         else
#else
         COVER(0x02ED)
#endif
         {
            if (oskStaticAlarmCycleTime[alarmID] != 0)
            {
               /* cyclic timer  */
               COVER(0x02EE)
               osAlarmTime[alarmID] += oskStaticAlarmCycleTime[alarmID];
               osInsertMinHeap(alarmID);      /* reinsert  TR:SPMF20:0015 */
            }
            else
            {
               COVER(0x02EF)
               osAlarmActivated[alarmID]= 0;
            }
         }
#else
         COVER(0x02F0)
#endif

#if (osdNumberOfAlarmSetEvent > 0)
         if (oskAlarmAction[alarmID] == osdAlarmActionSetEvent)
         {
            COVER(0x02F1)
            /* event timer */
            (void) osSysSetEvent(oskAlarmTask[alarmID], oskAlarmEvent[alarmID]); 
         }
         else /* alarm action is not set event */
         {
            COVER(0x02F2)
#else 
            COVER(0x02F3)
#endif
#if (osdNumberOfAlarmCallback > 0)
            if (oskAlarmAction[alarmID] == osdAlarmActionCallback)
            {
               COVER(0x02F4)
               (oskAlarmCallback[alarmID])(); /* TR:SOSK22:0107 */
            }
            else /* alarm action is not alarm callback */
            {
               COVER(0x02F5)
#else 
               COVER(0x02F6)
#endif
#if (osdNumberOfAlarmIncrementCounter > 0)
               if (oskAlarmAction[alarmID] == osdAlarmActionIncrementCounter)
               {
                  COVER(0x02F7)
                  (void)osIncrementCounter(oskAlarmIncrementCounterID[alarmID]);
               }
               else /* alarm action is not increment counter */
               {
                  COVER(0x02F8)
#else 
                  COVER(0x02F9)
#endif
#if (osdNumberOfAlarmActivateTask > 0)
                  COVER(0x02FA)
                  (void) osSysActivateTask(oskAlarmTask[alarmID]);
#endif
#if (osdNumberOfAlarmIncrementCounter > 0)
               } /* end of else path of (oskAlarmAction[alarmID] == osdAlarmActionIncrementCounter) */
#endif
#if (osdNumberOfAlarmCallback > 0)
            } /* end of else path of (oskAlarmAction[alarmID] == osdAlarmActionCallback) */
#endif
#if (osdNumberOfAlarmSetEvent > 0)
         } /* end of else path of (oskAlarmAction[alarmID] == osdAlarmActionSetEvent) */
#endif
#if (osdUseHighResolutionTimer == 0)
      }
      else /* osdIF_COUNTER */
      {
         COVER(0x02FB)
         break;
      }osdENDIF_COUNTER
      COVER(0x02FC)
   }/*while*/

   COVER(0x02FD)
#endif

} /* END OF osWorkAlarms */
#endif /* (0 == osdUserDefinedSystemTimer) */
/* TR:SPMF24:0007 End */


#if (osdUseHighResolutionTimer == 1)
osqFunc1 void osqFunc2 osWorkTIPs(void)
{
   osTIPType TIP_ID;
   osbool    osStopWorkTIPs;
   
   /* Anything to do? */
   if (osGetActiveAlarmCount() == 0)
   {
      /* Nothing to do, end this routine */
      osClearTimerInterruptPoint();
      return;
   }
   else
   {
      /* Yes, get next TIP (Alarm or ST) */
      TIP_ID = osGetFirstAlarm();

      /* Already expired ? */
      osdIF_COUNTER(osGetSystemCounter(), < , osAlarmTime[TIP_ID])
      {  
         /* Not yet expired, program it */
         if (osSetTimerInterruptPoint( osAlarmTime[TIP_ID] ) == osdTRUE)
         { /* Successfully programmed, end this routine */
            return;
         }
      }osdENDIF_COUNTER
   }

   osStopWorkTIPs = osdFALSE;
   do 
   {
      /* TIP already expired (earlier or during programming), so work it now */
      (void)osRemoveMinItemMinHeap();
      
      #if (osdAlarmsOnHiResSystemTimer>0)&&(osdNumberOfHiResSchedTabs>0)
      if (TIP_ID>=osdNumberOfAlarms)
      {
      #endif
      #if (osdNumberOfHiResSchedTabs>0)
         osHRSTWorkSchedTab(TIP_ID);
      #endif
      #if (osdAlarmsOnHiResSystemTimer>0)&&(osdNumberOfHiResSchedTabs>0)
      }
      else
      {
      #endif
      #if (osdAlarmsOnHiResSystemTimer>0)
         osWorkAlarm(TIP_ID); 
      #endif
      #if (osdAlarmsOnHiResSystemTimer>0)&&(osdNumberOfHiResSchedTabs>0)
      }
      #endif
      
   /* This point can only be reached, if the TIP was in the past */
   /* osHRSTWorkScheduleTables/osWorkAlarms() might have added a new TIP to the heap */
   /* Restart now */
   
      /* Anything else to do? */
      if (osGetActiveAlarmCount() == 0)
      {
         /* Nothing to do, end this routine */
         osClearTimerInterruptPoint();
         osStopWorkTIPs = osdTRUE;
      }
      else
      {
         /* Yes, get next TIP (Alarm or ST) */
         TIP_ID = osGetFirstAlarm();

         /* Already expired ? */
         osdIF_COUNTER(osGetSystemCounter(), < , osAlarmTime[TIP_ID])
         {  
            /* Not yet expired, program it */
            if (osSetTimerInterruptPoint( osAlarmTime[TIP_ID] ) == osdTRUE)
            { /* Successfully programmed, end this routine */
              osStopWorkTIPs = osdTRUE;
            }
         }osdENDIF_COUNTER
      }
   } while (osStopWorkTIPs == osdFALSE);
   
}
#endif /* ((0 == osdUserDefinedSystemTimer) && ((osdUseHighResolutionTimer == 0) || (osdAlarmsOnHiResSystemTimer > 0))) */

#endif /* #if (osdUseHeap) && (osdNumberOfAlarms + osdNumberOfHiResSchedTabs > 0) */

#if (osdNumberOfAlarms > 0)

/*-+--------------------------------------------------------------------------
 / osInitAlarms
 / Funktion:
 /   - prepares the RAM part of all alarms
 / Context:
 /   OS initialization.
 /   This function is meant to be OS internal.
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/
/* TR:SPMF20:0014 Start */
osqFunc1 void osqFunc2 osInitAlarms(void)
{
   /* CovComment 4:  Function: osInitAlarms */
   osAlarmIndexType alarmID;
#if (osdAlarmsOnHiResSystemTimer > 0)
   TickType now;
   now = osGetSystemCounter();
   COVER(0x02FE)
#endif

   COVER(0x02FF)
   /* counters were already initialized (in StartOSc) */

#if (osdUseHeap != 0)
   COVER(0x0300)
   osInitMinHeap();
#endif


   for (alarmID = 0; alarmID < osrNumberOfAlarms; alarmID++)
   {
      if ((oskAlarmAutoStart[alarmID] & osActiveAppMode) != 0)
      {
#if (osdUseHeap != 0)
         osAlarmTime[alarmID] = oskStaticAlarmTime[alarmID];
         osAlarmActivated[alarmID] = 1;
         osInsertMinHeap(alarmID);
         COVER(0x0301)
#else
         osAlarmTime[alarmID] = oskStaticAlarmTime[alarmID];
         COVER(0x0302)
#endif
      }
      else /* no autostart for this alarm */
      {
#if (osdUseHeap != 0)
         COVER(0x0303)
         osAlarmActivated[alarmID] = 0;
#else
         COVER(0x0304)
         osAlarmTime[alarmID] = 0;
#endif
      }
   } /* for (alarmID= 0; alarmID < osrNumberOfAlarms; alarmID++) */

#if (osdNumberOfVarAlarms > 0)

   /*complete the init of all variable alarms*/
   for (alarmID= 0; alarmID < osrNumberOfVarAlarms; alarmID++)
   {
      if ((oskAlarmAutoStart[alarmID] & osActiveAppMode) != 0)
      {
         osAlarmCycleTime[alarmID] = oskStaticAlarmCycleTime[alarmID];
         COVER(0x0305)
      }
      else
      {
         osAlarmCycleTime[alarmID] = 0;
         COVER(0x0306)
      }
   }
   COVER(0x0307)
 #endif
} /* END OF osInitAlarms */ /* TR:SPMF20:0014 End */

#endif  /*!osdNumberOfAlarms*/

#if (osdSystemCounterNeeded != 0)
/* KB begin osekHWInitTimerSrc (overwritten) */
/* KB end osekHWInitTimerSrc */

/* KB begin osekHWTimerInterruptSrc (overwritten) */
/* KB end osekHWTimerInterruptSrc */

#endif /*(osdSystemCounterNeeded != 0)*/

/* KB begin osekEndOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
/* Reset to default section TR:SPMF49:0004 */
#pragma SET_CODE_SECTION()
#endif
/* KB end osekEndOfCModule */

/* END OF MODULE osektime.c */


