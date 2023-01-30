/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osek.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=2.12
|
|  Description: contains osek prototypes and defines
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
#ifndef _OSEK_H      /* PRQA S 0883 EOF */ /* see MISRA comment above */
#define _OSEK_H

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

/* autosar conformant information publishing */
#define OS_VENDOR_ID 30        /*Autosar/HIS vendor ID Vector-Informatik*/
#define OS_MODULE_ID 0x01
#define OS_AR_MAJOR_VERSION 3
#define OS_AR_MINOR_VERSION 1
#define OS_AR_PATCH_VERSION 0
/* KB begin vrmReleaseNumber (overwritten) */
/* TR:SPMF36:0002 Start */
/* Source release number */
#define osdVrmMajRelNum 5
#define osdVrmMinRelNum 6
/* TR:SPMF36:0002 End */
/* KB end vrmReleaseNumber */
#define OS_SW_MAJOR_VERSION osdVrmMajRelNumRef
#define OS_SW_MINOR_VERSION osdVrmMinRelNumRef
/* KB begin AutosarPatchVersion (default) */
#define OS_SW_PATCH_VERSION 0
/* KB end AutosarPatchVersion */

/* TR:SOSK22:0013 Start */
/* TR:SOSK22:0015 Start */
/* defines for all conformance classes */
#define BCC1   1U /* TR:SOSK22:0017 */
#define BCC2   2U /* TR:SOSK22:0018 */
#define ECC1   3U /* TR:SOSK22:0019 */
#define ECC2   4U /* TR:SOSK22:0020 */
/* TR:SOSK22:0013 End */
/* TR:SOSK22:0015 End */

/* and for all scalability classes */
#define SC1    1U
#define SC2    2U
#define SC3    3U
#define SC4    4U

#define STANDARD_STATUS 0U
#define EXTENDED_STATUS 1U

#if defined USE_QUOTE_INCLUDES
 #include "osektype.h"
#else
 #include <osektype.h>
#endif

#if defined USE_QUOTE_INCLUDES
 #include "osekqm.h"
#else
 #include <osekqm.h>
#endif


#define osdComStandard 0U
#define osdComExtended 1U
/* Are we in a PRQA/QAC/MISRA-check? */
#ifdef PRQA_PTRDIFF_T
 /* YES: Perform some adaptations to the OS */
 /* First the general adaptations: */
 #pragma PRQA_NO_RETURN osAbortSystem
 #pragma PRQA_NO_RETURN osAssertFailed
 #pragma PRQA_NO_RETURN osSysShutdownOS

 /* Then possible plattform specific adaptations: */
 /* KB begin osekHWosPrqaAdaptation (default) */
 /* no platform specific adaptations for PRQA/QAC */
 /* KB end osekHWosPrqaAdaptation */
#endif

/* Known Compilers */
/* KB begin osekCompilerDefines (overwritten) */
#define osdCompilerGHSARM 1
#define osdCompilerTIARM  2
/* KB end osekCompilerDefines */

#ifdef osdIncludeLibConfig

   #define osdPreTCB  1U        
   #define osdPostTCB 0U 

   #if (osdLibVariant == 1U)
    #if defined USE_QUOTE_INCLUDES
     #include "oseklib1.h"
    #else
     #include <oseklib1.h>
    #endif
   #endif
   
   #if (osdLibVariant == 2U)
    #if defined USE_QUOTE_INCLUDES
     #include "oseklib2.h"
    #else
     #include <oseklib2.h>
    #endif
   #endif
   
   #if (osdLibVariant == 3U)
    #if defined USE_QUOTE_INCLUDES
     #include "oseklib3.h"
    #else
     #include <oseklib3.h>
    #endif
   #endif
   
   #if (osdLibVariant == 4U)
    #if defined USE_QUOTE_INCLUDES
     #include "oseklib4.h"
    #else
     #include <oseklib4.h>
    #endif
   #endif
   
   #if ((osdLibVariant < 1) || (osdLibVariant > 4))
   #error unknown library variant/configuration file
   #endif

   #undef osdPreTCB 
   #undef osdPostTCB
   
#else /*osdIncludeLibConfig*/

   #define osdPreTCB  1        
   #define osdPostTCB 0 
   #if defined USE_QUOTE_INCLUDES
    #include "tcb.h"  /* include before */
   #else
    #include <tcb.h>  /* include before */
   #endif
   #undef osdPreTCB 
   #undef osdPostTCB

#endif /*osdIncludeLibConfig*/


/* KB begin osekStartOfHModule (default) */
/* KB end osekStartOfHModule */


/* include hardware specific header files before OSEK Typedefinitions */
/* KB begin osekHWincludeHwHeaderPreTypes (overwritten) */
/* KB end osekHWincludeHwHeaderPreTypes */

#if defined USE_QUOTE_INCLUDES
 #include "osekcov.h"
 #include "osekasrt.h" /* posix types must be defined      */
 #include "osekerr.h"  /* definitions of all error numbers */
#else
 #include <osekcov.h>
 #include <osekasrt.h> /* posix types must be defined      */
 #include <osekerr.h>  /* definitions of all error numbers */
#endif


/* access rights */
#define NO_ACCESS 0U /* TR:SASR30:0356 Start Possible values of ObjectAccessType */
#define ACCESS 1U    /* TR:SASR30:0356 End */


#define INVALID_SCHEDULETABLE ((ScheduleTableType)(0xFFFFFFFFUL))
#define INVALID_PROCESS (((osProcessType)(0xFFFFFFFFUL)))


/* Schedule Table status confirms to AS 3.0 */
/* TR:SASR30:0362 Start Possible values of ScheduleTableStatusType */
#define SCHEDULETABLE_STOPPED                 0U /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 */
#define SCHEDULETABLE_NEXT                    1U /* TR:SASR30:0288 *//* TR:SASR30:0295 *//* TR:SASR30:0301 */
#define SCHEDULETABLE_WAITING                 2U /* TR:SASR30:0301 */
#define SCHEDULETABLE_RUNNING                 3U /* TR:SASR30:0288 *//* TR:SASR30:0301 */
#define SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS 4U /* TR:SASR30:0295 *//* TR:SASR30:0301 */
/* TR:SASR30:0362 End */

/* values for AccessType */
#define oskAccess_None 0x0U
#define oskAccess_Read 0x1U
#define oskAccess_Write 0x2U
#define oskAccess_Execute 0x4U
#define oskAccess_Stack 0x8U

/* TR:SASR30:0351 Start Macros for AccessType */
#define OSMEMORY_IS_READABLE(x) (((x) & oskAccess_Read)? 1 : 0)
#define OSMEMORY_IS_WRITEABLE(x) (((x) & oskAccess_Write)? 1 : 0)
#define OSMEMORY_IS_EXECUTABLE(x) (((x) & oskAccess_Execute)? 1 : 0)
#define OSMEMORY_IS_STACKSPACE(x) (((x) & oskAccess_Stack)? 1 : 0)
/* TR:SASR30:0351 End */

/* TR:SASR30:0366 Start Possible values for RestartType */
#define RESTART    1
#define NO_RESTART 2
/* TR:SASR30:0366 End */

/* SCHEDULETABLE AUTOSTART TYPE */
#define osdScheduleTableAutostartNO                  0U
#define osdScheduleTableAutostartABSOLUT             1U
#define osdScheduleTableAutostartRELATIVE            2U
#define osdScheduleTableAutostartSYNCHRON            3U

/* ALARM AUTOSTART TYPE */
#define osdAlarmAutostartNO                          0U
#define osdAlarmAutostartABSOLUTE                    1U
#define osdAlarmAutostartRELATIVE                    2U

#define OSINVALIDAPPMODE                             0U

/* KB begin osekHwTASKmacro (default) */
/* OSEK-conform task-function-macro */
#define TASK(x)  void x##func(void) /* TR:SOSK22:0250 */
/* KB end osekHwTASKmacro */
/* KB begin osekHWISRmacro (default) */
/* TR:SOSK22:0267 Start */
/* OSEK-conform interrupt-function-macro */
#define ISR(x) void x##func(void)
/* TR:SOSK22:0267 End */
/* KB end osekHWISRmacro */
/* KB begin osekHWAlrmCallbckmacro (default) */
/* TR:SOSK22:0117 Start */
/* OSEK-conform function-macro for alarm callbacks */
#define ALARMCALLBACK(x) void x(void)
/* TR:SOSK22:0117 End */
/* KB end osekHWAlrmCallbckmacro */
/* Default application mode is generated (OSEK 2.2) */

/* implementation specific constants */
/* KB begin osekConstants (overwritten) */
#define osdPrioBitsPerWord 32
/* KB end osekConstants */




