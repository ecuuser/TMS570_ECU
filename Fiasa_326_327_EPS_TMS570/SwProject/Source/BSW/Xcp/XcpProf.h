

/*****************************************************************************
| Project Name:   XCP Protocol Layer
|    File Name:   XcpProf.h
|
|  Description:   Header of XCP Protocol Layer
|                 XCP V1.0 slave device driver
|                 Professional Version
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2013 by Vector Informatik GmbH.           All rights reserved.
|
|       This software is copyright protected and 
|       proporietary to Vector Informatik GmbH.
|       Vector Informatik GmbH grants to you only
|       those rights as set out in the license conditions.
|       All other rights remain with Vector Informatik GmbH.
| 
|       Diese Software ist urheberrechtlich geschuetzt. 
|       Vector Informatik GmbH raeumt Ihnen an dieser Software nur 
|       die in den Lizenzbedingungen ausdruecklich genannten Rechte ein.
|       Alle anderen Rechte verbleiben bei Vector Informatik GmbH.
|
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| Ds           Sven Deckardt             Vector Informatik GmbH
| Eta          Edgar Tongoona            Vector Informatik GmbH
| Hr           Andreas Herkommer         Vector Informatik GmbH
| Ore          Oliver Reineke            Vector Informatik GmbH
| Svh          Sven Hesselmann           Vector Informatik GmbH
| Tri          Frank Triem               Vector Informatik GmbH
| Za           Rainer Zaiser             Vector Informatik GmbH
| Bwr          Brandon Root              Vector CANtech
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
|  Date       Version  Author  Description
| ----------  -------  ------  -----------------------------------------------
| 2000-24-09  10        Ds     - New header description
| 2003-24-04  10        Ds     - Swap GET_SECTOR_INFO Mode and Number
| 2003-24-04  10        Ds     - Swap SET_SEGMENT_MODE Mode and Number
| 2003-25-04  10        Ds     - Swap GET_SEGMENT_INFO Mode and Number
| 2003-28-04  10        Ds     - GET_SEGMENT_MODE reserved position 1
| 2003-28-04  10        Ds     - GET_PAGE_INFO reserved position 1
| 2003-10-30  1.0.03    Ds     - Rename xcp20.h to xcpProf.h 
| 2003-11-20  1.01.00   Tri    Updated to PSC standard.
|                              MISRA rules applied.
|                              Minor changes.
| 2004-02-11  1.01.01   Ds,Tri Updated and adaption for CANape
|                              ESCAN00007511: Warning when compiling XCP.H
|                              ESCAN00007517: Compiler error when using a packet length of 253 bytes or greater
|                              ESCAN00007518: Seed & Key: reading of the unlock key not performed correctly
|                              ESCAN00007532: Division by zero in calculation of the queue size
|                              ESCAN00007533: Memory overflow check during memory allocation might not be detected.
| 2004-06-16  1.02.00   Tri    ESCAN00008482: Add user defined function to service GET_ID
| 2005-01-03  1.03.00   Tri,Za ESCAN00008009: Rename module versions according to PD_PSC_Development
|                              ESCAN00009121: Add copyright note
|                              ESCAN00009125: Remove defines for revision 18
|                              ESCAN00009127: Remove XCP_ENABLE_SEND_BUFFER
|                              ESCAN00009130: Add support for data stimulation (STIM)
|                              ESCAN00007824: Warning due to unreferenced label 'negative_response1'
|                              ESCAN00008012: Remove include definitions of the standard libraries within XCP Professional
|                              ESCAN00008015: Avoid usage of the test mode within XCP Professional
|                              ESCAN00008018: XCP module version in response of CC_GET_COMM_MODE_INFO corrected
|                              ESCAN00008004: Compiler error when block upload is enabled and block download is disabled
|                              ESCAN00008005: Resource bit for CAL/PAG always set in response upon CC_CONNECT
|                              ESCAN00009141: Compiler warnings while compilation with Tasking Compiler
|                              ESCAN00007823: Warning about unreferenced variable 'prescaler'
|                              ESCAN00008003: Compiler error when block download is disabled and Programming enabled
|                              ESCAN00008060: Issue in negative response of command BUILD_CHECKSUM
|                              ESCAN00008013: Checksum calculation wrong
|                              ESCAN00008072: Compiler warning in range check of defines
|                              ESCAN00007971: Implement and support 'session configuration id'
|                              ESCAN00008006: Page switching always enabled when programming is enabled.
|                              ESCAN00008010: Remove extern declaration for xcp struct
|                              ESCAN00009154: Update Seed & Key
|                              ESCAN00010703: PROGRAM size = 0 is valid
|                              ESCAN00008017: Rework of Flash Programming by Flash Kernel
|                              ESCAN00009200: Positive Response upon command PROGRAM_START not correct
|                              ESCAN00010705: Rework command PROGRAM_RESET
|                              ESCAN00010706: Return the status of event channels
|                              ESCAN00010707: Consistency check in case of no DAQ released
|                              ESCAN00008008: Apply PSC naming convention for types and structures
|                              ESCAN00009173: Consistency check for generator DLL and component
|                              ESCAN00008007: Rename the post-organified filenames to xcpProf.h and xcpProf.c
|                              ESCAN00009172: Atmega only: Compiler error due to pointer conversion from RAM to Flash
|                              ESCAN00007209: Apply naming convention to callback functions
|                              ESCAN00009144: Minor changes
| 2005-02-01  1.04.00   Tri    ESCAN00010989: Update comment for version scan
|                              ESCAN00010848: Move timestamp unit of response to GET_DAQ_EVENT_INFO in low nibble
| 2005-02-17  1.05.00   Tri    ESCAN00011210: Support GENy Fwk 1.3 DLL Versions
| 2005-02-28  1.06.00   Tri    ESCAN00010961: Include XCP Transport Layer on CAN
| 2005-05-10  1.07.00   Tri    ESCAN00011446: Tasking Compiler only: Compiler Warnings
|                              ESCAN00012314: Compatibility with CANape 5.5.x regarding timestamp unit
|                              ESCAN00012356: Support data paging on Star12X / Metrowerks
|                              ESCAN00012617: Add service to retrieve XCP state
| 2006-01-03  1.08.00   Tri    ESCAN00013899: Data acquisition not possible during cold start
|                              ESCAN00009196: PROGRAM_FORMAT is not implemented as specified
|                              ESCAN00009199: Negative Response to command PROGRAM_PREPARE is not correct
|                              ESCAN00009202: Programming Info not implemented correctly
|                              ESCAN00014313: Warning because of undefined 'kXcpStimOdtCount'
|                              ESCAN00013634: Remove kXcpPacketHeaderSize
|                              ESCAN00014710: Rework Calibration Data Page Freeze
|                              ESCAN00014712: Rework Segment Info and Page Info
|                              ESCAN00014775: Delayed EEPROM read access not possible
| 2006-03-09  1.09.00   Tri    ESCAN00013637: Support command TRANSPORT_LAYER_CMD
|                              ESCAN00015283: Start of a single DAQ list is not possible
|                              ESCAN00015607: Support XCP on FlexRay Transport Layer
| 2006-05-05  1.10.00   Tri    ESCAN00016158: Add demo disclaimer to XCP Basic
|                              ESCAN00016098: Calculation of CRC16 CCITT is not correct
| 2006-05-30  1.11.00   Tri    ESCAN00016225: Support Cp_XcpOnLin
| 2006-07-18  1.12.00   Tri    ESCAN00016955: Support AUTOSAR CRC module
|                              ESCAN00016958: Delayed EEPROM read access not possible
| 2006-10-26  1.13.00   Tri    ESCAN00017516: Support Cp_XcpOnCanAsr
|                              ESCAN00017504: Replace P_MEM_ROM by MEMORY_FAR resp. V_MEMRAM2_FAR
|                              ESCAN00017804: Multiple definitions of XCP_DISABLE_TESTMODE
|                              ESCAN00017878: Overwriting of memory during data acquisition allocation
| 2007-01-30  1.14.00   Tri    ESCAN00018808: Support data paging on Star12X / Cosmic
| 2007-04-03  1.15.00   Eta    ESCAN00018153: Overwriting of memory during data stimulation
|                       Svh    ESCAN00020126: Commands SHORT_DOWNLOAD and MODIFY_BITS must be supported
|                              ESCAN00012618: Support command MODIFY_BITS
|                              ESCAN00020127: It has to be possible to en-/disable XCP globally
|                              ESCAN00019094: Extend implementation for runtime deactivation of XCP (professional)
|                              ESCAN00020128: Add AUTOSAR based API
|                              ESCAN00018154: Support overwriting of XcpSendDto() in header
|                              ESCAN00015859: Support memory read protection
| 2007-05-25  1.16.00   Svh    ESCAN00020906: Compiler error due to incorrect pointer assignment
| 2007-07-09  1.16.01   Hr     Support AUTOSAR Memory Mapping
| 2007-12-07  1.16.02   Hr     ISS046 - Only CTOs are flushed by the Protocol Layer
| 2007-09-14  1.17.00   Svh    ESCAN00022293: Support for SET_SEGMENT_MODE and GET_SEGMENT_MODE added
| 2007-12-17  1.18.00   Svh    ESCAN00023759: Compile error for MCS12x
| 2008-03-17  1.19.00   Svh    ESCAN00021035: XcpSendCallBack() always returns 1
|                              ESCAN00024265: STIM with time stamp is not supported
|                              ESCAN00024863: Missing error code in CC_TRANSPORT_LAYER_CMD
|                              ESCAN00025020: Possible stack issues with big MAX_DTO values in case Send Queue is not used
|                              ESCAN00023570: Do not set default answer is last CRM is still pending
| 2008-04-10  1.20.00   Svh    ESCAN00025979: tXcpDto wrong structure ordering causing erroneous one-time Stim trigger
| 2008-04-30  1.21.00   Eta    ESCAN00026424: compiler error when using Cosmic with option -pck
|                       Svh    ESCAN00026491: Data inconsistency of ODTs in case of Overrun + FlexRay
| 2008-04-30  1.21.01   Svh    ESCAN00026541: compiler error due to unknown symbol
| 2008-06-04  1.21.02   Svh    ESCAN00027343: Redefinition of ApplXcpSendFlush
| 2008-07-21  1.22.00   Hr     ESCAN00022545: Memory Read Protection always returns Ok to CANape
|                              ESCAN00020637: Support different Info Time Unit for DTO handling
|                              ESCAN00017954: Support MIN_ST_PGM
|                              ESCAN00017951: Add open interface for command processing
|                              ESCAN00028579: CC_PROGRAM_START should support an application callback
|                       Svh    ESCAN00028720: Support ADDRESS_GRANULARITY WORD
| 2008-09-10  1.23.00   Svh    ESCAN00029890: Incorrect checksum calculation
|                              ESCAN00029896: Command pending for several call backs added
|                              ESCAN00029897: XcpStimEventStatus() returns 1 also if no STIM data is available
|                              ESCAN00029905: Configuration of parameter MIN_ST in response of GET_COMM_MODE_INFO command added
| 2008-10-01  1.23.01   Hr     ESCAN00030382: Compiler error due to missing ;
| 2008-10-10  1.23.02   Bwr    ESCAN00030037: Support for more than 255 ODT entries
| 2008-12-01  1.24.00   Hr     ESCAN00031342: Version information of implementation inconsistent to release version information
|                              ESCAN00031726: Add support for XcpOnTcpIpAsr
|                              ESCAN00031948: Event gets lost, if a Response is still pending
|                              ESCAN00031949: Add error check for ODT_SIZE_WORD with no DAQ_HDR_ODT_DAQ
|                       Bwr    ESCAN00030566: SET_REQUEST with incorrect mode is ignored
|                              ESCAN00030601: Support for more than 255 ODTs
| 2009-02-05  1.24.01   Hr     ESCAN00032861: CC_SET_DAQ_PTR fails due to Diab Data Compiler bug
| 2009-02-27  1.24.02   Hr     ESCAN00031794: Compiler warning: large type was implicitly cast to small type
|                              ESCAN00033655: Canbedded compile error due to uint8
| 2009-05-13  1.25.00   Hr     ESCAN00033909: New features implemented: Prog Write Protection, Timestamps, Calibration activation
| 2009-10-08  1.25.01   Hr     ESCAN00038283: After second measurement start with INCA no timestamps are generated anymore.
|                              ESCAN00038805: Implement Compiler and Memory Abstraction to allow correct usage in AUTOSAR stacks
| 2009-11-26            Hr     ESCAN00039350: TMS320 Compile error: struct has no field "EightByteField"
| 2010-03-24  1.26.00   Hr     ESCAN00041784: new API for better calibration support
|                              ESCAN00041784: Queue size calculation incorrect under certain conditions
| 2010-04-26  1.26.01   Hr     ESCAN00041960: Remove Address Granularity Word
|                              ESCAN00042970: Support MISRA2004
| 2010-06-08  1.27.00   Hr     ESCAN00042867: Support Multiple Transport Layers
|                              ESCAN00043141: Support Xcp_InitMemory Service
|                              ESCAN00043334: Queue size calculation incorrect on 32Bit Platforms
|                              ESCAN00043861: Support different Send Queue replacement strategies
|                              ESCAN00043862: Storage of DAQ configuration in resume mode shall be limited to needed memory only
|                              ESCAN00043875: Support Info Mem for Plug and Play purposes
| 2010-10-13  1.27.01   Hr     ESCAN00045792: Send Queue limited to 255 Entries by typecasts
|                              ESCAN00045771: '##' does not produce a valid preprocessing token
| 2010-11-17  1.27.02   Hr     ESCAN00046963: Read Protection not independent of Write Protection
|                              ESCAN00041943: Compiler Warning: condition is always false
| 2011-01-10  1.28.00   Hr     ESCAN00045981: Add support to read out FR Parameters
|                              ESCAN00046233: Adapt AUTOSAR version check
|                              ESCAN00043858: Support Measurement of Stack Variables
|                              ESCAN00048313: Rework XCP_TRANSPORT_LAYER_VERSION to be multi transport layer capable
|                              ESCAN00048571: CC_PROGRAM_CLEAR does not make use of programming write protection
|                              ESCAN00048723: Compiler abstraction incomplete
| 2011-04-08  1.29.00   Hr     ESCAN00049491: MainFunction of Transport Layer might be called twice
|                              ESCAN00049884: The Macro XCP_DEACTIVATE does not deactivate the Protocol Layer
|                              ESCAN00049974: Add DET checks to implementation
|                              ESCAN00049976: Replace sections by NOINIT variant
| 2011-05-05  1.30.00   Ore,Hr ESCAN00050094: Xcp Control: Extend XCP_DEACTIVATE Macro to perform a disconnect of component
|                              ESCAN00050091: Virtual FlexRay Parameters: Address Extension 0xff can not be used
|                              ESCAN00048721: Send Queue behaviour shall be selectable during runtime
|                              ESCAN00051373: Software might hang in endless software loop
|                              ESCAN00051440: Optimization to prevent a goto in the code
|                              ESCAN00051447: ApplXcpSend does not have a return value
|                              ESCAN00051324: Add Generic Measurement
| 2011-08-17  1.30.01   Hr     ESCAN00052799: XCP master cannot measure variables via Generic Measurement feature
|                              ESCAN00052802: Generic Measurement: XCP master aborts connection to XCP slave
| 2011-09-30  1.30.02   Hr     ESCAN00053954: Check DAQ lists for validity before they are started
|                              ESCAN00054616: Get DAQ Event Info does not work if Virtual FlexRy Parameters is active
| 2011-11-02            Hr     ESCAN00054316: Issue of memory read/write protection in DAQ measurement
| 2011-12-08  1.30.03   Hr     ESCAN00055482: AR3-1482: Support variant legacy file names
| 2012-02-17  1.30.04   Hr     ESCAN00055214: DAQ Lists can be extended after START_STOP_SYNCH
| 2012-05-31  1.30.05   Hr     ESCAN00058915: Trap if WRITE_DAQ is used before a DAQ list is created.
| 2012-07-17  1.30.06   Hr     ESCAN00060212: Cfg5 error: Xcp makes use of CANbedded classifier
|                              ESCAN00061075: Compile error or warning due to return value of MainFunction
|                              ESCAN00060904: Provide an API to detect XCP state and usage
| 2012-10-18  1.31.00   Hr     ESCAN00062359: Add module specific define
|                              ESCAN00060583: AR3-2446: Implement all necessary countermeasures for SilentBSW
|                              ESCAN00060551: AR3-2443: Implement Silent Checks in BSW module code
|                              ESCAN00059404: ETH used instead of TCPIP in macros
|                              ESCAN00057330: AR3-2374: Implement Silent BSW
|                              ESCAN00061036: AR3-2378: Implement AMD timemeasurement support
|                              ESCAN00062480: CANXCP_CODE undefined in XcpProf.c 
| 2012-10-18  1.31.01   Hr     ESCAN00063364: Compiler error: DET enabled with XcpGetSessionStatus API
| 2013-01-21  2.01.00   Hr     ESCAN00064372: Create AUTOSAR 4.0 branch
| 2013-01-21  2.02.00   Hr     ESCAN00064819: Session Configuration ID not reset during CLEAR_DAQ_REQ
|                              ESCAN00064768: AR4-296: Support ASAM 1.1 Specification
|                              ESCAN00064770: AR4-300: Support 65k Events
|                              ESCAN00064864: Remove DAQ list clearing during CONNECT command
|                              ESCAN00066642: Compiler warning: #42-D: operand types are incompatible ("tXcpData *" and "tXcpData **")
|                              ESCAN00065886: Compiler warning: [10343] cast discards qualifiers from pointer target type
| 2013-08-20  2.03.00   Hr     ESCAN00069259: Compile error: incompatible argument type in XcpCalculateCrc call
|                              ESCAN00069418: Optimize: DTOs shall be aligned to 32Bit
|                              ESCAN00068345: Compiler warning: warning #177-D: label "negative_response1" was declared but never referenced
|                              ESCAN00066813: The MISRA justifications are not implemented according WI_MISRAC2004_PES.pdf
| 2013-11-07  2.03.01   Hr     ESCAN00071221: Compiler warning: cast truncates constant value
|                              ESCAN00072219: DAQ Timestamp Unit check causes compile error for ASAM 1.1 types
|                              ESCAN00072274: API Xcp_GetSessionStatus does not report polling flag
| 2013-11-28  2.04.00   Hr     ESCAN00072723: Event configuration limited to 255 entries
|                              ESCAN00072326: Support Generic GET_ID
|                              ESCAN00072401: Support custom CRC Cbk
|                              ESCAN00067723: AR4-535: Predefined Runtime Measurement Points
|***************************************************************************/

