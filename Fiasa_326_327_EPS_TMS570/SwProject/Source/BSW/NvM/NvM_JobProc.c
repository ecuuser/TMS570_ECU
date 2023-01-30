/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2010 by Vector Informatik GmbH.                                                  All rights reserved.
 * 
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NvM_JobProc.c
 *      Project:  MemService_AsrNvM
 *       Module:  NvM - Submodule JobProc (Job Processing)
 *    Generator:  -
 *
 *  Description:  This sub-module implements the FSM for the NVM, including the state
 *                description table.
 *  
 *********************************************************************************************************************/

/* Do not modify this file! */

/**********************************************************************************************************************
 *  MODULE SWITCH
 *********************************************************************************************************************/
#define NVM_IMPLEMENTATION

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  INCLUDE OF CONFIGURATION (ALL SECTIONS)
 *********************************************************************************************************************/
#include "NvM_Cfg.h"
#include "NvM_PrivateCfg.h"
/**********************************************************************************************************************
 *  MODULE HEADER INCLUDES
 *********************************************************************************************************************/
#include "NvM_JobProc.h"

/**********************************************************************************************************************
 *  INCLUDE OF THE ACTIONS AND QUERIES
 *********************************************************************************************************************/
#include "NvM_Act.h"
#include "NvM_Qry.h"

/**********************************************************************************************************************
 *  TARGET AND COMPILER
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (     (NVM_JOBPROC_MAJOR_VERSION != (3u)) \
       || (NVM_JOBPROC_MINOR_VERSION != (7u)))
  #error "Version numbers of NvM_JobProc.c and NvM_JobProc.h are inconsistent!"
#endif

#if (     (NVM_CFG_MAJOR_VERSION != (3u)) \
       || (NVM_CFG_MINOR_VERSION != (7u)))
  #error "Version numbers of NvM_JobProc.c and NvM_Cfg.h are inconsistent!"
#endif

#if (     (NVM_ACT_MAJOR_VERSION != (3u)) \
       || (NVM_ACT_MINOR_VERSION != (7u)))
  #error "Version numbers of NvM_JobProc.c and NvM_Act.h are inconsistent!"
#endif

#if (     (NVM_QRY_MAJOR_VERSION != (3u)) \
       || (NVM_QRY_MINOR_VERSION != (7u)))
  #error "Version numbers of NvM_JobProc.c and NvM_Qry.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  IDENTIFICATION
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  DATE AND TIME
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  INTERNAL DEFINES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  INTERNAL MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  INTERNAL TYPE DEFINITIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  INTERNAL STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  INTERNAL FORWARD DECLARATIONS
 **********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

    STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_FsmQuery(NvM_StateQueryPtrType);
    STATIC FUNC(void, NVM_PRIVATE_CODE)    NvM_FsmAction(NvM_StateChangeActionsPtrType);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *  INTERNAL MODULE GLOBAL VARIABLES
 *********************************************************************************************************************/

#define NVM_START_SEC_VAR_FAST_8BIT
#include "MemMap.h"

   /* at least for development mode (where the following two state types are enums) the 
    * compiler is expected to ensure correct alignment, regardless of any given section alignment.
    * The state variables are used quite frequently (but never via pointers)
    */
   VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobMainState_t;
   VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobSubState_t;

#define NVM_STOP_SEC_VAR_FAST_8BIT
#include "MemMap.h"

#define NVM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

   /* state of the task state machine */
   VAR(NvM_StateType, NVM_PRIVATE_DATA) NvM_TaskState_t = NVM_STATE_UNINIT;

#define NVM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

    VAR(NvM_BlockInfoType, NVM_PRIVATE_DATA) NvM_CurrentBlockInfo_t;

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define NVM_NO_OF_SERVICES (NVM_INT_FID_NO_JOB_PENDING + 1u)