#if ((osdSC== SC3) || (osdSC== SC4)) 
/* TR:SASR30:0357 Start Possible values of ObjectTypeType */
#define OBJECT_TASK 0
#define OBJECT_ISR 1
#define OBJECT_ALARM 2
#define OBJECT_RESOURCE 3
#define OBJECT_COUNTER 4
#define OBJECT_SCHEDULETABLE 5
/* TR:SASR30:0357 End */
#define osdNumberOfObjectTypes 6
#endif


 #if osdErrorHook
  #if osdGetServiceIdMacros
   
   #define OSServiceId_ActivateTask          0x1100U
   #define OSServiceId_TerminateTask         0x1200U
   #define OSServiceId_ChainTask             0x1300U
   #define OSServiceId_Schedule              0x1400U
   #define OSServiceId_GetTaskState          0x1500U
   #define OSServiceId_GetTaskID             0x1600U

   #define OSServiceId_EnableAllInterrupts   0x2400U
   #define OSServiceId_DisableAllInterrupts  0x2500U
   #define OSServiceId_ResumeOSInterrupts    0x2A00U
   #define OSServiceId_SuspendOSInterrupts   0x2900U
   #define OSServiceId_ResumeAllInterrupts   0x2C00U
   #define OSServiceId_SuspendAllInterrupts  0x2B00U

   #define OSServiceId_GetResource           0x3100U
   #define OSServiceId_ReleaseResource       0x3200U

   #define OSServiceId_SetEvent              0x4100U
   #define OSServiceId_ClearEvent            0x4200U
   #define OSServiceId_GetEvent              0x4300U
   #define OSServiceId_WaitEvent             0x4400U

   #define OSServiceId_GetAlarmBase          0x5100U
   #define OSServiceId_GetAlarm              0x5200U
   #define OSServiceId_SetRelAlarm           0x5300U
   #define OSServiceId_SetAbsAlarm           0x5400U
   #define OSServiceId_CancelAlarm           0x5500U

   #define OSServiceId_StartScheduleTableRel  0x7100U /* TR:SASR30:0375 */
   #define OSServiceId_StartScheduleTableAbs  0x7200U /* TR:SASR30:0376 */
   #define OSServiceId_StopScheduleTable      0x7300U /* TR:SASR30:0377 */
   #define OSServiceId_GetScheduleTableStatus 0x7400U /* TR:SASR30:0382 */
   #define OSServiceId_NextScheduleTable      0x7500U /* TR:SASR30:0378 */

   #define OSServiceId_IncrementCounter        0x8100U /* TR:SASR30:0383 */
   #define OSServiceId_GetISRID                0x8200U /* TR:SASR30:0369 */

   #define OSServiceId_CallTrustedFunction     0x9300U /* TR:SASR30:0370 */
   #define OSServiceId_TerminateApplication    0x9400U
   #define OSServiceId_SyncScheduleTable       0x9500U /* TR:SASR30:0380 */
   #define OSServiceId_SetScheduleTableAsync   0x9600U /* TR:SASR30:0381 */
   #define OSServiceId_GetTaskMaxExecutionTime 0x9800U
   #define OSServiceId_GetISRMaxExecutionTime  0x9900U
   #define OSServiceId_GetTaskMaxBlockingTime  0x9A00U
   #define OSServiceId_GetISRMaxBlockingTime   0x9B00U
   #define OSServiceId_StartScheduleTableSynchron   0x9C00U /* TR:SASR30:0379 */
   #define OSServiceId_GetTaskMinInterArrivalTime 0x9000U
   #define OSServiceId_GetISRMinInterArrivalTime  0x9F00U


   #define OSErrorGetServiceId()       ((OSServiceIdType) (osLastError & 0xFF00U))  /* TR:SOSK22:0130 *//* TR:SASR30:0241 OSErrorGetServiceId */

  #endif

   #define OSErrorGetosCANError()      osLastError /* TR:SPMF10:0022 *//* TR:SASR30:0241 OSErrorGetosCANError */

   #if ((STATUS_LEVEL == EXTENDED_STATUS) && (!defined(osdSuppressFilenames) ))
    #define OSErrorGetosCANLineNumber() osActiveTaskLineNumber /* TR:SASR30:0241 OSErrorGetosCANLineNumber */
    #define OSErrorGetosCANModulName()  osActiveTaskModule     /* TR:SASR30:0241 OSErrorGetosCANModulName */
   #endif

  #if osdParameterAccessMacros 
   /* TR:SOSK22:0131 Start *//* TR:SASR30:0241 Start OSError_(API_Name) */
   #define OSError_ActivateTask_TaskID()                      (osAPIParam1.osTaskType) 
   #define OSError_ChainTask_TaskID()                         (osAPIParam1.osTaskType) 
   #define OSError_GetTaskID_TaskID()                         (osAPIParam1.osTaskRefType) 
   #define OSError_GetTaskState_TaskID()                      (osAPIParam1.osTaskType) 
   #define OSError_GetTaskState_State()                       (osAPIParam2.osTaskStateRefType) 

   #define OSError_GetResource_ResID()                        (osAPIParam1.osResourceType) 
   #define OSError_ReleaseResource_ResID()                    (osAPIParam1.osResourceType) 

   #define OSError_SetEvent_TaskID()                          (osAPIParam1.osTaskType) 
   #define OSError_SetEvent_Mask()                            (osAPIParam2.osEventMaskType) 
   #define OSError_GetEvent_TaskID()                          (osAPIParam1.osTaskType) 
   #define OSError_GetEvent_Event()                           (osAPIParam2.osEventMaskRefType) 
   #define OSError_ClearEvent_Mask()                          (osAPIParam1.osEventMaskType) 
   #define OSError_WaitEvent_Mask()                           (osAPIParam1.osEventMaskType) 

   #define OSError_GetAlarmBase_AlarmID()                     (osAPIParam1.osAlarmType) 
   #define OSError_GetAlarmBase_Info()                        (osAPIParam2.osAlarmBaseRefType) 
   #define OSError_SetRelAlarm_AlarmID()                      (osAPIParam1.osAlarmType) 
   #define OSError_SetRelAlarm_increment()                    (osAPIParam2.osTickType) 
   #define OSError_SetRelAlarm_cycle()                        (osAPIParam3.osTickType)
   #define OSError_SetAbsAlarm_AlarmID()                      (osAPIParam1.osAlarmType) 
   #define OSError_SetAbsAlarm_start()                        (osAPIParam2.osTickType) 
   #define OSError_SetAbsAlarm_cycle()                        (osAPIParam3.osTickType)
   #define OSError_CancelAlarm_AlarmID()                      (osAPIParam1.osAlarmType) 
   #define OSError_GetAlarm_AlarmID()                         (osAPIParam1.osAlarmType) 
   #define OSError_GetAlarm_Tick()                            (osAPIParam2.osTickRefType)
 
   #define OSError_StartScheduleTableRel_ScheduleTableID()    (osAPIParam1.osScheduleTableType)
   #define OSError_StartScheduleTableRel_Offset()             (osAPIParam2.osTickType)
   #define OSError_StartScheduleTableAbs_ScheduleTableID()    (osAPIParam1.osScheduleTableType)
   #define OSError_StartScheduleTableAbs_Tickvalue()          (osAPIParam2.osTickType)
   #define OSError_StopScheduleTable_ScheduleTableID()        (osAPIParam1.osScheduleTableType)
   #define OSError_NextScheduleTable_ScheduleTableID_current()(osAPIParam1.osScheduleTableType)
   #define OSError_NextScheduleTable_ScheduleTableID_next()   (osAPIParam2.osScheduleTableType)
   #define OSError_IncrementCounter_CounterID()               (osAPIParam1.osCounterType)
   #define OSError_GetScheduleTableStatus_ScheduleID()        (osAPIParam1.osScheduleTableType)
   #define OSError_GetScheduleTableStatus_ScheduleStatus()    (osAPIParam2.osScheduleTableStatusRefType)

   #if (osdScheduleTableSyncUsed != 0)
    #define OSError_StartScheduleTableSynchron_ScheduleTableID(x) (osAPIParam1.osScheduleTableType)
    #define OSError_SyncScheduleTable_ScheduleID()             (osAPIParam1.osScheduleTableType)
    #define OSError_SyncScheduleTable_GlobalTime()             (osAPIParam2.osTickType)
    #define OSError_SetScheduleTableAsync_ScheduleID()         (osAPIParam1.osScheduleTableType)
   #endif

   #if ((osdSC== SC3) || (osdSC== SC4))
    #define OSError_CallTrustedFunction_FunctionIndex()        (osAPIParam1.osFunctionIndexType) 
    #define OSError_CallTrustedFunction_FunctionParams()       (osAPIParam2.osTrustedFunctionParameterRefType) 
    #define OSError_TerminateApplication_RestartOption()       (osAPIParam1.RestartType) 
    #define OSError_CallNonTrustedFunction_FunctionIndex()     (osAPIParam1.osFunctionIndexType) 
    #define OSError_CallNonTrustedFunction_FunctionParams()    (osAPIParam2.osTrustedFunctionParameterRefType) 
   #endif

   #if (osdTimingProtectionUsed != 0)
    #define OSError_GetTaskMaxExecutionTime_TaskID()           (osAPIParam1.osTaskType)
    #define OSError_GetTaskMaxExecutionTime_MaxTime()          (osAPIParam2.osTimeRefType)
    #define OSError_GetISRMaxExecutionTime_ISRID()             (osAPIParam1.osISRType)
    #define OSError_GetISRMaxExecutionTime_MaxTime()           (osAPIParam2.osTimeRefType)
    #define OSError_GetTaskMinInterArrivalTime_TaskID()        (osAPIParam1.osTaskType)
    #define OSError_GetTaskMinInterArrivalTime_MinTime()       (osAPIParam2.osTimeRefType)
    #define OSError_GetISRMinInterArrivalTime_ISRID()          (osAPIParam1.osISRType)
    #define OSError_GetISRMinInterArrivalTime_MinTime()        (osAPIParam2.osTimeRefType)
    #define OSError_GetTaskMaxBlockingTime_TaskID()            (osAPIParam1.osTaskType)
    #define OSError_GetTaskMaxBlockingTime_BlockType()         (osAPIParam2.osBlockType)
    #define OSError_GetTaskMaxBlockingTime_ResourceID()        (osAPIParam3.osResourceType)
    #define OSError_GetTaskMaxBlockingTime_MaxTime()           (osAPIParam4)
    #define OSError_GetISRMaxBlockingTime_ISRID()              (osAPIParam1.osISRType)
    #define OSError_GetISRMaxBlockingTime_BlockType()          (osAPIParam2.osBlockType)
    #define OSError_GetISRMaxBlockingTime_ResourceID()         (osAPIParam3.osResourceType)
    #define OSError_GetISRMaxBlockingTime_MaxTime()            (osAPIParam4)
   #endif

  /* TR:SASR30:0241 End *//* TR:SOSK22:0131 End */
  #endif /* #if osdParameterAccessMacros */
 #endif /* #if osdErrorHook */

