/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Cd_NvMProxy.c
* Module Description: Complex Driver NvMProxy which acts as a proxy between 
*                      applications requiring NvM services and the application 
*                      which hosts the NvM driver
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
 * Version Control:
 * Date Created:      Thu Feb 07 16:33:22 2012
 * %version:          7 %
 * %derived_by:       czgng4 %
 * %date_modified:    Wed Nov 20 08:22:33 2013 % 
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 02/07/12   1        JJW       Initial creation
 * 11/20/12   3        JJW       Corrected NvM block forwarding to pass the NULL_PTR reference to command writing of
 *									the default RAM buffer.  Corrected Status mirror update variable
 * 12/06/12   4        JJW       Completed NvM RAM Block Status request forwarding
 * 03/01/13   5        KJS       Corrected anomaly 4437 and QAC corrections
 * 05/30/13   6        JJW       Added support for WriteAll operation and multi-block status shadow.  Added array
 *								 bound checking.
 * 11/20/13   7        LWW       Added built in support for CRC and redundant block checking
 */


/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "Std_Types.h"
#include "Cd_NvMProxy.h"
#include "NvM.h"
#include "SchM_NvMProxy.h"
#include <string.h>
#include "Crc.h"

/**************************************************************************************************
* Module Types
**************************************************************************************************/

#define D_MULTIBLOCKID_CNT_U08	0u

typedef struct {
	VAR(boolean, AUTOMATIC) Pend;							/* Pending Proxy Forwarding 		*/
	VAR(NvM_RequestResultType, AUTOMATIC) BlkStatus;		/* Block Status Mirror				*/
	P2CONST(uint8, AUTOMATIC, AUTOMATIC) SrcPtr;			/* Pointer to source data buffer 	*/
} NvMPWriteBuff_Type;

typedef struct {
	VAR(boolean, AUTOMATIC) Pend;							/* Pending Proxy Forwarding 		*/
	VAR(boolean, AUTOMATIC) BlockChanged;					/* Block Status Mirror				*/
} NvMPSetRBSBuff_Type;

/**************************************************************************************************
* Module Variables
**************************************************************************************************/

/* NvM Proxy request buffers are considered non-critical.  This design requires the buffer to be writable by 
 * all applications that require proxy support.
 */

#define NVMPROXY_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

static VAR(NvMPWriteBuff_Type, AUTOMATIC) NvMPWriteRqst_Cnt_M_Str[D_NUMPRXYBLOCKS_CNT_U16];
static VAR(NvMPSetRBSBuff_Type, AUTOMATIC) NvMPSetRBSRqst_Cnt_M_Str[D_NUMPRXYBLOCKS_CNT_U16];

#define NVMPROXY_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


/**************************************************************************************************
* Local Function Prototypes
**************************************************************************************************/


