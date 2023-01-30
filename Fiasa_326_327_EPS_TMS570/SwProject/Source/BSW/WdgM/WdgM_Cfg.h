/* Copyright (C) 2010-2012 TTTech Automotive GmbH. All rights reserved
 * Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
 *
 * Name
 *    WdgM_Cfg.h
 *
 * Purpose
 *   Include file for Watchdog Manager Module
 *
 * Revisions
 *
 *   11-Oct-2010  (PPU) Creation
 *   05-Nov-2010  (PPU) WDGM352, WDGM338, WDGM339 post-build defines moved
 *                      to pre-build space
 *   17-Nov-2010  (PPU) Macro validation added
 *   17-Aug-2011  (JDU) [41718] callback functions' return type is void
 *   29-Aug-2011  (PPU) [41425] RTE typedefs separated, WDGM_USE_RTE repaired
 *   18-Oct-2011  (VLE) [43092] global transitions repaired - global transition
 *                              flag introduced
 *   23-Dec-2011  (PPU) [43770] MainFunction write access to entity mem removed
 *   10-Jan-2012  (VLE) [44107] d/pf debouncing parameters optimization
 *   16-Jan-2012  (PPU) [44329] Version, Id, Checksum added to the Config
 *   27-Jan-2012  (PPU) [44257] Watchdog border Tick parameters added to config
 *   13-Mar-2012  (PPU) [45210] Hardware TickCounter implemented
 *   20-Apr-2012  (PPU) [45700] Trigger Mode implemented
 *   25-Apr-2012  (VLE) [45927] RememberedEntityId replaced by global transition
                                flags
 *   23-Aug-2012  (PPU) [48298] OS Partition Reset removed
 *   28-Aug-2012  (VLE) [46820] Compiler abstraction according to AUTOSAR
 *   04-Sep-2012  (PPU) [48587] Formal review - change the version to 2.0.0
 */



/* -------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                           */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(3:3205) The identifier 'WdgM_ModeType' / WdgM_ConfigType
                   is not used and could be removed.
 * Justification : The type 'WdgM_ModeType' / WdgM_ConfigType is used in
                   WdgM.c / WdgM.c and WdgM_Checkpoint.c.                     */

#ifndef _WDGM_CFG_H_
#define _WDGM_CFG_H_

#include "Std_Types.h"
#include "WdgIf_Types.h"

/* Timebase Tick sources
   The tick source defines are on this position as they are used
   later in the WdgM_Cfg_Features.h generated file   */
#define WDGM_INTERNAL_SOFTWARE_TICK  0  /* */
#define WDGM_INTERNAL_HARDWARE_TICK  1  /* */
#define WDGM_EXTERNAL_TICK           2  /* */

/* Generated or provided by the user - preprocessor options for module features */
#include "WdgM_Cfg_Features.h"

/* ****************************************************************************
 * Macro validation
 ******************************************************************************/

 /* S-WdgM module version */
#define WDGM_CFG_TYPES_HDR_MAJOR_VERSION      2
#define WDGM_CFG_TYPES_HDR_MINOR_VERSION      0
#define WDGM_CFG_TYPES_HDR_PATCH_VERSION      3


/* AUTOSAR features */
#ifndef WDGM_VERSION_INFO_API
    #error "Macro WDGM_VERSION_INFO_API should be defined! (STD_ON/STD_OFF)"
#endif

#ifndef WDGM_DEV_ERROR_DETECT
    #error "Macro WDGM_DEV_ERROR_DETECT should be defined! (STD_ON/STD_OFF)"
#endif

#ifndef WDGM_DEM_REPORT
    #error "Macro WDGM_DEM_REPORT should be defined! (STD_ON/STD_OFF)"
#endif

#ifndef WDGM_DEFENSIVE_BEHAVIOR
    #error "Macro WDGM_DEFENSIVE_BEHAVIOR should be defined! (STD_ON/STD_OFF)"
#endif

#ifndef WDGM_IMMEDIATE_RESET
    #error "Macro WDGM_IMMEDIATE_RESET should be defined! (STD_ON/STD_OFF)"
#endif

#ifndef WDGM_OFF_MODE_ENABLED
    #error "Macro WDGM_OFF_MODE_ENABLED should be defined! (STD_ON/STD_OFF)"
#endif

