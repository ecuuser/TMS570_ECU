/**************************************************************************************************
   Project Name: AUTOSAR_GbR CAN-TP
      File Name: CanTp_Cbk.h

      Description: Callback header file of the AUTOSAR CAN Transport Protocol, according to:
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
   2008-01-16   1.02.00  Her     ESCAN00024152: AUTOSAR Rel. 3.0
   2008-07-31   1.03.00  Her     ESCAN00028856: Reduce resource consumption: addressing type, buffer provision, single connection
   2010-01-07   1.04.00  Her     ESCAN00040003: MISRA conformance improved
   2013-07-11   1.25.00  Dth     ESCAN00068731: Harmonization of version numbers
**************************************************************************************************/
#if !defined( CANTP_CBK_H )
#define CANTP_CBK_H

/**************************************************************************************************
* Include files
**************************************************************************************************/

/**************************************************************************************************
* Version Checks
**************************************************************************************************/
#define CANTP_CBK_VERSION           0x0125u
#define CANTP_CBK_RELEASE_VERSION   0x00u

/**************************************************************************************************
* Global defines
**************************************************************************************************/


/**************************************************************************************************
* Global data types and structures
**************************************************************************************************/


/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, CANTP_CODE) CanTp_RxIndication(  PduIdType CanTpRxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pCanTpRxPduPtr);
extern FUNC(void, CANTP_CODE) CanTp_TxConfirmation(PduIdType CanIfTxPduId);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#endif
/* ifndef CANTP_CBK_H */

/************   Organi, Version 3.7.0 Vector-Informatik GmbH  ************/
