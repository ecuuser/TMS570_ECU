/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: OSEK 2.2 / Autosar OS 3.0
|    File Name: osek.h
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.03
|
|  Description: contains OSEK/AUTOSAR types and defines
|               (to be used by safety related code and QM code)
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2011-2012 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* MISRA RULE 19.15 VIOLATION: The QAC-Tool states a violation of rule 19.15 with 
 * message 0883 below. Anyhow, there is a double include prevention and therefore,
 * the message is considered to be wrong. */
/* double include preventer */
#ifndef _OSEKTYPE_H      /* PRQA S 0883 EOF */ /* see MISRA comment above */
#define _OSEKTYPE_H

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

/* application error code */
#define INVALID_OSAPPLICATION 0xFFU /* TR:SASR30:0352 */


/* OS type definitions */
/* KB begin osTypeDefinitions (default) */
typedef unsigned char  osuint8;
typedef unsigned short osuint16;
typedef unsigned long  osuint32;
typedef signed   char  osint8;
typedef signed   short osint16;
typedef signed   long  osint32;
/* KB end osTypeDefinitions */

/* Boolean definition */
/* KB begin osekBooleanDef (overwritten) */
#ifndef osbool
 #define osbool osuint8
#endif
/* KB end osekBooleanDef */

/* Type for boolean arrays */
/* KB begin osekBooleanArrayBaseTypeDef (default) */
typedef osbool osBoolArrayBaseType;
/* KB end osekBooleanArrayBaseTypeDef */

/* implementation specific types (OSEK types) */
/* KB begin osekTypes (overwritten) */
/*
    !!! Max priorities: Min(2^(sizeof(osPrioType)*8), 2^(sizeof(osPrioOffsetType)*8) * sizeof(osPrioFlagType)*8)

*/
typedef osuint16       osPrioType;         /* TR:SOSK22:0023 */ /* has to be unsigned (invalid is higher than others) */
typedef osuint8        osPrioOffsetType;   /* TR:SOSK22:0023 */
typedef osuint32       osPrioFlagType;     /* TR:SOSK22:0023 */
typedef osuint32       osResAccessMaskType;

typedef osuint32       osStartFlagType;
typedef osuint8        osTypeIntLevel;
typedef osuint8        osContextOverlayType;
typedef osuint8        osTaskPreemptionType;
typedef osuint8        osTaskFlagType;
typedef osuint8        osQEntryCountType;
typedef osuint8        osActivationCountType;
typedef osuint32       osStackDataType;
typedef osuint32       osStackSizeType;
typedef osuint16       osTaskIndexType;     /* TR:SOSK22:0021 */ /* TR:SOSK22:0156 */
typedef osuint16       osResourceIndexType; /* TR:SOSK22:0024 */ /* TR:SOSK22:0025 */
typedef osuint16       osAlarmIndexType;    /* TR:SPMF81:0002 */ /* TR:SOSK22:0026 */

typedef osuint32       PhysicalTimeType; /* TR:SASR30:0367 */

#define osdMaxAllowedTimeStamp 0xffffffffU
/* KB end osekTypes */

/* Autosar types */
/* KB begin atosTypes (overwritten) */
typedef osuint16                 osProcessType;
typedef osuint16                 ISRType;              /* TR:SASR30:0360 */
typedef osuint16                 ScheduleTableType;    /* TR:SASR30:0344 *//* TR:SASR30:0345 *//* TR:SASR30:0361 */
typedef osuint8                  ScheduleTableStatusType;                  /* TR:SASR30:0362 */
typedef ScheduleTableStatusType* ScheduleTableStatusRefType;               /* TR:SASR30:0363 */
typedef osuint8                  RestartType;          /* TR:SASR30:0366 */
typedef osuint16                 CounterType;          /* TR:SPMF81:0003 *//* TR:SASR30:0347 *//* TR:SASR30:0364 */
typedef osuint8                  ProtectionReturnType; /* TR:SASR30:0365 */
typedef osuint8                  ApplicationType;      /* TR:SASR30:0346 *//* TR:SASR30:0352 */
typedef osuint16                 TrustedFunctionIndexType;                 /* TR:SASR30:0353 */
typedef void*                    TrustedFunctionParameterRefType;          /* TR:SASR30:0354 */
typedef void (*TrustedFunctionType)(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);

