/********************************************************************************************************************
|    File Name: CANIF.C
|
|  Description: Implementation of the AUTOSAR CAN Interface
|--------------------------------------------------------------------------------------------------------------------
|               C O P Y R I G H T
|--------------------------------------------------------------------------------------------------------------------
| Copyright (c) 1996-2014 by Vector Informatik GmbH.       All rights reserved.
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
| Bir          Holger Birke              Vector Informatik GmbH
|--------------------------------------------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|--------------------------------------------------------------------------------------------------------------------
| Date        Version   Author  Description
| ----------  --------  ------  -------------------------------------------------------------------------------------
| 2005-09-12  0.01      Ard       first implementation
| 2006-01-18  0.02      Ard     - Fix issue when sending queued PDUs
| 2006-02-06  0.03      Ard     - Fix queue handling
| 2006-02-08  0.04      Ard     - Use global interrupt disable routines from osek
| 2006-02-09  0.05      Ard     - Inform DET if Can_Write returns CAN_BUSY when sending from queue
| 2006-02-10  0.06      Ard     - Change to STOP mode in BusOff notification before notifying upper layer
| 2006-03-30  0.07      Ard     - Change Version of CanIf_Types
| 2006-04-05  0.08      Ard     - Remove controller state check in CanIf_Init()
| 2006-04-24  0.09      Ard     - Add missing preprocessor switches at Det_ReportError call
| 2006-05-24  2.00      Ard     - AUTOSAR 2.0
| 2006-05-31  2.01      Ard     - Support DET, RxIndication function type 2 (TP)
|                                 rename CANIF_CS_STOP mode
|                                 add missing channel mode
| 2006-06-21  2.02      Ard     - Add CanIf_InitMemory function
| 2006-06-22  2.03      Ard     - Changes in channel mode state machine
|                                 Change API of CanIf_GetChannelMode and CanIf_GetControllerMode
| 2006-06-23  2.04      Ard     - Modifiy init functions
| 2006-06-26  2.05      Ard     - Changes in channel mode state machine
|                                 Remove PDU specific de/activation of DLC-Check
|                                 Add global initialization structure
| 2006-07-03  2.06      Ard     - Change parameter value of WakeupNotification
| 2006-07-03  2.07      Ard     - Remove EcuM and ComM header includes
| 2006-07-05  2.08      Ard     - Remove Det calls which will never be reached
|                               - Change API of CanIf_Init
|                               - Changes in Version history and Version defines
| 2006-07-12  2.09      Ard     - Remove compile warnings
|                                 changes in CanIf.h and CanIf_Types.h
| 2006-09-05  2.10      Ard     - Remove MISRA warnings
| 2006-09-18  2.11      Ard     - Add Tx polling mode
| 2006-11-17  2.12      Ard     - Support postbuild configurations
| 2006-12-20  2.13      Ard     - Adapt access to generated data
|                                 Add BusOff polling
| 2007-02-20  2.14      Ard     - Abandon reception in BasicCAN if no BasicCAN messages and ranges are configured
| 2007-02-22  2.15      Ard     - ESCAN00019715: Add dynamic Tx DLC support
|                               - ESCAN00019714: Change ControllerWakeup callback function name
| 2007-03-01  2.16      Ard     - ESCAN00019796: Change type of local variable to PduLengthType
| 2007-03-20  2.17      Ard     - ESCAN00020010: Remove spurious DET error when transmitting queued messages
| 2007-03-30  2.18      Ard     - Support VStdLib copy algorithms (configurable)
| 2007-03-12  3.00      Ard     - AUTOSAR 2.1
| 2007-09-03  3.01      Ard     - ESCAN00022117: Fix compile warning due to inconsistent function declaration
|                               - ESCAN00022291: Fix memory qualifiers 
|                               - ESCAN00022292: Add support for modified CanIf state machine
|                               - ESCAN00022119: Add additionally check of generated data
|                               - ESCAN00022479: Fix wake up notification handling 
|                               - ESCAN00022491: Remove compile warning in CanIf_SetWakeupEvent
| 2007-10-12  3.02      Ard     - ESCAN00022751: Fix accidentally raised DET error in CanIf_ConvertPduId
| 2007-11-05  3.03      Ard     - ESCAN00023167: Introduce binary search
|                                 ESCAN00023168: Support extended IDs
|                                 ESCAN00023165: Apply fix for Can_Init API
|                                 ESCAN00023199: Encapsulate Dummy statements with precompiler switch
|                                 ESCAN00023502: Modify CanIf_InitController API 
|                                 ESCAN00024165: Change handling of DLC for advanced indication function
| 2008-02-22  4.00      Ard     - ESCAN00024947: AUTOSAR 3.0
| 2008-04-10  4.01      Ard     - ESCAN00026007: MISRA compliance + Minor changes
|                                 ESCAN00026212: Implement Library version check
|                                 ESCAN00026257: Fix spelling of include filenames
|                                 ESCAN00025964: Access DEM errors via generated constants
| 2008-05-13  4.02      Ard     - ESCAN00026849: Fix unexpected DET Error in case of activated CANIF_CANCEL_SUPPORT_API
| 2008-05-14  4.03      Ard     - ESCAN00026647: Introduce extended generator checks
|                                 ESCAN00026946: Fix transmission of wrong CanID in case of  CANIF_DYNAMIC_TX_DLC == STD_OFF
|                                 ESCAN00026971: Fix unexpected behaviour after DET error is raised in CanIf_Transmit
| 2008-07-28  4.04      Ard     - ESCAN00028771: Add BrsTime support for runtime measurement
|                                 ESCAN00027656: Support wake up validation
|                                 ESCAN00025740: Remove Beta Disclaimer
|                                 ESCAN00029138: Fix post-build data access to TransceiverUpToLow map table
|                                 ESCAN00029110: Remove channel specific bus off notification function
|                                 ESCAN00029314: Check version of generated data with pre-processor
|                                 ESCAN00029315: Change version definitions
| 2008-09-10  4.05      Ard     - ESCAN00029908: Rework Critical sections
|                                 ESCAN00029825: Change dummy Statement handling
|                                 ESCAN00029828: Support precompile and link-time CRC check
| 2008-11-06  4.06      Ard     - ESCAN00031108: Avoid compiler warnings
|                                 ESCAN00031111: Avoid preprocessor warnings
|                                 ESCAN00031182: Remove Compiler warning due to pointless statement in CanIf_Init()
|                                 ESCAN00031206: Add pre-processor error message if ReadRxPduData API is activated
|                                 ESCAN00031640: Raise DET error in case of inconsistent transceiver configuration
|                                 ESCAN00031731: Unbalanced call of CanIf_LeaveCritical
|                                 ESCAN00031732: Fix unexpected Tx confirmation of cancelled PDUs (CanIf_CancelTransmit)
| 2009-02-19  4.07      Ard     - ESCAN00032430: Change referenced generator version to correct value
|                                 ESCAN00032434: Remove compiler warning due to unused variable in CanIf_HlIndication
|                                 ESCAN00032207: Fix compile error "Invalid pointer conversion" in CanIf_SetPduMode
|                                 ESCAN00032330: Code improvements (e.g. runtime, comments, ...)
|                                 ESCAN00033078: Support state transition "CANIF_CS_STARTED" to "CANIF_CS_SLEEP"
|                                 ESCAN00032595: Support transceiver state transition to normal during wake up 
|                                 ESCAN00033608: Support new requirements (DEM to DET, ApplDlcErrorNotification)
| 2009-04-09  4.08      Ard     - ESCAN00034547: Support new requirements (TxPduId Mapping)
| 2009-06-17  4.09      Rna     - ESCAN00034553: Provide Hash Search algorithm
| 2009-07-06  4.10      Bir     - ESCAN00034841: Confirmation without critical section
| 2009-07-23  4.11      Rna     - ESCAN00036101: pre-processor checks for building the library
| 2009-08-03            Rna       ESCAN00035031: Compiler error: "Wrong pointer cast"
| 2009-08-24  4.11.01   Rna     - ESCAN00037328: DET reports that CANIF is not initialized 
| 2009-09-01  4.11.02   Rna     - ESCAN00037493: Some PDUs are not received by the ECU
| 2009-09-29  4.11.03   Rna     - ESCAN00037987: Some PDUs are not received by the ECU
| 2009-10-22            Rna     - ESCAN00037935: Compile error in CanIf_cfg.h (changes only in CanIf_Compiler_Cfg.inc)
| 2009-12-18  4.11.04   Rna     - ESCAN00039858: Upper layer, for example TP, receives wrong data from CanDriver/CanInterface
| 2010-01-11  4.11.05   Rna     - ESCAN00039888: CanIf_HlIndication() incompatible near pointer cast (changes only for CanIf_Types.h)
| 2010-01-20  4.12.00   Rna     - ESCAN00040264: Support 8 and 16 bit CanIf_HwHandleType for variable Hrh
| 2010-02-10            Rna       ESCAN00040966: Code optimization in case of only one channel used
| 2010-02-19            Rna       ESCAN00040119: CANIF code size optimization at function CanIf_SetPduMode()
| 2010-03-04  4.13.00   Rna     - ESCAN00041353: Support dynamic Tx objects
| 2010-04-01            Rna       ESCAN00041879: Compiler warnings:"condition is always false" and "undefined enum value" occur
| 2010-04-14            Rna       ESCAN00041366: Runtime of CanIf_Transmit is too high
| 2010-05-03  4.13.01   Rna     - ESCAN00042675: Reference to Generator changed
| 2010-07-20  4.14.00   Rna     - ESCAN00044166: Support Common CAN
| 2010-06-28  4.15.00   Rna     - ESCAN00043633: Changes regarding interrupt locks
| 2010-07-14            Rna       ESCAN00042905: compiler warning occurs "controller" was set but never used
| 2010-07-14            Rna       ESCAN00043501: Support Tx Bitqueue
| 2010-08-09            Rna       ESCAN00044608: MISRA compliance changes
| 2010-09-27  4.15.01   Rna     - ESCAN00045607: Compile error: "identifier channel is undefined"
| 2010-09-28  4.16.00   Rna     - ESCAN00045687: Changes regarding one channel optimization
| 2010-09-29            Rna       ESCAN00045645: Compiler warning:  undefined enum value
| 2010-09-29            Rna       ESCAN00045644: Compiler warning: condition is always true in CanIf_SetChannelMode
| 2010-10-04            Rna       ESCAN00045749: Support "Teilnetzbetrieb"
| 2010-12-06            Rna       ESCAN00046249: Adapt AUTOSAR version check
| 2011-01-31            Seu       ESCAN00048317: When using Tx-bitqueue CAN-messages are not send in the order: high-priority (first) low-priority(last)
| 2011-04-02            Rna       ESCAN00048457: Compiler warning: Variable was defined but never referenced
| 2011-02-14            Rna       ESCAN00048657: Undefined type "CanTransmitHandle"
| 2011-03-21  4.17.00   Rna       ESCAN00049391: Compiler warning: enumeration constant "CANIF_GET_OFFLINE" not handled in switch
| 2011-05-09            Seu       ESCAN00050278: Add support for partial networking
| 2011-05-25            Seu       ESCAN00051107: Compiler warning: conditional expression or part of it is always true/false/ statement not reached
| 2011-05-25            Seu       ESCAN00051108: Compiler warning: possible redundant expression / parameter unused
| 2011-05-30            Seu       ESCAN00051026: special character must not be used in comments
| 2011-10-07  4.18.00   Seu       ESCAN00053271: AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
| 2011-10-12            Seu       ESCAN00054204: MISRA compliance changes R13
| 2011-10-14            Seu       ESCAN00037355: QAC reports rule violation: An integer constant expression with negative value is being converted to an unsigned type
| 2011-10-18            Seu       ESCAN00046190: AR3-297 AR3-894: Precompile Optimization of Rx Indication
| 2011-10-21            Seu       ESCAN00051563: Remove the AUTOSAR Release Version Check
| 2011-10-22            Seu       ESCAN00053264: AR3-2069: Remove non-SchM code for critical section handling
| 2011-10-28            Seu       ESCAN00054339: AR3-1738: Add support for asynchronous transceiver driver
| 2011-11-10            Seu       ESCAN00054772: Basic CAN TxPdu must be cancelled both in queue and in CAN driver
| 2011-11-23            Seu       ESCAN00055082: Compile error implicit declared function "SchM_Enter_CanIf_(0u)();"
| 2011-12-08            Seu       ESCAN00054368: AR3-2024: Add support of 2 new PDU modes for partial network wake up filter mechanism
| 2012-03-14  4.18.01   Seu       ESCAN00056251: A DET is reported during initialization / partial networking Tx Pdu filter is not enabled (only Post-build configuration)
| 2012-03-14            Seu       ESCAN00057367: ECU does not receive any messages (Partial Networking only)
| 2012-03-14            Seu       ESCAN00057578: Out-of-date data is send after pdu mode is set to online (only Partial Networking)
| 2012-03-19  4.19.00   Seu       ESCAN00055329: Support the usage of the same wakeup source for different multiple ECU configuration channels
| 2012-03-23            Seu       ESCAN00057838: Macro name has to have the MSN prefix
| 2012-03-23            Seu       ESCAN00057842: Some changes to support GENy and CFG5 in one source code
| 2012-04-03            Seu       ESCAN00056144: Implement AUTOSAR 3.2.1 wakeup behaviour
| 2012-04-03            Seu       ESCAN00058112: Access to tables can be optimized
| 2012-05-29  4.19.01   Seu       ESCAN00058619: Channel does not wake up when CanIf_CheckWakeup is called
| 2012-05-29            Seu       ESCAN00058657: Channel does not wake up / EcuM_SetWakeupEvent() is not called
| 2012-06-22            Seu       ESCAN00057360: AR3-2383: Implement handling of call to Dem_ReportErrorStatus
| 2012-06-30            Rna       ESCAN00059732: Changes for "Silent BSW" PduId validation at function CanIf_HlIndication()
| 2012-08-10  4.20.00   Seu       ESCAN00059457: AR3-2398: Update Partial Network Handling according ASR3.2.2
| 2012-08-10            Seu       ESCAN00060105: AR3-2406: Asynchronous transceiver handling according to AUTOASR 3.2.2
| 2012-08-10            Seu       ESCAN00059926: AR3-2406: Remove CanIf_MainFunction_CheckWakeup() API
| 2012-08-13            Seu       ESCAN00060165: Setting the CAN ID in function CanIf_SetDynamicTxId() is secured with a critical section
| 2012-08-13            Seu       ESCAN00060765: AR3-2406: Remove feature CANIF_TRCV_WAKEUPSTATETRANSITION
| 2012-08-13            Seu       ESCAN00059616: Compiler error: variable 'CanIf_CheckWakeupState' is undefined
| 2012-08-31            Seu       ESCAN00061139: Data inversion occurs: older data set is send after newer one
| 2012-09-03            Seu       ESCAN00060317: Compiler error: Variables CanIf_TxQueueCounter and Controller undefined
| 2012-09-13            Seu       ESCAN00061345: Rx path is switched off unexpectedly
| 2013-04-08  4.20.01   Seu       ESCAN00061759: Compiler warning: Variable "queueEndElementIdx" was declared but never referenced
| 2013-04-08            Seu       ESCAN00063650: Compiler warning:  "variable "wuController" was set but never used"
| 2013-04-18            Rna       ESCAN00066737: Changed handling for return value of function CanIf_SetPduMode()
| 2013-05-03  4.21.00   Seu       ESCAN00066105: AR3-2494: Implement AMD timemeasurement support
| 2013-07-16  4.22.00   Rna       ESCAN00068997: Extend controller mode handling
| 2013-12-12  4.22.01   Rna       ESCAN00072535: TxQueue won't be deleted in case of Busoff
|*******************************************************************************************************************/

#define CANIF_SOURCE
#define __CANIF_SRC__     /* for all msr module (used by RTM), ESCAN00066105 */

/* PRQA S 0715 EOF */ /* MD_CanIf_1.1 */
/* PRQA S 3453 EOF */ /* MD_MSR_19.7 */
/* PRQA S 0850 EOF */ /* MD_MSR_19.8 */
/* PRQA S 0857 EOF */ /* MD_CanIf_1.1_NumberOfMacroDefinitions */
/* PRQA S 3412 EOF */ /* MD_MSR_19.4 */


/*******************************************************************************************************************/
/*  Include files                                                                                                  */
/*******************************************************************************************************************/

#include "CanIf.h"

#include "CanIf_Cbk.h"

#include "SchM_CanIf.h"

/* Required as CAN API is called from CanIf.c not from generated data */
# include "Can.h"
# include "Can_Cfg.h"

#if !defined (CANIF_AVOID_VSTDLIB_COPY)
/* For VStdLib / CanIf.h/CanIf_Cfg.h has to be included before       */
/* possibility to explicitely avoid usage of VStdLib copy algorithm  */
# include "v_cfg.h"
# include "v_def.h"

# if defined (VGEN_ENABLE_VSTDLIB)
/* Check if VStdlib is system                                        */
#  if defined (VSTD_HL_USE_VSTD_RAMMEMCPY)
/* Copy algorithm is available                                       */
#   define CANIF_USES_VSTDLIB_COPY      STD_ON
#  endif
# endif
#endif


#if (CANIF_TRCV_HANDLING == STD_ON)
# include "CanIf_CanTrcv.h"
#endif

/* CANIF233 */
#if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_TRCV_HANDLING == STD_ON))
# include "CanSM_Cbk.h"
#endif


#if (CANIF_PROD_ERROR_DETECT == STD_ON)
# include "Dem.h"
#endif

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif


#if !defined (V_SUPPRESS_EXTENDED_VERSION_CHECK)
# include "v_ver.h"
#endif


#if !defined (CANIF_AMD_RUNTIME_MEASUREMENT)
# define CANIF_AMD_RUNTIME_MEASUREMENT                STD_OFF
#endif

#if (CANIF_AMD_RUNTIME_MEASUREMENT == STD_ON)
# include "AmdRtm.h"
#endif

/*******************************************************************************************************************/
/*  Version check                                                                                                  */
/*******************************************************************************************************************/


/* CanIf.c version definition (module version) */
#define CANIF_MAJOR_VERSION   0x04u
#define CANIF_MINOR_VERSION   0x22u
#define CANIF_PATCH_VERSION   0x01u



/* CanIf_cbk.h version check */
#if (CANIF_CBK_MAJOR_VERSION != 0x04u)
# error "Source and Header files are inconsistent!"
#endif

#if (CANIF_CBK_MINOR_VERSION != 0x04u)
# error "Source and Header files are inconsistent!"
#endif

#if (CANIF_CBK_PATCH_VERSION != 0x00u)
# error "Source and Header files are inconsistent!"
#endif

/* CanIf_types.h version check */
#if (CANIF_TYPES_MAJOR_VERSION != 0x04u)
# error "Source and Header files are inconsistent!"
#endif

#if (CANIF_TYPES_MINOR_VERSION != 0x16u)
# error "Source and Header files are inconsistent!"
#endif

#if (CANIF_TYPES_PATCH_VERSION != 0x00u)
# error "Source and Header files are inconsistent!"
#endif

/* CanIf.h version check */
#if (CANIF_API_MAJOR_VERSION != 0x04u)
# error "Source and Header files are inconsistent!"
#endif

#if (CANIF_API_MINOR_VERSION != 0x22u)
# error "Source and Header files are inconsistent!"
#endif

#if (CANIF_API_PATCH_VERSION != 0x01u)
# error "Source and Header files are inconsistent!"
#endif

/*******************************************************************************************************************/
/*  Compatibility / Defaults                                                                                       */
/*******************************************************************************************************************/

#if !defined (CANIF_IDENTITY_MANAGER_CONFIG)
# define CANIF_IDENTITY_MANAGER_CONFIG                STD_OFF
#endif

/* ESCAN00046190 */
#if !defined (CANIF_RX_INDICATION_TYPE_I_IS_USED)
# define CANIF_RX_INDICATION_TYPE_I_IS_USED           STD_ON
#endif

#if !defined (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT)
# define CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT      STD_OFF
#endif

#if !defined (CANIF_PN_WU_TX_PDU_FILTER)
# define CANIF_PN_WU_TX_PDU_FILTER                    STD_OFF
#endif

#if !defined (CANIF_PN_TRCV_HANDLING)
# define CANIF_PN_TRCV_HANDLING                       STD_OFF
#endif

#if !defined (CANIF_DYNAMIC_TX_DLC)
# define CANIF_DYNAMIC_TX_DLC                         STD_ON
#endif

#if !defined (CANIF_EXTENDED_STATE_MACHINE)
# define CANIF_EXTENDED_STATE_MACHINE                 STD_OFF
#endif

#if !defined (CANIF_SEARCH_ALGORITHM)
# define CANIF_SEARCH_ALGORITHM                       CANIF_LINEAR
#endif

#if !defined (CANIF_RX_PASS_STATIC_DLC)
# define CANIF_RX_PASS_STATIC_DLC                     STD_OFF
#endif

#if !defined (CANIF_LIBRARY_SUPPORT)
# define CANIF_LIBRARY_SUPPORT                        STD_OFF
#endif

#if !defined (CANIF_SUPPRESS_CANIF_GENDATA_VERSION_CHECK)
# define CANIF_SUPPRESS_CANIF_GENDATA_VERSION_CHECK   STD_OFF
#endif

#if !defined (CANIF_WAKEUP_VALIDATION)
# define CANIF_WAKEUP_VALIDATION                      STD_OFF
#endif

#if !defined (CANIF_WAKEUP_VALID_ALL_RX_MSGS)
# define CANIF_WAKEUP_VALID_ALL_RX_MSGS               STD_OFF
#endif

#if !defined (CANIF_USES_VSTDLIB_COPY)
# define CANIF_USES_VSTDLIB_COPY                      STD_OFF
#endif

#if !defined (CANIF_DEM_REPORT_DLC_FAILED)
/* Default AUTOSAR behaviour */
# define CANIF_DEM_REPORT_DLC_FAILED                  STD_ON
#endif

#if !defined (CANIF_USER_DLC_ERROR_NOTIFICATION)
# define CANIF_USER_DLC_ERROR_NOTIFICATION            STD_OFF
#endif

#if !defined (CANIF_DEMTODET_E_FULL_TX_BUFFER)
# define CANIF_DEMTODET_E_FULL_TX_BUFFER              STD_OFF
#endif

#if !defined (CANIF_DEMTODET_E_STOPPED)
# define CANIF_DEMTODET_E_STOPPED                     STD_OFF
#endif


#if !defined(CANIF_ONE_CONTROLLER_OPTIMIZATION)
# define CANIF_ONE_CONTROLLER_OPTIMIZATION            STD_OFF
#endif


#if !defined(CANIF_SETDYNAMICTXID_API)
# define CANIF_SETDYNAMICTXID_API                     STD_OFF
#endif 


#if !defined(CANIF_OPTIMIZE_TX_WITH_SHORT_PIA_GAP)
# define CANIF_OPTIMIZE_TX_WITH_SHORT_PIA_GAP         STD_ON
#endif


#if defined (CANIF_TRCV_WAKEUPSTATETRANSITION)
# error "Feature CANIF_TRCV_WAKEUPSTATETRANSITION is not supported by CAN interface!"
#endif


/* Feature validation */
#if defined (V_EXTENDED_BUILD_LIB_CHECK)
# if (CANIF_LIBRARY_SUPPORT != STD_ON)
#  error "Activate Library Solution in PreConfig file! (Attribute: If_AsrIfCan_IsLibrarySolution)"
# endif
#endif

#if defined (V_EXTENDED_BUILD_LIB_CHECK)
# if !defined (CANIF_SUPPRESS_TRANSCEIVERMAPPING_BUILDLIBCHECK)   
#  if (CANIF_TRCV_HANDLING == STD_ON)  /* If Trcv Handling is active, we need the mapping (for PB)*/ 
#   if (CANIF_TRCV_MAPPING != STD_ON)
#    error "It is strongly suggested to activate the feature 'Transceiver Mapping' in a library delivery."
#   endif
#  endif
# endif
#endif

#if defined (V_EXTENDED_BUILD_LIB_CHECK)
# if (CANIF_CONFIG_VARIANT  == CANIF_CFGVAR_PRECOMPILETIME)
#  error "Config variant: "precompile config" not possible for a library delivery" 
# endif
#endif
  


/* Wakeup Validation not allowed with Extended State machine */
#if (CANIF_WAKEUP_VALIDATION == STD_ON)
# if (CANIF_EXTENDED_STATE_MACHINE == STD_ON)
#  error "Invalid configuration: Wake up validation (CANIF_WAKEUP_VALIDATION) is activated with extended state machine (CANIF_EXTENDED_STATE_MACHINE)"
# endif
#endif

/* WakeUp Validation without WakeUp support not acceptable */
#if (CANIF_WAKEUP_VALIDATION == STD_ON)
# if (CANIF_WAKEUP_SUPPORT == STD_OFF)
#  error "Invalid configuration: Wake up validation (CANIF_WAKEUP_VALIDATION) is activated without activating wake up support (CANIF_WAKEUP_SUPPORT)"
# endif
#endif


