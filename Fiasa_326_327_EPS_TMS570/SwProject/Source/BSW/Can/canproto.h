/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */

/* STARTSINGLE_OF_MULTIPLE */

/* ***************************************************************************
| Project Name: DrvCan_TMS470Dcan
|    CBD: File Name: CAN_DEF.H
|    Asr: File Name: Can.h
|
|  Description: Application-Interface of the CAN-Driver
|               Declaration of functions, variables, and constants
|
|     Compiler: see module file
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 1996-2014 by Vector Informatik GmbH.       All rights reserved.
|
| This software is copyright protected and proprietary 
| to Vector Informatik GmbH. Vector Informatik GmbH 
| grants to you only those rights as set out in the 
| license conditions. All other rights remain with 
| Vector Informatik GmbH.
|
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Ht           Heike Honert              Vector Informatik GmbH
| Bir          Holger Birke              Vector Informatik GmbH
| Pl           Georg Pfluegel            Vector Informatik GmbH
| Kk           Karol Kostolny            Vector Informatik GmbH
| Seg          Sebastian Gaertner        Vector Informatik GmbH
| Ou           Mihai Olariu              Vector Informatik GmbH
| Aj           Arthur Jendrusch          Vector Informatik GmbH
| Rse          Robert Schelkle           Vector Informatik GmbH
| Zam          Artjom Zabirko            Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------ -- --------------------------------------------------
| 2006-11-06   1.00    Pl     - ESCAN00020209: Create a new can-driver for the TMS470PSF761
| 2007-06-12   1.01    Pl     - ESCAN00020210: Support all features for a standard can-driver 
|                                              (Extended and Mixed ID, RAM-check added)
| 2007-09-04   1.02    Kk     - ESCAN00022217: Support low level message transmit feature
|                             - ESCAN00022235: Issue in RAM check in function CanLL_IsMailboxCorrupt() fixed
| 2007-11-01   1.03    Pl     - ESCAN00023055: Support Autosar 2.1 for the TMS470PSF761
| 2008-04-24   1.04    Pl     - ESCAN00025297: Support new platform Nios from Altera
|                             - ESCAN00026389: Inside the Tx-Task there is a missing Interruptlock necessary
| 2008-07-01   1.05    Pl     - ESCAN00027990: Update to Autosar 3.0 for the Platform TMS470/TMS570 DCAN
| 2009-06-16   1.06    Pl     - ESCAN00035177: Update to new Highlevel Version 3.07.01
|                             - ESCAN00034736: Compiler Warnings: function declared implicitly
|                             - ESCAN00034821: Compiler Warnings: variable "canHwRxBasicStartIdx" was set but never used
|                             - ESCAN00034825: Compiler Warnings: variable "status_stop" was set but never used
| 2009-07-23   1.07    Seg    - ESCAN00029495: Support of Highend Features and Multiple Configuration for the Platform TMS470/TMS570 DCAN
| 2009-09-29   1.08    Seg    - ESCAN00038099: Add Compiler Abstraction and Memory mapping
|                             - ESCAN00038181: CAN communication fails
| 2009-11-04   1.09    Seg    - ESCAN00038927: Can ISR prototype CanIsr_0 is always set and cannot be disabled
| 2009-11-18   1.10    Seg    - ESCAN00039366: support local power down mode
|                             - ESCAN00039256: ECU is blocked and nothing was working or other unexpected behaviour
| 2010-04-08   1.10.01 Pl     - ESCAN00042030: If a single channel configuration use not the first hardware channel, the reception of messages did not work
| 2010-07-12   1.11    Ou     - ESCAN00043180: Autosar only: Compiler Warnings: function declared implicitly
|                             - ESCAN00043953: Implement the DCAN "Init bit" errata
| 2010-10-25   1.12    Pl     - ESCAN00046368: Support of the TMS570PSFC66 for CANbedded added
| 2011-02-09   1.12.01 Ht     - ESCAN00048103: Issue regarding undefined asm object
| 2011-07-12   1.13    Pl     - ESCAN00049170: CAN driver stuck in endless loop after a "wake up on bus activity" if "local power down mode" is selected
|                             - ESCAN00052107: Malfunction of "wake up on bus activity" if "local power down mode" is selected
|                             - ESCAN00052162: a parity check error occur during the initialisation of the CAN-cell
| 2011-09-19   1.14    Pl     - ESCAN00053686: Support of configurations with no BasicCAN             
| 2011-12-16   1.14.01 Aj     - ESCAN00055628: Compiler error if individual polling and cancel in hardware
| 2012-01-26   1.14.02 Pl     - ESCAN00056116: Compile error in Can_MainFunction_Wakeup occur
| 2012-02-23   1.14.03 Pl     - ESCAN00057058: make the disabling of the hardware feature "parity check" configurable
| 2012-05-24   1.15.00 Pl     - ESCAN00057481: compile-error occur if no Basic-CAN Object is configured
|                             - ESCAN00059147: Support Global and Local Power down Mode for CANbedded
|                             - ESCAN00059246: Wrong receptions with the Std Id FullCAN object if C_ENABLE_RX_MASK_EXT_ID is set
|                             - ESCAN00059248: After the FullCANOverrun handling Extended Id Masking for Extended FullCAN objects didn't work
| 2012-06-19   1.16.00 Pl     - ESCAN00059528: Support Autosar R14
|                             - ESCAN00060207: AutoSar only: Can_SetControllerMode(controller, CAN_T_STOP) returns CAN_OK instead of CAN_NOT_OK
| 2012-11-08   1.17.00 Pl     - ESCAN00061303: Support of new platform Tms320ARM added
|                             - ESCAN00062872: parameter for CanLL_HandleIllIrptNumber has offset -1
| 2012-11-23   1.18.00 Pl     - ESCAN00063286: Support of QCC compiler for the Tms320ArmDcan
|                             - ESCAN00063756: If an overrun occur to an Full-CAN hardware object, the mask of it will be set to an wrong value
|                                              during the overrun handling
| 2012-12-20   1.19.00 Rse    - ESCAN00060563: AR3-2445: Perform SilentBSW module analysis for critical code parts
|                             - ESCAN00060963: Can_InitController() writes VIM register
| 2013-10-06   1.20.00 Zam    - ESCAN00070918: Source code optimizations to speed up the runtime of message RAM access 
|                             - ESCAN00070921: Support Asr 403 Cfg5 High-End for Jacinto6 (Tms320Arm)
|                             - ESCAN00070923: Overrun occurs with higher probability
| 2013-10-24   1.21.00 Zam    - ESCAN00071153: AR4-328: Predefined Runtime Measurement Points
| 2013-11-20   1.22.00 Zam    - ESCAN00072097: CANbedded only : No CAN communication after second Bus-off occurrence
|                             - ESCAN00072399: Inconsistent data may occur
|                             - ESCAN00072400: Optimize CAN RAM check, some adaptations for CANbedded 
| 2014-01-22   1.23.00 Zam    - ESCAN00073143: Adaption of software flags (Stop, Sleep,Bussof) for ASR and Hll
|                             - ESCAN00073452: Compiler warning: argument to macro is empty
|************************************************************************** */
/*****************************************************************************
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Bir          Holger Birke              Vector Informatik GmbH
| Wr           Hans Waaser               Vector Informatik GmbH
| Ces          Senol Cendere             Vector Informatik GmbH
| Pl           Georg Pfluegel            Vector Informatik GmbH
| Tvi          Timo Vanoni               Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               C O R E    R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 2005-09-15 0.01.00 Bir  - Creation
| 2005-11-17 1.00.00 Bir  - Finish CANoe, M32C
|                         - Change include structure and naming
| 2005-11-23 1.01.00 Bir  - some minor changes
| 2005-12-01 1.02.00 Bir  - Global Interrupt handling via OSEK supported
| 2006-01-19 1.03.00 Bir  - Wrong handle found and DET occur in CanFullCanMsgReceived
|                         - C_DISABLE_RESET_CAN_BUSOFF set (baudrate out of CANoe)
| 2006-03-16 1.04.00 Wr   - Added support for NEC V850 aFCAN
|                         - Added CanLL_GeneratedStructureH for platform C_COMP_GHS_V85X  
|                         - Added general return value defines
|                         - Defined APPL_CAN_WAKEUP() to CanHL_WakeUpHandling()
|                         - Mapping of CanWakeUp() to Can_SetControllerMode(Controller, CAN_T_WAKEUP)
| 2006-04-19 1.05.00 Wr   - Add switches to enable OSEK ISR handling for platform C_COMP_GHS_V85X
| 2006-05-22 2.00.00 Bir  - Support for AutoSar 2.0
|                         - Include stucture update
|                         - DET - switch change
|                         - API adaption Can_Init(), Can_Write()
|                         - add Can_GetVersionInfo()
| 2006-06-06 2.01.00 Bir  - internal naming corrections for version defines
|                         - API for Det_ReportError changed (add parameter)
| 2006-06-12 2.02.00 Bir  - CaninitObject calculation changed
|                         - TriCore update for Interrupt priority defines
| 2006-06-12 2.03.00 Bir  - SetControllerMode return ok for unsupported stop/start or sleep/wakeup
|                         - CaninitObject calculation changed
| 2006-06-12 2.04.00 Bir  - kCanNotSupported defined to 0x02 to avoid CAN_NOT_OK for that case
| 2006-07-05 2.05.00 Bir  - Can_HwHandleType as uint8
|                         - Review rework
| 2006-07-10 2.06.00 Bir  - Can_Write try/send also in case busy
| 2006-08-15 2.07.00 Bir  - mapping of CanSingleGlobalInterruptX changed
| 2006-09-04 2.08.00 Bir  - minor change in can.h: ControllerName length expand to 20
| 2006-09-04 2.09.00 Bir  - minor change for MISRA compliance
|                         - add canStatus for init info
|                         - minor adaption to MAC71xx
|                         - No interrupt lock inside "CanBasicCanMsgReceived"
|                         - Add FullCAN Tx
|                         - Add Tx Polling
|                         - Add Hardware Loop and DEM call
|                         - DET call for initialized call of can_init()
|                         - Add Can_InitMemory function
| 2006-11-06 2.10.00 Bir  - review rework
| 2006-11-08 2.11.00 Ces/Bir - Add Platform Mcs12x
|                         - Add local variable Controller in function Can_InitMemory()
|                         - Add define C_ENABLE_COPY_TX_DATA in header
| 2006-11-09 2.12.00 Bir  - Prepare for Postbuild struct (organi switch "C_HL_ENABLE_ASR_POSTBUILD_STRUCT" added)
| 2006-11-11 2.13.00 Pl   - Add Platform TMS470_DCAN
| 2006-11-15 2.14.00 Bir  - Postbuild changes
|                         - Review changes
|                         - change CAN_HL_TX_OFFSET_HW_TO_LOG and logTxObjHandle value
|                         - ESCAN00018785: Send out of confirmation (Tx Queue)
| 2007-01-15 2.15.00 Bir  - ESCAN00018896: wrong call to Dem_SetEventStatus
|                         - deactivate "CanOverrunNotification" due to no more need since ASR2.0
|                         - Support "Can_MainFunction_BusOff"
|                         - call Can_InitController in case of change mode from busoff to start
|                         - Add Can_EnterCritical(), Can_LeaveCritical() / interrupt mapping over vstdlib or SchM
|                         - Change Version Scan Information
|                         - Remove V850 specific parts (shift to LL)
|                         - Remove Reinit DET report out of Can_InitController()
| 2007-02-20 2.16.00 Bir  - minor improvements
|                         - ESCAN00019720: Wakeup does not appear after set sleep mode
| 2007-03-09 2.20.00 Bir  - ESCAN00019889: Update to ASR2.1
|                         - ESCAN00019889: change calculation of CAN_HL_TX_OFFSET_HW_TO_LOG (because multiplexed tx)
|                         - remove FullCAN switches to secure postbuild functionality without compile with FullCANs
|                         - ESCAN00020129: Compiler error: identifier "i" is undefined
|                         - Reduce BasicCAN logical mailbox to real BasicCAN (DLC_FIFO include size of Basic CAN)
|                         - Reduce Unused mailboxes logical mailbox to amount of sections (DLC_FIFO include size)
|                         - Move all version defines from Proto.h to CAN.h (license scanning)
|                         - set DLC also for FullCAN Tx objects
|                         - generated Tables: CanActiveSendPdu,CanActiveSendState (size matter at link time)
|                         - return not ok for try to set sleep mode but failed in hw
|                         - move multichannel api define to can.h
|                         - do "CanLL_InitPowerOn" before "CanLL_InitPowerOnChannelSpecific"
|                         - move osek-switches out of irq.c
|                         - add CanLL_InitMemoryPowerOn token for special ll init
| 2007-08-28 2.21.00 Bir  - ESCAN00022112: Rx Basic CAN used with wrong Stop index
|                         - renaming "CaninitObject" to "Can_Init_CtrlIdx" (no runtime effect)
|                         - ESCAN00022168: Driver does not enter Stop mode for Sleep request (when sleep is not sup.)
|                         - ESCAN00022232: Add stop-mode compatibility for FNOS-RP migration
|                         - ESCAN00022262: CanResetBusOffEnd() used with only one parameter
|                         - Add new Token "CanLL_RxFull_SearchHandle" for special HW-support (XGate)
|                         - ESCAN00022390: Hw start-stop-index changed to RAM-table
| 2007-10-15 2.22.00 Bir  - ESCAN00022773: use of #ifndef instead of #if !defined
|                         - ESCAN00022774: nothing done here
|                         - ESCAN00023040: nothing done here
|                         - ESCAN00023038: nothing done here
|                         - ESCAN00023047: nothing done here
|                         - ESCAN00023049: nothing done here
|                         - ESCAN00023127: nothing done here
|                         - ESCAN00023265: remove brackets around Can_EnterCritical
|                         - QAC / MISRA reworks
|                         - Add memory qualifiers
| 2007-12-14 2.23.00 Bir  - ESCAN00023442: Add extended Id support
|                         - ESCAN00024354: Ignore API call with controller deactivated by identity
| 2008-02-06 3.00.00 Bir  - ESCAN00024406: ASR3.0
| 2008-03-25 3.01.00 Bir  - Add dummy assignment in "ResetBusOffEnd" avoid compiler warnings
|                         - ESCAN00025672: review reworks
|                         - ESCAN00025664: Message send with wrong ID type
|                         - ESCAN00026087: Case sensitive naming for all File names (and includes)
|                         - ESCAN00026186: Extension for MSR3.0 LinkTime checks
|                         - ESCAN00025957: No access on "DEM-events" via DEM created and exported constant values
|                         - Move compatibility section (switches needed earlier)
| 2008-05-14 3.02.00 Bir  - ESCAN00026859: V_MEMRAM0 not allowed for type cast
|                         - ESCAN00026861: Token extern declaration
|                         - ESCAN00026990: Add LL-Token to reject Remote frames
| 2008-06-30 3.03.00 Bir  - ESCAN00027986 +(ESCAN00025773): Code optimization (save ROM and runtime)
|                           + Start/StopLoop as macro
|                           + Max Loop counter define move to LL
|                           + Add some FullCan switches to be organified for Basic CAN controllers
|                           + Multiple Search for Basic CAN hw object
|                           + CanInterrupt Lock only in nested interrupt case (CAN_NESTED_INTERRUPTS)
|                           + remove some hw-start/stop indexes and there calculation use instead info from mailbox-tab
|                         - ESCAN00028069: change controller amount to library capable setting
|                         - ESCAN00026596: Extension for MSR3.0 generator version checks
| 2008-08-19 3.03.01 Bir  - minor review changes
| 2008-09-11 3.04.00 Bir  - ESCAN00029942: Generator Version Check failed
| 2008-09-18 3.05.00 Bir  - ESCAN00029830: Add Linktime/Postbuild config CRC check
|                         - ESCAN00029434: rename "INTERRUPT" and "POLLING" switch
| 2008-10-15 3.06.00 Bir  - ESCAN00029707: change transition from uninit->start->stop to uninit->stop
|                         - ESCAN00029129: Source of HW loop timer is not available to application
|                         - ESCAN00030728: move platform typedefs to can.h
| 2008-10-28 3.06.01 Bir  - ESCAN00030926: lock interrupts while Tx confirmation.
|                         - Add include protection for canproto.h
| 2008-10-28 3.07.00 Bir  - ESCAN00032401: CAN driver stays in an endless loop
|                         - ESCAN00032291: BusOff handling took some time with locked interrupts
|                         - ESCAN00032612: Support Individual Polling
|                         - ESCAN00032614: Add new memory qualifier V_MEMROM4_CFG for postbuild data access
| 2009-03-16 3.07.01 Bir  - ESCAN00033874: Add LL-token "CanLL_tCanRxInfoStruct" for struct tCanRxInfoStruct
| 2009-04-03 3.07.02 Bir  - ESCAN00034409: Add PRQA comments for MISRA justification
|                         - ESCAN00034551: Add support for reverse Rx Basic CAN polling
|                         - ESCAN00034552: Optimize Rx Basic CAN polling loop
|                         - ESCAN00034773: Add cancel Tx in Hardware within Tx polling task
| 2009-04-20 3.08.00 Bir  - ESCAN00034118: Add compiler abstraction
|                         - ESCAN00034119: Add memory abstraction
|                         - (see ESCAN 35490) Report DEM as DET "CAN_DEV_TIMEOUT_DETECT"
|                         - ESCAN00036041: compiler waring label not referenced
| 2009-07-08 3.09.00 Bir  - ESCAN00034780: Confirmation without critical section
| 2009-07-22 3.09.01 Bir  - ESCAN00036593: compile error (variable declaration after assignment)
| 2009-08-03 3.09.02 Bir  - ESCAN00036822: Tx data inconsistency 
| 2009-08-24 3.09.03 Bir  - ESCAN00037276: Compiler warning "function declared implicitly"
| 2009-09-15 3.10.00 Bir  - ESCAN00037784: Add Generic Confirmation function
|                         - ESCAN00037789: Add feature Rx Queue
|                         - change order of Rx-DLC and "CanLL_RxBasicGetCANDataPtr" (support for mailbox in RAM)
|                         - ESCAN00038814: Wrong pointer class for Tx data used
| 2010-01-19 3.11.00 Bir  - ESCAN00040258: Use Can_HwHandleType instead of uint8
|                         - ESCAN00040432: Code optimization for 1 controller systems
|                         - ESCAN00040433: Support dynamic FullCAN id
| 2010-03-03 3.11.01 Bir  - small review reworks
|                         - ESCAN00041364: Optimize Runtime of Can_SetControllerMode
|                         - ESCAN00041432: Declaration for ISRs missing in case of Full Polling with Indiv Polling
| 2010-03-03 3.12.00 Bir  - ESCAN00041791: Suppress unexpected wakeup notification
|                         - ESCAN00041984: Support Common CAN
|                         - ESCAN00041996: Split Critical Sections
|                         - ESCAN00042333: Add Hardware assertion notification to DET
|                         - ESCAN00042459: Support Wakeup-switch-off (no sleep mode - stop mode instead)
|                         - ESCAN00043085: Compiler warnings due to missing cast
|                         - ESCAN00043224: New API Can_GetStatus()
|                         - ESCAN00043250: Add Application Interrupt lock functions
|                         - canWakeUp() call changed to CAN_WAKEUP() - used for LL
|                         - ESCAN00047602: compiler warning: "comparison between signed and unsigned"
|                         - ESCAN00044114: Stop sending messages after transition to stop mode (and back to started)
| 2010-11-23 3.13.00 Bir  - ESCAN00043999: Support usage without v_def.h
|                         - ESCAN00044276: Reject unwanted ID types (software Filter)
|                         - ESCAN00045682: Compiler warning: dead assignment to "X" eliminated
|                         - ESCAN00045883: Can_SetControllerMode doesn't return CAN_NOT_OK when called with invalid Transition parameter
|                         - ESCAN00045884: Can_CheckWakeup doesn't raise the CAN_E_UNINIT development error
|                         - ESCAN00046363: Adapt AUTOSAR version check
|                         - rename "canInterruptCounter" to "canCanInterruptCounter" CBD compatibility
|                         - ESCAN00047875: Add support for partial network
|                         - ESCAN00047951: Compile error, if the feature "Optimize for one controller" is used
| 2011-03-11 4.00.00  Bir - ESCAN00043688: Support Autosar 4.0 R1
|                         - ESCAN00043998: Add GenData checker
|                         - ESCAN00044010: Add Notification for Overrun detection
|                         - ESCAN00047111: Support RAM check
|                         - ESCAN00046778: Support Multiple Identity Configuration
| 2010-04-05 4.00.01  Bir - void cast DET call for MSR40 + review reworks (minors)
|                         - ESCAN00049572: RAM-check: communication is not deactivated
|                         - ESCAN00050862: EcuM_CheckWakeup is not called in case of Wakeup Polling
|                         - ESCAN00051562: Remove the AUTOSAR Release Version Check
|                         - ESCAN00047929: Can_Init() does not initialize CAN controllers - but Can Interface do this
| 2011-06-21 4.01.00  Bir - ESCAN00050960: Provide API for Generic Pretransmit (AR3-1654 )
|                         - ESCAN00051102: Compiler warning: narrowing or signed-to-unsigned type conversion found: int to unsigned char
|                         - ESCAN00052324: Compile error if the feature "Optimize for one controller" and "Rx Queue" is used
|                         - ESCAN00054829: Fault tolerant API: Do not throw DET in case of MultipleEcuConfig inactive controller for 'Can_CheckWakeup'
|                         - ESCAN00053648: Wrong Define name used "CAN_DEACTIVATE_COMMUNICATION"
|                         - ESCAN00053270: AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
|                         - ESCAN00053263: AR3-2069: Remove non-SchM code for critical section handling
|                         - ESCAN00054038: Compiler warning: variable "canApiContext" was set but never used
|                         - ESCAN00054813: Add Mirror functionality
| 2011-11-21 4.01.01  Bir - ESCAN00055001: Support Transition HW-Loops for MSR30
|                         - ESCAN00055076: Misra compliance
| 2011-12-14 4.01.02  Bir - ESCAN00055566: Include of Det with camel case spelling
| 2011-12-15 4.01.03  Bir - ESCAN00055589: CAN219
|                         - ESCAN00056004: Add Code Trace ability to AutoSar SWS
|                         - Add explicit type casts to satisfy COSMIC compilers (MCS12x)
|                         - ESCAN00056185: Change Version Check
| 2012-01-20 4.02.00  Bir - ESCAN00055076: Misra compliance
|                         - Use !CAN_USE_VECTOR_IF instead of VGEN_GENERATOR_GENY (also support CFG5 in mixed systems)
|                         - ESCAN00057438: AR3-2383: Implement handling of call to Dem_ReportErrorStatus
|                         - ESCAN00057164: Wakeup while Re-Init ASR3.2.1
|                         - ESCAN00054830: Can_SetControllerMode() return failed
| 2012-05-31 4.02.01  Bir - ESCAN00059203: Compiler error: missing variable canHwChannel in Can_CleanUpSendState()
|                         - ESCAN00059265: Compiler error: hardware loop index is not available as define for API
| 2012-06-12 4.03.00  Bir - ESCAN00057437: AR3-2374: Implement Silent BSW
|                         - ESCAN00059412: AR4-135: support MSR 4 R5
|                         - ESCAN00059488: Compiler error: identifier "canConfigPtr" is undefined
|                         - ESCAN00060494: Compiler error: SchM_Enter_Can((area)) causes Compiler Error with external SchM Usage
| 2012-09-03 4.03.01  Bir - Improve MISRA compliance
|                         - ESCAN00061352: Endless Loop
| 2012-09-03 4.04.00  Bir - ESCAN00061042: AR3-2378: Implement AMD time measurement support
|                         - ESCAN00060586: AR3-2446: Update Code analysis and change analysis UUIDs (like described in Silent design)
|                         - ESCAN00060554: AR3-2443: Implement Silent Checks in BSW module code
|                         - ESCAN00062679: Add source defines according to MICROSAR template source file
| 2012-12-10 4.04.01  Bir - Rework Silent BSW
| 2013-01-28 4.04.02  Bir - ESCAN00064474: Modify Hook_On (code can be removed by integration organi)
| 2013-02-02 4.05.00  Bir - optimize token StopReinit usage
|                         - move some global compatibility defines from proto.h to can.h
|                         - ESCAN00063652: RxQueue extension to 16bit size
|                         - ESCAN00064324: AR4-325: Implement Post-Build Loadable
|                         - ESCAN00066278: Incorrect comment description for function Can_CheckWakeup / Can_Cbk_CheckWakeup
| 2013-06-11 4.05.01  Bir - ESCAN00067936: Can_GetStatus wrongly returns CAN_STATUS_INCONSISTENT
| 2013-06-12 4.06.00  Tvi/Bir - ESCAN00069107: AR4-397: Implement support for CAN-FD according to ASR4.1.1
|                           ESCAN00070197: Compiler warning: variable canConfigPtr was declared but never referenced
|                           ESCAN00068900: Compiler warning
|                           ESCAN00067711: AR4-328 / RTM measurement R8
|                           ESCAN00071048: Support null_ptr data in Can_Write() for DLC==0
|****************************************************************************/

