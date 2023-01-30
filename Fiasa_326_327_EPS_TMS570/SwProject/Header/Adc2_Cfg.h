/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Adc2_Cfg.h
* Module Description: Adc2 Complex Driver configuration
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sat Jul 28 18:03:04 2012
* %version:          7 %
* %derived_by:       nzx5jd %
* %date_modified:    Wed Jan 15 12:21:09 2014 %
*---------------------------------------------------------------------------*/


#ifndef ADC2_CFG_H
#define ADC2_CFG_H

/* Include definitions for Diagnostic Event API */
#include "Ap_DiagMgr.h"
#include "CDD_Data.h"

#define D_ADC2NUMEVTCH_CNT_U08	0u				/* Number of channels sampled (e.g. number of bits set in D_ADC2EVTCH_CNT_U32) */
#define D_ADC2EVTCH_CNT_U32		0x0000u
#define D_ADC2EVTBUFSZ_CNT_U08	0u				/* Number of results allocated in ADC RAM, must be even */
#define D_ADC2EVSRC_CNT_U32		0u

#define D_ADC2NUMG1CH_CNT_U08	4u				/* Number of channels sampled (e.g. number of bits set in D_ADC2G1CH_CNT_U32) */
#define D_ADC2G1CH_CNT_U32		0x2103u
#define D_ADC2G1BUFSZ_CNT_U08	4u				/* Number of results allocated in ADC RAM, must be even */
#define D_ADC2G1SRC_CNT_U32		3u

#define D_ADC2NUMG2CH_CNT_U08	0u				/* Number of channels sampled (e.g. number of bits set in D_ADC2G2CH_CNT_U32) */
#define D_ADC2G2CH_CNT_U32		0x0000u
#define D_ADC2G2BUFSZ_CNT_U08	60u				/* Number of results allocated in ADC RAM, must be even */
#define D_ADC2G2SRC_CNT_U32		0u


#define ADC2_E_PERDIAG_FAILURE	NTC_Num_PerDiag_ADC2Flt

#define ADC2_E_PERDIAG_INFO		0x04u

#define ADC2_REPORTERRORSTATUS(event, param, status)	NxtrDiagMgr10_ReportNTCStatus(event, param, status)
#define ADC2_EVENT_PASSED								NTC_STATUS_PASSED
#define ADC2_EVENT_FAILED								NTC_STATUS_FAILED


#define D_PHASEBCHN_CNT_U16			0u
#define D_PHASEACHN_CNT_U16			1u
#define D_VREFDUMMYCHN_CNT_U16		2u			/* Used to create an even number of reads */
#define D_SYSCVSWITCHCHN_CNT_U16	3u


/* Event Group Register Configuration */
#define D_ADC2EVINTENA_CNT_U32		0u
#define D_ADC2EVSAMPDISEN_CNT_U32	0u
#define D_ADC2EVFIFORESETCR_CNT_U32	0u
#define D_ADC2EVDMACR_CNT_U32		0u

/* Group 1 Register Configuration */
#define D_ADC2G1INTENA_CNT_U32		0u
#define D_ADC2G1SAMPDISEN_CNT_U32	0u
#define D_ADC2G1FIFORESETCR_CNT_U32	0u
#define D_ADC2G1DMACR_CNT_U32		0x0008u

/* Group 2 Register Configuration */
#define D_ADC2G2INTENA_CNT_U32		0u
#define D_ADC2G2SAMPDISEN_CNT_U32	0u
#define D_ADC2G2FIFORESETCR_CNT_U32	0u
#define D_ADC2G2DMACR_CNT_U32		0u

/* define D_HWTRGADC1Gx_CNT_LGC to STD_ON to use hardware triggering; STD_OFF to use software triggering */
#define D_HWTRGADC2EV_CNT_LGC		STD_OFF
#define D_HWTRGADC2G1_CNT_LGC		STD_ON
#define D_HWTRGADC2G2_CNT_LGC		STD_OFF

/* define D_ADC2USEDMA_CNT_LGC to STD_ON if using DMA to transfer ADC data; STD_OFF if not using DMA */
#define D_ADC2USEDMA_CNT_LGC	STD_ON

#define Adc2_Write_ADC2OffsetComp_Cnt_u8p8(val)		CDD_ADC2OffsetComp_Cnt_G_u8p8 = (val)

#endif
