/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : SpiNxt.c
* Module Description: SPI driver: Partial Autosar API implementation
* Product           : Gen II Plus - EA3.0
* Author            : Abdullah Husain
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Tue Sep 20 16:33:22 2011
* %version:          10 %
* %derived_by:       nz63rn %
* %date_modified:    Wed Apr 02 10:35:04 2014 % 
*---------------------------------------------------------------------------*/

#include "SpiNxt.h"
#include "Dio.h"
#include "SchM_SpiNxt.h"


/* PRQA S 303 ++ 
 * MISRA Rule 11.3 violation. This deviation is required for register access.  The rule is suppressed for the entire 
 * file due to the frequency of usage throughout this driver.  Annotation at each deviation unnecessarily clutters the file.
 */


/* Local Function Prototypes*/
#if (D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC) 
/* these static functions are only called from code that is conditionally compiled for D_SPINXT_USEWITHTC */
/* therefore the function declarations are conditionally compiled to avoid QAC warning when compiled for other than D_SPINXT_USEWITHTC */
static FUNC(void, SPI_CODE) mibspiEnableGroupNotification(mibspictrlregs_t *mibspi, uint32 group, uint32 level);
static FUNC(void, SPI_CODE) mibspiSetData8(const mibspictrlregs_t *mibspi, uint32 group, const uint8 data[]);
static FUNC(uint32, SPI_CODE) mibspiGetData8(const mibspictrlregs_t *mibspi, uint32 group, uint8 data[]);
#endif

/* Module internal structure typedef */
typedef struct {
	P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) SrcDataBufferPtr;
	P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr;
	VAR(Spi_NumberOfDataType, AUTOMATIC) Length;
}EbCfg_Type;

/* Module Internal */
#define SPINXT_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

#if (D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC)
static VAR(EbCfg_Type, AUTOMATIC) ExtBufCfg_Str[D_SPINXTNUMCHAN_CNT_U16];
#endif

static VAR (Spi_SeqResultType, AUTOMATIC) SeqResult_Enum[D_SPINXTNUMSEQ_CNT_U16];
#define SPINXT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

#define SPINXT_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */
/* AUTOSAR Compliant Spi API */


/*! \fn Std_ReturnType SpiNxt_SetupEB(Spi_ChannelType Channel, Spi_DataType SrcDataBufferPtr, Spi_DataType DesDataBufferPtr, Spi_NumberOfDataType Length)
*   \brief Service to setup the buffers and the length of data for the EB SPI Handler/Driver Channel specified.
*   \param[in] Channel - Channel ID.
*   \param[in] SrcDataBufferPtr - Pointer to source data bufer.
*   \param[in] DesDataBufferPtr  - pointer to destination data buffer in RAM.
*   \param[in] Length  - Length of the data to be transmitted from SrcdataBufferPtr and/or received from DesDataBufferPtr Min.: 1 Max.: Max of data specified at configuration for this channel
*
*   \return Std_ReturnType 
*              E_OK: Setup command has been accepted
*              E_NOT_OK: Setup command has not been accepted
*
*   This driver function is a minimalist implementation intended for use with the Turns Counter component.

*/
FUNC(Std_ReturnType, SPI_CODE) SpiNxt_SetupEB
(
    VAR(Spi_ChannelType, AUTOMATIC) Channel,
    P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) SrcDataBufferPtr,
    P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr,
    VAR(Spi_NumberOfDataType, AUTOMATIC) Length
)

{
#if D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC
	/* TODO: Provide error checking and reporting */	
	ExtBufCfg_Str[Channel].SrcDataBufferPtr = SrcDataBufferPtr;
	ExtBufCfg_Str[Channel].DesDataBufferPtr = DesDataBufferPtr;
	ExtBufCfg_Str[Channel].Length = Length;
	return( E_OK );
#else
	/* return not ok if called with D_SPINXTUSEWITH_CNT_ENUM != D_SPINXT_USEWITHTC */
	return ( E_NOT_OK );
#endif /* D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC */
}

