/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */

/* STARTSINGLE_OF_MULTIPLE */

#ifdef C_COMP_TI_TMS470_DCAN
/* ***************************************************************************
| Project Name: DrvCan_TMS470Dcan
|    CBD: File Name: CAN_DRV.C
|    Asr: File Name: Can.c
|
|  Description: Implementation of the CAN driver
|               Target systems: TMS470PSF761
|               Compiler:       Texas Instruments
|               TechnicalReference: TechnicalReference_DrvCanAsr_Tms470_Dcan.pdf */
#endif


/*----------------------------------------------------------------------------
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
| --------     ---------------------     -------------------------------------
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
| ---------  ---  ------  ----------------------------------------------------
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
|************************************************************************* */
/*****************************************************************************
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
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
| 2006-03-16 1.04.00 Wr   - Added channel compatibility defines
|                         - Removed local parameter canHwChannels
|                         - Changed order of CanLL_TransmitLocalParameter
|                           and CanLL_TxTransmissionLocalParameter in Can_Write()
|                         - Rename CanWakeup() to CanHL_WakeupHandling()
| 2006-04-19 1.05.00 Wr   - Added V850 specific handling for transition to sleep   
| 2006-05-22 2.00.00 Bir  - Support for AutoSar 2.0
|                         - Include stucture update
|                         - DET - switch change
|                         - API adaption Can_Init(), Can_Write()
|                         - add Can_GetVersionInfo()
| 2006-06-06 2.01 Bir     - internal naming corrections for version defines
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
| 2006-09-04 2.08.00 Bir  - minor change: ControllerName length expand to 20
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
|                 Bir     - Move Fullcan Overrun notification token behind FullCAN Begin token
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
|                         - remove FullCAN switches to secure postbuild functionality without compile with fullcan's
|                         - ESCAN00020129: Compiler error: identifier "i" is undefined
|                         - Reduce BasicCAN logical mailbox to real BasicCAN (DLC_FIFO inlcude size of Basic CAN)
|                         - Reduce Unused mailboxes logical mailbox to amount of sections (DLC_FIFO inlcude size of section)
|                         - Move all version defines from Proto.h to CAN.h (license scanning)
|                         - set DLC also for FullCAN Tx objects
|                         - generated Tables: CanActiveSendPdu,CanActiveSendState (size matter at link time)
|                         - return not ok for try to set sleep mode but failed in hw
|                         - move multichannel api define to can.h
|                         - do "CanLL_InitPowerOn" before "CanLL_InitPowerOnChannelSpecific"
|                         - move osek-switches out of irq.c
|                         - add CanLL_InitMemoryPowerOn token for special ll init
| 2007-08-28 2.21.00 Bir  - ESCAN00022112: Rx Basic CAN used with wrong Stop index
|                         - renaming "CaninitObject" to "Can_Init_CtrlIdx"
|                         - ESCAN00022168: Driver does not enter Stop mode for Sleep request (when sleep is not supported)
|                         - ESCAN00022232: Add stop-mode compatibility for FNOS-RP migration
|                         - ESCAN00022262: CanResetBusOffEnd() used with only one parameter
|                         - Add new Token "CanLL_RxFull_SearchHandle" for special HW-support (XGate)
|                         - ESCAN00022390: Hw start-stop-index changed to RAM-table
| 2007-10-15 2.22.00 Bir  - ESCAN00022773: use of #ifndef instead of #if !defined
|                         - ESCAN00022774: improve runtime while change mode (stop to sleep)
|                         - ESCAN00023040: minor improvements (add CAN177, CAN179, CAN181, CAN184, CAN186)
|                         - ESCAN00023040: remove Interrupt locking in Can_write() due to CanIf do this
|                         - ESCAN00023038: Multiple ECU
|                         - ESCAN00023047: Add version check
|                         - ESCAN00023049: change API of can_init() to one parameter, Add const in Can_InitController() + Add Can_InitStruct API
|                         - ESCAN00023127: compiler warnings due to dummy assignments (used to satisfy other compilers)
|                         - ESCAN00023265: nothing to do here
|                         - ESCAN00023265: remove brackets around Can_EnterCritical
|                         - QAC / MISRA reworks
|                         - Add memory qualifiers
|                         - Review reworks
| 2007-12-14 2.23.00 Bir  - ESCAN00023442: Add extended Id support
|                         - some small changes for cancellation (cancel only less priority objects - more efficient)
|                         - protect Can_MainFunction_Read against reentrant (ASR spec)
|                         - ESCAN00024354: Ignore API call with controller deactivated by identity
|                         - review rework
| 2008-02-06 3.00.00 Bir  - ESCAN00024406: ASR3.0
| 2008-03-25 3.01.00 Bir  - Add dummy assignment in "ResetBusOffEnd" avoid compiler warnings
|                         - ESCAN00025672: review reworks
|                         - ESCAN00025664: Message send with wrong ID type
|                         - ESCAN00026087: Case sensitive naming for all File names (and includes)
|                         - ESCAN00026186: Extension for MSR3.0 LinkTime checks
|                         - ESCAN00025957: No access on "DEM-events" via DEM created and exported constant values
| 2008-05-14 3.02.00 Bir  - ESCAN00026859: V_MEMRAM0 not allowed for type cast
|                         - ESCAN00026861: Token extern declaration added
|                         - ESCAN00026990: Add LL-Token to reject Remote frames
| 2008-06-30 3.03.00 Bir  - ESCAN00027986 +(ESCAN00025773): Code optimization to save ROM and runtime: 
|                           + Start/StopLoop as macro
|                           + Max Loop counter define move to LL
|                           + Add some FullCan switches to be organified for Basic CAN controllers
|                           + Multiple Search for Basic CAN hw object
|                           + CanInterrupt Lock only in nested interrupt case (CAN_NESTED_INTERRUPTS)
|                           + remove some hw-start/stop indexes and there calculation use instead info from mailbox-table
|                         - ESCAN00028069: change controller amount to library capable setting
|                         - ESCAN00026596: Extension for MSR3.0 generator version checks
| 2008-08-19 3.03.01 Bir  - minor review changes
|                         - ESCAN00029385: change naming finishFullCan to finishRxFullCan (canbedded compliance)
| 2008-09-11 3.04.00 Bir  - ESCAN00029942: Generator Version Check failed
| 2008-09-18 3.05.00 Bir  - ESCAN00029830: Add Linktime/Postbuild config CRC check
|                         - ESCAN00029434: rename "INTERRUPT" and "POLLING" switch
| 2008-10-15 3.06.00 Bir  - remove CAN_HL_HW_x_STOPINDEX -> not used in HL and does not work for LL
|                         - ESCAN00029707: change transition from uninit->start->stop to uninit->stop
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
|                         - ESCAN00035606: Report DEM as DET "CAN_DEV_TIMEOUT_DETECT"
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
|                         - ESCAN00045682: Compiler warning: dead assignment to "x" eliminated
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
| 2011-04-05 4.00.01  Bir - void cast DET call for MSR40 + review reworks (minors)
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
| 2011-12-14 4.01.02  Bir - ESCAN00055566: Include of det with camel case spelling
| 2011-12-15 4.01.03  Bir - ESCAN00055589: CAN219
|                         - ESCAN00056004: Add Code Traceability to AutoSar SWS
|                         - Add explicit type casts to satisfy COSMIC compilers (Mcs12x)
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
|                         - Add support for FullCAN Tx cancellation only
|                         - ESCAN00062679: Add source defines according to MICROSAR template source file
| 2012-12-10 4.04.01  Bir - Rework Silent BSW
| 2013-01-28 4.04.02  Bir - ESCAN00064474: Modify Hook_On (code can be removed by integration organi)
| 2013-02-02 4.05.00  Bir - optimize token StopReinit usage
|                         - move some global compatibility defines from proto.h to can.h
|                         - ESCAN00063652: RxQueue extension to 16bit size
|                         - ESCAN00064324: AR4-325: Implement Post-Build Loadable
|                         - ESCAN00066278: Incorrect comment description for function Can_CheckWakeup / Can_Cbk_CheckWakeup
| 2013-06-11 4.05.01  Bir - ESCAN00067936: Can_GetStatus wrongly returns CAN_STATUS_INCONSISTENT
|                           Add QAC deviations for 6010, 6030, 6050, 6080
| 2013-06-12 4.06.00  Tvi/Bir - ESCAN00069107: AR4-397: Implement support for CAN-FD according to ASR4.1.1
|                           ESCAN00070197: Compiler warning: variable canConfigPtr was declared but never referenced
|                           ESCAN00068900: Compiler warning
|                           ESCAN00067711: AR4-328 / RTM measurement R8
|                           ESCAN00070625: Adapt usage of CanResetBusOffEnd
|                           ESCAN00071048: Support null_ptr data in Can_Write() for DLC==0
|***************************************************************************/

/* CAN077, CAN079, CAN394 */
/***************************************************************************/
/* Include files                                                           */
/***************************************************************************/
#define C_DRV_INTERNAL /* compatibility */
#define CAN_SOURCE     /* testability */
#define __CAN_SRC__    /* for all msr module (used by RTM) */

/* PRQA S 3109 EOF */ /* MD_Can_3109 */
/* PRQA S 2001 EOF */ /* MD_Can_2001 */
/* PRQA S 2006 EOF */ /* MD_Can_2006 */
/* PRQA S 0488 EOF */ /* MD_Can_17.4 */
/* PRQA S 0489 EOF */ /* MD_Can_17.4 */
/* PRQA S 0750 EOF */ /* MD_Can_0750 */
/* PRQA S 3412 EOF */ /* MD_Can_3412 */
/* PRQA S 3458 EOF */ /* MD_Can_3458 */
/* PRQA S 3453 EOF */ /* MD_Can_3453 */
/* PRQA S 0850 EOF */ /* MD_Can_0850 */
/* PRQA S 0715 EOF */ /* MD_Can_0715 */
/* PRQA S 0857 EOF */ /* MD_Can_0857 */
/* PRQA S 0828 EOF */ /* MD_Can_0828 */

/* CAN034, CAN058, CAN238 */
/* CAN036 */
#include "CanIf_Cbk.h"   /* for callback declaration */
/* CAN222 */
#include "CanIf.h"       /* for version check */
#include "canproto.h"    /* have to be last include due to channel define will lead to problems */


#if (CAN_DEV_ERROR_DETECT == STD_ON)
/* CAN393 */
# include "Det.h"
#endif
#if (CAN_MICROSAR_VERSION != CAN_MSR403)
# if !defined( V_SUPPRESS_EXTENDED_VERSION_CHECK )
#  include "v_ver.h"
# endif
#endif

#if !defined (CAN_AMD_RUNTIME_MEASUREMENT)
# define CAN_AMD_RUNTIME_MEASUREMENT STD_OFF
#endif
#if (CAN_AMD_RUNTIME_MEASUREMENT == STD_ON)
# include "AmdRtm.h"
#endif

#if !defined (CAN_RUNTIME_MEASUREMENT_SUPPORT)
# define CAN_RUNTIME_MEASUREMENT_SUPPORT STD_OFF
#endif
#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
/* AR4-328 */
# include "Rtm.h"
#endif

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* CAN111 not the SW version but all file versions that represent the SW version are checked */
#if (DRVCAN__COREASR_VERSION           != 0x0406u)
# error "Source and Header file are inconsistent!"
#endif
#if (DRVCAN__COREASR_RELEASE_VERSION   != 0x00u)
# error "Source and Header file are inconsistent!"
#endif
#if (DRVCAN_APIASR_VERSION             != 0x0403u)
# error "Source and Header file are inconsistent!"
#endif
#if (DRVCAN_APIASR_RELEASE_VERSION     != 0x00u)
# error "Source and Header file are inconsistent!"
#endif
#if defined(CAN_GEN_BASE_VERSION)
# if (CAN_GEN_BASE_VERSION              != 0x0106u)
#  error "Source and Generated Header file are inconsistent!"
# endif
#elif defined(CAN_GEN_BASE_CFG5_VERSION)
# define CAN_GEN_BASE_VERSION  CAN_GEN_BASE_CFG5_VERSION
# if (CAN_GEN_BASE_CFG5_VERSION         != 0x0101u)
#  error "Source and Generated Header file are inconsistent!"
# endif
#else
# error "No CAN_GEN_BASE_VERSION nor CAN_GEN_BASE_CFG5_VERSION is defined"
#endif
#if( DRVCAN_TMS470DCANASR_VERSION != 0x0123)
 #error "Source and Header file are inconsistent!"
#endif

#if( DRVCAN_TMS470DCANASR_RELEASE_VERSION != 0x00)
 #error "Source and Header file are inconsistent!"
#endif

# if( CAN_GEN_Tms470DcanAsr_VERSION != 0x0101)
 #error "Generated Data are inconsistent!"
# endif

#if (CAN_MICROSAR_VERSION != CAN_MSR403)
# if !defined( V_SUPPRESS_EXTENDED_VERSION_CHECK )
/* The name of this const variable is defined via v_ver.h and depends on the version of the C file. The value of the const variable is also defined externally and is used for consistency checks, too. */
#  define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
V_DEF_CONST(V_NONE, uint32, CONST) DRVCAN_TMS470DCANASR_LIB_SYMBOL = DRVCAN_TMS470DCANASR_LIB_VERSION;   /* PRQA S 3408 */ /* MD_Can_3408_Asr_libCheck */
#  define CAN_STOP_SEC_CONST_UNSPECIFIED   /*--------------------------------*/
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif
#endif

/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
#if defined(IF_ASRIFCAN_VERSION) && defined(CANIF_VENDOR_ID)
# if (CANIF_VENDOR_ID == 0x001E) 
#   define CAN_USE_VECTOR_IF
#  if (IF_ASRIFCAN_VERSION < 0x0410)
#   define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#  endif
# endif
#endif
/* Compatibility to CBD */
#define canCanInterruptCounter canInterruptCounter

/* Hook mapping */
# if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
#define CanHookBegin_Can_Init()                              Rtm_Start(RtmConf_RtmMeasurementPoint_Can_Init)
#define CanHookEnd_Can_Init()                                Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_Init)
#define CanHookBegin_Can_InitController()                    Rtm_Start(RtmConf_RtmMeasurementPoint_Can_InitController)
#define CanHookEnd_Can_InitController()                      Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_InitController)
#define CanHookBegin_Can_SetControllerMode()                 Rtm_Start(RtmConf_RtmMeasurementPoint_Can_SetControllerMode)
#define CanHookEnd_Can_SetControllerMode()                   Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_SetControllerMode)
#define CanHookBegin_Can_Write()                             Rtm_Start(RtmConf_RtmMeasurementPoint_Can_Write)
#define CanHookEnd_Can_Write()                               Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_Write)

# else /* BRS runtime measurement */
#define CanHookBegin_Can_Init()
#define CanHookEnd_Can_Init()
#define CanHookBegin_Can_InitController() \

#define CanHookEnd_Can_InitController() \

#define CanHookBegin_Can_SetControllerMode() \

#define CanHookEnd_Can_SetControllerMode() \

#define CanHookBegin_Can_Write() \

#define CanHookEnd_Can_Write() \

# endif

#define CanHookBegin_CanHL_TxConfirmation() \

#define CanHookEnd_CanHL_TxConfirmation() \

#define CanHookBegin_CanBasicCanMsgReceived() \

#define CanHookEnd_CanBasicCanMsgReceived() \

#define CanHookBegin_CanFullCanMsgReceived() \

#define CanHookEnd_CanFullCanMsgReceived() \

#define CanHookBegin_Can_GetVersionInfo()
#define CanHookEnd_Can_GetVersionInfo()
#define CanHookBegin_Can_InitMemory()
#define CanHookEnd_Can_InitMemory()
#define CanHookBegin_Can_InitStruct()
#define CanHookEnd_Can_InitStruct()
#define CanHookBegin_Can_ChangeBaudrate()
#define CanHookEnd_Can_ChangeBaudrate()
#define CanHookBegin_Can_CheckBaudrate()
#define CanHookEnd_Can_CheckBaudrate()
#define CanHookBegin_Can_SetBaudrate()
#define CanHookEnd_Can_SetBaudrate()
#define CanHookStateChange_StartSync( oldState, newState )
#define CanHookStateChange_StopSync( oldState, newState )
#define CanHookStateChange_WakeupSync( oldState, newState )
#define CanHookStateChange_SleepSync( oldState, newState )
#define CanHookStateChange_StartAsync( oldState, newState )
#define CanHookStateChange_StopAsync( oldState, newState )
#define CanHookStateChange_WakeupAsync( oldState, newState )
#define CanHookStateChange_SleepAsync( oldState, newState )
#define CanHookBegin_Can_DisableControllerInterrupts()
#define CanHookEnd_Can_DisableControllerInterrupts()
#define CanHookBegin_Can_EnableControllerInterrupts()
#define CanHookEnd_Can_EnableControllerInterrupts()
#define CanHookBegin_Can_CheckWakeup()
#define CanHookEnd_Can_CheckWakeup()
#define CanHookBegin_Can_MainFunction_Write() \

#define CanHookEnd_Can_MainFunction_Write() \

#define CanHookBegin_Can_MainFunction_Read() \

#define CanHookEnd_Can_MainFunction_Read() \

#define CanHookBegin_Can_MainFunction_BusOff()
#define CanHookEnd_Can_MainFunction_BusOff()
#define CanHookBegin_Can_MainFunction_Wakeup()
#define CanHookEnd_Can_MainFunction_Wakeup()
#define CanHookBegin_Can_MainFunction_Mode()
#define CanHookEnd_Can_MainFunction_Mode()
#define CanHookBegin_Can_CancelTx()
#define CanHookEnd_Can_CancelTx()
#define CanHookBegin_Can_ResetBusOffStart()
#define CanHookEnd_Can_ResetBusOffStart()
#define CanHookBegin_Can_ResetBusOffEnd()
#define CanHookEnd_Can_ResetBusOffEnd()
#define CanHookBegin_Can_GetStatus()
#define CanHookEnd_Can_GetStatus()

#if defined (MISRA_CHECK)
# pragma PRQA_MACRO_MESSAGES_OFF "CanSetPointerToCanHardware",     0303,0306       /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_CanInterruptDisable",      0303,0306       /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_CanInterruptRestore",      0277,0303,0306  /* MD_Can_0277_negation */ /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_TxIsHWObjFree",            0303,0306       /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsSleep",                0303,0306       /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsStop",                 0303,0306,3344  /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */ /* MD_Can_3344_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsBusOff",               0303,0306,3344  /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */ /* MD_Can_3344_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsPassive",              0303,0306,3344  /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */ /* MD_Can_3344_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsWarning",              0303,0306,3344  /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */ /* MD_Can_3344_LL */
#endif

/* Define chiphardware                     */
/* Constants concerning can chip registers */
/* control registers for msg objects       */
   
#define kClearAll          ((vuint16)0x0000)       /* 00000000 00000000 */ /* use to clear all Bit in a word     */
#define kClearAll32        ((vuint32)0x00000000)   /* 00000000 00000000 */ /* use to clear all Bits in 32-Bit Register */
#define kErrBusOff         ((vuint16)0x0080)       /* 00000000 10000000 */ /* Error:  Busoff  Limit reached      */
#define kErrWarning        ((vuint16)0x0040)       /* 00000000 01000000 */ /* Error:  Warning Limit reached      */
#define kErrPassive        ((vuint16)0x0020)       /* 00000000 00100000 */ /* Error:  Passive Limit reached      */
#define kWakeupPending     ((vuint16)0x0200)       /* 00000000 00100000 */ /* Status: CAN was waked up           */


/* defines to test a bit in a register */
#define kIFxBusy           ((vuint16)0x8000)       /* 10000000 00000000 */ /* Test IFx Command Request           */ 
#define kCanStatusInt      ((vuint16)0x8000)       /* 10000000 00000000 */ /* Statusinterrupt in CAN_Cell        */

/* defines to set a Bit in the CAN Control Register */
#define kSetWUBA           ((vuint32)0x02000000)   /* 00000000 00000000 */
#define kSetPDR            ((vuint32)0x01000000)   /* 00000000 00000000 */
#define kSetDE3            ((vuint32)0x00100000)   /* 00000000 00000000 */
#define kSetDE2            ((vuint32)0x00080000)   /* 00000000 00000000 */
#define kSetDE1            ((vuint32)0x00040000)   /* 00000000 00000000 */
#define kSetIE1            ((vuint32)0x00020000)   /* 00000000 00000000 */
#define kSetInitDbg        ((vuint32)0x00010000)   /* 00000000 00000000 */
#define kSetSWR            ((vuint32)0x00008001)   /* 00000000 00000000 */ /* Ou: Init bit must be same time set in case of 16/32-bit accesses  */
#define kSetPMD            ((vuint32)0x00001400)   /* 00000000 00000000 */
#define kSetABO            ((vuint32)0x00000200)   /* 00000000 00000000 */
#define kSetIDS            ((vuint32)0x00000100)   /* 00000000 00000000 */
                                               
#define kSetTest           ((vuint32)0x00000080)   /* 00000000 10000000 */
#define kSetCCE            ((vuint32)0x00000040)   /* 00000000 01000000 */
#define kSetDAR            ((vuint32)0x00000020)   /* 00000000 00100000 */
#define kSetEIE            ((vuint32)0x00000008)   /* 00000000 00001000 */
#define kSetSIE            ((vuint32)0x00000004)   /* 00000000 00000100 */
#define kSetIE             ((vuint32)0x00000002)   /* 00000000 00000010 */
#define kSetInit           ((vuint32)0x00000001)   /* 00000000 00000001 */

/* defines to set a Bit in the Status Register */
#define kPDA               ((vuint16)0x0400)       /* 00000100 00000000 */
#define kRxOk              ((vuint16)0x0010)       /* 00000000 00010000 */
#define kTxOk              ((vuint16)0x0008)       /* 00000000 00001000 */

/* defines to set a Bit in the IFx Command Mask Register */
#define kSetWrRd           ((vuint16)0x0080)       /* 00000000 10000000 */
#define kSetMask           ((vuint16)0x0040)       /* 00000000 01000000 */
#define kSetArb            ((vuint16)0x0020)       /* 00000000 00100000 */
#define kSetControl        ((vuint16)0x0010)       /* 00000000 00010000 */
#define kSetClrIntPnd      ((vuint16)0x0008)       /* 00000000 00001000 */
#define kSetTxRqstNDat     ((vuint16)0x0004)       /* 00000000 00000100 */
#define kSetDataA          ((vuint16)0x0002)       /* 00000000 00000010 */
#define kSetDataB          ((vuint16)0x0001)       /* 00000000 00000001 */

/* defines to set a Bit in the IFx Mask Register */
#define kSetMsgVal         ((vuint16)0x8000)       /* 10000000 00000000 */
#define kSetDir            ((vuint16)0x2000)       /* 00100000 00000000 */

/* defines to set a Bit in the IFx Message Control Register */
#define kSetNewData       ((vuint16)0x8000)        /* 10000000 00000000 */
#define kSetMsgLst        ((vuint16)0x4000)        /* 01000000 00000000 */
#define kSetIntPnd        ((vuint16)0x2000)        /* 00100000 00000000 */
#define kSetUMask         ((vuint16)0x1000)        /* 00010000 00000000 */
#define kSetTxIE          ((vuint16)0x0800)        /* 00001000 00000000 */
#define kSetRxIE          ((vuint16)0x0400)        /* 00000100 00000000 */
#define kSetRmtEn         ((vuint16)0x0200)        /* 00000010 00000000 */
#define kSetTxRqst        ((vuint16)0x0100)        /* 00000001 00000000 */
#define kSetEoB           ((vuint16)0x0080)        /* 00000000 10000000 */

/* define to set a Bit in the Mask Register */
#define kSetMDir          ((vuint16)0x4000)        /* 01000000 00000000 */
#define kSetXtd           ((vuint16)0x4000)        /* 01000000 00000000 */
#define kSetMXtd          ((vuint16)0x8000)        /* 10000000 00000000 */

/* define to handle Stopmode */ 
#define kSetStopMode       ((vuint8)0x0001)

#if defined ( C_ENABLE_ERROR_POLLING )
# define kSetEnableErrorInt                        kClearAll
#else
# define kSetEnableErrorInt                        kSetEIE
#endif

#if defined ( C_ENABLE_INDIVIDUAL_POLLING ) 
#define CAN_INDIV_POLLING(channel,hwObjHandle)     CanHwObjIndivPolling[channel][hwObjHandle]
# define kSetEnableTxCanInt                        kSetTxIE
# define kSetEnableRxBasicCanInt                   kSetRxIE
# define kSetEnableRxFullCanInt                    kSetRxIE
#else
# define CAN_INDIV_POLLING(channel,hwObjHandle)    0
# if defined ( C_ENABLE_TX_POLLING )
# define kSetEnableTxCanInt                        kClearAll
# else
# define kSetEnableTxCanInt                        kSetTxIE
# endif

# if defined ( C_ENABLE_RX_BASICCAN_POLLING )
# define kSetEnableRxBasicCanInt                   kClearAll
# else
# define kSetEnableRxBasicCanInt                   kSetRxIE
# endif

# if defined ( C_ENABLE_RX_FULLCAN_POLLING )
# define kSetEnableRxFullCanInt                    kClearAll
# else
# define kSetEnableRxFullCanInt                    kSetRxIE
# endif
#endif

#if defined( C_ENABLE_MIXED_ID )
# define kSetUseUMask                              kSetUMask
#else
# define kSetUseUMask                              kClearAll
#endif




/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/
#define CAN_HL_TX_OFFSET_HW_TO_LOG(ch) (canTxOffsetHwToLog[(ch)]) /* used in LL */

#if ( CAN_MIXED_ID == STD_ON )
# define CAN_GET_ID_FOR_PRIOCHECK(id) ( (((id) & CAN_EXTENDED_ID_MASK) == CAN_EXTENDED_ID_MASK) ? ((id) & (uint32)(~(CAN_EXTENDED_ID_MASK))) : ((id)<<18) )
#else
# define CAN_GET_ID_FOR_PRIOCHECK(id) (id)
#endif
/* low prio first */
#define CAN_SORT_PRIOLIST_BYID(x, y) \
        if (   CAN_GET_ID_FOR_PRIOCHECK(CanActiveSendId[logTxObjHandle_PrioList[(x)]].id)     \
             < CAN_GET_ID_FOR_PRIOCHECK(CanActiveSendId[logTxObjHandle_PrioList[(y)]].id) ) { \
          tmp_logTxObjHandle = logTxObjHandle_PrioList[(x)];                                  \
          logTxObjHandle_PrioList[(x)] = logTxObjHandle_PrioList[(y)];                        \
          logTxObjHandle_PrioList[(y)] = tmp_logTxObjHandle;                                  \
        }

/* for LL compatibility */
#if defined(C_ENABLE_GEN_HW_START_STOP_IDX)
# define CAN_HL_HW_TX_NORMAL_INDEX(hwch)     (CAN_CONTROLLER_CONFIG(hwch).TxBasicHwStart)
# define CAN_HL_HW_TX_STARTINDEX(hwch)       ((CanObjectHandle/*need for COSMIC*/)CAN_HL_MIN(CAN_CONTROLLER_CONFIG(hwch).TxBasicHwStart, CAN_CONTROLLER_CONFIG(hwch).TxFullHwStart))
# define CAN_HL_HW_TX_FULL_STARTINDEX(hwch)  (CAN_CONTROLLER_CONFIG(hwch).TxFullHwStart)
# define CAN_HL_HW_UNUSED_STARTINDEX(hwch)   (CAN_CONTROLLER_CONFIG(hwch).UnusedHwStart)
# define CAN_HL_HW_RX_FULL_STARTINDEX(hwch)  (CAN_CONTROLLER_CONFIG(hwch).RxFullHwStart)
# define CAN_HL_HW_RX_BASIC_STARTINDEX(hwch) (CAN_CONTROLLER_CONFIG(hwch).RxBasicHwStart)
# define CAN_HL_HW_TX_STOPINDEX(hwch)        ((CanObjectHandle/*need for COSMIC*/)CAN_HL_MAX(CAN_CONTROLLER_CONFIG(hwch).TxBasicHwStop, CAN_CONTROLLER_CONFIG(hwch).TxFullHwStop))
# define CAN_HL_HW_TX_FULL_STOPINDEX(hwch)   (CAN_CONTROLLER_CONFIG(hwch).TxFullHwStop)
# define CAN_HL_HW_UNUSED_STOPINDEX(hwch)    (CAN_CONTROLLER_CONFIG(hwch).UnusedHwStop)
# define CAN_HL_HW_RX_FULL_STOPINDEX(hwch)   (CAN_CONTROLLER_CONFIG(hwch).RxFullHwStop)
# define CAN_HL_HW_RX_BASIC_STOPINDEX(hwch)  (CAN_CONTROLLER_CONFIG(hwch).RxBasicHwStop)
#else
# define CAN_ASR_HW_TX_NORMAL_INDEX(hwch)     (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).TxBasicHandleStart].HwHandle)
# if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST)
#  define CAN_ASR_HW_TX_STARTINDEX(hwch)      (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).TxBasicHandleStart].HwHandle)
# else
#  define CAN_ASR_HW_TX_STARTINDEX(hwch)      (CAN_ASR_HW_TX_FULL_STARTINDEX(hwch))
# endif
# define CAN_ASR_HW_TX_STOPINDEX(hwch)        (CAN_ASR_HW_TX_STARTINDEX(hwch) + (CAN_CONTROLLER_CONFIG(hwch).TxBasicHandleMax * CAN_MULTIPLEXED_TX_MAX) + CAN_CONTROLLER_CONFIG(hwch).TxFullHandleMax)

# if !defined(C_HL_TX_FULLCAN_HWHANDLE_REVERSE)
#  define CAN_ASR_HW_TX_FULL_STARTINDEX(hwch)  (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).TxFullHandleStart].HwHandle)
#  define CAN_ASR_HW_TX_FULL_STOPINDEX(hwch)   (CAN_ASR_HW_TX_FULL_STARTINDEX(hwch) + CAN_CONTROLLER_CONFIG(hwch).TxFullHandleMax)
# else
#  define CAN_ASR_HW_TX_FULL_STARTINDEX(hwch)  ((CAN_CONTROLLER_CONFIG(hwch).TxFullHandleStart != CAN_CONTROLLER_CONFIG(hwch).TxFullHandleStop) ? \
  (CAN_MAILBOX[(CAN_CONTROLLER_CONFIG(hwch).TxFullHandleStop-1)].HwHandle) : (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).TxFullHandleStart].HwHandle))
#  define CAN_ASR_HW_TX_FULL_STOPINDEX(hwch)   (CAN_ASR_HW_TX_FULL_STARTINDEX(hwch) + CAN_CONTROLLER_CONFIG(hwch).TxFullHandleMax)
# endif

# define CAN_ASR_HW_UNUSED_STARTINDEX(hwch)   (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).UnusedHandleStart].HwHandle)
# define CAN_ASR_HW_UNUSED_STOPINDEX(hwch)   ((CAN_CONTROLLER_CONFIG(hwch).UnusedHandleStart != CAN_CONTROLLER_CONFIG(hwch).UnusedHandleStop) ? \
  (CAN_MAILBOX[(CAN_CONTROLLER_CONFIG(hwch).UnusedHandleStop-1)].HwHandle + CAN_MAILBOX[(CAN_CONTROLLER_CONFIG(hwch).UnusedHandleStop-1)].DLC_FIFO) : (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).UnusedHandleStart].HwHandle))

# if !defined(C_HL_RX_FULLCAN_HWHANDLE_REVERSE)
#  define CAN_ASR_HW_RX_FULL_STARTINDEX(hwch)  (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStart].HwHandle)
#  define CAN_ASR_HW_RX_FULL_STOPINDEX(hwch)   ((CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStart != CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStop) ? \
  (CAN_MAILBOX[(CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStop-1)].HwHandle+1) : (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStart].HwHandle))
# else
#  define CAN_ASR_HW_RX_FULL_STARTINDEX(hwch)  ((CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStart != CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStop) ? \
  (CAN_MAILBOX[(CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStop-1)].HwHandle) : (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStart].HwHandle))
#  define CAN_ASR_HW_RX_FULL_STOPINDEX(hwch)   ((CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStart != CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStop) ? \
  (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStart].HwHandle+1) : (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).RxFullHandleStart].HwHandle))
# endif

# if !defined(C_HL_BASICCAN_HWHANDLE_REVERSE)
#  define CAN_ASR_HW_RX_BASIC_STARTINDEX(hwch) (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStart].HwHandle)
#  define CAN_ASR_HW_RX_BASIC_STOPINDEX(hwch)  ((CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStart != CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStop) ? \
  (CAN_MAILBOX[(CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStop-1)].HwHandle + CAN_MAILBOX[(CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStop-1)].DLC_FIFO) : \
  (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStart].HwHandle))
# else
#  define CAN_ASR_HW_RX_BASIC_STARTINDEX(hwch) ((CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStart != CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStop) ? \
  (CAN_MAILBOX[(CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStop-1)].HwHandle) : (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStart].HwHandle))
#  define CAN_ASR_HW_RX_BASIC_STOPINDEX(hwch)  ((CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStart != CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStop) ? \
  (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStart].HwHandle + CAN_MAILBOX[(CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStart)].DLC_FIFO) : \
  (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(hwch).RxBasicHandleStart].HwHandle))
