/* Copyright (C) 2010-2012 TTTech Automotive GmbH. All rights reserved
 * Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
 *
 * Name
 *    WdgM.c
 *
 * Purpose
 *   Watchdog Manager main file
 *
 * Revisions
 *
 *   11-Oct-2010  (PPU) Creation
 *   05-Nov-2010  (PPU) WDGM352, WDGM338, WDGM339 post-build defines moved
 *                      to pre-build space
 *   04-Jul-2011  (PPU) [41323] #include MemMap.h for code added,
 *   20-Jul-2011  (PPU) [41673] WdgMCheckpointLocInitialId is always zero
 *   21-Jul-2011  (PPU) [41408] Entity Deactivation/Activation added
 *   22-Jul-2011  (PPU) [41718] Callback for Local and Global status added
 *   31-Aug-2011  (PPU) [41739] Overflow correction repaired
 *   05-Sep-2011  (PPU) [42340] for safety reasons use the primary reset path
 *                              for IMMEDIATE_RESET
 *   12-Sep-2011  (PPU) [42477] WDGM134, notification in STATE_STOPPED removed
 *   13-Sep-2011  (PPU) [42503] WDGM129, error message to DEM in STATE_STOPPED
 *   15-Sep-2011  (PPU) [42526] Removed compiling warnings (DisableEntity part)
 *   21-Sep-2011  (PPU) [42537] WDGM_DEM_SUPERVISION_REPORT moved to WdgM_Cfg_Feature.h file
 *   30-Sep-2011  (PPU) [42797] Compiler warnings removed,
 *                              the SE deactivation/activation simplified
 *   11-Sep-2011  (PPU) [42943] SE Deactivation/Activation issue removed
 *   18-Oct-2011  (VLE) [43092] global transitions repaired - global transition
 *                              flag introduced
 *   09-Dec-2011  (PPU) [43881] Unused variable removed
 *   23-Dec-2011  (PPU) [43770] MainFunction write access to entity mem removed
 *   10-Jan-2012  (VLE) [44107] d/pf debouncing parameters optimization
 *   19-Jan-2012  (PPU) [43913] MainFunction() interrupted by Checkpoint() corrections
 *   02-Feb-2012  (PPU) [44257] Number of Ticks in SupervisionCycle check added
 *   02-Mar-2012  (PPU) [44418] Checksum for configuration added
 *   13-Mar-2012  (PPU) [45210] Hardware TickCounter implemented
 *   20-Apr-2012  (PPU) [45700] Trigger Mode implemented
 *   25-Apr-2012  (VLE) [45927] RememberedEntityId replaced by global transition
 *                              flags
 *   27-Apr-2012  (VLE) [45959] Periodicity of deadline and program flow
 *                              tolerances repaired
 *   10-May-2012  (VLE) [46206] Minor changes to increase test coverage
 *   06-Jul-2012  (VLE) [47131] Combined X-Y-Monitoring violations repaired
 *   07-Jul-2012  (VLE) [47328] Uninitialized local variable - repaired
 *   07-Jul-2012  (VLE) [45709] Alive counter overrun problem solved
 *   13-Aug-2012  (VLE) [48167] AUTOSAR 3.1 compatibility function naming
 *   21-Aug-2012  (VLE) [47131] Combined X-Y-Monitoring optimized for coverage
 *   22-Aug-2012  (VLE) [46993] External modules Det, Dem, Mcu, BswM_WdgM
 *                              replaced by user-defined Appl_* modules
 *   23-Aug-2012  (PPU) [48298] OS Partition Reset removed
 *   28-Aug-2012  (PPU) [48320] First cycle Alive counter reset
 *   28-Aug-2012  (VLE) [46820] Compiler abstraction according to AUTOSAR
 *   04-Sep-2012  (PPU) [48587] Formal review - change the version to 2.0.0
 */



/* -------------------------------------------------------------------------- */
/*                        GENERAL JUSTIFICATIONS                              */
/* -------------------------------------------------------------------------- */
/* Tracebility to UDD Checklist p. 6.1
 * Justification : The Traceability to UDD is given by clear and unique function
                   names, defines and parameters. The traceability to AUTOSAR is
                   done by using label WDGMxyz: what coresponds to the AUTOSAR
                   used specification                                         */
/* -------------------------------------------------------------------------- */



/* -------------------------------------------------------------------------- */
/*                         SUPRESSED MISRA VIOLATONS                          */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:5087) #include statements in a file should only be
   preceded by other preprocessor directives or comments.
 * Justification : MemMap-pragmas must be included here. See AUTOSAR
 *                 requirement MEMMAP003.                                     */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:1503) The function 'XXX' is
                   defined but is not used within this project.
 * Justification : The function 'XXX' is the interface of this SW module
                   to the other SW modules.                                   */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:2006) 'YYYY' has more than one 'return' path.
 * Justification : The function YYYY' has more as one return paths to improve
                   runtime behavior and code readability. It is used in
                   function start phase by input parameter check only. All the
                   returns are preceeded by a Det call.                       */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:2018) This switch default label is unreachable.
 * Justification : As the switch jump variable lives together with other task
                   variables, there is potential possibility of it's corruption.
                   To capture this failure we use the 'default:' statement.   */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:3408) 'g_wdgm_cfg_ptr' has external linkage but is
                   being defined without any previous declaration.
 * Justification : 'g_wdgm_cfg_ptr' is used only in the S-WdgM sources and must
                   not be visible to other software modules.                  */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:1505) The function 'WdgM_GetTickCount' is only
                   referenced in the translation unit where it is defined.
 * Justification : 'WdgM_GetTickCount' is being referenced by both WdgM.c and
                   WdgM_Checkpoint.c.                                         */

/* ****************************************************************************
 * Remark
 * In the whole module
 *  - the term 'current', 'actual' means the runtime value (e.g. current Checkpoint)
 *  - the term 'configured', 'defined' means the value comming from configuration
 ******************************************************************************/

/* ****************************************************************************
 * Includes
 ******************************************************************************/
#include "WdgM.h"
#include "WdgIf.h"
#if (WDGM_DEV_ERROR_DETECT == STD_ON)
    #include "Appl_Det.h"
#endif /* (WDGM_DEV_ERROR_DETECT == STD_ON) */
#if (WDGM_DEM_REPORT == STD_ON)
    #include "Appl_Dem.h"
#endif /* (WDGM_DEM_REPORT == STD_ON) */
#if (WDGM_SECOND_RESET_PATH == STD_ON)
    #include "Appl_Mcu.h"
#endif /* (WDGM_SECOND_RESET_PATH == STD_ON) */


/* ***************************************************************************
 * Source version
 *****************************************************************************/
#define WDGM_SW_MAJOR_VERSION_SOURCE  2
#define WDGM_SW_MINOR_VERSION_SOURCE  0
#define WDGM_SW_PATCH_VERSION_SOURCE  3

/* Protection against incorrect include file version */
#if !(  (WDGM_SW_MAJOR_VERSION ==             \
         WDGM_SW_MAJOR_VERSION_SOURCE         \
        )                                     \
     && (WDGM_SW_MINOR_VERSION ==             \
         WDGM_SW_MINOR_VERSION_SOURCE         \
        )                                     \
     && (WDGM_SW_PATCH_VERSION ==             \
         WDGM_SW_PATCH_VERSION_SOURCE         \
        )                                     \
     )
  #error "Version mismatch! Incorrect version of WdgM.h"
#endif

/* ***************************************************************************
 * Global WdgM variables
 *****************************************************************************/
#define WDGM_GLOBAL_START_SEC_VAR_32BIT
#include "MemMap.h"
/* PRQA S 5087 2 */ /* PRQA S 3408 2 */
/* Pointer to loaded ROM configuration, NULL_PTR if WdgM is not initialized */
  P2CONST (WdgM_ConfigType, WDGM_CONST, WDGM_APPL_CONST) g_wdgm_cfg_ptr = NULL_PTR;
#define WDGM_GLOBAL_STOP_SEC_VAR_32BIT
#include "MemMap.h"   /* PRQA S 5087 */

#define WDGM_GLOBAL_START_SEC_VAR_32BIT
#include "MemMap.h"   /* PRQA S 5087 */
/* S-WdgM Timebase Tick Counter */
  STATIC VAR (WdgM_TimeBaseTickType, WDGM_VAR) g_wdgm_tick_count = 0;
#define WDGM_GLOBAL_STOP_SEC_VAR_32BIT
#include "MemMap.h"   /* PRQA S 5087 */

#define WDGM_GLOBAL_START_SEC_VAR_BOOLEAN
#include "MemMap.h"   /* PRQA S 5087 */
#if (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK)
  #if (WDGM_TICK_OVERRUN_CORRECTION == STD_ON)
  STATIC VAR (WdgM_BooleanParamType, WDGM_VAR) g_wdgm_tick_count_overrun = FALSE;
  #endif /* (WDGM_TICK_OVERRUN_CORRECTION == STD_ON) */
#endif /* (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK) */
#define WDGM_GLOBAL_STOP_SEC_VAR_BOOLEAN
#include "MemMap.h"   /* PRQA S 5087 */

/* ***************************************************************************
 * Internal definitions
 *****************************************************************************/
/* Magic constants for the SE deactivation/activation. Magic numbers are safer
   as simple TRUE/FALSE (0,1) for corruption detection */
#define WDGM_SE_STATE_REQUEST_NONE        0x43u
#define WDGM_SE_STATE_REQUEST_ACTIVATE    0x92u
#define WDGM_SE_STATE_REQUEST_DEACTIVATE  0xcau


/* ***************************************************************************
 * Internal functions
 *****************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */

STATIC FUNC (void, WDGM_CODE) Init_EntityMemoryL
    (P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr);

STATIC FUNC (void, WDGM_CODE) Init_EntityMemoryG
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
  #if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
    , CONST (WdgM_SupervisedEntityIdType, AUTOMATIC) entity_id
  #endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */
    );

STATIC FUNC (Std_ReturnType, WDGM_CODE) WatchdogTrigger (void);

STATIC FUNC (Std_ReturnType, WDGM_CODE) Init_CheckConfigChecksum (void);

STATIC FUNC (void, WDGM_CODE) BuildEntitiesStatus
    ( P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) local_status_failed_ptr
    , P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) local_status_expired_ptr
    );

#if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
STATIC FUNC (void, WDGM_CODE) WriteStateChangeRequest
    ( VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
    , VAR (WdgM_StateRequestType, AUTOMATIC) state_request
    );

STATIC FUNC (Std_ReturnType, WDGM_CODE) ReadStateChangeRequest
    ( VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
    , P2VAR (WdgM_StateRequestType, AUTOMATIC, WDGM_APPL_DATA) state_request_ptr
    );

STATIC FUNC (WdgM_LocalStatusType, WDGM_CODE) DeactivateEntity
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
    , VAR (WdgM_LocalStatusType, AUTOMATIC) local_status
    , VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
    );

STATIC FUNC (WdgM_LocalStatusType, WDGM_CODE) ActivateEntity
    ( VAR (WdgM_LocalStatusType, AUTOMATIC) local_status
    , VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
    );
#endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */

STATIC FUNC (WdgM_LocalStatusType, WDGM_CODE) BuildAliveLocalStatus
    (P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr);

STATIC FUNC (void , WDGM_CODE) CheckDeadlineHangup
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
    , P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) aperiodic_local_status_deadline
    , VAR (WdgM_CheckpointIdType, AUTOMATIC) remembered_checkpoint_id
    , VAR (WdgM_BooleanParamType, AUTOMATIC) local_activity_flag
    , VAR (WdgM_TimeBaseTickType, AUTOMATIC) remembered_checkpoint_time
    , VAR (WdgM_ViolationCntType, AUTOMATIC) deadline_violation_cnt
    , VAR (WdgM_TimeBaseTickType, AUTOMATIC) current_tick_count
    );

STATIC FUNC (void, WDGM_CODE) CheckDeadlineViolation
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
    , P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) aperiodic_local_status_deadline
    , VAR (WdgM_ViolationCntType, AUTOMATIC) deadline_violation_cnt
    );

STATIC FUNC (void, WDGM_CODE) CheckProgramFlowViolation
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
    , P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) aperiodic_local_status_programflow
    , VAR (WdgM_ViolationCntType, AUTOMATIC) program_flow_violation_cnt
    );

STATIC FUNC (Std_ReturnType, WDGM_CODE) ImmediateWatchdogReset (void);