/*! \fn Spi_SeqResultType SpiNxt_GetSequenceResult(Spi_SequenceType Sequence)
*   \brief This service returns the last transmission result of the specified Sequence.
*   \param[in] Sequence - Sequence ID. An invalid sequence ID will return an undefined result.
*
*   \return Spi_SeqResultType
*
*   This driver function is a minimalist implementation with no error checking
*/
FUNC(Spi_SeqResultType, SPI_CODE) SpiNxt_GetSequenceResult( Spi_SequenceType Sequence )
{
	return( SeqResult_Enum[Sequence]);
}


/*! \fn Std_ReturnType SpiNxt_AsyncTransmit(Spi_SequenceType Sequence)
*   \brief Service to transmit data on the SPI bus.
*   \param[in] Sequence - Sequence ID.
*
*   \return Std_ReturnType 
*              E_OK: Transmission command has been accepted
*              E_NOT_OK: Transmission command has not been accepted
*
*   This driver function is a minimalist implementation intended for use with the Turns Counter component.  
*   It assumes one-to-one channel-to-sequence correspondence.
*/
FUNC(Std_ReturnType, SPI_CODE) SpiNxt_AsyncTransmit( Spi_SequenceType Sequence )
{	
	Std_ReturnType result_T_Cnt;

#if D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC

	/* Reset the TICKCNT trigger register to provide the appropriate CS to SPI Data delay.
	 * The TICKCNT trigger is required because the HW CS to CLK delay does not have a large
	 * enough range to meet the TC requirements
	 */
	
	/* Start new message sequence if last transfer is complete (i.e. Sequence is not PENDING)
	 * and sequence 0 was requested.  This driver is an incomplete implementation that only
	 * supports sequence 0 at this time for the TurnsCounter on mibSPI3
	 */
	if((0U == Sequence) && ( SPI_SEQ_PENDING != SeqResult_Enum[Sequence])){

		SeqResult_Enum[Sequence] = SPI_SEQ_PENDING;

		/* Load the transfer group with the new data */
		mibspiSetData8( mibspiREG3, TRANS_GRP_0, (ExtBufCfg_Str[Sequence].SrcDataBufferPtr) );
	 
		/* Provide an exclusive area around the events that need to be synchronized */
		SchM_Enter_SpiNxt(SPINXT_EXCLUSIVE_AREA_0);
		
		Dio_WriteChannel(SPI_TCCS, STD_LOW);
		/* Force TICKCNT Reload to synchronize counter with Software CS assertion */
		mibspiREG3->TICKCNT |= (1UL << 30U);  /* RELOAD */
		
		/* Enable the transfer group to begin transfer upon the expiration of the TICKCNT period */
		mibspiTransfer( mibspiREG3, TRANS_GRP_0 );
		
		SchM_Exit_SpiNxt(SPINXT_EXCLUSIVE_AREA_0);
		
		result_T_Cnt = E_OK;
	}
	else{
		result_T_Cnt = E_NOT_OK;
	}

#else	
	/* return not ok if called with D_SPINXTUSEWITH_CNT_ENUM != D_SPINXT_USEWITHTC */
	result_T_Cnt = E_NOT_OK;

#endif /* D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC */

	return( result_T_Cnt );
}



/* End AUTOSAR Api */

/*! \fn void SpiNxt_Init(void)
*   \brief Initializes the SpiNxt Driver
*
*    This is a minimalist implementation of the initialization routine which initializes
*    MIBSPI3 and MIBSPI5 for the Turns Counter or the Digital MSB; differences are handled 
*    through constants defined in SpiNxt_Cfg.h (SpiNxt_Cfg.h.tt).
*/
FUNC(void, SPI_CODE) SpiNxt_Init(void)
{
VAR(uint32, AUTOMATIC) i;

     /*! \b initialise \b MIBSPI3 */

    /** bring MIBSPI3 out of reset */
    mibspiREG3->GCR0 = 1U;

    /** enable MIBSPI3 multibuffered mode and enable buffer RAM */
    mibspiREG3->MIBSPIE = 1U;

    /** MIBSPI3 master mode and clock configuration */
    mibspiREG3->GCR1 = MIBSPI3_GCR1;

	/* disable all interrupts */
	mibspiREG3->INT0 = 0U;				
	
    /** MIBSPI3 enable pin configuration */
    mibspiREG3->ENAHIGHZ = 0U;  /* ENABLE HIGHZ */

    /** - Delays */
    mibspiREG3->DELAY = MIBSPI3_DELAY;
	
	/* chip select default definition */
	#ifdef MIBSPI3_CSDEF
		mibspiREG3->CSDEF = MIBSPI3_CSDEF;
	#endif

    /** - Data Format 0 */
    mibspiREG3->FMT0 = MIBSPI3_FMT0;
    /** - Data Format 1 */
	#ifdef MIBSPI3_FMT1
		mibspiREG3->FMT1 = MIBSPI3_FMT1;
	#endif
    /** - Data Format 2 */
	#ifdef MIBSPI3_FMT2
		mibspiREG3->FMT2 = MIBSPI3_FMT2;
	#endif
    /** - Data Format 3 */
	#ifdef MIBSPI3_FMT3
		mibspiREG3->FMT3 = MIBSPI3_FMT3;
	#endif
	
    /** - wait for buffer initialisation complete before accessing MibSPI registers */
    while ((mibspiREG3->BUFINIT) != 0U) { /* wait */ }

    /** - initialise transfer groups */
    mibspiREG3->TGCTRL[0] = MIBSPI3_TGCNTRL0;
	#ifdef MIBSPI3_TGCNTRL1
		mibspiREG3->TGCTRL[1] = MIBSPI3_TGCNTRL1;
	#endif
	#ifdef MIBSPI3_TGCNTRL2
		mibspiREG3->TGCTRL[2] = MIBSPI3_TGCNTRL2;
	#endif
	#ifdef MIBSPI3_TGCNTRL3
		mibspiREG3->TGCTRL[3] = MIBSPI3_TGCNTRL3;
	#endif
	#ifdef MIBSPI3_TGCNTRL4
		mibspiREG3->TGCTRL[4] = MIBSPI3_TGCNTRL4;
	#endif
	#ifdef MIBSPI3_TGCNTRL5
		mibspiREG3->TGCTRL[5] = MIBSPI3_TGCNTRL5;
	#endif
	#ifdef MIBSPI3_TGCNTRL6
		mibspiREG3->TGCTRL[6] = MIBSPI3_TGCNTRL6;
	#endif
	#ifdef MIBSPI3_TGCNTRL7
		mibspiREG3->TGCTRL[7] = MIBSPI3_TGCNTRL7;
	#endif

    mibspiREG3->LTGPEND =  MIBSPI3_TOTALTGLENGTH - 1UL;

	/** - initialise buffer ram */
	#ifdef MIBSPI3_BUFRAMCTRLINIT 
		i = 0U;

        while (i < MIBSPI3_TOTALTGLENGTH)
        {
            mibspiRAM3->tx[i++].control = (uint16)MIBSPI3_BUFRAMCTRLINIT;  
        }
	#endif

    /** - interrupt configuration */
	#ifdef MIBSPI3_INTCFG
		/** - set interrupt levels */
		mibspiREG3->LVL = MIBSPI3_LVL;

		/** - clear any pending interrupts */
		mibspiREG3->FLG = 0xFFFFU;

		/** - enable interrupts */
		mibspiREG3->INT0 = MIBSPI3_INT0;
	#endif

    /** - configure tick counter */
	#ifdef MIBSPI3_TICKCNT
		mibspiREG3->TICKCNT = MIBSPI3_TICKCNT;
    #endif
	
	/** configure DMA control */
	#ifdef MIBSPI3_DMACTRL0
		mibspiREG3->DMACTRL[0] = MIBSPI3_DMACTRL0;
	#endif

    /** - Finally start MIBSPI3 */
    mibspiREG3->ENA = 1U;
    
    /*! \b initialise \b MIBSPI5 */

    /** bring MIBSPI5 out of reset */
    mibspiREG5->GCR0 = 1U;

    /** enable MIBSPI5 multibuffered mode and enable buffer RAM */
    mibspiREG5->MIBSPIE = 1U;

    /** MIBSPI5 master mode and clock configuration */
    mibspiREG5->GCR1 = MIBSPI5_GCR1;

	/* disable all interrupts */
	mibspiREG5->INT0 = 0U;				
	
    /** MIBSPI5 enable pin configuration */
    mibspiREG5->ENAHIGHZ = 0U;  /* ENABLE HIGHZ */

    /** - Delays */
    mibspiREG5->DELAY = MIBSPI5_DELAY;

	/* chip select default definition */
	#ifdef MIBSPI5_CSDEF
		mibspiREG5->CSDEF = MIBSPI5_CSDEF;
	#endif

    /** - Data Format 0 */
    mibspiREG5->FMT0 = MIBSPI5_FMT0;
    /** - Data Format 1 */
	#ifdef MIBSPI5_FMT1
		mibspiREG5->FMT1 = MIBSPI5_FMT1;
	#endif
    /** - Data Format 2 */
	#ifdef MIBSPI5_FMT2
		mibspiREG5->FMT2 = MIBSPI5_FMT2;
	#endif
    /** - Data Format 3 */
	#ifdef MIBSPI5_FMT3
		mibspiREG5->FMT3 = MIBSPI5_FMT3;
	#endif

    /** - wait for buffer initialisation complete before accessing MibSPI registers */
    while ((mibspiREG5->BUFINIT) != 0U) { /* wait */ }


    /** - initialise transfer groups */
    mibspiREG5->TGCTRL[0] = MIBSPI5_TGCNTRL0;
	#ifdef MIBSPI5_TGCNTRL1
		mibspiREG5->TGCTRL[1] = MIBSPI5_TGCNTRL1;
	#endif
	#ifdef MIBSPI5_TGCNTRL2
		mibspiREG5->TGCTRL[2] = MIBSPI5_TGCNTRL2;
	#endif
	#ifdef MIBSPI5_TGCNTRL3
		mibspiREG5->TGCTRL[3] = MIBSPI5_TGCNTRL3;
	#endif
	#ifdef MIBSPI5_TGCNTRL4
		mibspiREG5->TGCTRL[4] = MIBSPI5_TGCNTRL4;
	#endif
	#ifdef MIBSPI5_TGCNTRL5
		mibspiREG5->TGCTRL[5] = MIBSPI5_TGCNTRL5;
	#endif
	#ifdef MIBSPI5_TGCNTRL6
		mibspiREG5->TGCTRL[6] = MIBSPI5_TGCNTRL6;
	#endif
	#ifdef MIBSPI5_TGCNTRL7
		mibspiREG5->TGCTRL[7] = MIBSPI5_TGCNTRL7;
	#endif

    mibspiREG5->LTGPEND =  MIBSPI5_TOTALTGLENGTH - 1UL;

	/** - initialise buffer ram */
	#ifdef MIBSPI5_BUFRAMCTRLINIT 
		i = 0U;

        while (i < MIBSPI5_TOTALTGLENGTH)
        {
            mibspiRAM5->tx[i++].control = MIBSPI5_BUFRAMCTRLINIT;  
        }
	#endif

    /** - interrupt configuration */
	/* NOTE - SpiNxt_Irq.c currently only has mibspi3 interrupt functionality hardcoded for Turns Counter */
	/* mibspi5 interrupts would require changes here and in SpiNxt_Irq.c */

    /** - configure tick counter */
	#ifdef MIBSPI5_TICKCNT
		mibspiREG5->TICKCNT = MIBSPI5_TICKCNT;
    #endif

	/** configure DMA control */
	#ifdef MIBSPI5_DMACTRL0
		mibspiREG5->DMACTRL[0] = MIBSPI5_DMACTRL0;
	#endif

  /** - Finally start MIBSPI5 */
    mibspiREG5->ENA = 1U;
	
  /* Enable Configured Notifications: */
  /* limited configurability -- only checks for notification on transfer group 0 for mibspi3 */
  /* since there is no configurability of mibspi5 interrupts at this time, also no need to   */
  /* configure notification for mibspi5 */
  #ifdef MIBSPI3_TG0_NOTIF
		mibspiEnableGroupNotification(mibspiREG3, TRANS_GRP_0, 0U);
		mibspiEnableGroupNotification(mibspiREG3, TRANS_GRP_0, 1U);
  #endif
  
   /* Init DIO Chip selects to inactive */
  #ifdef DIOCS_INIT
		DIOCS_INIT;
  #endif


  /* Init Sequence Statuses per Autosar requirements */
  for (i = 0U; i < D_SPINXTNUMSEQ_CNT_U16; i++)
  {
		SeqResult_Enum[i] = SPI_SEQ_OK;
  }
 
}