# endif
# if !defined(CAN_HL_HW_TX_NORMAL_INDEX)
#  define CAN_HL_HW_TX_NORMAL_INDEX(hwch)     CAN_ASR_HW_TX_NORMAL_INDEX(hwch)
# endif
# if !defined(CAN_HL_HW_TX_FULL_STARTINDEX) && !defined(CAN_HL_HW_TX_FULL_STOPINDEX) && !defined(CAN_HL_HW_TX_STARTINDEX) && !defined(CAN_HL_HW_TX_STOPINDEX)
#  define CAN_HL_HW_TX_STARTINDEX(hwch)       CAN_ASR_HW_TX_STARTINDEX(hwch)
#  define CAN_HL_HW_TX_STOPINDEX(hwch)        CAN_ASR_HW_TX_STOPINDEX(hwch)
#  define CAN_HL_HW_TX_FULL_STARTINDEX(hwch)  CAN_ASR_HW_TX_FULL_STARTINDEX(hwch)
#  define CAN_HL_HW_TX_FULL_STOPINDEX(hwch)   CAN_ASR_HW_TX_FULL_STOPINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_UNUSED_STARTINDEX) && !defined(CAN_HL_HW_UNUSED_STOPINDEX)
#  define CAN_HL_HW_UNUSED_STARTINDEX(hwch)   CAN_ASR_HW_UNUSED_STARTINDEX(hwch)
#  define CAN_HL_HW_UNUSED_STOPINDEX(hwch)    CAN_ASR_HW_UNUSED_STOPINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_RX_FULL_STARTINDEX) && !defined(CAN_HL_HW_RX_FULL_STOPINDEX)
#  define CAN_HL_HW_RX_FULL_STARTINDEX(hwch)  CAN_ASR_HW_RX_FULL_STARTINDEX(hwch)
#  define CAN_HL_HW_RX_FULL_STOPINDEX(hwch)   CAN_ASR_HW_RX_FULL_STOPINDEX(hwch)
# endif
# if !defined(CAN_HL_HW_RX_BASIC_STARTINDEX) && !defined(CAN_HL_HW_RX_BASIC_STOPINDEX)
#  define CAN_HL_HW_RX_BASIC_STARTINDEX(hwch) CAN_ASR_HW_RX_BASIC_STARTINDEX(hwch)
#  define CAN_HL_HW_RX_BASIC_STOPINDEX(hwch)  CAN_ASR_HW_RX_BASIC_STOPINDEX(hwch)
# endif
#endif
#if !defined( CAN_ACTIVESEND_STATE )
/* may be overwritten within LL to handle Tx FIFO/Queue */
# define CAN_ACTIVESEND_STATE(obj) (CanActiveSendState[(obj)])
#endif
#if !defined( CAN_ACTIVESEND_PDUID )
/* may be overwritten within LL to handle Tx FIFO/Queue */
# define CAN_ACTIVESEND_PDUID(obj) (CanActiveSendPdu[(obj)])
#endif
/* may be used by LL to free tx object between CanLL_TxBegin and CanLL_TxEnd */
#define CAN_FREE_TX_OBJECT(obj) CAN_ACTIVESEND_STATE(obj) = CANFREEOBJ

#if defined( C_ENABLE_INDIVIDUAL_POLLING )
/* define first index to array CanHwObjIndivPolling[][] */
#  define CAN_HWOBJINDIVPOLLING_INDEX0                     (canHwChannel)
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK )
# if !defined( CAN_RAM_CHECK_MAILBOX_RESULT ) /* May be defined by test suite to stimulate RAM_CHECK failure (return kCanFalse) */
#  if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON )
#   define CAN_RAM_CHECK_MAILBOX_RESULT(ch, hwObjHandle) CanLL_IsMailboxCorrupt((hwObjHandle))
#  else
#   define CAN_RAM_CHECK_MAILBOX_RESULT(ch, hwObjHandle) CanLL_IsMailboxCorrupt((ch), (hwObjHandle))
#  endif
# endif
# if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX ) /* with Mailbox Notification */
#  define DO_CAN_RAM_CHECK(hwObjHandle) \
  if( ((canStatus[channel] & CAN_STATUS_INIT) != CAN_STATUS_INIT ) ||  /* PowerOn */ \
      ((canStatus[channel] & CAN_STATUS_SLEEP) == CAN_STATUS_SLEEP )   /* Wakeup */  ) \
  { \
    if( kCanTrue == CAN_RAM_CHECK_MAILBOX_RESULT(channel, (hwObjHandle)) ) \
    { \
      Appl_CanCorruptMailbox((uint8)channel, (hwObjHandle)); \
      canRamCheckStatus = kCanRamCheckFailed; \
    } \
  }
# else                                          /* no Mailbox Notification */
#  define DO_CAN_RAM_CHECK(hwObjHandle) \
  if( ((canStatus[channel] & CAN_STATUS_INIT) != CAN_STATUS_INIT ) ||  /* PowerOn */ \
      ((canStatus[channel] & CAN_STATUS_SLEEP) == CAN_STATUS_SLEEP )   /* Wakeup */  ) \
  { \
    if( kCanTrue == CAN_RAM_CHECK_MAILBOX_RESULT(channel, (hwObjHandle)) ) \
    { \
      canRamCheckStatus = kCanRamCheckFailed; \
    } \
  }
# endif
#else
# define DO_CAN_RAM_CHECK(hwObjHandle)
#endif

#define CanHL_IsSleep(ch) ((canStatus[ch] & CAN_STATUS_SLEEP) == CAN_STATUS_SLEEP)
#define CanHL_IsStop(ch) ((canStatus[ch] & CAN_STATUS_STOP) == CAN_STATUS_STOP)
#define CanHL_IsBusOff(ch) ((canStatus[ch] & CAN_STATUS_BUSOFF) == CAN_STATUS_BUSOFF)

/* Multiple Identity */
#define cantVIdentityMsk uint16
#define CanSetActiveIdentity(identityLog) \
{ \
  canActiveIdentityLog = (identityLog); \
  canActiveIdentityMsk = (cantVIdentityMsk) (((cantVIdentityMsk) 1) << (identityLog)); \
}
#if defined V_ACTIVE_IDENTITY_MSK
# undef V_ACTIVE_IDENTITY_MSK  /* this define from v_cfg.h is replaced and no more used (but header may included by other module) */ /* PRQA S 0841 */ /* MD_Can_0841 */
#endif
#define V_ACTIVE_IDENTITY_MSK                canActiveIdentityMsk
#if defined V_ACTIVE_IDENTITY_LOG
# undef V_ACTIVE_IDENTITY_LOG  /* this define from v_cfg.h is replaced and no more used (but header may included by other module) */ /* PRQA S 0841 */ /* MD_Can_0841 */
#endif
#define V_ACTIVE_IDENTITY_LOG                canActiveIdentityLog

#if (CAN_GENERIC_PRETRANSMIT == STD_ON)
# define PDUINFO_PTR PduInfoPtr_var
#else
# define PDUINFO_PTR PduInfo
#endif

#if !defined (CAN_APPLICATION_DEM_REPORTERROR)
# define CAN_APPLICATION_DEM_REPORTERROR STD_OFF
#endif
#if (CAN_APPLICATION_DEM_REPORTERROR == STD_OFF)
# define Can_Dem_ReportError(EventId) ( (void) Dem_ReportErrorStatus((EventId), DEM_EVENT_STATUS_FAILED) )
#endif

#if (CAN_FD_SUPPORT == CAN_FULL)
# define CAN_DECODE_DLI(dlc) (Can_DliToBytesMap[(dlc)&0xFu])
#  define CAN_MAX_RX_BUFFER_DLC CAN_GLOBAL_CONFIG(CanMaxRxBufferDlc)
#  define CAN_MAX_TX_BUFFER_DLC CAN_GLOBAL_CONFIG(CanMaxTxBufferDlc)
#else
# define CAN_DECODE_DLI(dlc) (dlc)
# define CAN_MAX_RX_BUFFER_DLC 8u
# define CAN_MAX_TX_BUFFER_DLC 8u
#endif



# define CAN_BASIS_ADR(channel)                    (CAN_CellAddrMapPtr) CanBasisAdr[channel]
# define CAN_NUMBER_OF_MSG(channel)                CanNumberOfMsgObj[channel]
# define CAN_LL_STATUS(channel)                    canllStatus[channel]
# define STATUS_STOP_MODE(channel)                 status_stop[channel]
# define STATUS_BUS_OFF(channel)                   status_busoff[channel]
# define STATUS_SLEEP(channel)                     status_sleep[channel]
# define NORMAL_MODE(channel)                      normal_mode[channel]
# define TX_SEND_FLAG(channel,k)                   txsendflag[channel][k]
# define RX_MSGOBJ(channel)                        rxMsgObj[channel]
# define RX_MSGOBJ_ID_LOW(channel)                 rxMsgObj[channel].Id[0]
# define RX_MSGOBJ_ID_HIGH(channel)                rxMsgObj[channel].Id[1]
# define RX_MSGOBJ_DLC(channel)                    rxMsgObj[channel].Dlc
# define RX_MSGOBJ_DATA(channel)                   rxMsgObj[channel].Data.ucData[0]
# define RX_MSGOBJ_MSGCNTRL(channel)               rxMsgObj[channel].MessageCntrl
# define LAST_RXOBJECT(channel)                    CanNumberOfMsgObj[channel]

# if defined (C_COMP_TI_TMS470_DCAN)    
#  define VIM_MASK(channel)                        (V_DEF_P2VAR(V_NONE ,vuint32, VAR_NOINIT, INT_CTRL)) vimSetReg[channel]
#  define VIM_CLRMASK(channel)                     (V_DEF_P2VAR(V_NONE ,vuint32, VAR_NOINIT, INT_CTRL)) vimClrReg[channel]
#  define VIM_SETMASK(channel)                     (V_DEF_P2VAR(V_NONE ,vuint32, VAR_NOINIT, INT_CTRL)) vimSetReg[channel]
#  define INTERRUPT_SRC(channel)                   interruptSrc[channel]
# endif



#define TX_MSGOBJ_ID_LOW(txlogobj)                 txMsgObj[txlogobj].Id[0]
#define TX_MSGOBJ_ID_HIGH(txlogobj)                txMsgObj[txlogobj].Id[1]
#define TX_MSGOBJ_DLC(txlogobj)                    txMsgObj[txlogobj].Dlc
#define TX_MSGOBJ_UCDATA(txlogobj)                 txMsgObj[txlogobj].Data.ucData



#if defined(C_ENABLE_HW_LOOP_TIMER)
#  if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON )
#   define CanDeclareTimerResult      vuint8 canTimerResult
#   define APPLCANTIMERSTART(x)       ApplCanTimerStart(x)
#   define CANTIMERRESULT_UPDATE(x)   canTimerResult = ApplCanTimerLoop(x)
#   define WHILE_CONDITON(x)          while((x) && (canTimerResult != 0))
#   define APPLCANTIMEREND(x)         ApplCanTimerEnd(x)
#  else
#   define CanDeclareTimerResult      vuint8 canTimerResult
#   define APPLCANTIMERSTART(x)       ApplCanTimerStart(channel, (x))
#   define CANTIMERRESULT_UPDATE(x)   canTimerResult = ApplCanTimerLoop(channel, (x))
#   define WHILE_CONDITON(x)          while((x) && (canTimerResult != 0))
#   define APPLCANTIMEREND(x)         ApplCanTimerEnd(channel, (x))
#  endif
#else
# define CanDeclareTimerResult
# define APPLCANTIMERSTART(x)
# define CANTIMERRESULT_UPDATE(x)   
# define WHILE_CONDITON(x)            while(x)
# define APPLCANTIMEREND(x)
#endif

#if !defined (C_DISABLE_DCAN_ISSUE22_WORKAROUND) && !defined (C_ENABLE_DCAN_ISSUE22_WORKAROUND)
# define C_ENABLE_DCAN_ISSUE22_WORKAROUND
#endif

#if defined (C_COMP_TI_TMS470_DCAN) 
# define CanLL_CanInterruptDisable(canHwChannel, localInterruptOldFlagPtr)                 \
{                                                                                          \
  *(localInterruptOldFlagPtr) = *VIM_MASK(canHwChannel) & INTERRUPT_SRC(canHwChannel); /* SBSW_CAN_LL017 */ \
  *VIM_CLRMASK(canHwChannel) = INTERRUPT_SRC(canHwChannel); /* SBSW_CAN_LL013 */           \
}
#endif


#if defined (C_COMP_TI_TMS470_DCAN) 
# define CanLL_CanInterruptRestore(canHwChannel, localInterruptOldFlag)                    \
{                                                                                          \
  if (((localInterruptOldFlag) & INTERRUPT_SRC(canHwChannel)) != 0 )                       \
  {                                                                                        \
    *VIM_SETMASK(canHwChannel) = INTERRUPT_SRC(canHwChannel); /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */  /* PRQA S 0306 */ /* MD_Can_0306_HWaccess */ /* SBSW_CAN_LL013 */ \
  }                                                                                        \
}
#endif



/* CanLL_TxIsHWObjFree() is implemented as function below in the section reserved for functions */

#if defined( C_ENABLE_SLEEP_WAKEUP )
# define CanLL_HwIsSleep( CAN_HW_CHANNEL_CANPARA_ONLY)  (STATUS_SLEEP(channel) == kCanTrue)
#else
# define CanLL_HwIsSleep( CAN_HW_CHANNEL_CANPARA_ONLY)  (kCanFalse != kCanFalse)  /* avoid misra warning */
#endif


#define CanLL_HwIsStop( CAN_HW_CHANNEL_CANPARA_ONLY ) (STATUS_STOP_MODE(channel)) /* PRQA S 3344 */ /* MD_Can_3344_LL */ 

#define CanLL_HwIsBusOff( CAN_HW_CHANNEL_CANPARA_ONLY ) (CAN_LL_STATUS(channel) & kErrBusOff)

#if defined( C_ENABLE_EXTENDED_STATUS )
# define CanLL_HwIsPassive( CAN_HW_CHANNEL_CANPARA_ONLY )              \
    ( ((CanRxActualErrorCounter(CAN_HW_CHANNEL_CANPARA_ONLY) > 127) || \
       (CanTxActualErrorCounter(CAN_HW_CHANNEL_CANPARA_ONLY) > 127)) )

# define CanLL_HwIsWarning( CAN_HW_CHANNEL_CANPARA_ONLY )             \
    ( ((CanRxActualErrorCounter(CAN_HW_CHANNEL_CANPARA_ONLY) > 95) || \
       (CanTxActualErrorCounter(CAN_HW_CHANNEL_CANPARA_ONLY) > 95)))
#endif /* C_ENABLE_EXTENDED_STATUS */
#if defined(C_MULTIPLE_RECEIVE_CHANNEL)
# define CanLL_ApplCanTimerStart(loop)  ApplCanTimerStart(channel, loop)
# define CanLL_ApplCanTimerEnd(loop)    ApplCanTimerEnd(channel, loop)
# define CanLL_ApplCanTimerLoop(loop)   ApplCanTimerLoop(channel, loop)
#else
# define CanLL_ApplCanTimerStart(loop)  ApplCanTimerStart(loop)
# define CanLL_ApplCanTimerEnd(loop)    ApplCanTimerEnd(loop)
# define CanLL_ApplCanTimerLoop(loop)   ApplCanTimerLoop(loop)
#endif


/***************************************************************************/
/* Defines / data types / structs / unions                                 */
/***************************************************************************/
/* Define CAN Chip hardware; segment must be located in locator file    */
/* register layout of the can chip                                      */
/* Structure describing CAN receive buffer. */

#if defined(C_CPUTYPE_BIGENDIAN)
typedef volatile struct
{
  vuint16      ComMask;              /* Command Mask register      */
  vuint16      ComRequest;           /* Command Request register   */
  vuint16      Mask2;                /* Mask register 2            */
  vuint16      Mask1;                /* Mask register 1            */
  vuint16      ArbitrFld2;           /* Arbitration 2              */
  vuint16      ArbitrFld1;           /* Arbitration 1              */
  vuint16      notused10;            /* not used                   */   
  vuint16      MessageCntrl;         /* Message Control Register   */
  can_data     Data;                 /* CAN Data Register          */
  vuint16      notused11[4];         /* not used                   */   
   
} CanMsgObj;


typedef volatile struct
{
  vuint32      CntrlReg;             /* CAN Control Register            Baseaddress + 0x00  */

  vuint16      notused1;
  vuint16      StatReg;              /* CAN Status Register             Baseaddress + 0x04  */

  vuint16      notused2;         
  vuint16      ErrorCount;           /* CAN Errorcounter Register       Baseaddress + 0x08  */

  vuint16      BRP_Reg;              /* Baud Rate Prescaler Register    Baseaddress + 0x0E  */
  vuint16      BitTiming;            /* CAN Bittiming Register          Baseaddress + 0x0C  */

  vuint16      InterruptReg1;        /* CAN Interrupt Register          Baseaddress + 0x12  */
  vuint16      InterruptReg;         /* CAN Interrupt Register1         Baseaddress + 0x10  */

  vuint16      notused3;
  vuint16      TestReg;              /* Test Register                   Baseaddress + 0x14  */

  vuint16      notused4[3];         
  vuint16      ParityErrorCode;      /* ParityErrorCode                 Baseaddress + 0x1C  */

  vuint16      notused5[48];

  vuint16      AutoBusOnTime2;       /* BusOnTime Regsiter2             Baseaddress + 0x82  */
  vuint16      AutoBusOnTime1;       /* BusOnTime Regsiter1             Baseaddress + 0x80  */

  vuint16      notused6;         
  vuint16      TransRequestX;        /* Transmission request Register   Baseaddress + 0x84  */

  vuint32      TransRequest[4];      /* Transmission request Register   Baseaddress + 0x88  */

  vuint16      notused7;         
  vuint16      NewDataX;             /* New Data Register               Baseaddress + 0x98  */

  vuint32      NewData[4];           /* New Data Register               Baseaddress + 0x9C  */

  vuint16      notused8;         
  vuint16      InterrPendingX;       /* InterrPending Register          Baseaddress + 0xAC  */

  vuint32      InterrPending[4];     /* InterrPending Register          Baseaddress + 0xB0  */

  vuint16      notused9;         
  vuint16      MessageValidX;        /* MessageValid Register           Baseaddress + 0xC0  */

  vuint32      MessageValid[4];      /* MessageValid Register           Baseaddress + 0xC4  */

  vuint32      notused10;

  vuint16      IntPndMux[8];         /* NIntPndMux Register             Baseaddress + 0xD8  */
  vuint16      notused11[12];           
 
  CanMsgObj    sMsgObj[3];           /* Message Interface Register      Baseaddress + 0x100 */
  vuint16      notused12[50];           

  vuint32      can_IO_ctrlTx;        /*  can_IO_ctrlTx Register         Baseaddress + 0x1E0 */
  vuint32      can_IO_ctrlRx;        /*  can_IO_ctrlRx Register         Baseaddress + 0x1E0 */
    
} CAN_CellAddrMap;
V_DEF_P2SFR_CAN_TYPE(V_NONE, CAN_CellAddrMap) CAN_CellAddrMapPtr;
#endif



/***************************************************************************/
/* Constants                                                               */
/***************************************************************************/
#define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* BR:012 */
V_DEF_CONST(V_NONE, uint8, CONST) Can_MainVersion         = CAN_SW_MAJOR_VERSION; /* PRQA S 3408 */ /* MD_Can_3408_Asr_libCheck */
V_DEF_CONST(V_NONE, uint8, CONST) Can_SubVersion          = CAN_SW_MINOR_VERSION; /* PRQA S 3408 */ /* MD_Can_3408_Asr_libCheck */
V_DEF_CONST(V_NONE, uint8, CONST) Can_ReleaseVersion      = CAN_SW_PATCH_VERSION; /* PRQA S 3408 */ /* MD_Can_3408_Asr_libCheck */


#if (CAN_FD_SUPPORT == CAN_FULL)
V_DEF_CONST(CAN_STATIC, uint8, CAN_CONST) Can_DliToBytesMap[16] =
{
 0,  1,  2,  3,
 4,  5,  6,  7,
 8, 12, 16, 20,
24, 32, 48, 64
};
#endif

/* Global constants with CAN driver main and subversion */


#define CAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***************************************************************************/
/* CAN-Hardware Data Definitions                                           */
/***************************************************************************/

/***************************************************************************/
/* global data definitions                                                 */
/***************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined(C_ENABLE_MULTI_ECU_CONFIG)
V_DEF_VAR(V_NONE, uint16, VAR_NOINIT) canActiveIdentityMsk; /* PRQA S 3408 */ /* MD_Can_Asr_3408 */
V_DEF_VAR(V_NONE, uint8, VAR_NOINIT)  canActiveIdentityLog; /* PRQA S 3408 */ /* MD_Can_Asr_3408 */
#endif



/***************************************************************************/
/* local data definitions                                                  */
/***************************************************************************/
/* CAN418 */
#if defined(C_ENABLE_RX_POLLING)
V_DEF_VAR(CAN_STATIC, Can_ReturnType, VAR_NOINIT) canRxTaskActive;  /* suppress reentrance */
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API != STD_ON) && (CAN_DEV_TIMEOUT_DETECT == STD_ON) && (CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_MICROSAR_VERSION == CAN_MSR30)
V_DEF_VAR(CAN_STATIC, uint8, VAR_NOINIT) canApiContext;   /* Context of current used API (Init,InitController,SetControllerMode,disable/enableControlerInterrupts) */
#endif
#if (CAN_DEV_ERROR_DETECT == STD_ON) && defined(CAN_ENABLE_CORE_GEN_CHECK)
V_DEF_VAR(CAN_STATIC, Can_HwHandleType, VAR_NOINIT) canMailboxIndex;   /* Used for Can_CheckGenDataController() */
#endif

/* RAM CATEGORY 1 START*/
/* RAM CATEGORY 1 END*/

#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
V_DEF_VAR (CAN_STATIC, uint8, VAR_INIT) canConfigInitFlag = CAN_STATUS_UNINIT; /* used to check double initialization */
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#if defined(CAN_ENABLE_SELECTABLE_PB) || defined(C_ENABLE_MULTI_ECU_CONFIG)
# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
V_DEF_P2CONST (CAN_STATIC, Can_ConfigType, VAR_INIT, CONST_PBCFG) canConfigPtr = NULL_PTR; /* UREQ00035484 */
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#else
# define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# if (CAN_MICROSAR_VERSION == CAN_MSR403)
V_DEF_CONSTP2CONST(CAN_STATIC, Can_ConfigType, CONST, CONST_PBCFG) canConfigPtr = &Can_GlobalConfig; /* PRQA S 3218 */ /* MD_Can_3218 */
# else
V_DEF_CONSTP2CONST(CAN_STATIC, Can_ConfigType, CONST, CONST_PBCFG) canConfigPtr = &CanConfig; /* PRQA S 3218 */ /* MD_Can_3218 */
# endif
# define CAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/***************************************************************************/
/*  local prototypes                                                       */
/***************************************************************************/
#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined( C_ENABLE_SLEEP_WAKEUP )
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_WakeUpHandling(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK )
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle);
/* CODE CATEGORY 4 END */
#endif

#if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
     (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
      !defined( C_ENABLE_TX_POLLING )        || \
      !defined( C_ENABLE_ERROR_POLLING )     ||\
       defined( C_ENABLE_INDIVIDUAL_POLLING ) || \
      !defined( C_ENABLE_WAKEUP_POLLING ))        /* ISR necessary; no pure polling configuration*/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_HandleIllIrptNumber(CAN_CHANNEL_CANTYPE_FIRST vuint16 intnumber);
#endif





#define CAN_STOP_SEC_STATIC_CODE  /*---------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***************************************************************************/
/*  Error Check                                                            */
/***************************************************************************/
#if !defined(C_ENABLE_SLEEP_WAKEUP)
# if (CAN_SLEEP_SUPPORT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON)
#  error "C_ENABLE_SLEEP_WAKEUP organified but generated like supported"
# endif
#endif
#if (CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_SLEEP_SUPPORT == STD_OFF)
# error "activated CAN_WAKEUP_SUPPORT need activated CAN_SLEEP_SUPPORT"
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
# if (CAN_LOOP_MAX == 0)
#  error "CAN_LOOP_MAX should not be generated as 0"
# endif
#else
# if (CAN_HARDWARE_CANCELLATION == STD_ON)
#  error "C_ENABLE_HW_LOOP_TIMER organified but generated like supported"
# endif
#endif
#if defined(C_ENABLE_MULTI_ECU_CONFIG)
#else
# if (CAN_MULTI_ECU_CONFIG == STD_ON)
#  error "C_ENABLE_MULTI_ECU_CONFIG organified but generated like supported"
# endif
#endif
# if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
#  error "C_ENABLE_CANCEL_IN_HW organified but generated like supported"
# endif
#if (CAN_DEV_TIMEOUT_DETECT == STD_ON)
# if (CAN_DEV_ERROR_DETECT == STD_OFF)
#  error "CAN_DEV_TIMEOUT_DETECT is switched on but CAN_DEV_ERROR_DETECT is not"
# endif
#endif
#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
# if defined( C_ENABLE_PARTIAL_NETWORK )
#  error "No need to switch on partial Network for MicroSar in version 4.0"
# endif
# if ( CAN_BUSOFF_SUPPORT_API == STD_ON )
#  error "BUSOFF_SUPPORT_API not supported for MicroSar in version 4.0"
# endif
# if ( CAN_EXTENDED_STATE_MACHINE == STD_ON )
#  error "CAN_EXTENDED_STATE_MACHINE not supported for MicroSar in version 4.0"
# endif
# if ( CAN_DEV_TIMEOUT_DETECT == STD_ON )
#  error "CAN_DEV_TIMEOUT_DETECT not supported for MicroSar in version 4.0"
# endif
#endif
# if !defined(C_ENABLE_HW_LOOP_TIMER) && defined(C_ENABLE_PARTIAL_NETWORK)
#  error "Feature 'partial network' (CanPnEnable) need 'Hardware Loop Check'"
# endif
#if (CAN_MIRROR_MODE == STD_ON) && (CAN_GENERIC_CONFIRMATION != CAN_API2) && (CAN_GENERIC_PRECOPY != STD_ON)
# error "CAN_MIRROR_MODE need CAN_GENERIC_CONFIRMATION with CAN_API2 and CAN_GENERIC_PRECOPY as STD_ON"
#endif

/***************************************************************************/
/*  Functions                                                              */
/***************************************************************************/
#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined(C_ENABLE_HW_LOOP_TIMER) || (((CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)) ) /* always used for sync mode */
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON )
#  define CanHL_ApplCanTimerStart( timerIdx )  ApplCanTimerStart( timerIdx );
#  define CanHL_ApplCanTimerEnd( timerIdx )    ApplCanTimerEnd( timerIdx );
# else
#  define CanHL_ApplCanTimerStart( timerIdx )  ApplCanTimerStart( Controller, (timerIdx) );
#  define CanHL_ApplCanTimerEnd( timerIdx )    ApplCanTimerEnd( Controller, (timerIdx) );
# endif
# define CanHL_ApplCanTimerLoop( timerIdx )   if (ApplCanTimerLoop( CAN_CHANNEL_CANPARA_FIRST (timerIdx) ) != CAN_OK) \
                                              { \
                                                break; \
                                              }
#else
# define CanHL_ApplCanTimerStart( timerIdx )
# define CanHL_ApplCanTimerLoop( timerIdx )
# define CanHL_ApplCanTimerEnd( timerIdx )
#endif

#if defined(C_ENABLE_HW_LOOP_TIMER) || (((CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)) ) /* always used for sync mode */
# if (CAN_HW_LOOP_SUPPORT_API != STD_ON)
/* CAN280, CAN281 */
/****************************************************************************
| NAME:             ApplCanTimerStart
| CALLED BY:        CAN driver
| PRECONDITIONS:    Preprocessed
| INPUT PARAMETERS: Controller, source
| RETURN VALUES:    None
| DESCRIPTION:      start loop count
****************************************************************************/
/* Used as macro to save runtime and code */
#  if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON )
#   if ((CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403))
/* CAN398 */
#    define ApplCanTimerStart(source)     ((void)GetCounterValue( CAN_OS_COUNTER_ID, &canLoopTimeout[0][(source)]))
#   else
#    define ApplCanTimerStart(source)     (canLoopTimeout[0][(source)] = 0)
#   endif
#  else
#   if ((CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403))
#    define ApplCanTimerStart(ch, source) ((void)GetCounterValue( CAN_OS_COUNTER_ID, &canLoopTimeout[(ch)][(source)]))
#   else
#    define ApplCanTimerStart(ch, source) (canLoopTimeout[(ch)][(source)] = 0)
#   endif
#  endif
/****************************************************************************
| NAME:             ApplCanTimerLoop
| CALLED BY:        CAN driver
| PRECONDITIONS:    Preprocessed
| INPUT PARAMETERS: Controller, source
| RETURN VALUES:    Can_ReturnType: CAN_NOT_OK (break) or CAN_OK (continue)
| DESCRIPTION:      decide whether a hardware loop continue or not by check 
|                   generated max loop value
****************************************************************************/
/* CAN295, CAN296 */
V_DEF_FUNC(CAN_STATIC, Can_ReturnType, STATIC_CODE) ApplCanTimerLoop (CAN_CHANNEL_CANTYPE_FIRST uint8 source)
{
  Can_ReturnType retval;
#  if ((CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403))
  TickType elapsedTime;
  TickType startTime;
  retval = CAN_OK;
  startTime =canLoopTimeout[channel][source]; /* temporary variable because GetElapsedValue modify original data */
  Can_CheckDetErrorReturnValue((source <= CAN_LOOP_MAX), CAN_HW_ACCESS_ID, CAN_E_PARAM_HANDLE, CAN_NOT_OK); /* SBSW_CAN_HL06 */
#   if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnValue((channel < kCanNumberOfChannels), CAN_HW_ACCESS_ID, CAN_E_PARAM_CONTROLLER, CAN_NOT_OK); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL41 */
#   endif
  if ( GetElapsedValue( CAN_OS_COUNTER_ID, &startTime, &elapsedTime ) != E_OK )
  {
    Can_CallDetReportError(CAN_HW_ACCESS_ID, CAN_E_PARAM_HANDLE); /* SBSW_CAN_HL06 */
    retval = CAN_NOT_OK;
  }
  else
  {
    if ( CAN_OS_TICK2MS( elapsedTime ) >= CAN_TIMEOUT_DURATION )
    {
      retval = CAN_NOT_OK; /* Mode Change syncron  &  hw loop check*/
#   if defined(C_ENABLE_HW_LOOP_TIMER)
      if (source < CAN_LOOP_MAX)
      { /* hardware loop check (no mode-changes) */
        Can_CallDetReportError(CAN_HW_ACCESS_ID, CAN_E_TIMEOUT_DET); /* SBSW_CAN_HL06 */
        canIsHardwareCanceled[channel] = TRUE; /* SBSW_CAN_HL32 */
      }
#   endif
    }
  }
#   if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  startTime = startTime;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
#   endif
#  else /* CAN_MSR3 */
  retval = CAN_OK;
  Can_SilentBswCheckErrorReturnValue((source < CAN_LOOP_MAX), CAN_HW_ACCESS_ID, CAN_E_PARAM_HANDLE, CAN_NOT_OK); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL42 */
#   if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnValue((channel < kCanNumberOfChannels), CAN_HW_ACCESS_ID, CAN_E_PARAM_CONTROLLER, CAN_NOT_OK); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL59 */
#   endif
  {
    canLoopTimeout[channel][source]++; /* SBSW_CAN_HL33 */
    if ( canLoopTimeout[channel][source] >= CAN_TIMEOUT_DURATION )
    {
      retval = CAN_NOT_OK;
#   if defined( C_ENABLE_PARTIAL_NETWORK )
      if ( canTimeoutCall[channel] == TRUE )
#   endif
      {
        /* CAN297 */
#   if (CAN_DEV_TIMEOUT_DETECT == STD_ON)
        Can_CallDetReportError(canApiContext, CAN_E_TIMEOUT_DET); /* SBSW_CAN_HL06 */
#   else
#    if (CAN_PROD_ERROR_DETECT == STD_ON) /* CAN084 is explicitely ignored due to vector general requirementes */
        /* CAN234, CAN235 */
        Can_Dem_ReportError(canDemErrorTimeout); /* CAN029, CAN081 */ /* SBSW_CAN_HL52 */
#    endif
#   endif
        canIsHardwareCanceled[channel] = TRUE; /* SBSW_CAN_HL32 */
      }
    }
  }
#  endif /* CAN_MSR3/4 */
  return retval;
}
/****************************************************************************
| NAME:             ApplCanTimerEnd
| CALLED BY:        CAN driver
| PRECONDITIONS:    Preprocessed
| INPUT PARAMETERS: Controller, source
| RETURN VALUES:    None
| DESCRIPTION:      do nothing (stop loop count)
****************************************************************************/
/* Used as macro to save runtime and code */
/* because of possible nested timers .. timer has to be reset */
#  define ApplCanTimerEnd ApplCanTimerStart

# endif /* (CAN_HW_LOOP_SUPPORT_API != STD_ON) */
#endif /* C_ENABLE_HW_LOOP_TIMER */

/****************************************************************************
| NAME:             CanInit
| CALLED BY:        Application
| PRECONDITIONS:    Preprocessed
| INPUT PARAMETERS: Controller, init object
| RETURN VALUES:    none
| DESCRIPTION:      used for BusOff handling to reinitialized (here mapped to std AutoSar API)
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInit(CAN_CHANNEL_CANTYPE_FIRST uint8 initObject)
{
  Can_CheckDetErrorReturnVoid((initObject >= CAN_INIT_OBJ_START_IDX[channel]), CAN_INIT_ID, CAN_E_PARAM_POINTER); /* SBSW_CAN_HL06 */
