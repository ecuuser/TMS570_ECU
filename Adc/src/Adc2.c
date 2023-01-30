/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Adc2.c
* Module Description: ADC Unit 2 Complex Device Driver
* Product           : Gen II Plus - EA3.0
* Author            : Lonnie Newton
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Fri Nov 02 09:15:00 2012
* %version:          7 %
* %derived_by:       nzt9hv %
* %date_modified:    Wed Apr 09 16:52:39 2014 %
*---------------------------------------------------------------------------*/

#include "Adc2.h"
#include "Adc_Common.h"
#include "CDD_Data.h"
#include "Calconstants.h"
#include "SystemTime.h"
#include "Ap_DiagMgr.h"
#include "Adc.h"
#include "GlobalMacro.h"


#define D_ADC2NUMRSLTBUF_CNT_U08		64U	/* The number of result buffers is based on the value of BNDEND, which the
												FDD specifies to result in 64 buffers.  This number could become part of
												the configuration file if the use case arises */

/* Check that the ADC RAM allocation configuration is valid */
/* Is the sum of the buffers correct?, Is any buffer an odd number? */
#if (((D_ADC2EVTBUFSZ_CNT_U08 + D_ADC2G1BUFSZ_CNT_U08 + D_ADC2G2BUFSZ_CNT_U08) != D_ADC2NUMRSLTBUF_CNT_U08) || \
	((D_ADC2EVTBUFSZ_CNT_U08 & 1U)> 0U) || ((D_ADC2G1BUFSZ_CNT_U08 & 1U)>0U) || ((D_ADC2G2BUFSZ_CNT_U08 & 1U)> 0U))
	#error "Invalid Adc1 result RAM buffer allocation configuration: EVT, G1 and G2 allocation must sum to 64, and all must be even"
#endif

#define ADC2_START_SEC_CONST_32
#include "MemMap.h"
/* Module internal configuration data structure, post build configuration of this module not currently supported.
 * Thus the configuration structure is defined within the static source and initialized with values from the
 * configuration file.
 */
STATIC CONST(Adc_GroupConfigDataType, ADC_PBCFG) T_Adc2GroupConfigData_Cnt_Str[3] =
{
	{
		D_ADC2NUMEVTCH_CNT_U08,
		D_ADC2EVTCH_CNT_U32,
		&(((uint32*)D_ADC2RSLTBASEADR_CNT_U32)[0]),
	},
	{
		D_ADC2NUMG1CH_CNT_U08,
		D_ADC2G1CH_CNT_U32,
		&(((uint32*)D_ADC2RSLTBASEADR_CNT_U32)[D_ADC2EVTBUFSZ_CNT_U08]),
	},
	{
		D_ADC2NUMG2CH_CNT_U08,
		D_ADC2G2CH_CNT_U32,
		&(((uint32*)D_ADC2RSLTBASEADR_CNT_U32)[D_ADC2EVTBUFSZ_CNT_U08 + D_ADC2G1BUFSZ_CNT_U08]),
	}
};
#define ADC2_STOP_SEC_CONST_32
#include "MemMap.h" /* PRQA S 5087 */


