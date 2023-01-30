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
 *         File:  NvM_Crc.h
 *    Component:  MemService_AsrNvM
 *       Module:  NvM - Submodule Crc (Crc processing)
 *    Generator:  -
 *
 *  Description:  This sub-module implements the CRC recalculation FSM that recalculates the CRC piece-wise.
 *    
 *                This file is an internal include; it shall not be included by other modules than NvM!
 *  
 *********************************************************************************************************************/

/* Do not modify this file! */

/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
#if (!defined NVM_CRC_H_)
#define NVM_CRC_H_

/**********************************************************************************************************************
 * VERSION IDENTIFICATION
 *********************************************************************************************************************/
#define NVM_CRC_MAJOR_VERSION    (3u)
#define NVM_CRC_MINOR_VERSION    (7u)
#define NVM_CRC_PATCH_VERSION    (1u)

/**********************************************************************************************************************
 * MACRO DEFINITIONS
 *********************************************************************************************************************/

/* Define optimal pointer class for crc buffer, depending on NVM_CRC_INT_BUFFER setting.                            *
 * CRC buffer will either point to user RAM Block (NVM_APPL_DATA) or to an internal buffer (NVM_PRIVATE_DATE)       *
 * Since it NVM_CRC_INT_BUFFER is is pre-compile, so we can do it...                                                */
#if(STD_ON == NVM_CRC_INT_BUFFER)
#   define NVM_CRC_BUFFER_PTR_CLASS NVM_PRIVATE_DATA
#else
#   define NVM_CRC_BUFFER_PTR_CLASS NVM_APPL_DATA
#endif

/******************************************************************************
 * Define pseudo API (for performance reasons as macros)
 ******************************************************************************/

#define NvM_CrcJob_GetCrcLength(selfPtr)                    ((selfPtr)->HandlerInstance_pt->crcLength)
#define NvM_CrcJob_isBusy(selfPtr)                          ((selfPtr)->RemainingLength_u16 != 0)

#define NvM_CrcJob_ReassignBuffer(selfPtr, crcPtr) ((selfPtr)->CrcBuffer = (crcPtr)) 


typedef P2VAR(uint8, AUTOMATIC, NVM_CRC_BUFFER_PTR_CLASS) NvM_CrcBufferPtrType;
typedef P2CONST(uint8, AUTOMATIC, NVM_CRC_BUFFER_PTR_CLASS) NvM_CrcBufferConstPtrType;

typedef P2VAR(uint32, AUTOMATIC, NVM_PRIVATE_DATA) NvM_CrcValuePtrType;
typedef P2CONST(uint8, AUTOMATIC, NVM_PRIVATE_DATA) NvM_CrcValueRefType;

typedef P2FUNC(void, NVM_PRIVATE_CODE, NvM_CrcCalculateFPtr) (NvM_ConstRamAddressType, uint16, NvM_CrcValuePtrType);
typedef P2FUNC(boolean, NVM_PRIVATE_CODE, NvM_CrcCompareFPtr) (NvM_CrcBufferConstPtrType, NvM_CrcValueRefType);
typedef P2FUNC(void, NVM_PRIVATE_CODE, NvM_CrcCopyToBufferFPtr) (NvM_CrcBufferPtrType, NvM_CrcValueRefType);

struct NvM_CrcHandlerClass
{
    NvM_CrcCalculateFPtr    calc;
    NvM_CrcCompareFPtr      compare;
    NvM_CrcCopyToBufferFPtr copyToBuffer;
    uint32                  initialCrcValue;
    uint8                   crcLength;
};

typedef struct NvM_CrcJobStruct
{
    uint32                      CurrentCrcValue;
    NvM_ConstRamAddressType     RamData_pt;
    NvM_CrcBufferPtrType        CrcBuffer;
    NvM_CrcHandlerClassConstPtr HandlerInstance_pt;
    uint16                      RemainingLength_u16;
} NvM_CrcJobType;

typedef P2VAR(NvM_CrcJobType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_CrcJobPtrType;
typedef P2CONST(NvM_CrcJobType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_CrcJobConstPtrType;

/**********************************************************************************************************************
 * API FUNCTIONS
 *********************************************************************************************************************/
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* "Dummy" Handler for Disabled CRC -> always exists */
extern CONST(struct NvM_CrcHandlerClass, NVM_PRIVATE_CONST) NvM_Crc_NoCrcHandler_t;

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CODE
#include "MemMap.h"

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcQueueInit(void);
    extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcQueueJob(NvM_BlockIdType);
    extern FUNC(NvM_BlockIdType, NVM_PRIVATE_CODE) NvM_CrcGetQueuedBlockId(void);
#endif

    extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_Create(NvM_CrcJobPtrType, NvM_BlockDescrPtrType, NvM_RamAddressType);
    extern FUNC(void, NvM_PRIVATE_CODE) NvM_CrcJob_Process(NvM_CrcJobPtrType, uint16_least);
    extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_CopyToBuffer(NvM_CrcJobConstPtrType);
    extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_CrcJob_Compare(NvM_CrcJobConstPtrType);

#if(NVM_CRC_INT_BUFFER == STD_ON)
    extern FUNC(void, NVM_PRIVATE_CODE) NvM_CrcJob_ExportBufferedValue(NvM_CrcJobConstPtrType, NvM_CrcBufferPtrType);
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"


#endif /* NVM_CRC_H_ */
/*---- End of File ---------------------------------------------------------*/