#define NVMPROXY_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */
/*****************************************************************************
  * Name:        NvMProxy_Init
  * Description: (Trusted)
  * Inputs:      None 
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, AUTOMATIC) NvMProxy_Init( void )
{
	VAR(uint16, AUTOMATIC) i;
	VAR(uint16, AUTOMATIC) j;
	VAR(uint16, AUTOMATIC) CalcCRC_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) StrdCRC_Cnt_T_u16;
	VAR(boolean, AUTOMATIC) EEDiagFailed_Cnt_T_lgc;
	VAR(uint8, AUTOMATIC) NTC6FltParam_Cnt_T_u08 = 0U;
	VAR(NxtrDiagMgrStatus, AUTOMATIC) NTC6FltSts_Cnt_T_enum = NTC_STATUS_PASSED;
	VAR(uint8, AUTOMATIC) NTC7FltParam_Cnt_T_u08 = 0U;
	VAR(NxtrDiagMgrStatus, AUTOMATIC) NTC7FltSts_Cnt_T_enum = NTC_STATUS_PASSED;
	VAR(uint8, AUTOMATIC) NTC8FltParam_Cnt_T_u08 = 0U;
	VAR(NxtrDiagMgrStatus, AUTOMATIC) NTC8FltSts_Cnt_T_enum = NTC_STATUS_PASSED;
	VAR(uint8, AUTOMATIC) NTCAFltParam_Cnt_T_u08 = 0U;
	VAR(NxtrDiagMgrStatus, AUTOMATIC) NTCAFltSts_Cnt_T_enum = NTC_STATUS_PASSED;

	/* TODO: DET Checks on NvM vs NvMProxy configuration */
	
	/* Copy the data to protected memory, update Block Status Mirrors with NvM Status, skip the multi-block request index because it has special handling */
	for (i = (D_MULTIBLOCKID_CNT_U08 + 1U); i < D_NUMPRXYBLOCKS_CNT_U16; i++)
	{
		EEDiagFailed_Cnt_T_lgc = FALSE;

		switch (NvMProxyCfg[i].initHandling)
		{
			case NVMPROXY_CRC16:
				/* Copy Data from non-secured source location to secured destination location */
				(void)memcpy((void *)NvMProxyCfg[i].securePtr, (const void *)NvMProxyCfg[i].unsecurePtr, NvMProxyCfg[i].secureSize); /* PRQA S 3200 */ /* Return value is a pointer to the destination which is not needed in this algorithm */
				/* Update the block status shadow */
				NvM_GetErrorStatus(NvMProxyCfg[i].NvMBlock, &(NvMPWriteRqst_Cnt_M_Str[i].BlkStatus));

				/* Perform the CRC Check */
				CalcCRC_Cnt_T_u16 = Crc_CalculateCRC16(NvMProxyCfg[i].securePtr, (uint32)NvMProxyCfg[i].secureSize, NvMProxyCfg[i].NvMBlock);
				StrdCRC_Cnt_T_u16 = ((((uint16)(NvMProxyCfg[i].unsecurePtr)[NvMProxyCfg[i].secureSize])<<8U) | ((uint16)(NvMProxyCfg[i].unsecurePtr)[NvMProxyCfg[i].secureSize+1U]));

				if (CalcCRC_Cnt_T_u16 != StrdCRC_Cnt_T_u16)
				{
					EEDiagFailed_Cnt_T_lgc = TRUE;
				}
			break;
			case NVMPROXY_REDUNDANT:
				/* Copy Data from non-secured source location to secured destination location */
				(void)memcpy((void *)NvMProxyCfg[i].securePtr, (const void *)NvMProxyCfg[i].unsecurePtr, NvMProxyCfg[i].secureSize); /* PRQA S 3200 */ /* Return value is a pointer to the destination which is not needed in this algorithm */
				/* Update the block status shadow */
				NvM_GetErrorStatus(NvMProxyCfg[i].NvMBlock, &(NvMPWriteRqst_Cnt_M_Str[i].BlkStatus));

				/* Perform the Redundant Check */
				for (j = 0U; j < NvMProxyCfg[i].secureSize; j++)
				{
					if ((NvMProxyCfg[i].securePtr)[j] != (uint8)~(NvMProxyCfg[i].unsecurePtr)[j + NvMProxyCfg[i].secureSize])
					{
						EEDiagFailed_Cnt_T_lgc = TRUE;
					}
				}
			break;
			case NVMPROXY_ZERODATA:
				(void)memset((void*)NvMProxyCfg[i].securePtr, 0, NvMProxyCfg[i].secureSize);
				/* Update the block status shadow */
				NvM_GetErrorStatus(NvMProxyCfg[i].NvMBlock, &(NvMPWriteRqst_Cnt_M_Str[i].BlkStatus));
			break;
			default:
				/* Copy Data from non-secured source location to secured destination location */
				(void)memcpy((void *)NvMProxyCfg[i].securePtr, (const void *)NvMProxyCfg[i].unsecurePtr, NvMProxyCfg[i].secureSize); /* PRQA S 3200 */ /* Return value is a pointer to the destination which is not needed in this algorithm */
				/* Update the block status shadow */
				NvM_GetErrorStatus(NvMProxyCfg[i].NvMBlock, &(NvMPWriteRqst_Cnt_M_Str[i].BlkStatus));
			break;
		}

		if (TRUE == EEDiagFailed_Cnt_T_lgc)
		{
			switch (NvMProxyCfg[i].failResponse)
			{
				case NVMPROXY_NTC_0A:
					NTCAFltSts_Cnt_T_enum = NTC_STATUS_FAILED;
					NTCAFltParam_Cnt_T_u08 = (uint8)NvMProxyCfg[i].NvMBlock;
				break;
				case NVMPROXY_NTC_06_ROMDEF:
					NTC6FltSts_Cnt_T_enum = NTC_STATUS_FAILED;
					NTC6FltParam_Cnt_T_u08 = (uint8)NvMProxyCfg[i].NvMBlock;

					/* Load ROM Default Values */
					for (j = 0U; j < NvMProxyCfg[i].secureSize; j++)
					{
						(NvMProxyCfg[i].securePtr)[j] = NvMProxyCfg[i].failActData[j];
					}
				break;
				case NVMPROXY_NTC_07_ROMDEF:
					NTC7FltSts_Cnt_T_enum = NTC_STATUS_FAILED;
					NTC7FltParam_Cnt_T_u08 = (uint8)NvMProxyCfg[i].NvMBlock;

					/* Load ROM Default Values */
					for (j = 0U; j < NvMProxyCfg[i].secureSize; j++)
					{
						(NvMProxyCfg[i].securePtr)[j] = NvMProxyCfg[i].failActData[j];
					}
				break;
				case NVMPROXY_NTC_08_ROMDEF:
					NTC8FltSts_Cnt_T_enum = NTC_STATUS_FAILED;
					NTC8FltParam_Cnt_T_u08 = (uint8)NvMProxyCfg[i].NvMBlock;

					/* Load ROM Default Values */
					for (j = 0U; j < NvMProxyCfg[i].secureSize; j++)
					{
						(NvMProxyCfg[i].securePtr)[j] = NvMProxyCfg[i].failActData[j];
					}
				break;
				case NVMPROXY_NTC_06_NOTIFFUNC:
					NTC6FltSts_Cnt_T_enum = NTC_STATUS_FAILED;
					NTC6FltParam_Cnt_T_u08 = (uint8)NvMProxyCfg[i].NvMBlock;

					/* Call Notification Function */
					NvMProxyCfg[i].failActFunc();
				break;
				case NVMPROXY_NTC_07_NOTIFFUNC:
					NTC7FltSts_Cnt_T_enum = NTC_STATUS_FAILED;
					NTC7FltParam_Cnt_T_u08 = (uint8)NvMProxyCfg[i].NvMBlock;

					/* Call Notification Function */
					NvMProxyCfg[i].failActFunc();
				break;
				case NVMPROXY_NTC_08_NOTIFFUNC:
					NTC8FltSts_Cnt_T_enum = NTC_STATUS_FAILED;
					NTC8FltParam_Cnt_T_u08 = (uint8)NvMProxyCfg[i].NvMBlock;

					/* Call Notification Function */
					NvMProxyCfg[i].failActFunc();
				break;
				default:
				break;

			}
		}
	}
	
	(void)NVMPROXY_REPORTERRORSTATUS(NTC_Num_NvMBlkDftActA, NTC6FltParam_Cnt_T_u08, NTC6FltSts_Cnt_T_enum);
	(void)NVMPROXY_REPORTERRORSTATUS(NTC_Num_NvMBlkDftActB, NTC7FltParam_Cnt_T_u08, NTC7FltSts_Cnt_T_enum);
	(void)NVMPROXY_REPORTERRORSTATUS(NTC_Num_NvMBlkDftActC, NTC8FltParam_Cnt_T_u08, NTC8FltSts_Cnt_T_enum);
	(void)NVMPROXY_REPORTERRORSTATUS(NTC_Num_EEPROMDiag, NTCAFltParam_Cnt_T_u08, NTCAFltSts_Cnt_T_enum);

	/* Update the Multi-Block status shadow */
	NvM_GetErrorStatus(D_MULTIBLOCKID_CNT_U08, &(NvMPWriteRqst_Cnt_M_Str[D_MULTIBLOCKID_CNT_U08].BlkStatus));
}

