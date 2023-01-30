/* Kernbauer Version: 1.16 Konfiguration: Gw_AsrPduR Erzeugungsgangnummer: 1158 */

/* STARTSINGLE_OF_MULTIPLE */

/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2011 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PduR.c
 *      Project:  Gw_AsrPduR
 *       Module:  MICROSAR PDU Router
 *    Generator:  GENy
 *
 *  Description:  Implements AUTOSAR PDU Router SWS Version: 2.2.1
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Hartmut Hoerner               HH            Vector Informatik GmbH
 *  Gunnar de Haan                dH            Vector Informatik GmbH
 *  Holger Birke                  Bir           Vector Informatik GmbH
 *  Hannes Haas                   vishs         Vector Informatik GmbH
 *  Erich Schondelmaier           visehs        Vector Informatik GmbH
 *  Gunnar Meiss                  visms         Vector Informatik GmbH
 *  Safiulla Shakir               visssa        Vector Informatik GmbH
 *  Sebastian Waldvogel           visswa        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version  Date        Author     Change Id       Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.00.00  2004-10-21   HH/dH/Bir -               initial version
 *  1.01.00  2004-11-18   HH        -               rework of code inspection
 *  1.02.00  2005-07-20   HH        -               update to Autosar 1.0 spec
 *  2.00.00  2006-06-14   vishs     -               Update to Autosar 2.0 spec
 *  2.01.00  2006-06-16   vishs     -               ASR compliant header file structure
 *                        vishs     ESCAN00017204   added support for LIN_IF
 *                        vishs     ESCAN00017205   naming convention for internal names
 *                        vishs     ESCAN00017289   code replication is not used
 *                        vishs     ESCAN00018046   consistency check of GENy dll implementation version
 *                        vishs     ESCAN00018049   added support for CAN_TP
 *  2.02.00  2007-02-09   vishs     ESCAN00018027   configuration variant 3 (Post-Build) support
 *                        vishs     ESCAN00018918   Adapted multiple include protection according to impl. rules
 *                        vishs     ESCAN00019488   Allow DCM I-PDU transmission over CAN_IF
 *  2.03.00  2007-08-07   vishs     ESCAN00019585   Corrected assertion handing in PduR_DcmTransmit()
 *                        vishs     ESCAN00020247   Update to AUTOSAR 2.1 specification
 *                        vishs     ESCAN00020699   Routing between DCM and FrTp and FrIf added
 *                        vishs     ESCAN00021037   Removed magic number for link- and pre-compile configuration
 *                        vishs     ESCAN00021608   Compiler error in systems with LinIf and Gw_PduR
 *  2.04.00  2007-11-06   vishs     ESCAN00021825   Added interface routing for CanIf, LinIf and FrIf
 *                        vishs     ESCAN00022036   Removed non-selectable post-build configuration feature
 *                        vishs     ESCAN00022639   Added TP layer routing for CanTp and FrTp
 *                        vishs     ESCAN00023115   Added callout functions for IF layer routing (ASR RFC18729)
 *  2.04.01  2007-12-05   vishs     ESCAN00023555   Removed linker error within IF Gateway if used on CAN bus only
 *  2.05.00  2008-01-31   vishs     ESCAN00023614   Added J1939 support for COM
 *                        vishs     ESCAN00023615   Allow forwarding of PDUs between COM and CanTp
 *                        vishs     ESCAN00023527   Update to AUTOSAR 2.2.1 specification (AUTOSAR Release 3.0)
 *                                                   - Compiler and memory abstraction
 *                                                   - AR version check of used BSW modules (AUTOSAR 2.1 versions)
 *  3.00.00  2008-04-03   vishs     ESCAN00024199   TP layer gateway ring-buffer support added
 *                        vishs     ESCAN00024576   Fixed compiler warning
 *                        vishs     ESCAN00023527   AR version check of used BSW modules (AUTOSAR 3.0 versions)
 *                        vishs     ESCAN00024677   Corrected return value check of callout functions
 *                        vishs     ESCAN00024330   Renamed ComTpApi_* to Com_Tp*
 *                        vishs     ESCAN00024855   Removed compiler warning
 *                        vishs     ESCAN00025432   Support of DEM errors provided as defines
 *                        vishs     ESCAN00025460   Removed consistency chek for IF gateway configuration data
 *  3.01.00  2008-05-16   vishs     ESCAN00026211   Library consistency check
 *                        vishs     ESCAN00026291   Removed V_CRITICAL_SECTION_USE_VECTOR_COMMENT
 *                        vishs     ESCAN00026292   PduR_GetVersionInfo now exports instanceID
 *                        vishs     ESCAN00026645   Generator Version Check added
 *  3.02.00  2008-06-17   vishs     ESCAN00027250   Support for TMS320 memory model added (no changes required)
 *                        vishs     ESCAN00026645   TP Gateway Generator Version Check added
 *                        vishs     ESCAN00027223   Direct include of Vector Informatik include files
 *  3.03.00  2008-07-14   vishs     ESCAN00027971   TP layer routing hangs in case of a buffer overflow
 *                        vishs     ESCAN00027975   Missing cast leads to generator tool compatiblity check failing
 *                        vishs     ESCAN00027978   Abort initialization after failed generator version check
 *                        vishs     ESCAN00028107   Removed compiler warning
 *                        vishs     ESCAN00027670   Allow deactivation of gateway features at pre-compile time
 *  3.04.00  2008-10-16   vishs     ESCAN00027223   Modified include structure of Vector Informatik includes
 *                        vishs     ESCAN00029044   Loss of TP PDUs during TP layer routing
 *                        vishs     ESCAN00029134   Changed FRTP AR version compatibility check to correct version
 *                        vishs     ESCAN00029121   Corrected memory qualifiers for post-build modifiable types
 *                        vishs     ESCAN00029438   Remove unrequired call to DET in case of single frame TP routing
 *                        vishs     ESCAN00029545   Own MemCpy functions provided - activation trough user config file
 *                        vishs     ESCAN00029591   Optimized access to API forwarding routing tables
 *                        vishs     ESCAN00029773   Precompile- and link time configuration CRC check
 *                        vishs     ESCAN00029986   Application access to interface and TP layer services
 *                        vishs     ESCAN00030053   Added Dcm to FrIf API forwarding
 *  3.05.00  2008-11-13   vishs     ESCAN00031161   Wrong definition for Memmap section
 *                        vishs     ESCAN00031220   Internal TP I-PDU communication
 *  3.05.01  2009-01-08   vishs     ESCAN00032284   Changed pre-configuration
 *  3.06.00  2009-01-28   visehs    ESCAN00032637   Add IpduM Routing
 *           2009-03-27   visehs    ESCAN00033510   Compiler Warning: variable pQStart was declared but never referenced
 *           2009-03-27   visehs    ESCAN00033991   Only execute the main body of GwTp_RxIndication if this is the first call to RxIndication for the ongoing routing.
 *           2009-04-02   visehs    ESCAN00034346   Linker Error in PduR.c with PduR_Core functions
 *  3.06.01  2009-04-02   visehs    ESCAN00034423   Wrong praeprocessor directive in PduR.c for IpduM support in the Lin and Flexray API
 *           2009-04-02   visehs    ESCAN00034424   Wrong function call for IpduM TxConfirmation in the Flexray interface
 *           2009-04-02   visehs    ESCAN00034426   Typo in function calls IpduM TxConfirmation and RxConfiramtion in the Lin API
 *  3.06.02  2009-04-23   visehs    ESCAN00034709   Uninitialized struct in PduR_GwTp_RxIndication
 *  3.07.00  2009-04-09   visehs    ESCAN00035755   Add MostIf and MostTp Support
 *           2009-06-10   visehs    ESCAN00035777   Add Il_AsrIpduMIsBmwSub Support
 *           2009-06-10   visehs    ESCAN00035575   one preprocessor switch encapsulate all BAC21 features
 *  3.08.00  2009-06-22   visms     ESCAN00035904   Support Multiple Configurations
 *  3.09.00  2009-06-29   visms     ESCAN00035624   Support LinTp
 *           2009-06-29   visehs    ESCAN00034705   Renamed J1939 as J1939Tp
 *           2009-07-09   vishs     ESCAN00033781   AUTOSAR 4.0 Style CanTp routing
 *           2009-07-16   vishs     ESCAN00034231   Remove Det Error PDUR_E_TP_BUFFER_SIZE_LIMIT
 *           2009-07-16   visms     ESCAN00034190   Pointless comparison of unsigned integer with zero in <MSN>_Init()
 *           2009-07-16   visms     ESCAN00036100   Library Preprocessor Checks
 *           2009-08-04   visms     ESCAN00036387   Intra ECU TP communication fails for Service ID 0x19
 *           2009-07-20   visehs    ESCAN00036552   Allow more than 255 routing relations for the GW use case to be configured
 *  3.09.01  2009-09-18   visms     ESCAN00037839   Support MOST Dynamic DLC Routing
 *                        visms     ESCAN00037840   Change MostTpDapHeaderType to kMostIfDapHdrLen
 *  3.09.02  2009-09-15   visehs    ESCAN00037986   PDU Routing to the wrong bus in case of LinTp in combination with FrTp
 *           2009-10-15   visehs    ESCAN00038015   Memory area could overwritten during VPB communication
 *           2009-10-15   visehs    ESCAN00037887   Service IDs reported to DET are not matching the specification
 *  3.10.00  2009-09-09   visehs    ESCAN00037658   Support SoAdTp communication (IP Support)
 *  3.11.00  2009-09-26   visehs    ESCAN00038443   Tp messages will not be gated using the AUTOSAR 4.0 CanTp API if the Chunk Size and Buffer Size are equal
 *           2009-09-26   visehs    ESCAN00037849   Support CanNm2Com and FrNm2Com Interface
 *           2009-11-09   visms     ESCAN00037251   Support Dobt-CanTp Dispatcher
 *           2009-11-10   visms     ESCAN00038295   Compiler error: PDUR_LINTP2COM_ROUTING undefined
 *           2009-11-10   visms     ESCAN00038296   Compiler error: PDUR_DEACTIVATE_DEM_VERSION_CHECK undefined
 *           2009-11-11   visehs    ESCAN00039029   Service ID PDUR_FCT_DCMTX is reported to DET in PduR_ComTransmit
 *           2009-11-13   visms     ESCAN00038625   Support E_PENDING in as return of <Lo>Transmit
 *           2009-11-13   visehs    ESCAN00037889   Memory is overwritten with MOST
 *           2009-11-20   visehs    ESCAN00038553   Manage Remaining Chunks within the Buffer
 *  3.12.00  2010-02-02   visms     ESCAN00039221   Call CddDobt_PduRCanTpCallout only for Dobt capable CanTp Rx Pdus
 *           2010-02-19   visehs    ESCAN00040855   Tp messages will not be routed if the payload is smaller than the chunksize
 *           2010-02-25   visehs    ESCAN00041039   CanTp connections are failing to Dcm, Com and ApplTp
 *           2010-03-01   visms     ESCAN00041272   MISRA-C:2004 Update
 *  3.13.00  2010-03-24   visehs    ESCAN00041796   Linker Error: unresolved external symbol Ipdum_TriggerTransmit
 *           2010-03-24   visehs    ESCAN00041799   Compiler Error:  'PduR_TpCnv_TxCom2LoInfo' : undeclared identifier
 *           2010-03-24   visehs    ESCAN00040669   Compiler Warning:  'pCATx' :unused unreferenced local variable
 *           2010-03-24   visehs    ESCAN00039668   Support Routing of 2 Consecutive CanTp Single Frames for CanTp 4.0 API
 *           2010-04-01   visehs    ESCAN00042017   Det Error occurs due to an unexpected API call
 *           2010-04-15   visehs    ESCAN00040305   Add Feature Tp Parameter Control
 *           2010-05-17   visehs    ESCAN00042972   Misra warning: Structure has fewer initializers than its declared size
 *           2010-05-17   visehs    ESCAN00042974   Null pointer assignment in function PduR_Core_CanTpProvideRxBuffer()
 *           2010-05-21   visehs    ESCAN00043076   Rename function parameter value name J1939Xxx to J1939TpXxx
 *  3.13.01  2010-06-21   visehs    ESCAN00043511   Det_ReportError is called with IpduM Module ID
 *           2010-06-21   visehs    ESCAN00043491   Add BAC30 IPDUM Compatibility Defines
 *  3.14.00  2010-06-25   visssa    ESCAN00043581   Support TP Receive Cancellation
 *           2010-07-20   visssa    ESCAN00043968   Support TP Transmit Cancellation
 *           2010-07-28   visms     ESCAN00044309   Multiple ECU: PduR_DcmChangeParameterRequest with inactive DcmRxPduId
 *           2010-07-30   visms     ESCAN00034188   Optimize ProvideBuffer, RxIndication and TxConfirmation calls in PduR_MainFunction
 *           2010-08-10   visehs    ESCAN00044523   Support Optimized Routing with FrTp
 *           2010-08-11   visehs    ESCAN00043995   Support PduRoutingPathGoups
 *           2010-08-11   visehs    ESCAN00041722   Compiler warning: unreachable code in PduR_CanTpProvideRxBuffer
 *  3.14.01  2010-08-21   visehs    ESCAN00045516   RoutingPath Groups cannot be disabled
 *           2010-08-21   visehs    ESCAN00045422   Linker Error: unresolved external symbol ApplIf_TxConfirmation
 *           2010-08-22   visehs    ESCAN00039232   Added a consistency check for the PduIdType
 *           2010-08-22   visehs    ESCAN00045553   Second FrTp consecutive frame to Dcm and ApplTp is blocked forever until watch dog reset
 *  3.14.02  2010-10-05   visehs    ESCAN00045786   ApplTp_TxConfirmation is not called
 *           2010-10-13   visehs    ESCAN00045795   RAM will be overwritten is no TP Buffers are configured
 *           2010-10-15   visms     ESCAN00045936   Notify Dem if the PduIdType Check fails
 *           2010-10-15   visms     ESCAN00045505   Routing of Functional Requests with Fan Out Stops
 *           2010-10-15   visms     ESCAN00045944   Physical Multiple ECU: ECU is blocked until Watch-Dog reset
 *           2010-10-15   visms     ESCAN00045891   PduR_<Up>CancelReceiveRequest does not work
 *           2010-10-21   visms     ESCAN00044894   Include and check PduR Headers only if the component is supported
 *           2010-10-21   visms     ESCAN00046298   Linker Error with PduR_GwTpTxConfirmation
 *  3.14.03  2010-10-21   visehs    ESCAN00046355   Compile error due to missing Define "PDUR_CANIF_SUPPORT"
 *  3.14.04  2010-10-27   visehs    ESCAN00046407   Compile error occurs if PDUR routing group support is enabled
 *  3.15.00  2010-10-19   visms     ESCAN00045920   Support Rx CanNm and FrNm
 *           2010-11-30   visms     ESCAN00046248   Perform AUTOSAR version check only for Vector
 *           2010-12-08   visms     ESCAN00040225   AR3-297 AR3-894: Support PduInfoType instead of the DataPtr
 *           2010-12-16   visehs    ESCAN00047004   Balance the Routing time of Physical TP Routings
 *           2010-12-08   visms     ESCAN00047232   Compiler warning PduR_Core_UpTpTxConfirmation declared but not used
 *           2010-12-16   visehs    ESCAN00045919   Optimize Wrap Around interaction with Lower Layer TPs and Physical TP Routings
 *           2011-01-17   visms     ESCAN00046408   Compiler Error: struct has no field "DestPduCntIndex"
 *           2011-02-22   visms     ESCAN00048509   Support CDD
 *           2011-02-22   visms     ESCAN00048088   Length of copied SDU data is not indicated in PduR_<Lo>TriggerTransmit() API
 *  3.15.01  2011-02-24   visehs    ESCAN00048899   Compiler warning occurs: zero used for undefined preprocessing identifier
 *           2011-02-24   visehs    ESCAN00048901   Compiler warning occurs:" PduR_GwIf_Init" was declared but never referenced
 *           2011-02-24   visehs    ESCAN00048903   Compiler warning: nested comment is not allowed
 *           2011-02-25   visms     ESCAN00048926   Unexpected ECU behavior on reception of a TP SDU
 *           2011-02-25   visms     ESCAN00048937   Compiler Warning: extern used with definition
 * 3.15.02   2011-03-15   visehs    ESCAN00049284   DET error occurs in function EnableRouting() and DisableRouting()
 * 3.15.03   2011-04-12   visehs    ESCAN00049366   DET error occurs in function PduR_GwIf_RxIndication()
 *           2011-04-12   visehs    ESCAN00049756   Add PDUR_SOURCE Define at the beginning of the PduR.c file
 *           2011-04-10   visehs    ESCAN00050229   Interface Layer routing with TriggerTransmit FiFo queued routing: Arbitrary value are transmitted
 *           2011-04-28   visehs    ESCAN00050402   Tp buffer deadlock during a multi-frame transport protocol transmission
 *           2011-05-11   visehs    ESCAN00050818   Misra warning: possible truncation at implicit conversion to type "unsigned short"
 * 3.15.04   2011-05-17   visehs    ESCAN00050649   Some functional transport protocol requests (SF) are not routed to the upper Tp layer
 * 3.15.05   2011-05-23   visehs    ESCAN00051055   Compiler Error occurs due to an inconsistent version number
 * 3.16.00   2011-05-23   visehs    ESCAN00051060   Harmonize the Source code with the general PduR generator Dll
 *           2011-05-31   visswa    ESCAN00051144   Implement RxIndication and TriggerTransmit Prototypes as specified in ASR 3.2.1
 *           2011-06-08   visswa    ESCAN00049144   SDU data pointer points to the lower layer Rx data instead of PduR single buffer
 *           2011-06-14   visehs    ESCAN00050286   Use PDUR_GW_COMIF instead of PDUR_GATEWAY_OPERATION
 *           2011-07-01   visswa    ESCAN00051960   AR3-962 MISRA in Generated Code
 *           2011-07-01   visswa    ESCAN00049985   Misra warning: 842 Rule 19.5: Macros shall not be #define'd or #undef'd within a block
 *           2011-07-05   visswa    ESCAN00052008   Resolve PClint warnings
 *           2011-07-13   visms     ESCAN00052180   Remove VPB Support
 *           2011-07-13   visms     ESCAN00052182   Remove CanTp Conversion Support
 *           2011-07-18   visswa    ESCAN00051502   Remove the AUTOSAR Release Version Check
 *           2011-07-19   visswa    ESCAN00052073   Compiler reports a missing semikolon in the file pdur.c
 *           2011-07-22   visswa    ESCAN00052343   Compiler Error occurs due to missing function declaration of SchM_Enter_PduR(...)
 *           2011-07-25   visswa    ESCAN00052261   Remove consistency check of BaseEnv.SizeOfPduIdType
 *           2011-07-28   visehs    ESCAN00050580   N:1 Routings under certain conditions
 *           2011-07-28   visswa    ESCAN00052333   TP Routing buffer remains locked in case of a failed Tp transmission request
 *           2011-07-28   visswa    ESCAN00052434   TP Routing buffer remains locked after MostTp routing
 *           2011-08-16   visswa    ESCAN00052191   Remove unused includes in PduR.c
 * 3.16.01   2011-09-26   visehs    ESCAN00053818   Compile error: CddDobt_Transmit: undeclared identifier
 *           2011-09-26   visehs    ESCAN00053867   Made the  PduR_MultiTp_ProvideTxBuffer and PduR_MultiTp_TxConfirmation more robust
 * 3.16.02   2011-10-28   visehs    ESCAN00054565   Compiler error: 'retVal' : undeclared identifier in function PduR_MultiTp_TxConfirmation
 * 3.17.00   2011-10-24   visswa    ESCAN00053254   AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
 *           2011-10-26   visswa    ESCAN00053259   AR3-2069: Remove non-SchM code for critical section handling
 *           2011-11-03   visswa    ESCAN00054623   [ASR3] Incorrect memory mapping of PduR internal function declarations
 *           2011-11-03   visswa    ESCAN00054630   [ASR3] Incorrect mapping of PduR global data into memory section VAR_NOINIT_UNSPECIFIED
 *           2011-11-28   visehs    ESCAN00052155   Compiler warning: "condition is always true" (The fixed functions are generated since version 3.15.00)
 * 3.18.00   2012-03-23   visehs    ESCAN00057366   AR3-2383: DCM receive data must not be corrupted.
 *           2012-03-23   visehs    ESCAN00060357   Tp Gateway use case: Changed return value for the initial Tp buffer request due to optimization reasons
 * 3.19.00   2012-08-08   visms     ESCAN00060604   AR3-2457: Dynamic DLC with TriggerTransmit based Communication Interfaces
 * 3.20.00   2012-10-25   visehs    ESCAN00062517   Tp Gateway use case: Changed return value for the initial Tp buffer request for all use cases due to optimization reasons
 * 3.21.00   2013-02-05   visehs    ESCAN00061005   AR3-2378: Implement AMD timemeasurement support
 *           2013-02-05   visehs    ESCAN00064680   AR3-2509: Support exclusive n:1 Routing Diagnose Requests from CanTp/DoIp/CDD to <Lo>Tp switchable via RoutingPathGroup
 *           2013-03-20   visehs    ESCAN00066042   Make the Enable-,DisableRouting APIs more robust
 * 3.21.01   2013-03-20   visehs    ESCAN00066178   Compiler error: Undefined symbol PduR_GetState()
 * 3.21.02   2013-10-02   visehs    ESCAN00069955   Memory could be overwritten by interface gateway routings with a TT- FIFO with queue depth > 1
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */
/* PRQA S 0488 EOF *//* MD_PduR_0488 */
/* PRQA S 0489 EOF *//* MD_PduR_0489 */
/* PRQA S 2006 EOF *//* MD_MSR_14.7 */
/* PRQA S 3109 EOF *//* MD_MSR_19.4 */
/* PRQA S 3453 EOF *//* MD_MSR_19.7 */
/*lint -emacro(731, PduR_Det_Assert*) *//* Boolean argument required by assertion macro implementation. No change possible. */
/*lint -esym(750, PDUR_SOURCE) *//* Identification macro of source file. Required due to Vector coding rules. */
/*lint -estring(766, *Memmap.h) *//* The memory abstraction concept uses includes of MemMap.h at any place in the source code. This is required by AUTOSAR. */
/*lint -emacro(960, PduR_Det_Assert*) *//* Null statement caused by assertion macro implementation. Accepted due to code readability */
/*lint -esym(960, 19.6) *//* RULE 19.6: The memory abstraction concept is based on section name redefinition. This is required by AUTOSAR. */
/*lint -esym(960, 8.7) *//* RULE 8.7: RULE 8.7: Declaration in non-block scope due to generic function pointer table implementation */
/*lint -esym(961, 19.7) *//* RULE 19.7: Function like macros are used to increase runtime efficiency and the readability of code */
/* *INDENT-ON* */

