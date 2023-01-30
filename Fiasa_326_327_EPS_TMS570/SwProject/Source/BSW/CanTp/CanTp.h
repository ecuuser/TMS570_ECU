/**************************************************************************************************
   Project Name: AUTOSAR_GbR CAN-TP
      File Name: CanTp.h

    Description: Main header file of the AUTOSAR CAN Transport Protocol, according to:
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
   2007-03-02   1.02.00  Her     ESCAN00019812: no changes
   2007-05-17   1.03.00  Her     ESCAN00021101: AUTOSAR Rel. 2.1
   2007-09-12   1.04.00  Her     ESCAN00022298: no changes
                         Her     ESCAN00022367: no changes
                         Her     ESCAN00022368: no changes
   2007-11-19   1.05.00  Her     ESCAN00023272: no changes
   2007-12-07   1.06.00  Her     ESCAN00023559: CanTp_Transmit: incorrect function parameter
   2008-01-16   1.07.00  Her     ESCAN00024058: no changes
                         Her     ESCAN00024152: ASR R. 3.0 new requirements
   2008-02-14   1.07.01  Her     ESCAN00024691: Rx buffer provision fails with blocksize zero
   2008-03-28   1.07.02  Her     ESCAN00025806: no changes
   2008-04-08   1.08.00  Her     ESCAN00025872: Correct setting of DEM errors
                         Her     ESCAN00025890: no changes
                         Her     ESCAN00026036: no changes
   2008-04-22   1.09.00  Her     ESCAN00026172: Introduction of the Library Version Check
                         Her     ESCAN00026250: Rename files and #include statements according coding styles
                         Her     ESCAN00026671: Extension for MSR3.0 generator version checks
                         Her     ESCAN00027017: Use dynamic channel allocation to reduce resource consumption
   2008-06-13   1.09.01  Her     ESCAN00027556: no changes
   2008-06-19   1.09.02  Her     ESCAN00027716: no changes
   2008-06-20   1.09.03  Her     ESCAN00027749: no changes
   2008-06-24   1.09.04  Her     ESCAN00027838: Adapt CanTp configuration table start address for post build process
   2008-07-02   1.09.05  Her     ESCAN00028008: no changes
   2008-07-11   1.09.06  Her     ESCAN00028326: no changes
   2008-07-31   1.10.00  Her     ESCAN00028721: Length check for Flow Control frames corrected
                         Her     ESCAN00028856: Reduce resource consumption: addressing type, buffer provision, single connection
                         Her     ESCAN00029776: Conditioning of dummy statements
   2008-09-23   1.10.01  Her     ESCAN00029781: Pre-Compile and Link-Time CRC Check
                         Her     ESCAN00030174: no changes
                         Her     ESCAN00030387: no changes
   2008-11-11   1.10.02  Her     ESCAN00031233: Reduce resource consumption (add functional reception to single connection path)
                         Her     ESCAN00031610: no changes
                         Her     ESCAN00031715: Burst mode extension (support high-speed transmission and reception)
                         Her     ESCAN00032191: Assertion fails erroneously (cleanup compiler warnings)
   2009-01-14   1.10.03  Her     ESCAN00032339: no changes
   2009-01-16   1.10.04  Her     ESCAN00032433: Illegal memory access via NULL pointer
   2009-01-20   1.10.05  Her     ESCAN00032453: no changes
                         Her     ESCAN00032472: no changes
                         Her     ESCAN00032522: Split the CanTp_MainFunction into Rx and Tx part
                         Her     ESCAN00032539: no changes
                         Her     ESCAN00033192: no changes
   2009-01-25   1.11.00  Her     ESCAN00033429: Wait Frames: CanTp_WFTmax data type changed (uint8 to uint16)
                         Her     ESCAN00032786: Indications to the application must be aware of the application status
                         Her     ESCAN00033439: Remapping of NSDU-IDs to user configured numbers
                         Her     ESCAN00033512: Support dynamic Flow Control N-PDU content
                         Her     ESCAN00033922: Undefined preprocessor identifier
   2009-07-01   1.12.00  Her     ESCAN00033693: Add support for multiple configuration
                         Her     ESCAN00033785: Optimized TP Routing (ASR4.0)
                         Her     ESCAN00034541: Using Rx instead of Tx channel count
                         Her     ESCAN00034627: CanTp_Transmit wrapper function for remapped NSDU-ID handling
                         Her     ESCAN00034663: Compiler error for single connection configuration
                         Her     ESCAN00034706: no changes
                         Her     ESCAN00035809: no changes
                         Her     ESCAN00036040: no changes
                         Her     ESCAN00036117: add preprocessor checks for library builds
   2009-07-20   1.13.00  Her     ESCAN00036540: Transmission stops after unexpected Flow Control reception
                         Her     ESCAN00035216: Add Mixed-11 Addressing for CAN/LIN-Gateway Use Case
                         Her     ESCAN00036456: from untested beta to tested release version
   2009-08-11   1.14.00  Her     ESCAN00036875: Missing PduR_CanTpTxConfirmation call in case of Tx buffer provision timeout
   2009-08-25   1.14.01  Her     ESCAN00037344: Missing preprocessor switch leads to a compile error
   2009-08-26   1.14.02  Her     ESCAN00037347: no changes
                         Her     ESCAN00037393: CanTp receives wrong Sdu (phys/func sorting goes wrong)
   2009-08-28   1.14.03  Her     ESCAN00037422: N_Br has not necessarily to be used in the code
                         Her     ESCAN00037425: Move default AUTOSAR macros from source to include file
                         Her     ESCAN00038075: no changes
   2009-11-03   1.14.04  Her     ESCAN00037284: Use 2 ProvideRxBufferCalls for the FF
                         Her     ESCAN00038848: Make CanTp228 requirement optional
                         Her     ESCAN00039090: no changes
                         Her     ESCAN00039468: no changes
                         Her     ESCAN00039477: no changes
                         Her     ESCAN00039533: no changes
                         Her     ESCAN00039572: no changes
   2009-12-10   1.14.05  Her     ESCAN00039586: Dynamic BS calculation optimization
                         Her     ESCAN00039216: no changes
                         Her     ESCAN00040003: MISRA conformance improved 
                         Her     ESCAN00040045: no changes
                         Her     ESCAN00040084: Compiler warning: redundant redeclaration of 'vCanTp_AdminData'
   2010-02-18   1.15.00  Her     ESCAN00040792: no changes
                         Her     ESCAN00040300: Switch CanTp Parameters BS, Stmin at runtime via CanTp_ChangeParameterRequest API
                         Her     ESCAN00041040: no changes
                         Her     ESCAN00041114: no changes
                         Her     ESCAN00041628: Reset the transmit state to idle before calling the confirmation callout function of the PduR
                         Her     ESCAN00041870: no changes
                         Her     ESCAN00041916: no changes
                         Her     ESCAN00042052: For functional diagnostic requests the wrong Id is handed to the PduR
                         Her     ESCAN00042563: no changes
                         Her     ESCAN00042575: Strictly keep the reception sequence independent of the buffer provision return value
                         Her     ESCAN00042652: Adapt type of invalid handle definition to the PduIdType definition
                         Her     ESCAN00042958: no changes
                         Her     ESCAN00042945: no changes
                         Her     ESCAN00042882: no changes
                         Her     ESCAN00042885: no changes
                         Her     ESCAN00043033: no changes
   2010-06-17   1.15.01  Mhe     ESCAN00043464: no changes
   2010-06-28   1.15.02  Tne     ESCAN00043558: no changes
   2010-07-15   1.16.00  Her     ESCAN00040590: Optimize constant Sdu settings in precompile variant
                         Her     ESCAN00043991: Support TP Receive Cancellation
                         Her     ESCAN00044193: no changes
                         Her     ESCAN00044239: no changes
                         Her     ESCAN00044374: no changes
                         Her     ESCAN00044670: no changes
                         Her     ESCAN00044857: no changes
   2010-09-23   1.16.01  Her     ESCAN00045555: no changes
                         Her     ESCAN00045557: no changes
   2010-09-28   1.16.02  Her     ESCAN00045609: Compile error "'CANTP_DL' : is not a member of 'sTxNsduCfg'; undeclared identifier"
                         Her     ESCAN00045702: no changes
                         Her     ESCAN00045739: no changes
   2010-10-08   1.16.03  Her     ESCAN00045856: no changes
   2010-10-13   1.17.00  Her     ESCAN00045283: Replace use of V_USE_DUMMY_STATEMENT
                         Her     ESCAN00045310: Change the transmit cancellation availability from general to connection specific
                         Her     ESCAN00045765: Change selected production errors to development errors
                         Her     ESCAN00046076: no changes
                         Her     ESCAN00046284: Adapt AUTOSAR version check
                         Her     ESCAN00047069: no changes
                         Her     ESCAN00047079: no changes
                         Her     ESCAN00047291: no changes
                         Her     ESCAN00047353: Adapt CanTp_MainFunction for usage with Identity Manager Configuration
                         Her     ESCAN00047528: no changes
                         Her     ESCAN00047788: no changes
                         Her     ESCAN00047978: no changes
                         Her     ESCAN00048115: no changes
   2011-02-22   1.18.00  Her     ESCAN00048099: no changes
                         Her     ESCAN00048895: no changes
                         Her     ESCAN00049011: no changes
                         Her     ESCAN00049026: TP shall judge a received FC frame to be invalid if the STmin is a reserved value
                         Her     ESCAN00049050: AUTOSAR 4 compatibility
                         Her     ESCAN00049130: Add DCM call-out for every Mixed11-Addressing FF or SF reception
                         Her     ESCAN00049199: no changes
   2011-04-06   1.18.01  Her     ESCAN00049698: Wrong Define use order of Define CANTP_TX_FC_FROM_ISR
                         Her     ESCAN00049839: Compilation error due to undefined DEM symbol CANTP_E_COM
   2011-04-07   1.18.02  Her     ESCAN00049947: Compilation error due to undeclared identifier CanTp_E_Rx_Com and CanTp_E_Tx_Com
   2011-04-12   1.18.03  Her     ESCAN00050027: no changes
                         Her     ESCAN00050043: no changes
   2011-04-20   1.19.00  Her     ESCAN00048513: Transmission confirmation cannot be resolved
                         Her     ESCAN00049432: no changes
                         Her     ESCAN00049945: Support Half Duplex communication
                         Her     ESCAN00050534: no changes
                         Her     ESCAN00050563: no changes
                         Her     ESCAN00063835: no changes
                         Her     ESCAN00050773: no changes
                         Her     ESCAN00052244: no changes
   2011-08-15            Dth     ESCAN00052682: CANTP_##ECK_HALF_DUPLEX renamed to CANTP_##__ENABLE_HALF_DUPLEX_CHECK
                         Dth     ESCAN00052760: no changes
   2011-11-17   1.20.00  Dth     ESCAN00053503: critical section handling only via SchM
                         Dth     ESCAN00051742: no changes
                         Dth     ESCAN00054836: no changes
                         Dth     ESCAN00052691: no changes
                         Dth     ESCAN00053503: no changes
                         Dth     ESCAN00054280: no changes
                         Dth     ESCAN00054364: no changes
                         Dth     ESCAN00054664: no changes
                         Dth     ESCAN00054300: no changes
                         Dth     ESCAN00054324: no changes
                         Dth     ESCAN00054420: no changes
                         Dth     ESCAN00054523: simplified use of configuration access macros
                         Dth     ESCAN00054525: no changes
                         Dth     ESCAN00054819: no changes
                         Dth     ESCAN00054656: no changes
                         Dth     ESCAN00054700: no changes
                         Dth     ESCAN00054685: no changes
                         Dth     ESCAN00055330: no changes
   2012-01-05   1.20.01  Dth     ESCAN00055795: no chnages
                         Dth     ESCAN00055799: no changes
                         Dth     ESCAN00055814: no changes
                         Dth     ESCAN00055822: no changes
   2012-01-23   1.20.02  Dth     ESCAN00056210: Compile error: 'CANTP_NBR' : is not a member of 'sRxNsduCfg'
   2012-02-22   1.20.03  Dth     ESCAN00056988: no changes
                         Dth     ESCAN00056192: AR3.2 API function remapping
   2012-02-23   1.21.00  Dth     ESCAN00056792: no changes
                         Dth     ESCAN00056193: missing 'extern' keyword in function declaration
                         Dth     ESCAN00056951: no changes
   2012-03-30   1.21.01  Dth     ESCAN00056990: CanTp internal constants should be defined in CanTp.c
                         Dth     ESCAN00055796: no changes
                         Dth     ESCAN00057558: no changes
   2012-06-15   1.21.02  Dth     ESCAN00059163: no changes
                         Dth     ESCAN00059137: no changes
                         Dth     ESCAN00056982: no changes
                         Dth     ESCAN00058822: after FlowControl, no STmin should be used
   2012-08-28   1.21.03  Dth     ESCAN00060308: no changes
                         Dth     ESCAN00060406: no changes
                         Dth     ESCAN00060079: Support SF individual asynchron mode
   2012-10-04   1.22.00  Dth     ESCAN00060581: no changes
                         Dth     ESCAN00061034: no changes
                         Dth     ESCAN00063804: no changes
                         Dth     ESCAN00063603: optional deactivation of error reporting if idle connection is canceled
   2013-02-18   1.23.00  Dth     ESCAN00064038: suppress FC.OVFL for buffer status BUFREQ_E_NOT_OK
                         Dth     ESCAN00064983: Block Size 0 conflicts with segmented buffers
   2013-04-08   1.24.00  Dth     ESCAN00065895: no changes
                         Dth     ESCAN00066463: Implementation of Low Level Routing extension
                         Dth     ESCAN00066858: switch CANTP_BS_ZERO_MULTI_BUFFER removed
   2013-07-11   1.25.00  Dth     ESCAN00067223: no changes
                         Dth     ESCAN00067701: no changes
                         Dth     ESCAN00068529: no changes
                         Dth     ESCAN00068731: no changes
                         Dth     ESCAN00067672: Notification to DEM in case of a buffer overflow and fast routing use case
**************************************************************************************************/
#if !defined( CANTP_H )
#define CANTP_H