/* ESCAN00031206 - ReadRxPduDataAPI currently not suggested to be enabled */
#if (CANIF_READRXPDUDATA_API == STD_ON)
# error "Invalid configuration: Activation of the feature ReadRxPduDataAPI is currently not suggested"
#endif


#if !defined (V_USE_DUMMY_STATEMENT)
# error "The define V_USE_DUMMY_STATEMENT shall be defined either in Compiler_Cfg.h or as parameter for the Compiler"
#endif


/*******************************************************************************************************************/
/*  Version check (external modules)                                                                               */
/*******************************************************************************************************************/

/* ESCAN00051563 - all ASR checks removed */

/* Check AR Version of the CAN Driver */

/* Check AR Version of the ECU Manager */

/* Check AR Version of the Development Error Tracer */

/* Check AR Version of the Diagnostics Event Manager */


/*******************************************************************************************************************/
/*  Defines / data types / structs / unions                                                                        */
/*******************************************************************************************************************/

#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)

/*! \def Define CANIF_PN_WU_TXPDU_FILTER_EN
 * Signals partial networking TxPdu wakeup filter is enabled
 * Used to set & to evaluate variable CanIf_ChPnWuTxPduFilterState
 */
# define CANIF_PN_WU_TXPDU_FILTER_EN            1u

/*! \def Define CANIF_PN_WU_TXPDU_FILTER_DIS
 * Signals partial networking TxPdu wakeup filter is not enabled
 * Used to set & to evaluate variable CanIf_ChPnWuTxPduFilterState
 */
# define CANIF_PN_WU_TXPDU_FILTER_DIS           0u

/*! \def Define CANIF_PN_WU_TXPDU_FILTER_AVBL
 * Signals channel supports partial networking Tx Pdu wakeup filtering
 * Used to evaluate return value of CANIF_CFG_PN_WU_TXPDU_FILTER_ACTIVE()
 */
# define CANIF_PN_WU_TXPDU_FILTER_SUPP          (CanIf_BoolType)1u

/*! \def Define CANIF_PN_WU_TXPDU_FILTER_NOT_AVBL
 * Signals channel does not support partial networking Tx Pdu wakeup filtering
 * Used to evaluate return value of CANIF_CFG_PN_WU_TXPDU_FILTER_ACTIVE()
 */
# define CANIF_PN_WU_TXPDU_FILTER_NOT_SUPP      (CanIf_BoolType)0u

/*! \def Define CANIF_PN_MASK_GET_DLC
 * Used to mask out the PnWuTxPdu flag (See next MACRO)
 */
# define CANIF_PN_WU_FLAG_MASK_OUT     0x7Fu

/*! \def Define CANIF_PN_GET_WU_FLAG_DLC
 * Mask to check whether TxPduId is marked as PnWuTxPdu or not
 * If masking DLC returns != 0 then TxPdu is marked otherwise not
 */
# define CANIF_PN_WU_FLAG_GET          (uint8)(~(CANIF_PN_WU_FLAG_MASK_OUT))

#endif


#define CANIF_MAGIC_NUMBER                      0xDEAFu
#define CANIF_GENDATA_VERSION                   0x0600u

/* GENy */
#define CANIF_GENTOOL_GENY_MAJOR_VERSION_REF    0x03u
#define CANIF_GENTOOL_GENY_MINOR_VERSION_REF    0x21u

/* CFG5 */
#define CANIF_GENTOOL_CFG5_MAJOR_VERSION_REF    0x01u
#define CANIF_GENTOOL_CFG5_MINOR_VERSION_REF    0x00u


#if (CANIF_LIBRARY_SUPPORT == STD_ON) 
# define CANIF_INDIRECT_E_FULL_TX_BUFFER        CanIf_DemError_TxBufferFull
# define CANIF_INDIRECT_E_STOPPED               CanIf_DemError_Stopped
# define CANIF_INDIRECT_E_INVALID_DLC           CanIf_DemError_InvalidDlc
# define CANIF_INDIRECT_E_SLEEP_REQ_FAILED      CanIf_DemError_SleepReqFailed
#else
# define CANIF_INDIRECT_E_FULL_TX_BUFFER        CANIF_E_FULL_TX_BUFFER
# define CANIF_INDIRECT_E_STOPPED               CANIF_E_STOPPED
# define CANIF_INDIRECT_E_INVALID_DLC           CANIF_E_INVALID_DLC
# define CANIF_INDIRECT_E_SLEEP_REQ_FAILED      CANIF_E_SLEEP_REQ_FAILED
#endif

#if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
#define CANIF_STOP_FLAG        0x40000000u
#define CANIF_RANGE_FLAG       0x20000000u
#else
#define CANIF_STOP_FLAG        0x4000u
#define CANIF_RANGE_FLAG       0x2000u
#endif


#if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK ) || (CANIF_CRC_CHECK == STD_ON)
# define CanIf_GeneratorCompatibilityError()      EcuM_GeneratorCompatibilityError((uint16) CANIF_MODULE_ID, (uint8) 0)
#endif


#if (CANIF_PROD_ERROR_DETECT == STD_ON)
# if !defined (CanIf_Dem_ReportError)
# define CanIf_Dem_ReportError(EventId)           ((void)Dem_ReportErrorStatus((EventId), DEM_EVENT_STATUS_FAILED))
# endif
# if !defined (CanIf_Dem_ReportPassed)
# define CanIf_Dem_ReportPassed(EventId)          ((void)Dem_ReportErrorStatus((EventId), DEM_EVENT_STATUS_PASSED))
# endif
#else
# define CanIf_Dem_ReportError(EventId)
# define CanIf_Dem_ReportPassed(EventId)
#endif

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# define CanIf_Det_ReportError(APIID, ErrorCode)  (Det_ReportError(CANIF_MODULE_ID, 0, (APIID), (ErrorCode)))
#else
# define CanIf_Det_ReportError(APIID, ErrorCode)
#endif

/* ParameterList: uint8 Hrh, PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc, Can_IdType CanId */
#if (CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON)
#define CanIf_Indirect_HlIndication(hrh, pduid, cansduptr, candlc, canid)     CanIf_HlIndication((hrh), (pduid), (cansduptr), (candlc), (canid))
#else
#define CanIf_Indirect_HlIndication(hrh, pduid, cansduptr, candlc, canid)     CanIf_HlIndication((hrh), (pduid), (cansduptr), (candlc))
#endif


#if (CANIF_ONE_CONTROLLER_OPTIMIZATION==STD_ON)
# define CANIF_CHANNEL_CANTYPE_FIRST 
# define CANIF_CHANNEL_CANTYPE_ONLY             void /* PRQA S 3460 */ /* MD_MSR_19.4 */
# define CANIF_CHANNEL_CANPARA_ONLY     
# define CANIF_CHANNEL_CANPARA_FIRST     
# define CanIf_Controller_Value                 0u
# define CANIF_CHANNEL_CANTYPE_LOCAL
# define CANIF_WUCHANNEL_CANTYPE_LOCAL
# define CanIf_Controller_Value_Local           0u
# define CanIf_WU_Controller_Value_Local        0u
# define CANIF_CFG_GENERIC_EMAXCONTROLLER       1u
# define CANIF_CFG_TX_ECONTROLLER               0u
# define CANIF_CFG_TX_ECONTROLLER_X             0u
# define CANIF_MAXCANCTRLOFALLIDENTITIES        1u
#else
# define CANIF_CHANNEL_CANTYPE_FIRST            uint8 Controller,   /* PRQA S 3460 */ /* MD_MSR_19.4 */
# define CANIF_CHANNEL_CANTYPE_ONLY             uint8 Controller    /* PRQA S 3460 */ /* MD_MSR_19.4 */
# define CANIF_CHANNEL_CANPARA_ONLY             Controller
# define CANIF_CHANNEL_CANPARA_FIRST            Controller,
# define CanIf_Controller_Value                 Controller
# define CANIF_CHANNEL_CANTYPE_LOCAL            uint8 controller;   /* PRQA S 3460 */ /* MD_MSR_19.4 */
# define CANIF_WUCHANNEL_CANTYPE_LOCAL          uint8 wuController; /* PRQA S 3460 */ /* MD_MSR_19.4 */
# define CanIf_Controller_Value_Local           controller
# define CanIf_WU_Controller_Value_Local        wuController
# define CANIF_CFG_GENERIC_EMAXCONTROLLER       CANIF_CFG_GENERIC(eMaxController)
# define CANIF_CFG_TX_ECONTROLLER               CANIF_CFG_TX(CanTxPduId, eController)
# define CANIF_CFG_TX_ECONTROLLER_X             CANIF_CFG_TX(PduId, eController)
# define CANIF_MAXCANCTRLOFALLIDENTITIES        CanIf_MaxCanCtrlOfAllIdentities
#endif

#if (CANIF_TRCV_HANDLING == STD_ON)
# if (CANIF_TRCV_MAPPING == STD_ON)
#  define CANIF_TRCVIDUPPER_TYPE_LOCAL           uint8 TrcvIdUpper; /* PRQA S 3460 */ /* MD_MSR_19.4 */
#  define CanIf_TrcvIdUpper_Local                TrcvIdUpper
# else
#  define CANIF_TRCVIDUPPER_TYPE_LOCAL
#   if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON)
#    define CanIf_TrcvIdUpper_Local              0u
#   else
#    define CanIf_TrcvIdUpper_Local              Transceiver
#   endif
# endif
#endif



#if defined (CANIF_ENABLE_SELECTABLE_PB)
  
# define CANIF_CFG                               (CanIf_Configuration)

# define CANIF_CFG_GENERIC(field)                (CanIf_Configuration->field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_CONTROLLER(index, field)      (CanIf_ControllerConfiguration[(index)]->field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_RX(index, field)              (CanIf_Configuration->eRxPduConfig[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */

# define CANIF_CFG_RX_MASK(index)                (CanIf_Configuration->eRxPduMask[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_RX_ID(index)                  (CanIf_Configuration->eRxPduId[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */

# define CANIF_CFG_TX(index, field)              (CanIf_Configuration->eTxPduConfig[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_TX_QUEUEINDEX(index)          (CanIf_Configuration->eTxPduQueueIndex[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_MAILBOX(index, field)         (CanIf_Configuration->eMailBoxConfig[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */

# define CANIF_CFG_WAKEUP(index, field)          (CanIf_Configuration->eWakeUpConfig[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */


# define CANIF_CFG_CONVERTPDU(index)             (CanIf_Configuration->eNPB2CanIfPduId[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_TRCVUPTOLOWMAP(index, field)  (CanIf_Configuration->eTransceiverMap[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_TXPDUMAP(index)               (CanIf_Configuration->eTxPduMap[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */

# define CANIF_CFG_RXDHRANDOMNUMBER1(index)      (CanIf_Configuration->eCanIf_RxDHRandomNumber1[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_RXDHRANDOMNUMBER2(index)      (CanIf_Configuration->eCanIf_RxDHRandomNumber2[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_RXDHADJUST(index)             (CanIf_Configuration->eCanIf_RxDHAdjust[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_RXDHADJUSTCOUNT               (CanIf_Configuration->eCanIf_RxDHAdjustcount) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_MAX_RXPDUHANDLE               (CanIf_Configuration->eMaxRxPDUHandle) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_STAT2DYN_INDIRECTION(index)   (CanIf_Configuration->eCanIf_TxPduStatic2DynamicIndirection[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_TXQUEUE_STARTINDEX(index)     (CanIf_Configuration->eCanIf_TxQueueStartIndex[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_TXQUEUE_PADBITS(index)        (CanIf_Configuration->eCanIf_TxQueuePadBits[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
/* table content: channel ( -> index) supports partial networking wakeup Tx Pdu filtering or not */
/* index == ControllerId */
# define CANIF_CFG_PNWUTXPDUFILTERACTIVE(index)  (CanIf_Configuration->eCanIf_ChWithPnWuTxPduFilterTbl[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
/* table content mapping transceiver id 2 controller id */
# define CANIF_CFG_TRCVTOCTRLMAP(index)         (CanIf_Configuration->eCanIf_TrcvToCtrlMap[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
/* table to convert local TrcvId 2 global TrcvId */
# define CANIF_CFG_TRCVUPTOUPPERMAP(index)       (CanIf_Configuration->eCanIf_TransceiverUpToUpperMap[(index)]) /* PRQA S 3410 */ /* MD_CanIf_19.10 */

/* # define CANIF_CFG_MAGIC()                       (*(CanIf_Configuration->eMagicNumber)) */

#else /* CANIF_ENABLE_SELECTABLE_PB */
/* Don't use () in macros -> Compiler */
# if (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON)
#  define CANIF_CFG                               (CanIf_Configuration)
# else
#  define CANIF_CFG                               (&CanIf_Config)
# endif

# if (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON)
#  define CANIF_CFG_GENERIC(field)                (CanIf_Configuration->field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# else
#  define CANIF_CFG_GENERIC(field)                (CanIf_Config.field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# endif

# define CANIF_CFG_CONTROLLER(index, field)      (CanIf_ControllerConfig[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */

# define CANIF_CFG_RX(index, field)              (CanIf_RxPduConfig[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_RX_MASK(index)                (CanIf_RxPduMask[(index)])
# define CANIF_CFG_RX_ID(index)                  (CanIf_RxPduId[(index)])


# define CANIF_CFG_TX(index, field)              (CanIf_TxPduConfig[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_TX_QUEUEINDEX(index)          (CanIf_TxPduQueueIndex[(index)])
# define CANIF_CFG_MAILBOX(index, field)         (CanIf_MailBoxConfig[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */

# if (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON)
#  define CANIF_CFG_WAKEUP(index, field)         (CanIf_Configuration->eWakeUpConfig[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# else
#  define CANIF_CFG_WAKEUP(index, field)         (CanIf_WakeUpConfig[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# endif /* (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON) */

# define CANIF_CFG_CONVERTPDU(index)             (CanIf_NPB2CanIfPduId[(index)])
# define CANIF_CFG_TRCVUPTOLOWMAP(index, field)  (CanIf_TransceiverUpToLowMap[(index)].field) /* PRQA S 3410 */ /* MD_CanIf_19.10 */
# define CANIF_CFG_TXPDUMAP(index)               (CanIf_TxPduMap[(index)])

# define CANIF_CFG_RXDHRANDOMNUMBER1(index)      (CanIf_RxDHRandomNumber1[(index)])
# define CANIF_CFG_RXDHRANDOMNUMBER2(index)      (CanIf_RxDHRandomNumber2[(index)])
# define CANIF_CFG_RXDHADJUST(index)             (CanIf_RxDHAdjust[(index)])

# if (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON)
#  define CANIF_CFG_RXDHADJUSTCOUNT               (CanIf_Configuration->eCanIf_RxDHAdjustcount)
#  define CANIF_CFG_MAX_RXPDUHANDLE               (CanIf_Configuration->eMaxRxPDUHandle)
# else
#  define CANIF_CFG_RXDHADJUSTCOUNT               (CanIf_Config.eCanIf_RxDHAdjustcount)
#  define CANIF_CFG_MAX_RXPDUHANDLE               (CanIf_Config.eMaxRxPDUHandle)
# endif /* (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON) */

# define CANIF_CFG_STAT2DYN_INDIRECTION(index)   (CanIf_TxPduStatic2DynamicIndirection[(index)])
# define CANIF_CFG_TXQUEUE_STARTINDEX(index)     (CanIf_TxQueueStartIndex[(index)])
# define CANIF_CFG_TXQUEUE_PADBITS(index)        (CanIf_TxQueuePadBits[(index)])

/* table content: channel ( -> index) supports partial network or not */
/* index == ControllerId */
# define CANIF_CFG_PNWUTXPDUFILTERACTIVE(index)  (CanIf_ChWithPnWuTxPduFilterTbl[(index)])
/* table content mapping transceiver id 2 controller id */
# define CANIF_CFG_TRCVTOCTRLMAP(TrcvId)         (CanIf_TrcvToCtrlMap[(TrcvId)])
/* table to convert local TrcvId 2 global TrcvId */
# define CANIF_CFG_TRCVUPTOUPPERMAP(index)       (CanIf_TransceiverUpToUpperMap[(index)])

/* # define CANIF_CFG_MAGIC()                     (CanIf_MagicNumber) */

#endif /* CANIF_ENABLE_SELECTABLE_PB */

#define CANIF_CFG_MAGIC()                        (*(CANIF_CFG_GENERIC(eMagicNumber)))

#define CANIF_CFG_RXINDICATION(index)            (CanIf_RxIndicationFctList[(index)])
#define CANIF_CFG_TXCONFIRMATION(index)          (CanIf_TxConfirmationFctList[(index)])
#define CANIF_CFG_BUSOFFNOTIFICATION()           (CanIf_BusOffNotificationFct)
#define CANIF_CFG_WAKEUPEVENT()                  (CanIf_WakeUpEventFct)
#define CANIF_CFG_WAKEUPVALIDATION()             (CanIf_WakeUpValidationFct)
#define CANIF_CFG_DLCERRORNOTIFICATION()         (CanIf_DlcErrorNotificationFct)

/* ESCAN00053264 */ /* ESCAN00055082 */
#define CanIf_EnterCritical(area)     SchM_Enter_CanIf(area)
#define CanIf_LeaveCritical(area)     SchM_Exit_CanIf(area)

#define CANIF_NOP      ((uint8)0xFFu)

#if (CANIF_BITQUEUE == STD_ON)
#if ( CPU_TYPE == CPU_TYPE_32 )
# define kCanTxQueueShift     5u
#endif
#if ( CPU_TYPE == CPU_TYPE_16 )
# define kCanTxQueueShift     4u
#endif
#if ( CPU_TYPE == CPU_TYPE_8 )
# define kCanTxQueueShift     3u
#endif

/* mask used to get the flag index from the handle */
# define kCanTxQueueMask      (((uint8)1u << kCanTxQueueShift) - (uint8)1u)
#endif
/*******************************************************************************************************************/
/*  Version check (generated data)                                                                                 */
/*******************************************************************************************************************/


/* Check version of the generated data */
#if (CANIF_SUPPRESS_CANIF_GENDATA_VERSION_CHECK == STD_OFF)

# if (CANIF_GENTOOL == CANIF_GENY)

# define GENTOOL_MAJOR_VERSION         IF_ASRIFCAN_GENTOOL_GENY_MAJOR_VERSION
# define GENTOOL_MINOR_VERSION         IF_ASRIFCAN_GENTOOL_GENY_MINOR_VERSION
# define GENTOOL_PATCH_VERSION         IF_ASRIFCAN_GENTOOL_GENY_PATCH_VERSION

/* Check major and minor Version only */
#  if (IF_ASRIFCAN_GENTOOL_GENY_MAJOR_VERSION != CANIF_GENTOOL_GENY_MAJOR_VERSION_REF)
#   error "Unexpected major version of generated data. Please check the version of the generator."
#  endif

/* Avoid version check for developer/beta versions */
#  if (IF_ASRIFCAN_GENTOOL_GENY_PATCH_VERSION != 0xFFu)
#   if (IF_ASRIFCAN_GENTOOL_GENY_MINOR_VERSION != CANIF_GENTOOL_GENY_MINOR_VERSION_REF)
#    error "Unexpected minor version of generated data. Please check the version of the generator."
#   endif
#  else
/* Increment minor version of GenTool for 0xFF Versions */
#   if ((IF_ASRIFCAN_GENTOOL_GENY_MINOR_VERSION + 1u) != CANIF_GENTOOL_GENY_MINOR_VERSION_REF)
#    error "Unexpected minor version of generated data. Please check the version of the generator."
#   endif
#  endif

# elif (CANIF_GENTOOL == CANIF_CFG5)

# define GENTOOL_MAJOR_VERSION         IF_ASRIFCAN_GENTOOL_CFG5_MAJOR_VERSION
# define GENTOOL_MINOR_VERSION         IF_ASRIFCAN_GENTOOL_CFG5_MINOR_VERSION
# define GENTOOL_PATCH_VERSION         IF_ASRIFCAN_GENTOOL_CFG5_PATCH_VERSION

/* Check major and minor Version only */
#  if (IF_ASRIFCAN_GENTOOL_CFG5_MAJOR_VERSION != CANIF_GENTOOL_CFG5_MAJOR_VERSION_REF)
#   error "Unexpected major version of generated data. Please check the version of the generator."
#  endif

/* Avoid version check for developer/beta versions */
#  if (IF_ASRIFCAN_GENTOOL_CFG5_PATCH_VERSION != 0xFFu)
#   if (IF_ASRIFCAN_GENTOOL_CFG5_MINOR_VERSION != CANIF_GENTOOL_CFG5_MINOR_VERSION_REF)
#    error "Unexpected minor version of generated data. Please check the version of the generator."
#   endif
#  else
/* Increment minor version of GenTool for 0xFF Versions */
#   if ((IF_ASRIFCAN_GENTOOL_CFG5_MINOR_VERSION + 1u) != CANIF_GENTOOL_CFG5_MINOR_VERSION_REF)
#    error "Unexpected minor version of generated data. Please check the version of the generator."
#   endif
#  endif
# else
#  error "Invalid generation tool!"
# endif
#endif



/*******************************************************************************************************************/
/*  Compatibility defines                                                                                          */
/*******************************************************************************************************************/

#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
#define CanIf_SetPduMode      CanIf_SetChannelMode
#endif


/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define CANIF_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

CONST(uint8, CANIF_CONST) CanIf_MainVersion         = CANIF_SW_MAJOR_VERSION;
CONST(uint8, CANIF_CONST) CanIf_SubVersion          = CANIF_SW_MINOR_VERSION;
CONST(uint8, CANIF_CONST) CanIf_ReleaseVersion      = CANIF_SW_PATCH_VERSION;

#define CANIF_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */




#define CANIF_START_SEC_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if !defined (V_SUPPRESS_EXTENDED_VERSION_CHECK)
CONST(uint32, CANIF_CONST) IF_ASRIFCAN_LIB_SYMBOL   = IF_ASRIFCAN_LIB_VERSION; /* PRQA S 3408 */ /* MD_CanIf_8.8 */
#endif

#define CANIF_STOP_SEC_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */




/*******************************************************************************************************************/
/*  local prototypes                                                                                               */
/*******************************************************************************************************************/

#define CANIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (CANIF_TRANSMIT_BUFFER == STD_ON)
/* static void CanIf_TxQueueTreatment(uint8 Controller); */
STATIC FUNC(Std_ReturnType, CANIF_CODE) CanIf_TxQueueTreatment(uint8 Controller);

/* static void CanIf_TxQueueTransmit(uint8 Controller, PduIdType PduId); */
STATIC FUNC(Std_ReturnType, CANIF_CODE) CanIf_TxQueueTransmit(CANIF_CHANNEL_CANTYPE_FIRST PduIdType PduId);
#endif

#if (CANIF_TRANSMIT_BUFFER == STD_ON)
/* Initialize and reset queue */
/* static void CanIf_ClearQueue(uint8 Controller); */
STATIC FUNC(void, CANIF_CODE) CanIf_ClearQueue(CANIF_CHANNEL_CANTYPE_ONLY);
#else 
# define CanIf_ClearQueue(x)
#endif

/* Handle DLC check, indication for upper layers */
#if (CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON)
/* static void CanIf_HlIndication(CanIf_HwHandleType Hrh, PduIdType PduId, const uint8 *CanSduPtr, uint8 CanDlc, Can_IdType CanId); */
STATIC FUNC(void, CANIF_CODE) CanIf_HlIndication(CanIf_HwHandleType  Hrh, PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc, Can_IdType CanId);
#else
STATIC FUNC(void, CANIF_CODE) CanIf_HlIndication(CanIf_HwHandleType  Hrh, PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc);
#endif

/* static void CanIf_HlTxConfirmation(PduIdType CanTxPduId); */
STATIC FUNC(void, CANIF_CODE) CanIf_HlTxConfirmation(PduIdType CanTxPduId);

#define CANIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*******************************************************************************************************************/
/*  local data definitions                                                                                         */
/*******************************************************************************************************************/

#if (CANIF_READRXPDUDATA_API == STD_ON)

#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* V_MEMRAM0 static V_MEMRAM1 SduPtrType V_MEMRAM2 CanIf_RxSduPtr; */
STATIC VAR(SduPtrType, CANIF_VAR_NOINIT) CanIf_RxSduPtr;

#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* CANIF_READRXPDUDATA_API */


