/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *                 TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *                 Property of Texas Instruments, Unauthorized reproduction and/or distribution
 *                 is strictly prohibited.  This product  is  protected  under  copyright  law
 *                 and  trade  secret law as an  unpublished work.
 *                 (C) Copyright Texas Instruments - 2012.  All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  fee.c
 *      Project:  Tms570_FEEDriver
 *       Module:  FEE Driver
 *    Generator:  None
 *
 *  Description:  This file implements the Autosar FEE 3.1 Api's.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  Vishwanath Reddy
 *---------------------------------------------------------------------------------------------------------------------
 * Revision History
 *---------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *---------------------------------------------------------------------------------------------------------------------
 * 00.01.00       07Sept2012    Vishwanath Reddy     0000000000000    Initial Version
 * 00.01.01       14Sept2012    Vishwanath Reddy     0000000000000    Review changes
 * 00.01.02       30Nov2012     Vishwanath Reddy     SDOCM00097786    Misra Fixes, Memory segmentation changes.
 * 00.01.03       14Jan2013     Vishwanath Reddy     SDOCM00098510    Changes as requested by Vector.
 * 00.01.04		  12Feb2012	  	Vishwanath Reddy     SDOCM00099152    Integration issues fix. 
 * 00.01.05		  04Mar2013	  	Vishwanath Reddy     SDOCM00099152    Added Deleting a block feature, bug fixes. 
 * 00.01.08		  05Apr2013	    Vishwanath Reddy     SDOCM00099152    Added feature : CRC check for unconfigured  blocks,
																	  Main function modified to complete writes as fast 
																	  as possible, Added Non polling mode support.
 * 00.01.09		  19Apr2013	  	Vishwanath Reddy     SDOCM00099152    Warning removal, Added feature comparision of data  
																	  during write.
 * 01.10.00		  21Apr2013	  	Vishwanath Reddy     SDOCM00104635    Corrected version information.
                                                                      Changes for supporting more than two VS.	
 * 01.20.00		  6Jan2013	  	Vishwanath Reddy     SDOCM00000000    Corrected version information.																	  
 * 01.20.01		  12Sep2014	  	Vishwanath Reddy     SDOCM00000000    Updated version information for SDOCM00112930.
 *                                                                    In API, Fee_InternalUpdateGlobalStructure first
 *                                                                    set the module state, then set the module result.   
 * 01.21.00		  15Oct2014     Vishwanath Reddy     SDOCM00113379    RAM Optimization changes. Version Info Updated.
 * 01.22.00		  26Dec2014     Vishwanath Reddy     SDOCM00114423    Changes for unification of Champion/Archer.
 *                                                                    Version Check Updated.
 *                                                                    Source, Design and Requirement tags added.
 * 01.23.00		  12Oct2015     Vishwanath Reddy     SDOCM00119455    Updated version information for SDOCM00119455.
 * 01.23.01		  17Nov2015     Vishwanath Reddy     SDOCM00120161    Updated version history.
 * 01.23.02		  10Mar2016     Vishwanath Reddy     SDOCM00121622    Updated version history. 
 *********************************************************************************************************************/

 
 /**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Fee.h"
#include "Fee_Cbk.h"
#include "SchM_Fee.h"
#include "Det.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Fee Version Check */
#if (FEE_AR_MAJOR_VERSION != 0x03U)
    #error Fee.c: FEE_AR_MAJOR_VERSION of Fee.h is incompatible.
#endif /* FEE_AR_MAJOR_VERSION */
#if (FEE_AR_MINOR_VERSION != 0x01)
    #error Fee.c: FEE_AR_MINOR_VERSION of Fee.h is incompatible.
#endif /* FEE_AR_MINOR_VERSION */
#if (FEE_AR_PATCH_VERSION != 0x00)
    #error Fee.c: FEE_AR_PATCH_VERSION of Fee.h is incompatible.
#endif /* FEE_AR_PATCH_VERSION */
#if (FEE_SW_MAJOR_VERSION != 1U)
    #error Fee.c: FEE_SW_MAJOR_VERSION of Fee.h is incompatible.