#if !defined ( __XCP_H_ )
#define __XCP_H_


/***************************************************************************/
/* Include                                                                 */
/***************************************************************************/

/* Includes for XcpProf.c/XcpBasic.c */
    #include "Xcp_Cfg.h"
    #include "Xcp_Lcfg.h"

/* Include the Transport Layer for CAN (AUTOSAR CAN Interface) if available. */
#if defined ( XCP_TRANSPORT_LAYER_TYPE_CAN_ASR )
  #include "CanXcp.h"
  #include "CanXcp_Cfg.h"
#endif

/* Include the Transport Layer for FlexRay (AUTOSAR FlexRay Interface) if available. */
#if defined ( XCP_TRANSPORT_LAYER_TYPE_FLEXRAY_ASR )
  #include "FrXcp.h"
#endif

/* Include the Transport Layer for Ethernet if available. */
#if defined ( XCP_TRANSPORT_LAYER_TYPE_TCPIP_ASR )
  #include "TcpIpXcp.h"
#endif

/* Include the Transport Layer for Lin if available. */
#if defined ( XCP_TRANSPORT_LAYER_TYPE_LIN_ASR )
  #include "LinXcp.h"
#endif


/***************************************************************************/
/* Version                                                                 */
/***************************************************************************/

/* BCD coded version number of XCP module */
/* ##V_CFG_MANAGEMENT ##CQProject : Cp_Xcp CQComponent : Implementation */
#define CP_XCP_VERSION         0x0204u
#define CP_XCP_RELEASE_VERSION 0x00u

/* Version of the XCP Protocol Layer Specification V1.1 */
#if ! defined ( XCP_VERSION )
  #define XCP_VERSION 0x0101
#endif

#define XCP_VENDOR_ID   30u
#define XCP_MODULE_ID   26u


/***************************************************************************/
/* Type definitions                                                        */
/***************************************************************************/
/* Development errors */
#if defined ( XCP_ENABLE_DEV_ERROR_DETECT )
/* Definition of the API ID */
  #define XCP_INIT_SERVICE_ID                   0u
  #define XCP_EVENT_SERVICE_ID                  1u
  #define XCP_STIMEVENTSTATUS_SERVICE_ID        2u
  #define XCP_SENDEVENT_SERVICE_ID              3u
  #define XCP_PUTCHAR_SERVICE_ID                4u
  #define XCP_PRINT_SERVICE_ID                  5u
  #define XCP_DISCONNECT_SERVICE_ID             6u
  #define XCP_SENDCRM_SERVICE_ID                7u
  #define XCP_GETXCPDATAPOINTER_SERVICE_ID      8u
  #define XCP_CONTROL_SERVICE_ID                9u
  #define XCP_GETVERSIONINFO_SERVICE_ID        10u
  #define XCP_COMMAND_SERVICE_ID               11u
  #define XCP_SENDCALLBACK_SERVICE_ID          12u
  #define XCP_EXIT_SERVICE_ID                  13u
  #define XCP_GETSTATE_SERVICE_ID              14u
  #define XCP_SETACTIVETL_SERVICE_ID           15u
  #define XCP_GETACTIVETL_SERVICE_ID           16u
  #define XCP_PRINTF_SERVICE_ID                17u
  #define XCP_PRINTDAQLIST_SERVICE_ID          18u
  #define XCP_EXTENDEDEVENT_SERVICE_ID         19u
  #define XCP_MAINFUNCTION_SERVICE_ID         200u

/* Definition of errors/exceptions */
  #define XCP_E_INV_POINTER                     1u
  #define XCP_E_NOT_INITIALIZED                 2u
  #define XCP_E_INVALID_PDUID                   3u
  #define XCP_E_NULL_POINTER                   18u
  #define XCP_E_WRONG_CONTROL_COMMAND           4u
#endif

/* Types used by appl call-backs */
#define XCP_RESUME_NONE       0x00
#define XCP_RESUME_ACTIVE     0x01


/***************************************************************************/
/* Commands                                                                */
/***************************************************************************/

/*-------------------------------------------------------------------------*/
/* Standard Commands */

#define CC_CONNECT                        0xFF
#define CC_DISCONNECT                     0xFE
#define CC_GET_STATUS                     0xFD
#define CC_SYNC                           0xFC

#define CC_GET_COMM_MODE_INFO             0xFB
#define CC_GET_ID                         0xFA
#define CC_SET_REQUEST                    0xF9
#define CC_GET_SEED                       0xF8
#define CC_UNLOCK                         0xF7
#define CC_SET_MTA                        0xF6
#define CC_UPLOAD                         0xF5
#define CC_SHORT_UPLOAD                   0xF4
#define CC_BUILD_CHECKSUM                 0xF3
                                          
#define CC_TRANSPORT_LAYER_CMD            0xF2
#define CC_USER_CMD                       0xF1


/*-------------------------------------------------------------------------*/
/* Calibration Commands*/

#define CC_DOWNLOAD                       0xF0

#define CC_DOWNLOAD_NEXT                  0xEF
#define CC_DOWNLOAD_MAX                   0xEE
#define CC_SHORT_DOWNLOAD                 0xED
#define CC_MODIFY_BITS                    0xEC


/*-------------------------------------------------------------------------*/
/* Page switching Commands (PAG) */

#define CC_SET_CAL_PAGE                   0xEB
#define CC_GET_CAL_PAGE                   0xEA

#define CC_GET_PAG_PROCESSOR_INFO         0xE9
#define CC_GET_SEGMENT_INFO               0xE8
#define CC_GET_PAGE_INFO                  0xE7
#define CC_SET_SEGMENT_MODE               0xE6
#define CC_GET_SEGMENT_MODE               0xE5
#define CC_COPY_CAL_PAGE                  0xE4


/*-------------------------------------------------------------------------*/
/* DATA Acquisition and Stimulation Commands (DAQ/STIM) */
                                          
#define CC_CLEAR_DAQ_LIST                 0xE3
#define CC_SET_DAQ_PTR                    0xE2
#define CC_WRITE_DAQ                      0xE1
#define CC_SET_DAQ_LIST_MODE              0xE0
#define CC_GET_DAQ_LIST_MODE              0xDF
#define CC_START_STOP_DAQ_LIST            0xDE
#define CC_START_STOP_SYNCH               0xDD

#define CC_GET_DAQ_CLOCK                  0xDC
#define CC_READ_DAQ                       0xDB
#define CC_GET_DAQ_PROCESSOR_INFO         0xDA
#define CC_GET_DAQ_RESOLUTION_INFO        0xD9 
#define CC_GET_DAQ_LIST_INFO              0xD8
#define CC_GET_DAQ_EVENT_INFO             0xD7

#define CC_FREE_DAQ                       0xD6
#define CC_ALLOC_DAQ                      0xD5
#define CC_ALLOC_ODT                      0xD4
#define CC_ALLOC_ODT_ENTRY                0xD3


/*-------------------------------------------------------------------------*/
/* Non volatile memory Programming Commands PGM */

#define CC_PROGRAM_START                  0xD2
#define CC_PROGRAM_CLEAR                  0xD1
#define CC_PROGRAM                        0xD0
#define CC_PROGRAM_RESET                  0xCF

#define CC_GET_PGM_PROCESSOR_INFO         0xCE
#define CC_GET_SECTOR_INFO                0xCD
#define CC_PROGRAM_PREPARE                0xCC
#define CC_PROGRAM_FORMAT                 0xCB 
#define CC_PROGRAM_NEXT                   0xCA
#define CC_PROGRAM_MAX                    0xC9
#define CC_PROGRAM_VERIFY                 0xC8


/*-------------------------------------------------------------------------*/
/* Customer specific commands */

#define CC_WRITE_DAQ_MULTIPLE             0xC7


/*-------------------------------------------------------------------------*/
/* Packet Identifiers Slave -> Master */
#define PID_RES                           0xFF   /* response packet        */
#define PID_ERR                           0xFE   /* error packet           */
#define PID_EV                            0xFD   /* event packet           */
#define PID_SERV                          0xFC   /* service request packet */


/*-------------------------------------------------------------------------*/
/* Command Return Codes */

#define CRC_CMD_SYNCH           0x00

#define CRC_CMD_BUSY            0x10
#define CRC_DAQ_ACTIVE          0x11
#define CRC_PRM_ACTIVE          0x12

#define CRC_CMD_UNKNOWN         0x20
#define CRC_CMD_SYNTAX          0x21
#define CRC_OUT_OF_RANGE        0x22
#define CRC_WRITE_PROTECTED     0x23
#define CRC_ACCESS_DENIED       0x24
#define CRC_ACCESS_LOCKED       0x25
#define CRC_PAGE_NOT_VALID      0x26
#define CRC_PAGE_MODE_NOT_VALID 0x27
#define CRC_SEGMENT_NOT_VALID   0x28
#define CRC_SEQUENCE            0x29
#define CRC_DAQ_CONDIF          0x2A

#define CRC_MEMORY_OVERFLOW     0x30
#define CRC_GENERIC             0x31
#define CRC_VERIFY              0x32
#define CRC_RESOURCE_TEMP_NOT_ACCESSIBLE 0x33


/*-------------------------------------------------------------------------*/
/* Event Codes */

#define EVC_RESUME_MODE        0x00
#define EVC_CLEAR_DAQ          0x01
#define EVC_STORE_DAQ          0x02
#define EVC_STORE_CAL          0x03
#define EVC_CMD_PENDING        0x05
#define EVC_DAQ_OVERLOAD       0x06
#define EVC_SESSION_TERMINATED 0x07
#define EVC_TIME_SYNC          0x08
#define EVC_STIM_TIMEOUT       0x09
#define EVC_SLEEP              0x0A
#define EVC_WAKE_UP            0x0B
#define EVC_USER               0xFE
#define EVC_TRANSPORT          0xFF


/*-------------------------------------------------------------------------*/
/* Service Request Codes */ 

#define SERV_RESET 0x00 /* Slave requesting to be reset */
#define SERV_TEXT  0x01 /* Plain ASCII text null terminated */


/*-------------------------------------------------------------------------*/
/* Flush Types */

#define XCP_FLUSH_CTO   0u
#define XCP_FLUSH_DTO   1u
#define XCP_FLUSH_ALL   2u


/***************************************************************************/
/* Definitions                                                             */
/***************************************************************************/

/*-------------------------------------------------------------------------*/
/* ResourceMask (CONNECT) */

#define RM_CAL_PAG                  0x01
#define RM_DAQ                      0x04
#define RM_STIM                     0x08
#define RM_PGM                      0x10


/*-------------------------------------------------------------------------*/
/* CommModeBasic (CONNECT) */

#define PI_MOTOROLA                   0x01

#define CMB_BYTE_ORDER                (0x01u<<0)
#define CMB_ADDRESS_GRANULARITY       (0x03u<<1)
#define CMB_SLAVE_BLOCK_MODE          (0x01u<<6)
#define CMB_OPTIONAL                  (0x01u<<7)

#define CMB_ADDRESS_GRANULARITY_BYTE  (0<<1)
#define CMB_ADDRESS_GRANULARITY_WORD  (1<<1)
#define CMB_ADDRESS_GRANULARITY_DWORD (2<<1)
#define CMB_ADDRESS_GRANULARITY_QWORD (3<<1)


/*-------------------------------------------------------------------------*/
/* Protocol Info (GET_COMM_MODE_INFO - COMM_OPTIONAL) */

#define CMO_MASTER_BLOCK_MODE  0x01
#define CMO_INTERLEAVED_MODE   0x02   


/*-------------------------------------------------------------------------*/
/* Session Status (GET_STATUS and SET_REQUEST) */

#define SS_STORE_CAL_REQ       0x0001u 
#define SS_BLOCK_UPLOAD        0x0002u /* Internal */
#define SS_STORE_DAQ_REQ_NO_RESUME 0x0002u /* Internal */
#define SS_STORE_DAQ_REQ       0x0004u
#define SS_CLEAR_DAQ_REQ       0x0008u
#define SS_ERROR               0x0010u /* Internal */
#define SS_CONNECTED           0x0020u /* Internal */
#define SS_DAQ                 0x0040u
#define SS_RESUME              0x0080u
#define SS_POLLING             0x0100u /* Internal */
#define SS_STORE_DAQ_REQ_NO_RESUME_INTERNAL 0x0200u /* Internal */


/*-------------------------------------------------------------------------*/
/* Identifier Type (GET_ID) */

#define IDT_ASCII              0
#define IDT_ASAM_NAME          1
#define IDT_ASAM_PATH          2
#define IDT_ASAM_URL           3
#define IDT_ASAM_UPLOAD        4
#define IDT_VECTOR_MAPNAMES    0xDB
#define IDT_VECTOR_INFOMEM     0xDC
#define IDT_VECTOR_GENMEAS     0xA2

