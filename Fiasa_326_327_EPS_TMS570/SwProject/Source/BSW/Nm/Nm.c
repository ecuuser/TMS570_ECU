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
 *         File:  Nm.c
 *    Component:  AUTOSAR NM Interface
 *       Module:  AUTOSAR NM
 *    Generator:  -
 *
 *  Description:  Implementation of AUTOSAR Generic Network Management Interface
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
 *  2.01.00   2008-02-01  visoh   ESCAN00024708 Added Coordinator Synchronization Support
 *  2.02.00   2008-02-27  visoh   ESCAN00024931 Fixed NM Coordination problem with Sleep / Wakeup and OSEK NM
 *  2.02.01   2008-03-06  visoh                 Adaptations for changed FlexRay NM configuration
 *  2.03.00   2008-03-10  visoh   ESCAN00025260 Link-time configuration variant support for the number of channels
 *                                ESCAN00025261 Extended Coordinator Synchronization Support
 *                                              Adapted MemMap Sections / Compiler Abstraction Macros
 *  2.04.00   2008-03-30  visoh   ESCAN00025670 Reworked Extended Coordinator Synchronization Support
 *                                              Adapted Compiler Abstraction Macros
 *  2.05.00   2008-04-21  visoh   ESCAN00025482 Code Optimizations
 *                                ESCAN00026022 Dependency corrected
 *                                ESCAN00026252 Adapted include naming
 *  2.05.01   2008-04-23  visoh   ESCAN00026228 MSR 3.0 Version check added
 *                                ESCAN00026487 API Naming corrected
 *                                ESCAN00026663 Generator Version check added
 *                                ESCAN00026866 Corrected issue with API services
 *  2.06.00   2008-05-30  vismas  ESCAN00027192 Corrected timing calculation
 *                                ESCAN00027193 Added support for CANNM-OSEKNM mix channel
 *  2.06.01   2008-06-19  vismas  ESCAN00027732 Adapted include and define for interaction with NmOsek
 *  2.07.00   2008-07-07  visoh   ESCAN00027720 Fixed Coordination Wake Up / Sleep issue
 *                                ESCAN00027899 Changed Instance ID reported to DET
 *                                ESCAN00028004 Corrected cast problems
 *  2.07.01   2008-08-08  visoh   ESCAN00029050 Corrected compile error with CAN-OSEK coordination
 *                                ESCAN00029133 Fixed CANNM-OSEKNM coordination issue
 *  2.08.00   2008-08-08  visoh   ESCAN00028596 Extension for usage with ComM 2.1
 *                                ESCAN00029046 No changes
 *  2.08.01   2008-09-17  visoh   ESCAN00030021 Corrected encapsulation of NM_INSTANCE_ID
 *  2.08.02   2008-09-18  visoh   ESCAN00030093 Corrected compiler errors
 *                                ESCAN00030107 Corrected encapsulation of OSEKNM_INT_CHANNEL
 *  2.09.00   2008-09-23  visoh   ESCAN00030006 Added PreCompile Crc Check
 *                                ESCAN00030120 Corrected synchronized OSEK NM channel handling
 *                                ESCAN00030707 Corrected Coordinator Sleep issue with OSEK NM (Coordinator Extension)
 *                                ESCAN00030724 Corrected Coordinator Sleep issue with FlexRay
 *  2.09.01   2008-09-24  visoh   ESCAN00031071 Adaptations due to changes in CanNm / FrNm
 *  2.10.00   2008-11-25  visoh   ESCAN00031593 Reworked Coordination Extension Algorithm
 *                                              Compiler Abstraction corrections
 *                                ESCAN00031961 No changes
 *                                ESCAN00032241 Corrected coordinator extension restart behavior
 *                                ESCAN00032242 Corrected coordinator extension restart behavior
 *                                ESCAN00032243 Corrected channel indirection issue for OSEK NM callbacks
 *  2.10.01   2009-03-10  visoh   ESCAN00032478 Added dummy statement to avoid compiler warnings
 *                                ESCAN00033744 Optimized setting of sleep bit (Coordinator Extension Support);
 *                                              MISRA compliance and further optimizations
 *                                ESCAN00034048 Corrected compiler warning
 *                                ESCAN00034422 Corrected passive start-up behavior for OSEK NM
 *  2.10.02   2009-05-07  visoh   ESCAN00034830 Corrected coordination timeout detection mechanism
 *  2.10.03   2009-06-22  visoh   ESCAN00034255 No changes in this file
 *                                ESCAN00035907 Improvements to avoid MISRA warnings
 *  2.11.00   2009-07-23  visoh   ESCAN00034949 Optimized access to bus-specific timing values (coordinator)
 *                                ESCAN00036116 Added pre-compile checks for library build
 *                                ESCAN00036310 Added error check for correct usage of OSEK NM
 *                                ESCAN00036561 Added exclusive area against interruption from any BusNm
 *                                ESCAN00036562 Potential data inconsistency corrected
 *                                ESCAN00036609 Extended 'Enable/Disable Communication' feature
 *  2.11.01   2009-08-27  visoh   ESCAN00037414 Removed pre-processor encapsulation of Nm_NetworkStartIndication
 *  2.12.00   2009-11-13  visoh   ESCAN00039161 Added NM User Data Support via Com
 *  2.13.00   2010-06-16  visoh   ESCAN00043405 Added API to check limp home status of CAN NM and OSEK NM
 *                                ESCAN00043406 Added state change notifications for OSEK NM
 *                                ESCAN00043439 Added extended OSEK NM initialization
 *                                ESCAN00043541 Corrected wake-up sequence for CAN-OSEK NM channels
 *  2.14.00   2010-06-30  visoh   ESCAN00043702 Added error check for state change handling on CAN-OSEK NM channels
 *                                ESCAN00043723 No changes in this file
 *                                ESCAN00043725 Corrected Check Limp Home API handling for CAN-OSEK NM channels
 *                                ESCAN00043708 Added Gateway Extension
 *                                ESCAN00044061 Corrected start notification handling
 *                                ESCAN00044134 Corrected start-up sequence issue with OSEK NM
 *  2.15.00   2010-07-27  visoh   ESCAN00043781 Added passive coordination for Coordinator Synchronization Support
 *  2.16.00   2010-08-11  visoh   ESCAN00043776 Added Car Wakeup feature
 *                                ESCAN00043778 No changes in this file
 *                                ESCAN00043792 Added Partial Networking feature
 *                                ESCAN00044593 No changes in this file
 *  2.17.00   2010-09-30  visoh   ESCAN00045723 Removed Partial Networking feature
 *                                ESCAN00045745 Changed handling for FrNm and Com Control
 *                                ESCAN00046522 Support Fiat Class B NM (MSR)
 *                                ESCAN00046271 Adapted AUTOSAR version check
 *                                ESCAN00046777 Support multiple configuration use case
 *                                ESCAN00047251 Corrected sleep sequence for passive coordination
 *                                ESCAN00047596 Corrected restart sequence for passive coordination
 *                                ESCAN00048718 Corrected compile error for Fiat Class B
 *                                ESCAN00048796 Corrected problem with invalid call of CanNm_GetNodeIdentifier
 *  2.17.01   2011-05-03  vismdr  ESCAN00049359 No changes in this file
 *  2.18.00   2011-06-01  vismdr  ESCAN00048490 Removed State Report Feature switch checks
 *                                ESCAN00050087 No changes in this file
 *                                ESCAN00051368 No changes in this file
 *                                ESCAN00051656 Removed version check for CanNm, FrNm
 *                                ESCAN00051914 Nm_PassiveStartUp: restart if OSEK NM is in Wait Bus Sleep mode
 *                                ESCAN00052253 Adapted typecasts for lines with shift operator (<<)
 *  2.19.00   2011-12-01  vismdr  ESCAN00052258 Encapsulated pre-processor feature switches more explicitly
 *                                ESCAN00053241 Removed non-SchM code for critical section handling
 *                                ESCAN00053242 No changes in this file
 *                                ESCAN00055736 No changes in this file
 *  2.19.01   2012-02-13  vismdr  ESCAN00055255 Actively coordinated channels are restarted if a condition to abort
 *                                              sleep on passively coordinated AUTOSAR NM channels is detected
 *                                ESCAN00056545 No changes in this file
 *                                ESCAN00057429 Added dummy statements for nmChannelHandle / channel parameter
 *  2.20.00   2012-06-12  vismdr  ESCAN00059354 Adapted Nm_DisableCommunication / Nm_EnableCommunication
 *  2.21.00   2012-08-28  vismdr  ESCAN00057459 Support Coordinator for OSEK NM channels only
 *                                ESCAN00061077 Added typecasts to assignment
 *  2.22.00   2012-11-21  vismdr  ESCAN00062789 Support Fiat Class C NM (MSR)
 *  2.23.00   2013-02-07  vismdr  ESCAN00064216 NM Coordinator: added support for Fiat Class B NM and Fiat Class C NM
 *                                ESCAN00064982 No changes in this file
 *                                ESCAN00065144 Added MISRA justification for more than 1024 macro definitions
 *  2.24.00   2013-04-09  vismdr  ESCAN00065186 Resetting Nm_CoordSleepInd flag on Coordinator Timeout
 *                                ESCAN00066111 Added run-time measurement support
 *  2.25.00   2013-08-09  vismdr  ESCAN00069032 Adapted MISRA justifications
 *                                ESCAN00069710 Extended State Change Notifications; added BusOff callbacks
 *********************************************************************************************************************/

/* PRQA S 0857 EOF */ /* MD_MSR_1.1 */ /* ESCAN00065144 */
#define NM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Nm.h"                                                              /* Include Network Management Interface */
#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else
# include "Nm_Cbk.h"                                                         /* Include NM Interface Callback Header */
#  include "ComM_Nm.h"                                                               /* Include ComM callback header */
# if ( NM_BUSNM_CANNM_ENABLED == STD_ON )
#  include "CanNm.h"                                                                        /* Include CAN NM Header */
# endif
# if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
#  include "FrNm.h"                                                                     /* Include FlexRay NM Header */
# endif
# if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
#  include "NmOsek.h"                                                                      /* Include OSEK NM Header */
# endif
# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#  include "NmFiatB.h"                                                             /* Include Fiat Class B NM Header */
# endif
# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#  include "NmFiatC.h"                                                             /* Include Fiat Class C NM Header */
# endif
# if ( NM_DEV_ERROR_DETECT == STD_ON )
#  include "Det.h"                                                               /* Include Development Error Tracer */
# endif
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
#  include "SchM_Nm.h"                                             /* Include Scheduler Module for Critical Sections */
# endif
#endif

#if defined ( NM_USE_EXTENDED_ASR_VERSION_CHECK )
# include "EcuM_Cbk.h"                                                                       /* EcuM Callback Header */
# include "v_ver.h"                                                                          /* Version Check Header */
#else
# if ( NM_CRC_CHECK == STD_ON )
#  include "EcuM_Cbk.h"                                                                      /* EcuM Callback Header */
# endif
#endif

#if ( NM_AMD_RUNTIME_MEASUREMENT == STD_ON )
# include "AmdRtm.h"             /* ESCAN00066111 */ /* AUTOSAR Monitoring and Debugging Run-Time Measurement Header */
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Vendor specific version information is BCD coded */
#if ( (NM_SW_MAJOR_VERSION != (0x02u)) \
   || (NM_SW_MINOR_VERSION != (0x25u)) \
   || (NM_SW_PATCH_VERSION != (0x00u)) )
# error "Vendor specific version numbers of Nm.c and Nm.h are inconsistent"
#endif

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
/* If Macro Layer Optimization is enabled all functions are mapped in the header file. */
#else
/* Vendor specific version information check */
# if ( (NM_CBK_MAJOR_VERSION != (0x02u)) \
    || (NM_CBK_MINOR_VERSION != (0x25u)) \
    || (NM_CBK_PATCH_VERSION != (0x00u)) )
#  error "Vendor specific version numbers of Nm.c and Nm_Cbk.h are inconsistent"
# endif

/* ESCAN00051656 */

# if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
/* Check for minimum OSEK NM version that has to be provided */
#  if ( (NM_DIROSEK_VERSION < (0x0385u)) \
      || ( (NM_DIROSEK_VERSION == (0x0385u)) && (NM_DIROSEK_RELEASE_VERSION < (0x00u)) ) )
#   error "OSEK NM has to be provided at least with version 3.85.00"
#  endif
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
/* Check for minimum NmFiatB version that has to be provided */ /* ESCAN00064216 */
#  if ( (NM_ASRNMCLASSB_FIAT_VERSION < (0x0102u)) \
      || ( (NM_ASRNMCLASSB_FIAT_VERSION == (0x0102u)) && (NM_ASRNMCLASSB_FIAT_RELEASE_VERSION < (0x00u)) ) )
#   error "NmFiatB has to be provided at least with version 1.02.00"
#  endif
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
/* Check for minimum NmFiatC version that has to be provided */ /* ESCAN00062789, ESCAN00064216 */
#  if ( (NM_ASRNMPWRTRAIN_FIAT_VERSION < (0x0101u)) \
      || ( (NM_ASRNMPWRTRAIN_FIAT_VERSION == (0x0101u)) && (NM_ASRNMPWRTRAIN_FIAT_RELEASE_VERSION < (0x00u)) ) )
#   error "NmFiatC has to be provided at least with version 1.01.00"
#  endif
# endif
#endif

/**********************************************************************************************************************
 *  LOCAL CONFIGURATION
 *********************************************************************************************************************/
# if ( defined ( NM_ENABLE_CHANNELTYPE_CANNM ) && defined ( NM_ENABLE_CHANNELTYPE_FRNM ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_CANNM ) && defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_CANNM ) && defined ( NM_ENABLE_CHANNELTYPE_NMFIATC ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_CANNM ) && defined ( NM_ENABLE_CHANNELTYPE_OSEKNM ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_CANNM ) && defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_FRNM ) && defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_FRNM ) && defined ( NM_ENABLE_CHANNELTYPE_NMFIATC ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_FRNM ) && defined ( NM_ENABLE_CHANNELTYPE_OSEKNM ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_FRNM ) && defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) && defined ( NM_ENABLE_CHANNELTYPE_NMFIATC ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) && defined ( NM_ENABLE_CHANNELTYPE_OSEKNM ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) && defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_NMFIATC ) && defined ( NM_ENABLE_CHANNELTYPE_OSEKNM ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_NMFIATC ) && defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) ) || \
     ( defined ( NM_ENABLE_CHANNELTYPE_OSEKNM ) && defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) )
#  define NM_ENABLE_MULTIPLE_NM_USAGE
# else
#  define NM_DISABLE_MULTIPLE_NM_USAGE
# endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
/* If Macro Layer Optimization is enabled all functions are mapped in the header file. */
#else

/* Magic Number Value for checking configurations */
# define NM_MAGIC_NUMBER_CHECK         (0xBABEu)

# define NM_INSTANCE_ID               ((uint8)0x00)

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
/* ESCAN00053241 */ /* PRQA S 3453 2 */ /* MD_MSR_19.7 */
#  define NM_ENTER_CRITICAL(critSection) SchM_Enter_Nm(critSection)
#  define NM_LEAVE_CRITICAL(critSection) SchM_Exit_Nm(critSection)
# endif

# if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#   define NM_ONM_CHANNEL_IDX         (localChannel)
#  else
#   define NM_ONM_CHANNEL_IDX         (channel)
#  endif
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
/* Mask for BusSleep and WaitBusSleep flags returned by NmGetStatus() */ /* ESCAN00051914 */
#  define NMDIROSEK_BUSSLEEP_OR_WAITBUSSLEEP_STATUS  (0x30)
# endif

# if ( ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_OSEK_SUPPORT_ENABLED == STD_ON ) ) \
  