/* definitions to save the parameters in global variables before calling the service */
#if osdParameterAccessMacros && osdErrorHook
   #define osSaveActivateTask_TaskID(x)                      (osAPIParam1.osTaskType = (x));
   #define osSaveChainTask_TaskID(x)                         (osAPIParam1.osTaskType = (x));
   #define osSaveGetTaskID_TaskID(x)                         (osAPIParam1.osTaskRefType = (x));
   #define osSaveGetTaskState_TaskID(x)                      (osAPIParam1.osTaskType = (x));
   #define osSaveGetTaskState_State(y)                       (osAPIParam2.osTaskStateRefType = (y));
   #define osSaveGetResource_ResID(x)                        (osAPIParam1.osResourceType = (x));
   #define osSaveReleaseResource_ResID(x)                    (osAPIParam1.osResourceType = (x));
   #define osSaveSetEvent_TaskID(x)                          (osAPIParam1.osTaskType = (x));
   #define osSaveSetEvent_Mask(y)                            (osAPIParam2.osEventMaskType = (y));
   #define osSaveGetEvent_TaskID(x)                          (osAPIParam1.osTaskType = (x));
   #define osSaveGetEvent_Event(y)                           (osAPIParam2.osEventMaskRefType = (y));
   #define osSaveClearEvent_Mask(x)                          (osAPIParam1.osEventMaskType = (x));
   #define osSaveWaitEvent_Mask(x)                           (osAPIParam1.osEventMaskType = (x));
   #define osSaveGetAlarmBase_AlarmID(x)                     (osAPIParam1.osAlarmType = (x));
   #define osSaveGetAlarmBase_Info(y)                        (osAPIParam2.osAlarmBaseRefType = (y));
   #define osSaveSetRelAlarm_AlarmID(x)                      (osAPIParam1.osAlarmType = (x)) ;
   #define osSaveSetRelAlarm_increment(y)                    (osAPIParam2.osTickType = (y));
   #define osSaveSetRelAlarm_cycle(z)                        (osAPIParam3.osTickType = (z));
   #define osSaveSetAbsAlarm_AlarmID(x)                      (osAPIParam1.osAlarmType = (x));
   #define osSaveSetAbsAlarm_start(y)                        (osAPIParam2.osTickType = (y));
   #define osSaveSetAbsAlarm_cycle(z)                        (osAPIParam3.osTickType = (z));
   #define osSaveCancelAlarm_AlarmID(x)                      (osAPIParam1.osAlarmType = (x));
   #define osSaveGetAlarm_AlarmID(x)                         (osAPIParam1.osAlarmType = (x));
   #define osSaveGetAlarm_Tick(y)                            (osAPIParam2.osTickRefType = (y));
   #define osSaveIncrementCounter_CounterID(x)               (osAPIParam1.osCounterType = (x));
   #define osSaveStartScheduleTableRel_ScheduleTableID(x)    (osAPIParam1.osScheduleTableType = (x));
   #define osSaveStartScheduleTableRel_Offset(y)             (osAPIParam2.osTickType = (y));
   #define osSaveStartScheduleTableAbs_ScheduleTableID(x)    (osAPIParam1.osScheduleTableType = (x));
   #define osSaveStartScheduleTableAbs_Tickvalue(y)          (osAPIParam2.osTickType = (y));
   #define osSaveStopScheduleTable_ScheduleTableID(x)        (osAPIParam1.osScheduleTableType = (x));
   #define osSaveNextScheduleTable_ScheduleTableID_current(x)(osAPIParam1.osScheduleTableType = (x));
   #define osSaveNextScheduleTable_ScheduleTableID_next(y)   (osAPIParam2.osScheduleTableType = (y));
   #define osSaveGetScheduleTableStatus_ScheduleID(x)        (osAPIParam1.osScheduleTableType = (x));
   #define osSaveGetScheduleTableStatus_ScheduleStatus(y)    (osAPIParam2.osScheduleTableStatusRefType = (y));
#if (osdScheduleTableSyncUsed != 0)
   #define osSaveStartScheduleTableSynchron_ScheduleTableID(x) (osAPIParam1.osScheduleTableType = (x));
   #define osSaveSyncScheduleTable_ScheduleID(x)             (osAPIParam1.osScheduleTableType = (x));
   #define osSaveSyncScheduleTable_GlobalTime(y)             (osAPIParam2.osTickType = (y));
   #define osSaveSetScheduleTableAsync_ScheduleID(x)         (osAPIParam1.osScheduleTableType = (x));
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
   #define osSaveCallTrustedFunction_FunctionIndex(x)   (osAPIParam1.osFunctionIndexType = (x));
   #define osSaveCallTrustedFunction_FunctionParams(y)  (osAPIParam2.osTrustedFunctionParameterRefType = (y));
   #define osSaveTerminateApplication_RestartOption(x)  (osAPIParam1.osRestartType = (x));
   #define osSaveCallNonTrustedFunction_FunctionIndex(x)   (osAPIParam1.osFunctionIndexType = (x));
   #define osSaveCallNonTrustedFunction_FunctionParams(y)  (osAPIParam2.osTrustedFunctionParameterRefType = (y));
#endif

#if (osdTimingProtectionUsed != 0)
   #define osSaveGetTaskMaxExecutionTime_TaskID(x)           (osAPIParam1.osTaskType     = (x));
   #define osSaveGetTaskMaxExecutionTime_MaxTime(y)          (osAPIParam2.osTimeRefType  = (y));
   #define osSaveGetISRMaxExecutionTime_ISRID(x)             (osAPIParam1.osISRType      = (x));
   #define osSaveGetISRMaxExecutionTime_MaxTime(y)           (osAPIParam2.osTimeRefType  = (y));
   #define osSaveGetTaskMinInterArrivalTime_TaskID(x)        (osAPIParam1.osTaskType     = (x));
   #define osSaveGetTaskMinInterArrivalTime_MinTime(y)       (osAPIParam2.osUnionTPTimeStampRefType  = (y));
   #define osSaveGetISRMinInterArrivalTime_ISRID(x)          (osAPIParam1.osISRType      = (x));
   #define osSaveGetISRMinInterArrivalTime_MinTime(y)        (osAPIParam2.osUnionTPTimeStampRefType  = (y));
   #define osSaveGetTaskMaxBlockingTime_TaskID(x)            (osAPIParam1.osTaskType     = (x));
   #define osSaveGetTaskMaxBlockingTime_BlockType(y)         (osAPIParam2.osBlockType    = (y));
   #define osSaveGetTaskMaxBlockingTime_ResourceID(z)        (osAPIParam3.osResourceType = (z));
   #define osSaveGetTaskMaxBlockingTime_MaxTime(z1)          (osAPIParam4                = (z1));
   #define osSaveGetISRMaxBlockingTime_ISRID(x)              (osAPIParam1.osISRType      = (x));
   #define osSaveGetISRMaxBlockingTime_BlockType(y)          (osAPIParam2.osBlockType    = (y));
   #define osSaveGetISRMaxBlockingTime_ResourceID(z)         (osAPIParam3.osResourceType = (z));
   #define osSaveGetISRMaxBlockingTime_MaxTime(z1)           (osAPIParam4                = (z1));
#endif
#else /* osdParameterAccessMacros && osdErrorHook */

   #define osSaveActivateTask_TaskID(x)  
   #define osSaveChainTask_TaskID(x)     
   #define osSaveGetTaskID_TaskID(x)      
   #define osSaveGetTaskState_TaskID(x)  
   #define osSaveGetTaskState_State(y)  
   #define osSaveGetResource_ResID(x)
   #define osSaveReleaseResource_ResID(x)
   #define osSaveSetEvent_TaskID(x)     
   #define osSaveSetEvent_Mask(y)     
   #define osSaveGetEvent_TaskID(x)     
   #define osSaveGetEvent_Event(y)        
   #define osSaveClearEvent_Mask(x)      
   #define osSaveWaitEvent_Mask(x)       
   #define osSaveGetAlarmBase_AlarmID(x)    
   #define osSaveGetAlarmBase_Info(y)     
   #define osSaveSetRelAlarm_AlarmID(x)   
   #define osSaveSetRelAlarm_increment(y)    
   #define osSaveSetRelAlarm_cycle(z)     
   #define osSaveSetAbsAlarm_AlarmID(x)    
   #define osSaveSetAbsAlarm_start(y)    
   #define osSaveSetAbsAlarm_cycle(z)    
   #define osSaveCancelAlarm_AlarmID(x)   
   #define osSaveGetAlarm_AlarmID(x)      
   #define osSaveGetAlarm_Tick(y)         
   #define osSaveIncrementCounter_CounterID(x)
   #define osSaveStartScheduleTableRel_ScheduleTableID(x)
   #define osSaveStartScheduleTableRel_Offset(y)
   #define osSaveStartScheduleTableAbs_ScheduleTableID(x)
   #define osSaveStartScheduleTableAbs_Tickvalue(y)
   #define osSaveStopScheduleTable_ScheduleTableID(x)
   #define osSaveNextScheduleTable_ScheduleTableID_current(x)
   #define osSaveNextScheduleTable_ScheduleTableID_next(y)
   #define osSaveGetScheduleTableStatus_ScheduleID(x)
   #define osSaveGetScheduleTableStatus_ScheduleStatus(y)
#if (osdScheduleTableSyncUsed != 0)
   #define osSaveStartScheduleTableSynchron_ScheduleTableID(x) 
   #define osSaveSyncScheduleTable_ScheduleID(x)
   #define osSaveSyncScheduleTable_GlobalTime(x)
   #define osSaveSetScheduleTableAsync_ScheduleID(x)
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
   #define osSaveCallTrustedFunction_FunctionIndex(x)
   #define osSaveCallTrustedFunction_FunctionParams(y)
   #define osSaveTerminateApplication_RestartOption(x)
   #define osSaveCallNonTrustedFunction_FunctionIndex(x)
   #define osSaveCallNonTrustedFunction_FunctionParams(y)
