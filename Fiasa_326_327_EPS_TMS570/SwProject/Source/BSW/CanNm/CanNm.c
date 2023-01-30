
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
 *         File:  CanNm.c
 *    Component:  AUTOSAR CAN Network Management
 *       Module:  AUTOSAR Network Management
 *    Generator:  -
 *
 *  Description:  Source of AUTOSAR CAN Network Management
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
 *  4.02.00   2008-02-27  visoh   ESCAN00024920 Fixed Bus Load Reduction issue
 *  4.02.01   2008-03-03  visoh                 Pre-processor corrections for passive nodes
 *  4.03.00   2008-03-04  visoh   ESCAN00025032 Corrected NM message layout configuration parameter to be channel-specific
 *                                ESCAN00025037 Link-time configuration variant support for the number of channels
 *                                ESCAN00025390 Extended Coordinator Synchronization Support
 *                                              Adapted MemMap Sections / Compiler Abstraction Macros
 *  4.03.01   2008-03-30  visoh   ESCAN00025661 Corrected Compiler Abstraction Macros and Repeat Message Indication flag handling
 *                                              Adapted Extended Coordinator Synchronization Support
 *  4.03.02   2008-04-09  visoh   ESCAN00025932 Changed DEM handling
 *  4.04.00   2008-04-21  visoh   ESCAN00025479 Corrected CAN BusOff Support Handling
 *                                ESCAN00026254 Adapted include naming
 *  4.04.01   2008-04-23  visoh   ESCAN00026225 MSR 3.0 Version check added
 *                                ESCAN00026661 Generator Version check added
 *  4.05.00   2008-07-07  visoh   ESCAN00027898 Changed Instance ID reported to DET
 *                                ESCAN00028002 Corrected cast problems
 *  4.06.00   2008-09-23  visoh   ESCAN00030005 Added PreCompile and Linktime Crc Check
 *                                ESCAN00030159 Removed main function definition
 *  4.06.01   2008-11-04  visoh   ESCAN00031053 Corrected configuration handling for link-time compatibility
 *  4.07.00   2008-11-25  visoh   ESCAN00031593 Adapted Coordinator Extension Support
 *                                              Compiler Abstraction corrections
 *                                ESCAN00031361 Corrected include error
 *                                ESCAN00031641 Corrected compiler abstraction issue (fixed implicitly with ESCAN00031593)
 *  4.07.01   2009-01-28  visoh   ESCAN00032597 Corrected Communication Control behavior
 *                                ESCAN00033741 Optimized Bus Load Reduction handling; MISRA compliance
 *                                ESCAN00034046 Corrected compiler warning
 *  4.08.00   2009-06-18  visoh   ESCAN00033694 Multiple ECU Support
 *                                ESCAN00034522 Corrected Startup Behavior
 *                                ESCAN00034832 No changes in this file
 *                                ESCAN00035503 Improvements to avoid MISRA warnings
 *  4.09.00   2009-07-21  visoh   ESCAN00036115 Added pre-compile checks for library build
 *                                ESCAN00036567 Corrected potential data inconsistency
 *  4.09.01   2009-09-17  visoh   ESCAN00037225 Corrected message transmission handling
 *  4.10.00   2009-10-07  visoh   ESCAN00037081 Corrected Restart Behavior
 *                                ESCAN00037848 Added NM User Data Support via Com
 *                                ESCAN00039378 Corrected initialization of Tx data buffer
 *  4.10.01   2010-03-03  visoh   ESCAN00039571 Adapted casts for usage with Cosmic compiler and strict option
 *  4.11.00   2010-03-25  visoh   ESCAN00041660 Corrected compiler error with CanNm_UserDataPosition
 *                                ESCAN00041849 Added QNX Support; optimized access to post-build data
 *  4.12.00   2010-04-28  visoh   ESCAN00042327 Removed superfluous QNX item
 *                                ESCAN00042562 Added Feature 'Extended Bus Synchronization'
 *  4.13.00   2010-06-16  visoh   ESCAN00043403 Added API to check limp home status
 *  4.14.00   2010-07-07  visoh   ESCAN00043418 Corrected compiler error with CanNm_TxMessageData
 *                                ESCAN00043887 Added Support for NM Gateway
 *  4.15.00   2010-08-19  visoh   ESCAN00044753 Added CanNm_Transmit due to changed handling in PduR
 *                                ESCAN00044896 Adapted pointer casts to correct compiler abstraction
 *  4.16.00   2010-08-20  visdhf  ESCAN00043787 Added Support for Active Wake Up Bit
 *                                ESCAN00043772 Added Support for Car Wake Up
 *                                ESCAN00043794 Added Support for Partial Networking
 *                                ESCAN00043785 Added Support for Fast Wake Up
 *  4.17.00   2010-10-04  visoh   ESCAN00045764 Changed some DEM errors to DET
 *                                ESCAN00045879 Reworked Partial Networking
 *                                ESCAN00046097 Added Support for PduInfoType in APIs
 *                                ESCAN00046267 Adapted AUTOSAR version check
 *                                ESCAN00046915 Reworked Fast Wake Up (now Immediate Transmission)
 *                                ESCAN00047248 Corrected API handling for CanNm_Transmit
 *                                ESCAN00047362 Added critical sections for interrupt lock optimization
 *                                ESCAN00047497 Adapted main function to support multiple configuration use case
 *                                ESCAN00048323 Corrected Partial Networking initialization
 *                                ESCAN00048706 Corrected compile error due to missing declarations
 *                                ESCAN00048707 Corrected immediate transmission handling
 *  4.17.01   2011-04-28  vismdr  ESCAN00050304 Critical section is also left in CanNm_SetCoordBits
 *                                ESCAN00050423 Corrected syntax error related to Single Channel Optimization
 *                                ESCAN00050470 Corrected CANNM_E_CANIF_TRANSMIT_ERROR reporting
 *  4.17.02   2011-05-23  vismdr  ESCAN00051043 Re-added DEM errors and made them configurable
 *  4.18.00   2011-05-31  vismdr  ESCAN00048297 Added call of CanSM_TxTimeoutException for Tx Timeout handling
 *                                ESCAN00050076 No changes in this file
 *                                ESCAN00050080 No changes in this file
 *                                ESCAN00050282 Added CanNm_ConfirmPnAvailability definition
 *                                ESCAN00051150 Removed Support for non-PduInfoType APIs
 *                                ESCAN00051411 Adapted return value usage of PduR_CanNmTriggerTransmit
 *                                ESCAN00051654 Removed version check for CanIf
 *                                ESCAN00051912 CanNm_PassiveStartUp: restart possible in Prepare Bus Sleep Mode
 *  4.19.00   2011-10-05  vismdr  ESCAN00052254 Encapsulated pre-processor feature switches more explicitly
 *                                ESCAN00053229 Removed ORGANI checks for C_COMP_ and C_CLIENT_
 *                                ESCAN00053565 No changes in this file
 *                                ESCAN00053603 Only using SchM as critical section handler
 *                                ESCAN00054369 Adapted Message Timeout Timer handling
 *                                ESCAN00054839 Added support for RX PDUs with different lengths
 *  4.19.01   2012-03-21  vismdr  ESCAN00056701 PN messages are processed properly by CanNm_RxIndication
 *                                ESCAN00057728 Immediate Msg TX requires CanNm_TriggerTransmission to return NM_E_OK
 *                                ESCAN00057816 EIRA and ERA calculation is processed if PN availability is unconfirmed
 *  4.20.00   2012-06-12  vismdr  ESCAN00059355 Encapsulated pre-processor Com Control Enabled more explicitly
 *  4.21.00   2012-08-23  vismdr  ESCAN00059456 Msg Timeout Timer is not stopped if Tx is disabled
 *                                ESCAN00060200 Post-build ability of CANNM_MSG_REDUCED_TIME, CANNM_MSG_CYCLE_OFFSET
 *  4.22.00   2013-04-10  vismdr  ESCAN00063982 CanNm_DisableCommunication prevents TX NM PDU after CanNm_Transmit call
 *                                ESCAN00064042 Adapted CanNm_PbChConfigPtr declaration and initialization
 *                                ESCAN00064221 Adapted condition for Nm_CarWakeUpIndication
 *                                ESCAN00064767 Adapted condition for sending NM message due to Immediate Restart
 *                                ESCAN00064796 NM Msg Tx due to Immediate Restart after State Change Notification
 *                                ESCAN00066109 Added run-time measurement support
 *                                ESCAN00066499 Added function definition of CanNm_DisablePNActivationState
 *                                ESCAN00067173 Resetting CRI Bit in CanNm_DisablePNActivationState
 *  4.22.01   2013-07-15  vismdr  ESCAN00068528 Adapted initialization check in CanNm_DisablePNActivationState
 *  4.22.02   2013-09-30  vismdr  ESCAN00069312 Fixed usage of CanNm_TxMessageData in CanNm_DisablePNActivationState
 *                                ESCAN00071869 Fixed compile error in configurations with PN Feature enabled
 *********************************************************************************************************************/

#define CANNM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES (CANNM082)
 *********************************************************************************************************************/
#include "CanNm.h"                                                          /* Include CAN Network Management header */
#include "CanNm_Cbk.h"                                                             /* Include CAN NM callback header */
#include "Nm_Cbk.h"                                                          /* Include NM Interface callback header */
#include "CanIf.h"                                                                   /* Include CAN Interface header */
#if ( CANNM_DEV_ERROR_DETECT == STD_ON )
# include "Det.h"                                                                /* Include Development Error Tracer */
#endif
#if ( CANNM_PROD_ERROR_DETECT == STD_ON )
  /* DEM is already included via CanNm_Cfg.h */
#endif
/* ESCAN00053603 */
#include "SchM_CanNm.h"                                            /* Include Scheduler Module for Critical Sections */

#if defined ( CANNM_USE_EXTENDED_ASR_VERSION_CHECK )
# include "EcuM_Cbk.h"                                                                       /* EcuM Callback Header */
# include "v_ver.h"                                                                          /* Version Check Header */
#else
# if ( CANNM_CRC_CHECK == STD_ON )
#  include "EcuM_Cbk.h"                                                                      /* EcuM Callback Header */
# endif
#endif

#if ( CANNM_COM_USER_DATA_ENABLED == STD_ON ) || defined ( CANNM_PN_CALC_FEATURE_ENABLED )
# include "PduR_CanNm.h"                                                           /* PduR Callback Header for CanNm */
#endif

#if( CANNM_PN_FEATURE_ENABLED == STD_ON )
# include "CanSM_Cbk.h"                                                           /* CanSM Callback Header for CanNm */
#endif

#if ( CANNM_AMD_RUNTIME_MEASUREMENT == STD_ON )
# include "AmdRtm.h"             /* ESCAN00066109 */ /* AUTOSAR Monitoring and Debugging Run-Time Measurement Header */
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* CANNM200: vendor specific version information check */
#if (  (CANNM_SW_MAJOR_VERSION != (0x04u)) \
    || (CANNM_SW_MINOR_VERSION != (0x22u)) \
    || (CANNM_SW_PATCH_VERSION != (0x02u)) )
# error "Vendor specific version numbers of CanNm.c and CanNm.h are inconsistent"
#endif

/* CANNM200: vendor specific version information check */
#if (  (CANNM_CBK_MAJOR_VERSION != (0x04u)) \
    || (CANNM_CBK_MINOR_VERSION != (0x22u)) \
    || (CANNM_CBK_PATCH_VERSION != (0x02u)) )
# error "Vendor specific version numbers of CanNm.c and CanNm_Cbk.h are inconsistent"
#endif

/* ESCAN00051654 */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
/* PRQA S 3453 2 */ /* MD_MSR_19.4 */ /* ESCAN00053603 */ 
# define CANNM_ENTER_CRITICAL(critSection) SchM_Enter_CanNm(critSection)
# define CANNM_LEAVE_CRITICAL(critSection) SchM_Exit_CanNm(critSection)

#if ( CANNM_PROD_ERROR_DETECT == STD_ON ) && ( CANNM_CONFIG_VARIANT == 1 )
#  if ( CANNM_DEM2DET_ENABLED == STD_OFF )
/* ESCAN00051043 */
#   define CanNm_DemInitFailed            CANNM_ERROR_CODE_INIT_FAILED
#  endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF )
#  if ( CANNM_DEM2DET_ENABLED == STD_OFF )
/* ESCAN00051043 */
#   define CanNm_DemTxError               CANNM_ERROR_CODE_CANIF_TRANSMIT_ERROR
#  endif

#  define CanNm_DemNetTimeout             CANNM_ERROR_CODE_NW_TIMEOUT
# endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF ) */
#endif /* ( CANNM_PROD_ERROR_DETECT == STD_ON ) && ( CANNM_CONFIG_VARIANT == 1 ) */

/* Definition of channel parameter for local functions. */
/* Local functions do not use a channel parameter in single channel configurations. */
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# define CANNM_CHANNEL_PARA_ONLY
# define CANNM_CHANNEL_PARA_FIRST
#else
# define CANNM_CHANNEL_PARA_ONLY          CANNM_CHANNEL_IDX
# define CANNM_CHANNEL_PARA_FIRST         CANNM_CHANNEL_IDX,
#endif

#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# define CANNM_SYSTEM_CHANNEL_IDX         (CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_CHANNEL_ID)
# define CANNM_CHANNEL_IDX                ((NetworkHandleType)0u)
# define CANNM_NMTOSYSTEM_CHANNEL_IND     CANNM_SYSTEM_CHANNEL_IDX
#else
# define CANNM_SYSTEM_CHANNEL_IDX         (nmChannelHandle)
# define CANNM_CHANNEL_IDX                (channel)
# define CANNM_NMTOSYSTEM_CHANNEL_IND     (CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_CHANNEL_ID)
#endif

/* Definition of CanNm_RxIndication parameter access macros */
#define CANNM_RXINDICATION_PARAM_PTR     (PduInfoPtr)
#define CANNM_RXINDICATION_PARAM_DATAPTR (PduInfoPtr->SduDataPtr)

/* Magic Number Value for checking configurations */
#define CANNM_MAGIC_NUMBER_CHECK          0xBABE

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/* Enumeration type for Communication Control (optimized) */
/* The application has no communication need and is ready to sleep. */
# define COMM_READY_SLEEP                 ((uint8)0x00u)
/* The application has communication need. */
# define COMM_NORMAL_OPERATION            ((uint8)0x01u)
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
/* Enumeration type for Message Transmission Control (optimized) */
/* Message Transmission Ability is disabled */
# define MSG_TX_DISABLED                  ((uint8)0x00u)
/* Message Transmission Ability is enabled */
# define MSG_TX_ENABLED                   ((uint8)0x01u)
#endif

#if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED ) || \
    defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED ) || \
            ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/* Enumeration type for message layout (optimized) */ /* ESCAN00071869 */
/* No Position, i.e. NID / CBV disabled */
# define CANNM_PDU_OFF                    ((uint8)0xFF)
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
# define CANNM_REPEAT_MSG_BIT_MASK        ((uint8)0x01u)
# define CANNM_REPEAT_MSG_BIT_INV_MASK    ((uint8)0xFEu)
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON )
# define CANNM_ACT_WU_BIT_MASK        ((uint8)0x10u)
# define CANNM_ACT_WU_BIT_INV_MASK    ((uint8)0xEFu)
#endif

#if( CANNM_PN_FEATURE_ENABLED == STD_ON )
# define CANNM_CRI_BIT_MASK           ((uint8)0x40u)
# define CANNM_CRI_BIT_INV_MASK       ((uint8)0xBFu)
#endif

#define CANNM_INSTANCE_ID                 ((uint8)0u)

#if defined ( CANNM_MULTI_ECU_ENABLED ) || ( CANNM_CONFIG_VARIANT == 3 )
/* ESCAN00060200 */
# define CANNM_CFG_MSG_CYCLE_OFFSET       ((CanNm_PbChConfigPtr[CANNM_CHANNEL_IDX]).CANNM_MSG_CYCLE_OFFSET)
# define CANNM_CFG_MSG_REDUCED_TIME       ((CanNm_PbChConfigPtr[CANNM_CHANNEL_IDX]).CANNM_MSG_REDUCED_TIME)
# define CANNM_CFG_NODE_ID                ((CanNm_PbChConfigPtr[CANNM_CHANNEL_IDX]).CANNM_NODE_ID)
# define CANNM_CFG_TX_PDU_ID              ((CanNm_PbChConfigPtr[CANNM_CHANNEL_IDX]).CANNM_TX_PDU_ID)
# define CANNM_CFG_TX_USER_DATA_PDU_ID    ((CanNm_PbChConfigPtr[CANNM_CHANNEL_IDX]).CANNM_TX_USER_DATA_PDU_ID)
# define CANNM_CFG_PN_ENABLED             ((CanNm_PbChConfigPtr[CANNM_CHANNEL_IDX]).CANNM_PN_ENABLED)
# define CANNM_CFG_CAR_WUP_ENABLED        ((CanNm_PbChConfigPtr[CANNM_CHANNEL_IDX]).CANNM_CAR_WAKE_UP_RX_ENABLED)
#else
/* ESCAN00060200 */
# define CANNM_CFG_MSG_CYCLE_OFFSET       ((CanNm_PbChannelConfig0[CANNM_CHANNEL_IDX]).CANNM_MSG_CYCLE_OFFSET)
# define CANNM_CFG_MSG_REDUCED_TIME       ((CanNm_PbChannelConfig0[CANNM_CHANNEL_IDX]).CANNM_MSG_REDUCED_TIME)
# define CANNM_CFG_NODE_ID                ((CanNm_PbChannelConfig0[CANNM_CHANNEL_IDX]).CANNM_NODE_ID)
# define CANNM_CFG_TX_PDU_ID              ((CanNm_PbChannelConfig0[CANNM_CHANNEL_IDX]).CANNM_TX_PDU_ID)
# define CANNM_CFG_TX_USER_DATA_PDU_ID    ((CanNm_PbChannelConfig0[CANNM_CHANNEL_IDX]).CANNM_TX_USER_DATA_PDU_ID)
# define CANNM_CFG_PN_ENABLED             ((CanNm_PbChannelConfig0[CANNM_CHANNEL_IDX]).CANNM_PN_ENABLED)
# define CANNM_CFG_CAR_WUP_ENABLED        ((CanNm_PbChannelConfig0[CANNM_CHANNEL_IDX]).CANNM_CAR_WAKE_UP_RX_ENABLED)
#endif