/* PRQA S 3453 EOF */ /* MD_MSR_19.7 */

/*******************************************************************************
* CanTp Component Version
*******************************************************************************/
/* AUTOSAR CAN Transport Protocol version */
/* ##V_CFG_MANAGEMENT ##CQProject : Tp_AsrTpCan CQComponent : Implementation */
#define TP_ASRTPCAN_VERSION          (0x0125u)  /* BCD coded version number          */
#define TP_ASRTPCAN_RELEASE_VERSION  (0x00u)    /* BCD coded release version number  */
/* ******* Note: Keep this version numbers consistent with the BSWMD file *********  */

/* vendor and module identification */
#define CANTP_VENDOR_ID         0x001Eu
#define CANTP_MODULE_ID         0x0023u          /* see CanTp:115 */



/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "CanTp_Types.h"
#include "ComStack_Types.h"
#include "CanTp_Cbk.h"

#if !defined( CANTP_DCM_REQUEST_DETECT )
# define  CANTP_DCM_REQUEST_DETECT             STD_OFF
# define  CANTP_DISABLE_DCM_REQUEST_DETECT
#else
# if( CANTP_DCM_REQUEST_DETECT == STD_ON )
#  define CANTP_ENABLE_DCM_REQUEST_DETECT
# else
#  define CANTP_DISABLE_DCM_REQUEST_DETECT
# endif
#endif
#if defined( CANTP_ENABLE_DCM_REQUEST_DETECT )
# include "Dcm_Cbk.h"
#endif

#if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
# include "v_ver.h"
#endif

#if( CANTP_DEV_ERROR_DETECT == STD_ON )
# include "Det.h"
#endif

#if( CANTP_PROD_ERROR_DETECT == STD_ON )
# include "Dem.h"
#endif

#include "CanTp_PBcfg.h"


/**************************************************************************************************
* Global defines
**************************************************************************************************/
/* AUTOSAR Software Specification Version Information */
#if !( (defined(CANTP_AUTOSARVERSION4)) || (defined(CANTP_AUTOSARVERSION3)) )
# define CANTP_AUTOSARVERSION3
#endif
#if defined ( CANTP_AUTOSARVERSION4 )
/* Document Version   3.0.0
   Part of Release    4.0
   Revision           0001, dated 2009-12-07 **********/
# define CANTP_AR_RELEASE_MAJOR_VERSION         (0x04u)
# define CANTP_AR_RELEASE_MINOR_VERSION         (0x00u)
# define CANTP_AR_RELEASE_REVISION_VERSION      (0x01u)
#else
/* Document Version   2.4.0
   Part of Release    3.2
   Revision           0001, dated 2011-04-27 **********/
# define CANTP_AR_MAJOR_VERSION  (0x02u)
# define CANTP_AR_MINOR_VERSION  (0x04u)
# define CANTP_AR_PATCH_VERSION  (0x00u)
#endif

/* Component Version Information */
/* PRQA S 3412 3   */ /* RULE 19.4: Macro defines an unrecognized code-fragment but only for QAC. */
#define CANTP_SW_MAJOR_VERSION (uint8)(TP_ASRTPCAN_VERSION >> 8)       /* Major version number */
#define CANTP_SW_MINOR_VERSION (uint8)(TP_ASRTPCAN_VERSION & 0x00FFu)  /* Minor version number */
#define CANTP_SW_PATCH_VERSION (uint8)(TP_ASRTPCAN_RELEASE_VERSION)    /* Patch level version number */

#if !defined( CANTP_AUTOSARVERSION3 )
# if !defined STATIC
#  define STATIC static
# endif
#endif

#if !defined( CANTP_HAVE_INIT_CFG_PTR )
# if defined ( CANTP_AUTOSARVERSION4 )
#  define CANTP_HAVE_INIT_CFG_PTR             STD_ON
# else
#  define CANTP_HAVE_INIT_CFG_PTR             STD_OFF
# endif
#endif

/* Vector extension to AR4 (see ISO-TP) */
#if !defined( CANTP_USE_ONLY_FIRST_FC )
# define CANTP_USE_ONLY_FIRST_FC              STD_OFF
#endif

/* CanTp234: CanTp_RxIndication shall be implemented using a pre-compile macro   */
#if !defined( CANTP_RX_INDICATION_API ) 
# define  CANTP_RX_INDICATION_API             STD_ON
#endif
/* CanTp237: CanTp_TxConfirmation shall be implemented using a pre-compile macro */
#if !defined( CANTP_TX_CONFIRMATION_API ) 
# define  CANTP_TX_CONFIRMATION_API           STD_ON
#endif
/* Priority inversion */
#if !defined( CANTP_HIGH_RX_LOW_TX_PRIO ) 
# define  CANTP_HIGH_RX_LOW_TX_PRIO           STD_ON
#endif

/* Additional indication callbacks */ 
#if (!defined(CANTP_RX_SF_INDICATION))
# define CANTP_RX_SF_INDICATION               STD_OFF
#endif
#if (!defined(CANTP_RX_FF_INDICATION))
# define CANTP_RX_FF_INDICATION               STD_OFF
#endif
#if (!defined(CANTP_RX_CF_INDICATION))
# define CANTP_RX_CF_INDICATION               STD_OFF
#endif
#if (!defined(CANTP_TX_FRAME_CONFIRMATION))
# define CANTP_TX_FRAME_CONFIRMATION          STD_OFF
#endif

/* Separated Rx/Tx MainFunction API */
#if (!defined(CANTP_RXTX_MAINFUNCTION_API))
# define CANTP_RXTX_MAINFUNCTION_API          STD_OFF
#endif
#if (!defined(CANTP_IDENTITY_MANAGER_CONFIG))
# define CANTP_IDENTITY_MANAGER_CONFIG        STD_OFF
#endif