#endif

   #define osSaveGetTaskMaxExecutionTime_TaskID(x)
   #define osSaveGetTaskMaxExecutionTime_MaxTime(y)
   #define osSaveGetISRMaxExecutionTime_ISRID(x)
   #define osSaveGetISRMaxExecutionTime_MaxTime(y)
   #define osSaveGetTaskMinInterArrivalTime_TaskID(x)
   #define osSaveGetTaskMinInterArrivalTime_MinTime(y)
   #define osSaveGetISRMinInterArrivalTime_ISRID(x)
   #define osSaveGetISRMinInterArrivalTime_MinTime(y)
   #define osSaveGetTaskMaxBlockingTime_TaskID(x)
   #define osSaveGetTaskMaxBlockingTime_BlockType(y)
   #define osSaveGetTaskMaxBlockingTime_ResourceID(z)
   #define osSaveGetTaskMaxBlockingTime_MaxTime(z1)
   #define osSaveGetISRMaxBlockingTime_ISRID(x)
   #define osSaveGetISRMaxBlockingTime_BlockType(y)
   #define osSaveGetISRMaxBlockingTime_ResourceID(z)
   #define osSaveGetISRMaxBlockingTime_MaxTime(z1)

#endif /* osdParameterAccessMacros && osdErrorHook else */


/* OSEK types */
/* implementation specific OSEK types */


#if ((osdSC== SC3) || (osdSC== SC4))

/* KB begin osekHWosStartupHookType (default) */
typedef void                (*osStartupHookType)(void);
/* KB end osekHWosStartupHookType */
/* KB begin osekHWosShutdownHookType (default) */
typedef void                (*osShutdownHookType)(StatusType Error);
/* KB end osekHWosShutdownHookType */
/* KB begin osekHWosErrorHookType (default) */
typedef void                (*osErrorHookType)(StatusType Error);
/* KB end osekHWosErrorHookType */

#endif /*((osdSC== SC3) || (osdSC== SC4))*/

/* KB begin osekOSEKdeclarations (default) */
/* TR:SOSK22:0160 Start */
#define DeclareTask(TaskId)     osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed1##TaskId
#define DeclareResource(ResId)  osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed2##ResId
#define DeclareEvent(Event)     osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed3##Event
#define DeclareAlarm(AlarmId)   osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed4##AlarmId
/* TR:SOSK22:0160 End */
/* KB end osekOSEKdeclarations */    /* DeclareTask, DeclareAlarm,... */

/* structure for AlarmBase */
typedef struct
{
   TickType maxallowedvalue;/* Maximum possible allowed count value (for example */
                            /* in ticks or angle degrees) */ /* TR:SOSK22:0310 */
   TickType ticksperbase;   /* Number of ticks required to reach a counter-specific */
                            /* (significant) unit. */ /* TR:SOSK22:0311 */
   TickType mincycle;       /* Minimum allowed number of ticks for a cyclic alarm */
                            /* (only for systems with Extended Status). */ /* TR:SOSK22:0312 */
} AlarmBaseType;  /* TR:SOSK22:0308 */

typedef AlarmBaseType     *AlarmBaseRefType; /* TR:SOSK22:0309 */

typedef osTIPType         osHeapType;

typedef osuint16          OSServiceIdType; /* TR:SOSK22:0356 */
typedef void              (*osAlarmCallbackType)(void);
typedef osuint8           BlockTypeType;


typedef union
{
   TaskType          osTaskType;
   TaskRefType       osTaskRefType;
   ResourceType      osResourceType; 
   EventMaskType     osEventMaskType;
   osTIPType         osAlarmType;
   CounterType       osCounterType;
   ScheduleTableType osScheduleTableType;
   ISRType           osISRType;
#if ((osdSC== SC3) || (osdSC== SC4))
   TrustedFunctionIndexType osFunctionIndexType;
   RestartType       osRestartType;
#endif
#if (osdTimingProtectionUsed != 0)
   osTPTimeType          *osTimeRefType;
#endif
} osAPIParam1Type;

typedef union
{
   TaskStateRefType           osTaskStateRefType;
   EventMaskType              osEventMaskType;
   EventMaskRefType           osEventMaskRefType;
   AlarmBaseRefType           osAlarmBaseRefType;
   TickType                   osTickType;
   TickRefType                osTickRefType;
   ScheduleTableType          osScheduleTableType;
   ScheduleTableStatusRefType osScheduleTableStatusRefType;
#if ((osdSC== SC3) || (osdSC== SC4))
   TrustedFunctionParameterRefType osTrustedFunctionParameterRefType;
#endif
   BlockTypeType              osBlockType;
#if (osdTimingProtectionUsed != 0)
   osTPTimeType               *osTimeRefType;
   osTPTimeStampRefType       osUnionTPTimeStampRefType;
#endif
} osAPIParam2Type;

typedef union
{
   TickType     osTickType;
   ResourceType osResourceType;

} osAPIParam3Type;



/* Schedule Table related */
typedef TickType osSTOffsetType;
typedef TickType GlobalTimeTickType;
typedef osuint16 osSTIndexType;


#if (osdTimingProtectionUsed)

/* possible values for type BlockTypeType */
#define OS_ALL_INTERRUPTS 1
#define OS_OS_INTERRUPTS  2
#define OS_RESOURCE       3

/* Additional resource-IDs for blocking-time measurement*/
#define osdRESID_OS_INTERRUPTS ((osdNumberOfAllResources) + 0)
#define osdRESID_ALL_INTERRUPTS ((osdNumberOfAllResources) + 1)

#endif




#if osdORTIDebug
 #define osdTestMacros 1
#endif

#ifdef osdUseTrace
 #define osdTestMacros 2
#endif

#ifndef osdTestMacros
 #if defined USE_QUOTE_INCLUDES
  #include "emptymac.h"
 #else
  #include <emptymac.h>
 #endif
#else                           
 #if (osdTestMacros == 1)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac1.h"
  #else
   #include <testmac1.h>
  #endif
 #endif
 #if (osdTestMacros == 2)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac2.h"
  #else
   #include <testmac2.h>
  #endif
 #endif
 #if (osdTestMacros == 3)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac3.h"
  #else
   #include <testmac3.h>
  #endif
 #endif
 #if (osdTestMacros == 4)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac4.h"
  #else
   #include <testmac4.h>
  #endif
 #endif
#endif /*osdTestMacros*/


/* KB begin osekHWVariableSectionStartHeader (default) */
/* KB end osekHWVariableSectionStartHeader */

/* KB begin osekCtrlVarDecl (overwritten) */
/* KB end osekCtrlVarDecl */

/* error handling                      */
#if (STATUS_LEVEL == EXTENDED_STATUS)
#ifndef osdSuppressFilenames 
/* variables for error handling */
osqRAM0 extern osqRAM1 osqRAM2 osLineNumberType osqRAM3 osActiveTaskLineNumber;

/* MISRA RULE 6.3 VIOLATION: The variable osActiveTaskModule is used to store the name of the 
 * file where the last OS-API-service has been called. This is performed by usage of the 
 * __FILE__ macro. Unfortunately some compilers warn if the type is not a character pointer. 
 * Usage of char* is save here as no computation on the value is intended. 
 */
osqRAM0 extern osqPROM1 const osqPROM2 char osqPROM3 * osqRAM1 osqRAM2 osqRAM3 osActiveTaskModule; /* PRQA S 5013 */
#endif
#endif

osqRAM0 extern osqRAM1 volatile osqRAM2 osuint8 osqRAM3 osORTICurrentServiceId;

/* KB begin osekHWDeclareOsSystemCounterExtern (default) */
#if osdSystemCounterNeeded
#if (osdUseCounterAPI==0)
osqRAM0 extern osqRAM1 volatile osqRAM2 TickType osqRAM3 osSystemCounter; /* TR:SOSK22:0100 */
#endif
#endif
/* KB end osekHWDeclareOsSystemCounterExtern */


/* KB begin osekHWDefineNegateTick (default) */
/* KB end osekHWDefineNegateTick */

osqRAM0 extern osqRAM1 osqRAM2 osuint8 osqRAM3 osActiveAppMode; /* TR:SOSK22:0067 */

#if (osdParameterAccessMacros && osdErrorHook)
osqRAM0 extern osqRAM1 osqRAM2 osAPIParam1Type osqRAM3 osAPIParam1;
osqRAM0 extern osqRAM1 osqRAM2 osAPIParam2Type osqRAM3 osAPIParam2;
osqRAM0 extern osqRAM1 osqRAM2 osAPIParam3Type osqRAM3 osAPIParam3;
#if (osdTimingProtectionUsed != 0)
osqRAM0 extern osqPRAM1 osTPTimeType osqPRAM2 osqPRAM3 * osqRAM1 osqRAM2 osqRAM3 osAPIParam4;
#endif
#endif

#if (osdErrorHook!=0)
/* KB begin osekExternGlobalErrorVariables (overwritten) */
#if (osdORTIDebug || defined(osdGHSDebugSupport))
extern osqRAM1 osqRAM2 StatusType osqRAM3 osLastErrorCode;
#endif
/* KB end osekExternGlobalErrorVariables */
#endif



/* KB begin osekHWVariableSectionEndHeader (overwritten) */
/* KB end osekHWVariableSectionEndHeader */


osqFunc1 void osqFunc2 osAbortSystem(osuint16 uiError);




#if ((osdSC== SC3) || (osdSC== SC4))
#endif /*((osdSC== SC3) || (osdSC== SC4))*/

osqFunc1 void osqFunc2 osInitTimer(void); /* TR:SPMF24:0006 */

#if osdTimingProtectionUsed
/* KB begin osTPTimerPrototypes (default) */
osqFunc1 void osqFunc2 osTPStartTimerBlock(ResourceType res);
osqFunc1 void osqFunc2 osTPStopTimerBlock(ResourceType res);

#if osdTimingMeasurement
   osqFunc1 StatusType osqFunc2 osGetTaskMaxExecutionTime(TaskType TaskID,  osTPTimeRefType MaxTime);
   osqFunc1 StatusType osqFunc2 osGetISRMaxExecutionTime(ISRType ISRID, osTPTimeRefType MaxTime);
   osqFunc1 StatusType osqFunc2 osGetTaskMinInterArrivalTime(TaskType TaskID, osTPTimeStampRefType MinTime);
   osqFunc1 StatusType osqFunc2 osGetISRMinInterArrivalTime(ISRType ISRID, osTPTimeStampRefType MinTime);
   osqFunc1 StatusType osqFunc2 osGetTaskMaxBlockingTime(TaskType TaskID, BlockTypeType BlockType, 
                                                         ResourceType ResourceID, osTPTimeRefType MaxTime);
   osqFunc1 StatusType osqFunc2 osGetISRMaxBlockingTime(ISRType ISRID, BlockTypeType BlockType, 
                                                        ResourceType ResourceID, osTPTimeRefType MaxTime);
#endif /* osdTimingMeasurement */
/* KB end osTPTimerPrototypes */
#endif /* osdTimingProtectionUsed */


/* TR:SASR30:0001 Start */
/* OSEK-Prototypes */
/* system services */
#if (STATUS_LEVEL == EXTENDED_STATUS) && !defined(osdSuppressFilenames)
/* TR:SOSK22:0165 Start */
/* TR:SOSK22:0226 Start */
/* TR:SOSK22:0229 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define ActivateTask(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysActivateTask(x))
#else
#define ActivateTask(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osActivateTask(x))
#endif
/* TR:SOSK22:0165 End */
/* TR:SOSK22:0226 End */
/* TR:SOSK22:0229 End */
/* TR:SOSK22:0169 Start */
#if ((osdSC == SC3) || (osdSC == SC4))
#define TerminateTask() (osActiveTaskLineNumber = __LINE__,\
   osActiveTaskModule = __FILE__,\
   osPsysTerminateTask())
#else
#define TerminateTask() (osActiveTaskLineNumber = __LINE__,\
   osActiveTaskModule = __FILE__,\
   osTerminateTask())
#endif
/* TR:SOSK22:0169 End */
/* TR:SOSK22:0178 Start */
#if ((osdSC == SC3) || (osdSC == SC4))
#define ChainTask(x) (osActiveTaskLineNumber = __LINE__,\
   osActiveTaskModule = __FILE__,\
   osPsysChainTask(x))
#else
#define ChainTask(x) (osActiveTaskLineNumber = __LINE__,\
   osActiveTaskModule = __FILE__,\
   osChainTask(x))
#endif
/* TR:SOSK22:0178 End */
/* TR:SOSK22:0182 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define Schedule() (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysSchedule())
#else
#define Schedule() (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osSchedule())
#endif
/* TR:SOSK22:0182 End */
/* TR:SOSK22:0210 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetTaskID(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetTaskID(x))
#else
#define GetTaskID(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetTaskID(x))
#endif
/* TR:SOSK22:0210 End */
/* TR:SOSK22:0211 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetTaskState(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetTaskState((x), (y)))
#else
#define GetTaskState(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetTaskState((x), (y)))
#endif
/* TR:SOSK22:0211 End */
#else /*STATUS_LEVEL...*/
/* TR:SOSK22:0145 Start This is only an example of system service interface */
/* TR:SOSK22:0165 Start */
/* TR:SOSK22:0226 Start */
/* TR:SOSK22:0229 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define ActivateTask(x) (osPsysActivateTask(x))
#else
#define ActivateTask(x) (osActivateTask(x))
#endif
/* TR:SOSK22:0145 End */
/* TR:SOSK22:0165 End */
/* TR:SOSK22:0226 End */
/* TR:SOSK22:0229 End */
/* TR:SOSK22:0169 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define TerminateTask() osPsysTerminateTask()
#else
#define TerminateTask() osTerminateTask()
#endif
/* TR:SOSK22:0169 End */
/* TR:SOSK22:0178 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define ChainTask(x) (osPsysChainTask(x))
#else
#define ChainTask(x) (osChainTask(x))
#endif
/* TR:SOSK22:0178 End */
/* TR:SOSK22:0182 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define Schedule() osPsysSchedule()
#else
#define Schedule() osSchedule()
#endif
/* TR:SOSK22:0182 End */
/* TR:SOSK22:0210 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetTaskID(x) (osPsysGetTaskID(x))
#else
#define GetTaskID(x) (osGetTaskID(x))
#endif
/* TR:SOSK22:0210 End */
/* TR:SOSK22:0211 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetTaskState(x, y) (osPsysGetTaskState((x), (y)))
#else
#define GetTaskState(x, y) (osGetTaskState((x), (y)))
#endif
/* TR:SOSK22:0211 End */
#endif /*STATUS_LEVEL...*/


/* interrupt handling */

/* KB begin osekHwOsekGlobalPrototypes (overwritten) */

/* implementation specific prototypes */



#define osSetAlarmLevel() osEnableLevel()    /* set to level of alarm interrupt */


extern osqRAM1 osqRAM2 osIntLevelType osqRAM3 osSavedIntLevel;

/* prototypes for interrupt handling functions implemented as functions for THUMB mode only */
void osRestoreEnableLevel(void);       

#pragma SWI_ALIAS(osWritePeripheral8, 0x84);
void osWritePeripheral8(osuint16 area, osuint32 address, osuint8 value);   /* TR:SPMF95:0004 */
/* The name function name osWritePeripheral16 is ok. 8-16-32, 116 makes no sense. */
#pragma SWI_ALIAS(osWritePeripheral16, 0x85);
void osWritePeripheral16(osuint16 area, osuint32 address, osuint16 value); /* PRQA S 4152 */ /* TR:SPMF95:0005 */
#pragma SWI_ALIAS(osWritePeripheral32, 0x86);
void osWritePeripheral32(osuint16 area, osuint32 address, osuint32 value); /* TR:SPMF95:0006 */

#pragma SWI_ALIAS(osReadPeripheral8, 0x87);
osuint8 osReadPeripheral8(osuint16 area, osuint32 address); /* TR:SPMF95:0001 */
/* The name function name osWritePeripheral16 is ok. 8-16-32, 116 makes no sense. */
#pragma SWI_ALIAS(osReadPeripheral16, 0x88);
osuint16 osReadPeripheral16(osuint16 area, osuint32 address); /* PRQA S 4152 */ /* TR:SPMF95:0002 */
#pragma SWI_ALIAS(osReadPeripheral32, 0x89);
osuint32 osReadPeripheral32(osuint16 area, osuint32 address); /* TR:SPMF95:0003 */

#pragma SWI_ALIAS(osModifyPeripheral8, 0x8A);
void osModifyPeripheral8(osuint16 area, osuint32 address, osuint8 clearmask, osuint8 setmask);    /* TR:SPMF95:0007 */
/* The name function name osWritePeripheral16 is ok. 8-16-32, 116 makes no sense. */
#pragma SWI_ALIAS(osModifyPeripheral16, 0x8B);
void osModifyPeripheral16(osuint16 area, osuint32 address, osuint16 clearmask, osuint16 setmask); /* PRQA S 4152 */ /* TR:SPMF95:0008 */
#pragma SWI_ALIAS(osModifyPeripheral32, 0x8C);
void osModifyPeripheral32(osuint16 area, osuint32 address, osuint32 clearmask, osuint32 setmask); /* TR:SPMF95:0009 */
/* KB end osekHwOsekGlobalPrototypes */ 


#if (STATUS_LEVEL == EXTENDED_STATUS) && !defined(osdSuppressFilenames)
/* TR:SOSK22:0212 Start */
   #if ((osdSC == SC2) ||  (osdSC == SC1))
      #define EnableAllInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osEnableAllInterrupts())
   #else
      #define EnableAllInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osPsysEnableAllInterrupts())
   #endif
/* TR:SOSK22:0212 End */
/* TR:SOSK22:0071 Start */
/* TR:SOSK22:0072 Start */
/* TR:SOSK22:0213 Start */
   #if ((osdSC == SC2) || (osdSC == SC1))
      #define DisableAllInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osDisableAllInterrupts())
   #else
      #define DisableAllInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osPsysDisableAllInterrupts())
   #endif
/* TR:SOSK22:0071 End */
/* TR:SOSK22:0072 End */
/* TR:SOSK22:0213 End */
/* TR:SOSK22:0216 Start */
   #if ((osdSC== SC2) || (osdSC== SC1))
      #define ResumeOSInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osResumeOSInterrupts())
   #else
      #define ResumeOSInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osPsysResumeOSInterrupts())
   #endif
/* TR:SOSK22:0216 End */
/* TR:SOSK22:0217 Start */
   #if ((osdSC == SC2) || (osdSC == SC1))
      #define SuspendOSInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osSuspendOSInterrupts())
   #else
      #define SuspendOSInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osPsysSuspendOSInterrupts())
   #endif
/* TR:SOSK22:0217 End */
/* TR:SOSK22:0214 Start */
   #if ((osdSC== SC2) || (osdSC== SC1))
      #define ResumeAllInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osResumeAllInterrupts())
   #else
      #define ResumeAllInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osPsysResumeAllInterrupts())
   #endif
/* TR:SOSK22:0214 End */
/* TR:SOSK22:0215 Start */
   #if ((osdSC == SC2) || (osdSC == SC1))
      #define SuspendAllInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osSuspendAllInterrupts())
   #else
      #define SuspendAllInterrupts() (osActiveTaskLineNumber = __LINE__, \
         osActiveTaskModule = __FILE__,  \
         osPsysSuspendAllInterrupts())
   #endif
/* TR:SOSK22:0215 End */
#else /*STATUS_LEVEL...*/
/* TR:SOSK22:0212 Start */
   #if ((osdSC == SC2) ||  (osdSC == SC1))
      #define EnableAllInterrupts() (osEnableAllInterrupts())
   #else
      #define EnableAllInterrupts() (osPsysEnableAllInterrupts())
   #endif