/* S-WDGM specific features */
#ifndef WDGM_GLOBAL_TRANSITIONS
    #error "Macro WDGM_GLOBAL_TRANSITIONS should be defined! (STD_ON/STD_OFF)"
#endif

#ifndef WDGM_USE_OS_SUSPEND_INTERRUPT
    #error "Macro WDGM_USE_OS_SUSPEND_INTERRUPT should be defined! (STD_ON/STD_OFF)"
#endif

#ifndef WDGM_TIMEBASE_SOURCE
    #error "Macro WDGM_TIMEBASE_SOURCE should be defined! "
#endif

#if (WDGM_TIMEBASE_SOURCE != WDGM_INTERNAL_SOFTWARE_TICK)
  #if (WDGM_TIMEBASE_SOURCE != WDGM_INTERNAL_HARDWARE_TICK)
    #if (WDGM_TIMEBASE_SOURCE != WDGM_EXTERNAL_TICK)
       #error "Macro WDGM_TIMEBASE_SOURCE should have defined value!"
     #endif
  #endif
#endif

#ifndef WDGM_TICK_OVERRUN_CORRECTION
    #error "Macro WDGM_TICK_OVERRUN_CORRECTION should be defined! (STD_ON/STD_OFF)"
#endif

#ifndef WDGM_USE_RTE
    #error "Macro WDGM_USE_RTE should be defined! (STD_ON/STD_OFF)"
#endif

#ifndef WDGM_FIRSTCYCLE_ALIVECOUNTER_RESET
    #error "Macro WDGM_FIRSTCYCLE_ALIVECOUNTER_RESET should be defined! (STD_ON/STD_OFF)"
#endif

/* Others */
#ifndef FALSE
    #error "Macro FALSE should be defined! ((boolean)0)"
#endif

#ifndef TRUE
    #error "Macro TRUE should be defined! ((boolean)1)"
#endif

#ifndef NULL_PTR
    #define NULL_PTR ((void *) 0)
#endif


/* ****************************************************************************
 * Defines
 ******************************************************************************/
/* Partition Reset defines */
#define WDGM_INVALID_OSAPPLICATION 0xFFu
typedef uint8 WdgM_ApplicationType;

/* ***************************************************************************
 * Interrupt disable/enable
 *****************************************************************************/
/* Force the user defined interrupt disable/enable functions */
#define WDGM_USE_USER_SUSPEND_INTERRUPT STD_ON

#if (WDGM_USE_OS_SUSPEND_INTERRUPT == STD_ON)
  /* Use Schedule Manager to disable/restore interrupts */
  #include "SchM_WdgM.h"
  #define WdgM_GlobalSuspendInterrupts()   SchM_Enter_WdgM(WDGM_EXCLUSIVE_AREA_0)
  #define WdgM_GlobalRestoreInterrupts()   SchM_Exit_WdgM(WDGM_EXCLUSIVE_AREA_0)
#else
  #if (WDGM_USE_USER_SUSPEND_INTERRUPT == STD_ON)
  /* User defined functions for global interrupt disable/enable */
  #define WdgM_GlobalSuspendInterrupts()   GlobalSuspendInterrupts()
  #define WdgM_GlobalRestoreInterrupts()   GlobalRestoreInterrupts()
  #else
    #define WdgM_GlobalSuspendInterrupts()
    #define WdgM_GlobalRestoreInterrupts()
  #endif /* (WDGM_USE_USER_SUSPEND_INTERRUPT == STD_ON) */
#endif /* (WDGM_USE_OS_SUSPEND_INTERRUPT == STD_ON) */


/* ****************************************************************************
 * Type definitions
 ******************************************************************************/

typedef boolean WdgM_BooleanParamType;

#if (WDGM_USE_RTE == STD_ON)
  #include "Rte_Type.h" /* */
#else

/**
 *  This type identifies an individual Supervised Entity for the Watchdog Manager.
 */
  typedef uint16 WdgM_SupervisedEntityIdType;

/**
 *  This type identifies a Checkpoint in the context of a Supervised Entity
 *  for the Watchdog Manager.
 */
  typedef uint16 WdgM_CheckpointIdType;