#if !defined( __AUTOSAR_CAN_HL_H__ )
#define  __AUTOSAR_CAN_HL_H__


/***************************************************************************/
/* Version                  (abcd: Main version ab Sub Version cd )        */
/***************************************************************************/
/* internal Version of the Core part CanProto.h */
/* ##V_CFG_MANAGEMENT ##CQProject : DrvCan__coreAsr CQComponent : Implementation */
#define DRVCAN__COREASR_VERSION           0x0406u
#define DRVCAN__COREASR_RELEASE_VERSION   0x00u

/***************************************************************************/
/* Include                                                                 */
/***************************************************************************/
#include "Can.h"         /* include also all needed types */
/* CAN406 */
#include "SchM_Can.h"

/***************************************************************************/
/* compatibility defines                                                   */
/***************************************************************************/
#define C_ENABLE_COPY_TX_DATA
#define CAN_EXTENDED_ID_MASK        0x80000000UL
#if (CAN_MIXED_ID == STD_ON) || (CAN_EXTENDED_ID == STD_ON )
# define CAN_FD_MASK                0x40000000UL
# define CAN_ID_MASK                0x3FFFFFFFUL
# define CAN_ID_MAX                 0x1FFFFFFFUL
#else
# define CAN_FD_MASK                0x4000u
# define CAN_ID_MASK                0x3FFFu
# define CAN_ID_MAX                 0x07FFu
#endif
#define kCanAllChannels             ((CanChannelHandle)0xFFU)