/* Internal job descriptor table */
CONST(NvM_IntServiceDescrType, NVM_PRIVATE_CONST) NvM_IntServiceDescrTable_at[NVM_NO_OF_SERVICES] =
{
    /* NVM_INT_FID_WRITE_BLOCK */
    {
        NVM_ACT_ID_InitWriteBlock, NVM_STATE_WRITE_INITIAL, NVM_WRITE_BLOCK
    },

    /* NVM_INT_FID_READ_BLOCK */
    {
        NVM_ACT_ID_ReadNvBlock, NVM_STATE_READ_READ_DATA, NVM_READ_BLOCK
    },

    /* NVM_INT_FID_RESTORE_DEFAULTS */
    {
        NVM_ACT_ID_InitRestoreBlockDefaults, NVM_STATE_FSM_FINISHED, NVM_RESTORE_BLOCK_DEFAULTS
    },

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    /* NVM_INT_FID_INVALIDATE_NV_BLOCK */
    {
        NVM_ACT_ID_InvalidateNvBlock, NVM_STATE_INVALIDATING_BLOCK, NVM_INVALIDATE_NV_BLOCK
    },

    /* NVM_INT_FID_ERASE_BLOCK */
    {
        NVM_ACT_ID_EraseNvBlock, NVM_STATE_ERASE_ERASE_BLOCK, NVM_ERASE_BLOCK
    },
#else
    /* NVM_INT_FID_INVALIDATE_NV_BLOCK */
    {
        NVM_ACT_ID_Nop, NVM_STATE_FSM_FINISHED, NVM_INVALIDATE_NV_BLOCK
    },

    /* NVM_INT_FID_ERASE_BLOCK */
    {
        NVM_ACT_ID_Nop, NVM_STATE_FSM_FINISHED, NVM_ERASE_BLOCK
    },
#endif
    /* NVM_INT_FID_WRITE_ALL */
    {
        NVM_ACT_ID_InitWriteAll, NVM_STATE_WRITEALL_PROC_BLOCK, NVM_WRITE_ALL
    },

    /* NVM_INT_FID_READ_ALL */
    {
        NVM_ACT_ID_InitReadAll, NVM_STATE_READALL_PROC_CONFIG_ID, NVM_READ_ALL
    },
    /* NVM_INT_FID_NO_JOB_PENDING */
    {
        NVM_ACT_ID_Nop, NVM_STATE_FSM_FINISHED, NVM_MAINFUNCTION
    }
};


/* these macros shall increase the readability of the State Descriptor Table */
#define NVM_STATE_IF
#define NVM_STATE_ELSEIF
#define NVM_STATE_THEN
#define NVM_STATE_ELSE
#define NVM_NEXT_STATE(state) (state)

/**********************************************************************************************************************
 *  STATE DESCRIPTOR TABLE
 *********************************************************************************************************************/
STATIC CONST(NvM_StateDescrType, NVM_PRIVATE_CONST) NvM_StateDescrTable_at[] =
{
    /* NVM_STATE_UNINIT
     * if the TASK runs when the NVM is not initialized yet, use Wait Action to remain in UNINIT state.
     * This state can only be left through a call to NvM_Init by ECU state manager
     */
    {
        {
            /* Exit 1 */
            {
                NVM_STATE_IF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_UNINIT)
            },
            /* Exit 2 */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_UNINIT)
            },
            /* Exit 3 */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_UNINIT)
            }
        },
        /* final case */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
            NVM_NEXT_STATE(NVM_STATE_UNINIT)
        }
    },
