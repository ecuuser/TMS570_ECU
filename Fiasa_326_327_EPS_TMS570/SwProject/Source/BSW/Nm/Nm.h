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
 *         File:  Nm.h
 *    Component:  AUTOSAR NM Interface
 *       Module:  AUTOSAR NM
 *    Generator:  -
 *
 *  Description:  Header of AUTOSAR Generic Network Management Interface
 *                AUTOSAR Release 3.0
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Oliver Hornung                visoh         Vector Informatik GmbH
 *  Markus Schwarz                vismas        Vector Informatik GmbH
 *  Markus Drescher               vismdr        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  2.00.00   2007-07-23  visoh   ESCAN00021576 Update to AUTOSAR 3.0
 *                        vismas  ESCAN00022361 Added NM coordination feature
 *  2.01.00   2008-02-01  visoh   ESCAN00024708 No changes
 *  2.02.00   2008-02-27  visoh   ESCAN00024931 No changes
 *  2.02.01   2008-03-06  visoh                 No changes
 *  2.03.00   2008-03-10  visoh   ESCAN00025260 Link-time configuration variant support for the number of channels
 *                                ESCAN00025261 Extended Coordinator Synchronization Support
 *  2.04.00   2008-03-30  visoh   ESCAN00025670 Adapted Compiler Abstraction Macros
 *  2.05.00   2008-04-21  visoh   ESCAN00025482 No changes
 *                                ESCAN00026022 No changes
 *                                ESCAN00026252 No changes
 *  2.05.01   2008-04-23  visoh   ESCAN00026228 No changes
 *                                ESCAN00026487 API Naming corrected
 *                                ESCAN00026663 No changes
 *                                ESCAN00026866 No changes
 *  2.06.00   2008-05-30  vismas  ESCAN00027192 Corrected timing calculation
 *                                ESCAN00027193 Added support for CANNM-OSEKNM mix channel
 *  2.06.01   2008-06-19  vismas  ESCAN00027732 No changes
 *  2.07.00   2008-07-07  visoh   ESCAN00027720 No changes
 *                                ESCAN00027899 No changes
 *                                ESCAN00028004 No changes
 *  2.07.01   2008-08-08  visoh   ESCAN00029050 No changes
 *                                ESCAN00029133 No changes
 *  2.08.00   2008-08-08  visoh   ESCAN00028596 Extension for usage with ComM 2.1
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
 *  2.13.00   2010-06-16  visoh   ESCAN00043405 Added API to check limp home status of CAN NM and OSEK NM
 *                                ESCAN00043406 No changes in this file
 *                                ESCAN00043439 No changes in this file
 *                                ESCAN00043541 No changes in this file
 *  2.14.00   2010-06-30  visoh   ESCAN00043702 No changes in this file
 *                                ESCAN00043723 Corrected compile error for Check Limp Home API
 *                                ESCAN00043725 No changes in this file
 *                                ESCAN00043708 Added Gateway Extension
 *                                ESCAN00044061 No changes in this file
 *                                ESCAN00044134 No changes in this file
 *  2.15.00   2010-07-27  visoh   ESCAN00043781 No changes in this file
 *  2.16.00   2010-08-11  visoh   ESCAN00043776 Added Car Wakeup feature
 *                                ESCAN00043778 No changes in this file
 *                                ESCAN00043792 Added Partial Networking feature
 *                                ESCAN00044593 No changes in this file
 *  2.17.00   2010-09-30  visoh   ESCAN00045723 Removed Partial Networking feature
 *                                ESCAN00045745 Changed handling for FrNm and Com Control
 *                                ESCAN00046522 Support Fiat Class B NM (MSR)
 *                                ESCAN00046271 Adapted AUTOSAR version check
 *                                ESCAN00046777 No changes in this file
 *                                ESCAN00047251 No changes in this file
 *                                ESCAN00047596 No changes in this file
 *                                ESCAN00048718 No changes in this file
 *                                ESCAN00048796 No changes in this file
 *  2.17.01   2011-05-03  vismdr  ESCAN00049359 Adapted version check
 *  2.18.00   2011-06-01  vismdr  ESCAN00048490 No changes in this file
 *                                ESCAN00050087 No changes in this file
 *                                ESCAN00051368 Switched API IDs of Nm_DisableCommunication / Nm_EnableCommunication
 *                                ESCAN00051656 Removed version check for CanNm, FrNm
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
 *                                ESCAN00064982 Added Nm_InitMemory to NM_MACRO_LAYER_OPT_ENABLED definition block
 *                                ESCAN00065144 No changes in this file
 *  2.24.00   2013-04-09  vismdr  ESCAN00065186 No changes in this file
 *                                ESCAN00066111 No changes in this file
 *  2.25.00   2013-08-09  vismdr  ESCAN00069032 Adapted MISRA justifications
 *                                ESCAN00069710 No changes in this file
 *********************************************************************************************************************/

