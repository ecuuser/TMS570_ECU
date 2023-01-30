/* Kernbauer Version: 1.16 Konfiguration: Il_AsrCom Erzeugungsgangnummer: 2604 */

/* STARTSINGLE_OF_MULTIPLE */
/* KB begin Com_HeaderText */
/* KB end Com_HeaderText */
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2013 by Vector Informatik GmbH.                                                  All rights reserved.
 
                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  Com.h
      Project:  MICROSAR Com
       Module:  -
    Generator:  -

  \brief Description:  Vector AUTOSAR Com header file
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
-----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
-----------------------------------------------------------------------------------------------------------------------
  Gunnar Meiss                  visms         Vector Informatik GmbH
  Hannes Haas                   vishs         Vector Informatik GmbH
  Michael Bissinger             visbsm        Vector Informatik GmbH
  Safiulla Shakir               visssa        Vector Informatik GmbH
  Dominik Biber                 visdbi        Vector Informatik GmbH
  Sebastian Waldvogel           visswa        Vector Informatik GmbH
  Heiko Huebler                 vishho        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
-----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Change Id     Description
-----------------------------------------------------------------------------------------------------------------------
  01.00.00  2006-08-01  visms, vishs, visbsm  Creation
  01.01.00  2007-02-02  visbsm  ESCAN00018670 Post build support (Com_ConfigStruct)
                        visms   ESCAN00018767 Increment the COM_IMPLEMENTATION_VERSION
                        visms   ESCAN00018739 Compiler warning due to static prototypes
                        visms   ESCAN00018863 CodeInspection
                        visms   ESCAN00018882 Implement support for VStdLib Interface 2.14
                        visms   ESCAN00018919 Implement an AUTOSAR conform include protection
                        visbsm,
                        vishs   ESCAN00018690 No changes here
                        visms   ESCAN00018681 No changes here
                        visms   ESCAN00019017 No changes here
  02.00.00  2007-08-08  visms   ESCAN00019386 Improve Performance of small static interfaces
                        visms   ESCAN00019661 Support COM_IPDU_SIZE as PduInfoPtr ->SduLength
                        visms   ESCAN00019557 VStdLib Compatibility
                        visms   ESCAN00019555 Pclint Misra Improvements
                        visms   ESCAN00019778 [SR:032] Com_IpduGroupTransmit
                        visbsm  ESCAN00019638 Support adding/removing of Rx update bits in post build configuration
                        vishs   ESCAN00019840 No changes here
                        visms,
                        vishs   ESCAN00019909 Add AUTOSAR 2.1 and Gw Support
                        vishs   ESCAN00017202 Optimized shadow buffer handling
                        vishs   ESCAN00019903 No changes
                        visms   ESCAN00020258 Com_ServideIdType Prefix
                        vishs   ESCAN00020214 Added GenSigMissingSourceValue support for signal gateway
                        visbsm  ESCAN00021422 Replaced boolean with uint8 in generated ROM data
                        visbsm  ESCAN00021849 post build indirection
  02.01.00 2007-08-16   visms   ESCAN00021239 Remove Published Information Casts
                        visbsm  ESCAN00022299 Fixed memory qualifiers in Com_ConfigStruct
                        visms   ESCAN00022624 Remove Non-Selectable Post-build feature
                        visbsm  ESCAN00022735 MISRA rework
                        visbsm  ESCAN00022715 Support Com_GetConfigurationId in all configuration variants
                        visbsm  ESCAN00022811 Support signal conversion
  02.02.00 2007-11-27   visbsm  ESCAN00023050 Callout support
                        visbsm  ESCAN00023194 Support indication and rx timeout flags
                        visbsm  ESCAN00023144 No changes here
  02.03.00 2008-01-24   vishs   ESCAN00023768 Support for PDUs, signals and signal groups >8Bytes
                        vishs   ESCAN00023769 Added TP layer PDU support
                        visbsm  ESCAN00024191 Added transmission mode selector, tx signal filters
  02.03.01 2008-02-14   visbsm  ESCAN00024598 No changes here
  03.00.00 2008-02-22   visms   ESCAN00024213 MSN_SW_*_VERSION
                        visms   ESCAN00024475 Remove Com_IpduGroupStart Compatibility
                        visms   ESCAN00024624 Remove Com_ApplicationDataRefType
                        visms   ESCAN00024632 No changes here
                        visms   ESCAN00024631 COM_E_PARAM in Com_Init
                        visms   ESCAN00024630 *MainFunction Calls before Com_Init
                        visms   ESCAN00024643 Rx Deadline Notification Prototype
                        visms   ESCAN00024330 Harmonize Prototypes
                        vishs   ESCAN00024849 No changes here
                        visbsm  ESCAN00018744 Compiler Abstraction
                        visbsm  ESCAN00024602 Memory Abstraction
                        visms   ESCAN00024730 Com_TxBuffer_WriteIpduWithMask Preprocessor
                        visms   ESCAN00024633 Datatype of Com_SignalIdType and Com_SignalGroupIdType
                        visms   ESCAN00023624 Revise Comments
                        visms   ESCAN00025232 No changes here
                        visms   ESCAN00025239 Remove V_CRITICAL_SECTION_USE_VECTOR_COMMENT
                        visbsm  ESCAN00025421 No changes here
                        visbsm  ESCAN00025452 No changes here
  03.01.00 2008-04-14   visbsm  ESCAN00025997 No changes here
                        visms   ESCAN00026159 PduIdType Check
                        visms   ESCAN00026220 No changes here
                        visms   ESCAN00026346 Com_Tp API Assertions
                        visms   ESCAN00027082 No changes here
  03.02.00 2008-06-02   visms   ESCAN00027222 VStdLib MemCpy
                        visbsm  ESCAN00026655 Generator Version Checks
  03.03.00 2008-06-05   visms   ESCAN00027390 Multiple message transmissions in Com_IpduGroupTransmit
                        visms   ESCAN00027131 Com_TriggerIPDUSend
                        visbsm  ESCAN00027503 No changes here
                        visbsm  ESCAN00027871 No changes here
                        visms   ESCAN00027998 Compile Error with Indication or Timeout Flags
                        visms   ESCAN00027257 Support TMS 320
  03.04.00 2008-07-28   vishs   ESCAN00027074 Removed unused constants
                        vishs   ESCAN00028432 Optimized Com_XxBuffer implementation
                        vishs   ESCAN00028436 Precompile variants for signal access
                        visbsm  ESCAN00025070 ComIPduSignalProcessing
                        vishs   ESCAN00028444 Precompile variants for notification handling
                        visbsm  ESCAN00028442 Precompile Optimization of Tx Algorithm
                        vishs   ESCAN00028441 Used function like macros for critical internal routines
                        visbsm  ESCAN00028432 Precompile Optimization for Signal Access
                        visbsm  ESCAN00022803 Compiler switches shall have defined values
                        visbsm  ESCAN00028355 No changes here
                        visms   ESCAN00029123 Compile Error VStdMemCpy APIs with Postbuild data in GPAGE for MCS12x
                        visms   ESCAN00029251 Compile Error with Flag API
                        visms   ESCAN00029125 Compile Error if COM_PBCFG and COM_CONST are different
                        visssa  ESCAN00029357 Remove SubComponent Testsuite API
  03.05.00 2008-09-08   visms   ESCAN00029411 PreCompile and Linktime Crc Check
                        visbsm  ESCAN00028446 Signal Access Macro API
                        visms   ESCAN00030426 Remove Com_EnableReceptionDM, Com_DisableReceptionDM Return Value
                        visms   ESCAN00030236 Add Com_GetConfigurationStringPtr
                        visms   ESCAN00030398 Precompile Optimization of Com_GetConfigurationId
                        visms   ESCAN00030400 Precompile Optimization of Com_GetStatus
                        visms   ESCAN00030402 Precompile Optimization of Com_TriggerTransmit
                        visms   ESCAN00030404 Precompile Optimization of Com_TriggerIPDUSend
                        visms   ESCAN00030408 Precompile Optimization of Com_DeInit
                        visms   ESCAN00030430 Precompile Optimization of Com_MainFunctionRx or Com_MainFunctionTx
                        visms   ESCAN00030432 Precompile Optimization of Com_EnableReceptionDM or Com_DisableReceptionDM
                        visms   ESCAN00028453 Optimize Runtime by Reduction of Static Methods
                        visms   ESCAN00028450 Precompile Optimization of Subcomponents
  03.06.00 2008-11-05   visbsm  ESCAN00031040 Remove signal group routing buffers 
           2008-11-11   visms   ESCAN00031097 No changes here
                        visms   ESCAN00031089 Use COM_VAR_NOINIT for com_ConfigStructPtr
                        visms   ESCAN00031086 Memory Class TYPEDEF for typedefs
                        visms   ESCAN00030867 Update Brief Descriptions
           2008-11-12   visbsm  ESCAN00030036 Error notifications for outstanding not confirmed I-PDUs
           2008-11-14   visms   ESCAN00031090 No changes here
                        visms   ESCAN00030561 No changes here
           2008-11-21   visbsm  ESCAN00028805 Signal invalidation
           2008-11-24   visms   ESCAN00031363 Compile Error with Gnu in Com_Signal_GetSignalAttribute
                        visms   ESCAN00031511 Add Rx Signal Write Access as Macro
           2008-11-27   visms   ESCAN00031687 Compile Error Missing close of const segment
                        visms   ESCAN00031840 Com_SignalGw_MissingSourceValue Mapping with Metrowerks
  03.07.00 2008-12-23   visms   ESCAN00031392 Add ComFirstTimeoutFactor
  03.07.01 2009-02-05   visms   ESCAN00032663 No changes here
  03.07.02 2009-02-06   visms   ESCAN00032893 No changes here
  03.07.03 2009-03-02   visms   ESCAN00033507 No changes here
  03.08.00 2009-03-04   visms   ESCAN00032228 BAC 2.1 Compatibility
                        visms   ESCAN00031092 BSW00441
                        visms   ESCAN00031000 Compiler Error with Com_Signal_SignalBitLengthType
                        visms   ESCAN00033465 Compiler Warning: unused static function "Com_RxBuffer_WriteIpduWithMask"
                        visms   ESCAN00033898 Compiler Error with vstdlib.h (case sensitive)
                        visms   ESCAN00032804 Invalidation Returns Last Valid Value
  03.09.00 2009-04-29   visms   ESCAN00034536 Stopy Cyclic Transmission in case of a Rx I-PDU timeout
                        visms   ESCAN00033724 CAN MOST Gateway
                        visdbi  ESCAN00035230 No changes here
                        visdbi  ESCAN00035411 Com_RxIndication Callout SduPtr is not valid
  03.10.00 2009-06-24   visdbi  ESCAN00035941 No changes here
                        visdbi  ESCAN00035950 No changes here
           2009-07-09   visdbi  ESCAN00036343 Generate Com_InvalidateSignal and Com_InvalidateSignalGroup as Defines
           2009-07-16   visms   ESCAN00036121 Library Preprocessor Checks
           2009-07-16   visms   ESCAN00036378 No changes here
           2009-07-20   visssa  ESCAN00036526 Random data is accessed instead of configuration data after post-build update
           2009-07-20   visms   ESCAN00035785 No changes here
           2009-07-20   visssa  ESCAN00036435 No changes here
           2009-07-22   visms   ESCAN00036578 No changes here
                        visms   ESCAN00034816 Preprocessor error with "memory protection OS"
           2009-07-29   visms   ESCAN00036238 No changes here
                        visms   ESCAN00036359 Update Call Context Description of Com_SendSignal* and Com_InvalidateSignal*
                        visms   ESCAN00036734 No changes here
           2009-07-30   visdbi  ESCAN00036485 ComInvalidNotification at Com_Init, Com_Deinit, Com_IPduGroupStart and Timeout
                        visdbi  ESCAN00036742 No changes here
                        visdbi  ESCAN00038420 No changes here
           2009-08-05   visms   ESCAN00036845 No changes here
                        visdbi  ESCAN00036846 No changes here
                        visdbi  ESCAN00036881 No changes here
                        visdbi  ESCAN00036887 Update bit state is not evaluated while routing Rx signals or signal groups
                        visdbi  ESCAN00036892 Linker Error: unresolved external symbol _Com_RxBuffer_BitIsSet referenced
                                              in function _Com_MainFunctionRouteSignals
           2009-08-06   visdbi  ESCAN00036124 No changes here
                        visdbi  ESCAN00036986 No changes here
                        visdbi  ESCAN00036987 No changes here
           2009-08-06   visms   ESCAN00035442 Cyclic Transmission of Routed Signals with MSV in Timeout
           2009-08-10   visdbi  ESCAN00036974 No changes here
                        visdbi  ESCAN00036979 No changes here
                        visdbi  ESCAN00036982 No changes here
  03.11.00 2009-09-01   visdbi  ESCAN00037509 GenSigMissingSourceValue is not written to the Tx signals after an Rx update bit signal timeout
                        visdbi  ESCAN00037500 Invalidate Tx signals of a routing relation if an Rx timeout occurs
                        visdbi  ESCAN00037470 No changes here
                        visdbi  ESCAN00037222 Com_TxModeHdlr_TriggerIpduSend* and MISRA-C:2004 Rule 5.1
                        visdbi  ESCAN00037549 Compiler error when using  indication/ timeout flags
           2009-09-15   visdbi  ESCAN00037695 No changes here
           2009-09-16   visdbi  ESCAN00037781 No changes here
                        visdbi  ESCAN00037594 No changes here
           2009-09-17   visdbi  ESCAN00037814 Add consistency check for the feature 'Stop Tx PDU Transmission on Rx Timeout'
  03.12.00 2009-10-15   visdbi  ESCAN00038203 Optimization of Critical Sections
                        visdbi  ESCAN00038424 No changes here
                        visdbi  ESCAN00038419 No changes here
                        visdbi  ESCAN00038208 No changes here
           2009-10-22   visdbi  ESCAN00038041 compiler warning: Possible loss of data
                        visdbi  ESCAN00038628 No changes here
           2009-11-02   visdbi  ESCAN00038678 No changes here
           2009-11-19   visdbi  ESCAN00039266 No changes here
                        visdbi  ESCAN00039267 No changes here
                        visdbi  ESCAN00039268 No changes here
                        visdbi  ESCAN00039269 No changes here
           2009-11-27   visdbi  ESCAN00039437 MISRA-C:2004 Rule 5.1 violation (e.g. 'Com_TxModeHdlr_TriggerDeferredIpduSend_Param')
           2009-12-04   visdbi  ESCAN00039531 Execution continues after reporting DET
  03.13.00 2010-01-22   visdbi  ESCAN00040086 No changes here
           2010-02-24   visdbi  ESCAN00040984 Support Optional Invalidation (F334)
           2010-02-26   visdbi  ESCAN00041232 Signal Data with ComBitPosition > 63 are not received or transmitted.
  03.14.00 2010-01-22   visdbi  ESCAN00040337 Support signal access macros for Tx signals (if TMS is not required)
           2010-01-27   visdbi  ESCAN00040403 Support signal access macros with numerical literal as parameter (HisCom0004)
           2010-02-02   visdbi  ESCAN00039640 Add pre-compile switch to use VStdMemCpyFarRamToFarRam()
                        visdbi  ESCAN00039639 No changes here
           2010-02-10   visdbi  ESCAN00040622 Optimization of ROM tables Com_8BitValue, Com_16BitValue, Com_32BitValue
           2010-03-11   visdbi  ESCAN00041503 Feature 'ComGwInvalidateTxOnRxTimeout' is not fully functional
           2010-04-07   visdbi  ESCAN00042122 No changes here
           2010-04-07   visdbi  ESCAN00042123 No changes here
           2010-04-07   visdbi  ESCAN00042125 Pre-compile optimization for flag provider macro access
           2010-04-07   visdbi  ESCAN00042014 Two consecutive stop section pragma in memory mapping abstraction
           2010-04-07   visdbi  ESCAN00042135 Reset timeout flag if the signal / signal group is received again
           2010-04-13   visdbi  ESCAN00042258 Indication flag is set, if an invalid value is received and 'ComDataInvalidAction' is configured to 'NOTIFY'
           2010-04-13   visdbi  ESCAN00041306 Rx Invalidation is not supported in Link-Time and Post-Build Variant
  03.15.00 2010-04-26   visdbi  ESCAN00042540 Support transfer property TRIGGERED_ON_CHANGE
           2010-04-26   visdbi  ESCAN00042004 Support RxFilter "MaskedNewDiffersMaskedOld" (F352)
           2010-04-26   visdbi  ESCAN00042404 MISRA-C:2004 Rule 16.4 violation
           2010-04-27   visdbi  ESCAN00041661 No changes here
           2010-04-27   visdbi  ESCAN00041497 No changes here
           2010-04-27   visdbi  ESCAN00042584 No changes here
           2010-04-29   visdbi  ESCAN00041490 Add u Suffix to Unsigned Constant Defines
           2010-04-29   visdbi  ESCAN00041672 Frequent locks could be optimized
           2010-04-30   visdbi  ESCAN00042672 Adapt function 'Com_TxSigIf_SendByteArray()'
           2010-05-04   visdbi  ESCAN00042723 Signal data pointers must be word aligned
           2010-05-11   visdbi  ESCAN00042851 Compiler error: 'Com_RxNHdlr_TimeoutFlagCnt' undeclared identifier
  03.16.00 2010-05-18   visdbi  ESCAN00043003 No changes here
           2010-05-21   visdbi  ESCAN00043064 Support Transmission Deadline Monitoring
           2010-06-29   visdbi  ESCAN00043649 Support unlimited number of I-Pdu groups
           2010-07-01   visdbi  ESCAN00043741 Support Transmission Deadline Monitoring for Tx Mode None
           2010-07-14   visdbi  ESCAN00043945 No changes here
           2010-07-22   visdbi  ESCAN00044038 ComPdus shall Reference multiple ComIPduGroups
           2010-07-22   visdbi  ESCAN00040121 No changes here
           2010-07-22   visdbi  ESCAN00044285 No changes here
           2010-08-05   visdbi  ESCAN00044472 Adapt function 'Com_RxSigIf_ReceiveByteArray()'
  03.16.01 2010-10-20   visdbi  ESCAN00046208 Compiler error: undeclared identifier 'Com_RxNHdlr_NotificationCnt'
                        visdbi  ESCAN00046209 Compiler error: undeclared identifier 'Com_RxNHdlr_NotiFlagCnt'
                        visdbi  ESCAN00046214 No changes here
  03.17.00 2010-11-18   visdbi  ESCAN00046126 No changes here
           2010-11-30   visms   ESCAN00046263 Perform AUTOSAR version check only for Vector
           2010-12-01   visdbi  ESCAN00047018 Support Dynamic DLC
           2010-12-09   visdbi  ESCAN00045993 No changes here
                        visdbi  ESCAN00045889 No changes here
                        visdbi  ESCAN00047075 Compiler error: 'Com_GetStatus' undefined
                        visdbi  ESCAN00045539 No changes here
           2011-01-27   visdbi  ESCAN00048094 No changes here
                        visdbi  ESCAN00048190 No changes here
  03.18.00 2011-02-15   visdbi  ESCAN00043936 Support Autosar 4.0 R1
           2011-03-15   visdbi  ESCAN00049300 AUTOSAR requirements COM425 deviation
                        visdbi  ESCAN00049306 I-PDU based reception deadline monitoring control
                        visdbi  ESCAN00049309 No changes here
           2011-03-16   visdbi  ESCAN00049371 Support Tx Timeout Flag Interface
           2011-03-22   visdbi  ESCAN00049449 Support Confirmation Flag Interface
  03.18.01 2011-03-29   visdbi  ESCAN00049637 Linker error: unresolved Symbol SchM_Exit_ComCOM_EXCLUSIVE_AREA_1
                        visdbi  ESCAN00049638 Compiler warning: 'SchM_Enter_Com'/'SchM_Exit_Com' undefined
           2011-04-01   visdbi  ESCAN00049768 PcLint warning: Expected unsigned type
           2011-04-05   visdbi  ESCAN00049874 No changes here
           2011-04-06   visdbi  ESCAN00049889 Support old version defines in AR 4.0 COM for compatibility with RTE
           2011-04-06   visdbi  ESCAN00049917 MISRA-C:2004 Rule 19.10 violation for Com_SetIpduGroup()
                        visdbi  ESCAN00049931 No changes here
  03.19.00 2011-04-13   visdbi  ESCAN00050093 ECU resets at a call to 'Com_DeInit()'
                        visdbi  ESCAN00050098 No changes here
           2011-04-19   visdbi  ESCAN00050132 Evaluate 'TRIGGERED_ON_CHANGE' condition in signal access macros
                        visdbi  ESCAN00050106 Change signal group access API description
           2011-04-27   visdbi  ESCAN00050134 AR3-1585: Support ComIPduTriggerTransmitCallout
           2011-05-06   visswa  ESCAN00050650 AR3-1391: Measurement of COM Signals
           2011-05-26   visdbi  ESCAN00050844 No changes here
           2011-05-30   visdbi  ESCAN00050737 AR3-1330: Support configurable update-bit clear context
           2011-05-31   visdbi  ESCAN00050455 AR3-1536: Support TRANSFER-PROPERTY *-WITHOUT-REPETITION
                        visdbi  ESCAN00049155 No changes here
                        visdbi  ESCAN00051287 No changes here
                        visdbi  ESCAN00051286 Remove ComBAC21Compatibility
                        visdbi  ESCAN00051146 AR3-1684: Implement RxIndication and TriggerTransmit Prototypes as specified in ASR 3.2.1
           2011-06-07   visdbi  ESCAN00050780 Remove "Tp" infix Com_TpProvideRxBuffer and Com_TpProvideTxBuffer
                        visdbi  ESCAN00051458 No changes here
           2011-06-14   visdbi  ESCAN00051503 Remove the AUTOSAR 3 Release Version Check
           2011-07-14   visdbi  ESCAN00052072 Compiler reports a missing semicolon in the file com.c
           2011-07-18   visdbi  ESCAN00045379 ECU resets at Com_SignalGw_Indication if a message is received
           2011-08-03   visdbi  ESCAN00052551 Improve MISRA compliance
  03.20.00 2011-09-09   visdbi  ESCAN00053044 ASR4: Rx signal write access
                        visdbi  ESCAN00052493 AR4-44: Support Signal Groups for ASR4
                        visdbi  ESCAN00051598 Remove the AUTOSAR 4 Release Version Check
           2011-09-16   visdbi  ESCAN00052017 No changes here
           2011-09-21   visdbi  ESCAN00053732 [ASR4] Optimization for Rx/Tx only configurations
                        visdbi  ESCAN00053737 Adapted generation of 'Com_LMgt_ConfigurationId'
           2011-09-26   visswa  ESCAN00053257 AR3-2069: Remove non-SchM code for critical section handling
           2011-10-20   visswa  ESCAN00054354 AR3-962: MISRA in Generated Code
                        visswa  ESCAN00053250 AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
  03.21.00 2011-10-25   visswa  ESCAN00054441 [ASR4] Improve MISRA compliance
           2011-10-31   visdbi  ESCAN00054596 No changes here
                        visdbi  ESCAN00053829 AR3-1794: TMS Switch Evaluation in Signal Access Macro API
           2011-11-14   vishho  ESCAN00053957 AR4-49: Explicit TMS Switch
  03.22.00 2011-12-07   vishho  ESCAN00055317 AR3-2327: Event Based Tx Deadline Monitoring
  03.23.00 2012-01-18   visdbi  ESCAN00054050 AR4-46: Support Rx timeout default values which differ from initial default values
           2012-01-19   visdbi  ESCAN00056142 AR4-59: Support Signal Gateway
           2012-01-23   visdbi  ESCAN00055338 No changes here
  03.24.00 2012-03-16   visdbi  ESCAN00056872 AR3-2373: Immediate Signal Routing
           2012-03-22   visdbi  ESCAN00056876 AR3-2372: Route the RX DLC to the TX DLC
           2012-03-30   visdbi  ESCAN00056809 No changes here
                        visdbi  ESCAN00057291 No changes here
           2012-05-16   visdbi  ESCAN00058970 No changes here
           2012-05-22   visdbi  ESCAN00056966 AR3-2374: Implement Silent BSW
           2012-06-12   visdbi  ESCAN00059255 No changes here
  03.25.00 2012-07-10   vishho  ESCAN00058758 AR3-2390: Implement alive timeout behaviour according to Bugzilla 52102
  03.26.00 2012-07-19   vishho  ESCAN00059409 AR4-196: Support Com_TriggerIpduSend with phase shift and direct IF transmisssion
                        vishho  ESCAN00060208 ASR4: Transmission mode MIXED with phase shift not functional 
                        vishho  ESCAN00059432 AR4-60: Support Toyota "MsgID messages" use-case
                        vishho  ESCAN00060397 Improved Transition Mode Switch behavior
           2012-08-02   vishho  ESCAN00052215 No changes here
           2012-08-14   vishho  ESCAN00060798 No changes here
  03.26.01 2012-09-17   vishho  ESCAN00061447 No changes here
                        vishho  ESCAN00061448 No changes here
  03.27.00 2012-10-11   vishho  ESCAN00062098 Alive Timeout not functional 
           2013-01-22   vishho  ESCAN00063426 AR4-349: support TMC EVENT_INT implementation (AUTOSAR 4.0.3 COM789)
                        vishho  ESCAN00063382 Separate Misra/PcLint comments with blank
                        vishho  ESCAN00064587 AR3-2481: Add support for ComTransferProperty TRIGGERED_ON_CHANGE for uint8_N signals
                        vishho  ESCAN00062369 No changes here
                        vishho  ESCAN00057825 No changes here
           2013-02-18   vishho  ESCAN00064670 No changes here
                        vishho  ESCAN00064020 No changes here
                        vishho  ESCAN00064858 AR3-2494: Implement AMD timemeasurement support
                        vishho  ESCAN00065017 No changes here
                        vishho  ESCAN00064140 No changes here
           2013-03-11   visdbi  ESCAN00065562 No changes here
                        visdbi  ESCAN00065756 No changes here
           2013-04-15   visdbi  ESCAN00065859 No changes here
                        visdbi  ESCAN00066680 ASR3: Tx Error Notifications called with disabled interrupts
  03.28.00 2013-07-11   visdbi  ESCAN00068926 No changes here
                        visdbi  ESCAN00066878 ASR4: Compiler warning: implicitly cast to small type
                        visdbi  ESCAN00067150 Clarify transmission context after a send request
  03.29.00 2013-10-07   vishho  ESCAN00070525 No changes here
**********************************************************************************************************************/
/* KB begin Com_LMgt_HeaderFileProlog */
/* KB end Com_LMgt_HeaderFileProlog */
/* KB begin Com_Signal_HeaderFileProlog */
/* KB end Com_Signal_HeaderFileProlog */
/* KB begin Com_Buffer_HeaderFileProlog */
/* KB end Com_Buffer_HeaderFileProlog */
/* KB begin Com_RxBuffer_HeaderFileProlog */
/* KB end Com_RxBuffer_HeaderFileProlog */
/* KB begin Com_RxDlMon_HeaderFileProlog */
/* KB end Com_RxDlMon_HeaderFileProlog */
/* KB begin Com_RxLLIf_HeaderFileProlog */
/* KB end Com_RxLLIf_HeaderFileProlog */
/* KB begin Com_RxNHdlr_HeaderFileProlog */
/* KB end Com_RxNHdlr_HeaderFileProlog */
/* KB begin Com_RxSigIf_HeaderFileProlog */
/* KB end Com_RxSigIf_HeaderFileProlog */
/* KB begin Com_RxUbHdlr_HeaderFileProlog */
/* KB end Com_RxUbHdlr_HeaderFileProlog */
/* KB begin Com_RxInv_HeaderFileProlog */
/* KB end Com_RxInv_HeaderFileProlog */
/* KB begin Com_TxInv_HeaderFileProlog */
/* KB end Com_TxInv_HeaderFileProlog */
/* KB begin Com_TxBuffer_HeaderFileProlog */
/* KB end Com_TxBuffer_HeaderFileProlog */
/* KB begin Com_TxDlMon_HeaderFileProlog */
/* KB end Com_TxDlMon_HeaderFileProlog */
/* KB begin Com_TxEventDlMon_HeaderFileProlog */
/* KB end Com_TxEventDlMon_HeaderFileProlog */
/* KB begin Com_TxLLIf_HeaderFileProlog */
/* KB end Com_TxLLIf_HeaderFileProlog */
/* KB begin Com_TxModeHdlr_HeaderFileProlog */
/* KB end Com_TxModeHdlr_HeaderFileProlog */
/* KB begin Com_TxNHdlr_HeaderFileProlog */
/* KB end Com_TxNHdlr_HeaderFileProlog */
/* KB begin Com_TxSigIf_HeaderFileProlog */
/* KB end Com_TxSigIf_HeaderFileProlog */
/* KB begin Com_SignalGw_HeaderFileProlog */
/* KB end Com_SignalGw_HeaderFileProlog */

#ifndef COM_H
# define COM_H


/**********************************************************************************************************************
 * MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */
/* PRQA S 0750 EOF */ /* MD_MSR_18.4 */
/* PRQA S 3109 EOF */ /* MD_MSR_14.3 */
/* PRQA S 3453 EOF */ /* MD_MSR_19.7 */
/* PRQA S 0342 EOF */ /* MD_Com_0342 */
/* *INDENT-ON* */

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "ComStack_Types.h"
# include "Com_Cfg.h"
# if (COM_DEV_ERROR_DETECT == STD_ON)
#  include "Det.h"
# endif
# include "SchM_Com.h"
# if (COM_VSTDLIB_MEM_API == STD_ON)
#  include "v_inc.h"
# endif

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/* ##V_CFG_MANAGEMENT ##CQProject : Il_AsrCom CQComponent : Implementation */

/** This is the Com bcd coded main- and subversion bcd. */
# define IL_ASRCOM_VERSION                     0x0329u
/** This is the Com bcd coded releaseversion. */
# define IL_ASRCOM_RELEASE_VERSION             0x00u
/** This is the Com decimal Kernelbuilder build version. */
# define IL_ASRCOM_BUILD_VERSION    2604

# define COM_VENDOR_ID              30u
# define COM_MODULE_ID              50u

#  define COM_AR_MAJOR_VERSION       3u
#  define COM_AR_MINOR_VERSION       0u
#  define COM_AR_PATCH_VERSION       1u

# define COM_SW_MAJOR_VERSION       ((IL_ASRCOM_VERSION >> 8u) & 0x00FFu)
# define COM_SW_MINOR_VERSION       (IL_ASRCOM_VERSION & 0x00FFu)
# define COM_SW_PATCH_VERSION       IL_ASRCOM_RELEASE_VERSION

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
/* Com GenTool Compatibility Check */
# if ( COM_IMPLEMENTATION_VERSION != 0x012Fu )
#  error "Com: The generated Configuration Data and Source are inconsistent!"
# endif
# if (COM_VSTDLIB_MEM_API == STD_ON)
#  if ( VSTDLIB__COREHLL_VERSION < 0x0214u )
#   error "Com: Incompatible VSTDLIB__COREHLL_VERSION with this Com Implementation!"
#  endif
# endif

# if defined ( COMSTACKTYPE_VENDOR_ID )
#  if ( COMSTACKTYPE_VENDOR_ID == COM_VENDOR_ID )
#   if ( COMSTACKTYPE_SW_MAJOR_VERSION < 3u )
#    error "Com: Incompatible COMSTACKTYPE_SW_MAJOR_VERSION with this Com Implementation!"
#   else
#    if ( COMSTACKTYPE_SW_MAJOR_VERSION == 3u )
#     if ( COMSTACKTYPE_SW_MINOR_VERSION < 5u )
#      error "Com: Incompatible COMSTACKTYPE_SW_MINOR_VERSION with this Com Implementation!"
#     else
#      if ( COMSTACKTYPE_SW_MINOR_VERSION == 5u )
#       if ( COMSTACKTYPE_SW_PATCH_VERSION < 0u )
#        error "Com: Incompatible COMSTACKTYPE_SW_PATCH_VERSION with this Com Implementation!"
#       endif
#      endif
#     endif
#    endif
#   endif
#  endif/* ( COMSTACKTYPE_VENDOR_ID == COM_VENDOR_ID ) */
# endif/* ( COMSTACKTYPE_VENDOR_ID ) */

/* SchM Compatibility Check */
#  if defined (SYSSERVICE_ASRSCHM_VERSION)
#   if (SYSSERVICE_ASRSCHM_VERSION < 0x0205u)
#    error "Com: Incompatible SYSSERVICE_ASRSCHM_VERSION version with this Com Implementation!"
#   endif
#  endif

/**********************************************************************************************************************
  CONSISTENCY CHECK
**********************************************************************************************************************/
#  if (COM_AUTOSARVERSION != 3)
#   error "Only AUTOSAR R3.x is supported!"
#  endif
#  if defined(V_EXTENDED_BUILD_LIB_CHECK)
#   if(COM_CONFIG_VARIANT == 1)
#    error "The COM_CONFIG_VARIANT is set to Precompile and V_EXTENDED_BUILD_LIB_CHECK is defined. Change the Configuration Variant for a Library!"
#   endif
#  endif
#  if (COM_SIGNALGW_STOPTXONRXTIMEOUT == STD_ON)
#   if (COM_SIGNAL_ACCESS_MACRO_API == STD_ON)
#    error "The feature StopTxOnRxTimeout is not supported with the signal access macro api!"
#   endif
#   if (COM_SIGNALGW_UB == STD_ON)
#    error "The feature StopTxOnRxTimeout is not supported with enabled update bit support!"
#   endif
#  endif

/** \defgroup PrivateMacros PrivateMacros
    \brief    The public constant or function macros shall not be used by the application. */

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/* KB begin Com_LMgt_GlobalConstantMacros */
/** API service called with wrong parameter */
# define COM_E_PARAM                0x01u
/** Error code if any other API service is called before COM was initialized with Com_Init() */
# define COM_E_UNINIT               0x02u
/** the service is currently not available e.g. the corresponding I-PDU group is stopped */
# define COM_SERVICE_NOT_AVAILABLE  0x80u
/** a timeout has occurred */
# define COM_TIMEOUT                0x81u
/** Use the following defines where uint8 is used instead of boolean to avoid platform dependancies (post build) */
# define COM_CFG_FALSE            ((uint8)0x00u)
# define COM_CFG_TRUE             ((uint8)0x01u)


/** \brief Use the following define for GLOBAL COM FUNCTIONS. They are static for the release build, but public for the test build
    \note  The extern keyword is not required for function declarations, but it must be used for variable declarations. */
# if (COM_TSC_TESTCODE == STD_ON)
#  define COM_STATIC
# else
#  define COM_STATIC STATIC
# endif/* (COM_TSC_TESTCODE == STD_ON) */

/** This is the maximum value for a sint8 variable. */
# define COM_SINT8_MAX    127u
/** This is the maximum value for a sint16 variable. */
# define COM_SINT16_MAX   32767u
/** This is the maximum value for a sint32 variable. */
# define COM_SINT32_MAX   2147483647u
/** This is the maximum value for a uint8 variable. */
# define COM_UINT8_MAX    255u
/** This is the maximum value for a uint16 variable. */
# define COM_UINT16_MAX   65535u
/** This is the maximum value for a uint32 variable. */
# define COM_UINT32_MAX   4294967295u
/** This is the maximum value for a uint8 variable depending on the target system. */
#  if defined (_TEXAS_INSTRUMENTS_C_TMS320_)
#   define COM_UINT8_MAX_VAL 0xFFFFu
#  else
#   define COM_UINT8_MAX_VAL 0xFFu
#  endif

# if(COM_CONFIG_VARIANT != 2)
#  define com_Buffer  com_UnionBuffer.raw
# endif
/* KB end Com_LMgt_GlobalConstantMacros */
/* KB begin Com_Signal_GlobalConstantMacros */
/* KB end Com_Signal_GlobalConstantMacros */
/* KB begin Com_Buffer_GlobalConstantMacros */
# if (COM_CONFIG_VARIANT == 1)
#  define COM_BUFFER        COM_SIGNALGROUPIF
# else
#  define COM_BUFFER        STD_ON
# endif
/* KB end Com_Buffer_GlobalConstantMacros */
/* KB begin Com_RxBuffer_GlobalConstantMacros */
/* KB end Com_RxBuffer_GlobalConstantMacros */
/* KB begin Com_RxDlMon_GlobalConstantMacros */
/* KB end Com_RxDlMon_GlobalConstantMacros */
/* KB begin Com_RxLLIf_GlobalConstantMacros */
/* KB end Com_RxLLIf_GlobalConstantMacros */
/* KB begin Com_RxNHdlr_GlobalConstantMacros */
# if (COM_RXNHDLR == STD_ON)
/** \addtogroup PrivateMacros */
/**\{*/
#  define COM_RX_NHDLR_NONOTIFLAG ((Com_RxNHdlr_NotiFlagIdType)COM_RXNHDLR_NOTIFLAGID_MAXVAL)
#  define COM_RX_NHDLR_NOTIMEOUTFLAG ((Com_RxNHdlr_TimeoutFlagIdType)COM_RXNHDLR_TIMEOUTFLAGID_MAXVAL)

#  define COM_TIMEOUTMASK         0x04u
#  define COM_RXNHDLR_INHIBITMASK 0x02u
/**\}*/
# endif/* COM_RXNHDLR == STD_ON */
#  if ((COM_RXDLMON == STD_ON) || (COM_RXUBHDLR_TIMEOUT == STD_ON))
#    if (COM_RXNHDLR_RXFILTER == STD_ON)
#     if ((COM_RXNHDLR_INHIBITNOTIFUNC == STD_ON) && (COM_RXNHDLR_RXFILTER_SIGNOTIFUNC == STD_ON))
#      define COM_RXNHDLR_TIMEOUTMASK STD_ON
#     else
#      define COM_RXNHDLR_TIMEOUTMASK STD_OFF
#     endif
#     if ((COM_RXNHDLR_INHIBITINDFLAG == STD_ON) && (COM_RXNHDLR_RXFILTER_SIGINDFLAG == STD_ON))
#      define COM_RXNHDLR_TIMEOUTMASK_FLAG STD_ON
#     else
#      define COM_RXNHDLR_TIMEOUTMASK_FLAG STD_OFF
#     endif
#     if ((COM_RXNHDLR_INHIBITNOTIFUNC == STD_ON) && (COM_RXNHDLR_RXFILTER_SIGGRPNOTIFUNC == STD_ON))
#      define COM_RXNHDLR_TIMEOUTMASK_SIGGRP STD_ON
#     else
#      define COM_RXNHDLR_TIMEOUTMASK_SIGGRP STD_OFF
#     endif
#     if ((COM_RXNHDLR_INHIBITINDFLAG == STD_ON) && (COM_RXNHDLR_RXFILTER_SIGGRPINDFLAG == STD_ON))
#      define COM_RXNHDLR_TIMEOUTMASK_FLAG_SIGGRP STD_ON
#     else
#      define COM_RXNHDLR_TIMEOUTMASK_FLAG_SIGGRP STD_OFF
#     endif
#    else
#     define COM_RXNHDLR_TIMEOUTMASK      STD_OFF
#     define COM_RXNHDLR_TIMEOUTMASK_FLAG STD_OFF
#     define COM_RXNHDLR_TIMEOUTMASK_SIGGRP      STD_OFF
#     define COM_RXNHDLR_TIMEOUTMASK_FLAG_SIGGRP STD_OFF
#    endif
#  else
#   define COM_RXNHDLR_TIMEOUTMASK      STD_OFF
#   define COM_RXNHDLR_TIMEOUTMASK_FLAG STD_OFF
#   define COM_RXNHDLR_TIMEOUTMASK_SIGGRP      STD_OFF
#   define COM_RXNHDLR_TIMEOUTMASK_FLAG_SIGGRP STD_OFF
#  endif
/* KB end Com_RxNHdlr_GlobalConstantMacros */
/* KB begin Com_RxSigIf_GlobalConstantMacros */
/* KB end Com_RxSigIf_GlobalConstantMacros */
/* KB begin Com_RxUbHdlr_GlobalConstantMacros */
/* KB end Com_RxUbHdlr_GlobalConstantMacros */
/* KB begin Com_RxInv_GlobalConstantMacros */
#  define COM_RXINV_INHIBITMASK   0x01u
/* KB end Com_RxInv_GlobalConstantMacros */
/* KB begin Com_TxInv_GlobalConstantMacros */
/* KB end Com_TxInv_GlobalConstantMacros */
/* KB begin Com_TxBuffer_GlobalConstantMacros */
/* KB end Com_TxBuffer_GlobalConstantMacros */
/* KB begin Com_TxDlMon_GlobalConstantMacros */
/* KB end Com_TxDlMon_GlobalConstantMacros */
/* KB begin Com_TxEventDlMon_GlobalConstantMacros */
/* KB end Com_TxEventDlMon_GlobalConstantMacros */
/* KB begin Com_TxLLIf_GlobalConstantMacros */
/* KB end Com_TxLLIf_GlobalConstantMacros */
/* KB begin Com_TxModeHdlr_GlobalConstantMacros */
# if (COM_TXMODEHDLR == STD_ON)
#  define COM_TXMODEHDLR_TXMODE_NONE      ((Com_TxModeHdlr_TxModeMode)0x00u)
#  define COM_TXMODEHDLR_TXMODE_DIRECT    ((Com_TxModeHdlr_TxModeMode)0x01u)
#  define COM_TXMODEHDLR_TXMODE_PERIODIC  ((Com_TxModeHdlr_TxModeMode)0x02u)
#  define COM_TXMODEHDLR_TXMODE_MIXED     ((Com_TxModeHdlr_TxModeMode)0x03u)

#  define COM_TXMODE_PARAM_TIMEOFFSET         ((Com_TxModeHdlr_TxModeParamRef)0x00u)
#  define COM_TXMODE_PARAM_TIMEPERIOD         ((Com_TxModeHdlr_TxModeParamRef)0x01u)
#  define COM_TXMODE_PARAM_REPETITIONCOUNT    ((Com_TxModeHdlr_TxModeParamRef)0x02u)
#  define COM_TXMODE_PARAM_REPETITIONPERIOD   ((Com_TxModeHdlr_TxModeParamRef)0x03u)
# endif/* COM_TXMODEHDLR == STD_ON */
/* KB end Com_TxModeHdlr_GlobalConstantMacros */
/* KB begin Com_TxNHdlr_GlobalConstantMacros */
/* KB end Com_TxNHdlr_GlobalConstantMacros */
/* KB begin Com_TxSigIf_GlobalConstantMacros */
/* KB end Com_TxSigIf_GlobalConstantMacros */
/* KB begin Com_SignalGw_GlobalConstantMacros */
/* KB end Com_SignalGw_GlobalConstantMacros */

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/* KB begin Com_LMgt_GlobalFunctionMacros */
# if (COM_VSTDLIB_MEM_API == STD_ON)
#  define Com_LMgt_MemSet(DestPtr, Pattern, Length)             VStdMemSet((DestPtr), (Pattern), (uint16)(Length))
#  define Com_LMgt_MemClr(DestPtr, Length)                      VStdMemClr((DestPtr), (uint16)(Length))
#  if defined (COM_USEONLY_FARMEMCPY)
#   define Com_LMgt_MemCpyRamToRam(DestPtr, SrcPtr, Length)      VStdMemCpyFarRamToFarRam((DestPtr), (SrcPtr), (Length))
#   define Com_LMgt_MemCpyRomToRam(DestPtr, SrcPtr, Length)      VStdMemCpyFarRomToFarRam((DestPtr), (SrcPtr), (Length))
#  else
#   define Com_LMgt_MemCpyRamToRam(DestPtr, SrcPtr, Length)      VStdMemCpyRamToRam((DestPtr), (SrcPtr), (Length))
#   define Com_LMgt_MemCpyRomToRam(DestPtr, SrcPtr, Length)      VStdMemCpyRomToRam((DestPtr), (SrcPtr), (Length))
#  endif
# else
#  define Com_LMgt_MemSet(pDest, Pattern, Length)\
{\
  uint16 iCnt = (Length);\
  while(iCnt > (uint16)0x0000)\
  {\
    iCnt--;\
    (pDest)[iCnt] = (Pattern);\
  }\
}

#  define Com_LMgt_MemCpy(pDest, pSrc, Length)\
{\
  uint16 iCnt = (Length);\
  while(iCnt > (uint16)0x0000)\
  {\
    iCnt--;\
    (pDest)[iCnt] = (pSrc)[iCnt];\
  }\
}

#  define Com_LMgt_MemClr(DestPtr, Length)                      Com_LMgt_MemSet((DestPtr), ((uint16)0x0000), (uint16)(Length))
#  define Com_LMgt_MemCpyRamToRam(DestPtr, SrcPtr, Length)      Com_LMgt_MemCpy((DestPtr), (SrcPtr), (Length))
#  define Com_LMgt_MemCpyRomToRam(DestPtr, SrcPtr, Length)      Com_LMgt_MemCpy((DestPtr), (SrcPtr), (Length))
# endif

#  if defined (_TEXAS_INSTRUMENTS_C_TMS320_)
#   define COM_CAST2UINT8(argument)        ((uint8) ((argument) & (uint8)0x00FFU))
#  else
#   define COM_CAST2UINT8(argument)        ((uint8) (argument))
#  endif

# if (COM_TSC_TESTCODE == STD_ON)
/* ##V_TEST_CODE_START ##Ms */
#  define COM_EXCLUSIVE_AREA_0
#  define COM_EXCLUSIVE_AREA_1
#  define COM_EXCLUSIVE_AREA_2
#  define COM_EXCLUSIVE_AREA_3
#  define COM_EXCLUSIVE_AREA_4
#  define SchM_Enter_Com(ComExlusiveAreaId)
#  define SchM_Exit_Com(ComExlusiveAreaId)
/* ##V_TEST_CODE_STOP ##Ms */
# else
# endif

#  if (COM_CONFIG_VARIANT == 3)
#   define Com_ConfigValue(x)                                    (com_ConfigStructPtr->Com_ConfigType##x)
#  else
#   define Com_ConfigValue(x)                                    (Com_ConfigStruct.Com_ConfigType##x)
#  endif

# if (COM_DEV_ERROR_DETECT == STD_ON)
#   define Com_LMgt_CheckDetErrorReturnVoid( CONDITION, API_ID, ERROR_CODE )           { if((CONDITION) == 0) { \
                                                                                          Det_ReportError( (COM_MODULE_ID), 0, ((uint8)(API_ID)), ((uint8)(ERROR_CODE))); \
                                                                                          return; } }
#   define Com_LMgt_CheckDetErrorReturnValue(CONDITION, API_ID, ERROR_CODE, RET_VAL )  { if((CONDITION) == 0) { \
                                                                                          Det_ReportError( (COM_MODULE_ID), 0, ((uint8)(API_ID)), ((uint8)(ERROR_CODE))); \
                                                                                          return (RET_VAL); } }
#   define Com_LMgt_CheckDetErrorContinue(   CONDITION, API_ID, ERROR_CODE )           { if((CONDITION) == 0) { \
                                                                                          Det_ReportError( (COM_MODULE_ID), 0, ((uint8)(API_ID)), ((uint8)(ERROR_CODE))); } }
#   define Com_LMgt_CheckDetErrorBreak(      CONDITION, API_ID, ERROR_CODE )           { if((CONDITION) == 0) { \
                                                                                          Det_ReportError( (COM_MODULE_ID), 0, ((uint8)(API_ID)), ((uint8)(ERROR_CODE))); \
                                                                                          break; } }
#   define Com_LMgt_CallDetErrorContinue(               API_ID, ERROR_CODE )           { Det_ReportError( (COM_MODULE_ID), 0, ((uint8)(API_ID)), ((uint8)(ERROR_CODE))); }
#   define Com_LMgt_CallFatalError(                             ERROR_CODE)              Det_ReportError( (COM_MODULE_ID), 0, ((uint8)COMServiceId_Il_AsrComInternal), ((uint8)(ERROR_CODE)))

#  define Com_LMgt_CheckFatalErrorRetVoid(  CONDITION,         ERROR_CODE )             Com_LMgt_CheckDetErrorReturnVoid((CONDITION), ((uint8)COMServiceId_Il_AsrComInternal), (ERROR_CODE))
#  define Com_LMgt_CheckFatalErrorRetValue( CONDITION,         ERROR_CODE, RET_VAL)     Com_LMgt_CheckDetErrorReturnValue((CONDITION), ((uint8)COMServiceId_Il_AsrComInternal), (ERROR_CODE), (RET_VAL))
#  define Com_LMgt_CheckFatalErrorBreak(    CONDITION,         ERROR_CODE )             Com_LMgt_CheckDetErrorBreak((CONDITION), ((uint8)COMServiceId_Il_AsrComInternal), (ERROR_CODE))
# else
#  define Com_LMgt_CheckDetErrorReturnVoid( CONDITION, API_ID, ERROR_CODE )
#  define Com_LMgt_CheckDetErrorReturnValue(CONDITION, API_ID, ERROR_CODE, RET_VAL )
#  define Com_LMgt_CheckDetErrorContinue(   CONDITION, API_ID, ERROR_CODE )
#  define Com_LMgt_CheckDetErrorBreak(      CONDITION, API_ID, ERROR_CODE )
#  define Com_LMgt_CallDetErrorReturnValue(            API_ID, ERROR_CODE, RET_VAL )
#  define Com_LMgt_CallDetErrorContinue(               API_ID, ERROR_CODE )
#  define Com_LMgt_CheckFatalErrorRetVoid(  CONDITION,         ERROR_CODE )
#  define Com_LMgt_CheckFatalErrorRetValue( CONDITION,         ERROR_CODE, RET_VAL)
#  define Com_LMgt_CheckFatalErrorBreak(    CONDITION,         ERROR_CODE )
#  define Com_LMgt_CallFatalError(                             ERROR_CODE)
# endif/* (COM_DEV_ERROR_DETECT == STD_ON) */

/**********************************************************************************************************************
  Com_LMgt_RxIpduActive
**********************************************************************************************************************/
#  if (COM_LMGT_MULTIPLEIPDUGROUPREF == STD_ON)
#   define Com_LMgt_RxIpduActive(ComRxPduId)        (0 < com_LMgt_RxPduGroupState[(ComRxPduId)])
#  else
#   define Com_LMgt_RxIpduActive(ComRxPduId)        (FALSE != com_LMgt_RxPduGroupState[(ComRxPduId)])
#  endif

/**********************************************************************************************************************
  Com_LMgt_TxIpduActive
**********************************************************************************************************************/
#  if (COM_LMGT_MULTIPLEIPDUGROUPREF == STD_ON)
#   define Com_LMgt_TxIpduActive(ComTxPduId)        (0 < com_LMgt_TxPduGroupState[(ComTxPduId)])
#  else
#   define Com_LMgt_TxIpduActive(ComTxPduId)        (FALSE != com_LMgt_TxPduGroupState[(ComTxPduId)])
#  endif

#  if ((COM_DEV_ERROR_DETECT == STD_ON) || (COM_DE_INIT_API == STD_ON))
#   define Com_LMgt_GetIPduGroupCnt()                  (Com_ConfigValue(Com_LMgt_IPduGroupCnt))
#  endif

/* KB end Com_LMgt_GlobalFunctionMacros */
/* KB begin Com_Signal_GlobalFunctionMacros */
# if (COM_RXSIGIF == STD_ON)
#  define   Com_Signal_GetRxSignalCnt()         (Com_ConfigValue(Com_Signal_RxSignalCnt))
# else
#  define   Com_Signal_GetRxSignalCnt()         ((Com_SignalIdType) 0)
# endif

# if (COM_SIGNALGROUPIF == STD_ON)
#  if (COM_RXSIGIF == STD_ON)
#   define  Com_Signal_GetRxSignalGroupCnt()    (Com_ConfigValue(Com_Signal_RxSignalGroupCnt))
#  else
#   define   Com_Signal_GetRxSignalGroupCnt()   ((Com_SignalGroupIdType) 0)
#  endif
# endif

# if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_ON)
#  define Com_Signal_GetSignalAttribute(SignalId, Attribute) (Com_ConfigValue(Com_Signal_SignalAttributes)[((SignalId) - (Com_Signal_GetRxSignalCnt()))].Com_Signal_SignalAttrType##Attribute)
# else
#  define Com_Signal_GetSignalAttribute(SignalId, Attribute) (Com_ConfigValue(Com_Signal_SignalAttributes)[(SignalId)].Com_Signal_SignalAttrType##Attribute)
# endif
/* KB end Com_Signal_GlobalFunctionMacros */
/* KB begin Com_Buffer_GlobalFunctionMacros */
/* KB end Com_Buffer_GlobalFunctionMacros */
/* KB begin Com_RxBuffer_GlobalFunctionMacros */
/* KB end Com_RxBuffer_GlobalFunctionMacros */
/* KB begin Com_RxDlMon_GlobalFunctionMacros */
/* KB end Com_RxDlMon_GlobalFunctionMacros */
/* KB begin Com_RxLLIf_GlobalFunctionMacros */
/* KB end Com_RxLLIf_GlobalFunctionMacros */
/* KB begin Com_RxNHdlr_GlobalFunctionMacros */
# if (COM_RXNHDLR == STD_ON)
/** \addtogroup PrivateMacros */
/**\{*/
#   if (COM_RXNHDLR_INHIBITNOTIFUNC == STD_ON)
#    if((COM_RXNHDLR_TIMEOUTMASK == STD_ON) || (COM_RXNHDLR_TIMEOUTMASK_SIGGRP == STD_ON))
#     define Com_RxNHdlr_SetRxTimeoutMask(NotificationId) \
      { \
        com_RxNHdlr_InhibitNotification[(NotificationId)] &= COM_CAST2UINT8(~COM_RXNHDLR_INHIBITMASK); \
        com_RxNHdlr_InhibitNotification[(NotificationId)] |= COM_CAST2UINT8(COM_TIMEOUTMASK); \
      }
#     define Com_RxNHdlr_ClrRxTimeoutMask(NotificationId) com_RxNHdlr_InhibitNotification[(NotificationId)] &= COM_CAST2UINT8(~COM_TIMEOUTMASK)
#     define Com_RxNHdlr_SetInhibitNotification(NotificationId) \
      { \
        if(0 == (com_RxNHdlr_InhibitNotification[(NotificationId)] & COM_TIMEOUTMASK)) \
        { \
          com_RxNHdlr_InhibitNotification[(NotificationId)] |= COM_CAST2UINT8(COM_RXNHDLR_INHIBITMASK); \
        } \
      }
#    else
#     define Com_RxNHdlr_SetInhibitNotification(NotificationId) com_RxNHdlr_InhibitNotification[(NotificationId)] |= COM_CAST2UINT8(COM_RXNHDLR_INHIBITMASK)
#    endif /* (COM_RXDLMON == STD_ON) && ((COM_RXNHDLR_RXFILTER_SIGNOTIFUNC == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGGRPNOTIFUNC == STD_ON) */
#    define Com_RxNHdlr_ClrInhibitNotification(NotificationId) com_RxNHdlr_InhibitNotification[(NotificationId)] &= COM_CAST2UINT8(~COM_RXNHDLR_INHIBITMASK)
#   endif/* COM_RXNHDLR_INHIBITNOTIFUNC == STD_ON */
#   if (COM_RXNHDLR_INHIBITINDFLAG == STD_ON)
#    if((COM_RXNHDLR_TIMEOUTMASK_FLAG == STD_ON) || (COM_RXNHDLR_TIMEOUTMASK_FLAG_SIGGRP == STD_ON))
#     define Com_RxNHdlr_SetRxTimeoutMaskFlag(NotificationId) \
      { \
        com_RxNHdlr_InhibitNotiFlag[(NotificationId)] &= COM_CAST2UINT8(~COM_RXNHDLR_INHIBITMASK); \
        com_RxNHdlr_InhibitNotiFlag[(NotificationId)] |= COM_CAST2UINT8(COM_TIMEOUTMASK); \
      }
#     define Com_RxNHdlr_ClrRxTimeoutMaskFlag(NotificationId) com_RxNHdlr_InhibitNotiFlag[(NotificationId)] &= COM_CAST2UINT8(~COM_TIMEOUTMASK)
#     define Com_RxNHdlr_SetInhibitNotificationFlag(NotificationId) \
      { \
        if(0 == (com_RxNHdlr_InhibitNotiFlag[(NotificationId)] & COM_TIMEOUTMASK)) \
        { \
          com_RxNHdlr_InhibitNotiFlag[(NotificationId)] |= COM_CAST2UINT8(COM_RXNHDLR_INHIBITMASK); \
        } \
      }
#    else
#     define Com_RxNHdlr_SetInhibitNotificationFlag(NotificationId) com_RxNHdlr_InhibitNotiFlag[(NotificationId)] |= COM_CAST2UINT8(COM_RXNHDLR_INHIBITMASK)
#    endif /* (COM_RXDLMON == STD_ON) && (COM_RXNHDLR_RXFILTER_SIGINDFLAG == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGGRPINDFLAG == STD_ON) */
#    define Com_RxNHdlr_ClrInhibitNotificationFlag(NotificationId) com_RxNHdlr_InhibitNotiFlag[(NotificationId)] &= COM_CAST2UINT8(~COM_RXNHDLR_INHIBITMASK)
#   endif/* COM_RXNHDLR_INHIBITINDFLAG == STD_ON */
#   define Com_RxNHdlr_NotificationFlagInhibited(NotificationFlagId)  (0 != (com_RxNHdlr_InhibitNotiFlag[(NotificationFlagId)]))
#   if ((COM_RXINV_INHIBITNOTIFUNC == STD_ON) || (COM_RXNHDLR_INHIBITNOTIFUNC == STD_ON))
#    define Com_RxNHdlr_NotificationInhibited(NotificationId)  (com_RxNHdlr_InhibitNotification[(NotificationId)])
#    if((COM_RXNHDLR_TIMEOUTMASK == STD_ON) || (COM_RXNHDLR_TIMEOUTMASK_SIGGRP == STD_ON))
#     define Com_RxNHdlr_CallNotificationFunc(NotiIndex)  { \
                                                            Com_RxNHdlr_ClrRxTimeoutMask(NotiIndex); \
                                                          if (0 == Com_RxNHdlr_NotificationInhibited(NotiIndex)) \
                                                          { \
                                                            Com_RxNHdlr_NotificationFuncPtr[(NotiIndex)](); \
                                                          } \
                                                        }
#    else
#     define Com_RxNHdlr_CallNotificationFunc(NotiIndex)  { \
                                                          if (0 == Com_RxNHdlr_NotificationInhibited(NotiIndex)) \
                                                          { \
                                                            Com_RxNHdlr_NotificationFuncPtr[(NotiIndex)](); \
                                                          } \
                                                        }