#if (CAN_MICROSAR_VERSION == CAN_MSR40)
  Can_InitController((uint8)channel, &Can_ControllerBaudrateConfig[((uint8)(initObject - (uint8)(CAN_INIT_OBJ_START_IDX[channel])) & 0x03u)]); /* SBSW_CAN_HL07 */
#else
  Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL07 */
#endif
#if ( CAN_BUSOFF_SUPPORT_API == STD_ON )
  { /* CanResetBusOffStart/Stop (and CanResetBusSleep) use this call. When application do this call the state has to be set to START here because it will not be done in SetControllerMode() */
    (void)Can_SetControllerMode((uint8)channel, CAN_T_START); /* SBSW_CAN_HL08 */
  }
#endif
#if defined( V_ENABLE_USE_DUMMY_STATEMENT ) && (CAN_DEV_ERROR_DETECT == STD_OFF) && (CAN_MICROSAR_VERSION != CAN_MSR40)
  initObject = initObject;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
#endif
}


/* CAN016 */
/****************************************************************************
| NAME:             CanHL_TxConfirmation
| CALLED BY:        Tx-Interrupt and Polling Task
| PRECONDITIONS:
| INPUT PARAMETERS: Controller, txhwhandle
| RETURN VALUES:    none
| DESCRIPTION:      Transmit Confirmation handling
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_TxConfirmation(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle)
{
  CanHookBegin_CanHL_TxConfirmation();
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnVoid((channel < kCanNumberOfChannels), CAN_TXCNF_ID, CAN_E_PARAM_CONTROLLER); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL14 */
# endif
  Can_SilentBswCheckErrorReturnVoid(((txObjHandle >=  CAN_HL_HW_TX_STARTINDEX(canHwChannel)) && (txObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel))),
                                    CAN_TXCNF_ID, CAN_E_PARAM_HANDLE); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL57 */
  {
    CanObjectHandle logTxObjHandle;
    PduIdType tmp_pdu;
#if ( CAN_CANCEL_SUPPORT_API == STD_ON )
    uint8_least tmp_state;
#endif
#if (CAN_GENERIC_CONFIRMATION == CAN_API2)
    Can_ReturnType generic_retval;
#endif
    CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
    CanSetPointerToCanHardware;
#if defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON)
    /* Global interrupt disabling needed to avoid another can_write while interface send out of queue (first send out of queue avoid inversion) */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_3); /* SBSW_CAN_HL11 */
#else
# if defined( C_ENABLE_INDIVIDUAL_POLLING ) /* no nesting for same interrupt possible */
    Can_DisableControllerInterrupts((uint8)channel); /* avoid nested call of confirmation due to new transmit meanwhile (tx interrupt while tx task) */ /* SBSW_CAN_HL13 */
# endif
#endif
    logTxObjHandle = (CanObjectHandle)(txObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(channel));
    {
    # if !(defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON))
      Can_EnterCritical(CAN_EXCLUSIVE_AREA_0); /* SBSW_CAN_LL002 */
    # endif
    
      IF_TRANSMIT.ComMask       =  kSetWrRd  |  kSetControl | kSetClrIntPnd; /* SBSW_CAN_LL004 */
    
      if(CAN_INDIV_POLLING(channel,txObjHandle) != 0) /* PRQA S 3325 */ /* MD_Can_3325_LL */
      {                                               /* PRQA S 3201 */ /* MD_Can_3201_LL */
        IF_TRANSMIT.MessageCntrl   = kSetEoB; /* SBSW_CAN_LL004 */
      }
      else
      {
        IF_TRANSMIT.MessageCntrl   = kSetEoB |  kSetEnableTxCanInt; /* SBSW_CAN_LL004 */
      }
    
      IF_TRANSMIT.ComRequest    =  txObjHandle + 1; /* SBSW_CAN_LL004 */
    # if !(defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON))    
      Can_LeaveCritical(CAN_EXCLUSIVE_AREA_0); /* SBSW_CAN_LL002 */
    # endif
    }
    tmp_pdu   = CAN_ACTIVESEND_PDUID(logTxObjHandle);    /* pdu for confirmation parameter */
#if ( CAN_CANCEL_SUPPORT_API == STD_ON )
    tmp_state = (uint8_least)CAN_ACTIVESEND_STATE(logTxObjHandle);
#endif
    
    { /* mailbox is send out successful (without cancelation) */
      CAN_ACTIVESEND_STATE(logTxObjHandle) = CANFREEOBJ; /* free active pdu to allow next tx out of confirmation or direct (reload queue) */ /* SBSW_CAN_HL09 */
      
#if (CAN_GENERIC_CONFIRMATION == STD_ON)
      if (Appl_GenericConfirmation( tmp_pdu ) == CAN_OK) /* SBSW_CAN_HL12 */
#endif
#if (CAN_GENERIC_CONFIRMATION == CAN_API2)
      {
        Can_PduType canPdu;
        tCanTxInfoStruct canTxInfoStruct;

        #error "MirrorMode not supported"
        
        canPdu.sdu = (Can_SduPtrType)canTxInfoStruct.pChipData;
        canPdu.length = CanTxActualDLC((&canTxInfoStruct));
# if ( CAN_EXTENDED_ID == STD_ON )
#  if ( CAN_MIXED_ID == STD_ON )
        if ( CanTxActualIdType((&canTxInfoStruct)) == kCanIdTypeStd)
        {
          canPdu.id = (Can_IdType)CanTxActualStdId((&canTxInfoStruct));
        }
        else
#  else /* pure Extended ID */
#  endif
        { /* Extended ID */
          canPdu.id = (Can_IdType)(CanTxActualExtId((&canTxInfoStruct)) | CAN_EXTENDED_ID_MASK);
        }
# else /* Standard ID */
        canPdu.id = CanTxActualStdId((&canTxInfoStruct));
# endif
        canPdu.swPduHandle = tmp_pdu;
        generic_retval = Appl_GenericConfirmation( (uint8)channel, &canPdu ); /* PRQA S 0312 */ /* MD_Can_0312 */
      }
      if (generic_retval == CAN_OK)
#endif
      {
#if ( CAN_CANCEL_SUPPORT_API == STD_ON )
        if (tmp_state == CANCANCELOBJSW)
        { /* SW cancelation - just notifiy IF */
          CanIf_CancelTxNotification( tmp_pdu, FALSE ); /* SBSW_CAN_HL12 */
        }
        else
#endif
        {
          /* CAN234 */
          CanIf_TxConfirmation( tmp_pdu ); /* SBSW_CAN_HL12 */
        }
      }
#if (CAN_GENERIC_CONFIRMATION != STD_OFF) && (CAN_TRANSMIT_BUFFER == STD_ON)
      else
      {
# if ( CAN_CANCEL_SUPPORT_API == STD_ON )
        /* SW cancelation - just notifiy IF to restart sending out of Queue */
        CanIf_CancelTxNotification( tmp_pdu, FALSE ); /* SBSW_CAN_HL12 */
# else
#  error "When using Generic Confirmation and Transmit buffer (If) the Cancel-support-api (if) has to be activated"
# endif
      }
#endif
      
    }
#if defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON)
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_3); /* SBSW_CAN_HL11 */
#else
# if defined( C_ENABLE_INDIVIDUAL_POLLING )
    Can_EnableControllerInterrupts((uint8)channel); /* SBSW_CAN_HL13 */
# endif
#endif
  }
  CanHookEnd_CanHL_TxConfirmation();
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* CAN013 */
/****************************************************************************
| NAME:             CanBasicCanMsgReceived
| CALLED BY:        Rx-Interrupt and Polling Task
| PRECONDITIONS:    none
| INPUT PARAMETERS: Controller number, handle to receive object
| RETURN VALUES:    none
| DESCRIPTION:      receive data and call confirmation
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle)
{
  CanHookBegin_CanBasicCanMsgReceived();
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnVoid((channel < kCanNumberOfChannels), CAN_RXINDI_ID, CAN_E_PARAM_CONTROLLER); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL15 */
# endif
  {
    uint8 localDlc;
    Can_IdType localId;
    Can_HwHandleType localHrh;
    tCanRxInfoStruct CanRxInfoStruct;
# if (CAN_GENERIC_PRECOPY == STD_ON) && !defined( C_ENABLE_RX_QUEUE )
    Can_ReturnType generic_retval;
# endif
    #if defined( C_ENABLE_HW_LOOP_TIMER )
    vuint8 canTimerResult;
    #endif
    
    CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
    
    /* CAN012 */
# if defined( C_ENABLE_INDIVIDUAL_POLLING ) /* || (( CAN_NESTED_INTERRUPTS == STD_ON ) && ( CAN_RX_PROCESSING == CAN_INTERRUPT )) - no nesting for same interrupt possible */
    Can_DisableControllerInterrupts((uint8)channel); /* SBSW_CAN_HL13 */
# endif
    /* CAN299, CAN300 */
    CanSetPointerToCanHardware;
    
    assertHardware( ((IF_RECEIVE.ComRequest & kIFxBusy) != kIFxBusy), channel, kErrorRxHwBufferBusy ); /* SBSW_CAN_LL005 */
    
    
    
    /* WrRd,Mask,Arb,Control,ClrIntPnd,TxRqstNDat,DataA,DataB set */
    IF_RECEIVE.ComMask     =  kSetMask | kSetArb | kSetControl | kSetClrIntPnd | kSetTxRqstNDat | kSetDataA | kSetDataB; /* SBSW_CAN_LL004 */
    IF_RECEIVE.ComRequest  =  rxObjHandle + 1; /* SBSW_CAN_LL004 */
    
    if(((IF_RECEIVE.ComRequest & kIFxBusy) == kIFxBusy))
    {
      APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
    
      do{
          CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
    
        } WHILE_CONDITON( ((IF_RECEIVE.ComRequest & kIFxBusy) == kIFxBusy) );
    
      APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
    }
    
    # if defined( C_ENABLE_EXTENDED_ID )  
    RX_MSGOBJ_ID_LOW(channel)          =  IF_RECEIVE.ArbitrFld1; /* SBSW_CAN_LL006 */
    # endif
    RX_MSGOBJ_ID_HIGH(channel)         =  IF_RECEIVE.ArbitrFld2; /* SBSW_CAN_LL006 */
    
    RX_MSGOBJ_DLC(channel)             =  IF_RECEIVE.MessageCntrl & 0xF;  /* only Bit0-3 are interesting for DLC */ /* SBSW_CAN_LL006 */
    
    #if defined(C_CPUTYPE_BIGENDIAN)
    RX_MSGOBJ(channel).Data.ucData[3]  =  IF_RECEIVE.Data.ucData[0]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[2]  =  IF_RECEIVE.Data.ucData[1]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[1]  =  IF_RECEIVE.Data.ucData[2]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[0]  =  IF_RECEIVE.Data.ucData[3]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[7]  =  IF_RECEIVE.Data.ucData[4]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[6]  =  IF_RECEIVE.Data.ucData[5]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[5]  =  IF_RECEIVE.Data.ucData[6]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[4]  =  IF_RECEIVE.Data.ucData[7]; /* SBSW_CAN_LL006 */
    #endif
    
    
    RX_MSGOBJ_MSGCNTRL(channel)        =  IF_RECEIVE.MessageCntrl; /* SBSW_CAN_LL006 */
    (CanRxInfoStruct.pChipMsgObj) = (CanChipMsgPtr)&RX_MSGOBJ(channel);
  /**************************** RAM check failed  *********************************/
# if defined( C_ENABLE_CAN_RAM_CHECK )
  if ((canStatus[channel] & CAN_DEACTIVATE_CONTROLLER) == CAN_DEACTIVATE_CONTROLLER)
  {
    goto finishBasicCan;
  }
# endif
  /**************************** Overrun  ******************************************/
#  if defined( C_ENABLE_OVERRUN )
    if ((RX_MSGOBJ_MSGCNTRL(channel) & kSetMsgLst)!= 0)
    { 
      /* clear Bit MsgLst in rxMsgObj */
      /* WrRd,Mask,Arb,Control,ClrIntPnd,TxRqstNDat,DataA,DataB set */
      IF_RECEIVE.ComMask = kSetWrRd | kSetControl; /* SBSW_CAN_LL004 */
    
      if((rxObjHandle & 0x0001) != 0)
      {
        if(CAN_INDIV_POLLING(channel,rxObjHandle) != 0) /* PRQA S 3325 */ /* MD_Can_3325_LL */
        {                                               /* PRQA S 3201 */ /* MD_Can_3201_LL */
        /* EoB=1 => last Element of FIFO, clear MsgLst */
        IF_RECEIVE.MessageCntrl =  kSetUMask | kSetEoB;  /* EoB = 1 */ /* SBSW_CAN_LL004 */
        }
        else
        {
        /* EoB=1 => last Element of FIFO, clear MsgLst */               
        IF_RECEIVE.MessageCntrl =  kSetEnableRxBasicCanInt | kSetUMask | kSetEoB;  /* EoB = 1 */ /* SBSW_CAN_LL004 */
        }
      }
      else
      {
        if(CAN_INDIV_POLLING(channel,rxObjHandle) != 0) /* PRQA S 3325 */ /* MD_Can_3325_LL */
        {                                               /* PRQA S 3201 */ /* MD_Can_3201_LL */
        /* EoB=0 => first Element of FIFO, clear MsgLst */
        IF_RECEIVE.MessageCntrl =  kSetUMask;            /* EoB = 0 */ /* SBSW_CAN_LL004 */
        }
        else
        {
        /* EoB=0 => first Element of FIFO, clear MsgLst */
        IF_RECEIVE.MessageCntrl =  kSetEnableRxBasicCanInt | kSetUMask;            /* EoB = 0 */ /* SBSW_CAN_LL004 */
        }
      }
    
      IF_RECEIVE.ComRequest = rxObjHandle + 1; /* SBSW_CAN_LL004 */
    
#  if (CAN_OVERRUN_NOTIFICATION == CAN_DET)
      Can_CallDetReportError(CAN_RXINDI_ID, CAN_E_DATALOST); /* CAN395 */ /* SBSW_CAN_HL06 */
#  elif (CAN_OVERRUN_NOTIFICATION == CAN_APPL)
      Appl_CanOverrun( (uint8)channel ); /* SBSW_CAN_HL14 */
#  endif
    }
#  endif
  /**************************** reject remote frames  *****************************/
  /* CAN237 */
  /**************************** Get DLC and Data Pointer **************************/
    /* CAN060, CAN 423 */
    (CanRxInfoStruct.pChipData)         = (CanChipDataPtr)&(RX_MSGOBJ_DATA(channel));  
    localDlc = CanRxActualDLC((&CanRxInfoStruct));
    Can_SilentBswCheckErrorReturnVoid_EnableChIR((localDlc <= CAN_MAX_RX_BUFFER_DLC), CAN_RXINDI_ID, CAN_E_PARAM_DLC); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL17 */
  /**************************** Get ID  &  reject unwanted ID type ****************/
# if ( CAN_EXTENDED_ID == STD_ON )
#  if ( CAN_MIXED_ID == STD_ON )
    if ( CanRxActualIdType((&CanRxInfoStruct)) == kCanIdTypeStd)
    {
      localId = (Can_IdType)CanRxActualStdId((&CanRxInfoStruct));
    }
    else
#  else /* pure Extended ID */
#  endif
    { /* Extended ID */
      localId = (Can_IdType)(CanRxActualExtId((&CanRxInfoStruct)) | CAN_EXTENDED_ID_MASK);
    }
# else /* Standard ID */
    localId = CanRxActualStdId((&CanRxInfoStruct));
# endif
  /**************************** Search Hrh  ***************************************/
#   if !defined(C_HL_BASICCAN_HWHANDLE_REVERSE)
    localHrh = (Can_HwHandleType)((Can_HwHandleType)rxObjHandle - CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)); /* calculate 0 based basic can index */
#   else
    localHrh = (Can_HwHandleType)((CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel)-1) - (Can_HwHandleType)rxObjHandle); /* calculate 0 based basic can index */
#   endif
    localHrh = (Can_HwHandleType)(localHrh / (CAN_MAILBOX[CAN_CONTROLLER_CONFIG(canHwChannel).RxBasicHandleStart].DLC_FIFO)); /* get basic can for this fifo */
    localHrh = (Can_HwHandleType)(localHrh + CAN_CONTROLLER_CONFIG(canHwChannel).RxBasicHandleStart); /* get mailbox index for this basic can */
    Can_SilentBswCheckErrorReturnVoid_EnableChIR((CAN_MAILBOX[localHrh].MailboxType == RxBasicCANType), CAN_RXINDI_ID, CAN_E_PARAM_HANDLE); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL19 */
    Can_SilentBswCheckErrorReturnVoid_EnableChIR(((localHrh >= CAN_CONTROLLER_CONFIG(canHwChannel).RxBasicHandleStart) &&
                                       (localHrh < CAN_CONTROLLER_CONFIG(canHwChannel).RxBasicHandleStop)),
                                       CAN_RXINDI_ID, CAN_E_PARAM_HANDLE); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL21 */
# if defined( C_ENABLE_RX_QUEUE )
  /**************************** Rx Queue handling **********************************/
  /* Copy data to RxQueue and leave Rx path ASAP */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_4); /* SBSW_CAN_HL11 */
    if (canRxQueueInfo.Count < kCanRxQueueSize)   /* Queue not full */ /* SBSW_CM_CAN_HL49 */
    {
      uint8_least i;
      canRxQueueBuffer[canRxQueueInfo.WriteIndex].Hrh = localHrh; /* SBSW_CAN_HL40 */
      canRxQueueBuffer[canRxQueueInfo.WriteIndex].id  = localId; /* SBSW_CAN_HL40 */
      canRxQueueBuffer[canRxQueueInfo.WriteIndex].dlc = localDlc; /* SBSW_CAN_HL40 */
      for (i = 0; i < localDlc; i++) 
      {
        canRxQueueBuffer[canRxQueueInfo.WriteIndex].data[i] = CanRxInfoStruct.pChipData[i]; /* SBSW_CAN_HL41 */
      }
      canRxQueueInfo.Count++;
      if (canRxQueueInfo.WriteIndex < (uint16)(kCanRxQueueSize - 1) )
      {
        canRxQueueInfo.WriteIndex++;
      }
      else
      {
        canRxQueueInfo.WriteIndex = 0; /* SBSW_CM_CAN_HL50 */
      }
    }
    else /* Queue full last message will be lost -> overrun */
    { /* do not change ReadIndex to override latest message because inconsistency problem (currently reading queue) */
      Can_CallDetReportError(CAN_RXINDI_ID, CAN_E_RXQUEUE); /* SBSW_CAN_HL06 */
    }
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_4); /* SBSW_CAN_HL11 */
# else /* C_ENABLE_RX_QUEUE */
  /**************************** Interface + Appl Notifications *********************/
#  if (CAN_GENERIC_PRECOPY == STD_ON)
    {
      generic_retval = Appl_GenericPrecopy((uint8)channel, localId, localDlc, (Can_DataPtrType)CanRxInfoStruct.pChipData);  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL15 */
    }
    if (generic_retval == CAN_OK)
#  endif
    {
      /* CAN234, CAN279, CAN396 */
      CanIf_RxIndication(localHrh, localId, localDlc, (Can_DataPtrType)CanRxInfoStruct.pChipData);  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL16 */
    }
# endif
/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
/* need for some lowlevel complience */
    goto finishBasicCan;     /* to avoid compiler warning */
finishBasicCan:
    ; /* avoid compiler warning for no statement after label */
# if defined( C_ENABLE_INDIVIDUAL_POLLING ) /* || (( CAN_NESTED_INTERRUPTS == STD_ON ) && ( CAN_RX_PROCESSING == CAN_INTERRUPT )) - no nesting for same interrupt possible */
    Can_EnableControllerInterrupts((uint8)channel); /* SBSW_CAN_HL13 */
# endif
  }
  CanHookEnd_CanBasicCanMsgReceived();
} /* PRQA S 6010,6050,6030 */ /* MD_MSR_STPTH,MD_MSR_STCAL,MD_MSR_STCYC */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* CAN013 */
/****************************************************************************
| NAME:             CanFullCanMsgReceived
| CALLED BY:        RxInterrupt
| PRECONDITIONS:    none
| INPUT PARAMETERS: Controller number, handle to receive object
| RETURN VALUES:    none
| DESCRIPTION:      receive data and call confirmation
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanFullCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle)
{
  CanHookBegin_CanFullCanMsgReceived();
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnVoid((channel < kCanNumberOfChannels), CAN_RXINDI_ID, CAN_E_PARAM_CONTROLLER); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL16 */
# endif
  {
    uint8 localDlc;
    Can_IdType localId;
    Can_HwHandleType localHrh;
    tCanRxInfoStruct CanRxInfoStruct;
# if (CAN_GENERIC_PRECOPY == STD_ON) && !defined( C_ENABLE_RX_QUEUE )
    Can_ReturnType generic_retval;
# endif
    #if defined( C_ENABLE_HW_LOOP_TIMER )
    vuint8 canTimerResult;
    #endif
    CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */

    /* CAN012 TBD move to mainfuntion */
# if defined( C_ENABLE_INDIVIDUAL_POLLING ) /* || (( CAN_NESTED_INTERRUPTS == STD_ON ) && ( CAN_RX_PROCESSING == CAN_INTERRUPT )) - no nesting for same interrupt possible */
    Can_DisableControllerInterrupts((uint8)channel); /* SBSW_CAN_HL13 */
# endif
    /* CAN299, CAN300 */
    CanSetPointerToCanHardware;
    
    
    
    /* WrRd,Mask,Arb,Control,ClrIntPnd,TxRqstNDat,DataA,DataB set */
    IF_RECEIVE.ComMask    = kSetMask | kSetArb | kSetControl | kSetClrIntPnd | kSetTxRqstNDat | kSetDataA | kSetDataB; /* SBSW_CAN_LL004 */
    IF_RECEIVE.ComRequest = rxObjHandle + 1; /* SBSW_CAN_LL004 */
    
    if(((IF_RECEIVE.ComRequest & kIFxBusy) == kIFxBusy))
    {
      APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
    
      do{
          CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
    
        } WHILE_CONDITON( ((IF_RECEIVE.ComRequest & kIFxBusy) == kIFxBusy) );
    
      APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
    }
    
    # if defined( C_ENABLE_EXTENDED_ID )
    RX_MSGOBJ_ID_LOW(channel)    =  IF_RECEIVE.ArbitrFld1; /* SBSW_CAN_LL006 */
    # endif
    RX_MSGOBJ_ID_HIGH(channel)   =  IF_RECEIVE.ArbitrFld2; /* SBSW_CAN_LL006 */
    
    /* only Bit0-3 are interesting for DLC */
    RX_MSGOBJ_DLC(channel)             =  IF_RECEIVE.MessageCntrl & 0xF;  /* only Bit0-3 are interesting for DLC */ /* SBSW_CAN_LL006 */
    
    #if defined(C_CPUTYPE_BIGENDIAN)
    RX_MSGOBJ(channel).Data.ucData[3]  =  IF_RECEIVE.Data.ucData[0]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[2]  =  IF_RECEIVE.Data.ucData[1]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[1]  =  IF_RECEIVE.Data.ucData[2]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[0]  =  IF_RECEIVE.Data.ucData[3]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[7]  =  IF_RECEIVE.Data.ucData[4]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[6]  =  IF_RECEIVE.Data.ucData[5]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[5]  =  IF_RECEIVE.Data.ucData[6]; /* SBSW_CAN_LL006 */
    RX_MSGOBJ(channel).Data.ucData[4]  =  IF_RECEIVE.Data.ucData[7]; /* SBSW_CAN_LL006 */
    #endif
    
    
    RX_MSGOBJ_MSGCNTRL(channel)        =  IF_RECEIVE.MessageCntrl; /* SBSW_CAN_LL006 */
    (CanRxInfoStruct.pChipMsgObj) = (CanChipMsgPtr)&RX_MSGOBJ(channel);
  /**************************** RAM check failed  *********************************/
#if defined( C_ENABLE_CAN_RAM_CHECK )
  if ((canStatus[channel] & CAN_DEACTIVATE_CONTROLLER) == CAN_DEACTIVATE_CONTROLLER)
  {
    goto finishRxFullCan;
  }
#endif
  /**************************** Overrun  ******************************************/
#  if defined( C_ENABLE_FULLCAN_OVERRUN )
  if ((RX_MSGOBJ_MSGCNTRL(channel) & kSetMsgLst)!= 0)
  { 
    /* WrRd,Mask,Arb,Control,ClrIntPnd,TxRqstNDat,DataA,DataB set */
    IF_RECEIVE.ComMask = kSetWrRd | kSetControl; /* SBSW_CAN_LL004 */
    
    /* clear MsgLst */
    #if defined (C_ENABLE_INDIVIDUAL_POLLING)
      if(CAN_INDIV_POLLING(channel,rxObjHandle) != 0)
      {
        IF_RECEIVE.MessageCntrl = kSetEoB;
      }
      else
      {
        IF_RECEIVE.MessageCntrl = kSetEoB | kSetRxIE;
      }
    #else
      # if defined (C_ENABLE_RX_FULLCAN_POLLING)
        IF_RECEIVE.MessageCntrl = kSetEoB; /* SBSW_CAN_LL004 */
      #else
        IF_RECEIVE.MessageCntrl = kSetEoB | kSetRxIE; /* SBSW_CAN_LL004 */
      #endif
    #endif
  
  
    IF_RECEIVE.ComRequest = rxObjHandle + 1; /* SBSW_CAN_LL004 */
  
#  if (CAN_OVERRUN_NOTIFICATION == CAN_DET)
     Can_CallDetReportError(CAN_RXINDI_ID, CAN_E_DATALOST); /* CAN395 */ /* SBSW_CAN_HL06 */
#  elif (CAN_OVERRUN_NOTIFICATION == CAN_APPL)
     Appl_CanFullCanOverrun( (uint8)channel ); /* SBSW_CAN_HL14 */
#  endif
  }
#  endif
  /**************************** reject remote frames  *****************************/
  /* CAN237 */
  /**************************** get DLC  ******************************************/
    /* CAN060, CAN 423 */
    (CanRxInfoStruct.pChipData) = (CanChipDataPtr)&(RX_MSGOBJ_DATA(channel));
    localDlc = CanRxActualDLC((&CanRxInfoStruct));
    Can_SilentBswCheckErrorReturnVoid_EnableChIR((localDlc <= CAN_MAX_RX_BUFFER_DLC), CAN_RXINDI_ID, CAN_E_PARAM_DLC); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL17 */
  /**************************** Get ID  &  reject unwanted ID type*****************/
# if ( CAN_EXTENDED_ID == STD_ON )
#  if ( CAN_MIXED_ID == STD_ON )
    if ( CanRxActualIdType((&CanRxInfoStruct)) == kCanIdTypeStd )
    {
      localId = (Can_IdType)CanRxActualStdId((&CanRxInfoStruct));
    }
    else
#  else /* pure Extended ID */
#  endif
    {
      localId = (Can_IdType)(CanRxActualExtId((&CanRxInfoStruct)) | CAN_EXTENDED_ID_MASK);
    }
# else
    localId = CanRxActualStdId((&CanRxInfoStruct));
# endif
  /**************************** search Hrh  ***************************************/
#  if !defined(C_HL_RX_FULLCAN_HWHANDLE_REVERSE)
    localHrh = (Can_HwHandleType)((Can_HwHandleType)((Can_HwHandleType)rxObjHandle - CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)) + CAN_CONTROLLER_CONFIG(canHwChannel).RxFullHandleStart);
#  else
    localHrh = (Can_HwHandleType)((Can_HwHandleType)((CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel)-1) - (Can_HwHandleType)rxObjHandle) + CAN_CONTROLLER_CONFIG(canHwChannel).RxFullHandleStart);
#  endif
    Can_SilentBswCheckErrorReturnVoid_EnableChIR(((localHrh >= CAN_CONTROLLER_CONFIG(canHwChannel).RxFullHandleStart) &&
                                       (localHrh < CAN_CONTROLLER_CONFIG(canHwChannel).RxFullHandleStop)),
                                       CAN_RXINDI_ID, CAN_E_PARAM_HANDLE); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL21 */
# if defined( C_ENABLE_RX_QUEUE )
  /**************************** Rx Queue handling *********************************/
  /* Copy data to RxQueue and leave Rx path ASAP */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_4); /* SBSW_CAN_HL11 */
    if (canRxQueueInfo.Count < kCanRxQueueSize)   /* Queue not full */  /* SBSW_CM_CAN_HL49 */
    {
      uint8_least i;
      canRxQueueBuffer[canRxQueueInfo.WriteIndex].Hrh = localHrh; /* SBSW_CAN_HL40 */
      canRxQueueBuffer[canRxQueueInfo.WriteIndex].id  = localId; /* SBSW_CAN_HL40 */
      canRxQueueBuffer[canRxQueueInfo.WriteIndex].dlc = localDlc; /* SBSW_CAN_HL40 */
      for (i = 0; i < localDlc; i++) 
      {
        canRxQueueBuffer[canRxQueueInfo.WriteIndex].data[i] = CanRxInfoStruct.pChipData[i]; /* SBSW_CAN_HL41 */
      }
      canRxQueueInfo.Count++;
      if (canRxQueueInfo.WriteIndex < (uint16)(kCanRxQueueSize - 1) )
      {
        canRxQueueInfo.WriteIndex++;
      }
      else
      {
        canRxQueueInfo.WriteIndex = 0;  /* SBSW_CM_CAN_HL50 */
      }
    }
    else /* Queue full last message will be lost -> overrun */
    { /* do not change ReadIndex to override latest message because inconsistency problem (currently reading queue) */
      Can_CallDetReportError(CAN_RXINDI_ID, CAN_E_RXQUEUE); /* SBSW_CAN_HL06 */
    }
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_4); /* SBSW_CAN_HL11 */
# else /* C_ENABLE_RX_QUEUE */
  /**************************** Interface + Appl Notifications ********************/
#  if (CAN_GENERIC_PRECOPY == STD_ON)
    {
      generic_retval = Appl_GenericPrecopy((uint8)channel, localId, localDlc, (Can_DataPtrType)CanRxInfoStruct.pChipData);  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL15 */
    }
    if (generic_retval == CAN_OK)
#  endif
    {
      /* CAN234, CAN279, CAN396 */
      CanIf_RxIndication(localHrh, localId, localDlc, (Can_DataPtrType)CanRxInfoStruct.pChipData);  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL16 */
    }
# endif
/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
/* need for some lowlevel complience (e.g. mac71xx) */
    goto finishRxFullCan;     /* to avoid compiler warning */
finishRxFullCan:
    ; /* avoid compiler warning for no statement after label */
# if defined( C_ENABLE_INDIVIDUAL_POLLING ) /* || (( CAN_NESTED_INTERRUPTS == STD_ON ) && ( CAN_RX_PROCESSING == CAN_INTERRUPT )) - no nesting for same interrupt possible */
    Can_EnableControllerInterrupts((uint8)channel); /* SBSW_CAN_HL13 */
# endif
  }
  CanHookEnd_CanFullCanMsgReceived();
} /* PRQA S 6010,6050 */ /* MD_MSR_STPTH,MD_MSR_STCAL */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

/****************************************************************************
| NAME:             CanHL_ErrorHandling
| CALLED BY:        ErrorISR() and Polling Task
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - error interrupt notification for busoff
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_ErrorHandling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnVoid((channel < kCanNumberOfChannels), CAN_CTRBUSOFF_ID, CAN_E_PARAM_CONTROLLER); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL02 */
#endif
  {
    CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */

    CanSetPointerToCanHardware;
    CAN_LL_STATUS(channel) = (STATREG & (kErrBusOff | kWakeupPending)); /* SBSW_CAN_LL006 */
    #if defined (C_ENABLE_SLEEP_WAKEUP)
    # if defined (C_ENABLE_WAKEUP_POLLING)
    # else
    if ((CAN_LL_STATUS(channel) & kWakeupPending) == kWakeupPending)
    {
      CAN_LL_STATUS(channel) &= ~kWakeupPending; /* PRQA S 0277 */ /* MD_Can_0277_negation */  /* PRQA S 4130 */ /* MD_Can_4130_LL */ /* SBSW_CAN_LL006 */
      CanLL_WakeUpHandling(CAN_CHANNEL_CANPARA_ONLY); /* SBSW_CAN_LL007 */
    }
    # endif /* C_ENABLE_WAKEUP_POLLING */
    #endif /* C_ENABLE_SLEEP_WAKEUP */
    
    if ( (STATUS_BUS_OFF(channel) == kCanFalse) && \
         ((CAN_LL_STATUS(channel) & kErrBusOff) == kErrBusOff) && \
         ((CNTRLREG & kSetInit) == kSetInit) )
    {
      STATUS_BUS_OFF(channel) = kCanTrue; /* SBSW_CAN_LL006 */
      CAN_LL_STATUS(channel) &= ~kErrBusOff; /* PRQA S 0277 */ /* MD_Can_0277_negation */  /* PRQA S 4130 */ /* MD_Can_4130_LL */ /* SBSW_CAN_LL006 */
    {
      /* ? ECU Manager restart Controller (no ResetBusOffStart/End needed) */
      Can_EnterCritical(CAN_EXCLUSIVE_AREA_6); /* SBSW_CAN_HL11 */
      canIsBusOff[channel] = TRUE; /* SBSW_CAN_HL17 */
      canStatus[channel] |= CAN_STATUS_BUSOFF; /* SBSW_CAN_HL02 */
      /* CAN020, CAN272, CAN273, CAN274   Controller is in stop mode after CanResetBusOffStart */
#if (CAN_BUSOFF_SUPPORT_API == STD_OFF)
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
      CanResetBusOffStart(channel, lastInitObject[channel]); /* SBSW_CAN_HL18 */
# else
      CanResetBusOffStart(lastInitObject[channel]); /* SBSW_CAN_HL18 */
# endif
#endif
      canStatus[channel] = (uint8)((canStatus[channel] & (CAN_STATUS_INIT | CAN_DEACTIVATE_CONTROLLER)) | CAN_STATUS_STOP); /* no more call of stop from CAN Interface */ /* SBSW_CAN_HL02 */
      Can_LeaveCritical(CAN_EXCLUSIVE_AREA_6); /* SBSW_CAN_HL11 */
      /* CAN019, CAN234 */
      CanIf_ControllerBusOff((uint8)channel); /* SBSW_CAN_HL19 */
    }


      /* clear status in hardware and software */
    #if defined( C_ENABLE_ERROR_POLLING )
    #else
      CAN_LL_STATUS(channel) = STATREG; /* SBSW_CAN_LL006 */
    #endif
      CAN_LL_STATUS(channel) &= ~kErrBusOff; /* PRQA S 0277 */ /* MD_Can_0277_negation */  /* PRQA S 4130 */ /* MD_Can_4130_LL */ /* SBSW_CAN_LL006 */
    }
  }
}

