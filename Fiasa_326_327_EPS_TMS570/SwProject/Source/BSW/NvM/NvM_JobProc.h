/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2010 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NvM_JobProc.h
 *    Component:  MemService_AsrNvM
 *       Module:  NvM - Submodule JobProc (Job Processing)
 *    Generator:  -
 *
 *  Description:  This sub-module implements the FSM for the NVM, including the state description table
 *    
 *                This file is an internal include; it shall not be included by other modules than NvM!
 *  
 *********************************************************************************************************************/

/* Do not modify this file! */

/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
#if (!defined NVM_JOBPROC_H_)
#define NVM_JOBPROC_H_

/**********************************************************************************************************************
 * VERSION IDENTIFICATION
 *********************************************************************************************************************/
#define NVM_JOBPROC_MAJOR_VERSION    (3u)
#define NVM_JOBPROC_MINOR_VERSION    (7u)
#define NVM_JOBPROC_PATCH_VERSION    (0u)

#include "NvM_Act.h"
#include "NvM_Qry.h"
#include "NvM_Crc.h"

/**********************************************************************************************************************
 * API MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * API TYPE DEFINITIONS
 *********************************************************************************************************************/
/* type of a job that is to be queued */
typedef struct
{
    NvM_BlockIdType             JobBlockId_t;
    NvM_InternalServiceIdType   JobServiceId_t;
    NvM_RamAddressType          RamAddr_t;
} NvM_JobType;