/* derived from the ImAddressed information of the NmOsek */
#  define NMDIROSEK_TOKENATOWNNODE    (0x40)

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#   define NM_SYNC_ONM_CHANNEL        (Nm_PbConfigPtr->NM_SYNC_ONM_CHANNEL_ID)
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#    define NM_SYNC_ONM_CHANNEL_IND   (Nm_SystemToNmChannelInd[NM_SYNC_ONM_CHANNEL])
#   else
#    define NM_SYNC_ONM_CHANNEL_IND   NM_SYNC_ONM_CHANNEL
#   endif
#  else
#  endif

#  define OSEKNM_TRING                (((NmCountRingTyp_Field[nmOsekChannel]+1)*NmCallCycle_Field[nmOsekChannel])/Nm_LConfiguration.NM_MAIN_FUNCTION_PERIOD)
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#   define OSEKNM_TWAITBUSSLEEP       ((NmCountWaitBussleep_Field[nmOsekChannel]*NmCallCycle_Field[nmOsekChannel])/Nm_LConfiguration.NM_MAIN_FUNCTION_PERIOD)
#  else
#   define OSEKNM_TWAITBUSSLEEP       (Nm_LChannelConfiguration[NM_SYNC_ONM_CHANNEL_IND].NM_SHUTDOWN_TIME)
#  endif

# endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#   define NM_GWCOORD_CHANNEL         (0u)
#   define NM_GWCOORD_API_CHANNEL     
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) || (( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && \
      (defined ( NM_ENABLE_CHANNELTYPE_CANNM )   || defined ( NM_ENABLE_CHANNELTYPE_FRNM ) || \
       defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )))
#  define NM_CALCULATE_DELAY_TIME_SHUTDOWN_TIME_REQURIED
# endif
/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

# if defined ( NM_ENABLE_COORD_SYNC_SUPPORT ) \
  || ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
/* ----------- Local 8 Bit Data definitions without initialization need ----------- */
#define NM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */


#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
STATIC VAR( uint8, NM_VAR_NOINIT ) Nm_CoordPassiveChannels;
STATIC VAR( uint8, NM_VAR_NOINIT ) Nm_CoordPrio;
#  endif

#define NM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif

#endif /* else defined NM_MACRO_LAYER_OPT_ENABLED */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#if defined ( NM_USE_EXTENDED_ASR_VERSION_CHECK )
#define NM_START_SEC_CONST_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* The name of this const variable is defined via v_ver.h and depends on the version of the C file. 
   The value of the const variable is also defined externally and is used for consistency checks. */
CONST( uint32, NM_CONST ) NM_ASRNMIF_LIB_SYMBOL = NM_ASRNMIF_LIB_VERSION;

#define NM_STOP_SEC_CONST_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else

#define NM_START_SEC_CONST_8BIT
#include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* NM Interface version (BCD coded). */
CONST(uint8, NM_CONST) Nm_MainVersion      = (uint8)NM_SW_MAJOR_VERSION;
CONST(uint8, NM_CONST) Nm_SubVersion       = (uint8)NM_SW_MINOR_VERSION;
CONST(uint8, NM_CONST) Nm_ReleaseVersion   = (uint8)NM_SW_PATCH_VERSION;

#define NM_STOP_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define NM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if (NM_PASSIVE_MODE_ENABLED == STD_OFF )
STATIC FUNC( Nm_ReturnType, NM_CODE ) Nm_NmNetworkRequest( CONST( NetworkHandleType, AUTOMATIC ) channel );
STATIC FUNC( Nm_ReturnType, NM_CODE ) Nm_NmNetworkRelease( CONST( NetworkHandleType, AUTOMATIC ) channel );
# endif

#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
STATIC FUNC( Nm_ReturnType, NM_CODE ) Nm_RequestBusSynchronization( CONST( NetworkHandleType, AUTOMATIC ) channel );
#  endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
STATIC FUNC( void, NM_CODE ) Nm_CalculateDelayTime( void );
# else
# endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
STATIC FUNC( boolean, NM_CODE ) Nm_GetOverallRemoteSleepInd( void );
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
STATIC FUNC( Nm_ReturnType, NM_CODE ) Nm_SetCoordBits( CONST( NetworkHandleType, AUTOMATIC ) channel,
                                                       CONST( uint8, AUTOMATIC ) coordBits );
#  endif
# endif

# if defined ( NM_ONM_STATE_CHANGE_IND )
STATIC FUNC( void, NM_CODE ) Nm_TriggerOnmStateChangeNotification( CONST( NetworkHandleType, AUTOMATIC ) channel,
                                                                   CONST( Nm_StateType, AUTOMATIC ) newState );
# endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
/**********************************************************************************************************************
  Nm_RequestBusSynchronization
 **********************************************************************************************************************/
