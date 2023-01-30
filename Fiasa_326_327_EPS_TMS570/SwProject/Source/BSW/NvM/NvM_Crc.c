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
 *         File:  NvM_Crc.c
 *      Project:  MemService_AsrNvM
 *       Module:  NvM - Submodule Crc (Crc processing)
 *    Generator:  -
 *
 *  Description:  This sub-module implements the CRC recalculation FSM that 
 *                recalculates the CRC piece-wise
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
#include "NvM_Crc.h"



/**********************************************************************************************************************
 *  TARGET AND COMPILER
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if (     (NVM_CRC_MAJOR_VERSION != (3u)) \
       || (NVM_CRC_MINOR_VERSION != (7u)))
  #error "Version numbers of NvM_Crc.c and NvM_Crc.h are inconsistent!"
#endif

#if (     (NVM_CFG_MAJOR_VERSION != (3u)) \
       || (NVM_CFG_MINOR_VERSION != (7u)))
  #error "Version numbers of NvM_Crc.c and NvM_Cfg.h are inconsistent!"
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
#define NVM_CRC_CLASS_NONE  0x00u
#define NVM_CRC_CLASS_16    0x01u
#define NVM_CRC_CLASS_32    0x02u

/**********************************************************************************************************************
 *  INTERNAL TYPE DEFINITIONS
 **********************************************************************************************************************/

typedef P2VAR(NvM_CrcQueueEntryType, AUTOMATIC, NVM_CONFIG_DATA) NvM_CrcQueueEntryPtr;

/**********************************************************************************************************************
 *  INTERNAL STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  INTERNAL FORWARD DECLARATIONS
 **********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, NVM_PRIVATE_CODE)  NvM_Crc_NoCrc_Calculate    (NvM_ConstRamAddressType, uint16, NvM_CrcValuePtrType);
static FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_Compare      (NvM_CrcBufferConstPtrType, NvM_CrcValueRefType);
static FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_CopyToBuffer (NvM_CrcBufferPtrType, NvM_CrcValueRefType);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *  INTERNAL MODULE GLOBAL VARIABLES
 *********************************************************************************************************************/
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* "Dummy" Handler for Disabled CRC -> always exists */
CONST(struct NvM_CrcHandlerClass, NVM_PRIVATE_CONST) NvM_Crc_NoCrcHandler_t =
{
    NvM_Crc_NoCrc_Calculate,
    NvM_Crc_NoCrc_Compare,
    NvM_Crc_NoCrc_CopyToBuffer,
    0, /* initial value */
    0  /* crc length */
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

    STATIC VAR(NvM_BlockIdType, NVM_PRIVATE_DATA) NvM_CrcQueueScanStart_u16;

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

/**********************************************************************************************************************
 *  IMPLEMENTATION
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_CrcQueueInit()
!
!-----------------------------------------------------------------------------
!   Function Description: Initialization of NvM's Crc_Queue
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   none
!   Parameter (Output):  none
!   Returnvalue:         none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PRIVATE_CODE) NvM_CrcQueueInit(void)
{
    uint16_least counter = (NvM_CrcQueueSize_u16 + NVM_CRC_QUEUE_BITINDEX_MASK) >> NVM_CRC_QUEUE_ENTRY_SHIFT;
    
    /* clear the Crc Queue */
    do
    {
        --counter;
        NvM_CrcQueue_at[counter] = 0u;
    }
    while(counter > 0);

    /* start queue scan with block 1, since block ID 0 is a reserved block, never requesting CRC re-calculation */
    NvM_CrcQueueScanStart_u16 = 1u;
}