typedef P2VAR(NvM_JobType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_JobPtrType;

/* job processing structure: contains all information related to
   the processing of one certain job
*/
typedef struct
{
    NvM_BlockDescrPtrType       Descriptor_pt;
    NvM_RamMngmtPtrType         Mngmt_pt;
    NvM_RamAddressType          RamAddr_t;
    NvM_CrcJobType              BlockCrcJob_t;
    uint16                      NvIdentifier_u16;
#if(STD_ON == NVM_CRC_INT_BUFFER)
    uint16                      ByteCount_u16;
#endif
    NvM_RequestResultType       LastResult_t;
    uint8                       WriteRetryCounter_u8;
    uint8                       InternalFlags_u8;    
    uint8                       NvState_u8;
} NvM_BlockInfoType;

typedef P2VAR(NvM_BlockInfoType, AUTOMATIC, NVM_FAST_DATA) NvM_BlockInfoPtrType;
/* Possible states of the NVManager */
/* Used for the task-, the jobmain-, and the jobsub-state machine */
typedef enum
{
    /* Possible states of the task state machine */
    NVM_STATE_UNINIT = 0u,
    NVM_STATE_IDLE,
    #if ((STD_ON == NVM_JOB_PRIORISATION) && (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1))
        NVM_STATE_HIGH_PRIO_JOB,
    #endif
    NVM_STATE_NORMAL_PRIO_JOB,
#if (NVM_KILL_WRITEALL_API == STD_ON)
    NVM_STATE_MULTI_BLOCK_JOB,
#endif
    /* Possible states of the jobmain- and jobsub state machine */

    /* Read Block */
    NVM_STATE_READ_READ_DATA,

    NVM_STATE_READ_CMP_CRC,
    NVM_STATE_READ_IMPL_RECOV,

    /* Write Block */
    NVM_STATE_WRITE_INITIAL,
    NVM_STATE_WRITE_TEST_PRI_READ,
    NVM_STATE_WRITE_TEST_SEC_READ,
    NVM_STATE_WRITE_WR_DATA_CRC_1,
    NVM_STATE_WRITE_WR_DATA_CRC_2,
    
#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    /* Invalidate Nv Block */
    NVM_STATE_INVALIDATING_BLOCK,

    /* Erase Nv Block */
    NVM_STATE_ERASE_ERASE_BLOCK,
#endif

    /* Restore Block Defaults - no states necessary */

    /* Read all */
    NVM_STATE_READALL_PROC_CONFIG_ID,
    NVM_STATE_READALL_PROC_RAM_BLOCK,
    NVM_STATE_READALL_CHK_EXT_RUNTIME,
    NVM_STATE_READALL_WR_ONCE_PROT,

#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    NVM_STATE_READALL_CHK_RAM_VALIDITY,
#endif

    NVM_STATE_READALL_READ_NV,

    /* Write All */
    NVM_STATE_WRITEALL_PROC_BLOCK,
    NVM_STATE_WRITEALL_CHECK_SKIP,
    NVM_STATE_WRITEALL_WRITE_FSM,
    NVM_STATE_WRITEALL_WAIT_MEMHWA,

    NVM_STATE_FSM_FINISHED
} NvM_StateIdType;

/* Force implizit cast for enum NvM_StateIdType into uint8 when using
 * NvMStateType as data type. But only for production mode in order to
 * see not only numbers when debugging in debug mode
 */
#if (STD_ON == NVM_DEV_ERROR_DETECT)
    typedef NvM_StateIdType NvM_StateType;
#else
    typedef uint8 NvM_StateType;
#endif

/* Descriptor, describing an internal service (async  NVM job) */
typedef struct
{
    NvM_StateActionType    InitialActionId;
    NvM_StateType          InitialState_t;
    NvM_ServiceIdType      PublicFid_t;
} NvM_IntServiceDescrType;

/**********************************************************************************************************************
 * MACROS / DEFINES
 *********************************************************************************************************************/

/* the maximum number of conditional exits a stat can have, the final ("else") exit is implicit */
#define NVM_MAX_NUM_OF_STATE_CONDITIONS (3u)

/* the maximum number of Query functions that can be ANDed together to form a state exit condition */
#define NVM_MAX_NUM_OF_QRY_AND (2u)

/**********************************************************************************************************************
 * TYPE DEFINITIONS
 *********************************************************************************************************************/
typedef struct
{
    NvM_StateActionType ExitHandler_t;
    NvM_StateActionType EntryHandler_t;
} NvM_StateChangeActionsType;

typedef P2CONST(NvM_StateChangeActionsType, AUTOMATIC, NVM_PRIVATE_CONST) NvM_StateChangeActionsPtrType;

/* describe one State exit with its condition, its Actions and its following state */
typedef struct
{
    NvM_StateQueryType         Queries_at[NVM_MAX_NUM_OF_QRY_AND];
    NvM_StateChangeActionsType Actions_t;
    NvM_StateType              NextState_t;
} NvM_StateChangeIfDescrType;

/* describe the final state exit ("else") to be taken if no condition matched */
typedef struct
{
    NvM_StateChangeActionsType Actions_t;
    NvM_StateType              NextState_t;
} NvM_StateChangeElseDescrType;

/* describe a state with it's possible change conditions */
typedef struct
{
    NvM_StateChangeIfDescrType   ChangeConditions_at[NVM_MAX_NUM_OF_STATE_CONDITIONS];
    NvM_StateChangeElseDescrType FinalCondition_t;
} NvM_StateDescrType;

/**********************************************************************************************************************
 * VARIABLES
 *********************************************************************************************************************/
#define NVM_START_SEC_VAR_FAST_8BIT
#include "MemMap.h"

   /* at least for development mode (where the following two state types are enums) 
    * the compiler is expected to ensure correct alignment, regardless of any given section alignment.
    * The state variables are used quite frequently (but never via pointers)
    */
   extern VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobMainState_t;
   extern VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobSubState_t;


/* extern definition of variables that area used in the NvM submodules
 * They are defined in NvM.c
 */
    extern VAR(uint8, NVM_FAST_DATA) NvM_ApiFlags_u8;

#define NVM_STOP_SEC_VAR_FAST_8BIT
#include "MemMap.h"

#define NVM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

   /* state of the task state machine */
   extern VAR(NvM_StateType, NVM_PRIVATE_DATA) NvM_TaskState_t;

#define NVM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

    extern VAR(NvM_JobType, NVM_PRIVATE_DATA) NvM_CurrentJob_t;
    extern VAR(NvM_BlockInfoType, NVM_PRIVATE_DATA) NvM_CurrentBlockInfo_t;

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

    /* Internal job descriptor table */
    extern CONST(NvM_IntServiceDescrType, NVM_PRIVATE_CONST) NvM_IntServiceDescrTable_at[];

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/**********************************************************************************************************************
 * FUNCTIONS
 *********************************************************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h"

    /* FSM processing functions */
    extern FUNC(NvM_StateType, NVM_PRIVATE_CODE) NvM_Fsm(NvM_StateType);
    extern FUNC(void, NVM_PRIVATE_CODE) NvM_JobProcInit(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* NVM_JOBPROC_H_ */


/*---- End of File -------------------------------------------------------- */