#if !defined (NM_H)
#define NM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "v_cfg.h"                                                            /* Include Vector configuration header */
#if defined ( VGEN_ENABLE_NM_OSEK_D ) && !defined ( VGEN_ENABLE_IF_ASRIFCAN )
# include "NmIf_Cfg.h"                                                         /* Include NM Interface Configuration */
#else
# include "Nm_Cfg.h"                                                           /* Include NM Interface Configuration */
#endif
#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#  include "ComM_Nm.h"                                                               /* Include ComM callback header */
# if ( NM_BUSNM_CANNM_ENABLED == STD_ON )
#  include "CanNm.h"                                                                        /* Include CAN NM Header */
# endif
# if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
#  include "FrNm.h"                                                                     /* Include FlexRay NM Header */
# endif
# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#  include "NmFiatB.h"                                                             /* Include Fiat Class B NM Header */
# endif
# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#  include "NmFiatC.h"                                                             /* Include Fiat Class C NM Header */
# endif
#endif


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Module internal check */
#if (  (NM_STACKTYPES_MAJOR_VERSION != (0x02u)) \
    || (NM_STACKTYPES_MINOR_VERSION != (0x25u)) \
    || (NM_STACKTYPES_PATCH_VERSION != (0x00u)))
# error "Vendor specific version numbers of NmStackTypes.h and Nm.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : Nm_AsrNmIf CQComponent : Implementation */
/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define NM_ASRNMIF_VERSION          (0x0225u)
#define NM_ASRNMIF_RELEASE_VERSION    (0x00u)

/* vendor and module identification */
#define NM_VENDOR_ID              (30u)
#define NM_MODULE_ID              (29u)

/* AUTOSAR Software Specification Version Information */
/* Document Version   1.0.1
   Part of Release    3.1
   Revision           0001, dated 2008-06-23 */
#define NM_AR_MAJOR_VERSION       (0x01u)
#define NM_AR_MINOR_VERSION       (0x00u)
#define NM_AR_PATCH_VERSION       (0x01u)

/* Component Version Information */
#define NM_SW_MAJOR_VERSION       (NM_ASRNMIF_VERSION >> 8u)
#define NM_SW_MINOR_VERSION       (NM_ASRNMIF_VERSION & 0x00FFu)
#define NM_SW_PATCH_VERSION       (NM_ASRNMIF_RELEASE_VERSION)


#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else

/* Definition of API-Ids. */
# define NM_INIT_ID                                 (0x00u)
# define NM_PASSIVESTARTUP_ID                       (0x01u)
# if (NM_PASSIVE_MODE_ENABLED == STD_OFF )
#  define NM_NETWORKREQUEST_ID                      (0x02u)
#  define NM_NETWORKRELEASE_ID                      (0x03u)
# endif
# if ( NM_COM_CONTROL_ENABLED == STD_ON )
#  define NM_DISABLENMCOMMUNICATION_ID              (0x04u)
#  define NM_ENABLENMCOMMUNICATION_ID               (0x05u)
# endif
# if ( NM_USER_DATA_ENABLED == STD_ON )
#  if (NM_PASSIVE_MODE_ENABLED == STD_OFF )
#   define NM_SETUSERDATA_ID                        (0x06u)
#  endif
#  define NM_GETUSERDATA_ID                         (0x07u)
# endif
# if ( ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) )
#  define NM_GETPDUDATA_ID                          (0x08u)
# endif
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON )
#  define NM_REPEATMESSAGEREQUEST_ID                (0x09u)
# endif
# if ( NM_NODE_ID_ENABLED == STD_ON )
#  define NM_GETNODEIDENTIFIER_ID                   (0x0Au)
#  define NM_GETLOCALNODEIDENTIFIER_ID              (0x0Bu)
# endif
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#  define NM_CHECKREMOTESLEEPIND_ID                 (0x0Du)
# endif
# define NM_GETSTATE_ID                             (0x0Eu)
# if ( NM_VERSION_INFO_API == STD_ON )
#  define NM_GETVERSIONINFO_ID                      (0x0Fu)
# endif
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
#  define NM_MAINFUNCTION_ID                        (0x10u)
# endif

  /* Error Codes that are reported to the Development Error Tracer. */