/*-------------------------------------------------------------------------*/
/* Checksum Types (BUILD_CHECKSUM) */

#define XCP_CHECKSUM_TYPE_ADD11      0x01  /* Add BYTE into a BYTE checksum, ignore overflows */
#define XCP_CHECKSUM_TYPE_ADD12      0x02  /* Add BYTE into a WORD checksum, ignore overflows */
#define XCP_CHECKSUM_TYPE_ADD14      0x03  /* Add BYTE into a DWORD checksum, ignore overflows */
#define XCP_CHECKSUM_TYPE_ADD22      0x04  /* Add WORD into a WORD checksum, ignore overflows, blocksize must be modulo 2 */
#define XCP_CHECKSUM_TYPE_ADD24      0x05  /* Add WORD into a DWORD checksum, ignore overflows, blocksize must be modulo 2 */ 
#define XCP_CHECKSUM_TYPE_ADD44      0x06  /* Add DWORD into DWORD, ignore overflows, blocksize must be modulo 4 */
#define XCP_CHECKSUM_TYPE_CRC16      0x07  /* See CRC error detection algorithms */
#define XCP_CHECKSUM_TYPE_CRC16CCITT 0x08  /* See CRC error detection algorithms */
#define XCP_CHECKSUM_TYPE_CRC32      0x09  /* See CRC error detection algorithms */
#define XCP_CHECKSUM_TYPE_DLL        0xFF  /* User defined, ASAM MCD 2MC DLL Interface */


/*-------------------------------------------------------------------------*/
/* Page Mode (SET_CAL_PAGE) */

#define CAL_ECU                0x01
#define CAL_XCP                0x02
#define CAL_ALL                0x80        /* not supported */


/*-------------------------------------------------------------------------*/
/* PAG_PROPERTIES (GET_PAG_PROCESSOR_INFO) */

#define PAG_PROPERTY_FREEZE               0x01


/*-------------------------------------------------------------------------*/
/* PAGE_PROPERTIES (GET_PAGE_INFO)*/

#define ECU_ACCESS_TYPE                   0x03
#define XCP_READ_ACCESS_TYPE              0x0C
#define XCP_WRITE_ACCESS_TYPE             0x30

/* ECU_ACCESS_TYPE */
#define ECU_ACCESS_NONE                   (0<<0)
#define ECU_ACCESS_WITHOUT                (1<<0)
#define ECU_ACCESS_WITH                   (2<<0)
#define ECU_ACCESS_DONT_CARE              (3<<0)

/* XCP_READ_ACCESS_TYPE */
#define XCP_READ_ACCESS_NONE              (0<<2)
#define XCP_READ_ACCESS_WITHOUT           (1<<2)
#define XCP_READ_ACCESS_WITH              (2<<2)
#define XCP_READ_ACCESS_DONT_CARE         (3<<2)

/* XCP_WRITE_ACCESS_TYPE */
#define XCP_WRITE_ACCESS_NONE             (0<<4)
#define XCP_WRITE_ACCESS_WITHOUT          (1<<4)
#define XCP_WRITE_ACCESS_WITH             (2<<4)
#define XCP_WRITE_ACCESS_DONT_CARE        (3<<4)


/*-------------------------------------------------------------------------*/
/* SEGMENT_MODE (GET_SEGMENT_MODE, SET_SEGMENT_MODE) */

#define SEGMENT_FLAG_FREEZE               0x01 /* */


/*-------------------------------------------------------------------------*/
/* DAQ_LIST_MODE (GET_DAQ_LIST_MODE, SET_DAQ_LIST_MODE) */

#define DAQ_FLAG_SELECTED                 0x01u /* */
#define DAQ_FLAG_DIRECTION                0x02u /* Data Stimulation Mode */

#define DAQ_FLAG_TIMESTAMP                0x10u /* Timestamps */
#define DAQ_FLAG_NO_PID                   0x20u /* No PID */
#define DAQ_FLAG_RUNNING                  0x40u /* Is started */
#define DAQ_FLAG_RESUME                   0x80u /* Resume Mode */

#define DAQ_FLAG_RESERVED                 0x08u 
#define DAQ_FLAG_OVERRUN                  0x08u /* Overun (Internal Use) */


/*-------------------------------------------------------------------------*/
/* GET_DAQ_PROCESSOR_INFO */

/* DAQ_PROPERTIES */
#define DAQ_PROPERTY_CONFIG_TYPE          0x01
#define DAQ_PROPERTY_PRESCALER            0x02
#define DAQ_PROPERTY_RESUME               0x04
#define DAQ_PROPERTY_BIT_STIM             0x08
#define DAQ_PROPERTY_TIMESTAMP            0x10
#define DAQ_PROPERTY_NO_PID               0x20
#define DAQ_PROPERTY_OVERLOAD_INDICATION  0xC0

/* DAQ Overload Indication Type */
#define DAQ_OVERLOAD_INDICATION_NONE      (0<<6)
#define DAQ_OVERLOAD_INDICATION_PID       (1<<6)
#define DAQ_OVERLOAD_INDICATION_EVENT     (2<<6)

/* DAQ_KEY_BYTE */
#define DAQ_OPT_TYPE                      0x0F
#define DAQ_EXT_TYPE                      0x30
#define DAQ_HDR_TYPE                      0xC0

/* DAQ Optimisation Type */
#define DAQ_OPT_DEFAULT                   (0<<0)
#define DAQ_OPT_ODT_16                    (1<<0)
#define DAQ_OPT_ODT_32                    (2<<0)
#define DAQ_OPT_ODT_64                    (3<<0)
#define DAQ_OPT_ALIGNMENT                 (4<<0)
#define DAQ_OPT_MAX_ENTRY_SIZE            (5<<0)

/* DAQ Address Extension Scope */
#define DAQ_EXT_FREE                      (0<<4)
#define DAQ_EXT_ODT                       (1<<4)
#define DAQ_EXT_DAQ                       (3<<4)

/* DAQ Identification Field Type */
#define DAQ_HDR_PID                       (0<<6)
#define DAQ_HDR_ODT_DAQB                  (1<<6)
#define DAQ_HDR_ODT_DAQW                  (2<<6)
#define DAQ_HDR_ODT_FIL_DAQW              (3<<6)
 

/*-------------------------------------------------------------------------*/
/* GET_DAQ_RESOLUTION_INFO */

/* TIMESTAMP_MODE */
#define DAQ_TIMESTAMP_SIZE  0x07
#define DAQ_TIMESTAMP_FIXED 0x08
#define DAQ_TIMESTAMP_UNIT  0xF0

/* DAQ Timestamp Size */
#define DAQ_TIMESTAMP_OFF         (0<<0)
#define DAQ_TIMESTAMP_BYTE        (1<<0)
#define DAQ_TIMESTAMP_WORD        (2<<0)
#define DAQ_TIMESTAMP_DWORD       (4<<0)

/* DAQ Timestamp Unit */
#define DAQ_TIMESTAMP_UNIT_1NS    (0<<4)
#define DAQ_TIMESTAMP_UNIT_10NS   (1<<4)
#define DAQ_TIMESTAMP_UNIT_100NS  (2<<4)
#define DAQ_TIMESTAMP_UNIT_1US    (3<<4)
#define DAQ_TIMESTAMP_UNIT_10US   (4<<4)
#define DAQ_TIMESTAMP_UNIT_100US  (5<<4)
#define DAQ_TIMESTAMP_UNIT_1MS    (6<<4)
#define DAQ_TIMESTAMP_UNIT_10MS   (7<<4)
#define DAQ_TIMESTAMP_UNIT_100MS  (8<<4)
#define DAQ_TIMESTAMP_UNIT_1S     (9<<4)
#define DAQ_TIMESTAMP_UNIT_1PS    (10<<4)
#define DAQ_TIMESTAMP_UNIT_10PS   (11<<4)
#define DAQ_TIMESTAMP_UNIT_100PS  (12<<4)


/*-------------------------------------------------------------------------*/
/* DAQ_LIST_PROPERTIES (GET_DAQ_LIST_INFO) */

#define DAQ_LIST_PREDEFINED           0x01
#define DAQ_LIST_FIXED_EVENT          0x02
#define DAQ_LIST_DIR_DAQ              0x04
#define DAQ_LIST_DIR_STIM             0x08


/*-------------------------------------------------------------------------*/
/* EVENT_PROPERTY (GET_DAQ_EVENT_INFO) */

#define DAQ_EVENT_DIRECTION_DAQ      0x04
#define DAQ_EVENT_DIRECTION_STIM     0x08
#define DAQ_EVENT_DIRECTION_DAQ_STIM 0x0C
#define DAQ_EVENT_CONSISTENCY_DAQ    0x40
#define DAQ_EVENT_CONSISTENCY_EVENT  0x80


/*-------------------------------------------------------------------------*/
/* Comm mode programming parameter (PROGRAM_START) */

#define PI_PGM_BLOCK_DOWNLOAD      0x01
#define PI_PGM_BLOCK_UPLOAD        0x40   


/*-------------------------------------------------------------------------*/
/* PGM_PROPERTIES (GET_PGM_PROCESSOR_INFO) */

#define PGM_ACCESS_TYPE                   0x03
#define PGM_COMPRESSION_TYPE              0x0C
#define PGM_ENCRYPTION_TYPE               0x30
#define PGM_NON_SEQ_TYPE                  0xC0

/* PGM Access Mode */
#define PGM_ACCESS_ABSOLUTE               (1<<0)
#define PGM_ACCESS_FUNCTIONAL             (2<<0)
#define PGM_ACCESS_FREE                   (3<<0)

/* PGM Compression type */
#define PGM_COMPRESSION_NONE              (0<<2)
#define PGM_COMPRESSION_SUPPORTED         (1<<2)
#define PGM_COMPRESSION_REQUIRED          (3<<2)

/* PGM Encryption type */
#define PGM_ENCRYPTION_NONE               (0<<4)
#define PGM_ENCRYPTION_SUPPORTED          (1<<4)
#define PGM_ENCRYPTION_REQUIRED           (3<<4)

/* PGM non sequential programming type */
#define PGM_NON_SEQ_NONE                  (0<<6)
#define PGM_NON_SEQ_SUPPORTED             (1<<6)
#define PGM_NON_SEQ_REQUIRED              (3<<6)


/***************************************************************************/
/* XCP Commands and Responces, Type Definition */
/***************************************************************************/

/* Protocol command structure definition */
#define CRO_CMD                                         CRO_BYTE(0)
#define CRM_CMD                                         CRM_BYTE(0)
#define CRM_ERR                                         CRM_BYTE(1)
/* CONNECT */

#define CRO_CONNECT_LEN                                 2
#define CRO_CONNECT_MODE                                CRO_BYTE(1)
#define CRM_CONNECT_LEN                                 8
#define CRM_CONNECT_RESOURCE                            CRM_BYTE(1)
#define CRM_CONNECT_COMM_BASIC                          CRM_BYTE(2)
#define CRM_CONNECT_MAX_CTO_SIZE                        CRM_BYTE(3)
#define CRM_CONNECT_MAX_DTO_SIZE                        CRM_WORD(2)
#define CRM_CONNECT_PROTOCOL_VERSION                    CRM_BYTE(6)
#define CRM_CONNECT_TRANSPORT_VERSION                   CRM_BYTE(7)


/* DISCONNECT */
                                        
#define CRO_DISCONNECT_LEN                              1
#define CRM_DISCONNECT_LEN                              1


/* GET_STATUS */                                        

#define CRO_GET_STATUS_LEN                              1

#define CRM_GET_STATUS_LEN                              6
#define CRM_GET_STATUS_STATUS                           CRM_BYTE(1)
#define CRM_GET_STATUS_PROTECTION                       CRM_BYTE(2)
#define CRM_GET_STATUS_CONFIG_ID                        CRM_WORD(2)


/* SYNCH */
                                        
#define CRO_SYNCH_LEN                                   1

#define CRM_SYNCH_LEN                                   2
#define CRM_SYNCH_RESULT                                CRM_BYTE(1)
                                                 
                                                       
/* GET_COMM_MODE_INFO */

#define CRO_GET_COMM_MODE_INFO_LEN                      1

#define CRM_GET_COMM_MODE_INFO_LEN                      8
#define CRM_GET_COMM_MODE_INFO_COMM_OPTIONAL            CRM_BYTE(2)
#define CRM_GET_COMM_MODE_INFO_MAX_BS                   CRM_BYTE(4)
#define CRM_GET_COMM_MODE_INFO_MIN_ST                   CRM_BYTE(5)
#define CRM_GET_COMM_MODE_INFO_QUEUE_SIZE               CRM_BYTE(6)
#define CRM_GET_COMM_MODE_INFO_DRIVER_VERSION           CRM_BYTE(7)


/* GET_ID */
                                            
#define CRO_GET_ID_LEN                                  2
#define CRO_GET_ID_TYPE                                 CRO_BYTE(1)

#define CRM_GET_ID_LEN                                  8
#define CRM_GET_ID_MODE                                 CRM_BYTE(1)
#define CRM_GET_ID_LENGTH                               CRM_DWORD(1)
#define CRM_GET_ID_DATA                                 (&CRM_BYTE(8))

/* SET_REQUEST */

#define CRO_SET_REQUEST_LEN                             4
#define CRO_SET_REQUEST_MODE                            CRO_BYTE(1)
#define CRO_SET_REQUEST_CONFIG_ID                       CRO_WORD(1)

#define CRM_SET_REQUEST_LEN                             1

                                                        
/* GET_SEED */
                                          
#define CRO_GET_SEED_LEN                                3
#define CRO_GET_SEED_MODE                               CRO_BYTE(1)
#define CRO_GET_SEED_RESOURCE                           CRO_BYTE(2)

#define CRM_GET_SEED_LEN                                (CRM_GET_SEED_LENGTH+2u)
#define CRM_GET_SEED_LENGTH                             CRM_BYTE(1)
#define CRM_GET_SEED_DATA                               (&CRM_BYTE(2))

                                                        
/* UNLOCK */
                                            
#define CRO_UNLOCK_LEN                                  8
#define CRO_UNLOCK_LENGTH                               CRO_BYTE(1)
#define CRO_UNLOCK_KEY                                  (&CRO_BYTE(2))

#define CRM_UNLOCK_LEN                                  2
#define CRM_UNLOCK_PROTECTION                           CRM_BYTE(1)

                                                        
/* SET_MTA */

#define CRO_SET_MTA_LEN                                 8
#define CRO_SET_MTA_EXT                                 CRO_BYTE(3)
#define CRO_SET_MTA_ADDR                                CRO_DWORD(1)

#define CRM_SET_MTA_LEN                                 1


/* UPLOAD */

#define CRM_UPLOAD_MAX_SIZE                             ((uint8)(xcp.Daq.xcpMaxCTO-1))
#define CRO_UPLOAD_LEN                                  2
#define CRO_UPLOAD_SIZE                                 CRO_BYTE(1)

#define CRM_UPLOAD_LEN                                  1 /* +CRO_UPLOAD_SIZE */
#define CRM_UPLOAD_DATA                                 (&CRM_BYTE(1))


/* SHORT_UPLOAD */

#define CRO_SHORT_UPLOAD_LEN                            8
#define CRO_SHORT_UPLOAD_SIZE                           CRO_BYTE(1)
#define CRO_SHORT_UPLOAD_EXT                            CRO_BYTE(3)
#define CRO_SHORT_UPLOAD_ADDR                           CRO_DWORD(1)

#define CRM_SHORT_UPLOAD_MAX_SIZE                       ((uint8)(xcp.Daq.xcpMaxCTO-1))

#define CRM_SHORT_UPLOAD_LEN                            1 /* +CRO_SHORT_UPLOAD_SIZE */
#define CRM_SHORT_UPLOAD_DATA                           (&CRM_BYTE(1))


