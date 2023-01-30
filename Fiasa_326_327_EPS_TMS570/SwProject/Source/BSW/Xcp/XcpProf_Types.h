#define C_INTERNAL_USE_VECTOR


/*****************************************************************************
| Project Name:   XCP Protocol Layer
|    File Name:   XcpProf_Types.h
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

#if !defined ( XCPPROF_TYPES_H )
#define XCPPROF_TYPES_H

#include "ComStack_Types.h"
#include "XcpProf.h"


typedef struct
{
  P2FUNC(void, XCP_CODE, ApplXcpSend)( uint8 len, P2CONST(uint8, AUTOMATIC, XCP_APPL_DATA) msg );
  P2FUNC(void, XCP_CODE, ApplXcpSendFlush)( uint8 FlushType );
  #if defined ( XCP_ENABLE_TL_COMMAND )
  P2FUNC(uint8, XCP_CODE, ApplXcpTLService)( P2CONST(uint8, AUTOMATIC, XCP_APPL_DATA) pCmd );
  #endif
} Xcp_TlApiType;


#endif
/* XCPPROF_TYPES_H */