#if !defined(C_DRV_INTERNAL)
# error "canproto.h should only be included by Can.c"
#endif
#if defined(kCanNumberOfChannels)
# error "kCanNumberOfChannels should not be generated"
#else
/* real amount of controllers in this system (LT and PB) */
# define kCanNumberOfChannels CAN_GLOBAL_CONFIG(CanControllerMax) 
/* if kCanNumberOfChannels used to declare a table/dimension this table has to be generated to be also LT-capable */
/*  -> see ESCAN00028069 controller-amount has to be linktime-capable */
#endif
#if defined(kCanNumberOfHwChannels)
# error "kCanNumberOfHwChannels should not be generated"
#else
/* kompatibility to common-can drivers */
/* real amount of controllers in this system (LT and PB) */
# if ( CAN_COMMON_CAN == STD_ON )
#  define kCanNumberOfHwChannels CAN_GLOBAL_CONFIG(CanHwChannelMax)
# else
#  define kCanNumberOfHwChannels CAN_GLOBAL_CONFIG(CanControllerMax)
# endif
#endif

#if !defined(CAN_MULTIPLEXED_TX_MAX)
# error "CAN_MULTIPLEXED_TX_MAX is not generated"
#endif
#if (CAN_MULTIPLEXED_TRANSMISSION == STD_ON)
# define C_ENABLE_MULTIPLEXED_TRANSMISSION
# if (CAN_MULTIPLEXED_TX_MAX != 3)
#  error "CAN_MULTIPLEXED_TX_MAX generated with wrong value"
# endif
#else
# if (CAN_MULTIPLEXED_TX_MAX != 1)
#  error "CAN_MULTIPLEXED_TX_MAX generated with wrong value"
# endif
#endif
#if !defined(CAN_DEV_TIMEOUT_DETECT)
# error "CAN_DEV_TIMEOUT_DETECT is not generated"
#endif
/* Compatibility default */
#if !defined( CAN_OVERRUN_NOTIFICATION )
# if !defined( CAN_NONE )
#  define CAN_NONE 0
# endif
# if !defined( CAN_DET )
#  define CAN_DET 1
# endif
# if !defined( CAN_APPL )
#  define CAN_APPL 2
# endif
# define CAN_OVERRUN_NOTIFICATION  CAN_NONE
#else
# if (CAN_OVERRUN_NOTIFICATION != CAN_NONE)
#  define C_ENABLE_OVERRUN
#  define C_ENABLE_FULLCAN_OVERRUN
# endif
#endif

