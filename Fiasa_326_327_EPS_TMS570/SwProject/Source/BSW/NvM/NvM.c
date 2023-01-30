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
 *         File:  NvMS.c
 *      Project:  MemService_AsrNvM
 *       Module:  NvM
 *    Generator:  -
 *
 *  Description:  The NVRAM Manager ensure the data storage and maintenance of NV data. 
 *                The NVRAM Manager shall be able to administrate the NV data of an EEPROM 
 *                and/or a FLASH EEPROM emulation device.
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

#ifndef V_SUPPRESS_EXTENDED_VERSION_CHECK
#include "v_ver.h"
#endif

/**********************************************************************************************************************
 *  MODULE HEADER INCLUDES (INCLUDE PUBLIC AND PART OF NvM_Cfg.h)
 *********************************************************************************************************************/
#include "NvM.h"

#include "NvM_PrivateCfg.h"

/* include the central internal include */
#include "NvM_JobProc.h"

/**********************************************************************************************************************
 *  INCLUDES OF NVM SUBMODULES
 *********************************************************************************************************************/
#include "NvM_Act.h"
#include "NvM_Qry.h"
#include "NvM_Queue.h"
#include "NvM_Crc.h"

/**********************************************************************************************************************
 *  CALLBACK ROUTINES DECLARATIONS OF THE OWN MODULE
 *********************************************************************************************************************/
#include "NvM_Cbk.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (  (NVM_SW_MAJOR_VERSION != (3u)) \
    || (NVM_SW_MINOR_VERSION != (7u)) \
    || (NVM_AR_MAJOR_VERSION != (2u)) \
    || (NVM_AR_MINOR_VERSION != (2u)) \
    || (NVM_AR_PATCH_VERSION != (0u)))

    #error "Version numbers of NvM.c and NvM.h are inconsistent!"

#endif

#if (    (NVM_CFG_MAJOR_VERSION != (3u)) \
      || (NVM_CFG_MINOR_VERSION != (7u)))
    #error "Version numbers of NvM.c and NvM_Cfg.h are inconsistent!"
#endif

#if (    (NVM_PRIV_CFG_MAJOR_VERSION != (3u)) \
      || (NVM_PRIV_CFG_MINOR_VERSION != (7u)))
    #error "Version numbers of NvM.c and NvM_PrivateCfg.h are inconsistent!"
#endif

#if ((NVM_TYPES_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
       || (NVM_TYPES_MINOR_VERSION != NVM_SW_MINOR_VERSION))
  #error "Version numbers of NvM.c and NvM_Types.h are inconsistent!"
#endif

#if ((NVM_ACT_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
       || (NVM_ACT_MINOR_VERSION != NVM_SW_MINOR_VERSION))
  #error "Version numbers of NvM.c and NvM_Act.h are inconsistent!"
#endif

#if ((NVM_QRY_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
       || (NVM_QRY_MINOR_VERSION != NVM_SW_MINOR_VERSION))
  #error "Version numbers of NvM.c and NvM_Qry.h are inconsistent!"
#endif

#if ((NVM_JOBPROC_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
       || (NVM_JOBPROC_MINOR_VERSION != NVM_SW_MINOR_VERSION))
  #error "Version numbers of NvM.c and NvM_JobProc.h are inconsistent!"
#endif

#if ((NVM_CRC_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
    || (NVM_CRC_MINOR_VERSION != NVM_SW_MINOR_VERSION))
  #error "Version numbers of NvM.c and NvM_Crc.h are inconsistent!"
#endif

#if ((NVM_QUEUE_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) \
       || (NVM_QUEUE_MINOR_VERSION != NVM_SW_MINOR_VERSION))
  #error "Version numbers of NvM.c and NvM_Queue.h are inconsistent!"
#endif

#include "Crc.h" /* always needed, since the config Block has a CRC */


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

#define NVM_START_SEC_VAR_FAST_8BIT
#include "MemMap.h"

    /* API flags - which are accessable from API */
    VAR(uint8, NVM_FAST_DATA) NvM_ApiFlags_u8;

#define NVM_STOP_SEC_VAR_FAST_8BIT
#include "MemMap.h"

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

   static VAR(struct NvM_CrcJobStruct, NVM_PRIVATE_DATA) NvM_AsyncCrcJob_t;

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#ifndef V_SUPPRESS_EXTENDED_VERSION_CHECK
    /* 
    The name of this const variable is defined via v_ver.h and depends on the 
    version of the C file. The value of the const variable is also defined 
    externally and is used for consistency checks, too. 
    */
    CONST( uint32, NVM_PUBLIC_CONST ) MEMSERVICE_ASRNVM_LIB_SYMBOL = MEMSERVICE_ASRNVM_LIB_VERSION;
#endif

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/**********************************************************************************************************************
 *  INTERNAL MODDULE GLOBAL VARIABLES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  IMPLEMENTATION
 **********************************************************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h"

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_Init()
!
!-----------------------------------------------------------------------------
!   Function Description: Service for basic NVRAM manager initialisation:
!                         initializes internal structures and the state
!                         machines.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   none
!   Parameter (Output):  none
!   Returnvalue:         none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PUBLIC_CODE) NvM_Init(void)
{
    /* local variables */
    uint16_least NvM_BlockCount_u16loc;

    #if(NVM_DEV_ERROR_DETECT == STD_ON)
        /* Perform RAM and ROM block length checks.                          *
         * It is essential that always both checks are perfomed, sinc it     *
         * eases debugging in case of errors                                 *
         * Since the DET often ends up in an endless loop, we also defer     *
         * error reporting.                                                  */
        const uint8_least RamBlocksFailed = NvM_CfgCheckRamBlockLengths();
        const uint8_least RomBlocksFailed = NvM_CfgCheckRomBlockLengths();

        if((RamBlocksFailed != 0) || (RomBlocksFailed != 0))
        {
            if(RamBlocksFailed != 0)
            {
                NvM_Errorhook(NVM_INIT, NVM_E_RAM_BLOCK_LENGTH);
            }

            if(RomBlocksFailed != 0)
            {
                NvM_Errorhook(NVM_INIT, NVM_E_ROM_BLOCK_LENGTH);
            }
            NvM_JobMainState_t = NVM_STATE_UNINIT;

            return; /* stay unitialized */
        }
    #endif

    #if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
        /* no queuing is used in api config class 1 */
        NvM_QueueInit();
    #endif

#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    NvM_CrcQueueInit();

    /* initialize crc Job with "dummy job" -> CRC for Block 0. It will never be executed, due to its Block Descriptor values */
    NvM_CrcJob_Create(&NvM_AsyncCrcJob_t, &NvM_BlockDescriptorTable_at[0], NULL_PTR);
