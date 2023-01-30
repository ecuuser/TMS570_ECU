/* Copyright (C) 2010-2012 TTTech Automotive GmbH. All rights reserved
 * Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
 *
 * Name
 *    WdgM_Checkpoint.c
 *
 * Purpose
 *   Watchdog Manager - Checkpoint reached file
 *
 * Revisions
 *
 *   25-Mar-2011  (PPU) Creation
 *   04-Jul-2011  (PPU) [41323] #include MemMap.h for code added,
 *                              disable/enable interrupt for crit. section added
 *   20-Jul-2011  (PPU) [41673] WdgMCheckpointLocInitialId is always zero
 *   05-Sep-2011  (PPU) [42340] for safety reasons use the primary reset path
 *                              for IMMEDIATE_RESET
 *   15-Sep-2011  (VLE) [42509] check for a valid global transition repaired
 *                              in the case of a local initial checkpoint
 *   15-Sep-2011  (PPU) [42526] compiler warnings (RememberedEntityID_net) removed
 *   30-Sep-2011  (PPU) [42797] Compiler warnings removed,
 *   18-Oct-2011  (VLE) [43092] global transitions repaired - global transition
 *                              flag introduced
 *   18-Oct-2011  (VLE) [42983] deadlines of all global transitions now checked
 *   09-Dec-2011  (PPU) [43881] Unused variable removed
 *   23-Dec-2011  (PPU) [43770] MainFunction write access to entity mem removed
 *   10-Jan-2012  (VLE) [44107] d/pf debouncing parameters optimization
 *   24-Jan-2012  (PPU) [44450] CP interrupted by MainFunction issue
 *   17-Apr-2012  (VLE) [45759] clearing of global transition flag repaired
 *   25-Apr-2012  (VLE) [45927] RememberedEntityId replaced by global transition
 *                              flags
 *   08-May-2012  (VLE) [43054] Splitting of program flow not allowed any more
 *   10-May-2012  (VLE) [46206] Minor changes to increase test coverage
 *   22-Aug-2012  (VLE) [46993] External modules Det, Dem, Mcu, BswM_WdgM
 *                              replaced by user-defined Appl_* modules
 *   24-Aug-2012  (PPU) [48261] 'ProgramFlowViolationCnt is wrongly incremented'
 *                              replaced by DET call
 *   28-Aug-2012  (VLE) [46820] Compiler abstraction according to AUTOSAR
 *   04-Sep-2012  (PPU) [48587] Formal review - change the version to 2.0.0
 *   05-Sep-2012  (PPU) [48583] Formal review - repaired point 1, 2, 6.16, 6.18
 */



/* -------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                           */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:1503) The function 'WdgM_CheckpointReached' is
                   defined but is not used within this project.
 * Justification : The function 'WdgM_CheckpointReached' is the interface
                   of this SW module to the other SW modules.                 */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:2018) This switch default label is unreachable.
 * Justification : As the variable 'local_status' lives together with other task
                   variables, there is potential possibility of it's corruption.
                   To capture this failure we use the 'default:' statement.   */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:1505) The function 'xx' is only referenced in the
                   translation unit where it is defined.
                   MISRA-C:2004 Rule 8.10
 * Justification : 'WdgM_WriteGlobalActivityFlag',
                   'WdgM_ReadGlobalTransitionFlag' and
                   'WdgM_WriteGlobalTransitionFlag' are used in both WdgM.c and
                   WdgM_Checkpoint.c                                          */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:3447) 'g_wdgm_cfg_ptr' has external linkage but this
                   declaration is not in a header file.
 * Justification : The variable 'g_wdgm_cfg_ptr' is declared in the source file
                   WdgM.c and must be visible only in both WdgM.c and
                   WdgM_Checkpoint.c, therefore it is not defined as external in
                   a header file.                                             */


/* ****************************************************************************
 * Remark
 * In the whole module
 *  - the term 'current', 'actual' means the runtime value (e.g. current Checkpoint)
 *  - the term 'configured', 'defined' means the value comming from configuration
 *
 ******************************************************************************/

/* ****************************************************************************
 * Includes
 ******************************************************************************/
#include "WdgM.h"
#if (WDGM_DEV_ERROR_DETECT == STD_ON)
    #include "Appl_Det.h"
#endif /* (WDGM_DEV_ERROR_DETECT == STD_ON) */


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
 * Global variables
 *****************************************************************************/


/* ***************************************************************************
 * Externals
 *****************************************************************************/
/* Pointer to loaded ROM configuration, NULL_PTR if WdgM is not initialized */
extern P2CONST (WdgM_ConfigType, AUTOMATIC, WDGM_APPL_CONST) g_wdgm_cfg_ptr; /* PRQA S 3447 */

/* ***************************************************************************
 * Internal functions
 *****************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */

STATIC FUNC (void, WDGM_CODE) ProgramFlowAndDeadlineMonitoring
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
    , P2CONST (WdgM_CheckPointType, AUTOMATIC, WDGM_APPL_CONST) current_checkpoint_ptr
    , VAR (WdgM_CheckpointIdType, AUTOMATIC) CPID
    , VAR (WdgM_TimeBaseTickType, AUTOMATIC) current_tick_count
    , VAR (WdgM_CheckpointIdType, AUTOMATIC) RememberedCheckpointId
  #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
    , VAR (WdgM_SharedBooleanType, AUTOMATIC) global_activity
  #endif /* (WDGM_GLOBAL_TRANSITIONS == STD_ON) */
    );

