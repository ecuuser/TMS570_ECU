/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : SpiNxt.h
* Module Description: Nexteer Autosar SPI driver
* Product           : Gen II Plus - EA3.0
* Author            : Abdullah Husain
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue Sep 20 16:33:22 2011
* %version:          4 %
* %derived_by:       nz63rn %
* %date_modified:    Wed Apr 02 10:35:04 2014 % 
*---------------------------------------------------------------------------*/


#ifndef SPINXT_H
#define SPINXT_H

#include "sys_common.h"
#include "Std_Types.h"
#include "mibspi_regs.h"
#include "Spi.h" /* Include Spi.h to provide the Autosar Spi driver definitions for this module */
#include "SpiNxt_Cfg.h"

#define TRANS_GRP_0        0U
#define TRANS_GRP_1        1U

/*! \enum chipSelect
*   \brief Transfer Group Chip Select
*/
enum chipSelect
{
    CS_NONE = 0xFF,
    CS_0    = 0xFE,
    CS_1    = 0xFD,
    CS_2    = 0xFB,
    CS_3    = 0xF7,
    CS_4    = 0xEF,
    CS_5    = 0xDF,
    CS_6    = 0xBF,
    CS_7    = 0x7F
};

/*! \enum triggerEvent
*   \brief Transfer Group Trigger Event
*/
enum triggerEvent
{
    TRG_NEVER   = 0,
    TRG_RISING  = 1,
    TRG_FALLING = 2,
    TRG_BOTH    = 3,
    TRG_HIGH    = 5,
    TRG_LOW     = 6,
    TRG_ALWAYS  = 7
};

/*! \enum mibspiPinSelect
*   \brief mibspi Pin Select
*/
enum mibspiPinSelect
{
    PIN_CS0   = 0,
    PIN_CS1 = 1,
    PIN_CS2 = 2,
    PIN_CS3  = 3,
    PIN_CS4 = 4,
    PIN_CS5    = 5,
    PIN_CS6    = 6,
    PIN_CS7  = 7,
    PIN_ENA = 8,
    PIN_CLK = 9,
    PIN_SIMO = 10,
    PIN_SOMI = 11,
   PIN_SIMO_1 = 17,
   PIN_SIMO_2 = 18,
   PIN_SIMO_3 = 19,
   PIN_SIMO_4 = 20,
   PIN_SIMO_5 = 21,
   PIN_SIMO_6 = 22,
   PIN_SIMO_7 = 23,
   PIN_SOMI_1 = 25,
   PIN_SOMI_2 = 26,
   PIN_SOMI_3 = 27,
   PIN_SOMI_4 = 28,
   PIN_SOMI_5 = 29,
   PIN_SOMI_6 = 30,
   PIN_SOMI_7 = 31
};

/*! \enum triggerSource
*   \brief Transfer Group Trigger Source
*/
enum triggerSource
{
    TRG_DISABLED,
    TRG_GIOA0,
    TRG_GIOA1,
    TRG_GIOA2,
    TRG_GIOA3,
    TRG_GIOA4,
    TRG_GIOA5,
    TRG_GIOA6,
    TRG_GIOA7,
    TRG_HET8,
    TRG_HET10,
    TRG_HET12,
    TRG_HET14,
    TRG_HET16,
    TRG_HET18,
    TRG_TICK
};

#if D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC
/***************************************************************************************************
********** Turns Counter spi configuration section **********
***************************************************************************************************/

/**************************************************************************************************
* Notification function externs
**************************************************************************************************/
extern FUNC( void, AUTOMATIC ) TurnsCounter_TxConfirmation( void );

/**************************************************************************************************
* Defines / Constants
**************************************************************************************************/
/* Channel IDs*/
#define SPI_TCDATA_CH	0U

/* Sequence IDs*/
#define SPI_TCDATA_SEQ  0U

/* Misc Configs */
#define D_SPINXTNUMCHAN_CNT_U16  1U
#define D_SPINXTNUMSEQ_CNT_U16  1U

/* global control config */
#define MIBSPI3_GCR1 ((1UL << 1)  /* CLOKMOD  = internally generated */  \
					|  1UL)       /* MASTER = master */

