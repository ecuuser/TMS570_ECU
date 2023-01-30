/*****************************************************************************
* Copyright 2015 Nexteer 
* Nexteer Confidential
*
* Module File Name  : Dma.h
* Module Description: DMA Peripheral Header
* Product           : CBD
* Author            : Owen Tosh
*****************************************************************************
* Version Control:
* Date Created:      Tue Mar 11 12:00:00 2014
* %version:          4 %
* %derived_by:       nz63rn %
***********************************************************************************************************************/
/***********************************************************************************************************************
* Change History:
* Date      Rev      Author    Change Description                                                                CR#
* --------  -------  --------  --------------------------------------------------------------------------------- -----
* 04/08/14   1       OT        Initial version
* 04/29/14   2       OT        Added data integrity functionality                                                11855
* 05/02/14   3       OT        Updated to FDD 52 v002 (removed slow SPI integrity check scheme)                  11871
* 01/31/15   4       KMC       Added Dma_DmaRstFail_Cnt_G_lgc and added dummy struct element for                 CR12749
*                              64-bit alignment of beginning and end of DMADataType_Str for ES-52 v004
***********************************************************************************************************************/


#ifndef DMA_H
#define DMA_H


#include "Dma_Cfg.h"
#include "appinit_cfg.h"



#if (D_DMAFLSTSTENABLED_CNT_ENUM == STD_ON)
	#include "crc_regs.h"
#endif

#if (D_FASTSPIGROUPENABLED_CNT_ENUM == STD_ON)
	#include "SpiNxt.h"
	#include "mibspi_regs.h"
#endif

#if (D_FASTADCGROUPENABLED_CNT_ENUM == STD_ON)
	#include "Adc2.h"
#endif

#if (D_FASTPWMGROUPENABLED_CNT_ENUM == STD_ON)
	#include "Nhet_SENT_Prog.h"
	#include "epwm_regs.h"
#endif

#if (D_SLOWADCGROUPENABLED_CNT_ENUM == STD_ON)
	#include "Adc.h"
#endif



/* FlsTst Groups */
#if (D_DMAFLSTSTENABLED_CNT_ENUM == STD_ON)
	#define D_CRCCTRLREGSTART_CNT_U32		&(CRCCTRLREG->CRC_REGL1)
	#define D_CRCPSASIGREGSTART_CNT_U32		&(CRCCTRLREG->PSA_SIGREGL1)
#endif


/* 50us SPI Group */
#if (D_FASTSPIGROUPENABLED_CNT_ENUM == STD_ON)
	#define D_NUMFASTSPIWORDS_CNT_U16		D_TGSIZE_CNT_U16
	#define D_FASTSPISTARTADDR_CNT_U32		&(mibspiRAM3->rx[0].data)
	#define D_NUMSLOWSPIWORDS_CNT_U16		D_TGSIZE_CNT_U16
	#define D_SLOWSPISTARTADDR_CNT_U32		&(mibspiRAM5->rx[0].data)
#endif


/* 50us ADC Group */
#if (D_FASTADCGROUPENABLED_CNT_ENUM == STD_ON)
	#define D_NUMFASTADCCHANNELS_CNT_U16	D_ADC2G1BUFSZ_CNT_U08
	#define D_FASTADCSTARTADDR_CNT_U32		(D_ADC2RSLTBASEADR_CNT_U32 + (4u * D_ADC2EVTBUFSZ_CNT_U08) + 2u) /* +2 for 16-bit offset in ADC buffer */
#endif


/* 50us PWM Group */
#if (D_FASTPWMGROUPENABLED_CNT_ENUM == STD_ON)
	#define D_DMANHETPERIODADDR_CNT_U32		&(HET_PRD_BUF1_0.memory.data_word)
	#define D_EPWMSTARTADDR_CNT_U32			&(ePWM1->CMPA)
#endif


/* 2ms ADC Group */
#if (D_SLOWADCGROUPENABLED_CNT_ENUM == STD_ON)
	#define D_NUMSLOWADCCHANNELS_CNT_U16	D_ADC1G2BUFSZ_CNT_U08
	#define D_SLOWADCSTARTADDR_CNT_U32		(0xFF3E0000ul + (4u * (D_ADC1EVTBUFSZ_CNT_U08 + D_ADC1G1BUFSZ_CNT_U08)) + 2u) /* 60 unused buffers, +2 for 16-bit offset */
#endif


#if (D_FASTSPIGROUPENABLED_CNT_ENUM == STD_ON) || \
	(D_FASTADCGROUPENABLED_CNT_ENUM == STD_ON) || \
	(D_SLOWADCGROUPENABLED_CNT_ENUM == STD_ON) || \
	(D_FASTPWMGROUPENABLED_CNT_ENUM == STD_ON)

typedef struct
{
	float64 DummyVarForAlignment_Uls_f64; /* will align beginning and end of struct to 64-bit boundary -- see MDD */
#if (D_FASTSPIGROUPENABLED_CNT_ENUM == STD_ON)
	uint16	FastSPI_Cnt_u16[D_NUMFASTSPIWORDS_CNT_U16];
	uint16	SlowSPI_Cnt_u16[D_NUMSLOWSPIWORDS_CNT_U16];
#endif
#if (D_SLOWADCGROUPENABLED_CNT_ENUM == STD_ON)
	uint16	SlowADC_Cnt_u16[D_NUMFASTADCCHANNELS_CNT_U16];
#endif
#if (D_FASTADCGROUPENABLED_CNT_ENUM == STD_ON)
	uint16	FastADC_Cnt_u16[D_NUMSLOWADCCHANNELS_CNT_U16];
#endif
#if (D_FASTPWMGROUPENABLED_CNT_ENUM == STD_ON)
	uint16	PWMCmp_Cnt_u16[4][2];
	uint32	PWMPeriod_Cnt_u32;
#endif
} DMADataType_Str;

extern volatile VAR(DMADataType_Str, DMA_VAR) DMAData_G_str;
#endif

extern VAR(boolean, DMA_VAR) Dma_DmaRstFail_Cnt_G_lgc;

extern FUNC(void, DMA_CODE) Dma_Init(void);

extern FUNC(boolean, DMA_CODE) Dma_SlowADCGroupValidity(void);

extern FUNC(void, DMA_CODE) Dma_InvalidateSlowADCGroup(void);

extern FUNC(void, DMA_CODE) Dma_SetupMtrCtrlGroups(void);

extern FUNC(void, DMA_CODE) Dma_SetupFlsTstBlock( VAR(uint32, AUTOMATIC) CRCAddr_Cnt_T_u32,
												  VAR(uint32, AUTOMATIC) FlsAddr_Cnt_T_u32,
												  VAR(uint16, AUTOMATIC) DmaFrameCount_Cnt_T_u16,
												  VAR(uint16, AUTOMATIC) DmaElementCount_Cnt_T_u16 );

extern FUNC(void, DMA_CODE) Dma_EnableFlsTstBlock(void);

extern FUNC(void, DMA_CODE) Dma_DisableFlsTstBlock(void);


#endif