/**
 *  This type distinguishes the different modes that were configured
 *  for the Watchdog Manager.
 */
  typedef uint8 WdgM_ModeType; /* PRQA S 3205 */

  /**
  *  The Local Monitoring Status represents status
  *  of each Supervised Entity individually.
  */
  typedef uint8  WdgM_LocalStatusType;
  #define WDGM_LOCAL_STATUS_OK            0u
  #define WDGM_LOCAL_STATUS_FAILED        1u
  #define WDGM_LOCAL_STATUS_EXPIRED       2u
  #define WDGM_LOCAL_STATUS_DEACTIVATED   4u

/**
 *  The Global Monitoring Status summarizes
 *  the Local Monitoring Status of all Supervised Entities.
 */
  typedef uint8 WdgM_GlobalStatusType;
  #define WDGM_GLOBAL_STATUS_OK            0u
  #define WDGM_GLOBAL_STATUS_FAILED        1u
  #define WDGM_GLOBAL_STATUS_EXPIRED       2u
  #define WDGM_GLOBAL_STATUS_STOPPED       3u
  #define WDGM_GLOBAL_STATUS_DEACTIVATED   4u

#endif  /* (WDGM_USE_RTE == STD_ON) */

/**
 *  This type identifies a Transition in the context
 *  of a Checkpoint for the Watchdog Manager.
 */
typedef uint16 WdgM_TransitionIdType;

/**
 * This type represents the basic S-WDGM Timebase Tick.
 * The Transition deadlines are measured with this type.
 */
typedef uint32 WdgM_TimeBaseTickType;

/**
 * This type represents Watchdog trigger time in miliseconds.
 */
typedef uint16 WdgM_TriggerTimeMsType;

 /**
 * This type represents Watchdog trigger time in Ticks.
 */
typedef uint16 WdgM_TriggerTimeTickType;

/**
 *  This type represents alive counter.
 */
typedef uint32 WdgM_AliveCntType; /* */

/**
 *  This type represents alive counter margins.
 */
typedef uint16 WdgM_AliveMarginType;

/**
 *  This type represents supervision cycle counter.
 */
typedef uint16 WdgM_SupervisedCycCntType;

/**
 *  This type represents reference cycle tolerance.
 */
typedef uint16 WdgM_RefCycleType;

/**
 *  This type represents the physical watchdog ID.
 */
typedef uint8 WdgM_WatchdogIdType;

/**
 *  This type represents the global shared Boolean.
 */
typedef uint8 WdgM_SharedBooleanType;

/**
 *  This type represents the deadline and PF violation counter.
 */
typedef uint16 WdgM_ViolationCntType;

/**
 *  This type represents the S-WdgM configuration version.
 */
typedef uint8  WdgM_ConfigVersionType;

/**
 *  This type represents the S-WdgM configuration identificator number.
 */
typedef uint32  WdgM_ConfigIdType;

/**
 *  This type represents the S-WdgM configuration checksum.
 */
typedef uint32 WdgM_ConfigChecksumType;

/**
 *  This type represents SE deactivation/activation request.
 */
typedef uint8 WdgM_StateRequestType;

/**
 *  This type represents ID of the S-WdgM Caller.
 */
typedef uint16 WdgM_CallerIdType;

/**
 *  This type represents S-WdgM Trigger Mode.
 */
typedef uint8 WdgM_TriggerModeIdType;


/* ****************************************************************************
 * RAM structures
 *
 * Abbreviations for memory segmentation:
 * ...LType,  ...LRef     S-WdgM Local Entity RAM memory
 * ...GType,  ...GRef     S-WdgM Global RAM memory
 * ...GSType, ...GSRef    S-WdgM Global Shared RAM memory
 ******************************************************************************/

/* ****************************************************************************
 * 1. RAM structures - S-WdgM Entity Local RAM ( Application local )
 *    Write access to this memory is allowed only from context where the current
 *    entity with it's WdgM_CheckpointReached() is placed.
 ******************************************************************************/

/** Alive Counters, it's runtime values
 *  write access: WdgM_CheckpointReached() and WdgM_Init() */
typedef struct {
    VAR (WdgM_AliveCntType, AUTOMATIC) AliveCounter;
                                /**< The Alive counter for current Checkpoint */
} WdgM_AliveCounterLType;