#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON )
/* have to be done here to avoid declaration of "channel" in Can.h */
# define channel                                ((CanChannelHandle)0)
# define canHwChannel                           ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STARTINDEX(ch)       ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STOPINDEX(ch)        ((CanChannelHandle)0)
#else
#  define channel                               Controller
#  define canHwChannel                          Controller
#  define CAN_HL_HW_CHANNEL_STARTINDEX(ch)      (ch)
#  define CAN_HL_HW_CHANNEL_STOPINDEX(ch)       (ch)
#endif

#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
# if !defined(CAN_EMULATE_SLEEP)
#  define CAN_EMULATE_SLEEP STD_ON
# endif
# if !defined(CAN_TRANSITION_CHECK)
#  define CAN_TRANSITION_CHECK STD_ON
# endif
#else
# if !defined(CAN_EMULATE_SLEEP)
#  define CAN_EMULATE_SLEEP STD_OFF
# endif
# if !defined(CAN_TRANSITION_CHECK)
#  define CAN_TRANSITION_CHECK STD_OFF
# endif
#endif
#if !defined(CAN_REINIT_START)
# define CAN_REINIT_START STD_OFF
#endif

#if (CAN_RAM_CHECK != CAN_NONE) && (CAN_EXTENDED_STATE_MACHINE == STD_ON)
# error "Feature RAM_CHECK is not available in combination with EXTENDED_STATE_MACHINE"
/* no stop mode called after wakeup but need to run RAM check */
#endif