#define CANNM_NO_RESTART       ((uint8)0u)
#define CANNM_PASSIVE_RESTART  ((uint8)1u)
#define CANNM_ACTIVE_RESTART   ((uint8)2u)

#if ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF )
/* ESCAN00051043 */
# if ( CANNM_PROD_ERROR_DETECT == STD_ON ) && ( CANNM_DEM2DET_ENABLED == STD_OFF )
/* CANNM_E_CANIF_TRANSMIT_ERROR is being reported to Dem */
#  define CANNM_ENABLE_TX_ERR_REPORT_AS_DEM
# endif

# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) && ( CANNM_DEM2DET_ENABLED == STD_ON )
/* CANNM_E_CANIF_TRANSMIT_ERROR is being reported to Det */
#  define CANNM_ENABLE_TX_ERR_REPORT_AS_DET
# endif
#endif

#if( CANNM_PN_FEATURE_ENABLED == STD_ON )
/* ESCAN00056701 */
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
/* RangeConfig DLC Check has been adjusted by CanNm: Use regular PN Info Length for CanNm_RxIndication */ 
#  define CANNM_RX_IND_ADJUSTED_INFO_LENGTH (CanNm_LConfiguration.CANNM_PN_INFO_LENGTH)
# else
/* Use variable PN Info Length for CanNm_RxIndication */ 
#  define CANNM_RX_IND_ADJUSTED_INFO_LENGTH (adjustedInfoLength)
# endif
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/* CANNM016, CANNM188: Macros for development error detection.  */
#if ( CANNM_DEV_ERROR_DETECT == STD_ON )
/* CANNM018, CANNM019, CANNM039, CANNM191: Check of initialization. */
# define CANNM_CHECK_INIT(ApiId)        { \
                                          if(CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_UNINIT) { Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(ApiId), CANNM_E_NO_INIT ); return; } \
                                        }  /* PRQA S 3458 */ /* MD_MSR_19.4 */
# define CANNM_CHECK_INIT_RET(ApiId)    { \
                                          if(CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_UNINIT) { Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(ApiId), CANNM_E_NO_INIT ); return NM_E_NOT_OK; } \
                                        }  /* PRQA S 3458 */ /* MD_MSR_19.4 */
/* CANNM018, CANNM019, CANNM192, CANNM196: Check of channel parameters. */
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
#  define CANNM_CHECK_CHANNEL_PARAM(ApiId)      { \
                                                  if(( nmChannelHandle >= CanNm_LConfiguration.CANNM_NUMBER_OF_SYSTEM_CHANNELS ) || ( channel == (NetworkHandleType)CANNM_INVALID_CHANNEL )) { Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(ApiId), CANNM_E_INVALID_CHANNEL ); return; } \
                                                }  /* PRQA S 3458 */ /* MD_MSR_19.4 */
#  define CANNM_CHECK_CHANNEL_PARAM_RET(ApiId)  { \
                                                  if(( nmChannelHandle >= CanNm_LConfiguration.CANNM_NUMBER_OF_SYSTEM_CHANNELS ) || ( channel == (NetworkHandleType)CANNM_INVALID_CHANNEL )) { Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(ApiId), CANNM_E_INVALID_CHANNEL ); return NM_E_NOT_OK; } \
                                                }  /* PRQA S 3458 */ /* MD_MSR_19.4 */
# endif
#else   /* ( CANNM_DEV_ERROR_DETECT == STD_ON ) */
/* CANNM018, CANNM019, CANNM039, CANNM191: Check of initialization. */
# define CANNM_CHECK_INIT(ApiId)        { \
                                          if(CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_UNINIT) { return; } \
                                        }  /* PRQA S 3458 */ /* MD_MSR_19.4 */
# define CANNM_CHECK_INIT_RET(ApiId)    { \
                                          if(CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_UNINIT) { return NM_E_NOT_OK; } \
                                        }  /* PRQA S 3458 */ /* MD_MSR_19.4 */
/* CANNM018, CANNM019, CANNM192, CANNM196: Check of channel parameters. */
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
#  define CANNM_CHECK_CHANNEL_PARAM(ApiId)      { \
                                                  if(( nmChannelHandle >= CanNm_LConfiguration.CANNM_NUMBER_OF_SYSTEM_CHANNELS ) || ( channel == (NetworkHandleType)CANNM_INVALID_CHANNEL )) { return; } \
                                                }  /* PRQA S 3458 */ /* MD_MSR_19.4 */
#  define CANNM_CHECK_CHANNEL_PARAM_RET(ApiId)  { \
                                                  if(( nmChannelHandle >= CanNm_LConfiguration.CANNM_NUMBER_OF_SYSTEM_CHANNELS ) || ( channel == (NetworkHandleType)CANNM_INVALID_CHANNEL )) { return NM_E_NOT_OK; } \
                                                }  /* PRQA S 3458 */ /* MD_MSR_19.4 */
# endif
#endif   /* else ( CANNM_DEV_ERROR_DETECT == STD_ON ) */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

#if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
/* ----------- Local 8 Bit Data definitions without initialization need ----------- */
#define CANNM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

STATIC VAR( uint8, CANNM_VAR_NOINIT ) nmMinPnChannel;

#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif
#endif

/* ----------- Local Data definitions with unspecified size and frequent access ----------- */
#define CANNM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Pointer to Linktime channel configuration for speeding up access */
STATIC P2CONST( CanNm_LChannelConfigType, CANNM_VAR_NOINIT_FAST, CANNM_CONST ) CanNm_LConfigPtr;
#if defined ( CANNM_MULTI_ECU_ENABLED ) || ( CANNM_CONFIG_VARIANT == 3 )
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) || ( CANNM_NODE_ID_ENABLED == STD_ON ) || \
     ( CANNM_PN_FEATURE_ENABLED == STD_ON ) || ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
/* Pointer to Postbuild channel configuration */ /* ESCAN00064042 */
STATIC P2CONST( CanNm_PbChannelConfigType, CANNM_VAR_NOINIT_FAST, CANNM_PBCFG ) CanNm_PbChConfigPtr;
# endif
#endif

#define CANNM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define CANNM_START_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* CAN NM version (BCD coded). */
CONST(uint8, CANNM_CONST) CanNm_MainVersion     = (uint8)CANNM_SW_MAJOR_VERSION;
CONST(uint8, CANNM_CONST) CanNm_SubVersion      = (uint8)CANNM_SW_MINOR_VERSION;
CONST(uint8, CANNM_CONST) CanNm_ReleaseVersion  = (uint8)CANNM_SW_PATCH_VERSION;

#define CANNM_STOP_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined ( CANNM_USE_EXTENDED_ASR_VERSION_CHECK )
#define CANNM_START_SEC_CONST_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* The name of this const variable is defined via v_ver.h and depends on the version of the C file. 
   The value of the const variable is also defined externally and is used for consistency checks. */
CONST( uint32, CANNM_CONST ) NM_ASRNMCAN_LIB_SYMBOL = NM_ASRNMCAN_LIB_VERSION;

#define CANNM_STOP_SEC_CONST_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define CANNM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Local Init functions for each channel. */
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
STATIC FUNC( void, CANNM_CODE ) CanNm_LocalInit( void );
#else
STATIC FUNC( void, CANNM_CODE ) CanNm_LocalInit( CONST( NetworkHandleType, AUTOMATIC ) channel );
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/* Local function for triggering NM message transmission. */
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
STATIC FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_TriggerTransmission( void );
# else
STATIC FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_TriggerTransmission( CONST( NetworkHandleType, AUTOMATIC ) channel );
# endif
#endif

/* State transition function. */
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
STATIC FUNC( void, CANNM_CODE ) CanNm_StateTransition( CONST( Nm_StateType, AUTOMATIC ) nextNmState );
#else
STATIC FUNC( void, CANNM_CODE ) CanNm_StateTransition( CONST( NetworkHandleType, AUTOMATIC ) channel, CONST( Nm_StateType, AUTOMATIC ) nextNmState );
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/**********************************************************************************************************************
  CanNm_TriggerTransmission
**********************************************************************************************************************/
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
STATIC FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_TriggerTransmission( void )
# else
STATIC FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_TriggerTransmission( CONST( NetworkHandleType, AUTOMATIC ) channel )
# endif
{
  VAR( PduInfoType, AUTOMATIC ) nmPduInfo;
  VAR( Std_ReturnType, AUTOMATIC ) retVal;
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  VAR( uint8, AUTOMATIC ) i;
# endif


# if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
  /* Get User Data via PduR / Com */
  nmPduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, CANNM_VAR_NOINIT))&(CanNm_TxMessageData[CANNM_CHANNEL_IDX][(CanNm_UserDataPosition[CANNM_CHANNEL_IDX])]);
  /* SDU Length is set by the upper layer to the number of copied bytes */
#  if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  retVal = PduR_CanNmTriggerTransmit( CANNM_CFG_TX_USER_DATA_PDU_ID, &nmPduInfo ); /* ESCAN00051411 */
  if( (retVal == E_NOT_OK) || (nmPduInfo.SduLength != (PduLengthType)CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_USER_DATA_LENGTH) )
  {
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)CANNM_MAINFUNCTION_ID, CANNM_E_PDUR_TRIGGERTX_ERROR );
  }
#  else
  (void)PduR_CanNmTriggerTransmit( CANNM_CFG_TX_USER_DATA_PDU_ID, &nmPduInfo ); /* ESCAN00051411 */
#  endif
# endif

# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  /* Get Internal Requests */
  if( ((boolean)CanNm_PnEnabled[CANNM_CHANNEL_IDX] == TRUE) && ((boolean)CanNm_LConfiguration.CANNM_PN_EIRA_CALC_ENABLED == TRUE) )
  {
    /* copy the requests and apply the PN filter mask: */
    CANNM_ENTER_CRITICAL(CANNM_EXCLUSIVE_AREA_0);
    for( i=0u; i<CanNm_LConfiguration.CANNM_PN_INFO_LENGTH; i++ )
    {
      CanNm_PnClusterReqNew[i] |= (uint8)((CanNm_TxMessageData[CANNM_CHANNEL_IDX][i+CanNm_LConfiguration.CANNM_PN_INFO_OFFSET]) & CanNm_PnFilterMask[i]);
    }
    CANNM_LEAVE_CRITICAL(CANNM_EXCLUSIVE_AREA_0);
  }
# endif

  /* Set actual data */
# if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED )
  CANNM_ENTER_CRITICAL(CANNM_EXCLUSIVE_AREA_1);
  nmPduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, CANNM_VAR_NOINIT))(CanNm_TxMessageData[CANNM_CHANNEL_IDX]);
# else
  nmPduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, CANNM_VAR_NOINIT))CanNm_TxMessageData;
# endif
  nmPduInfo.SduLength = (PduLengthType)CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_LENGTH;

# if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
  /* Clear Request shortly before a transmission is requested */
  CanNm_MsgRequest[CANNM_CHANNEL_IDX] = 0u;
# endif

  /* Transmit a NM message. */
  retVal = CanIf_Transmit( CANNM_CFG_TX_PDU_ID, &nmPduInfo );
# if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED )
  CANNM_LEAVE_CRITICAL(CANNM_EXCLUSIVE_AREA_1);
# endif

  /* ESCAN00050470 */
  if( retVal == E_OK )
  {
# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_ON )
    /* A flag is used in order to ensure data consistency of the timeout timer. */
    CanNm_MsgConfirmationFlag[CANNM_CHANNEL_IDX] = TRUE;
# else
    /* CANNM064: Start Timeout Timer */ /* ESCAN00054369 */
    CanNm_MsgTimeoutTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_MSG_TIMEOUT_TIME + (CanNm_TimerCounterType)1u;
# endif
  }
# if defined ( CANNM_ENABLE_TX_ERR_REPORT_AS_DEM ) || defined ( CANNM_ENABLE_TX_ERR_REPORT_AS_DET )
  else
  {
#  if defined ( CANNM_ENABLE_TX_ERR_REPORT_AS_DEM )
    /* CANNM018, CANNM020: Report Transmission Error to DEM */ /* ESCAN00051043 */
    Dem_ReportErrorStatus( CanNm_DemTxError, DEM_EVENT_STATUS_FAILED );
#  endif

#  if defined ( CANNM_ENABLE_TX_ERR_REPORT_AS_DET )
    /* ESCAN00045764: Report Transmission Error to DET */ /* ESCAN00051043 */
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)CANNM_MAINFUNCTION_ID, CANNM_E_CANIF_TRANSMIT_ERROR );
#  endif
  }
# endif

  return retVal;
}
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) */