#if (WDGM_TIMEBASE_SOURCE == WDGM_INTERNAL_SOFTWARE_TICK)
  #if ! defined(WDGM_UNIT_TESTS)
   STATIC FUNC (void, WDGM_CODE) WdgM_UpdateTickCount (void); /* PRQA S 1503 */
  #endif /* (WDGM_UNIT_TESTS) */
#endif /* (WDGM_TIMEBASE_SOURCE == WDGM_INTERNAL_SOFTWARE_TICK) */

/* ****************************************************************************
 * WdgM_Init
 *  This function initializes the Watchdog Manager.
 *    WDGM243: removed because inconsistency between AUTOSAR 3.1 and 4.0
 ******************************************************************************/
/* PRQA S 1503 2 */
FUNC (void, WDGM_CODE) WdgM_Init
    (P2CONST (WdgM_ConfigType, AUTOMATIC, WDGM_APPL_CONST) WdgMConfigPtr)
{
    VAR (Std_ReturnType, AUTOMATIC) ret;
    VAR (WdgM_WatchdogIdType, AUTOMATIC) wdg_dev;
    VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) nr_of_entities;
    VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) entity_id;
    P2CONST (WdgM_WatchdogDeviceType, AUTOMATIC, WDGM_APPL_CONST) device_ptr;
    P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr;
  #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
    VAR (WdgM_TransitionIdType, AUTOMATIC) g_tr;
  #endif /* (WDGM_GLOBAL_TRANSITIONS == STD_ON) */
  #if (WDGM_OFF_MODE_ENABLED == STD_OFF)
    VAR (WdgM_ModeType, AUTOMATIC) trg_mode;
  #endif /* (WDGM_OFF_MODE_ENABLED == STD_OFF) */

    /* ------------------------------ */
    /* Check the S-WdgM Configuration */
    /* ------------------------------ */

    /* Set the global config pointer */
    g_wdgm_cfg_ptr = WdgMConfigPtr;

    /* WDGM255: the configuration NULL_PTR pointer check */
    if (g_wdgm_cfg_ptr == NULL_PTR)
    {
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_Init
                             , WDGM_E_NULL_POINTER
                             );
        return; /* PRQA S 2006 */
    }

    /* Check the S-WdgM Configuration version */
    if (  (g_wdgm_cfg_ptr->WdgMConfigMajorVersion != WDGM_SW_MAJOR_VERSION_SOURCE)
            ||(g_wdgm_cfg_ptr->WdgMConfigMinorVersion != WDGM_SW_MINOR_VERSION_SOURCE)
            )
    {
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_Init
                             , WDGM_E_PARAM_CONFIG
                             );
        g_wdgm_cfg_ptr = NULL_PTR;
        return; /* PRQA S 2006 */
    }

    /* Check the S-WdgM Configuration Checksum */
    ret =  Init_CheckConfigChecksum();
    if (ret != E_OK)
    {
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_Init
                             , WDGM_E_PARAM_CONFIG
                             );
        g_wdgm_cfg_ptr = NULL_PTR;
        return; /* PRQA S 2006 */
    }

    /* Check the number of configured Entities */
    if ( g_wdgm_cfg_ptr->NrOfSupervisedEntities == 0)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_Init
                             , WDGM_E_PARAM_SEID
                             );
        g_wdgm_cfg_ptr = NULL_PTR;
        return;  /* PRQA S 2006 */
    }

    /* ---------------------------- */
    /* Check the Watchdog Device(s) */
    /* ---------------------------- */

    /* Check the Trigger Mode setup */
    if (g_wdgm_cfg_ptr->NrOfTriggerModes <= g_wdgm_cfg_ptr->WdgMInitialTriggerModeId)
    {
         WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_Init
                             , WDGM_E_PARAM_CONFIG
                             );
        g_wdgm_cfg_ptr = NULL_PTR;
        return; /* PRQA S 2006 */
    }


    /* Initialize the Trigger Mode */
    g_wdgm_cfg_ptr->DataGRef->TriggerModeId = g_wdgm_cfg_ptr->WdgMInitialTriggerModeId;
    g_wdgm_cfg_ptr->DataGRef->PreviousTriggerModeId = g_wdgm_cfg_ptr->WdgMInitialTriggerModeId;

    for (wdg_dev=0; wdg_dev < g_wdgm_cfg_ptr->NrOfWatchdogDevices; wdg_dev++)
    {
        device_ptr = &g_wdgm_cfg_ptr->WdgMWatchdogDeviceRef[wdg_dev];
        /* WDGM139: Set the WdgIf Initial mode */
        ret = WdgIf_SetMode( wdg_dev
                           , device_ptr->WdgMTriggerModeRef
                                [g_wdgm_cfg_ptr->DataGRef->TriggerModeId].WdgMWatchdogMode
                           );
        if (ret == E_NOT_OK)
        {
            g_wdgm_cfg_ptr->DataGRef->GlobalMonitoringStatus = WDGM_GLOBAL_STATUS_STOPPED;
            WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                 , WDGM_VENDOR_ID
                                 , API_ID_WdgM_Init
                                 , WDGM_E_WDGIF_MODE
                                 );
            g_wdgm_cfg_ptr = NULL_PTR;
            return; /* PRQA S 2006 */
        }

      #if (WDGM_OFF_MODE_ENABLED == STD_OFF)
        /* WDGM030: WDGM_OFF_MODE_ENABLED disabled?
           The S-WdgM can have different Trigger Modes for each Watchdog defined,
           see the WdgM_TriggerModeType structure.
           The S-WdgM checks the Trigger Mode only, not the WdgM general Mode.
           The WDGIF_OFF_MODE can be allowed/disallowed for the all Wdg drivers only.   */
        for (trg_mode=0; trg_mode < g_wdgm_cfg_ptr->NrOfTriggerModes; trg_mode++)
        {
            if ( device_ptr->WdgMTriggerModeRef[trg_mode].WdgMWatchdogMode
                == WDGIF_OFF_MODE
                )
            {
                WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                    , WDGM_VENDOR_ID
                                    , API_ID_WdgM_Init
                                    , WDGM_E_DISABLE_NOT_ALLOWED
                                    );
                g_wdgm_cfg_ptr = NULL_PTR;
                return; /* PRQA S 2006 */
            }
        }
      #endif /* (WDGM_OFF_MODE_ENABLED == STD_OFF) */
    }

    /* ----------------------------------------------------------------------------*/
    /* After basic configuration checks the memory/variable initialization follows */
    /* ----------------------------------------------------------------------------*/

    /* Initialize Entities */

    /* Get the Number Of Supervised Entities */
    nr_of_entities = g_wdgm_cfg_ptr->NrOfSupervisedEntities;

    /* For all configured Entities */
    for (entity_id = 0; entity_id < nr_of_entities; entity_id++)
    {
        current_entity_ptr  = &g_wdgm_cfg_ptr->WdgMSupervisedEntityRef[entity_id];

        /* Is at least one Checkpoint for each SE defined? */
        if (current_entity_ptr->NrOfCheckpoints == 0)
        {
            /* WDGM004: There is no Checkpoint for current Entity defined */
            WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                 , WDGM_VENDOR_ID
                                 , API_ID_WdgM_Init
                                 , WDGM_E_CPID
                                 );
            g_wdgm_cfg_ptr = NULL_PTR;
            return; /* PRQA S 2006 */
        }

        /* Initialize each Supervised Entity separately */
        Init_EntityMemoryL (current_entity_ptr);   /* Local Entity memory */
        Init_EntityMemoryG ( current_entity_ptr
                         #if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
                           , entity_id
                         #endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */
                           );   /* Global and Shared Entity memory */
    }

    /* Initialize the Timebase Tick Counter */
    WdgM_SetTickCount(WDGM_INITIAL_TICK_COUNT);
      #if (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK)
    #if (WDGM_TICK_OVERRUN_CORRECTION == STD_ON)
    g_wdgm_tick_count_overrun = FALSE;
    #endif /* (WDGM_TICK_OVERRUN_CORRECTION == STD_ON) */
      #endif /* (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK) */
    #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
    /* Initialize Global Transitions */
    for (g_tr = 0; g_tr < g_wdgm_cfg_ptr->NrOfGlobalTransitions; g_tr ++)
    {
        WdgM_WriteGlobalTransitionFlag (g_tr, FALSE);
    }
    /* WDGM273: Initialize the Global Activity Flag */
    WdgM_GlobalSuspendInterrupts();
    WdgM_WriteGlobalActivityFlag (FALSE);
    WdgM_GlobalRestoreInterrupts();
    #endif /* (WDGM_GLOBAL_TRANSITIONS == STD_ON) */

    /* Initialize the Timebase Tick Counter buffer */
    g_wdgm_cfg_ptr->DataGRef->PreviousTickCounter = 0;

    /* Set Global Status to OK */
    g_wdgm_cfg_ptr->DataGRef->GlobalMonitoringStatus = WDGM_GLOBAL_STATUS_OK;

    /* Set Internal failure flag to OK */
    g_wdgm_cfg_ptr->DataGSRef->InternalFailureFlag = WDGM_INTERNAL_CP_TEST_OK;

    /* Main Function has not been started yet. */
    g_wdgm_cfg_ptr->DataGRef->WdgMMainStarted = FALSE;

 }   /* PRQA S 2006  */

/* *****************************************************************************
 * Init_EntityMemoryL()
 *  Function initialize Local memory of an Entity.
 ******************************************************************************/
STATIC FUNC (void, WDGM_CODE) Init_EntityMemoryL
    (P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr)
{
    VAR (WdgM_CheckpointIdType, AUTOMATIC) cp_id;

    /* WDGM271,... */
    current_entity_ptr->EntityStatusLRef->LocalActivityFlag = FALSE;

    /* Program Flow initialization */
    current_entity_ptr->EntityStatusLRef->ProgramFlowViolationCnt      = 0;

    /* Deadline initialization */
    current_entity_ptr->EntityStatusLRef->DeadlineViolationCnt         = 0;

    /* Initialize the Remembered Checkpoint time */
    current_entity_ptr->EntityStatusLRef->RememberedCheckpointTime     = 0;

    /* Initialize the Remembered Checkpoint ID */
    current_entity_ptr->EntityStatusLRef->RememberedCheckpointId = WDGM_INVALID_CP_ID;

     /* Initialize the all Alive counters */
    for (cp_id = 0; cp_id < current_entity_ptr->NrOfCheckpoints; cp_id++)
    {
        if (current_entity_ptr->WdgMCheckpointRef[cp_id].WdgMAliveLRef != NULL_PTR)
        {
             current_entity_ptr->WdgMCheckpointRef[cp_id].WdgMAliveLRef->AliveCounter = 0;
        }
    }
}

/* *****************************************************************************
 * Init_EntityMemoryG()
 *  Function initialize Global and Global Shared memory of an Entity.
 ******************************************************************************/
STATIC FUNC (void, WDGM_CODE) Init_EntityMemoryG
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
  #if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
    , CONST (WdgM_SupervisedEntityIdType, AUTOMATIC) entity_id
  #endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */
    )
{
    VAR (WdgM_CheckpointIdType, AUTOMATIC) cp_id;

    /* WDGM268,9 */
    if (current_entity_ptr->WdgMInitialStatus ==  WDGM_LOCAL_STATUS_OK)
    {
        current_entity_ptr->EntityStatusGRef->LocalMonitoringStatus
            = WDGM_LOCAL_STATUS_OK;
    }
    else
    {
        current_entity_ptr->EntityStatusGRef->LocalMonitoringStatus
            = WDGM_LOCAL_STATUS_DEACTIVATED;
    }
    current_entity_ptr->EntityStatusGRef->FailedSupervisionRefCycles   = 0;

    /* Program Flow initialization */
    current_entity_ptr->EntityStatusGRef->FailedProgramFlowRefCycles   = 0;
    current_entity_ptr->EntityStatusGRef->FailedProgramFlowCycCounter  = 0;
    current_entity_ptr->EntityStatusGRef->ProgramFlowViolationCnt      = 0;

    /* Deadline initialization */
    current_entity_ptr->EntityStatusGRef->FailedDeadlineRefCycles      = 0;
    current_entity_ptr->EntityStatusGRef->FailedDeadlineCycCounter     = 0;
    current_entity_ptr->EntityStatusGRef->DeadlineViolationCnt         = 0;

    /* Initialize the all Alive counters */
    for (cp_id = 0; cp_id < current_entity_ptr->NrOfCheckpoints; cp_id++)
    {
        if (current_entity_ptr->WdgMCheckpointRef[cp_id].WdgMAliveGRef != NULL_PTR)
        {
             current_entity_ptr->WdgMCheckpointRef[cp_id].
                WdgMAliveGRef->SupervisionAliveCounter = 0;
             current_entity_ptr->WdgMCheckpointRef[cp_id].
                WdgMAliveGRef->AliveCounterStamp = 0;
        }
    }
  #if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
    /* Initialize the SE deactivation / activation request array */
    WriteStateChangeRequest (entity_id, WDGM_SE_STATE_REQUEST_NONE);
  #endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */
}


