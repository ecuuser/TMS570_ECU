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
 *         File:  NvM_Act.c
 *      Project:  MemService_AsrNvM
 *       Module:  NvM - Submodule Act (Actions)
 *    Generator:  -
 *
 *  Description:  This sub-module implements all state machines' action handlers
 *                to be executed upon state transitions
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
 *  INCLUDE OF THE CENTRAL INTERNAL INCLUDE
 *********************************************************************************************************************/
#include "NvM_JobProc.h"

/**********************************************************************************************************************
 *  MODULE HEADER INCLUDES
 *********************************************************************************************************************/
#include "NvM_Act.h"

/**********************************************************************************************************************
 *  INCLUDE OF THE QUEUE VARIABLES
 *********************************************************************************************************************/
#include "NvM_Queue.h"

/**********************************************************************************************************************
 *  INCLUDE OF THE CRC VARIABLES
 *********************************************************************************************************************/
#include "NvM_Crc.h"

/**********************************************************************************************************************
 *  TARGET AND COMPILER
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (     (NVM_ACT_MAJOR_VERSION != (3u)) \
       || (NVM_ACT_MINOR_VERSION != (7u)))
  #error "Version numbers of NvM_Act.c and NvM_Act.h are inconsistent!"
#endif

#if (     (NVM_CFG_MAJOR_VERSION != (3u)) \
       || (NVM_CFG_MINOR_VERSION != (7u)))
  #error "Version numbers of NvM_Act.c and NvM_Cfg.h are inconsistent!"
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

/* extracts primary NvBlock state from NvState */
#define NVM_EXTRACT_NVSTATE_PRI(NvState)    (((NvState) >> NVM_PRI_NVBLOCK_STATE_SHIFT) & NVM_NVBLOCK_STATE_BIT_MASK)

/* extracts secondary NvBlock state from NvState */
#define NVM_EXTRACT_NVSTATE_SEC(NvState)    (((NvState) >> NVM_SEC_NVBLOCK_STATE_SHIFT) & NVM_NVBLOCK_STATE_BIT_MASK)

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

/**********************************************************************************************************************
 *  ACTION HANDLER FUNCTIONS
 *  They are PRIVATE, i.e. they will be called only
 *  inside the NVM. Normally this means "from same segment".
 **********************************************************************************************************************/

    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetInitialAttr(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitMainFsm(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitBlock(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadAll(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadBlockFsm(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteAll(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlock(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlockFsm(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitRestoreBlockDefaults(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishMainJob(void);
#if(NVM_KILL_WRITEALL_API == STD_ON)
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActKillWriteAll(void);
#endif

    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishBlock(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitNextBlockReadAll(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishCfgIdCheck(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishReadBlock(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishWriteBlock(void);

#if(NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishEraseBlock(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActEraseNvBlock(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInvalidateNvBlock(void);
#endif

    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrc(void);

    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActWriteNvBlock(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActReadNvBlock(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrcRead(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActRestoreRomDefaults(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActTestBlockBlank(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActValidateRam(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupRedundant(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupOther(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActUpdateNvState(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqIntegrityFailed(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqSkipped(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActWait(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActNop(void);

    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetMultiBlockJob(void);
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActCopyNvDataToBuf(void);

    /* internal helpers --> no action functions */
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_UpdateConfigIdBlock(void);
#if(NVM_CRC_INT_BUFFER == STD_ON)    
    static FUNC(boolean, NVM_PRIVATE_CODE) NvM_InternalCopyDataAndCalcCrc(NvM_BlockInfoPtrType, NvM_RamAddressType, NvM_ConstRamAddressType);
#endif

 /**********************************************************************************************************************
 *  INTERNAL HELPER FUNCTIONS
 *  They are PRIVATE, i.e. they will be called only
 *  inside the NVM. Normally this means "from same segment".
 **********************************************************************************************************************/
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_IntCreateNvState(P2VAR(uint8, AUTOMATIC, NVM_PRIVATE_DATA) NvState, 
      uint8 NewState);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"


/**********************************************************************************************************************
 *  INTERNAL MODULE GLOBAL VARIABLES
 *********************************************************************************************************************/

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

CONST(NvM_ActFctPtrType, NVM_PRIVATE_CONST) NvM_ActionTable_ap[NVM_ACT_ID_Nop + 1] =
{
    NvM_ActSetInitialAttr,
    NvM_ActInitMainFsm,
    NvM_ActInitBlock,
    NvM_ActInitReadAll,
    NvM_ActInitReadBlockFsm,
    NvM_ActInitWriteAll,
    NvM_ActInitWriteBlock,
    NvM_ActInitWriteBlockFsm,
    NvM_ActInitRestoreBlockDefaults,
    NvM_ActFinishMainJob,
#if(NVM_KILL_WRITEALL_API == STD_ON)
    NvM_ActKillWriteAll,
#endif
    NvM_ActFinishBlock,
    NvM_ActInitNextBlockReadAll,
    NvM_ActFinishCfgIdCheck,
    NvM_ActFinishReadBlock,
    NvM_ActFinishWriteBlock,

#if(NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    NvM_ActFinishEraseBlock,
    NvM_ActEraseNvBlock,
    NvM_ActInvalidateNvBlock,
#endif
    NvM_ActProcessCrc,
    NvM_ActWriteNvBlock,
    NvM_ActReadNvBlock,
    NvM_ActProcessCrcRead ,
    NvM_ActRestoreRomDefaults,
    NvM_ActTestBlockBlank,
    NvM_ActValidateRam,
    NvM_ActSetupRedundant,
    NvM_ActSetupOther,
    NvM_ActUpdateNvState,
    NvM_ActSetReqIntegrityFailed,
    NvM_ActSetReqSkipped,

    NvM_ActCopyNvDataToBuf,
    NvM_ActGetMultiBlockJob,
#if(NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
    NvM_ActGetNormalPrioJob,
    #if(NVM_JOB_PRIORISATION == STD_ON)
        NvM_ActGetHighPrioJob,   
        NvM_ActQueueFreeLastJob,
    #endif
#endif
    NvM_ActWait,
    NvM_ActNop
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/**********************************************************************************************************************
 *  IMPLEMENTATION
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActEraseNvBlock()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if(NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActEraseNvBlock(void)
    {
        if (E_OK != MemIf_EraseImmediateBlock((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
                                              NvM_CurrentBlockInfo_t.NvIdentifier_u16))
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
        }
        else
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
        }
    }
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActFinishBlock()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishBlock(void)
{
    const NvM_AsyncCbkPtrType Cbk_pt = NvM_CurrentBlockInfo_t.Descriptor_pt->CallbackFunc_pt;
    const boolean wasNotWriteAll = (boolean)(NvM_CurrentJob_t.JobServiceId_t != NVM_INT_FID_WRITE_ALL);

#if(NVM_KILL_WRITEALL_API == STD_ON)
    /* set result only, if KillWriteAll was not called; otherwise it was set by KillWriteAll */
    if(wasNotWriteAll || ((NvM_ApiFlags_u8 & NVM_APIFLAG_KILL_WR_ALL_SET) == 0))
    {
        NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamErrorStatus_u8 = NvM_CurrentBlockInfo_t.LastResult_t;
    }
#else
    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamErrorStatus_u8 = NvM_CurrentBlockInfo_t.LastResult_t;
#endif
    /* set RamAttributes for blocks of MngmtType REDUNDANT depending on state of primary NvBlock */
    if(NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT)
    {
      /* is primary NvBlock uptodate? */
      if(NVM_NVBLOCK_STATE_UPTODATE != NVM_EXTRACT_NVSTATE_PRI(NvM_CurrentBlockInfo_t.NvState_u8))
      {
          /* primary NvBlock is not uptodate */
          NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= NVM_PRI_DEFECT_SET;
      }
      else
      {
          /* primary NvBlock is uptodate */
          NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 &= NVM_PRI_DEFECT_CL;
      }
    }

    /* invoke the callback function, if it is present, and if we are not processing a WriteAll job 
    and if current block is not a DCM Block */
    if((wasNotWriteAll) && (Cbk_pt != NULL_PTR) &&
        (0 == (NvM_CurrentJob_t.JobBlockId_t & NVM_DCM_BLOCK_OFFSET)))
    {
        /* invoke callback, ignore its result. */     
        (FUNC(void, NVM_APPL_CODE))Cbk_pt(NvM_IntServiceDescrTable_at[NvM_CurrentJob_t.JobServiceId_t].PublicFid_t,
                     NvM_CurrentBlockInfo_t.LastResult_t);
    }
    
    /* prepare for next block, during ReadAll and WriteAll */
    NvM_CurrentJob_t.JobBlockId_t++;
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActInitNextBlockReadAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitNextBlockReadAll(void)
{
    NvM_ActFinishBlock();

    /* avoid intializing an invalid Block, which would cause usage of invalide memory addresses
     * (especially Block Descriptor)                                                            */
    if(NvM_CurrentJob_t.JobBlockId_t < NvM_NoOfBlockIds_t)
    {
        NvM_ActInitBlock();
#if(NVM_CRC_INT_BUFFER == STD_ON)
        /* ReAssign CRC buffer to Block's configured CRC buffer. It works, even if CRC buffer
           is NULL_PTR (i.e. no CRC configured), because in this case the CRC job is designed
           to prevent from using (dereferencing) this pointer                                  */
        NvM_CrcJob_ReassignBuffer(&NvM_CurrentBlockInfo_t.BlockCrcJob_t,
                        NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockCrcAddr_t);
#endif
    }
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActFinishMainJob()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishMainJob(void)
{
    const NvM_InternalServiceIdType currSrvId = NvM_CurrentJob_t.JobServiceId_t;

    if((currSrvId == NVM_INT_FID_READ_ALL) || (currSrvId == NVM_INT_FID_WRITE_ALL))
    {
        NvM_RequestResultType JobResult;
        
        if((currSrvId == NVM_INT_FID_WRITE_ALL) && (NvM_ApiFlags_u8 & NVM_APIFLAG_CANCEL_WR_ALL_SET))
        {
            JobResult = NVM_REQ_CANCELLED;
        }
        else if(NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_ERROR_SET)
        {
            JobResult = NVM_REQ_NOT_OK;
        }
        else
        {
            JobResult = NVM_REQ_OK;
        }

        NvM_BlockMngmtArea_at[0].NvRamErrorStatus_u8 = JobResult;

        if(NvM_MultiBlockCbk != NULL_PTR)
        {
            NvM_MultiBlockCbk(NvM_IntServiceDescrTable_at[currSrvId].PublicFid_t, JobResult);
        }

        NvM_EnterCriticalSection();
            NvM_ApiFlags_u8 &= (NVM_APIFLAG_READ_ALL_CL & NVM_APIFLAG_WRITE_ALL_CL);
        NvM_ExitCriticalSection();
        

        #if(NVM_DRV_MODE_SWITCH == STD_ON)
                MemIf_SetMode(MEMIF_MODE_SLOW);
        #endif
    }
    else if(currSrvId != NVM_INT_FID_NO_JOB_PENDING) /* --> single Block Job */
    {
        NvM_ActFinishBlock();
    }
    else
    {
        /* nothing to do -> there was no job actually pending */
    }
    /* MultiBlock/Single Block job/no job */

    NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_NO_JOB_PENDING;
}

#if(NVM_KILL_WRITEALL_API == STD_ON)
    
/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActKillWriteAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Kill WriteAll, 
!                         - finalize sub FSMs,
!                         - clean up internal variables
!                         - don't set any job result (was set in NvM_KillWritAll API)
!                         Precondition: only called, if QryWriteAllKilled was true
!                                       We don't need to check again.
!                                       Must be called from Main FSM => because it
!                                       terminates all SubFsms
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActKillWriteAll(void)
{
    #if(NVM_DRV_MODE_SWITCH == STD_ON)
            MemIf_SetMode(MEMIF_MODE_SLOW);
    #endif

    NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_NO_JOB_PENDING;

    /* Kill sub-FSMs */
    NvM_JobMainState_t = NvM_JobSubState_t = NVM_STATE_FSM_FINISHED;

    NvM_EnterCriticalSection();
        /* Note that (tehoretically) ReadAll as well as WriteAll might already have been requested.
         * => NvM_GetStatus(0, ...) delivers "CANCELLED", since the calling NvM_KillWriteAll */
        NvM_ApiFlags_u8 &= (NVM_APIFLAG_CANCEL_WR_ALL_CL & NVM_APIFLAG_KILL_WR_ALL_CL);

    NvM_ExitCriticalSection();
}
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActFinishReadBlock()
!
!-----------------------------------------------------------------------------
!   Function Description: finalize ReadBlock FSM.
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishReadBlock(void)
{
    const NvM_RamMngmtPtrType MngmtPtr = NvM_CurrentBlockInfo_t.Mngmt_pt;
    /* updates NvState for current block and changes active block */
    NvM_ActUpdateNvState();    
    
    if((NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT)    &&
       (NVM_EXTRACT_NVSTATE_PRI(NvM_CurrentBlockInfo_t.NvState_u8) != NVM_NVBLOCK_STATE_OUTDATED) &&
       (NVM_EXTRACT_NVSTATE_SEC(NvM_CurrentBlockInfo_t.NvState_u8) == NVM_NVBLOCK_STATE_OUTDATED))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }

    if(NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_BLOCK_WRITE_BLOCK_ONCE_ON)
    {
        if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_NV_INVALIDATED)
        {
            MngmtPtr->NvRamAttributes_u8 &= NVM_WR_PROT_CL;
        }
        else
        {
            MngmtPtr->NvRamAttributes_u8 |= NVM_WR_PROT_SET;
        }
    }

    if(NvM_CurrentBlockInfo_t.LastResult_t != NVM_REQ_OK)
    {
        NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_ERROR_SET;

        if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_NOT_OK)
        {
            NvM_SetError(NvM_DemErrReqFailed);
        }
        else if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_INTEGRITY_FAILED)
        {
            NvM_SetError(NvM_DemErrIntegrityFailed);
        }
        else
        {
            /* Nothing to do */
        }
    }

    
} /* End of NvM_ActFinishReadBlock() */

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActFinishWriteBlock()
!
!-----------------------------------------------------------------------------
!   Function Description: finalize WriteBlock FSM.
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishWriteBlock(void)
{
    const NvM_RamMngmtPtrType MngmtPtr = NvM_CurrentBlockInfo_t.Mngmt_pt;

    if(NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT)
    {
        if(NVM_EXTRACT_NVSTATE_PRI(NvM_CurrentBlockInfo_t.NvState_u8) != NVM_NVBLOCK_STATE_UPTODATE)
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
        }
        else
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
        }

        /* Report an error to the DEM, if the secondary is NOT up-to-date after writing.          *
         * Primary NV block is handled like all other NVRAM block types                           */
        if(NVM_EXTRACT_NVSTATE_SEC(NvM_CurrentBlockInfo_t.NvState_u8) != NVM_NVBLOCK_STATE_UPTODATE)
        {
            NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_ERROR_SET;
            NvM_SetError(NvM_DemErrReqFailed);
        }
    }

    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_OK)
    {
        /* mark permanent(!) Block as UNCHANGED */
        if(NvM_CurrentBlockInfo_t.RamAddr_t == NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockDataAddr_t)
        {
            MngmtPtr->NvRamAttributes_u8 &= NVM_STATE_CHANGED_CL;
        }

        if(NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_BLOCK_WRITE_BLOCK_ONCE_ON)
        {
            MngmtPtr->NvRamAttributes_u8 |= NVM_WR_PROT_SET;
        }
    }
    else
    {   /* remember error condition to deliver the correct result for ReadAll/WriteAll */
        NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_ERROR_SET;
        NvM_SetError(NvM_DemErrReqFailed);
    }
} /* End of NvM_ActFinishWriteBlock() */

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActInitBlock()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitBlock(void)
{
    /* just to get a shorter notation ... */
    const NvM_BlockInfoPtrType InfoPtr = &NvM_CurrentBlockInfo_t;

    /* we need the Block Descriptor quite frequntly */
    NvM_BlockDescrPtrType DescrPtr;
    boolean DCMBlockFlag;
    NvM_BlockIdType orgBlockId;
     

    if(0 == (NvM_CurrentJob_t.JobBlockId_t & NVM_DCM_BLOCK_OFFSET))
    {
        /* it is original NVRAM Block */
        orgBlockId = NvM_CurrentJob_t.JobBlockId_t;
        DCMBlockFlag = FALSE;
    }
    else
    {
        /* it is a DCM Block */
        orgBlockId = (NvM_CurrentJob_t.JobBlockId_t & (NVM_DCM_BLOCK_OFFSET ^ 0xFFFFu));
        DCMBlockFlag = TRUE;
    }

    DescrPtr = &NvM_BlockDescriptorTable_at[orgBlockId];

    InfoPtr->LastResult_t = NVM_REQ_OK;

    InfoPtr->Descriptor_pt = DescrPtr;
    InfoPtr->NvIdentifier_u16 = DescrPtr->NvIdentifier_u16;

    if(FALSE == DCMBlockFlag)
    {
        InfoPtr->Mngmt_pt = &NvM_BlockMngmtArea_at[NvM_CurrentJob_t.JobBlockId_t];
    }
    else
    {
        InfoPtr->Mngmt_pt = &NvM_DcmBlockMngmt_t;
    }

    /* For blocks of MngmtType DATASET or DATASET_ROM the DataIndex has to be added to NvIdentifier */
    if((DescrPtr->MngmtType_t & NVM_BLOCK_DATASET) != 0)
    {
      InfoPtr->NvIdentifier_u16 |= InfoPtr->Mngmt_pt->NvDataIndex_t;
    }

    if(NvM_CurrentJob_t.RamAddr_t == NULL_PTR)
    {
        NvM_CurrentBlockInfo_t.RamAddr_t = DescrPtr->RamBlockDataAddr_t;
    }
    else
    {
        NvM_CurrentBlockInfo_t.RamAddr_t = NvM_CurrentJob_t.RamAddr_t;
    }

    /* check NVM_PRI_DEFECT Flag only for blocks of MngmtType REDUNDANT */
    if(DescrPtr->MngmtType_t & NVM_BLOCK_REDUNDANT)
    {    
      /* clear NvState */
      InfoPtr->NvState_u8 &= 0;

      /* set primary NvBlock active */
      InfoPtr->NvState_u8 &= NVM_NVBLOCK_STATE_PRI_ACTIVE;

      if((InfoPtr->Mngmt_pt->NvRamAttributes_u8 & NVM_PRI_DEFECT_SET) != 0)
      {
          /* NVM_PRI_DEFECT Flag is set */

          /* set primary NvState to defect */
          NvM_IntCreateNvState(&InfoPtr->NvState_u8, NVM_NVBLOCK_STATE_DEFECT);
      }
      else
      {
          /* set primary NvState to unknown(0x00) */
          NvM_IntCreateNvState(&InfoPtr->NvState_u8, NVM_NVBLOCK_STATE_UNKNOWN);
      }    
    }

    NvM_CrcJob_Create(&InfoPtr->BlockCrcJob_t, DescrPtr, NvM_CurrentBlockInfo_t.RamAddr_t);
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActInitMainFsm()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitMainFsm(void)
{
    #if (STD_ON == NVM_DEV_DETECT_FSM_ERRORS)
        /* this prevents from indexing the IntJobDescr array out of bounds */
        if (NvM_CurrentJob_t.JobServiceId_t > NVM_INT_FID_NO_JOB_PENDING)
        {
            NvM_JobMainState_t = NVM_STATE_FSM_FINISHED;
            return;
        }
    #endif

    NvM_ActInitBlock();
    /* Initiate the main state machine */
    NvM_JobMainState_t = NvM_IntServiceDescrTable_at[NvM_CurrentJob_t.JobServiceId_t].InitialState_t;
    
    NvM_ActionTable_ap[NvM_IntServiceDescrTable_at[NvM_CurrentJob_t.JobServiceId_t].InitialActionId]();
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActInitReadAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Initialize ReadAll --> set up Block 1
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadAll(void)
{
    uint16_least currBlockId = NvM_NoOfBlockIds_t;

    /* clear Error and Dynamic Mismatch flags */
    NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_ERROR_CL & NVM_INTFLAG_DYN_MISMATCH_CL;

    do
    {
        currBlockId--;
        NvM_BlockMngmtArea_at[currBlockId].NvRamErrorStatus_u8 = NVM_REQ_PENDING;
    }
    while(currBlockId > 0); /* blockId 0 does not need to be set to PENDING, already done */

    NvM_CurrentJob_t.JobBlockId_t = 1u; /* first block id during ReadAll processing */
    
    NvM_ActInitBlock();
    NvM_ActSetInitialAttr();

    #if(NVM_DRV_MODE_SWITCH == STD_ON)
        MemIf_SetMode(MEMIF_MODE_FAST);
    #endif

    NvM_ActInitReadBlockFsm();
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActFinishCfgIdCheck()
!
!-----------------------------------------------------------------------------
!   Function Description: finalize Block 1 and Cfg Id check during ReadAll processing
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishCfgIdCheck(void)
{
    /* clear Config ID Mismatch Flag */
    NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_DYN_MISMATCH_CL;

    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_OK)
    {
        if((NvM_CompiledConfigId_t.Bytes_au8[0] != NvM_CurrentBlockInfo_t.RamAddr_t[0]) ||
           (NvM_CompiledConfigId_t.Bytes_au8[1] != NvM_CurrentBlockInfo_t.RamAddr_t[1]))
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;

#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
            NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_DYN_MISMATCH_SET;
            NvM_UpdateConfigIdBlock();
#endif
        }
    }
    else if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_NV_INVALIDATED)
    {
        NvM_UpdateConfigIdBlock();
    }
    else /* any other negative result */
    {
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
        NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_DYN_MISMATCH_SET;
        NvM_UpdateConfigIdBlock();
#endif
    }
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActInitWriteAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Initialize WriteAll
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteAll(void)
{
    /* clear Error flag */
    NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_ERROR_CL;
    
    NvM_CurrentJob_t.JobBlockId_t = 1u;

    NvM_ActInitBlock();
    
    #if(NVM_DRV_MODE_SWITCH == STD_ON)
        MemIf_SetMode(MEMIF_MODE_FAST);
    #endif
}
 /*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActInitWriteBlock()
!
!-----------------------------------------------------------------------------
!   Function Description: Initialize WriteBlock
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlock(void)
{
    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 = 0;

    /* determine LastResult from NvState for Blocks of MngmtType REDUNDANT */
    if(NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT)
    {
      /* determine LastResult_t from NvState */
      if(NVM_EXTRACT_NVSTATE_PRI(NvM_CurrentBlockInfo_t.NvState_u8) != NVM_NVBLOCK_STATE_DEFECT)
      {
          /* is current NvBlock not defect => test readability */
          NvM_ActTestBlockBlank();
      }
      else
      {
          NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
      }
    }

#if(STD_ON == NVM_CRC_INT_BUFFER)
    NvM_CurrentBlockInfo_t.ByteCount_u16 = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16;

    /* recalculated CRC shal be redirected to Internal buffer */
    NvM_CrcJob_ReassignBuffer(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, 
                              &NvM_InternalBuffer_au8[NvM_CurrentBlockInfo_t.ByteCount_u16]);
#endif
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActFinishEraseBlock()
!                  
!-----------------------------------------------------------------------------
!   Function Description: Finish erase block and invalidate block processing
!                         Evaluate result for redundant blocks,
!                         Report error to DEM, if processing failed.
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if(NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActFinishEraseBlock(void)
    {
        if(NvM_CurrentBlockInfo_t.LastResult_t != NVM_REQ_OK)
        {
            NvM_SetError(NvM_DemErrReqFailed);
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
        }
    }
#endif
/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActInitReadBlockFsm()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitReadBlockFsm(void)
{
    const NvM_StateActionType InitialActId = NvM_IntServiceDescrTable_at[NVM_INT_FID_READ_BLOCK].InitialActionId;
    NvM_JobSubState_t = NvM_IntServiceDescrTable_at[NVM_INT_FID_READ_BLOCK].InitialState_t;
    
    NvM_ActionTable_ap[InitialActId]();
}


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActInitWriteBlockFsm()
!
!-----------------------------------------------------------------------------
!   Function Description: Initialize the WriteBlock FSM as Sub-State Machine
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitWriteBlockFsm(void)
{
    const NvM_StateActionType InitialActId = NvM_IntServiceDescrTable_at[NVM_INT_FID_WRITE_BLOCK].InitialActionId;
    
    NvM_JobSubState_t = NvM_IntServiceDescrTable_at[NVM_INT_FID_WRITE_BLOCK].InitialState_t;
    NvM_ActionTable_ap[InitialActId]();
}


STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInitRestoreBlockDefaults(void)
{
    NvM_ActRestoreRomDefaults();
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActInvalidateNvBlock()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if(NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActInvalidateNvBlock(void)
    {
        if (E_OK != MemIf_InvalidateBlock((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
                                          NvM_CurrentBlockInfo_t.NvIdentifier_u16))
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
        }
        else
        {
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
        }
    }
#endif
/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActNop()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform nothing
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActNop(void)
{
    return;
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActWriteNvBlock()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActWriteNvBlock(void)
{
    const NvM_RamAddressType src_pt =
#if(NVM_CRC_INT_BUFFER == STD_ON)
        (NvM_CrcJob_GetCrcLength(&NvM_CurrentBlockInfo_t.BlockCrcJob_t) == 0) ?
                                            NvM_CurrentBlockInfo_t.RamAddr_t : NvM_InternalBuffer_au8;
#else
        NvM_CurrentBlockInfo_t.RamAddr_t;
#endif
    Std_ReturnType retValMemIf;

    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8++;

#if(NVM_KILL_WRITEALL_API == STD_ON)
    /* Prevent from issueing a write job to lower layer, if KillWriteAll was requested.
     *  Critical section, because EcuM (caller of NvM_KilWriteAll)
     *                    might run in a task which preempted our MainFunction!! */
    NvM_EnterCriticalSection();

    if((NvM_CurrentJob_t.JobServiceId_t != NVM_INT_FID_WRITE_ALL) ||
       ((NvM_ApiFlags_u8 & NVM_APIFLAG_KILL_WR_ALL_SET) == 0))
    {
#endif

        retValMemIf = MemIf_Write((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
                                                        NvM_CurrentBlockInfo_t.NvIdentifier_u16, src_pt);
        if(E_OK == retValMemIf)
        {
          NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
        }
        else
        {
          NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
        }

#if(NVM_KILL_WRITEALL_API == STD_ON)
    }
    else
    {
        /* Result is quite irrelevant, but PENDING prevents from write retry handling */
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    NvM_ExitCriticalSection();
#endif

}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActReadNvBlock()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActReadNvBlock(void)
{
    const uint8_least crcLen = NvM_CrcJob_GetCrcLength(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);
    const uint16_least BlockLength = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16;
#if(NVM_CRC_INT_BUFFER == STD_ON)
    /* => all read request for block with CRC are directed into internal buffer */
    const NvM_RamAddressType readDest_pt = (crcLen != 0) ? NvM_InternalBuffer_au8 : NvM_CurrentBlockInfo_t.RamAddr_t;

    /* reset Byte Count for same purpose as we subsequently re-init the CRC job */
    NvM_CurrentBlockInfo_t.ByteCount_u16 = BlockLength;
#else
    const NvM_RamAddressType readDest_pt = NvM_CurrentBlockInfo_t.RamAddr_t;    
#endif

    /* re-init CRC calc job, for two purposes:
       - if we are processing the secondary NV block of a redundant NVRAM Block, CRC calculation must be restarted
       - if we are actually processing a CRC block - the internal buffer will be the CRC source.
         (if we're processing a non-CRC block, it does not matter - it won't be used)
       First purpose is the reason to re-init CRC job also in case internal buffering was disabled.               */
    NvM_CrcJob_Create(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_CurrentBlockInfo_t.Descriptor_pt, readDest_pt);

    if (E_OK !=
            MemIf_Read((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
                       NvM_CurrentBlockInfo_t.NvIdentifier_u16,
                       0u,
                       readDest_pt,
                       BlockLength + crcLen))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActProcessCrcRead()
!
!-----------------------------------------------------------------------------
!   Function Description: Two purposes:
!                         - Calculate CRC after NV data Read
!                         - Copy data from internal buffer to user RAM block.
!                           (if NVM_CRC_INT_BUFFER is enabled)
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrcRead(void)
{
    const NvM_BlockInfoPtrType info_pt = &NvM_CurrentBlockInfo_t;
#if(NVM_CRC_INT_BUFFER)
    if(NvM_InternalCopyDataAndCalcCrc(info_pt, info_pt->RamAddr_t, NvM_InternalBuffer_au8))
    {
        const NvM_BlockDescrPtrType descr_pt = info_pt->Descriptor_pt;
        
        if(info_pt->RamAddr_t == descr_pt->RamBlockDataAddr_t)
        {
                
            /* copy CRC that has been read from NV to Block's Crc Buffer */
            NvM_CrcJob_ExportBufferedValue(&info_pt->BlockCrcJob_t, descr_pt->RamBlockCrcAddr_t);
        }
    }

#else    
    NvM_CrcJob_Process(&info_pt->BlockCrcJob_t, NvM_NoOfCrcBytes_u16);
#endif
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActRestoreRomDefaults()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActRestoreRomDefaults(void)
{
    const boolean romBlock_bl = (boolean)(NvM_CurrentBlockInfo_t.Descriptor_pt->RomDefaultBlock != 0);
    const NvM_GenericRomDefaultsPtrType def_ptr = NvM_CurrentBlockInfo_t.Descriptor_pt->defaults_pt;
    const NvM_RamAddressType RamBlock = NvM_CurrentBlockInfo_t.RamAddr_t;    
    
    if(def_ptr != NULL_PTR)
    {
        const NvM_RomAddressType RomBlock = (NvM_RomAddressType)def_ptr;
        if(romBlock_bl)
        {
            uint16_least ByteCount = NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16;
            
            do
            {
                --ByteCount;
                RamBlock[ByteCount] = RomBlock[ByteCount];
            }
            while(ByteCount > 0);
            
        }
        else 
        {
            ((NvM_InitCbkPtrType)def_ptr)();
        }

        /* we got some Default Data, is it a permanent RAM Block to be validated? */
        if(RamBlock == NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockDataAddr_t)
        {
            NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= (NVM_STATE_VALID_SET | NVM_STATE_CHANGED_SET);
    #if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
            NvM_CrcQueueJob(NvM_CurrentJob_t.JobBlockId_t);
    #endif
        }
    }
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActSetInitialAttr()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetInitialAttr(void)
{
    uint8 attribs_u8loc;

    /* set the write protection attribute if NVM_BLOCK_WRITE_PROT is TRUE */
    if (NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_BLOCK_WRITE_PROT_ON)
    {
        /* set the write protection (we don't need to set one bit, since it is
         * the only value that shall be set, all other bits are zero)
         */
         attribs_u8loc = NVM_WR_PROT_SET;
    }
    else
    {
        /* clear all bits */
          attribs_u8loc = 0u;
    }
    
    /* Overwrite all attribute flags with configured write protection setting. */
    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 = attribs_u8loc;
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActSetReqIntegrityFailed()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqIntegrityFailed(void)
{
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_INTEGRITY_FAILED;
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActSetReqSkipped()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetReqSkipped(void)
{
    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_BLOCK_SKIPPED;
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActSetupRedundant()
!
!-----------------------------------------------------------------------------
!   Function Description: Setup Redundant NV Block, reset write retries
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupRedundant(void)
{
    /* updates NvState for current block and changes active block */
    NvM_ActUpdateNvState();

    /* set the dataindex to process the second block */
    NvM_CurrentBlockInfo_t.NvIdentifier_u16 |= 0x01u;

    /* reset retry counter */
    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 = 0u;
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActSetupOther()
!
!-----------------------------------------------------------------------------
!   Function Description: Setup the other NV Block at redundant blocks, reset 
!                         write retries
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActSetupOther(void)
{
     /* reset retry counter */
    NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 = 0u;

    /* activate the inactive NvBlock */
    NvM_CurrentBlockInfo_t.NvIdentifier_u16 ^= 0x0001u;
    
    NvM_ActUpdateNvState();
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActUpdateNvState()
!
!-----------------------------------------------------------------------------
!   Function Description: updates NvState dependent on LastResult and marks
!                         the other NvBlock as active, if it is a redundant
!                         block
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActUpdateNvState(void)
{
    uint8 NvBlockState_u8;
    
    switch (NvM_CurrentBlockInfo_t.LastResult_t)
    {
        case (NVM_REQ_OK):
            /* set NvBlock state uptodate */
            NvBlockState_u8 = NVM_NVBLOCK_STATE_UPTODATE;
            break;

        case (NVM_REQ_NV_INVALIDATED):
            /* set NvBlock state outdated */
            NvBlockState_u8 = NVM_NVBLOCK_STATE_OUTDATED;
            break;

        default:
            /* set NvBlock state defect */
            NvBlockState_u8 = NVM_NVBLOCK_STATE_DEFECT;
            break;
    }

    /* save NvBlock state */
    NvM_IntCreateNvState(&NvM_CurrentBlockInfo_t.NvState_u8, NvBlockState_u8);

    /* mark the other NvBlock active */
    NvM_CurrentBlockInfo_t.NvState_u8 ^= NVM_NVBLOCK_STATE_SEC_ACTIVE;
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_IntCreateNvState(uint8 &NvState, uint8 NewState)
!
!-----------------------------------------------------------------------------
!   Function Description: creates current NvState and marks the other one
!                         active
!-----------------------------------------------------------------------------
!   Parameter:     NvState, NewState
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_IntCreateNvState(P2VAR(uint8, AUTOMATIC, NVM_PRIVATE_DATA) NvState, 
                                                         uint8 NewState)
{
    uint8 shift;

    /* determine shift factor */
    if((*NvState & NVM_NVBLOCK_STATE_SEC_ACTIVE) != 0)
    {
        shift = NVM_SEC_NVBLOCK_STATE_SHIFT;        
    }
    else
    {
        shift = NVM_PRI_NVBLOCK_STATE_SHIFT;        
    }

    /* set state of current NvBlock to 0x00 */
    *NvState &= (NVM_NVBLOCK_STATE_UNKNOWN << shift) ^ 0xFFu;

    /* set new state */
    *NvState |= (uint8)(NewState << shift);
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActGetMultiBlockJob()
!
!-----------------------------------------------------------------------------
!   Function Description: "Translate" the API Flags into the internal ServiceId
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetMultiBlockJob(void)
 {
    const uint8 multiJobFlags = NvM_ApiFlags_u8;

    NvM_CurrentJob_t.JobBlockId_t   = 0x00u;
    NvM_CurrentJob_t.RamAddr_t      = NULL_PTR; /* this is essential for further processing! */

    if (multiJobFlags & NVM_APIFLAG_WRITE_ALL_SET)
    {
        NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_WRITE_ALL;
    }
    else if (multiJobFlags & NVM_APIFLAG_READ_ALL_SET)
    {
        NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_READ_ALL;
    }
    else
    {
        /* Nothing to do, should not happen, since this function will be called, if
         * NvM_QryHighMultiJob returned true --> one flag must be set */
    }
 }

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActTestBlockBlank()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActTestBlockBlank(void)
{
    /* read one byte of the block to a temp buffer to see if the nv
     * is still empty. 
     */

    if(E_OK ==
        MemIf_Read((uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8,
                 NvM_CurrentBlockInfo_t.NvIdentifier_u16,
                 0u,
                 &NvM_TestBuffer_u8,
                 1u))
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_PENDING;
    }
    else
    {
        NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActValidateRam()
!
!-----------------------------------------------------------------------------
!   Function Description: If current RAM Block is permanent,
!                         mark it valid and unchanged.
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActValidateRam(void)
{
    /* Are we operating on the permanent RAM block? */
    if(NvM_CurrentBlockInfo_t.RamAddr_t == NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockDataAddr_t)
    {
       #if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
            /* only make valid, do not change the CHANGED flag) */
            NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= NVM_STATE_VALID_SET;
            NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 &= NVM_STATE_CHANGED_CL;
        #else
            /* make valid AND changed, because the application cannot do it. */
            NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |= (NVM_STATE_VALID_SET | NVM_STATE_CHANGED_SET);
        #endif
    }
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActWait()
!
!-----------------------------------------------------------------------------
!   Function Description: Perform a specific action
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActWait(void)
{
    NvM_CurrentBlockInfo_t.InternalFlags_u8 |= NVM_INTFLAG_WAIT_SET;
}


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ActCopyNvDataToBuf()
!
!-----------------------------------------------------------------------------
!   Function Description: Copies Block's NVData to internal Buffer
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActCopyNvDataToBuf(void)
{
  /* for larger values of NvM_NoOfCrcBytes_u16, scale down the number to be processed
                -> "share" CPU time between copying and calculation */
#if(STD_ON == NVM_CRC_INT_BUFFER)
    if(NvM_InternalCopyDataAndCalcCrc(&NvM_CurrentBlockInfo_t, NvM_InternalBuffer_au8, NvM_CurrentBlockInfo_t.RamAddr_t))
    {
        /* if copy and crc calculation finished, we have tocopy CRC value into
         * block's RAM CRC-Buffer (if the configured, permanent RAM Block is being used) as well as into internal buffer
        */
        const NvM_BlockDescrPtrType descr_pt = NvM_CurrentBlockInfo_t.Descriptor_pt;


        NvM_CrcJob_CopyToBuffer(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);

        /* If we're not processing a DCM Block alias, we have to copy the CRC into block's CRC buffer.
        * A DCM block does not have a RAM CRC buffer - the previous call copied the CRC into internal buffer */
        if(NvM_CurrentBlockInfo_t.RamAddr_t == descr_pt->RamBlockDataAddr_t)
        {
            NvM_CrcJob_ExportBufferedValue(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, descr_pt->RamBlockCrcAddr_t); 
        }
    }

#else /* (NVM_CRC_INT_BUFFER == STD_ON) */
   /* => no internal buffering */
   NvM_CrcJob_Process(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_NoOfCrcBytes_u16);

   if(!NvM_CrcJob_isBusy(&NvM_CurrentBlockInfo_t.BlockCrcJob_t))
   { /* if crc calculation finished, we have to append CRC value to block's RAM data */
       NvM_CrcJob_CopyToBuffer(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);
   }
#endif
}

STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_ActProcessCrc(void)
{
    NvM_CrcJob_Process(&NvM_CurrentBlockInfo_t.BlockCrcJob_t, NvM_NoOfCrcBytes_u16);
}

STATIC FUNC(void, NVM_PRIVATE_CODE) NvM_UpdateConfigIdBlock(void)
{
    NvM_CurrentBlockInfo_t.RamAddr_t[0] = NvM_CompiledConfigId_t.Bytes_au8[0];
    NvM_CurrentBlockInfo_t.RamAddr_t[1] = NvM_CompiledConfigId_t.Bytes_au8[1];

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    NvM_CrcQueueJob(1u);
#endif

    NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 |=
                    (NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET);
}

#if(NVM_CRC_INT_BUFFER == STD_ON)

static FUNC(boolean, NVM_PRIVATE_CODE) NvM_InternalCopyDataAndCalcCrc(
    NvM_BlockInfoPtrType info_pt, NvM_RamAddressType destPtr, NvM_ConstRamAddressType srcPtr)
{
    /* Decrease number of bytes to be processed at once during CRC calculation for larger values of NvM_NoOfCrcBytes.
       => We are copying AND calculating CRC! */
    const uint16_least maxBytes = (NvM_NoOfCrcBytes_u16 > 32u) ? (NvM_NoOfCrcBytes_u16 >> 1) : NvM_NoOfCrcBytes_u16;
  
    /* Calculation of bytes to be processed also depends on currently remaining bytes.
     * Unfortunately we have to compute it twice: here for data copy. In NvM_CrcJob_Process for CRC calculation */
    uint16_least currLength =  (info_pt->ByteCount_u16 < maxBytes) ? info_pt->ByteCount_u16 : maxBytes;

    info_pt->ByteCount_u16 -= currLength;

    destPtr = &destPtr[info_pt->ByteCount_u16];
    srcPtr = &srcPtr[info_pt->ByteCount_u16];

    do
    {
        --currLength;
        destPtr[currLength] = srcPtr[currLength];
    }
    while(currLength > 0);

    NvM_CrcJob_Process(&info_pt->BlockCrcJob_t, maxBytes);

    return (boolean)(!NvM_CrcJob_isBusy(&NvM_CurrentBlockInfo_t.BlockCrcJob_t));
}
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"


/*---- End of File ---------------------------------------------------------*/
