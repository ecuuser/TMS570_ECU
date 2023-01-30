/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2008 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ComStack_Types.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Provision of Comunication Stack Types
 *  
 *  -------------------------------------------------------------------------------------------------------------------
 *  MISRA VIOLATIONS
 *  -------------------------------------------------------------------------------------------------------------------
 *      
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Joachim Kalmbach              Jk            Vector Informatik
 *  Gunnar Meiss                  Ms            Vector Informatik
 *  Heike Honert                  Ht            Vector Informatik
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2007-08-01  Jk                    Initial creation
 *  03.00.00  2007-09-14  Jk                    Addaption for AUTOSAR 3.0 / NetworkHandleType added
 *  03.00.01  2007-11-20  Jk                    Version defines for CFG management added
 *  03.01.00  2008-03-18  Jk                    Version defines changed to specification version
 *  03.01.01  2008-04-18  Ms      ESCAN00026158 Support more than 255 Pdus per component
 *                        Ms      ESCAN00026165 COMSTACKTYPE_VENDOR_ID
 *                        Ms      ESCAN00028208 Remove non ISO-5.2.1 Characters
 *  03.02.00  2008-07-16  Jk                    BUSTRCV_E_OK added (specification inconsistency ComStackTypes <-> FrTrcv)
 *  03.02.01  2008-10-30  Lo                    Fixed COMSTACKTYPE_AR_MAJOR_VERSION
 *  03.02.02  2009-06-15  Ht      ESCAN00035189 Compiler Error due to storage qualifier used in struct definition             
 *  03.03.00  2010-03-23  Ht      ESCAN00041756 support TPParameterType
 *  03.03.01  2010-05-11  Ht      ESCAN00042906 correct version defines COMMONASR__COMMON_IMPL_COMSTACKTYPES..
 *  03.03.02  2011-07-06  Ht      ESCAN00051946 Add MAXVAL defines
 *********************************************************************************************************************/

#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
 
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : CommonAsr__Common CQComponent : Impl_ComStackTypes */
#define COMMONASR__COMMON_IMPL_COMSTACKTYPES_VERSION 0x0303
#define COMMONASR__COMMON_IMPL_COMSTACKTYPES_RELEASE_VERSION 0x02
 
/* AUTOSAR Software Specification Version Information */
/* AUTOSAR Document version 2.2.1 part of release 3.1.0 */
#define COMSTACKTYPE_AR_MAJOR_VERSION       (2u)
#define COMSTACKTYPE_AR_MINOR_VERSION       (2u)
#define COMSTACKTYPE_AR_PATCH_VERSION       (1u)

/* Component Version Information */
#define COMSTACKTYPE_SW_MAJOR_VERSION       (3u)
#define COMSTACKTYPE_SW_MINOR_VERSION       (3u)
#define COMSTACKTYPE_SW_PATCH_VERSION       (2u)

#define COMSTACKTYPE_VENDOR_ID              (30u)

/*General return codes for NotifResultType*/
 
#define NTFRSLT_OK              0x00  /*Action has been successfully finished:
                                                - message sent out (in case of confirmation),
                                                - message received (in case of indication) */
#define NTFRSLT_E_NOT_OK        0x01  /*Error notification:
                                                - message not successfully sent out (in case of confirmation),
                                                - message not successfully received (in case of indication) */
#define NTFRSLT_E_TIMEOUT_A     0x02  /*Error notification:
                                                - timer N_Ar/N_As (according to ISO specification [ISONM]) has passed its time-out value N_Asmax/N_Armax.
                                             This value can be issued to service user on both the sender and receiver side. */
#define NTFRSLT_E_TIMEOUT_BS    0x03  /*Error notification:
                                                - timer N_Bs has passed its time-out value N_Bsmax (according to ISO specification [ISONM]).
                                             This value can be issued to the service user on the sender side only. */
#define NTFRSLT_E_TIMEOUT_CR    0x04  /*Error notification:
                                                - timer N_Cr has passed its time-out value N_Crmax.
                                             This value can be issued to the service user on the receiver side only. */
#define NTFRSLT_E_WRONG_SN      0x05  /*Error notification:
                                                - unexpected sequence number (PCI.SN) value received.
                                             This value can be issued to the service user on the receiver side only. */
#define NTFRSLT_E_INVALID_FS    0x06  /*Error notification:
                                                - invalid or unknown FlowStatus value has been received in a flow control (FC) N_PDU.
                                             This value can be issued to the service user on the sender side only. */
#define NTFRSLT_E_UNEXP_PDU     0x07  /*Error notification:
                                                - unexpected protocol data unit received.
                                             This value can be issued to the service user on both the sender and receiver side. */