/**********************************************************************************************************************
  CanNm_LocalMainFunction
**********************************************************************************************************************/
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
FUNC( void, CANNM_CODE ) CanNm_LocalMainFunction( void )
#else
FUNC( void, CANNM_CODE ) CanNm_LocalMainFunction( CONST( NetworkHandleType, AUTOMATIC ) channel )
#endif
{
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  VAR( uint8, AUTOMATIC ) commState;            /* local copy of the global communication state. */
# if ( CANNM_COM_CONTROL_ENABLED == STD_ON )
  VAR ( uint8, AUTOMATIC ) txControlStateReq;    /* local copy of the requested Tx control state. */
# endif
#endif

#if defined ( CANNM_PN_CALC_FEATURE_ENABLED )
  VAR ( uint8, AUTOMATIC ) i;
  VAR ( uint8, AUTOMATIC ) j;
  VAR ( uint8, AUTOMATIC ) pnReqNew;
  VAR ( boolean, AUTOMATIC ) pnChanged;
#endif

#if ( CANNM_DEV_ERROR_DETECT == STD_ON )
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Check for correct channel (only for development error detection) */
  if( CANNM_CHANNEL_IDX >= CanNm_LConfiguration.CANNM_NUMBER_OF_CHANNELS)
  {
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)CANNM_MAINFUNCTION_ID, CANNM_E_INVALID_CHANNEL );
  }
  else
  { /* ESCAN00050423 */
# endif
#endif

    /* Check whether the NM is initialized. */
    if(CanNm_NmState[CANNM_CHANNEL_IDX] != NM_STATE_UNINIT)
    {

      /* Store current configuration pointer for faster access */
      CanNm_LConfigPtr = &(CanNm_LChannelConfig[CANNM_CHANNEL_IDX]);

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
      /* Check if the request has changed */
      txControlStateReq = CanNm_TxControlStateRequest[CANNM_CHANNEL_IDX];
      if( CanNm_TxControlState[CANNM_CHANNEL_IDX] != txControlStateReq )
      {
        CanNm_TxControlState[CANNM_CHANNEL_IDX] = txControlStateReq;
        if( txControlStateReq == MSG_TX_DISABLED )
        {
          /* CANNM174: Stop Nm Timeout Timer */
          CanNm_TimeoutTimer[CANNM_CHANNEL_IDX] = (CanNm_TimerCounterType)0u; 
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
          /* CANNM175: Reset Remote Sleep Timer and state. */
          CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX]    = (CanNm_TimerCounterType)0u;
          CanNm_RemoteSleepIndState[CANNM_CHANNEL_IDX] = FALSE;
# endif
          /* CANNM051, CANNM173: Stop NM message timer. */
          CanNm_MsgTimer[CANNM_CHANNEL_IDX] = (CanNm_TimerCounterType)0u;
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
          /* Do not stop Timeout Timer */ /* ESCAN00059456 */
# endif
        }
        else
        {

          /* CANNM179, CANNM206: Restart Nm Timeout Timer */
          CanNm_TimeoutTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_TIMEOUT_TIME + (CanNm_TimerCounterType)1u;
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
          if( CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_NORMAL_OPERATION )
          {
            /* CANNM180: Resume Remote Sleep Indication */
            CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_REMOTE_SLEEP_IND_TIME + (CanNm_TimerCounterType)1u;
          }
# endif
          if( ( CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_NORMAL_OPERATION ) || ( CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_REPEAT_MESSAGE ) )
          {
            /* CANNM005, CANNM178: Start NM message timer. */
            CanNm_MsgTimer[CANNM_CHANNEL_IDX] = CANNM_CFG_MSG_CYCLE_OFFSET + (CanNm_TimerCounterType)1u; /* ESCAN00060200 */
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
            /* Do not restart Timeout Timer */ /* ESCAN00054369 */
# endif
          }

        }
      }
#endif



#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
      /* Copy of the global communication state. */
      commState = CanNm_CommState[CANNM_CHANNEL_IDX];

      /* Processing of event: Tx Confirmation (#1) */
      if( CanNm_MsgConfirmationFlag[CANNM_CHANNEL_IDX] == TRUE )
      {
        CanNm_MsgConfirmationFlag[CANNM_CHANNEL_IDX] = FALSE;
# if ( CANNM_COM_CONTROL_ENABLED == STD_ON )
        if( CanNm_TxControlState[CANNM_CHANNEL_IDX] == MSG_TX_ENABLED )
# endif
        {
          /* CANNM099, CANNM206: Reset the Network timeout timer (in Network Mode only). */
          CanNm_TimeoutTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_TIMEOUT_TIME + (CanNm_TimerCounterType)1u;
# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
          /* CANNM065: Stop Transmission Timeout Timer */
          CanNm_MsgTimeoutTimer[CANNM_CHANNEL_IDX] = 0u; /* ESCAN00054369 */
# endif
        }
      }
#endif

      /* Processing of event: Rx Ind. (#2) */
      if( CanNm_MsgIndicationFlag[CANNM_CHANNEL_IDX] == TRUE )
      {
        CanNm_MsgIndicationFlag[CANNM_CHANNEL_IDX] = FALSE;
        switch ( CanNm_NmState[CANNM_CHANNEL_IDX] )
        {
          /* -------------------- Bus Sleep -------------------- */
        case NM_STATE_BUS_SLEEP:
          /* Request to restart the network if a NM message has been received in Bus-Sleep Mode. */
          Nm_NetworkStartIndication( CANNM_NMTOSYSTEM_CHANNEL_IND );
          break;

          /* -------------------- Prepare Bus Sleep -------------------- */
        case NM_STATE_PREPARE_BUS_SLEEP:
          /* CANNM090, CANNM095, CANNM124: Perform state transition. */
          CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_REPEAT_MESSAGE );
          break;

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
# if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) || ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON )
          /* -------------------- Normal Operation -------------------- */
        case NM_STATE_NORMAL_OPERATION:
#  if ( CANNM_COM_CONTROL_ENABLED == STD_ON )
          if( CanNm_TxControlState[CANNM_CHANNEL_IDX] == MSG_TX_ENABLED )
#  endif
          {
#  if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
            /* Restart Remote Sleep Indication Timer (Normal Operation) */
            CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_REMOTE_SLEEP_IND_TIME + (CanNm_TimerCounterType)1u;
#  endif

            /* CANNM052, CANNM155: Bus Load Reduction is configurable */
#  if ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON )
            /* Busload Reduction can only be active in normal operation and nowhere else (CANNM023, CANNM156, CANNM157) */
            if( (boolean)CanNm_LConfigPtr->CANNM_BUS_LOAD_REDUCTION_ACTIVE == TRUE )
            {
              /* CANNM069: Reload the NM Message Transmission Timer with reduced timing if a NM message has been received. */
              CanNm_MsgTimer[CANNM_CHANNEL_IDX] = CANNM_CFG_MSG_REDUCED_TIME + (CanNm_TimerCounterType)1u; /* ESCAN00060200 */
#   if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
              /* NM Message Transmission Timeout Timer remains untouched here */ /* ESCAN00054369 */
#   endif
            }
#  endif /* ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON ) */
          }

          /* -------------------- Ready Sleep -------------------- */
          /* FALLTHROUGH */
        case NM_STATE_READY_SLEEP:  /* PRQA S 2003 */ /* MD_CanNm_2003 */
#  if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
          /* Reset Remote Sleep in Normal Operation or Ready Sleep */
          if( CanNm_RemoteSleepIndState[CANNM_CHANNEL_IDX] == TRUE )
          {
            CanNm_RemoteSleepIndState[CANNM_CHANNEL_IDX] = FALSE;
            /* CANNM152: Notification that some nodes in the network are not ready to sleep. */
            Nm_RemoteSleepCancellation( CANNM_NMTOSYSTEM_CHANNEL_IND );
          }
#  endif
# endif /* ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) || ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON ) */
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

          /* -------------------- Repeat Message -------------------- */
          /* FALLTHROUGH */
        default:  /* PRQA S 2003 */ /* MD_CanNm_2003 */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
          if( CanNm_TxControlState[CANNM_CHANNEL_IDX] == MSG_TX_ENABLED )
#endif
          {
            /* CANNM098, CANNM206: Reset the Network timeout timer (in Network Mode only). */
            CanNm_TimeoutTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_TIMEOUT_TIME + (CanNm_TimerCounterType)1u;
          }

          break;
        }
      }

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
      /* Processing of event: Repeat Message Ind. (#3) */
      if( CanNm_RepeatMsgReqFlag[CANNM_CHANNEL_IDX] == TRUE )
      {
        CanNm_RepeatMsgBitIndFlag[CANNM_CHANNEL_IDX] = TRUE;
        /* Check for valid PDU Position */
        if( CanNm_LConfigPtr->CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF )
        {
          /* CANNM113, CANNM121: Set Repeat Message Bit */
          CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LConfigPtr->CANNM_PDU_CBV_POSITION] |= CANNM_REPEAT_MSG_BIT_MASK;
        }
      }
      if( CanNm_RepeatMsgBitIndFlag[CANNM_CHANNEL_IDX] == TRUE )
      {
# if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
        if( CanNm_RemoteSleepIndState[CANNM_CHANNEL_IDX] == TRUE )
        {
          /* CANNM152: Notification that some nodes in the network are not ready to sleep. */
          Nm_RemoteSleepCancellation( CANNM_NMTOSYSTEM_CHANNEL_IND );
        }
# endif
        /* CANNM090, CANNM111, CANNM112, CANNM119, CANNM120: Perform a State Transition to Repeat Message State. */
        CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_REPEAT_MESSAGE );
        CanNm_RepeatMsgReqFlag[CANNM_CHANNEL_IDX] = FALSE;
      }
#endif

      /* Processing of event: Network Restart (#4). */
      if( CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX] != CANNM_NO_RESTART )
      {
        /* CANNM090, CANNM095, CANNM123, CANNM128, CANNM129: Perform a state transition to Network Mode. */
        CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_REPEAT_MESSAGE );
      }

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
      /* Processing of event: Request / Release bus communication (#5). */
      if( commState == COMM_NORMAL_OPERATION )
      {
        if( CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_READY_SLEEP )
        {
          /* CANNM090, CANNM110: Perform a state transition because bus-communication has been requested. */
          CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_NORMAL_OPERATION);
        }
      }
      else
      {
        if( CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_NORMAL_OPERATION )
        {
          /* CANNM090, CANNM118: Perform a state transition because bus-communication has been released. */
          CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_READY_SLEEP );
        }
      }
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */

      /* Handling of NM Timeout Timer (#6) */
      if( CanNm_TimeoutTimer[CANNM_CHANNEL_IDX] != (CanNm_TimerCounterType)0u )
      {
        CanNm_TimeoutTimer[CANNM_CHANNEL_IDX]--;
        if( CanNm_TimeoutTimer[CANNM_CHANNEL_IDX] == (CanNm_TimerCounterType)0u )
        {
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
          if( CanNm_NmState[CANNM_CHANNEL_IDX] != NM_STATE_READY_SLEEP )
          {
            /* Handling of the Timeout Timer (Repeat Message State and Normal Operation State) */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) && ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF )
            /* CANNM018, CANNM019: Report error if the timeout timer times out in Repeat Message State or Normal Operation State. */
            Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_MAINFUNCTION_ID), CANNM_E_DEV_NETWORK_TIMEOUT );
# endif

# if ( CANNM_PROD_ERROR_DETECT == STD_ON ) && ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF )
            /* CANNM018, CANNM020, CANNM193, CANNM194: Report error if the timeout timer times out in Repeat Message State or Normal Operation State. */
            Dem_ReportErrorStatus( CanNm_DemNetTimeout, DEM_EVENT_STATUS_FAILED );
# endif

            /* CANNM101, CANNM117, CANNM206: Restart the NM Timeout Timer. */
            CanNm_TimeoutTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_TIMEOUT_TIME;


          }
          else
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */
          {
            /* CANNM090, CANNM109: Leave Ready Sleep State, when the Timeout Timer has expired. */
            CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_PREPARE_BUS_SLEEP );
          }
        }
      }

      /* Handling of Repeat Message Timer (#7) */
      if( CanNm_RepeatMsgTimer[CANNM_CHANNEL_IDX] != (CanNm_TimerCounterType)0u )
      {
        CanNm_RepeatMsgTimer[CANNM_CHANNEL_IDX]--;
        if( CanNm_RepeatMsgTimer[CANNM_CHANNEL_IDX] == (CanNm_TimerCounterType)0u ) 
        {
          /* CANNM090, CANNM102, CANNM103, CANNM106: Repeat Message State is left upon Repeat Message Timer timeout. */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
          CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  (Nm_StateType)((CanNm_CommState[CANNM_CHANNEL_IDX] == COMM_NORMAL_OPERATION) ? NM_STATE_NORMAL_OPERATION : NM_STATE_READY_SLEEP) );
#else
          CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_READY_SLEEP );
#endif
        }
      }

      /* Handling of Wait Bus Sleep Timer (#8) */
      if( CanNm_WaitBusSleepTimer[CANNM_CHANNEL_IDX] != (CanNm_TimerCounterType)0u )
      {
        CanNm_WaitBusSleepTimer[CANNM_CHANNEL_IDX]--;
        if( CanNm_WaitBusSleepTimer[CANNM_CHANNEL_IDX] == (CanNm_TimerCounterType)0u ) 
        {
          /* CANNM088, CANNM090, CANNM115, CANNM125: Prepare Bus-Sleep Mode is left upon Wait Bus-Sleep Timer timeout. */
          CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_BUS_SLEEP );
        }
      }

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
      /* Handling of Remote Sleep Indication Timer (#9) */
      if( CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX] != (CanNm_TimerCounterType)0u )
      {
        CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX]--;
        if( CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX] == (CanNm_TimerCounterType)0u )
        {
          /* Remote Sleep Indication (Normal Operation State only). */
          CanNm_RemoteSleepIndState[CANNM_CHANNEL_IDX] = TRUE;

          /* CANNM150: Notification that all other nodes are ready to sleep. */
          Nm_RemoteSleepIndication( CANNM_NMTOSYSTEM_CHANNEL_IND );
        }
      }
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
      /* Handling of Tx Message Timer (#10) */
      if( CanNm_MsgTimer[CANNM_CHANNEL_IDX] != (CanNm_TimerCounterType)0u )
      {
        CanNm_MsgTimer[CANNM_CHANNEL_IDX]--;
        if( (CanNm_MsgTimer[CANNM_CHANNEL_IDX] == (CanNm_TimerCounterType)0u)
# if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
          || (CanNm_MsgRequest[CANNM_CHANNEL_IDX] != 0u)
# endif
          )
        {
# if ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
          /* CANNM001, CANNM032, CANNM087: Transmit a NM message. */
          VAR(Nm_ReturnType, AUTOMATIC) success = CanNm_TriggerTransmission( CANNM_CHANNEL_PARA_ONLY );
# else
          /* CANNM001, CANNM032, CANNM087: Transmit a NM message. */
          (void)CanNm_TriggerTransmission( CANNM_CHANNEL_PARA_ONLY );
# endif

          {
# if ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
            if( CanNm_ImmediateNmMsgCount[CANNM_CHANNEL_IDX] != 0u )
            {
              /* Immediate Transmissions */
              if (success == (Nm_ReturnType)NM_E_OK) /* ESCAN00057728 */
              {
                CanNm_ImmediateNmMsgCount[CANNM_CHANNEL_IDX]--;
              }
              CanNm_MsgTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_IMMEDIATE_NM_CYCLE_TIME;
            }
            else
# endif
            {
              /* CANNM040: Reset Timer */
              CanNm_MsgTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_MSG_CYCLE_TIME;
            }
          }
        }
      }

# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
      /* Handling of Tx Message Timeout Timer (#11) */
      if( CanNm_MsgTimeoutTimer[CANNM_CHANNEL_IDX] != (CanNm_TimerCounterType)0u )
      {
        /* Decrement NM message timeout timer. */
        CanNm_MsgTimeoutTimer[CANNM_CHANNEL_IDX]--;

        if( CanNm_MsgTimeoutTimer[CANNM_CHANNEL_IDX] == (CanNm_TimerCounterType)0u )
        {
          /* CANNM066: Call timeout exception only once */
          Nm_TxTimeoutException( CANNM_NMTOSYSTEM_CHANNEL_IND );
#  if( CANNM_PN_FEATURE_ENABLED == STD_ON )
          if ( (boolean)CanNm_PnEnabled[CANNM_CHANNEL_IDX] == TRUE )
          {
            /* CANNM458: PN Feature enabled: call CanSM_TxTimeoutException */ /* ESCAN00048297 */
            CanSM_TxTimeoutException( CANNM_NMTOSYSTEM_CHANNEL_IND );
          }
#  endif
        }
      }
# endif /* ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF ) */
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
      {
# if defined ( CANNM_PN_CALC_FEATURE_ENABLED )
        PduInfoType nmPnInfo;
# endif

# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
        if(
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
          ((boolean)CanNm_PnEnabled[CANNM_CHANNEL_IDX] == TRUE)
#  else
          (CANNM_CHANNEL_IDX == nmMinPnChannel)
#  endif
          && ((boolean)CanNm_LConfiguration.CANNM_PN_EIRA_CALC_ENABLED == TRUE) )
        {
          pnChanged = FALSE;
          for( i=0u; i<CanNm_LConfiguration.CANNM_PN_INFO_LENGTH; i++ )
          {
            /* Check for new / repeated cluster requests */
            if( CanNm_PnClusterReqNew[i] != 0u )
            {
              /* Copy to local buffer to avoid long interrupt locks */
              CANNM_ENTER_CRITICAL(CANNM_EXCLUSIVE_AREA_0);
              pnReqNew = CanNm_PnClusterReqNew[i];
              /* Clear new / repeated request buffer */
              CanNm_PnClusterReqNew[i] = 0u;
              CANNM_LEAVE_CRITICAL(CANNM_EXCLUSIVE_AREA_0);

              /* Check for changes */
              j = (uint8)(CanNm_PnClusterReq[i]|pnReqNew);
              if( j != CanNm_PnClusterReq[i])
              {
                pnChanged = TRUE;
                /* Update EIRA */
                CanNm_PnClusterReq[i] = j;
              }

              /* Timer Restart Handling */
              for( j=0u; j<8u; j++ )
              {
                if( (pnReqNew & (1u<<j)) != 0u )
                {
                  CanNm_PnClusterResetTimer[i][j] = CanNm_LConfigPtr->CANNM_PN_RESET_TIME;
                }
              }
            }

            /* Timer Handling only necessary if at least one cluster is requested */
            if( CanNm_PnClusterReq[i] != 0u )
            {
              for( j=0u; j<8u; j++ )
              {
                if( CanNm_PnClusterResetTimer[i][j] != (CanNm_TimerCounterType)0u )
                {
                  CanNm_PnClusterResetTimer[i][j]--;

                  if( CanNm_PnClusterResetTimer[i][j] == (CanNm_TimerCounterType)0u ) /* PRQA S 0715 */ /* MD_MSR_1.1 */
                  {
                    pnChanged = TRUE;
                    /* Clear bit by AND operation with inversed bit */
                    CanNm_PnClusterReq[i] &= (uint8)(~(1u<<j));
                  }
                }
              }
            }
          }

          /* Change Indication */
          if( pnChanged == TRUE )
          {
            nmPnInfo.SduDataPtr = CanNm_PnClusterReq;
            nmPnInfo.SduLength = CanNm_LConfiguration.CANNM_PN_INFO_LENGTH;
            PduR_CanNmRxIndication( CanNm_LConfiguration.CANNM_PN_EIRA_RX_PDU_ID, &nmPnInfo );
          }
        }
# endif /* CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON */

# if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
        if( ((boolean)CanNm_PnEnabled[CANNM_CHANNEL_IDX] == TRUE)
          && ((boolean)CanNm_LConfigPtr->CANNM_PN_ERA_CALC_ENABLED == TRUE) )
        {
          pnChanged = FALSE;

          for( i=0u; i<CanNm_LConfiguration.CANNM_PN_INFO_LENGTH; i++ )
          {
            /* Check for new / repeated cluster requests */
            if( CanNm_PnClusterReqExtNew[CANNM_CHANNEL_IDX][i] != 0u )
            {
              /* Copy to local buffer to avoid long interrupt locks */
              CANNM_ENTER_CRITICAL(CANNM_EXCLUSIVE_AREA_0);
              pnReqNew = CanNm_PnClusterReqExtNew[CANNM_CHANNEL_IDX][i];
              /* Clear new / repeated request buffer */
              CanNm_PnClusterReqExtNew[CANNM_CHANNEL_IDX][i] = 0u;
              CANNM_LEAVE_CRITICAL(CANNM_EXCLUSIVE_AREA_0);

              /* Check for changes */
              j = (uint8)(CanNm_PnClusterReqExt[CANNM_CHANNEL_IDX][i]|pnReqNew);
              if( j != CanNm_PnClusterReqExt[CANNM_CHANNEL_IDX][i])
              {
                pnChanged = TRUE;
                /* Update ERA */
                CanNm_PnClusterReqExt[CANNM_CHANNEL_IDX][i] = j;
              }

              /* Timer Restart Handling */
              for( j=0u; j<8u; j++ )
              {
                if( (pnReqNew & (1u<<j)) != 0u )
                {
                  CanNm_PnClusterResetTimerExt[CANNM_CHANNEL_IDX][i][j] = CanNm_LConfigPtr->CANNM_PN_RESET_TIME;
                }
              }
            }

            /* Timer Handling only necessary if at least one cluster is requested */
            if( CanNm_PnClusterReqExt[CANNM_CHANNEL_IDX][i] != 0u )
            {
              for( j=0u; j<8u; j++ )
              {
                if( CanNm_PnClusterResetTimerExt[CANNM_CHANNEL_IDX][i][j] != (CanNm_TimerCounterType)0u )
                {
                  CanNm_PnClusterResetTimerExt[CANNM_CHANNEL_IDX][i][j]--;

                  if( CanNm_PnClusterResetTimerExt[CANNM_CHANNEL_IDX][i][j] == (CanNm_TimerCounterType)0u ) /* PRQA S 0715 */ /* MD_MSR_1.1 */
                  {
                    pnChanged = TRUE;
                    /* Clear bit by AND operation with inversed bit */
                    CanNm_PnClusterReqExt[CANNM_CHANNEL_IDX][i] &= (uint8)(~(1u<<j));
                  }
                }
              }
            }
          }

          /* Change Indication */
          if( pnChanged == TRUE )
          {
            nmPnInfo.SduDataPtr = CanNm_PnClusterReqExt[CANNM_CHANNEL_IDX];
            nmPnInfo.SduLength = CanNm_LConfiguration.CANNM_PN_INFO_LENGTH;
            PduR_CanNmRxIndication( CanNm_LConfigPtr->CANNM_PN_ERA_RX_PDU_ID, &nmPnInfo );
          }

        }
# endif /* CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON */

      }