# if ( NM_DEV_ERROR_DETECT == STD_ON )
#  define NM_E_NO_INIT                  ((uint8)0x01u)    /* API service used without module initialization. */
#  define NM_E_INVALID_CHANNEL          ((uint8)0x02u)    /* API service used with wrong channel handle. */
#  define NM_E_INIT_FAILED              ((uint8)0x03u)    /* Nm initialization has failed */
#  define NM_E_NULL_POINTER             ((uint8)0x13u)    /* Null pointer has been passed as an argument. */
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
#   define NM_E_PRIORITY_COLLISION      ((uint8)0x20u)    /* Two coordinators with the same priority are connected to the same bus */
#   define NM_E_SLEEPBIT_ERROR          ((uint8)0x21u)    /* Sleep Indication Bit received on an active channel */
#  endif
# endif

#endif

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
/* ESCAN00051656 */

# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
/* Check for minimum NmFiatB version that has to be provided */
#  if ( (NM_ASRNMCLASSB_FIAT_VERSION < (0x0100u)) \
      || ( (NM_ASRNMCLASSB_FIAT_VERSION == (0x0100u)) && (NM_ASRNMCLASSB_FIAT_RELEASE_VERSION < (0x00u)) ) )
#   error "NmFiatB has to be provided at least with version 1.00.00"
#  endif
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
/* Check for minimum NmFiatC version that has to be provided */ /* ESCAN00062789 */
#  if ( (NM_ASRNMPWRTRAIN_FIAT_VERSION < (0x0100u)) \
      || ( (NM_ASRNMPWRTRAIN_FIAT_VERSION == (0x0100u)) && (NM_ASRNMPWRTRAIN_FIAT_RELEASE_VERSION < (0x00u)) ) )
#   error "NmFiatC has to be provided at least with version 1.00.00"
#  endif
# endif
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#if defined ( NM_MACRO_LAYER_OPT_ENABLED )

/* Mapping to Bus NM */
# if ( NM_BUSNM_CANNM_ENABLED == STD_ON )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#  define NmCallBusNmFunction( function, channel )                              CanNm_##function( (channel) )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#  define NmCallBusNmFunction_1_Param( function, channel, param )               CanNm_##function( (channel), (param) )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#  define NmCallBusNmFunction_2_Param( function, channel, param1, param2 )      CanNm_##function( (channel), (param1), (param2) )
# else
#  if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#   define NmCallBusNmFunction( function, channel )                             FrNm_##function( (channel) )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#   define NmCallBusNmFunction_1_Param( function, channel, param )              FrNm_##function( (channel), (param) )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#   define NmCallBusNmFunction_2_Param( function, channel, param1, param2 )     FrNm_##function( (channel), (param1), (param2) )
#  else
#   if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#    define NmCallBusNmFunction( function, channel )                            NmFiatB_##function( (channel) )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#    define NmCallBusNmFunction_1_Param( function, channel, param )             NmFiatB_##function( (channel), (param) )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#    define NmCallBusNmFunction_2_Param( function, channel, param1, param2 )    NmFiatB_##function( (channel), (param1), (param2) )
#   else
#    if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#     define NmCallBusNmFunction( function, channel )                           NmFiatC_##function( (channel) )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#     define NmCallBusNmFunction_1_Param( function, channel, param )            NmFiatC_##function( (channel), (param) )
/* PRQA S 0342 1 */ /* MD_NmIf_0342 */
#     define NmCallBusNmFunction_2_Param( function, channel, param1, param2 )   NmFiatC_##function( (channel), (param1), (param2) )
#    else
#     error "NM configuration error: Macro Layer Optimization enabled but no corresponding BusNm found!"
#    endif /* else NM_ENABLE_CHANNELTYPE_NMFIATC */
#   endif /* else NM_ENABLE_CHANNELTYPE_NMFIATB */
#  endif /* else ( NM_BUSNM_FRNM_ENABLED == STD_ON ) */
# endif /* else ( NM_BUSNM_CAN_ENABLED == STD_ON ) */

/* NM Interface services called by the application.*/
# define Nm_Init( cfgPtr )