#endif
    NvM_ApiFlags_u8 = 0;

    /* set the ram attribute of block 0 to ok */
    NvM_BlockMngmtArea_at[0u].NvRamErrorStatus_u8 = NVM_REQ_OK;

    /* set all data indices to zero */
    NvM_BlockCount_u16loc = NvM_NoOfBlockIds_t;
    do
    {
        --NvM_BlockCount_u16loc;
        NvM_BlockMngmtArea_at[NvM_BlockCount_u16loc].NvDataIndex_t = 0;
    }
    while(NvM_BlockCount_u16loc > 0);

    /* initialize DCM block Mngmt area */
    NvM_DcmBlockMngmt_t.NvDataIndex_t = 0;
    NvM_DcmBlockMngmt_t.NvRamAttributes_u8 = 0u;
    NvM_DcmBlockMngmt_t.NvRamErrorStatus_u8 = 0u;
        
    NvM_JobProcInit();
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_SetDataIndex(BlockId, DataIndex)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall set the index to associate a
!   dataset NV/ROM block with its corresponding RAM block.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId, DataIndex
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (STD_ON == NVM_USE_DATASETS)
FUNC(void, NVM_PUBLIC_CODE) NvM_SetDataIndex(NvM_BlockIdType BlockId, uint8 DataIndex)
{
    /* local ram management area pointer */
    /* BlockId has to be used here before BlockId check to get the pointer. But the pointer is only
      used after BlockId check. */
    const NvM_RamMngmtPtrType NvM_RamMngt_ptloc = 
      (BlockId & NVM_DCM_BLOCK_OFFSET) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);

    const NvM_BlockIdType orgBlockId = (BlockId & (~NVM_DCM_BLOCK_OFFSET));


    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_SET_DATA_INDEX, NVM_E_NOT_INITIALIZED);
            return;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif


    /* Check ParamConfig */
    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID) /* Debug Mode */
        /* is the block id valid? */
        if ((NvM_NoOfBlockIds_t <= orgBlockId) || (0u == orgBlockId))
        {
            NvM_Errorhook(NVM_SET_DATA_INDEX, NVM_E_PARAM_BLOCK_ID);
            return;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

     /* check pending */
    #if (STD_ON == NVM_CFG_CHK_BLOCK_PENDING)
        if (NVM_REQ_PENDING == NvM_RamMngt_ptloc->NvRamErrorStatus_u8)
        {
            NvM_Errorhook(NVM_SET_DATA_INDEX, NVM_E_BLOCK_PENDING);
            return;
        }
        else
        {
           /* nothing to do */
        }
    #endif

    /* check block management type */
    if ((NvM_BlockDescriptorTable_at[orgBlockId].MngmtType_t & NVM_BLOCK_DATASET) != 0)
    {
        #if (STD_ON == NVM_CFG_CHK_PARAM_DATAINDEX)
            if (NvM_BlockDescriptorTable_at[orgBlockId].NvBlockCount_u8 <= DataIndex)
            {
                NvM_Errorhook(NVM_SET_DATA_INDEX, NVM_E_PARAM_BLOCK_DATA_IDX);
                return;
            }
            else
            {
                /* nothing to do */
            }
        #endif

        /* do SetDataIndex */
        NvM_RamMngt_ptloc->NvDataIndex_t = DataIndex;
    }
    else /* all other types */
    {
        #if (STD_ON == NVM_CFG_CHK_MNGMT_TYPE) /* Debug Mode */
            NvM_Errorhook(NVM_SET_DATA_INDEX, NVM_E_PARAM_BLOCK_TYPE);
            return;
        #endif
        /* don't set DataIndex!!!!! */
    } /* end check Block Management Type */
} /* End function NvM_SetDataIndex() */
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_GetDataIndex(BlockId)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall get the current index
!   (association) of a dataset NV/ROM block with its corresponding
!   RAM block.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  DataIndexPtr
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (STD_ON == NVM_USE_DATASETS)
FUNC(void, NVM_PUBLIC_CODE) NvM_GetDataIndex
    (
        NvM_BlockIdType BlockId,
        P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DataIndexPtr
    )
{
    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_GET_DATA_INDEX, NVM_E_NOT_INITIALIZED);
            return;
        }
        else
        {
            /* nothing to do in here */
        }
    #endif

    /* Check ParamConfig */
    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID) /* Debug Mode */
        /* is the block id valid? */
        if ((NvM_NoOfBlockIds_t <= (BlockId & (~NVM_DCM_BLOCK_OFFSET))) || (0u == (BlockId & (~NVM_DCM_BLOCK_OFFSET))))
        {
            NvM_Errorhook(NVM_GET_DATA_INDEX, NVM_E_PARAM_BLOCK_ID);
            return;
        }
        else
        {
           /* nothing to do in here */
        }
    #endif

    /* check pointer */
    #if (STD_ON == NVM_CFG_CHK_PARAM_POINTER)
        if (NULL_PTR == DataIndexPtr)
        {
            NvM_Errorhook(NVM_GET_DATA_INDEX, NVM_E_PARAM_DATA);
            return;
        }
        else
        {
           /* nothing to do */
        }
    #endif


    /* check block management type */
    /* apply only for Dataset */
    if ((NVM_BLOCK_DATASET & NvM_BlockDescriptorTable_at[BlockId & (~NVM_DCM_BLOCK_OFFSET)].MngmtType_t) == 0)
    {
        #if (STD_ON == NVM_CFG_CHK_MNGMT_TYPE) /* Debug Mode */
            NvM_Errorhook(NVM_GET_DATA_INDEX, NVM_E_PARAM_BLOCK_TYPE);
        #endif /* end check in debug mode */
        
        *DataIndexPtr = 0;
    }
    else
    {
        if(0 == (BlockId & NVM_DCM_BLOCK_OFFSET))
        {
            /* get DataIndex, the descriptor is valid */
            *DataIndexPtr = NvM_BlockMngmtArea_at[BlockId].NvDataIndex_t;
        }
        else
        {
            /* get DataIndex, the descriptor is valid */
            *DataIndexPtr = NvM_DcmBlockMngmt_t.NvDataIndex_t;
        }
    }

} /* End function NvM_GetDataIndex() */
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_SetBlockProtection(BlockId)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall set/reset the write protection for
!   the NV block. This shall be done by setting the write lock attribute in the
!   administrative part of the corresponding RAM block. Any further write/erase
!   requests to the NVRAM block shall be rejected
!   synchronously if the NV block write protection is set. The data area of the
!   RAM block shall remain writeable in case of write protection.
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId, ProtectionEnabled
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_3 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_3))

