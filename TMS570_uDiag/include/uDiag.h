/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : uDiag.h
* Module Description: Micro Diagnostic Common Header File
* Product           : Gen II Plus - EA3.0
* Author            : Lonnie Newton
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue May 31 09:10:25 2011 %
* %version:          9 %
* %derived_by:       nz63rn %
* %date_modified:    Mon Apr  7 10:26:06 2014 %
*---------------------------------------------------------------------------------------------------------------------
* Date      Rev      Author         Change Description                                                        SCR #
* -------   -------  --------  ---------------------------------------------------------------------------  ----------
* 07/13/12  2        LWW       Defined UDIAG_COMPILER_ISR for isr declaration
* 07/19/12  3        LN        Added Channel Definitions														5769
* 09/18/12  4        JJW       Added inclusion of uDiag_Cfg.h
* 11/29/12  5        LWW       Added WdgResetHandler
* 05/30/13  6        KMC	   Added inclusion of uDiagFPU_Init1, uDiagFPU_Init2, and Mcu_FpuIsr
* 10/10/13  7        KMC       Added conditional compiled NHET2 parity ESM channel -- for fix of anomaly 5801  10404
*                              Added trusted function support for RednRpdShtdn call from uDiagVIM_Per -- for   10408
*                              fix of anomaly 5810.  QAC cleanup.
* 01/06/14	8        KMC       Added prototypes for uDiag init functions that were previously RTE functions    11158
*                              Added constant for ESM group 3 channel 7 FMC uncorr ECC error, and changed 	   11176
*                              name of constant for ESM group 2 channel 4 FMC uncorr address parity error. 
*                              Added trusted function support for RednRpdShtdn call from uDiagECC_Per.  QAC
*                              cleanup.
* 04/07/14  9        KMC       Added prototypes for DMA parity error handling function and peripheral MPU      11435
*                              init.  Added constant for ESM channel for DMA parity.  Separated function 
*                              prototypes into "private" and "public" areas of file.
*/

#ifndef U_DIAG_H
#define U_DIAG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "uDiag_Cfg.h"

#if ((BC_UDIAG_UDIAGVIMPERTRUSTED == STD_OFF) || (BC_UDIAG_UDIAGECCPERTRUSTED == STD_OFF))
#include "Os.h"
#include "trustfct.h"
#endif

 
/*** Private Part (used by internal uDiag files only) *************************************/
#ifdef UDIAG_C

/**********************************************************************************************************************
 *  UDIAG PRIVATE GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
  
#define D_NTCPARMBIT0_CNT_U8		0x01U
#define D_NTCPARMBIT1_CNT_U8		0x02U
#define D_NTCPARMBIT2_CNT_U8		0x04U
#define D_NTCPARMBIT3_CNT_U8		0x08U
#define D_NTCPARMBIT4_CNT_U8		0x10U
#define D_NTCPARMBIT5_CNT_U8		0x20U
#define D_NTCPARMBIT6_CNT_U8		0x40U
#define D_NTCPARMBIT7_CNT_U8		0x80U

#define D_ADC1_CNT_U8				0U
#define D_ADC2_CNT_U8				1U
#define D_DCAN1_CNT_U8				0U
#define D_DCAN2_CNT_U8				1U
#define D_DCC1_CNT_U8				0U
#define D_DCC2_CNT_U8				1U
#define D_EVENBANK_CNT_U8			0U
#define D_ODDBANK_CNT_U8			1U

#define D_ADC2PARESMCHANNEL_CNT_U32			0x00000002UL		/* Group 1 - Channel 1 */
#define D_DMAMPUESMCHANNEL_CNT_U32			0x00000004UL		/* Group 1 - Channel 2 */
#define D_DMAPARESMCHANNEL_CNT_U32			0x00000008UL		/* Group 1 - Channel 2 */
#define D_FMCCORESMCHANNEL_CNT_U32			0x00000040UL		/* Group 1 - Channel 6 */
#define D_NHETPARESMCHANNEL_CNT_U32			0x00000080UL		/* Group 1 - Channel 7 */
#define D_HTUPARESMCHANNEL_CNT_U32			0x00000100UL		/* Group 1 - Channel 8 */
#define D_HTUMPUESMCHANNEL_CNT_U32			0x00000200UL		/* Group 1 - Channel 9 */
#define D_CLCKMONINTESMCHANNEL_CNT_U32		0x00000800UL		/* Group 1 - Channel 11 */
#define D_ADC1PARESMCHANNEL_CNT_U32			0x00080000UL 	    /* Group 1 - Channel 19 */
#define D_DCAN1PARESMCHANNEL_CNT_U32		0x00200000UL		/* Group 1 - Channel 21 */
#define D_DCAN2PARESMCHANNEL_CNT_U32		0x00800000UL		/* Group 1 - Channel 23 */
#define D_RAMEVENCORESMCHANNEL_CNT_U32		0x04000000UL		/* Group 1 - Channel 26 */
#define D_RAMODDCORESMCHANNEL_CNT_U32		0x10000000UL		/* Group 1 - Channel 28 */
#define D_DCC1ESMCHANNEL_CNT_U32			0x40000000UL		/* Group 1 - Channel 30 */