#define PDUR_SOURCE
/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "PduR.h"

#define GW_ASRPDUR_REQ_VERSION            (0x0321u)
#define GW_ASRPDUR_REQ_RELEASE_VERSION            (0x02u)
#define GW_ASRPDUR_REQ_DLL_IMPLEMENT      (0x14u)

/*---------------------------------------- DCM import -------------------------------------------------------------*/
#if(PDUR_DCM_SUPPORT == STD_ON)
# include "PduR_Dcm.h"
# include "Dcm_Cbk.h"
#endif

#if ( PDUR_DEV_ERROR_DETECT == STD_ON )
/* *INDENT-OFF* */
/*lint -save -e537 *//* Repeated include required for usage of DET module without PduR */
#  include "Det.h"
/*lint -restore */
/* *INDENT-ON* */
#endif

#if(PDUR_PROD_ERROR_DETECT == STD_ON)
# include "Dem.h"
#endif
#include "SchM_PduR.h"
#if (!defined(V_SUPPRESS_EXTENDED_VERSION_CHECK))
# include "v_ver.h"
#endif
#if((!defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)) || (PDUR_CRC_CHECK == STD_ON))
# include "EcuM_Cbk.h"
#endif

/*---------------------------------------- CDDDOBT import -------------------------------------------------------------*/
# if(PDUR_CDDDOBT_SUPPORT == STD_ON)
#  include "PduR_CanTp.h"
#  include "CddDobt_PduR_Cbk.h"
# endif

#if(PDUR_AMD_RUNTIME_MEASUREMENT == STD_ON)
# include "AmdRtm.h"
#endif

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
#if(GW_ASRPDUR_VERSION != GW_ASRPDUR_REQ_VERSION)
# error "PduR.c: PduR Source and Header files are inconsistent!"
#endif
#if(GW_ASRPDUR_RELEASE_VERSION != GW_ASRPDUR_REQ_RELEASE_VERSION)
# error "PduR.c: PduR Source and Header files are inconsistent!"
#endif
#if(GW_ASRPDUR_DLL_IMPLEMENTATION != GW_ASRPDUR_REQ_DLL_IMPLEMENT)
# error "PduR.c: The GENy DLL Version is not compatible to the Embedded Sources"
#endif

/*********************************************************************************************************************/
/* Consistency Checks and Compatibility                                                                              */
/*********************************************************************************************************************/
# if(PDUR_DCM_SUPPORT == STD_ON)
#  if !defined(DCM_PDUR_PERIODIC_TX_TYPE2_ENABLED)
#   define DCM_PDUR_PERIODIC_TX_TYPE2_ENABLED     STD_OFF
#  endif
# endif

#if defined ( COMSTACKTYPE_VENDOR_ID )
# if ( COMSTACKTYPE_VENDOR_ID == PDUR_VENDOR_ID )
#  if ( COMSTACKTYPE_SW_MAJOR_VERSION < 3u )
#   error "PduR: Incompatible COMSTACKTYPE_SW_MAJOR_VERSION with this PduR Implementation!"
#  else
#   if ( COMSTACKTYPE_SW_MAJOR_VERSION == 3u )
#    if ( COMSTACKTYPE_SW_MINOR_VERSION < 5u )
#     error "PduR: Incompatible COMSTACKTYPE_SW_MINOR_VERSION with this PduR Implementation!"
#    else
#     if ( COMSTACKTYPE_SW_MINOR_VERSION == 5u )
#      if ( COMSTACKTYPE_SW_PATCH_VERSION < 0u )
#       error "PduR: Incompatible COMSTACKTYPE_SW_PATCH_VERSION with this PduR Implementation!"
#      endif
#     endif
#    endif
#   endif
#  endif
# endif /* ( COMSTACKTYPE_VENDOR_ID == COM_VENDOR_ID ) */
#endif /* ( COMSTACKTYPE_VENDOR_ID ) */

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/
#if(PDUR_CONFIG_VARIANT == PDUR_CFGVAR_POSTBUILDTIME)
# define PDUR_MAGICNUMBER_FINAL               ((uint16)0xcafeu)
#endif /* (PDUR_CONFIG_VARIANT == PDUR_CFGVAR_POSTBUILDTIME) */
                                           /*lint -esym(750, PDUR_GWIF_NOINITVALUE) *//* Accept unused local macro symbol due to condition complexity */
#define PDUR_GWIF_NOINITVALUE                 ((uint16)0xFFFFu)
# if(PDUR_GW_TP == STD_ON)
                                             /*lint -esym(750, PDUR_GWTP_NOBUFFERFOUND) *//* Accept unused local macro symbol due to condition complexity */
#  define PDUR_GWTP_NOBUFFERFOUND              ((uint16)0xFFFFu)
# endif

#if (PDUR_PROD_ERROR_DETECT == STD_ON)
# if(PDUR_LIBRARY_SUPPORT == STD_ON)
#  define PDUR_PDUR_E_INIT_FAILED             PduR_DemError_InitFailed
#  define PDUR_PDUR_E_PDU_INSTANCE_LOST       PduR_DemError_InstanceLost
# else
#  if defined (Dem_PDUR_E_INIT_FAILED)
#   define PDUR_E_INIT_FAILED                  Dem_PDUR_E_INIT_FAILED
#  endif
#  if defined (Dem_PDUR_E_PDU_INSTANCE_LOST)
#   define PDUR_E_PDU_INSTANCE_LOST            Dem_PDUR_E_PDU_INSTANCE_LOST
#  endif
#  define PDUR_PDUR_E_INIT_FAILED              PDUR_E_INIT_FAILED
#  define PDUR_PDUR_E_PDU_INSTANCE_LOST        PDUR_E_PDU_INSTANCE_LOST
# endif /* (PDUR_LIBRARY_SUPPORT == STD_ON) */
#endif /* (PDUR_PROD_ERROR_DETECT == STD_ON) */

#if (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON)
# define PduR_GetNumberOfRoutingGroupDestPdusCnt() (pdur_NumberOfRoutingGroupDestPdus)
#endif

/* *INDENT-OFF* */
/*lint -esym(750, PduR_GwGet*) *//* Accept unused local macro symbol due to condition complexity */
/*lint -esym(750, PduR_GwSet*) *//* Accept unused local macro symbol due to condition complexity */
/* *INDENT-ON* */
#if (PDUR_USE_DYNAMIC_DLC == STD_ON)
# define PduR_GwGetInitialPduLength()         (pQI->sduLength)
# define PduR_GwGetPduLength(a)               ((PduLengthType)(a)[0])
# define PduR_GwSetPduLength(a, v)            ((a)[0] = (uint8)(v))
# define PduR_GwGetPduBufferStartPtr(a)       (&(a)[1])
# define PduR_GwGetBufferElementSize()        (PduR_GwIf_BufferIdxType) (pQI->sduLength + 1)
# define PduR_GwGetRxIndicationSduLength()    (PduInfoPtr->SduLength)
#else
# define PduR_GwGetInitialPduLength()         (pQI->sduLength)
# define PduR_GwGetPduLength(a)               (pQI->sduLength)
# define PduR_GwSetPduLength(a, v)
# define PduR_GwGetPduBufferStartPtr(a)       (a)
# define PduR_GwGetBufferElementSize()        ((PduR_GwIf_BufferIdxType) pQI->sduLength)
# define PduR_GwGetRxIndicationSduLength()    ((PduLengthType) pQI->sduLength)
#endif /* (PDUR_USE_DYNAMIC_DLC == STD_ON) */

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/
#define PduR_Core_SetState(state) (pdur_Core_State = (state))

#if (PDUR_PROD_ERROR_DETECT == STD_ON)
# define PduR_Dem_ReportErrorStatus(EventId, EventStatus)  (void)Dem_ReportErrorStatus((EventId), (EventStatus))
#else
# define PduR_Dem_ReportErrorStatus(EventId, EventStatus)
#endif /* (PDUR_PROD_ERROR_DETECT == STD_ON) */

/* *INDENT-OFF* */
/*lint -esym(750, PduR_Core_Mem*) *//* Accept unused local macro symbol due to condition complexity */
/* *INDENT-ON* */
#if(PDUR_VSTDLIB_MEM_API == STD_ON)
# define PduR_Core_MemCpyRamToRam(d, s, l)      VStdMemCpyRamToRam((d), (s), (l))
# define PduR_Core_MemCpyRomToRam(d, s, l)      VStdMemCpyRomToRam((d), (s), (l))
# define PduR_Core_MemClr(d, l)                 VStdMemClr((d), (l))
# define PduR_Core_MemSet(d, v, l)              VStdMemSet((d), (v), (uint16)(l))
#else
# define PduR_Core_MemCpy(pDest, pSrc, length)\
                            {\
                              uint16_least cnt = (uint16_least)(length);\
                              while(cnt > (uint16_least)0x00)\
                              {\
                                cnt--;\
                                (pDest)[cnt] = (pSrc)[cnt];\
                              }\
                            }
# define PduR_Core_MemSet(pDest, value, length)\
                            {\
                              uint16_least cnt = (uint16_least)(length);\
                              while(cnt > (uint16_least)0x00)\
                              {\
                                cnt--;\
                                (pDest)[cnt] = (uint8)(value);\
                              }\
                            }
# define PduR_Core_MemCpyRamToRam(d, s, l)      PduR_Core_MemCpy((d), (s), (l))
# define PduR_Core_MemCpyRomToRam(d, s, l)      PduR_Core_MemCpy((d), (s), (l))
# define PduR_Core_MemClr(d, l)                 PduR_Core_MemSet((d), 0x00, (l))
#endif /* (PDUR_VSTDLIB_MEM_API == STD_ON) */