/* *****************************************************************************
 * Init_CheckConfigChecksum()
 *  Function calculates a partial checksum of the S-WdgM configuration structure.
 *  The intention is to see whether we use the S-WdgM config and the config is not
 *  accidently overwritten by foreign download and it is palced on a right position.
 *  We do not check each config bit this is a job for Downloader and Startup checker.
 ******************************************************************************/
STATIC FUNC (Std_ReturnType, WDGM_CODE) Init_CheckConfigChecksum (void)
{
    VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) nr_of_entities;
    VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) entity_id;
    VAR (Std_ReturnType, AUTOMATIC) res;
    VAR (uint32, AUTOMATIC) checksum;
    VAR (WdgM_CheckpointIdType, AUTOMATIC) cp_id;
    VAR (WdgM_CheckpointIdType, AUTOMATIC) cp_idx;
    P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr;

    checksum = 0;
    cp_idx = 0;
    nr_of_entities = g_wdgm_cfg_ptr->NrOfSupervisedEntities;

    /* Go through all Entities and Checkpoints and build a checksum
       from Entity array and from Checkpoint array */
    for (entity_id = 0; entity_id < nr_of_entities; entity_id++)
    {
        /* Add the Entity elements to the checksum, each even element multiply by two */
        current_entity_ptr  = &g_wdgm_cfg_ptr->WdgMSupervisedEntityRef[entity_id];
        if ((entity_id & 0x1u) != 0u)
        {
            /* Each odd add to the checksum  */
            checksum += (uint32) current_entity_ptr->WdgMSupervisedEntityId;
        }
        else
        {
            /* Beginning with element 0, take each even element */
            checksum += (uint32) ((current_entity_ptr->WdgMSupervisedEntityId) << 1);
        }

        /* Add all checkpoint elements as we have only one array for all checkpoints */
        for (cp_id = 0; cp_id < current_entity_ptr->NrOfCheckpoints; cp_id++)
        {
            /* Add the checkpoint elemnts to the checksum, each even element multiply by two */
            if ((cp_idx & 0x1u) != 0u)
            {
                checksum +=
                   (uint32) current_entity_ptr->WdgMCheckpointRef[cp_id].WdgMCheckpointId;
            }
            else
            {
               checksum += (uint32)
                  ((current_entity_ptr->WdgMCheckpointRef[cp_id].WdgMCheckpointId) << 1);
            }
            /* Next checkpoint element */
            cp_idx++;
        }
    }

    /* Add defined elements from the main config structure. Beginning
       with the first element where each second element is multiplierd by two.
       (The same procedure in the configuration generator!) */
    checksum += (uint32) ((g_wdgm_cfg_ptr->WdgMConfigMajorVersion) << 1u);
    checksum += (uint32) g_wdgm_cfg_ptr->WdgMConfigMinorVersion;
    checksum += (uint32) ((g_wdgm_cfg_ptr->WdgMConfigId) << 1u);

    if( checksum != g_wdgm_cfg_ptr->WdgMConfigChecksum)
    {
        res = E_NOT_OK;
    }
    else
    {
        res = E_OK;
    }
    return (res);
}


/* *****************************************************************************
 * WdgM_GetLocalStatus()
 *  Returns a status of one supervised entity.
 ******************************************************************************/
/* PRQA S 1503  3 */
FUNC (Std_ReturnType, WDGM_CODE) WdgM_GetLocalStatus
    ( VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
    , P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) EntityStatus
    )
{
    VAR (Std_ReturnType, AUTOMATIC) res;

    /* WDGM173: Was the Watchdog Manager initialized? */
    if (g_wdgm_cfg_ptr == NULL_PTR)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_GetLocalStatus
                             , WDGM_E_NO_INIT
                             );
        res = E_NOT_OK;
    }
    else if (g_wdgm_cfg_ptr->NrOfSupervisedEntities <= SEID)
    {
        /* WDGM004 */
        /* WDGM172: Is the current SE ID inside of the configured border? */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_GetLocalStatus
                             , WDGM_E_PARAM_SEID
                             );
        res = E_NOT_OK;
    }
    else if (EntityStatus == NULL_PTR)
    {
        /* WDGM257: NULL_PTR pointer to out parameter */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_GetLocalStatus
                             , WDGM_E_NULL_POINTER
                             );
        res = E_NOT_OK;
    }
    else
    {
        *EntityStatus =
           g_wdgm_cfg_ptr->WdgMSupervisedEntityRef[SEID].
              EntityStatusGRef->LocalMonitoringStatus;
        res = E_OK;
    }

    return (res);
}

/* *****************************************************************************
 *  WdgM_GetGlobalStatus()
 *   Returns a status of all supervised entities.
 ******************************************************************************/
/* PRQA S 1503 2 */
FUNC (Std_ReturnType, WDGM_CODE) WdgM_GetGlobalStatus
    (P2VAR (WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) Status)
{
    VAR (Std_ReturnType, AUTOMATIC) res;

    /* WDGM176 Was the Watchdog Manager initialized? */
    if (g_wdgm_cfg_ptr == NULL_PTR)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_GetLocalStatus
                             , WDGM_E_NO_INIT
                             );
        res = E_NOT_OK;
    }
    else if (Status == NULL_PTR)     /* WDGM258: Null pointer to out parameter */
    {
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_GetGlobalStatus
                             , WDGM_E_NULL_POINTER
                             );
        res = E_NOT_OK;
    }
    else
    {
        *Status = g_wdgm_cfg_ptr->DataGRef->GlobalMonitoringStatus;
        res = E_OK;
    }

    return (res);
}


/* *****************************************************************************
 *  WdgM_GetMode()
 *    This function returns the current mode of the Watchdog Manager.
 *    In S-WdgM this value represets the trigger mode only. For compatibility
 *    with AUTOSAR the Mode type is used.
 ******************************************************************************/
/* PRQA S 1503 2 */
FUNC (Std_ReturnType, WDGM_CODE) WdgM_GetMode
    (P2VAR (WdgM_ModeType, AUTOMATIC, WDGM_APPL_DATA) Mode)
{
    VAR (Std_ReturnType, AUTOMATIC) res;

    /* WDGM253: Was the Watchdog Manager initialized? */
    if (g_wdgm_cfg_ptr == NULL_PTR)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_GetMode
                             , WDGM_E_NO_INIT
                             );
        res = E_NOT_OK;
    }
    else if (Mode == NULL_PTR)
    {
        /* WDGM258: Null pointer to out parameter  */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_GetMode
                             , WDGM_E_NULL_POINTER
                             );
        res = E_NOT_OK;
    }
    else
    {
        *Mode = (WdgM_ModeType) g_wdgm_cfg_ptr->DataGRef->TriggerModeId;
        res = E_OK;
    }

    return (res);
}

/* *****************************************************************************
 *  WdgM_SetMode()
 *    This function set the trigger mode of the Watchdog Manager.
 *    The function is only partly AUTOSAR 4.0r1 compatible. It switches the
 *    Watchdog timings only. The entities are neither deactivated nor activated.
 ******************************************************************************/
#if (WDGM_AUTOSAR_3_1_X_COMPATIBILITY != STD_ON)
/* PRQA S 1503 2 */
FUNC (Std_ReturnType, WDGM_CODE) WdgM_SetMode
    (VAR (WdgM_ModeType, AUTOMATIC) Mode, VAR (uint16, AUTOMATIC) CallerID)
#else
/* PRQA S 1503 2 */
FUNC (Std_ReturnType, WDGM_CODE) WdgM_SetMode
    (VAR (WdgM_ModeType, AUTOMATIC) Mode)
#endif /* (WDGM_AUTOSAR_3_1_X_COMPATIBILITY != STD_ON) */
{
    VAR (Std_ReturnType, AUTOMATIC) res;
  #if (WDGM_DEFENSIVE_BEHAVIOR == STD_ON)
    VAR (WdgM_CallerIdType, AUTOMATIC) i;
  #endif /* (WDGM_DEFENSIVE_BEHAVIOR == STD_ON) */
  #if (WDGM_AUTOSAR_3_1_X_COMPATIBILITY == STD_ON)
    VAR (uint16, AUTOMATIC) CallerID = 0;
  #endif /* (WDGM_AUTOSAR_3_1_X_COMPATIBILITY == STD_ON) */

    res = E_NOT_OK;

    /* WDGM021: Was the Watchdog Manager initialized? */
    if (g_wdgm_cfg_ptr == NULL_PTR)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_SetMode
                             , WDGM_E_NO_INIT
                             );
        return (res); /* PRQA S 2006 */
    }

    if ( g_wdgm_cfg_ptr->NrOfTriggerModes <= Mode )
    {
        /* WDGM258: Null pointer to out parameter  */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_SetMode
                             , WDGM_E_PARAM_MODE
                             );
        return (res); /* PRQA S 2006 */
    }

  #if (WDGM_DEFENSIVE_BEHAVIOR == STD_ON)
    /* WDGM245: Check the whether the caller is in the 'allowed' caller list */
    for (i = 0; i < g_wdgm_cfg_ptr->NrOfAllowedCallers; i++)
    {
        if (g_wdgm_cfg_ptr->WdgMCallersRef[i].WdgMAllowedCaller == CallerID)
        {
            res = E_OK;
            break;
        }
    }

    if ( res == E_NOT_OK )
    {
        /* WDGM245: Caller is not in the 'allowed' list */
        WDGM_DEM_REPORTERROR(WDGM_E_IMPROPER_CALLER, DEM_EVENT_STATUS_FAILED);
        return (res); /* PRQA S 2006 */
    }
  #endif /* (WDGM_DEFENSIVE_BEHAVIOR == STD_ON) */


    /* WDGM145 */
    if  (  (g_wdgm_cfg_ptr->DataGRef->GlobalMonitoringStatus == WDGM_GLOBAL_STATUS_OK)
        || (g_wdgm_cfg_ptr->DataGRef->GlobalMonitoringStatus == WDGM_GLOBAL_STATUS_FAILED)
        )
    {
        /* The WdgM 'Mode' is here casted to the only supported S-WdgM 'TriggerMode'*/
        g_wdgm_cfg_ptr->DataGRef->TriggerModeId = (WdgM_TriggerModeIdType) Mode;
        res = E_OK;
    }
    else
    {
        res = E_NOT_OK;
    }


    /* Remark for WDGM031: check for WDGM_OFF_MODE_ENABLED is done in WdgM_Init() */

    /* WDGM186: The new Watchdog Mode (SLOW, FAST, OFF) shall be set synchronously
       in the MainFunction inside of the allowed Watchdog time window */

    return (res);
}   /* PRQA S 2006 */


#if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
/* *****************************************************************************
 *  WdgM_ActivateSupervisionEntity()
 *    This function mark a SE for activation. The activation itself
 *    happens in the WdgM_MainFunction() after the status of each SE is calculated.
 ******************************************************************************/
/* PRQA S 1503 2 */
FUNC (Std_ReturnType, WDGM_CODE) WdgM_ActivateSupervisionEntity
    (VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID)
{
    VAR (Std_ReturnType, AUTOMATIC) res;

    res = E_NOT_OK;

    /* Was the Watchdog Manager initialized? */
    if (g_wdgm_cfg_ptr == NULL_PTR)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_ActivateSupervisionEntity
                             , WDGM_E_NO_INIT
                             );
    }
    /* WDGM278: Is the current SE ID inside of the configured border? */
    else if (g_wdgm_cfg_ptr->NrOfSupervisedEntities <= SEID)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_ActivateSupervisionEntity
                             , WDGM_E_PARAM_SEID
                             );
    }
    else
    {
        /* The SE Deactivation/Activation shall be explicitly enabled in the configuration */
        if (g_wdgm_cfg_ptr->WdgMSupervisedEntityRef[SEID].WdgMEnableEntityDeactivation == STD_ON)
        {
            /* Initiate Entity activation. SEID is in range [0...N] */
            WriteStateChangeRequest (SEID, WDGM_SE_STATE_REQUEST_ACTIVATE);
            res = E_OK;
        }
    }

    return(res);
}
#endif /* WDGM_ENTITY_DEACTIVATION_ENABLED */