STATIC FUNC( Nm_ReturnType, NM_CODE ) Nm_RequestBusSynchronization( CONST( NetworkHandleType, AUTOMATIC ) channel )
{
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
  VAR( Nm_ReturnType, AUTOMATIC ) retVal = NM_E_NOT_OK; /* ESCAN00057459 */
#    else
  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#    endif

#    if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#     if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_CANNM )
#     endif
  {
    retVal = CanNm_RequestBusSynchronization( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#    endif
#    if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#     if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_FRNM )
#     endif
  {
    retVal = FrNm_RequestBusSynchronization( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#    endif
#    if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#     if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#     endif
  {
    retVal = CanNm_RequestBusSynchronization( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#    endif
#    if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#     if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#     endif
  {
    retVal = NmFiatB_RequestBusSynchronization( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#    endif
#    if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#     if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#     endif
  {
    retVal = NmFiatC_RequestBusSynchronization( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#    endif

#    if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#     if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
#     else
#      if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
           (defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
           (defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )                                                   ) || \
           (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )) || \
            defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )                                                    || \
            defined ( NM_ENABLE_CHANNELTYPE_NMFIATC ))
  (void)channel; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#      endif
#     endif
#    endif

  return retVal;
}
#  endif /* ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON ) */

# if (NM_PASSIVE_MODE_ENABLED == STD_OFF )
/**********************************************************************************************************************
  Nm_NmNetworkRequest
**********************************************************************************************************************/
STATIC FUNC( Nm_ReturnType, NM_CODE ) Nm_NmNetworkRequest( CONST( NetworkHandleType, AUTOMATIC ) channel )
{
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  VAR( Nm_ReturnType, AUTOMATIC ) retVal = NM_E_NOT_OK;
#  else
  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#  endif


#  if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_CANNM )
#   endif
  {
    retVal = CanNm_NetworkRequest( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_FRNM )
#   endif
  {
    retVal = FrNm_NetworkRequest( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#   endif
  {
    GotoMode( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, Awake );
    retVal = NM_E_OK;

#   if defined ( NM_ONM_STATE_CHANGE_IND )
    Nm_OnmNetworkRequested[channel] = NM_STATE_NORMAL_OPERATION;

    /* Currently in Ready Sleep? */
    if ( Nm_OnmState[channel] == NM_STATE_READY_SLEEP )
    {
      /* Update state */
      Nm_TriggerOnmStateChangeNotification( channel, NM_STATE_NORMAL_OPERATION );
    }
    else
    {
      /* State will be updated on callback:
       * - ApplNmCanNormal 
       * - ApplNmWaitBusSleepCancel
       * - ApplNmBusOffEnd
       */
    }
#   endif
  }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#   endif
  {
    GotoMode( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, Awake );
    retVal = CanNm_NetworkRequest( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#   endif
  {
    retVal = NmFiatB_NetworkRequest( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#   endif
  {
    retVal = NmFiatC_NetworkRequest( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#  endif

#  if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
#   else
#    if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )   && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_FRNM )    && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) && defined ( NMFIATB_OPTIMIZE_CHANNEL_ENABLED )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_NMFIATC ) && defined ( NMFIATC_OPTIMIZE_CHANNEL_ENABLED )))
  (void)channel; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif
#   endif
#  endif

  return retVal;
}

/**********************************************************************************************************************
  Nm_NmNetworkRelease
**********************************************************************************************************************/
STATIC FUNC( Nm_ReturnType, NM_CODE ) Nm_NmNetworkRelease( CONST( NetworkHandleType, AUTOMATIC ) channel )
{
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  VAR( Nm_ReturnType, AUTOMATIC ) retVal = NM_E_NOT_OK;
#  else
  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#  endif


#  if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_CANNM )
#   endif
  {
    retVal = CanNm_NetworkRelease( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_FRNM )
#   endif
  {
    retVal = FrNm_NetworkRelease( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#   endif
  {
    GotoMode( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, BusSleep );
    retVal = NM_E_OK;

#   if defined ( NM_ONM_STATE_CHANGE_IND )
    Nm_OnmNetworkRequested[channel] = NM_STATE_READY_SLEEP;

    /* Currently in Normal Operation? */
    if ( Nm_OnmState[channel] == NM_STATE_NORMAL_OPERATION )
    {
      /*  Update State */
      Nm_TriggerOnmStateChangeNotification( channel, NM_STATE_READY_SLEEP );
    }
    else
    {
      /* State will be updated on callback:
       * - ApplNmWaitBusSleep
       * - ApplNmBusOffEnd
       */
    }
#   endif
  }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#   endif
  {
    retVal = CanNm_NetworkRelease( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#   endif
  {
    retVal = NmFiatB_NetworkRelease( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#   endif
  {
    retVal = NmFiatC_NetworkRelease( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
  }
#  endif

#  if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
#   else
#    if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )   && defined ( NMFIATB_OPTIMIZE_CHANNEL_ENABLED )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )   && defined ( NMFIATC_OPTIMIZE_CHANNEL_ENABLED )))
  (void)channel; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif
#   endif
#  endif

  return retVal;
}
# endif  /* (NM_PASSIVE_MODE_ENABLED == STD_OFF ) */


# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
/**********************************************************************************************************************
  Nm_CalculateDelayTime
**********************************************************************************************************************/
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
STATIC FUNC( void, NM_CODE ) Nm_CalculateDelayTime( void )
#  else
#  endif
{
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  VAR( NetworkHandleType, AUTOMATIC ) channel;
#  endif
#  if defined ( NM_CALCULATE_DELAY_TIME_SHUTDOWN_TIME_REQURIED )
  VAR( Nm_TimerCounterType, AUTOMATIC ) shutdownTime;
#  endif
#  if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
  VAR( Nm_TimerCounterType, AUTOMATIC ) ringTime;
#  endif

#  if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  if( Nm_PbConfigPtr->NM_SYNC_ONM_CHANNEL_ID != 0xFFu )
#   endif
  {
    VAR( NmConfigType, AUTOMATIC ) nmConfig;
    VAR( uint8, AUTOMATIC ) ringCycles;
    VAR( uint8, AUTOMATIC ) byte;
    VAR( uint8, AUTOMATIC ) bit;
    VAR( uint8, AUTOMATIC ) nmOsekChannel;
    VAR( uint8, AUTOMATIC ) nrOfNodes = 0;

#   if ( NM_DEV_ERROR_DETECT == STD_ON )
#    if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
    if( ( Nm_LChannelConfiguration[NM_SYNC_ONM_CHANNEL_IND].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#     if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
      || ( Nm_LChannelConfiguration[NM_SYNC_ONM_CHANNEL_IND].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#     endif
     )
#    else
    /* Only called for CAN-OSEK channels */
#    endif
#   endif
    {

#   if defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
      nmOsekChannel = (uint8)NmSystemToNmIndirection[NM_SYNC_ONM_CHANNEL];
#   else
      nmOsekChannel = (uint8)NM_SYNC_ONM_CHANNEL;
#   endif
      GetConfig( NM_SYNC_ONM_CHANNEL, &nmConfig );

      for( byte = (uint8)(nmOsekChannel*(uint8)((NM_NUMBER_OF_CONFIG_NODES)/8));
        byte < ((nmOsekChannel+1)*(uint8)((NM_NUMBER_OF_CONFIG_NODES)/8)); byte++)
      {
        for( bit=0; bit<=7; bit++ )
        {
          if( ((nmConfig.nmConfigChar[byte]) & (uint8)(1<<bit)) != 0 )
          {
            nrOfNodes++;
          }
        }
      }

    }
#   if ( NM_DEV_ERROR_DETECT == STD_ON )
#    if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
    else
    {
      Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_MAINFUNCTION_ID, NM_E_INVALID_CHANNEL );
      /* avoid compiler warning */
      nmOsekChannel = 0u;
    }
#    else
    /* Only called for CAN-OSEK channels */
#    endif
#   endif

    /* calculate shutdown timestamp */
    ringTime = (Nm_TimerCounterType)(nrOfNodes * OSEKNM_TRING);


    /*lint -e414 */
    /* Division by Zero is not possible as ringTime is always > 0 (nrOfNodes is at least 1 
       due to own node is always available; OSEKNM_TRING must be always > 0) */

#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
    ringCycles = (uint8)((((Nm_PbConfigPtr->NM_COORD_SHUTDOWN_TIME - OSEKNM_TWAITBUSSLEEP)-1) / ringTime)+1);
#   endif


    /*lint +e414 */
    /* Re-activate check */


    ringTime = (Nm_TimerCounterType)(ringTime * (Nm_TimerCounterType)ringCycles); /* ESCAN00061077 */
#   if defined ( NM_CALCULATE_DELAY_TIME_SHUTDOWN_TIME_REQURIED )
    shutdownTime = (Nm_TimerCounterType)(ringTime + OSEKNM_TRING + OSEKNM_TWAITBUSSLEEP);
#   endif
    /* Use ringTime for calculation of OSEK NM delay timer */
    /* As synchronization can only be gained to one OSEK NM use this time for all synchronized OSEK NM channels */
    ringTime -= OSEKNM_TRING;
  }
#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  else
#   endif
#  endif /* ( NM_OSEK_SUPPORT_ENABLED == STD_ON ) */

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  {
#   if defined ( NM_CALCULATE_DELAY_TIME_SHUTDOWN_TIME_REQURIED )
    shutdownTime = (Nm_TimerCounterType)Nm_PbConfigPtr->NM_COORD_SHUTDOWN_TIME;
#   endif
#   if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
    /* Use ringTime for calculation of OSEK NM delay timer */
    /* In this case no synchronized OSEK NM channel exists, set time to 0 */
    ringTime = 0;
#   endif
  }
#  endif


#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  /* determine value of delay timer */
  for( channel=0; channel<Nm_LConfiguration.NM_NUMBER_OF_CHANNELS; channel++ )
#  endif
  {
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
    if( ((Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[channel] == NM_COORD_SYN_ACTIVE)
#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
      /* only if channel is actively coordinated and no sleep indication received */
      && (Nm_CoordChannel[channel] != FALSE) && (Nm_CoordSleepInd[channel] == 0u)
#   endif
      )
#  endif
    {
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
      if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#   endif
      {
        Nm_DelayTimer[channel] = ringTime;
      }
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
      else
#   endif
#  endif
#  if defined ( NM_DISABLE_MULTIPLE_NM_USAGE ) && ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#  else
      {
#   if defined(NM_CALCULATE_DELAY_TIME_SHUTDOWN_TIME_REQURIED)
        Nm_DelayTimer[channel] = (Nm_TimerCounterType)(shutdownTime - (Nm_LChannelConfiguration[channel].NM_SHUTDOWN_TIME));
#   endif
#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) && ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
        if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#    endif
        {
          Nm_DelayTimer_OsekNm[channel] = ringTime;
        }
#   endif
      }
#  endif

#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
      /* ESCAN00033744 */
      /* Set Sleep Bit on all coordinated channels */
      (void)Nm_SetCoordBits( channel, (uint8)( Nm_CoordPrio | NM_COORD_BIT_SLEEP) );
#  endif

      /* ESCAN00027192 */
      if( Nm_DelayTimer[channel] == (Nm_TimerCounterType)0u ) 
      {
        (void)Nm_RequestBusSynchronization( channel );
        (void)Nm_NmNetworkRelease( channel );
      }

#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
      /* ESCAN00029133 */
      if(
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
        (Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM) && 
#    endif
        (Nm_DelayTimer_OsekNm[channel] == (Nm_TimerCounterType)0u) )
      {
        GotoMode( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, BusSleep );
      }
#  endif

    }
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
    else
    {
      /* Ensure delay timer is 0 for not actively coordinated channels */
      Nm_DelayTimer[channel] = (Nm_TimerCounterType)0u;
    }
#  endif

  }
}  /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
# endif  /* ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_GW_EXT_ENABLED ) */

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/**********************************************************************************************************************
  Nm_GetOverallRemoteSleepInd
**********************************************************************************************************************/
STATIC FUNC( boolean, NM_CODE ) Nm_GetOverallRemoteSleepInd( void )
{
  VAR( NetworkHandleType, AUTOMATIC ) channel;
  VAR( boolean, AUTOMATIC ) remoteSleep = TRUE;

  /* check if all SYNC busses indicate RemoteSleepIndication */
  for( channel=0; channel<Nm_LConfiguration.NM_NUMBER_OF_CHANNELS; channel++ )
  {
    if( ( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[channel] == NM_COORD_SYN_ACTIVE )
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
      /* only if channel is actively coordinated */
      && ( Nm_CoordChannel[channel] != FALSE )
#  endif
     )
    {
      /* get RemoteSleepIndication of this SYNC channel
       * Note: If AUTOSAR Nm is not in Network mode, it does not execute the API
       *       and does not evaluate RemoteSleepIndication.
       *      => RemoteSleepIndication is considered as true in this case.
       *      => As remoteSleep is initialized with TRUE it has to be still TRUE.
       */
      (void)Nm_CheckRemoteSleepIndication( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, &remoteSleep );

      /* evaluate RemoteSleepIndication */
      if( remoteSleep == FALSE )
      {
        /* at least 1 SYNC channel does not indicate RemoteSleepIndication => SYNC networks are not ready to sleep
        * => abort API execution */
        break;
      }
    }
  }
  return remoteSleep;
}
# endif  /* ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) */

# if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
/**********************************************************************************************************************
  Nm_SetCoordBits
**********************************************************************************************************************/
STATIC FUNC( Nm_ReturnType, NM_CODE ) Nm_SetCoordBits( CONST( NetworkHandleType, AUTOMATIC ) channel,
                                                       CONST( uint8, AUTOMATIC ) coordBits )
{
#  if defined( NM_DISABLE_MULTIPLE_NM_USAGE ) && ( defined ( NM_ENABLE_CHANNELTYPE_CANNM ) || defined ( NM_ENABLE_CHANNELTYPE_FRNM ) )
  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#  else
  VAR( Nm_ReturnType, AUTOMATIC ) retVal = NM_E_NOT_OK;
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_CANNM )
#   endif
  {
    retVal = CanNm_SetCoordBits( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, coordBits );
  }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_FRNM )
#   endif
  {
    retVal = FrNm_SetCoordBits( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, coordBits );
  }
#  endif


#  if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
#   else
#    if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )))
  (void)channel; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif
#   endif
#  endif

  return retVal;
}
# endif

# if defined ( NM_ONM_STATE_CHANGE_IND )
/* ESCAN00069710 */
/**********************************************************************************************************************
  Nm_TriggerOnmStateChangeNotification
**********************************************************************************************************************/
STATIC FUNC( void, NM_CODE ) Nm_TriggerOnmStateChangeNotification( CONST( NetworkHandleType, AUTOMATIC ) channel,
                                                                   CONST( Nm_StateType, AUTOMATIC ) newState )
{
  if ( Nm_OnmState[channel] != newState )
  {
    Nm_StateChangeNotification( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, Nm_OnmState[channel], newState );
    Nm_OnmState[channel] = newState;
  }
}
# endif

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Nm_Init
**********************************************************************************************************************/
/*! \brief      Initialization of the Network Management by initializing the respective bus NM.
 *  \param[in]  nmConfigPtr               Configuration structure for initializing the module
 *  \pre        Interrupts must be disabled
 *  \context    System Startup
 *  \note       Called by application (EcuM)
**********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_Init( P2CONST( Nm_ConfigType, AUTOMATIC, NM_CONST ) nmConfigPtr )
{

# if defined ( NM_USE_EXTENDED_ASR_VERSION_CHECK ) || ( NM_CRC_CHECK == STD_ON ) \
  || ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || ( NM_OSEK_SUPPORT_ENABLED == STD_ON )

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
  VAR( NetworkHandleType, AUTOMATIC ) channel;
#  endif
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_OFF )
  P2CONST( Nm_ConfigType, AUTOMATIC, NM_CONST ) Nm_PbConfigPtr;
#  endif

  if( nmConfigPtr == NULL_PTR )
  {
    /* Use standard configuration */
    Nm_PbConfigPtr = &Nm_Configuration0;
  }
  else
  {
    /* CANNM060: Use selected configuration */
    Nm_PbConfigPtr = nmConfigPtr;
  }

  /* Check the magic number */
  if( Nm_PbConfigPtr->NM_MAGIC_NUMBER != NM_MAGIC_NUMBER_CHECK )
  {
#  if ( NM_DEV_ERROR_DETECT == STD_ON )
    /* Report initialization failure to DET */
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_INIT_ID, NM_E_INIT_FAILED );
#  endif
  }
  else
  {

#  if defined ( NM_USE_EXTENDED_ASR_VERSION_CHECK )
    /* Check the GENy Generator version */
    if( ((Nm_PbConfigPtr->Nm_GeneratorVersion & 0x00FFFF00) != 
      ( ((uint32)NM_ASRNMIF_GENTOOL_GENY_MAJOR_VERSION << 16) | ((uint32)NM_ASRNMIF_GENTOOL_GENY_MINOR_VERSION << 8)) )
#   if ( NM_ASRNMIF_GENTOOL_GENY_PATCH_VERSION != 0x00u )
      || ( (Nm_PbConfigPtr->Nm_GeneratorVersion & 0x000000FF) < (NM_ASRNMIF_GENTOOL_GENY_PATCH_VERSION) )
#   endif
     )
    {
      /*  Call the Vector specific EcuM Error callback */
      EcuM_GeneratorCompatibilityError((uint16)NM_MODULE_ID, NM_INSTANCE_ID);
    }
    else
#  endif
    {

#  if ( NM_CRC_CHECK == STD_ON )
      if( Nm_PbConfigPtr->Nm_Cfg_PrecompileCRC != NM_PRECOMPILE_CRC )
      {
        EcuM_GeneratorCompatibilityError( (uint16) NM_MODULE_ID, NM_INSTANCE_ID );
      }
      else
#  endif
      {

        /* system-specific initialization */
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
        Nm_NetworkRequested = 0u;
#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
        Nm_CoordPrio = (uint8)( (Nm_LConfiguration.NM_COORD_ID << NM_COORD_BIT_PRIO_POS) & NM_COORD_BIT_PRIO_MASK);
        Nm_CoordPassiveChannels = 0u;
#   endif
#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT ) || ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
        Nm_AbortSleep_BusNm[0] = (uint8)0u;
#   endif

#  endif

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
        /* channel specific */
        for( channel=0; channel<Nm_LConfiguration.NM_NUMBER_OF_CHANNELS; channel++ )
        {

#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
          /* Init Coordinator functionality */
          Nm_DelayTimer[channel] = (Nm_TimerCounterType)0u;
#    if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
          Nm_DelayTimer_OsekNm[channel] = (Nm_TimerCounterType)0u;
          Nm_NotifyNetworkStart[channel] = NM_NOTIFYSTARTSLEEP;
#    endif
#   endif
#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
          Nm_NetworkStarted[channel] = 0u;
#   endif

#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
          Nm_CoordActiveInd[channel] = 0u;
          Nm_CoordTimeoutTimer[channel] = (Nm_TimerCounterType)0u;
          if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[channel] == NM_COORD_SYN_PASSIVE )
          {
            Nm_CoordChannel[channel] = FALSE;
            Nm_CoordPassiveChannels++;
            Nm_CoordSleepInd[channel] = 1u; /* ESCAN00055255 */
          }
          else
          {
            Nm_CoordChannel[channel] = TRUE;
            Nm_CoordSleepInd[channel] = 0u; /* ESCAN00055255 */
          }
#   endif


#   if defined ( NM_ONM_STATE_CHANGE_IND )
          Nm_OnmState[channel] = NM_STATE_BUS_SLEEP;
          Nm_OnmNetworkRequested[channel] = NM_STATE_READY_SLEEP;
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
          /* init OSEK NM channels at the end (ESCAN00044134) */
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
          if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#    endif
          {
#    if defined ( NM_ONM_EXT_INIT )
            /* ESCAN00043439 */
            NmOsekInit( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, (NmInitType)Nm_LConfiguration.NM_ONM_EXT_INIT_STATE );
#     if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
            if( (NmInitType)Nm_LConfiguration.NM_ONM_EXT_INIT_STATE == NM_NORMAL )
            {
#      if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
              if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[channel] != NM_COORD_SEL )
              {
                Nm_NetworkRequested |= (Nm_NetworkCoordType)((Nm_NetworkCoordType)1u<<channel); /* ESCAN00052253 */
              }
#      endif
#      if defined ( NM_ONM_STATE_CHANGE_IND )
              /* No need to change Nm_OnmState[channel], is done by callback (ApplNmCanNormal) */
              Nm_OnmNetworkRequested[channel] = NM_STATE_NORMAL_OPERATION;
#      endif
            }
#     endif
#   else
            NmOsekInit( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, NM_CANSLEEP );
#    endif
          }
#   endif
#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
          if( Nm_LChannelConfiguration[channel].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM ) 
#    endif
          {
            NmOsekInit( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, NM_CANSLEEP );
          }
#   endif

        }

#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
        /* NM (re-)initialized */
        Nm_NetCoordState[0] = NM_SLEEP_WAITSLEEP;
#   endif
#  endif

      }
    }
  }
# else
#  if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  (void)nmConfigPtr;  /* PRQA S 3112 */ /* MD_NmIf_3112 */
#  endif
# endif
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */

# if ( NM_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 * Nm_GetVersionInfo
**********************************************************************************************************************/
/*! \brief      Return Version Info of this Module
 *  \param[out] NmVerInfoPtr                   Pointer to store the Version Information to
 *  \context    Function must only be called from task level.
 *  \note       Called by application
**********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, NM_APPL_VAR ) NmVerInfoPtr )
{
  if( NmVerInfoPtr != NULL_PTR )
  {
    NmVerInfoPtr->vendorID = (uint16)NM_VENDOR_ID;
    NmVerInfoPtr->moduleID = (uint8)NM_MODULE_ID;
    NmVerInfoPtr->instanceID = NM_INSTANCE_ID;
    NmVerInfoPtr->sw_major_version = (uint8)NM_SW_MAJOR_VERSION;
    NmVerInfoPtr->sw_minor_version = (uint8)NM_SW_MINOR_VERSION;
    NmVerInfoPtr->sw_patch_version = (uint8)NM_SW_PATCH_VERSION;
  }
#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  /* [BR:001] Common Handling for Version Info API */
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_GETVERSIONINFO_ID, NM_E_NULL_POINTER );
  }
#  endif

}
# endif /* ( NM_VERSION_INFO_API == STD_ON ) */

/**********************************************************************************************************************
 *  Nm_PassiveStartUp
 *********************************************************************************************************************/
/*! \brief      Calls the respective Bus Startup Function
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Start of network management has failed
 *  \return     NM_E_NOT_EXECUTED - Service not executed due to wrong state
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
 *********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_PassiveStartUp( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{

  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
# if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( defined ( NM_ENABLE_CHANNELTYPE_OSEKNM ) \
  && ( ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || \
       defined ( NM_ONM_STATE_CHANGE_IND ) ) )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#  endif
# endif
# if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( NM_DEV_ERROR_DETECT == STD_ON )
  retVal = NM_E_NOT_OK;
# endif

# if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#   endif
#  endif
   )
# endif
  {
# if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANNM )
#  endif
    {
      retVal = CanNm_PassiveStartUp( nmChannelHandle );
    }
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM )
#  endif
    {
      retVal = FrNm_PassiveStartUp( nmChannelHandle );
    }
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#  endif
    {
      /* ESCAN00027720, ESCAN00034422, ESCAN00051914 */
      if( (( NmGetStatus(nmChannelHandle) & NMDIROSEK_BUSSLEEP_OR_WAITBUSSLEEP_STATUS ) != 0u) )
      {
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
        if( ((Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_CHANNEL_IDX] == NM_COORD_SEL) || (Nm_NetCoordState[0] == NM_SLEEP_WAITSLEEP) )
#  else
#  endif
        {
          GotoMode( nmChannelHandle, Awake);
          GotoMode( nmChannelHandle, BusSleep);

#   if defined ( NM_ONM_STATE_CHANGE_IND )
          Nm_OnmNetworkRequested[NM_CHANNEL_IDX] = NM_STATE_READY_SLEEP;
          /* State will be updated on callback (ApplNmCanNormal / ApplNmWaitBusSleepCancel) */
#   endif
        }
        retVal = NM_E_OK;
      }
      else
      {
        retVal = NM_E_NOT_EXECUTED;
      }
    }
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#  endif
    {
      retVal = CanNm_PassiveStartUp( nmChannelHandle );
      /* OSEK NM will be started via Coordination Algorithm */
    }
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#  endif
    {
      retVal = NmFiatB_PassiveStartUp( nmChannelHandle );
    }
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#  endif
    {
      retVal = NmFiatC_PassiveStartUp( nmChannelHandle );
    }
# endif
  }

# if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_PASSIVESTARTUP_ID, NM_E_INVALID_CHANNEL );
  }
# endif

# if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || (NM_DEV_ERROR_DETECT == STD_ON)
#  else
#   if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
        (defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
        (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )) || \
        (defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )   && defined ( NMFIATB_OPTIMIZE_CHANNEL_ENABLED )) || \
        (defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )   && defined ( NMFIATC_OPTIMIZE_CHANNEL_ENABLED )))
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#   endif
#  endif
# endif

  return retVal;
}

# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
/**********************************************************************************************************************
 * Nm_NetworkRequest
**********************************************************************************************************************/
/*! \brief      Request bus-communication by calling the respective bus function
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Requesting bus-communication has failed
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_NetworkRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{

  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
# if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
# endif

# if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#  endif
   )
# endif
  {
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
    if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_CHANNEL_IDX] != NM_COORD_SEL )
    {
      NM_ENTER_CRITICAL(NM_EXCLUSIVE_AREA_0);
      /* store application request */
      Nm_NetworkRequested |= (Nm_NetworkCoordType)((Nm_NetworkCoordType)1u<<NM_CHANNEL_IDX); /* ESCAN00052253 */
      NM_LEAVE_CRITICAL(NM_EXCLUSIVE_AREA_0);
    }
#  else
#  endif
    retVal = Nm_NmNetworkRequest( NM_CHANNEL_IDX );
  }

#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_NETWORKREQUEST_ID, NM_E_INVALID_CHANNEL );
    retVal = NM_E_NOT_OK;
  }
#  endif

  return retVal;
}

/**********************************************************************************************************************
 * Nm_NetworkRelease
**********************************************************************************************************************/
/*! \brief      Release bus-communication by calling the respective bus
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Releasing bus-communication has failed
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_NetworkRelease( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{

  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#  endif

# if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#  endif
   )
# endif
  {
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
    if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_CHANNEL_IDX] == NM_COORD_SEL )
    {
      retVal = Nm_NmNetworkRelease( NM_CHANNEL_IDX );
    }
    else
    {
      NM_ENTER_CRITICAL(NM_EXCLUSIVE_AREA_0);
      /* ESCAN00052253 */
      Nm_NetworkRequested &= (Nm_NetworkCoordType)(~((uint32_least)((Nm_NetworkCoordType)1u<<NM_CHANNEL_IDX)));
      NM_LEAVE_CRITICAL(NM_EXCLUSIVE_AREA_0);
      retVal = NM_E_OK;
    }
#  else
    retVal = Nm_NmNetworkRelease( NM_CHANNEL_IDX );
#  endif
  }

#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_NETWORKRELEASE_ID, NM_E_INVALID_CHANNEL );
    retVal = NM_E_NOT_OK;
  }
#  endif

  return retVal;
}
# endif /* ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) */

/**********************************************************************************************************************
 * Nm_GetState
**********************************************************************************************************************/
/*! \brief      Return current state and mode of the network management by
 *              calling the respective bus function
 *  \param[out] nmStatePtr                  Pointer where the state of the Network Management shall be copied to
 *  \param[out] nmModePtr                   Pointer where the mode of the Network Management shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Getting the NM state has failed
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_GetState( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                            CONSTP2VAR( Nm_StateType, AUTOMATIC, NM_APPL_VAR ) nmStatePtr,
                                            CONSTP2VAR( Nm_ModeType, AUTOMATIC, NM_APPL_VAR ) nmModePtr )
{

# if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#  if defined ( NM_ONM_STATE_CHANGE_IND )
#  else
  VAR( uint8, AUTOMATIC ) nmState;
#  endif
# endif

  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
# if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || defined( NM_ONM_STATE_CHANGE_IND )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#  endif
# endif
# if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( NM_DEV_ERROR_DETECT == STD_ON )
  retVal = NM_E_NOT_OK;
# endif

# if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#   endif
#  endif
   )
# endif
  {

# if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANNM )
#  endif
    {
      retVal = CanNm_GetState( nmChannelHandle, nmStatePtr, nmModePtr );
    }
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM )
#  endif
    {
      retVal = FrNm_GetState( nmChannelHandle, nmStatePtr, nmModePtr );
    }
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#  endif
    {
#  if ( NM_DEV_ERROR_DETECT == STD_ON )
      if( (nmStatePtr == NULL_PTR) || (nmModePtr == NULL_PTR) )
      {
        Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_GETSTATE_ID, NM_E_NULL_POINTER );
      }
      else
#  endif
      {
#  if defined ( NM_ONM_STATE_CHANGE_IND )
        *nmStatePtr = Nm_OnmState[NM_CHANNEL_IDX];
        if ( Nm_OnmState[NM_CHANNEL_IDX] == NM_STATE_BUS_SLEEP )
        {
          *nmModePtr = NM_MODE_BUS_SLEEP;
        }
        else if ( Nm_OnmState[NM_CHANNEL_IDX] == NM_STATE_PREPARE_BUS_SLEEP )
        {
          *nmModePtr = NM_MODE_PREPARE_BUS_SLEEP;
        }
        else
        {
          *nmModePtr = NM_MODE_NETWORK;
        }
#  else
        nmState = NmGetStatus( nmChannelHandle );
        if( NmStateBusSleep(nmState) != 0 )
        {
          *nmStatePtr = NM_STATE_BUS_SLEEP;
          *nmModePtr = NM_MODE_BUS_SLEEP;
        }
        else if( NmStateWaitBusSleep(nmState) != 0 )
        {
          *nmStatePtr = NM_STATE_PREPARE_BUS_SLEEP;
          *nmModePtr = NM_MODE_PREPARE_BUS_SLEEP;
        }
        else if( NmStateBusSleepInd(nmState) != 0 )
        {
          *nmStatePtr = NM_STATE_READY_SLEEP;
          *nmModePtr = NM_MODE_NETWORK;
        }
        else
        {
          *nmStatePtr = NM_STATE_NORMAL_OPERATION;
          *nmModePtr = NM_MODE_NETWORK;
        }
#  endif
        retVal = NM_E_OK;
      }
    }
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#  endif
    {
      retVal = CanNm_GetState( nmChannelHandle, nmStatePtr, nmModePtr );
    }
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#  endif
    {
      retVal = NmFiatB_GetState( nmChannelHandle, nmStatePtr, nmModePtr );
    }
# endif

# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#  endif
    {
      retVal = NmFiatC_GetState( nmChannelHandle, nmStatePtr, nmModePtr );
    }
# endif

  }
# if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_GETSTATE_ID, NM_E_INVALID_CHANNEL );
  }
# endif

# if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || (NM_DEV_ERROR_DETECT == STD_ON)
#  else
#   if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
        (defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
        (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )) || \
        (defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )   && defined ( NMFIATB_OPTIMIZE_CHANNEL_ENABLED )) || \
        (defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )   && defined ( NMFIATC_OPTIMIZE_CHANNEL_ENABLED )))
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#   endif
#  endif
# endif

  return retVal;
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */

# if ( NM_USER_DATA_ENABLED == STD_ON )
#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_COM_USER_DATA_ENABLED == STD_OFF )
/**********************************************************************************************************************
* Nm_SetUserData
**********************************************************************************************************************/
/*! \brief      Set user data for NM messages transmitted next on the bus by 
 *              calling the respective bus function
 *  \param[in]  nmUserDataPtr               Pointer to User data for the next transmitted NM message
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Setting of user data has failed
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_SetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                               CONSTP2CONST( uint8, AUTOMATIC, NM_APPL_VAR ) nmUserDataPtr )
{

  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#    endif
#   endif
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( NM_DEV_ERROR_DETECT == STD_ON )
  retVal = NM_E_NOT_OK;
#   endif

#   if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#    if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#     if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#     endif
#    endif
   )
#   endif
  {

#   if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANNM )
#    endif
    {
      retVal = CanNm_SetUserData( nmChannelHandle, nmUserDataPtr );
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM )
#    endif
    {
      retVal = FrNm_SetUserData( nmChannelHandle, nmUserDataPtr );
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#    endif
    {
      retVal = CanNm_SetUserData( nmChannelHandle, nmUserDataPtr );
      /* OSEK NM User Data cannot be set via NM Interface */
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#    endif
    {
      retVal = NmFiatB_SetUserData( nmChannelHandle, nmUserDataPtr );
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#    endif
    {
      retVal = NmFiatC_SetUserData( nmChannelHandle, nmUserDataPtr );
    }
#   endif

  }
#   if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_SETUSERDATA_ID, NM_E_INVALID_CHANNEL );
  }
#   endif

#   if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || (NM_DEV_ERROR_DETECT == STD_ON)
#    else
#     if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
          (defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
          (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )))
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#     endif