/* *** Optimization purposes *** */ 
/* Addressing types */ 
#if (!defined(CANTP_STANDARD_ADDRESSING))
# define CANTP_STANDARD_ADDRESSING            STD_ON
#endif
#if (!defined(CANTP_EXTENDED_ADDRESSING))
# define CANTP_EXTENDED_ADDRESSING            STD_ON
#endif
#if (!defined(CANTP_MIXED11_ADDRESSING))
# define CANTP_MIXED11_ADDRESSING             STD_OFF
#endif
/* Buffer provision */
#if (!defined(CANTP_RX_FULL_BUFFER_PROVISION))
# define CANTP_RX_FULL_BUFFER_PROVISION       STD_OFF
#endif
#if (!defined(CANTP_TX_FULL_BUFFER_PROVISION))
# define CANTP_TX_FULL_BUFFER_PROVISION       STD_OFF
#endif
/* Single connection version */
#if (!defined(CANTP_SINGLE_CONN_OPTIMIZED))
# define CANTP_SINGLE_CONN_OPTIMIZED          STD_OFF
#endif
#if (!defined(CANTP_SINGLE_CONN_NOPB_OPTIMIZED))
# define CANTP_SINGLE_CONN_NOPB_OPTIMIZED     STD_OFF
#endif
#if (!defined(CANTP_NUM_RXSDUS))
# define CANTP_NUM_RXSDUS                     0
#endif
#if( ((CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON) && (CANTP_NUM_RXSDUS      <= 1)) || \
     ((CANTP_SINGLE_CONN_OPTIMIZED      == STD_ON) && (CANTP_NUM_RX_CHANNELS <= 1)) )
# define CANTP_ENABLE_SINGLE_CONN
#else
# define CANTP_DISABLE_SINGLE_CONN
#endif

/* Dyn. channel assignment   */
#if (!defined(CANTP_RAM_OPTIMIZED))
# define CANTP_RAM_OPTIMIZED                  STD_OFF
#endif
#define CANTP_DYN_CHANNEL_ASSIGNMENT          CANTP_RAM_OPTIMIZED
/* NSDU-ID remapping */
#if (!defined(CANTP_ENABLE_RX_NSDU_REMAPPING))
# define CANTP_ENABLE_RX_NSDU_REMAPPING        STD_OFF
#endif
#if (!defined(CANTP_ENABLE_TX_NSDU_REMAPPING))
# define CANTP_ENABLE_TX_NSDU_REMAPPING        STD_OFF
#endif
#if (!defined(CANTP_ENABLE_WRAP_TRANSMIT))
# define CANTP_ENABLE_WRAP_TRANSMIT            STD_OFF
#endif
#if (!defined(CANTP_ENABLE_WRAP_CANCEL_TRANSMIT))
# define CANTP_ENABLE_WRAP_CANCEL_TRANSMIT     STD_OFF
#endif
/* Dynamic setting of FC values BS, STmin */
#if (!defined(CANTP_ENABLE_EXT_API_BS))
# define CANTP_ENABLE_EXT_API_BS               STD_OFF
#endif
#if (!defined(CANTP_ENABLE_EXT_API_STMIN))
# define CANTP_ENABLE_EXT_API_STMIN            STD_OFF
#endif
#if (!defined(CANTP_ENABLE_CHANGE_PARAM))
# define CANTP_ENABLE_CHANGE_PARAM             STD_OFF
#endif
/* Intentionally not commented out(2010-04-14): It shall not be possible to use the AR4.x API as well as the customer specific API */
#if( ((CANTP_ENABLE_EXT_API_STMIN == STD_ON) || (CANTP_ENABLE_EXT_API_BS == STD_ON)) && (CANTP_ENABLE_CHANGE_PARAM == STD_ON) )
# error "Select either AR 4.x ChangeParameterRequest API or customer specific Extended API STmin/BS !"
#endif 

/* with this version the tx confirmation was moved behind the state initialization (see ESCAN00041628) */
#define CANTP_ENABLE_TX_CONF_FINAL             STD_ON

/* Cancel transmission */
#if (!defined(CANTP_TC))
# define CANTP_TC                              STD_OFF
#endif
#if (!defined(CANTP_TC_NOTIFY_ALWAYS))
# define CANTP_TC_NOTIFY_ALWAYS                STD_OFF
#endif
/* Cancel reception */
#if (!defined(CANTP_RC))
# define CANTP_RC                              STD_OFF
#endif
#if (!defined(CANTP_RC_NOTIFY_ALWAYS))
# define CANTP_RC_NOTIFY_ALWAYS                STD_OFF
#endif
/* PduR buffer provision optimization (ASR 4.0) */
#if (!defined(CANTP_ENABLE_PDUR_SOR))
# define CANTP_ENABLE_PDUR_SOR                 STD_OFF
#endif
#if(CANTP_ENABLE_PDUR_SOR == STD_ON)
# define CANTP_ENABLE_PDUR_API40
#else
# define CANTP_DISABLE_PDUR_API40 
#endif
#if !defined( CANTP_SUPPRESS_PREPASS_INDICATION )
# define CANTP_SUPPRESS_PREPASS_INDICATION     STD_ON
#endif
#if !defined( CANTP_FF_PROVIDE_2_RXBUFFER_CALLS )
# define CANTP_FF_PROVIDE_2_RXBUFFER_CALLS     STD_OFF
#endif
#if !defined( CANTP_CALC_BS_OPTIMIZED )
# define CANTP_CALC_BS_OPTIMIZED               STD_OFF
#endif
#if !defined( CANTP_STRICT_RX_CALL_SEQ )
# define CANTP_STRICT_RX_CALL_SEQ              STD_OFF
#endif
#if !defined( CANTP_IGNORE_FC_WITH_RES_STMIN )
# define CANTP_IGNORE_FC_WITH_RES_STMIN        STD_OFF
#endif
#if !defined( CANTP_IGNORE_CF_WITH_WRONG_SN )
# define CANTP_IGNORE_CF_WITH_WRONG_SN         STD_OFF
#endif

#if !defined( CANTP_USE_STMIN_AFTER_FC )
# define CANTP_USE_STMIN_AFTER_FC               STD_OFF
#endif

#if !defined(CANTP_SUPPRESS_CANCEL_ERROR_WHEN_IDLE)
# define CANTP_SUPPRESS_CANCEL_ERROR_WHEN_IDLE  STD_OFF
#endif

#if !defined(CANTP_SUPPRESS_INVALID_BUFFER_FC_OVFL)
# define CANTP_SUPPRESS_INVALID_BUFFER_FC_OVFL  STD_OFF
#endif

#if !defined (CANTP_ENABLE_LLR_CALLOUTS)
# define CANTP_ENABLE_LLR_CALLOUTS              STD_OFF
#endif

#if !defined (CANTP_AMD_RUNTIME_MEASUREMENT)
# define CANTP_AMD_RUNTIME_MEASUREMENT          STD_OFF
#endif

/* Dem2Det, see CompanionGuide_V007.pdf: The development error codes: "CANTP_E_OPER_NOT_SUPPORTED" is 0xA0, "CANTP_E_COMM" is 0xB0 */ 
#if !defined( CANTP_OPER_NOT_SUPPORTED_REPORT_DEM )
# define CANTP_OPER_NOT_SUPPORTED_REPORT_DEM    STD_ON
#endif
#if !defined( CANTP_E_COMM_REPORT_DEM )
# define CANTP_E_COMM_REPORT_DEM                STD_ON
#endif

#if !defined (CANTP_GW_ERRORS_REPORT_DEM)
# define CANTP_GW_ERRORS_REPORT_DEM             STD_OFF
#endif

/* ---- error code redefinition ---- */
#if( CANTP_OPER_NOT_SUPPORTED_REPORT_DEM == STD_ON )
/* DEM is available, CanTp uses const variables and the belonging defines have to be supported via Dem_Cfg.
   (If the DEM is not available then CANTP_OPER_NOT_SUPPORTED_REPORT_DEM is always STD_OFF) */
#else
#  define CanTp_E_Oper_Not_Supported            CANTP_E_OPER_NOT_SUPPORTED
#endif

#if (CANTP_E_COMM_REPORT_DEM == STD_ON)
/* DEM is available, CanTp uses const variables and the belonging defines have to be supported via Dem_Cfg.
   (If the DEM is not available then CANTP_E_COMM_REPORT_DEM is always STD_OFF) */
# if defined(CANTP_AUTOSARVERSION3)
#  define CanTp_E_Rx_Com CanTp_E_Com
#  define CanTp_E_Tx_Com CanTp_E_Com
# endif
#else
# if defined(CANTP_E_COM)
#  if !defined(CANTP_E_COMM)
#   define CANTP_E_COMM                       CANTP_E_COM   /* try to compensate AR3.1 incompatible naming */
#  endif
# endif
# if defined(CANTP_E_COMM)
#  if !defined(CANTP_E_COM)
#   define CANTP_E_COM                        CANTP_E_COMM  /* try to compensate AR3.1 incompatible naming */
#  endif
# endif
/* adapt CanTp names to generated DET defined errors */
# if defined( CANTP_AUTOSARVERSION3 )
#  define CanTp_E_Rx_Com                      CANTP_E_COM
#  define CanTp_E_Tx_Com                      CANTP_E_COM
# else
#  define CanTp_E_Rx_Com                      CANTP_E_RX_COM
#  define CanTp_E_Tx_Com                      CANTP_E_TX_COM
# endif
#endif



#if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
# if ( CANTP_NUM_RX_CHANNELS == 2 )
#  define TP_RX_HDL(hdl)                      (hdl)
# else
#  define TP_RX_HDL(hdl)                      (0)
# endif
# define TP_TX_HDL(hdl)                       (0)
#else
# if( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
#  define TP_RX_HDL(hdl)                      (vCanTp_rxHdlMap[(hdl)])
#  define TP_TX_HDL(hdl)                      (vCanTp_txHdlMap[(hdl)])
# else
#  define TP_RX_HDL(hdl)                      (hdl)
#  define TP_TX_HDL(hdl)                      (hdl)
# endif
#endif