#endif /* CANNM_PN_FEATURE_ENABLED == STD_ON */

    }
#if ( CANNM_DEV_ERROR_DETECT == STD_ON )
# if defined ( CANNM_IDENTITY_MANAGER_CONFIG )
    /* ESCAN00047497: Do not report a DET error as component could be uninitialized in this configuration */
# else
    else
    {
      /* Report DET error only for active channels */
      if( (boolean)CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_CHANNEL_ACTIVE == TRUE )
      {
        Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)CANNM_MAINFUNCTION_ID, CANNM_E_NO_INIT );
      }
    }
# endif
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  } /* ESCAN00050423 */
# endif
#endif

} /* CanNm_LocalMainFunction */ /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */


/**********************************************************************************************************************
  CanNm_LocalInit
**********************************************************************************************************************/
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
STATIC FUNC( void, CANNM_CODE ) CanNm_LocalInit( void )
#else
STATIC FUNC( void, CANNM_CODE ) CanNm_LocalInit( CONST( NetworkHandleType, AUTOMATIC ) channel )
#endif
{

#if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED ) || defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED ) \
  || defined ( CANNM_PN_CALC_FEATURE_ENABLED ) || ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
  VAR ( uint8, AUTOMATIC ) i;
# if defined ( CANNM_PN_CALC_FEATURE_ENABLED )
  VAR ( uint8, AUTOMATIC ) j;
# endif
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  /* CANNM143: The bus-communication is initially released. */
  CanNm_CommState[CANNM_CHANNEL_IDX]     = COMM_READY_SLEEP;
#endif

  /* Reset flags */
  CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX]  = CANNM_NO_RESTART;
  CanNm_MsgIndicationFlag[CANNM_CHANNEL_IDX]   = FALSE;

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
  CanNm_ImmediateNmMsgCount[CANNM_CHANNEL_IDX] = 0u;
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  CanNm_MsgConfirmationFlag[CANNM_CHANNEL_IDX] = FALSE;

# if ( CANNM_NODE_DETECTION_ENABLED == STD_ON )  
  CanNm_RepeatMsgBitIndFlag[CANNM_CHANNEL_IDX] = FALSE;
  CanNm_RepeatMsgReqFlag[CANNM_CHANNEL_IDX] = FALSE;
# endif
#endif

  /* Reset Timers. */
  /* All timers have to be initialized since they are processed in every state. */
  CanNm_TimeoutTimer[CANNM_CHANNEL_IDX]      = (CanNm_TimerCounterType)0u;
  CanNm_WaitBusSleepTimer[CANNM_CHANNEL_IDX] = (CanNm_TimerCounterType)0u;
  CanNm_RepeatMsgTimer[CANNM_CHANNEL_IDX]    = (CanNm_TimerCounterType)0u;

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
  /* Reset Remote Sleep Timer and state. */
  CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX] = (CanNm_TimerCounterType)0u;
  CanNm_RemoteSleepIndState[CANNM_CHANNEL_IDX] = FALSE;
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
  /* CANNM033, CANNM051, CANNM061: The transmission of NM messages is initially stopped. */
  CanNm_MsgTimer[CANNM_CHANNEL_IDX] = (CanNm_TimerCounterType)0u;
# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
  /* CANNM068: Timeout Timer is initially stopped */
  CanNm_MsgTimeoutTimer[CANNM_CHANNEL_IDX] = (CanNm_TimerCounterType)0u;
# endif

# if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
  CanNm_MsgRequest[CANNM_CHANNEL_IDX] = 0u;
# endif
#endif


#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
  /* CANNM169: Per default the transmission control status is enabled. */
  CanNm_TxControlState[CANNM_CHANNEL_IDX] = MSG_TX_ENABLED;
  CanNm_TxControlStateRequest[CANNM_CHANNEL_IDX] = MSG_TX_ENABLED;
#endif

#if( CANNM_PN_FEATURE_ENABLED == STD_ON )
  /* CANNM456: The CanNm module's initialization shall cause the PN message filtering to be disabled. */
  CanNm_PnMessageFilterEnabled[CANNM_CHANNEL_IDX] = FALSE;
  CanNm_PnEnabled[CANNM_CHANNEL_IDX] = CANNM_CFG_PN_ENABLED;

  if( (boolean)CanNm_PnEnabled[CANNM_CHANNEL_IDX] == TRUE )
  {
# if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
    /* Initialize ERA */
    for( i=0u; i<CanNm_LConfiguration.CANNM_PN_INFO_LENGTH; i++ )
    {
      CanNm_PnClusterReqExt[CANNM_CHANNEL_IDX][i] = 0x00u;
      CanNm_PnClusterReqExtNew[CANNM_CHANNEL_IDX][i] = 0x00u;

      for( j=0u; j<8u; j++ )
      {
        CanNm_PnClusterResetTimerExt[CANNM_CHANNEL_IDX][i][j] = (CanNm_TimerCounterType)0u;
      }
    }
# endif
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
    /* Initialize EIRA */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#  else
    if( nmMinPnChannel == 0xFFu )
#  endif
    {
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#  else
      nmMinPnChannel = CANNM_CHANNEL_IDX;
#  endif
      for( i=0u; i<CanNm_LConfiguration.CANNM_PN_INFO_LENGTH; i++ ) 
      {
        CanNm_PnClusterReq[i] = 0x00u;
        CanNm_PnClusterReqNew[i] = 0x00u;

        for( j=0u; j<8u; j++ )
        {
          CanNm_PnClusterResetTimer[i][j] = (CanNm_TimerCounterType)0u;
        }
      }
    }
# endif
  }
#endif

  /* Initialize NM message data. */
#if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED ) || defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED )

  /* CANNM025: Initialize User Data with 0xFF */
  for( i=0u; i<CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_LENGTH; i++ )
  {
# if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED )
    CanNm_TxMessageData[CANNM_CHANNEL_IDX][i] = 0xFFu;
# endif
# if defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED )
    CanNm_RxMessageData[CANNM_CHANNEL_IDX][i] = 0xFFu;
# endif
  }

  /* The reserved bits are set to 0 */
# if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED )
  if( CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_NID_POSITION != CANNM_PDU_OFF )
  {
    /* CANNM013: Source Node Identifier */
#  if ( CANNM_NODE_ID_ENABLED == STD_ON )
    CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_NID_POSITION] = CANNM_CFG_NODE_ID;
#  else
    CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_NID_POSITION] = 0x00;
#  endif
  }

  if( CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF )
  {
#  if( CANNM_PN_FEATURE_ENABLED == STD_ON )
    if( (boolean)CanNm_PnEnabled[CANNM_CHANNEL_IDX] == TRUE )
    {
      /* Initialize with PN bit set */
      CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION] = CANNM_CRI_BIT_MASK;
    }
    else
#  endif
    {
      /* CANNM085: ControlBitVector = 0x00, RepeatMessageBit = FALSE */
      CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION] = 0x00u;
    }
  }
# endif

# if ( CANNM_USER_DATA_ENABLED == STD_ON ) || ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
  /* Ensure valid User Data Index */
  if( CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_LENGTH > CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_USER_DATA_LENGTH )
  {
    CanNm_UserDataPosition[CANNM_CHANNEL_IDX] = (uint8)(CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_LENGTH - CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_USER_DATA_LENGTH);
  }
  else
  {
    CanNm_UserDataPosition[CANNM_CHANNEL_IDX] = 0u;
  }
# endif
#endif

#if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED )
#else
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
  /* Initialize Transmission Dummy Buffer */
  for( i=0u; i<CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_LENGTH; i++ )
  {
    CanNm_TxMessageData[i] = 0xFFu;
  }
# endif
#endif

  /* CANNM141, CANNM144: State machine initialization without notification. */
  CanNm_NmState[CANNM_CHANNEL_IDX] = NM_STATE_BUS_SLEEP;
}  /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */


/**********************************************************************************************************************
  CanNm_StateTransition
**********************************************************************************************************************/
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
STATIC FUNC( void, CANNM_CODE ) CanNm_StateTransition( CONST( Nm_StateType, AUTOMATIC ) nextNmState )
#else
STATIC FUNC( void, CANNM_CODE ) CanNm_StateTransition( CONST( NetworkHandleType, AUTOMATIC ) channel, CONST( Nm_StateType, AUTOMATIC ) nextNmState )
#endif
{

  VAR( Nm_StateType, AUTOMATIC ) lastNmState;   /* Last state of the state machine. */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_RESTART_ENABLED == STD_ON )
  VAR( uint8, AUTOMATIC ) additionalTransmissionRequired = 0u;
#endif

  {
    /* Store the current state and acquire a new state. */
    lastNmState = CanNm_NmState[CANNM_CHANNEL_IDX];
    CanNm_NmState[CANNM_CHANNEL_IDX] = nextNmState;

    /* Perform action on transition */
    switch (nextNmState)
    {
      /* -------------------- transition to Bus Sleep -------------------- */
    case NM_STATE_BUS_SLEEP:
      /* CANNM093, CANNM126: Notify Nm Interface about state change. */
      Nm_BusSleepMode( CANNM_NMTOSYSTEM_CHANNEL_IND );
#if( CANNM_PN_FEATURE_ENABLED == STD_ON )
      /* CANNM456: Entering the Bus-Sleep Mode shall cause the PN message filtering to be disabled. */
      CanNm_PnMessageFilterEnabled[CANNM_CHANNEL_IDX] = FALSE;
#endif
      break;

      /* -------------------- transition to Prepare Bus Sleep -------------------- */
    case NM_STATE_PREPARE_BUS_SLEEP:
      /* CANNM093, CANNM114: Notify Nm Interface, that the network mode is stopped (Prepare Bus Sleep State is entered). */
      Nm_PrepareBusSleepMode( CANNM_NMTOSYSTEM_CHANNEL_IND );
      /* CANNM115: Reset the Bus Sleep Time timer. */
      CanNm_WaitBusSleepTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_WAIT_BUS_SLEEP_TIME + (CanNm_TimerCounterType)1u;

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON )
      if( (boolean)CanNm_LConfigPtr->CANNM_ACTIVE_WAKE_UP_BIT_ENABLED == TRUE )
      {
        if( CanNm_LConfigPtr->CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF )
        {
          /* CANNM455: Reset Active Wake-up Bit in CBV */
          CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LConfigPtr->CANNM_PDU_CBV_POSITION] &= CANNM_ACT_WU_BIT_INV_MASK;
        }
      }
#endif
      break;

      /* -------------------- transition to Ready Sleep -------------------- */
    case NM_STATE_READY_SLEEP:
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
      /* CANNM051, CANNM108: Stop NM message timer. */
      CanNm_MsgTimer[CANNM_CHANNEL_IDX] = (CanNm_TimerCounterType)0u;
# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
      /* Message Timeout Timer is not stopped here */ /* ESCAN00054369 */
# endif
# if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
      /* Reset Remote Sleep Timer (Normal to Ready Only)*/
      CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX] = (CanNm_TimerCounterType)0u;
# endif
# if ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
      /* Check for PDU Position set to PDU_OFF */
      if( CanNm_LConfigPtr->CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF )
      {
        /* CANNM107: Clear the repeat message bit (Repeat to Ready only). */
        CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LConfigPtr->CANNM_PDU_CBV_POSITION] &= CANNM_REPEAT_MSG_BIT_INV_MASK;
      }
# endif
# if ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
      CanNm_ImmediateNmMsgCount[CANNM_CHANNEL_IDX] = 0u; /* ESCAN00057728 */
# endif
#endif
      break;

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
      /* -------------------- transition to Normal Operation -------------------- */
    case NM_STATE_NORMAL_OPERATION:
# if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#  if ( CANNM_COM_CONTROL_ENABLED == STD_ON )
      if( CanNm_TxControlState[CANNM_CHANNEL_IDX] == MSG_TX_ENABLED )
#  endif
      {
        /* Restart remote Sleep Timer. */
        CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_REMOTE_SLEEP_IND_TIME + (CanNm_TimerCounterType)1u;
        CanNm_RemoteSleepIndState[CANNM_CHANNEL_IDX] = FALSE;
      }
# endif
      if( lastNmState == NM_STATE_READY_SLEEP )
      {
# if ( CANNM_COM_CONTROL_ENABLED == STD_ON )
        if( CanNm_TxControlState[CANNM_CHANNEL_IDX] == MSG_TX_ENABLED )
# endif
        {
          /* CANNM005, CANNM116: Start NM message timer. */
          CanNm_MsgTimer[CANNM_CHANNEL_IDX] = CANNM_CFG_MSG_CYCLE_OFFSET + (CanNm_TimerCounterType)1u; /* ESCAN00060200 */
# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
          /* Message Timeout Timer remains untouched here */ /* ESCAN00054369 */
# endif
        }
      }
      else
      {
# if ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
        /* Check for PDU Position set to PDU_OFF */
        if( CanNm_LConfigPtr->CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF )
        {
          /* CANNM107: Clear the repeat message bit. */
          CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LConfigPtr->CANNM_PDU_CBV_POSITION] &= CANNM_REPEAT_MSG_BIT_INV_MASK;
        }
# endif
      }
      break;
#endif

      /* -------------------- transition to Repeat Message -------------------- */
    default:
      /* Reset the Repeat Message Timer. */
      CanNm_RepeatMsgTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_REPEAT_MESSAGE_TIME + (CanNm_TimerCounterType)1u;
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
      /* Stop Remote Sleep Timer and clear Flag */
      CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX] = (CanNm_TimerCounterType)0u;
      CanNm_RemoteSleepIndState[CANNM_CHANNEL_IDX] = FALSE;
#endif
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
      /* Processing of event: Repeat Message Ind. */
      if( CanNm_RepeatMsgBitIndFlag[CANNM_CHANNEL_IDX] == TRUE )
      {
        CanNm_RepeatMsgBitIndFlag[CANNM_CHANNEL_IDX] = FALSE;
# if ( CANNM_REPEAT_MSG_IND_ENABLED == STD_ON )
        /* CANNM014: Notify NM Interface about Repeat Message Indication */
        Nm_RepeatMessageIndication( CANNM_NMTOSYSTEM_CHANNEL_IND );
# endif
      }
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
# if ( CANNM_COM_CONTROL_ENABLED == STD_ON )
      if( CanNm_TxControlState[CANNM_CHANNEL_IDX] == MSG_TX_ENABLED )
# endif
      {

# if ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
        if( (CanNm_LConfigPtr->CANNM_IMMEDIATE_NM_TRANSMISSIONS > 0u)
          && (CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX] == CANNM_ACTIVE_RESTART) )
        {
          /* Set the message timer to 1 to trigger transmission of the NM message in the same cycle: */
          CanNm_MsgTimer[CANNM_CHANNEL_IDX] = (CanNm_TimerCounterType)1u;
          CanNm_ImmediateNmMsgCount[CANNM_CHANNEL_IDX] = (uint8)(CanNm_LConfigPtr->CANNM_IMMEDIATE_NM_TRANSMISSIONS - 1u);
        }
        else
# endif
        {
          /* CANNM005, CANNM100: Start NM message timer. */
          CanNm_MsgTimer[CANNM_CHANNEL_IDX] = CANNM_CFG_MSG_CYCLE_OFFSET + (CanNm_TimerCounterType)1u; /* ESCAN00060200 */
        }
# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
        /* Message Timeout Timer remains untouched here */ /* ESCAN00054369 */
# endif
      }
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

      /* Additional actions when entering Network Mode */
      if( lastNmState < NM_STATE_READY_SLEEP )
      {

        /* Reset Wait Bus Sleep Timer */
        CanNm_WaitBusSleepTimer[CANNM_CHANNEL_IDX] = (CanNm_TimerCounterType)0u;
        /* CANNM096, CANNM206: Restart the Timeout Time timer whenever Network Mode is entered. */
        CanNm_TimeoutTimer[CANNM_CHANNEL_IDX] = CanNm_LConfigPtr->CANNM_TIMEOUT_TIME + (CanNm_TimerCounterType)1u;
        /* CANNM093, CANNM097: Notify Nm Interface, that the network mode is started. */
        Nm_NetworkMode( CANNM_NMTOSYSTEM_CHANNEL_IND );

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON )
        if( ((boolean)CanNm_LConfigPtr->CANNM_ACTIVE_WAKE_UP_BIT_ENABLED == TRUE)
          && (CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX] == CANNM_ACTIVE_RESTART) )
        {
          if( CanNm_LConfigPtr->CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF )
          {
            /* CANNM408: Set Active Wake-up Bit in CBV */
            CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LConfigPtr->CANNM_PDU_CBV_POSITION] |= CANNM_ACT_WU_BIT_MASK;
          }
        }
#endif

      }

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_RESTART_ENABLED == STD_ON )
      /* If Network Mode has been entered from Prepare Bus-Sleep Mode due to a network request,
      an asynchronous NM message transmission is requested as soon as Network Mode has been entered */
      if( (lastNmState == NM_STATE_PREPARE_BUS_SLEEP) &&
          (CanNm_MsgTimer[CANNM_CHANNEL_IDX] > (CanNm_TimerCounterType)1u) &&
          (CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX] == CANNM_ACTIVE_RESTART) /* ESCAN00064767 */ )
      {
        additionalTransmissionRequired = 1u;
      }
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_RESTART_ENABLED == STD_ON ) */

      /* Reset Restart Flag */
      CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX] = CANNM_NO_RESTART;

      break;
    }

    /* CANNM167: State Change Notification is configurable */