# if defined (C_ENABLE_SLEEP_WAKEUP)
/****************************************************************************
| NAME:             CanHL_WakeUpHandling
| CALLED BY:        WakeupISR()
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      wakeup notification by callback for higher layers
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_WakeUpHandling(CAN_CHANNEL_CANTYPE_ONLY)
{
#  if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnVoid((channel < kCanNumberOfChannels), CAN_CTRWAKEUP_ID, CAN_E_PARAM_CONTROLLER); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL26 */
#  endif
  {
    /* CAN270 (P), CAN269 */
    /* wakeup already done in "CanLL_WakeUpHandling" via macro "CanWakeUp" -> (void)Can_SetControllerMode((uint8)channel, CAN_T_WAKEUP); */
    /* ESCAN00032401: dont change to Stop mode here this will be done later from inside CANIf after Transceiver is switched to normal mode to avoid blocking while 
       Transceiver produce dominant disturbance */
    /* old API     CanIf_SetWakeupEvent( channel, CANIF_CONTROLLER_WAKEUP ); */

    canIsWakeup[channel] = TRUE; /* SBSW_CAN_HL20 */
    /* CAN235, CAN018, CAN271, CAN364 */
    EcuM_CheckWakeup(CanWakeupSourceRef[channel]); /* SBSW_CAN_HL21 */
  }
}
# endif

#if (CAN_DEV_ERROR_DETECT == STD_ON) && defined(CAN_ENABLE_CORE_GEN_CHECK)
/****************************************************************************
| NAME:             Can_CheckGenDataController
| CALLED BY:        Can_Init()
| PRECONDITIONS:    None
| INPUT PARAMETERS: uint8 Controller
| RETURN VALUES:    CAN_NOT_OK
|                   CAN_OK
| DESCRIPTION:      return CAN_NOT_OK if generated data is not valid
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, Can_ReturnType, STATIC_CODE) Can_CheckGenDataController(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  Can_ReturnType retval;
  Can_HwHandleType Htrh;
  Can_HwHandleType Htrh_first;
  Can_HwHandleType Hw_last;

  CanControllerConfig_TabPtrType canChCfgPtr = &CAN_CONTROLLER_CONFIG_INIT[canHwChannel]; /* SBSW_CAN_HL24 */
  Htrh_first = (Can_HwHandleType)-1; /* PRQA S 0277 */ /* MD_Can_0277_invalid */
  Hw_last = (Can_HwHandleType)-1;    /* PRQA S 0277 */ /* MD_Can_0277_invalid */
  retval = CAN_OK;

  {
/* --- Full CAN Tx --- */
    if ( (canChCfgPtr->TxFullHandleMax != 0) && (Htrh_first > canChCfgPtr->TxFullHandleStart) )
    {
      Htrh_first = canChCfgPtr->TxFullHandleStart;
    }
    if ( canChCfgPtr->TxFullHandleMax != (canChCfgPtr->TxFullHandleStop - canChCfgPtr->TxFullHandleStart) )
    {
      retval = CAN_NOT_OK;
    }
    for (Htrh = canChCfgPtr->TxFullHandleStart; Htrh < canChCfgPtr->TxFullHandleStop; Htrh++)
    {
      if (CAN_MAILBOX[Htrh].MailboxType != TxFullCANType)
      {
        retval = CAN_NOT_OK;
      }
      if (CAN_MAILBOX[Htrh].HwHandle == Hw_last)
      {
        retval = CAN_NOT_OK;
      }
      Hw_last = CAN_MAILBOX[Htrh].HwHandle;
      if (CAN_MAILBOX[Htrh].MsgController != canHwChannel)
      {
        retval = CAN_NOT_OK;
      }
    }
/* --- Basic CAN Tx --- */
    if ( (canChCfgPtr->TxBasicHandleMax != 0) && (Htrh_first > canChCfgPtr->TxBasicHandleStart) )
    {
      Htrh_first = canChCfgPtr->TxBasicHandleStart;
    }
    if ( canChCfgPtr->TxBasicHandleMax != (canChCfgPtr->TxBasicHandleStop - canChCfgPtr->TxBasicHandleStart) )
    {
      retval = CAN_NOT_OK;
    }
    for (Htrh = canChCfgPtr->TxBasicHandleStart; Htrh < canChCfgPtr->TxBasicHandleStop; Htrh++)
    {
      if (CAN_MAILBOX[Htrh].MailboxType != TxBasicCANType)
      {
        retval = CAN_NOT_OK;
      }
      if (CAN_MAILBOX[Htrh].HwHandle == Hw_last)
      {
        retval = CAN_NOT_OK;
      }
      Hw_last = CAN_MAILBOX[Htrh].HwHandle;
      if (CAN_MAILBOX[Htrh].MsgController != canHwChannel)
      {
        retval = CAN_NOT_OK;
      }
    }
/* --- Unused --- */
    if ( (canChCfgPtr->UnusedHandleMax != 0) && (Htrh_first > canChCfgPtr->UnusedHandleStart) )
    {
      Htrh_first = canChCfgPtr->UnusedHandleStart;
    }
    if ( canChCfgPtr->UnusedHandleMax != (canChCfgPtr->UnusedHandleStop - canChCfgPtr->UnusedHandleStart) )
    {
      retval = CAN_NOT_OK;
    }
    for (Htrh = canChCfgPtr->UnusedHandleStart; Htrh < canChCfgPtr->UnusedHandleStop; Htrh++)
    {
      if (CAN_MAILBOX[Htrh].MailboxType != UnusedCANType)
      {
        retval = CAN_NOT_OK;
      }
      if (CAN_MAILBOX[Htrh].HwHandle == Hw_last)
      {
        retval = CAN_NOT_OK;
      }
      Hw_last = CAN_MAILBOX[Htrh].HwHandle;
      if (CAN_MAILBOX[Htrh].MsgController != canHwChannel)
      {
        retval = CAN_NOT_OK;
      }
    }
/* --- Full CAN Rx --- */
    if ( (canChCfgPtr->RxFullHandleMax != 0) && (Htrh_first > canChCfgPtr->RxFullHandleStart) )
    {
      Htrh_first = canChCfgPtr->RxFullHandleStart;
    }
    if ( canChCfgPtr->RxFullHandleMax != (canChCfgPtr->RxFullHandleStop - canChCfgPtr->RxFullHandleStart) )
    {
      retval = CAN_NOT_OK;
    }
    for (Htrh = canChCfgPtr->RxFullHandleStart; Htrh < canChCfgPtr->RxFullHandleStop; Htrh++)
    {
      if (CAN_MAILBOX[Htrh].MailboxType != RxFullCANType)
      {
        retval = CAN_NOT_OK;
      }
      if (CAN_MAILBOX[Htrh].HwHandle == Hw_last)
      {
        retval = CAN_NOT_OK;
      }
      Hw_last = CAN_MAILBOX[Htrh].HwHandle;
      if (CAN_MAILBOX[Htrh].MsgController != canHwChannel)
      {
        retval = CAN_NOT_OK;
      }
    }
/* --- Basic CAN Rx --- */
    if ( (canChCfgPtr->RxBasicHandleMax != 0) && (Htrh_first > canChCfgPtr->RxBasicHandleStart) )
    {
      Htrh_first = canChCfgPtr->RxBasicHandleStart;
    }
    if ( canChCfgPtr->RxBasicHandleMax != (canChCfgPtr->RxBasicHandleStop - canChCfgPtr->RxBasicHandleStart) )
    {
      retval = CAN_NOT_OK;
    }
    for (Htrh = canChCfgPtr->RxBasicHandleStart; Htrh < canChCfgPtr->RxBasicHandleStop; Htrh++)
    {
      if (CAN_MAILBOX[Htrh].MailboxType != RxBasicCANType)
      {
        retval = CAN_NOT_OK;
      }
      if (CAN_MAILBOX[Htrh].HwHandle == Hw_last)
      {
        retval = CAN_NOT_OK;
      }
      if (CAN_MAILBOX[Htrh].MsgController != canHwChannel)
      {
        retval = CAN_NOT_OK;
      }
    }
/* --- Mailbox without gaps or overlapping (between channels) --- */
    if (canMailboxIndex != Htrh_first)
    {
      retval = CAN_NOT_OK;
    }
    canMailboxIndex = Htrh; /* next hw-channel-mailbox start here */
  }

  return retval;
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
#endif





#if defined( C_ENABLE_SLEEP_WAKEUP ) 
/* **************************************************************************
| NAME:             CanLL_WakeUpHandling
| CALLED BY:        CanWakeUpTask() and WakeUp-ISR
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: CanChannelHandle  channel        | current CAN channel
|                   and parameters which are defined in CanLL_WakeUpTaskLocalParameter
|
| RETURN VALUES:    -
|
| DESCRIPTION:      perform wakeup handling.
|
| ATTENTION:        CanLL_WakeUpHandling has to contain:
|                     ApplCanPreWakeUp(CAN_CHANNEL_CANPARA_ONLY);
|                     CanWakeUp(CAN_CHANNEL_CANPARA_ONLY);        - if hardware does not wake up automatically
|                     APPL_CAN_WAKEUP( channel );
|                   In case of CommonCAN, it might be necessary to call CanWakeUp even if the hardware
|                   wakes up automatically to make sure all associated HW channels are awaken.
************************************************************************** */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_WakeUpHandling(CAN_CHANNEL_CANTYPE_ONLY)
{


  Can_SetControllerMode(channel, CAN_T_WAKEUP); /* PRQA S 3746 */ /* MD_Can_3746_LL */  /* PRQA S 3200 */ /* MD_Can_3200_LL */ /* SBSW_CAN_LL008 */

  APPL_CAN_WAKEUP( channel ); /* SBSW_CAN_LL007 */
}
/* CODE CATEGORY 4 END */
#endif /*C_ENABLE_SLEEP_WAKEUP*/


#if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
     (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
      !defined( C_ENABLE_TX_POLLING )        || \
      !defined( C_ENABLE_ERROR_POLLING )     || \
       defined( C_ENABLE_INDIVIDUAL_POLLING )|| \
      !defined( C_ENABLE_WAKEUP_POLLING ))        /* ISR necessary; no pure polling configuration*/
/****************************************************************************
| NAME:             CanLL_HandleIllIrptNumber
| CALLED BY:        Can_CellIsr()
|                  
| PRECONDITIONS:    none
| INPUT PARAMETERS: Interruptnumber of Hardwareobject
| RETURN VALUES:    
| DESCRIPTION:      Clear the interrupt of a Hardwareobject
|                  
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_HandleIllIrptNumber(CAN_CHANNEL_CANTYPE_FIRST vuint16 intnumber)
{
  #if defined( C_ENABLE_HW_LOOP_TIMER )
  vuint8 canTimerResult;
  #endif

  CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
  CanSetPointerToCanHardware;

  assertHardware( ((IF_RECEIVE.ComRequest & kIFxBusy) != kIFxBusy), channel, kErrorRxHwBufferBusy ); /* SBSW_CAN_LL005 */
  if(((IF_RECEIVE.ComRequest & kIFxBusy) == kIFxBusy))
  {
    APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */

    do{
        CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */

      } WHILE_CONDITON( ((IF_RECEIVE.ComRequest & kIFxBusy) == kIFxBusy) );

    APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
  }

  /* WrRd,Mask,Arb,Control,ClrIntPnd,TxRqstNDat,DataA,DataB set */
  IF_RECEIVE.ComMask    = kSetMask | kSetArb | kSetControl | kSetClrIntPnd | kSetTxRqstNDat | kSetDataA | kSetDataB; /* SBSW_CAN_LL004 */
  IF_RECEIVE.ComRequest = intnumber + 1; /* SBSW_CAN_LL004 */
}
#endif

#if defined(C_ENABLE_CAN_RAM_CHECK)
/* **************************************************************************
| NAME:             CanLL_IsMailboxCorrupt
| CALLED BY:        CanCheckMemory()
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: CanChannelHandle  channel        | current CAN channel
|                   CanObjectHandle   hwObjHandle    | Handle to hardware object
|
| RETURN VALUES:    kCanTrue:  Mailbox is corrupt
|                   kCanFalse: Mailbox is not corrupt  
|
| DESCRIPTION:      check the current mailbox at index hwObjHandle
************************************************************************** */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle)
{
  vuint8  i;
  vuint8  retval;
  vuint32 CanMemCheckPattern[3] = {0x55555555U,0xAAAAAAAAU,0x00000000U};
  CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
#if defined( C_ENABLE_HW_LOOP_TIMER )
  vuint8 canTimerResult;
#endif

  retval = kCanFalse; 
  CanSetPointerToCanHardware;

  for(i = 0; i < 3; i++)
  {
    /************************************************************************************/
    /* write testvalues into the CAN-Register                                           */
    /************************************************************************************/
    if(((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy))
    {
      APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */

      do{
          CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */

        } WHILE_CONDITON( ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy) );

      APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */

#if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
      if ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy)
      {
        canIsHardwareCanceled[channel] = TRUE;
      }
#endif
    }
    /* Mask,Arb,Control,DataA,DataB set */
    IF_INIT.ComMask         =  kSetWrRd  |  kSetMask  |  kSetArb  |  kSetControl  |  kSetDataA  |  kSetDataB; /* SBSW_CAN_LL004 */
    IF_INIT.ArbitrFld1      =  (vuint16) CanMemCheckPattern[i]; /* SBSW_CAN_LL004 */
    IF_INIT.ArbitrFld2      =  (vuint16) CanMemCheckPattern[i]; /* SBSW_CAN_LL004 */
    IF_INIT.Mask1           =  (vuint16) CanMemCheckPattern[i]; /* SBSW_CAN_LL004 */
    IF_INIT.Mask2           =  (vuint16) CanMemCheckPattern[i]; /* SBSW_CAN_LL004 */
    IF_INIT.Data.ulData[0]  =  CanMemCheckPattern[i]; /* SBSW_CAN_LL004 */
    IF_INIT.Data.ulData[1]  =  CanMemCheckPattern[i]; /* SBSW_CAN_LL004 */
    IF_INIT.MessageCntrl    = (((vuint16)(CanMemCheckPattern[i])) & 0x008F); /* SBSW_CAN_LL004 */

    /* start copy data from IFx to ObjectRAM */
    IF_INIT.ComRequest   =  hwObjHandle + 1; /* SBSW_CAN_LL004 */
    
    if(((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy))
    {
      APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */

      do{
          CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */

        } WHILE_CONDITON( ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy) );

      APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */

#if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
      if ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy)
      {
        canIsHardwareCanceled[channel] = TRUE;
      }
#endif
    }
    /************************************************************************************/
    /* read testvalues from the CAN-Register                                            */
    /************************************************************************************/

    /* Mask,Arb,Control,DataA,DataB set */
    IF_RECEIVE.ComMask     =  kSetMask  |  kSetArb  |  kSetControl  |  kSetDataA  |  kSetDataB; /* SBSW_CAN_LL004 */

    /* start copy data from ObjectRAM to IFx */
    IF_RECEIVE.ComRequest  =  hwObjHandle + 1; /* SBSW_CAN_LL004 */
	
    if(((IF_RECEIVE.ComRequest & kIFxBusy) == kIFxBusy))
    {
      APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */

      do{
          CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */

        } WHILE_CONDITON( ((IF_RECEIVE.ComRequest & kIFxBusy) == kIFxBusy) );

      APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */

#if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
      if ((IF_RECEIVE.ComRequest & kIFxBusy) == kIFxBusy)
      {
        canIsHardwareCanceled[channel] = TRUE;
      }
#endif
    }

    if( (IF_RECEIVE.ArbitrFld1             != ((vuint16) CanMemCheckPattern[i])) || 
        (IF_RECEIVE.ArbitrFld2             != ((vuint16) CanMemCheckPattern[i])) ||
        (IF_RECEIVE.Mask1                  != ((vuint16) CanMemCheckPattern[i])) || 
        (IF_RECEIVE.Mask2                  != (((vuint16) CanMemCheckPattern[i]) | 0x2000)) ||
        (IF_RECEIVE.Data.ulData[0]         != CanMemCheckPattern[i]) || 
        (IF_RECEIVE.Data.ulData[1]         != CanMemCheckPattern[i]) ||
       ((IF_RECEIVE.MessageCntrl & 0x008F) != (((vuint16) CanMemCheckPattern[i]) & 0x008F)))
    {
      retval = kCanTrue; /* the mailbox is corrupt */
      break;
    }
  } 

  return(retval);
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* CODE CATEGORY 4 END */
#endif

#if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
     (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
      !defined( C_ENABLE_TX_POLLING )        || \
      defined( C_ENABLE_INDIVIDUAL_POLLING ) || \
      !defined( C_ENABLE_ERROR_POLLING )     ||\
      !defined( C_ENABLE_WAKEUP_POLLING ))        /* ISR necessary; no pure polling configuration*/
/* **************************************************************************
| NAME:             Can_CellIsr
| CALLED BY:        CanIsr_<x>, where x=0..2
| PRECONDITIONS:
| INPUT PARAMETERS: canHwChannel
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service functions according to the CAN controller
|                   interrupt stucture
|                   - check for the interrupt reason ( interrupt source )
|                   - work appropriate interrupt:
|                     + status/error interrupt (busoff, wakeup, error warning)
|                     + basic can receive
|                     + full can receive
|                     + can transmit
|
|                   If an Rx-Interrupt occurs while the CAN controller is in Sleep mode, 
|                   a wakeup has to be generated. 
|
|                   If an Tx-Interrupt occurs while the CAN controller is in Sleep mode, 
|                   an assertion has to be called and the interrupt has to be ignored.
|
|                   The name of BrsTimeStrt...() and BrsTimeStop...() can be addapted to 
|                   realy used name of the interrupt functions.
|
************************************************************************** */

#define CAN_STOP_SEC_STATIC_CODE  /*---------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CAN_START_SEC_CODE  /*---------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* CODE CATEGORY 1 START */
V_DEF_FUNC(V_NONE, void, CODE) Can_CellIsr( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
# if defined( C_ENABLE_HW_LOOP_TIMER )
  vuint8 canTimerResult;
# endif

  vuint16 intnumber;
  CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
 
# if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Start(RtmConf_RtmMeasurementPoint_Can_CellIsr);
# endif 
  CanSetPointerToCanHardware;

  intnumber = INTERRUPTREG;

  APPLCANTIMERSTART(kCanLoopIrqReq); /* SBSW_CAN_LL003 */

  do
  {
    if ((intnumber & 0x8000) == kCanStatusInt) 
    {
      /*********************************************************************/
      /* Status Interrupt                                                  */
      /*********************************************************************/
# if (defined( C_ENABLE_ERROR_POLLING ) && defined( C_ENABLE_WAKEUP_POLLING ))
      assertInternal (0, channel, kErrorHwObjNotInPolling); /* SBSW_CAN_LL005 */
# else     
      CanHL_ErrorHandling( CAN_CHANNEL_CANPARA_ONLY ); /* SBSW_CAN_LL007 */
# endif
    }
    else
    {
      /*********************************************************************/
      /* CAN-Message Interrupt                                             */
      /*********************************************************************/
      assertInternal (intnumber<=CAN_NUMBER_OF_MSG(channel), channel, kErrorIllIrptNumber); /* SBSW_CAN_LL005 */
# if defined ( C_ENABLE_RX_BASICCAN_OBJECTS )
      if(intnumber >= (CAN_HL_HW_RX_BASIC_STARTINDEX(channel) + 1))
      {
        /*******************************************************************/
        /* BasicCAN-Interrupt                                              */
        /*******************************************************************/
#  if (defined ( C_ENABLE_RX_BASICCAN_POLLING ) && !defined (C_ENABLE_INDIVIDUAL_POLLING))
        assertInternal (0, channel, kErrorHwObjNotInPolling); /* SBSW_CAN_LL005 */
#  else
        CanBasicCanMsgReceived( CAN_CHANNEL_CANPARA_FIRST intnumber - 1); /* SBSW_CAN_LL009 */
#  endif
      }
      else
# endif
      {                
        if(intnumber >= (CAN_HL_HW_RX_FULL_STARTINDEX(channel) + 1))
        {
# if defined ( C_ENABLE_RX_FULLCAN_OBJECTS )
          /*****************************************************************/
          /* FullCAN-Interrupt                                             */
          /*****************************************************************/
#  if (defined (C_ENABLE_RX_FULLCAN_POLLING) && !defined (C_ENABLE_INDIVIDUAL_POLLING))
          assertInternal (0, channel, kErrorHwObjNotInPolling); /* SBSW_CAN_LL005 */
#  else
          CanFullCanMsgReceived( CAN_CHANNEL_CANPARA_FIRST intnumber - 1); /* SBSW_CAN_LL009 */
#  endif
# endif
        }
        else
        {
          if(intnumber >= (CAN_HL_HW_TX_STOPINDEX(channel) + 1))
          {
            /***************************************************************/
            /* Illegal-Interrupt                                           */
            /***************************************************************/
            assertInternal (0, channel, kErrorIllIrptNumber); /* SBSW_CAN_LL005 */                  
            CanLL_HandleIllIrptNumber(CAN_CHANNEL_CANPARA_FIRST intnumber - 1); /* SBSW_CAN_LL009 */
          }
          else
          {
            if (intnumber == 0) 
            {
                /* unexpected interrupt, do nothing */
            }
            else
            {
# if (defined( C_ENABLE_TX_POLLING) && !defined (C_ENABLE_INDIVIDUAL_POLLING))
                /***************************************************************/
                /* TxSend-Interrupt                                            */
                /***************************************************************/
                assertInternal (0, channel, kErrorHwObjNotInPolling); /* SBSW_CAN_LL005 */                
# else 
                /* Tx Confirmation-Interrupt --------------------------------- */
                CanHL_TxConfirmation(CAN_CHANNEL_CANPARA_FIRST intnumber - 1); /* SBSW_CAN_LL009 */
# endif
            }
          }
        }
      }
    }

    intnumber = INTERRUPTREG;

    CANTIMERRESULT_UPDATE(kCanLoopIrqReq); /* SBSW_CAN_LL003 */

  } WHILE_CONDITON( (intnumber != 0) );

  APPLCANTIMEREND(kCanLoopIrqReq); /* SBSW_CAN_LL003 */

# if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
  Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_CellIsr);
# endif  
}/* PRQA S 6030,6050,6080 */ /* MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
/* CODE CATEGORY 1 END */



#define CAN_STOP_SEC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* ISR necessary; no pure polling configuration*/

#define CAN_STOP_SEC_STATIC_CODE  /*---------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*-------------------------------------------------------------------------*/


#define CAN_START_SEC_CODE  /*---------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#if (CAN_VERSION_INFO_API == STD_ON) /* CAN252 */
/* CAN224 */
/****************************************************************************
| NAME:             Can_GetVersionInfo
| CALLED BY:        Application
| PRECONDITIONS:    Preprocessed
| INPUT PARAMETERS: Pointer to version structure
| RETURN VALUES:    none
| DESCRIPTION:      get version of the can driver
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_GetVersionInfo( Can_VersionInfoPtrType VersionInfo )
{
  CanHookBegin_Can_GetVersionInfo();
  Can_CheckDetErrorReturnVoid((VersionInfo != NULL_PTR), CAN_VERSION_ID, CAN_E_PARAM_POINTER); /* SBSW_CAN_HL06 */
  {
    /* CAN105 */
    VersionInfo->vendorID   = CAN_VENDOR_ID; /* SBSW_CAN_HL23 */
    VersionInfo->moduleID   = CAN_MODULE_ID; /* SBSW_CAN_HL23 */
# if (CAN_MICROSAR_VERSION == CAN_MSR30)
    VersionInfo->instanceID = 0; /* SBSW_CAN_HL23 */
# endif
    VersionInfo->sw_major_version = (uint8)CAN_SW_MAJOR_VERSION; /* SBSW_CAN_HL23 */
    VersionInfo->sw_minor_version = (uint8)CAN_SW_MINOR_VERSION; /* SBSW_CAN_HL23 */
    VersionInfo->sw_patch_version = (uint8)CAN_SW_PATCH_VERSION; /* SBSW_CAN_HL23 */
  }
  CanHookEnd_Can_GetVersionInfo();
}
#endif

/* BR:011 */
/****************************************************************************
| NAME:             Can_InitMemory
| CALLED BY:        Application
| PRECONDITIONS:    none
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      initialization of global variables to rerun system without powerup
|                   Used to support debugging (let debugger run)
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_InitMemory( void )
{
  CanHookBegin_Can_InitMemory();
#if (CAN_DEV_ERROR_DETECT == STD_ON) || defined(CAN_ENABLE_SELECTABLE_PB)
  {
    CAN_CHANNEL_CANTYPE_LOCAL
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
    CanChannelHandle maxController;
#  if (CAN_MICROSAR_VERSION == CAN_MSR403)
    maxController = (CanChannelHandle)CanControllerMax;
#  else
    maxController = (CanChannelHandle)((CanConfigSet).CanControllerMax);
#  endif
    for (channel = 0; channel < maxController; channel++) /* loop over all available channels */
# endif /* CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF */
    {
      {
        canControllerConfigPtr[canHwChannel] = NULL_PTR; /* SBSW_CAN_HL24 */
      }
    }
  }
#endif
  canConfigInitFlag = CAN_STATUS_UNINIT;  /* CAN103 */
#if defined(CAN_ENABLE_SELECTABLE_PB) || defined(C_ENABLE_MULTI_ECU_CONFIG)
  canConfigPtr = NULL_PTR;
#endif /* otherwise const pointer is used */
  /* only needed by ASR (and only if variables have to be initialized but will not be done in normal init) */
#if(CAN_DEV_ERROR_DETECT == STD_OFF) && defined( V_ENABLE_USE_DUMMY_STATEMENT )
  canConfigInitFlag = canConfigInitFlag;
#endif
  CanHookEnd_Can_InitMemory();
}

#if (CAN_MICROSAR_VERSION == CAN_MSR30)
/****************************************************************************
| NAME:             Can_InitStruct
| CALLED BY:        Application
| PRECONDITIONS:    Can_Init() was called but not Can_InitController()
| INPUT PARAMETERS: Controller, Index of InitStruct to be set (Baudrate and masks)
| RETURN VALUES:    none
| DESCRIPTION:      Set InitStruct before Init Controller
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_InitStruct( uint8 Controller, uint8 Index )
{
  CanHookBegin_Can_InitStruct();
  Can_SilentBswCheckErrorReturnVoid(((channel < kCanNumberOfChannels) && 
                               (Index < (uint8)(CAN_INIT_OBJ_START_IDX[channel+1] - CAN_INIT_OBJ_START_IDX[channel])) ),
                               CAN_INIT_ID, CAN_E_PARAM_HANDLE); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL34 */
  {
    lastInitObject[channel] = (uint8)(CAN_INIT_OBJ_START_IDX[channel] + Index); /* SBSW_CAN_HL25 */
  }
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON ) && defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
  CanHookEnd_Can_InitStruct();
}
#endif /* only MSR30 */

#if (CAN_MICROSAR_VERSION == CAN_MSR403)
# if ((CAN_CHANGE_BAUDRATE_SUPPORT == STD_ON) || (CAN_SET_BAUDRATE_API == STD_OFF))
/* CAN449 */
/****************************************************************************
| NAME:             Can_ChangeBaudrate
| CALLED BY:        application
| PRECONDITIONS:    Stop mode
| INPUT PARAMETERS: uint8 Controller, const uint16 Baudrate
| RETURN VALUES:    Std_ReturnType: E_NOT_OK, E_OK
| DESCRIPTION:     This service shall change the baudrate of the CAN controller.
****************************************************************************/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_ChangeBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, AUTOMATIC) Baudrate )
{
  CanHookBegin_Can_ChangeBaudrate();
  Can_CheckDetErrorReturnValue((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_CHANGE_BR_ID, CAN_E_UNINIT, E_NOT_OK); /* CAN450 */ /* SBSW_CAN_HL06 */
  Can_SilentBswCheckErrorReturnValue((channel < kCanNumberOfChannels), CAN_CHANGE_BR_ID, CAN_E_PARAM_CONTROLLER, E_NOT_OK); /* CAN452 */ /* SBSW_CAN_HL06, SBSW_CM_CAN_HL34 */
  Can_CheckDetErrorReturnValue(((canStatus[channel] & CAN_STATUS_STOP) == CAN_STATUS_STOP), CAN_CHANGE_BR_ID, CAN_E_TRANSITION, E_NOT_OK); /* CAN256, CAN453 */ /* SBSW_CAN_HL06 */
  {
    uint8 baudrateIndex;
    for (baudrateIndex = CAN_INIT_OBJ_START_IDX[channel]; baudrateIndex < CAN_INIT_OBJ_START_IDX[channel+1]; baudrateIndex++)
    {
      if (CAN_INIT_OBJ_BAUDRATE[baudrateIndex] == Baudrate)
      {
        lastInitObject[channel] = baudrateIndex; /* SBSW_CAN_HL25 */
        Can_InitController((uint8)channel, NULL_PTR); /* CAN062, CAN260, CAN422, CAN255 */
        CanHookEnd_Can_ChangeBaudrate();
        return E_OK;
      }
    }
  }
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON ) && defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
  Can_CallDetReportError(CAN_CHANGE_BR_ID, CAN_E_PARAM_BAUDRATE); /* CAN451 */ /* SBSW_CAN_HL06 */
  CanHookEnd_Can_ChangeBaudrate();
  return E_NOT_OK;
}
# endif

