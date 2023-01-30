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
 *         File:  Nm_Cbk.h
 *    Component:  AUTOSAR NM Interface
 *       Module:  AUTOSAR NM
 *    Generator:  -
 *
 *  Description:  Callback header of AUTOSAR Network Management Interface
 *                AUTOSAR Release 3.0
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Oliver Hornung                visoh         Vector Informatik GmbH
 *  Markus Drescher               vismdr        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  2.00.00   2007-07-23  visoh   ESCAN00021576 Update to AUTOSAR 3.0
 *                        vismas  ESCAN00022361 No changes
 *  2.01.00   2008-02-01  visoh   ESCAN00024708 Added Coordinator Synchronization Support
 *  2.02.00   2008-02-27  visoh   ESCAN00024931 No changes
 *  2.02.01   2008-03-06  visoh                 No changes
 *  2.03.00   2008-03-10  visoh   ESCAN00025260 Link-time configuration variant support for the number of channels
 *                                ESCAN00025261 Extended Coordinator Synchronization Support
 *  2.04.00   2008-03-30  visoh   ESCAN00025670 No changes
 *  2.05.00   2008-04-21  visoh   ESCAN00025482 No changes
 *                                ESCAN00026022 No changes
 *                                ESCAN00026252 No changes
 *  2.05.01   2008-04-23  visoh   ESCAN00026228 No changes
 *                                ESCAN00026487 No changes
 *                                ESCAN00026663 No changes
 *                                ESCAN00026866 No changes
 *  2.06.00   2008-05-30  visoh   ESCAN00027192 No changes
 *                                ESCAN00027193 No changes
 *  2.06.01   2008-06-19  vismas  ESCAN00027732 No changes
 *  2.07.00   2008-07-07  visoh   ESCAN00027720 No changes
 *                                ESCAN00027899 No changes
 *                                ESCAN00028004 No changes
 *  2.07.01   2008-08-08  visoh   ESCAN00029050 No changes
 *                                ESCAN00029133 No changes
 *  2.08.00   2008-08-08  visoh   ESCAN00028596 No changes
 *                                ESCAN00029046 Adaptation of include names
 *  2.08.01   2008-09-17  visoh   ESCAN00030021 No changes
 *  2.08.02   2008-09-18  visoh   ESCAN00030093 No changes
 *                                ESCAN00030107 No changes
 *  2.09.00   2008-09-23  visoh   ESCAN00030006 No changes
 *                                ESCAN00030120 No changes
 *                                ESCAN00030707 No changes
 *                                ESCAN00030724 No changes
 *  2.09.01   2008-09-24  visoh   ESCAN00031071 No changes
 *  2.10.00   2008-11-25  visoh   ESCAN00031593 Compiler Abstraction corrections
 *                                ESCAN00031961 No changes
 *                                ESCAN00032241 No changes
 *                                ESCAN00032242 No changes
 *                                ESCAN00032243 No changes
 *  2.10.01   2009-03-10  visoh   ESCAN00032478 No changes
 *                                ESCAN00033744 MISRA compliance and further optimizations
 *                                ESCAN00034048 No changes
 *                                ESCAN00034422 No changes
 *  2.10.02   2009-05-07  visoh   ESCAN00034830 No changes
 *  2.10.03   2009-06-22  visoh   ESCAN00034255 No changes in this file
 *                                ESCAN00035907 No changes in this file
 *  2.11.00   2009-07-23  visoh   ESCAN00034949 No changes in this file
 *                                ESCAN00036116 No changes in this file
 *                                ESCAN00036310 No changes in this file
 *                                ESCAN00036561 No changes in this file
 *                                ESCAN00036562 No changes in this file
 *                                ESCAN00036609 No changes in this file
 *  2.11.01   2009-08-27  visoh   ESCAN00037414 No changes in this file
 *  2.12.00   2009-11-13  visoh   ESCAN00039161 No changes in this file
 *  2.13.00   2010-06-16  visoh   ESCAN00043405 No changes in this file
 *                                ESCAN00043406 No changes in this file
 *                                ESCAN00043439 No changes in this file
 *                                ESCAN00043541 No changes in this file
 *  2.14.00   2010-06-30  visoh   ESCAN00043702 No changes in this file
 *                                ESCAN00043723 No changes in this file
 *                                ESCAN00043725 No changes in this file
 *                                ESCAN00043708 Added Gateway Extension
 *                                ESCAN00044061 No changes in this file
 *                                ESCAN00044134 No changes in this file
 *  2.15.00   2010-07-27  visoh   ESCAN00043781 No changes in this file
 *  2.16.00   2010-08-11  visoh   ESCAN00043776 Added Car Wakeup feature
 *                                ESCAN00043778 Added Setting of NM System Byte feature
 *                                ESCAN00043792 Added Partial Networking feature
 *                                ESCAN00044593 No changes in this file
 *  2.17.00   2010-09-30  visoh   ESCAN00045723 Removed Partial Networking feature
 *                                ESCAN00045745 No changes in this file
 *                                ESCAN00046522 Support Fiat Class B NM (MSR)
 *                                ESCAN00046271 No changes in this file
 *                                ESCAN00046777 No changes in this file
 *                                ESCAN00047251 No changes in this file
 *                                ESCAN00047596 No changes in this file
 *                                ESCAN00048718 No changes in this file
 *                                ESCAN00048796 No changes in this file
 *  2.17.01   2011-05-03  vismdr  ESCAN00049359 No changes in this file
 *  2.18.00   2011-06-01  vismdr  ESCAN00048490 No changes in this file
 *                                ESCAN00050087 Updated API ID for Nm_CarWakeUpIndication
 *                                ESCAN00051368 Updated some API IDs
 *                                ESCAN00051656 No changes in this file
 *                                ESCAN00051914 No changes in this file
 *                                ESCAN00052253 No changes in this file
 *  2.19.00   2011-12-01  vismdr  ESCAN00052258 Encapsulated pre-processor feature switches more explicitly
 *                                ESCAN00053241 No changes in this file
 *                                ESCAN00053242 No changes in this file
 *                                ESCAN00055736 No changes in this file
 *  2.19.01   2012-02-13  vismdr  ESCAN00055255 No changes in this file
 *                                ESCAN00056545 No changes in this file
 *                                ESCAN00057429 No changes in this file
 *  2.20.00   2012-06-12  vismdr  ESCAN00059354 No changes in this file
 *  2.21.00   2012-08-28  vismdr  ESCAN00057459 No changes in this file
 *                                ESCAN00061077 No changes in this file
 *  2.22.00   2012-11-21  vismdr  ESCAN00062789 Support Fiat Class C NM (MSR)
 *  2.23.00   2013-02-07  vismdr  ESCAN00064216 No changes in this file
 *                                ESCAN00064982 No changes in this file
 *                                ESCAN00065144 No changes in this file
 *  2.24.00   2013-04-09  vismdr  ESCAN00065186 No changes in this file
 *                                ESCAN00066111 No changes in this file
 *  2.25.00   2013-08-09  vismdr  ESCAN00069032 No changes in this file
 *                                ESCAN00069710 No changes in this file
 *********************************************************************************************************************/

