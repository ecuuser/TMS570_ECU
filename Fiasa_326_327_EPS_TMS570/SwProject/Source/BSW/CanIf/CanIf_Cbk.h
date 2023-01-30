/********************************************************************************************************************
|    File Name: CANIF_CBK.H
|
|  Description: Type definitions of the AUTOSAR CAN Interface
|--------------------------------------------------------------------------------------------------------------------
|               C O P Y R I G H T
|--------------------------------------------------------------------------------------------------------------------
| Copyright (c) 1996-2011 by Vector Informatik GmbH.       All rights reserved.
|
| This software is copyright protected and proprietary
| to Vector Informatik GmbH. Vector Informatik GmbH
| grants to you only those rights as set out in the
| license conditions. All other rights remain with
| Vector Informatik GmbH.
|
|--------------------------------------------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|--------------------------------------------------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| Ard          Thomas Arnold             Vector Informatik GmbH
| Rna          Ruediger Naas             Vector Informatik GmbH
| Seu          Eugen Stripling           Vector Informatik GmbH
|--------------------------------------------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|--------------------------------------------------------------------------------------------------------------------
| Date        Version   Author  Description
| ----------  --------  ------  -------------------------------------------------------------------------------------
| 2006-05-24  2.00      Ard     - AUTOSAR 2.0
| 2007-05-15  3.00      Ard     - AUTOSAR 2.1
| 2008-02-22  4.00      Ard     - ESCAN00024947: AUTOSAR 3.0
| 2008-04-21  4.01      Ard     - ESCAN00026257: Fix spelling of include filenames
| 2008-08-19  4.02      Ard     - ESCAN00029315: Change version definitions
| 2010-02-18  4.03      Rna     - ESCAN00040264: Support 8 and 16 bit CanIf_HwHandleType for variable Hrh
| 2011-10-07  4.04      Seu       ESCAN00053271: AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
| 2011-10-12            Seu       ESCAN00054204: MISRA compliance changes R13
|*******************************************************************************************************************/

#ifndef CANIF_CBK_H
#define CANIF_CBK_H

/* PRQA S 0850 EOF */ /* MD_MSR_19.8 */
/* PRQA S 3453 EOF */ /* MD_MSR_19.7 */

#include "CanIf_Cfg.h"
/* CanIf_Types.h  is included by CanIf_Cfg.h */


#define CANIF_CBK_MAJOR_VERSION   0x04u
#define CANIF_CBK_MINOR_VERSION   0x04u
#define CANIF_CBK_PATCH_VERSION   0x00u

#define CANIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Tx Confirmation */
/* void CanIf_TxConfirmation(PduIdType CanTxPduId); */
FUNC(void, CANIF_CODE) CanIf_TxConfirmation(PduIdType CanTxPduId);

/* Rx Indication  */
/* void CanIf_RxIndication(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr); */
FUNC(void, CANIF_CODE) CanIf_RxIndication(CanIf_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR)CanSduPtr);

/* Cancel notification */
/* void CanIf_CancelTxConfirmation(const Can_PduType *PduInfoPtr); */
#if (CANIF_TRANSMIT_BUFFER == STD_ON)
# if (CANIF_TRANSMIT_CANCELLATION == STD_ON)
FUNC(void, CANIF_CODE) CanIf_CancelTxConfirmation(P2CONST(Can_PduType, AUTOMATIC, CANIF_CBK_DRV_VAR) PduInfoPtr);
# endif
#endif

/* BusOff notification */
/* void CanIf_ControllerBusOff(uint8 Controller); */
FUNC(void, CANIF_CODE) CanIf_ControllerBusOff(uint8 Controller);

/* NON AUTOSAR callback functions*/

/* Cancel notification */
/* void CanIf_CancelTxNotification(PduIdType PduId, CanIf_CancelResultType IsCancelled); */
#if (CANIF_CANCEL_SUPPORT_API == STD_ON)
FUNC(void, CANIF_CODE) CanIf_CancelTxNotification(PduIdType PduId, CanIf_CancelResultType IsCancelled);
#endif


#define CANIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif

