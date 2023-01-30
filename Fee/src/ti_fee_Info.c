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
 *         File:  ti_fee_info.c
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file implements the TI FEE Misc Api's.
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
 * 01.12.00		  13Dec2013     Vishwanath Reddy     SDOCM00105412    Traceability tags added. 
 *                                                                    MISRA C fixes.
 * 01.18.00		  12Oct2015     Vishwanath Reddy     SDOCM00119455    Update version history.
 * 01.18.01		  17Nov2015     Vishwanath Reddy     SDOCM00120161    Update version history.
 * 01.18.02		  05Feb2016     Vishwanath Reddy     SDOCM00121158    Update version history.
 *********************************************************************************************************************/

 
 /*********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "ti_fee.h"

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/**********************************************************************************************************************
 *  TI_Fee_GetVersionInfo
 *********************************************************************************************************************/
/*! \brief      This function returns the version information for the TI Fee module.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \return     none
 *  \context    Function could be called from task level
 *  \note       TI FEE API.
 *********************************************************************************************************************/
/* SourceId : HL_Fee_SourceId_12 */
/* DesignId : HL_FEE_DesignId_24 */
/* Requirements : HL_FEE_SR53, HL_FEE_SR54 */
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  This API will be called by application."*/
void TI_Fee_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr) 
{
	if(VersionInfoPtr != NULL_PTR)
	{
		VersionInfoPtr->sw_major_version = TI_FEE_MAJOR_VERSION;
		VersionInfoPtr->sw_minor_version = TI_FEE_MINOR_VERSION;
		VersionInfoPtr->sw_patch_version = TI_FEE_PATCH_VERSION;
	}	
}

/**********************************************************************************************************************
 *  TI_Fee_GetJobResult
 *********************************************************************************************************************/
/*! \brief      This function returns the Job result.
 *  \param[in]  u8EEPIndex
 *  \param[out] none
 *  \return     Job Result
 *  \context    Function could be called from task level
 *  \note       TI FEE API.
 **********************************************************************************************************************/
/* SourceId : HL_Fee_SourceId_10 */
/* DesignId : HL_FEE_DesignId_26 */
/* Requirements : HL_FEE_SR40, HL_FEE_SR41, HL_FEE_SR42, HL_FEE_SR43, HL_FEE_SR44, HL_FEE_SR45, HL_FEE_SR46*/
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  This API will be called by application."*/
TI_FeeJobResultType TI_Fee_GetJobResult(uint8 u8EEPIndex)
{
	return(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult);
}

/**********************************************************************************************************************
 *  TI_FeeErrorCode
 *********************************************************************************************************************/
/*! \brief      This function returns the Error status of the TI Fee module.
 *  \param[in]  u8EEPIndex
 *  \param[out] none
 *  \return     Error Code 
 *  \context    Function could be called from task level
 *  \note       TI FEE API.
 *********************************************************************************************************************/
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  This API will be called by application."*/
/* SourceId : HL_Fee_SourceId_36*/
/* DesignId : HL_FEE_DesignId_27 */
/* Requirements : HL_FEE_SR92 */ 
 TI_Fee_ErrorCodeType TI_FeeErrorCode(uint8 u8EEPIndex)
{
	return(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error);
}

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"
/*********************************************************************************************************************
 *  END OF FILE: ti_fee_info.c
 ********************************************************************************************************************/