#if (BC_UDIAG_GLADIATORCOMPATIBLE == STD_OFF)
#define D_NHET2PARESMCHANNEL_CNT_U32        0x00000004UL        /* Group 1 - Channel 34 */
#endif

#define D_IOMMESMCHANNEL_CNT_U32			0x00000020UL		/* Group 1 - Channel 37 */
#define D_DCC2ESMCHANNEL_CNT_U32			0x40000000UL		/* Group 1 - Channel 62 */

#define D_CCMR4COMPESMCHANNEL_CNT_U32		0x00000004UL		/* Group 2 - Channel 2 */
#define D_FMCUNCADDRPARESMCHANNEL_CNT_U32	0x00000010UL		/* Group 2 - Channel 4 FMC uncorrectable address parity error */
#define D_RAMEVENUNCESMCHANNEL_CNT_U32		0x00000040UL		/* Group 2 - Channel 6 */
#define D_RAMODDUNCESMCHANNEL_CNT_U32		0x00000100UL		/* Group 2 - Channel 8 */
#define D_RAMEVENADDPARESMCHANNEL_CNT_U32	0x00000400UL		/* Group 2 - Channel 10 */
#define D_RAMODDADDPARESMCHANNEL_CNT_U32	0x00001000UL		/* Group 2 - Channel 12 */
#define D_ECCLIVELOCKESMCHANNEL_CNT_U32		0x00010000UL		/* Group 2 - Channel 16 */

#define D_FMCUNCECCESMCHANNEL_CNT_U32		0x00000080UL 		/* Group 3 - Channel 7 FMC uncorrectable ECC error (not address parity) */

#define D_VIMTABLESIZE_CNT_U8		96U

/**********************************************************************************************************************
 *  UDIAG PRIVATE GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
FUNC(void, CD_UDIAG_APPL_CODE) NHETParityErr(void);
FUNC(void, CD_UDIAG_APPL_CODE) NHET2ParityErr(void);
FUNC(void, CD_UDIAG_APPL_CODE) HTUParityErr(void);
FUNC(void, CD_UDIAG_APPL_CODE) HTUMPUErr(void);
FUNC(void, CD_UDIAG_APPL_CODE) ADCParityErr(uint8 module);
FUNC(void, CD_UDIAG_APPL_CODE) DCANParityErr(uint8 module);
FUNC(void, CD_UDIAG_APPL_CODE) DMAParityErr(void);
FUNC(void, CD_UDIAG_APPL_CODE) RAMParityErr(uint8 module);
FUNC(void, CD_UDIAG_APPL_CODE) IOMMErr(void);
FUNC(void, CD_UDIAG_APPL_CODE) FlashECCCorrErr(void);
FUNC(void, CD_UDIAG_APPL_CODE) RAMECCCorrErr(uint8 BANK);
FUNC(void, CD_UDIAG_APPL_CODE) FlashECCUncorrErr(void);
FUNC(void, CD_UDIAG_APPL_CODE) RAMECCUncorrErr(uint8 BANK);
FUNC(void, CD_UDIAG_APPL_CODE) FlashECCLiveLockErr(void);
FUNC(void, CD_UDIAG_APPL_CODE) ClockMonitorErr(void);
FUNC(void, CD_UDIAG_APPL_CODE) DCCErr(uint8 module);
FUNC(void, CD_UDIAG_APPL_CODE) CCRMErr(void);
FUNC(void, CD_UDIAG_APPL_CODE) DMAMPUErr(void);

/**********************************************************************************************************************
 *  UDIAG PRIVATE GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  UDIAG PRIVATE GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 extern uint32 D_VIMTABLENAME_CNT_U32[D_VIMTABLESIZE_CNT_U8];

#endif /* UDIAG_C */
/*** Public Part  *****************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* UDIAG_COMPILER_ISR used in external function declaration */
#define UDIAG_COMPILER_ISR    interrupt


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
FUNC(void, CD_UDIAG_APPL_CODE) WdgResetHandler(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagFPU_Init1(void); 
FUNC(void, CD_UDIAG_APPL_CODE) uDiagFPU_Init2(void); 
UDIAG_COMPILER_ISR void Mcu_FpuIrq(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagVIM_RednRpdShtdn(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagECC_RednRpdShtdn(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagCCRM_Init(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagClockMonitor_Init(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagECC_Init(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagESM_Init(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagIOMM_Init(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagPeriphMPU_Init(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagParity_Init(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagStaticRegs_Init(void);
FUNC(void, CD_UDIAG_APPL_CODE) uDiagVIM_Init(void);
FUNC(void, CD_UDIAG_APPL_CODE) MicroDiag_Per1(void);

#if(BC_UDIAG_UDIAGVIMPERTRUSTED == STD_OFF) 
	void TWrapC_uDiagVIM_RednRpdShtdn(void);
	void TRUSTED_TWrapS_uDiagVIM_RednRpdShtdn(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
#endif

#if(BC_UDIAG_UDIAGECCPERTRUSTED == STD_OFF) 
	void TWrapC_uDiagECC_RednRpdShtdn(void);
	void TRUSTED_TWrapS_uDiagECC_RednRpdShtdn(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
#endif

#endif  /* U_DIAG_H */

/**********************************************************************************************************************
 *  END OF FILE: uDiag.h
 *********************************************************************************************************************/