#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_1)
    /* NVM_STATE_IDLE */
    /* in API config class 1, we only have to wait for a multi block job
     * ReadAll or WriteAll */
    {
        {
            /* Exit 1, Multi block job found */
            {
                NVM_STATE_IF{NVM_QRY_ID_MULTI_BLK_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetMultiBlockJob,
                                   NVM_ACT_ID_InitMainFsm},
#if (NVM_KILL_WRITEALL_API == STD_ON)
                   NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
#else
                   NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
#endif
            },
            /* Exit 2, no job found */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait,
                                   NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },
            /* Exit 3, not used, repeat previous */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait,
                                   NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
        /* final case, not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#elif(NVM_JOB_PRIORISATION == STD_ON)
    /* NVM_STATE_IDLE */
    /* Scan job lists, if no job was found: wait */
    {
        {
            /* Exit 1, Hi Prio Job found */
            {
                NVM_STATE_IF{NVM_QRY_ID_HI_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetHighPrioJob,
                                   NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
            },
            /* Exit 2, Normal prio job found */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_NORMAL_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetNormalPrioJob,
                                   NVM_ACT_ID_InitMainFsm},
                   NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },
            /* Exit 3, Multi block job found */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_MULTI_BLK_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetMultiBlockJob,
                                   NVM_ACT_ID_InitMainFsm},
#if (NVM_KILL_WRITEALL_API == STD_ON)
                   NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
#else
                   NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
#endif
            }
        },
        /* final case, no job found */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#else /* STD_OFF == NVM_JOB_PRIORISATION */
    /* NVM_STATE_IDLE */
    /* Scan job lists, if no job was found: wait */
    {
        {
            /* Exit 1, Single block job found */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_NORMAL_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetNormalPrioJob,
                                   NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },
            /* Exit 2, Multi block job found */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_MULTI_BLK_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetMultiBlockJob,
                                   NVM_ACT_ID_InitMainFsm},
#if (NVM_KILL_WRITEALL_API == STD_ON)
                   NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
#else
                   NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
#endif
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait,
                                   NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },

        /* final case, not uused, repeat */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#endif /* IDLE_STATE, depending on NVM_API_CONFIG_CLASS and NVM_JOB_PRIORISATION */