typedef TrustedFunctionIndexType NonTrustedFunctionIndexType;
typedef TrustedFunctionParameterRefType NonTrustedFunctionParameterRefType;
typedef TrustedFunctionType      NonTrustedFunctionType;

typedef osuint8                  AccessType;             /* TR:SASR30:0355 */
typedef osuint32                 ApplAccessMaskType;
typedef osuint8                  ObjectAccessType;       /* TR:SASR30:0356 */
typedef osuint8                  ObjectTypeType;         /* TR:SASR30:0357 */
typedef osuint16                 ObjectIDType;
typedef osuint32                 MemoryAddressType;
typedef void*                    MemoryStartAddressType; /* TR:SASR30:0358 */
typedef osuint32                 MemorySizeType;         /* TR:SASR30:0359 */

typedef osuint32                 osTPTimeStampType;
typedef osuint32                 osTPTimeType;
typedef osTPTimeType*            osTPTimeRefType;
/* KB end atosTypes */

/* typesdefs  */
/* KB begin osekHWosTaskFctType (default) */
typedef void                (*osTaskFctType)(void);
/* KB end osekHWosTaskFctType */

typedef osuint16              osStackUsageType;
typedef osuint8               osTaskStateType;
/* KB begin osekHWosStackPtrType (default) */
typedef void *              osStackPtrType;
/* KB end osekHWosStackPtrType */
typedef osuint8               osResCounterType;
typedef osuint32             TickType; /* TR:SOSK22:0306 */
typedef osint32              osTickTimeDiffType;

/* KB begin osDebugLineType (default) */
typedef int osLineNumberType;
/* KB end osDebugLineType */

/* KB begin osekOSEKTypes (overwritten) */
/* MPU setting for private data: 
   no instruction fetches enabled, full access, non-shared, 
   Outer and Inner Non-cacheable, memory type normal */
#define osdMPUAccessCtrlData  0x1308 

/* MPU setting for code: 
   instruction fetches enabled, Privileged/User read-only, non-shared, 
   Outer and Inner Non-cacheable, memory type normal */
#define osdMPUAccessCtrlCode  0x0608

/* MPU setting for default memory: 
   no instruction fetches enabled, Privileged R/W, User read-only, non-shared, 
   Outer and Inner Non-cacheable, memory type normal */
#define osdMPUAccessCtrlDefault 0x1208



typedef osuint32            EventMaskType; /* TR:SOSK22:0284 */
typedef osuint32            osStdFlagType;
typedef osTaskIndexType     TaskType;      /* TR:SOSK22:0156 */
typedef osResourceIndexType ResourceType;  /* TR:SOSK22:0268 */
typedef osAlarmIndexType    AlarmType;     /* TR:SOSK22:0359 */

typedef AlarmType osTIPType;
#define osdAutomaticEventMaskType /* enables automatic size calculation */

typedef osuint8              osIntLevelType;

#define osdStackAreaID         0
#define osdApplDataAreaID      1  
#define osdArea4ID             2
#define osdApplInitDataAreaID  3
#define osdArea6ID             4
#define osdAreaSharedGlobal    5
#define osdArea8ID             6
#define osdArea9ID             7
#define osdArea10ID            8
#define osdArea11ID            9
#define osdConstAreaID        10
#define osdCodeAreaID         11
#define osdLastAreaNr         11
#define osdLastWritableProtectionArea 9


/* KB end osekOSEKTypes */

