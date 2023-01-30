/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Cd_FeeIf.c
* Module Description: Fee interface module
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu Dec 16 13:41:03 2010
* %version:          3.1.1 %
* %derived_by:       nzdx8v %
* %date_modified:    Fri Jul 12 16:48:57 2013 % 
*---------------------------------------------------------------------------*/

#include "Cd_FeeIf.h"

/****************************************************************************
 *	Function Name:     FeeIf_Init
 *  Description:       Initialize Internal Variables and the Module Output value
 *  Inputs:            None
 *  Outputs:           None
 *****************************************************************************/
FUNC(void, FEEIF_CODE) FeeIf_Init(void)
{
	Fee_Init();
	/* TODO: Peform any Fee error recovery if necessary */

	while (MEMIF_BUSY == Fee_GetStatus())
	{
	  Fee_MainFunction();
	}
}

#if(BC_FEEIF_ECUSTARTUPTRUSTED == STD_OFF)

	/* FeeIf_Init Trusted Function Call Support */
	void TWrapC_FeeIf_Init(void)
	{
		(void)CallTrustedFunction((TrustedFunctionIndexType)TWrapS_FeeIf_Init, (TrustedFunctionParameterRefType)0);
	}
	void TRUSTED_TWrapS_FeeIf_Init(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
	{
		/* TODO: Do any parameter checking here if needed */
		FeeIf_Init();
	}

	/* Fee_MainFunction Trusted Function Call Support */
	void TWrapC_Fee_MainFunction(void)
	{
		(void)CallTrustedFunction((TrustedFunctionIndexType)TWrapS_Fee_MainFunction, (TrustedFunctionParameterRefType)0);
	}
	void TRUSTED_TWrapS_Fee_MainFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
	{
		/* TODO: Do any parameter checking here if needed */
		Fee_MainFunction();
	}

#endif

#if(BC_FEEIF_NVMTRUSTED == STD_OFF)

	/* Fee_SetMode -> Not required/empty function for current Fee Driver */

	/* Fee_Read Trusted Function Call Support */
	Std_ReturnType TWrapC_Fee_Read(uint16 BlockNumber,uint16 BlockOffset,uint8* DataBufferPtr,uint16 Length)
	{
		TrustedFunctionParameterType myargs;

		myargs.TWrapS_Fee_Read_args.os_arg_BlockNumber = BlockNumber;
		myargs.TWrapS_Fee_Read_args.os_arg_BlockOffset = BlockOffset;
		myargs.TWrapS_Fee_Read_args.os_arg_DataBufferPtr = DataBufferPtr;
		myargs.TWrapS_Fee_Read_args.os_arg_Length = Length;

		(void)CallTrustedFunction((TrustedFunctionIndexType)TWrapS_Fee_Read, &myargs);
		return (myargs.TWrapS_Fee_Read_args.os_result);
	}
	void TRUSTED_TWrapS_Fee_Read(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
	{
		/* TODO: Do any parameter checking here if needed */

		((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_Read_args.os_result = Fee_Read(((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_Read_args.os_arg_BlockNumber,
																								   ((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_Read_args.os_arg_BlockOffset,
																								   ((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_Read_args.os_arg_DataBufferPtr,
																								   ((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_Read_args.os_arg_Length);
	}

	/* Fee_Write Trusted Function Call Support */
	Std_ReturnType TWrapC_Fee_Write(uint16 BlockNumber,uint8* DataBufferPtr)
	{
		TrustedFunctionParameterType myargs;

		myargs.TWrapS_Fee_Write_args.os_arg_BlockNumber = BlockNumber;
		myargs.TWrapS_Fee_Write_args.os_arg_DataBufferPtr = DataBufferPtr;

		(void)CallTrustedFunction((TrustedFunctionIndexType)TWrapS_Fee_Write, &myargs);
		return (myargs.TWrapS_Fee_Write_args.os_result);
	}
	void TRUSTED_TWrapS_Fee_Write(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
	{
		/* TODO: Do any parameter checking here if needed */

		((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_Write_args.os_result = Fee_Write(((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_Write_args.os_arg_BlockNumber,
																							         ((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_Write_args.os_arg_DataBufferPtr);
	}

	/* Fee_EraseImmediateBlock Trusted Function Call Support */
	Std_ReturnType TWrapC_Fee_EraseImmediateBlock(uint16 BlockNumber)
	{
		TrustedFunctionParameterType myargs;

		myargs.TWrapS_Fee_EraseImmediateBlock_args.os_arg_BlockNumber = BlockNumber;

		(void)CallTrustedFunction((TrustedFunctionIndexType)TWrapS_Fee_EraseImmediateBlock, &myargs);
		return (myargs.TWrapS_Fee_EraseImmediateBlock_args.os_result);
	}
	void TRUSTED_TWrapS_Fee_EraseImmediateBlock(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
	{
		/* TODO: Do any parameter checking here if needed */

		((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_EraseImmediateBlock_args.os_result = Fee_EraseImmediateBlock(((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_EraseImmediateBlock_args.os_arg_BlockNumber);
	}

	/* Fee_InvalidateBlock Trusted Function Call Support */
	Std_ReturnType TWrapC_Fee_InvalidateBlock(uint16 BlockNumber)
	{
		TrustedFunctionParameterType myargs;

		myargs.TWrapS_Fee_InvalidateBlock_args.os_arg_BlockNumber = BlockNumber;

		(void)CallTrustedFunction((TrustedFunctionIndexType)TWrapS_Fee_InvalidateBlock, &myargs);
		return (myargs.TWrapS_Fee_InvalidateBlock_args.os_result);
	}
	void TRUSTED_TWrapS_Fee_InvalidateBlock(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
	{
		/* TODO: Do any parameter checking here if needed */

		((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_InvalidateBlock_args.os_result = Fee_InvalidateBlock(((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_InvalidateBlock_args.os_arg_BlockNumber);
	}

	/* Fee_Cancel Trusted Function Call Support */
	void TWrapC_Fee_Cancel(void)
	{
		(void)CallTrustedFunction((TrustedFunctionIndexType)TWrapS_Fee_Cancel, (TrustedFunctionParameterRefType)0);
	}
	void TRUSTED_TWrapS_Fee_Cancel(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
	{
		/* TODO: Do any parameter checking here if needed */
		Fee_Cancel();
	}

	/* Fee_GetStatus Trusted Function Call Support */
	uint8 TWrapC_Fee_GetStatus(void)
	{
		TrustedFunctionParameterType myargs;

		(void)CallTrustedFunction((TrustedFunctionIndexType)TWrapS_Fee_GetStatus, &myargs);
		return (myargs.TWrapS_Fee_GetStatus_args.os_result);
	}
	void TRUSTED_TWrapS_Fee_GetStatus(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
	{
		/* TODO: Do any parameter checking here if needed */

		((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_GetStatus_args.os_result = (uint8)Fee_GetStatus();
	}

	/* Fee_GetJobResult Trusted Function Call Support */
	uint8 TWrapC_Fee_GetJobResult(void)
	{
		TrustedFunctionParameterType myargs;

		(void)CallTrustedFunction((TrustedFunctionIndexType)TWrapS_Fee_GetJobResult, &myargs);
		return (myargs.TWrapS_Fee_GetJobResult_args.os_result);
	}
	void TRUSTED_TWrapS_Fee_GetJobResult(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
	{
		/* TODO: Do any parameter checking here if needed */

		((TrustedFunctionParameterType*)FunctionParams)->TWrapS_Fee_GetJobResult_args.os_result = (uint8)Fee_GetJobResult();
	}

	/* Suspend/Resume Erase API - Part of the ti_fee_util.c file */

	/* The command type is normally TI_Fee_EraseCommandType, but that data type is unknown to the OS, so the base type of uint8
	 * was used. This is typecasted back to TI_Fee_EraseCommandType on the trusted call side */
	void TWrapC_TI_Fee_SuspendResumeErase(uint8 Command)
	{
		TrustedFunctionParameterType myargs;

		myargs.TWrapS_TI_Fee_SuspendResumeErase_args.os_arg_Command = Command;

		(void)CallTrustedFunction((TrustedFunctionIndexType)TWrapS_TI_Fee_SuspendResumeErase, &myargs);
		return;
	}
	void TRUSTED_TWrapS_TI_Fee_SuspendResumeErase(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
	{
		 TI_Fee_SuspendResumeErase((TI_Fee_EraseCommandType)((TrustedFunctionParameterType*)FunctionParams)->TWrapS_TI_Fee_SuspendResumeErase_args.os_arg_Command);
	}

#endif
/******************************************************************************

CHANGE HISTORY:

 Date      Rev      Author          Change Description               SCR #
                                     (MDD Rev & Date)
-------   -------  --------  -----------------------------------   ----------
07/10/13   1.0     LWW        Initial Creation                     N/A
11/04/14   1.1.1   KJS        Added support for Suspend/Resume 
                              erease functions                     12677
12/15/14   1.1.2   PS         Added FEE Single bit ECC  
                              correction                           12802
01/27/15   3.1.1   PS         Updated new TT FEE component
                           	  and removed nexteer workaround
                           	  for FEE ECC correction			   12941
******************************************************************************/