#if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
/* *****************************************************************************
 *  WdgM_DeactivateSupervisionEntity()
 *    This function mark a SE for deactivation. The deactivation itself
 *    happens in the WdgM_MainFunction() before status of each SE is calculated.
 ******************************************************************************/
/* PRQA S 1503 2 */
FUNC (Std_ReturnType, WDGM_CODE) WdgM_DeactivateSupervisionEntity
    (VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID)
{
    VAR (Std_ReturnType, AUTOMATIC) res;

    res = E_NOT_OK;

    /* Was the Watchdog Manager initialized? */
    if (g_wdgm_cfg_ptr == NULL_PTR)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_DeactivateSupervisionEntity
                             , WDGM_E_NO_INIT
                             );
    }
    /* WDGM278: Is the current SE ID inside of the configured border? */
    else if (g_wdgm_cfg_ptr->NrOfSupervisedEntities <= SEID)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_DeactivateSupervisionEntity
                             , WDGM_E_PARAM_SEID
                             );
    }
    else
    {
        /* The SE Deactivation/Activation shall be explicitly enabled in the configuration */
        if (g_wdgm_cfg_ptr->WdgMSupervisedEntityRef[SEID].WdgMEnableEntityDeactivation == STD_ON)
        {
            /* Initiate Entity deactivation. SEID is in range [0...N] */
            WriteStateChangeRequest (SEID, WDGM_SE_STATE_REQUEST_DEACTIVATE);
            res = E_OK;
        }
    }

    return(res);
}
#endif /* WDGM_ENTITY_DEACTIVATION_ENABLED */


/* *****************************************************************************
 * WdgM_MainFunction()
 *  This function is running inside of a separate cyclic task
 ******************************************************************************/
FUNC (void, WDGM_CODE) WdgM_MainFunction (void)  /* PRQA S 1503  */
{
    VAR (WdgM_LocalStatusType, AUTOMATIC) local_status_failed;
    VAR (WdgM_LocalStatusType, AUTOMATIC) local_status_expired;
    VAR (WdgM_GlobalStatusType, AUTOMATIC) global_status;
  #if (WDGM_MULTIPLE_TRIGGER_MODES == STD_ON)
    VAR (Std_ReturnType, AUTOMATIC) ret;
  #endif /* (WDGM_MULTIPLE_TRIGGER_MODES == STD_ON) */
  #if ((WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK) || (WDGM_MULTIPLE_TRIGGER_MODES == STD_ON))
    P2CONST (WdgM_WatchdogDeviceType, AUTOMATIC, WDGM_APPL_CONST) device_ptr;
    VAR (WdgM_WatchdogIdType, AUTOMATIC) wdg_dev;
  #endif /* ((WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK)
             || (WDGM_MULTIPLE_TRIGGER_MODES == STD_ON)
            ) */
  #if (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK)
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) tick_count_diff;
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) current_tick_count;
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) previous_tick_count;
    VAR (WdgM_BooleanParamType, AUTOMATIC) positive_tick;
   #if (WDGM_TICK_OVERRUN_CORRECTION == STD_ON)
    VAR (WdgM_BooleanParamType, AUTOMATIC) tick_count_overrun;
   #endif /* (WDGM_TICK_OVERRUN_CORRECTION == STD_ON) */
  #endif /* (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK) */

    /* WDGM039: Check whether the Watchdog Manager was initialized. */
  #if (WDGM_DEFENSIVE_BEHAVIOR == STD_ON)
    if (g_wdgm_cfg_ptr == NULL_PTR)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_MainFunction
                             , WDGM_E_NO_INIT
                             );
        return;  /* PRQA S 2006 */
    }
  #endif /* WDGM_DEFENSIVE_BEHAVIOR */

    /* Check the Checkpoint's catastrofic failures like GS memory corruption */
    if ( g_wdgm_cfg_ptr->DataGSRef->InternalFailureFlag != WDGM_INTERNAL_CP_TEST_OK )
    {
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_MainFunction
                             , WDGM_E_MEMORY_FAILURE      /* GS memory failure */
                             );
        (void) ImmediateWatchdogReset();
        return;  /* PRQA S 2006 */
    }

  #if (WDGM_TIMEBASE_SOURCE == WDGM_INTERNAL_SOFTWARE_TICK)
    /* Increment the Timebase Tick Counter by one */
    WdgM_UpdateTickCount();
  #endif /* (WDGM_TIMEBASE_SOURCE == WDGM_INTERNAL_SOFTWARE_TICK) */

  #if (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK)
    /* When external Tick counter for deadline monitoring is used, then
     *  following counter checks are here done:
     *  1.stuck-in   2.negative jump   3. number of ticks in supervised cycle
     *
     *  The internal Tick increment we do not check, it is obvious
     *  that the counter is in the WdgM_UpdateTickCount above incremented properly.
     */

    /* Load the for check relevant input parameters */
  #if (WDGM_TICK_OVERRUN_CORRECTION == STD_ON)
    /* For case when overrun happens before, and next tick update happens
       just after the WdgM_GetTickCount below */
    WdgM_GlobalSuspendInterrupts();
  #endif /* (WDGM_TICK_OVERRUN_CORRECTION == STD_ON) */

    /* Load the current Tick counter value */
    current_tick_count = WdgM_GetTickCount();

  #if (WDGM_TICK_OVERRUN_CORRECTION == STD_ON)
    tick_count_overrun = g_wdgm_tick_count_overrun;
    WdgM_GlobalRestoreInterrupts();
  #endif /* (WDGM_TICK_OVERRUN_CORRECTION == STD_ON) */
    previous_tick_count = g_wdgm_cfg_ptr->DataGRef->PreviousTickCounter;
    g_wdgm_cfg_ptr->DataGRef->PreviousTickCounter = current_tick_count;

    positive_tick = FALSE;
    tick_count_diff = 0;

    /* Check Tick counter for 'stuck-in' and 'negative jump' in first cycle */
    if (g_wdgm_cfg_ptr->DataGRef->WdgMMainStarted == FALSE)
    {
        /* The first supervision cycle need to be checked separatelly:
           First time run, previous_tick_count is always ZERO! */
      #if (WDGM_TICK_OVERRUN_CORRECTION == STD_ON)
        if (tick_count_overrun == TRUE)
        {
            if (previous_tick_count <= current_tick_count)
            {
                positive_tick = TRUE;
            }
            /* Reset the Timebase overrun flag */
            g_wdgm_tick_count_overrun = FALSE;
        }
        else
      #endif /* (WDGM_TICK_OVERRUN_CORRECTION == STD_ON) */
        {
            if (previous_tick_count < current_tick_count)
            {
                positive_tick = TRUE;
            }
        }

        /* When the 'stuck-in' or 'negative jump' failure found call at this place Det module */
        if (positive_tick == FALSE)
        {
            WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                , WDGM_VENDOR_ID
                                , API_ID_WdgM_MainFunction
                                , WDGM_E_TIMEBASE
                                );
            return;  /* PRQA S 2006 */
        }
    }
    else
    {
        /* Check Tick counter for 'stuck-in' and 'negative jump' in all other cycles */
      #if (WDGM_TICK_OVERRUN_CORRECTION == STD_ON)
        if (tick_count_overrun == TRUE)
        {
            if (previous_tick_count > current_tick_count)
            {
                positive_tick = TRUE;
                /* diff = max_value - previous_tick_count + current_tick_count + 1 */
                tick_count_diff = (~previous_tick_count) + current_tick_count + 1;
            }
            /* Reset the Timebase overrun flag */
            g_wdgm_tick_count_overrun = FALSE;
        }
        else
      #endif /* (WDGM_TICK_OVERRUN_CORRECTION == STD_ON) */
        {
            if (previous_tick_count < current_tick_count)
            {
                positive_tick = TRUE;
                tick_count_diff = current_tick_count - previous_tick_count;
            }
        }

        /* When the 'stuck-in' or 'negative jump' failure found call at this place Det module */
        if (positive_tick == FALSE)
        {
            WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                , WDGM_VENDOR_ID
                                , API_ID_WdgM_MainFunction
                                , WDGM_E_TIMEBASE
                                );
            return;  /* PRQA S 2006 */
        }

        /* Check the number of counted Timebase Ticks inside the Supervision Cycle
           For correct triggering in a trigger_window following applies:
           WdgMTriggerWindowStartTicks <= trigger_window <  WdgMTriggerTimeoutTicks */
        for (wdg_dev=0; wdg_dev < g_wdgm_cfg_ptr->NrOfWatchdogDevices; wdg_dev++)
        {
             device_ptr = &g_wdgm_cfg_ptr->WdgMWatchdogDeviceRef[wdg_dev];
            if ( (device_ptr->WdgMTriggerModeRef[g_wdgm_cfg_ptr->DataGRef->TriggerModeId].
                    WdgMTriggerWindowStartTicks > tick_count_diff)
                 ||
                 (device_ptr->WdgMTriggerModeRef[g_wdgm_cfg_ptr->DataGRef->TriggerModeId].
                    WdgMTriggerTimeoutTicks <= tick_count_diff)
               )
            {
                WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                     , WDGM_VENDOR_ID
                                     , API_ID_WdgM_MainFunction
                                     , WDGM_E_TIMEBASE
                                     );
                return;  /* PRQA S 2006 */
            }
        }
    }

    /* Set Main Function has already been started. */
  #endif /* (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK) */

  #if (WDGM_MULTIPLE_TRIGGER_MODES == STD_ON)
    /* When a new Trigger Mode is requested then switch the WatchdogMode (OFF, SLOW, FAST) too.
       The Wdg driver excepts the switch to a new WatchdogMode is inside of the trigger window  */
    if (  g_wdgm_cfg_ptr->DataGRef->PreviousTriggerModeId
       != g_wdgm_cfg_ptr->DataGRef->TriggerModeId
       )
    {
        g_wdgm_cfg_ptr->DataGRef->PreviousTriggerModeId = g_wdgm_cfg_ptr->DataGRef->TriggerModeId;

        for (wdg_dev=0; wdg_dev < g_wdgm_cfg_ptr->NrOfWatchdogDevices; wdg_dev++)
        {
            device_ptr = &g_wdgm_cfg_ptr->WdgMWatchdogDeviceRef[wdg_dev];
            /* Set the new Trigger Mode */
            ret = WdgIf_SetMode
                            (
                              wdg_dev
                            , device_ptr->WdgMTriggerModeRef
                              [g_wdgm_cfg_ptr->DataGRef->TriggerModeId].WdgMWatchdogMode
                            );
            if (ret == E_NOT_OK)
            {
                /* WDGM139: Set GLOBAL_STATUS_STOPPED */
                g_wdgm_cfg_ptr->DataGRef->GlobalMonitoringStatus = WDGM_GLOBAL_STATUS_STOPPED;
                WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                    , WDGM_VENDOR_ID
                                    , API_ID_WdgM_MainFunction
                                    , WDGM_E_WDGIF_MODE
                                    );
               /* Run through to the GLOBAL STOPPED state */
            }
        }
    }
  #endif  /* (WDGM_MULTIPLE_TRIGGER_MODES == STD_ON) */

    /* ----------------------------------------------------------------------------
     * After this point we assume that the configuration and runtime checks are OK!
     * ---------------------------------------------------------------------------- */

    /* Global State of the state machine */
    global_status  = g_wdgm_cfg_ptr->DataGRef->GlobalMonitoringStatus;

    switch (global_status)
    {
        /* -------------------------------------------------------------------*/
        case WDGM_GLOBAL_STATUS_OK:
        case WDGM_GLOBAL_STATUS_FAILED:
        {
            /* Is at least one local status failed or expired? */
            BuildEntitiesStatus(&local_status_failed, &local_status_expired);

            if (local_status_expired == WDGM_LOCAL_STATUS_EXPIRED)
            {
                /* WDGM215 */
                if (g_wdgm_cfg_ptr->WdgMExpiredSupervisionCycleTol > 0)
                {
                    /* Initialise 'ExpiredCycleCounter' */
                    g_wdgm_cfg_ptr->DataGRef->ExpiredCycleCounter = 1u;
                    global_status = WDGM_GLOBAL_STATUS_EXPIRED;
                }
                else
                {
                    global_status = WDGM_GLOBAL_STATUS_STOPPED;   /* WDGM216 */
                }
            }
            /* WDGM076 */
            else if (local_status_failed == WDGM_LOCAL_STATUS_FAILED)
            {
                /* Goto FAILED or stay there */
                global_status = WDGM_GLOBAL_STATUS_FAILED;
            }
            else
            {
                /* Stay in OK or perform recovery */
                global_status = WDGM_GLOBAL_STATUS_OK;
            }
        }
        break;

        /* -------------------------------------------------------------------*/
        case WDGM_GLOBAL_STATUS_EXPIRED:
        {
            /* Is at least one local status failed or expired? */
            BuildEntitiesStatus(&local_status_failed, &local_status_expired);

            /* WDGM219 */
            if (local_status_expired == WDGM_LOCAL_STATUS_EXPIRED)
            {
                if (g_wdgm_cfg_ptr->DataGRef->ExpiredCycleCounter
                    < g_wdgm_cfg_ptr->WdgMExpiredSupervisionCycleTol
                   )
                {
                    g_wdgm_cfg_ptr->DataGRef->ExpiredCycleCounter++;
                    global_status = WDGM_GLOBAL_STATUS_EXPIRED;
                }
                else
                {
                    global_status = WDGM_GLOBAL_STATUS_STOPPED;   /* WDGM220 */
                }
            }
            else
            {
                /* Stay in the EXPIRED state, there is no way back */
                /* MISRA rule 14.10 */
            }
        }
        break;

        /* -------------------------------------------------------------------*/
        case WDGM_GLOBAL_STATUS_STOPPED:
        {
            /* WDGM122: End state, WD reset will follow */
          #if (WDGM_DEM_SUPERVISION_REPORT == STD_ON)
            /*  WDGM338, WDGM129: Error report to DEM */
            WDGM_DEM_REPORTERROR(WDGM_E_MONITORING, DEM_EVENT_STATUS_FAILED);
          #endif /* (WDGM_DEM_SUPERVISION_REPORT == STD_ON) */
        }
        break;

        /* -------------------------------------------------------------------*/
        case WDGM_GLOBAL_STATUS_DEACTIVATED:
        /* WDGM292: The S-WdgM shall not trigger the WD and shall not call
                    the WdgIf_SetTriggerCondition */
        break;

        /* -------------------------------------------------------------------*/
        default:  /* PRQA S 2018 */
        {
            /* Wrong state */
            WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                 , WDGM_VENDOR_ID
                                 , API_ID_WdgM_MainFunction
                                 , WDGM_E_PARAM_STATE
                                 );
            /* If this statement is reached then another process has
               corrupted/overwritten the status - perform an immediate
               reset! */
            (void)ImmediateWatchdogReset();
        }
        break;
    }

  #if (WDGM_STATE_CHANGE_NOTIFICATION == STD_ON)
    if (g_wdgm_cfg_ptr->WdgM_GlobalStateChangeCbk != NULL_PTR)
    {
        /* Global status changed? */
        if (g_wdgm_cfg_ptr->DataGRef->GlobalMonitoringStatus != global_status)
        {
          /* WDGM134: Do not provide notification in STATUS_STOPPED */
          #if (WDGM_IMMEDIATE_RESET == STD_ON)
            if (global_status != WDGM_GLOBAL_STATUS_STOPPED)
          #endif /* (WDGM_IMMEDIATE_RESET == STD_ON) */
            {
                (void)g_wdgm_cfg_ptr->WdgM_GlobalStateChangeCbk(global_status);
            }
        }
    }
  #endif /* WDGM_STATE_CHANGE_NOTIFICATION == STD_ON */

    /* Update the global state variable */
    g_wdgm_cfg_ptr->DataGRef->GlobalMonitoringStatus = global_status;

    /* WDGM119, 120, 121 */
    if (  (global_status == WDGM_GLOBAL_STATUS_OK)
       || (global_status == WDGM_GLOBAL_STATUS_FAILED)
       || (global_status == WDGM_GLOBAL_STATUS_EXPIRED)
       )
    {
        (void)WatchdogTrigger();
    }
    else
    {
        if (global_status != WDGM_GLOBAL_STATUS_DEACTIVATED)
        {
            /* WDGM122: global_status == WDGM_GLOBAL_STATUS_STOPPED */
          #if (WDGM_IMMEDIATE_RESET == STD_ON)
            /* WDGM133: Perform immediate reset, do not wait for WD timeout
               In contrast to AUTOSAR 4.0 for safety reasons the S-WdgM default reset
               path is the watchdog path. The IMMEDIATE_RESET parameter invokes immediate
               reset through watchdog and not via Mcu_Reset function as defined in AUTOSAR */
            (void)ImmediateWatchdogReset();
          #endif /* (WDGM_IMMEDIATE_RESET == STD_ON) */
        }
    }
    g_wdgm_cfg_ptr->DataGRef->WdgMMainStarted = TRUE;
}   /* PRQA S 2006  */