#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* NOTE: additionally SWITCH CANIF_PN_TRCV_HANDLING used because CanSM does not have a corresponding SWITCH */
/* PRQA S 3218 1 */ /* MD_CanIf_8.7 */
STATIC CONST(uint8, CANIF_CONST) CanIfState[CANIF_NO_MODE_PDU_GET_MODE_TYPE_END][CANIF_NO_MODE_PDU_SET_MODE_TYPE_END] =
{
  /*actual state CANIF_GET_OFFLINE: */
  {
    (uint8)(CANIF_NOP),                     /* CANIF_SET_OFFLINE */
    (uint8)(CANIF_NOP),                     /* CANIF_SET_RX_OFFLINE */
    (uint8)(CANIF_GET_RX_ONLINE),           /* CANIF_SET_RX_ONLINE */
    (uint8)(CANIF_NOP),                     /* CANIF_SET_TX_OFFLINE */
    (uint8)(CANIF_GET_TX_ONLINE),           /* CANIF_SET_TX_ONLINE */
    (uint8)(CANIF_GET_ONLINE),              /* CANIF_SET_ONLINE */
    (uint8)(CANIF_GET_OFFLINE_ACTIVE)       /* CANIF_SET_TX_OFFLINE_ACTIVE */
#if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
                                         ,
    (uint8)(CANIF_GET_ONLINE_WAKF),        /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_TX_ONLINE_WAKF)      /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  },
  
  /*actual state CANIF_GET_RX_ONLINE: */
  {
    (uint8)(CANIF_GET_OFFLINE),                 /* CANIF_SET_OFFLINE */
    (uint8)(CANIF_GET_OFFLINE),                 /* CANIF_SET_RX_OFFLINE */
    (uint8)(CANIF_NOP),                         /* CANIF_SET_RX_ONLINE */
    (uint8)(CANIF_NOP),                         /* CANIF_SET_TX_OFFLINE */
    (uint8)(CANIF_GET_ONLINE),                  /* CANIF_SET_TX_ONLINE */
    (uint8)(CANIF_GET_ONLINE),                  /* CANIF_SET_ONLINE */
    (uint8)(CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) /* CANIF_SET_TX_OFFLINE_ACTIVE */
#if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
                                       ,
    (uint8)(CANIF_GET_ONLINE_WAKF),             /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_ONLINE_WAKF)              /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  },
  
  /*actual state CANIF_GET_TX_ONLINE: */
  {
    (uint8)(CANIF_GET_OFFLINE),       /* CANIF_SET_OFFLINE */
    (uint8)(CANIF_NOP),               /* CANIF_SET_RX_OFFLINE */
    (uint8)(CANIF_GET_ONLINE),        /* CANIF_SET_RX_ONLINE */
    (uint8)(CANIF_GET_OFFLINE),       /* CANIF_SET_TX_OFFLINE */
    (uint8)(CANIF_NOP),               /* CANIF_SET_TX_ONLINE */
    (uint8)(CANIF_GET_ONLINE),        /* CANIF_SET_ONLINE */
    (uint8)(CANIF_GET_OFFLINE_ACTIVE) /* CANIF_SET_TX_OFFLINE_ACTIVE */
#if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
                      ,
    (uint8)(CANIF_GET_ONLINE_WAKF),   /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_TX_ONLINE_WAKF) /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  },
    
  /*actual state CANIF_GET_ONLINE: */
  {
    (uint8)(CANIF_GET_OFFLINE),                 /* CANIF_SET_OFFLINE */
    (uint8)(CANIF_GET_TX_ONLINE),               /* CANIF_SET_RX_OFFLINE */
    (uint8)(CANIF_NOP),                         /* CANIF_SET_RX_ONLINE */
    (uint8)(CANIF_GET_RX_ONLINE),               /* CANIF_SET_TX_OFFLINE */
    (uint8)(CANIF_NOP),                         /* CANIF_SET_TX_ONLINE */
    (uint8)(CANIF_NOP),                         /* CANIF_SET_ONLINE */
    (uint8)(CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) /* CANIF_SET_TX_OFFLINE_ACTIVE */
#if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
                      ,
    (uint8)(CANIF_GET_ONLINE_WAKF),             /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_ONLINE_WAKF)              /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  },
    
  /*actual state CANIF_GET_OFFLINE_ACTIVE: */
  { 
    (uint8)(CANIF_GET_OFFLINE),                  /* CANIF_SET_OFFLINE */
    (uint8)(CANIF_NOP),                          /* CANIF_SET_RX_OFFLINE */
    (uint8)(CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE), /* CANIF_SET_RX_ONLINE */
    (uint8)(CANIF_GET_OFFLINE),                  /* CANIF_SET_TX_OFFLINE */
    (uint8)(CANIF_GET_TX_ONLINE),                /* CANIF_SET_TX_ONLINE */
    (uint8)(CANIF_GET_ONLINE),                   /* CANIF_SET_ONLINE */
    (uint8)(CANIF_NOP)                           /* CANIF_SET_TX_OFFLINE_ACTIVE */
#if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
                      ,
    (uint8)(CANIF_GET_ONLINE_WAKF),              /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_TX_ONLINE_WAKF)            /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  } ,
        
  /*actual state CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE: */
  {
    (uint8)(CANIF_GET_OFFLINE),        /* CANIF_SET_OFFLINE */
    (uint8)(CANIF_GET_OFFLINE_ACTIVE), /* CANIF_SET_RX_OFFLINE */
    (uint8)(CANIF_NOP),                /* CANIF_SET_RX_ONLINE */
    (uint8)(CANIF_GET_RX_ONLINE),      /* CANIF_SET_TX_OFFLINE */
    (uint8)(CANIF_GET_ONLINE),         /* CANIF_SET_TX_ONLINE */
    (uint8)(CANIF_GET_ONLINE),         /* CANIF_SET_ONLINE */
    (uint8)(CANIF_NOP)                 /* CANIF_SET_TX_OFFLINE_ACTIVE */
#if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
                      ,
    (uint8)(CANIF_GET_ONLINE_WAKF),    /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_ONLINE_WAKF)     /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  }

#if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
  ,

  /* actual state CANIF_GET_ONLINE_WAKF: */
  {
    (uint8)(CANIF_GET_OFFLINE),                  /* CANIF_SET_OFFLINE */
    (uint8)(CANIF_GET_TX_ONLINE_WAKF),           /* CANIF_SET_RX_OFFLINE */
    (uint8)(CANIF_NOP),                          /* CANIF_SET_RX_ONLINE */
    (uint8)(CANIF_GET_RX_ONLINE),                /* CANIF_SET_TX_OFFLINE */
    (uint8)(CANIF_GET_ONLINE),                   /* CANIF_SET_TX_ONLINE */
    (uint8)(CANIF_GET_ONLINE),                   /* CANIF_SET_ONLINE */
    (uint8)(CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE), /* CANIF_SET_TX_OFFLINE_ACTIVE */
    (uint8)(CANIF_NOP),                          /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_NOP)                           /* CANIF_SET_TX_ONLINE_WAKF */
  },

  /* actual state CANIF_GET_TX_ONLINE_WAKF: */
  {
    (uint8)(CANIF_GET_OFFLINE),          /* CANIF_SET_OFFLINE */
    (uint8)(CANIF_NOP),                  /* CANIF_SET_RX_OFFLINE */
    (uint8)(CANIF_GET_ONLINE_WAKF),      /* CANIF_SET_RX_ONLINE */
    (uint8)(CANIF_GET_OFFLINE),          /* CANIF_SET_TX_OFFLINE */
    (uint8)(CANIF_GET_TX_ONLINE),        /* CANIF_SET_TX_ONLINE */
    (uint8)(CANIF_GET_ONLINE),           /* CANIF_SET_ONLINE */
    (uint8)(CANIF_GET_OFFLINE_ACTIVE),   /* CANIF_SET_TX_OFFLINE_ACTIVE */
    (uint8)(CANIF_GET_ONLINE_WAKF),      /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_NOP)                   /* CANIF_SET_TX_ONLINE_WAKF */
  }
#endif
};




#if (CANIF_BITQUEUE == STD_ON)
/* lookup table for setting the flags in the queue */
STATIC CONST(CanIf_TxQueueFlagType, CANIF_CONST) CanShiftLookUp[1 << kCanTxQueueShift] = 
{
  (CanIf_TxQueueFlagType)0x00000001u, (CanIf_TxQueueFlagType)0x00000002u, (CanIf_TxQueueFlagType)0x00000004u, (CanIf_TxQueueFlagType)0x00000008u, 
  (CanIf_TxQueueFlagType)0x00000010u, (CanIf_TxQueueFlagType)0x00000020u, (CanIf_TxQueueFlagType)0x00000040u, (CanIf_TxQueueFlagType)0x00000080u

#if ( CPU_TYPE > CPU_TYPE_8 ) 
 ,(CanIf_TxQueueFlagType)0x00000100u, (CanIf_TxQueueFlagType)0x00000200u, (CanIf_TxQueueFlagType)0x00000400u, (CanIf_TxQueueFlagType)0x00000800u, 
  (CanIf_TxQueueFlagType)0x00001000u, (CanIf_TxQueueFlagType)0x00002000u, (CanIf_TxQueueFlagType)0x00004000u, (CanIf_TxQueueFlagType)0x00008000u
#endif

#if ( CPU_TYPE > CPU_TYPE_16 )
 ,(CanIf_TxQueueFlagType)0x00010000u, (CanIf_TxQueueFlagType)0x00020000u, (CanIf_TxQueueFlagType)0x00040000u, (CanIf_TxQueueFlagType)0x00080000u, 
  (CanIf_TxQueueFlagType)0x00100000u, (CanIf_TxQueueFlagType)0x00200000u, (CanIf_TxQueueFlagType)0x00400000u, (CanIf_TxQueueFlagType)0x00800000u,
  (CanIf_TxQueueFlagType)0x01000000u, (CanIf_TxQueueFlagType)0x02000000u, (CanIf_TxQueueFlagType)0x04000000u, (CanIf_TxQueueFlagType)0x08000000u, 
  (CanIf_TxQueueFlagType)0x10000000u, (CanIf_TxQueueFlagType)0x20000000u, (CanIf_TxQueueFlagType)0x40000000u, (CanIf_TxQueueFlagType)0x80000000u
#endif
};
#endif 

#define CANIF_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#if ((defined (CANIF_ENABLE_SELECTABLE_PB)) || (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON))
# define CANIF_START_SEC_VAR_INIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* V_MEMRAM0 static V_MEMROM1 CanIf_ConfigType V_MEMROM2 V_MEMROM3* V_MEMRAM1 V_MEMRAM2 CanIf_Configuration; */
STATIC P2CONST(CanIf_ConfigType, CANIF_VAR_INIT, CANIF_PBCFG) CanIf_Configuration = NULL_PTR;

# define CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif /* CANIF_ENABLE_SELECTABLE_PB || (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON)*/


#define CANIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (CANIF_TRANSMIT_BUFFER == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_ClearQueue()
| CALLED BY:        CAN Interface
| PRECONDITIONS:    none
| INPUT PARAMETERS: CANIF_CHANNEL_CANTYPE_ONLY: Controller (in case of optimization one channel -> void)
| RETURN VALUES:    none
| DESCRIPTION:      Initialize queue for specified controller
*******************************************************************************************************************/
/* void CanIf_ClearQueue(uint8 Controller); */
STATIC FUNC(void, CANIF_CODE) CanIf_ClearQueue(CANIF_CHANNEL_CANTYPE_ONLY)
{
# if (CANIF_BITQUEUE == STD_ON)
  uint8 queueElementIdx;
# else
  PduIdType TxBCStartIndex;
  PduIdType TxBCStopIndex;
  PduIdType PduId;
# endif

# if (CANIF_BITQUEUE == STD_ON)
  for(queueElementIdx = CANIF_CFG_TXQUEUE_STARTINDEX(CanIf_Controller_Value); queueElementIdx < CANIF_CFG_TXQUEUE_STARTINDEX(CanIf_Controller_Value+1); queueElementIdx++)
  { 
    canIf_TxQueueFlags[queueElementIdx] = (CanIf_TxQueueFlagType)0;
  } 
# else

  CanIf_TxQueueCounter[CanIf_Controller_Value] = 0;

  /* Loop over all normal Tx PDU IDs of requested controller */
  TxBCStartIndex = CANIF_CFG_CONTROLLER(CanIf_Controller_Value, eTxBCStartIndex);
  TxBCStopIndex = CANIF_CFG_CONTROLLER(CanIf_Controller_Value, eTxBCStopIndex);

  for (PduId = TxBCStartIndex; PduId < TxBCStopIndex; PduId++) 
  {
    CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(PduId)].eQueued = 0;
  }
# endif
}
#endif  /* CANIF_TRANSMIT_BUFFER */


/*******************************************************************************************************************
| NAME:             CanIf_Init()
| SID:              0x01
| CALLED BY:        upper layer
| PRECONDITIONS:    All controllers in CANIF_CS_UNINIT or CANIF_CS_STOPPED mode
| INPUT PARAMETERS: const CanIf_ConfigType *ConfigPtr: Pointer to global configuration struct
| RETURN VALUES:    none
| DESCRIPTION:      Global initialisation of CAN Interface and CAN Driver
*******************************************************************************************************************/
/* void CanIf_Init(V_MEMROM1 CanIf_ConfigType V_MEMROM2 V_MEMROM3 *ConfigPtr) */
FUNC(void, CANIF_CODE) CanIf_Init( P2CONST(CanIf_ConfigType, AUTOMATIC, CANIF_PBCFG) ConfigPtr )
{
  CANIF_CHANNEL_CANTYPE_LOCAL

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if ((defined (CANIF_ENABLE_SELECTABLE_PB)) || (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON))
  /*  Check if ConfigPtr is valid */
  if (ConfigPtr == NULL_PTR) 
  {
    CanIf_Det_ReportError(CANIF_INIT_API, CANIF_E_PARAM_POINTER);
  } 
  else 
# endif /* (CANIF_ENABLE_SELECTABLE_PB) || (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON) */
#endif
  {
    /* Store Pointer to initialization */
#if ((defined (CANIF_ENABLE_SELECTABLE_PB)) || (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON))
    CanIf_Configuration = ConfigPtr;
#else 
# if (V_USE_DUMMY_STATEMENT == STD_ON)
    ConfigPtr = ConfigPtr; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
# endif
#endif

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
    /* Now we can use the macros to access Gendata as ConfigPtr is correctly stored */
    if (CANIF_CFG_GENERIC(eMagic) != CANIF_MAGIC_NUMBER) 
    {
      CanIf_Det_ReportError(CANIF_INIT_API, CANIF_E_CONFIG);
    } 
    else if (CANIF_CFG_MAGIC() != CANIF_MAGIC_NUMBER)
    {
      /* 2nd Magic Number check ( Check for correct alignment/sizes of postbuild data ) */
      CanIf_Det_ReportError(CANIF_INIT_API, CANIF_E_CONFIG);
    }
    else if (CANIF_CFG_GENERIC(eVersion) != CANIF_GENDATA_VERSION)
    {
      /* Version Check */
      CanIf_Det_ReportError(CANIF_INIT_API, CANIF_E_CONFIG);
    }
    else
#endif  /* CANIF_DEV_ERROR_DETECT */
    {

#if (CANIF_READRXPDUDATA_API == STD_ON)
      CanIf_RxSduPtr = NULL_PTR;
#endif

#if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
      if(  ( (CANIF_CFG_GENERIC(eGeneratorVersion) & 0x00FFFF00u) !=
            ( ((uint32)GENTOOL_MAJOR_VERSION << 16) | ((uint32)GENTOOL_MINOR_VERSION << 8) ) )
#if (GENTOOL_PATCH_VERSION != 0u)
           || ( (CANIF_CFG_GENERIC(eGeneratorVersion) & 0x000000FFu) < GENTOOL_PATCH_VERSION )
#endif
        ) 
      {
        /* better cast to void, function may change its return value */
        (void)CanIf_GeneratorCompatibilityError();
      } 
      else 
#endif
      
#if (CANIF_CRC_CHECK == STD_ON)
      if (CANIF_CFG_GENERIC(eCanIfPrecompileCRC) != CANIF_PRECOMPILE_CRC)
      {
        (void)CanIf_GeneratorCompatibilityError();
      }
      else
      if (CANIF_CFG_GENERIC(eCanIfLinktimeCRC) != CanIf_LinktimeCRC)
      {
        (void)CanIf_GeneratorCompatibilityError();
      }
      else
#endif
      {
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
# if (CANIF_TRCV_HANDLING == STD_ON)
#  if (CANIF_TRCV_MAPPING == STD_ON)
        uint8         transceiver;
#  endif /* CANIF_TRCV_MAPPING */
# endif  /* CANIF_TRCV_HANDLING */
#endif   /* CANIF_COMPATIBILITY_AUTOSAR21  */

#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
        Can_Init(&CanConfig);

# if (CANIF_TRCV_HANDLING == STD_ON)
#  if (CANIF_TRCV_MAPPING == STD_ON)

        for (transceiver = 0; transceiver < CANIF_CFG_GENERIC(eMaxTransceivers) ; transceiver++) 
        {
          uint8                                 lowAddress;
          uint8                                 lowIndex;
          CanIf_CanTrcv_InitFctType             lowFct;
          /* Indirection here */
          lowIndex   = CANIF_CFG_TRCVUPTOLOWMAP(transceiver, eDriverIndex);

          /* Currently we loop over all tranceiver indexes and convert the to the driver index          */
          /* So we just do the initialization for index 0 for each Driver                               */

          if (lowIndex == 0) 
          {

            lowAddress = CANIF_CFG_TRCVUPTOLOWMAP(transceiver, eDriverAddress);

            lowFct      = CanIf_TransceiverAPICanTrcv_InitFctMap[lowAddress];

            /* ESCAN00031640 */
            if (lowFct == NULL_PTR) 
            {
              CanIf_Det_ReportError(CANIF_INIT_API, CANIF_TRCV_E_TRANSCEIVER);
            }
            else
            {
              (void)lowFct();
            }
          }
          else
          {
            /* TransceiverIndex not equal to 0, so this TransceiverDriver has been initialized previously */
          }
        }
#  else  /* CANIF_TRCV_MAPPING */
        (void)CanTrcv_Init();
#  endif /* CANIF_TRCV_MAPPING */
# endif  /* CANIF_TRCV_HANDLING */
#endif   /* CANIF_COMPATIBILITY_AUTOSAR21  */

#if (CANIF_SETDYNAMICTXID_API == STD_ON)
        {
          PduIdType DynamicPduId;
          PduIdType CanPduId;
          for(CanPduId = 0; CanPduId < CANIF_CFG_GENERIC(eMaxTxPDUHandle); CanPduId++)
          {
            DynamicPduId = CANIF_CFG_STAT2DYN_INDIRECTION(CanPduId);
            if(DynamicPduId != (PduIdType)0xFFFFFFFFu)
            {
              CanIf_DynTxId[DynamicPduId] = CANIF_CFG_TX(CanPduId, eId);
            }
          }
        }
#endif

        /* Initialisation of all controllers */
#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
        for (controller = 0; controller < CANIF_CFG_GENERIC_EMAXCONTROLLER; controller++) 
#endif
        {
          CanIf_ControllerSleepRequestPassed[CanIf_Controller_Value_Local] = TRUE;  /*no Sleep request failed yet*/
          /* Set controller state to stopped */
          CanIf_ControllerMode[CanIf_Controller_Value_Local] = CANIF_CS_STOPPED;
          CanIf_ChannelMode[CanIf_Controller_Value_Local] = CANIF_GET_OFFLINE;
          /* Init Controller ( Configuration Index not supported ) */
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
          CanIf_InitController(CanIf_Controller_Value_Local, &CANIF_CFG_GENERIC(eControllerConfig)[CanIf_Controller_Value_Local]);
#else
          CanIf_InitController(CanIf_Controller_Value_Local, 0);
#endif
        }
      }
    }   /* Check MagicNumbers and Gendata version */
  }   /* Check ConfigPtr == NULL_PTR */
}

/*******************************************************************************************************************
| NAME:             CanIf_InitController()
| SID:              0x02
| CALLED BY:        upper layer, CanIf_Init()
| PRECONDITIONS:    Controller in CANIF_CS_STOPPED mode
| INPUT PARAMETERS: uint8 CanNetwork, const CanIf_ControllerConfigType *ConfigPtr: Pointer to configuration
| RETURN VALUES:    none
| DESCRIPTION:      Controller initialisation of CAN Interface and CAN Driver
*******************************************************************************************************************/
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* void CanIf_InitController(uint8 CanNetwork, const CanIf_ControllerConfigType *ConfigPtr) */
FUNC(void, CANIF_CODE) CanIf_InitController(uint8 CanNetwork, P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_PBCFG) ConfigPtr) /* PRQA S 3206 */ /* MD_CanIf_Redundancy_NotUsed */
#else
/* void CanIf_InitController(uint8 Controller, uint8 ConfigurationIndex) */
FUNC(void, CANIF_CODE) CanIf_InitController(uint8 Controller, uint8 ConfigurationIndex) /* PRQA S 3206 */ /* MD_CanIf_Redundancy_NotUsed */
#endif
{
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
  uint8 Controller;

  Controller = CanNetwork;
#else
# if (V_USE_DUMMY_STATEMENT == STD_ON)
#   if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON)
  Controller = Controller; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
#   endif
  ConfigurationIndex = ConfigurationIndex; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */ /* Avoid compile warnings */
# endif
#endif

#if ((CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF))
  if (Controller >= CANIF_CFG_GENERIC_EMAXCONTROLLER) 
  {
    CanIf_Det_ReportError(CANIF_INITCONTROLLER_API, CANIF_E_PARAM_CONTROLLER);
  }
  else 
#endif
  {
    CanIf_ControllerSleepRequestPassed[CanIf_Controller_Value] = TRUE;  /*no Sleep request failed yet*/
    if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_STARTED) 
    {
      /* Explicitely cast to void as return value cannot be used here */
      (void)CanIf_SetControllerMode(CanIf_Controller_Value, CANIF_CS_STOPPED);
    }
#if (CANIF_DEV_ERROR_DETECT == STD_ON) 
    if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_UNINIT) 
    {
      /* CanIf_Init was not called */
      CanIf_Det_ReportError(CANIF_INITCONTROLLER_API, CANIF_E_UNINIT);
    }
#endif
    if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_STOPPED) 
    {

#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
# if defined (CANIF_ENABLE_SELECTABLE_PB)
      CanIf_ControllerConfiguration[CanIf_Controller_Value] = ConfigPtr;
# else
#  if (V_USE_DUMMY_STATEMENT == STD_ON)
      ConfigPtr = ConfigPtr; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
#  endif  
# endif
#else
# if defined (CANIF_ENABLE_SELECTABLE_PB)
      /* Store configuration for controller */
      CanIf_ControllerConfiguration[CanIf_Controller_Value] = &CANIF_CFG_GENERIC(eControllerConfig)[CanIf_Controller_Value];
# endif
#endif

#if (CANIF_WAKEUP_VALIDATION == STD_ON)
      /* Initialize Wakeup Validation */
      CanIf_WakeUpValidationState[CanIf_Controller_Value] = CANIF_WUVALIDATION_ARMED;
#endif

#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
      CanIf_ChPnWuTxPduFilterState[CanIf_Controller_Value] = CANIF_PN_WU_TXPDU_FILTER_DIS;
#endif

#if (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON)
      CanIf_TxConfirmationState[CanIf_Controller_Value] = CANIF_NO_NOTIFICATION;
#endif

      /* Reset Transmit Queue */
      CanIf_ClearQueue(CANIF_CHANNEL_CANPARA_ONLY);

      /* Initialize CAN Controller */
      /* void Can_InitController( uint8 Controller, const Can_ControllerConfigType* Config ) */
      Can_InitController(CanIf_Controller_Value, &(CANIF_CFG_GENERIC(eCan_ControllerConfig)[CanIf_Controller_Value]));
    }
  }    /* Controller invalid (DET) */
}


/*******************************************************************************************************************
| NAME:             CanIf_SetControllerMode()
| SID:              0x3
| CALLED BY:        upper layer
| PRECONDITIONS:    CAN Interrupts are not disabled
| INPUT PARAMETERS: uint8 CanNetwork, CanIf_ControllerModeType ControllerMode: mode transition
| RETURN VALUES:    Result of state transition
| DESCRIPTION:      Execute state transition of network mode of a controller
*******************************************************************************************************************/
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_SetControllerMode(uint8 CanNetwork, CanIf_ControllerModeType ControllerMode); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerMode(uint8 CanNetwork, CanIf_ControllerModeType ControllerMode)
#else
/* Std_ReturnType CanIf_SetControllerMode(uint8 Controller, CanIf_ControllerModeType ControllerMode) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerMode(uint8 Controller, CanIf_ControllerModeType ControllerMode)
#endif
{
  Std_ReturnType retval;

#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
  uint8 Controller = CanNetwork;
#endif
  retval = E_NOT_OK;
# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF))
  Controller = Controller;
#endif
  /* Check parameters */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (Controller >= CANIF_CFG_GENERIC_EMAXCONTROLLER) 
  {
    CanIf_Det_ReportError(CANIF_SETCONTROLLERMODE_API, CANIF_E_PARAM_CONTROLLER);
  } 
  else 
#endif
  {
    /* return E_OK if controller is in state CANIF_CS_UNINIT */
    if (CanIf_ControllerMode[CanIf_Controller_Value] != CANIF_CS_UNINIT) 
    {
      /* return E_NOT_OK if requested device mode already active */
      CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_0);
      if (CanIf_ControllerMode[CanIf_Controller_Value] != ControllerMode) 
      {
        /* requested mode */
        switch (ControllerMode) 
        {
          case CANIF_CS_UNINIT:
            /* return E_NOT_OK */
            break;
          case CANIF_CS_STOPPED:
            /* Call wakeup if currently in sleep mode */
            if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_SLEEP) 
            {
#if (CANIF_EXTENDED_STATE_MACHINE == STD_ON)
              /* Do not allow SLEEP -> STOP transition */
#else
              /* CAN Driver transition to WakeUp and Stop required if WakeUp is initiated by application */
              if (Can_SetControllerMode(CanIf_Controller_Value, CAN_T_WAKEUP) == CAN_OK) 
              {
                if (Can_SetControllerMode(CanIf_Controller_Value, CAN_T_STOP) == CAN_OK) 
                {
                  /* Set channel mode to offline */
                  CanIf_ChannelMode[CanIf_Controller_Value] = CANIF_GET_OFFLINE;
                  /* Set network mode */
                  /* SET to STOP Mode */
                  CanIf_ControllerMode[CanIf_Controller_Value] = CANIF_CS_STOPPED;
                  retval = E_OK;
                } 
                else 
                {
                  /* retval already set to E_NOT_OK as default */
                }
              }
#endif
            } 
            /* Call stop if currently in running mode */
            else if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_STARTED) 
            {
              if (Can_SetControllerMode(CanIf_Controller_Value, CAN_T_STOP) == CAN_OK) 
              {
                /* Set channel mode to offline */
                if (CanIf_SetPduMode(CanIf_Controller_Value, CANIF_SET_OFFLINE) == E_OK) 
                {
                  /* Set network mode */
                  CanIf_ControllerMode[CanIf_Controller_Value] = CANIF_CS_STOPPED;

#if (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON)
                  /* CANIF739 */
                  /* TxConfirmationState is reset always when CAN controller is stopped
                   * - BusOff
                   * - Going to _SLEEP
                   * - CanIf_InitController() is called
                   * */
                  CanIf_TxConfirmationState[CanIf_Controller_Value] = CANIF_NO_NOTIFICATION;
#endif
                  retval = E_OK;
                } 
                else 
                {
                  /* retval already set to E_NOT_OK as default */
                }
              }
            } 
            else 
            {
              /* CAN Interface in invalid mode */
            }

            break;
          case CANIF_CS_STARTED:
            /* Transition only possible from CANIF_CS_STOPPED mode */
            if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_STOPPED) 
            {
              if (CanIf_ControllerSleepRequestPassed[CanIf_Controller_Value] == FALSE)    /*Sleeprequest was not successful*/
              {
                if (Can_SetControllerMode(CanIf_Controller_Value, CAN_T_WAKEUP) == CAN_OK) 
                {
                  CanIf_ControllerSleepRequestPassed[CanIf_Controller_Value] = TRUE;
                  if (Can_SetControllerMode(CanIf_Controller_Value, CAN_T_START) == CAN_OK) 
                  {
                    CanIf_ControllerMode[CanIf_Controller_Value] = CANIF_CS_STARTED;
                    retval = E_OK;
                  } 
                }
              }
              else
              {
                if (Can_SetControllerMode(CanIf_Controller_Value, CAN_T_START) == CAN_OK) 
                {
                  CanIf_ControllerMode[CanIf_Controller_Value] = CANIF_CS_STARTED;
                  retval = E_OK;
                } 
                else 
                {
                  /* retval already set to E_NOT_OK as default */
                }
              }
            }
#if (CANIF_EXTENDED_STATE_MACHINE == STD_ON)
            else if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_SLEEP) 
            {
              /* SLEEP -> STARTED allowed */
              if (Can_SetControllerMode(CanIf_Controller_Value, CAN_T_WAKEUP) == CAN_OK) 
              {
                /* Set channel mode to offline */
                CanIf_ChannelMode[CanIf_Controller_Value] = CANIF_GET_OFFLINE;
                /* Set network mode */
                CanIf_ControllerMode[CanIf_Controller_Value] = CANIF_CS_STARTED;
                retval = E_OK;
              }
            }
#endif
            else 
            {
              /* Transition not allowed */
              /* E_NOT_OK already set */
            }
            break;
          case CANIF_CS_SLEEP:
#if (CANIF_EXTENDED_STATE_MACHINE == STD_OFF)
            CanIf_ControllerSleepRequestPassed[CanIf_Controller_Value] = FALSE;
            /* Transition from STARTED TO STOPPED first */
            if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_STARTED)
            {
              if (Can_SetControllerMode(CanIf_Controller_Value, CAN_T_STOP) == CAN_OK) 
              {
                /* Set channel mode to offline */
                if (CanIf_SetPduMode(CanIf_Controller_Value, CANIF_SET_OFFLINE) == E_OK) 
                {
                  /* Set network mode */
                  CanIf_ControllerMode[CanIf_Controller_Value] = CANIF_CS_STOPPED;
                } 
                else 
                {
                  /* retval already set to E_NOT_OK as default */
                }
              }
            }
            /* CanIf_ControllerMode is now CANIF_CS_STOPPED unless an error occured 
                -> E_NOT_OK still set in case of uncomplete transition */
#endif
            if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_STOPPED) 
            {
#if (CANIF_EXTENDED_STATE_MACHINE == STD_ON)
              /* STOP -> SLEEP not allowed, E_NOT_OK already set */
            } 
            else if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_STARTED) 
            {
              /* START -> SLEEP allowed */
              /* Clear the Queue first - CanIf should be in Offline mode already */
              (void)CanIf_SetPduMode(CanIf_Controller_Value, CANIF_SET_OFFLINE);
#endif
#if (CANIF_WAKEUP_VALIDATION == STD_ON)
              /* CANIF756 / SREQ00007740: Reset wake up validation state -> we are going to sleep again */
              CanIf_WakeUpValidationState[CanIf_Controller_Value] = CANIF_WUVALIDATION_ARMED;
#endif

              if (Can_SetControllerMode(CanIf_Controller_Value, CAN_T_SLEEP) == CAN_OK) 
              {
                CanIf_ControllerMode[CanIf_Controller_Value] = CANIF_CS_SLEEP;
                CanIf_ControllerSleepRequestPassed[CanIf_Controller_Value] = TRUE;
                retval = E_OK;
              } 
              else 
              {
                /* retval is already set to E_NOT_OK */
              }
            } 
            else
            {
              /* Transition not allowed */
              /* E_NOT_OK already set */
            }
            break;
          default: /* PRQA S 2018 */ /* MD_CanIf_14.1 */
            retval = E_NOT_OK;
            break;
        }
      } 
      else 
      {
        /* CanIf already in requested state */
        retval = E_OK;
      }
      CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_0);
    }
  }
  return retval;
}


/*******************************************************************************************************************
| NAME:             CanIf_GetControllerMode()
| SID:              0x04
| CALLED BY:        upper layer
| PRECONDITIONS:    CanInterface is initialized
| INPUT PARAMETERS: uint8 CanNetwork, CanIf_ControllerModeType  *ControllerModePtr
| RETURN VALUES:    network mode of controller
| DESCRIPTION:      Execute state transition of a controller
*******************************************************************************************************************/
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_GetControllerMode(uint8 CanNetwork, CanIf_ControllerModeType *ControllerModePtr); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerMode(uint8 CanNetwork, P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) ControllerModePtr)
#else
/* Std_ReturnType CanIf_GetControllerMode(uint8 Controller, CanIf_ControllerModeType *ControllerModePtr) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerMode(uint8 Controller, P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) ControllerModePtr)
#endif
{
  Std_ReturnType retval;

#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
  uint8 Controller;

  Controller = CanNetwork;
#endif
#if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF))
  Controller = Controller;
#endif
  retval = E_NOT_OK;
  /* Deviation: No check for state uninit of CanIf simply return state */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (Controller >= CANIF_CFG_GENERIC_EMAXCONTROLLER ) 
  {
    /* Check CanNetwork parameter is valid */
    CanIf_Det_ReportError(CANIF_GETCONTROLLERMODE_API, CANIF_E_PARAM_CONTROLLER);
  }
# if defined (CANIF_ENABLE_SELECTABLE_PB)
  else if (CANIF_CFG == NULL_PTR) 
  {
    CanIf_Det_ReportError(CANIF_GETCONTROLLERMODE_API, CANIF_E_PARAM_POINTER);
  } 
# endif
  else if (ControllerModePtr == NULL_PTR) 
  {
    CanIf_Det_ReportError(CANIF_GETCONTROLLERMODE_API, CANIF_E_PARAM_POINTER);
  } 
  else 
#endif
  {
    *ControllerModePtr = CanIf_ControllerMode[CanIf_Controller_Value];
    retval = E_OK;
  }
  return retval;
}

/*******************************************************************************************************************
| NAME:             CanIf_Transmit()
| SID:              0x05
| CALLED BY:        upper layer
| PRECONDITIONS:    CAN Interface initialized
| INPUT PARAMETERS: PduIdType CanTxPduId: Handle of Tx PDU, 
|                   const PduInfoType *PduInfoPtr: PDU Info (Data length, data ptr)
| RETURN VALUES:    Result of transmission request
| DESCRIPTION:      Initiate transmission of a Tx PDU
*******************************************************************************************************************/
/* Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Transmit(PduIdType CanTxPduId, P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_MSG_VAR)PduInfoPtr)
{
  Can_PduType     localPdu;
  Std_ReturnType  retval;
#if CANIF_SETDYNAMICTXID_API == STD_ON
  PduIdType     DynamicPduId;
#endif
  CANIF_CHANNEL_CANTYPE_LOCAL
#if (CANIF_BITQUEUE == STD_ON)
  sint8_least queueElementIdx;
# if ((CANIF_TRANSMIT_CANCELLATION == STD_OFF) && (CANIF_OPTIMIZE_TX_WITH_SHORT_PIA_GAP == STD_OFF)) /* ESCAN00061759 */
  sint8_least queueEndElementIdx;
# endif
  uint8 elementBitIdx;
  PduIdType queueBitPos;
#endif  
  retval = E_NOT_OK;
  /* Check if CanTxPduId is valid */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (CanTxPduId >= CANIF_CFG_GENERIC(eMaxTxPDUHandle)) 
  {
    CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_PARAM_LPDU);
  } 
  else if (PduInfoPtr == NULL_PTR) 
  {
    CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_PARAM_POINTER);
  } 
  else
#endif
  {
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
    CanIf_TransmitStateType pnTxState;
    uint8 pnPduLength;
    pnTxState = CANIF_DO_TRANSMIT;
#endif

#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
    /* Collect configuration data */
    controller = CANIF_CFG_TX_ECONTROLLER;
#endif

    /* CANIF747 */
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
    /* Get the DLC, can include PnWuFlag */
    pnPduLength = CANIF_CFG_TX(CanTxPduId, eLength);

    /* CANIF748 */
    if (CANIF_PN_WU_TXPDU_FILTER_SUPP == CANIF_CFG_PNWUTXPDUFILTERACTIVE(CanIf_Controller_Value_Local))
    {
      /* CANIF750 */
      if (CANIF_PN_WU_TXPDU_FILTER_EN == CanIf_ChPnWuTxPduFilterState[CanIf_Controller_Value_Local])
      {
        if (0u == (pnPduLength & CANIF_PN_WU_FLAG_GET))
        {
          /* TxPdu does not pass the PnWuFilter -> transmission not allowed */
          pnTxState = CANIF_DO_NOT_TRANSMIT;
        }
      }
    }

    /* Check whether transmission is allowed or not */
    if (CANIF_DO_TRANSMIT == pnTxState)
#endif
    {
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
      if (CanIf_ControllerMode[CanIf_Controller_Value_Local] == CANIF_CS_UNINIT)
      {
        CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_UNINIT);
      }
      else
#endif
      {
        /* Check network mode */
        if (CanIf_ControllerMode[CanIf_Controller_Value_Local] == CANIF_CS_STARTED)
        {
          /* Check Channel mode */
          if (
               (CanIf_ChannelMode[CanIf_Controller_Value_Local] == CANIF_GET_ONLINE) ||
               (CanIf_ChannelMode[CanIf_Controller_Value_Local] == CANIF_GET_TX_ONLINE)
# if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
            || (CanIf_ChannelMode[CanIf_Controller_Value_Local] == CANIF_GET_ONLINE_WAKF)
            || (CanIf_ChannelMode[CanIf_Controller_Value_Local] == CANIF_GET_TX_ONLINE_WAKF)
# endif
             )
          {
            Can_ReturnType txResult;
            CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_4);

#if (CANIF_SETDYNAMICTXID_API == STD_ON)
            DynamicPduId = CANIF_CFG_STAT2DYN_INDIRECTION(CanTxPduId);
            if(DynamicPduId != (PduIdType)0xFFFFFFFFu)
            {
              (localPdu).id = CanIf_DynTxId[DynamicPduId];
            }
            else
            {
              (localPdu).id = CANIF_CFG_TX(CanTxPduId, eId);
            }
#else
            (localPdu).id = CANIF_CFG_TX(CanTxPduId, eId);
#endif
#if (CANIF_DYNAMIC_TX_DLC == STD_ON)
            (localPdu).length = (uint8)(PduInfoPtr->SduLength);
#else
# if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
            /* Mask out the PnWuFlag */
            (localPdu).length = (uint8)(CANIF_PN_WU_FLAG_MASK_OUT & pnPduLength);
# else
            (localPdu).length = CANIF_CFG_TX(CanTxPduId, eLength);
# endif
#endif
            (localPdu).sdu = (PduInfoPtr->SduDataPtr);
            (localPdu).swPduHandle = (CanTxPduId);

#if (CANIF_TRANSMIT_BUFFER == STD_ON) && (CANIF_OPTIMIZE_TX_WITH_SHORT_PIA_GAP == STD_OFF)
          /* Check if message is not a Tx Full CAN */
            if ( ( CanTxPduId >= CANIF_CFG_CONTROLLER(CanIf_Controller_Value_Local, eTxBCStartIndex) ) &&
                 ( CanTxPduId < CANIF_CFG_CONTROLLER(CanIf_Controller_Value_Local, eTxBCStopIndex ) )  )
            {  /* Queue the data / Overwrite data in Queue / always queue it also in empty queue to avoid quing after write return busy */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
              if ( (localPdu.sdu == NULL_PTR) && (localPdu.length != 0) )
              {
                CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_PARAM_POINTER);
              }
              else
# endif
              { /* Queue information */
# if (CANIF_USES_VSTDLIB_COPY != STD_ON)
                PduLengthType i;
# endif

# if (CANIF_TRANSMIT_CANCELLATION == STD_OFF)
#  if(CANIF_BITQUEUE == STD_ON)
                  CanIf_TxQueueFlagType localQueueCount = 0;
                  queueEndElementIdx = (sint8_least)(CANIF_CFG_TXQUEUE_STARTINDEX(CanIf_Controller_Value_Local));
                  /* process from last to first */
                  for(queueElementIdx = CANIF_CFG_TXQUEUE_STARTINDEX(CanIf_Controller_Value_Local+1)-1; queueElementIdx >= queueEndElementIdx; queueElementIdx--)
                  {
                    localQueueCount = canIf_TxQueueFlags[queueElementIdx];
                    if (localQueueCount != 0)
                    {
                      break;
                    }
                  }
#  else
                PduIdType localQueueCount;
                localQueueCount = CanIf_TxQueueCounter[CanIf_Controller_Value_Local];
#  endif /* (CANIF_BITQUEUE == STD_ON) */
# endif  /* (CANIF_TRANSMIT_CANCELLATION == STD_OFF) */
                CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eSduLength = localPdu.length;
# if (CANIF_USES_VSTDLIB_COPY == STD_ON)
                VStdMemCpyRamToRam(CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eSdu, localPdu.sdu, localPdu.length);
# else
                for (i = 0; i < localPdu.length; i++)
                {
                  CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eSdu[i] = localPdu.sdu[i];
                }
# endif
                /* Set queue flag for current PDU and return E_OK */
                /* Mark queued element */
# if (CANIF_BITQUEUE == STD_ON)
                queueBitPos  = CanTxPduId + CANIF_CFG_TXQUEUE_PADBITS(CanIf_Controller_Value_Local);
                queueElementIdx = (uint8)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
                elementBitIdx  = (uint8)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
                if( (canIf_TxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) == (CanIf_TxQueueFlagType)0 )
                {
                  canIf_TxQueueFlags[queueElementIdx] |= CanShiftLookUp[elementBitIdx];
                }
# else
                if (CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eQueued == 0)
                {
                  CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eQueued = 1;
                  CanIf_TxQueueCounter[CanIf_Controller_Value_Local] ++;
                }
# endif
                else
                {
                  /* Tx Buffer for this PduId busy - data is overwritten - queue flag already set */
# if (CANIF_DEMTODET_E_FULL_TX_BUFFER == STD_ON)
                  /* Only reported if development error detection is activated (by macro definition) */
                  CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_FULL_TX_BUFFER);
# else
                  CanIf_Dem_ReportError(CANIF_INDIRECT_E_FULL_TX_BUFFER);
# endif
                }
# if (CANIF_TRANSMIT_CANCELLATION == STD_OFF)
                if( localQueueCount != 0 ) /* queue was not empty and no internal PIA supported
                                              --> so send request out of confirmation will follow in queue handling */
                {
                  retval = E_OK; /*message is queued*/
                }
                else
# endif
                { /*retval = E_OK for CAN_OK or CAN_BUSY / E_NOT_OK for CAN_NOT_OK */
                  retval = CanIf_TxQueueTreatment(CanIf_Controller_Value_Local); /*send out of queue for internal PIA - trigger possible cancelation*/
                }
              } /* Development error check SduDataPtr == NULL_PTR */
            }
            else
            { /* Tx object is FullCAN (will not be queued) - do direct Tx */
#else       /* no Tx Buffer -                              do always direct Tx*/
              {
#endif
                /* (const Can_PduType*) cast required (No Compiler abstraction, target is on stack (RAM)
                const to mark it read-only / CA cast (-> to get the const )                          */
                txResult = Can_Write(CANIF_CFG_TX(CanTxPduId, eHth), (P2CONST(Can_PduType, AUTOMATIC, CANIF_VAR_STACK))&localPdu);
                if (txResult == CAN_BUSY)
                { /* Tx Object busy */
#if (CANIF_TRANSMIT_BUFFER == STD_ON) && (CANIF_OPTIMIZE_TX_WITH_SHORT_PIA_GAP == STD_ON)
                  /* Check if message is not a Tx Full CAN */
                  if ( ( CanTxPduId >= CANIF_CFG_CONTROLLER(CanIf_Controller_Value_Local, eTxBCStartIndex) ) &&
                     ( CanTxPduId < CANIF_CFG_CONTROLLER(CanIf_Controller_Value_Local, eTxBCStopIndex ) )  )
                  {
                    /* Queue the data / Overwrite data in Queue*/
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
                    if ( (localPdu.sdu == NULL_PTR) && (localPdu.length != 0) )
                    {
                      CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_PARAM_POINTER);
                    }
                    else
# endif
                    {
                      /* Queue information */
# if (CANIF_USES_VSTDLIB_COPY != STD_ON)
                      PduLengthType i;
# endif
                      CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eSduLength = localPdu.length;
# if (CANIF_USES_VSTDLIB_COPY == STD_ON)
                      VStdMemCpyRamToRam(CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eSdu, localPdu.sdu, localPdu.length);
# else
                      for (i = 0u; i < localPdu.length; i++)
                      {
                        /* PRQA S 0505 1 */ /* MD_CanIf_1.2 */
                        CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eSdu[i] = localPdu.sdu[i];
                      }
# endif
                      /* Set queue flag for current PDU and return E_OK */


                      /* Mark queued element */
# if (CANIF_BITQUEUE == STD_ON)
                      queueBitPos  = CanTxPduId + CANIF_CFG_TXQUEUE_PADBITS(CanIf_Controller_Value_Local);
                      queueElementIdx = (uint8)(queueBitPos >> kCanTxQueueShift);
                      elementBitIdx  = (uint8)(queueBitPos & kCanTxQueueMask);
                      if( (canIf_TxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) == (CanIf_TxQueueFlagType)0 )
                      {
                        canIf_TxQueueFlags[queueElementIdx] |= CanShiftLookUp[elementBitIdx];
                      }
# else
                      if (CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eQueued == 0u)
                      {
                        CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eQueued = 1u;
                        CanIf_TxQueueCounter[CanIf_Controller_Value_Local]++;
                      }
# endif
                      else
                      {
                        /* Tx Buffer for this PduId busy - data is overwritten - queue flag already set */
# if (CANIF_DEMTODET_E_FULL_TX_BUFFER == STD_ON)
                        /* Only reported if development error detection is activated (by macro definition) */
                        CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_FULL_TX_BUFFER);
# else
                        CanIf_Dem_ReportError(CANIF_INDIRECT_E_FULL_TX_BUFFER);
# endif
                      }
                      retval = E_OK;
                    } /* Development error check SduDataPtr == NULL_PTR */
                  }
                  else 
                  {
                    /* Tx object busy - FullCAN will not be queued */
                    retval = E_NOT_OK;
                  }
#else /* (CANIF_TRANSMIT_BUFFER == STD_ON) && (CANIF_OPTIMIZE_TX_WITH_SHORT_PIA_GAP == STD_ON) */
                  /* Tx Object busy */
# if (CANIF_DEMTODET_E_FULL_TX_BUFFER == STD_ON)
                  /* Only reported if development error detection is activated (by macro definition) */
                  CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_FULL_TX_BUFFER);
# else
                  CanIf_Dem_ReportError(CANIF_INDIRECT_E_FULL_TX_BUFFER);
# endif
#endif /* (CANIF_TRANSMIT_BUFFER == STD_ON) && (CANIF_OPTIMIZE_TX_WITH_SHORT_PIA_GAP == STD_ON) */
                  }
                  else if (txResult == CAN_NOT_OK)
                  { /* Can_Write failed */
                    retval = E_NOT_OK;
                  }
                  else
                  {
                    /* ESCAN00061139 - start */
#if ((CANIF_TRANSMIT_BUFFER == STD_ON) && (CANIF_OPTIMIZE_TX_WITH_SHORT_PIA_GAP == STD_ON))
                    /* Do clear the TxPdu queued flag of the transmitted BasicCAN-TxPdu */
                    if ( ( CanTxPduId >= CANIF_CFG_CONTROLLER(CanIf_Controller_Value_Local, eTxBCStartIndex) ) &&
                         ( CanTxPduId < CANIF_CFG_CONTROLLER(CanIf_Controller_Value_Local, eTxBCStopIndex ) ) )
                    {
# if (CANIF_BITQUEUE == STD_ON)
                      queueBitPos  = CanTxPduId + CANIF_CFG_TXQUEUE_PADBITS(CanIf_Controller_Value_Local);
                      queueElementIdx = (uint8)(queueBitPos >> kCanTxQueueShift);
                      elementBitIdx  = (uint8)(queueBitPos & kCanTxQueueMask);
                      canIf_TxQueueFlags[queueElementIdx] &= ~CanShiftLookUp[elementBitIdx];
# else
                      if (CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eQueued == 1u)
                      {
                        CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(CanTxPduId)].eQueued = 0u;
                        --CanIf_TxQueueCounter[CanIf_Controller_Value_Local];
                      }
# endif
                    }
#endif
                    /* ESCAN00061139 - end */

                    retval = E_OK;
                  }
                }
                CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_4);
              }
              else if ( (CanIf_ChannelMode[CanIf_Controller_Value_Local] == CANIF_GET_OFFLINE_ACTIVE) ||
                        (CanIf_ChannelMode[CanIf_Controller_Value_Local] == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) )
              {
                retval = E_OK;
                /* Choose destination for Tx Confirmation */
                CanIf_HlTxConfirmation(CanTxPduId);
              } 
              else 
              { /* Nothing to do, else required for MISRA */
                /* default retval = E_NOT_OK; */
              }
            }
            else 
            {
              /* STOPPED, possibly uninit if DevErrorDetection is not enabled */
#if (CANIF_DEMTODET_E_STOPPED == STD_ON)
              /* Only reported if development error detection is activated (by macro definition) */
              CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_STOPPED);
#else
              CanIf_Dem_ReportError(CANIF_INDIRECT_E_STOPPED);
#endif
              /* default   retval = E_NOT_OK; */
            }
        }
      }
    }
  return retval;
}