/* TR:SOSK22:0212 End */
/* TR:SOSK22:0071 Start */
/* TR:SOSK22:0072 Start */
/* TR:SOSK22:0213 Start */
   #if ((osdSC == SC2) || (osdSC == SC1))
      #define DisableAllInterrupts() (osDisableAllInterrupts())
   #else
      #define DisableAllInterrupts() (osPsysDisableAllInterrupts())
   #endif
/* TR:SOSK22:0071 End */
/* TR:SOSK22:0072 End */
/* TR:SOSK22:0213 End */
/* TR:SOSK22:0216 Start */
   #if ((osdSC== SC2) || (osdSC== SC1))
      #define ResumeOSInterrupts() (osResumeOSInterrupts())
   #else
      #define ResumeOSInterrupts() (osPsysResumeOSInterrupts())
   #endif
/* TR:SOSK22:0216 End */
/* TR:SOSK22:0217 Start */
   #if ((osdSC == SC2) || (osdSC == SC1))
      #define SuspendOSInterrupts() (osSuspendOSInterrupts())
   #else
      #define SuspendOSInterrupts() (osPsysSuspendOSInterrupts())
   #endif
/* TR:SOSK22:0217 End */
/* TR:SOSK22:0214 Start */
   #if ((osdSC== SC2) || (osdSC== SC1))
      #define ResumeAllInterrupts() (osResumeAllInterrupts())
   #else
      #define ResumeAllInterrupts() (osPsysResumeAllInterrupts())
   #endif
/* TR:SOSK22:0214 End */
/* TR:SOSK22:0215 Start */
   #if ((osdSC == SC2) || (osdSC == SC1))
      #define SuspendAllInterrupts() (osSuspendAllInterrupts())
   #else
      #define SuspendAllInterrupts() (osPsysSuspendAllInterrupts())
   #endif
/* TR:SOSK22:0215 End */
#endif /*STATUS_LEVEL...*/


/* resource management */

#if (STATUS_LEVEL == EXTENDED_STATUS) && !defined(osdSuppressFilenames)
/* TR:SOSK22:0218 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetResource(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetResource(x))
#else
#define GetResource(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetResource(x))
#endif
/* TR:SOSK22:0218 End */
/* TR:SOSK22:0219 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define ReleaseResource(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysReleaseResource(x))
#else
#define ReleaseResource(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osReleaseResource(x))
#endif
/* TR:SOSK22:0219 End */
#else /*STATUS_LEVEL...*/
/* TR:SOSK22:0218 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetResource(x) (osPsysGetResource(x))
#else
#define GetResource(x) (osGetResource(x))
#endif
/* TR:SOSK22:0218 End */
/* TR:SOSK22:0219 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define ReleaseResource(x) (osPsysReleaseResource(x))
#else
#define ReleaseResource(x) (osReleaseResource(x))
#endif
/* TR:SOSK22:0219 End */
#endif /*STATUS_LEVEL...*/


/* KB begin osekSemaphores (default) */
/* KB end osekSemaphores */

/* TR:SOSK22:0220 Start */
/* TR:SOSK22:0221 Start */
/* TR:SOSK22:0222 Start */
/* TR:SOSK22:0223 Start */
/* TR:SOSK22:0227 Start */
/* TR:SOSK22:0228 Start */
/* event control */
#if (CC == ECC1) || (CC == ECC2)

#if (STATUS_LEVEL == EXTENDED_STATUS) && !defined(osdSuppressFilenames)

#if ((osdSC== SC3) || (osdSC== SC4))
#define SetEvent(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysSetEvent((x), (y)))
#else
#define SetEvent(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osSetEvent((x), (y)))
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetEvent(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetEvent((x), (y)))
#else
#define GetEvent(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetEvent((x), (y)))
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define ClearEvent(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysClearEvent(x))
#else
#define ClearEvent(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osClearEvent(x))
#endif
   
#if ((osdSC== SC3) || (osdSC== SC4))
#define WaitEvent(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysWaitEvent(x))
#else
#define WaitEvent(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osWaitEvent(x))
#endif

#else /*STATUS_LEVEL...*/

#if ((osdSC== SC3) || (osdSC== SC4))
#define SetEvent(x, y) (osPsysSetEvent((x), (y)))
#else
#define SetEvent(x, y) (osSetEvent((x), (y)))
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetEvent(x, y) (osPsysGetEvent((x), (y)))
#else
#define GetEvent(x, y) (osGetEvent((x), (y)))
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define ClearEvent(x) (osPsysClearEvent(x))
#else
#define ClearEvent(x) (osClearEvent(x))
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define WaitEvent(x) (osPsysWaitEvent(x))
#else
#define WaitEvent(x) (osWaitEvent(x))
#endif

#endif /*STATUS_LEVEL...*/


#else /*CC...*/
#define SetEvent(x, y) (Event API used with wrong conformance class)
#define ClearEvent (x) (Event API used with wrong conformance class)
#define GetEvent(x, y) (Event API used with wrong conformance class)
#define WaitEvent(x)   (Event API used with wrong conformance class)
#endif /*CC...*/
/* TR:SOSK22:0220 End */
/* TR:SOSK22:0221 End */
/* TR:SOSK22:0222 End */
/* TR:SOSK22:0223 End */
/* TR:SOSK22:0227 End */
/* TR:SOSK22:0228 End */


/* alarms        */
#if (STATUS_LEVEL == EXTENDED_STATUS) && !defined(osdSuppressFilenames)

/* KB begin osekHwSetRelAlarmDefine1 (default) */
#if ((osdSC== SC3) || (osdSC== SC4))
#define SetRelAlarm(x, y, z) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysSetRelAlarm((x), (y), (z)))
#else
#define SetRelAlarm(x, y, z) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osSetRelAlarm((x), (y), (z)))
#endif
/* KB end osekHwSetRelAlarmDefine1 */

/* KB begin osekHwSetAbsAlarmDefine1 (default) */
#if ((osdSC== SC3) || (osdSC== SC4))
#define SetAbsAlarm(x, y, z) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysSetAbsAlarm((x), (y), (z)))
#else
#define SetAbsAlarm(x, y, z) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osSetAbsAlarm((x), (y), (z)))
#endif
/* KB end osekHwSetAbsAlarmDefine1 */
/* TR:SOSK22:0230 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define CancelAlarm(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysCancelAlarm(x))
#else
#define CancelAlarm(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osCancelAlarm(x))
#endif
/* TR:SOSK22:0230 End */
/* TR:SPMF09:0011 Start */
/* TR:SASR30:0383 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define IncrementCounter(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysIncrementCounter(x))
#else   
#define IncrementCounter(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osIncrementCounter(x))
#endif
/* TR:SASR30:0383 End */
/* TR:SPMF09:0011 End */
/* TR:SOSK22:0113 Start */
/* TR:SOSK22:0225 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetAlarm(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetAlarm((x), (y)))
#else
#define GetAlarm(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetAlarm((x), (y)))
#endif
/* TR:SOSK22:0113 End */
/* TR:SOSK22:0225 End */

/* TR:SASR30:0001 End */
/* TR:SASR30:0375 Start*/
#if ((osdSC== SC3) || (osdSC== SC4))
#define StartScheduleTableRel(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysStartScheduleTableRel((x), (y)))
#else
#define StartScheduleTableRel(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osStartScheduleTableRel((x), (y)))
#endif  
/* TR:SASR30:0375 End */ 
/* TR:SASR30:0376 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define StartScheduleTableAbs(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysStartScheduleTableAbs((x), (y)))
#else
#define StartScheduleTableAbs(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osStartScheduleTableAbs((x), (y)))
#endif
/* TR:SASR30:0376 End */
/* TR:SASR30:0377 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define StopScheduleTable(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysStopScheduleTable((x)))
#else
#define StopScheduleTable(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osStopScheduleTable((x)))
#endif
/* TR:SASR30:0377 End */
/* TR:SASR30:0378 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define NextScheduleTable(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysNextScheduleTable((x), (y)))
#else
#define NextScheduleTable(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osNextScheduleTable((x), (y)))
#endif
/* TR:SASR30:0378 End */
/* TR:SASR30:0382 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetScheduleTableStatus(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetScheduleTableStatus((x), (y)))
#else
#define GetScheduleTableStatus(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetScheduleTableStatus((x), (y)))
#endif
/* TR:SASR30:0382 End */
#if (osdScheduleTableSyncUsed != 0)
/* TR:SASR30:0380 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define SyncScheduleTable(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysSyncScheduleTable((x), (y)))
#else
#define SyncScheduleTable(x, y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osSyncScheduleTable((x), (y)))
#endif
/* TR:SASR30:0380 End */
/* TR:SASR30:0381 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define SetScheduleTableAsync(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysSetScheduleTableAsync(x))
#else
#define SetScheduleTableAsync(x) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osSetScheduleTableAsync(x))
#endif
/* TR:SASR30:0381 End */
/* TR:SASR30:0379 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define StartScheduleTableSynchron(x) (osActiveTaskLineNumber= __LINE__,    \
                                       osActiveTaskModule= __FILE__,        \
                                       osPsysStartScheduleTableSynchron(x))
#else
#define StartScheduleTableSynchron(x) (osActiveTaskLineNumber= __LINE__,\
                                       osActiveTaskModule= __FILE__,    \
                                       osStartScheduleTableSynchron(x))
#endif
/* TR:SASR30:0379 End */
#endif /* #if (osdScheduleTableSyncUsed != 0) */