#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# if( CANTP_NUM_RXSDUS >= 2 )
#  define CANTP_HDL_PTYPE_ONLY                                PduIdType
#  define CANTP_HDL_CPTYPE_ONLY                               PduIdType
#  define CANTP_HDL_PTYPE_FIRST                               PduIdType,
#  define CANTP_HDL_PVAL_ONLY                                 PduIdType tpHdl
#  define CANTP_HDL_CPVAL_ONLY                                PduIdType tpHdl
#  define CANTP_HDL_PVAL_FIRST                                PduIdType tpHdl,
#  define CANTP_HDL_CVAL_ONLY                                 tpHdl
#  define CANTP_HDL_CVAL_FIRST                                tpHdl,
# else
#  define CANTP_HDL_PTYPE_ONLY                                void        /* PRQA S 3460 */ /* MD_CANTP_MISRA_3460 */
#  define CANTP_HDL_CPTYPE_ONLY                               void        /* PRQA S 3460 */ /* MD_CANTP_MISRA_3460 */
#  define CANTP_HDL_PTYPE_FIRST
#  define CANTP_HDL_PVAL_ONLY                                 void        /* PRQA S 3460 */ /* MD_CANTP_MISRA_3460 */
#  define CANTP_HDL_CPVAL_ONLY                                void        /* PRQA S 3460 */ /* MD_CANTP_MISRA_3460 */
#  define CANTP_HDL_PVAL_FIRST
#  define CANTP_HDL_CVAL_ONLY
#  define CANTP_HDL_CVAL_FIRST
# endif
#else
# if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#  if( CANTP_NUM_RX_CHANNELS >= 2 )
#   define CANTP_HDL_PTYPE_ONLY                               PduIdType
#   define CANTP_HDL_CPTYPE_ONLY                              PduIdType
#   define CANTP_HDL_PTYPE_FIRST                              PduIdType,
#   define CANTP_HDL_PVAL_ONLY                                PduIdType tpHdl
#   define CANTP_HDL_CPVAL_ONLY                               PduIdType tpHdl
#   define CANTP_HDL_PVAL_FIRST                               PduIdType tpHdl,
#   define CANTP_HDL_CVAL_ONLY                                tpHdl
#   define CANTP_HDL_CVAL_FIRST                               tpHdl,
#  else
#   define CANTP_HDL_PTYPE_ONLY                               void        /* PRQA S 3460 */ /* MD_CANTP_MISRA_3460 */
#   define CANTP_HDL_CPTYPE_ONLY                              void        /* PRQA S 3460 */ /* MD_CANTP_MISRA_3460 */
#   define CANTP_HDL_PTYPE_FIRST
#   define CANTP_HDL_PVAL_ONLY                                void        /* PRQA S 3460 */ /* MD_CANTP_MISRA_3460 */
#   define CANTP_HDL_CPVAL_ONLY                               void        /* PRQA S 3460 */ /* MD_CANTP_MISRA_3460 */
#   define CANTP_HDL_PVAL_FIRST
#   define CANTP_HDL_CVAL_ONLY
#   define CANTP_HDL_CVAL_FIRST
#  endif
# else
#  define CANTP_HDL_PTYPE_ONLY                                PduIdType
#  define CANTP_HDL_CPTYPE_ONLY                               PduIdType
#  define CANTP_HDL_PTYPE_FIRST                               PduIdType tpHdl,
#  define CANTP_HDL_PVAL_ONLY                                 PduIdType tpHdl
#  define CANTP_HDL_CPVAL_ONLY                                PduIdType tpHdl
#  define CANTP_HDL_PVAL_FIRST                                PduIdType tpHdl,
#  define CANTP_HDL_CVAL_ONLY                                 tpHdl
#  define CANTP_HDL_CVAL_FIRST                                tpHdl,
# endif
#endif

#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# if( CANTP_NUM_RXSDUS == 2 )
#  define CANTP_TX_HDL_CVAL_ONLY                              0
#  define CANTP_TX_HDL_CVAL_FIRST                             0,
# else
#  define CANTP_TX_HDL_CVAL_ONLY
#  define CANTP_TX_HDL_CVAL_FIRST
# endif
#else
# if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#  if( CANTP_NUM_RX_CHANNELS == 2 )
#   define CANTP_TX_HDL_CVAL_ONLY                             0
#   define CANTP_TX_HDL_CVAL_FIRST                            0,
#  else
#   define CANTP_TX_HDL_CVAL_ONLY
#   define CANTP_TX_HDL_CVAL_FIRST
#  endif
# else
#   define CANTP_TX_HDL_CVAL_ONLY                            CANTP_HDL_CVAL_ONLY
#   define CANTP_TX_HDL_CVAL_FIRST                           CANTP_HDL_CVAL_FIRST
# endif
#endif

/* Access to Link-time data */
#define vCanTp_LData(DataItem) (vCanTp_AdminData.DataItem)  /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
/* Retrieve configuration:
   1. Either as ext. ptr. declared here (in a struct or as 'loose' variables) and hence have CanTp_Init(void); or
   2. In a struct given via CanTp_Init( CfgPtr); */

#if defined( CANTP_ENABLE_SINGLE_CONN )
# define CanTpGET_NumCanTpRxSduId       1
#else
# if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#  define CanTpGET_NumCanTpRxSduId      2
# else
#  if( CANTP_HAVE_INIT_CFG_PTR == STD_ON)
#   define CanTpGET_NumCanTpRxSduId     vCanTp_LData(CfgPtr)->NumCanTpRxSduId
#  else
#   define CanTpGET_NumCanTpRxSduId     vCanTp_Cfg.NumCanTpRxSduId
#  endif
# endif
#endif

#if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
# define CanTpGET_NumCanTpTxSduId       1
#else
# if( CANTP_HAVE_INIT_CFG_PTR == STD_ON)
#  define CanTpGET_NumCanTpTxSduId      vCanTp_LData(CfgPtr)->NumCanTpTxSduId
# else
#  define CanTpGET_NumCanTpTxSduId      vCanTp_Cfg.NumCanTpTxSduId
# endif
#endif

#if defined( CANTP_ENABLE_SINGLE_CONN )
# define TPHDL                          (0)
# define TPRXHDL                        (0)
# define TPTXHDL                        (0)
#else
# define TPHDL                          (tpHdl)
# define TPRXHDL                        (tpHdl)
# if(CANTP_SINGLE_CONN_OPTIMIZED == STD_ON)
#  define TPTXHDL                       (0)
# else
#  define TPTXHDL                       (tpHdl)
# endif
#endif

#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# if ( CANTP_NUM_RXSDUS == 2 )
#  define vCanTp_RxPBCfg(CfgItem, elm, pBItem, cItem)   ((elm==CANTP_RX__RXNSDU_ID)?(cItem):(cItem##_FUNC))  /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */  /* PRQA S 0342 */ /* MD_CANTP_MISRA_0342 */
#  define vCanTp_PBCfg(CfgItem, elm, pBItem, cItem)     (cItem)
# else
#  define vCanTp_RxPBCfg(CfgItem, elm, pBItem, cItem)   (cItem)
#  define vCanTp_PBCfg(CfgItem, elm, pBItem, cItem)     (cItem)
# endif
# define vCanTp_PBCfgPtr(CfgItem, elm)                  (CfgItem)
#else
# if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
#  define vCanTp_RxPBCfg(CfgItem, elm, pBItem, cItem)   (CfgItem[(elm)].pBItem)  /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#  define vCanTp_PBCfg(CfgItem, elm, pBItem, cItem)     (CfgItem[(elm)].pBItem)  /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#  define vCanTp_PBCfgPtr(CfgItem, elm)                 (CfgItem[(elm)])         /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#   if( CANTP_HAVE_INIT_CFG_PTR == STD_ON)
#    define vCanTp_PBCfgPtr_(CfgItem)                   (vCanTp_LData(CfgPtr)->CfgItem)  /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#   else
#    define vCanTp_PBCfgPtr_(CfgItem)                   (vCanTp_Cfg.CfgItem)             /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#   endif

# else
#  if( CANTP_HAVE_INIT_CFG_PTR == STD_ON)
#   define vCanTp_RxPBCfg(CfgItem, elm, pBItem, cItem)  ( vCanTp_LData(CfgPtr)->CfgItem[(elm)].pBItem )  /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#   define vCanTp_PBCfg(CfgItem, elm, pBItem, cItem)    ( vCanTp_LData(CfgPtr)->CfgItem[(elm)].pBItem )  /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#   define vCanTp_PBCfgPtr(CfgItem, elm)                ( vCanTp_LData(CfgPtr)->CfgItem[(elm)] )         /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#   define vCanTp_PBCfgPtr_(CfgItem)                    ( vCanTp_LData(CfgPtr)->CfgItem )                /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#  else
#   define vCanTp_RxPBCfg(CfgItem, elm, pBItem, cItem)  ( vCanTp_Cfg.CfgItem[(elm)].pBItem )  /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#   define vCanTp_PBCfg(CfgItem, elm, pBItem, cItem)    ( vCanTp_Cfg.CfgItem[(elm)].pBItem )  /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#   define vCanTp_PBCfgPtr(CfgItem, elm)                ( vCanTp_Cfg.CfgItem[(elm)] )         /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#   define vCanTp_PBCfgPtr_(CfgItem)                    ( vCanTp_Cfg.CfgItem )                /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
#  endif
# endif
#endif

#if !defined( CANTP_CONSTANT_RX__DL )
# define CANTP_CONSTANT_RX__DL                          STD_OFF
#endif
#if !defined( CANTP_CONSTANT_RX__DL )
# define CANTP_CONSTANT_RX__DL                          STD_OFF
#endif
#if !defined( CANTP_CONSTANT_RX__NBR )
# define CANTP_CONSTANT_RX__NBR                         STD_OFF
#endif
#if !defined( CANTP_CONSTANT_RX__NCR )
# define CANTP_CONSTANT_RX__NCR                         STD_OFF
#endif
#if !defined( CANTP_CONSTANT_RX__WFTMAX )
# define CANTP_CONSTANT_RX__WFTMAX                      STD_OFF
#endif
#if !defined( CANTP_CONSTANT_RX__PADDING_ACTIVATION )
# define CANTP_CONSTANT_RX__PADDING_ACTIVATION          STD_OFF
#endif
#if !defined( CANTP_CONSTANT_RX__TA_TYPE )
# define CANTP_CONSTANT_RX__TA_TYPE                     STD_OFF
#endif
#if !defined( CANTP_CONSTANT_RX__MAX_PAYLOAD_LENGTH )
# define CANTP_CONSTANT_RX__MAX_PAYLOAD_LENGTH          STD_OFF
#endif
#if !defined( CANTP_CONSTANT_RX__BS )
# define CANTP_CONSTANT_RX__BS                          STD_OFF
#endif
#if !defined( CANTP_CONSTANT_RX__STMIN )
# define CANTP_CONSTANT_RX__STMIN                       STD_OFF
#endif