/* BUILD_CHECKSUM */

#define CRO_BUILD_CHECKSUM_LEN                          8
#define CRO_BUILD_CHECKSUM_SIZE                         CRO_DWORD(1)

#define CRM_BUILD_CHECKSUM_LEN                          8
#define CRM_BUILD_CHECKSUM_TYPE                         CRM_BYTE(1)
#define CRM_BUILD_CHECKSUM_RESULT                       CRM_DWORD(1)

       
/* DOWNLOAD */
                                            
#define CRO_DOWNLOAD_MAX_SIZE                           ((uint8)((xcp.Daq.xcpMaxCTO-2)))

#define CRO_DOWNLOAD_LEN                                2 /* + CRO_DOWNLOAD_SIZE */
#define CRO_DOWNLOAD_SIZE                               CRO_BYTE(1)
#define CRO_DOWNLOAD_DATA                               (&CRO_BYTE(2))

#define CRM_DOWNLOAD_LEN                                1


/* DOWNLOAD_NEXT */
                                            
#define CRO_DOWNLOAD_NEXT_MAX_SIZE                      ((uint8)((xcp.Daq.xcpMaxCTO-2)))

#define CRO_DOWNLOAD_NEXT_LEN                           2 /* + size */
#define CRO_DOWNLOAD_NEXT_SIZE                          CRO_BYTE(1)
#define CRO_DOWNLOAD_NEXT_DATA                          (&CRO_BYTE(2))

#define CRM_DOWNLOAD_NEXT_LEN                           1

                                                        
/* DOWNLOAD_MAX */

#define CRO_DOWNLOAD_MAX_MAX_SIZE                       ((uint8)(xcp.Daq.xcpMaxCTO-1))

#define CRO_DOWNLOAD_MAX_DATA                           (&CRO_BYTE(1))

#define CRM_DOWNLOAD_MAX_LEN                            1


/* SHORT_DOWNLOAD */

#define CRO_SHORT_DOWNLOAD_LEN                          8
#define CRO_SHORT_DOWNLOAD_SIZE                         CRO_BYTE(1)
#define CRO_SHORT_DOWNLOAD_EXT                          CRO_BYTE(3)
#define CRO_SHORT_DOWNLOAD_ADDR                         CRO_DWORD(1)
#define CRO_SHORT_DOWNLOAD_DATA                         (&CRO_BYTE(8))

#define CRM_SHORT_DOWNLOAD_MAX_SIZE                     ((uint8)((xcp.Daq.xcpMaxCTO-8)))
#define CRM_SHORT_DOWNLOAD_LEN                          1 /* +CRO_SHORT_UPLOAD_SIZE */

                                                        
/* MODIFY_BITS */

#define CRO_MODIFY_BITS_LEN                             6
#define CRO_MODIFY_BITS_SHIFT                           CRO_BYTE(1)
#define CRO_MODIFY_BITS_AND                             CRO_WORD(1)
#define CRO_MODIFY_BITS_XOR                             CRO_WORD(2)

#define CRM_MODIFY_BITS_LEN                             1

                                                        
/* SET_CAL_PAGE */
                                      
#define CRO_SET_CAL_PAGE_LEN                            4
#define CRO_SET_CAL_PAGE_MODE                           CRO_BYTE(1)
#define CRO_SET_CAL_PAGE_SEGMENT                        CRO_BYTE(2)
#define CRO_SET_CAL_PAGE_PAGE                           CRO_BYTE(3)

#define CRM_SET_CAL_PAGE_LEN                            1

                                                        
/* GET_CAL_PAGE */
                                      
#define CRO_GET_CAL_PAGE_LEN                            3
#define CRO_GET_CAL_PAGE_MODE                           CRO_BYTE(1)
#define CRO_GET_CAL_PAGE_SEGMENT                        CRO_BYTE(2)

#define CRM_GET_CAL_PAGE_LEN                            4
#define CRM_GET_CAL_PAGE_PAGE                           CRM_BYTE(3)


/* GET_PAG_PROCESSOR_INFO */

#define CRO_GET_PAG_PROCESSOR_INFO_LEN                  1

#define CRM_GET_PAG_PROCESSOR_INFO_LEN                  3
#define CRM_GET_PAG_PROCESSOR_INFO_MAX_SEGMENT          CRM_BYTE(1)
#define CRM_GET_PAG_PROCESSOR_INFO_PROPERTIES           CRM_BYTE(2)


/* GET_SEGMENT_INFO */

#define CRO_GET_SEGMENT_INFO_LEN                        5
#define CRO_GET_SEGMENT_INFO_MODE                       CRO_BYTE(1)
#define CRO_GET_SEGMENT_INFO_NUMBER                     CRO_BYTE(2)
#define CRO_GET_SEGMENT_INFO_MAPPING_INDEX              CRO_BYTE(3)
#define CRO_GET_SEGMENT_INFO_MAPPING                    CRO_BYTE(4)

#define CRM_GET_SEGMENT_INFO_LEN                        8
#define CRM_GET_SEGMENT_INFO_MAX_PAGES                  CRM_BYTE(1)
#define CRM_GET_SEGMENT_INFO_ADDRESS_EXTENSION          CRM_BYTE(2)
#define CRM_GET_SEGMENT_INFO_MAX_MAPPING                CRM_BYTE(3)
#define CRM_GET_SEGMENT_INFO_COMPRESSION                CRM_BYTE(4)
#define CRM_GET_SEGMENT_INFO_ENCRYPTION                 CRM_BYTE(5)
#define CRM_GET_SEGMENT_INFO_MAPPING_INFO               CRM_DWORD(1)


/* GET_PAGE_INFO */

#define CRO_GET_PAGE_INFO_LEN                           4
#define CRO_GET_PAGE_INFO_SEGMENT_NUMBER                CRO_BYTE(2)
#define CRO_GET_PAGE_INFO_PAGE_NUMBER                   CRO_BYTE(3)

#define CRM_GET_PAGE_INFO_LEN                           3
#define CRM_GET_PAGE_INFO_PROPERTIES                    CRM_BYTE(1)
#define CRM_GET_PAGE_INFO_INIT_SEGMENT                  CRM_BYTE(2)


/* SET_SEGMENT_MODE */

#define CRO_SET_SEGMENT_MODE_LEN                        3
#define CRO_SET_SEGMENT_MODE_MODE                       CRO_BYTE(1)
#define CRO_SET_SEGMENT_MODE_SEGMENT                    CRO_BYTE(2)

#define CRM_SET_SEGMENT_MODE_LEN                        1


/* GET_SEGMENT_MODE */

#define CRO_GET_SEGMENT_MODE_LEN                        3
#define CRO_GET_SEGMENT_MODE_SEGMENT                    CRO_BYTE(2)

#define CRM_GET_SEGMENT_MODE_LEN                        3
#define CRM_GET_SEGMENT_MODE_MODE                       CRM_BYTE(2)


/* COPY_CAL_PAGE */

#define CRO_COPY_CAL_PAGE_LEN                           5
#define CRO_COPY_CAL_PAGE_SRC_SEGMENT                   CRO_BYTE(1)
#define CRO_COPY_CAL_PAGE_SRC_PAGE                      CRO_BYTE(2)
#define CRO_COPY_CAL_PAGE_DEST_SEGMENT                  CRO_BYTE(3)
#define CRO_COPY_CAL_PAGE_DEST_PAGE                     CRO_BYTE(4)

#define CRM_COPY_CAL_PAGE_LEN                           1


/* CLEAR_DAQ_LIST */

#define CRO_CLEAR_DAQ_LIST_LEN                          4
#define CRO_CLEAR_DAQ_LIST_DAQ                          CRO_WORD(1)

#define CRM_CLEAR_DAQ_LIST_LEN                          1

                                                        
/* SET_DAQ_PTR */

#define CRO_SET_DAQ_PTR_LEN                             6
#define CRO_SET_DAQ_PTR_DAQ                             CRO_WORD(1)
#define CRO_SET_DAQ_PTR_ODT                             CRO_BYTE(4)
#define CRO_SET_DAQ_PTR_IDX                             CRO_BYTE(5)

#define CRM_SET_DAQ_PTR_LEN                             1


/* WRITE_DAQ */

#define CRO_WRITE_DAQ_LEN                               8
#define CRO_WRITE_DAQ_BITOFFSET                         CRO_BYTE(1)
#define CRO_WRITE_DAQ_SIZE                              CRO_BYTE(2)
#define CRO_WRITE_DAQ_EXT                               CRO_BYTE(3)
#define CRO_WRITE_DAQ_ADDR                              CRO_DWORD(1)

#define CRM_WRITE_DAQ_LEN                               1


/* WRITE_DAQ_MULTIPLE */
#define CRO_WRITE_DAQ_MULTIPLE_LEN                      8
#define CRO_WRITE_DAQ_MULTIPLE_COMMAND                  CRO_BYTE(0)
#define CRO_WRITE_DAQ_MULTIPLE_NODAQ                    CRO_BYTE(1)
#define CRO_WRITE_DAQ_MULTIPLE_BITOFFSET(i)             CRO_BYTE(2 + (8*(i))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define CRO_WRITE_DAQ_MULTIPLE_SIZE(i)                  CRO_BYTE(3 + (8*(i))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define CRO_WRITE_DAQ_MULTIPLE_EXT(i)                   CRO_BYTE(8 + (8*(i))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define CRO_WRITE_DAQ_MULTIPLE_ADDR(i)                  CRO_DWORD(1 + (2*(i))) /* PRQA S 3453 */ /* MD_MSR_19.7 */

#define CRM_WRITE_DAQ_MULTIPLE_LEN                      1


/* SET_DAQ_LIST_MODE */

#define CRO_SET_DAQ_LIST_MODE_LEN                       8
#define CRO_SET_DAQ_LIST_MODE_MODE                      CRO_BYTE(1)
#define CRO_SET_DAQ_LIST_MODE_DAQ                       CRO_WORD(1)
#define CRO_SET_DAQ_LIST_MODE_EVENTCHANNEL              CRO_WORD(2)
#define CRO_SET_DAQ_LIST_MODE_PRESCALER                 CRO_BYTE(6)
#define CRO_SET_DAQ_LIST_MODE_PRIORITY                  CRO_BYTE(7)

#define CRM_SET_DAQ_LIST_MODE_LEN                       6


/* GET_DAQ_LIST_MODE */

#define CRO_GET_DAQ_LIST_MODE_LEN                       4
#define CRO_GET_DAQ_LIST_MODE_DAQ                       CRO_WORD(1)

#define CRM_GET_DAQ_LIST_MODE_LEN                       8
#define CRM_GET_DAQ_LIST_MODE_MODE                      CRM_BYTE(1)
#define CRM_GET_DAQ_LIST_MODE_EVENTCHANNEL              CRM_WORD(2)
#define CRM_GET_DAQ_LIST_MODE_PRESCALER                 CRM_BYTE(6)
#define CRM_GET_DAQ_LIST_MODE_PRIORITY                  CRM_BYTE(7)


/* START_STOP_DAQ_LIST */
                                        
#define CRO_START_STOP_LEN                              4
#define CRO_START_STOP_MODE                             CRO_BYTE(1)
#define CRO_START_STOP_DAQ                              CRO_WORD(1)

#define CRM_START_STOP_LEN                              2
#define CRM_START_STOP_FIRST_PID                        CRM_BYTE(1)


/* START_STOP_SYNCH */
  
#define CRO_START_STOP_SYNC_LEN                         2
#define CRO_START_STOP_SYNC_MODE                        CRO_BYTE(1)

#define CRM_START_STOP_SYNC_LEN                         1


/* GET_DAQ_CLOCK */

#define CRO_GET_DAQ_CLOCK_LEN                           1

#define CRM_GET_DAQ_CLOCK_LEN                           8
#define CRM_GET_DAQ_CLOCK_TIME                          CRM_DWORD(1)


/* READ_DAQ */

#define CRO_READ_DAQ_LEN                                1

#define CRM_READ_DAQ_LEN                                8
#define CRM_READ_DAQ_BITOFFSET                          CRM_BYTE(1)
#define CRM_READ_DAQ_SIZE                               CRM_BYTE(2)
#define CRM_READ_DAQ_EXT                                CRM_BYTE(3)
#define CRM_READ_DAQ_ADDR                               CRM_DWORD(1)


/* GET_DAQ_PROCESSOR_INFO */

#define CRO_GET_DAQ_PROCESSOR_INFO_LEN                  1

#define CRM_GET_DAQ_PROCESSOR_INFO_LEN                  8
#define CRM_GET_DAQ_PROCESSOR_INFO_PROPERTIES           CRM_BYTE(1)
#define CRM_GET_DAQ_PROCESSOR_INFO_MAX_DAQ              CRM_WORD(1)
#define CRM_GET_DAQ_PROCESSOR_INFO_MAX_EVENT            CRM_WORD(2)
#define CRM_GET_DAQ_PROCESSOR_INFO_MIN_DAQ              CRM_BYTE(6)
#define CRM_GET_DAQ_PROCESSOR_INFO_DAQ_KEY_BYTE         CRM_BYTE(7)


/* GET_DAQ_RESOLUTION_INFO */
                                
#define CRO_GET_DAQ_RESOLUTION_INFO_LEN                 1

#define CRM_GET_DAQ_RESOLUTION_INFO_LEN                 8
#define CRM_GET_DAQ_RESOLUTION_INFO_GRANULARITY_DAQ     CRM_BYTE(1)
#define CRM_GET_DAQ_RESOLUTION_INFO_MAX_SIZE_DAQ        CRM_BYTE(2)
#define CRM_GET_DAQ_RESOLUTION_INFO_GRANULARITY_STIM    CRM_BYTE(3)
#define CRM_GET_DAQ_RESOLUTION_INFO_MAX_SIZE_STIM       CRM_BYTE(4)
#define CRM_GET_DAQ_RESOLUTION_INFO_TIMESTAMP_MODE      CRM_BYTE(5)
#define CRM_GET_DAQ_RESOLUTION_INFO_TIMESTAMP_TICKS     CRM_WORD(3)

                                                        
/* GET_DAQ_LIST_INFO */

#define CRO_GET_DAQ_LIST_INFO_LEN                       4
#define CRO_GET_DAQ_LIST_INFO_DAQ                       CRO_WORD(1)

#define CRM_GET_DAQ_LIST_INFO_LEN                       6
#define CRM_GET_DAQ_LIST_INFO_PROPERTIES                CRM_BYTE(1)
#define CRM_GET_DAQ_LIST_INFO_MAX_ODT                   CRM_BYTE(2)
#define CRM_GET_DAQ_LIST_INFO_MAX_ODT_ENTRY             CRM_BYTE(3)
#define CRM_GET_DAQ_LIST_INFO_FIXED_EVENT               CRM_WORD(2)


/* GET_DAQ_EVENT_INFO */

#define CRO_GET_DAQ_EVENT_INFO_LEN                      4
#define CRO_GET_DAQ_EVENT_INFO_EVENT                    CRO_WORD(1)

#define CRM_GET_DAQ_EVENT_INFO_LEN                      7
#define CRM_GET_DAQ_EVENT_INFO_PROPERTIES               CRM_BYTE(1)
#define CRM_GET_DAQ_EVENT_INFO_MAX_DAQ_LIST             CRM_BYTE(2)
#define CRM_GET_DAQ_EVENT_INFO_NAME_LENGTH              CRM_BYTE(3)
#define CRM_GET_DAQ_EVENT_INFO_TIME_CYCLE               CRM_BYTE(4)
#define CRM_GET_DAQ_EVENT_INFO_TIME_UNIT                CRM_BYTE(5)
#define CRM_GET_DAQ_EVENT_INFO_PRIORITY                 CRM_BYTE(6)