/* KB begin osekDispatcherLockType (default) */
typedef osuint8               osDispatcherLockType;
/* KB end osekDispatcherLockType */

/* KB begin osekHwMemoryQualifierDefines (overwritten) */
/* osqROM0 extern osqROM1 const osqROM2 osVersionVariantCodingType osqROM3 oskVersionVariant;  */
/* osqROM0 osqROM1 const osqROM2 osVersionVariantCodingType osqROM3 oskVersionVariant; */
#define osqROM0
#define osqROM1
#define osqROM2
#define osqROM3

/* extern osqPROM1 const osqPROM2 char osqPROM3 * osqROM1 const osqROM2 osqROM3 oskTcbTaskName[osdNumberOfAllTasks]; */
#define osqPROM1
#define osqPROM2
#define osqPROM3

/* osqRAM0 osqRAM1 volatile osqRAM2 TickType osqRAM3 osSystemCounter; */
/* osqRAM0 osqRAM1 osqRAM2 osDispatcherLockType osqRAM3 osLockDispatcher; */
#define osqRAM0 
#define osqRAM1 
#define osqRAM2 
#define osqRAM3 

/* osqPRAM1 char osqPRAM2 * osqPRAM3 osActiveTaskModule; */
#define osqPRAM1
#define osqPRAM2
#define osqPRAM3

/* osqRAM0 osqRAM1 volatile osqRAM2 TickType osqRAM3 osSystemCounter; (for safe context variables) */
/* osqRAM0 osqRAM1 osqRAM2 osDispatcherLockType osqRAM3 osLockDispatcher; (for safe context variables) */
#define osqScRAM0 
#define osqScRAM1 
#define osqScRAM2 
#define osqScRAM3 

/* osqPRAM1 char osqPRAM2 * osqPRAM3 osActiveTaskModule; (for safe context variables) */
#define osqScPRAM1
#define osqScPRAM2
#define osqScPRAM3

/* osqBOOL1 volatile osqBOOL2 osbool osqBOOL3 osStartDispatcher; */
#define osqBOOL1 
#define osqBOOL2 
#define osqBOOL3 

/* osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osCounter[5]; */
/* extern osqTcbRAM1 osqTcbRAM2 osQEntryCountType osqTcbRAM3 osQReadyTaskHead[osdNumberOfPriorities]; */
#define osqTcbRAM1 
#define osqTcbRAM2 
#define osqTcbRAM3 

/* extern (osqPTcbRAM1 osqPTcbRAM2 TaskType osqPTcbRAM3 *) osqROM1 const osqROM2 osqROM3 oskQActivationQueues[osdNumberOfPriorities]; */
#define osqPTcbRAM1 
#define osqPTcbRAM2 
#define osqPTcbRAM3 

/* osqStack1 osqStack2 osStackDataType osqStack3 osTaskStack1[80]; */
#define osqStack1
#define osqStack2
#define osqStack3

/* osqFunc1 void osqFunc2 Function1(void); */
#define osqFunc1
#define osqFunc2 

/* qualifiers for inline functions (one qualifier for each function) */
#define osqInlineGetHighPrioBit
/* KB end osekHwMemoryQualifierDefines */

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
typedef osuint8 StatusType; /* TR:SOSK22:0151 */
#define E_OK 0 /* TR:SOSK22:0147 */ /* TR:SOSK22:0152 */

#endif

typedef osuint8              TaskStateType;    /* TR:SOSK22:0158 */ 
typedef osuint8              AppModeType;      /* TR:SOSK22:0349 */
typedef TaskType            *TaskRefType;      /* TR:SOSK22:0157 */
typedef TaskStateType       *TaskStateRefType; /* TR:SOSK22:0159 */
typedef TickType            *TickRefType;      /* TR:SOSK22:0307 */
typedef EventMaskType       *EventMaskRefType; /* TR:SOSK22:0285 */
typedef ISRType             *ISRRefType;