#endif /* FEE_SW_MAJOR_VERSION */
#if (FEE_SW_MINOR_VERSION != 23U)
    #error Fee.c: FEE_SW_MINOR_VERSION of Fee.h is incompatible.
#endif /* FEE_SW_MINOR_VERSION */
#if (FEE_SW_PATCH_VERSION != 2U)
    #error Fee.c: FEE_SW_PATCH_VERSION of Fee.h is incompatible.
#endif /* FEE_SW_PATCH_VERSION */

/**********************************************************************************************************************
 *  Configuration CHECK
 *********************************************************************************************************************/
#if ((FEE_NUMBER_OF_EEPS > 2U))
	#error fee.c: Number of EEP's can't be more than 2.
#endif	

/**********************************************************************************************************************
 *  General Global Variables/defines
 *********************************************************************************************************************/
/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_CONST_UNSPECIFIED
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"
const Fee_GeneralConfigType Fee_General=
{
    FEE_DEV_ERROR_DETECT,
  	FEE_INDEX,
    FEE_NVM_JOB_END_NOTIFICATION,
    FEE_NVM_JOB_ERROR_NOTIFICATION,
    FEE_POLLING_MODE,
    FEE_VERSION_INFO_API,        
	FEE_VIRTUAL_PAGE_SIZE   
};

const Fee_PublishedInformationType Fee_PublishedInformation =
{
    FEE_BLOCK_OVERHEAD,
    FEE_MAXIMUM_BLOCKING_TIME,
    FEE_PAGE_OVERHEAD,
	FEE_VIRTUAL_SECTOR_OVERHEAD	
};

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CONST_UNSPECIFIED
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/***********************************************************************************************************************
 *  Fee_Init
 **********************************************************************************************************************/
/*! \brief      This function is used to initialize the TI Fee module.
 *				It determines which Virtual Sector to use, sets up the Flash state machine.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \return     none
 *  \context    Function could be called from task level
 *  \note       Autosar FEE API.
 **********************************************************************************************************************/
/* SourceId : FEE_SourceId_001 */
/* DesignId : AR_FEE_DesignId_009 */
/* Requirements : AR_FEE_SR9, AR_FEE_SR10, AR_FEE_SR14, AR_FEE_SR30, AR_FEE_SR31, AR_FEE_SR32, AR_FEE_SR100, 
   AR_FEE_SR102 */
 void Fee_Init(void)
 {
	/* Call TI FEE Initialization API */
	TI_Fee_Init();		
	/* Update job result and module as required by MEMIF */
	Fee_InternalUpdateGlobalStructure();				
 }
 
 /***********************************************************************************************************************
 *  Fee_Write
 **********************************************************************************************************************/
/*! \brief      This function initiates the Write operation to a Block.
 *  \param[in]  uint16 BlockNumber
 *  \param[in]  uint8* DataBufferPtr
 *  \param[out] none
 *  \return     E_NOT_OK
 *  \return     E_OK
 *  \context    Function could be called from task level
 *  \note       Autosar FEE API.
 **********************************************************************************************************************/
/* SourceId : FEE_SourceId_002 */
/* DesignId : AR_FEE_DesignId_010 */
/* Requirements : AR_FEE_SR12, AR_FEE_SR39, AR_FEE_SR40, AR_FEE_SR41 */
 /*SAFETYMCUSW 62 D MR:16.7 <APPROVED> "Reason - since DataBufferPtr is modified by FEE, it cannot be declared de declared as const."*/
Std_ReturnType Fee_Write(uint16 BlockNumber,uint8* DataBufferPtr)
{
	/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside of FEE."*/
	Std_ReturnType oResult=E_OK;
	
	/* Call TI FEE Write API */
	oResult = TI_Fee_WriteAsync(BlockNumber,DataBufferPtr);	
	
	/* Update job result and module state as required by MEMIF */
	Fee_InternalUpdateGlobalStructure();
	
	return(oResult);
}

