
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
 *         File:  CanNm.h
 *    Component:  AUTOSAR CAN Network Management
 *       Module:  AUTOSAR Network Management
 *    Generator:  -
 *
 *  Description:  Header of AUTOSAR CAN Network Management
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
 *  4.01.00   2008-02-01  visoh   ESCAN00024714 Added Coordinator Synchronization Support
 *  4.02.00   2008-02-27  visoh   ESCAN00024920 No changes
 *  4.02.01   2008-03-03  visoh                 No changes
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
 *                                ESCAN00030159 Removed main function declaration
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
 *                                ESCAN00037848 Added NM User Data Support via Com
 *                                ESCAN00039378 No changes in this file
 *  4.10.01   2010-03-03  visoh   ESCAN00039571 No changes in this file
 *  4.11.00   2010-03-25  visoh   ESCAN00041660 No changes in this file
 *                                ESCAN00041849 Added QNX Support
 *  4.12.00   2010-04-28  visoh   ESCAN00042327 No changes in this file
 *                                ESCAN00042562 Added Feature 'Extended Bus Synchronization'
 *  4.13.00   2010-06-16  visoh   ESCAN00043403 Added API to check limp home status
 *  4.14.00   2010-07-07  visoh   ESCAN00043418 No changes in this file
 *                                ESCAN00043887 Added Support for NM Gateway
 *  4.15.00   2010-08-19  visoh   ESCAN00044753 Added CanNm_Transmit due to changed handling in PduR
 *                                ESCAN00044896 No changes in this file
 *  4.16.00   2010-08-20  visdhf  ESCAN00043787 No changes in this file
 *                                ESCAN00043772 Added Support for Car Wake Up
 *                                ESCAN00043794 Added Support for Partial Networking
 *                                ESCAN00043785 No changes in this file
 *  4.17.00   2010-10-04  visoh   ESCAN00045764 Changed some DEM errors to DET
 *                                ESCAN00045879 Reworked Partial Networking
 *                                ESCAN00046097 Added Support for PduInfoType in APIs
 *                                ESCAN00046267 Adapted AUTOSAR version check
 *                                ESCAN00046915 No changes in this file
 *                                ESCAN00047248 Corrected API handling for CanNm_Transmit
 *                                ESCAN00047362 No changes in this file
 *                                ESCAN00047497 No changes in this file
 *                                ESCAN00048323 No changes in this file
 *                                ESCAN00048706 No changes in this file
 *                                ESCAN00048707 No changes in this file
 *  4.17.01   2011-04-28  vismdr  ESCAN00050304 No changes in this file
 *                                ESCAN00050423 No changes in this file
 *                                ESCAN00050470 No changes in this file
 *  4.17.02   2011-05-23  vismdr  ESCAN00051043 Det errors have been made configurable
 *  4.18.00   2011-05-16  vismdr  ESCAN00048297 No changes in this file
 *                                ESCAN00050076 No changes in this file
 *                                ESCAN00050080 No changes in this file
 *                                ESCAN00050282 Added CanNm_ConfirmPnAvailability declaration, updated API IDs
 *                                ESCAN00051411 No changes in this file
 *                                ESCAN00051654 No changes in this file
 *                                ESCAN00051912 No changes in this file
 *  4.19.00   2011-10-05  vismdr  ESCAN00052254 Encapsulated pre-processor feature switches more explicitly
 *                                ESCAN00053229 No changes in this file
 *                                ESCAN00053565 No changes in this file
 *                                ESCAN00053603 No changes in this file
 *                                ESCAN00054369 No changes in this file
 *                                ESCAN00054839 No changes in this file
 *  4.19.01   2012-03-21  vismdr  ESCAN00056701 No changes in this file
 *                                ESCAN00057728 No changes in this file
 *                                ESCAN00057816 No changes in this file
 *  4.20.00   2012-06-12  vismdr  ESCAN00059355 Encapsulated pre-processor Com Control Enabled more explicitly
 *  4.21.00   2012-08-23  vismdr  ESCAN00059456 No changes in this file
 *                                ESCAN00060200 No changes in this file
 *  4.22.00   2013-04-10  vismdr  ESCAN00063982 No changes in this file
 *                                ESCAN00064042 No changes in this file
 *                                ESCAN00064221 No changes in this file
 *                                ESCAN00064767 No changes in this file
 *                                ESCAN00064796 No changes in this file
 *                                ESCAN00066109 No changes in this file
 *                                ESCAN00066499 Added function prototype of CanNm_DisablePNActivationState
 *                                ESCAN00067173 No changes in this file
 *  4.22.01   2013-07-15  vismdr  ESCAN00068528 No changes in this file
 *  4.22.02   2013-09-30  vismdr  ESCAN00069312 No changes in this file
 *                                ESCAN00071869 No changes in this file
 *********************************************************************************************************************/

