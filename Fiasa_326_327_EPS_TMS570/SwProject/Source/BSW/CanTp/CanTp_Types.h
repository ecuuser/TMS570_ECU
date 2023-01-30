/**************************************************************************************************
   Project Name: AUTOSAR_GbR CAN-TP
      File Name: CanTp_Types.h

      Description: Type definition header of the Vector
                   AUTOSAR CAN Transport Protocol, according to:
                   AUTOSAR_SWS_CAN_TP (Release 3.2)

  -------------------------------------------------------------------------------------------------
       C O P Y R I G H T
  -------------------------------------------------------------------------------------------------
       Copyright (c) 2001 - 2013 by Vector Informatik GmbH. All rights reserved.

       This software is copyright protected and proprietary to Vector Informatik GmbH.
       Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
       All other rights remain with Vector Informatik GmbH.


       REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE COPYRIGHT AGREEMENT.

  -------------------------------------------------------------------------------------------------
                 A U T H O R   I D E N T I T Y
  -------------------------------------------------------------------------------------------------
   Initials     Name                      Company
   --------     ---------------------     ---------------------------------------------------------
   Her          Peter Herrmann            Vector Informatik GmbH

  -------------------------------------------------------------------------------------------------
                 R E V I S I O N   H I S T O R Y
  -------------------------------------------------------------------------------------------------
   Date         Rev.     Author  Description
   ----------   -------  ------  ------------------------------------------------------------------
   2006-10-04   1.00.00  Her     Initial version
   2007-05-17   1.01.00  Her     ESCAN00021101: AUTOSAR Rel. 2.1
   2008-01-16   1.02.00  Her     ESCAN00024152: ASR R. 3.0 new requirements
   2008-04-22   1.03.00  Her     ESCAN00026250: Rename files and #include statements according coding styles
                         Her     ESCAN00026671: Extension for MSR3.0 generator version checks
                         Her     ESCAN00027017: Use dynamic channel allocation to reduce resource consumption
   2008-07-11   1.04.00  Her     ESCAN00028326: Resource optimization transfered to GENy
   2008-07-31   1.05.00  Her     ESCAN00028856: Reduce resource consumption: addressing type, buffer provision, single connection
   2008-09-23   1.06.00  Her     ESCAN00029781: Pre-Compile and Link-Time CRC Check
   2009-02-23   1.07.00  Her     ESCAN00032457: Data type of CanTp_WFTmax prepared for change (uint8 to uint16)
   2009-02-25   1.08.00  Her     ESCAN00033429: Data type of CanTp_WFTmax changed (uint8 to uint16)
                         Her     ESCAN00033439: Remapping of NSDU-IDs to user configured numbers
                         Her     ESCAN00033512: Support dynamic Flow Control N-PDU content 
   2009-06-17   1.09.00  Her     ESCAN00035809: Compiler abstraction missing
   2009-06-17   1.10.00  Her     ESCAN00035216: Add Mixed-11 Addressing (Gateway UseCase)
   2009-08-26   1.11.00  Her     ESCAN00037347: STmin is gone below
   2010-01-07   1.12.00  Her     ESCAN00040003: MISRA conformance improved 
   2010-02-18   1.13.00  Her     ESCAN00040300: Switch CanTp Parameters BS, Stmin at runtime via CanTp_ChangeParameterRequest API
   2010-03-29   1.14.00  Her     ESCAN00041916: Consistency of preprocessor switches
                         Her     ESCAN00042575: Strictly keep the reception sequence independent of the buffer provision return value
                         Her     ESCAN00042652: Adapt type of invalid handle definition to the PduIdType definition
   2010-07-15   1.15.00  Her     ESCAN00040590: Optimize constant Sdu settings in precompile variant
                         Her     ESCAN00043991: Support TP Receive Cancellation
                         Her     ESCAN00044374: Change Parameter API function accesses unmapped memory
   2010-10-13   1.16.00  Her     ESCAN00045310: Change the transmit cancellation availability from general to connection specific
   2010-10-13   1.17.00  Her     ESCAN00048115: Support more than 255 statically configured Sdu-Id for Rx and Tx side
   2011-02-22   1.18.00  Her     ESCAN00049050: AUTOSAR 4 compatibility
   2011-04-20   1.19.00  Her     ESCAN00049945: Support Half Duplex communication
   2012-07-30   1.19.01  Dth     ESCAN00054420: parameter check in CanTp_Transmit corrected
                         Dth     ESCAN00060406: CanTp_Types.h file version corrected
   2013-07-11   1.25.00  Dth     ESCAN00068731: Harmonization of version numbers
**************************************************************************************************/
#if !defined( CANTP_TYPES_H )
#define CANTP_TYPES_H
/* PRQA  S 0883 EOF */ /* RULE 19.15: Multiple includes are checked for possible problems. */
/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "ComStack_Types.h"
#include "CanTp_Cfg.h"

