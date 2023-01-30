/*****************************************************************************
* Copyright 2015 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : AppStartup.c
* Module Description: Application Startup Sequence
* Product           : Gen II Plus EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri May 11 12:17:00 2012
 * %version:          8 %
 * %derived_by:       nz63rn %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/09/12  1        LWW       Initial Version
 * 07/06/12  2        LWW       Updates for conditional compilation, removed data abort function, corrected
 *                              FPAROVR reg value on single bit flash ECC test, updated flashBadECC pointer value,
 *                              DCAN parity test logic changes, added read on FUNCERRADD after flashecc test
 * 09/28/12	 3		  LN		Corrected anomaly 3784 by reading TCRAMs uncorrectable Error Address Register
 * 								after the initialization test causes a fault.									6350
 * 11/29/12  4        LWW       Added WdgResetHandler call
 * 02/14/13  5        LWW       Anomaly correction on ADC parity functions
 * 08/02/13  6        LWW       Anomaly 3689 correction, changes to allow thumb mode compilation
 * 10/03/13  7        LWW       Anomaly 5758 correction
 * 02/02/15  8        KMC		ICR 4700 update -- add DMA MPU and HTU MPU startup prooftests					CR12836
 */

#include <string.h> /* provide and memcpy() definition */
#include "system_regs.h"
#include "esm_regs.h"
#include "efc_regs.h"
#include "stc_regs.h"
#include "pbist_regs.h"
#include "mibspi_regs.h"
#include "n2het_regs.h"
#include "adc_regs.h"
#include "htu_regs.h"
#include "dcan_regs.h"
#include "dma_regs.h"
#include "vim_regs.h"
#include "flash_regs.h"
#include "pcr_regs.h"
#include "tcram_regs.h"
#include "ccm_regs.h"
#include "gio_regs.h"
#include "appinit_cfg.h"
#include "ResetCause.h"
#include "sys_core.h"
#include "uDiag.h"
#include "prooftestv02.h"

/* PRQA S 303 EOF 
 * MISRA-C:2004 Rule 11.3: This deviation is required for register access.  The rule is suppressed for the entire file */

/* MISRA-C:2004 Rule 19.1: This deviation is required for AUTOSAR memory map requirements.  Rule suppressed by line at each occurrence. */

typedef struct
{
	uint64  DummyVarForAlignment_Cnt_u64;
	uint32  TestVar1_Cnt_u32;
	uint32  TestVar2_Cnt_u32;
} DmaMPUTest_Str;

#if (MIBADC1_PARITY_ENABLE)
static void adc1ParityCheck(void);
#define D_ADC1RAMLOC_CNT_U32		0xFF3E0000U
#define D_ADC1RAMPARLOC_CNT_U32		0xFF3E1000U
#endif

#if (MIBADC2_PARITY_ENABLE)
static void adc2ParityCheck(void);
#define D_ADC2RAMLOC_CNT_U32		0xFF3A0000U
#define D_ADC2RAMPARLOC_CNT_U32		0xFF3A1000U
#endif

#if (DCAN1_PARITY_ENABLE)
static void dcan1ParityCheck(void);
#define D_DCAN1RAMPARLOC_CNT_U32	0xFF1E0010U
#define D_DCAN1RAMLOC_CNT_U32		0xFF1E0000U
#endif

#if (DCAN2_PARITY_ENABLE)
static void dcan2ParityCheck(void);
#define D_DCAN2RAMPARLOC_CNT_U32	0xFF1C0010U
#define D_DCAN2RAMLOC_CNT_U32		0xFF1C0000U
#endif

#if (DCAN3_PARITY_ENABLE)
static void dcan3ParityCheck(void);
#define D_DCAN3RAMPARLOC_CNT_U32	0xFF1A0010U
#define D_DCAN3RAMLOC_CNT_U32		0xFF1A0000U
#endif

#if (MIBSPI1_PARITY_ENABLE)
static void mibspi1ParityCheck(void);
#define D_SPI1RAMPARLOC_CNT_U32		0xFF0E0400U
#define D_SPI1RAMLOC_CNT_U32		0xFF0E0000U
#endif

#if (MIBSPI3_PARITY_ENABLE)
static void mibspi3parityCheck(void);
#define D_SPI3RAMPARLOC_CNT_U32		0xFF0C0400U
#define D_SPI3RAMLOC_CNT_U32		0xFF0C0000U
#endif

#if (MIBSPI5_PARITY_ENABLE)
static void mibspi5ParityCheck(void);
#define D_SPI5RAMPARLOC_CNT_U32		0xFF0A0400U
#define D_SPI5RAMLOC_CNT_U32		0xFF0A0000U
#endif

#if (N2HET1_PARITY_ENABLE)
static void nhet1ParityCheck(void);
#define D_NHET1RAMPARLOC_CNT_U32	0xFF462000U
#define D_NHET1RAMLOC_CNT_U32		0xFF460000U
#endif

#if (N2HET2_PARITY_ENABLE)
static void nhet2parityCheck(void);
#define D_NHET2RAMPARLOC_CNT_U32	0xFF442000U
#define D_NHET2RAMLOC_CNT_U32		0xFF440000U
#endif

#if (N2HET1TU_PARITY_ENABLE)
static void htu1ParityCheck(void);
#define D_HTU1RAMPARLOC_CNT_U32		0xFF4E0200U
#define D_HTU1RAMLOC_CNT_U32		0xFF4E0000U
#endif

#if (N2HET2TU_PARITY_ENABLE)
static void htu2ParityCheck(void);
#define D_HTU2RAMPARLOC_CNT_U32		0xFF4C0200U
#define D_HTU2RAMLOC_CNT_U32		0xFF4C0000U
#endif

#if (VIM_PARITY_ENABLE)
static void vimParityCheck(void);
#define D_VIMRAMPARLOC_CNT_U32		0xFFF82400U
#define D_VIMRAMLOC_CNT_U32			0xFFF82000U
#endif

#if (DMA_PARITY_ENABLE)
static void dmaParityCheck(void);
#define D_DMARAMLOC_CNT_U32			0xFFF80000U
#define D_DMARAMPARLOC_CNT_U32		0xFFF80A00U
#endif

#if ((N2HET1TU_MPU_ENABLE) || (N2HET2TU_MPU_ENABLE))
static void WaitForHtuTransfer(const volatile uint32* const FRCTR_ptr);
/* Address offsets in NHET RAM for HTU Startup MPU test */
/* The "16" is length in bytes of each HET instruction.  Never changes */
/* The "8" is the byte offset to get the data field */
#define D_HTUSTARTUPADDR1_CNT_U32 	((uint32)(16U*(uint16)pHET_trans1_7) + 8UL)
#define D_HTUSTARTUPADDR2_CNT_U32 	((uint32)(16U*(uint16)pHET_mvstrt2_7) + 8UL)
#define D_HTUSTARTUPADDR3_CNT_U32 	((uint32)(16U*(uint16)pHET_trans3_7) + 8UL)
#define D_HTUSTARTUPADDR4_CNT_U32 	((uint32)(16U*(uint16)pHET_mvstrt4_7) + 8UL)

#define D_HTUDATA1_CNT_U32 		(0x01UL << 7) /* NHET Low Res data HTUData1 */
#define D_HTUDATA2_CNT_U32 		(0x02UL << 7) /* NHET Low Res data HTUData2 */
#define D_HTUDATA3_CNT_U32 		(0x03UL << 7) /* NHET Low Res data HTUData3 */
#define D_HTUDATA4_CNT_U32 		(0x04UL << 7) /* NHET Low Res data HTUData4 */
#define D_HTUDUMMYDATA_CNT_U32 	(55UL << 7)   /* NHET Low Res data DUMMY */
#define D_HTUTESTDATA_CNT_U32	(0xAAAAAAAAUL) /* test data pattern for main memory */
#define D_HTUTESTWAIT_CNT_U32 	(0x03UL << 7) /* NHET Low Res counter 3 LR loops */
#define D_HTUWAITTIMEOUT_CNT_U16 240U /* timeout loop counter */
#endif

#if (N2HET1TU_MPU_ENABLE)
#define STARTUP_START_SEC_VAR_NOINIT_32
#include "MemMap.h" /* PRQA S 5087 */
static volatile uint32 HTU1MPUTest_Cnt_M_u32[4];
#define STARTUP_STOP_SEC_VAR_NOINIT_32
#include "MemMap.h" /* PRQA S 5087 */
static void StartupHTU1Init(void);
static void Nhet1HTUMPUCheck(void);
#define D_BASEADDNHET1RAM_CNT_U32  (0xFF460000UL)
#endif

#if (N2HET2TU_MPU_ENABLE)
#define STARTUP_START_SEC_VAR_NOINIT_32
#include "MemMap.h" /* PRQA S 5087 */
static volatile uint32 HTU2MPUTest_Cnt_M_u32[4];
#define STARTUP_STOP_SEC_VAR_NOINIT_32
#include "MemMap.h" /* PRQA S 5087 */
static void StartupHTU2Init(void);
static void Nhet2HTUMPUCheck(void);
#define D_BASEADDNHET2RAM_CNT_U32  (0xFF440000UL)
#endif

#if (DMA_MPU_ENABLE)
#define STARTUP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
static volatile DmaMPUTest_Str DmaMPUTest1_Uls_M_str; /* PRQA S 3218 */
/* MISRA-C:2004 Rule 8.7: This deviation is required to keep the memory map intact. */
static volatile DmaMPUTest_Str DmaMPUTest2_Uls_M_str;
#define STARTUP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
static void WaitForDmaTransfer(void);
static void DmaMpuCheck(void);
#define D_DMAMPUTESTDATA1_CNT_U32 (0xAAAAAAAAUL)
#define D_DMAMPUTESTDATA2_CNT_U32 (0x55555555UL)
#define D_DMAMPUTESTDATA3_CNT_U32 (0x00000000UL)
#define D_DMAMPUTESTDATA4_CNT_U32 (0xFFFFFFFFUL)
#define D_DMAWAITLOOPCOUNT_CNT_U16 40U
#endif

#define D_TCRAMA1BITERROR_CNT_U32	0x08400000
#define D_TCRAMA2BITERROR_CNT_U32 	0x08400010
#define D_TCRAMB1BITERROR_CNT_U32	0x08400008
#define D_TCRAMB2BITERROR_CNT_U32 	0x08400018
#define D_TCRAMA1BIT_CNT_U32		0x08000000
#define D_TCRAMA2BIT_CNT_U32		0x08000010
#define D_TCRAMB1BIT_CNT_U32		0x08000008
#define D_TCRAMB2BIT_CNT_U32		0x08000018
#define D_FLASHBADECC_CNT_U32		0x20000020

static void checkB0RAMECC(void);
static void checkB1RAMECC(void);
static void checkFlashECC(void);
static void DiagFailed(void);
static void AppInit(void);
static void Startup(void);

typedef void (*handler_fptr)(const unsigned char *in, unsigned char *out);

#pragma WEAK(__TI_Handler_Table_Base)
#pragma WEAK(__TI_Handler_Table_Limit)
#pragma WEAK(__TI_CINIT_Base)
#pragma WEAK(__TI_CINIT_Limit)

extern unsigned   __TI_Handler_Table_Base;
extern unsigned   __TI_Handler_Table_Limit;
extern unsigned   __TI_CINIT_Base;
extern unsigned   __TI_CINIT_Limit;
extern unsigned   __TI_PINIT_Base;
extern unsigned   __TI_PINIT_Limit;
extern unsigned * __binit__;

extern void main(void);
extern void AppStartupCallout1(void);
extern void AppStartupCallout2(void);

#pragma INTERRUPT(Startup, RESET)
#pragma INTERRUPT(_c_int00, RESET)
#pragma CODE_STATE(_c_int00, 32);