/** WdgM entity states, it's runtime values.
 *  read access:  WdgM_CheckpointReached() and WdgM_MainFunction()
 *  write access: WdgM_CheckpointReached() and WdgM_Init() */
 typedef struct {
    VAR (WdgM_BooleanParamType, AUTOMATIC) LocalActivityFlag;
                                /**< Activated after current SE was initialized */
    VAR (WdgM_CheckpointIdType, AUTOMATIC) RememberedCheckpointId;
                                /**< The remembered ID of the last Checkpoint */
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) RememberedCheckpointTime;
                                /**< The remembered time of the last Checkpoint */
    VAR (WdgM_ViolationCntType, AUTOMATIC) DeadlineViolationCnt;
                                /**< Counter counting deadline violations
                                     in the last reference cycle */
    VAR (WdgM_ViolationCntType, AUTOMATIC) ProgramFlowViolationCnt;
                                /**< Counter counting program flow violations
                                     in the last reference cycle */
} WdgM_EntityStatusLType;

/* ****************************************************************************
 * 2. RAM structures - S-WdgM global RAM ( used by S-WdgM only)
 *    Write access to this memory is allowed only from context where the
 *    WdgM_MainFunction() is placed.
 ******************************************************************************/
/** Alive supervision counter
 *  write access: WdgM_MainFunction() */
typedef struct {
    VAR (WdgM_AliveCntType, AUTOMATIC) AliveCounterStamp;
                                /**< The Alive counter stamp for current Checkpoint */
    VAR (WdgM_AliveCntType, AUTOMATIC) SupervisionAliveCounter;
                                /**< Supervision cycle counter (counts S-WDGM cycles) */
} WdgM_AliveCounterGType;

/** WdgM entity states, it's runtime values.
 *  read access:  WdgM_MainFunction() and WdgM_CheckpointReached()
 *  write access: WdgM_MainFunction() */
typedef struct {
    VAR (WdgM_LocalStatusType, AUTOMATIC) LocalMonitoringStatus;
                                /**< Local Status of current SE, build in the cyclic
                                     supervised task */
    VAR (WdgM_SupervisedCycCntType, AUTOMATIC) FailedSupervisionRefCycles;
                                /**< Number of failed alive supervision cycles */
    VAR (WdgM_SupervisedCycCntType, AUTOMATIC) FailedDeadlineRefCycles;
                                /**< Failed reference cycle counter value for
                                     deadline violations */
    VAR (WdgM_SupervisedCycCntType, AUTOMATIC) FailedDeadlineCycCounter;
                                /**< Reference cycle counter for deadline violations */
    VAR (WdgM_SupervisedCycCntType, AUTOMATIC) FailedProgramFlowRefCycles;
                                /**< Failed reference cycle counter value for
                                     program flow violations */
    VAR (WdgM_SupervisedCycCntType, AUTOMATIC) FailedProgramFlowCycCounter;
                                /**< Reference cycle counter for program flow violations */
    VAR (WdgM_ViolationCntType, AUTOMATIC) DeadlineViolationCnt;
                                /**< Counter stamp represent deadline violations
                                     in the last reference cycle */
    VAR (WdgM_ViolationCntType, AUTOMATIC) ProgramFlowViolationCnt;
                                /**< Counter stamp represent program flow violations
                                     in the last reference cycle */
} WdgM_EntityStatusGType;


/** WdgM global data. Read by all modules (tasks).
 *  write access: WdgM_MainFunction(), WdgM_Init() and WdgM_UpdateTickCount() */
typedef struct {
    VAR (WdgM_GlobalStatusType, AUTOMATIC) GlobalMonitoringStatus;
                                /**< Global Monitoring status that summarizes
                                     the Local Monitoring status of all SE's */
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) PreviousTickCounter;
                                /**< Remebered Tick Counter */
    VAR (WdgM_SupervisedCycCntType, AUTOMATIC) ExpiredCycleCounter;
                                /**< WDGM219 Expired Cycle Counter */
    VAR (WdgM_BooleanParamType, AUTOMATIC) WdgMMainStarted;
                                /**< After MainFunction runs once
                                     it is TRUE, else FALSE */
    VAR (WdgM_TriggerModeIdType, AUTOMATIC) TriggerModeId;
                                /**< Actual Watchdog Trigger Mode */

    VAR (WdgM_TriggerModeIdType, AUTOMATIC) PreviousTriggerModeId;
                                /**< Previous Watchdog Trigger Mode */
} WdgM_DataGType;