/* *INDENT-OFF* */
/*lint -esym(750, PduR_Core_EnterCriticalArea) *//* Accept unused local macro symbol due to condition complexity */
/*lint -esym(750, PduR_Core_LeaveCriticalArea) *//* Accept unused local macro symbol due to condition complexity */
/* *INDENT-ON* */
#define PduR_Core_EnterCriticalArea()           SchM_Enter_PduR(PDUR_EXCLUSIVE_AREA_0)
#define PduR_Core_LeaveCriticalArea()           SchM_Exit_PduR(PDUR_EXCLUSIVE_AREA_0)

# if(PDUR_GW_TP == STD_ON)
#  if(PDUR_GWTP_2PROVIDERXBUFFER_CALLS == STD_ON)
#   define PduR_GetGwTpBufferEndIndex()         pBA->bufferRxEndIdx
#  else
#   define PduR_GetGwTpBufferEndIndex()         pBI->bufferEndIdx
#  endif
# endif

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/*======================================== PDUR_START_SEC_CODE ========================================*/
#define PDUR_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */

#  if(PDUR_GW_TP == STD_ON)
/**********************************************************************************************************************
  PduR_GwTpResetRouting
**********************************************************************************************************************/
/** \brief    This function will be called by the PduR GwTp to reset a TP routing.
    \param    GwTpRxPduId       ID of the GwTp I-PDU that will be received.
    \return   none
    \context  The function can be called on interrupt and task level and has not to be interrupted by other
              PduR_GwTpResetRouting calls for the same GwTpRxPduId.
    \note     The function is called by the PduR GwTp.
**********************************************************************************************************************/
STATIC FUNC(void, PDUR_CODE) PduR_GwTpResetRouting(PduIdType GwTpRxPduId);

/**********************************************************************************************************************
  PduR_GwTpRouteAndTransmit
**********************************************************************************************************************/
/** \brief    The function is called by the PduR GwTp to route SF to Dcm and trigger the transmission on <Lo>TPs.
    \param    GwTpRxPduId                     ID of the GwTp I-PDU that will be transmitted.
    \param    pBA                             Pointer to the Buffer Administration structure.
    \param    pSrcPduInfo                     Pointer to the source buffer and the number of bytes to copy.
    \return   none
    \pre      PduR_Init() is executed successfully and the PDU Router is in PDUR_ONLINE state.
    \context  The function can be called on interrupt and task level and has not to be interrupted by other
              PduR_GwTpRouteAndTransmit calls for the same GwTpTxPduId.
    \note     The function is called by the PduR GwTp.
**********************************************************************************************************************/
STATIC FUNC(void, PDUR_CODE) PduR_GwTpRouteAndTransmit(PduIdType GwTpRxPduId, PduR_GwTp_BufferAdminTypePtr pBA,
                                                       PduInfoType pSrcPduInfo);
#  endif /* (PDUR_GW_TP == STD_ON) */


#if (PDUR_CONFIG_VARIANT == PDUR_CFGVAR_POSTBUILDTIME)
/**********************************************************************************************************************
  PduR_Core_CheckPbDataConsistency
**********************************************************************************************************************/
/** \brief    The function is verifies the configuration data.
    \return   boolean
              TRUE          The Configuration is valid.
              FALSE         The Configuration is invalid.
    \note     The function is called by the PduR.
**********************************************************************************************************************/
STATIC FUNC(boolean, PDUR_CODE) PduR_Core_CheckPbDataConsistency(void);
#endif


#define PDUR_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== PDUR_STOP_SEC_CODE ========================================*/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/*======================================== PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED ========================================*/
#define PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */
#if (PDUR_SELECTABLE_INIT_POINTER == STD_ON)
P2CONST(PduR_PBConfigType, PDUR_VAR_ZERO_INIT, PDUR_PBCFG) pdur_Core_PBConfigPtr = NULL_PTR;
#endif
#define PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED ========================================*/

/*======================================== PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED ========================================*/
#define PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */
VAR(PduR_Core_StateType, PDUR_VAR_ZERO_INIT) pdur_Core_State = PDUR_UNINIT;
#define PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED ========================================*/

/*======================================== PDUR_START_SEC_VAR_NOINIT_BOOLEAN ========================================*/
#define PDUR_START_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */
# if(PDUR_CDDDOBT_SUPPORT == STD_ON)
VAR(boolean, PDUR_VAR_NOINIT) pdur_CddDobtState = FALSE;
# endif
#define PDUR_STOP_SEC_VAR_NOINIT_BOOLEAN
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== PDUR_STOP_SEC_VAR_NOINIT_BOOLEAN ========================================*/

/*======================================== PDUR_START_SEC_CONST_UNSPECIFIED ========================================*/
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */
#if((PDUR_PROD_ERROR_DETECT == STD_ON) && (PDUR_LIBRARY_SUPPORT == STD_ON))
/**********************************************************************************************************************
| NAME:             PduR_DemError...
| DESCRIPTION:      Link time error codes of DEM
**********************************************************************************************************************/
extern CONST(Dem_EventIdType, PDUR_CONST) PduR_DemError_InitFailed;
extern CONST(Dem_EventIdType, PDUR_CONST) PduR_DemError_InstanceLost;
#endif /* ((PDUR_PROD_ERROR_DETECT == STD_ON) && (PDUR_LIBRARY_SUPPORT == STD_ON)) */

#if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
# if(PDUR_LIBRARY_SUPPORT == STD_ON)
CONST(uint32, PDUR_CONST) GW_ASRPDUR_LIB_SYMBOL = GW_ASRPDUR_LIB_VERSION;
# endif
#endif
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== PDUR_STOP_SEC_CONST_UNSPECIFIED ========================================*/

/*======================================== PDUR_START_SEC_CODE ========================================*/
#define PDUR_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */
/**********************************************************************************************************************
  GLOBAL AND LOCAL FUNCTIONS
**********************************************************************************************************************/

#if(PDUR_VERSION_INFO_API == STD_ON)
FUNC(void, PDUR_CODE) PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PDUR_APPL_DATA) versioninfo)
{
  PduR_Det_AssertReturnFunc(NULL_PTR != versioninfo, PDUR_FCT_VERSIONINFO, PDUR_E_DATA_PTR_INVALID);

  versioninfo->vendorID = (uint16) PDUR_VENDOR_ID;
  versioninfo->moduleID = (uint8) PDUR_MODULE_ID;
  versioninfo->instanceID = (uint8) 0x00u;
  versioninfo->sw_major_version = (uint8) PDUR_SW_MAJOR_VERSION;
  versioninfo->sw_minor_version = (uint8) PDUR_SW_MINOR_VERSION;
  versioninfo->sw_patch_version = (uint8) PDUR_SW_PATCH_VERSION;

}                               /* End of PduR_GetVersionInfo() */
#endif


#if(PDUR_CONFIG_VARIANT == PDUR_CFGVAR_POSTBUILDTIME)
FUNC(uint32, PDUR_CODE) PduR_GetConfigurationId(void)
{
  PduR_Det_AssertReturnFuncValue(PduR_Core_GetState() == PDUR_ONLINE, PDUR_FCT_CONFIGURATIONID, PDUR_E_INVALID_REQUEST,
                                 0);
  return PduR_GetCfgElement(PbConfigId);

}                               /* End of PduR_GetConfigurationId() */
#endif

/**********************************************************************************************************************
  PduR Initialization
**********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_PBCFG) ConfigPtr)
{
  /* ConfVariant 1, 2 do not use the ConfigPtr. This might lead to a compiler warning which can be ignored. */
  PduR_Det_AssertReturnFunc((PduR_Core_GetState() == PDUR_UNINIT), PDUR_FCT_INIT, PDUR_E_INVALID_REQUEST);

#if(PDUR_SELECTABLE_INIT_POINTER == STD_ON)
  pdur_Core_PBConfigPtr = ConfigPtr;
#else
# if (PDUR_USE_DUMMY_STATEMENT == STD_ON)
  ConfigPtr = ConfigPtr;        /* PRQA S 3199 *//* MD_PduR_3199 *//*lint -e438 */
# endif
#endif

#if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
  /* The check tests if major and minor version of generator and library are valid */
  if (((PduR_GetCfgElement(GeneratorVersion) & (uint32) 0x00FFFF00u) !=
       (((uint32) GW_ASRPDUR_GENTOOL_GENY_MAJOR_VERSION << 16u) |
        ((uint32) GW_ASRPDUR_GENTOOL_GENY_MINOR_VERSION << 8u)))
# if defined ( GW_ASRPDUR_GENTOOL_GENY_PATCH_VERSION )
#  if ( GW_ASRPDUR_GENTOOL_GENY_PATCH_VERSION != 0)
      || ((PduR_GetCfgElement(GeneratorVersion) & (uint32) 0x000000FFu) <
          (uint32) GW_ASRPDUR_GENTOOL_GENY_PATCH_VERSION)
#  endif
# endif
    )
  {
    EcuM_GeneratorCompatibilityError((uint16) PDUR_MODULE_ID, (uint8) 0u);
    /* Abort initialization as generator is not compatible */
    return;
  }
#  if(PDUR_GW_COMIF == STD_ON)
  if (((PduR_GetCfgElement(GwGeneratorVersion) & (uint32) 0x00FFFF00u) !=
       (((uint32) GW_ASRPDURGW_GENTOOL_GENY_MAJOR_VERSION << 16u) |
        ((uint32) GW_ASRPDURGW_GENTOOL_GENY_MINOR_VERSION << 8u)))
#   if defined ( GW_ASRPDURGW_GENTOOL_GENY_PATCH_VERSION )
#    if ( GW_ASRPDURGW_GENTOOL_GENY_PATCH_VERSION != 0)
      || ((PduR_GetCfgElement(GwGeneratorVersion) & (uint32) 0x000000FFu) <
          (uint32) GW_ASRPDURGW_GENTOOL_GENY_PATCH_VERSION)
#    endif
#   endif
    )
  {
    EcuM_GeneratorCompatibilityError((uint16) PDUR_MODULE_ID, (uint8) 0u);
    /* Abort initialization as generator is not compatible */
    return;
  }
#  endif
#   if(PDUR_GW_TP == STD_ON)
  if (((PduR_GetCfgElement(GwTpGeneratorVersion) & (uint32) 0x00FFFF00u) !=
       (((uint32) GW_ASRPDURGWTP_GENTOOL_GENY_MAJOR_VERSION << 16u) |
        ((uint32) GW_ASRPDURGWTP_GENTOOL_GENY_MINOR_VERSION << 8u)))
#    if defined ( GW_ASRPDURGWTP_GENTOOL_GENY_PATCH_VERSION )
#     if ( GW_ASRPDURGWTP_GENTOOL_GENY_PATCH_VERSION != 0)
      || ((PduR_GetCfgElement(GwTpGeneratorVersion) & (uint32) 0x000000FFu) <
          (uint32) GW_ASRPDURGWTP_GENTOOL_GENY_PATCH_VERSION)
#     endif
#    endif
    )
  {
    EcuM_GeneratorCompatibilityError((uint16) PDUR_MODULE_ID, (uint8) 0u);
    /* Abort initialization as generator is not compatible */
    return;
  }
#   endif
#endif
#if(PDUR_CRC_CHECK == STD_ON)
  if (PduR_GetCfgElement(PrecompileCRC) != PDUR_PRECOMPILE_CRC)
  {
    EcuM_GeneratorCompatibilityError((uint16) PDUR_MODULE_ID, (uint8) 0u);
    /* Abort initialization as current configuration is not compatible with the pre-compile configuration */
    return;
  }
  if (PduR_GetCfgElement(LinktimeCRC) != PduR_LinktimeCRC)
  {
    EcuM_GeneratorCompatibilityError((uint16) PDUR_MODULE_ID, (uint8) 0u);
    /* Abort initialization as current configuration is not compatible with the link-time configuration */
    return;
  }
#endif


#if(PDUR_CONFIG_VARIANT == PDUR_CFGVAR_POSTBUILDTIME)
  if (FALSE == PduR_Core_CheckPbDataConsistency())
  {
    PduR_Core_SetState(PDUR_UNINIT);
    PduR_Det_ReportError(PDUR_FCT_INIT, PDUR_E_CONFIG_PTR_INVALID);
    PduR_Dem_ReportErrorStatus(PDUR_PDUR_E_INIT_FAILED, DEM_EVENT_STATUS_FAILED);
    return;
  }
#endif /* (PDUR_CONFIG_VARIANT == PDUR_CFGVAR_POSTBUILDTIME) */

#if((PDUR_CANTP_SUPPORT == STD_ON) && (PDUR_CANTP_2PROVIDERXBUFFER_CALLS == STD_ON))
  /* PRQA S 0850 MEMCLR_0850 *//* MD_MSR_19.8 */
  /* PRQA S 0310 MEMCLR_0310 *//* MD_PduR_0310 */
  PduR_Core_MemClr((P2VAR(uint8, TYPEDEF, PDUR_VAR_NOINIT)) pdur_CanTpProvide2RxBufferCallsWrapper,
                   (uint16) sizeof(PduR_Provide2RxBufferCallsWrapperType) * PduR_GetCfgElement(RxCanTpMaxCnt));
  /* PRQA L:MEMCLR_0310 */
  /* PRQA L:MEMCLR_0850 */
#endif
#if((PDUR_FRTP_SUPPORT == STD_ON) && (PDUR_FRTP_2PROVIDERXBUFFER_CALLS == STD_ON))
  /* PRQA S 0850 MEMCLR_0850 *//* MD_MSR_19.8 */
  /* PRQA S 0310 MEMCLR_0310 *//* MD_PduR_0310 */
  PduR_Core_MemClr((P2VAR(uint8, TYPEDEF, PDUR_VAR_NOINIT)) pdur_FrTpProvide2RxBufferCallsWrapper,
                   (uint16) sizeof(PduR_Provide2RxBufferCallsWrapperType) * PduR_GetCfgElement(RxFrTpMaxCnt));
  /* PRQA L:MEMCLR_0310 */
  /* PRQA L:MEMCLR_0850 */
#endif
#if((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
  {
    sint16_least iRr;
    for (iRr = ((sint16_least) PduR_GetCfgElement(IfRoutingTxInfoCnt)) - 1; iRr >= 0; iRr--)
    {
      PduR_GwIf_TxPduRoutingITypePtr pQI = &PduR_GetCfgElement(IfRoutingTxInfo)[iRr];

      if ((PDUR_GWIF_SINGLEBUFFER == pQI->bufferType)
# if(PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
          || (PDUR_GWIF_TT_FIFO == pQI->bufferType)
# endif
        )
      {
        /* Buffer initialization */
        PduR_Det_Assert(pQI->initValueStartIdx != PDUR_GWIF_NOINITVALUE, PDUR_FCT_INIT, PDUR_E_INVALID_CFG_DATA);

        /* PRQA S 0850 MEMCPY_0850 *//* MD_MSR_19.8 */
        /* PRQA S 0310 MEMCPY_0310 *//* MD_PduR_0310 */
# if (PDUR_USE_DYNAMIC_DLC == STD_ON)
        pdur_Core_GwBuffer[pQI->bufferStartIdx] = pQI->sduLength;
        PduR_Core_MemCpyRomToRam(&pdur_Core_GwBuffer[pQI->bufferStartIdx + 1],
                                 &PduR_GetCfgElement(IfRoutingInitValues)[pQI->initValueStartIdx], pQI->sduLength);
# else
        PduR_Core_MemCpyRomToRam(&pdur_Core_GwBuffer[pQI->bufferStartIdx],
                                 &PduR_GetCfgElement(IfRoutingInitValues)[pQI->initValueStartIdx], pQI->sduLength);
# endif
        /* PRQA L:MEMCPY_0310 */
        /* PRQA L:MEMCPY_0850 */
      }
    }
  }
#endif


#if(PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  /* Initialize the queue administration - according to PLATFORM056 FALSE is defined to (boolean)0 */
  /* PRQA S 0850 MEMCLR_0850 *//* MD_MSR_19.8 */
  /* PRQA S 0310 MEMCLR_0310 *//* MD_PduR_0310 */
  PduR_Core_MemClr((P2VAR(uint8, TYPEDEF, PDUR_VAR_NOINIT)) pdur_GwIf_QueueAdmin,
                   (uint16) sizeof(PduR_GwIf_QueueAdminType) * PduR_GetCfgElement(IfRoutingQueuedTxPduCnt));
  /* PRQA L:MEMCLR_0310 */
  /* PRQA L:MEMCLR_0850 */
