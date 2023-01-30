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
 *         File:  NvM_Queue.c
 *      Project:  MemService_AsrNvM
 *       Module:  NvM - Submodule Queue
 *    Generator:  -
 *
 *  Description:  This sub-module contains the queue-handling of the (optionally)
 *                prioritized job queue.
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
 *  INCLUDE MAIN HEADER (BECAUSE OF ERROR CODES)
 *********************************************************************************************************************/
#include "NvM.h"
#include "NvM_PrivateCfg.h"

/**********************************************************************************************************************
 *  INCLUDE OF THE CENTRAL INTERNAL INCLUDE
 *********************************************************************************************************************/
#include "NvM_JobProc.h"

/**********************************************************************************************************************
 *  MODULE HEADER INCLUDES
 *********************************************************************************************************************/
#include "NvM_Queue.h"

/**********************************************************************************************************************
 *  TARGET AND COMPILER
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

#if (     (NVM_QUEUE_MAJOR_VERSION != (3u)) \
       || (NVM_QUEUE_MINOR_VERSION != (7u)))
  #error "Version numbers of NvM_Queue.c and NvM_Queue.h are inconsistent!"
#endif

#if (     (NVM_CFG_MAJOR_VERSION != (3u)) \
       || (NVM_CFG_MINOR_VERSION != (7u)))
    #error "Version numbers of NvM_Queue.c and NvM_cfg.h are inconsistent!"
#endif

/* this ist the only object we always need, regardless of NVM_API_CONFIG_CLASS */
#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

     VAR(NvM_JobType, NVM_PRIVATE_DATA) NvM_CurrentJob_t;

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

/* queueing is only needed in config classes 2 and 3 */
#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)


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
#define NVM_IMMEDIATE_JOB_PRIO  (0x00u)
#define NVM_LOWEST_JOB_PRIO     (0xFFu)
#define NVM_LIST_END            (0xFFu)

/**********************************************************************************************************************
 *  INTERNAL MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  INTERNAL TYPE DEFINITIONS
 **********************************************************************************************************************/

/* type to reference to a List */
typedef P2VAR(NvM_QueueEntryRefType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_QueueListHeadRefType;

typedef struct
{
    NvM_QueueEntryRefType SrvList;
    NvM_QueueEntryRefType EmptyList;
} NvM_JobQueueType;

/**********************************************************************************************************************
 *  INTERNAL DATA
 **********************************************************************************************************************/
#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"
    /*---- Internal Module Global Variables ------------------------------- */
    #if(NVM_JOB_PRIORISATION == STD_ON)
        STATIC VAR(NvM_JobQueueType, NVM_PRIVATE_DATA) NvM_HighPrioQueue;

        STATIC VAR(NvM_QueueEntryRefType, NVM_PRIVATE_DATA) NvM_LastJobEntry;
    #endif
    
    STATIC VAR(NvM_JobQueueType, NVM_PRIVATE_DATA) NvM_NormalPrioQueue;

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

/**********************************************************************************************************************
 *  INTERNAL FORWARD DECLARATIONS
 **********************************************************************************************************************/
    static FUNC(void, NVM_PRIVATE_CODE) NvM_QueuePush(NvM_QueueListHeadRefType, NvM_QueueEntryRefType);
    static FUNC(NvM_QueueEntryRefType, NVM_PRIVATE_CODE) NvM_QueuePop(NvM_QueueListHeadRefType);

#if(NVM_JOB_PRIORISATION == STD_ON)
    static FUNC(void, NVM_PRIVATE_CODE) NvM_QueueRequeueLastJob(void);
#endif
/**********************************************************************************************************************
 *  IMPLEMENTATION
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QueueInit
!
!-----------------------------------------------------------------------------
!   Function Description: Initialization of the NvM submodule NvM_Queue
!
!-----------------------------------------------------------------------------
!   Parameter:        none
!   Returnvalue:      void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PRIVATE_CODE) NvM_QueueInit(void)
{
    uint8_least index = NvM_QueueSizes_t.MaxIndex;


    /* link all list elements */
    while(index > 0)
    {
        /* element at <index> is linked to its predecessor */
        NvM_JobQueue_at[index].PrevEntry = index - 1u;
       
        /* now we are at the predecessor, link it with it successor */
        NvM_JobQueue_at[index - 1u].NextEntry = index;

        /* intializing the SeviceId member of each list element is not necessary, because initially
           they are in the "empty" list --> the member will not be used.
           Once an element gets into the job queue, the Service Id will be initialized */
         

        --index;
    }

    /* split the lists into two separate ring lists */
    index = NvM_QueueSizes_t.NpSize;

    #if (STD_ON == NVM_JOB_PRIORISATION)
        NvM_LastJobEntry = NVM_LIST_END;

        NvM_HighPrioQueue.SrvList = NVM_LIST_END;
        NvM_HighPrioQueue.EmptyList = index;
    
        NvM_JobQueue_at[NvM_QueueSizes_t.MaxIndex].NextEntry = index;
        NvM_JobQueue_at[index].PrevEntry = NvM_QueueSizes_t.MaxIndex;
    #endif

    /* normal prio queue */
    NvM_JobQueue_at[--index].NextEntry = 0;
    NvM_JobQueue_at[0].PrevEntry = index;

    NvM_NormalPrioQueue.EmptyList = 0;
    NvM_NormalPrioQueue.SrvList = NVM_LIST_END;
}


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QueueJob
!
!-----------------------------------------------------------------------------
!   Function Description: Queues a new job
!
!-----------------------------------------------------------------------------
!   Parameter:        BlockId, ServiceId, RamAddress
!   Returnvalue:      boolean -> TRUE (job queued) / FALSE (queue full)
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QueueJob(NvM_BlockIdType BlockId,
                                   NvM_InternalServiceIdType ServiceId,
                                          NvM_RamAddressType RamAddress
    )
{
  const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = 
    (BlockId & NVM_DCM_BLOCK_OFFSET) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);
    boolean retVal;