#if ((NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) && (STD_ON == NVM_JOB_PRIORISATION))
    /* NVM_STATE_HIGH_PRIO_JOB */
    /* High prio WriteJob/not cancelable */
    {
        {
            {   /* main job fsm still running */
                NVM_STATE_IF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
            },
            {   /* main job fsm finished */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },
            {   /* error fallthrough */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
        /* final case */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#endif

#if ((NVM_JOB_PRIORISATION == STD_ON) && (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1))
    /* NVM_STATE_NORMAL_PRIO_JOB */
    /* cancelable, all "NOT HighPrioWrite" jobs */
    {
        {
            {   /* low prio job running or finished, immediate job occoured */
                NVM_STATE_IF{NVM_QRY_ID_HI_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetHighPrioJob, NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
            },
            {   /* continue with the running job */
                NVM_STATE_ELSEIF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },
            {   /* job fsm finished */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_QueueFreeLastJob},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
        /* final case, not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#else
    /* NVM_STATE_NORMAL_PRIO_JOB */
    /* not cancelable as there are no hi prio jobs,
     * jobs do not need to be freed after processing */  
    {
        {
            {   /* continue the running job */
                NVM_STATE_IF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },
            {   /* job finished */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },
            {   /* not used */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishReadBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },

#endif
#if (NVM_KILL_WRITEALL_API == STD_ON)
       /* NVM_STATE_MULTI_BLOCK_JOB */
#   if ((NVM_JOB_PRIORISATION == STD_ON) && (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1))
    /* NVM_STATE_NORMAL_PRIO_JOB */
    /* cancelable, all "NOT HighPrioWrite" jobs */
    {
        {
            {   /* WriteAll, but it was killed => Finish FSM, even if a high prio job might be waiting 
                   It would be next job in "normal" processing - from IDLE */
                NVM_STATE_IF{NVM_QR_ID_WRITEALL_KILLED, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_KillWritAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },
            {   /* low prio job running or finished, immediate job occoured */
                NVM_STATE_ELSEIF{NVM_QRY_ID_HI_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetHighPrioJob, NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
            },
            {   /* continue with the running job */
                NVM_STATE_ELSEIF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
            }
        },
        /* final case: job fsm finished */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#   else
    /* not cancelable as there are no hi prio jobs,
     * jobs do not need to be freed after processing */  
    {
        {
            {   /* WriteAll, but it was killed => Finish FSM, even if a high prio job might be waiting 
                   It would be next job in "normal" processing - from IDLE */
                NVM_STATE_IF{NVM_QR_ID_WRITEALL_KILLED, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_KillWritAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },
            {   /* continue the running job */
                NVM_STATE_ELSEIF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
            },
            {   /* job finished */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#   endif /* Job prioritization */
#endif /* NVM_KILL_WRITEALL_API */
    /* ----------------- Read Block states ------------------------------- */
    /* NVM_STATE_READ_READ_DATA */
    {
        {
            {
                /* nv busy */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READ_READ_DATA)
            },
            {
                /* ready, ok, crc */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_CRC_BUSY},
                NVM_STATE_THEN{NVM_ACT_ID_ProcessCrcRead, NVM_ACT_ID_Wait},
                NVM_NEXT_STATE(NVM_STATE_READ_CMP_CRC)
            },
            {
                /* ready, ok, no crc */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_ValidateRam, NVM_ACT_ID_FinishReadBlock},
                NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }

        },
        {
            /* ready, not ok */
            NVM_STATE_ELSE{NVM_ACT_ID_Nop,  NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READ_IMPL_RECOV)
        }
    },
    /* NVM_STATE_READ_CMP_CRC */
    /* read state and crc */
    {
        {
            {
                /* crc not ready */
                NVM_STATE_IF{NVM_QRY_ID_CRC_BUSY, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_ProcessCrcRead, NVM_ACT_ID_Wait},
                NVM_NEXT_STATE(NVM_STATE_READ_CMP_CRC)
            },
            {
                /* ready match */
                NVM_STATE_ELSEIF{NVM_QRY_ID_CRC_MATCH, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_ValidateRam, NVM_ACT_ID_FinishReadBlock},
                NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                /* ready mismatch */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetReqIntegrityFailed, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READ_IMPL_RECOV)
            }
        },
        {   /* finally... ... not used. */
            NVM_STATE_ELSE{NVM_ACT_ID_SetReqIntegrityFailed, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
    /* NVM_STATE_READ_IMPL_RECOV */
    {
        {
            {
                /* Redundant block? -> read redundant nv */
                NVM_STATE_IF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant, NVM_ACT_ID_ReadNvBlock},
                NVM_NEXT_STATE(NVM_STATE_READ_READ_DATA)
            },
            {
                /* not redundant, try the ROM defaults */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_RestoreRomDefaults, NVM_ACT_ID_FinishReadBlock},
                NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                /* not used */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_RestoreRomDefaults, NVM_ACT_ID_FinishReadBlock},
                NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        {   /* not used */
            NVM_STATE_THEN{NVM_ACT_ID_RestoreRomDefaults, NVM_ACT_ID_FinishReadBlock},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },

    /* ------------------ write block states --------------------------- */
    /* NVM_STATE_WRITE_INITIAL = initial state of Write Block */
    {
        {
            {   /* crc is busy (even if no crc was configured) -> copy NvData to buffer (and calculate CRC)*/
                NVM_STATE_IF{NVM_QRY_ID_CRC_BUSY, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_CopyNvDataToBuf, NVM_ACT_ID_Wait},
                NVM_NEXT_STATE(NVM_STATE_WRITE_INITIAL)
            },
            {   /* no crc or crc ready -> test primary NvBlock, if necessary */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_PRI_READ)
            },
            {   /* crc ready -> not used */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_PRI_READ)
            }
        },
        {   /* not used */
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
    /* NVM_STATE_WRITE_TEST_PRI_READ */
    {
        {
            {   /* read of primary NvBlock not finished -> wait */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_PRI_READ)
            },
            {   /* result of primary NvBlock OK -> test secondary NvBlock */
                NVM_STATE_IF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_LAST_RESULT_OK},
                NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_TestBlockBlank},
                NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_SEC_READ)
            },
            {   /* result of primary NvBlock not OK -> write primary NvBlock first */
                NVM_STATE_ELSEIF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
            }
        },
        {   /* not a redundant Block */
            NVM_STATE_ELSE{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
        }
    },
    /* NVM_STATE_WRITE_TEST_SEC_READ */
    {
        {
            {   /* read of secondary NvBlock not finished -> wait */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_SEC_READ)
            },
            {   /* result of secondary NvBlock OK -> write primary NvBlock first */
                NVM_STATE_IF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_WriteNvBlock},
                NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
            },
            {   /* result of secondary NvBlock not OK -> write secondary NvBlock first */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
            }
        },
        {   /* not used */
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },

    /* NVM_STATE_WRITE_WR_DATA_CRC_1 */
    {
        {
            {   /* nv write not finished -> wait */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
            },
            {   /* result ok -> write other NvBlock */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_WriteNvBlock},
                NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
            },
            {   /* result not ok, write retries exceeded -> write other NvBlock */
                NVM_STATE_ELSEIF{NVM_QRY_ID_WRITE_RETRIES_EXCEEDED, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_WriteNvBlock},
                NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
            }
        },
        {   /* result not ok -> retry */
            NVM_STATE_ELSE{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
        }
    },
    /* NVM_STATE_WRITE_WR_DATA_CRC_2 */
    {
        {
            {   /* nv write not finished -> wait */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
            },
            {   /* result ok -> update NvState and finish block */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishWriteBlock},
                NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* result not ok, retries exceeded -> update NvState and finish block */
                NVM_STATE_ELSEIF{NVM_QRY_ID_WRITE_RETRIES_EXCEEDED, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishWriteBlock},
                NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        {   /* result not ok -> retry */
            NVM_STATE_ELSE{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
        }
    },    
#if(NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    /* ------------------ Invalidate Block states -------------------------- */
    /* NVM_STATE_INVALIDATING_BLOCK */
    {
        {
            {   /* nv busy -> wait; if not busy LastResult is set */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_INVALIDATING_BLOCK)
            },
            {   /* nv ready, result okay, redundant -> invalidate redundant*/
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_REDUNDANT_BLOCK},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant, NVM_ACT_ID_InvalidateNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_INVALIDATING_BLOCK)
            },
            {   /* nv ready and (not redundant or result not ok) -> finish; result is already set */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
    /* --------------------- Erase Block states -------------------------- */
    /* NVM_STATE_ERASE_ERASE_BLOCK */
    {
        {
            {   /* nv busy -> wait */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_ERASE_ERASE_BLOCK)
            },
            {   /* nv ready, result ok, redundant -> erase redundant*/
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_REDUNDANT_BLOCK},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant,NVM_ACT_ID_EraseNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_ERASE_ERASE_BLOCK)
            },
            {   /* nv ready, not redundant or result nok -> finish (LastResult was previously set) */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
#endif
    /* --------------------- Restore Block Defaults states ----------------- */

    /* no states necesary --> the only transition goes implicitly from
     *  NVM_STATE_FSM_FINISHED to NVM_STATE_FSM_FINSIHED */


    /* ------------------ Readall states --------------------------- */
    /* NVM_STATE_READALL_PROC_CONFIG_ID = analyse Config NV Block */
    {
        {
            {   /* sub fsm still running? */
                NVM_STATE_IF{NVM_QRY_ID_SUB_FSM_RUNNING, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READALL_PROC_CONFIG_ID)
            },
            {   /* sub fsm read finished */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_FinishCfgIdCheck, NVM_ACT_ID_InitNextBlockReadAll},
                NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_FinishCfgIdCheck, NVM_ACT_ID_InitNextBlockReadAll},
                NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishCfgIdCheck, NVM_ACT_ID_InitNextBlockReadAll},
            NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
        }
    },

#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    /* NVM_STATE_READALL_PROC_RAM_BLOCK = analyse Ram Block */
    {
        {
            {   /* last block finished -> end read all */
                NVM_STATE_IF{NVM_QRY_ID_LAST_BLOCK_DONE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* last block not finished, check valid/crc
                   => if the block does not have CRC, this transition will never be taken, because CRC won't be busy */
                NVM_STATE_ELSEIF{NVM_QRY_ID_RAM_VALID, NVM_QRY_ID_CRC_BUSY},
                NVM_STATE_THEN{NVM_ACT_ID_ProcessCrc, NVM_ACT_ID_Wait},
                NVM_NEXT_STATE(NVM_STATE_READALL_CHK_RAM_VALIDITY)
            },
            {   /* not valid or no crc */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READALL_CHK_EXT_RUNTIME)
            }
        },
        {   /* not used */
            NVM_STATE_ELSE{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_CHK_EXT_RUNTIME)
        }
    },
#else
    /* NVM_STATE_READALL_PROC_RAM_BLOCK = analyse Ram Block */
    {
        {
            {   /* last block finished -> end read all */
                NVM_STATE_IF{NVM_QRY_ID_LAST_BLOCK_DONE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* last block not finished, we don't check the block's validity */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READALL_CHK_EXT_RUNTIME)
            },
            {   /* not used */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READALL_CHK_EXT_RUNTIME)
            }
        },
        {   /* not used */
            NVM_STATE_ELSE{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_CHK_EXT_RUNTIME)
        }
    },
#endif

#if(NVM_DYNAMIC_CONFIGURATION == STD_ON)
    /* NVM_STATE_READALL_CHK_EXT_RUNTIME: */
    {
        {
            {   
                NVM_STATE_IF{NVM_QRY_ID_SKIP_BLOCK, NVM_QRY_ID_WRITE_BLOCK_ONCE},
                NVM_STATE_THEN{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_TestBlockBlank},
                NVM_NEXT_STATE(NVM_STATE_READALL_WR_ONCE_PROT)
            },
            {   
                NVM_STATE_ELSEIF{NVM_QRY_ID_SKIP_BLOCK, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_InitNextBlockReadAll},
                NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_EXT_RUNTIME, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_RestoreRomDefaults, NVM_ACT_ID_InitNextBlockReadAll},
                NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_InitReadBlockFsm, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_READ_NV)
        }
    },
#else
    /* NVM_STATE_READALL_CHK_EXT_RUNTIME: */
    {
        {
            {   
                NVM_STATE_IF{NVM_QRY_ID_SKIP_BLOCK, NVM_QRY_ID_WRITE_BLOCK_ONCE},
                NVM_STATE_THEN{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_TestBlockBlank},
                NVM_NEXT_STATE(NVM_STATE_READALL_WR_ONCE_PROT)
            },
            {   
                NVM_STATE_ELSEIF{NVM_QRY_ID_SKIP_BLOCK, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_InitNextBlockReadAll},
                NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_InitReadBlockFsm, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READALL_READ_NV)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_InitReadBlockFsm, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_READ_NV)
        }
    },
#endif /* #if(NVM_DYNAMIC_CONFIGURATION == STD_ON) */
    /* NVM_STATE_READALL_WR_ONCE_PROT: a write once block shall be skipped */
    {
        {
            {   /* one byte was read - wait for MemHwA to finish this read job */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READALL_WR_ONCE_PROT)
            },
            {   /* byte was read - result was ok --> next block, please */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_FinishReadBlock,NVM_ACT_ID_InitNextBlockReadAll},
                NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {   /* result nok, redundant -> try redundant */
                NVM_STATE_ELSEIF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant, NVM_ACT_ID_TestBlockBlank},
                NVM_NEXT_STATE(NVM_STATE_READALL_WR_ONCE_PROT)
            }
        },
        {   /* not redundant or done, result nok. */
            NVM_STATE_ELSE{NVM_ACT_ID_FinishReadBlock, NVM_ACT_ID_InitNextBlockReadAll},
            NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
        }
    },
#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    /* NVM_STATE_READALL_CHK_RAM_VALIDITY = analyse Ram Block */
    {
        {
            {   /* Crc not ready -> Wait */
                NVM_STATE_IF{NVM_QRY_ID_CRC_BUSY, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_ProcessCrc, NVM_ACT_ID_Wait},
                NVM_NEXT_STATE(NVM_STATE_READALL_CHK_RAM_VALIDITY)
            },
            {   /* crc ready, crc match -> finish block and use current attributes */
                NVM_STATE_ELSEIF{NVM_QRY_ID_CRC_MATCH, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {   /* crc mismatch */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READALL_CHK_EXT_RUNTIME)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_CHK_EXT_RUNTIME)
        }
    },
#endif

    /* NVM_STATE_READALL_READ_NV */
    {
        {
            {   /* read in process -> do nothing */
                NVM_STATE_IF{NVM_QRY_ID_SUB_FSM_RUNNING, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READALL_READ_NV)
            },
            {   /* sub fsm finished */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
        }
    },
    /* ------------------ writeall block states ------------------------------ */
    /* NVM_STATE_WRITEALL_PROC_BLOCK */
    {
        {
            {   /* write all cancled ->finish */
                NVM_STATE_IF{NVM_QRY_ID_CANCEL_WRITE_ALL, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },

            {   /* last block done  */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_BLOCK_DONE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITEALL_WAIT_MEMHWA)
            },
            {    /* not cancled, not last block done */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitBlock, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITEALL_CHECK_SKIP)
            }
        },
        {   /* transition not used */
            NVM_STATE_ELSE{NVM_ACT_ID_InitBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITEALL_CHECK_SKIP)
        }
    },
    /* NVM_STATE_WRITEALL_CHECK_SKIP */
    {
        {
            {   /* block shall be written during write all */
                NVM_STATE_IF{NVM_QRY_ID_BLK_WRITE_ALL, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_InitWriteBlockFsm, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITEALL_WRITE_FSM)
            },
            {   /* skip block */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_FinishBlock},
                NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_FinishBlock},
                NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_FinishBlock},
            NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
        }
    },
    /* NVM_STATE_WRITEALL_WRITE_FSM */
    {
        {
            {   /* write fsm still runnin - do nothing */
                NVM_STATE_IF{NVM_QRY_ID_SUB_FSM_RUNNING, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITEALL_WRITE_FSM)
            },
            {   /* fsm finished - handle next block */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_FinishBlock, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_FinishBlock, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
            }
        },
        { /* transition not used */
            NVM_STATE_THEN{NVM_ACT_ID_FinishBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
        }
    },
    /* NVM_STATE_WRITEALL_WAIT_MEMHWA */
    {
        {
            {   /* write all cancelled */
                NVM_STATE_IF{NVM_QRY_ID_CANCEL_WRITE_ALL, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* MemHwA is still busy  */
                NVM_STATE_ELSEIF{NVM_QRY_ID_MEMHWA_BUSY, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_WRITEALL_WAIT_MEMHWA)
            },
            {   /* MemHwA is completly IDLE */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        { /* transition not used */
            NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },

    /* NVM_STATE_FSM_FINISHED */
    /* always stay in this state. Only by re-initialising a FSM exits this state */
    {
        {
            /* Exit 1 */
            {
                NVM_STATE_IF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            /* Exit 2 */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            /* Exit 3 */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        /* final case */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    }
 };

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*= Implementation ======================================================== */

#define NVM_START_SEC_CODE
#include "MemMap.h"

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_JobProcInit()
!
!-----------------------------------------------------------------------------
!   Function initializes the variables of the submodule
!
!-----------------------------------------------------------------------------
!   Parameter:      none
!   Returnvalue:    none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PRIVATE_CODE) NvM_JobProcInit(void)
{
    NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_NO_JOB_PENDING;

    NvM_CurrentBlockInfo_t.InternalFlags_u8 = 0;

    NvM_JobMainState_t = NVM_STATE_FSM_FINISHED;
    NvM_JobSubState_t  = NVM_STATE_FSM_FINISHED;
    NvM_TaskState_t    = NVM_STATE_IDLE;
}


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_Fsm()
!
!-----------------------------------------------------------------------------
!   Function Description: This function executes exactly one State of a state
!   machine: e.g. the initial state of the State Machine for ReadBlock. This
!   initial state contains four exits. Which exit is taken depends on the querys
!   which in turn lead to the actions. At last the next state is stored. The
!   next time the function is called, it executes this next state.
!   This function is called from NvM_Mainfunction() which is called
!   cyclically by an Application (or event-driven when NVM is an ECC Task).
!
!-----------------------------------------------------------------------------
!   Parameter:     NvM_CurrentState_t           denotes the current state
!   Returnvalue:   the new state
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(NvM_StateType, NVM_PRIVATE_CODE) NvM_Fsm(NvM_StateType NvM_CurrentState_t)
{
    /* local variables */
    NvM_StateType NvM_RetState_tloc;
    NvM_StateChangeActionsPtrType ChangeActions_ptloc;
    CONSTP2CONST(NvM_StateDescrType, AUTOMATIC, NVM_PRIVATE_CONST) CurrentState_ptloc =
        &NvM_StateDescrTable_at[NvM_CurrentState_t];

    /* Execute the first query, if it is fulfilled then do the corresponding
     * action and return with the next state to NvM_MainFunction(). If the first
     * query is not true then execute next query as long as the right exit is found.
     */
    #if (3u == NVM_MAX_NUM_OF_STATE_CONDITIONS)
        if(NvM_FsmQuery(CurrentState_ptloc->ChangeConditions_at[0].Queries_at))
        {
            NvM_RetState_tloc = CurrentState_ptloc->ChangeConditions_at[0].NextState_t;
            ChangeActions_ptloc = &CurrentState_ptloc->ChangeConditions_at[0].Actions_t;
        }
        else if (NvM_FsmQuery(CurrentState_ptloc->ChangeConditions_at[1].Queries_at))
        {
            NvM_RetState_tloc = CurrentState_ptloc->ChangeConditions_at[1].NextState_t;
            ChangeActions_ptloc = &CurrentState_ptloc->ChangeConditions_at[1].Actions_t;
        }
        else if (NvM_FsmQuery(CurrentState_ptloc->ChangeConditions_at[2].Queries_at))
        {
            NvM_RetState_tloc = CurrentState_ptloc->ChangeConditions_at[2].NextState_t;
            ChangeActions_ptloc = &CurrentState_ptloc->ChangeConditions_at[2].Actions_t;
        }
        else
        {
            NvM_RetState_tloc = CurrentState_ptloc->FinalCondition_t.NextState_t;
            ChangeActions_ptloc = &CurrentState_ptloc->FinalCondition_t.Actions_t;
        }
    #else
        #error "Only case '3 conditions (4 state exits)' is implemented"
    #endif

    NvM_FsmAction(ChangeActions_ptloc);

    return NvM_RetState_tloc;
}


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_FsmQuery()
!
!-----------------------------------------------------------------------------
!   Function Description: Process a State machine query (logical AND)
!
!-----------------------------------------------------------------------------
!   Parameter:     NvM_Queries_at the Queries to be ANDed together
!   Returnvalue:   the new state
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_FsmQuery(NvM_StateQueryPtrType NvM_Queries_at)
{
    #if (2u == NVM_MAX_NUM_OF_QRY_AND)
        /* Currently there are Queryies with side-effects, forcing
         * execution in the defined order
         */

        boolean retVal = NvM_QueryTable_ap[NvM_Queries_at[0u]]();

        if (retVal)
        {
            retVal = NvM_QueryTable_ap[NvM_Queries_at[1u]]();
        }

        return retVal;
    #else
     #error "Currently two AND-associated queries per state exit are supported"
    #endif
} /* end NvM_FsmQuery */


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_FsmAction()
!
!-----------------------------------------------------------------------------
!   Function Description: Process a State change --> perform the
!                         defined actions
!
!-----------------------------------------------------------------------------
!   Parameter:     NvM_Actions_t the Actions to be performed
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_FsmAction(NvM_StateChangeActionsPtrType NvM_Actions_pt)
{
    NvM_ActionTable_ap[NvM_Actions_pt->ExitHandler_t]();
    NvM_ActionTable_ap[NvM_Actions_pt->EntryHandler_t]();
}


#define NVM_STOP_SEC_CODE
#include "MemMap.h"
/*---- End of File ---------------------------------------------------------*/