#if !defined (NM_CBK_H)
#define NM_CBK_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "v_cfg.h"                                                            /* Include Vector configuration header */
#if defined ( VGEN_ENABLE_NM_OSEK_D ) && !defined ( VGEN_ENABLE_IF_ASRIFCAN )
# include "NmIf_Cfg.h"                                                          /* Include NM Interface Configuration */
#else
# include "Nm_Cfg.h"                                                            /* Include NM Interface Configuration */
#endif
#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
# include "Nm.h"                                                              /* Include Network Management Interface */
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
  /* vendor specific version information is BCD coded */
# if (  (NM_SW_MAJOR_VERSION != (0x02u)) \
     || (NM_SW_MINOR_VERSION != (0x25u)) \
     || (NM_SW_PATCH_VERSION != (0x00u)) )
#  error "Vendor specific version numbers of Nm.h and Nm_Cbk.h are inconsistent"
# endif
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Component Version Information (BCD coded) */
#define NM_CBK_MAJOR_VERSION    (0x02u)
#define NM_CBK_MINOR_VERSION    (0x25u)
#define NM_CBK_PATCH_VERSION    (0x00u)

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else
/* Definition of Callback API-Ids. */ /* ESCAN00051368 */
# define NM_NETWORKSTARTINDICATION_ID         (0x11u)
# define NM_NETWORKMODE_ID                    (0x12u)
# if ( NM_BUSNM_CANNM_ENABLED == STD_ON )
#  define NM_PREPAREBUSSLEEPMODE_ID           (0x13u)
# endif
# define NM_BUSSLEEPMODE_ID                   (0x14u)
# if ( NM_PDU_RX_INDICATION_ENABLED == STD_ON )
#  define NM_PDURXINDICATION_ID               (0x15u)
# endif
# if ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
#  define NM_STATECHANGENOTIFICATION_ID       (0x16u)
# endif
# if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
#  define NM_ACTIVECOORDINDICATION_ID         (0x1Cu)
# endif
# if ( NM_CAR_WAKE_UP_RX_ENABLED == STD_ON )
/* ESCAN00050087 */
#  define NM_CAR_WAKE_UP_INDICATION_ID        (0x1Du)
# endif
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#  define NM_REMOTESLEEPINDICATION_ID         (0x24u)
#  define NM_REMOTESLEEPCANCELLATION_ID       (0x25u)
# endif
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON )
#  define NM_REPEATMESSAGEINDICATION_ID       (0x28u)
# endif
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
#  define NM_TXTIMEOUTEXCEPTION_ID            (0x29u)
# endif

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