# if (CAN_CHANGE_BAUDRATE_SUPPORT == STD_ON)
/* CAN454 */
/****************************************************************************
| NAME:             Can_CheckBaudrate
| CALLED BY:        application
| PRECONDITIONS:    Initialized
| INPUT PARAMETERS: uint8 Controller, const uint16 Baudrate
| RETURN VALUES:    Std_ReturnType: E_NOT_OK, E_OK
| DESCRIPTION:      This service shall check if a certain baudrate of the CAN controller is supported.
****************************************************************************/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, AUTOMATIC) Baudrate )
{
  CanHookBegin_Can_CheckBaudrate();
  Can_CheckDetErrorReturnValue((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_CHECK_BR_ID, CAN_E_UNINIT, E_NOT_OK); /* CAN456, CAN459 */ /* SBSW_CAN_HL06 */
  Can_CheckDetErrorReturnValue((channel < kCanNumberOfChannels), CAN_CHECK_BR_ID, CAN_E_PARAM_CONTROLLER, E_NOT_OK); /* CAN457 */ /* SBSW_CAN_HL06 */
  {
    uint8 baudrateIndex;
    for (baudrateIndex = CAN_INIT_OBJ_START_IDX[channel]; baudrateIndex < CAN_INIT_OBJ_START_IDX[channel+1]; baudrateIndex++)
    {
      if (CAN_INIT_OBJ_BAUDRATE[baudrateIndex] == Baudrate)
      {
        CanHookEnd_Can_CheckBaudrate();
        return E_OK;
      }
    }
  }
#  if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON ) && defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
#  endif
  Can_CallDetReportError(CAN_CHECK_BR_ID, CAN_E_PARAM_BAUDRATE); /* CAN458 */ /* SBSW_CAN_HL06 */
  CanHookEnd_Can_CheckBaudrate();
  return E_NOT_OK;
}
# endif /* CAN_CHANGE_BAUDRATE_SUPPORT == STD_ON */

# if (CAN_SET_BAUDRATE_API == STD_ON)
/****************************************************************************
| NAME:             Can_SetBaudrate
| CALLED BY:        application
| PRECONDITIONS:    Stop mode
| INPUT PARAMETERS: uint8 Controller, uint16 BaudRateConfigID
| RETURN VALUES:    Std_ReturnType: E_NOT_OK, E_OK
| DESCRIPTION:      This service shall set the baud rate configuration of the CAN controller. Depending 
|                   on necessary baud rate modifications the controller might have to reset.
****************************************************************************/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{
  CanHookBegin_Can_SetBaudrate();
  Can_CheckDetErrorReturnValue((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_SET_BR_ID, CAN_E_UNINIT, E_NOT_OK); /* CAN492 */
  Can_SilentBswCheckErrorReturnValue((channel < kCanNumberOfChannels), CAN_SET_BR_ID, CAN_E_PARAM_CONTROLLER, E_NOT_OK); /* CAN494 */ 
  Can_CheckDetErrorReturnValue(((canStatus[channel] & CAN_STATUS_STOP) == CAN_STATUS_STOP), CAN_SET_BR_ID, CAN_E_TRANSITION, E_NOT_OK); /* CAN260 */
  Can_CheckDetErrorReturnValue((BaudRateConfigID < (uint16)(CAN_INIT_OBJ_START_IDX[channel+1] - CAN_INIT_OBJ_START_IDX[channel])), 
                                  CAN_SET_BR_ID, CAN_E_PARAM_BAUDRATE, E_NOT_OK); /* CAN493 */
  {
    lastInitObject[channel] = (uint8)(CAN_INIT_OBJ_START_IDX[channel] + BaudRateConfigID);
    Can_InitController((uint8)channel, NULL_PTR); /* CAN062, CAN256, CAN422, CAN255 */
  }
  
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON ) && defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
  CanHookEnd_Can_SetBaudrate();
  return E_OK;
}
# endif /* CAN_SET_BAUDRATE_API == STD_ON */

#endif /* only MSR403 */


/* CAN239, CAN154, CAN250, CAN053, CAN407, CAN054, CAN055, CAN223, CAN176 */
/****************************************************************************
| NAME:             Can_Init
| CALLED BY:        CanInterface
| PRECONDITIONS:    Disabled Interrupts
| INPUT PARAMETERS: Pointer to Configuration structure
| RETURN VALUES:    none
| DESCRIPTION:      initialization of global CAN hardware
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_Init( Can_ConfigPtrType ConfigPtr )
{
  CAN_CHANNEL_CANTYPE_LOCAL
  CanHookBegin_Can_Init();
#if defined(CAN_ENABLE_SELECTABLE_PB) || defined(C_ENABLE_MULTI_ECU_CONFIG)
# if (CAN_MICROSAR_VERSION == CAN_MSR403)
  if (ConfigPtr == NULL_PTR) {
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
    return;
  }
  if (ConfigPtr->FinalMagicNumber != 0xfa50u) {
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
    return;
  }
# else
  Can_CheckDetErrorReturnVoid((ConfigPtr != NULL_PTR), CAN_INIT_ID, CAN_E_PARAM_POINTER); /* CAN175 */ /* SBSW_CAN_HL06 */
  Can_CheckDetErrorReturnVoid((ConfigPtr->FinalMagicNumber == 0xaffeu), CAN_INIT_ID, CAN_E_PARAM_POINTER); /* SBSW_CAN_HL06 */
# endif
  canConfigPtr = ConfigPtr; /* CAN056, CAN021, CAN291 */
#else
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  ConfigPtr = ConfigPtr;     /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  ConfigPtr = canConfigPtr;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
#endif /* CAN_ENABLE_SELECTABLE_PB ||  || C_ENABLE_MULTI_ECU_CONFIG */
  /* already initialized -> 2nd call is not allowed */
  Can_CheckDetErrorReturnVoid(canConfigInitFlag == CAN_STATUS_UNINIT, CAN_INIT_ID, CAN_E_TRANSITION); /* CAN174, CAN247 */ /* SBSW_CAN_HL06 */
#if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
  if (  ( CAN_GLOBAL_CONFIG(Can_BaseDll_GeneratorVersion)     != (uint16)CAN_GEN_BASE_VERSION ) ||
        ( CAN_GLOBAL_CONFIG(Can_PlatformDll_GeneratorVersion) != (uint16)CAN_GEN_Tms470DcanAsr_VERSION ) )
  {
# if (CAN_MICROSAR_VERSION == CAN_MSR403)
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION);
# else
    EcuM_GeneratorCompatibilityError((uint16) CAN_MODULE_ID, (uint8) 0); /* SBSW_CAN_HL26 */
# endif
    return;
  }
#endif
#if (CAN_MICROSAR_VERSION != CAN_MSR403)
# if ( CAN_CRC_CHECK == STD_ON )
  if (( CAN_GLOBAL_CONFIG(Can_ePrecompileCRC) != CAN_PRECOMPILE_CRC ) || ( CAN_GLOBAL_CONFIG(Can_eLinktimeCRC) != Can_LinktimeCRC ))
  {
    EcuM_GeneratorCompatibilityError((uint16) CAN_MODULE_ID, (uint8) 0u); /* SBSW_CAN_HL26 */
    return;
  }
# endif
#endif
#if (CAN_DEV_ERROR_DETECT == STD_ON) && defined(CAN_ENABLE_SELECTABLE_PB) && (CAN_MICROSAR_VERSION != CAN_MSR403)
  if (
# if ( CAN_COMMON_CAN == STD_ON )
       (kCanNumberOfHwChannels > kCanNumberOfMaxUsedControllers) ||
# endif
       (kCanNumberOfChannels > kCanNumberOfMaxUsedControllers) ||
       (kCanNumberOfUsedHwChannels > kCanNumberOfMaxUsedControllers) )
  { /* check consistency of generated Data (real channel amount against max value) */
    Can_CallDetReportError(CAN_INIT_ID, CAN_E_PARAM_POINTER); /* SBSW_CAN_HL06 */
  }
#endif
  {
    {
      Can_SignedHwHandleType tmp_objcnt;
#if defined(C_ENABLE_RX_POLLING)
      canRxTaskActive = CAN_FREE;
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API != STD_ON) && (CAN_DEV_TIMEOUT_DETECT == STD_ON) && (CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_MICROSAR_VERSION == CAN_MSR30)
      canApiContext = CAN_INIT_ID;
#endif
#if defined( C_ENABLE_RX_QUEUE )
/* delete RxQueue (all channels) */
      canRxQueueInfo.WriteIndex = 0;  /* SBSW_CM_CAN_HL50 */
      canRxQueueInfo.ReadIndex = 0;
      canRxQueueInfo.Count = 0;
#endif
/* Set active Identity */
#if defined ( C_ENABLE_MULTI_ECU_CONFIG )
      CanSetActiveIdentity(CAN_GLOBAL_CONFIG(IdentitySelected)); /* SBSW_CAN_HL46 */
#endif
      #if defined( V_ENABLE_USE_DUMMY_STATEMENT )
      STATUS_STOP_MODE(0) = STATUS_STOP_MODE(0); /* dummy assignment to avoid compiler warning */ /* SBSW_CAN_LL010 */
      #endif
      #if defined (C_SINGLE_RECEIVE_CHANNEL )
      CAN_LL_STATUS(channel)    = 0; /* SBSW_CAN_LL006 */
      STATUS_STOP_MODE(channel) = 0; /* SBSW_CAN_LL006 */
      #else
      {
        vuint16 channel_number;
      
        for(channel_number=0; channel_number<kCanNumberOfChannels; channel_number++)
        {
          CAN_LL_STATUS(channel_number)    = 0; /* SBSW_CAN_LL006 */
          STATUS_STOP_MODE(channel_number) = 0; /* SBSW_CAN_LL006 */
        }  
      }
      #endif
      
      canConfigInitFlag = CAN_STATUS_INIT; /* CAN246, CAN248 - before Controller Init begin */
/* calculate logical tx handle over all logical channels (done here because of multiple ecu) */
      tmp_objcnt=0;
#if (CAN_DEV_ERROR_DETECT == STD_ON) && defined(CAN_ENABLE_CORE_GEN_CHECK)
      canMailboxIndex = 0;
#endif
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
      for (channel = 0; channel < kCanNumberOfChannels; channel++) /* over all */
#endif
      {
/*      calculate hw to log   */
#if defined(C_ENABLE_GEN_HW_START_STOP_IDX) /* generated as tool-table */
# if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST)
        CAN_HL_TX_OFFSET_HW_TO_LOG(channel) = (Can_SignedHwHandleType)(tmp_objcnt - (Can_SignedHwHandleType)CAN_CONTROLLER_CONFIG_INIT[CAN_HL_HW_CHANNEL_STARTINDEX(channel)].TxBasicHwStart); /* SBSW_CAN_HL27 */
# else
        CAN_HL_TX_OFFSET_HW_TO_LOG(channel) = (Can_SignedHwHandleType)(tmp_objcnt - (Can_SignedHwHandleType)CAN_CONTROLLER_CONFIG_INIT[CAN_HL_HW_CHANNEL_STARTINDEX(channel)].TxFullHwStart); /* SBSW_CAN_HL27 */
# endif
#else
# if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST)
        CAN_HL_TX_OFFSET_HW_TO_LOG(channel) = (Can_SignedHwHandleType)(tmp_objcnt - (Can_SignedHwHandleType)CAN_MAILBOX[CAN_CONTROLLER_CONFIG_INIT[CAN_HL_HW_CHANNEL_STARTINDEX(channel)].TxBasicHandleStart].HwHandle); /* SBSW_CAN_HL27 */
# else
#  if defined(C_HL_TX_FULLCAN_HWHANDLE_REVERSE)
#   error "This configuration is not supported - generated the hardware index table or use none-reverse order here"
#  else
        CAN_HL_TX_OFFSET_HW_TO_LOG(channel) = (Can_SignedHwHandleType)(tmp_objcnt - (Can_SignedHwHandleType)CAN_MAILBOX[CAN_CONTROLLER_CONFIG_INIT[CAN_HL_HW_CHANNEL_STARTINDEX(channel)].TxFullHandleStart].HwHandle); /* SBSW_CAN_HL27 */
#  endif
# endif
#endif
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
        tmp_objcnt = (Can_SignedHwHandleType)(tmp_objcnt + (Can_SignedHwHandleType)CAN_CONTROLLER_CONFIG_INIT[CAN_HL_HW_CHANNEL_STARTINDEX(channel)].TxFullHandleMax + (Can_SignedHwHandleType)(CAN_CONTROLLER_CONFIG_INIT[CAN_HL_HW_CHANNEL_STARTINDEX(channel)].TxBasicHandleMax * CAN_MULTIPLEXED_TX_MAX));
#endif
/*      initizalize startup values for each controllers   */
        canStatus[channel] = CAN_STATUS_UNINIT; /* SBSW_CAN_HL02 */
#if ((CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403))
        canStatusReq[channel] = CAN_STATUS_UNINIT; /* SBSW_CAN_HL04 */
#endif
        canIsBusOff[channel] = FALSE;  /* startup: no busoff */ /* SBSW_CAN_HL17 */
        lastInitObject[channel] = (uint8)(CAN_INIT_OBJ_START_IDX[channel]); /* SBSW_CAN_HL25 */
#if defined (C_ENABLE_SLEEP_WAKEUP)
        canIsWakeup[channel] = FALSE; /* SBSW_CAN_HL20 */
#endif
        canCanInterruptCounter[channel] = 0; /* SBSW_CAN_HL28 */
#if defined( C_ENABLE_PARTIAL_NETWORK )
        canTimeoutCall[channel] = TRUE; /* SBSW_CAN_HL29 */
#endif

#if (CAN_DEV_ERROR_DETECT == STD_ON) || defined(CAN_ENABLE_SELECTABLE_PB)
        {
          {
# if defined(CAN_ENABLE_CORE_GEN_CHECK) && (CAN_DEV_ERROR_DETECT == STD_ON)
            if ( Can_CheckGenDataController(CAN_HW_CHANNEL_CANPARA_ONLY) == CAN_NOT_OK ) /* SBSW_CAN_HL22 */
            { /* check Generated Data for this channel */
              Can_CallDetReportError(CAN_INIT_ID, CAN_E_PARAM_POINTER); /* SBSW_CAN_HL06 */
            }
# endif
            canControllerConfigPtr[canHwChannel] = NULL_PTR; /* SBSW_CAN_HL24 */
          }
        }
#endif

        /* CAN239, CAN245 */
#if (CAN_MICROSAR_VERSION == CAN_MSR40)
        Can_InitController((uint8)channel, &Can_ControllerBaudrateConfig[0]);      /* use always first initStruct */ /* SBSW_CAN_HL07 */
#elif (CAN_MICROSAR_VERSION == CAN_MSR403)
        canStatus[channel] |= CAN_STATUS_STOP; /* set to stop mode before set baudrate to avoid DET */
# if (CAN_SET_BAUDRATE_API == STD_ON)
        (void)Can_SetBaudrate( (uint8)channel, CAN_CONTROLLER_CONFIG_INIT[CAN_HL_HW_CHANNEL_STARTINDEX(channel)].CanControllerDefaultBaudrateIdx);
# else
        (void)Can_ChangeBaudrate( (uint8)channel, CAN_CONTROLLER_CONFIG_INIT[CAN_HL_HW_CHANNEL_STARTINDEX(channel)].CanControllerDefaultBaudrate); /* CAN435_Conf */
# endif
#else
# if (CANIF_VENDOR_ID != 0x001E) /* For Vector ASR3 this will be done within Can Interface */
        Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL07 */
# endif
#endif
      }
    }
  }
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
# if !(defined(CAN_ENABLE_SELECTABLE_PB) || defined(C_ENABLE_MULTI_ECU_CONFIG))
  ConfigPtr = ConfigPtr; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
#endif
  CanHookEnd_Can_Init();
} /* PRQA S 6010 */ /* MD_MSR_STPTH */

/* CAN062, CAN255, CAN229, CAN192, CAN236, CAN237, CAN419, CAN422 */
/****************************************************************************
| NAME:             Can_InitController
| CALLED BY:        CanInterface
| PRECONDITIONS:    Disabled Interrupts
| INPUT PARAMETERS: Controller number, Pointer to Configuration structure
| RETURN VALUES:    none
| DESCRIPTION:      initialization of Controller special CAN hardware
****************************************************************************/
#if (CAN_MICROSAR_VERSION == CAN_MSR40)
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerBaudrateConfigPtrType Config )
#else
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerConfigPtrType ControllerConfigPtr )
#endif
{
  CanHookBegin_Can_InitController();
  /* CAN248 */
  Can_CheckDetErrorReturnVoid((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_INITCTR_ID, CAN_E_UNINIT); /* CAN187 */ /* SBSW_CAN_HL06 */
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnVoid((channel < kCanNumberOfChannels), CAN_INITCTR_ID, CAN_E_PARAM_CONTROLLER); /* CAN189 */ /* SBSW_CAN_HL06, SBSW_CM_CAN_HL03 */
#endif
#if ( CAN_MICROSAR_VERSION == CAN_MSR40 )
  Can_CheckDetErrorReturnVoid(( Config != NULL_PTR ), CAN_INITCTR_ID, CAN_E_PARAM_POINTER); /* CAN188 */ /* SBSW_CAN_HL06 */
#endif
#if defined ( C_ENABLE_MULTI_ECU_CONFIG )
  if ( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) != (cantVIdentityMsk)0 )  /* PRQA S 2004 */ /* MD_Can_2004 */
#endif
  {
    uint8 initObject;
    Can_HwHandleType hwObjHandle;
    Can_HwHandleType Htrh;
    CanObjectHandle logTxObjHandle;
#if defined( C_ENABLE_CAN_RAM_CHECK )
    uint8 canRamCheckStatus;
#endif
    
    #if defined( C_ENABLE_HW_LOOP_TIMER )
    vuint8 canTimerResult;
    #endif
    
    V_DEF_P2SFR_CAN(V_NONE, CAN_CellAddrMap, VAR_NOINIT) pCanNode;
    
    #if defined( C_ENABLE_DCAN_ISSUE22_WORKAROUND )
    vuint16 nbOfIterations;
    vuint32 tmpCNTRLREG;
    #endif
    
    vuint8 unused_init_flag;

#if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API != STD_ON) && (CAN_DEV_TIMEOUT_DETECT == STD_ON) && (CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_MICROSAR_VERSION == CAN_MSR30)
    canApiContext = CAN_INITCTR_ID;
#endif
/* --- Init global data --- */
#if (CAN_MICROSAR_VERSION == CAN_MSR40)
    lastInitObject[channel] = (uint8)((uint8)CAN_INIT_OBJ_START_IDX[channel] + (uint8)*Config); /* SBSW_CAN_HL25 */
#endif
    initObject = lastInitObject[channel];
#if defined( C_ENABLE_CAN_RAM_CHECK )
    canRamCheckStatus = kCanRamCheckOk;
#endif
    {
#if defined(CAN_ENABLE_SELECTABLE_PB)
      canControllerConfigPtr[canHwChannel] = &CAN_CONTROLLER_CONFIG_INIT[canHwChannel]; /* SBSW_CAN_HL24 */
#else
# if (CAN_DEV_ERROR_DETECT == STD_ON)
      canControllerConfigPtr[canHwChannel] = &CanControllerConfig[canHwChannel]; /* SBSW_CAN_HL24 */
# endif
#endif
      #if defined( V_ENABLE_USE_DUMMY_STATEMENT )
      lastInitObject[channel] = lastInitObject[channel];  /* dummy assignment to avoid compiler warning */ /* SBSW_CAN_LL010 */
      #endif
      
      unused_init_flag = 0;
      
      
      # if defined( C_ENABLE_SLEEP_WAKEUP )
      STATUS_SLEEP(channel) = kCanFalse; /* SBSW_CAN_LL006 */
      # endif
      
      CanSetPointerToCanHardware;
      
      #if defined( C_ENABLE_DCAN_ISSUE22_WORKAROUND )
      tmpCNTRLREG = CNTRLREG;
      #endif
      
      /* set CAN-cell into Initmode */
      #if defined(C_ENABLE_DONT_CHANGE_CNTRLREG_SETTINGS)
      CNTRLREG |= kSetInit; /* SBSW_CAN_LL004 */
      #else
      CNTRLREG = kSetInit | kSetPMD; /* SBSW_CAN_LL004 */
      #endif
      
      #if defined( C_ENABLE_DCAN_ISSUE22_WORKAROUND )
      if((tmpCNTRLREG & kSetInit) == 0)
      {
        /* neither power-on nor bus-off did occur -> DCAN#22 issue workaround is necessary */
        /* according to the erratum the CAN interrupts have to locked at this point */
      
        /* wait into the loop at least 6 CAN clock cycles */
        nbOfIterations = CAN_GLOBAL_CONFIG(CanErrata22Iterations);
        while(nbOfIterations > 0)
        {
          nbOfIterations--;
          asm(" nop"); /* SBSW_CAN_LL011 */
          asm(" nop"); /* SBSW_CAN_LL011 */
          asm(" nop"); /* SBSW_CAN_LL011 */
          asm(" nop"); /* SBSW_CAN_LL011 */
          asm(" nop"); /* SBSW_CAN_LL011 */
          asm(" nop"); /* SBSW_CAN_LL011 */
        }
      
        CNTRLREG |= kSetSWR;   /* software reset */ /* SBSW_CAN_LL004 */
      
      #if defined(C_ENABLE_DONT_CHANGE_CNTRLREG_SETTINGS)
        CNTRLREG &= ~(kSetPMD); /* SBSW_CAN_LL004 */
        CNTRLREG |= (tmpCNTRLREG & kSetPMD); /* SBSW_CAN_LL004 */
      #else
        CNTRLREG |= kSetPMD; /* SBSW_CAN_LL004 */
      #endif
      
      }
      #endif
      
      /* allow CCE to write in the Configregister and configure wakeup */
      CNTRLREG |= (kSetCCE | kSetWUBA); /* SBSW_CAN_LL004 */
      
      /* clear Statregister and Testregister */ 
      CAN_LL_STATUS(channel) = 0; /* SBSW_CAN_LL006 */
      TESTREG  = kClearAll; /* SBSW_CAN_LL004 */
      
      /* init Bit-Timing with user-generated Data */ 
      BITTIMING = CanInitBitTiming[initObject]; /* SBSW_CAN_LL004 */
      
      /* init Baud Rate Prescaler Extension with user-generated Data */
      BRP_REG = CanInitBRP_Reg[initObject]; /* SBSW_CAN_LL004 */
      
      
      { 
#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
/* --- Init Full CAN Tx --- */
        for (Htrh = CAN_CONTROLLER_CONFIG(canHwChannel).TxFullHandleStart; Htrh < CAN_CONTROLLER_CONFIG(canHwChannel).TxFullHandleStop; Htrh++)
        {
          hwObjHandle = CAN_MAILBOX[Htrh].HwHandle;
          logTxObjHandle = (CanObjectHandle)(hwObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(channel));
          CAN_ACTIVESEND_STATE(logTxObjHandle) = CANFREEOBJ; /* SBSW_CAN_HL09, SBSW_CM_CAN_HL55 */
          DO_CAN_RAM_CHECK(hwObjHandle); /* SBSW_CAN_HL30 */
          if(((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy))
          {
            APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
            do{
                CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
              } WHILE_CONDITON( ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy) );
          
            APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
          #if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
            if ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy)
            {
              canIsHardwareCanceled[channel] = TRUE;
            }
          #endif
          }
          
           /* WrRd,Mask,Arb,Control,DataA,DataB set */
            IF_INIT.ComMask        = kSetWrRd | kSetMask | kSetArb | kSetControl | kSetDataA | kSetDataB; /* SBSW_CAN_LL004 */
          
            /* ID=0,MsgVal,Dir set */
            IF_INIT.ArbitrFld2     = kSetMsgVal | kSetDir; /* SBSW_CAN_LL004 */
            IF_INIT.ArbitrFld1     = kClearAll; /* SBSW_CAN_LL004 */
          
          if(CAN_INDIV_POLLING(channel,hwObjHandle) != 0) /* PRQA S 3325 */ /* MD_Can_3325_LL */
          {                                               /* PRQA S 3201 */ /* MD_Can_3201_LL */
          IF_INIT.MessageCntrl   = kSetEoB; /* EoB set */ /* SBSW_CAN_LL004 */
          }
          else
          {
          IF_INIT.MessageCntrl   = kSetEoB |  kSetEnableTxCanInt; /* EoB,TxIE set */ /* SBSW_CAN_LL004 */
          }
            
            /* Mask and Data=0, MDir set */ 
            IF_INIT.Mask1          = kClearAll; /* SBSW_CAN_LL004 */
            IF_INIT.Mask2          = kSetMDir; /* SBSW_CAN_LL004 */
            IF_INIT.Data.ulData[0] = kClearAll32; /* SBSW_CAN_LL004 */
            IF_INIT.Data.ulData[1] = kClearAll32; /* SBSW_CAN_LL004 */
          
          /* start copy data from IFx to ObjectRAM */
          /* first address of Objekt in CAN-Cell starts with 1 ! */
          IF_INIT.ComRequest     = hwObjHandle + 1; /* SBSW_CAN_LL004 */
          
          
# if ( CAN_DYNAMIC_FULLCAN_ID == STD_OFF ) /* if needed the init of id,dlc and type is done in InitTxObj to avoid problems with uninit registers */
#  if ( CAN_EXTENDED_ID == STD_ON)
#   if ( CAN_MIXED_ID == STD_ON)
          if ( (CAN_MAILBOX[Htrh].IDValue & CAN_EXTENDED_ID_MASK) != CAN_EXTENDED_ID_MASK)
          {
            # if defined( C_ENABLE_EXTENDED_ID )
            TX_MSGOBJ_ID_LOW(logTxObjHandle)  = (vuint16)MK_STDID1(CAN_MAILBOX[Htrh].IDValue); /* SBSW_CAN_LL015 */
            # endif  
            TX_MSGOBJ_ID_HIGH(logTxObjHandle) = (vuint16)MK_STDID0(CAN_MAILBOX[Htrh].IDValue) | kSetMsgVal | kSetDir; /* SBSW_CAN_LL015 */
            TX_MSGOBJ_DLC(logTxObjHandle) = MK_TX_DLC(CAN_MAILBOX[Htrh].DLC_FIFO); /* SBSW_CAN_LL015 */
            
          }
          else
#   endif
          {
            # if defined( C_ENABLE_EXTENDED_ID )
            TX_MSGOBJ_ID_LOW(logTxObjHandle)  = (vuint16)MK_EXTID1(CAN_MAILBOX[Htrh].IDValue); /* SBSW_CAN_LL015 */
            # endif  
            TX_MSGOBJ_ID_HIGH(logTxObjHandle) = (vuint16)MK_EXTID0(CAN_MAILBOX[Htrh].IDValue) | kSetMsgVal | kSetDir; /* SBSW_CAN_LL015 */
            TX_MSGOBJ_DLC(logTxObjHandle) = MK_TX_DLC_EXT(CAN_MAILBOX[Htrh].DLC_FIFO); /* SBSW_CAN_LL015 */
            
          }
#  else
          # if defined( C_ENABLE_EXTENDED_ID )
          TX_MSGOBJ_ID_LOW(logTxObjHandle)  = (vuint16)MK_STDID1(CAN_MAILBOX[Htrh].IDValue); /* SBSW_CAN_LL015 */
          # endif  
          TX_MSGOBJ_ID_HIGH(logTxObjHandle) = (vuint16)MK_STDID0(CAN_MAILBOX[Htrh].IDValue) | kSetMsgVal | kSetDir; /* SBSW_CAN_LL015 */
          TX_MSGOBJ_DLC(logTxObjHandle) = MK_TX_DLC(CAN_MAILBOX[Htrh].DLC_FIFO); /* SBSW_CAN_LL015 */
          
#  endif
# endif
        }
#endif
/* --- Init Basic CAN Tx --- */
        {
          CanObjectHandle endlogTxObjHandle;
          hwObjHandle = CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel);
          endlogTxObjHandle = (CanObjectHandle)((CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(channel)) + CAN_MULTIPLEXED_TX_MAX);
          for (logTxObjHandle = (CanObjectHandle)(hwObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(channel)); logTxObjHandle < endlogTxObjHandle; logTxObjHandle++)
          {
            CAN_ACTIVESEND_STATE(logTxObjHandle) = CANFREEOBJ; /* SBSW_CAN_HL09 */
            DO_CAN_RAM_CHECK(hwObjHandle); /* SBSW_CAN_HL30 */
            if(((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy))
            {
              APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
            
              do{
                  CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
            
                } WHILE_CONDITON( ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy) );
            
              APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
            
            #if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
              if ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy)
              {
                canIsHardwareCanceled[channel] = TRUE;
              }
            #endif
            }
            
             /* WrRd,Mask,Arb,Control,DataA,DataB set */
              IF_INIT.ComMask        = kSetWrRd | kSetMask | kSetArb | kSetControl | kSetDataA | kSetDataB; /* SBSW_CAN_LL004 */
            
              /* ID=0,MsgVal,Dir set */
              IF_INIT.ArbitrFld2     = kSetMsgVal | kSetDir; /* SBSW_CAN_LL004 */
              IF_INIT.ArbitrFld1     = kClearAll; /* SBSW_CAN_LL004 */
            
            if(CAN_INDIV_POLLING(channel,hwObjHandle) != 0) /* PRQA S 3325 */ /* MD_Can_3325_LL */
            {                                               /* PRQA S 3201 */ /* MD_Can_3201_LL */
            IF_INIT.MessageCntrl   = kSetEoB; /* EoB set */ /* SBSW_CAN_LL004 */
            }
            else
            {
            IF_INIT.MessageCntrl   = kSetEoB |  kSetEnableTxCanInt; /* EoB,TxIE set */ /* SBSW_CAN_LL004 */
            }
              
              /* Mask and Data=0, MDir set */ 
              IF_INIT.Mask1          = kClearAll; /* SBSW_CAN_LL004 */
              IF_INIT.Mask2          = kSetMDir; /* SBSW_CAN_LL004 */
              IF_INIT.Data.ulData[0] = kClearAll32; /* SBSW_CAN_LL004 */
              IF_INIT.Data.ulData[1] = kClearAll32; /* SBSW_CAN_LL004 */
            
            /* start copy data from IFx to ObjectRAM */
            /* first address of Objekt in CAN-Cell starts with 1 ! */
            IF_INIT.ComRequest     = hwObjHandle + 1; /* SBSW_CAN_LL004 */
            
            hwObjHandle++;
          }
        }
      } /* Common CAN:  Tx only on first hwChannel */
/* --- Init Unused Mailboxes --- */
      for (Htrh = CAN_CONTROLLER_CONFIG(canHwChannel).UnusedHandleStart; Htrh < CAN_CONTROLLER_CONFIG(canHwChannel).UnusedHandleStop; Htrh++)
      {
        for (hwObjHandle = CAN_MAILBOX[Htrh].HwHandle; hwObjHandle < (Can_HwHandleType)(CAN_MAILBOX[Htrh].HwHandle + CAN_MAILBOX[Htrh].DLC_FIFO); hwObjHandle++)
        {
          if(((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy))
          {
            APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
            do{
                CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
              } WHILE_CONDITON( ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy) );
          
            APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
          #if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
            if ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy)
            {
              canIsHardwareCanceled[channel] = TRUE;
            }
          #endif
          }
          /* all interface registers will initialized once for initialization of unused msg.objects -> see ESCAN00072400 */
          if(unused_init_flag == 0)
          {
            /* Mask,Arb,Control,DataA,DataB set */
            IF_INIT.ComMask        = kSetWrRd | kSetMask | kSetArb | kSetControl | kSetDataA | kSetDataB; /* SBSW_CAN_LL004 */
          
            /* Unused MsgObjekt => MsgVal=0 */  
            IF_INIT.ArbitrFld1     = kClearAll; /* SBSW_CAN_LL004 */
            IF_INIT.ArbitrFld2     = kClearAll; /* SBSW_CAN_LL004 */
          
            /* Mask and Data=0 */ 
            IF_INIT.Mask1          = kClearAll; /* SBSW_CAN_LL004 */
            IF_INIT.Mask2          = kClearAll; /* SBSW_CAN_LL004 */
            IF_INIT.Data.ulData[0] = kClearAll32; /* SBSW_CAN_LL004 */
            IF_INIT.Data.ulData[1] = kClearAll32; /* SBSW_CAN_LL004 */
          
            IF_INIT.MessageCntrl   = kSetEoB; /* SBSW_CAN_LL004 */
            
            unused_init_flag = 1;
          }
          
          /* start copy data from IFx to ObjectRAM */
          /* first address of Objekt in CAN-Cell starts with 1 ! */
          IF_INIT.ComRequest     = hwObjHandle + 1; /* SBSW_CAN_LL004 */
          
        }
      }
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* --- Init Full CAN Rx --- */
      for (Htrh = CAN_CONTROLLER_CONFIG(canHwChannel).RxFullHandleStart; Htrh < CAN_CONTROLLER_CONFIG(canHwChannel).RxFullHandleStop; Htrh++)
      {
        hwObjHandle=CAN_MAILBOX[Htrh].HwHandle;
        DO_CAN_RAM_CHECK(hwObjHandle); /* SBSW_CAN_HL30 */
# if ( CAN_EXTENDED_ID == STD_ON)
#  if ( CAN_MIXED_ID == STD_ON)
        if ( (CAN_MAILBOX[Htrh].IDValue & CAN_EXTENDED_ID_MASK) != CAN_EXTENDED_ID_MASK)
        {
          if(((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy))
          {
            APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
            do{
                CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
              } WHILE_CONDITON( ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy) );
          
            APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
          #if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
            if ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy)
            {
              canIsHardwareCanceled[channel] = TRUE;
            }
          #endif
          }
          
          
          /* WrRd,Mask,Arb,Control,DataA,DataB set */
          IF_INIT.ComMask        = kSetWrRd | kSetMask | kSetArb | kSetControl | kSetDataA | kSetDataB; /* SBSW_CAN_LL004 */
          
          /* ID=0,Dir=0,MsgVal */
          #if defined( C_ENABLE_EXTENDED_ID )
          IF_INIT.ArbitrFld1     = (vuint16)(MK_STDID1(CAN_MAILBOX[Htrh].IDValue)); /* SBSW_CAN_LL004 */
          #endif  
          IF_INIT.ArbitrFld2     = kSetMsgVal | (vuint16)(MK_STDID0(CAN_MAILBOX[Htrh].IDValue)); /* SBSW_CAN_LL004 */
          
          IF_INIT.Mask1          = kClearAll; /* SBSW_CAN_LL004 */
          IF_INIT.Mask2          = kSetMXtd | kSetMDir; /* SBSW_CAN_LL004 */
          
          /* EoB,RxIE,DLC set */
          if(CAN_INDIV_POLLING(channel,hwObjHandle) != 0) /* PRQA S 3325 */ /* MD_Can_3325_LL */
          {                                               /* PRQA S 3201 */ /* MD_Can_3201_LL */
            IF_INIT.MessageCntrl   = kSetEoB; /* SBSW_CAN_LL004 */
          }
          else
          {
            IF_INIT.MessageCntrl   = kSetEoB | kSetEnableRxFullCanInt; /* SBSW_CAN_LL004 */
          }
          
             
          /* Data=0 */
          IF_INIT.Data.ulData[0] = kClearAll32; /* SBSW_CAN_LL004 */
          IF_INIT.Data.ulData[1] = kClearAll32; /* SBSW_CAN_LL004 */
          
          assertGen( hwObjHandle >= CAN_HL_HW_RX_FULL_STARTINDEX(channel), channel, kErrorToManyFullCanObjects); /* SBSW_CAN_LL005 */
          
          /* start copy data from IFx to ObjectRAM */
          /* first address of Objekt in CAN-Cell starts with 1 ! */
          IF_INIT.ComRequest     = hwObjHandle + 1; /* SBSW_CAN_LL004 */
          
        }
        else