/* *****************************************************************************
 * WatchdogTrigger()
 *   The local function triggers the hardware Watchdogs.
 ******************************************************************************/
STATIC FUNC (Std_ReturnType, WDGM_CODE) WatchdogTrigger (void)
{
    P2CONST (WdgM_WatchdogDeviceType, AUTOMATIC, WDGM_APPL_CONST) device_ptr;
    VAR (Std_ReturnType, AUTOMATIC) res;
    VAR (WdgM_TriggerModeIdType, AUTOMATIC) trigger_mode;
    VAR (uint8, AUTOMATIC) i;
    VAR (WdgM_BooleanParamType, AUTOMATIC) failed;

    res = E_NOT_OK;
    failed = FALSE;

    /* Get the current Trigger Mode */
    trigger_mode = g_wdgm_cfg_ptr->DataGRef->TriggerModeId;

    /* WDGM002: trigger all Watchdogs */
    for (i=0; i < g_wdgm_cfg_ptr->NrOfWatchdogDevices; i++)
    {
        device_ptr = &g_wdgm_cfg_ptr->WdgMWatchdogDeviceRef[i];
        /* WDGM119: Do not trigger watchdogs configured as WDGIF_OFF_MODE  */
      #if (WDGM_OFF_MODE_ENABLED == STD_ON)
        if (device_ptr->WdgMTriggerModeRef[trigger_mode].WdgMWatchdogMode != WDGIF_OFF_MODE)
      #endif /* (WDGM_OFF_MODE_ENABLED == STD_ON) */
        {
            res = WdgIf_SetTriggerWindow
                    ( i
                    , device_ptr->WdgMTriggerModeRef[trigger_mode].WdgMTriggerWindowStart
                    , device_ptr->WdgMTriggerModeRef[trigger_mode].WdgMTriggerTimeout
                    );
            if (res == E_NOT_OK)
            {
                failed = TRUE;
                WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                     , WDGM_VENDOR_ID
                                     , API_ID_WdgM_MainFunction
                                     , WDGM_E_WDGIF_MODE
                                     );
              #if (WDGM_SECOND_RESET_PATH == STD_ON)
                /* Immediate reset through MCU internal functionality,
                   this function usualy doesn't return */
                (void) Appl_Mcu_PerformReset();
              #endif /* (WDGM_SECOND_RESET_PATH == STD_ON) */
            }
        }
    }
    if (failed == TRUE)
    {
       res = E_NOT_OK;
    }
    return (res);
}

/* *****************************************************************************
 * ImmediateWatchdogReset()
 *   The local function performs immediate reset. Primary the Watchdog itself
 *   is used for reseting. When the primary reset path returns an error and
 *   when the second reset path is enabled then the second path is used too.
 ******************************************************************************/
STATIC FUNC (Std_ReturnType, WDGM_CODE) ImmediateWatchdogReset (void)
{
  #if (WDGM_OFF_MODE_ENABLED == STD_ON)
    P2CONST (WdgM_WatchdogDeviceType, AUTOMATIC, WDGM_APPL_CONST) device_ptr;
    VAR (WdgM_TriggerModeIdType, AUTOMATIC) trigger_mode;
  #endif /* (WDGM_OFF_MODE_ENABLED == STD_ON) */
    VAR (Std_ReturnType, AUTOMATIC) res;
    VAR (uint8, AUTOMATIC) i;
    VAR (WdgM_BooleanParamType, AUTOMATIC) failed;

    res = E_NOT_OK;
    failed = FALSE;

  #if (WDGM_OFF_MODE_ENABLED == STD_ON)
    trigger_mode = g_wdgm_cfg_ptr->DataGRef->TriggerModeId;
  #endif /* (WDGM_OFF_MODE_ENABLED == STD_ON) */

    for (i=0; i < g_wdgm_cfg_ptr->NrOfWatchdogDevices; i++)
    {
      #if (WDGM_OFF_MODE_ENABLED == STD_ON)
        device_ptr = &g_wdgm_cfg_ptr->WdgMWatchdogDeviceRef [i];
        if (device_ptr->WdgMTriggerModeRef[trigger_mode].WdgMWatchdogMode != WDGIF_OFF_MODE)
      #endif /* (WDGM_OFF_MODE_ENABLED == STD_ON) */
        {
            /* Perform immediate reset through the watchdog */
            res = WdgIf_SetTriggerWindow(i, 0, 0);

            if (res == E_NOT_OK)
            {
                failed = TRUE;
                WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                     , WDGM_VENDOR_ID
                                     , API_ID_WdgM_PerformReset
                                     , WDGM_E_WDGIF_MODE
                                     );
              #if (WDGM_SECOND_RESET_PATH == STD_ON)
                /* In failure case perform immediate reset through MCU */
                (void) Appl_Mcu_PerformReset();
              #endif /* (WDGM_SECOND_RESET_PATH == STD_ON) */
            }
        }
    }
    if (failed  == TRUE)
    {
       res = E_NOT_OK;
    }

    /* Immediate reset shall stop the MCU activity, otherwise the result can be
       unintended system behavior. Stopping activity solve also problems with
       double resets. */
    return (res);
}


/* *****************************************************************************
 *  WdgM_PerformReset()
 *    This function instructs the Watchdog Manager to cause a watchdog reset.
 ******************************************************************************/
FUNC (Std_ReturnType, WDGM_CODE) WdgM_PerformReset (void) /* PRQA S 1503  */
{
    VAR (Std_ReturnType, AUTOMATIC) res;

    /* WDGM270: Was the Watchdog Manager initialized? */
    if ( g_wdgm_cfg_ptr == NULL_PTR)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_PerformReset
                             , WDGM_E_NO_INIT
                             );
        res = E_NOT_OK;
    }
    else
    {
        /* WDGM232: the Watchdog Manager shall set the trigger condition
                    for all configured Watchdog Drivers to 0 */
        res = ImmediateWatchdogReset();

        /* WDGM233: */
        g_wdgm_cfg_ptr->DataGRef->GlobalMonitoringStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
    }

    return (res);
}

/* *****************************************************************************
 * WdgM_GetTickCount()
 *
 *   The routine returns the value of the S-WDGM Timebase Tick Counter
 ******************************************************************************/
FUNC (WdgM_TimeBaseTickType, WDGM_CODE) WdgM_GetTickCount (void) /* PRQA S 1503 */ /* PRQA S 1505 */
{
  /* NEXTEER PATCH DESCRIPTION: The patch in this function prevents a write to a global variable which is not 
   *   write accessible from all applications which use this function (i.e. CheckpointReached uses this function
   *   from multiple applications as required by the WdgM configuration ).
   */
  VAR(WdgM_TimeBaseTickType, AUTOMATIC) tick_count;	/* Nexteer Patch: Add local buffer variable */

  #if (WDGM_TIMEBASE_SOURCE == WDGM_INTERNAL_HARDWARE_TICK)
    WdgIf_GetTickCounter (&tick_count);	/* Nexteer Patch: Supply local buffer variable to get hardware tick value */
  #else
    /* (WDGM_TIMEBASE_SOURCE == WDGM_INTERNAL_SOFTWARE_TICK)
       || (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK) */
    tick_count = g_wdgm_tick_count;	/* Nexteer Patch: Set local buffer variable to software tick value */
  #endif /* (WDGM_TIMEBASE_SOURCE == WDGM_INTERNAL_HARDWARE_TICK) */
    return (tick_count);	/* Nexteer Patch: Return local buffer variable */
}