/*****************************************************************************
  * Name:        NvMProxy_MainFunction
  * Description: (Non-Trusted)
  * Inputs:      None 
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, AUTOMATIC) NvMProxy_MainFunction( void )
{
	VAR(uint8, AUTOMATIC) i;
	VAR(uint16, AUTOMATIC) CalcCRC_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) j;

	/* In the event that E_OK is not returned from the NvM BSW this function will 
	 * retry the request on the subsequent MainFunction cycle
	 */
	
	/* Update Block Status Mirrors with NvM Status, skip the multi-block request index because it has special handling */
	for( i = (D_MULTIBLOCKID_CNT_U08 + 1U); i < D_NUMPRXYBLOCKS_CNT_U16; i++ )
	{
		/* Exclusive area protection is not required around the usage fo the shared resource NvMPWriteRqst_Cnt_M_Str because usage arbitration is based on the state of the Pend flag within a record */
		if(TRUE == NvMPWriteRqst_Cnt_M_Str[i].Pend)
		{			
			/* Copy the secured data area to the unsecured data area so that the NvM driver has write access for computation and update of a block Crc, if configured.
			 *  Ideally the data buffer used by the NvM driver for writing would be the secured data buffer, but at this time this Proxy is not fully implemented
			 *  and does not have CRC computation capability.  Crc calculation strategy is to be implemented in a future version of this Proxy.
			 */

			(void)memcpy((void *)NvMProxyCfg[i].unsecurePtr, (const void *)NvMProxyCfg[i].securePtr, NvMProxyCfg[i].secureSize); /* PRQA S 3200 */ /* Return value is a pointer to the destination which is not needed in this algorithm */

			if (NVMPROXY_CRC16 == NvMProxyCfg[i].initHandling)
			{
				CalcCRC_Cnt_T_u16 = Crc_CalculateCRC16(NvMProxyCfg[i].securePtr, (uint32)NvMProxyCfg[i].secureSize, NvMProxyCfg[i].NvMBlock);

				(NvMProxyCfg[i].unsecurePtr)[NvMProxyCfg[i].secureSize] = (uint8)(CalcCRC_Cnt_T_u16>>8U);
				(NvMProxyCfg[i].unsecurePtr)[NvMProxyCfg[i].secureSize+1U] = (uint8)(CalcCRC_Cnt_T_u16 & 0x00FFU);
			}
			else if (NVMPROXY_REDUNDANT == NvMProxyCfg[i].initHandling)
			{
				for (j = 0U; j < NvMProxyCfg[i].secureSize; j++)
				{
					(NvMProxyCfg[i].unsecurePtr)[j + NvMProxyCfg[i].secureSize] = (uint8)~(NvMProxyCfg[i].securePtr)[j];
				}
			}
			else
			{
				/* Do Nothing */
			}

			/* Forward Request to the NvM driver */
			if( E_OK == NvM_WriteBlock( NvMProxyCfg[i].NvMBlock, NULL_PTR))
			{
				/* The request was successfully forwarded to the NvM driver, clear the request forward pending flag */
				NvMPWriteRqst_Cnt_M_Str[i].Pend = FALSE;
			}
		}
		else if(TRUE == NvMPSetRBSRqst_Cnt_M_Str[i].Pend)
		{			
			/* Copy the secured data area to the unsecured data area so that the NvM driver has write access for computation and update of a block Crc, if configured.
			 *  Ideally the data buffer used by the NvM driver for writing would be the secured data buffer, but at this time this Proxy is not fully implemented
			 *  and does not have CRC computation capability.  Crc calculation strategy is to be implemented in a future version of this Proxy.
			 */

			(void)memcpy((void *)NvMProxyCfg[i].unsecurePtr, (const void *)NvMProxyCfg[i].securePtr, NvMProxyCfg[i].secureSize); /* PRQA S 3200 */ /* Return value is a pointer to the destination which is not needed in this algorithm */

			if (NVMPROXY_CRC16 == NvMProxyCfg[i].initHandling)
			{
				CalcCRC_Cnt_T_u16 = Crc_CalculateCRC16(NvMProxyCfg[i].securePtr, (uint32)NvMProxyCfg[i].secureSize, NvMProxyCfg[i].NvMBlock);

				(NvMProxyCfg[i].unsecurePtr)[NvMProxyCfg[i].secureSize] = (uint8)(CalcCRC_Cnt_T_u16>>8U);
				(NvMProxyCfg[i].unsecurePtr)[NvMProxyCfg[i].secureSize+1U] = (uint8)(CalcCRC_Cnt_T_u16 & 0x00FFU);
			}
			else if (NVMPROXY_REDUNDANT == NvMProxyCfg[i].initHandling)
			{
				for (j = 0U; j < NvMProxyCfg[i].secureSize; j++)
				{
					(NvMProxyCfg[i].unsecurePtr)[j + NvMProxyCfg[i].secureSize] = ~(NvMProxyCfg[i].securePtr)[j];
				}
			}
			else
			{
				/* Do Nothing */
			}

			/* Forward Request to the NvM driver */
			NvM_SetRamBlockStatus( NvMProxyCfg[i].NvMBlock, NvMPSetRBSRqst_Cnt_M_Str[i].BlockChanged );
			/* The SetRamBlockStatus API is always accepted by the NvM driver, clear the request forward pending flag */
			NvMPSetRBSRqst_Cnt_M_Str[i].Pend = FALSE;
		}
		else /* The request is not pending to be forwarded, update the mirror status with the NvM drivers status of the related block */
		{
			NvM_GetErrorStatus(NvMProxyCfg[i].NvMBlock, &(NvMPWriteRqst_Cnt_M_Str[i].BlkStatus));
		}
	}
	
	/* Forward WriteAll and update Multi-Block Status Mirror with NvM Status.
     * Forwarding of the WriteAll is performed after all of the SetRamBlock Status requests have been processed to ensure proper processing order.
	 */
	if(TRUE == NvMPWriteRqst_Cnt_M_Str[D_MULTIBLOCKID_CNT_U08].Pend)
	{
		NvM_WriteAll();
		NvMPWriteRqst_Cnt_M_Str[D_MULTIBLOCKID_CNT_U08].Pend = FALSE;
	}
	else /* The request is not pending to be forwarded, update the mirror status with the NvM drivers status of the related block */
	{
		NvM_GetErrorStatus(D_MULTIBLOCKID_CNT_U08, &(NvMPWriteRqst_Cnt_M_Str[D_MULTIBLOCKID_CNT_U08].BlkStatus));
	}
}