#  endif
        {
          if(((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy))
          {
            APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
            do{
                CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
              } WHILE_CONDITON( ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy) );
          
            APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
          #if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
            if ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy)
            {
              canIsHardwareCanceled[channel] = TRUE;
            }
          #endif
          }
          
          
          /* WrRd,Mask,Arb,Control,DataA,DataB set */
          IF_INIT.ComMask        = kSetWrRd | kSetMask | kSetArb | kSetControl | kSetDataA | kSetDataB; /* SBSW_CAN_LL004 */
          
          /* ID=0,Dir=0,MsgVal */
          #if defined( C_ENABLE_EXTENDED_ID )
          IF_INIT.ArbitrFld1     = (vuint16)(MK_EXTID1(CAN_MAILBOX[Htrh].IDValue)); /* SBSW_CAN_LL004 */
          #endif  
          IF_INIT.ArbitrFld2     = kSetMsgVal | (vuint16)(MK_EXTID0(CAN_MAILBOX[Htrh].IDValue)); /* SBSW_CAN_LL004 */
          
          IF_INIT.Mask1          = kClearAll; /* SBSW_CAN_LL004 */
          IF_INIT.Mask2          = kSetMXtd | kSetMDir; /* SBSW_CAN_LL004 */
          
          /* EoB,RxIE,DLC set */
          if(CAN_INDIV_POLLING(channel,hwObjHandle) != 0) /* PRQA S 3325 */ /* MD_Can_3325_LL */
          {                                               /* PRQA S 3201 */ /* MD_Can_3201_LL */
            IF_INIT.MessageCntrl   = kSetEoB; /* SBSW_CAN_LL004 */
          }
          else
          {
            IF_INIT.MessageCntrl   = kSetEoB | kSetEnableRxFullCanInt; /* SBSW_CAN_LL004 */
          }
          
             
          /* Data=0 */
          IF_INIT.Data.ulData[0] = kClearAll32; /* SBSW_CAN_LL004 */
          IF_INIT.Data.ulData[1] = kClearAll32; /* SBSW_CAN_LL004 */
          
          assertGen( hwObjHandle >= CAN_HL_HW_RX_FULL_STARTINDEX(channel), channel, kErrorToManyFullCanObjects); /* SBSW_CAN_LL005 */
          
          /* start copy data from IFx to ObjectRAM */
          /* first address of Objekt in CAN-Cell starts with 1 ! */
          IF_INIT.ComRequest     = hwObjHandle + 1; /* SBSW_CAN_LL004 */
          
        }
# else
        if(((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy))
        {
          APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
        
          do{
              CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
        
            } WHILE_CONDITON( ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy) );
        
          APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
        
        #if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
          if ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy)
          {
            canIsHardwareCanceled[channel] = TRUE;
          }
        #endif
        }
        
        
        /* WrRd,Mask,Arb,Control,DataA,DataB set */
        IF_INIT.ComMask        = kSetWrRd | kSetMask | kSetArb | kSetControl | kSetDataA | kSetDataB; /* SBSW_CAN_LL004 */
        
        /* ID=0,Dir=0,MsgVal */
        #if defined( C_ENABLE_EXTENDED_ID )
        IF_INIT.ArbitrFld1     = (vuint16)(MK_STDID1(CAN_MAILBOX[Htrh].IDValue)); /* SBSW_CAN_LL004 */
        #endif  
        IF_INIT.ArbitrFld2     = kSetMsgVal | (vuint16)(MK_STDID0(CAN_MAILBOX[Htrh].IDValue)); /* SBSW_CAN_LL004 */
        
        IF_INIT.Mask1          = kClearAll; /* SBSW_CAN_LL004 */
        IF_INIT.Mask2          = kSetMXtd | kSetMDir; /* SBSW_CAN_LL004 */
        
        /* EoB,RxIE,DLC set */
        if(CAN_INDIV_POLLING(channel,hwObjHandle) != 0) /* PRQA S 3325 */ /* MD_Can_3325_LL */
        {                                               /* PRQA S 3201 */ /* MD_Can_3201_LL */
          IF_INIT.MessageCntrl   = kSetEoB; /* SBSW_CAN_LL004 */
        }
        else
        {
          IF_INIT.MessageCntrl   = kSetEoB | kSetEnableRxFullCanInt; /* SBSW_CAN_LL004 */
        }
        
           
        /* Data=0 */
        IF_INIT.Data.ulData[0] = kClearAll32; /* SBSW_CAN_LL004 */
        IF_INIT.Data.ulData[1] = kClearAll32; /* SBSW_CAN_LL004 */
        
        assertGen( hwObjHandle >= CAN_HL_HW_RX_FULL_STARTINDEX(channel), channel, kErrorToManyFullCanObjects); /* SBSW_CAN_LL005 */
        
        /* start copy data from IFx to ObjectRAM */
        /* first address of Objekt in CAN-Cell starts with 1 ! */
        IF_INIT.ComRequest     = hwObjHandle + 1; /* SBSW_CAN_LL004 */
        
# endif
      }
#endif
#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* --- Init Basic CAN Rx --- */
      for (Htrh = CAN_CONTROLLER_CONFIG(canHwChannel).RxBasicHandleStart; Htrh < CAN_CONTROLLER_CONFIG(canHwChannel).RxBasicHandleStop; Htrh++)
      {
        for (hwObjHandle = CAN_MAILBOX[Htrh].HwHandle; hwObjHandle < (Can_HwHandleType)(CAN_MAILBOX[Htrh].HwHandle + CAN_MAILBOX[Htrh].DLC_FIFO); hwObjHandle++)
        {
          DO_CAN_RAM_CHECK(hwObjHandle); /* SBSW_CAN_HL30 */
          if(((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy))
          {
            APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
            do{
                CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
              } WHILE_CONDITON( ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy) );
          
            APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
          
          #if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API == STD_ON)
            if ((IF_INIT.ComRequest & kIFxBusy) == kIFxBusy)
            {
              canIsHardwareCanceled[channel] = TRUE;
            }
          #endif
          }
          
          
          /* WrRd,Mask,Arb,Control,DataA,DataB set */
          IF_INIT.ComMask     =  kSetWrRd | kSetMask | kSetArb | kSetControl | kSetDataA | kSetDataB; /* SBSW_CAN_LL004 */
          
          /* same mask, code table for ASR and HLL */
          
          IF_INIT.ArbitrFld1  =  CanInitBasicCod1[initObject][(((vuint8)(hwObjHandle - CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel))) & (vuint8)0xFE)>>1];
          IF_INIT.ArbitrFld2  =  CanInitBasicCod2[initObject][(((vuint8)(hwObjHandle - CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel))) & (vuint8)0xFE)>>1] | kSetMsgVal;
          IF_INIT.Mask1       =  CanInitBasicMsk1[initObject][(((vuint8)(hwObjHandle - CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel))) & (vuint8)0xFE)>>1];
          IF_INIT.Mask2       =  CanInitBasicMsk2[initObject][(((vuint8)(hwObjHandle - CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel))) & (vuint8)0xFE)>>1] | kSetMDir;                        
                                     
          if((hwObjHandle & 0x0001) == 0)
          {
            if(CAN_INDIV_POLLING(channel,hwObjHandle) != 0) /* PRQA S 3325 */ /* MD_Can_3325_LL */
            {                                               /* PRQA S 3201 */ /* MD_Can_3201_LL */
              IF_INIT.MessageCntrl = kSetUMask;
            }
            else
            {
              IF_INIT.MessageCntrl = kSetUMask | kSetEnableRxBasicCanInt;
            }
          
          }
          else
          {
            if(CAN_INDIV_POLLING(channel,hwObjHandle) != 0) /* PRQA S 3325 */ /* MD_Can_3325_LL */
            {                                               /* PRQA S 3201 */ /* MD_Can_3201_LL */
              IF_INIT.MessageCntrl = kSetUMask | kSetEoB;
            }
            else
            {
              IF_INIT.MessageCntrl = kSetUMask | kSetEoB | kSetEnableRxBasicCanInt;
            }
          }
          
          
          
          /* start copy data from IFx to ObjectRAM */
          /* first address of Objekt in CAN-Cell starts with 1 ! */
          IF_INIT.ComRequest  =  hwObjHandle + 1; /* SBSW_CAN_LL004 */
                
        }
      }
#endif
      
      #if defined (C_COMP_TI_TMS470_DCAN) 
      # if defined( C_ENABLE_VIM_ACCESS_BY_DRIVER )
      #  if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
              (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
              !defined( C_ENABLE_TX_POLLING )        || \
              !defined( C_ENABLE_ERROR_POLLING )     || \
              !defined( C_ENABLE_WAKEUP_POLLING ))
      if((canStatus[canHwChannel] & CAN_STATUS_INIT) == 0)
      {
          *VIM_SETMASK(canHwChannel) = INTERRUPT_SRC(canHwChannel); /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */  /* PRQA S 0306 */ /* MD_Can_0306_HWaccess */ /* SBSW_CAN_LL013 */
      }
      #  endif
      # endif
      #endif
      
      #if defined( C_ENABLE_RX_BASICCAN_POLLING ) && defined( C_ENABLE_RX_FULLCAN_POLLING ) && \
          defined( C_ENABLE_TX_POLLING )          && defined( C_ENABLE_ERROR_POLLING )      && \
          defined( C_ENABLE_WAKEUP_POLLING )
      NORMAL_MODE(channel) = kSetEnableErrorInt | kSetWUBA | kSetPMD; /* SBSW_CAN_LL006 */
      #else
      NORMAL_MODE(channel) = kSetEnableErrorInt | kSetWUBA | kSetPMD | kSetIE ; /* SBSW_CAN_LL006 */
      #endif    
      
      
      
      canStatus[channel] &= (uint8)(CAN_STATUS_INIT | CAN_STATUS_SLEEP | CAN_DEACTIVATE_CONTROLLER);  /* clean up (do not activate communication and let sleep and init to detect ram-check request) */ /* SBSW_CAN_HL02 */

      /* CAN259, CAN260 */
#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
      /* BusOff, Wakeup and Re-Init lead direct to stop mode, otherwise it is only a re-init with transition afterwards. */
      if ( (canStatusReq[channel] & CAN_STATUS_SETMODE) != CAN_STATUS_SETMODE )
      {
        canStatusReq[channel] = CAN_STATUS_UNINIT; /* no more polling or notification, BusOff, Wakeup notified before otherwise Re-Init only allowed in Stop mode */ /* SBSW_CAN_HL04 */
#else
      {
#endif
        STATUS_STOP_MODE(channel) = kSetStopMode; /* SBSW_CAN_LL006 */
        canStatus[channel] |= (CAN_STATUS_STOP);  /* set stop */ /* SBSW_CAN_HL02 */
      }
    } /* end of loop over all hw channels */
#if defined( C_ENABLE_CAN_RAM_CHECK )
    if( ((canStatus[channel] & CAN_STATUS_INIT) != CAN_STATUS_INIT ) ||  /* PowerOn */
        ((canStatus[channel] & CAN_STATUS_SLEEP) == CAN_STATUS_SLEEP )   /* Wakeup */  )
    {
      if( canRamCheckStatus == kCanRamCheckFailed )
      {
        if (Appl_CanRamCheckFailed((uint8)channel) == CAN_DEACTIVATE_CONTROLLER) /* let the application decide if communication is disabled */ /* SBSW_CAN_HL31 */
        {
          canStatus[channel] |= CAN_DEACTIVATE_CONTROLLER;    /* Application decise to deactivate communication in case RAM_CHECK failed */ /* SBSW_CAN_HL02 */
        }
        else
        {
          canStatus[channel] &= (uint8)(~(CAN_DEACTIVATE_CONTROLLER)); /* Application decise to activate communication in case RAM_CHECK failed */  /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
        }
      }
      else
      {
        canStatus[channel] &= (uint8)(~(CAN_DEACTIVATE_CONTROLLER)); /* Re-activate communication in case no RAM_CHECK failed */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
      }
    }
#endif    
    canStatus[channel] |= (CAN_STATUS_INIT);  /* set Init */ /* SBSW_CAN_HL02 */
#if defined (C_ENABLE_SLEEP_WAKEUP)
    if (canIsWakeup[channel] == TRUE) /* CAN443 */
    {
      canIsWakeup[channel] = FALSE; /* SBSW_CAN_HL20 */
      EcuM_SetWakeupEvent(CanWakeupSourceRef[channel]); /* CAN461 */ /* SBSW_CAN_HL21 */
    }
#endif
  } /* controller active in Multiple ECU config */
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
# if (CAN_MICROSAR_VERSION != CAN_MSR40)
  ControllerConfigPtr = ControllerConfigPtr; /* dummy assignment -> avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON )
  Controller = Controller;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
#endif
  CanHookEnd_Can_InitController();
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/* CAN230, CAN017, CAN294, CAN196, CAN197, CAN201, CAN425, CAN426 */
/****************************************************************************
| NAME:             Can_SetControllerMode
| CALLED BY:        CanInterface
| PRECONDITIONS:    none
| INPUT PARAMETERS: Controller number, transition to next mode
| RETURN VALUES:    CAN_OK, CAN_NOT_OK
| DESCRIPTION:      change Controller mode / CanIf enter critical section before (locked interrupts)
|                   (possible values: CAN_T_START, CAN_T_STOP, CAN_T_SLEEP, CAN_T_WAKEUP)
****************************************************************************/
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition )
{
  Can_ReturnType transitionRequest;
  Can_ReturnType transitionDone;
  Can_ReturnType retval;
  retval = CAN_NOT_OK;  /* CAN089 For sucessfull transtions it is set explicite to CAN_OK*/

  CanHookBegin_Can_SetControllerMode();
#if defined ( C_ENABLE_MULTI_ECU_CONFIG ) /* move below channel det-check */
  if ( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  { /* inactive Controller ... nothing to do here */
    return retval;
  }
#endif
  {
  /* CAN248 */
    Can_CheckDetErrorReturnValue((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_SETCTR_ID, CAN_E_UNINIT, CAN_NOT_OK); /* CAN198 */ /* SBSW_CAN_HL06 */
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
    Can_SilentBswCheckErrorReturnValue((channel < kCanNumberOfChannels), CAN_SETCTR_ID, CAN_E_PARAM_CONTROLLER, CAN_NOT_OK); /* CAN199 */ /* SBSW_CAN_HL06, SBSW_CM_CAN_HL01 */
#endif
  /* CAN248 */
    Can_CheckDetErrorReturnValue((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_SETCTR_ID, CAN_E_UNINIT, CAN_NOT_OK); /* SBSW_CAN_HL06 */
#if ( CAN_TRANSITION_CHECK == STD_ON )  /* ASR4 extension SREQ00000291 */
  /* CAN409 */ /* No-Stop -> Start is invalid */
    Can_CheckDetErrorReturnValue(((CanHL_IsStop(channel)) || (Transition != CAN_T_START)), CAN_SETCTR_ID, CAN_E_TRANSITION, CAN_NOT_OK); /* SBSW_CAN_HL06 */
  /* CAN411, CAN412 */ /* No Stop Nor Sleep -> Sleep   or   No Sleep Nor Stop --> Wakeup   is invalid */
    Can_CheckDetErrorReturnValue(( (CanHL_IsStop(channel)) || (CanHL_IsSleep(channel)) ||
            ((Transition != CAN_T_WAKEUP) && (Transition != CAN_T_SLEEP)) ),
             CAN_SETCTR_ID, CAN_E_TRANSITION, CAN_NOT_OK); /* SBSW_CAN_HL06 */
  /* CAN410 */ /* No Start Nor Stop -> Stop is invalid */
    Can_CheckDetErrorReturnValue(( (!CanHL_IsSleep(channel)) || (Transition != CAN_T_STOP) ),
                                 CAN_SETCTR_ID, CAN_E_TRANSITION, CAN_NOT_OK); /* SBSW_CAN_HL06 */
#endif
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_6); /* SBSW_CAN_HL11 */
#if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API != STD_ON) && (CAN_DEV_TIMEOUT_DETECT == STD_ON) && (CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_MICROSAR_VERSION == CAN_MSR30)
    canApiContext = CAN_SETCTR_ID;
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
    canIsHardwareCanceled[channel] = FALSE; /* SBSW_CAN_HL32 */
#endif
#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
    canStatusReq[channel] |= CAN_STATUS_SETMODE; /* mark ongoing state change (suppress stop transition in Can_InitController) */ /* SBSW_CAN_HL04 */
#endif
    {
      switch(Transition)
      {
/* --------------------- CAN_T_START --------------------- */
      case CAN_T_START:
        retval = CAN_OK;
        transitionDone = CAN_OK;
#if (CAN_BUSOFF_SUPPORT_API == STD_OFF)
        if (canIsBusOff[channel] == TRUE)
        {
          canIsBusOff[channel] = FALSE; /* no more busoff */ /* SBSW_CAN_HL17 */ /* do this before CanResetBusOffEnd() so LL may overwrite it */
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
          CanResetBusOffEnd(channel, lastInitObject[channel]); /* SBSW_CAN_HL18 */
# else
          CanResetBusOffEnd(lastInitObject[channel]); /* SBSW_CAN_HL18 */
# endif
        }
        else /* do not reinit after busoff, this will be done while CanResetBusOffx() */
#endif
        {
#if ( CAN_REINIT_START == STD_ON ) /* additional to stop-transition-reinit */
          /* CAN384 */
# if (CAN_MICROSAR_VERSION == CAN_MSR40)
          Can_InitController((uint8)channel, &Can_ControllerBaudrateConfig[((uint8)(lastInitObject[channel] - (uint8)CAN_INIT_OBJ_START_IDX[channel]) & 0x03u)]); /* SBSW_CAN_HL07 */
# else
          Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL07 */
# endif
#endif
        }
/* --- CAN_T_START: set request and wait limited time --- */
        {
          /* CAN261 */
          {
            vuint8 index;
            CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
            CanSetPointerToCanHardware;
          
            CNTRLREG = NORMAL_MODE(channel); /* SBSW_CAN_LL004 */
            CAN_LL_STATUS(channel) = kCanFalse; /* SBSW_CAN_LL006 */
            STATUS_STOP_MODE(channel) = kCanFalse; /* SBSW_CAN_LL006 */
            STATUS_BUS_OFF(channel) = kCanFalse; /* SBSW_CAN_LL006 */
          
            for ( index = 0; index < 4; index++ )
            {
              TX_SEND_FLAG(channel, index) = 0; /* SBSW_CAN_LL014 */
            }
          
            transitionRequest = kCanOk; 
          }
          if ( transitionRequest == CAN_NOT_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
          { /* PRQA S 3201 */ /* MD_Can_3201 */
            retval = CAN_NOT_OK;
            transitionDone = CAN_NOT_OK; /* at least one HW channel is not in new state (CAN_MSR40: poll later) */
          }
        } /* loop canHwChannel */
#if defined(C_ENABLE_HW_LOOP_TIMER)
        if (( transitionDone == CAN_OK ) && ( canIsHardwareCanceled[channel] == FALSE )) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
#else
        if ( transitionDone == CAN_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
#endif
        { /* PRQA S 3201 */ /* MD_Can_3201 */
          CanHookStateChange_StartSync(canStatus[channel], (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_STOP))) | CAN_STATUS_START) ); /* PRQA S 0277 */ /* MD_Can_0277_negation */
          canStatus[channel] = (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_STOP))) | CAN_STATUS_START); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
          canStatusReq[channel] &= (uint8)(~(CAN_STATUS_SETMODE)); /* allow reinit in notification */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL04 */
          /* CAN234 */
          CanIf_ControllerModeIndication( (uint8)channel, CANIF_CS_STARTED ); /* SBSW_CAN_HL01 */
#endif
        }
        break;

/* ---------------------- CAN_T_STOP -------------------- */
      case CAN_T_STOP:
        if (canIsBusOff[channel] == FALSE)          /* ESCAN00032291: no call of STOP inside busoff (avoid blocking) */
        {
          retval = CAN_OK;
          transitionDone = CAN_OK;
# if (CAN_MICROSAR_VERSION == CAN_MSR40)
          Can_InitController((uint8)channel, &Can_ControllerBaudrateConfig[((uint8)(lastInitObject[channel] - (uint8)CAN_INIT_OBJ_START_IDX[channel]) & 0x03u)]); /* SBSW_CAN_HL07 */
# else
          Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL07 */
# endif
#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403) 
/* --- CAN_T_STOP: set request and wait limited time --- */
          {
            /* CAN263 */
            
            vuint8 index;
             
            /*reset swr_flag_request */
            for ( index = 0; index < 4; index++ )
            {
              TX_SEND_FLAG(channel, index) = 0;
            }
            
            STATUS_STOP_MODE(channel) = kSetStopMode;
            transitionRequest = kCanOk;
            
            if ( transitionRequest == CAN_NOT_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
            { /* PRQA S 3201 */ /* MD_Can_3201 */
              retval = CAN_NOT_OK;
              transitionDone = CAN_NOT_OK; /* at least one HW channel is not in new state (CAN_MSR40: poll later) */
            }
          } /* loop canHwChannel */
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
          if (( transitionDone == CAN_OK ) && ( canIsHardwareCanceled[channel] == FALSE )) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
#else
          if ( transitionDone == CAN_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
#endif
          { /* PRQA S 3201 */ /* MD_Can_3201 */
            CanHookStateChange_StopSync(canStatus[channel], (uint8)((canStatus[channel] & CAN_STATUS_INIT) | CAN_STATUS_STOP) );
            canStatus[channel] = (uint8)((canStatus[channel] & (CAN_STATUS_INIT | CAN_DEACTIVATE_CONTROLLER)) | CAN_STATUS_STOP); /* SBSW_CAN_HL02 */
#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
            canStatusReq[channel] &= (uint8)(~(CAN_STATUS_SETMODE)); /* allow reinit in notification */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL04 */
            /* CAN234 */
            CanIf_ControllerModeIndication( (uint8)channel, CANIF_CS_STOPPED ); /* SBSW_CAN_HL01 */
#endif
          }
        } /* canIsBusOff */
        break;

/* ------------------ CAN_T_WAKEUP -------------------- */
      case CAN_T_WAKEUP:
#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403) /* CAN048  does not appear in MSR30 (syncron) */
        if ( canStatusReq[channel] == CAN_STATUS_SLEEP ) /* not allowed while transition to sleep */ /* SBSW_CAN_HL04 */
        {
          retval = CAN_NOT_OK;
# if (CAN_DEV_ERROR_DETECT == STD_ON) /* CAN026, CAN028, CAN091, CAN082, CAN083 */
          Can_CallDetReportError(CAN_SETCTR_ID, CAN_E_TRANSITION); /* SBSW_CAN_HL06 */
# endif
          break; /* PRQA S 0771,3333 */ /* MD_Can_14.6 */
        }
#endif
#if defined( C_ENABLE_SLEEP_WAKEUP ) /* hardware is only in sleep when wakeup over bus is activate and supported */
        if (CanWakeupSourceRef[channel] != 0) /* otherwise emulated sleep */
        {
          retval = CAN_OK;
          transitionDone = CAN_OK;
          {
            #if (CAN_ENABLE_SLEEP_WAKEUP_GLOBAL == STD_ON)
            V_DEF_CONST(V_NONE, vuint32, AUTOMATIC) can_power_down_mask[3] = {0x03,0x0C,0x30};
            #endif
            
            CanDeclareGlobalInterruptOldStatus
            CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
            CanSetPointerToCanHardware;
            
            CanNestedGlobalInterruptDisable(); /* SBSW_CAN_LL002 */
            
            #if (CAN_ENABLE_SLEEP_WAKEUP_GLOBAL == STD_ON)
            *((V_DEF_P2VAR(V_NONE, vuint32, VAR_NOINIT, VAR_NOINIT)) 0xFFFFE0A4) |= can_power_down_mask[channel]; /* SBSW_CAN_LL016 */
            CNTRLREG                 = NORMAL_MODE(channel); /* SBSW_CAN_LL004 */
            STATUS_SLEEP(channel)    = kCanFalse; /* SBSW_CAN_LL006 */
            STATUS_BUS_OFF(channel)  = kCanFalse; /* SBSW_CAN_LL006 */
            transitionRequest        = kCanOk;
            #endif
            
            #if (CAN_ENABLE_SLEEP_WAKEUP_GLOBAL == STD_OFF)
            CNTRLREG &= ~(kSetPDR); /* SBSW_CAN_LL004 */
            transitionRequest            = kCanRequested;
            #endif
            
            CanNestedGlobalInterruptRestore(); /* SBSW_CAN_LL002 */
            
            if ( transitionRequest == CAN_NOT_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
            { /* PRQA S 3201 */ /* MD_Can_3201 */
              retval = CAN_NOT_OK;
              transitionDone = CAN_NOT_OK; /* at least one HW channel is not in new state (CAN_MSR40: poll later) */
            }
            if ( transitionRequest == CAN_REQUESTED ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
            { /* PRQA S 3201 */ /* MD_Can_3201 */
              CanHL_ApplCanTimerStart(kCanLoopWakeup); /* SBSW_CAN_HL33 */
              /* CAN268, CAN370, CAN371, CAN372 */
              do
              {
                #if (CAN_ENABLE_SLEEP_WAKEUP_GLOBAL == STD_OFF)
                CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
                CanSetPointerToCanHardware;
                
                if ( ((STATREG & kPDA) == kPDA) )
                {
                  transitionRequest = kCanFailed;
                }
                else
                {
                  CNTRLREG                 = NORMAL_MODE(channel); /* SBSW_CAN_LL004 */
                  STATUS_SLEEP(channel)    = kCanFalse; /* SBSW_CAN_LL006 */
                  transitionRequest        = kCanOk;
                }
                #endif
                
                CanHL_ApplCanTimerLoop(kCanLoopWakeup); /* SBSW_CAN_HL33 */
              } while ( transitionRequest != CAN_OK );
              CanHL_ApplCanTimerEnd(kCanLoopWakeup); /* SBSW_CAN_HL33 */
              if ( transitionRequest != CAN_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
              { /* PRQA S 3201 */ /* MD_Can_3201 */
                transitionDone = CAN_NOT_OK; /* at least one HW channel is not in new state (CAN_MSR40: poll later) */
#  if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
                canStatusReq[channel] = CAN_STATUS_WAKEUP; /* Asyncron polling on */ /* SBSW_CAN_HL04 */
#  endif
#  if (CAN_MICROSAR_VERSION == CAN_MSR30)
                retval = CAN_NOT_OK;
#  endif
              }
            }
          } /* loop canHwChannel */
# if defined(C_ENABLE_HW_LOOP_TIMER)
          if ( (transitionDone == CAN_OK) && (canIsHardwareCanceled[channel] == FALSE) ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
# else
          if ( transitionDone == CAN_OK ) /* CAN_NOT_SUPPORTED is CAN_OK (stay in Stop mode instead) */  /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
# endif
          { /* PRQA S 3201 */ /* MD_Can_3201 */
            CanHookStateChange_WakeupSync(canStatus[channel], (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_SLEEP))) | CAN_STATUS_STOP) ); /* PRQA S 0277 */ /* MD_Can_0277_negation */
# if defined( C_ENABLE_CAN_RAM_CHECK )
#  if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
            canStatusReq[channel] &= (uint8)(~(CAN_STATUS_SETMODE)); /* remove mark ongoing state change (suppress stop transition in Can_InitController) */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL04 */
#  endif
#  if (CAN_MICROSAR_VERSION == CAN_MSR40)
            Can_InitController((uint8)channel, &Can_ControllerBaudrateConfig[((uint8)(lastInitObject[channel] - (uint8)CAN_INIT_OBJ_START_IDX[channel]) & 0x03u)]); /* SBSW_CAN_HL07 */
#  else
            Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL07 */
#  endif
# else
# endif
            canStatus[channel] = (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_SLEEP))) | CAN_STATUS_STOP); /* remove CAN_STATUS_SLEEP after Init call to force RAM_CHECK */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
# if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
            canStatusReq[channel] &= (uint8)(~(CAN_STATUS_SETMODE)); /* allow reinit in notification */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL04 */
            /* CAN234 */
            CanIf_ControllerModeIndication( (uint8)channel, CANIF_CS_STOPPED ); /* SBSW_CAN_HL01 */
# endif
          }
        }
        else /* no wakeup-source-ref: do emulated sleep mode */
#endif
        {
          /* CAN267    CAN_NOT_SUPPORTED is CAN_OK (stay in Stop mode instead) */
          retval = CAN_OK;
          canStatus[channel] = (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_SLEEP))) | CAN_STATUS_STOP); /* del SLEEP for CAN_EMULATE_SLEEP */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
          canStatusReq[channel] &= (uint8)(~(CAN_STATUS_SETMODE)); /* allow reinit in notification */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL04 */
          /* CAN234, CAN405 */
          CanIf_ControllerModeIndication( (uint8)channel, CANIF_CS_STOPPED ); /* SBSW_CAN_HL01 */
#endif
        }
      break;

/* ------------------------- CAN_T_SLEEP ------------------------- */
      case CAN_T_SLEEP:
#if defined( C_ENABLE_SLEEP_WAKEUP )
        /* CAN257 */
        if (CanWakeupSourceRef[channel] != 0) /* otherwise emulated sleep */
        {
          retval = CAN_OK;
          transitionDone = CAN_OK;
# if (CAN_EXTENDED_STATE_MACHINE == STD_ON)
#  if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
          CanResetBusSleep(channel, lastInitObject[channel]); /* SBSW_CAN_HL18 */
#  else
          CanResetBusSleep(lastInitObject[channel]); /* SBSW_CAN_HL18 */
#  endif
# endif
          /* --- CAN_T_SLEEP: set request and wait limited time --- */
          {
# if defined( C_ENABLE_PARTIAL_NETWORK )
            if (CAN_PARTIAL_NET[channel] == TRUE)
            {
              canTimeoutCall[channel] = FALSE; /* SBSW_CAN_HL29 */
            }
# endif
            /* CAN265 */
            /* ASR: if controller need START before SLEEP just request this start before and wait small time (no hw loop) */
            
            #if (CAN_ENABLE_SLEEP_WAKEUP_GLOBAL == STD_ON)
            vuint32 can_power_down_mask[3] = {0x03,0x0C,0x30};
            # if defined (C_ENABLE_WAKEUP_POLLING)
            # else
            CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
            CanSetPointerToCanHardware;
            # endif
            #endif
            
            #if (CAN_ENABLE_SLEEP_WAKEUP_GLOBAL == STD_OFF)
            CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
            CanSetPointerToCanHardware;
            #endif
            
            CanDeclareGlobalInterruptOldStatus
            CanNestedGlobalInterruptDisable(); /* SBSW_CAN_LL002 */
            
            #if defined (C_ENABLE_WAKEUP_POLLING)
            #else
            CNTRLREG = NORMAL_MODE(channel) | kSetSIE; /* SBSW_CAN_LL004 */
            #endif
            
            #if (CAN_ENABLE_SLEEP_WAKEUP_GLOBAL == STD_ON)
            *((V_DEF_P2VAR(V_NONE, vuint32, VAR_NOINIT, VAR_NOINIT)) 0xFFFFE084) |= can_power_down_mask[channel]; /* SBSW_CAN_LL016 */
            
            STATUS_SLEEP(channel) = kCanTrue; /* SBSW_CAN_LL006 */
            transitionRequest         = kCanOk;
            #endif
            
            #if (CAN_ENABLE_SLEEP_WAKEUP_GLOBAL == STD_OFF)
            CNTRLREG |= kSetPDR; /* SBSW_CAN_LL004 */
            transitionRequest = kCanRequested;
            #endif
            
            CanNestedGlobalInterruptRestore(); /* SBSW_CAN_LL002 */
            
            if ( transitionRequest == CAN_NOT_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
            { /* PRQA S 3201 */ /* MD_Can_3201 */
              retval = CAN_NOT_OK;
              transitionDone = CAN_NOT_OK; /* at least one HW channel is not in new state (CAN_MSR40: poll later) */
            }
            if ( transitionRequest == CAN_REQUESTED ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
            { /* PRQA S 3201 */ /* MD_Can_3201 */
              CanHL_ApplCanTimerStart(kCanLoopSleep); /* SBSW_CAN_HL33 */
              /* CAN266, CAN370, CAN371, CAN372 */
              do
              {
                #if (CAN_ENABLE_SLEEP_WAKEUP_GLOBAL == STD_OFF)
                CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
                CanSetPointerToCanHardware;
                
                if ( ((STATREG & kPDA) == 0) && ((CNTRLREG & kSetPDR) == kSetPDR) )
                {
                  STATUS_SLEEP(channel) = kCanFalse;
                  transitionRequest = kCanFailed;
                }
                else
                {
                  STATUS_SLEEP(channel) = kCanTrue; /* SBSW_CAN_LL006 */
                  transitionRequest = kCanOk;
                }
                #endif
                
                CanHL_ApplCanTimerLoop(kCanLoopSleep); /* SBSW_CAN_HL33 */
              } while ( transitionRequest != CAN_OK );
              CanHL_ApplCanTimerEnd(kCanLoopSleep); /* SBSW_CAN_HL33 */
              if ( transitionRequest != CAN_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
              { /* PRQA S 3201 */ /* MD_Can_3201 */
                transitionDone = CAN_NOT_OK; /* at least one HW channel is not in new state (CAN_MSR40: poll later) */
#  if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
                canStatusReq[channel] = CAN_STATUS_SLEEP; /* Asyncron polling on */ /* SBSW_CAN_HL04 */
#  endif
#  if (CAN_MICROSAR_VERSION == CAN_MSR30)
                retval = CAN_NOT_OK;
#  endif
              }
            }
          } /* loop canHwChannel */
# if defined(C_ENABLE_HW_LOOP_TIMER)
          if ( (transitionDone == CAN_OK)  && (canIsHardwareCanceled[channel] == FALSE) ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
# else
          if ( transitionDone == CAN_OK ) /* PRQA S 3355,3356,3358,3359 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */
# endif
          { /* PRQA S 3201 */ /* MD_Can_3201 */
            CanHookStateChange_SleepSync(canStatus[channel], (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_STOP))) | CAN_STATUS_SLEEP) ); /* PRQA S 0277 */ /* MD_Can_0277_negation */
            canStatus[channel] = (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_STOP))) | CAN_STATUS_SLEEP); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