#if ( CANNM_STATE_CHANGE_IND_ENABLED == STD_ON )
    /* CANNM166: Notify Nm Interface that state has changed */
    Nm_StateChangeNotification( CANNM_NMTOSYSTEM_CHANNEL_IND, lastNmState, nextNmState );
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_RESTART_ENABLED == STD_ON )
    if ( additionalTransmissionRequired != 0u )
    {
      /* CANNM122: Request the transmission of the asynchronous NM message in Network Mode. */
      /* Call CanNm_TriggerTransmission after Nm_StateChangeNotification because the user data might have been
       * changed inside the Nm_StateChangeNotification call
       */ /* ESCAN00064796 */
      (void)CanNm_TriggerTransmission( CANNM_CHANNEL_PARA_ONLY ); /* Return value of function is not evaluated. */
    }
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_RESTART_ENABLED == STD_ON ) */
  }
}  /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * CanNm_Init
 **********************************************************************************************************************/
/*! \brief      Initialization of the CAN Network Management (CANNM041)
 *              and its internal state machine
 *              By default the NM starts in the Bus-Sleep Mode.
 *  \param[in]  cannmConfigPtr               Configuration structure for initializing the module
 *  \pre        Interrupts must be disabled
 *  \pre        CANNM142: Initialization after CanIf and before call of any NM service
 *  \context    System Startup
 *  \note       Called by Application (EcuM)
 **********************************************************************************************************************/
FUNC( void, CANNM_CODE ) CanNm_Init( CONSTP2CONST( CanNm_ConfigType, AUTOMATIC, CANNM_PBCFG ) cannmConfigPtr )
{
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#else
  VAR( uint8, AUTOMATIC ) i;
#endif
  P2CONST( CanNm_ConfigType, AUTOMATIC, CANNM_PBCFG ) configPtr;

  if( cannmConfigPtr == NULL_PTR )
  {
    /* Use standard configuration */
    configPtr = &CanNm_Configuration0;
  }
  else
  {
    /* CANNM060: Use selected configuration */
    configPtr = cannmConfigPtr;
  }

  /* Check the magic number */
  if( configPtr->CANNM_MAGIC_NUMBER != CANNM_MAGIC_NUMBER_CHECK )
  {
#if ( CANNM_PROD_ERROR_DETECT == STD_ON ) && ( CANNM_DEM2DET_ENABLED == STD_OFF )
    /* CANNM018, CANNM020: Report initialization failure to DEM */ /* ESCAN00051043 */
    Dem_ReportErrorStatus( CanNm_DemInitFailed, DEM_EVENT_STATUS_FAILED );
#endif

#if ( CANNM_DEV_ERROR_DETECT == STD_ON ) && ( CANNM_DEM2DET_ENABLED == STD_ON )
    /* ESCAN00045764: Report initialization failure to DET */ /* ESCAN00051043 */
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)CANNM_INIT_ID, CANNM_E_INIT_FAILED );
#endif
  }
  else
  {

#if defined ( CANNM_USE_EXTENDED_ASR_VERSION_CHECK )
    /* Check the GENy Generator version */
    if( ( (configPtr->CanNm_GeneratorVersion & 0x00FFFF00) != 
      ( ((uint32)NM_ASRNMCAN_GENTOOL_GENY_MAJOR_VERSION << 16) | ((uint32)NM_ASRNMCAN_GENTOOL_GENY_MINOR_VERSION << 8) ) )
# if ( NM_ASRNMCAN_GENTOOL_GENY_PATCH_VERSION != 0x00u )
      || ( (configPtr->CanNm_GeneratorVersion & 0x000000FF) < (NM_ASRNMCAN_GENTOOL_GENY_PATCH_VERSION) )
# endif
      )
    {
      /*  Call the Vector specific EcuM Error callback */
      EcuM_GeneratorCompatibilityError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID );
    }
    else
#endif
    {

#if ( CANNM_CRC_CHECK == STD_ON )
      if( (configPtr->CanNm_Cfg_PrecompileCRC != CANNM_PRECOMPILE_CRC) || (configPtr->CanNm_Cfg_LinktimeCRC != CanNm_LinktimeCRC) )
      {
        EcuM_GeneratorCompatibilityError( (uint16) CANNM_MODULE_ID, CANNM_INSTANCE_ID );
      }
      else
#endif
      {

#if defined ( CANNM_MULTI_ECU_ENABLED ) || ( CANNM_CONFIG_VARIANT == 3 )
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) || ( CANNM_NODE_ID_ENABLED == STD_ON ) || \
     ( CANNM_PN_FEATURE_ENABLED == STD_ON ) || ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
        /* Save Pointer to postbuild channel configuration */ /* ESCAN00064042 */
        CanNm_PbChConfigPtr = configPtr->CanNm_PbChannelConfigPtr;
# endif
#endif

        /* Initialize each channel. */
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
        /* Local Initialization */
        CanNm_LocalInit();
#else
        /* Initializing channel independent values */
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
        nmMinPnChannel = 0xFFu;
# endif

        for( i=0u; i<CanNm_LConfiguration.CANNM_NUMBER_OF_CHANNELS; i++ )
        {
          /* Initialize only active channel */
          if( (boolean)CanNm_LChannelConfig[i].CANNM_CHANNEL_ACTIVE == TRUE )
          {
            CanNm_LocalInit( (NetworkHandleType)i );
          }
          /* CANNM204: else set NM state to uninitialized */
          else
          {
            CanNm_NmState[i] = NM_STATE_UNINIT;
          }
        }
#endif /* else defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED ) */

      }
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
 *  CanNm_PassiveStartUp
 **********************************************************************************************************************/
/*! \brief      Starts the NM from the Bus Sleep Mode and triggers
 *              a transition to the Network Mode (Repeat Message State)
 *              This service has no effect if the current state is not equal to 
 *              Bus Sleep Mode. In that case NM_E_NOT_EXECUTED is returned
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Start of network management has failed
 *  \return     NM_E_NOT_EXECUTED - Service not executed due to wrong state
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_PassiveStartUp( CANNM_CHANNEL_SYSTEMTYPE_ONLY )
{
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#else
  /* Create channel handle of Nm instance. */
  VAR ( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_PASSIVESTARTUP_ID )
#endif
#if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_PASSIVESTARTUP_ID )
#endif

  /* CANNM128 */
  if( (CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_BUS_SLEEP) ||
      (CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_PREPARE_BUS_SLEEP) /* ESCAN00051912 */ )
  {
    if( CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX] == CANNM_NO_RESTART )
    {
      CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX] = CANNM_PASSIVE_RESTART;
    }
    return NM_E_OK;
  }
  /* CANNM147 */
  else
  {
    return NM_E_NOT_EXECUTED;
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */


#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
/***********************************************************************************************************************
 *  CanNm_NetworkRequest
 **********************************************************************************************************************/
/*! \brief      Request bus-communication
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Requesting bus-communication has failed
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_NetworkRequest( CANNM_CHANNEL_SYSTEMTYPE_ONLY )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_NETWORKREQUEST_ID )
# endif
# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_NETWORKREQUEST_ID )
# endif

  /* CANNM104: Request network */
  CanNm_CommState[CANNM_CHANNEL_IDX] = COMM_NORMAL_OPERATION;
  
  /* Ensure Start-Up (ESCAN00034522, ESCAN00037081) */
  if( (CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX] == CANNM_NO_RESTART)
    && ( (CanNm_NmState[CANNM_CHANNEL_IDX] < NM_STATE_READY_SLEEP)
# if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
    /* CANNM448: Change to Network Mode if Multiple Network Request is set to true */
    || ( ((boolean)CanNm_PnEnabled[CANNM_CHANNEL_IDX] == TRUE) &&
         ((boolean)CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PN_HANDLE_MULTIPLE_NETWORK_REQUEST == TRUE)
       )
# endif
    ) )
  {
    CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX] = CANNM_ACTIVE_RESTART;
  }
  return NM_E_OK;
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */


/***********************************************************************************************************************
 *  CanNm_NetworkRelease
 **********************************************************************************************************************/
/*! \brief      Release bus-communication
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Releasing bus-communication has failed
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_NetworkRelease( CANNM_CHANNEL_SYSTEMTYPE_ONLY )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_NETWORKRELEASE_ID )
# endif
# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_NETWORKRELEASE_ID )
# endif  

  /* CANNM105: Release network */
  CanNm_CommState[CANNM_CHANNEL_IDX] = COMM_READY_SLEEP;
  return NM_E_OK;
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) */


/***********************************************************************************************************************
 *  CanNm_GetState
 **********************************************************************************************************************/
/*! \brief      Return current state and mode of the network management (CANNM091)
 *  \param[out] nmStatePtr                  Pointer where the state of the Network Management shall be copied to
 *  \param[out] nmModePtr                   Pointer where the mode of the Network Management shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Getting the NM state has failed
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_GetState( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( Nm_StateType, AUTOMATIC, CANNM_APPL_VAR ) nmStatePtr, CONSTP2VAR( Nm_ModeType, AUTOMATIC, CANNM_APPL_VAR ) nmModePtr )
{
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_GETSTATE_ID )
#endif
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_GETSTATE_ID )

#if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  if( ( nmStatePtr == NULL_PTR ) || ( nmModePtr == NULL_PTR ) )
  {
    /* CANNM016, CANNM018, CANNM019, CANNM196: Report Null Pointer failure to DET */
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_GETSTATE_ID), CANNM_E_NULL_POINTER );
    return NM_E_NOT_OK;
  }
  else
#endif
  {
    /* Set state */
    *nmStatePtr = CanNm_NmState[CANNM_CHANNEL_IDX];
    /* Set mode respective to the state */
    if(CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_BUS_SLEEP)                     /* Bus Sleep */
    {
      *nmModePtr = NM_MODE_BUS_SLEEP;
    }
    else if(CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_PREPARE_BUS_SLEEP)    /* Prepare Sleep */
    {
      *nmModePtr = NM_MODE_PREPARE_BUS_SLEEP;
    }
    else                                   /* Ready Sleep, Normal Operation, Repeat Message */
    {
      *nmModePtr = NM_MODE_NETWORK;                
    }

    return NM_E_OK;
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */

#if ( CANNM_USER_DATA_ENABLED == STD_ON )  /* CANNM053, CANNM158: User Data Support is configurable */
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if ( CANNM_COM_USER_DATA_ENABLED == STD_OFF )  /* ESCAN00037848 */
/***********************************************************************************************************************
 *  CanNm_SetUserData
 **********************************************************************************************************************/
/*! \brief      Set user data for NM messages transmitted next on the bus (CANNM015, CANNM159)
 *  \param[in]  nmUserDataPtr               Pointer to User data for the next transmitted NM message
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Setting of user data has failed
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_SetUserData( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2CONST( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmUserDataPtr )
{
  VAR( uint8, AUTOMATIC ) i;
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#  else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_SETUSERDATA_ID )
#  endif
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_SETUSERDATA_ID )

#  if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  if( nmUserDataPtr == NULL_PTR )
  {
    /* CANNM016, CANNM018, CANNM019, CANNM196: Report Null Pointer failure to DET */
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_SETUSERDATA_ID), CANNM_E_NULL_POINTER );
    return NM_E_NOT_OK;
  }
  else
#  endif
  {
    CANNM_ENTER_CRITICAL(CANNM_EXCLUSIVE_AREA_2);
    for( i=CanNm_UserDataPosition[CANNM_CHANNEL_IDX]; i<CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_LENGTH; i++ )
    {
      {
        CanNm_TxMessageData[CANNM_CHANNEL_IDX][i] = nmUserDataPtr[i-CanNm_UserDataPosition[CANNM_CHANNEL_IDX]];
      }
    }
    CANNM_LEAVE_CRITICAL(CANNM_EXCLUSIVE_AREA_2);
    return NM_E_OK;
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#  endif /* ( CANNM_COM_USER_DATA_ENABLED == STD_OFF ) */
# endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) */


/***********************************************************************************************************************
 *  CanNm_GetUserData
 **********************************************************************************************************************/
/*! \brief      Get user data out of the last NM messages received from the bus (CANNM031, CANNM160)
 *  \param[in]  nmUserDataPtr               Pointer where user data out of the last received NM message shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Getting of user data has failed
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_GetUserData( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmUserDataPtr )
{
  VAR( uint8, AUTOMATIC ) i;
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_GETUSERDATA_ID )
# endif
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_GETUSERDATA_ID )

# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  if( nmUserDataPtr == NULL_PTR )
  {
    /* CANNM016, CANNM018, CANNM019, CANNM196: Report Null Pointer failure to DET */
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_GETUSERDATA_ID), CANNM_E_NULL_POINTER );
    return NM_E_NOT_OK;
  }
  else
# endif
  {
    CANNM_ENTER_CRITICAL(CANNM_EXCLUSIVE_AREA_5);
    for( i=0u; i<CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_USER_DATA_LENGTH; i++ )
    {
      nmUserDataPtr[i] = CanNm_RxMessageData[CANNM_CHANNEL_IDX][i+CanNm_UserDataPosition[CANNM_CHANNEL_IDX]];
    }
    CANNM_LEAVE_CRITICAL(CANNM_EXCLUSIVE_AREA_5);
    return NM_E_OK;
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif  /* ( CANNM_USER_DATA_ENABLED == STD_ON ) */


#if ( CANNM_NODE_ID_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  CanNm_GetNodeIdentifier
 **********************************************************************************************************************/
/*! \brief      Get node identifier of the last received NM message (CANNM132)
 *  \param[out] nmNodeIdPtr                 Pointer where node identifier from the last received NM message shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Getting of node identifier has failed
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_GetNodeIdentifier( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmNodeIdPtr )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_GETNODEIDENTIFIER_ID )
# endif
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_GETNODEIDENTIFIER_ID )

# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  if( nmNodeIdPtr == NULL_PTR )
  {
    /* CANNM016, CANNM018, CANNM019, CANNM196: Report Null Pointer failure to DET */
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_GETNODEIDENTIFIER_ID), CANNM_E_NULL_POINTER );
    return NM_E_NOT_OK;
  }
  else
# endif
  {
    /* Check for PDU Position set to STD_OFF */
    if( CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_NID_POSITION == CANNM_PDU_OFF )
    {
      return NM_E_NOT_OK;
    }
    else
    {
      *nmNodeIdPtr = CanNm_RxMessageData[CANNM_CHANNEL_IDX][CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_NID_POSITION];
      return NM_E_OK;
    }
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */


/***********************************************************************************************************************
 *  CanNm_GetLocalNodeIdentifier
 **********************************************************************************************************************/
/*! \brief      Get node identifier configured for the local node (CANNM133)
 *  \param[out] nmNodeIdPtr                 Pointer where node identifier of the local node shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Getting of local node identifier has failed
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_GetLocalNodeIdentifier( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmNodeIdPtr )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_GETLOCALNODEIDENTIFIER_ID )
# endif
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_GETLOCALNODEIDENTIFIER_ID )

# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  if( nmNodeIdPtr == NULL_PTR )
  {
    /* CANNM016, CANNM018, CANNM019, CANNM196: Report Null Pointer failure to DET */
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_GETLOCALNODEIDENTIFIER_ID), CANNM_E_NULL_POINTER );
    return NM_E_NOT_OK;
  }
  else
# endif
  {
    /* Read Node Id from Configuration */
    *nmNodeIdPtr = CANNM_CFG_NODE_ID;
    return NM_E_OK;
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ( CANNM_NODE_ID_ENABLED == STD_ON ) */


#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON )  /* CANNM136: Node Detection is configurable */
/***********************************************************************************************************************
 *  CanNm_RepeatMessageRequest
 **********************************************************************************************************************/
/*! \brief      Request state change to Repeat Message State
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Repeat Message Request has failed
 *  \return     NM_E_NOT_EXECUTED - Service not executed due to wrong state
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_RepeatMessageRequest( CANNM_CHANNEL_SYSTEMTYPE_ONLY )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_REPEATMESSAGEREQUEST_ID )
# endif
# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_REPEATMESSAGEREQUEST_ID )
# endif

  /* CANNM137: Repeat Message Request only in Ready Sleep and Normal Operation */
  if( ( CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_READY_SLEEP ) || ( CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_NORMAL_OPERATION ) )
  {
    /* CANNM112, CANNM120: Request Transition to Repeat Message State */
    CanNm_RepeatMsgReqFlag[CANNM_CHANNEL_IDX] = TRUE;
    return NM_E_OK;
  }
  else
  {
    return NM_E_NOT_EXECUTED;
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON ) */


#if ( ( CANNM_NODE_ID_ENABLED == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) )  /* CANNM139 Get PDU Data is configurable */
/***********************************************************************************************************************
 *  CanNm_GetPduData
 **********************************************************************************************************************/
/*! \brief      Get the whole PDU data out of the last NM message received from the bus (CANNM138)
 *  \param[out] nmPduDataPtr                Pointer where PDU Data out of the most recently received NM message shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Getting the PDU data has failed
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_GetPduData( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmPduDataPtr )
{
  VAR( uint8, AUTOMATIC ) i;
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_GETPDUDATA_ID )
# endif
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_GETPDUDATA_ID )

# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  if( nmPduDataPtr == NULL_PTR )
  {
    /* CANNM016, CANNM018, CANNM019, CANNM196: Report Null Pointer failure to DET */
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_GETPDUDATA_ID), CANNM_E_NULL_POINTER );
    return NM_E_NOT_OK;
  }
  else