#if !defined( CANTP_CONSTANT_TX__DL )
# define CANTP_CONSTANT_TX__DL                          STD_OFF
#endif
#if !defined( CANTP_CONSTANT_TX__NAS )
# define CANTP_CONSTANT_TX__NAS                         STD_OFF
#endif
#if !defined( CANTP_CONSTANT_TX__NBS )
# define CANTP_CONSTANT_TX__NBS                         STD_OFF
#endif
#if !defined( CANTP_CONSTANT_TX__NCS )
# define CANTP_CONSTANT_TX__NCS                         STD_OFF
#endif
#if !defined( CANTP_CONSTANT_TX__PADDING_ACTIVATION )
# define CANTP_CONSTANT_TX__PADDING_ACTIVATION          STD_OFF
#endif
#if !defined( CANTP_CONSTANT_TX__TA_TYPE )
# define CANTP_CONSTANT_TX__TA_TYPE                     STD_OFF
#endif
#if !defined( CANTP_CONSTANT_TX__ADDRESSING_FORMAT )
# define CANTP_CONSTANT_TX__ADDRESSING_FORMAT           STD_OFF
#endif
#if !defined( CANTP_CONSTANT_TX__MAX_PAYLOAD_LENGTH )
# define CANTP_CONSTANT_TX__MAX_PAYLOAD_LENGTH          STD_OFF
#endif


/* *** RX *** */
# if( CANTP_CONSTANT_RX__DL == STD_ON )
#  define vCanTp_PBCfg_RX__DL(elm)                      (CANTP_RX__DL)
# else
#  define vCanTp_PBCfg_RX__DL(elm)                      (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_DL, CANTP_RX__DL))
# endif

# if( CANTP_CONSTANT_RX__BS == STD_ON )
#  define vCanTp_PBCfg_RX__BS(elm)                      (CANTP_RX__BS)
# else
#  define vCanTp_PBCfg_RX__BS(elm)                      (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_BS, CANTP_RX__BS))
# endif

# if( CANTP_CONSTANT_RX__NAR == STD_ON )
#  define vCanTp_PBCfg_RX__NAR(elm)                     (CANTP_RX__NAR)
# else
#  define vCanTp_PBCfg_RX__NAR(elm)                     (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_NAR, CANTP_RX__NAR))
# endif

# if( CANTP_CONSTANT_RX__NBR == STD_ON )
#  define vCanTp_PBCfg_RX__NBR(elm)                     (CANTP_RX__NBR)
# else
#  define vCanTp_PBCfg_RX__NBR(elm)                     (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_NBR, CANTP_RX__NBR))
# endif

# if( CANTP_CONSTANT_RX__NCR == STD_ON )
#  define vCanTp_PBCfg_RX__NCR(elm)                     (CANTP_RX__NCR)
# else
#  define vCanTp_PBCfg_RX__NCR(elm)                     (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_NCR, CANTP_RX__NCR))
# endif

# if( CANTP_CONSTANT_RX__WFTMAX == STD_ON )
#  define vCanTp_PBCfg_RX__WFTMAX(elm)                  (CANTP_RX__WFTMAX)
# else
#  define vCanTp_PBCfg_RX__WFTMAX(elm)                  (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_WFTMAX, CANTP_RX__WFTMAX))
# endif

# if( CANTP_CONSTANT_RX__PADDING_ACTIVATION == STD_ON )
#  define vCanTp_PBCfg_RX__PADDING_ACTIVATION(elm)      (CANTP_RX__PADDING_ACTIVATION)
# else
#  define vCanTp_PBCfg_RX__PADDING_ACTIVATION(elm)      (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_PADDING_ACTIVATION, CANTP_RX__PADDING_ACTIVATION))
# endif

# if( CANTP_CONSTANT_RX__TA_TYPE == STD_ON )
#  define vCanTp_PBCfg_RX__TA_TYPE(elm)                 (CANTP_RX__TA_TYPE)
# else
#  define vCanTp_PBCfg_RX__TA_TYPE(elm)                 (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_TA_TYPE, CANTP_RX__TA_TYPE))
# endif

# if( CANTP_CONSTANT_RX__ADDRESSING_FORMAT == STD_ON )
#  define vCanTp_PBCfg_RX__ADDRESSING_FORMAT(elm)       (CANTP_RX__ADDRESSING_FORMAT)
# else
#  define vCanTp_PBCfg_RX__ADDRESSING_FORMAT(elm)       (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_RX_ADDRESSING_FORMAT, CANTP_RX__ADDRESSING_FORMAT))
# endif

# if( CANTP_CONSTANT_RX__STMIN == STD_ON )
#  define vCanTp_PBCfg_RX__STMIN(elm)                   (CANTP_RX__STMIN)
# else
#  define vCanTp_PBCfg_RX__STMIN(elm)                   (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_STMIN, CANTP_RX__STMIN))
# endif

# if( CANTP_CONSTANT_RX__DUPLEX_MODE == STD_ON )
#  define vCanTp_PBCfg_RX__DUPLEX_MODE(elm)             (CANTP_RX__DUPLEX_MODE)
# else
#  define vCanTp_PBCfg_RX__DUPLEX_MODE(elm)             (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_DUPLEX_MODE, CANTP_RX__DUPLEX_MODE))
# endif

# if( CANTP_CONSTANT_RX__MAX_PAYLOAD_LENGTH == STD_ON )
#  define vCanTp_PBCfg_RX__MAX_PLEN(elm)                (CANTP_RX__MAX_PAYLOAD_LENGTH)
# else
#  define vCanTp_PBCfg_RX__MAX_PLEN(elm)                (vCanTp_PBCfg(vCanTp_RxNsduCfg, elm, CANTP_MAX_PAYLOAD_LENGTH, CANTP_RX__MAX_PAYLOAD_LENGTH))
# endif

/* *** TX *** */
# if( CANTP_CONSTANT_TX__DL == STD_ON )
#  define vCanTp_PBCfg_TX__DL(elm)                      (CANTP_TX__DL)
# else
#  define vCanTp_PBCfg_TX__DL(elm)                      (vCanTp_PBCfg(vCanTp_TxNsduCfg, elm, CANTP_DL, CANTP_TX__DL))
# endif

# if( CANTP_CONSTANT_TX__NAS == STD_ON )
#  define vCanTp_PBCfg_TX__NAS(elm)                     (CANTP_TX__NAS)
# else
#  define vCanTp_PBCfg_TX__NAS(elm)                     (vCanTp_PBCfg(vCanTp_TxNsduCfg, elm, CANTP_NAS, CANTP_TX__NAS))
# endif

# if( CANTP_CONSTANT_TX__NBS == STD_ON )
#  define vCanTp_PBCfg_TX__NBS(elm)                     (CANTP_TX__NBS)
# else
#  define vCanTp_PBCfg_TX__NBS(elm)                     (vCanTp_PBCfg(vCanTp_TxNsduCfg, elm, CANTP_NBS, CANTP_TX__NBS))
# endif

# if( CANTP_CONSTANT_TX__NCS == STD_ON )
#  define vCanTp_PBCfg_TX__NCS(elm)                     (CANTP_TX__NCS)
# else
#  define vCanTp_PBCfg_TX__NCS(elm)                     (vCanTp_PBCfg(vCanTp_TxNsduCfg, elm, CANTP_NCS, CANTP_TX__NCS))
# endif

# if( CANTP_CONSTANT_TX__PADDING_ACTIVATION == STD_ON )
#  define vCanTp_PBCfg_TX__PADDING_ACTIVATION(elm)      (CANTP_TX__PADDING_ACTIVATION)
# else
#  define vCanTp_PBCfg_TX__PADDING_ACTIVATION(elm)      (vCanTp_PBCfg(vCanTp_TxNsduCfg, elm, CANTP_PADDING_ACTIVATION, CANTP_TX__PADDING_ACTIVATION))
# endif

# if( CANTP_CONSTANT_TX__TA_TYPE == STD_ON )
#  define vCanTp_PBCfg_TX__TA_TYPE(elm)                 (CANTP_TX__TA_TYPE)
# else
#  define vCanTp_PBCfg_TX__TA_TYPE(elm)                 (vCanTp_PBCfg(vCanTp_TxNsduCfg, elm, CANTP_TA_TYPE, CANTP_TX__TA_TYPE))
# endif

# if( CANTP_CONSTANT_TX__ADDRESSING_FORMAT == STD_ON )
#  define vCanTp_PBCfg_TX__ADDRESSING_FORMAT(elm)       (CANTP_TX__ADDRESSING_FORMAT)
# else
#  define vCanTp_PBCfg_TX__ADDRESSING_FORMAT(elm)       (vCanTp_PBCfg(vCanTp_TxNsduCfg, elm, CANTP_TX_ADDRESSING_FORMAT, CANTP_TX__ADDRESSING_FORMAT))
# endif

# if( CANTP_CONSTANT_TX__DUPLEX_MODE == STD_ON )
#  define vCanTp_PBCfg_TX__DUPLEX_MODE(elm)             (CANTP_TX__DUPLEX_MODE)
# else
#  define vCanTp_PBCfg_TX__DUPLEX_MODE(elm)             (vCanTp_PBCfg(vCanTp_TxNsduCfg, elm, CANTP_DUPLEX_MODE, CANTP_TX__DUPLEX_MODE))
# endif

# if( CANTP_CONSTANT_TX__MAX_PAYLOAD_LENGTH == STD_ON )
#  define vCanTp_PBCfg_TX__MAX_PLEN(elm)                (CANTP_TX__MAX_PAYLOAD_LENGTH)
# else
#  define vCanTp_PBCfg_TX__MAX_PLEN(elm)                (vCanTp_PBCfg(vCanTp_TxNsduCfg, elm, CANTP_MAX_PAYLOAD_LENGTH, CANTP_TX__MAX_PAYLOAD_LENGTH))
# endif

#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )

# if( CANTP_NUM_RXSDUS == 2 )
#  define CANTP_RX_CFG_PTR(hdl, pBElm, cElm)     ((hdl==CANTP_RX__RXNSDU_ID)?(cElm):(cElm##_FUNC))  /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */  /* PRQA S 0342 */ /* MD_CANTP_MISRA_0342 */
# else
#  define CANTP_RX_CFG_PTR(hdl, pBElm, cElm)     (cElm)
# endif