#     if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
  /* NmFiatB / NmFiatC provides only a macro definition of NmFiatB_SetUserData / NmFiatC_SetUserData */
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
  (void)nmUserDataPtr;   /* PRQA S 3112 */ /* MD_NmIf_3112 */
#     endif
#    endif
#   endif

  return retVal;
}
#  endif /* ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_COM_USER_DATA_ENABLED == STD_OFF ) */

/**********************************************************************************************************************
* Nm_GetUserData
**********************************************************************************************************************/
/*! \brief      Get user data out of the last NM message received from the bus
 *              by calling the respective bus function
 *  \param[in]  nmUserDataPtr               Pointer where user data out of the last received NM message
                                            shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Getting of user data has failed
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_GetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                               CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmUserDataPtr )
{

  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#   endif
#  endif
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( NM_DEV_ERROR_DETECT == STD_ON )
  retVal = NM_E_NOT_OK;
#  endif

#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#    endif
#   endif
   )
#  endif
  {

#  if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANNM )
#   endif
    {
      retVal = CanNm_GetUserData( nmChannelHandle, nmUserDataPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM )
#   endif
    {
      retVal = FrNm_GetUserData( nmChannelHandle, nmUserDataPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#   endif
    {
      retVal = CanNm_GetUserData( nmChannelHandle, nmUserDataPtr );
      /* OSEK NM User Data cannot be read via NM Interface */
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#   endif
    {
      retVal = NmFiatB_GetUserData( nmChannelHandle, nmUserDataPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#   endif
    {
      retVal = NmFiatC_GetUserData( nmChannelHandle, nmUserDataPtr );
    }
#  endif

  }
#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_GETUSERDATA_ID, NM_E_INVALID_CHANNEL );
  }
#  endif

#  if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || (NM_DEV_ERROR_DETECT == STD_ON)
#   else
#    if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )))
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif

#    if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
  /* NmFiatB / NmFiatC provides only a macro definition of NmFiatB_GetUserData / NmFiatC_GetUserData */
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
  (void)nmUserDataPtr;   /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif
#   endif
#  endif

  return retVal;
}
# endif  /* ( NM_USER_DATA_ENABLED == STD_ON ) */

# if ( NM_NODE_ID_ENABLED == STD_ON )
/**********************************************************************************************************************
 * Nm_GetNodeIdentifier
**********************************************************************************************************************/
/*! \brief      Get node identifier of the last received NM message by
 *              calling the respective bus function
 *  \param[out] nmNodeIdPtr                 Pointer where node identifier from the last received NM message
 *                                          shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Getting of node identifier has failed
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_GetNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                     CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmNodeIdPtr )
{

  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#   endif
#  endif
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( NM_DEV_ERROR_DETECT == STD_ON )
  retVal = NM_E_NOT_OK;
#  endif

#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#    endif
#   endif
   )
#  endif
  {

#  if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANNM )
#   endif
    {
      retVal = CanNm_GetNodeIdentifier( nmChannelHandle, nmNodeIdPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM )
#   endif
    {
      retVal = FrNm_GetNodeIdentifier( nmChannelHandle, nmNodeIdPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#   endif
    {
      retVal = CanNm_GetNodeIdentifier( nmChannelHandle, nmNodeIdPtr );
      /* Not available for OSEK NM */
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#   endif
    {
      retVal = NmFiatB_GetNodeIdentifier( nmChannelHandle, nmNodeIdPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#   endif
    {
      retVal = NmFiatC_GetNodeIdentifier( nmChannelHandle, nmNodeIdPtr );
    }
#  endif

  }
#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_GETNODEIDENTIFIER_ID, NM_E_INVALID_CHANNEL );
  }
#  endif

#  if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || (NM_DEV_ERROR_DETECT == STD_ON)
#   else
#    if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )))
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif

#    if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
  /* NmFiatB / NmFiatC provides only a macro definition of NmFiatB_GetNodeIdentifier / NmFiatC_GetNodeIdentifier */
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
  (void)nmNodeIdPtr;     /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif
#   endif
#  endif


  return retVal;
}

/**********************************************************************************************************************
 * Nm_GetLocalNodeIdentifier
**********************************************************************************************************************/
/*! \brief      Get node identifier configured for the local node by
 *              calling the respective bus function
 *  \param[out] nmNodeIdPtr                 Pointer where node identifier of the local node shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Getting of local node identifier has failed
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_GetLocalNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                          CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmNodeIdPtr )
{

  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#   endif
#  endif
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( NM_DEV_ERROR_DETECT == STD_ON )
  retVal = NM_E_NOT_OK;
#  endif

#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#    endif
#   endif
   )
#  endif
  {

#  if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANNM )
#   endif
    {
      retVal = CanNm_GetLocalNodeIdentifier( nmChannelHandle, nmNodeIdPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM )
#   endif
    {
      retVal = FrNm_GetLocalNodeIdentifier( nmChannelHandle, nmNodeIdPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#   endif
    {
      retVal = CanNm_GetLocalNodeIdentifier( nmChannelHandle, nmNodeIdPtr );
      /* Not available for OSEK NM */
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#   endif
    {
      retVal = NmFiatB_GetLocalNodeIdentifier( nmChannelHandle, nmNodeIdPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#   endif
    {
      retVal = NmFiatC_GetLocalNodeIdentifier( nmChannelHandle, nmNodeIdPtr );
    }
#  endif

  }
#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_GETLOCALNODEIDENTIFIER_ID, NM_E_INVALID_CHANNEL );
  }
#  endif

#  if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || (NM_DEV_ERROR_DETECT == STD_ON)
#   else
#    if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )))
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif

#    if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
  /* NmFiatB / NmFiatC provides only a macro definition of NmFiatB_GetLocalNodeIdentifier /
   * NmFiatC_GetLocalNodeIdentifier
   */
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
  (void)nmNodeIdPtr;     /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif
#   endif
#  endif

  return retVal;
}
# endif /* ( NM_NODE_ID_ENABLED == STD_ON ) */

# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON )
/**********************************************************************************************************************
 * Nm_RepeatMessageRequest
**********************************************************************************************************************/
/*! \brief      Request state change to Repeat Message State by
 *              calling the respective bus function
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Repeat Message Request has failed
 *  \return     NM_E_NOT_EXECUTED - Service not executed due to wrong state
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_RepeatMessageRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{

  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#   endif
#  endif
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( NM_DEV_ERROR_DETECT == STD_ON )
  retVal = NM_E_NOT_OK;
#  endif

#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#    endif
#   endif
   )
#  endif
  {

#  if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANNM )
#   endif
    {
      retVal = CanNm_RepeatMessageRequest( nmChannelHandle );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM )
#   endif
    {
      retVal = FrNm_RepeatMessageRequest( nmChannelHandle );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#   endif
    {
      retVal = CanNm_RepeatMessageRequest( nmChannelHandle );
      /* Not available for OSEK NM */
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#   endif
    {
      retVal = NmFiatB_RepeatMessageRequest( nmChannelHandle );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#   endif
    {
      retVal = NmFiatC_RepeatMessageRequest( nmChannelHandle );
    }
#  endif

  }
#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_REPEATMESSAGEREQUEST_ID, NM_E_INVALID_CHANNEL );
  }
#  endif

#  if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || (NM_DEV_ERROR_DETECT == STD_ON)
#   else
#    if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )))
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif

#    if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
  /* NmFiatB / NmFiatC provides only a macro definition of NmFiatB_RepeatMessageRequest /
   * NmFiatC_RepeatMessageRequest
   */
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif
#   endif
#  endif


  return retVal;
}
# endif /* ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON ) */

# if ( ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) )
/**********************************************************************************************************************
 * Nm_GetPduData
**********************************************************************************************************************/
/*! \brief      Get the whole PDU data out of the last NM message received
 *              from the bus by calling the respective bus function
 *  \param[out] nmPduDataPtr                Pointer where PDU Data out of the most recently received NM message
 *                                          shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Getting the PDU data has failed
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_GetPduData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                              CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmPduDataPtr )
{

  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#   endif
#  endif
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( NM_DEV_ERROR_DETECT == STD_ON )
  retVal = NM_E_NOT_OK;
#  endif

#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#    endif
#   endif
   )
#  endif
  {

#  if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANNM )
#   endif
    {
      retVal = CanNm_GetPduData( nmChannelHandle, nmPduDataPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM )
#   endif
    {
      retVal = FrNm_GetPduData( nmChannelHandle, nmPduDataPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#   endif
    {
      retVal = CanNm_GetPduData( nmChannelHandle, nmPduDataPtr );
      /* OSEK NM PDU data cannot be read via NM Interface */
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#   endif
    {
      retVal = NmFiatB_GetPduData( nmChannelHandle, nmPduDataPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#   endif
    {
      retVal = NmFiatC_GetPduData( nmChannelHandle, nmPduDataPtr );
    }
#  endif

  }
#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_GETPDUDATA_ID, NM_E_INVALID_CHANNEL );
  }
#  endif

#  if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || (NM_DEV_ERROR_DETECT == STD_ON)
#   else
#    if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )))
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif

#    if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
  /* NmFiatB / NmFiatC provides only a macro definition of NmFiatB_GetPduData / NmFiatC_GetPduData */
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
  (void)nmPduDataPtr;    /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif
#   endif
#  endif

  return retVal;
}
# endif /* ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) */


# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/**********************************************************************************************************************
 * Nm_CheckRemoteSleepIndication