/***********************************************************************************************************************
 *  Fee_MainFunction
 **********************************************************************************************************************/
/*! \brief      This function is a cyclic function. It will Write data, Read Data, Invalidate Block, Erase Block,
 *				Copy blocks, Erase Sectors.
 *  \param[in]  none
 *  \param[in]  none
 *  \param[out] none
 *  \return     none 
 *  \context    Function could be called from task level
 *  \note       Autosar FEE API.
 **********************************************************************************************************************/
/* SourceId : FEE_SourceId_003 */
/* DesignId : AR_FEE_DesignId_017 */
/* Requirements : AR_FEE_SR15, AR_FEE_SR38, AR_FEE_SR42, AR_FEE_SR69, AR_FEE_SR70, AR_FEE_SR71, AR_FEE_SR72 */
 void Fee_MainFunction(void)
{
	/* Call TI FEE Main API */
	TI_Fee_MainFunction();	
	
	/* Update job result and module as required by MEMIF */
	Fee_InternalUpdateGlobalStructure();	
}

/***********************************************************************************************************************
 *  Fee_Read
 **********************************************************************************************************************/
/*! \brief      This function performs the Read operation on the Block.
 *  \param[in]  uint16 BlockNumber
 *  \param[in]  uint16 BlockOffset
 *  \param[in]  uint8* DataBufferPtr
 *  \param[in]  uint16 Length
 *  \param[out] none
 *  \return     none 
 *  \context    Function could be called from task level
 *  \note       Autosar FEE API.
 **********************************************************************************************************************/
/* SourceId : FEE_SourceId_004 */
/* DesignId : AR_FEE_DesignId_011 */
/* Requirements : AR_FEE_SR35, AR_FEE_SR36, AR_FEE_SR37, AR_FEE_SR99 */
 /*SAFETYMCUSW 62 D MR:16.7 <APPROVED> "Reason - since DataBufferPtr is modified by FEE, it cannot be declared de declared as const."*/
Std_ReturnType Fee_Read(uint16 BlockNumber,uint16 BlockOffset,uint8* DataBufferPtr,uint16 Length)
{
	/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside of FEE."*/
	Std_ReturnType oResult=E_OK;
	
	/* Call TI FEE Read API */
	oResult = TI_Fee_Read(BlockNumber,BlockOffset,DataBufferPtr,Length);	
	
	/* Update job result and module state as required by MEMIF */
	Fee_InternalUpdateGlobalStructure();
			
	return(oResult);	
}

/***********************************************************************************************************************
 *  Fee_EraseImmediateBlock
 **********************************************************************************************************************/
/*! \brief     	This function performs the Erase Immediate operation on a block .
 *  \param[in]	uint16 BlockNumber
 *  \param[out] none 
 *  \return 	Std_ReturnType
 *  \context    
 *  \note       Autosar FEE API.
 **********************************************************************************************************************/
/* SourceId : FEE_SourceId_005 */
/* DesignId : AR_FEE_DesignId_012 */
/* Requirements : AR_FEE_SR58, AR_FEE_SR59, AR_FEE_SR60, AR_FEE_SR61 */
 Std_ReturnType Fee_EraseImmediateBlock(uint16 BlockNumber)
{
	/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside of FEE."*/
	Std_ReturnType oResult=E_OK;
	#if (FEE_DEV_ERROR_DETECT == STD_ON)
	uint8 u8EEPIndex = 0U;
	#endif
	
	/* Call TI FEE Erase Immediate API */
	oResult = TI_Fee_EraseImmediateBlock(BlockNumber);	
	
	/* Update job result and module state as required by MEMIF */
	Fee_InternalUpdateGlobalStructure();
	
	/* If the detection of developement error is enabled, report DET error */	
	#if (FEE_DEV_ERROR_DETECT == STD_ON)
	if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_BlockInvalid)
	#if(FEE_NUMBER_OF_EEPS == 2U)
	||(TI_Fee_GlobalVariables[u8EEPIndex+1U].Fee_Error == Error_BlockInvalid)
	#endif
	)
	{
		(void)Det_ReportError(FEE_MODULE_ID,FEE_INSTANCE_ID,FEE_SID_ERASEIMMEDIATEBLOCK,FEE_E_INVALID_BLOCK_NO);
	}
		
	
	if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_InvalidBlockIndex)
	#if(FEE_NUMBER_OF_EEPS == 2U)
	||(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_InvalidBlockIndex)
	#endif
	)
	{
		(void)Det_ReportError(FEE_MODULE_ID,FEE_INSTANCE_ID,FEE_SID_INVALIDATEBLOCK,FEE_E_INVALID_BLOCK_NO);
	}		
	#endif
			
	return(oResult);
}