/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_QueueCrcJob()
!
!-----------------------------------------------------------------------------
!   Function Description: Function queues a CRC recalculation request for one
!                         block. 
!-----------------------------------------------------------------------------
!   Parameter (Input):   BlockId
!   Parameter (Output):  none
!   Returnvalue:         none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PRIVATE_CODE) NvM_CrcQueueJob(NvM_BlockIdType BlockId)
{
    /* perform calculations outside of Critical section, in order to make it as short as possible */
    const NvM_CrcQueueEntryType bitMask = (NvM_CrcQueueEntryType)(1u << (BlockId & NVM_CRC_QUEUE_BITINDEX_MASK));
    const NvM_CrcQueueEntryPtr queueEntry = &NvM_CrcQueue_at[BlockId >> NVM_CRC_QUEUE_ENTRY_SHIFT];

    NvM_EnterCriticalSection();

        /* set the Block's corresponding bit */            
        *queueEntry |= bitMask;

    NvM_ExitCriticalSection();
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_CrcGetQueuedBlockId()
!
!-----------------------------------------------------------------------------
!   Function Description: Function checks if there are still CRC jobs queued.
!                         It returns the next block for CRC calculation.
!
!
!-----------------------------------------------------------------------------
!   Module Global:       RAM_MANAGEMENT
!   Parameter (Input):   none
!   Parameter (Output):  none
!   Returnvalue:         NvM_BlockIdType, 0, if CRC queue was empty
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(NvM_BlockIdType, NVM_PRIVATE_CODE) NvM_CrcGetQueuedBlockId(void)
{
    uint16_least newBlockId = NvM_CrcQueueScanStart_u16;

    NvM_CrcQueueEntryPtr CurrQueuePtr  = &NvM_CrcQueue_at[newBlockId >> NVM_CRC_QUEUE_ENTRY_SHIFT];
    NvM_CrcQueueEntryType QueueBitMask = (NvM_CrcQueueEntryType)(NVM_CRC_QUEUE_ENTRY_MASK << (newBlockId & NVM_CRC_QUEUE_BITINDEX_MASK));

    /* mask out lowest 4 bits --> make blockId multiple of 16 or 32 (depending on platform) */
    newBlockId &= ~(NVM_CRC_QUEUE_BITINDEX_MASK);
    
    QueueBitMask &= *CurrQueuePtr;
    if(QueueBitMask == 0u)
    {   
        /* search for the first non-zero byte --> CRC job(s) queued */
        for((newBlockId += NVM_CRC_QUEUE_ENTRY_BITS);
            (newBlockId < NvM_CrcQueueSize_u16);
            (newBlockId += NVM_CRC_QUEUE_ENTRY_BITS))
        {
            QueueBitMask = *(++CurrQueuePtr);                
            
            if(QueueBitMask != 0u)
            {
                /* we found (at least) one CRC job */
                break; /* leave the loop */
            }
        }
    } /* if(QueueBitMask == 0) --> no job with first queue check */


    /* we found a non-zero word: find lowest bit that is set. */
    if(QueueBitMask != 0)
    {
#if(NVM_CRC_QUEUE_ENTRY_BITS > 16u)
        /* is none of the lower 16 bits set? */
        if((QueueBitMask & 0xFFFFu) == 0u)
        {
            newBlockId |= 0x10u;
            QueueBitMask >>= 16u;
        }
#endif
        /*is none of the lower 8bits set? */
        if((QueueBitMask & 0xFFu) == 0u)
        {
            newBlockId |= 0x08u;
            QueueBitMask >>= 8u;
        }

        /* is none of the lower 4 bits set?*/
        if((QueueBitMask & 0x0Fu) == 0u)
        {  
            newBlockId |= 0x04u;
            QueueBitMask >>= 4u;
        }

        /* is none of the lower 2 bits set? */            
        if((QueueBitMask & 0x03u) == 0u)
        { 
            newBlockId |= 2u;
            QueueBitMask >>= 2u;
        }

        /* Process least significant bit.                                                     *
         * If the least signifcant bit is zero, add 1 (because bit 1 must then be set)        *
         * If LSB is set add nothing.                                                         *
         * The cast appears to be unnecessary. However, some Compilers might issue a warning, *
         * if uint16_least is 16bit, while QueueBitMask is 32bit width                        */
        newBlockId  |= (uint16_least)((QueueBitMask & 1u) ^ 1u); 

        /* now, we have exactly one of the 16 or 32bits - the lowest tat was set */

        /* update Block Id where to start the next queue scan                         *
         * The cast is necessary if uint16_least (newBlockId) is 32bit width.         *
         * ... Just avoid compiler warnings, as truncation is avoided below           */
        NvM_CrcQueueScanStart_u16 = (NvM_BlockIdType)(newBlockId + 1u);

        /* handle (avoid) overflow/wrap-around */
        if(NvM_CrcQueueScanStart_u16 >= NvM_CrcQueueSize_u16)
        {
            NvM_CrcQueueScanStart_u16 = 1u;

        }

        QueueBitMask = (NvM_CrcQueueEntryType)(1u << (newBlockId & NVM_CRC_QUEUE_BITINDEX_MASK));

        NvM_EnterCriticalSection();
        {    
            /* clear the Block's corresponding bit, since it was set (and cannot be cleared eslewhere, we can use XOR) */            
            *CurrQueuePtr ^= QueueBitMask;
        }
        NvM_ExitCriticalSection();

        /* Now we better check the BlockId (queue may contain unused bits at its end) */
        if(newBlockId >= NvM_CrcQueueSize_u16)
        {
            newBlockId = 0;
        }
    } /* if(QueueBitMask != 0) --> from word-wise queue-scan */
    else /* words in queue were zero - no block found */
    {
        /* the end of the queue was reached --> next cycle starts with BlockId 1 */
        NvM_CrcQueueScanStart_u16 = 1u;
        newBlockId = 0;
    }

    return (NvM_BlockIdType)newBlockId;
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) */


#define NVM_START_SEC_CODE
#include "MemMap.h"

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_CrcJob_Create(...)
!
!-----------------------------------------------------------------------------
!   Function Description: Cyclically called function for processing the CRC
!                         calculation.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   descPtr    - pointer to BlockDescriptor entry
!                        ramDataPtr - pointer to user buffer
!   Parameter (Output):  self       - pointer to CrcJob instance to be created
!   Returnvalue:         none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_Create(NvM_CrcJobPtrType self, NvM_BlockDescrPtrType descr_pt, NvM_RamAddressType ramData_pt)
{
    self->HandlerInstance_pt = NvM_CrcHandlerTable_at[descr_pt->CrcSettings];
    
    self->CurrentCrcValue = self->HandlerInstance_pt->initialCrcValue;

    self->RamData_pt = ramData_pt;
    self->CrcBuffer = (ramData_pt != NULL_PTR) ? (&ramData_pt[descr_pt->NvBlockLength_u16]) : NULL_PTR;

    /* let an CRC job complete immediately, if there's actually no CRC, or if there are no RAM data */
    self->RemainingLength_u16 = 
        ((self->HandlerInstance_pt->crcLength > 0) && (ramData_pt != NULL_PTR)) ? descr_pt->NvBlockLength_u16 : 0;
}

/*!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!   Function name: NvM_CrcJob_Process(NvM_CrcJobPtrType self)
!
!-----------------------------------------------------------------------------
!   Function Description: Cyclically called function for processing the CRC
!                         calculation.
!
!-----------------------------------------------------------------------------
!   Parameter (Input):   self          - pointer to CrcJob instance
!                        processLength - Maximum number of Bytes to process
!                                        within this call.
!   Parameter (Output):  none
!   Returnvalue:         none
!+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_Process(NvM_CrcJobPtrType self, uint16_least processLength)
{
    if(self->RemainingLength_u16 > 0)
    { 
        const NvM_ConstRamAddressType currRamPtr = self->RamData_pt;
        uint16_least currLength = self->RemainingLength_u16;

        /* if both value are equal, we would not need to adapt currentLength, but finishJob needs to be set. */
        if(currLength > processLength)
        {
            currLength = processLength;
        }
        
        self->RemainingLength_u16 -= currLength;
        
        /* set RamAddress for next calculation cycle */
        self->RamData_pt = &currRamPtr[currLength];

        self->HandlerInstance_pt->calc(currRamPtr, currLength, &self->CurrentCrcValue);
    }
}