#    endif /* ((COM_RXNHDLR_TIMEOUTMASK == STD_ON) || (COM_RXNHDLR_TIMEOUTMASK_SIGGRP == STD_ON)) */
#   else
#    define Com_RxNHdlr_CallNotificationFunc(NotiIndex)  Com_RxNHdlr_NotificationFuncPtr[(NotiIndex)]()
#   endif
/**\}*/
# endif/* (COM_RXNHDLR == STD_ON) */
/* KB end Com_RxNHdlr_GlobalFunctionMacros */
/* KB begin Com_RxSigIf_GlobalFunctionMacros */
/* KB end Com_RxSigIf_GlobalFunctionMacros */
/* KB begin Com_RxUbHdlr_GlobalFunctionMacros */
/* KB end Com_RxUbHdlr_GlobalFunctionMacros */
/* KB begin Com_RxInv_GlobalFunctionMacros */
#  if (COM_RXINV_INHIBITNOTIFUNC == STD_ON)
#   define Com_RxInv_SetInhibitNotification(NotificationId) com_RxNHdlr_InhibitNotification[(NotificationId)] |= COM_CAST2UINT8(COM_RXINV_INHIBITMASK)
#   define Com_RxInv_ClrInhibitNotification(NotificationId) com_RxNHdlr_InhibitNotification[(NotificationId)] &= COM_CAST2UINT8(~COM_RXINV_INHIBITMASK)
#  endif
#  if (COM_RXINV_INHIBITINDFLAG == STD_ON)
#   define Com_RxInv_SetInhibitNotificationFlag(NotificationId) com_RxNHdlr_InhibitNotiFlag[(NotificationId)] |= COM_CAST2UINT8(COM_RXINV_INHIBITMASK)
#   define Com_RxInv_ClrInhibitNotificationFlag(NotificationId) com_RxNHdlr_InhibitNotiFlag[(NotificationId)] &= COM_CAST2UINT8(~COM_RXINV_INHIBITMASK)
#  endif
/* KB end Com_RxInv_GlobalFunctionMacros */
/* KB begin Com_TxInv_GlobalFunctionMacros */
/* KB end Com_TxInv_GlobalFunctionMacros */
/* KB begin Com_TxBuffer_GlobalFunctionMacros */
/* KB end Com_TxBuffer_GlobalFunctionMacros */
/* KB begin Com_TxDlMon_GlobalFunctionMacros */
/* KB end Com_TxDlMon_GlobalFunctionMacros */
/* KB begin Com_TxEventDlMon_GlobalFunctionMacros */
/* KB end Com_TxEventDlMon_GlobalFunctionMacros */
/* KB begin Com_TxLLIf_GlobalFunctionMacros */
/* KB end Com_TxLLIf_GlobalFunctionMacros */
/* KB begin Com_TxModeHdlr_GlobalFunctionMacros */
# if (COM_TXMODEHDLR == STD_ON)
#  define Com_TxModeHdlr_GetCurrentTxMode(TxPduId)          (Com_ConfigValue(Com_TxModeHdlr_TxMode)[com_TxModeHdlr_CurrentTxMode[(TxPduId)]].txMode)
#  define Com_TxModeHdlr_GetTxModeParameter(TxPduId, Param) (Com_ConfigValue(Com_16BitValue)[Com_ConfigValue(Com_TxModeHdlr_TxMode)[com_TxModeHdlr_CurrentTxMode[(TxPduId)]].paramRef + (Param)])
# endif
/* KB end Com_TxModeHdlr_GlobalFunctionMacros */
/* KB begin Com_TxNHdlr_GlobalFunctionMacros */
/* KB end Com_TxNHdlr_GlobalFunctionMacros */
/* KB begin Com_TxSigIf_GlobalFunctionMacros */
/* KB end Com_TxSigIf_GlobalFunctionMacros */
/* KB begin Com_SignalGw_GlobalFunctionMacros */
# if (COM_SIGNALGW_DEFERREDROUTING == STD_ON)
#  if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
#   define Com_SignalGw_HandleSignalGwEvent(gwHdl) (0 < com_SignalGw_IndicationFlag[(gwHdl)])
#   define Com_SignalGw_ClrHandleSignalGwEvent(gwHdl) com_SignalGw_IndicationFlag[(gwHdl)] = 0
#  else
#   define Com_SignalGw_HandleSignalGwEvent(gwHdl) (FALSE != com_SignalGw_IndicationFlag[(gwHdl)])
#   define Com_SignalGw_ClrHandleSignalGwEvent(gwHdl) com_SignalGw_IndicationFlag[(gwHdl)] = FALSE
#  endif/* (COM_DYNAMIC_DLC_SUPPORT == STD_ON) */
# endif/* (COM_SIGNALGW_DEFERREDROUTING == STD_ON) */
/* KB end Com_SignalGw_GlobalFunctionMacros */

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/* KB begin Com_Signal_GlobalDataTypesAndStructures */

/** AUTOSAR COM signal object identifier. */
# if (COM_CONFIG_VARIANT == 1) && (COM_OPTIMIZE_IDTYPES == STD_ON)
#  if (COM_SIGNALCNT <= COM_UINT8_MAX)
typedef uint8 Com_SignalIdType;
#   define COM_SIGNALID_MAXVAL COM_UINT8_MAX_VAL
#  elif (COM_SIGNALCNT <= COM_UINT16_MAX)
typedef uint16 Com_SignalIdType;
#   define COM_SIGNALID_MAXVAL COM_UINT16_MAX
#  else
#   error "The number of signals is either not defined or larger than COM_UINT16_MAX"
#  endif
# else
typedef uint16 Com_SignalIdType;
#  define COM_SIGNALID_MAXVAL COM_UINT16_MAX
# endif/* (COM_CONFIG_VARIANT == 1) */

/** AUTOSAR COM signal conversion handle. */
#  if (COM_CONFIG_VARIANT == 1)
#   if (COM_SIGCONVERSIONCNT < COM_UINT8_MAX)
typedef uint8 Com_Signal_ConversionHdlType;
#    define COM_SIGNAL_CONVERSIONHDL_MAXVAL COM_UINT8_MAX_VAL
#   elif (COM_SIGCONVERSIONCNT < COM_UINT16_MAX)
typedef uint16 Com_Signal_ConversionHdlType;
#    define COM_SIGNAL_CONVERSIONHDL_MAXVAL COM_UINT16_MAX
#   else
#    error "The number of converted signals is either not defined or larger than COM_UINT16_MAX"
#   endif
#  else
typedef uint16 Com_Signal_ConversionHdlType;
#   define COM_SIGNAL_CONVERSIONHDL_MAXVAL COM_UINT16_MAX
#  endif/* (COM_CONFIG_VARIANT == 1) */

/** AUTOSAR COM signal group object identifier. */
# if (COM_CONFIG_VARIANT == 1) && (COM_OPTIMIZE_IDTYPES == STD_ON)
#  if (COM_SIGNALGROUPCNT <= COM_UINT8_MAX)
typedef uint8 Com_SignalGroupIdType;
#   define COM_SIGNALGROUPID_MAXVAL COM_UINT8_MAX_VAL
#  elif (COM_SIGNALGROUPCNT <= COM_UINT16_MAX)
typedef uint16 Com_SignalGroupIdType;
#   define COM_SIGNALGROUPID_MAXVAL COM_UINT16_MAX
#  else
#   error "The number of signal groups is either not defined or larger than COM_UINT16_MAX"
#  endif
# else
typedef uint16 Com_SignalGroupIdType;
#  define COM_SIGNALGROUPID_MAXVAL COM_UINT16_MAX
# endif/* (COM_CONFIG_VARIANT == 1) */

typedef struct
{
  PduLengthType pduOffset;
  PduLengthType grpByteLength;
  uint16 comBufferIdx;
} Com_Signal_SigGrpBufferInfoType;

#  if (COM_LARGESIGNAL == STD_ON)
typedef uint16 Com_Signal_SignalBitLengthType;
#  else
typedef uint8 Com_Signal_SignalBitLengthType;
#  endif

#  if (COM_LARGECOMIPDU == STD_ON)
typedef uint16 Com_Signal_SignalBitPositionType;
#   define COM_SIGNAL_SIGBITPOSITION_MAXVAL COM_UINT16_MAX
#  else
typedef uint8 Com_Signal_SignalBitPositionType;
#   define COM_SIGNAL_SIGBITPOSITION_MAXVAL COM_UINT8_MAX_VAL
#  endif

typedef uint16 Com_Signal_AccessAttrType;
typedef uint8 Com_Signal_FilterAlgorithmType;
typedef uint16 Com_Signal_FilterHdlType;
# define COM_SIGNAL_FILTERHDL_MAXVAL COM_UINT16_MAX
typedef uint16 Com_Signal_FilterParamRef;

typedef struct
{
  Com_Signal_SignalBitLengthType Com_Signal_SignalAttrTypeLength;
  Com_Signal_SignalBitPositionType Com_Signal_SignalAttrTypeBitPosition;
  PduIdType Com_Signal_SignalAttrTypeIpdu;
# if (COM_SIGNALGROUPIF == STD_ON)
  Com_SignalGroupIdType Com_Signal_SignalAttrTypeSignalGroup;
# endif
  Com_Signal_AccessAttrType Com_Signal_SignalAttrTypeAccessAttributes;
  Com_Signal_FilterHdlType Com_Signal_SignalAttrTypeFilterHdl;
#  if (COM_SIGNALCONVERSION == STD_ON)
  Com_Signal_ConversionHdlType Com_Signal_SignalAttrTypeConversionHdl;
#  endif
#  if (((COM_RXINV == STD_ON) || (COM_TXINV == STD_ON)) && (COM_SIGNAL_ACCESS_MACRO_API == STD_OFF))
  uint16 Com_Signal_SignalAttrTypeInvalidValueHdl;
#  endif
} Com_Signal_SignalAttrType;

# if (COM_TXMODEHDLR_TMS == STD_ON)
typedef struct
{
  Com_Signal_FilterAlgorithmType FilterAlgorithm;
  Com_Signal_FilterParamRef ParamRef;
} Com_Signal_SignalFilterType;
# endif

#  if (COM_SIGNALCONVERSION == STD_ON)
typedef uint8 Com_Signal_ConversionVariantType;
typedef sint32 Com_Signal_ConversionFactorType;
typedef sint32 Com_Signal_ConversionOffsetType;
typedef uint32 Com_Signal_ConversionScalingType;

typedef struct
{
  Com_Signal_ConversionVariantType Variant;
  Com_Signal_ConversionFactorType Factor;
  Com_Signal_ConversionOffsetType Offset;
  Com_Signal_ConversionScalingType Scaling;
} Com_Signal_SignalConversionType;

typedef P2CONST(Com_Signal_SignalConversionType, TYPEDEF, COM_PBCFG) Com_Signal_SignalConvRefType;

#  endif/* COM_SIGNALCONVERSION == STD_ON */
/* KB end Com_Signal_GlobalDataTypesAndStructures */
/* KB begin Com_Buffer_GlobalDataTypesAndStructures */
/* KB end Com_Buffer_GlobalDataTypesAndStructures */
/* KB begin Com_RxBuffer_GlobalDataTypesAndStructures */
# if (COM_RXBUFFER == STD_ON)
typedef struct
{
  PduLengthType length;         /* Length of the Rx I-PDU */
  uint16 comBufferIdx;          /* PDU RAM buffer start index to com_Buffer[] */
  uint16 configDataIdx;         /* Offset to Rx PDU specific constant tables i.e. default values, masks */
} Com_RxBuffer_IpduInfoType;
# endif/* COM_RXBUFFER == STD_ON */
/* KB end Com_RxBuffer_GlobalDataTypesAndStructures */
/* KB begin Com_RxDlMon_GlobalDataTypesAndStructures */
/* KB end Com_RxDlMon_GlobalDataTypesAndStructures */
/* KB begin Com_RxLLIf_GlobalDataTypesAndStructures */
# if (COM_RXLLIF == STD_ON) && (COM_RXPDUCALLOUT == STD_ON)
typedef PduIdType Com_RxLLIf_PduCalloutIdType;
typedef P2FUNC(boolean, COM_APPL_CODE, Com_RxLLIf_PduCalloutFuncPtrType) (PduIdType ComRxPduId,
                                                                          CONSTP2CONST(PduInfoType, AUTOMATIC,
                                                                                       COM_APPL_DATA) PduInfoPtr);
# endif
/* KB end Com_RxLLIf_GlobalDataTypesAndStructures */
/* KB begin Com_RxNHdlr_GlobalDataTypesAndStructures */
# if (COM_RXNHDLR == STD_ON)

#  if (COM_CONFIG_VARIANT == 1)
#   if ((COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFUNCTION == STD_ON))
#    if (COM_RXSIGALLNOTIFICATIONCNT < COM_UINT8_MAX)
typedef uint8 Com_RxNHdlr_NotificationIdxType;
#    elif (COM_RXSIGALLNOTIFICATIONCNT < COM_UINT16_MAX)
typedef uint16 Com_RxNHdlr_NotificationIdxType;
#    else
#     error "Com.h: Notification function count is out of range (> COM_UINT16_MAX) or COM_RXSIGALLNOTIFICATIONCNT not defined."
#    endif
#   endif/* ((COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFUNCTION == STD_ON)) */
#   if ((COM_RXNHDLR_TIMEOUTFUNCTION == STD_ON) || (COM_RXUBHDLR_TIMEOUTFUNCTION == STD_ON))
#    if (COM_RXSIGALLTIMEOUTNOTICNT < COM_UINT8_MAX)
typedef uint8 Com_RxNHdlr_TimeoutIdxType;
#    elif (COM_RXSIGALLTIMEOUTNOTICNT < COM_UINT16_MAX)
typedef uint16 Com_RxNHdlr_TimeoutIdxType;
#    else
#     error "Com.h: Error notification function count is out of range (> COM_UINT16_MAX) or COM_RXSIGALLTIMEOUTNOTICNT not defined."
#    endif
#   endif/* ((COM_RXNHDLR_TIMEOUTFUNCTION == STD_ON) || (COM_RXUBHDLR_TIMEOUTFUNCTION == STD_ON)) */
#   if ((COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON))
#    if (COM_RXSIGALLNOTIFLAGCNT < COM_UINT8_MAX)
typedef uint8 Com_RxNHdlr_NotiFlagIdType;
#     define COM_RXNHDLR_NOTIFLAGID_MAXVAL COM_UINT8_MAX_VAL
#    elif (COM_RXSIGALLNOTIFLAGCNT < COM_UINT16_MAX)
typedef uint16 Com_RxNHdlr_NotiFlagIdType;
#     define COM_RXNHDLR_NOTIFLAGID_MAXVAL COM_UINT16_MAX
#    else
#     error "Com.h: Indication flag count is out of range (> COM_UINT16_MAX) or COM_RXSIGALLNOTIFLAGCNT not defined."
#    endif
#   endif
#   if ((COM_RXNHDLR_TIMEOUTFLAG == STD_ON) || (COM_RXUBHDLR_TIMEOUTFLAG == STD_ON))
#    if (COM_RXSIGALLTIMEOUTFLAGCNT < COM_UINT8_MAX)
typedef uint8 Com_RxNHdlr_TimeoutFlagIdType;
#     define COM_RXNHDLR_TIMEOUTFLAGID_MAXVAL COM_UINT8_MAX_VAL
#    elif (COM_RXSIGALLTIMEOUTFLAGCNT < COM_UINT16_MAX)
typedef uint16 Com_RxNHdlr_TimeoutFlagIdType;
#     define COM_RXNHDLR_TIMEOUTFLAGID_MAXVAL COM_UINT16_MAX
#    else
#     error "Com.h: Timeout flag count is out of range (> COM_UINT16_MAX) or COM_RXSIGALLTIMEOUTFLAGCNT not defined."
#    endif
#   endif
#  else/* (COM_CONFIG_VARIANT != 1) */
#    if ((COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFUNCTION == STD_ON))
typedef uint16 Com_RxNHdlr_NotificationIdxType;
#    endif
#    if ((COM_RXNHDLR_TIMEOUTFUNCTION == STD_ON) || (COM_RXUBHDLR_TIMEOUTFUNCTION == STD_ON))
typedef uint16 Com_RxNHdlr_TimeoutIdxType;
#    endif
#    if ((COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON))
typedef uint16 Com_RxNHdlr_NotiFlagIdType;
#     define COM_RXNHDLR_NOTIFLAGID_MAXVAL COM_UINT16_MAX
#    endif
#    if ((COM_RXNHDLR_TIMEOUTFLAG == STD_ON) || (COM_RXUBHDLR_TIMEOUTFLAG == STD_ON))
typedef uint16 Com_RxNHdlr_TimeoutFlagIdType;
#     define COM_RXNHDLR_TIMEOUTFLAGID_MAXVAL COM_UINT16_MAX
#    endif
#  endif/* (COM_CONFIG_VARIANT == 1) */

typedef P2FUNC(void, COM_APPL_CODE, Com_RxNHdlr_NotiFuncPtrType) (void);
typedef P2FUNC(void, COM_APPL_CODE, Com_RxNHdlr_TimeoutFuncPtrType) (void);

#  if ((COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON) || (COM_RXNHDLR_TIMEOUTFLAG == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON) || (COM_RXUBHDLR_TIMEOUTFLAG == STD_ON))
#   if (COM_CONFIG_VARIANT == 1)
#    if ((COM_NOTIFLAGBYTECNT < COM_UINT8_MAX) && (COM_TIMEOUTFLAGBYTECNT < COM_UINT8_MAX))
typedef uint8 Com_RxNHdlr_FlagOffsType;
#    elif ((COM_NOTIFLAGBYTECNT < COM_UINT16_MAX) && (COM_TIMEOUTFLAGBYTECNT < COM_UINT16_MAX))
typedef uint16 Com_RxNHdlr_FlagOffsType;
#    else
#     error "Com.h: Notification flag count is out of range (> COM_UINT16_MAX)."
#    endif
#   else/* (COM_CONFIG_VARIANT != 1) */
typedef uint16 Com_RxNHdlr_FlagOffsType;
#   endif/* COM_CONFIG_VARIANT */

typedef uint8 Com_RxNHdlr_FlagMaskType;

typedef struct
{
  Com_RxNHdlr_FlagOffsType Com_RxNHdlr_FlagInfoTypeOffset;
  Com_RxNHdlr_FlagMaskType Com_RxNHdlr_FlagInfoTypeMask;
} Com_RxNHdlr_FlagInfoType;
#  endif/* ((COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON) || (COM_RXNHDLR_TIMEOUTFLAG == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON) || (COM_RXUBHDLR_TIMEOUTFLAG == STD_ON)) */

#   if ((COM_RXNHDLR_RXFILTER == STD_ON) && (COM_RXSIGNAL_ACCESS_MACRO_API == STD_OFF))
#    if ((COM_RXNHDLR_RXFILTER_SIGNOTIFUNC == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGINDFLAG == STD_ON))
typedef struct
{
  Com_SignalIdType signalId;
#     if (COM_RXNHDLR_RXFILTER_SIGNOTIFUNC == STD_ON)
  Com_RxNHdlr_NotificationIdxType notificationIdx;
#     endif
#     if (COM_RXNHDLR_RXFILTER_SIGINDFLAG == STD_ON)
  Com_RxNHdlr_NotiFlagIdType notificationFlagIdx;
#     endif
#     if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
  PduLengthType validDlc;
#     endif
} Com_RxNHdlr_FilterSigInfoType;
#    endif/* ((COM_RXNHDLR_RXFILTER_SIGNOTIFUNC == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGINDFLAG == STD_ON)) */

#    if ((COM_RXNHDLR_RXFILTER_SIGGRPNOTIFUNC == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGGRPINDFLAG == STD_ON))
typedef struct
{
  Com_RxNHdlr_FilterGrpSigIdxType grpSigIdx;
#     if (COM_RXNHDLR_RXFILTER_SIGGRPNOTIFUNC == STD_ON)
  Com_RxNHdlr_NotificationIdxType notificationIdx;
#     endif
#     if (COM_RXNHDLR_RXFILTER_SIGGRPINDFLAG == STD_ON)
  Com_RxNHdlr_NotiFlagIdType notificationFlagIdx;
#     endif
#     if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
  PduLengthType validDlc;
#     endif
} Com_RxNHdlr_FilterSigGrpInfoType;
#    endif/* ((COM_RXNHDLR_RXFILTER_SIGGRPNOTIFUNC == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGGRPINDFLAG == STD_ON)) */
#   endif/* ((COM_RXNHDLR_RXFILTER == STD_ON) && (COM_RXSIGNAL_ACCESS_MACRO_API == STD_OFF)) */

#  if (COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON)
typedef struct
{
  Com_RxNHdlr_NotificationIdxType notificationIdx;
#   if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
  PduLengthType validDlc;
#   endif
} Com_RxNHdlr_NotiFuncIndirectionType;
#  endif/* (COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON) */

#  if (COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON)
typedef struct
{
  Com_RxNHdlr_NotiFlagIdType notiFlagId;
#   if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
  PduLengthType validDlc;
#   endif
} Com_RxNHdlr_NotiFlagIndirectionType;
#  endif/* (COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON) */

# endif/* (COM_RXNHDLR == STD_ON) */
/* KB end Com_RxNHdlr_GlobalDataTypesAndStructures */
/* KB begin Com_RxSigIf_GlobalDataTypesAndStructures */
/* KB end Com_RxSigIf_GlobalDataTypesAndStructures */
/* KB begin Com_RxUbHdlr_GlobalDataTypesAndStructures */
#  if (COM_RXUBHDLR == STD_ON)
#   if (COM_CONFIG_VARIANT == 1)
#    if (COM_RXUBCNT < COM_UINT8_MAX)
typedef uint8 Com_RxUbHdlr_UbIdType;
#    elif (COM_RXUBCNT < COM_UINT16_MAX)
typedef uint16 Com_RxUbHdlr_UbIdType;
#    else
#     error "Com.h: Update bit count is out of range (> COM_UINT16_MAX) or COM_RXUBCNT not defined."
#    endif
#   else
typedef uint16 Com_RxUbHdlr_UbIdType;
#   endif
        /* if (COM_CONFIG_VARIANT == 1) */
typedef P2FUNC(void, COM_APPL_CODE, Com_RxUbHdlr_NotiFuncPtrType) (void);

typedef struct
{
  Com_Signal_SignalBitPositionType updatebitPosition;
#   if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
  PduLengthType validDlc;
#   endif
} Com_RxUbHdlr_UbBitPositionType;
#  endif
       /* (COM_RXUBHDLR == STD_ON) */
/* KB end Com_RxUbHdlr_GlobalDataTypesAndStructures */
/* KB begin Com_RxInv_GlobalDataTypesAndStructures */
#  if (COM_RXINV == STD_ON)
#   if (COM_RXINV_NOTIINVFUNC == STD_ON)
typedef struct
{
  Com_RxInv_InvNotiFuncIdxType invNotiFuncIdx;  /* Index of the Rx invalid notification function */
  boolean comRxDataTimeoutAction;       /* TRUE: ComRxDataTimeoutAction is set - FALSE: ComRxDataTimeoutAction is not set */
} Com_RxInv_NotiInvFuncIndirType;
#   endif
        /* (COM_RXINV_NOTIINVFUNC == STD_ON) */

#   if (COM_SIGNAL_ACCESS_MACRO_API != STD_ON)
#    if ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON))
typedef struct
{
  Com_RxInv_InvObjIdxType invObjIdx;
#     if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
  PduLengthType validDlc;
#     endif
} Com_RxInv_InvalidObjectIndType;
#    endif
         /* ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON)) */
#   endif
        /* (COM_SIGNAL_ACCESS_MACRO_API != STD_ON) */
#  endif
       /* (COM_RXINV == STD_ON) */
/* KB end Com_RxInv_GlobalDataTypesAndStructures */
/* KB begin Com_TxInv_GlobalDataTypesAndStructures */
/* KB end Com_TxInv_GlobalDataTypesAndStructures */
/* KB begin Com_TxBuffer_GlobalDataTypesAndStructures */
# if (COM_TXBUFFER == STD_ON)
typedef struct
{
  PduLengthType length;         /* Length of the Tx I-PDU */
  uint16 comBufferIdx;          /* PDU RAM buffer start index to com_Buffer[] */
  uint16 configDataIdx;         /* Offset to Tx PDU specific constant tables i.e. default values, masks */
} Com_TxBuffer_IpduInfoType;
# endif/* COM_TXBUFFER == STD_ON */
/* KB end Com_TxBuffer_GlobalDataTypesAndStructures */
/* KB begin Com_TxDlMon_GlobalDataTypesAndStructures */
/* KB end Com_TxDlMon_GlobalDataTypesAndStructures */
/* KB begin Com_TxEventDlMon_GlobalDataTypesAndStructures */
/* KB end Com_TxEventDlMon_GlobalDataTypesAndStructures */
/* KB begin Com_TxLLIf_GlobalDataTypesAndStructures */
# if (COM_TXLLIF == STD_ON)
#  if ((COM_TXPDUCALLOUT == STD_ON) || (COM_TXPDUTRIGGERTRANSMITCALLOUT == STD_ON))
typedef PduIdType Com_TxLLIf_PduCalloutIdType;
typedef P2FUNC(boolean, COM_APPL_CODE, Com_TxLLIf_PduCalloutFuncPtrType) (PduIdType ComTxPduId,
                                                                          CONSTP2VAR(PduInfoType, AUTOMATIC,
                                                                                     AUTOMATIC) PduInfoPtr);
#  endif/* ((COM_TXPDUCALLOUT == STD_ON) || (COM_TXPDUTRIGGERTRANSMITCALLOUT == STD_ON)) */

#   if (COM_TPINTERFACE == STD_ON)
typedef struct
{
  boolean lockedForTpTx;
  PduInfoType pduInfo;
} Com_TxLLIf_TpPduInfoType;
#   endif/* (COM_TPINTERFACE == STD_ON) */
# endif/* COM_TXLLIF == STD_ON */
/* KB end Com_TxLLIf_GlobalDataTypesAndStructures */
/* KB begin Com_TxModeHdlr_GlobalDataTypesAndStructures */
# if (COM_TXMODEHDLR == STD_ON)
typedef uint16 Com_TxModeHdlr_TxModeHdlType;
typedef uint8 Com_TxModeHdlr_TxModeMode;
typedef sint16 Com_TxModeHdlr_TxModeParamRef;
typedef struct
{
  Com_TxModeHdlr_TxModeMode txMode;
  Com_TxModeHdlr_TxModeParamRef paramRef;
} Com_TxModeHdlr_TxModeType;
# endif/* COM_TXMODEHDLR == STD_ON */
/* KB end Com_TxModeHdlr_GlobalDataTypesAndStructures */
/* KB begin Com_TxNHdlr_GlobalDataTypesAndStructures */
# if (COM_TXNHDLR == STD_ON)
#  if (COM_CONFIG_VARIANT == 1)
#   if (COM_TXNHDLR_NOTIFICATIONFUNCTION == STD_ON)
#    if (COM_TXSIGNOTIFICATIONCNT < COM_UINT8_MAX)
typedef uint8 Com_TxNHdlr_NotificationIdxType;
#    elif (COM_TXSIGNOTIFICATIONCNT < COM_UINT16_MAX)
typedef uint16 Com_TxNHdlr_NotificationIdxType;
#    else
#     error "Com.h: Notification function count is out of range (> COM_UINT16_MAX) or COM_TXSIGNOTIFICATIONCNT not defined."
#    endif
#   endif
#   if (COM_TXNHDLR_TIMEOUTFUNCTION == STD_ON)
#    if (COM_TXSIGTIMEOUTNOTICNT < COM_UINT8_MAX)
typedef uint8 Com_TxNHdlr_TimeoutIdxType;
#    elif (COM_TXSIGTIMEOUTNOTICNT < COM_UINT16_MAX)
typedef uint16 Com_TxNHdlr_TimeoutIdxType;
#    else
#     error "Com.h: Error notification function count is out of range (> COM_UINT16_MAX) or COM_TXSIGTIMEOUTNOTICNT not defined."
#    endif
#   endif
#   if (COM_TXNHDLR_ERRORNOTIFICATION == STD_ON)
#    if (COM_TXSIGERRORNOTICNT < COM_UINT8_MAX)
typedef uint8 Com_TxNHdlr_ErrorNotiIdxType;
#    elif (COM_TXSIGERRORNOTICNT < COM_UINT16_MAX)
typedef uint16 Com_TxNHdlr_ErrorNotiIdxType;
#    else
#     error "Com.h: Error notification function count is out of range (> COM_UINT16_MAX) or COM_TXSIGNOTIFICATIONCNT not defined."
#    endif
#   endif
#  else
#    if (COM_TXNHDLR_NOTIFICATIONFUNCTION == STD_ON)
typedef uint16 Com_TxNHdlr_NotificationIdxType;
#    endif
#    if (COM_TXNHDLR_TIMEOUTFUNCTION == STD_ON)
typedef uint16 Com_TxNHdlr_TimeoutIdxType;
#    endif
#    if (COM_TXNHDLR_ERRORNOTIFICATION == STD_ON)
typedef uint16 Com_TxNHdlr_ErrorNotiIdxType;
#    endif
#  endif/* (COM_CONFIG_VARIANT == 1) */
typedef P2FUNC(void, COM_APPL_CODE, Com_TxNHdlr_NotiFuncPtrType) (void);
# endif/* COM_TXNHDLR == STD_ON */

/* KB end Com_TxNHdlr_GlobalDataTypesAndStructures */
/* KB begin Com_TxSigIf_GlobalDataTypesAndStructures */
/* KB end Com_TxSigIf_GlobalDataTypesAndStructures */
/* KB begin Com_SignalGw_GlobalDataTypesAndStructures */
# if (COM_SIGNALGW_DEFERREDROUTING == STD_ON)

/** Specifies indices in the different routing tables */
typedef uint16 Com_SignalGw_RRHdlType;

#  if ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON))
/** Pdu specific routing information */
typedef struct
{
#   if (COM_SIGNALIF == STD_ON)
  Com_SignalGw_RRHdlType SigRRStartIdx;
#   endif
#   if (COM_SIGNALGROUPIF == STD_ON)
  Com_SignalGw_RRHdlType SigGrpRRStartIdx;
#   endif
} Com_SignalGw_IpduInfoType;
#  endif/* ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON)) */

#  if (COM_SIGNALIF == STD_ON)
/** Signal routing relation definition */
typedef struct
{
#   if (COM_SIGNALGW_UB == STD_ON)
  Com_Signal_SignalBitPositionType UbPosition;
#   endif
  Com_SignalIdType Com_SignalGw_SignalRRTypeRxId;
  Com_SignalIdType Com_SignalGw_SignalRRTypeTxId;
#   if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
  PduLengthType validDlc;
#   endif
} Com_SignalGw_SignalRRType;
#  endif


#  if (COM_SIGNALGROUPIF == STD_ON)
/** Definition of partial signal routing relations within a group */
typedef struct
{
  Com_SignalIdType Com_SignalGw_GroupSignalRRTypeRxId;
  Com_SignalIdType Com_SignalGw_GroupSignalRRTypeTxId;
} Com_SignalGw_GroupSignalRRType;