**********************************************************************************************************************/
/*! \brief      Check if remote sleep indication takes place or not by
 *              calling the respective bus function
 *  \param[out] nmRemoteSleepIndPtr                Pointer where remote sleep status shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Checking remote sleep indication has failed
 *  \return     NM_E_NOT_EXECUTED - Service not executed due to wrong state
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_CheckRemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                              CONSTP2VAR( boolean, AUTOMATIC, NM_APPL_VAR ) nmRemoteSleepIndPtr )
{

  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#   endif
#  endif
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( NM_OSEK_SUPPORT_ENABLED == STD_ON ) \
  || ( NM_DEV_ERROR_DETECT == STD_ON )
  retVal = NM_E_NOT_OK;
#  endif

#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#    endif
#   endif
   )
#  endif
  {

#  if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANNM )
#   endif
    {
      retVal = CanNm_CheckRemoteSleepIndication( nmChannelHandle, nmRemoteSleepIndPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM )
#   endif
    {
      retVal = FrNm_CheckRemoteSleepIndication( nmChannelHandle, nmRemoteSleepIndPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#   endif
    {

#   if ( NM_DEV_ERROR_DETECT == STD_ON )
      if( nmRemoteSleepIndPtr == NULL_PTR )
      {
        Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_CHECKREMOTESLEEPIND_ID, NM_E_NULL_POINTER );
      }
      else
#   endif
      {

        if( NmGetRemoteSleepInd(nmChannelHandle) == 0x00 )
        {
          *nmRemoteSleepIndPtr = FALSE;
        }
        else
        {
          *nmRemoteSleepIndPtr = TRUE;
        }
        retVal = NM_E_OK;

      }
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#   endif
    {

#   if ( NM_DEV_ERROR_DETECT == STD_ON )
      if( nmRemoteSleepIndPtr == NULL_PTR )
      {
        Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_CHECKREMOTESLEEPIND_ID, NM_E_NULL_POINTER );
      }
      else
#   endif
      {

        if( NmGetRemoteSleepInd(nmChannelHandle) == 0x00 )
        {
          *nmRemoteSleepIndPtr = FALSE;
          retVal = NM_E_OK;
        }
        else
        {
          retVal = CanNm_CheckRemoteSleepIndication( nmChannelHandle, nmRemoteSleepIndPtr );
        }

      }
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#   endif
    {
      retVal = NmFiatB_CheckRemoteSleepIndication( nmChannelHandle, nmRemoteSleepIndPtr );
    }
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#   endif
    {
      retVal = NmFiatC_CheckRemoteSleepIndication( nmChannelHandle, nmRemoteSleepIndPtr );
    }
#  endif

  }
#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_CHECKREMOTESLEEPIND_ID, NM_E_INVALID_CHANNEL );
  }
#  endif

#  if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || (NM_DEV_ERROR_DETECT == STD_ON)
#   else
#    if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
         (defined ( NM_ENABLE_CHANNELTYPE_FRNM )      && defined ( FRNM_OPTIMIZE_CHANNEL_ENABLED    )))
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif

#    if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#     if ( defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) && defined( NMFIATB_TYPE_MASTER ) ) || \
         ( defined ( NM_ENABLE_CHANNELTYPE_NMFIATC ) && defined( NMFIATC_MASTER_NODE ) )
#     else
  /* NmFiatB / NmFiatC provides only a macro definition of NmFiatB_CheckRemoteSleepIndication /
   * NmFiatC_CheckRemoteSleepIndication if this is no master node
   */
  (void)nmChannelHandle;     /* PRQA S 3112 */ /* MD_NmIf_3112 */
  (void)nmRemoteSleepIndPtr; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#     endif
#    endif
#   endif
#  endif


  return retVal;
}
# endif /* ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) */

# if ( NM_COM_CONTROL_ENABLED == STD_ON )
/**********************************************************************************************************************
 * Nm_EnableCommunication
**********************************************************************************************************************/
/*! \brief      Enable NM message transmission control status by calling
 *              the respective bus function
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Enable NM Message transmission control status has failed
 *  \return     NM_E_NOT_EXECUTED - Service not executed due to wrong state
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_EnableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#    endif
#   endif
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( NM_BUSNM_FRNM_ENABLED == STD_ON ) \
  || ( NM_DEV_ERROR_DETECT == STD_ON )
  retVal = NM_E_NOT_OK;
#   endif

#   if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#    if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#     if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#     endif
#    endif
   )
#   endif
  {

#   if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANNM )
#    endif
    {
      retVal = CanNm_EnableCommunication( nmChannelHandle );
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM )
#    endif
    {
      retVal = NM_E_NOT_EXECUTED;
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#    endif
    {
      TalkNM( nmChannelHandle );
      retVal = NM_E_OK;
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#    endif
    {
      TalkNM( nmChannelHandle );
      retVal = CanNm_EnableCommunication( nmChannelHandle );
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#    endif
    {
      retVal = NmFiatB_EnableCommunication( nmChannelHandle );
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#    endif
    {
      retVal = NmFiatC_EnableCommunication( nmChannelHandle );
    }
#   endif

  }
#   if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_ENABLENMCOMMUNICATION_ID, NM_E_INVALID_CHANNEL );
  }
#   endif

#   if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || (NM_DEV_ERROR_DETECT == STD_ON)
#    else
#     if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
          (defined ( NM_ENABLE_CHANNELTYPE_FRNM )                                                     ) || \
          (defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )   && defined ( NMFIATB_OPTIMIZE_CHANNEL_ENABLED )) || \
          (defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )   && defined ( NMFIATC_OPTIMIZE_CHANNEL_ENABLED )))
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#     endif
#    endif
#   endif

  return retVal;
#  else /* ( NM_PASSIVE_MODE_ENABLED != STD_OFF ) */
#   if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#   endif

  return NM_E_NOT_EXECUTED; /* ESCAN00059354 */ /* Transmission cannot be re-enabled if Passive Mode Enabled is ON */
#  endif
}

/**********************************************************************************************************************
 * Nm_DisableCommunication
**********************************************************************************************************************/
/*! \brief      Disable NM message transmission control status by calling
 *              the respective bus function
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Disable NM Message transmission control status has failed
 *  \return     NM_E_NOT_EXECUTED - Service not executed due to wrong state
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by application (ComM)
**********************************************************************************************************************/
FUNC( Nm_ReturnType, NM_CODE ) Nm_DisableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
  VAR( Nm_ReturnType, AUTOMATIC ) retVal;
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#    endif
#   endif
#   if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || ( NM_BUSNM_FRNM_ENABLED == STD_ON ) \
  || ( NM_DEV_ERROR_DETECT == STD_ON )
  retVal = NM_E_NOT_OK;
#   endif

#   if ( NM_DEV_ERROR_DETECT == STD_ON )
  if( (nmChannelHandle < Nm_LConfiguration.NM_NUMBER_OF_SYSTEM_CHANNELS)
#    if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#     if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (channel < Nm_LConfiguration.NM_NUMBER_OF_CHANNELS)
#     endif
#    endif
   )
#   endif
  {

#   if defined ( NM_ENABLE_CHANNELTYPE_CANNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANNM )
#    endif
    {
      retVal = CanNm_DisableCommunication( nmChannelHandle );
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_FRNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM )
#    endif
    {
      retVal = NM_E_NOT_EXECUTED;
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#    endif
    {
      SilentNM( nmChannelHandle );
      retVal = NM_E_OK;
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#    endif
    {
      SilentNM( nmChannelHandle );
      retVal = CanNm_DisableCommunication( nmChannelHandle );
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATB )
#    endif
    {
      retVal = NmFiatB_DisableCommunication( nmChannelHandle );
    }
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
#    endif
    {
      retVal = NmFiatC_DisableCommunication( nmChannelHandle );
    }
#   endif

  }
#   if ( NM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_DISABLENMCOMMUNICATION_ID, NM_E_INVALID_CHANNEL );
  }
#   endif

#   if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* ESCAN00057429 */
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE ) || (NM_DEV_ERROR_DETECT == STD_ON)
#    else
#     if ((defined ( NM_ENABLE_CHANNELTYPE_CANNM )     && defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED   )) || \
          (defined ( NM_ENABLE_CHANNELTYPE_FRNM )                                                     ) || \
          (defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )   && defined ( NMFIATB_OPTIMIZE_CHANNEL_ENABLED )) || \
          (defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )   && defined ( NMFIATC_OPTIMIZE_CHANNEL_ENABLED )))
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#     endif
#    endif
#   endif
  return retVal;
#  else /* ( NM_PASSIVE_MODE_ENABLED != STD_OFF ) */
#   if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_NmIf_3112 */
#   endif

  return NM_E_NOT_EXECUTED; /* ESCAN00059354 */ /* Transmission cannot be disabled if Passive Mode Enabled is ON */
#  endif
}
# endif /* ( NM_COM_CONTROL_ENABLED == STD_ON ) */





# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/**********************************************************************************************************************
 * Nm_InitMemory
**********************************************************************************************************************/
/*! \brief      Initialize Memory, so that expected start values are set
 *  \pre        Interrupts are disabled
 *  \context    System startup
 *  \note       Called by application
 *  \note       Vector Extension [BR:011]
**********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_InitMemory( void )
{
  {
    Nm_NetCoordState[NM_GWCOORD_CHANNEL] = NM_UNINITIALIZED;
  }
}
# endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/**********************************************************************************************************************
 * Nm_MainFunction
**********************************************************************************************************************/
/*! \brief      Task function implements the coordination / gateway handling.
 *              It checks if networks have to be set to sleep or woken-up
 *  \pre        NM is initialized
 *  \context    Function must only be called from task level.
 *  \note       Scheduled by the BSW scheduler
**********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_MainFunction( void )
{
#  if ( ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_OSEK_SUPPORT_ENABLED == STD_ON ) )
  VAR( NmStatusType, AUTOMATIC ) nmStatus;
#  endif
  VAR( NetworkHandleType, AUTOMATIC ) channel;
  VAR( boolean, AUTOMATIC ) sleepCondition;
#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
  VAR( Nm_NetworkCoordType, NM_VAR_NOINIT ) Nm_CoordSleepIndChannels;
#   endif

  /* Init check */
  if( Nm_NetCoordState[0] != NM_UNINITIALIZED )
  {

    NM_ENTER_CRITICAL(NM_EXCLUSIVE_AREA_1);

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
    /* Check Coordinator Active Indication / Active Timeout */
    sleepCondition = (boolean)(Nm_NetworkRequested == (Nm_NetworkCoordType)0u);

    Nm_CoordSleepIndChannels = 0u;
    for( channel=0; channel<Nm_LConfiguration.NM_NUMBER_OF_CHANNELS; channel++ )
    {
      /* Check Coordination state */
      if( Nm_CoordActiveInd[channel] != 0u )
      {
        Nm_CoordActiveInd[channel] = 0u;
        /* Set Coordinator passive */
        if( Nm_CoordChannel[channel] != FALSE )
        {
          Nm_CoordChannel[channel] = FALSE;
          (void)Nm_SetCoordBits( channel, (uint8)NM_COORD_BIT_INV_MASK );
          Nm_CoordPassiveChannels++;
          if( Nm_NetCoordState[0] == NM_SLEEP_WAITANNOUNCESLEEP )
          {
            (void)Nm_NmNetworkRelease( channel );
#    if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
            /* Use Delay Timer as Restart Indication for FrNm */
            Nm_DelayTimer[channel] = (Nm_TimerCounterType)0u;
#    endif
          }
        }

        if( Nm_CoordSleepInd[channel] == 0u )
        {
          /* Reset Coordination Timer with short timeout value (no shutdown) */
          Nm_CoordTimeoutTimer[channel] = (Nm_TimerCounterType)(2*(Nm_LChannelConfiguration[channel].NM_MSG_CYCLE_TIME+1));
          /* Restart from Shutdown? */
          if( Nm_NetCoordState[0] > NM_SLEEP_WAITANNOUNCESLEEP )
          {
            sleepCondition = FALSE;
          }
        }
        else
        {
          /* Reset Coordination Timer with long timeout value (shutdown) */
          Nm_CoordTimeoutTimer[channel] = (Nm_TimerCounterType)(Nm_LChannelConfiguration[channel].NM_SHUTDOWN_TIME
            +Nm_LChannelConfiguration[channel].NM_MSG_CYCLE_TIME);
        }
      }

      /* Check if coordinator has to be active again */
      if( Nm_CoordTimeoutTimer[channel] > (Nm_TimerCounterType)0u )
      {
        Nm_CoordTimeoutTimer[channel]--;
        if( Nm_CoordTimeoutTimer[channel] == (Nm_TimerCounterType)0u )
        {
          /* Set Priority */
          (void)Nm_SetCoordBits( channel, Nm_CoordPrio );
          /* Set Coordinator active again */
          Nm_CoordChannel[channel] = TRUE;
          Nm_CoordPassiveChannels--;
          /* Restart if no sleep indication received */
          if( Nm_CoordSleepInd[channel] == 0u )
          {
            sleepCondition = FALSE;
          }
          else if ( Nm_NetCoordState[0] == NM_AWAKE )
          {
            Nm_CoordSleepInd[channel] = 0u; /* ESCAN00065186 */
          }
          else
          {
            /* Intentionally left empty */
          }
        }
      }

      /* Count Sleep Indications of passive coordinated channels */
      if( /* ESCAN00055255 */ (Nm_CoordChannel[channel] == FALSE) && (Nm_CoordSleepInd[channel] != 0u) )
      {
        Nm_CoordSleepIndChannels++;
      }
    }

    if( sleepCondition != FALSE )
    {
      NM_ENTER_CRITICAL(NM_EXCLUSIVE_AREA_0);
      /* SYNC sleep condition:
      * sleep condition is true as long as there is no SYNC network request by application or
      * not any sync active coordinated network indicates a RemoteSleep */
      sleepCondition = Nm_GetOverallRemoteSleepInd();
      NM_LEAVE_CRITICAL(NM_EXCLUSIVE_AREA_0);
    }
#   else
    NM_ENTER_CRITICAL(NM_EXCLUSIVE_AREA_0);
    /* SYNC sleep condition:
    * sleep condition is true as long as there is no SYNC network request by application or
    * not any sync active coordinated network indicates a RemoteSleep */
    sleepCondition = (boolean)((Nm_GetOverallRemoteSleepInd()) && ((boolean)(Nm_NetworkRequested == 0x00)));
    NM_LEAVE_CRITICAL(NM_EXCLUSIVE_AREA_0);
#   endif
#  endif

    {

      switch( Nm_NetCoordState[NM_GWCOORD_CHANNEL] )
      {
        /*-------------------- Awake --------------------*/
      case NM_AWAKE:
        /* Shutdown */
        if( sleepCondition != FALSE )
        {
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT ) || ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
          /* ESCAN00030707 */
          Nm_AbortSleep_BusNm[NM_GWCOORD_CHANNEL] = 0u;
#  endif
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
          if( Nm_CoordPassiveChannels != 0u )
          {
            for( channel=0; channel<Nm_LConfiguration.NM_NUMBER_OF_CHANNELS; channel++ )
            {
              if( Nm_CoordChannel[channel] == FALSE )
              {
                /* Release Communication on passive coordinated channel */
                (void)Nm_NmNetworkRelease( channel );
#    if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
                /* Use Delay Timer as Restart Indication for FrNm */
                Nm_DelayTimer[channel] = (Nm_TimerCounterType)0u;
#    endif
              }
            }
            Nm_NetCoordState[0] = NM_SLEEP_WAITANNOUNCESLEEP;
          }
          else
#   endif
#  endif
          {

#  if ( ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_OSEK_SUPPORT_ENABLED == STD_ON ) )
#    if ( ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_OSEK_SUPPORT_ENABLED == STD_ON ) )
            if( Nm_PbConfigPtr->NM_SYNC_ONM_CHANNEL_ID != 0xFFu )
#    endif
            {
              Nm_NetCoordState[NM_GWCOORD_CHANNEL] = NM_SLEEP_WAITTOKEN;
            }
            else
#  endif

            {
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
              Nm_CalculateDelayTime();
#  endif
              Nm_NetCoordState[NM_GWCOORD_CHANNEL] = NM_SLEEP_WAITSLEEP;
            }
          }
        }
        break;

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
        /*-------------------- Wait Announce Sleep --------------------*/
      case NM_SLEEP_WAITANNOUNCESLEEP:
        if( (sleepCondition != FALSE) && (Nm_AbortSleep_BusNm[0] == 0u) )
        {
          /* Sleep Indication for all passive channels */
          if( Nm_CoordSleepIndChannels == Nm_CoordPassiveChannels )
          {
            Nm_CalculateDelayTime();
            Nm_NetCoordState[0] = NM_SLEEP_WAITSLEEP;
          }
        }
        else
        {
          /* Restart all coordinated channels as channel may changed from passive to active */
          for( channel=0; channel<Nm_LConfiguration.NM_NUMBER_OF_CHANNELS; channel++ )
          {
            if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[channel] != NM_COORD_SEL )
            {

              /* ESCAN00047596: Restart Indication for channels that are in sleep */
              if( Nm_NetworkStarted[channel] == 0x00u )
              {
                ComM_Nm_RestartIndication( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
              }

              (void)Nm_NmNetworkRequest( channel );
#    if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
              /* Use Delay Timer as Restart Indication for FrNm */
              Nm_DelayTimer[channel] = (Nm_TimerCounterType)1u;
#    endif
              /* ESCAN00047251: Clear Sleep Indication Flag */
              Nm_CoordSleepInd[channel] = 0u;

            }
          }
          Nm_NetCoordState[0] = NM_AWAKE;
        }
        break;
#   endif
#  endif

#  if ( ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_OSEK_SUPPORT_ENABLED == STD_ON ) )
        /*-------------------- Wait Token --------------------*/
      case NM_SLEEP_WAITTOKEN:
        if( sleepCondition != FALSE )
        {
#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
          nmStatus = NmGetStatus( Nm_PbConfigPtr->NM_SYNC_ONM_CHANNEL_ID );
#   endif
          if( ((nmStatus & NMDIROSEK_TOKENATOWNNODE) != 0) || (NmStateLimphome(nmStatus)) )
          {
            Nm_NetCoordState[NM_GWCOORD_CHANNEL] = NM_SLEEP_WAITTOKENLOSS;
          }
        }
        else
        {
          Nm_NetCoordState[NM_GWCOORD_CHANNEL] = NM_AWAKE;
        }
        break;
#  endif

#  if ( ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_OSEK_SUPPORT_ENABLED == STD_ON ) )
        /*-------------------- Wait Token Loss --------------------*/
      case NM_SLEEP_WAITTOKENLOSS:
        if( sleepCondition != FALSE )
        {
#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
          nmStatus = NmGetStatus( Nm_PbConfigPtr->NM_SYNC_ONM_CHANNEL_ID );
#   endif
          if( (nmStatus & NMDIROSEK_TOKENATOWNNODE) == 0 )
          {
            Nm_CalculateDelayTime( NM_GWCOORD_API_CHANNEL );
            Nm_NetCoordState[NM_GWCOORD_CHANNEL] = NM_SLEEP_WAITSLEEP;
          }
        }
        else
        {
          Nm_NetCoordState[NM_GWCOORD_CHANNEL] = NM_AWAKE;
        }
        break;
#  endif

        /*-------------------- Wait Sleep --------------------*/
      default:
        if( (sleepCondition != FALSE)
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT ) || ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
            && (Nm_AbortSleep_BusNm[NM_GWCOORD_CHANNEL] == 0u)
#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
            && (Nm_CoordSleepIndChannels == Nm_CoordPassiveChannels) /* ESCAN00055255 */
#   endif
#  endif
           )
        {

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#    if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
          for( channel=0; channel<Nm_LConfiguration.NM_NUMBER_OF_CHANNELS; channel++ )
#    endif
          {
            /* Note: Timer of a not coordinated channel is always 0 */
            if( Nm_DelayTimer[channel] != (Nm_TimerCounterType)0u )
            {
              Nm_DelayTimer[channel]--;
              if( Nm_DelayTimer[channel] == (Nm_TimerCounterType)0u )
              {
                (void)Nm_RequestBusSynchronization( channel );
                (void)Nm_NmNetworkRelease( channel );
              }
            }

#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
            /* Note: Timer of a not coordinated channel is always 0 */
            if( Nm_DelayTimer_OsekNm[channel] > (Nm_TimerCounterType)0u )
            {
              Nm_DelayTimer_OsekNm[channel]--;
              if( Nm_DelayTimer_OsekNm[channel] == (Nm_TimerCounterType)0u )
              {
                GotoMode( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID, BusSleep );
              }
            }
#   endif

          }
#  endif
        }
        /* Restart / Wake Up */
        else
        {
          /* Change state as soon as possible to avoid problems with PassiveStartUp */
          Nm_NetCoordState[NM_GWCOORD_CHANNEL] = NM_AWAKE;

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
          for( channel=0; channel<Nm_LConfiguration.NM_NUMBER_OF_CHANNELS; channel++ )
#  endif
          {
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
            if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[channel] != NM_COORD_SEL )
#  endif
            {

              /* Restart Indication for channels that are in sleep */
              if( Nm_NetworkStarted[channel] == 0x00u )
              {
                ComM_Nm_RestartIndication( Nm_LChannelConfiguration[channel].NM_CHANNEL_ID );
              }

              /* request channel */
              (void)Nm_NmNetworkRequest( channel );

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )

#    if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
              /* Use Delay Timer as Restart Indication for FrNm */
              Nm_DelayTimer[channel] = (Nm_TimerCounterType)1u;
#    endif

              /* Reset Coordination handling */
              if( Nm_CoordChannel[channel] != FALSE )
              {
                (void)Nm_SetCoordBits( channel, (uint8)(Nm_CoordPrio) );
              }
              else
              {
                if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[channel] == NM_COORD_SYN_ACTIVE )
                {
                  Nm_CoordTimeoutTimer[channel] = (Nm_TimerCounterType)(2*(Nm_LChannelConfiguration[channel].NM_MSG_CYCLE_TIME+1));
                }
              }
              Nm_CoordSleepInd[channel] = 0u;
#   endif
#  endif

            }
          }

        }
        break;
      }

    } /* channel-specific handling */

    NM_LEAVE_CRITICAL(NM_EXCLUSIVE_AREA_1);

  }  /* init check */

#  if ( NM_DEV_ERROR_DETECT == STD_ON )
#   if defined ( NM_IDENTITY_MANAGER_CONFIG )
  /* ESCAN00046777: Do not report a DET error as component could be uninitialized in this configuration */
#   else
  else
  {
    Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_MAINFUNCTION_ID, NM_E_NO_INIT );
  }
#   endif
#  endif

}  /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
# endif

/**********************************************************************************************************************
 * Nm_NetworkStartIndication
 *********************************************************************************************************************/
/*! \brief      Notification that a NM-message has been received in the Bus-Sleep Mode
 *  \context    Function must only be called from task level.
 *  \note       Called by BusNm Main Functions (CanNm, FrNm, NmOsek, NmFiatB, NmFiatC)
 *********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_NetworkStartIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  ComM_Nm_NetworkStartIndication( nmChannelHandle );
}

# if ( NM_BUSNM_CANNM_ENABLED == STD_ON ) || ( NM_BUSNM_FRNM_ENABLED == STD_ON ) \
  || defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
/**********************************************************************************************************************
 * Nm_NetworkMode
 *********************************************************************************************************************/
/*! \brief      Notification that the network management has entered Network Mode
 *  \context    Function must only be called from task level.
 *  \note       Called by BusNm Main Functions (CanNm, FrNm, NmFiatB, NmFiatC)
 *********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_NetworkMode( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#   endif
#  endif


#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
  if( Nm_NotifyNetworkStart[NM_CHANNEL_IDX] != NM_SUPPRESSNOTIFYSTART )
#   endif
#  endif
  {

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && ( NM_STATE_CHANGE_IND_ENABLED == STD_OFF )
    Nm_NotifyNetworkStart[NM_CHANNEL_IDX] = NM_SUPPRESSNOTIFYSTART;
#   endif
    Nm_NetworkStarted[NM_CHANNEL_IDX] = 1u;
#  endif

    ComM_Nm_NetworkMode( nmChannelHandle );
  }

#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
  if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_CHANNEL_IDX] != NM_COORD_SEL )
  {
#   if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC ) && defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC )
    {
      /* Do nothing */
    }
    else
#   endif
#   if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC ) && defined( NM_DISABLE_MULTIPLE_NM_USAGE )
#   else
    {
      Nm_AbortSleep_BusNm[0] = 1u;
    }
#   endif
  }
#  endif
}
# endif


# if ( NM_BUSNM_CANNM_ENABLED == STD_ON ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || \
  defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
/**********************************************************************************************************************
 * Nm_PrepareBusSleepMode
**********************************************************************************************************************/
/*! \brief      Notification that the CAN network management has entered Prepare Bus Sleep Mode
 *  \context    Function must only be called from task level.
 *  \note       Called by BusNm Main Functions (CanNm, NmFiatB, NmFiatC)
**********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_PrepareBusSleepMode( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )  
#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#    if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
    Nm_NotifyNetworkStart[Nm_SystemToNmChannelInd[nmChannelHandle]] = NM_NOTIFYSTARTPREPSLEEP;
#    else
    Nm_NotifyNetworkStart[nmChannelHandle] = NM_NOTIFYSTARTPREPSLEEP;
#    endif
#   endif
#  endif

  ComM_Nm_PrepareBusSleepMode( nmChannelHandle );
}
# endif

# if ( NM_BUSNM_CANNM_ENABLED == STD_ON ) || ( NM_BUSNM_FRNM_ENABLED == STD_ON ) \
  || defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
/**********************************************************************************************************************
 * Nm_BusSleepMode
**********************************************************************************************************************/
/*! \brief      Notification that the network management has entered Bus Sleep Mode
 *  \context    Function must only be called from task level.
 *  \note       Called by BusNm Main Functions (CanNm, FrNm, NmFiatB, NmFiatC)
**********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_BusSleepMode( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM )
#    endif
  {
    /* Note: It must be ensured that for an ASR-OSEK channel the OSEK is asleep before ASR.
    Otherwise OSEK NM could call CanResetBusSleep(=CanInit()) after the ASR has signalled its sleep.
    The CAN controller would not be wakeable anymore.
    Under normal operating conditions, the OSEK NM is always asleep first.
    In case of limphome, the OSEK-NM might be late. As limphome is a failure state, the coordination
    has not the highest priority. Therefore the OSEK-NM is forced to sleep if not already done. */
    if( NmStateBusSleep(NmGetStatus( nmChannelHandle )) == 0 )
    {
#    if defined ( NM_ENABLE_IF_ASRIFCAN ) && defined ( NM_ENABLE_AUTOSAR_USAGE )
      /* CAN handling is provided by CAN Station Manager */
#    else
      CanChannelHandle osekNmChannel;
#     if defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
      osekNmChannel = NmSystemToNmIndirection[nmChannelHandle];
#     else
      osekNmChannel = nmChannelHandle;
#     endif
#    endif

#    if defined ( NM_ENABLE_IF_ASRIFCAN )
#     if defined ( NM_ENABLE_AUTOSAR_USAGE )
      /* CAN handling is provided by CAN Station Manager */
#     else
#      if defined ( NM_ENABLE_CHANNEL_INDIRECTION )
      (void)CanIf_SetControllerMode( NmNmToCanIndirection[osekNmChannel], CANIF_CS_STOPPED );
      (void)CanIf_SetControllerMode( NmNmToCanIndirection[osekNmChannel], CANIF_CS_STARTED );
      (void)CanIf_SetPduMode( NmNmToCanIndirection[osekNmChannel], CANIF_SET_RX_ONLINE);
#      else
      (void)CanIf_SetControllerMode( osekNmChannel, CANIF_CS_STOPPED );
      (void)CanIf_SetControllerMode( osekNmChannel, CANIF_CS_STARTED );
      (void)CanIf_SetPduMode( osekNmChannel, CANIF_SET_RX_ONLINE);
#      endif
#     endif
#    else
#     if defined ( NM_ENABLE_CHANNEL_INDIRECTION )
      CanResetBusSleep((uint8)NmNmToCanIndirection[osekNmChannel], NmCanPara_Field[osekNmChannel]);
#     else
      CanResetBusSleep((uint8)osekNmChannel, NmCanPara_Field[osekNmChannel]);
#     endif
#    endif

      NmOsekInit(nmChannelHandle, NM_CANSLEEP);
    }
  }

  Nm_NotifyNetworkStart[NM_CHANNEL_IDX] = NM_NOTIFYSTARTSLEEP;
#   endif
#  endif

  ComM_Nm_BusSleepMode( nmChannelHandle );

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_BUSNM_FRNM_ENABLED == STD_ON )
  /* ESCAN00030724 */
  if( ((Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_CHANNEL_IDX] != NM_COORD_SEL)
#    if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
    && (Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_FRNM)
#    endif
    && (Nm_NetCoordState[0] != NM_SLEEP_WAITSLEEP)
#    if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
    && (Nm_DelayTimer[NM_CHANNEL_IDX] != (Nm_TimerCounterType)0u)
#    endif
    )
  {
    ComM_Nm_RestartIndication( nmChannelHandle );
    (void)Nm_NmNetworkRequest( NM_CHANNEL_IDX );
  }
  else
#   endif
  {
    Nm_NetworkStarted[NM_CHANNEL_IDX] = 0u;
#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
    if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_CHANNEL_IDX] != NM_COORD_SEL )
    {
      /* Indicate Sleep for the channel */
      Nm_CoordSleepInd[NM_CHANNEL_IDX] = 1u;
    }
#   endif
  }
#  endif
}
# endif



# if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
/**********************************************************************************************************************
 * Nm_ActiveCoordIndication
**********************************************************************************************************************/
/*! \brief      Notification that a NM message with the Coordinator Bit set was received
 *  \param[in]  nmCoordPrio      Coordination Priority received
 *  \context    Function is called from interrupt or task level.
 *  \note       Called by BusNm Rx Indication (CanNm, FrNm)
**********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_ActiveCoordIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                CONST( uint8, AUTOMATIC ) nmCoordPrio,
                                                CONST( uint8, AUTOMATIC ) nmSleepInd )
{
#  if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
#  endif

  if( ((Nm_CoordPrio < nmCoordPrio) && ((Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_CHANNEL_IDX] == NM_COORD_SYN_ACTIVE))
    || ((Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_CHANNEL_IDX] == NM_COORD_SYN_PASSIVE) )
  {
    if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_CHANNEL_IDX] == NM_COORD_SYN_ACTIVE )
    {
      Nm_CoordActiveInd[NM_CHANNEL_IDX] = 1u;
    }
    Nm_CoordSleepInd[NM_CHANNEL_IDX] = nmSleepInd;
  }
#  if ( NM_DEV_ERROR_DETECT == STD_ON )
  else if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_CHANNEL_IDX] == NM_COORD_SYN_ACTIVE )
  {
    if( Nm_CoordPrio == nmCoordPrio )
    {
      Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_ACTIVECOORDINDICATION_ID, NM_E_PRIORITY_COLLISION );
    }
    if( nmSleepInd != 0x00 )
    {
      Det_ReportError( (uint16)NM_MODULE_ID, NM_INSTANCE_ID, (uint8)NM_ACTIVECOORDINDICATION_ID, NM_E_SLEEPBIT_ERROR );
    }
  }
  else
  {
    /* MISRA compliance */
  }
#  endif
}
# endif


# if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
/**********************************************************************************************************************
 * ApplNmCanNormal
**********************************************************************************************************************/
/*! \brief      Notification that OSEK NM entered 'Network Mode'
 *  \context    Function could be called from interrupt level and from task level
 *  \note       Called by NmOsek Main Function
**********************************************************************************************************************/
FUNC( void, NM_CODE ) ApplNmCanNormal( NM_CHANNEL_APPLTYPE_ONLY )
{
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_ONM_STATE_CHANGE_IND )
#   if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) localChannel = Nm_SystemToNmChannelInd[channel];
#   endif
#  endif


#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
  if( Nm_NotifyNetworkStart[NM_ONM_CHANNEL_IDX] == NM_NOTIFYSTARTSLEEP )