#define NTFRSLT_E_WFT_OVRN      0x08  /*Error notification:
                                                - flow control WAIT frame that exceeds the maximum counter N_WFTmax received.
                                             This value can be issued to the service user on the receiver side. */
#define NTFRSLT_E_NO_BUFFER     0x09  /*Error notification:
                                                - flow control (FC) N_PDU with FlowStatus = OVFLW received. 
                                                  It indicates that the buffer on the receiver side of a segmented message transmission
                                                  cannot store the number of bytes specified by the FirstFrame DataLength (FF_DL) parameter
                                                  in the FirstFrame and therefore the transmission of the 19 of 23 AUTOSAR_SWS_ComStackTypes
                                                  segmented message was aborted.
                                                - no buffer within the TP available to transmit the segmented I-PDU.
                                             This value can be issued to the service user on both the sender and receiver side. */
#define NTFRSLT_E_CANCELATION_OK         0x0A  /*Action has been successfully finished:
                                                         - Requested cancellation has been executed.*/
#define NTFRSLT_E_CANCELATION_NOT_OK     0x0B  /*Error notification:
                                                         - Due to an internal error the requested cancelation has not been executed. This will happen e.g., if the to be canceled transmission has been executed already.*/
/* 0x0C-0x1E Reserved values for future usage. */
/* extension of R4.0 R1 */
#define NTFRSLT_PARAMETER_OK             0x0D     /* The parameter change request has been successfully executed */
#define NTFRSLT_E_PARAMETER_NOT_OK       0x0E     /* The request for the change of the parameter did not complete successfully */
#define NTFRSLT_E_RX_ON                  0x0F     /* The parameter change request not executed successfully due to an ongoing reception */
#define NTFRSLT_E_VALUE_NOT_OK           0x10     /* The parameter change request not executed successfully due to a wrong value */


/*General return codes for BusTrcvErrorType*/
#define BUSTRCV_OK         0x00
/*BUSTRCV_E_OK needed by FrTrcv specification inconcistency between ComStackTypes and FrTrcv*/
#define BUSTRCV_E_OK       0x00
#define BUSTRCV_E_ERROR    0x01

 
/* ISO15765-2 conform items */
/* range 100-150            */
#define TPPARAMTYPE_CANTP_STMIN                100u
#define TPPARAMTYPE_CANTP_BS                   101u

/* ISO10681-2 conform items */
/* range 150-200            */
#define TPPARAMTYPE_FRTP_BC                    150u
#define TPPARAMTYPE_FRTP_BFS                   151u
#define TPPARAMTYPE_FRTP_MAX_WFT               152u
#define TPPARAMTYPE_FRTP_MAX_RETRIES           153u

/* Vector extensions */
#define TPPARAMTYPE_FRTP_TA                  160u
#define TPPARAMTYPE_FRTP_SA                  161u
#define TPPARAMTYPE_FRTP_NUM_TX_PDUS_TO_USE  162u
#define TPPARAMTYPE_FRTP_BW_LIMITATION       163u
#define TPPARAMTYPE_FRTP_MAX_TX_PDU_LEN      164u


#define PDUIDTYPE_MAXVAL        0xFFFFu             /* value depends on typedef "PduIdType" */
#define PDULENGTHTYPE_MAXVAL    0xFFFFu             /* value depends on typedef "PduLengthType" */
  

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef uint16       PduIdType;           /*The size of this global type depends on the maximum number of PDUs used within one software module.*/
   
typedef uint16       PduLengthType;       /*The size of this global type depends on the maximum length of PDUs to be sent by an ECU.*/


typedef  P2VAR(uint8, TYPEDEF, AUTOSAR_COMSTACKDATA) SduDataPtrType;
typedef struct
{
   SduDataPtrType SduDataPtr;
   PduLengthType SduLength;
}PduInfoType;

typedef enum                          
{
         BUFREQ_OK,           /*Buffer request accomplished successful.*/
         BUFREQ_E_NOT_OK,     /*Buffer request not successful. Buffer cannot be accessed.*/
         BUFREQ_E_BUSY,       /*Temporarily no buffer available. It's up the requestor to retry request for a certain time.*/
         BUFREQ_E_OVFL        /*No Buffer of the required length can be provided.*/
} BufReq_ReturnType;

typedef uint8        NotifResultType;
 
typedef uint8        BusTrcvErrorType;

typedef uint8        NetworkHandleType;

/* ISO15765-2 conform items */
typedef uint8        TPParameterType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* COMSTACK_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: ComStack_Types.h
 *********************************************************************************************************************/
/************   Organi, Version 3.9.0 Vector-Informatik GmbH  ************/