FUNC(void, NVM_PUBLIC_CODE) NvM_SetBlockProtection(NvM_BlockIdType BlockId, boolean ProtectionEnabled)
{
    /* local desc. pointer */
    /* BlockId has to be used here before BlockId check to get the pointer. But the pointer is only
      used after BlockId check. */
    const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = 
      (BlockId & NVM_DCM_BLOCK_OFFSET) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);

    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_SET_BLOCK_PROTECTION, NVM_E_NOT_INITIALIZED);
            return;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* Check ParamConfig */
    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID) /* Debug Mode */
        /* is the block id valid? */
        if ((NvM_NoOfBlockIds_t <= (BlockId & (~NVM_DCM_BLOCK_OFFSET))) || (0u == (BlockId & (~NVM_DCM_BLOCK_OFFSET))))
        {
            NvM_Errorhook(NVM_SET_BLOCK_PROTECTION, NVM_E_PARAM_BLOCK_ID);
            return;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* check pending */
    #if (STD_ON == NVM_CFG_CHK_BLOCK_PENDING)
        if (NVM_REQ_PENDING == NvM_RamMngmt_ptloc->NvRamErrorStatus_u8)
        {
            NvM_Errorhook(NVM_SET_BLOCK_PROTECTION, NVM_E_BLOCK_PENDING);
            return;
        }
        else
        {
           /* nothing to do */
        }
    #endif

    /* check the block protection */


    /* is the block write once? */
    if ((NvM_BlockDescriptorTable_at[BlockId & (~NVM_DCM_BLOCK_OFFSET)].Flags_u8 & NVM_BLOCK_WRITE_BLOCK_ONCE_ON) != 0)
    {
        NvM_Errorhook(NVM_SET_BLOCK_PROTECTION, NVM_E_BLOCK_CONFIG);
        return;
    }
    else
    {
        /* nothing to do */
    }

    NvM_EnterCriticalSection();
    /* shall the write protection be enabled? */
    if (ProtectionEnabled)
    {
        NvM_RamMngmt_ptloc->NvRamAttributes_u8 |= NVM_WR_PROT_SET;
    }
    else
    {
        NvM_RamMngmt_ptloc->NvRamAttributes_u8 &= NVM_WR_PROT_CL;
    }
    NvM_ExitCriticalSection();
}
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_GetErrorStatus(BlockId)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall read the block dependent error/
!   status information in the administrative part of a RAM block.The
!   status/error information shall be set by a former or current asynchronous
!   request.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  NvM_RequestResultType
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PUBLIC_CODE) NvM_GetErrorStatus
    (
        NvM_BlockIdType BlockId,
        P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr
    )
{
    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_GET_ERROR_STATUS, NVM_E_NOT_INITIALIZED);
            /* return error indicating request result */
            return;
        }
        else
        {
            /* nothing to do in here */
        }
    #endif

    /* Check ParamConfig */
    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID) /* Debug Mode */
        /* is the block id valid? */
        if (NvM_NoOfBlockIds_t <= (BlockId & (~NVM_DCM_BLOCK_OFFSET)))
        {
            NvM_Errorhook(NVM_GET_ERROR_STATUS, NVM_E_PARAM_BLOCK_ID);
            /* because it may be dangerous to use the BlockDescriptor
             * which in fact does not exist, we return immediately
             */
            return;
        }
        else
        {
            /* nothing to do in here */
        }
    #endif

    /* check pointer */
    #if (STD_ON == NVM_CFG_CHK_PARAM_POINTER)
        if (NULL_PTR == RequestResultPtr)
        {
            NvM_Errorhook(NVM_GET_ERROR_STATUS, NVM_E_PARAM_DATA);
            return;
        }
        else
        {
           /* nothing to do */
        }
    #endif

    if(0 == (BlockId & NVM_DCM_BLOCK_OFFSET))
    {
      /* get the ErrorStatus */
      *RequestResultPtr = NvM_BlockMngmtArea_at[BlockId].NvRamErrorStatus_u8;
    }
    else
    {
      /* get the ErrorStatus */
      *RequestResultPtr = NvM_DcmBlockMngmt_t.NvRamErrorStatus_u8;
    }

} /* End function NvM_GetErrorStatus(BlockId)  */

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_GetVersionInfo(versioninfo)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall read the version info of the
!   module: Module Id, Vendor Id, Vendor specific version numbers
!-----------------------------------------------------------------------------
!   Parameter (Input):   none
!   Parameter (Output):  versioninfo
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (STD_ON == NVM_VERSION_INFO_API)
FUNC(void, NVM_PUBLIC_CODE) NvM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA) versioninfo)
{
    /* check pointer */
    #if (STD_ON == NVM_CFG_CHK_PARAM_POINTER)
        if (NULL_PTR == versioninfo)
        {
            NvM_Errorhook(NVM_GET_VERSION_INFO, NVM_E_PARAM_DATA);
            return;
        }
        else
        {
           /* nothing to do */
        }
    #endif

    versioninfo->vendorID         = NVM_VENDOR_ID;
    versioninfo->moduleID         = NVM_MODULE_ID;
    versioninfo->instanceID       = NVM_INSTANCE_ID;
    versioninfo->sw_major_version = NVM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = NVM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = NVM_SW_PATCH_VERSION;
}
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_SetRamBlockStatus(BlockId, BlockChanged)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall set a permanent RAM block to the
!   valid or the invalid state.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId, BlockChanged
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (STD_ON == NVM_SET_RAM_BLOCK_STATUS_API)
FUNC(void, NVM_PUBLIC_CODE) NvM_SetRamBlockStatus(NvM_BlockIdType BlockId, boolean BlockChanged)
{
    /* local ram management pointer */
    /* BlockId has to be used here before BlockId check to get the pointer. But the pointer is only
      used after BlockId check. */
    const NvM_BlockIdType orgBlockId = BlockId & (~NVM_DCM_BLOCK_OFFSET);
    const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = 
                (BlockId != orgBlockId) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);
    const NvM_BlockDescrPtrType NvM_Descr_ptloc = &NvM_BlockDescriptorTable_at[orgBlockId];

    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_SET_RAM_BLOCK_STATUS, NVM_E_NOT_INITIALIZED);
            return;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif


    /* Check ParamConfig */
    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID) /* Debug Mode */
        /* is the block id valid? */
        if ((NvM_NoOfBlockIds_t <= orgBlockId) || (0u == orgBlockId))
        {
            NvM_Errorhook(NVM_SET_RAM_BLOCK_STATUS, NVM_E_PARAM_BLOCK_ID);
            return;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

     /* check pending */
    #if (STD_ON == NVM_CFG_CHK_BLOCK_PENDING)
        if (NVM_REQ_PENDING == NvM_RamMngmt_ptloc->NvRamErrorStatus_u8)
        {
            NvM_Errorhook(NVM_SET_RAM_BLOCK_STATUS, NVM_E_BLOCK_PENDING);
            return;
        }
        else
        {
           /* nothing to do */
        }
    #endif

    /* is it a permanent block? */
    if (NULL_PTR != NvM_Descr_ptloc->RamBlockDataAddr_t)
    {
        NvM_EnterCriticalSection();
        if (BlockChanged)
        {
            /* set block changed and valid */
            NvM_RamMngmt_ptloc->NvRamAttributes_u8 |= (NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET);
            NvM_ExitCriticalSection();

            /* Block is configured with CALC_RAM_BLOCK_CRC? 
             *  (Crc itself is being checked before queuing) 
             *  We don't queue DCM block aliases for CRC calculation, as they don't actually have a 
             *  permanent RAM block assigned
             */
            if ((orgBlockId == BlockId) && (NvM_Descr_ptloc->Flags_u8 & NVM_CALC_RAM_BLOCK_CRC_ON))
            {
                /* queue the CRC calculation job */
                NvM_CrcQueueJob(orgBlockId);
            }
        }
        else
        {
            /* set block unchanged */
            NvM_RamMngmt_ptloc->NvRamAttributes_u8 &= (NVM_STATE_CHANGED_CL & NVM_STATE_VALID_CL);
            NvM_ExitCriticalSection();
        }
    }
    else
    {
        /* nothing to do */
    }
}
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ReadBlock(BlockId, NvM_DstPtr)
!
!-----------------------------------------------------------------------------
!   Function Description: Request to copy the data of the NV block to
!   its corresponding RAM block. If the block to be written is permanent a
!   NULL_PTR shall be given as parameter, otherwise a pointer to the ram
!   block shall be given.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  NvM_DstPtr
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_2 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_2))
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_ReadBlock(NvM_BlockIdType BlockId,
                             P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr)
{
    /* local ram management pointer */
    /* BlockId has to be used here before BlockId check to get the pointer. But the pointer is only
      used after BlockId check. */
    const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = 
      (BlockId & NVM_DCM_BLOCK_OFFSET) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);
    const NvM_BlockIdType orgBlockId = (BlockId & (~NVM_DCM_BLOCK_OFFSET));

  
    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_READ_BLOCK, NVM_E_NOT_INITIALIZED);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif


    /* Check ParamConfig */
    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID) /* Debug Mode */
        /* is the block id valid? */
        if ((NvM_NoOfBlockIds_t <= orgBlockId) || (0u == orgBlockId))
        {
            NvM_Errorhook(NVM_READ_BLOCK, NVM_E_PARAM_BLOCK_ID);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* check if the dataindex is not higher than the block count */
    #if (STD_ON == NVM_CFG_CHK_PARAM_DATAINDEX)
        /* check is only necessary for blocks of MngmtType DATASET or DATASET_ROM */
        if((NvM_BlockDescriptorTable_at[orgBlockId].MngmtType_t & NVM_BLOCK_DATASET) != 0)
        {
          if (NvM_RamMngmt_ptloc->NvDataIndex_t >= NvM_BlockDescriptorTable_at[orgBlockId].NvBlockCount_u8)
          {
              NvM_Errorhook(NVM_READ_BLOCK, NVM_E_PARAM_BLOCK_DATA_IDX);
              return E_NOT_OK;
          }
          else
          {
             /* nothing to do */
          }
        }
    #endif

    /* check pointer if it is a non permanent block */
    #if (STD_ON == NVM_CFG_CHK_PARAM_POINTER)
        if ((NULL_PTR == NvM_BlockDescriptorTable_at[orgBlockId].RamBlockDataAddr_t) && (NULL_PTR == NvM_DstPtr))
        {
            NvM_Errorhook(NVM_READ_BLOCK, NVM_E_PARAM_ADDRESS);
            return E_NOT_OK;
        }
        else
        {
           /* nothing to do */
        }
    #endif

    /* queue the read job (pending check will be performed there */
    if (NvM_QueueJob(BlockId, NVM_INT_FID_READ_BLOCK, NvM_DstPtr))
    {
        /* is the permanent RAM block requested? */
        if((NvM_DstPtr == NULL_PTR) || (NvM_DstPtr == NvM_BlockDescriptorTable_at[orgBlockId].RamBlockDataAddr_t))
        {
            NvM_EnterCriticalSection();
            /* set the ram block invalid and unchanged (=> invalid, but changed makes no sense!) */
            NvM_RamMngmt_ptloc->NvRamAttributes_u8 &= (NVM_STATE_VALID_CL & NVM_STATE_CHANGED_CL);
            NvM_ExitCriticalSection();
        }
        
        return E_OK;
    }
    else
    {
      /* queuing the job failed */
      return E_NOT_OK;
    }
}
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_WriteBlock(BlockId, NvM_SrcPtr)
!
!-----------------------------------------------------------------------------
!   Function Description: Request to copy the data of the RAM block to its
!   corresponding NV block. If the block to be written is permanent a NULL_PTR
!   shall be given as parameter, otherwise a pointer to the ram block shall be
!   given.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId, NvM_SrcPtr
!   Parameter (Output):  none
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_2 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_2))
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_WriteBlock
    (
        NvM_BlockIdType BlockId,
        P2CONST(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
    )
{
    /* local ram management pointer */
    /* BlockId has to be used here before BlockId check to get the pointer. But the pointer is only
      used after BlockId check. */
    const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = 
      (BlockId & NVM_DCM_BLOCK_OFFSET) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);
    const NvM_BlockIdType orgBlockId = (BlockId & (~NVM_DCM_BLOCK_OFFSET));

    
    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_WRITE_BLOCK, NVM_E_NOT_INITIALIZED);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }

    #endif

    /* Check ParamConfig */
    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID) /* Debug Mode */
        /* is the block id valid? */
        if ((NvM_NoOfBlockIds_t <= orgBlockId) || (0u == orgBlockId))
        {
            NvM_Errorhook(NVM_WRITE_BLOCK, NVM_E_PARAM_BLOCK_ID);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* check pointer if the block is non permanent */
    #if (STD_ON == NVM_CFG_CHK_PARAM_POINTER)
        if ((NULL_PTR == NvM_BlockDescriptorTable_at[orgBlockId].RamBlockDataAddr_t) && (NULL_PTR == NvM_SrcPtr))
        {
            NvM_Errorhook(NVM_WRITE_BLOCK, NVM_E_PARAM_ADDRESS);
            return E_NOT_OK;
        }
        else
        {
           /* nothing to do */
        }
    #endif

    /* check if the dataindex is not higher than the block count */
    #if (STD_ON == NVM_CFG_CHK_PARAM_DATAINDEX)
        /* check is only necessary for blocks of MngmtType DATASET or DATASET_ROM */
        if((NvM_BlockDescriptorTable_at[orgBlockId].MngmtType_t & NVM_BLOCK_DATASET) != 0)
        {
          if (NvM_RamMngmt_ptloc->NvDataIndex_t >= NvM_BlockDescriptorTable_at[orgBlockId].NvBlockCount_u8)
          {
              NvM_Errorhook(NVM_WRITE_BLOCK, NVM_E_PARAM_BLOCK_DATA_IDX);
              return E_NOT_OK;
          }
          else
          {
             /* nothing to do */
          }
        }
    #endif

    /* is the block write protected?
     * This check shall ALWAYS be performed.
     */
    if ((NvM_RamMngmt_ptloc->NvRamAttributes_u8 & NVM_WR_PROT_SET) != 0)
    {
        /* check the block protection */
        NvM_Errorhook(NVM_WRITE_BLOCK, NVM_E_NV_WRITE_PROTECTED);
        return E_NOT_OK;
    }

    /* is the block locked? */
    if((0 == (BlockId & NVM_DCM_BLOCK_OFFSET)) && ((NvM_RamMngmt_ptloc->NvRamAttributes_u8 & NVM_LOCK_STAT_SET) != 0))
    {
      /* check the block lock status without error notification to Det or Dem */        
      return E_NOT_OK;
    }

    /* queue the write job */
    if (NvM_QueueJob(BlockId, NVM_INT_FID_WRITE_BLOCK, (NvM_RamAddressType)NvM_SrcPtr))
    {
        /* ist a permanent RAM block ? */
        if((NvM_SrcPtr == NULL_PTR) || (NvM_SrcPtr == NvM_BlockDescriptorTable_at[orgBlockId].RamBlockDataAddr_t))
        {
            NvM_EnterCriticalSection();
            /* set the ram block status valid and changed */
            NvM_RamMngmt_ptloc->NvRamAttributes_u8 |= (NVM_STATE_VALID_SET | NVM_STATE_CHANGED_SET);
            NvM_ExitCriticalSection();        
        }
        return E_OK;
    }
    else
    { 
      /* queuing the job failed */
      return E_NOT_OK;
    }
}
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_RestoreBlockDefaults(BlockId, NvM_DstPtr)
!
!-----------------------------------------------------------------------------
!   Function Description: Request to restore the ROM block default data to
!   its corresponding RAM block. If the ram block is not permanent NvM_DstPtr
!   shall be used as output pointer, otherwise a NULL_PTR shall be handed.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  NvM_DstPtr
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_2 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_2))
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_RestoreBlockDefaults(NvM_BlockIdType BlockId,
                                        P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
    )
{
    /* local desc. pointer */
    /* BlockId has to be used here before BlockId check to get the pointer. But the pointer is only
      used after BlockId check. */
    const NvM_BlockDescrPtrType NvM_Descr_ptloc = &(NvM_BlockDescriptorTable_at[BlockId & (~NVM_DCM_BLOCK_OFFSET)]);
    /* local ram management pointer */
    /* BlockId has to be used here before BlockId check to get the pointer. But the pointer is only
      used after BlockId check. */
    const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = 
      (BlockId & NVM_DCM_BLOCK_OFFSET) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);
 

    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_RESTORE_BLOCK_DEFAULTS, NVM_E_NOT_INITIALIZED);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* Check ParamConfig */
    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID) /* Debug Mode */
        /* is the block id valid? */
        if ((NvM_NoOfBlockIds_t <= (BlockId & (~NVM_DCM_BLOCK_OFFSET))) || (0u == (BlockId & (~NVM_DCM_BLOCK_OFFSET))))
        {
            NvM_Errorhook(NVM_RESTORE_BLOCK_DEFAULTS, NVM_E_PARAM_BLOCK_ID);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* check pointer if the block is non permanent */
    #if (STD_ON == NVM_CFG_CHK_PARAM_POINTER)
        if ((NULL_PTR == NvM_Descr_ptloc->RamBlockDataAddr_t) && (NULL_PTR == NvM_DstPtr))
        {
            NvM_Errorhook(NVM_RESTORE_BLOCK_DEFAULTS, NVM_E_PARAM_ADDRESS);
            return E_NOT_OK;
        }
        else
        {
           /* nothing to do */
        }
    #endif

    /* check configuration (ROM defaults available) */
    #if (STD_ON == NVM_CFG_CHK_MNGMT_TYPE)

        /* is no rom block or a init callback available? */
        if (NULL_PTR == NvM_Descr_ptloc->defaults_pt)
        {
            NvM_Errorhook(NVM_RESTORE_BLOCK_DEFAULTS, NVM_E_BLOCK_CONFIG);
            return E_NOT_OK;
        }
        else
        {
            /* Ok, go on and restore */
        }

    #endif

    /* queue the restore job */
    if (NvM_QueueJob(BlockId, NVM_INT_FID_RESTORE_DEFAULTS, NvM_DstPtr))
    {
        
        /* permanent RAM block? */
        if((NvM_DstPtr == NULL_PTR) || (NvM_Descr_ptloc->RamBlockDataAddr_t == NvM_DstPtr))
        {
            NvM_EnterCriticalSection();
            /* set the ram block invalid and unchanged (=> invalid, but changed makes no sense!) */
            NvM_RamMngmt_ptloc->NvRamAttributes_u8 &= (NVM_STATE_VALID_CL & NVM_STATE_CHANGED_CL);
            NvM_ExitCriticalSection();
        }
        return E_OK;
    }
    else
    {
      /* queuing the job failed */
      return E_NOT_OK;
    }
}
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_EraseNvBlock(BlockId)
!
!-----------------------------------------------------------------------------
!   Function Description: Request to erase a NV block. The content of the RAM
!   block shall remain unmodified.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  none
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_3 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_3))
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_EraseNvBlock(NvM_BlockIdType BlockId)
{
    #if (STD_ON == NVM_DEV_ERROR_DETECT)
        /* local desc. pointer */
        NvM_BlockDescrPtrType NvM_Block_ptloc;
    #endif
    /* local ram management pointer */
    /* BlockId has to be used here before BlockId check to get the pointer. But the pointer is only
      used after BlockId check. */
    const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = 
      (BlockId & NVM_DCM_BLOCK_OFFSET) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);
    const NvM_BlockIdType orgBlockId = (BlockId & (~NVM_DCM_BLOCK_OFFSET));

    
    #if (STD_ON == NVM_DEV_ERROR_DETECT)
        /* local desc. pointer */
        NvM_Block_ptloc = &(NvM_BlockDescriptorTable_at[orgBlockId]);
    #endif

    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_ERASE_BLOCK, NVM_E_NOT_INITIALIZED);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* Check ParamConfig */
    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID) /* Debug Mode */
        /* is the block id valid? */
        if ((NvM_NoOfBlockIds_t <= orgBlockId) || (0u == orgBlockId))
        {
            NvM_Errorhook(NVM_ERASE_BLOCK, NVM_E_PARAM_BLOCK_ID);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* check dataindex */
    #if (STD_ON == NVM_CFG_CHK_PARAM_DATAINDEX)
        /* check is only necessary for blocks of MngmtType DATASET or DATASET_ROM */
        if((NvM_BlockDescriptorTable_at[orgBlockId].MngmtType_t & NVM_BLOCK_DATASET) != 0)
        {
            if (NvM_RamMngmt_ptloc->NvDataIndex_t >= NvM_BlockDescriptorTable_at[orgBlockId].NvBlockCount_u8)
            {
                NvM_Errorhook(NVM_ERASE_BLOCK, NVM_E_PARAM_BLOCK_DATA_IDX);
                return E_NOT_OK;
            }
            else
            {
                /* nothing to do */
            }
        }
    #endif

    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID)
        /* check if the block is high prio */
        if (0u != NvM_Block_ptloc->BlockPrio_u8)
        {
            NvM_Errorhook(NVM_ERASE_BLOCK, NVM_E_BLOCK_CONFIG);
            return E_NOT_OK;
        }
        else
        {
            /* nothing to do */
        }
    #endif

    /* is the block write protected?  */
    if((NvM_RamMngmt_ptloc->NvRamAttributes_u8 & NVM_WR_PROT_SET) != 0)
    {
        /* check the block protection */
        NvM_Errorhook(NVM_ERASE_BLOCK, NVM_E_NV_WRITE_PROTECTED);
        return E_NOT_OK;
    }
    else
    {
        /* nothing to do */
    }

    /* is the block locked? */
    if((0 == (BlockId & NVM_DCM_BLOCK_OFFSET)) && ((NvM_RamMngmt_ptloc->NvRamAttributes_u8 & NVM_LOCK_STAT_SET) != 0))
    {
      /* check the block lock status without error notification to Det or Dem */        
      return E_NOT_OK;
    }
    else
    {
        /* nothing to do */
    }

    /* queue the erase job */
    if (NvM_QueueJob(BlockId, NVM_INT_FID_ERASE_BLOCK, NULL_PTR))
    {
        return E_OK;
    }
    else
    {
      /* queuing the job failed */
      return E_NOT_OK;
    }
}
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_InvalidateNvBlock(BlockId)
!
!-----------------------------------------------------------------------------
!   Function Description: Request to invalidate a NV block. The RAM block shall
!   remain unmodified.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  none
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (NVM_API_CONFIG_CLASS_3 == (NVM_API_CONFIG_CLASS & NVM_API_CONFIG_CLASS_3))
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_InvalidateNvBlock(NvM_BlockIdType BlockId)
{
     /* local ram management pointer */
    /* BlockId has to be used here before BlockId check to get the pointer. But the pointer is only
      used after BlockId check. */
    const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = 
      (BlockId & NVM_DCM_BLOCK_OFFSET) ? (&NvM_DcmBlockMngmt_t) : (&NvM_BlockMngmtArea_at[BlockId]);
    const NvM_BlockIdType orgBlockId = (BlockId & (~NVM_DCM_BLOCK_OFFSET));

    
    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_INVALIDATE_NV_BLOCK, NVM_E_NOT_INITIALIZED);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }

    #endif

    /* Check ParamConfig */
    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID) /* Debug Mode */
        /* is the block id valid? */
        if ((orgBlockId == 0) || (orgBlockId >= NvM_NoOfBlockIds_t))
        {
            NvM_Errorhook(NVM_INVALIDATE_NV_BLOCK, NVM_E_PARAM_BLOCK_ID);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* check dataindex */
    #if (STD_ON == NVM_CFG_CHK_PARAM_DATAINDEX)
        /* check is only necessary for blocks of MngmtType DATASET or DATASET_ROM */
        if((NvM_BlockDescriptorTable_at[orgBlockId].MngmtType_t & NVM_BLOCK_DATASET) != 0)
        {
            if (NvM_RamMngmt_ptloc->NvDataIndex_t >= NvM_BlockDescriptorTable_at[orgBlockId].NvBlockCount_u8)
            {
                NvM_Errorhook(NVM_INVALIDATE_NV_BLOCK, NVM_E_PARAM_BLOCK_DATA_IDX);
                return E_NOT_OK;
            }
            else
            {
                /* nothing to do */
            }
        }
    #endif

    /* is the block write protected?
     * This check shall ALWAYS be performed.
     */
    if ((NvM_RamMngmt_ptloc->NvRamAttributes_u8 & NVM_WR_PROT_SET) != 0)
    {
        /* check the block protection */
        NvM_Errorhook(NVM_INVALIDATE_NV_BLOCK, NVM_E_NV_WRITE_PROTECTED);
        return E_NOT_OK;
    }
    else
    {
        /* nothing to do */
    }

    /* is the block locked? */
    if((0 == (BlockId & NVM_DCM_BLOCK_OFFSET)) && ((NvM_RamMngmt_ptloc->NvRamAttributes_u8 & NVM_LOCK_STAT_SET) != 0))
    {
      /* check the block lock status without error notification to Det or Dem */        
      return E_NOT_OK;
    }
    else
    {
        /* nothing to do */
    }

    /* queue the erase job */
    if (NvM_QueueJob(BlockId, NVM_INT_FID_INVALIDATE_NV_BLOCK, NULL_PTR))
    {
        return E_OK;
    }
    else
    {
      /* queuing the job failed */
      return E_NOT_OK;
    }
}
#endif

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_ReadAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Request to read the data of all configured RAM
!   blocks from their corresponding NV blocks.
!   Only the data of valid NV blocks is read.
!-----------------------------------------------------------------------------
!   Parameter (Input):   none
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PUBLIC_CODE) NvM_ReadAll(void)
{
    /* local ram management pointer */
    const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = &NvM_BlockMngmtArea_at[0];

    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_READ_ALL, NVM_E_NOT_INITIALIZED);
            return;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /*  it is a critical section. */
    NvM_EnterCriticalSection();

    /* check pending */
    #if (STD_ON == NVM_CFG_CHK_BLOCK_PENDING)

        if (NVM_REQ_PENDING == NvM_RamMngmt_ptloc->NvRamErrorStatus_u8)
        {
            NvM_Errorhook(NVM_READ_ALL, NVM_E_BLOCK_PENDING);
            NvM_ExitCriticalSection();
            return;
        }

        /* set the ram block pending */
        NvM_RamMngmt_ptloc->NvRamErrorStatus_u8 = NVM_REQ_PENDING;
    #else
        NvM_RamMngmt_ptloc->NvRamErrorStatus_u8 = NVM_REQ_PENDING;
    #endif

     /* set the "ReadAll" flag */
     NvM_ApiFlags_u8 |= NVM_APIFLAG_READ_ALL_SET;
     NvM_ExitCriticalSection();
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_WriteAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Request to copy the data of all configured RAM
!   blocks to their corresponding NV blocks.
!   Only the data of valid RAM blocks shall be written.
!-----------------------------------------------------------------------------
!   Parameter (Input):   none
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PUBLIC_CODE) NvM_WriteAll(void)
{
    /* local ram management pointer */
    const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = &NvM_BlockMngmtArea_at[0u];

    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_WRITE_ALL, NVM_E_NOT_INITIALIZED);
            return;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /*  it is a critical section. */
    NvM_EnterCriticalSection();

    /* check pending */
    #if (STD_ON == NVM_CFG_CHK_BLOCK_PENDING)

        if (NVM_REQ_PENDING == NvM_RamMngmt_ptloc->NvRamErrorStatus_u8)
        {
            NvM_Errorhook(NVM_WRITE_ALL, NVM_E_BLOCK_PENDING);
            NvM_ExitCriticalSection();
            return;
        }
        else
        {
           /* nothing to do */
        }

        /* set the ram block pending */
        NvM_RamMngmt_ptloc->NvRamErrorStatus_u8 = NVM_REQ_PENDING;
    #else
        NvM_RamMngmt_ptloc->NvRamErrorStatus_u8 = NVM_REQ_PENDING;
    #endif

    /* set the "WriteAll" flag while clearing  "Cancel WriteAll" and "Kill WriteAll flags".
     * Note: Since ReadAll flag can be expected to be cleared (otherwise WriteAll would not be allowed),
     *       we do need to use bit mask operations -> just assign the WriteAll flag.                    */
    NvM_ApiFlags_u8 = NVM_APIFLAG_WRITE_ALL_SET;
    NvM_ExitCriticalSection();

}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_CancelWriteAll()
!
!-----------------------------------------------------------------------------
!   Function Description: Request to cancel a pending WriteAll request.
!-----------------------------------------------------------------------------
!   Parameter (Input):   none
!   Parameter (Output):  none
!   Returnvalue:         void
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PUBLIC_CODE) NvM_CancelWriteAll(void)
{
    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_CANCEL_WRITE_ALL, NVM_E_NOT_INITIALIZED);
            return;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* since a NvM_ReadAll or NvM_WriteAll might arrive at nearly the same time (this is allowed),
     *  it is a critical section. */
    NvM_EnterCriticalSection();

    /* set the "Cancel WriteAll" flag */
    NvM_ApiFlags_u8 |= NVM_APIFLAG_CANCEL_WR_ALL_SET;
    NvM_ExitCriticalSection();
}