/*******************************************************************************************************************
| NAME:             CanIf_HlTxConfirmation()
| SID:              0x13
| CALLED BY:        CAN Driver
| PRECONDITIONS:    CAN Interface initialized
| INPUT PARAMETERS: PduIdType CanTxPduId: Handle of Tx PDU
| RETURN VALUES:    none
| DESCRIPTION:      Confirmation for a successful transmission
*******************************************************************************************************************/
/* static void CanIf_HlTxConfirmation(PduIdType CanTxPduId) */
STATIC FUNC(void, CANIF_CODE) CanIf_HlTxConfirmation(PduIdType CanTxPduId) 
{
  uint8 index;
  CanIf_TxConfirmationFctType txConfirmationFct;

  
  index = CANIF_CFG_TX(CanTxPduId, eTxConfirmation);


  txConfirmationFct = CANIF_CFG_TXCONFIRMATION(index);

  if (txConfirmationFct != NULL_PTR) 
  {
#if (CANIF_ENABLE_TX_LPDU_REMAPPING == STD_ON)
    PduIdType mappedPduId;
    mappedPduId = CANIF_CFG_TX(CanTxPduId, eMappedPduId);
    txConfirmationFct(mappedPduId);
#else
    txConfirmationFct(CanTxPduId);
#endif
  }
}


/*******************************************************************************************************************
| NAME:             CanIf_TxConfirmation()
| SID:              0x13
| CALLED BY:        CAN Driver
| PRECONDITIONS:    CAN Interface initialized
| INPUT PARAMETERS: PduIdType CanTxPduId: Handle of Tx PDU
| RETURN VALUES:    none
| DESCRIPTION:      Confirmation for a successful transmission
*******************************************************************************************************************/
/* void CanIf_TxConfirmation(PduIdType CanTxPduId) */
FUNC(void, CANIF_CODE) CanIf_TxConfirmation(PduIdType CanTxPduId)
{

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (CanTxPduId >=  CANIF_CFG_GENERIC(eMaxTxPDUHandle)) 
  {
    CanIf_Det_ReportError(CANIF_TXCONFIRMATION_API, CANIF_E_PARAM_LPDU);
  } 
  else if (CanIf_ControllerMode[CANIF_CFG_TX_ECONTROLLER] == CANIF_CS_UNINIT ) 
  {
    CanIf_Det_ReportError(CANIF_TXCONFIRMATION_API, CANIF_E_UNINIT);
  } 
  else 
#endif
  {
    if (CanIf_ControllerMode[CANIF_CFG_TX_ECONTROLLER] == CANIF_CS_STARTED) 
    {
      if (
           (CanIf_ChannelMode[CANIF_CFG_TX_ECONTROLLER] == CANIF_GET_ONLINE)   ||
           (CanIf_ChannelMode[CANIF_CFG_TX_ECONTROLLER] == CANIF_GET_TX_ONLINE)
# if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
        || (CanIf_ChannelMode[CANIF_CFG_TX_ECONTROLLER] == CANIF_GET_ONLINE_WAKF)
        || (CanIf_ChannelMode[CANIF_CFG_TX_ECONTROLLER] == CANIF_GET_TX_ONLINE_WAKF)
# endif
         )
      {
#if ((CANIF_PN_WU_TX_PDU_FILTER == STD_ON) || (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON))
        CANIF_CHANNEL_CANTYPE_LOCAL
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
        controller = CANIF_CFG_TX(CanTxPduId, eController);
# endif
#endif

#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
        /*Tx message confirmed, deactivate Tx filter*/
        /* CANIF751 */
        CanIf_ChPnWuTxPduFilterState[CanIf_Controller_Value_Local] = CANIF_PN_WU_TXPDU_FILTER_DIS;
#endif

#if (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON)
        /* CANIF740 */
        CanIf_TxConfirmationState[CanIf_Controller_Value_Local] = CANIF_TX_RX_NOTIFICATION;
#endif

#if (CANIF_TRANSMIT_BUFFER == STD_ON)
        {
          /* Send queued messages directly if Normal Tx message was confirmed */
          PduIdType queueindex;
          queueindex = CANIF_CFG_TX_QUEUEINDEX(CanTxPduId);

          /* Check if queue is affected (Normal Tx object) */
          if (queueindex != (PduIdType)0xFFFFFFFFu)
          {
            /* Send queued messages directly */
            CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_2);
            (void)CanIf_TxQueueTreatment(CANIF_CFG_TX_ECONTROLLER);
            CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_2);  /*lock over queue handling + write call (driver does not expect direct call inbetween)*/
          }
        }
#endif

        CanIf_HlTxConfirmation(CanTxPduId);
      }
    }
  }
}

/*******************************************************************************************************************
| NAME:             CanIf_RxIndication()
| SID:              0x14
| CALLED BY:        CAN Driver
| PRECONDITIONS:    CAN Interface initialized
| INPUT PARAMETERS: uint8 Hrh: Handle of hardware object
|                   Can_IdType CanId: Id of receive message
|                   uint8 CanDlc: DLC of received message
|                   const uint8 *CanSduPtr: Pointer to data of received message
| RETURN VALUES:    none
| DESCRIPTION:      Find PDU ID of received messages
*******************************************************************************************************************/
/* void CanIf_RxIndication(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr) */
FUNC(void, CANIF_CODE) CanIf_RxIndication(CanIf_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR)CanSduPtr)
{
  PduIdType RxPduId;
#if (CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH)
  Can_IdType hash1;
  Can_IdType hash2;
#endif
#if ((CANIF_SEARCH_ALGORITHM == CANIF_BINARY) || (CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH))
  boolean continueSearch;
#endif
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (CanSduPtr == NULL_PTR) 
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, CANIF_E_PARAM_POINTER);
  } 
  else if (CanDlc > 8u)
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, CANIF_E_PARAM_DLC);
# if (CANIF_EXTENDEDID_SUPPORT != STD_ON)
  } 
  else if (CanId > 0x7FFu)
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, CANIF_E_PARAM_CANID);
# endif
  } 
  else if (Hrh >= CANIF_CFG_GENERIC(eMaxMailBox)) 
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, CANIF_E_PARAM_HRH);
  } 
  else 
#endif
  {
#if (CANIF_WAKEUP_VALIDATION == STD_ON)
# if (CANIF_WAKEUP_VALID_ALL_RX_MSGS == STD_ON)
    CANIF_CHANNEL_CANTYPE_LOCAL
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
    /* Acquire controller from CanIf_Mailbox struct */
    controller = CANIF_CFG_MAILBOX(Hrh, eController);
#  endif
    if (CanIf_ControllerMode[CanIf_Controller_Value_Local] == CANIF_CS_STARTED) 
    {
        /* SREQ00007759, All messages will be used for validation only in controller mode STARTED*/
        CanIf_WakeUpValidationState[CanIf_Controller_Value_Local] = CANIF_WUVALIDATION_DETECTED;
    }
# endif
#endif

    /* No Rx-Pdus or Ranges configured. Nothing to search. */
    if (CANIF_CFG_GENERIC(eMaxRxPDUHandle) != 0) 
    {

      RxPduId = CANIF_CFG_MAILBOX(Hrh, ePduIdLast);
      if (RxPduId != CanIf_RxPduHnd_INVALID)
      {
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
        if (RxPduId >= CANIF_CFG_GENERIC(eMaxRxPDUHandle)) 
        {
          CanIf_Det_ReportError(CANIF_RXINDICATION_API, CANIF_E_PARAM_LPDU);
        } 
        else 
#endif
        {
          if (CANIF_RxFullCANMailbox == CANIF_CFG_MAILBOX(Hrh, eMailBoxType)) 
          {
            /* Full CAN message */
            CanIf_Indirect_HlIndication(Hrh, RxPduId, CanSduPtr, CanDlc, CanId);
          } 
          else 
          {
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
            if (CANIF_RxBasicCANMailbox == CANIF_CFG_MAILBOX(Hrh, eMailBoxType)) 
            {
#endif
#if ((CANIF_SEARCH_ALGORITHM == CANIF_BINARY) || (CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH))
              /* Ranges message (searched linearly also in case of binary search) */
              continueSearch = TRUE;
              while  ( (CANIF_CFG_RX_MASK(RxPduId) & (CANIF_STOP_FLAG | CANIF_RANGE_FLAG)) == CANIF_RANGE_FLAG )  
              {
                if (CANIF_CFG_RX_ID(RxPduId) == (CanId & CANIF_CFG_RX_MASK(RxPduId)) ) 
                {
                  /* ID matches - Pdu identified */
                  CanIf_Indirect_HlIndication(Hrh, RxPduId, CanSduPtr, CanDlc, CanId);
                  continueSearch = FALSE;
                  break;
                }
                RxPduId--;
              }
              if ( (CANIF_CFG_RX_MASK(RxPduId) & (CANIF_STOP_FLAG | CANIF_RANGE_FLAG)) == (CANIF_STOP_FLAG | CANIF_RANGE_FLAG) ) 
              {
                /* End flag for Search algorithm is set, this means no more messages to search for */
                continueSearch = FALSE;
                if (CANIF_CFG_RX_ID(RxPduId) == (CanId & CANIF_CFG_RX_MASK(RxPduId)) ) 
                {
                  /* ID matches - Pdu identified */
                  CanIf_Indirect_HlIndication(Hrh, RxPduId, CanSduPtr, CanDlc, CanId);
                }
              }
#endif
#if (CANIF_SEARCH_ALGORITHM == CANIF_BINARY)
              if (continueSearch == TRUE)
              {

                PduIdType first;
                PduIdType last;
                PduIdType mid;
                PduIdType resultId;

                resultId = CanIf_RxPduHnd_INVALID;

                /* Get first and last object to search over */

                first = CANIF_CFG_MAILBOX(Hrh, ePduIdFirst);
                last = RxPduId;

                while (first <= last) 
                {
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
                  sint32 diffId;
# else
                  sint16 diffId;
# endif

                  mid = ((last + first) >> 1);

# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
                  diffId = (sint32)(CanId - CANIF_CFG_RX_ID(mid));

# else
                  diffId = (sint16)(CanId - CANIF_CFG_RX_ID(mid));
# endif
      
                
                  if (diffId == 0 ) 
                  {
                    resultId = mid;
                    break;
                  } 
                  if (diffId > 0) {
                    last = mid;
                  } 
                  else 
                  {
                    first = mid;
                  }

                  if((last - first) < 2)
                  {
                    if(CanId == CANIF_CFG_RX_ID(first))
                    {
                      resultId = first;
                      break; /* PRQA S 0771 */ /* MD_CanIf_14.6 */
                    } 
                    else if(CanId == CANIF_CFG_RX_ID(last))
                    { 
                      resultId = last;
                      break; /* PRQA S 0771 */ /* MD_CanIf_14.6 */
                    } 
                    else
                    {
                      break; /* PRQA S 0771 */ /* MD_CanIf_14.6 */
                    }
                  }
                }
                
                if (resultId != CanIf_RxPduHnd_INVALID) 
                {
                  CanIf_Indirect_HlIndication(Hrh, resultId, CanSduPtr, CanDlc, CanId);
                } 
                else 
                {
                  /* Not found - ignore received PDU */
                }
              }
#endif
#if (CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH)
              if (continueSearch == TRUE)
              {
                hash1 = ((CanId ^ CANIF_CFG_RXDHRANDOMNUMBER1(CANIF_CFG_MAILBOX(Hrh, eController))) % CANIF_CFG_RXDHADJUSTCOUNT);
                hash2 = ((CanId ^ CANIF_CFG_RXDHRANDOMNUMBER2(CANIF_CFG_MAILBOX(Hrh, eController))) % CANIF_CFG_RXDHADJUSTCOUNT);
                RxPduId = ((uint16)CANIF_CFG_RXDHADJUST(hash1)) + ((uint16)CANIF_CFG_RXDHADJUST(hash2));
                if (RxPduId >= CANIF_CFG_MAX_RXPDUHANDLE)
                {
                  RxPduId -= CANIF_CFG_MAX_RXPDUHANDLE;
                }
                if (CANIF_CFG_RX_ID(RxPduId) == CanId)
                {
                  /* ID matches - Pdu identified */
                  CanIf_Indirect_HlIndication(Hrh, RxPduId, CanSduPtr, CanDlc, CanId);
                }
              }
#endif
#if (CANIF_SEARCH_ALGORITHM == CANIF_LINEAR)
              /* Basic CAN message */
              /* Checked for invalid RxPduId earlier */
              do 
              {
                if (CANIF_CFG_RX_ID(RxPduId) == (CanId & CANIF_CFG_RX_MASK(RxPduId)) ) 
                {
                  /* ID matches - Pdu identified */
                  CanIf_Indirect_HlIndication(Hrh, RxPduId, CanSduPtr, CanDlc, CanId);
                  break;
                }
              }
              while ( ( (CANIF_CFG_RX_MASK(RxPduId--) & CANIF_STOP_FLAG) != CANIF_STOP_FLAG) );
              /* Index 0 in generated table ALWAYS has the STOP_FLAG set (see while condition), 
                 Underrun to 0xFFFF only in case of not matched -> RxPduId will not be used any more */
#endif

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
            } 
            else 
            {
              /* Hrh does not belong to Rx Mailbox */
              CanIf_Det_ReportError(CANIF_RXINDICATION_API, CANIF_E_CONFIG);
            }
#endif
          }
        }
      }
    }
  }
}


/*******************************************************************************************************************
| NAME:             CanIf_HlIndication()
| SID:              0x14
| CALLED BY:        CanIf_RxIndication
| PRECONDITIONS:    CAN Interface initialized
| INPUT PARAMETERS: CanIf_HwHandleType Hrh: Handle of hardware object
|                   Can_IdType CanId: Id of receive message
|                   uint8 CanDlc: DLC of received message
|                   const uint8 *CanSduPtr: Pointer to data of received message
| RETURN VALUES:    none
| DESCRIPTION:      DLC check, Call of user indication function
*******************************************************************************************************************/
#if (CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON)
/* static void CanIf_HlIndication(uint8 Hrh, PduIdType PduId, const uint8 *CanSduPtr, uint8 CanDlc, Can_IdType CanId) */
/* PRQA S 3206 1 */ /* MD_CanIf_Redundancy_NotUsed */
STATIC FUNC(void, CANIF_CODE) CanIf_HlIndication(CanIf_HwHandleType  Hrh, PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc, Can_IdType CanId)
#else
/* static void CanIf_HlIndication(uint8 Hrh, PduIdType PduId, const uint8 *CanSduPtr, uint8 CanDlc) */
/* PRQA S 3206 1 */ /* MD_CanIf_Redundancy_NotUsed */
STATIC FUNC(void, CANIF_CODE) CanIf_HlIndication(CanIf_HwHandleType  Hrh, PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc)
#endif
{
  CANIF_CHANNEL_CANTYPE_LOCAL

#if (V_USE_DUMMY_STATEMENT == STD_ON)
  /* Avoid compiler warnings as CanDlc is not used in all configurations */
  CanDlc = CanDlc; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON)
  /* ESCAN00051108 */
  Hrh = Hrh; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
# endif
#endif
#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
  /* Acquire controller from CanIf_Mailbox struct */
  controller = CANIF_CFG_MAILBOX(Hrh, eController);
#endif

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* ESCAN00051107 -> avoids compiler warning */
  if (CanIf_Controller_Value_Local >= CANIF_CFG_GENERIC_EMAXCONTROLLER) 
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, CANIF_E_CONFIG);
  }
  else
# endif /* (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) */
  if (CanIf_ControllerMode[CanIf_Controller_Value_Local] == CANIF_CS_UNINIT )
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, CANIF_E_UNINIT);
  } 
  else if (PduId >= CANIF_CFG_GENERIC(eMaxRxPDUHandle)) 
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, CANIF_E_PARAM_LPDU);
  }
  else
#endif
  {
    if (CanIf_ControllerMode[CanIf_Controller_Value_Local] == CANIF_CS_STARTED) 
    {

#if (CANIF_WAKEUP_VALIDATION == STD_ON)
# if (CANIF_WAKEUP_VALID_ALL_RX_MSGS != STD_ON)
      /* SREQ00007759: Only ECUs receive list will validate an Rx event / Controllermode: Started, PduMode: Don't care*/
      CanIf_WakeUpValidationState[CanIf_Controller_Value_Local] = CANIF_WUVALIDATION_DETECTED;
# endif
#endif
      if ( (CanIf_ChannelMode[CanIf_Controller_Value_Local] == CANIF_GET_ONLINE) ||
           (CanIf_ChannelMode[CanIf_Controller_Value_Local] == CANIF_GET_RX_ONLINE) ||
           (CanIf_ChannelMode[CanIf_Controller_Value_Local] == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE)
# if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
        || (CanIf_ChannelMode[CanIf_Controller_Value_Local] == CANIF_GET_ONLINE_WAKF)
# endif
         )
      {
#if (CANIF_DLC_CHECK == STD_ON)
        /* DLC check - if configured DLC == 0 the following condition is always false and DLC check is deactivated */
        if (CanDlc < CANIF_CFG_RX(PduId, eDlc) ) 
        {
# if (CANIF_USER_DLC_ERROR_NOTIFICATION == STD_ON)
          CanIf_DlcErrorNotifictionFctType dlcErrorNotification;
# endif          
# if (CANIF_DEM_REPORT_DLC_FAILED == STD_ON)
          /* Notification to DEM */
          CanIf_Dem_ReportError(CANIF_INDIRECT_E_INVALID_DLC);
# endif
# if (CANIF_USER_DLC_ERROR_NOTIFICATION == STD_ON)
          /* Notification to Application */
          dlcErrorNotification = CANIF_CFG_DLCERRORNOTIFICATION();
          if (dlcErrorNotification != NULL_PTR)
          {
            dlcErrorNotification(PduId);
          }
# endif
        } 
        else 
#endif

        {
#if (CANIF_READRXPDUDATA_API == STD_ON)
          /* Store Ptr to Sdu, set valid */
          CanIf_RxSduPtr = CanSduPtr;
#endif

          /* Parameter Check */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
          if ( CANIF_CFG_RX(PduId, eRxIndication) >= CANIF_CFG_GENERIC(eMaxRxIndication) ) 
          {
            CanIf_Det_ReportError(CANIF_RXINDICATION_API, CANIF_E_CONFIG);
          } 
          else 
#endif
          {
            uint8 index;
            index = CANIF_CFG_RX(PduId, eRxIndication);

            /* ESCAN00046190 */
#if (CANIF_RX_INDICATION_TYPE_I_IS_USED == STD_ON)
            if (CANIF_CFG_RXINDICATION(index).eRxIndicationLayout == CanIf_SimpleRxIndicationLayout) 
            {
              CanIf_SimpleRxIndicationFctType rxIndicationFct;
              rxIndicationFct = CANIF_CFG_RXINDICATION(index).eRxIndicationFct.eSimpleRxIndicationType;
              if (rxIndicationFct != NULL_PTR) 
              {
                /* CA cast (-> to get the const ) */
                /* CANIF_APPL_VAR -> located in CAN Driver */
                rxIndicationFct(CANIF_CFG_RX(PduId, eUpperPduId), (P2CONST(uint8, AUTOMATIC, CANIF_UL_STANDARD_VAR))CanSduPtr);
              }
            } 
            else
#endif

#if (CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON)
            if (CANIF_CFG_RXINDICATION(index).eRxIndicationLayout == CanIf_NmOsekRxIndicationLayout) 
            {
              CanIf_NmOsekRxIndicationFctType rxIndicationFct;
              rxIndicationFct = CANIF_CFG_RXINDICATION(index).eRxIndicationFct.eNmOsekRxIndicationType;
              if (rxIndicationFct != NULL_PTR) 
              {
                /* CA cast (-> to get the const ) */
                /* CANIF_APPL_VAR -> located in CAN Driver */
                rxIndicationFct(CANIF_CFG_RX(PduId, eUpperPduId), (P2CONST(uint8, AUTOMATIC, CANIF_UL_OSEKNM_VAR))CanSduPtr, CanId);
              }
            
            } 
            else
#endif
            if (CanIf_AdvancedRxIndicationLayout == CANIF_CFG_RXINDICATION(index).eRxIndicationLayout)
            {
              CanIf_AdvancedRxIndicationFctType rxIndicationFct;
              PduInfoType pduinfo;
              /* cast from CANIF_CBK_DRV_VAR to AUTOSAR_COMSTACKDATA --> has to be resolved in compiler abstraction configuration */
              /* const to non-const cast is not avoidable */
              /* PRQA S 0311 1*/ /* MD_CanIf_11.5 */
              pduinfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA))CanSduPtr;
#if (CANIF_RX_PASS_STATIC_DLC == STD_ON)
              /* old requirement: CANIF262: Predefined DLC is passed to upper layer not the currently received one */
              pduinfo.SduLength = CANIF_CFG_RX(PduId, Dlc);
#else
              /* new requirement: CANIF262: Currently received DLC value is passed to upper layer */
              pduinfo.SduLength = CanDlc;
#endif
              rxIndicationFct = CANIF_CFG_RXINDICATION(index).eRxIndicationFct.eAdvancedRxIndicationType;
              if (rxIndicationFct != NULL_PTR) 
              {
                /* CA cast (-> to get the const ) */
                /* PTR to Stack -> AUTOMATIC */
                rxIndicationFct(CANIF_CFG_RX(PduId, eUpperPduId), (P2CONST(PduInfoType, AUTOMATIC, CANIF_UL_ADVANCED_VAR))&pduinfo);
              }
            }
#if ((CANIF_RX_INDICATION_TYPE_I_IS_USED == STD_ON) || (CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON))
            else
            {
              /* Avoids MISRA warning */
            }
#endif
          }
# if (CANIF_READRXPDUDATA_API == STD_ON)
          /* Set invalid */
          CanIf_RxSduPtr = NULL_PTR;
# endif            
        }
      }
    }
  }
}

/*******************************************************************************************************************
| NAME:             CanIf_ControllerBusOff()
| SID:              0x16
| CALLED BY:        CAN Driver
| PRECONDITIONS:    -
| INPUT PARAMETERS: uint8 Controller: Controller
| RETURN VALUES:    none
| DESCRIPTION:      Indication of BusOff from CAN Driver
*******************************************************************************************************************/
/* void CanIf_ControllerBusOff(uint8 Controller) */
FUNC(void, CANIF_CODE) CanIf_ControllerBusOff(uint8 Controller)
{

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (Controller >= CANIF_CFG_GENERIC_EMAXCONTROLLER) 
  {
    CanIf_Det_ReportError(CANIF_CONTROLLERBUSOFF_API, CANIF_E_PARAM_CONTROLLER);
  } 
  else if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_UNINIT ) 
  {
    CanIf_Det_ReportError(CANIF_CONTROLLERBUSOFF_API, CANIF_E_UNINIT);
  } 
  else 
#endif
  {
    CanIf_BusOffNotificationFctType busoffnotificationFct;

    /* Explicitely cast to void as return value cannot be used here */
    /* CANIF739 is implemented in CanIf_SetControllerMode() */
    (void)CanIf_SetControllerMode(CanIf_Controller_Value, CANIF_CS_STOPPED);
    
    /*ESCAN00072535  with DrvCan__coreAsr Version >= 4.0.0 the CanIf PDU mode needs to be set explicit*/
    /*includes deletion of the Tx queue*/
    (void)CanIf_SetPduMode(CanIf_Controller_Value, CANIF_SET_OFFLINE);
    
    /* Set CAN Interface to Stopped mode, CAN Controller is BusOff */
    CanIf_ControllerMode[CanIf_Controller_Value] = CANIF_CS_STOPPED;


    busoffnotificationFct = CANIF_CFG_BUSOFFNOTIFICATION();

    if (busoffnotificationFct != NULL_PTR) {
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
      busoffnotificationFct((ComM_ChannelHandleType)CanIf_Controller_Value);
#else
      busoffnotificationFct(CanIf_Controller_Value);
#endif
    }
  }
#if ((CANIF_ONE_CONTROLLER_OPTIMIZATION==STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF) && (V_USE_DUMMY_STATEMENT == STD_ON))
  Controller = Controller; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
#endif
}



/*******************************************************************************************************************
| NAME:             CanIf_SetPduMode()
| SID:              0x09
| CALLED BY:        Application
| PRECONDITIONS:    CAN Interrupts are not disabled
| INPUT PARAMETERS: uint8 Channel, CanIf_ChannelRequestTypeChannelRequest
| RETURN VALUES:    none
| DESCRIPTION:      Set channel mode of specified channel
*******************************************************************************************************************/
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_SetChannelMode(uint8 Channel, CanIf_ChannelSetModeType ChannelRequest) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetChannelMode(uint8 Channel, CanIf_ChannelSetModeType ChannelRequest)
#else
/* Std_ReturnType CanIf_SetPduMode(uint8 Controller, CanIf_PduSetModeType PduModeRequest) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPduMode(uint8 Controller, CanIf_PduSetModeType PduModeRequest)
#endif
{
  Std_ReturnType retval;

#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
  /* Function parameter mapping */
  uint8                     Controller;
  CanIf_ChannelSetModeType  PduModeRequest;

  Controller      = Channel;
  PduModeRequest  = ChannelRequest;