#define INVALID_ISR  ((ISRType)(0xFFFFFFFFUL))
/* TR:SOSK22:0239 Start */
#define INVALID_TASK ((TaskType)(0xFFFFFFFFUL)) /* TR:SOSK22:0249 */

/* idle definition for task */
#define osdNoActiveTask   INVALID_TASK
/* TR:SOSK22:0239 End */
/* idle definition for prio */
#define osdNoActivePrio   ((osPrioType)(0xFFFFFFFFUL))

/* KB begin osekHWosIsrStoredInfoStructType (overwritten) */
typedef struct{
   ISRType IsrId;
   osIntLevelType InitialIntLevel;
   osuint8 ORTIServiceId;
   osbool   InSystemFct;
   ApplicationType savedApplID;
   ISRType currentISRID;
   osbool isKilled;
   osuint32 stackstart;
   osuint32 reqMask0;
   osuint32 reqMask1;
   osuint32 reg2start;
   osuint32 reg2sizecfg;
   osuint32 reg3start;
   osuint32 reg3sizecfg;
   osuint32 reg4start;
   osuint32 reg4sizecfg;
   osuint32 reg4access;
   osuint32 reg5start;
   osuint32 reg5sizecfg;
   osuint32 reg6start;
   osuint32 reg6sizecfg;
   osuint32 reg6access;
   osuint32 reg8start;
   osuint32 reg8sizecfg;
   osuint32 reg8access;
   osuint32 reg9start;
   osuint32 reg9sizecfg;
   osuint32 reg9access;
   osuint32 reg10start;
   osuint32 reg10sizecfg;
   osuint32 reg10access;
   osuint32 reg11start;
   osuint32 reg11sizecfg;
   osuint32 reg11access;
   osuint16 prevContext;
}osIsrStoredInfoType;
/* KB end osekHWosIsrStoredInfoStructType */

#define osdFALSE 0U
#define osdTRUE  1U

#define osdNULL ((osqPROM1 osqPROM2 void osqPROM3 *)0)


