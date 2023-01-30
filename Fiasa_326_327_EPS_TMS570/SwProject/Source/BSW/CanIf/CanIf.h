/********************************************************************************************************************
|    File Name: CANIF.H
|
|  Description: API of the AUTOSAR CAN Interface
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
| 2005-09-12  0.01      Ard     - first implementation
| 2006-02-13  0.02      Ard     - activate Tx queue per default
| 2006-05-24  2.00      Ard     - AUTOSAR 2.0
| 2006-06-21  2.01      Ard     - Add CanIf_InitMemory function
| 2006-06-21  2.02      Ard     - Add CanIf_InitMemory function
| 2006-06-22  2.03      Ard     - Change CanIf_Init API
|                                 Changes in version history and defines
| 2006-07-12  2.04      Ard     - Move redefinition to CANIF_READRXPDU_DATA_API to CanIf.h
| 2006-09-18  2.05      Ard     - Add Tx polling mode
| 2006-11-17  2.06      Ard     - Support postbuild configurations
| 2007-02-22  2.07      Ard     - ESCAN00019715: Add dynamic Tx DLC support
|                               - ESCAN00019714: Change ControllerWakeup callback function name
| 2007-05-15  3.00      Ard     - AUTOSAR 2.1
| 2007-09-03  3.01      Ard     - ESCAN00022117: Fix compile warning due to inconsistent function declaration
| 2007-10-12  3.02      Ard     - ESCAN00022751: Fix accidentially raised DET error in CanIf_ConvertPduId
| 2007-11-30  3.03      Ard     - ESCAN00023502: Modify CanIf_InitController API 
| 2008-02-22  4.00      Ard     - ESCAN00024947: AUTOSAR 3.0 
| 2008-04-10  4.01      Ard     - ESCAN00026007: MISRA compliance + Minor changes
|                                 ESCAN00026212: Implement Library version check
| 2008-05-13  4.02      Ard     - ESCAN00026849: Fix unexpected DET Error in case of activated CANIF_CANCEL_SUPPORT_API
| 2008-05-14  4.03      Ard     - ESCAN00026647: Introduce extended generator checks
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
|                                 ESCAN00031732: Fix unexpected Tx confirmation of canceled PDUs (CanIf_CancelTransmit)
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
| 2009-12-18  4.11.04   Rna     - ESCAN00039858: Uppler layer, for example TP, receives wrong data from CanDriver/CanInterface
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
| 2012-04-03            Seu       ESCAN00056144: Implement AUTOSAR 3.2.1 wakeup behavior
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
#ifndef CANIF_H
#define CANIF_H

/* PRQA S 0850 EOF */ /* MD_MSR_19.8 */
/* PRQA S 3453 EOF */ /* MD_MSR_19.7 */

/*******************************************************************************************************************/
/*  Include files                                                                                                  */
/*******************************************************************************************************************/

#include "CanIf_Cfg.h"
/* CanIf_Types.h  is included by CanIf_Cfg.h */

/* Version of CAN Interface module */
/* ##V_CFG_MANAGEMENT ##CQProject : If_AsrIfCan CQComponent : Implementation */
#define IF_ASRIFCAN_VERSION               0x0422u
#define IF_ASRIFCAN_RELEASE_VERSION       0x01u

#define CANIF_SW_MAJOR_VERSION            ((IF_ASRIFCAN_VERSION & 0xFF00u) >> 8u)
#define CANIF_SW_MINOR_VERSION            (IF_ASRIFCAN_VERSION & 0xFFu)
#define CANIF_SW_PATCH_VERSION            (IF_ASRIFCAN_RELEASE_VERSION)

/* Autosar release version */
#define CANIF_AR_MAJOR_VERSION            0x03u
#define CANIF_AR_MINOR_VERSION            0x00u
#define CANIF_AR_PATCH_VERSION            0x01u

#define CANIF_API_MAJOR_VERSION           ((IF_ASRIFCAN_VERSION & 0xFF00u) >> 8u)
#define CANIF_API_MINOR_VERSION           (IF_ASRIFCAN_VERSION & 0xFFu)
#define CANIF_API_PATCH_VERSION           (IF_ASRIFCAN_RELEASE_VERSION)

/*******************************************************************************************************************/
/*  Compatibility defines                                                                                          */
/*******************************************************************************************************************/

#if !defined (CANIF_COMPATIBILITY_AUTOSAR21)
# define CANIF_COMPATIBILITY_AUTOSAR21                              STD_OFF
#endif


/*******************************************************************************************************************/
/*  Function prototypes                                                                                            */
/*******************************************************************************************************************/

#define CANIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Initialisation of global variables, call once before any other CanIf function */
/* void CanIf_InitMemory(void); */
FUNC(void, CANIF_CODE) CanIf_InitMemory(void);

