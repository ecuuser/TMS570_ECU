/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Cd_FeeIf.h
* Module Description: Fee interface header
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue May 31 09:10:25 2011 %
* %version:          1 %
* %derived_by:       czgng4 %
* %date_modified:    Fri Jul 12 16:48:51 2013 %
*---------------------------------------------------------------------------------------------------------------------
* Date      Rev      Author         Change Description                                                        SCR #
* -------   -------  --------  ---------------------------------------------------------------------------  ----------
* 07/11/13  1        LWW       Initial Version
*/

#ifndef CD_FEEIF_H
#define CD_FEEIF_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "MemIf_Types.h"
#include "fee.h"
#include "Cd_NvMMgr_Cfg.h"
#if(BC_FEEIF_NVMTRUSTED == STD_OFF) || (BC_FEEIF_ECUSTARTUPTRUSTED == STD_OFF)
#include "Os.h"
#include "trustfct.h"
#endif

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

FUNC(void, FEEIF_CODE) FeeIf_Init(void);

#if(BC_FEEIF_ECUSTARTUPTRUSTED == STD_OFF)
	void TWrapC_FeeIf_Init(void);
	void TRUSTED_TWrapS_FeeIf_Init(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
	void TWrapC_Fee_MainFunction(void);
	void TRUSTED_TWrapS_Fee_MainFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
#endif

#if(BC_FEEIF_NVMTRUSTED == STD_OFF)
	Std_ReturnType TWrapC_Fee_Read(uint16 BlockNumber,uint16 BlockOffset,uint8* DataBufferPtr,uint16 Length);
	void TRUSTED_TWrapS_Fee_Read(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
	Std_ReturnType TWrapC_Fee_Write(uint16 BlockNumber,uint8* DataBufferPtr);
	void TRUSTED_TWrapS_Fee_Write(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
	Std_ReturnType TWrapC_Fee_EraseImmediateBlock(uint16 BlockNumber);
	void TRUSTED_TWrapS_Fee_EraseImmediateBlock(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
	Std_ReturnType TWrapC_Fee_InvalidateBlock(uint16 BlockNumber);
	void TRUSTED_TWrapS_Fee_InvalidateBlock(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
	void TWrapC_Fee_Cancel(void);
	void TRUSTED_TWrapS_Fee_Cancel(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
	uint8 TWrapC_Fee_GetStatus(void);
	void TRUSTED_TWrapS_Fee_GetStatus(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
	uint8 TWrapC_Fee_GetJobResult(void);
	void TRUSTED_TWrapS_Fee_GetJobResult(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
	void TWrapC_TI_Fee_SuspendResumeErase(uint8 Command);
	void TRUSTED_TWrapS_TI_Fee_SuspendResumeErase(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
#endif

#endif  /* CD_FEEIF_H */