#define NM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*---------------- NM Interface callback functions ----------------*/

/* Notification that a NM-message has been received in the Bus-Sleep Mode. */
extern FUNC( void, NM_CODE ) Nm_NetworkStartIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

/* Notification that the network management has entered Network Mode. */
extern FUNC( void, NM_CODE ) Nm_NetworkMode( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

# if ( NM_BUSNM_CANNM_ENABLED == STD_ON ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || \
  defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
/* Notification that the network management has entered Prepare Bus-Sleep Mode. */
extern FUNC( void, NM_CODE ) Nm_PrepareBusSleepMode( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

/* Notification that the network management has entered Bus-Sleep Mode. */
extern FUNC( void, NM_CODE ) Nm_BusSleepMode( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

# if( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/* Notification that the network management has detected that all other nodes are ready to sleep. */
extern FUNC( void, NM_CODE ) Nm_RemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

/* Notification that the network management has detected that no more all other nodes are ready to sleep. */
extern FUNC( void, NM_CODE ) Nm_RemoteSleepCancellation( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

# if ( NM_PDU_RX_INDICATION_ENABLED == STD_ON )
/* Notification that a NM message has been received. */
extern FUNC( void, NM_CODE ) Nm_PduRxIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON )
/* Notification that a NM message has been received where a Repeat Message Bit is set. */
extern FUNC( void, NM_CODE ) Nm_RepeatMessageIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

# if ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
/* Notification that the CAN Generic NM state has changed. */
extern FUNC( void, NM_CODE ) Nm_StateChangeNotification( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONST( Nm_StateType, AUTOMATIC) nmPreviousState, CONST( Nm_StateType, AUTOMATIC ) nmCurrentState );
# endif

# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
/* Notification that a Tx Timeout occurred */
extern FUNC( void, NM_CODE ) Nm_TxTimeoutException( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

# if ( NM_CAR_WAKE_UP_RX_ENABLED == STD_ON )
extern FUNC( void, NM_CODE ) Nm_CarWakeUpIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif


# if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
extern FUNC( void, NM_CODE ) Nm_ActiveCoordIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONST( uint8, AUTOMATIC ) nmCoordPrio, CONST( uint8, AUTOMATIC ) nmSleepInd );
# endif


#define NM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* else defined ( NM_MACRO_LAYER_OPT_ENABLED ) */

#endif  /* NM_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: Nm_Cbk.h
 *********************************************************************************************************************/