# define CANTP_RX1_CFG_PTR(hdl, pBElm, cElm)                          (cElm)
# define CANTP_RX1_CFG_PTR__DL(hdl)                                   (CANTP_RX__DL)
# define CANTP_RX1_CFG_PTR__NAR(hdl)                                  (CANTP_RX__NAR)
# define CANTP_RX1_CFG_PTR__NBR(hdl)                                  (CANTP_RX__NBR)
# define CANTP_RX1_CFG_PTR__NCR(hdl)                                  (CANTP_RX__NCR)
# define CANTP_RX1_CFG_PTR__WFTMAX(hdl)                               (CANTP_RX__WFTMAX)
# define CANTP_RX1_CFG_PTR__ADDRESSING_FORMAT(hdl)                    (CANTP_RX__ADDRESSING_FORMAT)
# define CANTP_RX_CFG_PTR__STMIN(hdl)                                 (CANTP_RX__STMIN)
# define CANTP_RX_CFG_PTR__BS(hdl)                                    (CANTP_RX__BS)
# define CANTP_RX_CFG_PTR__NBR(hdl)                                   (CANTP_RX_CFG_PTR(hdl, CANTP_NBR, CANTP_RX__NBR))
# define CANTP_TX_CFG_PTR(pBElm, cElm)                                (cElm)
# define CANTP_TX_CFG_PTR__ADDRESSING_FORMAT()                        (CANTP_TX__ADDRESSING_FORMAT)

#else /* CANTP_SINGLE_CONN_NOPB_OPTIMIZED */

# define CANTP_RX1_CFG_PTR(hdl, pBElm, cElm)     (pRxNsduCfg->pBElm)    /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
# define CANTP_RX_CFG_PTR(hdl,pBElm, cElm)       (pRxNsduCfg->pBElm)    /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */
# define CANTP_TX_CFG_PTR(pBElm, cElm)           (pTxNsduCfg->pBElm)    /* PRQA S 3410 */ /* MD_CANTP_MISRA_3410 */

# if( CANTP_CONSTANT_RX__DL == STD_ON )
#  define CANTP_RX_CFG_PTR__DL(hdl)                     (CANTP_RX__DL)
# else
#  define CANTP_RX_CFG_PTR__DL(hdl)                     (CANTP_RX_CFG_PTR(hdl, CANTP_DL, CANTP_RX__DL))
# endif
# define CANTP_RX1_CFG_PTR__DL(hdl)                     (CANTP_RX_CFG_PTR__DL(hdl))

# if( CANTP_CONSTANT_RX__BS == STD_ON )
#  define CANTP_RX_CFG_PTR__BS(hdl)                     (CANTP_RX__BS)
# else
#  define CANTP_RX_CFG_PTR__BS(hdl)                     (CANTP_RX_CFG_PTR(hdl, CANTP_BS, CANTP_RX__BS))
# endif
# define CANTP_RX1_CFG_PTR__BS(hdl)                     (CANTP_RX_CFG_PTR__BS(hdl))

# if( CANTP_CONSTANT_RX__STMIN == STD_ON )
#  define CANTP_RX_CFG_PTR__STMIN(hdl)                  (CANTP_RX__STMIN)
# else
#  define CANTP_RX_CFG_PTR__STMIN(hdl)                  (CANTP_RX_CFG_PTR(hdl, CANTP_STMIN, CANTP_RX__STMIN))
# endif
# define CANTP_RX1_CFG_PTR__STMIN(hdl)                  (CANTP_RX_CFG_PTR__STMIN(hdl))

# if( CANTP_CONSTANT_RX__NAR == STD_ON )
#  define CANTP_RX_CFG_PTR__NAR(hdl)                    (CANTP_RX__NAR)
# else
#  define CANTP_RX_CFG_PTR__NAR(hdl)                    (CANTP_RX_CFG_PTR(hdl, CANTP_NAR, CANTP_RX__NAR))
# endif
# define CANTP_RX1_CFG_PTR__NAR(hdl)                    (CANTP_RX_CFG_PTR__NAR(hdl))

# if( CANTP_CONSTANT_RX__NBR == STD_ON )
#  define CANTP_RX_CFG_PTR__NBR(hdl)                    (CANTP_RX__NBR)
# else
#  define CANTP_RX_CFG_PTR__NBR(hdl)                    (CANTP_RX_CFG_PTR(hdl, CANTP_NBR, CANTP_RX__NBR))
# endif
# define CANTP_RX1_CFG_PTR__NBR(hdl)                    (CANTP_RX_CFG_PTR__NBR(hdl))

# if( CANTP_CONSTANT_RX__NCR == STD_ON )
#  define CANTP_RX_CFG_PTR__NCR(hdl)                    (CANTP_RX__NCR)
# else
#  define CANTP_RX_CFG_PTR__NCR(hdl)                    (CANTP_RX_CFG_PTR(hdl, CANTP_NCR, CANTP_RX__NCR))
# endif
# define CANTP_RX1_CFG_PTR__NCR(hdl)                    (CANTP_RX_CFG_PTR__NCR(hdl))

# if( CANTP_CONSTANT_RX__WFTMAX == STD_ON )
#  define CANTP_RX_CFG_PTR__WFTMAX(hdl)                 (CANTP_RX__WFTMAX)
# else
#  define CANTP_RX_CFG_PTR__WFTMAX(hdl)                 (CANTP_RX_CFG_PTR(hdl, CANTP_WFTMAX, CANTP_RX__WFTMAX))
# endif
# define CANTP_RX1_CFG_PTR__WFTMAX(hdl)                 (CANTP_RX_CFG_PTR__WFTMAX(hdl))

# if( CANTP_CONSTANT_RX__PADDING_ACTIVATION == STD_ON )
#  define CANTP_RX_CFG_PTR__PADDING_ACTIVATION(hdl)     (CANTP_RX__PADDING_ACTIVATION)
# else
#  define CANTP_RX_CFG_PTR__PADDING_ACTIVATION(hdl)     (CANTP_RX_CFG_PTR(hdl, CANTP_PADDING_ACTIVATION, CANTP_RX__PADDING_ACTIVATION))
# endif
# define CANTP_RX1_CFG_PTR__PADDING_ACTIVATION(hdl)     (CANTP_RX_CFG_PTR__PADDING_ACTIVATION(hdl))

# if( CANTP_CONSTANT_RX__TA_TYPE == STD_ON )
#  define CANTP_RX_CFG_PTR__TA_TYPE(hdl)                (CANTP_RX__TA_TYPE)
# else
#  define CANTP_RX_CFG_PTR__TA_TYPE(hdl)                (CANTP_RX_CFG_PTR(hdl, CANTP_TA_TYPE, CANTP_RX__TA_TYPE))
# endif
# define CANTP_RX1_CFG_PTR__TA_TYPE(hdl)                (CANTP_RX_CFG_PTR__TA_TYPE(hdl))

# if( CANTP_CONSTANT_RX__ADDRESSING_FORMAT == STD_ON )
#  define CANTP_RX_CFG_PTR__ADDRESSING_FORMAT(hdl)      (CANTP_RX__ADDRESSING_FORMAT)
# else
#  define CANTP_RX_CFG_PTR__ADDRESSING_FORMAT(hdl)      (CANTP_RX_CFG_PTR(hdl, CANTP_RX_ADDRESSING_FORMAT, CANTP_RX__ADDRESSING_FORMAT))
# endif
# define CANTP_RX1_CFG_PTR__ADDRESSING_FORMAT(hdl)      (CANTP_RX_CFG_PTR__ADDRESSING_FORMAT(hdl))

/* *** TX *** */
# if( CANTP_CONSTANT_TX__DL == STD_ON )
#  define CANTP_TX_CFG_PTR__DL()                        (CANTP_TX__DL)
# else
#  define CANTP_TX_CFG_PTR__DL()                        (CANTP_TX_CFG_PTR(CANTP_DL, CANTP_TX__DL))
# endif

# if( CANTP_CONSTANT_TX__NAS == STD_ON )
#  define CANTP_TX_CFG_PTR__NAS()                       (CANTP_TX__NAS)
# else
#  define CANTP_TX_CFG_PTR__NAS()                       (CANTP_TX_CFG_PTR(CANTP_NAS, CANTP_TX__NAS))
# endif

# if( CANTP_CONSTANT_TX__NBS == STD_ON )
#  define CANTP_TX_CFG_PTR__NBS()                       (CANTP_TX__NBS)
# else
#  define CANTP_TX_CFG_PTR__NBS()                       (CANTP_TX_CFG_PTR(CANTP_NBS, CANTP_TX__NBS))
# endif

# if( CANTP_CONSTANT_TX__NCS == STD_ON )
#  define CANTP_TX_CFG_PTR__NCS()                       (CANTP_TX__NCS)
# else
#  define CANTP_TX_CFG_PTR__NCS()                       (CANTP_TX_CFG_PTR(CANTP_NCS, CANTP_TX__NCS))
# endif

# if( CANTP_CONSTANT_TX__ADDRESSING_FORMAT == STD_ON )
#  define CANTP_TX_CFG_PTR__ADDRESSING_FORMAT()         (CANTP_TX__ADDRESSING_FORMAT)
# else
#  define CANTP_TX_CFG_PTR__ADDRESSING_FORMAT()         (CANTP_TX_CFG_PTR(CANTP_TX_ADDRESSING_FORMAT, CANTP_TX__ADDRESSING_FORMAT))
# endif

# if( CANTP_CONSTANT_TX__PADDING_ACTIVATION == STD_ON )
#  define CANTP_TX_CFG_PTR__PADDING_ACTIVATION()        (CANTP_TX__PADDING_ACTIVATION)
# else
#  define CANTP_TX_CFG_PTR__PADDING_ACTIVATION()        (CANTP_TX_CFG_PTR(CANTP_PADDING_ACTIVATION, CANTP_TX__PADDING_ACTIVATION))
# endif

# if( CANTP_CONSTANT_TX__TA_TYPE == STD_ON )
#  define CANTP_TX_CFG_PTR__TA_TYPE()                   (CANTP_TX__TA_TYPE)
# else
#  define CANTP_TX_CFG_PTR__TA_TYPE()                   (CANTP_TX_CFG_PTR(CANTP_TA_TYPE, CANTP_TX__TA_TYPE))
# endif

# if( CANTP_CONSTANT_TX__TC == STD_ON )
#  define CANTP_TX_CFG_PTR__TC()                        (CANTP_TX__TC)
# else
#  define CANTP_TX_CFG_PTR__TC()                        (CANTP_TX_CFG_PTR(CANTPTC, CANTP_TX__TC))
# endif

#endif /* CANTP_SINGLE_CONN_NOPB_OPTIMIZED */