#endif
# if(PDUR_GW_TP == STD_ON)
  {
    sint16_least iBuffer;
    P2VAR(uint8, AUTOMATIC, PDUR_VAR) pBufferInfoStart;
    pBufferInfoStart = &pdur_Core_GwBuffer[PduR_GetCfgElement(TpRoutingBufferRefOffset)];

    /* Initialize Routing Relations */
    /* PRQA S 0850 MEMSET_850 *//* MD_MSR_19.8 */
    PduR_Core_MemSet(pBufferInfoStart, PDUR_GWTP_ROUTING_IDLE,
                     sizeof(uint8) * PduR_GetCfgElement(TpRoutingRelationCnt));
    /* PRQA L:MEMSET_850 */

    /* Initialize Buffer Elements */
    for (iBuffer = ((sint16_least) PduR_GetCfgElement(TpRoutingBufferCnt)) - 1; iBuffer >= 0; iBuffer--)
    {
      pdur_GwTp_BufferAdmin[iBuffer].rrId = PDUR_GWTP_BUFFER_IDLE;
    }
  }
# endif

# if(PDUR_CDDDOBT_SUPPORT == STD_ON)
  pdur_CddDobtState = FALSE;
# endif
  PduR_Core_SetState(PDUR_ONLINE);
#if(PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON)
  {
    /* PRQA S 0850 MEMCLR_0850 *//* MD_MSR_19.8 */
    /* PRQA S 0310 MEMCLR_0310 *//* MD_PduR_0310 */
    PduR_Core_MemClr((P2VAR(PduR_RoutingPathGroupIdType, TYPEDEF, PDUR_VAR_NOINIT)) pdur_DestPduStateCnt,
                     (PduR_RoutingPathGroupIdType) sizeof(PduR_RoutingPathGroupIdType) *
                     (PduR_GetNumberOfRoutingGroupDestPdusCnt()));
    /* PRQA L:MEMCLR_0310 */
    /* PRQA L:MEMCLR_0850 */
    /* The first index has to be set differently to 0. The index contains all DestPduReferences which are not assigned to a PduRRoutingPathGroup */
    pdur_DestPduStateCnt[0] = 1;
    {
      sint16_least siRPGIdx;
      for (siRPGIdx = ((sint16_least) PduR_GetCfgElement(RoutingPathGroupCnt)) - 1; siRPGIdx >= 0; siRPGIdx--)
      {
        pdur_RoutingPathGroupState[siRPGIdx] = FALSE;   /*set true after init of Acitve Routing Path Count */
        if (0 != PduR_GetCfgElement(RoutingPathGroupStateInit)[siRPGIdx])
        {
          PduR_EnableRouting((PduR_RoutingPathGroupIdType) siRPGIdx);
        }
      }
    }
  }
#endif

}                               /* End of PduR_Init() */

#if(PDUR_CONFIG_VARIANT == PDUR_CFGVAR_POSTBUILDTIME)
STATIC FUNC(boolean, PDUR_CODE) PduR_Core_CheckPbDataConsistency(void)
{
  boolean retVal = TRUE;
  if (NULL_PTR != pdur_Core_PBConfigPtr)
  {
    if (PduR_GetCfgElement(FinalMagicNumber) != PDUR_MAGICNUMBER_FINAL)
    {
      retVal = FALSE;
    }
# if(PDUR_CANIF_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(RxCanIf2Up)[PduR_GetCfgElement(RxCanIf2UpCnt)].destPduId != PDUR_PORT_CANIF)
    {
      retVal = FALSE;
    }
    if (PduR_GetCfgElement(TxCanIf2Up)[PduR_GetCfgElement(TxCanIf2UpCnt)].destPduId != PDUR_PORT_CANIF)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_MOSTIF_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(RxMostIf2Up)[PduR_GetCfgElement(RxMostIf2UpCnt)].destPduId != PDUR_PORT_MOSTIF)
    {
      retVal = FALSE;
    }
    if (PduR_GetCfgElement(TxMostIf2Up)[PduR_GetCfgElement(TxMostIf2UpCnt)].destPduId != PDUR_PORT_MOSTIF)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_FRIF_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(RxFrIf2Up)[PduR_GetCfgElement(RxFrIf2UpCnt)].destPduId != PDUR_PORT_FRIF)
    {
      retVal = FALSE;
    }
    if (PduR_GetCfgElement(TxFrIf2Up)[PduR_GetCfgElement(TxFrIf2UpCnt)].destPduId != PDUR_PORT_FRIF)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_LINIF_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(RxLinIf2Up)[PduR_GetCfgElement(RxLinIf2UpCnt)].destPduId != PDUR_PORT_LINIF)
    {
      retVal = FALSE;
    }
    if (PduR_GetCfgElement(TxLinIf2Up)[PduR_GetCfgElement(TxLinIf2UpCnt)].destPduId != PDUR_PORT_LINIF)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_CANTP_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(RxCanTp2Up)[PduR_GetCfgElement(RxCanTp2UpCnt)].destPduId != PDUR_PORT_CANTP)
    {
      retVal = FALSE;
    }
    if (PduR_GetCfgElement(TxCanTp2Up)[PduR_GetCfgElement(TxCanTp2UpCnt)].destPduId != PDUR_PORT_CANTP)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_LINTP_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(RxLinTp2Up)[PduR_GetCfgElement(RxLinTp2UpCnt)].destPduId != PDUR_PORT_LINTP)
    {
      retVal = FALSE;
    }
    if (PduR_GetCfgElement(TxLinTp2Up)[PduR_GetCfgElement(TxLinTp2UpCnt)].destPduId != PDUR_PORT_LINTP)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_SOAD_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(RxSoAdTp2Up)[PduR_GetCfgElement(RxSoAdTp2UpCnt)].destPduId != PDUR_PORT_SOADTP)
    {
      retVal = FALSE;
    }
    if (PduR_GetCfgElement(TxSoAdTp2Up)[PduR_GetCfgElement(TxSoAdTp2UpCnt)].destPduId != PDUR_PORT_SOADTP)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_MOSTTP_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(RxMostTp2Up)[PduR_GetCfgElement(RxMostTp2UpCnt)].destPduId != PDUR_PORT_MOSTTP)
    {
      retVal = FALSE;
    }
    if (PduR_GetCfgElement(TxMostTp2Up)[PduR_GetCfgElement(TxMostTp2UpCnt)].destPduId != PDUR_PORT_MOSTTP)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_FRTP_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(RxFrTp2Up)[PduR_GetCfgElement(RxFrTp2UpCnt)].destPduId != PDUR_PORT_FRTP)
    {
      retVal = FALSE;
    }
    if (PduR_GetCfgElement(TxFrTp2Up)[PduR_GetCfgElement(TxFrTp2UpCnt)].destPduId != PDUR_PORT_FRTP)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_COM_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(TxCom2Lo)[PduR_GetCfgElement(TxCom2LoCnt)].destPduId != PDUR_PORT_COM)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_DCM_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(TxDcm2Lo)[PduR_GetCfgElement(TxDcm2LoCnt)].destPduId != PDUR_PORT_DCM)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_APPLIF_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(TxApplIf2Lo)[PduR_GetCfgElement(TxApplIf2LoCnt)].destPduId != PDUR_PORT_APPLIF)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_APPLTP_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(TxApplTp2Lo)[PduR_GetCfgElement(TxApplTp2LoCnt)].destPduId != PDUR_PORT_APPLTP)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_IPDUM_SUPPORT == STD_ON)
    if (PduR_GetCfgElement(TxIpduM2Lo)[PduR_GetCfgElement(TxIpduM2LoCnt)].destPduId != PDUR_PORT_IPDUM)
    {
      retVal = FALSE;
    }
# endif
# if(PDUR_IPDUM_SUPPORT == STD_ON)
#  if(PDUR_IPDUM_OPTIMIZED == STD_OFF)
    if (PduR_GetCfgElement(TxIpduM2Up)[PduR_GetCfgElement(TxIpduM2UpCnt)].destPduId != PDUR_PORT_IPDUM)
    {
      retVal = FALSE;
    }
    if (PduR_GetCfgElement(RxIpduM2Up)[PduR_GetCfgElement(RxIpduM2UpCnt)].destPduId != PDUR_PORT_IPDUM)
    {
      retVal = FALSE;
    }
#  endif
# endif
  }
  else
  {
    retVal = FALSE;
  }
  return retVal;
}                               /* End of PduR_Core_CheckPbDataConsistency() */
#endif /* (PDUR_CONFIG_VARIANT == PDUR_CFGVAR_POSTBUILDTIME) */

FUNC(void, PDUR_CODE) PduR_InitMemory(void)
{
  PduR_Core_SetState(PDUR_UNINIT);
#if (PDUR_SELECTABLE_INIT_POINTER == STD_ON)
  pdur_Core_PBConfigPtr = NULL_PTR;
#endif
# if(PDUR_CDDDOBT_SUPPORT == STD_ON)
  pdur_CddDobtState = FALSE;
# endif
}                               /* End of PduR_InitMemory() */

/*********************************************************************************************************************/
/* Dcm Tx Confirmation Wrapper                                                                                       */
/*********************************************************************************************************************/
# if(PDUR_DCM_SUPPORT == STD_ON)
FUNC(void, PDUR_CODE) PduR_DcmTxConfirmation(PduIdType DcmTxPduId)
{
  Dcm_TxConfirmation(DcmTxPduId, NTFRSLT_OK);
}
# endif
       /* defined(GW_ASRPDUR_ENABLE_FEATURE_DCM_COMMENT) */

/*********************************************************************************************************************/
/* Interface gateway specific functions                                                                              */
/*********************************************************************************************************************/

# if((PDUR_MULTICAST_FROMIF_SUPPORT == STD_ON) && (PDUR_GW_COMIF == STD_ON))
FUNC(void, PDUR_CODE) PduR_MultiIf_RxIndication(PduIdType multiRxStartId,
                                                P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr)
{
  PduR_Core_MultiDestITypePtr pMRr = &PduR_GetCfgElement(RxMultiIf2Up)[multiRxStartId];

  do
  {
    PduR_Det_AssertReturnFunc(pMRr->destPort != PDUR_PORT_INVALID, PDUR_FCT_MULTIIFRXIND, PDUR_E_INVALID_CFG_DATA);
#  if (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON)
    if (0 != pdur_DestPduStateCnt[pMRr->DestPduCntIndex])
#  endif /* (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON) */
    {
      PduR_UpIfRxIndicationFctPtrType pUpIfRxIndicationFctPtr = PduR_Core_UpIfRxIndication[pMRr->destPort];
      if (pUpIfRxIndicationFctPtr != NULL_PTR)
      {
        pUpIfRxIndicationFctPtr(pMRr->destPduId, PduInfoPtr);
      }
    }
    pMRr++;
  }
  while (pMRr->startId == multiRxStartId);

}                               /* End of PduR_MultiIf_RxIndication() */
# endif
        /* (PDUR_MULTICAST_FROMIF_SUPPORT == STD_ON) */

# if(PDUR_GW_COMIF == STD_ON)