/*! \fn void mibspiSetData(mibspictrlregs_t *mibspi, uint32 group, uint16 data[])
*   \brief Set Buffer Data
*   \param[in] mibspi   - Spi module base address
*   \param[in] group - Transfer group (0..7)
*   \param[in] data  - new data for transfer group
*
*   This function updates the data for the specified transfer group,
*   the length of the data must match the length of the transfer group.
*/
FUNC(void, SPI_CODE) mibspiSetData(const mibspictrlregs_t *mibspi, uint32 group, const uint16 data[])
{

    P2VAR(mibspiRAM_t, AUTOMATIC, AUTOMATIC) ram = ((mibspi == mibspiREG1) ? mibspiRAM1 : ((mibspi == mibspiREG3) ? mibspiRAM3 : mibspiRAM5));
    VAR(uint32, AUTOMATIC) start  = (mibspi->TGCTRL[group] >> 8) & 0xFFU;
    VAR(uint32, AUTOMATIC) end    = (group == 7UL) ? (mibspi->LTGPEND + 1UL) : ((uint32)(mibspi->TGCTRL[group+1U] >> 8) & 0xFFUL);
	VAR(uint16, AUTOMATIC) i = 0U;
	
    if (end < start) {end = 128U;}

    while (start < end)
    {
        ram->tx[start].data = data[i];
		i++;
        start++;
    }
}