#define MIBSPI5_GCR1 ((1UL << 1)  /* CLOKMOD  = internally generated */  \
					|  1UL)       /* MASTER = master */

/* delay config */
#define MIBSPI3_DELAY ((255UL << 24) /* C2TDELAY */  \
                    |  (255UL << 16) /* T2CDELAY */  \
                    |  (0UL << 8)    /* T2EDELAY */  \
                    |   0UL)         /* C2EDELAY */

					
#define MIBSPI5_DELAY ((0UL << 24) /* C2TDELAY */  \
                    |  (0UL << 16) /* T2CDELAY */  \
                    |  (0UL << 8)  /* T2EDELAY */  \
                    |   0UL)       /* C2EDELAY */
/* note - mibspi5  C2T and T2C delays are disabled in data format registers */
					
/* chip select default definition - "inactive" value for chip selects */
/* define MIBSPI3_CSDEF, MIBSPI5_CSDEF needed only if there are active high chip selects */
/* default is 0x000000FFUL */
/* if needed define _CSDEF constants with active high bits set to 0 */

/* data format config */
/* must define MIBSPI3_FMT0; define MIBSPI3_FMT1, 2, 3 as needed */
#define MIBSPI3_FMT0 ((255UL << 24)  /* wdelay */            \
                    | (0UL << 23)    /* parity polarity */   \
                    | (0UL << 22)    /* parity enable */     \
                    | (0UL << 21)    /* wait on enable */    \
                    | (0UL << 20)    /* shift direction */   \
					| (0UL << 19)	 /* half duplex enable*/ \
                    | (0UL << 18)    /* disable cs timers */ \
                    | (0UL << 17)    /* clock polarity */    \
                    | (0UL << 16)    /* clock phase */       \
                    | (255UL << 8)   /* baudrate prescale */ \
                    |  8UL)          /* data word length */

/* must define MIBSPI5_FMT0; define MIBSPI5_FMT1, 2, 3 as needed */
#define MIBSPI5_FMT0 ((94UL << 24)  /* wdelay */            \
                    | (0UL << 23)   /* parity polarity */   \
                    | (0UL << 22)   /* parity enable */     \
                    | (0UL << 21)   /* wait on enable */    \
                    | (1UL << 20)   /* shift direction */   \
					| (0UL << 19)	/* half duplex enable*/ \
                    | (1UL << 18)   /* disable cs timers */ \
                    | (0UL << 17)   /* clock polarity */    \
                    | (0UL << 16)   /* clock phase */       \
                    | (130UL << 8)  /* baudrate prescale */ \
                    |  6UL)         /* data word length */
/* MIBSPI5 format 0 wdelay 1.2us: use 94 to give 1.2 usec on 80MHz VLCK and 1.28 usec on 75MHz VCLK */	
/* MIBSPI5 format 0 baudrate prescale 585kHz: use 130 to give 610.687kHz on 80MHz VCLK and 572.519kHz on 75MHz VCLK */

#define MIBSPI5_FMT1 ((94UL << 24)  /* wdelay */            \
                    | (0UL << 23)   /* parity polarity */   \
                    | (0UL << 22)   /* parity enable */     \
                    | (0UL << 21)   /* wait on enable */    \
                    | (1UL << 20)   /* shift direction */   \
					| (0UL << 19)	/* half duplex enable*/ \
                    | (1UL << 18)   /* disable cs timers */ \
                    | (0UL << 17)   /* clock polarity */    \
                    | (0UL << 16)   /* clock phase */       \
                    | (130UL << 8)  /* baudrate prescale */ \
                    |  16UL)        /* data word length */
/* MIBSPI5 format 1 wdelay 1.2us: use 94 to give 1.2 usec on 80MHz VLCK and 1.28 usec on 75MHz VCLK */	
/* MIBSPI5 format 1 baudrate prescale 585kHz: use 130 to give 610.687kHz on 80MHz VCLK and 572.519kHz on 75MHz VCLK */