#endif

  retval = E_NOT_OK;
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (Controller >= CANIF_CFG_GENERIC_EMAXCONTROLLER) 
  {
    CanIf_Det_ReportError(CANIF_SETPDUMODE_API, CANIF_E_PARAM_CONTROLLER);
  } 
  else if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_UNINIT) 
  {
    CanIf_Det_ReportError(CANIF_SETPDUMODE_API, CANIF_E_UNINIT);
  } 
  else 
#endif
  {
    /* Channel mode transitions only available in CANIF_CS_STARTED mode */
    if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_STARTED) 
    {
      retval = E_OK;
      CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_3);

      /* Do allow transitions if target mode is equal current mode */
      /* PRQA S 3689 1 */ /* MD_CanIf_21.1 */
      if(CanIfState[CanIf_ChannelMode[CanIf_Controller_Value]][PduModeRequest] != CANIF_NOP)
      {
        switch (PduModeRequest) 
        {
          case CANIF_SET_OFFLINE:
          case CANIF_SET_TX_OFFLINE:
          case CANIF_SET_TX_OFFLINE_ACTIVE:
            switch(CanIf_ChannelMode[CanIf_Controller_Value])
            {
              case CANIF_GET_TX_ONLINE:
              case CANIF_GET_ONLINE:
#if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)) /* ESCAN00057578 */
              case CANIF_GET_TX_ONLINE_WAKF:
              case CANIF_GET_ONLINE_WAKF:
#endif
                CanIf_ClearQueue(CANIF_CHANNEL_CANPARA_ONLY);
                break;
              default:
                break;
            }
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
            CanIf_ChPnWuTxPduFilterState[CanIf_Controller_Value] = CANIF_PN_WU_TXPDU_FILTER_DIS;
#endif
            break;
          case CANIF_SET_ONLINE:
          case CANIF_SET_TX_ONLINE:
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
            CanIf_ChPnWuTxPduFilterState[CanIf_Controller_Value] = CANIF_PN_WU_TXPDU_FILTER_DIS;
#endif
            break;
#if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
          case CANIF_SET_ONLINE_WAKF:
          case CANIF_SET_TX_ONLINE_WAKF:
# if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
            /* CANIF752 */
            if((CANIF_PN_WU_TXPDU_FILTER_SUPP == CANIF_CFG_PNWUTXPDUFILTERACTIVE(CanIf_Controller_Value)))
            {
              /* CANIF749 */
              CanIf_ChPnWuTxPduFilterState[CanIf_Controller_Value] = CANIF_PN_WU_TXPDU_FILTER_EN;
            }
# endif
            break;
#endif
          default:
            break;
        }
        /* PRQA S 3689 1 */ /* MD_CanIf_21.1 */
        CanIf_ChannelMode[CanIf_Controller_Value] = (CanIf_PduGetModeType)CanIfState[CanIf_ChannelMode[CanIf_Controller_Value]][PduModeRequest];
      }
      CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_3);
    }
  }
# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION==STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF) && (V_USE_DUMMY_STATEMENT == STD_ON))
  Controller = Controller; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
# endif
  return retval;
}

/*******************************************************************************************************************
| NAME:             CanIf_GetPduMode()
| SID:              0x0A
| CALLED BY:        Application
| PRECONDITIONS:    -
| INPUT PARAMETERS: uint8 Channel, CanIf_ChannelModeType *ChannelModePtr
| RETURN VALUES:    Std_ReturnType (E_OK, E_NOT_OK)
| DESCRIPTION:      Request channel mode of specified channel
*******************************************************************************************************************/
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_GetChannelMode(uint8 Channel, CanIf_ChannelGetModeType *ChannelModePtr) */
/* PRQA S 3206 1 */ /* MD_CanIf_Redundancy_NotUsed */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetChannelMode(uint8 Channel, P2VAR(CanIf_ChannelGetModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) ChannelModePtr)
#else
/* Std_ReturnType CanIf_GetPduMode(uint8 Controller, CanIf_PduGetModeType *PduModePtr) */
/* PRQA S 3206 1 */ /* MD_CanIf_Redundancy_NotUsed */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetPduMode(uint8 Controller, P2VAR(CanIf_PduGetModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) PduModePtr)
#endif
{
  Std_ReturnType retval;

#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
  uint8                   Controller;
  P2VAR(CanIf_PduGetModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) PduModePtr;

  Controller  = Channel;
  PduModePtr  = ChannelModePtr;
#endif
#if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (V_USE_DUMMY_STATEMENT == STD_ON))
  Controller = Controller; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
#endif
  /* Default return value */
  retval = E_NOT_OK;

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (CanIf_ControllerMode[CanIf_Controller_Value] == CANIF_CS_UNINIT) 
  {
    /* Channel mode unspecified in CANIF_CS_UNINIT mode */
    CanIf_Det_ReportError(CANIF_GETPDUMODE_API, CANIF_E_UNINIT);
  } 
# if defined (CANIF_ENABLE_SELECTABLE_PB)
  else if (CANIF_CFG == NULL_PTR) 
  {
    CanIf_Det_ReportError(CANIF_GETPDUMODE_API, CANIF_E_PARAM_POINTER);
  } 
# endif
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
  else if (Controller >= CANIF_CFG_GENERIC_EMAXCONTROLLER) 
  {
    CanIf_Det_ReportError(CANIF_GETPDUMODE_API, CANIF_E_PARAM_CONTROLLER);
  }
# endif
  else if (PduModePtr == NULL_PTR) 
  {
    CanIf_Det_ReportError(CANIF_GETPDUMODE_API, CANIF_E_PARAM_POINTER);
  } 
  else 
#endif
  {
    *PduModePtr = CanIf_ChannelMode[CanIf_Controller_Value];
    retval = E_OK;
  }
  return retval;
}

#if (CANIF_TRANSMIT_BUFFER == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_TxQueueTransmit()
| CALLED BY:        CanIf_TxQueueTreatment
| PRECONDITIONS:    critical section already entered (secure queue)
| INPUT PARAMETERS: CANIF_CHANNEL_CANTYPE_ONLY: Controller (in case of optimization one channel -> void),
|                   PduIdType PduId ( has to be a Normal Tx PDU )
| RETURN VALUES:    none
| DESCRIPTION:      Transmit message and remove from queue
*******************************************************************************************************************/
/* static void CanIf_TxQueueTransmit(uint8 Controller, PduIdType PduId) */
STATIC FUNC(Std_ReturnType, CANIF_CODE) CanIf_TxQueueTransmit(CANIF_CHANNEL_CANTYPE_FIRST PduIdType PduId)
{
  Can_PduType localPdu;
  Can_ReturnType txResult;
  Std_ReturnType retval;
# if CANIF_SETDYNAMICTXID_API == STD_ON
  PduIdType       DynamicPduId;
# endif
# if (CANIF_BITQUEUE == STD_ON)
  uint8 queueElementIdx;
  uint8 elementBitIdx;
  PduIdType queueBitPos;
# endif


# if (CANIF_SETDYNAMICTXID_API == STD_ON)
  DynamicPduId = CANIF_CFG_STAT2DYN_INDIRECTION(PduId);
  if(DynamicPduId != (PduIdType)0xFFFFFFFFu)
  {
    (localPdu).id = CanIf_DynTxId[DynamicPduId];
  }
  else
  {
    (localPdu).id = CANIF_CFG_TX(PduId, eId);
  }
# else
  (localPdu).id = CANIF_CFG_TX(PduId, eId);
# endif
# if (CANIF_DYNAMIC_TX_DLC == STD_ON)
  (localPdu).length = (uint8)CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(PduId)].eSduLength;
# else
#  if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
  (localPdu).length = (uint8)(CANIF_PN_WU_FLAG_MASK_OUT & CANIF_CFG_TX(PduId, eLength));
#  else
  (localPdu).length = CANIF_CFG_TX(PduId, eLength);
#  endif
# endif
  (localPdu).sdu = CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(PduId)].eSdu;
  (localPdu).swPduHandle = (PduId);

  txResult = Can_Write(CANIF_CFG_TX(PduId, eHth), &localPdu);
  if (txResult == CAN_OK) 
  { /*tx requested in hw*/
# if (CANIF_BITQUEUE == STD_ON)
    queueBitPos  = PduId + CANIF_CFG_TXQUEUE_PADBITS(CanIf_Controller_Value);
    queueElementIdx = (uint8)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
    elementBitIdx  = (uint8)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
    canIf_TxQueueFlags[queueElementIdx] &= ~CanShiftLookUp[elementBitIdx]; /* clear flag from the queue */
# else
    CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(PduId)].eQueued = 0;
    CanIf_TxQueueCounter[CanIf_Controller_Value]--;
# endif
    retval = E_OK;
  } 
  else if (txResult == CAN_BUSY)
  { /*also ok due to confirmation queue handling may be interrupted by canif_transmit() or just a cancel request*/
    retval = E_OK;
  }
  else /*CAN_NOT_OK*/
  {
    retval = E_NOT_OK;
  }
  return retval;
}
#endif



#if (CANIF_TRANSMIT_BUFFER == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_TxQueueTreatment()
| CALLED BY:        CanIf_TxConfirmation
| PRECONDITIONS:    critical section already entered (secure queue)
| INPUT PARAMETERS: uint8 Controller
| RETURN VALUES:    none
| DESCRIPTION:      Check if queued PDUs have to be transmitted
*******************************************************************************************************************/
/* static void CanIf_TxQueueTreatment(uint8 Controller) */
/* PRQA S 3206 1 */ /* MD_CanIf_Redundancy_NotUsed */
STATIC FUNC(Std_ReturnType, CANIF_CODE) CanIf_TxQueueTreatment(uint8 Controller)
{
  PduIdType PduId;
  Std_ReturnType retval;

# if (CANIF_BITQUEUE == STD_ON)
  /* FOR-loop: cnt.-variable */
  sint8_least queueElementIdx; 
  /* FOR-loop: stores the end-condition, improves performance */
  sint8_least queueEndElementIdx;
  sint8  elementBitIdx;
  CanIf_TxQueueFlagType  elem;
# endif

# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (V_USE_DUMMY_STATEMENT == STD_ON))
  Controller = Controller; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
# endif  
 
  retval = E_NOT_OK; /*default nothing to send*/

# if (CANIF_BITQUEUE == STD_ON)
   /* Get the end-condition of the following FOR-loop */
  queueEndElementIdx = (sint8_least)(CANIF_CFG_TXQUEUE_STARTINDEX(CanIf_Controller_Value));

  /* process from last to first */
  for(queueElementIdx = CANIF_CFG_TXQUEUE_STARTINDEX(CanIf_Controller_Value+1)-1; queueElementIdx >= queueEndElementIdx; queueElementIdx--)
  { 
    elem = canIf_TxQueueFlags[queueElementIdx];
    if(elem != (CanIf_TxQueueFlagType)0) /* is there any flag set in the queue element? */
    {
      /* iterate through all flags and notify application for every scheduled transmission */
      for(elementBitIdx = ((sint8)1 << kCanTxQueueShift) - (sint8)1; elementBitIdx >= (sint8)0; elementBitIdx--)
      { 
        if( ( elem & CanShiftLookUp[elementBitIdx] ) != (CanIf_TxQueueFlagType)0)
        {
          PduId = (((PduIdType)queueElementIdx << kCanTxQueueShift) + (PduIdType)elementBitIdx) - CANIF_CFG_TXQUEUE_PADBITS(CanIf_Controller_Value);
          /* Send and remove from queue */
          retval = CanIf_TxQueueTransmit(CANIF_CHANNEL_CANPARA_FIRST PduId);
          break;
        }
      }
    }
  }
# else
  if (CanIf_TxQueueCounter[CanIf_Controller_Value] != 0) 
  {
    /* CanIf_TxQueueCounter always 0 if CanIf_ControllerConfiguration[Controller]->TxStopIndex = 0 */
    for (PduId = CANIF_CFG_CONTROLLER(CanIf_Controller_Value, eTxBCStopIndex) - (PduIdType)1; PduId > CANIF_CFG_CONTROLLER(CanIf_Controller_Value, eTxBCStartIndex); PduId--) 
    {
      if (CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(PduId)].eQueued != 0) 
      {
        /* Send and remove from queue */
        retval = CanIf_TxQueueTransmit(CANIF_CHANNEL_CANPARA_FIRST PduId);
        break;
      }
    }
    /* Avoid usage of signed datatype for PduId */
    if (PduId == CANIF_CFG_CONTROLLER(CanIf_Controller_Value, eTxBCStartIndex)) 
    {
      if (CanIf_TxQueue[CANIF_CFG_TX_QUEUEINDEX(PduId)].eQueued != 0) 
      {
        /* Send and remove from queue */
        retval = CanIf_TxQueueTransmit(CANIF_CHANNEL_CANPARA_FIRST PduId);
      }
    }
  }
# endif
  return retval;
}
#endif

#if (CANIF_READRXPDUDATA_API == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_ReadRxPduData()
| SID:              0x06
| CALLED BY:        Upper layer
| PRECONDITIONS:    CanIf Initialized
| INPUT PARAMETERS: PduIdType CanRxPduId - specifies RxPpdu
|                   PduInfoType *PduInfoPtr - Pointer to struct to copy DLC and data to
| RETURN VALUES:    Std_ReturnType
| DESCRIPTION:      Provide DLC and data of the specified Pdu to upper layers
*******************************************************************************************************************/
/* Std_ReturnType CanIf_ReadRxPduData(PduIdType CanRxPduId, PduInfoType *PduInfoPtr) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ReadRxPduData(PduIdType CanRxPduId, P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_MSG_VAR) PduInfoPtr)
{
  Std_ReturnType retval;
  
  retval = E_NOT_OK;
  /* Check for valid parameters */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (CanRxPduId >= CANIF_CFG_GENERIC(eMaxRxPDUHandle)) 
  {
    CanIf_Det_ReportError(CANIF_READRXDATA_API, CANIF_E_PARAM_LPDU);
  } 
  else if (PduInfoPtr == NULL_PTR) 
  {
    CanIf_Det_ReportError(CANIF_READRXDATA_API, CANIF_E_PARAM_POINTER);
  } 
  else 
#endif
  {
    if (CanIf_RxSduPtr != NULL_PTR) 
    {
      uint8 len;
      /* Deviation: No check if CanIf is CANIF_CS_UNINIT for current controller, 
         we do not know which controller received this PDU */
      /* Same problem for the channel mode */
   
      /* Assuming a copy from a temp buffer in same memory section */
      len = CANIF_CFG_RX(CanRxPduId, eDlc);
      PduInfoPtr->SduLength = len;      
      while (len > 0) 
      {
        len--;
        PduInfoPtr->SduDataPtr[len] = CanIf_RxSduPtr[len];
      }
      retval = E_OK; 
    } 
    else 
    {
      /* RxData Invalid, HwBuffer or Temporary buffer can be overwritten */
    }
  }
  return retval;
}
#endif


#if (CANIF_VERSION_INFO_API == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_GetVersionInfo()
| SID:              0x0B
| CALLED BY:        Upper layer
| PRECONDITIONS:
| INPUT PARAMETERS: versioninfo - buffer to copy version info to
| RETURN VALUES:    Std_ReturnType
| DESCRIPTION:      Provide DLC and data of the specified Pdu to upper layers
*******************************************************************************************************************/
/* void CanIf_GetVersionInfo(Std_VersionInfoType *Versioninfo) */
FUNC(void, CANIF_CODE) CanIf_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_VAR) VersionInfo)
{
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (VersionInfo == NULL_PTR)
  {
    CanIf_Det_ReportError(CANIF_GETVERSIONINFO_API, CANIF_E_PARAM_POINTER);
  }
  else
# endif
  {
    VersionInfo->vendorID         = CANIF_VENDOR_ID;
    VersionInfo->moduleID         = CANIF_MODULE_ID;
    VersionInfo->instanceID       = 0;
    VersionInfo->sw_major_version = CANIF_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = CANIF_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = CANIF_SW_PATCH_VERSION;
  }
}
#endif



/*******************************************************************************************************************
| NAME:             CanIf_InitMemory()
| SID:              none
| CALLED BY:        Upper layer
| PRECONDITIONS:    
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Initializes global variables. This function has to be called
|                   before any other calls to the CanIf API
*******************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_InitMemory(void)
{
  CANIF_CHANNEL_CANTYPE_LOCAL
# if ((defined (CANIF_ENABLE_SELECTABLE_PB)) || (CANIF_IDENTITY_MANAGER_CONFIG == STD_ON))
  CanIf_Configuration = NULL_PTR;
# endif
#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
  for (controller = 0; controller < CANIF_MAXCANCTRLOFALLIDENTITIES; controller++)
#endif
  {
    CanIf_ControllerMode[CanIf_Controller_Value_Local] = CANIF_CS_UNINIT;
  }
}



#if (CANIF_TRANSMIT_BUFFER == STD_ON)
# if (CANIF_TRANSMIT_CANCELLATION == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_CancelTxConfirmation()
| SID:              0x15
| CALLED BY:        CAN Driver
| PRECONDITIONS:    CanInterface is initialized
|                   Valid PDU ID is passed
| INPUT PARAMETERS: const Can_PduType*
| RETURN VALUES:    none
| DESCRIPTION:      CanIf is indicated of a cancelled PDU by the driver
*******************************************************************************************************************/
/* void CanIf_CancelTxConfirmation(const Can_PduType* PduInfoPtr) */
FUNC(void, CANIF_CODE) CanIf_CancelTxConfirmation(P2CONST(Can_PduType, AUTOMATIC, CANIF_CBK_DRV_VAR) PduInfoPtr)
{
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (PduInfoPtr->swPduHandle >= CANIF_CFG_GENERIC(eMaxTxPDUHandle)) 
  {
    CanIf_Det_ReportError(CANIF_TXCONFIRMATION_API, CANIF_E_PARAM_LPDU);
  } 
  else if (CanIf_ControllerMode[CANIF_CFG_TX(PduInfoPtr->swPduHandle, eController)] == CANIF_CS_UNINIT ) 
  {
    CanIf_Det_ReportError(CANIF_TXCONFIRMATION_API, CANIF_E_UNINIT);
  } 
  else 
#endif
  {
    PduIdType queueindex;
    CANIF_CHANNEL_CANTYPE_LOCAL
#if (CANIF_BITQUEUE == STD_ON)
    uint8 queueElementIdx; /* index for accessing the tx queue */
    uint8 elementBitIdx;  /* bit index within the tx queue element */
    PduIdType queueBitPos;  /* physical bitposition of the handle */
#endif

#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
    controller = CANIF_CFG_TX(PduInfoPtr->swPduHandle, eController);
#endif

    /* Check if PduInfoPtr->swPduHandle is queued */
    queueindex = CANIF_CFG_TX_QUEUEINDEX(PduInfoPtr->swPduHandle);

    /* Check if queue is affected (Normal Tx object) */
    if (queueindex != (PduIdType)0xFFFFFFFFu)
    {
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
      if (queueindex >= CANIF_CFG_GENERIC(eMaxTxPDUHandle))
      {
        CanIf_Det_ReportError(CANIF_CANCELTRANSMIT_API, CANIF_E_PARAM_LPDU);
      } 
      else
#endif
      {
        CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_1); 
#if (CANIF_BITQUEUE == STD_ON)
        queueBitPos  = (PduInfoPtr->swPduHandle) + CANIF_CFG_TXQUEUE_PADBITS(CanIf_Controller_Value_Local);
        queueElementIdx = (uint8)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
        elementBitIdx  = (uint8)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
        if( (canIf_TxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) == (CanIf_TxQueueFlagType)0 )
        {
          PduLengthType len; 
          /* Buffer is free, store the cancelled one */
          canIf_TxQueueFlags[queueElementIdx] |= CanShiftLookUp[elementBitIdx];
#else
        if (CanIf_TxQueue[queueindex].eQueued == 0) 
        {
          PduLengthType len; 
          /* Buffer is free, store the cancelled one */
          CanIf_TxQueue[queueindex].eQueued = 1;
#endif


          CanIf_TxQueue[queueindex].eSduLength = PduInfoPtr->length;
          for (len = 0; len < PduInfoPtr->length; len++) 
          {
            CanIf_TxQueue[queueindex].eSdu[len] = PduInfoPtr->sdu[len];
          }
          /* Find appropriate controller for swPduHandle */
#if (CANIF_BITQUEUE == STD_OFF)  
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
          controller = CANIF_CFG_TX(PduInfoPtr->swPduHandle, eController);
# endif
          CanIf_TxQueueCounter[CanIf_Controller_Value_Local]++;
#endif
        }
        else
        {
          /* Newer PDU already queued, discard the cancelled one */
        }
        CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_1); 
      }
      /* Send queued messages directly */
      CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_2); 
      (void)CanIf_TxQueueTreatment(CANIF_CFG_TX(PduInfoPtr->swPduHandle, eController));
      CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_2);  /*lock over queue handling + write call (driver does not expect direct call inbetween)*/
    } 
    else 
    {
      /* Full CANs won't be cancelled */
    }
    
  }
}
# endif
#endif



#if (CANIF_CANCEL_SUPPORT_API == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_CancelTransmit()
| SID:              -
| CALLED BY:        Upper layer
| PRECONDITIONS:    CanInterface is initialized
|                   Valid PDU ID is passed
| INPUT PARAMETERS: PduIdType
| RETURN VALUES:    none
| DESCRIPTION:      Initiate cancellation of a TxPDU
*******************************************************************************************************************/
/* void CanIf_CancelTransmit(PduIdType CanTxPduId) */
FUNC(void, CANIF_CODE) CanIf_CancelTransmit(PduIdType CanTxPduId)
{
  /* Check if CanTxPduId is valid */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (CanTxPduId >= CANIF_CFG_GENERIC(eMaxTxPDUHandle)) 
  {
    CanIf_Det_ReportError(CANIF_CANCELTRANSMIT_API, CANIF_E_PARAM_LPDU);
  } 
  else
#endif
  {
    Can_HwHandleType  hth;
#if (CANIF_TRANSMIT_BUFFER == STD_ON)
    PduIdType         queueindex;
#endif
#if (CANIF_BITQUEUE == STD_ON)
    uint8 queueElementIdx; /* index for accessing the tx queue */
    uint8 elementBitIdx;  /* bit index within the tx queue element */
    PduIdType queueBitPos;  /* physical bitposition of the handle */
    CANIF_CHANNEL_CANTYPE_LOCAL
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
    /* Collect configuration data */
    controller = CANIF_CFG_TX_ECONTROLLER;
# endif
#endif
   
    hth = CANIF_CFG_TX(CanTxPduId, eHth);
#if (CANIF_TRANSMIT_BUFFER == STD_ON)
    /* Check if PDU has to be cancelled from queue */

    queueindex = CANIF_CFG_TX_QUEUEINDEX(CanTxPduId);

    /* Check if FullCAN message */
    if (queueindex != (PduIdType)0xFFFFFFFFu)
    {
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
      if (queueindex >= CANIF_CFG_GENERIC(eMaxTxPDUHandle))
      {
        CanIf_Det_ReportError(CANIF_CANCELTRANSMIT_API, CANIF_E_PARAM_LPDU);
      } 
      else
# endif
      { 
        CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_1); 

# if (CANIF_BITQUEUE == STD_ON)
        queueBitPos  = CanTxPduId + CANIF_CFG_TXQUEUE_PADBITS(CanIf_Controller_Value_Local);
        queueElementIdx = (uint8)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
        elementBitIdx  = (uint8)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
        if( (canIf_TxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (CanIf_TxQueueFlagType)0 )
        {
          canIf_TxQueueFlags[queueElementIdx] &= ~CanShiftLookUp[elementBitIdx]; /* clear flag from the queue */
# else
          if (CanIf_TxQueue[queueindex].eQueued != 0)
          {
            /* Cancel PDU from queue */
            CANIF_CHANNEL_CANTYPE_LOCAL

            CanIf_TxQueue[queueindex].eQueued = 0;
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
            controller = CANIF_CFG_TX_ECONTROLLER;
#  endif
            CanIf_TxQueueCounter[CanIf_Controller_Value_Local]--;
# endif
          }
          /* ESCAN00054772 */
          Can_CancelTx(hth, CanTxPduId);
          CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_1);
        } 
      } 
      else 
      {
        /* Handle FullCan messages */
        Can_CancelTx(hth, CanTxPduId);
      }
# else  /* CANIF_TRANSMIT_BUFFER */
    Can_CancelTx(hth, CanTxPduId);
# endif /* CANIF_TRANSMIT_BUFFER */
  }
}

