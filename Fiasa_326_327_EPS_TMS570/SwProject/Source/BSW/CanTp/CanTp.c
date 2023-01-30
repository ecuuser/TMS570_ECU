/**************************************************************************************************
   Project Name: AUTOSAR_GbR CAN-TP
      File Name: CanTp.c

    Description: Implementation of the AUTOSAR CAN Transport Protocol, according to:
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
   Mhe          Matthias Heil             Vector Informatik GmbH
   Tne          Thomas Necker             Vector Informatik GmbH
   Dth          Thomas Dedler             Vector Informatik GmbH

  -------------------------------------------------------------------------------------------------
                 R E V I S I O N   H I S T O R Y
  -------------------------------------------------------------------------------------------------
   Date         Rev.     Author  Description
   ----------   -------  ------  ------------------------------------------------------------------
   2006-10-04   1.00.00  Her     Initial version
   2007-02-23   1.01.00  Her     Added HighRxLowTx Priority inversion
   2007-03-02   1.02.00  Her     ESCAN00019812: corrected typo (rx- instead of tx-init called 
   2007-05-17   1.03.00  Her     ESCAN00021101: AUTOSAR Rel. 2.1
   2007-09-12   1.04.00  Her     ESCAN00022298: no changes
                         Her     ESCAN00022367: cleaned warnings
                         Her     ESCAN00022368: cleaned warnings
   2007-11-19   1.05.00  Her     ESCAN00023272: Initialization of pTpTxState is incomplete
   2007-12-07   1.06.00  Her     ESCAN00023559: CanTp_Transmit: incorrect function parameter
   2008-01-16   1.07.00  Her     ESCAN00024058: Rx buffer provision (incomplete first CF) corrected
                         Her     ESCAN00024152: ASR R. 3.0 new requirements
   2008-02-14   1.07.01  Her     ESCAN00024691: Rx buffer provision fails with blocksize zero
                                                added new DEM macro
   2008-03-28   1.07.02  Her     ESCAN00025806: adapted to CanIf Rel. 3.1
   2008-04-08   1.08.00  Her     ESCAN00025872: Correct setting of DEM errors
                         Her     ESCAN00025890: Rx buffer provision behaviour corrected
                         Her     ESCAN00026036: Wrong sequence number in consecutive frame of segmented TP transmission
   2008-04-22   1.09.00  Her     ESCAN00026172: Introduction of the Library Version Check
                         Her     ESCAN00026250: Rename files and #include statements according coding styles
                         Her     ESCAN00026671: Extension for MSR3.0 generator version checks
                         Her     ESCAN00027017: Use dynamic channel allocation to reduce resource consumption
   2008-06-13   1.09.01  Her     ESCAN00027556: Missing cast leads to generator tool compatiblity check failing
   2008-06-19   1.09.02  Her     ESCAN00027716: Transmission failure
   2008-06-20   1.09.03  Her     ESCAN00027749: First Frame is transmitted instead of a Single Frame
   2008-06-24   1.09.04  Her     ESCAN00027838: Adapt CanTp configuration table start address for post build process
   2008-07-02   1.09.05  Her     ESCAN00028008: Abort initialization after failed generator version check
   2008-07-11   1.09.06  Her     ESCAN00028326: Resource optimization transfered to GENy
   2008-07-31   1.10.00  Her     ESCAN00028721: Length check for Flow Control frames corrected
                         Her     ESCAN00028856: Reduce resource consumption: addressing type, buffer provision, single connection
                         Her     ESCAN00029776: Conditioning of dummy statements
   2008-09-23   1.10.01  Her     ESCAN00029781: Pre-Compile and Link-Time CRC Check
                         Her     ESCAN00030174: Complete support of Tx burst mode, added missing CanTp_TxStateTask call
                         Her     ESCAN00030387: Compiler warnings cleaned up
   2008-11-11   1.10.02  Her     ESCAN00031233: Reduce resource consumption (add functional reception to single connection path)
                         Her     ESCAN00031610: Reception of unexpected frames on an unidirectional Tx channel
                         Her     ESCAN00031715: Burst mode extension (support high-speed transmission and reception)
                         Her     ESCAN00032191: Assertion fails erroneously (cleanup compiler warnings)
   2009-01-14   1.10.03  Her     ESCAN00032339: Wrong Tx SDU-ID used
   2009-01-16   1.10.04  Her     ESCAN00032433: Illegal memory access via NULL pointer
   2009-01-20   1.10.05  Her     ESCAN00032453: CanTp_InitMemory initialization not correct
                         Her     ESCAN00032472: MISRA conformance improved
                         Her     ESCAN00032522: Split the CanTp_MainFunction into Rx and Tx part
                         Her     ESCAN00032539: Reception data overwrites internal memory
                         Her     ESCAN00033192: Compiler error for single connection precompile configuration
   2009-01-25   1.11.00  Her     ESCAN00033429: Wait Frames: CanTp_WFTmax data type changed (uint8 to uint16)
                         Her     ESCAN00032786: Indications to the application must be aware of the application status
                         Her     ESCAN00033439: Remapping of NSDU-IDs to user configured numbers
                         Her     ESCAN00033512: Support dynamic Flow Control N-PDU content 
                         Her     ESCAN00033922: No changes
   2009-07-01   1.12.00  Her     ESCAN00033693: Add support for multiple configuration
                         Her     ESCAN00033785: Optimized TP Routing (ASR4.0)
                         Her     ESCAN00034541: Using Rx instead of Tx channel count
                         Her     ESCAN00034627: CanTp_Transmit wrapper function for remapped NSDU-ID handling
                         Her     ESCAN00034663: Compiler error for single connection configuration
                         Her     ESCAN00034706: Tx Buffer provision delivers BUSY 
                         Her     ESCAN00035809: Compiler abstraction missing
                         Her     ESCAN00036040: Compilerwarning (condition always false) in CanTp_Shutdown
                         Her     ESCAN00036117: no changes
   2009-07-20   1.13.00  Her     ESCAN00036540: Transmission stops after unexpected Flow Control reception
                         Her     ESCAN00035216: Add Mixed-11 Addressing for CAN/LIN-Gateway Use Case
                         Her     ESCAN00036456: from untested beta to tested release version
   2009-08-11   1.14.00  Her     ESCAN00036875: Missing PduR_CanTpTxConfirmation call in case of Tx buffer provision timeout
   2009-08-25   1.14.01  Her     ESCAN00037344: Missing preprocessor switch leads to a compile error
   2009-08-26   1.14.02  Her     ESCAN00037347: STmin is gone below
                         Her     ESCAN00037393: CanTp receives wrong Sdu (phys/func sorting goes wrong)
   2009-08-28   1.14.03  Her     ESCAN00037422: N_Br has not necessarily to be used in the code
                         Her     ESCAN00037425: Move default AUTOSAR macros from source to include file
                         Her     ESCAN00038075: Double Flow Control frame transmission
   2009-11-03   1.14.04  Her     ESCAN00037284: Use 2 ProvideRxBufferCalls for the FF
                         Her     ESCAN00038848: Make CanTp228 requirement optional
                         Her     ESCAN00039090: Avoid superfluous wait frames
                         Her     ESCAN00039468: compile error for Single Connection Pre-Compile
                         Her     ESCAN00039477: Single Connection without functional Rx-NSduId uses tphdl
                         Her     ESCAN00039533: compiler warning (variable pRxNsduCfg was set but never used)
                         Her     ESCAN00039572: Compiler error for strict compiler options
   2009-12-10   1.14.05  Her     ESCAN00039586: Dynamic BS calculation optimization
                         Her     ESCAN00039216: Optimization of Tx Interrupt runtime
                         Her     ESCAN00040003: MISRA conformance improved 
                         Her     ESCAN00040045: Wrong Pdu-Id used within the PduR_CanTpRxIndication
                         Her     ESCAN00040084: no changes
   2010-02-18   1.15.00  Her     ESCAN00040792: Interrupt lock is missing for dynamic channel assignment
                         Her     ESCAN00040300: Switch CanTp Parameters BS, Stmin at runtime via CanTp_ChangeParameterRequest API
                         Her     ESCAN00041040: Revert wrong optimization based on ESCAN00039216
                         Her     ESCAN00041114: Use 2 ProvideRxBufferCalls for the FF reception
                         Her     ESCAN00041628: Reset the transmit state to idle before calling the confirmation callout function of the PduR
                         Her     ESCAN00041870: Avoid calling of the confirmation callout function of the PduR during power up
                         Her     ESCAN00041916: Consistency of preprocessor switches
                         Her     ESCAN00042052: For functional diagnostic requests the wrong Id is handed to the PduR
                         Her     ESCAN00042563: Improve critical section protection for nested interrupts
                         Her     ESCAN00042575: Strictly keep the reception sequence independent of the buffer provision return value
                         Her     ESCAN00042652: Adapt type of invalid handle definition to the PduIdType definition
                         Her     ESCAN00042958: PDUR returns BUFREQ_E_BUSY endlessly
                         Her     ESCAN00042945: N_CS Timeout not working properly
                         Her     ESCAN00042882: Significant runtime increase of main functions
                         Her     ESCAN00042885: Runtime optimization of local pointers used in main functions
                         Her     ESCAN00043033: Missing TX buffer check during last cycle of NCS timeout
   2010-06-17   1.15.01  Mhe     ESCAN00043464: CanTp stops receiving and stops interacting with PduR
   2010-06-28   1.15.02  Tne     ESCAN00043558: CanTp causes exception due to read access to unmapped memory area
   2010-07-15   1.16.00  Her     ESCAN00040590: Optimize constant Sdu settings in precompile variant
                         Her     ESCAN00043991: Support TP Receive Cancellation
                         Her     ESCAN00044193: Using FC (N_Bs) instead of CF (N_Cs) timeout
                         Her     ESCAN00044239: Support nested interrupt handling for CanTp_RxIndication
                         Her     ESCAN00044374: Change Parameter API function accesses unmapped memory
                         Her     ESCAN00044670: Assure that calculated timer values are greater than zero
                         Her     ESCAN00044857: Compiler warnings:  "variable set but never used" and "nested comment"
   2010-09-23   1.16.01  Her     ESCAN00045555: Compile error "unexpected end of file in macro expansion"
                         Her     ESCAN00045557: Use different defines for invalid BS and STmin
   2010-09-28   1.16.02  Her     ESCAN00045609: Compile error "'CANTP_DL' : is not a member of 'sTxNsduCfg'; undeclared identifier"
                         Her     ESCAN00045702: Compile error: "undefined variable 'pTxNsduCfg'"
                         Her     ESCAN00045739: Flow Control with status "Wait" is suppressed erroneously
   2010-10-08   1.16.03  Her     ESCAN00045856: transmission stops due to an erroneous timeout
   2010-10-13   1.17.00  Her     ESCAN00045283: Replace use of V_USE_DUMMY_STATEMENT
                         Her     ESCAN00045310: Change the transmit cancellation availability from general to connection specific
                         Her     ESCAN00045765: Change selected production errors to development errors
                         Her     ESCAN00046076: Ignore invalid CanTp messages without DET error reporting
                         Her     ESCAN00046284: Adapt AUTOSAR version check
                         Her     ESCAN00047069: Compiler Error undeclared identifier  'CANTP_NAR'
                         Her     ESCAN00047079: TP High-Level routing too slow for Stmin = 0
                         Her     ESCAN00047291: Support specific Wait Frame overrun indication
                         Her     ESCAN00047353: Adapt CanTp_MainFunction for usage with Identity Manager Configuration
                         Her     ESCAN00047528: TP High Level routing speeding up
                         Her     ESCAN00047788: Use CanIf transmit cancellation to avoid unexpected confirmations
                         Her     ESCAN00047978: TP accepts N-PDUs with a too small DLC
                         Her     ESCAN00048115: Support more than 255 statically configured Sdu-Id for Rx and Tx side
   2011-02-22   1.18.00  Her     ESCAN00048099: Asynchronous frame transmission from task level
                         Her     ESCAN00048895: Improve handling of development errors
                         Her     ESCAN00049011: Compiler warning:variable "pRxNsduCfg" was set but never used
                         Her     ESCAN00049026: Non ISO compliant customer specific  behaviour for FC and CF reception
                         Her     ESCAN00049050: AUTOSAR 4 compatibility
                         Her     ESCAN00049130: Add DCM call-out for every Mixed11-Addressing FF or SF reception
                         Her     ESCAN00049199: Correction of frame length calculation 
   2011-04-06   1.18.01  Her     ESCAN00049698: no changes
                         Her     ESCAN00049839: no changes
   2011-04-07   1.18.02  Her     ESCAN00049947: no changes
   2011-04-12   1.18.03  Her     ESCAN00050027: Instance Id is obsolete for GetVersionInfo
                         Her     ESCAN00050043: Use NULL_PTR instead of TP_NORETRY
   2011-04-20   1.19.00  Her     ESCAN00048513: Transmission confirmation cannot be resolved
                         Her     ESCAN00049432: Check maximum transmit length
                         Her     ESCAN00049945: Support Half Duplex communication
                         Her     ESCAN00050534: Cancellation of wrong NPduId in the CanIf
                         Her     ESCAN00050563: Wrong STmin value used in FC frames
                         Her     ESCAN00063835: Wrong BS value used by CanTp
                         Her     ESCAN00050773: 2'nd functional diagnostic request does not respond
                         Her     ESCAN00052244: CanTp channel resource allocation fails
   2011-08-15            Dth     ESCAN00052682: CANTP_##ECK_HALF_DUPLEX renamed to CANTP_##__ENABLE_HALF_DUPLEX_CHECK
                         Dth     ESCAN00052760: Handling for invalid SduId missing in half duplex mode
   2011-11-17   1.20.00  Dth     ESCAN00053503: no changes
                         Dth     ESCAN00051742: Remove the AUTOSAR Release Version Check
                         Dth     ESCAN00054836: Wrong number of parameters for vCanTp_DetAssert
                         Dth     ESCAN00052691: dummy statement replaced by conditional variable declarations
                         Dth     ESCAN00053503: critical section handling only via SchM
                         Dth     ESCAN00054280: pointer check in vCanTp_RxRetrieveApplRxBuffer changed
                         Dth     ESCAN00054364: buffer provision with CANTP_ASYNC_TRANSMIT corrected
                         Dth     ESCAN00054664: inconsistent FC.WT timeouts resolved
                         Dth     ESCAN00054300: incomplete re-initialization of Tx channel resolved
                         Dth     ESCAN00054324: handling of DET errors in CanTp_ReadParameterRequest corrected
                         Dth     ESCAN00054420: SduId/PduId check in CanTp_Transmit and CanTp_RxIndiation corrected
                         Dth     ESCAN00054523: simplified use of configuration access macros
                         Dth     ESCAN00054525: behavior of uninitialized CanTp corrected
                         Dth     ESCAN00054819: duplicate initialization check removed
                         Dth     ESCAN00054656: busy buffers not supported with TX_FULL_BUFFER_PROVISION = OFF
                         Dth     ESCAN00054700: correction of Tx buffer handling with status BUFREQ_E_OVFL
                         Dth     ESCAN00054685: correction of Rx buffer handling with too small buffers
                         Dth     ESCAN00055330: inconsistent implementation of CANTP_OPER_NOT_SUPPORTED_REPORT_DEM
   2012-01-05   1.20.01  Dth     ESCAN00055795: incomplete re-initialization of Rx channel resolved
                         Dth     ESCAN00055799: reporting of invalid Tx buffer changed to DET
                         Dth     ESCAN00055814: timeout of unexpected FF reception due to blocked TxSemaphore resolved
                         Dth     ESCAN00055822: blocked CanTp after missing Tx Confirmation resolved
   2012-01-23   1.20.02  Dth     ESCAN00056210: Compile error: 'CANTP_NBR' : is not a member of 'sRxNsduCfg'
   2012-02-22   1.20.03  Dth     ESCAN00056988: Compile error: CANTP_VAR_INIT is undefined
                         Dth     ESCAN00056192: no changes
   2012-02-23   1.21.00  Dth     ESCAN00056792: modified SduId handling with Cfg5 for RxCancellation and Read/ChangeParameter APIs
                         Dth     ESCAN00056193: no changes
                         Dth     ESCAN00056951: negative result of CanIf_Transmit leads to erroneous buffer handling with AR4 PduR API
   2012-03-30   1.21.01  Dth     ESCAN00056990: CanTp internal constants should be defined in CanTp.c
                         Dth     ESCAN00055796: Wrong naming of DET API Ids
                         Dth     ESCAN00057558: FC.CTS should only be sent if enough buffer is available (AR4 PduR API)
   2012-06-15   1.21.02  Dth     ESCAN00059163: Init Check in CanTp Main Function corrected
                         Dth     ESCAN00059137: transmit request for active Sdu not rejected with dynamic channel assignment
                         Dth     ESCAN00056982: implementation of findings from SilentBSW analysis
                         Dth     ESCAN00058822: after Flow Control, no STmin should be used
   2012-08-28   1.21.03  Dth     ESCAN00060308: Unexpected CF reception leads to erroneous behavior
                         Dth     ESCAN00060406: CanTp_Types.h file version corrected
                         Dth     ESCAN00060079: Support SF individual asynchron mode
   2012-10-04   1.22.00  Dth     ESCAN00060581: Implementation / traceability of SilentBSW countermeasures
                         Dth     ESCAN00061034: support for time measurement added
                         Dth     ESCAN00063804: Initialization of channels in vCanTp_InitFromLCfgPtr() corrected
                         Dth     ESCAN00063603: optional deactivation of error reporting if idle connection is canceled
   2013-02-18   1.23.00  Dth     ESCAN00064038: suppress FC.OVFL for buffer status BUFREQ_E_NOT_OK
                         Dth     ESCAN00064983: Block Size 0 conflicts with segmented buffers
   2013-04-08   1.24.00  Dth     ESCAN00065895: Compiler warning: variable 'pTxNsduCfg' set but not used
                         Dth     ESCAN00066463: Implementation of Low Level Routing extension
                         Dth     ESCAN00066858: switch CANTP_BS_ZERO_MULTI_BUFFER removed
   2013-07-11   1.25.00  Dth     ESCAN00067223: Compiler warning: large type was implicitly cast to small type
                         Dth     ESCAN00067701: Unreachable code in case of AR3 PduR API
                         Dth     ESCAN00068529: Compiler error: commas in comments removed
                         Dth     ESCAN00068731: Harmonization of version numbers
                         Dth     ESCAN00067672: Notification to DEM in case of a buffer overflow and fast routing use case
**************************************************************************************************/

#define CANTP_SOURCE

/******** global MISRA justifications ********/
/* PRQA S 0488 EOF */ /* MD_CANTP_MISRA_0488 */
/* PRQA S 0489 EOF */ /* MD_CANTP_MISRA_0489 */
/* PRQA S 0715 EOF */ /* MD_MSR_19.6         */
/* PRQA S 0841 EOF */ /* MD_MSR_19.6         */
/* PRQA S 0850 EOF */ /* MD_CANTP_MISRA_0850 */
/* PRQA S 3453 EOF */ /* MD_MSR_19.7         */
/* PRQA S 3458 EOF */ /* MD_MSR_19.4         */
/* PRQA S 5087 EOF */ /* MD_MSR_19.1         */
/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "CanTp.h"
#include "CanTp_Cfg.h"
#include "CanTp_Priv.h"
#if ( (!defined( V_SUPPRESS_EXTENDED_VERSION_CHECK )) || (CANTP_CRC_CHECK == STD_ON) )
# include "EcuM_Cbk.h"
#endif

/* critical sections handled by SchM */
#include "SchM_CanTp.h"

#include "PduR_CanTp.h"
#include "CanIf.h"


/* time measurement support */
#if (CANTP_AMD_RUNTIME_MEASUREMENT == STD_ON)
# include "AmdRtm.h"
#endif

/* low level routing support */
#if (CANTP_ENABLE_LLR_CALLOUTS == STD_ON)
# include CANTP_LLR_CBK_INCLUDE                         /* PRQA S 0832 */ /* MD_CANTP_MISRA_0832 */
#endif


/**************************************************************************************************
* Version Checks
**************************************************************************************************/
#if( TP_ASRTPCAN_VERSION != 0x0125u )
# error "The included header CanTp.h is incompatible with the CanTp.c version."
#endif
#if( TP_ASRTPCAN_RELEASE_VERSION != 0x00u )
# error "The included header CanTp.h is incompatible with the CanTp.c release version."
#endif

#if defined( CANTP_AUTOSARVERSION4 )
# if( CANTP_AR_RELEASE_MAJOR_VERSION != 0x04u )
#  error "The major version number of the AUTOSAR SWS is incompatible with the CanTp release version."
# endif
# if( CANTP_AR_RELEASE_MINOR_VERSION != 0x00u )
#  error "The minor version number of the AUTOSAR SWS is incompatible with the CanTp release version."
# endif
# if( CANTP_AR_RELEASE_REVISION_VERSION != 0x01u )
#  error "The revision number of the AUTOSAR SWS is incompatible with the CanTp release version."
# endif
#else
# if( CANTP_AR_MAJOR_VERSION != 0x02u )
#  error "The major version number of the AUTOSAR SWS is incompatible with the CanTp release version."
# endif
# if( CANTP_AR_MINOR_VERSION != 0x04u )
#  error "The minor version number of the AUTOSAR SWS is incompatible with the CanTp release version."
# endif
# if( CANTP_AR_PATCH_VERSION != 0x00u )
#  error "The patch version number of the AUTOSAR SWS is incompatible with the CanTp release version."
# endif
#endif

#if( CANTP_TYPES_VERSION != 0x0125u )
# error "The included header CanTp_Types.h is incompatible with the CanTp version."
#endif
#if( CANTP_TYPES_RELEASE_VERSION != 0x00u )
# error "The included header CanTp_Types.h is incompatible with the CanTp release version."
#endif

#if( CANTP_CBK_VERSION != 0x0125u )
# error "The included header CanTp_Cbk.h is incompatible with the CanTp version."
#endif
#if( CANTP_CBK_RELEASE_VERSION != 0x00u )
# error "The included header CanTp_Cbk.h is incompatible with the CanTp release version."
#endif

#if( CANTP_PRIV_VERSION != 0x0125u )
# error "The included header CanTp_Priv.h is incompatible with the CanTp version."
#endif
#if( CANTP_PRIV_RELEASE_VERSION != 0x00u )
# error "The included header CanTp_Priv.h is incompatible with the CanTp release version."
#endif

/**************************************************************************************************
* Version Checks for referenced components
**************************************************************************************************/
#if( CANTP_FF_PROVIDE_2_RXBUFFER_CALLS == STD_ON )
# if( CANTP_RX_FULL_BUFFER_PROVISION == STD_OFF )
#  error "The accelerated FF handling is only available if the Full Buffer Provision on Rx side is enabled."
# endif
# if( ((PDUR_SW_MAJOR_VERSION) <  0x03u) || \
     (((PDUR_SW_MAJOR_VERSION) == 0x03u) && ((PDUR_SW_MINOR_VERSION) < 0x11u)) )
#  error "If the CanTpFFProvide2RxBufferCalls attribute is enabled then the PduR version needs to be 3.11.00 or greater."
# endif
#endif

/**************************************************************************************************
* consistency check for preprocessor switches
**************************************************************************************************/
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# if !defined( CANTP_TASK_CYCLE )              || \
     !defined( CANTP_MAX_TXPDU_ID )            || \
     !defined( CANTP_MAX_RXPDU_ID )            || \
     !defined( CANTP_NUM_TXSDUS )              || \
     !defined( CANTP_NUM_RXSDUS )              || \
     !defined( CANTP_INSTANCE_ID )
#  error "Inconsistent common switches detected for the 'Single connection without postbuild' optimization !"
# endif

# if !defined( CANTP_RX__DL )                  || \
     !defined( CANTP_RX__NAR )                 || \
     !defined( CANTP_RX__NBR )                 || \
     !defined( CANTP_RX__NCR )                 || \
     !defined( CANTP_RX__RXNSDU_ID )           || \
     !defined( CANTP_RX__RXNPDU_ID )           || \
     !defined( CANTP_RX__TXFC_NPDU_ID )        || \
     !defined( CANTP_RX__PADDING_ACTIVATION )  || \
     !defined( CANTP_RX__TA_TYPE )             || \
     !defined( CANTP_RX__ADDRESSING_FORMAT )   || \
     !defined( CANTP_RX__MAX_PAYLOAD_LENGTH )  || \
     !defined( CANTP_RX__BS )                  || \
     !defined( CANTP_RX__STMIN )               || \
     !defined( CANTP_RX__WFTMAX )              || \
     !defined( CANTP_RX__RX_NTA )              || \
     !defined( CANTP_RX__TXFC_NTA )               \
     || \
     !defined( CANTP_TX__DL )                  || \
     !defined( CANTP_TX__NAS )                 || \
     !defined( CANTP_TX__NBS )                 || \
     !defined( CANTP_TX__NCS )                 || \
     !defined( CANTP_TX__TXNSDU_ID )           || \
     !defined( CANTP_TX__TXNPDU_ID )           || \
     !defined( CANTP_TX__RXFC_NPDU_ID )        || \
     !defined( CANTP_TX__PADDING_ACTIVATION )  || \
     !defined( CANTP_TX__TA_TYPE )             || \
     !defined( CANTP_TX__ADDRESSING_FORMAT )   || \
     !defined( CANTP_TX__MAX_PAYLOAD_LENGTH )  || \
     !defined( CANTP_TX__TX_NTA )              || \
     !defined( CANTP_TX__RXFC_NTA )
#  error "Inconsistent switches detected for the 'Single connection without postbuild' optimization !"
# endif

# if( CANTP_NUM_RXSDUS >= 2 )
#  if !defined( CANTP_RX__RXNSDU_ID_FUNC )          || \
      !defined( CANTP_RX__RXNPDU_ID_FUNC )          || \
      !defined( CANTP_RX__RX_NTA_FUNC )
#   error "Inconsistent switches detected for the 'Single connection without postbuild with functional reception' optimization !"
#  endif
# endif
#endif


/**************************************************************************************************
* Defines / Constants
**************************************************************************************************/
#define CANTP_START_SEC_CONST_32BIT
#include "MemMap.h"
#if !defined( V_SUPPRESS_EXTENDED_VERSION_CHECK )
/* PRQA S 3408 2 */ /* RULE 8.8: External linkage defined without previous definition due to generated code. */
CONST( uint32, CANTP_CONST ) TP_ASRTPCAN_LIB_SYMBOL = TP_ASRTPCAN_LIB_VERSION;
#endif
#define CANTP_STOP_SEC_CONST_32BIT
#include "MemMap.h"  /* MISRA RULE 87 VIOLATION: Only preprocessor statements and comments before '#include'. */

/**************************************************************************************************
* Macros
**************************************************************************************************/
/* application callbacks */
#define vCanTp_RxApplRxIndication(tpHdl,CanTpRxPduId,Result)                     (PduR_CanTpRxIndication(   (CanTpRxPduId),(Result)))
#define vCanTp_TxApplTxConfirmation(tpHdl,CanTpTxPduId,Result)                   (PduR_CanTpTxConfirmation( (CanTpTxPduId),(Result)))
#if ( CANTP_ENABLE_CHANGE_PARAM == STD_ON )
# define vCanTp_RxApplChangeParamConfirmation(CanTpRxPduId,Result)               (PduR_CanTpChangeParameterConfirmation( (CanTpRxPduId),(Result)))
#else
# define vCanTp_RxApplChangeParamConfirmation(CanTpRxPduId,Result)
#endif
#if defined( CANTP_ENABLE_PDUR_API40 )
# define vCanTp_RxApplStartOfReception(CanTpRxPduId, SduLength, RxBufSizePtr)          (PduR_CanTpStartOfReception((CanTpRxPduId), (SduLength), (RxBufSizePtr)))
# define vCanTp_RxApplCopyRxData(CanTpRxPduId, SduLength,               RxBufSizePtr)  (PduR_CanTpCopyRxData((CanTpRxPduId), (SduLength),           (RxBufSizePtr)))
# define vCanTp_TxApplCopyTxData(CanTpRxPduId, SduLength, RetryInfoPtr, RxBufSizePtr)  (PduR_CanTpCopyTxData((CanTpRxPduId), (SduLength), NULL_PTR, (RxBufSizePtr)))
#else
# define vCanTp_RxApplStartOfReception(CanTpRxPduId, SduLength, RxBufSizePtr)
# define vCanTp_RxApplCopyRxData(CanTpRxPduId, SduLength,               RxBufSizePtr)
# define vCanTp_TxApplCopyTxData(CanTpRxPduId, SduLength, RetryInfoPtr, RxBufSizePtr)
#endif
#define vCanTp_TxApplProvideTxBuffer(tpHdl,CanTpTxPduId,PduInfoPtr,MinLength)    (PduR_CanTpProvideTxBuffer((CanTpTxPduId),(PduInfoPtr),(MinLength)))
#define vCanTp_RxApplProvideRxBuffer(tpHdl,CanTpRxPduId,TpSduLength,PduInfoPtr)  (PduR_CanTpProvideRxBuffer((CanTpRxPduId),(TpSduLength),(PduInfoPtr)))

#if defined( CANIF_CANCEL_SUPPORT_API )
# define CANTP_CANIF_ENABLE_TC                  CANIF_CANCEL_SUPPORT_API        /* Vector extension is available */
#else
# if defined( CANIF_CANCEL_TRANSMIT_SUPPORT )
#  define CANTP_CANIF_ENABLE_TC                 CANIF_CANCEL_TRANSMIT_SUPPORT   /* AR4 switch is available       */
# endif
#endif
#if !defined( CANTP_CANIF_ENABLE_TC )
# define CANTP_CANIF_ENABLE_TC                  STD_OFF
#endif

#if( CANTP_CANIF_ENABLE_TC == STD_ON )
# define CANIF_CANCELTRANSMIT(PduId)                                             (CanIf_CancelTransmit(PduId))
#else
# define CANIF_CANCELTRANSMIT(PduId)
#endif

#if (CANTP_RX_SF_INDICATION == STD_ON)
# define vCanTp_RxApplRxSFIndication(CanTpRxPduId,Result)                        (Appl_CanTpRxSFIndication( (CanTpRxPduId),(Result)))
#else
# define vCanTp_RxApplRxSFIndication(CanTpRxPduId,Result)
#endif
#if (CANTP_RX_FF_INDICATION == STD_ON)
# define vCanTp_RxApplRxFFIndication(CanTpRxPduId,Result)                        (Appl_CanTpRxFFIndication( (CanTpRxPduId),(Result)))
#else
# define vCanTp_RxApplRxFFIndication(CanTpRxPduId,Result)
#endif
#if (CANTP_RX_CF_INDICATION == STD_ON)
# define vCanTp_RxApplRxCFIndication(CanTpRxPduId,Result)                        (Appl_CanTpRxCFIndication( (CanTpRxPduId),(Result)))
#else
# define vCanTp_RxApplRxCFIndication(CanTpRxPduId,Result)
#endif
#if (CANTP_TX_FRAME_CONFIRMATION == STD_ON)
# define vCanTp_TxApplTxFrameConfirmation(CanTpTxPduId,PduInfo)                  (Appl_CanTpTxFrameConfirmation((CanTpTxPduId), &(PduInfo)))
#else
# define vCanTp_TxApplTxFrameConfirmation(CanTpTxPduId,PduInfo)
#endif

/* ******************************************* */
/* AUTOSAR-compliant error reporting (DEM/DET) */
/* Assertions */
#if !defined( vCanTp_DetAssert )
# if(CANTP_DEV_ERROR_DETECT == STD_ON)
#  if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#   define vCanTp_DetAssert(check,apiId,errorId)          { if(!(check)) { (void)Det_ReportError(CANTP_MODULE_ID,CANTP_INSTANCE_ID,     (apiId),(errorId)); }}
#   define vCanTp_DetAssertReturn(check,apiId,errorId,rc) { if(!(check)) { (void)Det_ReportError(CANTP_MODULE_ID,CANTP_INSTANCE_ID,     (apiId),(errorId)); return(rc); }}
#   define vCanTp_DetAssertVReturn(check,apiId,errorId)   { if(!(check)) { (void)Det_ReportError(CANTP_MODULE_ID,CANTP_INSTANCE_ID,     (apiId),(errorId)); return; }}
#  else
#   define vCanTp_DetAssert(check,apiId,errorId)          { if(!(check)) { (void)Det_ReportError(CANTP_MODULE_ID,vCanTp_Cfg.InstanceId, (apiId),(errorId)); }}
#   define vCanTp_DetAssertReturn(check,apiId,errorId,rc) { if(!(check)) { (void)Det_ReportError(CANTP_MODULE_ID,vCanTp_Cfg.InstanceId, (apiId),(errorId)); return(rc); }}
#   define vCanTp_DetAssertVReturn(check,apiId,errorId)   { if(!(check)) { (void)Det_ReportError(CANTP_MODULE_ID,vCanTp_Cfg.InstanceId, (apiId),(errorId)); return; }}
#  endif
# else
#  define vCanTp_DetAssert(check,apiId,errorId)
#  define vCanTp_DetAssertReturn(check,apiId,errorId,rc)
#  define vCanTp_DetAssertVReturn(check,apiId,errorId)
# endif
#endif

/* Errors */
#if !defined( vCanTp_DetReportError )
# if(CANTP_DEV_ERROR_DETECT == STD_ON)
#  if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#   define vCanTp_DetReportError(apiId,errorId)   { (void)Det_ReportError(CANTP_MODULE_ID,CANTP_INSTANCE_ID,               (apiId),(errorId)); }
#  else
#    define vCanTp_DetReportError(apiId,errorId)  { (void)Det_ReportError(CANTP_MODULE_ID,vCanTp_Cfg.InstanceId,           (apiId),(errorId)); }
#  endif
# else
#  define vCanTp_DetReportError(apiId,errorId)
# endif
#endif

/* DEM */
#if !defined( vCanTp_DemSetEventStatus )
# if(CANTP_PROD_ERROR_DETECT == STD_ON)
#  define vCanTp_DemReportError( evId, evStatus)                                   { (void)Dem_ReportErrorStatus((evId), (evStatus)); }
#  define vCanTp_DemSetEventStatus(check, evId, evStatus)           { if(!(check)) { (void)Dem_ReportErrorStatus((evId), (evStatus)); return; }}
#  define vCanTp_DemSetEventStatusReturn(check, evId, evStatus, ret){ if(!(check)) { (void)Dem_ReportErrorStatus((evId), (evStatus)); return (ret); }}
#  define vCanTp_DemSetEventStatusVReturn(check, evId, evStatus)    { if(!(check)) { (void)Dem_ReportErrorStatus((evId), (evStatus)); return; }}
# else
#  define vCanTp_DemReportError( evId, evStatus)
#  define vCanTp_DemSetEventStatus(check, evId, evStatus)
#  define vCanTp_DemSetEventStatusReturn(check, evId, evStatus, ret)
#  define vCanTp_DemSetEventStatusVReturn(check, evId, evStatus)
# endif
#endif

#if(CANTP_E_COMM_REPORT_DEM == STD_ON)
# if (CANTP_SUPPRESS_PREPASS_INDICATION == STD_ON)                                                  /* CANTP228: RfC 40397 - remove of DEM notification in case of successful transfer            */
#  define vCanTp_DemReportErrorPass(EID)  
# else
#  define vCanTp_DemReportErrorPass(EID)    vCanTp_DemReportError(EID, DEM_EVENT_STATUS_PREPASSED)  /* CanTp228: if everything is ok then call DEM (CanTp_E_(Tx_)Com, DEM_EVENT_STATUS_PREPASSED) */
# endif
#else /* CANTP_E_COMM_REPORT_DEM */
# define vCanTp_DemReportErrorPass(EID)                                                             /* Do not report PrePass to DET [vCanTp_DetReportError(CanTp_TxConfirmation_SId, CanTp_E_Com)] */
#endif /* CANTP_E_COMM_REPORT_DEM */

#if(CANTP_E_COMM_REPORT_DEM == STD_ON)
# define vCanTp_DemReportErrorTxFail(EID)   vCanTp_DemReportError(EID, DEM_EVENT_STATUS_PREFAILED)  /* CanTp229: if anything failed then call DEM (CanTp_E_(Tx_)Com, DEM_EVENT_STATUS_PREFAILED) */
#else /* CANTP_E_COMM_REPORT_DEM */
# define vCanTp_DemReportErrorTxFail(EID)   vCanTp_DetReportError(CanTp_TxConfirmation_SId, EID)
#endif /* CANTP_E_COMM_REPORT_DEM */

#if(CANTP_E_COMM_REPORT_DEM == STD_ON)
# define vCanTp_DemReportErrorRxFail(EID)   vCanTp_DemReportError(EID, DEM_EVENT_STATUS_PREFAILED)  /* CanTp229: if anything failed then call DEM (CanTp_E_(Tx_)Com, DEM_EVENT_STATUS_PREFAILED) */
#else /* CANTP_E_COMM_REPORT_DEM */
# define vCanTp_DemReportErrorRxFail(EID)   vCanTp_DetReportError(CanTp_RxIndication_SId, EID)
#endif /* CANTP_E_COMM_REPORT_DEM */


#if(CANTP_SUPPRESS_CANCEL_ERROR_WHEN_IDLE == STD_OFF)
# if(CANTP_OPER_NOT_SUPPORTED_REPORT_DEM == STD_ON)
#  define vCanTp_DemReportErrorCancelNotSupported(ApiId)        vCanTp_DemReportError(CanTp_E_Oper_Not_Supported, DEM_EVENT_STATUS_PREFAILED)
# else
#  define vCanTp_DemReportErrorCancelNotSupported(ApiId)        vCanTp_DetReportError((ApiId), CanTp_E_Oper_Not_Supported)
# endif
#else
# define vCanTp_DemReportErrorCancelNotSupported(ApiId)         /* report nothing */
#endif


/* *********************************************** */
/* Extended, non AUTOSAR-compliant error reporting */
/* Assertions */
#if !defined( vCanTp_Assert )
# if(CANTP_HAVE_EXT_DEV_ERROR_DETECT == STD_ON)
#  if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#   define vCanTp_Assert(check,apiId,errorId,errorParam)           { if(!(check)) { vCanTp_ReportError(CANTP_MODULE_ID,CANTP_INSTANCE_ID,(apiId),(errorId),(errorParam)); }}
#   define vCanTp_AssertReturn(check,apiId,errorId,errorParam,rc)  { if(!(check)) { vCanTp_ReportError(CANTP_MODULE_ID,CANTP_INSTANCE_ID,(apiId),(errorId),(errorParam)); return(rc); }}
#   define vCanTp_AssertVReturn(check,apiId,errorId,errorParam)    { if(!(check)) { vCanTp_ReportError(CANTP_MODULE_ID,CANTP_INSTANCE_ID,(apiId),(errorId),(errorParam)); }}
#   define vCanTp_AssertAlways(apiId,errorId,errorParam,rc)                       { vCanTp_ReportError(CANTP_MODULE_ID,CANTP_INSTANCE_ID,(apiId),(errorId),(errorParam)); return(rc); }
#   define vCanTp_AssertVAlways(apiId,errorId,errorParam)                         { vCanTp_ReportError(CANTP_MODULE_ID,CANTP_INSTANCE_ID,(apiId),(errorId),(errorParam)); }
#  else
#   define vCanTp_Assert(check,apiId,errorId,errorParam)           { if(!(check)) { vCanTp_ReportError(CANTP_MODULE_ID,vCanTp_Cfg.InstanceId,(apiId),(errorId),(errorParam)); }}
#   define vCanTp_AssertReturn(check,apiId,errorId,errorParam,rc)  { if(!(check)) { vCanTp_ReportError(CANTP_MODULE_ID,vCanTp_Cfg.InstanceId,(apiId),(errorId),(errorParam)); return(rc); }}
#   define vCanTp_AssertVReturn(check,apiId,errorId,errorParam)    { if(!(check)) { vCanTp_ReportError(CANTP_MODULE_ID,vCanTp_Cfg.InstanceId,(apiId),(errorId),(errorParam)); }}
#   define vCanTp_AssertAlways(apiId,errorId,errorParam,rc)                       { vCanTp_ReportError(CANTP_MODULE_ID,vCanTp_Cfg.InstanceId,(apiId),(errorId),(errorParam)); return(rc); }
#   define vCanTp_AssertVAlways(apiId,errorId,errorParam)                         { vCanTp_ReportError(CANTP_MODULE_ID,vCanTp_Cfg.InstanceId,(apiId),(errorId),(errorParam)); }
#  endif
# else
#  define vCanTp_Assert(check,apiId,errorId,errorParam)
#  define vCanTp_AssertReturn(check,apiId,errorId,errorParam,rc)
#  define vCanTp_AssertVReturn(check,apiId,errorId,errorParam)
#  define vCanTp_AssertAlways(apiId,errorId,errorParam,rc)
#  define vCanTp_AssertVAlways(apiId,errorId,errorParam)
# endif
#endif

/* Errors */
#if !defined( vCanTp_Error )
# if(CANTP_HAVE_EXT_DEV_ERROR_DETECT == STD_ON)
#  if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#   define vCanTp_Error(apiId,errorId,errorParam)  {vCanTp_ReportError(CANTP_MODULE_ID,CANTP_INSTANCE_ID,    (apiId),(errorId),(errorParam));}
#  else
#   define vCanTp_Error(apiId,errorId,errorParam) {vCanTp_ReportError(CANTP_MODULE_ID,vCanTp_Cfg.InstanceId,(apiId),(errorId),(errorParam));}
#  endif
# else
#  define vCanTp_Error(apiId,errorId,errorParam)
# endif
#endif

/* Format calculation */
#if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
/* multiple addressing */
# define FORMAT_OFFSET                          fmtOffset

# if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#  if( CANTP_RX__MAX_PAYLOAD_LENGTH == CANTP_MAX_PAYLOAD_LENGTH_NA )
#   define vCanTp_rxGetAdrFmt(elm)               ((uint8)0)
#  else
#   define vCanTp_rxGetAdrFmt(elm)               ((uint8)1)
#  endif
#  if( CANTP_NUM_RXSDUS <= 1 )
#  else
#   if( CANTP_RX__MAX_PAYLOAD_LENGTH != CANTP_RX__MAX_PAYLOAD_LENGTH_FUNC )
#    error "When using Single Connection Pre-Compile then the physical and the functional Rx-NSdu must be configured with the same addressing type."
#   endif
#  endif
#  if( CANTP_TX__MAX_PAYLOAD_LENGTH == CANTP_MAX_PAYLOAD_LENGTH_NA )
#   define vCanTp_txGetAdrFmt(elm)               ((uint8)0)
#  else
#   define vCanTp_txGetAdrFmt(elm)               ((uint8)1)
#  endif

# elif( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#  if( CANTP_NUM_RX_CHANNELS <= 1 )
#   define vCanTp_rxGetAdrFmt(elm)               ((vCanTp_PBCfg_RX__MAX_PLEN(0) == CANTP_MAX_PAYLOAD_LENGTH_NA) ? ((uint8)0) : ((uint8)1))
#   define vCanTp_txGetAdrFmt(elm)               ((vCanTp_PBCfg_TX__MAX_PLEN(0) == CANTP_MAX_PAYLOAD_LENGTH_NA) ? ((uint8)0) : ((uint8)1))
#  else
     /* "When using Single Connection then the physical and the functional Rx-NSdu must be configured with the same addressing type." */
#   define vCanTp_rxGetAdrFmt(elm)               ((vCanTp_PBCfg_RX__MAX_PLEN(elm) == CANTP_MAX_PAYLOAD_LENGTH_NA) ? ((uint8)0) : ((uint8)1))
#   define vCanTp_txGetAdrFmt(elm)               ((vCanTp_PBCfg_TX__MAX_PLEN(elm) == CANTP_MAX_PAYLOAD_LENGTH_NA) ? ((uint8)0) : ((uint8)1))
#  endif
# else /* CANTP_SINGLE_CONN_OPTIMIZED == STD_OFF */
#  define vCanTp_rxGetAdrFmt(elm)               ((vCanTp_PBCfg_RX__MAX_PLEN(elm) == CANTP_MAX_PAYLOAD_LENGTH_NA) ? ((uint8)0) : ((uint8)1))
#  define vCanTp_txGetAdrFmt(elm)               ((vCanTp_PBCfg_TX__MAX_PLEN(elm) == CANTP_MAX_PAYLOAD_LENGTH_NA) ? ((uint8)0) : ((uint8)1))
# endif /* CANTP_SINGLE_CONN_OPTIMIZED */

#elif ( (CANTP_STANDARD_ADDRESSING == STD_ON) && ((CANTP_EXTENDED_ADDRESSING == STD_OFF) && (CANTP_MIXED11_ADDRESSING == STD_OFF)) )
/* standard addressing */
# define FORMAT_OFFSET                          ((uint8)0)
# define vCanTp_rxGetAdrFmt(elm)                ((uint8)0)
# define vCanTp_txGetAdrFmt(elm)                ((uint8)0)
#elif ( (CANTP_STANDARD_ADDRESSING == STD_OFF) && ((CANTP_EXTENDED_ADDRESSING == STD_ON) || (CANTP_MIXED11_ADDRESSING == STD_ON)) )
/* extended and/or mixed11 addressing */
# define FORMAT_OFFSET                          ((uint8)1)
# define vCanTp_rxGetAdrFmt(elm)                ((uint8)1)
# define vCanTp_txGetAdrFmt(elm)                ((uint8)1)
#endif

/* Length calculation */
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# define vCanTp_rxGetPayloadLenFF(elm)         ( (uint8) CANTP_RX__MAX_PAYLOAD_LENGTH-1 )
# define vCanTp_rxGetPayloadLenCF(elm)         ( (uint8) CANTP_RX__MAX_PAYLOAD_LENGTH   )
# define vCanTp_rxGetPayloadLenSF(elm)         ( (uint8) CANTP_RX__MAX_PAYLOAD_LENGTH   )
# define vCanTp_txGetPayloadLenFF(elm)         ( (uint8) CANTP_TX__MAX_PAYLOAD_LENGTH-1 )
# define vCanTp_txGetPayloadLenCF(elm)         ( (uint8) CANTP_TX__MAX_PAYLOAD_LENGTH   )
# define vCanTp_txGetPayloadLenSF(elm)         ( (uint8) CANTP_TX__MAX_PAYLOAD_LENGTH   )
# define vCanTp_rxGetPayloadLen(elm,frmType)   ( ((frmType) == cCanTp_FF) ? (uint8)(CANTP_RX__MAX_PAYLOAD_LENGTH-1) : (uint8)(CANTP_RX__MAX_PAYLOAD_LENGTH) )
# define vCanTp_txGetPayloadLen(elm,frmType)   ( ((frmType) == cCanTp_FF) ? (uint8)(CANTP_TX__MAX_PAYLOAD_LENGTH-1) : (uint8)(CANTP_TX__MAX_PAYLOAD_LENGTH) )
#else
# define vCanTp_rxGetPayloadLenFF(elm)        ( (uint8) (vCanTp_PBCfg_RX__MAX_PLEN(elm)-1) )
# define vCanTp_rxGetPayloadLenCF(elm)        ( (uint8) (vCanTp_PBCfg_RX__MAX_PLEN(elm)) )
# define vCanTp_rxGetPayloadLenSF(elm)        ( (uint8) (vCanTp_PBCfg_RX__MAX_PLEN(elm)) )
# define vCanTp_txGetPayloadLenFF(elm)        ( (uint8) (vCanTp_PBCfg_TX__MAX_PLEN(elm)-1) )
# define vCanTp_txGetPayloadLenCF(elm)        ( (uint8) (vCanTp_PBCfg_TX__MAX_PLEN(elm)) )
# define vCanTp_txGetPayloadLenSF(elm)        ( (uint8) (vCanTp_PBCfg_TX__MAX_PLEN(elm)) )
# define vCanTp_rxGetPayloadLen(elm,frmType)  ( ((frmType) == cCanTp_FF) ? (uint8)(vCanTp_PBCfg_RX__MAX_PLEN(elm)-1) : (uint8)(vCanTp_PBCfg_RX__MAX_PLEN(elm)) )
# define vCanTp_txGetPayloadLen(elm,frmType)  ( ((frmType) == cCanTp_FF) ? (uint8)(vCanTp_PBCfg_TX__MAX_PLEN(elm)-1) : (uint8)(vCanTp_PBCfg_TX__MAX_PLEN(elm)) )
#endif


/* Internal data and macro definitions */
/* ----------------------------------- */
/* vCanTp_FrameType */
#define cCanTp_SF                 0
#define cCanTp_FF                 1
#define cCanTp_CF                 2
#define cCanTp_FC                 3
#define cCanTp_InvalidFrame       4
#define cCanTp_NumberOfFrameTypes 5

/* CanTp_StatusType */
#define cCanTp_Uninitialized      CANTP_OFF
#define cCanTp_Initialized        CANTP_ON
#define cCanTp_Shutdown           cCanTp_Uninitialized

#define cCanTp_TxOk               1
#define cCanTp_TxNotOk            2

/* vCanTp_TxStateType */
#define cTxState_Idle                     0  /* must be zero due to optimization */
#define cTxState_WaitFC                   1
#define cTxState_WaitForTpTxCF            2
#define cTxState_WaitForTxBuffer          3
#define cTxState_WaitForSForFFConfIsr     4
#define cTxState_WaitForCFConfIsr         5

/* vCanTp_RxStateType */
#define cRxState_Idle                     0  /* must be zero due to optimization */
#define cRxState_WaitCF                   1
#define cRxState_WaitForFCConfIsr         2
#define cRxState_WaitForRxBuffer          3
#define cRxState_WaitForFCWaitConfIsr     4
#define cRxState_WaitForFCWait            5
#define cRxState_WaitForFCOverConfIsr     6

#define cCanTp_FrameLength                8
/* FC byte positions */
#define cCanTp_FmtOffsetFrameType         0
#define cCanTp_FmtOffsetFs                0
#define cCanTp_FmtOffsetBs                1
#define cCanTp_FmtOffsetStmin             2

/* Constants for frame assembly */
#define cCanTp_SF_OFFSET                  1
#define cCanTp_FF_OFFSET                  2
#define cCanTp_CF_OFFSET                  1
#define cCanTp_FC_OFFSET                  0
#define cCanTp_TPCIMaxLength              3
#define cCanTp_LengthFC                   3  /* FS-BS-STMIN    */
#define cCanTp_maxLengthFC                4  /* TA (ext addr.) */

/* Address-mode specific offsets */
#define cCanTp_TPCIOffsetNA        0
#define cCanTp_TPCIOffsetEA        1

/* Masks for frame parsing */
#define cCanTp_DLMaskSF            0x0f
#define cCanTp_DLMaskFF            0x0f
#define cCanTp_FrameTypeMask       0xf0
#define cCanTp_FSMask              0x0f

/* Helper to initiate a status change during the next CanTp-Task-execution */
#define cCanTp_Queued             1
#define cCanTp_NotQueued          0  /* must be zero due to optimization */

/* Other helpers */
#define cCanTp_CFNoError          0
#define cCanTp_CFError            1
#define cCanTp_SNFirstCF          1u
#define cCanTp_SNMaxCF            0u
#define cCanTp_MaxSNError         0x1e

/* Regarding NotifResultType: Currently values in the range of 0x79 are invalid.
   In AUTOSARs' future further return codes may be specified for other communication systems. */
#define cCanTp_NoResultNotification  0x79
#define cCanTp_NoAdminReset          0x7a
#define cCanTp_Initialize            0x7f

/* Data assemble/disassemble macro */
#define vCanTp_Make16Bit(hiByte,loByte) ((uint16)((((uint16)(hiByte))<<8) | ((uint16)(loByte))))


/**************************************************************************************************
* Typedef and Struct definitions
**************************************************************************************************/
typedef          P2VAR(vCanTp_TxStateType, AUTOMATIC, CANTP_APPL_DATA)  vCanTp_TpTxStatePtrType;
typedef          P2VAR(vCanTp_RxStateType, AUTOMATIC, CANTP_APPL_DATA)  vCanTp_TpRxStatePtrType;
typedef volatile P2VAR(PduIdType,          AUTOMATIC, CANTP_VAR_NOINIT) vCanTp_VolatileTpTxHdlMapPtrType;
typedef volatile P2VAR(PduIdType,          AUTOMATIC, CANTP_VAR_NOINIT) vCanTp_VolatileTpRxHdlMapPtrType;


/**************************************************************************************************
* Data definitions
**************************************************************************************************/
#if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
# define CANTP_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h"  /* MISRA RULE 87 VIOLATION: Only preprocessor statements and comments before '#include'. */
/* PRQA S 3408 2 */ /* RULE 8.8: External linkage defined without previous definition due to generated code. */
VAR(PduIdType, CANTP_VAR_NOINIT) vCanTp_NumRxChannelsAvail;
VAR(PduIdType, CANTP_VAR_NOINIT) vCanTp_NumTxChannelsAvail;
# define CANTP_STOP_SEC_VAR_NOINIT_8BIT
# include "MemMap.h"  /* MISRA RULE 87 VIOLATION: Only preprocessor statements and comments before '#include'. */
#endif

#if ( CANTP_ENABLE_CHANGE_PARAM == STD_ON )
# define CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"  /* MISRA RULE 87 VIOLATION: Only preprocessor statements and comments before '#include'. */
/* PRQA S 3408 2 */ /* RULE 8.8: External linkage defined without previous definition due to generated code. */
VAR(PduIdType,       CANTP_VAR_NOINIT) vCanTp_changeParamConfId;
VAR(NotifResultType, CANTP_VAR_NOINIT) vCanTp_changeParamConfResult;
# define CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"  /* MISRA RULE 87 VIOLATION: Only preprocessor statements and comments before '#include'. */
#endif /* CANTP_ENABLE_CHANGE_PARAM */

# if( CANTP_TX_SERIALIZE == STD_ON )
# define CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"  /* MISRA RULE 87 VIOLATION: Only preprocessor statements and comments before '#include'. */
/* PRQA S 3408 5 */ /* RULE 8.8: External linkage defined without previous definition due to generated code. */
VAR(vCanTp_TxSemaphoreType, CANTP_VAR_NOINIT) vCanTp_TxSemaphore;
# if ( CANTP_TX_SINGLE_SERIALIZE == STD_ON )
# else
VAR(vCanTp_TxConflictType,   CANTP_VAR_NOINIT) vCanTp_TxConflict;
# endif
# define CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"  /* MISRA RULE 87 VIOLATION: Only preprocessor statements and comments before '#include'. */
#endif

/**************************************************************************************************
* Prototypes of extern functions
**************************************************************************************************/

/**************************************************************************************************
* Prototypes of local functions
**************************************************************************************************/

#define CANTP_START_SEC_CODE
#include "MemMap.h"  /* MISRA RULE 87 VIOLATION: Only preprocessor statements and comments before '#include'. */

#if( CANTP_RXTX_MAINFUNCTION_API == STD_ON )
#else
STATIC FUNC(void,  CANTP_CODE)   CanTp_MainFunctionRx(void);
STATIC FUNC(void,  CANTP_CODE)   CanTp_MainFunctionTx(void);
#endif

STATIC FUNC(void,  CANTP_CODE)   vCanTp_InitFromLCfgPtr(void);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_RxInitState(CANTP_HDL_PTYPE_ONLY);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_RxInit(CANTP_HDL_PVAL_FIRST  NotifResultType notifyCode, uint8 errCode);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_TxInitState(CANTP_HDL_PTYPE_ONLY);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_TxInit(CANTP_HDL_PVAL_FIRST  NotifResultType notifyCode);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_RxStateTask(CANTP_HDL_PTYPE_ONLY);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_TxStateTask(CANTP_HDL_PTYPE_ONLY);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_RxRetrieveApplRxBuffer(CANTP_HDL_CPTYPE_ONLY);
STATIC FUNC(BufReq_ReturnType,   CANTP_CODE) vCanTp_TxRetrieveApplTxBuffer(CANTP_HDL_CPTYPE_ONLY);
STATIC FUNC(vCanTp_TxReturnType, CANTP_CODE) vCanTp_CanIfTransmit(CANTP_HDL_PVAL_FIRST
                                                                  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) TPCI, 
                                                                  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) payload, 
                                                                  vCanTp_FrameType FrameType);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_CanIfRxIndication(CANTP_HDL_PVAL_FIRST  uint8 direction, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_CanIfTxConfirmation(CANTP_HDL_PVAL_FIRST vCanTp_operatingType dir);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_TxCFTxConfirmation(CANTP_HDL_PTYPE_ONLY);
STATIC FUNC(uint8, CANTP_CODE)   vCanTp_TxGetStminTimerFromStminValue(uint8 tpSTminValue);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_MemCpy(P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest, P2CONST(uint8, AUTOMATIC, CANTP_APPL_DATA) pSrc, uint16 nCnt);
STATIC FUNC(void,  CANTP_CODE)   vCanTp_MemSet(P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest, uint8 val, uint16 nCnt);
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
STATIC FUNC(PduIdType, CANTP_CODE) vCanTp_RxGetResource(CANTP_HDL_PTYPE_ONLY);
STATIC FUNC(PduIdType, CANTP_CODE) vCanTp_TxGetResource(CANTP_HDL_PTYPE_ONLY);
# endif

/**************************************************************************************************
*  Implementation
**************************************************************************************************/


/**************************************************************************************************
   Function name    : CanTp_TxInitState
   ------------------------------------------------------------------------------------------------
   Description      : Initialize the transmit channel state structure specified by parameter
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself
   ------------------------------------------------------------------------------------------------
   Parameter        : tpHdl,
   ------------------------------------------------------------------------------------------------
   Returncode       : None
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void,  CANTP_CODE)   vCanTp_TxInitState(CANTP_HDL_PVAL_ONLY)
{
  vCanTp_TpTxStatePtrType pTpTxState;

#if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
# if( CANTP_NUM_RX_CHANNELS >= 2)
#  if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)tpHdl; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
#  endif
# endif
#endif
  
  pTpTxState = &vCanTp_TxState[TPTXHDL];

  /* tpHdl is reinitialized completely */
  /* PRQA S 310 2 */ /* MD_CANTP_MISRA_310 */
  vCanTp_MemSet((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) pTpTxState, 0x00u, sizeof(vCanTp_TxStateType));

  pTpTxState->channel   = CANTP_INVALID_HDL;
  pTpTxState->frameType = cCanTp_InvalidFrame;
  pTpTxState->bufState  = BUFREQ_OK;
}
/* vCanTp_TxInitState */


/**************************************************************************************************
   Function name    : CanTp_RxInitState
   ------------------------------------------------------------------------------------------------
   Description      : Initialize the receive channel state structure specified by parameter
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself
   ------------------------------------------------------------------------------------------------
   Parameter        : tpHdl,
   ------------------------------------------------------------------------------------------------
   Returncode       : None
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void,  CANTP_CODE) vCanTp_RxInitState(CANTP_HDL_PVAL_ONLY)
{
  vCanTp_TpRxStatePtrType pTpRxState;

  pTpRxState = &vCanTp_RxState[TPRXHDL];

  /* tpHdl is reinitialized completely */
  /* PRQA S 310 2 */ /* MD_CANTP_MISRA_310 */
  vCanTp_MemSet((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))pTpRxState, 0x00u, sizeof(vCanTp_RxStateType));

  pTpRxState->channel   = CANTP_INVALID_HDL;
  pTpRxState->frameType = cCanTp_InvalidFrame;
  pTpRxState->bufState  = BUFREQ_OK;
}
/* vCanTp_RxInitState */

/**************************************************************************************************
   Function name    : CanTpTxInit
   ------------------------------------------------------------------------------------------------
   Description      : Initialize the transmit Channel specified by parameter
                      Call TxConfirmation of application if valid notify-code is given
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself
   ------------------------------------------------------------------------------------------------
   Parameter        : uint8 tpHdl,
                      NotifResultType notifyCode to be given to application
   ------------------------------------------------------------------------------------------------
   Returncode       : None
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void,  CANTP_CODE)   vCanTp_TxInit(CANTP_HDL_PVAL_FIRST  NotifResultType notifyCode)
{
  vCanTp_TpTxStatePtrType pTpTxState;
  uint8 indicationPduR = 0;
#if defined( CANTP_ENABLE_SINGLE_CONN )
#else
# if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)tpHdl; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
# endif
#endif

  /* SilentBSW: ensure that handle is valid (even if DET is disabled) */
  if (TPTXHDL >= CanTpGET_NumCanTpTxSduId)  /* SilentBSW: SBSW_AsrTpCan_019 */  /* PRQA S 3325 */ /* MD_CANTP_SBSW_CHECK */  /* PRQA S 3201 4 */ /* MD_CANTP_SBSW_CHECK */
  {
    vCanTp_DetReportError(CanTp_TxInit_Sid, CANTP_E_INVALID_TX_ID)
    return;
  }

#if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
if(vCanTp_txHdlMap[tpHdl] != CANTP_INVALID_HDL)
#endif
  {
    pTpTxState = &vCanTp_TxState[TP_TX_HDL(tpHdl)]; 
    if((pTpTxState->ChannelState != cTxState_Idle) &&
       (notifyCode != (NotifResultType)cCanTp_NoResultNotification))
    { 
      indicationPduR = 1;
#if( (CANTP_PROD_ERROR_DETECT == STD_ON) || (CANTP_E_COMM_REPORT_DEM == STD_ON) )
      /* PRQA S 3200 QAC_L1  */ /* RULE 16.10: No usage of return value intended. */
      if(notifyCode == NTFRSLT_OK)
      { 
        vCanTp_DemReportErrorPass(CanTp_E_Tx_Com)  /* CanTp228: if everything is ok then call DEM (CanTp_E_(Tx_)Com, DEM_EVENT_STATUS_PREPASSED) */
      }
      else
      { 
        vCanTp_DemReportErrorTxFail(CanTp_E_Tx_Com) /* CanTp229: if anything failed then call DEM (CanTp_E_(Tx_)Com, DEM_EVENT_STATUS_PREFAILED) */
      }
  /* PRQA  L:QAC_L1 */
#endif /* CANTP_PROD_ERROR_DETECT || CANTP_E_COMM_REPORT_DEM */
    }

    if ( (pTpTxState->ChannelState == cTxState_WaitForSForFFConfIsr) ||
         (pTpTxState->ChannelState == cTxState_WaitForCFConfIsr) )
    {
      if (pTpTxState->queued == 0)
      {
        /* no transmission request pending, only waiting for confirmation; release semaphore and cancel transmission */
# if( CANTP_TX_SERIALIZE == STD_ON )
        vCanTp_TxSemaphore.hdl = CANTP_INVALID_HDL;
#endif
        CANIF_CANCELTRANSMIT(vCanTp_PBCfg(vCanTp_TxNsduCfg, TPTXHDL, CANTP_TXNPDU_ID, CANTP_TX__TXNPDU_ID));
      }
    }


    /* tpHdl is reinitialized completely */
#if defined( CANTP_ENABLE_SINGLE_CONN )
    vCanTp_TxInitState();
#else
    vCanTp_TxInitState(TP_TX_HDL(tpHdl));
#endif

#if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
    if(vCanTp_txHdlMap[tpHdl] != CANTP_INVALID_HDL)
    {
      vCanTp_txHdlMap[tpHdl] = CANTP_INVALID_HDL;
      vCanTp_NumTxChannelsAvail++;
    }
#endif

    if(indicationPduR > 0)
    {
#if ( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON )
      vCanTp_TxApplTxConfirmation(TPTXHDL, vCanTp_PBCfg(vCanTp_TxNsduCfg, TPTXHDL, CANTP_REMAP_TXNSDU_ID, CANTP_TX__REMAP_TXNSDU_ID), notifyCode);
#else
      vCanTp_TxApplTxConfirmation(TPTXHDL, vCanTp_PBCfg(vCanTp_TxNsduCfg, TPTXHDL, CANTP_TXNSDU_ID, CANTP_TX__TXNSDU_ID), notifyCode);
#endif
    }

  }
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */
/* vCanTp_TxInit */


/**************************************************************************************************
   Function name    : CanTpRxInit
   ------------------------------------------------------------------------------------------------
   Description      : Initialize the receive Channel specified by parameter
                      Call RxIndication of application if valid notify-code is given
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself
   ------------------------------------------------------------------------------------------------
   Parameter        : uint8 tpHdl,
                      NotifResultType notifyCode to be given to application
   ------------------------------------------------------------------------------------------------
   Returncode       : None
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void,  CANTP_CODE)   vCanTp_RxInit(CANTP_HDL_PVAL_FIRST  NotifResultType notifyCode,  uint8 errCode)
{
  vCanTp_TpRxStatePtrType pTpRxState;
  uint8 indicationPduR = 0;

  /* SilentBSW: ensure that handle is valid (even if DET is disabled) */
  if (TPRXHDL >= CanTpGET_NumCanTpRxSduId)  /* SilentBSW: SBSW_AsrTpCan_020 */  /* PRQA S 3325 */ /* MD_CANTP_SBSW_CHECK */  /* PRQA S 3201 4 */ /* MD_CANTP_SBSW_CHECK */
  {
    vCanTp_DetReportError(CanTp_RxInit_Sid, CANTP_E_INVALID_RX_ID)
    return;
  }

#if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
  if(vCanTp_rxHdlMap[tpHdl] != CANTP_INVALID_HDL)
#endif
  {
    pTpRxState = &vCanTp_RxState[TP_RX_HDL(tpHdl)];
    if((pTpRxState->ChannelState != cRxState_Idle) && 
       (notifyCode != (NotifResultType)cCanTp_NoResultNotification))
    { 
#if ( CANTP_STRICT_RX_CALL_SEQ == STD_ON )
      if(pTpRxState->ApplState == CANTP_APPL_INFORMED)
#endif
      { /* Indicate to application */
        indicationPduR = 1;
      }

#if( (CANTP_PROD_ERROR_DETECT == STD_ON) || (CANTP_E_COMM_REPORT_DEM == STD_ON) )
      /* PRQA S 3200 QAC_L1  */ /* RULE 16.10: No usage of return value intended. */
      if(notifyCode == NTFRSLT_OK)
      {
        vCanTp_DemReportErrorPass(CanTp_E_Rx_Com)  /* CanTp295: if everything is ok then call DEM (CanTp_E_(Rx_)Com, DEM_EVENT_STATUS_PREPASSED) */
      }
      else
      {
        vCanTp_DemReportErrorRxFail(CanTp_E_Rx_Com)  /* CanTp229: if anything failed then call DEM (CanTp_E_(Rx_)Com, DEM_EVENT_STATUS_PREFAILED) */
      }
  /* PRQA  L:QAC_L1  */
#endif /* CANTP_PROD_ERROR_DETECT || CANTP_E_COMM_REPORT_DEM */
    }

    if( (pTpRxState->ChannelState == cRxState_WaitForFCConfIsr) ||
        (pTpRxState->ChannelState == cRxState_WaitForFCOverConfIsr) ||
        (pTpRxState->ChannelState == cRxState_WaitForFCWaitConfIsr) )
    {
      if (pTpRxState->queued == 0)
      {
        /* no FC transmission request pending, only waiting for confirmation; release semaphore and cancel transmission */
#if( CANTP_TX_SERIALIZE == STD_ON )
        vCanTp_TxSemaphore.hdl = CANTP_INVALID_HDL;
#endif
        CANIF_CANCELTRANSMIT(vCanTp_PBCfg(vCanTp_RxNsduCfg, TPRXHDL, CANTP_TXFC_NPDU_ID, CANTP_RX__TXFC_NPDU_ID));
      }
    }

    /* tpHdl is reinitialized completely */
#if defined( CANTP_ENABLE_SINGLE_CONN )
    vCanTp_RxInitState();
#else
    vCanTp_RxInitState(TP_RX_HDL(tpHdl));
#endif

#if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
    if(errCode != cCanTp_NoAdminReset)
    {
      vCanTp_rxHdlMap[tpHdl] = CANTP_INVALID_HDL;
      vCanTp_NumRxChannelsAvail++;
    }
#else
# if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
    (void)errCode; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
# endif
#endif

    if(indicationPduR > 0)
    {
#if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
      vCanTp_RxApplRxIndication(TPRXHDL, vCanTp_RxPBCfg(vCanTp_RxNsduCfg, TPRXHDL, CANTP_REMAP_RXNSDU_ID, CANTP_RX__REMAP_RXNSDU_ID), notifyCode);
#else
      vCanTp_RxApplRxIndication(TPRXHDL, vCanTp_RxPBCfg(vCanTp_RxNsduCfg, TPRXHDL, CANTP_RXNSDU_ID, CANTP_RX__RXNSDU_ID), notifyCode);
#endif
    }

  }
} /* PRQA S 2006 */ /* MD_MSR_14.7 */
/* vCanTp_RxInit */


#if( (CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON) && (CANTP_ENABLE_WRAP_TRANSMIT == STD_ON) )
/**************************************************************************************************
   Function name    : CanTpWrapper_Transmit
   ------------------------------------------------------------------------------------------------
   Description      : Before calling CanTp_Transmit de-wrap the user defined NSDU-ID.
   ------------------------------------------------------------------------------------------------
   Called by        : Pdu-Router or other application
   ------------------------------------------------------------------------------------------------
   Parameter        : PduIdType     CanTpTxSduId
                      PduInfoType*  CanTpTxInfoPtr
   ------------------------------------------------------------------------------------------------
   Returncode       : Std_ReturnType: E_OK in case the transmit-request was accepted and will be 
                                      executed or
                                      E_NOT_OK in case the request was invalid or the affected
                                      channel was busy.
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTpWrapper_Transmit(PduIdType CanTpTxSduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr)
{
# if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
# else
  VAR(PduIdType, AUTOMATIC)       tpHdl;
  VAR(uint8,     AUTOMATIC)       found;
# endif
  VAR(Std_ReturnType, AUTOMATIC)  rc;

# if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
  rc = CanTp_Transmit(0, CanTpTxInfoPtr);
# else
  rc    = E_NOT_OK; 
  found = 0;
  tpHdl = vCanTp_PBCfgPtr_(NumCanTpTxSduId);
  while(tpHdl > 0)
  { /* search the SduId belonging to the remapped SduId */
    tpHdl--;
    if(vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl, CANTP_REMAP_TXNSDU_ID, CANTP_TX__REMAP_TXNSDU_ID) == CanTpTxSduId)
    { /* found matching remapped id */
      /* tpHdl = vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl, CANTP_TXNSDU_ID, CANTP_TX__TXNSDU_ID); implicitly done by sorted ids within generated data */
      found = 1;
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
  }

  vCanTp_DetAssert((found > 0), CanTp_Transmit_SId, CANTP_E_PARAM_ID)
  if(found != 0)
  { /* matching SduId found */
    rc = CanTp_Transmit(tpHdl, CanTpTxInfoPtr);
  }
# endif /* (CANTP_SINGLE_CONN_OPTIMIZED) */
  return(rc);
} /* CanTpWrapper_Transmit() */
#endif

/**************************************************************************************************
   Function name    : CanTp_Transmit
   ------------------------------------------------------------------------------------------------
   Description      : 
   ------------------------------------------------------------------------------------------------
   Called by        : Pdu-Router or other application
   ------------------------------------------------------------------------------------------------
   Parameter        : PduIdType CanTpTxSduId
                      PduInfoType* pData
   ------------------------------------------------------------------------------------------------
   Returncode       : Std_ReturnType: E_OK in case the transmit-request was accepted and will be 
                                      executed, soon, or
                                      E_NOT_OK in case the request was invalid or the affected
                                      channel was busy.
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_Transmit(PduIdType CanTpTxSduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pData)  
{
  VAR(vCanTp_FrameType, AUTOMATIC) frmType;
#if( (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON) || ((CANTP_CONSTANT_TX__TA_TYPE == STD_ON) && (CANTP_CONSTANT_TX__NCS == STD_ON)) )
#else
  P2CONST(vCanTp_TxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pTxNsduCfg;
#endif
#if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#else
  VAR(PduIdType, AUTOMATIC)        tpHdl;
#endif
  VAR(Std_ReturnType, AUTOMATIC)   ret;
  vCanTp_TpTxStatePtrType          pTpTxState;
#if ( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#else
# if( ((CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON) && (CANTP_ENABLE_WRAP_TRANSMIT == STD_OFF)) ||\
      ((CANTP_HAVE_INIT_CFG_PTR        == STD_ON) && (CANTP_ENABLE_WRAP_TRANSMIT == STD_OFF)) )
  VAR(uint8,     AUTOMATIC) found;
# endif
#endif

  /* PRQA S 3200 QAC_L1 */ /* RULE 16.10: No usage of return value intended. */
  /* PRQA S 3201 QAC_L1 */ /* MD_CANTP_MISRA_3201 */
  /* PRQA S 3355 QAC_L1 */ /* MD_CANTP_MISRA_3355 */
  /* PRQA S 3356 QAC_L1 */ /* MD_CANTP_MISRA_3356 */
  /* PRQA S 3358 QAC_L1 */ /* MD_CANTP_MISRA_3358 */
  /* PRQA S 3359 QAC_L1 */ /* MD_CANTP_MISRA_3359 */

#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
  vCanTp_DetAssertReturn((CanTpTxSduId <= CANTP_MAX_NUM_TXSDUS),                CanTp_Transmit_SId, CANTP_E_INVALID_TX_ID, E_NOT_OK)
#else
#  if(CANTP_HAVE_INIT_CFG_PTR == STD_ON)
  /*vCanTp_DetAssert((CanTpTxSduId <  vCanTp_LData(CfgPtr)->NumCanTpTxSduId),     CanTp_Transmit_SId, CANTP_E_INVALID_TX_ID)
    The number is counted in count per identity, but the TxSduId is incremented over all identities. So this assertion is not valid anymore */
#  else
  vCanTp_DetAssertReturn((CanTpTxSduId <  vCanTp_Cfg.NumCanTpTxSduId),          CanTp_Transmit_SId, CANTP_E_INVALID_TX_ID, E_NOT_OK)
#  endif
#endif
  /* PDUR Spec. V2.2.16 R4.0 Rev 0001 chapt. 7.1.2.2: Note that the CanTp_Transmit may or may not contain data. */
  vCanTp_DetAssertReturn((pData != NULL_PTR),                                   CanTp_Transmit_SId, CANTP_E_INVALID_TX_BUFFER, E_NOT_OK)
  /* CANTP299: Only the data length information of the structure indicated by CanTpTxInfoPtr has to be used.
     Its value indicates the payload length of the N-SDU, which is to be transmitted. */
  vCanTp_DetAssertReturn((pData->SduLength <= CANTP_MAX_DATA_LENGTH),           CanTp_Transmit_SId, CANTP_E_INVALID_TX_LENGTH, E_NOT_OK)

  if(vCanTp_LData(InitState) != cCanTp_Initialized)
  { /* reject any transmit request in state CANTP_OFF */
#if(CANTP_OPER_NOT_SUPPORTED_REPORT_DEM == STD_ON)
    vCanTp_DemReportError(CanTp_E_Oper_Not_Supported, DEM_EVENT_STATUS_FAILED)  /* CanTp101 */
#else  /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */
    vCanTp_DetReportError(CanTp_Transmit_SId, CANTP_E_UNINIT)                   /* CanTp101 */
#endif /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */

    return(E_NOT_OK);
  }

  ret = E_NOT_OK;

#if ( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
# if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)CanTpTxSduId; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
# endif
# if( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON )
  vCanTp_DetAssertReturn((vCanTp_PBCfg(vCanTp_TxNsduCfg, 0, CANTP_REMAP_TXNSDU_ID, CANTP_TX__REMAP_TXNSDU_ID) == CanTpTxSduId), CanTp_Transmit_SId, CANTP_E_PARAM_ID, E_NOT_OK)
# endif

#else   /* ( CANTP_SINGLE_CONN_OPTIMIZED == STD_OFF ) */

# if( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON )
#  if( CANTP_ENABLE_WRAP_TRANSMIT == STD_ON )
  tpHdl = CanTpTxSduId;  /* see CanTpWrapper_Transmit() */
#  else
  found = 0;
  tpHdl = vCanTp_PBCfgPtr_(NumCanTpTxSduId);
  while(tpHdl > 0)
  { /* search the SduId belonging to the remapped SduId */
    tpHdl--;
    if(vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl, CANTP_REMAP_TXNSDU_ID, CANTP_TX__REMAP_TXNSDU_ID) == CanTpTxSduId)
    { /* found matching remapped id */
      /* tpHdl = vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl, CANTP_TXNSDU_ID, CANTP_TX__TXNSDU_ID); implicitly done by sorted ids within generated data */
      found = 1;
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
  }
  vCanTp_DetAssert((found > 0), CanTp_Transmit_SId, CANTP_E_INVALID_TX_ID)
  if(found == 0)
  { /* no matching SduId found */
    return(E_NOT_OK); 
  }
#  endif
# else  /* ( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_OFF ) */
  /* PRQA S 3198 2 */ /* Initial assignment for safety reasons. */
  tpHdl = CanTpTxSduId;
# endif

# if( CANTP_HAVE_INIT_CFG_PTR == STD_ON )
  /* Different identities are available */
#  if( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON )
   /* Already searched for a valid Sdu-Id */
#  else
  found = 0;
  tpHdl = vCanTp_LData(CfgPtr)->NumCanTpTxSduId;
  while(tpHdl > 0)
  { /* search the SduId belonging to the actual identity */
    tpHdl--;
    if(vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl, CANTP_TXNSDU_ID, CANTP_TX__TXNSDU_ID) == CanTpTxSduId)
    { /* found matching id */
      /* tpHdl = vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl, CANTP_TXNSDU_ID, CANTP_TX__TXNSDU_ID); implicitly done by sorted ids within generated data */
      found = 1;
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
  }
  vCanTp_DetAssert((found > 0), CanTp_Transmit_SId, CANTP_E_INVALID_TX_ID)
  if(found == 0)
  { /* no matching SduId found */
    return(E_NOT_OK); 
  }
#  endif
# else
  /* No different identities are available */
# endif
#endif  /* ( CANTP_SINGLE_CONN_OPTIMIZED ) */

  /* PRQA S 0505 2 */ /* MD_CANTP_MISRA_0505 */
  if( pData->SduLength > 0 )
  { /* min length checked */
    Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);   /* CanTp_Transmit */

    /* check for half duplex */
#if !defined( CANTP_TX__DUPLEX_MODE )
    if(vCanTp_PBCfg_TX__DUPLEX_MODE(TPTXHDL) == CANTP_MODE_HALF_DUPLEX)
#endif
    { /* check if a reception is in progress */
#if( CANTP_TX__ENABLE_HALF_DUPLEX_CHECK == STD_ON )
      PduIdType rxHdl;
      rxHdl = (vCanTp_PBCfg(vCanTp_TxNsduCfg, TPTXHDL, CANTP_RXNSDU_ID, CANTP_RX__RXNSDU_ID));
      if(rxHdl != CANTP_INVALID_HDL) /* TaType == CanTp_Physical or Uni-directional */
      {
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
        if(vCanTp_rxHdlMap[rxHdl] != CANTP_INVALID_HDL)
# endif
        { /* found a valid rxHdl */
          if(vCanTp_RxState[TP_RX_HDL(rxHdl)].ChannelState != cRxState_Idle)
          { /* Rx side seems to be busy - reject transmit */
            Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);   /* CanTp_Transmit */
            return(E_NOT_OK);
          }
        }
      }
#endif /* CANTP_TX__ENABLE_HALF_DUPLEX_CHECK */
    } /* endif half duplex */

    /* check if Sdu is already in use */
#if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
    if (vCanTp_txHdlMap[tpHdl] == CANTP_INVALID_HDL)
    {
      /* Sdu is not in use; try to get a free channel */
      if(vCanTp_TxGetResource(tpHdl) != CANTP_INVALID_HDL)
      {
        /* free channel successfully allocated */
        pTpTxState = &vCanTp_TxState[TP_TX_HDL(tpHdl)];
#else
    pTpTxState = &vCanTp_TxState[TP_TX_HDL(tpHdl)];
    if(pTpTxState->ChannelState == cTxState_Idle)
    {
      /* transmission not in progress */
      {
#endif

        ret = E_OK;

#if( (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON) || ((CANTP_CONSTANT_TX__TA_TYPE == STD_ON) && (CANTP_CONSTANT_TX__NCS == STD_ON)) )
#else
        pTxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_TxNsduCfg, TPTXHDL));
#endif

        /* check for single / multi frame */
        if(pData->SduLength <= vCanTp_txGetPayloadLenSF(TPTXHDL)) 
        { /* single frame sufficient */
          frmType = cCanTp_SF; 
        }
        else 
        { /* Multi frame necessary */
          frmType = cCanTp_FF;
#if(!defined(CANTP_TX__TA_TYPE))
          if( CANTP_TX_CFG_PTR__TA_TYPE() == CANTP_FUNCTIONAL )
#endif
#if( (CANTP_CHECK_TX_TA_TYPE == CANTP_TAT_DYN) || (CANTP_CHECK_TX_TA_TYPE == CANTP_TAT_FUNC) )
          { /* Don't accept functional FF in 1:n connections */
            vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_UNEXP_PDU);
# if defined( CANTP_AUTOSARVERSION4 )
            vCanTp_DetReportError(CanTp_Transmit_SId, CANTP_E_INVALID_TATYPE)
# endif
            ret = E_NOT_OK;
          }
#endif
        }

        if(ret == E_OK)
        { /* Prepare transmission of the first frame of this connection during the CanTp_MainFunctionTx */
          pTpTxState->DataIndex   = 0;
          pTpTxState->DataLength  = pData->SduLength;
          pTpTxState->frameType   = frmType;
          pTpTxState->channel     = TPTXHDL;
          /* Set channel state to get a buffer and start with SF/FF payload already */
          pTpTxState->Timer        = CANTP_TX_CFG_PTR__NCS();   /* see CanTp:167 */
          pTpTxState->ChannelState = cTxState_WaitForTxBuffer;
#if( CANTP_ASYNC_TRANSMIT == STD_ON )
          /* CANTP176: The function CanTp_Transmit() shall be asynchronous */
#else
# if (CANTP_ASYNC_SF_TRANSMIT == STD_ON)
          if (frmType != cCanTp_SF)
# endif
          {
            (void)vCanTp_TxRetrieveApplTxBuffer(CANTP_TX_HDL_CVAL_ONLY);
          }
#endif
        }
      } /* endif resource available */
    } /* endif Sdu already in use */
    Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);   /* CanTp_Transmit */
  } /* endif zero length */
  /* PRQA  L:QAC_L1 */
  return(ret);
} /* PRQA S 2006 */ /* MD_MSR_14.7 */ /* PRQA S 6010 */ /* MD_MSR_STPTH */  /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* CanTp_Transmit() */

/**************************************************************************************************
   Function name    : vCanTp_CanIfRxIndication
   ------------------------------------------------------------------------------------------------
   Description      : Indication of the reception of a CanIf-Pdu containing CanTp-data
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp
   ------------------------------------------------------------------------------------------------
   Parameter        : Zero based CanIfRxPduId which is equivalent to the CanTp-connection
   ------------------------------------------------------------------------------------------------
   Returncode       : void
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void,  CANTP_CODE) vCanTp_CanIfRxIndication(CANTP_HDL_PVAL_FIRST
                                                        uint8 direction,
                                                        P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu)
{
#if defined( CANTP_ENABLE_PDUR_API40 )
  VAR(PduInfoType,       AUTOMATIC)  PduInfo;
  VAR(BufReq_ReturnType, AUTOMATIC)  bReq;
#endif
#if( CANTP_RX_FULL_BUFFER_PROVISION == STD_ON )
  VAR(PduLengthType, AUTOMATIC) counter;
#endif
  VAR(uint8, AUTOMATIC)         hiByte; 
  VAR(uint8, AUTOMATIC)         loByte;
  VAR(uint8, AUTOMATIC)         frmType;
#if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
  VAR(uint8, AUTOMATIC)         fmtOffset;
#endif
  VAR(uint8, AUTOMATIC)         frmOffset;
  VAR(PduLengthType, AUTOMATIC) CFlength;
  VAR(uint8, AUTOMATIC)         SNinFrame;
  vCanTp_TpRxStatePtrType       pTpRxState;
  vCanTp_TpTxStatePtrType       pTpTxState;
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
  P2CONST(vCanTp_RxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pRxNsduCfg;
#endif

  Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);  /* vCanTp_CanIfRxIndication */

#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
  pRxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_RxNsduCfg,TPRXHDL));
# if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)pRxNsduCfg;  /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
# endif
#endif

#  if( (CANTP_SINGLE_CONN_OPTIMIZED == STD_ON) && ( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_OFF ) && ( CANTP_CONSTANT_RX__MAX_PAYLOAD_LENGTH == STD_OFF ) )
#   if( CANTP_NUM_RX_CHANNELS >= 2 )
    /* "When using Single Connection then the physical and the functional Rx-NSdu must be configured with the same addressing type." */
  vCanTp_DetAssert( ((vCanTp_RxNsduCfg[0].CANTP_MAX_PAYLOAD_LENGTH) == (vCanTp_RxNsduCfg[1].CANTP_MAX_PAYLOAD_LENGTH)), CanTp_RxIndication_SId, CANTP_E_PARAM_ID)
#   endif
#  endif /* CANTP_SINGLE_CONN_OPTIMIZED */

  pTpRxState = &vCanTp_RxState[TP_RX_HDL(tpHdl)];
  pTpTxState = &vCanTp_TxState[TP_TX_HDL(tpHdl)];

  /* get addressing format offset */
#if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
 fmtOffset = (uint8)((direction == CANTP_RX) ? ( vCanTp_rxGetAdrFmt(tpHdl)) : ( vCanTp_txGetAdrFmt(tpHdl))); 
#else
# if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)direction;  /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
# endif
#endif

  /* check frame type */
  frmType = (uint8)(pPdu->SduDataPtr[FORMAT_OFFSET] & cCanTp_FrameTypeMask);
  switch(frmType)
  {
  /**********************
  * Received FirstFrame *
  **********************/
  case kL4_FirstFrame:
    /* Distinguish between 1:1 and 1:n connection */
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON  )
# if( CANTP_NUM_RXSDUS >= 2 )
    if(tpHdl == CANTP_RX__RXNSDU_ID_FUNC)
    { /* Don't accept functional FF in 1:n connections */
      vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_UNEXP_PDU, cCanTp_Initialize);
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
# endif
#endif /* CANTP_SINGLE_CONN_NOPB_OPTIMIZED */

#if( !defined(CANTP_RX__TA_TYPE) )
    if(CANTP_RX_CFG_PTR__TA_TYPE(TPRXHDL) == CANTP_FUNCTIONAL)
#endif
#if( (CANTP_CHECK_RX_TA_TYPE == CANTP_TAT_DYN) || (CANTP_CHECK_RX_TA_TYPE == CANTP_TAT_FUNC) )
    { /* Don't accept functional FF in 1:n connections */
      vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_UNEXP_PDU, cCanTp_Initialize);
# if defined( CANTP_AUTOSARVERSION4 )
      vCanTp_DetReportError(CanTp_RxIndication_SId, CANTP_E_INVALID_TATYPE)
# endif
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
#endif
#if( !defined(CANTP_RX__TA_TYPE) )
    else
#endif
    { /* PRQA S 3201 */ /* May not be reachable in every configruation */
      /* Check if this FF is expected */
      if(pTpRxState->ChannelState != cRxState_Idle)  
      { /* See if the frame belongs to an already running connection */
#if( (CANTP_SINGLE_CONN_OPTIMIZED == STD_ON) && (CANTP_NUM_RX_CHANNELS <= 1) )
#else
        if(pTpRxState->channel == tpHdl)
#endif
        { /* Stop running reception to set up with new FF */
          /* Notification is 'UNEXP_PDU' relying on ISO 15765-2.2 because AR is inconsistent from 3.x (NOT_OK) til 4.0 (NOT_OK and UNEXP_PDU) */
          vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_UNEXP_PDU, cCanTp_NoAdminReset);
        }
#if( (CANTP_SINGLE_CONN_OPTIMIZED == STD_ON) && (CANTP_NUM_RX_CHANNELS <= 1) )
#else
        else
        { /* frame from another connection: Ignore */
          break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
        }
#endif
      }

      /* Start a new connection */
      pTpRxState->frameType  = cCanTp_FF;
      pTpRxState->channel    = TPRXHDL;

      /* *** Adopt dynamically set STMIN/BS user values *** */
#if ( CANTP_ENABLE_EXT_API_BS == STD_ON )
      CANTP_DYN_BS[TPRXHDL]    = vCanTp_DynBS[TPRXHDL];    /* Dynamic BS values can be used from now on for the next receptions */
#endif
#if ( CANTP_ENABLE_EXT_API_STMIN == STD_ON )
      CANTP_DYN_STMIN[TPRXHDL] = vCanTp_DynSTmin[TPRXHDL]; /* Dynamic STmin values can be used from now on for the next receptions */
#endif
      /* *** Get current STMIN/BS values from this connection runtime-data *** */
      pTpRxState->STMin = vCanTp_RxGetSTmin(TPRXHDL);
      pTpRxState->BlocksizeCounter = vCanTp_RxGetBlockSize(TPRXHDL);

      /* *** end of extended API BS/STmin *** */

      /* read DL */
      hiByte = (uint8)(pPdu->SduDataPtr[FORMAT_OFFSET] & cCanTp_DLMaskFF);
      loByte = (uint8)(pPdu->SduDataPtr[FORMAT_OFFSET + 1]);
      /* store length info */
      pTpRxState->DataLength = vCanTp_Make16Bit(hiByte,loByte);
      pTpRxState->DataIndex  = 0;
      pTpRxState->providedDataLength = 0;

      /* Length announced in FF has to be larger than the payload that would fit into a SF */
      if( (pTpRxState->DataLength > (vCanTp_rxGetPayloadLenSF(TPRXHDL))) && (pPdu->SduLength == cCanTp_FrameLength) )
      { /* No underrun of min. length and DLC check ok */
        /* Prepare getting a buffer - Indication of FC(CTS/WT/OVFL) is done later after buffer-retrieval */
        frmOffset = (uint8) (FORMAT_OFFSET + cCanTp_FF_OFFSET);        /* Add frame format offset (now pointing to first payload byte) */
        pTpRxState->Timer      = CANTP_RX1_CFG_PTR__NBR(tpHdl);     /* see CanTp:166 */
        pTpRxState->WFTCounter = CANTP_RX1_CFG_PTR__WFTMAX(tpHdl);  /* Init max. no. of wait frames*/
        vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (&vCanTp_rxBuf[TP_RX_HDL(tpHdl)][0]), 
                      (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (pPdu->SduDataPtr + frmOffset), 
                      (cCanTp_FrameLength - frmOffset) );

#if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
        vCanTp_RxApplRxFFIndication(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID, CANTP_RX__REMAP_RXNSDU_ID), E_OK);
#else
        vCanTp_RxApplRxFFIndication(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID, CANTP_RX__RXNSDU_ID), E_OK);
#endif

#if defined( CANTP_ENABLE_PDUR_API40 )
# if ( CANTP_STRICT_RX_CALL_SEQ == STD_ON )
        if(pTpRxState->ApplState != CANTP_APPL_INFORMED)
# endif
        {
          /* PRQA S 3335 QAC_L3 */ /* RULE 8.1: Declaration available via macro redefinition. */
# if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
          bReq = vCanTp_RxApplStartOfReception(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID,CANTP_RX__REMAP_RXNSDU_ID), /* CanTpRxPduId */
                                              pTpRxState->DataLength,                                                    /* SduLength    */
                                              &(pTpRxState->providedDataLength));                                        /* RxBufSizePtr */
# else
          bReq = vCanTp_RxApplStartOfReception(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID,      CANTP_RX__RXNSDU_ID), /* CanTpRxPduId */
                                              pTpRxState->DataLength,                                              /* SduLength    */
                                              &(pTpRxState->providedDataLength));                                  /* RxBufSizePtr */
# endif
          pTpRxState->bufState = bReq;
          /* ***
          BUFREQ_OK: Connection has been accepted. RxBufferSizePtr indicates the available receive buffer.
          BUFREQ_E_BUSY: Currently no buffer of the requested size is available. RxBufferSizePtr remains unchanged. 
                        2009-03-25, Hs: "Connection has been rejected" - is not correct, should behave like before.
          BUFREQ_E_NOT_OK: Connection has been rejected. RxBufferSizePtr remains unchanged.
          BUFREQ_E_OVFL:   ... is missing
          
          AR4: 
          CANTP275: If the upper layer cannot provide a buffer because of an error or a resource limitation,  
                    the  PduR_CanTpStartOfReception()  function returns BUFREQ_E_NOT_OK or BUFREQ_E_OVFL. 
          *** */
# if(( CANTP_STRICT_RX_CALL_SEQ == STD_ON ) || ( CANTP_RC == STD_ON ) )
          if((pTpRxState->bufState == BUFREQ_OK) || (pTpRxState->bufState == BUFREQ_E_BUSY))
          { /* now the application is informed about a reception being in process */
            pTpRxState->ApplState = (uint8)(CANTP_APPL_INFORMED & 0x01);
          }
# endif
        }
        /* from AR4 3.0.5 Draft: 
            CANTP081: After the reception of a FF, if PduR_CanTpStartOfReception returns BUFREQ_E_NOT_OK 
                      the CanTp module shall abort the reception. No Flow Control will be sent in this case.   
            CANTP318: After the reception of a FF, if PduR_CanTpStartOfReception returns BUFREQ_E_OVFL 
                      the CanTp module shall send a FC(OVFLW) and abort the reception. 
                      If the error occurs after a CF reception, the FC frame shall not be sent. 
                      In case of CF the buffer status is returned by the PduR_CanTpCopyRxData() function. */
        /* from AR4 V3.0.0: 
            CANTP081: After the reception of a FF, if PduR_CanTpStartOfReception returns BUFREQ_E_NOT_OK or BUFREQ_E_OVFL 
                      the  CanTp  module  shall  send a FC(OVFLW) and abort the reception. 
                      If the error occurs after a CF reception, the FC frame shall not  be  sent.  
                      In case of CF the  buffer  status  is  returned  by  the PduR_CanTpCopyRxData() function.
            CANTP271: If  PduR_CanTpCopyRxData returns BUFREQ_E_NOT_OK / BUFREQ_E_OVFL / BUFREQ_E_BUSY 
                      after reception of a CF in a block the CanTp shall abort the reception. */
        if( (pTpRxState->bufState == BUFREQ_E_NOT_OK) || (pTpRxState->bufState == BUFREQ_E_OVFL) )
        { /* Segmented  reception and FF: send FC(OVFL) and stop (CanTp081)
             The application notification (NTFRSLT_E_NO_BUFFER) is done from the FC confirmation. */
          pTpRxState->bufState     = BUFREQ_E_NOT_OK;
          pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
          pTpRxState->ChannelState = cRxState_WaitForFCOverConfIsr;
          pTpRxState->queued++;  /* Set FC(OVFL) transmission request */
          VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
        }
        else
#endif /* CANTP_ENABLE_PDUR_API40 */
        {  /* CANTP082 from AR4 V3.0.0: If the function PduR_CanTpStartOfReception() returns BUFREQ_E_BUSY
              the CanTp module shall suspend the N-SDU reception by sending the next FC(WT) (this is done after subsequent PduR_CanTpCpyRxData) */
          pTpRxState->ChannelState = cRxState_WaitForRxBuffer;
          pTpRxState->ExpectedSN = cCanTp_SNFirstCF;   /* Wait for a CF with first SN */
#if( CANTP_CONSTANT_BS == STD_ON )
          CANTP_CONST_BS[TPRXHDL] = 0;
#endif
#if( CANTP_RX_GET_BUFFER_FROM_ISR == STD_ON )
          vCanTp_RxRetrieveApplRxBuffer(CANTP_HDL_CVAL_ONLY);
#endif
        }
      }
      else 
      { /* invalid data length */
        vCanTp_DetReportError(CanTp_RxIndication_SId, CANTP_E_INVALID_RX_LENGTH)
        vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)cCanTp_NoResultNotification, cCanTp_Initialize);
      }
    }
    break; 
    /* FF */

  /***********************
  * Received SingleFrame *
  ***********************/
  case kL4_SingleFrame:
    /* Check if this SF is expected */
    if (pTpRxState->ChannelState != cRxState_Idle)  
    { /* See if the frame belongs to the connection */
      if (pTpRxState->channel == TPRXHDL)
      { /* Stop running reception to set up with new SF */
        /* Notification is 'UNEXP_PDU' relying on ISO 15765-2.2 because AR is inconsistent from 3.x (NOT_OK) til 4.0 (NOT_OK and UNEXP_PDU) */
        vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_UNEXP_PDU, cCanTp_NoAdminReset);
      }
      else
      { /* frame from other connection: Ignore */
        break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
      }
    }

    /* Start a new connection */
    pTpRxState->frameType  = cCanTp_SF;
    /* read DL */
    pTpRxState->DataLength = (uint16)(pPdu->SduDataPtr[FORMAT_OFFSET] & cCanTp_DLMaskSF);
    frmOffset = (uint8)(cCanTp_SF_OFFSET + vCanTp_rxGetAdrFmt(tpHdl));
    if( ((pTpRxState->DataLength) > 0) && ((pTpRxState->DataLength) <= (vCanTp_rxGetPayloadLenSF(TPRXHDL))) && ((pPdu->SduLength) >= ((pTpRxState->DataLength) + FORMAT_OFFSET + cCanTp_SF_OFFSET)) )
    { /* Maximum length not exceeded and not zero and DLC check succeeded */
      vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (&vCanTp_rxBuf[TP_RX_HDL(tpHdl)][0]), 
                    (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (pPdu->SduDataPtr + frmOffset),
                    (pTpRxState->DataLength) );

      pTpRxState->Timer   = CANTP_RX_CFG_PTR__NBR(tpHdl); /* see CanTp:166 */
      pTpRxState->channel = TPRXHDL;

#if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
        vCanTp_RxApplRxSFIndication(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID, CANTP_RX__REMAP_RXNSDU_ID), E_OK);
#else
        vCanTp_RxApplRxSFIndication(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID, CANTP_RX__RXNSDU_ID), E_OK);
#endif

#if defined( CANTP_ENABLE_PDUR_API40 )
# if ( CANTP_STRICT_RX_CALL_SEQ == STD_ON )
      if(pTpRxState->ApplState != CANTP_APPL_INFORMED)
# endif
      {
# if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
        bReq = vCanTp_RxApplStartOfReception(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID,CANTP_RX__REMAP_RXNSDU_ID), /* CanTpRxPduId */
                                            pTpRxState->DataLength,                                                    /* SduLength    */
                                            &(pTpRxState->providedDataLength));                                        /* RxBufSizePtr */
# else
        bReq = vCanTp_RxApplStartOfReception(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID,      CANTP_RX__RXNSDU_ID), /* CanTpRxPduId */
                                            pTpRxState->DataLength,                                              /* SduLength    */
                                            &(pTpRxState->providedDataLength));                                  /* RxBufSizePtr */
# endif
        /* PRQA  L:QAC_L3 */
        pTpRxState->bufState = bReq;
        /* ***
        BUFREQ_OK: Connection has been accepted. RxBufferSizePtr indicates the available receive buffer.
        BUFREQ_E_BUSY: Currently no buffer of the requested size is available. RxBufferSizePtr remains unchanged. 
                      2009-03-25, Hs: "Connection has been rejected" - is not correct, should behave like before.
        BUFREQ_E_NOT_OK: Connection has been rejected. RxBufferSizePtr remains unchanged.
        BUFREQ_E_OVFL:   ... is missing
        *** */
# if(( CANTP_STRICT_RX_CALL_SEQ == STD_ON ) || ( CANTP_RC == STD_ON ) )
        if((pTpRxState->bufState == BUFREQ_OK) || (pTpRxState->bufState == BUFREQ_E_BUSY))
        { /* now the application is informed about a reception being in process */
          pTpRxState->ApplState = (uint8)(CANTP_APPL_INFORMED & 0x01);
        }
# endif
      }
      if( (pTpRxState->bufState == BUFREQ_E_NOT_OK) || (pTpRxState->bufState == BUFREQ_E_OVFL) )
      {
        vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
      }
      else
#endif /* CANTP_ENABLE_PDUR_API40 */
      {
        pTpRxState->ChannelState = cRxState_WaitForRxBuffer;        /* Prepare getting a buffer from the application */
#if( CANTP_RX_GET_BUFFER_FROM_ISR == STD_ON )
        vCanTp_RxRetrieveApplRxBuffer(CANTP_HDL_CVAL_ONLY);
#endif
      }
    }
    else 
    { /* Maximum length exceeded or zero */
      vCanTp_DetReportError(CanTp_RxIndication_SId, CANTP_E_INVALID_RX_LENGTH)
      vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)cCanTp_NoResultNotification, cCanTp_Initialize);
    }
    break;
    /* SF */

  /*****************************
  * Received consecutive frame *
  *****************************/
  case kL4_ConsecutiveFrame:
  {
#if (CANTP_HIGH_RX_LOW_TX_PRIO == STD_ON)
    if( (pTpRxState->ChannelState == cRxState_WaitForFCConfIsr) && (pTpRxState->queued == 0) )
    {
      /* CF received before Tx confirmation of FC; treat FC as confirmed and release semaphore */
#if( CANTP_TX_SERIALIZE == STD_ON )
      vCanTp_TxSemaphore.hdl = CANTP_INVALID_HDL;
#endif
      CANIF_CANCELTRANSMIT(vCanTp_PBCfg(vCanTp_RxNsduCfg, TPRXHDL, CANTP_TXFC_NPDU_ID, CANTP_RX__TXFC_NPDU_ID));
      vCanTp_CanIfTxConfirmation(CANTP_HDL_CVAL_FIRST  CANTP_RX); /* mark FC as confirmed */
    }
#endif

    /* Check if tpHdl is in use */
#if defined( CANTP_ENABLE_SINGLE_CONN )
    if( (pTpRxState->ChannelState == cRxState_WaitCF) )
#else
    if( (pTpRxState->ChannelState == cRxState_WaitCF) && (pTpRxState->channel == tpHdl) )
#endif
    { /* Prepare reception */
      pTpRxState->frameType = cCanTp_CF;
      SNinFrame = (uint8)(pPdu->SduDataPtr[FORMAT_OFFSET] & kL4_SNMask);
      CFlength = (PduLengthType)vCanTp_rxGetPayloadLenCF(TPRXHDL);
      if(CFlength > (pTpRxState->DataLength - pTpRxState->DataIndex))
      { /* Reduce payload for last CF */
        CFlength = (pTpRxState->DataLength - pTpRxState->DataIndex);
      }
      if((pPdu->SduLength) < (CFlength + FORMAT_OFFSET + cCanTp_CF_OFFSET))
      {
        /* DLC check failed */
      }
      else if(SNinFrame != (uint8)(pTpRxState->ExpectedSN))
      { /* Wrong SN */
#if ( CANTP_IGNORE_CF_WITH_WRONG_SN == STD_ON )
       /* Ignore CF (wprocan-a00-00-a, TMC_FAQ_EN) */
#else
        vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  NTFRSLT_E_WRONG_SN, cCanTp_Initialize);
#endif
      }
      else
      { /* Correct SN received */
#if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
        vCanTp_RxApplRxCFIndication(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID, CANTP_RX__REMAP_RXNSDU_ID), SNinFrame);
#else
        vCanTp_RxApplRxCFIndication(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID, CANTP_RX__RXNSDU_ID), SNinFrame);
#endif
#if defined( CANTP_ENABLE_PDUR_API40 )
        PduInfo.SduLength  = CFlength;
#endif
        /*** Copy Data ***/
#if( CANTP_RX_FULL_BUFFER_PROVISION == STD_ON )
        if((pTpRxState->providedDataLength >= CFlength) || (pTpRxState->providedDataLength >= (pTpRxState->DataLength - pTpRxState->DataIndex)) )
#endif
        { /* Buffer still big enough for next or last CF */
#if defined( CANTP_ENABLE_PDUR_API40 )
          PduInfo.SduDataPtr = ((pPdu->SduDataPtr) + cCanTp_CF_OFFSET + FORMAT_OFFSET);

          /* PRQA S 3335 QAC_L4 */ /* RULE 8.1: Declaration available via macro redefinition. */
# if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
          bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID,CANTP_RX__REMAP_RXNSDU_ID), /* CanTpRxPduId */
                                        &PduInfo,                                                                  /* PduInfoPtr   */
                                        &pTpRxState->providedDataLength);                                          /* RxBufSizePtr */
# else
          bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID,      CANTP_RX__RXNSDU_ID), /* CanTpRxPduId */
                                        &PduInfo,                                                            /* PduInfoPtr   */
                                        &pTpRxState->providedDataLength);                                    /* RxBufSizePtr */
# endif
          /* PRQA  L:QAC_L4 */

          pTpRxState->DataIndex = (PduLengthType)(pTpRxState->DataIndex + CFlength);                 /* Increase index during reception */
#else /* (CANTP_ENABLE_PDUR_API40 == STD_OFF) */
          vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))pTpRxState->DataBufferPtr, (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) ((pPdu->SduDataPtr) + cCanTp_CF_OFFSET + FORMAT_OFFSET), CFlength);
          pTpRxState->DataBufferPtr += CFlength;
          /* Update positions + indices */
          pTpRxState->providedDataLength        = (PduLengthType)(pTpRxState->providedDataLength - CFlength);        /* Decrease space during reception */
          pTpRxState->DataIndex                 = (PduLengthType)(pTpRxState->DataIndex + CFlength);                 /* Increase index during reception */
          pTpRxState->ApplPduInfoPtr->SduLength = (PduLengthType)(pTpRxState->ApplPduInfoPtr->SduLength + CFlength); /* Increase Rx-counter on CF       */
#endif
        }
#if( CANTP_RX_FULL_BUFFER_PROVISION == STD_ON )
        else
        { /* Buffer insufficient for next or last CF:
               - fill in available application buffer,
               - copy the rest to the internal Tp buffer,
               - request another application buffer    */
# if defined( CANTP_ENABLE_PDUR_API40 )
          PduInfo.SduDataPtr = ((pPdu->SduDataPtr) + cCanTp_CF_OFFSET + FORMAT_OFFSET);
          PduInfo.SduLength  = pTpRxState->providedDataLength;
          /* the following as to be done before the copyRxData becuse the provideLength is decreased by the PduR */
          pTpRxState->DataIndex = (PduLengthType)(pTpRxState->DataIndex + pTpRxState->providedDataLength);  /* Increase index during reception */
          counter               = CFlength - pTpRxState->providedDataLength;                                /* fragment size for internal storage */
          vCanTp_DetAssertVReturn((counter <= 8), CanTp_RxIndication_SId, CANTP_E_INVALID_RX_BUFFER)
          /* copy partial CF content to the appl. buffer */
          /* PRQA S 3335 QAC_L5 */ /* RULE 8.1: Declaration available via macro redefinition. */
#  if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
          bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID,CANTP_RX__REMAP_RXNSDU_ID), /* CanTpRxPduId */
                                        &PduInfo,                                                                  /* PduInfoPtr   */
                                        &pTpRxState->providedDataLength);                                          /* RxBufSizePtr */
#  else
          bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID,      CANTP_RX__RXNSDU_ID), /* CanTpRxPduId */
                                        &PduInfo,                                                            /* PduInfoPtr   */
                                        &pTpRxState->providedDataLength);                                    /* RxBufSizePtr */
#  endif
          /* PRQA  L:QAC_L5 */
          vCanTp_DetAssert((bReq == BUFREQ_OK), CanTp_RxIndication_SId, CANTP_E_INVALID_RX_BUFFER)          /* the provided length must be copied by the PduR in any case */
# else /* (CANTP_ENABLE_PDUR_API40 == STD_OFF) */
          /* copy partial CF content to the appl. buffer */
          vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))pTpRxState->DataBufferPtr, (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) ((pPdu->SduDataPtr) + cCanTp_CF_OFFSET + FORMAT_OFFSET), pTpRxState->providedDataLength);
          pTpRxState->DataBufferPtr            += pTpRxState->providedDataLength;
          pTpRxState->DataIndex                 = (PduLengthType)(pTpRxState->DataIndex + pTpRxState->providedDataLength);           /* Increase index during reception */
          pTpRxState->ApplPduInfoPtr->SduLength = (PduLengthType)(pTpRxState->ApplPduInfoPtr->SduLength + pTpRxState->providedDataLength); /* Increase Rx-counter on CF */
          counter = CFlength - pTpRxState->providedDataLength;
# endif /* (CANTP_ENABLE_PDUR_API40) */

          /* Copy the rest of the CF content to the internal CanTp buffer */
          vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(&vCanTp_rxBuf[TP_RX_HDL(tpHdl)][0]), 
# if defined( CANTP_ENABLE_PDUR_API40 )
                        (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(((pPdu->SduDataPtr + cCanTp_CF_OFFSET + FORMAT_OFFSET + PduInfo.SduLength))), 
# else
                        (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(((pPdu->SduDataPtr + cCanTp_CF_OFFSET + FORMAT_OFFSET + pTpRxState->providedDataLength))), 
# endif
                        counter);

          pTpRxState->FrameIndex      = counter; /* bytes left */
          vCanTp_DetAssertVReturn(((pTpRxState->FrameIndex) <= 8), CanTp_RxIndication_SId, CANTP_E_INVALID_STATE)   
          pTpRxState->FrameStartIndex = 0;
          /* Request another appl. buffer and check for FC(WT).
             Do not reload the timeout while trying to get more buffer */
          pTpRxState->ChannelState = cRxState_WaitForRxBuffer;
# if( CANTP_RX_GET_BUFFER_FROM_ISR == STD_ON )
          /* multiple transmitted FCs due to modified BS value; is called during BS handling below: vCanTp_RxRetrieveApplRxBuffer() */
          /* buffer size of zero: request a new buffer immediately because buffer request below will not be reached */
          if(pTpRxState->BlocksizeCounter == 0)
          {
            vCanTp_RxRetrieveApplRxBuffer(CANTP_HDL_CVAL_ONLY);
          }
# else
#  if !defined( CANTP_ENABLE_PDUR_API40 )
          pTpRxState->providedDataLength = 0;
#  endif
# endif
        }
#endif /* (CANTP_RX_FULL_BUFFER_PROVISION) */

        if(pTpRxState->DataIndex >= pTpRxState->DataLength)
        { /* Reception complete: 
             cancel reception (stop waiting for CF/FC),
             user callback RxIndication (multi frame complete)  */  
          vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  NTFRSLT_OK, cCanTp_Initialize);
        }
        else
        { /* Reception incomplete, calculate next expected SN */
          pTpRxState->ExpectedSN = (uint8)((pTpRxState->ExpectedSN + 1) & 0x0F);
          /* Do BS-counter-handling */
#if(CANTP_CHECK_BS == STD_ON)
          { /* BS-counter is in use */
            if(pTpRxState->BlocksizeCounter > 0)
            {
              pTpRxState->BlocksizeCounter--;
              if(pTpRxState->BlocksizeCounter == 0)
              { /* Either FC.CTS or FC.WT has to be sent */
                pTpRxState->Timer = CANTP_RX1_CFG_PTR__NAR(tpHdl);
# if( CANTP_RX_FULL_BUFFER_PROVISION == STD_ON )
                if( (pTpRxState->FrameIndex == 0) && ((pTpRxState->providedDataLength >= CFlength) || (pTpRxState->providedDataLength >= (pTpRxState->DataLength - pTpRxState->DataIndex))))
# endif
                { /* Buffer still big enough for next or last CF and no fragment behind: send FC.CTS */
                  if(pTpRxState->ChannelState != cRxState_WaitForFCConfIsr)
                  {
                    pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                    pTpRxState->queued++; /* Set FC transmission request */
                    VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
                  }
                }
# if( CANTP_RX_FULL_BUFFER_PROVISION == STD_ON )
                else
                { /* Request another appl. buffer and send FC.WT */
                  if( (pTpRxState->ChannelState == cRxState_Idle) || (pTpRxState->ChannelState == cRxState_WaitCF) )
                  {
# if defined( CANTP_ENABLE_PDUR_API40 )
                    pTpRxState->ChannelState = cRxState_WaitForFCWaitConfIsr;
                    pTpRxState->queued++;
                    VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
# else
                    pTpRxState->ChannelState = cRxState_WaitForRxBuffer;
#   if( CANTP_RX_GET_BUFFER_FROM_ISR == STD_ON )
                    vCanTp_RxRetrieveApplRxBuffer(CANTP_HDL_CVAL_ONLY);
#   endif
#  endif
                  }
                }
# endif
                break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
              } /* if( BS-counter == 0 ) */
            } /* if (BS-counter > 0 )   */
          } /* if( BS-counter in use ) */
#endif  /* BS is used */
          if( (pTpRxState->ChannelState == cRxState_WaitCF) 
#if( CANTP_CONSTANT_BS == STD_ON )
            || (CANTP_CONST_BS[TPRXHDL] != 0)
#endif
            )
          { /* Reload timeout if only waiting for next CF (enough buffer, no FC necessary) */
            pTpRxState->Timer = CANTP_RX1_CFG_PTR__NCR(tpHdl);
          }
        } /* else ( Txn complete ) */
      } /* if( SN OK) */
    }

#if ( CANTP_GW_ERRORS_REPORT_DEM == STD_ON)
    else
    {
      /* CF is not expected; if previous CF is still waiting for a buffer, a buffer oveflow has definitely occurred */
      if ( (cRxState_WaitForRxBuffer == pTpRxState->ChannelState) && (cCanTp_CF == pTpRxState->frameType) )
      {
        /* report DEM error */
        vCanTp_DemReportError(CanTp_E_Gw_Buffer_Overflow, DEM_EVENT_STATUS_FAILED)

        /* terminate connection to prevent undefined behavior (otherwise either Wrong SN or some kind of timeout will occure */
        vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
      }
    }
#endif
    break;
    /* CF */
  }
  
  /******************************
  * Received flow control frame *
  ******************************/
  case kL4_FlowControl:
  { 
#if (CANTP_HIGH_RX_LOW_TX_PRIO == STD_ON)
    if(pTpTxState->queued == 0)
    {
      if( (pTpTxState->ChannelState == cTxState_WaitForSForFFConfIsr) && (pTpTxState->frameType == cCanTp_FF) )
      {
        /* FC received before Tx confirmation of FF; treat FF as confirmed and release semaphore */
#if( CANTP_TX_SERIALIZE == STD_ON )
        vCanTp_TxSemaphore.hdl = CANTP_INVALID_HDL;
#endif
        CANIF_CANCELTRANSMIT(vCanTp_PBCfg(vCanTp_TxNsduCfg, TPTXHDL, CANTP_TXNPDU_ID, CANTP_TX__TXNPDU_ID));
        vCanTp_CanIfTxConfirmation(CANTP_HDL_CVAL_FIRST  CANTP_TX); /* mark FF as Tx-confirmed */
      }
      else if( (pTpTxState->ChannelState == cTxState_WaitForCFConfIsr) && (pTpTxState->BlocksizeCounter == 1) )
      {
        /* FC received before Tx confirmation of last CF in block; treat CF as confirmed and release semaphore */
#if( CANTP_TX_SERIALIZE == STD_ON )
        vCanTp_TxSemaphore.hdl = CANTP_INVALID_HDL;
#endif
        CANIF_CANCELTRANSMIT(vCanTp_PBCfg(vCanTp_TxNsduCfg, TPTXHDL, CANTP_TXNPDU_ID, CANTP_TX__TXNPDU_ID));
        vCanTp_TxCFTxConfirmation(CANTP_HDL_CVAL_ONLY);            /* mark CF as Tx-Confirmed */
      }
      else { /* MISRA */ }
    }
    else
    { /* Unexpected FC: Ignore ! */
      /* vCanTp_Error(CanTp_RxIndication_SId, NTFRSLT_E_UNEXP_PDU, (uint32)pTpTxState->ChannelState) (... see below) */
    }
#endif

    /* Check if expected frame and tpHdl in use */
#if defined( CANTP_ENABLE_SINGLE_CONN )
    if( (pTpTxState->ChannelState == cTxState_WaitFC) )
#else
    if( (pTpTxState->ChannelState == cTxState_WaitFC) && (pTpTxState->channel == tpHdl) )
#endif
    { /* Evaluate FS */
#if defined( CANTP_ENABLE_PDUR_API40 )
      PduLengthType reqMinLen;
      reqMinLen = vCanTp_txGetPayloadLen(TPTXHDL, (pTpTxState->frameType));
      if(reqMinLen > (pTpTxState->DataLength - pTpTxState->OverallDataIndex) )
      {
        reqMinLen = pTpTxState->DataLength - pTpTxState->OverallDataIndex;
      }
#endif
      if((pPdu->SduLength) >= ((cCanTp_LengthFC + FORMAT_OFFSET) + cCanTp_FC_OFFSET))
      { /* DLC check succeeded */
        switch(*(pPdu->SduDataPtr + FORMAT_OFFSET) & cCanTp_FSMask)
        {
        case kL4_FlowStatus_ClearToSend:
          { /* Get blocksize and STMIN value */
#if ( CANTP_IGNORE_FC_WITH_RES_STMIN == STD_ON )
# if( CANTP_USE_ONLY_FIRST_FC == STD_ON )
            if(pTpTxState->firstFC == 0)
# endif
            {
              uint8 tmpSTMin;
              tmpSTMin = pPdu->SduDataPtr[FORMAT_OFFSET + cCanTp_FmtOffsetStmin];
              /* When Reserved value is received, FC is rejected (wprocan-a00-00-a) */
              if( ((tmpSTMin & 0x80) != 0) && ((tmpSTMin < 0xF1) || (tmpSTMin > 0xF9)) )
              { /* Invalid value, ignore frame */
                break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
              }
            }
#endif  /* CANTP_IGNORE_FC_WITH_RES_STMIN */

#if( CANTP_USE_ONLY_FIRST_FC == STD_ON )
            if(pTpTxState->firstFC == 0)
            {
              pTpTxState->firstFC = 1;
              pTpTxState->BS               = pPdu->SduDataPtr[FORMAT_OFFSET + cCanTp_FmtOffsetBs];       /* store   BS    */
              pTpTxState->BlocksizeCounter = pPdu->SduDataPtr[FORMAT_OFFSET + cCanTp_FmtOffsetBs];       /* current BS    */
              pTpTxState->STMin            = pPdu->SduDataPtr[FORMAT_OFFSET + cCanTp_FmtOffsetStmin];    /* current STmin */
            }
            else
            { /* keep BS from first FC */
              pTpTxState->BlocksizeCounter = pTpTxState->BS;
            }
#else  /* CANTP_USE_ONLY_FIRST_FC */
            {
              pTpTxState->BlocksizeCounter = pPdu->SduDataPtr[FORMAT_OFFSET + cCanTp_FmtOffsetBs];       /* current BS    */
              pTpTxState->STMin            = pPdu->SduDataPtr[FORMAT_OFFSET + cCanTp_FmtOffsetStmin];    /* current STmin */
            }
#endif /* CANTP_USE_ONLY_FIRST_FC */

            /* Prepare sending of next CF */
            pTpTxState->frameType  = cCanTp_CF;
            pTpTxState->TimerSTMin = vCanTp_TxGetStminTimerFromStminValue(pTpTxState->STMin);
            if((pTpTxState->TimerSTMin) == 1)
            { /* Burst Mode */
#if defined( CANTP_ENABLE_PDUR_API40 )
              if(pTpTxState->providedDataLength < reqMinLen)
              { /* need more buffer, assuming N_CS timeout */
                pTpTxState->Timer = (vCanTp_PBCfg_TX__NCS(TPHDL));    /* see CanTp:167 */
                pTpTxState->providedDataLength = 0;
                pTpTxState->ChannelState = cTxState_WaitForTxBuffer;
              }
              else
#endif /* CANTP_ENABLE_PDUR_API40 */
              { /* enough buffer, using CAN confirmation timeout */
                pTpTxState->Timer = vCanTp_PBCfg_TX__NAS(TPHDL);
                pTpTxState->ChannelState = cTxState_WaitForCFConfIsr;
                pTpTxState->queued++;
                vCanTp_TxStateTask(CANTP_TX_HDL_CVAL_ONLY);
              }
            }
            else
            { /* No Burst Mode */
#if defined( CANTP_ENABLE_PDUR_API40 )
              if(pTpTxState->providedDataLength < reqMinLen)
              {
                pTpTxState->providedDataLength = 0;
                pTpTxState->Timer = (vCanTp_PBCfg_TX__NCS(TPTXHDL));    /* see CanTp:167 */
                pTpTxState->ChannelState = cTxState_WaitForTxBuffer;
              }
              else
#endif
              {
#if ( CANTP_USE_STMIN_AFTER_FC == STD_ON )
                /* transmit CF after STmin */
                pTpTxState->Timer        = vCanTp_TxGetStminTimerFromStminValue(pTpTxState->STMin);
#else
                /* transmit CF in next task cycle */
                pTpTxState->Timer        = 1;
                pTpTxState->TimerSTMin   = 1;
#endif
                pTpTxState->ChannelState = cTxState_WaitForTpTxCF;
              }
            }
          }
          break;
          /* FC.CTS */
     
        case kL4_FlowStatus_Wait:
          { /* WaitFrame received, restart timer */
            pTpTxState->Timer = vCanTp_PBCfg_TX__NBS(TPTXHDL);
          }
          break;
          /* FC.WT */
          
        case kL4_FlowStatus_OVFLW:
#if ( CANTP_IGNORE_FC_OVFL_INVALID_FS == STD_ON )
          /* Ignore FC (wprocan-a00-00-a, TMC_FAQ_EN) */
#else
          { /* Receiver reported an Overrun - terminate channel */
            vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER);
          }
#endif
          break;
          /* FC.OVFL */

        default:
#if ( CANTP_IGNORE_FC_OVFL_INVALID_FS == STD_ON )
          /* Ignore FC (wprocan-a00-00-a, TMC_FAQ_EN) */
#else
          { /* Indicate an invalid FS */
            vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_INVALID_FS);
          }
#endif
          break;
        } /* switch FS */ 
      } /* DLC check */
      else
      {
        vCanTp_DetReportError(CanTp_RxIndication_SId, CANTP_E_INVALID_RX_LENGTH)
      }
    } /* state check */
    else
    { /* Unexpected FC: Ignore ! */
      vCanTp_Error(CanTp_RxIndication_SId, NTFRSLT_E_UNEXP_PDU, (uint32)pTpTxState->ChannelState)
    }
  }
  break;
  /* FC */
  
  default:
    /* Ignore unknown frame types */
    vCanTp_Error(CanTp_RxIndication_SId, NTFRSLT_E_UNEXP_PDU, (uint32)pTpTxState->ChannelState)
    break;
  } /* switch(frmType) */

  Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* vCanTp_CanIfRxIndication */
} /* PRQA S 2006 */ /* MD_MSR_14.7 */  /* PRQA S 6010 */ /* MD_MSR_STPTH */  /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6050 */ /* MD_MSR_STCAL */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* vCanTp_CanIfRxIndication */


#if(CANTP_RX_INDICATION_API == STD_ON)
/**************************************************************************************************
   Function name    : CanTp_RxIndication
   ------------------------------------------------------------------------------------------------
   Description      : Processes the RxIndication coming from the CanIf in case the Pdu:
                      a) belongs to a channel configured for this ECU
                      b) has the correct target address (== local address of one of the connections
                         configured for this ECU)
   ------------------------------------------------------------------------------------------------
   Called by        : CanIf
   ------------------------------------------------------------------------------------------------
   Parameter        : PduIdType CanIfRxPduId: Zero-based CanIfRxPduId of a received CanTp-frame from 
                                             the CanIf
                      const PduInfoType *CanSduPtr: Pointer to the payload of the frame
   ------------------------------------------------------------------------------------------------
   Returncode       : void
   ------------------------------------------------------------------------------------------------
   Misc             : Several vCanTp_RxIndication-calls that interrupt each can appear in case of 
                      more than one CAN channel is connected!
**************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_RxIndication(  PduIdType CanTpRxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pCanTpRxPduPtr)
{
  VAR(PduIdType, AUTOMATIC) SduHdl;
  VAR(uint8, AUTOMATIC)     errC;
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
  VAR(PduIdType, AUTOMATIC) tmpHdl;
# endif
  VAR(uint8, AUTOMATIC) FrameType;
  VAR(uint8, AUTOMATIC) direction;
# if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
  VAR(uint8, AUTOMATIC) adrType;
# endif
# if( CANTP_EXTENDED_ADDRESSING == STD_ON )
  VAR(uint8, AUTOMATIC) currentTA;
# endif
# if( CANTP_MIXED11_ADDRESSING == STD_ON )
  VAR(uint8, AUTOMATIC) currentAE;
# endif


# if (CANTP_ENABLE_LLR_CALLOUTS == STD_ON)
  /* AR3-2539: pass RxIndication to low level routing module */
  if (vCanTp_LLR_RxIndication(CanTpRxPduId, pCanTpRxPduPtr) == E_NOT_OK)
  {
    return;
  }
# endif


  vCanTp_DetAssertVReturn((pCanTpRxPduPtr != NULL_PTR),                       CanTp_RxIndication_SId, CANTP_E_INVALID_RX_BUFFER)
# if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
  vCanTp_DetAssertVReturn((CanTpRxPduId < CANTP_MAX_RXPDU_ID),                CanTp_RxIndication_SId, CANTP_E_INVALID_RX_ID)
# else
  vCanTp_DetAssertVReturn((CanTpRxPduId < vCanTp_PBCfgPtr_(NumCanIfRxPduId)), CanTp_RxIndication_SId, CANTP_E_INVALID_RX_ID)
# endif
  /* PRQA S 3355 QAC_L1 */ /* MD_CANTP_MISRA_3355 */
  /* PRQA S 3356 QAC_L1 */ /* MD_CANTP_MISRA_3356 */
  /* PRQA S 3359 QAC_L1 */ /* MD_CANTP_MISRA_3359 */
  /* PRQA S 3200 QAC_L1 */ /* RULE 16.10: No usage of return value intended. */
  /* PRQA S 3201 QAC_L1 */ /* MD_CANTP_MISRA_3201 */
  /* PRQA  L:QAC_L1 */

  if(vCanTp_LData(InitState) != cCanTp_Initialized)
  { /* reject any transmit request in state CANTP_OFF */
# if(CANTP_OPER_NOT_SUPPORTED_REPORT_DEM == STD_ON)
    vCanTp_DemReportError(CanTp_E_Oper_Not_Supported, DEM_EVENT_STATUS_FAILED)  /* CanTp101 */
# else  /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */
    vCanTp_DetReportError(CanTp_RxIndication_SId, CANTP_E_UNINIT)               /* CanTp101 */
# endif /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */

    return;
  }

  /*** decision from 2006-12-12: ***
  a) get Addressing: ID into Rx or Tx table (Rx adr. type must be equal to Tx adr. type)
  b) read Frame, get direction (FC means Tx, otherwise Rx) and if so the TA
  c) no multiple usage of same FC PduId for several PduIds
     if(rx)
      if(standard):  ok: take the handle from a)
      if(extended):  getRxHdlExt(CanTpRxPduId, currentTA)
     if(tx)
      if(standard):  getTxHdl(CanTpRxPduId)
      if(extended):  getTxHdlExt(CanTpRxPduId, currentTA)   ***/

  errC = E_OK; 
  direction  = CANTP_RX;
  FrameType = kL4_InvalidFrameType;

# if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
  adrType = GetAddressingType(CanTpRxPduId);
  switch(adrType)
  {
# endif
# if( CANTP_STANDARD_ADDRESSING == STD_ON )
#  if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
    case CANTP_STANDARD:
#  endif
    { /* STANDARD ADDRESSING */
      FrameType = (uint8)((*pCanTpRxPduPtr->SduDataPtr) & kL4_FrameTypeMask);
      if(FrameType != kL4_FlowControl)
      { /* RX direction */
        SduHdl = GetRxSdu(CanTpRxPduId);
      }
      else
      { /* TX direction */
        direction   = CANTP_TX;
        SduHdl = GetTxSdu(CanTpRxPduId);
      }
    }
#  if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
    break;
#  endif
# endif

# if( CANTP_EXTENDED_ADDRESSING == STD_ON )
#  if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
    case CANTP_EXTENDED:
#  endif
    { /* EXTENDED ADDRESSING */
      currentTA = (uint8)(pCanTpRxPduPtr->SduDataPtr[0]);
      FrameType = (uint8)(pCanTpRxPduPtr->SduDataPtr[1] & kL4_FrameTypeMask);
      if(FrameType  != kL4_FlowControl)
      { /* RX direction */
        SduHdl = GetRxSduExt(CanTpRxPduId, currentTA);
      }
      else
      { /* TX direction */
        direction   = CANTP_TX;
        SduHdl = GetTxSduExt(CanTpRxPduId, currentTA);
      }
    }
#  if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
    break;
#  endif
# endif

# if( CANTP_MIXED11_ADDRESSING == STD_ON )
#  if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
    case CANTP_MIXED11:
#  endif
    { /* MIXED11 ADDRESSING */
      currentAE = (uint8)(pCanTpRxPduPtr->SduDataPtr[0]);
      FrameType = (uint8)(pCanTpRxPduPtr->SduDataPtr[1] & kL4_FrameTypeMask);

# if defined ( CANTP_ENABLE_DCM_REQUEST_DETECT )
      if( (FrameType == kL4_SingleFrame) || (FrameType == kL4_FirstFrame) )
      { /* indicate each SF or FF */
        Dcm_OnRequestDetection(CanTpRxPduId, currentAE);
      }
# endif

      if(FrameType != kL4_FlowControl)
      { /* RX direction */
        SduHdl = GetRxSduMixed11(CanTpRxPduId, currentAE);
      }
      else
      { /* TX direction */
        direction   = CANTP_TX;
        SduHdl = GetTxSduMixed11(CanTpRxPduId, currentAE);
      }
    }
#  if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
    break;
#  endif
# endif

# if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
    default:
      SduHdl = CANTP_INVALID_HDL;
      /* Do not report this DET error. With Multiple ECU configurations where this can happen, it should just be ignored
         vCanTp_DetReportError(CanTp_RxIndication_SId, CANTP_E_PARAM_CONFIG) */
    break;
# endif

# if( CANTP_MULTIPLE_ADDRESSING == STD_ON )
  } /* end switch */
# endif

  if((direction == CANTP_RX) && (SduHdl != CANTP_INVALID_HDL))
  { /* check for half duplex */
# if !defined( CANTP_RX__DUPLEX_MODE )
    if((vCanTp_PBCfgPtr(vCanTp_RxNsduCfg, SduHdl)).CANTP_DUPLEX_MODE == CANTP_MODE_HALF_DUPLEX)
# endif
    { /* check if a transmission is in progress */
# if ( CANTP_RX__ENABLE_HALF_DUPLEX_CHECK == STD_ON)
      PduIdType txHdl;
      txHdl = (vCanTp_PBCfg(vCanTp_RxNsduCfg, SduHdl, CANTP_TXNSDU_ID, CANTP_TX__TXNSDU_ID));
      if(txHdl != CANTP_INVALID_HDL) /* TaType == CanTp_Physical or Uni-directional */  /* PRQA S 3355 */ /* MD_CANTP_MISRA_3355 */ /* PRQA S 3358 */ /* MD_CANTP_MISRA_3358 */
      {
#  if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
        if(vCanTp_txHdlMap[txHdl] != CANTP_INVALID_HDL)
#  endif
        { /* found valid txHdl */
          if(vCanTp_TxState[TP_TX_HDL(txHdl)].ChannelState != cTxState_Idle)
          { /* Tx side seems to be busy - ignore reception */
            SduHdl = CANTP_INVALID_HDL;
          }
        }
      }
# endif /* CANTP_RX__ENABLE_HALF_DUPLEX_CHECK */
    } /* transmission in progress */
  }  /* endif half duplex */

  if(SduHdl != CANTP_INVALID_HDL)
  { 
# if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#  if( CANTP_PADDING_ACTIVE == STD_ON )
#   if( CANTP_RX__PADDING_ACTIVATION == STD_ON )
    if( (direction == CANTP_RX) && (pCanTpRxPduPtr->SduLength < cCanTp_FrameLength) ) { errC = E_NOT_OK; } /* A received N-PDU < 8 bytes is considered corrupt */
#   else
    if( (direction == CANTP_RX) && (pCanTpRxPduPtr->SduLength < (CANTP_RX__DL) ) )    { errC = E_NOT_OK; } /* A received N-PDU < minLength configured is considered corrupt */
#   endif
#   if( CANTP_TX__PADDING_ACTIVATION == STD_ON )
    if( (direction == CANTP_TX) && (pCanTpRxPduPtr->SduLength < cCanTp_FrameLength) ) { errC = E_NOT_OK; } /* A received FC N-PDU < 8 bytes is considered corrupt */
#   else
    if( (direction == CANTP_TX) && (pCanTpRxPduPtr->SduLength < (CANTP_TX__DL)))      { errC = E_NOT_OK; } /* A received FC N-PDU < minLength configured is considered corrupt */
#   endif
#  else
    /* without padding */
    if( ((direction == CANTP_RX) && (pCanTpRxPduPtr->SduLength < (CANTP_RX__DL)))  /* A received N-PDU < min. length configured is considered corrupt    */
    ||  ((direction == CANTP_TX) && (pCanTpRxPduPtr->SduLength < (CANTP_TX__DL)))) /* A received FC N-PDU < min. length configured is considered corrupt */
    { errC = E_NOT_OK; }
#  endif

# else /* CANTP_SINGLE_CONN_NOPB_OPTIMIZED */

#  if ( CANTP_PADDING_ACTIVE == STD_ON )
    if(direction == CANTP_RX)
    {
#   if( !defined(CANTP_RX__PADDING_ACTIVATION))
      if(vCanTp_PBCfg_RX__PADDING_ACTIVATION(SduHdl) == STD_ON)
#   endif
#   if(CANTP_CHECK_RX_PADDING == STD_ON)
      {
        if(pCanTpRxPduPtr->SduLength < cCanTp_FrameLength)
        {
          /* A received N-PDU < 8 bytes is considered corrupt */
          errC = E_NOT_OK;
        }
      }
#   endif
    }
    if(direction == CANTP_TX)
    {
#   if( !defined(CANTP_TX__PADDING_ACTIVATION))
      if(vCanTp_PBCfg_TX__PADDING_ACTIVATION(SduHdl) == STD_ON)
#   endif
#   if(CANTP_CHECK_TX_PADDING == STD_ON)
      {
        if(pCanTpRxPduPtr->SduLength < cCanTp_FrameLength)
        {
          /* A received FC N-PDU < 8 bytes is considered corrupt */
          errC = E_NOT_OK;
        }
      }
#   endif
    }
#  else /* CANTP_PADDING_ACTIVE */
    if(direction == CANTP_RX)
    {
      if(pCanTpRxPduPtr->SduLength < (vCanTp_PBCfg_RX__DL(SduHdl)))
      {
        /* A received N-PDU < min. length configured is considered corrupt */
        errC = E_NOT_OK;
      }
    }
    if(direction == CANTP_TX)
    {
      if(pCanTpRxPduPtr->SduLength < (vCanTp_PBCfg_TX__DL(SduHdl)))
      {
        /* A received FC N-PDU < min. length configured is considered corrupt */
        errC = E_NOT_OK;
      }
    }
#  endif /* CANTP_PADDING_ACTIVE */
# endif /* CANTP_SINGLE_CONN_NOPB_OPTIMIZED */
    if(errC != E_OK)
    { 
      vCanTp_DetReportError(CanTp_RxIndication_SId, CANTP_E_PARAM_CONFIG)
    }
    else
    {
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
      /* Got a correct SduHdl, now check for channel availability  */
      if(direction == CANTP_RX)
      { /* RX */
        Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);    /* CanTp_RxIndication */
        if( (vCanTp_rxHdlMap[SduHdl] == CANTP_INVALID_HDL) )
        { /* unused connection */

          if ( (FrameType == kL4_SingleFrame)  ||
               (FrameType == kL4_FirstFrame) )
          {
            tmpHdl = vCanTp_RxGetResource(SduHdl);
            Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* CanTp_RxIndication */
            if(tmpHdl != CANTP_INVALID_HDL)
            {
              vCanTp_CanIfRxIndication(SduHdl,  direction, pCanTpRxPduPtr);
            }
            /* else { No free rx SduHdl: ignore } */
          }
          else
          {
            /* no new connection need to be started - ignore frame */
            Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* CanTp_RxIndication */
          }
        }
        else 
        { /* used connection */
          Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* CanTp_RxIndication */
          vCanTp_CanIfRxIndication(SduHdl, direction, pCanTpRxPduPtr);
        }
      }
      else
      { /* TX */
        /* vCanTp_DetAssert((vCanTp_txHdlMap[SduHdl] != CANTP_INVALID_HDL), CanTp_RxIndication_SId, CANTP_E_UNINIT) (canceled due to unexpected FC receptions) */
        if( (vCanTp_txHdlMap[SduHdl] != CANTP_INVALID_HDL) )
        { /* the tx path must be available, allocation already done during FF reception  */
          vCanTp_CanIfRxIndication(SduHdl, direction, pCanTpRxPduPtr);
        }
      }
# else
#  if defined( CANTP_ENABLE_SINGLE_CONN )
      vCanTp_CanIfRxIndication(direction, pCanTpRxPduPtr);
#  else
      vCanTp_CanIfRxIndication(SduHdl, direction, pCanTpRxPduPtr);
#  endif
# endif
    }
  }
  else
  { /* No matching ID, ignore frame */
  }



} /* PRQA S 2006 */ /* MD_MSR_14.7 */  /* PRQA S 6010 */ /* MD_MSR_STPTH */  /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6050 */ /* MD_MSR_STCAL */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* vCanTp_RxIndication */
#endif


/**************************************************************************************************
   Function name    : vCanTp_CanIfTxConfirmation
   ------------------------------------------------------------------------------------------------
   Description      : This function is called by the CanIf (i.e. by vCanTp_TxConfirmation) 
                      in case a TP-frame has been transmitted successfully.
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself - Function vCanTp_TxConfirmation
   ------------------------------------------------------------------------------------------------
   Parameter        : CanTp-channel the Tx-confirmation belongs to 
   ------------------------------------------------------------------------------------------------
   Return code      : None.
   ------------------------------------------------------------------------------------------------
   Misc             : This function expects a crit. sect. to be active
**************************************************************************************************/
STATIC FUNC(void,  CANTP_CODE)   vCanTp_CanIfTxConfirmation(CANTP_HDL_PVAL_FIRST  vCanTp_operatingType dir)
{
  vCanTp_TpTxStatePtrType pTpTxState;
  vCanTp_TpRxStatePtrType pTpRxState;
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
# if( (CANTP_CONSTANT_RX__NBR == STD_ON) && (CANTP_CONSTANT_RX__NCR == STD_ON) && (CANTP_CONSTANT_RX__WFTMAX == STD_ON) )
# else
  P2CONST(vCanTp_RxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pRxNsduCfg;
# endif
# if( (CANTP_CONSTANT_TX__TA_TYPE == STD_ON) && (CANTP_CONSTANT_TX__NBS == STD_ON) )
# else
  P2CONST(vCanTp_TxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pTxNsduCfg;
# endif
#endif

  Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);  /* vCanTp_CanIfTxConfirmation */

  /*************
  * TX-channel *
  *************/

  pTpTxState = &vCanTp_TxState[TP_TX_HDL(tpHdl)];
#if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#else
  if( (TP_TX_HDL(tpHdl) == CANTP_INVALID_HDL) )
  { /* here we do not know the direction */
  }
  else
#endif
  {
#if defined( CANTP_ENABLE_SINGLE_CONN )
    if( (dir == CANTP_TX) )
    {
#else
    if(dir == CANTP_TX)
    {
      if(tpHdl == pTpTxState->channel)
#endif
      { /* Handle Tx confirmation */
#if( (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON) || ((CANTP_CONSTANT_TX__TA_TYPE == STD_ON) && (CANTP_CONSTANT_TX__NBS == STD_ON)) )
#else
        pTxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_TxNsduCfg, TPTXHDL));
#endif
        switch(pTpTxState->ChannelState)
        {
        case cTxState_WaitForSForFFConfIsr:
          if(pTpTxState->frameType == cCanTp_SF)
          { /* SF was TxConfirmed */
            vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_OK);
          }
          else
          { /* FF was TxConfirmed */
#if( CANTP_USE_ONLY_FIRST_FC == STD_ON )
            pTpTxState->firstFC = 0;
#endif

#if( !defined(CANTP_TX__TA_TYPE))
            if(CANTP_TX_CFG_PTR__TA_TYPE() == CANTP_PHYSICAL)
#endif
#if( (CANTP_CHECK_TX_TA_TYPE == CANTP_TAT_DYN) || (CANTP_CHECK_TX_TA_TYPE == CANTP_TAT_PHYS) )
            { /* 1:1 connection: Always wait for a FC */
              pTpTxState->Timer        = CANTP_TX_CFG_PTR__NBS();
              pTpTxState->ChannelState = cTxState_WaitFC;
            }
#endif
#if( !defined(CANTP_TX__TA_TYPE))
            else
#endif
#if( (CANTP_CHECK_TX_TA_TYPE == CANTP_TAT_DYN) || (CANTP_CHECK_TX_TA_TYPE == CANTP_TAT_FUNC) )
            { /* 1:n connection */
              vCanTp_DetReportError(CanTp_TxConfirmation_SId, CANTP_E_PARAM_CONFIG)
            }
#endif
          }
          break;
        case cTxState_WaitForCFConfIsr:
          /* CF was TxConfirmed */
          vCanTp_TxCFTxConfirmation(CANTP_HDL_CVAL_ONLY);
          break;

        default:
          /* leave without any changes to internal states
             used e.g. if a transmit cancellation appeared */
          break;
        }  /* switch( ChannelState ) */
      } /* if(tpHdl == pTpTxState->channel) */
    } /* if(dir == CANTP_TX) */
  } /* end else */


  /*************
  * RX-channel *
  *************/
#if defined( CANTP_ENABLE_SINGLE_CONN )
#else
  if( (TP_RX_HDL(tpHdl) == CANTP_INVALID_HDL) )
  {  /* here we do not know the direction */
  }
  else
#endif
  {
    pTpRxState = &vCanTp_RxState[TP_RX_HDL(tpHdl)];
    if(dir == CANTP_RX)
    {
#if defined( CANTP_ENABLE_SINGLE_CONN )
#else
      if(tpHdl == pTpRxState->channel)
#endif
      { /* Handle RxConfirmation */
#if( (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON) || ((CANTP_CONSTANT_RX__NBR == STD_ON) && (CANTP_CONSTANT_RX__NCR == STD_ON) && (CANTP_CONSTANT_RX__WFTMAX == STD_ON)) )
#else
        pRxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_RxNsduCfg, TPRXHDL));
#endif
        {
          switch(pTpRxState->ChannelState)
          {
          case cRxState_WaitForFCConfIsr:
            /* Wait for next CF, reset SN */
            pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NCR(tpHdl);
            pTpRxState->WFTCounter   = CANTP_RX1_CFG_PTR__WFTMAX(tpHdl);  /* re-init wait frame counter */
            pTpRxState->ChannelState = cRxState_WaitCF;
            break;

          case cRxState_WaitForFCWaitConfIsr:
            /* After Tx confirmation of a FC.WT: decr. wait frame counter */
            vCanTp_DetAssert((pTpRxState->WFTCounter >= 1), vCanTp_CanIfTxConfirmation_Sid, (CANTP_E_PARAM_CONFIG))
            pTpRxState->WFTCounter--; 
            /* Prepare getting a buffer */
            pTpRxState->Timer = (((CANTP_RX1_CFG_PTR__NBR(tpHdl) << 2) + 1) / 5); /* see CanTp222 */
            pTpRxState->ChannelState = cRxState_WaitForFCWait;
            break;

          case cRxState_WaitForFCOverConfIsr:
            /* Stop receiving frames on this tpConn */
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
            break;

          default:
            /* leave without any changes to internal states 
               used e.g. if a transmit cancellation appeared */
            break; 
          } /* switch( ChannelState ) */
        }
      } /* if(tpHdl == pTpRxState->channel) */
    } /* if(dir == CANTP_RX) */
    else {  }
  } /* else if( (TP_RX_HDL(tpHdl) == CANTP_INVALID_HDL) )*/
  Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* vCanTp_CanIfTxConfirmation */
} /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* vCanTp_CanIfTxConfirmation */

/**************************************************************************************************
   Function name    : CanTp_MainFunctionTx
   ------------------------------------------------------------------------------------------------
   Description      : Central timer task of the Tx-part of all (full duplex) channels
                      Tasks are to survey transmit timing conditions + transmit CanTp-frames
                      Cyclical called function.
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp_MainFunction itself (After all: OS or application)
   ------------------------------------------------------------------------------------------------
   Parameter        : void
   ------------------------------------------------------------------------------------------------
   Returncode       : void
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
#if( CANTP_RXTX_MAINFUNCTION_API == STD_ON )
/* PRQA S 3408 3 */ /* RULE 8.8: External linkage defined without previous definition due to generated code.
                                  For AR4 the SchM_CanTp.h contains the prototypes for the main funktions ([rte_sws_7283]) */
FUNC(void,  CANTP_CODE)   CanTp_MainFunctionTx(void)
#else
STATIC FUNC(void,  CANTP_CODE)   CanTp_MainFunctionTx(void)
#endif
{
#if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#else
  VAR(PduIdType, AUTOMATIC)       tpHdl;
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
  vCanTp_VolatileTpTxHdlMapPtrType pTxHdlMap;
# endif
#endif
  VAR(BufReq_ReturnType, AUTOMATIC) retc;
#if ( (CANTP_TX_SERIALIZE == STD_ON) && (CANTP_TX_SINGLE_SERIALIZE == STD_OFF) )
  VAR(uint8, AUTOMATIC)             tmp;
#endif

#if( CANTP_IDENTITY_MANAGER_CONFIG == STD_ON )
  if(vCanTp_LData(InitState) != cCanTp_Initialized)
  {
    return;
  }
#else
  vCanTp_DetAssertVReturn(vCanTp_LData(InitState) == cCanTp_Initialized, CanTp_MainFunctionTx_SId, CANTP_E_UNINIT)
#endif

#if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#else
  tpHdl = vCanTp_PBCfgPtr_(NumCanTpTxSduId);
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
  pTxHdlMap = vCanTp_txHdlMap;
# endif
  while(tpHdl > 0)
  {
    tpHdl--;
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
    if(pTxHdlMap[tpHdl] == CANTP_INVALID_HDL)
    {
      continue;  /* PRQA S 0770 */ /* MD_CANTP_MISRA_0770 */
    }
# endif
    Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_1);  /* CanTp_MainFunctionTx */
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
    if(pTxHdlMap[tpHdl] == CANTP_INVALID_HDL)
    {
      Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_1);  /* CanTp_MainFunctionTx */
      continue;  /* PRQA S 0770 */ /* MD_CANTP_MISRA_0770 */
    }
# endif
#endif

    if(vCanTp_TxState[TP_TX_HDL(tpHdl)].Timer != 0)
    { /* Channel is used */
      vCanTp_TpTxStatePtrType pTpTxState;
      pTpTxState = &vCanTp_TxState[TP_TX_HDL(tpHdl)];
      pTpTxState->Timer--;
      if(pTpTxState->TimerSTMin > 0) 
      { 
        (pTpTxState->TimerSTMin)--; 
      }

      if(pTpTxState->Timer == 0)
      { /* Timeout */
        switch(pTpTxState->ChannelState)
        {
        case cTxState_WaitFC:
        {
          /* FC Timeout occurred, i.e. CANTP_NBS went by after a FF */
#if ( CANTP_GW_ERRORS_REPORT_DEM == STD_ON)
          /* report gateway specific DEM error */
          if (pTpTxState->frameType == cCanTp_FF)
          {
            vCanTp_DemReportError(CanTp_E_Gw_Ecu_Missing, DEM_EVENT_STATUS_FAILED)
          }
#endif

          vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_TIMEOUT_BS);

          break;
        }

        case cTxState_WaitForTpTxCF:
        {
          if(pTpTxState->bufState == BUFREQ_OK)
          { /* Timer expired (STMIN has passed) */
#if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
            pTpTxState->Timer        = vCanTp_PBCfg_TX__NAS(0);
#else
            pTpTxState->Timer        = vCanTp_PBCfg_TX__NAS(tpHdl);
#endif
            pTpTxState->ChannelState = cTxState_WaitForCFConfIsr;
            pTpTxState->queued++;
            vCanTp_TxStateTask(CANTP_TX_HDL_CVAL_ONLY); /* Try first transmission right now */
          }
          else
          { /* this condition should never be reached */
            vCanTp_Error(CanTp_MFuncTx_SId, CANTP_WRONG_STATE, (((uint32)TPTXHDL) | (((uint32)(pTpTxState->bufState)) << 8) ))
          }
          break;
        }

        case cTxState_WaitForTxBuffer:
          retc = vCanTp_TxRetrieveApplTxBuffer(CANTP_TX_HDL_CVAL_ONLY);
          if(retc == BUFREQ_E_BUSY)
          {
            vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER);
          }
          break;

        case cTxState_WaitForSForFFConfIsr:
        case cTxState_WaitForCFConfIsr:
          /* Timeout of the TxConfirmation of a SF, FF or CF */
          vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_TIMEOUT_A);
#if ( CANTP_TX_SERIALIZE == STD_ON )
          /* Initialize transmit semaphore, all further processing on other 'channels' is handled from task level */
# if ( CANTP_TX_SINGLE_SERIALIZE == STD_ON )
# else
          vCanTp_TxConflict.wrpos = 0;
          vCanTp_TxConflict.rdpos = 0;
          tmp = (CANTP_TX_MAX_NUM_CONFLICT);
          while(tmp > 0)
          { /* re-initialize completely */
            tmp--;
            vCanTp_TxConflict.hdl[tmp] = CANTP_INVALID_HDL;
          }
# endif
#endif
          break;

        default:
          vCanTp_Error(CanTp_MFuncTx_SId, CANTP_WRONG_STATE, (((uint32)TPTXHDL) | (((uint32)(pTpTxState->ChannelState)) << 8) ))
          break;
        } /* End of "switch(txState())"*/
      } /* timeout */
      else
      { /* No timeout */
        /* a buffer request on task level may be pending if                                   */
        /* - segmented buffers are supported or                                               */
        /* - buffer request is done asynchronously (not in the context of CanTp_Transmit)  or */
        /* - the initial request returned a buffer with status "busy"                         */
        if(pTpTxState->ChannelState == cTxState_WaitForTxBuffer)
        {
          (void)vCanTp_TxRetrieveApplTxBuffer(CANTP_TX_HDL_CVAL_ONLY);
        }
        else
        {
          if(pTpTxState->bufState == BUFREQ_OK)  /* redundant: || ((pTpTxState->bufState == BUFREQ_E_BUSY) && (pTpTxState->ChannelState == cTxState_WaitForTxBuffer)) */
          { /* Buffer available or in process of being retrieved */
            /* Now try sending until the state is on "wait for sth." */
            vCanTp_TxStateTask(CANTP_TX_HDL_CVAL_ONLY);
          }
          else
          { /* We'll run into the next buffer retrieval or into a timeout */
            vCanTp_Error(CanTp_MFuncTx_SId, CANTP_WRONG_STATE, (((uint32)TPTXHDL) | (((uint32)(pTpTxState->bufState)) << 8) ))
          }
        }
      }

    } /* pChannel in use */
#if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#else
    Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_1);  /* CanTp_MainFunctionTx */
  } /* for loop ( all channels ) */
#endif
} /* PRQA S 2006 */ /* MD_MSR_14.7 */ /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6080 */ /* MD_MSR_STMIF */  /* PRQA S 6010 */ /* MD_MSR_STPTH */
/* CanTp_MainFunctionTx */

/**************************************************************************************************
   Function name    : vCanTp_TxRetrieveApplTxBuffer
   ------------------------------------------------------------------------------------------------
   Description      : Central interface to application to get a buffer with Tx-data
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself
   ------------------------------------------------------------------------------------------------
   Parameter        : uint8 tpHdl
   ------------------------------------------------------------------------------------------------
   Returncode       : void
   ------------------------------------------------------------------------------------------------
   Misc             : Expects to be called in "critical section"
**************************************************************************************************/
#if defined( CANTP_ENABLE_PDUR_API40 )
STATIC FUNC(BufReq_ReturnType,  CANTP_CODE)   vCanTp_TxRetrieveApplTxBuffer(CANTP_HDL_CPVAL_ONLY)
{
  VAR(BufReq_ReturnType, AUTOMATIC)               bReq;
  VAR(PduInfoType, AUTOMATIC)                     PduInfo;
  VAR(PduLengthType, AUTOMATIC)                   TxDataCnt;
  VAR(PduLengthType, AUTOMATIC)                   frmLen;
  vCanTp_TpTxStatePtrType pTpTxState;
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
  P2CONST(vCanTp_TxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pTxNsduCfg;
  pTxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_TxNsduCfg, TPTXHDL));
#endif
#if( (CANTP_SINGLE_CONN_OPTIMIZED == STD_ON) && (CANTP_NUM_RX_CHANNELS >= 2) ) 
# if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)tpHdl; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
# endif
#endif

  pTpTxState = &vCanTp_TxState[TP_TX_HDL(tpHdl)];
  bReq = BUFREQ_E_NOT_OK;

#if (CANTP_TX_FULL_BUFFER_PROVISION == STD_ON)
  PduInfo.SduDataPtr = &vCanTp_txBuf[TP_TX_HDL(tpHdl)][pTpTxState->FrameIndex];
  /* Handle segmented Tx-buffer retrieval */
  if( (pTpTxState->providedDataLength > 0)  &&
     ((pTpTxState->providedDataLength + pTpTxState->FrameIndex) <  vCanTp_txGetPayloadLen(TPTXHDL, pTpTxState->frameType)) &&
     ((pTpTxState->providedDataLength + pTpTxState->FrameIndex) <= (pTpTxState->DataLength - pTpTxState->OverallDataIndex))
    )
  { /* Too few bytes left: store remaining fragment (new buffer needed AND remaining buffer too less for current frameType ) */
    PduInfo.SduLength  = pTpTxState->providedDataLength;
    /* copy fragment to internal buffer */
    /* CANTP272:  ISO  15765-2  does  not  support  such  a mechanism,  the  CANTP  does  not  implement  any  kind  of  recovery. 
                  Thus, the parameter is always set to TP_NORETRY and upper layers can return a buffer of free length. */
    /* PRQA S 3335 QAC_L11 */ /* RULE 8.1: Declaration available via macro redefinition. */
# if ( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON )
    bReq = vCanTp_TxApplCopyTxData(CANTP_TX_CFG_PTR(CANTP_REMAP_TXNSDU_ID, CANTP_TX__REMAP_TXNSDU_ID),
                                  &PduInfo,
                                   NULL_PTR,  /* PduRetryInfo->TpDataState = TP_NORETRY is not supported for CanTp (see PduR V3.0.0 AR4.0 Rev1 PDUR518) */
                                  &TxDataCnt);
# else
    bReq = vCanTp_TxApplCopyTxData(CANTP_TX_CFG_PTR(CANTP_TXNSDU_ID, CANTP_TX__TXNSDU_ID),
                                  &PduInfo,
                                   NULL_PTR,  /* PduRetryInfo->TpDataState = TP_NORETRY is not supported for CanTp (see PduR V3.0.0 AR4.0 Rev1 PDUR518) */
                                  &TxDataCnt);
# endif
    /* PRQA  L:QAC_L11 */
    vCanTp_DetAssertReturn(bReq == BUFREQ_OK, vCanTp_TxRetrieveApplTxBuffer_SId, CANTP_E_INVALID_TX_BUFFER, BUFREQ_E_NOT_OK)

    /* Recognize the fragment length and reset the providedLength */
    pTpTxState->FrameIndex         = (PduLengthType)(pTpTxState->FrameIndex + pTpTxState->providedDataLength);
    pTpTxState->providedDataLength = TxDataCnt;
    /* update buffer pointer */
    PduInfo.SduDataPtr = &vCanTp_txBuf[TP_TX_HDL(tpHdl)][pTpTxState->FrameIndex];
  }  /* endif fragment available */
#else
#endif

  if(pTpTxState->frameType == cCanTp_SF)
  {
    frmLen = pTpTxState->DataLength;
  }
  else
  {
    frmLen = vCanTp_txGetPayloadLen(TPTXHDL, (pTpTxState->frameType));
    if(pTpTxState->frameType == cCanTp_CF)
    {
      if(frmLen > (pTpTxState->DataLength - pTpTxState->OverallDataIndex) )
      {
        frmLen = pTpTxState->DataLength - pTpTxState->OverallDataIndex;
      }
    }
  }

  PduInfo.SduLength = frmLen - pTpTxState->FrameIndex;
  if(pTpTxState->providedDataLength < PduInfo.SduLength)
  { /* reduce to available buffer size */
    PduInfo.SduLength  = pTpTxState->providedDataLength;
  }

  if(PduInfo.SduLength == 0)
  {
    /* PRQA S 3335 QAC_L12 */ /* RULE 8.1: Declaration available via macro redefinition. */
#if ( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON )
    bReq = vCanTp_TxApplCopyTxData(CANTP_TX_CFG_PTR(CANTP_REMAP_TXNSDU_ID, CANTP_TX__REMAP_TXNSDU_ID),
                                  &PduInfo,
                                   NULL_PTR,  /*  PduRetryInfo->TpDataState = TP_NORETRY is not supported for CanTp (see PduR V3.0.0 AR4.0 Rev1 PDUR518) */
                                  &(TxDataCnt));
#else
    bReq = vCanTp_TxApplCopyTxData(CANTP_TX_CFG_PTR(CANTP_TXNSDU_ID, CANTP_TX__TXNSDU_ID),
                                  &PduInfo,
                                   NULL_PTR,  /*  PduRetryInfo->TpDataState = TP_NORETRY is not supported for CanTp (see PduR V3.0.0 AR4.0 Rev1 PDUR518) */
                                  &(TxDataCnt));
#endif
    /* PRQA  L:QAC_L12 */
    if(bReq == BUFREQ_OK)
    {
      pTpTxState->providedDataLength = (PduLengthType)(TxDataCnt);
    }
  }

  PduInfo.SduLength = frmLen;
  if(pTpTxState->providedDataLength < PduInfo.SduLength)
  { /* reduce requested length to available buffer size */
    PduInfo.SduLength = pTpTxState->providedDataLength;
  }

  switch(bReq)
  {
  case BUFREQ_OK:
  {
    pTpTxState->bufState = BUFREQ_OK;
    if((PduInfo.SduLength + pTpTxState->FrameIndex) >= (frmLen))
    { /* At least one CAN frame can be filled up */
      pTpTxState->Timer = CANTP_TX_CFG_PTR__NAS();
      pTpTxState->queued++;
      pTpTxState->DataIndex = 0;
      if(pTpTxState->frameType == cCanTp_CF)
      {
        if( (pTpTxState->TimerSTMin < 1) )
        {
          pTpTxState->ChannelState = cTxState_WaitForCFConfIsr;
          vCanTp_TxStateTask(CANTP_TX_HDL_CVAL_ONLY);
        }
        else
        {
          pTpTxState->Timer = pTpTxState->TimerSTMin;
          pTpTxState->ChannelState = cTxState_WaitForTpTxCF;
        }
      }
      else
      {
        pTpTxState->ChannelState = cTxState_WaitForSForFFConfIsr;
        vCanTp_TxStateTask(CANTP_TX_HDL_CVAL_ONLY);
      }
    }
    else 
    { 
      /* Handle segmented Tx-buffer retrieval */
      /* Too few bytes left: store remaining fragment(new buffer needed AND remaining buffer too less for current frameType ) */
      if(pTpTxState->providedDataLength > 0)
      { /* at least one byte has been provided */
        pTpTxState->Timer = CANTP_TX_CFG_PTR__NCS();
      }
      else
      {
        bReq = BUFREQ_E_BUSY;
      }
    }
    break;
  }

  case BUFREQ_E_BUSY:
    /* CANTP279: If upper layer temporarily has no Tx buffer available, the PduR_CanTpCopyTxData() function returns BUFREQ_E_BUSY.
       CANTP184: If the PduR_CanTpCopyTxData() function returns BUFREQ_E_BUSY, the CanTp module shall later (implementation specific) retry to receive a buffer.
       CANTP185: If no buffer is provided before the expiration of the N_Cs timer the CanTp module shall abort this transmission session.
       CANTP280: If buffer is not available within N_Cs timeout the CanTp module shall notify the upper layer by calling PduR_CanTpTxConfirmation with the result NTFRSLT_E_NOT_OK.
       CANTP089: When the Tx buffer is provided, the CanTp module shall resume the transmission of the N-SDU. */
    if(pTpTxState->bufState == BUFREQ_E_BUSY)
    { /* just wait for getting more buffer or until timeout appears */
    }
    else
    { /* CanTp167: after timeout give up, but anyway the next try is within the next cycle */
      pTpTxState->Timer = (CANTP_TX_CFG_PTR__NCS());   /* see CanTp:167 */
      pTpTxState->bufState = BUFREQ_E_BUSY;
    }
    break;

  case BUFREQ_E_NOT_OK:
    vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER);
    break;

  case BUFREQ_E_OVFL:
  default:
    /* buffer status not supported */
#if(CANTP_OPER_NOT_SUPPORTED_REPORT_DEM == STD_ON)
    vCanTp_DemReportError(CanTp_E_Oper_Not_Supported, DEM_EVENT_STATUS_FAILED)
#else  /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */
    vCanTp_DetReportError(vCanTp_TxRetrieveApplTxBuffer_SId, CanTp_E_Oper_Not_Supported)
#endif /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */

    vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST (NotifResultType)NTFRSLT_E_NO_BUFFER);
    break;
  } /* switch(bReq) */

  return(bReq);
}
#else /* (CANTP_ENABLE_PDUR_API40 == STD_OFF) */

STATIC FUNC(BufReq_ReturnType,  CANTP_CODE)   vCanTp_TxRetrieveApplTxBuffer(CANTP_HDL_CPVAL_ONLY)
{
  VAR(BufReq_ReturnType, AUTOMATIC) bReq;
  VAR(uint16, AUTOMATIC)            minLen;
  vCanTp_TpTxStatePtrType           pTpTxState;
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
  P2CONST(vCanTp_TxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pTxNsduCfg;
  pTxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_TxNsduCfg, TPTXHDL));
#endif
#if( (CANTP_SINGLE_CONN_OPTIMIZED == STD_ON) && (CANTP_NUM_RX_CHANNELS >= 2) ) 
  (void)tpHdl; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
#endif

  pTpTxState = &vCanTp_TxState[TP_TX_HDL(tpHdl)];
#if (CANTP_TX_FULL_BUFFER_PROVISION == STD_ON)
  /* Handle segmented Tx-buffer retrieval */
  if( (pTpTxState->providedDataLength > 0)    && 
     ((pTpTxState->providedDataLength + pTpTxState->FrameIndex) <  vCanTp_txGetPayloadLen(TPTXHDL, pTpTxState->frameType))     &&
     ((pTpTxState->providedDataLength + pTpTxState->FrameIndex) < (pTpTxState->DataLength - pTpTxState->OverallDataIndex))
    )
  { /* Too few bytes left: store remaining fragment
      (new buffer needed AND remaining buffer too less for current frameType ) */
    uint8_least tmp;
    for(tmp = 0; tmp < pTpTxState->providedDataLength; tmp++)
    {
      vCanTp_txBuf[TP_TX_HDL(tpHdl)][tmp + pTpTxState->FrameIndex] = pTpTxState->DataBufferPtr[pTpTxState->DataIndex + tmp];
    } 
    /* Recognize the fragment length and reset the providedLength */
    pTpTxState->FrameIndex         = (PduLengthType)(pTpTxState->FrameIndex + pTpTxState->providedDataLength);
    pTpTxState->providedDataLength = 0;
    /* Deliver the real number of bytes taken from the provided buffer */
    pTpTxState->ApplPduInfoPtr->SduLength = (pTpTxState->DataIndex) + (pTpTxState->FrameIndex);
  }

  minLen = 0;                       /* if minLen == 0 then arbitrary size (but > 0) may be provided */
#else
  minLen = pTpTxState->DataLength;  /* Exact length of the requested transmit buffer */
#endif

#if ( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON )
  bReq   = vCanTp_TxApplProvideTxBuffer(tpHdl, 
                                        CANTP_TX_CFG_PTR(CANTP_REMAP_TXNSDU_ID, CANTP_TX__REMAP_TXNSDU_ID),
                                        (P2VAR(PduInfoTypeCanTpApplDataPtr, AUTOMATIC, CANTP_APPL_DATA)) (&pTpTxState->ApplPduInfoPtr),
                                        minLen); /* if minLen == 0 then arbitrary size (but > 0) may be provided, otherwise  */
                                                 /* the exact length of the requested transmit buffer must be provided.      */
#else
  bReq   = vCanTp_TxApplProvideTxBuffer(tpHdl, 
                                        CANTP_TX_CFG_PTR(CANTP_TXNSDU_ID, CANTP_TX__TXNSDU_ID),
                                        (P2VAR(PduInfoTypeCanTpApplDataPtr, AUTOMATIC, CANTP_APPL_DATA)) (&pTpTxState->ApplPduInfoPtr),
                                        minLen); /* if minLen == 0 then arbitrary size (but > 0) may be provided, otherwise  */
                                                 /* the exact length of the requested transmit buffer must be provided.      */
#endif

  switch(bReq)
  {
  case BUFREQ_OK:
  {
    vCanTp_DetAssert((pTpTxState->ApplPduInfoPtr != NULL_PTR), vCanTp_TxRetrieveApplTxBuffer_SId, CANTP_E_INVALID_TX_BUFFER)
    pTpTxState->bufState = BUFREQ_OK;
    if(pTpTxState->ApplPduInfoPtr != NULL_PTR)
    {
      /* we got a buffer; assert validity */
      vCanTp_DetAssert((pTpTxState->ApplPduInfoPtr->SduDataPtr != NULL_PTR), vCanTp_TxRetrieveApplTxBuffer_SId, CANTP_E_INVALID_TX_BUFFER)

#if (CANTP_TX_FULL_BUFFER_PROVISION == STD_ON)
      if((pTpTxState->ApplPduInfoPtr->SduDataPtr != NULL_PTR) && (pTpTxState->ApplPduInfoPtr->SduLength  >  minLen))
#else
      if((pTpTxState->ApplPduInfoPtr->SduDataPtr != NULL_PTR) && (pTpTxState->ApplPduInfoPtr->SduLength  >=  pTpTxState->DataLength))
#endif
      {
        /* Copy PduInfo from appl. to internal structures */
        pTpTxState->DataBufferPtr      = pTpTxState->ApplPduInfoPtr->SduDataPtr;
        pTpTxState->providedDataLength = pTpTxState->ApplPduInfoPtr->SduLength;
#if (CANTP_TX_FULL_BUFFER_PROVISION == STD_ON)
        if(((pTpTxState->providedDataLength + pTpTxState->FrameIndex) >= vCanTp_txGetPayloadLen(TPTXHDL, pTpTxState->frameType)) ||
           ((pTpTxState->providedDataLength + pTpTxState->FrameIndex) >= (pTpTxState->DataLength - pTpTxState->OverallDataIndex))
          )
#endif
        { /* At least one CAN frame can be filled up */
          /* SduLength is reset to '0' in order to increment it during transmission */
          pTpTxState->ApplPduInfoPtr->SduLength = 0;
          pTpTxState->queued++;
          pTpTxState->DataIndex = 0;
          if(pTpTxState->frameType == cCanTp_CF)
          {
            if( (pTpTxState->TimerSTMin == 0) || (pTpTxState->STMin == 0) )
            {
              pTpTxState->Timer = CANTP_TX_CFG_PTR__NAS();
              pTpTxState->ChannelState = cTxState_WaitForCFConfIsr;
              vCanTp_TxStateTask(CANTP_TX_HDL_CVAL_ONLY);
            }
            else
            {
              pTpTxState->Timer = pTpTxState->TimerSTMin;
              pTpTxState->ChannelState = cTxState_WaitForTpTxCF;
            }
          }
          else
          {
            pTpTxState->Timer = CANTP_TX_CFG_PTR__NAS();
            pTpTxState->ChannelState = cTxState_WaitForSForFFConfIsr;
            vCanTp_TxStateTask(CANTP_TX_HDL_CVAL_ONLY);
          }
        }
#if (CANTP_TX_FULL_BUFFER_PROVISION == STD_ON)
        else 
        {   /* Handle segmented Tx-buffer retrieval */
          { /* Too few bytes left: store remaining fragment
              (new buffer needed AND remaining buffer too less for current frameType ) */
            uint8_least tmp;
            for(tmp = 0; tmp < pTpTxState->providedDataLength; tmp++)
            {
              vCanTp_txBuf[TP_TX_HDL(tpHdl)][tmp + pTpTxState->FrameIndex] = pTpTxState->DataBufferPtr[tmp];
            } 
            /* Recognize the fragment length and reset the providedLength */
            pTpTxState->FrameIndex         = (PduLengthType)(pTpTxState->FrameIndex + pTpTxState->providedDataLength);
            pTpTxState->providedDataLength = 0;
          }
          pTpTxState->queued++;
          pTpTxState->Timer = (CANTP_TX_CFG_PTR__NCS());    /* see CanTp:167 */
        }
#endif
      }
      else
      { /* Buffer not large enough */
        bReq = BUFREQ_E_NOT_OK;
        vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER);
      }
    }
    else
    { /* No buffer provided */
      bReq = BUFREQ_E_NOT_OK;
      vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER);
    }
    break;
  }


  case BUFREQ_E_BUSY:
    if(pTpTxState->bufState == BUFREQ_E_BUSY)
    { /* just wait for getting more buffer or until timeout appears */
    }
    else
    { /* CanTp167: after timeout give up, but anyway the next try is within the next cycle */
      pTpTxState->Timer = (CANTP_TX_CFG_PTR__NCS());   /* see CanTp:167 */
      pTpTxState->bufState = BUFREQ_E_BUSY;
    }
    break;


  case BUFREQ_E_NOT_OK:
    vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER);
    break;


  case BUFREQ_E_OVFL:
  default:
    /* buffer status not supported */
#if(CANTP_OPER_NOT_SUPPORTED_REPORT_DEM == STD_ON)
    vCanTp_DemReportError(CanTp_E_Oper_Not_Supported, DEM_EVENT_STATUS_FAILED)
#else  /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */
    vCanTp_DetReportError(vCanTp_TxRetrieveApplTxBuffer_SId, CanTp_E_Oper_Not_Supported)
#endif /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */

    vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST (NotifResultType)NTFRSLT_E_NO_BUFFER);
    break;
  } /* switch(bReq) */

  return(bReq);
} /* PRQA S 6010 */ /* MD_MSR_STPTH */  /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* vCanTp_TxRetrieveApplTxBuffer */
#endif /* (CANTP_ENABLE_PDUR_API40) */

/**************************************************************************************************
   Function name    : CanTp_MainFunctionRx
   ------------------------------------------------------------------------------------------------
   Description      : Central timer task of the Rx-part of all (fullduplex) channels
                      Task is to survey receive timing conditions
                      Cyclical called function
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp_MainFunction itself (After all: OS or application)
   ------------------------------------------------------------------------------------------------
   Parameter        : void
   ------------------------------------------------------------------------------------------------
   Returncode       : void
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
#if( CANTP_RXTX_MAINFUNCTION_API == STD_ON )
/* PRQA S 3408 3 */ /* RULE 8.8: External linkage defined without previous definition due to generated code.
                                  For AR4 the SchM_CanTp.h contains the prototypes for the main funktions ([rte_sws_7283]) */
FUNC(void,  CANTP_CODE)   CanTp_MainFunctionRx(void)
#else
STATIC FUNC(void,  CANTP_CODE)   CanTp_MainFunctionRx(void)
#endif
{
#if defined( CANTP_ENABLE_SINGLE_CONN )
#else
  VAR(PduIdType, AUTOMATIC) tpHdl;
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
  vCanTp_VolatileTpRxHdlMapPtrType pRxHdlMap;
# endif
#endif
#if ( (CANTP_TX_SERIALIZE == STD_ON) && (CANTP_TX_SINGLE_SERIALIZE == STD_OFF) )
  VAR(uint8, AUTOMATIC)             tmp;
#endif

#if( CANTP_IDENTITY_MANAGER_CONFIG == STD_ON )
  if(vCanTp_LData(InitState) != cCanTp_Initialized)
  {
    return;
  }
#else
  vCanTp_DetAssertVReturn(vCanTp_LData(InitState) == cCanTp_Initialized, CanTp_MainFunctionRx_SId, CANTP_E_UNINIT)
#endif

#if( CANTP_ENABLE_CHANGE_PARAM == STD_ON )
  if(vCanTp_changeParamConfResult != NTFRSLT_OK)
  {
    /* PRQA S 3335 QAC_L13 */ /* RULE  8.1 : Declaration available via macro redefinition. */
    /* PRQA S 3200 QAC_L13 */ /* RULE 16.10: This unused return value depends on the unrecognized declaration. */
    vCanTp_RxApplChangeParamConfirmation((vCanTp_changeParamConfId), (vCanTp_changeParamConfResult));
    /* PRQA  L:QAC_L13 */
    vCanTp_changeParamConfResult = NTFRSLT_OK;
  }
#endif

#if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
# if( CANTP_NUM_RX_CHANNELS == 1 )
# else
  /* Iterate through all channels */
  tpHdl = CANTP_NUM_RX_CHANNELS;
  while(tpHdl > 0)
  { /* Is the channel idle or a communication running (timer running means communication running) */
    tpHdl--;
    Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_1);  /* CanTp_MainFunctionRx */
# endif
#else
  /* Iterate through all channels */
  tpHdl = vCanTp_PBCfgPtr_(NumCanTpRxSduId);
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
  pRxHdlMap = vCanTp_rxHdlMap;
# endif
  while(tpHdl > 0)
  { /* Is the channel idle or a communication running (timer running means communication running) */
    tpHdl--;
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
    if(pRxHdlMap[tpHdl] == CANTP_INVALID_HDL)
    {
      continue;  /* PRQA S 0770 */ /* MD_CANTP_MISRA_0770 */
    }
# endif
    Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_1);  /* CanTp_MainFunctionRx */
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
    if(pRxHdlMap[tpHdl] == CANTP_INVALID_HDL)
    {
      Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_1);  /* CanTp_MainFunctionRx */
      continue;  /* PRQA S 0770 */ /* MD_CANTP_MISRA_0770 */
    }
# endif
#endif

    if(vCanTp_RxState[TP_RX_HDL(tpHdl)].Timer != 0)
    { /* Channel is used! */   
      vCanTp_TpRxStatePtrType pTpRxState;
      pTpRxState = &vCanTp_RxState[TP_RX_HDL(tpHdl)];
      pTpRxState->Timer--;
      if(pTpRxState->Timer == 0)
      { /* timeout reached */
        switch(pTpRxState->ChannelState)
        {
        case cRxState_WaitCF:
        {
          vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_TIMEOUT_CR, cCanTp_Initialize);
          break;
        }
        
        case cRxState_WaitForFCConfIsr:
        case cRxState_WaitForFCOverConfIsr:
        case cRxState_WaitForFCWaitConfIsr:
        { /* FC confirmation Timeout */
          if(pTpRxState->bufState == BUFREQ_E_NOT_OK)
          { /* Coming here after: rxBufferProvision returned NO_BUFFER and thus 
                                  sending a FC(OVFL) and 
                                  missing confirmation. */
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
          }
          else
          {
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_TIMEOUT_A, cCanTp_Initialize);
          }
#if ( CANTP_TX_SERIALIZE == STD_ON )
# if ( CANTP_TX_SINGLE_SERIALIZE == STD_ON )
# else
          /* Initialize completely, all further processing on other 'channels' is handled from task level */
          vCanTp_TxConflict.wrpos = 0;
          vCanTp_TxConflict.rdpos = 0;
          tmp = (CANTP_TX_MAX_NUM_CONFLICT);
          while(tmp > 0)
          { /* re-initialize completely */
            tmp--;
            vCanTp_TxConflict.hdl[tmp] = CANTP_INVALID_HDL;
          }
# endif
#endif
          break;
        }

        case cRxState_WaitForFCWait:
        { /* FC(WT) was confirmed, now do another try */
          if(pTpRxState->WFTCounter == 0)
          { /* WFTmax reached (CanTp223) */
#if defined ( CANTP_AUTOSARVERSION4 )
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_WFT_OVRN, cCanTp_Initialize);
# else
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NOT_OK, cCanTp_Initialize);
# endif
          }
          else 
          { /* Time for next buffer request towards the application */
            pTpRxState->Timer = 1;
            pTpRxState->ChannelState = cRxState_WaitForRxBuffer;
#if( CANTP_RX_GET_BUFFER_FROM_ISR == STD_ON )
            vCanTp_RxRetrieveApplRxBuffer(CANTP_HDL_CVAL_ONLY);
#endif
          }
          break;
        }

        case cRxState_WaitForRxBuffer:
          if( (pTpRxState->DataIndex + pTpRxState->FrameIndex) >= pTpRxState->DataLength)
          { /* reception complete but insufficient buffer, do not send any FC behind */
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
          }
          else if(pTpRxState->WFTCounter == 0)
          { /* WFTmax reached (CanTp223) */
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NOT_OK, cCanTp_Initialize);
          }
          else
          {
            /* Set FC(WT) transmission request */
#if( CANTP_CONSTANT_BS == STD_ON )
            if(pTpRxState->BlocksizeCounter != 0)
            {
              vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
            }
            else
#endif
            {
              pTpRxState->Timer = ((((vCanTp_PBCfg_RX__NBR(TPRXHDL)) << 2) + 1) / 5); /* see CanTp222 */
              pTpRxState->ChannelState = cRxState_WaitForFCWaitConfIsr;
              pTpRxState->queued++;  
              VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
            }
          }
          break;

        default:
          vCanTp_Error(CanTp_MFuncRx_SId, CANTP_E_INVALID_STATE, (pTpRxState->ChannelState))
          break;
        } /* switch(pTpRxState->ChannelState) */
      } /* if(pTpRxState->Timer == 0) */
      else
      {
        /*************************************************************************
        * Timeout not reached yet, keep on counting (and trying to get a buffer) *
        *************************************************************************/
        if( (pTpRxState->ChannelState == cRxState_WaitForRxBuffer) || (pTpRxState->ChannelState == cRxState_WaitForFCWait) )
        { /* Still trying to retrieve buffer from application */
          vCanTp_RxRetrieveApplRxBuffer(CANTP_HDL_CVAL_ONLY);
        }
        else
        {
          vCanTp_RxStateTask(CANTP_HDL_CVAL_ONLY);
        }
      }      
    } /* if(vCanTp_PBCfg(ChanState)[tpHdl].RxState.Timer != 0) */
#if defined( CANTP_ENABLE_SINGLE_CONN )
#else
    Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_1);  /* CanTp_MainFunctionRx */
  } /* for loop ( all channels ) */
#endif
} /* PRQA S 2006 */ /* MD_MSR_14.7 */  /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6080 */ /* MD_MSR_STMIF */  /* PRQA S 6010 */ /* MD_MSR_STPTH */
/* CanTp_MainFunctionRx */

/**************************************************************************************************
   Function name    : vCanTp_RxRetrieveApplRxBuffer
   ------------------------------------------------------------------------------------------------
   Description      : Central interface to application to get an Buffer for Rx-data
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself
   ------------------------------------------------------------------------------------------------
   Parameter        : uint8 tpHdl
   ------------------------------------------------------------------------------------------------
   Returncode       : void
   ------------------------------------------------------------------------------------------------
   Misc             : Expects to be called in "critical section"
**************************************************************************************************/
#if defined( CANTP_ENABLE_PDUR_API40 )
STATIC FUNC(void,  CANTP_CODE)   vCanTp_RxRetrieveApplRxBuffer(CANTP_HDL_CPVAL_ONLY)
{
  VAR(PduLengthType, AUTOMATIC)      payloadLength;
  VAR(BufReq_ReturnType, AUTOMATIC)  bReq;
  VAR(vCanTp_TpRxStatePtrType, AUTOMATIC) pTpRxState;
  VAR(PduInfoType, AUTOMATIC)        PduInfo;
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
  P2CONST(vCanTp_RxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pRxNsduCfg;
  pRxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_RxNsduCfg, TPRXHDL));
#endif

  pTpRxState = &vCanTp_RxState[TP_RX_HDL(tpHdl)];
  if(pTpRxState->bufState == BUFREQ_E_BUSY)
  {
    PduInfo.SduLength = 0; /* check if there is more buffer available */
    /* PRQA S 3335 QAC_L6 */ /* RULE 8.1: Declaration available via macro redefinition. */
# if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
    pTpRxState->bufState = (CanTp_BufferState)vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID,CANTP_RX__REMAP_RXNSDU_ID), /* CanTpRxPduId */
                                &PduInfo,                                                                                                       /* PduInfoPtr   */
                                &pTpRxState->providedDataLength);                                                                               /* RxBufSizePtr */
# else
    pTpRxState->bufState = (CanTp_BufferState)vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID,      CANTP_RX__RXNSDU_ID), /* CanTpRxPduId */
                                &PduInfo,                                                                                                 /* PduInfoPtr   */
                                &pTpRxState->providedDataLength);                                                                         /* RxBufSizePtr */
# endif
    /* PRQA  L:QAC_L6 */
  }

  switch(pTpRxState->bufState)
  {
    case BUFREQ_OK:
    {
      PduInfo.SduDataPtr =  (&vCanTp_rxBuf[TP_RX_HDL(tpHdl)][0]);
      /* we got a buffer */
      switch(pTpRxState->frameType)
      {
        case cCanTp_FF:
        { /* ------- */
          payloadLength = (PduLengthType)vCanTp_rxGetPayloadLenFF(TPRXHDL);
          /* check if large enough */
#if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
          if((pTpRxState->providedDataLength >= payloadLength))
#else
          if((pTpRxState->providedDataLength >= pTpRxState->DataLength))
#endif
          { /* Valid and large enough: copy data */
            /* An SduLength of 0 is possible in order to poll the available receive buffer size. 
               In this case no data are to be copied and SduDataPtr might be invalid. */
            PduInfo.SduLength  = payloadLength;
            /* PRQA S 3335 QAC_L7 */ /* RULE 8.1: Declaration available via macro redefinition. */
#if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
            bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID,CANTP_RX__REMAP_RXNSDU_ID), /* CanTpRxPduId */
                                          &PduInfo,                                                                  /* PduInfoPtr   */
                                          &pTpRxState->providedDataLength);                                          /* RxBufSizePtr */
#else
            bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID,      CANTP_RX__RXNSDU_ID), /* CanTpRxPduId */
                                          &PduInfo,                                                            /* PduInfoPtr   */
                                          &pTpRxState->providedDataLength);                                    /* RxBufSizePtr */
#endif
            /* PRQA  L:QAC_L7 */
            pTpRxState->Timer = CANTP_RX1_CFG_PTR__NAR(tpHdl);
            if(bReq == BUFREQ_OK)
            {
              pTpRxState->DataIndex = (PduLengthType)(pTpRxState->DataIndex + payloadLength);          /* Increase index during reception */
#if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
              /* Check for FC(CTS) or FC(WT) */
              if( ( (pTpRxState->providedDataLength) >= (vCanTp_rxGetPayloadLenCF(TPRXHDL)))  ||
                  (((pTpRxState->providedDataLength) + (pTpRxState->DataIndex)) >= (pTpRxState->DataLength)) )
#endif
              { /* The provided buffer matches at least one CF or one CF is sufficient for all frame data bytes */
                /* Prepare FC(CTS)  (AssembleFC will check for enough buffer when calculating the BS)           */
                pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
              }
#if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
              else
              { /* No buffer left for next CF */
                if(pTpRxState->WFTCounter == 0)
                { /* WFTmax reached (CanTp223) */
                  vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NOT_OK, cCanTp_Initialize);
                }
                else
                {
                  /* Prepare FC(WT)  (AssembleFC will check for enough buffer when calculating the BS) */
                  pTpRxState->frameType    = cCanTp_CF;
                  pTpRxState->Timer = (((CANTP_RX1_CFG_PTR__NBR(tpHdl) << 2) + 1) / 5); /* see CanTp222 */
                  pTpRxState->ChannelState = cRxState_WaitForFCWaitConfIsr;
                }
              }
#endif
            }
            else
            { /* CopyRxData failed - giving up with FC(OVFL) */
              pTpRxState->ChannelState = cRxState_WaitForFCOverConfIsr;
            }

            pTpRxState->queued++;
            VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
          }
          else
          { /* Buffer not large enough to hold FF bytes. Set FC(OVFL) transmission request */
            pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
            pTpRxState->ChannelState = cRxState_WaitForFCOverConfIsr;
            pTpRxState->queued++;  /* Set FC(OVFL) transmission request */
            VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
          }
        }
        break;

        case cCanTp_SF:
        { /* ------- */
          payloadLength = pTpRxState->DataLength;
          if(pTpRxState->providedDataLength >= payloadLength)
          { /* buffer is ok and large enough */
            /* copy data buffered during RxIndication from CanTp to Appl. */
            PduInfo.SduLength  = payloadLength;
            PduInfo.SduDataPtr = (&vCanTp_rxBuf[TP_RX_HDL(tpHdl)][0]);
            /* PRQA S 3335 QAC_L8 */ /* RULE 8.1: Declaration available via macro redefinition. */
#if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
            bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID,CANTP_RX__REMAP_RXNSDU_ID), /* CanTpRxPduId */
                                          &PduInfo,                                                                  /* PduInfoPtr   */
                                          &pTpRxState->providedDataLength);                                          /* RxBufSizePtr */
#else
            bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID,      CANTP_RX__RXNSDU_ID), /* CanTpRxPduId */
                                          &PduInfo,                                                            /* PduInfoPtr   */
                                          &pTpRxState->providedDataLength);                                    /* RxBufSizePtr */
#endif
            /* PRQA  L:QAC_L8 */
            if(bReq == BUFREQ_OK)
            { /* Update application position index */
              vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  NTFRSLT_OK, cCanTp_Initialize);
            }
            else
            { /* CopyRxData failed - giving up with  appl indication*/
              vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
            }
          }
          else
          { /* buffer not large enough */
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
          }
        }
        break;    

        case cCanTp_CF:
#if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
        { /* ------- */
          payloadLength = (PduLengthType)vCanTp_rxGetPayloadLenCF(TPRXHDL);
          if( (pTpRxState->providedDataLength >= payloadLength) || (pTpRxState->providedDataLength >= (pTpRxState->DataLength - pTpRxState->DataIndex)) )
          { /* Got a valid data buffer! Large enough for next or last frame */
            if(pTpRxState->FrameIndex != 0)
            { /* Copy captured fragment to newly provided buffer */
              PduInfo.SduLength = pTpRxState->FrameIndex;
            }
            else
            { /* ask for (more) buffer */
              PduInfo.SduLength = 0;
            }
            PduInfo.SduDataPtr = &(vCanTp_rxBuf[TP_RX_HDL(tpHdl)][pTpRxState->FrameStartIndex]);
            /* PRQA S 3335 QAC_L9 */ /* RULE 8.1: Declaration available via macro redefinition. */
# if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
            bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID,CANTP_RX__REMAP_RXNSDU_ID), /* CanTpRxPduId */
                                          &PduInfo,                                                                  /* PduInfoPtr   */
                                          &pTpRxState->providedDataLength);                                          /* RxBufSizePtr */
# else
            bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID,      CANTP_RX__RXNSDU_ID), /* CanTpRxPduId */
                                          &PduInfo,                                                            /* PduInfoPtr   */
                                          &pTpRxState->providedDataLength);                                    /* RxBufSizePtr */
# endif
            /* PRQA  L:QAC_L9 */
            if(bReq != BUFREQ_OK)
            { /* CopyRxData failed - giving up with appl indication */
              vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  NTFRSLT_E_NOT_OK, cCanTp_Initialize);
            }
            else
            { /* Update positions + indices */
              pTpRxState->DataIndex  = (pTpRxState->DataIndex + pTpRxState->FrameIndex);
              /* Reset Rx-counter to have exact buffer-level later */
              pTpRxState->FrameIndex = 0;
            }

            if(pTpRxState->DataIndex >= pTpRxState->DataLength)
            { /* Transmission complete: stop waiting for CF/FC, callback RxIndication (multi frame complete) */  
              vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  NTFRSLT_OK, cCanTp_Initialize);
            }
            else 
            { /* transmission incomplete */
# if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#  if( CANTP_RX__BS != 0 )
#   if( CANTP_CONSTANT_BS == STD_ON )
#   else
                /* Prepare FC; Note: When arriving here, then a FC is sent unconditionally.
                   Due to the dynamically calculated BS the block must be complete now !  */
                if(pTpRxState->BlocksizeCounter > 0) 
                {
                  pTpRxState->BlocksizeCounter--;
                  if(pTpRxState->BlocksizeCounter == 0)
                  {
                    pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
                    pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                    pTpRxState->queued++;
                    VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
                  }
                }
#   endif  /* CANTP_CONSTANT_BS */
#  else  /* (CANTP_RX__BS != 0) */
              if( (pTpRxState->DataIndex) < (vCanTp_rxGetPayloadLenCF(tpHdl)) + (vCanTp_rxGetPayloadLenFF(tpHdl)) )
              { /* Prepare FC; Note: When arriving here, then a FC is sent unconditionally.
                                     ... but only if its the very first FC.CTS */
                pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
                pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                pTpRxState->queued++;
                VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
              }
              else
              {
                if(pTpRxState->FrameIndex == 0)
                { /* Nothing more captured - await new data */
                  pTpRxState->ChannelState = cRxState_WaitCF;
                }
                else
                { /* Still some data captured but no more buffer available */
                  vCanTp_Assert(pTpRxState->ChannelState == cRxState_WaitForRxBuffer, CanTp_RxIndication_SId, CANTP_WRONG_STATE, 0)
                }
              }
#  endif  /* (CANTP_RX__BS != 0) */
# else /* CANTP_SINGLE_CONN_NOPB_OPTIMIZED */
#  if ( (CANTP_ENABLE_EXT_API_BS == STD_ON) || (CANTP_ENABLE_CHANGE_PARAM == STD_ON) )
              if( (CANTP_DYN_BS[TPRXHDL]) != 0 )
#  else
#   if(!defined(CANTP_RX__BS))
              if( (CANTP_RX1_CFG_PTR__BS(TPRXHDL) != 0) )
#   endif
#  endif
#  if( CANTP_CHECK_BS == STD_ON )
              { /* Prepare FC; Note: When arriving here, then a FC is sent unconditionally.
                   ... but only if BS > 0 is configured or its the very first FC.CTS */
#  if( CANTP_CONSTANT_BS == STD_ON )
#  else
                if(pTpRxState->BlocksizeCounter > 0) 
                {
                  pTpRxState->BlocksizeCounter--;
                  if(pTpRxState->BlocksizeCounter == 0)
                  {
                    pTpRxState->Timer        = CANTP_RX_CFG_PTR__NAR(TPRXHDL);
                    pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                    pTpRxState->queued++;
                    VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
                  }
                }
#   endif  /* CANTP_CONSTANT_BS */
              }
#  endif  /* CANTP_CHECK_BS == STD_ON */

#  if ( (CANTP_ENABLE_EXT_API_BS == STD_ON) || (CANTP_ENABLE_CHANGE_PARAM == STD_ON) || (!defined(CANTP_RX__BS)) )
              else
#  endif
              { /* Prepare FC; Note: When arriving here, then a FC is sent unconditionally.
                               ... but only if its the very first FC.CTS */
                if( (pTpRxState->DataIndex) < ((vCanTp_rxGetPayloadLenCF(TPRXHDL)) + (vCanTp_rxGetPayloadLenFF(TPRXHDL))) )
                {
                  pTpRxState->Timer        = CANTP_RX_CFG_PTR__NAR(TPRXHDL);
                  pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                  pTpRxState->queued++;
                  VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
                }
                else
                {
                  if(pTpRxState->FrameIndex == 0)
                  { /* Nothing more captured - await new data */
                    pTpRxState->ChannelState = cRxState_WaitCF;
                  }
                  else
                  { /* Still some data captured but no more buffer available */
                    vCanTp_Assert(pTpRxState->ChannelState == cRxState_WaitForRxBuffer, CanTp_RxIndication_SId, CANTP_WRONG_STATE, 0)
                  }
                }
              }
# endif  /* CANTP_SINGLE_CONN_NOPB_OPTIMIZED */
            } /* endif transmission incomplete */
          } /* endif enough buffer provided */
          else 
          { /* Not large enough for next or last frame .... */
            PduLengthType len;
            if(pTpRxState->FrameIndex == 0)
            { /* no actual fragment available, so just poll PduR to get latest buffer size */
              len = 0;
            }
            else if(pTpRxState->providedDataLength >= pTpRxState->FrameIndex)
            { /* Store whole fragment */
              len = pTpRxState->FrameIndex;
            }
            else
            { /* Store part of fragment if application buffer is available -  otherwise poll PduR */
              len = pTpRxState->providedDataLength;
            }
            PduInfo.SduLength  = len;
            PduInfo.SduDataPtr = &(vCanTp_rxBuf[TP_RX_HDL(tpHdl)][pTpRxState->FrameStartIndex]);
            /* PRQA S 3335 QAC_L10 */ /* RULE 8.1: Declaration available via macro redefinition. */
# if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
            bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID,CANTP_RX__REMAP_RXNSDU_ID), /* CanTpRxPduId */
                                          &PduInfo,                                                                  /* PduInfoPtr   */
                                          &pTpRxState->providedDataLength);                                          /* RxBufSizePtr */
# else
            bReq = vCanTp_RxApplCopyRxData(CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID,      CANTP_RX__RXNSDU_ID), /* CanTpRxPduId */
                                          &PduInfo,                                                            /* PduInfoPtr   */
                                          &pTpRxState->providedDataLength);                                    /* RxBufSizePtr */
# endif
            /* PRQA  L:QAC_L10 */
            if(bReq == BUFREQ_OK)
            {
              pTpRxState->DataIndex                 = (pTpRxState->DataIndex + len);
              pTpRxState->FrameIndex                = (pTpRxState->FrameIndex - len);
              vCanTp_DetAssertVReturn(((pTpRxState->FrameIndex) <= 8), vCanTp_RxRetrieveApplRxBuffer_SId, CANTP_E_INVALID_STATE)
              pTpRxState->FrameStartIndex           = (uint8)(pTpRxState->FrameStartIndex + len);
            }
          } /* endif fragment available */

          if(pTpRxState->ChannelState != cRxState_Idle)
          {
            if( (pTpRxState->FrameIndex == 0) &&                                                                /* no data to copy and ...*/
                 ( (pTpRxState->providedDataLength >= payloadLength) ||                                         /*    buffer is sufficient for next  */
                   (pTpRxState->providedDataLength >= (pTpRxState->DataLength - pTpRxState->DataIndex)) ))      /*    or last CF */

            { /* buffer available, but no data to copy - first send a CTS to receive next CF ... */
# if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#  if( CANTP_RX__BS != 0 )
              { /* ... but only if BS > 0 is configured or its the very first FC.CTS */
                pTpRxState->Timer = CANTP_RX1_CFG_PTR__NAR(tpHdl);
                pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                pTpRxState->queued++; /* Set FC transmission request */
                VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
              }
#  else
              if( (pTpRxState->DataIndex) < (vCanTp_rxGetPayloadLenCF(tpHdl)) + (vCanTp_rxGetPayloadLenFF(tpHdl)) )
              { /* ... but only if BS > 0 is configured or its the very first FC.CTS */
                pTpRxState->Timer = CANTP_RX_CFG_PTR__NAR(tpHdl);
                pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                pTpRxState->queued++; /* Set FC transmission request */
                VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
              }
              else
              { /* ... otherwise the data is received by accident or we run into the CF timeout */ 
                pTpRxState->ChannelState = cRxState_WaitCF;
              }
#  endif
# else
#  if ( CANTP_VARIABLE_BS == STD_ON )
              if( (vCanTp_RxGetBlockSize(TPRXHDL) != 0)  ||
                    ((pTpRxState->DataIndex) < ((vCanTp_rxGetPayloadLenCF(TPRXHDL)) + (vCanTp_rxGetPayloadLenFF(TPRXHDL))) ) )
#  else
#   if( CANTP_CHECK_BS == STD_OFF )
              if( ((pTpRxState->DataIndex) < ((vCanTp_rxGetPayloadLenCF(TPRXHDL)) + (vCanTp_rxGetPayloadLenFF(TPRXHDL))) ) )
#   endif
#  endif
              { /* ... but only if BS > 0 is configured or its the very first FC.CTS */
                pTpRxState->Timer = CANTP_RX_CFG_PTR__NAR(TPRXHDL);
                pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                pTpRxState->queued++; /* Set FC transmission request */
                VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
              }
#  if ( (CANTP_VARIABLE_BS == STD_ON) || (CANTP_CHECK_BS == STD_OFF) )
              else
              { /* ... otherwise the data is received by accident or we run into the CF timeout */ 
                pTpRxState->ChannelState = cRxState_WaitCF;
              }
#  endif
# endif
            } /* end else enough buffer provided */
          } /* endif cRxState_Idle */
        } /* end case cCanTp_CF */
#endif
        break;
        
        default:
          /* no valid frame type */
          vCanTp_Error(vCanTp_RxRetrieveApplRxBuffer_SId, CANTP_WRONG_STATE, (((uint32)tpHdl) | (((uint32)(pTpRxState->frameType)) << 8) ))
          break;
      }
    }
    break; /* BUFREQ_OK */
  
    case BUFREQ_E_BUSY:
    { /*pTpRxState->bufState = BUFREQ_E_BUSY; * keep buffer status not used anymore */
      if(cCanTp_SF != pTpRxState->frameType)
      { /* Segmented  reception:
          send FC(WT) and continue recall ProvideRxBuffer() after TxConfirmation */
        if( (pTpRxState->ChannelState == cRxState_WaitForFCWait) && (pTpRxState->Timer > 1) )
        { /* FC.WT already transmitted, at the moment we're just looking for more buffer until the next FC.WT is expected */
        }
        else
        { /* Set FC(WT) transmission request */
          if(pTpRxState->WFTCounter == 0)
          { /* WFTmax reached (CanTp223) */
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NOT_OK, cCanTp_Initialize);
          }
          else
          {
            pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
            pTpRxState->ChannelState = cRxState_WaitForFCWaitConfIsr;
            pTpRxState->queued++;  
            VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
          }
        }
      }
      /* else { Unsegmented reception: ignore SF } */
    }
    break; /* BUFREQ_E_BUSY */
  
    case BUFREQ_E_OVFL:
    case BUFREQ_E_NOT_OK: 
    {
    /* ATTENTION: With AUTOSAR 2.0 no distinction is made between BUFREQ_E_OVFL and BUFREQ_E_NOT_OK !
    case BUFREQ_E_NOT_OK:
      Suppress sending FC and cancel reception
      vCanTp_RxInit(tpHdl, (NotifResultType)cCanTp_NoResultNotification, cCanTp_Initialize);
      break;
    */
      if(cCanTp_SF != pTpRxState->frameType)
      { /* Segmented  reception */
        if(cCanTp_CF == pTpRxState->frameType)
        { /* Segmented  reception and CF: Do not send FC(OVFL) (CanTp081),
            but call application indication */
#if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
          vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
#endif
        }
        else
        { /* Segmented  reception and FF: send FC(OVFL) and stop (CanTp081)
            The application notification (NTFRSLT_E_NO_BUFFER) is done from the FC confirmation. */
          pTpRxState->bufState     = BUFREQ_E_NOT_OK;
          pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
          pTpRxState->ChannelState = cRxState_WaitForFCOverConfIsr;
          pTpRxState->queued++;  /* Set FC(OVFL) transmission request */
          VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
        }
      }
      else 
      { /* Unsegmented reception: ignore SF but call application indication  */
        vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
      }
    }
    break; /* BUFREQ_E_OVFL */

     /* PRQA S 2018 2 */ /* RULE 14.1: If it can be shown statically that a switch statement is unreachable, message 2018 will be generated. */
    default:
    {
      /* unknown buffer request result */
      vCanTp_Error(vCanTp_RxRetrieveApplRxBuffer_SId, CANTP_E_INVALID_RX_BUFFER, CANTP_E_INVALID_PATH)
    }
    break;
  } /* switch(buffer request result) */

#if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
  if( (pTpRxState->bufState != BUFREQ_OK) && (pTpRxState->Timer == 0) )
  { /* No more retries left - Permanent failure to get a buffer */
    if(pTpRxState->frameType == cCanTp_SF)
    { /* Unsegmented reception */
      vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
    }
    else
    { /* Segmented reception */
      pTpRxState->Timer = CANTP_RX1_CFG_PTR__NAR(tpHdl);
      pTpRxState->ChannelState = cRxState_WaitForFCOverConfIsr;
      pTpRxState->queued++;  /* Set FC(OVFL) transmission request */
      VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
    }
  }
#endif
} /* vCanTp_RxRetrieveApplRxBuffer */

#else /* (CANTP_ENABLE_PDUR_API40 == STD_OFF) */

STATIC FUNC(void,  CANTP_CODE)   vCanTp_RxRetrieveApplRxBuffer(CANTP_HDL_CPVAL_ONLY)
{
  VAR(PduLengthType, AUTOMATIC)      payloadLength;
  VAR(BufReq_ReturnType, AUTOMATIC)  bReq;
  VAR(vCanTp_TpRxStatePtrType, AUTOMATIC) pTpRxState;
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
  P2CONST(vCanTp_RxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pRxNsduCfg;
  pRxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_RxNsduCfg, TPRXHDL));
#endif

  pTpRxState = &vCanTp_RxState[TP_RX_HDL(tpHdl)];
#if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
  bReq = vCanTp_RxApplProvideRxBuffer(tpHdl,
                                      CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID,CANTP_RX__REMAP_RXNSDU_ID),
                                      pTpRxState->DataLength,
                                      (P2VAR(PduInfoTypeCanTpApplDataPtr, AUTOMATIC, CANTP_APPL_DATA)) (&pTpRxState->ApplPduInfoPtr) );
#else
  bReq = vCanTp_RxApplProvideRxBuffer(tpHdl,
                                      CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID,CANTP_RX__RXNSDU_ID),
                                      pTpRxState->DataLength,
                                      (P2VAR(PduInfoTypeCanTpApplDataPtr, AUTOMATIC, CANTP_APPL_DATA)) (&pTpRxState->ApplPduInfoPtr) );
#endif
#if( ( CANTP_STRICT_RX_CALL_SEQ == STD_ON ) || ( CANTP_RC == STD_ON ) )
  if((bReq == BUFREQ_OK) || (bReq == BUFREQ_E_BUSY))
  { /* now the application is informed about a reception being in process */
    pTpRxState->ApplState = (uint8)(CANTP_APPL_INFORMED & 0x01);
  }
#endif

  switch(bReq)
  {
  case BUFREQ_OK:
  {
    vCanTp_DetAssert((pTpRxState->ApplPduInfoPtr != NULL_PTR), vCanTp_RxRetrieveApplRxBuffer_SId, CANTP_E_INVALID_RX_BUFFER)
    if(pTpRxState->ApplPduInfoPtr != NULL_PTR)
    {
      /* we got a buffer; assert validity */
      vCanTp_DetAssert((pTpRxState->ApplPduInfoPtr->SduDataPtr != NULL_PTR), vCanTp_RxRetrieveApplRxBuffer_SId, CANTP_E_INVALID_RX_BUFFER)

      switch(pTpRxState->frameType)
      {
        case cCanTp_FF:
        {
          payloadLength = (PduLengthType)vCanTp_rxGetPayloadLenFF(TPRXHDL);
          /* check if large enough */
#if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
          if((pTpRxState->ApplPduInfoPtr->SduDataPtr != NULL_PTR) && (pTpRxState->ApplPduInfoPtr->SduLength  >= payloadLength))
#else
          if((pTpRxState->ApplPduInfoPtr->SduDataPtr != NULL_PTR) && (pTpRxState->ApplPduInfoPtr->SduLength  >= pTpRxState->DataLength))
#endif
          { /* Valid and large enough: copy data */
            pTpRxState->providedDataLength = pTpRxState->ApplPduInfoPtr->SduLength;
            pTpRxState->DataBufferPtr      = pTpRxState->ApplPduInfoPtr->SduDataPtr;
            /* Copy FF that was buffered before to the Rx-data-buffer */
            vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(pTpRxState->DataBufferPtr),  
                          (&vCanTp_rxBuf[TP_RX_HDL(tpHdl)][0]),
                           payloadLength);
#if( (CANTP_FF_PROVIDE_2_RXBUFFER_CALLS == STD_ON) && (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON) )
            pTpRxState->DataIndex           = (PduLengthType)(pTpRxState->DataIndex + payloadLength);
            pTpRxState->ApplPduInfoPtr->SduLength = payloadLength;                                             /* Reset Rx-counter on FF-X   */
# if ( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
            bReq = vCanTp_RxApplProvideRxBuffer(tpHdl,
                                                CANTP_RX_CFG_PTR(tpHdl, CANTP_REMAP_RXNSDU_ID,CANTP_RX__REMAP_RXNSDU_ID),
                                                ((pTpRxState->DataLength)),
                                                (P2VAR(PduInfoTypeCanTpApplDataPtr, AUTOMATIC, CANTP_APPL_DATA)) (&pTpRxState->ApplPduInfoPtr) );
# else
            bReq = vCanTp_RxApplProvideRxBuffer(tpHdl,
                                                CANTP_RX_CFG_PTR(tpHdl, CANTP_RXNSDU_ID,CANTP_RX__RXNSDU_ID),
                                                ((pTpRxState->DataLength)),
                                                (P2VAR(PduInfoTypeCanTpApplDataPtr, AUTOMATIC, CANTP_APPL_DATA)) (&pTpRxState->ApplPduInfoPtr) );
# endif
             if(bReq == BUFREQ_OK)
            {
              pTpRxState->DataBufferPtr      = pTpRxState->ApplPduInfoPtr->SduDataPtr;
              pTpRxState->providedDataLength = pTpRxState->ApplPduInfoPtr->SduLength;
              pTpRxState->ApplPduInfoPtr->SduLength = 0;                                                       /* Really copied into this newly provided buffer */
            }
            else
            { /* invalid buffer */
              pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
              pTpRxState->ChannelState = cRxState_WaitForFCOverConfIsr;
              pTpRxState->queued++;  /* Set FC(OVFL) transmission request */
              VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
              break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
            }
#else
            pTpRxState->DataBufferPtr      += payloadLength;
            pTpRxState->providedDataLength  = (PduLengthType)(pTpRxState->providedDataLength - payloadLength); /* Decrease space during reception */
            pTpRxState->DataIndex           = (PduLengthType)(pTpRxState->DataIndex + payloadLength);          /* Increase index during reception */
            pTpRxState->ApplPduInfoPtr->SduLength = payloadLength;                                             /* Reset Rx-counter on FF-X   */
#endif

#if( (CANTP_FF_PROVIDE_2_RXBUFFER_CALLS == STD_ON) )
            /* Prepare FC(CTS)  (AssembleFC will check for enough buffer when calculating the BS)           */
            pTpRxState->Timer = CANTP_RX1_CFG_PTR__NAR(tpHdl);
            pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
            pTpRxState->queued++;
            VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
#else
# if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
            /* Check for FC(CTS) or FC(WT) */
            if( ( (pTpRxState->providedDataLength) >= (vCanTp_rxGetPayloadLenCF(TPRXHDL)))  ||
                (((pTpRxState->providedDataLength) + (pTpRxState->DataIndex)) >= (pTpRxState->DataLength))
              )
# endif
            { /* The provided buffer matches at least one CF or one CF is sufficient for all frame data bytes */
              /* Prepare FC(CTS)  (AssembleFC will check for enough buffer when calculating the BS)           */
              pTpRxState->Timer = CANTP_RX1_CFG_PTR__NAR(tpHdl);
              pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
              pTpRxState->queued++;
              VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
            }
# if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
            else
            { /* No buffer left for next CF */
                if(pTpRxState->WFTCounter == 0)
                { /* WFTmax reached (CanTp223) */
                  vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NOT_OK, cCanTp_Initialize);
                }
                else
                {
                  /* ask for more buffer from task level before sending a FC(.WT/.OVFL) */
                  /* the timer is still running */
                  pTpRxState->frameType    = cCanTp_CF;
                  pTpRxState->ChannelState = cRxState_WaitForRxBuffer;
                }
            }
# endif
#endif
          }
          else
          { /* Buffer not large enough to hold FF bytes */
            pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
            pTpRxState->ChannelState = cRxState_WaitForFCOverConfIsr;
            pTpRxState->queued++;  /* Set FC(OVFL) transmission request */
            VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
          }
        }
        break;

        case cCanTp_SF:
        {
          payloadLength = pTpRxState->DataLength;
          if((pTpRxState->ApplPduInfoPtr->SduDataPtr != NULL_PTR) &&
             (pTpRxState->ApplPduInfoPtr->SduLength  >= payloadLength))
          { /* buffer is ok and large enough */
            /* copy data buffered during RxIndication from CanTp to Appl. */
            vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (pTpRxState->ApplPduInfoPtr->SduDataPtr),  
                          (&vCanTp_rxBuf[TP_RX_HDL(tpHdl)][0]),
                           payloadLength);
            /* Update application position index */
            pTpRxState->ApplPduInfoPtr->SduLength = payloadLength;
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  NTFRSLT_OK, cCanTp_Initialize);
          }
          else
          { /* buffer not large enough */
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
          }
        }
        break;    

        case cCanTp_CF:
#if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
        {
          payloadLength = (PduLengthType)vCanTp_rxGetPayloadLenCF(TPRXHDL);
          if( (pTpRxState->ApplPduInfoPtr->SduDataPtr != NULL_PTR) && (pTpRxState->ApplPduInfoPtr->SduLength  >  0 ) )
          { /* Got a valid data buffer! */
            PduLengthType availBufSize;
            availBufSize = pTpRxState->ApplPduInfoPtr->SduLength;
            if( (availBufSize  >= payloadLength) || (availBufSize  >= (pTpRxState->DataLength - pTpRxState->DataIndex)) )
            { /* Large enough for next or last frame */
              if(pTpRxState->FrameIndex == 0)
              { /* Nothing captured, just update buffer pointer and keep provided length */
                pTpRxState->DataBufferPtr = pTpRxState->ApplPduInfoPtr->SduDataPtr;
                pTpRxState->providedDataLength = availBufSize;
                pTpRxState->ApplPduInfoPtr->SduLength = 0;
              }
              else
              { /* Copy captured fragment to newly provided buffer */
                pTpRxState->DataBufferPtr = pTpRxState->ApplPduInfoPtr->SduDataPtr;
                vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (pTpRxState->ApplPduInfoPtr->SduDataPtr), 
                               (&(vCanTp_rxBuf[TP_RX_HDL(tpHdl)][pTpRxState->FrameStartIndex])), 
                               (pTpRxState->FrameIndex) );
                /* Update positions + indices */
                pTpRxState->DataBufferPtr += pTpRxState->FrameIndex;
                pTpRxState->DataIndex      = (pTpRxState->DataIndex + pTpRxState->FrameIndex);
                pTpRxState->providedDataLength = (availBufSize - pTpRxState->FrameIndex);
                /* Reset Rx-counter to have exact buffer-level later */
                pTpRxState->ApplPduInfoPtr->SduLength = pTpRxState->FrameIndex;
                pTpRxState->FrameIndex = 0;
              }

              if(pTpRxState->DataIndex >= pTpRxState->DataLength)
              { /* Transmission complete: stop waiting for CF/FC, callback RxIndication (multi frame complete) */  
                vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  NTFRSLT_OK, cCanTp_Initialize);
              }
              else 
              {
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# if( CANTP_RX__BS != 0 )
                { /* Prepare FC; Note: When arriving here, then a FC is sent unconditionally.
                    Due to the dynamically calculated BS the block must be complete now !  */
                  pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
                  pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                  pTpRxState->queued++;
                  VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
                }
# else
                if( (pTpRxState->DataIndex) < ((vCanTp_rxGetPayloadLenCF(tpHdl)) + (vCanTp_rxGetPayloadLenFF(tpHdl))) )
                { /* Prepare FC; Note: When arriving here, then a FC is sent unconditionally.
                     ... but only if BS > 0 is configured or its the very first FC.CTS */
                  pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
                  pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                  pTpRxState->queued++;
                  VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
                }
                else
                {
                  if(pTpRxState->FrameIndex == 0)
                  { /* Nothing more captured - await new data */
                    pTpRxState->ChannelState = cRxState_WaitCF;
                  }
                  else
                  { /* Still some data captured but no more buffer available */
                    vCanTp_Assert(pTpRxState->ChannelState == cRxState_WaitForRxBuffer, CanTp_RxIndication_SId, CANTP_WRONG_STATE, 0)
                  }
                }
# endif
#else /* CANTP_SINGLE_CONN_NOPB_OPTIMIZED */
# if ( CANTP_VARIABLE_BS == STD_ON )
                if( (vCanTp_RxGetBlockSize(TPRXHDL) != 0)  ||
                    ((pTpRxState->DataIndex) < ((vCanTp_rxGetPayloadLenCF(TPRXHDL)) + (vCanTp_rxGetPayloadLenFF(TPRXHDL))) ) )
# else
#  if( CANTP_CHECK_BS == STD_OFF )
                if( ((pTpRxState->DataIndex) < ((vCanTp_rxGetPayloadLenCF(TPRXHDL)) + (vCanTp_rxGetPayloadLenFF(TPRXHDL))) ) )
#  endif
# endif
                { /* Prepare FC; Note: When arriving here, then a FC is sent unconditionally.
                     ... but only if BS > 0 is configured or its the very first FC.CTS */
                  pTpRxState->Timer        = CANTP_RX_CFG_PTR__NAR(TPRXHDL);
                  pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                  pTpRxState->queued++;
                  VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
                }
# if ( (CANTP_VARIABLE_BS == STD_ON) || (CANTP_CHECK_BS == STD_OFF) )
                else
                {
                  if(pTpRxState->FrameIndex == 0)
                  { /* Nothing more captured - await new data */
                    pTpRxState->ChannelState = cRxState_WaitCF;
                  }
                  else
                  { /* Still some data captured but no more buffer available */
                    vCanTp_Assert(pTpRxState->ChannelState == cRxState_WaitForRxBuffer, CanTp_RxIndication_SId, CANTP_WRONG_STATE, 0)
                  }
                }
# endif
#endif /* CANTP_SINGLE_CONN_NOPB_OPTIMIZED */
              }
            }
            else
            { /* Not large enough for next or last frame */
              PduLengthType len;
              pTpRxState->providedDataLength = pTpRxState->ApplPduInfoPtr->SduLength;
              if(pTpRxState->FrameIndex == 0)
              { /* Nothing captured */
                pTpRxState->ApplPduInfoPtr->SduLength = 0;
              }
              else
              { /* Store (part of) fragment to new buffer */
                pTpRxState->DataBufferPtr = pTpRxState->ApplPduInfoPtr->SduDataPtr;
                if(pTpRxState->providedDataLength >= pTpRxState->FrameIndex)
                { /* Store fragment */
                  len = pTpRxState->FrameIndex;
                }
                else
                { /* Store fragment at least partly */
                  len = pTpRxState->providedDataLength;
                }
                vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (pTpRxState->ApplPduInfoPtr->SduDataPtr), 
                              (&(vCanTp_rxBuf[TP_RX_HDL(tpHdl)][pTpRxState->FrameStartIndex])), 
                              len);
                pTpRxState->ApplPduInfoPtr->SduLength = len;
                pTpRxState->DataBufferPtr            += len;
                pTpRxState->DataIndex                 = (pTpRxState->DataIndex + len);
                pTpRxState->FrameIndex                = (pTpRxState->FrameIndex - len);
                vCanTp_DetAssertVReturn(((pTpRxState->FrameIndex) <= 8), vCanTp_RxRetrieveApplRxBuffer_SId, CANTP_E_INVALID_STATE)
                pTpRxState->FrameStartIndex           = (uint8)(pTpRxState->FrameStartIndex + len);
                pTpRxState->providedDataLength        = (pTpRxState->providedDataLength - len);
              }

              if ( (pTpRxState->FrameIndex > 0) || (pTpRxState->providedDataLength == 0) )
              { /* Still some fragment lying around, get more buffer.
                   Do not reload the timeout while trying to get more buffer. */
                pTpRxState->ChannelState = cRxState_WaitForRxBuffer;
              }
              else
              { /* No data available - first send a CTS to receive next CF ... */
                pTpRxState->FrameStartIndex = 0;
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# if( CANTP_RX__BS != 0 )
                { /* ... but only if BS > 0 is configured or its the very first FC.CTS */
                  pTpRxState->Timer = CANTP_RX1_CFG_PTR__NAR(tpHdl);
                  pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                  pTpRxState->queued++; /* Set FC transmission request */
                  VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
                }
# else
                if( (pTpRxState->DataIndex) < ((vCanTp_rxGetPayloadLenCF(tpHdl)) + (vCanTp_rxGetPayloadLenFF(tpHdl))) )
                { /* ... but only if BS > 0 is configured or its the very first FC.CTS */
                  pTpRxState->Timer = CANTP_RX1_CFG_PTR__NAR(tpHdl);
                  pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                  pTpRxState->queued++; /* Set FC transmission request */
                  VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
                }
                else
                { /* ... otherwise the data is received by accident or we run into the CF timeout */ 
                  pTpRxState->ChannelState = cRxState_WaitCF;
                }
# endif
#else

# if ( CANTP_VARIABLE_BS == STD_ON )
              if( (vCanTp_RxGetBlockSize(TPRXHDL) != 0)  ||
                    ((pTpRxState->DataIndex) < ((vCanTp_rxGetPayloadLenCF(TPRXHDL)) + (vCanTp_rxGetPayloadLenFF(TPRXHDL))) ) )
# else
#  if( CANTP_CHECK_BS == STD_OFF )
              if( ((pTpRxState->DataIndex) < ((vCanTp_rxGetPayloadLenCF(tpHdl)) + (vCanTp_rxGetPayloadLenFF(tpHdl))) ) )
#  endif
# endif
                { /* ... but only if BS > 0 is configured or its the very first FC.CTS */
                  pTpRxState->Timer = CANTP_RX_CFG_PTR__NAR(TP_RX_HDL(tpHdl));
                  pTpRxState->ChannelState = cRxState_WaitForFCConfIsr;
                  pTpRxState->queued++; /* Set FC transmission request */
                  VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
                }
# if ( (CANTP_VARIABLE_BS == STD_ON) || (CANTP_CHECK_BS == STD_OFF) )
                else
                { /* ... otherwise the data is received by accident or we run into the CF timeout */ 
                  pTpRxState->ChannelState = cRxState_WaitCF;
                }
# endif
#endif
              }
            }
          }
          else
          { /* No valid buffer provided */
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
          }
        }
#endif
        break;
        
        default:
          /* no valid frame type */
          vCanTp_Error(vCanTp_RxRetrieveApplRxBuffer_SId, CANTP_WRONG_STATE, (((uint32)tpHdl) | (((uint32)(pTpRxState->frameType)) << 8) ))
          break;
      }
    }
#if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
    else
    { /* No buffer provided */
      vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
    }
#endif
  }
  break; /* BUFREQ_OK */
  
  case BUFREQ_E_BUSY:
  {
    if(cCanTp_SF != pTpRxState->frameType)
    { /* Segmented  reception: send FC(WT) and continue recall ProvideRxBuffer() after TxConfirmation */
      if( (pTpRxState->ChannelState == cRxState_WaitForFCWait) && (pTpRxState->Timer > 1) )
      { /* FC.WT already transmitted, at the moment we're just looking for more buffer until the next FC.WT is expected */
      }
      else
      {
#if (CANTP_VARIABLE_BS == STD_ON)
        /* With BS != 0 or after a FF, FC.WT must be transmitted */
        if ( (0 != vCanTp_RxGetBlockSize(TPRXHDL)) || (cCanTp_CF != pTpRxState->frameType) )
#else
# if (CANTP_CHECK_BS == STD_OFF)
        /* BS is always 0; check only for frame type */
        if ( cCanTp_CF != pTpRxState->frameType )
# else
        /* BS is always != 0; FC need to be sent */
# endif
#endif
        {
          /* set FC(WT) transmission request */
          if(pTpRxState->WFTCounter == 0)
          { /* WFTmax reached (CanTp223) */
            vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NOT_OK, cCanTp_Initialize);
          }
          else
          {
            pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
            pTpRxState->ChannelState = cRxState_WaitForFCWaitConfIsr;
            pTpRxState->queued++;
            VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
          }
        }
        /* else: no FC.WT allowed; just wait for new buffer until timeout */
      }
    }
    /* else { Unsegmented reception: ignore SF } */
  }
  break; /* BUFREQ_E_BUSY */

#if (CANTP_SUPPRESS_INVALID_BUFFER_FC_OVFL == STD_ON)
  case BUFREQ_E_NOT_OK:
    /* invalid buffer: only cancel reception, do not send a FC.OVFL */
    vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
  break;
#else
  case BUFREQ_E_NOT_OK: /* fall-through, no break */
#endif
  case BUFREQ_E_OVFL:
  {
    if(cCanTp_SF != pTpRxState->frameType)
    { /* Segmented  reception */
      if(cCanTp_CF == pTpRxState->frameType)
      { /* Segmented  reception and CF: Do not send FC(OVFL) (CanTp081),
           but call application indication */
#if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
        vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
#endif
      }
      else
      { /* Segmented  reception and FF: send FC(OVFL) and stop (CanTp081)
           The application notification (NTFRSLT_E_NO_BUFFER) is done from the FC confirmation. */
        pTpRxState->bufState     = BUFREQ_E_NOT_OK;
        pTpRxState->Timer        = CANTP_RX1_CFG_PTR__NAR(tpHdl);
        pTpRxState->ChannelState = cRxState_WaitForFCOverConfIsr;
        pTpRxState->queued++;  /* Set FC(OVFL) transmission request */
        VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
      }
    }
    else 
    { /* Unsegmented reception: ignore SF but call application indication  */
      vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
    }
  }
  break; /* BUFREQ_E_OVFL */
    /* PRQA S 2018 2 */ /* RULE 14.1: If it can be shown statically that a switch statement is unreachable, message 2018 will be generated. */
  default:
    /* unknown buffer request result */
    vCanTp_Error(vCanTp_RxRetrieveApplRxBuffer_SId, CANTP_E_INVALID_RX_BUFFER, (uint32)bReq)
    break;
  } /* switch(buffer request result) */

#if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
  if( (pTpRxState->bufState != BUFREQ_OK) && (pTpRxState->Timer == 0) )
  { /* No more retries left - Permanent failure to get a buffer */
    if(pTpRxState->frameType == cCanTp_SF)
    { /* Unsegmented reception */
      vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER, cCanTp_Initialize);
    }
    else
    { /* Segmented reception */
      pTpRxState->Timer = CANTP_RX1_CFG_PTR__NAR(tpHdl);
      pTpRxState->ChannelState = cRxState_WaitForFCOverConfIsr;
      pTpRxState->queued++;  /* Set FC(OVFL) transmission request */
      VCANTP_RXSTATETASK(CANTP_HDL_CVAL_ONLY);
    }
  }
#endif
} /* PRQA S 2006 */ /* MD_MSR_14.7 */  /* PRQA S 6010 */ /* MD_MSR_STPTH */  /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6080 */ /* MD_MSR_STMIF */

#endif /* (CANTP_ENABLE_PDUR_API40) */


/**************************************************************************************************
   Function name    : CanTp_MainFunction
   ------------------------------------------------------------------------------------------------
   Description      : Main function of the AUTOSAR CAN Transport Protocol
   ------------------------------------------------------------------------------------------------
   Called by        : OS Task, to be called cyclically
   ------------------------------------------------------------------------------------------------
   Parameter        : void
   ------------------------------------------------------------------------------------------------
   Returncode       : void
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
/* PRQA S 3408 3 */ /* RULE 8.8: External linkage defined without previous definition due to generated code.
                                  For AR4 the SchM_CanTp.h contains the prototypes for the main funktions ([rte_sws_7283]) */
FUNC(void, CANTP_CODE) CanTp_MainFunction(void)
{
#if( CANTP_HAVE_INIT_CFG_PTR == STD_ON)
  vCanTp_DetAssertVReturn(vCanTp_LData(CfgPtr)    != NULL_PTR,           CanTp_MainFunction_SId, CANTP_E_UNINIT)
#endif
  CanTp_MainFunctionRx();
  CanTp_MainFunctionTx();
} /* PRQA S 2006 */ /* MD_MSR_14.7 */

/**************************************************************************************************
   Function name    : vCanTp_TxStateTask
   ------------------------------------------------------------------------------------------------
   Description      : Transmit a single CAN frame
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself
   ------------------------------------------------------------------------------------------------
   Parameter        : uint8 tpHdl (Number of current transmit tpHdl)
   ------------------------------------------------------------------------------------------------
   Returncode       : void 
   ------------------------------------------------------------------------------------------------
   Misc             : Note: This function transmits a single(!) frame, i.e. for transmission of 
                      several PDUs per cycle (Burst-mode with 'STmin==0') the CanTp_MainFunctionTx
                      has to call this function several times.
**************************************************************************************************/
#if defined( CANTP_ENABLE_PDUR_API40 )
STATIC FUNC(void,  CANTP_CODE)   vCanTp_TxStateTask(CANTP_HDL_PVAL_ONLY)
{
  VAR(PduInfoType, AUTOMATIC)         payload;
  VAR(PduInfoType, AUTOMATIC)         tpci;
  VAR(uint8, AUTOMATIC)               tmpBuffer[cCanTp_TPCIMaxLength];
  VAR(vCanTp_TxReturnType, AUTOMATIC) txResult;
  VAR(vCanTp_FrameType, AUTOMATIC)    frmType;
  VAR(PduLengthType, AUTOMATIC)       dataLen;
  vCanTp_TpTxStatePtrType             pTpTxState;
  VAR(PduLengthType, AUTOMATIC)       TxDataCnt;
  VAR(BufReq_ReturnType, AUTOMATIC)   bReq;
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
  P2CONST(vCanTp_TxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pTxNsduCfg;
#endif

  Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);  /* vCanTp_TxStateTask */

#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
  pTxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_TxNsduCfg, TPTXHDL));
#endif

  pTpTxState = &vCanTp_TxState[TP_TX_HDL(tpHdl)];
  if( (pTpTxState->frameType == cCanTp_CF) && (pTpTxState->TimerSTMin > 0) && (pTpTxState->STMin > 0) )
  { /* wait for STmin expiry if no burst mode is selected */
  }
  else if(pTpTxState->queued != cCanTp_NotQueued)
  {
    frmType = cCanTp_InvalidFrame;
    /* Enough data available (either enough for 1 frame or end of transfer) */         
    { /* Build CanTp frame (TPCI and payload) */
      /* Prepare TPCI */
      tpci.SduDataPtr = tmpBuffer;

      /* Prepare TP-data (payload-SduInfo) */
      payload.SduDataPtr = &vCanTp_txBuf[TP_TX_HDL(tpHdl)][pTpTxState->FrameIndex];
      switch(pTpTxState->frameType)
      {
      case cCanTp_SF:
        /***************
        * TpAssembleSF *
        ***************/
        tpci.SduLength  = cCanTp_SF_OFFSET;
        frmType = cCanTp_SF;
        tmpBuffer[cCanTp_FmtOffsetFrameType]  = kL4_SingleFrame; 
        tmpBuffer[cCanTp_FmtOffsetFrameType] |= (uint8)((pTpTxState->DataLength) & 0x0F); 
        payload.SduLength = pTpTxState->DataLength - pTpTxState->FrameIndex;
        break;

      case cCanTp_FF:
        /***************
        * TpAssembleFF *
        ***************/
        tpci.SduLength  = cCanTp_FF_OFFSET;
        frmType = cCanTp_FF;
        tmpBuffer[cCanTp_FmtOffsetFrameType]   = kL4_FirstFrame;
        tmpBuffer[cCanTp_FmtOffsetFrameType]  |= (uint8)(((pTpTxState->DataLength) >> 8) & 0x0F);
        tmpBuffer[cCanTp_FmtOffsetFrameType+1] = (uint8)  (pTpTxState->DataLength);
        /*Set tx index to next free data element*/
        payload.SduLength = (PduLengthType)vCanTp_txGetPayloadLenFF(TPTXHDL) - pTpTxState->FrameIndex;
        pTpTxState->seqNumber        = 1u; /* Set SN to initial starting number */
        pTpTxState->BlocksizeCounter = 0u; /* To calculate next transition to cTxState_WaitFC */

        pTpTxState->DataIndex        = 0;
        pTpTxState->OverallDataIndex = 0;
        break;

      case cCanTp_CF:
        /*************
        * AssembleCF *
        *************/
        tpci.SduLength  = cCanTp_CF_OFFSET;
        tmpBuffer[cCanTp_FmtOffsetFrameType]  = kL4_ConsecutiveFrame;
        tmpBuffer[cCanTp_FmtOffsetFrameType] |= (uint8) (pTpTxState->seqNumber);
        {
          PduLengthType CFlength;
          frmType = cCanTp_CF;
          CFlength  = (PduLengthType)vCanTp_txGetPayloadLenCF(TPTXHDL);
          dataLen   = pTpTxState->DataLength - pTpTxState->OverallDataIndex;
          if(dataLen >= CFlength)
          { /* Next CF */
            payload.SduLength = CFlength;
          }
          else
          { /* Last CF */
            payload.SduLength = dataLen;
          }    
          payload.SduLength = payload.SduLength - pTpTxState->FrameIndex;
        }
        break;
        
      default:
        tpci.SduLength    = 0;
        payload.SduLength = 0;
        vCanTp_Error(CanTp_Transmit_SId, NTFRSLT_E_UNEXP_PDU, (pTpTxState->frameType))
        break;
      }

      /* PRQA S 3335 QAC_L13 */ /* RULE 8.1: Declaration available via macro redefinition. */
#if ( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON )
      bReq = vCanTp_TxApplCopyTxData(CANTP_TX_CFG_PTR(CANTP_REMAP_TXNSDU_ID, CANTP_TX__REMAP_TXNSDU_ID),
                                    &payload,
                                     NULL_PTR,  /*  PduRetryInfo->TpDataState = TP_NORETRY is not supported for CanTp (see PduR V3.0.0 AR4.0 Rev1 PDUR518) */
                                    &TxDataCnt);
#else
      bReq = vCanTp_TxApplCopyTxData(CANTP_TX_CFG_PTR(CANTP_TXNSDU_ID, CANTP_TX__TXNSDU_ID),
                                    &payload,
                                     NULL_PTR,  /*  PduRetryInfo->TpDataState = TP_NORETRY is not supported for CanTp (see PduR V3.0.0 AR4.0 Rev1 PDUR518) */
                                    &TxDataCnt);
#endif
      /* PRQA  L:QAC_L13 */
      switch(bReq)
        {
        case BUFREQ_OK: /* Transmit data */
          pTpTxState->providedDataLength = TxDataCnt;
          payload.SduLength = payload.SduLength + pTpTxState->FrameIndex;
          txResult = vCanTp_CanIfTransmit(CANTP_HDL_CVAL_FIRST  &tpci, &payload, frmType);
          if(txResult != cCanTp_TxNotOk)
          { /* Successful transmitted */
            pTpTxState->queued  = 0;
            if(pTpTxState->channel != CANTP_INVALID_HDL)
            {
              pTpTxState->channel = TPTXHDL;
              /* Update admin-data in case of FF or CF */
              pTpTxState->DataIndex         += (payload.SduLength - pTpTxState->FrameIndex); /* Increase current index */
              pTpTxState->OverallDataIndex   = (pTpTxState->OverallDataIndex + payload.SduLength);
              pTpTxState->FrameIndex         = 0;
            }
          }
          else 
          { /* Cancel the connection; no retry is desired */
            vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST (NotifResultType)NTFRSLT_E_NOT_OK);
          }
          break;
        case BUFREQ_E_BUSY:
          if(pTpTxState->bufState == BUFREQ_E_BUSY)
          { /* just wait for getting more buffer or until timeout appears */
          }
          else
          {
            pTpTxState->Timer = (CANTP_TX_CFG_PTR__NCS());   /* see CanTp:167 */
            pTpTxState->ChannelState = cTxState_WaitForTxBuffer;
            pTpTxState->bufState = BUFREQ_E_BUSY;
          }
          break;
        case BUFREQ_E_NOT_OK:
          vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_E_NO_BUFFER);
          break;
        default:
#if(CANTP_OPER_NOT_SUPPORTED_REPORT_DEM == STD_ON)
          vCanTp_DemReportError(CanTp_E_Oper_Not_Supported, DEM_EVENT_STATUS_FAILED)
#else  /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */
          vCanTp_DetReportError(vCanTp_TxRetrieveApplTxBuffer_SId, CanTp_E_Oper_Not_Supported)
#endif /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */
          /**** Change of the internal status by yourself should not be done ****/
          vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST (NotifResultType)NTFRSLT_E_NO_BUFFER);            /****/

          break;
        } /* switch(bReq) */
    } /* if( enough data ) */
  } /* if(pTpTxState->queued != 0) */
  else { /* MISRA */ }
  Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* vCanTp_TxStateTask */
} /* vCanTp_TxStateTask */

#else /* (CANTP_ENABLE_PDUR_API40 == STD_OFF) */

STATIC FUNC(void,  CANTP_CODE)   vCanTp_TxStateTask(CANTP_HDL_PVAL_ONLY)
{
  VAR(PduInfoType, AUTOMATIC)         payload;
  VAR(PduInfoType, AUTOMATIC)         tpci;
  VAR(uint8, AUTOMATIC)               tmpBuffer[cCanTp_TPCIMaxLength];
  VAR(vCanTp_TxReturnType, AUTOMATIC) txResult;
  VAR(vCanTp_FrameType, AUTOMATIC)    frmType;
  VAR(PduLengthType, AUTOMATIC)       dataLen;
  vCanTp_TpTxStatePtrType             pTpTxState;

#if( (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON) || (CANTP_CONSTANT_TX__NCS == STD_ON) )
#else
  P2CONST(vCanTp_TxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pTxNsduCfg;
#endif
#if defined( CANTP_ENABLE_SINGLE_CONN )
#else
#  if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)tpHdl; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
# endif
#endif

  Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);  /* vCanTp_TxStateTask */

#if( (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON) || (CANTP_CONSTANT_TX__NCS == STD_ON) )
#else
  pTxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_TxNsduCfg, TPTXHDL));
#endif

  pTpTxState = &vCanTp_TxState[TP_TX_HDL(tpHdl)];
  if( (pTpTxState->frameType == cCanTp_CF) && (pTpTxState->TimerSTMin > 0) && (pTpTxState->STMin > 0) )
  { /* wait for STmin expiry if no burst mode is selected */
  }
  else if(pTpTxState->queued != cCanTp_NotQueued)
  {
    frmType = cCanTp_InvalidFrame;
    /* Enough data available? (either enough for 1 frame or end of transfer) */         
#if (CANTP_TX_FULL_BUFFER_PROVISION == STD_ON)
    if( (pTpTxState->bufState == BUFREQ_OK) && 
       (((pTpTxState->providedDataLength + pTpTxState->FrameIndex) >= vCanTp_txGetPayloadLen(pTpTxState->channel, pTpTxState->frameType)) || 
        ((pTpTxState->providedDataLength + pTpTxState->FrameIndex) >= (pTpTxState->DataLength - pTpTxState->OverallDataIndex)))
      )
#endif
    { /* Build CanTp frame (TPCI and payload) */
      /* Prepare TPCI */
      tpci.SduDataPtr = tmpBuffer;
      /* Prepare TP-data (payload-SduInfo) */
      payload.SduDataPtr = pTpTxState->DataBufferPtr + pTpTxState->DataIndex;
      
      switch(pTpTxState->frameType)
      {
      case cCanTp_SF:
        /***************
        * TpAssembleSF *
        ***************/
        tpci.SduLength  = cCanTp_SF_OFFSET;
        frmType = cCanTp_SF;
        tmpBuffer[cCanTp_FmtOffsetFrameType]  = kL4_SingleFrame; 
        tmpBuffer[cCanTp_FmtOffsetFrameType] |= (uint8)((pTpTxState->DataLength) & 0x0F); 
        payload.SduLength = pTpTxState->DataLength;
        break;

      case cCanTp_FF:
        /***************
        * TpAssembleFF *
        ***************/
        tpci.SduLength  = cCanTp_FF_OFFSET;
        frmType = cCanTp_FF;
        tmpBuffer[cCanTp_FmtOffsetFrameType]   = kL4_FirstFrame;
        tmpBuffer[cCanTp_FmtOffsetFrameType]  |= (uint8)(((pTpTxState->DataLength) >> 8) & 0x0F);
        tmpBuffer[cCanTp_FmtOffsetFrameType+1] = (uint8)  (pTpTxState->DataLength);
        /*Set tx index to next free data element*/
        payload.SduLength = (PduLengthType)vCanTp_txGetPayloadLenFF(TPTXHDL);
        pTpTxState->seqNumber        = 1u; /* Set SN to initial starting number */
        pTpTxState->BlocksizeCounter = 0u; /* To calculate next transition to cTxState_WaitFC */

        pTpTxState->DataIndex        = 0;
        pTpTxState->OverallDataIndex = 0;
        break;

      case cCanTp_CF:
        /*************
        * AssembleCF *
        *************/
        tpci.SduLength  = cCanTp_CF_OFFSET;
        tmpBuffer[cCanTp_FmtOffsetFrameType]  = kL4_ConsecutiveFrame;
        tmpBuffer[cCanTp_FmtOffsetFrameType] |= (uint8) (pTpTxState->seqNumber);
        {
          PduLengthType CFlength;
          frmType = cCanTp_CF;
          CFlength  = (PduLengthType)vCanTp_txGetPayloadLenCF(TPTXHDL);
          dataLen   = pTpTxState->DataLength - pTpTxState->OverallDataIndex;
          if(dataLen >= CFlength)
          { /* Next CF */
            payload.SduLength = CFlength;
          }
          else
          { /* Last CF */
            payload.SduLength = dataLen;
          }    
        }
        break;
        
      default:
        tpci.SduLength    = 0;
        payload.SduLength = 0;
        vCanTp_Error(CanTp_Transmit_SId, NTFRSLT_E_UNEXP_PDU, (pTpTxState->frameType))
        break;
      }
      
      /* Transmit data */
      txResult = vCanTp_CanIfTransmit(CANTP_HDL_CVAL_FIRST  &tpci, &payload, frmType);
      if(txResult != cCanTp_TxNotOk)
      { /* Successful transmitted */
        pTpTxState->queued  = 0;
        if(pTpTxState->ApplPduInfoPtr != NULL_PTR)
        {
          pTpTxState->channel = TPTXHDL;
          /* Update admin-data in case of FF or CF */
          pTpTxState->DataIndex                 += (payload.SduLength - pTpTxState->FrameIndex); /* Increase current index */
          pTpTxState->OverallDataIndex           = (pTpTxState->OverallDataIndex + payload.SduLength);
          pTpTxState->ApplPduInfoPtr->SduLength  = pTpTxState->DataIndex;                        /* Increase transmitted data length */
          pTpTxState->providedDataLength        -= (payload.SduLength - pTpTxState->FrameIndex); /* Decrease space left    */
          pTpTxState->FrameIndex                 = 0;
        }
      }
      else 
      { /* do not cancel the connection, in AR3 retry is desired */
        /* vCanTp_TxInit(tpHdl, (NotifResultType) BUSTRCV_E_ERROR; */
      }
    } /* if( enough data ) */
#if (CANTP_TX_FULL_BUFFER_PROVISION == STD_ON)
    else
    { /* not enough data -> request additonal data from the application */
      pTpTxState->bufState     = BUFREQ_E_BUSY;
      pTpTxState->Timer        = (CANTP_TX_CFG_PTR__NCS());    /* see CanTp:167 */
      pTpTxState->ChannelState = cTxState_WaitForTxBuffer;
      /* intentionally left for task level processing, now required for speeding up - give the application some time to provide more buffer */
      (void)vCanTp_TxRetrieveApplTxBuffer(CANTP_TX_HDL_CVAL_ONLY); 
    }
#endif
  } /* if(pTpTxState->queued != 0) */
  else { /* MISRA */ }

  Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* vCanTp_TxStateTask */
  
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* vCanTp_TxStateTask */
#endif /* (CANTP_ENABLE_PDUR_API40) */

/**************************************************************************************************
   Function name    : vCanTp_RxStateTask
   ------------------------------------------------------------------------------------------------
   Description      : Transmit a CAN frame
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself
   ------------------------------------------------------------------------------------------------
   Parameter        : uint8 tpHdl (Number of current reception tpHdl)
   ------------------------------------------------------------------------------------------------
   Returncode       : void 
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void,  CANTP_CODE)   vCanTp_RxStateTask(CANTP_HDL_PVAL_ONLY)
{
  VAR(vCanTp_TxReturnType, AUTOMATIC) txResult;
  VAR(PduInfoType, AUTOMATIC)         tpci;
  VAR(uint8, AUTOMATIC)               tmpBuffer[cCanTp_maxLengthFC];
  VAR(uint8, AUTOMATIC)               bsValue;
  VAR(boolean, AUTOMATIC)             transmitFC;
# if (CANTP_RX_FULL_BUFFER_PROVISION == STD_ON)
  VAR(uint16, AUTOMATIC)              defBlockSize;
# endif
  vCanTp_TpRxStatePtrType pTpRxState;
  VAR(PduInfoType, AUTOMATIC)         payload;

#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
# if( ((CANTP_ENABLE_EXT_API_STMIN == STD_ON) && (CANTP_ENABLE_EXT_API_BS  == STD_ON)) || \
      ((CANTP_ENABLE_CHANGE_PARAM  == STD_ON))                                         || \
      ((CANTP_CONSTANT_RX__BS      == STD_ON) && (CANTP_CONSTANT_RX__STMIN == STD_ON)) )
# else
  P2CONST(vCanTp_RxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pRxNsduCfg;
# endif
#endif

  Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);  /* vCanTp_RxStateTask */

#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
# if( ((CANTP_ENABLE_EXT_API_STMIN == STD_ON) && (CANTP_ENABLE_EXT_API_BS  == STD_ON)) || \
      ((CANTP_ENABLE_CHANGE_PARAM  == STD_ON))                                         || \
      ((CANTP_CONSTANT_RX__BS      == STD_ON) && (CANTP_CONSTANT_RX__STMIN == STD_ON)) )
# else
  pRxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_RxNsduCfg, TPRXHDL));
# endif
#endif

  pTpRxState = &vCanTp_RxState[TP_RX_HDL(tpHdl)];
  if(pTpRxState->queued != 0)
  {
    transmitFC = TRUE;  /* may only be set to FALSE for unsupported ChannelStates */
    if( (pTpRxState->channel == CANTP_INVALID_HDL) || (pTpRxState->channel == TPRXHDL) )
    {
      tpci.SduDataPtr = tmpBuffer;                                 /* set data buffer ptr  */
      bsValue         = vCanTp_RxGetBlockSize(TPRXHDL);            /* expect configured BS */

      /* AssembleFC */
      tpci.SduLength  = cCanTp_LengthFC;
      switch(pTpRxState->ChannelState) 
      { 
        case cRxState_WaitForFCConfIsr:
        {
          tmpBuffer[cCanTp_FmtOffsetFrameType] = kL4_FlowControl;
#if( CANTP_RX_FULL_BUFFER_PROVISION == STD_ON )
          if(bsValue == 0)  /* PRQA S 3355 */ /* MD_CANTP_MISRA_3355 */ /* PRQA S 3358 */ /* MD_CANTP_MISRA_3358 */ /* PRQA S 3356 */ /* MD_CANTP_MISRA_3356 */ /* PRQA S 3359 */ /* MD_CANTP_MISRA_3359 */
          {                 /* PRQA S 3201 */ /* MD_CANTP_MISRA_3201 */
            /* No more FCs used, check if provided length is sufficient for next frame */
          }
          else 
          {                 /* PRQA S 3201 */ /* MD_CANTP_MISRA_3201 */
            /* Consider BS Calculation */
# if( CANTP_CONSTANT_BS == STD_ON )
            if(CANTP_CONST_BS[TPRXHDL] != 0)
            { /* use the very first calculation of the BS */
              bsValue = (CANTP_CONST_BS[TPRXHDL]);
            }
# endif
            if( (pTpRxState->providedDataLength) >= ((pTpRxState->DataLength) - (pTpRxState->DataIndex)) )
            { /* enough buffer for the complete message is available: use the configured BS */
            }
            else 
            { /* Calculate BS */
# if( CANTP_CONSTANT_BS == STD_ON )
              if(CANTP_CONST_BS[TPRXHDL] == 0)
# endif
              {
                defBlockSize = ((uint16)bsValue) * (vCanTp_rxGetPayloadLenCF(TPRXHDL));
                if((pTpRxState->providedDataLength) < defBlockSize)
                { /* Provided length by application is insufficient for next block */
                  if( (pTpRxState->providedDataLength) < (vCanTp_rxGetPayloadLenCF(TPRXHDL)) )
                  { /* Provided length is insufficient for the next (CF) frame */
                    bsValue = 1;
                  }
                  else
                  { /* Provided length is insufficient, reduce next block */
                    bsValue = (uint8)(pTpRxState->providedDataLength / vCanTp_rxGetPayloadLenCF(TPRXHDL));
# if( CANTP_CALC_BS_OPTIMIZED == STD_ON )  /* FFS */
                    if((pTpRxState->providedDataLength) > (bsValue * (vCanTp_rxGetPayloadLenCF(tpHdl))) )
                    { /* enough buffer for a part of the next CF: use internal buffer and increment BS */
                      bsValue++;
                    }
# endif
                  }
                }
                else
                { /* Provided length is enough for the next block : take the configured (or already calculated) BS */
                }
# if( CANTP_CONSTANT_BS == STD_ON )
                CANTP_CONST_BS[TPRXHDL] = bsValue; /* store calculated value for later use when transmitting the next FC */
# endif
              }
            } /* Calculate BS */
          }
#endif  /* CANTP_RX_FULL_BUFFER_PROVISION == STD_ON */
          pTpRxState->BlocksizeCounter = bsValue; /* Load internal BS counter */
        }
        break;

        case cRxState_WaitForFCOverConfIsr:
          tmpBuffer[cCanTp_FmtOffsetFrameType] = (uint8)(kL4_FlowControl | kL4_FlowStatus_OVFLW);
        break;
        
        case cRxState_WaitForFCWaitConfIsr:   /* Do BS-counter-handling */
# if ( CANTP_VARIABLE_BS == STD_ON )
          if( (vCanTp_RxGetBlockSize(TPRXHDL) != 0) &&
              ((pTpRxState->DataIndex) >= ((vCanTp_rxGetPayloadLenCF(TPRXHDL)) + (vCanTp_rxGetPayloadLenFF(TPRXHDL))) ) )  /* PRQA S 3355 */ /* MD_CANTP_MISRA_3355 */ /* PRQA S 3358 */ /* MD_CANTP_MISRA_3358 */
          { /* ... only if its the very first FC.WT */
            transmitFC = FALSE;
          }
# else
#  if(CANTP_CHECK_BS == STD_OFF)
          if( (pTpRxState->DataIndex) >= ((vCanTp_rxGetPayloadLenCF(TPRXHDL)) + (vCanTp_rxGetPayloadLenFF(TPRXHDL))) )
          { /* ... only if its the very first FC.WT */
            transmitFC = FALSE;
          }
#  endif
# endif
          if(transmitFC == TRUE) /* PRQA S 3355 */ /* MD_CANTP_MISRA_3355 */ /* PRQA S 3358 */ /* MD_CANTP_MISRA_3358 */
          { /* send FC.WT */
            tmpBuffer[cCanTp_FmtOffsetFrameType] = (uint8)(kL4_FlowControl | kL4_FlowStatus_Wait);
          }
          else
          {  /* PRQA S 3201 */ /* MD_CANTP_MISRA_3201 */
            pTpRxState->queued  = 0;                             /* suppress FC.WT */
            pTpRxState->ChannelState = cRxState_WaitForRxBuffer; /* but still wait for further buffer */
          }
        break;
        
        default:
          /* unknown frame type based on an unknown ChannelState => Don't transmit! */
          vCanTp_Error(CanTp_MFuncRx_SId, CANTP_WRONG_STATE, tpHdl)
          transmitFC = FALSE;
        break;
      } /* switch Rx-state */

      tmpBuffer[cCanTp_FmtOffsetBs] = bsValue;
      if(transmitFC == TRUE)
      { /* get STmin */
        tmpBuffer[(cCanTp_FmtOffsetStmin)] = vCanTp_RxGetSTmin(TPRXHDL);

        /* init pdu info */
        payload.SduDataPtr = NULL_PTR; 
        payload.SduLength  = 0;
        txResult = vCanTp_CanIfTransmit(CANTP_HDL_CVAL_FIRST  &tpci, &payload, (vCanTp_FrameType)cCanTp_FC);
        if(txResult != cCanTp_TxNotOk)
        { /* Successfully transmitted */
          pTpRxState->queued  = 0;
        }
        else
        { /* Do not cancel the connection, keep on trying until timeout */
          /* vCanTp_RxInit(CANTP_HDL_CVAL_FIRST  (NotifResultType) NTFRSLT_E_NOT_OK, cCanTp_Initialize); */
        }
      } /* if(transmitFC == TRUE) */
    } /* if(pTpRxState->channel == CANTP_INVALID_HDL) */
  } /* if(pTpRxState->queued != 0) */
  Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* vCanTp_RxStateTask */
} /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* vCanTp_RxStateTask */

/**************************************************************************************************
   Function name    : vCanTp_TxCFTxConfirmation
   ------------------------------------------------------------------------------------------------
   Description      : Does all internal TxConf-Actions for CFs
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself
   ------------------------------------------------------------------------------------------------
   Parameter        : uint8 tpHdl - CanTp-channel to do this Tx-related action for.
   ------------------------------------------------------------------------------------------------
   Returncode       : void
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void, CANTP_CODE) vCanTp_TxCFTxConfirmation(CANTP_HDL_PVAL_ONLY)
{
  vCanTp_TpTxStatePtrType pTpTxState;
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# if( CANTP_NUM_RXSDUS == 2 )
#  if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)tpHdl; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
#  endif
# endif
#else
# if( ((CANTP_CONSTANT_TX__NAS == STD_OFF) || (CANTP_CONSTANT_TX__NBS == STD_OFF) || (CANTP_CONSTANT_TX__NCS == STD_OFF)) || \
      ((CANTP_CONSTANT_TX__TA_TYPE == STD_OFF) && (CANTP_HAVE_EXT_DEV_ERROR_DETECT == STD_ON)) )
  P2CONST(vCanTp_TxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pTxNsduCfg;
# endif
# if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON ) 
#  if( CANTP_NUM_RX_CHANNELS == 2 )
#   if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)tpHdl; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
#   endif
#  endif
# endif
# if( ((CANTP_CONSTANT_TX__NAS == STD_OFF) || (CANTP_CONSTANT_TX__NBS == STD_OFF) || (CANTP_CONSTANT_TX__NCS == STD_OFF)) || \
      ((CANTP_CONSTANT_TX__TA_TYPE == STD_OFF) && (CANTP_HAVE_EXT_DEV_ERROR_DETECT == STD_ON)) )
  pTxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_TxNsduCfg, TPTXHDL));
# endif
#endif

  pTpTxState = &vCanTp_TxState[TP_TX_HDL(tpHdl)];
#if( (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON) || (CANTP_CONSTANT_TX__TA_TYPE == STD_ON) )
# if(CANTP_TX__TA_TYPE == CANTP_FUNCTIONAL)
   vCanTp_AssertVAlways(vCanTp_TxCFTxConfirmation_SId, CANTP_E_PARAM_CONFIG, (uint16)0)
# endif
#else
  vCanTp_AssertVReturn(CANTP_TX_CFG_PTR__TA_TYPE() == CANTP_PHYSICAL, vCanTp_TxCFTxConfirmation_SId, CANTP_E_PARAM_CONFIG, 0)
#endif
  /*********************
  * CF was TxConfirmed *
  *********************/
  if((pTpTxState->OverallDataIndex) < pTpTxState->DataLength)
  { /* Still data left, proceed with transmission of next CF */
    pTpTxState->seqNumber += 1;
    pTpTxState->TimerSTMin = vCanTp_TxGetStminTimerFromStminValue(pTpTxState->STMin);

    if(pTpTxState->BlocksizeCounter != 0)
    { /* Blockwise Tx */
      pTpTxState->BlocksizeCounter--;
      if(pTpTxState->BlocksizeCounter == 0)
      { /* Block finished - Wait for FC */
        pTpTxState->Timer = CANTP_TX_CFG_PTR__NBS();
        pTpTxState->ChannelState = cTxState_WaitFC;
      }
      else
      { /* Still CFs in the block left: Proceed with Txn of next CF */
        if( (pTpTxState->providedDataLength < vCanTp_txGetPayloadLenCF(TPTXHDL)) &&
            (pTpTxState->providedDataLength < (pTpTxState->DataLength - pTpTxState->OverallDataIndex))
          )
        { /* remaining data too few for a CF */
          pTpTxState->ChannelState = cTxState_WaitForTxBuffer;
          pTpTxState->Timer = CANTP_TX_CFG_PTR__NCS();    /* see CanTp:167 */
          (void)vCanTp_TxRetrieveApplTxBuffer(CANTP_TX_HDL_CVAL_ONLY);
        }
        else
        {
          if(pTpTxState->STMin == 0)
          { /* "Burst mode" and enough buffer - Transmit next CF */
            pTpTxState->Timer = CANTP_TX_CFG_PTR__NAS();
            pTpTxState->ChannelState = cTxState_WaitForCFConfIsr;
            pTpTxState->queued++;
            vCanTp_TxStateTask(CANTP_TX_HDL_CVAL_ONLY);
          }
          else
          { /* No "Burst mode" and enough buffer: Prepare waiting for expiry of STMIN before transmit of next CF */
            pTpTxState->Timer = vCanTp_TxGetStminTimerFromStminValue(pTpTxState->STMin);
            pTpTxState->ChannelState = cTxState_WaitForTpTxCF;
          }
        }
      }
    }
    else
    { /* Tx without blocks, BlocksizeCounter == 0 */
#if defined( CANTP_ENABLE_PDUR_API40 )
# if (CANTP_TX_FULL_BUFFER_PROVISION == STD_ON)
      if( (pTpTxState->providedDataLength < vCanTp_txGetPayloadLenCF(TPTXHDL)) &&
          (pTpTxState->providedDataLength < (pTpTxState->DataLength - pTpTxState->OverallDataIndex))
        )
      { /* remaining data too few for a CF */
        pTpTxState->ChannelState = cTxState_WaitForTxBuffer;
        pTpTxState->Timer = CANTP_TX_CFG_PTR__NCS();    /* see CanTp:167 */
#  if( CANTP_TX_GET_BUFFER_SYNC == STD_ON )
        (void)vCanTp_TxRetrieveApplTxBuffer(CANTP_TX_HDL_CVAL_ONLY);
#  endif
      }
      else
# endif
#endif
      { /* Assuming enough buffer - Transmit next CF */
        if(pTpTxState->STMin == 0)
        { /* "Burst mode": send next CF at once */
          pTpTxState->Timer = CANTP_TX_CFG_PTR__NAS();
          pTpTxState->ChannelState = cTxState_WaitForCFConfIsr;
          pTpTxState->queued++;
          vCanTp_TxStateTask(CANTP_TX_HDL_CVAL_ONLY);
        }
        else
        { /* wait for expiry of STMIN */
          pTpTxState->Timer = vCanTp_TxGetStminTimerFromStminValue(pTpTxState->STMin);
          pTpTxState->ChannelState = cTxState_WaitForTpTxCF;
        }
      }
    }
  }
  else
  { /* No more data left, last CF is confirmed, indication to application */
    vCanTp_TxInit(CANTP_TX_HDL_CVAL_FIRST  (NotifResultType)NTFRSLT_OK);
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* vCanTp_TxCFTxConfirmation */


/**************************************************************************************************
   Function name    : vCanTp_TxGetStminTimerFromStminValue
   ------------------------------------------------------------------------------------------------
   Description      : Calculate task cycles to provide required STmin time
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself
   ------------------------------------------------------------------------------------------------
   Parameter        : uint8 tpSTminValue
   ------------------------------------------------------------------------------------------------
   Returncode       : void 
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(uint8, CANTP_CODE)   vCanTp_TxGetStminTimerFromStminValue(uint8 tpSTminValue)
{ 
  VAR(uint8, AUTOMATIC)  taskCycles;  /* Selected call cycle is rounded up to next possible call value */
  VAR(uint16, AUTOMATIC) cycleTime;

  /*
  Hex value Description
  00...7F   SeparationTime (STmin) range: 0 msec ... 127 msec
            The units of STmin in the range 00 hex ... 7F hex are absolute milliseconds (msec).
  F1...F9   SeparationTime (STmin) range: 100...900 micro seconds
            The units of STmin in the range F1 hex ... F9 hex are even 100 microseconds, where parameter
            value F1 hex represents 100 micro seconds and parameter value F9 hex represents 900 micro seconds.
  80...F0   Reserved
  FA...FF   Reserved
  */
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
  cycleTime = CANTP_TASK_CYCLE;     /* configured task cycle time in msec */
#else
  cycleTime = vCanTp_PBCfgPtr_(TaskCycle); /* configured task cycle time in msec */
#endif

  if((tpSTminValue & 0x80) != 0)
  { /* 100microsec * (tpSTminValue - 0xF0) */
    if((tpSTminValue >= 0xF1) && (tpSTminValue <= 0xF9))
    { /* Valid value but in the range of microseconds => 1 taskcycle */
      taskCycles = 1;
    }
    else
    { /* Invalid value */
#if(CANTP_HAVE_EXT_DEV_ERROR_DETECT == STD_ON)
      vCanTp_Error(vCanTp_TxGetStminTimerFromStminValue_SId, CANTP_E_PARAM_CONFIG, tpSTminValue)
#endif
      taskCycles = (uint8)(((127 + (cycleTime -1)) / cycleTime) + 1);
      /* If an FC N_PDU message is received with a reserved ST parameter value, then the sending network entity
         shall use the longest ST value specified by this part of ISO 15765 (7F hex ... 127 ms) instead of the value
         received from the receiving network entity for the duration of the ongoing segmented message transmission. */
    }
  }
  else
  { /* milliseconds */
    if(tpSTminValue == 0)
    { /* At once */
      taskCycles = 1;  
    }
    else
    { /* Later */
      taskCycles = (uint8)(((tpSTminValue + (cycleTime -1)) / cycleTime) + 1);
    }
  }
  return taskCycles;
} /* vCanTp_TxGetStminTimerFromStminValue */

#if ( CANTP_ENABLE_EXT_API_STMIN == STD_ON )
/**************************************************************************************************
   Function name    : CanTp_SetSTmin
   ------------------------------------------------------------------------------------------------
   Description      : Set a new value for STmin.
   ------------------------------------------------------------------------------------------------
   Called by        : Application
   ------------------------------------------------------------------------------------------------
   Parameter        : CanTpRxSduId  ID of CAN N-SDU for which the new value shall be set
                      CanTpSTmin    This parameter contains the new value for STmin
   ------------------------------------------------------------------------------------------------
   Returncode       : The actual value for STmin (new value, if the given value was valid 
                      otherwise the old value) 
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(uint8, CANTP_CODE) CanTp_SetSTmin(PduIdType CanTpRxSduId, uint8 CanTpSTmin) 
{
# if( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
  VAR(uint8,     AUTOMATIC) stmin;
  VAR(PduIdType, AUTOMATIC) tpHdl;
#  if(CANTP_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8,     AUTOMATIC) found;
  found = 0;
#  endif
# endif

  /* STmin normalization */
  if((CanTpSTmin & 0x80) != 0)
  {
    if((CanTpSTmin >= 0xF1) && (CanTpSTmin <= 0xF9))
    { /* Valid value in the range of microseconds => keep new value  */ 
    }
    else
    { /* Reserved value */
# if(CANTP_HAVE_EXT_DEV_ERROR_DETECT == STD_ON)
      vCanTp_Error(CanTp_SetSTmin_SId, CANTP_E_PARAM_CONFIG, CanTpSTmin)
# endif
      CanTpSTmin = 0x7F; /* limited to max. 127dec */
    }
  }
  else 
  { /* Valid value in the range of milliseconds => keep new value  */ 
  }

# if( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
  stmin = CANTP_INVALID_STMIN;  /* if no matching id found then return invalid value */
#  if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
  tpHdl = CANTP_NUM_RX_CHANNELS;
#  else
  tpHdl = vCanTp_PBCfgPtr_(NumCanTpRxSduId);
#  endif
  while(tpHdl > 0)
  { /* search the SduId belonging to the remapped SduId */
    tpHdl--;
    if(CanTpRxSduId == (vCanTp_PBCfg(vCanTp_RxNsduCfg, tpHdl, CANTP_REMAP_RXNSDU_ID, CANTP_RX__REMAP_RXNSDU_ID)))
    { /* found matching remapped id */
      /* tpHdl = vCanTp_PBCfg(vCanTp_RxNsduCfg, tpHdl, CANTP_RXNSDU_ID, CANTP_RX__RXNSDU_ID); implicitly done by sorted ids within generated data */
#  if(CANTP_DEV_ERROR_DETECT == STD_ON)
      found = 1;
#  endif
      vCanTp_DynSTmin[tpHdl] = CanTpSTmin;  /* use valid stmin value */
      stmin = CanTpSTmin;
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
  }
  vCanTp_DetAssert((found > 0), CanTp_SetSTmin_SId, CANTP_E_PARAM_ID)
  return(stmin);
# else
#  if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#  else
  vCanTp_DetAssertReturn( (CanTpRxSduId < vCanTp_PBCfgPtr_(NumCanTpRxSduId)), CanTp_SetSTmin_SId, CANTP_E_PARAM_ID, CANTP_INVALID_STMIN)
#  endif
  vCanTp_DynSTmin[CanTpRxSduId] = CanTpSTmin;  /* use valid stmin value */
  return(CanTpSTmin);
# endif
}
#endif

#if ( CANTP_ENABLE_EXT_API_BS == STD_ON )
/**************************************************************************************************
   Function name    : CanTp_SetBS
   ------------------------------------------------------------------------------------------------
   Description      : Set a new value for BS.
   ------------------------------------------------------------------------------------------------
   Called by        : Application
   ------------------------------------------------------------------------------------------------
   Parameter        : CanTpRxSduId  ID of CAN N-SDU for which the new value shall be set
                      CanTpBS       This parameter contains the new value for BS
   ------------------------------------------------------------------------------------------------
   Returncode       : The actual value for BS (new value, if the given value was valid 
                      otherwise the old value)
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(uint8, CANTP_CODE) CanTp_SetBS(PduIdType CanTpRxSduId, uint8 CanTpBS)
{
# if( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
  VAR(uint8,     AUTOMATIC) bs;
  VAR(PduIdType, AUTOMATIC) tpHdl;
#  if(CANTP_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8,     AUTOMATIC) found;
  found = 0;
#  endif

  bs = CANTP_INVALID_BS; /* if no matching id found then return invalid value */

#  if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
  tpHdl = CANTP_NUM_RX_CHANNELS;
#  else
  tpHdl = vCanTp_PBCfgPtr_(NumCanTpRxSduId);
#  endif
  while(tpHdl > 0)
  { /* search the SduId belonging to the remapped SduId */
    tpHdl--;
    if(CanTpRxSduId == (vCanTp_PBCfg(vCanTp_RxNsduCfg, tpHdl, CANTP_REMAP_RXNSDU_ID, CANTP_RX__REMAP_RXNSDU_ID)))
    { /* found matching remapped id */
      /* tpHdl = vCanTp_PBCfg(vCanTp_RxNsduCfg, tpHdl, CANTP_RXNSDU_ID, CANTP_RX__RXNSDU_ID); implicitly done by sorted ids within generated data */
#  if(CANTP_DEV_ERROR_DETECT == STD_ON)
      found = 1;
#  endif
      /* use valid bs value */
      vCanTp_DynBS[tpHdl] = CanTpBS;
      bs = CanTpBS;
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
  }
  vCanTp_DetAssert((found > 0), CanTp_SetBS_SId, CANTP_E_PARAM_ID)
  return(bs);
# else
#  if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#  else
  vCanTp_DetAssertReturn((CanTpRxSduId < vCanTp_PBCfgPtr_(NumCanTpRxSduId)), CanTp_SetBS_SId, CANTP_E_PARAM_ID, CANTP_INVALID_BS)
#  endif
  vCanTp_DynBS[CanTpRxSduId] = CanTpBS;  /* use valid bs value */
  return(CanTpBS);
# endif
}
#endif

#if ( CANTP_ENABLE_CHANGE_PARAM == STD_ON )
/**************************************************************************************************
   Function name    : CanTp_ReadParameterRequest
   ------------------------------------------------------------------------------------------------
   Description      : This service is used to read the reception parameters BS and STmin for a 
                      specified N-SDU.
   ------------------------------------------------------------------------------------------------
   Called by        : Application
   ------------------------------------------------------------------------------------------------
   Parameter        : CanTpRxSduId  Id of the reception N-SDU on which the reception parameter has to be read.
                      Pid           Specify the parameter for which the value has to be read (BS or STmin).
                      Pval          The value of the parameter.
   ------------------------------------------------------------------------------------------------
   Returncode       : E_OK:     request is accepted.
                      E_NOT_OK: request is not accepted.
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(Std_ReturnType,CANTP_CODE) CanTp_ReadParameterRequest(PduIdType CanTpRxSduId, TPParameterType Pid, uint16* Pval)
{
  Std_ReturnType retc;
  uint8 errC;
  PduIdType     RxHdl;

  vCanTp_DetAssertReturn((Pval != NULL_PTR),                              CanTp_ReadParameterRequest_Sid, CANTP_E_PARAM_ADDRESS, E_NOT_OK)
  vCanTp_DetAssertReturn((vCanTp_LData(InitState) == cCanTp_Initialized), CanTp_ReadParameterRequest_Sid, CANTP_E_UNINIT,        E_NOT_OK) /* CanTp293 */

  retc = E_NOT_OK;
  errC = 0x00; /* errC = 1: wrong Id, errC = 2: wrong type */
#if ( defined(CANTP_GEN_GENERATOR_MSR) && (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_OFF) )
  RxHdl = CANTP_INVALID_HDL;
  if(CanTpRxSduId < CanTpGET_NumCanTpRxSduId)
  {
    RxHdl = vCanTp_PduRIdMap[CanTpRxSduId];
  }
#else
  RxHdl = CanTpRxSduId;
#endif

#if defined( CANTP_ENABLE_SINGLE_CONN )
  vCanTp_DetAssertReturn((CanTpRxSduId < 1), CanTp_ReadParameterRequest_Sid, CANTP_E_PARAM_ID, E_NOT_OK)
  if(RxHdl >= 1)
#else /* CANTP_SINGLE_CONN_OPTIMIZED */
# if(CANTP_SINGLE_CONN_OPTIMIZED == STD_ON)
  vCanTp_DetAssertReturn((CanTpRxSduId < 2), CanTp_ReadParameterRequest_Sid, CANTP_E_PARAM_ID, E_NOT_OK)
  if(RxHdl >= 2)
# else /* CANTP_SINGLE_CONN_OPTIMIZED */
  vCanTp_DetAssertReturn((RxHdl < vCanTp_PBCfgPtr_(NumCanTpRxSduId)), CanTp_ReadParameterRequest_Sid, CANTP_E_PARAM_ID, E_NOT_OK)
  if((RxHdl >= vCanTp_PBCfgPtr_(NumCanTpRxSduId) ))
# endif /* CANTP_SINGLE_CONN_OPTIMIZED */
#endif /* CANTP_SINGLE_CONN_OPTIMIZED */
  {
    errC = 1; /* wrong Id */
  }
  else
  {
    vCanTp_DetAssert(((Pid == TPPARAMTYPE_CANTP_STMIN) || (Pid == TPPARAMTYPE_CANTP_BS)), CanTp_ReadParameterRequest_Sid, CANTP_E_PARAM_ID)
    if( (Pid != TPPARAMTYPE_CANTP_STMIN) && (Pid != TPPARAMTYPE_CANTP_BS) )
    {
      errC = 2; /* wrong type */
    }
  }

  if(errC == 0)
  { /* got the correct Id and the correct type */
    retc = E_OK;
    if(Pid == TPPARAMTYPE_CANTP_STMIN)
    {
      *Pval = CANTP_DYN_STMIN[RxHdl];   /* PRQA S 3689 */ /* MD_CANTP_MISRA_3689 */
    }
    else if(Pid == TPPARAMTYPE_CANTP_BS)
    {
      *Pval = CANTP_DYN_BS[RxHdl];      /* PRQA S 3689 */ /* MD_CANTP_MISRA_3689 */
    }
    else
    { /* MISRA (FFU) */
    }
  }

  return(retc);
} /* PRQA S 2006 */ /* MD_MSR_14.7 */  /* PRQA S 6010 */ /* MD_MSR_STPTH */
/* CanTp_ReadParameterRequest */
#endif /* ( CANTP_ENABLE_CHANGE_PARAM == STD_ON ) */

#if ( CANTP_ENABLE_CHANGE_PARAM == STD_ON )
/**************************************************************************************************
   Function name    : CanTp_ChangeParameterRequest
   ------------------------------------------------------------------------------------------------
   Description      : This service is used to request the change of reception parameters 
                      BS and STmin for a specified N-SDU.
   ------------------------------------------------------------------------------------------------
   Called by        : Application
   ------------------------------------------------------------------------------------------------
   Parameter        : CanTpRxSduId  Id of the received N-SDU on which the reception parameter has to be changed.
                      Pid           Specify the parameter for which the value has to be changed (BS or STmin).
                      Pval          The new value of the parameter.
   ------------------------------------------------------------------------------------------------
   Returncode       : E_OK:     request is accepted.
                      E_NOT_OK: request is not accepted.
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_ChangeParameterRequest(PduIdType CanTpRxSduId, TPParameterType Pid, uint16 Pval)
{/* CANTP303: A parameter change is only possible if the related N-SDU is not in the process of reception
              It is not possible after reception of FF until indication for last CF reception of the related N-SDU.
    CANTP304: If the change of a parameter is requested for an N-SDU that is on reception process then immediately 
              E_NOT_OK is returned and no value is changed. 
              After the request rejection the CanTp module shall call PduR_CanTpChangeParameterRequestConfirmation 
              - with notification result NTFRSLT_E_RX_ON.
    CANTP305: If development error detection is enabled the function CanTp_ChangeParameterRequest shall check the 
              validity of function parameters (Identifier, Parameter and requested value). 
              If any of the parameter value is invalid, the CanTp_ChangeParameterRequest function shall raise the 
              development error CANTP_E_PARAM_ID and return E_NOT_OK. 
              After a change was rejected the CanTp shall call PduR_CanTpChangeParameterRequestConfirmation 
              - with notification result NTFRSLT_E_PARAMETER_NOT_OK in case of a wrong Identifier or Parameter type value, 
              - with notification result NTFRSLT_E_VALUE_NOT_OK     in case of a wrong Value requested.
    CANTP306: After CanTp_ChangeParameterRequest service has been successfully executed the 
              PduR_CanTpChangeParameterRequestConfirmation is called 
              - with notification result NTFRSLT_PARAMETER_OK. */


  Std_ReturnType retc;
  uint8 errC;
  PduIdType     RxHdl;
#if ( CANTP_DYN_CHANNEL_ASSIGNMENT != STD_ON )
  vCanTp_TpRxStatePtrType pTpRxState;
#endif

  vCanTp_DetAssertReturn((vCanTp_LData(InitState) == cCanTp_Initialized), CanTp_ChangeParameterRequest_Sid, CANTP_E_UNINIT, E_NOT_OK) /* CanTp293 */
  retc = E_NOT_OK;
  errC = 0x00; /* errC = 1: busy reception, errC = 2: wrong Id, errC = 3: wrong type, (errC = 4: already busy), errC = 5: wrong value */
#if ( defined(CANTP_GEN_GENERATOR_MSR) && (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_OFF) )
  RxHdl = CANTP_INVALID_HDL;
  if(CanTpRxSduId < CanTpGET_NumCanTpRxSduId)
  {
    RxHdl = vCanTp_PduRIdMap[CanTpRxSduId];
  }
#else
  RxHdl = CanTpRxSduId;
#endif

  if(vCanTp_changeParamConfResult != NTFRSLT_OK)
  { /* change parameter already requested:  
       call confirmation synchronously with NTFRSLT_E_RX_ON and return E_NOT_OK */
    /* PRQA S 3335 QAC_L13 */ /* RULE 8.1: Declaration available via macro redefinition. */
    /* PRQA S 3200 QAC_L13 */ /* RULE 16.10: This unused return value depends on the unrecognized declaration. */
    vCanTp_RxApplChangeParamConfirmation((CanTpRxSduId), (NTFRSLT_E_RX_ON));
    /* PRQA  L:QAC_L13 */
  }
  else
  {
#if defined( CANTP_ENABLE_SINGLE_CONN )
    vCanTp_DetAssert((RxHdl < 1), CanTp_ChangeParameterRequest_Sid, CANTP_E_PARAM_ID)
    if(RxHdl >= 1)
#else /* CANTP_SINGLE_CONN_OPTIMIZED */
# if(CANTP_SINGLE_CONN_OPTIMIZED == STD_ON)
    vCanTp_DetAssert((RxHdl < 2), CanTp_ChangeParameterRequest_Sid, CANTP_E_PARAM_ID)
    if(RxHdl >= 2)
# else /* CANTP_SINGLE_CONN_OPTIMIZED */
    vCanTp_DetAssert((RxHdl < vCanTp_PBCfgPtr_(NumCanTpRxSduId)), CanTp_ChangeParameterRequest_Sid, CANTP_E_PARAM_ID)
    if( (RxHdl >= vCanTp_PBCfgPtr_(NumCanTpRxSduId)) )
# endif /* CANTP_SINGLE_CONN_OPTIMIZED */
#endif /* CANTP_SINGLE_CONN_OPTIMIZED */
    {
      errC = 2; /* wrong Id */
    }
    else
    {
      vCanTp_DetAssert(((Pid == TPPARAMTYPE_CANTP_STMIN) || (Pid == TPPARAMTYPE_CANTP_BS)), CanTp_ChangeParameterRequest_Sid, CANTP_E_PARAM_ID)
      if( (Pid != TPPARAMTYPE_CANTP_STMIN) && (Pid != TPPARAMTYPE_CANTP_BS) )
      {
        errC = 3; /* wrong type */
      }
    }

    if(errC == 0)
    { /* got the correct Id and the correct type */
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
      if( (vCanTp_rxHdlMap[RxHdl] != CANTP_INVALID_HDL) )
      {
        errC = 1; /* busy reception */
      }
# else /* CANTP_DYN_CHANNEL_ASSIGNMENT */
      pTpRxState = &vCanTp_RxState[TP_RX_HDL(RxHdl)];  /* PRQA S 3689 */ /* MD_CANTP_MISRA_3689 */
      if(pTpRxState->ChannelState != cRxState_Idle)
      {
        errC = 1; /* busy reception */
      }
# endif /* CANTP_DYN_CHANNEL_ASSIGNMENT */
    else
      { /* the reception is idle */
        if(Pid == TPPARAMTYPE_CANTP_STMIN)
        { /* STmin normalization */
          if((Pval & 0x80) != 0)
          {
            if((Pval >= 0xF1) && (Pval <= 0xF9))
            { /* Valid value in the range of microseconds => keep new value  */ 
            }
            else
            { /* Reserved value */
              vCanTp_DetReportError(CanTp_ChangeParameterRequest_Sid, CANTP_E_PARAM_ID)
              /* Pval = 0x7F; 2010-04-14: do not limit but handle as wrong value */
              errC = 5; /* wrong value */
            }
          }
          if(errC == 0)
          {
            /* use valid stmin value */
            CANTP_DYN_STMIN[RxHdl] = (uint8)Pval;   /* PRQA S 3689 */ /* MD_CANTP_MISRA_3689 */
          }
        } /* endif (Pid == STMIN */
        else if(Pid == TPPARAMTYPE_CANTP_BS)
        {
          /* use new bs value */
          CANTP_DYN_BS[RxHdl] = (uint8)Pval;        /* PRQA S 3689 */ /* MD_CANTP_MISRA_3689 */
        } /* endif (Pid == BS */
        else
        { /* MISRA (FFU) */
        }
      } /* endelse (reception == idle */
    } /* endif (errC == 0) */

    vCanTp_changeParamConfId = CanTpRxSduId;

    if(errC == 0)
    { /* no error:          return OK and call confirmation with NTFRSLT_PARAMETER_OK */
      retc = E_OK;
      vCanTp_changeParamConfResult = NTFRSLT_PARAMETER_OK;
    }
    else if(errC == 1)
    { /* busy reception:    return NOT_OK and call confirmation with NTFRSLT_E_RX_ON */
      vCanTp_changeParamConfResult = NTFRSLT_E_RX_ON;
    }
    else if(errC == 2)
    { /* wrong id:  return NOT_OK and call confirmation with NTFRSLT_E_PARAMETER_NOT_OK */
      /* ATTENTION: Do not know for which Id this confirmation should be called !!! */
      vCanTp_changeParamConfResult = NTFRSLT_E_PARAMETER_NOT_OK;
    }
    else if(errC == 3)
    { /* wrong type:  return NOT_OK and call confirmation with NTFRSLT_E_PARAMETER_NOT_OK */
      vCanTp_changeParamConfResult = NTFRSLT_E_PARAMETER_NOT_OK;
    }
    else
    { /* wrong value:       return NOT_OK and call confirmation with NTFRSLT_E_VALUE_NOT_OK */
      vCanTp_changeParamConfResult = NTFRSLT_E_VALUE_NOT_OK;
    }
  } /* endelse already busy */

  return(retc);
} /* PRQA S 2006 */ /* MD_MSR_14.7 */  /* PRQA S 6010 */ /* MD_MSR_STPTH */  /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* CanTp_ChangeParameterRequest */
#endif /* ( CANTP_ENABLE_CHANGE_PARAM == STD_ON ) */


/**************************************************************************************************
   Function name    : CanTp_Init
   ------------------------------------------------------------------------------------------------
   Description      : Initializes the runtime data of the CanTp
   ------------------------------------------------------------------------------------------------
   Called by        : AUTOSAR EcuM
   ------------------------------------------------------------------------------------------------
   Parameter        : Pointer to configuration structure of CanTp located in ROM/Flash.
   ------------------------------------------------------------------------------------------------
   Returncode       : None
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
#if defined( CANTP_AUTOSARVERSION4 )
FUNC(void, CANTP_CODE) CanTp_Init(P2CONST(vCanTp_CfgType, AUTOMATIC, CANTP_CODE) pCfgPtr)   /* CanTp208:  Added parameter for CanTp_Init function */
#else
# if(CANTP_HAVE_INIT_CFG_PTR == STD_ON)
FUNC(void, CANTP_CODE) CanTp_Init(CONSTP2CONST(void, AUTOMATIC, CANTP_CODE) pCfgPtr)
# else
FUNC(void, CANTP_CODE) CanTp_Init(void)
# endif
#endif
{
#if (defined( CANTP_AUTOSARVERSION4 )) || \
    (defined( CANTP_AUTOSARVERSION3 ) && ( CANTP_HAVE_INIT_CFG_PTR == STD_ON ))
  vCanTp_DetAssertVReturn((pCfgPtr != NULL_PTR), CanTp_Init_SId, CANTP_E_PARAM_ADDRESS)
  vCanTp_LData(CfgPtr) = pCfgPtr;
#endif
  vCanTp_InitFromLCfgPtr();
} /* PRQA S 2006 */ /* MD_MSR_14.7 */

/**************************************************************************************************
   Function name    : vCanTp_InitFromLCfgPtr
   ------------------------------------------------------------------------------------------------
   Description      : Initializes the runtime data of the CanTp and sets the CanTp state variable to 
                      'initialized'.
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp_Init
   ------------------------------------------------------------------------------------------------
   Parameter        : None
   ------------------------------------------------------------------------------------------------
   Returncode       : None
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void,  CANTP_CODE) vCanTp_InitFromLCfgPtr(void)
{
  VAR(PduIdType, AUTOMATIC) tmp;

  vCanTp_LData(InitState) = cCanTp_Uninitialized;

#if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
  vCanTp_AssertVReturn((vCanTp_NumRxChannels <= vCanTp_PBCfgPtr_(NumCanTpRxSduId)), vCanTp_InitMemory_Sid, CANTP_E_PARAM_CONFIG, 0)
  vCanTp_AssertVReturn((vCanTp_NumTxChannels <= vCanTp_PBCfgPtr_(NumCanTpTxSduId)), vCanTp_InitMemory_Sid, CANTP_E_PARAM_CONFIG, 0)
  vCanTp_NumRxChannelsAvail = vCanTp_NumRxChannels;
  vCanTp_NumTxChannelsAvail = vCanTp_NumTxChannels;
#endif

#if !defined( V_SUPPRESS_EXTENDED_VERSION_CHECK )
# if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# else
    /* PRQA S 3355 QAC_L1 */ /* MD_CANTP_MISRA_3355 */
    /* PRQA S 3356 QAC_L1 */ /* MD_CANTP_MISRA_3356 */
  if( ((vCanTp_PBCfgPtr_(CanTp_GeneratorVersion) & (uint32)0x00FFFF00u) != ((((uint32)TP_ASRTPCAN_GENTOOL_GENY_MAJOR_VERSION) << 16u) | (((uint32)TP_ASRTPCAN_GENTOOL_GENY_MINOR_VERSION) <<  8u))) 
#  if(TP_ASRTPCAN_GENTOOL_GENY_PATCH_VERSION > 0)
   || ((vCanTp_PBCfgPtr_(CanTp_GeneratorVersion) & (uint32)0x000000FFu) <  (TP_ASRTPCAN_GENTOOL_GENY_PATCH_VERSION) ) 
#  endif
    )
  {
    EcuM_GeneratorCompatibilityError((uint16)CANTP_MODULE_ID, (uint8)0);  /* module id, instance id */
    return;                   /* Abort initialization as generator is not compatible */
  }
  /* PRQA  L:QAC_L1 */
# endif
#endif

#if(CANTP_CRC_CHECK == STD_ON)
# if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# else
  if(vCanTp_PBCfgPtr_(CanTp__PrecompileCRC) != (uint32)CANTP_PRECOMPILE_CRC)
  {
    EcuM_GeneratorCompatibilityError((uint16)CANTP_MODULE_ID, (uint8)0u);  /* module id, instance id */
    return;                   /* Abort initialization as current configuration is not compatible with the pre-compile configuration */
  }
  if(vCanTp_PBCfgPtr_(CanTp__LinktimeCRC) != (uint32)CanTp_LinktimeCRC)
  {
    EcuM_GeneratorCompatibilityError((uint16)CANTP_MODULE_ID, (uint8)0u);  /* module id, instance id */
    return;                   /* Abort initialization as current configuration is not compatible with the link-time configuration */
  }
#  if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
  if(vCanTp_PBCfgPtr_(NumCanTpRxSduId) != CANTP_NUM_RX_CHANNELS)
  {
    EcuM_GeneratorCompatibilityError((uint16)CANTP_MODULE_ID, (uint8)0u);  /* module id, instance id */
    return;                   /* Abort initialization as current configuration is not compatible with the link-time configuration */
  }
#  endif
# endif
#endif


#if defined( CANTP_ENABLE_SINGLE_CONN )
  /* ------------------------------------------------------------------- */
  /* Initialize CanTp channel structures for single channel optimization */
  /* ------------------------------------------------------------------- */
  vCanTp_RxInit((NotifResultType)cCanTp_NoResultNotification, cCanTp_NoAdminReset);
  vCanTp_TxInit((NotifResultType)cCanTp_NoResultNotification);

# if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)tmp; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */  /* PRQA S 3321 */ /* Variable may be unset at this point, which is uncritical as it is not used here */
# endif

#elif( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
  /* ------------------------------------------------------------------------------ */
  /* Initialize CanTp channel structures for single channel precompile optimization */
  /* ------------------------------------------------------------------------------ */
  vCanTp_RxInit(0, (NotifResultType)cCanTp_NoResultNotification, cCanTp_NoAdminReset);
  vCanTp_RxInit(1, (NotifResultType)cCanTp_NoResultNotification, cCanTp_NoAdminReset);
  vCanTp_TxInit(0, (NotifResultType)cCanTp_NoResultNotification);

# if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)tmp; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */  /* PRQA S 3321 */ /* Variable may be unset at this point, which is uncritical as it is not used here */
# endif

#elif ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
  /* ------------------------------------------------------------------ */
  /* Initialize CanTp channel structures for dynamic channel assignment */
  /* ------------------------------------------------------------------ */

  /* initialize RX */
  /* ------------- */
  tmp = vCanTp_PBCfgPtr_(NumCanTpRxSduId);
  while(tmp > 0)
  { /* Rx handle map */
    tmp--;
    vCanTp_rxHdlMap[tmp] = CANTP_INVALID_HDL;
  }

  tmp = vCanTp_NumRxChannelsAvail;
  while(tmp > 0)
  { /* Rx state */
    tmp--;
    vCanTp_RxInitState(tmp);
  }

  /* initialize TX */
  /* ------------- */
  tmp = vCanTp_PBCfgPtr_(NumCanTpTxSduId);
  while(tmp > 0)
  { /* Tx handle map */
    tmp--;
    vCanTp_txHdlMap[tmp] = CANTP_INVALID_HDL;
  }

  tmp = vCanTp_NumTxChannelsAvail;
  while(tmp > 0)
  { /* Tx state */
    tmp--;
    vCanTp_TxInitState(tmp);
  }
#else
  /* --------------------------------------------------------------- */
  /* Initialize CanTp channel structures for standard configurations */
  /* --------------------------------------------------------------- */

  /* initialize RX */
  /* ------------- */
  tmp = vCanTp_PBCfgPtr_(NumCanTpRxSduId);
  while(tmp > 0)
  { /* Rx */
    tmp--;
    vCanTp_RxInit(tmp, (NotifResultType)cCanTp_NoResultNotification, cCanTp_NoAdminReset);
  }

  /* initialize TX */
  /* ------------- */
  tmp = vCanTp_PBCfgPtr_(NumCanTpTxSduId);
  while(tmp > 0)
  { /* Tx */
    tmp--;
    vCanTp_TxInit(tmp, (NotifResultType)cCanTp_NoResultNotification);
  }
#endif


#if( (CANTP_ENABLE_CHANGE_PARAM == STD_ON) )
  vCanTp_changeParamConfResult = NTFRSLT_OK;
#endif

#if( (CANTP_ENABLE_EXT_API_BS == STD_ON) || (CANTP_ENABLE_EXT_API_STMIN == STD_ON) || (CANTP_ENABLE_CHANGE_PARAM == STD_ON) )
  /* Initialize CanTp dynamic blocksize/STmin values */
# if defined( CANTP_ENABLE_SINGLE_CONN )
#  if ( (CANTP_ENABLE_EXT_API_BS == STD_ON) || (CANTP_ENABLE_CHANGE_PARAM == STD_ON) )
    CANTP_DYN_BS[0]    = vCanTp_PBCfg_RX__BS(0);
#  endif
#  if( CANTP_ENABLE_EXT_API_BS == STD_ON )
    vCanTp_DynBS[0]    = CANTP_DYN_BS[0];
#  endif
#  if ( (CANTP_ENABLE_EXT_API_STMIN == STD_ON) || (CANTP_ENABLE_CHANGE_PARAM == STD_ON) )
    CANTP_DYN_STMIN[0] = vCanTp_PBCfg_RX__STMIN(0);
#  endif
#  if( CANTP_ENABLE_EXT_API_STMIN == STD_ON )
    vCanTp_DynSTmin[0] = CANTP_DYN_STMIN[0];
#  endif
# else /* CANTP_SINGLE_CONN_OPTIMIZED */
  /* Initialize CanTp dynamic blocksize/STmin values */
#  if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
  tmp = CANTP_NUM_RX_CHANNELS;
#  else
  tmp = vCanTp_PBCfgPtr_(NumCanTpRxSduId);
#  endif
  while(tmp > 0)
  { /* Rx initial values */
    tmp--;
#  if ( (CANTP_ENABLE_EXT_API_BS == STD_ON) || (CANTP_ENABLE_CHANGE_PARAM == STD_ON) )
    CANTP_DYN_BS[tmp] = vCanTp_PBCfg_RX__BS(tmp);
#  endif
#  if( CANTP_ENABLE_EXT_API_BS == STD_ON )
    vCanTp_DynBS[tmp] = CANTP_DYN_BS[tmp];
#  endif
#  if ( (CANTP_ENABLE_EXT_API_STMIN == STD_ON) || (CANTP_ENABLE_CHANGE_PARAM == STD_ON) )
    CANTP_DYN_STMIN[tmp] = vCanTp_PBCfg_RX__STMIN(tmp);
#  endif
#  if( CANTP_ENABLE_EXT_API_STMIN == STD_ON )
    vCanTp_DynSTmin[tmp] = CANTP_DYN_STMIN[tmp];
#  endif
  }
# endif /* CANTP_SINGLE_CONN_OPTIMIZED */
#endif /* (CANTP_ENABLE_EXT_API_BS == STD_ON) || (CANTP_ENABLE_EXT_API_STMIN == STD_ON) || (CANTP_ENABLE_CHANGE_PARAM == STD_ON) */

#if( CANTP_TX_SERIALIZE == STD_ON )
  /* Initialize transmit semaphore */
  vCanTp_TxSemaphore.hdl  = CANTP_INVALID_HDL;
# if( CANTP_TX_SINGLE_SERIALIZE == STD_ON )
# else
  vCanTp_TxConflict.wrpos = 0;
  vCanTp_TxConflict.rdpos = 0;
  tmp = (CANTP_TX_MAX_NUM_CONFLICT);
  while(tmp > 0)
  { /* Rx initial values */
    tmp--;
    vCanTp_TxConflict.hdl[tmp] = CANTP_INVALID_HDL;
  }
# endif
#endif

  vCanTp_LData(InitState) = cCanTp_Initialized;
} /* PRQA S 2006 */ /* MD_MSR_14.7 */
/* vCanTp_InitFromLCfgPtr */

/**************************************************************************************************
   Function name    : CanTp_InitMemory
   ------------------------------------------------------------------------------------------------
   Description      : Initializes the RAM data of the CanTp
   ------------------------------------------------------------------------------------------------
   Called by        : AUTOSAR EcuM
   ------------------------------------------------------------------------------------------------
   Parameter        : void
   ------------------------------------------------------------------------------------------------
   Returncode       : None
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_InitMemory(void)
{
#if( CANTP_HAVE_INIT_CFG_PTR == STD_ON )
# if ( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
  vCanTp_LData(CfgPtr)    = NULL_PTR;
# else
  vCanTp_LData(CfgPtr)    = &vCanTp_Cfg;
# endif
#endif
  vCanTp_LData(InitState) = cCanTp_Uninitialized;
}  /* End of CanTp_InitMemory() */

/**************************************************************************************************
   Function name    : CanTp_Shutdown
   ------------------------------------------------------------------------------------------------
   Description      : Shutdown resp. re-initialize the CanTp.
                      Does nothing in case the CanTp never was initialized before.
   ------------------------------------------------------------------------------------------------
   Called by        : AUTOSAR EcuM
   ------------------------------------------------------------------------------------------------
   Parameter        : None
   ------------------------------------------------------------------------------------------------
   Returncode       : None
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_Shutdown(void)
{
  vCanTp_DetAssertVReturn(vCanTp_LData(InitState) == cCanTp_Initialized, CanTp_Shutdown_SId, CANTP_E_UNINIT)

  /* PRQA S 3355 QAC_L1 */ /* MD_CANTP_MISRA_3355 */
  /* PRQA S 3356 QAC_L1 */ /* MD_CANTP_MISRA_3356 */
  /* PRQA S 3358 QAC_L1 */ /* MD_CANTP_MISRA_3358 */
  /* PRQA S 3201 QAC_L1 */ /* MD_CANTP_MISRA_3201 */
  if(cCanTp_Initialized == vCanTp_LData(InitState))
  {
    vCanTp_InitFromLCfgPtr();
    vCanTp_LData(InitState) = cCanTp_Shutdown;
  }
  else
  { /* If an internal error occurs while stopping the CanTp the DEM module should be notified. */
#if(CANTP_OPER_NOT_SUPPORTED_REPORT_DEM == STD_ON)
    vCanTp_DemReportError(CanTp_E_Oper_Not_Supported, DEM_EVENT_STATUS_FAILED)
#else  /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */
    vCanTp_DetReportError(CanTp_Shutdown_SId, CanTp_E_Oper_Not_Supported)
#endif /* CANTP_OPER_NOT_SUPPORTED_REPORT_DEM */
  }
  /* PRQA  L:QAC_L1 */

} /* PRQA S 2006 */ /* MD_MSR_14.7 */
/* CanTp_Shutdown */


#if(CANTP_TX_CONFIRMATION_API == STD_ON)
/**************************************************************************************************
   Function name    : CanTp_TxConfirmation
   ------------------------------------------------------------------------------------------------
   Description      : get handle from pdu id and hand it to CanTp
   ------------------------------------------------------------------------------------------------
   Called by        : CanIf
   ------------------------------------------------------------------------------------------------
   Parameter        : PduIdType CanIfTxPduId: CanIfTxPduId of the CanIf of a transmitted CanTp-frame
   ------------------------------------------------------------------------------------------------
   Returncode       : void
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_TxConfirmation(PduIdType CanIfTxPduId)
{
  VAR(PduIdType, AUTOMATIC) tpHdl;
  vCanTp_TpRxStatePtrType   pTpRxState;
  vCanTp_TpTxStatePtrType   pTpTxState;


# if (CANTP_ENABLE_LLR_CALLOUTS == STD_ON)
  /* AR3-2539: pass TxConfirmation to low level routing module */
  if (vCanTp_LLR_TxConfirmation(CanIfTxPduId) == E_NOT_OK)
  {
    return;
  }
# endif


  vCanTp_DetAssertVReturn(vCanTp_LData(InitState) == cCanTp_Initialized,     CanTp_TxConfirmation_SId, CANTP_E_UNINIT)
# if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
  vCanTp_DetAssertVReturn(CanIfTxPduId <= CANTP_MAX_TXPDU_ID,                CanTp_TxConfirmation_SId, CANTP_E_INVALID_TX_ID)
# else
  vCanTp_DetAssertVReturn(CanIfTxPduId <= vCanTp_PBCfgPtr_(MaxCanIfTxPduId), CanTp_TxConfirmation_SId, CANTP_E_INVALID_TX_ID)
# endif

  pTpRxState = &vCanTp_RxState[0];
  pTpTxState = &vCanTp_TxState[0];
# if( CANTP_TX_SERIALIZE == STD_ON )
  tpHdl = vCanTp_TxSemaphore.hdl;
  vCanTp_TxSemaphore.hdl = CANTP_INVALID_HDL;
  if (tpHdl != CANTP_INVALID_HDL)
  {
    if(vCanTp_TxSemaphore.dir == CANTP_TX)
    { /* TX direction */
#  if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
      if(vCanTp_txHdlMap[tpHdl] != CANTP_INVALID_HDL)
#  endif
      {
        if(pTpTxState[TP_TX_HDL(tpHdl)].channel != CANTP_INVALID_HDL)
        {
          if(vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl,CANTP_TXNPDU_ID,CANTP_TX__TXNPDU_ID) == CanIfTxPduId)  /* PRQA S 3356 */ /* MD_CANTP_MISRA_3356 */ /* PRQA S 3359 */ /* MD_CANTP_MISRA_3359 */
          {                                                                                              /* PRQA S 3201 */ /* MD_CANTP_MISRA_3201 */
            vCanTp_CanIfTxConfirmation(CANTP_HDL_CVAL_FIRST  CANTP_TX);
          } /* PduId match */
        } /* valid hdl    */
      } /* valid dyn hdl */
    }
    else
    { /* RX direction */
#  if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
      if(vCanTp_rxHdlMap[tpHdl] != CANTP_INVALID_HDL)
#  endif
      {
        if(pTpRxState[TP_RX_HDL(tpHdl)].channel != CANTP_INVALID_HDL)
        {
          if(vCanTp_PBCfg(vCanTp_RxNsduCfg, tpHdl,CANTP_TXFC_NPDU_ID,CANTP_RX__TXFC_NPDU_ID) == CanIfTxPduId)  /* PRQA S 3356 */ /* MD_CANTP_MISRA_3356 */ /* PRQA S 3359 */ /* MD_CANTP_MISRA_3359 */
          {                                                                                                    /* PRQA S 3201 */ /* MD_CANTP_MISRA_3201 */
            vCanTp_CanIfTxConfirmation(CANTP_HDL_CVAL_FIRST  CANTP_RX);
          } /* PduId match */
        } /* valid hdl    */
      } /* valid dyn hdl */
    }
  } /* valid tpHdl */

#  if( CANTP_TX_SINGLE_SERIALIZE == STD_ON )
#  else
  if( (vCanTp_TxConflict.hdl[vCanTp_TxConflict.rdpos] != CANTP_INVALID_HDL) )
  { /* conflict to be solved */
    tpHdl = vCanTp_TxConflict.hdl[vCanTp_TxConflict.rdpos]; /* for the next transmission */
    vCanTp_TxConflict.hdl[vCanTp_TxConflict.rdpos] = CANTP_INVALID_HDL;
    if( (vCanTp_operatingType)(vCanTp_TxConflict.dir[vCanTp_TxConflict.rdpos]) == CANTP_TX)
    {
      vCanTp_TxStateTask(CANTP_HDL_CVAL_ONLY);
    }
    else
    {
      vCanTp_RxStateTask(CANTP_HDL_CVAL_ONLY);
    }
    vCanTp_TxConflict.rdpos++;
  }
#  endif
# else /* CANTP_TX_SERIALIZE */
#  if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#   if( CANTP_NUM_RX_CHANNELS == 1 )
  if(pTpRxState->channel != CANTP_INVALID_HDL)
  {
    {
      if( (pTpRxState->ChannelState == cRxState_WaitForFCConfIsr)     || 
          (pTpRxState->ChannelState == cRxState_WaitForFCWaitConfIsr) || 
          (pTpRxState->ChannelState == cRxState_WaitForFCOverConfIsr) )
      {
        if( (pTpRxState->frameType == cCanTp_FF) || (pTpRxState->frameType == cCanTp_CF) )
        { /* RX direction */
          if(vCanTp_PBCfg(vCanTp_RxNsduCfg,0,CANTP_TXFC_NPDU_ID,CANTP_RX__TXFC_NPDU_ID) == CanIfTxPduId)
          { /* Found */
            vCanTp_CanIfTxConfirmation(CANTP_HDL_CVAL_FIRST  CANTP_RX);
            return;
          }
        }
      }
    }
  }
#   else
  /* RX direction */
  tpHdl = CANTP_NUM_RX_CHANNELS;
  while(tpHdl > 0)
  {
    tpHdl--;
    if(pTpRxState[TP_RX_HDL(tpHdl)].channel != CANTP_INVALID_HDL)
    {
      {
        if( (pTpRxState[TP_RX_HDL(tpHdl)].ChannelState == cRxState_WaitForFCConfIsr)     || 
            (pTpRxState[TP_RX_HDL(tpHdl)].ChannelState == cRxState_WaitForFCWaitConfIsr) || 
            (pTpRxState[TP_RX_HDL(tpHdl)].ChannelState == cRxState_WaitForFCOverConfIsr) )
        {
          if( (pTpRxState[TP_RX_HDL(tpHdl)].frameType == cCanTp_FF) || (pTpRxState[TP_RX_HDL(tpHdl)].frameType == cCanTp_CF) )
          { /* RX direction */
            if(vCanTp_PBCfg(vCanTp_RxNsduCfg, tpHdl,CANTP_TXFC_NPDU_ID,CANTP_RX__TXFC_NPDU_ID) == CanIfTxPduId)
            { /* Found */
              vCanTp_CanIfTxConfirmation(CANTP_HDL_CVAL_FIRST  CANTP_RX);
              return;
            }
          }
        }
      }
    }
  }
#   endif
  if(pTpTxState->channel != CANTP_INVALID_HDL)
  { 
    {
      if( (pTpTxState->ChannelState == cTxState_WaitForSForFFConfIsr) || 
          (pTpTxState->ChannelState == cTxState_WaitForCFConfIsr) )
      {
        if(pTpTxState->frameType != cCanTp_FC)
        { /* TX direction */
          if(vCanTp_PBCfg(vCanTp_TxNsduCfg,0,CANTP_TXNPDU_ID,CANTP_TX__TXNPDU_ID) == CanIfTxPduId)
          { /* Found */
            vCanTp_CanIfTxConfirmation(CANTP_HDL_CVAL_FIRST  CANTP_TX);
          }
        }
      }
    }
  }
#  else /* CANTP_SINGLE_CONN_OPTIMIZED */
  /* TX direction */
  tpHdl = vCanTp_PBCfgPtr_(NumCanTpTxSduId);
  while(tpHdl > 0)
  {
    tpHdl--;
#   if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
    if(vCanTp_txHdlMap[tpHdl] == CANTP_INVALID_HDL) { continue; }  /* PRQA S 0770 */ /* MD_CANTP_MISRA_0770 */
#   endif
    if(pTpTxState[TP_TX_HDL(tpHdl)].channel != CANTP_INVALID_HDL)
    { 
      {
        if( (pTpTxState[TP_TX_HDL(tpHdl)].ChannelState == cTxState_WaitForSForFFConfIsr) || 
            (pTpTxState[TP_TX_HDL(tpHdl)].ChannelState == cTxState_WaitForCFConfIsr) )
        {
          if(pTpTxState[TP_TX_HDL(tpHdl)].frameType != cCanTp_FC)
          { /* TX direction */
            if(vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl,CANTP_TXNPDU_ID,CANTP_TX__TXNPDU_ID) == CanIfTxPduId)
            { /* Found */
              vCanTp_CanIfTxConfirmation(CANTP_HDL_CVAL_FIRST  CANTP_TX);
              return;
            }
          }
        }
      }
    }
  } /* endwhile TX direction */

  /* RX direction */
  tpHdl = vCanTp_PBCfgPtr_(NumCanTpRxSduId);
  while(tpHdl > 0)
  {
    tpHdl--;
#   if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
    if(vCanTp_rxHdlMap[tpHdl] == CANTP_INVALID_HDL) { continue; }  /* PRQA S 0770 */ /* MD_CANTP_MISRA_0770 */
#   endif
    if(pTpRxState[TP_RX_HDL(tpHdl)].channel != CANTP_INVALID_HDL)
    {
      {
        if( (pTpRxState[TP_RX_HDL(tpHdl)].ChannelState == cRxState_WaitForFCConfIsr)     || 
            (pTpRxState[TP_RX_HDL(tpHdl)].ChannelState == cRxState_WaitForFCWaitConfIsr) || 
            (pTpRxState[TP_RX_HDL(tpHdl)].ChannelState == cRxState_WaitForFCOverConfIsr) )
        {
          if( (pTpRxState[TP_RX_HDL(tpHdl)].frameType == cCanTp_FF) || (pTpRxState[TP_RX_HDL(tpHdl)].frameType == cCanTp_CF) )
          { /* RX direction */
            if(vCanTp_PBCfg(vCanTp_RxNsduCfg, tpHdl,CANTP_TXFC_NPDU_ID,CANTP_RX__TXFC_NPDU_ID) == CanIfTxPduId)
            { /* Found */
              vCanTp_CanIfTxConfirmation(CANTP_HDL_CVAL_FIRST  CANTP_RX);
              return;
            }
          }
        }
      }
    }
  } /* endwhile RX direction */
#  endif /* CANTP_SINGLE_CONN_OPTIMIZED */
# endif /* CANTP_TX_SERIALIZE */

  /* PRQA S 3200 4 */ /* RULE 16.10: No usage of return value intended. */

  return; /* MISRA */
} /* PRQA S 2006 */ /* RULE MD_MSR_14.7 */ /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* CanTp_TxConfirmation */
#endif


/**************************************************************************************************
   Function name    : vCanTp_CanIfTransmit
   ------------------------------------------------------------------------------------------------
   Description      : Passes the CanTp's request to transmit a data frame on the underlying 
                      bus system to the CanIf.
   ------------------------------------------------------------------------------------------------
   Called by        : CanTp itself
   ------------------------------------------------------------------------------------------------
   Parameter        : PduIdType tpHdl: actual connection
                      PduInfoType* TPCI: Pointer and length of the CanTp-generated TPCI
                      PduInfoType* payload: Pointer and length to the fragment of the payload the
                                            application wants to transmit via TP
                      vCanTp_FrameType FrameType: Detailed frame type so that the CanTp can decide
                                                whether a real or a dummy TxConfirmation shall be
                                                given or whether the channel will be closed down
                                                after that frame.
   ------------------------------------------------------------------------------------------------
   Returncode       : vCanTp_TxReturnType: Preprocessed return code of the CanIf_Transmit()-call
                                         (See definition of vCanTp_TxReturnType for details)
   ------------------------------------------------------------------------------------------------
   Misc             : NOTE: Rx/Tx can be determined by looking at frame type

**************************************************************************************************/
STATIC FUNC(vCanTp_TxReturnType, CANTP_CODE) vCanTp_CanIfTransmit(CANTP_HDL_PVAL_FIRST
                                                                  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) TPCI, 
                                                                  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) payload, 
                                                                  vCanTp_FrameType FrameType)
{
  VAR(PduIdType, AUTOMATIC)            TxPduId;
  VAR(uint16, AUTOMATIC)               CanTpDL;
  VAR(vCanTp_TxReturnType, AUTOMATIC)  ret;
  VAR(Std_ReturnType, AUTOMATIC)       canIfRet;
#if (CANTP_PADDING_ACTIVE == STD_ON)
  VAR(uint8, AUTOMATIC)                padding;
#endif
#if( ((CANTP_PADDING_ACTIVE == STD_ON) && (CANTP_HAVE_PADDING_BYTE   == STD_ON )) ||  \
     ((CANTP_TX_SERIALIZE   == STD_ON) && (CANTP_TX_SINGLE_SERIALIZE == STD_OFF)) )
  VAR(sint8, AUTOMATIC)                i;
# endif
#if( CANTP_TX_SERIALIZE == STD_ON )
  VAR(PduIdType, AUTOMATIC)            SduHdl;
  VAR(vCanTp_operatingType, AUTOMATIC) direction;
#endif
  VAR(PduInfoType, AUTOMATIC)          PduInfo;
  VAR(uint8, AUTOMATIC)                canIfTxBuf[CANTP_MAX_FRAME_LENGTH];
  P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)pBuf;
  VAR(PduLengthType, AUTOMATIC)        frameIndex;
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# if( CANTP_NUM_RXSDUS >= 2 )
#  if( CANTP_USE_DUMMY_STATEMENT == STD_ON )
  (void)tpHdl; /* avoid warning */  /* PRQA S 3112 */ /* MD_CANTP_MISRA_3112 */
#  endif
# endif
#else
  P2CONST(vCanTp_RxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pRxNsduCfg;
  P2CONST(vCanTp_TxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pTxNsduCfg;
#endif

  vCanTp_AssertReturn((payload != NULL_PTR),              vCanTp_CanIfTransmit_SId, CANTP_E_INVALID_TX_BUFFER, 0, cCanTp_TxNotOk)
  vCanTp_AssertReturn((TPCI    != NULL_PTR),              vCanTp_CanIfTransmit_SId, CANTP_E_INVALID_TX_BUFFER, 1, cCanTp_TxNotOk)
  vCanTp_AssertReturn((FrameType != cCanTp_InvalidFrame), vCanTp_CanIfTransmit_SId, CANTP_E_PARAM_CONFIG,      0, cCanTp_TxNotOk)

#if (CANTP_PADDING_ACTIVE == STD_ON)
  /* PRQA S 3198 2 */ /* Initial assignment for safety reasons. */
  padding = STD_OFF;
#endif

  /* TxPduId = CANTP_INVALID_HDL; not necessary */
  ret     = cCanTp_TxNotOk;
  PduInfo.SduDataPtr = canIfTxBuf;
  /* PduInfo.SduLength  = 0; not necessary */
  pBuf       = PduInfo.SduDataPtr;
  frameIndex = 0;

#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
  pRxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_RxNsduCfg, TPRXHDL));
  pTxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_TxNsduCfg, TPTXHDL));
#endif

  /* Recognize PduId */
  if(FrameType == cCanTp_FC) 
  { /* RX direction */
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
    vCanTp_DetAssertReturn(TP_RX_HDL(tpHdl) < vCanTp_PBCfgPtr_(NumCanTpRxSduId), CanTp_MFuncTx_SId, CANTP_E_INVALID_RX_ID, cCanTp_TxNotOk)
#endif

    TxPduId    = CANTP_RX1_CFG_PTR(tpHdl, CANTP_TXFC_NPDU_ID, CANTP_RX__TXFC_NPDU_ID);
    CanTpDL    = CANTP_RX1_CFG_PTR__DL(tpHdl);
#if( CANTP_PADDING_ACTIVE == STD_ON )
# if( (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON) || (CANTP_CONSTANT_RX__PADDING_ACTIVATION == STD_ON) )
    padding = CANTP_RX__PADDING_ACTIVATION;  
# else
    if(CANTP_RX_CFG_PTR__PADDING_ACTIVATION(TP_RX_HDL(tpHdl)) == STD_ON )
    { 
      padding = STD_ON;  
    }
# endif
#endif

    /* Assemble AI into the frame buffer */
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON ) || ( CANTP_CONSTANT_RX__ADDRESSING_FORMAT == STD_ON )
# if(CANTP_RX__ADDRESSING_FORMAT == CANTP_EXTENDED)
    { /* Target address  */
      *pBuf = CANTP_RX1_CFG_PTR(tpHdl, CANTP_TXFC_NTA, CANTP_RX__TXFC_NTA); /* TPCI begins here: */
      pBuf++;
    }
# elif(CANTP_RX__ADDRESSING_FORMAT == CANTP_MIXED11)
    { /* Address extension  */
      *pBuf = CANTP_RX1_CFG_PTR(tpHdl, CANTP_RX_NTA, CANTP_RX__RX_NTA); /* TPCI begins here: */
      pBuf++;
    }
# endif
#else
    if(CANTP_RX_CFG_PTR__ADDRESSING_FORMAT(TP_RX_HDL(tpHdl)) == CANTP_EXTENDED)
    { /* Target address  */
      *pBuf = CANTP_RX_CFG_PTR(TP_RX_HDL(tpHdl), CANTP_TXFC_NTA, CANTP_RX__TXFC_NTA); /* TPCI begins here: */
      pBuf++;
    }
    else if(CANTP_RX_CFG_PTR__ADDRESSING_FORMAT(TP_RX_HDL(tpHdl)) == CANTP_MIXED11)
    { /* Adress extension  */
      *pBuf = CANTP_RX_CFG_PTR(TP_RX_HDL(tpHdl), CANTP_RX_NTA, CANTP_RX__RX_NTA); /* TPCI begins here: */
      pBuf++;
    }
    else { /* MISRA */ }
#endif
  }
  else
  { /* TX direction */
#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
#else
    vCanTp_DetAssertReturn(TP_TX_HDL(tpHdl) < vCanTp_PBCfgPtr_(NumCanTpTxSduId), CanTp_MFuncTx_SId, CANTP_E_INVALID_TX_ID, cCanTp_TxNotOk)
#endif
    TxPduId    = CANTP_TX_CFG_PTR(CANTP_TXNPDU_ID, CANTP_TX__TXNPDU_ID);
    CanTpDL    = CANTP_TX_CFG_PTR__DL();

#if( CANTP_PADDING_ACTIVE == STD_ON )
# if( (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON) || (CANTP_CONSTANT_TX__PADDING_ACTIVATION == STD_ON) )
    padding = CANTP_TX__PADDING_ACTIVATION;  
# else
    if(CANTP_TX_CFG_PTR__PADDING_ACTIVATION() == STD_ON )
    { 
      padding = STD_ON;  
    }
# endif
#endif

    frameIndex = vCanTp_TxState[TP_TX_HDL(tpHdl)].FrameIndex;
    /* Assemble AI into the frame buffer */
#if( ((CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON)  || (CANTP_CONSTANT_TX__ADDRESSING_FORMAT == STD_ON)) )
# if( (CANTP_TX__ADDRESSING_FORMAT == CANTP_EXTENDED) || (CANTP_TX__ADDRESSING_FORMAT == CANTP_MIXED11) )
    { /* Target address / Address extension  */
      *pBuf = CANTP_TX_CFG_PTR(CANTP_TX_NTA, CANTP_TX__TX_NTA); /* TPCI begins here: */
      pBuf++;
    }
# endif
#else
    if( (CANTP_TX_CFG_PTR__ADDRESSING_FORMAT() == CANTP_EXTENDED) ||
        (CANTP_TX_CFG_PTR__ADDRESSING_FORMAT() == CANTP_MIXED11) )
    { /* Target address / Address extension  */
      *pBuf = CANTP_TX_CFG_PTR(CANTP_TX_NTA, CANTP_TX__TX_NTA); /* TPCI begins here: */
      pBuf++;
    }
#endif
  }

  if(TxPduId != CANTP_INVALID_HDL)  /* PRQA S 3355 */ /* MD_CANTP_MISRA_3355 */ /* PRQA S 3358 */ /* MD_CANTP_MISRA_3358 */
  { /* Assemble Tx frame */
    /* Copy TPCI */
    /* PRQA S 0505 3 */ /* MD_CANTP_MISRA_0505 */
    vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(pBuf), (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(TPCI->SduDataPtr), TPCI->SduLength);
    pBuf += TPCI->SduLength;
    if(payload->SduDataPtr != NULL_PTR) /* is it a FC */
    { /* Copy fragment */
      vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(pBuf), 
                    (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(vCanTp_txBuf[TP_TX_HDL(tpHdl)]), 
                     frameIndex);
      pBuf += frameIndex;
      /* Copy payload */
      frameIndex = (payload->SduLength - frameIndex);
      vCanTp_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(pBuf), (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(payload->SduDataPtr), frameIndex);
      pBuf += frameIndex;
    }

    PduInfo.SduLength = ((uint8)(pBuf-PduInfo.SduDataPtr));  /* length of the frame right now */
    if(PduInfo.SduLength > 0)
    { /* data found */
#if( CANTP_PADDING_ACTIVE == STD_ON )
      if(padding == STD_ON )  /* PRQA S 3355 */ /* MD_CANTP_MISRA_3355 */ /* PRQA S 3358 */ /* MD_CANTP_MISRA_3358 */ /* PRQA S 3356 */ /* MD_CANTP_MISRA_3356 */ /* PRQA S 3359 */ /* MD_CANTP_MISRA_3359 */
      {                       /* PRQA S 3201 */ /* MD_CANTP_MISRA_3201 */
# if( CANTP_HAVE_PADDING_BYTE == STD_ON )
        i = cCanTp_FrameLength;
        while(i > PduInfo.SduLength)
        { /* fill up remaining bytes */
          i--;
          PduInfo.SduDataPtr[i] = CANTP_PADDING_PATTERN;
        }
# endif
        PduInfo.SduLength = cCanTp_FrameLength; /* adapt the length for CanIf */
      }
#endif
      /* *****************************************************************
      * Transmit the frame in case one Pdu has been found "free" for use *
      ****************************************************************** */
      if(PduInfo.SduLength >= CanTpDL)  /* PRQA S 3355 */ /* MD_CANTP_MISRA_3355 */ /* PRQA S 3358 */ /* MD_CANTP_MISRA_3358 */
      {
#if ( CANTP_TX_SERIALIZE == STD_ON )
        if(FrameType == cCanTp_FC)
        {
          SduHdl = (TPRXHDL);
          direction = CANTP_RX;
        }
        else
        {
          SduHdl = (TPTXHDL);
          direction = CANTP_TX;
        }

        /* PRQA S 3198 2 */ /* Initial assignment for safety reasons. */
        canIfRet = E_OK; /* assume everything will be fine */
        if(vCanTp_TxSemaphore.hdl == CANTP_INVALID_HDL)
        { /* Tx currently unused, transmit now */

# if (CANTP_ENABLE_LLR_CALLOUTS == STD_ON)
          /* AR3-2539: pass CanIf_Transmit request to low level routing module */
          canIfRet = vCanTp_LLR_CanIf_Transmit(TxPduId, &PduInfo);
          if (canIfRet != E_NOT_OK)
          {
            canIfRet = CanIf_Transmit(TxPduId, &PduInfo);
          }
# else
          canIfRet = CanIf_Transmit(TxPduId, &PduInfo);
# endif

          if(canIfRet == E_OK)
          {
            vCanTp_TxSemaphore.hdl = SduHdl;
            vCanTp_TxSemaphore.dir = direction;
          }
        }
        else
        { /* await confirmation of the transmission currently in process */
# if ( CANTP_TX_SINGLE_SERIALIZE == STD_ON )
# else
          if(vCanTp_TxConflict.hdl[vCanTp_TxConflict.wrpos] == CANTP_INVALID_HDL)
          { /* request buffer still available, get the number of current entries */
            if((vCanTp_TxConflict.wrpos) > (vCanTp_TxConflict.rdpos))
            {
              i = (vsint8)((vCanTp_TxConflict.wrpos) - (vCanTp_TxConflict.rdpos));
            }
            else if((vCanTp_TxConflict.wrpos) < (vCanTp_TxConflict.rdpos))
            {
              i = (vsint8)( ((CANTP_TX_MAX_NUM_CONFLICT) - (vCanTp_TxConflict.rdpos)) + (vCanTp_TxConflict.wrpos) );
            }
            else
            {
              i = 0;
            }
            vCanTp_TxConflict.idx = vCanTp_TxConflict.rdpos; /* need a struct due to the bittype turnaround */
            while(i > 0)
            { /* check the request buffer to avoid multiple entries with the same id due to a retry */
              if( (vCanTp_TxConflict.hdl[vCanTp_TxConflict.idx] == SduHdl) && (vCanTp_TxConflict.dir[vCanTp_TxConflict.idx] == direction) )
              { /* already stored, repeatedly called from task level */
                return(cCanTp_TxNotOk);
              }
              i--;
              (vCanTp_TxConflict.idx)++;  /* wrap around is done using a bittype */
            }
            vCanTp_TxConflict.hdl[vCanTp_TxConflict.wrpos] = SduHdl;
            vCanTp_TxConflict.dir[vCanTp_TxConflict.wrpos] = (uint8)direction;
            vCanTp_TxConflict.wrpos++;   /* wrap around is done using a bittype */
          }
          else
          { /* try to resolve conflict from task level */
          }
# endif
          canIfRet = E_NOT_OK;
        }
#else
        canIfRet = CanIf_Transmit(TxPduId, &PduInfo);
#endif
        if(E_OK == canIfRet)
        { /* Pdu is "in use" now */
          ret = cCanTp_TxOk;
          vCanTp_TxApplTxFrameConfirmation(TxPduId, PduInfo);
        }
        else
        {
          vCanTp_Error(vCanTp_CanIfTransmit_SId, CANTP_CANIF_ERR, TxPduId);
        }
      }
      else
      { /* PRQA S 3201 */ /* MD_CANTP_MISRA_3201 */
        /* A transmit N-PDU < min. length configured is considered corrupt */
        vCanTp_DetReportError(CanTp_Transmit_SId, CANTP_E_PARAM_CONFIG)
      }
    }
    else
    { /* Assert that a Pdu to send has been found */
      vCanTp_AssertAlways(vCanTp_CanIfTransmit_SId, CANTP_TXPDU_ADMIN_ERR, (uint16)TP_TX_HDL(tpHdl), cCanTp_TxNotOk)
    }
  }

  return ret;
} /* PRQA S 2006 */ /* MD_MSR_14.7 */  /* PRQA S 6010 */ /* MD_MSR_STPTH */  /* PRQA S 6030 */ /* MD_MSR_STCYC */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* vCanTp_CanIfTransmit */


#if( (CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON) && (CANTP_ENABLE_WRAP_CANCEL_TRANSMIT == STD_ON) )
/**************************************************************************************************
   Function name    : CanTpWrapper_CancelTransmitRequest
   ------------------------------------------------------------------------------------------------
   Description      : Before calling CanTpWrapper_TransmitRequest to de-wrap the user defined NSDU-ID.
   ------------------------------------------------------------------------------------------------
   Called by        : Pdu-Router or other application
   ------------------------------------------------------------------------------------------------
   Parameter        : PduIdType CanTpTxSduId - contains the CanTp unique identifier of the N-SDU 
                                               which transfer has to be cancelled.
   ------------------------------------------------------------------------------------------------
   Returncode       : Std_ReturnType: E_OK: Cancellation request of the transfer (SENDING or RECEIVING) 
                                            of the specified N-SDU is accepted.
                                      E_NOT_OK: Cancellation request of the transfer of the specified 
                                            N-SDU is rejected (e. g. cancellation is requested
                                            at the receiver in an 1:n connection or in an unsegmented
                                            transfer at the receiver or cancellation is not allowed for 
                                            the corresponding channel).
   ------------------------------------------------------------------------------------------------
   Misc             : Note that if a transfer is in progress, that will generate a time-out error 
                      on the receiver side.
**************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTpWrapper_CancelTransmitRequest(PduIdType CanTpTxSduId)
{
# if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
# else
  VAR(PduIdType, AUTOMATIC)       tpHdl;
  VAR(uint8,     AUTOMATIC)       found;
# endif
  VAR(Std_ReturnType, AUTOMATIC)  rc;

# if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
  rc = CanTp_CancelTransmitRequest(CanTpTxSduId);
# else
  rc    = E_NOT_OK; 
  found = 0;
  tpHdl = vCanTp_PBCfgPtr_(NumCanTpTxSduId);
  while(tpHdl > 0)
  { /* search the SduId belonging to the remapped SduId */
    tpHdl--;
    if(vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl, CANTP_REMAP_TXNSDU_ID, CANTP_TX__REMAP_TXNSDU_ID) == CanTpTxSduId)
    { /* found matching remapped id */
      /* tpHdl = vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl, CANTP_TXNSDU_ID, CANTP_TX__TXNSDU_ID); implicitly done by sorted ids within generated data */
      found = 1;
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
  }

  vCanTp_DetAssert((found > 0), CanTp_Transmit_SId, CANTP_E_PARAM_ID)
  if(found != 0)
  { /* matching SduId found */
    rc = CanTp_CancelTransmitRequest(tpHdl);
  }
# endif /* (CANTP_SINGLE_CONN_OPTIMIZED) */

  if(rc == E_OK)
  {
    Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);  /* CanTpWrapper_CancelTransmitRequest */
    vCanTp_TxInit(CanTpTxSduId, (NotifResultType)NTFRSLT_E_CANCELATION_OK);
    Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* CanTpWrapper_CancelTransmitRequest */
  }
#if( CANTP_TC_NOTIFY_ALWAYS == STD_ON )
  else
  {
    vCanTp_TxApplTxConfirmation(0, CanTpTxSduId, NTFRSLT_E_CANCELATION_NOT_OK);
  }
#endif

  return(rc);
} /* CanTpWrapper_CancelTransmitRequest() */
#endif


#if( CANTP_TC == STD_ON )
/**************************************************************************************************
   Function name    : CanTp_CancelTransmitRequest
   ------------------------------------------------------------------------------------------------
   Description      : Used to cancel the transfer of pending N-SDUs. The connection is identified 
                      by CanTpTxSduId. This function has to be called with the PDU-Id of the CanTp 
                      (i. e. the upper layer has to translate its own PDU-Id into the one of the TP 
                       for the corresponding message).
   ------------------------------------------------------------------------------------------------
   Called by        : Pdu-Router or other application
   ------------------------------------------------------------------------------------------------
   Parameter        : PduIdType CanTpTxSduId - contains the CanTp unique identifier of the N-SDU 
                                               which transfer has to be cancelled.
   ------------------------------------------------------------------------------------------------
   Returncode       : Std_ReturnType: E_OK: Cancellation request of the specified N-SDU is accepted.
                                      E_NOT_OK: Cancellation request is rejected; the reason can be 
                                            - request is issued for an N-SDU that is not segmented, or 
                                            - request is issued for an N-SDU that is not in the reception process
   ------------------------------------------------------------------------------------------------
   Misc             : Note that if a transfer is in progress, that will generate a time-out error 
                      on the receiver side.
   Use case         : Cancel a diagnostic transmission due to the reception of another 
                      diagnostic protocol with higher priority.
**************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelTransmitRequest(PduIdType CanTpTxSduId)  
{ /*  The transmit cancellation feature allows the upper layer to cancel a transmission in progress.
      Use case: Cancel a diagnostic transmission due to the reception of another diagnostic protocol with higher priority. 
      CANTP242: This feature shall be (de)activated by static configuration (parameter CanTpTc).
      CANTP243: After the call of the service CanTp_CancelTransmitRequest(), the transfer on this connection shall be aborted.
      CANTP244: The Api PduR_CanTpTxConfirmation() shall be called after a transmit cancellation with value NTFRSLT_E_CANCELATION_OK.
      CANTP254: If development error detection is enabled the function CanTp_CancelTransmitRequest shall check the validity of CanTpTxSduId parameter. 
                If the parameter value is invalid: 
                  - raise development error CANTP_E_PARAM_ID and return E_NOT_OK.
                If the parameter value indicates a cancel request for an N-SDU that is not on transmission process: 
                  - call DEM with EventId = CANTP_E_OPER_NOT_SUPPORTED, EventStatus = DEM_EVENT_STATUS_PREFAILED and return E_NOT_OK.
      CANTP255: If successfully executed: call the PduR_CanTpTxConfirmation with notification result NTFRSLT_E_CANCELATION_OK.
      CANTP256: The CanTp shall abort the transmission of the current N-SDU if the service returns E_OK.
      CANTP274: Transmit Cancellation is triggered by the call of CanTp_CancelTransmitRequest().

      Return value:
      E_OK:       Cancellation request of the specified N-SDU is accepted.
      E_NOT_OK:   Cancellation request is rejected; the reason can be that 
                  - request is issued for an N-SDU that is not segmented, 
                  - request is issued after the last CF has been requested for transmission or 
                  - cancellation is not possible for the related N-SDU due to configuration.
  */

  vCanTp_TpTxStatePtrType         pTpTxState;
  VAR(Std_ReturnType, AUTOMATIC)  retc;
  VAR(PduIdType, AUTOMATIC)       tpHdl;
# if( (CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON) && (CANTP_ENABLE_WRAP_CANCEL_TRANSMIT == STD_OFF) )
  VAR(uint8, AUTOMATIC)           found;
# endif
# if( CANTP_CONSTANT_TX__TC == STD_ON )
# else
  P2CONST(vCanTp_TxNsduCfgType, AUTOMATIC, CANTP_APPL_CONST) pTxNsduCfg;
# endif

  vCanTp_DetAssertReturn((vCanTp_LData(InitState) == cCanTp_Initialized), CanTp_CancelTransmitRequest_SId, CANTP_E_UNINIT, E_NOT_OK) /* CanTp293 */
  retc  = E_OK;
# if((( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON ) && ( CANTP_ENABLE_WRAP_CANCEL_TRANSMIT == STD_ON ) )  ||\
     ( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_OFF) )
  tpHdl = CanTpTxSduId;
# endif

# if ( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON )
#  if( CANTP_ENABLE_WRAP_CANCEL_TRANSMIT == STD_ON )
#  else
  tpHdl = vCanTp_PBCfgPtr_(NumCanTpTxSduId);
  found = 0;
  while(tpHdl > 0)
  { /* search the SduId belonging to the remapped SduId */
    tpHdl--;
    if(vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl, CANTP_REMAP_TXNSDU_ID, CANTP_TX__REMAP_TXNSDU_ID) == CanTpTxSduId)
    { /* found matching remapped id */
      found = 1;
      CANIF_CANCELTRANSMIT(vCanTp_PBCfg(vCanTp_TxNsduCfg, tpHdl, CANTP_TXNPDU_ID, CANTP_TX__TXNPDU_ID));
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
  }
  if(found == 0)
  { /* no matching SduId found */
    vCanTp_DetReportError(CanTp_CancelTransmitRequest_SId, CANTP_E_PARAM_ID);
    retc  = E_NOT_OK;
  }
#  endif /* CANTP_ENABLE_WRAP_CANCEL_TRANSMIT */
# endif  /* CANTP_ENABLE_TX_NSDU_REMAPPING    */

# if( CANTP_CONSTANT_TX__TC == STD_ON )
#  if( CANTP_TX__TC == STD_OFF )
  retc = E_NOT_OK; /* cancellation disabled for all N-SDU-IDs */
#  endif
# else
  pTxNsduCfg = &(vCanTp_PBCfgPtr(vCanTp_TxNsduCfg, TPTXHDL));
# endif

# if( ( CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON ) && ( CANTP_ENABLE_WRAP_CANCEL_TRANSMIT == STD_OFF ) )
  if(retc == E_OK)
# endif
  {
    if(tpHdl >= CanTpGET_NumCanTpTxSduId)
    { /* invalid Sdu-Id */
      vCanTp_DetReportError(CanTp_CancelTransmitRequest_SId, CANTP_E_PARAM_ID)
      retc = E_NOT_OK;
    }
    else
    { /* valid id */
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
      Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);   /* CanTp_CancelTransmitRequest */
      if( (vCanTp_txHdlMap[tpHdl] == CANTP_INVALID_HDL) )
      { /* no transmission in progress */
        Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0); /* CanTp_CancelTransmitRequest */

        vCanTp_DemReportErrorCancelNotSupported(CanTp_CancelTransmitRequest_SId)
        retc = E_NOT_OK;
      }
      else
# endif
      {
        pTpTxState = &vCanTp_TxState[TP_TX_HDL(CanTpTxSduId)]; 
        if(pTpTxState->ChannelState == cTxState_Idle)
        { /* no transmission in progress */
          vCanTp_DemReportErrorCancelNotSupported(CanTp_CancelTransmitRequest_SId)
          retc = E_NOT_OK;
        }
        else
        { /* neither invalid Sdu-Id nor idle process detected */
          if(pTpTxState->frameType == cCanTp_SF)
          { /* unsegmented transmission */
            retc = E_NOT_OK;
          }
          else
          { /* is it the last CF */
            if(pTpTxState->OverallDataIndex >= pTpTxState->DataLength)
            { /* Last CF already given to CanIf */
              retc = E_NOT_OK;
            }    
            else
            { /* is the cancellation of this N-SDU-ID enabled */ 
# if( CANTP_CONSTANT_TX__TC == STD_ON )
              /* cancellation enabled for N-SDU-IDs (CANTP_TX__TC must be STD_ON here) */
# else  /* CANTP_CONSTANT_TX__TC */
              if(CANTP_TX_CFG_PTR__TC() == STD_OFF)
              { /* cancellation not allowed for this N-SDU-ID */
                retc = E_NOT_OK;
              }    
              else
# endif  /* CANTP_CONSTANT_TX__TC */
              { /* stop transmission and inform PduR */
# if ( CANTP_ENABLE_WRAP_CANCEL_TRANSMIT == STD_OFF )
#  if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_OFF )
                Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);  /* CanTp_CancelTransmitRequest */
#  endif
                vCanTp_TxInit(CANTP_HDL_CVAL_FIRST (NotifResultType)NTFRSLT_E_CANCELATION_OK);
#  if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_OFF )
                Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* CanTp_CancelTransmitRequest */
#  endif
# endif
              } /* endelse stop transmission  */
            } /* endelse cancellation enabled */
          } /* endelse last CF                */
        } /* endelse transmission in progress */
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
        Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* CanTp_CancelTransmitRequest */
# endif
      } /* endelse CANTP_INVALID_HDL */
    } /* endelse valid id */
  } /* endif (retc ==  E_OK) */

# if( CANTP_TC_NOTIFY_ALWAYS == STD_ON )
  if(retc != E_OK)
  {
#  if( CANTP_ENABLE_WRAP_CANCEL_TRANSMIT == STD_ON )
#  else
    vCanTp_TxApplTxConfirmation(tpHdl, CanTpTxSduId, NTFRSLT_E_CANCELATION_NOT_OK);
#  endif
  }
# endif

  return(retc);
} /* PRQA S 2006 */ /* MD_MSR_14.7 */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* CanTp_CancelTransmitRequest */
#endif /* CANTP_TC == STD_ON */



#if( CANTP_RC == STD_ON )
/**************************************************************************************************
   Function name    : CanTp_CancelReceiveRequest
   ------------------------------------------------------------------------------------------------
   Description      : Used to cancel the reception of N-SDUs. The connection is identified 
                      by CanTpRxSduId. This function has to be called with the PDU-Id of the CanTp 
                      (i. e. the upper layer has to translate its own PDU-Id into the one of the TP 
                       for the corresponding message).
   ------------------------------------------------------------------------------------------------
   Called by        : Pdu-Router or other application
   ------------------------------------------------------------------------------------------------
   Parameter        : PduIdType CanTpRxSduId - contains the CanTp unique identifier of the N-SDU 
                                               for which the reception has to be cancelled.
   ------------------------------------------------------------------------------------------------
   Returncode       : Std_ReturnType: E_OK: Cancellation request of the specified N-SDU is accepted.
                                      E_NOT_OK: Cancellation request of the specified 
                                            N-SDU is rejected (e. g. cancellation is requested
                                            for an N-SDU that is not segmented or not in the 
                                            reception process.
   ------------------------------------------------------------------------------------------------
   Misc             : Note that if a transfer is in progress, that will generate a time-out error 
                      on the receiver side.
**************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelReceiveRequest(PduIdType CanTpRxSduId)
{ /*  This service cancels the reception of an N-SDU initiated by the reception of a First Frame and consequently calls of PduR_StartOfReception.
      CANTP260: If development error detection is enabled: check the validity of CanTpRxSduId parameter. 
                If the parameter value is invalid: 
                - raise the development error CANTP_E_PARAM_ID
                - return E_NOT_OK.
                If the parameter value indicates a cancel reception request for an N-SDU that it is not on reception process
                - call the DEM with EventId = CANTP_E_OPER_NOT_SUPPORTED, EventStatus = DEM_EVENT_STATUS_PREFAILED
                - return E_NOT_OK.
      CANTP261: The CanTp shall abort the reception of the current N-SDU if the service returns E_OK.
      CANTP262: The CanTp shall reject the request for receive cancellation
                - in case of a Single Frame reception or 
                - if the CanTp is in the process of receiving the last CF (i.e. the service is called after N-Cr timeout is started for the last CF). 
                In this case the CanTp shall return E_NOT_OK.
      CANTP263: If the CanTp_CancelReceiveRequest service has been successfully executed: call PduR_CanTpRxIndication(NTFRSLT_E_CANCELATION_OK)
  
      E_OK:     Cancellation request of the specified N-SDU is accepted.
      E_NOT_OK: Cancellation request is rejected; the reason can be that 
                - request is issued for an N-SDU that is not segmented, 
                - request is issued for an N-SDU that is not in the reception process. */

  vCanTp_TpRxStatePtrType         pTpRxState;
  VAR(Std_ReturnType, AUTOMATIC)  retc;
  VAR(PduIdType, AUTOMATIC)       tpHdl;
# if( (CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON) )
  VAR(uint8, AUTOMATIC)           found;
# endif

  vCanTp_DetAssertReturn((vCanTp_LData(InitState) == cCanTp_Initialized), CanTp_CancelReceiveRequest_SId, CANTP_E_UNINIT, E_NOT_OK) /* CanTp293 */
  retc  = E_OK;

# if( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
  tpHdl = vCanTp_PBCfgPtr_(NumCanTpRxSduId);
  found = 0;
  while(tpHdl > 0)
  { /* search the SduId belonging to the remapped SduId */
    tpHdl--;
    if(vCanTp_PBCfg(vCanTp_RxNsduCfg, tpHdl, CANTP_REMAP_RXNSDU_ID, CANTP_RX__REMAP_TXNSDU_ID) == CanTpRxSduId)
    { /* found matching remapped id */
      found = 1;
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
  }
  if(found == 0)
  { /* no matching SduId found */
    vCanTp_DetReportError(CanTp_CancelReceiveRequest_SId, CANTP_E_PARAM_ID);
    retc  = E_NOT_OK;
  }
# elif ( defined(CANTP_GEN_GENERATOR_MSR) && (CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_OFF) )
  tpHdl = CANTP_INVALID_HDL;
  if(CanTpRxSduId < CanTpGET_NumCanTpRxSduId)
  {
    tpHdl = vCanTp_PduRIdMap[CanTpRxSduId];
  }
#else
  tpHdl = CanTpRxSduId;
#endif


# if( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
  if(retc == E_OK)
# endif
  {
    if(tpHdl >= CanTpGET_NumCanTpRxSduId)
    { /* invalid Sdu-Id */
      vCanTp_DetReportError(CanTp_CancelReceiveRequest_SId, CANTP_E_PARAM_ID)
      retc = E_NOT_OK;
    }
    else 
    { /* valid id */
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
      Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);    /* CanTp_CancelReceiveRequest */
      if( (vCanTp_rxHdlMap[tpHdl] == CANTP_INVALID_HDL) )
      { /* no reception in progress */
        Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* CanTp_CancelReceiveRequest */

        vCanTp_DemReportErrorCancelNotSupported(CanTp_CancelReceiveRequest_SId)
        retc = E_NOT_OK;
      }
      else
# endif
      {
        pTpRxState = &vCanTp_RxState[TP_RX_HDL(tpHdl)];
        if(pTpRxState->ChannelState == cRxState_Idle)
        { /* no reception in progress */
          vCanTp_DemReportErrorCancelNotSupported(CanTp_CancelReceiveRequest_SId)
          retc = E_NOT_OK;
        }
        else
        { /* neither invalid Sdu-Id nor idle process detected */
          if(pTpRxState->frameType == cCanTp_SF)
          { /* unsegmented reception */
            retc = E_NOT_OK;
          }
          else
          { /* is the reception in process */
            if( (pTpRxState->ApplState == (uint8)(CANTP_APPL_NOT_INFORMED)) ||   /* no buffer provision request up to now */
                (pTpRxState->DataIndex >= pTpRxState->DataLength) )              /* last CF already received */
            { 
              retc = E_NOT_OK;
            }    
            else
            { /* stop reception and inform PduR */
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_OFF )
              Tp_AsrTpCan_EnterCritical(CANTP_EXCLUSIVE_AREA_0);  /* CanTp_CancelReceiveRequest */
# endif
# if( CANTP_ENABLE_RX_NSDU_REMAPPING == STD_ON )
#  if defined( CANTP_ENABLE_SINGLE_CONN )
              vCanTp_RxInit(              (NotifResultType)NTFRSLT_E_CANCELATION_OK, cCanTp_Initialize);
#  else
              vCanTp_RxInit(CanTpRxSduId, (NotifResultType)NTFRSLT_E_CANCELATION_OK, cCanTp_Initialize);
#  endif
# else
              vCanTp_RxInit(CANTP_HDL_CVAL_FIRST (NotifResultType)NTFRSLT_E_CANCELATION_OK, cCanTp_Initialize);
# endif
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_OFF )
              Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);  /* CanTp_CancelReceiveRequest */
# endif
            }
          }
        }
# if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
        Tp_AsrTpCan_LeaveCritical(CANTP_EXCLUSIVE_AREA_0);    /* CanTp_CancelReceiveRequest */
# endif
      } /* endelse CANTP_INVALID_HDL */
    } /* endelse valid id */
  } /* endif (retc == E_OK) */

# if( CANTP_RC_NOTIFY_ALWAYS == STD_ON )
  if(retc != E_OK)
  {
    vCanTp_RxApplRxIndication(tpHdl, CanTpRxSduId, NTFRSLT_E_CANCELATION_NOT_OK);
  }
# endif

  return(retc);
} /* PRQA S 2006 */ /* MD_MSR_14.7 */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* CanTp_CancelReceiveRequest */
#endif /* CANTP_RC */



/**************************************************************************************************
   Function name    : vCanTp_MemCpy
   ------------------------------------------------------------------------------------------------
   Description      : Copy N-bytes from src to dest.
   ------------------------------------------------------------------------------------------------
   Called by        : -
   ------------------------------------------------------------------------------------------------
   Parameter        : uint8* pDest    <=> destination ptr.
                      uint8* pSrc     <=> source ptr.
                      uint16 nCnt     <=> no of bytes to copy
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void, CANTP_CODE) vCanTp_MemCpy(P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest, 
                                              P2CONST(uint8, AUTOMATIC, CANTP_APPL_DATA) pSrc, 
                                              uint16 nCnt)
{
  vCanTp_DetAssertVReturn(pDest, vCanTp_MemCpy_SId, CANTP_E_NULL_PTR)
  vCanTp_DetAssertVReturn(pSrc,  vCanTp_MemCpy_SId, CANTP_E_NULL_PTR)
  
  while(nCnt > (uint16)0x0000)
  {
    nCnt--;
    ((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))pDest)[nCnt] = pSrc[nCnt];  /* PRQA S 0505 */ /* MD_CANTP_MISRA_0505 */
  } 
} /* PRQA S 2006 */ /* MD_MSR_14.7 */
/* vCanTp_MemCpy */

/**************************************************************************************************
   Function name    : vCanTp_MemSet
   ------------------------------------------------------------------------------------------------
   Description      : Fill N-bytes with a given value.
   ------------------------------------------------------------------------------------------------
   Called by        : -
   ------------------------------------------------------------------------------------------------
   Parameter        : uint8* pDest    <=> destination ptr.
                      uint8  val      <=> fill value
                      uint16 nCnt     <=> no of bytes to copy
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(void, CANTP_CODE) vCanTp_MemSet(P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest, 
                                            uint8  val, 
                                            uint16 nCnt)
{
  vCanTp_DetAssertVReturn(pDest, vCanTp_MemSet_SId, CANTP_E_NULL_PTR)
 
  while(nCnt > (uint16)0x0000)
  {
    nCnt--;
    pDest[nCnt] = (uint8)val;  /* PRQA S 0505 */ /* MD_CANTP_MISRA_0505 */
  } 
} /* PRQA S 2006 */ /* MD_MSR_14.7 */
/* vCanTp_MemSet */


#if ( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
/**************************************************************************************************
   Function name    : vCanTp_RxGetResource
   ------------------------------------------------------------------------------------------------
   Description      : Allocates - if available - a resource for handling one SDU-Id
   ------------------------------------------------------------------------------------------------
   Called by        : -
   ------------------------------------------------------------------------------------------------
   Parameter        : - 
   ------------------------------------------------------------------------------------------------
   Returncode       : handle no. or CANTP_INVALID_HDL
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(PduIdType, CANTP_CODE) vCanTp_RxGetResource(CANTP_HDL_PVAL_ONLY)
{
  PduIdType cnt;
  PduIdType ret;

  ret = CANTP_INVALID_HDL;
  cnt = vCanTp_NumRxChannels;
  while( (cnt != (PduIdType)0) && (vCanTp_NumRxChannelsAvail != (PduIdType)0) )
  {
    cnt--;
    if(vCanTp_RxState[cnt].channel == CANTP_INVALID_HDL)
    { /* found free resource */
      vCanTp_NumRxChannelsAvail--;
      vCanTp_rxHdlMap[tpHdl] = cnt; 
      ret = cnt;
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
  } 
  return(ret);
} /* vCanTp_RxGetResource */

/**************************************************************************************************
   Function name    : vCanTp_TxGetResource
   ------------------------------------------------------------------------------------------------
   Description      : Allocates - if available - a resource for handling one SDU-Id
   ------------------------------------------------------------------------------------------------
   Called by        : -
   ------------------------------------------------------------------------------------------------
   Parameter        : - 
   ------------------------------------------------------------------------------------------------
   Returncode       : handle no. or CANTP_INVALID_HDL
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
STATIC FUNC(PduIdType, CANTP_CODE) vCanTp_TxGetResource(CANTP_HDL_PVAL_ONLY)
{
  PduIdType cnt;
  PduIdType ret;

  ret = CANTP_INVALID_HDL;
  cnt = vCanTp_NumTxChannels;
  while( (cnt != (PduIdType)0) && (vCanTp_NumTxChannelsAvail != (PduIdType)0) )
  {
    cnt--;
    if(vCanTp_TxState[cnt].channel == CANTP_INVALID_HDL)
    { /* found free resource */
      vCanTp_NumTxChannelsAvail--;
      vCanTp_txHdlMap[tpHdl] = cnt; 
      ret = cnt;
      break;  /* PRQA S 3333 */ /* MD_CANTP_MISRA_3333 */
    }
  } 
  return(ret);
} /* vCanTp_TxGetResource */

#endif


#if(CANTP_VERSION_INFO_API == STD_ON)
/**************************************************************************************************
   Function name    : CanTp_GetVersionInfo
   ------------------------------------------------------------------------------------------------
   Description      : AUTOSAR compliant API to retrieve its version from the CanTp component
   ------------------------------------------------------------------------------------------------
   Called by        : Any non-CanTp software-unit 
   ------------------------------------------------------------------------------------------------
   Parameter        : Std_VersionInfoType *pVersionInfo: Ptr to struct to the store version info in
   ------------------------------------------------------------------------------------------------
   Returncode       : None
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTP_APPL_DATA) pVersionInfo)
{
  vCanTp_DetAssertVReturn((pVersionInfo != (Std_VersionInfoType*)0), CanTp_GetVersionInfo_SId, CANTP_E_PARAM_ADDRESS)
  /* Note that CanTp_GetVersionInfo can be called before initialization of the CanTp module (see CANTP031)  */
    /* PRQA S 0505 6 */ /* MD_CANTP_MISRA_0505 */
  pVersionInfo->vendorID         = CANTP_VENDOR_ID;
  pVersionInfo->moduleID         = CANTP_MODULE_ID;
# if defined( CANTP_AUTOSARVERSION3 )
  pVersionInfo->instanceID       = 0;   /* obsolete since AR4 - see General Requirements on Basic Software Modules V3.0.0, R4.0Rev1 */
# endif
  pVersionInfo->sw_major_version = CANTP_SW_MAJOR_VERSION;
  pVersionInfo->sw_minor_version = CANTP_SW_MINOR_VERSION;
  pVersionInfo->sw_patch_version = CANTP_SW_PATCH_VERSION;
} /* PRQA S 2006 */ /* MD_MSR_14.7 */
/* CanTp_GetVersionInfo */
#endif

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"  /* MISRA RULE 87 VIOLATION: Only preprocessor statements and comments before '#include'. */



/* module specific MISRA deviations:
  MD_CANTP_MISRA_310:
    Reason:     RULE 11.4: The pointer casting is required to perform a simple memory operation (memcopy, memset, ...).
                           The implementation is hardware dependent and the functionality 
                           is verified at integration time with the customer hardware.
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_0342:
    Reason:     Rule 19.13: the ISO glue operator '##' is used to reduce code complexity and to improve readability
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_0488:
    Reason:     RULE 17.4: The pointer arithmetic is required to perform signal to network translation and the implementation is hardware dependent.
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_0489:
    Reason:     RULE 17.4: The functionality is verified at integration time with the customer hardware.
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_0505:
    Reason:     Rule 1.2: Pointer check is done by DET macro that may be inactive in some configurations
    Risk:       invalid pointer access may not be detected if DET is disabled
    Prevention: enable DET

  MD_CANTP_MISRA_0715:
    Reason:     Portability: Higher complexity is accepted to reach a reduced resource consumption and a higher performance.
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_0770:
    Reason:     RULE 14.5: Continue statement in control flow for a better readability and less resource consumption.
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_0832:
    Reason:     Macro substitution in #include is used as file name must be configurable
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_0850:
    Reason:     Rule 19.8: with single channel optimization, the macro parameter may be optimized away
    Risk:       undefined behavior for ISO C90 compilers when macro parameter is omitted
    Prevention: do not use single channel optimization with ISO C90 compilers

  MD_CANTP_MISRA_3112:
    Reason:     Rule 14.2: Statements which could be removed are kept intentionally to avoid compiler warnings.
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_3201:
    Reason:     Rule 14.1: statement not reachable as a conditional statement is always true or false (see also QAC 3355 / QAC 3356).
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_3333:
    Reason:     Rule 14.6: Break statement in control flow not belonging to the switch-case for a better readability and less resource consumption.
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_3355:
    Reason:     Rule 13.7: result of operation is always true when parts of the code are inactive in a certain configuration for optimization reasons.
    Risk:       dead code
    Prevention: verify by inspection that there is a configuration where the state is not always true

  MD_CANTP_MISRA_3356:
    Reason:     Rule 13.7: result of operation is always false when parts of the code are inactive in a certain configuration for optimization reasons.
    Risk:       dead code
    Prevention: verify by inspection that there is a configuration where the state is not always false

  MD_CANTP_MISRA_3358:
    Reason:     Rule 13.7: result of operation is always true (see also QAC 3355).
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_3359:
    Reason:     Rule 13.7: result of operation is always false (see also QAC 3356).
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_3410:
    Reason:     Rule 19.10: When embracing the macro parameters completely the QAC fails with a hard parser error.
    Risk:       unexpected evaluation order if parameter is an expression
    Prevention: only pass simple variables as parameters

  MD_CANTP_MISRA_3460:
    Reason:     Rule 19.4: macros with type identifier is need for single channel optimization.
    Risk:       none
    Prevention: N/A

  MD_CANTP_MISRA_3689:
    Reason:     Rule 21.1: array index out of bounds is not possible because of previous checks in the code that are not recognized by QAC
    Risk:       none
    Prevention: N/A


  MD_CANTP_SBSW_CHECK:
    Reason:     silent BSW safety check will have no effect in some configurations
    Risk:       unnecessary increase of code size
    Prevention: N/A

********************************** */