FUNC(void, PDUR_CODE) PduR_GwIf_RxIndication(PduIdType GwIfRxPduId,
                                             P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr)
{
  PduInfoType destPduInfo;
  PduR_Core_TransmitFctPtrType pDestFunc;
  PduR_GwIf_TxPduRoutingITypePtr pQI = &PduR_GetCfgElement(IfRoutingTxInfo)[GwIfRxPduId];
  PduR_Det_AssertReturnFunc(pQI->destPort != PDUR_PORT_INVALID, PDUR_FCT_GWIF_RXIND, PDUR_E_INVALID_CFG_DATA);

#  if(PDUR_CALLOUT_SUPPORT == STD_ON)
  if ((PduR_GwIf_RrIdType) 0x00 != pQI->calloutFuncIdx)
  {
    destPduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
    destPduInfo.SduLength = PduR_GwGetRxIndicationSduLength();
    PduR_Det_AssertReturnFunc(PduR_Core_CalloutFunctions[pQI->calloutFuncIdx] != NULL_PTR, PDUR_FCT_GWIF_RXIND,
                              PDUR_E_INVALID_CFG_DATA);
    if (FALSE == PduR_Core_CalloutFunctions[pQI->calloutFuncIdx] (&destPduInfo))
    {
      return;
    }
  }
#  endif

  /* ----------------------------------------------  No Buffer Routing ---------------------------------------------- */
  if (PDUR_GWIF_NOBUFFER == pQI->bufferType)
  {
    pDestFunc = PduR_Core_TransmitFctPtrTbl[pQI->destPort];
    PduR_Det_AssertReturnFunc(pDestFunc != NULL_PTR, PDUR_FCT_GWIF_RXIND, PDUR_E_INVALID_CFG_DATA);
    destPduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
    destPduInfo.SduLength = PduR_GwGetRxIndicationSduLength();
    (void) pDestFunc(pQI->destPduId, &destPduInfo);
    return;
  }
  {
#  if((PDUR_SB_TX_BUFFER_SUPPORT == STD_ON) || (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON))
    P2VAR(uint8, AUTOMATIC, PDUR_VAR) pQStart;
    uint8 dataLength2copy;
    if (PduR_GwGetRxIndicationSduLength() > PduR_GwGetInitialPduLength())
    {
      dataLength2copy = PduR_GwGetInitialPduLength();
    }
    else
    {
      dataLength2copy = (uint8) PduR_GwGetRxIndicationSduLength();
    }
#  endif
#  if(PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)
/* ---------------------------------------------  Single Buffer Routing --------------------------------------------- */
    if (PDUR_GWIF_SINGLEBUFFER == pQI->bufferType)
    {
      pQStart = &pdur_Core_GwBuffer[pQI->bufferStartIdx];
      PduR_Core_EnterCriticalArea();
      PduR_GwSetPduLength(pQStart, PduR_GwGetInitialPduLength());
      /* PRQA S 0850 MEMCPY_0850 *//* MD_MSR_19.8 */
      PduR_Core_MemCpyRamToRam(PduR_GwGetPduBufferStartPtr(pQStart), PduInfoPtr->SduDataPtr, dataLength2copy);
      /* PRQA L:MEMCPY_0850 */
      PduR_Core_LeaveCriticalArea();
      pDestFunc = PduR_Core_TransmitFctPtrTbl[pQI->destPort];
      PduR_Det_AssertReturnFunc(pDestFunc != NULL_PTR, PDUR_FCT_GWIF_RXIND, PDUR_E_INVALID_CFG_DATA);
      destPduInfo.SduDataPtr = PduR_GwGetPduBufferStartPtr(pQStart);

#   if(PDUR_MOSTIF_SUPPORT == STD_ON)
      if (PDUR_PORT_MOSTIF == pQI->destPort)
      {
        destPduInfo.SduLength = PduR_GwGetInitialPduLength() | (PduLengthType) 0x8000;
      }
      else
#   endif
      {
        destPduInfo.SduLength = PduR_GwGetInitialPduLength();
      }
      (void) pDestFunc(pQI->destPduId, &destPduInfo);
      return;
    }
#  endif
#  if(PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
    {
      PduR_GwIf_QueueAdminTypePtr pQA;
/* --------------------------------------------- D-FiFo Queued Handling ---------------------------------------------*/
      if (PDUR_GWIF_D_FIFO == pQI->bufferType)
      {
        pQA = &pdur_GwIf_QueueAdmin[GwIfRxPduId];

        PduR_Core_EnterCriticalArea();
        if (FALSE == pQA->bTxConfP)
        {
          /* target I-PDU is available - no queuing required */
          pDestFunc = PduR_Core_TransmitFctPtrTbl[pQI->destPort];
          PduR_Det_AssertReturnFunc(pDestFunc != NULL_PTR, PDUR_FCT_GWIF_RXIND, PDUR_E_INVALID_CFG_DATA);
          destPduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
          destPduInfo.SduLength = PduR_GwGetRxIndicationSduLength();
          if (E_NOT_OK != pDestFunc(pQI->destPduId, &destPduInfo))
          {
            pQA->bTxConfP = TRUE;
          }
          else
          {
            PduR_Dem_ReportErrorStatus(PDUR_PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED);
          }
        }
        else
        {
          /* target I-PDU in use - queuing required */
          pQStart = &pdur_Core_GwBuffer[pQI->bufferStartIdx + pQA->wrIdx];
          if (pQA->sduCount < pQI->queueDepth)
          {
            /* queue not full -> add SDU to queue */
            PduR_GwSetPduLength(pQStart, PduR_GwGetRxIndicationSduLength());
            /* PRQA S 0850 MEMCPY_0850 *//* MD_MSR_19.8 */
            PduR_Core_MemCpyRamToRam(PduR_GwGetPduBufferStartPtr(pQStart), PduInfoPtr->SduDataPtr, dataLength2copy);
            /* PRQA L:MEMCPY_0850 */
            pQA->wrIdx += PduR_GwGetBufferElementSize();
            if (pQA->wrIdx >= pQI->queueSize)
            {
              /* Wrap around required */
              pQA->wrIdx = (PduR_GwIf_BufferIdxType) 0x00;
            }
            pQA->sduCount++;
          }
          else
          {
            /* queue full -> flush queue and transmit new SDU */
            pQA->wrIdx = pQA->rdIdx;
            pQA->sduCount = (PduR_GwIf_SduCountType) 0x00;
            PduR_Dem_ReportErrorStatus(PDUR_PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED);

            pDestFunc = PduR_Core_TransmitFctPtrTbl[pQI->destPort];
            PduR_Det_AssertReturnFunc(pDestFunc != NULL_PTR, PDUR_FCT_GWIF_RXIND, PDUR_E_INVALID_CFG_DATA);
            destPduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
            destPduInfo.SduLength = PduR_GwGetRxIndicationSduLength();
            if (E_NOT_OK == pDestFunc(pQI->destPduId, &destPduInfo))
            {
              pQA->bTxConfP = FALSE;
              PduR_Dem_ReportErrorStatus(PDUR_PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED);
            }
          }
        }
        PduR_Core_LeaveCriticalArea();
        return;
      }
/* --------------------------------------------- TT-FiFo Queued Handling --------------------------------------------*/
      if (PDUR_GWIF_TT_FIFO == pQI->bufferType)
      {
        Std_ReturnType funcResult;
        pQA = &pdur_GwIf_QueueAdmin[GwIfRxPduId];

        PduR_Core_EnterCriticalArea();
        if (FALSE == pQA->bTxConfP)
        {
          pQStart = &pdur_Core_GwBuffer[pQI->bufferStartIdx];
          /* target I-PDU is available, queue is empty - SDU can be added to the queue directly (for TT data provision) */
          pDestFunc = PduR_Core_TransmitFctPtrTbl[pQI->destPort];
          PduR_Det_AssertReturnFunc(pDestFunc != NULL_PTR, PDUR_FCT_GWIF_RXIND, PDUR_E_INVALID_CFG_DATA);
          PduR_Det_AssertReturnFunc(pQI->destPort != PDUR_PORT_CANIF, PDUR_FCT_GWIF_RXIND, PDUR_E_INVALID_CFG_DATA);
          destPduInfo.SduDataPtr = PduR_GwGetPduBufferStartPtr(pQStart);
          destPduInfo.SduLength = PduR_GwGetInitialPduLength();
          PduR_GwSetPduLength(pQStart, PduR_GwGetInitialPduLength());
          /* PRQA S 0850 MEMCPY_0850 *//* MD_MSR_19.8 */
          PduR_Core_MemCpyRamToRam(PduR_GwGetPduBufferStartPtr(pQStart), PduInfoPtr->SduDataPtr, dataLength2copy);
          /* PRQA L:MEMCPY_0850 */
          pQA->rdIdx = (PduR_GwIf_BufferIdxType) 0x00;
          pQA->wrIdx = (PduR_GwIf_BufferIdxType) 0x00;
          pQA->sduCount = (PduR_GwIf_SduCountType) 0x00;
          funcResult = pDestFunc(pQI->destPduId, &destPduInfo);
          if ((E_NOT_OK != funcResult)
#   if (PDUR_LINIF_SUPPORT == STD_ON)
              /* LIN IF will always return E_NOT_OK for unconditional frames (see LINIF341) */
              || (pQI->destPort == PDUR_PORT_LINIF)
#   endif
            )
          {
            pQA->bTxConfP = TRUE;
            pQA->sduCount = (PduR_GwIf_SduCountType) 0x01;
            pQA->wrIdx += PduR_GwGetBufferElementSize();
          }
          else
          {
            PduR_Dem_ReportErrorStatus(PDUR_PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED);
          }
        }
        else
        {
          pQStart = &pdur_Core_GwBuffer[pQI->bufferStartIdx + pQA->wrIdx];
          /* target I-PDU in use - queuing required */
          if (pQA->sduCount < pQI->queueDepth)
          {
            /* queue not full -> add SDU to queue */
            PduR_GwSetPduLength(pQStart, PduR_GwGetInitialPduLength());
            /* PRQA S 0850 MEMCPY_0850 *//* MD_MSR_19.8 */
            PduR_Core_MemCpyRamToRam(PduR_GwGetPduBufferStartPtr(pQStart), PduInfoPtr->SduDataPtr, dataLength2copy);
            /* PRQA L:MEMCPY_0850 */
            pQA->wrIdx += PduR_GwGetBufferElementSize();
            if (pQA->wrIdx >= pQI->queueSize)
            {
              /* Wrap around required */
              pQA->wrIdx = (PduR_GwIf_BufferIdxType) 0x00;
            }
            pQA->sduCount++;
          }
          else
          {
            /* queue full -> flush the queue. Add and transmit the new SDU to the first element */
            PduR_Dem_ReportErrorStatus(PDUR_PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED);
            PduR_GwSetPduLength(pQStart, PduR_GwGetInitialPduLength());
            /* PRQA S 0850 MEMCPY_0850 *//* MD_MSR_19.8 */
            PduR_Core_MemCpyRamToRam(PduR_GwGetPduBufferStartPtr(pQStart), PduInfoPtr->SduDataPtr, dataLength2copy);
            /* PRQA L:MEMCPY_0850 */
            pDestFunc = PduR_Core_TransmitFctPtrTbl[pQI->destPort];
            PduR_Det_AssertReturnFunc(pDestFunc != NULL_PTR, PDUR_FCT_GWIF_RXIND, PDUR_E_INVALID_CFG_DATA);
            PduR_Det_AssertReturnFunc(pQI->destPort != PDUR_PORT_CANIF, PDUR_FCT_GWIF_RXIND, PDUR_E_INVALID_CFG_DATA);
            destPduInfo.SduDataPtr = PduR_GwGetPduBufferStartPtr(pQStart);
            destPduInfo.SduLength = PduR_GwGetInitialPduLength();
            pQA->rdIdx = (PduR_GwIf_BufferIdxType) 0x00;
            pQA->wrIdx = (PduR_GwIf_BufferIdxType) 0x00;
            pQA->sduCount = (PduR_GwIf_SduCountType) 0x00;
            funcResult = pDestFunc(pQI->destPduId, &destPduInfo);
            if ((E_NOT_OK != funcResult)
#   if (PDUR_LINIF_SUPPORT == STD_ON)
                /* LIN IF will always return E_NOT_OK for unconditional frames (see LINIF341) */
                || (pQI->destPort == PDUR_PORT_LINIF)
#   endif
              )
            {
              pQA->sduCount = (PduR_GwIf_SduCountType) 0x01;
              pQA->wrIdx += PduR_GwGetBufferElementSize();
            }
            else
            {
              PduR_Dem_ReportErrorStatus(PDUR_PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED);

              pQA->bTxConfP = FALSE;
            }
          }
        }
        PduR_Core_LeaveCriticalArea();
      }
    }
#  endif /* (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
  }
}                               /* End of PduR_GwIf_RxIndication() */

#  if((PDUR_SB_TX_BUFFER_SUPPORT == STD_ON) || (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON))
FUNC(Std_ReturnType, PDUR_CODE) PduR_GwIf_TriggerTransmit(PduIdType GwIfTxPduId,
                                                          CONSTP2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr)
{
  PduR_GwIf_TxPduRoutingITypePtr pQI = &PduR_GetCfgElement(IfRoutingTxInfo)[GwIfTxPduId];

#   if(PDUR_SB_TX_BUFFER_SUPPORT == STD_ON)
  if (PDUR_GWIF_SINGLEBUFFER == pQI->bufferType)
  {
    P2VAR(uint8, AUTOMATIC, PDUR_VAR) pQStart = &pdur_Core_GwBuffer[pQI->bufferStartIdx];
    PduR_Core_EnterCriticalArea();
    PduInfoPtr->SduLength = PduR_GwGetInitialPduLength();
    /* PRQA S 0850 MEMCPY_0850 *//* MD_MSR_19.8 */
    PduR_Core_MemCpyRamToRam(PduInfoPtr->SduDataPtr, PduR_GwGetPduBufferStartPtr(pQStart),
                             PduR_GwGetInitialPduLength());
    /* PRQA L:MEMCPY_0850 */
    PduR_Core_LeaveCriticalArea();
    return E_OK;
  }
#   endif
#   if(PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  if (PDUR_GWIF_TT_FIFO == pQI->bufferType)
  {
    PduR_GwIf_QueueAdminTypePtr pQA = &pdur_GwIf_QueueAdmin[GwIfTxPduId];
    PduR_Core_EnterCriticalArea();
    if (FALSE == pQA->bTxConfP)
    {
      pQA->bTxConfP = TRUE;
      pQA->sduCount = (PduR_GwIf_SduCountType) 0x01;
      pQA->wrIdx += PduR_GwGetBufferElementSize();
      if (pQA->wrIdx >= pQI->queueSize)
      {
        /* Wrap around required */
        pQA->wrIdx = (PduR_GwIf_BufferIdxType) 0x00;
      }
    }
    {
      P2VAR(uint8, AUTOMATIC, PDUR_VAR) pQStart = &pdur_Core_GwBuffer[pQI->bufferStartIdx + pQA->rdIdx];
      PduInfoPtr->SduLength = PduR_GwGetInitialPduLength();
      /* PRQA S 0850 MEMCPY_0850 *//* MD_MSR_19.8 */
      PduR_Core_MemCpyRamToRam(PduInfoPtr->SduDataPtr, PduR_GwGetPduBufferStartPtr(pQStart),
                               PduR_GwGetInitialPduLength());
      /* PRQA L:MEMCPY_0850 */
      PduR_Core_LeaveCriticalArea();
    }
    return E_OK;
  }
#   endif
  /* (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
  PduR_Det_AssertAlways(PDUR_FCT_GWIF_TXTT, PDUR_E_UNEXPECTED_CALL);
  return E_NOT_OK;
}                               /* End of PduR_GwIf_TriggerTransmit() */
#  endif  /* ((PDUR_SB_TX_BUFFER_SUPPORT == STD_ON) || (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)) */

FUNC(void, PDUR_CODE) PduR_GwIf_TxConfirmation(PduIdType GwIfTxPduId)
{
#  if(PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  PduR_GwIf_QueueAdminTypePtr pQA;
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) pQStart;
  PduInfoType destPduInfo;
  PduR_Core_TransmitFctPtrType pDestFunc;
  Std_ReturnType funcResult;
  PduR_GwIf_TxPduRoutingITypePtr pQI = &PduR_GetCfgElement(IfRoutingTxInfo)[GwIfTxPduId];

/* --------------------------------------------- D-FiFo Queued Handling - PDUR259 -----------------------------------*/
  if (PDUR_GWIF_D_FIFO == pQI->bufferType)
  {
    pQA = &pdur_GwIf_QueueAdmin[GwIfTxPduId];
    PduR_Det_AssertReturnFunc(GwIfTxPduId < PduR_GetCfgElement(IfRoutingQueuedTxPduCnt), PDUR_FCT_GWIF_TXCONF,
                              PDUR_E_INVALID_CFG_DATA);

    PduR_Core_EnterCriticalArea();
    if (FALSE != pQA->bTxConfP)
    {
      if ((PduR_GwIf_SduCountType) 0x00 == pQA->sduCount)
      {
        /* Queue is empty now */
        pQA->bTxConfP = FALSE;
      }
      else
      {
        /* Further SDUs are pending, transmit them */
        pQStart = &pdur_Core_GwBuffer[pQI->bufferStartIdx] + pQA->rdIdx;
        pDestFunc = PduR_Core_TransmitFctPtrTbl[pQI->destPort];
        destPduInfo.SduLength = PduR_GwGetPduLength(pQStart);
        do
        {

          destPduInfo.SduDataPtr = PduR_GwGetPduBufferStartPtr(pQStart);
          funcResult = pDestFunc(pQI->destPduId, &destPduInfo);
          /* Remove FiFo entry from queue */
          pQA->rdIdx += PduR_GwGetBufferElementSize();
          if (pQA->rdIdx >= pQI->queueSize)
          {
            /* Wrap around required */
            pQA->rdIdx = (PduR_GwIf_BufferIdxType) 0x00;
          }
          pQA->sduCount--;

          if (E_NOT_OK == funcResult)
          {
            PduR_Dem_ReportErrorStatus(PDUR_PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED);
          }
        }
        while ((E_NOT_OK == funcResult) && (pQA->sduCount > (PduR_GwIf_SduCountType) 0x00));

        if (E_NOT_OK == funcResult)
        {
          /* FiFo is empty and all transmission attempts have failed */
          pQA->bTxConfP = FALSE;
        }
      }
    }
    else
    {
      /* unexpected confirmation - ignore it */
    }
    PduR_Core_LeaveCriticalArea();
  }
/* ------------------------------------------ TT-FiFo Queued Handling - PDUR256 -------------------------------------*/
  else if (PDUR_GWIF_TT_FIFO == pQI->bufferType)
  {
    pQA = &pdur_GwIf_QueueAdmin[GwIfTxPduId];
    PduR_Det_AssertReturnFunc(GwIfTxPduId < PduR_GetCfgElement(IfRoutingQueuedTxPduCnt), PDUR_FCT_GWIF_TXCONF,
                              PDUR_E_INVALID_CFG_DATA);

    PduR_Core_EnterCriticalArea();
    if (FALSE != pQA->bTxConfP)
    {
      if ((PduR_GwIf_SduCountType) 0x01 == pQA->sduCount)
      {
        pQA->sduCount = (PduR_GwIf_SduCountType) 0x00;
        pQA->bTxConfP = FALSE;
      }
      else
      {
        pQStart = &pdur_Core_GwBuffer[pQI->bufferStartIdx] + pQA->rdIdx;
        pDestFunc = PduR_Core_TransmitFctPtrTbl[pQI->destPort];
        destPduInfo.SduLength = PduR_GwGetInitialPduLength();
        do
        {
          /* Remove previously transmitted FiFo entry from queue */
          pQA->sduCount--;
          pQA->rdIdx += PduR_GwGetBufferElementSize();
          if (pQA->rdIdx >= pQI->queueSize)
          {
            /* Wrap around required */
            pQA->rdIdx = (PduR_GwIf_BufferIdxType) 0x00;
          }
          /* Transmit next entry */
          destPduInfo.SduDataPtr = PduR_GwGetPduBufferStartPtr(pQStart);
          funcResult = pDestFunc(pQI->destPduId, &destPduInfo);
          if ((E_NOT_OK == funcResult)
#   if (PDUR_LINIF_SUPPORT == STD_ON)
              /* LIN IF will always return E_NOT_OK for unconditional frames (see LINIF341) */
              && (pQI->destPort != PDUR_PORT_LINIF)
#   endif
            )
          {
            PduR_Dem_ReportErrorStatus(PDUR_PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED);
          }
        }
        while (((E_NOT_OK == funcResult) && (pQA->sduCount > (PduR_GwIf_SduCountType) 0x01))
#   if (PDUR_LINIF_SUPPORT == STD_ON)
               /* LIN IF will always return E_NOT_OK for unconditional frames (see LINIF341) */
               && (pQI->destPort != PDUR_PORT_LINIF)
#   endif
          );

        if ((E_NOT_OK == funcResult)
#   if (PDUR_LINIF_SUPPORT == STD_ON)
            /* LIN IF will always return E_NOT_OK for unconditional frames (see LINIF341) */
            && (pQI->destPort != PDUR_PORT_LINIF)
#   endif
          )
        {
          pQA->sduCount = (PduR_GwIf_SduCountType) 0x00;
          pQA->wrIdx = pQA->rdIdx;
          pQA->bTxConfP = FALSE;
        }
      }
    }
    else
    {
      /* unexpected confirmation - ignore it */
    }
    PduR_Core_LeaveCriticalArea();
  }
  else
  {
    /* Empty statement to satisfy MISRA Rule 60 */
  }
#  else
#   if (PDUR_USE_DUMMY_STATEMENT == STD_ON)
  GwIfTxPduId = GwIfTxPduId;    /* PRQA S 3199 *//* MD_PduR_3199 *//*lint -e438 */
#   endif
#  endif
  /* (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */
}                               /* End of PduR_GwIf_TxConfirmation() */

# endif
        /* (PDUR_GW_COMIF == STD_ON) */
       /* defined(GW_ASRPDUR_ENABLE_FEATURE_GATEWAY_COMMENT) */
# if(PDUR_GW_TP == STD_ON)
/*********************************************************************************************************************/
/* Transport protocol gateway specific functions                                                                     */
/*********************************************************************************************************************/
STATIC FUNC(void, PDUR_CODE) PduR_GwTpResetRouting(PduIdType GwTpRxPduId)
{
  uint16_least bufferInfoIdx = PduR_GetCfgElement(TpRoutingBufferRefOffset) + GwTpRxPduId;
  uint8 bufferId = pdur_Core_GwBuffer[bufferInfoIdx];
  if (PDUR_GWTP_ROUTING_IDLE != bufferId)
  {
    PduR_GwTp_BufferAdminTypePtr pBA = &pdur_GwTp_BufferAdmin[bufferId];
    if (PDUR_BIT_FALSE == pBA->bRxIndicationPending)
    {
      /* Initialize buffer administration */
      pBA->rrId = PDUR_GWTP_BUFFER_IDLE;

      /* Deactivate routing relation */
      pdur_Core_GwBuffer[bufferInfoIdx] = PDUR_GWTP_ROUTING_IDLE;
    }
    else
    {
      pBA->bRoutingCanceled = PDUR_BIT_TRUE;
    }
  }
}                               /* End of PduR_GwTpResetRouting() */


FUNC(BufReq_ReturnType, PDUR_CODE) PduR_GwTp_ProvideRxBuffer(PduIdType GwTpRxPduId, PduLengthType TpSduLength,
                                                             P2VAR(PduInfoTypeApplPtr, AUTOMATIC,
                                                                   PDUR_APPL_DATA) PduInfoPtr)
{
  PduR_GwTp_BufferITypePtr pBI;
  uint8 bufferId;
  PduR_GwTp_BufferAdminTypePtr pBA = NULL_PTR;
  PduR_GwTp_RRITypePtr pRI = &PduR_GetCfgElement(TpRoutingRrInfo)[GwTpRxPduId];
  uint16_least bufferInfoIdx = PduR_GetCfgElement(TpRoutingBufferRefOffset) + GwTpRxPduId;
  BufReq_ReturnType retVal = BUFREQ_OK;
#  if (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON)
  if (0 == pdur_DestPduStateCnt[pRI->DestPduCntIndex])
  {
    return BUFREQ_E_NOT_OK;
  }
#  endif/* (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON) */
  PduR_Core_EnterCriticalArea();
  bufferId = pdur_Core_GwBuffer[bufferInfoIdx];
  if (PDUR_GWTP_ROUTING_IDLE == bufferId)
  {
    /* FF or SF is received - initialize routing relation */
    sint16_least startBufferIdx;
    sint16_least iBuffer;
    uint16 lastSuitableBufferIdx = PDUR_GWTP_NOBUFFERFOUND;
    PduLengthType iRequiredBufferLength;
#  if (PDUR_MOSTTP_SUPPORT == STD_ON)
    if (pRI->destPort == PDUR_PORT_MOSTTP)
    {
      /*DAP header size has to be taken into account to find the routing buffer */
      iRequiredBufferLength = TpSduLength + kMostIfDapHdrLen;
    }
    else
#  endif
    {
#  if(PDUR_GWTP_2PROVIDERXBUFFER_CALLS == STD_ON)
      iRequiredBufferLength = pRI->tpChunkSize + PDUR_CANTPFFSIZE;
#  else
      iRequiredBufferLength = TpSduLength;
#  endif
    }

    if (iRequiredBufferLength < pRI->tpChunkSize)
    {
      startBufferIdx = ((sint16_least) PduR_GetCfgElement(TpRoutingBufferCnt)) - 1;
    }
    else
    {
      startBufferIdx = (sint16_least) pRI->smallestBufferIdx;
    }

    pBI = &PduR_GetCfgElement(TpRoutingBufferInfo)[startBufferIdx];
    for (iBuffer = startBufferIdx; iBuffer >= 0; iBuffer--)
    {
      if ((pBI->bufferLength >= TpSduLength) && (pBI->bufferLength >= iRequiredBufferLength))
      {
        if (PDUR_GWTP_BUFFER_IDLE == pdur_GwTp_BufferAdmin[iBuffer].rrId)
        {
          pdur_Core_GwBuffer[bufferInfoIdx] = (uint8) iBuffer;
          pBA = &pdur_GwTp_BufferAdmin[iBuffer];
          break;
        }
      }
      else
      {
        if (PDUR_GWTP_BUFFER_IDLE == pdur_GwTp_BufferAdmin[iBuffer].rrId)
        {
          lastSuitableBufferIdx = (uint16) iBuffer;
        }
      }
      pBI--;
    }
    if (pBA == NULL_PTR)
    {
      /* The received TP PDU is larger than the largest available TP buffer element.
         The routing is executed using a ringbuffer mechanism that allows a smaller
         receive buffer. However, there is a risk of a buffer overflow. */
      if (PDUR_GWTP_NOBUFFERFOUND == lastSuitableBufferIdx)
      {
        /*return allways BUFREQ_E_NOT_OK in order to avoid a buffer request retry in the Tp module */
        retVal = BUFREQ_E_NOT_OK;
      }
      else
      {
#  if (PDUR_MOSTTP_SUPPORT == STD_ON)
        /* ring-buffer mechanism for a MOST destination routing in ProvideRxBuffer is not be supported */
        PduR_Det_ReportError(PDUR_FCT_GWTP_PRORX, PDUR_E_TP_RX_REQ_REJECTED);
        pBA = NULL_PTR;
        retVal = BUFREQ_E_NOT_OK;
#  else
        pdur_Core_GwBuffer[bufferInfoIdx] = (uint8) lastSuitableBufferIdx;
        pBI = &PduR_GetCfgElement(TpRoutingBufferInfo)[lastSuitableBufferIdx];
        pBA = &pdur_GwTp_BufferAdmin[lastSuitableBufferIdx];
#  endif
      }
    }
    if (pBA != NULL_PTR)
    {
      /* initialize the buffer administration element */
      pBA->rrId = GwTpRxPduId;
      pBA->tpSduLength = TpSduLength;
      pBA->iPendingConfirmations = 0;
      /*ProvideRxBuffer PduInfoPtr returns the startposition of the buffer + DAP header. */
#  if (PDUR_MOSTTP_SUPPORT == STD_ON)
      if (pRI->destPort == PDUR_PORT_MOSTTP)
      {
        pBA->rxIdx = pBI->bufferStartIdx + kMostIfDapHdrLen;
      }
      else
#  endif
      {
        pBA->rxIdx = pBI->bufferStartIdx;
      }
      pBA->txIdx = pBI->bufferStartIdx;
      pBA->bTxTriggered = PDUR_BIT_FALSE;
      pBA->bBufferIsEmpty = PDUR_BIT_TRUE;
      pBA->bFirstTxBufferRequested = PDUR_BIT_FALSE;
      pBA->bRxIndicationPending = PDUR_BIT_TRUE;
      pBA->bRoutingCanceled = PDUR_BIT_FALSE;
#  if(PDUR_GWTP_2PROVIDERXBUFFER_CALLS == STD_ON)
      pBA->bufferRxEndIdx = pBI->bufferEndIdx;
#  endif
    }
  }
  else
  {
    /* Handle the buffer that has been released with this call */
    pBI = &PduR_GetCfgElement(TpRoutingBufferInfo)[bufferId];
    pBA = &pdur_GwTp_BufferAdmin[bufferId];
    if (PDUR_BIT_FALSE != pBA->bRxIndicationPending)
    {
      if (PDUR_BIT_FALSE == pBA->bRoutingCanceled)
      {
        if ((PduLengthType) 0x00u != pBA->rxPduInfo.SduLength)
        {
          pBA->bBufferIsEmpty = PDUR_BIT_FALSE;
          pBA->rxIdx += pBA->rxPduInfo.SduLength;
          if (pBA->rxIdx >= PduR_GetGwTpBufferEndIndex())
          {
            /*wrap around */
            pBA->rxIdx = pBI->bufferStartIdx;
          }
        }

        if ((PDUR_BIT_FALSE == pBA->bTxTriggered) && (pRI->destPort != PDUR_PORT_MULTI))
        {
          PduInfoType destPduInfo;
          PduR_Core_TransmitFctPtrType pDestFunc = PduR_Core_TransmitFctPtrTbl[pRI->destPort];
#   if(PDUR_CDDDOBT_SUPPORT == STD_ON)
          PduR_SwitchTransmitFctPtr2CddDobt(pRI->destPort, pRI->destPduId, pDestFunc);
#   endif
          PduR_Det_Assert(pDestFunc != NULL_PTR, PDUR_FCT_GWTP_PRORX, PDUR_E_PDU_ID_INVALID);
          destPduInfo.SduDataPtr = NULL_PTR;    /* unused, see CanTp110, FrTp149 */
          destPduInfo.SduLength = pBA->tpSduLength;
          if (E_NOT_OK == pDestFunc(pRI->destPduId, &destPduInfo))
          {
            PduR_Det_ReportError(PDUR_FCT_GWTP_PRORX, PDUR_E_TP_TX_REQ_REJECTED);
            pBA->bRxIndicationPending = PDUR_BIT_FALSE;
            PduR_GwTpResetRouting(GwTpRxPduId);
            retVal = BUFREQ_E_NOT_OK;
          }
          else
          {
            pBA->bTxTriggered = PDUR_BIT_TRUE;
            pBA->iPendingConfirmations++;
          }
        }
      }
      else
      {
        pBA->bRxIndicationPending = PDUR_BIT_FALSE;
        PduR_GwTpResetRouting(GwTpRxPduId);
        retVal = BUFREQ_E_NOT_OK;
      }
    }
    else
    {
      retVal = BUFREQ_E_BUSY;
    }
  }

  if ((pBA != NULL_PTR) && (BUFREQ_OK == retVal))
  {
    uint16_least availableLinearBuffer;
    if (pBA->rxIdx > pBA->txIdx)
    {
      availableLinearBuffer = (uint16_least) (PduR_GetGwTpBufferEndIndex() - pBA->rxIdx);
#  if(PDUR_GWTP_2PROVIDERXBUFFER_CALLS == STD_ON)
      if (availableLinearBuffer < pRI->tpChunkSize)
      {
        /*init end of data to ensure that the tx pointer end at valid data */
        pBA->bufferRxEndIdx = pBA->rxIdx;
        /*wrap around and recalculate available buffer */
        pBA->rxIdx = pBI->bufferStartIdx;
        availableLinearBuffer = (uint16_least) (pBA->txIdx - pBA->rxIdx);
      }
#  endif
    }
    else if ((pBA->rxIdx < pBA->txIdx))
    {
      availableLinearBuffer = (uint16_least) (pBA->txIdx - pBA->rxIdx);
    }
    else
    {
      if (PDUR_BIT_FALSE == pBA->bBufferIsEmpty)
      {
        /* Rx buffer is full */
        availableLinearBuffer = (uint16_least) 0x00u;
        retVal = BUFREQ_E_BUSY;
      }
      else
      {
        availableLinearBuffer = (uint16_least) (PduR_GetGwTpBufferEndIndex() - pBA->rxIdx);
      }
    }

    if (availableLinearBuffer >= pRI->tpChunkSize)
    {
      pBA->rxPduInfo.SduLength = pRI->tpChunkSize;
    }
    else
    {
#  if(PDUR_GWTP_2PROVIDERXBUFFER_CALLS == STD_ON)
      pBA->rxPduInfo.SduLength = 0;
      retVal = BUFREQ_E_BUSY;
#  else
      pBA->rxPduInfo.SduLength = availableLinearBuffer;
#  endif
    }
    pBA->rxPduInfo.SduDataPtr = &pdur_Core_GwBuffer[pBA->rxIdx];
    *PduInfoPtr = &(pBA->rxPduInfo);
  }
  else
  {
    *PduInfoPtr = NULL_PTR;
  }
  PduR_Core_LeaveCriticalArea();

  return retVal;

}                               /* End of PduR_GwTp_ProvideRxBuffer() */