/* ESCAN00064982 */
# define Nm_InitMemory()

# if ( NM_VERSION_INFO_API == STD_ON )
#  define Nm_GetVersionInfo( NmVerInfoPtr )    { if ( (NmVerInfoPtr) != NULL_PTR ) { \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->vendorID = (uint16)NM_VENDOR_ID; \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->moduleID = (uint8) NM_MODULE_ID; \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->instanceID = (uint8)0x00u; \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->sw_major_version = (uint8)NM_SW_MAJOR_VERSION; \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->sw_minor_version = (uint8)NM_SW_MINOR_VERSION; \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->sw_patch_version = (uint8)NM_SW_PATCH_VERSION; \
                                                 } \
                                               }  /* PRQA S 3458 */ /* MD_MSR_19.4 */
# endif

/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
# define Nm_PassiveStartUp( channel )                                     (NmCallBusNmFunction( PassiveStartUp, (channel) ))
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define Nm_NetworkRequest( channel )                                    (NmCallBusNmFunction( NetworkRequest, (channel) ))
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define Nm_NetworkRelease( channel )                                    (NmCallBusNmFunction( NetworkRelease, (channel) ))
# endif
# if ( NM_USER_DATA_ENABLED == STD_ON )
#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_COM_USER_DATA_ENABLED == STD_OFF )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#   define Nm_SetUserData( channel,  nmUserDataPtr )                      (NmCallBusNmFunction_1_Param( SetUserData, (channel), (nmUserDataPtr) ))
#  endif
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define Nm_GetUserData( channel,  nmUserDataPtr )                       (NmCallBusNmFunction_1_Param( GetUserData, (channel), (nmUserDataPtr) ))
# endif
# if ( NM_NODE_ID_ENABLED == STD_ON )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define Nm_GetNodeIdentifier( channel,  nmNodeIdPtr )                   (NmCallBusNmFunction_1_Param( GetNodeIdentifier, (channel), (nmNodeIdPtr) ))
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define Nm_GetLocalNodeIdentifier( channel,  nmNodeIdPtr )              (NmCallBusNmFunction_1_Param( GetLocalNodeIdentifier, (channel), (nmNodeIdPtr) ))
# endif
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define Nm_RepeatMessageRequest( channel )                              (NmCallBusNmFunction( RepeatMessageRequest, (channel) ))
# endif
# if ( ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define Nm_GetPduData( channel, nmPduDataPtr )                          (NmCallBusNmFunction_1_Param( GetPduData, (channel), (nmPduDataPtr) ))
# endif
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define Nm_CheckRemoteSleepIndication( channel,  nmRemoteSleepIndPtr )  (NmCallBusNmFunction_1_Param( CheckRemoteSleepIndication, (channel), (nmRemoteSleepIndPtr) ))
# endif
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
# define Nm_GetState( channel,  nmStatePtr, nmModePtr )                   (NmCallBusNmFunction_2_Param( GetState, (channel), (nmStatePtr), (nmModePtr) ))
# if ( NM_COM_CONTROL_ENABLED == STD_ON )
#  if ( NM_BUSNM_FRNM_ENABLED == STD_ON ) || ( NM_PASSIVE_MODE_ENABLED == STD_ON )
/* ESCAN00045745 */
#   define Nm_EnableCommunication( channel )                              (NM_E_NOT_EXECUTED)
#   define Nm_DisableCommunication( channel )                             (NM_E_NOT_EXECUTED)
#  else
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#   define Nm_EnableCommunication( channel )                              (NmCallBusNmFunction( EnableCommunication, (channel) ))
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#   define Nm_DisableCommunication( channel )                             (NmCallBusNmFunction( DisableCommunication, (channel) ))
#  endif
# endif

/* NM Interface callback functions */
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
# define Nm_NetworkStartIndication( channel )                             (ComM_Nm_NetworkStartIndication( (channel) ))
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
# define Nm_NetworkMode( channel )                                        (ComM_Nm_NetworkMode( (channel) ))
# if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
# else
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define Nm_PrepareBusSleepMode( channel )                               (ComM_Nm_PrepareBusSleepMode( (channel) ))
# endif
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
# define Nm_BusSleepMode( channel )                                       (ComM_Nm_BusSleepMode( (channel) ))