/*! \fn void mibspiSetData8(mibspictrlregs_t *mibspi, uint32 group, uint8 data[])
*   \brief Set Buffer Data from 8bit source array
*   \param[in] mibspi   - Spi module base address
*   \param[in] group - Transfer group (0..7)
*   \param[in] data  - new data for transfer group
*
*   This function updates the data for the specified transfer group,
*   the length of the data must match the length of the transfer group.
*/
#if (D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC) 
/* this static function is only called from code that is conditionally compiled for D_SPINXT_USEWITHTC */
/* therefore this function is conditionally compiled to avoid QAC warning when compiled for other than D_SPINXT_USEWITHTC */
static FUNC(void, SPI_CODE) mibspiSetData8(const mibspictrlregs_t *mibspi, uint32 group, const uint8 data[])
{
    P2VAR(mibspiRAM_t, AUTOMATIC, AUTOMATIC) ram = (mibspi == mibspiREG1) ? mibspiRAM1 : ((mibspi == mibspiREG3) ? mibspiRAM3 : mibspiRAM5);
    VAR(uint32, AUTOMATIC) start  = (mibspi->TGCTRL[group] >> 8) & 0xFFU;
    VAR(uint32, AUTOMATIC) end    = (group == 7UL) ? (mibspi->LTGPEND + 1UL) : ((uint32)(mibspi->TGCTRL[group+1U] >> 8) & 0xFFUL);
	VAR(uint16, AUTOMATIC) i = 0U;

    if (end < start) {end = 128U;}

    while (start < end)
    {
        ram->tx[start].data = (uint16)(data[i]);
		i++;
        start++;
    }
}
#endif