# if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
            canStatusReq[channel] &= (uint8)(~(CAN_STATUS_SETMODE)); /* allow reinit in notification */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL04 */
            /* CAN234 */
            CanIf_ControllerModeIndication( (uint8)channel, CANIF_CS_SLEEP ); /* SBSW_CAN_HL01 */
# endif
          }
        }
        else /* no wakeup-source-ref: do emulated sleep mode */
#endif
        /* CAN258, CAN290, CAN404 */
        {
#if (CAN_MICROSAR_VERSION == CAN_MSR30)
          /* controller stay in stop mode / CAN_NOT_SUPPORTED is CAN_OK */
          retval = CAN_OK;
#endif
#if ( CAN_EMULATE_SLEEP == STD_ON )
          retval = CAN_OK;
          canStatus[channel] = (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_STOP))) | CAN_STATUS_SLEEP); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL02 */
# if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
          canStatusReq[channel] &= (uint8)(~(CAN_STATUS_SETMODE)); /* allow reinit in notification */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL04 */
          /* CAN234 */
          CanIf_ControllerModeIndication( (uint8)channel, CANIF_CS_SLEEP ); /* SBSW_CAN_HL01 */
# endif
#endif
        }
      break; /* CAN_T_SLEEP */

      default: /* PRQA S 2018 */ /* MD_Can_Asr_2018 */
#if (CAN_DEV_ERROR_DETECT == STD_ON) /* CAN026, CAN028, CAN091, CAN082, CAN083 */
        Can_CallDetReportError(CAN_SETCTR_ID, CAN_E_TRANSITION); /* CAN200 */ /* SBSW_CAN_HL06 */
        retval = CAN_NOT_OK; /* CAN089 */
#endif
      break;
      } /* switch */
    }
#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
    canStatusReq[channel] &= (uint8)(~(CAN_STATUS_SETMODE)); /* remove mark ongoing state change (suppress stop transition in Can_InitController) */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL04 */
#endif

#if defined(C_ENABLE_HW_LOOP_TIMER)
    if ( canIsHardwareCanceled[channel] == TRUE )
    { /* while mode change a hardware cancelation appear and therefor the mode change is not successfull */
      canIsHardwareCanceled[channel] = FALSE; /* SBSW_CAN_HL32 */
      retval = CAN_NOT_OK; /* CAN092, CAN093 */
# if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
      canStatusReq[channel] = CAN_STATUS_UNINIT; /* no more status polling - request failed */ /* SBSW_CAN_HL04 */
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON) /* CAN026, CAN028, CAN091, CAN082, CAN083 */
      Can_CallDetReportError(CAN_SETCTR_ID, CAN_E_TRANSITION); /* SBSW_CAN_HL06 */
# endif
    }
#endif
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_6); /* SBSW_CAN_HL11 */
  }
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON ) && defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
#endif
  CanHookEnd_Can_SetControllerMode();
  return retval;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/* CAN231, CAN204, CAN292 */
/****************************************************************************
| NAME:             Can_DisableControllerInterrupts
| CALLED BY:        CanInterface or other higher layer
| PRECONDITIONS:    none
| INPUT PARAMETERS: Controller number
| RETURN VALUES:    none
| DESCRIPTION:      disable can interrupt for this Controller
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_DisableControllerInterrupts( uint8 Controller )
{
  CanHookBegin_Can_DisableControllerInterrupts();
  /* CAN248 */
    Can_CheckDetErrorReturnVoid((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_DIINT_ID, CAN_E_UNINIT); /* CAN205 */ /* SBSW_CAN_HL06 */
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
    Can_SilentBswCheckErrorReturnVoid((channel < kCanNumberOfChannels), CAN_DIINT_ID, CAN_E_PARAM_CONTROLLER); /* CAN206 */ /* SBSW_CAN_HL06, SBSW_CM_CAN_HL37 */
#endif
  /* CAN248 */
  Can_CheckDetErrorReturnVoid((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_DIINT_ID, CAN_E_UNINIT); /* CAN205 */ /* SBSW_CAN_HL06 */
#if defined ( C_ENABLE_MULTI_ECU_CONFIG )
  Can_CheckDetErrorReturnVoid(( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) != (cantVIdentityMsk)0 ), CAN_DIINT_ID, CAN_E_PARAM_CONTROLLER); /* SBSW_CAN_HL06 */
#endif
  {
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_1); /* SBSW_CAN_HL11 */
#if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API != STD_ON) && (CAN_DEV_TIMEOUT_DETECT == STD_ON) && (CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_MICROSAR_VERSION == CAN_MSR30)
    canApiContext = CAN_DIINT_ID;
#endif
    if (canCanInterruptCounter[channel] == 0)
    {
#if ( CAN_INTLOCK == CAN_DRIVER ) || ( CAN_INTLOCK == CAN_BOTH )
      {
        /* CAN049 */
        CanLL_CanInterruptDisable(canHwChannel, &canCanInterruptOldStatus[canHwChannel]); /* SBSW_CAN_HL35 */
      }
#endif
#if ( CAN_INTLOCK == CAN_APPL ) || ( CAN_INTLOCK == CAN_BOTH )
      ApplCanInterruptDisable((uint8)channel); /* SBSW_CAN_HL36 */
#endif
    }
    canCanInterruptCounter[channel]++; /* CAN202 */ /* SBSW_CAN_HL28 */
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_1); /* SBSW_CAN_HL11 */
  }
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON ) && defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
#endif
  CanHookEnd_Can_DisableControllerInterrupts();
}

/* CAN232, CAN293 */
/****************************************************************************
| NAME:             Can_EnableControllerInterrupts
| CALLED BY:        CanInterface or other higher layer
| PRECONDITIONS:    none
| INPUT PARAMETERS: Controller number
| RETURN VALUES:    none
| DESCRIPTION:      enable can interrupt for this Controller
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_EnableControllerInterrupts( uint8 Controller )
{
  CanHookBegin_Can_EnableControllerInterrupts();
  /* CAN248 */
  Can_CheckDetErrorReturnVoid((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_ENINT_ID, CAN_E_UNINIT); /* CAN209 */ /* SBSW_CAN_HL06 */
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnVoid((channel < kCanNumberOfChannels), CAN_ENINT_ID, CAN_E_PARAM_CONTROLLER); /* CAN210 */ /* SBSW_CAN_HL06, SBSW_CM_CAN_HL38 */
#endif
  /* CAN248 */
  Can_CheckDetErrorReturnVoid((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_ENINT_ID, CAN_E_UNINIT); /* CAN209 */ /* SBSW_CAN_HL06 */
#if defined ( C_ENABLE_MULTI_ECU_CONFIG )
  Can_CheckDetErrorReturnVoid(( ((cantVIdentityMsk)CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) != (cantVIdentityMsk)0 ), CAN_ENINT_ID, CAN_E_PARAM_CONTROLLER); /* SBSW_CAN_HL06 */
#endif
  {
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_1); /* SBSW_CAN_HL11 */
    if (canCanInterruptCounter[channel] != 0) /* CAN208 */
    {
      canCanInterruptCounter[channel]--; /* SBSW_CAN_HL28 */
#if defined(C_ENABLE_HW_LOOP_TIMER) && (CAN_HW_LOOP_SUPPORT_API != STD_ON) && (CAN_DEV_TIMEOUT_DETECT == STD_ON) && (CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_MICROSAR_VERSION == CAN_MSR30)
      canApiContext = CAN_ENINT_ID;
#endif
      if (canCanInterruptCounter[channel] == 0)
      {
#if ( CAN_INTLOCK == CAN_DRIVER ) || ( CAN_INTLOCK == CAN_BOTH )
        {
          /* CAN050 */
          CanLL_CanInterruptRestore(canHwChannel, canCanInterruptOldStatus[canHwChannel]); /* SBSW_CAN_HL35 */
        }
#endif
#if ( CAN_INTLOCK == CAN_APPL ) || ( CAN_INTLOCK == CAN_BOTH )
        ApplCanInterruptRestore((uint8)channel); /* SBSW_CAN_HL36 */
#endif
      }      
    }
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_1); /* SBSW_CAN_HL11 */
  }
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON ) && defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
#endif
  CanHookEnd_Can_EnableControllerInterrupts();
}

/* CAN233, CAN275, CAN100 */
/****************************************************************************
| NAME:             Can_Write
| CALLED BY:        CanInterface
| PRECONDITIONS:    Interrupt locked by CANInterface
| INPUT PARAMETERS: Controller number, handle to mailbox, Pointer to Pdu data, type of handle
| RETURN VALUES:    CAN_OK, CAN_NOT_OK, CAN_BUSY
| DESCRIPTION:      Send CAN message
****************************************************************************/
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_Write( Can_HwHandleType Hth, Can_PduInfoPtrType PduInfo )
{
  Can_ReturnType retval;
  CAN_CHANNEL_CANTYPE_LOCAL
  /* CAN216, CAN248 */
  Can_CheckDetErrorReturnValue((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_WRITE_ID, CAN_E_UNINIT, CAN_NOT_OK); /* unknown channel for postbuild */ /* SBSW_CAN_HL06 */
  CanHookBegin_Can_Write();
  retval = CAN_OK;
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  canHwChannel = CAN_MAILBOX[Hth].MsgController;
#endif
  /* CAN089 */
  /* CAN248 */
  Can_CheckDetErrorReturnValue((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_WRITE_ID, CAN_E_UNINIT, CAN_NOT_OK); /* SBSW_CAN_HL06 */
  /* CAN217 */
  Can_CheckDetErrorReturnValue(( (CAN_MAILBOX[Hth].MailboxType == TxBasicCANType) || 
               (CAN_MAILBOX[Hth].MailboxType == TxFullCANType) ),
               CAN_WRITE_ID, CAN_E_PARAM_HANDLE, CAN_NOT_OK); /* SBSW_CAN_HL06 */
#if defined ( C_ENABLE_MULTI_ECU_CONFIG )
  Can_CheckDetErrorReturnValue(( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) != (cantVIdentityMsk)0 ),
                               CAN_WRITE_ID, CAN_E_PARAM_HANDLE, CAN_NOT_OK); /* SBSW_CAN_HL06 */
#endif
  /* CAN219 */
  Can_CheckDetErrorReturnValue(( PduInfo != NULL_PTR ), CAN_WRITE_ID, CAN_E_PARAM_POINTER, CAN_NOT_OK); /* SBSW_CAN_HL06 */
  /* CAN219 */
  Can_CheckDetErrorReturnValue(( (PduInfo->sdu != NULL_PTR) || (PduInfo->length == 0) ), CAN_WRITE_ID, CAN_E_PARAM_POINTER, CAN_NOT_OK); /* SBSW_CAN_HL06 */
  /* CAN218 */
  Can_CheckDetErrorReturnValue(( PduInfo->length <= CAN_MAX_TX_BUFFER_DLC ), CAN_WRITE_ID, CAN_E_PARAM_DLC, CAN_NOT_OK); /* SBSW_CAN_HL06 */
#if (CAN_FD_SUPPORT == CAN_NONE)
  Can_CheckDetErrorReturnValue(( (PduInfo->id & (Can_IdType)CAN_FD_MASK) != (Can_IdType)CAN_FD_MASK ), CAN_WRITE_ID, CAN_E_PARAM_POINTER, CAN_NOT_OK); /* SBSW_CAN_HL06 */
#endif
  Can_CheckDetErrorReturnValue(( (PduInfo->id & (Can_IdType)CAN_ID_MASK) <= (Can_IdType)CAN_ID_MAX ), CAN_WRITE_ID, CAN_E_PARAM_POINTER, CAN_NOT_OK); /* SBSW_CAN_HL06 */
  /* CAN214 */
  if (canIsBusOff[channel] == TRUE) /* Hardware is in BusOff recovery state and is not able to handle a request */
  {
    retval = CAN_BUSY;
  }
#if defined( C_ENABLE_CAN_RAM_CHECK )
  else if ((canStatus[channel] & CAN_DEACTIVATE_CONTROLLER) == CAN_DEACTIVATE_CONTROLLER)
  {
    retval = CAN_NOT_OK;
  }
#endif
  else
  {
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) 
    uint8_least muxTx;
#endif
    Can_HwHandleType txObjHandle;
    CanObjectHandle  logTxObjHandle;
    txObjHandle = CAN_MAILBOX[Hth].HwHandle;
    logTxObjHandle = (CanObjectHandle)(txObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(channel));
    /* Can_Write() could be called reentrant, therefor also for polling systems the interrupts have to be locked */
    /* this is essential while check for object is free (inbetween if (free) and set to not free) and save pdu handle */
    /* done by CanIF: Can_EnterCritical(); */
#if !defined(CAN_USE_VECTOR_IF)
    /* No Vector Interface used, Interrupts may not be locked and reentrant call may occur. Time inbetwen seach and lock of object is critical */
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_2); /* SBSW_CAN_HL11 */
#endif
#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
    if ( CAN_MAILBOX[Hth].MailboxType == TxBasicCANType )
#endif
    {
      /* CAN278, CAN285 */
      /* CAN277, CAN101, CAN076, CAN401, CAN402, CAN403 */
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
      for (muxTx = 0; muxTx < CAN_MULTIPLEXED_TX_MAX; muxTx++)
      {
        if (CAN_ACTIVESEND_STATE(logTxObjHandle) == CANFREEOBJ) 
        { /* prio 1: find free mailbox (no cancelation) */
          break;
        }
        logTxObjHandle++;
      }
      if (muxTx == CAN_MULTIPLEXED_TX_MAX)
      { /* found no free object */
        muxTx = 0; /* illegal value removed */
        logTxObjHandle--; /* set to last valid handle */
      } /* otherwise the muxTx and logTxObjHandle are the free or to be canceled one */
#else /* C_ENABLE_MULTIPLEXED_TRANSMISSION */
#endif
    } /* end BasicCAN handling */
      /* no special FullCAN handling needed */

/* start  common handling for FullCAN and BasicCAN */
    if (CAN_ACTIVESEND_STATE(logTxObjHandle) == CANFREEOBJ)
    {
      /* CAN212 */
      V_DEF_P2CONST(V_NONE, uint8, AUTOMATIC, APPL_VAR) CanMemCopySrcPtr;
      #if defined( C_ENABLE_HW_LOOP_TIMER )
      vuint8 canTimerResult;
      #endif
      
      CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
      
#if (CAN_GENERIC_PRETRANSMIT == STD_ON)
      Can_PduType PduInfo_var; /* temporary buffer to avoid data modification on const data */
      Can_PduInfoPtrType_var PduInfoPtr_var;
      PduInfoPtr_var = &PduInfo_var;
      PduInfo_var.id = PduInfo->id; /* PduInfo copy from const-pointer context to var-pointer context */
      PduInfo_var.length = PduInfo->length;
      PduInfo_var.sdu = PduInfo->sdu;
      PduInfo_var.swPduHandle = PduInfo->swPduHandle;
      Appl_GenericPreTransmit( (uint8)channel, PduInfoPtr_var );  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL47 */
#endif
      /* CAN276 */
      CAN_ACTIVESEND_PDUID(logTxObjHandle) = PDUINFO_PTR->swPduHandle; /* SBSW_CAN_HL10 */
      CAN_ACTIVESEND_STATE(logTxObjHandle) = CANSENDOBJ; /* SBSW_CAN_HL09 */
      txObjHandle = (Can_HwHandleType)(logTxObjHandle - CAN_HL_TX_OFFSET_HW_TO_LOG(channel)); /* PRQA S 3760 */ /* MD_Can_3760_LogToHw */

      CanSetPointerToCanHardware; 
      #if defined( V_ENABLE_USE_DUMMY_STATEMENT )
      txObjHandle = txObjHandle;
      #endif
#if ( CAN_EXTENDED_ID == STD_ON)
# if ( CAN_MIXED_ID == STD_ON)
      if ( ((PDUINFO_PTR->id) & CAN_EXTENDED_ID_MASK) != CAN_EXTENDED_ID_MASK)
      {
#  if ( CAN_DYNAMIC_FULLCAN_ID == STD_OFF ) && defined(C_ENABLE_TX_FULLCAN_OBJECTS)
        if (CAN_MAILBOX[Hth].MailboxType == TxBasicCANType)
#  endif
        {
          #if defined( C_ENABLE_EXTENDED_ID )
          TX_MSGOBJ_ID_LOW(logTxObjHandle)  = (vuint16)MK_STDID1(PDUINFO_PTR->id); /* SBSW_CAN_LL015 */
          #endif
          TX_MSGOBJ_ID_HIGH(logTxObjHandle) = (vuint16)MK_STDID0(PDUINFO_PTR->id)  | kSetMsgVal | kSetDir; /* SBSW_CAN_LL015 */
        }
        TX_MSGOBJ_DLC(logTxObjHandle) = MK_TX_DLC(PDUINFO_PTR->length); /* SBSW_CAN_LL015 */
      }
        else
# endif
      {
# if ( CAN_DYNAMIC_FULLCAN_ID == STD_OFF ) && defined(C_ENABLE_TX_FULLCAN_OBJECTS)
        if (CAN_MAILBOX[Hth].MailboxType == TxBasicCANType)
# endif
        {
          #if defined( C_ENABLE_EXTENDED_ID )
          TX_MSGOBJ_ID_LOW(logTxObjHandle)  = (vuint16)MK_EXTID1(PDUINFO_PTR->id); /* SBSW_CAN_LL015 */
          #endif
          TX_MSGOBJ_ID_HIGH(logTxObjHandle) = (vuint16)MK_EXTID0(PDUINFO_PTR->id)  | kSetMsgVal | kSetDir; /* SBSW_CAN_LL015 */
        }
        TX_MSGOBJ_DLC(logTxObjHandle) = MK_TX_DLC_EXT(PDUINFO_PTR->length); /* SBSW_CAN_LL015 */
      }
#else
# if ( CAN_DYNAMIC_FULLCAN_ID == STD_OFF ) && defined(C_ENABLE_TX_FULLCAN_OBJECTS)
      if (CAN_MAILBOX[Hth].MailboxType == TxBasicCANType)
# endif
      {
        #if defined( C_ENABLE_EXTENDED_ID )
        TX_MSGOBJ_ID_LOW(logTxObjHandle)  = (vuint16)MK_STDID1(PDUINFO_PTR->id); /* SBSW_CAN_LL015 */
        #endif
        TX_MSGOBJ_ID_HIGH(logTxObjHandle) = (vuint16)MK_STDID0(PDUINFO_PTR->id)  | kSetMsgVal | kSetDir; /* SBSW_CAN_LL015 */
      }
      TX_MSGOBJ_DLC(logTxObjHandle) = MK_TX_DLC(PDUINFO_PTR->length); /* SBSW_CAN_LL015 */
#endif
      if(PDUINFO_PTR->sdu != NULL_PTR)
      {
        CanMemCopySrcPtr = PDUINFO_PTR->sdu;
        /* CAN059, CAN011, CAN427 */
        {
          vuint16 copy_counter;
        
          for(copy_counter=0; copy_counter<8; copy_counter++)
          {
            txMsgObj[logTxObjHandle].Data.ucData[copy_counter] = *CanMemCopySrcPtr; /* SBSW_CAN_LL015 */
            CanMemCopySrcPtr++;
          }
        }
        
      }
      CanSetPointerToCanHardware;
      if(((IF_TRANSMIT.ComRequest & kIFxBusy) == kIFxBusy))
      {
        APPLCANTIMERSTART(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
      
        do{
            CANTIMERRESULT_UPDATE(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
      
          } WHILE_CONDITON( ((IF_TRANSMIT.ComRequest & kIFxBusy) == kIFxBusy) );
      
        APPLCANTIMEREND(kCanLoopBusyReq); /* SBSW_CAN_LL003 */
      }
      
      /* WrRd,Mask,Arb,Control,DataA,DataB set */
      IF_TRANSMIT.ComMask         =  kSetWrRd | kSetMask | kSetArb | kSetControl | kSetDataA | kSetDataB; /* SBSW_CAN_LL004 */
      
      /* copy ID, Dlc and Data from the MsgObjectBuffer in IF1 */ 
      
      #if defined( C_ENABLE_EXTENDED_ID )
      IF_TRANSMIT.ArbitrFld1      =  TX_MSGOBJ_ID_LOW(logTxObjHandle); /* SBSW_CAN_LL004 */
      #endif
      IF_TRANSMIT.ArbitrFld2      =  TX_MSGOBJ_ID_HIGH(logTxObjHandle); /* SBSW_CAN_LL004 */
      
      #if defined (C_ENABLE_INDIVIDUAL_POLLING)     
      /* set Dlc and TxRqst */
      if(CAN_INDIV_POLLING(channel, txObjHandle) != 0) /* PRQA S 3325 */ /* MD_Can_3325_LL */
      {                                                /* PRQA S 3201 */ /* MD_Can_3201_LL */
        IF_TRANSMIT.MessageCntrl  =  TX_MSGOBJ_DLC(logTxObjHandle) | kSetTxRqst | kSetEoB;
      }
      else
      {
        IF_TRANSMIT.MessageCntrl  =  TX_MSGOBJ_DLC(logTxObjHandle) | kSetTxRqst | kSetEoB | kSetEnableTxCanInt;
      }
      #else     
      # if defined (C_ENABLE_TX_POLLING)     
       IF_TRANSMIT.MessageCntrl  =  TX_MSGOBJ_DLC(logTxObjHandle) | kSetTxRqst | kSetEoB; /* SBSW_CAN_LL004 */
      # else
       IF_TRANSMIT.MessageCntrl  =  TX_MSGOBJ_DLC(logTxObjHandle) | kSetTxRqst | kSetEoB | kSetEnableTxCanInt; /* SBSW_CAN_LL004 */
      # endif /* C_ENABLE_TX_POLLING */
      #endif /* C_ENABLE_INDIVIDUAL_POLLING */
      
      #if defined(C_CPUTYPE_BIGENDIAN)
      IF_TRANSMIT.Data.ucData[0]  =  txMsgObj[logTxObjHandle].Data.ucData[3]; /* SBSW_CAN_LL004 */
      IF_TRANSMIT.Data.ucData[1]  =  txMsgObj[logTxObjHandle].Data.ucData[2]; /* SBSW_CAN_LL004 */
      IF_TRANSMIT.Data.ucData[2]  =  txMsgObj[logTxObjHandle].Data.ucData[1]; /* SBSW_CAN_LL004 */
      IF_TRANSMIT.Data.ucData[3]  =  txMsgObj[logTxObjHandle].Data.ucData[0]; /* SBSW_CAN_LL004 */
      IF_TRANSMIT.Data.ucData[4]  =  txMsgObj[logTxObjHandle].Data.ucData[7]; /* SBSW_CAN_LL004 */
      IF_TRANSMIT.Data.ucData[5]  =  txMsgObj[logTxObjHandle].Data.ucData[6]; /* SBSW_CAN_LL004 */
      IF_TRANSMIT.Data.ucData[6]  =  txMsgObj[logTxObjHandle].Data.ucData[5]; /* SBSW_CAN_LL004 */
      IF_TRANSMIT.Data.ucData[7]  =  txMsgObj[logTxObjHandle].Data.ucData[4]; /* SBSW_CAN_LL004 */
      #endif
      
      
      /* start copy data from IF1 to ObjectRAM */
      IF_TRANSMIT.ComRequest      =  txObjHandle + 1; /* SBSW_CAN_LL004 */
      
      if (txObjHandle < 32)
      {
        TX_SEND_FLAG(channel,0) |= ((vuint32)0x1<<(txObjHandle)); /* SBSW_CAN_LL014 */
      }
      else
      {
        TX_SEND_FLAG(channel,1) |= ((vuint32)0x1<<(txObjHandle-32)); /* SBSW_CAN_LL014 */
      }
    } /* free */
    else
    {
      /* CAN213, CAN214, CAN215 */
      retval = CAN_BUSY; /* always busy also if cancelation (BasicCAN) was possible */
    } 
/* end  common handling for FullCAN and BasicCAN */

    /* Can_EnableControllerInterrupts((uint8)channel); done by CanIF: avoid change of pdu information due to tx interrupt while changing */
#if !defined(CAN_USE_VECTOR_IF) /* No Vector Interface used, Interrupts may not be locked */
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_2); /* SBSW_CAN_HL11 */
#endif
  }
  CanHookEnd_Can_Write();
  return retval;
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */

/* CAN360, CAN361 */
/****************************************************************************
| NAME:             ASR4.x - Can_CheckWakeup / ASR3.x - Can_Cbk_CheckWakeup
| CALLED BY:        CanIf
| PRECONDITIONS:
| INPUT PARAMETERS: Controller
| RETURN VALUES:     E_OK, E_NOT_OK (feedback whether this controller cause wakeup before)
| DESCRIPTION:      wakeup callback for higher layers
****************************************************************************/
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckWakeup( uint8 Controller )
{
  Std_ReturnType retval;
  retval = E_NOT_OK; /* CAN089 */
  CanHookBegin_Can_CheckWakeup();
#if defined (C_ENABLE_SLEEP_WAKEUP)
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnValue((channel < kCanNumberOfChannels), CAN_CKWAKEUP_ID, CAN_E_PARAM_CONTROLLER, E_NOT_OK); /* CAN363 */ /* SBSW_CAN_HL06, SBSW_CM_CAN_HL28 */
# endif
# if defined ( C_ENABLE_MULTI_ECU_CONFIG )
  if ( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
  {
    return retval;
  }
# endif
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  /* CAN248 */
  Can_CheckDetErrorReturnValue((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_CKWAKEUP_ID, CAN_E_UNINIT, E_NOT_OK); /* CAN362 / ESCAN00045884 */ /* SBSW_CAN_HL06 */
# endif
  {
    if (canIsWakeup[channel] == TRUE)
    {
      canIsWakeup[channel] = FALSE; /* SBSW_CAN_HL20 */
      /* since there is no more call from CanIf to EcuM_SetWakeupEvent in AutoSar 3.2.1/4.0.3 */
      /* Driver call this to prevent missing wakeup-notification (multiple call is ok) */
      EcuM_SetWakeupEvent(CanWakeupSourceRef[channel]); /* SBSW_CAN_HL21 */
      retval = E_OK;
    }
  }
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON ) && defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
#else
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
#endif
  CanHookEnd_Can_CheckWakeup();
  return retval;
}

/* CAN110, CAN225*/
/****************************************************************************
| NAME:             Can_MainFunction_Write
| CALLED BY:        Application()
| PRECONDITIONS:    none
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      Polling of Tx events to handle Tx confirmations
|                   Polling of Tx Cancelation events
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Write( void )
{
  /* CAN178, CAN099, CAN007, CAN431 */
#if defined(C_ENABLE_TX_POLLING) 
  CAN_CHANNEL_CANTYPE_LOCAL
  CanObjectHandle txObjHandle;
  #if defined( C_ENABLE_TX_POLLING )
    CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
    vuint8  can_transrequest;
  #endif
  CanHookBegin_Can_MainFunction_Write();
  /* CAN179, CAN248 */
  Can_CheckDetErrorReturnVoid((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_MAINFCT_WRITE_ID, CAN_E_UNINIT); /* SBSW_CAN_HL06 */
  /* canSendSemaphor no more needed because of ControllerInterrupts disabled while Can_Write() */
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
  {
# if defined ( C_ENABLE_MULTI_ECU_CONFIG )
    if ( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
    {
      continue; /* PRQA S 0770 */ /* MD_Can_0770 */
    }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON) /* CAN026, CAN028, CAN091, CAN082, CAN083 */
    /* CAN248 */
    Can_CheckDetErrorReturnVoid((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_MAINFCT_WRITE_ID, CAN_E_UNINIT); /* SBSW_CAN_HL06 */
# endif
    {
# if defined( C_ENABLE_SLEEP_WAKEUP ) || ( CAN_EMULATE_SLEEP == STD_ON )
      if ( !CanHL_IsSleep(channel) )
# endif
      {
        {
#  if defined(C_ENABLE_TX_POLLING)
          {
          CanSetPointerToCanHardware;
            for ( txObjHandle = CAN_HL_HW_TX_STARTINDEX(canHwChannel); txObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel); txObjHandle++ )
            {
#   if defined( C_ENABLE_INDIVIDUAL_POLLING )
              if ( CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][txObjHandle] != (uint8)0 )
#   endif
              {
                CanDeclareGlobalInterruptOldStatus
                CanSetPointerToCanHardware;
                can_transrequest = 0;
                
                CanNestedGlobalInterruptDisable(); /* SBSW_CAN_LL002 */
                if (txObjHandle < 32)
                {
                  if (TX_SEND_FLAG(channel,0) != 0)
                  {
                    if ( ((TRANSREQUEST(0)         & ((vuint32)0x1<<(txObjHandle))) == 0) && \
                         ((TX_SEND_FLAG(channel,0) & ((vuint32)0x1<<(txObjHandle))) != 0)    )
                      {
                        can_transrequest = 1;
                        TX_SEND_FLAG(channel,0) &= ~((vuint32)0x1<<(txObjHandle)); /* SBSW_CAN_LL014 */
                      }
                  }
                }
                else
                {
                  if (TX_SEND_FLAG(channel,1) != 0)
                  {
                    if ( ((TRANSREQUEST(1)         & ((vuint32)0x1<<(txObjHandle-32))) == 0) && \
                         ((TX_SEND_FLAG(channel,1) & ((vuint32)0x1<<(txObjHandle-32))) != 0)    )
                      {
                        can_transrequest = 1;
                        TX_SEND_FLAG(channel,1) &= ~((vuint32)0x1<<(txObjHandle-32)); /* SBSW_CAN_LL014 */
                      }
                  }
                }
                CanNestedGlobalInterruptRestore(); /* SBSW_CAN_LL002 */
                
                if (can_transrequest != 0)
                {
                  /* interrupts locked inside */
                  /* CAN031 */
                  CanHL_TxConfirmation( CAN_HW_CHANNEL_CANPARA_FIRST txObjHandle ); /* SBSW_CAN_HL37 */
                }
              }
            }
          }
#  endif
        } /* CanHL_IsSleep */
      } /* end of loop over all hw channels */
    }
  }
#else
  CanHookBegin_Can_MainFunction_Write();
#endif /* C_ENABLE_TX_POLLING */
  CanHookEnd_Can_MainFunction_Write();
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/* CAN226 */
/****************************************************************************
| NAME:             Can_MainFunction_Read
| CALLED BY:        Application, CAN Interface
| PRECONDITIONS:    none
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      Polling of Rx events to handle Rx Indication
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Read( void )
{
  /* CAN180, CAN099, CAN007, CAN431 */
#if  defined(C_ENABLE_RX_POLLING) || (defined( C_ENABLE_RX_QUEUE ) && (CAN_GENERIC_PRECOPY == STD_ON))
  CAN_CHANNEL_CANTYPE_LOCAL
#endif
#if defined(C_ENABLE_RX_POLLING)
# if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) 
  Can_HwHandleType Htrh;
# endif
  CanObjectHandle rxObjHandle;
  vuint8 can_newdata;
  CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
  /* Local Parameter for RxFull and RxBasic normaly the same so only used one (otherwise use ASR-switch to add it in RxFull LocalPara */
  /* --> CanLL_RxBasicCANTaskLocalParameter */
  CanHookBegin_Can_MainFunction_Read();
  /* CAN181, CAN248 */
  Can_CheckDetErrorReturnVoid((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_MAINFCT_READ_ID, CAN_E_UNINIT); /* SBSW_CAN_HL06 */
  /* CAN012 */
  if ( canRxTaskActive == CAN_FREE)
  {
    canRxTaskActive = CAN_BUSY;
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
    {
# if defined ( C_ENABLE_MULTI_ECU_CONFIG )
      if ( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
      {
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# endif
      /* CAN248 */
      Can_CheckDetErrorReturnVoid((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_MAINFCT_READ_ID, CAN_E_UNINIT); /* SBSW_CAN_HL06 */
      {
# if defined( C_ENABLE_SLEEP_WAKEUP ) || ( CAN_EMULATE_SLEEP == STD_ON )
        if ( !CanHL_IsSleep(channel) )
# endif
        {
          {
# if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
            {
            CanSetPointerToCanHardware;
              for (Htrh = CAN_CONTROLLER_CONFIG(canHwChannel).RxFullHandleStart; Htrh < CAN_CONTROLLER_CONFIG(canHwChannel).RxFullHandleStop; Htrh++ )
              {
                rxObjHandle = CAN_MAILBOX[Htrh].HwHandle;
#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
                if ( CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][rxObjHandle] != (uint8)0 )
#  endif
                {
                  can_newdata = 0;
                  CanSetPointerToCanHardware;
                  
                  
                  if (rxObjHandle < 32)
                  {
                    if (NEWDATA(0) != 0)
                    {
                      if ((NEWDATA(0) & ((vuint32)0x1<<(rxObjHandle))) != 0)
                      {
                        can_newdata = 1;
                      }
                    }
                  }
                  else
                  {
                    if ((NEWDATA(1) & 0x3FFFFFFF) != 0)
                    {
                      if ((NEWDATA(1) & ((vuint32)0x1<<(rxObjHandle-32))) != 0)
                      {
                        can_newdata = 1;
                      }
                    }
                  }
                  
                  if (can_newdata != 0) 
                  {
                    /* interrupts locked inside */
                    /* CAN108 */
                    CanFullCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle); /* SBSW_CAN_HL50 */
                  }
                }
              }
            }
# endif
# if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
            {
            CanSetPointerToCanHardware;

              {
                Can_HwHandleType hwObjStart;
                Can_HwHandleType hwObjStop;
                hwObjStart = (Can_HwHandleType)CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel);
                hwObjStop  = (Can_HwHandleType)CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel);
                for (rxObjHandle = hwObjStart; rxObjHandle < hwObjStop; rxObjHandle++)
                {
#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
                  if ( CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][rxObjHandle] != (uint8)0 )
#  endif
                  {
                    can_newdata = 0;
                    CanSetPointerToCanHardware;
                      
                    
                    if (rxObjHandle < 32)
                    {
                      if ((NEWDATA(0) & ((vuint32)0x1<<(rxObjHandle))) != 0)     
                      {
                        can_newdata = 1;
                      }
                    }  
                    else
                    {
                      if ((NEWDATA(1) & ((vuint32)0x1<<(rxObjHandle-32))) != 0)  
                      {
                        can_newdata = 1;
                      }
                    }
                    
                    
                    if (can_newdata != 0) 
                    {
                      /* interrupts locked inside */
                      /* CAN108 */
                      CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle); /* SBSW_CAN_HL38 */
                    }
                  }
                }
              }
            }
# endif
          } /* CanHL_IsSleep */
        } /* end of loop over all hw channels */
      }
    }
    canRxTaskActive = CAN_FREE;
  }
  else
  { /* empty else just to satisfy rule checker */
  }