/* FREE_DAQ */

#define CRO_FREE_DAQ_LEN                                1

#define CRM_FREE_DAQ_LEN                                1


/* ALLOC_DAQ */

#define CRO_ALLOC_DAQ_LEN                               4
#define CRO_ALLOC_DAQ_COUNT                             CRO_WORD(1)

#define CRM_ALLOC_DAQ_LEN                               1


/* ALLOC_ODT */

#define _CRO_ALLOC_ODT_LEN                              3
#define _CRO_ALLOC_ODT_DAQ                              CRO_WORD(1)
#define _CRO_ALLOC_ODT_COUNT                            CRO_BYTE(1)

#define CRO_ALLOC_ODT_LEN                               5
#define CRO_ALLOC_ODT_DAQ                               CRO_WORD(1)
#define CRO_ALLOC_ODT_COUNT                             CRO_BYTE(4)

#define CRM_ALLOC_ODT_LEN                               1


/* ALLOC_ODT_ENTRY */

#define CRO_ALLOC_ODT_ENTRY_LEN                         6
#define CRO_ALLOC_ODT_ENTRY_DAQ                         CRO_WORD(1)
#define CRO_ALLOC_ODT_ENTRY_ODT                         CRO_BYTE(4)
#define CRO_ALLOC_ODT_ENTRY_COUNT                       CRO_BYTE(5)

#define CRM_ALLOC_ODT_ENTRY_LEN                         1


/* PROGRAM_START */
                                     
#define CRO_PROGRAM_START_LEN                           1

#define CRM_PROGRAM_START_LEN                           7
#define CRM_PROGRAM_COMM_MODE_PGM                       CRM_BYTE(2) 
#define CRM_PROGRAM_MAX_CTO_PGM                         CRM_BYTE(3) 
#define CRM_PROGRAM_MAX_BS_PGM                          CRM_BYTE(4) 
#define CRM_PROGRAM_MIN_ST_PGM                          CRM_BYTE(5) 
#define CRM_PROGRAM_QUEUE_SIZE_PGM                      CRM_BYTE(6) 

                                                        
/* PROGRAM_CLEAR */
                                     
#define CRO_PROGRAM_CLEAR_LEN                           8
#define CRO_PROGRAM_CLEAR_MODE                          CRO_BYTE(1)
#define CRO_PROGRAM_CLEAR_SIZE                          CRO_DWORD(1)

#define CRM_PROGRAM_CLEAR_LEN                           1

                                                        
/* PROGRAM */

#define CRO_PROGRAM_MAX_SIZE                            ((uint8)((xcp.Daq.xcpMaxCTO-2)))
                                           
#define CRO_PROGRAM_LEN                                 2 /* + CRO_PROGRAM_SIZE */ 
#define CRO_PROGRAM_SIZE                                CRO_BYTE(1)
#define CRO_PROGRAM_DATA                                (&CRO_BYTE(2))

#define CRM_PROGRAM_LEN                                 1


/* PROGRAM RESET */

#define CRO_PROGRAM_RESET_LEN                           1

#define CRM_PROGRAM_RESET_LEN                           1

                                                        
/*GET_PGM_PROCESSOR_INFO*/

#define CRO_GET_PGM_PROCESSOR_INFO_LEN                  1

#define CRM_GET_PGM_PROCESSOR_INFO_LEN                  3
#define CRM_GET_PGM_PROCESSOR_INFO_PROPERTIES           CRM_BYTE(1)
#define CRM_GET_PGM_PROCESSOR_INFO_MAX_SECTOR           CRM_BYTE(2)

 
/* GET_SECTOR_INFO */

#define CRO_PROGRAM_GET_SECTOR_INFO_LEN                 3
#define CRO_PROGRAM_GET_SECTOR_INFO_MODE                CRO_BYTE(1)
#define CRO_PROGRAM_GET_SECTOR_INFO_NUMBER              CRO_BYTE(2)

#define CRM_PROGRAM_GET_SECTOR_INFO_LEN                 8
#define CRM_PROGRAM_GET_SECTOR_CLEAR_SEQ_NUM            CRM_BYTE(1)
#define CRM_PROGRAM_GET_SECTOR_PGM_SEQ_NUM              CRM_BYTE(2)
#define CRM_PROGRAM_GET_SECTOR_PGM_METHOD               CRM_BYTE(3)
#define CRM_PROGRAM_GET_SECTOR_SECTOR_INFO              CRM_DWORD(1)
#define CRM_PROGRAM_GET_SECTOR_NAME_LENGTH              CRM_BYTE(1)


/* PROGRAM_PREPARE */
                                   
#define CRO_PROGRAM_PREPARE_LEN                         4
#define CRO_PROGRAM_PREPARE_SIZE                        CRO_WORD(1)

#define CRM_PROGRAM_PREPARE_LEN                         1


/* PROGRAM_FORMAT */

#define CRO_PROGRAM_FORMAT_LEN                          5
#define CRO_PROGRAM_FORMAT_COMPRESSION_METHOD           CRO_BYTE(1)
#define CRO_PROGRAM_FORMAT_ENCRYPTION_METHOD            CRO_BYTE(2)
#define CRO_PROGRAM_FORMAT_PROGRAMMING_METHOD           CRO_BYTE(3)
#define CRO_PROGRAM_FORMAT_ACCESS_METHOD                CRO_BYTE(4)

#define CRM_PROGRAM_FORMAT_LEN                          1


/* PROGRAM_NEXT */

#define CRO_PROGRAM_NEXT_MAX_SIZE                       ((uint8)((xcp.Daq.xcpMaxCTO-2)))

#define CRO_PROGRAM_NEXT_LEN                            2 /* + size */
#define CRO_PROGRAM_NEXT_SIZE                           CRO_BYTE(1)
#define CRO_PROGRAM_NEXT_DATA                           (&CRO_BYTE(2))

#define CRM_PROGRAM_NEXT_LEN                            3
#define CRM_PROGRAM_NEXT_ERR_SEQUENCE                   CRM_BYTE(1)
#define CRM_PROGRAM_NEXT_SIZE_EXPECTED_DATA             CRM_BYTE(2)


/* PROGRAM_MAX */

#define CRO_PROGRAM_MAX_MAX_SIZE                        ((uint8)((xcp.Daq.xcpMaxCTO-1)))
                                       
#define CRO_PROGRAM_MAX_DATA                            (&CRO_BYTE(1))

#define CRM_PROGRAM_MAX_LEN                             1


/* PROGRAM_VERIFY */

#define CRO_PROGRAM_VERIFY_LEN                          8
#define CRO_PROGRAM_VERIFY_MODE                         CRO_BYTE(1)
#define CRO_PROGRAM_VERIFY_TYPE                         CRO_WORD(1)
#define CRO_PROGRAM_VERIFY_VALUE                        CRO_DWORD(1)

#define CRM_PROGRAM_VERIFY_LEN                          1


/* GET_SLAVE_ID */

#define CRO_GET_SLAVE_ID_LEN                            6
#define CRO_GET_SLAVE_ID_SUB_CODE                       CRO_BYTE(1)
#define CRO_GET_SLAVE_ID_X                              CRO_BYTE(2)
#define CRO_GET_SLAVE_ID_C                              CRO_BYTE(3)
#define CRO_GET_SLAVE_ID_P                              CRO_BYTE(4)
#define CRO_GET_SLAVE_ID_MODE                           CRO_BYTE(5)

#define CRM_GET_SLAVE_ID_LEN                            8
#define CRM_GET_SLAVE_ID_X                              CRM_BYTE(1)
#define CRM_GET_SLAVE_ID_C                              CRM_BYTE(2)
#define CRM_GET_SLAVE_ID_P                              CRM_BYTE(3)
#define CRM_GET_SLAVE_ID_CAN_ID_CMD_STIM                CRM_DWORD(1)

                                                        
/* GET_DAQ_ID */
                                   
#define CRO_GET_DAQ_ID_LEN                              3
#define CRO_GET_DAQ_ID_SUB_CODE                         CRO_BYTE(1)
#define CRO_GET_DAQ_ID_DAQ                              CRO_WORD(1)

#define CRM_GET_DAQ_ID_LEN                              8
#define CRM_GET_DAQ_ID_FIXED                            CRM_BYTE(1)
#define CRM_GET_DAQ_ID_ID                               CRM_DWORD(1)


/* SET_DAQ_ID */
                                   
#define CRO_SET_DAQ_ID_LEN                              8
#define CRO_SET_DAQ_ID_SUB_CODE                         CRO_BYTE(1)
#define CRO_SET_DAQ_ID_DAQ                              CRO_WORD(1)
#define CRO_SET_DAQ_ID_ID                               CRO_DWORD(1)

#define CRM_SET_DAQ_ID_LEN                              1

/* SET_SLAVE_PORT */

#define CRO_SET_SLAVE_PORT_LEN                          4
#define CRO_SET_SLAVE_PORT_SUB_CODE                     CRO_BYTE(1)
#define CRO_SET_SLAVE_PORT_PORT                         CRO_WORD(1)

#define CRM_SET_SLAVE_PORT                              1  

#if defined ( XCP_ENABLE_GET_SESSION_STATUS_API )
  #define XCP_DISCONNECTED                              0u
  #define XCP_CONNECTED                                 1u
#endif


/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/



#if defined ( XCP_ENABLE_SEND_EVENT ) || defined ( XCP_ENABLE_SERV_TEXT )
  #define EV_BYTE(x)            (xcp.Ev.b[x]) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#endif

#define CRO_BYTE(x)             (pCmd->b[x]) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define CRO_WORD(x)             (pCmd->w[x]) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define CRO_DWORD(x)            (pCmd->dw[x]) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define CRM_BYTE(x)             (xcp.Crm.b[x]) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define CRM_WORD(x)             (xcp.Crm.w[x]) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define CRM_DWORD(x)            (xcp.Crm.dw[x]) /* PRQA S 3453 */ /* MD_MSR_19.7 */




/****************************************************************************/
/* Default data type definitions                                            */
/****************************************************************************/

#if !defined ( STATIC )
  #define STATIC static
#endif

#if !defined ( FUNC )
  #define FUNC(rettype, memclass) rettype
#endif

#if !defined ( P2VAR )
  #define P2VAR(ptrtype, memclass, ptrclass) ptrtype * ptrclass
#endif

#if !defined ( P2CONST )
  #define P2CONST(ptrtype, memclass, ptrclass) const ptrtype * ptrclass
#endif

#if !defined ( CONST )
  #define CONST(type, memclass) const type
#endif

#if !defined ( VAR )
  #define VAR(vartype, memclass) vartype
#endif

#if !defined ( XCP_APPL_DATA )
  #define XCP_APPL_DATA
#endif


/*
   DAQBYTEPTR and MTABYTEPTR may be defined different to BYTEPTR to save memory
   Example:
     #define BYTEPTR     unsigned char *
     #define MTABYTEPTR  huge unsigned char *
     #define DAQBYTEPTR  unsigned char *
*/
#if !defined ( DAQBYTEPTR ) && defined ( XCP_MEMORY_MODEL_PAGED ) 
#endif
#if defined ( DAQBYTEPTR )
#else
  #define DAQBYTEPTR P2VAR(uint8, AUTOMATIC, XCP_DAQ_DATA)
#endif
#if !defined ( ROMDAQBYTEPTR ) && defined ( XCP_MEMORY_MODEL_PAGED ) 
#endif
#if defined ( ROMDAQBYTEPTR )
#else
  #define ROMDAQBYTEPTR P2CONST(uint8, AUTOMATIC, XCP_DAQ_DATA)
#endif

#if !defined ( MTABYTEPTR ) && defined ( XCP_MEMORY_MODEL_PAGED ) 
#endif
#if defined ( MTABYTEPTR )
#else
  #define MTABYTEPTR P2VAR(uint8, AUTOMATIC, XCP_MTA_DATA)
#endif
#if !defined ( ROMMTABYTEPTR ) && defined ( XCP_MEMORY_MODEL_PAGED ) 
#endif
#if defined ( ROMMTABYTEPTR )
#else
  #define ROMMTABYTEPTR P2CONST(uint8, AUTOMATIC, XCP_MTA_DATA)
#endif

/* Pointer type used to point into the xcp structure */
#if defined ( BYTEPTR )
#else
  #define BYTEPTR P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)
#endif
#if defined ( ROMBYTEPTR )
#else
  #define ROMBYTEPTR P2CONST(uint8, AUTOMATIC, XCP_APPL_DATA)
#endif


/****************************************************************************/
/* Checks and default values                                                */
/****************************************************************************/

/* Turn off test instrumentation, if not used */
#if !defined(XCP_ASSERT)
  #define XCP_ASSERT(x) 
#endif
#if !defined(XCP_PRINT)
  #define XCP_PRINT(x) 
#endif

/* Check limits of the XCP imnplementation
*/
#if defined ( kXcpMaxCTOMax )
  #if ( kXcpMaxCTOMax > 255 )
    #error "kXcpMaxCTOMax must be < 256"
  #endif
  #if ( kXcpMaxCTOMax < 8 )
    #error "kXcpMaxCTOMax must be > 7"
  #endif
#else
  #error "kXcpMaxCTOMax must be defined!"
#endif

#if defined ( kXcpMaxDTOMax )
  #if ( kXcpMaxDTOMax > 255 )
    #error "kXcpMaxDTOMax must be < 256"
  #endif
  #if ( kXcpMaxDTOMax < 8 )
    #error "kXcpMaxDTOMax must be > 7"
  #endif
#else
  #error "kXcpMaxDTOMax must be defined!"
#endif


#if defined ( XCP_ENABLE_DAQ )

/* kXcpDaqMemSize must be defined 
*/
  #if defined ( kXcpDaqMemSize )
  #else
    #error "Please define kXcpDaqMemSize"
  #endif

/* Use send queue as default
*/
  #if defined ( XCP_ENABLE_SEND_QUEUE ) || defined ( XCP_DISABLE_SEND_QUEUE )
  #else
    #define XCP_ENABLE_SEND_QUEUE
  #endif 

/*
  Max. size of an object referenced by an ODT entry
  XCP_MAX_ODT_ENTRY_SIZE may be limited 
*/
  #if defined ( XCP_MAX_ODT_ENTRY_SIZE )
  #else
    #if defined ( XCP_ENABLE_DAQ_HDR_ODT_DAQ )
      #define XCP_MAX_ODT_ENTRY_SIZE (xcp.Daq.xcpMaxDTO-2)
    #else
      #define XCP_MAX_ODT_ENTRY_SIZE (xcp.Daq.xcpMaxDTO-1)
    #endif
  #endif

#else /* XCP_ENABLE_DAQ */
  #if defined ( XCP_ENABLE_WRITE_DAQ_MULTIPLE )
    #error "Please activate DAQ measurement first!"
  #endif
#endif /* XCP_ENABLE_DAQ */



/****************************************************************************/
/* XCP Packet Type Definition                                               */
/****************************************************************************/

typedef struct {
  uint8 b[kXcpMaxDTOMax];
  uint8 l;
} tXcpDtouS;

typedef union {
  tXcpDtouS buffer;
#if defined ( XCP_ENABLE_ALIGNED_DTO )
  uint16 w[ ((kXcpMaxDTOMax + 3) & 0xFFFC) / 2  ];
  uint32 dw[ ((kXcpMaxDTOMax + 3) & 0xFFFC) / 4 ];
#endif
} tXcpDto;

typedef union { /* PRQA S 0750 */ /* MD_MSR_18.4 */
  /* There might be a loss of up to 3 bytes. */
  uint8  b[ ((kXcpMaxCTOMax + 3) & 0xFFC)      ];
  uint16 w[ ((kXcpMaxCTOMax + 3) & 0xFFC) / 2  ];
  uint32 dw[ ((kXcpMaxCTOMax + 3) & 0xFFC) / 4 ];
} tXcpCto;