#if !defined(CAN_OS_TICK2MS)
# if (CAN_MICROSAR_VERSION == CAN_MSR403)
#  error "CAN_OS_TICK2MS() should be defined to OS_TICKS2MS_<counterShortName>() macro from OS"
# endif
# define CAN_OS_TICK2MS(tick) (tick) /* used direct by 401 implementation */
#endif
#if !defined(CAN_OS_COUNTER_ID)
# if (CAN_MICROSAR_VERSION == CAN_MSR403)
#  error "CAN_OS_COUNTER_ID should be defined to 'counterShortName' from OS"
# endif
# define CAN_OS_COUNTER_ID CanTimeoutDurationCounterId /* used direct by 401 implementation */
#endif



/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
/* for variable CanActiveSendState */
#define CANFREEOBJ                    (Can_HwHandleType)0xFF   /* mark objects as free (-1) */
#define kCanBufferFree                CANFREEOBJ               /* compatibility for cancel in hw task */
#define CANCANCELOBJ                  (Can_HwHandleType)0xFE   /* mark object as currently canceling */
#define kCanBufferCancel              CANCANCELOBJ             /* compatibility for LL cancel interrupt / task */
#define CANCANCELOBJSW                0xFD
#define CANSENDOBJ                    0x01                     /* occupied send object */

/* generel return values */
#define kCanFailed                  CAN_NOT_OK
#define kCanOk                      CAN_OK
#define kCanNotSupported            CAN_NOT_SUPPORTED
#define kCanRequested               CAN_REQUESTED

#define kCanTrue                    0x01
#define kCanFalse                   0x00

#define CAN_GLOBAL_CONFIG(x)        canConfigPtr->x   /* PRQA S 3410 */ /* MD_Can_3410 */
#if defined(CAN_ENABLE_SELECTABLE_PB)
/* CAN221 */
/* Pointer parameter of init function used (selectable post build) */
/* Use this pointer directly with the controller offset */
# define CAN_CONTROLLER_CONFIG(hwch) (*(canControllerConfigPtr[hwch]))
/* or get out of global pointer: canConfigPtr->canControllerConfigPtr */
# define CAN_CONTROLLER_CONFIG_INIT  (canConfigPtr->CanControllerConfig_TabPtr)
# define CAN_MAILBOX                 (canConfigPtr->CanMailbox_TabPtr)
# define CAN_INIT_OBJ_START_IDX      (canConfigPtr->CanInitObjectStartIndex_TabPtr)
# define CAN_INIT_OBJ_BAUDRATE       (canConfigPtr->CanInitObjectBaudrate_TabPtr)
# define CAN_INIT_OBJ_FD_CONFIG      (canConfigPtr->CanInitObjectFdConfig_TabPtr)
# define CanHwObjIndivPolling        (canConfigPtr->CanHwObjIndivPolling_TabPtr) /* PRQA S 3436 */ /* MD_Can_3436 */
# define CAN_PARTIAL_NET             (canConfigPtr->CanPartialNetwork_TabPtr)
# if (CAN_MICROSAR_VERSION == CAN_MSR403)
/* postbuild capable RAM */
#  define CanActiveSendPdu           (canConfigPtr->CanActiveSendPdu_TabPtr)    /* PRQA S 3436 */ /* MD_Can_3436 */
#  define CanActiveSendState         (canConfigPtr->CanActiveSendState_TabPtr)  /* PRQA S 3436 */ /* MD_Can_3436 */
#  define CanActiveSendId            (canConfigPtr->CanActiveSendId_TabPtr)     /* PRQA S 3436 */ /* MD_Can_3436 */
# endif
/* hardware specific starts here */
#define CanBasisAdr          (canConfigPtr->CanBasisAdrPtr)
#define interruptSrc         (canConfigPtr->interruptSrcPtr)
#define vimClrReg            (canConfigPtr->vimClrRegPtr)
#define vimSetReg            (canConfigPtr->vimSetRegPtr)
#define CanNumberOfMsgObj    (canConfigPtr->CanNumberOfMsgObjPtr)
#define CanInitBitTiming     (canConfigPtr->CanInitBitTimingPtr)
#define CanInitBRP_Reg       (canConfigPtr->CanInitBRP_RegPtr)
#define CanInitBasicMsk      (canConfigPtr->CanInitBasicMskPtr)
#define CanInitBasicMskLo    (canConfigPtr->CanInitBasicMskLoPtr)
#define CanInitBasicCod      (canConfigPtr->CanInitBasicCodPtr)
#define CanInitBasicCodLo    (canConfigPtr->CanInitBasicCodLoPtr)
/* mixed: */
#define CanInitBasic1CodLo   (canConfigPtr->CanInitBasic1CodLoPtr)
#define CanInitBasic1Cod     (canConfigPtr->CanInitBasic1CodPtr)
#define CanInitBasic1MskLo   (canConfigPtr->CanInitBasic1MskLoPtr)
#define CanInitBasic1Msk     (canConfigPtr->CanInitBasic1MskPtr)
#else
/* CAN220 */
/* Pointer parameter of init function not used (no selectable post build or link-time configuration) */
# define CAN_CONTROLLER_CONFIG(hwch) CanControllerConfig[hwch]
# define CAN_CONTROLLER_CONFIG_INIT  CanControllerConfig
# define CAN_MAILBOX                 CanMailbox
# define CAN_INIT_OBJ_START_IDX      CanInitObjectStartIndex
# define CAN_INIT_OBJ_BAUDRATE       CanInitObjectBaudrate
# define CAN_INIT_OBJ_FD_CONFIG      CanInitObjectFdConfig
# define CAN_PARTIAL_NET             CanPartialNetwork
#endif

/***************************************************************************/
/* Default switches                                                        */
/* Automatic define settings, depending on user configuration in can_cfg.h */
/***************************************************************************/
#if defined (MISRA_CHECK)
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualIdType",              0488           /* MD_Can_0488_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualExtId",               0310           /* MD_Can_0310 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualStdId",               0310           /* MD_Can_0310 */
#endif
#define C_HL_DISABLE_OVERRUN_IN_STATUS

#if defined( V_GEN_GENERATOR5 )
# define C_HL_RX_FULLCAN_HWHANDLE_REVERSE
# define C_HL_BASICCAN_HWHANDLE_REVERSE

#endif

#define C_HL_DISABLE_HW_RANGES_FILTER

#define C_HL_ENABLE_IDTYPE_IN_ID


#if defined (C_HL_ENABLE_IDTYPE_IN_ID)
/* Specify the ID tables which contain the ID type */
# define C_LL_RX_IDTYPE_TABLE      CanRxId0
# define C_LL_TX_IDTYPE_TABLE      CanTxId0
#endif


#define C_HL_DISABLE_DUMMY_FCT_CALL


#define C_HL_DISABLE_TX_MSG_DESTROYED


#define C_HL_ENABLE_CANCEL_IN_HW_TASK


#define C_HL_DISABLE_HW_EXIT_TRANSMIT 

#define C_HL_ENABLE_LAST_INIT_OBJ     

#if defined (C_COMP_TI_TMS470_DCAN) 
# define C_HL_ENABLE_CAN_IRQ_DISABLE   
#endif


#define C_HL_DISABLE_ADJUST_RXHANDLE  

#define C_HL_ENABLE_REJECT_UNWANTED_IDTYPE

#define C_HL_DISABLE_REJECT_REMOTE_FRAME

#define C_HL_DISABLE_REJECT_REMOTE_FRAME_FULLCAN

#define C_HL_DISABLE_COPROCESSOR_SUPPORT


# if !( defined (C_ENABLE_DRIVER_STATUS) || defined (C_DISABLE_DRIVER_STATUS))
#  define C_ENABLE_DRIVER_STATUS
# endif