#if (NVM_KILL_WRITEALL_API == STD_ON)
    /*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    !   Function name: NvM_KillWriteAll()
    !
    !-----------------------------------------------------------------------------
    !   Function Description: Request to kill a pending WriteAll request, i.e.
    !                         To cancel it destructively
    !                         (in contrast to NvM_Cancelwriteall)
    !                         Shall only called by EcuM (or comparable SW)
    !-----------------------------------------------------------------------------
    !   Parameter (Input):   none
    !   Parameter (Output):  none
    !   Returnvalue:         void
    !+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    void NvM_KillWriteAll(void)
    {
        /* Check Uninit */
        #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
            /* is the module initialized? */
            if (NVM_STATE_UNINIT == NvM_TaskState_t)
            {
                NvM_Errorhook(NVM_KILL_WRITE_ALL, NVM_E_NOT_INITIALIZED);
                return;
            }
            else
            {
                /* Here is nothing to do */
            }
        #endif

        /* since a NvM_KillWriteAll might be called from a task which preempted NvM_MainFunction,
         *  this is a critical section. */
        NvM_EnterCriticalSection();

        if(NvM_ApiFlags_u8 & NVM_APIFLAG_WRITE_ALL_SET)
        {
            /*  Clear WriteAll Flag -> if WriteAll was just queued, but not started yet, it will be simply discarded.
             *                      -> WriteAll may be requested immediately after we return.
             *  set both flags, "Cancel WriteAll" and "Kill WriteAll". The former one, makes sure, that
             *  No Block processing will be started, if WriteAll was not started until now               */
            NvM_ApiFlags_u8 &= NVM_APIFLAG_WRITE_ALL_CL;
            NvM_ApiFlags_u8 |= NVM_APIFLAG_KILL_WR_ALL_SET | NVM_APIFLAG_CANCEL_WR_ALL_SET;

            /* Check whether current job is actually a writeAll job, and if it actually processes an NVRAM Block */
            if((NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_WRITE_ALL) && 
               (NvM_CurrentJob_t.JobBlockId_t > 0)                        &&
               (NvM_CurrentJob_t.JobBlockId_t < NvM_NoOfBlockIds_t))
            {
                const NvM_RamMngmtPtrType mngmt_pt = NvM_CurrentBlockInfo_t.Mngmt_pt;
                const uint8 deviceId = (uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8;
                /* immediatelly set it to NVM_REQ_OK, if it is VALID, othewise set it to skipped */
                mngmt_pt->NvRamErrorStatus_u8 =
                    ((mngmt_pt->NvRamAttributes_u8 & NVM_STATE_VALID_SET) != 0) ? NVM_REQ_OK : NVM_REQ_BLOCK_SKIPPED;

                /* immediately cancel the device the block is assigned to, if it is BUSY */
                if(MemIf_GetStatus(deviceId) == MEMIF_BUSY)
                {
                    MemIf_Cancel(deviceId);
                }
            }

            /* Mark WriteAll as CANCELLED for the world (EcuM), however the internal handling does not finish immediately */
            NvM_BlockMngmtArea_at[0].NvRamErrorStatus_u8 = NVM_REQ_CANCELLED;

        }
        NvM_ExitCriticalSection();
    }
