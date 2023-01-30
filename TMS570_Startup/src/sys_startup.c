/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : sys_startup.c
* Module Description: TI Halcogen based micro init
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/* Version Control:
 * Date Created:      Thu Nov 11 16:33:22 2010
 * %version:          17 %
 * %derived_by:       gz7pm0 %
 * %date_modified:    Tue Jan 28 14:46:32 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/09/12  1        LWW       Initial Version
 * 06/11/12  2        LWW       Updates for LPO Trim issue
 * 07/06/12  3        LWW       Changed to disable resets in PLLCTL1, cleared VIM ISR requests prior to 
 *                              going to bootloader code, enabled DCAN parity prior to memory initialization
 * 08/06/12  4        BG        Added PLL Recovery Code
 * 08/14/12  5        BG        Updated PLL Recovery Code
 * 09/14/12  6        BDO       Update TrimLPO function to trim LPOMON HF and LF trims incrementally.
 * 02/14/13  8        LWW       Updates to make PLL and Flash Waitstates configurable
 * 02/15/13  9        BWL       Made RAM pbist only run on banks enabled in OTP memory
 * 08/02/13  11       LWW       Anomaly 3689 correction, changes to allow thumb mode compilation
 * 10/18/13	 12	      RM        ICR 4338: TI Errata: Repeat PBIST self test
 * 11/04/13  13       RM		ICR 4338: TI Errata: Repeat PBIST self test
 * 01/28/14  14       RM		CR 11315: K2xx: PBIST#4 Errata: PBIST self test workaround
 * 01/28/14  15       RM		CR 11315: K2xx: PBIST#4 Errata: PBIST self test workaround(Updated Revision History)
 * 04/28/14  16       BWL		Turn on DMA Parity before memory initalization.
 * 05/29/14	 17		  LK		Updated to match latest Halcogen 03.09.00 release for PBIST issue. 
 */

/* Include Files */
#include "sys_core.h"
#include "sys_memory.h"
#include "ResetCause.h"
#include "startup_cfg.h"
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
#include "sys_pmu.h"


/* Embedded Constants */
#define D_OTP1BITERRADDR_CNT_U32 		0xF00803F4U
#define D_OTP2BITERRADDR_CNT_U32		0xF00803FCU
#define D_DPRAMSELECT_CNT_U32			0x4U
#define D_SPRAMSELECT_CNT_U32			0x8U
#define D_EFCAUTOLOADERROREN_CNT_U32    0x00040000U /* 18 OUTPUT */
#define D_EFCINSTRUCTIONERROREN_CNT_U32 0x00080000U /* 19 OUTPUT */
#define D_EFCINSTRUCTIONINFOEN_CNT_U32  0x00100000U /* 20 OUTPUT */
#define D_EFCSELFTESTERROREN_CNT_U32   	0x00200000U /* 21 OUTPUT */
#define D_EFCSELFTESTDONE_CNT_U32		0x00008000U /* 15 */
#define D_EFCSELFTESTERROR_CNT_U32  	0x00004000U /* 14 */
#define D_OUTPUTENABLE_CNT_U32        	0x0003C000U /* 17:14 OUTPUT */
#define D_SELFTESTERROR_CNT_U32         0x18U
#define D_LPOTRIMVALUE_CNT_U32  		(((*(uint32*)0xF00801B4U) & 0xFFFF0000)>>16)

#define D_LOWBYTEMASK_CNT_U32 			0x0000000FFUL
#define D_CURRENTLPOTRIMMASK_CNT_U32	0x00000FFFFUL
#define D_LPOMONLFTRIMMASK_CNT_U32   	0xFFFFFF00UL
#define D_LPOMONHFTRIMMASK_CNT_U32  	0xFFFF00FFUL

#define D_PLLSLIPMASK_CNT_U32		    0x00000300

#define D_OTPRAMDEVICEADDR_CNT_U32		((volatile uint32*)0xF0080148u)
#define GetRamDomian1Enabled()			((boolean)((*D_OTPRAMDEVICEADDR_CNT_U32 >> 10) & 0x01u))
#define GetRamDomian2Enabled()			((boolean)((*D_OTPRAMDEVICEADDR_CNT_U32 >> 12) & 0x01u))
#define GetRamDomian3Enabled()			((boolean)((*D_OTPRAMDEVICEADDR_CNT_U32 >> 14) & 0x01u))

#define D_ESRAM5ENABLE_CNT_U32			((uint32)(0x01<<20))
#define D_ESRAM6ENABLE_CNT_U32			((uint32)(0x01<<21))
#define D_ESRAM8ENABLE_CNT_U32			((uint32)(0x01<<27))

/* Type Definitions */                  

enum systemClockSource
{
    SYS_OSC       		= 0,  /**< Alias for oscillator clock Source                */
    SYS_PLL1      		= 1,  /**< Alias for Pll1 clock Source                      */
    SYS_EXTERNAL1  		= 3, /**< Alias for external clock Source                  */
    SYS_LPO_LOW   		= 4,  /**< Alias for low power oscillator low clock Source  */
    SYS_LPO_HIGH  		= 5,  /**< Alias for low power oscillator high clock Source */
    SYS_PLL2    		= 6,			 /**< Alias for Pll2 clock Source                      */
    SYS_EXTERNAL2 		= 7,  /**< Alias for external 2 clock Source                */
    SYS_VCLK      		= 9   /**< Alias for synchronous VCLK1 clock Source         */
};


/* External Functions */
extern void BootStartup(void);
static void Startup(void);
static inline void DiagFailedReset(void);
static void resetStartup(uint32);
static inline void pwronStartup(void);
static inline void afterSTC(void);
static inline void setupPLL(void);
static inline void trimLPO(void);
static inline void setupFlash(void);
static inline void periphInit(void);
static inline void mapClocks(void);
static inline void ccmSelfCheck(void);
static inline void stcSelfCheck(void);
static inline void cpuSelfTest(void);
static inline void efcCheck(void);
static inline void efcSelfTest(void);
static inline boolean efcStuckZeroTestPassed(void);
static inline boolean checkEFCSelfTestPassed(void);
static inline void fmcBus2Check(void);
static inline void fmcECCcheck(void);
static inline void pbistSelfCheck(void);
static inline void pbistRun(uint32, uint32);
static inline void pbistStop(void);
static inline void memInitialization(uint32);
static inline void Delay(void);
static inline void errata_PBIST_4(void);

/* Startup Routine */
#pragma INTERRUPT(Startup, RESET)
#pragma INTERRUPT(_c_int00, RESET)
#pragma CODE_STATE(_c_int00, 32);
void _c_int00()
{
	Startup();
}
static void Startup(void)
{
/***************************** INITIALIZATION STEP 01 *****************************/
    /* Enable VFP Unit */
    _coreEnableVfp_();

/***************************** INITIALIZATION STEP 02 *****************************/
    /* Initialize Core Registers, including stack pointers for all modes */
    _coreInitRegisters_();

/*############################ ERRATA DEVICE#140 WORKAROUND ############################*/
    /* Implement work-around for CCM-R4 issue on silicon revision A */
	if (systemREG1->DEV == 0x802AAD05)
	{
		_esmCcmErrorsClear_();
	}

/***************************** INITIALIZATION STEP 03 *****************************/
    /* Enable response to ECC errors indicated by CPU for accesses to flash */
    flashWREG->FEDACCTRL1 = 0x000A060A;

/***************************** INITIALIZATION STEP 04 *****************************/
	/* Enable CPU Event Export */
    /* This allows the CPU to signal any single-bit or double-bit errors detected
     * by its ECC logic for accesses to program flash or data RAM.
     */
    asm("	mrc   p15, #0x00, r0,         c9, c12, #0x00");
    asm("	orr   r0,  r0,    #0x10");
    asm("	mcr   p15, #0x00, r0,         c9, c12, #0x00");
    asm("	mrc   p15, #0x00, r0,         c9, c12, #0x00");

/***************************** INITIALIZATION STEP 05 *****************************/
    /* Enable CPU ECC checking for ATCM (flash accesses) */
    asm("	mrc   p15, #0x00, r0,         c1, c0,  #0x01");
    asm("	orr   r0,  r0,    #0x1<<25");
    asm("	dmb");
    asm("	mcr   p15, #0x00, r0,         c1, c0,  #0x01");
    asm("	isb");

/***************************** INITIALIZATION STEP 06 *****************************/
    /* Reset handler: the following instructions read from the system exception status register
     * to identify the cause of the CPU reset.
     */

    /* Special Handling when Debugger connected (bypass normal startup) */
    if ((_coreGetDebugStatusAndControlRegister_() & 0x00004000U) != 0)
    {
    	/* clear all reset status flags */
		systemREG1->SYSESR = 0xFFFF;
		ResetCause_Cnt_Enum = DEBUGRESET;
		/* TODO: Do we want to set error pin here? */

		/* continue with normal start-up sequence */
		resetStartup(D_RAMRESETINITMASKTMS_CNT_U32);
    }

    /* check for power-on reset condition */
	if (0 != (systemREG1->SYSESR & 0x8000))
	{
		/* clear all reset status flags */
		systemREG1->SYSESR = 0xFFFF;
		ResetCause_Cnt_Enum = PWRONRESET;

		/* continue with normal start-up sequence */
		pwronStartup();
	}
	else if (0 != (systemREG1->SYSESR & 0x4000))
	{
		/* Reset caused due to oscillator failure. */
		/* clear all reset status flags */
		systemREG1->SYSESR = 0xFFFF;
		ResetCause_Cnt_Enum = OSCFAIL;
		/* TODO: Do we want to set error pin here? */

		resetStartup(D_RAMRESETINITMASKTMS_CNT_U32);
	}
	else if (0 != (systemREG1->SYSESR & 0x2000))
	{
		/* Reset caused due to windowed watchdog violation. */
		/* clear all reset status flags */
		systemREG1->SYSESR = 0xFFFF;
		ResetCause_Cnt_Enum = WDGFAIL;
		/* TODO: Do we want to set error pin here? */

		resetStartup(D_RAMRESETINITMASKTMS_CNT_U32);
	}
	else if (0 != (systemREG1->SYSESR & 0x20))
	{
		/* Reset caused due to CPU reset.
		CPU reset can be caused by CPU self-test completion, or
		by toggling the "CPU RESET" bit of the CPU Reset Control Register. */

		/* reset could be caused by stcSelfCheck run or by an actual CPU self-test run */
		if ((stcREG->STCSCSCR & 0xF) == 0xA)			/* check if this was an stcSelfCheck run */
		{
			/* check if the self-test fail bit is set */
			if ((stcREG->STCGSTAT & 0x3) != 0x3)
			{
				systemREG1->SYSESR = 0xFFFF;
				ResetCause_Cnt_Enum = STCSCFAILED;
				DiagFailedReset();						/* STC self-check has failed */
			}
			else										/* STC self-check has passed */
			{
				stcREG->STCSCSCR = 0x05;				/* clear self-check mode */
				stcREG->STCGSTAT = 0x3;					/* clear STC global status flags */
				ESMREGS->ESMSR1 = 0x08000000;		/* clear ESM group1 channel 27 status flag */
				/* clear all reset status flags */
				systemREG1->SYSESR = 0xFFFF;
/***************************** INITIALIZATION STEP 22 *****************************/
				cpuSelfTest();							/* Start CPU Self-Test */
			}
		}
		else if ((stcREG->STCGSTAT & 0x1) == 0x1)		/* CPU reset caused by CPU self-test completion */
		{
			if ((stcREG->STCGSTAT & 0x2) == 0x2)		/* Self-Test Fail flag is set */
			{
				systemREG1->SYSESR = 0xFFFF;
				ResetCause_Cnt_Enum = STCFAILED;
				DiagFailedReset();						/* CPU self-test failed */
			}
			else										/* CPU self-test completed successfully */
			{
				stcREG->STCGSTAT = 0x3;					/* clear STC global status flags */
				/* clear all reset status flags */
				systemREG1->SYSESR = 0xFFFF;
				afterSTC();								/* Continue start-up sequence after CPU STC completed */
			}
		}
		else											/* CPU reset caused by software writing to CPU RESET bit */
		{
			/* clear all reset status flags */
			systemREG1->SYSESR = 0xFFFF;
			
			if (PWRONRESET == ResetCause_Cnt_Enum)
			{
				ResetCause_Cnt_Enum = CPURESET;
			}
			resetStartup(D_RAMRESETINITMASKTMS_CNT_U32);
		}
	}
	else if (systemREG1->SYSESR & 0x10)
	{
		/* clear all reset status flags */
		systemREG1->SYSESR = 0xFFFF;

		if ((STCSCFAILED == ResetCause_Cnt_Enum) ||
			(STCFAILED == ResetCause_Cnt_Enum) ||
			(ESM3NONZERO == ResetCause_Cnt_Enum) ||
			(EFCSTFAILED == ResetCause_Cnt_Enum) ||
			(SPPBISTFAILED == ResetCause_Cnt_Enum) ||
			(DPPBISTFAILED == ResetCause_Cnt_Enum) ||
			(EFCSTUCKZERO == ResetCause_Cnt_Enum) ||
			(EFCERROR == ResetCause_Cnt_Enum) ||
			(FLSBUS2CORRFAILED == ResetCause_Cnt_Enum) ||
			(FLSBUS2ADDCAPFAILED == ResetCause_Cnt_Enum) ||
			(FLSBUS2MULBITDETFAILED == ResetCause_Cnt_Enum) ||
			(FLSBUS2SNGBITDETFAILED == ResetCause_Cnt_Enum) ||
			(CCMSTFAILED == ResetCause_Cnt_Enum) ||
			(CCMSTEFFAILED == ResetCause_Cnt_Enum) ||
			(CCMEFFAILED == ResetCause_Cnt_Enum) ||
			(PBISTSCFAILED == ResetCause_Cnt_Enum) ||
			(LPOTRIMERROR == ResetCause_Cnt_Enum))
		{
			ESMREGS->ESMEKR = 0xAU;  						/* Force error pin for safety */
			resetStartup(D_RAMPWRONINITMASKTMS_CNT_U32);
		}

		if (PWRONRESET == ResetCause_Cnt_Enum)
		{
			ResetCause_Cnt_Enum = SWRESET;
		}
		resetStartup(D_RAMRESETINITMASKTMS_CNT_U32);
	}
	else
	{
		/* Reset caused by nRST being driven low externally. */
		/* clear all reset status flags */
		systemREG1->SYSESR = 0xFFFF;
		ResetCause_Cnt_Enum = EXTRESET;
		/* TODO: Do we want to set error pin here? */

		resetStartup(D_RAMRESETINITMASKTMS_CNT_U32);
	}
}

static inline void DiagFailedReset(void)
{
	ESMREGS->ESMEKR = 0xAU;  			/* Force error pin for safety */
	systemREG1->SYSECR |= 0x00008000U;
	asm(" B $");
}

static void resetStartup(uint32 MemInitMask_Cnt_T_u32)
{
	setupPLL();
	periphInit();
	setupFlash();
	trimLPO();
	mapClocks();

	memInitialization(MemInitMask_Cnt_T_u32);
}
static inline void pwronStartup(void)
{
/***************************** INITIALIZATION STEP 07 *****************************/
	/* Check if there were ESM group3 errors during power-up.
	 * These could occur during eFuse auto-load or during reads from flash OTP
	 * during power-up. Device operation is not reliable and not recommended
	 * in this case.
	 * An ESM group3 error only drives the nERROR pin low. An external circuit
	 * that monitors the nERROR pin must take the appropriate action to ensure that
	 * the system is placed in a safe state, as determined by the application.
	 */
	if (0 != ESMREGS->ESMSR3)
	{
		ResetCause_Cnt_Enum = ESM3NONZERO;
		DiagFailedReset();
	}
/***************************** INITIALIZATION STEP 08 *****************************/
/***************************** INITIALIZATION STEP 09 *****************************/
	/* Configure PLL control registers and enable PLLs.
	 * The PLL takes (127 + 1024 * NR) oscillator cycles to acquire lock.
	 * This initialization sequence performs all the tasks that are not
	 * required to be done at full application speed while the PLL locks.
	 */
	setupPLL();

/***************************** INITIALIZATION STEP 10 *****************************/
	/* Run eFuse controller start-up checks and start eFuse controller ECC self-test.
	 * This includes a check for the eFuse controller error outputs to be stuck-at-zero.
	 */
	efcCheck();

/***************************** INITIALIZATION STEP 11 *****************************/
	/* Enable clocks to peripherals and release peripheral reset */
	periphInit();

/***************************** INITIALIZATION STEP 12 *****************************/
	/* Configure device-level multiplexing and I/O multiplexing */
	/* Intentionally skipped... done in Port Init function in application */

/***************************** INITIALIZATION STEP 13 *****************************/
	/* Wait for eFuse controller self-test to complete and check results */
	if (FALSE == checkEFCSelfTestPassed())							/* eFuse controller ECC logic self-test failed */
	{
		ResetCause_Cnt_Enum = EFCSTFAILED;
		DiagFailedReset();
	}

/***************************** INITIALIZATION STEP 14 *****************************/
/***************************** INITIALIZATION STEP 15 *****************************/
	/* Set up flash address and data wait states based on the target CPU clock frequency
	 * The number of address and data wait states for the target CPU clock frequency are specified
	 * in the specific part's datasheet.
	 */
	setupFlash();

/***************************** INITIALIZATION STEP 16 *****************************/
	/* Configure the LPO such that HF LPO is as close to 10MHz as possible */
	trimLPO();

/***************************** INITIALIZATION STEP 17 *****************************/
	/* Check if there was an ESM error from FMC OTP read during power-up */
	fmcBus2Check();

/***************************** INITIALIZATION STEP 18 *****************************/
	/* Wait for PLLs to start up and map clock domains to desired clock sources */
	mapClocks();

/***************************** INITIALIZATION STEP 21 *****************************/
	/* Make sure that the CPU self-test controller can actually detect a fault inside CPU */
	stcSelfCheck();

}
static inline void afterSTC(void)
{
	uint32 SpRamGrpStms_Cnt_T_u32;

/***************************** INITIALIZATION STEP 23 *****************************/
	/* Make sure that CCM-R4F is working as expected.
	 * This function puts the CCM-R4F module through its self-test modes.
	 * It ensures that the CCM-R4F is indeed capable of detecting a CPU mismatch,
	 * and is also capable of indicating a mismatch error to the ESM.
	 */
	ccmSelfCheck();


/***************************** INITIALIZATION STEP 24 *****************************/
    /* Work Around for Errata PBIST#4:
     *
     * Errata Description:
     *            PBIST ROM Algorithm might not execute after a cold power-on
     * Workaround:
     *            Initialize the ROM before using it */
    errata_PBIST_4();

    /* Run a diagnostic check on the memory self-test controller.
     * This function chooses a RAM test algorithm and runs it on an on-chip ROM.
     * The memory self-test is expected to fail. The function ensures that the PBIST controller
     * is capable of detecting and indicating a memory self-test failure.
     */
    pbistSelfCheck();

    /* Run PBIST on ROM.
     * The PBIST controller needs to be configured separately for ROMs.
     * The actual "RAM Group" for all on-chip ROMs is defined in the device datasheet.
     */
    pbistRun(0x00000003U, (uint32)0x2); /* PBIST and STC ROM*/

    /* Wait for PBIST for ROM to be completed */
	while (0 == (systemREG1->MSTCGSTAT & 0x1));

	/* Check if ROM passed the self-test */
	if ((0 != pbistREG->FSRF0) || (0 != pbistREG->FSRF1))
	{
		/* ROM failed the self-test. */
		ResetCause_Cnt_Enum = SPPBISTFAILED;
		DiagFailedReset();
	}

	/* Disable PBIST clocks and disable memory self-test mode */
	pbistStop();

/***************************** INITIALIZATION STEP 25, 32**************************/
	/* Run PBIST on Single Port RAM */
	SpRamGrpStms_Cnt_T_u32 = D_SPRAMGRPSTMS_CNT_U32;

	/*Ram Domain 1 corresponds to ES Ram 5*/
	if(TRUE == GetRamDomian1Enabled())
	{
		SpRamGrpStms_Cnt_T_u32 |= D_ESRAM5ENABLE_CNT_U32;
	}
	else
	{
		SpRamGrpStms_Cnt_T_u32 &= ~D_ESRAM5ENABLE_CNT_U32;
	}

	/*Ram Domain 2 corresponds to ES Ram 6*/
	if(TRUE == GetRamDomian2Enabled())
	{
		SpRamGrpStms_Cnt_T_u32 |= D_ESRAM6ENABLE_CNT_U32;
	}
	else
	{
		SpRamGrpStms_Cnt_T_u32 &= ~D_ESRAM6ENABLE_CNT_U32;
	}

	/*Ram Domain 3 corresponds to ES Ram 8*/
	if(TRUE == GetRamDomian3Enabled())
	{
		SpRamGrpStms_Cnt_T_u32 |= D_ESRAM8ENABLE_CNT_U32;
	}
	else
	{
		SpRamGrpStms_Cnt_T_u32 &= ~D_ESRAM8ENABLE_CNT_U32;
	}

	pbistRun(SpRamGrpStms_Cnt_T_u32, D_SPRAMSELECT_CNT_U32);

/***************************** INITIALIZATION STEP 33 ****************************/
	/* Wait for PBIST for SP RAM to be completed */
	while (0 == (systemREG1->MSTCGSTAT & 0x1));

	/* Check if SP RAM passed the self-test */
	if ((0 != pbistREG->FSRF0) || (0 != pbistREG->FSRF1))
	{
		/* SP RAM failed the self-test. */
		ResetCause_Cnt_Enum = SPPBISTFAILED;
		DiagFailedReset();
	}

	/* Disable PBIST clocks and disable memory self-test mode */
	pbistStop();

/***************************** INITIALIZATION STEP 28 *****************************/
	pbistRun(D_DPRAMGRPSTMS_CNT_U32, D_DPRAMSELECT_CNT_U32);

/***************************** INITIALIZATION STEP 31 ****************************/
	/* Wait for PBIST for DP RAM to be completed */
	while (0 == (systemREG1->MSTCGSTAT & 0x1));

	/* Check if DP RAM passed the self-test */
	if ((0 != pbistREG->FSRF0) || (0 != pbistREG->FSRF1))
	{
		/* Dual Port RAM failed the self-test. */
		ResetCause_Cnt_Enum = DPPBISTFAILED;
		DiagFailedReset();
	}

	/* Disable PBIST clocks and disable memory self-test mode */
	pbistStop();
	ResetCause_Cnt_Enum = PWRONRESET;

	memInitialization(D_RAMPWRONINITMASKTMS_CNT_U32);
}

static inline void memInitialization(uint32 MemInitMask_Cnt_T_u32)
{
	#if (DCAN3MEM_PWRENABLE == STD_ON)
		DCAN3REG->CTL = 0x00002800;
	#endif

	#if (DCAN2MEM_PWRENABLE == STD_ON)
		DCAN2REG->CTL = 0x00002800;
	#endif

	#if (DCAN1MEM_PWRENABLE == STD_ON)
		DCAN1REG->CTL = 0x00002800;
	#endif

	#if (DMAMEM_INIT == STD_ON)
		DMACTRLREG->DMAPCR = 0x0Aul;	/* enable parity */
		DMACTRLREG->GCTRL = 1ul << 16;	/* enable DMA */
	#endif
	_memoryInit_(MemInitMask_Cnt_T_u32);

/***************************** INITIALIZATION STEP 27 *****************************/
	/* Enable ECC checking for TCRAM accesses.
	 * This function enables the CPU's ECC logic for accesses to B0TCM and B1TCM.
	 */
	_coreEnableRamEcc_();

	VIM->INTREQ0 = 0xFFFFFFFFU;
	VIM->INTREQ1 = 0xFFFFFFFFU;
	VIM->INTREQ2 = 0xFFFFFFFFU;
	VIM->INTREQ3 = 0xFFFFFFFFU;

	BootStartup();
}

static inline void cpuSelfTest(void)
{
	volatile uint8 i;

	stcREG->STCGCR0 = 0x00180001;						/* Run all 24 test intervals starting from interval 0 */

	for (i=0; i<16; i++);								/* wait for 16 VBUS clock cycles at least */

	stcREG->STCGCR1 = 0xA;								/* Enable self-test */

	asm("	WFI");										/* Idle the CPU so that the self-test can start */
	asm("	NOP");
	asm("	NOP");
}

static inline void setupPLL(void)
{

	if ((systemREG1->GBLSTAT & D_PLLSLIPMASK_CNT_U32) != 0x00000000)
	{  /* PLL Recovery */
		systemREG1->GBLSTAT = D_PLLSLIPMASK_CNT_U32; /* clear Glbstat slip bits */
		ESMREGS->ESMSR1 |= 0x400 ; /* clear ESM Stat1 bit 10 */
	}


    /* Configure PLL control registers */
    systemREG1->PLLCTL1 = D_PLLCTL1VAL_CNT_U32;
    systemREG1->PLLCTL2 = D_PLLCTL2VAL_CNT_U32;
    systemREG2->PLLCTL3 = 0x7F055F00;

	/* Enable PLL(s) to start up */
	systemREG1->CSDISCLR = D_CSDISCLRVAL_CNT_U32;
}

static inline void efcCheck(void)
{
	if (efcREG->ERROR == 0x0)
	{
		if (TRUE == efcStuckZeroTestPassed())						/* run stuck-at-zero test and check if it passed */
		{
			efcSelfTest();							/* start EFC ECC logic self-test */
		}
		else
		{
			ResetCause_Cnt_Enum = EFCSTUCKZERO;
			DiagFailedReset();
		}
	}
	else											/* EFC Error Register is not zero */
	{
		if (efcREG->ERROR == 0x15)						/* one-bit error detected during autoload */
		{
			efcSelfTest();							/* start EFC ECC logic self-test */
		}
		else
		{
			ResetCause_Cnt_Enum = EFCERROR;
			DiagFailedReset();
		}
	}
}

static inline boolean efcStuckZeroTestPassed(void)
{
	boolean TestPassed_Cnt_T_lgc = FALSE;

	/* configure the output enable for auto load error , instruction info,
  	   instruction error, and self test error using boundary register
  	   and drive values one across all the errors */
  	efcREG->BOUNDARY = (D_OUTPUTENABLE_CNT_U32 | D_EFCINSTRUCTIONINFOEN_CNT_U32 | D_EFCINSTRUCTIONERROREN_CNT_U32 | D_EFCAUTOLOADERROREN_CNT_U32 | D_EFCSELFTESTERROREN_CNT_U32);

	/* Read from the pin register. This register holds the current values
  	   of above errors. This value should be 0x5c00.If not at least one of
  	   the above errors is stuck at 0. */
	if ((efcREG->PINS & 0x5C00) == 0x5C00)
	{
		/* check if the ESM group1 channels 40 is set and group3 channel 2 is set */
		if (((ESMREGS->ESTATUS4[0] & 0x200) == 0x200) && ((ESMREGS->ESMSR3 & 0x2) == 0x2))
		{
			TestPassed_Cnt_T_lgc = TRUE;									/* stuck-at-zero test passed */
		}
	}
	/* put the pins back low */
	efcREG->BOUNDARY = D_OUTPUTENABLE_CNT_U32;
	ESMREGS->ESTATUS4[0] = 0x300;				/* clear group1 flags */
	ESMREGS->ESMSR3 = 0x2;					/* clear group3 flag */
	ESMREGS->ESMEKR = 0x5;							/* The nERROR pin will become inactive once the LTC counter expires */

	return TestPassed_Cnt_T_lgc;
}

static inline void efcSelfTest(void)
{
	/* configure self-test cycles */
	efcREG->SELF_TEST_CYCLES = 0x258;

	/* configure self-test signature */
	efcREG->SELF_TEST_SIGN = 0x5362F97F;

	/* configure boundary register to start ECC self-test */
	efcREG->BOUNDARY = 0x0000200F;
}

static inline void periphInit(void)
{
	/* Release peripherals from reset and enable clocks to all peripherals */
    /* - Power-up all peripherals */
    pcrREG->PSPWRDWNCLR0 = D_PSPWRDWNCLR0VAL_CNT_U32;
    pcrREG->PSPWRDWNCLR1 = D_PSPWRDWNCLR1VAL_CNT_U32;
    pcrREG->PSPWRDWNCLR2 = D_PSPWRDWNCLR2VAL_CNT_U32;
    pcrREG->PSPWRDWNCLR3 = D_PSPWRDWNCLR3VAL_CNT_U32;

    pcrREG->PCSPWRDWNCLR0 = D_PCSPWRDWNCLR0VAL_CNT_U32;
    pcrREG->PCSPWRDWNCLR1 = D_PCSPWRDWNCLR1VAL_CNT_U32;

    /* Enable Peripherals */
    systemREG1->PENA = 1U;
}

static inline boolean checkEFCSelfTestPassed(void)
{
	boolean TestPassed_Cnt_T_lgc = FALSE;
	/* wait until EFC self-test is done */
	while(0 == (efcREG->PINS & D_EFCSELFTESTDONE_CNT_U32));

	/* check if EFC self-test error occurred */
	if ((0 == (efcREG->PINS & D_EFCSELFTESTERROR_CNT_U32)) && (0 == (efcREG->ERROR & D_SELFTESTERROR_CNT_U32)))
	{
		if ((ESMREGS->ESTATUS4[0] & 0x100) != 0x100)		/* check if EFC self-test error is set */
		{
			TestPassed_Cnt_T_lgc = TRUE;
		}
	}
	return TestPassed_Cnt_T_lgc;
}

static inline void setupFlash(void)
{
    /* Setup flash read mode, address wait states and data wait states */
    flashWREG->FRDCNTL =  D_FRDCNTLVAL_CNT_U32;

    /*############################ ERRATA DEVICE#145 WORKAROUND ############################*/
	/* Implement work-around for Cold Temp Flash Errors issue on silicon revision A */
	if (systemREG1->DEV == 0x802AAD05)
	{
		flashWREG->FSPRD = 0x00010000; /* Disable pre-emption */
	}

    /* Setup flash access wait states for bank 7 */
	flashWREG->FSM_WR_ENA = 0x5;
	flashWREG->EEPROM_CONFIG = 0x00030002;

    /* Disable write access to flash state machine registers */
	flashWREG->FSM_WR_ENA = 0xA;

	/* We are leaving the flash banks' and pump's fall-back mode as ACTIVE */
	/* This needs to be changed for any application that wants to turn off any unused flash bank */

    /* TODO: Turn off fall-back mode on flash banks we may want to turn off.  Special code for different devices needed?? */
}

static inline void trimLPO(void)
{
	volatile uint32 LPOTrimOTPValue_Cnt_T_u32;
	volatile uint32 CurrentTrim_Cnt_T_u32;
	volatile uint32 CurrLowFrqTrim_Cnt_T_u32;
	volatile uint32 CurrHighFrqTrim_Cnt_T_u32;
	volatile uint32 AdjCurrHighFrqTrim_Cnt_T_u32;
	volatile uint32 OTPLowFrqTrim_Cnt_T_u32;
	volatile uint32 OTPHighFrqTrim_Cnt_T_u32;
	volatile uint32 CurrentLPOMONCTL_Cnt_T_u32;

	LPOTrimOTPValue_Cnt_T_u32 = D_LPOTRIMVALUE_CNT_U32;
	CurrentLPOMONCTL_Cnt_T_u32 = systemREG1->LPOMONCTL;

    /* Configure LPO */
    /* Load TRIM values from OTP if present else load user defined values */
    if (LPOTrimOTPValue_Cnt_T_u32 != 0xFFFFU)
    {
    	CurrentTrim_Cnt_T_u32 = CurrentLPOMONCTL_Cnt_T_u32 & D_CURRENTLPOTRIMMASK_CNT_U32;

        CurrLowFrqTrim_Cnt_T_u32 = CurrentTrim_Cnt_T_u32 & D_LOWBYTEMASK_CNT_U32;
        CurrHighFrqTrim_Cnt_T_u32 = (CurrentTrim_Cnt_T_u32 >> 8u) & D_LOWBYTEMASK_CNT_U32;

        OTPLowFrqTrim_Cnt_T_u32 = LPOTrimOTPValue_Cnt_T_u32 & D_LOWBYTEMASK_CNT_U32;
        OTPHighFrqTrim_Cnt_T_u32 = (LPOTrimOTPValue_Cnt_T_u32 >> 8u) & D_LOWBYTEMASK_CNT_U32;

        while( OTPLowFrqTrim_Cnt_T_u32 != CurrLowFrqTrim_Cnt_T_u32)
        {
        	if (OTPLowFrqTrim_Cnt_T_u32 > CurrLowFrqTrim_Cnt_T_u32)
        	{
        		CurrLowFrqTrim_Cnt_T_u32++;
        	}
        	else
        	{
        		CurrLowFrqTrim_Cnt_T_u32--;
        	}

        	CurrentTrim_Cnt_T_u32 = ((CurrentTrim_Cnt_T_u32 & D_LPOMONLFTRIMMASK_CNT_U32) |  CurrLowFrqTrim_Cnt_T_u32);

        	systemREG1->LPOMONCTL  = ((1U << 24U) | CurrentTrim_Cnt_T_u32);
        	Delay();
        }

        while( OTPHighFrqTrim_Cnt_T_u32 != CurrHighFrqTrim_Cnt_T_u32)
        {
        	if (OTPHighFrqTrim_Cnt_T_u32 > CurrHighFrqTrim_Cnt_T_u32)
        	{
        		CurrHighFrqTrim_Cnt_T_u32++;
        	}
        	else
        	{
        		CurrHighFrqTrim_Cnt_T_u32--;
        	}

        	AdjCurrHighFrqTrim_Cnt_T_u32 = ((CurrHighFrqTrim_Cnt_T_u32 << 8u) & ~D_LPOMONHFTRIMMASK_CNT_U32);

        	CurrentTrim_Cnt_T_u32 = ((CurrentTrim_Cnt_T_u32 & D_LPOMONHFTRIMMASK_CNT_U32) |  AdjCurrHighFrqTrim_Cnt_T_u32);

        	systemREG1->LPOMONCTL  = ((1U << 24U) | CurrentTrim_Cnt_T_u32);
        	Delay();
        }
    }
    else
    {
    	if (PWRONRESET == ResetCause_Cnt_Enum)
    	{
    		ResetCause_Cnt_Enum = LPOTRIMERROR;
    		DiagFailedReset();
    	}
    }
}

static inline void fmcBus2Check(void)
{
	flashWREG->FEDACCTRL1 = 0x000A060A;		/* enable ECC logic inside FMC */
	ESMREGS->ESMSR1 = 0x40;				/* clear ESM group1 channel 6 flag if present (1 bit ECC error) */
	fmcECCcheck();

}

static inline void fmcECCcheck(void)
{
	volatile uint32 otpread_Cnt_T_u32;

	otpread_Cnt_T_u32 = *(volatile uint32*)D_OTP1BITERRADDR_CNT_U32;				/* read location with deliberate 1-bit error */
	if (0 != (ESMREGS->ESMSR1 & 0x40))
	{
		if (otpread_Cnt_T_u32 != 0x9ABCDEF0U)
		{		
			ResetCause_Cnt_Enum = FLSBUS2CORRFAILED;	/* ECC logic inside FMC cannot correct 1-bit error (Nexteer Added) */
			DiagFailedReset();
		}
		/* 1-bit failure was indicated and corrected */
		flashWREG->FEDACSTATUS = 0x00010006;
		ESMREGS->ESMSR1 = 0x40;			/* clear ESM group1 channel 6 flag */

		otpread_Cnt_T_u32 = *(volatile uint32*)D_OTP2BITERRADDR_CNT_U32;			/* read location with deliberate 2-bit error */
		if (0 != (ESMREGS->ESMSR3 & 0x80))
		{
			/* 2-bit failure was detected correctly */
			if (flashWREG->FUNCERRADD != 0xF00803F8)
			{			
				ResetCause_Cnt_Enum = FLSBUS2ADDCAPFAILED; /* Error Address not captured for 2-bit error (Nexteer Added) */
				DiagFailedReset();
			}

			flashWREG->FEDACSTATUS = 0x00020100;
			ESMREGS->ESMSR3 = 0x80;		/* clear ESM group3 channel 7 */
			ESMREGS->ESMEKR = 0x5;				/* The nERROR pin will become inactive once the LTC counter expires */

		}
		else
		{				
			ResetCause_Cnt_Enum = FLSBUS2MULBITDETFAILED;	/* ECC logic inside FMC cannot detect 2-bit error */
			DiagFailedReset();
		}
	}
	else
	{			
		ResetCause_Cnt_Enum = FLSBUS2SNGBITDETFAILED;	/* ECC logic inside FMC cannot detect 1-bit error */
		DiagFailedReset();
	}
}

static inline void mapClocks(void)
{
    /* Setup synchronous peripheral clock dividers for VCLK1, VCLK2, VCLK3 */
    systemREG1->VCLKR   = 1U;
    systemREG1->VCLK2R  = 1U;
    systemREG2->VCLK3R  = 1U;

	/* Wait for PLL(s) to acquire lock and become available */
	while ((systemREG1->CSVSTAT & D_CSVSTATMASK_CNT_U32) != D_CSVSTATMASK_CNT_U32);

	/* Map device clock domains to desired sources and configure top-level dividers */
	/* All clock domains are working off the default clock sources until now */
	/* The below assignments can be easily modified using the HALCoGen GUI */

    /* Setup GCLK, HCLK and VCLK clock source for normal operation, power down mode and after wakeup */
    systemREG1->GHVSRC = (SYS_PLL1 << 24U)
                       | (SYS_PLL1 << 16U)
                       |  SYS_PLL1;

    /* Setup synchronous peripheral clock dividers for VCLK1, VCLK2, VCLK3 */
    systemREG1->VCLKR   = 1U;
    systemREG1->VCLK2R  = 1U;
    systemREG2->VCLK3R  = 1U;

    /* Setup RTICLK */
    systemREG1->RCLKSRC = SYS_VCLK;

    /* Setup asynchronous peripheral clock sources for AVCLK1 and AVCLK2 */
    systemREG1->VCLKASRC = (SYS_PLL2 << 8U)
                          |  SYS_VCLK;

    systemREG2->VCLKACON1 = (SYS_VCLK << 16);

	/* Now the PLLs are locked and the PLL outputs can be sped up */
	/* The R-divider was programmed to be 0xF. Now this divider is changed to 0 */

    /* TODO: Should we be doing this in steps per the initialization document? */
	systemREG1->PLLCTL1 &= 0xE0FFFFFF;
	systemREG2->PLLCTL3 &= 0xE0FFFFFF;
}

static inline void stcSelfCheck(void)
{
	volatile uint8 i;

	/* Run a diagnostic check on the CPU self-test controller */
	/* First set up the STC clock divider as STC is only supported up to 90MHz... we are running at 80MHz */
	systemREG2->STCCLKDIV = 0x01000000;					/* STC clock is now normal mode CPU clock frequency/2 = 160MHz/2 */
	stcREG->STCGCR0 = 0x00010001;						/* Select one test interval, restart self-test next time, 0x00010001 */
	stcREG->STCSCSCR = 0x1A;							/* Enable comparator self-check and stuck-at-0 fault insertion in CPU, 0x1A */
	stcREG->STCTPR = 0xFFFFFFFF;						/* Maximum time-out period */

	for (i=0; i<16; i++);								/* wait for 16 VBUS clock cycles at least */

	stcREG->STCGCR1 = 0xA;								/* Enable self-test */

	for (i=0; i<16; i++);								/* wait for 16 VBUS clock cycles at least */

	asm("	WFI");										/* Idle the CPU so that the self-test can start */
	asm("	NOP");
	asm("	NOP");
	asm("	NOP");
	asm("	NOP");
}

static inline void ccmSelfCheck(void)
{
	/* Run a diagnostic check on the CCM-R4F module */
	/* This step ensures that the CCM-R4F can actually indicate an error */

	CCMREG->CCMKEYR = 0x6;								/* Configure CCM in self-test mode */
	while ((CCMREG->CCMSR & 0x100) != 0x100);			/* Wait for CCM self-test to complete */

	/* Check if there was an error during the self-test */
	if ((CCMREG->CCMSR & 0x1) == 0x1)
	{
		ResetCause_Cnt_Enum = CCMSTFAILED;
		DiagFailedReset();
		/* CCM-R4 is not able to flag a compare error in self-test mode.
		 * Lock-step operation cannot be verified.
		 */
	}
	else
	{
		/* Check CCM-R4 self-test error flag by itself (without compare error) */
		CCMREG->CCMKEYR = 0xF;						/* Configure CCM in self-test error-forcing mode */
		if ((ESMREGS->ESMSR1 & 0x80000000) != 0x80000000)
		{
			ResetCause_Cnt_Enum = CCMSTEFFAILED;
			DiagFailedReset();
			/* CCM-R4 self-test error flag is not set in ESM register.
			 * Could be due to a connection issue inside the part.
			 */
		}
		else
		{
			ESMREGS->ESMSR1 = 0x80000000;	/* clear ESM group1 channel 31 flag */

			CCMREG->CCMKEYR = 0x9;						/* Configure CCM in error-forcing mode */
			if ((ESMREGS->ESMSR2 & 0x4) != 0x4)		/* check if compare error flag is set */
			{
				ResetCause_Cnt_Enum = CCMEFFAILED;
				DiagFailedReset();
				/* CCM-R4 compare error flag is not set in ESM.
				 * Lock-step operation cannot be verified.
				 */
			}
			else
			{
				ESMREGS->ESMSR2 = 0x4;				/* clear ESM group2 channel 2 flag */
				ESMREGS->ESTATUS5EMU = 0x4;				/* clear ESM group2 shadow status flag */
				ESMREGS->ESMSR1 = 0x80000000;		/* ESM self-test error needs to also be cleared */

				/* Clear CCM-R4 CMPE flag */
				CCMREG->CCMSR = 0x00010000;  

				/* Return CCM-R4 to lock-step mode */
				CCMREG->CCMKEYR = 0x0;

				ESMREGS->ESMEKR = 0x5;						/* The nERROR pin will become inactive once the LTC counter expires */
			}
		}
	}
}

static inline void pbistSelfCheck(void)
{
    volatile uint32 i = 0U;
    uint32 PBIST_FSRF0, PBIST_FSRF1, PBIST_wait_done_loop = 0U;

    /* Run a diagnostic check on the memory self-test controller */
    /* First set up the PBIST ROM clock as this clock frequency is limited to 90MHz */

    /* Disable PBIST clocks and ROM clock */
    pbistREG->PACT = 0x0U;
    
    /* PBIST ROM clock frequency = HCLK frequency /2 */
    /* Disable memory self controller */
    systemREG1->MSTGCR = 0x00000105U;                
    
    /* Disable Memory Initialization controller */
    systemREG1->MINITGCR = 0x5U;

    /* Enable memory self controller */
    systemREG1->MSTGCR = 0x0000010AU;                               

    /* Clear PBIST Done */
    systemREG1->MSTCGSTAT = 0x1U;
    
    /* Enable PBIST controller */
    systemREG1->MSINENA = 0x1U;

    /* wait for 32 VBUS clock cycles at least, based on HCLK to VCLK ratio */
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Wait for few clock cycles (Value of i not used)" */
	/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Wait for few clock cycles (Value of i not used)" */
    for (i=0U; i<(32U + (32U * 1U)); i++){ /* Wait */ }


    /* Enable PBIST clocks and ROM clock */
    pbistREG->PACT = 0x3U;

    /* CPU control of PBIST */
    pbistREG->DLR = 0x10U;

    /* Custom always fail algo, this will not use the ROM and just set a fail */
    pbistREG->RAMT         = 0x00002000U;
    *(volatile uint32 *)0xFFFFE400U = 0x4C000001U;
    *(volatile uint32 *)0xFFFFE440U = 0x00000075U;
    *(volatile uint32 *)0xFFFFE404U = 0x4C000002U;
    *(volatile uint32 *)0xFFFFE444U = 0x00000075U;
    *(volatile uint32 *)0xFFFFE408U = 0x4C000003U;
    *(volatile uint32 *)0xFFFFE448U = 0x00000075U;
    *(volatile uint32 *)0xFFFFE40CU = 0x4C000004U;
    *(volatile uint32 *)0xFFFFE44CU = 0x00000075U;
    *(volatile uint32 *)0xFFFFE410U = 0x4C000005U;
    *(volatile uint32 *)0xFFFFE450U = 0x00000075U;
    *(volatile uint32 *)0xFFFFE414U = 0x4C000006U;
    *(volatile uint32 *)0xFFFFE454U = 0x00000075U;
    *(volatile uint32 *)0xFFFFE418U = 0x00000000U;
    *(volatile uint32 *)0xFFFFE458U = 0x00000001U;

    /* PBIST_RUN */
    pbistREG->rsvd1[1U]    = 1U;

    /* wait until memory self-test done is indicated */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
    while ((systemREG1->MSTCGSTAT & 0x1U) != 0x1U) 
    {
        PBIST_wait_done_loop++;
    }/* Wait */

    /* Check for the failure */
    PBIST_FSRF0 = pbistREG->FSRF0;
    PBIST_FSRF1 = pbistREG->FSRF1;
    if (((PBIST_FSRF0 & 0x1U) != 0x1U) && ((PBIST_FSRF1 & 0x1U) != 0x1U))
    {
        /* No failure was indicated even if the always fail algorithm was run*/
		ResetCause_Cnt_Enum = PBISTSCFAILED;
		DiagFailedReset();
		/* The PBIST controller is not capable of reporting a failure.
		 * PBIST cannot be used to verify memory integrity.
		 */
    }
    else
    {
        /* Check that the algorithm executed in the expected amount of time. */
        /* This time is dependent on the ROMCLKDIV selected above            */
        if (PBIST_wait_done_loop >= 2U)
        {
			/* no failure was indicated even if the march13n algorithm was run on a ROM */
			ResetCause_Cnt_Enum = PBISTSCFAILED;
			DiagFailedReset();
			/* The PBIST controller is not capable of reporting a failure.
			 * PBIST cannot be used to verify memory integrity.
			 */
        }
        
        /* Disable PBIST clocks and ROM clock */
        pbistREG->PACT = 0x0U;

        /* Disable PBIST */
        systemREG1->MSTGCR &= 0xFFFFFFF0U;
        systemREG1->MSTGCR |= 0x5U;

    }
}


static inline void pbistRun(uint32 raminfoL, uint32 algomask)
{
	volatile uint8 i;
	systemREG1->MSTGCR = 0x00000105U;					/* PBIST ROM clock frequency = HCLK frequency /2 Disable memory self controller*/
	systemREG1->MINITGCR = 0x5;							/* Disable Memory Initialization controller*/
	systemREG1->MSTGCR = 0x0000010AU;					/* Enable memory self controller */
    systemREG1->MSTCGSTAT = 0x1U;                       /* Clear PBIST Done */
	systemREG1->MSINENA = 0x1U;							/* Enable PBIST controller */

	for (i = 0; i < 32; i++);							/* software loop to wait at least 32 VCLK cycles */

	pbistREG->PACT = 0x3;								/* Enable PBIST clocks and ROM clock */
	pbistREG->ALGO = algomask;							/* Select all algorithms to be tested */
	pbistREG->RINFOL = raminfoL;						/* Select RAM groups */
	pbistREG->RINFOU = 0x00000000;						/* Select all RAM groups */
	pbistREG->OVER = 0x0;								/* ROM contents will not override RINFOx settings */
	pbistREG->ROM = 0x3;								/* Algorithm code is loaded from ROM */
	pbistREG->DLR = 0x14;								/* Start PBIST */
}

static inline void pbistStop(void)
{
	pbistREG->PACT = 0x0;							/* disable pbist clocks and ROM clock */
	systemREG1->MSTGCR &= ~(0xF);
	systemREG1->MSTGCR |= 0x5;
}

static inline void Delay(void)
{
	uint16 i;

	for (i=0; i<20; i++)
	{
		asm("	NOP");
	}
}

/** @fn void errata_PBIST_4(void)
*   @brief Workaround for the Errata PBIST#4.
*
*   This function is workaround for Errata PBIST#4.
*   This function is designed to initialize the ROMs using the PBIST controller.
*   The CPU will configure the PBIST controller to test the PBIST ROM and STC ROM.
*   This function should be called at startup after system init before using the ROMs.
*/
static inline void errata_PBIST_4(void)
{
    volatile uint32 i = 0U;
    uint8 ROM_count;
    sint32 PBIST_wait_done_loop;
    uint32 pmuCalibration, pmuCount;

    /* PMU calibration */
    _pmuEnableCountersGlobal_();
    _pmuResetCounters_();
    _pmuStartCounters_(pmuCYCLE_COUNTER);
    _pmuStopCounters_(pmuCYCLE_COUNTER);
    pmuCalibration=_pmuGetCycleCount_();

    /* ROM_init Setup using special reserved registers as part of errata fix */
    /* (Only to be used in this function) */
    *(volatile uint32 *)0xFFFF0400U = 0x0000000AU;
    *(volatile uint32 *)0xFFFF040CU = 0x0000EE0AU;

    /* Loop for Executing PBIST ROM and STC ROM */
    for (ROM_count = 0U; ROM_count < 2U; ROM_count++)
    {
        PBIST_wait_done_loop = 0;
    
        /* Disable PBIST clocks and ROM clock */
        pbistREG->PACT = 0x0U;
        
        /* PBIST Clocks did not disable */
        if(pbistREG->PACT != 0x0U ) 
        {
			ResetCause_Cnt_Enum = PBISTSCFAILED;
			DiagFailedReset();
        }
        else
        {
            /* PBIST ROM clock frequency = HCLK frequency /2 */
            /* Disable memory self controller */
            systemREG1->MSTGCR = 0x00000105U;
            
            /* Disable Memory Initialization controller */
            systemREG1->MINITGCR = 0x5U;

            /* Enable memory self controller */
            systemREG1->MSTGCR = 0x0000010AU;                               

            /* Clear PBIST Done */
            systemREG1->MSTCGSTAT = 0x1U;
            
            /* Enable PBIST controller */
            systemREG1->MSINENA = 0x1U;

			/*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Wait for few clock cycles (Value of i not used)" */
	        /*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "Wait for few clock cycles (Value of i not used)" */	
            /* wait for 32 VBUS clock cycles at least, based on HCLK to VCLK ratio */
            for (i=0U; i<(32U + (32U * 1U)); i++){ /* Wait */ }

            /* Enable PBIST clocks and ROM clock */
            pbistREG->PACT = 0x3U;

            /* CPU control of PBIST */
            pbistREG->DLR = 0x10U;

            /* Load PBIST ALGO to initialize the ROMs */
            *(volatile uint32 *)0xFFFFE400U = 0x00000001U;
            *(volatile uint32 *)0xFFFFE440U = 0x00000025U;
            *(volatile uint32 *)0xFFFFE404U = 0x62400001U;
            *(volatile uint32 *)0xFFFFE444U = 0x00000004U;
            *(volatile uint32 *)0xFFFFE408U = 0x00068003U;
            *(volatile uint32 *)0xFFFFE448U = 0x00000000U;
            *(volatile uint32 *)0xFFFFE40CU = 0x00000004U;
            *(volatile uint32 *)0xFFFFE44CU = 0x00006860U;
            *(volatile uint32 *)0xFFFFE410U = 0x00000000U;
            *(volatile uint32 *)0xFFFFE450U = 0x00000001U;
            *(volatile uint32 *)0xFFFFE540U = 0x000003E8U;
            *(volatile uint32 *)0xFFFFE550U = 0x00000001U;
            *(volatile uint32 *)0xFFFFE530U = 0x00000000U;
            
			/* SELECT ROM */
            if (ROM_count == 1U)
            {   
                /* SELECT PBIST ROM */          
                *(volatile uint32 *)0xFFFFE520U = 0x00000002U;
                *(volatile uint32 *)0xFFFFE524U = 0x00000000U;
                pbistREG->RAMT                  = 0x01002008U;
            } 
            else
            {               
                /* SELECT STC ROM */    
                *(volatile uint32 *)0xFFFFE520U = 0xFFF0007CU;
                *(volatile uint32 *)0xFFFFE524U = 0x0A63FFFFU;
                pbistREG->RAMT                  = 0x02002008U;
            }

            /*  Setup using special reserved registers as part of errata fix */
            /*      (Only to be used in this function) */
            pbistREG->rsvd1[4U]    = 1U;
            pbistREG->rsvd1[0U]    = 3U;

            /* Start PMU counter */
			_pmuResetCounters_();
            _pmuStartCounters_(pmuCYCLE_COUNTER);

            /* PBIST_RUN */
            pbistREG->rsvd1[1U]    = 1U;

            /* wait until memory self-test done is indicated */
            /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Hardware status bit read check" */
            while ((systemREG1->MSTCGSTAT & 0x1U) != 0x1U) 
            {
            }/* Wait */

			/* Stop PMU counter */
            _pmuStopCounters_(pmuCYCLE_COUNTER);
			
			/* Get CPU cycle count */
            pmuCount =_pmuGetCycleCount_();
			
			/* Calculate PBIST test complete time in ROM Clock */
			/* 2 - Divide value ( Default is 2 in HALCoGen) */
			/* 1000 = 0x3E8 - Test Loop count in ROM Algorithm */
			pmuCount = pmuCount - pmuCalibration;
            PBIST_wait_done_loop = ((sint32)pmuCount/2) - 1000;

            /* Check PBIST status results (Address, Status, Count, etc...) */
            if ((pbistREG->FSRA0 | pbistREG->FSRA1 | pbistREG->FSRDL0 | pbistREG->rsvd3 |
                 pbistREG->FSRDL1 | pbistREG->rsvd4[0U] | pbistREG->rsvd4[1U]) != 0U)
            {
				ResetCause_Cnt_Enum = PBISTSCFAILED;
				DiagFailedReset();
            }

            /* Check that the algorithm executed in the expected amount of time. */
            /* This time is dependent on the ROMCLKDIV selected */
            if ((PBIST_wait_done_loop <= 20) || (PBIST_wait_done_loop >= 200) )
            {
				ResetCause_Cnt_Enum = PBISTSCFAILED;
				DiagFailedReset();
            }

            /* Disable PBIST clocks and ROM clock */
            pbistREG->PACT = 0x0U;

            /* Disable PBIST */
            systemREG1->MSTGCR &= 0xFFFFFFF0U;
            systemREG1->MSTGCR |= 0x5U;
        }
    } /* ROM Loop */

    /* ROM restore default setup */
    /* (must be completed before continuing) */
    *(volatile uint32 *)0xFFFF040CU = 0x0000AA0AU;
    *(volatile uint32 *)0xFFFF040CU = 0x0000AA05U;
	*(volatile uint32 *)0xFFFF0400U = 0x00000005U;

	_pmuDisableCountersGlobal_();
}