#define MIBSPI5_FMT2 ((0UL << 24)   /* wdelay */            \
                    | (0UL << 23)   /* parity polarity */   \
                    | (0UL << 22)   /* parity enable */     \
                    | (0UL << 21)   /* wait on enable */    \
                    | (1UL << 20)   /* shift direction */   \
					| (0UL << 19)	/* half duplex enable*/ \
                    | (1UL << 18)   /* disable cs timers */ \
                    | (0UL << 17)   /* clock polarity */    \
                    | (0UL << 16)   /* clock phase */       \
                    | (130UL << 8)  /* baudrate prescale */ \
                    |  11UL)        /* data word length */
/* MIBSPI5 format 2 baudrate prescale 585kHz: use 130 to give 610.687kHz on 80MHz VCLK and 572.519kHz on 75MHz VCLK */

/* transfer group config */
/* must define MIBSPI3_TGCNTRL0; define MIBSPI3_TGCNTRL1, 2, 3, 4, 5, 6, 7 as needed */
/* note that for any transfer group that is used, the following transfer group must  */
/* have the "start buffer" field defined */
#define MIBSPI3_TGCNTRL0 ((0UL << 31)                /* tg enable */      \
                       |  (1UL << 30)                /* oneshot */        \
                       |  (0UL << 29)                /* pcurrent reset */ \
                       |  ((uint32)TRG_BOTH << 20)   /* trigger event */  \
                       |  ((uint32)TRG_TICK << 16)   /* trigger source */ \
                       |  (0UL << 8))                /* start buffer */

#define MIBSPI3_TGCNTRL1 ((0UL << 31)                   /* tg enable */      \
                       |  (0UL << 30)                   /* oneshot */        \
                       |  (0UL << 29)                   /* pcurrent reset */ \
                       |  ((uint32)TRG_NEVER << 20)     /* trigger event */  \
                       |  ((uint32)TRG_DISABLED << 16)  /* trigger source */ \
                       |  (10UL << 8))                  /* start buffer */
					   
#define MIBSPI3_TOTALTGLENGTH (10UL) 					   

/* must define MIBSPI5_TGCNTRL0; define MIBSPI5_TGCNTRL1, 2, 3, 4, 5, 6, 7 as needed */
/* note that for any transfer group that is used, the following transfer group must  */
/* have the "start buffer" field defined */
#define MIBSPI5_TGCNTRL0 ((0UL << 31)                   /* tg enable */      \
                       |  (1UL << 30)                   /* oneshot */        \
                       |  (0UL << 29)                   /* pcurrent reset */ \
                       |  ((uint32)TRG_ALWAYS << 20)    /* trigger event */  \
                       |  ((uint32)TRG_DISABLED << 16)  /* trigger source */ \
                       |  (0UL << 8))                   /* start buffer */

#define MIBSPI5_TGCNTRL1 ((0UL << 31)                   /* tg enable */      \
                       |  (1UL << 30)                   /* oneshot */        \
                       |  (0UL << 29)                   /* pcurrent reset */ \
                       |  ((uint32)TRG_ALWAYS << 20)    /* trigger event */  \
                       |  ((uint32)TRG_DISABLED << 16)  /* trigger source */ \
                       |  (3UL << 8))                   /* start buffer */

#define MIBSPI5_TGCNTRL2 ((0UL << 31)                   /* tg enable */      \
                       |  (1UL << 30)                   /* oneshot */        \
                       |  (0UL << 29)                   /* pcurrent reset */ \
                       |  ((uint32)TRG_ALWAYS << 20)    /* trigger event */  \
                       |  ((uint32)TRG_DISABLED << 16)  /* trigger source */ \
                       |  ((uint32)(3+3) << 8))         /* start buffer */

#define MIBSPI5_TGCNTRL3 ((0UL << 31)                   /* tg enable */      \
                       |  (1UL << 30)                   /* oneshot */        \
                       |  (0UL << 29)                   /* pcurrent reset */ \
                       |  ((uint32)TRG_ALWAYS << 20)    /* trigger event */  \
                       |  ((uint32)TRG_DISABLED << 16)  /* trigger source */ \
                       |  ((uint32)(3+3+10) << 8))      /* start buffer */

#define MIBSPI5_TGCNTRL4 ((0UL << 31)                   /* tg enable */      \
                       |  (1UL << 30)                   /* oneshot */        \
                       |  (0UL << 29)                   /* pcurrent reset */ \
                       |  ((uint32)TRG_ALWAYS << 20)    /* trigger event */  \
                       |  ((uint32)TRG_DISABLED << 16)  /* trigger source */ \
                       |  ((uint32)(3+3+10+4) << 8))    /* start buffer */

#define MIBSPI5_TGCNTRL5 ((0UL << 31)                   /* tg enable */      \
                       |  (1UL << 30)                   /* oneshot */        \
                       |  (0UL << 29)                   /* pcurrent reset */ \
                       |  ((uint32)TRG_ALWAYS << 20)    /* trigger event */  \
                       |  ((uint32)TRG_DISABLED << 16)  /* trigger source */ \
                       |  ((uint32)(3+3+10+4+97) << 8)) /* start buffer */

#define MIBSPI5_TOTALTGLENGTH (3UL + 3UL + 10UL + 4UL + 97UL) 					

/* buffer ram control word init */
#define MIBSPI3_BUFRAMCTRLINIT (((uint16)4U << 13)    /* buffer mode */       \
                             |  ((uint16)0U << 12)    /* hold chip select */  \
                             |  ((uint16)0U << 11)    /* lock transmission */ \
                         	 |  ((uint16)1U << 10)    /* enable WDELAY */     \
                             |  ((uint16)0U << 8)     /* data format */       \
                             |  (uint16)CS_3 )        /* chip select */
				 
							 
/* interrupt configuration */
/* #define MIBSPI3_INTCFG to use interrupts for mibspi3 */
/* do not define MIBSPI3_INTCFG if mibspi3 interrupts not used */
/* #define MIBSPI3_LVL for interrupt level register init value */
/* #define MIBSPI3_INT0 for interrupt enable register init value */

#define MIBSPI3_INTCFG
#define MIBSPI3_LVL ((0UL << 9)  /* TXINT */    \
                 |   (0UL << 8)  /* RXINT */    \
                 |   (0UL << 6)  /* OVRNINT */  \
                 |   (0UL << 4)  /* BITERR */   \
                 |   (0UL << 3)  /* DESYNC */   \
                 |   (0UL << 2)  /* PARERR */   \
                 |   (0UL << 1)  /* TIMEOUT */  \
                 |   (0UL))      /* DLENERR */
				 
/* enable interrupts */
#define MIBSPI3_INT0 ((0UL << 9)  /* TXINT */   \
                 |   (0UL << 8)   /* RXINT */   \
                 |   (0UL << 6)   /* OVRNINT */ \
                 |   (0UL << 4)   /* BITERR */  \
                 |   (0UL << 3)   /* DESYNC */  \
                 |   (0UL << 2)   /* PARERR */  \
                 |   (0UL << 1)   /* TIMEOUT */ \
                 |   (0UL))       /* DLENERR */

/* #define MIBSPI5_INTCFG to use interrupts for mibspi5 */
/* do not define MIBSPI5_INTCFG if mibspi5 interrupts not used */
/* #define MIBSPI5_LVL for interrupt level register */
/* #define MIBSPI5_INT0 for interrupt enable register */
/* NOTE - SpiNxt_Irq.c currently only has mibspi3 interrupt functionality hardcoded for Turns Counter */
/* mibspi5 interrupts would require changes here and in SpiNxt.c (SpiNxt_Init) and SpiNxt_Irq.c */

/* tick counter init */
/* #define MIBSPI3_TICKCNT to tick counter init value for mibspi3 */
/* do not define MIBSPI3_TICKCNT if tick counter initialization not needed */					 

#define MIBSPI3_TICKCNT ((1UL << 31) /* TICKENA */   \
	                   | (0UL << 30) /* RELOAD */    \
	                   | (0UL << 28) /* CLKCTRL */   \
	                   | (16UL))     /* TICKVALUE */
/* configure tick counter to provide the require TurnsCounter Spi message CS to CLK delay 
 * TICKVALUE: Initial delay is 50 uS at SPICLK ticks of 255/80MHz - 
 * the CS to SCLK delay + 1 count to account for unknown state of the spi clock divider
 */					   

/* #define MIBSPI5_TICKCNT to tick counter init value for mibspi5 */								 
/* do not define MIBSPI5_TICKCNT if tick counter initialization not needed */								 