# endif
  {
    CANNM_ENTER_CRITICAL(CANNM_EXCLUSIVE_AREA_5);
    /* Copy Data from Buffer */
    for( i=0u; i<CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_LENGTH; i++ )
    {
      nmPduDataPtr[i] = CanNm_RxMessageData[CANNM_CHANNEL_IDX][i];
    }
    CANNM_LEAVE_CRITICAL(CANNM_EXCLUSIVE_AREA_5);
    return NM_E_OK;
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ( CANNM_NODE_ID_ENABLED == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) */


#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
# if ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )  /* CANNM185: Bus Synchronization is configurable */
/***********************************************************************************************************************
 *  CanNm_RequestBusSynchronization
 **********************************************************************************************************************/
/*! \brief      Request bus synchronization (CANNM130: transmission of an asynchronous NM message)
                to support coordination of coupled networks (CANNM184)
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Requesting bus synchronization has failed
 *  \return     NM_E_NOT_EXECUTED - Service not executed due to wrong state
 *  \pre        NM is initialized
 *  \context    Function could be called from task level only
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_RequestBusSynchronization( CANNM_CHANNEL_SYSTEMTYPE_ONLY )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_REQUESTBUSSYNC_ID )
# endif
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_REQUESTBUSSYNC_ID )

  /* CANNM187: Bus synchronization may only be requested in Network Mode. */
  if( ( CanNm_NmState[CANNM_CHANNEL_IDX] != NM_STATE_BUS_SLEEP ) && ( CanNm_NmState[CANNM_CHANNEL_IDX] != NM_STATE_PREPARE_BUS_SLEEP )
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
    /* CANNM181: and if PDU transmission ability is not disabled */
        && ( CanNm_TxControlState[CANNM_CHANNEL_IDX] == MSG_TX_ENABLED ) 
# endif
        )
  {
    /* CANNM186: Trigger Transmission */
    return CanNm_TriggerTransmission( CANNM_CHANNEL_PARA_ONLY );
  }
  else
  {
    return NM_E_NOT_EXECUTED;
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
# endif /* ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON ) */
#endif


#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  CanNm_CheckRemoteSleepIndication
 **********************************************************************************************************************/
/*! \brief      Check if remote sleep was indicated or not (CANNM153)
 *  \param[out] nmRemoteSleepIndPtr                Pointer where PDU Data out of the most recently received NM message shall be copied to
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Checking remote sleep indication has failed
 *  \return     NM_E_NOT_EXECUTED - Service not executed due to wrong state
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_CheckRemoteSleepIndication( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONSTP2VAR( boolean, AUTOMATIC, CANNM_APPL_VAR ) nmRemoteSleepIndPtr )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_CHECKREMOTESLEEPIND_ID )
# endif
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_CHECKREMOTESLEEPIND_ID )

# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  if( nmRemoteSleepIndPtr == NULL_PTR )
  {
    /* CANNM016, CANNM018, CANNM019, CANNM196: Report Null Pointer failure to DET */
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_CHECKREMOTESLEEPIND_ID), CANNM_E_NULL_POINTER );
    return NM_E_NOT_OK;
  }
  else
# endif
  {
    /* CANNM154: Check Remote Sleep Indication may only be requested in Ready Sleep State and during Normal Operation. */
# if defined ( CANNM_REMOTE_SLEEP_EXTENSION )
    /* + additionally in Repeat Message */
    if( (CanNm_NmState[CANNM_CHANNEL_IDX] != NM_STATE_BUS_SLEEP) && (CanNm_NmState[CANNM_CHANNEL_IDX] != NM_STATE_PREPARE_BUS_SLEEP) )
#else
    if( (CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_READY_SLEEP) || (CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_NORMAL_OPERATION) )
#endif
    {
      *nmRemoteSleepIndPtr = CanNm_RemoteSleepIndState[CANNM_CHANNEL_IDX];
      return NM_E_OK;
    }
    else
    {
      return NM_E_NOT_EXECUTED;
    }
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) */


#if ( CANNM_VERSION_INFO_API == STD_ON )
/***********************************************************************************************************************
 *  CanNm_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief      Return Version Info of this Module
 *  \param[out] versioninfo                Pointer to store the Version Information to
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from Application
 **********************************************************************************************************************/
FUNC( void, CANNM_CODE ) CanNm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CANNM_APPL_VAR ) versioninfo)
{
  if( versioninfo != NULL_PTR )
  {
    versioninfo->vendorID = (uint16)CANNM_VENDOR_ID;
    versioninfo->moduleID = (uint8)CANNM_MODULE_ID;
    versioninfo->instanceID = CANNM_INSTANCE_ID;
    versioninfo->sw_major_version = (uint8)CANNM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)CANNM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)CANNM_SW_PATCH_VERSION;
  }
# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  /* [BR:001]: Common Handling of Get Version API */
  else
  {
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_GETVERSIONINFO_ID), CANNM_E_NULL_POINTER );
  }
# endif
}
#endif /* ( CANNM_VERSION_INFO_API == STD_ON ) */


#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )  /* CANNM168: Communication Control is configurable */
/***********************************************************************************************************************
 *  CanNm_EnableCommunication
 **********************************************************************************************************************/
/*! \brief      Enable NM message transmission control status (CANNM176)
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Enable NM Message transmission control status has failed
 *  \return     NM_E_NOT_EXECUTED - Service not executed due to wrong state
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_EnableCommunication( CANNM_CHANNEL_SYSTEMTYPE_ONLY )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_ENABLENMCOMMUNICATION_ID )
# endif
# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_ENABLENMCOMMUNICATION_ID )
# endif

  /* CANNM177: Enable NM PDU transmission ability only if disabled */
  if( CanNm_TxControlState[CANNM_CHANNEL_IDX] == MSG_TX_DISABLED )
  {
    /* Enable NM PDU transmission ability */
    CanNm_TxControlStateRequest[CANNM_CHANNEL_IDX] = MSG_TX_ENABLED;
    return NM_E_OK;
  }
  else
  {
    return NM_E_NOT_EXECUTED;
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */


/***********************************************************************************************************************
 *  CanNm_DisableCommunication
 **********************************************************************************************************************/
/*! \brief      Disable NM message transmission control status (CANNM170)
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Disable NM Message transmission control status has failed
 *  \return     NM_E_NOT_EXECUTED - Service not executed due to wrong state
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_DisableCommunication( CANNM_CHANNEL_SYSTEMTYPE_ONLY )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_DISABLENMCOMMUNICATION_ID )
# endif
# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_DISABLENMCOMMUNICATION_ID )
# endif

  /* CANNM172: Disable Nm PDU transmission ability in Network Mode */
  if( CanNm_NmState[CANNM_CHANNEL_IDX] > NM_STATE_PREPARE_BUS_SLEEP )
  {
    CanNm_TxControlStateRequest[CANNM_CHANNEL_IDX] = MSG_TX_DISABLED;
    return NM_E_OK;
  }
  else
  {
    return NM_E_NOT_EXECUTED;
  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON ) */


/***********************************************************************************************************************
 *  CanNm_InitMemory
 **********************************************************************************************************************/
/*! \brief      Initialize Memory, so that expected start values are set
 *  \pre        Interrupts are disabled
 *  \context    System startup
 *  \note       Called from Application
 *  \note       Vector Extension [BR:011]
 **********************************************************************************************************************/
FUNC( void, CANNM_CODE ) CanNm_InitMemory( void )
{
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CanNm_NmState[0] = NM_STATE_UNINIT;
#else
  VAR( uint8, AUTOMATIC ) i;
  for( i=0u; i<CanNm_LConfiguration.CANNM_NUMBER_OF_CHANNELS; i++ )
  {
    CanNm_NmState[i] = NM_STATE_UNINIT;
  }
#endif
}


#if defined ( CANNM_ENABLE_COORD_SYNC_SUPPORT )
/***********************************************************************************************************************
 *  CanNm_SetCoordBits
 **********************************************************************************************************************/
/*! \brief      Set Coordination Bits in the Control Bit Vector
 *  \param[in]  nmCoordBits             Coordination Bits
 *  \return     NM_E_OK - No error
 *  \return     NM_E_NOT_OK - Setting coordination bits has failed
 *  \pre        NM is initialized
 *  \context    Function could be called from task level only
 *  \note       Called from NM Interface
 **********************************************************************************************************************/
FUNC( Nm_ReturnType, CANNM_CODE ) CanNm_SetCoordBits( CANNM_CHANNEL_SYSTEMTYPE_FIRST  CONST( uint8, AUTOMATIC ) nmCoordBits )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM_RET( CANNM_SETCOORDINATORBITS_ID )
# endif
# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT_RET( CANNM_SETCOORDINATORBITS_ID )
# endif

  /* Set Coordination Bits */
  if( CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF )
  {
    CANNM_ENTER_CRITICAL(CANNM_EXCLUSIVE_AREA_3);
    CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION] =
      (uint8)( (CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION] & (uint8)NM_COORD_BIT_INV_MASK) | (nmCoordBits & (uint8)NM_COORD_BIT_MASK) );
    CANNM_LEAVE_CRITICAL(CANNM_EXCLUSIVE_AREA_3); /* ESCAN00050304 */
  }
  return NM_E_OK;

}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif



#if defined( CANNM_ENABLE_GET_CONTEXT ) || \
  (defined( VGEN_ENABLE_MDWRAP ) && defined( VQNX_ENABLE_CONTEXT_SWITCH ))
/***********************************************************************************************************************
 *  CanNm_GetModuleContext
 **********************************************************************************************************************/
/*! \brief      Get all internal variables (module context)
 *  \param[in]  pContext                Pointer where the module context shall be copied to
 *  \pre        NM is initialized
 *  \context    Function could be called from task level only
 *  \note       Called from Application
 **********************************************************************************************************************/
FUNC( void, CANNM_CODE ) CanNm_GetModuleContext( P2VAR(CanNm_ModuleContextStructType, AUTOMATIC, CANNM_APPL_VAR) pContext )
{

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  VAR( NetworkHandleType, AUTOMATIC ) channel;
# endif

# if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED ) || defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED ) \
  || defined ( CANNM_PN_CALC_FEATURE_ENABLED )
  VAR ( uint8, AUTOMATIC ) i;
# endif
# if defined ( CANNM_PN_CALC_FEATURE_ENABLED )
  VAR ( uint8, AUTOMATIC ) j;
# endif

  /* Save Magic Number */
  pContext->canNmMagicNumber = (((uint32)NM_ASRNMCAN_VERSION)<<8)+NM_ASRNMCAN_RELEASE_VERSION;

  /* Save global context */
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  for( i=0u; i<CanNm_LConfiguration.CANNM_PN_INFO_LENGTH; i++ )
  {
    pContext->PnClusterReq[i] = CanNm_PnClusterReq[i];
    pContext->PnClusterReqNew[i] = CanNm_PnClusterReqNew[i];
    for( j=0u; j<8u; j++ )
    {
      pContext->PnClusterResetTimer[i][j] = CanNm_PnClusterResetTimer[i][j];
    }
  }
# endif

  /* Save channel-specific context */
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  for( channel=0u; channel<CanNm_LConfiguration.CANNM_NUMBER_OF_CHANNELS; channel++ )
# endif
  {

    pContext->TimeoutTimer[CANNM_CHANNEL_IDX] = CanNm_TimeoutTimer[CANNM_CHANNEL_IDX];
    pContext->WaitBusSleepTimer[CANNM_CHANNEL_IDX] = CanNm_WaitBusSleepTimer[CANNM_CHANNEL_IDX];
    pContext->RepeatMsgTimer[CANNM_CHANNEL_IDX] = CanNm_RepeatMsgTimer[CANNM_CHANNEL_IDX];

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
    pContext->MsgTimer[CANNM_CHANNEL_IDX] = CanNm_MsgTimer[CANNM_CHANNEL_IDX];
#  if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
    pContext->MsgTimeoutTimer[CANNM_CHANNEL_IDX] = CanNm_MsgTimeoutTimer[CANNM_CHANNEL_IDX];
#  endif
# endif

# if (CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON)
    for( i=0u; i<CanNm_LConfiguration.CANNM_PN_INFO_LENGTH; i++ )
    {
      pContext->PnClusterReqExt[CANNM_CHANNEL_IDX][i] = CanNm_PnClusterReqExt[CANNM_CHANNEL_IDX][i];
      pContext->PnClusterReqExtNew[CANNM_CHANNEL_IDX][i] = CanNm_PnClusterReqExtNew[CANNM_CHANNEL_IDX][i];
      for( j=0u; j<8u; j++ )
      {
        pContext->PnClusterResetTimerExt[CANNM_CHANNEL_IDX][i][j] = CanNm_PnClusterResetTimerExt[CANNM_CHANNEL_IDX][i][j];
      }
    }
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
    pContext->RemoteSleepTimer[CANNM_CHANNEL_IDX] = CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX];
    pContext->RemoteSleepIndState[CANNM_CHANNEL_IDX] = CanNm_RemoteSleepIndState[CANNM_CHANNEL_IDX];
# endif

    pContext->NmState[CANNM_CHANNEL_IDX] = (uint8)CanNm_NmState[CANNM_CHANNEL_IDX];
    pContext->NetworkRestartFlag[CANNM_CHANNEL_IDX] = CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX];
    pContext->MsgIndicationFlag[CANNM_CHANNEL_IDX] = CanNm_MsgIndicationFlag[CANNM_CHANNEL_IDX];

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    pContext->CommState[CANNM_CHANNEL_IDX] = CanNm_CommState[CANNM_CHANNEL_IDX];
    pContext->MsgConfirmationFlag[CANNM_CHANNEL_IDX] = CanNm_MsgConfirmationFlag[CANNM_CHANNEL_IDX];
# endif

# if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED ) || defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED )
    for( i=0u; i<CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_LENGTH; i++ )
    {
#  if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED )
      pContext->TxMessageData[CANNM_CHANNEL_IDX][i] = CanNm_TxMessageData[CANNM_CHANNEL_IDX][i];
#  endif
#  if defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED )
      pContext->RxMessageData[CANNM_CHANNEL_IDX][i] = CanNm_RxMessageData[CANNM_CHANNEL_IDX][i];
#  endif
    }
# endif

# if ( CANNM_USER_DATA_ENABLED == STD_ON ) || ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
    pContext->UserDataPosition[CANNM_CHANNEL_IDX] = CanNm_UserDataPosition[CANNM_CHANNEL_IDX];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
    pContext->RepeatMsgBitIndFlag[CANNM_CHANNEL_IDX] = CanNm_RepeatMsgBitIndFlag[CANNM_CHANNEL_IDX];
    pContext->RepeatMsgReqFlag[CANNM_CHANNEL_IDX] = CanNm_RepeatMsgReqFlag[CANNM_CHANNEL_IDX];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
    pContext->TxControlState[CANNM_CHANNEL_IDX] = CanNm_TxControlState[CANNM_CHANNEL_IDX];
    pContext->TxControlStateRequest[CANNM_CHANNEL_IDX] = CanNm_TxControlStateRequest[CANNM_CHANNEL_IDX];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
    pContext->ImmediateNmMsgCount[CANNM_CHANNEL_IDX] = CanNm_ImmediateNmMsgCount[CANNM_CHANNEL_IDX];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
    pContext->MsgRequest[CANNM_CHANNEL_IDX] = CanNm_MsgRequest[CANNM_CHANNEL_IDX];
#  endif
# endif


# if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
    pContext->PnMessageFilterEnabled[CANNM_CHANNEL_IDX] = (uint8)CanNm_PnMessageFilterEnabled[CANNM_CHANNEL_IDX];
# endif
  }
}
#endif

#if defined( CANNM_ENABLE_SET_CONTEXT ) || \
  (defined( VGEN_ENABLE_QWRAP ) && defined( VQNX_ENABLE_CONTEXT_SWITCH ))
/***********************************************************************************************************************
 *  CanNm_SetModuleContext
 **********************************************************************************************************************/
/*! \brief      Set all internal variables (module context)
 *  \param[in]  pContext                Pointer where the module context shall be copied from
 *  \return     NM_E_OK     - Context set successfully
 *  \return     NM_E_NOT_OK - Magic number check failed, context not set
 *  \pre        NM is initialized
 *  \context    Function could be called from task level only
 *  \note       Called from Application
 **********************************************************************************************************************/
