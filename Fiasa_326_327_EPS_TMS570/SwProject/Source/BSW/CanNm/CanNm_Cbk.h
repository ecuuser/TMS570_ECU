
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2007-2013 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  CanNm_Cbk.h
 *    Component:  AUTOSAR CAN Network Management
 *       Module:  AUTOSAR Network Management
 *    Generator:  -
 *
 *  Description:  Callback Header of AUTOSAR CAN Network Management
 *                AUTOSAR Release 3.0
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Oliver Hornung                visoh         Vector Informatik GmbH
 *  Daniel Hof                    visdhf        Vector Informatik GmbH
 *  Markus Drescher               vismdr        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  4.00.00   2007-11-14  visoh   ESCAN00023234 Update to AUTOSAR 3.0
 *  4.01.00   2008-02-01  visoh   ESCAN00024714 No changes
 *  4.02.00   2008-02-27  visoh   ESCAN00024920 No changes
 *  4.02.01   2008-03-03  visoh   No changes
 *  4.03.00   2008-03-04  visoh   ESCAN00025032 No changes
 *                                ESCAN00025037 Link-time configuration variant support for the number of channels
 *                                ESCAN00025390 No changes
 *  4.03.01   2008-03-30  visoh   ESCAN00025661 No changes
 *  4.03.02   2008-04-09  visoh   ESCAN00025932 No changes
 *  4.04.00   2008-04-21  visoh   ESCAN00025479 No changes
 *                                ESCAN00026254 No changes
 *  4.04.01   2008-04-23  visoh   ESCAN00026225 No changes
 *                                ESCAN00026661 No changes
 *  4.05.00   2008-07-07  visoh   ESCAN00027898 No changes
 *                                ESCAN00028002 No changes
 *  4.06.00   2008-09-23  visoh   ESCAN00030005 No changes
 *                                ESCAN00030159 No changes
 *  4.06.01   2008-11-04  visoh   ESCAN00031053 No changes
 *  4.07.00   2008-11-25  visoh   ESCAN00031593 Compiler Abstraction corrections
 *                                ESCAN00031361 No changes
 *                                ESCAN00031641 No changes
 *  4.07.01   2009-01-28  visoh   ESCAN00032597 No changes
 *                                ESCAN00033741 MISRA compliance
 *                                ESCAN00034046 No changes
 *  4.08.00   2009-06-18  visoh   ESCAN00033694 No changes in this file
 *                                ESCAN00034522 No changes in this file
 *                                ESCAN00034832 No changes in this file
 *                                ESCAN00035503 No changes in this file
 *  4.09.00   2009-07-21  visoh   ESCAN00036115 No changes in this file
 *                                ESCAN00036567 No changes in this file
 *  4.09.01   2009-09-17  visoh   ESCAN00037225 No changes in this file
 *  4.10.00   2009-10-07  visoh   ESCAN00037081 No changes in this file
 *                                ESCAN00037848 No changes in this file
 *                                ESCAN00039378 No changes in this file
 *  4.10.01   2010-03-03  visoh   ESCAN00039571 No changes in this file
 *  4.11.00   2010-03-25  visoh   ESCAN00041660 No changes in this file
 *                                ESCAN00041849 No changes in this file
 *  4.12.00   2010-04-28  visoh   ESCAN00042327 No changes in this file
 *                                ESCAN00042562 No changes in this file
 *  4.13.00   2010-06-16  visoh   ESCAN00043403 No changes in this file
 *  4.14.00   2010-07-07  visoh   ESCAN00043418 No changes in this file
 *                                ESCAN00043887 No changes in this file
 *  4.15.00   2010-08-19  visoh   ESCAN00044753 No changes in this file
 *                                ESCAN00044896 No changes in this file
 *  4.16.00   2010-08-20  visdhf  ESCAN00043787 No changes in this file
 *                                ESCAN00043772 No changes in this file
 *                                ESCAN00043794 No changes in this file
 *                                ESCAN00043785 No changes in this file
 *  4.17.00   2010-10-04  visoh   ESCAN00045764 No changes in this file
 *                                ESCAN00045879 No changes in this file
 *                                ESCAN00046097 Added Support for PduInfoType in APIs
 *                                ESCAN00046267 No changes in this file
 *                                ESCAN00046915 No changes in this file
 *                                ESCAN00047248 No changes in this file
 *                                ESCAN00047362 No changes in this file
 *                                ESCAN00047497 No changes in this file
 *                                ESCAN00048323 No changes in this file
 *                                ESCAN00048706 No changes in this file
 *                                ESCAN00048707 No changes in this file
 *  4.17.01   2011-04-28  vismdr  ESCAN00050304 No changes in this file
 *                                ESCAN00050423 No changes in this file
 *                                ESCAN00050470 No changes in this file
 *  4.17.02   2011-05-23  vismdr  ESCAN00051043 No changes in this file
 *  4.18.00   2011-05-16  vismdr  ESCAN00048297 No changes in this file
 *                                ESCAN00050076 No changes in this file
 *                                ESCAN00050080 No changes in this file
 *                                ESCAN00050282 No changes in this file
 *                                ESCAN00051150 Removed Support for non-PduInfoType APIs
 *                                ESCAN00051411 No changes in this file
 *                                ESCAN00051654 No changes in this file
 *                                ESCAN00051912 No changes in this file
 *  4.19.00   2011-10-05  vismdr  ESCAN00052254 No changes in this file
 *                                ESCAN00053229 No changes in this file
 *                                ESCAN00053565 No changes in this file
 *                                ESCAN00053603 No changes in this file
 *                                ESCAN00054369 No changes in this file
 *                                ESCAN00054839 No changes in this file
 *  4.19.01   2012-03-21  vismdr  ESCAN00056701 No changes in this file
 *                                ESCAN00057728 No changes in this file
 *                                ESCAN00057816 No changes in this file
 *  4.20.00   2012-06-12  vismdr  ESCAN00059355 No changes in this file
 *  4.21.00   2012-08-23  vismdr  ESCAN00059456 No changes in this file
 *                                ESCAN00060200 No changes in this file
 *  4.22.00   2013-04-10  vismdr  ESCAN00063982 No changes in this file
 *                                ESCAN00064042 No changes in this file
 *                                ESCAN00064221 No changes in this file
 *                                ESCAN00064767 No changes in this file
 *                                ESCAN00064796 No changes in this file
 *                                ESCAN00066109 No changes in this file
 *                                ESCAN00066499 No changes in this file
 *                                ESCAN00067173 No changes in this file
 *  4.22.01   2013-07-15  vismdr  ESCAN00068528 No changes in this file
 *  4.22.02   2013-09-30  vismdr  ESCAN00069312 No changes in this file
 *                                ESCAN00071869 No changes in this file
 *********************************************************************************************************************/

#if !defined (CANNM_CBK_H)
#define CANNM_CBK_H

/**********************************************************************************************************************
 * INCLUDES (CANNM082)
 *********************************************************************************************************************/
#include "CanNm_Cfg.h"                                                               /* Include CAN NM Configuration */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Component Version Information (BCD coded) */
#define CANNM_CBK_MAJOR_VERSION         (0x04u)
#define CANNM_CBK_MINOR_VERSION         (0x22u)
#define CANNM_CBK_PATCH_VERSION         (0x02u)

/* Definition of Callback API-Ids. */
#if ( ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF ) )
# define CANNM_TXCONFIRMATION_ID        (0x0Fu)
#endif
#define CANNM_RXINDICATION_ID           (0x10u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CANNM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Rx indication function for NM message. */
extern FUNC( void, CANNM_CODE ) CanNm_RxIndication( VAR( PduIdType, AUTOMATIC ) canNmRxPduId,
                                                    P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr );

#if ( ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF ) )
/* Tx confirmation function for NM message. */
extern FUNC( void, CANNM_CODE ) CanNm_TxConfirmation( VAR( PduIdType, AUTOMATIC ) canNmTxPduId );
#endif

#define CANNM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif  /* CANNM_CBK_H */

/********************************************7**************************************************************************
 *  END OF FILE: CanNm_Cbk.h
 *********************************************************************************************************************/