/* Enable Notifications */
/* limited configurability -- only checks for notification on transfer group 0 for mibspi3 */
/* since there is no configurability of mibspi5 interrupts at this time, also no need to   */
/* configure notification for mibspi5 */
/* #define MIBSPI3_TG0_NOTIF to enable notification for transfer group 0 on mibspi3 */						 

/* enable notification for the Turns Counter end of message */
#define MIBSPI3_TG0_NOTIF

/* DIO chip select initialization */
/* #define DIOCS_INIT to initialize DIO chip select pin(s) to inactive level */
/* e.g. #define DIOCS_INIT Dio_WriteChannel(SPI_TCCS, STD_HIGH) */
/* do not define if not needed */
#define DIOCS_INIT Dio_WriteChannel(SPI_TCCS, STD_HIGH)

/* Notification Functions */
#define CALL_MIBSPI3_NOTIFFCN()  TurnsCounter_TxConfirmation()

#elif D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHDIGMSB
/***************************************************************************************************
********** Digital MSB spi configuration section **********
***************************************************************************************************/

/**************************************************************************************************
* Notification function externs
**************************************************************************************************/

/**************************************************************************************************
* Defines / Constants
**************************************************************************************************/
/* Channel IDs*/
#define SPI_DIE1DATA_CH	0U
#define SPI_DIE2DATA_CH 1U

/* Sequence IDs*/
#define SPI_DIE1DATA_SEQ 0U
#define SPI_DIE2DATA_SEQ 1U

/* Misc */
#define D_SPINXTNUMCHAN_CNT_U16  2U
#define D_SPINXTNUMSEQ_CNT_U16  2U
#define D_TGSIZE_CNT_U16 3U

/* global control config */
#define MIBSPI3_GCR1 ((1UL << 1)  /* CLOKMOD  = internally generated */  \
					|  1UL)       /* MASTER = master */

#define MIBSPI5_GCR1 ((1UL << 1)  /* CLOKMOD  = internally generated */  \
					|  1UL)       /* MASTER = master */

/* delay config */
#define MIBSPI3_DELAY ((4UL << 24) /* C2TDELAY */  \
                    |  (1UL << 16) /* T2CDELAY */  \
                    |  (0UL << 8)  /* T2EDELAY */  \
                    |   0UL)       /* C2EDELAY */
/* C2TDELAY = 75ns; T2CDELAY = 25ns */
					
#define MIBSPI5_DELAY ((4UL << 24) /* C2TDELAY */  \
                    |  (1UL << 16) /* T2CDELAY */  \
                    |  (0UL << 8)  /* T2EDELAY */  \
                    |   0UL)       /* C2EDELAY */
/* C2TDELAY = 75ns; T2CDELAY = 25ns */					
					
/* chip select default definition - "inactive" value for chip selects */
/* define MIBSPI3_CSDEF, MIBSPI5_CSDEF needed only if there are active high chip selects */
/* default is 0x000000FFUL */
/* if needed define _CSDEF constants with active high bits set to 0 */


/* data format config */
/* must define MIBSPI3_FMT0; define MIBSPI3_FMT1, 2, 3 as needed */
#define MIBSPI3_FMT0  ((4UL << 24)   /* wdelay */            \
                    |  (0UL << 23)   /* parity polarity */   \
                    |  (0UL << 22)   /* parity enable */     \
                    |  (0UL << 21)   /* wait on enable */    \
                    |  (0UL << 20)   /* shift direction */   \
					|  (0UL << 19)	 /* half duplex enable*/ \
					|  (0UL << 18)	 /* disable cs timers */ \
					|  (1UL << 17)   /* clock polarity */    \
                    |  (0UL << 16)   /* clock phase */       \
                    |  (7UL << 8)    /* baudrate prescale */ \
                    |   16UL)        /* data word length */
/* wdelay = 75ns; even parity; do not transmit parity bit; do not wait on enable; shift MSB first;
 * full duplex; use C2TDELAY and T2CDELAY; clock active low; no phase delay; 
 * SPI clocked at 10MHz; 16 bit transfers
 */ 

