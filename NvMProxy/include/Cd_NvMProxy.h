/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Cd_NvMProxy.h
* Module Description: Module header defining external interfaces
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
 * Version Control:
 * Date Created:      Wed Feb  8 10:43:55 2012
 * %version:          3 %
 * %derived_by:       xz0btk %
 * %date_modified:    Fri May 31 12:56:29 2013 % 
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 02/08/12   1        JJW       Initial creation
 * 10/19/12   2        JJW       Support for GetErrorStatus and SetRamBlockStatus operations
 * 05/30/13   3        JJW       Support for WriteAll operation
 */

#ifndef NVMPROXY_H
#define NVMPROXY_H

#include "Cd_NvMProxy_Cfg.h"

/* NvMProxy Private Data */
extern NvM_RequestResultType NvMProxy_BlkStatus[D_NUMPRXYBLOCKS_CNT_U16];

/* NvMProxy External API's */
extern FUNC(void, AUTOMATIC) NvMProxy_Init( void );
extern FUNC(void, AUTOMATIC) NvMProxy_MainFunction( void );
extern FUNC(void, AUTOMATIC) NvMProxy_WriteAll( void );
extern FUNC(Std_ReturnType, AUTOMATIC) NvMProxy_WriteBlock(NvM_BlockIdType Block, P2CONST(uint8, AUTOMATIC, AUTOMATIC) SrcPtr);
extern FUNC(void, AUTOMATIC) NvMProxy_GetErrorStatus(NvM_BlockIdType Block, P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr);
extern FUNC(void, AUTOMATIC) NvMProxy_SetRamBlockStatus(NvM_BlockIdType Block, boolean BlockChanged);

#endif
