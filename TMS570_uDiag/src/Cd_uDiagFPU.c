/*****************************************************************************
* Copyright 2011 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Cd_uDiagFPU.c
* Module Description: FPU exception diagnostics
* Product           : Gen II Plus - EA3.0
* Author            : Kathleen Creager
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Mon May 20 13:53:48 2013
* %version:          2 %
* %derived_by:       nz63rn %
* %date_modified:    Wed Jun 26 09:45:37 2013 % 
*---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ---------
 * 05/20/13   1       KMC		Initial Version
 * 06/26/13   2       KMC       Added D_ENABLEFPUDIAG_CNT_LGC to enable/disable FPU exception handling         7139
 */

#define UDIAG_C /* to include module private section of header */
#include "uDiag.h"
#include "Os.h"
#include "Interrupts.h"
#include "Ap_DiagMgr.h"
#include "RednRpdShtdn.h"
#include "sys_core.h"
#include "Cd_uDiagUtility.h"

#pragma INTERRUPT(Mcu_FpuIrq, FIQ);
#pragma CODE_STATE(Mcu_FpuIrq, 32);

#define UDIAG_START_SEC_VAR_SAVED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(uint32, CD_UDIAG_VAR_NOINIT) FPUExceptionAddr_Cnt_D_u32;
#define UDIAG_STOP_SEC_VAR_SAVED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


/* FPSCR exception flag bits */
#define D_FPSCRBITIOC_CNT_U32       0x00000001U
#define D_FPSCRBITDZC_CNT_U32       0x00000002U
#define D_FPSCRBITOFC_CNT_U32       0x00000004U


/* Secondary Auxiliary Control Register FPU exception output bits to enable */
#define D_VFPEXCEPTIONOUTPUTEN_CNT_U32	   0x00001600U  /* Bit8 = IDC, Bit9 = DZC, Bit10 = IOC, Bit11 = UFC, Bit12 = OFC, Bit13 = IXC */


/*****************************************************************************
  * Name:        Mcu_FpuIrq
  * Description: Nexteer extension to the AUTOSAR specification.  Handles FPU failures detected by VFP peripheral
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
UDIAG_COMPILER_ISR void Mcu_FpuIrq(void)
{

    VAR(uint32, AUTOMATIC) FPUStatusReg_Cnt_T_u32;
	VAR(ENUM_ResetCause, AUTOMATIC) ResetCause_Cnt_T_Enum;
	
	FPUExceptionAddr_Cnt_D_u32 = _uDiagGetLinkRegForFiqIsr_();
	FPUStatusReg_Cnt_T_u32 = _coreGetFPSCR_();
	if ((FPUStatusReg_Cnt_T_u32 & D_FPSCRBITDZC_CNT_U32) != 0U)
	{
		ResetCause_Cnt_T_Enum = FPUDZCEXCP;
	}
	else if ((FPUStatusReg_Cnt_T_u32 & D_FPSCRBITOFC_CNT_U32) != 0U)
	{
		ResetCause_Cnt_T_Enum = FPUOFCEXCP;
	}
	else if ((FPUStatusReg_Cnt_T_u32 & D_FPSCRBITIOC_CNT_U32) != 0U)
	{
		ResetCause_Cnt_T_Enum = FPUIOCEXCP;
	}
	else /* unknown FPU Exception */
	{
		ResetCause_Cnt_T_Enum = FPUUNKNOWNEXCP;
	}
	RednRpdShtdn (ResetCause_Cnt_T_Enum);

}

/**********************************************************************************************************************
 *
 * Name: uDiagFPU_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once before the OS is started
 *
 *********************************************************************************************************************/

FUNC(void, CD_UDIAG_APPL_CODE) uDiagFPU_Init1(void)
{

#if( D_ENABLEFPUDIAG_CNT_LGC != STD_OFF ) /* check != STD_OFF so code will be included if symbol not defined */

	VAR(uint32, AUTOMATIC) SecAuxCtrlRegVal_Cnt_T_u32;
	VAR(ENUM_ResetCause, AUTOMATIC) ResetCause_Cnt_T_Enum;

	ResetCause_Cnt_T_Enum = ResetCause_Cnt_Enum;
	
	if ((ResetCause_Cnt_T_Enum != FPUDZCEXCP) &&
	    (ResetCause_Cnt_T_Enum != FPUOFCEXCP) &&
		(ResetCause_Cnt_T_Enum != FPUIOCEXCP) &&
		(ResetCause_Cnt_T_Enum != FPUUNKNOWNEXCP))
	{
		SecAuxCtrlRegVal_Cnt_T_u32 = _coreGetSecondaryAuxiliaryControlRegister_();
		SecAuxCtrlRegVal_Cnt_T_u32 |= D_VFPEXCEPTIONOUTPUTEN_CNT_U32;
		_coreSetSecondaryAuxiliaryControlRegister_(SecAuxCtrlRegVal_Cnt_T_u32);
	}
#endif	
}
  
/**********************************************************************************************************************
 *
 * Name: uDiagFPU_Init2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the OS is started (but before the RTE is started)
 *
 *********************************************************************************************************************/

FUNC(void, CD_UDIAG_APPL_CODE) uDiagFPU_Init2(void)
{
#if( D_ENABLEFPUDIAG_CNT_LGC != STD_OFF ) /* check != STD_OFF so code will be included if symbol not defined */

	VAR(ENUM_ResetCause, AUTOMATIC) ResetCause_Cnt_T_Enum;

	ResetCause_Cnt_T_Enum = ResetCause_Cnt_Enum;

	if ((ResetCause_Cnt_T_Enum != FPUDZCEXCP) &&
	    (ResetCause_Cnt_T_Enum != FPUOFCEXCP) &&
		(ResetCause_Cnt_T_Enum != FPUIOCEXCP) &&
		(ResetCause_Cnt_T_Enum != FPUUNKNOWNEXCP))
	{
	    EnableVFPInterrupt();
	}
	
#endif
}