#endif


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_MainFunction
!
!-----------------------------------------------------------------------------
!   Function Description: This  function shall perform the processing of the
!   NVRAM Manager jobs. Therefore it has to be called cyclically.
!-----------------------------------------------------------------------------
!   Module Global: none
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PUBLIC_CODE) NvM_MainFunction(void)
{
    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_MAINFUNCTION, NVM_E_NOT_INITIALIZED);
            return;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* reset the wait flag */
    NvM_CurrentBlockInfo_t.InternalFlags_u8 &= NVM_INTFLAG_WAIT_CL;

#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    if(!NvM_CrcJob_isBusy(&NvM_AsyncCrcJob_t))
    {
        const NvM_BlockIdType newCrcBlockId = NvM_CrcGetQueuedBlockId();
        const NvM_BlockDescrPtrType descr_pt = &NvM_BlockDescriptorTable_at[newCrcBlockId];

        /* copy CRC from previous CRC job to crc buffer, before we create a new one */
        NvM_CrcJob_CopyToBuffer(&NvM_AsyncCrcJob_t);

        /* create new Crc Job with next BlockId from CRC queue
         * Note: If the queue is empty we get 0.
         *       Due to block 0's Desctiptor, it will result in an "empty" CRC job.
         *       We may ommit a special check here                                    */
        NvM_CrcJob_Create(&NvM_AsyncCrcJob_t, descr_pt, descr_pt->RamBlockDataAddr_t);

#if(NVM_CRC_INT_BUFFER == STD_ON)
        NvM_CrcJob_ReassignBuffer(&NvM_AsyncCrcJob_t, descr_pt->RamBlockCrcAddr_t);
#endif
    }

    /* call the cyclic crc processing function */
    NvM_CrcJob_Process(&NvM_AsyncCrcJob_t, NvM_NoOfCrcBytes_u16);