void _c_int00()
{
	Startup();
}
static void Startup(void)
{
	/* Initialize Application Stack Pointers */
	 _coreInitRegisters_();

	 /* Callout for Application Specific processing */
	 AppStartupCallout1();

	/* Release the MibSPIx modules from local reset.
	 * This will cause the MibSPIx RAMs to get initialized along with the parity memory.
	 */
#if (MIBSPI1_ENABLE)
	mibspiREG1->GCR0 = 0x1;
#endif
#if (MIBSPI3_ENABLE)
	mibspiREG3->GCR0 = 0x1;
#endif
#if (MIBSPI5_ENABLE)
	mibspiREG5->GCR0 = 0x1;
#endif
#if (GIO_ENABLE)
    gioCTRL->GCR0 = 1; /* This is the Offset of the GIO module */
#endif

    if (DEBUGRESET == ResetCause_Cnt_Enum)
    {
    	asm(" B $");
    }

    /* Determine Type of Watchdog Reset */
    if (WDGFAIL == ResetCause_Cnt_Enum)
    {
    	WdgResetHandler();
    }

/***************************** INITIALIZATION STEP 29 ****************************/
	/* Test the CPU ECC mechanism for RAM accesses.
	 * The checkBxRAMECC functions cause deliberate single-bit and double-bit errors in TCRAM accesses
	 * by corrupting 1 or 2 bits in the ECC. Reading from the TCRAM location with a 2-bit error
	 * in the ECC causes a data abort exception. The data abort handler is written to look for
	 * deliberately caused exception and to return the code execution to the instruction
	 * following the one that caused the abort.
	 */

    if (PWRONRESET == ResetCause_Cnt_Enum)
    {
		checkB0RAMECC();
		checkB1RAMECC();

/***************************** INITIALIZATION STEP 30 ****************************/
		/* Test the CPU ECC mechanism for Flash accesses.
		 * The checkFlashECC function uses the flash interface module's diagnostic mode 7
		 * to create single-bit and double-bit errors in CPU accesses to the flash. A double-bit
		 * error on reading from flash causes a data abort exception.
		 * The data abort handler is written to look for deliberately caused exception and
		 * to return the code execution to the instruction following the one that was aborted.
		 *
		 */
		checkFlashECC();
		flashWREG->FDIAGCTRL = 0x000A0007;					/* disable flash diagnostic mode */

/***************************** INITIALIZATION STEP 36A ***************************/

		#if (N2HET1_PARITY_ENABLE)
			nhet1ParityCheck();
		#endif
		#if (N2HET1TU_PARITY_ENABLE)
			htu1ParityCheck();
		#endif
		#if (N2HET2_PARITY_ENABLE)
			nhet2parityCheck();
		#endif
		#if (N2HET2TU_PARITY_ENABLE)
			htu2ParityCheck();
		#endif
		#if (MIBADC1_PARITY_ENABLE)
			adc1ParityCheck();
		#endif
		#if (MIBADC2_PARITY_ENABLE)
			adc2ParityCheck();
		#endif
		#if (DCAN1_PARITY_ENABLE)
			dcan1ParityCheck();
		#endif
		#if (DCAN2_PARITY_ENABLE)
			dcan2ParityCheck();
		#endif
		#if (DCAN3_PARITY_ENABLE)
			dcan3ParityCheck();
		#endif
		#if (VIM_PARITY_ENABLE)
			vimParityCheck();
		#endif
		#if (DMA_PARITY_ENABLE)
			dmaParityCheck();
		#endif
		#if (N2HET1TU_MPU_ENABLE)
			Nhet1HTUMPUCheck();
		#endif
		#if (N2HET2TU_MPU_ENABLE)
			Nhet2HTUMPUCheck();
		#endif
		#if (DMA_MPU_ENABLE)
			DmaMpuCheck();
		#endif

		/***************************** INITIALIZATION STEP 35 ****************************/
		/* Wait for MibSPIx memory initialization to complete */
		#if (MIBSPI1_ENABLE)
			while (mibspiREG1->BUFINIT);
		#endif
		#if (MIBSPI3_ENABLE)
			while (mibspiREG3->BUFINIT);
		#endif
		#if (MIBSPI5_ENABLE)
			while (mibspiREG5->BUFINIT);
		#endif

		/***************************** INITIALIZATION STEP 36B ***************************/
		#if (MIBSPI1_PARITY_ENABLE)
			mibspi1ParityCheck();
		#endif
		#if (MIBSPI3_PARITY_ENABLE)
			mibspi3parityCheck();
		#endif
		#if (MIBSPI5_PARITY_ENABLE)
			mibspi5ParityCheck();
		#endif
    }
	else
	{
		#if (VIM_PARITY_ENABLE)
			VIMPAR->PARCTL = 0x0000000A;
		#endif
		#if (DMA_PARITY_ENABLE)
			DMACTRLREG->DMAPCR = 0x0000000A;
		#endif
		#if (N2HET1_PARITY_ENABLE)
			NHET0->NHETPCR = 0x0000000A;
		#endif
		#if (N2HET1TU_PARITY_ENABLE)
			htuREG1->PCR = 0x0000000A;
		#endif
		#if (N2HET2_PARITY_ENABLE)
			NHET1->NHETPCR = 0x0000000A;
		#endif
		#if (N2HET2TU_PARITY_ENABLE)
			htuREG2->PCR = 0x0000000A;
		#endif
		#if (MIBADC1_PARITY_ENABLE)
			adcREG1->PARCR = 0x0000000A;
		#endif
		#if (MIBADC2_PARITY_ENABLE)
			adcREG2->PARCR = 0x0000000A;
		#endif
		#if (DCAN1_PARITY_ENABLE)
			DCAN1REG->CTL = 0x00002800;
		#endif
		#if (DCAN2_PARITY_ENABLE)
			DCAN2REG->CTL = 0x00002800;
		#endif
		#if (DCAN3_PARITY_ENABLE)
			DCAN3REG->CTL = 0x00002800;
		#endif
		#if (MIBSPI1_PARITY_ENABLE)
			mibspiREG1->MIBSPIE = 0x1;
			mibspiREG1->EDEN = 0xA;
		#endif
		#if (MIBSPI3_PARITY_ENABLE)
			mibspiREG3->MIBSPIE = 0x1;
			mibspiREG3->EDEN = 0xA;
		#endif
		#if (MIBSPI5_PARITY_ENABLE)
			mibspiREG5->MIBSPIE = 0x1;
			mibspiREG5->EDEN = 0xA;
		#endif
	}

    AppInit();

}

#if (VIM_PARITY_ENABLE)
/* Routine to check VIM RAM parity error detection and signaling mechanism */
static void vimParityCheck(void)
{
	volatile uint32 vimramread_Cnt_T_u32;

	VIMPAR->PARCTL = 0x0000010A;				/* Enable parity checking and parity test mode */
	(*(volatile uint32 *)D_VIMRAMPARLOC_CNT_U32) ^= 0x1;					/* flip a bit in the VIM RAM parity location */
	VIMPAR->PARCTL = 0x0000000A;				/* disable parity test mode */

	vimramread_Cnt_T_u32 = *(volatile uint32 *)D_VIMRAMLOC_CNT_U32;					/* cause parity error */

	if (0x1 != VIMPAR->PARFLG)
	{
		ResetCause_Cnt_Enum = VIMPARFLGFAILED;
		ESMREGS->ESMSR1 = 0x8000;		/* clear ESM group1 channel 15 flag */
		*(volatile uint32 *)D_VIMRAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
		DiagFailed();

	}
	else if (D_VIMRAMLOC_CNT_U32 != VIMPAR->ADDERR)
	{
		ResetCause_Cnt_Enum = VIMPARADDERRFAILED;
		VIMPAR->PARFLG = 0x1;					/* clear VIM RAM parity error flag in VIM */
		ESMREGS->ESMSR1 = 0x8000;		/* clear ESM group1 channel 15 flag */
		*(volatile uint32 *)D_VIMRAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
		DiagFailed();
	}
	else if (0U == (ESMREGS->ESMSR1 & 0x8000))	/* check if ESM group1 channel 15 is flagged */
	{
		/* VIM RAM parity error was not flagged to ESM. */
		ResetCause_Cnt_Enum = VIMPARESMFAILED;
		VIMPAR->PARFLG = 0x1;					/* clear VIM RAM parity error flag in VIM */
		*(volatile uint32 *)D_VIMRAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
		DiagFailed();
	}
	else
	{
		VIMPAR->PARFLG = 0x1;					/* clear VIM RAM parity error flag in VIM */
		ESMREGS->ESMSR1 = 0x8000;		/* clear ESM group1 channel 15 flag */
		*(volatile uint32 *)D_VIMRAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
	}
}
#endif

#if (DMA_PARITY_ENABLE)
/* Routine to check DMA control packet RAM parity error detection and signaling mechanism */
static void dmaParityCheck(void)
{
	volatile uint32 dmaread_Cnt_T_u32;

	DMACTRLREG->DMAPCR = 0x0000010A;					/* Enable parity checking and parity test mode */
	(*(volatile uint32 *)D_DMARAMPARLOC_CNT_U32) ^= 0x1;					/* Flip a bit in DMA RAM parity location */
	DMACTRLREG->DMAPCR = 0x0000000A;					/* Disable parity test mode */

	dmaread_Cnt_T_u32 = *(volatile uint32 *)D_DMARAMLOC_CNT_U32;					/* Cause parity error */

	if (0U == (ESMREGS->ESMSR1 & 0x8))		/* Check if ESM group1 channel 3 is flagged */
	{
		/* DMA RAM parity error was not flagged to ESM. */
		ResetCause_Cnt_Enum = DMAPARESMFAILED;
		DMACTRLREG->DMAPAR = 0x01000000;			/* clear DMA parity error flag in DMA */
		*(volatile uint32 *)D_DMARAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
		DiagFailed();
	}
	else
	{
		DMACTRLREG->DMAPAR = 0x01000000;			/* clear DMA parity error flag in DMA */
		ESMREGS->ESMSR1 = 0x8;			/* clear ESM group1 channel 3 flag */
		*(volatile uint32 *)D_DMARAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
	}
}
#endif

#if (N2HET1_PARITY_ENABLE)
static void nhet1ParityCheck(void)
{
	volatile uint32 nhetread_Cnt_T_u32;

	NHET0->NHETPCR = 0x0000010A;			/* Set TEST mode and enable parity checking */
	(*(volatile uint32 *)D_NHET1RAMPARLOC_CNT_U32) ^= 0x1;					/* flip parity bit */
	NHET0->NHETPCR = 0x0000000A;			/* Disable TEST mode */

	nhetread_Cnt_T_u32 = *(volatile uint32 *)D_NHET1RAMLOC_CNT_U32;					/* read to cause parity error */

	if (0U == (ESMREGS->ESMSR1 & 0x80))		/* check if ESM group1 channel 7 is flagged */
	{
		/* NHET1 RAM parity error was not flagged to ESM. */
		ResetCause_Cnt_Enum = N2HET1PARESMFAILED;
		*(volatile uint32 *)D_NHET1RAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
		DiagFailed();
	}
	else
	{
		ESMREGS->ESMSR1 = 0x80;			/* clear ESM group1 channel 7 flag */
		*(volatile uint32 *)D_NHET1RAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
	}
}
#endif

#if (N2HET1TU_PARITY_ENABLE)
static void htu1ParityCheck(void)
{
	volatile uint32 hturead_Cnt_T_u32;

	htuREG1->PCR = 0x0000010A;				/* Enable parity and TEST mode */
	(*(volatile uint32 *)D_HTU1RAMPARLOC_CNT_U32) ^= 0x1;						/* flip parity bit */
	htuREG1->PCR = 0x0000000A;				/* Disable parity RAM test mode */

	hturead_Cnt_T_u32 = *(volatile uint32 *)D_HTU1RAMLOC_CNT_U32;					/* read to cause parity error */

	if (0U == (ESMREGS->ESMSR1 & 0x100))		/* check if ESM group1 channel 8 is flagged */
	{
		/* HTU1 RAM parity error was not flagged to ESM. */
		ResetCause_Cnt_Enum = N2HET1TUPARESMFAILED;
		htuREG1->PAR = 0x00010000;			/* Clear HTU parity error flag */
		*(volatile uint32 *)D_HTU1RAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
		DiagFailed();
	}
	else
	{
		htuREG1->PAR = 0x00010000;			/* Clear HTU parity error flag */
		ESMREGS->ESMSR1 = 0x100;
		*(volatile uint32 *)D_HTU1RAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
	}

}
#endif

#if (N2HET2_PARITY_ENABLE)
static void nhet2parityCheck(void)
{
	volatile uint32 nhetread_Cnt_T_u32;

	NHET1->NHETPCR = 0x0000010A;			/* Set TEST mode and enable parity checking */
	(*(volatile uint32 *)D_NHET2RAMPARLOC_CNT_U32) ^= 0x1;					/* flip parity bit */
	NHET1->NHETPCR = 0x0000000A;			/* Disable TEST mode */

	nhetread_Cnt_T_u32 = *(volatile uint32 *)D_NHET2RAMLOC_CNT_U32;					/* read to cause parity error */

	if ((0U == (ESMREGS->ESMSR1 & 0x80)) && (0U == (ESMREGS->ESTATUS4[0] & 0x4)))		/* check if ESM group1 channel 7 or 34 is flagged */
	{
		/* NHET2 RAM parity error was not flagged to ESM. */
		ResetCause_Cnt_Enum = N2HET2PARESMFAILED;
		*(volatile uint32 *)D_NHET2RAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
		DiagFailed();
	}
	else
	{
		ESMREGS->ESMSR1 = 0x80;			/* clear ESM group1 channel 7 flag */
		ESMREGS->ESTATUS4[0] = 0x4;			/* clear ESM group1 channel 34 flag */
		*(volatile uint32 *)D_NHET2RAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
	}
}
#endif

