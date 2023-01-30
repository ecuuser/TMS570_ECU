/*******************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : NtWrap.h
* Module Description: Non-trusted function call wrapper definitions to allow
*						calling of SCom server functions not located in the
*						application with the Diag service handler.
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*******************************************************************************/
/*******************************************************************************
* Version Control:
* Date Created:      Tue Jan  7 15:00:00 2014
* %version:          2 %
* %derived_by:       nzx5jd %
* %date_modified:    Tue Jan 28 14:35:28 2014 %
*******************************************************************************/
/*******************************************************************************
* Change History:
* Date      Rev      Author    Change Description
* --------  -------  --------  ------------------------------------------------
* 01/07/14   1       OT        Initial version (Ap8 and Ap9)
* 01/28/14   2       OT        Updated polarity non-trusted call per updated polarity component
* 04/21/14   3       OT        Added non-trusted function call for InvalidateSlowADCGroup
*******************************************************************************/

#ifndef NTWRAP_H
#define NTWRAP_H

#include "Std_Types.h"
#include "Rte_Type.h"
#include "Os.h"
#include "Wdg_TMS570LS3x.h"
#include "WdgM.h"


/***** RTE Client Function Prototypes *****/

extern FUNC(void,           RTE_NTWRAP_APPL_CODE) NtWrapC_AbsHwPos_SCom_CustClrTrim(void);
extern FUNC(Std_ReturnType, RTE_NTWRAP_APPL_CODE) NtWrapC_AbsHwPos_SCom_CustSetTrim(void);
extern FUNC(void,           RTE_NTWRAP_APPL_CODE) NtWrapC_AbsHwPos_SCom_NxtClearTrim(void);
extern FUNC(Std_ReturnType, RTE_NTWRAP_APPL_CODE) NtWrapC_AbsHwPos_SCom_NxtSetTrim(Float Offset_HwDeg_T_f32);
extern FUNC(Std_ReturnType, RTE_NTWRAP_APPL_CODE) NtWrapC_AstLmt_Scom_ManualTrqCmd(Boolean EnableManualCtrl, Float MtrTrqCmd_MtrNm_f32);
extern FUNC(Std_ReturnType, RTE_NTWRAP_APPL_CODE) NtWrapC_CmMtrCurr_SCom_CalGain(void);
extern FUNC(Std_ReturnType, RTE_NTWRAP_APPL_CODE) NtWrapC_CmMtrCurr_SCom_CalOffset(void);
extern FUNC(void,           RTE_NTWRAP_APPL_CODE) NtWrapC_CmMtrCurr_SCom_SetMtrCurrCals(P2CONST(PhaseCurrCal_DataType, AUTOMATIC, RTE_NTWRAP_APPL_DATA) ShCurrCalPtr);
extern FUNC(Std_ReturnType, RTE_NTWRAP_APPL_CODE) NtWrapC_DigHwTrqSENT_SCom_ClrTrqTrim(void);
extern FUNC(Std_ReturnType, RTE_NTWRAP_APPL_CODE) NtWrapC_DigHwTrqSENT_SCom_SetTrqTrim(void);
extern FUNC(void,           RTE_NTWRAP_APPL_CODE) NtWrapC_Polarity_SCom_SetPolarity(UInt8 Polarity_Cnt_T_b08);
extern FUNC(void,           RTE_NTWRAP_APPL_CODE) NtWrapC_SCom_EOLNomMtrParam_Set(Float NomKe_VpRadpS_f32, Float NomRmtr_Ohm_f32);
extern FUNC(void,           RTE_NTWRAP_APPL_CODE) NtWrapC_TrqCanc_Scom_SetCogTrqCal(P2CONST(CoggingCancTrq, AUTOMATIC, RTE_NTWRAP_APPL_DATA) CogTrqCalPtr, UInt16 ID);
extern FUNC(void,           RTE_NTWRAP_APPL_CODE) NtWrapC_TrqCmdScl_SCom_Set(Float Par_f32);


/***** Non-RTE Client Function Prototypes *****/

extern FUNC(void, NTWRAP_CODE) TWrapC_CallFblStart(void);
extern FUNC(void, NTWRAP_CODE) TWrapC_Adc_Init( void * ConfigSet );
extern FUNC(void, NTWRAP_CODE) TWrapC_Adc2_Init1(void);
extern FUNC(void, NTWRAP_CODE) TWrapC_PwmCdd_Init(void);
extern FUNC(void, NTWRAP_CODE) TWrapC_StaMd_Init0(void);
extern FUNC(void, NTWRAP_CODE) TWrapC_Wdg_TMS570LS3x_Init( P2CONST(Wdg_TMS570LS3x_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr );
extern FUNC(void, NTWRAP_CODE) TWrapC_WdgM_Init( P2CONST (WdgM_ConfigType, AUTOMATIC, WDGM_APPL_CONST) WdgMConfigPtr );
extern FUNC(void, NTWRAP_CODE) TWrapC_NvMProxy_Init(void);
extern FUNC(void, NTWRAP_CODE) TWrapC_Dma_InvalidateSlowADCGroup(void);
extern FUNC(void, NTWRAP_CODE) TWrapC_ProcessF0FF(P2VAR(uint8, AUTOMATIC, AUTOMATIC) t_SrvcData_Cnt_T_u08, VAR(uint16, AUTOMATIC) RequestDataIdx_Cnt_T_u16);


/***** XCP Function Prototypes *****/

extern FUNC(void, NTWRAP_CODE) NONTRUSTED_NtWrapS_XcpWriteAp8( VAR(NonTrustedFunctionIndexType, AUTOMATIC) Index_Cnt_T_u16, VAR(NonTrustedFunctionParameterRefType, AUTOMATIC) Par );
extern FUNC(void, NTWRAP_CODE) NONTRUSTED_NtWrapS_XcpWriteAp9( VAR(NonTrustedFunctionIndexType, AUTOMATIC) Index_Cnt_T_u16, VAR(NonTrustedFunctionParameterRefType, AUTOMATIC) Par );
extern FUNC(void, NTWRAP_CODE) TRUSTED_TWrapS_XcpWriteAp0( VAR(TrustedFunctionIndexType, AUTOMATIC) Index_Cnt_T_u16, VAR(TrustedFunctionParameterRefType, AUTOMATIC) Par );

#endif