#endif
    /* call the job main state machine, which performs the NVM as long as
     * NVM does not have to wait (then leave Main Function)
     */
    do
    {
        /* main task state machine */
        NvM_TaskState_t = NvM_Fsm(NvM_TaskState_t);

        /* job main state machine */
        NvM_JobMainState_t = NvM_Fsm(NvM_JobMainState_t);

        /* job sub state machine */
        NvM_JobSubState_t = NvM_Fsm(NvM_JobSubState_t);
    }
    while ((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_WAIT_SET) == 0);
}


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_JobEndNotification
!
!-----------------------------------------------------------------------------
!   Function Description: This function is the job end notification for
!                         the MemHwA. 
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PUBLIC_CODE) NvM_JobEndNotification(void)
{
#if(STD_OFF == NVM_POLLING_MODE)
     NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
#endif
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_JobErrorNotification
!
!-----------------------------------------------------------------------------
!   Function Description: This function is the job error notification for
!                         the MemHwA.
!-----------------------------------------------------------------------------
!   Parameter:     none
!   Returnvalue:   none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PUBLIC_CODE) NvM_JobErrorNotification(void)
{
#if(STD_OFF == NVM_POLLING_MODE)
    /* sets LastResult depending on JobResult of lower layer */
    switch(MemIf_GetJobResult(NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8))
    {       

        case MEMIF_BLOCK_INCONSISTENT:
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_INTEGRITY_FAILED;
            break;

        case MEMIF_BLOCK_INVALID:
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NV_INVALIDATED;
            break;

        default:
            NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
    }
#endif
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_SetBlockLockStatus(BlockId, Locked)
!
!-----------------------------------------------------------------------------
!   Function Description: The request shall set/reset the lock status for
!   the NV block. This shall be done by setting the lock status attribute in the
!   administrative part of the corresponding RAM block. 
!   The NV contents associated to the NVRAM block identified by BlockId, will not
!   be modi-fied by any request. The Block shall be skipped during NvM_WriteAll. 
!   Other write/erase requests shall be rejected. At processing NvM_ReadAll a
!   locked block shall be loaded from NV memory.write protection.
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId, Locked
!   Parameter (Output):  none
!   Returnvalue:         Std_ReturnType
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetBlockLockStatus(NvM_BlockIdType BlockId, boolean Locked)
{
    /* local desc. pointer */
    /* BlockId has to be used here before BlockId check to get the pointer. But the pointer is only
      used after BlockId check. */
    const NvM_RamMngmtPtrType NvM_RamMngmt_ptloc = &NvM_BlockMngmtArea_at[BlockId & (~NVM_DCM_BLOCK_OFFSET)];

    /* Check Uninit */
    #if (STD_ON == NVM_CFG_CHK_STATUS_UNINIT) /* Debug Mode */
        /* is the module initialized? */
        if (NVM_STATE_UNINIT == NvM_TaskState_t)
        {
            NvM_Errorhook(NVM_SET_BLOCK_LOCK_STATUS, NVM_E_NOT_INITIALIZED);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* Check ParamConfig */
    #if (STD_ON == NVM_CFG_CHK_PARAM_BLOCKID) /* Debug Mode */
        /* is the block id valid? */
        if ((NvM_NoOfBlockIds_t <= (BlockId & (~NVM_DCM_BLOCK_OFFSET))) || (0u == (BlockId & (~NVM_DCM_BLOCK_OFFSET))))
        {
            NvM_Errorhook(NVM_SET_BLOCK_LOCK_STATUS, NVM_E_PARAM_BLOCK_ID);
            return E_NOT_OK;
        }
        else
        {
            /* Here is nothing to do */
        }
    #endif

    /* check pending */
    #if (STD_ON == NVM_CFG_CHK_BLOCK_PENDING)
        if (NVM_REQ_PENDING == NvM_RamMngmt_ptloc->NvRamErrorStatus_u8)
        {
            NvM_Errorhook(NVM_SET_BLOCK_LOCK_STATUS, NVM_E_BLOCK_PENDING);
            return E_NOT_OK;
        }
        else
        {
           /* nothing to do */
        }
    #endif

    
    NvM_EnterCriticalSection();
    /* shall the lock status be enabled? */
    if (Locked)
    {
        NvM_RamMngmt_ptloc->NvRamAttributes_u8 |= NVM_LOCK_STAT_SET;
    }
    else
    {
        NvM_RamMngmt_ptloc->NvRamAttributes_u8 &= NVM_LOCK_STAT_CL;
    }
    NvM_ExitCriticalSection();
    return E_OK;
}


#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*---- End of File ---------------------------------------------------------*/