#if !defined (CANNM_H)
#define CANNM_H

/**********************************************************************************************************************
 * INCLUDES (CANNM082)
 *********************************************************************************************************************/
#include "CanNm_Cfg.h"                                                               /* Include CAN NM Configuration */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : Nm_AsrNmCan CQComponent : Implementation */
/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define NM_ASRNMCAN_VERSION          (0x0422u)
#define NM_ASRNMCAN_RELEASE_VERSION  (0x02u)

/* CANNM021: vendor and module identification */
#define CANNM_VENDOR_ID              (30u)
#define CANNM_MODULE_ID              (31u)

/* CANNM021: AUTOSAR Software Specification Version Information (BCD coded) */
/* Document Version   3.0.1
   Part of Release    3.1
   Revision           0001, dated 2008-06-23 */
#define CANNM_AR_MAJOR_VERSION       (0x03u)
#define CANNM_AR_MINOR_VERSION       (0x00u)
#define CANNM_AR_PATCH_VERSION       (0x01u)

/* CANNM021: Component Version Information (BCD coded) */
#define CANNM_SW_MAJOR_VERSION       (NM_ASRNMCAN_VERSION >> 8)
#define CANNM_SW_MINOR_VERSION       (NM_ASRNMCAN_VERSION & 0x00FFu)
#define CANNM_SW_PATCH_VERSION       (NM_ASRNMCAN_RELEASE_VERSION)

/* Definition of API-Ids. */
#define CANNM_INIT_ID                             (0x00u)
#define CANNM_PASSIVESTARTUP_ID                   (0x01u)
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
# define CANNM_NETWORKREQUEST_ID                  (0x02u)
# define CANNM_NETWORKRELEASE_ID                  (0x03u)
#endif
#if ( CANNM_USER_DATA_ENABLED == STD_ON )
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if ( CANNM_COM_USER_DATA_ENABLED == STD_OFF )
#   define CANNM_SETUSERDATA_ID                   (0x04u)
#  endif
# endif
# define CANNM_GETUSERDATA_ID                     (0x05u)
#endif
#if ( CANNM_NODE_ID_ENABLED == STD_ON )
# define CANNM_GETNODEIDENTIFIER_ID               (0x06u)
# define CANNM_GETLOCALNODEIDENTIFIER_ID          (0x07u)
#endif
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
# define CANNM_REPEATMESSAGEREQUEST_ID            (0x08u)
#endif
#if ( ( CANNM_NODE_ID_ENABLED == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) )
# define CANNM_GETPDUDATA_ID                      (0x0Au)
#endif
#define CANNM_GETSTATE_ID                         (0x0Bu)
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
# define CANNM_DISABLENMCOMMUNICATION_ID          (0x0Cu)
# define CANNM_ENABLENMCOMMUNICATION_ID           (0x0Du)
#endif
#define CANNM_MAINFUNCTION_ID                     (0x13u)
#if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
/* ESCAN00050282 */
# define CANNM_TRANSMIT_ID                        (0x14u)
#endif
#if defined ( CANNM_ENABLE_COORD_SYNC_SUPPORT )
# define CANNM_SETCOORDINATORBITS_ID              (0x15u)
#endif
#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/* ESCAN00050282 */
# define CANNM_CONFIRMPNAVAILABILITY_ID           (0x16u)
#endif
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
# if ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
#  define CANNM_REQUESTBUSSYNC_ID                 (0xC0u)
# endif
#endif
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
# define CANNM_CHECKREMOTESLEEPIND_ID             (0xD0u)
#endif
#if ( CANNM_VERSION_INFO_API == STD_ON )
# define CANNM_GETVERSIONINFO_ID                  (0xF1u)
#endif
#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/* ESCAN00066499 */
# define CANNM_DISABLE_PN_ACTIVATION_STATE_ID     (0xFDu)
#endif