FUNC(void, PDUR_CODE) PduR_GwTp_RxIndication(PduIdType GwTpRxPduId, NotifResultType Result)
{
  uint8 bufferId;
  uint16_least bufferInfoIdx = PduR_GetCfgElement(TpRoutingBufferRefOffset) + GwTpRxPduId;

  PduR_Core_EnterCriticalArea();
  bufferId = pdur_Core_GwBuffer[bufferInfoIdx];

  if (PDUR_GWTP_ROUTING_IDLE != bufferId)
  {
    PduR_GwTp_BufferAdminTypePtr pBA = &pdur_GwTp_BufferAdmin[bufferId];
    {
      if (pBA->bRxIndicationPending != PDUR_BIT_FALSE)
      {
        pBA->bRxIndicationPending = PDUR_BIT_FALSE;

        if ((NTFRSLT_OK == Result) && (PDUR_BIT_FALSE == pBA->bRoutingCanceled))
        {
          PduR_GwTp_BufferITypePtr pBI = &PduR_GetCfgElement(TpRoutingBufferInfo)[bufferId];
          pBA->rxIdx += pBA->rxPduInfo.SduLength;
          if (pBA->rxIdx >= pBI->bufferEndIdx)
          {
            pBA->rxIdx = pBI->bufferStartIdx;
          }
          pBA->bBufferIsEmpty = PDUR_BIT_FALSE;
          if (PDUR_BIT_FALSE == pBA->bTxTriggered)
          {
            PduInfoType srcPduInfo;
            srcPduInfo.SduDataPtr = &pdur_Core_GwBuffer[pBA->txIdx];
            srcPduInfo.SduLength = pBA->tpSduLength;
            PduR_GwTpRouteAndTransmit(GwTpRxPduId, pBA, srcPduInfo);
          }
        }
        else
        {
          PduR_GwTpResetRouting(GwTpRxPduId);
        }
      }
    }
  }
  PduR_Core_LeaveCriticalArea();
}                               /* End of PduR_GwTp_RxIndication() */

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_GwTp_ProvideTxBuffer(PduIdType GwTpTxPduId,
                                                             P2VAR(PduInfoTypeApplPtr, AUTOMATIC,
                                                                   PDUR_APPL_DATA) PduInfoPtr, PduLengthType Length)
{
  uint8 bufferId;
  uint16_least bufferInfoIdx = PduR_GetCfgElement(TpRoutingBufferRefOffset) + GwTpTxPduId;
  BufReq_ReturnType retVal = BUFREQ_OK;
#  if (PDUR_USE_DUMMY_STATEMENT == STD_ON)
  /* Length attribute required for generic function pointer table implementation */
  Length = Length;              /* PRQA S 3199 *//* MD_PduR_3199 *//*lint -e438 */
#  endif

  PduR_Core_EnterCriticalArea();
  bufferId = pdur_Core_GwBuffer[bufferInfoIdx];
  if (PDUR_GWTP_ROUTING_IDLE != bufferId)
  {
    PduR_GwTp_BufferITypePtr pBI = &PduR_GetCfgElement(TpRoutingBufferInfo)[bufferId];
    PduR_GwTp_BufferAdminTypePtr pBA = &pdur_GwTp_BufferAdmin[bufferId];

    if (PduR_GetCfgElement(TpRoutingRrInfo)[GwTpTxPduId].destPort != PDUR_PORT_MULTI)
    {
      if (PDUR_BIT_FALSE == pBA->bFirstTxBufferRequested)
      {
        /* First call to provide Tx Buffer. No Tx buffer can be freed yet */
        pBA->bFirstTxBufferRequested = PDUR_BIT_TRUE;
      }
      else
      {
        /* Free the previously used Tx buffer to allow reusage on the Rx side */
        if ((PduLengthType) 0x00u != pBA->txPduInfo.SduLength)
        {
          pBA->txIdx += pBA->txPduInfo.SduLength;
          if (pBA->txIdx >= PduR_GetGwTpBufferEndIndex())
          {
#  if(PDUR_GWTP_2PROVIDERXBUFFER_CALLS == STD_ON)
            pBA->bufferRxEndIdx = pBI->bufferEndIdx;
#  endif
            pBA->txIdx = pBI->bufferStartIdx;
          }
          if (pBA->txIdx == pBA->rxIdx)
          {
            /* Buffer is empty - no more released Rx data available */
            pBA->bBufferIsEmpty = PDUR_BIT_TRUE;
          }
        }
      }

      /* Assign new Tx buffer to the TP layer */
      if (PDUR_BIT_FALSE == pBA->bBufferIsEmpty)
      {
#  if (PDUR_BALANCE_ROUTING_TIME == STD_ON)
        PduR_GwTp_RRITypePtr pRI = &PduR_GetCfgElement(TpRoutingRrInfo)[GwTpTxPduId];
#  endif
        /* Rx is in front of Tx index */
        if (pBA->rxIdx > pBA->txIdx)
        {
          PduLengthType idxDif = (PduLengthType) (pBA->rxIdx - pBA->txIdx);
#  if (PDUR_BALANCE_ROUTING_TIME == STD_ON)
          if (idxDif >= pRI->tpChunkSize)
          {
            pBA->txPduInfo.SduLength = (pRI->tpChunkSize);
          }
          else
#  endif
          {
            pBA->txPduInfo.SduLength = idxDif;
          }
        }
        else
        {
          /* Tx is in front of Rx index (Tx is larger) */
          PduLengthType idxDif = (PduLengthType) (PduR_GetGwTpBufferEndIndex() - pBA->txIdx);
#  if (PDUR_BALANCE_ROUTING_TIME == STD_ON)
          if (idxDif >= pRI->tpChunkSize)
          {
            pBA->txPduInfo.SduLength = (pRI->tpChunkSize);
          }
          else
#  endif
          {
            pBA->txPduInfo.SduLength = idxDif;
          }
        }
#  if (PDUR_MOSTTP_SUPPORT == STD_ON)
        pBA->txPduInfo.SduDataPtr = (uint8 *) ((uint32) & pdur_Core_GwBuffer[pBA->txIdx] + kMostIfDapHdrLen);
#  else
        pBA->txPduInfo.SduDataPtr = &pdur_Core_GwBuffer[pBA->txIdx];
#  endif
        *PduInfoPtr = &(pBA->txPduInfo);
      }
      else
      {
        pBA->txPduInfo.SduLength = (PduLengthType) 0x00u;
        retVal = BUFREQ_E_BUSY;
        *PduInfoPtr = NULL_PTR;
      }
    }
    else
    {
      /* 1:N routing */
      pBA->txPduInfo.SduLength = pBA->tpSduLength;
      pBA->txPduInfo.SduDataPtr = &pdur_Core_GwBuffer[pBI->bufferStartIdx];
      *PduInfoPtr = &(pBA->txPduInfo);
    }
  }
  else
  {
    PduR_Det_ReportError(PDUR_FCT_GWTP_PROTX, PDUR_E_UNEXPECTED_CALL);
    retVal = BUFREQ_E_NOT_OK;
    *PduInfoPtr = NULL_PTR;
  }
  PduR_Core_LeaveCriticalArea();
  return retVal;
}                               /* End of PduR_GwTp_ProvideTxBuffer() */


FUNC(void, PDUR_CODE) PduR_GwTp_TxConfirmation(PduIdType GwTpTxPduId, NotifResultType Result)
{
  uint8 bufferId;
  uint16_least bufferInfoIdx = PduR_GetCfgElement(TpRoutingBufferRefOffset) + GwTpTxPduId;

  PduR_Core_EnterCriticalArea();
  bufferId = pdur_Core_GwBuffer[bufferInfoIdx];
  if (PDUR_GWTP_ROUTING_IDLE != bufferId)
  {
    PduR_GwTp_BufferAdminTypePtr pBA = &pdur_GwTp_BufferAdmin[bufferId];

    if (0 != pBA->iPendingConfirmations)
    {
      pBA->iPendingConfirmations--;
    }
    if (0 == pBA->iPendingConfirmations)
    {
      PduR_GwTpResetRouting(GwTpTxPduId);
    }
    else
    {
      PduR_Det_Assert(PduR_GetCfgElement(TpRoutingRrInfo)[GwTpTxPduId].destPort == PDUR_PORT_MULTI,
                      PDUR_FCT_GWTP_TXCONF, PDUR_E_UNEXPECTED_CALL);
    }
  }
  else
  {
    PduR_Det_ReportError(PDUR_FCT_GWTP_TXCONF, PDUR_E_UNEXPECTED_CALL);
  }
  PduR_Core_LeaveCriticalArea();

#  if (PDUR_USE_DUMMY_STATEMENT == STD_ON)
  Result = Result;              /* PRQA S 3199 *//* MD_PduR_3199 *//*lint -e438 */
#  endif
}                               /* End of PduR_GwTp_TxConfirmation() */

STATIC FUNC(void, PDUR_CODE) PduR_GwTpRouteAndTransmit(PduIdType GwTpRxPduId, PduR_GwTp_BufferAdminTypePtr pBA,
                                                       PduInfoType pSrcPduInfo)
{
  /* Multiple destination ports are allowed as all data can be provided at once */
  PduR_GwTp_RRITypePtr pRI = &PduR_GetCfgElement(TpRoutingRrInfo)[GwTpRxPduId];
  PduR_Core_TransmitFctPtrType pDestFunc;
  PduInfoType destPduInfo;
  destPduInfo.SduDataPtr = NULL_PTR;    /* unused, see CanTp110, FrTp149 */
  destPduInfo.SduLength = pSrcPduInfo.SduLength;

#  if(PDUR_MULTICAST_FROMTP_SUPPORT == STD_ON)
  if (pRI->destPort != PDUR_PORT_MULTI)
#  endif
  {
#  if (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON)
    if (0 != pdur_DestPduStateCnt[pRI->DestPduCntIndex])
#  endif /* (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON) */
    {
      pDestFunc = PduR_Core_TransmitFctPtrTbl[pRI->destPort];
      PduR_Det_Assert(pDestFunc != NULL_PTR, PDUR_FCT_GWTP_ROUTE, PDUR_E_PDU_ID_INVALID);
#   if(PDUR_CDDDOBT_SUPPORT == STD_ON)
      PduR_SwitchTransmitFctPtr2CddDobt(pRI->destPort, pRI->destPduId, pDestFunc);
#   endif
      if (E_OK == pDestFunc(pRI->destPduId, &destPduInfo))
      {
        pBA->iPendingConfirmations++;
      }
      else
      {
        PduR_Det_ReportError(PDUR_FCT_GWTP_ROUTE, PDUR_E_TP_TX_REQ_REJECTED);
        PduR_GwTpResetRouting(GwTpRxPduId);
      }
    }
  }
#  if(PDUR_MULTICAST_FROMTP_SUPPORT == STD_ON)
  else
  {
    PduR_GwTp_RRMulDestInfoTypePtr pMRI = &PduR_GetCfgElement(TpRoutingMultRrInfo)[pRI->destPduId];
    do
    {
#   if (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON)
      if (0 != pdur_DestPduStateCnt[pMRI->DestPduCntIndex])
#   endif /* (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON) */
      {
        PduR_UpTpProvideRxBufferFctPtrType pUpTpProvideRxBufferFctPtr = PduR_Core_UpTpProvideRxBuffer[pMRI->destPort];
        P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) pUlPduInfo = NULL_PTR;
        if (pUpTpProvideRxBufferFctPtr != NULL_PTR)
        {
          PduR_UpTpRxIndicationFctPtrType pUpTpRxIndicationFctPtr = PduR_Core_UpTpRxIndication[pMRI->destPort];
          if (BUFREQ_OK == pUpTpProvideRxBufferFctPtr(pMRI->destPduId, pSrcPduInfo.SduLength, &pUlPduInfo))
          {
            PduR_Det_Assert(NULL_PTR != pUlPduInfo, PDUR_FCT_GWTP_ROUTE, PDUR_E_DATA_PTR_INVALID);
            /* PRQA S 0505 DCMPDUINFOPTR_0505 *//* MD_PduR_0505_DcmPduInfo */
            PduR_Det_Assert(NULL_PTR != pUlPduInfo->SduDataPtr, PDUR_FCT_GWTP_ROUTE, PDUR_E_DATA_PTR_INVALID);
            /* PRQA L:DCMPDUINFOPTR_0505 */
            if (pUlPduInfo->SduLength >= pSrcPduInfo.SduLength)
            {
              /* Buffer received from DCM is valid and of sufficient size */
              /* PRQA S 0850 MEMCPY_0850 *//* MD_MSR_19.8 */
              PduR_Core_MemCpyRamToRam(pUlPduInfo->SduDataPtr, pSrcPduInfo.SduDataPtr, pSrcPduInfo.SduLength);
              if (pUpTpRxIndicationFctPtr != NULL_PTR)
              {
                pUpTpRxIndicationFctPtr(pMRI->destPduId, NTFRSLT_OK);
              }
#   if (PDUR_DEV_ERROR_DETECT == STD_ON)
              else
              {
                PduR_Det_ReportError(PDUR_FCT_GWTP_ROUTE, PDUR_E_PDU_ID_INVALID);
              }
#   endif
            }
            else
            {
              pUpTpRxIndicationFctPtr(pMRI->destPduId, NTFRSLT_E_NOT_OK);
            }
          }
          else
          {
            pUpTpRxIndicationFctPtr(pMRI->destPduId, NTFRSLT_E_NOT_OK);
          }
        }
        else
        {
          pDestFunc = PduR_Core_TransmitFctPtrTbl[pMRI->destPort];
#    if(PDUR_CDDDOBT_SUPPORT == STD_ON)
          PduR_SwitchTransmitFctPtr2CddDobt(pMRI->destPort, pMRI->destPduId, pDestFunc);
#    endif
          PduR_Det_Assert(pDestFunc != NULL_PTR, PDUR_FCT_GWTP_ROUTE, PDUR_E_PDU_ID_INVALID);
          if (E_OK == pDestFunc(pMRI->destPduId, &destPduInfo))
          {
            pBA->iPendingConfirmations++;
          }
          else
          {
            PduR_Det_ReportError(PDUR_FCT_GWTP_ROUTE, PDUR_E_TP_TX_REQ_REJECTED);
          }
        }
      }
      pMRI++;
    }
    while (pMRI->startId == pRI->destPduId);

    if (pBA->iPendingConfirmations > 0)
    {
      pBA->bTxTriggered = PDUR_BIT_TRUE;
    }
    else
    {
      /* All transmission requests failed. Reset the routing */
      PduR_GwTpResetRouting(GwTpRxPduId);
    }
  }
#  endif /* PDUR_MULTICAST_FROMTP_SUPPORT */
}


#  if(PDUR_MULTI_TP_TX_SUPPORT == STD_ON)
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_MultiTp_ProvideTxBuffer(PduIdType MultiTpRxPduId,
                                                                P2VAR(PduInfoTypeApplPtr, AUTOMATIC,
                                                                      PDUR_APPL_DATA) PduInfoPtr, PduLengthType Length)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  uint8 iCallCounter = 0;
  PduIdType firstElementStartId;
  PduR_GwTp_RRMulDestInfoTypePtr pMRI = &PduR_GetCfgElement(TpRoutingMultTx2UpRrInfo)[MultiTpRxPduId];
  do
  {
    firstElementStartId = pMRI->startId;
#   if (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON)
    if (0 != pdur_DestPduStateCnt[pMRI->DestPduCntIndex])
#   endif/* (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON) */
    {
      if (0 == iCallCounter)
      {
        PduR_UpTpProvideTxBufferFctPtrType pUpTpProvideTxBufferFctPtr = PduR_Core_UpTpProvideTxBuffer[pMRI->destPort];
        if (pUpTpProvideTxBufferFctPtr != NULL_PTR)
        {
          retVal = pUpTpProvideTxBufferFctPtr(pMRI->destPduId, PduInfoPtr, Length);
          ++iCallCounter;
        }
      }
      else
      {
        /* MultiTp Routing must called exclusively. This must be ensured by the routing group configuration */
        PduR_Det_ReportError(PDUR_FCT_MULTITPPROTX, PDUR_E_UNEXPECTED_CALL);
        retVal = BUFREQ_E_NOT_OK;
        break;
      }
    }
    pMRI++;
  }
  while (pMRI->startId == firstElementStartId);
  return retVal;
}                               /* End of PduR_MultiTp_ProvideTxBuffer() */

FUNC(void, PDUR_CODE) PduR_MultiTp_TxConfirmation(PduIdType MultiTpRxPduId, NotifResultType Result)
{
  uint8 iCallCounter = 0;
  PduIdType firstElementStartId;
  PduR_GwTp_RRMulDestInfoTypePtr pMRI = &PduR_GetCfgElement(TpRoutingMultTx2UpRrInfo)[MultiTpRxPduId];
  do
  {
    firstElementStartId = pMRI->startId;
#   if (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON)
    if (0 != pdur_DestPduStateCnt[pMRI->DestPduCntIndex])
#   endif/* (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON) */
    {
      if (0 == iCallCounter)
      {
        PduR_UpTpTxConfirmationFctPtrType pUpTpTxConfirmationFctPtr = PduR_Core_UpTpTxConfirmation[pMRI->destPort];
        if (pUpTpTxConfirmationFctPtr != NULL_PTR)
        {
          pUpTpTxConfirmationFctPtr(pMRI->destPduId, Result);
          ++iCallCounter;
        }
      }
      else
      {
        /* MultiTp Routing must called exclusively. This must be ensured by the routing group configuration */
        PduR_Det_ReportError(PDUR_FCT_MULTITP_TXCONF, PDUR_E_UNEXPECTED_CALL);
        break;
      }
    }
    pMRI++;
  }
  while (pMRI->startId == firstElementStartId);
}                               /* End of PduR_MultiTp_TxConfirmation() */

#  endif/* PDUR_MULTICAST_FROMTP_SUPPORT */
# endif
    /* (PDUR_GW_TP == STD_ON) */
    /* defined(GW_ASRPDUR_ENABLE_FEATURE_TPGATEWAY_COMMENT) */

# if(PDUR_CDDDOBT_SUPPORT == STD_ON)
FUNC(void, PDUR_CODE) PduR_CddDobtSetCanTpState(boolean CddDobtState)
{
  PduR_Det_AssertReturnFunc(PduR_Core_GetState() == PDUR_ONLINE, PDUR_FCT_CDDDOBTSETCANTPSTATE, PDUR_E_INVALID_REQUEST);
  pdur_CddDobtState = CddDobtState;
}

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CddDobtProvideTxBuffer(PduIdType CanTpTxPduId,
                                                               P2VAR(PduInfoTypeApplPtr, AUTOMATIC,
                                                                     PDUR_APPL_DATA) PduInfoPtr, uint16 Length)
{
  PduR_Det_AssertReturnFuncValue(PduR_Core_GetState() == PDUR_ONLINE, PDUR_FCT_CDDDOBTPROTX, PDUR_E_INVALID_REQUEST,
                                 BUFREQ_E_NOT_OK);
  PduR_Det_AssertReturnFuncValue(PduInfoPtr != NULL_PTR, PDUR_FCT_CDDDOBTPROTX, PDUR_E_DATA_PTR_INVALID,
                                 BUFREQ_E_NOT_OK);
  PduR_Det_AssertReturnFuncValue(CanTpTxPduId < PduR_GetCfgElement(TxCanTp2UpCnt), PDUR_FCT_CDDDOBTPROTX,
                                 PDUR_E_PDU_ID_INVALID, BUFREQ_E_NOT_OK);
  PduR_Det_AssertReturnFuncValue(PduR_GetCfgElement(TxCanTp2Up)[CanTpTxPduId].destPort != PDUR_PORT_INVALID,
                                 PDUR_FCT_CDDDOBTPROTX, PDUR_E_PDU_ID_INVALID, BUFREQ_E_NOT_OK);
  PduR_Det_AssertReturnFuncValue(pdur_CddDobtState == TRUE, PDUR_FCT_CDDDOBTPROTX, PDUR_E_INVALID_REQUEST,
                                 BUFREQ_E_NOT_OK);

  return PduR_CanTpProvideTxBuffer(CanTpTxPduId, PduInfoPtr, Length);
}