/* PRQA S 3673 1 */ /* MD_CanNm_3673 */
FUNC( Nm_ReturnType, CANNM_CODE) CanNm_SetModuleContext( P2VAR(CanNm_ModuleContextStructType, AUTOMATIC, CANNM_APPL_VAR) pContext )
{

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  VAR( NetworkHandleType, AUTOMATIC ) channel;
# endif

# if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED ) || defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED ) \
  || defined ( CANNM_PN_CALC_FEATURE_ENABLED )
  VAR ( uint8, AUTOMATIC ) i;
# endif
# if defined ( CANNM_PN_CALC_FEATURE_ENABLED )
  VAR ( uint8, AUTOMATIC ) j;
# endif

  VAR( Nm_ReturnType, AUTOMATIC ) retVal = NM_E_NOT_OK;

  /* Check Magic Number */
  if( pContext->canNmMagicNumber == ((((uint32)NM_ASRNMCAN_VERSION)<<8)+NM_ASRNMCAN_RELEASE_VERSION) )
  {
    retVal = NM_E_OK;

  /* Save global context */
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
    for( i=0u; i<CanNm_LConfiguration.CANNM_PN_INFO_LENGTH; i++ )
    {
      CanNm_PnClusterReq[i] = pContext->PnClusterReq[i];
      CanNm_PnClusterReqNew[i] = pContext->PnClusterReqNew[i];
      for( j=0u; j<8u; j++ )
      {
        CanNm_PnClusterResetTimer[i][j] = pContext->PnClusterResetTimer[i][j];
      }
    }
# endif

    /* Save channel-specific context */
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
    for( channel=0u; channel<CanNm_LConfiguration.CANNM_NUMBER_OF_CHANNELS; channel++ )
# endif
    {

      CanNm_TimeoutTimer[CANNM_CHANNEL_IDX] = pContext->TimeoutTimer[CANNM_CHANNEL_IDX];
      CanNm_WaitBusSleepTimer[CANNM_CHANNEL_IDX] = pContext->WaitBusSleepTimer[CANNM_CHANNEL_IDX];
      CanNm_RepeatMsgTimer[CANNM_CHANNEL_IDX] = pContext->RepeatMsgTimer[CANNM_CHANNEL_IDX];

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
      CanNm_MsgTimer[CANNM_CHANNEL_IDX] = pContext->MsgTimer[CANNM_CHANNEL_IDX];
#  if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
      CanNm_MsgTimeoutTimer[CANNM_CHANNEL_IDX] = pContext->MsgTimeoutTimer[CANNM_CHANNEL_IDX];
#  endif
# endif

# if (CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON)
      for( i=0u; i<CanNm_LConfiguration.CANNM_PN_INFO_LENGTH; i++ )
      {
        CanNm_PnClusterReqExt[CANNM_CHANNEL_IDX][i] = pContext->PnClusterReqExt[CANNM_CHANNEL_IDX][i];
        CanNm_PnClusterReqExtNew[CANNM_CHANNEL_IDX][i] = pContext->PnClusterReqExtNew[CANNM_CHANNEL_IDX][i];
        for( j=0u; j<8u; j++ )
        {
          CanNm_PnClusterResetTimerExt[CANNM_CHANNEL_IDX][i][j] = pContext->PnClusterResetTimerExt[CANNM_CHANNEL_IDX][i][j];
        }
      }
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
      CanNm_RemoteSleepTimer[CANNM_CHANNEL_IDX] = pContext->RemoteSleepTimer[CANNM_CHANNEL_IDX];
      CanNm_RemoteSleepIndState[CANNM_CHANNEL_IDX] = pContext->RemoteSleepIndState[CANNM_CHANNEL_IDX];
# endif

      CanNm_NmState[CANNM_CHANNEL_IDX] = (Nm_StateType)pContext->NmState[CANNM_CHANNEL_IDX];
      CanNm_NetworkRestartFlag[CANNM_CHANNEL_IDX] = pContext->NetworkRestartFlag[CANNM_CHANNEL_IDX];
      CanNm_MsgIndicationFlag[CANNM_CHANNEL_IDX] = pContext->MsgIndicationFlag[CANNM_CHANNEL_IDX];

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
      CanNm_CommState[CANNM_CHANNEL_IDX] = pContext->CommState[CANNM_CHANNEL_IDX];
      CanNm_MsgConfirmationFlag[CANNM_CHANNEL_IDX] = pContext->MsgConfirmationFlag[CANNM_CHANNEL_IDX];
# endif

# if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED ) || defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED )
      for( i=0u; i<CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_LENGTH; i++ )
      {
#  if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED )
        CanNm_TxMessageData[CANNM_CHANNEL_IDX][i] = pContext->TxMessageData[CANNM_CHANNEL_IDX][i];
#  endif
#  if defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED )
        CanNm_RxMessageData[CANNM_CHANNEL_IDX][i] = pContext->RxMessageData[CANNM_CHANNEL_IDX][i];
#  endif
      }
# endif

# if ( CANNM_USER_DATA_ENABLED == STD_ON ) || ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
      CanNm_UserDataPosition[CANNM_CHANNEL_IDX] = pContext->UserDataPosition[CANNM_CHANNEL_IDX];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
      CanNm_RepeatMsgBitIndFlag[CANNM_CHANNEL_IDX] = pContext->RepeatMsgBitIndFlag[CANNM_CHANNEL_IDX];
      CanNm_RepeatMsgReqFlag[CANNM_CHANNEL_IDX] = pContext->RepeatMsgReqFlag[CANNM_CHANNEL_IDX];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
      CanNm_TxControlState[CANNM_CHANNEL_IDX] = pContext->TxControlState[CANNM_CHANNEL_IDX];
      CanNm_TxControlStateRequest[CANNM_CHANNEL_IDX] = pContext->TxControlStateRequest[CANNM_CHANNEL_IDX];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
      CanNm_ImmediateNmMsgCount[CANNM_CHANNEL_IDX] = pContext->ImmediateNmMsgCount[CANNM_CHANNEL_IDX];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
    CanNm_MsgRequest[CANNM_CHANNEL_IDX] = pContext->MsgRequest[CANNM_CHANNEL_IDX];
#  endif
# endif


# if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
      CanNm_PnMessageFilterEnabled[CANNM_CHANNEL_IDX] = (boolean)pContext->PnMessageFilterEnabled[CANNM_CHANNEL_IDX];
# endif
    }
  }

  return retVal;
}
#endif


/***********************************************************************************************************************
 *  CanNm_RxIndication
 **********************************************************************************************************************/
/*! \brief      This function is called by the CAN Interface after a CAN L-PDU has been received (CANNM035)
 *  \param[in]  canNmRxPduId             ID of CAN NM PDU that has been received
 *  \param[in]  PduInfoPtr               Pointer to a PduInfoType containing the received CAN NM SDU and its length
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from data link layer
 **********************************************************************************************************************/
FUNC( void, CANNM_CODE ) CanNm_RxIndication( VAR( PduIdType, AUTOMATIC ) canNmRxPduId,
                                             P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr )
{
#if ( ( CANNM_NODE_ID_ENABLED == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) ) \
  || defined ( CANNM_ENABLE_COORD_SYNC_SUPPORT ) || ( CANNM_PN_FEATURE_ENABLED == STD_ON ) \
  || ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
  /* local variables */
  VAR( uint8, AUTOMATIC ) i;
#endif

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
  VAR( boolean, AUTOMATIC ) msgRelevant;
  VAR( uint8, AUTOMATIC ) reqCluster;
#endif

#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  if( CANNM_CHANNEL_IDX == canNmRxPduId )
#else
  /* Create Channel Handle */
  VAR( NetworkHandleType, AUTOMATIC ) channel = (NetworkHandleType)canNmRxPduId;
  /* Check channel parameter. */
  if( channel < (NetworkHandleType)CanNm_LConfiguration.CANNM_NUMBER_OF_CHANNELS )
#endif
  {
    /* Check whether CAN NM is initialized. */
    if( CanNm_NmState[CANNM_CHANNEL_IDX] != NM_STATE_UNINIT )
    {
#if ( CANNM_DEV_ERROR_DETECT == STD_ON )
      if( (PduInfoPtr == NULL_PTR) || (PduInfoPtr->SduDataPtr == NULL_PTR) )
      {
        /* CANNM016, CANNM018, CANNM019, CANNM196: Report Null Pointer failure to DET */
        Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_RXINDICATION_ID), CANNM_E_NULL_POINTER );
      }
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
      /* RangeConfig DLC Check has been adjusted by CanNm */ /* ESCAN00054839 */
      else if( PduInfoPtr->SduLength != CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_LENGTH )
      {
        Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_RXINDICATION_ID), CANNM_E_RXINDICATION_DLC_ERROR );
      }
# endif
      else
#endif
      {

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )

        if( (boolean)CanNm_PnEnabled[CANNM_CHANNEL_IDX] == TRUE /* ESCAN00057816 */ )
        {
          msgRelevant = FALSE;
          if( (CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF)
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
              /* No need to check RX PDU Length, fixed length assumed */ /* ESCAN00054839 */
# else
              /* Check whether CBV Byte can be found inside RX PDU buffer */ /* ESCAN00054839 */
              && (PduInfoPtr->SduLength > CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION)
# endif
            )
          {

            if( (((uint8)(CANNM_RXINDICATION_PARAM_DATAPTR[CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION]) & CANNM_CRI_BIT_MASK) != 0u)
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
                /* No need to check RX PDU Length, fixed length assumed */ /* ESCAN00056701 */
# else
                /* Check whether first PN Info byte can be found inside RX PDU buffer */ /* ESCAN00056701 */
                && (PduInfoPtr->SduLength > CanNm_LConfiguration.CANNM_PN_INFO_OFFSET)
# endif
              )
            {
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
              /* No need to check RX PDU Length, fixed length assumed */ /* ESCAN00056701 */
# else
              /* Determine right-hand operand for the for loop condition */ /* ESCAN00056701 */
              VAR( uint8, AUTOMATIC ) adjustedInfoLength;
              
              if ((uint8)(PduInfoPtr->SduLength) < (uint8)(CanNm_LConfiguration.CANNM_PN_INFO_OFFSET + CanNm_LConfiguration.CANNM_PN_INFO_LENGTH))
              {
                adjustedInfoLength = (uint8)(PduInfoPtr->SduLength - CanNm_LConfiguration.CANNM_PN_INFO_OFFSET);
              }
              else
              {
                /* Received Pdu is long enough so that the PN INFO Bytes are fully included */
                adjustedInfoLength = CanNm_LConfiguration.CANNM_PN_INFO_LENGTH;
              }
# endif
              /* PN is enabled, PN bit is true => apply filter algorithm: */

              /* copy the requests and apply the PN filter mask: */
              CANNM_ENTER_CRITICAL(CANNM_EXCLUSIVE_AREA_0);
              for( i=0u; i<CANNM_RX_IND_ADJUSTED_INFO_LENGTH; i++ ) /* ESCAN00056701 */
              {
                reqCluster = (uint8)(CANNM_RXINDICATION_PARAM_DATAPTR[i+CanNm_LConfiguration.CANNM_PN_INFO_OFFSET] & CanNm_PnFilterMask[i]);
                /* save current requests: */
                if( reqCluster != 0u ) /* PRQA S 0715 */ /* MD_MSR_1.1 */
                { /* PRQA S 0715 */ /* MD_MSR_1.1 */
                  msgRelevant = TRUE;
# if defined ( CANNM_PN_CALC_FEATURE_ENABLED )
#  if (CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON)
                  if( (boolean)CanNm_LConfiguration.CANNM_PN_EIRA_CALC_ENABLED == TRUE ) /* PRQA S 0715 */ /* MD_MSR_1.1 */
                  {
                    CanNm_PnClusterReqNew[i] |= reqCluster;
                  }
#  endif
#  if (CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON)
                  if( (boolean)CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PN_ERA_CALC_ENABLED == TRUE ) /* PRQA S 0715 */ /* MD_MSR_1.1 */
                  {
                    CanNm_PnClusterReqExtNew[CANNM_CHANNEL_IDX][i] |= reqCluster;
                  }
#  endif
# else
                  break;
# endif
                }
              }
              CANNM_LEAVE_CRITICAL(CANNM_EXCLUSIVE_AREA_0);

            }
          } /* if ( (CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF) && ... ) */
        }
        else
        {
          msgRelevant = TRUE;
        }

        if( (msgRelevant == TRUE) || ((boolean)CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_ALL_MESSAGES_KEEP_AWAKE == TRUE) ||
            (CanNm_PnMessageFilterEnabled[CANNM_CHANNEL_IDX] == FALSE) /* ESCAN00057816 */ )
#endif
        {

#if ( ( CANNM_NODE_ID_ENABLED == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) \
          || ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON ) )
          /* Copy the NM message data to the Rx Message Data Buffer. */
          CANNM_ENTER_CRITICAL(CANNM_EXCLUSIVE_AREA_4);
          for( i=0u; i<CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_LENGTH; i++ )
          {
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
            /* No need to check RX PDU Length, fixed length assumed */ /* ESCAN00054839 */
# else
            /* PDU received with PduInfoPtr->SduLength < CANNM_PDU_LENGTH */
            if ( i >= PduInfoPtr->SduLength)
            {
              /* Set byte that has not been received to zero */
              CanNm_RxMessageData[CANNM_CHANNEL_IDX][i] = 0u;
            }
            else
# endif
            {
              /* Copy received byte */
              CanNm_RxMessageData[CANNM_CHANNEL_IDX][i] = (uint8)(CANNM_RXINDICATION_PARAM_DATAPTR[i]);
            }
          }
          CANNM_LEAVE_CRITICAL(CANNM_EXCLUSIVE_AREA_4);
#endif

#if defined ( CANNM_ENABLE_COORD_SYNC_SUPPORT ) || (( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON ))
          /* Check PDU Position not set to PDU_OFF */
          if( (CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF)
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
              /* No need to check RX PDU Length, fixed length assumed */ /* ESCAN00054839 */
# else
              /* Check whether CBV Byte can be found inside RX PDU buffer */ /* ESCAN00054839 */
              && (PduInfoPtr->SduLength > CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION)
# endif
            )
          {
            i = (uint8)(CANNM_RXINDICATION_PARAM_DATAPTR[CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION]);
# if ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
            /* Check for state not Repeat Message */
            if( ( CanNm_NmState[CANNM_CHANNEL_IDX] != NM_STATE_REPEAT_MESSAGE ) && ( CanNm_RepeatMsgBitIndFlag[CANNM_CHANNEL_IDX] == FALSE ) )
            {
              /* Set the Repeat Message Indication */
              CanNm_RepeatMsgBitIndFlag[CANNM_CHANNEL_IDX] = (boolean)(i & CANNM_REPEAT_MSG_BIT_MASK);
            }
# endif

# if defined ( CANNM_ENABLE_COORD_SYNC_SUPPORT )
            /* Check for Coordination Bits */
            if( (i & NM_COORD_BIT_PRIO_MASK) != 0x00 )
            {
              Nm_ActiveCoordIndication( CANNM_NMTOSYSTEM_CHANNEL_IND, (i & NM_COORD_BIT_PRIO_MASK ), (i & NM_COORD_BIT_SLEEP) );
            }
# endif
          }
#endif

#if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
          if( ((boolean)CANNM_CFG_CAR_WUP_ENABLED == TRUE)
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
              /* No need to check RX PDU Length, fixed length assumed */ /* ESCAN00054839 */
# else
              /* Check whether Car Wake Up Byte can be found inside RX PDU buffer */ /* ESCAN00054839 */
              && (PduInfoPtr->SduLength > CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_CAR_WAKE_UP_BYTE_POSITION)
#  if ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED == STD_ON )
              /* And also check whether Node Identifier Byte can be found inside RX PDU buffer */ /* ESCAN00054839, ESCAN00064221 */
              && (((boolean)CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_CAR_WAKE_UP_FILTER_ENABLED == FALSE) ||
                  (PduInfoPtr->SduLength > CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_NID_POSITION))
#  endif
# endif
            )
          {
            if( (CanNm_RxMessageData[CANNM_CHANNEL_IDX][CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_CAR_WAKE_UP_BYTE_POSITION]
              & (1u<<CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_CAR_WAKE_UP_BIT_POSITION)) != 0u )
            {
# if ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED == STD_ON )
              if( ((boolean)CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_CAR_WAKE_UP_FILTER_ENABLED == FALSE)
                || (CanNm_RxMessageData[CANNM_CHANNEL_IDX][CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_NID_POSITION]
                  == CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_CAR_WAKE_UP_FILTER_NODE_ID) )
# endif
              {
                Nm_CarWakeUpIndication( CANNM_NMTOSYSTEM_CHANNEL_IND );
              }
            }
          }
#endif

          /* The indication is processed in CanNm_MainFunction. */
          CanNm_MsgIndicationFlag[CANNM_CHANNEL_IDX] = TRUE;

          /* CANNM165: PDU Rx Indication is configurable */
#if ( CANNM_PDU_RX_INDICATION_ENABLED == STD_ON )
          /* CANNM037, CANNM164: Notify NM Interface that a Nm message has been received */
          Nm_PduRxIndication( CANNM_NMTOSYSTEM_CHANNEL_IND );
#endif

        }

      }
    }  /* (CanNm_NmState[CANNM_CHANNEL_IDX] != NM_STATE_UNINIT) */

#if ( CANNM_DEV_ERROR_DETECT == STD_ON )
    else
    {
      /* CANNM016, CANNM018, CANNM019, CANNM196: Development error detection */
      Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_RXINDICATION_ID), CANNM_E_NO_INIT );
    }
#endif

  }  /* (channel check) */
#if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    /* CANNM016, CANNM018, CANNM019, CANNM196: Development error detection */
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_RXINDICATION_ID), CANNM_E_INVALID_CHANNEL );
  }
#else
# if ( CANNM_USE_DUMMY_STATEMENT == STD_ON )
#  if defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED ) || defined ( CANNM_ENABLE_COORD_SYNC_SUPPORT )
#  else
  /* PRQA S 3112 1 */ /* MD_CanNm_3112 */
  (void)CANNM_RXINDICATION_PARAM_PTR;
#  endif
# endif
#endif

}  /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */


#if ( ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF) )
/***********************************************************************************************************************
 *  CanNm_TxConfirmation
 **********************************************************************************************************************/
/*! \brief      This function is called by the CAN Interface after a CAN NM PDU 
 *              has been successfully transmitted (CANNM034)
 *  \param[in]  canNmTxPduId             ID of CAN NM PDU that has been transmitted
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from data link layer
 **********************************************************************************************************************/
FUNC( void, CANNM_CODE ) CanNm_TxConfirmation( VAR( PduIdType, AUTOMATIC ) canNmTxPduId )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  if( CANNM_CFG_TX_PDU_ID == canNmTxPduId )
# else
  /* local variables */
  VAR( NetworkHandleType, AUTOMATIC ) channel;

  /* Mapping from PDU ID to corresponding channel */
  for( channel=0u; channel<(NetworkHandleType)CanNm_LConfiguration.CANNM_NUMBER_OF_CHANNELS; channel++ )
  {
    if( CANNM_CFG_TX_PDU_ID == canNmTxPduId )
    {
      break;
    }
  }


  /* CANNM016, CANNM018, CANNM019, CANNM196:  Check channel parameter. */
  if( channel < (NetworkHandleType)CanNm_LConfiguration.CANNM_NUMBER_OF_CHANNELS )