/* Initialisation of CAN Interface */
/* void CanIf_Init(const CanIf_ConfigType *ConfigPtr) */
/* void CanIf_Init(V_MEMROM1 CanIf_ConfigType V_MEMROM2 V_MEMROM3 *ConfigPtr); */
FUNC(void, CANIF_CODE) CanIf_Init( P2CONST(CanIf_ConfigType, AUTOMATIC, CANIF_PBCFG) ConfigPtr);


/* Initialisation of Controller */
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* void CanIf_InitController(uint8 CanNetwork, const CanIf_ControllerConfigType *ConfigPtr) */
FUNC(void, CANIF_CODE) CanIf_InitController(uint8 CanNetwork, P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_PBCFG) ConfigPtr);
#else
/* void CanIf_InitController(uint8 Controller, uint8 ConfigurationIndex) */
FUNC(void, CANIF_CODE) CanIf_InitController(uint8 Controller, uint8 ConfigurationIndex);
#endif



/* Set controller mode */
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_SetControllerMode(uint8 CanNetwork, CanIf_ControllerModeType ControllerMode); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerMode(uint8 CanNetwork, CanIf_ControllerModeType ControllerMode);
#else
/* Std_ReturnType CanIf_SetControllerMode(uint8 Controller, CanIf_ControllerModeType ControllerMode) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerMode(uint8 Controller, CanIf_ControllerModeType ControllerMode);
#endif


/* Get controller mode */
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_GetControllerMode(uint8 CanNetwork, CanIf_ControllerModeType *ControllerModePtr); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerMode(uint8 CanNetwork, P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) ControllerModePtr);
#else
/* Std_ReturnType CanIf_GetControllerMode(uint8 Controller, CanIf_ControllerModeType *ControllerModePtr); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerMode(uint8 Controller, P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) ControllerModePtr);
#endif

/* Initiate transmission */
/* Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Transmit(PduIdType CanTxPduId, P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_MSG_VAR)PduInfoPtr);

/* Request received data */
/* Std_ReturnType CanIf_ReadRxPduData(PduIdType CanRxPduId, PduInfoType *PduInfoPtr) */
#if (CANIF_READRXPDUDATA_API == STD_ON)
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ReadRxPduData(PduIdType CanRxPduId, P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_MSG_VAR) PduInfoPtr);
#endif


/* Configure PDU mode */
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_SetChannelMode(uint8 Channel, CanIf_ChannelSetModeType ChannelRequest) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetChannelMode(uint8 Channel, CanIf_ChannelSetModeType ChannelRequest);
#else
/* Std_ReturnType CanIf_SetPduMode(uint8 Controller, CanIf_PduSetModeType PduModeRequest); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPduMode(uint8 Controller, CanIf_PduSetModeType PduModeRequest);
#endif


/* Request PDU mode */
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_GetChannelMode(uint8 Channel, CanIf_ChannelGetModeType *ChannelModePtr) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetChannelMode(uint8 Channel, P2VAR(CanIf_ChannelGetModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) ChannelModePtr);
#else
/* Std_ReturnType CanIf_GetPduMode(uint8 Controller, CanIf_PduGetModeType *PduModePtr); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetPduMode(uint8 Controller, P2VAR(CanIf_PduGetModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) PduModePtr);
#endif



/* Request version info */
/* void CanIf_GetVersionInfo(Std_VersionInfoType *VersionInfo) */
# if (CANIF_VERSION_INFO_API == STD_ON)
FUNC(void, CANIF_CODE) CanIf_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_VAR) VersionInfo);
# endif

#if (CANIF_TRCV_HANDLING == STD_ON)
# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_SetTransceiverMode(uint8 CanNetwork, CanIf_TransceiverModeType TransceiverMode); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTransceiverMode(uint8 CanNetwork, CanIf_TransceiverModeType TransceiverMode);
# else
/* Std_ReturnType CanIf_SetTransceiverMode(uint8 Transceiver, CanIf_TransceiverModeType TransceiverMode); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTransceiverMode(uint8 Transceiver, CanIf_TransceiverModeType TransceiverMode);
# endif

# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_GetTransceiverMode(uint8 CanNetwork, CanIf_TransceiverModeType *TransceiverModePtr); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTransceiverMode(uint8 CanNetwork, P2VAR(CanIf_TransceiverModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) TransceiverModePtr);
# else
/* Std_ReturnType CanIf_GetTransceiverMode(uint8 Transceiver, CanIf_TransceiverModeType *TransceiverModePtr); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTransceiverMode(uint8 Transceiver, P2VAR(CanIf_TransceiverModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) TransceiverModePtr);
# endif

# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_GetTrcvWakeupReason(uint8 CanNetwork, CanIf_TrcvWakeupReasonType *TrcvWuReasonPtr) */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvWakeupReason(uint8 CanNetwork, P2VAR(CanIf_TrcvWakeupReasonType, AUTOMATIC, CANIF_APPL_STATE_VAR) TrcvWuReasonPtr);
# else
/* Std_ReturnType CanIf_GetTrcvWakeupReason(uint8 Transceiver, CanIf_TrcvWakeupReasonType *TrcvWuReasonPtr); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvWakeupReason(uint8 Transceiver, P2VAR(CanIf_TrcvWakeupReasonType, AUTOMATIC, CANIF_APPL_STATE_VAR) TrcvWuReasonPtr);
# endif

# if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* Std_ReturnType CanIf_SetTransceiverWakeupMode(uint8 CanNetwork, CanIf_TrcvWakeupModeType TrcvWakeupMode); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTransceiverWakeupMode(uint8 CanNetwork, CanIf_TrcvWakeupModeType TrcvWakeupMode);
# else
/* Std_ReturnType CanIf_SetTransceiverWakeupMode(uint8 Transceiver, CanIf_TrcvWakeupModeType TrcvWakeupMode); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTransceiverWakeupMode(uint8 Transceiver, CanIf_TrcvWakeupModeType TrcvWakeupMode);
# endif
#endif

#if (CANIF_PN_TRCV_HANDLING == STD_ON)
/* void CanIf_ConfirmPnAvailability(uint8 Transceiver); */
FUNC(void, CANIF_CODE) CanIf_ConfirmPnAvailability(uint8 Transceiver);