FUNC(void, PDUR_CODE) PduR_CddDobtTxConfirmation(PduIdType CanTpTxPduId, NotifResultType Result)
{
  PduR_Det_AssertReturnFunc(PduR_Core_GetState() == PDUR_ONLINE, PDUR_FCT_CDDDOBTTXCFM, PDUR_E_INVALID_REQUEST);
  PduR_Det_AssertReturnFunc(CanTpTxPduId < PduR_GetCfgElement(TxCanTp2UpCnt), PDUR_FCT_CDDDOBTTXCFM,
                            PDUR_E_PDU_ID_INVALID);
  PduR_Det_AssertReturnFunc(pdur_CddDobtState == TRUE, PDUR_FCT_CDDDOBTTXCFM, PDUR_E_INVALID_REQUEST);

  PduR_CanTpTxConfirmation(CanTpTxPduId, Result);
}

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CddDobtProvideRxBuffer(PduIdType CanTpRxPduId, PduLengthType TpSduLength,
                                                               P2VAR(PduInfoTypeApplPtr, AUTOMATIC,
                                                                     PDUR_APPL_DATA) PduInfoPtr)
{
  PduR_Core_DestITypePtr pDI;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  PduR_Det_AssertReturnFuncValue(PduR_Core_GetState() == PDUR_ONLINE, PDUR_FCT_CDDDOBTPRORX, PDUR_E_INVALID_REQUEST,
                                 BUFREQ_E_NOT_OK);
  PduR_Det_AssertReturnFuncValue(PduInfoPtr != NULL_PTR, PDUR_FCT_CDDDOBTPRORX, PDUR_E_DATA_PTR_INVALID,
                                 BUFREQ_E_NOT_OK);
  PduR_Det_AssertReturnFuncValue(CanTpRxPduId < PduR_GetCfgElement(RxCanTp2UpCnt), PDUR_FCT_CDDDOBTPRORX,
                                 PDUR_E_PDU_ID_INVALID, BUFREQ_E_NOT_OK);
  PduR_Det_AssertReturnFuncValue(PduR_GetCfgElement(RxCanTp2Up)[CanTpRxPduId].destPort != PDUR_PORT_INVALID,
                                 PDUR_FCT_CDDDOBTPRORX, PDUR_E_PDU_ID_INVALID, BUFREQ_E_NOT_OK);
  PduR_Det_AssertReturnFuncValue(pdur_CddDobtState == TRUE, PDUR_FCT_CDDDOBTPRORX, PDUR_E_INVALID_REQUEST,
                                 BUFREQ_E_NOT_OK);
  pDI = &PduR_GetCfgElement(RxCanTp2Up)[CanTpRxPduId];
  {
#  if (PDUR_MULTIPLE_CONFIGURATION == STD_ON)
    if (pDI->destPort != PDUR_PORT_INVALID)
#  endif
    {
#  if (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON)
      if (0 != pdur_DestPduStateCnt[pDI->DestPduCntIndex])
#  endif
        /* (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON) */
      {
#   if(PDUR_GW_TP == STD_ON)
        if (pDI->destPort == PDUR_PORT_GW)
        {
          return PduR_GwTp_ProvideRxBuffer(pDI->destPduId, TpSduLength, PduInfoPtr);
        }
#   endif
        {
#  if (PDUR_CANTP_2PROVIDERXBUFFER_CALLS == STD_ON)
          /* Start of ESCAN00044523 */
          PduR_Provide2RxBufferCallsWrapperTypePtr pProvideRxBufferCallsWrapper =
            &pdur_CanTpProvide2RxBufferCallsWrapper[CanTpRxPduId];
          {
            pProvideRxBufferCallsWrapper->ProvideRxBufferCallCounter++;
            /*emulate the second ProvideRxBuffer call of the UL */
            if (pProvideRxBufferCallsWrapper->ProvideRxBufferCallCounter == 2)
            {
              PduLengthType iSduLength = (*PduInfoPtr)->SduLength;
              /* The feature PDUR_CANTP_2PROVIDERXBUFFER_CALLS requires minimum a buffer in the UL with the size FF + 1 Byte */
              if (pProvideRxBufferCallsWrapper->ProvidedBufferLengthByUL > iSduLength)
              {
                pProvideRxBufferCallsWrapper->CopiedDataLength = iSduLength;
                (*PduInfoPtr)->SduDataPtr = (*PduInfoPtr)->SduDataPtr + iSduLength;
                (*PduInfoPtr)->SduLength = pProvideRxBufferCallsWrapper->ProvidedBufferLengthByUL - iSduLength;
                return BUFREQ_OK;
              }
              else
              {
                pProvideRxBufferCallsWrapper->ProvideRxBufferCallCounter = 0;
                PduR_Det_AssertReturnFuncValue(FALSE, PDUR_FCT_CANTPPRORX, PDUR_E_UL_BUFFER_UNDERRUN, BUFREQ_E_NOT_OK);
              }
            }
            else if (pProvideRxBufferCallsWrapper->ProvideRxBufferCallCounter == 3)
            {
              /*Reset all pointer manipulations to ensure that the upper layer module adjusts its pointer correct */
              (*PduInfoPtr)->SduDataPtr = (*PduInfoPtr)->SduDataPtr - (pProvideRxBufferCallsWrapper->CopiedDataLength);
              (*PduInfoPtr)->SduLength = pProvideRxBufferCallsWrapper->CopiedDataLength + (*PduInfoPtr)->SduLength;
            }
          }
          if (pProvideRxBufferCallsWrapper->ProvideRxBufferCallCounter != 2)
            /*End of ESCAN00044523 */
#  endif
          {
            PduR_UpTpProvideRxBufferFctPtrType pUpTpProvideRxBufferFctPtr =
              PduR_Core_UpTpProvideRxBuffer[pDI->destPort];
            if (pUpTpProvideRxBufferFctPtr != NULL_PTR)
            {
              retVal = pUpTpProvideRxBufferFctPtr(pDI->destPduId, TpSduLength, PduInfoPtr);
            }
#  if (PDUR_DEV_ERROR_DETECT == STD_ON)
            else
            {
              PduR_Det_ReportError(PDUR_FCT_CANTPPRORX, PDUR_E_PDU_ID_INVALID);
            }
#  endif
#  if (PDUR_CANTP_2PROVIDERXBUFFER_CALLS == STD_ON)     /*Start ESCAN00044523 */
            if (pProvideRxBufferCallsWrapper->ProvideRxBufferCallCounter == 1)
            {
              if (retVal == BUFREQ_OK)
              {
                pProvideRxBufferCallsWrapper->ProvidedBufferLengthByUL = (*PduInfoPtr)->SduLength;
              }
              else
              {
                pdur_CanTpProvide2RxBufferCallsWrapper[CanTpRxPduId].ProvideRxBufferCallCounter = 0;
              }
            }
#  endif  /*End ESCAN00044523 */
          }
        }
      }
    }
  }
  return retVal;
}                               /* End of PduR_CddDobtProvideRxBuffer() */

FUNC(void, PDUR_CODE) PduR_CddDobtRxIndication(PduIdType CanTpRxPduId, NotifResultType Result)
{
  PduR_Det_AssertReturnFunc(PduR_Core_GetState() == PDUR_ONLINE, PDUR_FCT_CDDDOBTRXIND, PDUR_E_INVALID_REQUEST);
  PduR_Det_AssertReturnFunc(CanTpRxPduId < PduR_GetCfgElement(RxCanTp2UpCnt), PDUR_FCT_CDDDOBTRXIND,
                            PDUR_E_PDU_ID_INVALID);
  PduR_Det_AssertReturnFunc(pdur_CddDobtState == TRUE, PDUR_FCT_CDDDOBTRXIND, PDUR_E_INVALID_REQUEST);

  PduR_CanTpRxIndication(CanTpRxPduId, Result);
}
# endif

#if ((PDUR_CHANGEPARAMETER_SUPPORT == STD_ON) || (PDUR_READPARAMETER_SUPPORT == STD_ON) || (PDUR_RECEIVECANCELLATION_SUPPORT == STD_ON))
FUNC(boolean, PDUR_CODE) PduR_Core_GetLoTpHandleFromUpTpHandle(PduR_Core_DestITypePtr pDIStart, PduIdType pDICnt,
                                                               PduIdType UpRxPduIdPort, PduIdType UpRxPduId,
                                                               P2VAR(PduIdType, AUTOMATIC, PDUR_APPL_DATA) LoRxPduId)
{
  sint16_least sLoRxPduId;
  for (sLoRxPduId = ((sint16_least) pDICnt) - 1; sLoRxPduId >= 0; sLoRxPduId--)
  {
    PduR_Core_DestITypePtr pCurRR = &pDIStart[sLoRxPduId];
    if (pCurRR->destPort == UpRxPduIdPort)
    {
      if (pCurRR->destPduId == UpRxPduId)
      {
        *LoRxPduId = (PduIdType) sLoRxPduId;
        return TRUE;
      }
    }
# if(PDUR_MULTICAST_FROMTP_SUPPORT == STD_ON)
    else if (pCurRR->destPort == PDUR_PORT_MULTI)
    {
      PduIdType MultiTpRxPduId = pCurRR->destPduId;
      PduR_GwTp_RRMulDestInfoTypePtr pMRR = &PduR_GetCfgElement(TpRoutingMultRrInfo)[MultiTpRxPduId];
      while (pMRR->startId == pCurRR->destPduId)
      {
        if (pMRR->destPort == UpRxPduIdPort)
        {
          if (pMRR->destPduId == UpRxPduId)
          {
            *LoRxPduId = (PduIdType) sLoRxPduId;
            return TRUE;
          }
        }
        MultiTpRxPduId++;
        pMRR = &PduR_GetCfgElement(TpRoutingMultRrInfo)[MultiTpRxPduId];
      }
    }
# endif
  }
  return FALSE;
}
#endif


#if (PDUR_ROUTINGPATHGROUP_SUPPORT == STD_ON)
FUNC(void, PDUR_CODE) PduR_EnableRouting(PduR_RoutingPathGroupIdType id)
{
  PduR_Det_AssertReturnFunc(PduR_Core_GetState() == PDUR_ONLINE, PDUR_FCT_ENABLEROUTING, PDUR_E_INVALID_REQUEST);
  PduR_Det_AssertReturnFunc(id < PduR_GetCfgElement(RoutingPathGroupCnt), PDUR_FCT_ENABLEROUTING,
                            PDUR_E_ROUTING_TABLE_ID_INVALID);
  if (FALSE == pdur_RoutingPathGroupState[id])
  {
    uint16 PathGroupIndirectionIdx = PduR_GetCfgElement(RPG2DestPduStateCntStartIndex)[id];
    uint16 PathGroupIndirectionStopIdx = PduR_GetCfgElement(RPG2DestPduStateCntStartIndex)[id + 1];
    for (; PathGroupIndirectionIdx < PathGroupIndirectionStopIdx; PathGroupIndirectionIdx++)
    {
      pdur_DestPduStateCnt[PduR_GetCfgElement(RPG2DestPduStateCntInd)[PathGroupIndirectionIdx]]++;
    }
    pdur_RoutingPathGroupState[id] = TRUE;
  }
}

FUNC(void, PDUR_CODE) PduR_DisableRouting(PduR_RoutingPathGroupIdType id)
{
  PduR_Det_AssertReturnFunc(PduR_Core_GetState() == PDUR_ONLINE, PDUR_FCT_DISABLEROUTING, PDUR_E_INVALID_REQUEST);
  PduR_Det_AssertReturnFunc(id < PduR_GetCfgElement(RoutingPathGroupCnt), PDUR_FCT_DISABLEROUTING,
                            PDUR_E_ROUTING_TABLE_ID_INVALID);
  if (TRUE == pdur_RoutingPathGroupState[id])
  {
    uint16 PathGroupIndirectionIdx = PduR_GetCfgElement(RPG2DestPduStateCntStartIndex)[id];
    uint16 PathGroupIndirectionStopIdx = PduR_GetCfgElement(RPG2DestPduStateCntStartIndex)[id + 1];
    for (; PathGroupIndirectionIdx < PathGroupIndirectionStopIdx; PathGroupIndirectionIdx++)
    {
      pdur_DestPduStateCnt[PduR_GetCfgElement(RPG2DestPduStateCntInd)[PathGroupIndirectionIdx]]--;
    }
    pdur_RoutingPathGroupState[id] = FALSE;
  }
}
#endif
#define PDUR_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_19.1 */
/*lint -restore */
/*======================================== PDUR_STOP_SEC_CODE ========================================*/


/**********************************************************************************************************************
 * GLOBAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* module specific MISRA deviations:
   MD_PduR_0310:  MISRA rule: 11.4
     Reason:      Cast operation to uint8* required for optimized memory clear operation. Implementation is correct.
     Risk:        Invalid memory access.
     Prevention:  Verified at integration with the customer hardware with the automated integration test suite.

   MD_PduR_0505_DcmPduInfo:  MISRA rule: 1.2
     Reason:      Pointer validity of pDcmPduInfo is checked with previous assertion.
     Risk:        Invalid pointer dereferencing.
     Prevention:  No functional risk.

   MD_PduR_0488:  MISRA rule: 17.4
     Reason:      The pointer arithmetic is required for optimized routing implementation.
     Risk:        Invalid memory accesses.
     Prevention:  Verified at integration with the customer hardware with the automated integration test suite.

   MD_PduR_0489:  MISRA rule: 17.4
     Reason:      The pointer arithmetic is required for optimized routing implementation.
     Risk:        Invalid memory accesses.
     Prevention:  Verified at integration with the customer hardware with the automated integration test suite.

   MD_PduR_0635:  MISRA rule: 6.4
     Reason:      Bitfields are required for RAM optimized administration of the PduR routing buffer.
     Risk:        Undefined compiler behaviour.
     Prevention:  Usage of vbittype in bit-fields verified by CAN-Driver component.

   MD_PduR_1334:  MISRA rule: 16.4
     Reason:      Generic paramer identifier [Up]RxPduId differs due to the upper layer specific parameter names.
     Risk:        Compiler warning.
     Prevention:  Not required.

   MD_PduR_3199:
     Reason:      Dummy statement required to avoid compiler warnings.
     Risk:        No functional risk.
     Prevention:  Not required.

   MD_PduR_3201_LLTriggerTransmit:  MISRA rule: 14.1
     Reason:      Control flow depends on implementation of Det_ReportError. In case function Det_ReportError returns
                  the statement is reachable.
     Risk:        Compiler warning.
     Prevention:  Not required.

   MD_PduR_3408:  MISRA rule: 8.8
     Reason:      Dummy buffer element required due to post-build support and complex condition dependencies.
     Risk:        No functional risk.
     Prevention:  Not required.

   MD_PduR_3410:  MISRA rule: 19.10
     Reason:      The used semantic of the macro does not allow enclosing the parameter in braces. The usage is correct.
     Risk:        No functional risk.
     Prevention:  Not required.

   MD_PduR_3684:  MISRA rule: 8.12
     Reason:      Empty brackets needed to avoid compile optimization because of library build.
     Risk:        Invalid memory accesses.
     Prevention:  Covered by code review.
*/
/* *INDENT-ON* */

/**********************************************************************************************************************
 * END OF FILE: PduR.c
 *********************************************************************************************************************/
/* STOPSINGLE_OF_MULTIPLE */