/* ****************************************************************************
 * 3. RAM structures - S-WdgM global shared RAM ( used by S-WdgM and others )
 *    Write access to this memory is allowed from all modules. As this is
 *    a global shared memory, the variables that are used by S-WdgM shall be
 *    protected, e.g. by checksum.
  ******************************************************************************/
/** WdgM global shared data. Read and write by all modules (tasks).
    read access:  WdgM_CheckpointReached() and WdgM_MainFunction()
    write access: WdgM_CheckpointReached() and WdgM_Init() */
typedef struct {
    VAR (WdgM_SharedBooleanType, AUTOMATIC) GlobalActivityFlag;
                                /**< Gets TRUE after first valid CP was reported */
    VAR (WdgM_SharedBooleanType, AUTOMATIC) GlobalActivityFlag_neg;
                                /**< Validates 'GlobalActivityFlag' only */
    VAR (uint16, AUTOMATIC) InternalFailureFlag;
                                /**< Sigmalize a failure inside CheckpointReached() */
} WdgM_DataGSType;

/** WdgM global shared data. Read and write by all modules (tasks).
    Used by global transitions from SE_start->SE_end
    read access:  WdgM_CheckpointReached() in both SE_begin and SE_end
    write access: WdgM_CheckpointReached() in both SE_begin and SE_end */
typedef struct {
    VAR (WdgM_SharedBooleanType, AUTOMATIC) GlobalTransitionFlag;
                                /**< Initialized to FALSE. Gets TRUE when a global
                                     transition was started, FALSE when it was
                                     completed. */
    VAR (WdgM_SharedBooleanType, AUTOMATIC) GlobalTransitionFlag_neg;
                                /**< Validates 'GlobalTransitionFlag' only */
} WdgM_GlobalTransitionFlagGSType;

/** WdgM global shared data. Written by all contexts.
    Represents Entity deactivation/activation request structure */
typedef struct {
    VAR (WdgM_StateRequestType, AUTOMATIC) StateChangeRequest;
                                /**< SE deactivation/activation state request */
    VAR (WdgM_StateRequestType, AUTOMATIC) StateChangeRequest_neg;
                                /**< Validates DeactivationStatus only */
} WdgM_EntityGSType;


/* ****************************************************************************
 * ROM structures
 * This part contains S-WdgM configuration structures placed in FLASH
 ******************************************************************************/

/** Watchdog trigger and Modes */
typedef struct {
    VAR (WdgM_TriggerTimeMsType, AUTOMATIC) WdgMTriggerWindowStart;
                                /**< Minimum trigger time, unit: [ms] */
    VAR (WdgM_TriggerTimeTickType, AUTOMATIC) WdgMTriggerWindowStartTicks;
                                /**< Minimum trigger time, unit: [Timebase Ticks] */
    VAR (WdgM_TriggerTimeMsType, AUTOMATIC) WdgMTriggerTimeout;
                                /**< Watchdog timeout time, unit: [ms] */
    VAR (WdgM_TriggerTimeTickType, AUTOMATIC) WdgMTriggerTimeoutTicks;
                                /**< Watchdog timeout time, unit: [Timebase Ticks] */
    VAR (WdgIf_ModeType, AUTOMATIC) WdgMWatchdogMode;
                                /**< Watchdog mode */
} WdgM_TriggerModeType;

/** Watchdog devices */
typedef struct {
    P2CONST (WdgM_TriggerModeType, AUTOMATIC, WDGM_APPL_CONST) WdgMTriggerModeRef;
                                /**< Reference to Watchdog trigger and Mode */
} WdgM_WatchdogDeviceType;

/** Trigger Mode change allowed Callers */
 typedef struct {
    VAR (WdgM_CallerIdType, AUTOMATIC) WdgMAllowedCaller;
 } WdgM_CallersType;


/* ****************************************************************************/

/** Transition to previous Checkpoint (=Incomming Transitions only!)*/
typedef struct
{
    VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) EntitySourceId;
                                /**< The ID of the source SE for this Transition */
    VAR (WdgM_CheckpointIdType, AUTOMATIC) CheckpointSourceId;
                                /**< The ID of the source CP for this Transition */

    /* Deadline supervision setup */
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) WdgMDeadlineMin;
                                /**< WDGM317_Conf: Transition minimum time,
                                     unit: S-WDGM Timebase Tick */
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) WdgMDeadlineMax;
                                /**< WDGM318_Conf: Transition maximum time
                                     unit: S-WDGM Timebase Tick. If positive
                                     then a deadline is defined. */

} WdgM_TransitionType;