#if !defined(CANTP_TX_CFG_PTR__TC)
# define CANTP_TX_CFG_PTR__TC()                 (CANTP_TX_CFG_PTR(CANTPTC, CANTP_TX__TC))
#endif
#if !defined(CANTP_TX_CFG_PTR__TA_TYPE)
# define CANTP_TX_CFG_PTR__TA_TYPE()            (CANTP_TX_CFG_PTR(CANTP_TA_TYPE, CANTP_TX__TA_TYPE))
#endif
#if !defined(CANTP_TX_CFG_PTR__DL)
# define CANTP_TX_CFG_PTR__DL()                 (CANTP_TX_CFG_PTR(CANTP_DL, CANTP_TX__DL))
#endif
#if !defined(CANTP_TX_CFG_PTR__NAS)
# define CANTP_TX_CFG_PTR__NAS()                (CANTP_TX_CFG_PTR(CANTP_NAS, CANTP_TX__NAS))
#endif
#if !defined(CANTP_TX_CFG_PTR__NBS)
# define CANTP_TX_CFG_PTR__NBS()                (CANTP_TX_CFG_PTR(CANTP_NBS, CANTP_TX__NBS))
#endif
#if !defined(CANTP_TX_CFG_PTR__NCS)
# define CANTP_TX_CFG_PTR__NCS()                (CANTP_TX_CFG_PTR(CANTP_NCS, CANTP_TX__NCS))
#endif


/* *** helper macros to access BS and STmin *** */
#if ( (CANTP_ENABLE_EXT_API_BS == STD_ON) || (CANTP_ENABLE_CHANGE_PARAM == STD_ON) )
# define vCanTp_RxGetBlockSize(tpHdl)     CANTP_DYN_BS[(tpHdl)]
#else
# define vCanTp_RxGetBlockSize(tpHdl)     CANTP_RX_CFG_PTR__BS((tpHdl))
#endif

#if ( (CANTP_ENABLE_EXT_API_STMIN == STD_ON) || (CANTP_ENABLE_CHANGE_PARAM == STD_ON) )
# define vCanTp_RxGetSTmin(tpHdl)        CANTP_DYN_STMIN[(tpHdl)]
#else
# define vCanTp_RxGetSTmin(tpHdl)        CANTP_RX_CFG_PTR__STMIN((tpHdl))
#endif



/* Only for testing purposes */

#define CANTP_TAT_DYN                    (0)
#define CANTP_TAT_PHYS                   (1)
#define CANTP_TAT_FUNC                   (2)

#define CANTP_INVALID_BS                 (0xFFu)
#define CANTP_INVALID_STMIN              (0xFFu)

#if(!defined(CANTP_TX__TA_TYPE))
# define CANTP_CHECK_TX_TA_TYPE          CANTP_TAT_DYN
#else
# if(CANTP_TX__TA_TYPE == CANTP_PHYSICAL)
#  define CANTP_CHECK_TX_TA_TYPE         CANTP_TAT_PHYS
# else
#  define CANTP_CHECK_TX_TA_TYPE         CANTP_TAT_FUNC
# endif
#endif

#if(!defined(CANTP_RX__TA_TYPE))
# define CANTP_CHECK_RX_TA_TYPE          CANTP_TAT_DYN
#else
# if(CANTP_RX__TA_TYPE == CANTP_PHYSICAL)
#  define CANTP_CHECK_RX_TA_TYPE         CANTP_TAT_PHYS
# else
#  define CANTP_CHECK_RX_TA_TYPE         CANTP_TAT_FUNC
# endif
#endif

#if(!defined(CANTP_RX__BS))
# define CANTP_CHECK_BS              STD_ON         /* BS need to be checked; it is not constant */
#else
# if(CANTP_RX__BS != 0)
#  define CANTP_CHECK_BS             STD_ON         /* BS need to be checked; it is constant but != 0 */
# else
#  if( (CANTP_ENABLE_CHANGE_PARAM == STD_ON) || (CANTP_ENABLE_EXT_API_BS == STD_ON) )
#   define CANTP_CHECK_BS            STD_ON         /* BS need to be checked; it is constant and 0, but may be changed by API */
#  else
#   define CANTP_CHECK_BS            STD_OFF        /* BS check not needed; it is always 0 */
#  endif
# endif
#endif

#if( (CANTP_ENABLE_CHANGE_PARAM == STD_ON) || (CANTP_ENABLE_EXT_API_BS == STD_ON) )
# define CANTP_VARIABLE_BS          STD_ON          /* BS may be changed by APIs */
#else
# if (CANTP_CONSTANT_RX__BS == STD_OFF)
#  define CANTP_VARIABLE_BS         STD_ON          /* BS is different between N_SDUs */
# else
#  define CANTP_VARIABLE_BS         STD_OFF         /* BS is constant and can't be changed --> CANTP_RX__BS is available */
# endif
#endif

#if(!defined(CANTP_RX__PADDING_ACTIVATION))
# define CANTP_CHECK_RX_PADDING      STD_ON
#else
# if(CANTP_RX__PADDING_ACTIVATION != 0)
#  define CANTP_CHECK_RX_PADDING     STD_ON
# else
#  define CANTP_CHECK_RX_PADDING     STD_OFF
# endif
#endif

#if(!defined(CANTP_TX__PADDING_ACTIVATION))
# define CANTP_CHECK_TX_PADDING      STD_ON
#else
# if(CANTP_TX__PADDING_ACTIVATION != 0)
#  define CANTP_CHECK_TX_PADDING     STD_ON
# else
#  define CANTP_CHECK_TX_PADDING     STD_OFF
# endif
#endif


/**************************************************************************************************
* Consistency check
**************************************************************************************************/
#if !defined (CANTP_USE_DUMMY_STATEMENT)
# define CANTP_USE_DUMMY_STATEMENT    STD_ON
#endif

#ifdef V_EXTENDED_BUILD_LIB_CHECK
 /* pre-processor checks for building the library */
# if( CANTP_CONFIG_VARIANT == 1 )
#  error "This configuration variant is not sufficient to support a LIB build process."
# endif
#endif

/* GENy Tp_AsrTpCan DLL Version 1.13.00 is the last one with an "uint8 WFTmax counter". 
   After this version the data type is changed to uint16. This is done (due to the include sequence) in CanTp_Types.h
   ESCAN00033429/00032457: Data type of CanTp_WFTmax changed (uint8 to uint16) */

#if( CANTP_SINGLE_CONN_NOPB_OPTIMIZED == STD_ON )
# if( CANTP_SINGLE_CONN_OPTIMIZED == STD_OFF )
#  error "The 'Single Connection' optimization must be activated if the 'No Postbuild' optimization is used !"
# endif
# if( CANTP_NUM_RXSDUS > 2 )
#  error "The 'Single Connection' optimization does not allow more than 2 (one physical and one functional ta-type) Rx-Pdu-Ids !"
# endif
#endif
#if( CANTP_SINGLE_CONN_OPTIMIZED == STD_ON )
# if( CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON )
#  error "It makes no sense to use the 'Single Connection' together with the 'Dynamic Channel' optimization. Please turn off one of the two !"
# endif
# if (CANTP_HAVE_INIT_CFG_PTR == STD_OFF)
#  if( CANTP_NUM_RX_CHANNELS > 2 )
#   error "The 'Single Connection' optimization does not allow more than 2 (one physical and one functional ta-type) Rx-Pdu-Ids !"
#  endif
# endif
#endif

#if( (CANTP_STANDARD_ADDRESSING == STD_OFF) && (CANTP_EXTENDED_ADDRESSING == STD_OFF) && (CANTP_MIXED11_ADDRESSING == STD_OFF) )
#  error "Undefined Addressing Type(s) configured !"
#else
# if( ((CANTP_STANDARD_ADDRESSING == STD_ON)  && ((CANTP_EXTENDED_ADDRESSING == STD_ON) || (CANTP_MIXED11_ADDRESSING == STD_ON))) ||\
      ((CANTP_STANDARD_ADDRESSING == STD_OFF) && ((CANTP_EXTENDED_ADDRESSING == STD_ON) && (CANTP_MIXED11_ADDRESSING == STD_ON))) ||\
      ((CANTP_STANDARD_ADDRESSING == STD_ON)  && ((CANTP_EXTENDED_ADDRESSING == STD_ON) && (CANTP_MIXED11_ADDRESSING == STD_ON)))   \
    )
#  define CANTP_MULTIPLE_ADDRESSING   STD_ON
# else
#  define CANTP_MULTIPLE_ADDRESSING   STD_OFF
# endif
#endif


#if( CANTP_ENABLE_WRAP_CANCEL_TRANSMIT == STD_ON )
# if( CANTP_TC == STD_OFF )
#  error "Inconsistent configuration: Please enable the CanTp Transmit Cancellation"
# endif
#endif

#if !defined( CANTP_RX_GET_BUFFER_FROM_ISR )
# define CANTP_RX_GET_BUFFER_FROM_ISR     STD_ON
#endif
#if !defined( CANTP_TX_FC_FROM_ISR )
# define CANTP_TX_FC_FROM_ISR             STD_ON
#endif
#if !defined( CANTP_TX_GET_BUFFER_SYNC )
# define CANTP_TX_GET_BUFFER_SYNC         STD_ON
#endif
#if !defined( CANTP_ASYNC_TRANSMIT )
# define CANTP_ASYNC_TRANSMIT             STD_OFF
#endif
#if !defined( CANTP_ASYNC_SF_TRANSMIT )
# define CANTP_ASYNC_SF_TRANSMIT          STD_OFF
#endif

#if( CANTP_TX_FC_FROM_ISR == STD_ON )
# define VCANTP_RXSTATETASK(hdl)          vCanTp_RxStateTask(hdl)
#else
# define VCANTP_RXSTATETASK(hdl)
#endif

#if !defined( CANTP_CONSTANT_BS )
# if defined( CANTP_AUTOSARVERSION4 )
#  define CANTP_CONSTANT_BS               STD_ON
# else
#  define CANTP_CONSTANT_BS               STD_OFF
# endif
#else
# if defined( CANTP_AUTOSARVERSION3 )
#  if( CANTP_CONSTANT_BS == STD_ON )
/* keep quiet, this will also change with AR 3.2 
#   error "Constant blocksize not supported with AUTOSAR 3.1"
*/
#  endif
# endif
#endif

/* Duplex Mode */
#if( CANTP_CONSTANT_RX__DUPLEX_MODE == STD_ON )
# if( CANTP_RX__DUPLEX_MODE == CANTP_MODE_HALF_DUPLEX )
#  define CANTP_RX__ENABLE_HALF_DUPLEX_CHECK    STD_ON
# else
#  define CANTP_RX__ENABLE_HALF_DUPLEX_CHECK    STD_OFF
# endif
#else
# define CANTP_RX__ENABLE_HALF_DUPLEX_CHECK     STD_ON
#endif
#if( CANTP_CONSTANT_TX__DUPLEX_MODE == STD_ON )
# if( CANTP_TX__DUPLEX_MODE == CANTP_MODE_HALF_DUPLEX )
#  define CANTP_TX__ENABLE_HALF_DUPLEX_CHECK   STD_ON
# else
#  define CANTP_TX__ENABLE_HALF_DUPLEX_CHECK   STD_OFF
# endif
#else
# define CANTP_TX__ENABLE_HALF_DUPLEX_CHECK    STD_ON
#endif

/* Serialize transmit requests */
#if !defined( CANTP_TX_SERIALIZE )
# define CANTP_TX_SERIALIZE               STD_OFF
#endif
#if !defined( CANTP_TX_SINGLE_SERIALIZE )
# define CANTP_TX_SINGLE_SERIALIZE        STD_ON
#endif

#define CANTP_TX_MAX_NUM_CONFLICT         16 /* must match the bittype for wrpos and rdpos to ensure a proper wrap around !!! */

typedef struct sTxConflict
{
  PduIdType      hdl[CANTP_TX_MAX_NUM_CONFLICT];
  uint8          dir[CANTP_TX_MAX_NUM_CONFLICT];
  vCanTp_BitType wrpos:4;
  vCanTp_BitType rdpos:4;
  vCanTp_BitType idx:4;
} vCanTp_TxConflictType;

typedef struct sTxSemaphore
{
  PduIdType            hdl;
  vCanTp_operatingType dir;
} vCanTp_TxSemaphoreType;


/* Definition of API-Ids. */
#define CanTp_Init_SId                     0x01
#define CanTp_Shutdown_SId                 0x02
#define CanTp_Transmit_SId                 0x03
#define CanTp_RxIndication_SId             0x04
#define CanTp_TxConfirmation_SId           0x05
#define CanTp_MainFunction_SId             0x06
#define CanTp_GetVersionInfo_SId           0x07
#define CanTp_CancelTransmitRequest_SId    0x08  /* V3.0.0 R4.0 Rev 1 */
#define CanTp_CancelReceiveRequest_SId     0x09  /* V3.0.0 R4.0 Rev 1 */
#define CanTp_ChangeParameterRequest_Sid   0x0A  /* V3.0.0 R4.0 Rev 1 */
#define CanTp_ReadParameterRequest_Sid     0x81  /* Vector non AR extension */
#define CanTp_RxInit_Sid                   0x90  /* Vector non AR extension */
#define CanTp_TxInit_Sid                   0x91  /* Vector non AR extension */
/* ***************************************** */

/* Available if CANTP_ENABLE_EXT_API_STMIN == STD_ON */
#define CanTp_SetSTmin_SId                 0x10  /* SiD requested by customer */
/* Available if CANTP_ENABLE_EXT_API_BS == STD_ON */
#define CanTp_SetBS_SId                    0x11  /* SiD requested by customer */
/* Available if CANTP_RXTX_MAINFUNCTION_API == STD_ON */
#define CanTp_MainFunctionRx_SId           0x20
#define CanTp_MainFunctionTx_SId           0x21
#if( CANTP_RXTX_MAINFUNCTION_API == STD_ON )
# define CanTp_MFuncRx_SId                 CanTp_MainFunctionRx_SId
# define CanTp_MFuncTx_SId                 CanTp_MainFunctionTx_SId
#else
# define CanTp_MFuncRx_SId                 CanTp_MainFunction_SId
# define CanTp_MFuncTx_SId                 CanTp_MainFunction_SId
#endif




/* macros for critical section handling */
#if defined( CANTP_AUTOSARVERSION3 )
# define Tp_AsrTpCan_EnterCritical(area) SchM_Enter_CanTp(area)
# define Tp_AsrTpCan_LeaveCritical(area) SchM_Exit_CanTp(area)
#else
# define Tp_AsrTpCan_EnterCritical(area) SchM_Enter_CanTp_##area()  /* PRQA S 0342 */ /* MD_CANTP_MISRA_0342 */
# define Tp_AsrTpCan_LeaveCritical(area) SchM_Exit_CanTp_##area()   /* PRQA S 0342 */ /* MD_CANTP_MISRA_0342 */
#endif

/*******************************************************************************
* Global data types and structures
*******************************************************************************/
/* vCanTp_TxReturnType */
typedef uint8 vCanTp_TxReturnType; /* CanIf_Transmit() ... */                              

/**************************************************************************************************
* External Data
**************************************************************************************************/
#define CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

/* Obsolete: is referenced via CanTp_Lcfg.h: extern VAR(vCanTp_AdminDataType, CANTP_VAR_NOINIT) vCanTp_AdminData; */

#define CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"


#define CANTP_START_SEC_CONST_32BIT
#include "MemMap.h"

#if(CANTP_CRC_CHECK == STD_ON )
extern CONST(uint32, CANTP_CONST) CanTp_LinktimeCRC;
#endif

#define CANTP_STOP_SEC_CONST_32BIT
#include "MemMap.h"

/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"

/* this switch is just a temporary workaround until compiler abstractions are implemented allover stable */
/* AUTOSAR CanTp API */
extern FUNC(void, CANTP_CODE)           CanTp_InitMemory(void);

#if defined( CANTP_AUTOSARVERSION4 )
extern FUNC(void, CANTP_CODE) CanTp_Init(P2CONST(vCanTp_CfgType, AUTOMATIC, CANTP_CODE) pCfgPtr);   /* CanTp208:  Added parameter for CanTp_Init function */
#else
# if(CANTP_HAVE_INIT_CFG_PTR == STD_ON)
extern FUNC(void, CANTP_CODE) CanTp_Init(CONSTP2CONST(void, AUTOMATIC, CANTP_CODE) pCfgPtr);
# else
extern FUNC(void, CANTP_CODE) CanTp_Init(void);
# endif
#endif

#if (CANTP_VERSION_INFO_API == STD_ON)
extern FUNC(void, CANTP_CODE)           CanTp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTP_APPL_DATA) pVersionInfo);
#endif
extern FUNC(void, CANTP_CODE)           CanTp_Shutdown(void);

#if defined( CANTP_AUTOSARVERSION3 )
/* For AR4 the SchM_CanTp.h contains the prototypes for the main funktions ([rte_sws_7283]) */
extern FUNC(void, CANTP_CODE)           CanTp_MainFunction(void);
# if( CANTP_RXTX_MAINFUNCTION_API == STD_ON )
extern FUNC(void, CANTP_CODE)           CanTp_MainFunctionRx(void);
extern FUNC(void, CANTP_CODE)           CanTp_MainFunctionTx(void);
# endif
#endif

#if ( CANTP_ENABLE_CHANGE_PARAM == STD_ON )
extern FUNC(Std_ReturnType , CANTP_CODE)                        CanTp_ChangeParameterRequest(PduIdType CanTpRxSduId, TPParameterType Pid, uint16  Pval);
#define CanTp_ChangeParameter(RxSduId, ParamId, ParamVal)       CanTp_ChangeParameterRequest(RxSduId, ParamId, ParamVal)        /* AR3.2 function name remapping */
extern FUNC(Std_ReturnType , CANTP_CODE)                        CanTp_ReadParameterRequest(  PduIdType CanTpRxSduId, TPParameterType Pid, uint16* Pval);
#define CanTp_ReadParameter(RxSduId, ParamId, ParamVal)         CanTp_ReadParameterRequest(RxSduId, ParamId, ParamVal)          /* AR3.2 function name remapping */
#endif
#if ( CANTP_ENABLE_EXT_API_STMIN == STD_ON )
extern FUNC(uint8, CANTP_CODE) CanTp_SetSTmin(PduIdType CanTpRxSduId, uint8 CanTpSTmin);
#endif
#if ( CANTP_ENABLE_EXT_API_BS == STD_ON )
extern FUNC(uint8, CANTP_CODE) CanTp_SetBS(PduIdType CanTpRxSduId, uint8 CanTpBS);
#endif

#if( (CANTP_ENABLE_TX_NSDU_REMAPPING == STD_ON) && (CANTP_ENABLE_WRAP_TRANSMIT == STD_ON) )
extern FUNC(Std_ReturnType, CANTP_CODE) CanTpWrapper_Transmit(PduIdType CanTpTxSduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pData);
#endif
extern FUNC(Std_ReturnType, CANTP_CODE) CanTp_Transmit(       PduIdType CanTpTxSduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pData);

#if( CANTP_TC == STD_ON )
# if( CANTP_ENABLE_WRAP_CANCEL_TRANSMIT == STD_ON )
extern FUNC(Std_ReturnType, CANTP_CODE) CanTpWrapper_CancelTransmitRequest(PduIdType CanTpTxPduId);
# endif
extern FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelTransmitRequest(PduIdType CanTpTxSduId);
#define CanTp_CancelTransmit(TxSduId)   CanTp_CancelTransmitRequest(TxSduId)    /* AR3.2 function name remapping */
#endif

#if( CANTP_RC == STD_ON )
extern FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelReceiveRequest(PduIdType CanTpRxSduId);  
#define CanTp_CancelReceive(RxSduId)    CanTp_CancelReceiveRequest(RxSduId)     /* AR3.2 function name remapping */
#endif

#if(CANTP_HAVE_EXT_DEV_ERROR_DETECT == STD_ON)
extern FUNC(void, CANTP_CODE)           vCanTp_ReportError(VAR(uint16, AUTOMATIC) ModuleId, 
                                                           VAR(uint8,  AUTOMATIC) InstanceId, 
                                                           VAR(uint8,  AUTOMATIC) ApiId, 
                                                           VAR(uint16, AUTOMATIC) ErrorId, 
                                                           VAR(uint32, AUTOMATIC) ErrorParam );
#endif

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#endif
/* ifndef CANTP_H */
/************   Organi, Version 3.7.0 Vector-Informatik GmbH  ************/