/*! \fn void mibspiSetCtrlData(mibspictrlregs_t *mibspi, uint32 group, uint32 data[])
*   \brief Set Buffer Control word and Data
*   \param[in] mibspi   - Spi module base address
*   \param[in] group - Transfer group (0..7)
*   \param[in] data  - new control word and data for transfer group as 32 bits.
*                      control word is the the upper 16 bits and data is the lower.
*
*   This function updates the data for the specified transfer group,
*   the length of the data must match the length of the transfer group.
*/
FUNC(void, SPI_CODE) mibspiSetCtrlData(const mibspictrlregs_t *mibspi, uint32 group, const uint32 data[])
{
    P2VAR(mibspiRAM_t, AUTOMATIC, AUTOMATIC) ram = (mibspi == mibspiREG1) ? mibspiRAM1 : ((mibspi == mibspiREG3) ? mibspiRAM3 : mibspiRAM5);
    VAR(uint32, AUTOMATIC) start  = (mibspi->TGCTRL[group] >> 8) & 0xFFU;
    VAR(uint32, AUTOMATIC) end    = (group == 7UL) ? (mibspi->LTGPEND + 1UL) : ((uint32)(mibspi->TGCTRL[group+1U] >> 8) & 0xFFUL);
	VAR(uint16, AUTOMATIC) i = 0U;

    if (end < start) {end = 128U;}

    while (start < end)
    {
        ram->tx[start].data = (uint16)(data[i]);
        ram->tx[start].control = (uint16)((data[i])>>16U);
        i++;
        start++;
    }
}

/*! \fn void mibspiGetData8(mibspictrlregs_t *mibspi, uint32 group, uint8 data[])
*   \brief Retrieves Buffer Data from receive buffer
*   \param[in]  mibspi   - Spi module base address
*   \param[in]  group - Transfer group (0..7)
*   \param[out] data  - pointer to data array
*
*   \return error flags from data buffer, if there was a receive error on
*           one of the buffers this will be reflected in the return value.
*
*   This function transfers the data from the specified transfer group recieve
*   buffers to the data array,  the length of the data must match the length 
*   of the transfer group.
*/
#if (D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC) 
/* this static function is only called from code that is conditionally compiled for D_SPINXT_USEWITHTC */
/* therefore this function is conditionally compiled to avoid QAC warning when compiled for other than D_SPINXT_USEWITHTC */
static FUNC(uint32, SPI_CODE) mibspiGetData8(const mibspictrlregs_t *mibspi, uint32 group, uint8 data[])
{
    P2VAR(mibspiRAM_t, AUTOMATIC, AUTOMATIC) ram = (mibspi == mibspiREG1) ? mibspiRAM1 : ((mibspi == mibspiREG3) ? mibspiRAM3 : mibspiRAM5);
    VAR(uint32, AUTOMATIC) start  = (mibspi->TGCTRL[group] >> 8) & 0xFFU;
    VAR(uint32, AUTOMATIC) end    = (group == 7UL) ? (mibspi->LTGPEND + 1UL) : ((uint32)(mibspi->TGCTRL[group+1U] >> 8) & 0xFFUL);
    VAR(uint32, AUTOMATIC) flags_Cnt_T_u32  = 0U;
	VAR(uint16, AUTOMATIC) i = 0U;
	
    if (end < start) {end = 128U;}

    while (start < end)
    {
        flags_Cnt_T_u32  |= ram->rx[start].flags;
        data[i] = (uint8)ram->rx[start].data;
		i++;
        start++;
    }
    return (flags_Cnt_T_u32 >> 8) & 0x5FU;
}
#endif