/*******************************************************************************************************************
| NAME:             CanIf_CancelTxNotification()
| SID:              -
| CALLED BY:        CAN Driver
| PRECONDITIONS:    CanInterface is initialized
|                   Valid PDU ID is passed
| INPUT PARAMETERS: PduIdType, cancellation was successful?
| RETURN VALUES:    none
| DESCRIPTION:      CAN Interface is notified of a cancelled PDU
|                   The confirmation won't be passed to upper layers
|                   Next message from queue will be transmitted
*******************************************************************************************************************/
/* void CanIf_CancelTxNotification(PduIdType PduId, CanIf_CancelResultType IsCancelled) */
/* PRQA S 3206 1 */ /* MD_CanIf_Redundancy_NotUsed */
FUNC(void, CANIF_CODE) CanIf_CancelTxNotification(PduIdType PduId, CanIf_CancelResultType IsCancelled)
{
# if (V_USE_DUMMY_STATEMENT == STD_ON)
  IsCancelled = IsCancelled; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
# endif
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (PduId >=  CANIF_CFG_GENERIC(eMaxTxPDUHandle)) 
  {
    CanIf_Det_ReportError(CANIF_TXNOTIFICATION_API, CANIF_E_PARAM_LPDU);
  } 
  else if (CanIf_ControllerMode[CANIF_CFG_TX_ECONTROLLER_X] == CANIF_CS_UNINIT ) 
  {
    CanIf_Det_ReportError(CANIF_TXNOTIFICATION_API, CANIF_E_UNINIT);
  } 
  else 
# endif
  {
    if (CanIf_ControllerMode[CANIF_CFG_TX_ECONTROLLER_X] == CANIF_CS_STARTED) 
    {
      if ( (CanIf_ChannelMode[CANIF_CFG_TX_ECONTROLLER_X] == CANIF_GET_ONLINE) ||
           (CanIf_ChannelMode[CANIF_CFG_TX_ECONTROLLER_X] == CANIF_GET_TX_ONLINE)
# if ((CANIF_PN_TRCV_HANDLING == STD_ON) || (CANIF_PN_WU_TX_PDU_FILTER == STD_ON))
           || (CanIf_ChannelMode[CANIF_CFG_TX_ECONTROLLER_X] == CANIF_GET_ONLINE_WAKF)
           || (CanIf_ChannelMode[CANIF_CFG_TX_ECONTROLLER_X] == CANIF_GET_TX_ONLINE_WAKF)
# endif
         )
      {
# if (CANIF_TRANSMIT_BUFFER == STD_ON)
        PduIdType queueindex;
        queueindex = CANIF_CFG_TX_QUEUEINDEX(PduId);

        /* Check if queue is affected (Normal Tx object) */
        if (queueindex != (PduIdType)0xFFFFFFFFu)
        {
          /* Send queued messages directly */
          CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_2);
          (void)CanIf_TxQueueTreatment(CANIF_CFG_TX_ECONTROLLER_X);
          CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_2);  /*lock over queue handling + write call (driver does not expect direct call inbetween)*/
        }
# endif
      }
    }
  }
}

#endif

#if (CANIF_TRCV_HANDLING == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_SetTransceiverMode()
| SID:              0x0D
| CALLED BY:        Ecu State Manager
| PRECONDITIONS:    Transceiver Driver is initialized
| INPUT PARAMETERS: uint8 Transceiver: Index to address transceiver
|                   CanIf_TransceiverModeType TransceiverMode: Requested transceiver mode
| RETURN VALUES:    E_OK: success / E_NOT_OK: fail
| DESCRIPTION:      Set transceiver to requested mode
*******************************************************************************************************************/
# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_SetTransceiverMode(uint8 CanNetwork, CanIf_TransceiverModeType TransceiverMode); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTransceiverMode(uint8 CanNetwork, CanIf_TransceiverModeType TransceiverMode)
# else
/* Std_ReturnType CanIf_SetTransceiverMode(uint8 Transceiver, CanIf_TransceiverModeType TransceiverMode) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTransceiverMode(uint8 Transceiver, CanIf_TransceiverModeType TransceiverMode)
# endif
{
  Std_ReturnType                  retval;

# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
  uint8 Transceiver;

  Transceiver = CanNetwork;
# endif

  retval = E_NOT_OK;
# if (CANIF_DEV_ERROR_DETECT == STD_ON) 
  
  if (Transceiver >= CANIF_CFG_GENERIC(eMaxTransceivers)) 
  {
    CanIf_Det_ReportError(CANIF_SETTRANSCEIVERMODE_API, CANIF_TRCV_E_TRANSCEIVER);
  } 
  else
# endif /* CANIF_DEV_ERROR_DETECT */
  {
# if (CANIF_TRCV_MAPPING == STD_ON)
    uint8                           lowIndex;
    uint8                           lowAddress;
    CanIf_CanTrcv_SetOpModeFctType  lowFct;

    lowIndex   = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverIndex);
    lowAddress = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverAddress);

    lowFct = CanIf_TransceiverAPICanTrcv_SetOpModeFctMap[lowAddress];

    /* ESCAN00031640 */
    if (lowFct == NULL_PTR)
    {
      CanIf_Det_ReportError(CANIF_SETTRANSCEIVERMODE_API, CANIF_TRCV_E_TRANSCEIVER);
      /* retval is already set to E_NOT_OK */
    }
    else
    {
      retval = lowFct(TransceiverMode, lowIndex);
    }
# else
    retval = CanTrcv_SetOpMode(TransceiverMode, Transceiver);
# endif
  }
  return retval;
}
#endif


#if (CANIF_TRCV_HANDLING == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_GetTransceiverMode()
| SID:              0x0E
| CALLED BY:        Ecu State Manager
| PRECONDITIONS:    Transceiver Driver is initialized
| INPUT PARAMETERS: uint8 Transceiver: Index to address transceiver
|                   CanIf_TransceiverModeType *TransceiverModePtr: Pointer to buffer for current transceiver mode
| RETURN VALUES:    E_OK: success / E_NOT_OK: fail
| DESCRIPTION:      Request current transceiver mode
*******************************************************************************************************************/
# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_GetTransceiverMode(uint8 CanNetwork, CanIf_TransceiverModeType *TransceiverModePtr); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTransceiverMode(uint8 CanNetwork, P2VAR(CanIf_TransceiverModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) TransceiverModePtr)
# else
/* Std_ReturnType CanIf_GetTransceiverMode(uint8 Transceiver, CanIf_TransceiverModeType *TransceiverModePtr) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTransceiverMode(uint8 Transceiver, P2VAR(CanIf_TransceiverModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) TransceiverModePtr)
# endif
{
  Std_ReturnType retval;

# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
  uint8 Transceiver;

  Transceiver = CanNetwork;
# endif

  retval = E_NOT_OK;
# if (CANIF_DEV_ERROR_DETECT == STD_ON) 
  
  if (Transceiver >= CANIF_CFG_GENERIC(eMaxTransceivers)) 
  {
    CanIf_Det_ReportError(CANIF_GETTRANSCEIVERMODE_API, CANIF_TRCV_E_TRANSCEIVER);
  } 
  else
# endif /* CANIF_DEV_ERROR_DETECT */
  {
# if (CANIF_TRCV_MAPPING == STD_ON)
    uint8                           lowIndex;
    uint8                           lowAddress;
    CanIf_CanTrcv_GetOpModeFctType  lowFct;

    lowIndex   = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverIndex);
    lowAddress = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverAddress);

    lowFct = CanIf_TransceiverAPICanTrcv_GetOpModeFctMap[lowAddress];

    /* ESCAN00031640 */
    if (lowFct == NULL_PTR)
    {
      CanIf_Det_ReportError(CANIF_GETTRANSCEIVERMODE_API, CANIF_TRCV_E_TRANSCEIVER);
      /* retval is already set to E_NOT_OK */
    }
    else
    {
      retval = lowFct(TransceiverModePtr, lowIndex);
    }
# else
    retval = CanTrcv_GetOpMode(TransceiverModePtr, Transceiver);
# endif
  }
  return retval;
}
#endif


#if (CANIF_TRCV_HANDLING == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_GetTrcvWakeupReason()
| SID:              0x0F
| CALLED BY:        Ecu State Manager
| PRECONDITIONS:    Transceiver Driver is initialized
| INPUT PARAMETERS: uint8 Transceiver: Index to address transceiver
|                   CanIf_TrcvWakeupReasonType *TrcvWuReasonPtr: Pointer to buffer for wake up reason
| RETURN VALUES:    E_OK: success / E_NOT_OK: fail
| DESCRIPTION:      Request wake up reason
*******************************************************************************************************************/
# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_GetTrcvWakeupReason(uint8 CanNetwork, CanIf_TrcvWakeupReasonType *TrcvWuReasonPtr) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvWakeupReason(uint8 CanNetwork, P2VAR(CanIf_TrcvWakeupReasonType, AUTOMATIC, CANIF_APPL_STATE_VAR) TrcvWuReasonPtr)
# else
/* Std_ReturnType CanIf_GetTrcvWakeupReason(uint8 Transceiver, CanIf_TrcvWakeupReasonType *TrcvWuReasonPtr) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvWakeupReason(uint8 Transceiver, P2VAR(CanIf_TrcvWakeupReasonType, AUTOMATIC, CANIF_APPL_STATE_VAR) TrcvWuReasonPtr)
# endif
{
  Std_ReturnType retval;

# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
  uint8 Transceiver;

  Transceiver = CanNetwork;
#endif

  retval = E_NOT_OK;
# if (CANIF_DEV_ERROR_DETECT == STD_ON) 
  if (Transceiver >= CANIF_CFG_GENERIC(eMaxTransceivers)) 
  {
    CanIf_Det_ReportError(CANIF_TRCVWAKEUPREASON_API, CANIF_TRCV_E_TRANSCEIVER);
  } 
  else
# endif /* CANIF_DEV_ERROR_DETECT */
  {
# if (CANIF_TRCV_MAPPING == STD_ON)
    uint8                                 lowIndex;
    uint8                                 lowAddress;
    CanIf_CanTrcv_GetBusWuReasonFctType   lowFct;

    lowIndex   = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverIndex);
    lowAddress = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverAddress);

    lowFct = CanIf_TransceiverAPICanTrcv_GetBusWuReasonFctMap[lowAddress];

    /* ESCAN00031640 */
    if (lowFct == NULL_PTR) 
    {
      CanIf_Det_ReportError(CANIF_TRCVWAKEUPREASON_API, CANIF_TRCV_E_TRANSCEIVER);
      /* retval is already set to E_NOT_OK */
    }
    else
    {
      retval = lowFct(lowIndex, TrcvWuReasonPtr);
    }
# else
    retval = CanTrcv_GetBusWuReason(Transceiver, TrcvWuReasonPtr);
# endif
  }
  return retval;
}
#endif


#if (CANIF_TRCV_HANDLING == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_SetTransceiverWakeupMode()
| SID:              0x10
| CALLED BY:        Ecu State Manager
| PRECONDITIONS:    Transceiver Driver is initialized
| INPUT PARAMETERS: uint8 Transceiver: Index to address transceiver
|                   CanIf_TrcvWakeupModeType TrcvWakeupMode: Set wake up mode
| RETURN VALUES:    E_OK: success / E_NOT_OK: fail
| DESCRIPTION:      Set transceiver wake up mode (enable, disable, clear)
*******************************************************************************************************************/
# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_SetTransceiverWakeupMode(uint8 CanNetwork, CanIf_TrcvWakeupModeType TrcvWakeupMode); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTransceiverWakeupMode(uint8 CanNetwork, CanIf_TrcvWakeupModeType TrcvWakeupMode)
# else
/* Std_ReturnType CanIf_SetTransceiverWakeupMode(uint8 Transceiver, CanIf_TrcvWakeupModeType TrcvWakeupMode) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTransceiverWakeupMode(uint8 Transceiver, CanIf_TrcvWakeupModeType TrcvWakeupMode)
# endif

{
  Std_ReturnType retval;

# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
  uint8 Transceiver;

  Transceiver = CanNetwork;
# endif

  retval = E_NOT_OK;
# if (CANIF_DEV_ERROR_DETECT == STD_ON) 
  if (Transceiver >= CANIF_CFG_GENERIC(eMaxTransceivers)) 
  {
    CanIf_Det_ReportError(CANIF_SETTRANSCEIVERWAKEUPMODE_API, CANIF_TRCV_E_TRANSCEIVER);
  } 
  else
# endif /* CANIF_DEV_ERROR_DETECT */
  {

# if (CANIF_TRCV_MAPPING == STD_ON)
    uint8                                 lowIndex;
    uint8                                 lowAddress;
    CanIf_CanTrcv_SetWakeupModeFctType    lowFct;

    lowIndex   = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverIndex);
    lowAddress = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverAddress);

    lowFct = CanIf_TransceiverAPICanTrcv_SetWakeupModeFctMap[lowAddress];
  
    /* ESCAN00031640 */
    if (lowFct == NULL_PTR)
    {
      CanIf_Det_ReportError(CANIF_SETTRANSCEIVERWAKEUPMODE_API, CANIF_TRCV_E_TRANSCEIVER);
      /* retval is already set to E_NOT_OK */
    }
    else
    {
      retval = lowFct(TrcvWakeupMode, lowIndex);
    }
# else
    retval = CanTrcv_SetWakeupMode(TrcvWakeupMode, Transceiver);
# endif
  }
  return retval;
}
#endif


/*******************************************************************************************************************
| NAME:             CanIf_CheckWakeup()
| SID:              0x11
| CALLED BY:        EcuM
| PRECONDITIONS:    CanInterface is initialized
| INPUT PARAMETERS: EcuM WakeupSource
| RETURN VALUES:    E_OK:     Check WakeUp request was accepted
|                   E_NOT_OK: Check WakeUp request was not accepted
| DESCRIPTION:      CAN Interface is asked by the EcuM if one of the possible 
|                   WakeUp Sources encoded in 'WakeupSource' is responsible
|                   for the WakeUp
*******************************************************************************************************************/
/* Std_ReturnType CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource)
{
  Std_ReturnType                        retval;

#if (CANIF_WAKEUP_SUPPORT == STD_ON)
  Std_ReturnType                        localRetval;
  EcuM_WakeupSourceType                 wokenUpSources;
  uint8                                 numWUsrc;
#if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) && ((CANIF_DEV_ERROR_DETECT == STD_ON) || (CANIF_EXTENDED_STATE_MACHINE == STD_ON)))
  CANIF_WUCHANNEL_CANTYPE_LOCAL
#endif

  wokenUpSources = 0u;
  retval         = E_OK;        /* WakeUp request will be accepted */

  /* Find the first WakeUp Source which pretends to be the responsible */
  /* Always cycle through all Sources */
  for (numWUsrc = 0; numWUsrc < CANIF_CFG_GENERIC(eMaxWakeUpSources); numWUsrc++) 
  {
    EcuM_WakeupSourceType                 wuSrc;
    CanIf_WakeUpTargetType                wuTrgtmodule;
    uint8                                 wuTrgtaddress;


    /* Acquire wake up source information */
    wuSrc         = CANIF_CFG_WAKEUP(numWUsrc, eWakeUpSource);
    wuTrgtmodule  = CANIF_CFG_WAKEUP(numWUsrc, eWakeUpTargetModule);
    wuTrgtaddress = CANIF_CFG_WAKEUP(numWUsrc, eWakeUpTargetAddress);

# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) && ((CANIF_DEV_ERROR_DETECT == STD_ON) || (CANIF_EXTENDED_STATE_MACHINE == STD_ON)))
    /* Find the correct CAN Controller */
    wuController  = CANIF_CFG_WAKEUP(numWUsrc, eController);
# endif

    /* Initialize localRetval for WakeUpSources which are not handled by CanIf*/
    localRetval = E_NOT_OK;

# if (CANIF_DEV_ERROR_DETECT == STD_ON) 
    /* DET error occurred
       other sources will be checked 
       return value will be E_NOT_OK
    */
    /* ESCAN00051107 -> avoids compiler warning */
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
    if (CanIf_WU_Controller_Value_Local >= CANIF_CFG_GENERIC_EMAXCONTROLLER) 
    {
      retval = E_NOT_OK;
      CanIf_Det_ReportError(CANIF_CHECKWAKEUP_API, CANIF_E_PARAM_CONTROLLER);
    }
    else
#  endif /* (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) */
    if (CanIf_ControllerMode[CanIf_WU_Controller_Value_Local] == CANIF_CS_UNINIT)
    {
      retval = E_NOT_OK;
      CanIf_Det_ReportError(CANIF_CHECKWAKEUP_API, CANIF_E_UNINIT);
    }
    else
# endif /* CANIF_DEV_ERROR_DETECT */
    {
      if ((WakeupSource & wuSrc) != 0u)
      {
        if (wuTrgtmodule == CANIF_WAKEUPREQUEST_CAN)
        {
          localRetval = Can_Cbk_CheckWakeup(wuTrgtaddress);
          if (localRetval == E_OK)
          {
            /* localRetval is E_OK if the requested source is responsible for the wakeup */
# if (CANIF_EXTENDED_STATE_MACHINE == STD_ON)
            /* Do CAN state transition only in case of FNOS */
            /* Controller WakeUp -> Set to started mode */
            /* Explicitely cast to void as return value cannot be used here */
            (void)CanIf_SetControllerMode(CanIf_WU_Controller_Value_Local, CANIF_CS_STARTED);
# endif
            /* Store source of woken up module */
            /* NOTE: only CAN wakeup sources will be notified to upper layers, reason: upwards compatibility to CanDrv < R14 */
            wokenUpSources |= wuSrc;
          } /* if (localRetval == E_OK) */
        } /* if (wuTrgtmodule == CANIF_WAKEUPREQUEST_CAN) */
# if (CANIF_TRCV_HANDLING == STD_ON)
        else if (wuTrgtmodule == CANIF_WAKEUPREQUEST_TRCV) 
        {
#  if (CANIF_TRCV_MAPPING == STD_ON)
          /* Indirection here */
          uint8                                 lowIndex;   /* Index / channel within TRCV driver */
          uint8                                 lowAddress; /* TRCV driver index */
          CanIf_CanTrcv_CB_WakeupByBusFctType   lowFct;

          lowIndex   = CANIF_CFG_TRCVUPTOLOWMAP(wuTrgtaddress, eDriverIndex);
          lowAddress = CANIF_CFG_TRCVUPTOLOWMAP(wuTrgtaddress, eDriverAddress);

          lowFct     = CanIf_TransceiverAPICanTrcv_CB_WakeupByBusFctMap[lowAddress];

          /* ESCAN00031640 */
          if (lowFct == NULL_PTR)
          {
            CanIf_Det_ReportError(CANIF_CHECKWAKEUP_API, CANIF_TRCV_E_TRANSCEIVER);
            /* localRetval is already set to E_NOT_OK */
          }
          else
          {
            (void)lowFct(lowIndex);
          }
#  else /* CANIF_TRCV_MAPPING */
          (void)CanTrcv_CB_WakeupByBus(wuTrgtaddress);
#  endif /* CANIF_MULTIPLE_TRANSCEIVER_SUPPORT */
        }
# endif /* CANIF_TRCV_HANDLING */
        else
        {
          /* CANIF_WAKEUPREQUEST_NONE nothing to do*/
        }
      } /* ValidWakeUpSource */
    } /* DET Error occurred */
  }   /* WakeUp-Source Loop */

  /* Optional EcuM call (in case a valid wake up responsible has been found) */
  if (wokenUpSources != 0u)
  {
    CanIf_WakeUpEventFctType wakeupnotificationFct;
    wakeupnotificationFct = CANIF_CFG_WAKEUPEVENT();

    if (wakeupnotificationFct != NULL_PTR) 
    {
      wakeupnotificationFct(wokenUpSources);
    }
  }

#else  /* CANIF_WAKEUP_SUPPORT */
# if (V_USE_DUMMY_STATEMENT == STD_ON)
  WakeupSource = WakeupSource; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
# endif
  retval = E_NOT_OK;
#endif /* CANIF_WAKEUP_SUPPORT */

  return retval;
}

/* SREQ00007735 */
/*******************************************************************************************************************
| NAME:             CanIf_CheckValidation()
| SID:              0x12
| CALLED BY:        EcuManager
| PRECONDITIONS:    A wake up event occurred and CanIf_CheckWakeup was called before / CanIf has to be initialized
| INPUT PARAMETERS: EcuM WakeupSource
| RETURN VALUES:    E_OK:     Check Validation request was accepted
|                   E_NOT_OK: Check Validation request was not accepted
| DESCRIPTION:      CAN Interface is asked by the EcuM if an Rx message was received since the last wake up event.
|                     In this case the call back function EcuM_ValidateWakeupEvent will be called.
*******************************************************************************************************************/
/* Std_ReturnType CanIf_CheckValidation(EcuM_WakeupSourceType WakeupSource) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckValidation(EcuM_WakeupSourceType WakeupSource)
{
  Std_ReturnType                        retval;
#if (CANIF_WAKEUP_VALIDATION == STD_ON)
  Std_ReturnType                        localRetval;
  EcuM_WakeupSourceType                 wokenUpSources;
  uint8                                 numWUsrc;

  retval         = E_OK;
  wokenUpSources = 0;

  /* Always cycle through all Sources */
  for (numWUsrc = 0; numWUsrc < CANIF_CFG_GENERIC(eMaxWakeUpSources); numWUsrc++)
  {
    EcuM_WakeupSourceType                 wuSrc;
    CANIF_WUCHANNEL_CANTYPE_LOCAL

    /* Acquire wake up source information */
    wuSrc         = CANIF_CFG_WAKEUP(numWUsrc, eWakeUpSource);

# if (CANIF_ONE_CONTROLLER_OPTIMIZATION==STD_OFF)
    /* Find the correct CAN Controller */
    wuController  = CANIF_CFG_WAKEUP(numWUsrc, eController);
# endif

# if (CANIF_DEV_ERROR_DETECT == STD_ON)
    /* DET error occurred
       other sources will be checked
       return value will be E_NOT_OK
    */
    /* ESCAN00051107 -> avoids compiler warning */
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
    if (CanIf_WU_Controller_Value_Local >= CANIF_CFG_GENERIC_EMAXCONTROLLER)
    {
      retval = E_NOT_OK;
      CanIf_Det_ReportError(CANIF_CHECKVALIDATIONUP_API, CANIF_E_PARAM_CONTROLLER);
    }
    else
#  endif
    if (CanIf_ControllerMode[CanIf_WU_Controller_Value_Local] == CANIF_CS_UNINIT)
    {
      retval = E_NOT_OK;
      CanIf_Det_ReportError(CANIF_CHECKVALIDATIONUP_API, CANIF_E_UNINIT);
    }
    else
# endif /* CANIF_DEV_ERROR_DETECT */
    {
      if ((WakeupSource & wuSrc ) != 0)
      {
        /* Passed wake up source is valid and wake up event occurred earlier */
        if ( CanIf_WakeUpValidationState[CanIf_WU_Controller_Value_Local] == CANIF_WUVALIDATION_DETECTED )
        {
          /* SREQ00007749, We detected a wake up validation */
          CanIf_WakeUpValidationState[CanIf_WU_Controller_Value_Local] = CANIF_WUVALIDATION_ARMED;

          localRetval = E_OK;
        }
        else
        {
          /* We detected no validation of the wake up event -> No error */
          localRetval = E_NOT_OK;
        }

        /* localRetval is E_OK if the requested source is responsible for the wakeup */
        if (localRetval == E_OK)
        {
          /* Store source of woken up module */
          wokenUpSources |= wuSrc;
        }
      } /* ValidWakeUpSource */
      else
      {
        /* Invalid wake up source passed / or no wake up occurred */
        /* Nothing to do */
      }
    } /* DET Error occured */
  }   /* WakeUp-Source Loop */

  /* SREQ00007765: EcuM call (in case a valid wake up validation for the requested source is pending) */
  if (wokenUpSources != 0)
  {
    CanIf_WakeUpValidationFctType wakeupvalidationFct;

    wakeupvalidationFct = CANIF_CFG_WAKEUPVALIDATION();

    if (wakeupvalidationFct != NULL_PTR)
    {
      wakeupvalidationFct(wokenUpSources);
    }
  }

#else  /* CANIF_WAKEUP_VALIDATION */
# if (V_USE_DUMMY_STATEMENT == STD_ON)
  WakeupSource = WakeupSource; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
# endif
  retval = E_NOT_OK;
#endif /* CANIF_WAKEUP_VALIDATION */

  return retval;
}



#if (CANIF_BUSOFF_RECOVERY_API == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_ResetBusOffStart()
| SID:              -
| CALLED BY:        Application
| PRECONDITIONS:    -
| INPUT PARAMETERS: uint8 Controller
| RETURN VALUES:    -
| DESCRIPTION:      API to recover a bus off event for not AUTOSAR compliant network management layers
*******************************************************************************************************************/
/* void CanIf_ResetBusOffStart(uint8 Controller) */
FUNC(void, CANIF_CODE) CanIf_ResetBusOffStart(uint8 Controller)
{
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (Controller >= CANIF_CFG_GENERIC_EMAXCONTROLLER)
  {
    CanIf_Det_ReportError(CANIF_TRCVWAKEUPREASON_API, CANIF_E_PARAM_CONTROLLER);
  }
  else
# else
#  if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (V_USE_DUMMY_STATEMENT == STD_ON))
  Controller = Controller; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
#  endif
# endif
  {
    CanIf_ControllerMode[CanIf_Controller_Value] = CANIF_CS_STARTED;
    CanIf_ChannelMode[CanIf_Controller_Value] = CANIF_GET_RX_ONLINE;
    Can_ResetBusOffStart(CanIf_Controller_Value);
  }
}