/***********************************************************************************************************************
 *  Fee_InvalidateBlock
 **********************************************************************************************************************/
/*! \brief     	This function performs the Invalidate operation on a block .
 *  \param[in]	uint16 BlockNumber
 *  \param[out] none 
 *  \return 	Std_ReturnType
 *  \context    
 *  \note       Autosar FEE API.
 **********************************************************************************************************************/
/* SourceId : FEE_SourceId_006 */
/* DesignId : AR_FEE_DesignId_013 */
/* Requirements : AR_FEE_SR51, AR_FEE_SR52, AR_FEE_SR53 */
 Std_ReturnType Fee_InvalidateBlock(uint16 BlockNumber)
{
	/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside of FEE."*/
	Std_ReturnType oResult=E_OK;

	/* Call TI FEE Invalidate Block API */
	oResult = TI_Fee_InvalidateBlock(BlockNumber);	
	
	/* Update job result and module state as required by MEMIF */
	Fee_InternalUpdateGlobalStructure();
			
	return(oResult);
}

/***********************************************************************************************************************
 *  Fee_Cancel
 **********************************************************************************************************************/
/*! \brief     	This functions cancels an ongoing operation.
 *  \param[in]	uint16 BlockNumber
 *  \param[out] none 
 *  \return 	Std_ReturnType
 *  \context    
 *  \note       Autosar FEE API.
 **********************************************************************************************************************/
/* SourceId : FEE_SourceId_007 */
/* DesignId : AR_FEE_DesignId_019 */
/* Requirements : AR_FEE_SR43, AR_FEE_SR44, AR_FEE_SR45 */
 void Fee_Cancel(void)
{
	uint8 u8EEPIndex = 0U;
	
	/* Call TI FEE Cancel API */
	TI_Fee_Cancel(u8EEPIndex);
	#if(FEE_NUMBER_OF_EEPS == 2U)
	TI_Fee_Cancel(u8EEPIndex+1U);
	#endif	
	
	/* Update job result and module state as required by MEMIF */
	Fee_InternalUpdateGlobalStructure();
}

/***********************************************************************************************************************
 *  Fee_GetStatus
 **********************************************************************************************************************/
/*! \brief      This function is pre-compile time configurable by the parameter FlsGetStatusApi
 *  \param[in]	none
 *  \param[out] none 
 *  \return 	MemIf_StatusType
 *  \context    
 *  \note       Autosar FEE API.
 **********************************************************************************************************************/
/* This function returns the Status of the FEE module */
/* SourceId : FEE_SourceId_008 */
/* DesignId : AR_FEE_DesignId_015 */
/* Requirements : AR_FEE_SR46, AR_FEE_SR47, AR_FEE_SR48 */
MemIf_StatusType Fee_GetStatus(void)
{
	#if(FEE_NUMBER_OF_EEPS == 1U)
	uint8 u8EEPIndex = 0U;
	#endif
	MemIf_StatusType ModuleState = MEMIF_UNINIT;	
	
	/* Update job result and module state as required by MEMIF */
	Fee_InternalUpdateGlobalStructure();
	
	#if(FEE_NUMBER_OF_EEPS == 2U)
	ModuleState = Fee_InternalGetStatus();		
	#elif(FEE_NUMBER_OF_EEPS == 1U)	
	if((TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Erase != 0U)||
	   (TI_Fee_oStatusWord[0].Fee_StatusWordType_ST.Copy != 0U)		
	  )
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY;
	}
	else
	{
		ModuleState = (MemIf_StatusType)TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState;
	}
	#endif	
	return(ModuleState);
}

