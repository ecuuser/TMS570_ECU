/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Template_Adc_Cfg.h
* Module Description: Adc Driver configuration
* Product           : Gen II Plus - EA3.0
* Author            : Selva Sengottaiyan
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sat Jul 28 18:03:04 2012
* %version:          3 %
* %derived_by:       nzt9hv %
* %date_modified:    Tue Apr 30 12:57:33 2013 %
*---------------------------------------------------------------------------*/


#ifndef ADC_CFG_H
#define ADC_CFG_H


#include "Adc.h"

/*** For 33E ADC (Current mode) define the following macro ***/
#define D_ADC1CURRENTMODE_ULS_LGC

/* Map user defined group conversion names to appropriate group indexer */
#define AdcFwdPath     		??
#define AdcFdbkPath     	??
#define adcGROUP0		??


#define D_ADC1NUMEVTCH_CNT_U08	??				/* Number of channels sampled (e.g. number of bits set in D_ADC1EVTCH_CNT_U32) */
#define D_ADC1EVTCH_CNT_U32		??
#define D_ADC1EVTBUFSZ_CNT_U08	??				/* Number of results allocated in ADC RAM, must be even */

#define D_ADC1NUMG1CH_CNT_U08	??				/* Number of channels sampled (e.g. number of bits set in D_ADC1G1CH_CNT_U32) */
#define D_ADC1G1CH_CNT_U32		??
#define D_ADC1G1BUFSZ_CNT_U08	??				/* Number of results allocated in ADC RAM, must be even */

#define D_ADC1NUMG2CH_CNT_U08	??				/* Number of channels sampled (e.g. number of bits set in D_ADC1G2CH_CNT_U32) */
#define D_ADC1G2CH_CNT_U32		??
#define D_ADC1G2BUFSZ_CNT_U08	??				/* Number of results allocated in ADC RAM, must be even */

#define ADC1_REPORTERRORSTATUS(event, param, status)		??

#define ADC_EVENT_PASSED				??
#define ADC_EVENT_FAILED				??
#define  D_TRUE_CNT_LGC                 ??
#define  D_FALSE_CNT_LGC                ??

typedef uint8	Adc_ConfigType;

/***************************************************************************************
* following constants added for use with DMA; see below for settings to use for 
* FDD33C rev 008 and FDD33E rev 002 (pre-DMA) compatibility
****************************************************************************************/
   
/* Event Group Register Configuration (Currently Not Used) */
#define D_ADC1GEVTSRC_CNT_U32		0U
#define D_ADC1GEVTDMACR_CNT_U32		0U

/* Group 1 Register Configuration */
#define D_ADC1G1SRC_CNT_U32			??
#define D_ADC1G1DMACR_CNT_U32		??

/* Group 2 Register Configuration */
#define D_ADC1G2SRC_CNT_U32			??
#define D_ADC1G2DMACR_CNT_U32		??

/* define D_ADC1USEDMA_CNT_LGC to STD_ON if using DMA to transfer ADC data; STD_OFF if not using DMA */
#define D_ADC1USEDMA_CNT_LGC     ??

/* define D_HWTRGADC1Gx_CNT_LGC to STD_ON to use hardware triggering; STD_OFF to use software triggering */
/* only used when D_ADC1USEDMA_CNT_LGC == STD_ON */
#define D_HWTRGADC1GEVT_CNT_LGC     ??
#define D_HWTRGADC1G1_CNT_LGC       ??
#define D_HWTRGADC1G2_CNT_LGC       ??

/***************************************************************************************
* for compatibility with FDD33C rev 008 and FDD 33E rev 002 use the following settings
* for these constants (which were added for additional configurability needed for DMA)
****************************************************************************************/

/* Event Group Register Configuration (Currently Not Used) */
#define D_ADC1GEVTSRC_CNT_U32		0U
#define D_ADC1GEVTDMACR_CNT_U32		0U

/* Group 1 Register Configuration */
#define D_ADC1G1SRC_CNT_U32			0U
#define D_ADC1G1DMACR_CNT_U32		0U

/* Group 2 Register Configuration */
#define D_ADC1G2SRC_CNT_U32			0U
#define D_ADC1G2DMACR_CNT_U32		0U

/* define D_ADC1USEDMA_CNT_LGC to STD_ON if using DMA to transfer ADC data; STD_OFF if not using DMA */
#define D_ADC1USEDMA_CNT_LGC     STD_OFF

/* define D_HWTRGADC1Gx_CNT_LGC to STD_ON to use hardware triggering; STD_OFF to use software triggering */
/* only used when D_ADC1USEDMA_CNT_LGC == STD_ON */
#define D_HWTRGADC1GEVT_CNT_LGC     STD_OFF
#define D_HWTRGADC1G1_CNT_LGC       STD_OFF
#define D_HWTRGADC1G2_CNT_LGC       STD_OFF

#define  Adc1_Write_ADC1OffsetComp_Cnt_u8p8(val)   ??= val

#endif

/*****************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description                 SCR #
-------   -------  --------  -----------------------------------     ----------
           1.0              	Initial Version      			
04/09/14   2        KMC         Updated for configurability to use    11684
                                with DMA.
06/27/14   3        Selva       Updated for ADC offset compensation  					
******************************************************************************/