/** Global Transition to previous Checkpoint (=Incomming Global Transitions only!)*/
typedef struct
{
    VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) EntitySourceId;
                                /**< The ID of the source SE for this Transition */
    VAR (WdgM_CheckpointIdType, AUTOMATIC) CheckpointSourceId;
                                /**< The ID of the source CP for this Transition */

    /* Deadline supervision setup */
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) WdgMDeadlineMin;
                                /**< WDGM317_Conf: Transition minimum time,
                                     unit: S-WDGM Timebase Tick */
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) WdgMDeadlineMax;
                                /**< WDGM318_Conf: Transition maximum time
                                     unit: S-WDGM Timebase Tick. If positive
                                     then a deadline is defined. */
    VAR (WdgM_TransitionIdType, AUTOMATIC) GlobalTransitionFlagId;
                                /**< Global transition flag: TRUE if the global
                                     transition is active but not passed yet
                                     FALSE if the global transition is either
                                     not active or has already passed */
} WdgM_GlobalTransitionType;

/* ****************************************************************************/

/** Checkpoint */
typedef struct
{
    VAR (WdgM_CheckpointIdType, AUTOMATIC) WdgMCheckpointId;
                                /**< WDGM306_Conf, Current Checkpoint ID, [0...CP-1]*/
    VAR (WdgM_BooleanParamType, AUTOMATIC) WdgMIsEndCheckpoint;
                                /**< Does this CP terminate the entity? */
    VAR (WdgM_BooleanParamType, AUTOMATIC) WdgMIsEndCheckpointGlobal;
                                /**< Does this CP terminate the global transitions? */
    /* Alive supervision setup */
    VAR (WdgM_AliveCntType, AUTOMATIC) WdgMExpectedAliveIndications;
                                /**< WDGM311_Conf, For cyclic Alive supervision,
                                     is the number of expected counts for monitored
                                     supervision cycle  */
    VAR (WdgM_AliveMarginType, AUTOMATIC) WdgMMinMargin;
                                /**< WDGM312_Conf, Minimum margin for Alive supervision,
                                     acceptable missed counts for monitored cycle */
    VAR (WdgM_AliveMarginType, AUTOMATIC) WdgMMaxMargin;
                                /**< WDGM313_Conf, Maximum margin for Alive suprevision,
                                     acceptable additional counts for monitored cycle */
    VAR (WdgM_RefCycleType, AUTOMATIC) WdgMSupervisionReferenceCycle;
                                /**< WDGM310_Conf, amout of the supervision cycles used
                                     as reference for the Alive supervision */
    P2VAR (WdgM_AliveCounterLType, AUTOMATIC, WDGM_APPL_DATA) WdgMAliveLRef;
                                /**< Reference to Alive counter for this Checkpoint,
                                     when set to NULL_PTR then no Alive counter is defined,
                                     and the Alive monitoring for this CP is deactivated  */
    P2VAR (WdgM_AliveCounterGType, AUTOMATIC, WDGM_APPL_DATA) WdgMAliveGRef;
                                /**< Reference to Alive counter for this Checkpoint,
                                     when set to NULL_PTR then no Alive counter is defined,
                                     and the Alive monitoring for this CP is deactivated  */

    /* Transition setup */
    VAR (WdgM_BooleanParamType, AUTOMATIC) WdgMDeadlineMonitoring;
                                /**< Deadline Monitoring on/off parameter, when set to on
                                     the deadline for this CP is evaluated */
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) WdgMOutgoingDeadlineMax;
                                /**< Is Maximum Deadline of all outgoing Deadlines for current
                                     Checkpoint. Is null when no Deadline defined
                                     unit: S-WDGM Timebase Tick */
    VAR (WdgM_TransitionIdType, AUTOMATIC) NrOfLocalTransitions;
                                /**< Number of the Local Incomming Transitions,
                                     [0...N], WDGM p.100 */
    P2CONST (WdgM_TransitionType, AUTOMATIC, WDGM_APPL_CONST) WdgMLocalTransitionRef;
                                /**< Reference to array of Local Incomming Transition
                                     structures that belongs to this Checkpoint */
    VAR (WdgM_TransitionIdType, AUTOMATIC) NrOfGlobalTransitions;
                                /**< Number of Incomming global transitions
                                    [0...N], WDGM p.100 */
    P2CONST (WdgM_GlobalTransitionType, AUTOMATIC, WDGM_APPL_CONST) WdgMGlobalTransitionsRef;
                                /**< Reference to array of Global Incomming Transition
                                     structures that belongs to this Checkpoint */
    VAR (WdgM_BooleanParamType, AUTOMATIC) WdgMStartsAGlobalTransition;
                                /**< Does this CP start a global transition? */
    VAR (WdgM_TransitionIdType, AUTOMATIC) NrOfStartedGlobalTransitions;
                                /**< Number of outgoing global transitions */
    P2CONST (WdgM_TransitionIdType, AUTOMATIC, WDGM_APPL_CONST) WdgMStartedGlobalTransitionIds;
                                /**< Array of indexes of the outgoing global
                                     transitions in the GlobalTransitionFlagsGSRef
                                     array */
} WdgM_CheckPointType;