# if ( CAN_INTLOCK == CAN_DRIVER ) || ( CAN_INTLOCK == CAN_BOTH )
#  define C_ENABLE_VIM_ACCESS_BY_DRIVER
# else
#  define C_DISABLE_VIM_ACCESS_BY_DRIVER
# endif


/***************************************************************************/
/* return values                                                           */
/***************************************************************************/
/* return values of CanRxActualIdType */
# define kCanIdTypeStd                  C_STD_ID
# define kCanIdTypeExt                  C_EXT_ID


/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/

#define CanDeclarePointerToCanHardware  V_DEF_P2SFR_CAN(V_NONE, CAN_CellAddrMap, VAR_NOINIT) pCanNode
#define CanSetPointerToCanHardware      pCanNode = CAN_BASIS_ADR(channel)
#define CanPointerToCanHardware         (*CAN_BASIS_ADR(channel))

#define IF_INIT                         pCanNode->sMsgObj[0]        
#define IF_TRANSMIT                     pCanNode->sMsgObj[0]        
#define IF_RECEIVE                      pCanNode->sMsgObj[1]        

#define CNTRLREG                        pCanNode->CntrlReg          
#define STATREG                         pCanNode->StatReg           
#define ERRORCOUNT                      pCanNode->ErrorCount        
#define BITTIMING                       pCanNode->BitTiming         
#define BRP_REG                         pCanNode->BRP_Reg           
#define INTERRUPTREG                    pCanNode->InterruptReg      
#define INTERRUPTREG1                   pCanNode->InterruptReg1     
#define TESTREG                         pCanNode->TestReg         
#define CANFUNCREG                      pCanNode->CAN_FuncReg
#define PARITYERRORCODE                 pCanNode->ParityErrorCode   
#define AUTOBUSONTIME1                  pCanNode->AutoBusOnTime1    
#define AUTOBUSONTIME2                  pCanNode->AutoBusOnTime2    
#define TRANSREQUESTX                   pCanNode->TransRequestX     
#define TRANSREQUEST(i)                 pCanNode->TransRequest[i]   
#define NEWDATAX                        pCanNode->NewDataX          
#define NEWDATA(i)                      pCanNode->NewData[i]        
#define INTERRPENDINGX                  pCanNode->InterrPendingX    
#define INTERRPENDING(i)                pCanNode->InterrPending[i]  
#define MESSAGEVALIDX                   pCanNode->MessageValidX     
#define MESSAGEVALID(i)                 pCanNode->MessageValid[i]   
#define INTPNDMUX                       pCanNode->IntPndMux[i]      
#define CAN_IO_CTRLTX                   pCanNode->can_IO_ctrlTx     
#define CAN_IO_CTRLRX                   pCanNode->can_IO_ctrlRx     





/* macros to set DLC and ID in rx-,tx-structures ---------------------------*/
/* MK... macros are used by the generation tool to fill the rx and tx structures */
/* In case the IDE bit is located in the ID registers, this bit has to be handled as must match.
   In general, this is done by setting the IDE bit to 0 in the .._MASK_.. macros.
*/

#define MK_RX_RANGE_MASK_IDSTD0(id)     (MK_STDID0(id))
#define MK_RX_RANGE_MASK_IDSTD1(id)     (0)
/* macros with postfix 2-4 not used */

#define MK_RX_RANGE_CODE_IDSTD0(id)     (MK_STDID0(id))
#define MK_RX_RANGE_CODE_IDSTD1(id)     (0)
/* macros with postfix 2-4 not used */

#define MK_RX_RANGE_MASK_IDEXT0(id)     ((vuint16)((((vuint32)(id) & 0xFFFF0000U) >> 16) & 0x1FFFU))
#define MK_RX_RANGE_MASK_IDEXT1(id)     (MK_EXTID1(id))
/* macros with postfix 2-4 not used */

#define MK_RX_RANGE_CODE_IDEXT0(id)     (MK_EXTID0(id))
#define MK_RX_RANGE_CODE_IDEXT1(id)     (MK_EXTID1(id))
/* macros with postfix 2-4 not used */



#define MK_STDID0(id)                   (((0x3FFFU & (id))<<2) & 0x1FFCU)
#define MK_STDID1(id)                   (0)



#define MK_EXTID0(id)                   ((vuint16)((((vuint32)(id) & 0xFFFF0000U) >> 16) & 0x1FFFU) | 0x4000U)
#define MK_EXTID1(id)                   ((vuint16)(id))




/* Message Configuration Register:
 * Example C16x:
 * DLC3 DLC2 DLC1 DLC0 Dir Xtd 0 0
 *                      |   |+------------- 0: standard ID; 1: exended ID
 *                      +------------------ 0: receive    ; 1: transmit
*/
#define C_RX_DIR             (0x0000U)      
#define C_TX_DIR             (0x2000U)
#define C_STD_ID             (0x0000U)                  
#define C_EXT_ID             (0x4000U)

#define MK_TX_DLC(dlc)       (dlc)
#define MK_TX_DLC_EXT(dlc)   (dlc)

#define XT_TX_DLC(dlc)       ((dlc)&0xF)  /* return code has to be vuint8 */


#if defined( C_SINGLE_RECEIVE_CHANNEL )
/* Bus-Off functions */
# define CanResetBusOffStart(a)  (CanInit(a))
# define CanResetBusOffEnd(a)

/* Bus-Sleep functions */
# define CanResetBusSleep(a)     (CanInit(a))

#else
/* Bus-Off functions */
# define CanResetBusOffStart(ch,a)  (CanInit((ch),(a)))
# define CanResetBusOffEnd(ch,a)
  
/* Bus-Sleep functions */
# define CanResetBusSleep(ch,a)     (CanInit((ch),(a)))
#endif


/* The macros CanRxActualIdRawx() have to provide the register context of the ID registers.
   It is not necessary to mask any bits. These macros are for internal use only and masking
   will be done in can_hls.c
*/
#if defined( C_ENABLE_EXTENDED_ID )
# define CanRxActualIdRaw0(rxStruct)     (((vuint16)*((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT)) ((rxStruct)->pChipMsgObj+2))) & 0x5FFFU)
# define CanRxActualIdRaw1(rxStruct)     ((vuint16)*((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT)) ((rxStruct)->pChipMsgObj )))
# define CanRxActualIdRaw2(rxStruct)      0
# define CanRxActualIdRaw3(rxStruct)      0
# define CanRxActualIdRaw4(rxStruct)      0
#else
# define CanRxActualIdRaw0(rxStruct)     (((vuint16)*((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT)) ((rxStruct)->pChipMsgObj+2))) & 0x5FFCU)  
# define CanRxActualIdRaw1(rxStruct)      0                                                             
# define CanRxActualIdRaw2(rxStruct)      0
# define CanRxActualIdRaw3(rxStruct)      0
# define CanRxActualIdRaw4(rxStruct)      0
#endif


/* Macros for CAN message access within ApplCanMsgReceived() or PreCopy() function */

#define CanRxActualExtId(rxStruct)         (((((vuint32)(*((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT))((rxStruct)->pChipMsgObj+2)))) & 0x0000FFFFU)<<16 ) & 0x1FFF0000U) | \
                                             (((vuint32)(*((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT))((rxStruct)->pChipMsgObj  )))) & 0x0000FFFFU)

#define CanRxActualStdId(rxStruct)         ((((vuint16)(*((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT))((rxStruct)->pChipMsgObj+2))) & 0xFFFCU)>>2) & (vuint16)0x7FF)
#define CanRxActualData(rxStruct,i)        ((*((rxStruct)->pChipMsgObj+8+(i))))


#if defined(C_CPUTYPE_BIGENDIAN)