/****************************************************************************/
/* DAQ Lists, Type Definition                                               */
/****************************************************************************/

/* Note:
   - Adressextensions are not used for DAQ
*/

#if defined ( XCP_ENABLE_DAQ )

/* ODT */
/* Size must be even !!! */
typedef struct {

  uint16 firstOdtEntry;       /* Absolute */
  uint16 lastOdtEntry;        /* Absolute */

  #if defined ( XCP_ENABLE_STIM )
  P2VAR(tXcpDto, AUTOMATIC, XCP_APPL_DATA) StimBuffer; 
  #endif

} tXcpOdt;

#if defined( XCP_ENABLE_ODT_SIZE_WORD )
typedef uint16 tXcpOdtIdx;
typedef uint16 tXcpOdtCnt;
#else
typedef uint8 tXcpOdtIdx;
typedef uint8 tXcpOdtCnt;
#endif

#if defined ( XCP_ENABLE_EXTENDED_EVENTS )
typedef uint16 tXcpEventType;
#else
typedef uint8 tXcpEventType;
#endif


/* DAQ list */
typedef struct {

  tXcpOdtIdx lastOdt;             /* Absolute */
  tXcpOdtIdx firstOdt;            /* Absolute */

  uint8 flags;

  #if defined ( kXcpMaxEvent ) && ! defined ( XCP_ENABLE_STIM )
  /* Event-Daq association array used */
  #else
  tXcpEventType eventChannel;
  #endif

  #if defined ( XCP_ENABLE_DAQ_PRESCALER )
  uint8 prescaler;  
  uint8 cycle;     
  #endif

} tXcpDaqList;

#endif /* XCP_ENABLE_DAQ */

/* Dynamic DAQ list structures */
typedef struct {

  uint8 activeTl;                 /* Active Transport Layer */
  uint8 xcpMaxCTO;                /* Current Max CTO */
  uint8 xcpMaxDTO;                /* Current Max DTO */

#if defined ( XCP_ENABLE_DAQ )    /* Data Acquisition */

  #if defined ( XCP_ENABLE_SEND_QUEUE )
  uint8           SendQueueBehaviour; /* Send Queue Behaviour - has to be set by Xcp: 0 = linear mode, 1 = ring buffer mode */
  #endif

  uint8           DaqCount;
  tXcpOdtCnt      OdtCount;       /* Absolute count */
  uint16          OdtEntryCount;  /* Absolute count */

  /* Session configuration id for resume mode */
  #if defined ( XCP_ENABLE_DAQ_RESUME )
  uint16 DaqConfigId;
  #endif

  /* Event-Daq association array */ 
  #if defined ( kXcpMaxEvent ) && ! defined ( XCP_ENABLE_STIM )
  uint8 EventDaq[kXcpMaxEvent];
  #endif

  union { /* PRQA S 0750 */ /* MD_MSR_18.4 */
    uint8         b[kXcpDaqMemSize];
    tXcpDaqList   DaqList[1];
  } u;

#endif /* XCP_ENABLE_DAQ */

} tXcpDaq;

typedef uint16 SessionStatusType;

#if defined ( XCP_ENABLE_DAQ )            /* Data Acquisition */

#if defined ( XCP_ENABLE_DAQ_TIMESTAMP )
  #if ( kXcpDaqTimestampSize == DAQ_TIMESTAMP_BYTE )
    typedef uint8 XcpDaqTimestampType;
  #elif ( kXcpDaqTimestampSize == DAQ_TIMESTAMP_WORD )
    typedef uint16 XcpDaqTimestampType;
  #elif ( kXcpDaqTimestampSize == DAQ_TIMESTAMP_DWORD )
    typedef uint32 XcpDaqTimestampType;
  #else
    #error "kXcpDaqTimestampSize not defined. Please define a valid timestamp type!"
  #endif
#endif


  /* Shortcuts */

  /* j is absolute odt number */
  #define DaqListOdtEntryCount(j) ((xcp.pOdt[j].lastOdtEntry-xcp.pOdt[j].firstOdtEntry)+1) /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define DaqListOdtLastEntry(j)  (xcp.pOdt[j].lastOdtEntry) /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define DaqListOdtFirstEntry(j) (xcp.pOdt[j].firstOdtEntry) /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define DaqListOdtStimBuffer(j) (xcp.pOdt[j].StimBuffer) /* PRQA S 3453 */ /* MD_MSR_19.7 */

  /* n is absolute odtEntry number */
  #define OdtEntrySize(n)         (xcp.pOdtEntrySize[n]) /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define OdtEntryAddr(n)         (xcp.pOdtEntryAddr[n]) /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define OdtEntryExt(n)          (xcp.pOdtEntryExt[n]) /* PRQA S 3453 */ /* MD_MSR_19.7 */

  /* i is daq number */
  #define DaqListOdtCount(i)      ((xcp.Daq.u.DaqList[i].lastOdt-xcp.Daq.u.DaqList[i].firstOdt)+1) /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define DaqListLastOdt(i)       xcp.Daq.u.DaqList[i].lastOdt /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define DaqListFirstOdt(i)      xcp.Daq.u.DaqList[i].firstOdt /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define DaqListFirstPid(i)      xcp.Daq.u.DaqList[i].firstOdt /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define DaqListFlags(i)         xcp.Daq.u.DaqList[i].flags /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define DaqListEventChannel(i)  xcp.Daq.u.DaqList[i].eventChannel /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define DaqListPrescaler(i)     xcp.Daq.u.DaqList[i].prescaler /* PRQA S 3453 */ /* MD_MSR_19.7 */
  #define DaqListCycle(i)         xcp.Daq.u.DaqList[i].cycle /* PRQA S 3453 */ /* MD_MSR_19.7 */


#endif /* XCP_ENABLE_DAQ */


/****************************************************************************/
/* Checksum, Type Definition                                                */
/****************************************************************************/
#if defined ( XCP_ENABLE_CHECKSUM )
  #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD11 ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD12 ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD14 ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_CRC16 ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_CRC16CCITT ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_CRC32 )
  typedef uint8 tXcpChecksumAddType;    /* Data type (width) of the data to be added.  */
  #endif
  #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD22 ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD24 )
  typedef uint16 tXcpChecksumAddType;   /* Data type (width) of the data to be added.  */
  #endif
  #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD44 )
  typedef uint32 tXcpChecksumAddType;   /* Data type (width) of the data to be added.  */
  #endif

  #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD11 )
  typedef uint8 tXcpChecksumSumType;    /* Data type (width) of the actually checksum. */
  #endif
  #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD12 ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD22 ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_CRC16 ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_CRC16CCITT )
  typedef uint16 tXcpChecksumSumType;   /* Data type (width) of the actually checksum. */
  #endif
  #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD14 ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD24 ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD44 ) || \
      ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_CRC32 ) 
  typedef uint32 tXcpChecksumSumType;   /* Data type (width) of the actually checksum. */
  #endif
#endif


/****************************************************************************/
/* XCP Segment CAL parameters                                               */
/* Sement info                                                              */
/****************************************************************************/

#if defined ( XCP_ENABLE_PAGE_INFO )
typedef struct {
    uint8  SegmentInfoMaxPages; 
    uint8  SegmentInfoInitSegment; 
    uint8  SegmentInfoAddressExtension;
    uint8  SegmentInfoMaxMapping;
    uint8  SegmentInfoMode;
    uint8  SegmentPageProperties[kXcpMaxPages];
    uint8  SegmentPageAktiv[kXcpMaxPages];        /* 1=aktiv, 0=deaktiv. */
    uint8  SegmentPageMode[kXcpMaxPages];         /* 1=ECU, 2=XCP */
    uint32 SegmentInfoMapping;
} tXcpSegmentInfo;
#endif


/****************************************************************************/
/* XCP Driver Variables, Type Definition                                    */
/****************************************************************************/

/* Return values */
#define XCP_CMD_DENIED              0
#define XCP_CMD_OK                  1
#define XCP_CMD_PENDING             2
#define XCP_CMD_SYNTAX              3
#define XCP_CMD_BUSY                4
#define XCP_CMD_UNKNOWN             5
#define XCP_CMD_OUT_OF_RANGE        6
#define XCP_MODE_NOT_VALID          7
#define XCP_CMD_ERROR               0xFF

/* Return values for XcpEvent() */
#define XCP_EVENT_NOP               0x00u   /* Inactive (DAQ not running, Event not configured) */
#define XCP_EVENT_DAQ               0x01u   /* DAQ active */
#define XCP_EVENT_DAQ_OVERRUN       0x02u   /* DAQ queue overflow */
#define XCP_EVENT_STIM              0x04u   /* STIM active */
#define XCP_EVENT_STIM_OVERRUN      0x08u   /* STIM data not available */

/* Bitmasks for xcp.SendStatus */
#define XCP_CRM_REQUEST             0x01u
#define XCP_DTO_REQUEST             0x02u
#define XCP_EVT_REQUEST             0x04u
#define XCP_CRM_PENDING             0x10u
#define XCP_DTO_PENDING             0x20u
#define XCP_EVT_PENDING             0x40u
#define XCP_SEND_PENDING            (XCP_DTO_PENDING|XCP_CRM_PENDING|XCP_EVT_PENDING)

typedef struct {
  /* Crm has to be the first object of this structure !! (refer to XcpInit()) */

  tXcpCto Crm;                           /* RES,ERR Message buffer */
  uint8   CrmLen;                        /* RES,ERR Message length */

#if defined ( XCP_ENABLE_SEND_EVENT ) || defined ( XCP_ENABLE_SERV_TEXT )
  tXcpCto Ev;                            /* EV,SERV Message buffer */
  uint8   EvLen;                         /* EV,SERV Message length */
#endif
  
  SessionStatusType SessionStatus;

  MTABYTEPTR Mta;                        /* Memory Transfer Address */
#if defined ( XCP_ENABLE_READCCCONFIG )
  uint8      MtaExt;
#endif

#if defined ( XCP_ENABLE_BLOCK_DOWNLOAD ) || defined (XCP_ENABLE_BLOCK_UPLOAD)
  uint8 NextDataBlockSize;
#endif

#if defined ( XCP_ENABLE_SEED_KEY )
  uint8 ProtectionStatus;                /* Resource Protection Status */
#endif

#if defined ( XCP_ENABLE_CHECKSUM ) && !defined ( XCP_ENABLE_CUSTOM_CRC )
  uint16              CheckSumSize;       /* Counter for checksum calculation */
  tXcpChecksumSumType CheckSum;           /* Actual checksum */
#endif

  /*
    Dynamic DAQ list structures
    This structure should be stored in resume mode
  */
  tXcpDaq Daq;

#if defined ( XCP_ENABLE_DAQ )            /* Data Acquisition */

  P2VAR(tXcpOdt, AUTOMATIC, XCP_APPL_DATA)  pOdt;
  P2VAR(DAQBYTEPTR, AUTOMATIC, XCP_APPL_DATA) pOdtEntryAddr;
  P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)    pOdtEntrySize;
#if defined ( XCP_ENABLE_VIRTUAL_MEASUREMENT )
  P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA)    pOdtEntryExt;
#endif
  
  /* Transmit Queue */
  #if defined ( XCP_ENABLE_SEND_QUEUE )
  P2VAR(tXcpDto, AUTOMATIC, XCP_APPL_DATA)  pQueue;
  uint16   QueueSize;
  uint16   QueueLen;
  uint16   QueueRp;
  #endif

  /* Transmit Status */
  #if defined ( XCP_ENABLE_SEND_QUEUE)
  volatile uint8 SendStatus;
  #endif

  /* Pointer for SET_DAQ_PTR */
  uint16 DaqListPtr;           
    
  #if defined ( XCP_ENABLE_STIM )
  tXcpDto StimBuffer[kXcpStimOdtCount];
  #endif
    
#endif /* XCP_ENABLE_DAQ */

} tXcpData;

#if defined ( XCP_ENABLE_VECTOR_INFOMEM )
typedef struct {
  uint16  MajorVersion;
  uint16  Patchversion;
  uint16  DaqMemory;
  uint16  StimOdtCount;
} tInfoMem;
#endif

typedef P2VAR(tXcpData, TYPEDEF, XCP_APPL_DATA) tXcpDataPtr;

/***************************************************************************/
/* External Declarations                                                   */
/***************************************************************************/

/*******************************************************************************
* External 8 Bit Constants
*******************************************************************************/
#define XCP_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONST(uint8, XCP_CONST) kXcpMainVersion;
extern CONST(uint8, XCP_CONST) kXcpSubVersion;
extern CONST(uint8, XCP_CONST) kXcpReleaseVersion;

#define XCP_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/****************************************************************************/
/* Prototypes                                                               */
/****************************************************************************/


/* Important external functions of xcp.c */
/*-----------------------------------------*/
#define XCP_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Initialization and deinitialization functions for the XCP Protocol Layer. */
extern FUNC(void, XCP_CODE) XcpInitMemory( void );
extern FUNC(void, XCP_CODE) XcpInit( void );
extern FUNC(void, XCP_CODE) XcpExit( void );

/* Trigger a XCP data acquisition or stimulation event */
/* Returns an error status XCP_EVENT_xxxx */
#if defined ( XCP_ENABLE_DAQ )
  extern FUNC(uint8, XCP_CODE) XcpEvent( tXcpEventType event );
  #if defined ( XCP_ENABLE_VIRTUAL_MEASUREMENT )
  extern FUNC(uint8, XCP_CODE) XcpExtendedEvent( tXcpEventType event, uint8 numBuffers, P2CONST(void, AUTOMATIC, XCP_APPL_DATA) virtAddress[],
                                                 P2CONST(void, AUTOMATIC, XCP_APPL_DATA) physAddress[], P2CONST(uint8, AUTOMATIC, XCP_APPL_DATA) physLength);
  #endif
#endif

/* Check if a XCP stimulation event can perform or delete the buffers */
/* Returns 1 (TRUE) if new stimulation data is available */
#if defined ( XCP_ENABLE_STIM )

  /* action */
  #define STIM_CHECK_ODT_BUFFER 1u
  #define STIM_RESET_ODT_BUFFER 2u

  extern FUNC(uint8, XCP_CODE) XcpStimEventStatus( tXcpEventType event, uint8 action );

#endif

/* Call the XCP command processor. */
extern FUNC(void, XCP_CODE) XcpCommand( P2CONST(uint32, AUTOMATIC, XCP_APPL_DATA) pCommand );

/* Transmit Notification */
/* Confirmation of the transmit request by ApplXcpSend(). */
/* Returns 0 when the XCP driver is idle */
extern FUNC(uint8, XCP_CODE) XcpSendCallBack( void );

/* Background Loop */
/* Return 1 (TRUE) if anything is still pending */
/* Used only if Checksum Calculation or EEPROM Programming is required */
extern FUNC(void, XCP_CODE) XcpBackground( void );

/*-----------------------------------------------------------------------------------*/
/* Functions or Macros that have to be provided externally to the XCP Protocol Layer */
/*-----------------------------------------------------------------------------------*/

/* Generate a native pointer from XCP address extension and address */
#if defined ( ApplXcpGetPointer )
#else
extern FUNC(MTABYTEPTR, XCP_CODE) ApplXcpGetPointer( uint8 addr_ext, uint32 addr );
#endif

#if defined ( XCP_ENABLE_MEM_ACCESS_BY_APPL )
extern FUNC(uint8, XCP_CODE) ApplXcpRead( uint32 addr );
extern FUNC(void, XCP_CODE) ApplXcpWrite( uint32 addr, uint8 data );
#endif

