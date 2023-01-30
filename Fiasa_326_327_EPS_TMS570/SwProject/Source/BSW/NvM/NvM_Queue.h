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
 *         File:  NvM_Queue.h
 *    Component:  MemService_AsrNvM
 *       Module:  NvM - Submodule Queue
 *    Generator:  -
 *
 *  Description:  This sub-module contains the queue-handling of the (optionally) prioritized job queue.
 *    
 *                This file is an internal include; it shall not be included by other modules than NvM!
 *  
 *********************************************************************************************************************/

/* Do not modify this file! */

/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
#if (!defined NVM_QUEUE_H_)
#define NVM_QUEUE_H_

/**********************************************************************************************************************
 * VERSION IDENTIFICATION
 *********************************************************************************************************************/
#define NVM_QUEUE_MAJOR_VERSION    (3u)
#define NVM_QUEUE_MINOR_VERSION    (7u)
#define NVM_QUEUE_PATCH_VERSION    (1u)

/* queueing is only needed in config classes 2 and 3 */
#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
/**********************************************************************************************************************
 * API MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * API TYPE DEFINITIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * API STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * API FUNCTIONS
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

    /* QUEUE processing functions */
    extern FUNC(void, NVM_PRIVATE_CODE) NvM_QueueInit(void);
    extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_QueueJob(NvM_BlockIdType, NvM_InternalServiceIdType, NvM_RamAddressType);

    extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNormalPrioJob(void);
    extern FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetNormalPrioJob(void);

#if(NVM_JOB_PRIORISATION == STD_ON)
    extern FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHighPrioJob(void);
    extern FUNC(void, NVM_PRIVATE_CODE) NvM_ActGetHighPrioJob(void);
    extern FUNC(void, NVM_PRIVATE_CODE) NvM_ActQueueFreeLastJob(void);
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* not config class 1 */


#endif /* NVM_QUEUE_H_ */
/*---- End of File ---------------------------------------------------------*/
