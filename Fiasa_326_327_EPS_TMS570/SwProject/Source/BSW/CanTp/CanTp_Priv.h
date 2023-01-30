/**************************************************************************************************
   Project Name: Tp_AsrTpCan
      File Name: CanTp_Priv.h

    Description: CanTp-specific/internal definitions and constants.

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
   Dth          Thomas Dedler             Vector Informatik GmbH

  -------------------------------------------------------------------------------------------------
                 R E V I S I O N   H I S T O R Y
  -------------------------------------------------------------------------------------------------
   Date         Rev.     Author  Description
   ----------   -------  ------  ------------------------------------------------------------------
   2006-10-04   1.00.00  Her     Initial version
   2007-06-06   1.01.00  Her     ESCAN00021101: AUTOSAR Rel. 2.1
   2008-01-16   1.02.00  Her     ESCAN00024152: ASR R. 3.0 new requirements
   2008-01-16   1.03.00  Her     ESCAN00027017: Use dynamic channel allocation to reduce resource consumption
   2008-07-31   1.04.00  Her     ESCAN00028721: Length check for Flow Control frames corrected
   2008-07-31   1.05.00  Her     ESCAN00028856: Reduce resource consumption: addressing type, buffer provision, single connection
   2010-01-07   1.06.00  Her     ESCAN00040003: MISRA conformance improved 
   2010-07-15   1.07.00  Her     ESCAN00040590: Optimize constant Sdu settings in precompile variant
   2011-04-20   1.08.00  Her     ESCAN00049432: Report DET error in case of a length violation
   2011-05-02   1.09.00  Her     ESCAN00050534: Cancellation of wrong NPduId in the CanIf (add debug info)
   2012-03-30   1.10.00  Dth     ESCAN00055796: Wrong naming of DET API Ids
   2013-07-11   1.25.00  Dth     ESCAN00068731: Harmonization of version numbers
   **************************************************************************************************/
#if !defined( CANTP_PRIV_H )
#define CANTP_PRIV_H

/**************************************************************************************************
* Include files
**************************************************************************************************/

/**************************************************************************************************
* Version Checks
**************************************************************************************************/
#define CANTP_PRIV_VERSION              0x0125u
#define CANTP_PRIV_RELEASE_VERSION      0x00u

/**************************************************************************************************
* Global defines
**************************************************************************************************/
/* Internal frame types */
#define kL4_SingleFrame                0x00
#define kL4_FirstFrame                 0x10
#define kL4_ConsecutiveFrame           0x20
#define kL4_CFMaskXOR                  0x50
#define kL4_FlowControl                0x30
#define kL4_InvalidFrameType           0xFF

/* Flowstatus-codes */
#define kL4_FlowStatus_ClearToSend     0x00
#define kL4_FlowStatus_Wait            0x01
#define kL4_FlowStatus_OVFLW           0x02
#define kL4_FirstFrameWithoutFC        0x50

#define kL4_FrameTypeMask              0xF0
#define kL4_SNMask                     0x0F

#if (CANTP_HAVE_EXT_DEV_ERROR_DETECT == STD_ON)
/* Vector-CanTp internal error codes */
# define CANTP_TXPDU_ADMIN_ERR    0x04
# define CANTP_CANIF_ERR          0x05u
# define CANTP_WRONG_STATE        0x0B
#endif

/* Vector-CanTp internal service-Ids */
#define vCanTp_CanIfTransmit_SId                       0x11u
#define vCanTp_TxGetStminTimerFromStminValue_SId       0x12u
#define vCanTp_TxCFTxConfirmation_SId                  0x13u
#define vCanTp_RxRetrieveApplRxBuffer_SId              0x14u
#define vCanTp_TxRetrieveApplTxBuffer_SId              0x15u
#define vCanTp_MemCpy_SId                              0x16u
#define vCanTp_CanIfTxConfirmation_Sid                 0x17u
#define vCanTp_TxGetResource_Sid                       0x18u
#define vCanTp_RxGetResource_Sid                       0x19u
#define vCanTp_InitMemory_Sid                          0x1Au
#define vCanTp_MemSet_SId                              0x1Bu
#define vCanTp_RxStateTask_Sid                         0x1Cu

/**************************************************************************************************
* Global data types and structures
**************************************************************************************************/


/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/
#if (CANTP_RX_SF_INDICATION == STD_ON)
extern void Appl_CanTpRxSFIndication(PduIdType CanTpRxPduId, uint8 Result);
#endif
#if (CANTP_RX_FF_INDICATION == STD_ON)
extern void Appl_CanTpRxFFIndication(PduIdType CanTpRxPduId, uint8 Result);
#endif
#if (CANTP_RX_CF_INDICATION == STD_ON)
extern void Appl_CanTpRxCFIndication(PduIdType CanTpRxPduId, uint8 SeqNo);
#endif
#if (CANTP_TX_FRAME_CONFIRMATION == STD_ON)
extern void Appl_CanTpTxFrameConfirmation(PduIdType pduId, PduInfoType *pduInfoPtr);
#endif

/***** end of header file ************************************************************************/
#endif /* ifndef CANTP_PRIV_H_H */
/************   Organi, Version 3.7.0 Vector-Informatik GmbH  ************/