/* must define MIBSPI5_FMT0; define MIBSPI5_FMT1, 2, 3 as needed */
#define MIBSPI5_FMT0  ((4UL << 24)   /* wdelay */            \
                    |  (0UL << 23)   /* parity polarity */   \
                    |  (0UL << 22)   /* parity enable */     \
                    |  (0UL << 21)   /* wait on enable */    \
                    |  (0UL << 20)   /* shift direction */   \
					|  (0UL << 19)	 /* half duplex enable*/ \
					|  (0UL << 18)	 /* disable cs timers */ \
					|  (1UL << 17)   /* clock polarity */    \
                    |  (0UL << 16)   /* clock phase */       \
                    |  (7UL << 8)    /* baudrate prescale */ \
                    |   16UL)        /* data word length */
/* wdelay = 75ns; even parity; do not transmit parity bit; do not wait on enable; shift MSB first;
 * full duplex; use C2TDELAY and T2CDELAY; clock active low; no phase delay; 
 * SPI clocked at 10MHz; 16 bit transfers
 */ 

/* transfer group config */
/* must define MIBSPI3_TGCNTRL0; define MIBSPI3_TGCNTRL1, 2, 3, 4, 5, 6, 7 as needed */
/* note that for any transfer group that is used, the following transfer group must  */
/* have the "start buffer" field defined */
#define MIBSPI3_TGCNTRL0 ((0UL << 31)                /* tg enable */      \
                       |  (0UL << 30)                /* oneshot */        \
                       |  (0UL << 29)                /* pcurrent reset */ \
                       |  ((uint32)TRG_RISING << 20) /* trigger event */  \
                       |  ((uint32)TRG_HET14 << 16)  /* trigger source */ \
                       |  (0UL << 8))                /* start buffer */

#define MIBSPI3_TGCNTRL1 ((0UL << 31)                        /* tg enable */      \
                       |  (1UL << 30)                        /* oneshot */        \
                       |  (0UL << 29)                        /* pcurrent reset */ \
                       |  ((uint32)TRG_FALLING << 20)        /* trigger event */  \
                       |  ((uint32)TRG_HET14 << 16)          /* trigger source */ \
                       |  ((uint32)(D_TGSIZE_CNT_U16) << 8)) /* start buffer */

#define MIBSPI3_TGCNTRL2 ((0UL << 31)                           /* tg enable */      \
                       |  (0UL << 30)                           /* oneshot */        \
                       |  (0UL << 29)                           /* pcurrent reset */ \
                       |  ((uint32)TRG_ALWAYS << 20)            /* trigger event */  \
                       |  ((uint32)TRG_DISABLED << 16)          /* trigger source */ \
                       |  ((uint32)(2U*D_TGSIZE_CNT_U16) << 8)) /* start buffer */
					   
#define MIBSPI3_TOTALTGLENGTH ((uint32)(2U*D_TGSIZE_CNT_U16)) 					   

/* must define MIBSPI5_TGCNTRL0; define MIBSPI5_TGCNTRL1, 2, 3, 4, 5, 6, 7 as needed */
/* note that for any transfer group that is used, the following transfer group must  */
/* have the "start buffer" field defined */
#define MIBSPI5_TGCNTRL0 ((0UL << 31)                /* tg enable */      \
                       |  (0UL << 30)                /* oneshot */        \
                       |  (0UL << 29)                /* pcurrent reset */ \
                       |  ((uint32)TRG_RISING << 20) /* trigger event */  \
                       |  ((uint32)TRG_HET18 << 16)  /* trigger source */ \
                       |  (0UL << 8))                /* start buffer */

#define MIBSPI5_TGCNTRL1 ((0UL << 31)                        /* tg enable */      \
                       |  (1UL << 30)                        /* oneshot */        \
                       |  (0UL << 29)                        /* pcurrent reset */ \
                       |  ((uint32)TRG_FALLING << 20)        /* trigger event */  \
                       |  ((uint32)TRG_HET18 << 16)          /* trigger source */ \
                       |  ((uint32)(D_TGSIZE_CNT_U16) << 8)) /* start buffer */

#define MIBSPI5_TGCNTRL2 ((0UL << 31)                           /* tg enable */      \
                       |  (0UL << 30)                           /* oneshot */        \
                       |  (0UL << 29)                           /* pcurrent reset */ \
                       |  ((uint32)TRG_ALWAYS << 20)            /* trigger event */  \
                       |  ((uint32)TRG_DISABLED << 16)          /* trigger source */ \
                       |  ((uint32)(2U*D_TGSIZE_CNT_U16) << 8)) /* start buffer */
					   
