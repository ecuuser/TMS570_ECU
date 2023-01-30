/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Template_Adc2_Cfg.h
* Module Description: Adc2 Complex Driver configuration
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


/*** Replace the ?? with required values ***/

#ifndef ADC2_CFG_H
#define ADC2_CFG_H

/* Include definitions for Diagnostic Event API */

#define D_ADC2NUMEVTCH_CNT_U08		??				/* Number of channels sampled (e.g. number of bits set in D_ADC2EVTCH_CNT_U32) */
#define D_ADC2EVTCH_CNT_U32		??
#define D_ADC2EVTBUFSZ_CNT_U08		??				/* Number of results allocated in ADC RAM, must be even */
#define D_ADC2EVSRC_CNT_U32		??

#define D_ADC2NUMG1CH_CNT_U08		??				/* Number of channels sampled (e.g. number of bits set in D_ADC2G1CH_CNT_U32) */
#define D_ADC2G1CH_CNT_U32		??
#define D_ADC2G1BUFSZ_CNT_U08		??				/* Number of results allocated in ADC RAM, must be even */
#define D_ADC2G1SRC_CNT_U32		??

#define D_ADC2NUMG2CH_CNT_U08		??				/* Number of channels sampled (e.g. number of bits set in D_ADC2G2CH_CNT_U32) */
#define D_ADC2G2CH_CNT_U32		??
#define D_ADC2G2BUFSZ_CNT_U08		??				/* Number of results allocated in ADC RAM, must be even */
#define D_ADC2G2SRC_CNT_U32		??


#define ADC2_E_PERDIAG_FAILURE		??

#define ADC2_E_PERDIAG_INFO				??

#define ADC2_REPORTERRORSTATUS(event, param, status)     ??		
#define ADC2_EVENT_PASSED				??
#define ADC2_EVENT_FAILED				??

/* The following macros are designed to grant access to the motor Isr adc results
 *  At the moment, for efficiency, they allow direct access to the ADC results.
 * NOTE: This API is an extension to the AUTOSAR Adc API.
 */

#define  D_PHASEBCHN_CNT_U16           ??
#define  D_PHASECCHN_CNT_U16           ??
#define  D_COSTHETA1CHN_CNT_U16        ??
#define  D_SINTHETA1CHN_CNT_U16        ??
#define  D_ADC2T1CHN_CNT_U16           ??
#define  D_ADC2T2CHN_CNT_U16           ??

/* need to redefine macros below for use with DMA */

#define Adc2_GetPhsBCurr_Cnt_u16_m   Adc2_ReadConversion(D_PHASEBCHN_CNT_U16)
#define Adc2_GetPhsCCurr_Cnt_u16_m   Adc2_ReadConversion(D_PHASECCHN_CNT_U16)
#define Adc2_GetCosTheta1_Cnt_u16_m  Adc2_ReadConversion(D_COSTHETA1CHN_CNT_U16)
#define Adc2_GetSinTheta1_Cnt_u16_m  Adc2_ReadConversion(D_SINTHETA1CHN_CNT_U16)
#define Adc2_GetT1_Cnt_u16_m         Adc2_ReadConversion(D_ADC2T1CHN_CNT_U16)
#define Adc2_GetT2_Cnt_u16_m         Adc2_ReadConversion(D_ADC2T2CHN_CNT_U16)

/***************************************************************************************
* following constants added for use with DMA; see below for settings to use for 
* FDD33C rev 008 and FDD33E rev 002 (pre-DMA) compatibility
****************************************************************************************/

/* Event Group Register Configuration */
#define D_ADC2EVINTENA_CNT_U32		??
#define D_ADC2EVSAMPDISEN_CNT_U32		??
#define D_ADC2EVFIFORESETCR_CNT_U32	??
#define D_ADC2EVDMACR_CNT_U32			??

/* Group 1 Register Configuration */
#define D_ADC2G1INTENA_CNT_U32		??
#define D_ADC2G1SAMPDISEN_CNT_U32	??
#define D_ADC2G1FIFORESETCR_CNT_U32	??
#define D_ADC2G1DMACR_CNT_U32		??

/* Group 2 Register Configuration */
#define D_ADC2G2INTENA_CNT_U32		??
#define D_ADC2G2SAMPDISEN_CNT_U32	??
#define D_ADC2G2FIFORESETCR_CNT_U32	??
#define D_ADC2G2DMACR_CNT_U32		??

/* define D_HWTRGADC1Gx_CNT_LGC to STD_ON to use hardware triggering; STD_OFF to use software triggering */
#define D_HWTRGADC2GEVT_CNT_LGC     ??
#define D_HWTRGADC2G1_CNT_LGC       ??
#define D_HWTRGADC2G2_CNT_LGC       ??

/* define D_ADC2USEDMA_CNT_LGC to STD_ON if using DMA to transfer ADC data; STD_OFF if not using DMA */
#define D_ADC2USEDMA_CNT_LGC     ??

/* define D_ISRGROUP_CNT_U8 for group to trigger motor control ISR on conversion completion
/* e.g. #define D_ISRGROUP_CNT_U8	0u 	for trigger from event group
/* only used when D_ADC2USEDMA_CNT_LGC == STD_OFF */
#define D_ISRGROUP_CNT_U8	??


/***************************************************************************************
* for compatibility with FDD33C rev 008 and FDD 33E rev 002 use the following settings
* for these constants (which were added for additional configurability needed for DMA)
****************************************************************************************/

/* Event Group Register Configuration */
#define D_ADC2EVINTENA_CNT_U32		8U
#define D_ADC2EVSAMPDISEN_CNT_U32	0x00000201U
#define D_ADC2EVFIFORESETCR_CNT_U32	0U
#define D_ADC2EVDMACR_CNT_U32		0U

/* Group 1 Register Configuration */
#define D_ADC2G1INTENA_CNT_U32		0U
#define D_ADC2G1SAMPDISEN_CNT_U32	0U
#define D_ADC2G1FIFORESETCR_CNT_U32	0U
#define D_ADC2G1DMACR_CNT_U32		0U

/* Group 2 Register Configuration */
#define D_ADC2G2INTENA_CNT_U32		0U
#define D_ADC2G2SAMPDISEN_CNT_U32	0U
#define D_ADC2G2FIFORESETCR_CNT_U32	1U
#define D_ADC2G2DMACR_CNT_U32		0U

/* define D_HWTRGADC1Gx_CNT_LGC to STD_ON to use hardware triggering; STD_OFF to use software triggering */
#define D_HWTRGADC2GEVT_CNT_LGC     STD_OFF
#define D_HWTRGADC2G1_CNT_LGC       STD_ON
#define D_HWTRGADC2G2_CNT_LGC       STD_OFF

/* define D_ADC2USEDMA_CNT_LGC to STD_ON if using DMA to transfer ADC data; STD_OFF if not using DMA */
#define D_ADC2USEDMA_CNT_LGC     STD_OFF

/* define D_ISRGROUP_CNT_U8 for group to trigger motor control ISR on conversion completion
/* e.g. #define D_ISRGROUP_CNT_U8	0u 	for trigger from event group
/* only used when D_ADC2USEDMA_CNT_LGC == STD_OFF */
#define D_ISRGROUP_CNT_U8	0U

#define  Adc2_Write_ADC2OffsetComp_Cnt_u8p8(val)   ??= val

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