# endif
  {

# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
    /* CANNM016, CANNM018, CANNM019, CANNM196: Check whether CAN NM is initialized. */
    if( CanNm_NmState[CANNM_CHANNEL_IDX] != NM_STATE_UNINIT )
# endif
    {
      /* A flag is used in order to ensure data consistency of the timeout timer. */
      CanNm_MsgConfirmationFlag[CANNM_CHANNEL_IDX] = TRUE;
# if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
      /* Confirm User Data Transmission */
      PduR_CanNmTxConfirmation( CANNM_CFG_TX_USER_DATA_PDU_ID );
# endif
    }

# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
    else
    {
      Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_TXCONFIRMATION_ID), CANNM_E_NO_INIT );
    }
# endif

  }  /* ( channel check ) */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    /* CANNM016, CANNM018, CANNM019, CANNM196: Development error detection */
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_TXCONFIRMATION_ID), CANNM_E_INVALID_CHANNEL );
  }
# endif

}
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF ) */

#if ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  CanNm_Transmit
 **********************************************************************************************************************/
/*! \brief      This function is called by the NM or application to transmit a NM message within the next main function
 *  \param[in]  CanNmTxPduId  L-PDU handle of CAN L-PDU to be transmitted. This handle specifies the corresponding CAN
 *                            LPDU ID and implicitly the CAN Driver instance as well as the corresponding CAN
 *                            controller device.
 *  \param[in]  PduInfoPtr    Pointer to a structure with CAN L-PDU related data: DLC and pointer to CAN L-SDU buffer.
 *  \pre        NM is initialized
 *  \return     E_OK - transmit request has been accepted
 *  \return     E_NOT_OK - transmit request has not been accepted due to wrong state
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called from PduR
 **********************************************************************************************************************/
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_Transmit( VAR( PduIdType, AUTOMATIC ) CanNmTxPduId,
                                                   P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr)
{
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if ( (CANNM_PN_FEATURE_ENABLED == STD_ON) || (CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON) )
#   if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  if( CANNM_CHANNEL_IDX == CanNmTxPduId )
#   else
  /* Create Channel Handle */
  VAR( NetworkHandleType, AUTOMATIC ) channel = (NetworkHandleType)CanNmTxPduId;
  /* Check channel parameter. */
  if( channel < (NetworkHandleType)CanNm_LConfiguration.CANNM_NUMBER_OF_CHANNELS )
#   endif
  {
#   if ( CANNM_DEV_ERROR_DETECT == STD_ON )
    /* Check whether CAN NM is initialized. */
    if( CanNm_NmState[CANNM_CHANNEL_IDX] != NM_STATE_UNINIT )
#   endif
    {

#   if ( CANNM_DEV_ERROR_DETECT == STD_ON )
      if( PduInfoPtr == NULL_PTR )
      {
        Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_TRANSMIT_ID), CANNM_E_NULL_POINTER );
        return E_NOT_OK;
      }
      else
#   else
#    if ( CANNM_USE_DUMMY_STATEMENT == STD_ON )
      /* PRQA S 3112 1 */ /* MD_CanNm_3112 */
      (void)PduInfoPtr;
#    endif
#   endif
      {
        /* CANNM453: Spontaneous transmission is required if
         * - The PN Feature is enabled and the handling of multiple calls of CanNm_NetworkRequest() is disabled
         * - The Car Wake-Up Rx feature is enabled
         */
        if (
#   if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
             (((boolean)CanNm_PnEnabled[CANNM_CHANNEL_IDX] == TRUE) &&
              ((boolean)CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PN_HANDLE_MULTIPLE_NETWORK_REQUEST == FALSE))
#    if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
             ||
#    endif
#   endif
#   if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
             ((boolean)CANNM_CFG_CAR_WUP_ENABLED == TRUE)
#   endif
           )
        {
          if( ((CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_NORMAL_OPERATION) ||
               (CanNm_NmState[CANNM_CHANNEL_IDX] == NM_STATE_REPEAT_MESSAGE) )
#   if ( CANNM_COM_CONTROL_ENABLED == STD_ON )
              && (CanNm_TxControlState[CANNM_CHANNEL_IDX] != MSG_TX_DISABLED) /* ESCAN00063982 */
#   endif
            )
          {
            /* CANNM450: Normal Operation / Repeat Message - trigger transmission in next main function call */
            CanNm_MsgRequest[CANNM_CHANNEL_IDX] = 2u;
            return E_OK;
          }
          
          return E_NOT_OK;
        }
        else
        {
          /* CANNM405: Spontaneous transmission is not required */
          return E_OK;
        }
      }
    }
#   if ( CANNM_DEV_ERROR_DETECT == STD_ON )
    else
    {
      Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_TRANSMIT_ID), CANNM_E_NO_INIT );
      return E_NOT_OK;
    }
#   endif
  }
  else
  {
#   if ( CANNM_DEV_ERROR_DETECT == STD_ON )
    Det_ReportError( (uint16)CANNM_MODULE_ID, CANNM_INSTANCE_ID, (uint8)(CANNM_TRANSMIT_ID), CANNM_E_INVALID_CHANNEL );
#   endif
    return E_NOT_OK;
  }
#  else /* if ( (CANNM_PN_FEATURE_ENABLED != STD_ON) && (CANNM_CAR_WUP_RX_FEATURE_ENABLED != STD_ON) ) */
  /* CANNM405: PN Feature and Car Wake-Up Rx Enabled are disabled: no spontaneous NM message transmission required */
#   if ( CANNM_USE_DUMMY_STATEMENT == STD_ON )
  /* PRQA S 3112 2 */ /* MD_CanNm_3112 */
  (void)CanNmTxPduId;
  (void)PduInfoPtr;
#   endif
  return E_OK;
#  endif
# else
  return E_NOT_OK;
# endif
}  /* PRQA S 2006,6080 */ /* MD_MSR_14.7,MD_MSR_STMIF */
#endif

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  CanNm_ConfirmPnAvailability
 **********************************************************************************************************************/
/*! \brief      This function is called by CanSM to indicate that the PN filter functionality on the indicated NM
 *              channel shall be enabled.
 *  \param[in]  nmChannelHandle index of the network channel
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by CanSM
 **********************************************************************************************************************/
FUNC( void, CANNM_CODE ) CanNm_ConfirmPnAvailability( CANNM_CHANNEL_SYSTEMTYPE_ONLY )
{
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  /* Create channel handle of Nm instance. */
  VAR( NetworkHandleType, AUTOMATIC ) channel = CanNm_SystemToNmChannelInd[nmChannelHandle];
  /* Check of channel parameters. */
  CANNM_CHECK_CHANNEL_PARAM( CANNM_CONFIRMPNAVAILABILITY_ID )
# endif
# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT( CANNM_CONFIRMPNAVAILABILITY_ID )
# endif  

  /* CANNM457: Enable message filter if and only if the PN feature is enabled */
  CanNm_PnMessageFilterEnabled[CANNM_CHANNEL_IDX] = (boolean)CanNm_PnEnabled[CANNM_CHANNEL_IDX];
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */

/***********************************************************************************************************************
 *  CanNm_DisablePNActivationState
 **********************************************************************************************************************/
/*! \brief      This function may be called directly after CanNm_Init to completely disable any PN functionality
 *  \pre        NM is initialized
 *  \context    Function could be called from interrupt level or from task level
 *  \note       Called by Application
 **********************************************************************************************************************/
/* ESCAN00066499 */
FUNC( void, CANNM_CODE ) CanNm_DisablePNActivationState( void )
{
# if defined( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  VAR( NetworkHandleType, AUTOMATIC ) channel;
# endif
# if ( CANNM_DEV_ERROR_DETECT == STD_ON )
#  if defined( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#  else
  /* ESCAN00068528 */
  for (channel = 0u; /* Condition below */; channel++)
  {
    if ((CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_CHANNEL_ACTIVE != 0u) ||
        (channel == (NetworkHandleType)(CanNm_LConfiguration.CANNM_NUMBER_OF_CHANNELS - 1u)))
    {
      break;
    }
  }
#  endif
  /* Check whether the NM is initialized. */
  CANNM_CHECK_INIT( CANNM_DISABLE_PN_ACTIVATION_STATE_ID )
# endif
  
  CANNM_ENTER_CRITICAL(CANNM_EXCLUSIVE_AREA_0);
# if defined( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
#  if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  nmMinPnChannel = 0xFFu;
#  endif

  for ( channel = 0u; channel < CanNm_LConfiguration.CANNM_NUMBER_OF_CHANNELS; channel++ )
# endif
  {
    CanNm_PnEnabled[CANNM_CHANNEL_IDX] = 0u;

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
    /* ESCAN00069312 */
    /* Reset PN bit to zero */ /* ESCAN00067173 */
    if ( CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION != CANNM_PDU_OFF )
    {
      CanNm_TxMessageData[CANNM_CHANNEL_IDX][CanNm_LChannelConfig[CANNM_CHANNEL_IDX].CANNM_PDU_CBV_POSITION] &= CANNM_CRI_BIT_INV_MASK;
    }
# endif
  }

  CANNM_LEAVE_CRITICAL(CANNM_EXCLUSIVE_AREA_0);
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
#endif

#define CANNM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*******************************************************************************
  Verify the configuration of the CAN Network Management
*******************************************************************************/

/* CANNM197: Check Error Detection / Diagnostic switches */
#if ( defined ( CANNM_DEV_ERROR_DETECT ) && ( ( CANNM_DEV_ERROR_DETECT == STD_OFF ) || ( CANNM_DEV_ERROR_DETECT == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Development Error Detection Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_PROD_ERROR_DETECT ) && ( ( CANNM_PROD_ERROR_DETECT == STD_OFF ) || ( CANNM_PROD_ERROR_DETECT == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Diagnostic Event Manager Enabled has to be defined STD_OFF or STD_ON"
#endif

/* CANNM197: Check CAN Nm Configuration switches */
#if ( defined ( CANNM_VERSION_INFO_API ) && ( ( CANNM_VERSION_INFO_API == STD_OFF ) || ( CANNM_VERSION_INFO_API == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Version Info Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_NODE_DETECTION_ENABLED ) && ( ( CANNM_NODE_DETECTION_ENABLED == STD_OFF ) || ( CANNM_NODE_DETECTION_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Node Detection Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_REMOTE_SLEEP_IND_ENABLED ) && ( ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_OFF ) || ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Remote Sleep Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_USER_DATA_ENABLED ) && ( ( CANNM_USER_DATA_ENABLED == STD_OFF ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: User Data Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_BUS_SYNCHRONIZATION_ENABLED ) && ( ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_OFF ) || ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Bus Synchronization Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_PASSIVE_MODE_ENABLED ) && ( ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) || ( CANNM_PASSIVE_MODE_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Passive Mode Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_NODE_ID_ENABLED ) && ( ( CANNM_NODE_ID_ENABLED == STD_OFF ) || ( CANNM_NODE_ID_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Node Identifier Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_PDU_RX_INDICATION_ENABLED ) && ( ( CANNM_PDU_RX_INDICATION_ENABLED == STD_OFF ) || ( CANNM_PDU_RX_INDICATION_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Pdu Rx Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_STATE_CHANGE_IND_ENABLED ) && ( ( CANNM_STATE_CHANGE_IND_ENABLED == STD_OFF ) || ( CANNM_STATE_CHANGE_IND_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: State Change Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_COM_CONTROL_ENABLED ) && ( ( CANNM_COM_CONTROL_ENABLED == STD_OFF ) || ( CANNM_COM_CONTROL_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Communication Control Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_BUS_LOAD_REDUCTION_ENABLED ) && ( ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_OFF ) || ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Bus Load Reduction Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_IMMEDIATE_RESTART_ENABLED ) && ( ( CANNM_IMMEDIATE_RESTART_ENABLED == STD_OFF ) || ( CANNM_IMMEDIATE_RESTART_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Immediate Restart Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_REPEAT_MSG_IND_ENABLED ) && ( ( CANNM_REPEAT_MSG_IND_ENABLED == STD_OFF ) || ( CANNM_REPEAT_MSG_IND_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Repeat Message Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_IMMEDIATE_TXCONF_ENABLED ) && ( ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF ) || ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Immediate Tx Confirmation Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_DISABLE_TX_ERR_REPORT ) && ( ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF ) || ( CANNM_DISABLE_TX_ERR_REPORT == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Disable Transmission Error Reporting has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_CRC_CHECK ) && ( ( CANNM_CRC_CHECK == STD_OFF ) || ( CANNM_CRC_CHECK == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: CRC Check has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_USE_DUMMY_STATEMENT ) && ( ( CANNM_USE_DUMMY_STATEMENT == STD_OFF ) || ( CANNM_USE_DUMMY_STATEMENT == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Use Dummy Statement has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_COM_USER_DATA_ENABLED ) && ( ( CANNM_COM_USER_DATA_ENABLED == STD_OFF ) || ( CANNM_COM_USER_DATA_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: User Data Support via Com has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED ) && ( ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_OFF ) || ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Immediate Nm Transmission Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED ) && ( ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_OFF ) || ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Active Wup Bit Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_CAR_WUP_RX_FEATURE_ENABLED ) && ( ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_OFF ) || ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Car Wup Rx Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED ) && ( ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED == STD_OFF ) || ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: Car Wup Filter Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_PN_FEATURE_ENABLED ) && ( ( CANNM_PN_FEATURE_ENABLED == STD_OFF ) || ( CANNM_PN_FEATURE_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: PN Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_PN_ERA_CALC_FEATURE_ENABLED ) && ( ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_OFF ) || ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: PN ERA Calc Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED ) && ( ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_OFF ) || ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON ) ) )
#else
# error: "CAN NM configuration issue: PN EIRA Calc Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_DEM2DET_ENABLED ) && ( ( CANNM_DEM2DET_ENABLED == STD_OFF ) || ( CANNM_DEM2DET_ENABLED == STD_ON ) ) )
#else
/* ESCAN00051043 */
# error: "CAN NM configuration issue: Dem2Det Enabled has to be defined STD_OFF or STD_ON"
#endif
#if ( defined ( CANNM_AMD_RUNTIME_MEASUREMENT ) && ( ( CANNM_AMD_RUNTIME_MEASUREMENT == STD_OFF ) || ( CANNM_AMD_RUNTIME_MEASUREMENT == STD_ON ) ) )
#else
/* ESCAN00066109 */
# error: "CAN NM configuration issue: AmdRtm Time Measurement Enabled has to be defined STD_OFF or STD_ON"
#endif

/* CANNM163: Check configuration of Passive Mode */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_ON )
# if defined ( CANNM_ENABLE_COORD_SYNC_SUPPORT )
#  error "CAN NM configuration issue: CANNM_ENABLE_COORD_SYNC_SUPPORT should not be used with CANNM_PASSIVE_MODE_ENABLED."
# endif
#endif

/* Check Car Wakeup */
#if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_OFF ) && ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED == STD_ON )
# error "CAN NM configuration issue: CANNM_CAR_WUP_FILTER_FEATURE_ENABLED cannot be activated if CANNM_CAR_WUP_RX_FEATURE_ENABLED is STD_OFF."
#endif

/* Check PN Feature */
#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON ) && ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if ( CANNM_USER_DATA_ENABLED == STD_ON ) || ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
#  else
#   error "CAN NM configuration issue: CANNM_PN_EIRA_CALC_FEATURE_ENABLED activated requires CANNM_USER_DATA_ENABLED or CANNM_COM_USER_DATA_ENABLED to be enabled."
#  endif
# endif
#else
# if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
#  error "CAN NM configuration issue: CANNM_PN_ERA_CALC_FEATURE_ENABLED cannot be activated if CANNM_PN_FEATURE_ENABLED is STD_OFF."
# endif
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
#  error "CAN NM configuration issue: CANNM_PN_EIRA_CALC_FEATURE_ENABLED cannot be activated if CANNM_PN_FEATURE_ENABLED is STD_OFF."
# endif
#endif

/* Check configuration of Single Channel optimization */
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED ) && ( CANNM_NUMBER_OF_CANNM_CHANNELS > 1u )
# error "CAN NM configuration issue: Single Channel optimization is only in single channel configurations possible."
#endif

/* Check configuration of Node Detection */
#if ( CANNM_NODE_DETECTION_ENABLED == STD_ON ) && ( CANNM_NODE_ID_ENABLED == STD_OFF )
# error: "CAN NM configuration issue: CANNM_NODE_DETECTION_ENABLED cannot be activated if CANNM_NODE_ID_ENABLED is STD_OFF."
#endif

/* Check Gateway Configuration */

/* Check library configuration */
#if defined ( V_EXTENDED_BUILD_LIB_CHECK )
/* Provide library checks */
# if ( CANNM_CONFIG_VARIANT == 1u )
#  error: "CAN NM configuration issue: CANNM_CONFIG_VARIANT must not be Pre-Compile (1) when building libraries."
# endif
#endif


/*******************************************************************************
* ORGANI check
*******************************************************************************/
/* ESCAN00053229 */

/* module specific MISRA deviations:
 MD_CanNm_2003:
      Reason:     Fall through used for code optimizations.
      Risk:       There is a risk that a fall through is overseen by a code review and lead to unexpected results.
      Prevention: Fall through is marked with explicit comments to draw attention to it when code review is performed.
 MD_CanNm_3112:
      Reason:     Dummy statement to avoid compiler warnings.
      Risk:       There is no risk as such statements have no effect on the code.
      Prevention: Covered by code review.
 MD_CanNm_3673:
      Reason:     Common sense for Vector CANbedded components.
                  Note that declaring API parameter to const could lead to warnings or problems for some compilers.
      Risk:       Parameter is not defined as const and could be modified within this function.
      Prevention: The parameter is not modified. Covered by code review.
*/

/**********************************************************************************************************************
 *  END OF FILE: CanNm.c
 *********************************************************************************************************************/