# if ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
#  if defined ( UL_Nm_StateChangeNotification )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#   define Nm_StateChangeNotification( channel, prevState, currState )    UL_Nm_StateChangeNotification( channel, prevState, currState )
#  else
#   define Nm_StateChangeNotification( channel, prevState, currState )
#  endif
# endif
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#  if defined ( UL_Nm_RemoteSleepIndication )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#   define Nm_RemoteSleepIndication( channel )                            UL_Nm_RemoteSleepIndication( channel )
#  else
#   define Nm_RemoteSleepIndication( channel )
#  endif
#  if defined ( UL_Nm_RemoteSleepCancellation )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#   define Nm_RemoteSleepCancellation( channel )                          UL_Nm_RemoteSleepCancellation( channel )
#  else
#   define Nm_RemoteSleepCancellation( channel )
#  endif
# endif
# if ( NM_PDU_RX_INDICATION_ENABLED == STD_ON )
#  if defined ( UL_Nm_PduRxIndication )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#   define Nm_PduRxIndication( channel )                                  UL_Nm_PduRxIndication( channel )
#  else
#   define Nm_PduRxIndication( channel )
#  endif
# endif
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON )
#  if defined ( UL_Nm_RepeatMessageIndication )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#   define Nm_RepeatMessageIndication( channel )                          UL_Nm_RepeatMessageIndication( channel )
#  else
#   define Nm_RepeatMessageIndication( channel )
#  endif
# endif
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if defined ( UL_Nm_TxTimeoutException )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#   define Nm_TxTimeoutException( channel )                               UL_Nm_TxTimeoutException( channel )
#  else
#   define Nm_TxTimeoutException( channel )
#  endif
# endif
# if ( NM_CAR_WAKE_UP_RX_ENABLED == STD_ON )
#  if defined ( UL_Nm_CarWakeUpIndication )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#   define Nm_CarWakeUpIndication( channel )                              UL_Nm_CarWakeUpIndication( channel )
#  else
#   define Nm_CarWakeUpIndication( channel )
#  endif
# endif


#endif /* defined ( NM_MACRO_LAYER_OPT_ENABLED ) */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else
#define NM_START_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* NM Interface version (BCD coded). */
extern CONST(uint8, NM_CONST) Nm_MainVersion;
extern CONST(uint8, NM_CONST) Nm_SubVersion;
extern CONST(uint8, NM_CONST) Nm_ReleaseVersion;

#define NM_STOP_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern FUNC( void, NM_CODE ) Nm_Init( P2CONST( Nm_ConfigType, AUTOMATIC, NM_CONST ) nmConfigPtr );
# if ( NM_VERSION_INFO_API == STD_ON )
extern FUNC( void, NM_CODE ) Nm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, NM_APPL_VAR ) NmVerInfoPtr );
# endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
extern FUNC( void, NM_CODE ) Nm_MainFunction( void );
# endif

extern FUNC( Nm_ReturnType, NM_CODE ) Nm_PassiveStartUp( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_NetworkRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_NetworkRelease( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

# if ( NM_USER_DATA_ENABLED == STD_ON )
#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_COM_USER_DATA_ENABLED == STD_OFF )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_SetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2CONST( uint8, AUTOMATIC, NM_APPL_VAR ) nmUserDataPtr );
#  endif

extern FUNC( Nm_ReturnType, NM_CODE ) Nm_GetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmUserDataPtr );
# endif

# if ( NM_NODE_ID_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_GetNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmNodeIdPtr );
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_GetLocalNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmNodeIdPtr );
# endif

# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_RepeatMessageRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

# if ( ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_GetPduData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmPduDataPtr );
# endif

# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_CheckRemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( boolean, AUTOMATIC, NM_APPL_VAR ) nmRemoteSleepIndPtr );
# endif

extern FUNC( Nm_ReturnType, NM_CODE ) Nm_GetState( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( Nm_StateType, AUTOMATIC, NM_APPL_VAR ) nmStatePtr, CONSTP2VAR( Nm_ModeType, AUTOMATIC, NM_APPL_VAR ) nmModePtr );

# if ( NM_COM_CONTROL_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_EnableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_DisableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
extern FUNC( void, NM_CODE ) Nm_InitMemory( void );
# else
#define Nm_InitMemory()
# endif






#define NM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* else defined ( NM_MACRO_LAYER_OPT_ENABLED ) */

#endif  /* NM_H */

/**********************************************************************************************************************
 *  END OF FILE: Nm.h
 *********************************************************************************************************************/