# if defined( C_ENABLE_EXTENDED_ID )
#  define CanRxActualIdExtHi(rxStruct)     (*((rxStruct)->pChipMsgObj+2) & 0x1F)   /* return code has to be vuint8 */
#  define CanRxActualIdExtMidHi(rxStruct)  (*((rxStruct)->pChipMsgObj+3))          /* return code has to be vuint8 */
#  define CanRxActualIdExtMidLo(rxStruct)  (*((rxStruct)->pChipMsgObj))            /* return code has to be vuint8 */
#  define CanRxActualIdExtLo(rxStruct)     (*((rxStruct)->pChipMsgObj+1))          /* return code has to be vuint8 */
# endif

# define CanRxActualIdType(rxStruct)        (((vuint16)(*((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT))((rxStruct)->pChipMsgObj+2)))) & 0x4000U)
# define CanRxActualDLC(rxStruct)           ((*((rxStruct)->pChipMsgObj+5)) & 0x000FU)    

# if defined (C_SINGLE_RECEIVE_CHANNEL )
#   define CanRxActualErrorCounter()  (*(V_DEF_P2SFR_CAN(V_NONE, vuint8, VAR_NOINIT))(CanBasisAdr[0]+10))
#   define CanTxActualErrorCounter()  (*(V_DEF_P2SFR_CAN(V_NONE, vuint8, VAR_NOINIT))(CanBasisAdr[0]+11))
# else
#  define CanRxActualErrorCounter(channel)  (*(V_DEF_P2SFR_CAN(V_NONE, vuint8, VAR_NOINIT))(CanBasisAdr[channel]+10))
#  define CanTxActualErrorCounter(channel)  (*(V_DEF_P2SFR_CAN(V_NONE, vuint8, VAR_NOINIT))(CanBasisAdr[channel]+11))
# endif

#endif




/* Macros for CAN message access within PreTransmit() function */
#if defined( C_ENABLE_EXTENDED_ID )
# define CanTxWriteActId(txStruct,id)      { *((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT))((txStruct).pChipData-6)) = MK_STDID0(id) | 0xA000U; \
                                             *((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT))((txStruct).pChipData-8)) = 0; }

# define CanTxWriteActExtId(txStruct,id)   { *((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT))((txStruct).pChipData-6)) = MK_EXTID0(id) | 0xA000U; \
                                             *((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT))((txStruct).pChipData-8)) = MK_EXTID1(id); } 
#else
# define CanTxWriteActId(txStruct,id)      { *((V_DEF_P2SFR_CAN(V_NONE, vuint16, VAR_NOINIT))((txStruct).pChipData-6)) = MK_STDID0(id) | 0xA000U;}
#endif

#if defined(C_CPUTYPE_BIGENDIAN)
# define CanTxWriteActDLC(txStruct,dlc)     { *((txStruct).pChipData-3) = ( (*((txStruct).pChipData-3) & 0xF0) | (dlc) ); }
#endif


/* Macros to fill variables of the type tCanMsgTransmitStruct */
#define CanMsgTransmitSetStdId(pCanMsgTransmitStruct, id)                 { (pCanMsgTransmitStruct)->IdRaw = MK_STDID0(id); }

#define CanMsgTransmitSetExtId(pCanMsgTransmitStruct, id)                 { (pCanMsgTransmitStruct)->IdRawExt = (vuint16)(MK_EXTID1(id)); \
                                                                            (pCanMsgTransmitStruct)->IdRaw    = (vuint16)(MK_EXTID0(id)); }

#define CanMsgTransmitSetDlc(pCanMsgTransmitStruct, dlc)                  { (pCanMsgTransmitStruct)->DlcRaw = MK_TX_DLC(dlc); }
#define CanMsgTransmitSetData(pCanMsgTransmitStruct, dataByte, msgData)   { (pCanMsgTransmitStruct)->DataFld[(dataByte)] = (msgData); }


/* macros for buffer access */
#define StartRxReadSync()                 (VStdSuspendAllInterrupts())
#define EndRxReadSync()                   (VStdResumeAllInterrupts())

#define StartRxWriteSync()                (VStdSuspendAllInterrupts())
#define EndRxWriteSync()                  (VStdResumeAllInterrupts())

#define StartTxReadSync()
#define EndTxReadSync()

#define StartTxWriteSync()                (VStdSuspendAllInterrupts())
#define EndTxWriteSync()                  (VStdResumeAllInterrupts())

#define StartRxWriteCANSync() 
#define EndRxWriteCANSync()   

#define StartRxReadCANSync()  
#define EndRxReadCANSync()    

#define StartRxFullCANReadSync(Obj)       (VStdSuspendAllInterrupts())
#define EndRxFullCANReadSync(Obj)         (VStdResumeAllInterrupts())

#define StartRxFullCANWriteSync(obj)      (VStdSuspendAllInterrupts())
#define EndRxFullCANWriteSync(obj)        (VStdResumeAllInterrupts())

/* macros for flag access */
#define CanStartFlagWriteSync()           (VStdSuspendAllInterrupts())
#define CanEndFlagWriteSync()             (VStdResumeAllInterrupts())



#define CAN_HL_MIN(x,y) (((x)>(y)) ? (y) : (x))
#define CAN_HL_MAX(x,y) (((x)<(y)) ? (y) : (x))

/***************************************************************************************************/
/* General definition of checking macros */
# define Can_CheckErrorReturnVoid(cond, api, err)        \
{ if(!(cond)){                                           \
    Can_CallDetReportError((api), (err));                \
    return;                                              \
}}
# if defined( C_ENABLE_INDIVIDUAL_POLLING )
#  define Can_CheckErrorReturnVoid_EnableChIR(cond, api, err)        \
{ if(!(cond)){                                           \
    Can_EnableControllerInterrupts((uint8)channel);      \
    Can_CallDetReportError((api), (err));                \
    return;                                              \
}}
# else
#  define Can_CheckErrorReturnVoid_EnableChIR(cond, api, err)        \
{ if(!(cond)){                                           \
    Can_CallDetReportError((api), (err));                \
    return;                                              \
}}
# endif
# define Can_CheckErrorReturnValue(cond, api, err, ret)  \
{ if(!(cond)){                                           \
    Can_CallDetReportError((api), (err));                \
    return(ret);                                         \
}}
# define Can_CheckErrorContinue(cond, api, err)          \
{ if(!(cond)){                                           \
    Can_CallDetReportError((api), (err));                \
}}
# define Can_CheckErrorLoopContinue(cond, api, err)      \
{ if(!(cond)){                                           \
    Can_CallDetReportError((api), (err));                \
    continue;                                            \
}}
#if !defined(CAN_SILENT_CHECK)
# define CAN_SILENT_CHECK STD_OFF
#endif

/***************************************************************************************************/
/* Macros for DET abstraction */
#if(CAN_DEV_ERROR_DETECT == STD_ON) /* CAN026, CAN028, CAN091, CAN082, CAN083 */
# define Can_CheckDetErrorReturnVoid(cond, api, err)             Can_CheckErrorReturnVoid((cond), (api), (err))
# define Can_CheckDetErrorReturnVoid_EnableChIR(cond, api, err)  Can_CheckErrorReturnVoid_EnableChIR((cond), (api), (err))
# define Can_CheckDetErrorReturnValue(cond, api, err, ret)       Can_CheckErrorReturnValue((cond), (api), (err), (ret))
# define Can_CheckDetErrorContinue(cond, api, err)               Can_CheckErrorContinue((cond), (api), (err))
# define Can_CheckDetErrorLoopContinue(cond, api, err)           Can_CheckErrorLoopContinue((cond), (api), (err))
  /* CAN235, CAN082, CAN083, CAN027, CAN424 */