/* *****************************************************************************
 * WdgM_SetTickCount()
 *
 *   The routine set the S-WDGM Timebase Tick Counter to a given value.
 ******************************************************************************/
/* PRQA S 1503 2 */
FUNC (void, WDGM_CODE) WdgM_SetTickCount
    (VAR (WdgM_TimeBaseTickType, AUTOMATIC) time_base_tick)
{
    g_wdgm_tick_count = time_base_tick;
    return;
}

/* *****************************************************************************
 * WdgM_UpdateTickCount()
 *  Increments the S-WDGM Timebase Tick Counter
 *
 *  There are three possible incrementing sources for the S-WdgM Tick Counter:
 *   1. External, that is by calling of the WdgM_UpdateTickCount() function
 *   2. Internal software, the caller of this function is the WdgM_MainFunction itself.
 *   3. Internal hardware, the counter value is retrieved internally from the MCU
 *      through S-WdgIf and S-Wdg
 *  The function runs in caller context!
 ******************************************************************************/
  #if (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK)
    FUNC (void, WDGM_CODE) WdgM_UpdateTickCount (void) /* PRQA S 1503 */
  #else
   #if (WDGM_TIMEBASE_SOURCE == WDGM_INTERNAL_SOFTWARE_TICK)
    #if defined(WDGM_UNIT_TESTS)
     FUNC (void, WDGM_CODE) WdgM_UpdateTickCount (void) /* PRQA S 1503 */
    #else
     STATIC FUNC (void, WDGM_CODE) WdgM_UpdateTickCount (void) /* PRQA S 1503 */
    #endif /* defined(WDGM_UNIT_TESTS) */
   #endif /* (WDGM_TIMEBASE_SOURCE == WDGM_INTERNAL_SOFTWARE_TICK) */
  #endif /* (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK) */

#if (WDGM_TIMEBASE_SOURCE != WDGM_INTERNAL_HARDWARE_TICK)
{
    ++g_wdgm_tick_count;
  #if (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK)
   #if (WDGM_TICK_OVERRUN_CORRECTION == STD_ON)
    /* Check Timebase Tick Counter overrun */
    if ( g_wdgm_tick_count == 0)
    {
        g_wdgm_tick_count_overrun = TRUE;
    }
   #endif /* (WDGM_TICK_OVERRUN_CORRECTION == STD_ON) */
  #endif /* (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK) */
    return;
}
#endif /* (WDGM_TIMEBASE_SOURCE != WDGM_INTERNAL_HARDWARE_TICK) */

#if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
/* *****************************************************************************
 * WriteStateChangeRequest()
 *  This function writes the deactivation/activation request to the GS memory
 ******************************************************************************/
STATIC FUNC (void, WDGM_CODE) WriteStateChangeRequest
    ( VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
    , VAR (WdgM_StateRequestType, AUTOMATIC) state_request
    )
{
    WdgM_GlobalSuspendInterrupts();
    g_wdgm_cfg_ptr->EntityGSRef[SEID].StateChangeRequest =
            (WdgM_StateRequestType) state_request;
    g_wdgm_cfg_ptr->EntityGSRef[SEID].StateChangeRequest_neg =
            (WdgM_StateRequestType) ~state_request;
    WdgM_GlobalRestoreInterrupts();
}
#endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */

#if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
/* *****************************************************************************
 * ReadStateChangeRequest()
 *  This function reads the deactivation/activation request from the GS memory
 ******************************************************************************/
STATIC FUNC (Std_ReturnType, WDGM_CODE) ReadStateChangeRequest
    ( VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
    , P2VAR (WdgM_StateRequestType, AUTOMATIC, WDGM_APPL_DATA) state_request_ptr
    )
{
    VAR (WdgM_StateRequestType, AUTOMATIC) local_state;
    VAR (WdgM_StateRequestType, AUTOMATIC) local_state_neg;
    VAR (Std_ReturnType, AUTOMATIC) res;

    WdgM_GlobalSuspendInterrupts();
    local_state     = g_wdgm_cfg_ptr->EntityGSRef[SEID].StateChangeRequest;
    local_state_neg = (WdgM_StateRequestType)~(g_wdgm_cfg_ptr->EntityGSRef[SEID].
                         StateChangeRequest_neg);
    WdgM_GlobalRestoreInterrupts();
    if (local_state != local_state_neg)
    {
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_MainFunction
                             , WDGM_E_MEMORY_FAILURE         /* GS memory failure */
                             );
        (void)ImmediateWatchdogReset();
        res = E_NOT_OK;
    }
    else
    {
        *state_request_ptr = local_state;
        res = E_OK;
    }

    return(res);
}
#endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */

/* *****************************************************************************
 * BuildEntitiesStatus()
 *  The function pre-builds the Local Monitoring Status for all Entities.
 ******************************************************************************/
STATIC FUNC (void, WDGM_CODE) BuildEntitiesStatus
    ( P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) local_status_failed_ptr
    , P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) local_status_expired_ptr
    )
{
    P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr;
    VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) entity_id;
    VAR (WdgM_LocalStatusType, AUTOMATIC) local_status;
    VAR (WdgM_LocalStatusType, AUTOMATIC) periodic_local_status_alive;
    VAR (WdgM_LocalStatusType, AUTOMATIC) aperiodic_local_status_deadline;
    VAR (WdgM_LocalStatusType, AUTOMATIC) aperiodic_local_status_programflow;
    VAR (WdgM_ViolationCntType, AUTOMATIC) program_flow_violation_cnt;
    VAR (WdgM_ViolationCntType, AUTOMATIC) deadline_violation_cnt;
    VAR (WdgM_CheckpointIdType, AUTOMATIC) remembered_checkpoint_id;
    VAR (WdgM_BooleanParamType, AUTOMATIC) local_activity_flag;
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) remebered_checkpoint_time;
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) current_tick_count;

    /* Default values for returned status */
    *local_status_failed_ptr  =  WDGM_LOCAL_STATUS_OK;
    *local_status_expired_ptr =  WDGM_LOCAL_STATUS_OK;


    /* Evaluate and build a new local status for all entities */
    for (entity_id = 0; entity_id < g_wdgm_cfg_ptr->NrOfSupervisedEntities; entity_id++)
    {
        current_entity_ptr  = &g_wdgm_cfg_ptr->WdgMSupervisedEntityRef[entity_id];
        local_status = current_entity_ptr->EntityStatusGRef->LocalMonitoringStatus;

      #if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
        /* Check the deactivation request and when allowed then deactivate the entity
           BEFORE the entity state evaluation in the lines below happens */
        /* The SE Deactivation shall be explicitly enabled in the configuration */
        if (current_entity_ptr->WdgMEnableEntityDeactivation == STD_ON)
        {
            local_status = DeactivateEntity (current_entity_ptr, local_status, entity_id);
        }
      #endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */

        /* WDGM078, WDGM271, Local Activity Flag */
        if (local_status != WDGM_LOCAL_STATUS_DEACTIVATED)
        {
            /* -----------------------------------------------------------------
             * Step 1: Evaluate for current entity the Alive, Deadline
             *         and Program Flow status
             * -------------------------------------------------------------- */
            /* For interruptibility and consistency reason, load the sensitive variables
               that are written by WdgM_CheckpointReached() to the stack at one position here
               and disable interrupts around */
            WdgM_GlobalSuspendInterrupts();
            program_flow_violation_cnt =
                current_entity_ptr->EntityStatusLRef->ProgramFlowViolationCnt;
            deadline_violation_cnt     =
                current_entity_ptr->EntityStatusLRef->DeadlineViolationCnt;
            remembered_checkpoint_id   =
                current_entity_ptr->EntityStatusLRef->RememberedCheckpointId;
            local_activity_flag        =
                current_entity_ptr->EntityStatusLRef->LocalActivityFlag;
            remebered_checkpoint_time  =
                current_entity_ptr->EntityStatusLRef->RememberedCheckpointTime;
            current_tick_count         =
                WdgM_GetTickCount ();
            WdgM_GlobalRestoreInterrupts();

            /* Build local Alive status */
            periodic_local_status_alive = BuildAliveLocalStatus(current_entity_ptr);

            /* Check the Deadline hangup and merge the Deadline hangup status
               and Aperiodic status to one status */
            CheckDeadlineHangup( current_entity_ptr
                               , &aperiodic_local_status_deadline
                               , remembered_checkpoint_id
                               , local_activity_flag
                               , remebered_checkpoint_time
                               , deadline_violation_cnt
                               , current_tick_count
                               );

            /* Check Deadline Violation(s) */
            CheckDeadlineViolation( current_entity_ptr
                                  , &aperiodic_local_status_deadline
                                  , deadline_violation_cnt
                                  );

            /* Check Program Flow Violation(s) when for current SE requested */
            if (current_entity_ptr->WdgMProgramFlowMonitoring == TRUE)
            {
                CheckProgramFlowViolation( current_entity_ptr
                                         , &aperiodic_local_status_programflow
                                         , program_flow_violation_cnt
                                         );
            }
            else
            {
                /* Set aperiodic_local_status_programflow to OK if no program
                   flow is used. */
                aperiodic_local_status_programflow = WDGM_LOCAL_STATUS_OK;
            }

            /* -----------------------------------------------------------------
             * Step 2: Build for current entity a new Local Status
             * -------------------------------------------------------------- */
            switch (local_status)
            {
                /* -----------------------------------------------------------*/
                case WDGM_LOCAL_STATUS_OK:
                {
                    if ( (  (aperiodic_local_status_deadline == WDGM_LOCAL_STATUS_FAILED)
                         && (current_entity_ptr->WdgMFailedDeadlineRefCycleTol == 0)
                         )
                       ||
                         (  (aperiodic_local_status_programflow == WDGM_LOCAL_STATUS_FAILED)
                         && (current_entity_ptr->WdgMFailedProgramFlowRefCycleTol == 0)
                         )
                       ||
                         (  (periodic_local_status_alive == WDGM_LOCAL_STATUS_FAILED)
                         && (current_entity_ptr->WdgMFailedSupervisionRefCycleTol == 0)
                         )
                       )
                    {
                        /* WDGM202 */
                        local_status = WDGM_LOCAL_STATUS_EXPIRED;
                    }
                    else if ( (aperiodic_local_status_deadline == WDGM_LOCAL_STATUS_FAILED)
                              /* Next term is implied from the fact that the
                                 condition of the previous if did not trigger! */
                              /*&& (current_entity_ptr->WdgMFailedDeadlineRefCycleTol != 0) */
                            ||
                              (aperiodic_local_status_programflow == WDGM_LOCAL_STATUS_FAILED)
                              /* Next term is implied from the fact that the
                                 condition of the previous if did not trigger! */
                              /* && (current_entity_ptr->WdgMFailedProgramFlowRefCycleTol != 0) */
                            ||
                              (periodic_local_status_alive == WDGM_LOCAL_STATUS_FAILED)
                              /* Next term is implied from the fact that the
                                 condition of the previous if did not trigger! */
                              /* && (current_entity_ptr->WdgMFailedSupervisionRefCycleTol != 0) */
                            )
                    {
                        /* WDGM203 */
                        local_status = WDGM_LOCAL_STATUS_FAILED;

                        /* Partition Reset is currently not supported by the MICROSAR OS
                           the S-WdgM doesn't support this feature too */

                    }
                    else
                    {
                        /* MISRA rule 14.10 */
                    }
                }
                break;

                /* ----------------------------------------------------------- */
                case WDGM_LOCAL_STATUS_FAILED:
                {
                    /* Local status recovery FAILED->OK */
                    if (  (aperiodic_local_status_deadline    == WDGM_LOCAL_STATUS_OK)
                       && (aperiodic_local_status_programflow == WDGM_LOCAL_STATUS_OK)
                       && (periodic_local_status_alive        == WDGM_LOCAL_STATUS_OK)
                       )
                    {
                       /* WDGM205 */
                       local_status = WDGM_LOCAL_STATUS_OK;
                    }
                    /* FAILED->EXPIRED */
                    else if (
                              /* next 3 conditions cope with FAILED tolerances
                                 (how long the SE stays in FAILED, if tolerated) */
                              (  ( current_entity_ptr->EntityStatusGRef->FailedDeadlineRefCycles
                                 > current_entity_ptr->WdgMFailedDeadlineRefCycleTol
                                 )
                                 /* (FailedDeadlineRefCycles > 0) implies that
                                    (aperiodic_local_status_deadline == WDGM_LOCAL_STATUS_FAILED)
                                 */
                              )
                            ||
                              (  ( current_entity_ptr->EntityStatusGRef->FailedProgramFlowRefCycles
                                 > current_entity_ptr->WdgMFailedProgramFlowRefCycleTol
                                 )
                                 /* (FailedProgramFlowRefCycles > 0) implies that
                                    (aperiodic_local_status_programflow == WDGM_LOCAL_STATUS_FAILED)
                                 */
                              )
                            ||
                              (  ( current_entity_ptr->EntityStatusGRef->FailedSupervisionRefCycles
                                 > current_entity_ptr->WdgMFailedSupervisionRefCycleTol
                                 )
                                 /* (FailedSupervisionRefCycles > 0) implies that
                                    (periodic_local_status_alive == WDGM_LOCAL_STATUS_FAILED)
                                 */
                              )
                            )
                    {
                       /* WDGM206, WDGM097, WDGM202 */
                       local_status = WDGM_LOCAL_STATUS_EXPIRED;
                    }
                    else
                    {
                        /* MISRA rule 14.10 */
                    }
                }
                break;

                /* ----------------------------------------------------------- */
                case WDGM_LOCAL_STATUS_EXPIRED:
                /* End state, no way out */
                break;
                /* ----------------------------------------------------------*/
                /* No need to list WDGM_LOCAL_STATUS_DEACTIVATED - checked in
                   the "if" above. */

                default:   /* PRQA S 2018 */
                {
                    WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                         , WDGM_VENDOR_ID
                                         , API_ID_WdgM_MainFunction
                                         , WDGM_E_PARAM_STATE
                                         );
                    /* If this statement is reached then another process has
                       corrupted/overwritten the status - perform an immediate
                       reset! */
                    (void) ImmediateWatchdogReset();
                }
                break;
            }

            /* Return 'at least one' failure status */
            if (local_status == WDGM_LOCAL_STATUS_FAILED)
            {
                /* At least one status of one enitity is FAILED */
                *local_status_failed_ptr = WDGM_LOCAL_STATUS_FAILED;
            }
            else if (local_status == WDGM_LOCAL_STATUS_EXPIRED)
            {
                /* At least one status of one entity is EXPIRED */
                *local_status_expired_ptr = WDGM_LOCAL_STATUS_EXPIRED;
            }
            else
            {
                /* MISRA rule 14.10 */
            }
        }

      #if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
        /* Check the activation request and when allowed then activate the entity
           AFTER the entity state evaluation in the lines above happens */
        /* The SE Activation shall be explicitly enabled in the configuration */
        if (current_entity_ptr->WdgMEnableEntityDeactivation == STD_ON)
        {
            local_status = ActivateEntity (local_status, entity_id);
        }
      #endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */

      #if (WDGM_STATE_CHANGE_NOTIFICATION == STD_ON)
        if (current_entity_ptr->WdgM_LocalStateChangeCbk != NULL_PTR)
        {
            /* WDGM197: Local status changed? */
            if ( current_entity_ptr->EntityStatusGRef->LocalMonitoringStatus != local_status)
            {
                (void)current_entity_ptr->WdgM_LocalStateChangeCbk(local_status);
            }
        }
      #endif /* (WDGM_STATE_CHANGE_NOTIFICATION == STD_ON) */

        /* Update the current Local Status */
        current_entity_ptr->EntityStatusGRef->LocalMonitoringStatus = local_status;
    }
    return;
}