/*****************************************************************************
  * Name:        NvMProxy_WriteBlock
  * Description: 
  * Inputs:      None 
  * Outputs:     None
  *
*****************************************************************************/
FUNC(Std_ReturnType, AUTOMATIC) NvMProxy_WriteBlock(NvM_BlockIdType Block, P2CONST(uint8, AUTOMATIC, AUTOMATIC) SrcPtr)
{
	VAR(Std_ReturnType, AUTOMATIC) RetVal = E_NOT_OK;

	/* Provide Array over indexing protection because the caller might not be trusted */
	if((Block < D_NUMPRXYBLOCKS_CNT_U16) && (Block != D_MULTIBLOCKID_CNT_U08))
	{
		SchM_Enter_NvMProxy( NVMPROXY_EXCLUSIVE_AREA_0 );
		/* Accept the request only when a write operation on the block is not pending */
		if(NVM_REQ_PENDING != NvMPWriteRqst_Cnt_M_Str[Block].BlkStatus){	
			NvMPWriteRqst_Cnt_M_Str[Block].Pend = TRUE;
			NvMPWriteRqst_Cnt_M_Str[Block].SrcPtr = SrcPtr;
			/* Set the NvM Proxy mirror block status to indicate the Write is in progress */
			NvMPWriteRqst_Cnt_M_Str[Block].BlkStatus = NVM_REQ_PENDING;
			RetVal = E_OK;
		}
		SchM_Exit_NvMProxy( NVMPROXY_EXCLUSIVE_AREA_0 );
	}
	
	return(RetVal);
}