/* ****************************************************************************/

/** Supervised Entity */
typedef struct {
    VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) WdgMSupervisedEntityId;
                                /**< WDGM304_Conf, the ID of this SE, [0...SE-1] */
    VAR (WdgM_BooleanParamType, AUTOMATIC) WdgMEnableEntityDeactivation;
                                /**< Enables Entity Deactivation/Activation */
    VAR (WdgM_CheckpointIdType, AUTOMATIC) WdgMCheckpointLocInitialId;
                                /**< WDGM343_Conf, Initial Checkpoint ID for this SE */
    VAR (WdgM_CheckpointIdType, AUTOMATIC) NrOfCheckpoints;
                                /**< Number of defined CP's for this SE, 0 = No CP defined */
    P2CONST (WdgM_CheckPointType, AUTOMATIC, WDGM_APPL_CONST) WdgMCheckpointRef;
                                /**< Reference to array of Checkpoint structures,
                                     [0...CP-1] */
    VAR (WdgM_LocalStatusType, AUTOMATIC) WdgMInitialStatus;
                                /**< WDGM268,9 The initial state for this SE */
    VAR (WdgM_RefCycleType, AUTOMATIC) WdgMFailedSupervisionRefCycleTol;
                                /**< WDGM327_Conf, the number of allowed failed
                                     supervision cycles */
    VAR (WdgM_RefCycleType, AUTOMATIC) WdgMFailedDeadlineRefCycleTol;
                                /**< Reference cycle tolerance value for
                                     deadline violations */
    VAR (WdgM_RefCycleType, AUTOMATIC) WdgMDeadlineReferenceCycle;
                                /**< Reference cycle length in WdgM ticks for
                                     deadline violations */
    VAR (WdgM_RefCycleType, AUTOMATIC) WdgMFailedProgramFlowRefCycleTol;
                                /**< Reference cycle tolerance value for
                                     program flow violations */
    VAR (WdgM_RefCycleType, AUTOMATIC) WdgMProgramFlowReferenceCycle;
                                /**< Reference cycle length in WdgM ticks for
                                     program flow violations */
    VAR (WdgM_BooleanParamType, AUTOMATIC) WdgMProgramFlowMonitoring;
                                /**< Program Flow Monitoring, on/off parameter,
                                     when set to 'on' the Program Flow is evaluated */
    VAR (WdgM_ApplicationType, AUTOMATIC) OSApplication;
                                /**< ID of the OS Application this SE is part of.
                                     INVALID_OSAPPLICATION if not configured. */
    P2FUNC (void, WDGM_CODE, WdgM_LocalStateChangeCbk) (VAR (WdgM_LocalStatusType, AUTOMATIC));
                                /**< Entity Local Status Callback */
    P2VAR (WdgM_EntityStatusLType, AUTOMATIC, WDGM_APPL_DATA) EntityStatusLRef;
                                /**< Reference to Entity Status in local RAM */
    P2VAR (WdgM_EntityStatusGType, AUTOMATIC, WDGM_APPL_DATA) EntityStatusGRef;
                                /**< Reference to Entity Status in global RAM */

} WdgM_SupervisedEntityType;


/* ****************************************************************************/

/** Global Config
 *  This structure contains all post-build configurable parameters
 *  of the Watchdog Manager. A pointer to this structure is passed
 *  to the Watchdog Manager initialization function for configuration.
 */