/*! \fn uint32 mibspiGetData(mibspictrlregs_t *mibspi, uint32 group, uint16 data[])
*   \brief Retrieves Buffer Data from receive buffer
*   \param[in]  mibspi   - Spi module base address
*   \param[in]  group - Transfer group (0..7)
*   \param[out] data  - pointer to data array
*
*   \return error flags from data buffer, if there was a receive error on
*           one of the buffers this will be reflected in the return value.
*
*   This function transfers the data from the specified transfer group recieve
*   buffers to the data array,  the length of the data must match the length
*   of the transfer group.
*/
FUNC(uint32, SPI_CODE) mibspiGetData(const mibspictrlregs_t *mibspi, uint32 group, uint16 data[])
{

#if (D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHDIGMSB) 
/* hardcoded for DigMSB component for optimization because used in Motor Control ISR */
/* assumes mibspi 3 or 5, transfer group size == D_TGSIZE_CNT_U16, always returns 0 */

    P2VAR(mibspiRAM_t, AUTOMATIC, AUTOMATIC) ram = ((mibspi == mibspiREG3) ? mibspiRAM3 : mibspiRAM5);
    VAR(uint32, AUTOMATIC) start  = (mibspi->TGCTRL[group] >> 8) & 0xFFU;
	VAR(uint16, AUTOMATIC) i;

	for( i = 0u; i < D_TGSIZE_CNT_U16; i++ )
	{
		data[i] = ram->rx[start].data;
		start++;
    }

    return (0UL);
	
#else /* use original Halcogen code when used with anything other than Digital MSB */

    P2VAR(mibspiRAM_t, AUTOMATIC, AUTOMATIC) ram = (mibspi == mibspiREG1) ? mibspiRAM1 : ((mibspi == mibspiREG3) ? mibspiRAM3 : mibspiRAM5);
    VAR(uint32, AUTOMATIC) start  = (mibspi->TGCTRL[group] >> 8) & 0xFFU;
    VAR(uint32, AUTOMATIC) end    = (group == 7UL) ? (mibspi->LTGPEND + 1UL) : ((uint32)(mibspi->TGCTRL[group+1U] >> 8) & 0xFFUL);
    VAR(uint32, AUTOMATIC) flags_Cnt_T_u32  = 0U;
	VAR(uint16, AUTOMATIC) i = 0U;

    if (end < start) {end = 128U;}

    while (start < end)
    {
        flags_Cnt_T_u32  |= ram->rx[start].flags;
        data[i] = ram->rx[start].data;
		i++;
        start++;
    }
    return (flags_Cnt_T_u32 >> 8) & 0x5FU;
	
#endif

}

/*! \fn void mibspiTransfer(mibspictrlregs_t *mibspi, uint32 group)
*   \brief Transmit Transfer Group
*   \param[in] mibspi   - Spi module base address
*   \param[in] group - Transfer group (0..7)
*
*   Initiates a transfer for the specified transfer group.
*/
FUNC(void, SPI_CODE) mibspiTransfer(mibspictrlregs_t *mibspi, uint32 group)
{
    mibspi->TGCTRL[group] |= 0x80000000UL;
}


/*! \fn void mibspiEnableGroupNotification(mibspictrlregs_t *mibspi, uint32 group, uint32 )
*   \brief Enable Transfer Group interrupt
*   \param[in] mibspi   - Spi module base address
*   \param[in] group - Transfer group (0..7)
*   \param[in] level - Interrupt level
*
*   This function enables the transfer group finished interrupt.
*/

#if (D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC) 
/* this static function is only called from code that is conditionally compiled for D_SPINXT_USEWITHTC */
/* therefore this function is conditionally compiled to avoid QAC warning when compiled for other than D_SPINXT_USEWITHTC */
static FUNC(void, SPI_CODE) mibspiEnableGroupNotification(mibspictrlregs_t *mibspi, uint32 group, uint32 level)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */

    if (level != 0U)
    {
        mibspi->SETINTLVLRDY = 1UL << group;
    }
    else
    {
        mibspi->CLRINTLVLRDY = 1UL << group;
    }
    mibspi->SETINTENARDY = 1UL << group;

/* USER CODE BEGIN (14) */
/* USER CODE END */
}
#endif