/*******************************************************************************************************************
| NAME:             CanIf_ResetBusOffEnd()
| SID:              -
| CALLED BY:        Application
| PRECONDITIONS:    -
| INPUT PARAMETERS: uint8 Controller
| RETURN VALUES:    -
| DESCRIPTION:      API to recover a bus off event for not AUTOSAR compliant network management layers
*******************************************************************************************************************/
/* void CanIf_ResetBusOffEnd(uint8 Controller) */
FUNC(void, CANIF_CODE) CanIf_ResetBusOffEnd(uint8 Controller)
{
# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (V_USE_DUMMY_STATEMENT == STD_ON))
  Controller = Controller; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
# endif
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (Controller >= CANIF_CFG_GENERIC_EMAXCONTROLLER)
  {
    CanIf_Det_ReportError(CANIF_TRCVWAKEUPREASON_API, CANIF_E_PARAM_CONTROLLER);
  }
  else
# endif
  {
    /* CanIf already in CANIF_CS_STARTED and RX_ONLINE state. No need to switch states */
    Can_ResetBusOffEnd(CanIf_Controller_Value);
  }
}
#endif

#if (CANIF_SUPPORT_NONPB_API == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_ConvertPduId()
| SID:              -
| CALLED BY:        Application
| PRECONDITIONS:    -
| INPUT PARAMETERS: PduIdType PbPduId: PduId which has to be converted
|                   PduIdType *PduId:  Converted Pdu Id
| RETURN VALUES:    E_OK: Conversion successful
|                   E_NOT_OK: Vonversion not successful
| DESCRIPTION:      Convert a Tx PDU Id (defined at link time) to the correct Pdu Id which
|                   is valid after post build configuration (has to be used by upper layers
|                   which use Tx PDU which are not included in post build configuration of this layer
*******************************************************************************************************************/
/* Std_ReturnType CanIf_ConvertPduId(PduIdType PbPduId, PduIdType *PduId) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ConvertPduId(PduIdType PbPduId, P2VAR(PduIdType, AUTOMATIC, CANIF_APPL_MSG_VAR)PduId)
{
  Std_ReturnType retval;

  retval = E_OK;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  /* Compare LinkTime and PostBuild configuration AND if PduId parameter is valid */
  if (  ( CanIf_MaxNPBPduHandles != CANIF_CFG_GENERIC(eMaxNPBTxPDUHandle) )  &&
        ( PbPduId >= CanIf_MaxNPBPduHandles )   )
  {
    *PduId = CanIf_TxPduHnd_INVALID;
    retval = E_NOT_OK;
  }

  else
# endif
  {
    /* Always check if table is valid by evaluating the last entry
       better return an invalid handle here instead of raising a DET error */
    if (CANIF_CFG_CONVERTPDU(CanIf_MaxNPBPduHandles) != (PduIdType) 0xFEFEFEFEu)
    {
      *PduId = CanIf_TxPduHnd_INVALID;
      retval = E_NOT_OK;
    } 
    else
    {
      *PduId = CANIF_CFG_CONVERTPDU(PbPduId);
    }
  }
  return retval;
}
#endif


#if (CANIF_ENABLE_TX_LPDU_REMAPPING == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIfWrapper_Transmit()
| SID:              0x05
| CALLED BY:        upper layer
| PRECONDITIONS:    CAN Interface initialized
| INPUT PARAMETERS: PduIdType CanTxPduId: Handle of Tx PDU (Provided by UpperLayer, will be converted to CanIf's PduID
|                   const PduInfoType *PduInfoPtr: PDU Info (Data length, data ptr)
| RETURN VALUES:    Result of transmission request
| DESCRIPTION:      Initiate transmission of a Tx PDU (call CanIf_Transmit) after conversion of the provided PduId
|                   The Tx PduId will be provided by the upper layer and converted by this function.
*******************************************************************************************************************/
/* Std_ReturnType CanIfWrapper_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr); */
FUNC(Std_ReturnType, CANIF_CODE) CanIfWrapper_Transmit(PduIdType CanTxPduId, P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_MSG_VAR)PduInfoPtr)
{
  Std_ReturnType retval;
  retval = E_NOT_OK;

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (CanTxPduId < CANIF_CFG_GENERIC(eMapTxPduOffset))
  {
    CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_PARAM_LPDU);
  }
  else if (CanTxPduId >= (CANIF_CFG_GENERIC(eMapTxPduOffset) + CANIF_CFG_GENERIC(eMaxMappedTxPDUs)) )
  {
    CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_PARAM_LPDU);
  }
  else
#endif
  {
    PduIdType mappedCanTxPdu;

    mappedCanTxPdu = CANIF_CFG_TXPDUMAP((CanTxPduId - CANIF_CFG_GENERIC(eMapTxPduOffset)));
    /* Parameters will be checked in CanIf_Transmit if development error detection is active */
    retval = CanIf_Transmit(mappedCanTxPdu, PduInfoPtr);
  }
  return retval;
}
#endif

#if(CANIF_SETDYNAMICTXID_API == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_SetDynamicTxId(PduIdType CanTxPduId, Can_IdType CanId)
| SID:              0x0C
| CALLED BY:        Application
| PRECONDITIONS:    CAN Interface initialized
| Caveats:          This function may not be interrupted by CanIf_Transmit() if the same L-PDU ID is handled
| INPUT PARAMETERS: PduIdType CanTxPduId: Handle of Tx PDU provided by UpperLayer
|                   Can_IdType CanId: Id of transmit message
| RETURN VALUES:    none
| DESCRIPTION:      This service reconfigures the corresponding CAN identifier of the requested CAN L-PDU
*******************************************************************************************************************/
void CanIf_SetDynamicTxId(PduIdType CanTxPduId, Can_IdType CanId)
{
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  CANIF_CHANNEL_CANTYPE_LOCAL
# endif
  PduIdType dynamicPduId;
# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) && (CANIF_DEV_ERROR_DETECT == STD_ON))
    /* Collect configuration data */
  controller = CANIF_CFG_TX_ECONTROLLER;
# endif
  dynamicPduId = CANIF_CFG_STAT2DYN_INDIRECTION(CanTxPduId);
  /* Check if CanTxPduId is valid */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (CanTxPduId >= CANIF_CFG_GENERIC(eMaxTxPDUHandle))
  {
    CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_INVALID_TXPDUID);
  }
  else if (dynamicPduId == (PduIdType)0xFFFFFFFFu) /*no dynamic TxPdu handle*/
  {
    CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_INVALID_TXPDUID);
  } 
#  if (CANIF_EXTENDEDID_SUPPORT != STD_ON)
  else if (CanId > 0x7FF)
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, CANIF_E_PARAM_CANID);
  }
#  endif
  else if(CanIf_ControllerMode[CanIf_Controller_Value_Local] == CANIF_CS_UNINIT)
  {
    CanIf_Det_ReportError(CANIF_TRANSMIT_API, CANIF_E_UNINIT);
  }
  else
# endif
  {
    CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_5); /* ESCAN00060165 */
    CanIf_DynTxId[dynamicPduId]= CanId;
    CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_5); /* ESCAN00060165 */
  }
}
#endif

/* CANIF754 */
#if (CANIF_PN_TRCV_HANDLING == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_ConfirmPnAvailability()
| SID:              0x1a
| CALLED BY:        Transceiver driver
| PRECONDITIONS:    -
| INPUT PARAMETERS: <Transceiver> CAN transceiver, which was checked for PN availability
| RETURN VALUES:    void
| DESCRIPTION:      This service indicates that the transceiver is running in PN communication mode
|                   Synchronous
|                   Reentrant
*******************************************************************************************************************/
/* void CanIf_ConfirmPnAvailability(uint8 Transceiver); */
FUNC(void, CANIF_CODE) CanIf_ConfirmPnAvailability(uint8 Transceiver)
{
# if (CANIF_TRCV_MAPPING == STD_ON)
  /* CANIF753 */
  CanSM_ConfirmPnAvailability(CANIF_CFG_TRCVUPTOUPPERMAP(Transceiver));
# else
  /* CANIF753 */
  CanSM_ConfirmPnAvailability(Transceiver);
# endif
}
#endif

#if (CANIF_PN_TRCV_HANDLING == STD_ON)
/* CANIF762 */
/*******************************************************************************************************************
| NAME:             CanIf_ClearTrcvWufFlagIndication()
| SID:              0x20
| CALLED BY:        CanSM
| PRECONDITIONS:    CanIf_InitController() and CanIf_Init() already called && all transceiver driver have been initialized
| INPUT PARAMETERS: <Transceiver> CAN transceiver, for which the API was called
| RETURN VALUES:    void
| DESCRIPTION:      This service indicates that the transceiver has cleared the WufFlag
|                   Asynchronous
|                   Reentrant
*******************************************************************************************************************/
/* void CanIf_ClearTrcvWufFlagIndication(uint8 Transceiver) */
FUNC(void, CANIF_CODE) CanIf_ClearTrcvWufFlagIndication(uint8 Transceiver)
{
  CANIF_TRCVIDUPPER_TYPE_LOCAL
# if (CANIF_TRCV_MAPPING == STD_ON)
  CanIf_TrcvIdUpper_Local = CANIF_CFG_TRCVUPTOUPPERMAP(Transceiver);
# endif /* CANIF_TRCV_MAPPING */

  /* CANIF757 */
  CanSM_ClearTrcvWufFlagIndication(CanIf_TrcvIdUpper_Local);

# if ((V_USE_DUMMY_STATEMENT == STD_ON) && (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON))
  Transceiver = Transceiver;
# endif /* ((V_USE_DUMMY_STATEMENT == STD_ON) && (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON)) */
}
#endif

#if (CANIF_PN_TRCV_HANDLING == STD_ON)
/* CANIF763 */
/*******************************************************************************************************************
| NAME:             CanIf_CheckTrcvWakeFlagIndication()
| SID:              0x21
| CALLED BY:        Transceiver driver
| PRECONDITIONS:    CanIf_InitController() and CanIf_Init() already called && all transceiver driver have been initialized
| INPUT PARAMETERS: <Transceiver> CAN transceiver, for which the API was called
| RETURN VALUES:    void
| DESCRIPTION:      This service indicates the reason for the wake up that the CAN transceiver has detected
|                   Asynchronous
|                   Reentrant
*******************************************************************************************************************/
/* void CanIf_CheckTrcvWakeFlagIndication(uint8 Transceiver); */
FUNC(void, CANIF_CODE)CanIf_CheckTrcvWakeFlagIndication(uint8 Transceiver)
{
  CANIF_TRCVIDUPPER_TYPE_LOCAL
# if (CANIF_TRCV_MAPPING == STD_ON)
  CanIf_TrcvIdUpper_Local = CANIF_CFG_TRCVUPTOUPPERMAP(Transceiver);
# endif /* CANIF_TRCV_MAPPING */
  /* CANIF759 */
  CanSM_CheckTransceiverWakeFlagIndication(CanIf_TrcvIdUpper_Local);

# if ((V_USE_DUMMY_STATEMENT == STD_ON) && (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON))
  Transceiver = Transceiver;
# endif /* ((V_USE_DUMMY_STATEMENT == STD_ON) && (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON)) */
}
#endif

#if (CANIF_TRCV_HANDLING == STD_ON)
/* CANIF764 */
/*******************************************************************************************************************
| NAME:             CanIf_TrcvModeIndication()
| SID:              0x22
| CALLED BY:        Transceiver driver
| PRECONDITIONS:    CanIf_InitController() and CanIf_Init() already called && all transceiver driver have been initialized
| INPUT PARAMETERS: <Transceiver> CAN transceiver, for which the API was called
|                   <TransceiverMode> Indicated mode
| RETURN VALUES:    void
| DESCRIPTION:      This service indicates that the transceiver mode has changed to TransceiverMode
|                   Asynchronous (SPI), Synchronous (DIO)
|                   Non Reentrant
*******************************************************************************************************************/
/* void CanIf_TrcvModeIndication(uint8 Transceiver, CanIf_TransceiverModeType TransceiverMode); */
FUNC(void, CANIF_CODE) CanIf_TrcvModeIndication(uint8 Transceiver, CanIf_TransceiverModeType TransceiverMode)
{
  CANIF_TRCVIDUPPER_TYPE_LOCAL
# if (CANIF_TRCV_MAPPING == STD_ON)
  CanIf_TrcvIdUpper_Local = CANIF_CFG_TRCVUPTOUPPERMAP(Transceiver);
# endif

  /* CANIF758 */
  CanSM_TransceiverModeIndication(CanIf_TrcvIdUpper_Local, TransceiverMode);

# if ((V_USE_DUMMY_STATEMENT == STD_ON) && (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_TRCV_MAPPING == STD_OFF))
  Transceiver = Transceiver;
# endif /* ((V_USE_DUMMY_STATEMENT == STD_ON) && (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_TRCV_MAPPING == STD_OFF)) */
}
#endif

#if (CANIF_PN_TRCV_HANDLING == STD_ON)
/* CANIF763 */
/*******************************************************************************************************************
| NAME:             CanIf_ClearTrcvWufFlag()
| SID:              0x1e
| CALLED BY:        CanSM
| PRECONDITIONS:    CanIf_InitController() and CanIf_Init() already called && all transceiver driver have been initialized
| INPUT PARAMETERS: <Transceiver> CAN transceiver, for which the API was called
| RETURN VALUES:    <Std_ReturnType> E_OK: Request has been accepted
|                                    E_NOT_OK: Request has not been accepted
| DESCRIPTION:      Requests the CanIf module to clear the WUF flag of the designated CAN Transceiver
|                   Synchronous
|                   Reentrant for different CAN Transceivers
*******************************************************************************************************************/
/* Std_ReturnType CanIf_ClearTrcvWufFlag(uint8 Transceiver) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ClearTrcvWufFlag(uint8 Transceiver)
{
  Std_ReturnType localRetVal=E_NOT_OK;

# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (Transceiver >= CANIF_CFG_GENERIC(eMaxTransceivers))
  {
    /* CANIF769 */
    CanIf_Det_ReportError(CANIF_CLEARTRCVWUFFLAG_API, CANIF_TRCV_E_TRANSCEIVER);
  }
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
  else if(CANIF_CS_UNINIT == CanIf_ControllerMode[CANIF_CFG_TRCVTOCTRLMAP(Transceiver)])
#  else
  else if(CANIF_CS_UNINIT == CanIf_ControllerMode[0])
#  endif
  {
    /* CANIF767 */
    CanIf_Det_ReportError(CANIF_CLEARTRCVWUFFLAG_API, CANIF_E_UNINIT);
  }
  else
# endif
  {
# if (CANIF_TRCV_MAPPING == STD_ON)
    /* CANIF766 */
    uint8                                  TrcvDriverId;
    uint8                                  TrcvDriverCh;
    CanIf_CanTrcv_ClearTrcvWufFlagFctType  lowFct;

    /* Get transceiver IDs */
    TrcvDriverCh = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverIndex);
    TrcvDriverId = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverAddress);

    /* get the corresponding transceiver API */
    lowFct = CanIf_TransceiverAPICanTrcv_ClearTrcvWufFlagFctMap[TrcvDriverId];

    if ((CanIf_CanTrcv_ClearTrcvWufFlagFctType)NULL_PTR != lowFct)
    {
      localRetVal = lowFct(TrcvDriverCh);
    }
    else
    {
      /* ESCAN00031640 */
      CanIf_Det_ReportError(CANIF_CLEARTRCVWUFFLAG_API, CANIF_TRCV_E_TRANSCEIVER);
      /* retval is already set to E_NOT_OK */
    }
# else
    /* CANIF766 */
    localRetVal = CanTrcv_ClearTrcvWufFlag(Transceiver);
# endif
  }
  return localRetVal;
}
#endif /* (CANIF_PN_TRCV_HANDLING == STD_ON) */

#if (CANIF_PN_TRCV_HANDLING == STD_ON)
/* CANIF761 */
/*******************************************************************************************************************
| NAME:             CanIf_CheckTrcvWakeFlag()
| SID:              0x1f
| CALLED BY:        CanSM
| PRECONDITIONS:    CanIf_InitController() and CanIf_Init() already called && all transceiver driver have been initialized
| INPUT PARAMETERS: <Transceiver> CAN transceiver, for which the API was called
| RETURN VALUES:    <Std_ReturnType> E_OK: Request has been accepted
|                                    E_NOT_OK: Request has not been accepted
| DESCRIPTION:      Requests the CanIf module to check the Wake flag of the designated CAN Transceiver
|                   Synchronous
|                   Reentrant for different CAN Transceivers
*******************************************************************************************************************/
/* Std_ReturnType CanIf_CheckTrcvWakeFlag(uint8 Transceiver); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckTrcvWakeFlag(uint8 Transceiver)
{
  Std_ReturnType localRetVal=E_NOT_OK;

# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  if (Transceiver >= CANIF_CFG_GENERIC(eMaxTransceivers))
  {
    /* CANIF770 */
    CanIf_Det_ReportError(CANIF_CHECKTRCVWAKEFLAG_API, CANIF_TRCV_E_TRANSCEIVER);
  }
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
  else if(CANIF_CS_UNINIT == CanIf_ControllerMode[CANIF_CFG_TRCVTOCTRLMAP(Transceiver)])
#  else
  else if(CANIF_CS_UNINIT == CanIf_ControllerMode[0])
#  endif
  {
    /* CANIF768 */
    CanIf_Det_ReportError(CANIF_CHECKTRCVWAKEFLAG_API, CANIF_E_UNINIT);
  }
  else
# endif
  {
# if (CANIF_TRCV_MAPPING == STD_ON)
    /*CANIF765*/
    uint8                               TrcvDriverId;
    uint8                               TrcvDriverCh;
    CanIf_CanTrcv_CheckWakeFlagFctType  lowFct;

    /* Get transceiver IDs */
    TrcvDriverCh = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverIndex);
    TrcvDriverId = CANIF_CFG_TRCVUPTOLOWMAP(Transceiver, eDriverAddress);

    /* get the corresponding transceiver API */
    lowFct = CanIf_TransceiverAPICanTrcv_CheckWakeFlagFctMap[TrcvDriverId];

    if ((CanIf_CanTrcv_CheckWakeFlagFctType)NULL_PTR != lowFct)
    {
      localRetVal = lowFct(TrcvDriverCh);
    }
    else
    {
      /* ESCAN00031640 */
      CanIf_Det_ReportError(CANIF_CHECKTRCVWAKEFLAG_API, CANIF_TRCV_E_TRANSCEIVER);
      /* retval is already set to E_NOT_OK */
    }
# else
    localRetVal = CanTrcv_CheckWakeFlag(Transceiver);
# endif
  }
  return localRetVal;
}
#endif /* (CANIF_PN_TRCV_HANDLING == STD_ON) */

/* CANIF734 */ /* CANIF737 */ /* CANIF738 */
#if (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON)
/*******************************************************************************************************************
| NAME:             CanIf_GetTxConfirmationState()
| SID:              0x19
| CALLED BY:        CanSM (CAN State Manager)
| PRECONDITIONS:    CanIf has been initialized
| INPUT PARAMETERS: <Controller>            Abstracted CanIf ControllerId which is assigned to a CAN controller
| RETURN VALUES:    <CanIf_NotifStatusType> CANIF_NO_NOTIFICATION    == No transmit event occurred for the requested CAN controller
|                                           CANIF_TX_RX_NOTIFICATION == The requested CAN controller has successfully transmitted any message
| DESCRIPTION:      This service reports, if any TX confirmation has been done for the whole CAN controller since the last CAN controller start.
|                   Synchronous
|                   Reentrant (Not for the same controller)
*******************************************************************************************************************/
/* CanIf_NotifStatusType CanIf_GetTxConfirmationState(uint8 Controller) */
FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_GetTxConfirmationState(uint8 Controller)
{
  CanIf_NotifStatusType eLocalRetVal = CANIF_NO_NOTIFICATION;
# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (V_USE_DUMMY_STATEMENT == STD_ON))
  Controller = Controller; /* PRQA S 3199 */ /* MD_CanIf_Redundancy */
# endif

# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF)
  if (CanIf_Controller_Value >= CANIF_CFG_GENERIC_EMAXCONTROLLER)
  {
    /* CANIF736 */
    CanIf_Det_ReportError(CANIF_GETTXCONFIRMATIONSTATE_API, CANIF_E_PARAM_CONTROLLER);
  }
  else
#  endif
  if (CANIF_CS_UNINIT == CanIf_ControllerMode[CanIf_Controller_Value])
  {
    /* CANIF735 */
    CanIf_Det_ReportError(CANIF_GETTXCONFIRMATIONSTATE_API, CANIF_E_UNINIT);
  }
  else
# endif
  {
    /* Get the actual Tx confirmation state of designated CAN channel */
    eLocalRetVal = CanIf_TxConfirmationState[CanIf_Controller_Value];
  }
  return eLocalRetVal;
}
#endif


/*******************************************************************************************************************
| NAME:             CanIf_XXX()
| SID:              0xXXX
| CALLED BY:        XXX
| PRECONDITIONS:    XXX
| INPUT PARAMETERS: XXX
| RETURN VALUES:    XXX
| DESCRIPTION:      XXX
*******************************************************************************************************************/

#define CANIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/****************************************************************************/
/*  MISRA deviations                                                        */
/****************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_CanIf_1.1:
  Reason: Complex code structure used and not split in modules or functions to make the code compact and efficient.
  Risk: Difficult to understand.
  Prevention: Code inspection and multiple configuration aspects used in component test.

MD_CanIf_1.2:
  Reason: Usual C-access to access an array within a structure.
  Risk: Access unknown memory.
  Prevention: Code inspection and test of the different variants in the component test.

MD_CanIf_8.7:
  Reason: Definition of CanIfState in global section because of better over-view.
  Risk: Name conflict.
  Prevention: Compiler optimize and check for name conflicts.

MD_CanIf_8.8
  Reason: External linkage used for library check.
  Risk: Library check failed.
  Prevention: Integration test version check.

MD_CanIf_8.8_CanIf_Lcfg.c
  Reason: Header files where the call back functions are defined are not known by CanIf.
  Risk: Compiler error occurs if a call back function with the same name is defined more than one time.
  Prevention: Configuration tool allows only to define a call back function with unique name otherwise an error occurs
              during generation process.

MD_CanIf_8.12:
  Reason: Arrays declared without size, because size depends on configuration and is unknown here, especially
          for Link-time tables.
  Risk: Data access outside table.
  Prevention: Code inspection and test of the different variants in the component test.

MD_CanIf_11.1:
  Reason: Cast to different pointer type required to avoid compiler warning due to usage of a union of function pointer types.
  Risk: None due to fact that function pointer are used.
  Prevention: Test of the different variants in the component test.

MD_CanIf_11.5:
  Reason: Pointer cast to P2VAR is necessary to avoid compiler warning because "SduDataPtr" within "PduInfoType" is defined
          as P2VAR during "CanSduPtr" is P2CONST.
  Risk: CAN data could be modified after cast to P2VAR.
  Prevention: Code inspection and test of the different variants in the component test.

MD_CanIf_13.7:
  Reason: This IF statement is used for proper functionality of code.
  Risk: Not needful code.
  Prevention: Code inspection.

MD_CanIf_14.1:
  Reason: This does not lead to any problems but the default-section cannot be avoided as it will result in another MISRA violation.
  Risk: None.
  Prevention: None.

MD_CanIf_14.5:
  Reason: Continue statement is used for proper functionality of code and for better readability.
  Risk: Relevant fragments of code not executed.
  Prevention: Code inspection.

MD_CanIf_14.6:
  Reason: More than one break statement is used to terminate the loop during the binary search algorithm.
          This leads to more efficient code which is easier to read and maintain..
  Risk: Relevant fragments of code not executed.
  Prevention: Code inspection.

MD_CanIf_19.10:
  Reason: Parameter used in structures that does not allow brackets.
  Risk: None atomic parameter lead to compile errors.
  Prevention: Used parameter is always atomic depend on usage.

MD_CanIf_21.1:
  Reason: In case the API is used in the right way then there is no any problem and thus the variable
          which is used to access the array has not to be checked.
  Risk: API does not do what desired.
  Prevention: Use the API in the right way.

MD_CanIf_Redundancy:
  Reason: Dummy assignment used to satisfy API parameters that are never used.
  Risk: None.
  Prevention: None.

MD_CanIf_Redundancy_NotUsed:
  Reason: In case of CANIF_ONE_CONTROLLER_OPTIMIZATION is enabled not all function parameters are used to ensure the optimization.
  Risk: None.
  Prevention: None.

MD_CanIf_1.1_NumberOfMacroDefinitions
  Reason: Code which is much better / easier to maintain.
  Risk: Compiler and preprocessor do not support more than 1024 macro definitions
  Prevention: Test of software with real compiler and preprocessor on real MCU-target.

*/