#if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
/* *****************************************************************************
 * DeactivateEntity()
 *  The function deactivates an entity.
 *  When the addressed entity is in a state LOCAL_STATUS_OK or in LOCAL_STATUS_FAILED
 *  then this function will deactivate the entity and the entity will be switched
 *  to a state LOCAL_STATUS_DEACTIVATED.
 *  Restrictions:
 *  - The function is not AUTOSAR 4.0 conform!
 *  - The function uses read and write access to the global shared (GS) memmory,
 *  - Before an Entity can be deactivated, it must pass it's End Checkpoint to
 *    clear the LocalActivityFlag. The clearing can't be done in this function
 *    because of the necessary memory write access to local memory area.
 ******************************************************************************/
STATIC FUNC (WdgM_LocalStatusType, WDGM_CODE) DeactivateEntity
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
    , VAR (WdgM_LocalStatusType, AUTOMATIC) local_status
    , VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
    )
{
    VAR (WdgM_StateRequestType, AUTOMATIC) target_entity_state;
    P2CONST (WdgM_CheckPointType, AUTOMATIC, WDGM_APPL_CONST) current_checkpoint_ptr;
    VAR (WdgM_CheckpointIdType, AUTOMATIC) cp_id;

    /* SE deactivation is possible only in STATUS_OK and STATUS_FAILED */
    if ((local_status == WDGM_LOCAL_STATUS_OK)
       || (local_status == WDGM_LOCAL_STATUS_FAILED))
    {
       /* Load the targeted entity state, it shall be an atomic read
          as the variable is in global shared memory area */
        (void) ReadStateChangeRequest (SEID, &target_entity_state);

        /* Is the wished state 'deactivate' ? */
        if (target_entity_state == WDGM_SE_STATE_REQUEST_DEACTIVATE)
        {
            /* Reset Alive */
            current_entity_ptr->EntityStatusGRef->FailedSupervisionRefCycles = 0;
            for (cp_id = 0; cp_id < current_entity_ptr->NrOfCheckpoints; cp_id++)
            {
                current_checkpoint_ptr = &current_entity_ptr->WdgMCheckpointRef[cp_id];

                if (current_checkpoint_ptr->WdgMAliveGRef != NULL_PTR)
                {
                    /* Here we assume that both pointers WdgMAlive[X]Ref are either
                       set or NULL */
                    current_checkpoint_ptr->WdgMAliveGRef->AliveCounterStamp
                        = current_checkpoint_ptr->WdgMAliveLRef->AliveCounter;
                    current_checkpoint_ptr->WdgMAliveGRef->SupervisionAliveCounter = 0;
                }
            }

            /* Reset Deadline */
            current_entity_ptr->EntityStatusGRef->FailedDeadlineRefCycles = 0;
            current_entity_ptr->EntityStatusGRef->FailedDeadlineCycCounter = 0;
            current_entity_ptr->EntityStatusGRef->DeadlineViolationCnt
                = current_entity_ptr->EntityStatusLRef->DeadlineViolationCnt;
            /* Reset Program Flow */
            current_entity_ptr->EntityStatusGRef->FailedProgramFlowRefCycles = 0;
            current_entity_ptr->EntityStatusGRef->FailedProgramFlowCycCounter = 0;
            current_entity_ptr->EntityStatusGRef->ProgramFlowViolationCnt
                = current_entity_ptr->EntityStatusLRef->ProgramFlowViolationCnt;
            /* Set the temporary status to DEACTIVATED */
            /* WDGM207, SE Deactivation */
            local_status = WDGM_LOCAL_STATUS_DEACTIVATED;

            /* Clear the deactivation event */
            WriteStateChangeRequest (SEID, WDGM_SE_STATE_REQUEST_NONE);
        }
        else if (target_entity_state == WDGM_SE_STATE_REQUEST_ACTIVATE)
        {
             ;
        }
        else if (target_entity_state == WDGM_SE_STATE_REQUEST_NONE)
        {
             ;
        }
        else
        {
            /* Wrong requested target status, GS memory corrupted? */
            (void)ImmediateWatchdogReset();
        }
    }
    return(local_status);
}
#endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */


#if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
/* *****************************************************************************
 * ActivateEntity()
 *  The function activates an entity.
 *  When the addressed entity is in a state LOCAL_STATUS_DEACTIVATED then
 *  this function will activate the entity and the entity will be switched
 *  to a state LOCAL_STATUS_OK
 *  Precondition:
 *  - The The Entity must be in a state DEACTIVATED. This state can be reached
 *    by WdgM_Init() or by WdgM_DeactivateSupervisionEntity()
 *  Restrictions:
 *  - The function is not AUTOSAR 4.0 conform!
 *  - The function uses read and write access in to global shared (GS) memmory,
 ******************************************************************************/
STATIC FUNC (WdgM_LocalStatusType, WDGM_CODE) ActivateEntity
    ( VAR (WdgM_LocalStatusType, AUTOMATIC) local_status
    , VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
    )
{
    VAR (WdgM_StateRequestType, AUTOMATIC) target_entity_state;

     /* The switch to STATUS_OK is possible from STATUS_DEACTIVATED only */
    if (local_status == WDGM_LOCAL_STATUS_DEACTIVATED)
    {
        /* Load the targeted entity state it shall be an atomic read
           as the variable is in global shared memory area */
        (void) ReadStateChangeRequest (SEID, &target_entity_state);

        if (target_entity_state == WDGM_SE_STATE_REQUEST_ACTIVATE)
        {
            /* WDGM209, SE Activation */
            local_status = WDGM_LOCAL_STATUS_OK;
            /* Clear the trigger event */
            WriteStateChangeRequest (SEID, WDGM_SE_STATE_REQUEST_NONE);
        }
        else if (target_entity_state == WDGM_SE_STATE_REQUEST_DEACTIVATE)
        {
            ;
        }
        else if (target_entity_state == WDGM_SE_STATE_REQUEST_NONE)
        {
            ;
        }
        else
        {
            /* Wrong target status, GS memory corrupted? */
            (void)ImmediateWatchdogReset();
        }
    }

    return(local_status);
}
#endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */

/* *****************************************************************************
 * BuildAliveLocalStatus()
 *   The function builds the Local Monitoring Status for Alive Monitoring.
 *   Only one Alive counter per Entity is supported.
 ******************************************************************************/
STATIC FUNC (WdgM_LocalStatusType, WDGM_CODE) BuildAliveLocalStatus
    (P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr)
{
    VAR (WdgM_AliveCntType, AUTOMATIC) max_count;
    VAR (WdgM_AliveCntType, AUTOMATIC) min_count;
    VAR (WdgM_AliveCntType, AUTOMATIC) current_count;
    VAR (WdgM_AliveCntType, AUTOMATIC) alive_counter;
    VAR (WdgM_LocalStatusType, AUTOMATIC) local_status = WDGM_LOCAL_STATUS_OK;
    P2CONST (WdgM_CheckPointType, AUTOMATIC, WDGM_APPL_CONST) current_checkpoint_ptr;
    VAR (WdgM_CheckpointIdType, AUTOMATIC) cp_id;

    /* Go through all Checkpoints of the current Entity */
    for (cp_id = 0; cp_id < current_entity_ptr->NrOfCheckpoints; cp_id++)
    {
        /* Pointer to CP */
        current_checkpoint_ptr = &current_entity_ptr->WdgMCheckpointRef[cp_id];

        /* For all CP's with Alive counter defined */
        if ( current_checkpoint_ptr->WdgMAliveGRef != NULL_PTR)
        {
          #if (WDGM_FIRSTCYCLE_ALIVECOUNTER_RESET == STD_ON)
            /* Clear alive counters in the first MainFunction call, start to
               check with the second MainFunction call. */
            if (g_wdgm_cfg_ptr->DataGRef->WdgMMainStarted == FALSE)
            {
                current_checkpoint_ptr->WdgMAliveGRef->AliveCounterStamp
                    = current_checkpoint_ptr->WdgMAliveLRef->AliveCounter;
            }
            else
          #endif /* (WDGM_FIRSTCYCLE_ALIVECOUNTER_RESET == STD_ON) */
            {
                /* How often should it be checked */
                if ( current_checkpoint_ptr->WdgMSupervisionReferenceCycle <=
                     ( current_checkpoint_ptr->WdgMAliveGRef->SupervisionAliveCounter + 1u )
                   )
                {
                    /* WDGM203, WDGM074: Check Configured Margins */
                    max_count = current_checkpoint_ptr->WdgMExpectedAliveIndications
                              + current_checkpoint_ptr->WdgMMaxMargin;
                    min_count = current_checkpoint_ptr->WdgMExpectedAliveIndications
                              - current_checkpoint_ptr->WdgMMinMargin;

                    /* Read the local Alive counter in one point of time to stack */
                    alive_counter =  current_checkpoint_ptr->WdgMAliveLRef->AliveCounter;

                    /* Get the actual count of the Alive counter */
                    current_count  = alive_counter
                                   - current_checkpoint_ptr->WdgMAliveGRef->AliveCounterStamp;
                    /* Check the configured count margins */
                    if (  (min_count > current_count) || (max_count < current_count) )
                    {
                        /* Alive indications are out of expected margins */
                        local_status = WDGM_LOCAL_STATUS_FAILED;
                        /* Update 'Failed' counter */
                        current_entity_ptr->EntityStatusGRef->FailedSupervisionRefCycles++;
                        /* As here the status for the whole entity is changed
                           the Alive Monitoring expect only one Alive counter per entity */
                    }
                    else
                    {
                        /* Reset 'Failed' counter */
                        current_entity_ptr->EntityStatusGRef->FailedSupervisionRefCycles = 0;
                    }
                    /* Load the Alive counter stamp with current value */
                    current_checkpoint_ptr->WdgMAliveGRef->AliveCounterStamp
                        = alive_counter;

                    /* Reset SupervisionAliveCounter */
                    current_checkpoint_ptr->WdgMAliveGRef->SupervisionAliveCounter = 0;
                }
                else
                {
                    /* Count SupervisionAliveCounter up */
                    current_checkpoint_ptr->WdgMAliveGRef->SupervisionAliveCounter ++;

                    /* Preserve status from previous rounds - do not overwrite with OK */
                    local_status = current_entity_ptr->EntityStatusGRef->LocalMonitoringStatus;
                }
            }
        }
    }
    return (local_status);
}