FUNC(boolean, NVM_PRIVATE_CODE) NvM_CrcJob_Compare(NvM_CrcJobConstPtrType self)
{
    return (boolean)((self->CrcBuffer != NULL_PTR) ? 
                                (self->HandlerInstance_pt->compare(self->CrcBuffer, (NvM_CrcValueRefType)&self->CurrentCrcValue)) : FALSE);
}


FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_CopyToBuffer(NvM_CrcJobConstPtrType self)
{
    if(self->CrcBuffer != NULL_PTR)
    {
        self->HandlerInstance_pt->copyToBuffer(self->CrcBuffer, (NvM_CrcValueRefType)&self->CurrentCrcValue);
    }
}


#if(NVM_CRC_INT_BUFFER == STD_ON)
    FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_ExportBufferedValue(NvM_CrcJobConstPtrType self, NvM_CrcBufferPtrType dest_pt)
    {
        if((dest_pt != NULL_PTR) && (self->CrcBuffer != NULL_PTR))
        {
            self->HandlerInstance_pt->copyToBuffer(dest_pt, self->CrcBuffer);
        }
    }
#endif

/********************* No-CRC Handler Functions *************************************************/
static FUNC(void, NVM_PRIVATE_CODE)  NvM_Crc_NoCrc_Calculate(NvM_ConstRamAddressType data_ptr, uint16 length, NvM_CrcValuePtrType currentValue)
{
    data_ptr[length];
    currentValue;
}

static FUNC(boolean, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_Compare(NvM_CrcBufferConstPtrType crcBuff, NvM_CrcValueRefType currentValue)
{
    crcBuff; currentValue;
    return TRUE;
}

static FUNC(void, NVM_PRIVATE_CODE) NvM_Crc_NoCrc_CopyToBuffer(NvM_CrcBufferPtrType dest, NvM_CrcValueRefType src)
{
    dest; src;
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*---- End of File ---------------------------------------------------------*/