#if defined ( XCP_ENABLE_CALIBRATION_MEM_ACCESS_BY_APPL ) || defined ( XCP_ENABLE_MEM_ACCESS_BY_APPL )
  #if defined ( XCP_ENABLE_CHECKSUM )
     #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD22 ) || \
         ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD24 ) || \
         ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD44 ) || \
         defined ( XCP_ENABLE_CALIBRATION_MEM_ACCESS_BY_APPL )
extern FUNC(tXcpChecksumAddType, XCP_CODE) ApplXcpReadChecksumValue( uint32 addr );
    #endif
  #endif
#endif


#if defined ( XCP_ENABLE_CALIBRATION_MEM_ACCESS_BY_APPL ) && !defined ( XCP_ENABLE_MEM_ACCESS_BY_APPL )
extern FUNC(uint8, XCP_CODE) ApplXcpCalibrationWrite(MTABYTEPTR addr, uint8 size, ROMBYTEPTR data);
extern FUNC(uint8, XCP_CODE) ApplXcpCalibrationRead(MTABYTEPTR addr, uint8 size, BYTEPTR data);
#endif
#if defined ( XCP_ENABLE_DAQ_MEM_ACCESS_BY_APPL ) && !defined ( XCP_ENABLE_MEM_ACCESS_BY_APPL )
extern FUNC(void, XCP_CODE) ApplXcpDAQRead(DAQBYTEPTR dest, ROMDAQBYTEPTR src, uint8 size);
#endif

/* Enable interrupts */
#if defined ( ApplXcpInterruptEnable )
#else
extern FUNC(void, XCP_CODE) ApplXcpInterruptEnable( void );
#endif

/* Disable interrupts */
#if defined ( ApplXcpInterruptDisable )
#else
extern FUNC(void, XCP_CODE) ApplXcpInterruptDisable( void );
#endif


/* Some available utility functions */
/*----------------------------------*/

/* Force a XCP disconnect */
extern FUNC(void, XCP_CODE) XcpDisconnect( void );

/* Set size of transfer objects */
extern FUNC(void, XCP_CODE) XcpSetActiveTl(uint8 MaxCto, uint8 MaxDto, uint8 ActiveTl);
extern FUNC(uint8, XCP_CODE) XcpGetActiveTl( void );

/* Send a pending XCP response packet (RES). */
/* To be used after a XCP_CMD_PENDING from EEPROM or FLASH programming. */
extern FUNC(void, XCP_CODE) XcpSendCrm( void );

/* Send a XCP event (EV) or service request (SERV) message */ 
#if defined ( XCP_ENABLE_SEND_EVENT )
extern FUNC(void, XCP_CODE) XcpSendEvent( uint8 evc, ROMBYTEPTR c, uint8 len);
#endif

/* Send a text message */
/* Implement print and putchar into a XCP SERV/SERV_TEXT message */
#if defined ( XCP_ENABLE_SERV_TEXT )
  #if defined ( XCP_ENABLE_SERV_TEXT_PUTCHAR )
extern FUNC(void, XCP_CODE) XcpPutchar( CONST(uint8, AUTOMATIC) c );
    #if defined ( XCP_ENABLE_SERV_TEXT_PRINT )
extern FUNC(void, XCP_CODE) XcpPrint( P2CONST(uint8, AUTOMATIC, XCP_APPL_DATA) str );
      #if defined ( XCP_ENABLE_SERV_TEXT_PRINTF )
extern FUNC(void, XCP_CODE) XcpPrintf( P2CONST(uint8, AUTOMATIC, XCP_APPL_DATA) str, ... );
      #endif
    #endif
  #endif
#endif


/* Functions that may have be provided externally depending on options */
/*---------------------------------------------------------------------*/

/* Utility functions from xcp.c */
/*------------------------------*/

/* Override option for the memory transfer function */
/* May be used for optimization */
/* #define XcpMemCpy, #define XcpMemSet to disable the implementation in xcp.c */
#if defined ( XcpMemCpy ) 
#else
extern FUNC(void, XCP_CODE) XcpMemCpy( DAQBYTEPTR dest, ROMDAQBYTEPTR src, uint8 n );
#endif
#if defined ( XcpMemSet )
#else
extern FUNC(void, XCP_CODE) XcpMemSet( BYTEPTR p, uint16 n, uint8 b );
#endif

/* Send a DTO */
/* Can be redefined to meet DMA requirements */
#if defined ( XCP_ENABLE_DAQ )
  #if defined ( XcpSendDto )
  /* XcpSendDto is redefined */
  #endif
#endif

/* Resolve a transmit stall condition in XcpPutchar() or XcpSendEvent() */
/* Returns true (!=0) if successfull */
#if defined ( XCP_ENABLE_SEND_EVENT ) || defined ( XCP_ENABLE_SERV_TEXT_PUTCHAR )
  #if defined ( XCP_ENABLE_SEND_QUEUE )
    #if defined ( ApplXcpSendStall )
    #else
      #if defined ( XCP_TRANSPORT_LAYER_TYPE_LIN )
        #define ApplXcpSendStall()  XcpLinSendStall()
      #else
extern FUNC(uint8, XCP_CODE) ApplXcpSendStall( void );
      #endif
    #endif
  #endif
#endif

/* Check addresses for valid write access */
/* Returns 0 (false) if access denied */
/* Used only, if write protection of memory areas is required */
#if defined ( XCP_ENABLE_WRITE_PROTECTION )
  #if defined ( ApplXcpCheckWriteAccess ) /* Not defined as macro */
  #else
extern FUNC(uint8, XCP_CODE) ApplXcpCheckWriteAccess( ROMMTABYTEPTR address, uint8 size );
  #endif
#endif

/* Check addresses for valid read access */
/* Returns 0 (false) if access denied */
/* Used only, if read protection of memory areas is required */
#if defined ( XCP_ENABLE_READ_PROTECTION )
  #if defined ( ApplXcpCheckReadAccess ) /* Not defined as macro */
  #else
extern FUNC(uint8, XCP_CODE) ApplXcpCheckReadAccess( ROMMTABYTEPTR address, uint16 size ); /* NEXTEER MANUAL EDIT */
  #endif
#endif

/* Check addresses for valid read/write access */
/* Returns 0 (false) if access denied */
/* Used only, if DAQ protection of memory areas is required */
#if defined ( XCP_ENABLE_DAQ )
  #if defined ( XCP_ENABLE_READ_PROTECTION ) || defined ( XCP_ENABLE_WRITE_PROTECTION )
extern FUNC(uint8, XCP_CODE) ApplXcpCheckDAQAccess(DAQBYTEPTR address, uint8 size);
  #endif
#endif

/* Calculate checksum for a memory range */
/* Returns 0 (false) if access denied */
/* Used only, if read protection of memory areas is required */
#if defined ( XCP_ENABLE_CHECKSUM ) && defined ( XCP_ENABLE_CUSTOM_CRC )
  #if defined ( ApplXcpCalculateChecksum ) /* Not defined as macro */
  #else
extern FUNC(uint8, XCP_CODE) ApplXcpCalculateChecksum( ROMBYTEPTR pMemArea, BYTEPTR pRes, uint32 length );
  #endif
#endif

/* Check addresses for valid programming access */
/* Returns 0 (false) if access denied */
/* Used only, if programming protection of memory areas is required */
#if defined ( XCP_ENABLE_PROGRAMMING_WRITE_PROTECTION )
  #if defined ( ApplXcpCheckProgramAccess ) /* Not defined as macro */
  #else
extern FUNC(uint8, XCP_CODE) ApplXcpCheckProgramAccess( MTABYTEPTR address, uint32 size );
  #endif
#endif

/* DAQ resume */
#if defined ( XCP_ENABLE_DAQ_RESUME )
extern FUNC(void, XCP_CODE) ApplXcpDaqResumeStore( P2CONST(tXcpDaq, AUTOMATIC, XCP_APPL_DATA) daq, uint16 size, uint8 measurementStart );
extern FUNC(void, XCP_CODE) ApplXcpDaqResumeClear(void);
extern FUNC(uint8, XCP_CODE) ApplXcpCalResumeStore(void);
extern FUNC(uint8, XCP_CODE) ApplXcpDaqResume( P2VAR(tXcpDaq, AUTOMATIC, XCP_APPL_DATA) daq );
#endif 

/* DAQ Timestamp */
#if defined ( XCP_ENABLE_DAQ_TIMESTAMP )
  #if defined ( ApplXcpGetTimestamp )
  /* ApplXcpGetTimestamp is redefined */
  #else
extern FUNC(XcpDaqTimestampType, XCP_CODE) ApplXcpGetTimestamp( void );
  #endif
#endif


/* Flash Programming by Flash Kernel */
#if defined ( XCP_ENABLE_BOOTLOADER_DOWNLOAD )

extern FUNC(uint8, XCP_CODE) ApplXcpDisableNormalOperation( MTABYTEPTR a, uint16 size );
extern FUNC(uint8, XCP_CODE) ApplXcpStartBootLoader( void );

#endif


/* Flash Programming */
#if defined ( XCP_ENABLE_PROGRAM )

extern FUNC(void, XCP_CODE) ApplXcpReset( void );

extern FUNC(uint8, XCP_CODE) ApplXcpProgramStart( void );
/* Returns:
   XCP_CMD_OK    
   XCP_CMD_PENDING - call XcpSendCrm when done
   XCP_CMD_ERROR 
*/

extern FUNC(uint8, XCP_CODE) ApplXcpFlashClear( MTABYTEPTR address, uint32 size );
/* Returns:
   XCP_CMD_OK    
   XCP_CMD_PENDING - call XcpSendCrm when done
   XCP_CMD_ERROR 
*/

extern FUNC(uint8, XCP_CODE) ApplXcpFlashProgram( ROMBYTEPTR data, MTABYTEPTR address, uint8 size );
/* Returns:
   XCP_CMD_OK      - FLASH written
   XCP_CMD_PENDING - FLASH write in progress, call XcpSendCrm when done
*/

#endif /* XCP_ENABLE_PROGRAM */


/* RAM/ROM Switching */
#if defined ( XCP_ENABLE_CALIBRATION_PAGE )

extern FUNC(uint8, XCP_CODE) ApplXcpGetCalPage( uint8 segment, uint8 mode );
extern FUNC(uint8, XCP_CODE) ApplXcpSetCalPage( uint8 segment, uint8 page, uint8 mode);

  #if defined ( XCP_ENABLE_PAGE_COPY )
extern FUNC(uint8, XCP_CODE) ApplXcpCopyCalPage( uint8 srcSeg, uint8 srcPage, uint8 destSeg, uint8 destPage );
/* Returns:
   XCP_CMD_OK    
   XCP_CMD_PENDING - call XcpSendCrm when done
   XCP_CMD_ERROR 
*/
  #endif
#endif
#if defined ( XCP_ENABLE_PAGE_FREEZE )
extern FUNC(void, XCP_CODE) ApplXcpSetFreezeMode( uint8 segment, uint8 mode );
extern FUNC(uint8, XCP_CODE) ApplXcpGetFreezeMode( uint8 segment );
#endif

/* Seed & Key */
#if defined ( XCP_ENABLE_SEED_KEY )

extern FUNC(uint8, XCP_CODE) ApplXcpGetSeed( const uint8 resource, P2VAR(uint8, AUTOMATIC, XCP_APPL_DATA) seed );
extern FUNC(uint8, XCP_CODE) ApplXcpUnlock( P2CONST(uint8, AUTOMATIC, XCP_APPL_DATA) key, const uint8 length );

#endif

/* User defined service of GET_ID */
#if defined ( XCP_ENABLE_GET_ID_GENERIC )
extern FUNC(uint32, XCP_CODE) ApplXcpGetIdData( MTABYTEPTR *pData, uint8 id );
#endif

/* EEPROM Programing */
#if defined ( XCP_ENABLE_WRITE_EEPROM )
/* Return values for ApplXcpCheckWriteEEPROM:
 XCP_CMD_OK      - EEPROM written
 XCP_CMD_DENIED  - This is not EEPROM
 XCP_CMD_PENDING - EEPROM write in progress, call XcpSendCrm when done
*/
extern FUNC(uint8, XCP_CODE) ApplXcpCheckWriteEEPROM( MTABYTEPTR addr, uint8 size, ROMBYTEPTR data );
#endif
#if defined ( XCP_ENABLE_READ_EEPROM )
/* Return values for ApplXcpCheckReadEEPROM:
 XCP_CMD_OK      - EEPROM read
 XCP_CMD_DENIED  - This is not EEPROM
*/
extern FUNC(uint8, XCP_CODE) ApplXcpCheckReadEEPROM( MTABYTEPTR addr, uint8 size, BYTEPTR data );
#endif


/* User defined service */ 
#if defined ( XCP_ENABLE_USER_COMMAND )
/* Return values for ApplXcpUserService:
 XCP_CMD_OK      - Done
 XCP_CMD_PENDING - Pending, call XcpSendCrm when done
 XCP_CMD_SYNTAX  - Error
*/
extern FUNC(uint8, XCP_CODE) ApplXcpUserService( ROMBYTEPTR pCmd );
#endif

#if defined ( XCP_ENABLE_OPENCMDIF )
/* Return values for ApplXcpOpenCmdIf:
 XCP_CMD_OK           - Done
 XCP_CMD_PENDING      - Pending, call XcpSendCrm when done
 XCP_CMD_UNKNOWN      - not implemented optional command
*/
extern FUNC(uint8, XCP_CODE) ApplXcpOpenCmdIf( ROMBYTEPTR pCmd, BYTEPTR pRes, BYTEPTR pLength );
#endif

#if defined ( XCP_ENABLE_VERSION_INFO_API )
extern FUNC(void, XCP_CODE) XcpGetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, XCP_APPL_DATA) XcpVerInfoPtr);
#endif

#if defined ( XCP_ENABLE_GET_SESSION_STATUS_API )
/* Get the session state of the XCP Protocol Layer */
extern FUNC(SessionStatusType, XCP_CODE) XcpGetSessionStatus( void );
#endif

#if defined ( XCP_ENABLE_GET_XCP_DATA_POINTER )
extern FUNC(void, XCP_CODE) XcpGetXcpDataPointer( P2VAR(tXcpDataPtr, AUTOMATIC, XCP_APPL_DATA) pXcpData );
#endif

#if defined ( XCP_ENABLE_CONTROL )
/* En- or disable the Xcp Protocol Layer globally */
extern FUNC(void, XCP_CODE) XcpControl( uint8 command );
  #define kXcp_Control_Disable   0x00u
  #define kXcp_Control_Enable    0x01u
#endif