/**************************************************************************************************
* Version Checks
**************************************************************************************************/
#define CANTP_TYPES_VERSION           0x0125u
#define CANTP_TYPES_RELEASE_VERSION   0x00u

/**************************************************************************************************
* Global defines
**************************************************************************************************/
/* AUTOSAR compliancy */

#define CANTP_OFF                       0x00
#define CANTP_ON                        0x01

/* DET error-IDs */
/* API errors could be a combination of: */
#define CANTP_E_PARAM_CONFIG            0x01u
#define CANTP_E_PARAM_ID                0x02u
#define CANTP_E_PARAM_ADDRESS           0x04u
/* module initialization */
#define CANTP_E_UNINIT                  0x20u
/* invalid values */
#define CANTP_E_INVALID_TX_ID           0x30u
#define CANTP_E_INVALID_RX_ID           0x40u
#define CANTP_E_INVALID_TX_BUFFER       0x50u
#define CANTP_E_INVALID_RX_BUFFER       0x60u
#define CANTP_E_INVALID_TX_LENGTH       0x70u
#define CANTP_E_INVALID_RX_LENGTH       0x80u
#define CANTP_E_INVALID_TATYPE          0x90u  /* CanTp293 from AR4 */

/* These #defines are the extension of NotifResultType from Vector side: */
#define CANTP_E_INVALID_STATE           (0x5Cu)/* invalid status      */    
#define CANTP_E_NULL_PTR                (0x5Du)/* invalid pointer     */
#define CANTP_E_INVALID_HDL             (0x5Eu)/* invalid handle      */
#define CANTP_E_INVALID_PATH            (0x5Fu)/* invalid prgram path */

/* Vector specific */
#define CANTP_MAX_FRAME_LENGTH            8    /* CAN frame         */
#define CANTP_MAX_DATA_LENGTH          4095    /* TP message length */
#define CANTP_MAX_PAYLOAD_LENGTH_NA       7    /* SF, Normal Adr.   */
#define CANTP_MAX_PAYLOAD_LENGTH_EA       6    /* SF, Extended Adr. */

/**************************************************************************************************
* Macros
**************************************************************************************************/

/**************************************************************************************************
* Global data types and structures
**************************************************************************************************/
/* AUTOSAR compliant */

/* Addressing Format */
#define CANTP_STANDARD                    0x00u
#define CANTP_EXTENDED                    0x01u
#define CANTP_MIXED11                     0x02u

/* TA-TYPE */
#define CANTP_PHYSICAL                    0x00u
#define CANTP_FUNCTIONAL                  0x01u

/* CHANNEL MODE */
#define CANTP_MODE_HALF_DUPLEX            0x00u
#define CANTP_MODE_FULL_DUPLEX            0x01u

typedef enum
{
  CANTP_IDLE = 0,
  CANTP_RX,
  CANTP_TX
} vCanTp_operatingType;

typedef enum
{
  CANTP_APPL_NOT_INFORMED = 0,
  CANTP_APPL_INFORMED     = 1
} vCanTp_ApplState;