/* Error Codes that are reported to the Development Error Tracer. */
#if ( CANNM_DEV_ERROR_DETECT == STD_ON )
# define CANNM_E_NO_INIT                  ((uint8)0x01u)    /* API service used without module initialization */
# define CANNM_E_INVALID_CHANNEL          ((uint8)0x02u)    /* API service used with wrong channel handle */
# if ( CANNM_DEM2DET_ENABLED == STD_ON )
/* ESCAN00051043 */
#  define CANNM_E_INIT_FAILED             ((uint8)0x03u)    /* CanNm initialization has failed */
# endif
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF )
#  if ( CANNM_DEM2DET_ENABLED == STD_ON )
/* ESCAN00051043 */
#   define CANNM_E_CANIF_TRANSMIT_ERROR   ((uint8)0x05u)    /* Call of CanIf function CanIf_Transmit has failed. */
#  endif
#  define CANNM_E_DEV_NETWORK_TIMEOUT     ((uint8)0x11u)    /* NM-Timeout Timer has abnormally expired outside of the Ready Sleep State */
# endif
# define CANNM_E_NULL_POINTER             ((uint8)0x12u)    /* Null pointer has been passed as an argument */
/* Vector Extension */
# define CANNM_E_RXINDICATION_DLC_ERROR   ((uint8)0x20u)    /* DLC of received NM message does not match with configured PDU Length */
# if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
#  define CANNM_E_PDUR_TRIGGERTX_ERROR    ((uint8)0x21u)    /* Call of PduR_TriggerTransmit failed */
# endif
#endif

#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
/* The channel handle can be optimized in single channel configurations. */
/* Definition of channel parameter. */
# define CANNM_CHANNEL_SYSTEMTYPE_ONLY    void    /* PRQA S 3460 */ /* MD_MSR_19.4 */
# define CANNM_CHANNEL_SYSTEMTYPE_FIRST
#else
/* Definition of channel parameter. */
# define CANNM_CHANNEL_SYSTEMTYPE_ONLY    CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle
# define CANNM_CHANNEL_SYSTEMTYPE_FIRST   CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define CANNM_START_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* CAN NM version (BCD coded). */
extern CONST(uint8, CANNM_CONST) CanNm_MainVersion;
extern CONST(uint8, CANNM_CONST) CanNm_SubVersion;
extern CONST(uint8, CANNM_CONST) CanNm_ReleaseVersion;

#define CANNM_STOP_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CANNM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*------------------ CAN NM services called by Nm Interface. -----------------*/

extern FUNC( void, CANNM_CODE ) CanNm_Init( CONSTP2CONST( CanNm_ConfigType, AUTOMATIC, CANNM_PBCFG ) cannmConfigPtr );

extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_PassiveStartUp( CANNM_CHANNEL_SYSTEMTYPE_ONLY );

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_NetworkRequest( CANNM_CHANNEL_SYSTEMTYPE_ONLY );
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_NetworkRelease( CANNM_CHANNEL_SYSTEMTYPE_ONLY );
#endif

#if ( CANNM_USER_DATA_ENABLED == STD_ON )
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if ( CANNM_COM_USER_DATA_ENABLED == STD_OFF )
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_SetUserData( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2CONST( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmUserDataPtr );
#  endif
# endif
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_GetUserData( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmUserDataPtr );
#endif

#if ( CANNM_NODE_ID_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_GetNodeIdentifier( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmNodeIdPtr );
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_GetLocalNodeIdentifier( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmNodeIdPtr );
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_RepeatMessageRequest( CANNM_CHANNEL_SYSTEMTYPE_ONLY );
#endif

#if ( ( CANNM_NODE_ID_ENABLED == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) )
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_GetPduData( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmPduDataPtr );
#endif

extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_GetState( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( Nm_StateType, AUTOMATIC, CANNM_APPL_VAR ) nmStatePtr, CONSTP2VAR( Nm_ModeType, AUTOMATIC, CANNM_APPL_VAR ) nmModePtr );

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
# if ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_RequestBusSynchronization( CANNM_CHANNEL_SYSTEMTYPE_ONLY );
# endif
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_CheckRemoteSleepIndication( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( boolean, AUTOMATIC, CANNM_APPL_VAR ) nmRemoteSleepIndPtr );
#endif

#if ( CANNM_VERSION_INFO_API == STD_ON )
extern FUNC( void, CANNM_CODE ) CanNm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CANNM_APPL_VAR ) versioninfo);
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_EnableCommunication( CANNM_CHANNEL_SYSTEMTYPE_ONLY );
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_DisableCommunication( CANNM_CHANNEL_SYSTEMTYPE_ONLY );
#endif

#if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_Transmit( VAR( PduIdType, AUTOMATIC ) CanNmTxPduId, P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr);
#endif

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/* Notification for Pn Availability by CanSM */ /* ESCAN00050282 */
extern FUNC( void, CANNM_CODE ) CanNm_ConfirmPnAvailability( CANNM_CHANNEL_SYSTEMTYPE_ONLY );
#endif

