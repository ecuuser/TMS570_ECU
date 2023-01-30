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
 *         File:  NvM_Qry.c
 *      Project:  MemService_AsrNvM
 *       Module:  NvM - Submodule Qry (Query functions)
 *    Generator:  -
 *
 *  Description:  This sub-module implements the queries to be executed to evaluate
 *                the conditions for a state transition
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
 *  INCLUDE OF CONFIGURATION (PUBLIC SECTION)
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
#include "NvM_Qry.h"


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
#if (     (NVM_QRY_MAJOR_VERSION != (3u)) \
       || (NVM_QRY_MINOR_VERSION != (7u)))
  #error "Version numbers of NvM_Qry.c and NvM_Qry.h are inconsistent!"
#endif

#if (     (NVM_CFG_MAJOR_VERSION != (3u)) \
       || (NVM_CFG_MINOR_VERSION != (7u)))
  #error "Version numbers of NvM_Qry.c and NvM_Cfg.h are inconsistent!"
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

STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryBlockWriteAll(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCancelWriteAll(void);
#if(NVM_KILL_WRITEALL_API == STD_ON)
    STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteAllKilled(void);
#endif

STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcMatch(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcBusy(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHasRom(void);

STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastResultOk(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMainFsmRunning(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMultiJob(void);

STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNvBusy(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMemHwaBusy(void);

#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRamValid(void);
#endif

#if(NVM_DYNAMIC_CONFIGURATION == STD_ON)
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryExtRuntime(void);
#endif

STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRedundantBlock(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySkipBlock(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySubFsmRunning(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryTrue(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteBlockOnce(void);
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteRetriesExceeded(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"
/**********************************************************************************************************************
 *  INTERNAL MODULE GLOBAL VARIABLES
 *********************************************************************************************************************/

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* the query function table, indexed by NvM_StateQueryType */
CONST(NvM_QryFctPtrType, NVM_PRIVATE_CONST) NvM_QueryTable_ap[NVM_QRY_ID_TRUE + 1] =
{
    NvM_QryBlockWriteAll,
    NvM_QryCancelWriteAll,
#if(NVM_KILL_WRITEALL_API == STD_ON)
    NvM_QryWriteAllKilled,
#endif
    NvM_QryCrcBusy,
    NvM_QryCrcMatch,
#if(NVM_DYNAMIC_CONFIGURATION == STD_ON)
    NvM_QryExtRuntime,
#endif
    NvM_QryHasRom,
    NvM_QryLastBlockDone,
    NvM_QryLastResultOk,
    NvM_QryMainFsmRunning,
    NvM_QryMultiJob,
#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
    NvM_QryNormalPrioJob,
    #if (NVM_JOB_PRIORISATION == STD_ON)
        NvM_QryHighPrioJob,
    #endif
#endif
    NvM_QryNvBusy,
    NvM_QryMemHwaBusy,
#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    NvM_QryRamValid,
#endif
    NvM_QryRedundantBlock,
    NvM_QrySkipBlock,
    NvM_QrySubFsmRunning,
    NvM_QryWriteBlockOnce,
    NvM_QryWriteRetriesExceeded,  
    NvM_QryTrue
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


/**********************************************************************************************************************
 *  IMPLEMENTATION
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryBlockWriteAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Check if the block shall be written during
!                         NvM_WriteAll(). Conditions:
!                         * not write protected
!                         * permanent RAM block
!                         * Ram valid
!                         * not locked
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryBlockWriteAll(void)
{
#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    return (boolean)(((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & 
               (NVM_WR_PROT_SET | NVM_LOCK_STAT_SET | NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET)) == 
                                              (NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET)) &&
            (NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockDataAddr_t != NULL_PTR));
#else
    return (boolean)(((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & NVM_WR_PROT_SET
                            & NVM_LOCK_STAT_SET) == 0) &&
            (NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockDataAddr_t != NULL_PTR));
#endif
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryCancelWriteAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Test a specific condition
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCancelWriteAll(void)
{
    return (boolean)(NvM_ApiFlags_u8 & NVM_APIFLAG_CANCEL_WR_ALL_SET);
}

#if(NVM_KILL_WRITEALL_API == STD_ON)
/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryWriteAllKilled
!
!-----------------------------------------------------------------------------
!   Function Description: Test a specific condition
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteAllKilled(void)
{
    return (boolean)(((NvM_ApiFlags_u8 & NVM_APIFLAG_KILL_WR_ALL_SET) != 0) &&
                     (NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_WRITE_ALL));
}
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryCrcMatch()
!
!-----------------------------------------------------------------------------
!   Function Description: returns true if the recalculated crc matches the
!                         one read from the nv area
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcMatch(void)
{
    return (boolean)NvM_CrcJob_Compare(&NvM_CurrentBlockInfo_t.BlockCrcJob_t); 
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryCrcBusy()
!
!-----------------------------------------------------------------------------
!   Function Description: Test if the crc calculation for the current job is
!                         not finished yet
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcBusy(void)
{
    /* is the crc calculation not finished yet? */
    return (boolean)NvM_CrcJob_isBusy(&NvM_CurrentBlockInfo_t.BlockCrcJob_t);
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryHasRom()
!
!-----------------------------------------------------------------------------
!   Function Description: Returns true if the block has rom defaults or an
!                         initialization callback
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHasRom(void)
{
    return (uint8)((NvM_CurrentBlockInfo_t.Descriptor_pt->defaults_pt != NULL_PTR));
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryLastBlockDone()
!
!-----------------------------------------------------------------------------
!   Function Description: Returns true if the last block of NvM_WriteAll() or
!                         NvM_ReadAll() is finished.
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone(void)
{
    return (boolean)(NvM_CurrentJob_t.JobBlockId_t >= NvM_NoOfBlockIds_t);
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryLastResultOk()
!
!-----------------------------------------------------------------------------
!   Function Description: returns true if the last MemIf job was successful
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastResultOk(void)
{
    return (boolean)(NVM_REQ_OK == NvM_CurrentBlockInfo_t.LastResult_t);
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryMainFsmRunning()
!
!-----------------------------------------------------------------------------
!   Function Description: Test if a main job is running
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMainFsmRunning(void)
{
    return (boolean)(NVM_STATE_FSM_FINISHED != NvM_JobMainState_t);
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryMultiJob()
!
!-----------------------------------------------------------------------------
!   Function Description: Test if a multi job has been requested
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMultiJob(void)
{
    return (boolean)((NvM_ApiFlags_u8 & (NVM_APIFLAG_WRITE_ALL_SET | NVM_APIFLAG_READ_ALL_SET)) != 0);
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryNvBusy()
!
!-----------------------------------------------------------------------------
!   Function Description: Test if the MemIf is busy
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNvBusy(void)
{
    const uint8 deviceId = (uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8;

#if(STD_ON == NVM_POLLING_MODE)
    uint8 retVal = FALSE;

    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_PENDING)
    {
        if (MEMIF_BUSY == MemIf_GetStatus(deviceId))
        {
            retVal = TRUE;
        }
        else
        {
            switch(MemIf_GetJobResult(deviceId))
            {
                case MEMIF_JOB_OK:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
                    break;

                case MEMIF_BLOCK_INCONSISTENT:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_INTEGRITY_FAILED;
                    break;

                case MEMIF_BLOCK_INVALID:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NV_INVALIDATED;
                    break;

                default:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
            }
        }
    }
    return retVal;
#else
    return (boolean)(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_PENDING);
#endif
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryMemHwaBusy()
!
!-----------------------------------------------------------------------------
!   Function Description: Check, whether the MemHwa is BUSY or BUSY_INTERNAL
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMemHwaBusy(void)
{
    const MemIf_StatusType MemHwaStatus = MemIf_GetStatus(MEMIF_BROADCAST_ID);

    return (boolean)((MemHwaStatus == MEMIF_BUSY) || (MemHwaStatus == MEMIF_BUSY_INTERNAL));
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryExtRuntime()
!
!-----------------------------------------------------------------------------
!   Function Description: Test if the rom data of this block shall be read
!                         during NvM_ReadAll(). Condition:
!                         * dynamic mismatch flag set and
!                         * block is not resistant to changed sw and
!                         * has either a rom block or an init callback
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryExtRuntime(void)
{
    return (boolean)((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_DYN_MISMATCH_SET) &&
        ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_RESISTANT_TO_CHANGED_SW_ON) == 0));
}
#endif
/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryRedundantBlock()
!
!-----------------------------------------------------------------------------
!   Function Description: Test if the current block has been configured 
!                         redundant, and the redundant NV bock is not selected.
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRedundantBlock(void)
{
    return (boolean)((NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT) &&
        ((NvM_CurrentBlockInfo_t.NvIdentifier_u16 & 0x0001u) == 0));
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QrySkipBlock()
!
!-----------------------------------------------------------------------------
!   Function Description: Test a specific condition
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySkipBlock(void)
{
    return (boolean)(((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_SELECT_BLOCK_FOR_READALL_ON) == 0) ||                
        ((NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_DATASET) != 0));
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QrySubFsmRunning()
!
!-----------------------------------------------------------------------------
!   Function Description: Test a specific condition
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySubFsmRunning(void)
{
    return (boolean)(NVM_STATE_FSM_FINISHED != NvM_JobSubState_t);
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryTrue()
!
!-----------------------------------------------------------------------------
!   Function Description: Test a specific condition
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryTrue(void)
{
    return TRUE;
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryWriteBlockOnce()
!
!-----------------------------------------------------------------------------
!   Function Description: Returns true if the block can only be written once
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteBlockOnce(void)
{
#if(NVM_DYNAMIC_CONFIGURATION == STD_ON)
    const boolean extRuntime = NvM_QryExtRuntime();
#else
    const boolean extRuntime = FALSE;
#endif

    return (boolean)((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_BLOCK_WRITE_BLOCK_ONCE_ON) &&
             (!extRuntime));
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryWriteRetriesExceeded()
!
!-----------------------------------------------------------------------------
!   Function Description: Test a specific condition
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteRetriesExceeded(void)
{
    /* the initial try is also counted as retry. Therfore the total number of
       write retries may reach the configured number of attempts. */
    return (boolean)(NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 > NvM_NoOfWrAttempts_u8);
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QryRamValid()
!
!-----------------------------------------------------------------------------
!   Function Description: Test if the ram of the block is still valid or if the
!                         block is locked ==> Read during ReadAll
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   boolean -> TRUE/FALSE
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    STATIC FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRamValid(void)
    {
        return (boolean)((NvM_CurrentBlockInfo_t.RamAddr_t != NULL_PTR) &&
            ((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & NVM_STATE_VALID_SET) != 0) 
            && ((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & NVM_LOCK_STAT_SET) == 0));
    }
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*---- End of File ---------------------------------------------------------*/