/** Definition of signal group specific routing information */
typedef struct
{
#   if (COM_SIGNALGW_UB == STD_ON)
  Com_Signal_SignalBitPositionType Com_SignalGw_SignalGroupRRTypeUbPosition;
#   endif
  Com_SignalGroupIdType Com_SignalGw_SignalGroupRRTypeRxId;
  Com_SignalGroupIdType Com_SignalGw_SignalGroupRRTypeTxId;
  Com_SignalGw_RRHdlType Com_SignalGw_SignalGroupRRTypePartSigStartIdx;
#   if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
  PduLengthType validDlc;
#   endif
} Com_SignalGw_SignalGroupRRType;
#  endif/* (COM_SIGNALGROUPIF == STD_ON) */

#   if (COM_SIGNALGW_MSV == STD_ON)

/* values of Com_SignalGw_Ipdu/UbMsvEventType.txMode */
#    define COM_SIGNALGW_NOTRIGGERTX (uint8)0x00u
#    define COM_SIGNALGW_TRIGGERTX   (uint8)0x01u

/** Type of IPDU based MSV event handles */
typedef PduIdType Com_SignalGw_IpduMsvEventIdType;
typedef struct
{
  PduIdType Com_SignalGw_IpduMsvEventTypePduId;
  uint8 Com_SignalGw_IpduMsvEventTypeTxMode;
  uint8 Com_SignalGw_IpduMsvEventTypeMask[8];
} Com_SignalGw_IpduMsvEventType;

#    if (COM_RXUBHDLR == STD_ON)
/** Type of Update Bit based MSV event handles */
typedef uint16 Com_SignalGw_UbMsvEventIdType;
typedef struct
{
  PduIdType Com_SignalGw_UbMsvEventTypePduId;
  uint8 Com_SignalGw_UbMsvEventTypeTxMode;
  uint8 Com_SignalGw_UbMsvEventTypeMask[8];
} Com_SignalGw_UbMsvEventType;
#    endif

#   endif/* (COM_SIGNALGW_MSV == STD_ON) */

#   if (COM_SIGNALGW_INVTXONRXTO == STD_ON)
typedef struct
{
#    if ((COM_SIGNALGW_INVSIG_UB == STD_ON) || (COM_SIGNALGW_INVSIG_IPDU == STD_ON))
  Com_SignalGw_TxInvSigHdlType TxInvSigStartIdx;
#    endif
#    if ((COM_SIGNALGW_INVSIGGRP_UB == STD_ON) || (COM_SIGNALGW_INVSIGGRP_IPDU == STD_ON))
  Com_SignalGw_TxInvSigGrpHdlType TxInvSigGrpStartIdx;
#    endif
} Com_SignalGw_Rx2TxInvObjType;
#   endif/* (COM_SIGNALGW_INVTXONRXTO == STD_ON) */
# endif/* (COM_SIGNALGW_DEFERREDROUTING == STD_ON) */
/* KB end Com_SignalGw_GlobalDataTypesAndStructures */
/* KB begin Com_LMgt_GlobalDataTypesAndStructures */


/** This is a status value returned by the API service Com_GetStatus(). */
typedef enum
{
  COM_UNINIT = 0x00,  /**< The AUTOSAR COM module is not initialized or not usable. */
  COM_INIT = 0x01     /**< The AUTOSAR COM Module is initialized and usable. */
} Com_StatusType;

/** Unique identifier of an OSEK COM service. Example: COMServiceId_SendSignal 0x0A. */
typedef enum
{
  COMServiceId_Init = 0x01,
  COMServiceId_DeInit = 0x02,
  COMServiceId_IpduGroupStart = 0x03,
  COMServiceId_IpduGroupStop = 0x04,
  COMServiceId_DisableReceptionDM = 0x05,
  COMServiceId_EnableReceptionDM = 0x06,
  COMServiceId_GetStatus = 0x07,
  COMServiceId_GetConfigurationId = 0x08,
  COMServiceId_GetVersionInfo = 0x09,
  COMServiceId_SendSignal = 0x0A,
  COMServiceId_ReceiveSignal = 0x0B,
  COMServiceId_UpdateShadowSignal = 0x0C,
  COMServiceId_SendSignalGroup = 0x0D,
  COMServiceId_ReceiveSignalGroup = 0x0E,
  COMServiceId_ReceiveShadowSignal = 0x0F,
  COMServiceId_InvalidateSignal = 0x10,
  COMServiceId_ErrorGetServiceId = 0x11,
  COMServiceId_TriggerTransmit = 0x13,
  COMServiceId_RxIndication = 0x14,
  COMServiceId_TxConfirmation = 0x15,
  COMServiceId_InvalidateShadowSignal = 0x16,
  COMServiceId_TriggerIPDUSend = 0x17,
  COMServiceId_MainFunctionRx = 0x18,
  COMServiceId_MainFunctionTx = 0x19,
  COMServiceId_MainFunctionRouteSignals = 0x1A,
  COMServiceId_InvalidateSignalGroup = 0x1B,
  COMServiceId_Il_AsrComInternal = 0x80,     /**< This service Id is used to identify internal checks */
  COMServiceId_IpduGroupTransmit = 0x81,     /**< This service Id is used for Com_IpduGroupTransmit */
  COMServiceId_ProvideTxBuffer = 0x82,     /**< This service Id is used for Com_ProvideTxBuffer */
  COMServiceId_ProvideRxBuffer = 0x83,     /**< This service Id is used for Com_ProvideRxBuffer */
  COMServiceId_TpTxConfirmation = 0x84,      /**< This service Id is used for Com_TpTxConfirmation */
  COMServiceId_TpRxIndication = 0x85,         /**< This service Id is used for Com_TpRxIndication */
  COMServiceId_GetConfigurationString = 0x86,
  COMServiceId_DisableIPduReceptionDM = 0x87,
  COMServiceId_EnableIPduReceptionDM = 0x88
/**< This service Id is used for Com_GetConfigurationString */
} Com_ServiceIdType;

typedef uint8 Com_PduGroupIdType;

#  if (COM_SIGNALGW_MSV == STD_ON)
#   if defined (_METROWERKS_C_MCS12X_)
typedef CONST(uint8, AUTOMATIC) Com_SignalGw_MsvType[COM_MAXINVVALUELENGTH];
#   else
typedef uint8 Com_SignalGw_MsvType[COM_MAXINVVALUELENGTH];
#   endif
#  endif

typedef unsigned char Com_CharType;
typedef P2CONST(Com_CharType, TYPEDEF, COM_PBCFG) Com_CharTypePtr;