#if (N2HET2TU_PARITY_ENABLE)
static void htu2ParityCheck(void)
{
	volatile uint32 hturead_Cnt_T_u32;

	htuREG2->PCR = 0x0000010A;				/* Enable parity and TEST mode */
	(*(volatile uint32 *)D_HTU2RAMPARLOC_CNT_U32) ^= 0x1;						/* flip parity bit */
	htuREG2->PCR = 0x0000000A;				/* Disable parity RAM test mode */

	hturead_Cnt_T_u32 = *(volatile uint32 *)D_HTU2RAMLOC_CNT_U32;					/* read to cause parity error */

	if (0U == (ESMREGS->ESMSR1 & 0x100))		/* check if ESM group1 channel 8 is flagged */
	{
		/* HTU2 RAM parity error was not flagged to ESM. */
		ResetCause_Cnt_Enum = N2HET2TUPARESMFAILED;
		htuREG2->PAR = 0x00010000;			/* Clear HTU parity error flag */
		*(volatile uint32 *)D_HTU2RAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
		DiagFailed();
	}
	else
	{
		htuREG2->PAR = 0x00010000;			/* Clear HTU parity error flag */
		ESMREGS->ESMSR1 = 0x100;
		*(volatile uint32 *)D_HTU2RAMLOC_CNT_U32 = 0U;		/* Nexteer Added: Correct parity error */
	}

}
#endif

#if (MIBADC1_PARITY_ENABLE)
static void adc1ParityCheck(void)
{
	volatile uint32 adcramread_Cnt_T_u32;

	adcREG1->PARCR = 0x0000010A;					/* Set the TEST bit in the PARCR and enable parity checking */
	(*(volatile uint32 *)D_ADC1RAMPARLOC_CNT_U32) ^= 0x1;	/* flip parity bit */
	adcREG1->PARCR = 0x0000000A;					/* clear the TEST bit */

	adcramread_Cnt_T_u32 = *(volatile uint32 *)D_ADC1RAMLOC_CNT_U32;					/* This read is expected to trigger a parity error */

	adcREG1->PARCR = 0x0000010A;					/* Set the TEST bit in the PARCR and enable parity checking */
	(*(volatile uint32 *)D_ADC1RAMPARLOC_CNT_U32) ^= 0x1;	/* flip parity bit to correct error */
	adcREG1->PARCR = 0x0000000A;					/* clear the TEST bit */

	if (0U == (ESMREGS->ESMSR1 & 0x80000))	/* Check for ESM group1 channel 19 to be flagged */
	{
		/* no ADC1 RAM parity error was flagged to ESM */
		ResetCause_Cnt_Enum = MIBADC1PARESMFAILED;
		DiagFailed();
	}
	else
	{
		ESMREGS->ESMSR1 = 0x80000;		/* clear ADC1 RAM parity error flag */
	}
}
#endif

#if (MIBADC2_PARITY_ENABLE)
static void adc2ParityCheck(void)
{
	volatile uint32 adcramread_Cnt_T_u32;

	adcREG2->PARCR = 0x0000010A;					/* Set the TEST bit in the PARCR and enable parity checking */
	(*(volatile uint32 *)D_ADC2RAMPARLOC_CNT_U32) ^= 0x1;	/* flip parity bit */
	adcREG2->PARCR = 0x0000000A;					/* clear the TEST bit */

	adcramread_Cnt_T_u32 = *(volatile uint32 *)D_ADC2RAMLOC_CNT_U32;					/* This read is expected to trigger a parity error */

	adcREG2->PARCR = 0x0000010A;					/* Set the TEST bit in the PARCR and enable parity checking */
	(*(volatile uint32 *)D_ADC2RAMPARLOC_CNT_U32) ^= 0x1;	/* flip parity bit to correct error */
	adcREG2->PARCR = 0x0000000A;					/* clear the TEST bit */

	if (0U == (ESMREGS->ESMSR1 & 0x2))		/* Check for ESM group1 channel 1 to be flagged */
	{
		/* no ADC2 RAM parity error was flagged to ESM */
		ResetCause_Cnt_Enum = MIBADC2PARESMFAILED;
		DiagFailed();
	}
	else
	{
		ESMREGS->ESMSR1 = 0x2;			/* clear ADC2 RAM parity error flag */
	}
}
#endif

#if (DCAN1_PARITY_ENABLE)
static void dcan1ParityCheck(void)
{
	volatile uint32 dcanread_Cnt_T_u32;

	DCAN1REG->CTL = 0x00001481;				/* Disable parity, init mode, TEST mode */
	DCAN1REG->TEST = 0x00000200;			/* Enable RAM Direct Access mode */

	(*(volatile uint32 *)D_DCAN1RAMPARLOC_CNT_U32) ^= 0x00001000;				/* flip the parity bit */

	DCAN1REG->CTL = 0x00002880;				/* Enable parity, disable init, still TEST mode */

	dcanread_Cnt_T_u32 = *(volatile uint32 *)D_DCAN1RAMLOC_CNT_U32;					/* Read location with parity error */
	*(volatile uint32 *)D_DCAN1RAMLOC_CNT_U32 = dcanread_Cnt_T_u32;		/* Nexteer Added: Correct parity error */

	if (0U == (ESMREGS->ESMSR1 & 0x00200000))	/* check if ESM group1 channel 21 is flagged */
	{
		/* No DCAN1 RAM parity error was flagged to ESM */
		ResetCause_Cnt_Enum = DCAN1PARESMFAILED;
		DCAN1REG->ES = DCAN1REG->ES;		/* LWW Edit to clear parity error status register */
		DCAN1REG->CTL = 0x00002800;			/* disable TEST mode */
		DiagFailed();
	}
	else
	{
		DCAN1REG->ES = DCAN1REG->ES;		/* LWW Edit to clear parity error status register */
		ESMREGS->ESMSR1 = 0x00200000;	/* clear ESM group1 channel 21 flag */
		DCAN1REG->CTL = 0x00002800;			/* disable TEST mode */
	}

}
#endif

#if (DCAN2_PARITY_ENABLE)
static void dcan2ParityCheck(void)
{
	volatile uint32 dcanread_Cnt_T_u32;

	DCAN2REG->CTL = 0x00001481;				/* Disable parity, init mode, TEST mode */
	DCAN2REG->TEST = 0x00000200;			/* Enable RAM Direct Access mode */

	(*(volatile uint32 *)D_DCAN2RAMPARLOC_CNT_U32) ^= 0x00001000;				/* flip the parity bit */

	DCAN2REG->CTL = 0x00002880;				/* Enable parity, disable init, still TEST mode */

	dcanread_Cnt_T_u32 = *(volatile uint32 *)D_DCAN2RAMLOC_CNT_U32;					/* Read location with parity error */
	*(volatile uint32 *)D_DCAN2RAMLOC_CNT_U32 = dcanread_Cnt_T_u32;		/* Nexteer Added: Correct parity error */

	if (0U == (ESMREGS->ESMSR1 & 0x00800000))	/* check if ESM group1 channel 23 is flagged */
	{
		/* No DCAN2 RAM parity error was flagged to ESM */
		ResetCause_Cnt_Enum = DCAN2PARESMFAILED;
		DCAN2REG->ES = DCAN2REG->ES;		/* LWW Edit to clear parity error status register */
		DCAN2REG->CTL = 0x00002800;			/* disable TEST mode */
		DiagFailed();
	}
	else
	{
		DCAN2REG->ES = DCAN2REG->ES;		/* LWW Edit to clear parity error status register */
		ESMREGS->ESMSR1 = 0x00800000;	/* clear ESM group1 channel 23 flag */
		DCAN2REG->CTL = 0x00002800;			/* disable TEST mode */
	}

}
#endif

#if (DCAN3_PARITY_ENABLE)
static void dcan3ParityCheck(void)
{
	volatile uint32 dcanread_Cnt_T_u32;

	DCAN3REG->CTL = 0x00001481;				/* Disable parity, init mode, TEST mode */
	DCAN3REG->TEST = 0x00000200;			/* Enable RAM Direct Access mode */

	(*(volatile uint32 *)D_DCAN3RAMPARLOC_CNT_U32) ^= 0x00001000;				/* flip the parity bit */

	DCAN3REG->CTL = 0x00002880;				/* Enable parity, disable init, still TEST mode */

	dcanread_Cnt_T_u32 = *(volatile uint32 *)D_DCAN3RAMLOC_CNT_U32;					/* Read location with parity error */
	*(volatile uint32 *)D_DCAN3RAMLOC_CNT_U32 = dcanread_Cnt_T_u32;		/* Nexteer Added: Correct parity error */

	if (0U == (ESMREGS->ESMSR1 & 0x00400000))	/* check if ESM group1 channel 22 is flagged */
	{
		/* No DCAN3 RAM parity error was flagged to ESM */
		ResetCause_Cnt_Enum = DCAN3PARESMFAILED;
		DCAN3REG->ES = DCAN3REG->ES;		/* LWW Edit to clear parity error status register */
		DCAN3REG->CTL = 0x00002800;			/* disable TEST mode */
		DiagFailed();
	}
	else
	{
		DCAN3REG->ES = DCAN3REG->ES;		/* LWW Edit to clear parity error status register */
		ESMREGS->ESMSR1 = 0x00400000;	/* clear ESM group1 channel 22 flag */
		DCAN3REG->CTL = 0x00002800;			/* disable TEST mode... LWW Edit to enable init mode */
	}
}
#endif

#if (MIBSPI1_PARITY_ENABLE)
static void mibspi1ParityCheck(void)
{
	volatile uint32 spiread_Cnt_T_u32;

	mibspiREG1->MIBSPIE = 0x1;				/* enable multi-buffered mode */

	mibspiREG1->EDEN = 0xA;					/* enable parity error detection */
	mibspiREG1->PTESTEN = 1;				/* enable parity test mode */
	(*(volatile uint32 *)D_SPI1RAMPARLOC_CNT_U32) ^= 0x1;					/* flip bit 0 of the parity location */

	mibspiREG1->PTESTEN = 0;				/* disable parity test mode */

	spiread_Cnt_T_u32 = *(volatile uint32 *)D_SPI1RAMLOC_CNT_U32;					/* read from MibSPI1 RAM to cause parity error */

	if (0U == (ESMREGS->ESMSR1 & 0x20000))	/* check if ESM group1 channel 17 is flagged */
	{
		/* No MibSPI1 RAM parity error was flagged to ESM. */
		ResetCause_Cnt_Enum = MIBSPI1PARESMFAILED;
		mibspiREG1->UERRSTAT = 0x3;			/* clear parity error flags */
		mibspiREG1->PTESTEN = 1;							/* enable parity test mode */
		(*(volatile uint32 *)D_SPI1RAMPARLOC_CNT_U32) ^= 0x1;		/* flip bit 0 of the parity location (correct error) */
		mibspiREG1->PTESTEN = 0;							/* disable parity test mode */
		DiagFailed();
	}
	else
	{
		mibspiREG1->UERRSTAT = 0x3;			/* clear parity error flags */
		ESMREGS->ESMSR1 = 0x20000;		/* clear ESM group1 channel 17 flag */
		mibspiREG1->PTESTEN = 1;							/* enable parity test mode */
		(*(volatile uint32 *)D_SPI1RAMPARLOC_CNT_U32) ^= 0x1;		/* flip bit 0 of the parity location (correct error) */
		mibspiREG1->PTESTEN = 0;							/* disable parity test mode */
	}
}
#endif