/* Vector specific types */
typedef unsigned int vCanTp_BitType;
typedef uint8 vCanTp_StatusType;
typedef uint8 vCanTp_FrameType;
/* GENy Tp_AsrTpCan DLL Version 1.13.00 is the last one with an "uint8 WFTmax counter". After this version the data type is changed to uint16. */
typedef uint16 vCanTp_WFTmaxType;
/* Helper type for compiler abstraction */
typedef P2VAR(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoTypeCanTpApplDataPtr;

typedef struct
{
  PduIdType rxSduIdx;
  PduIdType txSduIdx;
  uint8     addrType;
} vCanTp_RxPduMapType;

/* Runtime-data (RAM) */

/* External Data (RAM) */
typedef uint8   vCanTp_RxStateEngineType;
typedef uint8   vCanTp_TxStateEngineType;
typedef uint16  vCanTp_ChanTimer;
typedef uint8   CanTp_BufferState;

/* *************** */
/* Rx-status (RAM) */
/* *************** */
typedef struct sRxState
{
  /* general info */
  vCanTp_FrameType          frameType;
  /* activation status */
  vCanTp_ChanTimer          Timer;
  vCanTp_RxStateEngineType  ChannelState;
  /* Pointers */
  P2VAR(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) ApplPduInfoPtr; /* If != 0: Buffer for Rx-data that was retrieved from App. */
  P2VAR(uint8,       AUTOMATIC, CANTP_APPL_DATA) DataBufferPtr;  /* If != 0: Buffer for Rx-data that was retrieved from App. */
  /* Lengths */
  PduLengthType             DataIndex;
  PduLengthType             DataLength;
  PduLengthType             providedDataLength;
  PduLengthType             FrameIndex;
  uint8                     FrameStartIndex;
  /* buffer admin */
  CanTp_BufferState         bufState;
  vCanTp_WFTmaxType         WFTCounter; 
  /* actual values */
  uint8                     BlocksizeCounter;
  uint8                     STMin;
  PduIdType                 channel;
  uint8                     queued;
  /* Bittypes */
  vCanTp_BitType            ExpectedSN:4;
#if( ( CANTP_STRICT_RX_CALL_SEQ == STD_ON ) || ( CANTP_RC == STD_ON ) )
  vCanTp_BitType            ApplState:1;    /* CANTP_APPL_[NOT_]INFORMED */
  vCanTp_BitType            res0:3;
#else
  vCanTp_BitType            res0:4;
#endif
} vCanTp_RxStateType;

/* *************** */
/* Tx-status (RAM) */
/* *************** */
typedef struct sTxState
{
  /* general info */
  vCanTp_FrameType          frameType;
  /* activation status */
  vCanTp_ChanTimer          Timer;
  vCanTp_TxStateEngineType  ChannelState;
  /* Pointers */
  P2VAR(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) ApplPduInfoPtr;
  P2VAR(uint8,       AUTOMATIC, CANTP_APPL_DATA) DataBufferPtr; /* If != 0: Buffer with Tx-data that was retrieved from App. */
  /* Lengths */
  PduLengthType             DataIndex;
  PduLengthType             DataLength;
  PduLengthType             providedDataLength;
  /* segmented Tx buffer */
  PduLengthType             OverallDataIndex;
  PduLengthType             FrameIndex;
  /* buffer admin */
  CanTp_BufferState         bufState;
  /* actual values */
  uint8                     STMin;
  uint8                     TimerSTMin;
  uint8                     BlocksizeCounter;
#if( CANTP_USE_ONLY_FIRST_FC == STD_ON )
  uint8                     BS;
#endif
  PduIdType                 channel;
  uint8                     queued;
  vCanTp_BitType            seqNumber:4;
#if( CANTP_USE_ONLY_FIRST_FC == STD_ON )
  vCanTp_BitType            firstFC:1;
  vCanTp_BitType            res0:3;
#else
  vCanTp_BitType            res0:4;
#endif
} vCanTp_TxStateType;

/************************************************
* Types for static-configuration (ROM/Flash) 
************************************************/
/*************
* CanTp (ROM) 
*************/

/******************
* RxNsdu (ROM)
******************/
typedef struct sRxNsduCfg
{
  /* Rx */
#if( CANTP_CONSTANT_RX__DL == STD_OFF )
  uint16                  CANTP_DL;
#endif
#if( CANTP_CONSTANT_RX__NAR == STD_OFF )
  uint16                  CANTP_NAR;
#endif
#if( CANTP_CONSTANT_RX__NBR == STD_OFF )
  uint16                  CANTP_NBR;
#endif
#if( CANTP_CONSTANT_RX__NCR == STD_OFF )
  uint16                  CANTP_NCR;
#endif
#if( CANTP_CONSTANT_RX__WFTMAX == STD_OFF )
  vCanTp_WFTmaxType       CANTP_WFTMAX;
#endif

  PduIdType               CANTP_RXNSDU_ID;       /* to   PduR  */
  PduIdType               CANTP_TXNSDU_ID;       /* from PduR  */
#if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
  PduIdType               CANTP_REMAP_RXNSDU_ID; /* to   PduR  */
#endif
  PduIdType               CANTP_RXNPDU_ID;    /* from CanIf */
  PduIdType               CANTP_TXFC_NPDU_ID; /* to   CanIf */

#if ( CANTP_PADDING_ACTIVE == STD_ON )
# if( CANTP_CONSTANT_RX__PADDING_ACTIVATION == STD_OFF )
  uint8                   CANTP_PADDING_ACTIVATION;
# endif
#endif
#if( CANTP_CONSTANT_RX__TA_TYPE == STD_OFF )
  uint8                   CANTP_TA_TYPE;
#endif
#if( CANTP_CONSTANT_RX__ADDRESSING_FORMAT == STD_OFF )
  uint8                   CANTP_RX_ADDRESSING_FORMAT;
#endif
#if( CANTP_CONSTANT_RX__MAX_PAYLOAD_LENGTH == STD_OFF )
  uint8                   CANTP_MAX_PAYLOAD_LENGTH;
#endif
#if( CANTP_CONSTANT_RX__BS == STD_OFF )
  uint8                   CANTP_BS;
#endif
#if( CANTP_CONSTANT_RX__STMIN == STD_OFF )
  uint8                   CANTP_STMIN;
#endif

  uint8                   CANTP_RX_NTA;   /* used for N_AE in case of Mixed11 addressing */
  uint8                   CANTP_TXFC_NTA;
#if( CANTP_CONSTANT_RX__DUPLEX_MODE == STD_OFF )
  uint8                   CANTP_DUPLEX_MODE;  /* CANTP_MODE_HALF_DUPLEX, CANTP_MODE_FULL_DUPLEX */
#endif
} vCanTp_RxNsduCfgType;

/******************
* TxNsdu (ROM)
******************/
typedef struct sTxNsduCfg
{
  /* Tx */
#if( CANTP_CONSTANT_TX__DL == STD_OFF )
  uint16                  CANTP_DL;
#endif
#if( CANTP_CONSTANT_TX__NAS == STD_OFF )
  uint16                  CANTP_NAS;
#endif
#if( CANTP_CONSTANT_TX__NBS == STD_OFF )
  uint16                  CANTP_NBS;
#endif
#if( CANTP_CONSTANT_TX__NCS == STD_OFF )
  uint16                  CANTP_NCS;
#endif

  PduIdType               CANTP_TXNSDU_ID;       /* from PduR  */
  PduIdType               CANTP_RXNSDU_ID;       /* to   PduR  */
#if ( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON )
  PduIdType               CANTP_REMAP_TXNSDU_ID; /* from PduR  */
#endif
  PduIdType               CANTP_TXNPDU_ID;    /* to   CanIf */
  PduIdType               CANTP_RXFC_NPDU_ID; /* from CanIf */

#if ( CANTP_PADDING_ACTIVE == STD_ON )
# if( CANTP_CONSTANT_TX__PADDING_ACTIVATION == STD_OFF )
  uint8                   CANTP_PADDING_ACTIVATION;
# endif
#endif
#if( CANTP_CONSTANT_TX__TA_TYPE == STD_OFF )
  uint8                   CANTP_TA_TYPE;
#endif
#if( CANTP_CONSTANT_TX__ADDRESSING_FORMAT == STD_OFF )
  uint8                   CANTP_TX_ADDRESSING_FORMAT;
#endif
#if( CANTP_CONSTANT_TX__MAX_PAYLOAD_LENGTH == STD_OFF )
  uint8                   CANTP_MAX_PAYLOAD_LENGTH;
#endif
#if ( CANTP_TC == STD_ON )
# if( CANTP_CONSTANT_TX__TC == STD_OFF )
  uint8                   CANTPTC;
# endif
#endif

  uint8                   CANTP_TX_NTA;   /* used for N_AE in case of Mixed11 addressing */
  uint8                   CANTP_RXFC_NTA;
#if( CANTP_CONSTANT_TX__DUPLEX_MODE == STD_OFF )
  uint8                   CANTP_DUPLEX_MODE;  /* CANTP_MODE_HALF_DUPLEX, CANTP_MODE_FULL_DUPLEX */
#endif
} vCanTp_TxNsduCfgType;

/* *********************************************** */
/* CanTp Overall (ROM)                             */
/* Struct to hold the complete CanTp-configuration */
/* *********************************************** */
typedef struct sCanTpCfg
{ 
#if !defined( V_SUPPRESS_EXTENDED_VERSION_CHECK )
  uint32              CanTp_GeneratorVersion;
#endif
#if (CANTP_CRC_CHECK == STD_ON )
  uint32              CanTp__PrecompileCRC;
  uint32              CanTp__LinktimeCRC;
#endif
  CONSTP2CONST(vCanTp_RxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) vCanTp_RxNsduCfg;
  CONSTP2CONST(vCanTp_TxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) vCanTp_TxNsduCfg;
  CONSTP2CONST(vCanTp_RxPduMapType,  AUTOMATIC, CANTP_APPL_CONST) vCanTp_rxPduMap;
# if (CANTP_HAVE_MULTI_PURPOSE_TP == STD_ON)
  /* Pointer to callback-cfg-table */
  CONSTP2CONST(vCanTp_CbkCfgType, AUTOMATIC, CANTP_APPL_CONST) CbkCfg;   
# endif
  uint16              TaskCycle;  /* Defines the repetition period of the Cyclic Timeout Supervision Task in ms. */
  /* Overall maximum CanIf-Pdu-Ids Tx and Rx */
  PduIdType MaxCanIfTxPduId;
  PduIdType NumCanIfRxPduId;
  /* Overall maximum PduR-SduIds Tx and Rx */
  PduIdType NumCanTpTxSduId;
  PduIdType NumCanTpRxSduId;
  uint8               InstanceId;  /* Instance Id for DET/DEM reporting */
  uint16              magicNumber; /* Magic number to recognize valid configuration */
} vCanTp_CfgType;

typedef  vCanTp_CfgType  CanTp_ConfigType;    /* AR 4 naming */

/*************************************
* External administration data (RAM) *
*************************************/
typedef struct sCanTpAdmin
{
#if (CANTP_HAVE_INIT_CFG_PTR == STD_ON)
  P2CONST(vCanTp_CfgType, AUTOMATIC, CANTP_APPL_CONST) CfgPtr;
#endif
  /* keep track of the initialization status */
  vCanTp_StatusType       InitState; 
} vCanTp_AdminDataType;

typedef enum 
{ /* The reason is sent to the other peer (not on Rx side in a 1:n connection or in an 
     unsegmented transfer at the receiver or cancellation is not allowed for the 
     corresponding channel) by the means of an appropriate FC frame. */
  CANTP_CNLDO, /* Cancel Transfer because data are outdated                 */
  CANTP_CNLNB, /* Cancel Transfer because no further buffer can be provided */
  CANTP_CNLOR  /* Cancel Transfer because of another reason                 */
} CanTp_CancelReasonType;

/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/

#endif
/* ifndef CANTP_TYPES_H */