# if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
#  define Can_CallDetReportError(api, err)                 ((void) Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, (api), (err)))
# else
#  define Can_CallDetReportError(api, err)                 (Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, (api), (err)))
# endif
# define assertHardware(a, b, c)  if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertInternal(a, b, c)  if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertUser(a, b, c)      if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertGen(a, b, c)       if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define C_ENABLE_HARDWARE_CHECK
# define C_ENABLE_INTERNAL_CHECK
# define C_ENABLE_USER_CHECK
# define C_ENABLE_GEN_CHECK
#else
# define Can_CheckDetErrorReturnVoid(cond, api, err)
# define Can_CheckDetErrorReturnVoid_EnableChIR(cond, api, err)
# define Can_CheckDetErrorReturnValue(cond, api, err, ret)
# define Can_CheckDetErrorContinue(cond, api, err)
# define Can_CheckDetErrorLoopContinue(cond, api, err)
# define Can_CallDetReportError(api, err)
# define assertHardware(a, b, c)
# define assertInternal(a, b, c)
# define assertUser(a, b, c)
# define assertGen(a, b, c)
#endif

/***************************************************************************************************/
/* Macros for SBSW check abstraction */
#if(CAN_SILENT_CHECK == STD_ON)
# define Can_SilentBswCheckErrorReturnVoid(cond, api, err)            Can_CheckErrorReturnVoid( (cond), (api), (err))
# define Can_SilentBswCheckErrorReturnVoid_EnableChIR(cond, api, err) Can_CheckErrorReturnVoid_EnableChIR( (cond), (api), (err))
# define Can_SilentBswCheckErrorReturnValue(cond, api, err, ret)      Can_CheckErrorReturnValue( (cond), (api), (err), (ret))
#else
# define Can_SilentBswCheckErrorReturnVoid(cond, api, err)            Can_CheckDetErrorReturnVoid( (cond), (api), (err) )  
# define Can_SilentBswCheckErrorReturnVoid_EnableChIR(cond, api, err) Can_CheckDetErrorReturnVoid_EnableChIR( (cond), (api), (err) )  
# define Can_SilentBswCheckErrorReturnValue(cond, api, err, ret)      Can_CheckDetErrorReturnValue( (cond), (api), (err), (ret) )
#endif 

/***************************************************************************************************/
/* Macros for Critical Area abstraction */
#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
# define Can_EnterCritical(area)     SchM_Enter_Can_##area() /* PRQA S 0342 */ /* MD_Can_0342 */
# define Can_LeaveCritical(area)     SchM_Exit_Can_##area() /* PRQA S 0342*/ /* MD_Can_0342 */
#else
# define Can_EnterCritical(area)     SchM_Enter_Can(area) /* do not use double brackets here ESCAN00060494 */
# define Can_LeaveCritical(area)     SchM_Exit_Can(area)
#endif

#define CanDeclareGlobalInterruptOldStatus
/* CAN_EXCLUSIVE_AREA_0 called only by LL code */
#define CanSingleGlobalInterruptDisable()     Can_EnterCritical(CAN_EXCLUSIVE_AREA_0)
#define CanSingleGlobalInterruptRestore()     Can_LeaveCritical(CAN_EXCLUSIVE_AREA_0)
#define CanGlobalInterruptDisable()           Can_EnterCritical(CAN_EXCLUSIVE_AREA_0)
#define CanGlobalInterruptRestore()           Can_LeaveCritical(CAN_EXCLUSIVE_AREA_0)
#define CanNestedGlobalInterruptDisable()     Can_EnterCritical(CAN_EXCLUSIVE_AREA_0)
#define CanNestedGlobalInterruptRestore()     Can_LeaveCritical(CAN_EXCLUSIVE_AREA_0)

/* For LL: parameter has to be 'channel' not CAN_CHANNEL_PARA_ONLY */
# define CAN_CAN_INTERRUPT_RESTORE(ch)  Can_EnableControllerInterrupts((uint8)(ch))
# define CAN_CAN_INTERRUPT_DISABLE(ch)  Can_DisableControllerInterrupts((uint8)(ch))

/***************************************************************************************************/
/* Macros for LL-HLL compatibility */
#if defined(C_ENABLE_SLEEP_WAKEUP)
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON )
#  define APPL_CAN_WAKEUP(ch)        (CanHL_WakeUpHandling())
# else
#  define APPL_CAN_WAKEUP(ch)        (CanHL_WakeUpHandling(ch))
# endif
# if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
/* remove canStatusReq - sleep because wakeup may occur before sleep is reached and will cause DET otherwise */
#  define CAN_WAKEUP(ch)              canStatusReq[ch] &= (uint8)(~CAN_STATUS_SLEEP); ((void) Can_SetControllerMode((uint8)(ch), CAN_T_WAKEUP))
# else
#  define CAN_WAKEUP(ch)              ((void) Can_SetControllerMode((uint8)(ch), CAN_T_WAKEUP))
# endif
#endif

/***************************************************************************/
/* error codes                                                             */
/***************************************************************************/
/* error numbers for User Assertions 0x20-0x3f - hardware depended */

/* error numbers for Gentool Assertions 0x60-0x7f - hardware depended */
# define kErrorToManyFullCanObjects              ((vuint8)0x63)
/* error numbers for Hardware Assertions 0xa0-0xbf - hardware depended */
#define kErrorRxHwBufferBusy        0xa0u
#define kErrorTxHwBufferBusy        0xa1u

/* error numbers for Internal Assertions 0xe0-0xff - hardware depended */
# define kErrorIllIrptNumber                     ((vuint8)0xe2u)
# define kErrorHwObjNotInPolling                 ((vuint8)0xe3u)

/***************************************************************************/
/* Special switches need by CAN driver                                     */
/***************************************************************************/

/***************************************************************************/
/* data types                                                              */
/***************************************************************************/
typedef struct sCanRxInfoStruct
{
/* uint8 Channel; */
  CanChipMsgPtr  pChipMsgObj;
  CanChipDataPtr pChipData;
/* Can_HwHandleType  Handle; */
/* CPU-specific part */
} tCanRxInfoStruct;



/***************************************************************************/
/* module global variable declaration                                      */
/***************************************************************************/

/***************************************************************************/
/* External Declarations                                                   */
/***************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***************************************************************************/
/* local function prototypes (only internal usage)                         */
/***************************************************************************/
#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInit(CAN_CHANNEL_CANTYPE_FIRST uint8 initObject);
#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
#endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanFullCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
#endif
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_ErrorHandling(CAN_HW_CHANNEL_CANTYPE_ONLY);
# if defined (C_ENABLE_SLEEP_WAKEUP)
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_WakeUpHandling(CAN_CHANNEL_CANTYPE_ONLY);
# endif
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_TxConfirmation(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle);

#if defined(C_ENABLE_HW_LOOP_TIMER) || (((CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)) ) /* always used for sync mode */
# if (CAN_HW_LOOP_SUPPORT_API != STD_ON)
V_DEF_FUNC(CAN_STATIC, Can_ReturnType, STATIC_CODE) ApplCanTimerLoop(CAN_CHANNEL_CANTYPE_FIRST uint8 source);
# endif
#endif

#if (CAN_DEV_ERROR_DETECT == STD_ON) && defined(CAN_ENABLE_CORE_GEN_CHECK)
V_DEF_FUNC(CAN_STATIC, Can_ReturnType, STATIC_CODE) Can_CheckGenDataController(CAN_HW_CHANNEL_CANTYPE_ONLY);
#endif

#define CAN_STOP_SEC_STATIC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#if (CAN_MICROSAR_VERSION == CAN_MSR403)
# define CAN_START_SEC_CODE  /*--------------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerConfigPtrType ControllerConfigPtr );

# define CAN_STOP_SEC_CODE  /*----------------------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

#endif /* __AUTOSAR_CAN_HL_H__ */

/* End of channel */



/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */

/************   Organi, Version 3.9.1 Vector-Informatik GmbH  ************/