#define ADC2_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */
/*****************************************************************************
  * Name:        Adc2_Init1
  * Description: Adc2 primary initialization and initial conversion trigger 
  * Inputs:      None 
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, ADC2_CODE) Adc2_Init1  (void)
{
	VAR(sint8, AUTOMATIC) i; /* use case of this indexer requires it to be signed */
	VAR(uint8, AUTOMATIC) Group_Cnt_T_u08;
	VAR(uint32, AUTOMATIC) convMask_Cnt_T_u32;
	VAR(uint16, AUTOMATIC)  ADCOffset_Cnt_T_u8p8;
	
	/* ADC RAM Auto-Initialization is performed by Mcu_Init*/
	/* Parity Enabled by uDiag Component */

	/* Enable ADC for normal operation */
	adcREG2->OPMODECR = 0x80140001U;

	/* Configure the ADCLK Frequency (Vclk /(Prescale + 1))*/
	adcREG2->CLOCKCR = 4U;

	/* Assign the 64 words ADC FIFO RAM to three conversion Groups */
	adcREG2->BNDEND = 0x02U;
	/* Compute the result buffer boundaries based on the configured result RAM allocations */
	adcREG2->BNDCR  = (uint32) (((uint32)(D_ADC2EVTBUFSZ_CNT_U08 & 0xFEU) << 15U) +
					  ((uint32)(D_ADC2EVTBUFSZ_CNT_U08 + D_ADC2G1BUFSZ_CNT_U08) >> 1U));

	adcREG2->G0SAMP = 6U;
	adcREG2->G1SAMP = 6U;
	adcREG2->G2SAMP = 6U;

	/* Perform Offset Calibration */
	ADC2_REPORTERRORSTATUS(NTC_Num_PerDiag_ADC2Flt, D_NTCPARMBIT1_CNT_U8, (ADCOffsetCalibration(adcREG2,&ADCOffset_Cnt_T_u8p8)));

    /* Common Register Configuration */
	adcREG2->RSTCR = 0U;
	adcREG2->EVTDIR = 0U;
	adcREG2->EVTDIS = 0U;
	adcREG2->EVTPSEL = 0U;
	adcREG2->MAGINT1MASK = 0U;
	adcREG2->MAGINT2MASK = 0U;
	adcREG2->MAGINT3MASK = 0U;
	adcREG2->MAGINTCR1 = 0U;
	adcREG2->MAGINTCR2 = 0U;
	adcREG2->MAGINTCR3 = 0U;
	adcREG2->MAGTHRINTENASET = 0U;
	adcREG2->MAGTHRINTENACLR = 0x7U;

	/* Event Group Register Configuration */
	adcREG2->G0SRC = D_ADC2EVSRC_CNT_U32;
	adcREG2->GxINTENA[D_GROUPEV_CNT_U8] = D_ADC2EVINTENA_CNT_U32;
	adcREG2->GxINTCR[D_GROUPEV_CNT_U8] = 0U;
	adcREG2->G0SAMPDISEN = D_ADC2EVSAMPDISEN_CNT_U32;
	adcREG2->GxFIFORESETCR[D_GROUPEV_CNT_U8] = D_ADC2EVFIFORESETCR_CNT_U32;
	adcREG2->G0DMACR = D_ADC2EVDMACR_CNT_U32;
	adcREG2->GxMODECR[D_GROUPEV_CNT_U8] = 0x00010030U;

	/* Group 1 Register Configuration */
	adcREG2->G1SRC = D_ADC2G1SRC_CNT_U32;
	adcREG2->GxINTENA[D_GROUP1_CNT_U8] = D_ADC2G1INTENA_CNT_U32;
	adcREG2->GxINTCR[D_GROUP1_CNT_U8] = 0U;
	adcREG2->G1SAMPDISEN = D_ADC2G1SAMPDISEN_CNT_U32;
	adcREG2->GxFIFORESETCR[D_GROUP1_CNT_U8] = D_ADC2G1FIFORESETCR_CNT_U32;
	adcREG2->G1DMACR = D_ADC2G1DMACR_CNT_U32;
	adcREG2->GxMODECR[D_GROUP1_CNT_U8] = 0x00010030U;

	/* Group 2 Register Configuration */
	adcREG2->G2SRC = D_ADC2G2SRC_CNT_U32;
	adcREG2->GxINTENA[D_GROUP2_CNT_U8] = D_ADC2G2INTENA_CNT_U32;
	adcREG2->GxINTCR[D_GROUP2_CNT_U8] = 0U;
	adcREG2->G2SAMPDISEN = D_ADC2G2SAMPDISEN_CNT_U32;
	adcREG2->GxFIFORESETCR[D_GROUP2_CNT_U8] = D_ADC2G2FIFORESETCR_CNT_U32;
	adcREG2->G2DMACR = D_ADC2G2DMACR_CNT_U32;
	adcREG2->GxMODECR[D_GROUP2_CNT_U8] = 0x00010030U;

	/* Indirect initialization of Adc Ram buffer pointers.  There is no direct method to set the pointers
	 * and all pointers start at 0 after init.  
	 * NOTE: The G2 pointer is intentionally left uninitialized here because it is required by the FDD design to
	 * perform a software triggered conversion of the Event group signals at init.  Leaving the pointer uninitialized
	 * allows the G2 group to be lined up with the event group memory for the initial sw triggered conversion.
	 * */
	i = (sint8) D_ADC2EVTBUFSZ_CNT_U08; /* init to number of dummy conversions required, using a mathematical expression vs conditional to explicitly reduce branching */
	Group_Cnt_T_u08 = D_GROUP1_CNT_U8;

	while(i > 0){
		convMask_Cnt_T_u32 = (1ul << (Min_m(i, 16))) - 1ul; /* compute required conversion mask, up to 16 bits. */
		i -= 16; /* Decrement i by the max number of conversions, it is signed so a negative number will allow exiting the loop */
		adcREG2->GxSEL[Group_Cnt_T_u08] = convMask_Cnt_T_u32; /* Start the dummy conversion */
		while((adcREG2->GxSR[Group_Cnt_T_u08] & D_GROUPBUSY_CNT_U32) != 0U){
			/* wait */
		}
	}

	
	/* Trigger Initial Adc Conversions, for sw trigger the conversions start immediately */
	Adc2_StartGroupConversion(D_GROUPEV_CNT_U8); /* This does not actually trigger an event group, rather it only selects the channels for when the group is triggered */
	Adc2_StartGroupConversion(D_GROUP1_CNT_U8);
	Adc2_StartGroupConversion(D_GROUP2_CNT_U8);	/* The G2 Adc Ram addr should be pointing to the start of event group memory at this point for initial conversion */


	/******************************************************/
	/* Reconfigure the Adc groups for hardware triggering */
 	/******************************************************/
	#if (D_HWTRGADC2GEVT_CNT_LGC == STD_ON)
		adcREG2->GxMODECR[D_GROUPEV_CNT_U8] = 0x00010038U;
	#endif

	#if (D_HWTRGADC2G1_CNT_LGC == STD_ON)
		adcREG2->GxMODECR[D_GROUP1_CNT_U8] = 0x00010038U;
	#endif
	
	#if (D_HWTRGADC2G2_CNT_LGC == STD_ON)
		adcREG2->GxMODECR[D_GROUP2_CNT_U8] = 0x00010038U;
	#endif
	