typedef struct {
    /* Config Version, Identification */
    VAR (WdgM_ConfigVersionType, AUTOMATIC) WdgMConfigMajorVersion;
                                    /**< Is the same as S-WDGM Major version */
    VAR (WdgM_ConfigVersionType, AUTOMATIC) WdgMConfigMinorVersion;
                                    /**< Is the same as S-WDGM Minor version */
    VAR (WdgM_ConfigIdType, AUTOMATIC) WdgMConfigId;
                                    /**< Is the curent configuration identificator */
    /* ConfigSet + Mode */
    VAR (WdgM_TriggerModeIdType, AUTOMATIC) WdgMInitialTriggerModeId;
                                    /**< S-WDGM module initial trigger mode
                                        [0...N] */
    VAR (WdgM_SupervisedCycCntType, AUTOMATIC) WdgMExpiredSupervisionCycleTol;
                                    /**< WDGM329, defines the number of
                                         supervision cycles for which the watchdog
                                         reset trigger should be postponed */
    VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) WdgMGlobInitialEntityId;
                                    /**< Entity ID of the Global Initial Checkpoint */
    VAR (WdgM_CheckpointIdType, AUTOMATIC) WdgMGlobInitialCheckpointId;
                                    /**< Global Initial Checkpoint Id */
    VAR (WdgM_CheckpointIdType, AUTOMATIC) NrOfAllCheckpoints;
                                    /**< Number of all Checkpoints */
    VAR (WdgM_TransitionIdType, AUTOMATIC) NrOfGlobalTransitions;
                                    /**< Number of global transitions in the
                                         configuration */
    /* Watchdog device(s) */
    VAR (WdgM_WatchdogIdType, AUTOMATIC) NrOfWatchdogDevices;
                                    /**< Number of Watchdogs, 0 = no Watchdog */
    VAR (WdgM_TriggerModeIdType, AUTOMATIC) NrOfTriggerModes;
                                    /**< Number of Watchdogs trigger modes
                                         [1...N], trigger must be defined */
    P2CONST (WdgM_WatchdogDeviceType, AUTOMATIC, WDGM_APPL_CONST) WdgMWatchdogDeviceRef;
                                    /**< WDGM349_Conf, reference to the array
                                         of Watchdog structures */

    /* SetMode Callers */
    VAR (WdgM_CallerIdType, AUTOMATIC) NrOfAllowedCallers;
                                    /**< Number of allowed SetMode callers
                                         [0,...,255], when 0 then caller is not allowed */
    P2CONST (WdgM_CallersType, AUTOMATIC, WDGM_APPL_CONST) WdgMCallersRef;
                                    /**< Reference to callers array */

    /* Entities */
    VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) NrOfSupervisedEntities;
                                    /**< Number of all Supervised Entities,
                                         0 = no SE defined */
    P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) WdgMSupervisedEntityRef;
                                    /**< Reference to array of SE structures,
                                        [0...SE-1] */
    /* RAM data structures */
    P2VAR (WdgM_DataGType, AUTOMATIC, WDGM_APPL_DATA) DataGRef;
                                    /**< Reference to S-WDGM Global RAM data */
    P2VAR (WdgM_DataGSType, AUTOMATIC, WDGM_APPL_DATA) DataGSRef;
                                    /**< Reference to S-WDGM Global shared RAM data  */
    P2VAR (WdgM_EntityGSType, AUTOMATIC, WDGM_APPL_DATA) EntityGSRef;
                                    /**< Reference to S-WDGM Global shared data array
                                         for an Entiy */
    P2VAR (WdgM_GlobalTransitionFlagGSType, AUTOMATIC, WDGM_APPL_DATA) GlobalTransitionFlagsGSRef;
                                    /**< Reference to S-WDGM Global shared array
                                         of global transition flags */
    /* Callback notification */
    P2FUNC (void, WDGM_CODE, WdgM_GlobalStateChangeCbk) (VAR (WdgM_GlobalStatusType, AUTOMATIC));
                                    /**< Global Status Callback, NULL_PTR when not used */
    /* Config Checksum */
    VAR (WdgM_ConfigChecksumType, AUTOMATIC) WdgMConfigChecksum;
                                    /**< Is the current S-WDGM configuration checksum */

}  WdgM_ConfigType; /* PRQA S 3205 */


#endif  /*_WDGM_CFG_H_*/