/***********************************************************************************************************************
 *  Fee_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief      This function is pre-compile time configurable by the parameter FEE_VERSION_INFO_API
 *  \param[in]	Std_VersionInfoType* VersionInfoPtr
 *  \param[out] none 
 *  \return 	none
 *  \context    
 *  \note       Autosar FEE API.
 **********************************************************************************************************************/
/* SourceId : FEE_SourceId_009 */
/* DesignId : AR_FEE_DesignId_014 */
/* Requirements : AR_FEE_SR54, AR_FEE_SR55, AR_FEE_SR56, AR_FEE_SR57 */
 #if (FEE_VERSION_INFO_API == STD_ON)
/* This function returns the version information for the Fee module */
void Fee_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr)
{
	if(NULL_PTR != VersionInfoPtr)
	{
		VersionInfoPtr->moduleID = FEE_MODULE_ID;
		VersionInfoPtr->vendorID = FEE_VENDOR_ID;
		VersionInfoPtr->sw_major_version = FEE_SW_MAJOR_VERSION;
		VersionInfoPtr->sw_minor_version = FEE_SW_MINOR_VERSION;
		VersionInfoPtr->sw_patch_version = FEE_SW_PATCH_VERSION;
	}	
}
#endif

/***********************************************************************************************************************
 *  Fee_SetMode
 **********************************************************************************************************************/
/*! \brief      This function sets the Fee module's operation mode to the given "Mode" parameter
 *  \param[in]	Std_VersionInfoType* VersionInfoPtr
 *  \param[out] none 
 *  \return 	none
 *  \context    
 *  \note       Autosar FEE API.
 **********************************************************************************************************************/
/* SourceId : FEE_SourceId_010 */
/* DesignId : AR_FEE_DesignId_018 */
/* Requirements : AR_FEE_SR33, AR_FEE_SR34 */
 void Fee_SetMode(MemIf_ModeType Mode)
{
	/* This is a dummy function */
	/* To avoid MISRA warning */
	Mode=Mode;
}

/***********************************************************************************************************************
 *  Fee_GetJobResult
 **********************************************************************************************************************/
/*! \brief      This function returns the Job result.
 *  \param[in]  u8EEPIndex
 *  \param[out] none
 *  \return     Job Result
 *  \context    Function could be called from task level
 *  \note       TI FEE API.
 **********************************************************************************************************************/
/* SourceId : FEE_SourceId_011 */
/* DesignId : AR_FEE_DesignId_016 */
/* Requirements : AR_FEE_SR49, AR_FEE_SR50 */
 MemIf_JobResultType Fee_GetJobResult(void)
{	
	/* Update job result and module as required by MEMIF */
	Fee_InternalUpdateGlobalStructure();	
	
	return((MemIf_JobResultType)TI_Fee_GlobalVariables[TI_Fee_u8DeviceIndex].Fee_u16JobResult);
}

/***********************************************************************************************************************
 *  Fee_InternalUpdateGlobalStructure
 **********************************************************************************************************************/
/*! \brief      This function updates the module state and job result.
 *  \param[in]	none
 *  \param[out] none 
 *  \return 	none
 *  \context    
 *  \note       FEE Internal API.
 **********************************************************************************************************************/ 