typedef struct
{
  /* --- Generator Version Check --- */
#  if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
  uint32 Com_ConfigTypeCom_GeneratorVersion;
#    if (COM_SIGNALGW == STD_ON)
  uint32 Com_ConfigTypeCom_GwGeneratorVersion;
#    endif
#  endif

#  if (COM_CRC_CHECK == STD_ON )
  uint32 Com_ConfigTypeCom_LMgt_PrecompileCRC;
  uint32 Com_ConfigTypeCom_LMgt_LinktimeCRC;
#  endif

  /* --- Global --- */
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_16BitValue;   /* COM_16BITVALUECNT */
# if (((COM_TXMODEHDLR_TMS == STD_ON) && (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)) || (COM_TXINV == STD_ON) || (COM_RXINV == STD_ON))
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_8BitValue;     /* COM_8BITVALUECNT  */
  P2CONST(uint32, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_32BitValue;   /* COM_32BITVALUECNT */
# endif

  /* --- Com_LMgt --- */
#  if (COM_GET_CONFIGURATION_ID_API == STD_ON )
  uint32 Com_ConfigTypeCom_LMgt_ConfigurationId;
#  endif
#  if (COM_GET_CONFIGURATION_STRING_PTR_API == STD_ON )
  P2CONST(Com_CharType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_LMgt_ConfigurationStringPtr;
#  endif

#  if ((COM_DEV_ERROR_DETECT == STD_ON) || (COM_DE_INIT_API == STD_ON))
  Com_PduGroupIdType Com_ConfigTypeCom_LMgt_IPduGroupCnt;       /* COM_IPDUGROUPCNT */
#  endif

#  if ((COM_LMGT_RX == STD_ON) || (COM_LMGT_TX == STD_ON))
#   if (COM_LMGT_MULTIPLEIPDUGROUPREF == STD_ON)
#    if (COM_LMGT_IPDUGROUPHIERARCHY == STD_ON)
  P2CONST(Com_LMgt_IPduGroup2SubGroupsType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_LMgt_IPduGroup2SubGroups;   /* COM_IPDUGROUPCNT + 1 */
  P2CONST(Com_PduGroupIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_LMgt_IPduGroup2SubGroupsIndirection;      /* COM_LMGT_IPDUGROUP2SUBGROUPSTARGETCOUNT */
#    endif
  Com_PduGroupIdType Com_ConfigTypeCom_LMgt_SubIPduGroupCnt;    /* COM_SUBIPDUGROUPCNT */
#   endif
  P2CONST(Com_LMgt_IPduGroup2IPdusType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_LMgt_IPduGroup2IPdus;   /* COM_IPDUGROUPCNT + 1 */
  P2CONST(PduIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_LMgt_IPduGroup2IPdusIndirection;   /* COM_LMGT_IPDUGROUP2IPDUSTARGETCOUNT */
#  endif


  /* --- Com_Signal --- */
# if ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON))
  Com_SignalIdType Com_ConfigTypeCom_Signal_SignalCnt;  /* COM_SIGNALCNT */
# endif
# if (COM_RXSIGIF == STD_ON)
  Com_SignalIdType Com_ConfigTypeCom_Signal_RxSignalCnt;        /* COM_RXSIGNALCNT */
# endif
#  if ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON))
#   if (COM_CONFIG_VARIANT == 3) && (COM_EXTSIGHDLSPACE == STD_ON)
  P2CONST(Com_SignalIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_Signal_Ext2IntSignalId;     /* COM_EXTERNALSIGCNT */
#   endif                       /* (COM_CONFIG_VARIANT == 3) && (COM_EXTSIGHDLSPACE == STD_ON) */
#   if (COM_SIGNALCONVERSION == STD_ON)
  P2CONST(Com_Signal_SignalConversionType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_Signal_SignalConversion;     /* COM_SIGCONVERSIONCNT */
#   endif                       /* (COM_SIGNALCONVERSION == STD_ON) */
#  endif                        /* ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON)) */

# if (COM_SIGNALGROUPIF == STD_ON)
  Com_SignalGroupIdType Com_ConfigTypeCom_Signal_SignalGroupCnt;        /* COM_SIGNALGROUPCNT */
  Com_SignalGroupIdType Com_ConfigTypeCom_Signal_RxSignalGroupCnt;      /* COM_RXSIGNALGROUPCNT */
  P2CONST(PduIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_Signal_SignalGroup2IpduIndirection;        /* COM_SIGNALGROUPCNT */
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_Signal_SignalGroupMaskIdx;    /* COM_SIGNALGROUPCNT */
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_Signal_SignalGroupMask;
  P2CONST(Com_Signal_SigGrpBufferInfoType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_Signal_SigGrpBufferInfo;     /* COM_SIGNALGROUPCNT */
#   if (COM_CONFIG_VARIANT == 3) && (COM_EXTSIGHDLSPACE == STD_ON)
  P2CONST(Com_SignalGroupIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_Signal_Ext2IntSignalGroupId;   /* COM_EXTERNALSIGGRPCNT */
#   endif                       /* (COM_CONFIG_VARIANT == 3) && (COM_EXTSIGHDLSPACE == STD_ON) */
# endif                         /* (COM_SIGNALGROUPIF == STD_ON) */

# if (COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON)
#  if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)
  P2CONST(Com_Signal_SignalAttrType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_Signal_SignalAttributes;   /* COM_SIGNALCNT + 1 */
#  endif
# endif
# if ((COM_TXMODEHDLR_TMS == STD_ON) && (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF))
  P2CONST(Com_Signal_SignalFilterType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_Signal_SignalFilter;     /* COM_FILTERCNT */
# endif

  /* --- Com_RxBuffer --- */
# if (COM_RXBUFFER == STD_ON)
  PduIdType Com_ConfigTypeCom_RxBuffer_RxIpduCnt;
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxBuffer_IpduInitValue;
  P2CONST(Com_RxBuffer_IpduInfoType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxBuffer_IpduInfo; /* COM_RXIPDUCNT */
# endif

  /* --- Com_RxNHdlr  || Com_RxUbHdlr --- */
# if ((COM_RXNHDLR == STD_ON) || (COM_RXUBHDLR == STD_ON))
#  if (((COM_RXNHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) && (COM_RXNHDLR_IMMEDIATE_SIGNALPROCESSING == STD_ON)) || ((COM_RXUBHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) && (COM_RXUBHDLR_IMMEDIATE_SIGNALPROCESSING == STD_ON)))
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_DeferredSignalProcessing;      /* COM_RXIPDUCNT */
#  endif
# endif

  /* --- Com_RxNHdlr --- */
# if (COM_RXNHDLR == STD_ON)
#  if (COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON)
  P2CONST(Com_RxNHdlr_NotificationIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_Ipdu2NotificationFunctions;  /* COM_MAXRXIPDUCNT + 1 */
  P2CONST(Com_RxNHdlr_NotiFuncIndirectionType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_NotiFuncIndirection;     /* COM_RXSIGNOTIFICATIONCNT */
#  endif
#  if (COM_RXNHDLR_TIMEOUTFUNCTION == STD_ON)
  P2CONST(Com_RxNHdlr_TimeoutIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_Ipdu2TimeoutFunctions;    /* COM_MAXRXIPDUCNT + 1 */
  P2CONST(Com_RxNHdlr_TimeoutIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_TimeoutFuncIndirection;   /* COM_RXSIGTIMEOUTNOTICNT */
#  endif
#  if (COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON)
  P2CONST(Com_RxNHdlr_NotiFlagIndirectionType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_NotiFlagIndirection;     /* COM_RXSIGNOTIFLAGCNT */
  P2CONST(Com_RxNHdlr_NotiFlagIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_Ipdu2NotificationFlags;   /* COM_MAXRXIPDUCNT + 1 */
#  endif
#  if (COM_RXNHDLR_TIMEOUTFLAG == STD_ON)
  P2CONST(Com_RxNHdlr_TimeoutFlagIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_TimeoutFlagIndirection;        /* COM_RXSIGTIMEOUTFLAGCNT */
  P2CONST(Com_RxNHdlr_TimeoutFlagIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_Ipdu2TimeoutFlags;     /* COM_MAXRXIPDUCNT + 1 */
#  endif
#   if ((COM_RXNHDLR_RXFILTER == STD_ON) && (COM_RXSIGNAL_ACCESS_MACRO_API == STD_OFF))
#    if ((COM_RXNHDLR_RXFILTER_SIGNOTIFUNC == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGINDFLAG == STD_ON))
  P2CONST(Com_RxNHdlr_FilterSigIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_IPdu2FilterSigs;        /* COM_RXIPDUCNT + 1 */
  P2CONST(Com_RxNHdlr_FilterSigInfoType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_FilterSigInfo; /* COM_RXNHDLR_FILTERSIGCNT */
#    endif
#    if ((COM_RXNHDLR_RXFILTER_SIGGRPNOTIFUNC == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGGRPINDFLAG == STD_ON))
  P2CONST(Com_RxNHdlr_FilterSigGrpIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_IPdu2FilterSigGrps;  /* COM_RXIPDUCNT + 1 */
  P2CONST(Com_RxNHdlr_FilterSigGrpInfoType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_FilterSigGrpInfo;   /* COM_RXNHDLR_FILTERSIGGRPCNT + 1 */
#     if (COM_RXNHDLR_RXFILTER_GRPSIG == STD_ON)
  P2CONST(Com_SignalIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxNHdlr_FilterGrpSigIndirection;    /* COM_RXNHDLR_FILTERGRPSIGCNT */
#     endif
#    endif
#   endif
# endif                         /* COM_RXNHDLR == STD_ON */

  /* --- Com_RxUbHdlr --- */
#  if (COM_RXUBHDLR == STD_ON)
  Com_RxUbHdlr_UbIdType Com_ConfigTypeCom_RxUbHdlr_UpdateBitCnt;
  P2CONST(Com_RxUbHdlr_UbIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxUbHdlr_Ipdu2UpdateBits;      /* COM_MAXRXIPDUCNT + 1 */
  P2CONST(Com_RxUbHdlr_UbBitPositionType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxUbHdlr_UbBitPosition;       /* COM_RXUBCNT */
#   if (COM_RXUBHDLR_NOTIFICATIONFUNCTION == STD_ON)
  P2CONST(Com_RxNHdlr_NotificationIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxUbHdlr_NotiFuncIndirection;        /* COM_RXUBCNT */
#   endif
#   if (COM_RXUBHDLR_TIMEOUTFUNCTION == STD_ON)
  P2CONST(Com_RxNHdlr_TimeoutIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxUbHdlr_TimeoutFuncIndirection;  /* COM_RXUBCNT */
#   endif
#   if (COM_RXUBHDLR_TIMEOUTDEFAULTVALUE == STD_ON)
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxUbHdlr_TimeoutMaskIdx;      /* COM_RXUBCNT */
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxUbHdlr_TimeoutMask;
#   endif
#   if (COM_RXUBHDLR_FIRSTTIMEOUT == STD_ON)
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxUbHdlr_FirstTimeoutTime;    /* COM_RXUBCNT */
#   endif
#   if (COM_RXUBHDLR_TIMEOUT == STD_ON)
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxUbHdlr_TimeoutTime; /* COM_RXUBCNT */
#   endif
#   if (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON)
  P2CONST(Com_RxNHdlr_NotiFlagIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxUbHdlr_NotiFlagHdl;     /* COM_RXUBCNT */
#   endif
#   if (COM_RXUBHDLR_TIMEOUTFLAG == STD_ON)
  P2CONST(Com_RxNHdlr_TimeoutFlagIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxUbHdlr_TimeoutFlagHdl;       /* COM_RXUBCNT */
#   endif
#  endif

  /* --- Com_RxDlMon --- */
# if (COM_RXDLMON == STD_ON)
#  if (COM_RXDLMON_FIRSTTIMEOUT == STD_ON)
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxDlMon_FirstTimeoutTime;     /* COM_MAXRXIPDUCNT */
#  endif
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxDlMon_TimeoutTime;  /* COM_MAXRXIPDUCNT */
#  if (COM_RXDLMON_TIMEOUTDEFAULTVALUE == STD_ON)
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxDlMon_IpduTimeoutMask;
#  endif
# endif

  /* --- Com_RxLLIf --- */
# if (COM_RXLLIF == STD_ON) && (COM_RXPDUCALLOUT == STD_ON)
  P2CONST(Com_RxLLIf_PduCalloutIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxLLIf_PduCalloutIndirection;    /* COM_MAXRXIPDUCNT */
# endif

  /* --- Com_RxInv --- */
#  if (COM_RXINV == STD_ON)
#   if (COM_SIGNAL_ACCESS_MACRO_API != STD_ON)
#    if (COM_SIGNALIF == STD_ON)
  P2CONST(Com_RxInv_InvSigIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxInv_IPdu2InvalidSignals;   /* COM_RXIPDUCNT + 1 */
  P2CONST(Com_ValueIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxInv_InitValueIdx; /* COM_RXINVSIGNALCNT */
  P2CONST(Com_SignalIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxInv_InvalidSignalHandles; /* COM_RXINVSIGNALCNT */
#    endif
#    if (COM_SIGNALGROUPIF == STD_ON)
  P2CONST(Com_RxInv_InvSigGroupIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxInv_IPdu2InvalidSignalGroups; /* COM_RXIPDUCNT + 1 */
  P2CONST(Com_SignalIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxInv_InvalidGroupSignalHandles;    /* COM_RXINVGROUPSIGNALCNT */
#    endif
#    if ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON))
  P2CONST(Com_RxInv_InvalidObjectIndType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxInv_InvalidObjectIndirection;       /* COM_RXINVSIGNALCNT + COM_RXINVSIGNALGROUPCNT */
#    endif
#   endif
#   if (COM_RXINV_NOTIINVFUNC == STD_ON)
#    if ( (COM_RXINV_NOTIINVFUNC_NOUB_TO == STD_ON) || (COM_RXINV_NOTIINVFUNC_NOUB == STD_ON) )
  P2CONST(Com_RxInv_NotiInvObjNoUbIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxInv_IPdu2NotiInvObjNoUb;   /* COM_RXIPDUCNT + 1 */
  P2CONST(Com_RxInv_NotiInvFuncIndirType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxInv_NotiInvFuncIndirNoUb;   /* COM_RXINVNOTIINVOBJNOUBCNT */
#    endif
#    if ( (COM_RXINV_NOTIINVFUNC_UB == STD_ON) || (COM_RXINV_NOTIINVFUNC_UB_TO == STD_ON) )
  P2CONST(Com_RxInv_NotiInvFuncIndirType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_RxInv_NotiInvFuncIndirUb;     /* COM_RXUBCNT */
#    endif
#   endif
#  endif

  /* --- Com_TxBuffer --- */
# if (COM_TXBUFFER == STD_ON)
  PduIdType Com_ConfigTypeCom_TxBuffer_TxIpduCnt;
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxBuffer_IpduInitValue;
  P2CONST(Com_TxBuffer_IpduInfoType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxBuffer_IpduInfo; /* COM_TXIPDUCNT */
# endif

  /* --- Com_TxNHdlr --- */
# if (COM_TXNHDLR_NOTIFICATIONFUNCTION == STD_ON)
  P2CONST(Com_TxNHdlr_NotificationIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxNHdlr_Ipdu2NotificationFunctions;  /* COM_MAXTXIPDUCNT + 1 */
  P2CONST(Com_TxNHdlr_NotificationIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxNHdlr_NotiFuncIndirection; /* COM_TXSIGNOTIFICATIONCNT */
# endif
# if ((COM_TXNHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) && (COM_TXNHDLR_IMMEDIATE_SIGNALPROCESSING == STD_ON))
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxNHdlr_CallNotiDeferred;      /* COM_TXIPDUCNT */
# endif

# if (COM_TXNHDLR_ERRORNOTIFICATION == STD_ON)
  P2CONST(Com_TxNHdlr_ErrorNotiIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxNHdlr_Ipdu2ErrorFunctions;    /* COM_MAXTXIPDUCNT + 1 */
  P2CONST(Com_TxNHdlr_ErrorNotiIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxNHdlr_ErrorNotiFuncIndirection;       /* COM_TXSIGNOTIFICATIONCNT */
# endif

# if (COM_TXNHDLR_TIMEOUTFUNCTION == STD_ON)
  P2CONST(Com_TxNHdlr_TimeoutIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxNHdlr_Ipdu2TimeoutFunctions;    /* COM_MAXTXIPDUCNT + 1 */
  P2CONST(Com_TxNHdlr_TimeoutIdxType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxNHdlr_TimeoutFuncIndirection;   /* COM_TXSIGTIMEOUTNOTICNT */
# endif

  /* --- Com_TxSigIf --- */
# if (COM_TXSIGIF == STD_ON)
#  if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)
#   if (COM_TXMODEHDLR_DIRECT_TRANSMISSION == STD_ON)
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxSigIf_SignalTransferEventProperty;   /* COM_TXSIGNALCNT */
#   endif
#  endif
#  if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)
#   if (COM_TXMODEHDLR_TMS == STD_ON)
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxSigIf_SignalFilterStateMask; /* COM_TXSIGNALCNT */
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxSigIf_SignalFilterStateOffset;      /* COM_TXSIGNALCNT */
#   endif
#  endif

#  if (COM_TXUBHDLR == STD_ON)
#   if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)
  P2CONST(Com_Signal_SignalBitPositionType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxSigIf_Signal2UbBitPos;    /* COM_TXSIGNALCNT */
#   endif
#   if (COM_SIGNALGROUPIF == STD_ON)
  P2CONST(Com_Signal_SignalBitPositionType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxSigIf_SignalGroup2UbBitPos;       /* COM_TXSIGNALGROUPCNT */
#   endif
#  endif

# endif

  /* --- Com_TxModeHdlr --- */
# if (COM_TXMODEHDLR == STD_ON)
  P2CONST(Com_TxModeHdlr_TxModeHdlType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxModeHdlr_TxModeTrue;  /* COM_MAXTXIPDUCNT */
#  if (COM_TXMODEHDLR_TXMODEFALSE == STD_ON)
  P2CONST(Com_TxModeHdlr_TxModeHdlType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxModeHdlr_TxModeFalse; /* COM_MAXTXIPDUCNT */
#  endif
  P2CONST(Com_TxModeHdlr_TxModeType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxModeHdlr_TxMode; /* COM_MAXTXMODECNT */
#  if (COM_TXMODEHDLR_TXMODEFALSE == STD_ON)
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxModeHdlr_SigFilterStartIdx; /* COM_TXIPDUCNT + 1 */
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxModeHdlr_FilterStateInitBytes;       /* COM_FILTERSTATEBYTECNT */
#  endif
#  if (COM_TXMODEHDLR_MINIMUM_DELAY == STD_ON)
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxModeHdlr_MinDelayTime;      /* COM_MAXTXIPDUCNT */
#  endif                        /* (COM_TXMODEHDLR_MINIMUM_DELAY == STD_ON) */
# endif

  /* --- Com_TxLLIf --- */

# if (COM_TXUBHDLR == STD_ON)
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxLLIf_ClearUbMask;
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxLLIf_ClearUpdateBit; /* COM_TXIPDUCNT */
# endif


# if (COM_TXLLIF == STD_ON)
#  if (COM_TXPDUCALLOUT == STD_ON)
  P2CONST(Com_TxLLIf_PduCalloutIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxLLIf_PduCalloutIndirection;    /* COM_MAXTXIPDUCNT */
#  endif
#   if (COM_TXPDUTRIGGERTRANSMITCALLOUT == STD_ON)
  P2CONST(Com_TxLLIf_PduCalloutIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxLLIf_PduTriggerTransmitCalloutIndirection;     /* COM_MAXTXIPDUCNT */
#   endif
# endif

#  if (COM_TPINTERFACE == STD_ON)
  P2CONST(uint8, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxLLIf_IsTpLayerIpdu;  /* COM_TXIPDUCNT */
#  endif

  /* --- Com_TxDlMon --- */
# if (COM_TXDLMON == STD_ON)
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxDlMon_TimeoutTime;  /* COM_TXIPDUCNT */
#   if (COM_TXDLMON_TXCONFIRMATION == STD_ON)
  P2CONST(boolean, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxDlMon_TimeoutContext;      /* COM_TXIPDUCNT */
#   endif
# endif

  /* --- Com_TxEventDlMon --- */
#  if (COM_TXEVENTDLMON == STD_ON)
  P2CONST(uint16, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_TxEventDlMon_TimeoutConst;    /* COM_TXIPDUCNT */
#  endif

  /* --- Com_SignalGw --- */
# if (COM_SIGNALGW == STD_ON)
  uint16 Com_ConfigTypeCom_SignalGw_SignalBufferIdx;    /* signal gateway routing buffer with com_Buffer[] */
  P2CONST(PduIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_RxIpdu2GwHandle;  /* COM_MAXRXIPDUCNT */
# endif
# if (COM_SIGNALGW_DEFERREDROUTING == STD_ON)
  PduIdType Com_ConfigTypeCom_SignalGw_NumberOfRoutedIpdus;
#  if (COM_SIGNAL_ACCESS_MACRO_API != STD_ON)
#   if ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON))
  P2CONST(Com_SignalGw_IpduInfoType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_IpduRoutingInfo;  /* COM_ROUTEDRXIPDUCNT + 1 */
#   endif
#   if (COM_SIGNALIF == STD_ON)
  P2CONST(Com_SignalGw_SignalRRType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_SignalRR; /* COM_SIGNALRRCNT + 1 */
#   endif
#   if (COM_SIGNALGROUPIF == STD_ON)
  P2CONST(Com_SignalGw_SignalGroupRRType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_SignalGroupRR;       /* COM_SIGNALGROUPRRCNT + 1 */
  P2CONST(Com_SignalGw_GroupSignalRRType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_GroupSignalRR;       /* COM_PARTSIGNALRRCNT + 1 */
#   endif
#  endif
/* --- Com_SignalGw Missing Source Value--- */
#   if (COM_SIGNALGW_MSV == STD_ON)
  P2CONST(Com_SignalGw_MsvType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_MissingSourceValue;    /* COM_TXIPDUCNT */
  P2CONST(Com_SignalGw_IpduMsvEventIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_RxIpdu2MsvEvents;   /* COM_RXIPDUCNT + 1 */
  P2CONST(Com_SignalGw_IpduMsvEventType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_IpduMsvEvent; /* COM_RXIPDUMSVEVENTCNT */

#    if (COM_RXUBHDLR == STD_ON)
  P2CONST(Com_SignalGw_UbMsvEventIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_RxUb2MsvEvents;       /* COM_RXUBCNT + 1 */
  P2CONST(Com_SignalGw_UbMsvEventType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_UbMsvEvent;     /* COM_RXUBMSVEVENTCNT */
#    endif
#   endif

#   if (COM_SIGNALGW_INVTXONRXTO == STD_ON)
#    if (COM_SIGNALGW_INVTXONRXTO_UB == STD_ON)
  P2CONST(Com_SignalGw_Rx2TxInvObjType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_RxUb2TxInvObj; /* COM_RXUBCNT + 1 */
#    endif
#    if (COM_SIGNALGW_INVTXONRXTO_IPDU == STD_ON)
  P2CONST(Com_SignalGw_Rx2TxInvObjType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_RxIPdu2TxInvObj;       /* COM_ROUTEDRXIPDUCNT + 1 */
#    endif
#    if ((COM_SIGNALGW_INVSIG_UB == STD_ON) || (COM_SIGNALGW_INVSIG_IPDU == STD_ON))
  P2CONST(Com_SignalIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_TxInvSignals;      /* COM_SIGNALGW_TXINVSIGCNT */
#    endif
#    if ((COM_SIGNALGW_INVSIGGRP_UB == STD_ON) || (COM_SIGNALGW_INVSIGGRP_IPDU == STD_ON))
  P2CONST(Com_SignalGroupIdType, AUTOMATIC, COM_PBCFG) Com_ConfigTypeCom_SignalGw_TxInvSignalGroups;    /* COM_SIGNALGW_TXINVSIGGRPCNT  */
#    endif
#   endif
# endif                         /* (COM_SIGNALGW_DEFERREDROUTING == STD_ON) */

  /* - */
  uint16 Com_ConfigTypeFinalMagicNumber;
} Com_ConfigType;

# if (COM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
  Com_LMgt_FatalErrorType ERROR CODES
**********************************************************************************************************************/
/** This enum contains all error codes, which can be used with Com_LMgt_ConditionalFatalError and Com_LMgt_FatalError */
typedef enum
{
  Com_TxModeHdlr_Param_TriggerDeferredIpduSend = 3,           /**< The Parameter of Com_TxModeHdlr_TriggerDeferredIpduSend is too large. */
  Com_TxModeHdlr_Param_Confirmation = 4,                      /**< The Parameter of Com_TxModeHdlr_Confirmation is too large. */
  Com_TxModeHdlr_Param_StopCyclicTransmission = 5,            /**< The Parameter of Com_TxModeHdlr_StopCyclicTransmission is too large. */
  Com_TxModeHdlr_Param_StartCyclicTransmission = 6,           /**< The Parameter of Com_TxModeHdlr_StartCyclicTransmission is too large. */
  Com_TxModeHdlr_Param_StartDeferredCyclicTransmission = 7,   /**< The Parameter of Com_TxModeHdlr_StartDeferred is too large. */
  Com_TxModeHdlr_Param_Stop = 8,                              /**< The Parameter of Com_TxModeHdlr_Stop is too large. */
  Com_TxModeHdlr_Param_TriggerImmediateIpduSend = 9,          /**< The Parameter of Com_TxModeHdlr_TriggerImmediateIpduSend is too large. */
  Com_RxBuffer_SignalId_Param = 10,                           /**< The SignalId (handled as parameter to a RxBuffer function) is too large */
  Com_RxBuffer_InvalidPointer_Param = 11,                     /**< The data pointer handled by the application to a RxBuffer function is invalid */
  Com_RxBuffer_IpduId_Param = 12,                             /**< The IpduId (handled as parameter to a RxBuffer function) is invalid */
  Com_RxBuffer_InvalidByteOffset = 13,                        /**< The signal byte offset retrieved from a configuration table is too large */
  Com_RxBuffer_SignalGroupId_Param = 14,                      /**< The SignalGroupId (handled as parameter to a RxBuffer function) is too large */
  Com_TxBuffer_SignalId_Param = 15,                           /**< The SignalId (handled as parameter to a TxBuffer function) is too large */
  Com_TxBuffer_InvalidPointer_Param = 16,                     /**< The data pointer handled by the application to a TxBuffer function is invalid */
  Com_TxBuffer_IpduId_Param = 17,                             /**< The IpduId (handled as parameter to a TxBuffer function) is invalid */
  Com_TxBuffer_InvalidByteOffset = 18,                        /**< The signal byte offset retrieved from a configuration table is too large */
  Com_TxBuffer_SignalGroupId_Param = 19,                      /**< The SignalGroupId (handled as parameter to a TxBuffer function) is too large */
  Com_Signal_UnsupportedBusSignalType = 20,                   /**< Unsupported bus signal type. Configuration data might be corrupted */
  Com_Signal_VariableOutOfRange = 21,                         /**< The tested variable will not fit into the provided data type */
  Com_Signal_InconsistentConfigurationData = 22,              /**< The configuration data is not consistent. The tested config value must not occur in this section */
  Com_TxLLIf_Transmit_PduInfoNullPointer = 23,                /**< The PduInfo.SduDataPtr is a null pointer. */
  Com_TriggerTransmit_PduInfoNullPointer = 24,                /**< The PduInfo.SduDataPtr is a null pointer. */
  Com_RxIndication_PduInfoNullPointer = 25,                   /**< The PduInfo.SduDataPtr is a null pointer. */
  Com_RxIndication_PduInfoLength = 26,                        /**< The PduInfo.SduLength is too large. */
  Com_TriggerTransmit_PduInfoLength = 27,                     /**< The PduInfo.SduLength is too large. */
  Com_TxLLIf_Transmit_PduInfoLength = 28,                     /**< The PduInfo.SduLength is too large. */
  Com_ReceiveSignal_PduId = 29,                               /**< The PduId retrieved from Com_Signal subcomponent is too large. */
  Com_ReceiveShadowSignal_PduId = 30,                         /**< The PduId retrieved from Com_Signal subcomponent is too large. */
  Com_ReceiveSignalGroup_PduId = 31,                          /**< The PduId retrieved from Com_Signal subcomponent is too large. */
  Com_SendSignal_PduId = 32,                                  /**< The PduId retrieved from Com_Signal subcomponent is too large. */
  Com_SendSignalGroup_PduId = 33,                             /**< The PduId retrieved from Com_Signal subcomponent is too large. */
  Com_UpdateShadowSignal_PduId = 34,                          /**< The PduId retrieved from Com_Signal subcomponent is too large. */
  Com_TxLLIf_Transmit_IpduIdParam = 35,                       /**< The Parameter of Com_TxLLIf_Transmit is too large. */
  Com_TxSigIf_Init_SignalGroupIndex = 36,                     /**< COM_SIGNALGROUPINDEX is too large. */
  Com_UpdateShadowSignal_SigGroupId = 37,                     /**< Com_UpdateShadowSignal was called for a signal that doesn't belong to a signal group. */
  Com_RxNHdlr_IpduIdParamTooLarge = 38,                       /**< The IPDU parameter of a RxNHdlr service function is > number of configured Pdus. */
  Com_RxNHdlr_TimeoutFuncIdxTooLarge = 39,                      /**< Error function pointer index too large */
  Com_RxNHdlr_NotiFuncIdxTooLarge = 40,                       /**< Notification function pointer index too large */
  Com_TxBuffer_InvalidBitPosition = 41,                       /**< The indicated bit possition is not within the allowed range (0..7) */
  Com_RxBuffer_InvalidBitPosition = 42,                       /**< The indicated bit possition is not within the allowed range (0..7) */
  Com_RxUbHdlr_IpduId_Param = 43,                             /**< The IpduId (handled as parameter to a RxUbHdlr function) is invalid */
  Com_RxUbHdlr_InvalidFctPtr = 44,                            /**< A NULL pointer is referenced within a deferred notification function call. Flag must never be set for a Ub without a configured notification. */
  Com_RxUbHdlr_InvalidUbHdl = 45,                             /**< A invalid update bit handle was detected within the IPDU to Ub Hdl ROM table */
  Com_RxDlMon_Indication_Param = 46,                          /**< The IpduId (handled as parameter to a RxDlMon function) is invalid */
  Com_RxDlMon_Stop_Param = 47,                                /**< The IpduId (handled as parameter to a RxDlMon function) is invalid */
  Com_TxNHdlr_IpduIdParamTooLarge = 48,                       /**< The IPDU parameter of a TxNHdlr service function is > number of configured Pdus. */
  Com_TxNHdlr_NotiFuncIdxTooLarge = 49,                       /**< Notification function pointer index too large */
  Com_TxNHdlr_TimeoutFuncIdxTooLarge = 50,                      /**< Error function pointer index too large */
  Com_LMgt_NullPointerParameter = 51,                         /**< A pointer parameter is zero. This is not an allowed address. */
  Com_IpduGroupTransmit_IpduGroupStopped = 53,                /**< The Ipdu group of an Ipdu is not started. Perform Com_IpduGroupStart for the Ipdu group, before this method is used for th Ipdu Group. */
  Com_SignalGw_InvalidGwHandle = 54,                          /**< Gateway hdl. retrieved from Com_SignalGw_RxIpdu2GwHandle is invalid */
  Com_SignalGw_InvalidSignalHandle = 55,                      /**< Signal hdl. retrieved from a routing table is invalid */
  Com_SignalGw_InvalidUpdateBitPosition = 56,                 /**< Update bit position retrieved from a routing table is invalid */
  Com_SignalGw_InvalidSignalGrpHandle = 57,                   /**< Signal group hdl. retrieved from a routing table is invalid */
  Com_RxNHdlr_InvalidSigIdForIndFlagAccess = 58,              /**< RxSigId parameter used for indication flag access is invalid */
  Com_RxNHdlr_InvalidSigIdForToutFlagAccess = 59,             /**< RxSigId parameter used for timeout flag access is invalid */
  Com_RxNHdlr_NotiFlagIdxTooLarge = 60,                       /**< Too large indication flag index retrieved from configuration data */
  Com_RxNHdlr_TimeoutFlagIdxTooLarge = 61,                      /**< Too large timeout flag index retrieved from configuration data */
  Com_LMgt_PduIdTypeTooSmall = 62,                            /**< The PduIdType cannot hold the number of used I-Pdus */
  Com_TxModeHdlr_Param_TriggerIpduSendOnceDeferred = 63,      /**< The Parameter of Com_TxModeHdlr_TriggerIpduSendOnceDeferred is too large. */
  Com_Buffer_SignalId_Param = 64,                             /**< The SignalId (handled as parameter to a RxBuffer function) is too large */
  Com_Buffer_InvalidPointer_Param = 65,                       /**< The data pointer handled by the application to a RxBuffer function is invalid */
  Com_LMgt_SizeOfBoolean = 66,                                /**< Size of datatype 'boolean' must be '1' for a correct behavior of the functions Com_Signal_WriteSignal() and Com_Signal_ReadSignal() */
  Com_RxInv_NoInvalidValue = 67,                              /**< Function was called for a signal without a configured invalid value */
  Com_RxUbHdlr_TimeoutFlagIdxTooLarge = 68,                   /**< Too large update-bit timeout flag index retrieved from configuration data */
  Com_RxUbHdlr_NotificationFlagIdxTooLarge = 69,              /**< Too large update-bit notification flag index retrieved from configuration data */
  Com_LMgt_SubIpduGroupId = 70,                               /**< The Sub I-Pdu Group ID is too large. */
  Com_LMgt_IpduId = 71,                                       /**< The I-Pdu ID is too large. */
  Com_TxNHdlr_TimeoutFlagIdxTooLarge = 72,                    /**< Too large timeout flag index retrieved from configuration data */
  Com_TxNHdlr_TimeoutFlagByteIdxTooLarge = 73,                /**< Too large timeout flag byte index retrieved from configuration data */
  Com_TxNHdlr_NotificationFlagIdxTooLarge = 74,                    /**< Too large timeout flag index retrieved from configuration data */
  Com_TxNHdlr_NotificationFlagByteIdxTooLarge = 75,                 /**< Too large timeout flag byte index retrieved from configuration data */
  Com_TxEventDlMon_IpduIdParamTooLarge = 76,                 /**< Function called with too large IpduId */
  Com_TxModeHdlr_Param_StopTransmission = 77,                /**< Function called with too large IpduId */
  Com_SignalGw_Param_RouteImmediate = 78                     /**< Function called with not expected IpduId */
} Com_LMgt_FatalErrorType;
# endif

/* KB end Com_LMgt_GlobalDataTypesAndStructures */


/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES (Com)
**********************************************************************************************************************/
/* *INDENT-OFF* */
/* PRQA S 3684 GLOBALDATAPROTOTYPES_3684 */ /* MD_Com_3684 */
/* *INDENT-ON* */
/* KB begin Com_LMgt_GlobalDataPrototypes */
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
#  define COM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_CONFIG_VARIANT == 3)
/**********************************************************************************************************************
  com_ConfigStructPtr
**********************************************************************************************************************/
/** \brief  If post build is configured this pointer points to the actual config struct. It is initialized 
            during Com_Init(...).
**********************************************************************************************************************/
extern P2CONST(Com_ConfigType, COM_VAR_NOINIT, COM_PBCFG) com_ConfigStructPtr;
#  endif/* (COM_CONFIG_VARIANT == 3) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_INIT_UNSPECIFIED ========================================*/
# define COM_START_SEC_VAR_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_LMgt_Status
**********************************************************************************************************************/
/** \brief  If the Com is initialized, the value is COM_INIT, else COM_UNINIT.
**********************************************************************************************************************/
extern VAR(Com_StatusType, COM_VAR_INIT) com_LMgt_Status;

/* KB begin Com_StopMemSection */
# define COM_STOP_SEC_VAR_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_INIT_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

/**********************************************************************************************************************
  com_Buffer
**********************************************************************************************************************/
# if(COM_CONFIG_VARIANT == 2)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_8BIT ========================================*/
#   define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

extern VAR(uint8, COM_VAR_NOINIT) com_Buffer[];

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_8BIT ========================================*/
/* KB end Com_StopMemSection */
# else
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
#  define COM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

                   /* PRQA S 0759 1 */ /* MD_MSR_18.4 */
extern VAR(Com_BufferType, COM_VAR_NOINIT) com_UnionBuffer;

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */
# endif

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
# define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_16BitValue
**********************************************************************************************************************/
extern CONST(uint16, COM_PBCFG) Com_16BitValue[COM_16BITVALUECNT];

# if (((COM_TXMODEHDLR_TMS == STD_ON)&& (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)) || (COM_TXINV == STD_ON) || (COM_RXINV == STD_ON))
/**********************************************************************************************************************
  Com_8BitValue
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_8BitValue[COM_8BITVALUECNT];

/**********************************************************************************************************************
  Com_32BitValue
**********************************************************************************************************************/
extern CONST(uint32, COM_PBCFG) Com_32BitValue[COM_32BITVALUECNT];
# endif

/**********************************************************************************************************************
  Com_LMgt_ConfigurationString
**********************************************************************************************************************/
extern CONST(Com_CharType, COM_PBCFG) Com_LMgt_ConfigurationString[];

/* KB begin Com_StopMemSection */
# define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

#  if (COM_LMGT_MULTIPLEIPDUGROUPREF == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_BOOLEAN ========================================*/
#   define COM_START_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_LMgt_IPduGroupState
**********************************************************************************************************************/
extern VAR(boolean, COM_VAR_NOINIT) com_LMgt_IPduGroupState[];  /* COM_SUBIPDUGROUPCNT */

#   if ((COM_RXUBHDLR_TIMEOUT == STD_ON) || (COM_RXDLMON == STD_ON))
/**********************************************************************************************************************
  com_LMgt_DmGroupState
**********************************************************************************************************************/
extern VAR(boolean, COM_VAR_NOINIT) com_LMgt_DmGroupState[];    /* COM_SUBIPDUGROUPCNT */
#   endif/* ((COM_RXUBHDLR_TIMEOUT == STD_ON) || (COM_RXDLMON == STD_ON)) */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_BOOLEAN ========================================*/
/* KB end Com_StopMemSection */
#  endif/* (COM_LMGT_MULTIPLEIPDUGROUPREF == STD_ON) */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_8BIT ========================================*/
# define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

# if ((COM_RXUBHDLR_TIMEOUT == STD_ON) || (COM_RXDLMON == STD_ON))
/**********************************************************************************************************************
  com_LMgt_RxDmState
**********************************************************************************************************************/
extern VAR(uint8, COM_VAR_NOINIT) com_LMgt_RxDmState[]; /* COM_MAXRXIPDUCNT */

# endif/* ((COM_RXUBHDLR_TIMEOUT == STD_ON) || (COM_RXDLMON == STD_ON)) */


/**********************************************************************************************************************
  com_LMgt_RxPduGroupState
**********************************************************************************************************************/
extern VAR(uint8, COM_VAR_NOINIT) com_LMgt_RxPduGroupState[];   /* COM_MAXRXIPDUCNT */

/**********************************************************************************************************************
  com_LMgt_TxPduGroupState
**********************************************************************************************************************/
extern VAR(uint8, COM_VAR_NOINIT) com_LMgt_TxPduGroupState[];   /* COM_MAXTXIPDUCNT */

/* KB begin Com_StopMemSection */
# define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_8BIT ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG_ROOT ========================================*/
# define COM_START_SEC_PBCFG_ROOT
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_ConfigStruct
**********************************************************************************************************************/
extern CONST(Com_ConfigType, COM_PBCFG) Com_ConfigStruct;

/* KB begin Com_StopMemSection */
# define COM_STOP_SEC_PBCFG_ROOT
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG_ROOT ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
# define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if ((COM_LMGT_RX == STD_ON) || (COM_LMGT_TX == STD_ON))
#   if ((COM_LMGT_MULTIPLEIPDUGROUPREF == STD_ON) && (COM_LMGT_IPDUGROUPHIERARCHY == STD_ON))
/**********************************************************************************************************************
  Com_LMgt_IPduGroup2SubGroups
**********************************************************************************************************************/
extern CONST(Com_LMgt_IPduGroup2SubGroupsType, COM_PBCFG) Com_LMgt_IPduGroup2SubGroups[];       /* COM_IPDUGROUPCNT + 1 */

/**********************************************************************************************************************
  Com_LMgt_IPduGroup2SubGroupsIndirection
**********************************************************************************************************************/
extern CONST(Com_PduGroupIdType, COM_PBCFG) Com_LMgt_IPduGroup2SubGroupsIndirection[];  /* COM_LMGT_IPDUGROUP2SUBGROUPSTARGETCOUNT */
#   endif
        /* ((COM_LMGT_MULTIPLEIPDUGROUPREF == STD_ON) && (COM_LMGT_IPDUGROUPHIERARCHY == STD_ON)) */

/**********************************************************************************************************************
  Com_LMgt_IPduGroup2IPdus
**********************************************************************************************************************/
extern CONST(Com_LMgt_IPduGroup2IPdusType, COM_PBCFG) Com_LMgt_IPduGroup2IPdus[];       /* COM_IPDUGROUPCNT + 1 */

/**********************************************************************************************************************
  Com_LMgt_IPduGroup2IPdusIndirection
**********************************************************************************************************************/
extern CONST(PduIdType, COM_PBCFG) Com_LMgt_IPduGroup2IPdusIndirection[];       /* COM_LMGT_IPDUGROUP2IPDUSTARGETCOUNT */

#  endif/* ((COM_LMGT_RX == STD_ON) || (COM_LMGT_TX == STD_ON)) */


/* KB begin Com_StopMemSection */
# define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_32BIT ========================================*/
#  define COM_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_CRC_CHECK == STD_ON )
/**********************************************************************************************************************
  Com_LMgt_LinktimeCRC
**********************************************************************************************************************/
extern CONST(uint32, COM_CONST) Com_LMgt_LinktimeCRC;
#  endif

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_32BIT ========================================*/
/* KB end Com_StopMemSection */
/* KB end Com_LMgt_GlobalDataPrototypes */
/* KB begin Com_Signal_GlobalDataPrototypes */
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
# define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

# if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)
/**********************************************************************************************************************
  Com_Signal_SignalAttributes
**********************************************************************************************************************/
extern CONST(Com_Signal_SignalAttrType, COM_PBCFG) Com_Signal_SignalAttributes[];       /* COM_SIGNALCNT */
# endif/* (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF) */

# if ((COM_TXMODEHDLR_TMS == STD_ON) && (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF))
/**********************************************************************************************************************
  Com_Signal_SignalFilter
**********************************************************************************************************************/
extern CONST(Com_Signal_SignalFilterType, COM_PBCFG) Com_Signal_SignalFilter[]; /* COM_FILTERCNT */
# endif/* ((COM_TXMODEHDLR_TMS == STD_ON) && (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)) */

#  if (COM_SIGNALCONVERSION == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SignalConversion
**********************************************************************************************************************/
extern CONST(Com_Signal_SignalConversionType, COM_PBCFG) Com_Signal_SignalConversion[]; /* COM_SIGCONVERSIONCNT */
#  endif

# if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SignalGroup2IpduIndirection
**********************************************************************************************************************/
extern CONST(PduIdType, COM_PBCFG) Com_Signal_SignalGroup2IpduIndirection[];    /* COM_SIGNALGROUPCNT */


/**********************************************************************************************************************
  Com_Signal_SignalGroupMaskIdx
**********************************************************************************************************************/
extern CONST(uint16, COM_PBCFG) Com_Signal_SignalGroupMaskIdx[];        /* COM_SIGNALGROUPCNT */


/**********************************************************************************************************************
  Com_Signal_SignalGroupMask
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_Signal_SignalGroupMask[];    /* Number of mask bytes for signal groups */


/**********************************************************************************************************************
  Com_Signal_SigGrpBufferInfo
**********************************************************************************************************************/
extern CONST(Com_Signal_SigGrpBufferInfoType, COM_PBCFG) Com_Signal_SigGrpBufferInfo[]; /* COM_SIGNALGROUPCNT */
# endif/* (COM_SIGNALGROUPIF == STD_ON) */

#  if (COM_CONFIG_VARIANT == 3) && (COM_EXTSIGHDLSPACE == STD_ON)
/**********************************************************************************************************************
  Com_Signal_Ext2IntSignalId
**********************************************************************************************************************/
extern CONST(Com_SignalIdType, COM_PBCFG) Com_Signal_Ext2IntSignalId[];

#   if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_Signal_Ext2IntSignalGroupId
**********************************************************************************************************************/
extern CONST(Com_SignalGroupIdType, COM_PBCFG) Com_Signal_Ext2IntSignalGroupId[];
#   endif
#  endif/* (COM_CONFIG_VARIANT == 3) && (COM_EXTSIGHDLSPACE == STD_ON) */

/* KB begin Com_StopMemSection */
# define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
/* KB end Com_Signal_GlobalDataPrototypes */
/* KB begin Com_Buffer_GlobalDataPrototypes */
/* KB end Com_Buffer_GlobalDataPrototypes */
/* KB begin Com_RxBuffer_GlobalDataPrototypes */
# if (COM_RXBUFFER == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxBuffer_IpduInitValue
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_RxBuffer_IpduInitValue[];    /* Number of init bytes */
/**********************************************************************************************************************
  Com_RxBuffer_IpduInfo
**********************************************************************************************************************/
extern CONST(Com_RxBuffer_IpduInfoType, COM_PBCFG) Com_RxBuffer_IpduInfo[];     /* Number of Rx I-PDUs */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
# endif/* COM_RXBUFFER == STD_ON */
/* KB end Com_RxBuffer_GlobalDataPrototypes */
/* KB begin Com_RxDlMon_GlobalDataPrototypes */
# if (COM_RXDLMON == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_16BIT ========================================*/
#  define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_RxDlMon_TimeoutCnt
**********************************************************************************************************************/
extern VAR(uint16, COM_VAR_NOINIT) com_RxDlMon_TimeoutCnt[];    /* COM_MAXRXIPDUCNT */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_16BIT ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_RXDLMON_TIMEOUTDEFAULTVALUE == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_IpduTimeoutMask
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_RxDlMon_IpduTimeoutMask[];   /* Number of timeout mask bytes */
#  endif

#  if (COM_RXDLMON_FIRSTTIMEOUT == STD_ON)
/**********************************************************************************************************************
  Com_RxDlMon_TimeoutTime
**********************************************************************************************************************/
extern CONST(uint16, COM_PBCFG) Com_RxDlMon_FirstTimeoutTime[]; /* COM_MAXRXIPDUCNT */
#  endif

/**********************************************************************************************************************
  Com_RxDlMon_TimeoutTime
**********************************************************************************************************************/
extern CONST(uint16, COM_PBCFG) Com_RxDlMon_TimeoutTime[];      /* COM_MAXRXIPDUCNT */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
# endif
/* KB end Com_RxDlMon_GlobalDataPrototypes */
/* KB begin Com_RxLLIf_GlobalDataPrototypes */
# if (COM_RXLLIF == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
#   define COM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#   if (COM_TPINTERFACE == STD_ON)
/**********************************************************************************************************************
  com_RxLLIf_TpPduInfo
**********************************************************************************************************************/
extern VAR(PduInfoType, COM_VAR_NOINIT) com_RxLLIf_TpPduInfo[]; /* COM_MAXTXIPDUCNT */
#   endif

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

#  if (COM_RXPDUCALLOUT == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#   define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxLLIf_PduCallout
**********************************************************************************************************************/
extern CONST(Com_RxLLIf_PduCalloutFuncPtrType, COM_CONST) Com_RxLLIf_PduCallout[];      /* COM_MAXRXCALLOUTCNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#   define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxLLIf_PduCalloutIndirection
**********************************************************************************************************************/
extern CONST(Com_RxLLIf_PduCalloutIdType, COM_PBCFG) Com_RxLLIf_PduCalloutIndirection[];        /* COM_MAXRXIPDUCNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
#  endif
# endif/* COM_RXLLIF == STD_ON */
/* KB end Com_RxLLIf_GlobalDataPrototypes */
/* KB begin Com_RxNHdlr_GlobalDataPrototypes */
# if (COM_RXNHDLR == STD_ON)
#   if ((COM_RXINV == STD_ON) || (COM_RXNHDLR_RXFILTER == STD_ON))
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_8BIT ========================================*/
#    define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#    if ((COM_RXINV_INHIBITNOTIFUNC == STD_ON) || (COM_RXNHDLR_INHIBITNOTIFUNC == STD_ON))
/**********************************************************************************************************************
  com_RxNHdlr_InhibitNotification
**********************************************************************************************************************/
extern VAR(uint8, COM_VAR_NOINIT) com_RxNHdlr_InhibitNotification[];    /* COM_RXSIGALLNOTIFICATIONCNT */
#    endif/* ((COM_RXINV_INHIBITNOTIFUNC == STD_ON) || (COM_RXNHDLR_INHIBITNOTIFUNC == STD_ON)) */

#    if ((COM_RXINV_INHIBITINDFLAG == STD_ON) || (COM_RXNHDLR_INHIBITINDFLAG == STD_ON))
/**********************************************************************************************************************
  com_RxNHdlr_InhibitNotiFlag
**********************************************************************************************************************/
extern VAR(uint8, COM_VAR_NOINIT) com_RxNHdlr_InhibitNotiFlag[];        /* COM_RXSIGALLNOTIFLAGCNT */
#    endif/* ((COM_RXINV_INHIBITINDFLAG == STD_ON) || (COM_RXNHDLR_INHIBITINDFLAG == STD_ON)) */

/* KB begin Com_StopMemSection */
#    define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_8BIT ========================================*/
/* KB end Com_StopMemSection */
#   endif/* ((COM_RXINV == STD_ON) || (COM_RXNHDLR_RXFILTER == STD_ON)) */

#  if (COM_RXNHDLR_DEFERRED_SIGNALPROCESSING == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
#   define COM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_RxNHdlr_HandleIPduDeferred
**********************************************************************************************************************/
#   if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
extern VAR(PduLengthType, COM_VAR_NOINIT) com_RxNHdlr_HandleIPduDeferred[];     /* COM_MAXRXIPDUCNT */
#   else
extern VAR(boolean, COM_VAR_NOINIT) com_RxNHdlr_HandleIPduDeferred[];   /* COM_MAXRXIPDUCNT */
#   endif
        /* (COM_DYNAMIC_DLC_SUPPORT == STD_ON) */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

#  endif/* (COM_RXNHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) */

#  if ((COM_RXINV_INHIBITNOTIFUNC == STD_ON) || (COM_RXNHDLR_INHIBITNOTIFUNC == STD_ON) || ((COM_DEV_ERROR_DETECT == STD_ON) && (COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON)))
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#   define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_NotificationCnt
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotificationIdxType, COM_CONST) Com_RxNHdlr_NotificationCnt;

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

#  endif

#  if (COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#   define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_Ipdu2NotificationFunctions
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotificationIdxType, COM_PBCFG) Com_RxNHdlr_Ipdu2NotificationFunctions[];      /* COM_MAXRXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_RxNHdlr_NotiFuncIndirection
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotiFuncIndirectionType, COM_PBCFG) Com_RxNHdlr_NotiFuncIndirection[]; /* COM_RXSIGNOTIFICATIONCNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

#  endif/* (COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON) */

#  if ((COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFUNCTION == STD_ON))

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#   define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_NotificationFuncPtr
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotiFuncPtrType, COM_CONST) Com_RxNHdlr_NotificationFuncPtr[]; /* COM_RXSIGALLNOTIFICATIONCNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

#  endif/* ((COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFUNCTION == STD_ON)) */

#  if (((COM_RXNHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) && (COM_RXNHDLR_IMMEDIATE_SIGNALPROCESSING == STD_ON)) || ((COM_RXUBHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) && (COM_RXUBHDLR_IMMEDIATE_SIGNALPROCESSING == STD_ON)))
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#   define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_DeferredSignalProcessing
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_RxNHdlr_DeferredSignalProcessing[];  /* COM_RXIPDUCNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

#  endif/* (((COM_RXNHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) && (COM_RXNHDLR_IMMEDIATE_SIGNALPROCESSING == STD_ON)) || ((COM_RXUBHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) && (COM_RXUBHDLR_IMMEDIATE_SIGNALPROCESSING == STD_ON))) */

#  if ((COM_RXINV_INHIBITINDFLAG == STD_ON) || (COM_RXNHDLR_INHIBITINDFLAG == STD_ON) || ((COM_DEV_ERROR_DETECT == STD_ON) && ((COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON))))
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#   define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_NotiFlagCnt
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotiFlagIdType, COM_CONST) Com_RxNHdlr_NotiFlagCnt;

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */
#  endif

#  if (COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#   define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_NotiFlagIndirection
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotiFlagIndirectionType, COM_PBCFG) Com_RxNHdlr_NotiFlagIndirection[]; /* COM_RXSIGNOTIFLAGCNT */

/**********************************************************************************************************************
  Com_RxNHdlr_Ipdu2NotificationFlags
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotiFlagIdType, COM_PBCFG) Com_RxNHdlr_Ipdu2NotificationFlags[];       /* COM_MAXRXIPDUCNT + 1 */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

#  endif/* (COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON) */

#  if ((COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON))
#    if (COM_CONFIG_VARIANT != 1)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#     define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#     include "MemMap.h"    /* PRQA S 5087 */   /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_SignalNotiFlagHdl
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotiFlagIdType, COM_CONST) Com_RxNHdlr_SignalNotiFlagHdl[];    /* COM_RXSIGNALCNT */

#     if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_RxNHdlr_SignalGroupNotiFlagHdl
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotiFlagIdType, COM_CONST) Com_RxNHdlr_SignalGroupNotiFlagHdl[];       /* COM_RXSIGNALGROUPCNT */
#     endif/* (COM_SIGNALGROUPIF == STD_ON) */

/* KB begin Com_StopMemSection */
#     define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#     include "MemMap.h"    /* PRQA S 5087 */   /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */
#    endif/* (COM_CONFIG_VARIANT != 1) */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_8BIT ========================================*/
#   define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_RxNHdlr_NotificationFlags
**********************************************************************************************************************/
extern VAR(uint8, COM_VAR_NOINIT) com_RxNHdlr_NotificationFlags[];      /* COM_NOTIFLAGBYTECNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_8BIT ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#   define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_NotificationFlagInfo
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_FlagInfoType, COM_CONST) Com_RxNHdlr_NotificationFlagInfo[];   /* COM_RXSIGALLNOTIFLAGCNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

#  endif/* ((COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON)) */

#  if (COM_RXNHDLR_TIMEOUTFLAG == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#   define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_TimeoutFlagIndirection
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_TimeoutFlagIdType, COM_PBCFG) Com_RxNHdlr_TimeoutFlagIndirection[];    /* COM_RXSIGTIMEOUTFLAGCNT */

/**********************************************************************************************************************
  Com_RxNHdlr_Ipdu2TimeoutFlags
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_TimeoutFlagIdType, COM_PBCFG) Com_RxNHdlr_Ipdu2TimeoutFlags[]; /* COM_MAXRXIPDUCNT + 1 */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

#  endif /* (COM_RXNHDLR_TIMEOUTFLAG == STD_ON) */

#  if ((COM_RXNHDLR_TIMEOUTFLAG == STD_ON) || (COM_RXUBHDLR_TIMEOUTFLAG == STD_ON))
#   if (COM_DEV_ERROR_DETECT == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#    define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_TimeoutFlagCnt
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_TimeoutFlagIdType, COM_CONST) Com_RxNHdlr_TimeoutFlagCnt;

/* KB begin Com_StopMemSection */
#    define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */
#   endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_8BIT ========================================*/
#   define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_RxNHdlr_TimeoutFlags
**********************************************************************************************************************/
extern VAR(uint8, COM_VAR_NOINIT) com_RxNHdlr_TimeoutFlags[];   /* COM_TIMEOUTFLAGBYTECNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_8BIT ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#   define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_TimeoutFlagInfo
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_FlagInfoType, COM_CONST) Com_RxNHdlr_TimeoutFlagInfo[];        /* COM_RXSIGALLTIMEOUTFLAGCNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

#    if (COM_CONFIG_VARIANT != 1)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#     define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#     include "MemMap.h"    /* PRQA S 5087 */   /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_SignalTimeoutFlagHdl
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_TimeoutFlagIdType, COM_CONST) Com_RxNHdlr_SignalTimeoutFlagHdl[];      /* COM_RXSIGNALCNT */

#     if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_RxNHdlr_SignalGroupTimeoutFlagHdl
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_TimeoutFlagIdType, COM_CONST) Com_RxNHdlr_SignalGroupTimeoutFlagHdl[]; /* COM_RXSIGNALGROUPCNT */
#     endif/* (COM_SIGNALGROUPIF == STD_ON) */

/* KB begin Com_StopMemSection */
#     define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#     include "MemMap.h"    /* PRQA S 5087 */   /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */
#    endif/* (COM_CONFIG_VARIANT != 1) */

#  endif/* ((COM_RXNHDLR_TIMEOUTFLAG == STD_ON) || (COM_RXUBHDLR_TIMEOUTFLAG == STD_ON)) */

#  if (COM_RXNHDLR_TIMEOUTFUNCTION == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#   define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#   if (COM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
  Com_RxNHdlr_TimeoutNotiCnt
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_TimeoutIdxType, COM_CONST) Com_RxNHdlr_TimeoutNotiCnt;
#   endif

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#   define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_Ipdu2TimeoutFunctions
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_TimeoutIdxType, COM_PBCFG) Com_RxNHdlr_Ipdu2TimeoutFunctions[];        /* COM_MAXRXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_RxNHdlr_TimeoutFuncIndirection
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_TimeoutIdxType, COM_PBCFG) Com_RxNHdlr_TimeoutFuncIndirection[];       /* COM_RXSIGTIMEOUTNOTICNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
#  endif/* (COM_RXNHDLR_TIMEOUTFUNCTION == STD_ON) */

#  if ((COM_RXNHDLR_TIMEOUTFUNCTION == STD_ON) || (COM_RXUBHDLR_TIMEOUTFUNCTION == STD_ON))
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#   define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxNHdlr_TimeoutNotiFuncPtr
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_TimeoutFuncPtrType, COM_CONST) Com_RxNHdlr_TimeoutNotiFuncPtr[];       /* COM_RXSIGALLTIMEOUTNOTICNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

#  endif/* ((COM_RXNHDLR_TIMEOUTFUNCTION == STD_ON) || (COM_RXUBHDLR_TIMEOUTFUNCTION == STD_ON)) */

#   if ((COM_RXNHDLR_RXFILTER == STD_ON) && (COM_RXSIGNAL_ACCESS_MACRO_API == STD_OFF))
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#    define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#    if ((COM_RXNHDLR_RXFILTER_SIGNOTIFUNC == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGINDFLAG == STD_ON))
/**********************************************************************************************************************
  Com_RxNHdlr_IPdu2FilterSigs
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_FilterSigIdxType, COM_PBCFG) Com_RxNHdlr_IPdu2FilterSigs[];    /* COM_RXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_RxNHdlr_FilterSignals
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_FilterSigInfoType, COM_PBCFG) Com_RxNHdlr_FilterSigInfo[];     /* COM_RXNHDLR_FILTERSIGCNT */
#    endif/* ((COM_RXNHDLR_RXFILTER_SIGNOTIFUNC == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGINDFLAG == STD_ON)) */

#    if ((COM_RXNHDLR_RXFILTER_SIGGRPNOTIFUNC == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGGRPINDFLAG == STD_ON))
/**********************************************************************************************************************
  Com_RxNHdlr_IPdu2FilterSigGrps
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_FilterSigGrpIdxType, COM_PBCFG) Com_RxNHdlr_IPdu2FilterSigGrps[];      /* COM_RXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_RxNHdlr_FilterSignals
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_FilterSigGrpInfoType, COM_PBCFG) Com_RxNHdlr_FilterSigGrpInfo[];       /* COM_RXNHDLR_FILTERSIGGRPCNT + 1 */

#     if (COM_RXNHDLR_RXFILTER_GRPSIG == STD_ON)
/**********************************************************************************************************************
  Com_RxNHdlr_FilterGrpSigIndirection
**********************************************************************************************************************/
extern CONST(Com_SignalIdType, COM_PBCFG) Com_RxNHdlr_FilterGrpSigIndirection[];        /* COM_RXNHDLR_FILTERGRPSIGCNT */
#     endif/* (COM_RXNHDLR_RXFILTER_GRPSIG == STD_ON) */
#    endif/* ((COM_RXNHDLR_RXFILTER_SIGGRPNOTIFUNC == STD_ON) || (COM_RXNHDLR_RXFILTER_SIGGRPINDFLAG == STD_ON)) */

/* KB begin Com_StopMemSection */
#    define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
#   endif/* ((COM_RXNHDLR_RXFILTER == STD_ON) && (COM_RXSIGNAL_ACCESS_MACRO_API == STD_OFF)) */
# endif/* COM_RXNHDLR == STD_ON */
/* KB end Com_RxNHdlr_GlobalDataPrototypes */
/* KB begin Com_RxSigIf_GlobalDataPrototypes */
/* KB end Com_RxSigIf_GlobalDataPrototypes */
/* KB begin Com_RxUbHdlr_GlobalDataPrototypes */
#  if (COM_RXUBHDLR == STD_ON)

#   if (COM_RXUBHDLR_DEFERRED_SIGNALPROCESSING == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_BOOLEAN ========================================*/
#    define COM_START_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_RxUbHdlr_HandleUbDeferred
**********************************************************************************************************************/
extern VAR(boolean, COM_VAR_NOINIT) com_RxUbHdlr_HandleUbDeferred[];    /* COM_RXUBCNT */

/* KB begin Com_StopMemSection */
#    define COM_STOP_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_BOOLEAN ========================================*/
/* KB end Com_StopMemSection */
#   endif
        /* (COM_RXUBHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) */

#   if (COM_RXUBHDLR_TIMEOUT == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_16BIT ========================================*/
#    define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_RxUbHdlr_TimeoutCnt
**********************************************************************************************************************/
extern VAR(uint16, COM_VAR_NOINIT) com_RxUbHdlr_TimeoutCnt[];   /* COM_RXUBCNT */

/* KB begin Com_StopMemSection */
#    define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_16BIT ========================================*/
/* KB end Com_StopMemSection */
#   endif
        /* (COM_RXUBHDLR_TIMEOUT == STD_ON) */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#   define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_RxUbHdlr_UpdateBitCnt
**********************************************************************************************************************/
extern CONST(Com_RxUbHdlr_UbIdType, COM_PBCFG) Com_RxUbHdlr_UpdateBitCnt;

/**********************************************************************************************************************
  Com_RxUbHdlr_Ipdu2UpdateBits
**********************************************************************************************************************/
extern CONST(Com_RxUbHdlr_UbIdType, COM_PBCFG) Com_RxUbHdlr_Ipdu2UpdateBits[];  /* COM_MAXRXIPDUCNT + 1 */

#   if (COM_RXUBHDLR_NOTIFICATIONFUNCTION == STD_ON)
/**********************************************************************************************************************
  Com_RxUbHdlr_NotiFuncIndirection
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotificationIdxType, COM_PBCFG) Com_RxUbHdlr_NotiFuncIndirection[];    /* COM_RXUBCNT */
#   endif
        /* (COM_RXUBHDLR_NOTIFICATIONFUNCTION == STD_ON) */

#   if (COM_RXUBHDLR_TIMEOUTFUNCTION == STD_ON)
/**********************************************************************************************************************
  Com_RxUbHdlr_TimeoutFuncIndirection
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_TimeoutIdxType, COM_PBCFG) Com_RxUbHdlr_TimeoutFuncIndirection[];      /* COM_RXUBCNT */
#   endif
        /* (COM_RXUBHDLR_TIMEOUTFUNCTION == STD_ON) */

/**********************************************************************************************************************
  Com_RxUbHdlr_UbBitPosition
**********************************************************************************************************************/
extern CONST(Com_RxUbHdlr_UbBitPositionType, COM_PBCFG) Com_RxUbHdlr_UbBitPosition[];   /* COM_RXUBCNT */

#   if (COM_RXUBHDLR_TIMEOUTDEFAULTVALUE == STD_ON)
/**********************************************************************************************************************
  Com_RxUbHdlr_TimeoutMask
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_RxUbHdlr_TimeoutMask[];      /* Number of Ub mask bytes (masking the I-PDU) */

/**********************************************************************************************************************
  Com_RxUbHdlr_TimeoutMaskIdx
**********************************************************************************************************************/
extern CONST(uint16, COM_PBCFG) Com_RxUbHdlr_TimeoutMaskIdx[];  /* Number of Ub bits */
#   endif
        /* (COM_RXUBHDLR_TIMEOUTDEFAULTVALUE == STD_ON) */

#   if (COM_RXUBHDLR_FIRSTTIMEOUT == STD_ON)
/**********************************************************************************************************************
  Com_RxUbHdlr_FirstTimeoutTime
**********************************************************************************************************************/
extern CONST(uint16, COM_PBCFG) Com_RxUbHdlr_FirstTimeoutTime[];        /* COM_RXUBCNT */
#   endif
        /* (COM_RXUBHDLR_FIRSTTIMEOUT == STD_ON) */

#   if (COM_RXUBHDLR_TIMEOUT == STD_ON)
/**********************************************************************************************************************
  Com_RxUbHdlr_TimeoutTime
**********************************************************************************************************************/
extern CONST(uint16, COM_PBCFG) Com_RxUbHdlr_TimeoutTime[];     /* COM_RXUBCNT */
#   endif
        /* (COM_RXUBHDLR_TIMEOUT == STD_ON) */

#   if (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON)
/**********************************************************************************************************************
  Com_RxUbHdlr_NotiFlagHdl
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotiFlagIdType, COM_PBCFG) Com_RxUbHdlr_NotiFlagHdl[]; /* COM_RXSIGALLNOTIFLAGCNT */
#   endif
        /* (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON) */

#   if (COM_RXUBHDLR_TIMEOUTFLAG == STD_ON)
/**********************************************************************************************************************
  Com_RxUbHdlr_TimeoutFlagHdl
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_TimeoutFlagIdType, COM_PBCFG) Com_RxUbHdlr_TimeoutFlagHdl[];   /* COM_RXSIGALLTIMEOUTFLAGCNT */
#   endif
        /* (COM_RXUBHDLR_TIMEOUTFLAG == STD_ON) */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
#  endif
       /* (COM_RXUBHDLR == STD_ON) */
/* KB end Com_RxUbHdlr_GlobalDataPrototypes */
/* KB begin Com_RxInv_GlobalDataPrototypes */
#  if (COM_RXINV == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#   define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#   if (COM_RXINV_NOTIINVFUNC == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_IPdu2NotiInvObjNoUb
**********************************************************************************************************************/
#    if ( (COM_RXINV_NOTIINVFUNC_NOUB_TO == STD_ON) || (COM_RXINV_NOTIINVFUNC_NOUB == STD_ON) )
extern CONST(Com_RxInv_NotiInvObjNoUbIdxType, COM_PBCFG) Com_RxInv_IPdu2NotiInvObjNoUb[];       /* COM_RXIPDUCNT + 1 */
#    endif

/**********************************************************************************************************************
  Com_RxInv_NotiInvFuncIndirNoUb
**********************************************************************************************************************/
#    if ( (COM_RXINV_NOTIINVFUNC_NOUB_TO == STD_ON) || (COM_RXINV_NOTIINVFUNC_NOUB == STD_ON) )
extern CONST(Com_RxInv_NotiInvFuncIndirType, COM_PBCFG) Com_RxInv_NotiInvFuncIndirNoUb[];       /* COM_RXINVNOTIINVOBJNOUBCNT */
#    endif

/**********************************************************************************************************************
  Com_RxInv_NotiInvFuncIndirUb
**********************************************************************************************************************/
#    if ( (COM_RXINV_NOTIINVFUNC_UB == STD_ON) || (COM_RXINV_NOTIINVFUNC_UB_TO == STD_ON) )
extern CONST(Com_RxInv_NotiInvFuncIndirType, COM_PBCFG) Com_RxInv_NotiInvFuncIndirUb[]; /* COM_RXUBCNT */
#    endif

#   endif
        /* (COM_RXINV_NOTIINVFUNC == STD_ON) */

#   if (COM_SIGNAL_ACCESS_MACRO_API != STD_ON)
#    if (COM_SIGNALIF == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_IPdu2InvalidSignals
**********************************************************************************************************************/
extern CONST(Com_RxInv_InvSigIdxType, COM_PBCFG) Com_RxInv_IPdu2InvalidSignals[];       /* COM_RXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_RxInv_InvalidSignalHandles
**********************************************************************************************************************/
extern CONST(Com_ValueIdxType, COM_PBCFG) Com_RxInv_InitValueIdx[];     /* COM_RXINVSIGNALCNT */

/**********************************************************************************************************************
  Com_RxInv_InvalidSignalHandles
**********************************************************************************************************************/
extern CONST(Com_SignalIdType, COM_PBCFG) Com_RxInv_InvalidSignalHandles[];     /* COM_RXINVSIGNALCNT */
#    endif

#    if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_IPdu2InvalidSignalGroups
**********************************************************************************************************************/
extern CONST(Com_RxInv_InvSigGroupIdxType, COM_PBCFG) Com_RxInv_IPdu2InvalidSignalGroups[];     /* COM_RXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_RxInv_InvalidGroupSignalHandles
**********************************************************************************************************************/
extern CONST(Com_SignalIdType, COM_PBCFG) Com_RxInv_InvalidGroupSignalHandles[];        /* COM_RXINVGROUPSIGNALCNT */
#    endif

#    if ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_InvalidObjectIndirection
**********************************************************************************************************************/
extern CONST(Com_RxInv_InvalidObjectIndType, COM_PBCFG) Com_RxInv_InvalidObjectIndirection[];   /* COM_RXINVSIGNALCNT + COM_RXINVSIGNALGROUPCNT */
#    endif
#   endif
        /* (COM_SIGNAL_ACCESS_MACRO_API != STD_ON) */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#   define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#   if ((((COM_SIGNAL_ACCESS_MACRO_API != STD_ON) && ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON))) || (COM_RXINV_NOTIINVFUNC == STD_ON)) && (COM_RXNHDLR == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_InvalidNotiFuncPtr
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotiFuncPtrType, COM_CONST) Com_RxInv_InvalidNotiFuncPtr[];    /* COM_RXINVSIGNALCNT + COM_RXINVSIGNALGROUPCNT + 1 */
#   endif/* ((((COM_SIGNAL_ACCESS_MACRO_API != STD_ON) && ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON))) || (COM_RXINV_NOTIINVFUNC == STD_ON)) && (COM_RXNHDLR == STD_ON)) */

#   if (COM_SIGNAL_ACCESS_MACRO_API != STD_ON)
#    if ((COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFUNCTION == STD_ON))
#     if (COM_SIGNALIF == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_SignalNotificationId
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotificationIdxType, COM_CONST) Com_RxInv_SignalNotificationId[];      /* COM_RXINVSIGNALCNT */
#     endif
          /* (COM_SIGNALIF == STD_ON) */

#     if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_SignalGroupNotificationId
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotificationIdxType, COM_CONST) Com_RxInv_SignalGroupNotificationId[]; /* COM_RXINVSIGNALGROUPCNT */
#     endif
          /* (COM_SIGNALGROUPIF == STD_ON) */
#    endif
         /* ((COM_RXNHDLR_NOTIFICATIONFUNCTION == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFUNCTION == STD_ON)) */

#    if ((COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON))
#     if (COM_SIGNALIF == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_SigNotificationFlagId
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotiFlagIdType, COM_CONST) Com_RxInv_SigNotificationFlagId[];  /* COM_RXINVSIGNALCNT */
#     endif
          /* (COM_SIGNALIF == STD_ON) */

#     if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_SigGrpNotificationFlagId
**********************************************************************************************************************/
extern CONST(Com_RxNHdlr_NotiFlagIdType, COM_CONST) Com_RxInv_SigGrpNotificationFlagId[];       /* COM_RXINVSIGNALGROUPCNT */
#     endif
          /* (COM_SIGNALGROUPIF == STD_ON) */
#    endif
         /* ((COM_RXNHDLR_NOTIFICATIONFLAG == STD_ON) || (COM_RXUBHDLR_NOTIFICATIONFLAG == STD_ON)) */

#    if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_InvalidSignalGroup2GroupSignals
**********************************************************************************************************************/
extern CONST(Com_SignalIdType, COM_PBCFG) Com_RxInv_InvalidSignalGroup2GroupSignals[];  /* COM_RXINVSIGNALGROUPCNT + 1 */
#    endif
         /* (COM_SIGNALGROUPIF == STD_ON) */
#   endif
        /* (COM_SIGNAL_ACCESS_MACRO_API != STD_ON) */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */
#  endif
       /* (COM_RXINV == STD_ON) */
/* KB end Com_RxInv_GlobalDataPrototypes */
/* KB begin Com_TxInv_GlobalDataPrototypes */
/* KB end Com_TxInv_GlobalDataPrototypes */
/* KB begin Com_TxBuffer_GlobalDataPrototypes */
# if (COM_TXBUFFER == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_TxBuffer_IpduInitValue
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_TxBuffer_IpduInitValue[];    /* Number of init bytes */

/**********************************************************************************************************************
  Com_TxBuffer_IpduInfo
**********************************************************************************************************************/
extern CONST(Com_TxBuffer_IpduInfoType, COM_PBCFG) Com_TxBuffer_IpduInfo[];     /* Number of Tx I-PDUs */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
# endif/* COM_TXBUFFER == STD_ON */
/* KB end Com_TxBuffer_GlobalDataPrototypes */
/* KB begin Com_TxDlMon_GlobalDataPrototypes */
# if (COM_TXDLMON == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_16BIT ========================================*/
#  define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_TxDlMon_TimeoutCnt
**********************************************************************************************************************/
extern VAR(uint16, COM_VAR_NOINIT) com_TxDlMon_TimeoutCnt[];    /* COM_MAXTXIPDUCNT */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_16BIT ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_TxDlMon_TimeoutTime
**********************************************************************************************************************/
extern CONST(uint16, COM_PBCFG) Com_TxDlMon_TimeoutTime[];      /* COM_TXIPDUCNT */

#   if (COM_TXDLMON_TXCONFIRMATION == STD_ON)
/**********************************************************************************************************************
  Com_TxDlMon_TimeoutContext
**********************************************************************************************************************/
extern CONST(boolean, COM_PBCFG) Com_TxDlMon_TimeoutContext[];  /* COM_TXIPDUCNT */
#   endif/* (COM_TXDLMON_TXCONFIRMATION == STD_ON) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
# endif
/* KB end Com_TxDlMon_GlobalDataPrototypes */
/* KB begin Com_TxEventDlMon_GlobalDataPrototypes */
#  if (COM_TXEVENTDLMON == STD_ON)
/**********************************************************************************************************************
  com_TxEventDlMon_TimeoutCounter
**********************************************************************************************************************/

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_16BIT ========================================*/
#   define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */
extern VAR(uint16, COM_VAR_NOINIT) com_TxEventDlMon_TimeoutCounter[];   /* COM_MAXTXIPDUCNT */
/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_16BIT ========================================*/
/* KB end Com_StopMemSection */

/**********************************************************************************************************************
  Com_TxEventDlMon_TimeoutConst
**********************************************************************************************************************/

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#   define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */
extern CONST(uint16, COM_PBCFG) Com_TxEventDlMon_TimeoutConst[];        /* COM_TXIPDUCNT */
/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

#  endif
/* KB end Com_TxEventDlMon_GlobalDataPrototypes */
/* KB begin Com_TxLLIf_GlobalDataPrototypes */
# if (COM_TXLLIF == STD_ON)

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_TXUBHDLR == STD_ON)
/**********************************************************************************************************************
  Com_TxLLIf_ClearUbMask
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_TxLLIf_ClearUbMask[];        /* Number of I-PDU mask bytes */

/**********************************************************************************************************************
  Com_TxLLIf_ClearUpdateBit
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_TxLLIf_ClearUpdateBit[];     /* COM_MAXTXIPDUCNT */
#  endif /* (COM_TXUBHDLR == STD_ON) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */


#  if ((COM_TXPDUCALLOUT == STD_ON) || (COM_TXPDUTRIGGERTRANSMITCALLOUT == STD_ON))
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#   define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_TxLLIf_PduCallout
**********************************************************************************************************************/
extern CONST(Com_TxLLIf_PduCalloutFuncPtrType, COM_CONST) Com_TxLLIf_PduCallout[];      /* COM_MAXTXCALLOUTCNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */
#  endif/* ((COM_TXPDUCALLOUT == STD_ON) || (COM_TXPDUTRIGGERTRANSMITCALLOUT == STD_ON)) */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_TXPDUCALLOUT == STD_ON)
/**********************************************************************************************************************
  Com_TxLLIf_PduCalloutIndirection
**********************************************************************************************************************/
extern CONST(Com_TxLLIf_PduCalloutIdType, COM_PBCFG) Com_TxLLIf_PduCalloutIndirection[];        /* COM_MAXTXIPDUCNT */
#  endif/* (COM_TXPDUCALLOUT == STD_ON) */

#   if (COM_TXPDUTRIGGERTRANSMITCALLOUT == STD_ON)
/**********************************************************************************************************************
  Com_TxLLIf_PduTriggerTransmitCalloutIndirection
**********************************************************************************************************************/
extern CONST(Com_TxLLIf_PduCalloutIdType, COM_PBCFG) Com_TxLLIf_PduTriggerTransmitCalloutIndirection[]; /* COM_MAXTXIPDUCNT */
#   endif/* (COM_TXPDUTRIGGERTRANSMITCALLOUT == STD_ON) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

#   if (COM_TPINTERFACE == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#    define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_TxLLIf_IsTpLayerIpdu
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_TxLLIf_IsTpLayerIpdu[];      /* COM_TXIPDUCNT */

/* KB begin Com_StopMemSection */
#    define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
#    define COM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_TxLLIf_TpPduInfo
**********************************************************************************************************************/
extern VAR(Com_TxLLIf_TpPduInfoType, COM_VAR_NOINIT) com_TxLLIf_TpPduInfo[];    /* COM_MAXTXIPDUCNT */

/* KB begin Com_StopMemSection */
#    define COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */
#   endif/* (COM_TPINTERFACE == STD_ON) */

#   if (COM_SIGNALGW_DLCROUTING == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
#    define COM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_TxLLIf_CurrentDlc
**********************************************************************************************************************/
extern VAR(PduLengthType, COM_VAR_NOINIT) com_TxLLIf_CurrentDlc[];      /* COM_MAXTXIPDUCNT */

/* KB begin Com_StopMemSection */
#    define COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#    include "MemMap.h"    /* PRQA S 5087 */    /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */
#   endif/* (COM_SIGNALGW_DLCROUTING == STD_ON) */

# endif/* COM_TXLLIF == STD_ON */
/* KB end Com_TxLLIf_GlobalDataPrototypes */
/* KB begin Com_TxModeHdlr_GlobalDataPrototypes */
# if (COM_TXMODEHDLR == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
#  define COM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_TxModeHdlr_CurrentTxMode
**********************************************************************************************************************/
extern VAR(Com_TxModeHdlr_TxModeHdlType, COM_VAR_NOINIT) com_TxModeHdlr_CurrentTxMode[];        /* COM_MAXTXIPDUCNT */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_16BIT ========================================*/
#   define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#   if (COM_TXMODEHDLR_DIRECT_REPETITION == STD_ON)
/**********************************************************************************************************************
  com_TxModeHdlr_RepCycleCnt
**********************************************************************************************************************/
extern VAR(uint16, COM_VAR_NOINIT) com_TxModeHdlr_RepCycleCnt[];        /* COM_MAXTXIPDUCNT */
#   endif/* (COM_TXMODEHDLR_DIRECT_REPETITION == STD_ON) */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_16BIT ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_8BIT ========================================*/
#   define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#   if (COM_TXMODEHDLR_DIRECT_REPETITION == STD_ON)
/**********************************************************************************************************************
  com_TxModeHdlr_RepetitionCnt
**********************************************************************************************************************/
extern VAR(uint8, COM_VAR_NOINIT) com_TxModeHdlr_RepetitionCnt[];       /* COM_MAXTXIPDUCNT */
#   endif/* (COM_TXMODEHDLR_DIRECT_REPETITION == STD_ON) */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_8BIT ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_BOOLEAN ========================================*/
#  define COM_START_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_TxModeHdlr_TransmitRequest
**********************************************************************************************************************/
extern VAR(boolean, COM_VAR_NOINIT) com_TxModeHdlr_TransmitRequest[];   /* COM_MAXTXIPDUCNT */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_BOOLEAN ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_16BIT ========================================*/
#  define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_TXMODEHDLR_CYCLIC_TRANSMISSION == STD_ON)
/**********************************************************************************************************************
  com_TxModeHdlr_CycleTimeCnt
**********************************************************************************************************************/
extern VAR(uint16, COM_VAR_NOINIT) com_TxModeHdlr_CycleTimeCnt[];       /* COM_MAXTXIPDUCNT */
#  endif/* (COM_TXMODEHDLR_CYCLIC_TRANSMISSION == STD_ON) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_16BIT ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_BOOLEAN ========================================*/
#  define COM_START_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_TXMODEHDLR_CYCLIC_TRANSMISSION == STD_ON)
/**********************************************************************************************************************
  com_TxModeHdlr_CyclicSendRequest
**********************************************************************************************************************/
extern VAR(boolean, COM_VAR_NOINIT) com_TxModeHdlr_CyclicSendRequest[]; /* COM_MAXTXIPDUCNT */
#  endif/* (COM_TXMODEHDLR_CYCLIC_TRANSMISSION == STD_ON) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_BOOLEAN ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_16BIT ========================================*/
#  define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_TXMODEHDLR_MINIMUM_DELAY == STD_ON)
/**********************************************************************************************************************
  com_TxModeHdlr_DelayTimeCnt
**********************************************************************************************************************/
extern volatile VAR(uint16, COM_VAR_NOINIT) com_TxModeHdlr_DelayTimeCnt[];      /* COM_MAXTXIPDUCNT */
#  endif/* (COM_TXMODEHDLR_MINIMUM_DELAY == STD_ON) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_16BIT ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_TxModeHdlr_TxModeTrue
**********************************************************************************************************************/
extern CONST(Com_TxModeHdlr_TxModeHdlType, COM_PBCFG) Com_TxModeHdlr_TxModeTrue[];      /* COM_MAXTXIPDUCNT */

#  if (COM_TXMODEHDLR_TXMODEFALSE == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_TxModeFalse
**********************************************************************************************************************/
extern CONST(Com_TxModeHdlr_TxModeHdlType, COM_PBCFG) Com_TxModeHdlr_TxModeFalse[];     /* COM_MAXTXIPDUCNT */
#  endif/* (COM_TXMODEHDLR_TXMODEFALSE == STD_ON) */

/**********************************************************************************************************************
  Com_TxModeHdlr_TxMode
**********************************************************************************************************************/
extern CONST(Com_TxModeHdlr_TxModeType, COM_PBCFG) Com_TxModeHdlr_TxMode[];     /* COM_MAXTXMODECNT */

#  if (COM_TXMODEHDLR_TXMODEFALSE == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_SigFilterStartIdx
**********************************************************************************************************************/
extern CONST(uint16, COM_PBCFG) Com_TxModeHdlr_SigFilterStartIdx[];     /* COM_TXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_TxModeHdlr_FilterStateInitBytes
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_TxModeHdlr_FilterStateInitBytes[];   /* COM_FILTERSTATEBYTECNT */
#  endif/* (COM_TXMODEHDLR_TXMODEFALSE == STD_ON) */

#  if (COM_TXMODEHDLR_MINIMUM_DELAY == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_MinDelayTime
**********************************************************************************************************************/
extern CONST(uint16, COM_PBCFG) Com_TxModeHdlr_MinDelayTime[];  /* COM_MAXTXIPDUCNT */
#  endif/* (COM_TXMODEHDLR_MINIMUM_DELAY == STD_ON) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

# endif/* COM_TXMODEHDLR == STD_ON */
/* KB end Com_TxModeHdlr_GlobalDataPrototypes */
/* KB begin Com_TxNHdlr_GlobalDataPrototypes */
# if (COM_TXNHDLR == STD_ON)
#  if (COM_TXNHDLR_DEFERRED_SIGNALPROCESSING == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_BOOLEAN ========================================*/
#   define COM_START_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_TxNHdlr_HandleIPduDeferred
**********************************************************************************************************************/
extern VAR(boolean, COM_VAR_NOINIT) com_TxNHdlr_HandleIPduDeferred[];   /* COM_MAXTXIPDUCNT */

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_BOOLEAN ========================================*/
/* KB end Com_StopMemSection */
#  endif/* (COM_TXNHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#  define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_TXNHDLR_NOTIFICATIONFUNCTION == STD_ON)
#   if (COM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
  Com_TxNHdlr_NotificationCnt
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_NotificationIdxType, COM_CONST) Com_TxNHdlr_NotificationCnt;
#   endif/* (COM_DEV_ERROR_DETECT == STD_ON) */

/**********************************************************************************************************************
  Com_TxNHdlr_NotificationFuncPtr
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_NotiFuncPtrType, COM_CONST) Com_TxNHdlr_NotificationFuncPtr[]; /* COM_TXSIGNOTIFICATIONCNT */
#  endif/* (COM_TXNHDLR_NOTIFICATIONFUNCTION == STD_ON) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_TXNHDLR_NOTIFICATIONFUNCTION == STD_ON)
/**********************************************************************************************************************
  Com_TxNHdlr_Ipdu2NotificationFunctions
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_NotificationIdxType, COM_PBCFG) Com_TxNHdlr_Ipdu2NotificationFunctions[];      /* COM_MAXTXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_TxNHdlr_NotiFuncIndirection
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_NotificationIdxType, COM_PBCFG) Com_TxNHdlr_NotiFuncIndirection[];     /* COM_TXSIGNOTIFICATIONCNT */
#  endif/* (COM_TXNHDLR_NOTIFICATIONFUNCTION == STD_ON) */

#  if ((COM_TXNHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) && (COM_TXNHDLR_IMMEDIATE_SIGNALPROCESSING == STD_ON))
/**********************************************************************************************************************
  Com_TxNHdlr_CallNotiDeferred
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_TxNHdlr_CallNotiDeferred[];  /* COM_TXIPDUCNT */
#  endif/* ((COM_TXNHDLR_DEFERRED_SIGNALPROCESSING == STD_ON) && (COM_TXNHDLR_IMMEDIATE_SIGNALPROCESSING == STD_ON)) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
# endif

# if (COM_TXNHDLR == STD_ON) && (COM_TXNHDLR_ERRORNOTIFICATION == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_BOOLEAN ========================================*/
#  define COM_START_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_TxNHdlr_WaitingForConfirmation
**********************************************************************************************************************/
extern VAR(boolean, COM_VAR_NOINIT) com_TxNHdlr_WaitingForConfirmation[];       /* COM_MAXTXIPDUCNT */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_BOOLEAN ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#  define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
  Com_TxNHdlr_ErrorNotiCnt
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_ErrorNotiIdxType, COM_CONST) Com_TxNHdlr_ErrorNotiCnt;
#  endif

/**********************************************************************************************************************
  Com_TxNHdlr_ErrorNotiFuncPtr
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_NotiFuncPtrType, COM_CONST) Com_TxNHdlr_ErrorNotiFuncPtr[];    /* COM_TXSIGERRORNOTICNT */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_TxNHdlr_Ipdu2ErrorFunctions
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_ErrorNotiIdxType, COM_PBCFG) Com_TxNHdlr_Ipdu2ErrorFunctions[];        /* COM_MAXTXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_TxNHdlr_ErrorNotiFuncIndirection
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_ErrorNotiIdxType, COM_PBCFG) Com_TxNHdlr_ErrorNotiFuncIndirection[];   /* COM_TXSIGNOTIFICATIONCNT */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
# endif


# if (COM_TXNHDLR == STD_ON) && (COM_TXNHDLR_TIMEOUTFUNCTION == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CONST_UNSPECIFIED ========================================*/
#  define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

#  if (COM_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
  Com_TxNHdlr_TimeoutNotiCnt
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_TimeoutIdxType, COM_CONST) Com_TxNHdlr_TimeoutNotiCnt;
#  endif

/**********************************************************************************************************************
  Com_TxNHdlr_TimeoutNotiFuncPtr
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_NotiFuncPtrType, COM_CONST) Com_TxNHdlr_TimeoutNotiFuncPtr[];  /* COM_TXSIGTIMEOUTNOTICNT */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CONST_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_TxNHdlr_Ipdu2TimeoutFunctions
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_TimeoutIdxType, COM_PBCFG) Com_TxNHdlr_Ipdu2TimeoutFunctions[];        /* COM_MAXTXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_TxNHdlr_TimeoutFuncIndirection
**********************************************************************************************************************/
extern CONST(Com_TxNHdlr_TimeoutIdxType, COM_PBCFG) Com_TxNHdlr_TimeoutFuncIndirection[];       /* COM_TXSIGTIMEOUTNOTICNT */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
# endif/* (COM_TXNHDLR == STD_ON) && (COM_TXNHDLR_TIMEOUTFUNCTION == STD_ON) */

/* KB end Com_TxNHdlr_GlobalDataPrototypes */
/* KB begin Com_TxSigIf_GlobalDataPrototypes */
# if (COM_TXSIGIF == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_BOOLEAN ========================================*/
#  define COM_START_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */


#  if (COM_SIGNALGROUPIF == STD_ON) && (COM_TXMODEHDLR_DIRECT_TRANSMISSION == STD_ON)
/**********************************************************************************************************************
  com_TxSigIf_SignalGroupEventFlag
**********************************************************************************************************************/
extern VAR(uint8, COM_VAR_NOINIT) com_TxSigIf_SignalGroupEventFlag[];   /* COM_TXSIGNALGROUPCNT */
#  endif/* (COM_SIGNALGROUPIF == STD_ON) && (COM_TXMODEHDLR_DIRECT_TRANSMISSION == STD_ON) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_BOOLEAN ========================================*/
/* KB end Com_StopMemSection */


/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */


#  if (COM_TXUBHDLR == STD_ON)
#   if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)
/**********************************************************************************************************************
  Com_TxSigIf_Signal2UbBitPos
**********************************************************************************************************************/
extern CONST(Com_Signal_SignalBitPositionType, COM_PBCFG) Com_TxSigIf_Signal2UbBitPos[];        /* COM_TXSIGNALCNT */
#   endif /* (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF) */
#  endif /* (COM_TXUBHDLR == STD_ON) */

#  if ((COM_SIGNALGROUPIF == STD_ON) && (COM_TXUBHDLR == STD_ON))
/**********************************************************************************************************************
  Com_TxSigIf_SignalGroup2UbBitPos
**********************************************************************************************************************/
extern CONST(Com_Signal_SignalBitPositionType, COM_PBCFG) Com_TxSigIf_SignalGroup2UbBitPos[];   /* COM_TXSIGNALGROUPCNT */
#  endif /* ((COM_SIGNALGROUPIF == STD_ON) && (COM_TXUBHDLR == STD_ON)) */


#  if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)
#   if (COM_TXMODEHDLR_DIRECT_TRANSMISSION == STD_ON)
/**********************************************************************************************************************
  Com_TxSigIf_SignalTransferEventProperty
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_TxSigIf_SignalTransferEventProperty[];       /* COM_TXSIGNALCNT */
#   endif/* (COM_TXMODEHDLR_DIRECT_TRANSMISSION == STD_ON) */
#  endif/* (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF) */

#  if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)
#   if (COM_TXMODEHDLR_TMS == STD_ON)
/**********************************************************************************************************************
  Com_TxSigIf_SignalFilterStateMask
**********************************************************************************************************************/
extern CONST(uint8, COM_PBCFG) Com_TxSigIf_SignalFilterStateMask[];     /* COM_TXSIGNALCNT */

/**********************************************************************************************************************
  Com_TxSigIf_SignalFilterStateOffset
**********************************************************************************************************************/
extern CONST(uint16, COM_PBCFG) Com_TxSigIf_SignalFilterStateOffset[];  /* COM_TXSIGNALCNT */
#   endif/* (COM_TXMODEHDLR_TMS == STD_ON) */
#  endif/* (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF) */

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
# endif/* COM_TXSIGIF == STD_ON */
/* KB end Com_TxSigIf_GlobalDataPrototypes */
/* KB begin Com_SignalGw_GlobalDataPrototypes */
# if (COM_SIGNALGW_DEFERREDROUTING == STD_ON)

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
#  define COM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_SignalGw_IndicationFlag
**********************************************************************************************************************/
#  if ((COM_DYNAMIC_DLC_SUPPORT == STD_ON) || (COM_SIGNALGW_DLCROUTING == STD_ON))
extern VAR(PduLengthType, COM_VAR_NOINIT) com_SignalGw_IndicationFlag[];        /* COM_MAXRXIPDUCNT */
#  else
extern VAR(boolean, COM_VAR_NOINIT) com_SignalGw_IndicationFlag[];      /* COM_MAXRXIPDUCNT */
#  endif

/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_VAR_NOINIT_BOOLEAN ========================================*/
#   define COM_START_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  com_SignalGw_IPduTimeoutFlag
**********************************************************************************************************************/
#   if (COM_SIGNALGW_RXTIMEOUT == STD_ON)
extern VAR(boolean, COM_VAR_NOINIT) com_SignalGw_IPduTimeoutFlag[];     /* COM_MAXRXIPDUCNT */
#   endif

/**********************************************************************************************************************
  com_SignalGw_UbTimeoutFlag
**********************************************************************************************************************/
#   if (COM_SIGNALGW_RXTIMEOUTUB == STD_ON)
extern VAR(boolean, COM_VAR_NOINIT) com_SignalGw_UbTimeoutFlag[];       /* COM_MAXRXUBCNT */
#   endif

/* KB begin Com_StopMemSection */
#   define COM_STOP_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#   include "MemMap.h"    /* PRQA S 5087 */     /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_VAR_NOINIT_BOOLEAN ========================================*/
/* KB end Com_StopMemSection */

/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/**********************************************************************************************************************
  Com_SignalGw_NumberOfRoutedIpdus
**********************************************************************************************************************/
extern CONST(PduIdType, COM_PBCFG) Com_SignalGw_NumberOfRoutedIpdus;

#  if ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON))
/**********************************************************************************************************************
  Com_SignalGw_IpduRoutingInfo
**********************************************************************************************************************/
extern CONST(Com_SignalGw_IpduInfoType, COM_PBCFG) Com_SignalGw_IpduRoutingInfo[];      /* COM_ROUTEDRXIPDUCNT + 1 */
#  endif /* ((COM_SIGNALIF == STD_ON) || (COM_SIGNALGROUPIF == STD_ON)) */
#  if (COM_SIGNALIF == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_SignalRR
**********************************************************************************************************************/
extern CONST(Com_SignalGw_SignalRRType, COM_PBCFG) Com_SignalGw_SignalRR[];     /* COM_SIGNALRRCNT */
#  endif /* (COM_SIGNALIF == STD_ON) */

#  if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_SignalGroupRR
**********************************************************************************************************************/
extern CONST(Com_SignalGw_SignalGroupRRType, COM_PBCFG) Com_SignalGw_SignalGroupRR[];   /* COM_SIGNALGROUPRRCNT + 1 */

/**********************************************************************************************************************
  Com_SignalGw_GroupSignalRR
**********************************************************************************************************************/
extern CONST(Com_SignalGw_GroupSignalRRType, COM_PBCFG) Com_SignalGw_GroupSignalRR[];   /* COM_PARTSIGNALRRCNT */

#  endif/* (COM_SIGNALGROUPIF == STD_ON) */

#   if (COM_SIGNALGW_MSV == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_MissingSourceValue
**********************************************************************************************************************/
extern CONST(Com_SignalGw_MsvType, COM_PBCFG) Com_SignalGw_MissingSourceValue[];        /* COM_TXIPDUCNT */

/**********************************************************************************************************************
  Com_SignalGw_RxIpdu2MsvEvents
**********************************************************************************************************************/
extern CONST(Com_SignalGw_IpduMsvEventIdType, COM_PBCFG) Com_SignalGw_RxIpdu2MsvEvents[];       /* COM_RXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_SignalGw_IpduMsvEvent
**********************************************************************************************************************/
extern CONST(Com_SignalGw_IpduMsvEventType, COM_PBCFG) Com_SignalGw_IpduMsvEvent[];     /* COM_RXIPDUMSVEVENTCNT */

#    if (COM_RXUBHDLR == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_UbMsvEvent
**********************************************************************************************************************/
extern CONST(Com_SignalGw_UbMsvEventType, COM_PBCFG) Com_SignalGw_UbMsvEvent[]; /* COM_RXUBMSVEVENTCNT */

/**********************************************************************************************************************
  Com_SignalGw_RxUb2MsvEvents
**********************************************************************************************************************/
extern CONST(Com_SignalGw_UbMsvEventIdType, COM_PBCFG) Com_SignalGw_RxUb2MsvEvents[];   /* COM_RXUBCNT + 1 */

#    endif
         /* (COM_RXUBHDLR == STD_ON) */
#   endif
        /* (COM_SIGNALGW_MSV == STD_ON) */

#   if (COM_SIGNALGW_STOPTXONRXTIMEOUT == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_StopTxOnRxToutIdx
**********************************************************************************************************************/
extern CONST(PduIdType, COM_PBCFG) Com_SignalGw_StopTxOnRxToutIdx[];    /* IL_ASRCOM_ROUTEDRXIPDUCNT + 1 */

/**********************************************************************************************************************
  Com_SignalGw_StopTxPduList
**********************************************************************************************************************/
extern CONST(PduIdType, COM_PBCFG) Com_SignalGw_StopTxPduList[];
#   endif
        /* (COM_SIGNALGW_STOPTXONRXTIMEOUT == STD_ON) */

#   if (COM_SIGNALGW_INVTXONRXTO == STD_ON)
#    if (COM_SIGNALGW_INVTXONRXTO_UB == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_RxUb2TxInvObj
**********************************************************************************************************************/
extern CONST(Com_SignalGw_Rx2TxInvObjType, COM_PBCFG) Com_SignalGw_RxUb2TxInvObj[];
#    endif/* (COM_SIGNALGW_INVTXONRXTO_UB == STD_ON) */

#    if (COM_SIGNALGW_INVTXONRXTO_IPDU == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_RxIPdu2TxInvObj
**********************************************************************************************************************/
extern CONST(Com_SignalGw_Rx2TxInvObjType, COM_PBCFG) Com_SignalGw_RxIPdu2TxInvObj[];
#    endif/* (COM_SIGNALGW_INVTXONRXTO_IPDU == STD_ON) */

#    if ((COM_SIGNALGW_INVSIG_UB == STD_ON) || (COM_SIGNALGW_INVSIG_IPDU == STD_ON))
/**********************************************************************************************************************
  Com_SignalGw_TxInvSignals
**********************************************************************************************************************/
extern CONST(Com_SignalIdType, COM_PBCFG) Com_SignalGw_TxInvSignals[];
#    endif/* (COM_SIGNALGW_INVSIG_UB == STD_ON) || (COM_SIGNALGW_INVSIG_IPDU == STD_ON)) */

#    if ((COM_SIGNALGW_INVSIGGRP_UB == STD_ON) || (COM_SIGNALGW_INVSIGGRP_IPDU == STD_ON))
/**********************************************************************************************************************
  Com_SignalGw_TxInvSignalGroups
**********************************************************************************************************************/
extern CONST(Com_SignalGroupIdType, COM_PBCFG) Com_SignalGw_TxInvSignalGroups[];
#    endif/* ((COM_SIGNALGW_INVSIGGRP_UB == STD_ON) || (COM_SIGNALGW_INVSIGGRP_IPDU == STD_ON)) */
#   endif/* (COM_SIGNALGW_INVTXONRXTO == STD_ON) */
/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */

# endif/* (COM_SIGNALGW_DEFERREDROUTING == STD_ON) */

# if (COM_SIGNALGW == STD_ON)
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_PBCFG ========================================*/
#  define COM_START_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */
/**********************************************************************************************************************
  Com_SignalGw_RxIpdu2GwHandle
**********************************************************************************************************************/
extern CONST(PduIdType, COM_PBCFG) Com_SignalGw_RxIpdu2GwHandle[];      /* COM_MAXRXIPDUCNT */
/* KB begin Com_StopMemSection */
#  define COM_STOP_SEC_PBCFG
/*lint -save -esym(961, 19.1) */
#  include "MemMap.h"    /* PRQA S 5087 */      /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_PBCFG ========================================*/
/* KB end Com_StopMemSection */
# endif/* (COM_SIGNALGW == STD_ON) */
/* KB end Com_SignalGw_GlobalDataPrototypes */
/* PRQA L:GLOBALDATAPROTOTYPES_3684 */

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/* KB begin Com_StartMemSection */
/*======================================== COM_START_SEC_CODE ========================================*/
# define COM_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/* KB end Com_StartMemSection */

/* KB begin Com_LMgt_GlobalFunctionPrototypes */
/**********************************************************************************************************************
  Com_Init
**********************************************************************************************************************/
/** \brief    This service initializes internal and external interfaces and variables of the AUTOSAR COM layer
              for the further processing. After calling this function the inter-ECU communication is still disabled.
    \param    config  Pointer to the COM configuration data, if COM_CONFIG_VARIANT 3 is configured.
    \return   none
    \pre      Com_InitMemory() has to be executed previously, if the startup code does not initialise variables.
    \context  The function must be called on task level and has not to interrupted
              by other administrative function calls.
    \note     The function is used by the Ecu State Manager
    \warning  Com_Init shall not pre-empt any COM function.
              The rest of the system must guarantee that Com_Init is not called in such a way.
**********************************************************************************************************************/
extern FUNC(void, COM_CODE) Com_Init(P2CONST(Com_ConfigType, AUTOMATIC, COM_PBCFG) config);

/**********************************************************************************************************************
  Com_InitMemory
**********************************************************************************************************************/
/** \brief    The function initialises variables, which cannot be initialised with the startup code.
    \return   none
    \pre      Com_Init() is not called yet.
    \context  The function must be called on task level.
    \note     The function is used by the application.
**********************************************************************************************************************/
extern FUNC(void, COM_CODE) Com_InitMemory(void);

# if (COM_DE_INIT_API == STD_ON )
/**********************************************************************************************************************
  Com_DeInit
**********************************************************************************************************************/
/** \brief    This service stops the inter-ECU communication. All started I-PDU groups are stopped and have
              to be started again, if needed, after Com_Init is called. By a call to ComDeInit COM is put into an
              not initialized state.
    \return   none
    \context  The function must be called on task level and has not to interrupted
              by other administrative function calls.
    \note     The function is used by the application.
    \warning  Com_DeInit shall not pre-empt any COM function.
              The rest of the system must guarantee that Com_DeInit is not called in such a way.
**********************************************************************************************************************/
extern FUNC(void, COM_CODE) Com_DeInit(void);
# endif


#  if (COM_RECEPTION_DM_API == STD_ON )
/**********************************************************************************************************************
  Com_EnableReceptionDM
**********************************************************************************************************************/
/** \brief    Enables the reception deadline monitoring for the I-PDUs within the given I-PDU group.
    \param    IpduGroupId ID of I-PDU group where reception DM shall be enabled.
    \return   none
    \context  The function must be called on task level and has not to interrupted
              by other Com_EnableReceptionDM and Com_DisableReceptionDM calls.
    \note     The function is used by the <Bus>Sm (AUTOSAR <Bus> State Manager)
**********************************************************************************************************************/
extern FUNC(void, COM_CODE) Com_EnableReceptionDM(Com_PduGroupIdType IpduGroupId);

/**********************************************************************************************************************
  Com_DisableReceptionDM
**********************************************************************************************************************/
/** \brief    Disables the reception deadline monitoring for the I-PDUs within the given I-PDU group.
    \param    IpduGroupId ID of I-PDU group where reception DM shall be disabled.
    \return   none
    \context  The function must be called on task level and has not to interrupted
              by other Com_EnableReceptionDM and Com_DisableReceptionDM calls.
    \note     The function is used by the <Bus>Sm (AUTOSAR <Bus> State Manager)
**********************************************************************************************************************/
extern FUNC(void, COM_CODE) Com_DisableReceptionDM(Com_PduGroupIdType IpduGroupId);
#  endif
       /* COM_RECEPTION_DM_API */

/**********************************************************************************************************************
  Com_IpduGroupStart
**********************************************************************************************************************/
/** \brief    Starts a preconfigured I-PDU group.
              For example, cyclic I-PDUs will be sent out cyclically after the call of Com_IpduGroupStart().
              If Initialize is true all I-PDUs of the I-PDU group shall be (re-)initialized before the I-PDU group
              is started. That is they shall behave like after a start-up of COM, for example the old_value of the
              filter objects and shadow buffers of signal groups have to be (re-)initialized.
    \param    IpduGroupId ID of I-PDU group to be started
    \param    Initialize  Flag to request initialization of the data in the I-PDUs of this I-PDU group
    \return   none
    \context  The function must be called on task level and has not to interrupted
              by other Com_IpduGroupStart and Com_IpduGroupStop calls.
    \note     The function is used by ComM (Ccl_AsrComM, AUTOSAR Communication Manager)
    \warning  Note that this function is not only called by the ComM but also from other modules e.g. diagnosis.
**********************************************************************************************************************/
extern FUNC(void, COM_CODE) Com_IpduGroupStart(Com_PduGroupIdType IpduGroupId, boolean Initialize);

/**********************************************************************************************************************
  Com_IpduGroupStop
**********************************************************************************************************************/
/** \brief    Stops a preconfigured I-PDU group.
              For example, cyclic I-PDUs will be stopped after the call of Com_IpduGroupStop().
    \param    IpduGroupId ID of I-PDU group to be stopped
    \return   none
    \context  The function must be called on task level.
    \note     The function is used by ComM (Ccl_AsrComM, AUTOSAR Communication Manager)
    \warning  A call to Com_IpduGroupStop must not be interrupted by another call to Com_IpduGroupStop,
              Com_IpduGroupStart, Com_EnableReceptionDM() or Com_DisablReceptionDM.
              Note that this function is not only called by the ComM but also from other modules e.g. diagnosis.
    \SilentBsw Parameter Check by caller
    \param     IpduGroupId  value is checked by function -> n.a.
**********************************************************************************************************************/
extern FUNC(void, COM_CODE) Com_IpduGroupStop(Com_PduGroupIdType IpduGroupId);


#  if (COM_IPDU_GROUP_TRANSMIT_API == STD_ON )
/**********************************************************************************************************************
  Com_IpduGroupTransmit
**********************************************************************************************************************/
/** \brief    Sets a transmission request for all I-PDUs of a preconfigured I-PDU group.
    \param    IpduGroupId ID of I-PDU group to be stopped
    \return   none
    \pre      The I-PDU group is started.
    \context  The function must be called on task level.
    \note     The function is used by Ccl with Il_Ni extension.
**********************************************************************************************************************/
extern FUNC(void, COM_CODE) Com_IpduGroupTransmit(Com_PduGroupIdType IpduGroupId);
#  endif/* (COM_IPDU_GROUP_TRANSMIT_API == STD_ON ) */

# if (COM_MAIN_FUNCTION_RX_API == STD_ON )
/**********************************************************************************************************************
  Com_MainFunctionRx
**********************************************************************************************************************/
/** \brief    This function shall perform the processing of the AUTOSAR COM receive processing that are not directly
              initiated by the calls from the RTE and PDU-R.
              A call to Com_MainFunctionRx returns simply if COM was not previously initialized with
              a call to Com_Init.
    \return   none
    \context  The function must be called on task level.
    \note     The function is called by the BSW Scheduler.
**********************************************************************************************************************/
extern FUNC(void, COM_CODE) Com_MainFunctionRx(void);
# endif/* (COM_MAIN_FUNCTION_RX_API == STD_ON ) */

# if (COM_MAIN_FUNCTION_TX_API == STD_ON )
/**********************************************************************************************************************
  Com_MainFunctionTx
**********************************************************************************************************************/
/** \brief    This function shall perform the processing of the AUTOSAR COM transmission activities that are not
              directly initiated by the calls from the RTE and PDU-R.
              A call to Com_MainFunctionTx returns simply if COM was not previously initialized with
              a call to Com_Init.
    \return   none
    \context  The function must be called on task level.
    \note     The function is called by the BSW Scheduler.
**********************************************************************************************************************/
extern FUNC(void, COM_CODE) Com_MainFunctionTx(void);
# endif/* (COM_MAIN_FUNCTION_TX_API == STD_ON ) */

#  if (COM_GET_CONFIGURATION_ID_API == STD_ON )
/**********************************************************************************************************************
  Com_GetConfigurationId
**********************************************************************************************************************/
/** \brief    Provides the unique identifier of the configuration.
    \return   uint32
    \context  The function can be called on interrupt and task level.
**********************************************************************************************************************/
extern FUNC(uint32, COM_CODE) Com_GetConfigurationId(void);
#  endif

#  if (COM_GET_CONFIGURATION_STRING_PTR_API == STD_ON )
/**********************************************************************************************************************
  Com_GetConfigurationString
**********************************************************************************************************************/
/** \brief    Provides a pointer to an configuration string identifier. The length is delimited by "\0".
    \return   Com_CharTypePtr
    \context  The function can be called on interrupt and task level.
**********************************************************************************************************************/
FUNC(Com_CharTypePtr, COM_CODE) Com_GetConfigurationStringPtr(void);
#  endif

/**********************************************************************************************************************
  Com_GetStatus
**********************************************************************************************************************/
/** \brief    Returns the status of the AUTOSAR COM module.
    \return   Com_StatusType
    \context  The function can be called on interrupt and task level.
**********************************************************************************************************************/
# if (COM_GET_STATUS_API == STD_ON )
extern FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void);
# else
#  if (COM_DEV_ERROR_DETECT == STD_ON)
#   define Com_GetStatus() com_LMgt_Status
#  endif
# endif

# if (COM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
  Com_GetVersionInfo
**********************************************************************************************************************/
/** \brief    Returns the version information of this module.
    \param    versioninfo Pointer to where to store the version information of this module.
    \return   none
    \context  The function can be called on interrupt and task level.
**********************************************************************************************************************/
extern FUNC(void, COM_CODE) Com_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, COM_APPL_VAR) versioninfo);
# endif/* (COM_VERSION_INFO_API == STD_ON) */


# if (COM_TRIGGER_IPDU_SEND_API == STD_ON)
/**********************************************************************************************************************
  Com_TriggerIPDUSend
**********************************************************************************************************************/
/** \brief    By a call to Com_TriggerIPDUSend the I-PDU with the given ID is triggered for transmission
    \param    ComTxPduId    ID of AUTOSAR COM Tx I-PDU.
    \return   void
    \context  The function can be called on interrupt and task level.
    \note     The function shall only be called from within an I-PDU callout.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TriggerIPDUSend(PduIdType ComTxPduId);
# endif /* (COM_TRIGGER_IPDU_SEND_API == STD_ON) */
/* KB end Com_LMgt_GlobalFunctionPrototypes */
/* KB begin Com_Signal_GlobalFunctionPrototypes */
#  if (COM_SIGNALCONVERSION == STD_ON)
/**********************************************************************************************************************
  Com_ConvertSignal
**********************************************************************************************************************/
/** \brief    The service Com_ConvertSignal() converts bus signal data to ecu internal data and vice versa. 
              If the SignalId parameter refers to a receive signal the data is converted from BUS representation to ECU
              internal representation. If the SignalId refers to a transmit signal the data is converted from ECU
              internal representation to BUS representation.
    \param    SignalId      ID of AUTOSAR COM signal to be converted.
    \param    FromDataPtr   Reference to the signal data to be converted.
    \param    ToDataPtr     Reference to the memory where the result is stored.
    \return   none
    \context  The function can be called on interrupt and task level.
    \note     The function is called by the upper layer.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_ConvertSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) FromDataPtr,
                                       P2VAR(void, AUTOMATIC, COM_APPL_VAR) ToDataPtr);

/**********************************************************************************************************************
  Com_Convert_SignedBusToEcu
**********************************************************************************************************************/
/** \brief    The service Com_Convert_SignedBusToEcu() is normally called by Com_ConvertSignal. This method can be 
              called if the parameters are all known to the caller in order to save the additional function call.
    \param    ConversionPtr  Pointer to the conversion record (see Com_Signal_GetConversion).
    \param    BusData        The unconverted value.
    \return   sint32         The converted value.
    \context  The function can be called on interrupt and task level.
    \note     The function is called by Com_ConvertSignal or the upper layer.
**********************************************************************************************************************/
FUNC(sint32, COM_CODE) Com_Convert_SignedBusToEcu(Com_Signal_SignalConvRefType ConversionPtr, sint32 BusData);

/**********************************************************************************************************************
  Com_Convert_UnsignedBusToEcu
**********************************************************************************************************************/
/** \brief    The service Com_Convert_UnsignedBusToEcu() is normally called by Com_ConvertSignal. This method can be 
              called if the parameters are all known to the caller in order to save the additional function call.
    \param    ConversionPtr  Pointer to the conversion record (see Com_Signal_GetConversion).
    \param    BusData        The unconverted value.
    \return   uint32         The converted value.
    \context  The function can be called on interrupt and task level.
    \note     The function is called by Com_ConvertSignal or the upper layer.
**********************************************************************************************************************/
FUNC(uint32, COM_CODE) Com_Convert_UnsignedBusToEcu(Com_Signal_SignalConvRefType ConversionPtr, uint32 BusData);

/**********************************************************************************************************************
  Com_Convert_SignedEcuToBus
**********************************************************************************************************************/
/** \brief    The service Com_Convert_SignedEcuToBus() is normally called by Com_ConvertSignal. This method can be 
              called if the parameters are all known to the caller in order to save the additional function call.
    \param    ConversionPtr  Pointer to the conversion record (see Com_Signal_GetConversion).
    \param    EcuData        The unconverted value.
    \return   sint32         The converted value.
    \context  The function can be called on interrupt and task level.
    \note     The function is called by Com_ConvertSignal or the upper layer.
**********************************************************************************************************************/
FUNC(sint32, COM_CODE) Com_Convert_SignedEcuToBus(Com_Signal_SignalConvRefType ConversionPtr, sint32 EcuData);

/**********************************************************************************************************************
  Com_Convert_UnsignedEcuToBus
**********************************************************************************************************************/
/** \brief    The service Com_Convert_UnsignedEcuToBus() is normally called by Com_ConvertSignal. This method can be 
              called if the parameters are all known to the caller in order to save the additional function call.
    \param    ConversionPtr  Pointer to the conversion record (see Com_Signal_GetConversion).
    \param    EcuData        The unconverted value.
    \return   uint32         The converted value.
    \context  The function can be called on interrupt and task level.
    \note     The function is called by Com_ConvertSignal or the upper layer.
**********************************************************************************************************************/
FUNC(uint32, COM_CODE) Com_Convert_UnsignedEcuToBus(Com_Signal_SignalConvRefType ConversionPtr, uint32 EcuData);
#  endif/* (COM_SIGNALCONVERSION == STD_ON) */
/* KB end Com_Signal_GlobalFunctionPrototypes */
/* KB begin Com_Buffer_GlobalFunctionPrototypes */
/* KB end Com_Buffer_GlobalFunctionPrototypes */
/* KB begin Com_RxBuffer_GlobalFunctionPrototypes */
#  if ((COM_RXUBHDLR == STD_ON) || ((COM_SIGNALGW_UB == STD_ON) && (COM_SIGNAL_ACCESS_MACRO_API != STD_ON)))
/**********************************************************************************************************************
  Com_RxBuffer_BitIsSet
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_RxBuffer_BitIsSet(PduIdType ComRxPduId, Com_Signal_SignalBitPositionType bitPos);
#  endif
/* KB end Com_RxBuffer_GlobalFunctionPrototypes */
/* KB begin Com_RxDlMon_GlobalFunctionPrototypes */
/* KB end Com_RxDlMon_GlobalFunctionPrototypes */
/* KB begin Com_RxLLIf_GlobalFunctionPrototypes */
/* KB end Com_RxLLIf_GlobalFunctionPrototypes */
/* KB begin Com_RxNHdlr_GlobalFunctionPrototypes */
#  if (COM_RXNHDLR_RXFILTER == STD_ON)
/**********************************************************************************************************************
  Com_RxNHdlr_EvaluateFilter
**********************************************************************************************************************/
#   if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
FUNC(void, COM_CODE) Com_RxNHdlr_EvaluateFilter(PduIdType ComRxPduId,
                                                P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) NewIpduBufPtr,
                                                PduLengthType ComPduLength);
#   else
FUNC(void, COM_CODE) Com_RxNHdlr_EvaluateFilter(PduIdType ComRxPduId,
                                                P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) NewIpduBufPtr);
#   endif
#  endif/* (COM_RXNHDLR_RXFILTER == STD_ON) */
/* KB end Com_RxNHdlr_GlobalFunctionPrototypes */
/* KB begin Com_RxSigIf_GlobalFunctionPrototypes */
# if (COM_SIGNALIF == STD_ON)
/**********************************************************************************************************************
  Com_ReceiveSignal
**********************************************************************************************************************/
/** \brief    The service Com_ReceiveSignal updates the signal referenced by SignalDataPtr
              with the data in the signal object identified by SignalId.
    \param    SignalId                    Id of signal to be received.
    \param    SignalDataPtr               Reference to the signal data in which to store the received data.
    \return   uint8
              E_OK                        service has been accepted
              COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped 
                                          (or service failed due to development error)
    \context  The function can be called on interrupt and task level.
    \note     The function is called by the upper layer.
**********************************************************************************************************************/
#  if (COM_SIGNAL_ACCESS_MACRO_API == STD_ON)
#   define Com_ReceiveSignal(SignalId, SignalDataPtr) Com_Get##SignalId((SignalDataPtr))
#  else
FUNC(uint8, COM_CODE) Com_ReceiveSignal(Com_SignalIdType SignalId, P2VAR(void, AUTOMATIC, COM_APPL_VAR) SignalDataPtr);
#  endif
# endif/* (COM_SIGNALIF == STD_ON) */

# if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_ReceiveShadowSignal
**********************************************************************************************************************/
/** \brief    The service Com_ReceiveShadowSignal updates the group signal which is referenced by SignalDataPtr
              with the data in the shadow buffer. The data in the shadow buffer should be updated before the call
              of Com_ReceiveShadowSignal by a call of the service Com_ReceiveSignalGroup.
    \param    SignalId                    Id of group signal to be received.
    \param    SignalDataPtr               Reference to the group signal data in which to store the received data.
    \return   void
    \context  The function can be called on interrupt and task level.
              To guarantee data consistency of the whole signal group the complete reception of a signal group
              (consecutive calls of 'Com_ReceiveSignalGroup' and 'Com_ReceiveShadowSignal')
              must not be interrupted by another reception request for the same signal group.
    \note     The function is called by the upper layer.
**********************************************************************************************************************/
#  if (COM_SIGNAL_ACCESS_MACRO_API == STD_ON)
#   define Com_ReceiveShadowSignal(SignalId, SignalDataPtr) Com_Get##SignalId((SignalDataPtr))
#  else
FUNC(void, COM_CODE) Com_ReceiveShadowSignal(Com_SignalIdType SignalId,
                                             P2VAR(void, AUTOMATIC, COM_APPL_VAR) SignalDataPtr);
#  endif

/**********************************************************************************************************************
  Com_ReceiveSignalGroup
**********************************************************************************************************************/
/** \brief    The service Com_ReceiveSignalGroup copies the received signal group from the I-PDU to the shadow buffer.
              After this call, the group signals could be copied from the shadow buffer to the upper layer by
              a call of Com_ReceiveShadowSignal.
    \param    SignalGroupId               Id of signal group to be received.
    \return   uint8
              E_OK                        service has been accepted
              COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped 
                                          (or service failed due to development error)
    \context  The function can be called on interrupt and task level.
    \note     The function is called by the upper layer.
**********************************************************************************************************************/
#  if (COM_SIGNAL_ACCESS_MACRO_API == STD_OFF)
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId);
#  else
#   define Com_ReceiveSignalGroup(SignalGroupId) Com_ReceiveSignalGroupAsMacro((Com_SignalGroupIdType) (SignalGroupId))
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroupAsMacro(Com_SignalGroupIdType SignalGroupId);
#  endif
# endif

# if (COM_SIGNAL_ACCESS_MACRO_API == STD_ON) && (COM_APPLTYPE_UINT8N == STD_ON)
/**********************************************************************************************************************
  Com_RxSigIf_ReceiveByteArray
**********************************************************************************************************************/
/** \brief    This function is necessary because the reception of a byte array requires a loop for the byte transfer.
              This requirements can not be fulfilled within a macro. Nevertheless this function is much faster than
              the normal Com_Receive(Shadow)Signal because it does not need to collect all signal attributes and 
              calculate the buffer position.
    \param    SignalDataPtr               The application data (target) pointer.
    \param    BufferDataPtr               The com_Buffer (source) pointer.
    \param    count                       The number of bytes to copy.
    \return   void
    \context  The function can be called on interrupt and task level.
    \warning  The function is called by the upper layer via signal access macros and shall not be called directly.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxSigIf_ReceiveByteArray(P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalDataPtr,
                                                  P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) BufferDataPtr,
                                                  uint16 count);
# endif
/* KB end Com_RxSigIf_GlobalFunctionPrototypes */
/* KB begin Com_RxUbHdlr_GlobalFunctionPrototypes */
/* KB end Com_RxUbHdlr_GlobalFunctionPrototypes */
/* KB begin Com_RxInv_GlobalFunctionPrototypes */
#  if (COM_RXINV == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_CheckInvalidation
**********************************************************************************************************************/
#   if (COM_DYNAMIC_DLC_SUPPORT == STD_ON)
FUNC(void, COM_CODE) Com_RxInv_CheckInvalidation(PduIdType ComRxPduId, P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) SduPtr,
                                                 P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) SduMaskPtr,
                                                 PduLengthType ComPduLength);
#   else
FUNC(void, COM_CODE) Com_RxInv_CheckInvalidation(PduIdType ComRxPduId, P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) SduPtr,
                                                 P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) SduMaskPtr);
#   endif
#  endif
       /* (COM_RXINV == STD_ON) */
/* KB end Com_RxInv_GlobalFunctionPrototypes */
/* KB begin Com_TxInv_GlobalFunctionPrototypes */
#  if (COM_TXINV == STD_ON)
#   if (COM_SIGNALIF == STD_ON)
/**********************************************************************************************************************
  Com_InvalidateSignal
**********************************************************************************************************************/
/** \brief    Sender side AUTOSAR Software Component indicates via the RTE to AUTOSAR COM that it is not able to
              provide a valid value for the corresponding signal (e.g. sensor is faulty).
              After invalidation of the current signal data a Com_SendSignal is performed internally.
    \param    SignalId      ID of signal to be invalidated.
    \return   uint8
              E_OK                        service has been accepted
              COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped 
                                          (or service failed due to development error)
    \context  The function can be called on interrupt and task level and has not to be interrupted
              by other Com_SendSignal and Com_InvalidateSignal calls for the same SignalId.
    \note     The function is called by the upper layer.
**********************************************************************************************************************/
#    if (COM_SIGNAL_ACCESS_MACRO_API == STD_OFF)
FUNC(uint8, COM_CODE) Com_InvalidateSignal(Com_SignalIdType SignalId);
#    else
#     define Com_InvalidateSignal(SignalId) Com_Invalidate##SignalId()
#    endif
       /* (COM_SIGNAL_ACCESS_MACRO_API == STD_OFF) */
#   endif/* (COM_SIGNALIF == STD_ON) */


#   if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_InvalidateSignalGroup
**********************************************************************************************************************/
/** \brief    Sender side AUTOSAR Software Component indicates via the RTE to AUTOSAR COM that it is not able to
              provide a valid value for the corresponding signal group. (e.g. sensor is faulty).
              After invalidation of the current signal group data a Com_SendSignalGroup is performed internally.
    \param    SignalGroupId      ID of signal group to be invalidated.
    \return   uint8
              E_OK                        service has been accepted
              COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped 
              (or service failed due to development error)
    \context  The function can be called on interrupt and task level and has not to be interrupted
              by other Com_InvalidateSignalGroup calls for the same SignalGroupId
              and by Com_UpdateShadowSignal calls for a SignalId which is contained in the SignalGroupId.
    \note     The function is called by the upper layer.
**********************************************************************************************************************/
#    if (COM_SIGNAL_ACCESS_MACRO_API == STD_OFF)
FUNC(uint8, COM_CODE) Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId);
#    else
#     define Com_InvalidateSignalGroup(SignalGroupId) Com_InvalidateGrp##SignalGroupId()
#    endif
       /* (COM_SIGNAL_ACCESS_MACRO_API == STD_OFF) */
#   endif/* (COM_SIGNALGROUPIF == STD_ON) */
#  endif/* (COM_TXINV == STD_ON) */
/* KB end Com_TxInv_GlobalFunctionPrototypes */
/* KB begin Com_TxBuffer_GlobalFunctionPrototypes */
/* KB end Com_TxBuffer_GlobalFunctionPrototypes */
/* KB begin Com_TxDlMon_GlobalFunctionPrototypes */
/* KB end Com_TxDlMon_GlobalFunctionPrototypes */
/* KB begin Com_TxEventDlMon_GlobalFunctionPrototypes */
#  if (COM_TXEVENTDLMON == STD_ON)

FUNC(void, COM_CODE) Com_TxEventDlMon_Event(PduIdType ComTxPduId);

#  endif
       /* COM_TXEVENTDLMON == STD_ON */
/* KB end Com_TxEventDlMon_GlobalFunctionPrototypes */
/* KB begin Com_TxLLIf_GlobalFunctionPrototypes */
# if (COM_TSI_TESTCODE == STD_ON)
/* ##V_TEST_CODE_START ##visdbi */
/**********************************************************************************************************************
  Com_TxLLIf_InhibitTxConfirmation
**********************************************************************************************************************/
/** \brief    This function inhibits the Tx Confirmation of the given Tx I-Pdu.
              Use COM_PDUID_MAXVAL to release the lock.
    \param    ComTxPduId     ID of AUTOSAR COM I-PDU to be inhibited.
    \return   void
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxLLIf_InhibitTxConfirmation(PduIdType ComTxPduId);
/* ##V_TEST_CODE_END ##visdbi */
# endif/* (COM_TSI_TESTCODE == STD_ON) */
/* KB end Com_TxLLIf_GlobalFunctionPrototypes */
/* KB begin Com_TxModeHdlr_GlobalFunctionPrototypes */
#  if (COM_TXEVENTDLMON == STD_ON)
/**********************************************************************************************************************
Com_TxModeHdlr_StopCyclicTransmission
**********************************************************************************************************************/
/** \brief    This method stops the cyclic transmission of an I-PDU and cancels outstanding transmission requests of
              an I-PDU, if the I-PDU is active.
    \param    ComTxPduId    ID of AUTOSAR COM Tx I-PDU.
    \return   none
    \context  The function can be called on interrupt and task level,
              but must not interfer with Com_TxModeHdlr_MainFunction.
    \SilentBsw Parameter Check by caller
    \param     ComTxPduId  value checked by function -> n.a.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_StopCyclicTransmission(CONST(PduIdType, AUTOMATIC) ComTxPduId);
#  endif/* (COM_TXEVENTDLMON == STD_ON) */

# if (COM_TSI_TESTCODE == STD_ON) || (COM_SIGNALGW_CANMOST == STD_ON)
/**********************************************************************************************************************
Com_TxModeHdlr_StopTransmission
**********************************************************************************************************************/
/** \brief    This method stops the cyclic transmission of an I-PDU and cancells outstanding transmission requests of
              an I-PDU and reloads the time offset counter, if the I-PDU is restarted later.
    \param    ComTxPduId    ID of AUTOSAR COM Tx I-PDU.
    \return   none
    \context  The function can be called on interrupt and task level,
              but must not interfer with Com_TxModeHdlr_MainFunction.
    \note     The function is called by the Testsuite.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_StopTransmission(CONST(PduIdType, AUTOMATIC) ComTxPduId);
# endif/* (COM_TSI_TESTCODE == STD_ON) || (COM_SIGNALGW_CANMOST == STD_ON) */


# if (COM_TXMODEHDLR_DIRECT_TRANSMISSION == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_TriggerDeferredIpduSend
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_TriggerDeferredIpduSend(CONST(PduIdType, AUTOMATIC) ComTxPduId
#   if (COM_TXMODEHDLR_DIRECT_WITHOUTREPETITION == STD_ON)
                                                            , boolean TriggerWithoutRepetition
#   endif
  );
# endif /* (COM_TXMODEHDLR_DIRECT_TRANSMISSION == STD_ON) */

# if ((COM_SIGNALIF == STD_ON) && (COM_TXMODEHDLR_TMS == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_UpdateTxMode
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_UpdateTxMode(CONST(PduIdType, AUTOMATIC) ComTxPduId, uint16 FilterByteOffs,
                                                 uint8 FilterBitMask, boolean FilterState);
# endif /* ((COM_SIGNALIF == STD_ON) && (COM_TXMODEHDLR_TMS == STD_ON)) */

# if ((COM_SIGNALGROUPIF == STD_ON) && (COM_TXMODEHDLR_TMS == STD_ON))
/**********************************************************************************************************************
  Com_TxModeHdlr_UpdateFilterBit
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_UpdateFilterBit(uint16 FilterByteOffs, uint8 FilterBitMask, boolean FilterState);
# endif /* ((COM_SIGNALGROUPIF == STD_ON) && (COM_TXMODEHDLR_TMS == STD_ON)) */

#  if (COM_TXEVENTDLMON == STD_ON)
/**********************************************************************************************************************
  Com_TxModeHdlr_StartCyclicTransmission
**********************************************************************************************************************/
/** \brief    This method starts the cyclic transmission of an I-PDU.
              The time offset is NOT taken into account and the delay time will be reset.
    \param    ComTxPduId    ID of AUTOSAR COM Tx I-PDU.
    \return   none
    \context  The function can be called on interrupt and task level,
              but must not interfer with Com_TxModeHdlr_MainFunction.
    \SilentBsw Parameter Check by caller
    \param     ComTxPduId  checked by function -> n.a.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_StartCyclicTransmission(CONST(PduIdType, AUTOMATIC) ComTxPduId);
#  endif

# if (COM_TSI_TESTCODE == STD_ON)
/* ##V_TEST_CODE_START ##Ms */
/**********************************************************************************************************************
  Com_TxModeHdlr_StartDeferredCyclicTransmission
**********************************************************************************************************************/
/** \brief    This method starts the cyclic transmission of an I-PDU.
              The time offset is taken into account and the delay time will be reset.
    \param    ComTxPduId    ID of AUTOSAR COM Tx I-PDU.
    \return   none
    \context  The function can be called on interrupt and task level,
              but must not interfer with Com_TxModeHdlr_MainFunction.
    \note     The function is called by the Testsuite.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_StartDeferredCyclicTransmission(CONST(PduIdType, AUTOMATIC) ComTxPduId);

/**********************************************************************************************************************
  Com_TxModeHdlr_TriggerImmediateIpduSend
**********************************************************************************************************************/
/** \brief    This method sets an transmission request. The I-PDU transmit request is performed with the next tx
              task call. The time offset is not taken into account.
    \param    ComTxPduId    ID of AUTOSAR COM Tx I-PDU.
    \return   none
    \context  The function can be called on interrupt and task level,
              but must not interfer with Com_TxModeHdlr_MainFunction.
    \note     The function is called by the Testsuite.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxModeHdlr_TriggerImmediateIpduSend(CONST(PduIdType, AUTOMATIC) ComTxPduId);
/* ##V_TEST_CODE_END ##Ms */
# endif/* (COM_TSI_TESTCODE == STD_ON) */
/* KB end Com_TxModeHdlr_GlobalFunctionPrototypes */
/* KB begin Com_TxNHdlr_GlobalFunctionPrototypes */
/* KB end Com_TxNHdlr_GlobalFunctionPrototypes */
/* KB begin Com_TxSigIf_GlobalFunctionPrototypes */
# if (COM_SIGNALIF == STD_ON)
/**********************************************************************************************************************
  Com_SendSignal
**********************************************************************************************************************/
/** \brief    The service Com_SendSignal updates the signal object identified by SignalId
              with the signal data referenced by the SignalDataPtr parameter. 
              If the signal has any triggered transfer property and the current transmission mode of the Tx I-PDU
              has a DIRECT part, the update is followed by a transmission of the Tx I-PDU within the next mainfunction
              Tx call respecting the minimum delay time.
    \param    SignalId      ID of signal to be sent.
    \param    SignalDataPtr Reference to the signal data to be transmitted.
    \return   uint8
              E_OK                        service has been accepted
              COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped 
                                          (or service failed due to development error)
    \context  The function can be called on interrupt and task level and has not to be interrupted
              by other Com_SendSignal and Com_InvalidateSignal calls for the same SignalId.
    \note     The function is called by the upper layer.
    \warning  If the method is used on a microcontroller like the Tms320 DSP and the datatype uint8 is unsigned short
              the 8 MSB bits of the variable shall never be set.
              If the method is used on a microcontroller like the S12X and the datatype is uint16, sint16, uint32
              or sint32 the SignalDataPtr must be word aligned.
**********************************************************************************************************************/
#  if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)
FUNC(uint8, COM_CODE) Com_SendSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#  else
#   define Com_SendSignal(SignalId, SignalDataPtr) Com_Set##SignalId((SignalDataPtr))
#   if ((COM_TXMODEHDLR_TMS == STD_ON) || (COM_TMS_SUPPORT == STD_OFF))
FUNC(uint8, COM_CODE) Com_SendSignalAsMacro(Com_SignalIdType SignalId,
                                            P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#   endif
#  endif/* (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF) */
# endif/* (COM_SIGNALIF == STD_ON) */

# if (COM_SIGNALGROUPIF == STD_ON)
/**********************************************************************************************************************
  Com_SendSignalGroup
**********************************************************************************************************************/
/** \brief    The service Com_SendSignalGroup copies the content of the associated shadow buffer to
              the associated I-PDU. Prior to this call, all group signals should be updated in the shadow buffer by
              the call of Com_UpdateShadowSignal.
    \param    SignalGroupId      ID of signal group to be send.
    \return   uint8
              E_OK                        service has been accepted
              COM_SERVICE_NOT_AVAILABLE   corresponding I-PDU group was stopped 
              (or service failed due to development error)
    \context  The function can be called on interrupt and task level and has not to be interrupted
              by other Com_SendSignalGroup calls for the same SignalGroupId.
    \note     The function is called by the upper layer.
**********************************************************************************************************************/
#  if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)
FUNC(uint8, COM_CODE) Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId);
#  else
#   define Com_SendSignalGroup(SignalGroupId) Com_SendSignalGroupAsMacro((Com_SignalGroupIdType) (SignalGroupId))
FUNC(uint8, COM_CODE) Com_SendSignalGroupAsMacro(Com_SignalGroupIdType SignalGroupId);
#  endif

/**********************************************************************************************************************
  Com_UpdateShadowSignal
**********************************************************************************************************************/
/** \brief    The service Com_UpdateShadowSignal updates a group signal with the data, referenced by SignalDataPtr.
              The update of the group signal data is done in the shadow buffer, not in the I-PDU.
              To send out the shadow buffer, Com_SendSignalGroup has to be called.
              Sign extension and byte swapping are performed as the group signal is inserted into the shadow buffer.
    \param    SignalId      ID of group signal to be updated.
    \param    SignalDataPtr Reference to the group signal data to be updated.
    \return   void
    \context  The function can be called on interrupt and task level.
              To guarantee data consistency of the whole signal group the complete transmission of a signal group
              (consecutive calls of 'Com_UpdateShadowSignal' and 'Com_SendSignalGroup')
              must not be interrupted by another transmission request for the same signal group
              or by a call of 'Com_InvalidateSignalGroup'.
    \note     The function is called by the upper layer.
    \warning  If the method is used on a microcontroller like the S12X and the datatype is uint16, sint16, uint32
              or sint32 the SignalDataPtr must be word aligned.
**********************************************************************************************************************/
#  if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_OFF)
FUNC(void, COM_CODE) Com_UpdateShadowSignal(Com_SignalIdType SignalId,
                                            P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#  else
#   define Com_UpdateShadowSignal(SignalId, SignalDataPtr) Com_Set##SignalId((SignalDataPtr))
#   if ((COM_TXMODEHDLR_TMS == STD_ON) || (COM_TMS_SUPPORT == STD_OFF))
FUNC(void, COM_CODE) Com_UpdateShadowSignalAsMacro(Com_SignalIdType SignalId,
                                                   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#   endif
#  endif
# endif/* (COM_SIGNALGROUPIF == STD_ON) */

# if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_ON) && (COM_APPLTYPE_UINT8N == STD_ON)
/**********************************************************************************************************************
  Com_TxSigIf_SendByteArray
**********************************************************************************************************************/
/** \brief    This function is necessary because the transmission of a byte array requires a loop for the byte transfer
              This requirements can not be fulfilled within a macro. Nevertheless this function is much faster than the
              normal Com_(Send/UpdateShadow)Signal because it does not need to collect all signal attributes and 
              calculate the buffer position.
    \param    SignalDataPtr               The application data (source) pointer.
    \param    BufferDataPtr               The com_Buffer (target) pointer.
    \param    count                       The number of bytes to copy.
    \return   void
    \context  The function can be called on interrupt and task level.
    \warning  The function is called by the upper layer via signal access macros and shall not be called directly.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxSigIf_SendByteArray(P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) SignalDataPtr,
                                               P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) BufferDataPtr, uint16 count);
# endif /* (COM_TXSIGNAL_ACCESS_MACRO_API == STD_ON) && (COM_APPLTYPE_UINT8N == STD_ON) */

# if (COM_TXSIGNAL_ACCESS_MACRO_API == STD_ON) && (COM_APPLTYPE_UINT8N == STD_ON) && (COM_TXSIGIF_TRIGGEREDONCHANGE == STD_ON)
/**********************************************************************************************************************
  Com_TxSigIf_SendTriggeredOnChangeByteArray
**********************************************************************************************************************/
/** \brief    This function is necessary because the trigger condition test and the transmission of a byte array 
              requires a loop for the byte transfer.
              This requirements can not be fulfilled within a macro. Nevertheless this function is much faster than the
              normal Com_(Send/UpdateShadow)Signal because it does not need to collect all signal attributes and 
              calculate the buffer position.
    \param    SignalDataPtr               The application data (source) pointer.
    \param    BufferDataPtr               The com_Buffer (target) pointer.
    \param    count                       The number of bytes to copy.
    \return   void
    \context  The function can be called on interrupt and task level.
    \warning  The function is called by the upper layer via signal access macros and shall not be called directly.
**********************************************************************************************************************/
FUNC(boolean,
     COM_CODE) Com_TxSigIf_SendTriggeredOnChangeByteArray(P2CONST(uint8, AUTOMATIC, COM_APPL_VAR) SignalDataPtr,
                                                          P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) BufferDataPtr,
                                                          uint16 count);
# endif /* (COM_TXSIGNAL_ACCESS_MACRO_API == STD_ON) && (COM_APPLTYPE_UINT8N == STD_ON) && (COM_TXSIGIF_TRIGGEREDONCHANGE == STD_ON) */
/* KB end Com_TxSigIf_GlobalFunctionPrototypes */
/* KB begin Com_SignalGw_GlobalFunctionPrototypes */
# if (COM_SIGNALGW == STD_ON)
/**********************************************************************************************************************
  Com_MainFunctionRouteSignals
**********************************************************************************************************************/
/** \brief   Calls the signal gateway part of COM to forward received signals to be routed.
             The insertion of this call is necessary for decoupling receive interrupts and signal gateway tasks.
             A call to Com_MainFunctionRouteSignals returns simply if COM was not previously initialized with a
             call to Com_Init.
    \return  None
    \context The function must be called on task level.
    \note    The function is called by the BSW Scheduler.
    \warning The time between to consecutive calls (perhaps the related task/thread cycle)
             affects directly the signal gateway latency.
**********************************************************************************************************************/
#   if (COM_SIGNALGW_DEFERREDROUTING == STD_ON)
FUNC(void, COM_CODE) Com_MainFunctionRouteSignals(void);
#   else
#    define Com_MainFunctionRouteSignals()
#   endif
# endif/* (COM_SIGNALGW == STD_ON) */

#  if (COM_SIGNALGW_IMMEDIATEROUTING == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_RouteImmediate
**********************************************************************************************************************/
/** \brief   This function performs the signal routings for Rx I-PDUs
             with ComIPduSignalProcessing configured to IMMEDIATE.
             Only the signal data is copied from Rx to Tx buffer and the transmission mode conditions are evaluated.
             Com_MainfunctionTx() is still required for transmission request of the corresponding Tx I-PDU.
    \param   ComRxPduId    ID of AUTOSAR COM Rx I-PDU.
             ComPduLength  Length of the received Rx I-PDU.
    \return  None
    \context The function is called on interrupt or on task level.
    \note    The function is called by Com_RxIndication.
    \SilentBsw Parameter Check by caller
    \param     ComRxPduId  value has to satisfy following condition 
                           (ComRxPduId < Com_ConfigStruct.Com_ConfigTypeCom_RxBuffer_RxIpduCnt)
    \param     ComPduLength value not used as pointer write access index -> n.a.
**********************************************************************************************************************/
#   if ((COM_DYNAMIC_DLC_SUPPORT == STD_ON) || (COM_SIGNALGW_DLCROUTING == STD_ON))
FUNC(void, COM_CODE) Com_SignalGw_RouteImmediate(PduIdType ComRxPduId, PduLengthType ComPduLength);
#   else
FUNC(void, COM_CODE) Com_SignalGw_RouteImmediate(PduIdType ComRxPduId);
#   endif
#  endif/* (COM_SIGNALGW_IMMEDIATEROUTING == STD_ON) */
/* KB end Com_SignalGw_GlobalFunctionPrototypes */

/* KB begin Com_StopMemSection */
# define COM_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== COM_STOP_SEC_CODE ========================================*/
/* KB end Com_StopMemSection */
#endif /* COM_H */

/**********************************************************************************************************************
  END OF FILE: Com.h
**********************************************************************************************************************/
/* STOPSINGLE_OF_MULTIPLE */