#if osdTimingProtectionUsed

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetTaskMaxExecutionTime(x,y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetTaskMaxExecutionTime(x,y))
#else
#define GetTaskMaxExecutionTime(x,y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetTaskMaxExecutionTime(x,y))
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetISRMaxExecutionTime(x,y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetISRMaxExecutionTime(x,y))
#else
#define GetISRMaxExecutionTime(x,y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetISRMaxExecutionTime(x,y))
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetTaskMinInterArrivalTime(x,y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetTaskMinInterArrivalTime(x,y))
#else
#define GetTaskMinInterArrivalTime(x,y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetTaskMinInterArrivalTime(x,y))
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetISRMinInterArrivalTime(x,y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetISRMinInterArrivalTime(x,y))
#else
#define GetISRMinInterArrivalTime(x,y) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetISRMinInterArrivalTime(x,y))
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetTaskMaxBlockingTime(x,y,z,z1) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetTaskMaxBlockingTime(x,y,z,z1))
#else
#define GetTaskMaxBlockingTime(x,y,z,z1) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetTaskMaxBlockingTime(x,y,z,z1))
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetISRMaxBlockingTime(x,y,z,z1) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osPsysGetISRMaxBlockingTime(x,y,z,z1))
#else
#define GetISRMaxBlockingTime(x,y,z,z1) (osActiveTaskLineNumber= __LINE__,\
   osActiveTaskModule= __FILE__,\
   osGetISRMaxBlockingTime(x,y,z,z1))
#endif


#endif /*osdTimingProtectionUsed*/

#else /*STATUS_LEVEL...*/
/* TR:SASR30:0001 Start */
/* KB begin osekHwSetRelAlarmDefine2 (default) */
#if ((osdSC== SC3) || (osdSC== SC4))
#define SetRelAlarm(x, y, z) (osPsysSetRelAlarm((x), (y), (z)))
#else
#define SetRelAlarm(x, y, z) (osSetRelAlarm((x), (y), (z)))
#endif
/* KB end osekHwSetRelAlarmDefine2 */

/* KB begin osekHwSetAbsAlarmDefine2 (default) */
#if ((osdSC== SC3) || (osdSC== SC4))
#define SetAbsAlarm(x, y, z) (osPsysSetAbsAlarm((x), (y), (z)))
#else
#define SetAbsAlarm(x, y, z) (osSetAbsAlarm((x), (y), (z)))
#endif
/* KB end osekHwSetAbsAlarmDefine2 */
 /* TR:SOSK22:0230 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define CancelAlarm(x) (osPsysCancelAlarm(x))
#else
#define CancelAlarm(x) (osCancelAlarm(x))
#endif
/* TR:SOSK22:0230 End */
/* TR:SPMF09:0011 Start */   
/* TR:SASR30:0383 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define IncrementCounter(x) (osPsysIncrementCounter(x))
#else
#define IncrementCounter(x) (osIncrementCounter(x))
#endif
/* TR:SASR30:0383 End */
/* TR:SPMF09:0011 End */
/* TR:SOSK22:0113 Start */
/* TR:SOSK22:0225 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetAlarm(x, y) (osPsysGetAlarm((x), (y)))
#else
#define GetAlarm(x, y) (osGetAlarm((x), (y)))
#endif
/* TR:SOSK22:0113 End */
/* TR:SOSK22:0225 End */
/* TR:SASR30:0001 End */

/* TR:SASR30:0375 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define StartScheduleTableRel(x, y) osPsysStartScheduleTableRel((x), (y))
#else
#define StartScheduleTableRel(x, y) osStartScheduleTableRel((x), (y))
#endif
/* TR:SASR30:0375 End */
/* TR:SASR30:0376 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define StartScheduleTableAbs(x, y) osPsysStartScheduleTableAbs((x), (y))
#else
#define StartScheduleTableAbs(x, y) osStartScheduleTableAbs((x), (y))
#endif
/* TR:SASR30:0376 End */
/* TR:SASR30:0377 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define StopScheduleTable(x) osPsysStopScheduleTable((x))
#else
#define StopScheduleTable(x) osStopScheduleTable((x))
#endif
/* TR:SASR30:0377 End */
/* TR:SASR30:0378 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define NextScheduleTable(x, y) osPsysNextScheduleTable((x), (y))
#else
#define NextScheduleTable(x, y) osNextScheduleTable((x), (y))
#endif
/* TR:SASR30:0378 End */
/* TR:SASR30:0382 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define GetScheduleTableStatus(x, y) osPsysGetScheduleTableStatus((x), (y))
#else
#define GetScheduleTableStatus(x, y) osGetScheduleTableStatus((x), (y))
#endif
/* TR:SASR30:0382 End*/

#if (osdScheduleTableSyncUsed != 0)
/* TR:SASR30:0380 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define SyncScheduleTable(x, y) osPsysSyncScheduleTable((x), (y))
#else
#define SyncScheduleTable(x, y) osSyncScheduleTable((x), (y))
#endif
/* TR:SASR30:0380 End */
/* TR:SASR30:0381 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define SetScheduleTableAsync(x) osPsysSetScheduleTableAsync(x)
#else
#define SetScheduleTableAsync(x) osSetScheduleTableAsync(x)
#endif
/* TR:SASR30:0381 End */
/* TR:SASR30:0379 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
#define StartScheduleTableSynchron(x) osPsysStartScheduleTableSynchron(x)
#else
#define StartScheduleTableSynchron(x) osStartScheduleTableSynchron(x)
#endif
/* TR:SASR30:0379 End */

#endif /*osdScheduleTableSyncUsed*/


#if osdTimingProtectionUsed

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetTaskMaxExecutionTime(x,y) osPsysGetTaskMaxExecutionTime(x,y)
#else
#define GetTaskMaxExecutionTime(x,y) osGetTaskMaxExecutionTime(x,y)
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetISRMaxExecutionTime(x,y) osPsysGetISRMaxExecutionTime(x,y)
#else
#define GetISRMaxExecutionTime(x,y) osGetISRMaxExecutionTime(x,y)
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetTaskMinInterArrivalTime(x,y) osPsysGetTaskMinInterArrivalTime(x,y)
#else
#define GetTaskMinInterArrivalTime(x,y) osGetTaskMinInterArrivalTime(x,y)
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetISRMinInterArrivalTime(x,y) osPsysGetISRMinInterArrivalTime(x,y)
#else
#define GetISRMinInterArrivalTime(x,y) osGetISRMinInterArrivalTime(x,y)
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetTaskMaxBlockingTime(x,y,z,z1) osPsysGetTaskMaxBlockingTime(x,y,z,z1)
#else
#define GetTaskMaxBlockingTime(x,y,z,z1) osGetTaskMaxBlockingTime(x,y,z,z1)
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
#define GetISRMaxBlockingTime(x,y,z,z1) osPsysGetISRMaxBlockingTime(x,y,z,z1)
#else
#define GetISRMaxBlockingTime(x,y,z,z1) osGetISRMaxBlockingTime(x,y,z,z1)
#endif


#endif /*osdTimingProtectionUsed*/


#endif /*STATUS_LEVEL...*/




#if ((osdSC== SC3) || (osdSC== SC4))
#define GetApplicationID() (osPsysGetApplicationID())  /* TR:SASR30:0368 */

#define CheckObjectOwnership(x, y) (osPsysCheckObjectOwnership((x), (y)))   /* TR:SASR30:0374 */

#define CheckObjectAccess(x, y, z) (osPsysCheckObjectAccess((x), (y), (z))) /* TR:SASR30:0373 */

#define CallTrustedFunction(x, y) (osPsysCallTrustedFunction((x), (y)))     /* TR:SASR30:0370 */

#define CallNonTrustedFunction(x, y) (osPsysCallNonTrustedFunction((x), (y)))

#endif  /* ((osdSC== SC3) || (osdSC== SC4)) */


/* TR:SPMF20:0013 Start */
/* definitions for static alarms */
/* these macros should be used as parameters for SetRelAlarm/SetAbsAlarm in case of static alarms */
#define OS_STATIC_ALARM_TIME 0
#define OS_STATIC_CYCLE_TIME 0
/* TR:SPMF20:0013 End */

/* TR:SOSK22:0139 Start */
/* TR:SOSK22:0233 Start */
/* Operating system execution control */
#if ((osdSC== SC3) || (osdSC== SC4))
#define ShutdownOS(x) (osPsysShutdownOS(x)) /* TR:SOSK22:0140 */
#else
#define ShutdownOS(x) (osShutdownOS(x)) /* TR:SOSK22:0140 */
#endif
/* TR:SOSK22:0139 End */
/* TR:SOSK22:0233 End */

osqFunc1 void osqFunc2 osStartOSasm(void); /* TR:SPMF05:0001 */

/* Definition of StartOS(). */
/* Error-Checking is done is osStartOSc */
/* TR:SPMF05:0001 Start */
/* TR:SOSK22:0067 Start */
/* TR:SOSK22:0133 Start */
/* TR:SOSK22:0202 Start */
/* TR:SOSK22:0203 Start */
/* TR:SOSK22:0232 Start */
/* TR:SOSK22:0350 Start */
/* TR:SOSK22:0352 Start */
#define StartOS(x)                              \
   osActiveAppMode=(x);                         \
   osStartOSasm()
/* TR:SPMF05:0001 End */
/* TR:SOSK22:0067 End */
/* TR:SOSK22:0133 End */
/* TR:SOSK22:0202 End */
/* TR:SOSK22:0203 End */
/* TR:SOSK22:0232 End */
/* TR:SOSK22:0350 End */
/* TR:SOSK22:0352 End */

/* return application mode depending on number of AppModes */
/* TR:SOSK22:0136 Start */
/* TR:SOSK22:0231 Start */
/* TR:SOSK22:0350 Start */
/* TR:SASR30:0185 Start No error hook in GetActiveApplicationMode */
 #if ((osdSC== SC3) || (osdSC== SC4))
   /* TR:SASR30:0035 Start Context check in GetActiveApplicationMode  */
   /* TR:SASR30:0336 Start Context check in GetActiveApplicationMode  */
  #define GetActiveApplicationMode() ((osuint8)(((osdValidCtx_GetActiveApplicationMode & osCurrentContext) != 0) ? osActiveAppMode : OSINVALIDAPPMODE))
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
 #else
  #define GetActiveApplicationMode() (osActiveAppMode)
 #endif