/* *****************************************************************************
 * CheckDeadlineHangup()
 *  The function checks the Deadline Monitoring case when the second CP
 *  of a Transition is not called anymore. Shall be called before
 *  the CheckDeadlineViolation() routine.
 ******************************************************************************/
STATIC FUNC (void , WDGM_CODE) CheckDeadlineHangup
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
    , P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) aperiodic_local_status_deadline
    , VAR (WdgM_CheckpointIdType, AUTOMATIC) remembered_checkpoint_id
    , VAR (WdgM_BooleanParamType, AUTOMATIC) local_activity_flag
    , VAR (WdgM_TimeBaseTickType, AUTOMATIC) remembered_checkpoint_time
    , VAR (WdgM_ViolationCntType, AUTOMATIC) deadline_violation_cnt
    , VAR (WdgM_TimeBaseTickType, AUTOMATIC) current_tick_count
    )
{
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) time_diff;
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) outgoing_deadline_max;
  #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
    P2CONST (WdgM_CheckPointType, AUTOMATIC, WDGM_APPL_CONST) remembered_checkpoint_ptr;
    VAR (WdgM_TransitionIdType, AUTOMATIC) g_tr;
    VAR (boolean, AUTOMATIC) g_tr_occurred = FALSE;
  #endif /* WDGM_GLOBAL_TRANSITIONS == STD_ON */

    /* Check if a deadline violation has been detected and set the deadline status */
    if (   current_entity_ptr->EntityStatusGRef->DeadlineViolationCnt
        == deadline_violation_cnt
       )
    {
        /* New deadline violation not detected */
        *aperiodic_local_status_deadline = WDGM_LOCAL_STATUS_OK;
    }
    else
    {
        /* New deadline violation detected */
        *aperiodic_local_status_deadline = WDGM_LOCAL_STATUS_FAILED;
    }

    /* Check Deadline hangup for walid CP only */
    if (remembered_checkpoint_id != WDGM_INVALID_CP_ID)
    {
      #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
        remembered_checkpoint_ptr =
            &current_entity_ptr->WdgMCheckpointRef [remembered_checkpoint_id];
      #endif /* WDGM_GLOBAL_TRANSITIONS == STD_ON */

        if (  /* if current entity is running */
             (local_activity_flag  == TRUE)
           #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
             /* or in the case that the last check point of
                this entity has started a global transition */
             || (remembered_checkpoint_ptr->WdgMStartsAGlobalTransition == TRUE)
           #endif /* WDGM_GLOBAL_TRANSITIONS == STD_ON */
           )
        {
            /* WDGM231: Check Dedline Monitoring hang-up case when a CP wasn't called.
               Take the time between current and last remembered CP time
               and compare it with max outgoing deadline time of the previous remembered CP */

            outgoing_deadline_max =
               current_entity_ptr->WdgMCheckpointRef[remembered_checkpoint_id].
                    WdgMOutgoingDeadlineMax;

            /* Is the Outgoing Max Time for the remembered CP defined?
               The End Checkpoints have no Outgoing Max time */
            if (outgoing_deadline_max != 0)
            {
              #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
                /* Check global transition flag for all outgoing global
                   transitons out of this checkpoint. */
                /* Find out if a global transition out of this checkpoint has already occurred */
                for (  g_tr = 0;
                       g_tr < remembered_checkpoint_ptr->NrOfStartedGlobalTransitions;
                       g_tr ++
                    )
                {
                    if (  WdgM_ReadGlobalTransitionFlag
                            ( remembered_checkpoint_ptr->WdgMStartedGlobalTransitionIds [g_tr]
                            , FALSE
                            )
                       == FALSE
                       )
                    {
                        /* If global transition flag is false then this
                           transition has alread occurred! */
                        g_tr_occurred = TRUE;
                        break;
                    }
                }

                /* If remembered checkpoint has started a potential global
                   transitions and one of these global transitions has indeed
                   occured */
                if (g_tr_occurred == TRUE)
                {
                    /* do not check local timeout,
                       because a global transition has already occured */
                }
                else
              #endif /* WDGM_GLOBAL_TRANSITIONS == STD_ON */
                /* Take periodicity in account, in case deadline errors are
                   tolerated for this entity. */
                if (  (current_entity_ptr->WdgMDeadlineReferenceCycle == 0)
                   || (current_entity_ptr->EntityStatusGRef->FailedDeadlineCycCounter == 0)
                   )
                {
                    /* Check normally for a local timeout */
                    /* The time between 'now' and last remembered CP time */
                    time_diff = current_tick_count - remembered_checkpoint_time;

                    if ( time_diff > outgoing_deadline_max)
                    {
                        /* The next Checkpoint wasn't called, set local status to
                           FAILED, whether it should move to EXPIRED is checked in
                           the MainFunction. */
                        *aperiodic_local_status_deadline = WDGM_LOCAL_STATUS_FAILED;
                    }
                }
                else
                {
                    /* MISRA rule 14.10 */
                }
            }
        }
    }
    return;
}

/* *****************************************************************************
 * CheckDeadlineViolation()
 *  The function checks Deadline Violation and updates the 'failed' counter.
 *  Precondition: The CheckDeadlineHangup() was already executed.
 ******************************************************************************/
STATIC FUNC (void, WDGM_CODE) CheckDeadlineViolation
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
    , P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) aperiodic_local_status_deadline
    , VAR (WdgM_ViolationCntType, AUTOMATIC) deadline_violation_cnt
    )
{
    VAR (WdgM_LocalStatusType, AUTOMATIC) temp_aperiodic_local_status_deadline;

    /* At least one deadline violation was detected during the last
       supervision cycle? */
    if (  (*aperiodic_local_status_deadline == WDGM_LOCAL_STATUS_FAILED)
       || (current_entity_ptr->EntityStatusGRef->FailedDeadlineRefCycles > 0)
       )
    {
        /* Keep the error status in this reference cycle. */
        temp_aperiodic_local_status_deadline = *aperiodic_local_status_deadline;
        *aperiodic_local_status_deadline = WDGM_LOCAL_STATUS_FAILED;

        if (current_entity_ptr->EntityStatusGRef->FailedDeadlineCycCounter == 0)
        {
            /* Update FAILED counter (number of reference cycles in which
               the SE was in state FAILED) */
            current_entity_ptr->EntityStatusGRef->FailedDeadlineRefCycles++;

            /* No deadline violation during the last supervision cycle -> Recovery */
            if (  (current_entity_ptr->EntityStatusGRef->DeadlineViolationCnt
                   == deadline_violation_cnt
                  )
               && (temp_aperiodic_local_status_deadline == WDGM_LOCAL_STATUS_OK)
               )
            {
                /* Reset error status for the next deadline supervision cycle */
                *aperiodic_local_status_deadline = WDGM_LOCAL_STATUS_OK;

                /* Reset FAILED reference cycles counter */
                current_entity_ptr->EntityStatusGRef->FailedDeadlineRefCycles = 0;
            }
            else
            {
                /* Reset the Deadline violation flag in the beginning of a
                   supervision cycle. */
                current_entity_ptr->EntityStatusGRef->DeadlineViolationCnt
                    = deadline_violation_cnt;
            }
        }

        /* How often should it be checked for Deadline Violations? */
        if ( current_entity_ptr->WdgMDeadlineReferenceCycle <=
             ( current_entity_ptr->EntityStatusGRef->FailedDeadlineCycCounter + 1u )
           )
        {
            /* Reset the Cycle Counter (number of S-WdgM cycles in which
               the SE was in state FAILED) */
            current_entity_ptr->EntityStatusGRef->FailedDeadlineCycCounter = 0;
        }
        else
        {
            /* Count FAILED Cycle Counter up */
            current_entity_ptr->EntityStatusGRef->FailedDeadlineCycCounter ++;
        }
    }
    return;
}

/* *****************************************************************************
 * CheckProgramFlowViolation()
 *  The function checks Program Flow Violation and updates the 'failed' counter.
 ******************************************************************************/
STATIC FUNC (void, WDGM_CODE) CheckProgramFlowViolation
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
    , P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) aperiodic_local_status_programflow
    , VAR (WdgM_ViolationCntType, AUTOMATIC) program_flow_violation_cnt
    )
{
    /* Check if a program flow violation has been detected */
    if (   current_entity_ptr->EntityStatusGRef->ProgramFlowViolationCnt
        == program_flow_violation_cnt
       )
    {
        /* New program flow violation not detected */
        *aperiodic_local_status_programflow = WDGM_LOCAL_STATUS_OK;
    }
    else
    {
        /* New program flow violation detected */
        *aperiodic_local_status_programflow = WDGM_LOCAL_STATUS_FAILED;
    }

    /* At least one program flow violation was detected during the last
       supervision cycle? */
    if (  (*aperiodic_local_status_programflow == WDGM_LOCAL_STATUS_FAILED)
       || (current_entity_ptr->EntityStatusGRef->FailedProgramFlowRefCycles > 0)
       )
    {
        /* Keep the error status in this reference cycle. */
        *aperiodic_local_status_programflow = WDGM_LOCAL_STATUS_FAILED;

        if (current_entity_ptr->EntityStatusGRef->FailedProgramFlowCycCounter == 0)
        {
            /* Update FAILED counter (number of reference cycles in which
               the SE was in state FAILED) */
            current_entity_ptr->EntityStatusGRef->FailedProgramFlowRefCycles++;

            /* No program flow violation during the last supervision cycle -> Recovery */
            if (   current_entity_ptr->EntityStatusGRef->ProgramFlowViolationCnt
                == program_flow_violation_cnt
               )
            {
                /* Reset error status for the next program flow supervision cycle */
                *aperiodic_local_status_programflow = WDGM_LOCAL_STATUS_OK;

                /* Reset FAILED reference cycles counter */
                current_entity_ptr->EntityStatusGRef->FailedProgramFlowRefCycles = 0;
            }
            else
            {
                /* Reset the Program flow violation flag in the beginning of a
                   supervision cycle. */
                current_entity_ptr->EntityStatusGRef->ProgramFlowViolationCnt
                    = program_flow_violation_cnt;
            }
        }

        /* How often should it be checked for Program Flow Violations? */
        if ( current_entity_ptr->WdgMProgramFlowReferenceCycle <=
             ( current_entity_ptr->EntityStatusGRef->FailedProgramFlowCycCounter + 1u )
           )
        {
            /* Reset the Cycle Counter (number of S-WdgM cycles in which
               the SE was in state FAILED) */
            current_entity_ptr->EntityStatusGRef->FailedProgramFlowCycCounter = 0;
        }
        else
        {
            /* Count FAILED Cycle Counter up */
            current_entity_ptr->EntityStatusGRef->FailedProgramFlowCycCounter ++;
        }
    }
    return;
}

#define WDGM_STOP_SEC_CODE
#include "MemMap.h"         /* PRQA S 5087 */
