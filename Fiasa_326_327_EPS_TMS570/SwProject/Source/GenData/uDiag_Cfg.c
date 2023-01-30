
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : uDiag_Cfg.c
* Module Description: Configuration file of uDiag module
* Product           : Gen II Plus - EA3.0
* Generator         : artt 2.0.2.0
* Generation Time   : 28.05.2014 13:34:40
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 13 18:34:17 2012
 * %version:          4 %
 * %date_modified:    Thu Oct  4 13:57:17 2012 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 09/17/12   1       JJW       Initial template creation
 * 10/04/12   2       JJW       Added support for link-time register value determination
 * 10/04/12   3       JJW       Corrected constant suffixes
 * 04/07/14   4       KMC       Changed to use sizeof(var) - 1 for offset                                     11435
 * 04/21/14   5       KMC       Changed to use sizeof(var) + integer offset value (for anomaly 6589)          11803
 */
#define UDIAG_C
#include "uDiag.h"
#include "Nhet.h"
#include "Usr_RegCkDefs.h"
#include "Dma.h"

#define UDIAG_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

/* uDiag Configuration Definitions */
CONST(uDiag_RegChkType, AUTOMATIC) StaticRegTable_Cnt_M_str[ D_NUMOFTESTEDREGS_CNT_U16 ] = {
/* Register value definitions determined Pre-compile */
	{0xFFFFFF48ul, 0x01010001ul},                                      /* GHVSRC */
	{0xFFFFFF50ul, 0x00000009ul},                                      /* RCLKSRC */
	{0xFFFFFFC4ul, 0x0000000Aul},                                      /* BMMCR1 */
	{0xFFFFFFD0ul, 0x01010100ul},                                      /* CLKCNTL */
	{0xFFFF0000ul, 0x05050A05ul},                                      /* LOGICPDPWRCTRL0 */
	{0xFFFF0010ul, 0x050A0000ul},                                      /* MEMPDPWRCTRL0 */
	{0xFFFF0020ul, 0x00000004ul},                                      /* PDCLKDISREG */
	{0xFFFF00A0ul, 0x00000000ul},                                      /* GLOBALCTRL1 */
	{0xFFFFEB10ul, 0x02020000ul},                                      /* PINMMR00 */
	{0xFFFFEB14ul, 0x01010400ul},                                      /* PINMMR01 */
	{0xFFFFEB18ul, 0x04010101ul},                                      /* PINMMR02 */
	{0xFFFFEB1Cul, 0x01040001ul},                                      /* PINMMR03 */
	{0xFFFFEB20ul, 0x10100104ul},                                      /* PINMMR04 */
	{0xFFFFEB24ul, 0x01080404ul},                                      /* PINMMR05 */
	{0xFFFFEB28ul, 0x01010110ul},                                      /* PINMMR06 */
	{0xFFFFEB2Cul, 0x01010101ul},                                      /* PINMMR07 */
	{0xFFFFEB30ul, 0x01010101ul},                                      /* PINMMR08 */
	{0xFFFFEB34ul, 0x01010101ul},                                      /* PINMMR09 */
	{0xFFFFEB38ul, 0x01010101ul},                                      /* PINMMR10 */
	{0xFFFFEB3Cul, 0x01010101ul},                                      /* PINMMR11 */
	{0xFFFFEB40ul, 0x01010101ul},                                      /* PINMMR12 */
	{0xFFFFEB44ul, 0x01010101ul},                                      /* PINMMR13 */
	{0xFFFFEB48ul, 0x01010101ul},                                      /* PINMMR14 */
	{0xFFFFEB4Cul, 0x01010101ul},                                      /* PINMMR15 */
	{0xFFFFEB50ul, 0x01010101ul},                                      /* PINMMR16 */
	{0xFFFFEB54ul, 0x01010101ul},                                      /* PINMMR17 */
	{0xFFFFEB58ul, 0x00010001ul},                                      /* PINMMR18 */
	{0xFFFFEB5Cul, 0x01010101ul},                                      /* PINMMR19 */
	{0xFFFFEB60ul, 0x01010101ul},                                      /* PINMMR20 */
	{0xFFFFEB64ul, 0x01010001ul},                                      /* PINMMR21 */
	{0xFFFFEB68ul, 0x01010101ul},                                      /* PINMMR22 */
	{0xFFFFEB6Cul, 0x00000001ul},                                      /* PINMMR23 */
	{0xFFFFEB70ul, 0x00000000ul},                                      /* PINMMR24 */
	{0xFFFFEB74ul, 0x00000000ul},                                      /* PINMMR25 */
	{0xFFFFEB78ul, 0x01010000ul},                                      /* PINMMR26 */
	{0xFFFFEB7Cul, 0x01010101ul},                                      /* PINMMR27 */
	{0xFFFFEB80ul, 0x01010101ul},                                      /* PINMMR28 */
	{0xFFFFEB84ul, 0x00000101ul},                                      /* PINMMR29 */
	{0xFFFFEB88ul, 0x00000202ul},                                      /* PINMMR30 */
	{0xFFF87000ul, 0x00000311ul},                                      /* FRDCNTL */
	{0xFFF87008ul, 0x000A060Aul},                                      /* FEDACTRL1 */
	{0xFFFFF800ul, 0x0005000Aul},                                      /* RAMCTRL_EVEN */
	{0xFFFFF804ul, 0x00000001ul},                                      /* RAMTHRESHOLD_EVEN */
	{0xFFFFF80Cul, 0x00000001ul},                                      /* RAMINTCTRL_EVEN */
	{0xFFFFF830ul, 0x00000005ul},                                      /* RAMTEST_EVEN */
	{0xFFFFF900ul, 0x0005000Aul},                                      /* RAMCTRL_ODD */
	{0xFFFFF904ul, 0x00000001ul},                                      /* RAMTHRESHOLD_ODD */
	{0xFFFFF90Cul, 0x00000001ul},                                      /* RAMINTCTRL_ODD */
	{0xFFFFF930ul, 0x00000005ul},                                      /* RAMTEST_ODD */
	{0xFFFFE580ul, 0x00000000ul},                                      /* PACT */
	{0xFFFFE604ul, 0x00000005ul},                                      /* STCGCR1 */
	{0xFFFFF604ul, 0x00000000ul},                                      /* CCMKEYR */
	{0xFFFFFF70ul, 0x00055F00ul},                                      /* PLLCTL1 */
	{0xFFFFFF74ul, 0x00007200ul},                                      /* PLLCTL2 */
	{0xFFFFE100ul, 0x60055F00ul},                                      /* PLLCTL3 */
	{0xFFFFEC00ul, 0x0000000Aul},                                      /* DCCGCTRL_DCC1 */
	{0xFFFFEC08ul, 0x00002475ul},                                      /* DCCCNT0SEED_DCC1 */
	{0xFFFFEC0Cul, 0x00009AF2ul},                                      /* DCCVALID0SEED_DCC1 */
	{0xFFFFEC10ul, 0x00002648ul},                                      /* DCCCNT1SEED_DCC1 */
	{0xFFFFEC24ul, 0x0000A003ul},                                      /* DCCCNT1CLKSRC_DCC1 */
	{0xFFFFEC28ul, 0x00000000ul},                                      /* DCCCNT0CLKSRC_DCC1 */
	{0xFFFFF400ul, 0x0000000Aul},                                      /* DCCGCTRL_DCC2 */
	{0xFFFFF408ul, 0x00004BD9ul},                                      /* DCCCNT0SEED_DCC2 */
	{0xFFFFF40Cul, 0x000004B1ul},                                      /* DCCVALID0SEED_DCC2 */
	{0xFFFFF410ul, 0x00013880ul},                                      /* DCCCNT1SEED_DCC2 */
	{0xFFFFF424ul, 0x0000A008ul},                                      /* DCCCNT1CLKSRC_DCC2 */
	{0xFFFFF428ul, 0x00000000ul},                                      /* DCCCNT0CLKSRC_DCC2 */
	{0xFFFFF500ul, 0x00000000ul},                                      /* ESMEEPAPR1 */
	{0xFFFFF508ul, 0x54280BCEul},                                      /* ESMIESR1 */
	{0xFFFFF510ul, 0x00000800ul},                                      /* ESMILSR1 */
	{0xFFFFF534ul, 0x00003FFFul},                                      /* ESMLTCPR */
	{0xFFFFF540ul, 0x00000000ul},                                      /* ESMIEPSR4 */
	{0xFFFFF548ul, 0x40000024ul},                                      /* ESMIESR4 */
	{0xFFFFF550ul, 0x00000000ul},                                      /* ESMILSR4 */
	{0xFFFFFC00ul, 0x00000003ul},                                      /* RTIGCTRL */
	{0xFFFFFC04ul, 0x00000000ul},                                      /* RTITBCTRL */
	{0xFFFFFC80ul, 0x00000001ul},                                      /* RTISETINTENA */
	{0xFFFFFC90ul, 0xA98559DAul},                                      /* RTIDWDCTRL */
	{0xFFFFFC94ul, 0x00000039ul},                                      /* RTIDWDPRLD */
	{0xFFFFFCA4ul, 0x00000005ul},                                      /* RTIWWDRXNCTRL */
	{0xFFFFFCA8ul, 0x00000005ul},                                      /* RTIWWDSIZECTRL */
	{0xFE000008ul, 0x00000000ul},                                      /* CRC_CTRL1 */
	{0xFFFFFDF0ul, 0x0000000Aul},                                      /* PARCTL */
	{0xFFFFFE10ul, 0x00000003ul},                                      /* FIRQPR0_FIQ_IRQ */
	{0xFFFFFE14ul, 0x00000000ul},                                      /* FIRQPR1_FIQ_IRQ */
	{0xFFFFFE18ul, 0x00000000ul},                                      /* FIRQPR2_FIQ_IRQ */
	{0xFFFFFE80ul, 0x00012803ul},                                      /* CHANCTRL0 */
	{0xFFFFFEDCul, 0x03030303ul},                                      /* CHANCTRL23 */
	{0xFFF7C004ul, 0x80140001ul},                                      /* ADOPMODECR_ADC1 */
	{0xFFF7C008ul, 0x00000004ul},                                      /* ADCLOCKCR_ADC1 */
	{0xFFF7C00Cul, 0x00000000ul},                                      /* ADCALCR_ADC1 */
	{0xFFF7C010ul, 0x00010031ul},                                      /* ADEVMODECR_ADC1 */
	{0xFFF7C014ul, 0x00010030ul},                                      /* ADG1MODECR_ADC1 */
	{0xFFF7C018ul, 0x00010038ul},                                      /* ADG2MODECR_ADC1 */
	{0xFFF7C01Cul, 0x00000000ul},                                      /* ADEVSRC_ADC1 */
	{0xFFF7C020ul, 0x00000000ul},                                      /* ADG1SRC_ADC1 */
	{0xFFF7C024ul, 0x00000001ul},                                      /* ADG2SRC_ADC1 */
	{0xFFF7C028ul, 0x00000000ul},                                      /* ADEVINTENA_ADC1 */
	{0xFFF7C02Cul, 0x00000000ul},                                      /* ADG1INTENA_ADC1 */
	{0xFFF7C030ul, 0x00000000ul},                                      /* ADG2INTENA_ADC1 */
	{0xFFF7C058ul, 0x001E001Eul},                                      /* ADBNDCR_ADC1 */
	{0xFFF7C05Cul, 0x00000002ul},                                      /* ADBNDEND_ADC1 */
	{0xFFF7C060ul, 0x00000006ul},                                      /* ADEVSAMP_ADC1 */
	{0xFFF7C064ul, 0x00000006ul},                                      /* ADG1SAMP_ADC1 */
	{0xFFF7C068ul, 0x00000006ul},                                      /* ADG2SAMP_ADC1 */
	{0xFFF7C078ul, 0x00000000ul},                                      /* ADEVSEL_ADC1 */
	{0xFFF7C07Cul, 0x00000000ul},                                      /* ADG1SEL_ADC1 */
	{0xFFF7C080ul, 0x00002121ul},                                      /* ADG2SEL_ADC1 */
	{0xFFF7C180ul, 0x0000000Aul},                                      /* ADPARCR_ADC1 */
	{0xFFF7C204ul, 0x80140001ul},                                      /* ADOPMODECR_ADC2 */
	{0xFFF7C208ul, 0x00000004ul},                                      /* ADCLOCKCR_ADC2 */
	{0xFFF7C20Cul, 0x00000000ul},                                      /* ADCALCR_ADC2 */
	{0xFFF7C210ul, 0x00010030ul},                                      /* ADEVMODECR_ADC2 */
	{0xFFF7C214ul, 0x00010038ul},                                      /* ADG1MODECR_ADC2 */
	{0xFFF7C218ul, 0x00010030ul},                                      /* ADG2MODECR_ADC2 */
	{0xFFF7C21Cul, 0x00000000ul},                                      /* ADEVSRC_ADC2 */
	{0xFFF7C220ul, 0x00000003ul},                                      /* ADG1SRC_ADC2 */
	{0xFFF7C224ul, 0x00000000ul},                                      /* ADG2SRC_ADC2 */
	{0xFFF7C228ul, 0x00000000ul},                                      /* ADEVINTENA_ADC2 */
	{0xFFF7C22Cul, 0x00000000ul},                                      /* ADG1INTENA_ADC2 */
	{0xFFF7C230ul, 0x00000000ul},                                      /* ADG2INTENA_ADC2 */
	{0xFFF7C258ul, 0x00000002ul},                                      /* ADBNDCR_ADC2 */
	{0xFFF7C25Cul, 0x00000002ul},                                      /* ADBNDEND_ADC2 */
	{0xFFF7C260ul, 0x00000006ul},                                      /* ADEVSAMP_ADC2 */
	{0xFFF7C264ul, 0x00000006ul},                                      /* ADG1SAMP_ADC2 */
	{0xFFF7C268ul, 0x00000006ul},                                      /* ADG2SAMP_ADC2 */
	{0xFFF7C278ul, 0x00000000ul},                                      /* ADEVSEL_ADC2 */
	{0xFFF7C27Cul, 0x00002103ul},                                      /* ADG1SEL_ADC2 */
	{0xFFF7C280ul, 0x00000000ul},                                      /* ADG2SEL_ADC2 */
	{0xFFF7C380ul, 0x0000000Aul},                                      /* ADPARCR_ADC2 */
	{0xFFF7B800ul, 0x00060001ul},                                      /* HETGCR_HET1 */
	{0xFFF7B804ul, 0x00000700ul},                                      /* HETPFR_HET1 */
	{0xFFF7B81Cul, 0x00000000ul},                                      /* HETEXC1_HET1 */
	{0xFFF7B824ul, 0x00000000ul},                                      /* HETPRY_HET1 */
	{0xFFF7B82Cul, 0x00000000ul},                                      /* HETAND_HET1 */
	{0xFFF7B834ul, 0x00000000ul},                                      /* HETHRSH_HET1 */
	{0xFFF7B838ul, 0x00000000ul},                                      /* HETXOR_HET1 */
	{0xFFF7B83Cul, 0x00000016ul},                                      /* HETREQENS_HET1 */
	{0xFFF7B844ul, 0x00000010ul},                                      /* HETREQDS_HET1 */
	{0xFFF7B874ul, 0x0000000Aul},                                      /* HETPCR_HET1 */
	{0xFFF7B87Cul, 0x00000000ul},                                      /* HETPPR_HET1 */
	{0xFFF7B88Cul, 0x00000000ul},                                      /* HETLBPSEL_HET1 */
	{0xFFF7B890ul, 0x00050000ul},                                      /* HETLBPDIR_HET1 */
	{0xFFF7B894ul, 0x00000000ul},                                      /* HETPINDIS_HET1 */
	{0xFFF7B900ul, 0x00030001ul},                                      /* HETGCR_HET2 */
	{0xFFF7B904ul, 0x00000400ul},                                      /* HETPFR_HET2 */
	{0xFFF7B91Cul, 0x00000000ul},                                      /* HETEXC1_HET2 */
	{0xFFF7B924ul, 0x00000000ul},                                      /* HETPRY_HET2 */
	{0xFFF7B92Cul, 0x00000000ul},                                      /* HETAND_HET2 */
	{0xFFF7B934ul, 0x000000F4ul},                                      /* HETHRSH_HET2 */
	{0xFFF7B938ul, 0x00000000ul},                                      /* HETXOR_HET2 */
	{0xFFF7B93Cul, 0x00000000ul},                                      /* HETREQENS_HET2 */
	{0xFFF7B944ul, 0x00000000ul},                                      /* HETREQDS_HET2 */
	{0xFFF7B94Cul, 0x00000000ul},                                      /* HETDIR_HET2 */
	{0xFFF7B974ul, 0x0000000Aul},                                      /* HETPCR_HET2 */
	{0xFFF7B97Cul, 0x00000000ul},                                      /* HETPPR_HET2 */
	{0xFFF7B98Cul, 0x00000000ul},                                      /* HETLBPSEL_HET2 */
	{0xFFF7B990ul, 0x00050000ul},                                      /* HETLBPDIR_HET2 */
	{0xFFF7B994ul, 0x00000000ul},                                      /* HETPINDIS_HET2 */
	{0xFFF7A400ul, 0x00010100ul},                                      /* HTU__GC_HTU1 */
	{0xFFF7A44Cul, 0x00000000ul},                                      /* HTU__MP1S_HTU1 */
	{0xFFF7A450ul, 0x00000000ul},                                      /* HTU__MP1E_HTU1 */
	{0xFFF7A500ul, 0x00000000ul},                                      /* HTU__GC_HTU2 */
	{0xFF4E0008ul, 0x00000000ul},                                      /* HTU_IHADDRCT_HTU1 */
	{0xFF4E000Cul, 0x00000000ul},                                      /* HTU_ITCOUNT_HTU1 */
	{0xFFF7BC00ul, 0x00000001ul},                                      /* GIOGCR0 */
	{0xFFF7BC08ul, 0x00000000ul},                                      /* GIOINTDET */
	{0xFFF7BC0Cul, 0x00000000ul},                                      /* GIOPOL */
	{0xFFF7BC34ul, 0x00000000ul},                                      /* GIODIR_A_ */
	{0xFFF7BC54ul, 0x00000000ul},                                      /* GIODIR_B_ */
	{0xFFFFF1B0ul, 0x0F090909ul},                                      /* DMA_DMAMPCTRL */
	{0xFFFFF1B8ul, 0xFF0A0000ul},                                      /* DMA_DMAMPR0S */
	{0xFFFFF1BCul, 0xFF473FFFul},                                      /* DMA_DMAMPR0E */
	{0xFFFFF1C0ul, 0xFCF78C00ul},                                      /* DMA_DMAMPR1S */
	{0xFFFFF1C4ul, 0xFE0001FFul},                                      /* DMA_DMAMPR1E */
	{0xFFFFF1D0ul, 0x00200000ul},                                      /* DMA_DMAMPR3S */
	{0xFFFFF1D4ul, 0xFFFFFFFFul},                                      /* DMA_DMAMPR3E */
	{0xFFF80004ul, 0xFE000068ul},                                      /* DMA_CP00_IDADDR */
	{0xFFF80008ul, 0x00010001ul},                                      /* DMA_CP00_ITCOUNT */
	{0xFFF80010ul, 0x0000F000ul},                                      /* DMA_CP00_CHCTRL */
	{0xFFF80024ul, 0xFE000060ul},                                      /* DMA_CP01_IDADDR */
	{0xFFF80030ul, 0x0000F108ul},                                      /* DMA_CP01_CHCTRL */
	{0xFFF80040ul, 0xFF0C0202ul},                                      /* DMA_CP02_ISADDR */
	{0xFFF80048ul, 0x00010003ul},                                      /* DMA_CP02_ITCOUNT */
	{0xFFF80050ul, 0x0000511Ful},                                      /* DMA_CP02_CHCTRL */
	{0xFFF80054ul, 0x00020004ul},                                      /* DMA_CP02_EIOFF */
	{0xFFF80060ul, 0xFF3A0002ul},                                      /* DMA_CP03_ISADDR */
	{0xFFF80068ul, 0x00010004ul},                                      /* DMA_CP03_ITCOUNT */
	{0xFFF80070ul, 0x0000511Ful},                                      /* DMA_CP03_CHCTRL */
	{0xFFF80074ul, 0x00020004ul},                                      /* DMA_CP03_EIOFF */
	{0xFFF800A4ul, 0xFF4600E8ul},                                      /* DMA_CP05_IDADDR */
	{0xFFF800A8ul, 0x00010001ul},                                      /* DMA_CP05_ITCOUNT */
	{0xFFF800B0ul, 0x0007A101ul},                                      /* DMA_CP05_CHCTRL */
	{0xFFF800C4ul, 0xFCF78C10ul},                                      /* DMA_CP06_IDADDR */
	{0xFFF800C8ul, 0x00040002ul},                                      /* DMA_CP06_ITCOUNT */
	{0xFFF800D0ul, 0x0000511Ful},                                      /* DMA_CP06_CHCTRL */
	{0xFFF800D4ul, 0x00060002ul},                                      /* DMA_CP06_EIOFF */
	{0xFFF800D8ul, 0x01000004ul},                                      /* DMA_CP06_FIOFF */
	{0xFFF80120ul, 0xFF3E00F2ul},                                      /* DMA_CP09_ISADDR */
	{0xFFF80128ul, 0x00010004ul},                                      /* DMA_CP09_ITCOUNT */
	{0xFFF80130ul, 0x0000511Ful},                                      /* DMA_CP09_CHCTRL */
	{0xFFF80134ul, 0x00020004ul},                                      /* DMA_CP09_EIOFF */
	{0xFFF80180ul, 0xFF0A0202ul},                                      /* DMA_CP12_ISADDR */
	{0xFFF80188ul, 0x00010003ul},                                      /* DMA_CP12_ITCOUNT */
	{0xFFF80190ul, 0x0000511Ful},                                      /* DMA_CP12_CHCTRL */
	{0xFFF80194ul, 0x00020004ul},                                      /* DMA_CP12_EIOFF */
/* Register value definitions determined at Link-time */
	{0xFFFFFDF8ul, ((uint32)&VIM_Fallback)},                           /* FBPARERR */
	{0xFFF80044ul, ((uint32)&DMAData_G_str.FastSPI_Cnt_u16[0])},       /* DMA_CP02_IDADDR */
	{0xFFF80064ul, ((uint32)&DMAData_G_str.FastADC_Cnt_u16[0])},       /* DMA_CP03_IDADDR */
	{0xFFF800A0ul, ((uint32)&DMAData_G_str.PWMPeriod_Cnt_u32)},        /* DMA_CP05_ISADDR */
	{0xFFF800C0ul, ((uint32)&DMAData_G_str.PWMCmp_Cnt_u16[0][0])},     /* DMA_CP06_ISADDR */
	{0xFFF80124ul, ((uint32)&DMAData_G_str.SlowADC_Cnt_u16[0])},       /* DMA_CP09_IDADDR */
	{0xFFF80184ul, ((uint32)&DMAData_G_str.SlowSPI_Cnt_u16[0])},       /* DMA_CP12_IDADDR */
	{0xFFFFF1C8ul, ((uint32)&DMAData_G_str)},                          /* DMA_DMAMPR2S */
	{0xFFFFF1CCul, ((uint32)&DMAData_G_str + sizeof(DMAData_G_str) - 1UL)},  /* DMA_DMAMPR2E */
	{0xFFF7A474ul, ((uint32)&Nhet_HtuDataTrq_Cnt_G_str)},              /* HTU__MP0S_HTU1 */
	{0xFFF7A478ul, ((uint32)&Nhet_HtuDataTrq_Cnt_G_str + 60UL)},       /* HTU__MP0E_HTU1 */
	{0xFF4E0010ul, ((uint32)&Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq1_Cnt_u32[0])},  /* HTU_IFADDRA_HTU1 */
	{0xFF4E0020ul, ((uint32)&Nhet_HtuDataTrq_Cnt_G_str.HtuDataTrq2_Cnt_u32[0])},  /* HTU_IFADDRB_HTU1 */
};


#define UDIAG_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