/* TR:SASR30:0185 End */
/* TR:SOSK22:0350 End */
/* TR:SOSK22:0231 End */
/* TR:SOSK22:0136 End */

/* TR:SASR30:0185 Start No error hook in GetISRID */
/* TR:SASR30:0369 Start */
#if ((osdSC== SC3) || (osdSC== SC4))
/* TR:SASR30:0035 Start Context check in GetISRID  */
/* TR:SASR30:0336 Start Context check in GetISRID  */
#define GetISRID() (((osdValidCtx_GetISRID & osCurrentContext) != 0) ? osaActiveISRID : INVALID_ISR) /* TR:SASR30:0108 *//* TR:SASR30:0369 */
/* TR:SASR30:0336 End */
/* TR:SASR30:0035 End */
#else
#define GetISRID() (osaActiveISRID) /* TR:SASR30:0108 *//* TR:SASR30:0369 */
#endif
/* TR:SASR30:0369 End */
/* TR:SASR30:0185 End */

/* KB begin osekCallBackSectionStart (default) */
/* KB end osekCallBackSectionStart */
/* TR:SOSK22:0235 Start */
#if osdPreTaskHook
osqFunc1 void osqFunc2 PreTaskHook (void); /* TR:SOSK22:0142 */ /* TR:SOSK22:0206 */
#endif
/* TR:SOSK22:0235 End */
/* TR:SOSK22:0236 Start */
#if osdPostTaskHook
osqFunc1 void osqFunc2 PostTaskHook (void); /* TR:SOSK22:0141 */ /* TR:SOSK22:0207 */
#endif
/* TR:SOSK22:0236 End */
/* KB begin osekCallBackSectionEnd (default) */
/* KB end osekCallBackSectionEnd */

#if defined osdTestMacros || osdLib || (osdSC== SC3) || (osdSC== SC4)
 #if osdPreTaskHook
  osqFunc1 void osqFunc2 osInterPreTaskHook (void);
 #endif
 #if osdPostTaskHook
  osqFunc1 void osqFunc2 osInterPostTaskHook (void);
 #endif
#endif

#if osdStackCheck
 #if osdStackUsageMeasurement
  osqFunc1 osStackUsageType osqFunc2 osGetStackUsage(TaskType taskId); /* TR:SPMF08:0007 */
  /* KB begin osekStackUsagePrototypes (overwritten) */
  /* implementation specific prototypes for stack usage calculation */
  osStackUsageType osGetSystemStackUsage(void);
  
  /* KB end osekStackUsagePrototypes */
 #endif
#endif

/* KB begin osekHWosExternGetSystemCounter (default) */
/* TR:SOSK22:0101 Start */
#if (osdUseCounterAPI!=0)
 #define osdSystemCounterVar osCounter[SystemTimer]
#elif osdSystemCounterNeeded 
 #define osdSystemCounterVar osSystemCounter
#else
 #define osdSystemCounterVar SYSTEM_TIMER_NOT_USABLE_IN_THIS_CONFIGURATION
#endif

#define osGetSystemCounter() osdSystemCounterVar
/* TR:SOSK22:0101 End */
/* KB end osekHWosExternGetSystemCounter */


#if !defined osdProvideTimeStamp
#define osdProvideTimeStamp 0
#endif
/* TR:SPMF29:0001 Start */
/* structure for version and variant coding */
typedef struct
{
   osuint8 ucMagicNumber1;     /* magic number (e.g. for identification in hex files) */
   osuint8 ucMagicNumber2;     /* defined as osuint8 for independancy of byte order   */
   osuint8 ucMagicNumber3;     /*                                                     */
   osuint8 ucMagicNumber4;     /*                                                     */
   osuint8 ucSysVersionMaj;    /* version of operating system, Major                  */
   osuint8 ucSysVersionMin;    /* version of operating system, Minor                  */
   osuint8 ucGenVersionMaj;    /* version of code generator                           */
   osuint8 ucGenVersionMin;    /* version of code generator                           */
   osuint8 ucSysVariant1;      /* general variant coding 1                            */
   osuint8 ucSysVariant2;      /* general variant coding 2                            */
   osuint8 ucOrtiVariant;      /* ORTI version and variant     TR:SPMF14:0011  TR:SPMF29:0003        */ 
   /* KB begin osekTypeSpecVersionVariant (overwritten) */
   /* typedef of implementation specific variant coding */
   osuint16 ucSpecVariant;
   /* KB end osekTypeSpecVersionVariant */
} osVersionVariantCodingType;
/* TR:SPMF29:0001 End */

/* KB begin osekConstSectionHeaderStart (default) */
/* KB end osekConstSectionHeaderStart */
osqROM0 extern osqROM1 const osqROM2 osVersionVariantCodingType osqROM3 oskVersionVariant;
/* KB begin osekConstSectionHeaderEnd (default) */
/* KB end osekConstSectionHeaderEnd */


/* setup defines for filling up the variant coding structure */
#if CC == BCC1
   #define osdVariantCC 0U
#elif CC == BCC2
   #define osdVariantCC 1U
#elif CC == ECC1
   #define osdVariantCC 2U
#elif CC == ECC2
   #define osdVariantCC 3U
#else
#error wrong conformance class
#endif

#if STATUS_LEVEL == EXTENDED_STATUS
   #define osdVariantStatus 1U
#else
   #define osdVariantStatus 0U
#endif

#if osdNonPreempt
   #define osdVariantSchedule 0U
#elif osdFullPreempt
   #define osdVariantSchedule 1U
#elif osdMixedPreempt
   #define osdVariantSchedule 2U
#else
#error wrong scheduling policy
#endif


#if osdStackCheck
   #define osdVariantStackcheck 1U
#else
   #define osdVariantStackcheck 0U
#endif


#ifndef osdSuppressFilenames
   #define osdVariantModulnamesEnabled 1U
#else
   #define osdVariantModulnamesEnabled 0U
#endif
/* TR:SPMF12:0005 Start */
#if osdEnableAssertions
   #define osdVariantAssertionsEnabled 1U
#else
   #define osdVariantAssertionsEnabled 0U
#endif
/* TR:SPMF12:0005 End */
#if (osdSC== SC1)
   #define osdVariantSC 0U
#elif (osdSC== SC2)
   #define osdVariantSC 1U
#elif (osdSC== SC3)
   #define osdVariantSC 2U
#elif (osdSC== SC4)
   #define osdVariantSC 3U
#else
#error wrong scalability class
#endif

#if !osdLib
#if (osdNumberOfScheduleTables>0)
   #define osdVariantFeaturesUsed_ST 1U
#else 
   #define osdVariantFeaturesUsed_ST 0U
#endif
#if (osdNumberOfHiResSchedTabs>0)
   #define osdVariantFeaturesUsed_HRST 1U
#else 
   #define osdVariantFeaturesUsed_HRST 0U
#endif
#else
   #define osdVariantFeaturesUsed_ST 0U
   #define osdVariantFeaturesUsed_HRST 0U
#endif
#if (osdScheduleTableSyncUsed)
   #define osdVariantFeaturesUsed_Sync 1U
#else 
   #define osdVariantFeaturesUsed_Sync 0U
#endif
#if (osdTimingProtectionUsed)
   #define osdVariantFeaturesUsed_TP   1U
#else 
   #define osdVariantFeaturesUsed_TP   0U
#endif

#if osdORTIEnabled
/* osdORTIStdVersion is decimal coded, osdVariantORTIVersion shall be BCD coded */
#define osdVariantORTIVersion ((((osdORTIStdVersion)/100)<<4)|(((osdORTIStdVersion)%100)/10))
#define osdVariantORTIDebug osdORTIDebug
#else
#define osdVariantORTIVersion 0
#define osdVariantORTIDebug 0
#endif /*osdORTIEnabled*/



/* KB begin osekDefineSpecVersionVariant (overwritten) */
#if osdORTIDebug
   #define osdVariantORTI 1
#else
   #define osdVariantORTI 0
#endif

#if osdThumbMode
   #define osdVariantThumbMode 1
#else
   #define osdVariantThumbMode 0
#endif

#if (osdTMS570LS1x_2x==1)
   #define osdVariantDerivative 0
#endif
#if (osdTMS570LS3x==1)
   #define osdVariantDerivative 1
#endif

/* KB end osekDefineSpecVersionVariant */


#ifdef osdIncludeLibConfig

 /* include now tcb.h, but only for the application code
  * include both parts of the tcb, pre and post
  */

 #define osdPreTCB  0
 #define osdPostTCB 1

 #if (osdLibVariant == 1)
  #if defined USE_QUOTE_INCLUDES
   #include "oseklib1.h"
  #else
   #include <oseklib1.h>
  #endif
 #endif
   
 #if (osdLibVariant == 2)
  #if defined USE_QUOTE_INCLUDES
   #include "oseklib2.h"
  #else
   #include <oseklib2.h>
  #endif
 #endif
   
 #if (osdLibVariant == 3)
  #if defined USE_QUOTE_INCLUDES
   #include "oseklib3.h"
  #else
   #include <oseklib3.h>
  #endif
 #endif
   
 #if (osdLibVariant == 4)
  #if defined USE_QUOTE_INCLUDES
   #include "oseklib4.h"
  #else
   #include <oseklib4.h>
  #endif
 #endif

 #undef osdPreTCB 
 #undef osdPostTCB
      

#else

 #define osdPreTCB  0
 #define osdPostTCB 1
 #if defined USE_QUOTE_INCLUDES
  #include "tcb.h"
 #else
  #include <tcb.h>
 #endif
 #undef osdPreTCB 
 #undef osdPostTCB

#endif

/* include hardware specific header files after OSEK Typedefinitions */
/* KB begin osekHWincludeHwHeaderPostTypes (overwritten) */
/* KB end osekHWincludeHwHeaderPostTypes */

/* KB begin osekEndOfHModule (overwritten) */
/* KB end osekEndOfHModule */

/*lint -restore re-enable messages*/

#endif/* double include preventer */

/* END OF HEADER osek.h */