STATIC FUNC (WdgM_TransitionIdType, WDGM_CODE) FindTransitionId
    ( P2CONST (WdgM_TransitionType, AUTOMATIC, WDGM_APPL_CONST) current_transition_ptr
    , VAR (WdgM_CheckpointIdType, AUTOMATIC) RememberedCheckpointId
    , VAR (WdgM_TransitionIdType, AUTOMATIC) nr_of_incomming_transitions
    );

#if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
  STATIC FUNC (WdgM_SharedBooleanType, WDGM_CODE) WdgM_ReadAndClearGlobalTransitionFlags
      ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
      , P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) previous_entity_ptr
      , VAR (WdgM_CheckpointIdType, AUTOMATIC) g_tr_source_cp_id
      , VAR (WdgM_TransitionIdType, AUTOMATIC) current_g_tr_flag_id
      , VAR (WdgM_CheckpointIdType, AUTOMATIC) RememberedCheckpointId
      );

  STATIC FUNC (WdgM_SharedBooleanType, WDGM_CODE) WdgM_ReadGlobalActivityFlag (void);

  STATIC FUNC (void, WDGM_CODE) ClearGlobalIncomingTrFlagsForCP
      (P2CONST (WdgM_CheckPointType, AUTOMATIC, WDGM_APPL_CONST) current_checkpoint_ptr);
#endif /* (WDGM_GLOBAL_TRANSITIONS == STD_ON) */


/* *****************************************************************************
 *  WdgM_CheckpointReached
 *
 *    This function is the point where the observed software indicates to
 *    the S-WDGM that a Checkpoint was reached.
 *    The main functionality is:
 *     - Program flow check
 *     - Deadline check
 *     - Alive counter update
 *
 *    The routine is running in the CALLER context!
 ******************************************************************************/

#if (WDGM_AUTOSAR_3_1_X_COMPATIBILITY != STD_ON)
  /* Checkpoint reached functionality as defined by AUTOSAR 4.0 r1 */
  /* PRQA S 1503 3 */
  FUNC (Std_ReturnType, WDGM_CODE) WdgM_CheckpointReached
      ( VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
      , VAR (WdgM_CheckpointIdType, AUTOMATIC) CPID
      )
#else
  /* Update alive counter functionality as defined by AUTOSAR 3.1 */
  /* PRQA S 1503 2 */
  FUNC (Std_ReturnType, WDGM_CODE) WdgM_UpdateAliveCounter
      (VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID)