#define MIBSPI5_TOTALTGLENGTH ((uint32)(2U*D_TGSIZE_CNT_U16)) 					   

/* buffer ram control word init */
/* define if control word initialization is needed */
#define MIBSPI3_BUFRAMCTRLINIT (((uint16)4U << 13)     /* buffer mode */       \
                             |  ((uint16)0U << 12)     /* hold chip select */  \
                             |  ((uint16)1U << 11)     /* lock transmission */ \
                         	 |  ((uint16)1U << 10)     /* enable WDELAY */     \
                             |  ((uint16)0U << 8)      /* data format */       \
                             |  (uint16)CS_0)          /* chip select */
/* continuous buffer mode; do not hold cs; lock transmission; use wdelay; data format 0; use CS0 */

#define MIBSPI5_BUFRAMCTRLINIT (((uint16)4U << 13)     /* buffer mode */       \
                             |  ((uint16)0U << 12)     /* hold chip select */  \
                             |  ((uint16)1U << 11)     /* lock transmission */ \
                         	 |  ((uint16)1U << 10)     /* enable WDELAY */     \
                             |  ((uint16)0U << 8)      /* data format */       \
                             |  (uint16)CS_0)          /* chip select */
/* continuous buffer mode; do not hold cs; lock transmission; use wdelay; data format 0; use CS0 */							 
							 
/* interrupt configuration */
/* #define MIBSPI3_INTCFG to use interrupts for mibspi3 */
/* do not define MIBSPI3_INTCFG if mibspi3 interrupts not used */
/* #define MIBSPI3_LVL for interrupt level register init value */
/* #define MIBSPI3_INT0 for interrupt enable register init value */
/* NOTE - SpiNxt_Irq.c currently only has mibspi3 interrupt functionality hardcoded for Turns Counter */
/* mibspi3 interrupts for DigMsb would require changes here and in SpiNxt_Irq.c */

/* #define MIBSPI5_INTCFG to use interrupts for mibspi5 */
/* do not define MIBSPI5_INTCFG if mibspi5 interrupts not used */
/* #define MIBSPI5_LVL for interrupt level register */
/* #define MIBSPI5_INT0 for interrupt enable register */
/* NOTE - SpiNxt_Irq.c currently only has mibspi3 interrupt functionality hardcoded for Turns Counter */
/* mibspi5 interrupts for DigMsb would require changes here and in SpiNxt.c (SpiNxt_Init) and SpiNxt_Irq.c */

/* tick counter init */
/* #define MIBSPI3_TICKCNT to tick counter init value for mibspi3 */
/* do not define MIBSPI3_TICKCNT if tick counter initialization not needed */	
#define MIBSPI3_TICKCNT  0UL  /* disable tick counter */				 

/* #define MIBSPI5_TICKCNT to tick counter init value for mibspi5 */								 
/* do not define MIBSPI5_TICKCNT if tick counter initialization not needed */								 
#define MIBSPI5_TICKCNT  0UL  /* disable tick counter */

/* DMA control init */
/* conditionally #define DMA control init values if DMA is being used */
#if (BC_SPINXT_USEDMA == STD_ON)

/* #define MIBSPI3_DMACTRL0 to DMACTRL[0] init value for mibspi3 */
#define MIBSPI3_DMACTRL0     ((0UL << 31)   	/* oneshot      */       \
							| ((uint32)(D_TGSIZE_CNT_U16-1U) << 24) /* Buffer ID    */       \
							| (1UL << 20)   	/* RXDMA Map    */       \
							| (0UL << 16)   	/* TXDMA Map    */       \
	                       	| (1UL << 15)   	/* RXDMA Enable */       \
	                       	| (0UL << 14)   	/* TXDMA Enable */       \
	                       	| (0UL << 13)		/* NoBreak      */       \
	                       	| (0UL << 8))	/* ICOUNT */