#if(NVM_JOB_PRIORISATION == STD_ON)
    const uint8 priority = NvM_BlockDescriptorTable_at[BlockId & (~NVM_DCM_BLOCK_OFFSET)].BlockPrio_u8;
    /* NvM_HighPrioQueue is only the right queue if block has an immediate priority, current job is a 
      write-job and requested block is not a DCM-Block. Otherwise NvM_NormalPrioQueue is right queue. */
    CONSTP2VAR(NvM_JobQueueType, AUTOMATIC, NVM_PRIVATE_DATA) UsedQueue =
        ((priority == 0) && (ServiceId == NVM_INT_FID_WRITE_BLOCK) && ((BlockId & NVM_DCM_BLOCK_OFFSET) == 0)) ? 
        (&NvM_HighPrioQueue) : (&NvM_NormalPrioQueue);
#else
    CONSTP2VAR(NvM_JobQueueType, AUTOMATIC, NVM_PRIVATE_DATA) UsedQueue = &NvM_NormalPrioQueue;
#endif

    NvM_EnterCriticalSection();

    /* check pending */
    #if (STD_ON == NVM_CFG_CHK_BLOCK_PENDING)
        if (NVM_REQ_PENDING == NvM_RamMngmt_ptloc->NvRamErrorStatus_u8)
        {
            const NvM_ServiceIdType PublicServiceId = NvM_IntServiceDescrTable_at[ServiceId].PublicFid_t;
            NvM_ExitCriticalSection();
            
            NvM_Errorhook(PublicServiceId, NVM_E_BLOCK_PENDING);
            return FALSE;
        }
    #endif

    /* check queue fill level */
    if(UsedQueue->EmptyList != NVM_LIST_END)
    {
        /* get element from free-list */
        const NvM_QueueEntryRefType elem = NvM_QueuePop(&UsedQueue->EmptyList);
        CONSTP2VAR(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) elemPtr = &NvM_JobQueue_at[elem];

        elemPtr->BlockId   = BlockId;
        elemPtr->RamAddr_t = RamAddress;
        elemPtr->ServiceId = ServiceId;

#if(NVM_JOB_PRIORISATION == STD_ON)
        elemPtr->JobPrio = priority;
#endif

        NvM_QueuePush(&UsedQueue->SrvList, elem);

        retVal = TRUE;
        NvM_RamMngmt_ptloc->NvRamErrorStatus_u8 = NVM_REQ_PENDING;
    }
    else
    {   /* no free element --> queuing failed */
        /* no free element --> queuing failed */
        const NvM_ServiceIdType PublicServiceId = NvM_IntServiceDescrTable_at[ServiceId].PublicFid_t;
        /* call the development error callback for listoverflow and
        * set retVal to FALSE */
        NvM_Errorhook(PublicServiceId, NVM_E_LIST_OVERFLOW);
        
        retVal = FALSE;
    }

    NvM_ExitCriticalSection();
    return retVal;
}


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QueueRequeueLastJob
!
!-----------------------------------------------------------------------------
!   Function Description: Puts the last found job back into the Normal Prio
!                         Queue. It will be inserted at the list end.       
!
!-----------------------------------------------------------------------------
!   Parameter:        None
!   Returnvalue:      None
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if(NVM_JOB_PRIORISATION == STD_ON)
    static FUNC(void, NVM_PRIVATE_CODE) NvM_QueueRequeueLastJob(void)
    {
        if(NvM_LastJobEntry != NVM_LIST_END)
        {
            NvM_EnterCriticalSection();
            /* add element at list start */
            NvM_QueuePush(&NvM_NormalPrioQueue.SrvList, NvM_LastJobEntry);

            /*  set the highest possible priority */
            NvM_JobQueue_at[NvM_LastJobEntry].JobPrio = NVM_IMMEDIATE_JOB_PRIO;

            /* shift Queue Start to next element, remember: it is a ring list ... */
            NvM_NormalPrioQueue.SrvList = NvM_JobQueue_at[NvM_LastJobEntry].NextEntry;
            
            NvM_LastJobEntry = NVM_LIST_END;
            NvM_ExitCriticalSection();
        }
    }
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryHighPrioJob
!
!-----------------------------------------------------------------------------
!   Function Description: Checks the high Prio Job list for a job
!                         Just returns whether the queue is empty. 
!
!-----------------------------------------------------------------------------
!   Parameter:        None.
!   Returnvalue:      TRUE  -> the queue is not empty,
!                     FALSE -> the queue is empty
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if(NVM_JOB_PRIORISATION == STD_ON)
    FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHighPrioJob(void)
    {
        return (NvM_HighPrioQueue.SrvList != NVM_LIST_END);
    }
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryNormalPrioJob
!
!-----------------------------------------------------------------------------
!   Function Description: Checks the normal Prio Job list for a job
!                         Just returns whether the queue is empty. 
!
!-----------------------------------------------------------------------------
!   Parameter:        None.
!   Returnvalue:      TRUE  -> the queue is not empty,
!                     FALSE -> the queue is empty
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNormalPrioJob(void)
{
    return (NvM_NormalPrioQueue.SrvList != NVM_LIST_END);
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActGetHighPrioJob
!
!-----------------------------------------------------------------------------
!   Function Description: Retrieves the next job from the High prio job queue.
!                         The next job is the last element in the list.
!                         The Queue is expected to contain at least one element.
!-----------------------------------------------------------------------------
!   Parameter:        None.
!   Returnvalue:      None.
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if(NVM_JOB_PRIORISATION == STD_ON)
    FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetHighPrioJob(void)
    {
        NvM_QueueEntryRefType elem;

        /* when current job was interrupted, requeue last job before starting the high prio job */
        if(NVM_STATE_NORMAL_PRIO_JOB == NvM_TaskState_t)
        {
            /* cancel the underlying device, if we think it is still pending,  *
             *  This guarantees that our current device id is valid            */
            if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_PENDING)
            {
                MemIf_Cancel((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8);
            }
            
            NvM_QueueRequeueLastJob();        
        }

        NvM_EnterCriticalSection();
        
        /* make the last entry (predecessor of list head) the current entry */
        NvM_HighPrioQueue.SrvList = NvM_JobQueue_at[NvM_HighPrioQueue.SrvList].PrevEntry;

        /* get the head element (it's actually the last one) from list, the new head is its successor,
         *  which is the origninal head.
         */
        elem = NvM_QueuePop(&NvM_HighPrioQueue.SrvList);

        /* an immediate write job cannot be interrupted, therefore we can
         *  free the list element */
        NvM_QueuePush(&NvM_HighPrioQueue.EmptyList, elem);
        
        NvM_CurrentJob_t.JobBlockId_t   = NvM_JobQueue_at[elem].BlockId;
        NvM_CurrentJob_t.JobServiceId_t = NvM_JobQueue_at[elem].ServiceId;
        NvM_CurrentJob_t.RamAddr_t      = NvM_JobQueue_at[elem].RamAddr_t;
        
        /* make sure that the last job entry is empty --> no re-queuing will be performed */
        NvM_LastJobEntry = NVM_LIST_END;

        NvM_ExitCriticalSection();

        /* Device of new high prio write job must be cancelled so that high prio job can start as soon as possible. */
        if((0x00 == NvM_BlockDescriptorTable_at[NvM_CurrentJob_t.JobBlockId_t].BlockPrio_u8) &&
          (NVM_INT_FID_WRITE_BLOCK == NvM_CurrentJob_t.JobServiceId_t))
        {
          MemIf_Cancel(NvM_BlockDescriptorTable_at[NvM_CurrentJob_t.JobBlockId_t].DeviceId_u8);
          NvM_JobSubState_t = NVM_STATE_FSM_FINISHED;
        }

    }
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActQueueFreeLastJob
!
!-----------------------------------------------------------------------------
!   Function Description: Frees the last found job item.
!                         It will be added to the normal queue's free list. 
!
!-----------------------------------------------------------------------------
!   Parameter:        None.
!   Returnvalue:      None.
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if(NVM_JOB_PRIORISATION == STD_ON)
    FUNC(void, NVM_PRIVATE_CODE) NvM_ActQueueFreeLastJob(void)
    {
        if(NvM_LastJobEntry != NVM_LIST_END)
        {
            NvM_EnterCriticalSection();
            /* add element at list start */
            NvM_QueuePush(&NvM_NormalPrioQueue.EmptyList, NvM_LastJobEntry);

            NvM_LastJobEntry = NVM_LIST_END;
            NvM_ExitCriticalSection();
        }
    }
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActGetNormalPrioJob
!
!-----------------------------------------------------------------------------
!   Function Description: Scans the given queue for the entry with highest 
!                         priority, located nearest to the list end.
!                         The element is removed from the list, but stored
!                         in NvM_lastJobEntry.
!                         The job parameters will be copied to the passed
!                         job Structure.
!                         The Queue is expected to contain at least one element.
!-----------------------------------------------------------------------------
!   Parameter:        None.
!   Returnvalue:      None.
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetNormalPrioJob(void)
{
#if (NVM_JOB_PRIORISATION == STD_ON)
    /* search for the highest prioritized entry */
    NvM_QueueEntryRefType maxPrioElem;
    NvM_QueueEntryRefType currentElem;
    uint8 maxPrio;

    NvM_EnterCriticalSection();
    /* We have to gurantee, that we really get the last element.
     * We only get it, as long as our head element remains the head element.
     * Otherwise it would just point to its predecessor.
     */
    currentElem = maxPrioElem = NvM_JobQueue_at[NvM_NormalPrioQueue.SrvList].PrevEntry;
    
    maxPrio = NvM_JobQueue_at[maxPrioElem].JobPrio;

    NvM_ExitCriticalSection();

    /* the actual iteration over the queue is not a critical section,
       because the conmsistency of the list (prev and next pointers) is guaranteed by
       NvM_QueueJob()
       If the queue contains only one element, it will be checked twice
       (one iteration - it will be compared with itself -> that's no problem*/
    do
    {
        currentElem = NvM_JobQueue_at[currentElem].PrevEntry;

        if(NvM_JobQueue_at[currentElem].JobPrio < maxPrio)
        {
            maxPrioElem = currentElem;
            maxPrio = NvM_JobQueue_at[currentElem].JobPrio;
        }
    }
    while(currentElem != NvM_NormalPrioQueue.SrvList);


    /* now, we have the entry of interest. */
    NvM_LastJobEntry = maxPrioElem;

    NvM_CurrentJob_t.JobBlockId_t = NvM_JobQueue_at[maxPrioElem].BlockId;
    NvM_CurrentJob_t.JobServiceId_t = NvM_JobQueue_at[maxPrioElem].ServiceId;
    NvM_CurrentJob_t.RamAddr_t = NvM_JobQueue_at[maxPrioElem].RamAddr_t;


    /* remove entry from the queue, discard the return value */
    NvM_EnterCriticalSection();

    (void)NvM_QueuePop(&maxPrioElem);
    
    /* if it was the first element of the queue, we need to adjust the real queue head.
     * Otherwise it would not have been changeg be removing the entry.
    */
    if(NvM_NormalPrioQueue.SrvList == NvM_LastJobEntry)
    {
        NvM_NormalPrioQueue.SrvList = maxPrioElem;
    }

    NvM_ExitCriticalSection();

#else
    NvM_QueueEntryRefType elem;

    NvM_EnterCriticalSection();
    /* just take the last queue element, don't store it in NvM_LastJobEntry (it does not exist), 
     * but remove it from the queue.
     * Just update the queue head to point to its prev element (which is the tail), then pop.
       After that, the head points to the head again.
     */
    NvM_NormalPrioQueue.SrvList = NvM_JobQueue_at[NvM_NormalPrioQueue.SrvList].PrevEntry;
    elem = NvM_QueuePop(&NvM_NormalPrioQueue.SrvList);

    /* free the element --> add it to free-list */
    NvM_QueuePush(&NvM_NormalPrioQueue.EmptyList, elem);

    NvM_CurrentJob_t.JobBlockId_t = NvM_JobQueue_at[elem].BlockId;
    NvM_CurrentJob_t.JobServiceId_t = NvM_JobQueue_at[elem].ServiceId;
    NvM_CurrentJob_t.RamAddr_t = NvM_JobQueue_at[elem].RamAddr_t;

    
    NvM_ExitCriticalSection();
#endif /* NVM_JOB_PRIORISATION */
} /* NvM_ActGetNormalPrioJob */

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QueuePush
!
!-----------------------------------------------------------------------------
!   Function Description: Pushes the given element onto the given list,
!                         i.e. the element is inserted at list head.        
!
!-----------------------------------------------------------------------------
!   Parameter:        queue - reference to the queue start pointer
!                     elem  - reference to the element to be pushed.
!   Returnvalue:      None.
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_QueuePush(NvM_QueueListHeadRefType queue, NvM_QueueEntryRefType elem)
{
    CONSTP2VAR(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) elemPtr = &NvM_JobQueue_at[elem];

    if(*queue == NVM_LIST_END)
    {
        /* queue is currently empty. put new element in, link it with itself */
        *queue = elem;
        elemPtr->NextEntry = elemPtr->PrevEntry = elem;
    }
    else
    {
        CONSTP2VAR(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) NextPtr = &NvM_JobQueue_at[*queue];

        elemPtr->NextEntry = *queue;
        elemPtr->PrevEntry = NextPtr->PrevEntry;

        NvM_JobQueue_at[NextPtr->PrevEntry].NextEntry = elem;
        NextPtr->PrevEntry = elem;
        *queue = elem;
    }
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QueuePop
!
!-----------------------------------------------------------------------------
!   Function Description: Pops the first element from the given list,  
!                         i.e. the element is removed from the list and   
!                         will be returned.
!                         The given list shall not be empty!
!-----------------------------------------------------------------------------
!   Parameter:        queue - reference to the queue start pointer
!   Returnvalue:      Reference to the list element.
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(NvM_QueueEntryRefType, NVM_PRIVATE_CODE) NvM_QueuePop(NvM_QueueListHeadRefType queue)
{
    const uint8 retVal = *queue;
    CONSTP2VAR(NvM_QueueEntryType, AUTOMATIC, NVM_PRIVATE_DATA) elemPtr = &NvM_JobQueue_at[retVal];

    if(elemPtr->NextEntry == retVal)
    {
        /* element is linked with itself, therefore the list is empty, now */
        *queue = NVM_LIST_END;
    }
    else
    {
        *queue = elemPtr->NextEntry;

        NvM_JobQueue_at[elemPtr->NextEntry].PrevEntry = elemPtr->PrevEntry;
        NvM_JobQueue_at[elemPtr->PrevEntry].NextEntry = elemPtr->NextEntry;
    }

    return retVal;
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"


#endif /* not config class 1 */
/*---- End of File ---------------------------------------------------------*/