static 
void Fee_InternalUpdateGlobalStructure(void)
{	
	uint8 u8EEPIndex = 0U;	
 
	while(u8EEPIndex<FEE_NUMBER_OF_EEPS)
	{	
		/* Update correct info for MEMIF */
		switch (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult)
		{
			case JOB_OK :
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = (TI_FeeJobResultType)MEMIF_JOB_OK;
				break;
			case JOB_FAILED:	
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = (TI_FeeJobResultType)MEMIF_JOB_FAILED;
				break;
			case JOB_PENDING:
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = (TI_FeeJobResultType)MEMIF_JOB_PENDING;
				break;
			case JOB_CANCELLED:
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = (TI_FeeJobResultType)MEMIF_JOB_CANCELLED;
				break;
			case BLOCK_INCONSISTENT:
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = (TI_FeeJobResultType)MEMIF_BLOCK_INCONSISTENT;
				break;
			case BLOCK_INVALID:
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = (TI_FeeJobResultType)MEMIF_BLOCK_INVALID;
				break;
			default:
				break;
		}
		switch (TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState)
		{
			case IDLE:
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = (TI_FeeModuleStatusType)MEMIF_IDLE;
				break;
			case BUSY:
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = (TI_FeeModuleStatusType)MEMIF_BUSY;
				break;
			case BUSY_INTERNAL:
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = (TI_FeeModuleStatusType)MEMIF_BUSY_INTERNAL;
				break;
			default :
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = (TI_FeeModuleStatusType)MEMIF_UNINIT;
				break;
		}
		if((TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Erase != 0U))
		{
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = (TI_FeeJobResultType)MEMIF_JOB_PENDING;
		}
		u8EEPIndex++;
	}
}


#if(FEE_NUMBER_OF_EEPS == 2U)
static 
MemIf_StatusType Fee_InternalGetStatus(void)
{
	MemIf_StatusType ModuleState = MEMIF_UNINIT;
	
	if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_UNINIT)	
	   &&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_UNINIT))
	{
		ModuleState = (MemIf_StatusType)MEMIF_UNINIT;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_UNINIT)	
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_IDLE))
	{
		ModuleState = (MemIf_StatusType)MEMIF_IDLE;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_UNINIT)	
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_BUSY))	
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY;
	}	
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_UNINIT)	
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_BUSY_INTERNAL))
	{
		ModuleState =(MemIf_StatusType) MEMIF_BUSY_INTERNAL;
	}
	else
	{
		/* MISRA C Compliance */
	}
	
	
	if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_IDLE)	
	   &&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_UNINIT))
	{
		ModuleState = (MemIf_StatusType)MEMIF_IDLE;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_IDLE)	
		    &&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_IDLE))	
	{
		ModuleState =(MemIf_StatusType) MEMIF_IDLE;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_IDLE)	
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_BUSY))	
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY;
	}	
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_IDLE)	
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_BUSY_INTERNAL))
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY_INTERNAL;
	}
	else
	{
		/* MISRA C Compliance */
	}
		
	if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_BUSY)	
		&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_UNINIT))
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_BUSY)	
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_IDLE))
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_BUSY)	
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_BUSY))	
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY;
	}	
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_BUSY)	
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_BUSY_INTERNAL))
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY;
	}
	else
	{
		/* MISRA C Compliance */
	}
		
	
	if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_BUSY_INTERNAL)
		&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_UNINIT))	 	
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY_INTERNAL;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_BUSY_INTERNAL)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_IDLE))	
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY_INTERNAL;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_BUSY_INTERNAL)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_BUSY))
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY;
	}	
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == MEMIF_BUSY_INTERNAL)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == MEMIF_BUSY_INTERNAL))
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY_INTERNAL;
	}
	else
	{
		/* MISRA C Compliance */
	}
	
	
	if((TI_Fee_oStatusWord[0].Fee_StatusWordType_ST.Erase != 0U) ||
	   (TI_Fee_oStatusWord[1].Fee_StatusWordType_ST.Erase != 0U) ||
	   (TI_Fee_oStatusWord[0].Fee_StatusWordType_ST.Copy != 0U) ||
	   (TI_Fee_oStatusWord[1].Fee_StatusWordType_ST.Copy != 0U)
	  )
	{
		ModuleState = (MemIf_StatusType)MEMIF_BUSY;
	}	
	return(ModuleState);
}
#endif

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/**********************************************************************************************************************
 *  END OF FILE: fee.c
 *********************************************************************************************************************/
 