#endif /* (WDGM_AUTOSAR_3_1_X_COMPATIBILITY != STD_ON) */
{
    VAR (Std_ReturnType, AUTOMATIC) res = E_OK;
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) tick_count_now;
    VAR (WdgM_LocalStatusType, AUTOMATIC) aperiodic_local_status;
    P2CONST (WdgM_CheckPointType, AUTOMATIC, WDGM_APPL_CONST) current_checkpoint_ptr;
    P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr;
    VAR (WdgM_CheckpointIdType, AUTOMATIC) remembered_cp_id;
  #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
    VAR (WdgM_TransitionIdType, AUTOMATIC) g_tr;
    VAR (WdgM_SharedBooleanType, AUTOMATIC) global_activity_flag;
  #endif /* (WDGM_GLOBAL_TRANSITIONS == STD_ON) */
  #if (WDGM_AUTOSAR_3_1_X_COMPATIBILITY == STD_ON)
    VAR (WdgM_CheckpointIdType, AUTOMATIC) CPID = 0;
  #endif /* (WDGM_AUTOSAR_3_1_X_COMPATIBILITY == STD_ON) */

    /* WDGM279: Was the Watchdog Manager initialized? */
    if (g_wdgm_cfg_ptr == NULL_PTR)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_CheckpointReached
                             , WDGM_E_NO_INIT
                             );
        res = E_NOT_OK;
    }
    /* WDGM278: Is the current SE ID inside of the configured border? */
    else if (g_wdgm_cfg_ptr->NrOfSupervisedEntities <= SEID)
    {
        /* WDGM004 */
        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                             , WDGM_VENDOR_ID
                             , API_ID_WdgM_CheckpointReached
                             , WDGM_E_PARAM_SEID
                             );
        res = E_NOT_OK;
    }
    else
    {
        /* Load current SE pointer */
        current_entity_ptr     = &g_wdgm_cfg_ptr->WdgMSupervisedEntityRef[SEID];

        /* WDGM284: Is the current Checkpoint ID inside defined borders? */
        if ((current_entity_ptr->NrOfCheckpoints) <= CPID)
        {
        /* WDGM004: */
            WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                 , WDGM_VENDOR_ID
                                 , API_ID_WdgM_CheckpointReached
                                 , WDGM_E_CPID
                                 );
            res = E_NOT_OK;
        }
        else
        {
            /* ----------------------------------------------------------------
             * After this point we assume that the configuration for SE and CP is OK!
             * -------------------------------------------------------------- */

             /* Load current CP pointer */
            current_checkpoint_ptr =
                &g_wdgm_cfg_ptr->WdgMSupervisedEntityRef[SEID].WdgMCheckpointRef[CPID];

            /* For interruptibility and consistency reason, load the sensitive variables
               that are written by WdgM_MainFunction() to the stack at one position here
               and disable interrupts around */
            WdgM_GlobalSuspendInterrupts();
            /* Get current TickCount */
            tick_count_now = WdgM_GetTickCount();
            /* Load current Aperiodic Local Monitoring Status */
            aperiodic_local_status =
                current_entity_ptr->EntityStatusGRef->LocalMonitoringStatus;
          #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
            global_activity_flag = WdgM_ReadGlobalActivityFlag();
            if (  (global_activity_flag == FALSE)
               && (g_wdgm_cfg_ptr->WdgMGlobInitialCheckpointId == CPID)
               && (g_wdgm_cfg_ptr->WdgMGlobInitialEntityId
                  == current_entity_ptr->WdgMSupervisedEntityId
                  )
               )
            {
                /* Access function is used, because the GlobalAtivityFlag is a data
                   placed in different protection area */
                WdgM_WriteGlobalActivityFlag(TRUE);
            }

            /* WDGM252: */
            /* If this check point is global terminating - reset global activity flag */
            if (current_checkpoint_ptr->WdgMIsEndCheckpointGlobal == TRUE)
            {
                WdgM_WriteGlobalActivityFlag(FALSE);
            }
          #endif /* (WDGM_GLOBAL_TRANSITIONS == STD_ON) */
            remembered_cp_id = current_entity_ptr->EntityStatusLRef->RememberedCheckpointId;
            /* Remember the current Checkpoint */
            current_entity_ptr->EntityStatusLRef->RememberedCheckpointId = CPID;
            WdgM_GlobalRestoreInterrupts();

            switch (aperiodic_local_status)
            {
                /* -------------------------------------------------------------------*/
                case WDGM_LOCAL_STATUS_OK:
                case WDGM_LOCAL_STATUS_FAILED:
                {
                    /* Is the current CP defined in the Config? */
                    if (current_checkpoint_ptr->WdgMCheckpointId == CPID)
                    {
                        /* Program Flow and Deadline Monitoring */
                        ProgramFlowAndDeadlineMonitoring ( current_entity_ptr
                                                         , current_checkpoint_ptr
                                                         , CPID
                                                         , tick_count_now
                                                         , remembered_cp_id
                                                       #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
                                                         , global_activity_flag
                                                       #endif /* (WDGM_GLOBAL_TRANSITIONS
                                                                  == STD_ON) */
                                                         );

                        /* Alive Monitoring       */
                        /* Update counter for all defined (the first too!) Checkpoints */
                        if (current_checkpoint_ptr->WdgMAliveLRef != NULL_PTR)
                        {
                            WdgM_GlobalSuspendInterrupts();

                            /* Update the current Alive counter */
                            ++current_checkpoint_ptr->WdgMAliveLRef->AliveCounter;

                            /* issue45709: check alive counter for overflow */
                            /* Note: if an overflow happens then an error has
                               already occurred, because this means that this
                               AC came more times during the last supervision
                               cycle than can be configured.
                               If local_AC == global_ACStamp (after increment)
                               then an overflow has just happened. In this case
                               set the AC back to ACStamp - 1 to indicate the
                               error:
                               in this case the alive counter is indicated to
                               have moved AC - ACStamp times == 0xFFFFFFFF times
                               which is way higher than the maximum of
                               WdgMExpectedAliveIndications + MaxMargin, hence
                               an error is detected during the next
                               WdgM_MainFunction. */
                            if ( current_checkpoint_ptr->WdgMAliveLRef->AliveCounter
                              == current_checkpoint_ptr->WdgMAliveGRef->AliveCounterStamp
                               )
                            {
                                /* Set local AliveCounter back to global
                                   AliveCounterStamp - 1 to indicate an error. */
                                --current_checkpoint_ptr->WdgMAliveLRef->AliveCounter;
                            }

                            WdgM_GlobalRestoreInterrupts();
                        }
                    }
                    else
                    {
                        /* Current CP is not defined in the Config */
                        WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                             , WDGM_VENDOR_ID
                                             , API_ID_WdgM_CheckpointReached
                                             , WDGM_E_CPID
                                             );
                        res = E_NOT_OK;
                    }
                }
                break;

                /* -------------------------------------------------------------------*/
                case WDGM_LOCAL_STATUS_EXPIRED:
                {
                    /* End state, no way out. */
                }
                break;

                /* -------------------------------------------------------------------*/
                case WDGM_LOCAL_STATUS_DEACTIVATED:
                {
                    /* WDGM208: No activity here. */
                }
                break;

                /* -------------------------------------------------------------------*/
                default:  /* PRQA S 2018 */
                {
                    res = E_NOT_OK;
                    WDGM_DET_REPORTERROR ( WDGM_MODULE_ID
                                         , WDGM_VENDOR_ID
                                         , API_ID_WdgM_CheckpointReached
                                         , WDGM_E_PARAM_STATE
                                         );
                    /* If this statement is reached then another process has
                       corrupted/overwritten the status - perform an immediate
                       reset! */
                    g_wdgm_cfg_ptr->DataGSRef->InternalFailureFlag = WDGM_INTERNAL_CP_TEST_NOK;
                }
                break;
            }

            /* Remember the current time */
            current_entity_ptr->EntityStatusLRef->RememberedCheckpointTime = tick_count_now;

            /* WDGM248: Remember current Supervised Entity - OBSOLETE!
               NOT DONE ANY MORE! */
          #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
            /* Set global transition flag for ALL OUTGOING GLOBAL TRANSITIONS */
            for (g_tr = 0; g_tr < current_checkpoint_ptr->NrOfStartedGlobalTransitions; g_tr ++)
            {
                WdgM_WriteGlobalTransitionFlag
                    (current_checkpoint_ptr->WdgMStartedGlobalTransitionIds[g_tr], TRUE);
            }
          #endif /* WDGM_GLOBAL_TRANSITIONS == STD_ON */
        }
    }
    return (res);
}

#if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
/* *****************************************************************************
 *  WdgM_WriteGlobalActivityFlag()
 *   The 'GlobalActivityFlag' variable can be placed in
 *   different protected memory area as the caller of the WdgM_CheckpointReached()
 *   function. Therefore the variable is placed in to a shared memory array
 *   and the function writes negated value for later validity check.
 *   NOTE: Caller must protect from interrupts!
 ******************************************************************************/
/* PRQA S 1503 2 */
FUNC (void, WDGM_CODE) WdgM_WriteGlobalActivityFlag
    (VAR (WdgM_SharedBooleanType, AUTOMATIC) activity_flag)
{
    g_wdgm_cfg_ptr->DataGSRef->GlobalActivityFlag = activity_flag;
    g_wdgm_cfg_ptr->DataGSRef->GlobalActivityFlag_neg =
       (WdgM_SharedBooleanType) ~activity_flag;
}

/* *****************************************************************************
 *  WdgM_ReadGlobalActivityFlag()
 *   The read uses a negated value validation check. When the check shows
 *   a failure, the MCU_Reset is called.
 *   NOTE: Caller must protect from interrupts!
 ******************************************************************************/
STATIC FUNC (WdgM_SharedBooleanType, WDGM_CODE) WdgM_ReadGlobalActivityFlag (void)
{
    VAR (WdgM_SharedBooleanType, AUTOMATIC) activity_flag;

    activity_flag = g_wdgm_cfg_ptr->DataGSRef->GlobalActivityFlag;
    if (   activity_flag
       != (WdgM_SharedBooleanType)~g_wdgm_cfg_ptr->DataGSRef->GlobalActivityFlag_neg
       )
    {
        g_wdgm_cfg_ptr->DataGSRef->InternalFailureFlag = WDGM_INTERNAL_CP_TEST_NOK;
        /* Memory is corrupted and the value of the flag cannot be trusted:
           return FALSE. */
        activity_flag = FALSE;
    }

    return(activity_flag);
}

/* *****************************************************************************
 *  WdgM_ReadGlobalTransitionFlag()
 *   The read uses a negated value validation check. When the check shows
 *   a failure, the MCU_Reset is called.
 ******************************************************************************/
/* PRQA S 1505 4 */
FUNC (WdgM_SharedBooleanType, WDGM_CODE) WdgM_ReadGlobalTransitionFlag
    ( VAR (WdgM_TransitionIdType, AUTOMATIC) global_tr_id
    , VAR (uint8, AUTOMATIC) clear_after_read
    )
{
    VAR (WdgM_SharedBooleanType, AUTOMATIC) transition_flag;

    WdgM_GlobalSuspendInterrupts();
    transition_flag =
        g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef [global_tr_id].GlobalTransitionFlag;
    if (   transition_flag
       != (WdgM_SharedBooleanType) ~g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef [global_tr_id].
            GlobalTransitionFlag_neg
       )
    {
        g_wdgm_cfg_ptr->DataGSRef->InternalFailureFlag = WDGM_INTERNAL_CP_TEST_NOK;
        /* Memory is corrupted and the value of the flag cannot be trusted:
           return FALSE. */
        transition_flag = FALSE;
    }
    else if (clear_after_read == TRUE)
    {
        g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef [global_tr_id].GlobalTransitionFlag =
           (WdgM_SharedBooleanType)FALSE;
        g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef [global_tr_id].GlobalTransitionFlag_neg =
           (WdgM_SharedBooleanType)~FALSE;
    }
    else
    {
        ; /* MISRA rule 14.10 */
    }
    WdgM_GlobalRestoreInterrupts();

    return(transition_flag);
}

/* *****************************************************************************
 *  WdgM_ReadAndClearGlobalTransitionFlags()
 *   The read uses a negated value validation check. When the check shows
 *   a failure, the MCU_Reset is called.
 *   Returns TRUE if the given checkpoint starts at least one global transition
 *   and the global transition flags of all started global transitions are TRUE,
 *   and the given global transition source checkpoint ID (g_tr_source_cp_id)
 *   matches the remembered checkpoint ID of the previous entity.
 *   Returns FALSE if no global transitions are started or at least one global
 *   transition flag is false (program flow has gone this way).
 *   All global transition flags are cleared.
 ******************************************************************************/
STATIC FUNC (WdgM_SharedBooleanType, WDGM_CODE) WdgM_ReadAndClearGlobalTransitionFlags
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
    , P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) previous_entity_ptr
    , VAR (WdgM_CheckpointIdType, AUTOMATIC) g_tr_source_cp_id
    , VAR (WdgM_TransitionIdType, AUTOMATIC) current_g_tr_flag_id
    , VAR (WdgM_CheckpointIdType, AUTOMATIC) RememberedCheckpointId
    )
{
    P2CONST (WdgM_CheckPointType, AUTOMATIC, WDGM_APPL_CONST) previous_checkpoint_ptr;
    VAR (WdgM_SharedBooleanType, AUTOMATIC) prev_g_tr_flag;
    VAR (WdgM_SharedBooleanType, AUTOMATIC) transition_flag;
    VAR (WdgM_TransitionIdType, AUTOMATIC) prev_cp_started_g_tr_id;
    VAR (WdgM_CheckpointIdType, AUTOMATIC) previous_remembered_cpid;
    VAR (WdgM_TransitionIdType, AUTOMATIC) g_tr_flag_id;

    prev_g_tr_flag = FALSE;

    WdgM_GlobalSuspendInterrupts();
    /* Take remembered Checkpoint ID of the previous entity */
    if (current_entity_ptr != previous_entity_ptr)
    {
        previous_remembered_cpid =
            previous_entity_ptr->EntityStatusLRef->RememberedCheckpointId;
    }
    else
    {
        /* If previous entity is current entity then take the remembered CP ID
           which is saved in the atomic read before overwriting it with the
           current CP ID. */
        previous_remembered_cpid = RememberedCheckpointId;
    }

    if (previous_remembered_cpid != WDGM_INVALID_CP_ID)
    {
        previous_checkpoint_ptr =
            &previous_entity_ptr->WdgMCheckpointRef [previous_remembered_cpid];
        prev_cp_started_g_tr_id = previous_checkpoint_ptr->NrOfStartedGlobalTransitions;

        /* Check if when coming from a global transition, then if the
           current incoming global transition is active at all.
           Otherwise no splitting of PF is possible. */
        transition_flag = TRUE;
        if (current_g_tr_flag_id != WDGM_INVALID_TR_ID)
        {
            /* Read and check global transition flag for consistency. */
            transition_flag =
                g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef
                    [current_g_tr_flag_id].GlobalTransitionFlag;
            if (   transition_flag
               != (WdgM_SharedBooleanType)
                    ~g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef [current_g_tr_flag_id].
                        GlobalTransitionFlag_neg
               )
            {
                g_wdgm_cfg_ptr->DataGSRef->InternalFailureFlag = WDGM_INTERNAL_CP_TEST_NOK;
                /* Memory is corrupted and the value of the flag cannot be
                   trusted: return FALSE. */
                transition_flag = FALSE;
            }
        }

              /* Has the previous checkpoint started any global transitions? */
        if (  (prev_cp_started_g_tr_id > 0)
              /* WDGM247: Is there a transition between current and remembered
                 checkpoint of the previous entity? */
           && (g_tr_source_cp_id == previous_remembered_cpid)
              /* Coming from a local transition or coming from an active global
                 transition (if incoming global transition is not active then
                 no check is needed). */
           && (transition_flag == TRUE)
           )
        {
            prev_g_tr_flag = TRUE;

            while (prev_cp_started_g_tr_id > 0)
            {
                /* Get global transition flag ID. */
                g_tr_flag_id =
                    previous_checkpoint_ptr->WdgMStartedGlobalTransitionIds
                        [prev_cp_started_g_tr_id - 1];
                /* Read and check global transition flag for consistency. */
                transition_flag =
                    g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef [g_tr_flag_id].GlobalTransitionFlag;
                if ( transition_flag
                   != (WdgM_SharedBooleanType) ~g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef
                        [g_tr_flag_id].GlobalTransitionFlag_neg
                   )
                {
                    g_wdgm_cfg_ptr->DataGSRef->InternalFailureFlag = WDGM_INTERNAL_CP_TEST_NOK;
                    /* Memory is corrupted and the value of the flag cannot be
                       trusted: return FALSE. */
                    transition_flag = FALSE;
                }

                /* Clear global transition flag. */
                g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef [g_tr_flag_id].GlobalTransitionFlag
                    = (WdgM_SharedBooleanType)FALSE;
                g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef [g_tr_flag_id].GlobalTransitionFlag_neg
                    = (WdgM_SharedBooleanType)~FALSE;

                /* Global transition does not lead to the
                   currently checked checkpoint - local transition */
                if (g_tr_flag_id != current_g_tr_flag_id)
                {
                    /* Global transition not active */
                    if (transition_flag != TRUE)
                    {
                        /* Program Flow error - splitting of prgram flow! */
                        /* Program Flow took another global transition from the
                           previous checkpoint. */
                        current_entity_ptr->EntityStatusLRef->ProgramFlowViolationCnt++;
                    }
                }

                /* If at least one global transition flag is FALSE - another path
                   has already been taken - return FALSE! */
                prev_g_tr_flag = (WdgM_SharedBooleanType) (prev_g_tr_flag && transition_flag);

                prev_cp_started_g_tr_id--;
            }
        }
    }
    WdgM_GlobalRestoreInterrupts();

    return prev_g_tr_flag;
}

/* *****************************************************************************
 *  WdgM_WriteGlobalTransitionFlag()
 *   The read uses a negated value validation check. When the check shows
 *   a failure, the MCU_Reset is called.
 ******************************************************************************/
/* PRQA S 1503 4 */
FUNC (void, WDGM_CODE) WdgM_WriteGlobalTransitionFlag
    ( VAR (WdgM_TransitionIdType, AUTOMATIC) global_tr_id
    , VAR (WdgM_SharedBooleanType, AUTOMATIC) new_value
    )
{
    WdgM_GlobalSuspendInterrupts();
    g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef[global_tr_id].GlobalTransitionFlag = new_value;
    g_wdgm_cfg_ptr->GlobalTransitionFlagsGSRef[global_tr_id].GlobalTransitionFlag_neg =
       (WdgM_SharedBooleanType)~new_value;
    WdgM_GlobalRestoreInterrupts();

    return;
}
#endif /* (WDGM_GLOBAL_TRANSITIONS == STD_ON) */



/* *****************************************************************************
 *  FindTransitionId()
 *    For the current CP parse all the defined Incomming transitions
 *    and find the actual transition.
 *
 *    Return:
 *      Transition Id + 1  ... when transition found
 *      0                  ... when transition not found.
 ******************************************************************************/
STATIC FUNC (WdgM_TransitionIdType, WDGM_CODE) FindTransitionId
    ( P2CONST (WdgM_TransitionType, AUTOMATIC, WDGM_APPL_CONST) current_transition_ptr
    , VAR (WdgM_CheckpointIdType, AUTOMATIC) RememberedCheckpointId
    , VAR (WdgM_TransitionIdType, AUTOMATIC) nr_of_incomming_transitions
    )
{
    VAR (WdgM_TransitionIdType, AUTOMATIC) transition_id;

    while (nr_of_incomming_transitions > 0)
    {
        /* WDGM247: Is there Transition between current and remembered checkpoint? */
        if (  current_transition_ptr[nr_of_incomming_transitions-1].CheckpointSourceId
           == RememberedCheckpointId
           )
        {
            /* Transition found */
            break;
        }
        nr_of_incomming_transitions--;
    }
    transition_id = nr_of_incomming_transitions;

    return (transition_id);
}

/* *****************************************************************************
 *  ProgramFlowAndDeadlineMonitoring
 *    The function checks the actual global and local program flow against the
 *    configured one.
 *    It also checks actual local and global transitions times against the
 *    configured deadlines.
 ******************************************************************************/
STATIC FUNC (void, WDGM_CODE) ProgramFlowAndDeadlineMonitoring
    ( P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) current_entity_ptr
    , P2CONST (WdgM_CheckPointType, AUTOMATIC, WDGM_APPL_CONST) current_checkpoint_ptr
    , VAR (WdgM_CheckpointIdType, AUTOMATIC) CPID
    , VAR (WdgM_TimeBaseTickType, AUTOMATIC) current_tick_count
    , VAR (WdgM_CheckpointIdType, AUTOMATIC) RememberedCheckpointId
  #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
    , VAR (WdgM_SharedBooleanType, AUTOMATIC) global_activity
  #endif /* (WDGM_GLOBAL_TRANSITIONS == STD_ON) */
    )
{
    VAR (WdgM_TransitionIdType, AUTOMATIC) loc_trans_id;
    VAR (WdgM_TransitionIdType, AUTOMATIC) nr_of_trans;
    P2CONST (WdgM_TransitionType, AUTOMATIC, WDGM_APPLCONST) current_transition_ptr;
    VAR (boolean, AUTOMATIC) check_program_flow;
    VAR (WdgM_TimeBaseTickType, AUTOMATIC) curr_trans_time;
  #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
    P2CONST (WdgM_GlobalTransitionType, AUTOMATIC, WDGM_APPL_CONST)
        current_global_transition_ptr;
    P2CONST (WdgM_SupervisedEntityType, AUTOMATIC, WDGM_APPL_CONST) previous_entity_ptr;
    VAR (WdgM_TransitionIdType, AUTOMATIC) glob_trans_id;
    VAR (WdgM_BooleanParamType, AUTOMATIC) glob_init_first_time;
    VAR (WdgM_TransitionIdType, AUTOMATIC) nr_of_global_transitions;
    VAR (WdgM_SharedBooleanType, AUTOMATIC) g_tr_flag;
    VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) source_entity_id;

    glob_trans_id        = 0;
    glob_init_first_time = FALSE;
  #endif /* WDGM_GLOBAL_TRANSITIONS == STD_ON */

    loc_trans_id         = 0;
    check_program_flow   = current_entity_ptr->WdgMProgramFlowMonitoring;

    /* -----------------------------------------------------------------------
       WDGM273: Check the Global Activity Status
       Global Transitions have to be configured independently from the Local
       Transitions and only in the context of Program Flow Supervision. WDGM p.35
       ---------------------------------------------------------------------- */
  #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
    if (global_activity == FALSE)
    {
        /* *** First time run, global activity */

        if (  (g_wdgm_cfg_ptr->WdgMGlobInitialCheckpointId       == CPID)
           && (g_wdgm_cfg_ptr->WdgMGlobInitialEntityId
              == current_entity_ptr->WdgMSupervisedEntityId
              )
           )
        {
            /* GlobalAtivityFlag set to TRUE atomically before calling this
               function. */

            /* Set PF exception flag */
            glob_init_first_time = TRUE;
        }
        /* If a CP has incoming global transitions and no incoming local transitions
           and global activity flag is false => Error */
        else if (  (current_checkpoint_ptr->NrOfGlobalTransitions > 0)
                && (current_checkpoint_ptr->NrOfLocalTransitions == 0)
                /* "and check_program_flow == TRUE" is redundant, because
                   program flow is always set to TRUE by the code generator
                   if NrOfGlobalTransitions > 0! */
                )
        {
            /* Program Flow violation */
            current_entity_ptr->EntityStatusLRef->ProgramFlowViolationCnt++;
            /* Whether a transition straight to EXPIRED shall be made is checked
               in the main function according to the configured tolerance. */
        }
        else
        {
            /* MISRA rule 14.10 */
        }

        /* Clear global transition flags of all incoming global transitions. */
        ClearGlobalIncomingTrFlagsForCP (current_checkpoint_ptr);
    }
    else
    {
        /* *** Second and all next runs */

        /* Global Transition defined? */
        if (current_checkpoint_ptr->NrOfGlobalTransitions > 0)
        {
            current_global_transition_ptr = current_checkpoint_ptr->WdgMGlobalTransitionsRef;

            nr_of_global_transitions = current_checkpoint_ptr->NrOfGlobalTransitions;
            while (nr_of_global_transitions > 0)
            {
                /* Take the ID and a pointer to the defined source SE */
                source_entity_id =
                    current_global_transition_ptr [nr_of_global_transitions - 1u].EntitySourceId;
                previous_entity_ptr =
                    &g_wdgm_cfg_ptr->WdgMSupervisedEntityRef [source_entity_id];


                /* Check all outgoing global transitions of the previous checkpoint
                   - if one has been taken (global transiton flag is FALSE) then
                   at this point program flow splitting occurs - PF violation! */
                g_tr_flag = WdgM_ReadAndClearGlobalTransitionFlags
                    ( current_entity_ptr
                    , previous_entity_ptr
                    , current_global_transition_ptr [nr_of_global_transitions - 1u].
                        CheckpointSourceId
                    , current_global_transition_ptr [nr_of_global_transitions - 1u].
                        GlobalTransitionFlagId
                    , RememberedCheckpointId
                    );


                if (g_tr_flag == TRUE)
                {
                    /* Store value for program flow */
                    glob_trans_id = nr_of_global_transitions;
                    /* glob_trans_id is checked at the end of the function */

                    /* ------------------------------------------------------ */
                    /* ---------- CHECK GLOBAL TRANSITION DEADLINE ---------- */
                    /* Transition found - check its deadline */
                    /* Deadline defined? */
                    if ( current_global_transition_ptr [nr_of_global_transitions - 1u].
                            WdgMDeadlineMax > 0
                       )
                    {
                        /* Calculate the current transition time */
                        curr_trans_time =
                            current_tick_count - (previous_entity_ptr->EntityStatusLRef->
                                RememberedCheckpointTime);

                        /* WDGM202: Compare the current transition time with the cofigured time */
                        if (  (curr_trans_time > current_global_transition_ptr
                                [nr_of_global_transitions - 1u].WdgMDeadlineMax)
                           || (curr_trans_time < current_global_transition_ptr
                                [nr_of_global_transitions - 1u].WdgMDeadlineMin)
                           )
                        {
                            /* Current Global Transition time out of configured border */
                            current_entity_ptr->EntityStatusLRef->DeadlineViolationCnt++;
                        }
                    }
                    /* ------------------------------------------------------ */
                }

                nr_of_global_transitions--;
            }
        }
    }
  #endif /* WDGM_GLOBAL_TRANSITIONS == STD_ON */

    /* ----------------------------------------------------------------------
       WDGM271: Check the Local Activity Status
       ---------------------------------------------------------------------- */
    if (  (current_entity_ptr->EntityStatusLRef->LocalActivityFlag == FALSE)
       && (check_program_flow == TRUE)
       )
    {
        /* *** First time run, local activity */
        /* WDGM251: */
        if (current_entity_ptr->WdgMCheckpointLocInitialId == CPID)
        {
            current_entity_ptr->EntityStatusLRef->LocalActivityFlag = TRUE;

            #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
            /* Set aperiodic status in case of an error */
            if (  (glob_trans_id == 0)
               && (current_checkpoint_ptr->NrOfGlobalTransitions > 0)
               && (glob_init_first_time == FALSE)
               )
            {
                /* Program Flow error */
                current_entity_ptr->EntityStatusLRef->ProgramFlowViolationCnt++;
                /* Whether a transition straight to EXPIRED shall be made is checked
                   in the main function according to the configured tolerance. */
            }
            #endif /* WDGM_GLOBAL_TRANSITIONS == STD_ON */
        }
        else
        {
            /* First run but no Local Initial CP => ERROR */
            current_entity_ptr->EntityStatusLRef->ProgramFlowViolationCnt++;
            /* Whether a transition straight to EXPIRED shall be made is checked
               in the main function according to the configured tolerance. */
        }
    }
    else
    {
        /* *** Entity second and all next runs, if passed by a start CP */

        /* Local Transition defined? */
        nr_of_trans = current_checkpoint_ptr->NrOfLocalTransitions;
        if (nr_of_trans != 0)
        { /* Local Incomming Transition defined, Global not found */
            /* Build pointer to Local Incomming Transitions */
            current_transition_ptr = current_checkpoint_ptr->WdgMLocalTransitionRef;
            loc_trans_id = FindTransitionId
                                ( current_transition_ptr
                                , RememberedCheckpointId
                                , nr_of_trans
                                );
            /* loc_trans_id == 0 means that no transition has been found */

            if (loc_trans_id > 0)
            {
                /* ---------------------------------------------------------- */
                /* ------------- CHECK LOCAL TRANSITION DEADLINE ------------ */
                /* To check Deadline we need to know whether the Transition time was
                   in the config defined (not specified in WDGM) */

                /* Deadline defined? */
                if (current_transition_ptr [loc_trans_id - 1].WdgMDeadlineMax > 0)
                {
                    /* Calculate the current transition time */
                    curr_trans_time =
                        current_tick_count -
                            (current_entity_ptr->EntityStatusLRef->RememberedCheckpointTime);

                    /* WDGM202: Compare the current transition time with the cofigured time */
                    if (  (curr_trans_time > current_transition_ptr
                            [loc_trans_id - 1u].WdgMDeadlineMax)
                       || (curr_trans_time < current_transition_ptr
                            [loc_trans_id - 1u].WdgMDeadlineMin)
                       )
                    {
                        /* Current Transition time out of configured border */
                        current_entity_ptr->EntityStatusLRef->DeadlineViolationCnt++;
                    }
                        /* WDGM231: When the Deadline transition end point is not called.
                           Then the check need to be done inside the cyclic MainFunction()! */
                }
                /* ---------------------------------------------------------- */

                #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
                /* Check for program flow splitting. */

                /* Check all outgoing global transitions of the previous checkpoint
                   - if one has been taken (global transiton flag is FALSE) then
                   at this point program flow splitting occurs - PF violation! */
                (void) WdgM_ReadAndClearGlobalTransitionFlags
                    ( current_entity_ptr
                    , current_entity_ptr /* coming from a local transition */
                    , RememberedCheckpointId
                    , WDGM_INVALID_TR_ID /* coming from a local transition */
                    , RememberedCheckpointId
                    );
                #endif /* WDGM_GLOBAL_TRANSITIONS == STD_ON */
            }

        }

        /* Set aperiodic status in case of an error */
        if (  (loc_trans_id == 0)
         #if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
           && (glob_trans_id == 0)
         #endif /* WDGM_GLOBAL_TRANSITIONS == STD_ON */
           && (check_program_flow == TRUE)
           )
        {
            /* Program Flow error */
            current_entity_ptr->EntityStatusLRef->ProgramFlowViolationCnt++;
            /* Whether a transition straight to EXPIRED shall be made is checked
               in the main function according to the configured tolerance. */
        }
    }   /* if LocalActivityFlag is TRUE */

    /* If a terminating check point (end check point) then reset activity status */
    /* Note, that a start checkpoint could be an end check point as well! */
    if (  (current_checkpoint_ptr->WdgMIsEndCheckpoint == TRUE)
       && (check_program_flow == TRUE)
       )
    {
        current_entity_ptr->EntityStatusLRef->LocalActivityFlag = FALSE;
    }
}

/* *****************************************************************************
 *  ClearGlobalIncomingTrFlagsForCP
 *    Clears global transition flags for all global incoming transitions of
 *    the provided checkpoint.
 *    Note: the global transition flags are not needed any more (already read)
 *    when this function is called.
 ******************************************************************************/
#if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
STATIC FUNC (void, WDGM_CODE) ClearGlobalIncomingTrFlagsForCP
    (P2CONST (WdgM_CheckPointType, AUTOMATIC, WDGM_APPL_CONST) current_checkpoint_ptr)
{
    P2CONST (WdgM_GlobalTransitionType, AUTOMATIC, WDGM_APPL_CONST) global_transitions_ptr;
    VAR (WdgM_TransitionIdType, AUTOMATIC) nr_of_global_transitions;

    /* Clear global transition flags for all GLOBAL INCOMING TRANSITIONS */
    /* Note: the flags have already been checked in previous local functions
       checking deadline and program flow. */
    global_transitions_ptr = current_checkpoint_ptr->WdgMGlobalTransitionsRef;

    nr_of_global_transitions = current_checkpoint_ptr->NrOfGlobalTransitions;
    while (nr_of_global_transitions > 0)
    {
        /* Clear global transition flags for this GLOBAL INCOMING TRANSITION */
        (void) WdgM_ReadGlobalTransitionFlag
            (global_transitions_ptr[nr_of_global_transitions-1].GlobalTransitionFlagId, TRUE);

        nr_of_global_transitions--;
    }
}
#endif /* WDGM_GLOBAL_TRANSITIONS == STD_ON */

#define WDGM_STOP_SEC_CODE
#include "MemMap.h"         /* PRQA S 5087 */