/* void CanIf_ClearTrcvWufFlagIndication(uint8 Transceiver); */
FUNC(void, CANIF_CODE) CanIf_ClearTrcvWufFlagIndication(uint8 Transceiver);

/* void CanIf_CheckTrcvWakeFlagIndication(uint8 Transceiver); */
FUNC(void, CANIF_CODE) CanIf_CheckTrcvWakeFlagIndication(uint8 Transceiver);
#endif

#if (CANIF_TRCV_HANDLING == STD_ON)
/* void CanIf_TrcvModeIndication(uint8 Transceiver, CanIf_TransceiverModeType TransceiverMode); */
FUNC(void, CANIF_CODE) CanIf_TrcvModeIndication(uint8 Transceiver, CanIf_TransceiverModeType TransceiverMode);
#endif

#if (CANIF_PN_TRCV_HANDLING == STD_ON)
/* Std_ReturnType CanIf_ClearTrcvWufFlag(uint8 Transceiver); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ClearTrcvWufFlag(uint8 Transceiver);

/* Std_ReturnType CanIf_CheckTrcvWakeFlag(uint8 Transceiver); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckTrcvWakeFlag(uint8 Transceiver);
#endif

/* Wake Up Handling */
/* Std_ReturnType CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource);

/* Std_ReturnType CanIf_CheckValidation(EcuM_WakeupSourceType WakeupSource); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckValidation(EcuM_WakeupSourceType WakeupSource);

/*void CanIf_SetDynamicTxId(PduIdType CanTxPduId, Can_IdType CanId)*/
FUNC(void, CANIF_CODE) CanIf_SetDynamicTxId(PduIdType CanTxPduId, Can_IdType CanId);

/* NON AUTOSAR API functions */

/* Cancelation of TxPDUs */
/* void CanIf_CancelTransmit(PduIdType CanTxPduId); */
#if (CANIF_CANCEL_SUPPORT_API == STD_ON)
FUNC(void, CANIF_CODE) CanIf_CancelTransmit(PduIdType CanTxPduId);
#endif

/* Bus Off Handling */
#if (CANIF_BUSOFF_RECOVERY_API == STD_ON)
/* void CanIf_ResetBusOffStart(uint8 Controller); */
FUNC(void, CANIF_CODE) CanIf_ResetBusOffStart(uint8 Controller);
/* void CanIf_ResetBusOffEnd(uint8 Controller); */
FUNC(void, CANIF_CODE) CanIf_ResetBusOffEnd(uint8 Controller);
#endif

/* API for non post-build higher layers */
#if (CANIF_SUPPORT_NONPB_API == STD_ON)
/* Std_ReturnType CanIf_ConvertPduId(PduIdType PbPduId, PduIdType *PduId); */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ConvertPduId(PduIdType PbPduId, P2VAR(PduIdType, AUTOMATIC, CANIF_APPL_MSG_VAR)PduId);
#endif


#if (CANIF_ENABLE_TX_LPDU_REMAPPING == STD_ON)
/* Std_ReturnType CanIfWrapper_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr); */
FUNC(Std_ReturnType, CANIF_CODE) CanIfWrapper_Transmit(PduIdType CanTxPduId, P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_MSG_VAR)PduInfoPtr);
#endif

/* CANIF734 */
#if (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON)
/* CanIf_NotifStatusType CanIf_GetTxConfirmationState(uint8 Controller) */
FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_GetTxConfirmationState(uint8 Controller);
#endif

#define CANIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define CANIF_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONST(uint8, CANIF_CONST) CanIf_MainVersion;
extern CONST(uint8, CANIF_CONST) CanIf_SubVersion;
extern CONST(uint8, CANIF_CONST) CanIf_ReleaseVersion;

#define CANIF_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



#endif