#if (D_ADC2USEDMA_CNT_LGC == STD_OFF)
/* not using DMA for ADC data transfer */
	
	/* Enable ISR on conversion completion for D_ISRGROUP_CNT_U8 group to trigger MtrCtl ISR */
	Adc2_EnableGroupNotification(D_ISRGROUP_CNT_U8);
#endif
  Adc2_Write_ADC2OffsetComp_Cnt_u8p8(ADCOffset_Cnt_T_u8p8);

}

FUNC(void, ADC2_CODE) Adc2_StartGroupConversion  (uint8 group)
{

    /* Setup FiFo size */
	adcREG2->GxINTCR[group] = T_Adc2GroupConfigData_Cnt_Str[group].NumOfChannels;

    /* Start Conversion */
	adcREG2->GxSEL[group] = T_Adc2GroupConfigData_Cnt_Str[group].ChannelSelect;
}

FUNC(void, ADC2_CODE) Adc2_EnableGroupNotification  (uint8 group)
{
    	adcREG2->GxINTENA[group] = 8U;
}

#define ADC2_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */


/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description              SCR #
-------   -------  --------  -----------------------------------  ----------
11/02/12   1.0      LN      	Initial Component Creation			CR6519
01/18/13   2      	JJW      	Updates per peer review
								Adc Ram pointer init workaround
17/02/13   2.1.1    Selva       D_ADC2xSRC_CNT_U32 Macros are defined
								in config file to make implementation 
								same accross different project
04/28/13   3.0      Selva       QAC fixes added.
05/22/13   4        LWW         Fixed incorrect dereferencing of function parameter
05/23/13   5        SP          QAC fixes							 8394                            
04/09/14   6        KMC         Updated to be configurable to use    11684
                                with DMA.
06/27/14   7        Selva       Updated for ADC offset compensation 
******************************************************************************/