#   endif
#  endif
  {

#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
#    if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#     if defined ( NM_ONM_STATE_CHANGE_IND )
#     else
    Nm_NotifyNetworkStart[NM_ONM_CHANNEL_IDX] = NM_SUPPRESSNOTIFYSTART;
#     endif
#    endif
    Nm_NetworkStarted[NM_ONM_CHANNEL_IDX] = 1u;
#   endif

    ComM_Nm_NetworkMode( (NetworkHandleType)channel );

#   if defined ( NM_ONM_STATE_CHANGE_IND )
    /* Transition from Bus Sleep to Normal Operation/Ready Sleep */ /* ESCAN00043406 */ /* ESCAN00069710 */
    Nm_TriggerOnmStateChangeNotification( NM_ONM_CHANNEL_IDX, Nm_OnmNetworkRequested[NM_ONM_CHANNEL_IDX] );
#   endif
  }

#   if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
  if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_ONM_CHANNEL_IDX] != NM_COORD_SEL )
  {
    Nm_AbortSleep_BusNm[0] = 1u;
  }
#   endif
}

#  if defined ( NM_ENABLE_EXTENDED_CALLBACK )
/**********************************************************************************************************************
 * ApplNmBusStart
**********************************************************************************************************************/
/*! \brief      Notification of OSEK NM Bus Start
 *  \context    Function could be called from interrupt level and from task level
 *  \note       Called by NmOsek Main Function
**********************************************************************************************************************/
FUNC( void, NM_CODE ) ApplNmBusStart( NM_CHANNEL_APPLTYPE_ONLY )
{
  /* empty */
#   if( NM_USE_DUMMY_STATEMENT == STD_ON )
  (void)channel;  /* PRQA S 3112 */ /* MD_NmIf_3112 */
#   endif
}

/**********************************************************************************************************************
 * ApplNmWaitBusSleep
**********************************************************************************************************************/
/*! \brief      Notification that OSEK NM entered 'Prepare Bus Sleep'
 *  \context    Function must only be called from task level.
 *  \note       Called by NmOsek Main Function
**********************************************************************************************************************/
FUNC( void, NM_CODE ) ApplNmWaitBusSleep( NM_CHANNEL_APPLTYPE_ONLY )
{
#   if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#    if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) || defined ( NM_ONM_STATE_CHANGE_IND )
#     if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) localChannel = Nm_SystemToNmChannelInd[channel];
#     endif
#    endif

#    if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
  if( Nm_LChannelConfiguration[NM_ONM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#    endif
  {
    ComM_Nm_PrepareBusSleepMode( (NetworkHandleType)channel );

#   if defined ( NM_ONM_STATE_CHANGE_IND )
    /* ESCAN00069710 */
    Nm_TriggerOnmStateChangeNotification( NM_ONM_CHANNEL_IDX, NM_STATE_PREPARE_BUS_SLEEP );
#   endif
  }
#   else
  /* Note: do not execute callback on mixed networks in a channel: CanNm already executes this callback */
#    if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  (void)channel;  /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif
#   endif
}

/**********************************************************************************************************************
 * ApplNmWaitBusSleepCancel
**********************************************************************************************************************/
/*! \brief      Notification that OSEK NM restarted from 'Prepare Bus Sleep'
 *  \context    Function must only be called from task level.
 *  \note       Called by NmOsek Main Function
**********************************************************************************************************************/
FUNC( void, NM_CODE ) ApplNmWaitBusSleepCancel( NM_CHANNEL_APPLTYPE_ONLY )
{
#   if ( defined ( NM_ENABLE_CHANNELTYPE_OSEKNM ) && \
         ( defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) || defined ( NM_ONM_STATE_CHANGE_IND ) ) ) || \
       ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) 
#    if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) localChannel = Nm_SystemToNmChannelInd[channel];
#    endif
#   endif

#   if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#    if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
  if( Nm_LChannelConfiguration[NM_ONM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#    endif
  {
    ComM_Nm_NetworkMode( (NetworkHandleType)channel );

#    if defined ( NM_ONM_STATE_CHANGE_IND )
    /* ESCAN00043406 */ /* ESCAN00069710 */
    Nm_TriggerOnmStateChangeNotification( NM_ONM_CHANNEL_IDX, Nm_OnmNetworkRequested[NM_ONM_CHANNEL_IDX] );
#    endif
  }
#   else
  /* Note: do not execute callback on mixed networks in a channel: CanNm already executes this callback */
#   endif

#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_ONM_CHANNEL_IDX] != NM_COORD_SEL )
  {
    Nm_AbortSleep_BusNm[0] = 1u;
  }
#   else
#   endif

}
#  endif

/**********************************************************************************************************************
 * ApplNmCanBusSleep
**********************************************************************************************************************/
/*! \brief      Notification that OSEK NM entered 'Bus Sleep'
 *  \context    Function must only be called from task level.
 *  \note       Called by NmOsek Main Function
**********************************************************************************************************************/
FUNC( void, NM_CODE ) ApplNmCanBusSleep( NM_CHANNEL_APPLTYPE_ONLY )
{
  /* empty */
#   if( NM_USE_DUMMY_STATEMENT == STD_ON )
  (void)channel;  /* PRQA S 3112 */ /* MD_NmIf_3112 */
#   endif
}

/**********************************************************************************************************************
 * ApplNmCanSleep
**********************************************************************************************************************/
/*! \brief      Notification that OSEK NM entered 'Bus Sleep'
 *  \context    Function must only be called from task level.
 *  \note       Called by NmOsek Main Function
**********************************************************************************************************************/
FUNC( void, NM_CODE ) ApplNmCanSleep( NM_CHANNEL_APPLTYPE_ONLY )
{
#  if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM ) || defined ( NM_ONM_STATE_CHANGE_IND )
#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || \
       defined ( NM_ONM_STATE_CHANGE_IND )
#    if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) localChannel = Nm_SystemToNmChannelInd[channel];
#    endif
#   endif
#  endif

#  if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM )
#   if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
  if( Nm_LChannelConfiguration[NM_ONM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_OSEKNM )
#   endif
  {

#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#    if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
    Nm_NotifyNetworkStart[NM_ONM_CHANNEL_IDX] = NM_NOTIFYSTARTSLEEP;
#    endif
    Nm_NetworkStarted[NM_ONM_CHANNEL_IDX] = 0u;

#    if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
    if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_ONM_CHANNEL_IDX] != NM_COORD_SEL )
    {
      /* Indicate Sleep for the channel */
      Nm_CoordSleepInd[NM_ONM_CHANNEL_IDX] = 1u;
    }
#    endif
#   endif

    ComM_Nm_BusSleepMode( (NetworkHandleType)channel );

#   if defined ( NM_ONM_STATE_CHANGE_IND )
    /* ESCAN00069710 */
    Nm_TriggerOnmStateChangeNotification( NM_ONM_CHANNEL_IDX, NM_STATE_BUS_SLEEP );
#   endif
  }
#  else
  /* Note: do not execute functionality on mixed networks in a channel: CanNm already executes the functionality */
#   if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  (void)channel;  /* PRQA S 3112 */ /* MD_NmIf_3112 */
#   endif
#  endif
}


#  if defined( NM_ENABLE_BUSOFF_NOTIFICATION )
/* ESCAN00069710 */
/**********************************************************************************************************************
 * ApplNmBusOff
**********************************************************************************************************************/
/*! \brief      Notification that OSEK NM was notified about BusOff state
 *  \context    Function must only be called from task level.
 *  \note       Called by NmOsek Main Function
**********************************************************************************************************************/
FUNC( void, NM_CODE ) ApplNmBusOff( NM_CHANNEL_APPLTYPE_ONLY )
{
#   if defined ( NM_ONM_STATE_CHANGE_IND )
#    if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) localChannel = Nm_SystemToNmChannelInd[channel];
#    endif
  if ( ( Nm_OnmState[NM_ONM_CHANNEL_IDX] == NM_STATE_NORMAL_OPERATION ) ||
       ( Nm_OnmState[NM_ONM_CHANNEL_IDX] == NM_STATE_READY_SLEEP ) )
  {
    Nm_TriggerOnmStateChangeNotification( NM_ONM_CHANNEL_IDX, NM_STATE_BUS_OFF );
  }
#   else
#    if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  (void)channel;  /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif
#   endif
}

/* ESCAN00069710 */
/**********************************************************************************************************************
 * ApplNmBusOffEnd
**********************************************************************************************************************/
/*! \brief      Notification that OSEK NM was notified about BusOff Recovery end state
 *  \context    Function must only be called from task level.
 *  \note       Called by NmOsek Main Function
**********************************************************************************************************************/
FUNC( void, NM_CODE ) ApplNmBusOffEnd( NM_CHANNEL_APPLTYPE_ONLY )
{
#   if defined ( NM_ONM_STATE_CHANGE_IND )
  /* ESCAN00069710 */
#    if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) localChannel = Nm_SystemToNmChannelInd[channel];
#    endif
  if ( Nm_OnmState[NM_ONM_CHANNEL_IDX] == NM_STATE_BUS_OFF )
  {
    Nm_TriggerOnmStateChangeNotification( NM_ONM_CHANNEL_IDX, Nm_OnmNetworkRequested[NM_ONM_CHANNEL_IDX] );
  }
#   else
#    if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  (void)channel;  /* PRQA S 3112 */ /* MD_NmIf_3112 */
#    endif
#   endif
}
#  endif


# endif /* NM_OSEK_SUPPORT_ENABLED == STD_ON */

#define NM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* else defined ( NM_MACRO_LAYER_OPT_ENABLED ) */


/*******************************************************************************
  Verify the configuration of the Network Management Interface
*******************************************************************************/

/* Check standard define switches */
#if defined ( STD_OFF ) && defined ( STD_ON ) && ( STD_ON != STD_OFF )
#else
# error: "Configuration issue: STD_ON and STD_OFF have to be defined to a different value!"
#endif

/* Check Error Detection / Diagnostic switches */
#if ( defined NM_DEV_ERROR_DETECT ) \
    && ( ( NM_DEV_ERROR_DETECT == STD_OFF ) || ( NM_DEV_ERROR_DETECT == STD_ON ) )
#else
# error: "Nm configuration issue: Development Error Detection has to be defined STD_OFF or STD_ON."
#endif