#else
  CanHookBegin_Can_MainFunction_Read();
#endif /* C_ENABLE_RX_POLLING */

#if defined( C_ENABLE_RX_QUEUE )
/* Execute RxQueue (all channels) */
  while ( canRxQueueInfo.Count != (uint16)0 )
  {
# if (CAN_GENERIC_PRECOPY == STD_ON)
#   if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF ) /* otherwise 'channel' is a define */
    channel = CAN_MAILBOX[canRxQueueBuffer[canRxQueueInfo.ReadIndex].Hrh].MsgController;
#   endif
    Can_SilentBswCheckErrorReturnVoid((channel < kCanNumberOfChannels), CAN_MAINFCT_READ_ID, CAN_E_PARAM_CONTROLLER); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL61 */
    if (Appl_GenericPrecopy( (uint8)channel,
                             canRxQueueBuffer[canRxQueueInfo.ReadIndex].id,
                             canRxQueueBuffer[canRxQueueInfo.ReadIndex].dlc,
                             (Can_DataPtrType)canRxQueueBuffer[canRxQueueInfo.ReadIndex].data ) == CAN_OK)  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL15 */
# endif
    {
      /* CAN234, CAN279, CAN396 */
      CanIf_RxIndication( canRxQueueBuffer[canRxQueueInfo.ReadIndex].Hrh,
                          canRxQueueBuffer[canRxQueueInfo.ReadIndex].id,
                          canRxQueueBuffer[canRxQueueInfo.ReadIndex].dlc,
                          (Can_DataPtrType)canRxQueueBuffer[canRxQueueInfo.ReadIndex].data );  /* PRQA S 0312 */ /* MD_Can_0312 */ /* SBSW_CAN_HL16 */
    }
    

    Can_EnterCritical(CAN_EXCLUSIVE_AREA_4); /* SBSW_CAN_HL11 */
    if (canRxQueueInfo.ReadIndex == (uint16)(kCanRxQueueSize - 1) )
    {
      canRxQueueInfo.ReadIndex = 0;
    }
    else
    {
      canRxQueueInfo.ReadIndex++;
    }
    canRxQueueInfo.Count--;
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_4); /* SBSW_CAN_HL11 */
  }
#endif
  CanHookEnd_Can_MainFunction_Read();
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/* CAN227 */
/****************************************************************************
| NAME:             Can_MainFunction_BusOff
| CALLED BY:        Application()
| PRECONDITIONS:    none
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      Polling of BusOff events to handle BusOff
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_BusOff( void )
{
  /* CAN183, CAN099, CAN007, CAN431 */
#if defined(C_ENABLE_ERROR_POLLING)
  CAN_CHANNEL_CANTYPE_LOCAL
  CanHookBegin_Can_MainFunction_BusOff();
  /* CAN184, CAN248 */
  Can_CheckDetErrorReturnVoid((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_MAINFCT_BO_ID, CAN_E_UNINIT); /* SBSW_CAN_HL06 */
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
  {
# if defined ( C_ENABLE_MULTI_ECU_CONFIG )
    if ( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
    {
      continue; /* PRQA S 0770 */ /* MD_Can_0770 */
    }
# endif
    /* CAN248 */
    Can_CheckDetErrorReturnVoid((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_MAINFCT_BO_ID, CAN_E_UNINIT); /* SBSW_CAN_HL06 */
    {
# if defined( C_ENABLE_SLEEP_WAKEUP ) || ( CAN_EMULATE_SLEEP == STD_ON )
      if ( !CanHL_IsSleep(channel) )
# endif
      {
        {
          /* CAN109 */
          CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY ); /* SBSW_CAN_HL39 */
        }
      }
    }
  }
#else /* C_ENABLE_ERROR_POLLING */
  CanHookBegin_Can_MainFunction_BusOff();
#endif /* C_ENABLE_ERROR_POLLING */
  CanHookEnd_Can_MainFunction_BusOff();
}

/* CAN228 */
/****************************************************************************
| NAME:             Can_MainFunction_Wakeup
| CALLED BY:        Application()
| PRECONDITIONS:    none
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      Polling of Wakeup events to handle Wakeup
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Wakeup( void )
{
  /* CAN185, CAN099, CAN007, CAN431 */
#if defined(C_ENABLE_WAKEUP_POLLING) && defined(C_ENABLE_SLEEP_WAKEUP)
  CAN_CHANNEL_CANTYPE_LOCAL
  CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
  CanHookBegin_Can_MainFunction_Wakeup();
  /* CAN186, CAN248 */
  Can_CheckDetErrorReturnVoid((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_MAINFCT_WU_ID, CAN_E_UNINIT); /* SBSW_CAN_HL06 */
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
  {
# if defined ( C_ENABLE_MULTI_ECU_CONFIG )
    if ( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
    {
      continue; /* PRQA S 0770 */ /* MD_Can_0770 */
    }
# endif
    /* CAN248 */
    Can_CheckDetErrorReturnVoid((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_MAINFCT_WU_ID, CAN_E_UNINIT); /* SBSW_CAN_HL06 */
    {
      pCanNode = CAN_BASIS_ADR(channel); /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */  /* PRQA S 3201 */ /* MD_Can_0306_HWaccess */
         
      CAN_LL_STATUS(channel) |= (STATREG & (kErrBusOff | kWakeupPending)); /* SBSW_CAN_LL006 */
      
      if ((CAN_LL_STATUS(channel) & kWakeupPending) == kWakeupPending)
      {
        CAN_LL_STATUS(channel) &= ~kWakeupPending; /* PRQA S 0277 */ /* MD_Can_0277_negation */  /* PRQA S 4130 */ /* MD_Can_4130_LL */ /* SBSW_CAN_LL006 */
        Can_EnterCritical(CAN_EXCLUSIVE_AREA_5); /* refer to ESCAN 00021223 - same problem like for CBD */ /* SBSW_CAN_HL11 */
        /* CAN112 */
        CanLL_WakeUpHandling(CAN_CHANNEL_CANPARA_ONLY); /* SBSW_CAN_HL51 */
        Can_LeaveCritical(CAN_EXCLUSIVE_AREA_5); /* SBSW_CAN_HL11 */
      }
    }
  }
#else
  CanHookBegin_Can_MainFunction_Wakeup();
#endif
  CanHookEnd_Can_MainFunction_Wakeup();
}


#if (CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)
/* CAN368, CAN369 */
/****************************************************************************
| NAME:             Can_MainFunction_Mode
| CALLED BY:        Application()
| PRECONDITIONS:    none
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      Polling of Mode change events notified to uppder layer (asyncron mode change)
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Mode( void )
{
  CanHookBegin_Can_MainFunction_Mode();
# if (CAN_DEV_ERROR_DETECT == STD_ON) /* CAN026, CAN028, CAN091, CAN082, CAN083 */
  /* CAN248 */
  Can_CheckDetErrorReturnVoid((canConfigInitFlag != CAN_STATUS_UNINIT), CAN_MAINFCT_MODE_ID, CAN_E_UNINIT); /* CAN379 */ /* SBSW_CAN_HL06 */
#  if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON )
  Can_CheckDetErrorReturnVoid((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_MAINFCT_MODE_ID, CAN_E_UNINIT); /* CAN379 */ /* SBSW_CAN_HL06 */
#  endif
# endif
  {
    /* CAN431 */
    CAN_CHANNEL_CANTYPE_LOCAL
    Can_EnterCritical(CAN_EXCLUSIVE_AREA_6); /* SBSW_CAN_HL11 */
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
    {
# if defined ( C_ENABLE_MULTI_ECU_CONFIG )
      if ( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) == (cantVIdentityMsk)0 )
      {
        continue; /* PRQA S 0770 */ /* MD_Can_0770 */
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON) /* CAN026, CAN028, CAN091, CAN082, CAN083 */
      /* CAN248 */
#  if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
      Can_CheckDetErrorLoopContinue((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_MAINFCT_MODE_ID, CAN_E_UNINIT); /* PRQA S 0770 */ /* MD_Can_0770 */ /* CAN379 */ /* SBSW_CAN_HL06 */
#  endif
# endif
      { /* no DET */
        switch (canStatusReq[channel]) /* only one request at one time is possible */
        {
#  if defined( C_ENABLE_SLEEP_WAKEUP ) /* hardware is only in sleep when wakeup over bus is activate and supported */
          case CAN_STATUS_WAKEUP:
            {
              Can_ReturnType transitionDone;
              #if (CAN_ENABLE_SLEEP_WAKEUP_GLOBAL == STD_OFF)
              CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
              CanSetPointerToCanHardware;
              
              if ( ((STATREG & kPDA) == kPDA) )
              {
                transitionDone = kCanFailed;
              }
              else
              {
                CNTRLREG                 = NORMAL_MODE(channel); /* SBSW_CAN_LL004 */
                STATUS_SLEEP(channel)    = kCanFalse; /* SBSW_CAN_LL006 */
                transitionDone        = kCanOk;
              }
              #endif
              
              if ( transitionDone == CAN_OK ) /* PRQA S 3355,3356,3358,3359,3353 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_3353_Asr_CommonCanTransition */
              { /* Mode changed - notify and reset request */  /* PRQA S 3201 */ /* MD_Can_3201 */
                CanHookStateChange_WakeupAsync(canStatus[channel], (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_SLEEP))) | CAN_STATUS_STOP) ); /* PRQA S 0277 */ /* MD_Can_0277_negation */
                canStatusReq[channel] = CAN_STATUS_UNINIT; /* SBSW_CAN_HL05 */
#   if defined( C_ENABLE_CAN_RAM_CHECK )
#    if (CAN_MICROSAR_VERSION == CAN_MSR40)
                Can_InitController((uint8)channel, &Can_ControllerBaudrateConfig[((uint8)(lastInitObject[channel] - (uint8)CAN_INIT_OBJ_START_IDX[channel]) & 0x03u)]); /* SBSW_CAN_HL07 */
#    else
                Can_InitController((uint8)channel, NULL_PTR); /* SBSW_CAN_HL07 */
#    endif
#   else
#   endif
                canStatus[channel] = (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_SLEEP))) | CAN_STATUS_STOP); /* remove CAN_STATUS_SLEEP after Init call to force RAM_CHECK */ /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL03 */
                /* CAN234, CAN373 */
                CanIf_ControllerModeIndication( (uint8)channel, CANIF_CS_STOPPED ); /* SBSW_CAN_HL01 */
              }
            }
            break;
#  endif /*  C_ENABLE_SLEEP_WAKEUP */
#  if defined( C_ENABLE_SLEEP_WAKEUP ) /* hardware is only in sleep when wakeup over bus is activate and supported */
          case CAN_STATUS_SLEEP:
            {
              Can_ReturnType transitionDone;
              #if (CAN_ENABLE_SLEEP_WAKEUP_GLOBAL == STD_OFF)
              CanDeclarePointerToCanHardware; /* PRQA S 3334 */ /* MD_Can_3334_LL */
              CanSetPointerToCanHardware;
              
              if ( ((STATREG & kPDA) == 0) && ((CNTRLREG & kSetPDR) == kSetPDR) )
              {
                STATUS_SLEEP(channel) = kCanFalse;
                transitionDone = kCanFailed;
              }
              else
              {
                STATUS_SLEEP(channel) = kCanTrue; /* SBSW_CAN_LL006 */
                transitionDone = kCanOk;
              }
              #endif
              
              if ( transitionDone == CAN_OK ) /* PRQA S 3355,3356,3358,3359,3353 */ /* MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7,MD_Can_3353_Asr_CommonCanTransition */
              { /* Mode changed - notify and reset request */  /* PRQA S 3201 */ /* MD_Can_3201 */
                CanHookStateChange_SleepAsync(canStatus[channel], (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_STOP))) | CAN_STATUS_SLEEP) ); /* PRQA S 0277 */ /* MD_Can_0277_negation */
                canStatus[channel] = (uint8)((canStatus[channel] & (uint8)(~(CAN_STATUS_STOP))) | CAN_STATUS_SLEEP); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_HL03 */
                canStatusReq[channel] = CAN_STATUS_UNINIT; /* SBSW_CAN_HL05 */
                /* CAN234, CAN373 */
                CanIf_ControllerModeIndication( (uint8)channel, CANIF_CS_SLEEP ); /* SBSW_CAN_HL01 */
              }
            }
            break;
#  endif /* C_ENABLE_SLEEP_WAKEUP */
          case CAN_STATUS_UNINIT:
            break;
          default:
            Can_CallDetReportError(CAN_MAINFCT_MODE_ID, CAN_E_TRANSITION); /* SBSW_CAN_HL06 */
            break;
        }
      }
    } /* over all channels*/
    Can_LeaveCritical(CAN_EXCLUSIVE_AREA_6); /* SBSW_CAN_HL11 */
  }
  CanHookEnd_Can_MainFunction_Mode();
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
#endif


/****************************************************************************
| NAME:             Can_CancelTx
| CALLED BY:        Interface()
| PRECONDITIONS:    none
| INPUT PARAMETERS: Can_HwHandleType Hth, PduIdType PduId
| RETURN VALUES:    none
| DESCRIPTION:      Cancel the tx message in hw buffer (hardware dependent) or just mark as do not confirmation
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_CancelTx( Can_HwHandleType Hth, PduIdType PduId )
{
#if ( CAN_CANCEL_SUPPORT_API == STD_ON )
  CAN_CHANNEL_CANTYPE_LOCAL
  Can_HwHandleType txObjHandle;
  CanObjectHandle logTxObjHandle;
  CanHookBegin_Can_CancelTx();
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  canHwChannel = CAN_MAILBOX[Hth].MsgController;
# endif
  txObjHandle = CAN_MAILBOX[Hth].HwHandle;
  logTxObjHandle = (CanObjectHandle)(txObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(channel));

  /* CAN248 */
  Can_CheckDetErrorReturnVoid((canControllerConfigPtr[CAN_HL_HW_CHANNEL_STARTINDEX(channel)] != NULL_PTR), CAN_WRITE_ID, CAN_E_UNINIT); /* SBSW_CAN_HL06 */
  Can_CheckDetErrorReturnVoid(( (CAN_MAILBOX[Hth].MailboxType == TxBasicCANType) ||
                                (CAN_MAILBOX[Hth].MailboxType == TxFullCANType) ),
                              CAN_WRITE_ID, CAN_E_PARAM_HANDLE); /* SBSW_CAN_HL06 */
# if defined ( C_ENABLE_MULTI_ECU_CONFIG )
  Can_CheckDetErrorReturnVoid(((cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) != (cantVIdentityMsk)0),
                              CAN_WRITE_ID, CAN_E_PARAM_HANDLE); /* SBSW_CAN_HL06 */
# endif
  {
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
    uint8_least muxTx;
    if ( CAN_MAILBOX[Hth].MailboxType == TxBasicCANType )
    {
      for (muxTx = 0; muxTx < CAN_MULTIPLEXED_TX_MAX; muxTx++)
      {
        if (CAN_ACTIVESEND_PDUID(logTxObjHandle) == PduId)
        {
          break;
        }
        logTxObjHandle++;
        txObjHandle++;
      }
    }
# endif
    if ((CAN_ACTIVESEND_PDUID(logTxObjHandle) == PduId) && ((CAN_ACTIVESEND_STATE(logTxObjHandle) == CANSENDOBJ)||(CAN_ACTIVESEND_STATE(logTxObjHandle) == CANCANCELOBJ)))
    { /* object to cancel is valid */
      CAN_ACTIVESEND_STATE(logTxObjHandle) = CANCANCELOBJSW; /* mark as canceled by SW */ /* SBSW_CAN_HL09, SBSW_CM_CAN_HL56 */
    }
  }
#else /* CAN_CANCEL_SUPPORT_API == STD_ON */
  CanHookBegin_Can_CancelTx();
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Hth = Hth;      /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
  PduId = PduId;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
#endif /* CAN_CANCEL_SUPPORT_API == STD_ON */
  CanHookEnd_Can_CancelTx();
} /* PRQA S 6010 */ /* MD_MSR_STPTH */

/****************************************************************************
| NAME:             Can_ResetBusOffStart
| CALLED BY:        Interface()
| PRECONDITIONS:    none
| INPUT PARAMETERS: uint8 Controller
| RETURN VALUES:    none
| DESCRIPTION:      (compatibility functions to CANbedded stacks)
|                   Bus Off handling start - to remove Bus Off state
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_ResetBusOffStart( uint8 Controller )
{
  CanHookBegin_Can_ResetBusOffStart();
#if ( CAN_BUSOFF_SUPPORT_API == STD_ON )
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnVoid((channel < kCanNumberOfChannels), CAN_CTRBUSOFF_ID, CAN_E_PARAM_CONTROLLER); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL24 */
# endif
# if defined ( C_ENABLE_MULTI_ECU_CONFIG )
  if ( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) != (cantVIdentityMsk)0 )
# endif
  {
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
    CanResetBusOffStart(channel, lastInitObject[channel]); /* SBSW_CAN_HL18 */
# else
    CanResetBusOffStart(lastInitObject[channel]); /* SBSW_CAN_HL18 */
#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
    Controller = Controller;        /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
#  endif
# endif
  }
#else
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;        /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
#endif /* ( CAN_BUSOFF_SUPPORT_API == STD_ON ) */
  CanHookEnd_Can_ResetBusOffStart();
}
/****************************************************************************
| NAME:             Can_ResetBusOffEnd
| CALLED BY:        Interface()
| PRECONDITIONS:    none
| INPUT PARAMETERS: uint8 Controller
| RETURN VALUES:    none
| DESCRIPTION:      (compatibility functions to CANbedded stacks)
|                   Bus Off handling end (may be asyncron to start) - to remove Bus Off state
****************************************************************************/
V_DEF_FUNC(V_NONE, void, CODE) Can_ResetBusOffEnd( uint8 Controller )
{
  CanHookBegin_Can_ResetBusOffEnd();
#if ( CAN_BUSOFF_SUPPORT_API == STD_ON )
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
  Can_SilentBswCheckErrorReturnVoid((channel < kCanNumberOfChannels), CAN_CTRBUSOFF_ID, CAN_E_PARAM_CONTROLLER); /* SBSW_CAN_HL06, SBSW_CM_CAN_HL25 */
# endif
# if defined ( C_ENABLE_MULTI_ECU_CONFIG )
  if ( (cantVIdentityMsk)(CanChannelIdentityAssignment[channel] & V_ACTIVE_IDENTITY_MSK) != (cantVIdentityMsk)0 )  /* PRQA S 2004 */ /* MD_Can_2004 */
# endif
  {
    canIsBusOff[channel] = FALSE; /* no more busoff */ /* SBSW_CAN_HL17 */ /* do this before CanResetBusOffEnd() so LL may overwrite it */
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_OFF )
    CanResetBusOffEnd(channel, lastInitObject[channel]); /* SBSW_CAN_HL18 */
# else
    CanResetBusOffEnd(lastInitObject[channel]); /* SBSW_CAN_HL18 */
# endif
#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
    Controller = Controller;      /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
#  endif
  }
#else
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;        /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
#endif /* ( CAN_BUSOFF_SUPPORT_API == STD_ON ) */
  CanHookEnd_Can_ResetBusOffEnd();
}

#if (CAN_GET_STATUS == STD_ON)
/****************************************************************************
| NAME:             Can_GetStatus
| CALLED BY:        NM
| PRECONDITIONS:    No reentrance
| INPUT PARAMETERS: uint8 Controller
| RETURN VALUES:    Bit coded status:
|                   CAN_STATUS_STOP
|                   CAN_STATUS_INIT
|                   CAN_STATUS_INCONSISTENT, CAN_DEACTIVATE_CONTROLLER
|                   CAN_STATUS_WARNING
|                   CAN_STATUS_PASSIVE
|                   CAN_STATUS_BUSOFF
|                   CAN_STATUS_SLEEP
| DESCRIPTION:      return the status of the hardware. 
|                   Only one of the statusbits Sleep,Stop,Busoff,Passiv,Warning is set.
|                   Sleep has the highest priority, error warning the lowest.
|                   CAN_STATUS_INCONSISTENT will be set if one Common CAN channel 
|                   is not stop or sleep.
|                   CAN_DEACTIVATE_CONTROLLER is set in case RAM_CHECH detect Issue
****************************************************************************/
V_DEF_FUNC(V_NONE, uint8, CODE) Can_GetStatus( uint8 Controller )
{
  Can_CheckDetErrorReturnValue((channel < kCanNumberOfChannels), CAN_HW_ACCESS_ID, CAN_E_PARAM_CONTROLLER, 0); /* SBSW_CAN_HL06 */
  CanHookBegin_Can_GetStatus();
# if defined( C_ENABLE_SLEEP_WAKEUP )
  /***************************** verify Sleep mode *************************************/
  if ( CanHL_IsSleep(channel) )
  {
    CanHookEnd_Can_GetStatus();
    return ((uint8)((canStatus[channel] & CAN_STATUS_INIT) | CAN_STATUS_SLEEP));
  }

# endif
  /***************************** verify Stop mode *************************************/
  if ( CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY) )
  {
    CanHookEnd_Can_GetStatus();
    return ((uint8)((canStatus[channel] & CAN_STATUS_INIT) | CAN_STATUS_STOP));
  }
  /***************************** verify Busoff *************************************/
  if ( CanLL_HwIsBusOff(CAN_HW_CHANNEL_CANPARA_ONLY) )
  {
    CanHookEnd_Can_GetStatus();
    return ((uint8)((canStatus[channel] & CAN_STATUS_INIT) | CAN_STATUS_BUSOFF));
  }
# if defined( C_ENABLE_EXTENDED_STATUS )
  /***************************** verify Error Passiv *******************************/
  {
    if ( CanLL_HwIsPassive(CAN_HW_CHANNEL_CANPARA_ONLY) )  
    {
      CanHookEnd_Can_GetStatus();
      return ((uint8)((canStatus[channel] & CAN_STATUS_INIT) | CAN_STATUS_PASSIVE));
    }
  }
  /***************************** verify Error Warning ******************************/
  {
    if ( CanLL_HwIsWarning(CAN_HW_CHANNEL_CANPARA_ONLY) )
    {
      CanHookEnd_Can_GetStatus();
      return ((uint8)((canStatus[channel] & CAN_STATUS_INIT) | CAN_STATUS_WARNING));
    }
  }
# endif /* C_ENABLE_EXTENDED_STATUS */
# if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON ) && defined( V_ENABLE_USE_DUMMY_STATEMENT )
  Controller = Controller;  /* dummy assignment avoid compiler warning */ /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
  CanHookEnd_Can_GetStatus();
  return ((uint8)(canStatus[channel] & CAN_STATUS_INIT));
}
#endif


#define CAN_STOP_SEC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/****************************************************************************/

/****************************************************************************/
/*  excluded Requirements                                                   */
/****************************************************************************/
/* part of other component: CAN240, CAN241, CAN256, CAN249 */
/* Currently no use-case / not supported: CAN242, CAN243, CAN244, CAN284 */

/****************************************************************************/
/*  MISRA deviations                                                        */
/****************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_Can_Asr_0781
Misra Rule 5.6
  Reason: Same name is used for same kind of data
  Risk: None.
  Prevention: None

MD_Can_3408_Asr_libCheck
Misra Rule 8.8
  Reason: external linkage used for library check
  Risk: library check failed.
  Prevention: Integration test version check

MD_Can_Asr_3447
Misra Rule 8.8
  Reason: external linkage but not in header file because this is only used for Driver internal
  Risk: Symbolic conflict for other module
  Prevention: module prefix are part of symbol and possible conflicts checked by linker

MD_Can_Asr_3408
Misra Rule 8.8
  Reason: external linkage but not in header file because this is only used for Driver internal
  Risk: Symbolic conflict for other module
  Prevention: module prefix are part of symbol and possible conflicts checked by linker

MD_Can_3353_Asr_logTxobjHandle
Misra Rule 9.1
  Reason: Because CAN_MULTIPLEXED_TX_MAX is at least 1 the variable logTxobjHandle_use is always set before
  Risk: None
  Prevention: None

MD_Can_3353_Asr_CommonCanTransition
Misra Rule 9.1
  Reason: TransitionDone will be set depend on CommonCAN loop usage. Because CommonCAN loop will always be entered the value will be set.
  Risk: None
  Prevention: None

MD_Can_Asr_3418
Misra Rule 12.10
  Reason: comma operator in for-loop header used to get a compact code
  Risk: None
  Prevention: None

MD_Can_Asr_2018
Misra Rule 14.1
  Reason: default case is not necessary for all configurations
  Risk: None
  Prevention: None

MD_Can_2004
Misra Rule 14.10
  Reason: no default handling needed for if-else-if here
  Risk: missing default handling
  Prevention: Review

MD_Can_0881_Asr_abstract
Misra Rule 19.12
  Reason: Compiler abstraction need replacement of classes to avoid name conflict. Order of ## operator is irrelevant here.
  Risk: None
  Prevention: None

MD_Can_3689_Asr_MuxTx
Misra Rule 21.1
  Reason: muxTx index seems to be out of bounds for the array canTxBasicDataBuffer but it is limited to maximum size of array.
  Risk: None
  Prevention: Review



MD_Can_3436:
Major
  Reason: Compatibility define used here.
  Risk: name conflict.
  Prevention: Code review and compiler check for name conflicts.

MD_Can_0715:
Misra Rule 1.1
  Reason: Complex code structure used and not split in modules or functions to make the code compact and efficent.
  Risk: Hard to understand.
  Prevention: Code inspection and multiple configuration aspects used in component test.

MD_Can_0828:
Misra Rule 1.1
  Reason: Nesting of #if statements bigger than 8 depends on configuration aspects.
  Risk: Compiler does not support that.
  Prevention: Used Compilers checked and limitations form ANSI is not relevant.

MD_Can_0857:
Misra Rule 1.1
  Reason: Macros used to make the code compact and efficent.
  Risk: Hard to understand.
  Prevention: Code inspection and multiple configuration aspects used in component test.

MD_Can_0277_negation:
Misra Rule 3.1
  Reason: negation of an unsigned value used to mask bits.
  Risk: None.
  Prevention: None.

MD_Can_0277_invalid:
Misra Rule 3.1
  Reason: define a invalid value by use highest value of the given data type.
  Risk: None.
  Prevention: None.

MD_Can_3218:
Misra Rule 8.7
  Reason: The usage of variables depend on configuration aspects and may be used only once, or defined global to improve overview.
  Risk: name conflict.
  Prevention: Compiler optimize and check for name conflicts.

MD_Can_3684:
Misra Rule 8.12
  Reason: Arrays declared without size, because size depends on configuration and is unknown here, especially for linktime tables.
  Risk: Data access outside table.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3760_LogToHw:
Misra Rule 10.01
  Reason: Calculating hardware index out of logical need a negative value in calcuation, but result is always positive.
  Risk: Data access out of bounce.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_0303_HWaccess:
Misra Rule 11.3
  Reason: Hardware access need pointer to CAN cell as volatile.
  Risk: Access of unknown memory.
  Prevention: Runtime tests.

MD_Can_0310:
Misra Rule 11.4
  Reason: cast increase performance here.
  Risk: pointer alignment does not fit and wrong memory is accessed.
  Prevention: Code inspection and component test.

MD_Can_0311:
Misra Rule 11.5
  Reason: Const pointer used only for read access. Same macro is used also for none const pointer.
  Risk: None.
  Prevention: None.

MD_Can_0312:
Misra Rule 11.5
  Reason: cast to none volatile pointer is ok here because usage of data is read only here.
  Risk: Upper Layer has to make sure that there is no write access to this data.
  Prevention: Documentation of API.

MD_Can_13.7:
Misra Rule 13.7
  Reason: Result or value is always true or false depend on configuration aspect and used platform specific implementation
  Risk: Incorrect platform specific return will be ignored.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3201:
Misra Rule 14.1
  Reason: Configuration or platform specific dependent unreachable code.
  Risk: Incorrect behavior depend on settings.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3109:
Misra Rule 14.3
  Reason: Empty statements occur multiple times because macros used like functions, and configuration aspects may deactivate complete functionality.
  Risk: Functionality unexpected missing.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_2001:
Misra Rule 14.4
  Reason: 'goto' statement used to optimize code (readability and runtime).
  Risk: Incorrect jump.
  Prevention: Code inspection.

MD_Can_0770:
Misra Rule 14.5
  Reason: 'continue' statement used to optimize code (readability and runtime).
  Risk: Relevant fragments of code not executed.
  Prevention: Code inspection.

MD_Can_14.6:
Misra Rule 14.6
  Reason: multiple break used for optimize code runtime
  Risk: Relevant fragments of code not executed.
  Prevention: Code inspection.

MD_Can_2006:
Misra Rule 14.7
  Reason: Multiple return path used to optimize code (readability and runtime).
  Risk: Return a function too soon.
  Prevention: Code inspection.

MD_Can_17.4:
Misra Rule 17.4
  Reason: Pointer arithmetic used multiple times to optimize runtime.
  Risk: Access wrong memory.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_0750:
Misra Rule 18.4
  Reason: Using union type to handel configuration specific data access.
  Risk: Misinterpreted data.
  Prevention: Code inspection.

MD_Can_3412:
Misra Rule 19.4
  Reason: Complex Macros with unrecognised code-fragment used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_3458:
Misra Rule 19.4
  Reason:Complex Macros with unbraced code statement blocks used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_3460:
Misra Rule 19.4
  Reason: void used as macro to get configuration specific API.
  Risk: Readability reduced.
  Prevention: Compile test.

MD_Can_0841:
Misra Rule 19.6
  Reason:undefine macro for compatibility reasons and re-usage of platform specific code.
  Risk: Meaning of macro is uncertain and may lead to wrong implementation.
  Prevention: Code inspection, compile tests and runtime tests.

MD_Can_3453:
Misra Rule 19.7
  Reason: Complex Macros used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_0850:
Misra Rule 19.8
  Reason: Macro argument is empty depend on usage of compiler abstraction.
  Risk: None.
  Prevention: Code inspection.

  MD_Can_3410:
Misra Rule 19.10
  Reason: Parameter used in structures that does not allow brackets
  Risk: None atomic parameter lead to compile errors
  Prevention: Used parameter is always atomic depend on usage

MD_Can_0342:
Misra Rule 19.13
  Reason: Glue operator used to abstract AuotSar compiler abstraction
  Risk: Only K&R compiler support glue operator
  Prevention: Compile test show whether compiler accept glue operator

MD_Can_3199_dummy:
Redundancy
  Reason: Dummy assignment used to satisfy API parameters that are never used.
  Risk: None.
  Prevention: None.





MD_Can_3334_LL:
Misra Rule 5.2
  Reason: CanDeclarePointerToCanHardware defines a variable
  Risk: no type check with MISRA possible.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3746_LL:
Misra Rule 10.1
  Reason: returns a value which is not being used
  Risk: no check of the return value.
  Prevention: Return value not necessary here.

MD_Can_4130_LL:
Misra Rule 12.7
  Reason: Bitwise operations on signed data will give implementation defined results
  Risk: issue in result.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3344_LL:
Misra Rule 13.2
  Reason: Value of control expression is not derived from an explicit logical operation.
  Risk: issue in control expression.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3325_LL
Misra Rule 14.01
  Reason: expression has a constant 'false' value
  Risk: potential that there is a issue in the expression.
  Prevention: Code inspection and test of the different variants in the component test.
MD_Can_3201_LL:
Misra Rule 14.01
  Reason: statement is unreachable
  Risk: potential that there is a issue in the expression.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3200_LL
Misra Rule 16.10
  Reason: returns a value which is not being used
  Risk: no check of the return value.
  Prevention: Return value not necessary here.

*/

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */

/************   Organi, Version 3.9.1 Vector-Informatik GmbH  ************/