/* Activation/Deactivation control macros */
#if defined( XCP_ENABLE_CONTROL )

  #if defined ( XCP_ACTIVATE )
  #else
    #if defined ( XCP_TRANSPORT_LAYER_TYPE_CAN_ASR )
      #if ( CANXCP_ENABLE_CONTROL == STD_ON )
        #define XCP_ACTIVATE_CAN() CanXcp_Control(kXcponCan_Control_Enable)
      #else
        #define XCP_ACTIVATE_CAN()
      #endif
    #else
      #define XCP_ACTIVATE_CAN()
    #endif
    #if defined ( XCP_TRANSPORT_LAYER_TYPE_FLEXRAY_ASR )
      #if ( FRXCP_ENABLE_CONTROL == STD_ON )
        #define XCP_ACTIVATE_FR() FrXcp_Control(kXcponFr_Control_Enable)
      #else
        #define XCP_ACTIVATE_FR() 
      #endif
    #else
      #define XCP_ACTIVATE_FR() 
    #endif
    #if defined ( XCP_TRANSPORT_LAYER_TYPE_TCPIP_ASR )
      #if ( ETHXCP_ENABLE_CONTROL == STD_ON )
        #define XCP_ACTIVATE_ETH() EthXcp_Control(kXcponEth_Control_Enable)
      #else
        #define XCP_ACTIVATE_ETH()
      #endif
    #else
      #define XCP_ACTIVATE_ETH()
    #endif
    #if defined ( XCP_TRANSPORT_LAYER_TYPE_LIN_ASR )
      #if ( LINXCP_ENABLE_CONTROL == STD_ON )
        #define XCP_ACTIVATE_LIN() LinXcp_Control(kXcponLin_Control_Enable)
      #else
        #define XCP_ACTIVATE_LIN()
      #endif
    #else
      #define XCP_ACTIVATE_LIN()
    #endif
    #define XCP_ACTIVATE() { XCP_ACTIVATE_CAN(); XCP_ACTIVATE_FR(); XCP_ACTIVATE_ETH(); XCP_ACTIVATE_LIN(); XcpControl(kXcp_Control_Enable); } /* PRQA S 3458 */ /* MD_MSR_19.4 */
  #endif

  #if defined ( XCP_DEACTIVATE )
  #else
    #if defined ( XCP_TRANSPORT_LAYER_TYPE_CAN_ASR )
      #if ( CANXCP_ENABLE_CONTROL == STD_ON )
        #define XCP_DEACTIVATE_CAN() CanXcp_Control(kXcponCan_Control_Disable)
      #else
        #define XCP_DEACTIVATE_CAN()
      #endif
    #else
      #define XCP_DEACTIVATE_CAN()
    #endif
    #if defined ( XCP_TRANSPORT_LAYER_TYPE_FLEXRAY_ASR )
      #if ( FRXCP_ENABLE_CONTROL == STD_ON )
        #define XCP_DEACTIVATE_FR() FrXcp_Control(kXcponFr_Control_Disable)
      #else
        #define XCP_DEACTIVATE_FR() 
      #endif
    #else
      #define XCP_DEACTIVATE_FR() 
    #endif
    #if defined ( XCP_TRANSPORT_LAYER_TYPE_TCPIP_ASR )
      #if ( ETHXCP_ENABLE_CONTROL == STD_ON )
        #define XCP_DEACTIVATE_ETH() EthXcp_Control(kXcponEth_Control_Disable)
      #else
        #define XCP_DEACTIVATE_ETH()
      #endif
    #else
      #define XCP_DEACTIVATE_ETH()
    #endif
    #if defined ( XCP_TRANSPORT_LAYER_TYPE_LIN_ASR )
      #if ( LINXCP_ENABLE_CONTROL == STD_ON )
        #define XCP_DEACTIVATE_LIN() LinXcp_Control(kXcponLin_Control_Disable)
      #else
        #define XCP_DEACTIVATE_LIN()
      #endif
    #else
      #define XCP_DEACTIVATE_LIN()
    #endif
    #define XCP_DEACTIVATE() { XcpDisconnect(); XCP_DEACTIVATE_CAN(); XCP_DEACTIVATE_FR(); XCP_DEACTIVATE_ETH(); XCP_DEACTIVATE_LIN(); XcpControl(kXcp_Control_Disable); } /* PRQA S 3458 */ /* MD_MSR_19.4 */
  #endif
#endif




#define XCP_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/*****************************************************************************/
/* Consistency and limit checks ( XCP Protocol Layer specific )              */
/*****************************************************************************/

/* The test mode must not be used with XCP Professional.  */



/* Check consistency of DAQ switch */

#if defined ( XCP_ENABLE_DAQ ) && defined ( XCP_DISABLE_DAQ )
  #error "XCP consistency error: DAQ must be either enabled or disabled."
#endif
#if defined ( XCP_ENABLE_DAQ ) || defined ( XCP_DISABLE_DAQ )
#else
  #error "XCP consistency error: DAQ must be enabled or disabled."
#endif

/* Check consistency of STIM switch */

#if defined ( XCP_ENABLE_STIM ) && defined ( XCP_DISABLE_STIM )
  #error "XCP consistency error: Data stimulation (STIM) must be either enabled or disabled."
#endif
#if defined ( XCP_ENABLE_STIM ) || defined ( XCP_DISABLE_STIM )
#else
  #error "XCP consistency error: Data stimulation (STIM) must be enabled or disabled."
#endif
#if defined ( XCP_ENABLE_STIM ) && defined ( XCP_DISABLE_DAQ )
  #error "XCP consistency error: Data stimulation (STIM) requires DAQ."
#endif
#if defined ( XCP_ENABLE_STIM ) 
  #if defined ( kXcpStimOdtCount )
  #else
    #error "XCP consistency error: Data stimulation (STIM) requires kXcpStimOdtCount."
  #endif
#endif

/* Check consistency of send queue */

#if defined ( XCP_ENABLE_SEND_QUEUE ) && defined ( XCP_DISABLE_SEND_QUEUE )
  #error "XCP consistency error: Send queue must be either enabled or disabled."
#endif
#if defined ( XCP_ENABLE_SEND_QUEUE ) || defined ( XCP_DISABLE_SEND_QUEUE )
#else
  #error "XCP consistency error: Send queue must be enabled or disabled."
#endif
#if defined ( XCP_ENABLE_SEND_QUEUE ) && defined ( XCP_DISABLE_DAQ )
  #error "XCP consistency error: Send queue cannot be used without DAQ."
#endif

/* Check consistency of communictaion mode info */

#if defined ( XCP_ENABLE_COMM_MODE_INFO ) && defined ( XCP_DISABLE_COMM_MODE_INFO )
  #error "XCP consistency error: Communictaion mode info must be either enabled or disabled."
#endif
#if defined ( XCP_ENABLE_COMM_MODE_INFO ) || defined ( XCP_DISABLE_COMM_MODE_INFO )
#else
  #error "XCP consistency error: Communictaion mode info must be enabled or disabled."
#endif

/* Check consistency of block download */

#if defined ( XCP_ENABLE_BLOCK_DOWNLOAD ) && defined ( XCP_DISABLE_BLOCK_DOWNLOAD )
  #error "XCP consistency error: Block download must be either enabled or disabled."
#endif
#if defined ( XCP_ENABLE_BLOCK_DOWNLOAD ) || defined ( XCP_DISABLE_BLOCK_DOWNLOAD )
#else
  #error "XCP consistency error: Block download must be enabled or disabled."
#endif
#if defined ( XCP_ENABLE_BLOCK_DOWNLOAD ) && defined ( XCP_DISABLE_COMM_MODE_INFO )
  #error "XCP consistency error: Communication mode info should be enabled when using block download."
#endif

/* Check service request */

#if defined ( XCP_ENABLE_SERV_TEXT ) && defined ( XCP_DISABLE_SERV_TEXT )
  #error "XCP consistency error: Service request must be either enabled or disabled."
#endif
#if defined ( XCP_ENABLE_SERV_TEXT ) || defined ( XCP_DISABLE_SERV_TEXT )
#else
  #error "XCP consistency error: Service request must be enabled or disabled."
#endif
#if defined ( XCP_ENABLE_SERV_TEXT ) && defined ( XCP_DISABLE_SERV_TEXT_PUTCHAR )
  #error "XCP consistency error: Without XcpPutchar is no service request possible."
#endif

/* Check service request XcpPutchar */

#if defined ( XCP_ENABLE_SERV_TEXT_PUTCHAR ) && defined ( XCP_DISABLE_SERV_TEXT_PUTCHAR )
  #error "XCP consistency error: XcpPutchar function must be either enabled or disabled."
#endif
#if defined ( XCP_ENABLE_SERV_TEXT_PUTCHAR ) || defined ( XCP_DISABLE_SERV_TEXT_PUTCHAR )
#else
  #error "XCP consistency error: XcpPutchar function must be enabled or disabled."
#endif
#if defined ( XCP_DISABLE_SERV_TEXT ) && defined ( XCP_ENABLE_SERV_TEXT_PUTCHAR )
  #error "XCP consistency error: XcpPutchar function can only be used with service requests."
#endif

/* check service request XcpPutchar */

#if defined ( XCP_ENABLE_SERV_TEXT_PRINT ) && defined ( XCP_DISABLE_SERV_TEXT_PRINT )
  #error "XCP consistency error: XcpPrint function must be either enabled or disabled."
#endif
#if defined ( XCP_ENABLE_SERV_TEXT_PRINT ) || defined ( XCP_DISABLE_SERV_TEXT_PRINT )
#else
  #error "XCP consistency error: XcpPrint function must be enabled or disabled."
#endif
#if defined ( XCP_ENABLE_SERV_TEXT ) && defined ( XCP_DISABLE_SERV_TEXT_PUTCHAR )
  #error "XCP consistency error: XcpPrint requires XcpPutchar function."
#endif

/* Check consistency of DAQ header ODT */
#if defined(XCP_ENABLE_DAQ) 
  #if defined ( XCP_ENABLE_DAQ_HDR_ODT_DAQ ) && defined ( XCP_DISABLE_DAQ_HDR_ODT_DAQ )
    #error "XCP consistency error: DAQ_HDR_ODT_DAQ must be either enabled or disabled."
  #endif
  #if defined ( XCP_ENABLE_DAQ_HDR_ODT_DAQ ) || defined ( XCP_DISABLE_DAQ_HDR_ODT_DAQ )
  #else
    #error "XCP consistency error: DAQ_HDR_ODT_DAQ must be enabled or disabled."
  #endif
#endif

/* Check consistency of Page switching */

#if defined ( XCP_ENABLE_CALIBRATION_PAGE ) && defined ( XCP_DISABLE_CALIBRATION_PAGE )
  #error "XCP consistency error: Page switching must be either enabled or disabled."
#endif
#if defined ( XCP_ENABLE_CALIBRATION_PAGE ) || defined ( XCP_DISABLE_CALIBRATION_PAGE )
#else
  #error "XCP consistency error: Page switching must be enabled or disabled."
#endif

/* Check range of kXcpStationIdLength */

#if defined ( kXcpStationIdLength )
  #if ( kXcpStationIdLength > 0xFF )
    #error "XCP error: kXcpStationIdLength must be < 256."
  #endif
#endif

/* Check range of kXcpStimOdtCount */

#if defined ( XCP_ENABLE_STIM )
  #if defined ( kXcpStimOdtCount )
    #if ( kXcpStimOdtCount > 0xFF )
      #error "XCP error: kXcpStimOdtCount must be <= 0xFF."
    #endif
  #endif
#endif

#if defined ( XCP_ENABLE_DAQ )

  /* Check range of kXcpDaqMemSize */

  #if defined ( kXcpDaqMemSize )
    #if ( kXcpDaqMemSize > 0xFFFF )
      #error "XCP error: kXcpDaqMemSize must be <= 0xFFFF."
    #endif
  #endif

  /* Check range of kXcpSendQueueMinSize. */

  #if defined ( kXcpSendQueueMinSize ) 
    #if ( kXcpSendQueueMinSize > 0xFF )
      #error "XCP error: kXcpSendQueueMinSize must be <= 0xFF."
    #endif
  #endif

  /* Check XCP_ENABLE_ODT_SIZE_WORD in combination with XCP_ENABLE_DAQ_HDR_ODT_DAQ */
  #if defined ( XCP_ENABLE_ODT_SIZE_WORD ) 
    #if defined ( XCP_ENABLE_DAQ_HDR_ODT_DAQ )
    #else
      #error "XCP error: If XCP_ENABLE_ODT_SIZE_WORD is enabled, XCP_ENABLE_DAQ_HDR_ODT_DAQ must be enabled as well."
    #endif
  #endif

#endif /* defined ( XCP_ENABLE_DAQ ) */

#if defined ( XCP_ENABLE_CHECKSUM )

  /* Check configuration of kXcpChecksumMethod */
  #if defined ( kXcpChecksumMethod )
    #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD11 ) || \
        ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD12 ) || \
        ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD14 ) || \
        ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD22 ) || \
        ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD24 ) || \
        ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD44 ) || \
        ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_CRC32 ) || \
        ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_CRC16CCITT )
    #else
      #error "XCP error: Checksum calculation method not supported."
    #endif
  #endif

  /* Check configuration of kXcpChecksumBlockSize. */
  #if defined ( kXcpChecksumBlockSize )
    #if ( kXcpChecksumBlockSize > 0xFFFF )
      #error "XCP error: Checksum block size is limited to a maximum of 0xFFFF."
    #endif
    #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD22 ) || \
        ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD24 )
      #if ((kXcpChecksumBlockSize % 2) != 0 )
        #error "XCP error: The blocksize must be modulo 2."
      #endif
    #endif
    #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_ADD44 )
      #if ((kXcpChecksumBlockSize % 4) != 0 )
        #error "XCP error: The blocksize must be modulo 4."
      #endif
    #endif
  #endif

  #if defined ( XCP_ENABLE_AUTOSAR_CRC_MODULE )
    #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_CRC32 )      || \
        ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_CRC16CCITT )
    #else
      #error "XCP error: Checksum calculation method not supported."
    #endif
    #if defined ( XCP_ENABLE_CRC16CCITT_REFLECTED )
      #error "XCP error: Checksum calculation method not supported."
    #endif
  #else
    #if ( kXcpChecksumMethod == XCP_CHECKSUM_TYPE_CRC32 )
      #error "XCP error: Checksum calculation method not supported."
    #endif
  #endif

#endif /* defined ( XCP_ENABLE_CHECKSUM ) */

#if defined ( XCP_ENABLE_DAQ_TIMESTAMP )

  /* Check configuration of kXcpDaqTimestampUnit. */

  #if defined ( kXcpDaqTimestampUnit )
    #if ( (kXcpDaqTimestampUnit >> 4) > 12 ) || ( (kXcpDaqTimestampUnit & 0x0F) > 0 )
      #error "XCP error: the value of kXcpDaqTimestampUnit is not valid."
    #endif
  #endif

  /* Check configuration of kXcpDaqTimestampTicksPerUnit. */

  #if defined ( kXcpDaqTimestampTicksPerUnit )
    #if ( (kXcpDaqTimestampTicksPerUnit > 0xFFFF) || (kXcpDaqTimestampTicksPerUnit == 0) )
      #error "XCP error: illegal range of kXcpDaqTimestampTicksPerUnit: 0 < kXcpDaqTimestampTicksPerUnit <= 0xFFFF."
    #endif
  #endif

  /* Check for configuration of kXcpDaqTimestampSize */
  #if defined ( kXcpDaqTimestampSize )
    #if ( kXcpDaqTimestampSize != DAQ_TIMESTAMP_BYTE ) && ( kXcpDaqTimestampSize != DAQ_TIMESTAMP_WORD ) && ( kXcpDaqTimestampSize != DAQ_TIMESTAMP_DWORD )
      #error "XCP error: Please define kXcpDaqTimestampSize to either DAQ_TIMESTAMP_BYTE, DAQ_TIMESTAMP_WORD or DAQ_TIMESTAMP_DWORD"
    #endif
  #endif

#endif

/* Check range of service request kXcpMaxSegment. */

#if defined ( XCP_ENABLE_PAGE_INFO )
  #if defined ( kXcpMaxSegment ) 
    #if  ( ( kXcpMaxSegment > 0xFF ) || ( kXcpMaxSegment == 0x00 ) )
      #error "XCP error: kXcpMaxSegment must be <= 0xFF and > 0x00."
    #endif
  #endif
#endif

/* Check range of service request kXcpProgramMaxSector. */

#if defined ( XCP_ENABLE_PROGRAM_INFO )
  #if defined ( kXcpProgramMaxSector )
    #if  ( ( kXcpProgramMaxSector > 0xFF ) || ( kXcpProgramMaxSector == 0x00 ) )
      #error "XCP error: kXcpProgramMaxSector must be <= 0xFF and > 0x00."
    #endif
  #endif
#endif


  #define C_KOMMENTAR_VECTOR



#endif /* ! defined ( __XCP_H_ ) */