/* TR:SOSK22:0122 Start */
/* TR:SOSK22:0146 Start */
/* TR:SASR30:0336 Start Definition of valid context for OS APIs */
/* context constants */
#define osdCtxTask           ((osuint16)0x0001)
#define osdCtxISRCat2        ((osuint16)0x0002) /* TR:SOSK22:0070 */
#define osdCtxPreTaskHook    ((osuint16)0x0004)
#define osdCtxPostTaskHook   ((osuint16)0x0008)
#define osdCtxErrorHook      ((osuint16)0x0010)
#define osdCtxApplErrorHook  ((osuint16)0x0020)
#define osdCtxEachErrorHook  ((osuint16)0x0030)  /* system and appl spec. ErrorHook */
#define osdCtxStartupHook    ((osuint16)0x0040)
#define osdCtxShutdownHook   ((osuint16)0x0080)
#define osdCtxProtectionHook ((osuint16)0x0100)
/* context constants for COM */
#define osdCtxCOMErrorHook   ((osuint16)0x0200)
#define osdCtxCOMCallback    ((osuint16)0x0400)
#define osdCtxStartComExtens ((osuint16)0x0800)
/* additional flag for ErrorHook called from StartupHook */
#define osdCtxErrorHookFromStartupHook ((osuint16)0x1000)
/* TR:SOSK22:0070 Start */
/* allowed call context for each API function */
#define osdValidCtx_ActivateTask             (  osdCtxTask           | osdCtxISRCat2        ) /* TR:SOSK22:0162 */
#define osdValidCtx_GetResource              (  osdCtxTask           | osdCtxISRCat2        ) /* TR:SOSK22:0271 */
#define osdValidCtx_ReleaseResource          (  osdCtxTask           | osdCtxISRCat2        ) /* TR:SOSK22:0277 */
#define osdValidCtx_SetEvent                 (  osdCtxTask           | osdCtxISRCat2        ) /* TR:SOSK22:0286 */
/* TR:SOSK22:0116 Start */
#define osdValidCtx_SetRelAlarm              (  osdCtxTask           | osdCtxISRCat2        ) /* TR:SOSK22:0324 */
#define osdValidCtx_SetAbsAlarm              (  osdCtxTask           | osdCtxISRCat2        ) /* TR:SOSK22:0332 */
#define osdValidCtx_CancelAlarm              (  osdCtxTask           | osdCtxISRCat2        ) /* TR:SOSK22:0339 */
/* TR:SOSK22:0116 End */
#define osdValidCtx_CallTrustedFunction      (  osdCtxTask           | osdCtxISRCat2        )
#define osdValidCtx_CallNonTrustedFunction   (  osdCtxTask           | osdCtxISRCat2        )
#define osdValidCtx_StartScheduleTableRel    (  osdCtxTask           | osdCtxISRCat2        ) 
#define osdValidCtx_StartScheduleTableAbs    (  osdCtxTask           | osdCtxISRCat2        ) 
#define osdValidCtx_StopScheduleTable        (  osdCtxTask           | osdCtxISRCat2        ) 
#define osdValidCtx_NextScheduleTable        (  osdCtxTask           | osdCtxISRCat2        ) 
#define osdValidCtx_SyncScheduleTable        (  osdCtxTask           | osdCtxISRCat2        ) 
#define osdValidCtx_GetScheduleTableStatus   (  osdCtxTask           | osdCtxISRCat2        ) 
#define osdValidCtx_SetScheduleTableAsync    (  osdCtxTask           | osdCtxISRCat2        ) 
#define osdValidCtx_IncrementCounter         (  osdCtxTask           | osdCtxISRCat2        ) 
#define osdValidCtx_TerminateTask            (  osdCtxTask                                  ) 
#define osdValidCtx_ChainTask                (  osdCtxTask                                  ) 
#define osdValidCtx_Schedule                 (  osdCtxTask                                  ) 
#define osdValidCtx_ClearEvent               (  osdCtxTask                                  ) 
#define osdValidCtx_WaitEvent                (  osdCtxTask                                  ) 
/* TR:SOSK22:0240 Start */
#define osdValidCtx_GetTaskID                (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxEachErrorHook  | osdCtxPreTaskHook        \
                                              | osdCtxPostTaskHook   | osdCtxProtectionHook     \
                                              | osdCtxCOMErrorHook                          ) 
/* TR:SOSK22:0240 End */
/* TR:SOSK22:0242 Start */
#define osdValidCtx_GetTaskState             (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxEachErrorHook  | osdCtxPreTaskHook        \
                                              | osdCtxPostTaskHook   | osdCtxCOMErrorHook   ) /* TR:SOSK22:0296 */
/* TR:SOSK22:0242 End */
#define osdValidCtx_GetEvent                 (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxEachErrorHook  | osdCtxPreTaskHook        \
                                              | osdCtxPostTaskHook                          )
#define osdValidCtx_GetAlarmBase             (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxEachErrorHook  | osdCtxPreTaskHook        \
                                              | osdCtxPostTaskHook                          ) /* TR:SOSK22:0314 */
#define osdValidCtx_GetAlarm                 (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxEachErrorHook  | osdCtxPreTaskHook        \
                                              | osdCtxPostTaskHook                          ) /* TR:SOSK22:0318 */
#define osdValidCtx_GetActiveApplicationMode (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxEachErrorHook  | osdCtxPreTaskHook        \
                                              | osdCtxPostTaskHook   | osdCtxStartupHook        \
                                              | osdCtxShutdownHook                          ) /* TR:SOSK22:0351 */
#define osdValidCtx_ShutdownOS               (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxEachErrorHook  | osdCtxStartupHook        \
                                              | osdCtxCOMErrorHook                          ) /* TR:SOSK22:0355 */
