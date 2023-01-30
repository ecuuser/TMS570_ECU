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
 *         File:  NvM_Cbk.h
 *    Component:  MemService_AsrNvM
 *       Module:  NvM
 *    Generator:  -
 *
 *  Description:  This file declares callback functions NvM_JobEndNotification and NvM_JobErrorNotification
 *  
 *********************************************************************************************************************/

/* Do not modify this file! */

/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
#if (!defined NVM_CBK_H_)
#define NVM_CBK_H_

/**********************************************************************************************************************
 * VERSION IDENTIFICATION
 *********************************************************************************************************************/
#define NVM_CBK_MAJOR_VERSION    (3u)
#define NVM_CBK_MINOR_VERSION    (7u)
#define NVM_CBK_PATCH_VERSION    (0u)

/**********************************************************************************************************************
 * CALLBACK FUNCTIONS
 *********************************************************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h"

    /* Callbacks are public, i.e. they will be called from outside of the NvM.
     * Usually this means "from far away" (another segment)
     */
    extern FUNC(void, NVM_PUBLIC_CODE) NvM_JobEndNotification(void);
    extern FUNC(void, NVM_PUBLIC_CODE) NvM_JobErrorNotification(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"


#endif
/*---- End of File ---------------------------------------------------------*/
