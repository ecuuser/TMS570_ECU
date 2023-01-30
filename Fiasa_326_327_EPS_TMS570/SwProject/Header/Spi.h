#ifndef SPI_H
#define SPI_H


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* Driver status enumerations */
typedef enum
{
    SPI_UNINIT = 0,
    SPI_IDLE = 1,
    SPI_BUSY = 2
}   Spi_StatusType;

typedef enum
{
    SPI_JOB_OK = 0,
    SPI_JOB_PENDING = 1,
    SPI_JOB_ACTIVE = 2,    /* this is an internal state */
    SPI_JOB_FAILED = 3
} Spi_JobResultType;

typedef enum
{
    SPI_DLC_OK = 0,
    SPI_DLC_PENDING = 1,
    SPI_DLC_FAILED = 2
}Spi_HwUnitResultType;

typedef enum
{
    SPI_SEQ_OK = 0,
    SPI_SEQ_PENDING = 1,
    SPI_SEQ_FAILED = 2,
    SPI_SEQ_CANCELLED = 3
} Spi_SeqResultType;

typedef enum
{
    SPI_MSB = 0,
    SPI_LSB = 1
} Spi_TransferType;

/* type for SpiCsPolarity and SpiShiftClockIdleLevel */
typedef enum
{
    SPI_LOW = STD_LOW,
    SPI_HIGH
} Spi_LevelType;

/* type for  SpiCsIdentifier */
typedef enum
{
    SPI_PCS0 = 0,
    SPI_PCS1,
    SPI_PCS2,
    SPI_PCS3,
    SPI_PCS4,
    SPI_PCS5,
    SPI_PCS6,
    SPI_PCS7
} Spi_PCsType;

/* type for SpiCsMode */
typedef enum
{
    SPI_SINGLE = 0,
    SPI_CONTINOUS = 1
} Spi_CsModeType;

/* enums end */

/* Driver, job, sequence status types */

typedef uint16 Spi_NumberOfDataType;
typedef uint16 Spi_JobType;

typedef uint8  Spi_DataType;
typedef uint8  Spi_ChannelType;
typedef uint8  Spi_SequenceType;
typedef uint8  Spi_HWUnitType;
typedef uint8  Spi_ExternalDeviceType;


#endif  /* SPI_H */