/* Check Bus Configuration switches */
#if ( defined NM_BUSNM_CANNM_ENABLED ) \
    && ( ( NM_BUSNM_CANNM_ENABLED == STD_OFF ) || ( NM_BUSNM_CANNM_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: CAN Bus Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined NM_BUSNM_FRNM_ENABLED ) \
    && ( ( NM_BUSNM_FRNM_ENABLED == STD_OFF ) || ( NM_BUSNM_FRNM_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: FlexRay Bus Enabled has to be defined STD_OFF or STD_ON."
#endif

/* Check Nm Interface Configuration switches */
#if ( defined NM_VERSION_INFO_API ) \
    && ( ( NM_VERSION_INFO_API == STD_OFF ) || ( NM_VERSION_INFO_API == STD_ON ) )
#else
# error: "Nm configuration issue: Version Info Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined NM_NODE_DETECTION_ENABLED ) \
    && ( ( NM_NODE_DETECTION_ENABLED == STD_OFF ) || ( NM_NODE_DETECTION_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: Node Detection Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined NM_REMOTE_SLEEP_IND_ENABLED ) \
    && ( ( NM_REMOTE_SLEEP_IND_ENABLED == STD_OFF ) || ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: Remote Sleep Indication Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined NM_USER_DATA_ENABLED ) \
    && ( ( NM_USER_DATA_ENABLED == STD_OFF ) || ( NM_USER_DATA_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: User Data Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined NM_BUS_SYNCHRONIZATION_ENABLED ) \
    && ( ( NM_BUS_SYNCHRONIZATION_ENABLED == STD_OFF ) || ( NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: Bus Synchronization Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined NM_PASSIVE_MODE_ENABLED ) \
  && ( ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) || ( NM_PASSIVE_MODE_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: Passive Mode Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined NM_NODE_ID_ENABLED ) \
    && ( ( NM_NODE_ID_ENABLED == STD_OFF ) || ( NM_NODE_ID_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: Node Identifier Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined NM_PDU_RX_INDICATION_ENABLED ) \
    && ( ( NM_PDU_RX_INDICATION_ENABLED == STD_OFF ) || ( NM_PDU_RX_INDICATION_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: Pdu Rx Indication Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined NM_STATE_CHANGE_IND_ENABLED ) \
    && ( ( NM_STATE_CHANGE_IND_ENABLED == STD_OFF ) || ( NM_STATE_CHANGE_IND_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: State Change Indication Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined NM_COM_CONTROL_ENABLED ) \
    && ( ( NM_COM_CONTROL_ENABLED == STD_OFF ) || ( NM_COM_CONTROL_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: Communication Control Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined ( NM_CRC_CHECK ) \
    && ( ( NM_CRC_CHECK == STD_OFF ) || ( NM_CRC_CHECK == STD_ON ) ) )
#else
# error: "Nm configuration issue: CRC Check has to be defined STD_OFF or STD_ON."
#endif
#if ( defined ( NM_USE_DUMMY_STATEMENT ) \
    && ( ( NM_USE_DUMMY_STATEMENT == STD_OFF ) || ( NM_USE_DUMMY_STATEMENT == STD_ON ) ) )
#else
# error: "Nm configuration issue: Use Dummy Statement has to be defined STD_OFF or STD_ON."
#endif
#if ( defined ( NM_COM_USER_DATA_ENABLED ) \
  && ( ( NM_COM_USER_DATA_ENABLED == STD_OFF ) || ( NM_COM_USER_DATA_ENABLED == STD_ON ) ) )
#else
# error: "Nm configuration issue: Com User Data Support has to be defined STD_OFF or STD_ON."
#endif
#if ( defined ( NM_CAR_WAKE_UP_RX_ENABLED ) \
  && ( ( NM_CAR_WAKE_UP_RX_ENABLED == STD_OFF ) || ( NM_CAR_WAKE_UP_RX_ENABLED == STD_ON ) ) )
#else
# error: "Nm configuration issue: Car WakeUp Rx Enabled has to be defined STD_OFF or STD_ON."
#endif

/* Check additional coordinator switches */
#if ( defined NM_COORDINATOR_SUPPORT_ENABLED ) \
    && ( ( NM_COORDINATOR_SUPPORT_ENABLED == STD_OFF ) || ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: Coordinator Support Enabled has to be defined STD_OFF or STD_ON."
#endif
#if ( defined NM_OSEK_SUPPORT_ENABLED ) \
    && ( ( NM_OSEK_SUPPORT_ENABLED == STD_OFF ) || ( NM_OSEK_SUPPORT_ENABLED == STD_ON ) )
#else
# error: "Nm configuration issue: OSEK Support Enabled has to be defined STD_OFF or STD_ON."
#endif

/* Check configuration of Passive Mode */
#if ( NM_PASSIVE_MODE_ENABLED == STD_ON )
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#  error: "Nm configuration issue: NM_COORDINATOR_SUPPORT_ENABLED should not be used with NM_PASSIVE_MODE_ENABLED."
# endif
# if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
#  error: "Nm configuration issue: NM_OSEK_SUPPORT_ENABLED should not be used with NM_PASSIVE_MODE_ENABLED."
# endif
#endif

#if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
/* Check configuration of Node Detection */
# if ( NM_NODE_DETECTION_ENABLED == STD_ON ) && ( NM_NODE_ID_ENABLED == STD_OFF )
# error: "Nm configuration issue: NM_NODE_DETECTION_ENABLED cannot be STD_ON if NM_NODE_ID_ENABLED is STD_OFF."
# endif
#endif

/* Check the configuration of Macro Layer Optimization */
#if ( defined NM_MACRO_LAYER_OPT_ENABLED )
# if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
#  error: "Nm configuration issue: Macro Layer Optimization is not possible when multiple NMs are active!"
# endif
# if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
#  error: "Nm configuration issue: Macro Layer Optimization is not possible when OSEK NM Support is enabled!"
# endif
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#  error: "Nm configuration issue: Macro Layer Optimization is not possible when Coordinator Support is enabled!"
# endif
#endif

/* Check coordinator configuration */
#if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
# if ( NM_NUMBER_OF_NM_CHANNELS == 1 )
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
/* Note: it is possible to use the coordinator on one channel, if two NM run on the same channel */
#  else
#   error "Nm configuration issue: Coordinator functionality makes no sense for one NM channel."
#  endif
# endif
# if ( NM_BUS_SYNCHRONIZATION_ENABLED == STD_OFF )
#  error: "Nm configuration issue: Bus Synchronization has to be enabled when Coordinator Support is enabled!"
# endif
# if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_OFF )
#  error "Nm configuration issue: Remote Sleep Indication is required for Coordinator functionality."
# endif
# if defined ( NM_ENABLE_COORD_SYNC_SUPPORT ) && defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#  error: "Nm configuration issue: NM Coordinator Synchronization Support cannot be enabled together with multiple NM Usage one one channel"
# endif
/* ESCAN00057459 */
# if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) && ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
/* ESCAN00043702 */
#  if defined ( NM_ONM_STATE_CHANGE_IND )
#  else
#   error: "Nm configuration issue: State Change Ind OSEK NM has to be enabled when OSEK NM and CAN NM are used on the same channel and State Change Ind is enabled!"
#  endif
# endif
#else
# if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
#  error: "Nm configuration issue: NM Coordinator Synchronization Support cannot be enabled without NM Coordinator Support"
# endif

/* Check NM GW configuration */

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
# else
#   if ( NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
#    error: "Nm configuration issue: Bus Synchronization has to be disabled when Coordinator Support and Gateway Handling are disabled!"
#   endif
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#   error: "Nm configuration issue: Usage of CAN NM and OSEK NM on the same channel is not possible without Coordination or Gateway Functionality!"
#  endif
# endif
#endif

/* Check NM / Diagnostic GW configuration */

/* Check configuration with OSEK Support */
#if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
# if defined ( NM_ENABLE_CHANNELTYPE_OSEKNM ) && defined ( NM_DISABLE_MULTIPLE_NM_USAGE )
#  if ( NM_USER_DATA_ENABLED == STD_ON )
#   error: "Nm configuration issue: User Data Support cannot be enabled if only OSEK NM channels are available!"
#  endif
#  if ( NM_NODE_ID_ENABLED == STD_ON )
#   error: "Nm configuration issue: Node Identifier cannot be enabled if only OSEK NM channels are available!"
#  endif
#  if ( NM_NODE_DETECTION_ENABLED == STD_ON )
#   error: "Nm configuration issue: Node Detection cannot be enabled if only OSEK NM channels are available!"
#  endif
/* ESCAN00057459 */
# endif
# if defined ( NM_ONM_STATE_CHANGE_IND ) && ( NM_STATE_CHANGE_IND_ENABLED == STD_OFF )
#  error: "Nm configuration issue: State Change Ind OSEK NM cannot be enabled when State Change Ind is disabled!"
# endif
#endif


/* Check number of channels */
#if ( NM_NUMBER_OF_NM_CHANNELS == 0 )
# error: "Nm configuration issue: No NM channel available!"
#endif

#if defined V_EXTENDED_BUILD_LIB_CHECK
/* Provide library checks */
# if defined ( NM_CFG_VAR_POST_COMP_ENABLED )
# else
#  error: "Nm configuration issue: NM Configuration Variant must not be Pre-Compile (1) when building libraries."
# endif
#endif

/*******************************************************************************
  Verify the configuration consistency between NM Interface and <Bus>Nm
 *******************************************************************************/

/* Check availability of a valid Bus NM */
#if ( NM_BUSNM_CANNM_ENABLED == NM_BUSNM_FRNM_ENABLED ) && ( NM_BUSNM_CANNM_ENABLED == STD_OFF )
# if ( NM_OSEK_SUPPORT_ENABLED == STD_OFF )
#  if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB ) || defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#  else
#   error: "Nm configuration issue: At least one of the following BusNms has to be active: CanNm, FrNm, NmOsek, NmFiatB, NmFiatC!"
#  endif
# endif
#endif

#if ( NM_BUSNM_CANNM_ENABLED == STD_OFF )
# define CANNM_NUMBER_OF_CANNM_CHANNELS 0
#endif

#if ( NM_BUSNM_FRNM_ENABLED == STD_OFF )
# define FRNM_NUMBER_OF_FRNM_CHANNELS 0
#endif

#if ( NM_OSEK_SUPPORT_ENABLED == STD_OFF )
# define kNmNumberOfChannels 0
#endif

#if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#else
# define NMFIATB_NUMBER_OF_NMFIATB_CHANNELS 0
#endif

#if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#else
# define NMFIATC_NUMBER_OF_NMFIATC_CHANNELS 0
#endif

#if ( FRNM_NUMBER_OF_FRNM_CHANNELS + CANNM_NUMBER_OF_CANNM_CHANNELS + kNmNumberOfChannels + \
  NMFIATB_NUMBER_OF_NMFIATB_CHANNELS + NMFIATC_NUMBER_OF_NMFIATC_CHANNELS != NM_NUMBER_OF_NM_CHANNELS )
# if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
/* Note: This check is not valid if 2 NM run on the same channel */
# else
#  error: "Nm configuration issue: Number of NM channels does not match with the summarized number of allowed bus-specific Nms (CanNm, FrNm, NmOsek, NmFiatB, NmFiatC)."
# endif
#endif

/* Check configuration switches Interface - CAN */
#if ( NM_BUSNM_CANNM_ENABLED == STD_ON )
# if ( NM_NODE_DETECTION_ENABLED != CANNM_NODE_DETECTION_ENABLED )
#  error "NM configuration issue: Node Detection settings between Nm Interface and CAN Nm are inconsistent."
# endif
# if ( NM_REMOTE_SLEEP_IND_ENABLED != CANNM_REMOTE_SLEEP_IND_ENABLED )
#  error "NM configuration issue: Remote Sleep Indication settings between Nm Interface and CAN Nm are inconsistent."
# endif
# if ( NM_USER_DATA_ENABLED != CANNM_USER_DATA_ENABLED )
#  error "NM configuration issue: User Data settings between Nm Interface and CAN Nm are inconsistent."
# endif
# if ( NM_BUS_SYNCHRONIZATION_ENABLED != CANNM_BUS_SYNCHRONIZATION_ENABLED )
#  error "NM configuration issue: Bus Synchronization settings between Nm Interface and CAN Nm are inconsistent."
# endif
# if ( NM_PASSIVE_MODE_ENABLED != CANNM_PASSIVE_MODE_ENABLED )
#  error "NM configuration issue: Passive Mode settings between Nm Interface and CAN Nm are inconsistent."
# endif
# if ( NM_NODE_ID_ENABLED != CANNM_NODE_ID_ENABLED )
#  error "NM configuration issue: Node Identifier settings between Nm Interface and CAN Nm are inconsistent."
# endif
# if ( NM_PDU_RX_INDICATION_ENABLED != CANNM_PDU_RX_INDICATION_ENABLED )
#  error "NM configuration issue: Pdu Rx Indication settings between Nm Interface and CAN Nm are inconsistent."
# endif
# if ( NM_STATE_CHANGE_IND_ENABLED != CANNM_STATE_CHANGE_IND_ENABLED )
#  error "NM configuration issue: State Change Indication settings between Nm Interface and CAN Nm are inconsistent."
# endif
# if ( NM_COM_CONTROL_ENABLED != CANNM_COM_CONTROL_ENABLED )
#  error "NM configuration issue: Communication Control settings between Nm Interface and CAN Nm are inconsistent."
# endif
# if ( NM_COM_USER_DATA_ENABLED != CANNM_COM_USER_DATA_ENABLED )
#  error: "NM configuration issue: Com User Data Support settings between Nm Interface and CAN Nm are inconsistent."
# endif
# if ( CANNM_CONFIG_VARIANT == 1u )
/* In CanNm pre-compile configurations, CANNM_CAR_WUP_RX_FEATURE_ENABLED may be STD_OFF for optimization reasons
 * if the feature is not active on any channel
 */
#  if ( NM_CAR_WAKE_UP_RX_ENABLED == STD_OFF ) && ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
#   error: "NM configuration issue: Car WakeUp Rx Feature Enabled settings between Nm Interface and CAN Nm are inconsistent."
#  endif
# else
#  if ( NM_CAR_WAKE_UP_RX_ENABLED != CANNM_CAR_WUP_RX_FEATURE_ENABLED )
#   error: "NM configuration issue: Car WakeUp Rx Feature Enabled settings between Nm Interface and CAN Nm are inconsistent."
#  endif
# endif
#else
#endif

/* Check configuration switches Interface - FlexRay */
#if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
# if ( NM_NODE_DETECTION_ENABLED != FRNM_NODE_DETECTION_ENABLED )
#  error "NM configuration issue: Node Detection settings between Nm Interface and FlexRay Nm are inconsistent."
# endif
# if ( NM_REMOTE_SLEEP_IND_ENABLED != FRNM_REMOTE_SLEEP_INDICATION_ENABLED )
#  error "NM configuration issue: Remote Sleep Indication settings between Nm Interface and FlexRay Nm are inconsistent."
# endif
# if ( NM_USER_DATA_ENABLED != FRNM_USER_DATA_ENABLED )
#  error "NM configuration issue: User Data settings between Nm Interface and FlexRay Nm are inconsistent."
# endif
# if ( NM_BUS_SYNCHRONIZATION_ENABLED != FRNM_BUS_SYNCHRONIZATION_ENABLED )
#  error "NM configuration issue: Bus Synchronization settings between Nm Interface and FlexRay Nm are inconsistent."
# endif
# if ( NM_PASSIVE_MODE_ENABLED != FRNM_PASSIVE_MODE_ENABLED )
#  error "NM configuration issue: Passive Mode settings between Nm Interface and FlexRay Nm are inconsistent."
# endif
# if ( NM_NODE_ID_ENABLED != FRNM_SOURCE_NODE_IDENTIFIER_ENABLED )
#  error "NM configuration issue: Node Identifier settings between Nm Interface and FlexRay Nm are inconsistent."
# endif
# if ( NM_PDU_RX_INDICATION_ENABLED != FRNM_PDU_RX_INDICATION_ENABLED )
#  error "NM configuration issue: Pdu Rx Indication settings between Nm Interface and FlexRay Nm are inconsistent."
# endif
# if ( NM_STATE_CHANGE_IND_ENABLED != FRNM_STATE_CHANGE_INDICATION_ENABLED )
#  error "NM configuration issue: State Change Indication settings between Nm Interface and FlexRay Nm are inconsistent."
# endif
# if ( NM_COM_USER_DATA_ENABLED != FRNM_COM_USER_DATA_ENABLED )
#  error: "NM configuration issue: Com User Data Support settings between Nm Interface and FlexRay Nm are inconsistent."
# endif
/* In FrNm pre-compile configurations, FRNM_CAR_WUP_RX_FEATURE_ENABLED may be STD_OFF for optimization reasons
 * if the feature is not active on any channel
 */
# if ( FRNM_CONFIG_VARIANT == 1u )
#  if ( NM_CAR_WAKE_UP_RX_ENABLED == STD_OFF ) && ( FRNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
#   error: "NM configuration issue: Car WakeUp Rx Feature Enabled settings between Nm Interface and FlexRay Nm are inconsistent."
#  endif
# else
#  if ( NM_CAR_WAKE_UP_RX_ENABLED != FRNM_CAR_WUP_RX_FEATURE_ENABLED  )
#   error: "NM configuration issue: Car WakeUp Rx Feature Enabled settings between Nm Interface and FlexRay Nm are inconsistent."
#  endif
# endif
#endif

/* check OSEK configuration */
#if ( NM_OSEK_SUPPORT_ENABLED == STD_ON)
# if defined ( NM_ENABLE_EXTENDED_CALLBACK )
# else
/* needed for callbacks to ComM (ESCAN00036310) */
#  error "Nm configuration issue: This component needs the Extended Callback feature of OSEK NM."
# endif
#  if defined ( NM_ENABLE_INDEXED_NM )
#  else
#   error "Nm configuration issue: This component needs indexed components of OSEK NM."
#  endif
#endif

/* Check coordinator configuration */
#if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
# if ( NM_BUSNM_CANNM_ENABLED == STD_ON )
#  if defined ( CANNM_REMOTE_SLEEP_EXTENSION )
#  else
#   error "Nm configuration issue: CanNm Extended Remote Sleep Indication is required for Coordinator functionality."
#  endif
# endif
# if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
#  if defined ( FRNM_REMOTE_SLEEP_EXTENSION )
#  else
#   error "Nm configuration issue: FlexRay Extended Remote Sleep Indication is required for Coordinator functionality."
#  endif
# endif
/* check OSEK configuration */
# if ( NM_OSEK_SUPPORT_ENABLED == STD_ON)
#  if defined ( NM_ENABLE_REMOTESLEEP_INDICATION )
#  else
/* needed to detect sleep readiness */
#   error "Nm configuration issue: This component needs remote sleep indication feature of OSEK NM."
#  endif
#  if defined ( NM_ENABLE_CONFIG )
#  else
/* needed to determine number of nodes in logical ring */
#   error "Nm configuration issue: This component needs the node monitoring feature of OSEK NM."
#  endif
#  if defined ( NM_ENABLE_TOKEN_ACCESS )
#  else
/* needed for Coordination algorithm */
#   error "Nm configuration issue: This component needs the feature NM_ENABLE_TOKEN_ACCESS."
#  endif
# endif
/* ESCAN00064216 */
# if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
#  if ( NM_BUSNM_CANNM_ENABLED == STD_ON )
#   if defined ( CANNM_ENABLE_COORD_SYNC_SUPPORT )
#   else
#    error: "Nm configuration issue: CAN NM Synchronization Coordination Support is required for Coordination with CAN"
#   endif
#  endif
#  if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
#   if defined ( FRNM_ENABLE_COORD_SYNC_SUPPORT )
#   else
#    error: "Nm configuration issue: FlexRay NM Synchronization Coordination Support is required for Coordination FlexRay"
#   endif
#  endif
#  if ( NM_BUSNM_CANNM_ENABLED == STD_OFF ) && ( NM_BUSNM_FRNM_ENABLED == STD_OFF )
#   error: "Nm configuration issue: At least one AUTOSAR NM (CAN NM or FlexRay NM) is required for the usage of NM Extended Coordination Support"
#  endif
# endif
#endif



/*******************************************************************************
  Incompatibility check to CCL
 *******************************************************************************/
/* ESCAN00069710 */
# if defined ( VGEN_ENABLE_CCL )
#  if defined ( NM_ONM_STATE_CHANGE_IND )
#   error "CCL cannot be used with this Nm_AsrNmIf version."
#  endif
# endif

/*******************************************************************************
* ORGANI check
*******************************************************************************/


/* module specific MISRA deviations:
 MD_NmIf_0342:
      Reason:     Glue operator necessary for code optimizations.
      Risk:       K&R Compilers do not support the glue operator.
      Prevention: Do not use K&R Compilers.
 MD_NmIf_3112:
      Reason:     Dummy statement to avoid compiler warnings.
      Risk:       There is no risk as such statements have no effect on the code.
      Prevention: Covered by code review.
 MD_NmIf_3689:
      Reason:     Missing run-time check for valid array index access due to performance reasons.
      Risk:       Wrong memory access may result in arbitrary behavior.
      Prevention: Covered by code review.
 MD_NmIf_5124:
      Reason:     The include is for debug purpose only and will be filtered for delivery.
      Risk:       There is no risk as this warning occurs only if singlesource files are used.
      Prevention: Do not use singlesource files for delivery.
*/

/**********************************************************************************************************************
 *  END OF FILE: Nm.c
 *********************************************************************************************************************/