#if (MIBSPI3_PARITY_ENABLE)
static void mibspi3parityCheck(void)
{
	volatile uint32 spiread_Cnt_T_u32;

	mibspiREG3->MIBSPIE = 0x1;				/* enable multi-buffered mode */

	mibspiREG3->EDEN = 0xA;					/* enable parity error detection */
	mibspiREG3->PTESTEN = 1;				/* enable parity test mode */
	(*(volatile uint32 *)D_SPI3RAMPARLOC_CNT_U32) ^= 0x1;					/* flip bit 0 of the parity location */

	mibspiREG3->PTESTEN = 0;				/* disable parity test mode */

	spiread_Cnt_T_u32 = *(volatile uint32 *)D_SPI3RAMLOC_CNT_U32;					/* read from MibSPI3 RAM to cause parity error */

	if (0U == (ESMREGS->ESMSR1 & 0x40000))	/* check if ESM group1 channel 18 is flagged */
	{
		/* No MibSPI3 RAM parity error was flagged to ESM. */
		ResetCause_Cnt_Enum = MIBSPI3PARESMFAILED;
		mibspiREG3->UERRSTAT = 0x3;			/* clear parity error flags */
		mibspiREG3->PTESTEN = 1;							/* enable parity test mode */
		(*(volatile uint32 *)D_SPI3RAMPARLOC_CNT_U32) ^= 0x1;		/* flip bit 0 of the parity location (correct error) */
		mibspiREG3->PTESTEN = 0;							/* disable parity test mode */
		DiagFailed();
	}
	else
	{
		mibspiREG3->UERRSTAT = 0x3;			/* clear parity error flags */
		ESMREGS->ESMSR1 = 0x40000;		/* clear ESM group1 channel 18 flag */
		mibspiREG3->PTESTEN = 1;							/* enable parity test mode */
		(*(volatile uint32 *)D_SPI3RAMPARLOC_CNT_U32) ^= 0x1;		/* flip bit 0 of the parity location (correct error) */
		mibspiREG3->PTESTEN = 0;							/* disable parity test mode */
	}
}
#endif

#if (MIBSPI5_PARITY_ENABLE)
static void mibspi5ParityCheck(void)
{
	volatile uint32 spiread_Cnt_T_u32;

	mibspiREG5->MIBSPIE = 0x1;				/* enable multi-buffered mode */

	mibspiREG5->EDEN = 0xA;					/* enable parity error detection */
	mibspiREG5->PTESTEN = 1;				/* enable parity test mode */
	(*(volatile uint32 *)D_SPI5RAMPARLOC_CNT_U32) ^= 0x1;					/* flip bit 0 of the parity location */

	mibspiREG5->PTESTEN = 0;				/* disable parity test mode */

	spiread_Cnt_T_u32 = *(volatile uint32 *)D_SPI5RAMLOC_CNT_U32;					/* read from MibSPI5 RAM to cause parity error */

	if (0U == (ESMREGS->ESMSR1 & 0x01000000))	/* check if ESM group1 channel 24 is flagged */
	{
		/* No MibSPI5 RAM parity error was flagged to ESM. */
		ResetCause_Cnt_Enum = MIBSPI5PARESMFAILED;
		mibspiREG5->UERRSTAT = 0x3;			/* clear parity error flags */
		mibspiREG5->PTESTEN = 1;							/* enable parity test mode */
		(*(volatile uint32 *)D_SPI5RAMPARLOC_CNT_U32) ^= 0x1;		/* flip bit 0 of the parity location (correct error) */
		mibspiREG5->PTESTEN = 0;							/* disable parity test mode */
		DiagFailed();
	}
	else
	{
		mibspiREG5->UERRSTAT = 0x3;			/* clear parity error flags */
		ESMREGS->ESMSR1 = 0x01000000;		/* clear ESM group1 channel 24 flag */
		mibspiREG5->PTESTEN = 1;							/* enable parity test mode */
		(*(volatile uint32 *)D_SPI5RAMPARLOC_CNT_U32) ^= 0x1;		/* flip bit 0 of the parity location (correct error) */
		mibspiREG5->PTESTEN = 0;							/* disable parity test mode */
	}
}
#endif

#if (DMA_MPU_ENABLE)

/******************************************************************************
  * Name:        WaitForDmaTransfer
  * Description: Implements a delay of at least 0.25 uSec for DMA transfer
  *              as needed by DmaMpuCheck()
  * Inputs:      NONE     
  * Outputs:     NONE 
  * Usage Notes: NONE 
  ****************************************************************************/
static void WaitForDmaTransfer(void)
{
	uint64 Sum_Uls_T_u64;
	uint16 LoopCount_Cnt_T_u16;

	/* the wait needs to be at least 0.25 uSec for the 4-byte DMA transfers */
	/* sum an unused volatile variable and then return the sum */
	/* so the compiler won't optimize out the loop */
	/* rationale: 0.25 uSec is 40 TMS570 clock cycles (at 160MHz) */
	/* since the loop takes more than one clock cycles to execute */
	/* a value of 40 is guaranteed not to stop the loop too soon */
	
	Sum_Uls_T_u64 = 0U;
	for (LoopCount_Cnt_T_u16 = 0U; LoopCount_Cnt_T_u16 < D_DMAWAITLOOPCOUNT_CNT_U16; LoopCount_Cnt_T_u16++)
	{
		/* don't care about possible overflow since value is a "don't care" */
		Sum_Uls_T_u64 += DmaMPUTest2_Uls_M_str.DummyVarForAlignment_Cnt_u64;
	} 
	DmaMPUTest2_Uls_M_str.DummyVarForAlignment_Cnt_u64 = Sum_Uls_T_u64;
}


/******************************************************************************
 * Name:        DmaMpuCheck
 * Description: Check DMA memory protection error detection and signaling mechanism
 * Inputs:      NONE     
 * Outputs:     ResetCause_Cnt_Enum is set if DMA MPU test fails 
 * Usage Notes: If DMA MPU test fails, this function calls DiagFailed() and does not return 
 ****************************************************************************/
static void DmaMpuCheck(void)
{
	uint32 TestFailureFlag_Cnt_T_u32 = 0UL;
	
	/* Set Up Memory Protection */
	DMACTRLREG->DMAMPCTRL = (0ul)
						  | (1ul)			/* Region 0 enable:		enabled */
						  | (0ul << 1)		/* Region 0 access:		read/write */
						  | (1ul << 3)		/* Region 0 interrupt:	enabled (enables MPU violation setting ESM interrupt) */

						  | (1ul << 8)		/* Region 1 enable:		enabled */
						  | (3ul << 9)		/* Region 1 access:		no access */
						  | (1ul << 11);	/* Region 1 interrupt:	enabled (enables MPU violation setting ESM interrupt) */

	
	DMACTRLREG->DMAMPR0S = (uint32)(&DmaMPUTest1_Uls_M_str);			/* Region 0 - DmaMPUTest1_Uls_M_str */
	DMACTRLREG->DMAMPR0E = ((uint32)(&DmaMPUTest1_Uls_M_str) + sizeof(DmaMPUTest1_Uls_M_str)) - 1U;

	DMACTRLREG->DMAMPR1S = 0x00000000ul;			/* Region 1 - full address space */
	DMACTRLREG->DMAMPR1E = 0xFFFFFFFFul;
	
	
	/* Enable Parity */
#if (DMA_PARITY_ENABLE == STD_ON)
	DMACTRLREG->DMAPCR = 0x0Aul;	/* enable parity */
#endif

	/* Disable Hardware Request Lines */
	DMACTRLREG->HWCHENAS = (0ul); /* no hardware channel requests enabled */	
	
	/* Enable DMA */
	DMACTRLREG->GCTRL = (3ul << 8)		/* Debug mode:	immediate halt */
					  | (1ul << 16);	/* DMA enable:	enabled */
					  
	/* set up channel 13 control packet for successful transfer  */				  
					  
	DMACTRLPKT13->ISADDR = (uint32)&(DmaMPUTest1_Uls_M_str.TestVar1_Cnt_u32);
	DMACTRLPKT13->IDADDR = (uint32)&(DmaMPUTest1_Uls_M_str.TestVar2_Cnt_u32);
	
	DMACTRLPKT13->ITCOUNT = 2ul				/* Element count:	configurable */
						  | (1ul << 16);	/* Frame count:		1 */
	
	DMACTRLPKT13->CHCTRL = (0ul)		/* Auto-init:				not enabled */
						 | (3ul << 1)	/* Addressing mode (write):	indexed */
						 | (3ul << 3)	/* Addressing mode (read):	indexed */
						 | (1ul << 8)	/* Transfer type:			block transfer */
						 | (1ul << 12)	/* Write element size:		16 bit */
						 | (1ul << 14)	/* Read element size:		16 bit */
						 | (0ul << 16);	/* Next channel:			none */
		/* transfer will be triggered by software request; SWCHENAS bit automatically cleared 
		   after one transfer if TTYPE is block transfer and auto-init is not enabled */
	
	DMACTRLPKT13->EIOFF = (2ul)			/* Source element offset:		2 bytes */
						| (2ul << 16);	/* Destination element offset:	2 bytes */
	
	DMACTRLPKT13->FIOFF = (0ul)			/* Source frame offset:			0 bytes */
						| (0ul << 16);	/* Destination frame offset:	0 bytes */
	
	DMACTRLREG->DREQASI3_CH13ASI = 13u;	/* Trigger channel 13 on request line 13 */
	
	DMACTRLREG->PAR1 |= (4ul << 8);		/* Channel 13:	Port B */
	
	DMACTRLREG->CHPRIOS |= (1ul << 13);	/* Channel 13:	high priority */

					  
	/* set up channel 14 control packet for unsuccessful transfer - source not accessible */				  
					  
	DMACTRLPKT14->ISADDR = (uint32)&(DmaMPUTest2_Uls_M_str.TestVar1_Cnt_u32);
	DMACTRLPKT14->IDADDR = (uint32)&(DmaMPUTest1_Uls_M_str.TestVar2_Cnt_u32);
	
	DMACTRLPKT14->ITCOUNT = 2ul				/* Element count:	configurable */
						  | (1ul << 16);	/* Frame count:		1 */
	
	DMACTRLPKT14->CHCTRL = (0ul)		/* Auto-init:				not enabled */
						 | (3ul << 1)	/* Addressing mode (write):	indexed */
						 | (3ul << 3)	/* Addressing mode (read):	indexed */
						 | (1ul << 8)	/* Transfer type:			block transfer */
						 | (1ul << 12)	/* Write element size:		16 bit */
						 | (1ul << 14)	/* Read element size:		16 bit */
						 | (0ul << 16);	/* Next channel:			none */
		/* transfer will be triggered by software request; SWCHENAS bit automatically cleared 
		   after one transfer if TTYPE is block transfer and auto-init is not enabled */
	
	DMACTRLPKT14->EIOFF = (2ul)			/* Source element offset:		2 bytes */
						| (2ul << 16);	/* Destination element offset:	2 bytes */
	
	DMACTRLPKT14->FIOFF = (0ul)			/* Source frame offset:			0 bytes */
						| (0ul << 16);	/* Destination frame offset:	0 bytes */
	
	DMACTRLREG->DREQASI3_CH14ASI = 14u;	/* Trigger channel 14 on request line 14 */
	
	DMACTRLREG->PAR1 |= (4ul << 4);		/* Channel 14:	Port B */
	
	DMACTRLREG->CHPRIOS |= (1ul << 14);	/* Channel 14:	high priority */

					  
	/* set up channel 15 control packet for unsuccessful transfer -- destination not accessible */				  
					  
	DMACTRLPKT15->ISADDR = (uint32)&(DmaMPUTest1_Uls_M_str.TestVar1_Cnt_u32);
	DMACTRLPKT15->IDADDR = (uint32)&(DmaMPUTest2_Uls_M_str.TestVar2_Cnt_u32);
	
	DMACTRLPKT15->ITCOUNT = 2ul				/* Element count:	configurable */
						  | (1ul << 16);	/* Frame count:		1 */
	
	DMACTRLPKT15->CHCTRL = (0ul)		/* Auto-init:				not enabled */
						 | (3ul << 1)	/* Addressing mode (write):	indexed */
						 | (3ul << 3)	/* Addressing mode (read):	indexed */
						 | (1ul << 8)	/* Transfer type:			block transfer */
						 | (1ul << 12)	/* Write element size:		16 bit */
						 | (1ul << 14)	/* Read element size:		16 bit */
						 | (0ul << 16);	/* Next channel:			none */
		/* transfer will be triggered by software request; SWCHENAS bit automatically cleared 
		   after one transfer if TTYPE is block transfer and auto-init is not enabled */
	
	DMACTRLPKT15->EIOFF = (2ul)			/* Source element offset:		2 bytes */
						| (2ul << 16);	/* Destination element offset:	2 bytes */
	
	DMACTRLPKT15->FIOFF = (0ul)			/* Source frame offset:			0 bytes */
						| (0ul << 16);	/* Destination frame offset:	0 bytes */
	
	DMACTRLREG->DREQASI3_CH15ASI = 15u;	/* Trigger channel 15 on request line 15 */
	
	DMACTRLREG->PAR1 |= (4ul << 0);		/* Channel 15:	Port B */
	
	DMACTRLREG->CHPRIOS |= (1ul << 15);	/* Channel 15:	high priority */

	/* write known data to test variables */
	DmaMPUTest1_Uls_M_str.TestVar1_Cnt_u32 = D_DMAMPUTESTDATA1_CNT_U32;
	DmaMPUTest1_Uls_M_str.TestVar2_Cnt_u32 = D_DMAMPUTESTDATA2_CNT_U32;
	DmaMPUTest2_Uls_M_str.TestVar1_Cnt_u32 = D_DMAMPUTESTDATA3_CNT_U32;
	DmaMPUTest2_Uls_M_str.TestVar2_Cnt_u32 = D_DMAMPUTESTDATA4_CNT_U32;

	/* test successful transfer */
	DMACTRLREG->SWCHENAS = (1ul << 13); /* request line 13 */
	WaitForDmaTransfer();
	if ((0U != (ESMREGS->ESMSR1 & 0x00000004UL)) ||
		(DmaMPUTest1_Uls_M_str.TestVar2_Cnt_u32 != D_DMAMPUTESTDATA1_CNT_U32))
	/* test failure if DMA MPU violation in ESM or data did not transfer */
	{
		TestFailureFlag_Cnt_T_u32 = DMAMPUSTARTUPFAIL;
	}
	if (TestFailureFlag_Cnt_T_u32 == 0UL)
	{		
		/* test unsuccessful transfer -- source inaccessible */
		DMACTRLREG->SWCHENAS = (1ul << 14); /* request line 14 */
		WaitForDmaTransfer();
		if ((0U == (ESMREGS->ESMSR1 & 0x00000004UL)) ||
			(DmaMPUTest1_Uls_M_str.TestVar2_Cnt_u32 != D_DMAMPUTESTDATA1_CNT_U32))
		/* test failure if no DMA MPU violation in ESM or data did transfer */		
		{
			TestFailureFlag_Cnt_T_u32 = DMAMPUSTARTUPFAIL;
		}
		else
		/* else clear ESM bit and DMA MPU status bit for next test */
		{
			ESMREGS->ESMSR1 = 0x00000004UL;
			DMACTRLREG->DMAMPST = 0x00000100UL; /* region 1 violation bit */
		}
	}
	if (TestFailureFlag_Cnt_T_u32 == 0UL)
	{		
		/* test unsuccessful transfer -- destination inaccessible */
		DMACTRLREG->SWCHENAS = (1ul << 15); /* request line 15 */
		WaitForDmaTransfer();
		if ((0U == (ESMREGS->ESMSR1 & 0x00000004UL)) ||
			(DmaMPUTest2_Uls_M_str.TestVar2_Cnt_u32 != D_DMAMPUTESTDATA4_CNT_U32))
		/* test failure if no DMA MPU violation in ESM or data did transfer */		
		{
			TestFailureFlag_Cnt_T_u32 = DMAMPUSTARTUPFAIL;
		}
		else
		/* else clear ESM bit and DMA MPU status bit */
		{
			ESMREGS->ESMSR1 = 0x00000004UL;
			DMACTRLREG->DMAMPST = 0x00000100UL; /* region 1 violation bit */
		}
	}
	
	/* end-of-test housekeeping */
	if (0U != (ESMREGS->ESMSR1 & 0x00000004UL))
	{
		ESMREGS->ESMSR1 = 0x00000004UL; /* clear ESM bit if needed  */
	}
	if (0U != (DMACTRLREG->DMAMPST & 0x00000100UL))
	{
		DMACTRLREG->DMAMPST = 0x00000100UL; /* clear region 1 DMA MPU violation bit if needed  */
	}
	DMACTRLREG->GCTRL |= 0x01UL;  /* reset DMA peripheral */
	
	if (TestFailureFlag_Cnt_T_u32 != 0UL)
	{
		ResetCause_Cnt_Enum = DMAMPUSTARTUPFAIL;
		DiagFailed();
	}
	
}
#endif

#if ((N2HET1TU_MPU_ENABLE) || (N2HET2TU_MPU_ENABLE))
/******************************************************************************
  * Name:        WaitForHtuTransfer
  * Description: Implements a delay of at least 1.5 uSec for HTU transfer
  *              as needed by Nhet1HTUMPUCheck and Nhet2HTUMPUCheck
  * Inputs:      FRCTR_ptr pointer to the running counter in the NHET program     
  * Outputs:     NONE 
  * Usage Notes: NONE 
  ****************************************************************************/
static void WaitForHtuTransfer(const volatile uint32* const FRCTR_ptr)
{
	uint32 StartValue_Cnt_T_u32;
	uint32 Elapsed_Cnt_T_u32;
	uint16 LoopCount_Cnt_T_u16;

	/* the wait needs to be at least 3 Nhet LR loops of 0.5 uSec each */
	/* wait for the counter in the Nhet program to advance by 3 */
	/* with a loop count limit of 240 in case the Nhet is not running properly */
	/* rationale: 1.5 uSec is 240 TMS570 clock cycles (at 160MHz) */
	/* since the do while loop takes more than one clock cycles to execute */
	/* a value of 240 is guaranteed not to stop the loop too soon */
	
	StartValue_Cnt_T_u32 = *FRCTR_ptr;
	LoopCount_Cnt_T_u16 = 0U;
	do
	{
		/* allow overflow if counter rolls over; results will be correct */
		/* since counter would take approx. 16.7 seconds to wrap all the way around */
		/* (25 bits counting once per 0.5 uSec) */
		Elapsed_Cnt_T_u32 = *FRCTR_ptr - StartValue_Cnt_T_u32;
		LoopCount_Cnt_T_u16++;
	} while ((Elapsed_Cnt_T_u32 < D_HTUTESTWAIT_CNT_U32) && (LoopCount_Cnt_T_u16 < D_HTUWAITTIMEOUT_CNT_U16));
}
#endif

#if (N2HET1TU_MPU_ENABLE)
/*****************************************************************************
 * Name:        Nhet1HTUMPUCheck
 * Description: NHET1 - startup check of HTU1 MPU error detection and signaling mechanism
 * Inputs:      None
 * Outputs:     ResetCause_Cnt_Enum is set if HTU1 MPU test fails
 * Usage Notes: If HTU1 MPU test fails, this function calls DiagFailed() and does not return 
 *****************************************************************************/
static void Nhet1HTUMPUCheck(void)
{

volatile HETPROGRAM7_UN* const HetProgAtStartup_ptr = (volatile HETPROGRAM7_UN*)D_BASEADDNHET1RAM_CNT_U32;

uint32 TestFailureFlag_Cnt_T_u32 = 0UL;
uint16 index_Cnt_T_u16;

	/* Start initialization of N2HET1 Peripheral (N2HET1 registers named NHET0; N2HET2 registers named NHET1) */
	NHET0->NHETGCR =
		(1UL << 24U) |					/* 0: Enable output buffers */
		(1UL << 18U) |					/* 0: When NHET is running, program fields are read-only */
		(1UL << 17U) |					/* 1: NHET doesn't stop when a software breakpoint is encountered.*/
		(1UL << 16U) |					/* 1: NHET is master */
		(0UL <<  0U);					/* 0: Stop NHET */
	
	
	/* copy the HET startup prog */
	(void) memcpy((void *) HetProgAtStartup_ptr, (const void *) HET_INIT7_PST, sizeof(HET_INIT7_PST)); /* PRQA S 312 */
	/* MISRA-C:2004 Rule 11.5: This deviation is required for memcpy call; volatile qualification not needed inside memcpy function */
	
	NHET0->NHETPFR =			/* Timer Prescale */
		(4UL << 8) |			/* 4 -> lr=16 */
		(0UL << 0);				/* 0 -> hr=1:  ts = 16*1 = 16 */
		
	NHET0->NHETSFENA =			/* Enable suppression Filter */
		(1UL << 30) |				/* Enable on ch 30 */
		(1UL << 12);				/* Enable on ch 12 */
	
	NHET0->NHETREQENS =			/* Enable HTU Request */
		(1UL << 1) |			/* Enable Request 1 */
		(1UL << 2) |  			/* Enable Request 2 */
		(1UL << 3) |            /* Enable Request 3 */
	    (1UL << 4);				/* Enable Request 4 */

	NHET0->NHETREQDS =			/* HTU Request Destination */
		(0UL << 1) |			/* HTU Request 1 */
		(0UL << 2) |  			/* HTU Request 2 */
		(0UL << 3) |  			/* HTU Request 3 */
		(0UL << 4);  			/* HTU Request 4 */
			
	/* End initialization of NHET 0 Peripheral */
	
	/* Startup Code HTU initialization   */
	StartupHTU1Init();

	/* Enable NHET */
	NHET0->NHETGCR |= 0x01U;			

	/* begin HTU MPU check */
	
	for (index_Cnt_T_u16 = 0u; index_Cnt_T_u16 < 4u; index_Cnt_T_u16++)
	{
		HTU1MPUTest_Cnt_M_u32[index_Cnt_T_u16] = D_HTUTESTDATA_CNT_U32;
	}
	
	/* test 1 - successful transfer from NHET RAM to main memory */
	HET_Transst_7.memory.data_word = D_HTUDATA1_CNT_U32; /* trigger transfer 1 */
	WaitForHtuTransfer (&(HET_FRCTR_7.memory.data_word));
	if ((HTU1MPUTest_Cnt_M_u32[1] != D_HTUDATA1_CNT_U32) || 
		(0U != (ESMREGS->ESMSR1 & 0x00000200UL)))
	/* test failure if data did not transfer or HTU MPU violation in ESM */
	{
		TestFailureFlag_Cnt_T_u32 = HTU1MPUSTARTUPFAIL;
	}
	if (TestFailureFlag_Cnt_T_u32 == 0UL)
	{
		/* test 2 - successful transfer from main memory to NHET RAM */
		HET_Transst_7.memory.data_word = D_HTUDATA2_CNT_U32; /* trigger transfer 2 */
		WaitForHtuTransfer (&(HET_FRCTR_7.memory.data_word));
		if ((HET_mvstrt2_7.memory.data_word != D_HTUTESTDATA_CNT_U32) ||
			(0U != (ESMREGS->ESMSR1 & 0x00000200UL)))
		/* test failure if data did not transfer or HTU MPU violation in ESM */
		{
			TestFailureFlag_Cnt_T_u32 = HTU1MPUSTARTUPFAIL;
		}
	}
	if (TestFailureFlag_Cnt_T_u32 == 0UL)
	{
		/* test 3 - unsuccessful transfer from NHET RAM to main memory */
		HET_Transst_7.memory.data_word = D_HTUDATA3_CNT_U32; /* trigger transfer 3 */
		WaitForHtuTransfer (&(HET_FRCTR_7.memory.data_word));
		if ((HTU1MPUTest_Cnt_M_u32[3] != D_HTUTESTDATA_CNT_U32) || 
			(0U == (ESMREGS->ESMSR1 & 0x00000200UL)))
		/* test failure if data did transfer (HTUMPUTest_Cnt_M_u32[3] changed from initial pattern) 
		   or no HTU MPU violation in ESM */
		{
			TestFailureFlag_Cnt_T_u32 = HTU1MPUSTARTUPFAIL;
		}
		else
		/* clear the ESM bit and MPCS bit for the next test */
		{
			ESMREGS->ESMSR1 = 0x00000200UL;
			HTU0REG->MPCS |= (1UL << 16U);	/* MPEFT0 */
		}
	}
	if (TestFailureFlag_Cnt_T_u32 == 0UL)
	{
		/* test 4 - unsuccessful transfer from main memory to NHET RAM */
		HET_Transst_7.memory.data_word = D_HTUDATA4_CNT_U32; /* trigger transfer 4 */
		WaitForHtuTransfer (&(HET_FRCTR_7.memory.data_word));
		if ((HET_mvstrt4_7.memory.data_word != D_HTUDUMMYDATA_CNT_U32) ||
			(0U == (ESMREGS->ESMSR1 & 0x00000200UL)))
		/* test failure if data did transfer (*Transfer4Data_ptr data changed from initial pattern) 
		   or no HTU MPU violation in ESM */
		{
			TestFailureFlag_Cnt_T_u32 = HTU1MPUSTARTUPFAIL;
		}
	}
	
	/* end-of-test housekeeping */

	NHET0->NHETGCR &= 0xFFFFFFFEUL;	/* Disable NHET */
	NHET0->NHETREQENC =			/* Disable HTU Request */
		(1UL << 1) |			/* Request 1 */
		(1UL << 2) |  			/* Request 2 */
		(1UL << 3) |            /* Request 3 */
		(1UL << 4);				/* Request 4 */

	HTU0REG->GC = 0x01U; /* reset HTU -- will return all HTU registers to reset value */
	if (0U != (ESMREGS->ESMSR1 & 0x00000200UL))
	{
		ESMREGS->ESMSR1 = 0x00000200UL; /* clear the ESM bit */
	}
	
	if (TestFailureFlag_Cnt_T_u32 != 0UL)
	{
		ResetCause_Cnt_Enum = HTU1MPUSTARTUPFAIL;
		DiagFailed();
	}
}

/*****************************************************************************
  * Name:        StartupHTU1Init
  * Description: This function initializes the HTU for the startup HTU MPU prooftest
  * Inputs:      None
  * Outputs:     None
  * Usage Notes: None
*****************************************************************************/
static inline void StartupHTU1Init(void)
{
												
	/***********************************************************
	 * Configure the control packets for HTU MPU startup prooftest *
	 ***********************************************************/
 
	/* Start by clearing the HTU memory....HTU Req 1
		Reset DIR, Size, Transfer mode means  HTU IHADDRCT = 0*/
	HTU0DCP1->IHADDRCT  = 	(0UL << 23U) | 	/* DIR */
							(0UL << 22U) | 	/* SIZE */
							(0UL << 21U) | 	/* ADDMH */
							(0UL << 20U) | 	/* ADDFM */
							(0UL << 18U) | 	/* TMBA */
							(0UL << 16U) | 	/* TMBB */
							(0UL << 2U)  ; 	/* IHADDR */	
							
	HTU0DCP1->IFADDRA  =  0UL;						/*clear the address of Buffer A */
    HTU0DCP1->IFADDRB  =  0UL;						/*clear the address of Buffer B */

    HTU0DCP1->ITCOUNT  =  (0UL << 16U) | 	/* IETCOUNT Element count reset to 0  */
						  (0UL << 0U) ;			/*Frame count set to 0 to make sure it is cleared before set	*/		
													
     				

    /* Start by clearing the HTU memory....HTU Req 2*/

   HTU0DCP2->IHADDRCT  = 	(0UL << 23U) | 	/* DIR */
							(0UL << 22U) | 	/* SIZE */
							(0UL << 21U) | 	/* ADDMH */
							(0UL << 20U) | 	/* ADDFM */
							(0UL << 18U) | 	/* TMBA */
							(0UL << 16U) | 	/* TMBB */
							(0UL << 2U); 	/* IHADDR */		
							
	HTU0DCP2->IFADDRA  =  0UL;						/*clear the address of Buffer A */
    HTU0DCP2->IFADDRB  =  0UL;						/*clear the address of Buffer B */

    HTU0DCP2->ITCOUNT  =  (0UL << 16U) | 		/* IETCOUNT Element count reset to 0  */
						  (0UL << 0U) ;			/*Frame count set to 0 to make sure it is cleared before set	*/		

    /* Start by clearing the HTU memory....HTU Req 3*/

   HTU0DCP3->IHADDRCT  = 	(0UL << 23U) | 	/* DIR */
							(0UL << 22U) | 	/* SIZE */
							(0UL << 21U) | 	/* ADDMH */
							(0UL << 20U) | 	/* ADDFM */
							(0UL << 18U) | 	/* TMBA */
							(0UL << 16U) | 	/* TMBB */
							(0UL << 2U); 	/* IHADDR */		
							
	HTU0DCP3->IFADDRA  =  0UL;						/*clear the address of Buffer A */
    HTU0DCP3->IFADDRB  =  0UL;						/*clear the address of Buffer B */

    HTU0DCP3->ITCOUNT  =  (0UL << 16U) | 		/* IETCOUNT Element count reset to 0  */
						  (0UL << 0U) ;			/*Frame count set to 0 to make sure it is cleared before set	*/		


    /* Start by clearing the HTU memory....HTU Req 4*/

   HTU0DCP4->IHADDRCT  = 	(0UL << 23U) | 	/* DIR */
							(0UL << 22U) | 	/* SIZE */
							(0UL << 21U) | 	/* ADDMH */
							(0UL << 20U) | 	/* ADDFM */
							(0UL << 18U) | 	/* TMBA */
							(0UL << 16U) | 	/* TMBB */
							(0UL << 2U); 	/* IHADDR */		
							
	HTU0DCP4->IFADDRA  =  0UL;						/*clear the address of Buffer A */
    HTU0DCP4->IFADDRB  =  0UL;						/*clear the address of Buffer B */

    HTU0DCP4->ITCOUNT  =  (0UL << 16U) | 		/* IETCOUNT Element count reset to 0  */
						  (0UL << 0U) ;			/*Frame count set to 0 to make sure it is cleared before set	*/		



	/* HTU Req 1 -- configure the control packet */
	HTU0DCP1->IFADDRA = (uint32)&(HTU1MPUTest_Cnt_M_u32[1]);		/* Main memory address; MPU allow access to index 1 and 2 */
	HTU0DCP1->ITCOUNT = 	(1UL 	<< 16U) | 	/* IETCOUNT */
							(1UL	<< 0U); 	/* IFTCOUNT */
							
	HTU0DCP1->IHADDRCT = (0UL << 23U) | /* DIR */		/* 0: transfer from NHET RAM to Main Memory */
						(0UL << 22U) | 	/* SIZE */      /* 32-bit transfer size */
						(0UL << 21U) | 	/* ADDMH */
						(0UL << 20U) | 	/* ADDFM */
						(1UL << 18U) | 	/* TMBA */		/* Circular buffer mode buffer A */
						(0UL << 16U) | 	/* TMBB */		/* One shot mode buffer B */
						(D_HTUSTARTUPADDR1_CNT_U32 << 0U); 	/* IHADDR */	/* address offset of NHET instruction data field location to transfer */
	
	/* HTU Req 2 -- configure the control packet */
	HTU0DCP2->IFADDRA = (uint32)&(HTU1MPUTest_Cnt_M_u32[2]);		/* Main memory address; MPU allow access to index 1 and 2 */
	HTU0DCP2->ITCOUNT = 	(1UL 	<< 16U) | 	/* IETCOUNT */
							(1UL	<< 0U); 	/* IFTCOUNT */
						
	HTU0DCP2->IHADDRCT = (1UL << 23U) | /* DIR */		/* 1: transfer from Main Memory to NHET RAM */
						(0UL << 22U) | 	/* SIZE */      /* 32-bit transfer size */
						(0UL << 21U) | 	/* ADDMH */
						(0UL << 20U) | 	/* ADDFM */
						(1UL << 18U) | 	/* TMBA */		/* Circular buffer  Buffer A*/
						(0UL << 16U) | 	/* TMBB */		/*  One shot mode  Buffer B*/
						(D_HTUSTARTUPADDR2_CNT_U32 << 0U); 	/* IHADDR */	/* address offset of NHET instruction data field location to transfer */

	/* HTU Req 3 -- configure the control packet */
	HTU0DCP3->IFADDRA = (uint32)&(HTU1MPUTest_Cnt_M_u32[3]);		/* Main memory address; MPU allow access to index 1 and 2 */
	HTU0DCP3->ITCOUNT = 	(1UL 	<< 16U) | 	/* IETCOUNT */
							(1UL	<< 0U); 	/* IFTCOUNT */
							
	HTU0DCP3->IHADDRCT = (0UL << 23U) | /* DIR */		/* 0: transfer from NHET RAM to Main Memory */
						(0UL << 22U) | 	/* SIZE */      /* 32-bit transfer size */
						(0UL << 21U) | 	/* ADDMH */
						(0UL << 20U) | 	/* ADDFM */
						(1UL << 18U) | 	/* TMBA */		/* Circular buffer mode buffer A */
						(0UL << 16U) | 	/* TMBB */		/* One shot mode buffer B */
						(D_HTUSTARTUPADDR3_CNT_U32 << 0U); 	/* IHADDR */	/* address offset of NHET instruction data field location to transfer */
	
	/* HTU Req 4 -- configure the control packet */
	HTU0DCP4->IFADDRA = (uint32)&(HTU1MPUTest_Cnt_M_u32[0]);		/* Main memory address; MPU allow access to index 1 and 2 */
	HTU0DCP4->ITCOUNT = 	(1UL 	<< 16U) | 	/* IETCOUNT */
							(1UL	<< 0U); 	/* IFTCOUNT */
						
	HTU0DCP4->IHADDRCT = (1UL << 23U) | /* DIR */		/* 1: transfer from Main Memory to NHET RAM */
						(0UL << 22U) | 	/* SIZE */      /* 32-bit transfer size */
						(0UL << 21U) | 	/* ADDMH */
						(0UL << 20U) | 	/* ADDFM */
						(1UL << 18U) | 	/* TMBA */		/* Circular buffer  Buffer A*/
						(0UL << 16U) | 	/* TMBB */		/*  One shot mode  Buffer B*/
						(D_HTUSTARTUPADDR4_CNT_U32 << 0U); 	/* IHADDR */	/* address offset of NHET instruction data field location to transfer */

	/*configure the HTU*/
	HTU0REG->CPENA = 0x154UL; 		      /* CPA is enabled, CPB is disabled for control packets 1, 2, 3, 4 */
	
	/* configure HTU MPU region 0 only */
	HTU0REG->MPCS = (0UL << 17U) |	/* MPEFT1 */	/*Cleared on reset*/
					(0UL << 16U) |	/* MPEFT0 */	/*Cleared on reset*/
					(0UL << 5U) |	/* INTENA01 */
					(0UL << 4U) |	/* ACCR01 */
					(0UL << 3U) |	/* REG01ENA */
					(1UL << 2U) |	/* INTENA0 */
					(1UL << 1U) |	/* ACCR */     /* no HTU access allowed outside configured region 0 */
					(1UL << 0U);	/* REG0ENA */
					
	/* allow read/write access to HTUMPUTest_Cnt_M_u32{1] and [2] */
	HTU0REG->MP0S = (uint32)&(HTU1MPUTest_Cnt_M_u32[1]); /* 32-bit aligned address of first allowed location in region 0 */
	HTU0REG->MP0E = (uint32)&(HTU1MPUTest_Cnt_M_u32[2]); /* 32-bit aligned address of last allowed location in region 0 */

	HTU0REG->GC	   =  (1UL << 16U) |      /*Enable the HTU*/
					  (1UL << 8U)  |       /* Allow HTU to continue on debug*/
					  (0UL << 0U);   	   /* No Reset request issued to the HTU module.*/
					  
}


#endif

#if (N2HET2TU_MPU_ENABLE)

/*****************************************************************************
 * Name:        Nhet2HTUMPUCheck
 * Description: NHET2 - startup check of HTU2 MPU error detection and signaling mechanism
 * Inputs:      None
 * Outputs:     ResetCause_Cnt_Enum is set if HTU2 MPU test fails
 * Usage Notes: If HTU2 MPU test fails, this function calls DiagFailed() and does not return 
 *****************************************************************************/