/* #define MIBSPI5_DMACTRL0 to DMACTRL[0] init value for mibspi5 */
#define MIBSPI5_DMACTRL0     ((0UL << 31)   	/* oneshot      */       \
							| ((uint32)(D_TGSIZE_CNT_U16-1U) << 24) /* Buffer ID    */       \
							| (1UL << 20)   	/* RXDMA Map    */       \
							| (0UL << 16)   	/* TXDMA Map    */       \
	                       	| (1UL << 15)   	/* RXDMA Enable */       \
	                       	| (0UL << 14)   	/* TXDMA Enable */       \
	                       	| (0UL << 13)		/* NoBreak      */       \
	                       	| (0UL << 8))	/* ICOUNT */

#endif /* BC_SPINXT_USEDMA */

/* Enable Notifications */
/* limited configurability -- only checks for notification on transfer group 0 for mibspi3 */
/* since there is no configurability of mibspi5 interrupts at this time, also no need to   */
/* configure notification for mibspi5 */
/* #define MIBSPI3_TG0_NOTIF to enable notification for transfer group 0 on mibspi3 */							 


/* DIO chip select initialization */
/* #define DIOCS_INIT to initialize DIO chip select pin(s) to inactive level */
/* e.g. #define DIOCS_INIT Dio_WriteChannel(SPI_TCCS, STD_HIGH) */
/* do not define if not needed */


/* Notification Functions -- define blank if unused*/
#define CALL_MIBSPI3_NOTIFFCN()


#endif /* #if D_SPINXTUSEWITH */


/* ISR notification for SpiNxt_Irq to core SpiNxt driver 
 *  The notification functions are not intended for use outside the SpiNxt BSW
 */
FUNC(void, SPI_CODE) mibspiGroupNotification(const mibspictrlregs_t *mibspi, uint32 group);
FUNC(void, SPI_CODE) mibspiNotification(const mibspictrlregs_t *mibspi, uint32 flags);


/* MIBSPI Interface Functions 
 * These Halcogen driver functions are externed for use in CDD instances that either
 * require the additional flexibility offered by the API, or for legacy reasons were
 * implemented prior to the creation of the Autosar Api for this BSW.
 */

FUNC(void, SPI_CODE) mibspiSetData(const mibspictrlregs_t *mibspi, uint32 group, const uint16 data[]);
FUNC(void, SPI_CODE) mibspiSetCtrlData(const mibspictrlregs_t *mibspi, uint32 group, const uint32 data[]);
FUNC(uint32, SPI_CODE) mibspiGetData(const mibspictrlregs_t *mibspi, uint32 group, uint16 data[]);
FUNC(void, SPI_CODE) mibspiTransfer(mibspictrlregs_t *mibspi, uint32 group);

/* AUTOSAR API 
 * This is a subset of the API specified by Autosar.  The subset was selected based on
 * the system funcitonality required at the time of implementation.
 */
void SpiNxt_Init(void);
FUNC(Std_ReturnType, SPI_CODE) SpiNxt_AsyncTransmit( Spi_SequenceType Sequence );
FUNC(Spi_SeqResultType, SPI_CODE) SpiNxt_GetSequenceResult( Spi_SequenceType Sequence );
FUNC(Std_ReturnType, SPI_CODE) SpiNxt_SetupEB
(
    Spi_ChannelType Channel,
    P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) SrcDataBufferPtr,
    P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr,
    Spi_NumberOfDataType Length
);

#endif

/***********************************************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description                                              SCR #
-------   -------  --------  -------------------------------------------------------------------  ----------
09/20/10   1.0      AH        Initial file creation
							  Generated by Halcogen mibspi.c v1.01.000
03/09/12   2		JJW		  Added Autosar Spi Api
							  Corrected MISRA violations, which included changing the
							  Halcogen generated JavaDoc commenting to a Doxygen commenting
							  style to avoid characters MISRA considers illegal.
08/02/13   3        KMC       Changes for configurability of SpiNxt for Turns Counter or Digital
                              MSB (CR 8834) and to fix anomaly 4713 (CR 8683) and QAC updates. 
							  Update to use StdDef mibspi register type definitions.
04/02/14	4		KMC		  Updated for ES-50A v005 and to fix anomaly 5929: added transfer        11435
                              group 1, changed initialization of transfer group 0, added 
                              initialization for SPI DMA control.							  
*************************************************************************************************************/