/*****************************************************************************
  * Name:        NvMProxy_WriteAll
  * Description: 
  * Inputs:      None 
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, AUTOMATIC) NvMProxy_WriteAll( void )
{
	SchM_Enter_NvMProxy( NVMPROXY_EXCLUSIVE_AREA_0 );
	/* Always sccept the request */
	NvMPWriteRqst_Cnt_M_Str[D_MULTIBLOCKID_CNT_U08].Pend = TRUE;
	/* Skip updating the source pointer, because it is not applicable to a multi-block request */
	/* Set the NvM Proxy mirror block status to indicate the Write is in progress */
	NvMPWriteRqst_Cnt_M_Str[D_MULTIBLOCKID_CNT_U08].BlkStatus = NVM_REQ_PENDING;
	SchM_Exit_NvMProxy( NVMPROXY_EXCLUSIVE_AREA_0 );
	
}

/*****************************************************************************
  * Name:        NvMProxy_GetErrorStatus
  * Description: 
  * Inputs:      None 
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, AUTOMATIC) NvMProxy_GetErrorStatus(NvM_BlockIdType Block, P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr)
{
	/* Provide Array over indexing protection because the caller might not be trusted */
	if(Block < D_NUMPRXYBLOCKS_CNT_U16)
	{
		*RequestResultPtr = NvMPWriteRqst_Cnt_M_Str[Block].BlkStatus;
	}
	else
	{
		*RequestResultPtr = NVM_REQ_NOT_OK;
	}
}

/*****************************************************************************
  * Name:        NvMProxy_SetRamBlockStatus
  * Description: 
  * Inputs:      None 
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, AUTOMATIC) NvMProxy_SetRamBlockStatus(NvM_BlockIdType Block, boolean BlockChanged)
{
	/* Provide Array over indexing protection because the caller might not be trusted */
	if((Block < D_NUMPRXYBLOCKS_CNT_U16) && (Block != D_MULTIBLOCKID_CNT_U08))
	{
		SchM_Enter_NvMProxy( NVMPROXY_EXCLUSIVE_AREA_0 );
		NvMPSetRBSRqst_Cnt_M_Str[Block].Pend = TRUE;
		NvMPSetRBSRqst_Cnt_M_Str[Block].BlockChanged = BlockChanged;		
		SchM_Exit_NvMProxy( NVMPROXY_EXCLUSIVE_AREA_0 );
	}
}


/**************************************************************************************************
* Local functions
**************************************************************************************************/


#define NVMPROXY_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */

