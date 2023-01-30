/*****************************************************************************
* Copyright 2015 Nexteer 
* Nexteer Confidential
*
* Module File Name  : Nhet.c
* Module Description: NHET PWM Driver
* Product           : Gen II Plus - EA3.0
* Author            : Selva Sengottaiyan
*****************************************************************************
* Version Control:
* %version:          7 %
* %derived_by:       nz63rn %
*---------------------------------------------------------------------------------------------------------------------
* Date      Rev      Author         Change Description                                                        SCR #
* -------   -------  --------  ---------------------------------------------------------------------------  ----------
* 02/01/13  1        Selva     Initial version for ePWM
* 07/29/13  2        OT        Implemented FDD 34B v003
* 08/01/13  3        Selva     Deleted  NHETPINDIS  in HET0                                                    CR9346
* 04/07/14  4        Selva    Implemented  FDD34B v 005														CR11062
* 04/23/14  5        SB        Anomaly fix 6589 - Correct the value for the HTU MP0E register 					 11799
* 11/26/14  6        VT        Anomaly fix 6844                                                                 12747
* 01/25/15  7        KMC       Updated to ES-34B v008; includes fix for anomaly 6488; re-ordered              CR12869
*                              code in Nhet_Init1 so that all initialization of each Nhet is complete
*							   before enabling the Nhet.
******************************************************************************/

/******************************************************************************
 *  INCLUDES
 ******************************************************************************/

#define  HTUDATATRQ
#include "Nhet.h"
#include <string.h> /* provide memset() and memcpy() definitions */

/*User Code Header - Start */
#include "htu_regs.h"
#include "Nhet_SENT_Prog.h"					
#include "CalConstants.h"
#include "ePWM_Cfg.h"

/* PRQA S 303 EOF 
 * MISRA-C:2004 Rule 11.3: This deviation is required for register access.  The rule is suppressed for the entire file */

/* PRQA S 312 EOF 
 * MISRA-C:2004 Rule 11.5: This deviation is required for memcpy of the NHET code into the NHETs.  The rule is suppressed for the entire file */

/* MISRA-C:2004 Rule 19.1: This deviation is required for AUTOSAR memory map requirements.  Rule suppressed by line at each occurrence. */
 
/*----------------------------------------------------------------------------*/
/* Global variables                                                           */
/*----------------------------------------------------------------------------*/
#define D_BASEADDNHETRAM_CNT_U32  0xFF460000UL
#define D_INSTTODATARATIO_CNT_U16	4U	/* instructions are 16 byte aligned, data field is 4 bytes.  Expressed as a ratio is 16/4 = 4*/
#define D_DATAFLDOFFSET_CNT_U16 	8U


#define D_WCAPHTUADDR1_CNT_U32 	(D_BASEADDNHETRAM_CNT_U32 + (uint32)(16U*(uint16)pHET_T1MSGCNTST_0) + 8UL)
													/* Need to define which instruction exactly is read from in NHET RAM */
													/* Be sure to count in bytes and include byte offset to DATA field */
													/* 0xff460000 is base address of HET RAM.  Only two options, NHET1, or NHET2 base address... */
													/* THe "16" is length in bytes of each HET instruction.  Never changes */
													/* The "54" is the instruction number to access with HTU, starting from 0 */
													/* the "8" is the byte offset to get the data field, this could change if you access control field... */

#define D_WCAPHTUADDR2_CNT_U32 	(D_BASEADDNHETRAM_CNT_U32 +(uint32)(16U*(uint16)pHET_T2MSGCNTST_0) + 8UL)
													/* Need to define which instruction exactly is read from in NHET RAM  */
													/* Be sure to count in bytes and include byte offset to DATA field */
													/* 0xff460000 is base address of HET RAM.  Only two options, NHET1, or NHET2 base address...*/
													/* THe "16" is length in bytes of each HET instruction.  Never changes*/
													/* The "83" is the instruction number to access with HTU, starting from 0*/
													/* the "8" is the byte offset to get the data field, this could change if you access control field...*/

#define D_CELEMENT_CNT_U16	8U							
													/* Number of elements (words) to transfer in a single event */
#define D_CFRAME_CNT_U16		(D_CBUFLEN_CNT_U16/D_CELEMENT_CNT_U16)		
												   /* Number of frame counts */

#define NHET_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

VAR(HtuDataTrq_Str, AUTOMATIC) volatile Nhet_HtuDataTrq_Cnt_G_str;
/* Main input capture circular buffer (for HTU transfers from HET RAM to main CPU RAM) */

#define NHET_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

#define NHET_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

/* global variable for peripheral startup diagnostic -- HTU1 failed to exit reset */
VAR(boolean, AUTOMATIC) Nhet_Htu1RstFail_Cnt_G_lgc;

#define NHET_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

STATIC INLINE FUNC(void, NHET_CODE) HTU1_Init(void);
/*User Code Header - End */

/*****************************************************************************
  * Name:        Nhet_Init1
  * Description: NHET primary initialization
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, NHET_CODE) Nhet_Init1(void)
{
	
/* Start initialization of NHET 1 Peripheral */
/* TI naming: NHET 1 registers named NHET0; NHET 2 registers named NHET1 */
	NHET0->NHETGCR =
		(1UL << 24U) |					/* 0: Enable output buffers */
		(1UL << 18U) |					/* 0: When NHET is running, program fields are read-only */
		(1UL << 17U) |					/* 1: NHET doesn't stop when a software breakpoint is encountered.*/
		(0UL << 16U) |					/* 1: NHET is slave */
		(0UL <<  0U);					/* 0: Stop NHET */
	
	if( (NHET0->NHETGCR & 0x1UL) == 0UL )
	{
		/* copy the HET0 program */
		(void) memcpy((void *) &e_HETPROGRAM0_UN, (const void *) HET_INIT0_PST, sizeof(HET_INIT0_PST));
		
		NHET0->NHETPFR =			/* Timer Prescale */
			(7UL << 8) |				/* 7 -> lr=128 */
			(0UL << 0);				/* 0 -> hr=1:  ts = 128*1 = 128 */
		
		NHET0->NHETPULDIS = 0UL;		/* Pull functionality enabled on all channels */
		NHET0->NHETPSL = 0UL;			/* All channels are set to pull down */
		
		NHET0->NHETSFPRLD =			/* Set suppression filter to 1.7us */
			(1UL << 18) |				/* Reserved */
			(0UL << 16) |				/* Scaling factor of 1 */
			(0x22UL << 0);			/* Counter preload value:  0x22 * 1 * 12.5ns = 0.425us */
		
		NHET0->NHETSFENA =			/* Enable suppression Filter */
			(1UL << 28) |				/* Enable on ch 28 */
			(1UL << 10);				/* Enable on ch 10 */
		
		NHET0->NHETREQENS =			/* HET Request Enable */
			(0UL << 0) |				/* Disable Request 0 */
			(1UL << 1) |				/* Enable Request 1 */
			(1UL << 2) |  				/* Enable Request 2 */
		    (1UL << 4);					/* Enable Request 4 */

		NHET0->NHETREQDS =				/* HET Request Destination */
			(0UL << 0) |						/* HTU Request 0 */
			(0UL << 1) |						/* HTU Request 1 */
			(0UL << 2) |  						/* HTU Request 2 */
			(D_CONFIGHETREGDMA_CNT_U32<< 4);	/* DMA Request 4 */
	
		/* Initialize HET0 program data words */
		HET_T1TRGMIN_0.memory.data_word = k_SENTSyncDelay_Cnt_u32 - 1000UL;
		HET_T2TRGMIN_0.memory.data_word = k_SENTSyncDelay_Cnt_u32 - 1000UL;
		HET_T1TRGMAX_0.memory.data_word = k_SENTSyncDelay_Cnt_u32;
		HET_T2TRGMAX_0.memory.data_word = k_SENTSyncDelay_Cnt_u32;

		HET_SYNCMIN_0.memory.data_word =  k_SENTSyncTrgMin_Cnt_u32;
	
		HET_SPI50U_BUF1_0.memory.data_word = (uint32)k_SPI50UOff_Cnt_u16;
		HET_SPI1m_BUF1_0.memory.data_word =  (uint32)k_SPI1mOff_Cnt_u16;
	
		/* Initialize Het Transfer Unit (HTU) 1 */
		HTU1_Init();

		NHET0->NHETGCR |= 0x01U;	/* Enable NHET */
	}
	/* End initialization of NHET 1 Peripheral */
	
	
	/* Start initialization of NHET 2 Peripheral */
	/* TI naming: NHET 1 registers named NHET0; NHET 2 registers named NHET1 */
	NHET1->NHETGCR =
		(0UL << 24) |							/* 0: Disable channel disable feature */
		(0UL << 18) |							/* 0: All masters can read and write the program fields.. */
		(1UL << 17) |							/* 1: NHET doesn't stop when a software breakpoint is encountered.*/
		(1UL << 16) |							/* 1: NHET is master */
		(0UL <<  0);							/* 0: Stop NHET */
	
	if( (NHET1->NHETGCR & 0x1UL) == 0UL )
	{
		/* copy the HET1 program */
		(void) memcpy((void *) &e_HETPROGRAM1_UN, (const void *) HET_INIT1_PST, sizeof(HET_INIT1_PST));
		
		NHET1->NHETPFR =					/* Timer Prescale */
			(4UL << 8) |						/* 7 -> lr=16 */
			(0UL << 0);						/* 0 -> hr=1:  ts = 16*1 = 16 */
		
		NHET1->NHETINTENAC = 0xFFFFFFFFUL;	/* Disable all interrupts */
		NHET1->NHETEXC1 = 0UL;				/* Disable exceptions */
		NHET1->NHETPRY = 0UL;					/* Interrupt priority level 2 */
		NHET1->NHETAND = 0UL;					/* No channels are AND shared */
		
		NHET1->NHETHRSH =					/* HR (input) Sharing */
			(0UL << 15) |						/* Do not share ch 30 and 31  */
			(0UL << 14) |						/* Do not share ch 28 and 29  */
			(0UL << 13) |						/* Do not share ch 26 and 27  */
			(0UL << 12) |						/* Do not share ch 24 and 25  */
			(0UL << 11) |						/* Do not share ch 22 and 23  */
			(0UL << 10) |						/* Do not share ch 20 and 21  */
			(0UL <<  9) |						/* Do not share ch 18 and 19  */
			(0UL <<  8) |						/* Do not share ch 16 and 17  */
			(1UL <<  7) |						/* Share ch 14 and 15  */
			(1UL <<  6) |						/* Share ch 12 and 13  */
			(1UL <<  5) |						/* Share ch 10 and 11  */
			(1UL <<  4) |						/* Share ch 8 and 9  */
			(0UL <<  3) |						/* Do not share ch 6 and 7  */
			(1UL <<  2) |						/* Share ch 4 and 5  */
			(0UL <<  1) |						/* Do not share ch 2 and 3  */
			(0UL <<  0);						/* Do not share ch 0 and 1  */
		
		NHET1->NHETXOR = 0UL;					/* No channels are XOR shared */
		NHET1->NHETREQENC = 0xFFUL;			/* Disable all request lines */
		NHET1->NHETREQDS = 0UL;				/* Assign request lines to HTU */
		NHET1->NHETDIR = 0UL;					/* All channels are inputs */
		NHET1->NHETPULDIS = 0UL;				/* Pull functionality enabled on all channels */
		NHET1->NHETPSL = 0UL;					/* All channels are set to pull down */
		NHET1->NHETPCR = 0xAUL;				/* Disable parity bit mapping, enable parity checking */
		NHET1->NHETPPR = 0UL;					/* No channels are affected by a parity error */
		
		NHET1->NHETSFPRLD =					/* Set suppression filter to 1.7us */
			(0x0UL << 16) |					/* Scaling factor of 1 */
			(0x6UL << 0);					/* Counter preload value:  0x6 * 1 * 12.5ns = 0.075us */
		
		NHET1->NHETSFENA =					/* Enable suppression Filter */
			(1UL << 15) |						/* Enable on ch 15 */
			(1UL << 14) |						/* Enable on ch 14 */
			(1UL << 13) |						/* Enable on ch 13 */
			(1UL << 12) |						/* Enable on ch 12 */
			(1UL << 11) |						/* Enable on ch 11 */
			(1UL << 10) |						/* Enable on ch 10 */
			(1UL <<  9) |						/* Enable on ch 9 */
			(1UL <<  8) |						/* Enable on ch 8 */
			(0UL <<  7) |						/* Disable on ch 7 */
			(0UL <<  6) |						/* Disable on ch 6 */
			(1UL <<  5) |						/* Enable on ch 5 */
			(1UL <<  4) |						/* Enable on ch 4 */
			(0UL <<  3) |						/* Disable on ch 3 */
			(0UL<<  2) |						/* Disable on ch 2 */
			(0UL <<  1) |						/* Disable on ch 1 */
			(0UL <<  0);						/* Disable on ch 0 */
		
		NHET1->NHETPINDIS = 0UL;				/* Output buffer enable is controlled by HETDIR */
		
		NHET1->NHETGCR |= 0x01UL;			/* Enable NHET */
		
		
	}
	/* End initialization of NHET 2 Peripheral */
	

}

/*****************************************************************************
  * Name:        HTU1_Init
  * Description: This function initializes the HTU 1 module
  * Inputs:      None
  * Outputs:     None
  *
*****************************************************************************/
STATIC INLINE FUNC(void, NHET_CODE) HTU1_Init(void)
{
	/* TI naming: HTU 1 registers named HTU0; HTU 2 registers named HTU1 */
	
 	/* check for HTU reset bit cleared; if not set flag */
	if (( HTU0REG->GC & 1UL ) == 1U)
	{
		/* Set global variable flag HTU 1 reset failed status for uDiag component */
		Nhet_Htu1RstFail_Cnt_G_lgc = TRUE;
	}
	else
	{
		/* Clear global variable flag HTU 1 reset failed status for uDiag component */
		Nhet_Htu1RstFail_Cnt_G_lgc = FALSE;
		
		/* init HTU0 registers */
   
		/***********************************************************
		* Configure the control packet for input capture HET code *
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


		/*HET instruction requests on HTU line 1 configure the control packet*/
	
		HTU0DCP1->IFADDRA = (uint32)&(Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq1_Cnt_u32[0]);		
		/*Initial frame address set to the RAM buffer*/
		HTU0DCP1->ITCOUNT = 	((uint32)D_CELEMENT_CNT_U16 	<< 16U) | 	/* IETCOUNT */
								((uint32)D_CFRAME_CNT_U16		<< 0U); 	/* IFTCOUNT */
							
		HTU0DCP1->IHADDRCT = (0UL << 23U) | 	/* DIR */	/* set to 1 for Main memory is read and then written to NHET RAM*/
							(0UL << 22U) | 	/* SIZE */
							(0UL << 21U) | 	/* ADDMH */
							(0UL << 20U) | 	/* ADDFM */
							(1UL << 18U) | 	/* TMBA */		/* Circular buffer mode  */
							(0UL << 16U) | 	/* TMBB */		/* One shot mode */
							((D_WCAPHTUADDR1_CNT_U32 & 0x0FFCUL) << 0U); 	/* IHADDR */	
							/*address of NHET instruction data field location to start( Least significant 12 bits, with LSB 2 bits masked out)*/
	
		/*HET instruction requests on HTU line 2 configure the control packet*/
	
		HTU0DCP2->IFADDRA = (uint32)&(Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq2_Cnt_u32[0]);		
		/*Initial frame address set to the RAM buffer*/
		HTU0DCP2->ITCOUNT = ((uint32)D_CELEMENT_CNT_U16 	<< 16U) | 	/* IETCOUNT */
							((uint32)D_CFRAME_CNT_U16		<< 0U); 		/* IFTCOUNT */
						
		HTU0DCP2->IHADDRCT = (0UL << 23U) | 	/* DIR */	/* set to 1 for Main memory is read and then written to NHET RAM*/
							(0UL << 22U) | 	/* SIZE */
							(0UL << 21U) | 	/* ADDMH */
							(0UL << 20U) | 	/* ADDFM */
							(1UL << 18U) | 	/* TMBA */		/* Circular buffer  Buffer A*/
							(0UL << 16U) | 	/* TMBB */		/*  One shot mode  Buffer B*/
							((D_WCAPHTUADDR2_CNT_U32 & 0x0FFCUL) << 0U); 	/* IHADDR */	
							/*address of NHET instruction data field location to start( Least significant 12 bits, with LSB 2 bits masked out)*/

	
		HTU0REG->CPENA = 0x14UL; 		      /* CPA is enabled for Control Packets 1 and 2 */

		/* Configure 1 region memory protection: */
		HTU0REG->MPCS = (0UL << 17U) |	/* MPEFT1 */	/*Cleared on reset*/
						(0UL << 16U) |	/* MPEFT0 */	/*Cleared on reset*/
						(0UL << 5U) |	/* INTENA01 */
						(0UL << 4U) |	/* ACCR01 */
						(0UL << 3U) |	/* REG01ENA */
						(1UL << 2U) |	/* INTENA0 */   /* Error Signaling is enabled region 0 */
						(1UL << 1U) |	/* ACCR */      /* HTU access forbidden outside region 0 */
						(1UL << 0U);	/* REG0ENA */   /* Region 0 enable */

		/* Region 0 memory protection covers the TCM RAM buffer containing the new values for the data fields of the Nhet instructions */
		HTU0REG->MP0S = (uint32)&Nhet_HtuDataTrq_Cnt_G_str;
		HTU0REG->MP0E = (uint32)&Nhet_HtuDataTrq_Cnt_G_str + ((uint32)sizeof(Nhet_HtuDataTrq_Cnt_G_str)-4UL);

		/* enable the HTU */
		HTU0REG->GC	   =  (1UL << 16U) |      /*Enable the HTU*/
						(1UL << 8U)  |       /* Allow HTU to continue on debug*/
						(0UL << 0U);   	   /* No Reset request issued to the HTU module.*/
	}				  
}