static void Nhet2HTUMPUCheck(void)
{

volatile HETPROGRAM7_UN* const HetProgAtStartup_ptr = (volatile HETPROGRAM7_UN*)D_BASEADDNHET2RAM_CNT_U32;

uint32 TestFailureFlag_Cnt_T_u32 = 0UL;
uint16 index_Cnt_T_u16;

	/* Start initialization of N2HET1 Peripheral (N2HET1 registers named NHET0; N2HET2 registers named NHET1) */
	NHET1->NHETGCR =
		(1UL << 24U) |					/* 0: Enable output buffers */
		(1UL << 18U) |					/* 0: When NHET is running, program fields are read-only */
		(1UL << 17U) |					/* 1: NHET doesn't stop when a software breakpoint is encountered.*/
		(1UL << 16U) |					/* 1: NHET is master */
		(0UL <<  0U);					/* 0: Stop NHET */
	
	/* copy the HET startup prog */
	(void) memcpy((void *) HetProgAtStartup_ptr, (const void *) HET_INIT7_PST, sizeof(HET_INIT7_PST)); /* PRQA S 312 */
	/* MISRA-C:2004 Rule 11.5: This deviation is required for memcpy call; volatile qualification not needed inside memcpy function */

	NHET1->NHETPFR =			/* Timer Prescale */
		(4UL << 8) |				/* 4 -> lr=16 */
		(0UL << 0);				/* 0 -> hr=1:  ts = 16*1 = 16 */
		
	NHET1->NHETSFENA =			/* Enable suppression Filter */
		(1UL << 30) |				/* Enable on ch 30 */
		(1UL << 12);				/* Enable on ch 12 */
	
	NHET1->NHETREQENS =			/* Enable HTU Request */
		(1UL << 1) |			/* Enable Request 1 */
		(1UL << 2) |  			/* Enable Request 2 */
		(1UL << 3) |            /* Enable Request 3 */
	    (1UL << 4);				/* Enable Request 4 */

	NHET1->NHETREQDS =			/* HTU Request Destination */
		(0UL << 1) |			/* HTU Request 1 */
		(0UL << 2) |  			/* HTU Request 2 */
		(0UL << 3) |  			/* HTU Request 3 */
		(0UL << 4);  			/* HTU Request 4 */
			
	/* End initialization of NHET 0 Peripheral */
	
	/* Startup Code HTU initialization   */
	StartupHTU2Init();

	/* Enable NHET */
	NHET1->NHETGCR |= 0x01U;			
	
	/* begin HTU MPU check */
	
	for (index_Cnt_T_u16 = 0u; index_Cnt_T_u16 < 4u; index_Cnt_T_u16++)
	{
		HTU2MPUTest_Cnt_M_u32[index_Cnt_T_u16] = D_HTUTESTDATA_CNT_U32;
	}
	
	/* test 1 - successful transfer from NHET RAM to main memory */
	HET_Transst_7.memory.data_word = D_HTUDATA1_CNT_U32; /* trigger transfer 1 */
	WaitForHtuTransfer (&(HET_FRCTR_7.memory.data_word));
	if ((HTU2MPUTest_Cnt_M_u32[1] != D_HTUDATA1_CNT_U32) || 
		(0U != (ESMREGS->ESMSR1 & 0x00000200UL)))
	/* test failure if data did not transfer or HTU MPU violation in ESM */
	{
		TestFailureFlag_Cnt_T_u32 = HTU2MPUSTARTUPFAIL;
	}
	if (TestFailureFlag_Cnt_T_u32 == 0UL)
	{
		/* test 2 - successful transfer from main memory to NHET RAM */
		HET_Transst_7.memory.data_word = D_HTUDATA2_CNT_U32; /* trigger transfer 2 */
		WaitForHtuTransfer (&(HET_FRCTR_7.memory.data_word));
		if ((HET_mvstrt2_7.memory.data_word != D_HTUTESTDATA_CNT_U32) ||
			(0U != (ESMREGS->ESMSR1 & 0x00000200UL)))
		/* test failure if data did not transfer or HTU MPU violation in ESM */
		{
			TestFailureFlag_Cnt_T_u32 = HTU2MPUSTARTUPFAIL;
		}
	}
	if (TestFailureFlag_Cnt_T_u32 == 0UL)
	{
		/* test 3 - unsuccessful transfer from NHET RAM to main memory */
		HET_Transst_7.memory.data_word = D_HTUDATA3_CNT_U32; /* trigger transfer 3 */
		WaitForHtuTransfer (&(HET_FRCTR_7.memory.data_word));
		if ((HTU2MPUTest_Cnt_M_u32[3] != D_HTUTESTDATA_CNT_U32) || 
			(0U == (ESMREGS->ESMSR1 & 0x00000200UL)))
		/* test failure if data did transfer (HTUMPUTest_Cnt_M_u32[3] changed from initial pattern) 
		   or no HTU MPU violation in ESM */
		{
			TestFailureFlag_Cnt_T_u32 = HTU2MPUSTARTUPFAIL;
		}
		else
		/* clear the ESM bit and MPCS bit for the next test */
		{
			ESMREGS->ESMSR1 = 0x00000200UL;
			HTU1REG->MPCS |= (1UL << 16U);	/* MPEFT0 */
		}
	}
	if (TestFailureFlag_Cnt_T_u32 == 0UL)
	{
		/* test 4 - unsuccessful transfer from main memory to NHET RAM */
		HET_Transst_7.memory.data_word = D_HTUDATA4_CNT_U32; /* trigger transfer 4 */
		WaitForHtuTransfer (&(HET_FRCTR_7.memory.data_word));
		if ((HET_mvstrt4_7.memory.data_word != D_HTUDUMMYDATA_CNT_U32) ||
			(0U == (ESMREGS->ESMSR1 & 0x00000200UL)))
		/* test failure if data did transfer (*Transfer4Data_ptr data changed from initial pattern) 
		   or no HTU MPU violation in ESM */
		{
			TestFailureFlag_Cnt_T_u32 = HTU2MPUSTARTUPFAIL;
		}
	}
	
	/* end-of-test housekeeping */
	NHET1->NHETGCR &= 0xFFFFFFFEUL;	/* Disable NHET */
	NHET1->NHETREQENC =			/* Disable HTU Request */
		(1UL << 1) |			/* Request 1 */
		(1UL << 2) |  			/* Request 2 */
		(1UL << 3) |            /* Request 3 */
		(1UL << 4);				/* Request 4 */

	HTU1REG->GC = 0x01U; /* reset HTU -- will return all HTU registers to reset value */
	if (0U != (ESMREGS->ESMSR1 & 0x00000200UL))
	{
		ESMREGS->ESMSR1 = 0x00000200UL; /* clear the ESM bit */
	}
	
	if (TestFailureFlag_Cnt_T_u32 != 0UL)
	{
		ResetCause_Cnt_Enum = HTU2MPUSTARTUPFAIL;
		DiagFailed();
	}
}

/*****************************************************************************
  * Name:        StartupHTU2Init
  * Description: This function initializes the HTU for the startup HTU MPU prooftest
  * Inputs:      None
  * Outputs:     None
  * Usage Notes: None
*****************************************************************************/
static inline void StartupHTU2Init(void)
{
												
	/***********************************************************
	 * Configure the control packets for HTU MPU startup prooftest *
	 ***********************************************************/
 
	/* Start by clearing the HTU memory....HTU Req 1
		Reset DIR, Size, Transfer mode means  HTU IHADDRCT = 0*/
	HTU1DCP1->IHADDRCT  = 	(0UL << 23U) | 	/* DIR */
							(0UL << 22U) | 	/* SIZE */
							(0UL << 21U) | 	/* ADDMH */
							(0UL << 20U) | 	/* ADDFM */
							(0UL << 18U) | 	/* TMBA */
							(0UL << 16U) | 	/* TMBB */
							(0UL << 2U)  ; 	/* IHADDR */	
							
	HTU1DCP1->IFADDRA  =  0UL;						/*clear the address of Buffer A */
    HTU1DCP1->IFADDRB  =  0UL;						/*clear the address of Buffer B */

    HTU1DCP1->ITCOUNT  =  (0UL << 16U) | 	/* IETCOUNT Element count reset to 0  */
						  (0UL << 0U) ;			/*Frame count set to 0 to make sure it is cleared before set	*/		
													
     				

    /* Start by clearing the HTU memory....HTU Req 2*/

   HTU1DCP2->IHADDRCT  = 	(0UL << 23U) | 	/* DIR */
							(0UL << 22U) | 	/* SIZE */
							(0UL << 21U) | 	/* ADDMH */
							(0UL << 20U) | 	/* ADDFM */
							(0UL << 18U) | 	/* TMBA */
							(0UL << 16U) | 	/* TMBB */
							(0UL << 2U); 	/* IHADDR */		
							
	HTU1DCP2->IFADDRA  =  0UL;						/*clear the address of Buffer A */
    HTU1DCP2->IFADDRB  =  0UL;						/*clear the address of Buffer B */

    HTU1DCP2->ITCOUNT  =  (0UL << 16U) | 		/* IETCOUNT Element count reset to 0  */
						  (0UL << 0U) ;			/*Frame count set to 0 to make sure it is cleared before set	*/		

    /* Start by clearing the HTU memory....HTU Req 3*/

   HTU1DCP3->IHADDRCT  = 	(0UL << 23U) | 	/* DIR */
							(0UL << 22U) | 	/* SIZE */
							(0UL << 21U) | 	/* ADDMH */
							(0UL << 20U) | 	/* ADDFM */
							(0UL << 18U) | 	/* TMBA */
							(0UL << 16U) | 	/* TMBB */
							(0UL << 2U); 	/* IHADDR */		
							
	HTU1DCP3->IFADDRA  =  0UL;						/*clear the address of Buffer A */
    HTU1DCP3->IFADDRB  =  0UL;						/*clear the address of Buffer B */

    HTU1DCP3->ITCOUNT  =  (0UL << 16U) | 		/* IETCOUNT Element count reset to 0  */
						  (0UL << 0U) ;			/*Frame count set to 0 to make sure it is cleared before set	*/		


    /* Start by clearing the HTU memory....HTU Req 4*/

   HTU1DCP4->IHADDRCT  = 	(0UL << 23U) | 	/* DIR */
							(0UL << 22U) | 	/* SIZE */
							(0UL << 21U) | 	/* ADDMH */
							(0UL << 20U) | 	/* ADDFM */
							(0UL << 18U) | 	/* TMBA */
							(0UL << 16U) | 	/* TMBB */
							(0UL << 2U); 	/* IHADDR */		
							
	HTU1DCP4->IFADDRA  =  0UL;						/*clear the address of Buffer A */
    HTU1DCP4->IFADDRB  =  0UL;						/*clear the address of Buffer B */

    HTU1DCP4->ITCOUNT  =  (0UL << 16U) | 		/* IETCOUNT Element count reset to 0  */
						  (0UL << 0U) ;			/*Frame count set to 0 to make sure it is cleared before set	*/		



	/* HTU Req 1 -- configure the control packet */
	HTU1DCP1->IFADDRA = (uint32)&(HTU2MPUTest_Cnt_M_u32[1]);		/* Main memory address; MPU allow access to index 1 and 2 */
	HTU1DCP1->ITCOUNT = 	(1UL 	<< 16U) | 	/* IETCOUNT */
							(1UL	<< 0U); 	/* IFTCOUNT */
							
	HTU1DCP1->IHADDRCT = (0UL << 23U) | /* DIR */		/* 0: transfer from NHET RAM to Main Memory */
						(0UL << 22U) | 	/* SIZE */      /* 32-bit transfer size */
						(0UL << 21U) | 	/* ADDMH */
						(0UL << 20U) | 	/* ADDFM */
						(1UL << 18U) | 	/* TMBA */		/* Circular buffer mode buffer A */
						(0UL << 16U) | 	/* TMBB */		/* One shot mode buffer B */
						(D_HTUSTARTUPADDR1_CNT_U32 << 0U); 	/* IHADDR */	/* address offset of NHET instruction data field location to transfer */
	
	/* HTU Req 2 -- configure the control packet */
	HTU1DCP2->IFADDRA = (uint32)&(HTU2MPUTest_Cnt_M_u32[2]);		/* Main memory address; MPU allow access to index 1 and 2 */
	HTU1DCP2->ITCOUNT = 	(1UL 	<< 16U) | 	/* IETCOUNT */
							(1UL	<< 0U); 	/* IFTCOUNT */
						
	HTU1DCP2->IHADDRCT = (1UL << 23U) | /* DIR */		/* 1: transfer from Main Memory to NHET RAM */
						(0UL << 22U) | 	/* SIZE */      /* 32-bit transfer size */
						(0UL << 21U) | 	/* ADDMH */
						(0UL << 20U) | 	/* ADDFM */
						(1UL << 18U) | 	/* TMBA */		/* Circular buffer  Buffer A*/
						(0UL << 16U) | 	/* TMBB */		/*  One shot mode  Buffer B*/
						(D_HTUSTARTUPADDR2_CNT_U32 << 0U); 	/* IHADDR */	/* address offset of NHET instruction data field location to transfer */

	/* HTU Req 3 -- configure the control packet */
	HTU1DCP3->IFADDRA = (uint32)&(HTU2MPUTest_Cnt_M_u32[3]);		/* Main memory address; MPU allow access to index 1 and 2 */
	HTU1DCP3->ITCOUNT = 	(1UL 	<< 16U) | 	/* IETCOUNT */
							(1UL	<< 0U); 	/* IFTCOUNT */
							
	HTU1DCP3->IHADDRCT = (0UL << 23U) | /* DIR */		/* 0: transfer from NHET RAM to Main Memory */
						(0UL << 22U) | 	/* SIZE */      /* 32-bit transfer size */
						(0UL << 21U) | 	/* ADDMH */
						(0UL << 20U) | 	/* ADDFM */
						(1UL << 18U) | 	/* TMBA */		/* Circular buffer mode buffer A */
						(0UL << 16U) | 	/* TMBB */		/* One shot mode buffer B */
						(D_HTUSTARTUPADDR3_CNT_U32 << 0U); 	/* IHADDR */	/* address offset of NHET instruction data field location to transfer */
	
	/* HTU Req 4 -- configure the control packet */
	HTU1DCP4->IFADDRA = (uint32)&(HTU2MPUTest_Cnt_M_u32[0]);		/* Main memory address; MPU allow access to index 1 and 2 */
	HTU1DCP4->ITCOUNT = 	(1UL 	<< 16U) | 	/* IETCOUNT */
							(1UL	<< 0U); 	/* IFTCOUNT */
						
	HTU1DCP4->IHADDRCT = (1UL << 23U) | /* DIR */		/* 1: transfer from Main Memory to NHET RAM */
						(0UL << 22U) | 	/* SIZE */      /* 32-bit transfer size */
						(0UL << 21U) | 	/* ADDMH */
						(0UL << 20U) | 	/* ADDFM */
						(1UL << 18U) | 	/* TMBA */		/* Circular buffer  Buffer A*/
						(0UL << 16U) | 	/* TMBB */		/*  One shot mode  Buffer B*/
						(D_HTUSTARTUPADDR4_CNT_U32 << 0U); 	/* IHADDR */	/* address offset of NHET instruction data field location to transfer */

	/*configure the HTU*/
	HTU1REG->CPENA = 0x154UL; 		      /* CPA is enabled, CPB is disabled for control packets 1, 2, 3, 4 */
	
	/* configure HTU MPU region 0 only */
	HTU1REG->MPCS = (0UL << 17U) |	/* MPEFT1 */	/*Cleared on reset*/
					(0UL << 16U) |	/* MPEFT0 */	/*Cleared on reset*/
					(0UL << 5U) |	/* INTENA01 */
					(0UL << 4U) |	/* ACCR01 */
					(0UL << 3U) |	/* REG01ENA */
					(1UL << 2U) |	/* INTENA0 */
					(1UL << 1U) |	/* ACCR */     /* no HTU access allowed outside configured region 0 */
					(1UL << 0U);	/* REG0ENA */
					
	/* allow read/write access to HTUMPUTest_Cnt_M_u32{1] and [2] */
	HTU1REG->MP0S = (uint32)&(HTU2MPUTest_Cnt_M_u32[1]); /* 32-bit aligned address of first allowed location in region 0 */
	HTU1REG->MP0E = (uint32)&(HTU2MPUTest_Cnt_M_u32[2]); /* 32-bit aligned address of last allowed location in region 0 */

	HTU1REG->GC	   =  (1UL << 16U) |      /*Enable the HTU*/
					  (1UL << 8U)  |       /* Allow HTU to continue on debug*/
					  (0UL << 0U);   	   /* No Reset request issued to the HTU module.*/
					  
}