#define osdValidCtx_GetISRID                 (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxEachErrorHook  | osdCtxProtectionHook     \
                                              | osdCtxCOMErrorHook                          ) 
#define osdValidCtx_CheckObjectAccess        (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxEachErrorHook  | osdCtxProtectionHook     \
                                              | osdCtxCOMErrorHook                          ) 
#define osdValidCtx_CheckObjectOwnership     (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxEachErrorHook  | osdCtxProtectionHook     \
                                              | osdCtxCOMErrorHook                          ) 
#define osdValidCtx_TerminateApplication     (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxApplErrorHook                         ) 
#define osdValidCtx_StartScheduleTableSynchron (  osdCtxTask           | osdCtxISRCat2      ) 
/* 
   Remarks:  
   - No checks for interrupt enable/disable functions because these functions
     can be called inside Cat1 ISRs (which can occur inside each context)  TR:SOSK22:0253  TR:SOSK22:0257 
                                                                           TR:SOSK22:0259  TR:SOSK22:0262
                                                                           TR:SOSK22:0264  TR:SOSK22:0357
   - No context mask for StartOS, because StartOS is only allowed outside
     the defined call contexts
*/
/* allowed call context for each COM-API function */
#define osdValidCtx_StartCOM                 (  osdCtxTask           | osdCtxISRCat2)
#define osdValidCtx_StopCOM                  (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxErrorHook      | osdCtxShutdownHook       \
                                              | osdCtxCOMErrorHook                          )
#define osdValidCtx_SendMessage              (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxCOMCallback                           )
#define osdValidCtx_ReceiveMessage           (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxCOMCallback                           )
#define osdValidCtx_GetMessageStatus         (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxCOMErrorHook   | osdCtxCOMCallback    )
#define osdValidCtx_InitMessage              (  osdCtxTask           | osdCtxISRCat2            \
                                              | osdCtxCOMErrorHook   | osdCtxCOMCallback        \
                                              | osdCtxStartComExtens                        )
/* TR:SASR30:0336 End */
/* TR:SOSK22:0122 End */
/* TR:SOSK22:0146 End */
/* TR:SOSK22:0070 End */

/* TR:SOSK22:0034 Start */
/* state of tasks */
#define PRE_READY       0
/* TR:SOSK22:0241 Start */
#define RUNNING         1  /* TR:SOSK22:0036 */ /* TR:SOSK22:0245 */
#define WAITING         2  /* TR:SOSK22:0038 */ /* TR:SOSK22:0246 */
#define READY           3  /* TR:SOSK22:0037 */ /* TR:SOSK22:0247 */
#define SUSPENDED       4  /* TR:SOSK22:0039 */ /* TR:SOSK22:0248 */
/* TR:SOSK22:0241 End */
/* TR:SOSK22:0034 End */
                                              
/* return codes for protection hook */
#ifndef OS_SUPPRESS_PROTHOOK_OLD_RET_VALS
#define PRO_KILLTASKISR           1U
#define PRO_KILLAPPL              2U
#define PRO_KILLAPPL_RESTART      3U
#endif /*OS_SUPPRESS_PROTHOOK_OLD_RET_VALS*/
/* TR:SASR30:0365 Start Possible values of ProtectionReturnType */
#define PRO_TERMINATETASKISR      1U
#define PRO_TERMINATEAPPL         2U
#define PRO_TERMINATEAPPL_RESTART 3U
#define PRO_SHUTDOWN              4U
#define PRO_IGNORE                5U
/* TR:SASR30:0365 End */

/* idle definition for resource list */
#define osdNoResource   ((ResourceType)(0xFFFFFFFFUL))

/* KB begin osekHWDefineDummyRead (default) */
#define osdDummyRead(x) ((x) = (x));         /* to avoid compiler warning */
/* KB end osekHWDefineDummyRead */

/*lint -restore re-enable messages*/

#endif/* double include preventer */

/* END OF HEADER osektype.h */