/*! \fn void mibspiNotification(mibspictrlregs_t *mibspi, uint32 flags)
*   \brief Error interrupt callback
*   \param[in] mibspi   - mibSpi module base address
*   \param[in] flags - Copy of error interrupt flags
*
* This is an error callback that is provided by the application and is called on
* an error interrupt.  The parameter passed to the callback is a copy of the error
* interrupt flag register.  It is hardcoded for channel 0/sequence 0 and the Turns Counter application.
*/
FUNC(void, SPI_CODE) mibspiNotification(const mibspictrlregs_t *mibspi, uint32 flags)
{
#if (D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC) 
	/* TODO: Provide notification processing (i.e. callout to configured function) */
	if(mibspi == mibspiREG3){
		Dio_WriteChannel( SPI_TCCS, STD_HIGH );
		/* Error detected, no valid receive data to read. */
		SeqResult_Enum[0] = SPI_SEQ_FAILED;
		/* TODO: Provide required error event notification */
	}
#endif
}

/*! \fn void mibspiGroupNotification(mibspictrlregs_t *mibspi, uint32 group)
*   \brief Transfer complete notification callback
*   \param[in] mibspi   - mibSpi module base address
*   \param[in] group - Transfer group
*
* This is a callback function provided by the application.  It is call when
* a transfer is complete.  The parameter is the transfer group that triggered
* the interrupt.
*/
FUNC(void, SPI_CODE) mibspiGroupNotification(const mibspictrlregs_t *mibspi, uint32 group)
{
	/* TODO: Provide notification processing (i.e. callout to configured fucntion) */
	/* Minimalist implementation of receiving data.  This driver is designed to only receive
	 * data on mibspi3 group 0 for the Turns Counter communication function.
	 * TODO: generalize the SPI receive process when required.
	 */
#if (D_SPINXTUSEWITH_CNT_ENUM == D_SPINXT_USEWITHTC) 
	if(mibspi == mibspiREG3){
		Dio_WriteChannel( SPI_TCCS, STD_HIGH );
		(void) mibspiGetData8( mibspi, group, ExtBufCfg_Str[0].DesDataBufferPtr ); 
		SeqResult_Enum[0] = SPI_SEQ_OK;
		/* TODO: evaluate return value of mibspiGetData to provide error notifications */
		CALL_MIBSPI3_NOTIFFCN();
	}
#endif
}

#define SPINXT_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */

/***************************************************************************************************************

CHANGE HISTORY:

 Date      Rev      Author         Change Description                                                   SCR #
-------   -------  --------  -----------------------------------                                      ----------
09/20/10   1.0      AH        Initial file creation
							  Generated by Halcogen mibspi.c v1.01.000
01/13/12   2.0		KJS		  Updated baudrate from original 1Mhz (at 65Mhz Vclk)
								to 883KHz for the 80Mhz Vclk, provides 1.2uS of delay 
								between word transmissions. 
03/09/12   3		JJW		  Added Autosar Spi Api
							  Corrected MISRA violations, which included changing the
							  Halcogen generated JavaDoc commenting to a Doxygen commenting
							  style to avoid characters MISRA considers illegal.
03/15/12   4		JJW		  AsyncTransmit design improvement using exclusive areas and 
								message transmit state check to ensure proper management
								of data transmission.
03/27/12   7		JJW		  Increased WDELAY and T2CDELAY to meet updated FDD 20C requirements.
03/18/13   8		KJS		  Adjusted timings based on FDD 98 and QAC Updates
08/02/13   9        KMC       Changes to make configurable for Turns Counter or Digital MSB (CR 8834) 
                              and to fix anomaly 4317 (CR 8683) and QAC updates. Update to use StdDef 
							  mibspi register type definitions.
04/02/14   10		KMC		  Removed special mibspiSetData code for DigMSB since it is no longer used    11435
                              from motor control ISR as of ES-50A v005. Updated special mibspiGetData 
							  code for DigMSB for ES-50A v005. Added DMA control initialization for
                              ES-50A v 005.  QAC cleanup.							  
*****************************************************************************************************************/