/* Vector extension */
extern FUNC( void, CANNM_CODE ) CanNm_InitMemory( void );

#if defined ( CANNM_ENABLE_COORD_SYNC_SUPPORT )
/* Extension */
extern FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_SetCoordBits( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONST( uint8, AUTOMATIC ) nmCoordBits );
#endif



#if defined( CANNM_ENABLE_GET_CONTEXT ) || \
  (defined( VGEN_ENABLE_MDWRAP ) && defined( VQNX_ENABLE_CONTEXT_SWITCH ))
extern FUNC( void, CANNM_CODE ) CanNm_GetModuleContext( P2VAR(CanNm_ModuleContextStructType, AUTOMATIC, CANNM_APPL_VAR) pContext );
#endif

#if defined( CANNM_ENABLE_SET_CONTEXT ) || \
  (defined( VGEN_ENABLE_QWRAP ) && defined( VQNX_ENABLE_CONTEXT_SWITCH ))
extern FUNC( Nm_ReturnType, CANNM_CODE) CanNm_SetModuleContext( P2VAR(CanNm_ModuleContextStructType, AUTOMATIC, CANNM_APPL_VAR) pContext );
#endif

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/* ESCAN00066499 */
extern FUNC( void, CANNM_CODE ) CanNm_DisablePNActivationState( void );
#endif

#define CANNM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
/*******************************************************************************
* Channel Parameter optimization
*******************************************************************************/

/* The channel handle of the Generic NM services is only used in multi channel configurations. */
# if defined ( CANNM_SOURCE )
# else
/* These macros have to be defined after the prototype definitions. */
#  define CanNm_PassiveStartUp( channel )                                       CanNm_PassiveStartUp()
#  if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#   define CanNm_NetworkRequest( channel )                                      CanNm_NetworkRequest()
#   define CanNm_NetworkRelease( channel )                                      CanNm_NetworkRelease()
#  endif
#  if ( CANNM_USER_DATA_ENABLED == STD_ON )
#   if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_COM_USER_DATA_ENABLED == STD_OFF )
#    define CanNm_SetUserData( channel, nmUserDataPtr )                         CanNm_SetUserData( nmUserDataPtr )
#   endif
#   define CanNm_GetUserData( channel, nmUserDataPtr )                          CanNm_GetUserData( nmUserDataPtr )
#  endif
#  if ( CANNM_NODE_ID_ENABLED == STD_ON )
#   define CanNm_GetNodeIdentifier( channel, nmNodeIdPtr )                      CanNm_GetNodeIdentifier( nmNodeIdPtr )
#   define CanNm_GetLocalNodeIdentifier( channel, nmNodeIdPtr )                 CanNm_GetLocalNodeIdentifier( nmNodeIdPtr )
#  endif
#  if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
#   define CanNm_RepeatMessageRequest( channel )                                CanNm_RepeatMessageRequest()
#  endif
#  if ( ( CANNM_NODE_ID_ENABLED == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) )
#   define CanNm_GetPduData( channel, nmPduData )                               CanNm_GetPduData( nmPduData )
#  endif
#  define CanNm_GetState( channel, nmStatePtr, nmModePtr )                      CanNm_GetState( nmStatePtr, nmModePtr )
#  if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#   if ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
#    define CanNm_RequestBusSynchronization( channel )                          CanNm_RequestBusSynchronization()
#   endif
#  endif
#  if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#   define CanNm_CheckRemoteSleepIndication( channel, nmRemoteSleepIndPtr )     CanNm_CheckRemoteSleepIndication( nmRemoteSleepIndPtr )
#  endif
#  if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
#   define CanNm_EnableCommunication( channel )                                 CanNm_EnableCommunication()
#   define CanNm_DisableCommunication( channel )                                CanNm_DisableCommunication()
#  endif
#  if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
/* No optimization for CanNm_Transmit as calling in PduR is done from a table */
#  endif
#  if defined ( CANNM_ENABLE_COORD_SYNC_SUPPORT )
#   define CanNm_SetCoordBits( channel, nmCoordBits )                           CanNm_SetCoordBits( nmCoordBits )
#  endif
#  if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/* ESCAN00050282 */
#   define CanNm_ConfirmPnAvailability( channel )                               CanNm_ConfirmPnAvailability()
#  endif
# endif

#endif /* defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED ) */

#endif  /* CANNM_H */

/**********************************************************************************************************************
 *  END OF FILE: CanNm.h
 *********************************************************************************************************************/