#endif

static void checkB0RAMECC(void)
{
	volatile uint32 ramread_Cnt_T_u32;

	TCRAM0->RAMCTRL = 0x0005010A;			/* enable writes to ECC RAM, enable ECC error response */
	TCRAM0->RAMTHRESHOLD = 0x1;				/* the first 1-bit error will cause an error response */
	TCRAM0->RAMINTCTRL = 0x1;				/* allow SERR to be reported to ESM */

	_coreDisableRamEcc_();
	(*(volatile uint32 *)D_TCRAMA1BITERROR_CNT_U32) ^= 0x1;						/* cause a 1-bit ECC error */
	_coreEnableRamEcc_();
	TCRAM0->RAMCTRL = 0x0005000A;			/* disable writes to ECC RAM */

	ramread_Cnt_T_u32 = *(volatile uint32 *)D_TCRAMA1BIT_CNT_U32;						/* read from location with 1-bit ECC error */
	(*(volatile uint64 *)D_TCRAMA1BIT_CNT_U32) = 0x0;                   /* write to fix ECC errors, although hardware should do this already for 1 bit error */

	if ((0U == (TCRAM0->RAMERRSTATUS & 1)) || (0U == (ESMREGS->ESMSR1 & 0x04000000)))	/* SERR not set in TCRAM1 or TCRAM2 modules */
	{
		/* TCRAM module does not reflect 1-bit error reported by CPU */
		ResetCause_Cnt_Enum = B0SNGBITRAMECCDETFAILED;
		ESMREGS->ESMSR1 = 0x04000000;
		TCRAM0->RAMERRSTATUS = 0x1;						/* clear SERR flag */
		DiagFailed();
	}
	else
	{
		TCRAM0->RAMERRSTATUS = 0x1;			/* clear SERR flag */
		ESMREGS->ESMSR1 = 0x04000000;		/* clear status flags for ESM group1 channels 26 and 28 */
	}

	TCRAM0->RAMCTRL = 0x0005010A;			/* enable writes to ECC RAM, enable ECC error response */

	_coreDisableRamEcc_();
	(*(volatile uint32 *)D_TCRAMA2BITERROR_CNT_U32) ^= 0x3;						/* cause a 2-bit ECC error */
	_coreEnableRamEcc_();
	ramread_Cnt_T_u32 = TCRAM0->RAMCTRL;

	ResetCause_Cnt_Enum = B0MULBITRAMECCDETFAILED;
	ramread_Cnt_T_u32 = *(volatile uint32 *)D_TCRAMA2BIT_CNT_U32;	/* read from location with 2-bit ECC error */
															/* this will cause a data abort to be generated */
	(*(volatile uint64 *)D_TCRAMA2BIT_CNT_U32) = 0x0;				/* write to fix ECC errors */
	TCRAM0->RAMCTRL &= ~(0x00000100);						/* disable writes to ECC RAM */

	if (PWRONRESET != ResetCause_Cnt_Enum)
	{
		DiagFailed();
	}

	/* Read register to allow further errors to be detected */
	ramread_Cnt_T_u32 = TCRAM0->RAMUERRADDR;
}

static void checkB1RAMECC(void)
{
	volatile uint32 ramread_Cnt_T_u32;

	TCRAM1->RAMCTRL = 0x0005010A;
	TCRAM1->RAMTHRESHOLD = 0x1;				/* the first 1-bit error will cause an error response */
	TCRAM1->RAMINTCTRL = 0x1;				/* allow SERR to be reported to ESM */

	_coreDisableRamEcc_();
	(*(volatile uint32 *)D_TCRAMB1BITERROR_CNT_U32) ^= 0x1;						/* cause a 1-bit ECC error */
	_coreEnableRamEcc_();
	TCRAM1->RAMCTRL = 0x0005000A;			/* disable writes to ECC RAM */

	ramread_Cnt_T_u32 = *(volatile uint32 *)D_TCRAMB1BIT_CNT_U32;						/* read from location with 1-bit ECC error */
	(*(volatile uint64 *)D_TCRAMB1BIT_CNT_U32) = 0x0;       /* write to fix ECC errors, although hardware should do this already for 1 bit error */

	if ((0U == (TCRAM1->RAMERRSTATUS & 1)) || (0U == (ESMREGS->ESMSR1 & 0x10000000)))	/* SERR not set in TCRAM1 or TCRAM2 modules */
	{
		/* TCRAM module does not reflect 1-bit error reported by CPU */
		ResetCause_Cnt_Enum = B1SNGBITRAMECCDETFAILED;
		TCRAM1->RAMERRSTATUS = 0x1;						/* clear SERR flag */
		ESMREGS->ESMSR1 = 0x10000000;
		DiagFailed();
	}
	else
	{
		TCRAM1->RAMERRSTATUS = 0x1;			/* clear SERR flag */
		ESMREGS->ESMSR1 = 0x10000000;		/* clear status flags for ESM group1 channels 26 and 28 */
	}

	TCRAM0->RAMCTRL = 0x0005010A;
	TCRAM1->RAMCTRL = 0x0005010A;			/* enable writes to ECC RAM, enable ECC error response */

	_coreDisableRamEcc_();
	(*(volatile uint32 *)D_TCRAMB2BITERROR_CNT_U32) ^= 0x3;						/* cause a 2-bit ECC error */
	_coreEnableRamEcc_();
	ramread_Cnt_T_u32 = TCRAM1->RAMCTRL;

	ResetCause_Cnt_Enum = B1MULBITRAMECCDETFAILED;
	ramread_Cnt_T_u32 = *(volatile uint32 *)D_TCRAMB2BIT_CNT_U32;		/* read from location with 2-bit ECC error */
													/* this will cause a data abort to be generated */
	(*(volatile uint64 *)D_TCRAMB2BIT_CNT_U32) = 0x0;		/* write to fix ECC errors */
	TCRAM1->RAMCTRL &= ~(0x00000100);				/* disable writes to ECC RAM */
	TCRAM0->RAMCTRL &= ~(0x00000100);				/* disable writes to ECC RAM */
	if (PWRONRESET != ResetCause_Cnt_Enum)
	{
		DiagFailed();
	}

	/* Read register to allow further errors to be detected */
	ramread_Cnt_T_u32 = TCRAM1->RAMUERRADDR;
}

static void checkFlashECC(void)
{
	/* Routine to check operation of ECC logic inside CPU for accesses to program flash */

	volatile uint32 flashread_Cnt_T_u32;

	flashWREG->FEDACCTRL1 = 0x000A060A;			/* Flash Module ECC Response enabled */

	flashWREG->FDIAGCTRL = 0x00050007;			/* Enable diagnostic mode and select diag mode 7 */
	flashWREG->FPAROVR = 0x00005A01;			/* Select ECC diagnostic mode, single-bit to be corrupted */
	flashWREG->FDIAGCTRL |= 0x01000000;			/* Set the trigger for the diagnostic mode */

	flashread_Cnt_T_u32 = *(volatile uint32*)D_FLASHBADECC_CNT_U32;					/* read a flash location from the mirrored memory map */
	flashWREG->FDIAGCTRL = 0x000A0007;			/* disable diagnostic mode */

	/* this will have caused a single-bit error to be generated and corrected by CPU */
	if ((0U == (flashWREG->FEDACSTATUS & 0x2)) || (0 == (ESMREGS->ESMSR1 & 0x40)))		/* single-bit error not captured in flash module */
	{
		/* TCRAM module does not reflect 1-bit error reported by CPU */
		ResetCause_Cnt_Enum = SNGBITFLSECCDETFAILED;
		flashWREG->FEDACSTATUS = 0x2;				/* clear single-bit error flag */
		ESMREGS->ESMSR1 = 0x40;					/* clear ESM flag */
		DiagFailed();
	}
	else
	{
		flashWREG->FEDACSTATUS = 0x2;				/* clear single-bit error flag */
		ESMREGS->ESMSR1 = 0x40;					/* clear ESM flag */

		flashWREG->FDIAGCTRL = 0x00050007;			/* Enable diagnostic mode and select diag mode 7 */
		flashWREG->FPAROVR = 0x00005A03;			/* Select ECC diagnostic mode, two bits of ECC to be corrupted */
		flashWREG->FDIAGCTRL |= 0x01000000;			/* Set the trigger for the diagnostic mode */

		ResetCause_Cnt_Enum = MULBITFLSECCDETFAILED;
		flashread_Cnt_T_u32 = *(volatile uint32*)D_FLASHBADECC_CNT_U32;					/* read from flash location from mirrored memory map */
													/* this will cause a data abort */
		if (PWRONRESET != ResetCause_Cnt_Enum)
		{
			DiagFailed();
		}

		/* Read register to allow further errors to be detected */
		flashread_Cnt_T_u32 = flashWREG->FUNCERRADD;
	}

}

static void DiagFailed(void)
{
	ESMREGS->ESMEKR = 0xAU;  			/* Force error pin for safety */
	AppInit();
}

static void AppInit(void)
{
	/***************************** INITIALIZATION STEP 43 ****************************/
	/* initalise copy table */
	if ((uint32 *)&__binit__ != (uint32 *)0xFFFFFFFFU)
	{
		extern void copy_in(void *binit);
		copy_in((void *)&__binit__);
	}

	/* initalise the C global variables */
	if (&__TI_Handler_Table_Base < &__TI_Handler_Table_Limit)
	{
		uint8 **tablePtr   = (uint8 **)&__TI_CINIT_Base;
		uint8 **tableLimit = (uint8 **)&__TI_CINIT_Limit;

		while (tablePtr < tableLimit)
		{
			uint8 *loadAdr = *tablePtr++;
			uint8 *runAdr  = *tablePtr++;
			uint8  idx     = *loadAdr++;
			handler_fptr   handler = (handler_fptr)(&__TI_Handler_Table_Base)[idx];

			(*handler)((const uint8 *)loadAdr, runAdr);
		}
	}

	/* Initialize constructors */
	if (__TI_PINIT_Base < __TI_PINIT_Limit)
	{
		void (**p0)() = (void *)__TI_PINIT_Base;

		while ((uint32)p0 < __TI_PINIT_Limit)
		{
			void (*p)() = *p0++;
			p();
		}
	}

	/* Callout for Application Specific processing */
	AppStartupCallout2();
	main();
}

